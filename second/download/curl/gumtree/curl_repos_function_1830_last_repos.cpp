static void do_pubkey_field(struct Curl_easy *data, int certnum,
                            const char *label, curl_asn1Element *elem)
{
  const char *output;

  /* Generate a certificate information record for the public key. */

  output = Curl_ASN1tostr(elem, 0);
  if(output) {
    if(data->set.ssl.certinfo)
      Curl_ssl_push_certinfo(data, certnum, label, output);
    if(!certnum)
      infof(data, "   %s: %s\n", label, output);
    free((char *) output);
  }
}