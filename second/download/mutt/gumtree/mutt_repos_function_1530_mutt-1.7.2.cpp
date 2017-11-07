static void maildir_update_tables (CONTEXT *ctx, int *index_hint)
{
  short old_sort;
  int old_count;
  int i, j;
  
  if (Sort != SORT_ORDER)
  {
    old_sort = Sort;
    Sort = SORT_ORDER;
    mutt_sort_headers (ctx, 1);
    Sort = old_sort;
  }
  
  old_count = ctx->msgcount;
  for (i = 0, j = 0; i < old_count; i++)
  {
    if (ctx->hdrs[i]->active && index_hint && *index_hint == i)
      *index_hint = j;
    
    if (ctx->hdrs[i]->active)
      ctx->hdrs[i]->index = j++;
  }

  mx_update_tables (ctx, 0);
  mutt_clear_threads (ctx);
}