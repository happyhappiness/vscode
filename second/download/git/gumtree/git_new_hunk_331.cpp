		long bottom, top;
		if (parse_range_arg(range_list.items[range_i].string,
				    nth_line_cb, &sb, lno, anchor,
				    &bottom, &top, sb.path))
			usage(blame_usage);
		if (lno < top || ((lno || bottom) && lno < bottom))
			die(Q_("file %s has only %lu line",
			       "file %s has only %lu lines",
			       lno), path, lno);
		if (bottom < 1)
			bottom = 1;
		if (top < 1)
			top = lno;
		bottom--;
		range_set_append_unsafe(&ranges, bottom, top);
