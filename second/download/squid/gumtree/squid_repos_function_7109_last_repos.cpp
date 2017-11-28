void Ipc::UdsSender::startSleep()
{
    Must(!sleeping);
    sleeping = true;
    eventAdd("Ipc::UdsSender::DelayedRetry",
             Ipc::UdsSender::DelayedRetry,
             new Pointer(this), 1, 0, false); // TODO: Use Fibonacci increments
}