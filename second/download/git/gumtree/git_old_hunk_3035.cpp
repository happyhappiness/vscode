}

static void print_ok_ref_status(struct ref *ref, int porcelain)
{
	if (ref->deletion)
		print_ref_status('-', "[deleted]", ref, NULL, NULL, porcelain);
	else if (is_null_sha1(ref->old_sha1))
		print_ref_status('*',
			(starts_with(ref->name, "refs/tags/") ? "[new tag]" :
			"[new branch]"),
			ref, ref->peer_ref, NULL, porcelain);
	else {
		char quickref[84];
		char type;
		const char *msg;

		strcpy(quickref, status_abbrev(ref->old_sha1));
		if (ref->forced_update) {
			strcat(quickref, "...");
			type = '+';
			msg = "forced update";
		} else {
			strcat(quickref, "..");
			type = ' ';
			msg = NULL;
		}
		strcat(quickref, status_abbrev(ref->new_sha1));

		print_ref_status(type, quickref, ref, ref->peer_ref, msg, porcelain);
	}
}

static int print_one_push_status(struct ref *ref, const char *dest, int count, int porcelain)
{
	if (!count)
