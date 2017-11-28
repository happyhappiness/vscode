void
FwdState::startComplete(FwdServer * theServers)
{
    debugs(17, 3, "fwdStartComplete: " << entry->url()  );

    if (theServers != NULL) {
        servers = theServers;
        connectStart();
    } else {
        startFail();
    }
}