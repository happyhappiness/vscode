		return error("%s: object corrupt or missing", sha1_to_hex(sha1));
	}
	obj->flags = HAS_OBJ;
	return fsck_obj(obj);
}

static int default_refs;

static void fsck_handle_reflog_sha1(const char *refname, unsigned char *sha1)
{
	struct object *obj;

