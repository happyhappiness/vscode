TCHAR *Curl_auth_build_spn(const char *service, const char *host,
                           const char *realm)
{
  char *utf8_spn = NULL;
  TCHAR *tchar_spn = NULL;

  (void) realm;

  /* Note: We could use DsMakeSPN() or DsClientMakeSpnForTargetServer() rather
     than doing this ourselves but the first is only available in Windows XP
     and Windows Server 2003 and the latter is only available in Windows 2000
     but not Windows95/98/ME or Windows NT4.0 unless the Active Directory
     Client Extensions are installed. As such it is far simpler for us to
     formulate the SPN instead. */

  /* Generate our UTF8 based SPN */
  utf8_spn = aprintf("%s/%s", service, host);
  if(!utf8_spn) {
    return NULL;
  }

  /* Allocate our TCHAR based SPN */
  tchar_spn = Curl_convert_UTF8_to_tchar(utf8_spn);
  if(!tchar_spn) {
    free(utf8_spn);

    return NULL;
  }

  /* Release the UTF8 variant when operating with Unicode */
  Curl_unicodefree(utf8_spn);

  /* Return our newly allocated SPN */
  return tchar_spn;
}