static void blame_chunk(struct scoreboard *sb,
			int tlno, int plno, int same,
			struct origin *target, struct origin *parent)
{
	struct blame_entry *e;

	for (e = sb->ent; e; e = e->next) {
		if (e->guilty || e->suspect != target)
			continue;
		if (same <= e->s_lno)
			continue;
		if (tlno < e->s_lno + e->num_lines)
			blame_overlap(sb, e, tlno, plno, same, parent);
	}
}