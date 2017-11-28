    delete ssl_crtd;
    ssl_crtd = NULL;
}

void Ssl::Helper::sslSubmit(CrtdMessage const & message, HLPCB * callback, void * data)
{
    assert(ssl_crtd);

    std::string msg = message.compose();
    msg += '\n';
    if (!ssl_crtd->trySubmit(msg.c_str(), callback, data)) {
        ::Helper::Reply failReply(::Helper::BrokenHelper);
        failReply.notes.add("message", "error 45 Temporary network problem, please retry later");
        callback(data, failReply);
        return;
    }
}
#endif //USE_SSL_CRTD

Ssl::CertValidationHelper * Ssl::CertValidationHelper::GetInstance()
{
    static Ssl::CertValidationHelper sslHelper;
