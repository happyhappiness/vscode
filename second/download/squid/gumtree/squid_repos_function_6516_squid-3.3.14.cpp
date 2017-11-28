void
Mgr::Inquirer::cleanup()
{
    if (Comm::IsConnOpen(conn)) {
        removeCloseHandler();
        conn->close();
    }
}