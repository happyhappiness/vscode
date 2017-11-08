char *safe_fname(const char *fname)
{
#define MAX_SAFE_NAMES 4
	static char fbuf[MAX_SAFE_NAMES][MAXPATHLEN*2];
	static int ndx = 0;
	int limit = sizeof fbuf / MAX_SAFE_NAMES - 1;
	char *t;

	ndx = (ndx + 1) % MAX_SAFE_NAMES;
	for (t = fbuf[ndx]; *fname; fname++) {
		if (*fname == '\\') {
			if ((limit -= 2) < 0)
				break;
			*t++ = '\\';
			*t++ = '\\';
		} else if (!isprint(*(uchar*)fname)) {
			if ((limit -= 4) < 0)
				break;
			sprintf(t, "\\%03o", *(uchar*)fname);
			t += 4;
		} else {
			if (--limit < 0)
				break;
			*t++ = *fname;
		}
	}
	*t = '\0';

	return fbuf[ndx];
}