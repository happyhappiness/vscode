bool
FtpStateData::doneWithServer() const
{
    return ctrl.fd < 0 && data.fd < 0;
}