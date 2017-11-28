void Adaptation::Icap::ModXact::bypassFailure()
{
    disableBypass("already started to bypass", false);

    Must(!isRetriable); // or we should not be bypassing
    // TODO: should the same be enforced for isRepeatable? Check icap_repeat??

    prepEchoing();

    startSending();

    // end all activities associated with the ICAP server

    stopParsing();

    stopWriting(true); // or should we force it?
    if (connection >= 0) {
        reuseConnection = false; // be conservative
        cancelRead(); // may not work; and we cannot stop connecting either
        if (!doneWithIo())
            debugs(93, 7, HERE << "Warning: bypass failed to stop I/O" << status());
    }

    service().noteFailure(); // we are bypassing, but this is still a failure
}