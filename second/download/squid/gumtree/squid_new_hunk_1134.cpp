
void
Log::Format::SquidReferer(const AccessLogEntry::Pointer &al, Logfile *logfile)
{
    const char *referer = NULL;
    if (al->request)
        referer = al->request->header.getStr(Http::HdrType::REFERER);

    if (!referer || *referer == '\0')
        referer = "-";

    char clientip[MAX_IPSTRLEN];
    al->getLogClientIp(clientip, MAX_IPSTRLEN);

    const SBuf url = !al->url.isEmpty() ? al->url : ::Format::Dash;

    logfilePrintf(logfile, "%9ld.%03d %s %s " SQUIDSBUFPH "\n",
                  (long int) current_time.tv_sec,
                  (int) current_time.tv_usec / 1000,
                  clientip,
                  referer,
                  SQUIDSBUFPRINT(url));
}

