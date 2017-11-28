void
Auth::Basic::Config::parse(Auth::Config * scheme, int n_configured, char *param_str)
{
    if (strcmp(param_str, "credentialsttl") == 0) {
        parse_time_t(&credentialsTTL);
    } else if (strcmp(param_str, "casesensitive") == 0) {
        parse_onoff(&casesensitive);
    } else if (strcmp(param_str, "utf8") == 0) {
        parse_onoff(&utf8);
    } else
        Auth::Config::parse(scheme, n_configured, param_str);
}