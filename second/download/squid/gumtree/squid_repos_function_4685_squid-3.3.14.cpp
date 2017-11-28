bool
ACLProtocolData::match(AnyP::ProtocolType toFind)
{
    return values->findAndTune (toFind);
}