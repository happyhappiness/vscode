static void
ftpReadQuit(FtpStateData * ftpState)
{
    /** \todo XXX should this just be a case of abortTransaction? */
    ftpState->serverComplete();
}