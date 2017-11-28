void
Ftp::Server::clientPinnedConnectionClosed(const CommCloseCbParams &io)
{
    ConnStateData::clientPinnedConnectionClosed(io);

    // TODO: Keep the control connection open after fixing the reset
    // problem below
    if (Comm::IsConnOpen(clientConnection))
        clientConnection->close();

    // TODO: If the server control connection is gone, reset state to login
    // again. Reseting login alone is not enough: FtpRelay::sendCommand() will
    // not re-login because FtpRelay::serverState() is not going to be
    // fssConnected. Calling resetLogin() alone is also harmful because
    // it does not reset correctly the client-to-squid control connection (eg
    // respond if required with an error code, in all cases)
    // resetLogin("control connection closure");
}