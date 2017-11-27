	
	IP6T_MATCH_ITERATE(e, print_match);

	t = ip6t_get_target(e);
	printf("Target name: `%s' [%u]\n", t->u.user.name, t->u.target_size);
	if (strcmp(t->u.user.name, IP6T_STANDARD_TARGET) == 0) {
		int pos = *(int *)t->data;
		if (pos < 0)
			printf("verdict=%s\n",
			       pos == -NF_ACCEPT-1 ? "NF_ACCEPT"
			       : pos == -NF_DROP-1 ? "NF_DROP"
			       : pos == IP6T_RETURN ? "RETURN"
			       : "UNKNOWN");
