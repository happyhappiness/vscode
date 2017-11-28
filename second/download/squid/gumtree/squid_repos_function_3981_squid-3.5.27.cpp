CbcPointer<Adaptation::Initiate>
Adaptation::Initiator::initiateAdaptation(Initiate *x)
{
    CbcPointer<Initiate> i(x);
    x->initiator(this);
    Start(x);
    return i;
}