void Adaptation::Icap::ModXact::handle204NoContent()
{
    stopParsing();
    prepEchoing();
}

// Called when we receive a 204 No Content response and
// when we are trying to bypass a service failure.
// We actually start sending (echoig or not) in startSending.
void Adaptation::Icap::ModXact::prepEchoing()
{
    disableRepeats("preparing to echo content");
