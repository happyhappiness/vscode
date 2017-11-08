int set_modtime(const char *fname, time_t modtime, mode_t mode)
{
	static int switch_step = 0;

	if (verbose > 2) {
		rprintf(FINFO, "set modtime of %s to (%ld) %s",
			fname, (long)modtime,
			asctime(localtime(&modtime)));
	}

	switch (switch_step) {
#ifdef HAVE_UTIMENSAT
#include "case_N.h"
		if (do_utimensat(fname, modtime, 0) == 0)
			break;
		if (errno != ENOSYS)
			return -1;
		switch_step++;
		/* FALLTHROUGH */
#endif

#ifdef HAVE_LUTIMES
#include "case_N.h"
		if (do_lutimes(fname, modtime, 0) == 0)
			break;
		if (errno != ENOSYS)
			return -1;
		switch_step++;
		/* FALLTHROUGH */
#endif

#include "case_N.h"
		switch_step++;
		if (preserve_times & PRESERVE_LINK_TIMES) {
			preserve_times &= ~PRESERVE_LINK_TIMES;
			if (S_ISLNK(mode))
				return 1;
		}
		/* FALLTHROUGH */

#include "case_N.h"
#ifdef HAVE_UTIMES
		if (do_utimes(fname, modtime, 0) == 0)
			break;
#else
		if (do_utime(fname, modtime, 0) == 0)
			break;
#endif

		return -1;
	}

	return 0;
}