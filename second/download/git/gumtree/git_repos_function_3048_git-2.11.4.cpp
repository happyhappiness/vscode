static struct diff_filepair *diff_filepair_dup(struct diff_filepair *pair)
{
	struct diff_filepair *new = xmalloc(sizeof(struct diff_filepair));
	new->one = pair->one;
	new->two = pair->two;
	new->one->count++;
	new->two->count++;
	return new;
}