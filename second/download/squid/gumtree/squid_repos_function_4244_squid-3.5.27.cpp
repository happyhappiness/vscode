void Adaptation::Icap::Xaction::swanSong()
{
    // kids should sing first and then call the parent method.
    if (cs.valid()) {
        debugs(93,6, HERE << id << " about to notify ConnOpener!");
        CallJobHere(93, 3, cs, Comm::ConnOpener, noteAbort);
        cs = NULL;
        service().noteConnectionFailed("abort");
    }

    closeConnection(); // TODO: rename because we do not always close

    if (!readBuf.isNull())
        readBuf.clean();

    if (commBuf)
        memFreeBuf(commBufSize, commBuf);

    tellQueryAborted();

    maybeLog();

    Adaptation::Initiate::swanSong();
}