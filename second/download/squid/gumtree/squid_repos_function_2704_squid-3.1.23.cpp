void
TunnelStateData::copy (size_t len, comm_err_t errcode, int xerrno, Connection &from, Connection &to, IOCB *completion)
{
    /* I think this is to prevent free-while-in-a-callback behaviour
     * - RBC 20030229
     */
    cbdataInternalLock(this);	/* ??? should be locked by the caller... */

    /* Bump the source connection timeout on any activity */
    if (!fd_closed(from.fd()))
        commSetTimeout(from.fd(), Config.Timeout.read, tunnelTimeout, this);

    /* Bump the dest connection read timeout on any activity */
    /* see Bug 3659: tunnels can be weird, with very long one-way transfers */
    if (!fd_closed(to.fd()))
        commSetTimeout(to.fd(), Config.Timeout.read, tunnelTimeout, this);

    if (errcode)
        from.error (xerrno);
    else if (len == 0 || fd_closed(to.fd())) {
        comm_close(from.fd());
        /* Only close the remote end if we've finished queueing data to it */

        if (from.len == 0 && !fd_closed(to.fd()) ) {
            comm_close(to.fd());
        }
    } else if (cbdataReferenceValid(this))
        comm_write(to.fd(), from.buf, len, completion, this, NULL);

    cbdataInternalUnlock(this);	/* ??? */
}