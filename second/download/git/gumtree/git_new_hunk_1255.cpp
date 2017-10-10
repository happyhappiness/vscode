		extra = read_commit_extra_headers(current_head, exclude_gpgsig);
	} else {
		struct commit_extra_header **tail = &extra;
		append_merge_tag_headers(parents, &tail);
	}

	if (commit_tree_extended(sb.buf, sb.len, active_cache_tree->oid.hash,
			 parents, oid.hash, author_ident.buf, sign_commit, extra)) {
		rollback_index_files();
		die(_("failed to write commit object"));
	}
	strbuf_release(&author_ident);
	free_commit_extra_headers(extra);
