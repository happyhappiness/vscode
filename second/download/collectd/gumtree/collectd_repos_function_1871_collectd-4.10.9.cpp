static int
iptcc_map_target(const TC_HANDLE_T handle,
	   struct rule_head *r)
{
	STRUCT_ENTRY *e = r->entry;
	STRUCT_ENTRY_TARGET *t = GET_TARGET(e);

	/* Maybe it's empty (=> fall through) */
	if (strcmp(t->u.user.name, "") == 0) {
		r->type = IPTCC_R_FALLTHROUGH;
		return 1;
	}
	/* Maybe it's a standard target name... */
	else if (strcmp(t->u.user.name, LABEL_ACCEPT) == 0)
		return iptcc_standard_map(r, -NF_ACCEPT - 1);
	else if (strcmp(t->u.user.name, LABEL_DROP) == 0)
		return iptcc_standard_map(r, -NF_DROP - 1);
	else if (strcmp(t->u.user.name, LABEL_QUEUE) == 0)
		return iptcc_standard_map(r, -NF_QUEUE - 1);
	else if (strcmp(t->u.user.name, LABEL_RETURN) == 0)
		return iptcc_standard_map(r, RETURN);
	else if (TC_BUILTIN(t->u.user.name, handle)) {
		/* Can't jump to builtins. */
		errno = EINVAL;
		return 0;
	} else {
		/* Maybe it's an existing chain name. */
		struct chain_head *c;
		DEBUGP("trying to find chain `%s': ", t->u.user.name);

		c = iptcc_find_label(t->u.user.name, handle);
		if (c) {
			DEBUGP_C("found!\n");
			r->type = IPTCC_R_JUMP;
			r->jump = c;
			c->references++;
			return 1;
		}
		DEBUGP_C("not found :(\n");
	}

	/* Must be a module?  If not, kernel will reject... */
	/* memset to all 0 for your memcmp convenience: don't clear version */
	memset(t->u.user.name + strlen(t->u.user.name),
	       0,
	       FUNCTION_MAXNAMELEN - 1 - strlen(t->u.user.name));
	r->type = IPTCC_R_MODULE;
	set_changed(handle);
	return 1;
}