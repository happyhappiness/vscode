static void
ftpReadQuit(Ftp::Gateway * ftpState)
{
    ftpState->serverComplete();
}