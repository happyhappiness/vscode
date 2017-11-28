static void
authDigestNonceEncode(digest_nonce_h * nonce)
{
    if (!nonce)
        return;

    if (nonce->key)
        xfree(nonce->key);

    nonce->key = xcalloc(base64_encode_len(sizeof(digest_nonce_data)), 1);
    struct base64_encode_ctx ctx;
    base64_encode_init(&ctx);
    size_t blen = base64_encode_update(&ctx, reinterpret_cast<uint8_t*>(nonce->key), sizeof(digest_nonce_data), reinterpret_cast<const uint8_t*>(&(nonce->noncedata)));
    blen += base64_encode_final(&ctx, reinterpret_cast<uint8_t*>(nonce->key)+blen);
}