static void one_remote_ref(const char *refname)
{
	struct ref *ref;
	struct object *obj;

	ref = alloc_ref(refname);

	if (http_fetch_ref(repo->url, ref) != 0) {
		fprintf(stderr,
			"Unable to fetch ref %s from %s\n",
			refname, repo->url);
		free(ref);
		return;
	}

	/*
	 * Fetch a copy of the object if it doesn't exist locally - it
	 * may be required for updating server info later.
	 */
	if (repo->can_update_info_refs && !has_sha1_file(ref->old_sha1)) {
		obj = lookup_unknown_object(ref->old_sha1);
		if (obj) {
			fprintf(stderr,	"  fetch %s for %s\n",
				sha1_to_hex(ref->old_sha1), refname);
			add_fetch_request(obj);
		}
	}

	ref->next = remote_refs;
	remote_refs = ref;
}