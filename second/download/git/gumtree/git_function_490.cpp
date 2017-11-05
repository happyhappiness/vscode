struct commit_list *get_shallow_commits_by_rev_list(int ac, const char **av,
						    int shallow_flag,
						    int not_shallow_flag)
{
	struct commit_list *result = NULL, *p;
	struct commit_list *not_shallow_list = NULL;
	struct rev_info revs;
	int both_flags = shallow_flag | not_shallow_flag;

	/*
	 * SHALLOW (excluded) and NOT_SHALLOW (included) should not be
	 * set at this point. But better be safe than sorry.
	 */
	clear_object_flags(both_flags);

	is_repository_shallow(); /* make sure shallows are read */

	init_revisions(&revs, NULL);
	save_commit_buffer = 0;
	setup_revisions(ac, av, &revs, NULL);

	if (prepare_revision_walk(&revs))
		die("revision walk setup failed");
	traverse_commit_list(&revs, show_commit, NULL, &not_shallow_list);

	/* Mark all reachable commits as NOT_SHALLOW */
	for (p = not_shallow_list; p; p = p->next)
		p->item->object.flags |= not_shallow_flag;

	/*
	 * mark border commits SHALLOW + NOT_SHALLOW.
	 * We cannot clear NOT_SHALLOW right now. Imagine border
	 * commit A is processed first, then commit B, whose parent is
	 * A, later. If NOT_SHALLOW on A is cleared at step 1, B
	 * itself is considered border at step 2, which is incorrect.
	 */
	for (p = not_shallow_list; p; p = p->next) {
		struct commit *c = p->item;
		struct commit_list *parent;

		if (parse_commit(c))
			die("unable to parse commit %s",
			    oid_to_hex(&c->object.oid));

		for (parent = c->parents; parent; parent = parent->next)
			if (!(parent->item->object.flags & not_shallow_flag)) {
				c->object.flags |= shallow_flag;
				commit_list_insert(c, &result);
				break;
			}
	}
	free_commit_list(not_shallow_list);

	/*
	 * Now we can clean up NOT_SHALLOW on border commits. Having
	 * both flags set can confuse the caller.
	 */
	for (p = result; p; p = p->next) {
		struct object *o = &p->item->object;
		if ((o->flags & both_flags) == both_flags)
			o->flags &= ~not_shallow_flag;
	}
	return result;
}