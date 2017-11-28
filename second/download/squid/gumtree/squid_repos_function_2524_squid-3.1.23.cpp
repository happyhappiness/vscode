void
ftpStart(FwdState * fwd)
{
    FtpStateData *ftpState = new FtpStateData(fwd);
    ftpState->start();
}