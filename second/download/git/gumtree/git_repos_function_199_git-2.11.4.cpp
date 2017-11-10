static struct combine_diff_path *intersect_paths(struct combine_diff_path *curr, int n, int num_parent)
{
	struct diff_queue_struct *q = &diff_queued_diff;
	struct combine_diff_path *p, **tail = &curr;
	int i, cmp;

	if (!n) {
		for (i = 0; i < q->nr; i++) {
			int len;
			const char *path;
			if (diff_unmodified_pair(q->queue[i]))
				continue;
			path = q->queue[i]->two->path;
			len = strlen(path);
			p = xmalloc(combine_diff_path_size(num_parent, len));
			p->path = (char *) &(p->parent[num_parent]);
			memcpy(p->path, path, len);
			p->path[len] = 0;
			p->next = NULL;
			memset(p->parent, 0,
			       sizeof(p->parent[0]) * num_parent);

			oidcpy(&p->oid, &q->queue[i]->two->oid);
			p->mode = q->queue[i]->two->mode;
			oidcpy(&p->parent[n].oid, &q->queue[i]->one->oid);
			p->parent[n].mode = q->queue[i]->one->mode;
			p->parent[n].status = q->queue[i]->status;
			*tail = p;
			tail = &p->next;
		}
		return curr;
	}

	/*
	 * paths in curr (linked list) and q->queue[] (array) are
	 * both sorted in the tree order.
	 */
	i = 0;
	while ((p = *tail) != NULL) {
		cmp = ((i >= q->nr)
		       ? -1 : compare_paths(p, q->queue[i]->two));

		if (cmp < 0) {
			/* p->path not in q->queue[]; drop it */
			*tail = p->next;
			free(p);
			continue;
		}

		if (cmp > 0) {
			/* q->queue[i] not in p->path; skip it */
			i++;
			continue;
		}

		oidcpy(&p->parent[n].oid, &q->queue[i]->one->oid);
		p->parent[n].mode = q->queue[i]->one->mode;
		p->parent[n].status = q->queue[i]->status;

		tail = &p->next;
		i++;
	}
	return curr;
}