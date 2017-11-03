static void mh_sort_natural (CONTEXT *ctx, struct maildir **md)
{
  if (!ctx || !md || !*md || ctx->magic != MUTT_MH || Sort != SORT_ORDER)
    return;
  dprint (4, (debugfile, "maildir: sorting %s into natural order\n",
	      ctx->path));
  *md = maildir_sort (*md, (size_t) -1, md_cmp_path);
}