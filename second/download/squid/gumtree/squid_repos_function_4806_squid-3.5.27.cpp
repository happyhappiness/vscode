void
ACLChecklist::nonBlockingCheck(ACLCB * callback_, void *callback_data_)
{
    preCheck("slow rules");
    callback = callback_;
    callback_data = cbdataReference(callback_data_);
    asyncCaller_ = true;

    /** The ACL List should NEVER be NULL when calling this method.
     * Always caller should check for NULL and handle appropriate to its needs first.
     * We cannot select a sensible default for all callers here. */
    if (accessList == NULL) {
        debugs(28, DBG_CRITICAL, "SECURITY ERROR: ACL " << this << " checked with nothing to match against!!");
        checkCallback(ACCESS_DUNNO);
        return;
    }

    if (prepNonBlocking()) {
        matchAndFinish(); // calls markFinished() on success
        if (!asyncInProgress())
            completeNonBlocking();
    } // else checkCallback() has been called
}