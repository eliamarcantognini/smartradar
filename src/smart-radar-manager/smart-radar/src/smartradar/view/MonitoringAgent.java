package smartradar.view;

import smartradar.msg.SerialCommChannel;
import smartradar.msg.MsgProtocol;

public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	SmartRadarView view;
	LoggerView logger;

	public MonitoringAgent(SerialCommChannel channel, SmartRadarView view, LoggerView logger) {
		this.view = view;
		this.logger = logger;
		this.channel = channel;
		this.view.enableCommands(false);
	}

	public void run() {
		while (true){
			try {
				String msg = channel.receiveMsg();
				if (msg.startsWith(MsgProtocol.SR_PREFIX.toString())) {
					String cmd = msg.substring(MsgProtocol.SR_PREFIX.toString().length());				
					if (cmd.startsWith(MsgProtocol.READY.toString())) {
						this.logger.log("Welcome! Smart radar is ready.");
						this.view.setInfo("MANUAL MODE");
						this.view.setManualMode(true);
					} else if (cmd.startsWith(MsgProtocol.AUTO_MODE.toString())) {
						view.setInfo("AUTOMATIC MODE");
						view.setAutoMode(true);
					} else if (cmd.startsWith(MsgProtocol.MANUAL_MODE.toString())) {
						view.setInfo("MANUAL MODE");
						view.setManualMode(true);
					} else if (cmd.startsWith(MsgProtocol.SINGLE_MODE.toString())) {
						view.setInfo("SINGLE MODE");
						view.setSingleMode(true);
					} else if (cmd.startsWith(MsgProtocol.ALARM_OFF.toString())) {
						view.setAlarm("");
					} else if (cmd.startsWith(MsgProtocol.ALARM_ON.toString())) {
						view.setAlarm("!!ALARM!!");
					} else if (cmd.startsWith(MsgProtocol.SLEEP_MODE_ON.toString())) {
						this.logger.log("Go sleeping...");
						view.setInfo("SLEEP MODE");
						view.enableCommands(false);
					} else if (cmd.startsWith(MsgProtocol.SLEEP_MODE_OFF.toString())) {
						this.logger.log("Wake up!");
						view.setSingleMode(true);
						view.setInfo("SINGLE MODE");
					}
				} else if (msg.startsWith(MsgProtocol.LOG_PREFIX.toString())) {	
					String cmd = msg.substring(MsgProtocol.LOG_PREFIX.toString().length());
					if (cmd.startsWith(MsgProtocol.DISTANCE.toString())) {
						cmd = cmd.substring(MsgProtocol.DISTANCE.toString().length());
						this.logger.log("Object distance: " + cmd);
					} else if (cmd.startsWith(MsgProtocol.RADIUS.toString())) {
						cmd = cmd.substring(MsgProtocol.RADIUS.toString().length());
						this.logger.log("Radar radius: " + cmd + "°");
					} 
				} else {
					this.logger.log("Log from Arduino: " + msg);
				}
			} catch (Exception ex){
				ex.printStackTrace();
			}
		}
	}
}
