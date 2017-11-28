void
Log::Format::SquidUserAgent(const AccessLogEntry::Pointer &al, Logfile * logfile)
{
    const char *agent = NULL;

    if (al->request)
        agent = al->request->header.getStr(Http::HdrType::USER_AGENT);

    if (!agent || *agent == '\0')
        agent = "-";

    char clientip[MAX_IPSTRLEN];
    al->getLogClientIp(clientip, MAX_IPSTRLEN);

    logfilePrintf(logfile, "%s [%s] \"%s\"\n",
                  clientip,
                  Time::FormatHttpd(squid_curtime),
                  agent);
}