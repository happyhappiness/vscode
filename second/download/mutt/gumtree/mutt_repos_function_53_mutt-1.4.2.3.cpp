int mutt_resend_message (FILE *fp, CONTEXT *ctx, HEADER *cur)
{
  HEADER *msg = mutt_new_header ();
  
  if (mutt_prepare_template (fp, ctx, msg, cur, 1) < 0)
    return -1;
  
  return ci_send_message (SENDRESEND, msg, NULL, ctx, cur);
}