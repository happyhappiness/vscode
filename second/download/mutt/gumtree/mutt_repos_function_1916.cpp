static void cmd_parse_expunge (IMAP_DATA* idata, const char* s)
{
  int expno, cur;
  HEADER* h;

  dprint (2, (debugfile, "Handling EXPUNGE\n"));

  expno = atoi (s);

  /* walk headers, zero seqno of expunged message, decrement seqno of those
   * above. Possibly we could avoid walking the whole list by resorting
   * and guessing a good starting point, but I'm guessing the resort would
   * nullify the gains */
  for (cur = 0; cur < idata->ctx->msgcount; cur++)
  {
    h = idata->ctx->hdrs[cur];

    if (h->index+1 == expno)
      h->index = -1;
    else if (h->index+1 > expno)
      h->index--;
  }

  idata->reopen |= IMAP_EXPUNGE_PENDING;
}