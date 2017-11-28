void Adaptation::Icap::ModXact::handle204NoContent()
{
    stopParsing();
    prepEchoing();
}