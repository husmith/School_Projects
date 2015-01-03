import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.GridLayout;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.Border;
import javax.swing.border.LineBorder;


public class MainFrame extends JFrame implements ActionListener {
	
	PaintPanel panel= new PaintPanel();
	
	Color _yellow;
	Color _red;
	Color _green;
	Color _blue;
	
	public MainFrame() {
		super("Paint!");
		
		setLayout(new BorderLayout(5,5));
		
		_red = new Color(238, 75, 62);
		_yellow = new Color(255,212, 82);
		_green = new Color(160,251, 113 );
		_blue = new Color(146,220, 224 );
		
		//create borders for buttons
		Border yborder = new LineBorder(_yellow, 10);
		Border bborder = new LineBorder(_blue, 10);
		Border gborder = new LineBorder(_green, 10);
		Border rborder = new LineBorder(_red, 10);
		
		//initialize the current color and size of the brush
		panel.setcurrentColor(_red);
		panel.setcurrentSize(10);
		
		add(panel); //add the PaintPanel to the frame
		
		//create two panels of buttons
		JPanel colorButtons = new JPanel(new GridLayout(4,1)); 
		JPanel sizeButtons = new JPanel(new GridLayout(4,1));
		add(colorButtons, BorderLayout.WEST);
		add(sizeButtons, BorderLayout.EAST);
		
//Create Jbuttons and override their actionPerformed
		//Write "callback function" in actionPerformed
		
		JButton red = new JButton("RED"); //Red
		red.setBorder(rborder);
		red.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) {
			panel.setcurrentColor(_red);
			}
		});
		colorButtons.add(red);
		
		JButton yellow = new JButton("YELLOW"); //Yellow
		yellow.setBorder(yborder);
		yellow.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) {
				panel.setcurrentColor(_yellow);
			}
		});
		colorButtons.add(yellow);
		
		JButton blue = new JButton("BLUE"); //Blue
		blue.setBorder(bborder);
		blue.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) { 
				panel.setcurrentColor(_blue);
			}
		});
		colorButtons.add(blue);
		
		JButton green = new JButton("GREEN"); //Green
		green.setBorder(gborder);
		green.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) {
				panel.setcurrentColor(_green);
			}
		});
		colorButtons.add(green);
		
		JButton small = new JButton("Small"); //Small
		small.setFont(new Font("Arial", Font.PLAIN, 10));
		small.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) {
				panel.setcurrentSize(5);
			}
		});
		sizeButtons.add(small);
		
		JButton medium = new JButton("Medium"); //Medium
		medium.setFont(new Font("Arial", Font.PLAIN, 15));
		medium.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) {
				panel.setcurrentSize(10);
			}
		});
		sizeButtons.add(medium);
		
		JButton large = new JButton("Large"); //Large
		large.setFont(new Font("Arial", Font.PLAIN, 20));
		large.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) {
				panel.setcurrentSize(20);
			}
		});
		sizeButtons.add(large);
		
		JButton clear = new JButton("Clear"); //Clear PaintPanel
		clear.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent ev) {
				panel.clearArray();
			}
		});
		sizeButtons.add(clear);
		
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		pack();
	}
	

	public static void main(String[] args) {
		//create new MainFrame
		MainFrame frame = new MainFrame();
		frame.setVisible(true);
	}


	@Override
	public void actionPerformed(ActionEvent e) {
		panel.setcurrentColor(_green);
		
	}
}
