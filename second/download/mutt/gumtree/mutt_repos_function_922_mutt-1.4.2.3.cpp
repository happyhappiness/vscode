void mutt_free_header (HEADER **h)
{
  if(!h || !*h) return;
  mutt_free_envelope (&(*h)->env);
  mutt_free_body (&(*h)->content);
  safe_free ((void **) &(*h)->tree);
  safe_free ((void **) &(*h)->path);
#ifdef MIXMASTER
  mutt_free_list (&(*h)->chain);
#endif
#if defined USE_POP || defined USE_IMAP
  safe_free ((void**) &(*h)->data);
#endif
  safe_free ((void **) h);
}