static void sanity_check_refcnt(struct scoreboard *sb)
{
	int baa = 0;
	struct blame_entry *ent;

	for (ent = sb->ent; ent; ent = ent->next) {
		/* Nobody should have zero or negative refcnt */
		if (ent->suspect->refcnt <= 0) {
			fprintf(stderr, "%s in %s has negative refcnt %d\n",
				ent->suspect->path,
				sha1_to_hex(ent->suspect->commit->object.sha1),
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