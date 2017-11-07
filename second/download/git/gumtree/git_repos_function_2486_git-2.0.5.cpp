static int ref_update_reject_duplicates(struct ref_update **updates, int n,
					enum action_on_err onerr)
{
	int i;
	for (i = 1; i < n; i++)
		if (!strcmp(updates[i - 1]->ref_name, updates[i]->ref_name)) {
			const char *str =
				"Multiple updates for ref '%s' not allowed.";
			switch (onerr) {
			case MSG_ON_ERR:
				error(str, updates[i]->ref_name); break;
			case DIE_ON_ERR:
				die(str, updates[i]->ref_name); break;
			case QUIET_ON_ERR:
				break;
			}
			return 1;
		}
	return 0;
}