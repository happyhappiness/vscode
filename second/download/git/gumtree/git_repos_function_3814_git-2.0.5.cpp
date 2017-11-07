static struct blame_list *setup_blame_list(struct scoreboard *sb,
					   struct origin *target,
					   int min_score,
					   int *num_ents_p)
{
	struct blame_entry *e;
	int num_ents, i;
	struct blame_list *blame_list = NULL;

	for (e = sb->ent, num_ents = 0; e; e = e->next)
		if (!e->scanned && !e->guilty &&
		    e->suspect == target &&
		    min_score < ent_score(sb, e))
			num_ents++;
	if (num_ents) {
		blame_list = xcalloc(num_ents, sizeof(struct blame_list));
		for (e = sb->ent, i = 0; e; e = e->next)
			if (!e->scanned && !e->guilty &&
			    e->suspect == target &&
			    min_score < ent_score(sb, e))
				blame_list[i++].ent = e;
	}
	*num_ents_p = num_ents;
	return blame_list;
}