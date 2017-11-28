void Adaptation::Icap::ModXact::writePrimeBody()
{
    Must(state.writing == State::writingPrime);
    Must(virginBodyWriting.active());

    const size_t size = (size_t)virgin.body_pipe->buf().contentSize();
    writeSomeBody("prime virgin body", size);

    if (virginBodyEndReached(virginBodyWriting)) {
        debugs(93, 5, HERE << "wrote entire body");
        stopWriting(true);
    }
}