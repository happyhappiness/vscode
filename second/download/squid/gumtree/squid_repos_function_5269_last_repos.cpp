void
Ftp::Relay::startDataUpload()
{
    assert(Comm::IsConnOpen(data.conn));

    debugs(9, 3, "begin data transfer to " << data.conn->remote <<
           " (" << data.conn->local << ")");

    if (!startRequestBodyFlow()) { // register to receive body data
        failed();
        return;
    }

    state = WRITING_DATA;
}