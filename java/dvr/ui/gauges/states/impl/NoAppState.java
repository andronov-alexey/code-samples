public class NoAppState extends StateBase {
	private final NoAppState.LocationListener m_locationListener = new NoAppState.LocationListener();

	private TextView m_tvSpeed;
	private TextView m_tvSpeedUnits;

	@SuppressLint("InflateParams")
	public NoAppState(GaugesViewManager _gaugesViewManager, Context _context) {
		super(_gaugesViewManager, _context);

		m_gaugesView = m_inflater.inflate(R.layout.gauges_no_app, null);
	}

	@Override
	public void onEnter() {
		super.onEnter();

		m_placeholder.addView(m_gaugesView);

		m_tvSpeed = (TextView) m_rootView.findViewById(R.id.speed);
		m_tvSpeedUnits = (TextView) m_rootView.findViewById(R.id.speed_unit);

		App.instance().getModule(GPSDataProvider.class).registerCallBack(m_locationListener);
	}

	@Override
	public void onLeave() {
		App.instance().getModule(GPSDataProvider.class).unregisterCallBack(m_locationListener);

		m_tvSpeed = null;
		m_tvSpeedUnits = null;

		super.onLeave();
	}

	@Override
	public void onActivated() {
		m_gaugesViewManager.setState(GaugesViewManager.STATE.APP_INACTIVE);

		super.onActivated();
	}

	private class LocationListener implements GPSDataProvider.ILocationChangedListener {
		private final String m_units;

		LocationListener() {
			m_units = App.instance().getAppContext().getString(R.string.preview_speed_units);
		}

		@Override
		public void onLocationChanged(Location _location) {
			if (_location.hasSpeed()) {
				m_tvSpeed.setText(_location.getSpeed());
				m_tvSpeed.setText(m_units);
			}
		}
	}
}
