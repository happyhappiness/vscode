void
Adaptation::Ecap::FirstLineRep::protocol(const Name &p)
{
    // TODO: what happens if we fail to translate some protocol?
    theMessage.protocol = TranslateProtocolId(p);
}