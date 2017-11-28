void Adaptation::Icap::ModXact::handle100Continue()
{
    Must(state.writing == State::writingPaused);
    // server must not respond before the end of preview: we may send ieof
    Must(preview.enabled() && preview.done() && !preview.ieof());

    // 100 "Continue" cancels our Preview commitment,
    // but not commitment to handle 204 or 206 outside Preview
    if (!state.allowedPostview204 && !state.allowedPostview206)
        stopBackup();

    state.parsing = State::psIcapHeader; // eventually
    icapReply->reset();

    state.writing = State::writingPrime;

    writeMore();
}