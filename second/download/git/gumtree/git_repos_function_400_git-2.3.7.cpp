static void record_rename_pair(int dst_index, int src_index, int score)
{
	struct diff_filespec *src, *dst;
	struct diff_filepair *dp;

	if (rename_dst[dst_index].pair)
		die("internal error: dst already matched.");

	src = rename_src[src_index].p->one;
	src->rename_used++;
	src->count++;

	dst = rename_dst[dst_index].two;
	dst->count++;

	dp = diff_queue(NULL, src, dst);
	dp->renamed_pair = 1;
	if (!strcmp(src->path, dst->path))
		dp->score = rename_src[src_index].score;
	else
		dp->score = score;
	rename_dst[dst_index].pair = dp;
}