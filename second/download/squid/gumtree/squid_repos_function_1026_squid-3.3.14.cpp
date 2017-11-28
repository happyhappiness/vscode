static void
parseBytesLine(size_t * bptr, const char *units)
{
    char *token;
    double d;
    int m;
    int u;

    if ((u = parseBytesUnits(units)) == 0) {
        self_destruct();
        return;
    }

    if ((token = strtok(NULL, w_space)) == NULL) {
        self_destruct();
        return;
    }

    if (strcmp(token, "none") == 0 || strcmp(token, "-1") == 0) {
        *bptr = static_cast<size_t>(-1);
        return;
    }

    d = xatof(token);

    m = u;			/* default to 'units' if none specified */

    if (0.0 == d)
        (void) 0;
    else if ((token = strtok(NULL, w_space)) == NULL)
        debugs(3, DBG_CRITICAL, "WARNING: No units on '" <<
               config_input_line << "', assuming " <<
               d << " " <<  units  );
    else if ((m = parseBytesUnits(token)) == 0) {
        self_destruct();
        return;
    }

    *bptr = static_cast<size_t>(m * d / u);

    if (static_cast<double>(*bptr) * 2 != (m * d / u) * 2) {
        debugs(3, DBG_CRITICAL, "ERROR: Invalid value '" <<
               d << " " << token << ": integer overflow (size_t).");
        self_destruct();
    }
}