static inline int diff_might_be_rename(void)
{
	int i;
	for (i = 0; i < diff_queued_diff.nr; i++)
		if (!DIFF_FILE_VALID(diff_queued_diff.queue[i]->one)) {
			/* fprintf(stderr, "diff_might_be_rename found creation of: %s\n", */
			/* 	diff_queued_diff.queue[i]->two->path); */
			return 1;
		}
	return 0;
}