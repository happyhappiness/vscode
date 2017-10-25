static void _ldap_free_urldesc (LDAPURLDesc *ludp)
{
  int i;

  if (!ludp)
     return;

  if (ludp->lud_dn)
     free(ludp->lud_dn);

  if (ludp->lud_filter)
     free(ludp->lud_filter);

  if (ludp->lud_attrs) {
    for (i = 0; ludp->lud_attrs[i]; i++)
       free(ludp->lud_attrs[i]);
    free(ludp->lud_attrs);
  }

  if (ludp->lud_exts) {
    for (i = 0; ludp->lud_exts[i]; i++)
       free(ludp->lud_exts[i]);
    free(ludp->lud_exts);
  }
  free (ludp);
}