AsyncJob::Pointer
Ftp::StartGateway(FwdState *const fwdState)
{
    return AsyncJob::Start(new Ftp::Gateway(fwdState));
}