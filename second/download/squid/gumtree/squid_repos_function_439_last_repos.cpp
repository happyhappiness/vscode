void
ClientHttpRequest::sslBumpNeed(Ssl::BumpMode mode)
{
    debugs(83, 3, HERE << "sslBump required: "<< Ssl::bumpMode(mode));
    sslBumpNeed_ = mode;
}