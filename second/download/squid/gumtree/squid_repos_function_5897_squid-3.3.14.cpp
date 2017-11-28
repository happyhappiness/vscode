void
Snmp::Inquirer::cleanup()
{
    if (Comm::IsConnOpen(conn)) {
        if (closer != NULL) {
            comm_remove_close_handler(conn->fd, closer);
            closer = NULL;
        }
        conn->close();
    }
    conn = NULL;
}