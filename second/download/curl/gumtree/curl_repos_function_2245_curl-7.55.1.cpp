bool Curl_auth_is_gssapi_supported(void)
{
  PSecPkgInfo SecurityPackage;
  SECURITY_STATUS status;

  /* Query the security package for Kerberos */
  status = s_pSecFn->QuerySecurityPackageInfo((TCHAR *)
                                              TEXT(SP_NAME_KERBEROS),
                                              &SecurityPackage);

  return (status == SEC_E_OK ? TRUE : FALSE);
}