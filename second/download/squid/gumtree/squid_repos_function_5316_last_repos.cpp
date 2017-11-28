const Comm::ConnectionPointer &
Ftp::Client::dataConnection() const
{
    return data.conn;
}