struct ref_to_prune {
	struct ref_to_prune *next;
	unsigned char sha1[20];
	char name[FLEX_ARRAY];
};

enum {
	REMOVE_EMPTY_PARENTS_REF = 0x01,
	REMOVE_EMPTY_PARENTS_REFLOG = 0x02
};

/*
 * Remove empty parent directories associated with the specified
 * reference and/or its reflog, but spare [logs/]refs/ and immediate
 * subdirs. flags is a combination of REMOVE_EMPTY_PARENTS_REF and/or
 * REMOVE_EMPTY_PARENTS_REFLOG.
 */
static void try_remove_empty_parents(struct files_ref_store *refs,
				     const char *refname,
				     unsigned int flags)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf sb = STRBUF_INIT;
	char *p, *q;
	int i;

	strbuf_addstr(&buf, refname);
	p = buf.buf;
	for (i = 0; i < 2; i++) { /* refs/{heads,tags,...}/ */
		while (*p && *p != '/')
			p++;
		/* tolerate duplicate slashes; see check_refname_format() */
		while (*p == '/')
			p++;
	}
	q = buf.buf + buf.len;
	while (flags & (REMOVE_EMPTY_PARENTS_REF | REMOVE_EMPTY_PARENTS_REFLOG)) {
		while (q > p && *q != '/')
			q--;
		while (q > p && *(q-1) == '/')
			q--;
		if (q == p)
			break;
		strbuf_setlen(&buf, q - buf.buf);

		strbuf_reset(&sb);
		files_ref_path(refs, &sb, buf.buf);
		if ((flags & REMOVE_EMPTY_PARENTS_REF) && rmdir(sb.buf))
			flags &= ~REMOVE_EMPTY_PARENTS_REF;

		strbuf_reset(&sb);
		files_reflog_path(refs, &sb, buf.buf);
		if ((flags & REMOVE_EMPTY_PARENTS_REFLOG) && rmdir(sb.buf))
			flags &= ~REMOVE_EMPTY_PARENTS_REFLOG;
	}
	strbuf_release(&buf);
	strbuf_release(&sb);
}

/* make sure nobody touched the ref, and unlink */
static void prune_ref(struct files_ref_store *refs, struct ref_to_prune *r)
{
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	if (check_refname_format(r->name, 0))
		return;

	transaction = ref_store_transaction_begin(&refs->base, &err);
	if (!transaction ||
	    ref_transaction_delete(transaction, r->name, r->sha1,
				   REF_ISPRUNING | REF_NODEREF, NULL, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		ref_transaction_free(transaction);
		error("%s", err.buf);
		strbuf_release(&err);
		return;
	}
	ref_transaction_free(transaction);
	strbuf_release(&err);
}

static void prune_refs(struct files_ref_store *refs, struct ref_to_prune *r)
{
	while (r) {
		prune_ref(refs, r);
		r = r->next;
	}
}

static int files_pack_refs(struct ref_store *ref_store, unsigned int flags)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE | REF_STORE_ODB,
			       "pack_refs");
	struct ref_iterator *iter;
	struct ref_dir *packed_refs;
	int ok;
	struct ref_to_prune *refs_to_prune = NULL;

	lock_packed_refs(refs, LOCK_DIE_ON_ERROR);
	packed_refs = get_packed_refs(refs);

	iter = cache_ref_iterator_begin(get_loose_ref_cache(refs), NULL, 0);
	while ((ok = ref_iterator_advance(iter)) == ITER_OK) {
		/*
		 * If the loose reference can be packed, add an entry
		 * in the packed ref cache. If the reference should be
		 * pruned, also add it to refs_to_prune.
		 */
		struct ref_entry *packed_entry;
		int is_tag_ref = starts_with(iter->refname, "refs/tags/");

		/* Do not pack per-worktree refs: */
		if (ref_type(iter->refname) != REF_TYPE_NORMAL)
			continue;

		/* ALWAYS pack tags */
		if (!(flags & PACK_REFS_ALL) && !is_tag_ref)
			continue;

		/* Do not pack symbolic or broken refs: */
		if (iter->flags & REF_ISSYMREF)
			continue;

		if (!ref_resolves_to_object(iter->refname, iter->oid, iter->flags))
			continue;

		/*
		 * Create an entry in the packed-refs cache equivalent
		 * to the one from the loose ref cache, except that
		 * we don't copy the peeled status, because we want it
		 * to be re-peeled.
		 */
		packed_entry = find_ref_entry(packed_refs, iter->refname);
		if (packed_entry) {
			/* Overwrite existing packed entry with info from loose entry */
			packed_entry->flag = REF_ISPACKED;
			oidcpy(&packed_entry->u.value.oid, iter->oid);
		} else {
			packed_entry = create_ref_entry(iter->refname, iter->oid->hash,
							REF_ISPACKED, 0);
			add_ref_entry(packed_refs, packed_entry);
		}
		oidclr(&packed_entry->u.value.peeled);

		/* Schedule the loose reference for pruning if requested. */
		if ((flags & PACK_REFS_PRUNE)) {
			struct ref_to_prune *n;
			FLEX_ALLOC_STR(n, name, iter->refname);
			hashcpy(n->sha1, iter->oid->hash);
			n->next = refs_to_prune;
			refs_to_prune = n;
		}
	}
	if (ok != ITER_DONE)
		die("error while iterating over references");

	if (commit_packed_refs(refs))
		die_errno("unable to overwrite old ref-pack file");

	prune_refs(refs, refs_to_prune);
	return 0;
}

/*
 * Rewrite the packed-refs file, omitting any refs listed in
 * 'refnames'. On error, leave packed-refs unchanged, write an error
