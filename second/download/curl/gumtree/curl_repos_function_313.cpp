char *
Curl_ldap_err2string_a(int error)

{
  return set_thread_string(LK_LDAP_ERROR, ldap_err2string(error));
}