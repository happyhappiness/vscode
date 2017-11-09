static void find_merge_parents(struct merge_parents *result,
			       struct strbuf *in, struct object_id *head)
{
	struct commit_list *parents;
	struct commit *head_commit;
	int pos = 0, i, j;

	parents = NULL;
	while (pos < in->len) {
		int len;
		char *p = in->buf + pos;
		char *newline = strchr(p, '\n');
		struct object_id oid;
		struct commit *parent;
		struct object *obj;

		len = newline ? newline - p : strlen(p);
		pos += len + !!newline;

		if (len < GIT_SHA1_HEXSZ + 3 ||
		    get_oid_hex(p, &oid) ||
		    p[GIT_SHA1_HEXSZ] != '\t' ||
		    p[GIT_SHA1_HEXSZ + 1] != '\t')
			continue; /* skip not-for-merge */
		/*
		 * Do not use get_merge_parent() here; we do not have
		 * "name" here and we do not want to contaminate its
		 * util field yet.
		 */
		obj = parse_object(&oid);
		parent = (struct commit *)peel_to_type(NULL, 0, obj, OBJ_COMMIT);
		if (!parent)
			continue;
		commit_list_insert(parent, &parents);
		add_merge_parent(result, &obj->oid, &parent->object.oid);
	}
	head_commit = lookup_commit(head);
	if (head_commit)
		commit_list_insert(head_commit, &parents);
	parents = reduce_heads(parents);

	while (parents) {
		struct commit *cmit = pop_commit(&parents);
		for (i = 0; i < result->nr; i++)
			if (!oidcmp(&result->item[i].commit, &cmit->object.oid))
				result->item[i].used = 1;
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