static int cldap_init(void) /* {{{ */
{
  /* Initialize LDAP library while still single-threaded as recommended in
   * ldap_initialize(3) */
  int debug_level;
  ldap_get_option(NULL, LDAP_OPT_DEBUG_LEVEL, &debug_level);
  return 0;
}