static void
tunnelConnectedWriteDone(int fd, char *buf, size_t size, comm_err_t flag, int xerrno, void *data)
{
    TunnelStateData *tunnelState = (TunnelStateData *)data;

    if (flag != COMM_OK) {
        tunnelErrorComplete(fd, data, 0);
        return;
    }

    if (cbdataReferenceValid(tunnelState)) {
        tunnelState->copyRead(tunnelState->server, TunnelStateData::ReadServer);
        tunnelState->copyRead(tunnelState->client, TunnelStateData::ReadClient);
    }
}