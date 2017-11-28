#if HAVE_NET_PFVAR_H
#include <net/pfvar.h>
#endif /* HAVE_NET_PFVAR_H */
#endif /* PF_TRANSPARENT required headers */

#if LINUX_NETFILTER
#include <linux/netfilter_ipv4.h>
#endif

// single global instance for access by other components.
Ip::Intercept Ip::Interceptor;

void
Ip::Intercept::StopTransparency(const char *str)
