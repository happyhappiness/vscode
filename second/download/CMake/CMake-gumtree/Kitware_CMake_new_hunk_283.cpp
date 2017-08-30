	return (a->current_fixup);

}



/* Error helper for new *_fsobj functions */

static void

fsobj_error(int *a_eno, struct archive_string *a_estr,

    int err, const char *errstr, const char *path)

{

	if (a_eno)

		*a_eno = err;

	if (a_estr)

		archive_string_sprintf(a_estr, errstr, path);

}



/*

 * TODO: Someday, integrate this with the deep dir support; they both

 * scan the path and both can be optimized by comparing against other

 * recent paths.

 */

/* TODO: Extend this to support symlinks on Windows Vista and later. */



/*

 * Checks the given path to see if any elements along it are symlinks.  Returns

 * ARCHIVE_OK if there are none, otherwise puts an error in errmsg.

 */

static int

check_symlinks_fsobj(char *path, int *a_eno, struct archive_string *a_estr,

    int flags)

{

#if !defined(HAVE_LSTAT)

	/* Platform doesn't have lstat, so we can't look for symlinks. */

	(void)path; /* UNUSED */

	(void)error_number; /* UNUSED */

	(void)error_string; /* UNUSED */

	(void)flags; /* UNUSED */

	return (ARCHIVE_OK);

#else

	int res = ARCHIVE_OK;

	char *tail;

	char *head;

	int last;

	char c;

	int r;

	struct stat st;

	int restore_pwd;



	/* Nothing to do here if name is empty */

	if(path[0] == '\0')

	    return (ARCHIVE_OK);



	/*

	 * Guard against symlink tricks.  Reject any archive entry whose

	 * destination would be altered by a symlink.

	 *

	 * Walk the filename in chunks separated by '/'.  For each segment:

	 *  - if it doesn't exist, continue

	 *  - if it's symlink, abort or remove it

	 *  - if it's a directory and it's not the last chunk, cd into it

	 * As we go:

	 *  head points to the current (relative) path

	 *  tail points to the temporary \0 terminating the segment we're

	 *      currently examining

	 *  c holds what used to be in *tail

	 *  last is 1 if this is the last tail

	 */

	restore_pwd = open(".", O_RDONLY | O_BINARY | O_CLOEXEC);

	__archive_ensure_cloexec_flag(restore_pwd);

	if (restore_pwd < 0)

		return (ARCHIVE_FATAL);

	head = path;

	tail = path;

	last = 0;

	/* TODO: reintroduce a safe cache here? */

	/* Skip the root directory if the path is absolute. */

	if(tail == path && tail[0] == '/')

		++tail;

	/* Keep going until we've checked the entire name.

	 * head, tail, path all alias the same string, which is

	 * temporarily zeroed at tail, so be careful restoring the

	 * stashed (c=tail[0]) for error messages.

	 * Exiting the loop with break is okay; continue is not.

	 */

	while (!last) {

		/*

		 * Skip the separator we just consumed, plus any adjacent ones

		 */

		while (*tail == '/')

		    ++tail;

		/* Skip the next path element. */

		while (*tail != '\0' && *tail != '/')

			++tail;

		/* is this the last path component? */

		last = (tail[0] == '\0') || (tail[0] == '/' && tail[1] == '\0');

		/* temporarily truncate the string here */

		c = tail[0];

		tail[0] = '\0';

		/* Check that we haven't hit a symlink. */

		r = lstat(head, &st);

		if (r != 0) {

			tail[0] = c;

			/* We've hit a dir that doesn't exist; stop now. */

			if (errno == ENOENT) {

				break;

			} else {

				/*

				 * Treat any other error as fatal - best to be

				 * paranoid here.

				 * Note: This effectively disables deep

				 * directory support when security checks are

				 * enabled. Otherwise, very long pathnames that

				 * trigger an error here could evade the

				 * sandbox.

				 * TODO: We could do better, but it would

				 * probably require merging the symlink checks

				 * with the deep-directory editing.

				 */

				fsobj_error(a_eno, a_estr, errno,

				    "Could not stat %s", path);

				res = ARCHIVE_FAILED;

				break;

			}

		} else if (S_ISDIR(st.st_mode)) {

			if (!last) {

				if (chdir(head) != 0) {

					tail[0] = c;

					fsobj_error(a_eno, a_estr, errno,

					    "Could not chdir %s", path);

					res = (ARCHIVE_FATAL);

					break;

				}

				/* Our view is now from inside this dir: */

				head = tail + 1;

			}

		} else if (S_ISLNK(st.st_mode)) {

			if (last) {

				/*

				 * Last element is symlink; remove it

				 * so we can overwrite it with the

				 * item being extracted.

				 */

				if (unlink(head)) {

					tail[0] = c;

					fsobj_error(a_eno, a_estr, errno,

					    "Could not remove symlink %s",

					    path);

					res = ARCHIVE_FAILED;

					break;

				}

				/*

				 * Even if we did remove it, a warning

				 * is in order.  The warning is silly,

				 * though, if we're just replacing one

				 * symlink with another symlink.

				 */

				tail[0] = c;

				/*

				 * FIXME:  not sure how important this is to

				 * restore

				 */

				/*

				if (!S_ISLNK(path)) {

					fsobj_error(a_eno, a_estr, 0,

					    "Removing symlink %s", path);

				}

				*/

				/* Symlink gone.  No more problem! */

				res = ARCHIVE_OK;

				break;

			} else if (flags & ARCHIVE_EXTRACT_UNLINK) {

				/* User asked us to remove problems. */

				if (unlink(head) != 0) {

					tail[0] = c;

					fsobj_error(a_eno, a_estr, 0,

					    "Cannot remove intervening "

					    "symlink %s", path);

					res = ARCHIVE_FAILED;

					break;

				}

				tail[0] = c;

			} else if ((flags &

			    ARCHIVE_EXTRACT_SECURE_SYMLINKS) == 0) {

				/*

				 * We are not the last element and we want to

				 * follow symlinks if they are a directory.

				 * 

				 * This is needed to extract hardlinks over

				 * symlinks.

				 */

				r = stat(head, &st);

				if (r != 0) {

					tail[0] = c;

					if (errno == ENOENT) {

						break;

					} else {

						fsobj_error(a_eno, a_estr,

						    errno,

						    "Could not stat %s", path);

						res = (ARCHIVE_FAILED);

						break;

					}

				} else if (S_ISDIR(st.st_mode)) {

					if (chdir(head) != 0) {

						tail[0] = c;

						fsobj_error(a_eno, a_estr,

						    errno,

						    "Could not chdir %s", path);

						res = (ARCHIVE_FATAL);

						break;

					}

					/*

					 * Our view is now from inside

					 * this dir:

					 */

					head = tail + 1;

				} else {

					tail[0] = c;

					fsobj_error(a_eno, a_estr, 0,

					    "Cannot extract through "

					    "symlink %s", path);

					res = ARCHIVE_FAILED;

					break;

				}

			} else {

				tail[0] = c;

				fsobj_error(a_eno, a_estr, 0,

				    "Cannot extract through symlink %s", path);

				res = ARCHIVE_FAILED;

				break;

			}

		}

		/* be sure to always maintain this */

		tail[0] = c;

		if (tail[0] != '\0')

			tail++; /* Advance to the next segment. */

	}

	/* Catches loop exits via break */

	tail[0] = c;

#ifdef HAVE_FCHDIR

	/* If we changed directory above, restore it here. */

	if (restore_pwd >= 0) {

		r = fchdir(restore_pwd);

		if (r != 0) {

			fsobj_error(a_eno, a_estr, errno,

			    "chdir() failure", "");

		}

		close(restore_pwd);

		restore_pwd = -1;

		if (r != 0) {

			res = (ARCHIVE_FATAL);

		}

	}

#endif

	/* TODO: reintroduce a safe cache here? */

	return res;

#endif

}



/*

 * Check a->name for symlinks, returning ARCHIVE_OK if its clean, otherwise

 * calls archive_set_error and returns ARCHIVE_{FATAL,FAILED}

 */

static int

check_symlinks(struct archive_write_disk *a)

{

	struct archive_string error_string;

	int error_number;

	int rc;

	archive_string_init(&error_string);

	rc = check_symlinks_fsobj(a->name, &error_number, &error_string,

	    a->flags);

	if (rc != ARCHIVE_OK) {

		archive_set_error(&a->archive, error_number, "%s",

		    error_string.s);

	}

	archive_string_free(&error_string);

	a->pst = NULL;	/* to be safe */

	return rc;

}





#if defined(__CYGWIN__)

/*

 * 1. Convert a path separator from '\' to '/' .

