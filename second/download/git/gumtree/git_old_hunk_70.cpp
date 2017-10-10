static void output(struct scoreboard *sb, int option)
{
	struct blame_entry *ent;

	if (option & OUTPUT_PORCELAIN) {
		for (ent = sb->ent; ent; ent = ent->next) {
			struct blame_entry *oth;
			struct origin *suspect = ent->suspect;
			struct commit *commit = suspect->commit;
			if (commit->object.flags & MORE_THAN_ONE_PATH)
				continue;
			for (oth = ent->next; oth; oth = oth->next) {
				if ((oth->suspect->commit != commit) ||
				    !strcmp(oth->suspect->path, suspect->path))
					continue;
				commit->object.flags |= MORE_THAN_ONE_PATH;
				break;
			}
		}
	}

	for (ent = sb->ent; ent; ent = ent->next) {
		if (option & OUTPUT_PORCELAIN)
