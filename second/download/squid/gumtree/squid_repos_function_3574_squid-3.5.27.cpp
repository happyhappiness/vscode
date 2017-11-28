bool
ConnStateData::isOpen() const
{
    return cbdataReferenceValid(this) && // XXX: checking "this" in a method
           Comm::IsConnOpen(clientConnection) &&
           !fd_table[clientConnection->fd].closing();
}