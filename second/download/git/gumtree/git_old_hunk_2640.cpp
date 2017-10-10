			unlock_ref(updates[i]->lock);
	string_list_clear(&refs_to_delete, 0);
	string_list_clear(&affected_refnames, 0);
	return ret;
}

char *shorten_unambiguous_ref(const char *refname, int strict)
{
	int i;
	static char **scanf_fmts;
	static int nr_rules;
	char *short_name;
