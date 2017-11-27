static void print_recipient_status (smtp_recipient_t recipient,
    const char *mailbox, void *arg)
{
  const smtp_status_t *status;

  status = smtp_recipient_status (recipient);
  if (status->text[strlen(status->text) - 2] == '\r')
    status->text[strlen(status->text) - 2] = 0;
  INFO ("notify_email: notify sent to %s: %d %s", mailbox, status->code,
      status->text);
}