Adaptation::Ecap::StatusLineRep::Area
Adaptation::Ecap::StatusLineRep::reasonPhrase() const
{
    return Area::FromTempString(std::string(theMessage.sline.reason()));
}