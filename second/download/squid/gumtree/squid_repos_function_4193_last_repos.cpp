void
ACLAtStepData::parse()
{
    while (const char *t = ConfigParser::strtokFile()) {
        if (strcasecmp(t, "SslBump1") == 0) {
            values.push_back(Ssl::bumpStep1);
        } else if (strcasecmp(t, "SslBump2") == 0) {
            values.push_back(Ssl::bumpStep2);
        } else if (strcasecmp(t, "SslBump3") == 0) {
            values.push_back(Ssl::bumpStep3);
        } else {
            debugs(28, DBG_CRITICAL, "FATAL: invalid AtStep step: " << t);
            self_destruct();
        }
    }
}