}

static void remote_ls(const char *path, int flags,
		      void (*userFunc)(struct remote_ls_ctx *ls),
		      void *userData);

static void process_ls_object(struct remote_ls_ctx *ls)
{
	unsigned int *parent = (unsigned int *)ls->userData;
	char *path = ls->dentry_name;
	char *obj_hex;

	if (!strcmp(ls->path, ls->dentry_name) && (ls->flags & IS_DIR)) {
		remote_dir_exists[*parent] = 1;
		return;
	}

	if (strlen(path) != 49)
		return;
	path += 8;
	obj_hex = xmalloc(strlen(path));
	/* NB: path is not null-terminated, can not use strlcpy here */
	memcpy(obj_hex, path, 2);
	strcpy(obj_hex + 2, path + 3);
	one_remote_object(obj_hex);
	free(obj_hex);
}

static void process_ls_ref(struct remote_ls_ctx *ls)
{
	if (!strcmp(ls->path, ls->dentry_name) && (ls->dentry_flags & IS_DIR)) {
		fprintf(stderr, "  %s\n", ls->dentry_name);
