void
TunnelStateData::Connection::error(int const xerrno)
{
    /* XXX fixme xstrerror and xerrno... */
    errno = xerrno;

    debugs(50, debugLevelForError(xerrno), HERE << conn << ": read/write failure: " << xstrerror());

    if (!ignoreErrno(xerrno))
        conn->close();
}