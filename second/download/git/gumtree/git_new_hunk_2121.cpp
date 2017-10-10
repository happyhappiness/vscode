			if (ret && only_to_die) {
				diagnose_invalid_sha1_path(prefix, filename,
							   tree_sha1,
							   name, len);
			}
			hashcpy(oc->tree, tree_sha1);
			strlcpy(oc->path, filename, sizeof(oc->path));

			free(new_filename);
			return ret;
		} else {
			if (only_to_die)
				die("Invalid object name '%.*s'.", len, name);
