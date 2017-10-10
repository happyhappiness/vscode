
			if (parse_commit(commit))
				die("Invalid commit %s in submodule path %s%s",
				    sha1_to_hex(entry.sha1),
				    base->buf, entry.path);

			hashcpy(sha1, commit->tree->object.oid.hash);
		}
		else
			continue;

		len = tree_entry_len(&entry);
		strbuf_add(base, entry.path, len);
