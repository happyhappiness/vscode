static void set_local_mailbox (ADDRESS *a, char *local_mailbox)
{
  FREE (&a->mailbox);
  a->mailbox = local_mailbox;
  a->intl_checked = 1;
  a->is_intl = 0;
}