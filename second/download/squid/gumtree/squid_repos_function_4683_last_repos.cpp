bool
Server::doneAll() const
{
    // servers are not done while the connection is open
    return !Comm::IsConnOpen(clientConnection) &&
           BodyProducer::doneAll();
}