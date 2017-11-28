void
Comm::ConnOpener::restart()
{
    debugs(5, 5, conn_ << " restarting after sleep");
    calls_.sleep_ = false;

    if (createFd())
        connect();
}