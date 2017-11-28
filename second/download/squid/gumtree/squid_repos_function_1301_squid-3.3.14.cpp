void
peerSelectInit(void)
{
    memset(&PeerStats, '\0', sizeof(PeerStats));
    memDataInit(MEM_FWD_SERVER, "FwdServer", sizeof(FwdServer), 0);
}