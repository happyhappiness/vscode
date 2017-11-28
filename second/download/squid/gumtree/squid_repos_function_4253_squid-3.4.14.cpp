inline const char *certSignAlgorithm(int sg)
{
    if (sg >=0 && sg < Ssl::algSignEnd)
        return Ssl::CertSignAlgorithmStr[sg];

    return NULL;
}