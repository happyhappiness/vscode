void
Transport::CloseConnection()
{
    (void) close(conn);
    conn = -1;
}