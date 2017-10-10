/*
 * Copyright (c) 2005, Junio C Hamano
 */
#include "cache.h"
#include "sigchain.h"

static struct lock_file *lock_file_list;

static void remove_lock_file(void)
{
	pid_t me = getpid();

	while (lock_file_list) {
		if (lock_file_list->owner == me &&
		    lock_file_list->filename[0]) {
			if (lock_file_list->fd >= 0)
				close(lock_file_list->fd);
			unlink_or_warn(lock_file_list->filename);
		}
		lock_file_list = lock_file_list->next;
	}
}

static void remove_lock_file_on_signal(int signo)
{
	remove_lock_file();
	sigchain_pop(signo);
	raise(signo);
}

/*
 * p = absolute or relative path name
 *
 * Return a pointer into p showing the beginning of the last path name
 * element.  If p is empty or the root directory ("/"), just return p.
 */
static char *last_path_elm(char *p)
{
	/* r starts pointing to null at the end of the string */
	char *r = strchr(p, '\0');

	if (r == p)
		return p; /* just return empty string */

	r--; /* back up to last non-null character */

	/* back up past trailing slashes, if any */
	while (r > p && *r == '/')
		r--;

	/*
	 * then go backwards until I hit a slash, or the beginning of
	 * the string
	 */
	while (r > p && *(r-1) != '/')
		r--;
	return r;
}


/* We allow "recursive" symbolic links. Only within reason, though */
#define MAXDEPTH 5

/*
 * p = path that may be a symlink
 * s = full size of p
 *
 * If p is a symlink, attempt to overwrite p with a path to the real
 * file or directory (which may or may not exist), following a chain of
 * symlinks if necessary.  Otherwise, leave p unmodified.
 *
 * This is a best-effort routine.  If an error occurs, p will either be
 * left unmodified or will name a different symlink in a symlink chain
 * that started with p's initial contents.
 *
 * Always returns p.
 */

static char *resolve_symlink(char *p, size_t s)
{
	int depth = MAXDEPTH;

	while (depth--) {
		char link[PATH_MAX];
		int link_len = readlink(p, link, sizeof(link));
		if (link_len < 0) {
			/* not a symlink anymore */
			return p;
		}
		else if (link_len < sizeof(link))
			/* readlink() never null-terminates */
			link[link_len] = '\0';
		else {
			warning("%s: symlink too long", p);
			return p;
		}

		if (is_absolute_path(link)) {
			/* absolute path simply replaces p */
			if (link_len < s)
				strcpy(p, link);
			else {
				warning("%s: symlink too long", p);
				return p;
			}
		} else {
			/*
			 * link is a relative path, so I must replace the
			 * last element of p with it.
			 */
			char *r = (char *)last_path_elm(p);
			if (r - p + link_len < s)
				strcpy(r, link);
			else {
				warning("%s: symlink too long", p);
				return p;
			}
		}
	}
	return p;
}

/* Make sure errno contains a meaningful value on error */
static int lock_file(struct lock_file *lk, const char *path, int flags)
{
	/*
	 * subtract 5 from size to make sure there's room for adding
	 * ".lock" for the lock file name
	 */
	static const size_t max_path_len = sizeof(lk->filename) - 5;

	if (strlen(path) >= max_path_len) {
		errno = ENAMETOOLONG;
		return -1;
	}
	strcpy(lk->filename, path);
	if (!(flags & LOCK_NODEREF))
		resolve_symlink(lk->filename, max_path_len);
	strcat(lk->filename, ".lock");
	lk->fd = open(lk->filename, O_RDWR | O_CREAT | O_EXCL, 0666);
	if (0 <= lk->fd) {
		if (!lock_file_list) {
			sigchain_push_common(remove_lock_file_on_signal);
			atexit(remove_lock_file);
		}
		lk->owner = getpid();
		if (!lk->on_list) {
			lk->next = lock_file_list;
			lock_file_list = lk;
			lk->on_list = 1;
		}
		if (adjust_shared_perm(lk->filename)) {
			int save_errno = errno;
			error("cannot fix permission bits on %s",
			      lk->filename);
			errno = save_errno;
			return -1;
		}
	}
	else
		lk->filename[0] = 0;
	return lk->fd;
}

void unable_to_lock_message(const char *path, int err, struct strbuf *buf)
{
	if (err == EEXIST) {
