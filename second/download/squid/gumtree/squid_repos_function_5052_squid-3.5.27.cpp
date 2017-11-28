void Ftp::Server::completeDataDownload()
{
    writeCustomReply(master->userDataDone, master->userDataDone == 226 ? "Transfer complete" : "Server error; transfer aborted");
    closeDataConnection();
}