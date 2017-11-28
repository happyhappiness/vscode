void
Comm::ConnOpener::retrySleep()
{
    Must(!calls_.sleep_);
    closeFd();
    calls_.sleep_ = true;
    eventAdd("Comm::ConnOpener::DelayedConnectRetry",
             Comm::ConnOpener::DelayedConnectRetry,
             new Pointer(this), 0.05, 0, false);
}