LIST *mutt_crypt_hook (ADDRESS *adr)
{
  return _mutt_list_hook (adr->mailbox, M_CRYPTHOOK);
}