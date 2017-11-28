static void
parseTimeLine(time_t * tptr, const char *units)
{
    char *token;
    double d;
    time_t m;
    time_t u;

    if ((u = parseTimeUnits(units)) == 0)
        self_destruct();

    if ((token = strtok(NULL, w_space)) == NULL)
        self_destruct();

    d = xatof(token);

    m = u;			/* default to 'units' if none specified */

    if (0 == d)
        (void) 0;
    else if ((token = strtok(NULL, w_space)) == NULL)
        debugs(3, 0, "WARNING: No units on '" <<
               config_input_line << "', assuming " <<
               d << " " << units  );
    else if ((m = parseTimeUnits(token)) == 0)
        self_destruct();

    *tptr = static_cast<time_t> (m * d / u);
}