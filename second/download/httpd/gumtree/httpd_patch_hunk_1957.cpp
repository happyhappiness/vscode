  * The -c option causes logresolve to apply the same check as httpd
  * compiled with -DMAXIMUM_DNS; after finding the hostname from the IP
  * address, it looks up the IP addresses for the hostname and checks
  * that one of these matches the original address.
  */
 
+#include "apr.h"
 #include "apr_lib.h"
-#if APR_HAVE_STDIO_H
-#include <stdio.h>
-#endif
+#include "apr_hash.h"
+#include "apr_getopt.h"
+#include "apr_strings.h"
+#include "apr_file_io.h"
+#include "apr_network_io.h"
+
 #if APR_HAVE_STDLIB_H
 #include <stdlib.h>
 #endif
-#if APR_HAVE_CTYPE_H
-#include <ctype.h>
-#endif
-#if APR_HAVE_NETDB_H
-#include <netdb.h>
-#endif
-#if APR_HAVE_NETINET_IN_H
-#include <netinet/in.h>
-#endif
-#if APR_HAVE_STRING_H
-#include <string.h>
-#endif
-#if APR_HAVE_SYS_SOCKET_H
-#include <sys/socket.h>
-#endif
-#if APR_HAVE_ARPA_INET_H
-#include <arpa/inet.h>
-#endif
-
-static void cgethost(struct in_addr ipnum, char *string, int check);
-static int get_line(char *s, int n);
-static void stats(FILE *output);
-
-#ifdef BEOS
-#define NO_ADDRESS NO_DATA
-#endif
-
-
-/* maximum line length */
-#ifndef MAXLINE
-#define MAXLINE 1024
-#endif
-
-/* maximum length of a domain name */
-#ifndef MAXDNAME
-#define MAXDNAME 256
-#endif
-
-/* number of buckets in cache hash apr_table_t */
-#define BUCKETS 256
-
-/*
- * struct nsrec - record of nameservice for cache linked list
- *
- * ipnum - IP number hostname - hostname noname - nonzero if IP number has no
- * hostname, i.e. hostname=IP number
- */
-
-struct nsrec {
-    struct in_addr ipnum;
-    char *hostname;
-    int noname;
-    struct nsrec *next;
-}    *nscache[BUCKETS];
-
-/*
- * statistics - obvious
- */
-
-#ifndef h_errno
-#ifdef __CYGWIN__
-extern __declspec(dllimport) int h_errno;
-#else
-extern int h_errno; /* some machines don't have this in their headers */
-#endif
-#endif
 
-/* largest value for h_errno */
-
-#define MAX_ERR (NO_ADDRESS)
-#define UNKNOWN_ERR (MAX_ERR+1)
-#define NO_REVERSE  (MAX_ERR+2)
+#define READ_BUF_SIZE 10240
+#define WRITE_BUF_SIZE 10240
+#define LINE_BUF_SIZE 2048
+
+static apr_file_t *errfile;
+static const char *shortname = "logresolve";
+static apr_hash_t *cache;
 
+/* Statistics */
 static int cachehits = 0;
 static int cachesize = 0;
 static int entries = 0;
 static int resolves = 0;
 static int withname = 0;
-static int errors[MAX_ERR + 3];
+static int doublefailed = 0;
+static int noreverse = 0;
 
 /*
- * cgethost - gets hostname by IP address, caching, and adding unresolvable
- * IP numbers with their IP number as hostname, setting noname flag
+ * prints various statistics to output
  */
