static void find_merge_parents(struct merge_parents *result,
			       struct strbuf *in, unsigned char *head)
{
	struct commit_list *parents, *next;
	struct commit *head_commit;
	int pos = 0, i, j;

	parents = NULL;
	while (pos < in->len) {
		int len;
		char *p = in->buf + pos;
		char *newline = strchr(p, '\n');
		unsigned char sha1[20];
		struct commit *parent;
		struct object *obj;

		len = newline ? newline - p : strlen(p);
		pos += len + !!newline;

		if (len < 43 ||
		    get_sha1_hex(p, sha1) ||
		    p[40] != '\t' ||
		    p[41] != '\t')
			continue; /* skip not-for-merge */
		/*
		 * Do not use get_merge_parent() here; we do not have
		 * "name" here and we do not want to contaminate its
		 * util field yet.
		 */
		obj = parse_object(sha1);
		parent = (struct commit *)peel_to_type(NULL, 0, obj, OBJ_COMMIT);
		if (!parent)
			continue;
		commit_list_insert(parent, &parents);
		add_merge_parent(result, obj->sha1, parent->object.sha1);
	}
	head_commit = lookup_commit(head);
	if (head_commit)
		commit_list_insert(head_commit, &parents);
	parents = reduce_heads(parents);

	while (parents) {
		for (i = 0; i < result->nr; i++)
			if (!hashcmp(result->item[i].commit,
				     parents->item->object.sha1))
				result->item[i].used = 1;
		next = parents->next;
		free(parents);
		parents = next;
	}

	for (i = j = 0; i < result->nr; i++) {
		if (result->item[i].used) {
			if (i != j)
				result->item[j] = result->item[i];
			j++;
		}
	}
	result->nr = j;
}