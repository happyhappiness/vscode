/*
 * Copyright (c) 2005, Junio C Hamano
 */
#include "cache.h"
#include "lockfile.h"
#include "sigchain.h"

static struct lock_file *volatile lock_file_list;

static void remove_lock_files(int skip_fclose)
{
	pid_t me = getpid();

	while (lock_file_list) {
		if (lock_file_list->owner == me) {
			/* fclose() is not safe to call in a signal handler */
			if (skip_fclose)
				lock_file_list->fp = NULL;
			rollback_lock_file(lock_file_list);
		}
		lock_file_list = lock_file_list->next;
	}
}

static void remove_lock_files_on_exit(void)
{
	remove_lock_files(0);
}

static void remove_lock_files_on_signal(int signo)
{
	remove_lock_files(1);
	sigchain_pop(signo);
	raise(signo);
}

/*
 * path = absolute or relative path name
 *
 * Remove the last path name element from path (leaving the preceding
 * "/", if any).  If path is empty or the root directory ("/"), set
 * path to the empty string.
 */
static void trim_last_path_component(struct strbuf *path)
{
	int i = path->len;

	/* back up past trailing slashes, if any */
	while (i && path->buf[i - 1] == '/')
		i--;

	/*
	 * then go backwards until a slash, or the beginning of the
	 * string
	 */
	while (i && path->buf[i - 1] != '/')
		i--;

	strbuf_setlen(path, i);
}


/* We allow "recursive" symbolic links. Only within reason, though */
#define MAXDEPTH 5

/*
 * path contains a path that might be a symlink.
 *
 * If path is a symlink, attempt to overwrite it with a path to the
 * real file or directory (which may or may not exist), following a
 * chain of symlinks if necessary.  Otherwise, leave path unmodified.
 *
 * This is a best-effort routine.  If an error occurs, path will
 * either be left unmodified or will name a different symlink in a
 * symlink chain that started with the original path.
 */
static void resolve_symlink(struct strbuf *path)
{
	int depth = MAXDEPTH;
	static struct strbuf link = STRBUF_INIT;

	while (depth--) {
		if (strbuf_readlink(&link, path->buf, path->len) < 0)
			break;

		if (is_absolute_path(link.buf))
			/* absolute path simply replaces p */
			strbuf_reset(path);
		else
			/*
			 * link is a relative path, so replace the
			 * last element of p with it.
			 */
			trim_last_path_component(path);

		strbuf_addbuf(path, &link);
	}
	strbuf_reset(&link);
}

/* Make sure errno contains a meaningful value on error */
static int lock_file(struct lock_file *lk, const char *path, int flags)
{
	size_t pathlen = strlen(path);

	if (!lock_file_list) {
		/* One-time initialization */
		sigchain_push_common(remove_lock_files_on_signal);
		atexit(remove_lock_files_on_exit);
	}

	if (lk->active)
		die("BUG: cannot lock_file(\"%s\") using active struct lock_file",
		    path);
	if (!lk->on_list) {
		/* Initialize *lk and add it to lock_file_list: */
		lk->fd = -1;
		lk->fp = NULL;
		lk->active = 0;
		lk->owner = 0;
		strbuf_init(&lk->filename, pathlen + LOCK_SUFFIX_LEN);
		lk->next = lock_file_list;
		lock_file_list = lk;
		lk->on_list = 1;
	} else if (lk->filename.len) {
		/* This shouldn't happen, but better safe than sorry. */
		die("BUG: lock_file(\"%s\") called with improperly-reset lock_file object",
		    path);
	}

	strbuf_add(&lk->filename, path, pathlen);
	if (!(flags & LOCK_NO_DEREF))
		resolve_symlink(&lk->filename);
	strbuf_addstr(&lk->filename, LOCK_SUFFIX);
	lk->fd = open(lk->filename.buf, O_RDWR | O_CREAT | O_EXCL, 0666);
	if (lk->fd < 0) {
		strbuf_reset(&lk->filename);
		return -1;
	}
	lk->owner = getpid();
	lk->active = 1;
	if (adjust_shared_perm(lk->filename.buf)) {
		int save_errno = errno;
		error("cannot fix permission bits on %s", lk->filename.buf);
		rollback_lock_file(lk);
		errno = save_errno;
		return -1;
	}
	return lk->fd;
}

void unable_to_lock_message(const char *path, int err, struct strbuf *buf)
{
	if (err == EEXIST) {
