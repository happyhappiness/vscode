bool
Ftp::Relay::mayReadVirginReplyBody() const
{
    // TODO: move this method to the regular FTP server?
    return Comm::IsConnOpen(data.conn);
}