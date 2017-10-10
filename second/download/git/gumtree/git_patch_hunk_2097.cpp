 	char *mark = get_revision_mark(revs, commit);
 	if (!strlen(mark))
 		return;
 	fputs(mark, stdout);
 	putchar(' ');
 }
-
-define_commit_slab(saved_parents, struct commit_list *);
-
-#define EMPTY_PARENT_LIST ((struct commit_list *)-1)
-
-void save_parents(struct rev_info *revs, struct commit *commit)
-{
-	struct commit_list **pp;
-
-	if (!revs->saved_parents_slab) {
-		revs->saved_parents_slab = xmalloc(sizeof(struct saved_parents));
-		init_saved_parents(revs->saved_parents_slab);
-	}
-
-	pp = saved_parents_at(revs->saved_parents_slab, commit);
-
-	/*
-	 * When walking with reflogs, we may visit the same commit
-	 * several times: once for each appearance in the reflog.
-	 *
-	 * In this case, save_parents() will be called multiple times.
-	 * We want to keep only the first set of parents.  We need to
-	 * store a sentinel value for an empty (i.e., NULL) parent
-	 * list to distinguish it from a not-yet-saved list, however.
-	 */
-	if (*pp)
-		return;
-	if (commit->parents)
-		*pp = copy_commit_list(commit->parents);
-	else
-		*pp = EMPTY_PARENT_LIST;
-}
-
-struct commit_list *get_saved_parents(struct rev_info *revs, const struct commit *commit)
-{
-	struct commit_list *parents;
-
-	if (!revs->saved_parents_slab)
-		return commit->parents;
-
-	parents = *saved_parents_at(revs->saved_parents_slab, commit);
-	if (parents == EMPTY_PARENT_LIST)
-		return NULL;
-	return parents;
-}
-
-void free_saved_parents(struct rev_info *revs)
-{
-	if (revs->saved_parents_slab)
-		clear_saved_parents(revs->saved_parents_slab);
-}
