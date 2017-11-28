void AsyncJob::deleteThis(const char *aReason)
{
    Must(aReason);
    stopReason = aReason;
    if (inCall != NULL) {
        // if we are in-call, then the call wrapper will delete us
        debugs(93, 4, typeName << " will NOT delete in-call job, reason: " << stopReason);
        return;
    }

    // there is no call wrapper waiting for our return, so we fake it
    debugs(93, 5, typeName << " will delete this, reason: " << stopReason);
    CbcPointer<AsyncJob> self(this);
    AsyncCall::Pointer fakeCall = asyncCall(93,4, "FAKE-deleteThis",
                                            JobMemFun(self, &AsyncJob::deleteThis, aReason));
    inCall = fakeCall;
    callEnd();
//    delete fakeCall;
}