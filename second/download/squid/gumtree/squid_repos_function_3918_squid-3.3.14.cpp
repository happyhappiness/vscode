Adaptation::Ecap::StatusLineRep::Area
Adaptation::Ecap::StatusLineRep::reasonPhrase() const
{
    return theMessage.sline.reason ?
           Area::FromTempString(std::string(theMessage.sline.reason)) : Area();
}