void mutt_check_rescore (CONTEXT *ctx)
{
  int i;

  if (option (OPTNEEDRESCORE) && option (OPTSCORE))
  {
    if ((Sort & SORT_MASK) == SORT_SCORE ||
	(SortAux & SORT_MASK) == SORT_SCORE)
    {
      set_option (OPTNEEDRESORT);
      if ((Sort & SORT_MASK) == SORT_THREADS)
	set_option (OPTSORTSUBTHREADS);
    }

    /* must redraw the index since the user might have %N in it */
    set_option (OPTFORCEREDRAWINDEX);
    set_option (OPTFORCEREDRAWPAGER);

    for (i = 0; ctx && i < ctx->msgcount; i++)
    {
      mutt_score_message (ctx, ctx->hdrs[i], 1);
      ctx->hdrs[i]->pair = 0;
    }
  }
  unset_option (OPTNEEDRESCORE);
}