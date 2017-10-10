}

static struct commit *get_commit_reference(const unsigned char *sha1)
{
	struct commit *r = lookup_commit_reference(sha1);
	if (!r)
		die(_("Not a valid commit name %s"), sha1_to_hex(sha1));
	return r;
}

static struct commit **get_bad_and_good_commits(int *rev_nr)
{
	struct commit **rev;
