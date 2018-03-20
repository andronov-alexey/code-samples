public class GaugesChangeReceiver extends BroadcastReceiver {
	private final String MESSAGE_EXTRA_KEY = "data";

	private final static ArrayList<IGaugesListener> m_listeners = new ArrayList<>();
	private final static MessageParser m_parser = new MessageParser();

	public interface IGaugesListener {
		void onGaugesChanged(List<Gauge> _gauges);
		void onManeuversChanged(List<Maneuver> _maneuvers);
	}

	@Override
	public void onReceive(Context _context, Intent _intent) {
		String message = _intent.getStringExtra(MESSAGE_EXTRA_KEY);

		MessageParser.PARSE_RESULT result = m_parser.parse(message);

		if (!result.maneuvers.isEmpty()) {
			_notifyManeuversChangeListeners(result.maneuvers);
		}

		if (!result.gauges.isEmpty()) {
			_notifyGaugesChangeListeners(result.gauges);
		}
	}

	public static void registerListener(IGaugesListener _listener) {
		synchronized (m_listeners) {
			m_listeners.add(_listener);
		}
	}

	public static void unregisterListener(IGaugesListener _listener) {
		synchronized (m_listeners) {
			m_listeners.remove(_listener);
		}
	}

	private static void _notifyGaugesChangeListeners(List<Gauge> _gauges) {
		synchronized (m_listeners) {
			for (IGaugesListener listener : m_listeners) {
				listener.onGaugesChanged(_gauges);
			}
		}
	}

	private static void _notifyManeuversChangeListeners(List<Maneuver> _maneuvers) {
		synchronized (m_listeners) {
			for (IGaugesListener listener : m_listeners) {
				listener.onManeuversChanged(_maneuvers);
			}
		}
	}
}
