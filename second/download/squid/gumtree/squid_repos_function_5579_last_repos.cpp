void
Comm::ConnOpener::swanSong()
{
    if (callback_ != NULL) {
        // inform the still-waiting caller we are dying
        sendAnswer(Comm::ERR_CONNECT, 0, "Comm::ConnOpener::swanSong");
    }

    // did we abort with a temporary FD assigned?
    if (temporaryFd_ >= 0)
        closeFd();

    // did we abort while waiting between retries?
    if (calls_.sleep_)
        cancelSleep();

    AsyncJob::swanSong();
}