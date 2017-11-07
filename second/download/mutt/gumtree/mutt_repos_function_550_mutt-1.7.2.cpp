void mutt_score_message (CONTEXT *ctx, HEADER *hdr, int upd_ctx)
{
  SCORE *tmp;

  hdr->score = 0; /* in case of re-scoring */
  for (tmp = Score; tmp; tmp = tmp->next)
  {
    if (mutt_pattern_exec (tmp->pat, 0, NULL, hdr) > 0)
    {
      if (tmp->exact || tmp->val == 9999 || tmp->val == -9999)
      {
	hdr->score = tmp->val;
	break;
      }
      hdr->score += tmp->val;
    }
  }
  if (hdr->score < 0)
    hdr->score = 0;
  
  if (hdr->score <= ScoreThresholdDelete)
    _mutt_set_flag (ctx, hdr, MUTT_DELETE, 1, upd_ctx);
  if (hdr->score <= ScoreThresholdRead)
    _mutt_set_flag (ctx, hdr, MUTT_READ, 1, upd_ctx);
  if (hdr->score >= ScoreThresholdFlag)
    _mutt_set_flag (ctx, hdr, MUTT_FLAG, 1, upd_ctx);
}