import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.Font;
import java.awt.GridBagConstraints;

import javax.swing.AbstractAction;
import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.KeyStroke;
import javax.swing.SwingConstants;
import javax.swing.UIManager;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridBagLayout;
import java.awt.event.ActionEvent;
import java.awt.event.KeyEvent;

public class ConnectFour {

	JFrame frame;
	JPanel board, mainPanel;
	JLabel[][] template;
	JLabel[] positions;
	JLabel message;
	
	String player;
	String p1 = "x";
	String p2 = "o";
	String[][] temp;
	int position;

	public static void main(String[] args) {
		EventQueue.invokeLater(new Runnable() {
			@SuppressWarnings("unused")
			public void run() {
				try {
					ConnectFour window = new ConnectFour();
					UIManager.put("OptionPane.background", Color.WHITE); // changes the joptionpane background colours
					UIManager.getLookAndFeelDefaults().put("Panel.background", Color.WHITE);
					UIManager.put("Button.background", Color.white);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	public ConnectFour() {
		this.position = 3; // position the player starts with
		player = p1;
		initialize(player, 0);
	}
	
	public void clean() { // cleans the boarda fter each game
		for (int i = 0; i < 6; i++) {
			for (int j = 0; j < 8; j++) {
				temp[i][j] = " ";
				
				template[i][j] = new JLabel();
				template[i][j].setText("|   " + temp[i][j] + "   ");
				template[i][j].setFont(new Font("Times New Roman", Font.PLAIN, 15));		
			}
		}
	}

	private void initialize(String p, int index) {
		
		frame = new JFrame();
		frame.setBackground(Color.WHITE);
		
		mainPanel = new JPanel(new FlowLayout());
		mainPanel.setBackground(Color.WHITE);
		mainPanel.setBorder(BorderFactory.createEmptyBorder(50, 5, 5, 5));
        
        this.positions = new JLabel[7]; // sets up the header that allows the x and o tokens to move across the spaces
        for (int i = 0; i < positions.length; i++) {
        	positions[i] = new JLabel(" ");
        	positions[i].setFont(new Font("Times New Roman", Font.PLAIN, 15));
        	mainPanel.add(positions[i]);
            if (index < (positions.length - 1)) {
            	mainPanel.add(Box.createHorizontalStrut(25));
            }
        }
        
        updatePosition(position, player);
        
        frame.add(mainPanel, BorderLayout.NORTH);
        setKeyBindings(mainPanel);
        
        frame.pack();
        frame.setLocationByPlatform(true);
        frame.setVisible(true);
		
		board = new JPanel();
		board.setBackground(Color.WHITE);
		frame.getContentPane().add(board, BorderLayout.CENTER);
		board.setPreferredSize(new Dimension(400, 10));
		
		GridBagLayout g = new GridBagLayout();
		GridBagConstraints gbc = new GridBagConstraints();
		board.setLayout(g);
		gbc.fill = GridBagConstraints.HORIZONTAL;
		
		template = new JLabel[6][8];
		temp = new String[6][8];

		for (int i = 0; i < 6; i++) { // sets up the board
			for (int j = 0; j < 8; j++) {
				temp[i][j] = " ";
				
				template[i][j] = new JLabel();
				template[i][j].setText("|   " + temp[i][j] + "   ");
				template[i][j].setFont(new Font("Times New Roman", Font.PLAIN, 15));	
				gbc.gridx = j;
				gbc.gridy = i;
				board.add(template[i][j], gbc);
				
			}
		}
		
		JLabel[] bottom = new JLabel[7];
		for (int i = 0; i < 7; i++) {
			bottom[i] = new JLabel("``````````");
			gbc.gridx = i;
			gbc.gridy = 8;
			board.add(bottom[i], gbc);
		}
		
		frame.setBounds(100, 100, 450, 300);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		playMove(mainPanel);
		frame.setLocationRelativeTo(null);  
		frame.setVisible(true);
		
	}
	
    public void choosePlayer(String p) { // toggles players
        if (p == "x") {
            player = "o"; // toggles
            System.out.println("Toggled!");
            updatePosition(position, " ");
            position = 3;
            updatePosition(3, player);
            playMove(mainPanel);
        } else if (p == "o") {
            player = "x"; // toggles
            System.out.println("Toggled!");
            updatePosition(position, " ");
            position = 3;
            updatePosition(3, player);
            playMove(mainPanel);
        }
    }
    
    public void updatePosition(int position, String value) { // ...yeah
        positions[position].setText(value);
    }
    
	public void playMove(JPanel jp) {        
        setKeyBindings(jp);
        
        frame.getContentPane().validate();
        frame.getContentPane().repaint();
        
    }
    
    public class ShiftRightAction extends AbstractAction {

        private static final long serialVersionUID = 1L;

        @Override
        public void actionPerformed(ActionEvent event) {
        	updatePosition(position, " ");
            position++;
            if (position > 6) {
            	position = 6;
            	updatePosition(position, player);
            } else {
            	updatePosition(position, player);
            	
            }
        }
        
    }
    
    public class ShiftLeftAction extends AbstractAction {

        private static final long serialVersionUID = 1L;

        @Override
        public void actionPerformed(ActionEvent event) {
        	updatePosition(position, " ");
            position--;
            if (position < 0) {
            	position = 0;
            	updatePosition(position, player);
            } else {
            	updatePosition(position, player);
            	
            }
        }
        
    }
    
    public class dropToken extends AbstractAction {

        private static final long serialVersionUID = 1L;

		@Override
        public void actionPerformed(ActionEvent event) {
            int index = position;
            
            for (int i = 1; i < 6; i++) {
            	if (temp[i][index] == "x" || temp[i][index] == "o") {
            		
            		boolean cont;
            	
            		System.out.println("Heh");

            		temp[i-1][index] = player;
            		template[i-1][index].setText("|   " + temp[i-1][index] + "   ");
            		
            		cont = scanTemplate(player);
            		System.out.println("continue? " + cont);
            		
            		String m = "Player " + player + " has won!! Play again?";
            		JLabel woohoo = new JLabel(m);
            		woohoo.setHorizontalAlignment(SwingConstants.CENTER);
        			woohoo.setFont(new Font("Times New Roman", Font.PLAIN, 15));
            		
            		if (cont == false) {
            			System.out.println("WHOOP WHOOP");
            			
            			int result = JOptionPane.showConfirmDialog(frame, woohoo, "Alexa play celebratory music",
            		               JOptionPane.YES_NO_OPTION,
            		               JOptionPane.PLAIN_MESSAGE);
            		            if(result == JOptionPane.YES_OPTION){
            		            	// frame.setVisible(false);
            		            	clean();
            		            	frame.setVisible(false);
                    			    new ConnectFour();
            		            } else if (result == JOptionPane.NO_OPTION){
            		            	System.exit(0);
            		            }
            			
            		} else {
            			choosePlayer(player);
                		break;
            		}
            	            		
            	} else if (temp[5][index] == " ") {
            		temp[5][index] = player;
            		template[5][index].setText("|   " + temp[5][index] + "   ");
            		System.out.println("Hah");
            		boolean cont = scanTemplate(player);
            		System.out.println("continue? " + cont);
            		if (cont == false) {
            			System.out.println("WHOOP WHOOP");
            		} else {
            			choosePlayer(player);
                		break;
            		}
            		
            	}
            	
            }
            
            for (int ii = 0; ii < 6; ii++) {
        		for (int j = 0; j < 8; j++) {
        			System.out.print("[" + temp[ii][j] + "]");
        		} System.out.print("\n");
        	}
            
        }
        
    }
    
    
    private void setKeyBindings(JPanel panel) {
        panel.getInputMap().put(
                KeyStroke.getKeyStroke(KeyEvent.VK_RIGHT, 0), "shiftRight");
        panel.getActionMap().put("shiftRight", new ShiftRightAction());
        panel.getInputMap().put(
                KeyStroke.getKeyStroke(KeyEvent.VK_LEFT, 0), "shiftLeft");
        panel.getActionMap().put("shiftLeft", new ShiftLeftAction());
        panel.getInputMap().put(
                KeyStroke.getKeyStroke(KeyEvent.VK_ENTER, 0), "drop");
        panel.getActionMap().put("drop", new dropToken());
    }
     
      public boolean scanTemplate(String p) {
	        boolean notFull = scanBoard();
	        System.out.println("notFull" + notFull);
	        boolean fourInARow = scanRow();
	        System.out.println("fourInARow" + fourInARow);
	        boolean fourInACol = scanColumn();
	        System.out.println("fourInACol" + fourInACol);
	        boolean fourInADiag = scanDiag();
	        System.out.println("fourInADiag" + fourInADiag);
	        if (notFull == true && fourInARow == false && fourInACol == false && fourInADiag == false) { // no wins / not full
	            return true;
	        } else if (notFull == false) {
	            return false;
	        } else if (fourInARow == true || fourInACol == true || fourInADiag == true) {
	            return false;
	        }
			return false;
	}
    		
    		
    	public boolean scanBoard() {
	        int numEmpty = 0;
	        for (int i = 0; i < 6; i++) {
	            for (int j = 0; j < 7; j++) {
	                if (temp[i][j] == " ") {
	                    numEmpty++;
	                }
	            }
	        }
	        if (numEmpty > 0) {
	            return true;
	        } else if (numEmpty == 0) {
	            return false;
	        }
			return false;
	    }

		public boolean scanRow() {
	        for (int i = 5; i >= 0; i--) { // starts from bottom row, moves up
	            int rowCountX = 0;
	            int rowCountO = 0;
	            for (int j = 0; j < 6; j++) { // starts from column 1, moves right
	                if (temp[i][j] == "x") {
	                    rowCountX++;
	                } else {
	                    rowCountX = 0;
	                }
	                if (temp[i][j] == "o") {
	                    rowCountO++;
	                } else {
	                    rowCountO = 0;
	                }
	            if (rowCountX == 4 || rowCountO == 4) {
	                return true;
	            }
	            }
	        }
			return false;
	    }

	    public boolean scanColumn() {
	        for (int j = 0; j < 7; j++) { // starts from column 1, moves right
	            int colCountX = 0;
	            int colCountO = 0;
	            for (int i = 5; i >= 0; i--) { // starts from bottom row, moves up
	                if (temp[i][j] == "x") {
	                    colCountX++;
	                } else {
	                    colCountX = 0;
	                }
	                if (temp[i][j] == "o") {
	                    colCountO++;
	                } else {
	                    colCountO = 0;
	                }
	            if (colCountX == 4 || colCountO == 4) {
	                return true;
	            }
	            }
	        }
			return false;
	    }

	    public boolean scanDiag() {
	        for (int row = 5; row > 0; row--) {
	            for (int col = 0; col < 7; col++) {
	                if (temp[row][col] == "x") {
	                    if (!(((row - 1) < 0) || ((col + 1) > 6))) {
	                        if (temp[row-1][col+1] == "x") {
	                            if (!(((row - 2) < 0) || ((col + 2) > 6))) {
	                                if (temp[row-2][col+2] == "x") {
	                                    if (!(((row - 3) < 0) || ((col + 3) > 6))) {
	                                        if (temp[row-3][col+3] == "x") {
	                                            return true;
	                                        }
	                                    }
	                                }
	                            }
	                        }
	                    }
	                }
	                if (temp[row][col] == "x") {
	                    if (!(((row - 1) < 0) || ((col - 1) < 0))) {
	                      if (temp[row-1][col-1] == "x") {
	                            if (!(((row - 2) < 0) || ((col - 2)) < 0)) {
	                                if (temp[row-2][col-2] == "x") {
	                                    if (!(((row - 3) < 0) || ((col - 3) < 0))) {
	                                        if (temp[row-3][col-3] == "x") {
	                                            return true;
	                                        }
	                                    }
	                                }
	                            }
	                        }
	                    }
	                }
	                if (temp[row][col] == "o") {
	                    if (!(((row - 1) < 0) || ((col + 1) > 6))) {
	                        if (temp[row-1][col+1] == "x") {
	                            if (!(((row - 2) < 0) || ((col + 2) > 6))) {
	                                if (temp[row-2][col+2] == "x") {
	                                    if (!(((row - 3) < 0) || ((col + 3) > 6))) {
	                                        if (temp[row-3][col+3] == "x") {
	                                            return true;
	                                        }
	                                    }
	                                }
	                            }
	                        }
	                    }
	                }
	                if (temp[row][col] == "x") {
	                    if (!(((row - 1) < 0) || ((col - 1) < 0))) {
	                        if (temp[row-1][col-1] == "x") {
	                            if (!(((row - 2) < 0) || ((col - 2)) < 0)) {
	                                if (temp[row-2][col-2] == "x") {
	                                    if (!(((row - 3) < 0) || ((col - 3) < 0))) {
	                                        if (temp[row-3][col-3] == "x") {
	                                            return true;
	                                        }
	                                    }
	                                }
	                            }
	                        }
	                    }
	                }
	            }
	        }
			return false;
	    }
    

}
