static int Curl_qsossl_trap_cert(SSLHandle * h)

{
  return 1;       /* Accept certificate. */
}