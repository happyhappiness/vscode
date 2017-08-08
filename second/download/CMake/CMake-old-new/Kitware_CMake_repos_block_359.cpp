{
#ifndef __CYGWIN__
/* unfortunately, on win32 there is no 'root' user with uid 0,
   so we just have to try the chown and see if it works */

	/* If we know we can't change it, don't bother trying. */
	if (a->user_uid != 0  &&  a->user_uid != a->uid) {
		archive_set_error(&a->archive, errno,
		    "Can't set UID=%jd", (intmax_t)a->uid);
		return (ARCHIVE_WARN);
	}
#endif

#ifdef HAVE_FCHOWN
	/* If we have an fd, we can avoid a race. */
	if (a->fd >= 0 && fchown(a->fd, a->uid, a->gid) == 0) {
		/* We've set owner and know uid/gid are correct. */
		a->todo &= ~(TODO_OWNER | TODO_SGID_CHECK | TODO_SUID_CHECK);
		return (ARCHIVE_OK);
	}
#endif

	/* We prefer lchown() but will use chown() if that's all we have. */
	/* Of course, if we have neither, this will always fail. */
#ifdef HAVE_LCHOWN
	if (lchown(a->name, a->uid, a->gid) == 0) {
		/* We've set owner and know uid/gid are correct. */
		a->todo &= ~(TODO_OWNER | TODO_SGID_CHECK | TODO_SUID_CHECK);
		return (ARCHIVE_OK);
	}
#elif HAVE_CHOWN
	if (!S_ISLNK(a->mode) && chown(a->name, a->uid, a->gid) == 0) {
		/* We've set owner and know uid/gid are correct. */
		a->todo &= ~(TODO_OWNER | TODO_SGID_CHECK | TODO_SUID_CHECK);
		return (ARCHIVE_OK);
	}
#endif

	archive_set_error(&a->archive, errno,
	    "Can't set user=%jd/group=%jd for %s",
	    (intmax_t)a->uid, (intmax_t)a->gid, a->name);
	return (ARCHIVE_WARN);
}