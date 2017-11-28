void
DigestCalcResponse(
    const HASHHEX HA1,      /* H(A1) */
    const char *pszNonce,   /* nonce from server */
    const char *pszNonceCount,  /* 8 hex digits */
    const char *pszCNonce,  /* client nonce */
    const char *pszQop,     /* qop-value: "", "auth", "auth-int" */
    const char *pszMethod,  /* method from the request */
    const char *pszDigestUri,   /* requested URL */
    const HASHHEX HEntity,  /* H(entity body) if qop="auth-int" */
    HASHHEX Response        /* request-digest or response-digest */
)
{
    SquidMD5_CTX Md5Ctx;
    HASH HA2;
    HASH RespHash;
    HASHHEX HA2Hex;

    /*  calculate H(A2)
     */
    SquidMD5Init(&Md5Ctx);
    SquidMD5Update(&Md5Ctx, pszMethod, strlen(pszMethod));
    SquidMD5Update(&Md5Ctx, ":", 1);
    SquidMD5Update(&Md5Ctx, pszDigestUri, strlen(pszDigestUri));
    if (pszQop && strcasecmp(pszQop, "auth-int") == 0) {
        SquidMD5Update(&Md5Ctx, ":", 1);
        SquidMD5Update(&Md5Ctx, HEntity, HASHHEXLEN);
    }
    SquidMD5Final((unsigned char *) HA2, &Md5Ctx);
    CvtHex(HA2, HA2Hex);

    /* calculate response
     */
    SquidMD5Init(&Md5Ctx);
    SquidMD5Update(&Md5Ctx, HA1, HASHHEXLEN);
    SquidMD5Update(&Md5Ctx, ":", 1);
    SquidMD5Update(&Md5Ctx, pszNonce, strlen(pszNonce));
    SquidMD5Update(&Md5Ctx, ":", 1);
    if (pszQop) {
        SquidMD5Update(&Md5Ctx, pszNonceCount, strlen(pszNonceCount));
        SquidMD5Update(&Md5Ctx, ":", 1);
        SquidMD5Update(&Md5Ctx, pszCNonce, strlen(pszCNonce));
        SquidMD5Update(&Md5Ctx, ":", 1);
        SquidMD5Update(&Md5Ctx, pszQop, strlen(pszQop));
        SquidMD5Update(&Md5Ctx, ":", 1);
    }
    SquidMD5Update(&Md5Ctx, HA2Hex, HASHHEXLEN);
    SquidMD5Final((unsigned char *) RespHash, &Md5Ctx);
    CvtHex(RespHash, Response);
}