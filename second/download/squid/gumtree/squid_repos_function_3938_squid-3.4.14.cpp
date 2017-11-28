void
Adaptation::Ecap::StatusLineRep::reasonPhrase(const Area &str)
{
    theMessage.sline.set(theMessage.sline.version, theMessage.sline.status(), str.toString().c_str());
}