		}
	}

	strbuf_release(&line);
}

static const char *files_packed_refs_path(struct files_ref_store *refs)
{
	return refs->packed_refs_path;
}

static void files_reflog_path(struct files_ref_store *refs,
			      struct strbuf *sb,
			      const char *refname)
{
	if (!refname) {
		/*
		 * FIXME: of course this is wrong in multi worktree
		 * setting. To be fixed real soon.
		 */
		strbuf_addf(sb, "%s/logs", refs->gitcommondir);
		return;
	}

	switch (ref_type(refname)) {
	case REF_TYPE_PER_WORKTREE:
	case REF_TYPE_PSEUDOREF:
		strbuf_addf(sb, "%s/logs/%s", refs->gitdir, refname);
		break;
	case REF_TYPE_NORMAL:
		strbuf_addf(sb, "%s/logs/%s", refs->gitcommondir, refname);
		break;
	default:
		die("BUG: unknown ref type %d of ref %s",
		    ref_type(refname), refname);
	}
}

static void files_ref_path(struct files_ref_store *refs,
			   struct strbuf *sb,
			   const char *refname)
{
	switch (ref_type(refname)) {
	case REF_TYPE_PER_WORKTREE:
	case REF_TYPE_PSEUDOREF:
		strbuf_addf(sb, "%s/%s", refs->gitdir, refname);
		break;
	case REF_TYPE_NORMAL:
		strbuf_addf(sb, "%s/%s", refs->gitcommondir, refname);
		break;
	default:
		die("BUG: unknown ref type %d of ref %s",
		    ref_type(refname), refname);
	}
}

/*
 * Get the packed_ref_cache for the specified files_ref_store,
 * creating it if necessary.
 */
static struct packed_ref_cache *get_packed_ref_cache(struct files_ref_store *refs)
{
	const char *packed_refs_file = files_packed_refs_path(refs);

	if (refs->packed &&
	    !stat_validity_check(&refs->packed->validity, packed_refs_file))
		clear_packed_ref_cache(refs);

	if (!refs->packed) {
		FILE *f;

		refs->packed = xcalloc(1, sizeof(*refs->packed));
		acquire_packed_ref_cache(refs->packed);
		refs->packed->cache = create_ref_cache(&refs->base, NULL);
		refs->packed->cache->root->flag &= ~REF_INCOMPLETE;
		f = fopen(packed_refs_file, "r");
		if (f) {
			stat_validity_update(&refs->packed->validity, fileno(f));
			read_packed_refs(f, get_ref_dir(refs->packed->cache->root));
			fclose(f);
		}
	}
	return refs->packed;
}

static struct ref_dir *get_packed_ref_dir(struct packed_ref_cache *packed_ref_cache)
{
	return get_ref_dir(packed_ref_cache->cache->root);
}

static struct ref_dir *get_packed_refs(struct files_ref_store *refs)
{
	return get_packed_ref_dir(get_packed_ref_cache(refs));
}
