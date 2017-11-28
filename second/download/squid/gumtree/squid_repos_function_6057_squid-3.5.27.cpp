void
Log::TcpLogger::Close(Logfile * lf)
{
    if (TcpLogger *logger = StillLogging(lf)) {
        debugs(50, 3, "Closing " << logger);
        typedef NullaryMemFunT<TcpLogger> Dialer;
        Dialer dialer(logger, &Log::TcpLogger::endGracefully);
        AsyncCall::Pointer call = asyncCall(50, 3, "Log::TcpLogger::endGracefully", dialer);
        ScheduleCallHere(call);
    }
    delete static_cast<Pointer*>(lf->data);
    lf->data = NULL;
}