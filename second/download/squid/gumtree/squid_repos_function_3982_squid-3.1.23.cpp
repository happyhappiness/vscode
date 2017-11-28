void Adaptation::Icap::Xaction::closeConnection()
{
    if (connection >= 0) {

        if (closer != NULL) {
            comm_remove_close_handler(connection, closer);
            closer = NULL;
        }

        cancelRead(); // may not work

        if (reuseConnection && !doneWithIo()) {
            //status() adds leading spaces.
            debugs(93,5, HERE << "not reusing pconn due to pending I/O" << status());
            reuseConnection = false;
        }

        if (reuseConnection) {
            IpAddress client_addr;
            //status() adds leading spaces.
            debugs(93,3, HERE << "pushing pconn" << status());
            AsyncCall::Pointer call = NULL;
            commSetTimeout(connection, -1, call);
            icapPconnPool->push(connection, theService->cfg().host.termedBuf(),
                                theService->cfg().port, NULL, client_addr);
            disableRetries();
        } else {
            //status() adds leading spaces.
            debugs(93,3, HERE << "closing pconn" << status());
            // comm_close will clear timeout
            comm_close(connection);
        }

        writer = NULL;
        reader = NULL;
        connector = NULL;
        connection = -1;
    }
}