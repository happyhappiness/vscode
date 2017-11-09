bool Curl_auth_is_spnego_supported(void)
{
  PSecPkgInfo SecurityPackage;
  SECURITY_STATUS status;

  /* Query the security package for Negotiate */
  status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *)
                                              TEXT(SP_NAME_NEGOTIATE),
                                              &SecurityPackage);

  return (status == SEC_E_OK ? TRUE : FALSE);
}