bool Curl_auth_is_digest_supported(void)
{
  PSecPkgInfo SecurityPackage;
  SECURITY_STATUS status;

  /* Query the security package for Digest */
  status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *) TEXT(SP_NAME_DIGEST),
                                              &SecurityPackage);

  return (status == SEC_E_OK ? TRUE : FALSE);
}