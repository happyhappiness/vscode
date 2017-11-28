void Adaptation::Icap::ModXact::handle204NoContent()
{
    stopParsing();
    prepEchoing();
}

void Adaptation::Icap::ModXact::handle206PartialContent()
{
    if (state.writing == State::writingPaused) {
        Must(preview.enabled());
        Must(state.allowedPreview206);
        debugs(93, 7, HERE << "206 inside preview");
    } else {
        Must(state.writing > State::writingPaused);
        Must(state.allowedPostview206);
        debugs(93, 7, HERE << "206 outside preview");
    }
    state.parsing = State::psHttpHeader;
    state.sending = State::sendingAdapted;
    state.readyForUob = true;
    checkConsuming();
}

// Called when we receive a 204 No Content response and
// when we are trying to bypass a service failure.
// We actually start sending (echoig or not) in startSending.
void Adaptation::Icap::ModXact::prepEchoing()
{
    disableRepeats("preparing to echo content");
