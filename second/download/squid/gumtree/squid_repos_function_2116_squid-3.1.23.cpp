void ServerStateData::quitIfAllDone()
{
#if USE_ADAPTATION
    if (!doneWithAdaptation()) {
        debugs(11,5, HERE << "transaction not done: still talking to ICAP");
        return;
    }
#endif

    if (!doneWithServer()) {
        debugs(11,5, HERE << "transaction not done: still talking to server");
        return;
    }

    debugs(11,3, HERE << "transaction done");

    deleteThis("ServerStateData::quitIfAllDone");
}