void
ftpStart(FwdState * fwd)
{
    AsyncJob::Start(new FtpStateData(fwd, fwd->serverConnection()));
}