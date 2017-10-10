
static int deref_tags, show_head, tags_only, heads_only, found_match, verify,
	   quiet, hash_only, abbrev, exclude_arg;
static const char **pattern;
static const char *exclude_existing_arg;

static void show_one(const char *refname, const unsigned char *sha1)
{
	const char *hex = find_unique_abbrev(sha1, abbrev);
	if (hash_only)
		printf("%s\n", hex);
	else
		printf("%s %s\n", hex, refname);
}

static int show_ref(const char *refname, const unsigned char *sha1, int flag, void *cbdata)
{
	const char *hex;
	unsigned char peeled[20];

	if (show_head && !strcmp(refname, "HEAD"))
		goto match;

	if (tags_only || heads_only) {
		int match;
