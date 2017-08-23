static int
set_ownership(struct archive_write_disk *a)
{
/* unfortunately, on win32 there is no 'root' user with uid 0,
   so we just have to try the chown and see if it works */

	/* If we know we can't change it, don't bother trying. */
	if (a->user_uid != 0  &&  a->user_uid != a->uid) {
		archive_set_error(&a->archive, errno,
		    "Can't set UID=%jd", (intmax_t)a->uid);
		return (ARCHIVE_WARN);
	}

	archive_set_error(&a->archive, errno,
	    "Can't set user=%jd/group=%jd for %ls",
	    (intmax_t)a->uid, (intmax_t)a->gid, a->name);
	return (ARCHIVE_WARN);
}