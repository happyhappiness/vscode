void
Adaptation::Ecap::XactionRep::noteMoreBodyDataAvailable(RefCount<BodyPipe> bp)
{
    Must(makingVb == opOn); // or we would not be registered as a consumer
    Must(theMaster);
    theMaster->noteVbContentAvailable();
}