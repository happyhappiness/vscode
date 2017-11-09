void mutt_attach_resend (FILE * fp, HEADER * hdr, ATTACH_CONTEXT *actx,
			 BODY * cur)
{
  short i;

  if (check_all_msg (actx, cur, 1) == -1)
    return;

  if (cur)
    mutt_resend_message (fp, Context, cur->hdr);
  else
  {
    for (i = 0; i < actx->idxlen; i++)
      if (actx->idx[i]->content->tagged)
	mutt_resend_message (actx->idx[i]->fp, Context, actx->idx[i]->content->hdr);
  }
}