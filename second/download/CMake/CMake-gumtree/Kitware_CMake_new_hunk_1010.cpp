		tree_enter_initial_dir(t);

		return (ARCHIVE_FATAL);

	}

	if (t->initial_filesystem_id == -1)

		t->initial_filesystem_id = t->current_filesystem_id;

	if (!a->traverse_mount_points) {

		if (t->initial_filesystem_id != t->current_filesystem_id)

			return (ARCHIVE_RETRY);

	}

	t->descend = descend;



	/*

	 * Honor nodump flag.

	 * If the file is marked with nodump flag, do not return this entry.

	 */

	if (a->honor_nodump) {

#if defined(HAVE_STRUCT_STAT_ST_FLAGS) && defined(UF_NODUMP)

		if (st->st_flags & UF_NODUMP)

			return (ARCHIVE_RETRY);

#elif defined(EXT2_IOC_GETFLAGS) && defined(EXT2_NODUMP_FL) &&\

      defined(HAVE_WORKING_EXT2_IOC_GETFLAGS)

		if (S_ISREG(st->st_mode) || S_ISDIR(st->st_mode)) {

			int stflags;



			t->entry_fd = open_on_current_dir(t,

			    tree_current_access_path(t),

			    O_RDONLY | O_NONBLOCK | O_CLOEXEC);

			__archive_ensure_cloexec_flag(t->entry_fd);

			if (t->entry_fd >= 0) {

				r = ioctl(t->entry_fd, EXT2_IOC_GETFLAGS,

					&stflags);

				if (r == 0 && (stflags & EXT2_NODUMP_FL) != 0)

					return (ARCHIVE_RETRY);

			}

		}

#endif

	}



	archive_entry_copy_stat(entry, st);



	/* Save the times to be restored. This must be in before

	 * calling archive_read_disk_descend() or any chance of it,

	 * especially, invokng a callback. */

	t->restore_time.mtime = archive_entry_mtime(entry);

	t->restore_time.mtime_nsec = archive_entry_mtime_nsec(entry);

	t->restore_time.atime = archive_entry_atime(entry);

	t->restore_time.atime_nsec = archive_entry_atime_nsec(entry);

	t->restore_time.filetype = archive_entry_filetype(entry);

	t->restore_time.noatime = t->current_filesystem->noatime;



	/*

	 * Perform time matching.

	 */

	if (a->matching) {

		r = archive_match_time_excluded(a->matching, entry);

		if (r < 0) {

			archive_set_error(&(a->archive), errno,

			    "Faild : %s", archive_error_string(a->matching));

			return (r);

		}

		if (r) {

			if (a->excluded_cb_func)

				a->excluded_cb_func(&(a->archive),

				    a->excluded_cb_data, entry);

			return (ARCHIVE_RETRY);

		}

	}



	/* Lookup uname/gname */

	name = archive_read_disk_uname(&(a->archive), archive_entry_uid(entry));

	if (name != NULL)

		archive_entry_copy_uname(entry, name);

	name = archive_read_disk_gname(&(a->archive), archive_entry_gid(entry));

	if (name != NULL)

		archive_entry_copy_gname(entry, name);



	/*

	 * Perform owner matching.

	 */

	if (a->matching) {

		r = archive_match_owner_excluded(a->matching, entry);

		if (r < 0) {

			archive_set_error(&(a->archive), errno,

			    "Faild : %s", archive_error_string(a->matching));

			return (r);

		}

		if (r) {

			if (a->excluded_cb_func)

				a->excluded_cb_func(&(a->archive),

				    a->excluded_cb_data, entry);

			return (ARCHIVE_RETRY);

		}

	}



	/*

	 * Invoke a meta data filter callback.

	 */

	if (a->metadata_filter_func) {

		if (!a->metadata_filter_func(&(a->archive),

		    a->metadata_filter_data, entry))

			return (ARCHIVE_RETRY);

	}



	/*

	 * Populate the archive_entry with metadata from the disk.

	 */

	archive_entry_copy_sourcepath(entry, tree_current_access_path(t));

	r = archive_read_disk_entry_from_file(&(a->archive), entry,

		t->entry_fd, st);



	return (r);

}



static int

_archive_read_next_header2(struct archive *_a, struct archive_entry *entry)

{

	struct archive_read_disk *a = (struct archive_read_disk *)_a;

	struct tree *t;

	int r;



	archive_check_magic(_a, ARCHIVE_READ_DISK_MAGIC,

	    ARCHIVE_STATE_HEADER | ARCHIVE_STATE_DATA,

	    "archive_read_next_header2");



	t = a->tree;

	if (t->entry_fd >= 0) {

		close_and_restore_time(t->entry_fd, t, &t->restore_time);

		t->entry_fd = -1;

	}



	for (;;) {

		r = next_entry(a, t, entry);

		if (t->entry_fd >= 0) {

			close(t->entry_fd);

			t->entry_fd = -1;

		}



		if (r == ARCHIVE_RETRY) {

			archive_entry_clear(entry);

			continue;

		}

		break;

	}



	/* Return to the initial directory. */

	tree_enter_initial_dir(t);



	/*

	 * EOF and FATAL are persistent at this layer.  By

