void
dnsShutdown(void)
{
    if (!dnsservers)
        return;

    helperShutdown(dnsservers);

    wordlistDestroy(&dnsservers->cmdline);

    if (!shutting_down)
        return;

    helperFree(dnsservers);

    dnsservers = NULL;
}