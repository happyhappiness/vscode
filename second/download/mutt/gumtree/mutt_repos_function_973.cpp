void mutt_attach_resend (FILE * fp, HEADER * hdr, ATTACHPTR ** idx, 
			 short idxlen, BODY * cur)
{
  short i;

  if (check_all_msg (idx, idxlen, cur, 1) == -1)
    return;

  if (cur)
    mutt_resend_message (fp, Context, cur->hdr);
  else
  {
    for (i = 0; i < idxlen; i++)
      if (idx[i]->content->tagged)
	mutt_resend_message (fp, Context, idx[i]->content->hdr);
  }
}