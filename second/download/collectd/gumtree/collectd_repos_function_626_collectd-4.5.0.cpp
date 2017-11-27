static int notify_email_notification (const notification_t *n)
{
  smtp_recipient_t recipient;

  struct tm timestamp_tm;
  char timestamp_str[64];

  char severity[32];
  char subject[MAXSTRING];

  char buf[4096] = "";
  int  buf_len = sizeof (buf);
  int i;

  ssnprintf (severity, sizeof (severity), "%s",
      (n->severity == NOTIF_FAILURE) ? "FAILURE"
      : ((n->severity == NOTIF_WARNING) ? "WARNING"
        : ((n->severity == NOTIF_OKAY) ? "OKAY" : "UNKNOWN")));

  ssnprintf (subject, sizeof (subject),
      (email_subject == NULL) ? DEFAULT_SMTP_SUBJECT : email_subject,
      severity, n->host);

  localtime_r (&n->time, &timestamp_tm);
  strftime (timestamp_str, sizeof (timestamp_str), "%Y-%m-%d %H:%M:%S",
      &timestamp_tm);
  timestamp_str[sizeof (timestamp_str) - 1] = '\0';

  /* Let's make RFC822 message text with \r\n EOLs */
  ssnprintf (buf, buf_len,
      "MIME-Version: 1.0\r\n"
      "Content-Type: text/plain;\r\n"
      "Content-Transfer-Encoding: 8bit\r\n"
      "Subject: %s\r\n"
      "\r\n"
      "%s - %s@%s\r\n"
      "\r\n"
      "Message: %s",
      subject,
      timestamp_str,
      severity,
      n->host,
      n->message);

  if (!(message = smtp_add_message (session))) {
    ERROR ("notify_email plugin: cannot set SMTP message");
    return (-1);   
  }
  smtp_set_reverse_path (message, email_from);
  smtp_set_header (message, "To", NULL, NULL);
  smtp_set_message_str (message, buf);

  for (i = 0; i < recipients_len; i++)
    recipient = smtp_add_recipient (message, recipients[i]);

  /* Initiate a connection to the SMTP server and transfer the message. */
  if (!smtp_start_session (session)) {
    char buf[MAXSTRING];
    ERROR ("notify_email plugin: SMTP server problem: %s",
        smtp_strerror (smtp_errno (), buf, sizeof buf));
    return (-1);
  } else {
    const smtp_status_t *status;
    /* Report on the success or otherwise of the mail transfer. */
    status = smtp_message_transfer_status (message);
    DEBUG ("notify_email plugin: SMTP server report: %d %s",
        status->code, (status->text != NULL) ? status->text : "\n");
    smtp_enumerate_recipients (message, print_recipient_status, NULL);
  }

  return (0);
}