void AsyncJob::callEnd()
{
    if (done()) {
        debugs(93, 5, *inCall << " ends job" << status());

        AsyncCall::Pointer inCallSaved = inCall;
        void *thisSaved = this;

        swanSong();

        delete this; // this is the only place where the object is deleted

        // careful: this object does not exist any more
        debugs(93, 6, HERE << *inCallSaved << " ended " << thisSaved);
        return;
    }

    debugs(inCall->debugSection, inCall->debugLevel,
           typeName << " status out:" << status());
    inCall = NULL;
}