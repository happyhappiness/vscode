bool
ACLSslErrorData::match(const Ssl::Errors *toFind)
{
    for (const Ssl::Errors *err = toFind; err; err = err->next ) {
        if (values->findAndTune(err->element))
            return true;
    }
    return false;
}