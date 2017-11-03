int mutt_messages_in_thread (CONTEXT *ctx, HEADER *hdr, int flag)
{
  THREAD *threads[2];
  int i, rc;

  if ((Sort & SORT_MASK) != SORT_THREADS || !hdr->thread)
    return (1);

  threads[0] = hdr->thread;
  while (threads[0]->parent)
    threads[0] = threads[0]->parent;

  threads[1] = flag ? hdr->thread : threads[0]->next;

  for (i = 0; i < ((flag || !threads[1]) ? 1 : 2); i++)
  {
    while (!threads[i]->message)
      threads[i] = threads[i]->child;
  } 

  if (Sort & SORT_REVERSE)
    rc = threads[0]->message->msgno - (threads[1] ? threads[1]->message->msgno : -1);
  else
    rc = (threads[1] ? threads[1]->message->msgno : ctx->msgcount) - threads[0]->message->msgno;
  
  if (flag)
    rc += 1;
  
  return (rc);
}