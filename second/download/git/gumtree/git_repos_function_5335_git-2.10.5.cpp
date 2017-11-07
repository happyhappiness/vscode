static void show_worktree_porcelain(struct worktree *wt)
{
	printf("worktree %s\n", wt->path);
	if (wt->is_bare)
		printf("bare\n");
	else {
		printf("HEAD %s\n", sha1_to_hex(wt->head_sha1));
		if (wt->is_detached)
			printf("detached\n");
		else
			printf("branch %s\n", wt->head_ref);
	}
	printf("\n");
}