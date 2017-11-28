static void
authDigestNonceEncode(digest_nonce_h * nonce)
{
    if (!nonce)
        return;

    if (nonce->key)
        xfree(nonce->key);

    nonce->key = xstrdup(base64_encode_bin((char *) &(nonce->noncedata), sizeof(digest_nonce_data)));
}