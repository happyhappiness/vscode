void
DigestCalcHA1(
    const char *pszAlg,
    const char *pszUserName,
    const char *pszRealm,
    const char *pszPassword,
    const char *pszNonce,
    const char *pszCNonce,
    HASH HA1,
    HASHHEX SessionKey
)
{
    SquidMD5_CTX Md5Ctx;

    if (pszUserName) {
        SquidMD5Init(&Md5Ctx);
        SquidMD5Update(&Md5Ctx, pszUserName, strlen(pszUserName));
        SquidMD5Update(&Md5Ctx, ":", 1);
        SquidMD5Update(&Md5Ctx, pszRealm, strlen(pszRealm));
        SquidMD5Update(&Md5Ctx, ":", 1);
        SquidMD5Update(&Md5Ctx, pszPassword, strlen(pszPassword));
        SquidMD5Final((unsigned char *) HA1, &Md5Ctx);
    }
    if (strcasecmp(pszAlg, "md5-sess") == 0) {
        HASHHEX HA1Hex;
        CvtHex(HA1, HA1Hex);	/* RFC2617 errata */
        SquidMD5Init(&Md5Ctx);
        SquidMD5Update(&Md5Ctx, HA1Hex, HASHHEXLEN);
        SquidMD5Update(&Md5Ctx, ":", 1);
        SquidMD5Update(&Md5Ctx, pszNonce, strlen(pszNonce));
        SquidMD5Update(&Md5Ctx, ":", 1);
        SquidMD5Update(&Md5Ctx, pszCNonce, strlen(pszCNonce));
        SquidMD5Final((unsigned char *) HA1, &Md5Ctx);
    }
    CvtHex(HA1, SessionKey);
}