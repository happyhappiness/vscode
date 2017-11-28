void
Mgr::Inquirer::noteWroteHeader(const CommIoCbParams& params)
{
    debugs(16, 5, HERE);
    writer = NULL;
    Must(params.flag == Comm::OK);
    Must(params.conn.getRaw() == conn.getRaw());
    Must(params.size != 0);
    // start inquiries at the initial pos
    inquire();
}