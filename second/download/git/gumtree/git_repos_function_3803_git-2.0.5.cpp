static void blame_overlap(struct scoreboard *sb, struct blame_entry *e,
			  int tlno, int plno, int same,
			  struct origin *parent)
{
	struct blame_entry split[3];

	split_overlap(split, e, tlno, plno, same, parent);
	if (split[1].suspect)
		split_blame(sb, split, e);
	decref_split(split);
}