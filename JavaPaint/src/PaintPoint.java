import java.awt.Color;
import java.awt.Point;

public class PaintPoint extends Point{
	Color _color;
	Point _point;
	int _size;
	public PaintPoint(Color c, Point p, int size){
		_color = c;
		_point = p;
		_size = size;	
	}
}
	