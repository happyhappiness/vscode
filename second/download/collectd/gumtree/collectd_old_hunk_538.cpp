
#define LCC_SET_ERRSTR(c, ...) do { \
  snprintf ((c)->errbuf, sizeof ((c)->errbuf), __VA_ARGS__); \
  (c)->errbuf[sizeof ((c)->errbuf) - 1] = 0; \
} while (0)

#if COLLECT_DEBUG
# define LCC_DEBUG(...) printf (__VA_ARGS__)
#else
# define LCC_DEBUG(...) /**/
#endif

/*
 * Types
 */
struct lcc_connection_s
{
  FILE *fh;
