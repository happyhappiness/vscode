void
ClientRequestContext::sslBumpAccessCheckDone(bool doSslBump)
{
    http->sslBumpNeeded(doSslBump);
    http->doCallouts();
}