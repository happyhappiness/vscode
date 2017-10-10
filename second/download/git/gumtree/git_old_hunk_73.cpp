		ent->num_lines = top - bottom;
		ent->suspect = o;
		ent->s_lno = bottom;
		ent->next = next;
		origin_incref(o);
	}
	origin_decref(o);

	range_set_release(&ranges);
	string_list_clear(&range_list, 0);

	sb.ent = ent;
	sb.path = path;

	read_mailmap(&mailmap, NULL);

	if (!incremental)
		setup_pager();

	assign_blame(&sb, opt);

	if (incremental)
		return 0;

	coalesce(&sb);

	if (!(output_option & OUTPUT_PORCELAIN))
		find_alignment(&sb, &output_option);

	output(&sb, output_option);
