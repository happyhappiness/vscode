
static void remote_ls(const char *path, int flags,
		      void (*userFunc)(struct remote_ls_ctx *ls),
		      void *userData);

/* extract hex from sharded "xx/x{40}" filename */
static int get_sha1_hex_from_objpath(const char *path, unsigned char *sha1)
{
	char hex[40];

	if (strlen(path) != 41)
		return -1;

	memcpy(hex, path, 2);
	path += 2;
	path++; /* skip '/' */
	memcpy(hex, path, 38);

	return get_sha1_hex(hex, sha1);
}

static void process_ls_object(struct remote_ls_ctx *ls)
{
	unsigned int *parent = (unsigned int *)ls->userData;
	const char *path = ls->dentry_name;
	unsigned char sha1[20];

	if (!strcmp(ls->path, ls->dentry_name) && (ls->flags & IS_DIR)) {
		remote_dir_exists[*parent] = 1;
		return;
	}

	if (!skip_prefix(path, "objects/", &path) ||
	    get_sha1_hex_from_objpath(path, sha1))
		return;

	one_remote_object(sha1);
}

static void process_ls_ref(struct remote_ls_ctx *ls)
{
	if (!strcmp(ls->path, ls->dentry_name) && (ls->dentry_flags & IS_DIR)) {
		fprintf(stderr, "  %s\n", ls->dentry_name);
