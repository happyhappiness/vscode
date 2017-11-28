bool
ACLSslErrorData::match(const Ssl::CertErrors *toFind)
{
    for (const Ssl::CertErrors *err = toFind; err; err = err->next ) {
        if (values->findAndTune(err->element.code))
            return true;
    }
    return false;
}