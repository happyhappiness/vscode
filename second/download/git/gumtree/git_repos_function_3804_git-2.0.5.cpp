static int find_last_in_target(struct scoreboard *sb, struct origin *target)
{
	struct blame_entry *e;
	int last_in_target = -1;

	for (e = sb->ent; e; e = e->next) {
		if (e->guilty || e->suspect != target)
			continue;
		if (last_in_target < e->s_lno + e->num_lines)
			last_in_target = e->s_lno + e->num_lines;
	}
	return last_in_target;
}