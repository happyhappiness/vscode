bool
ACLSslErrorData::match(const Security::CertErrors *toFind)
{
    for (const auto *err = toFind; err; err = err->next) {
        if (values.count(err->element.code))
            return true;
    }
    return false;
}