import java.awt.Dimension;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JPanel;

public class PaintPanel extends JPanel {

	private Color currentColor; //Color being used
	public int currentSize; //Size of brush
	private ArrayList<PaintPoint> _points; //Array that carries instances of color, size, point

	public PaintPanel() {
		
		_points = new ArrayList<PaintPoint>();

		//Every mousedrag registers as an event where the point, current color,
		//and current size are saved as a PaintPoint in _points
		addMouseMotionListener(new MouseAdapter() {
			@Override
			public void mouseDragged(MouseEvent ev) {
				_points.add(new PaintPoint(currentColor, ev.getPoint(), currentSize));
				
				repaint();
			}
		});

		setPreferredSize(new Dimension(400, 400));
	}

	public void clearArray(){ //clear the array _points
		_points.clear();
		repaint();
	}
	public Color getcurrentColor() { //get the current color of point
		return currentColor;
	}

	public void setcurrentColor(Color c) { //set the current color to c
		this.currentColor = c;
	}

	public int getcurrentSize() { //get the current size of a point
		return currentSize;
	}

	public void setcurrentSize(int s) { //set the current size to s
		this.currentSize = s;
	}
	
	@Override
	public void paintComponent(Graphics g) { //create graphics 
		super.paintComponent(g);
		//Iterate through _points and draw every PaintPoint 
		for (PaintPoint p : _points) { 
			g.setColor(p._color);
			g.fillOval(p._point.x, p._point.y, p._size, p._size);
			
			
		}
	}

}


