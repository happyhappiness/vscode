void
Comm::ConnOpener::cleanFd()
{
    debugs(5, 4, HERE << conn_ << " closing temp FD " << temporaryFd_);

    Must(temporaryFd_ >= 0);
    fde &f = fd_table[temporaryFd_];

    // Our write_handler was set without using Comm::Write API, so we cannot
    // use a cancellable Pointer-free job callback and simply cancel it here.
    if (f.write_handler) {

        /* XXX: We are about to remove write_handler, which was responsible
         * for deleting write_data, so we have to delete write_data
         * ourselves. Comm currently calls SetSelect handlers synchronously
         * so if write_handler is set, we know it has not been called yet.
         * ConnOpener converts that sync call into an async one, but only
         * after deleting ptr, so that is not a problem.
         */

        delete static_cast<Pointer*>(f.write_data);
        f.write_data = NULL;
        f.write_handler = NULL;
    }
    // Comm::DoSelect does not do this when calling and resetting write_handler
    // (because it expects more writes to come?). We could mimic that
    // optimization by resetting Comm "Select" state only when the FD is
    // actually closed.
    Comm::SetSelect(temporaryFd_, COMM_SELECT_WRITE, NULL, NULL, 0);

    if (calls_.timeout_ != NULL) {
        calls_.timeout_->cancel("Comm::ConnOpener::cleanFd");
        calls_.timeout_ = NULL;
    }
    // Comm checkTimeouts() and commCloseAllSockets() do not clear .timeout
    // when calling timeoutHandler (XXX fix them), so we clear unconditionally.
    f.timeoutHandler = NULL;
    f.timeout = 0;

    if (calls_.earlyAbort_ != NULL) {
        comm_remove_close_handler(temporaryFd_, calls_.earlyAbort_);
        calls_.earlyAbort_ = NULL;
    }
}