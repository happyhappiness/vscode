			DUPLICATE_SAME_ACCESS))
		die_lasterr("DuplicateHandle(%li) failed",
			(long) (intptr_t) hnd);
	return hresult;
}

static HANDLE swap_osfhnd(int fd, HANDLE new_handle)
{
	/*
	 * Create a copy of the original handle associated with fd
	 * because the original will get closed when we dup2().
	 */
	HANDLE handle = (HANDLE)_get_osfhandle(fd);
	HANDLE duplicate = duplicate_handle(handle);

	/* Create a temp fd associated with the already open "new_handle". */
	int new_fd = _open_osfhandle((intptr_t)new_handle, O_BINARY);

	assert((fd == 1) || (fd == 2));

	/*
	 * Use stock dup2() to re-bind fd to the new handle.  Note that
	 * this will implicitly close(1) and close both fd=1 and the
	 * originally associated handle.  It will open a new fd=1 and
	 * call DuplicateHandle() on the handle associated with new_fd.
	 * It is because of this implicit close() that we created the
	 * copy of the original.
	 *
	 * Note that we need to update the cached console handle to the
	 * duplicated one because the dup2() call will implicitly close
	 * the original one.
	 *
	 * Note that dup2() when given target := {0,1,2} will also
	 * call SetStdHandle(), so we don't need to worry about that.
	 */
	if (console == handle)
		console = duplicate;
	dup2(new_fd, fd);

	/* Close the temp fd.  This explicitly closes "new_handle"
	 * (because it has been associated with it).
	 */
	close(new_fd);

	fd_is_interactive[fd] |= FD_SWAPPED;

	return duplicate;
}

#ifdef DETECT_MSYS_TTY

#include <winternl.h>
#include <ntstatus.h>
