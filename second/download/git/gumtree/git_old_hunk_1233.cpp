		num = e->s_lno + e->num_lines;
		if (longest_src_lines < num)
			longest_src_lines = num;
		num = e->lno + e->num_lines;
		if (longest_dst_lines < num)
			longest_dst_lines = num;
		if (largest_score < ent_score(sb, e))
			largest_score = ent_score(sb, e);
	}
	max_orig_digits = decimal_width(longest_src_lines);
	max_digits = decimal_width(longest_dst_lines);
	max_score_digits = decimal_width(largest_score);

	if (compute_auto_abbrev)
		/* one more abbrev length is needed for the boundary commit */
		abbrev = auto_abbrev + 1;
}

/*
 * For debugging -- origin is refcounted, and this asserts that
 * we do not underflow.
 */
static void sanity_check_refcnt(struct scoreboard *sb)
{
	int baa = 0;
	struct blame_entry *ent;

	for (ent = sb->ent; ent; ent = ent->next) {
		/* Nobody should have zero or negative refcnt */
		if (ent->suspect->refcnt <= 0) {
			fprintf(stderr, "%s in %s has negative refcnt %d\n",
				ent->suspect->path,
				oid_to_hex(&ent->suspect->commit->object.oid),
				ent->suspect->refcnt);
			baa = 1;
		}
	}
	if (baa) {
		int opt = 0160;
		find_alignment(sb, &opt);
		output(sb, opt);
		die("Baa %d!", baa);
	}
}

static unsigned parse_score(const char *arg)
{
	char *end;
	unsigned long score = strtoul(arg, &end, 10);
