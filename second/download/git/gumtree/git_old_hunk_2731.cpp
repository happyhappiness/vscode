		display_progress(cp->progress, cp->count);
}

static int add_one_ref(const char *path, const struct object_id *oid,
		       int flag, void *cb_data)
{
	struct object *object = parse_object_or_die(oid->hash, path);
	struct rev_info *revs = (struct rev_info *)cb_data;

	add_pending_object(revs, object, "");

	return 0;
}

/*
