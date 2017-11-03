static void set_intl_mailbox (ADDRESS *a, char *intl_mailbox)
{
  FREE (&a->mailbox);
  a->mailbox = intl_mailbox;
  a->intl_checked = 1;
  a->is_intl = 1;
}