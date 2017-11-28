AsyncJob::Pointer
Ftp::StartRelay(FwdState *const fwdState)
{
    return AsyncJob::Start(new Ftp::Relay(fwdState));
}