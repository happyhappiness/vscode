void
Comm::ConnOpener::DelayedConnectRetry(void *data)
{
    Pointer *ptr = static_cast<Pointer*>(data);
    assert(ptr);
    if (ConnOpener *cs = ptr->valid()) {
        // Ew. we are now outside the all AsyncJob protections.
        // get back inside by scheduling another call...
        typedef NullaryMemFunT<Comm::ConnOpener> Dialer;
        AsyncCall::Pointer call = JobCallback(5, 4, Dialer, cs, Comm::ConnOpener::restart);
        ScheduleCallHere(call);
    }
    delete ptr;
}