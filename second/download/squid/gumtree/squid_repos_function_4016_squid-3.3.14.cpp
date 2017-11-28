void Adaptation::Icap::ModXact::writeMore()
{
    debugs(93, 5, HERE << "checking whether to write more" << status());

    if (writer != NULL) // already writing something
        return;

    switch (state.writing) {

    case State::writingInit:    // waiting for service OPTIONS
        Must(state.serviceWaiting);

    case State::writingConnect: // waiting for the connection to establish

    case State::writingHeaders: // waiting for the headers to be written

    case State::writingPaused:  // waiting for the ICAP server response

    case State::writingReallyDone: // nothing more to write
        return;

    case State::writingAlmostDone: // was waiting for the last write
        stopWriting(false);
        return;

    case State::writingPreview:
        writePreviewBody();
        return;

    case State::writingPrime:
        writePrimeBody();
        return;

    default:
        throw TexcHere("Adaptation::Icap::ModXact in bad writing state");
    }
}