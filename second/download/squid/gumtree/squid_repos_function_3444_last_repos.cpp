Adaptation::Ecap::Host::MessagePtr
Adaptation::Ecap::Host::newRequest() const
{
    static const MasterXaction::Pointer mx = new MasterXaction(XactionInitiator::initAdaptationOrphan_);
    return MessagePtr(new Adaptation::Ecap::MessageRep(new HttpRequest(mx)));
}