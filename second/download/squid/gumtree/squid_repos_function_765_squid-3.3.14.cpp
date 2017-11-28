void
ClientRequestContext::sslBumpAccessCheckDone(const allow_t &answer)
{
    if (!httpStateIsValid())
        return;

    const Ssl::BumpMode bumpMode = answer == ACCESS_ALLOWED ?
                                   static_cast<Ssl::BumpMode>(answer.kind) : Ssl::bumpNone;
    http->sslBumpNeed(bumpMode); // for processRequest() to bump if needed
    http->al->ssl.bumpMode = bumpMode; // for logging

    http->doCallouts();
}