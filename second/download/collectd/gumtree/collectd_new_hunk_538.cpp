
#define LCC_SET_ERRSTR(c, ...) do { \
  snprintf ((c)->errbuf, sizeof ((c)->errbuf), __VA_ARGS__); \
  (c)->errbuf[sizeof ((c)->errbuf) - 1] = 0; \
} while (0)

/*
 * Types
 */
struct lcc_connection_s
{
  FILE *fh;
