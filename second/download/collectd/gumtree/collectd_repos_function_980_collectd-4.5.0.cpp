static void iptcc_delete_rule(struct rule_head *r)
{
	DEBUGP("deleting rule %p (offset %u)\n", r, r->offset);
	/* clean up reference count of called chain */
	if (r->type == IPTCC_R_JUMP
	    && r->jump)
		r->jump->references--;

	list_del(&r->list);
	free(r);
}