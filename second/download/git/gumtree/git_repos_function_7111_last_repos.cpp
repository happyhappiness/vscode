static void write_item(const char *what, LPCWSTR wbuf, int wlen)
{
	char *buf;
	int len = WideCharToMultiByte(CP_UTF8, 0, wbuf, wlen, NULL, 0, NULL,
	    FALSE);
	buf = xmalloc(len);

	if (!WideCharToMultiByte(CP_UTF8, 0, wbuf, wlen, buf, len, NULL, FALSE))
		die("WideCharToMultiByte failed!");

	printf("%s=", what);
	fwrite(buf, 1, len, stdout);
	putchar('\n');
	free(buf);
}