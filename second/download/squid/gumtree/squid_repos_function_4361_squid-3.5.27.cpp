inline const char *sslCertAdaptAlgoritm(int alg)
{
    if (alg >=0 && alg < Ssl::algSetEnd)
        return Ssl::CertAdaptAlgorithmStr[alg];

    return NULL;
}