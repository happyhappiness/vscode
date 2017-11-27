static int
iptcc_standard_map(struct rule_head *r, int verdict)
{
	STRUCT_ENTRY *e = r->entry;
	STRUCT_STANDARD_TARGET *t;

	t = (STRUCT_STANDARD_TARGET *)GET_TARGET(e);

	if (t->target.u.target_size
	    != ALIGN(sizeof(STRUCT_STANDARD_TARGET))) {
		errno = EINVAL;
		return 0;
	}
	/* memset for memcmp convenience on delete/replace */
	memset(t->target.u.user.name, 0, FUNCTION_MAXNAMELEN);
	strcpy(t->target.u.user.name, STANDARD_TARGET);
	t->verdict = verdict;

	r->type = IPTCC_R_STANDARD;

	return 1;
}