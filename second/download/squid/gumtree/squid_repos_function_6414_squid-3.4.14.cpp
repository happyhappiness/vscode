void Ipc::UdsSender::DelayedRetry(void *data)
{
    Pointer *ptr = static_cast<Pointer*>(data);
    assert(ptr);
    if (UdsSender *us = dynamic_cast<UdsSender*>(ptr->valid())) {
        // get back inside AsyncJob protection by scheduling an async job call
        typedef NullaryMemFunT<Ipc::UdsSender> Dialer;
        AsyncCall::Pointer call = JobCallback(54, 4, Dialer, us, Ipc::UdsSender::delayedRetry);
        ScheduleCallHere(call);
    }
    delete ptr;
}