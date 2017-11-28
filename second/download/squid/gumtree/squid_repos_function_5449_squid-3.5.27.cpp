AsyncCall::Pointer
Ftp::Client::dataCloser()
{
    typedef CommCbMemFunT<Client, CommCloseCbParams> Dialer;
    return JobCallback(9, 5, Dialer, this, Ftp::Client::dataClosed);
}