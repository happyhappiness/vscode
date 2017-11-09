static void describe(const char *arg, int last_one)
{
	struct object_id oid;
	struct commit *cmit, *gave_up_on = NULL;
	struct commit_list *list;
	struct commit_name *n;
	struct possible_tag all_matches[MAX_TAGS];
	unsigned int match_cnt = 0, annotated_cnt = 0, cur_match;
	unsigned long seen_commits = 0;
	unsigned int unannotated_cnt = 0;

	if (get_oid(arg, &oid))
		die(_("Not a valid object name %s"), arg);
	cmit = lookup_commit_reference(&oid);
	if (!cmit)
		die(_("%s is not a valid '%s' object"), arg, commit_type);

	n = find_commit_name(&cmit->object.oid);
	if (n && (tags || all || n->prio == 2)) {
		/*
		 * Exact match to an existing ref.
		 */
		display_name(n);
		if (longformat)
			show_suffix(0, n->tag ? &n->tag->tagged->oid : &oid);
		if (suffix)
			printf("%s", suffix);
		printf("\n");
		return;
	}

	if (!max_candidates)
		die(_("no tag exactly matches '%s'"), oid_to_hex(&cmit->object.oid));
	if (debug)
		fprintf(stderr, _("searching to describe %s\n"), arg);

	if (!have_util) {
		struct hashmap_iter iter;
		struct commit *c;
		struct commit_name *n = hashmap_iter_first(&names, &iter);
		for (; n; n = hashmap_iter_next(&iter)) {
			c = lookup_commit_reference_gently(&n->peeled, 1);
			if (c)
				c->util = n;
		}
		have_util = 1;
	}

	list = NULL;
	cmit->object.flags = SEEN;
	commit_list_insert(cmit, &list);
	while (list) {
		struct commit *c = pop_commit(&list);
		struct commit_list *parents = c->parents;
		seen_commits++;
		n = c->util;
		if (n) {
			if (!tags && !all && n->prio < 2) {
				unannotated_cnt++;
			} else if (match_cnt < max_candidates) {
				struct possible_tag *t = &all_matches[match_cnt++];
				t->name = n;
				t->depth = seen_commits - 1;
				t->flag_within = 1u << match_cnt;
				t->found_order = match_cnt;
				c->object.flags |= t->flag_within;
				if (n->prio == 2)
					annotated_cnt++;
			}
			else {
				gave_up_on = c;
				break;
			}
		}
		for (cur_match = 0; cur_match < match_cnt; cur_match++) {
			struct possible_tag *t = &all_matches[cur_match];
			if (!(c->object.flags & t->flag_within))
				t->depth++;
		}
		if (annotated_cnt && !list) {
			if (debug)
				fprintf(stderr, _("finished search at %s\n"),
					oid_to_hex(&c->object.oid));
			break;
		}
		while (parents) {
			struct commit *p = parents->item;
			parse_commit(p);
			if (!(p->object.flags & SEEN))
				commit_list_insert_by_date(p, &list);
			p->object.flags |= c->object.flags;
			parents = parents->next;

			if (first_parent)
				break;
		}
	}

	if (!match_cnt) {
		struct object_id *oid = &cmit->object.oid;
		if (always) {
			printf("%s", find_unique_abbrev(oid->hash, abbrev));
			if (suffix)
				printf("%s", suffix);
			printf("\n");
			return;
		}
		if (unannotated_cnt)
			die(_("No annotated tags can describe '%s'.\n"
			    "However, there were unannotated tags: try --tags."),
			    oid_to_hex(oid));
		else
			die(_("No tags can describe '%s'.\n"
			    "Try --always, or create some tags."),
			    oid_to_hex(oid));
	}

	QSORT(all_matches, match_cnt, compare_pt);

	if (gave_up_on) {
		commit_list_insert_by_date(gave_up_on, &list);
		seen_commits--;
	}
	seen_commits += finish_depth_computation(&list, &all_matches[0]);
	free_commit_list(list);

	if (debug) {
		static int label_width = -1;
		if (label_width < 0) {
			int i, w;
			for (i = 0; i < ARRAY_SIZE(prio_names); i++) {
				w = strlen(_(prio_names[i]));
				if (label_width < w)
					label_width = w;
			}
		}
		for (cur_match = 0; cur_match < match_cnt; cur_match++) {
			struct possible_tag *t = &all_matches[cur_match];
			fprintf(stderr, " %-*s %8d %s\n",
				label_width, _(prio_names[t->name->prio]),
				t->depth, t->name->path);
		}
		fprintf(stderr, _("traversed %lu commits\n"), seen_commits);
		if (gave_up_on) {
			fprintf(stderr,
				_("more than %i tags found; listed %i most recent\n"
				"gave up search at %s\n"),
				max_candidates, max_candidates,
				oid_to_hex(&gave_up_on->object.oid));
		}
	}

	display_name(all_matches[0].name);
	if (abbrev)
		show_suffix(all_matches[0].depth, &cmit->object.oid);
	if (suffix)
		printf("%s", suffix);
	printf("\n");

	if (!last_one)
		clear_commit_marks(cmit, -1);
}