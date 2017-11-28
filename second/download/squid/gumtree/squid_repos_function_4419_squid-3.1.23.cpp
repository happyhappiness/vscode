bool
ACLProtocolData::match(protocol_t toFind)
{
    return values->findAndTune (toFind);
}