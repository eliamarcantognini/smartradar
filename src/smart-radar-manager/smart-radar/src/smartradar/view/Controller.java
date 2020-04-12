package smartradar.view;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import smartradar.msg.MsgProtocol;
import smartradar.msg.SerialCommChannel;

public class Controller implements ActionListener {
	
	LoggerView logger;
	SerialCommChannel channel;
	SmartRadarView view;
	
	public Controller(String port, SmartRadarView view, LoggerView logger) throws Exception {
		this.view = view;
		this.logger = logger;
		channel = new SerialCommChannel(port, 9600);
		
		System.out.println("Waiting Arduino for rebooting");
		Thread.sleep(4000);
		System.out.println("Ready.");
		
		new MonitoringAgent(channel, view, logger).start();
	}
	
	@Override
	public void actionPerformed(ActionEvent ev) {
		  try {
			  if (ev.getActionCommand().equals("Right")){
				  channel.sendMsg(MsgProtocol.SR_PREFIX.toString() + MsgProtocol.MOVE_RIGHT.toString());
				  logger.log("Radar moves to the right.");
			  }
			  if (ev.getActionCommand().equals("Left")) {
				  channel.sendMsg(MsgProtocol.SR_PREFIX.toString() + MsgProtocol.MOVE_LEFT.toString());
				  logger.log("Radar moves to the left.");
			  }
			  if (ev.getActionCommand().equals("Automatic")) {
				  channel.sendMsg(MsgProtocol.SR_PREFIX.toString() + MsgProtocol.AUTO_MODE.toString());
				  view.setInfo("AUTOMATIC MODE");
				  logger.log("Change to auto mode.");
			  }
			  if (ev.getActionCommand().equals("Single")) {
				  channel.sendMsg(MsgProtocol.SR_PREFIX.toString() + MsgProtocol.SINGLE_MODE.toString());
				  view.setInfo("SINGLE MODE");
				  logger.log("Change to single mode.");
			  }
			  if (ev.getActionCommand().equals("Manual")) {
				  channel.sendMsg(MsgProtocol.SR_PREFIX.toString() + MsgProtocol.MANUAL_MODE.toString());
				  view.setInfo("MANUAL MODE");
				  logger.log("Change to manual mode.");
			  }
			  if (ev.getActionCommand().equals("Slower")) {
				  channel.sendMsg(MsgProtocol.SR_PREFIX.toString() + MsgProtocol.POTENTIOMETER_UP.toString());
				  logger.log("Radar now moves slower!");
			  }
			  if (ev.getActionCommand().equals("Faster")) {
				channel.sendMsg(MsgProtocol.SR_PREFIX.toString() + MsgProtocol.POTENTIOMETER_DOWN.toString());
				  logger.log("Radar now moves faster!");  
			  }
		  } catch (Exception ex){
			  ex.printStackTrace();
		  }
	  }

	}
