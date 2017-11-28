bool
fde::readPending(int fdNumber)
{
    if (type == FD_SOCKET)
        return comm_monitors_read(fdNumber);

    return read_handler ? true : false ;
}