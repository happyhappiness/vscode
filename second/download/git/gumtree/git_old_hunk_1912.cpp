			if (is_git_directory(DEFAULT_GIT_DIR_ENVIRONMENT))
				gitdirenv = DEFAULT_GIT_DIR_ENVIRONMENT;
		}

		if (gitdirenv) {
			ret = setup_discovered_git_dir(gitdirenv,
						       cwd, offset, len,
						       nongit_ok);
			free(gitfile);
			return ret;
		}
		free(gitfile);

		if (is_git_directory("."))
			return setup_bare_git_dir(cwd, offset, len, nongit_ok);

		offset_parent = offset;
		while (--offset_parent > ceil_offset && cwd[offset_parent] != '/');
		if (offset_parent <= ceil_offset)
			return setup_nongit(cwd, nongit_ok);
		if (one_filesystem) {
			dev_t parent_device = get_device_or_die("..", cwd, offset);
			if (parent_device != current_device) {
				if (nongit_ok) {
					if (chdir(cwd))
						die_errno("Cannot come back to cwd");
					*nongit_ok = 1;
					return NULL;
				}
				cwd[offset] = '\0';
				die("Not a git repository (or any parent up to mount point %s)\n"
				"Stopping at filesystem boundary (GIT_DISCOVERY_ACROSS_FILESYSTEM not set).", cwd);
			}
		}
		if (chdir("..")) {
			cwd[offset] = '\0';
			die_errno("Cannot change to '%s/..'", cwd);
		}
		offset = offset_parent;
	}
}

const char *setup_git_directory_gently(int *nongit_ok)
