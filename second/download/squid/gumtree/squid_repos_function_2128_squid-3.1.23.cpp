bool
ServerStateData::canSend(int fd) const
{
    return fd >= 0 && !fd_table[fd].closing();
}