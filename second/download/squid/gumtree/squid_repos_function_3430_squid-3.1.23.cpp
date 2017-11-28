int
connIsUsable(ConnStateData * conn)
{
    if (conn == NULL || !cbdataReferenceValid(conn) || conn->fd == -1)
        return 0;

    return 1;
}