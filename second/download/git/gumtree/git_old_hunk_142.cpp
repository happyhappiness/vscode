	for (; *path; ++path)
		if (is_dir_sep(*path))
			ret = (char *)path;
	return ret;
}
#define find_last_dir_sep mingw_find_last_dir_sep
#define PATH_SEP ';'
#define PRIuMAX "I64u"
#define PRId64 "I64d"

void mingw_open_html(const char *path);
#define open_html mingw_open_html

/*
 * helpers
 */

char **make_augmented_environ(const char *const *vars);
void free_environ(char **env);

/*
 * A critical section used in the implementation of the spawn
 * functions (mingw_spawnv[p]e()) and waitpid(). Intialised in
 * the replacement main() macro below.
 */
extern CRITICAL_SECTION pinfo_cs;

/*
 * A replacement of main() that ensures that argv[0] has a path
 * and that default fmode and std(in|out|err) are in binary mode
 */

#define main(c,v) dummy_decl_mingw_main(); \
static int mingw_main(c,v); \
int main(int argc, char **argv) \
{ \
	extern CRITICAL_SECTION pinfo_cs; \
	_fmode = _O_BINARY; \
	_setmode(_fileno(stdin), _O_BINARY); \
	_setmode(_fileno(stdout), _O_BINARY); \
	_setmode(_fileno(stderr), _O_BINARY); \
	argv[0] = xstrdup(_pgmptr); \
	InitializeCriticalSection(&pinfo_cs); \
	return mingw_main(argc, argv); \
} \
static int mingw_main(c,v)

/*
 * Used by Pthread API implementation for Windows
 */
