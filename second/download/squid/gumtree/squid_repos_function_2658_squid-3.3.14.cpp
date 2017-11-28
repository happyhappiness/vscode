static void
htcpFreeSpecifier(htcpSpecifier * s)
{
    HTTPMSGUNLOCK(s->request);

    delete s;
}