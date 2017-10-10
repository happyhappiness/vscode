		struct cache_entry *ce = active_cache[i];
		struct blob *blob;

		if (S_ISGITLINK(ce->ce_mode))
			continue;

		blob = lookup_blob(&ce->oid);
		if (!blob)
			die("unable to add index blob to traversal");
		add_pending_object_with_path(revs, &blob->object, "",
					     ce->ce_mode, ce->name);
	}

