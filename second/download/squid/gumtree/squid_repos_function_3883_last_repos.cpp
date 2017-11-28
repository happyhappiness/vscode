void Ssl::CertValidationHelper::Shutdown()
{
    if (!ssl_crt_validator)
        return;
    helperShutdown(ssl_crt_validator);
    wordlistDestroy(&ssl_crt_validator->cmdline);
    delete ssl_crt_validator;
    ssl_crt_validator = NULL;

    // CertValidationHelper::HelperCache is a static member, it is not good policy to
    // reset it here. Will work because the current Ssl::CertValidationHelper is
    // always the same static object.
    delete HelperCache;
    HelperCache = NULL;
}