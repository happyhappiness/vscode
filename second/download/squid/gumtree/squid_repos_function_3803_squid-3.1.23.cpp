int
Adaptation::Ecap::StatusLineRep::statusCode() const
{
    // TODO: see statusCode(code) TODO above
    return static_cast<int>(theMessage.sline.status);
}