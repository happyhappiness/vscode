int
Adaptation::Ecap::StatusLineRep::statusCode() const
{
    // TODO: remove cast when possible
    return static_cast<int>(theMessage.sline.status());
}