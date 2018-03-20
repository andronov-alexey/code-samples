public class MessageParser {
	private final String DETAILS_KEY = "details";
	private final String MANEUVERS_KEY = "maneuvers";
	private final String GAUGES_KEY = "gauges";
	private final String STREETS_KEY = "streets";

	private final ManeuverParser m_maneuversParser = new ManeuverParser();
	private final GaugesParser m_gaugesParser = new GaugesParser();
	private final StreetParser m_streetsParser = new StreetParser();
	private final PARSE_RESULT m_result = new PARSE_RESULT();

	public class PARSE_RESULT {
		void clear() {
			maneuvers.clear();
			gauges.clear();
			streets.clear();
		}

		public List<Maneuver> maneuvers = new ArrayList<>();
		public List<Gauge> gauges = new ArrayList<>();
		public List<Street> streets = new ArrayList<>();
	}

	public PARSE_RESULT parse(String _data) {
		m_result.clear();

		try {
			JSONObject message = new JSONObject(_data);
			JSONObject details = message.getJSONObject(DETAILS_KEY);

			if (details.has(MANEUVERS_KEY)) {
				JSONArray maneuversArray = details.getJSONArray(MANEUVERS_KEY);
				m_result.maneuvers = m_maneuversParser.parse(maneuversArray);
			}

			if (details.has(GAUGES_KEY)) {
				JSONArray gaugesArray = details.getJSONArray(GAUGES_KEY);
				m_result.gauges = m_gaugesParser.parse(gaugesArray);
			}

			if (details.has(STREETS_KEY)) {
				JSONArray streetsArray = details.getJSONArray(STREETS_KEY);
				m_result.streets = m_streetsParser.parse(streetsArray);
			}
		} catch (JSONException e) {
			e.printStackTrace();
		}

		return m_result;
	}
}
