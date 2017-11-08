static struct commit_list *get_merge_bases_many_0(struct commit *one,
						  int n,
						  struct commit **twos,
						  int cleanup)
{
	struct commit_list *list;
	struct commit **rslt;
	struct commit_list *result;
	int cnt, i;

	result = merge_bases_many(one, n, twos);
	for (i = 0; i < n; i++) {
		if (one == twos[i])
			return result;
	}
	if (!result || !result->next) {
		if (cleanup) {
			clear_commit_marks(one, all_flags);
			clear_commit_marks_many(n, twos, all_flags);
		}
		return result;
	}

	/* There are more than one */
	cnt = commit_list_count(result);
	rslt = xcalloc(cnt, sizeof(*rslt));
	for (list = result, i = 0; list; list = list->next)
		rslt[i++] = list->item;
	free_commit_list(result);

	clear_commit_marks(one, all_flags);
	clear_commit_marks_many(n, twos, all_flags);

	cnt = remove_redundant(rslt, cnt);
	result = NULL;
	for (i = 0; i < cnt; i++)
		commit_list_insert_by_date(rslt[i], &result);
	free(rslt);
	return result;
}