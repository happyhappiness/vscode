static void count_diff_files(struct diff_queue_struct *q,
			     struct diff_options *opt, void *data)
{
	int *count = data;

	(*count) += q->nr;
}