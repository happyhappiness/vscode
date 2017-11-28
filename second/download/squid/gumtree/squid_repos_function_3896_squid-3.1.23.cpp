void Adaptation::Icap::ModXact::stopWriting(bool nicely)
{
    if (state.writing == State::writingReallyDone)
        return;

    if (writer != NULL) {
        if (nicely) {
            debugs(93, 7, HERE << "will wait for the last write" << status());
            state.writing = State::writingAlmostDone; // may already be set
            checkConsuming();
            return;
        }
        debugs(93, 3, HERE << "will NOT wait for the last write" << status());

        // Comm does not have an interface to clear the writer callback nicely,
        // but without clearing the writer we cannot recycle the connection.
        // We prevent connection reuse and hope that we can handle a callback
        // call at any time, usually in the middle of the destruction sequence!
        // Somebody should add comm_remove_write_handler() to comm API.
        reuseConnection = false;
        ignoreLastWrite = true;
    }

    debugs(93, 7, HERE << "will no longer write" << status());
    if (virginBodyWriting.active()) {
        virginBodyWriting.disable();
        virginConsume();
    }
    state.writing = State::writingReallyDone;
    checkConsuming();
}