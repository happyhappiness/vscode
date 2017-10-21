 * This file contains really simple implementations for rsync global
 * functions, so that module test harnesses can run standalone.
 **/

int modify_window = 0;
int module_id = -1;
struct exclude_list_struct server_exclude_list;

 void rprintf(UNUSED(enum logcode code), const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
}

 void _exit_cleanup(int code, const char *file, int line)
{
	fprintf(stderr, "exit(%d): %s(%d)\n",
		code, file, line);
	exit(code);
}
