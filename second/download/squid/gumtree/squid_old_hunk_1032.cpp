    static char ipbuf[MAX_IPSTRLEN] = {'\0'};
    if (ipbuf[0] == '\0')
        conn->local.toHostStr(ipbuf, MAX_IPSTRLEN);

    static MemBuf buf;
    buf.reset();
    buf.Printf(" FD %d, %s",conn->fd, ipbuf);

    const char *jobStatus = AsyncJob::status();
    buf.append(jobStatus, strlen(jobStatus));

    return buf.content();
}
