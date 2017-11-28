void Adaptation::Icap::ModXact::updateSources()
{
    Must(adapted.header);
    adapted.header->sources |= (service().cfg().connectionEncryption ? HttpMsg::srcIcaps : HttpMsg::srcIcap);
}