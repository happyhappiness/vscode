void
ServerStateData::handleAdaptationCompleted()
{
    debugs(11,5, HERE << "handleAdaptationCompleted");
    cleanAdaptation();

    // We stop reading origin response because we have no place to put it and
    // cannot use it. If some origin servers do not like that or if we want to
    // reuse more pconns, we can add code to discard unneeded origin responses.
    if (!doneWithServer()) {
        debugs(11,3, HERE << "closing origin conn due to ICAP completion");
        closeServer();
    }

    completeForwarding();
    quitIfAllDone();
}