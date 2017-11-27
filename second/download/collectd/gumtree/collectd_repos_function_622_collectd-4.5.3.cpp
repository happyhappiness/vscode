static void monitor_cb (const char *buf, int buflen, int writing, void *arg)
{
  char log_str[MAXSTRING];

  sstrncpy (log_str, buf, sizeof (log_str));
  if (buflen > 2)
    log_str[buflen - 2] = 0; /* replace \n with \0 */

  if (writing == SMTP_CB_HEADERS) {
    DEBUG ("notify_email plugin: SMTP --- H: %s", log_str);
    return;
  }
  DEBUG (writing
      ? "notify_email plugin: SMTP >>> C: %s"
      : "notify_email plugin: SMTP <<< S: %s",
      log_str);
}