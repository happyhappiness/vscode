static void X509_signature(struct SessionHandle *data,
                           int numcert,
                           ASN1_STRING *sig)
{
  char buf[1024];
  char *ptr = buf;
  int i;

  for(i=0; i<sig->length; i++)
    ptr+=snprintf(ptr, sizeof(buf)-(ptr-buf), "%02x:", sig->data[i]);

  infof(data, " Signature: %s\n", buf);
  Curl_ssl_push_certinfo(data, numcert, "Signature", buf);
}