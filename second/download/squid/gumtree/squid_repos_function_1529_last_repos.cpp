void
peerClearRRStart(void)
{
    static bool event_added = false;
    if (!event_added) {
        peerClearRRLoop(NULL);
        event_added=true;
    }
}