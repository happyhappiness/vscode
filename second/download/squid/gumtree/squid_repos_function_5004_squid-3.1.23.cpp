void AsyncJob::callStart(AsyncCall &call)
{
    // we must be called asynchronously and hence, the caller must lock us
    Must(cbdataReferenceValid(toCbdata()));

    Must(!inCall); // see AsyncJob::canBeCalled

    inCall = &call; // XXX: ugly, but safe if callStart/callEnd,Ex are paired
    debugs(inCall->debugSection, inCall->debugLevel,
           typeName << " status in:" << status());
}