void Adaptation::Icap::ModXact::swanSong()
{
    debugs(93, 5, HERE << "swan sings" << status());

    stopWriting(false);
    stopSending(false);

    // update adaptation history if start was called and we reserved a slot
    Adaptation::History::Pointer ah = virginRequest().adaptLogHistory();
    if (ah != NULL && adaptHistoryId >= 0)
        ah->recordXactFinish(adaptHistoryId);

    Adaptation::Icap::Xaction::swanSong();
}