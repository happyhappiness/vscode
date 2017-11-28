static void
parseTimeLine(time_msec_t * tptr, const char *units,  bool allowMsec,  bool expectMoreArguments = false)
{
    time_msec_t u = parseTimeUnits(units, allowMsec);
    if (u == 0) {
        self_destruct();
        return;
    }

    char *token = ConfigParser::NextToken();;
    if (!token) {
        self_destruct();
        return;
    }

    double d = xatof(token);

    time_msec_t m = u; /* default to 'units' if none specified */

    if (d) {
        if ((token = ConfigParser::PeekAtToken()) && (m = parseTimeUnits(token, allowMsec))) {
            (void)ConfigParser::NextToken();

        } else if (!expectMoreArguments) {
            self_destruct();
            return;

        } else {
            token = NULL; // show default units if dying below
            debugs(3, DBG_CRITICAL, "WARNING: No units on '" << config_input_line << "', assuming " << d << " " << units);
        }
    } else
        token = NULL; // show default units if dying below.

    *tptr = static_cast<time_msec_t>(m * d);

    if (static_cast<double>(*tptr) * 2 != m * d * 2) {
        debugs(3, DBG_CRITICAL, "FATAL: Invalid value '" <<
               d << " " << (token ? token : units) << ": integer overflow (time_msec_t).");
        self_destruct();
    }
}