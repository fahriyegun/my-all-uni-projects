import java.awt.*;
import java.applet.*;
import java.awt.event.*;
import java.util.Random;
import java.net.URL;
import java.net.MalformedURLException;

public class Tetris extends Applet {
	
	private final static int INITIAL_DELAY = 700;
	private final static byte ROWS = 25;
	private final static byte COLUMNS = 20;
	private final static int EMPTY = -1;
	private final static int DELETED_ROWS_PER_LEVEL = 3;
	private final static Color PIECE_COLORS[] = {
		new Color(0xFF00FF), // fucia
		new Color(0xDC143C), // crimson
		new Color(0x00CED1), // dark turquoise
		new Color(0xFFD700), // gold
		new Color(0x32CD32), // lime green
		new Color(0x008080), // teal
		new Color(0xFFA500), // orange
	};
	private final static Color BACKGROUND_COLOR = new Color(0xFFFACD);
	private final static Color BACKGROUND_COLORS = new Color(0xFFE4E1);
	private final static int PIECE_BITS[][][] = {
		{
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 0, 1, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 0, 1, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 1, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 0, 0},
		},
		{
			{0, 0, 0, 0},
			{0, 0, 0, 0},
			{0, 1, 1, 0},
			{0, 1, 1, 0},
		},
	};
	private static int tmp_grid[][] = new int[4][4]; // scratch space
	private static Random random = new Random();

	private int grid[][] = new int[ROWS][COLUMNS];
	private int next_piece_grid[][] = new int[4][4];
	private int num_rows_deleted = 0;
	private GridCanvas game_grid = new GridCanvas(grid, true);
	private Timer timer;
	private TetrisPiece cur_piece;
	private TetrisPiece next_piece = randomPiece();
	static int score_label=0 ;
	final Button start_newgame_butt = new TetrisButton("START");
	
	private class TetrisButton extends Button { 						
		public TetrisButton(String label) {
			super(label);
		}
		public Dimension getPreferredSize() {
			return new Dimension(280, super.getPreferredSize().width);
		}
	}
	private class TetrisPiece {
		private int squares[][];
		private int type;																
		private Point position = new Point(3, -4); // -4 to start above top row
		public int getX() { 
			return position.x;
}
		public int getY() {
			return position.y; 
			}
		public void setX(int newx) {
			position.x = newx;
			}
		public void setY(int newy) { 
			position.y = newy;
			}
		public void setPosition(int newx, int newy) {
			setX(newx); setY(newy);
			}
		public TetrisPiece(int type) {
			this.type = type;
			this.squares = new int[4][4];
			for(int i=0; i<4; i++)
				for(int j=0; j<4; j++)
					this.squares[i][j] = PIECE_BITS[type][i][j];
		}
		public boolean canStepDown() {
			synchronized(timer) {
				cut();
				position.y++;
				boolean OK = canPaste();
				position.y--;
				paste();
				return OK;
			}
		}
		public boolean canPaste() {
			for(int i=0; i<4; i++) {
				for(int j=0; j<4; j++) {
					int to_x = j + position.x;
					int to_y = i + position.y;
					if(squares[i][j]==1) { // piece contains this square?
						if(0 > to_x || to_x >= COLUMNS // square too far left or right?
							|| to_y >= ROWS) // square off bottom?
						{
							return false;
						}
						if(to_y >= 0 && grid[to_y][to_x] != EMPTY)
							return false;
					}
				}
			}
			return true;
		}
		public void stepDown() {
			position.y++;
		}
		public void cut() {
			for(int i=0; i<4; i++)
				for(int j=0; j<4; j++)
					if(squares[i][j]==1 && position.y+i>=0)
						grid[position.y + i][position.x + j] = EMPTY;
		}
		public void paste(int into[][]) {
			for(int i=0; i<4; i++)
				for(int j=0; j<4; j++)
					if(squares[i][j]==1 && position.y+i>=0)
						into[position.y + i][position.x + j] = type;
		}
		public void paste() {
			paste(grid);
		}
		public void rotate() {
			// copy the piece's data into a temp array
			for(int i=0; i<4; i++)
				for(int j=0; j<4; j++)
					tmp_grid[i][j] = squares[i][j];
			// copy back rotated 90 degrees
			for(int i=0; i<4; i++)
				for(int j=0; j<4; j++)
					squares[j][i] = tmp_grid[i][3-j];
		}
		public void rotateBack() {
			for(int i=0; i<4; i++)
				for(int j=0; j<4; j++)
					squares[i][j] = tmp_grid[i][j];
		}
		
		public boolean isTotallyOnGrid() {
			for(int i=0; i<4; i++) {
				if(position.y + i >= 0)
					return true; //everything from here down is on grid
				// this row is above grid so look for non-empty squares
				for(int j=0; j<4; j++)
					if(squares[i][j]==0)
						return false;
			}
			System.err.println("TetrisPiece.isTotallyOnGrid internal error");
			return false;
		}
	} // end class TetrisPiece
	private class Timer extends Thread {
		private long m_delay;
		private boolean m_paused = true;
		private boolean m_fast = false;
		private ActionListener m_cb;
		public Timer(long delay, ActionListener cb) { 
			setDelay(delay);
			m_cb = cb;
		}
		public void setPaused(boolean pause) { 
			m_paused = pause;
			synchronized(this) {
					this.notify();
			}
		}
		public boolean isPaused() {
			return m_paused; 
			}
		public void setDelay(long delay) {
			m_delay = delay; 
			}
		public boolean isRunning() {
			return !m_paused; 
			}
		public void setFast(boolean fast) {
			m_fast = fast;
			if(m_fast) {
				try {
					this.checkAccess();
					this.interrupt(); // no exception, so OK to interrupt
				} catch(SecurityException se) {}
			}
		}
		public boolean isFast() {
			return m_fast; 
			}
		public void faster() {
			m_delay = (int)(m_delay * .5); //increase the speed exponentially in reverse
		}
		public void run() {
			while(true) {
				try { 
					sleep(m_fast ? 30 : m_delay); 
				} catch (Exception e) {}
				if(m_paused) {
					try {
						synchronized(this) {
							this.wait();
						}
					} catch(InterruptedException ie) {}
				}
				synchronized(this) {
					m_cb.actionPerformed(null);
				}
			}
		}
	} // end class Timer
	private class GridCanvas extends DoubleBufferedCanvas {
		private int grid[][];
		private boolean paint_background;
		public GridCanvas(int[][] grid, boolean do_background) {
			this.grid = grid;
			paint_background = do_background;
			clear();
		}
	    private void clear() {
			for(int i=0; i<grid.length; i++)
				for(int j=0; j<grid[0].length; j++)
					grid[i][j] = EMPTY; ///////// -1 leyerek sildik
		}		
		public Dimension getPreferredSize() {
			return new Dimension(grid[0].length * 0, grid.length * 50);
		}
		public void paint(Graphics g) {
			g = this.startPaint(g); // returned g paints into offscreen image
			int width = this.getSize().width;
			int height = this.getSize().height;
			g.clearRect(0, 0, width, height);
			int cell_size, xstart, ystart;
			double panel_aspect_ratio = (double)width/height;
			double grid_aspect_ratio = (double)grid[0].length/grid.length;
			if(panel_aspect_ratio > grid_aspect_ratio) { 
				// extra space on sides
				cell_size = (int)((double)height/grid.length + 0.5);
				xstart = (int)(width/2 - (grid[0].length/2.0 * cell_size + 0.5));
				ystart = 0;
			}
			else { 
				// extra vertical space
				cell_size = (int)((double)width/grid[0].length + 0.5);
				xstart = 0;
				ystart = (int)(height/2 - (grid.length/2.0 * cell_size + 0.5));
			}
			if(paint_background) {
				g.setColor(BACKGROUND_COLORS);
				g.fillRect(xstart, ystart, COLUMNS*cell_size, ROWS*cell_size);
			}
			for(int i=0; i<grid.length; i++) {
				for(int j=0; j<grid[0].length; j++) {
					if(grid[i][j] != EMPTY) {
						g.setColor(PIECE_COLORS[grid[i][j]]);
						int x = xstart + j*cell_size;
						int y = ystart + i*cell_size;
						g.fill3DRect(x, y, cell_size, cell_size, true);
					}
				}
			}
			this.endPaint(); // paints accumulated image in one shot
		}
	} // end class GridCanvas
	private TetrisPiece randomPiece() {
		int rand = Math.abs(random.nextInt());
		return new TetrisPiece(rand % (PIECE_COLORS.length));
	}
	private void installNewPiece() {
		cur_piece = next_piece;
		cur_piece.setPosition(3, -4); //-4 to start above top of grid
		if(cur_piece.canPaste()) {
			next_piece = randomPiece();
			next_piece.setPosition(0, 0);
			next_piece.paste(next_piece_grid);
			
		}
		else
			gameOver();
	}
	private void gameOver() {
		timer.setPaused(true);
		int score = score_label;
		System.out.println("Game Over!\nYour score:" +score);
	}
	private boolean rowIsFull(int row) {
		for(int i=0; i<COLUMNS; i++)
			if(grid[row][i] == EMPTY)
				return false;
		return true;
	}
	private int countFullRows() {
		int n_full_rows = 0;
		for(int i=0; i<ROWS; i++)
			if(rowIsFull(i))
				n_full_rows++;
		return n_full_rows;
	}	
	private void removeRow(int row) {
		for(int j=0; j<COLUMNS; j++)
			grid[row][j] = EMPTY;
		for(int i=row; i>0; i--) {
			for(int j=0; j<COLUMNS; j++) {
				grid[i][j] = grid[i-1][j];
			}
		}
	}
	private void removeFullRows() {
		int n_full = countFullRows();
		score_label =score_label+(int) (10*Math.pow(2, n_full) - 10); //give points exponentially
		if(n_full == 0)
		return;
		if(num_rows_deleted / DELETED_ROWS_PER_LEVEL != (num_rows_deleted+n_full) / DELETED_ROWS_PER_LEVEL) {
			timer.faster();
			
		}
		num_rows_deleted += n_full;
		for(int i=ROWS-1; i>=0; i--)
			while(rowIsFull(i))
				removeRow(i);
		game_grid.repaint();
	}
	public void start() {
		timer = new Timer(INITIAL_DELAY, new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				synchronized(timer) {
					if(cur_piece.canStepDown()) {
						cur_piece.cut();
						cur_piece.stepDown();
						cur_piece.paste();
						if(timer.isFast())
							score_label= score_label+1; // a small reward for using fast mode
					}
					else { // it hit something
						timer.setFast(false);
						if( ! cur_piece.isTotallyOnGrid())
							gameOver();
						else {
							removeFullRows();
							installNewPiece();
						}
					}
				}
				game_grid.repaint();
			}
		});
		timer.start(); // pauses immediately
	}
	private void startGame() {
		timer.setDelay(INITIAL_DELAY);
		timer.setPaused(false);
		start_newgame_butt.setLabel("START NEW GAME");
		start_newgame_butt.setBackground(BACKGROUND_COLORS);
		
	}
	private void newGame() {
		game_grid.clear();
		installNewPiece();
		num_rows_deleted = 0;
		startGame();
	}
	public void init() {
		installNewPiece();
		start_newgame_butt.setBackground(BACKGROUND_COLORS);
		
		start_newgame_butt.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent ae) {
				if(start_newgame_butt.getLabel().equals("START"))
					startGame();
				else
					newGame();
			}
		});		
		//create key listener for rotating, moving left, moving right
		KeyListener key_listener = new KeyAdapter() {
			public void keyPressed(KeyEvent e) {
				if(timer.isPaused()) //don't do anything if game is paused
					return;
				if (e.getKeyCode() == 37 || e.getKeyCode() == 39) { //left or right arrow pressed
					int dir = e.getKeyCode() == 37 ? -1 : 1;
					synchronized(timer) {
						cur_piece.cut();
						cur_piece.setX(cur_piece.getX() + dir); // try to move
						if( ! cur_piece.canPaste())
							cur_piece.setX(cur_piece.getX() - dir); // undo move
						cur_piece.paste();
					}
					game_grid.repaint();
				}
				else if (e.getKeyCode() == 38) { //rotate
					synchronized(timer) {
						cur_piece.cut();
						cur_piece.rotate();
						if( ! cur_piece.canPaste())
							cur_piece.rotateBack();
						cur_piece.paste();
					}
					game_grid.repaint();
				}
				if (e.getKeyCode() == 40) { //down arrow pressed; drop piece
					timer.setFast(true);
				}
			}
		};
		start_newgame_butt.addKeyListener(key_listener);
		
		Panel right_panel = new Panel();	
		right_panel.setBackground(BACKGROUND_COLOR);
		
		Panel control_panel = new Panel();
		control_panel.add(start_newgame_butt);
		control_panel.setBackground(BACKGROUND_COLOR);
		right_panel.add(control_panel);
		
		// finaly, add all the main panels to the applet panel
		this.setLayout(new BorderLayout());
		this.add(game_grid, BorderLayout.CENTER);
		this.add(right_panel, BorderLayout.NORTH);
		this.setBackground(BACKGROUND_COLOR);
		this.validate();
	}
	public static void main(String[] args) {
		Frame frame = new Frame("Tetris");
		Tetris tetris = new Tetris();
		frame.add(tetris);
		tetris.init();
		tetris.start();

		frame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});

		frame.setSize(286, 455);
		frame.setResizable(false);
		frame.setVisible(true);
		frame.setLocationRelativeTo(null);
	}
} // end class Tetris
class DoubleBufferedCanvas extends Canvas {
	private Image mActiveOffscreenImage = null;
	private Dimension mOffscreenSize = new Dimension(-1,-1);
	private Graphics mActiveOffscreenGraphics = null;
	private Graphics mSystemGraphics = null;
	DoubleBufferedCanvas() {
	}
	public void update(Graphics g) {
		paint(g);
	}
	public Graphics startPaint (Graphics sysgraph) {
		mSystemGraphics = sysgraph;
		Dimension d = getSize();
		if ((mActiveOffscreenImage == null) ||
			(d.width != mOffscreenSize.width) ||
			(d.height != mOffscreenSize.height)) 
		{
			mActiveOffscreenImage = createImage(d.width, d.height);
			mActiveOffscreenGraphics = mActiveOffscreenImage.getGraphics();
			mOffscreenSize = d;
			mActiveOffscreenGraphics.setFont(getFont());
		}
		return mActiveOffscreenGraphics;
	}
	public void endPaint () {
		mSystemGraphics.drawImage(mActiveOffscreenImage, 0, 0, null);
	}
}