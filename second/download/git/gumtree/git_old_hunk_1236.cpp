		anchor = top + 1;
	}
	sort_and_merge_range_set(&ranges);

	for (range_i = ranges.nr; range_i > 0; --range_i) {
		const struct range *r = &ranges.ranges[range_i - 1];
		long bottom = r->start;
		long top = r->end;
		struct blame_entry *next = ent;
		ent = xcalloc(1, sizeof(*ent));
		ent->lno = bottom;
		ent->num_lines = top - bottom;
		ent->suspect = o;
		ent->s_lno = bottom;
		ent->next = next;
		origin_incref(o);
	}

	o->suspects = ent;
	prio_queue_put(&sb.commits, o->commit);

	origin_decref(o);

	range_set_release(&ranges);
	string_list_clear(&range_list, 0);

	sb.ent = NULL;
	sb.path = path;

	read_mailmap(&mailmap, NULL);

	assign_blame(&sb, opt);

	if (!incremental)
		setup_pager();

	free(final_commit_name);

	if (incremental)
		return 0;

	sb.ent = blame_sort(sb.ent, compare_blame_final);

	coalesce(&sb);

	if (!(output_option & OUTPUT_PORCELAIN))
		find_alignment(&sb, &output_option);

	output(&sb, output_option);
	free((void *)sb.final_buf);
