void
ConnStateData::clientAfterReadingRequests(int do_next_read)
{
    /*
     * If (1) we are reading a message body, (2) and the connection
     * is half-closed, and (3) we didn't get the entire HTTP request
     * yet, then close this connection.
     */

    if (fd_table[fd].flags.socket_eof) {
        if ((int64_t)in.notYetUsed < bodySizeLeft()) {
            /* Partial request received. Abort client connection! */
            debugs(33, 3, "clientAfterReadingRequests: FD " << fd << " aborted, partial request");
            comm_close(fd);
            return;
        }
    }

    clientMaybeReadData (do_next_read);
}