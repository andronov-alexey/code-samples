public class GaugesViewManager {

	private final Map<STATE, StateBase> m_states = new HashMap<>();

	private StateBase m_currentState;

	public enum STATE {
		UNINITIALIZED,
		NO_APP,
		APP_ACTIVE,
		APP_INACTIVE,
	}

	public GaugesViewManager(Context _context) {
		m_states.put(STATE.UNINITIALIZED, new EmptyState(this, _context));
		m_states.put(STATE.NO_APP, new NoAppState(this, _context));
		m_states.put(STATE.APP_ACTIVE, new AppActiveState(this, _context));
		m_states.put(STATE.APP_INACTIVE, new AppInactiveState(this, _context));

		m_currentState = m_states.get(STATE.UNINITIALIZED);
	}

	public void setState(STATE _state) {
		m_currentState.onLeave();

		m_currentState = m_states.get(_state);

		m_currentState.onEnter();
	}

	public void startListening() {
		if (App.instance().getModule(AppObserver.class).isAppActive()) {
			setState(STATE.APP_INACTIVE);
		} else {
			setState(STATE.NO_APP);
		}

		App.instance().getModule(AppObserver.class).registerListener(m_appListener);
	}

	public void stopListening() {
		App.instance().getModule(AppObserver.class).unregisterListener(m_appListener);

		setState(STATE.UNINITIALIZED);
	}

	private final AppObserver.IAppStateChangeListener m_appListener = new AppObserver.IAppStateChangeListener() {
		@Override
		public void onActivated() {
			m_currentState.onActivated();
		}

		@Override
		public void onDeactivated() {
			m_currentState.onDeactivated();
		}
	};
}
