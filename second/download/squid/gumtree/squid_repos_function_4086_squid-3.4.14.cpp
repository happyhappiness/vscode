void Adaptation::Icap::ModXact::noteBodyConsumerAborted(BodyPipe::Pointer)
{
    detailError(ERR_DETAIL_ICAP_XACT_BODY_CONSUMER_ABORT);
    mustStop("adapted body consumer aborted");
}