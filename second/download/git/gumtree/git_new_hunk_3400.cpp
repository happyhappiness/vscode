				path, sha1_to_hex(ce->sha1));

		if (ce_mode_s_ifmt == S_IFLNK && has_symlinks && !to_tempfile) {
			ret = symlink(new, path);
			free(new);
			if (ret)
				return error_errno("unable to create symlink %s",
						   path);
			break;
		}

		/*
		 * Convert from git internal format to working tree format
		 */
