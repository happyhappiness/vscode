static int
set_mode(struct archive_write_disk *a, int mode)
{
	int r = ARCHIVE_OK;
	mode &= 07777; /* Strip off file type bits. */

	if (a->todo & TODO_SGID_CHECK) {
		/*
		 * If we don't know the GID is right, we must stat()
		 * to verify it.  We can't just check the GID of this
		 * process, since systems sometimes set GID from
		 * the enclosing dir or based on ACLs.
		 */
		if ((r = lazy_stat(a)) != ARCHIVE_OK)
			return (r);
		if (0 != a->gid) {
			mode &= ~ S_ISGID;
		}
		/* While we're here, double-check the UID. */
		if (0 != a->uid
		    && (a->todo & TODO_SUID)) {
			mode &= ~ S_ISUID;
		}
		a->todo &= ~TODO_SGID_CHECK;
		a->todo &= ~TODO_SUID_CHECK;
	} else if (a->todo & TODO_SUID_CHECK) {
		/*
		 * If we don't know the UID is right, we can just check
		 * the user, since all systems set the file UID from
		 * the process UID.
		 */
		if (a->user_uid != a->uid) {
			mode &= ~ S_ISUID;
		}
		a->todo &= ~TODO_SUID_CHECK;
	}

	if (S_ISLNK(a->mode)) {
#ifdef HAVE_LCHMOD
		/*
		 * If this is a symlink, use lchmod().  If the
		 * platform doesn't support lchmod(), just skip it.  A
		 * platform that doesn't provide a way to set
		 * permissions on symlinks probably ignores
		 * permissions on symlinks, so a failure here has no
		 * impact.
		 */
		if (lchmod(a->name, mode) != 0) {
			archive_set_error(&a->archive, errno,
			    "Can't set permissions to 0%o", (int)mode);
			r = ARCHIVE_WARN;
		}
#endif
	} else if (!S_ISDIR(a->mode)) {
		/*
		 * If it's not a symlink and not a dir, then use
		 * fchmod() or chmod(), depending on whether we have
		 * an fd.  Dirs get their perms set during the
		 * post-extract fixup, which is handled elsewhere.
		 */
#ifdef HAVE_FCHMOD
		if (a->fd >= 0) {
			if (fchmod(a->fd, mode) != 0) {
				archive_set_error(&a->archive, errno,
				    "Can't set permissions to 0%o", (int)mode);
				r = ARCHIVE_WARN;
			}
		} else
#endif
			/* If this platform lacks fchmod(), then
			 * we'll just use chmod(). */
			if (la_chmod(a->name, mode) != 0) {
				archive_set_error(&a->archive, errno,
				    "Can't set permissions to 0%o", (int)mode);
				r = ARCHIVE_WARN;
			}
	}
	return (r);
}