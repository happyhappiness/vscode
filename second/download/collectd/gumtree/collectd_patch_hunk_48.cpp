 # include <netinet/ip6.h>
 #endif
 #if HAVE_NETINET_ICMP6_H
 # include <netinet/icmp6.h>
 #endif
 
-#include "liboping.h"
+#include "oping.h"
 
-#if DEBUG
+#if WITH_DEBUG
 # define dprintf(...) printf ("%s[%4i]: %-20s: ", __FILE__, __LINE__, __FUNCTION__); printf (__VA_ARGS__)
 #else
 # define dprintf(...) /**/
 #endif
 
-#define PING_DATA "Florian Forster <octo@verplant.org> http://verplant.org/"
+#define PING_ERRMSG_LEN 256
+
+struct pinghost
+{
+	char                    *hostname;
+	struct sockaddr_storage *addr;
+	socklen_t                addrlen;
+	int                      addrfamily;
+	int                      fd;
+	int                      ident;
+	int                      sequence;
+	struct timeval          *timer;
+	double                   latency;
+	char                    *data;
+
+	void                    *context;
+
+	struct pinghost         *next;
+};
+
+struct pingobj
+{
+	double      timeout;
+	int         ttl;
+	int         addrfamily;
+	char       *data;
+
+	char        errmsg[PING_ERRMSG_LEN];
+
+	pinghost_t *head;
+};
 
 /*
  * private (static) functions
  */
+static void ping_set_error (pingobj_t *obj, const char *function,
+	       	const char *message)
+{
+	snprintf (obj->errmsg, PING_ERRMSG_LEN, "%s: %s", function, message);
+	obj->errmsg[PING_ERRMSG_LEN - 1] = '\0';
+}
+
 static int ping_timeval_add (struct timeval *tv1, struct timeval *tv2,
 		struct timeval *res)
 {
 	res->tv_sec  = tv1->tv_sec  + tv2->tv_sec;
 	res->tv_usec = tv1->tv_usec + tv2->tv_usec;
 
