void sslBumpCfgRr::run(const RunnerRegistry &r)
{
    if (lastDeprecatedRule != Ssl::bumpEnd) {
        assert( lastDeprecatedRule == Ssl::bumpClientFirst || lastDeprecatedRule == Ssl::bumpNone);
        static char buf[1024];
        if (lastDeprecatedRule == Ssl::bumpClientFirst) {
            strcpy(buf, "ssl_bump deny all");
            debugs(3, DBG_CRITICAL, "WARNING: auto-converting deprecated implicit "
                   "\"ssl_bump deny all\" to \"ssl_bump none all\". New ssl_bump configurations "
                   "must not use implicit rules. Update your ssl_bump rules.");
        } else {
            strcpy(buf, "ssl_bump allow all");
            debugs(3, DBG_CRITICAL, "SECURITY NOTICE: auto-converting deprecated implicit "
                   "\"ssl_bump allow all\" to \"ssl_bump client-first all\" which is usually "
                   "inferior to the newer server-first bumping mode. New ssl_bump"
                   " configurations must not use implicit rules. Update your ssl_bump rules.");
        }
        parse_line(buf);
    }
}