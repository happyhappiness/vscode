static void
htcpLogHtcp(Ip::Address &caddr, int opcode, LogTags logcode, const char *url)
{
    AccessLogEntry::Pointer al = new AccessLogEntry;
    if (LOG_TAG_NONE == logcode.oldType)
        return;
    if (!Config.onoff.log_udp)
        return;
    al->htcp.opcode = htcpOpcodeStr[opcode];
    al->url = url;
    al->cache.caddr = caddr;
    al->cache.code = logcode;
    al->cache.trTime.tv_sec = 0;
    al->cache.trTime.tv_usec = 0;
    accessLogLog(al, NULL);
}