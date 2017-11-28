bool Adaptation::Icap::Xaction::haveConnection() const
{
    return connection != NULL && connection->isOpen();
}