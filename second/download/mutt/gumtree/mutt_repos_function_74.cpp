void mutt_env_to_local (ENVELOPE *e)
{
  mutt_addrlist_to_local (e->return_path);
  mutt_addrlist_to_local (e->from);
  mutt_addrlist_to_local (e->to);
  mutt_addrlist_to_local (e->cc);
  mutt_addrlist_to_local (e->bcc);
  mutt_addrlist_to_local (e->reply_to);
  mutt_addrlist_to_local (e->mail_followup_to);
}