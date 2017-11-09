static int asn1_object_dump(ASN1_OBJECT *a, char *buf, size_t len)
{
  int i, ilen;

  ilen = (int)len;
  if(ilen < 0)
    return 1; /* buffer too big */

  i = i2t_ASN1_OBJECT(buf, ilen, a);

  if(i >= ilen)
    return 1; /* buffer too small */

  return 0;
}