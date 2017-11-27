static int cldap_shutdown(void) /* {{{ */
{
  for (size_t i = 0; i < databases_num; i++)
    if (databases[i]->ld != NULL)
      ldap_unbind_ext_s(databases[i]->ld, NULL, NULL);
  sfree(databases);
  databases_num = 0;

  return (0);
}