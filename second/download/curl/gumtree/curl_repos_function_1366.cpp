CURLcode Curl_create_sspi_identity(const char *userp, const char *passwdp,
                                   SEC_WINNT_AUTH_IDENTITY *identity)
{
  xcharp_u useranddomain;
  xcharp_u user, dup_user;
  xcharp_u domain, dup_domain;
  xcharp_u passwd, dup_passwd;
  size_t domlen = 0;

  domain.const_tchar_ptr = TEXT("");

  /* Initialize the identity */
  memset(identity, 0, sizeof(*identity));

  useranddomain.tchar_ptr = Curl_convert_UTF8_to_tchar((char *)userp);
  if(!useranddomain.tchar_ptr)
    return CURLE_OUT_OF_MEMORY;

  user.const_tchar_ptr = _tcschr(useranddomain.const_tchar_ptr, TEXT('\\'));
  if(!user.const_tchar_ptr)
    user.const_tchar_ptr = _tcschr(useranddomain.const_tchar_ptr, TEXT('/'));

  if(user.tchar_ptr) {
    domain.tchar_ptr = useranddomain.tchar_ptr;
    domlen = user.tchar_ptr - useranddomain.tchar_ptr;
    user.tchar_ptr++;
  }
  else {
    user.tchar_ptr = useranddomain.tchar_ptr;
    domain.const_tchar_ptr = TEXT("");
    domlen = 0;
  }

  /* Setup the identity's user and length */
  dup_user.tchar_ptr = _tcsdup(user.tchar_ptr);
  if(!dup_user.tchar_ptr) {
    Curl_unicodefree(useranddomain.tchar_ptr);
    return CURLE_OUT_OF_MEMORY;
  }
  identity->User = dup_user.tbyte_ptr;
  identity->UserLength = curlx_uztoul(_tcslen(dup_user.tchar_ptr));
  dup_user.tchar_ptr = NULL;

  /* Setup the identity's domain and length */
  dup_domain.tchar_ptr = malloc(sizeof(TCHAR) * (domlen + 1));
  if(!dup_domain.tchar_ptr) {
    Curl_unicodefree(useranddomain.tchar_ptr);
    return CURLE_OUT_OF_MEMORY;
  }
  _tcsncpy(dup_domain.tchar_ptr, domain.tchar_ptr, domlen);
  *(dup_domain.tchar_ptr + domlen) = TEXT('\0');
  identity->Domain = dup_domain.tbyte_ptr;
  identity->DomainLength = curlx_uztoul(domlen);
  dup_domain.tchar_ptr = NULL;

  Curl_unicodefree(useranddomain.tchar_ptr);

  /* Setup ntlm identity's password and length */
  passwd.tchar_ptr = Curl_convert_UTF8_to_tchar((char *)passwdp);
  if(!passwd.tchar_ptr)
    return CURLE_OUT_OF_MEMORY;
  dup_passwd.tchar_ptr = _tcsdup(passwd.tchar_ptr);
  if(!dup_passwd.tchar_ptr) {
    Curl_unicodefree(passwd.tchar_ptr);
    return CURLE_OUT_OF_MEMORY;
  }
  identity->Password = dup_passwd.tbyte_ptr;
  identity->PasswordLength = curlx_uztoul(_tcslen(dup_passwd.tchar_ptr));
  dup_passwd.tchar_ptr = NULL;

  Curl_unicodefree(passwd.tchar_ptr);

  /* Setup the identity's flags */
  identity->Flags = SECFLAG_WINNT_AUTH_IDENTITY;

  return CURLE_OK;
}