void
Mgr::Inquirer::removeCloseHandler()
{
    if (closer != NULL) {
        comm_remove_close_handler(conn->fd, closer);
        closer = NULL;
    }
}