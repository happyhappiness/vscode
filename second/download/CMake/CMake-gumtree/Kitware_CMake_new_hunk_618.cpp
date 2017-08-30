		}



		/*

		 * Check for a mismatch between the type in the specification

		 * and the type of the contents object on disk.

		 */

		if (st != NULL) {

			if (((st->st_mode & S_IFMT) == S_IFREG &&

			      archive_entry_filetype(entry) == AE_IFREG)

#ifdef S_IFLNK

			  ||((st->st_mode & S_IFMT) == S_IFLNK &&

			      archive_entry_filetype(entry) == AE_IFLNK)

#endif

#ifdef S_IFSOCK

			  ||((st->st_mode & S_IFSOCK) == S_IFSOCK &&

			      archive_entry_filetype(entry) == AE_IFSOCK)

#endif

#ifdef S_IFCHR

			  ||((st->st_mode & S_IFMT) == S_IFCHR &&

			      archive_entry_filetype(entry) == AE_IFCHR)

#endif

#ifdef S_IFBLK

			  ||((st->st_mode & S_IFMT) == S_IFBLK &&

			      archive_entry_filetype(entry) == AE_IFBLK)

#endif

			  ||((st->st_mode & S_IFMT) == S_IFDIR &&

			      archive_entry_filetype(entry) == AE_IFDIR)

#ifdef S_IFIFO

			  ||((st->st_mode & S_IFMT) == S_IFIFO &&

			      archive_entry_filetype(entry) == AE_IFIFO)

#endif

			) {

				/* Types match. */

			} else {

				/* Types don't match; bail out gracefully. */

				if (mtree->fd >= 0)

					close(mtree->fd);

				mtree->fd = -1;

				if (parsed_kws & MTREE_HAS_OPTIONAL) {

					/* It's not an error for an optional

					 * entry to not match disk. */

					*use_next = 1;

				} else if (r == ARCHIVE_OK) {

					archive_set_error(&a->archive,

					    ARCHIVE_ERRNO_MISC,

					    "mtree specification has different"

					    " type for %s",

					    archive_entry_pathname(entry));

					r = ARCHIVE_WARN;

				}

				return (r);

			}

		}



		/*

		 * If there is a contents file on disk, pick some of the

		 * metadata from that file.  For most of these, we only

		 * set it from the contents if it wasn't already parsed

		 * from the specification.

		 */

		if (st != NULL) {

			if (((parsed_kws & MTREE_HAS_DEVICE) == 0 ||

				(parsed_kws & MTREE_HAS_NOCHANGE) != 0) &&

				(archive_entry_filetype(entry) == AE_IFCHR ||

				 archive_entry_filetype(entry) == AE_IFBLK))

				archive_entry_set_rdev(entry, st->st_rdev);

			if ((parsed_kws & (MTREE_HAS_GID | MTREE_HAS_GNAME))

				== 0 ||

			    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)

				archive_entry_set_gid(entry, st->st_gid);

			if ((parsed_kws & (MTREE_HAS_UID | MTREE_HAS_UNAME))

				== 0 ||

			    (parsed_kws & MTREE_HAS_NOCHANGE) != 0)

				archive_entry_set_uid(entry, st->st_uid);

			if ((parsed_kws & MTREE_HAS_MTIME) == 0 ||

			    (parsed_kws & MTREE_HAS_NOCHANGE) != 0) {

#if HAVE_STRUCT_STAT_ST_MTIMESPEC_TV_NSEC

				archive_entry_set_mtime(entry, st->st_mtime,

						st->st_mtimespec.tv_nsec);

