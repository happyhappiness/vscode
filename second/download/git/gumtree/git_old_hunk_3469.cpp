			if (retval == all_entries_not_interesting)
				break;
			if (retval == entry_not_interesting)
				continue;
		}

		switch (fn(entry.sha1, base,
			   entry.path, entry.mode, stage, context)) {
		case 0:
			continue;
		case READ_TREE_RECURSIVE:
			break;
		default:
			return -1;
		}

		if (S_ISDIR(entry.mode))
			hashcpy(sha1, entry.sha1);
		else if (S_ISGITLINK(entry.mode)) {
			struct commit *commit;

			commit = lookup_commit(entry.sha1);
			if (!commit)
				die("Commit %s in submodule path %s%s not found",
				    sha1_to_hex(entry.sha1),
				    base->buf, entry.path);

			if (parse_commit(commit))
				die("Invalid commit %s in submodule path %s%s",
				    sha1_to_hex(entry.sha1),
				    base->buf, entry.path);

			hashcpy(sha1, commit->tree->object.oid.hash);
		}
		else
			continue;
