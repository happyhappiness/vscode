    HTTPMSGUNLOCK(request);

    delete err;

    entry->unregisterAbort();

    entry->unlock("FwdState");

    entry = NULL;

    if (calls.connector != NULL) {
        calls.connector->cancel("FwdState destructed");
        calls.connector = NULL;
    }

    if (Comm::IsConnOpen(serverConn))
        closeServerConnection("~FwdState");

    serverDestinations.clear();

    debugs(17, 3, HERE << "FwdState destructor done");
}

/**
 * This is the entry point for client-side to start forwarding
