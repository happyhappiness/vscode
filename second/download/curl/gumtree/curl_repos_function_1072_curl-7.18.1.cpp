int Curl_gtls_init(void)
{
/* Unfortunately we can not init here, things like curl --version will
 * fail to work if there is no egd socket available because libgcrypt
 * will EXIT the application!!
 * By doing the actual init later (before actually trying to use GnuTLS),
 * we can at least provide basic info etc.
 */
  return 1;
}