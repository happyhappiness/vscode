void
Log::TcpLogger::DelayedReconnect(void *data)
{
    Pointer *ptr = static_cast<Pointer*>(data);
    assert(ptr);
    if (TcpLogger *logger = ptr->valid()) {
        // Get back inside AsyncJob protections by scheduling another call.
        typedef NullaryMemFunT<TcpLogger> Dialer;
        AsyncCall::Pointer call = JobCallback(MY_DEBUG_SECTION, 5, Dialer,
                                              logger,
                                              Log::TcpLogger::delayedReconnect);
        ScheduleCallHere(call);
    }
    delete ptr;
}