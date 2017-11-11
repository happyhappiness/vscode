static void append_lost(struct sline *sline, int n, const char *line, int len)
{
	struct lline *lline;
	unsigned long this_mask = (1UL<<n);
	if (line[len-1] == '\n')
		len--;

	FLEX_ALLOC_MEM(lline, line, line, len);
	lline->len = len;
	lline->next = NULL;
	lline->prev = sline->plost.lost_tail;
	if (lline->prev)
		lline->prev->next = lline;
	else
		sline->plost.lost_head = lline;
	sline->plost.lost_tail = lline;
	sline->plost.len++;
	lline->parent_map = this_mask;
}