void
ESIContext::setErrorMessage(char const *anError)
{
    if (!errormessage)
        errormessage = xstrdup(anError);
}