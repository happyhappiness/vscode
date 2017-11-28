void Adaptation::Icap::ModXact::handleCommWrote(size_t sz)
{
    debugs(93, 5, HERE << "Wrote " << sz << " bytes");

    if (state.writing == State::writingHeaders)
        handleCommWroteHeaders();
    else
        handleCommWroteBody();
}