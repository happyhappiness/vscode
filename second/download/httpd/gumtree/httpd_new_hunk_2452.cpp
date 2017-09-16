#endif

#ifdef    S_IFLNK

    case S_IFLNK:

	/* We used stat(), the only possible reason for this is that the

	 * symlink is broken.

	 */

	ap_log_rerror(APLOG_MARK, APLOG_NOERRNO | APLOG_ERR, r,

		    MODNAME ": broken symlink (%s)", fn);

	return HTTP_INTERNAL_SERVER_ERROR;

#endif

#ifdef    S_IFSOCK

#ifndef __COHERENT__

    case S_IFSOCK:

