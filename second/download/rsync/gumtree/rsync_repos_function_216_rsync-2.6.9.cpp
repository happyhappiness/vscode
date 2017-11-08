static void filtered_fwrite(FILE *f, const char *buf, int len, int use_isprint)
{
	const char *s, *end = buf + len;
	for (s = buf; s < end; s++) {
		if ((s < end - 4
		  && *s == '\\' && s[1] == '#'
		  && isdigit(*(uchar*)(s+2))
		  && isdigit(*(uchar*)(s+3))
		  && isdigit(*(uchar*)(s+4)))
		 || (*s != '\t'
		  && ((use_isprint && !isprint(*(uchar*)s))
		   || *(uchar*)s < ' '))) {
			if (s != buf && fwrite(buf, s - buf, 1, f) != 1)
				exit_cleanup(RERR_MESSAGEIO);
			fprintf(f, "\\#%03o", *(uchar*)s);
			buf = s + 1;
		}
	}
	if (buf != end && fwrite(buf, end - buf, 1, f) != 1)
		exit_cleanup(RERR_MESSAGEIO);
}