AsyncCall::Pointer
FtpStateData::dataCloser()
{
    typedef CommCbMemFunT<FtpStateData, CommCloseCbParams> Dialer;
    return JobCallback(9, 5, Dialer, this, FtpStateData::dataClosed);
}