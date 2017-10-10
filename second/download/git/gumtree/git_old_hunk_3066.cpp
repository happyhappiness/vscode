} **entries;
static int alloc, used;

static void append_to_tree(unsigned mode, unsigned char *sha1, char *path)
{
	struct treeent *ent;
	int len = strlen(path);
	if (strchr(path, '/'))
		die("path %s contains slash", path);

	ALLOC_GROW(entries, used + 1, alloc);
	ent = entries[used++] = xmalloc(sizeof(**entries) + len + 1);
	ent->mode = mode;
	ent->len = len;
	hashcpy(ent->sha1, sha1);
	memcpy(ent->name, path, len+1);
}

static int ent_compare(const void *a_, const void *b_)
{
	struct treeent *a = *(struct treeent **)a_;
	struct treeent *b = *(struct treeent **)b_;
