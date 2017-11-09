static void emit_add_line(const char *reset,
			  struct emit_callback *ecbdata,
			  const char *line, int len)
{
	emit_line_checked(reset, ecbdata, line, len,
			  DIFF_FILE_NEW, WSEH_NEW, '+');
}