void
Server::clientWriteDone(const CommIoCbParams &io)
{
    debugs(33,5, io.conn);
    Must(writer != nullptr);
    writer = nullptr;

    /* Bail out quickly on Comm::ERR_CLOSING - close handlers will tidy up */
    if (io.flag == Comm::ERR_CLOSING || !Comm::IsConnOpen(clientConnection)) {
        debugs(33,5, io.conn << " closing Bailout.");
        return;
    }

    Must(io.conn->fd == clientConnection->fd);

    if (io.flag && pipeline.front())
        pipeline.front()->initiateClose("write failure");

    afterClientWrite(io.size); // update state
    writeSomeData(); // maybe schedules another write
}