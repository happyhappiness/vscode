Adaptation::Ecap::Host::MessagePtr
Adaptation::Ecap::Host::newRequest() const
{
    return MessagePtr(new Adaptation::Ecap::MessageRep(new HttpRequest));
}