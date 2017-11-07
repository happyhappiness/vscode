void mutt_free_enter_state (ENTER_STATE **esp)
{
  if (!esp) return;
  
  safe_free ((void **) &(*esp)->wbuf);
  safe_free ((void **) esp);
}