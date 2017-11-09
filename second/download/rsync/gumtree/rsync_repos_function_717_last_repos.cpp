static struct pr_chunk *new_chunk(void) {
	struct pr_chunk *new_c = (struct pr_chunk *)malloc(sizeof(struct pr_chunk));

	if (!new_c)
		return NULL;

	new_c->type = 0;
	new_c->num = 0;
	new_c->min = 0;
	new_c->min_star = NULL;
	new_c->max = -1;
	new_c->max_star = NULL;
	new_c->flags = 0;
	new_c->cflags = 0;
	new_c->start = 0;
	new_c->len = 0;
	new_c->value = 0;
	new_c->fvalue = 0;
	new_c->strvalue = NULL;
	new_c->pnum = NULL;
	new_c->next = NULL;

	return new_c;
}