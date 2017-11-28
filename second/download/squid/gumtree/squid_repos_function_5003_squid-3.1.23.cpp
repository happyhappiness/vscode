bool AsyncJob::canBeCalled(AsyncCall &call) const
{
    if (inCall != NULL) {
        // This may happen when we have bugs or some module is not calling
        // us asynchronously (comm used to do that).
        debugs(93, 5, HERE << inCall << " is in progress; " <<
               call << " canot reenter the job.");
        return call.cancel("reentrant job call");
    }

    return true;
}