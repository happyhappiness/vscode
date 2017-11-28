void Adaptation::Icap::ModXact::noteBodyConsumerAborted(BodyPipe::Pointer)
{
    mustStop("adapted body consumer aborted");
}