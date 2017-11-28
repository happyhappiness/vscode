static void
htcpLogHtcp(IpAddress &caddr, int opcode, log_type logcode, const char *url)
{
    AccessLogEntry al;
    if (LOG_TAG_NONE == logcode)
        return;
    if (!Config.onoff.log_udp)
        return;
    al.htcp.opcode = htcpOpcodeStr[opcode];
    al.url = url;
    al.cache.caddr = caddr;
    al.cache.code = logcode;
    al.cache.msec = 0;
    accessLogLog(&al, NULL);
}