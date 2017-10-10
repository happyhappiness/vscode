		num = e->s_lno + e->num_lines;
		if (longest_src_lines < num)
			longest_src_lines = num;
		num = e->lno + e->num_lines;
		if (longest_dst_lines < num)
			longest_dst_lines = num;
		if (largest_score < blame_entry_score(sb, e))
			largest_score = blame_entry_score(sb, e);
	}
	max_orig_digits = decimal_width(longest_src_lines);
	max_digits = decimal_width(longest_dst_lines);
	max_score_digits = decimal_width(largest_score);

	if (compute_auto_abbrev)
		/* one more abbrev length is needed for the boundary commit */
		abbrev = auto_abbrev + 1;
}

static void sanity_check_on_fail(struct blame_scoreboard *sb, int baa)
{
	int opt = OUTPUT_SHOW_SCORE | OUTPUT_SHOW_NUMBER | OUTPUT_SHOW_NAME;
	find_alignment(sb, &opt);
	output(sb, opt);
	die("Baa %d!", baa);
}

static unsigned parse_score(const char *arg)
{
	char *end;
	unsigned long score = strtoul(arg, &end, 10);
