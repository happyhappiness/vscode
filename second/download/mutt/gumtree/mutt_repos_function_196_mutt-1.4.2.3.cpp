char *mutt_pgp_hook (ADDRESS *adr)
{
  return _mutt_string_hook (adr->mailbox, M_PGPHOOK);
}