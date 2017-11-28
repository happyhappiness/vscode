void Adaptation::Icap::ModXact::readMore()
{
    if (reader != NULL || doneReading()) {
        debugs(93,3,HERE << "returning from readMore because reader or doneReading()");
        return;
    }

    // do not fill readBuf if we have no space to store the result
    if (adapted.body_pipe != NULL &&
            !adapted.body_pipe->buf().hasPotentialSpace()) {
        debugs(93,3,HERE << "not reading because ICAP reply pipe is full");
        return;
    }

    if (readBuf.hasSpace())
        scheduleRead();
    else
        debugs(93,3,HERE << "nothing to do because !readBuf.hasSpace()");
}