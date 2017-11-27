const char *TC_GET_TARGET(const STRUCT_ENTRY *ce,
			  TC_HANDLE_T *handle)
{
	STRUCT_ENTRY *e = (STRUCT_ENTRY *)ce;
	struct rule_head *r = container_of(e, struct rule_head, entry[0]);

	iptc_fn = TC_GET_TARGET;

	switch(r->type) {
		int spos;
		case IPTCC_R_FALLTHROUGH:
			return "";
			break;
		case IPTCC_R_JUMP:
			DEBUGP("r=%p, jump=%p, name=`%s'\n", r, r->jump, r->jump->name);
			return r->jump->name;
			break;
		case IPTCC_R_STANDARD:
			spos = *(int *)GET_TARGET(e)->data;
			DEBUGP("r=%p, spos=%d'\n", r, spos);
			return standard_target_map(spos);
			break;
		case IPTCC_R_MODULE:
			return GET_TARGET(e)->u.user.name;
			break;
	}
	return NULL;
}