bool
ACLChecklist::goAsync(AsyncState *state)
{
    assert(state);
    assert(!asyncInProgress());
    assert(matchLoc_.parent);

    // TODO: add a once-in-a-while WARNING about fast directive using slow ACL?
    if (!asyncCaller_) {
        debugs(28, 2, this << " a fast-only directive uses a slow ACL!");
        return false;
    }

    // TODO: add a once-in-a-while WARNING about async loops?
    if (matchLoc_ == asyncLoc_) {
        debugs(28, 2, this << " a slow ACL resumes by going async again! (loop #" << asyncLoopDepth_ << ")");
        // external_acl_type may cause async auth lookup plus its own async check
        // which has the appearance of a loop. Allow some retries.
        // TODO: make it configurable and check BH retry attempts vs this check?
        if (asyncLoopDepth_ > 5)
            return false;
    }

    asyncLoc_ = matchLoc_; // prevent async loops
    ++asyncLoopDepth_;

    asyncStage_ = asyncStarting;
    changeState(state);
    state->checkForAsync(this); // this is supposed to go async

    // Did AsyncState object actually go async? If not, tell the caller.
    if (asyncStage_ != asyncStarting) {
        assert(asyncStage_ == asyncFailed);
        asyncStage_ = asyncNone; // sanity restored
        return false;
    }

    // yes, we must pause until the async callback calls resumeNonBlockingCheck
    asyncStage_ = asyncRunning;
    return true;
}