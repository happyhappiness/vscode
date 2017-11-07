static int find_move_in_parent(struct scoreboard *sb,
			       struct origin *target,
			       struct origin *parent)
{
	int last_in_target, made_progress;
	struct blame_entry *e, split[3];
	mmfile_t file_p;

	last_in_target = find_last_in_target(sb, target);
	if (last_in_target < 0)
		return 1; /* nothing remains for this target */

	fill_origin_blob(&sb->revs->diffopt, parent, &file_p);
	if (!file_p.ptr)
		return 0;

	made_progress = 1;
	while (made_progress) {
		made_progress = 0;
		for (e = sb->ent; e; e = e->next) {
			if (e->guilty || e->suspect != target ||
			    ent_score(sb, e) < blame_move_score)
				continue;
			find_copy_in_blob(sb, e, parent, split, &file_p);
			if (split[1].suspect &&
			    blame_move_score < ent_score(sb, &split[1])) {
				split_blame(sb, split, e);
				made_progress = 1;
			}
			decref_split(split);
		}
	}
	return 0;
}