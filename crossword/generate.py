import sys

from crossword import *
import copy

class CrosswordCreator():

    def __init__(self, crossword):
        """
        Create new CSP crossword generate.
        """
        self.crossword = crossword
        self.domains = {
            var: self.crossword.words.copy()
            for var in self.crossword.variables
        }

    def letter_grid(self, assignment):
        """
        Return 2D array representing a given assignment.
        """
        letters = [
            [None for _ in range(self.crossword.width)]
            for _ in range(self.crossword.height)
        ]
        for variable, word in assignment.items():
            direction = variable.direction
            for k in range(len(word)):
                i = variable.i + (k if direction == Variable.DOWN else 0)
                j = variable.j + (k if direction == Variable.ACROSS else 0)
                letters[i][j] = word[k]
        return letters

    def print(self, assignment):
        """
        Print crossword assignment to the terminal.
        """
        letters = self.letter_grid(assignment)
        for i in range(self.crossword.height):
            for j in range(self.crossword.width):
                if self.crossword.structure[i][j]:
                    print(letters[i][j] or " ", end="")
                else:
                    print("█", end="")
            print()

    def save(self, assignment, filename):
        """
        Save crossword assignment to an image file.
        """
        from Pillow import Image, ImageDraw, ImageFont
        cell_size = 100
        cell_border = 2
        interior_size = cell_size - 2 * cell_border
        letters = self.letter_grid(assignment)

        # Create a blank canvas
        img = Image.new(
            "RGBA",
            (self.crossword.width * cell_size,
             self.crossword.height * cell_size),
            "black"
        )
        font = ImageFont.truetype("assets/fonts/OpenSans-Regular.ttf", 80)
        draw = ImageDraw.Draw(img)

        for i in range(self.crossword.height):
            for j in range(self.crossword.width):

                rect = [
                    (j * cell_size + cell_border,
                     i * cell_size + cell_border),
                    ((j + 1) * cell_size - cell_border,
                     (i + 1) * cell_size - cell_border)
                ]
                if self.crossword.structure[i][j]:
                    draw.rectangle(rect, fill="white")
                    if letters[i][j]:
                        w, h = draw.textsize(letters[i][j], font=font)
                        draw.text(
                            (rect[0][0] + ((interior_size - w) / 2),
                             rect[0][1] + ((interior_size - h) / 2) - 10),
                            letters[i][j], fill="black", font=font
                        )

        img.save(filename)

    def solve(self):
        """
        Enforce node and arc consistency, and then solve the CSP.
        """
        self.enforce_node_consistency()
        self.ac3()
        return self.backtrack(dict())

    def enforce_node_consistency(self):
        """
        Update `self.domains` such that each variable is node-consistent.
        (Remove any values that are inconsistent with a variable's unary
         constraints; in this case, the length of the word.)
        """
        # make copy cuz we need to revise original domain
        domain = copy.deepcopy(self.domains)

        for variable in domain:
            # loop thru words in domain
            for word in domain[variable]:
                if len(word) != variable.length:
                    # if length of the word != variable length, delete it from orig
                    self.domains[variable].remove(word)

    def revise(self, x, y):
        """
        Make variable `x` arc consistent with variable `y`.
        To do so, remove values from `self.domains[x]` for which there is no
        possible corresponding value for `y` in `self.domains[y]`.

        Return True if a revision was made to the domain of `x`; return
        False if no revision was made.
        """
        # overlapping stuff
        ex, why = self.crossword.overlaps[x, y]
        revised = False
        domain = copy.deepcopy(self.domains)

        # if overlap
        if ex is not None:
            # look thru words in x's domain
            for word_in_x in domain[x]:
                matched_value = False
                # loop thru words in y's domain
                for word_in_y in self.domains[y]:
                    # if x's word and y's word have same letter in overlapping position
                    if word_in_x[ex] == word_in_y[why]:
                        matched_value = True
                        break  
                if matched_value:
                    continue   # proceed with another x
                else:
                    self.domains[x].remove(word_in_x)
                    revised = True
        return revised

    def ac3(self, arcs=None):
        """
        Update `self.domains` such that each variable is arc consistent.
        If `arcs` is None, begin with initial list of all arcs in the problem.
        Otherwise, use `arcs` as the initial list of arcs to make consistent.

        Return True if arc consistency is enforced and no domains are empty;
        return False if one or more domains end up empty.
        """
        # no arcs provided, start with an empty queue of all of the arcs in the problem
        if not arcs:
            queue = []
            for variable1 in self.domains:
                for variable2 in self.crossword.neighbors(variable1):
                    # if var1 and var2 aren't the same
                    if self.crossword.overlaps[variable1, variable2] is not None:
                        queue.append((variable1, variable2))

        while len(queue) > 0:
            x, y = queue.pop(0)
            # if x and y are revised
            if self.revise(x, y):
                # if domain of x has nothing left
                if len(self.domains[x]) == 0:
                    return False
                # get neighbours
                for neighbour in self.crossword.neighbors(x):
                    if neighbour != y:
                        queue.append((neighbour, x))
            return True

    def assignment_complete(self, assignment):
        """
        Return True if `assignment` is complete (i.e., assigns a value to each
        crossword variable); return False otherwise.
        """
        for variable in self.domains:
            if variable not in assignment:
                return False
        return True

    def consistent(self, assignment):
        """
        Return True if `assignment` is consistent (i.e., words fit in crossword
        puzzle without conflicting characters); return False otherwise.
        """
        # 1) all values are distinct
        # 2) every value is the correct length
        # 3) there are no conflicts between neighboring variables.

        # check if all values are distinct
        words = [*assignment.values()]
        if len(words) != len(set(words)):
            return False

        # check if every value is the correct length
        for variable in assignment:
            if variable.length != len(assignment[variable]):
                return False

        # check if there are any conflicts between neighbouring variables
        for variable in assignment:
            for neighbour in self.crossword.neighbors(variable):
                if neighbour in assignment:
                    x, y = self.crossword.overlaps[variable, neighbour]
                    if assignment[variable][x] != assignment[neighbour][y]:
                        return False
        return True


    def order_domain_values(self, var, assignment):
        """
        Return a list of values in the domain of `var`, in order by
        the number of values they rule out for neighboring variables.
        The first value in the list, for example, should be the one
        that rules out the fewest values among the neighbors of `var`.
        """
        words = {}
        neighbours = self.crossword.neighbors(var)

        for word in self.domains[var]:
            delete = 0
            for neighbour in neighbours:
                # don't count if neighbor has already assigned value
                if neighbour in assignment:
                    continue
                else:
                    # calculate overlap between two variables
                    ex, why = self.crossword.overlaps[var, neighbour]
                    for neighbour_word in self.domains[neighbour]:
                        # loop thru neighbour's words
                        if word[ex] != neighbour_word[why]:
                            delete += 1
            # add eliminated neighbour's words
            words[word] = delete
        # sort by number of eliminated neighbour values
        sort = {k: v for k, v in sorted(words.items(), key=lambda item: item[1])}
        return [*sort]

    def select_unassigned_variable(self, assignment):
        """
        Return an unassigned variable not already part of `assignment`.
        Choose the variable with the minimum number of remaining values
        in its domain. If there is a tie, choose the variable with the highest
        degree. If there is a tie, any of the tied variables are acceptable
        return values.
        """
        choice = {}
        for variable in self.domains:
            if variable not in assignment:
                choice[variable] = self.domains[variable]

        sorted_list = [v for v, k in sorted(choice.items(), key=lambda item:len(item[1]))]
        return sorted_list[0]

    def backtrack(self, assignment):
        """
        Using Backtracking Search, take as input a partial assignment for the
        crossword and return a complete assignment if possible to do so.

        `assignment` is a mapping from variables (keys) to words (values).

        If no assignment is possible, return None.
        """
        if len(assignment) == len(self.domains):
            return assignment

        # selecting one unassigned variables
        variable = self.select_unassigned_variable(assignment)
        for value in self.domains[variable]:
            # making assignment copy, with updated variable value
            assign = assignment.copy()
            assign[variable] = value
            # check consistency
            if self.consistent(assign):
                result = self.backtrack(assign)
                if result is not None:
                    return result
        return None

def main():

    # Check usage
    if len(sys.argv) not in [3, 4]:
        sys.exit("Usage: python generate.py structure words [output]")

    # Parse command-line arguments
    structure = sys.argv[1]
    words = sys.argv[2]
    output = sys.argv[3] if len(sys.argv) == 4 else None

    # Generate crossword
    crossword = Crossword(structure, words)
    creator = CrosswordCreator(crossword)
    assignment = creator.solve()

    # Print result
    if assignment is None:
        print("No solution.")
    else:
        creator.print(assignment)
        if output:
            creator.save(assignment, output)


if __name__ == "__main__":
    main()
