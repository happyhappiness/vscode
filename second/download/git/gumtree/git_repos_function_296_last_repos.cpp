void finish_copy_notes_for_rewrite(struct notes_rewrite_cfg *c, const char *msg)
{
	int i;
	for (i = 0; c->trees[i]; i++) {
		commit_notes(c->trees[i], msg);
		free_notes(c->trees[i]);
	}
	free(c->trees);
	free(c);
}