void
TunnelStateData::Connection::error(int const xerrno)
{
    debugs(50, debugLevelForError(xerrno), HERE << conn << ": read/write failure: " << xstrerr(xerrno));

    if (!ignoreErrno(xerrno))
        conn->close();
}