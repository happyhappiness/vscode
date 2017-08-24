{
		accpath = archive_entry_sourcepath(entry);
		if (accpath == NULL || (a->tree != NULL &&
		    a->tree_enter_working_dir(a->tree) != 0))
			accpath = archive_entry_pathname(entry);
		if (accpath == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Couldn't determine file path to read ACLs");
			return (ARCHIVE_WARN);
		}
		if (a->tree != NULL &&
#if !HAVE_SUN_ACL && !HAVE_DARWIN_ACL && !HAVE_ACL_GET_FD_NP
		    *fd < 0 &&
#endif
		    (a->follow_symlinks ||
		    archive_entry_filetype(entry) != AE_IFLNK)) {
			*fd = a->open_on_current_dir(a->tree,
			    accpath, O_RDONLY | O_NONBLOCK);
		}
	}