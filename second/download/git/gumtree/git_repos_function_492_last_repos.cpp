static void handle_split(struct blame_scoreboard *sb,
			 struct blame_entry *ent,
			 int tlno, int plno, int same,
			 struct blame_origin *parent,
			 struct blame_entry *split)
{
	if (ent->num_lines <= tlno)
		return;
	if (tlno < same) {
		struct blame_entry this[3];
		tlno += ent->s_lno;
		same += ent->s_lno;
		split_overlap(this, ent, tlno, plno, same, parent);
		copy_split_if_better(sb, split, this);
		decref_split(this);
	}
}