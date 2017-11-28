bool
fde::readPending(int fdNumber)
{
    if (type == FD_SOCKET)
        return Comm::MonitorsRead(fdNumber);

    return read_handler ? true : false ;
}