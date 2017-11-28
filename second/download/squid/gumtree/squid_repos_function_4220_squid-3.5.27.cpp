void Adaptation::Icap::Xaction::closeConnection()
{
    if (haveConnection()) {

        if (closer != NULL) {
            comm_remove_close_handler(connection->fd, closer);
            closer = NULL;
        }

        cancelRead(); // may not work

        if (reuseConnection && !doneWithIo()) {
            //status() adds leading spaces.
            debugs(93,5, HERE << "not reusing pconn due to pending I/O" << status());
            reuseConnection = false;
        }

        if (reuseConnection)
            disableRetries();

        const bool reset = !reuseConnection &&
                           (al.icap.outcome == xoGone || al.icap.outcome == xoError);

        Adaptation::Icap::ServiceRep &s = service();
        s.putConnection(connection, reuseConnection, reset, status());

        writer = NULL;
        reader = NULL;
        connector = NULL;
        connection = NULL;
    }
}