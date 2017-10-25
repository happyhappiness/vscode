static unsigned char *my_get_ext(X509 * cert, const int type,
                                 int extensiontype)
{
  int i;
  STACK_OF(ACCESS_DESCRIPTION) * accessinfo ;
  accessinfo =  X509_get_ext_d2i(cert, extensiontype, NULL, NULL) ;

  if (!sk_ACCESS_DESCRIPTION_num(accessinfo))
    return NULL;

  for (i = 0; i < sk_ACCESS_DESCRIPTION_num(accessinfo); i++) {
    ACCESS_DESCRIPTION * ad = sk_ACCESS_DESCRIPTION_value(accessinfo, i);
    if (OBJ_obj2nid(ad->method) == type) {
      if (ad->location->type == GEN_URI) {
        return i2s_ASN1_IA5STRING(ad->location->d.ia5);
      }
      return NULL;
    }
  }
  return NULL;
}