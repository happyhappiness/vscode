bool
FtpStateData::doneWithServer() const
{
    return !Comm::IsConnOpen(ctrl.conn) && !Comm::IsConnOpen(data.conn);
}