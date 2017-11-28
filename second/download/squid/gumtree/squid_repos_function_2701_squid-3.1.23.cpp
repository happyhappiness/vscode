void
TunnelStateData::Connection::error(int const xerrno)
{
    /* XXX fixme xstrerror and xerrno... */
    errno = xerrno;

    debugs(50, debugLevelForError(xerrno), "TunnelStateData::Connection::error: FD " << fd() <<
           ": read/write failure: " << xstrerror());

    if (!ignoreErrno(xerrno))
        comm_close(fd());
}