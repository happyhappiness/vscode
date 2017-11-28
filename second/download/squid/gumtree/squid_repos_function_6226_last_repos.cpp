void
Log::TcpLogger::disconnect()
{
    if (conn != NULL) {
        if (closer != NULL) {
            comm_remove_close_handler(conn->fd, closer);
            closer = NULL;
        }
        conn->close();
        conn = NULL;
    }
}