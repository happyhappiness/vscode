bool Curl_auth_is_ntlm_supported(void)
{
  PSecPkgInfo SecurityPackage;
  SECURITY_STATUS status;

  /* Query the security package for NTLM */
  status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *) TEXT(SP_NAME_NTLM),
                                              &SecurityPackage);

  return (status == SEC_E_OK ? TRUE : FALSE);
}