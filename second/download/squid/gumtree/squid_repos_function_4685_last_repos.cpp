void
Server::swanSong()
{
    if (Comm::IsConnOpen(clientConnection))
        clientConnection->close();

    BodyProducer::swanSong();
}