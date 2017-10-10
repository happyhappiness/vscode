	}
	closedir(dir);
}

static int default_refs;

static void fsck_handle_reflog_sha1(const char *refname, unsigned char *sha1)
{
	struct object *obj;

	if (!is_null_sha1(sha1)) {
		obj = lookup_object(sha1);
		if (obj) {
			obj->used = 1;
			mark_object_reachable(obj);
		} else {
			error("%s: invalid reflog entry %s", refname, sha1_to_hex(sha1));
			errors_found |= ERROR_REACHABLE;
		}
	}
}

static int fsck_handle_reflog_ent(unsigned char *osha1, unsigned char *nsha1,
		const char *email, unsigned long timestamp, int tz,
		const char *message, void *cb_data)
{
	const char *refname = cb_data;

	if (verbose)
		fprintf(stderr, "Checking reflog %s->%s\n",
			sha1_to_hex(osha1), sha1_to_hex(nsha1));

	fsck_handle_reflog_sha1(refname, osha1);
	fsck_handle_reflog_sha1(refname, nsha1);
	return 0;
}

static int fsck_handle_reflog(const char *logname, const unsigned char *sha1, int flag, void *cb_data)
{
	for_each_reflog_ent(logname, fsck_handle_reflog_ent, (void *)logname);
	return 0;
}

static int fsck_handle_ref(const char *refname, const unsigned char *sha1, int flag, void *cb_data)
{
	struct object *obj;
