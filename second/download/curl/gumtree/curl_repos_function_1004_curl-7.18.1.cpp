static bool unescape_elements (void *data, LDAPURLDesc *ludp)
{
  int i;

  if(ludp->lud_filter) {
    ludp->lud_filter = curl_easy_unescape(data, ludp->lud_filter, 0, NULL);
    if(!ludp->lud_filter)
       return (FALSE);
  }

  for (i = 0; ludp->lud_attrs && ludp->lud_attrs[i]; i++) {
    ludp->lud_attrs[i] = curl_easy_unescape(data, ludp->lud_attrs[i], 0, NULL);
    if(!ludp->lud_attrs[i])
       return (FALSE);
  }

  for (i = 0; ludp->lud_exts && ludp->lud_exts[i]; i++) {
    ludp->lud_exts[i] = curl_easy_unescape(data, ludp->lud_exts[i], 0, NULL);
    if(!ludp->lud_exts[i])
       return (FALSE);
  }

  if(ludp->lud_dn) {
    char *dn = ludp->lud_dn;
    char *new_dn = curl_easy_unescape(data, dn, 0, NULL);

    free(dn);
    ludp->lud_dn = new_dn;
    if(!new_dn)
       return (FALSE);
  }
  return (TRUE);
}