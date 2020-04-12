package smartradar.view;

import java.util.Date;

import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;

public class LoggerView extends JPanel {
	
	private static final long serialVersionUID = -7136604582644322216L;
	private JTextArea log;
	private JPanel mainPanel;
	
	public LoggerView() {
		setSize(1000, 800);
		
		this.mainPanel = new JPanel();
		log = new JTextArea(30, 40);
		log.setEditable(false);
		JScrollPane scroll = new JScrollPane(log);
		mainPanel.add(scroll);
		
	}
	
	public void log(String msg) {
		SwingUtilities.invokeLater(() -> {
			String date = new Date().toString().substring(4, 19);
			log.append("[" + date + "] " + msg + "\n");
		});
	}
	
	public JPanel getPanel() {
		return this.mainPanel;
	}
	
	
}
