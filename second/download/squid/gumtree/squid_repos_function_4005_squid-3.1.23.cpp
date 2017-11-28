void Adaptation::Icap::Xaction::swanSong()
{
    // kids should sing first and then call the parent method.

    closeConnection(); // TODO: rename because we do not always close

    if (!readBuf.isNull())
        readBuf.clean();

    if (commBuf)
        memFreeBuf(commBufSize, commBuf);

    tellQueryAborted();

    maybeLog();

    Adaptation::Initiate::swanSong();
}