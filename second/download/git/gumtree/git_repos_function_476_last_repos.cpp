static void queue_blames(struct blame_scoreboard *sb, struct blame_origin *porigin,
			 struct blame_entry *sorted)
{
	if (porigin->suspects)
		porigin->suspects = blame_merge(porigin->suspects, sorted);
	else {
		struct blame_origin *o;
		for (o = porigin->commit->util; o; o = o->next) {
			if (o->suspects) {
				porigin->suspects = sorted;
				return;
			}
		}
		porigin->suspects = sorted;
		prio_queue_put(&sb->commits, porigin->commit);
	}
}