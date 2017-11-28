static ssize_t
htcpBuildTstOpData(char *buf, size_t buflen, htcpStuff * stuff)
{
    switch (stuff->rr) {

    case RR_REQUEST:
        debugs(31, 3, "htcpBuildTstOpData: RR_REQUEST");
        return htcpBuildSpecifier(buf, buflen, stuff);

    case RR_RESPONSE:
        debugs(31, 3, "htcpBuildTstOpData: RR_RESPONSE");
        debugs(31, 3, "htcpBuildTstOpData: F1 = " << stuff->f1);

        if (stuff->f1)      /* cache miss */
            return 0;
        else            /* cache hit */
            return htcpBuildDetail(buf, buflen, stuff);

    default:
        fatal_dump("htcpBuildTstOpData: bad RR value");
    }

    return 0;
}