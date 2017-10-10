} **entries;
static int alloc, used;

static void append_to_tree(unsigned mode, unsigned char *sha1, char *path)
{
	struct treeent *ent;
	size_t len = strlen(path);
	if (strchr(path, '/'))
		die("path %s contains slash", path);

	FLEX_ALLOC_MEM(ent, name, path, len);
	ent->mode = mode;
	ent->len = len;
	hashcpy(ent->sha1, sha1);

	ALLOC_GROW(entries, used + 1, alloc);
	entries[used++] = ent;
}

static int ent_compare(const void *a_, const void *b_)
{
	struct treeent *a = *(struct treeent **)a_;
	struct treeent *b = *(struct treeent **)b_;
