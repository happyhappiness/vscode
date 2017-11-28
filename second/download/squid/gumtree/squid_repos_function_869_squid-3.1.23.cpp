void
ConnectStateData::callCallback(comm_err_t status, int xerrno)
{
    debugs(5, 3, "commConnectCallback: FD " << fd);

    comm_remove_close_handler(fd, commConnectFree, this);
    commSetTimeout(fd, -1, NULL, NULL);

    typedef CommConnectCbParams Params;
    Params &params = GetCommParams<Params>(callback);
    params.fd = fd;
    params.dns = dns;
    params.flag = status;
    params.xerrno = xerrno;
    ScheduleCallHere(callback);
    callback = NULL;

    commConnectFree(fd, this);
}