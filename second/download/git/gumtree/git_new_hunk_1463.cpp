
static void remote_ls(const char *path, int flags,
		      void (*userFunc)(struct remote_ls_ctx *ls),
		      void *userData);

/* extract hex from sharded "xx/x{40}" filename */
static int get_oid_hex_from_objpath(const char *path, struct object_id *oid)
{
	char hex[GIT_MAX_HEXSZ];

	if (strlen(path) != GIT_SHA1_HEXSZ + 1)
		return -1;

	memcpy(hex, path, 2);
	path += 2;
	path++; /* skip '/' */
	memcpy(hex, path, GIT_SHA1_HEXSZ - 2);

	return get_oid_hex(hex, oid);
}

static void process_ls_object(struct remote_ls_ctx *ls)
{
	unsigned int *parent = (unsigned int *)ls->userData;
	const char *path = ls->dentry_name;
	struct object_id oid;

	if (!strcmp(ls->path, ls->dentry_name) && (ls->flags & IS_DIR)) {
		remote_dir_exists[*parent] = 1;
		return;
	}

	if (!skip_prefix(path, "objects/", &path) ||
	    get_oid_hex_from_objpath(path, &oid))
		return;

	one_remote_object(&oid);
}

static void process_ls_ref(struct remote_ls_ctx *ls)
{
	if (!strcmp(ls->path, ls->dentry_name) && (ls->dentry_flags & IS_DIR)) {
		fprintf(stderr, "  %s\n", ls->dentry_name);
