			break;
		default:
			return -1;
		}

		if (S_ISDIR(entry.mode))
			hashcpy(sha1, entry.oid->hash);
		else if (S_ISGITLINK(entry.mode)) {
			struct commit *commit;

			commit = lookup_commit(entry.oid->hash);
			if (!commit)
				die("Commit %s in submodule path %s%s not found",
				    oid_to_hex(entry.oid),
				    base->buf, entry.path);

			if (parse_commit(commit))
				die("Invalid commit %s in submodule path %s%s",
				    oid_to_hex(entry.oid),
				    base->buf, entry.path);

			hashcpy(sha1, commit->tree->object.oid.hash);
		}
		else
			continue;

		len = tree_entry_len(&entry);
		strbuf_add(base, entry.path, len);
		strbuf_addch(base, '/');
		retval = read_tree_1(lookup_tree(sha1),
				     base, stage, pathspec,
				     fn, context);
		strbuf_setlen(base, oldlen);
		if (retval)
			return -1;
	}
