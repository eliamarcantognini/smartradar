package smartradar;

import javax.swing.SwingUtilities;

import smartradar.view.Controller;
import smartradar.view.LoggerView;
import smartradar.view.SmartRadarView;

public class SmartRadar {
	static SmartRadarView view = null;
	static LoggerView logger = null;
	
	public static void main(String[] args) throws Exception {
		SwingUtilities.invokeAndWait(() -> {
			logger = new LoggerView();
			view = new SmartRadarView(logger.getPanel());
		});
		
		String portName = "COM4";
		Controller controller = new Controller(portName, view, logger);
		view.registerController(controller);
		logger.log("Booting and calibrating. Please wait.");
		SwingUtilities.invokeLater(() -> {
			view.setVisible(true);
			logger.setVisible(true);
		});
	}
}
