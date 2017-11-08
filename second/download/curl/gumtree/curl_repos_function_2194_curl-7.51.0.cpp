bool Curl_auth_user_contains_domain(const char *user)
{
  bool valid = FALSE;

  if(user && *user) {
    /* Check we have a domain name or UPN present */
    char *p = strpbrk(user, "\\/@");

    valid = (p != NULL && p > user && p < user + strlen(user) - 1 ? TRUE :
                                                                    FALSE);
  }
#if defined(HAVE_GSSAPI) || defined(USE_WINDOWS_SSPI)
  else
    /* User and domain are obtained from the GSS-API credientials cache or the
       currently logged in user from Windows */
    valid = TRUE;
#endif

  return valid;
}