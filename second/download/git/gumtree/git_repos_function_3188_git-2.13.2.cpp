static void free_diffqueues(int n, struct diff_queue_struct *dq)
{
	int i, j;
	for (i = 0; i < n; i++)
		for (j = 0; j < dq[i].nr; j++)
			diff_free_filepair(dq[i].queue[j]);
	free(dq);
}