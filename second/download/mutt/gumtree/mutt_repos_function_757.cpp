static void init_common(void)
{
  /* this initialization should only run one time, but it may be called by
   * either pgp_gpgme_init or smime_gpgme_init */
  static bool has_run = 0;
  if (!has_run) {
    gpgme_check_version(NULL);
    gpgme_set_locale (NULL, LC_CTYPE, setlocale (LC_CTYPE, NULL));
#ifdef ENABLE_NLS
    gpgme_set_locale (NULL, LC_MESSAGES, setlocale (LC_MESSAGES, NULL));
#endif
    has_run = 1; /* note use of 1 here is intentional to avoid requiring "true"
		    to be defined.  see #3657 */
  }
}