void mutt_free_enter_state (ENTER_STATE **esp)
{
  if (!esp) return;
  
  FREE (&(*esp)->wbuf);
  FREE (esp);		/* __FREE_CHECKED__ */
}