				return read_file_or_gitlink(ce, buf);
			else
				return SUBMODULE_PATCH_WITHOUT_INDEX;
		} else if (has_symlink_leading_path(name, strlen(name))) {
			return error(_("reading from '%s' beyond a symbolic link"), name);
		} else {
			if (read_old_data(st, patch, name, buf))
				return error(_("failed to read %s"), name);
		}
	}
	return 0;
}

