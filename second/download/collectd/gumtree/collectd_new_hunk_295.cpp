#define DEBUGP_C(x, args...)	fprintf(stderr, x, ## args)
#else
#define DEBUGP(x, args...)
#define DEBUGP_C(x, args...)
#endif

#ifdef DEBUG
#define debug(x, args...)	fprintf(stderr, x, ## args)
#else
#define debug(x, args...)
#endif

static int sockfd = -1;
static int sockfd_use = 0;
static void *iptc_fn = NULL;

