static void Curl_mbedtls_sha256sum(const unsigned char *input,
                                    size_t inputlen,
                                    unsigned char *sha256sum,
                                    size_t sha256len UNUSED_PARAM)
{
  (void)sha256len;
  mbedtls_sha256(input, inputlen, sha256sum, 0);
}