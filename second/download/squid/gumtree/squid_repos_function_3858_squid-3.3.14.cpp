void
Adaptation::Initiate::initiator(const CbcPointer<Initiator> &i)
{
    Must(!theInitiator);
    Must(i.valid());
    theInitiator = i;
}