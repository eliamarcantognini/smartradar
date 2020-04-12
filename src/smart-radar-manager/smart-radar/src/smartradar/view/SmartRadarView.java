package smartradar.view;

import java.awt.BorderLayout;
import java.awt.Dimension;

import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class SmartRadarView extends JFrame {
	
	private static final long serialVersionUID = 8141739789083726946L;
	static final String INIT_MODE = "Booting...";
	private JButton moveRight;
	private JButton moveLeft;
	private JButton modeAuto;
	private JButton modeSingle;
	private JButton modeManual;
	private JButton potentiometerUp;
	private JButton potentiometerDown;
	private JLabel info;
	private JLabel alarmLabel;
	
	public SmartRadarView(final JPanel logger) {
		super(".:: Smart Radar Manager ::.");
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		this.setLayout(new BorderLayout());
		JPanel panel = new JPanel();
		panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));
		panel.add(Box.createRigidArea(new Dimension(0, 20)));
		this.add(panel, BorderLayout.CENTER);
		
		/**
		 * Info about modality
		 */
		JPanel infoLine = new JPanel();
		infoLine.setLayout(new BoxLayout(infoLine, BoxLayout.LINE_AXIS));
		info = new JLabel(INIT_MODE);
		info.setPreferredSize(new Dimension(200,15));
		infoLine.add(info);
		panel.add(infoLine);
		/**
		 * Alarm mode
		 */
		JPanel alarmLine = new JPanel();
		alarmLine.setLayout(new BoxLayout(alarmLine, BoxLayout.LINE_AXIS));
		alarmLabel = new JLabel("");
		alarmLabel.setPreferredSize(new Dimension(200, 15));
		alarmLine.add(alarmLabel);
		panel.add(alarmLine);
		/**
		 * Buttons
		 */
		JPanel buttonPanel = new JPanel();
		buttonPanel.setLayout(new BorderLayout());	
		JPanel modPanel = new JPanel();
		JPanel movesPanel = new JPanel();
		JPanel potPanel = new JPanel();
		// Modalities
		JLabel mod = new JLabel("Change modality:");
		modeAuto = new JButton("Automatic");
		modeManual = new JButton("Manual");
		modeSingle = new JButton("Single");
		modPanel.add(mod);
		modPanel.add(modeAuto);
		modPanel.add(modeManual);
		modPanel.add(modeSingle);
		buttonPanel.add(modPanel, BorderLayout.NORTH);
		// Moves
		JLabel manMoves = new JLabel("Radar moves to the");
		moveRight = new JButton("Right");
		moveLeft = new JButton("Left");
		movesPanel.add(manMoves);
		movesPanel.add(moveRight);
		movesPanel.add(moveLeft);
		buttonPanel.add(movesPanel, BorderLayout.CENTER);
		// Potentiometer
		JLabel potFreq = new JLabel("Radar goes");
		potentiometerDown = new JButton("Faster");
		potentiometerUp = new JButton("Slower");
		potPanel.add(potFreq);
		potPanel.add(potentiometerDown);
		potPanel.add(potentiometerUp);	
		buttonPanel.add(potPanel, BorderLayout.SOUTH);
		this.add(buttonPanel, BorderLayout.SOUTH);
		/**
		 * 
		 */
		panel.add(logger, BorderLayout.CENTER);
		panel.add(Box.createRigidArea(new Dimension(20,20)));
		this.getContentPane().add(panel);
		this.pack();
		this.setVisible(true);
		this.enableCommands(true);
	}
	
	public void setInfo(String msg){
		SwingUtilities.invokeLater(() -> {
			info.setText(msg);
		});
	}
	
	public void setAlarm(final String alarm) {
		SwingUtilities.invokeLater(() -> {
			alarmLabel.setText(alarm);
		});
	}
	
	public void enableCommands(final boolean on) {
		this.moveRight.setEnabled(on);
		this.moveLeft.setEnabled(on);
		this.modeAuto.setEnabled(on);
		this.modeSingle.setEnabled(on);
		this.modeManual.setEnabled(on);
		this.potentiometerUp.setEnabled(on);
		this.potentiometerDown.setEnabled(on);
		
	}
	
	public void setManualMode(final boolean on) {
		this.modeAuto.setEnabled(on);
		this.modeSingle.setEnabled(on);
		this.modeManual.setEnabled(!on);
		this.moveRight.setEnabled(on);
		this.moveLeft.setEnabled(on);
		this.potentiometerDown.setEnabled(!on);
		this.potentiometerUp.setEnabled(!on);
	}
	
	public void setSingleMode(final boolean on) {
		this.modeSingle.setEnabled(!on);
		this.modeAuto.setEnabled(on);
		this.modeManual.setEnabled(on);
		this.moveRight.setEnabled(!on);
		this.moveLeft.setEnabled(!on);
		this.potentiometerDown.setEnabled(on);
		this.potentiometerUp.setEnabled(on);
	}
	
	public void setAutoMode(final boolean on) {
		this.modeAuto.setEnabled(!on);
		this.moveRight.setEnabled(!on);
		this.moveLeft.setEnabled(!on);
		this.modeManual.setEnabled(on);
		this.modeSingle.setEnabled(on);
		this.potentiometerDown.setEnabled(on);
		this.potentiometerUp.setEnabled(on);
	}
	
	

	public void registerController(Controller controller) {
		moveLeft.addActionListener(controller);
		moveRight.addActionListener(controller);
		modeAuto.addActionListener(controller);
		modeSingle.addActionListener(controller);
		modeManual.addActionListener(controller);
		potentiometerDown.addActionListener(controller);
		potentiometerUp.addActionListener(controller);	
	}


}
