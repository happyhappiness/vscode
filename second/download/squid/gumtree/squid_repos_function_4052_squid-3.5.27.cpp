Adaptation::Ecap::Host::MessagePtr
Adaptation::Ecap::Host::newResponse() const
{
    return MessagePtr(new Adaptation::Ecap::MessageRep(new HttpReply));
}