static void free_rerere_dirs(void)
{
	int i;
	for (i = 0; i < rerere_dir_nr; i++) {
		free(rerere_dir[i]->status);
		free(rerere_dir[i]);
	}
	free(rerere_dir);
	rerere_dir_nr = rerere_dir_alloc = 0;
	rerere_dir = NULL;
}