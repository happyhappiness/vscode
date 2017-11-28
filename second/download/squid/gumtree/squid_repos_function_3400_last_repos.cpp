void
Adaptation::Ecap::StatusLineRep::reasonPhrase(const Area &)
{
    // Squid does not support external custom reason phrases so we have
    // to just reset it (in case there was a custom internal reason set)
    theMessage.sline.resetReason();
}