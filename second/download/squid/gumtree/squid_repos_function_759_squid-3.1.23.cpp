void
ClientHttpRequest::sslBumpNeeded(bool isNeeded)
{
    debugs(83, 3, HERE << "sslBump required: "<< (isNeeded ? "Yes" : "No"));
    sslBumpNeed = (isNeeded ? needConfirmed : needNot);
}