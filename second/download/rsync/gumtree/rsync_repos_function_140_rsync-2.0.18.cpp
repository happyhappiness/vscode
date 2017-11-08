int vslprintf(char *str, int n, const char *format, va_list ap)
{
#ifdef HAVE_VSNPRINTF
	int ret = vsnprintf(str, n, format, ap);
	if (ret > n || ret < 0) {
		str[n] = 0;
		return -1;
	}
	str[ret] = 0;
	return ret;
#else
	static char *buf;
	static int len=MAXPATHLEN*8;
	int ret;

	/* this code is NOT a proper vsnprintf() implementation. It
	   relies on the fact that all calls to slprintf() in rsync
	   pass strings which have already been checked to be less
	   than MAXPATHLEN in length and never more than 2 strings are
	   concatenated. This means the above buffer is absolutely
	   ample and can never be overflowed.

	   In the future we would like to replace this with a proper
	   vsnprintf() implementation but right now we need a solution
	   that is secure and portable. This is it.  */

	if (!buf) {
		buf = malloc(len);
		if (!buf) {
			/* can't call debug or we would recurse */
			exit_cleanup(1);
		}
	}

	vsprintf(buf, format, ap);
	ret = strlen(buf);
	if (ret > n) {
		/* yikes! */
		exit_cleanup(1);
	}
	buf[ret] = 0;
	
	memcpy(str, buf, ret+1);

	return ret;
#endif
}