void
ACLChecklist::resumeNonBlockingCheck(AsyncState *state)
{
    assert(asyncState() == state);
    changeState(NullState::Instance());

    if (asyncStage_ == asyncStarting) { // oops, we did not really go async
        asyncStage_ = asyncFailed; // goAsync() checks for that
        // Do not fall through to resume checks from the async callback. Let
        // the still-pending(!) goAsync() notice and notify its caller instead.
        return;
    }
    assert(asyncStage_ == asyncRunning);
    asyncStage_ = asyncNone;

    assert(!matchPath.empty());

    if (!prepNonBlocking())
        return; // checkCallback() has been called

    if (!finished())
        matchAndFinish();

    if (asyncInProgress())
        assert(!matchPath.empty()); // we have breadcrumbs to resume matching
    else
        completeNonBlocking();
}