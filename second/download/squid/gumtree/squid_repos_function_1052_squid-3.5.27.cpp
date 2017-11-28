static void
parseTimeLine(time_msec_t * tptr, const char *units,  bool allowMsec)
{
    char *token;
    double d;
    time_msec_t m;
    time_msec_t u;

    if ((u = parseTimeUnits(units, allowMsec)) == 0)
        self_destruct();

    if ((token = ConfigParser::NextToken()) == NULL)
        self_destruct();

    d = xatof(token);

    m = u;          /* default to 'units' if none specified */

    if (0 == d)
        (void) 0;
    else if ((token = ConfigParser::NextToken()) == NULL)
        debugs(3, DBG_CRITICAL, "WARNING: No units on '" <<
               config_input_line << "', assuming " <<
               d << " " << units  );
    else if ((m = parseTimeUnits(token, allowMsec)) == 0)
        self_destruct();

    *tptr = static_cast<time_msec_t>(m * d);

    if (static_cast<double>(*tptr) * 2 != m * d * 2) {
        debugs(3, DBG_CRITICAL, "ERROR: Invalid value '" <<
               d << " " << token << ": integer overflow (time_msec_t).");
        self_destruct();
    }
}