static char *x509_get_part (X509_NAME *name, int nid)
{
  static char ret[SHORT_STRING];

  if (!name ||
      X509_NAME_get_text_by_NID (name, nid, ret, sizeof (ret)) < 0)
    strfcpy (ret, _("Unknown"), sizeof (ret));

  return ret;
}