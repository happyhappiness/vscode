	}

	if (repair) {
		unsigned char sha1[20];
		hash_sha1_file(buffer.buf, buffer.len, tree_type, sha1);
		if (has_sha1_file(sha1))
			hashcpy(it->oid.hash, sha1);
		else
			to_invalidate = 1;
	} else if (dryrun)
		hash_sha1_file(buffer.buf, buffer.len, tree_type,
			       it->oid.hash);
	else if (write_sha1_file(buffer.buf, buffer.len, tree_type, it->oid.hash)) {
		strbuf_release(&buffer);
		return -1;
	}

	strbuf_release(&buffer);
	it->entry_count = to_invalidate ? -1 : i - *skip_count;
#if DEBUG
	fprintf(stderr, "cache-tree update-one (%d ent, %d subtree) %s\n",
		it->entry_count, it->subtree_nr,
		oid_to_hex(&it->oid));
#endif
	return i;
}

int cache_tree_update(struct index_state *istate, int flags)
{
