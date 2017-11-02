int Curl_axtls_init(void)
{
/* axTLS has no global init.  Everything is done through SSL and SSL_CTX
 * structs stored in connectdata structure.  Perhaps can move to axtls.h.
 */
  return 1;
}