void mutt_free_header (HEADER **h)
{
  if(!h || !*h) return;
  mutt_free_envelope (&(*h)->env);
  mutt_free_body (&(*h)->content);
  FREE (&(*h)->maildir_flags);
  FREE (&(*h)->tree);
  FREE (&(*h)->path);
#ifdef MIXMASTER
  mutt_free_list (&(*h)->chain);
#endif
#if defined USE_POP || defined USE_IMAP
  FREE (&(*h)->data);
#endif
  FREE (h);		/* __FREE_CHECKED__ */
}