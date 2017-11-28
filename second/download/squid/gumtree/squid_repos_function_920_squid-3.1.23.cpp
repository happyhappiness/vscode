void
AcceptFD::notify(int newfd, comm_err_t errcode, int xerrno, const ConnectionDetail &connDetails)
{
    if (theCallback != NULL) {
        typedef CommAcceptCbParams Params;
        Params &params = GetCommParams<Params>(theCallback);
        params.fd = fd;
        params.nfd = newfd;
        params.details = connDetails;
        params.flag = errcode;
        params.xerrno = xerrno;
        ScheduleCallHere(theCallback);
        theCallback = NULL;
    }
}