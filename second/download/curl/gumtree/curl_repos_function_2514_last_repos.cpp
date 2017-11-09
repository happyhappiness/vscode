static void Curl_darwinssl_sha256sum(const unsigned char *tmp, /* input */
                                     size_t tmplen,
                                     unsigned char *sha256sum, /* output */
                                     size_t sha256len)
{
  assert(sha256len >= CURL_SHA256_DIGEST_LENGTH);
  (void)CC_SHA256(tmp, (CC_LONG)tmplen, sha256sum);
}