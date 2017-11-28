bool
ClientHttpRequest::sslBumpNeeded() const
{
    assert(sslBumpNeed != needUnknown);
    return (sslBumpNeed == needConfirmed);
}