        Must(state.sending == State::sendingUndecided);
}

// adapted body consumer aborted
void Adaptation::Icap::ModXact::noteBodyConsumerAborted(BodyPipe::Pointer)
{
    mustStop("adapted body consumer aborted");
}

Adaptation::Icap::ModXact::~ModXact()
{
    delete bodyParser;
