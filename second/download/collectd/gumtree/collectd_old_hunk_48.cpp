# include <netinet/ip6.h>
#endif
#if HAVE_NETINET_ICMP6_H
# include <netinet/icmp6.h>
#endif

#include "liboping.h"

#if DEBUG
# define dprintf(...) printf ("%s[%4i]: %-20s: ", __FILE__, __LINE__, __FUNCTION__); printf (__VA_ARGS__)
#else
# define dprintf(...) /**/
#endif

#define PING_DATA "Florian Forster <octo@verplant.org> http://verplant.org/"

/*
 * private (static) functions
 */
static int ping_timeval_add (struct timeval *tv1, struct timeval *tv2,
		struct timeval *res)
{
	res->tv_sec  = tv1->tv_sec  + tv2->tv_sec;
	res->tv_usec = tv1->tv_usec + tv2->tv_usec;

