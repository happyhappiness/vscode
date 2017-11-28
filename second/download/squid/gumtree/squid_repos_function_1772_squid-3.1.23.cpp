static void
peerClearRRLoop(void *data)
{
    peerClearRR();
    eventAdd("peerClearRR", peerClearRRLoop, data, 5 * 60.0, 0);
}