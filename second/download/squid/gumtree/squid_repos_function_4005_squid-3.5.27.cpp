void
Adaptation::Ecap::StatusLineRep::statusCode(int code)
{
    theMessage.sline.set(theMessage.sline.version, static_cast<Http::StatusCode>(code), NULL);
}