-
-static void cgethost (struct in_addr ipnum, char *string, int check)
+#define NL APR_EOL_STR
+static void print_statistics (apr_file_t *output)
 {
-    struct nsrec **current, *new;
-    struct hostent *hostdata;
-    char *name;
-
-    current = &nscache[((ipnum.s_addr + (ipnum.s_addr >> 8) +
-                         (ipnum.s_addr >> 16) + (ipnum.s_addr >> 24)) % BUCKETS)];
-
-    while (*current != NULL && ipnum.s_addr != (*current)->ipnum.s_addr)
-        current = &(*current)->next;
+    apr_file_printf(output, "logresolve Statistics:" NL);
+    apr_file_printf(output, "Entries: %d" NL, entries);
+    apr_file_printf(output, "    With name   : %d" NL, withname);
+    apr_file_printf(output, "    Resolves    : %d" NL, resolves);
+
+    if (noreverse) {
+        apr_file_printf(output, "    - No reverse : %d" NL,
+                        noreverse);
+    }
 
-    if (*current == NULL) {
-        cachesize++;
-        new = (struct nsrec *) malloc(sizeof(struct nsrec));
-        if (new == NULL) {
-            perror("malloc");
-            fprintf(stderr, "Insufficient memory\n");
-            exit(1);
-        }
-        *current = new;
-        new->next = NULL;
-
-        new->ipnum = ipnum;
-
-        hostdata = gethostbyaddr((const char *) &ipnum, sizeof(struct in_addr),
-                                 AF_INET);
-        if (hostdata == NULL) {
-            if (h_errno > MAX_ERR)
-                errors[UNKNOWN_ERR]++;
-            else
-                errors[h_errno]++;
-            new->noname = h_errno;
-            name = strdup(inet_ntoa(ipnum));
-        }
-        else {
-            new->noname = 0;
-            name = strdup(hostdata->h_name);
-            if (check) {
-                if (name == NULL) {
-                    perror("strdup");
-                    fprintf(stderr, "Insufficient memory\n");
-                    exit(1);
-                }
-                hostdata = gethostbyname(name);
-                if (hostdata != NULL) {
-                    char **hptr;
-
-                    for (hptr = hostdata->h_addr_list; *hptr != NULL; hptr++)
-                        if (((struct in_addr *) (*hptr))->s_addr == ipnum.s_addr)
-                            break;
-                    if (*hptr == NULL)
-                        hostdata = NULL;
-                }
-                if (hostdata == NULL) {
-                    fprintf(stderr, "Bad host: %s != %s\n", name,
-                            inet_ntoa(ipnum));
-                    new->noname = NO_REVERSE;
-                    free(name);
-                    name = strdup(inet_ntoa(ipnum));
-                    errors[NO_REVERSE]++;
-                }
-            }
-        }
-        new->hostname = name;
-        if (new->hostname == NULL) {
-            perror("strdup");
-            fprintf(stderr, "Insufficient memory\n");
-            exit(1);
-        }
+    if (doublefailed) {
+        apr_file_printf(output, "    - Double lookup failed : %d" NL,
+                        doublefailed);
     }
-    else
-        cachehits++;
 
-    /* size of string == MAXDNAME +1 */
-    strncpy(string, (*current)->hostname, MAXDNAME);
-    string[MAXDNAME] = '\0';
+    apr_file_printf(output, "Cache hits      : %d" NL, cachehits);
+    apr_file_printf(output, "Cache size      : %d" NL, cachesize);
 }
 
 /*
- * prints various statistics to output
+ * usage info
  */
-
-static void stats (FILE *output)
+static void usage(void)
 {
-    int i;
-    char *ipstring;
-    struct nsrec *current;
-    char *errstring[MAX_ERR + 3];
-
-    for (i = 0; i < MAX_ERR + 3; i++)
-        errstring[i] = "Unknown error";
-    errstring[HOST_NOT_FOUND] = "Host not found";
-    errstring[TRY_AGAIN] = "Try again";
-    errstring[NO_RECOVERY] = "Non recoverable error";
-    errstring[NO_DATA] = "No data record";
-    errstring[NO_ADDRESS] = "No address";
-    errstring[NO_REVERSE] = "No reverse entry";
-
-    fprintf(output, "logresolve Statistics:\n");
-
-    fprintf(output, "Entries: %d\n", entries);
-    fprintf(output, "    With name   : %d\n", withname);
-    fprintf(output, "    Resolves    : %d\n", resolves);
-    if (errors[HOST_NOT_FOUND])
-        fprintf(output, "    - Not found : %d\n", errors[HOST_NOT_FOUND]);
-    if (errors[TRY_AGAIN])
-        fprintf(output, "    - Try again : %d\n", errors[TRY_AGAIN]);
-    if (errors[NO_DATA])
-        fprintf(output, "    - No data   : %d\n", errors[NO_DATA]);
-    if (errors[NO_ADDRESS])
-        fprintf(output, "    - No address: %d\n", errors[NO_ADDRESS]);
-    if (errors[NO_REVERSE])
-        fprintf(output, "    - No reverse: %d\n", errors[NO_REVERSE]);
-    fprintf(output, "Cache hits      : %d\n", cachehits);
-    fprintf(output, "Cache size      : %d\n", cachesize);
-    fprintf(output, "Cache buckets   :     IP number * hostname\n");
-
-    for (i = 0; i < BUCKETS; i++)
-        for (current = nscache[i]; current != NULL; current = current->next) {
-            ipstring = inet_ntoa(current->ipnum);
-            if (current->noname == 0)
-                fprintf(output, "  %3d  %15s - %s\n", i, ipstring,
-                        current->hostname);
-            else {
-                if (current->noname > MAX_ERR + 2)
-                    fprintf(output, "  %3d  %15s : Unknown error\n", i,
-                            ipstring);
-                else
-                    fprintf(output, "  %3d  %15s : %s\n", i, ipstring,
-                            errstring[current->noname]);
-            }
-        }
+    apr_file_printf(errfile,
+    "%s -- Resolve IP-addresses to hostnames in Apache log files."           NL
+    "Usage: %s [-s STATFILE] [-c]"                                           NL
+                                                                             NL
+    "Options:"                                                               NL
+    "  -s   Record statistics to STATFILE when finished."                    NL
+                                                                             NL
+    "  -c   Perform double lookups when resolving IP addresses."            NL,
+    shortname, shortname);
+    exit(1);
 }
+#undef NL
 
-
-/*
- * gets a line from stdin
- */
-
-static int get_line (char *s, int n)
+int main(int argc, const char * const argv[])
 {
-    char *cp;
+    apr_file_t * outfile;
+    apr_file_t * infile;
+    apr_getopt_t * o;
+    apr_pool_t * pool;
+    apr_pool_t *pline;
+    apr_status_t status;
+    const char * arg;
+    char * stats = NULL;
+    char * inbuffer;
+    char * outbuffer;
+    char line[LINE_BUF_SIZE];
+    int doublelookups = 0;
 
-    if (!fgets(s, n, stdin))
-        return (0);
-    cp = strchr(s, '\n');
-    if (cp)
-        *cp = '\0';
-    return (1);
-}
+    if (apr_app_initialize(&argc, &argv, NULL) != APR_SUCCESS) {
+        return 1;
+    }
+    atexit(apr_terminate);
 
-int main (int argc, char *argv[])
-{
-    struct in_addr ipnum;
-    char *bar, hoststring[MAXDNAME + 1], line[MAXLINE], *statfile;
-    int i, check;
-
-#if defined(WIN32) || (defined(NETWARE) && defined(USE_WINSOCK))
-    /*  If we apr'ify this code, apr_pool_create/apr_pool_destroy
-     *  should perform the WSAStartup/WSACleanup for us.
-     */
-    WSADATA wsaData;
-    WSAStartup(MAKEWORD(2, 0), &wsaData);
-#endif
+    if (argc) {
+        shortname = apr_filepath_name_get(argv[0]);
+    }
 
-    check = 0;
-    statfile = NULL;
-    for (i = 1; i < argc; i++) {
-        if (strcmp(argv[i], "-c") == 0)
-            check = 1;
-        else if (strcmp(argv[i], "-s") == 0) {
-            if (i == argc - 1) {
-                fprintf(stderr, "logresolve: missing filename to -s\n");
-                exit(1);
-            }
-            i++;
-            statfile = argv[i];
+    if (apr_pool_create(&pool, NULL) != APR_SUCCESS) {
+        return 1;
+    }
+    apr_file_open_stderr(&errfile, pool);
+    apr_getopt_init(&o, pool, argc, argv);
+
+    while (1) {
+        char opt;
+        status = apr_getopt(o, "s:c", &opt, &arg);
+        if (status == APR_EOF) {
+            break;
         }
-        else {
-            fprintf(stderr, "Usage: logresolve [-s statfile] [-c] < input > output\n");
-            exit(0);
+        else if (status != APR_SUCCESS) {
+            usage();
         }
+        else {
+            switch (opt) {
+            case 'c':
+                if (doublelookups) {
+                    usage();
+                }
+                doublelookups = 1;
+                break;
+            case 's':
+                if (stats) {
+                    usage();
+                }
+                stats = apr_pstrdup(pool, arg);
+                break;
+            } /* switch */
+        } /* else */
+    } /* while */
+
+    apr_file_open_stdout(&outfile, pool);
+    apr_file_open_stdin(&infile, pool);
+
+    /* Allocate two new 10k file buffers */
+    if ((outbuffer = apr_palloc(pool, WRITE_BUF_SIZE)) == NULL ||
+        (inbuffer = apr_palloc(pool, READ_BUF_SIZE)) == NULL) {
+        return 1;
     }
 
-    for (i = 0; i < BUCKETS; i++)
-        nscache[i] = NULL;
-    for (i = 0; i < MAX_ERR + 2; i++)
-        errors[i] = 0;
+    /* Set the buffers */
+    apr_file_buffer_set(infile, inbuffer, READ_BUF_SIZE);
+    apr_file_buffer_set(outfile, outbuffer, WRITE_BUF_SIZE);
+
+    cache = apr_hash_make(pool);
+    if(apr_pool_create(&pline, pool) != APR_SUCCESS){
+        return 1;
+    }
 
-    while (get_line(line, MAXLINE)) {
-        if (line[0] == '\0')
+    while (apr_file_gets(line, sizeof(line), infile) == APR_SUCCESS) {
+        char *hostname;
+        char *space;
+        apr_sockaddr_t *ip;
+        apr_sockaddr_t *ipdouble;
+        char dummy[] = " " APR_EOL_STR;
+
+        if (line[0] == '\0') {
             continue;
+        }
+
+        /* Count our log entries */
         entries++;
-        if (!apr_isdigit(line[0])) {  /* short cut */
-            puts(line);
-            withname++;
+
+        /* Check if this could even be an IP address */
+        if (!apr_isxdigit(line[0]) && line[0] != ':') {
+                withname++;
+            apr_file_puts(line, outfile);
             continue;
         }
-        bar = strchr(line, ' ');
-        if (bar != NULL)
-            *bar = '\0';
-        ipnum.s_addr = inet_addr(line);
-        if (ipnum.s_addr == 0xffffffffu) {
-            if (bar != NULL)
-                *bar = ' ';
-            puts(line);
+
+        /* Terminate the line at the next space */
+        if ((space = strchr(line, ' ')) != NULL) {
+            *space = '\0';
+        }
+        else {
+            space = dummy;
+        }
+
+        /* See if we have it in our cache */
+        hostname = (char *) apr_hash_get(cache, line, APR_HASH_KEY_STRING);
+        if (hostname) {
+            apr_file_printf(outfile, "%s %s", hostname, space + 1);
+            cachehits++;
+            continue;
+        }
+
+        /* Parse the IP address */
+        status = apr_sockaddr_info_get(&ip, line, APR_UNSPEC, 0, 0, pline);
+        if (status != APR_SUCCESS) {
+            /* Not an IP address */
             withname++;
+            *space = ' ';
+            apr_file_puts(line, outfile);
             continue;
         }
 
+        /* This does not make much sense, but historically "resolves" means
+         * "parsed as an IP address". It does not mean we actually resolved
+         * the IP address into a hostname.
+         */
         resolves++;
 
-        cgethost(ipnum, hoststring, check);
-        if (bar != NULL)
-            printf("%s %s\n", hoststring, bar + 1);
-        else
-            puts(hoststring);
+        /* From here on our we cache each result, even if it was not
+         * succesful
+         */
+        cachesize++;
+
+        /* Try and perform a reverse lookup */
+        status = apr_getnameinfo(&hostname, ip, 0) != APR_SUCCESS;
+        if (status || hostname == NULL) {
+            /* Could not perform a reverse lookup */
+            *space = ' ';
+            apr_file_puts(line, outfile);
+            noreverse++;
+
+            /* Add to cache */
+            *space = '\0';
+            apr_hash_set(cache, line, APR_HASH_KEY_STRING,
+                         apr_pstrdup(apr_hash_pool_get(cache), line));
+            continue;
+        }
+
+        /* Perform a double lookup */
+        if (doublelookups) {
+            /* Do a forward lookup on our hostname, and see if that matches our
+             * original IP address.
+             */
+            status = apr_sockaddr_info_get(&ipdouble, hostname, ip->family, 0,
+                                           0, pline);
+            if (status == APR_SUCCESS ||
+                memcmp(ipdouble->ipaddr_ptr, ip->ipaddr_ptr, ip->ipaddr_len)) {
+                /* Double-lookup failed  */
+                *space = ' ';
+                apr_file_puts(line, outfile);
+                doublefailed++;
+
+                /* Add to cache */
+                *space = '\0';
+                apr_hash_set(cache, line, APR_HASH_KEY_STRING,
+                             apr_pstrdup(apr_hash_pool_get(cache), line));
+                continue;
+            }
+        }
+
+        /* Outout the resolved name */
+        apr_file_printf(outfile, "%s %s", hostname, space + 1);
+
+        /* Store it in the cache */
+        apr_hash_set(cache, line, APR_HASH_KEY_STRING,
+                     apr_pstrdup(apr_hash_pool_get(cache), hostname));
+
+        apr_pool_clear(pline);
     }
 
-#if defined(WIN32) || (defined(NETWARE) && defined(USE_WINSOCK))
-     WSACleanup();
-#endif
+    /* Flush any remaining output */
+    apr_file_flush(outfile);
 
-    if (statfile != NULL) {
-        FILE *fp;
-        fp = fopen(statfile, "w");
-        if (fp == NULL) {
-            fprintf(stderr, "logresolve: could not open statistics file '%s'\n"
-                    ,statfile);
-            exit(1);
+    if (stats) {
+        apr_file_t *statsfile;
+        if (apr_file_open(&statsfile, stats,
+                       APR_FOPEN_WRITE | APR_FOPEN_CREATE | APR_FOPEN_TRUNCATE,
+                          APR_OS_DEFAULT, pool) != APR_SUCCESS) {
+            apr_file_printf(errfile, "%s: Could not open %s for writing.",
+                            shortname, stats);
+            return 1;
         }
-        stats(fp);
-        fclose(fp);
+        print_statistics(statsfile);
+        apr_file_close(statsfile);
     }
 
-    return (0);
+    return 0;
 }
