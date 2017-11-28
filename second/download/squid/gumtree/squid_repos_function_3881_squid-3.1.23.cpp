void Adaptation::Icap::ModXact::handleCommWroteHeaders()
{
    Must(state.writing == State::writingHeaders);

    // determine next step
    if (preview.enabled()) {
        if (preview.done())
            decideWritingAfterPreview("zero-size");
        else
            state.writing = State::writingPreview;
    } else if (virginBody.expected()) {
        state.writing = State::writingPrime;
    } else {
        stopWriting(true);
        return;
    }

    writeMore();
}