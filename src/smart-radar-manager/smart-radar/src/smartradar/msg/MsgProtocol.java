package smartradar.msg;

public enum MsgProtocol {
	SR_PREFIX("sr:"),
	LOG_PREFIX("lo:"),
	AUTO_MODE("m|0"),
	SINGLE_MODE("m|1"),
	MANUAL_MODE("m|2"),
	SLEEP_MODE_OFF("s|0"),
	SLEEP_MODE_ON("s|1"),
	ALARM_OFF("a|0"),
	ALARM_ON("a|1"),
	DISTANCE("d|"),
	RADIUS("r|"),
	READY("r"),
	MOVE_RIGHT("d|1"),
	MOVE_LEFT("d|-1"),
	POTENTIOMETER_UP("f|1"),
	POTENTIOMETER_DOWN("f|-1");
	
	private final String msg;
	
	private MsgProtocol(final String msg) {
		this.msg = msg;
	}
	
	public String toString() {
		return msg;
	}
}
