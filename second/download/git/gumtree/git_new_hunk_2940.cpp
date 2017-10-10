			ls->dentry_name, repo->url);
		aborted = 1;
		free(ref);
		return;
	}

	o = parse_object(ref->old_oid.hash);
	if (!o) {
		fprintf(stderr,
			"Unable to parse object %s for remote ref %s\n",
			oid_to_hex(&ref->old_oid), ls->dentry_name);
		aborted = 1;
		free(ref);
		return;
	}

	strbuf_addf(buf, "%s\t%s\n",
		    oid_to_hex(&ref->old_oid), ls->dentry_name);

	if (o->type == OBJ_TAG) {
		o = deref_tag(o, ls->dentry_name, 0);
		if (o)
			strbuf_addf(buf, "%s\t%s^{}\n",
				    oid_to_hex(&o->oid), ls->dentry_name);
	}
	free(ref);
}

static void update_remote_info_refs(struct remote_lock *lock)
{
