		goto out;
	}

	for (i = 0; i < refnames->nr; i++) {
		const char *refname = refnames->items[i].string;

		if (refs_delete_ref(&refs->base, msg, refname, NULL, flags))
			result |= error(_("could not remove reference %s"), refname);
	}

out:
	strbuf_release(&err);
	return result;
