static struct rule_head *iptcc_alloc_rule(struct chain_head *c, unsigned int size)
{
	struct rule_head *r = malloc(sizeof(*r)+size);
	if (!r)
		return NULL;
	memset(r, 0, sizeof(*r));

	r->chain = c;
	r->size = size;

	return r;
}