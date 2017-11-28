void
Adaptation::Ecap::StatusLineRep::reasonPhrase(const Area &)
{
    // Squid does not support custom reason phrases
    theMessage.sline.reason = NULL;
}