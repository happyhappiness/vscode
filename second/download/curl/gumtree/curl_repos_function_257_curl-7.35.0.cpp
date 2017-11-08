static char *i2s_ASN1_IA5STRING( ASN1_IA5STRING *ia5)
{
  char *tmp;
  if(!ia5 || !ia5->length)
    return NULL;
  tmp = OPENSSL_malloc(ia5->length + 1);
  memcpy(tmp, ia5->data, ia5->length);
  tmp[ia5->length] = 0;
  return tmp;
}