-/* Licensed to the Apache Software Foundation (ASF) under one or more
- * contributor license agreements.  See the NOTICE file distributed with
- * this work for additional information regarding copyright ownership.
- * The ASF licenses this file to You under the Apache License, Version 2.0
- * (the "License"); you may not use this file except in compliance with
- * the License.  You may obtain a copy of the License at
+/* Copyright 1999-2005 The Apache Software Foundation or its licensors, as
+ * applicable.
+ *
+ * Licensed under the Apache License, Version 2.0 (the "License");
+ * you may not use this file except in compliance with the License.
+ * You may obtain a copy of the License at
  *
  *     http://www.apache.org/licenses/LICENSE-2.0
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  */
 
 /*                       _                            _ _
-**   _ __ ___   ___   __| |    _ __ _____      ___ __(_) |_ ___
-**  | '_ ` _ \ / _ \ / _` |   | '__/ _ \ \ /\ / / '__| | __/ _ \
-**  | | | | | | (_) | (_| |   | | |  __/\ V  V /| |  | | ||  __/
-**  |_| |_| |_|\___/ \__,_|___|_|  \___| \_/\_/ |_|  |_|\__\___|
-**                       |_____|
-**
-**  URL Rewriting Module
-**
-**  This module uses a rule-based rewriting engine (based on a
-**  regular-expression parser) to rewrite requested URLs on the fly.
-**
-**  It supports an unlimited number of additional rule conditions (which can
-**  operate on a lot of variables, even on HTTP headers) for granular
-**  matching and even external database lookups (either via plain text
-**  tables, DBM hash files or even external processes) for advanced URL
-**  substitution.
-**
-**  It operates on the full URLs (including the PATH_INFO part) both in
-**  per-server context (httpd.conf) and per-dir context (.htaccess) and even
-**  can generate QUERY_STRING parts on result.   The rewriting result finally
-**  can lead to internal subprocessing, external request redirection or even
-**  to internal proxy throughput.
-**
-**  This module was originally written in April 1996 and
-**  gifted exclusively to the The Apache Software Foundation in July 1997 by
-**
-**      Ralf S. Engelschall
-**      rse engelschall.com
-**      www.engelschall.com
-*/
+ *   _ __ ___   ___   __| |    _ __ _____      ___ __(_) |_ ___
+ *  | '_ ` _ \ / _ \ / _` |   | '__/ _ \ \ /\ / / '__| | __/ _ \
+ *  | | | | | | (_) | (_| |   | | |  __/\ V  V /| |  | | ||  __/
+ *  |_| |_| |_|\___/ \__,_|___|_|  \___| \_/\_/ |_|  |_|\__\___|
+ *                       |_____|
+ *
+ *  URL Rewriting Module
+ *
+ *  This module uses a rule-based rewriting engine (based on a
+ *  regular-expression parser) to rewrite requested URLs on the fly.
+ *
+ *  It supports an unlimited number of additional rule conditions (which can
+ *  operate on a lot of variables, even on HTTP headers) for granular
+ *  matching and even external database lookups (either via plain text
+ *  tables, DBM hash files or even external processes) for advanced URL
+ *  substitution.
+ *
+ *  It operates on the full URLs (including the PATH_INFO part) both in
+ *  per-server context (httpd.conf) and per-dir context (.htaccess) and even
+ *  can generate QUERY_STRING parts on result.   The rewriting result finally
+ *  can lead to internal subprocessing, external request redirection or even
+ *  to internal proxy throughput.
+ *
+ *  This module was originally written in April 1996 and
+ *  gifted exclusively to the The Apache Software Foundation in July 1997 by
+ *
+ *      Ralf S. Engelschall
+ *      rse engelschall.com
+ *      www.engelschall.com
+ */
 
 #include "apr.h"
 #include "apr_strings.h"
 #include "apr_hash.h"
 #include "apr_user.h"
 #include "apr_lib.h"
 #include "apr_signal.h"
 #include "apr_global_mutex.h"
+#include "apr_dbm.h"
 
+#if APR_HAS_THREADS
+#include "apr_thread_mutex.h"
+#endif
+
+#define APR_WANT_MEMFUNC
 #define APR_WANT_STRFUNC
 #define APR_WANT_IOVEC
 #include "apr_want.h"
 
+/* XXX: Do we really need these headers? */
 #if APR_HAVE_UNISTD_H
 #include <unistd.h>
 #endif
 #if APR_HAVE_SYS_TYPES_H
 #include <sys/types.h>
 #endif
+#if APR_HAVE_STDARG_H
+#include <stdarg.h>
+#endif
+#if APR_HAVE_STDLIB_H
+#include <stdlib.h>
+#endif
+#if APR_HAVE_CTYPE_H
+#include <ctype.h>
+#endif
 
 #include "ap_config.h"
 #include "httpd.h"
 #include "http_config.h"
 #include "http_request.h"
 #include "http_core.h"
 #include "http_log.h"
 #include "http_protocol.h"
-#include "mod_rewrite.h"
+#include "http_vhost.h"
+
+#include "mod_ssl.h"
 
-/* mod_ssl.h is not safe for inclusion in 2.0, so duplicate the
- * optional function declarations. */
-APR_DECLARE_OPTIONAL_FN(char *, ssl_var_lookup,
-                        (apr_pool_t *, server_rec *,
-                         conn_rec *, request_rec *,
-                         char *));
-APR_DECLARE_OPTIONAL_FN(int, ssl_is_https, (conn_rec *));
+#include "mod_rewrite.h"
 
-#if !defined(OS2) && !defined(WIN32) && !defined(BEOS)  && !defined(NETWARE)
+#ifdef AP_NEED_SET_MUTEX_PERMS
 #include "unixd.h"
-#define MOD_REWRITE_SET_MUTEX_PERMS /* XXX Apache should define something */
 #endif
 
 /*
-** +-------------------------------------------------------+
-** |                                                       |
-** |             static module configuration
-** |                                                       |
-** +-------------------------------------------------------+
-*/
+ * in order to improve performance on running production systems, you
+ * may strip all rewritelog code entirely from mod_rewrite by using the
+ * -DREWRITELOG_DISABLED compiler option.
+ *
+ * DO NOT USE THIS OPTION FOR PUBLIC BINARY RELEASES. Otherwise YOU are
+ * responsible for answering all the mod_rewrite questions out there.
+ */
+#ifndef REWRITELOG_DISABLED
+
+#define rewritelog(x) do_rewritelog x
+#define REWRITELOG_MODE  ( APR_UREAD | APR_UWRITE | APR_GREAD | APR_WREAD )
+#define REWRITELOG_FLAGS ( APR_WRITE | APR_APPEND | APR_CREATE )
+
+#else /* !REWRITELOG_DISABLED */
+
+#define rewritelog(x)
+
+#endif /* REWRITELOG_DISABLED */
+
+/* remembered mime-type for [T=...] */
+#define REWRITE_FORCED_MIMETYPE_NOTEVAR "rewrite-forced-mimetype"
+#define REWRITE_FORCED_HANDLER_NOTEVAR  "rewrite-forced-handler"
+
+#define ENVVAR_SCRIPT_URL "SCRIPT_URL"
+#define REDIRECT_ENVVAR_SCRIPT_URL "REDIRECT_" ENVVAR_SCRIPT_URL
+#define ENVVAR_SCRIPT_URI "SCRIPT_URI"
+
+#define CONDFLAG_NONE               1<<0
+#define CONDFLAG_NOCASE             1<<1
+#define CONDFLAG_NOTMATCH           1<<2
+#define CONDFLAG_ORNEXT             1<<3
+
+#define RULEFLAG_NONE               1<<0
+#define RULEFLAG_FORCEREDIRECT      1<<1
+#define RULEFLAG_LASTRULE           1<<2
+#define RULEFLAG_NEWROUND           1<<3
+#define RULEFLAG_CHAIN              1<<4
+#define RULEFLAG_IGNOREONSUBREQ     1<<5
+#define RULEFLAG_NOTMATCH           1<<6
+#define RULEFLAG_PROXY              1<<7
+#define RULEFLAG_PASSTHROUGH        1<<8
+#define RULEFLAG_QSAPPEND           1<<9
+#define RULEFLAG_NOCASE             1<<10
+#define RULEFLAG_NOESCAPE           1<<11
+#define RULEFLAG_NOSUB              1<<12
+#define RULEFLAG_STATUS             1<<13
+
+/* return code of the rewrite rule
+ * the result may be escaped - or not
+ */
+#define ACTION_NORMAL               1<<0
+#define ACTION_NOESCAPE             1<<1
+#define ACTION_STATUS               1<<2
+
+
+#define MAPTYPE_TXT                 1<<0
+#define MAPTYPE_DBM                 1<<1
+#define MAPTYPE_PRG                 1<<2
+#define MAPTYPE_INT                 1<<3
+#define MAPTYPE_RND                 1<<4
+
+#define ENGINE_DISABLED             1<<0
+#define ENGINE_ENABLED              1<<1
+
+#define OPTION_NONE                 1<<0
+#define OPTION_INHERIT              1<<1
+
+#ifndef RAND_MAX
+#define RAND_MAX 32767
+#endif
+
+/* max cookie size in rfc 2109 */
+/* XXX: not used at all. We should do a check somewhere and/or cut the cookie */
+#define MAX_COOKIE_LEN 4096
+
+/* max line length (incl.\n) in text rewrite maps */
+#ifndef REWRITE_MAX_TXT_MAP_LINE
+#define REWRITE_MAX_TXT_MAP_LINE 1024
+#endif
+
+/* buffer length for prg rewrite maps */
+#ifndef REWRITE_PRG_MAP_BUF
+#define REWRITE_PRG_MAP_BUF 1024
+#endif
+
+/* for better readbility */
+#define LEFT_CURLY  '{'
+#define RIGHT_CURLY '}'
+
+/*
+ * expansion result items on the stack to save some cycles
+ *
+ * (5 == about 2 variables like "foo%{var}bar%{var}baz")
+ */
+#define SMALL_EXPANSION 5
+
+/*
+ * check that a subrequest won't cause infinite recursion
+ *
+ * either not in a subrequest, or in a subrequest
+ * and URIs aren't NULL and sub/main URIs differ
+ */
+#define subreq_ok(r) (!r->main || \
+    (r->main->uri && r->uri && strcmp(r->main->uri, r->uri)))
+
+
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                 Types and Structures
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
+
+typedef struct {
+    const char *datafile;          /* filename for map data files         */
+    const char *dbmtype;           /* dbm type for dbm map data files     */
+    const char *checkfile;         /* filename to check for map existence */
+    const char *cachename;         /* for cached maps (txt/rnd/dbm)       */
+    int   type;                    /* the type of the map                 */
+    apr_file_t *fpin;              /* in  file pointer for program maps   */
+    apr_file_t *fpout;             /* out file pointer for program maps   */
+    apr_file_t *fperr;             /* err file pointer for program maps   */
+    char *(*func)(request_rec *,   /* function pointer for internal maps  */
+                  char *);
+    char **argv;                   /* argv of the external rewrite map    */
+} rewritemap_entry;
+
+/* special pattern types for RewriteCond */
+typedef enum {
+    CONDPAT_REGEX = 0,
+    CONDPAT_FILE_EXISTS,
+    CONDPAT_FILE_SIZE,
+    CONDPAT_FILE_LINK,
+    CONDPAT_FILE_DIR,
+    CONDPAT_FILE_XBIT,
+    CONDPAT_LU_URL,
+    CONDPAT_LU_FILE,
+    CONDPAT_STR_GT,
+    CONDPAT_STR_LT,
+    CONDPAT_STR_EQ
+} pattern_type;
+
+typedef struct {
+    char        *input;   /* Input string of RewriteCond   */
+    char        *pattern; /* the RegExp pattern string     */
+    ap_regex_t  *regexp;  /* the precompiled regexp        */
+    int          flags;   /* Flags which control the match */
+    pattern_type ptype;   /* pattern type                  */
+} rewritecond_entry;
+
+/* single linked list for env vars and cookies */
+typedef struct data_item {
+    struct data_item *next;
+    char *data;
+} data_item;
+
+typedef struct {
+    apr_array_header_t *rewriteconds;/* the corresponding RewriteCond entries */
+    char      *pattern;              /* the RegExp pattern string             */
+    ap_regex_t *regexp;              /* the RegExp pattern compilation        */
+    char      *output;               /* the Substitution string               */
+    int        flags;                /* Flags which control the substitution  */
+    char      *forced_mimetype;      /* forced MIME type of substitution      */
+    char      *forced_handler;       /* forced content handler of subst.      */
+    int        forced_responsecode;  /* forced HTTP response status           */
+    data_item *env;                  /* added environment variables           */
+    data_item *cookie;               /* added cookies                         */
+    int        skip;                 /* number of next rules to skip          */
+} rewriterule_entry;
+
+typedef struct {
+    int           state;              /* the RewriteEngine state            */
+    int           options;            /* the RewriteOption state            */
+#ifndef REWRITELOG_DISABLED
+    const char   *rewritelogfile;     /* the RewriteLog filename            */
+    apr_file_t   *rewritelogfp;       /* the RewriteLog open filepointer    */
+    int           rewriteloglevel;    /* the RewriteLog level of verbosity  */
+#endif
+    apr_hash_t         *rewritemaps;  /* the RewriteMap entries             */
+    apr_array_header_t *rewriteconds; /* the RewriteCond entries (temp.)    */
+    apr_array_header_t *rewriterules; /* the RewriteRule entries            */
+    server_rec   *server;             /* the corresponding server indicator */
+} rewrite_server_conf;
+
+typedef struct {
+    int           state;              /* the RewriteEngine state           */
+    int           options;            /* the RewriteOption state           */
+    apr_array_header_t *rewriteconds; /* the RewriteCond entries (temp.)   */
+    apr_array_header_t *rewriterules; /* the RewriteRule entries           */
+    char         *directory;          /* the directory where it applies    */
+    const char   *baseurl;            /* the base-URL  where it applies    */
+} rewrite_perdir_conf;
+
+/* the (per-child) cache structures.
+ */
+typedef struct cache {
+    apr_pool_t         *pool;
+    apr_hash_t         *maps;
+#if APR_HAS_THREADS
+    apr_thread_mutex_t *lock;
+#endif
+} cache;
+
+/* cached maps contain an mtime for the whole map and live in a subpool
+ * of the cachep->pool. That makes it easy to forget them if necessary.
+ */
+typedef struct {
+    apr_time_t mtime;
+    apr_pool_t *pool;
+    apr_hash_t *entries;
+} cachedmap;
+
+/* the regex structure for the
+ * substitution of backreferences
+ */
+typedef struct backrefinfo {
+    char *source;
+    int nsub;
+    ap_regmatch_t regmatch[AP_MAX_REG_MATCH];
+} backrefinfo;
+
+/* single linked list used for
+ * variable expansion
+ */
+typedef struct result_list {
+    struct result_list *next;
+    apr_size_t len;
+    const char *string;
+} result_list;
 
+/* context structure for variable lookup and expansion
+ */
+typedef struct {
+    request_rec *r;
+    const char  *uri;
+    const char  *vary_this;
+    const char  *vary;
+    char        *perdir;
+    backrefinfo briRR;
+    backrefinfo briRC;
+} rewrite_ctx;
 
 /*
-**  Our interface to the Apache server kernel:
-**
-**  o  Runtime logic of a request is as following:
-**       while(request or subrequest)
-**           foreach(stage #0...#9)
-**               foreach(module) (**)
-**                   try to run hook
-**
-**  o  the order of modules at (**) is the inverted order as
-**     given in the "Configuration" file, i.e. the last module
-**     specified is the first one called for each hook!
-**     The core module is always the last!
-**
-**  o  there are two different types of result checking and
-**     continue processing:
-**     for hook #0,#1,#4,#5,#6,#8:
-**         hook run loop stops on first modules which gives
-**         back a result != DECLINED, i.e. it usually returns OK
-**         which says "OK, module has handled this _stage_" and for #1
-**         this have not to mean "Ok, the filename is now valid".
-**     for hook #2,#3,#7,#9:
-**         all hooks are run, independend of result
-**
-**  o  at the last stage, the core module always
-**       - says "HTTP_BAD_REQUEST" if r->filename does not begin with "/"
-**       - prefix URL with document_root or replaced server_root
-**         with document_root and sets r->filename
-**       - always return a "OK" independed if the file really exists
-**         or not!
-*/
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                 static module data
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
 
-    /* the module (predeclaration) */
+/* the global module structure */
 module AP_MODULE_DECLARE_DATA rewrite_module;
 
-    /* rewritemap int: handler function registry */
+/* rewritemap int: handler function registry */
 static apr_hash_t *mapfunc_hash;
 
-    /* the cache */
+/* the cache */
 static cache *cachep;
 
-    /* whether proxy module is available or not */
+/* whether proxy module is available or not */
 static int proxy_available;
 
+/* whether random seed can be reaped */
+static int rewrite_rand_init_done = 0;
+
+/* Locks/Mutexes */
 static const char *lockname;
 static apr_global_mutex_t *rewrite_mapr_lock_acquire = NULL;
+
+#ifndef REWRITELOG_DISABLED
 static apr_global_mutex_t *rewrite_log_lock = NULL;
+#endif
 
 /* Optional functions imported from mod_ssl when loaded: */
 static APR_OPTIONAL_FN_TYPE(ssl_var_lookup) *rewrite_ssl_lookup = NULL;
 static APR_OPTIONAL_FN_TYPE(ssl_is_https) *rewrite_is_https = NULL;
 
 /*
-** +-------------------------------------------------------+
-** |                                                       |
-** |           configuration directive handling
-** |                                                       |
-** +-------------------------------------------------------+
-*/
-
-/*
-**
-**  per-server configuration structure handling
-**
-*/
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |              rewriting logfile support
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
 
-static void *config_server_create(apr_pool_t *p, server_rec *s)
+#ifndef REWRITELOG_DISABLED
+static char *current_logtime(request_rec *r)
 {
-    rewrite_server_conf *a;
+    apr_time_exp_t t;
+    char tstr[80];
+    apr_size_t len;
 
-    a = (rewrite_server_conf *)apr_pcalloc(p, sizeof(rewrite_server_conf));
+    apr_time_exp_lt(&t, apr_time_now());
 
-    a->state           = ENGINE_DISABLED;
-    a->options         = OPTION_NONE;
-    a->rewritelogfile  = NULL;
-    a->rewritelogfp    = NULL;
-    a->rewriteloglevel = 0;
-    a->rewritemaps     = apr_array_make(p, 2, sizeof(rewritemap_entry));
-    a->rewriteconds    = apr_array_make(p, 2, sizeof(rewritecond_entry));
-    a->rewriterules    = apr_array_make(p, 2, sizeof(rewriterule_entry));
-    a->server          = s;
-    a->redirect_limit  = 0; /* unset (use default) */
+    apr_strftime(tstr, &len, sizeof(tstr), "[%d/%b/%Y:%H:%M:%S ", &t);
+    apr_snprintf(tstr+len, sizeof(tstr)-len, "%c%.2d%.2d]",
+                 t.tm_gmtoff < 0 ? '-' : '+',
+                 t.tm_gmtoff / (60*60), t.tm_gmtoff % (60*60));
 
-    return (void *)a;
+    return apr_pstrdup(r->pool, tstr);
 }
 
-static void *config_server_merge(apr_pool_t *p, void *basev, void *overridesv)
+static int open_rewritelog(server_rec *s, apr_pool_t *p)
 {
-    rewrite_server_conf *a, *base, *overrides;
-
-    a         = (rewrite_server_conf *)apr_pcalloc(p,
-                                                   sizeof(rewrite_server_conf));
-    base      = (rewrite_server_conf *)basev;
-    overrides = (rewrite_server_conf *)overridesv;
-
-    a->state = (overrides->state_set == 0) ? base->state : overrides->state;
-    a->state_set = overrides->state_set || base->state_set;
-    a->options = (overrides->options_set == 0) ? base->options : overrides->options;
-    a->options_set = overrides->options_set || base->options_set;
+    rewrite_server_conf *conf;
+    const char *fname;
 
-    a->server  = overrides->server;
-    a->redirect_limit = overrides->redirect_limit
-                          ? overrides->redirect_limit
-                          : base->redirect_limit;
+    conf = ap_get_module_config(s->module_config, &rewrite_module);
 
-    if (a->options & OPTION_INHERIT) {
-        /*
-         *  local directives override
-         *  and anything else is inherited
-         */
-        a->rewriteloglevel = overrides->rewriteloglevel != 0
-                             ? overrides->rewriteloglevel
-                             : base->rewriteloglevel;
-        a->rewritelogfile  = overrides->rewritelogfile != NULL
-                             ? overrides->rewritelogfile
-                             : base->rewritelogfile;
-        a->rewritelogfp    = overrides->rewritelogfp != NULL
-                             ? overrides->rewritelogfp
-                             : base->rewritelogfp;
-        a->rewritemaps     = apr_array_append(p, overrides->rewritemaps,
-                                              base->rewritemaps);
-        a->rewriteconds    = apr_array_append(p, overrides->rewriteconds,
-                                              base->rewriteconds);
-        a->rewriterules    = apr_array_append(p, overrides->rewriterules,
-                                              base->rewriterules);
-    }
-    else {
-        /*
-         *  local directives override
-         *  and anything else gets defaults
-         */
-        a->rewriteloglevel = overrides->rewriteloglevel;
-        a->rewritelogfile  = overrides->rewritelogfile;
-        a->rewritelogfp    = overrides->rewritelogfp;
-        a->rewritemaps     = overrides->rewritemaps;
-        a->rewriteconds    = overrides->rewriteconds;
-        a->rewriterules    = overrides->rewriterules;
+    /* - no logfile configured
+     * - logfilename empty
+     * - virtual log shared w/ main server
+     */
+    if (!conf->rewritelogfile || !*conf->rewritelogfile || conf->rewritelogfp) {
+        return 1;
     }
 
-    return (void *)a;
-}
-
-
-/*
-**
-**  per-directory configuration structure handling
-**
-*/
-
-static void *config_perdir_create(apr_pool_t *p, char *path)
-{
-    rewrite_perdir_conf *a;
-
-    a = (rewrite_perdir_conf *)apr_pcalloc(p, sizeof(rewrite_perdir_conf));
+    if (*conf->rewritelogfile == '|') {
+        piped_log *pl;
 
-    a->state           = ENGINE_DISABLED;
-    a->options         = OPTION_NONE;
-    a->baseurl         = NULL;
-    a->rewriteconds    = apr_array_make(p, 2, sizeof(rewritecond_entry));
-    a->rewriterules    = apr_array_make(p, 2, sizeof(rewriterule_entry));
-    a->redirect_limit  = 0; /* unset (use server config) */
+        fname = ap_server_root_relative(p, conf->rewritelogfile+1);
+        if (!fname) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
+                         "mod_rewrite: Invalid RewriteLog "
+                         "path %s", conf->rewritelogfile+1);
+            return 0;
+        }
 
-    if (path == NULL) {
-        a->directory = NULL;
+        if ((pl = ap_open_piped_log(p, fname)) == NULL) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
+                         "mod_rewrite: could not open reliable pipe "
+                         "to RewriteLog filter %s", fname);
+            return 0;
+        }
+        conf->rewritelogfp = ap_piped_log_write_fd(pl);
     }
     else {
-        /* make sure it has a trailing slash */
-        if (path[strlen(path)-1] == '/') {
-            a->directory = apr_pstrdup(p, path);
+        apr_status_t rc;
+
+        fname = ap_server_root_relative(p, conf->rewritelogfile);
+        if (!fname) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
+                         "mod_rewrite: Invalid RewriteLog "
+                         "path %s", conf->rewritelogfile);
+            return 0;
         }
-        else {
-            a->directory = apr_pstrcat(p, path, "/", NULL);
+
+        if ((rc = apr_file_open(&conf->rewritelogfp, fname,
+                                REWRITELOG_FLAGS, REWRITELOG_MODE, p))
+                != APR_SUCCESS) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
+                         "mod_rewrite: could not open RewriteLog "
+                         "file %s", fname);
+            return 0;
         }
     }
 
-    return (void *)a;
+    return 1;
 }
 
-static void *config_perdir_merge(apr_pool_t *p, void *basev, void *overridesv)
+static void do_rewritelog(request_rec *r, int level, char *perdir,
+                          const char *fmt, ...)
 {
-    rewrite_perdir_conf *a, *base, *overrides;
+    rewrite_server_conf *conf;
+    char *logline, *text;
+    const char *rhost, *rname;
+    apr_size_t nbytes;
+    int redir;
+    apr_status_t rv;
+    request_rec *req;
+    va_list ap;
 
-    a         = (rewrite_perdir_conf *)apr_pcalloc(p,
-                                                  sizeof(rewrite_perdir_conf));
-    base      = (rewrite_perdir_conf *)basev;
-    overrides = (rewrite_perdir_conf *)overridesv;
+    conf = ap_get_module_config(r->server->module_config, &rewrite_module);
 
-    a->state = (overrides->state_set == 0) ? base->state : overrides->state;
-    a->state_set = overrides->state_set || base->state_set;
-    a->options = (overrides->options_set == 0) ? base->options : overrides->options;
-    a->options_set = overrides->options_set || base->options_set;
-    a->redirect_limit = overrides->redirect_limit
-                          ? overrides->redirect_limit
-                          : base->redirect_limit;
- 
-    if (a->options & OPTION_MERGEBASE) { 
-        a->baseurl = (overrides->baseurl_set == 0) ? base->baseurl : overrides->baseurl;
-        a->baseurl_set = overrides->baseurl_set || base->baseurl_set;
-    }
-    else { 
-        a->baseurl = overrides->baseurl;
+    if (!conf->rewritelogfp || level > conf->rewriteloglevel) {
+        return;
     }
 
-    a->directory  = overrides->directory;
+    rhost = ap_get_remote_host(r->connection, r->per_dir_config,
+                               REMOTE_NOLOOKUP, NULL);
+    rname = ap_get_remote_logname(r);
 
-    if (a->options & OPTION_INHERIT) {
-        a->rewriteconds = apr_array_append(p, overrides->rewriteconds,
-                                           base->rewriteconds);
-        a->rewriterules = apr_array_append(p, overrides->rewriterules,
-                                           base->rewriterules);
-    }
-    else {
-        a->rewriteconds = overrides->rewriteconds;
-        a->rewriterules = overrides->rewriterules;
+    for (redir=0, req=r; req->prev; req = req->prev) {
+        ++redir;
     }
 
-    return (void *)a;
-}
-
+    va_start(ap, fmt);
+    text = apr_pvsprintf(r->pool, fmt, ap);
+    va_end(ap);
 
-/*
-**
-**  the configuration commands
-**
-*/
+    logline = apr_psprintf(r->pool, "%s %s %s %s [%s/sid#%pp][rid#%pp/%s%s%s] "
+                                    "(%d) %s%s%s%s" APR_EOL_STR,
+                           rhost ? rhost : "UNKNOWN-HOST",
+                           rname ? rname : "-",
+                           r->user ? (*r->user ? r->user : "\"\"") : "-",
+                           current_logtime(r),
+                           ap_get_server_name(r),
+                           (void *)(r->server),
+                           (void *)r,
+                           r->main ? "subreq" : "initial",
+                           redir ? "/redir#" : "",
+                           redir ? apr_itoa(r->pool, redir) : "",
+                           level,
+                           perdir ? "[perdir " : "",
+                           perdir ? perdir : "",
+                           perdir ? "] ": "",
+                           text);
 
-static const char *cmd_rewriteengine(cmd_parms *cmd,
-                                     void *in_dconf, int flag)
-{
-    rewrite_perdir_conf *dconf = in_dconf;
-    rewrite_server_conf *sconf;
+    rv = apr_global_mutex_lock(rewrite_log_lock);
+    if (rv != APR_SUCCESS) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+                      "apr_global_mutex_lock(rewrite_log_lock) failed");
+        /* XXX: Maybe this should be fatal? */
+    }
 
-    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
+    nbytes = strlen(logline);
+    apr_file_write(conf->rewritelogfp, logline, &nbytes);
 
-    /* server command? set both global scope and base directory scope */
-    if (cmd->path == NULL) {
-        sconf->state = (flag ? ENGINE_ENABLED : ENGINE_DISABLED);
-        sconf->state_set = 1;
-        dconf->state = sconf->state;
-        dconf->state_set = 1;
-    }
-    /* directory command? set directory scope only */
-    else {
-        dconf->state = (flag ? ENGINE_ENABLED : ENGINE_DISABLED);
-        dconf->state_set = 1;
+    rv = apr_global_mutex_unlock(rewrite_log_lock);
+    if (rv != APR_SUCCESS) {
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+                      "apr_global_mutex_unlock(rewrite_log_lock) failed");
+        /* XXX: Maybe this should be fatal? */
     }
 
-    return NULL;
+    return;
 }
+#endif /* !REWRITELOG_DISABLED */
 
-static const char *cmd_rewriteoptions(cmd_parms *cmd,
-                                      void *in_dconf, const char *option)
-{
-    int options = 0, limit = 0;
-    char *w;
 
-    while (*option) {
-        w = ap_getword_conf(cmd->pool, &option);
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                URI and path functions
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
 
-        if (!strcasecmp(w, "inherit")) {
-            options |= OPTION_INHERIT;
-        }
-        else if (!strncasecmp(w, "MaxRedirects=", 13)) {
-            limit = atoi(&w[13]);
-            if (limit <= 0) {
-                return "RewriteOptions: MaxRedirects takes a number greater "
-                       "than zero.";
-            }
-        }
-        else if (!strcasecmp(w, "MaxRedirects")) { /* be nice */
-            return "RewriteOptions: MaxRedirects has the format MaxRedirects"
-                   "=n.";
-        }
-        else if (!strcasecmp(w, "allowanyuri")) {
-            options |= OPTION_ANYURI;
-        }
-        else if (!strcasecmp(w, "mergebase")) {
-            options |= OPTION_MERGEBASE;
-        }
-        else {
-            return apr_pstrcat(cmd->pool, "RewriteOptions: unknown option '",
-                               w, "'", NULL);
-        }
+/* return number of chars of the scheme (incl. '://')
+ * if the URI is absolute (includes a scheme etc.)
+ * otherwise 0.
+ *
+ * NOTE: If you add new schemes here, please have a
+ *       look at escape_absolute_uri and splitout_queryargs.
+ *       Not every scheme takes query strings and some schemes
+ *       may be handled in a special way.
+ *
+ * XXX: we may consider a scheme registry, perhaps with
+ *      appropriate escape callbacks to allow other modules
+ *      to extend mod_rewrite at runtime.
+ */
+static unsigned is_absolute_uri(char *uri)
+{
+    /* fast exit */
+    if (*uri == '/' || strlen(uri) <= 5) {
+        return 0;
     }
 
-    /* server command? set both global scope and base directory scope */
-    if (cmd->path == NULL) { /* is server command */
-        rewrite_perdir_conf *dconf = in_dconf;
-        rewrite_server_conf *sconf =
-            ap_get_module_config(cmd->server->module_config,
-                                 &rewrite_module);
+    switch (*uri++) {
+    case 'a':
+    case 'A':
+        if (!strncasecmp(uri, "jp://", 5)) {        /* ajp://    */
+          return 6;
+        }
 
-        sconf->options |= options;
-        sconf->options_set = 1;
-        sconf->redirect_limit = limit;
-        dconf->options |= options;
-        dconf->options_set = 1;
-        dconf->redirect_limit = limit;
-     }
-    /* directory command? set directory scope only */
-    else {                  /* is per-directory command */
-        rewrite_perdir_conf *dconf = in_dconf;
+    case 'b':
+    case 'B':
+        if (!strncasecmp(uri, "alancer://", 10)) {   /* balancer:// */
+          return 11;
+        }
+        break;
 
-        dconf->options |= options;
-        dconf->options_set = 1;
-        dconf->redirect_limit = limit;
+    case 'f':
+    case 'F':
+        if (!strncasecmp(uri, "tp://", 5)) {        /* ftp://    */
+            return 6;
+        }
+        break;
+
+    case 'g':
+    case 'G':
+        if (!strncasecmp(uri, "opher://", 8)) {     /* gopher:// */
+            return 9;
+        }
+        break;
+
+    case 'h':
+    case 'H':
+        if (!strncasecmp(uri, "ttp://", 6)) {       /* http://   */
+            return 7;
+        }
+        else if (!strncasecmp(uri, "ttps://", 7)) { /* https://  */
+            return 8;
+        }
+        break;
+
+    case 'l':
+    case 'L':
+        if (!strncasecmp(uri, "dap://", 6)) {       /* ldap://   */
+            return 7;
+        }
+        break;
+
+    case 'm':
+    case 'M':
+        if (!strncasecmp(uri, "ailto:", 6)) {       /* mailto:   */
+            return 7;
+        }
+        break;
+
+    case 'n':
+    case 'N':
+        if (!strncasecmp(uri, "ews:", 4)) {         /* news:     */
+            return 5;
+        }
+        else if (!strncasecmp(uri, "ntp://", 6)) {  /* nntp://   */
+            return 7;
+        }
+        break;
     }
- 
-    return NULL;
+
+    return 0;
 }
 
-static const char *cmd_rewritelog(cmd_parms *cmd, void *dconf, const char *a1)
+/*
+ * escape absolute uri, which may or may not be path oriented.
+ * So let's handle them differently.
+ */
+static char *escape_absolute_uri(apr_pool_t *p, char *uri, unsigned scheme)
 {
-    rewrite_server_conf *sconf;
+    char *cp;
 
-    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
+    /* be safe.
+     * NULL should indicate elsewhere, that something's wrong
+     */
+    if (!scheme || strlen(uri) < scheme) {
+        return NULL;
+    }
 
-    sconf->rewritelogfile = a1;
+    cp = uri + scheme;
 
-    return NULL;
-}
+    /* scheme with authority part? */
+    if (cp[-1] == '/') {
+        /* skip host part */
+        while (*cp && *cp != '/') {
+            ++cp;
+        }
 
-static const char *cmd_rewriteloglevel(cmd_parms *cmd, void *dconf,
-                                       const char *a1)
-{
-    rewrite_server_conf *sconf;
+        /* nothing after the hostpart. ready! */
+        if (!*cp || !*++cp) {
+            return apr_pstrdup(p, uri);
+        }
 
-    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
+        /* remember the hostname stuff */
+        scheme = cp - uri;
 
-    sconf->rewriteloglevel = atoi(a1);
+        /* special thing for ldap.
+         * The parts are separated by question marks. From RFC 2255:
+         *     ldapurl = scheme "://" [hostport] ["/"
+         *               [dn ["?" [attributes] ["?" [scope]
+         *               ["?" [filter] ["?" extensions]]]]]]
+         */
+        if (!strncasecmp(uri, "ldap", 4)) {
+            char *token[5];
+            int c = 0;
 
-    return NULL;
+            token[0] = cp = apr_pstrdup(p, cp);
+            while (*cp && c < 5) {
+                if (*cp == '?') {
+                    token[++c] = cp + 1;
+                    *cp = '\0';
+                }
+                ++cp;
+            }
+
+            return apr_pstrcat(p, apr_pstrndup(p, uri, scheme),
+                                          ap_escape_uri(p, token[0]),
+                               (c >= 1) ? "?" : NULL,
+                               (c >= 1) ? ap_escape_uri(p, token[1]) : NULL,
+                               (c >= 2) ? "?" : NULL,
+                               (c >= 2) ? ap_escape_uri(p, token[2]) : NULL,
+                               (c >= 3) ? "?" : NULL,
+                               (c >= 3) ? ap_escape_uri(p, token[3]) : NULL,
+                               (c >= 4) ? "?" : NULL,
+                               (c >= 4) ? ap_escape_uri(p, token[4]) : NULL,
+                               NULL);
+        }
+    }
+
+    /* Nothing special here. Apply normal escaping. */
+    return apr_pstrcat(p, apr_pstrndup(p, uri, scheme),
+                       ap_escape_uri(p, cp), NULL);
 }
 
-static const char *cmd_rewritemap(cmd_parms *cmd, void *dconf, const char *a1,
-                                  const char *a2)
+/*
+ * split out a QUERY_STRING part from
+ * the current URI string
+ */
+static void splitout_queryargs(request_rec *r, int qsappend)
 {
-    rewrite_server_conf *sconf;
-    rewritemap_entry *newmap;
-    apr_finfo_t st;
+    char *q;
 
-    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
+    /* don't touch, unless it's an http or mailto URL.
+     * See RFC 1738 and RFC 2368.
+     */
+    if (is_absolute_uri(r->filename)
+        && strncasecmp(r->filename, "ajp", 3)
+        && strncasecmp(r->filename, "balancer", 8)
+        && strncasecmp(r->filename, "http", 4)
+        && strncasecmp(r->filename, "mailto", 6)) {
+        r->args = NULL; /* forget the query that's still flying around */
+        return;
+    }
 
-    newmap = apr_array_push(sconf->rewritemaps);
+    q = ap_strchr(r->filename, '?');
+    if (q != NULL) {
+        char *olduri;
+        apr_size_t len;
 
-    newmap->name = a1;
-    newmap->func = NULL;
-    if (strncmp(a2, "txt:", 4) == 0) {
-        newmap->type      = MAPTYPE_TXT;
-        newmap->datafile  = a2+4;
-        newmap->checkfile = a2+4;
-        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
-                                         (void *)cmd->server, a1);
-    }
-    else if (strncmp(a2, "rnd:", 4) == 0) {
-        newmap->type      = MAPTYPE_RND;
-        newmap->datafile  = a2+4;
-        newmap->checkfile = a2+4;
-        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
-                                         (void *)cmd->server, a1);
+        olduri = apr_pstrdup(r->pool, r->filename);
+        *q++ = '\0';
+        if (qsappend) {
+            r->args = apr_pstrcat(r->pool, q, "&", r->args, NULL);
+        }
+        else {
+            r->args = apr_pstrdup(r->pool, q);
+        }
+
+        len = strlen(r->args);
+        if (!len) {
+            r->args = NULL;
+        }
+        else if (r->args[len-1] == '&') {
+            r->args[len-1] = '\0';
+        }
+
+        rewritelog((r, 3, NULL, "split uri=%s -> uri=%s, args=%s", olduri,
+                    r->filename, r->args ? r->args : "<none>"));
     }
-    else if (strncmp(a2, "dbm", 3) == 0) {
-        const char *ignored_fname;
-        int bad = 0;
-        apr_status_t rv;
 
-        newmap->type = MAPTYPE_DBM;
-        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
-                                         (void *)cmd->server, a1);
+    return;
+}
 
-        if (a2[3] == ':') {
-            newmap->dbmtype    = "default";
-            newmap->datafile   = a2+4;
+/*
+ * strip 'http[s]://ourhost/' from URI
+ */
+static void reduce_uri(request_rec *r)
+{
+    char *cp;
+    apr_size_t l;
+
+    cp = (char *)ap_http_scheme(r);
+    l  = strlen(cp);
+    if (   strlen(r->filename) > l+3
+        && strncasecmp(r->filename, cp, l) == 0
+        && r->filename[l]   == ':'
+        && r->filename[l+1] == '/'
+        && r->filename[l+2] == '/' ) {
+
+        unsigned short port;
+        char *portp, *host, *url, *scratch;
+
+        scratch = apr_pstrdup(r->pool, r->filename); /* our scratchpad */
+
+        /* cut the hostname and port out of the URI */
+        cp = host = scratch + l + 3;    /* 3 == strlen("://") */
+        while (*cp && *cp != '/' && *cp != ':') {
+            ++cp;
         }
-        else if (a2[3] == '=') {
-            const char *colon = ap_strchr_c(a2 + 4, ':');
 
-            if (colon) {
-                newmap->dbmtype = apr_pstrndup(cmd->pool, a2 + 4,
-                                               colon - (a2 + 3) - 1);
-                newmap->datafile = colon + 1;
+        if (*cp == ':') {      /* additional port given */
+            *cp++ = '\0';
+            portp = cp;
+            while (*cp && *cp != '/') {
+                ++cp;
             }
-            else {
-                ++bad;
+            *cp = '\0';
+
+            port = atoi(portp);
+            url = r->filename + (cp - scratch);
+            if (!*url) {
+                url = "/";
             }
         }
+        else if (*cp == '/') { /* default port */
+            *cp = '\0';
+
+            port = ap_default_port(r);
+            url = r->filename + (cp - scratch);
+        }
         else {
-            ++bad;
+            port = ap_default_port(r);
+            url = "/";
         }
 
-        if (bad) {
-            return apr_pstrcat(cmd->pool, "RewriteMap: bad map:",
-                               a2, NULL);
+        /* now check whether we could reduce it to a local path... */
+        if (ap_matches_request_vhost(r, host, port)) {
+            rewritelog((r, 3, NULL, "reduce %s -> %s", r->filename, url));
+            r->filename = apr_pstrdup(r->pool, url);
         }
+    }
 
-        rv = apr_dbm_get_usednames_ex(cmd->pool, newmap->dbmtype,
-                                      newmap->datafile, &newmap->checkfile,
-                                      &ignored_fname);
-        if (rv != APR_SUCCESS) {
-            return apr_pstrcat(cmd->pool, "RewriteMap: dbm type ",
-                               newmap->dbmtype, " is invalid", NULL);
-        }
+    return;
+}
+
+/*
+ * add 'http[s]://ourhost[:ourport]/' to URI
+ * if URI is still not fully qualified
+ */
+static void fully_qualify_uri(request_rec *r)
+{
+    if (!is_absolute_uri(r->filename)) {
+        const char *thisserver;
+        char *thisport;
+        int port;
+
+        thisserver = ap_get_server_name(r);
+        port = ap_get_server_port(r);
+        thisport = ap_is_default_port(port, r)
+                   ? ""
+                   : apr_psprintf(r->pool, ":%u", port);
+
+        r->filename = apr_psprintf(r->pool, "%s://%s%s%s%s",
+                                   ap_http_scheme(r), thisserver, thisport,
+                                   (*r->filename == '/') ? "" : "/",
+                                   r->filename);
     }
-    else if (strncmp(a2, "prg:", 4) == 0) {
-        newmap->type      = MAPTYPE_PRG;
-        apr_tokenize_to_argv(a2 + 4, &newmap->argv, cmd->pool);
-        newmap->datafile  = NULL;
-        newmap->checkfile = newmap->argv[0];
-        newmap->cachename = NULL;
 
+    return;
+}
+
+/*
+ * stat() only the first segment of a path
+ */
+static int prefix_stat(const char *path, apr_pool_t *pool)
+{
+    const char *curpath = path;
+    const char *root;
+    const char *slash;
+    char *statpath;
+    apr_status_t rv;
+
+    rv = apr_filepath_root(&root, &curpath, APR_FILEPATH_TRUENAME, pool);
+
+    if (rv != APR_SUCCESS) {
+        return 0;
     }
-    else if (strncmp(a2, "int:", 4) == 0) {
-        newmap->type      = MAPTYPE_INT;
-        newmap->datafile  = NULL;
-        newmap->checkfile = NULL;
-        newmap->cachename = NULL;
-        newmap->func      = (char *(*)(request_rec *,char *))
-                            apr_hash_get(mapfunc_hash, a2+4, strlen(a2+4));
-        if ((sconf->state == ENGINE_ENABLED) && (newmap->func == NULL)) {
-            return apr_pstrcat(cmd->pool, "RewriteMap: internal map not found:",
-                               a2+4, NULL);
-        }
+
+    /* let's recognize slashes only, the mod_rewrite semantics are opaque
+     * enough.
+     */
+    if ((slash = ap_strchr_c(curpath, '/')) != NULL) {
+        rv = apr_filepath_merge(&statpath, root,
+                                apr_pstrndup(pool, curpath,
+                                             (apr_size_t)(slash - curpath)),
+                                APR_FILEPATH_NOTABOVEROOT |
+                                APR_FILEPATH_NOTRELATIVE, pool);
     }
     else {
-        newmap->type      = MAPTYPE_TXT;
-        newmap->datafile  = a2;
-        newmap->checkfile = a2;
-        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
-                                         (void *)cmd->server, a1);
+        rv = apr_filepath_merge(&statpath, root, curpath,
+                                APR_FILEPATH_NOTABOVEROOT |
+                                APR_FILEPATH_NOTRELATIVE, pool);
     }
-    newmap->fpin  = NULL;
-    newmap->fpout = NULL;
 
-    if (newmap->checkfile && (sconf->state == ENGINE_ENABLED)
-        && (apr_stat(&st, newmap->checkfile, APR_FINFO_MIN,
-                     cmd->pool) != APR_SUCCESS)) {
-        return apr_pstrcat(cmd->pool,
-                           "RewriteMap: file for map ", newmap->name,
-                           " not found:", newmap->checkfile, NULL);
+    if (rv == APR_SUCCESS) {
+        apr_finfo_t sb;
+
+        if (apr_stat(&sb, statpath, APR_FINFO_MIN, pool) == APR_SUCCESS) {
+            return 1;
+        }
     }
 
-    return NULL;
+    return 0;
 }
 
-static const char *cmd_rewritelock(cmd_parms *cmd, void *dconf, const char *a1)
+/*
+ * substitute the prefix path 'match' in 'input' with 'subst' (RewriteBase)
+ */
+static char *subst_prefix_path(request_rec *r, char *input, char *match,
+                               const char *subst)
 {
-    const char *error;
+    apr_size_t len = strlen(match);
 
-    if ((error = ap_check_cmd_context(cmd, GLOBAL_ONLY)) != NULL)
-        return error;
+    if (len && match[len - 1] == '/') {
+        --len;
+    }
 
-    /* fixup the path, especially for rewritelock_remove() */
-    lockname = ap_server_root_relative(cmd->pool, a1);
+    if (!strncmp(input, match, len) && input[len++] == '/') {
+        apr_size_t slen, outlen;
+        char *output;
 
-    if (!lockname) {
-        return apr_pstrcat(cmd->pool, "Invalid RewriteLock path ", a1);
+        rewritelog((r, 5, NULL, "strip matching prefix: %s -> %s", input,
+                    input+len));
+
+        slen = strlen(subst);
+        if (slen && subst[slen - 1] != '/') {
+            ++slen;
+        }
+
+        outlen = strlen(input) + slen - len;
+        output = apr_palloc(r->pool, outlen + 1); /* don't forget the \0 */
+
+        memcpy(output, subst, slen);
+        if (slen && !output[slen-1]) {
+            output[slen-1] = '/';
+        }
+        memcpy(output+slen, input+len, outlen - slen);
+        output[outlen] = '\0';
+
+        rewritelog((r, 4, NULL, "add subst prefix: %s -> %s", input+len,
+                    output));
+
+        return output;
     }
 
-    return NULL;
+    /* prefix didn't match */
+    return input;
 }
 
-static const char *cmd_rewritebase(cmd_parms *cmd, void *in_dconf,
-                                   const char *a1)
+
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                    caching support
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
+
+static void set_cache_value(const char *name, apr_time_t t, char *key,
+                            char *val)
 {
-    rewrite_perdir_conf *dconf = in_dconf;
+    cachedmap *map;
 
-    if (cmd->path == NULL || dconf == NULL) {
-        return "RewriteBase: only valid in per-directory config files";
-    }
-    if (a1[0] == '\0') {
-        return "RewriteBase: empty URL not allowed";
-    }
-    if (a1[0] != '/') {
-        return "RewriteBase: argument is not a valid URL";
-    }
+    if (cachep) {
+#if APR_HAS_THREADS
+        apr_thread_mutex_lock(cachep->lock);
+#endif
+        map = apr_hash_get(cachep->maps, name, APR_HASH_KEY_STRING);
 
-    dconf->baseurl = a1;
-    dconf->baseurl_set = 1;
+        if (!map) {
+            apr_pool_t *p;
 
-    return NULL;
+            if (apr_pool_create(&p, cachep->pool) != APR_SUCCESS) {
+#if APR_HAS_THREADS
+                apr_thread_mutex_unlock(cachep->lock);
+#endif
+                return;
+            }
+
+            map = apr_palloc(cachep->pool, sizeof(cachedmap));
+            map->pool = p;
+            map->entries = apr_hash_make(map->pool);
+            map->mtime = t;
+
+            apr_hash_set(cachep->maps, name, APR_HASH_KEY_STRING, map);
+        }
+        else if (map->mtime != t) {
+            apr_pool_clear(map->pool);
+            map->entries = apr_hash_make(map->pool);
+            map->mtime = t;
+        }
+
+        /* Now we should have a valid map->entries hash, where we
+         * can store our value.
+         *
+         * We need to copy the key and the value into OUR pool,
+         * so that we don't leave it during the r->pool cleanup.
+         */
+        apr_hash_set(map->entries,
+                     apr_pstrdup(map->pool, key), APR_HASH_KEY_STRING,
+                     apr_pstrdup(map->pool, val));
+
+#if APR_HAS_THREADS
+        apr_thread_mutex_unlock(cachep->lock);
+#endif
+    }
+
+    return;
 }
 
-static const char *cmd_rewritecond(cmd_parms *cmd, void *in_dconf,
-                                   const char *in_str)
+static char *get_cache_value(const char *name, apr_time_t t, char *key,
+                             apr_pool_t *p)
 {
-    rewrite_perdir_conf *dconf = in_dconf;
-    char *str = apr_pstrdup(cmd->pool, in_str);
-    rewrite_server_conf *sconf;
-    rewritecond_entry *newcond;
-    regex_t *regexp;
-    char *a1;
-    char *a2;
-    char *a3;
-    char *cp;
-    const char *err;
-    int rc;
+    cachedmap *map;
+    char *val = NULL;
 
-    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
+    if (cachep) {
+#if APR_HAS_THREADS
+        apr_thread_mutex_lock(cachep->lock);
+#endif
+        map = apr_hash_get(cachep->maps, name, APR_HASH_KEY_STRING);
 
-    /*  make a new entry in the internal temporary rewrite rule list */
-    if (cmd->path == NULL) {   /* is server command */
-        newcond = apr_array_push(sconf->rewriteconds);
-    }
-    else {                     /* is per-directory command */
-        newcond = apr_array_push(dconf->rewriteconds);
-    }
+        if (map) {
+            /* if this map is outdated, forget it. */
+            if (map->mtime != t) {
+                apr_pool_clear(map->pool);
+                map->entries = apr_hash_make(map->pool);
+                map->mtime = t;
+            }
+            else {
+                val = apr_hash_get(map->entries, key, APR_HASH_KEY_STRING);
+                if (val) {
+                    /* copy the cached value into the supplied pool,
+                     * where it belongs (r->pool usually)
+                     */
+                    val = apr_pstrdup(p, val);
+                }
+            }
+        }
 
-    /*  parse the argument line ourself */
-    if (parseargline(str, &a1, &a2, &a3)) {
-        return apr_pstrcat(cmd->pool, "RewriteCond: bad argument line '", str,
-                           "'", NULL);
+#if APR_HAS_THREADS
+        apr_thread_mutex_unlock(cachep->lock);
+#endif
     }
 
-    /*  arg1: the input string */
-    newcond->input = apr_pstrdup(cmd->pool, a1);
+    return val;
+}
 
-    /* arg3: optional flags field
-       (this have to be first parsed, because we need to
-        know if the regex should be compiled with ICASE!) */
-    newcond->flags = CONDFLAG_NONE;
-    if (a3 != NULL) {
-        if ((err = cmd_rewritecond_parseflagfield(cmd->pool, newcond,
-                                                  a3)) != NULL) {
-            return err;
-        }
+static int init_cache(apr_pool_t *p)
+{
+    cachep = apr_palloc(p, sizeof(cache));
+    if (apr_pool_create(&cachep->pool, p) != APR_SUCCESS) {
+        cachep = NULL; /* turns off cache */
+        return 0;
     }
 
-    /*  arg2: the pattern
-        try to compile the regexp to test if is ok */
-    cp = a2;
-    if (cp[0] == '!') {
-        newcond->flags |= CONDFLAG_NOTMATCH;
-        cp++;
-    }
+    cachep->maps = apr_hash_make(cachep->pool);
+#if APR_HAS_THREADS
+    (void)apr_thread_mutex_create(&(cachep->lock), APR_THREAD_MUTEX_DEFAULT, p);
+#endif
 
-    /* now be careful: Under the POSIX regex library
-       we can compile the pattern for case insensitive matching,
-       under the old V8 library we have to do it self via a hack */
-    if (newcond->flags & CONDFLAG_NOCASE) {
-        rc = ((regexp = ap_pregcomp(cmd->pool, cp, REG_EXTENDED|REG_ICASE))
-              == NULL);
-    }
-    else {
-        rc = ((regexp = ap_pregcomp(cmd->pool, cp, REG_EXTENDED)) == NULL);
+    return 1;
+}
+
+
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                    Map Functions
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
+
+/*
+ * General Note: key is already a fresh string, created (expanded) just
+ * for the purpose to be passed in here. So one can modify key itself.
+ */
+
+static char *rewrite_mapfunc_toupper(request_rec *r, char *key)
+{
+    char *p;
+
+    for (p = key; *p; ++p) {
+        *p = apr_toupper(*p);
     }
-    if (rc) {
-        return apr_pstrcat(cmd->pool,
-                           "RewriteCond: cannot compile regular expression '",
-                           a2, "'", NULL);
+
+    return key;
+}
+
+static char *rewrite_mapfunc_tolower(request_rec *r, char *key)
+{
+    char *p;
+
+    for (p = key; *p; ++p) {
+        *p = apr_tolower(*p);
     }
 
-    newcond->pattern = apr_pstrdup(cmd->pool, cp);
-    newcond->regexp  = regexp;
+    return key;
+}
+
+static char *rewrite_mapfunc_escape(request_rec *r, char *key)
+{
+    return ap_escape_uri(r->pool, key);
+}
+
+static char *rewrite_mapfunc_unescape(request_rec *r, char *key)
+{
+    ap_unescape_url(key);
 
-    return NULL;
+    return key;
 }
 
-static const char *cmd_rewritecond_parseflagfield(apr_pool_t *p,
-                                                  rewritecond_entry *cfg,
-                                                  char *str)
+static char *select_random_value_part(request_rec *r, char *value)
 {
-    char *cp;
-    char *cp1;
-    char *cp2;
-    char *cp3;
-    char *key;
-    char *val;
-    const char *err;
+    char *p = value;
+    unsigned n = 1;
 
-    if (str[0] != '[' || str[strlen(str)-1] != ']') {
-        return "RewriteCond: bad flag delimiters";
+    /* count number of distinct values */
+    while ((p = ap_strchr(p, '|')) != NULL) {
+        ++n;
+        ++p;
     }
 
-    cp = str+1;
-    str[strlen(str)-1] = ','; /* for simpler parsing */
-    for ( ; *cp != '\0'; ) {
-        /* skip whitespaces */
-        for ( ; (*cp == ' ' || *cp == '\t') && *cp != '\0'; cp++)
-            ;
-        if (*cp == '\0') {
-            break;
+    if (n > 1) {
+        /* initialize random generator
+         *
+         * XXX: Probably this should be wrapped into a thread mutex,
+         * shouldn't it? Is it worth the effort?
+         */
+        if (!rewrite_rand_init_done) {
+            srand((unsigned)(getpid()));
+            rewrite_rand_init_done = 1;
         }
-        cp1 = cp;
-        if ((cp2 = strchr(cp, ',')) != NULL) {
-            cp = cp2+1;
-            for ( ; (*(cp2-1) == ' ' || *(cp2-1) == '\t'); cp2--)
-                ;
-            *cp2 = '\0';
-            if ((cp3 = strchr(cp1, '=')) != NULL) {
-                *cp3 = '\0';
-                key = cp1;
-                val = cp3+1;
-            }
-            else {
-                key = cp1;
-                val = "";
-            }
-            if ((err = cmd_rewritecond_setflag(p, cfg, key, val)) != NULL) {
-                return err;
-            }
+
+        /* select a random subvalue */
+        n = (int)(((double)(rand() % RAND_MAX) / RAND_MAX) * n + 1);
+
+        /* extract it from the whole string */
+        while (--n && (value = ap_strchr(value, '|')) != NULL) {
+            ++value;
         }
-        else {
-            break;
+
+        if (value) { /* should not be NULL, but ... */
+            p = ap_strchr(value, '|');
+            if (p) {
+                *p = '\0';
+            }
         }
     }
 
-    return NULL;
+    return value;
 }
 
-static const char *cmd_rewritecond_setflag(apr_pool_t *p,
-                                           rewritecond_entry *cfg,
-                                           char *key, char *val)
+/* child process code */
+static void rewrite_child_errfn(apr_pool_t *p, apr_status_t err,
+                                const char *desc)
 {
-    if (   strcasecmp(key, "nocase") == 0
-        || strcasecmp(key, "NC") == 0    ) {
-        cfg->flags |= CONDFLAG_NOCASE;
-    }
-    else if (   strcasecmp(key, "ornext") == 0
-             || strcasecmp(key, "OR") == 0    ) {
-        cfg->flags |= CONDFLAG_ORNEXT;
-    }
-    else {
-        return apr_pstrcat(p, "RewriteCond: unknown flag '", key, "'", NULL);
-    }
-    return NULL;
+    ap_log_error(APLOG_MARK, APLOG_ERR, err, NULL, "%s", desc);
 }
 
-static const char *cmd_rewriterule(cmd_parms *cmd, void *in_dconf,
-                                   const char *in_str)
+static apr_status_t rewritemap_program_child(apr_pool_t *p,
+                                             const char *progname, char **argv,
+                                             apr_file_t **fpout,
+                                             apr_file_t **fpin)
 {
-    rewrite_perdir_conf *dconf = in_dconf;
-    char *str = apr_pstrdup(cmd->pool, in_str);
-    rewrite_server_conf *sconf;
-    rewriterule_entry *newrule;
-    regex_t *regexp;
-    char *a1;
-    char *a2;
-    char *a3;
-    char *cp;
-    const char *err;
-    int mode;
+    apr_status_t rc;
+    apr_procattr_t *procattr;
+    apr_proc_t *procnew;
 
-    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
+    if (   APR_SUCCESS == (rc=apr_procattr_create(&procattr, p))
+        && APR_SUCCESS == (rc=apr_procattr_io_set(procattr, APR_FULL_BLOCK,
+                                                  APR_FULL_BLOCK, APR_NO_PIPE))
+        && APR_SUCCESS == (rc=apr_procattr_dir_set(procattr,
+                                             ap_make_dirstr_parent(p, argv[0])))
+        && APR_SUCCESS == (rc=apr_procattr_cmdtype_set(procattr, APR_PROGRAM))
+        && APR_SUCCESS == (rc=apr_procattr_child_errfn_set(procattr,
+                                                           rewrite_child_errfn))
+        && APR_SUCCESS == (rc=apr_procattr_error_check_set(procattr, 1))) {
 
-    /*  make a new entry in the internal rewrite rule list */
-    if (cmd->path == NULL) {   /* is server command */
-        newrule = apr_array_push(sconf->rewriterules);
-    }
-    else {                     /* is per-directory command */
-        newrule = apr_array_push(dconf->rewriterules);
-    }
+        procnew = apr_pcalloc(p, sizeof(*procnew));
+        rc = apr_proc_create(procnew, argv[0], (const char **)argv, NULL,
+                             procattr, p);
 
-    /*  parse the argument line ourself */
-    if (parseargline(str, &a1, &a2, &a3)) {
-        return apr_pstrcat(cmd->pool, "RewriteRule: bad argument line '", str,
-                           "'", NULL);
-    }
+        if (rc == APR_SUCCESS) {
+            apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);
 
-    /* arg3: optional flags field */
-    newrule->forced_mimetype     = NULL;
-    newrule->forced_responsecode = HTTP_MOVED_TEMPORARILY;
-    newrule->flags  = RULEFLAG_NONE;
-    newrule->env[0] = NULL;
-    newrule->cookie[0] = NULL;
-    newrule->skip   = 0;
-    if (a3 != NULL) {
-        if ((err = cmd_rewriterule_parseflagfield(cmd->pool, newrule,
-                                                  a3)) != NULL) {
-            return err;
+            if (fpin) {
+                (*fpin) = procnew->in;
+            }
+
+            if (fpout) {
+                (*fpout) = procnew->out;
+            }
         }
     }
 
-    /*  arg1: the pattern
-     *  try to compile the regexp to test if is ok
-     */
-    cp = a1;
-    if (cp[0] == '!') {
-        newrule->flags |= RULEFLAG_NOTMATCH;
-        cp++;
-    }
-    mode = REG_EXTENDED;
-    if (newrule->flags & RULEFLAG_NOCASE) {
-        mode |= REG_ICASE;
-    }
-    if ((regexp = ap_pregcomp(cmd->pool, cp, mode)) == NULL) {
-        return apr_pstrcat(cmd->pool,
-                           "RewriteRule: cannot compile regular expression '",
-                           a1, "'", NULL);
-    }
-    newrule->pattern = apr_pstrdup(cmd->pool, cp);
-    newrule->regexp  = regexp;
+    return (rc);
+}
 
-    /*  arg2: the output string
-     *  replace the $<N> by \<n> which is needed by the currently
-     *  used Regular Expression library
-     *
-     * TODO: Is this still required for PCRE?  If not, does it *work* with PCRE?
-     */
-    newrule->output = apr_pstrdup(cmd->pool, a2);
+static apr_status_t run_rewritemap_programs(server_rec *s, apr_pool_t *p)
+{
+    rewrite_server_conf *conf;
+    apr_hash_index_t *hi;
+    apr_status_t rc;
+    int lock_warning_issued = 0;
 
-    /* now, if the server or per-dir config holds an
-     * array of RewriteCond entries, we take it for us
-     * and clear the array
+    conf = ap_get_module_config(s->module_config, &rewrite_module);
+
+    /*  If the engine isn't turned on,
+     *  don't even try to do anything.
      */
-    if (cmd->path == NULL) {  /* is server command */
-        newrule->rewriteconds   = sconf->rewriteconds;
-        sconf->rewriteconds = apr_array_make(cmd->pool, 2,
-                                            sizeof(rewritecond_entry));
-    }
-    else {                    /* is per-directory command */
-        newrule->rewriteconds   = dconf->rewriteconds;
-        dconf->rewriteconds = apr_array_make(cmd->pool, 2,
-                                            sizeof(rewritecond_entry));
+    if (conf->state == ENGINE_DISABLED) {
+        return APR_SUCCESS;
     }
 
-    return NULL;
-}
-
-static const char *cmd_rewriterule_parseflagfield(apr_pool_t *p,
-                                                  rewriterule_entry *cfg,
-                                                  char *str)
-{
-    char *cp;
-    char *cp1;
-    char *cp2;
-    char *cp3;
-    char *key;
-    char *val;
-    const char *err;
+    for (hi = apr_hash_first(p, conf->rewritemaps); hi; hi = apr_hash_next(hi)){
+        apr_file_t *fpin = NULL;
+        apr_file_t *fpout = NULL;
+        rewritemap_entry *map;
+        void *val;
 
-    if (str[0] != '[' || str[strlen(str)-1] != ']') {
-        return "RewriteRule: bad flag delimiters";
-    }
+        apr_hash_this(hi, NULL, NULL, &val);
+        map = val;
 
-    cp = str+1;
-    str[strlen(str)-1] = ','; /* for simpler parsing */
-    for ( ; *cp != '\0'; ) {
-        /* skip whitespaces */
-        for ( ; (*cp == ' ' || *cp == '\t') && *cp != '\0'; cp++)
-            ;
-        if (*cp == '\0') {
-            break;
+        if (map->type != MAPTYPE_PRG) {
+            continue;
         }
-        cp1 = cp;
-        if ((cp2 = strchr(cp, ',')) != NULL) {
-            cp = cp2+1;
-            for ( ; (*(cp2-1) == ' ' || *(cp2-1) == '\t'); cp2--)
-                ;
-            *cp2 = '\0';
-            if ((cp3 = strchr(cp1, '=')) != NULL) {
-                *cp3 = '\0';
-                key = cp1;
-                val = cp3+1;
-            }
-            else {
-                key = cp1;
-                val = "";
-            }
-            if ((err = cmd_rewriterule_setflag(p, cfg, key, val)) != NULL) {
-                return err;
-            }
+        if (!(map->argv[0]) || !*(map->argv[0]) || map->fpin || map->fpout) {
+            continue;
         }
-        else {
-            break;
+
+        if (!lock_warning_issued && (!lockname || !*lockname)) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, s,
+                         "mod_rewrite: Running external rewrite maps "
+                         "without defining a RewriteLock is DANGEROUS!");
+            ++lock_warning_issued;
+        }
+
+        rc = rewritemap_program_child(p, map->argv[0], map->argv,
+                                      &fpout, &fpin);
+        if (rc != APR_SUCCESS || fpin == NULL || fpout == NULL) {
+            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
+                         "mod_rewrite: could not start RewriteMap "
+                         "program %s", map->checkfile);
+            return rc;
         }
+        map->fpin  = fpin;
+        map->fpout = fpout;
     }
 
-    return NULL;
+    return APR_SUCCESS;
 }
 
-static const char *cmd_rewriterule_setflag(apr_pool_t *p,
-                                           rewriterule_entry *cfg,
-                                           char *key, char *val)
+
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                  Lookup functions
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
+
+static char *lookup_map_txtfile(request_rec *r, const char *file, char *key)
 {
-    int status = 0;
-    int i;
+    apr_file_t *fp = NULL;
+    char line[REWRITE_MAX_TXT_MAP_LINE + 1]; /* +1 for \0 */
+    char *value, *keylast;
+
+    if (apr_file_open(&fp, file, APR_READ|APR_BUFFERED, APR_OS_DEFAULT,
+                      r->pool) != APR_SUCCESS) {
+        return NULL;
+    }
+
+    keylast = key + strlen(key);
+    value = NULL;
+    while (apr_file_gets(line, sizeof(line), fp) == APR_SUCCESS) {
+        char *p, *c;
 
-    if (   strcasecmp(key, "redirect") == 0
-        || strcasecmp(key, "R") == 0       ) {
-        cfg->flags |= RULEFLAG_FORCEREDIRECT;
-        if (strlen(val) > 0) {
-            if (strcasecmp(val, "permanent") == 0) {
-                status = HTTP_MOVED_PERMANENTLY;
-            }
-            else if (strcasecmp(val, "temp") == 0) {
-                status = HTTP_MOVED_TEMPORARILY;
-            }
-            else if (strcasecmp(val, "seeother") == 0) {
-                status = HTTP_SEE_OTHER;
-            }
-            else if (apr_isdigit(*val)) {
-                status = atoi(val);
-            }
-            if (!ap_is_HTTP_REDIRECT(status)) {
-                return "RewriteRule: invalid HTTP response code "
-                       "for flag 'R'";
-            }
-            cfg->forced_responsecode = status;
-        }
-    }
-    else if (   strcasecmp(key, "noescape") == 0
-        || strcasecmp(key, "NE") == 0       ) {
-        cfg->flags |= RULEFLAG_NOESCAPE;
-    }
-    else if (   strcasecmp(key, "last") == 0
-             || strcasecmp(key, "L") == 0   ) {
-        cfg->flags |= RULEFLAG_LASTRULE;
-    }
-    else if (   strcasecmp(key, "next") == 0
-             || strcasecmp(key, "N") == 0   ) {
-        cfg->flags |= RULEFLAG_NEWROUND;
-    }
-    else if (   strcasecmp(key, "chain") == 0
-             || strcasecmp(key, "C") == 0    ) {
-        cfg->flags |= RULEFLAG_CHAIN;
-    }
-    else if (   strcasecmp(key, "type") == 0
-             || strcasecmp(key, "T") == 0   ) {
-        cfg->forced_mimetype = apr_pstrdup(p, val);
-        ap_str_tolower(cfg->forced_mimetype);
-    }
-    else if (   strcasecmp(key, "env") == 0
-             || strcasecmp(key, "E") == 0   ) {
-        for (i = 0; (cfg->env[i] != NULL) && (i < MAX_ENV_FLAGS); i++)
-            ;
-        if (i < MAX_ENV_FLAGS) {
-            cfg->env[i] = apr_pstrdup(p, val);
-            cfg->env[i+1] = NULL;
+        /* ignore comments and lines starting with whitespaces */
+        if (*line == '#' || apr_isspace(*line)) {
+            continue;
         }
-        else {
-            return "RewriteRule: too many environment flags 'E'";
+
+        p = line;
+        c = key;
+        while (c < keylast && *p == *c && !apr_isspace(*p)) {
+            ++p;
+            ++c;
         }
-    }
-    else  if ( strcasecmp(key, "cookie") == 0 || strcasecmp(key, "CO") == 0) {
-        for (i = 0; (cfg->cookie[i] != NULL) && (i < MAX_COOKIE_FLAGS); i++)
-            ;
-        if (i < MAX_COOKIE_FLAGS) {
-            cfg->cookie[i] = apr_pstrdup(p, val);
-            cfg->cookie[i+1] = NULL;
+
+        /* key doesn't match - ignore. */
+        if (c != keylast || !apr_isspace(*p)) {
+            continue;
         }
-        else {
-            return "RewriteRule: too many cookie flags 'CO'";
+
+        /* jump to the value */
+        while (*p && apr_isspace(*p)) {
+            ++p;
         }
+
+        /* no value? ignore */
+        if (!*p) {
+            continue;
+        }
+
+        /* extract the value and return. */
+        c = p;
+        while (*p && !apr_isspace(*p)) {
+            ++p;
+        }
+        value = apr_pstrmemdup(r->pool, c, p - c);
+        break;
     }
-    else if (   strcasecmp(key, "nosubreq") == 0
-             || strcasecmp(key, "NS") == 0      ) {
-        cfg->flags |= RULEFLAG_IGNOREONSUBREQ;
-    }
-    else if (   strcasecmp(key, "proxy") == 0
-             || strcasecmp(key, "P") == 0      ) {
-        cfg->flags |= RULEFLAG_PROXY;
-    }
-    else if (   strcasecmp(key, "passthrough") == 0
-             || strcasecmp(key, "PT") == 0      ) {
-        cfg->flags |= RULEFLAG_PASSTHROUGH;
-    }
-    else if (   strcasecmp(key, "skip") == 0
-             || strcasecmp(key, "S") == 0   ) {
-        cfg->skip = atoi(val);
-    }
-    else if (   strcasecmp(key, "forbidden") == 0
-             || strcasecmp(key, "F") == 0   ) {
-        cfg->flags |= RULEFLAG_FORBIDDEN;
-    }
-    else if (   strcasecmp(key, "gone") == 0
-             || strcasecmp(key, "G") == 0   ) {
-        cfg->flags |= RULEFLAG_GONE;
-    }
-    else if (   strcasecmp(key, "qsappend") == 0
-             || strcasecmp(key, "QSA") == 0   ) {
-        cfg->flags |= RULEFLAG_QSAPPEND;
-    }
-    else if (   strcasecmp(key, "nocase") == 0
-             || strcasecmp(key, "NC") == 0    ) {
-        cfg->flags |= RULEFLAG_NOCASE;
-    }
-    else {
-        return apr_pstrcat(p, "RewriteRule: unknown flag '", key, "'", NULL);
-    }
-    return NULL;
+    apr_file_close(fp);
+
+    return value;
 }
 
+static char *lookup_map_dbmfile(request_rec *r, const char *file,
+                                const char *dbmtype, char *key)
+{
+    apr_dbm_t *dbmfp = NULL;
+    apr_datum_t dbmkey;
+    apr_datum_t dbmval;
+    char *value;
 
-/*
-**
-**  Global Module Initialization
-**
-*/
+    if (apr_dbm_open_ex(&dbmfp, dbmtype, file, APR_DBM_READONLY, APR_OS_DEFAULT,
+                        r->pool) != APR_SUCCESS) {
+        return NULL;
+    }
 
-static int pre_config(apr_pool_t *pconf,
-                      apr_pool_t *plog,
-                      apr_pool_t *ptemp)
-{
-    APR_OPTIONAL_FN_TYPE(ap_register_rewrite_mapfunc) *map_pfn_register;
+    dbmkey.dptr  = key;
+    dbmkey.dsize = strlen(key);
 
-    /* register int: rewritemap handlers */
-    mapfunc_hash = apr_hash_make(pconf);
-    map_pfn_register = APR_RETRIEVE_OPTIONAL_FN(ap_register_rewrite_mapfunc);
-    if (map_pfn_register) {
-        map_pfn_register("tolower", rewrite_mapfunc_tolower);
-        map_pfn_register("toupper", rewrite_mapfunc_toupper);
-        map_pfn_register("escape", rewrite_mapfunc_escape);
-        map_pfn_register("unescape", rewrite_mapfunc_unescape);
+    if (apr_dbm_fetch(dbmfp, dbmkey, &dbmval) == APR_SUCCESS && dbmval.dptr) {
+        value = apr_pstrmemdup(r->pool, dbmval.dptr, dbmval.dsize);
     }
-    return OK;
+    else {
+        value = NULL;
+    }
+
+    apr_dbm_close(dbmfp);
+
+    return value;
 }
 
-static int post_config(apr_pool_t *p,
-                       apr_pool_t *plog,
-                       apr_pool_t *ptemp,
-                       server_rec *s)
+static char *lookup_map_program(request_rec *r, apr_file_t *fpin,
+                                apr_file_t *fpout, char *key)
 {
+    char *buf;
+    char c;
+    apr_size_t i, nbytes, combined_len = 0;
     apr_status_t rv;
-    void *data;
-    int first_time = 0;
-    const char *userdata_key = "rewrite_init_module";
-
-    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
-    if (!data) {
-        first_time = 1;
-        apr_pool_userdata_set((const void *)1, userdata_key,
-                              apr_pool_cleanup_null, s->process->pool);
-    }
+    const char *eol = APR_EOL_STR;
+    apr_size_t eolc = 0;
+    int found_nl = 0;
+    result_list *buflist = NULL, *curbuf = NULL;
 
-    /* check if proxy module is available */
-    proxy_available = (ap_find_linked_module("mod_proxy.c") != NULL);
+#ifndef NO_WRITEV
+    struct iovec iova[2];
+    apr_size_t niov;
+#endif
 
-    /* create the rewriting lockfiles in the parent */
-    if ((rv = apr_global_mutex_create(&rewrite_log_lock, NULL,
-                                      APR_LOCK_DEFAULT, p)) != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
-                     "mod_rewrite: could not create rewrite_log_lock");
-        return HTTP_INTERNAL_SERVER_ERROR;
+    /* when `RewriteEngine off' was used in the per-server
+     * context then the rewritemap-programs were not spawned.
+     * In this case using such a map (usually in per-dir context)
+     * is useless because it is not available.
+     *
+     * newlines in the key leave bytes in the pipe and cause
+     * bad things to happen (next map lookup will use the chars
+     * after the \n instead of the new key etc etc - in other words,
+     * the Rewritemap falls out of sync with the requests).
+     */
+    if (fpin == NULL || fpout == NULL || ap_strchr(key, '\n')) {
+        return NULL;
     }
 
-#ifdef MOD_REWRITE_SET_MUTEX_PERMS
-    rv = unixd_set_global_mutex_perms(rewrite_log_lock);
-    if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
-                     "mod_rewrite: Could not set permissions on "
-                     "rewrite_log_lock; check User and Group directives");
-        return HTTP_INTERNAL_SERVER_ERROR;
+    /* take the lock */
+    if (rewrite_mapr_lock_acquire) {
+        rv = apr_global_mutex_lock(rewrite_mapr_lock_acquire);
+        if (rv != APR_SUCCESS) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+                          "apr_global_mutex_lock(rewrite_mapr_lock_acquire) "
+                          "failed");
+            return NULL; /* Maybe this should be fatal? */
+        }
     }
+
+    /* write out the request key */
+#ifdef NO_WRITEV
+    nbytes = strlen(key);
+    apr_file_write(fpin, key, &nbytes);
+    nbytes = 1;
+    apr_file_write(fpin, "\n", &nbytes);
+#else
+    iova[0].iov_base = key;
+    iova[0].iov_len = strlen(key);
+    iova[1].iov_base = "\n";
+    iova[1].iov_len = 1;
+
+    niov = 2;
+    apr_file_writev(fpin, iova, niov, &nbytes);
 #endif
 
-    rv = rewritelock_create(s, p);
-    if (rv != APR_SUCCESS) {
-        return HTTP_INTERNAL_SERVER_ERROR;
-    }
+    buf = apr_palloc(r->pool, REWRITE_PRG_MAP_BUF + 1);
 
-    apr_pool_cleanup_register(p, (void *)s, rewritelock_remove,
-                              apr_pool_cleanup_null);
+    /* read in the response value */
+    nbytes = 1;
+    apr_file_read(fpout, &c, &nbytes);
+    do {
+        i = 0;
+        while (nbytes == 1 && (i < REWRITE_PRG_MAP_BUF)) {
+            if (c == eol[eolc]) {
+                if (!eol[++eolc]) {
+                    /* remove eol from the buffer */
+                    --eolc;
+                    if (i < eolc) {
+                        curbuf->len -= eolc-i;
+                        i = 0;
+                    }
+                    else {
+                        i -= eolc;
+                    }
+                    ++found_nl;
+                    break;
+                }
+            }
 
-    /* step through the servers and
-     * - open each rewriting logfile
-     * - open the RewriteMap prg:xxx programs
-     */
-    for (; s; s = s->next) {
-        if (!open_rewritelog(s, p)) {
-            return HTTP_INTERNAL_SERVER_ERROR;
-        }
+            /* only partial (invalid) eol sequence -> reset the counter */
+            else if (eolc) {
+                eolc = 0;
+            }
 
-        if (!first_time) {
-            if (run_rewritemap_programs(s, p) != APR_SUCCESS) {
-                return HTTP_INTERNAL_SERVER_ERROR;
+            /* catch binary mode, e.g. on Win32 */
+            else if (c == '\n') {
+                ++found_nl;
+                break;
             }
+
+            buf[i++] = c;
+            apr_file_read(fpout, &c, &nbytes);
         }
-    }
 
-    rewrite_ssl_lookup = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
-    rewrite_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
+        /* well, if there wasn't a newline yet, we need to read further */
+        if (buflist || (nbytes == 1 && !found_nl)) {
+            if (!buflist) {
+                curbuf = buflist = apr_palloc(r->pool, sizeof(*buflist));
+            }
+            else if (i) {
+                curbuf->next = apr_palloc(r->pool, sizeof(*buflist));
+                curbuf = curbuf->next;
 
-    return OK;
-}
+            }
+            curbuf->next = NULL;
 
+            if (i) {
+                curbuf->string = buf;
+                curbuf->len = i;
+                combined_len += i;
+                buf = apr_palloc(r->pool, REWRITE_PRG_MAP_BUF);
+            }
 
-/*
-**
-**  Per-Child Module Initialization
-**  [called after a child process is spawned]
-**
-*/
+            if (nbytes == 1 && !found_nl) {
+                i = 0;
+                continue;
+            }
+        }
 
-static void init_child(apr_pool_t *p, server_rec *s)
-{
-    apr_status_t rv;
+        break;
+    } while (1);
 
-    if (lockname != NULL && *(lockname) != '\0') {
-        rv = apr_global_mutex_child_init(&rewrite_mapr_lock_acquire,
-                                         lockname, p);
-        if (rv != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
-                         "mod_rewrite: could not init rewrite_mapr_lock_acquire"
-                         " in child");
+    /* concat the stuff */
+    if (buflist) {
+        char *p;
+
+        p = buf = apr_palloc(r->pool, combined_len + 1); /* \0 */
+        while (buflist) {
+            if (buflist->len) {
+                memcpy(p, buflist->string, buflist->len);
+                p += buflist->len;
+            }
+            buflist = buflist->next;
         }
+        *p = '\0';
+        i = combined_len;
+    }
+    else {
+        buf[i] = '\0';
     }
 
-    rv = apr_global_mutex_child_init(&rewrite_log_lock, NULL, p);
-    if (rv != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
-                     "mod_rewrite: could not init rewrite log lock in child");
+    /* give the lock back */
+    if (rewrite_mapr_lock_acquire) {
+        rv = apr_global_mutex_unlock(rewrite_mapr_lock_acquire);
+        if (rv != APR_SUCCESS) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+                          "apr_global_mutex_unlock(rewrite_mapr_lock_acquire) "
+                          "failed");
+            return NULL; /* Maybe this should be fatal? */
+        }
     }
-    
-    /* create the lookup cache */
-    cachep = init_cache(p);
-}
 
+    /* catch the "failed" case */
+    if (i == 4 && !strcasecmp(buf, "NULL")) {
+        return NULL;
+    }
 
-/*
-** +-------------------------------------------------------+
-** |                                                       |
-** |                     runtime hooks
-** |                                                       |
-** +-------------------------------------------------------+
-*/
+    return buf;
+}
 
 /*
-**
-**  URI-to-filename hook
-**
-**  [used for the rewriting engine triggered by
-**  the per-server 'RewriteRule' directives]
-**
-*/
-
-static int hook_uri2file(request_rec *r)
+ * generic map lookup
+ */
+static char *lookup_map(request_rec *r, char *name, char *key)
 {
-    rewrite_perdir_conf *dconf;
     rewrite_server_conf *conf;
-    const char *saved_rulestatus;
-    const char *var;
-    const char *thisserver;
-    char *thisport;
-    const char *thisurl;
-    char buf[512];
-    char docroot[512];
-    const char *ccp;
-    unsigned int port;
-    int rulestatus;
-    int n;
-    int l;
+    rewritemap_entry *s;
+    char *value;
+    apr_finfo_t st;
+    apr_status_t rv;
 
-    /*
-     *  retrieve the config structures
-     */
+    /* get map configuration */
     conf = ap_get_module_config(r->server->module_config, &rewrite_module);
+    s = apr_hash_get(conf->rewritemaps, name, APR_HASH_KEY_STRING);
 
-    dconf = (rewrite_perdir_conf *)ap_get_module_config(r->per_dir_config,
-                                                        &rewrite_module);
+    /* map doesn't exist */
+    if (!s) {
+        return NULL;
+    }
 
+    switch (s->type) {
     /*
-     *  only do something under runtime if the engine is really enabled,
-     *  else return immediately!
+     * Text file map (perhaps random)
      */
-    if (!dconf || dconf->state == ENGINE_DISABLED) {
-        return DECLINED;
-    }
+    case MAPTYPE_RND:
+    case MAPTYPE_TXT:
+        rv = apr_stat(&st, s->checkfile, APR_FINFO_MIN, r->pool);
+        if (rv != APR_SUCCESS) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+                          "mod_rewrite: can't access text RewriteMap file %s",
+                          s->checkfile);
+            rewritelog((r, 1, NULL,
+                        "can't open RewriteMap file, see error log"));
+            return NULL;
+        }
+
+        value = get_cache_value(s->cachename, st.mtime, key, r->pool);
+        if (!value) {
+            rewritelog((r, 6, NULL,
+                        "cache lookup FAILED, forcing new map lookup"));
+
+            value = lookup_map_txtfile(r, s->datafile, key);
+            if (!value) {
+                rewritelog((r, 5, NULL, "map lookup FAILED: map=%s[txt] key=%s",
+                            name, key));
+                set_cache_value(s->cachename, st.mtime, key, "");
+                return NULL;
+            }
+
+            rewritelog((r, 5, NULL,"map lookup OK: map=%s[txt] key=%s -> val=%s",
+                        name, key, value));
+            set_cache_value(s->cachename, st.mtime, key, value);
+        }
+        else {
+            rewritelog((r,5,NULL,"cache lookup OK: map=%s[txt] key=%s -> val=%s",
+                        name, key, value));
+        }
+
+        if (s->type == MAPTYPE_RND && *value) {
+            value = select_random_value_part(r, value);
+            rewritelog((r, 5, NULL, "randomly chosen the subvalue `%s'",value));
+        }
+
+        return *value ? value : NULL;
 
     /*
-     *  check for the ugly API case of a virtual host section where no
-     *  mod_rewrite directives exists. In this situation we became no chance
-     *  by the API to setup our default per-server config so we have to
-     *  on-the-fly assume we have the default config. But because the default
-     *  config has a disabled rewriting engine we are lucky because can
-     *  just stop operating now.
+     * DBM file map
      */
-    if (conf->server != r->server) {
-        return DECLINED;
-    }
+    case MAPTYPE_DBM:
+        rv = apr_stat(&st, s->checkfile, APR_FINFO_MIN, r->pool);
+        if (rv != APR_SUCCESS) {
+            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
+                          "mod_rewrite: can't access DBM RewriteMap file %s",
+                          s->checkfile);
+            rewritelog((r, 1, NULL,
+                        "can't open DBM RewriteMap file, see error log"));
+            return NULL;
+        }
 
-    /* Unless the anyuri option is set, ensure that the input to the
-     * first rule really is a URL-path, avoiding security issues with
-     * poorly configured rules.  See CVE-2011-3368, CVE-2011-4317. */
-    if ((dconf->options & OPTION_ANYURI) == 0
-        && ((r->unparsed_uri[0] == '*' && r->unparsed_uri[1] == '\0')
-            || !r->uri || r->uri[0] != '/')) {
-        rewritelog(r, 8, "Declining, request-URI '%s' is not a URL-path. "
-                    "Consult the manual entry for the RewriteOptions directive "
-                    "for options and caveats about matching other strings.",
-                    r->uri);
-        return DECLINED;
-    }
+        value = get_cache_value(s->cachename, st.mtime, key, r->pool);
+        if (!value) {
+            rewritelog((r, 6, NULL,
+                        "cache lookup FAILED, forcing new map lookup"));
+
+            value = lookup_map_dbmfile(r, s->datafile, s->dbmtype, key);
+            if (!value) {
+                rewritelog((r, 5, NULL, "map lookup FAILED: map=%s[dbm] key=%s",
+                            name, key));
+                set_cache_value(s->cachename, st.mtime, key, "");
+                return NULL;
+            }
+
+            rewritelog((r, 5, NULL, "map lookup OK: map=%s[dbm] key=%s -> "
+                        "val=%s", name, key, value));
+
+            set_cache_value(s->cachename, st.mtime, key, value);
+            return value;
+        }
+
+        rewritelog((r, 5, NULL, "cache lookup OK: map=%s[dbm] key=%s -> val=%s",
+                    name, key, value));
+        return *value ? value : NULL;
 
     /*
-     *  add the SCRIPT_URL variable to the env. this is a bit complicated
-     *  due to the fact that apache uses subrequests and internal redirects
+     * Program file map
      */
+    case MAPTYPE_PRG:
+        value = lookup_map_program(r, s->fpin, s->fpout, key);
+        if (!value) {
+            rewritelog((r, 5,NULL,"map lookup FAILED: map=%s key=%s", name,
+                        key));
+            return NULL;
+        }
 
-    if (r->main == NULL) {
-         var = apr_pstrcat(r->pool, "REDIRECT_", ENVVAR_SCRIPT_URL, NULL);
-         var = apr_table_get(r->subprocess_env, var);
-         if (var == NULL) {
-             apr_table_setn(r->subprocess_env, ENVVAR_SCRIPT_URL, r->uri);
-         }
-         else {
-             apr_table_setn(r->subprocess_env, ENVVAR_SCRIPT_URL, var);
-         }
-    }
-    else {
-         var = apr_table_get(r->main->subprocess_env, ENVVAR_SCRIPT_URL);
-         apr_table_setn(r->subprocess_env, ENVVAR_SCRIPT_URL, var);
-    }
+        rewritelog((r, 5, NULL, "map lookup OK: map=%s key=%s -> val=%s",
+                    name, key, value));
+        return value;
 
     /*
-     *  create the SCRIPT_URI variable for the env
+     * Internal Map
      */
+    case MAPTYPE_INT:
+        value = s->func(r, key);
+        if (!value) {
+            rewritelog((r, 5,NULL,"map lookup FAILED: map=%s key=%s", name,
+                        key));
+            return NULL;
+        }
 
-    /* add the canonical URI of this URL */
-    thisserver = ap_get_server_name(r);
-    port = ap_get_server_port(r);
-    if (ap_is_default_port(port, r)) {
-        thisport = "";
+        rewritelog((r, 5, NULL, "map lookup OK: map=%s key=%s -> val=%s",
+                    name, key, value));
+        return value;
     }
-    else {
-        apr_snprintf(buf, sizeof(buf), ":%u", port);
-        thisport = buf;
+
+    return NULL;
+}
+
+/*
+ * lookup a HTTP header and set VARY note
+ */
+static const char *lookup_header(const char *name, rewrite_ctx *ctx)
+{
+    const char *val = apr_table_get(ctx->r->headers_in, name);
+
+    if (val) {
+        ctx->vary_this = ctx->vary_this
+                         ? apr_pstrcat(ctx->r->pool, ctx->vary_this, ", ",
+                                       name, NULL)
+                         : apr_pstrdup(ctx->r->pool, name);
     }
-    thisurl = apr_table_get(r->subprocess_env, ENVVAR_SCRIPT_URL);
 
-    /* set the variable */
-    var = apr_pstrcat(r->pool, ap_http_method(r), "://", thisserver, thisport,
-                      thisurl, NULL);
-    apr_table_setn(r->subprocess_env, ENVVAR_SCRIPT_URI, var);
+    return val;
+}
 
-    if (!(saved_rulestatus = apr_table_get(r->notes,"mod_rewrite_rewritten"))) {
-        /* if filename was not initially set,
-         * we start with the requested URI
-         */
-        if (r->filename == NULL) {
-            r->filename = apr_pstrdup(r->pool, r->uri);
-            rewritelog(r, 2, "init rewrite engine with requested uri %s",
-                       r->filename);
-        }
-        else {
-            rewritelog(r, 2, "init rewrite engine with passed filename %s."
-                       " Original uri = %s", r->filename, r->uri);
-        }
+/*
+ * lookahead helper function
+ * Determine the correct URI path in perdir context
+ */
+static APR_INLINE const char *la_u(rewrite_ctx *ctx)
+{
+    rewrite_perdir_conf *conf;
 
-        /*
-         *  now apply the rules ...
-         */
-        rulestatus = apply_rewrite_list(r, conf->rewriterules, NULL);
-        apr_table_set(r->notes,"mod_rewrite_rewritten",
-                      apr_psprintf(r->pool,"%d",rulestatus));
+    if (*ctx->uri == '/') {
+        return ctx->uri;
     }
-    else {
-        rewritelog(r, 2,
-                   "uri already rewritten. Status %s, Uri %s, r->filename %s",
-                   saved_rulestatus, r->uri, r->filename);
-        rulestatus = atoi(saved_rulestatus);
+
+    conf = ap_get_module_config(ctx->r->per_dir_config, &rewrite_module);
+
+    return apr_pstrcat(ctx->r->pool, conf->baseurl
+                                     ? conf->baseurl : conf->directory,
+                       ctx->uri, NULL);
+}
+
+/*
+ * generic variable lookup
+ */
+static char *lookup_variable(char *var, rewrite_ctx *ctx)
+{
+    const char *result;
+    request_rec *r = ctx->r;
+    apr_size_t varlen = strlen(var);
+
+    /* fast exit */
+    if (varlen < 4) {
+        return apr_pstrdup(r->pool, "");
     }
 
-    if (rulestatus) {
-        unsigned skip;
+    result = NULL;
 
-        if (strlen(r->filename) > 6 &&
-            strncmp(r->filename, "proxy:", 6) == 0) {
-            /* it should be go on as an internal proxy request */
+    /* fast tests for variable length variables (sic) first */
+    if (var[3] == ':') {
+        if (var[4] && !strncasecmp(var, "ENV", 3)) {
+            var += 4;
+            result = apr_table_get(r->notes, var);
 
-            /* check if the proxy module is enabled, so
-             * we can actually use it!
-             */
-            if (!proxy_available) {
-                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                              "attempt to make remote request from mod_rewrite "
-                              "without proxy enabled: %s", r->filename);
-                return HTTP_FORBIDDEN;
+            if (!result) {
+                result = apr_table_get(r->subprocess_env, var);
             }
-
-            /* make sure the QUERY_STRING and
-             * PATH_INFO parts get incorporated
-             */
-            if (r->path_info != NULL) {
-                r->filename = apr_pstrcat(r->pool, r->filename,
-                                          r->path_info, NULL);
+            if (!result) {
+                result = getenv(var);
             }
-            if (r->args != NULL &&
-                r->uri == r->unparsed_uri) {
-                /* see proxy_http:proxy_http_canon() */
-                r->filename = apr_pstrcat(r->pool, r->filename,
-                                          "?", r->args, NULL);
+        }
+        else if (var[4] && !strncasecmp(var, "SSL", 3) && rewrite_ssl_lookup) {
+            result = rewrite_ssl_lookup(r->pool, r->server, r->connection, r,
+                                        var + 4);
+        }
+    }
+    else if (var[4] == ':') {
+        if (var[5]) {
+            request_rec *rr;
+            const char *path;
+
+            if (!strncasecmp(var, "HTTP", 4)) {
+                result = lookup_header(var+5, ctx);
             }
+            else if (!strncasecmp(var, "LA-U", 4)) {
+                if (ctx->uri && subreq_ok(r)) {
+                    path = ctx->perdir ? la_u(ctx) : ctx->uri;
+                    rr = ap_sub_req_lookup_uri(path, r, NULL);
+                    ctx->r = rr;
+                    result = apr_pstrdup(r->pool, lookup_variable(var+5, ctx));
+                    ctx->r = r;
+                    ap_destroy_sub_req(rr);
 
-            /* now make sure the request gets handled by the proxy handler */
-            if (PROXYREQ_NONE == r->proxyreq) {
-                r->proxyreq = PROXYREQ_REVERSE;
+                    rewritelog((r, 5, ctx->perdir, "lookahead: path=%s var=%s "
+                                "-> val=%s", path, var+5, result));
+
+                    return (char *)result;
+                }
             }
-            r->handler  = "proxy-server";
+            else if (!strncasecmp(var, "LA-F", 4)) {
+                if (ctx->uri && subreq_ok(r)) {
+                    path = ctx->uri;
+                    if (ctx->perdir && *path == '/') {
+                        /* sigh, the user wants a file based subrequest, but
+                         * we can't do one, since we don't know what the file
+                         * path is! In this case behave like LA-U.
+                         */
+                        rr = ap_sub_req_lookup_uri(path, r, NULL);
+                    }
+                    else {
+                        if (ctx->perdir) {
+                            rewrite_perdir_conf *conf;
 
-            rewritelog(r, 1, "go-ahead with proxy request %s [OK]",
-                       r->filename);
-            return OK;
-        }
-        else if ((skip = is_absolute_uri(r->filename)) > 0) {
-            /* it was finally rewritten to a remote URL */
+                            conf = ap_get_module_config(r->per_dir_config,
+                                                        &rewrite_module);
 
-            if (rulestatus != ACTION_NOESCAPE) {
-                rewritelog(r, 1, "escaping %s for redirect", r->filename);
-                r->filename = escape_absolute_uri(r->pool, r->filename, skip);
+                            path = apr_pstrcat(r->pool, conf->directory, path,
+                                               NULL);
+                        }
+
+                        rr = ap_sub_req_lookup_file(path, r, NULL);
+                    }
+
+                    ctx->r = rr;
+                    result = apr_pstrdup(r->pool, lookup_variable(var+5, ctx));
+                    ctx->r = r;
+                    ap_destroy_sub_req(rr);
+
+                    rewritelog((r, 5, ctx->perdir, "lookahead: path=%s var=%s "
+                                "-> val=%s", path, var+5, result));
+
+                    return (char *)result;
+                }
             }
+        }
+    }
 
-            /* append the QUERY_STRING part */
-            if (r->args) {
-                r->filename = apr_pstrcat(r->pool, r->filename, "?",
-                                          (rulestatus == ACTION_NOESCAPE)
-                                            ? r->args
-                                            : ap_escape_uri(r->pool, r->args),
-                                          NULL);
+    /* well, do it the hard way */
+    else {
+        char *p;
+        apr_time_exp_t tm;
+
+        /* can't do this above, because of the getenv call */
+        for (p = var; *p; ++p) {
+            *p = apr_toupper(*p);
+        }
+
+        switch (varlen) {
+        case  4:
+            if (!strcmp(var, "TIME")) {
+                apr_time_exp_lt(&tm, apr_time_now());
+                result = apr_psprintf(r->pool, "%04d%02d%02d%02d%02d%02d",
+                                      tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday,
+                                      tm.tm_hour, tm.tm_min, tm.tm_sec);
+                rewritelog((r, 1, ctx->perdir, "RESULT='%s'", result));
+                return (char *)result;
             }
+            break;
 
-            /* determine HTTP redirect response code */
-            if (ap_is_HTTP_REDIRECT(r->status)) {
-                n = r->status;
-                r->status = HTTP_OK; /* make Apache kernel happy */
+        case  5:
+            if (!strcmp(var, "HTTPS")) {
+                int flag = rewrite_is_https && rewrite_is_https(r->connection);
+                return apr_pstrdup(r->pool, flag ? "on" : "off");
             }
-            else {
-                n = HTTP_MOVED_TEMPORARILY;
+            break;
+
+        case  8:
+            switch (var[6]) {
+            case 'A':
+                if (!strcmp(var, "TIME_DAY")) {
+                    apr_time_exp_lt(&tm, apr_time_now());
+                    return apr_psprintf(r->pool, "%02d", tm.tm_mday);
+                }
+                break;
+
+            case 'E':
+                if (!strcmp(var, "TIME_SEC")) {
+                    apr_time_exp_lt(&tm, apr_time_now());
+                    return apr_psprintf(r->pool, "%02d", tm.tm_sec);
+                }
+                break;
+
+            case 'I':
+                if (!strcmp(var, "TIME_MIN")) {
+                    apr_time_exp_lt(&tm, apr_time_now());
+                    return apr_psprintf(r->pool, "%02d", tm.tm_min);
+                }
+                break;
+
+            case 'O':
+                if (!strcmp(var, "TIME_MON")) {
+                    apr_time_exp_lt(&tm, apr_time_now());
+                    return apr_psprintf(r->pool, "%02d", tm.tm_mon+1);
+                }
+                break;
             }
+            break;
 
-            /* now do the redirection */
-            apr_table_setn(r->headers_out, "Location", r->filename);
-            rewritelog(r, 1, "redirect to %s [REDIRECT/%d]", r->filename, n);
-            return n;
-        }
-        else if (strlen(r->filename) > 10 &&
-                 strncmp(r->filename, "forbidden:", 10) == 0) {
-            /* This URLs is forced to be forbidden for the requester */
-            return HTTP_FORBIDDEN;
-        }
-        else if (strlen(r->filename) > 5 &&
-                 strncmp(r->filename, "gone:", 5) == 0) {
-            /* This URLs is forced to be gone */
-            return HTTP_GONE;
-        }
-        else if (strlen(r->filename) > 12 &&
-                 strncmp(r->filename, "passthrough:", 12) == 0) {
-            /*
-             * Hack because of underpowered API: passing the current
-             * rewritten filename through to other URL-to-filename handlers
-             * just as it were the requested URL. This is to enable
-             * post-processing by mod_alias, etc.  which always act on
-             * r->uri! The difference here is: We do not try to
-             * add the document root
-             */
-            r->uri = apr_pstrdup(r->pool, r->filename+12);
-            return DECLINED;
-        }
-        else {
-            /* it was finally rewritten to a local path */
+        case  9:
+            switch (var[7]) {
+            case 'A':
+                if (var[8] == 'Y' && !strcmp(var, "TIME_WDAY")) {
+                    apr_time_exp_lt(&tm, apr_time_now());
+                    return apr_psprintf(r->pool, "%d", tm.tm_wday);
+                }
+                else if (!strcmp(var, "TIME_YEAR")) {
+                    apr_time_exp_lt(&tm, apr_time_now());
+                    return apr_psprintf(r->pool, "%04d", tm.tm_year+1900);
+                }
+                break;
 
-            /* expand "/~user" prefix */
-#if APR_HAS_USER
-            r->filename = expand_tildepaths(r, r->filename);
-#endif
-            rewritelog(r, 2, "local path result: %s", r->filename);
+            case 'E':
+                if (!strcmp(var, "IS_SUBREQ")) {
+                    result = (r->main ? "true" : "false");
+                }
+                break;
 
-            /* the filename must be either an absolute local path or an
-             * absolute local URL.
-             */
-            if (   *r->filename != '/'
-                && !ap_os_is_path_absolute(r->pool, r->filename)) {
-                return HTTP_BAD_REQUEST;
+            case 'F':
+                if (!strcmp(var, "PATH_INFO")) {
+                    result = r->path_info;
+                }
+                break;
+
+            case 'P':
+                if (!strcmp(var, "AUTH_TYPE")) {
+                    result = r->ap_auth_type;
+                }
+                break;
+
+            case 'S':
+                if (!strcmp(var, "HTTP_HOST")) {
+                    result = lookup_header("Host", ctx);
+                }
+                break;
+
+            case 'U':
+                if (!strcmp(var, "TIME_HOUR")) {
+                    apr_time_exp_lt(&tm, apr_time_now());
+                    return apr_psprintf(r->pool, "%02d", tm.tm_hour);
+                }
+                break;
             }
+            break;
 
-            /* if there is no valid prefix, we have
-             * to emulate the translator from the core and
-             * prefix the filename with document_root
-             *
-             * NOTICE:
-             * We cannot leave out the prefix_stat because
-             * - when we always prefix with document_root
-             *   then no absolute path can be created, e.g. via
-             *   emulating a ScriptAlias directive, etc.
-             * - when we always NOT prefix with document_root
-             *   then the files under document_root have to
-             *   be references directly and document_root
-             *   gets never used and will be a dummy parameter -
-             *   this is also bad
-             *
-             * BUT:
-             * Under real Unix systems this is no problem,
-             * because we only do stat() on the first directory
-             * and this gets cached by the kernel for along time!
-             */
-            n = prefix_stat(r->filename, r->pool);
-            if (n == 0) {
-                if ((ccp = ap_document_root(r)) != NULL) {
-                    l = apr_cpystrn(docroot, ccp, sizeof(docroot)) - docroot;
+        case 11:
+            switch (var[8]) {
+            case 'A':
+                if (!strcmp(var, "SERVER_NAME")) {
+                    result = ap_get_server_name(r);
+                }
+                break;
 
-                    /* always NOT have a trailing slash */
-                    if (docroot[l-1] == '/') {
-                        docroot[l-1] = '\0';
-                    }
-                    if (r->server->path
-                        && !strncmp(r->filename, r->server->path,
-                                    r->server->pathlen)) {
-                        r->filename = apr_pstrcat(r->pool, docroot,
-                                                  (r->filename +
-                                                   r->server->pathlen), NULL);
+            case 'D':
+                if (*var == 'R' && !strcmp(var, "REMOTE_ADDR")) {
+                    result = r->connection->remote_ip;
+                }
+                else if (!strcmp(var, "SERVER_ADDR")) {
+                    result = r->connection->local_ip;
+                }
+                break;
+
+            case 'E':
+                if (*var == 'H' && !strcmp(var, "HTTP_ACCEPT")) {
+                    result = lookup_header("Accept", ctx);
+                }
+                else if (!strcmp(var, "THE_REQUEST")) {
+                    result = r->the_request;
+                }
+                break;
+
+            case 'I':
+                if (!strcmp(var, "API_VERSION")) {
+                    return apr_psprintf(r->pool, "%d:%d",
+                                        MODULE_MAGIC_NUMBER_MAJOR,
+                                        MODULE_MAGIC_NUMBER_MINOR);
+                }
+                break;
+
+            case 'K':
+                if (!strcmp(var, "HTTP_COOKIE")) {
+                    result = lookup_header("Cookie", ctx);
+                }
+                break;
+
+            case 'O':
+                if (*var == 'S' && !strcmp(var, "SERVER_PORT")) {
+                    return apr_psprintf(r->pool, "%u", ap_get_server_port(r));
+                }
+                else if (var[7] == 'H' && !strcmp(var, "REMOTE_HOST")) {
+                    result = ap_get_remote_host(r->connection,r->per_dir_config,
+                                                REMOTE_NAME, NULL);
+                }
+                else if (!strcmp(var, "REMOTE_PORT")) {
+                    return apr_itoa(r->pool, r->connection->remote_addr->port);
+                }
+                break;
+
+            case 'S':
+                if (*var == 'R' && !strcmp(var, "REMOTE_USER")) {
+                    result = r->user;
+                }
+                else if (!strcmp(var, "SCRIPT_USER")) {
+                    result = "<unknown>";
+                    if (r->finfo.valid & APR_FINFO_USER) {
+                        apr_uid_name_get((char **)&result, r->finfo.user,
+                                         r->pool);
                     }
-                    else {
-                        r->filename = apr_pstrcat(r->pool, docroot,
-                                                  r->filename, NULL);
+                }
+                break;
+
+            case 'U':
+                if (!strcmp(var, "REQUEST_URI")) {
+                    result = r->uri;
+                }
+                break;
+            }
+            break;
+
+        case 12:
+            switch (var[3]) {
+            case 'I':
+                if (!strcmp(var, "SCRIPT_GROUP")) {
+                    result = "<unknown>";
+                    if (r->finfo.valid & APR_FINFO_GROUP) {
+                        apr_gid_name_get((char **)&result, r->finfo.group,
+                                         r->pool);
                     }
-                    rewritelog(r, 2, "prefixed with document_root to %s",
-                               r->filename);
                 }
+                break;
+
+            case 'O':
+                if (!strcmp(var, "REMOTE_IDENT")) {
+                    result = ap_get_remote_logname(r);
+                }
+                break;
+
+            case 'P':
+                if (!strcmp(var, "HTTP_REFERER")) {
+                    result = lookup_header("Referer", ctx);
+                }
+                break;
+
+            case 'R':
+                if (!strcmp(var, "QUERY_STRING")) {
+                    result = r->args;
+                }
+                break;
+
+            case 'V':
+                if (!strcmp(var, "SERVER_ADMIN")) {
+                    result = r->server->server_admin;
+                }
+                break;
             }
+            break;
 
-            rewritelog(r, 1, "go-ahead with %s [OK]", r->filename);
-            return OK;
-        }
-    }
-    else {
-        rewritelog(r, 1, "pass through %s", r->filename);
-        return DECLINED;
-    }
-}
+        case 13:
+            if (!strcmp(var, "DOCUMENT_ROOT")) {
+                result = ap_document_root(r);
+            }
+            break;
 
+        case 14:
+            if (*var == 'H' && !strcmp(var, "HTTP_FORWARDED")) {
+                result = lookup_header("Forwarded", ctx);
+            }
+            else if (!strcmp(var, "REQUEST_METHOD")) {
+                result = r->method;
+            }
+            break;
 
-/*
-**
-**  MIME-type hook
-**
-**  [used to support the forced-MIME-type feature]
-**
-*/
+        case 15:
+            switch (var[7]) {
+            case 'E':
+                if (!strcmp(var, "HTTP_USER_AGENT")) {
+                    result = lookup_header("User-Agent", ctx);
+                }
+                break;
 
-static int hook_mimetype(request_rec *r)
-{
-    const char *t;
+            case 'F':
+                if (!strcmp(var, "SCRIPT_FILENAME")) {
+                    result = r->filename; /* same as request_filename (16) */
+                }
+                break;
 
-    /* now check if we have to force a MIME-type */
-    t = apr_table_get(r->notes, REWRITE_FORCED_MIMETYPE_NOTEVAR);
-    if (t == NULL) {
-        return DECLINED;
-    }
-    else {
-        rewritelog(r, 1, "force filename %s to have MIME-type '%s'",
-                   r->filename, t);
-        ap_set_content_type(r, t);
-        return OK;
+            case 'P':
+                if (!strcmp(var, "SERVER_PROTOCOL")) {
+                    result = r->protocol;
+                }
+                break;
+
+            case 'S':
+                if (!strcmp(var, "SERVER_SOFTWARE")) {
+                    result = ap_get_server_version();
+                }
+                break;
+            }
+            break;
+
+        case 16:
+            if (!strcmp(var, "REQUEST_FILENAME")) {
+                result = r->filename; /* same as script_filename (15) */
+            }
+            break;
+
+        case 21:
+            if (!strcmp(var, "HTTP_PROXY_CONNECTION")) {
+                result = lookup_header("Proxy-Connection", ctx);
+            }
+            break;
+        }
     }
+
+    return apr_pstrdup(r->pool, result ? result : "");
 }
 
 
 /*
-**
-**  Fixup hook
-**
-**  [used for the rewriting engine triggered by
-**  the per-directory 'RewriteRule' directives]
-**
-*/
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                 Expansion functions
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
 
-static int hook_fixup(request_rec *r)
+/*
+ * Bracketed expression handling
+ * s points after the opening bracket
+ */
+static APR_INLINE char *find_closing_curly(char *s)
 {
-    rewrite_perdir_conf *dconf;
-    char *cp;
-    char *cp2;
-    const char *ccp;
-    char *prefix;
-    apr_size_t l;
-    int rulestatus;
-    int n;
-    char *ofilename;
-    int is_proxyreq;
-
-    dconf = (rewrite_perdir_conf *)ap_get_module_config(r->per_dir_config,
-                                                        &rewrite_module);
-
-    /* if there is no per-dir config we return immediately */
-    if (dconf == NULL) {
-        return DECLINED;
-    }
+    unsigned depth;
 
-    /* we shouldn't do anything in subrequests */
-    if (r->main != NULL) {
-        return DECLINED;
+    for (depth = 1; *s; ++s) {
+        if (*s == RIGHT_CURLY && --depth == 0) {
+            return s;
+        }
+        else if (*s == LEFT_CURLY) {
+            ++depth;
+        }
     }
 
-    /* if there are no real (i.e. no RewriteRule directives!)
-       per-dir config of us, we return also immediately */
-    if (dconf->directory == NULL) {
-        return DECLINED;
-    }
+    return NULL;
+}
 
-    /*
-     * Proxy request?
-     */
-  	is_proxyreq = (   r->proxyreq && r->filename
-  	               && !strncmp(r->filename, "proxy:", 6));
+static APR_INLINE char *find_char_in_curlies(char *s, int c)
+{
+    unsigned depth;
 
-    /*
-     *  .htaccess file is called before really entering the directory, i.e.:
-     *  URL: http://localhost/foo  and .htaccess is located in foo directory
-     *  Ignore such attempts, since they may lead to undefined behaviour.
-     */
-    if (is_proxyreq) {
-        l = strlen(dconf->directory) - 1;
-        if (r->filename && strlen(r->filename) == l &&
-            (dconf->directory)[l] == '/' &&
-            !strncmp(r->filename, dconf->directory, l)) {
-            return DECLINED;
+    for (depth = 1; *s; ++s) {
+        if (*s == c && depth == 1) {
+            return s;
+        }
+        else if (*s == RIGHT_CURLY && --depth == 0) {
+            return NULL;
+        }
+        else if (*s == LEFT_CURLY) {
+            ++depth;
         }
     }
 
-    /*
-     *  only do something under runtime if the engine is really enabled,
-     *  for this directory, else return immediately!
-     */
-    if (!dconf || dconf->state == ENGINE_DISABLED) {
-        return DECLINED;
-    }
+    return NULL;
+}
 
-    /*
-     *  Do the Options check after engine check, so
-     *  the user is able to explicitely turn RewriteEngine Off.
-     */
-    if (!(ap_allow_options(r) & (OPT_SYM_LINKS | OPT_SYM_OWNER))) {
-        /* FollowSymLinks is mandatory! */
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                     "Options FollowSymLinks or SymLinksIfOwnerMatch is off "
-                     "which implies that RewriteRule directive is forbidden: "
-                     "%s", r->filename);
-        return HTTP_FORBIDDEN;
-    }
+/* perform all the expansions on the input string
+ * putting the result into a new string
+ *
+ * for security reasons this expansion must be performed in a
+ * single pass, otherwise an attacker can arrange for the result
+ * of an earlier expansion to include expansion specifiers that
+ * are interpreted by a later expansion, producing results that
+ * were not intended by the administrator.
+ */
+static char *do_expand(char *input, rewrite_ctx *ctx)
+{
+    result_list *result, *current;
+    result_list sresult[SMALL_EXPANSION];
+    unsigned spc = 0;
+    apr_size_t span, inputlen, outlen;
+    char *p, *c;
+    apr_pool_t *pool = ctx->r->pool;
 
-    /*
-     *  remember the current filename before rewriting for later check
-     *  to prevent deadlooping because of internal redirects
-     *  on final URL/filename which can be equal to the inital one.
-     *  also, we'll restore original r->filename if we decline this
-     *  request
-     */
-    ofilename = r->filename;
+    span = strcspn(input, "\\$%");
+    inputlen = strlen(input);
 
-    if (r->filename == NULL) {
-        r->filename = apr_pstrdup(r->pool, r->uri);
-        rewritelog(r, 2, "init rewrite engine with requested uri %s",
-                   r->filename);
+    /* fast exit */
+    if (inputlen == span) {
+        return apr_pstrdup(pool, input);
     }
 
-    /*
-     *  now apply the rules ...
-     */
-    rulestatus = apply_rewrite_list(r, dconf->rewriterules, dconf->directory);
-    if (rulestatus) {
-        unsigned skip;
-
-        if (strlen(r->filename) > 6 &&
-            strncmp(r->filename, "proxy:", 6) == 0) {
-            /* it should go on as an internal proxy request */
+    /* well, actually something to do */
+    result = current = &(sresult[spc++]);
 
-            /* make sure the QUERY_STRING and
-             * PATH_INFO parts get incorporated
-             * (r->path_info was already appended by the
-             * rewriting engine because of the per-dir context!)
-             */
-            if (r->args != NULL) {
-                r->filename = apr_pstrcat(r->pool, r->filename,
-                                          "?", r->args, NULL);
+    p = input + span;
+    current->next = NULL;
+    current->string = input;
+    current->len = span;
+    outlen = span;
+
+    /* loop for specials */
+    do {
+        /* prepare next entry */
+        if (current->len) {
+            current->next = (spc < SMALL_EXPANSION)
+                            ? &(sresult[spc++])
+                            : (result_list *)apr_palloc(pool,
+                                                        sizeof(result_list));
+            current = current->next;
+            current->next = NULL;
+            current->len = 0;
+        }
+
+        /* escaped character */
+        if (*p == '\\') {
+            current->len = 1;
+            ++outlen;
+            if (!p[1]) {
+                current->string = p;
+                break;
             }
-
-            /* now make sure the request gets handled by the proxy handler */
-            if (PROXYREQ_NONE == r->proxyreq) {
-                r->proxyreq = PROXYREQ_REVERSE;
+            else {
+                current->string = ++p;
+                ++p;
             }
-            r->handler  = "proxy-server";
-
-            rewritelog(r, 1, "[per-dir %s] go-ahead with proxy request "
-                       "%s [OK]", dconf->directory, r->filename);
-            return OK;
         }
-        else if ((skip = is_absolute_uri(r->filename)) > 0) {
-            /* it was finally rewritten to a remote URL */
 
-            /* because we are in a per-dir context
-             * first try to replace the directory with its base-URL
-             * if there is a base-URL available
-             */
-            if (dconf->baseurl != NULL) {
-                /* skip 'scheme://' */
-                cp = r->filename + skip;
+        /* variable or map lookup */
+        else if (p[1] == '{') {
+            char *endp;
 
-                if ((cp = ap_strchr(cp, '/')) != NULL && *(++cp)) {
-                    rewritelog(r, 2,
-                               "[per-dir %s] trying to replace "
-                               "prefix %s with %s",
-                               dconf->directory, dconf->directory,
-                               dconf->baseurl);
+            endp = find_closing_curly(p+2);
+            if (!endp) {
+                current->len = 2;
+                current->string = p;
+                outlen += 2;
+                p += 2;
+            }
+
+            /* variable lookup */
+            else if (*p == '%') {
+                p = lookup_variable(apr_pstrmemdup(pool, p+2, endp-p-2), ctx);
+
+                span = strlen(p);
+                current->len = span;
+                current->string = p;
+                outlen += span;
+                p = endp + 1;
+            }
+
+            /* map lookup */
+            else {     /* *p == '$' */
+                char *key;
 
-                    /* I think, that hack needs an explanation:
-                     * well, here is it:
-                     * mod_rewrite was written for unix systems, were
-                     * absolute file-system paths start with a slash.
-                     * URL-paths _also_ start with slashes, so they
-                     * can be easily compared with system paths.
-                     *
-                     * the following assumes, that the actual url-path
-                     * may be prefixed by the current directory path and
-                     * tries to replace the system path with the RewriteBase
-                     * URL.
-                     * That assumption is true if we use a RewriteRule like
-                     *
-                     * RewriteRule ^foo bar [R]
-                     *
-                     * (see apply_rewrite_rule function)
-                     * However on systems that don't have a / as system
-                     * root this will never match, so we skip the / after the
-                     * hostname and compare/substitute only the stuff after it.
-                     *
-                     * (note that cp was already increased to the right value)
-                     */
-                    cp2 = subst_prefix_path(r, cp, (*dconf->directory == '/')
-                                                   ? dconf->directory + 1
-                                                   : dconf->directory,
-                                            dconf->baseurl + 1);
-                    if (strcmp(cp2, cp) != 0) {
-                        *cp = '\0';
-                        r->filename = apr_pstrcat(r->pool, r->filename,
-                                                  cp2, NULL);
+                /*
+                 * To make rewrite maps useful, the lookup key and
+                 * default values must be expanded, so we make
+                 * recursive calls to do the work. For security
+                 * reasons we must never expand a string that includes
+                 * verbatim data from the network. The recursion here
+                 * isn't a problem because the result of expansion is
+                 * only passed to lookup_map() so it cannot be
+                 * re-expanded, only re-looked-up. Another way of
+                 * looking at it is that the recursion is entirely
+                 * driven by the syntax of the nested curly brackets.
+                 */
+
+                key = find_char_in_curlies(p+2, ':');
+                if (!key) {
+                    current->len = 2;
+                    current->string = p;
+                    outlen += 2;
+                    p += 2;
+                }
+                else {
+                    char *map, *dflt;
+
+                    map = apr_pstrmemdup(pool, p+2, endp-p-2);
+                    key = map + (key-p-2);
+                    *key++ = '\0';
+                    dflt = find_char_in_curlies(key, '|');
+                    if (dflt) {
+                        *dflt++ = '\0';
+                    }
+
+                    /* reuse of key variable as result */
+                    key = lookup_map(ctx->r, map, do_expand(key, ctx));
+
+                    if (!key && dflt && *dflt) {
+                        key = do_expand(dflt, ctx);
+                    }
+
+                    if (key) {
+                        span = strlen(key);
+                        current->len = span;
+                        current->string = key;
+                        outlen += span;
                     }
+
+                    p = endp + 1;
                 }
             }
+        }
 
-            /* now prepare the redirect... */
-            if (rulestatus != ACTION_NOESCAPE) {
-                rewritelog(r, 1, "[per-dir %s] escaping %s for redirect",
-                           dconf->directory, r->filename);
-                r->filename = escape_absolute_uri(r->pool, r->filename, skip);
-            }
+        /* backreference */
+        else if (apr_isdigit(p[1])) {
+            int n = p[1] - '0';
+            backrefinfo *bri = (*p == '$') ? &ctx->briRR : &ctx->briRC;
 
-            /* append the QUERY_STRING part */
-            if (r->args) {
-                r->filename = apr_pstrcat(r->pool, r->filename, "?",
-                                          (rulestatus == ACTION_NOESCAPE)
-                                            ? r->args
-                                            : ap_escape_uri(r->pool, r->args),
-                                          NULL);
-            }
+            /* see ap_pregsub() in server/util.c */
+            if (bri->source && n < AP_MAX_REG_MATCH
+                && bri->regmatch[n].rm_eo > bri->regmatch[n].rm_so) {
+                span = bri->regmatch[n].rm_eo - bri->regmatch[n].rm_so;
 
-            /* determine HTTP redirect response code */
-            if (ap_is_HTTP_REDIRECT(r->status)) {
-                n = r->status;
-                r->status = HTTP_OK; /* make Apache kernel happy */
-            }
-            else {
-                n = HTTP_MOVED_TEMPORARILY;
+                current->len = span;
+                current->string = bri->source + bri->regmatch[n].rm_so;
+                outlen += span;
             }
 
-            /* now do the redirection */
-            apr_table_setn(r->headers_out, "Location", r->filename);
-            rewritelog(r, 1, "[per-dir %s] redirect to %s [REDIRECT/%d]",
-                       dconf->directory, r->filename, n);
-            return n;
-        }
-        else if (strlen(r->filename) > 10 &&
-                 strncmp(r->filename, "forbidden:", 10) == 0) {
-            /* This URL is forced to be forbidden for the requester */
-            return HTTP_FORBIDDEN;
-        }
-        else if (strlen(r->filename) > 5 &&
-                 strncmp(r->filename, "gone:", 5) == 0) {
-            /* This URL is forced to be gone */
-            return HTTP_GONE;
+            p += 2;
         }
+
+        /* not for us, just copy it */
         else {
-            /* it was finally rewritten to a local path */
+            current->len = 1;
+            current->string = p++;
+            ++outlen;
+        }
+
+        /* check the remainder */
+        if (*p && (span = strcspn(p, "\\$%")) > 0) {
+            if (current->len) {
+                current->next = (spc < SMALL_EXPANSION)
+                                ? &(sresult[spc++])
+                                : (result_list *)apr_palloc(pool,
+                                                           sizeof(result_list));
+                current = current->next;
+                current->next = NULL;
+            }
+
+            current->len = span;
+            current->string = p;
+            p += span;
+            outlen += span;
+        }
+
+    } while (p < input+inputlen);
+
+    /* assemble result */
+    c = p = apr_palloc(pool, outlen + 1); /* don't forget the \0 */
+    do {
+        if (result->len) {
+            ap_assert(c+result->len <= p+outlen); /* XXX: can be removed after
+                                                   * extensive testing and
+                                                   * review
+                                                   */
+            memcpy(c, result->string, result->len);
+            c += result->len;
+        }
+        result = result->next;
+    } while (result);
 
-            /* if someone used the PASSTHROUGH flag in per-dir
-             * context we just ignore it. It is only useful
-             * in per-server context
-             */
-            if (strlen(r->filename) > 12 &&
-                strncmp(r->filename, "passthrough:", 12) == 0) {
-                r->filename = apr_pstrdup(r->pool, r->filename+12);
-            }
+    p[outlen] = '\0';
 
-            /* the filename must be either an absolute local path or an
-             * absolute local URL.
-             */
-            if (   *r->filename != '/'
-                && !ap_os_is_path_absolute(r->pool, r->filename)) {
-                return HTTP_BAD_REQUEST;
-            }
+    return p;
+}
 
-            /* Check for deadlooping:
-             * At this point we KNOW that at least one rewriting
-             * rule was applied, but when the resulting URL is
-             * the same as the initial URL, we are not allowed to
-             * use the following internal redirection stuff because
-             * this would lead to a deadloop.
-             */
-            if (ofilename != NULL && strcmp(r->filename, ofilename) == 0) {
-                rewritelog(r, 1, "[per-dir %s] initial URL equal rewritten "
-                           "URL: %s [IGNORING REWRITE]",
-                           dconf->directory, r->filename);
-                return OK;
-            }
+/*
+ * perform all the expansions on the environment variables
+ */
+static void do_expand_env(data_item *env, rewrite_ctx *ctx)
+{
+    char *name, *val;
 
-            /* if there is a valid base-URL then substitute
-             * the per-dir prefix with this base-URL if the
-             * current filename still is inside this per-dir
-             * context. If not then treat the result as a
-             * plain URL
-             */
-            if (dconf->baseurl != NULL) {
-                rewritelog(r, 2,
-                           "[per-dir %s] trying to replace prefix %s with %s",
-                           dconf->directory, dconf->directory, dconf->baseurl);
-                r->filename = subst_prefix_path(r, r->filename,
-                                                dconf->directory,
-                                                dconf->baseurl);
-            }
-            else {
-                /* if no explicit base-URL exists we assume
-                 * that the directory prefix is also a valid URL
-                 * for this webserver and only try to remove the
-                 * document_root if it is prefix
-                 */
-                if ((ccp = ap_document_root(r)) != NULL) {
-                    prefix = apr_pstrdup(r->pool, ccp);
-                    /* always NOT have a trailing slash */
-                    l = strlen(prefix);
-                    if (prefix[l-1] == '/') {
-                        prefix[l-1] = '\0';
-                        l--;
-                    }
-                    if (strncmp(r->filename, prefix, l) == 0) {
-                        rewritelog(r, 2,
-                                   "[per-dir %s] strip document_root "
-                                   "prefix: %s -> %s",
-                                   dconf->directory, r->filename,
-                                   r->filename+l);
-                        r->filename = apr_pstrdup(r->pool, r->filename+l);
-                    }
-                }
-            }
+    while (env) {
+        name = do_expand(env->data, ctx);
+        if ((val = ap_strchr(name, ':')) != NULL) {
+            *val++ = '\0';
 
-            /* now initiate the internal redirect */
-            rewritelog(r, 1, "[per-dir %s] internal redirect with %s "
-                       "[INTERNAL REDIRECT]", dconf->directory, r->filename);
-            r->filename = apr_pstrcat(r->pool, "redirect:", r->filename, NULL);
-            r->handler = "redirect-handler";
-            return OK;
+            apr_table_set(ctx->r->subprocess_env, name, val);
+            rewritelog((ctx->r, 5, NULL, "setting env variable '%s' to '%s'",
+                        name, val));
         }
+
+        env = env->next;
     }
-    else {
-        rewritelog(r, 1, "[per-dir %s] pass through %s",
-                   dconf->directory, r->filename);
-        r->filename = ofilename;
-        return DECLINED;
-    }
-}
 
+    return;
+}
 
 /*
-**
-**  Content-Handlers
-**
-**  [used for redirect support]
-**
-*/
-
-static int handler_redirect(request_rec *r)
+ * perform all the expansions on the cookies
+ *
+ * TODO: use cached time similar to how logging does it
+ */
+static void add_cookie(request_rec *r, char *s)
 {
-    if (strcmp(r->handler, "redirect-handler")) {
-        return DECLINED;
-    }
+    char *var;
+    char *val;
+    char *domain;
+    char *expires;
+    char *path;
 
-    /* just make sure that we are really meant! */
-    if (strncmp(r->filename, "redirect:", 9) != 0) {
-        return DECLINED;
+    char *tok_cntx;
+    char *cookie;
+
+    var = apr_strtok(s, ":", &tok_cntx);
+    val = apr_strtok(NULL, ":", &tok_cntx);
+    domain = apr_strtok(NULL, ":", &tok_cntx);
+
+    if (var && val && domain) {
+        request_rec *rmain = r;
+        char *notename;
+        void *data;
+
+        while (rmain->main) {
+            rmain = rmain->main;
+        }
+
+        notename = apr_pstrcat(rmain->pool, var, "_rewrite", NULL);
+        apr_pool_userdata_get(&data, notename, rmain->pool);
+        if (!data) {
+            char *exp_time = NULL;
+
+            expires = apr_strtok(NULL, ":", &tok_cntx);
+            path = expires ? apr_strtok(NULL, ":", &tok_cntx) : NULL;
+
+            if (expires) {
+                apr_time_exp_t tms;
+                apr_time_exp_gmt(&tms, r->request_time
+                                     + apr_time_from_sec((60 * atol(expires))));
+                exp_time = apr_psprintf(r->pool, "%s, %.2d-%s-%.4d "
+                                                 "%.2d:%.2d:%.2d GMT",
+                                        apr_day_snames[tms.tm_wday],
+                                        tms.tm_mday,
+                                        apr_month_snames[tms.tm_mon],
+                                        tms.tm_year+1900,
+                                        tms.tm_hour, tms.tm_min, tms.tm_sec);
+            }
+
+            cookie = apr_pstrcat(rmain->pool,
+                                 var, "=", val,
+                                 "; path=", path ? path : "/",
+                                 "; domain=", domain,
+                                 expires ? "; expires=" : NULL,
+                                 expires ? exp_time : NULL,
+                                 NULL);
+
+            apr_table_addn(rmain->err_headers_out, "Set-Cookie", cookie);
+            apr_pool_userdata_set("set", notename, NULL, rmain->pool);
+            rewritelog((rmain, 5, NULL, "setting cookie '%s'", cookie));
+        }
+        else {
+            rewritelog((rmain, 5, NULL, "skipping already set cookie '%s'",
+                        var));
+        }
     }
 
-    if (is_redirect_limit_exceeded(r)) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
-                      "mod_rewrite: maximum number of internal redirects "
-                      "reached. Assuming configuration error. Use "
-                      "'RewriteOptions MaxRedirects' to increase the limit "
-                      "if neccessary.");
-        return HTTP_INTERNAL_SERVER_ERROR;
-    }
+    return;
+}
 
-    /* now do the internal redirect */
-    ap_internal_redirect(apr_pstrcat(r->pool, r->filename+9,
-                                     r->args ? "?" : NULL, r->args, NULL), r);
+static void do_expand_cookie(data_item *cookie, rewrite_ctx *ctx)
+{
+    while (cookie) {
+        add_cookie(ctx->r, do_expand(cookie->data, ctx));
+        cookie = cookie->next;
+    }
 
-    /* and return gracefully */
-    return OK;
+    return;
 }
 
+#if APR_HAS_USER
 /*
- * check whether redirect limit is reached
+ * Expand tilde-paths (/~user) through Unix /etc/passwd
+ * database information (or other OS-specific database)
  */
-static int is_redirect_limit_exceeded(request_rec *r)
+static char *expand_tildepaths(request_rec *r, char *uri)
 {
-    request_rec *top = r;
-    rewrite_request_conf *reqc;
-    rewrite_perdir_conf *dconf;
+    if (uri && *uri == '/' && uri[1] == '~') {
+        char *p, *user;
 
-    /* we store it in the top request */
-    while (top->main) {
-        top = top->main;
-    }
-    while (top->prev) {
-        top = top->prev;
+        p = user = uri + 2;
+        while (*p && *p != '/') {
+            ++p;
+        }
+
+        if (p > user) {
+            char *homedir;
+
+            user = apr_pstrmemdup(r->pool, user, p-user);
+            if (apr_uid_homepath_get(&homedir, user, r->pool) == APR_SUCCESS) {
+                if (*p) {
+                    /* reuse of user variable */
+                    user = homedir + strlen(homedir) - 1;
+                    if (user >= homedir && *user == '/') {
+                        *user = '\0';
+                    }
+
+                    return apr_pstrcat(r->pool, homedir, p, NULL);
+                }
+                else {
+                    return homedir;
+                }
+            }
+        }
     }
 
-    /* fetch our config */
-    reqc = (rewrite_request_conf *) ap_get_module_config(top->request_config,
-                                                         &rewrite_module);
+    return uri;
+}
+#endif  /* if APR_HAS_USER */
 
-    /* no config there? create one. */
-    if (!reqc) {
-        rewrite_server_conf *sconf;
 
-        reqc = apr_palloc(top->pool, sizeof(rewrite_request_conf));
-        sconf = ap_get_module_config(r->server->module_config, &rewrite_module);
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |              rewriting lockfile support
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
 
-        reqc->redirects = 0;
-        reqc->redirect_limit = sconf->redirect_limit
-                                 ? sconf->redirect_limit
-                                 : REWRITE_REDIRECT_LIMIT;
+static apr_status_t rewritelock_create(server_rec *s, apr_pool_t *p)
+{
+    apr_status_t rc;
 
-        /* associate it with this request */
-        ap_set_module_config(top->request_config, &rewrite_module, reqc);
+    /* only operate if a lockfile is used */
+    if (lockname == NULL || *(lockname) == '\0') {
+        return APR_SUCCESS;
     }
 
-    /* allow to change the limit during redirects. */
-    dconf = (rewrite_perdir_conf *)ap_get_module_config(r->per_dir_config,
-                                                        &rewrite_module);
+    /* create the lockfile */
+    rc = apr_global_mutex_create(&rewrite_mapr_lock_acquire, lockname,
+                                 APR_LOCK_DEFAULT, p);
+    if (rc != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rc, s,
+                     "mod_rewrite: Parent could not create RewriteLock "
+                     "file %s", lockname);
+        return rc;
+    }
 
-    /* 0 == unset; take server conf ... */
-    if (dconf->redirect_limit) {
-        reqc->redirect_limit = dconf->redirect_limit;
+#ifdef AP_NEED_SET_MUTEX_PERMS
+    rc = unixd_set_global_mutex_perms(rewrite_mapr_lock_acquire);
+    if (rc != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rc, s,
+                     "mod_rewrite: Parent could not set permissions "
+                     "on RewriteLock; check User and Group directives");
+        return rc;
     }
+#endif
+
+    return APR_SUCCESS;
+}
 
-    ap_log_rerror(APLOG_MARK, APLOG_DEBUG, 0, r,
-                  "mod_rewrite's internal redirect status: %d/%d.",
-                  reqc->redirects, reqc->redirect_limit);
+static apr_status_t rewritelock_remove(void *data)
+{
+    /* only operate if a lockfile is used */
+    if (lockname == NULL || *(lockname) == '\0') {
+        return APR_SUCCESS;
+    }
 
-    /* and now give the caller a hint */
-    return (reqc->redirects++ >= reqc->redirect_limit);
+    /* destroy the rewritelock */
+    apr_global_mutex_destroy (rewrite_mapr_lock_acquire);
+    rewrite_mapr_lock_acquire = NULL;
+    lockname = NULL;
+    return(0);
 }
 
 
 /*
-** +-------------------------------------------------------+
-** |                                                       |
-** |                  the rewriting engine
-** |                                                       |
-** +-------------------------------------------------------+
-*/
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |           configuration directive handling
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
 
 /*
- *  Apply a complete rule set,
- *  i.e. a list of rewrite rules
+ * own command line parser for RewriteRule and RewriteCond,
+ * which doesn't have the '\\' problem.
+ * (returns true on error)
+ *
+ * XXX: what an inclined parser. Seems we have to leave it so
+ *      for backwards compat. *sigh*
  */
-static int apply_rewrite_list(request_rec *r, apr_array_header_t *rewriterules,
-                              char *perdir)
+static int parseargline(char *str, char **a1, char **a2, char **a3)
 {
-    rewriterule_entry *entries;
-    rewriterule_entry *p;
-    int i;
-    int changed;
-    int rc;
-    int s;
+    char quote;
+
+    while (apr_isspace(*str)) {
+        ++str;
+    }
 
     /*
-     *  Iterate over all existing rules
+     * determine first argument
      */
-    entries = (rewriterule_entry *)rewriterules->elts;
-    changed = 0;
-    loop:
-    for (i = 0; i < rewriterules->nelts; i++) {
-        p = &entries[i];
+    quote = (*str == '"' || *str == '\'') ? *str++ : '\0';
+    *a1 = str;
 
-        /*
-         *  Ignore this rule on subrequests if we are explicitly
-         *  asked to do so or this is a proxy-throughput or a
-         *  forced redirect rule.
-         */
-        if (r->main != NULL &&
-            (p->flags & RULEFLAG_IGNOREONSUBREQ ||
-             p->flags & RULEFLAG_PROXY          ||
-             p->flags & RULEFLAG_FORCEREDIRECT    )) {
+    for (; *str; ++str) {
+        if ((apr_isspace(*str) && !quote) || (*str == quote)) {
+            break;
+        }
+        if (*str == '\\' && apr_isspace(str[1])) {
+            ++str;
             continue;
         }
+    }
 
-        /*
-         *  Apply the current rule.
-         */
-        rc = apply_rewrite_rule(r, p, perdir);
-        if (rc) {
-            /*
-             *  Indicate a change if this was not a match-only rule.
-             */
-            if (rc != 2) {
-                changed = ((p->flags & RULEFLAG_NOESCAPE)
-                           ? ACTION_NOESCAPE : ACTION_NORMAL);
-            }
+    if (!*str) {
+        return 1;
+    }
+    *str++ = '\0';
 
-            /*
-             *  Pass-Through Feature (`RewriteRule .. .. [PT]'):
-             *  Because the Apache 1.x API is very limited we
-             *  need this hack to pass the rewritten URL to other
-             *  modules like mod_alias, mod_userdir, etc.
-             */
-            if (p->flags & RULEFLAG_PASSTHROUGH) {
-                rewritelog(r, 2, "forcing '%s' to get passed through "
-                           "to next API URI-to-filename handler", r->filename);
-                r->filename = apr_pstrcat(r->pool, "passthrough:",
-                                         r->filename, NULL);
-                changed = ACTION_NORMAL;
-                break;
-            }
+    while (apr_isspace(*str)) {
+        ++str;
+    }
 
-            /*
-             *  Rule has the "forbidden" flag set which means that
-             *  we stop processing and indicate this to the caller.
-             */
-            if (p->flags & RULEFLAG_FORBIDDEN) {
-                rewritelog(r, 2, "forcing '%s' to be forbidden", r->filename);
-                r->filename = apr_pstrcat(r->pool, "forbidden:",
-                                         r->filename, NULL);
-                changed = ACTION_NORMAL;
-                break;
-            }
+    /*
+     * determine second argument
+     */
+    quote = (*str == '"' || *str == '\'') ? *str++ : '\0';
+    *a2 = str;
 
-            /*
-             *  Rule has the "gone" flag set which means that
-             *  we stop processing and indicate this to the caller.
-             */
-            if (p->flags & RULEFLAG_GONE) {
-                rewritelog(r, 2, "forcing '%s' to be gone", r->filename);
-                r->filename = apr_pstrcat(r->pool, "gone:", r->filename, NULL);
-                changed = ACTION_NORMAL;
-                break;
-            }
+    for (; *str; ++str) {
+        if ((apr_isspace(*str) && !quote) || (*str == quote)) {
+            break;
+        }
+        if (*str == '\\' && apr_isspace(str[1])) {
+            ++str;
+            continue;
+        }
+    }
 
-            /*
-             *  Stop processing also on proxy pass-through and
-             *  last-rule and new-round flags.
-             */
-            if (p->flags & RULEFLAG_PROXY) {
-                break;
-            }
-            if (p->flags & RULEFLAG_LASTRULE) {
-                break;
-            }
+    if (!*str) {
+        *a3 = NULL; /* 3rd argument is optional */
+        return 0;
+    }
+    *str++ = '\0';
 
-            /*
-             *  On "new-round" flag we just start from the top of
-             *  the rewriting ruleset again.
-             */
-            if (p->flags & RULEFLAG_NEWROUND) {
-                goto loop;
-            }
+    while (apr_isspace(*str)) {
+        ++str;
+    }
 
-            /*
-             *  If we are forced to skip N next rules, do it now.
-             */
-            if (p->skip > 0) {
-                s = p->skip;
-                while (   i < rewriterules->nelts
-                       && s > 0) {
-                    i++;
-                    p = &entries[i];
-                    s--;
-                }
-            }
+    if (!*str) {
+        *a3 = NULL; /* 3rd argument is still optional */
+        return 0;
+    }
+
+    /*
+     * determine third argument
+     */
+    quote = (*str == '"' || *str == '\'') ? *str++ : '\0';
+    *a3 = str;
+    for (; *str; ++str) {
+        if ((apr_isspace(*str) && !quote) || (*str == quote)) {
+            break;
         }
-        else {
-            /*
-             *  If current rule is chained with next rule(s),
-             *  skip all this next rule(s)
-             */
-            while (   i < rewriterules->nelts
-                   && p->flags & RULEFLAG_CHAIN) {
-                i++;
-                p = &entries[i];
-            }
+        if (*str == '\\' && apr_isspace(str[1])) {
+            ++str;
+            continue;
         }
     }
-    return changed;
+    *str = '\0';
+
+    return 0;
 }
 
-/*
- *  Apply a single(!) rewrite rule
- */
-static int apply_rewrite_rule(request_rec *r, rewriterule_entry *p,
-                              char *perdir)
+static void *config_server_create(apr_pool_t *p, server_rec *s)
 {
-    char *uri;
-    char *output;
-    const char *vary;
-    char newuri[MAX_STRING_LEN];
-    regex_t *regexp;
-    regmatch_t regmatch[AP_MAX_REG_MATCH];
-    backrefinfo *briRR = NULL;
-    backrefinfo *briRC = NULL;
-    int failed;
-    apr_array_header_t *rewriteconds;
-    rewritecond_entry *conds;
-    rewritecond_entry *c;
-    int i;
-    int rc;
-    int is_proxyreq = 0;
+    rewrite_server_conf *a;
 
-    /*
-     *  Initialisation
-     */
-    uri     = r->filename;
-    regexp  = p->regexp;
-    output  = p->output;
+    a = (rewrite_server_conf *)apr_pcalloc(p, sizeof(rewrite_server_conf));
 
-    /*
-     *  Add (perhaps splitted away) PATH_INFO postfix to URL to
-     *  make sure we really match against the complete URL.
-     */
-    if (perdir != NULL && r->path_info != NULL && r->path_info[0] != '\0') {
-        rewritelog(r, 3, "[per-dir %s] add path info postfix: %s -> %s%s",
-                   perdir, uri, uri, r->path_info);
-        uri = apr_pstrcat(r->pool, uri, r->path_info, NULL);
+    a->state           = ENGINE_DISABLED;
+    a->options         = OPTION_NONE;
+#ifndef REWRITELOG_DISABLED
+    a->rewritelogfile  = NULL;
+    a->rewritelogfp    = NULL;
+    a->rewriteloglevel = 0;
+#endif
+    a->rewritemaps     = apr_hash_make(p);
+    a->rewriteconds    = apr_array_make(p, 2, sizeof(rewritecond_entry));
+    a->rewriterules    = apr_array_make(p, 2, sizeof(rewriterule_entry));
+    a->server          = s;
+
+    return (void *)a;
+}
+
+static void *config_server_merge(apr_pool_t *p, void *basev, void *overridesv)
+{
+    rewrite_server_conf *a, *base, *overrides;
+
+    a         = (rewrite_server_conf *)apr_pcalloc(p,
+                                                   sizeof(rewrite_server_conf));
+    base      = (rewrite_server_conf *)basev;
+    overrides = (rewrite_server_conf *)overridesv;
+
+    a->state   = overrides->state;
+    a->options = overrides->options;
+    a->server  = overrides->server;
+
+    if (a->options & OPTION_INHERIT) {
+        /*
+         *  local directives override
+         *  and anything else is inherited
+         */
+#ifndef REWRITELOG_DISABLED
+        a->rewriteloglevel = overrides->rewriteloglevel != 0
+                             ? overrides->rewriteloglevel
+                             : base->rewriteloglevel;
+        a->rewritelogfile  = overrides->rewritelogfile != NULL
+                             ? overrides->rewritelogfile
+                             : base->rewritelogfile;
+        a->rewritelogfp    = overrides->rewritelogfp != NULL
+                             ? overrides->rewritelogfp
+                             : base->rewritelogfp;
+#endif
+        a->rewritemaps     = apr_hash_overlay(p, overrides->rewritemaps,
+                                              base->rewritemaps);
+        a->rewriteconds    = apr_array_append(p, overrides->rewriteconds,
+                                              base->rewriteconds);
+        a->rewriterules    = apr_array_append(p, overrides->rewriterules,
+                                              base->rewriterules);
+    }
+    else {
+        /*
+         *  local directives override
+         *  and anything else gets defaults
+         */
+#ifndef REWRITELOG_DISABLED
+        a->rewriteloglevel = overrides->rewriteloglevel;
+        a->rewritelogfile  = overrides->rewritelogfile;
+        a->rewritelogfp    = overrides->rewritelogfp;
+#endif
+        a->rewritemaps     = overrides->rewritemaps;
+        a->rewriteconds    = overrides->rewriteconds;
+        a->rewriterules    = overrides->rewriterules;
     }
 
-    /*
-     *  On per-directory context (.htaccess) strip the location
-     *  prefix from the URL to make sure patterns apply only to
-     *  the local part.  Additionally indicate this special
-     *  threatment in the logfile.
-     */
-    if (perdir) {
-        /*
-  	     * Proxy request?
-         */
-  	    is_proxyreq = (   r->proxyreq && r->filename
-  	                   && !strncmp(r->filename, "proxy:", 6));
+    return (void *)a;
+}
 
-        if (   !is_proxyreq && strlen(uri) >= strlen(perdir)
-            && strncmp(uri, perdir, strlen(perdir)) == 0) {
-            rewritelog(r, 3, "[per-dir %s] strip per-dir prefix: %s -> %s",
-                       perdir, uri, uri+strlen(perdir));
-            uri = uri+strlen(perdir);
-        }
-    }
+static void *config_perdir_create(apr_pool_t *p, char *path)
+{
+    rewrite_perdir_conf *a;
 
-    /*
-     *  Try to match the URI against the RewriteRule pattern
-     *  and exit immeddiately if it didn't apply.
-     */
-    if (perdir == NULL) {
-        rewritelog(r, 3, "applying pattern '%s' to uri '%s'",
-                   p->pattern, uri);
-    }
-    else {
-        rewritelog(r, 3, "[per-dir %s] applying pattern '%s' to uri '%s'",
-                   perdir, p->pattern, uri);
-    }
-    rc = (ap_regexec(regexp, uri, AP_MAX_REG_MATCH, regmatch, 0) == 0);
-    if (! (( rc && !(p->flags & RULEFLAG_NOTMATCH)) ||
-           (!rc &&  (p->flags & RULEFLAG_NOTMATCH))   ) ) {
-        return 0;
-    }
+    a = (rewrite_perdir_conf *)apr_pcalloc(p, sizeof(rewrite_perdir_conf));
 
-    /*
-     *  Else create the RewriteRule `regsubinfo' structure which
-     *  holds the substitution information.
-     */
-    briRR = (backrefinfo *)apr_palloc(r->pool, sizeof(backrefinfo));
-    if (!rc && (p->flags & RULEFLAG_NOTMATCH)) {
-        /*  empty info on negative patterns  */
-        briRR->source = "";
-        briRR->nsub   = 0;
+    a->state           = ENGINE_DISABLED;
+    a->options         = OPTION_NONE;
+    a->baseurl         = NULL;
+    a->rewriteconds    = apr_array_make(p, 2, sizeof(rewritecond_entry));
+    a->rewriterules    = apr_array_make(p, 2, sizeof(rewriterule_entry));
+
+    if (path == NULL) {
+        a->directory = NULL;
     }
     else {
-        briRR->source = apr_pstrdup(r->pool, uri);
-        briRR->nsub   = regexp->re_nsub;
-        memcpy((void *)(briRR->regmatch), (void *)(regmatch),
-               sizeof(regmatch));
-    }
-
-    /*
-     *  Initiallally create the RewriteCond backrefinfo with
-     *  empty backrefinfo, i.e. not subst parts
-     *  (this one is adjusted inside apply_rewrite_cond() later!!)
-     */
-    briRC = (backrefinfo *)apr_pcalloc(r->pool, sizeof(backrefinfo));
-    briRC->source = "";
-    briRC->nsub   = 0;
-
-    /*
-     *  Ok, we already know the pattern has matched, but we now
-     *  additionally have to check for all existing preconditions
-     *  (RewriteCond) which have to be also true. We do this at
-     *  this very late stage to avoid unnessesary checks which
-     *  would slow down the rewriting engine!!
-     */
-    rewriteconds = p->rewriteconds;
-    conds = (rewritecond_entry *)rewriteconds->elts;
-    failed = 0;
-    for (i = 0; i < rewriteconds->nelts; i++) {
-        c = &conds[i];
-        rc = apply_rewrite_cond(r, c, perdir, briRR, briRC);
-        if (c->flags & CONDFLAG_ORNEXT) {
-            /*
-             *  The "OR" case
-             */
-            if (rc == 0) {
-                /*  One condition is false, but another can be
-                 *  still true, so we have to continue...
-                 */
-                apr_table_unset(r->notes, VARY_KEY_THIS);
-                continue;
-            }
-            else {
-                /*  One true condition is enough in "or" case, so
-                 *  skip the other conditions which are "ornext"
-                 *  chained
-                 */
-                while (   i < rewriteconds->nelts
-                       && c->flags & CONDFLAG_ORNEXT) {
-                    i++;
-                    c = &conds[i];
-                }
-                continue;
-            }
+        /* make sure it has a trailing slash */
+        if (path[strlen(path)-1] == '/') {
+            a->directory = apr_pstrdup(p, path);
         }
         else {
-            /*
-             *  The "AND" case, i.e. no "or" flag,
-             *  so a single failure means total failure.
-             */
-            if (rc == 0) {
-                failed = 1;
-                break;
-            }
-        }
-        vary = apr_table_get(r->notes, VARY_KEY_THIS);
-        if (vary != NULL) {
-            apr_table_merge(r->notes, VARY_KEY, vary);
-            apr_table_unset(r->notes, VARY_KEY_THIS);
+            a->directory = apr_pstrcat(p, path, "/", NULL);
         }
     }
-    /*  if any condition fails the complete rule fails  */
-    if (failed) {
-        apr_table_unset(r->notes, VARY_KEY);
-        apr_table_unset(r->notes, VARY_KEY_THIS);
-        return 0;
-    }
 
-    /*
-     * Regardless of what we do next, we've found a match.  Check to see
-     * if any of the request header fields were involved, and add them
-     * to the Vary field of the response.
-     */
-    if ((vary = apr_table_get(r->notes, VARY_KEY)) != NULL) {
-        apr_table_merge(r->headers_out, "Vary", vary);
-        apr_table_unset(r->notes, VARY_KEY);
-    }
+    return (void *)a;
+}
 
-    /*
-     *  If this is a pure matching rule (`RewriteRule <pat> -')
-     *  we stop processing and return immediately. The only thing
-     *  we have not to forget are the environment variables and
-     *  cookies:
-     *  (`RewriteRule <pat> - [E=...,CO=...]')
-     */
-    if (strcmp(output, "-") == 0) {
-        do_expand_env(r, p->env, briRR, briRC);
-        do_expand_cookie(r, p->cookie, briRR, briRC);
-        if (p->forced_mimetype != NULL) {
-            if (perdir == NULL) {
-                /* In the per-server context we can force the MIME-type
-                 * the correct way by notifying our MIME-type hook handler
-                 * to do the job when the MIME-type API stage is reached.
-                 */
-                rewritelog(r, 2, "remember %s to have MIME-type '%s'",
-                           r->filename, p->forced_mimetype);
-                apr_table_setn(r->notes, REWRITE_FORCED_MIMETYPE_NOTEVAR,
-                               p->forced_mimetype);
-            }
-            else {
-                /* In per-directory context we operate in the Fixup API hook
-                 * which is after the MIME-type hook, so our MIME-type handler
-                 * has no chance to set r->content_type. And because we are
-                 * in the situation where no substitution takes place no
-                 * sub-request will happen (which could solve the
-                 * restriction). As a workaround we do it ourself now
-                 * immediately although this is not strictly API-conforming.
-                 * But it's the only chance we have...
-                 */
-                rewritelog(r, 1, "[per-dir %s] force %s to have MIME-type "
-                           "'%s'", perdir, r->filename, p->forced_mimetype);
-                ap_set_content_type(r, p->forced_mimetype);
-            }
-        }
-        return 2;
-    }
+static void *config_perdir_merge(apr_pool_t *p, void *basev, void *overridesv)
+{
+    rewrite_perdir_conf *a, *base, *overrides;
 
-    /*
-     *  Ok, now we finally know all patterns have matched and
-     *  that there is something to replace, so we create the
-     *  substitution URL string in `newuri'.
-     */
-    do_expand(r, output, newuri, sizeof(newuri), briRR, briRC);
-    if (perdir == NULL) {
-        rewritelog(r, 2, "rewrite %s -> %s", uri, newuri);
+    a         = (rewrite_perdir_conf *)apr_pcalloc(p,
+                                                  sizeof(rewrite_perdir_conf));
+    base      = (rewrite_perdir_conf *)basev;
+    overrides = (rewrite_perdir_conf *)overridesv;
+
+    a->state     = overrides->state;
+    a->options   = overrides->options;
+    a->directory = overrides->directory;
+    a->baseurl   = overrides->baseurl;
+
+    if (a->options & OPTION_INHERIT) {
+        a->rewriteconds = apr_array_append(p, overrides->rewriteconds,
+                                           base->rewriteconds);
+        a->rewriterules = apr_array_append(p, overrides->rewriterules,
+                                           base->rewriterules);
     }
     else {
-        rewritelog(r, 2, "[per-dir %s] rewrite %s -> %s", perdir, uri, newuri);
+        a->rewriteconds = overrides->rewriteconds;
+        a->rewriterules = overrides->rewriterules;
     }
 
-    /*
-     *  Additionally do expansion for the environment variable
-     *  strings (`RewriteRule .. .. [E=<string>]').
-     */
-    do_expand_env(r, p->env, briRR, briRC);
+    return (void *)a;
+}
 
-    /*
-     *  Also set cookies for any cookie strings
-     *  (`RewriteRule .. .. [CO=<string>]').
-     */
-    do_expand_cookie(r, p->cookie, briRR, briRC);
+static const char *cmd_rewriteengine(cmd_parms *cmd,
+                                     void *in_dconf, int flag)
+{
+    rewrite_perdir_conf *dconf = in_dconf;
+    rewrite_server_conf *sconf;
 
-    /*
-     *  Now replace API's knowledge of the current URI:
-     *  Replace r->filename with the new URI string and split out
-     *  an on-the-fly generated QUERY_STRING part into r->args
-     */
-    r->filename = apr_pstrdup(r->pool, newuri);
-    splitout_queryargs(r, p->flags & RULEFLAG_QSAPPEND);
+    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
 
-    /*
-     *   Add the previously stripped per-directory location
-     *   prefix if the new URI is not a new one for this
-     *   location, i.e. if it's not an absolute URL (!) path nor
-     *   a fully qualified URL scheme.
-     */
-    if (   perdir && !is_proxyreq && *r->filename != '/'
-        && !is_absolute_uri(r->filename)) {
-        rewritelog(r, 3, "[per-dir %s] add per-dir prefix: %s -> %s%s",
-                   perdir, r->filename, perdir, r->filename);
-        r->filename = apr_pstrcat(r->pool, perdir, r->filename, NULL);
+    if (cmd->path == NULL) { /* is server command */
+        sconf->state = (flag ? ENGINE_ENABLED : ENGINE_DISABLED);
+    }
+    else                   /* is per-directory command */ {
+        dconf->state = (flag ? ENGINE_ENABLED : ENGINE_DISABLED);
     }
 
-    /*
-     *  If this rule is forced for proxy throughput
-     *  (`RewriteRule ... ... [P]') then emulate mod_proxy's
-     *  URL-to-filename handler to be sure mod_proxy is triggered
-     *  for this URL later in the Apache API. But make sure it is
-     *  a fully-qualified URL. (If not it is qualified with
-     *  ourself).
-     */
-    if (p->flags & RULEFLAG_PROXY) {
-        /* For rules evaluated in server context, the mod_proxy fixup
-         * hook can be relied upon to escape the URI as and when
-         * necessary, since it occurs later.  If in directory context,
-         * the ordering of the fixup hooks is forced such that
-         * mod_proxy comes first, so the URI must be escaped here
-         * instead.  See PR 39746, 46428, and other headaches. */
-        if (perdir && (p->flags & RULEFLAG_NOESCAPE) == 0) {
-            char *old_filename = r->filename;
-
-            r->filename = ap_escape_uri(r->pool, r->filename);
-            rewritelog(r, 2, "[per-dir %s] escaped URI in per-dir context "
-                        "for proxy, %s -> %s", perdir, old_filename, r->filename);
-        }
+    return NULL;
+}
 
-        fully_qualify_uri(r);
-        if (perdir == NULL) {
-            rewritelog(r, 2, "forcing proxy-throughput with %s", r->filename);
-        }
-        else {
-            rewritelog(r, 2, "[per-dir %s] forcing proxy-throughput with %s",
-                       perdir, r->filename);
-        }
-        r->filename = apr_pstrcat(r->pool, "proxy:", r->filename, NULL);
-        return 1;
-    }
+static const char *cmd_rewriteoptions(cmd_parms *cmd,
+                                      void *in_dconf, const char *option)
+{
+    int options = 0;
+    char *w;
 
-    /*
-     *  If this rule is explicitly forced for HTTP redirection
-     *  (`RewriteRule .. .. [R]') then force an external HTTP
-     *  redirect. But make sure it is a fully-qualified URL. (If
-     *  not it is qualified with ourself).
-     */
-    if (p->flags & RULEFLAG_FORCEREDIRECT) {
-        fully_qualify_uri(r);
-        if (perdir == NULL) {
-            rewritelog(r, 2,
-                       "explicitly forcing redirect with %s", r->filename);
+    while (*option) {
+        w = ap_getword_conf(cmd->pool, &option);
+
+        if (!strcasecmp(w, "inherit")) {
+            options |= OPTION_INHERIT;
+        }
+        else if (!strncasecmp(w, "MaxRedirects=", 13)) {
+            ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
+                         "RewriteOptions: MaxRedirects option has been "
+                         "removed in favor of the global "
+                         "LimitInternalRecursion directive and will be "
+                         "ignored.");
         }
         else {
-            rewritelog(r, 2,
-                       "[per-dir %s] explicitly forcing redirect with %s",
-                       perdir, r->filename);
+            return apr_pstrcat(cmd->pool, "RewriteOptions: unknown option '",
+                               w, "'", NULL);
         }
-        r->status = p->forced_responsecode;
-        return 1;
     }
 
-    /*
-     *  Special Rewriting Feature: Self-Reduction
-     *  We reduce the URL by stripping a possible
-     *  http[s]://<ourhost>[:<port>] prefix, i.e. a prefix which
-     *  corresponds to ourself. This is to simplify rewrite maps
-     *  and to avoid recursion, etc. When this prefix is not a
-     *  coincidence then the user has to use [R] explicitly (see
-     *  above).
-     */
-    reduce_uri(r);
+    /* put it into the appropriate config */
+    if (cmd->path == NULL) { /* is server command */
+        rewrite_server_conf *conf =
+            ap_get_module_config(cmd->server->module_config,
+                                 &rewrite_module);
 
-    /*
-     *  If this rule is still implicitly forced for HTTP
-     *  redirection (`RewriteRule .. <scheme>://...') then
-     *  directly force an external HTTP redirect.
-     */
-    if (is_absolute_uri(r->filename)) {
-        if (perdir == NULL) {
-            rewritelog(r, 2,
-                       "implicitly forcing redirect (rc=%d) with %s",
-                       p->forced_responsecode, r->filename);
-        }
-        else {
-            rewritelog(r, 2, "[per-dir %s] implicitly forcing redirect "
-                       "(rc=%d) with %s", perdir, p->forced_responsecode,
-                       r->filename);
-        }
-        r->status = p->forced_responsecode;
-        return 1;
+        conf->options |= options;
     }
+    else {                  /* is per-directory command */
+        rewrite_perdir_conf *conf = in_dconf;
 
-    /*
-     *  Finally we had to remember if a MIME-type should be
-     *  forced for this URL (`RewriteRule .. .. [T=<type>]')
-     *  Later in the API processing phase this is forced by our
-     *  MIME API-hook function. This time it's no problem even for
-     *  the per-directory context (where the MIME-type hook was
-     *  already processed) because a sub-request happens ;-)
-     */
-    if (p->forced_mimetype != NULL) {
-        apr_table_setn(r->notes, REWRITE_FORCED_MIMETYPE_NOTEVAR,
-                      p->forced_mimetype);
-        if (perdir == NULL) {
-            rewritelog(r, 2, "remember %s to have MIME-type '%s'",
-                       r->filename, p->forced_mimetype);
-        }
-        else {
-            rewritelog(r, 2,
-                       "[per-dir %s] remember %s to have MIME-type '%s'",
-                       perdir, r->filename, p->forced_mimetype);
-        }
+        conf->options |= options;
     }
 
-    /*
-     *  Puuhhhhhhhh... WHAT COMPLICATED STUFF ;_)
-     *  But now we're done for this particular rule.
-     */
-    return 1;
+    return NULL;
 }
 
-static int apply_rewrite_cond(request_rec *r, rewritecond_entry *p,
-                              char *perdir, backrefinfo *briRR,
-                              backrefinfo *briRC)
+#ifndef REWRITELOG_DISABLED
+static const char *cmd_rewritelog(cmd_parms *cmd, void *dconf, const char *a1)
 {
-    char input[MAX_STRING_LEN];
-    apr_finfo_t sb;
-    request_rec *rsub;
-    regmatch_t regmatch[AP_MAX_REG_MATCH];
-    int rc;
+    rewrite_server_conf *sconf;
 
-    /*
-     *   Construct the string we match against
-     */
+    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
+    sconf->rewritelogfile = a1;
+
+    return NULL;
+}
 
-    do_expand(r, p->input, input, sizeof(input), briRR, briRC);
+static const char *cmd_rewriteloglevel(cmd_parms *cmd, void *dconf,
+                                       const char *a1)
+{
+    rewrite_server_conf *sconf;
 
-    /*
-     *   Apply the patterns
-     */
+    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
+    sconf->rewriteloglevel = atoi(a1);
 
-    rc = 0;
-    if (strcmp(p->pattern, "-f") == 0) {
-        if (apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS) {
-            if (sb.filetype == APR_REG) {
-                rc = 1;
-            }
+    return NULL;
+}
+#endif /* rewritelog */
+
+static const char *cmd_rewritemap(cmd_parms *cmd, void *dconf, const char *a1,
+                                  const char *a2)
+{
+    rewrite_server_conf *sconf;
+    rewritemap_entry *newmap;
+    apr_finfo_t st;
+    const char *fname;
+
+    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
+
+    newmap = apr_palloc(cmd->pool, sizeof(rewritemap_entry));
+    newmap->func = NULL;
+
+    if (strncasecmp(a2, "txt:", 4) == 0) {
+        if ((fname = ap_server_root_relative(cmd->pool, a2+4)) == NULL) {
+            return apr_pstrcat(cmd->pool, "RewriteMap: bad path to txt map: ",
+                               a2+4, NULL);
         }
+
+        newmap->type      = MAPTYPE_TXT;
+        newmap->datafile  = fname;
+        newmap->checkfile = fname;
+        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
+                                         (void *)cmd->server, a1);
     }
-    else if (strcmp(p->pattern, "-s") == 0) {
-        if (apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS) {
-            if ((sb.filetype == APR_REG) && sb.size > 0) {
-                rc = 1;
-            }
+    else if (strncasecmp(a2, "rnd:", 4) == 0) {
+        if ((fname = ap_server_root_relative(cmd->pool, a2+4)) == NULL) {
+            return apr_pstrcat(cmd->pool, "RewriteMap: bad path to rnd map: ",
+                               a2+4, NULL);
         }
+
+        newmap->type      = MAPTYPE_RND;
+        newmap->datafile  = fname;
+        newmap->checkfile = fname;
+        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
+                                         (void *)cmd->server, a1);
     }
-    else if (strcmp(p->pattern, "-l") == 0) {
-#if !defined(OS2)
-        if (apr_lstat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS) {
-            if (sb.filetype == APR_LNK) {
-                rc = 1;
-            }
+    else if (strncasecmp(a2, "dbm", 3) == 0) {
+        const char *ignored_fname;
+        apr_status_t rv;
+
+        newmap->type = MAPTYPE_DBM;
+        fname = NULL;
+        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
+                                         (void *)cmd->server, a1);
+
+        if (a2[3] == ':') {
+            newmap->dbmtype = "default";
+            fname = a2+4;
         }
-#endif
-    }
-    else if (strcmp(p->pattern, "-d") == 0) {
-        if (apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS) {
-            if (sb.filetype == APR_DIR) {
-                rc = 1;
+        else if (a2[3] == '=') {
+            const char *colon = ap_strchr_c(a2 + 4, ':');
+
+            if (colon) {
+                newmap->dbmtype = apr_pstrndup(cmd->pool, a2 + 4,
+                                               colon - (a2 + 3) - 1);
+                fname = colon + 1;
             }
         }
-    }
-    else if (strcmp(p->pattern, "-U") == 0) {
-        /* avoid infinite subrequest recursion */
-        if (strlen(input) > 0 && subreq_ok(r)) {
-
-            /* run a URI-based subrequest */
-            rsub = ap_sub_req_lookup_uri(input, r, NULL);
 
-            /* URI exists for any result up to 3xx, redirects allowed */
-            if (rsub->status < 400)
-                rc = 1;
+        if (!fname) {
+            return apr_pstrcat(cmd->pool, "RewriteMap: bad map:",
+                               a2, NULL);
+        }
 
-            /* log it */
-            rewritelog(r, 5, "RewriteCond URI (-U) check: "
-                       "path=%s -> status=%d", input, rsub->status);
+        if ((newmap->datafile = ap_server_root_relative(cmd->pool,
+                                                        fname)) == NULL) {
+            return apr_pstrcat(cmd->pool, "RewriteMap: bad path to dbm map: ",
+                               fname, NULL);
+        }
 
-            /* cleanup by destroying the subrequest */
-            ap_destroy_sub_req(rsub);
+        rv = apr_dbm_get_usednames_ex(cmd->pool, newmap->dbmtype,
+                                      newmap->datafile, &newmap->checkfile,
+                                      &ignored_fname);
+        if (rv != APR_SUCCESS) {
+            return apr_pstrcat(cmd->pool, "RewriteMap: dbm type ",
+                               newmap->dbmtype, " is invalid", NULL);
         }
     }
-    else if (strcmp(p->pattern, "-F") == 0) {
-        /* avoid infinite subrequest recursion */
-        if (strlen(input) > 0 && subreq_ok(r)) {
-
-            /* process a file-based subrequest:
-             * this differs from -U in that no path translation is done.
-             */
-            rsub = ap_sub_req_lookup_file(input, r, NULL);
-
-            /* file exists for any result up to 2xx, no redirects */
-            if (rsub->status < 300 &&
-                /* double-check that file exists since default result is 200 */
-                apr_stat(&sb, rsub->filename, APR_FINFO_MIN,
-                         r->pool) == APR_SUCCESS) {
-                rc = 1;
-            }
-
-            /* log it */
-            rewritelog(r, 5, "RewriteCond file (-F) check: path=%s "
-                       "-> file=%s status=%d", input, rsub->filename,
-                       rsub->status);
+    else if (strncasecmp(a2, "prg:", 4) == 0) {
+        apr_tokenize_to_argv(a2 + 4, &newmap->argv, cmd->pool);
 
-            /* cleanup by destroying the subrequest */
-            ap_destroy_sub_req(rsub);
+        fname = newmap->argv[0];
+        if ((newmap->argv[0] = ap_server_root_relative(cmd->pool,
+                                                       fname)) == NULL) {
+            return apr_pstrcat(cmd->pool, "RewriteMap: bad path to prg map: ",
+                               fname, NULL);
         }
+
+        newmap->type      = MAPTYPE_PRG;
+        newmap->datafile  = NULL;
+        newmap->checkfile = newmap->argv[0];
+        newmap->cachename = NULL;
     }
-    else if (strlen(p->pattern) > 1 && *(p->pattern) == '>') {
-        rc = (compare_lexicography(input, p->pattern+1) == 1 ? 1 : 0);
-    }
-    else if (strlen(p->pattern) > 1 && *(p->pattern) == '<') {
-        rc = (compare_lexicography(input, p->pattern+1) == -1 ? 1 : 0);
-    }
-    else if (strlen(p->pattern) > 1 && *(p->pattern) == '=') {
-        if (strcmp(p->pattern+1, "\"\"") == 0) {
-            rc = (*input == '\0');
-        }
-        else {
-            rc = (strcmp(input, p->pattern+1) == 0 ? 1 : 0);
+    else if (strncasecmp(a2, "int:", 4) == 0) {
+        newmap->type      = MAPTYPE_INT;
+        newmap->datafile  = NULL;
+        newmap->checkfile = NULL;
+        newmap->cachename = NULL;
+        newmap->func      = (char *(*)(request_rec *,char *))
+                            apr_hash_get(mapfunc_hash, a2+4, strlen(a2+4));
+        if ((sconf->state == ENGINE_ENABLED) && (newmap->func == NULL)) {
+            return apr_pstrcat(cmd->pool, "RewriteMap: internal map not found:",
+                               a2+4, NULL);
         }
     }
     else {
-        /* it is really a regexp pattern, so apply it */
-        rc = (ap_regexec(p->regexp, input, AP_MAX_REG_MATCH, regmatch,0) == 0);
-
-        /* if it isn't a negated pattern and really matched
-           we update the passed-through regex subst info structure */
-        if (rc && !(p->flags & CONDFLAG_NOTMATCH)) {
-            briRC->source = apr_pstrdup(r->pool, input);
-            briRC->nsub   = p->regexp->re_nsub;
-            memcpy((void *)(briRC->regmatch), (void *)(regmatch),
-                   sizeof(regmatch));
+        if ((fname = ap_server_root_relative(cmd->pool, a2)) == NULL) {
+            return apr_pstrcat(cmd->pool, "RewriteMap: bad path to txt map: ",
+                               a2, NULL);
         }
+
+        newmap->type      = MAPTYPE_TXT;
+        newmap->datafile  = fname;
+        newmap->checkfile = fname;
+        newmap->cachename = apr_psprintf(cmd->pool, "%pp:%s",
+                                         (void *)cmd->server, a1);
     }
+    newmap->fpin  = NULL;
+    newmap->fpout = NULL;
 
-    /* if this is a non-matching regexp, just negate the result */
-    if (p->flags & CONDFLAG_NOTMATCH) {
-        rc = !rc;
+    if (newmap->checkfile && (sconf->state == ENGINE_ENABLED)
+        && (apr_stat(&st, newmap->checkfile, APR_FINFO_MIN,
+                     cmd->pool) != APR_SUCCESS)) {
+        return apr_pstrcat(cmd->pool,
+                           "RewriteMap: file for map ", a1,
+                           " not found:", newmap->checkfile, NULL);
     }
 
-    rewritelog(r, 4, "RewriteCond: input='%s' pattern='%s%s' => %s",
-               input, (p->flags & CONDFLAG_NOTMATCH ? "!" : ""),
-               p->pattern, rc ? "matched" : "not-matched");
+    apr_hash_set(sconf->rewritemaps, a1, APR_HASH_KEY_STRING, newmap);
 
-    /* end just return the result */
-    return rc;
+    return NULL;
 }
 
-
-/*
-** +-------------------------------------------------------+
-** |                                                       |
-** |              URL transformation functions
-** |                                                       |
-** +-------------------------------------------------------+
-*/
-
-
-/*
-**
-**  perform all the expansions on the input string
-**  leaving the result in the supplied buffer
-**
-*/
-
-static void do_expand(request_rec *r, char *input, char *buffer, int nbuf,
-                      backrefinfo *briRR, backrefinfo *briRC)
+static const char *cmd_rewritelock(cmd_parms *cmd, void *dconf, const char *a1)
 {
-    char *inp, *outp;
-    apr_size_t span, space;
+    const char *error;
 
-    /*
-     * for security reasons this expansion must be performed in a
-     * single pass, otherwise an attacker can arrange for the result
-     * of an earlier expansion to include expansion specifiers that
-     * are interpreted by a later expansion, producing results that
-     * were not intended by the administrator.
-     */
+    if ((error = ap_check_cmd_context(cmd, GLOBAL_ONLY)) != NULL)
+        return error;
 
-    inp = input;
-    outp = buffer;
-    space = nbuf - 1; /* room for '\0' */
-
-    for (;;) {
-        span = strcspn(inp, "\\$%");
-        if (span > space) {
-            span = space;
-        }
-        memcpy(outp, inp, span);
-        inp += span;
-        outp += span;
-        space -= span;
-        if (space == 0 || *inp == '\0') {
-            break;
-        }
-        /* now we have a '\', '$', or '%' */
-        if (inp[0] == '\\') {
-            if (inp[1] != '\0') {
-                inp++;
-                goto skip;
-            }
-        }
-        else if (inp[1] == '{') {
-            char *endp;
-            endp = find_closing_bracket(inp+2, '{', '}');
-            if (endp == NULL) {
-                goto skip;
-            }
-            /*
-            * These lookups may be recursive in a very convoluted
-            * fashion -- see the LA-U and LA-F variable expansion
-            * prefixes -- so we copy lookup keys to a separate buffer
-            * rather than adding zero bytes in order to use them in
-            * place.
-            */
-            if (inp[0] == '$') {
-                /* ${...} map lookup expansion */
-                /*
-                * To make rewrite maps useful the lookup key and
-                * default values must be expanded, so we make
-                * recursive calls to do the work. For security
-                * reasons we must never expand a string that includes
-                * verbatim data from the network. The recursion here
-                * isn't a problem because the result of expansion is
-                * only passed to lookup_map() so it cannot be
-                * re-expanded, only re-looked-up. Another way of
-                * looking at it is that the recursion is entirely
-                * driven by the syntax of the nested curly brackets.
-                */
-                char *map, *key, *dflt, *result;
-                char xkey[MAX_STRING_LEN];
-                char xdflt[MAX_STRING_LEN];
-                key = find_char_in_brackets(inp+2, ':', '{', '}');
-                if (key == NULL) {
-                    goto skip;
-                }
-                map  = apr_pstrndup(r->pool, inp+2, key-inp-2);
-                dflt = find_char_in_brackets(key+1, '|', '{', '}');
-                if (dflt == NULL) {
-                    key  = apr_pstrndup(r->pool, key+1, endp-key-1);
-                    dflt = "";
-                }
-                else {
-                    key  = apr_pstrndup(r->pool, key+1, dflt-key-1);
-                    dflt = apr_pstrndup(r->pool, dflt+1, endp-dflt-1);
-                }
-                do_expand(r, key,  xkey,  sizeof(xkey),  briRR, briRC);
-                result = lookup_map(r, map, xkey);
-                if (result) {
-                    span = apr_cpystrn(outp, result, space) - outp;
-                }
-                else {
-                    do_expand(r, dflt, xdflt, sizeof(xdflt), briRR, briRC);
-                    span = apr_cpystrn(outp, xdflt, space) - outp;
-                }
-            }
-            else if (inp[0] == '%') {
-                /* %{...} variable lookup expansion */
-                char *var;
-                var  = apr_pstrndup(r->pool, inp+2, endp-inp-2);
-                span = apr_cpystrn(outp, lookup_variable(r, var), space) - outp;
-            }
-            else {
-                span = 0;
-            }
-            inp = endp+1;
-            outp += span;
-            space -= span;
-            continue;
-        }
-        else if (apr_isdigit(inp[1])) {
-            int n = inp[1] - '0';
-            backrefinfo *bri = NULL;
-            if (inp[0] == '$') {
-                /* $N RewriteRule regexp backref expansion */
-                bri = briRR;
-            }
-            else if (inp[0] == '%') {
-                /* %N RewriteCond regexp backref expansion */
-                bri = briRC;
-            }
-            /* see ap_pregsub() in src/main/util.c */
-            if (bri && n < AP_MAX_REG_MATCH
-                && bri->regmatch[n].rm_eo > bri->regmatch[n].rm_so) {
-                span = bri->regmatch[n].rm_eo - bri->regmatch[n].rm_so;
-                if (span > space) {
-                    span = space;
-                }
-                memcpy(outp, bri->source + bri->regmatch[n].rm_so, span);
-                outp += span;
-                space -= span;
-            }
-            inp += 2;
-            continue;
-        }
-        skip:
-        *outp++ = *inp++;
-        space--;
-    }
-    *outp++ = '\0';
-}
+    /* fixup the path, especially for rewritelock_remove() */
+    lockname = ap_server_root_relative(cmd->pool, a1);
 
+    if (!lockname) {
+        return apr_pstrcat(cmd->pool, "Invalid RewriteLock path ", a1);
+    }
 
-/*
-**
-**  perform all the expansions on the environment variables
-**
-*/
+    return NULL;
+}
 
-static void do_expand_env(request_rec *r, char *env[],
-                          backrefinfo *briRR, backrefinfo *briRC)
+static const char *cmd_rewritebase(cmd_parms *cmd, void *in_dconf,
+                                   const char *a1)
 {
-    int i;
-    char buf[MAX_STRING_LEN];
+    rewrite_perdir_conf *dconf = in_dconf;
 
-    for (i = 0; env[i] != NULL; i++) {
-        do_expand(r, env[i], buf, sizeof(buf), briRR, briRC);
-        add_env_variable(r, buf);
+    if (cmd->path == NULL || dconf == NULL) {
+        return "RewriteBase: only valid in per-directory config files";
+    }
+    if (a1[0] == '\0') {
+        return "RewriteBase: empty URL not allowed";
+    }
+    if (a1[0] != '/') {
+        return "RewriteBase: argument is not a valid URL";
     }
-}
 
-static void do_expand_cookie( request_rec *r, char *cookie[],
-                              backrefinfo *briRR, backrefinfo *briRC)
-{
-    int i;
-    char buf[MAX_STRING_LEN];
+    dconf->baseurl = a1;
 
-    for (i = 0; cookie[i] != NULL; i++) {
-        do_expand(r, cookie[i], buf, sizeof(buf), briRR, briRC);
-        add_cookie(r, buf);
-    }
+    return NULL;
 }
 
-
 /*
-**
-**  split out a QUERY_STRING part from
-**  the current URI string
-**
-*/
-
-static void splitout_queryargs(request_rec *r, int qsappend)
+ * generic lexer for RewriteRule and RewriteCond flags.
+ * The parser will be passed in as a function pointer
+ * and called if a flag was found
+ */
+static const char *cmd_parseflagfield(apr_pool_t *p, void *cfg, char *key,
+                                      const char *(*parse)(apr_pool_t *,
+                                                           void *,
+                                                           char *, char *))
 {
-    char *q;
-    char *olduri;
+    char *val, *nextp, *endp;
+    const char *err;
 
-    /* don't touch, unless it's an http or mailto URL.
-     * See RFC 1738 and RFC 2368.
-     */
-    if (   is_absolute_uri(r->filename)
-        && strncasecmp(r->filename, "http", 4)
-        && strncasecmp(r->filename, "mailto", 6)) {
-        r->args = NULL; /* forget the query that's still flying around */
-        return;
+    endp = key + strlen(key) - 1;
+    if (*key != '[' || *endp != ']') {
+        return "RewriteCond: bad flag delimiters";
     }
 
-    q = strchr(r->filename, '?');
-    if (q != NULL) {
-        olduri = apr_pstrdup(r->pool, r->filename);
-        *q++ = '\0';
-        if (qsappend) {
-            r->args = apr_pstrcat(r->pool, q, "&", r->args, NULL);
+    *endp = ','; /* for simpler parsing */
+    ++key;
+
+    while (*key) {
+        /* skip leading spaces */
+        while (apr_isspace(*key)) {
+            ++key;
         }
-        else {
-            r->args = apr_pstrdup(r->pool, q);
+
+        if (!*key || (nextp = ap_strchr(key, ',')) == NULL) { /* NULL should not
+                                                               * happen, but ...
+                                                               */
+            break;
         }
-        if (strlen(r->args) == 0) {
-            r->args = NULL;
-            rewritelog(r, 3, "split uri=%s -> uri=%s, args=<none>", olduri,
-                       r->filename);
+
+        /* strip trailing spaces */
+        endp = nextp - 1;
+        while (apr_isspace(*endp)) {
+            --endp;
+        }
+        *++endp = '\0';
+
+        /* split key and val */
+        val = ap_strchr(key, '=');
+        if (val) {
+            *val++ = '\0';
         }
         else {
-            if (r->args[strlen(r->args)-1] == '&') {
-                r->args[strlen(r->args)-1] = '\0';
-            }
-            rewritelog(r, 3, "split uri=%s -> uri=%s, args=%s", olduri,
-                       r->filename, r->args);
+            val = endp;
+        }
+
+        err = parse(p, cfg, key, val);
+        if (err) {
+            return err;
         }
+
+        key = nextp + 1;
     }
 
-    return;
+    return NULL;
 }
 
+static const char *cmd_rewritecond_setflag(apr_pool_t *p, void *_cfg,
+                                           char *key, char *val)
+{
+    rewritecond_entry *cfg = _cfg;
 
-/*
-**
-**  strip 'http[s]://ourhost/' from URI
-**
-*/
+    if (   strcasecmp(key, "nocase") == 0
+        || strcasecmp(key, "NC") == 0    ) {
+        cfg->flags |= CONDFLAG_NOCASE;
+    }
+    else if (   strcasecmp(key, "ornext") == 0
+             || strcasecmp(key, "OR") == 0    ) {
+        cfg->flags |= CONDFLAG_ORNEXT;
+    }
+    else {
+        return apr_pstrcat(p, "RewriteCond: unknown flag '", key, "'", NULL);
+    }
+    return NULL;
+}
 
-static void reduce_uri(request_rec *r)
+static const char *cmd_rewritecond(cmd_parms *cmd, void *in_dconf,
+                                   const char *in_str)
 {
-    char *cp;
-    unsigned short port;
-    char *portp;
-    char *hostp;
-    char *url;
-    char c;
-    char host[LONG_STRING_LEN];
-    char buf[MAX_STRING_LEN];
-    char *olduri;
-    apr_size_t l;
+    rewrite_perdir_conf *dconf = in_dconf;
+    char *str = apr_pstrdup(cmd->pool, in_str);
+    rewrite_server_conf *sconf;
+    rewritecond_entry *newcond;
+    ap_regex_t *regexp;
+    char *a1;
+    char *a2;
+    char *a3;
+    const char *err;
 
-    cp = (char *)ap_http_method(r);
-    l  = strlen(cp);
-    if (   strlen(r->filename) > l+3
-        && strncasecmp(r->filename, cp, l) == 0
-        && r->filename[l]   == ':'
-        && r->filename[l+1] == '/'
-        && r->filename[l+2] == '/'             ) {
-        /* there was really a rewrite to a remote path */
+    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
 
-        olduri = apr_pstrdup(r->pool, r->filename); /* save for logging */
+    /*  make a new entry in the internal temporary rewrite rule list */
+    if (cmd->path == NULL) {   /* is server command */
+        newcond = apr_array_push(sconf->rewriteconds);
+    }
+    else {                     /* is per-directory command */
+        newcond = apr_array_push(dconf->rewriteconds);
+    }
 
-        /* cut the hostname and port out of the URI */
-        apr_cpystrn(buf, r->filename+(l+3), sizeof(buf));
-        hostp = buf;
-        for (cp = hostp; *cp != '\0' && *cp != '/' && *cp != ':'; cp++)
-            ;
-        if (*cp == ':') {
-            /* set host */
-            *cp++ = '\0';
-            apr_cpystrn(host, hostp, sizeof(host));
-            /* set port */
-            portp = cp;
-            for (; *cp != '\0' && *cp != '/'; cp++)
-                ;
-            c = *cp;
-            *cp = '\0';
-            port = atoi(portp);
-            *cp = c;
-            /* set remaining url */
-            url = cp;
+    /* parse the argument line ourself
+     * a1 .. a3 are substrings of str, which is a fresh copy
+     * of the argument line. So we can use a1 .. a3 without
+     * copying them again.
+     */
+    if (parseargline(str, &a1, &a2, &a3)) {
+        return apr_pstrcat(cmd->pool, "RewriteCond: bad argument line '", str,
+                           "'", NULL);
+    }
+
+    /* arg1: the input string */
+    newcond->input = a1;
+
+    /* arg3: optional flags field
+     * (this has to be parsed first, because we need to
+     *  know if the regex should be compiled with ICASE!)
+     */
+    newcond->flags = CONDFLAG_NONE;
+    if (a3 != NULL) {
+        if ((err = cmd_parseflagfield(cmd->pool, newcond, a3,
+                                      cmd_rewritecond_setflag)) != NULL) {
+            return err;
         }
-        else if (*cp == '/') {
-            /* set host */
-            *cp = '\0';
-            apr_cpystrn(host, hostp, sizeof(host));
-            *cp = '/';
-            /* set port */
-            port = ap_default_port(r);
-            /* set remaining url */
-            url = cp;
+    }
+
+    /* arg2: the pattern */
+    if (*a2 == '!') {
+        newcond->flags |= CONDFLAG_NOTMATCH;
+        ++a2;
+    }
+
+    /* determine the pattern type */
+    newcond->ptype = 0;
+    if (*a2 && a2[1]) {
+        if (!a2[2] && *a2 == '-') {
+            switch (a2[1]) {
+            case 'f': newcond->ptype = CONDPAT_FILE_EXISTS; break;
+            case 's': newcond->ptype = CONDPAT_FILE_SIZE;   break;
+            case 'l': newcond->ptype = CONDPAT_FILE_LINK;   break;
+            case 'd': newcond->ptype = CONDPAT_FILE_DIR;    break;
+            case 'x': newcond->ptype = CONDPAT_FILE_XBIT;   break;
+            case 'U': newcond->ptype = CONDPAT_LU_URL;      break;
+            case 'F': newcond->ptype = CONDPAT_LU_FILE;     break;
+            }
         }
         else {
-            /* set host */
-            apr_cpystrn(host, hostp, sizeof(host));
-            /* set port */
-            port = ap_default_port(r);
-            /* set remaining url */
-            url = "/";
+            switch (*a2) {
+            case '>': newcond->ptype = CONDPAT_STR_GT; break;
+            case '<': newcond->ptype = CONDPAT_STR_LT; break;
+            case '=': newcond->ptype = CONDPAT_STR_EQ;
+                /* "" represents an empty string */
+                if (*++a2 == '"' && a2[1] == '"' && !a2[2]) {
+                    a2 += 2;
+                }
+                break;
+            }
         }
+    }
 
-        /* now check whether we could reduce it to a local path... */
-        if (ap_matches_request_vhost(r, host, port)) {
-            /* this is our host, so only the URL remains */
-            r->filename = apr_pstrdup(r->pool, url);
-            rewritelog(r, 3, "reduce %s -> %s", olduri, r->filename);
+    if (newcond->ptype && newcond->ptype != CONDPAT_STR_EQ &&
+        (newcond->flags & CONDFLAG_NOCASE)) {
+        ap_log_error(APLOG_MARK, APLOG_WARNING, 0, cmd->server,
+                     "RewriteCond: NoCase option for non-regex pattern '%s' "
+                     "is not supported and will be ignored.", a2);
+        newcond->flags &= ~CONDFLAG_NOCASE;
+    }
+
+    newcond->pattern = a2;
+
+    if (!newcond->ptype) {
+        regexp = ap_pregcomp(cmd->pool, a2,
+                             AP_REG_EXTENDED | ((newcond->flags & CONDFLAG_NOCASE)
+                                             ? AP_REG_ICASE : 0));
+        if (!regexp) {
+            return apr_pstrcat(cmd->pool, "RewriteCond: cannot compile regular "
+                               "expression '", a2, "'", NULL);
         }
-    }
-    return;
-}
 
+        newcond->regexp  = regexp;
+    }
 
-/*
-**
-**  add 'http[s]://ourhost[:ourport]/' to URI
-**  if URI is still not fully qualified
-**
-*/
+    return NULL;
+}
 
-static void fully_qualify_uri(request_rec *r)
+static const char *cmd_rewriterule_setflag(apr_pool_t *p, void *_cfg,
+                                           char *key, char *val)
 {
-    char buf[32];
-    const char *thisserver;
-    char *thisport;
-    int port;
+    rewriterule_entry *cfg = _cfg;
+    int error = 0;
 
-    if (!is_absolute_uri(r->filename)) {
+    switch (*key++) {
+    case 'c':
+    case 'C':
+        if (!*key || !strcasecmp(key, "hain")) {           /* chain */
+            cfg->flags |= RULEFLAG_CHAIN;
+        }
+        else if (((*key == 'O' || *key == 'o') && !key[1])
+                 || !strcasecmp(key, "ookie")) {           /* cookie */
+            data_item *cp = cfg->cookie;
 
-        thisserver = ap_get_server_name(r);
-        port = ap_get_server_port(r);
-        if (ap_is_default_port(port,r)) {
-            thisport = "";
+            if (!cp) {
+                cp = cfg->cookie = apr_palloc(p, sizeof(*cp));
+            }
+            else {
+                while (cp->next) {
+                    cp = cp->next;
+                }
+                cp->next = apr_palloc(p, sizeof(*cp));
+                cp = cp->next;
+            }
+
+            cp->next = NULL;
+            cp->data = val;
         }
         else {
-            apr_snprintf(buf, sizeof(buf), ":%u", port);
-            thisport = buf;
+            ++error;
         }
+        break;
+
+    case 'e':
+    case 'E':
+        if (!*key || !strcasecmp(key, "nv")) {             /* env */
+            data_item *cp = cfg->env;
+
+            if (!cp) {
+                cp = cfg->env = apr_palloc(p, sizeof(*cp));
+            }
+            else {
+                while (cp->next) {
+                    cp = cp->next;
+                }
+                cp->next = apr_palloc(p, sizeof(*cp));
+                cp = cp->next;
+            }
 
-        if (r->filename[0] == '/') {
-            r->filename = apr_psprintf(r->pool, "%s://%s%s%s",
-                                       ap_http_method(r), thisserver,
-                                       thisport, r->filename);
+            cp->next = NULL;
+            cp->data = val;
         }
         else {
-            r->filename = apr_psprintf(r->pool, "%s://%s%s/%s",
-                                       ap_http_method(r), thisserver,
-                                       thisport, r->filename);
+            ++error;
         }
-    }
-    return;
-}
-
-
-/* return number of chars of the scheme (incl. '://')
- * if the URI is absolute (includes a scheme etc.)
- * otherwise 0.
- *
- * NOTE: If you add new schemes here, please have a
- *       look at escape_absolute_uri and splitout_queryargs.
- *       Not every scheme takes query strings and some schemes
- *       may be handled in a special way.
- *
- * XXX: we should consider a scheme registry, perhaps with
- *      appropriate escape callbacks to allow other modules
- *      to extend mod_rewrite at runtime.
- */
-static unsigned is_absolute_uri(char *uri)
-{
-    /* fast exit */
-    if (*uri == '/' || strlen(uri) <= 5) {
-        return 0;
-    }
+        break;
 
-    switch (*uri++) {
     case 'f':
     case 'F':
-        if (!strncasecmp(uri, "tp://", 5)) {        /* ftp://    */
-            return 6;
+        if (!*key || !strcasecmp(key, "orbidden")) {       /* forbidden */
+            cfg->flags |= (RULEFLAG_STATUS | RULEFLAG_NOSUB);
+            cfg->forced_responsecode = HTTP_FORBIDDEN;
+        }
+        else {
+            ++error;
         }
         break;
 
     case 'g':
     case 'G':
-        if (!strncasecmp(uri, "opher://", 8)) {     /* gopher:// */
-            return 9;
+        if (!*key || !strcasecmp(key, "one")) {            /* gone */
+            cfg->flags |= (RULEFLAG_STATUS | RULEFLAG_NOSUB);
+            cfg->forced_responsecode = HTTP_GONE;
+        }
+        else {
+            ++error;
         }
         break;
 
     case 'h':
     case 'H':
-        if (!strncasecmp(uri, "ttp://", 6)) {       /* http://   */
-            return 7;
+        if (!*key || !strcasecmp(key, "andler")) {         /* handler */
+            cfg->forced_handler = val;
         }
-        else if (!strncasecmp(uri, "ttps://", 7)) { /* https://  */
-            return 8;
+        else {
+            ++error;
         }
         break;
 
     case 'l':
     case 'L':
-        if (!strncasecmp(uri, "dap://", 6)) {       /* ldap://   */
-            return 7;
+        if (!*key || !strcasecmp(key, "ast")) {            /* last */
+            cfg->flags |= RULEFLAG_LASTRULE;
         }
-        break;
-
-    case 'm':
-    case 'M':
-        if (!strncasecmp(uri, "ailto:", 6)) {       /* mailto:   */
-            return 7;
+        else {
+            ++error;
         }
         break;
 
     case 'n':
     case 'N':
-        if (!strncasecmp(uri, "ews:", 4)) {         /* news:     */
-            return 5;
+        if (((*key == 'E' || *key == 'e') && !key[1])
+            || !strcasecmp(key, "oescape")) {              /* noescape */
+            cfg->flags |= RULEFLAG_NOESCAPE;
+        }
+        else if (!*key || !strcasecmp(key, "ext")) {       /* next */
+            cfg->flags |= RULEFLAG_NEWROUND;
+        }
+        else if (((*key == 'S' || *key == 's') && !key[1])
+            || !strcasecmp(key, "osubreq")) {              /* nosubreq */
+            cfg->flags |= RULEFLAG_IGNOREONSUBREQ;
+        }
+        else if (((*key == 'C' || *key == 'c') && !key[1])
+            || !strcasecmp(key, "ocase")) {                /* nocase */
+            cfg->flags |= RULEFLAG_NOCASE;
         }
-        else if (!strncasecmp(uri, "ntp://", 6)) {  /* nntp://   */
-            return 7;
+        else {
+            ++error;
         }
         break;
-    }
-
-    return 0;
-}
-
 
-/* escape absolute uri, which may or may not be path oriented.
- * So let's handle them differently.
- */
-static char *escape_absolute_uri(apr_pool_t *p, char *uri, unsigned scheme)
-{
-    char *cp;
-
-    /* be safe.
-     * NULL should indicate elsewhere, that something's wrong
-     */
-    if (!scheme || strlen(uri) < scheme) {
-        return NULL;
-    }
-
-    cp = uri + scheme;
-
-    /* scheme with authority part? */
-    if (cp[-1] == '/') {
-        /* skip host part */
-        while (*cp && *cp != '/') {
-            ++cp;
+    case 'p':
+    case 'P':
+        if (!*key || !strcasecmp(key, "roxy")) {           /* proxy */
+            cfg->flags |= RULEFLAG_PROXY;
+        }
+        else if (((*key == 'T' || *key == 't') && !key[1])
+            || !strcasecmp(key, "assthrough")) {           /* passthrough */
+            cfg->flags |= RULEFLAG_PASSTHROUGH;
         }
-
-        /* nothing after the hostpart. ready! */
-        if (!*cp || !*++cp) {
-            return apr_pstrdup(p, uri);
+        else {
+            ++error;
         }
+        break;
 
-        /* remember the hostname stuff */
-        scheme = cp - uri;
-
-        /* special thing for ldap.
-         * The parts are separated by question marks. From RFC 2255:
-         *     ldapurl = scheme "://" [hostport] ["/"
-         *               [dn ["?" [attributes] ["?" [scope]
-         *               ["?" [filter] ["?" extensions]]]]]]
-         */
-        if (!strncasecmp(uri, "ldap", 4)) {
-            char *token[5];
-            int c = 0;
-
-            token[0] = cp = apr_pstrdup(p, cp);
-            while (*cp && c < 4) {
-                if (*cp == '?') {
-                    token[++c] = cp + 1;
-                    *cp = '\0';
-                }
-                ++cp;
-            }
-
-            return apr_pstrcat(p, apr_pstrndup(p, uri, scheme),
-                                          ap_escape_uri(p, token[0]),
-                               (c >= 1) ? "?" : NULL,
-                               (c >= 1) ? ap_escape_uri(p, token[1]) : NULL,
-                               (c >= 2) ? "?" : NULL,
-                               (c >= 2) ? ap_escape_uri(p, token[2]) : NULL,
-                               (c >= 3) ? "?" : NULL,
-                               (c >= 3) ? ap_escape_uri(p, token[3]) : NULL,
-                               (c >= 4) ? "?" : NULL,
-                               (c >= 4) ? ap_escape_uri(p, token[4]) : NULL,
-                               NULL);
+    case 'q':
+    case 'Q':
+        if (   !strcasecmp(key, "SA")
+            || !strcasecmp(key, "sappend")) {              /* qsappend */
+            cfg->flags |= RULEFLAG_QSAPPEND;
         }
-    }
-
-    /* Nothing special here. Apply normal escaping. */
-    return apr_pstrcat(p, apr_pstrndup(p, uri, scheme),
-                       ap_escape_uri(p, cp), NULL);
-}
-
-
-/*
-**
-**  Expand tilde-paths (/~user) through Unix /etc/passwd
-**  database information (or other OS-specific database)
-**
-*/
-#if APR_HAS_USER
-static char *expand_tildepaths(request_rec *r, char *uri)
-{
-    char user[LONG_STRING_LEN];
-    char *newuri;
-    int i, j;
-    char *homedir;
-
-    newuri = uri;
-    if (uri != NULL && strlen(uri) > 2 && uri[0] == '/' && uri[1] == '~') {
-        /* cut out the username */
-        for (j = 0, i = 2; j < sizeof(user)-1
-               && uri[i] != '\0'
-               && uri[i] != '/'  ; ) {
-            user[j++] = uri[i++];
-        }
-        user[j] = '\0';
-
-        /* lookup username in systems passwd file */
-        if (apr_get_home_directory(&homedir, user, r->pool) == APR_SUCCESS) {
-            /* ok, user was found, so expand the ~user string */
-            if (uri[i] != '\0') {
-                /* ~user/anything...  has to be expanded */
-                if (homedir[strlen(homedir)-1] == '/') {
-                    homedir[strlen(homedir)-1] = '\0';
-                }
-                newuri = apr_pstrcat(r->pool, homedir, uri+i, NULL);
-            }
-            else {
-                /* only ~user has to be expanded */
-                newuri = homedir;
-            }
+        else {
+            ++error;
         }
-    }
-    return newuri;
-}
-#endif  /* if APR_HAS_USER */
-
-
-
-/*
-** +-------------------------------------------------------+
-** |                                                       |
-** |              DBM hashfile support
-** |                                                       |
-** +-------------------------------------------------------+
-*/
-
-
-static char *lookup_map(request_rec *r, char *name, char *key)
-{
-    rewrite_server_conf *conf;
-    apr_array_header_t *rewritemaps;
-    rewritemap_entry *entries;
-    rewritemap_entry *s;
-    char *value;
-    apr_finfo_t st;
-    apr_status_t rv;
-    int i;
-
-    /* get map configuration */
-    conf = ap_get_module_config(r->server->module_config, &rewrite_module);
-    rewritemaps = conf->rewritemaps;
+        break;
 
-    entries = (rewritemap_entry *)rewritemaps->elts;
-    for (i = 0; i < rewritemaps->nelts; i++) {
-        s = &entries[i];
-        if (strcmp(s->name, name) == 0) {
-            if (s->type == MAPTYPE_TXT) {
-                if ((rv = apr_stat(&st, s->checkfile,
-                                   APR_FINFO_MIN, r->pool)) != APR_SUCCESS) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                                  "mod_rewrite: can't access text RewriteMap "
-                                  "file %s", s->checkfile);
-                    rewritelog(r, 1, "can't open RewriteMap file, "
-                               "see error log");
-                    return NULL;
-                }
-                value = get_cache_string(cachep, s->cachename, CACHEMODE_TS,
-                                         st.mtime, key);
-                if (value == NULL) {
-                    rewritelog(r, 6, "cache lookup FAILED, forcing new "
-                               "map lookup");
-                    if ((value =
-                         lookup_map_txtfile(r, s->datafile, key)) != NULL) {
-                        rewritelog(r, 5, "map lookup OK: map=%s key=%s[txt] "
-                                   "-> val=%s", s->name, key, value);
-                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
-                                         st.mtime, key, value);
-                        return value;
-                    }
-                    else {
-                        rewritelog(r, 5, "map lookup FAILED: map=%s[txt] "
-                                   "key=%s", s->name, key);
-                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
-                                         st.mtime, key, "");
-                        return NULL;
-                    }
-                }
-                else {
-                    rewritelog(r, 5, "cache lookup OK: map=%s[txt] key=%s "
-                               "-> val=%s", s->name, key, value);
-                    return value[0] != '\0' ? value : NULL;
-                }
-            }
-            else if (s->type == MAPTYPE_DBM) {
-                if ((rv = apr_stat(&st, s->checkfile,
-                                   APR_FINFO_MIN, r->pool)) != APR_SUCCESS) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                                  "mod_rewrite: can't access DBM RewriteMap "
-                                  "file %s", s->checkfile);
-                    rewritelog(r, 1, "can't open DBM RewriteMap file, "
-                               "see error log");
-                    return NULL;
-                }
-                value = get_cache_string(cachep, s->cachename, CACHEMODE_TS,
-                                         st.mtime, key);
-                if (value == NULL) {
-                    rewritelog(r, 6,
-                               "cache lookup FAILED, forcing new map lookup");
-                    if ((value =
-                         lookup_map_dbmfile(r, s->datafile, s->dbmtype, key)) != NULL) {
-                        rewritelog(r, 5, "map lookup OK: map=%s[dbm] key=%s "
-                                   "-> val=%s", s->name, key, value);
-                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
-                                         st.mtime, key, value);
-                        return value;
-                    }
-                    else {
-                        rewritelog(r, 5, "map lookup FAILED: map=%s[dbm] "
-                                   "key=%s", s->name, key);
-                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
-                                         st.mtime, key, "");
-                        return NULL;
-                    }
+    case 'r':
+    case 'R':
+        if (!*key || !strcasecmp(key, "edirect")) {        /* redirect */
+            int status = 0;
+
+            cfg->flags |= RULEFLAG_FORCEREDIRECT;
+            if (strlen(val) > 0) {
+                if (strcasecmp(val, "permanent") == 0) {
+                    status = HTTP_MOVED_PERMANENTLY;
                 }
-                else {
-                    rewritelog(r, 5, "cache lookup OK: map=%s[dbm] key=%s "
-                               "-> val=%s", s->name, key, value);
-                    return value[0] != '\0' ? value : NULL;
-                }
-            }
-            else if (s->type == MAPTYPE_PRG) {
-                if ((value =
-                     lookup_map_program(r, s->fpin, s->fpout, key)) != NULL) {
-                    rewritelog(r, 5, "map lookup OK: map=%s key=%s -> val=%s",
-                               s->name, key, value);
-                    return value;
-                }
-                else {
-                    rewritelog(r, 5, "map lookup FAILED: map=%s key=%s",
-                               s->name, key);
-                }
-            }
-            else if (s->type == MAPTYPE_INT) {
-                if ((value = s->func(r, key)) != NULL) {
-                    rewritelog(r, 5, "map lookup OK: map=%s key=%s -> val=%s",
-                               s->name, key, value);
-                    return value;
+                else if (strcasecmp(val, "temp") == 0) {
+                    status = HTTP_MOVED_TEMPORARILY;
                 }
-                else {
-                    rewritelog(r, 5, "map lookup FAILED: map=%s key=%s",
-                               s->name, key);
+                else if (strcasecmp(val, "seeother") == 0) {
+                    status = HTTP_SEE_OTHER;
                 }
-            }
-            else if (s->type == MAPTYPE_RND) {
-                if ((rv = apr_stat(&st, s->checkfile,
-                                   APR_FINFO_MIN, r->pool)) != APR_SUCCESS) {
-                    ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                                  "mod_rewrite: can't access text RewriteMap "
-                                  "file %s", s->checkfile);
-                    rewritelog(r, 1, "can't open RewriteMap file, "
-                               "see error log");
-                    return NULL;
-                }
-                value = get_cache_string(cachep, s->cachename, CACHEMODE_TS,
-                                         st.mtime, key);
-                if (value == NULL) {
-                    rewritelog(r, 6, "cache lookup FAILED, forcing new "
-                               "map lookup");
-                    if ((value =
-                         lookup_map_txtfile(r, s->datafile, key)) != NULL) {
-                        rewritelog(r, 5, "map lookup OK: map=%s key=%s[txt] "
-                                   "-> val=%s", s->name, key, value);
-                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
-                                         st.mtime, key, value);
+                else if (apr_isdigit(*val)) {
+                    status = atoi(val);
+                    if (status != HTTP_INTERNAL_SERVER_ERROR) {
+                        int idx =
+                            ap_index_of_response(HTTP_INTERNAL_SERVER_ERROR);
+
+                        if (ap_index_of_response(status) == idx) {
+                            return apr_psprintf(p, "RewriteRule: invalid HTTP "
+                                                   "response code '%s' for "
+                                                   "flag 'R'",
+                                                val);
+                        }
                     }
-                    else {
-                        rewritelog(r, 5, "map lookup FAILED: map=%s[txt] "
-                                   "key=%s", s->name, key);
-                        set_cache_string(cachep, s->cachename, CACHEMODE_TS,
-                                         st.mtime, key, "");
-                        return NULL;
+                    if (!ap_is_HTTP_REDIRECT(status)) {
+                        cfg->flags |= (RULEFLAG_STATUS | RULEFLAG_NOSUB);
                     }
                 }
-                else {
-                    rewritelog(r, 5, "cache lookup OK: map=%s[txt] key=%s "
-                               "-> val=%s", s->name, key, value);
-                }
-                if (value[0] != '\0') {
-                   value = select_random_value_part(r, value);
-                   rewritelog(r, 5, "randomly choosen the subvalue `%s'",
-                              value);
-                }
-                else {
-                    value = NULL;
-                }
-                return value;
+                cfg->forced_responsecode = status;
             }
         }
-    }
-    return NULL;
-}
-
-static char *lookup_map_txtfile(request_rec *r, const char *file, char *key)
-{
-    apr_file_t *fp = NULL;
-    apr_status_t rc;
-    char line[1024];
-    char *value = NULL;
-    char *cpT;
-    apr_size_t skip;
-    char *curkey;
-    char *curval;
-
-    rc = apr_file_open(&fp, file, APR_READ|APR_BUFFERED, APR_OS_DEFAULT, r->pool);
-    if (rc != APR_SUCCESS) {
-       return NULL;
-    }
-
-    while (apr_file_gets(line, sizeof(line), fp) == APR_SUCCESS) {
-        if (line[0] == '#') {
-            continue; /* ignore comments */
+        else {
+            ++error;
         }
-        cpT = line;
-        curkey = cpT;
-        skip = strcspn(cpT," \t\r\n");
-        if (skip == 0) {
-            continue; /* ignore lines that start with a space, tab, CR, or LF */
-        }
-        cpT += skip;
-        *cpT = '\0';
-        if (strcmp(curkey, key) != 0) {
-            continue; /* key does not match... */
-        }
-
-        /* found a matching key; now extract and return the value */
-        ++cpT;
-        skip = strspn(cpT, " \t\r\n");
-        cpT += skip;
-        curval = cpT;
-        skip = strcspn(cpT, " \t\r\n");
-        if (skip == 0) {
-            continue; /* no value... */
-        }
-        cpT += skip;
-        *cpT = '\0';
-        value = apr_pstrdup(r->pool, curval);
         break;
-    }
-    apr_file_close(fp);
-    return value;
-}
-
-static char *lookup_map_dbmfile(request_rec *r, const char *file,
-                                const char *dbmtype, char *key)
-{
-    apr_dbm_t *dbmfp = NULL;
-    apr_datum_t dbmkey;
-    apr_datum_t dbmval;
-    char *value;
-
-    if (apr_dbm_open_ex(&dbmfp, dbmtype, file, APR_DBM_READONLY, APR_OS_DEFAULT, 
-                        r->pool) != APR_SUCCESS) {
-        return NULL;
-    }
-
-    dbmkey.dptr  = key;
-    dbmkey.dsize = strlen(key);
-
-    if (apr_dbm_fetch(dbmfp, dbmkey, &dbmval) == APR_SUCCESS && dbmval.dptr) {
-        value = apr_pstrmemdup(r->pool, dbmval.dptr, dbmval.dsize);
-    }
-    else {
-        value = NULL;
-    }
-
-    apr_dbm_close(dbmfp);
-
-    return value;
-}
-
-static char *lookup_map_program(request_rec *r, apr_file_t *fpin,
-                                apr_file_t *fpout, char *key)
-{
-    char buf[LONG_STRING_LEN];
-    char c;
-    int i;
-    apr_size_t nbytes;
-    apr_status_t rv;
-
-#ifndef NO_WRITEV
-    struct iovec iova[2];
-    apr_size_t niov;
-#endif
 
-    /* when `RewriteEngine off' was used in the per-server
-     * context then the rewritemap-programs were not spawned.
-     * In this case using such a map (usually in per-dir context)
-     * is useless because it is not available.
-     *
-     * newlines in the key leave bytes in the pipe and cause
-     * bad things to happen (next map lookup will use the chars
-     * after the \n instead of the new key etc etc - in other words,
-     * the Rewritemap falls out of sync with the requests).
-     */
-    if (fpin == NULL || fpout == NULL || ap_strchr(key, '\n')) {
-        return NULL;
-    }
- 
-    /* take the lock */
+    case 's':
+    case 'S':
+        if (!*key || !strcasecmp(key, "kip")) {            /* skip */
+            cfg->skip = atoi(val);
+        }
+        else {
+            ++error;
+        }
+        break;
 
-    if (rewrite_mapr_lock_acquire) {
-        rv = apr_global_mutex_lock(rewrite_mapr_lock_acquire);
-        if (rv != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                          "apr_global_mutex_lock(rewrite_mapr_lock_acquire) "
-                          "failed");
-            return NULL; /* Maybe this should be fatal? */
+    case 't':
+    case 'T':
+        if (!*key || !strcasecmp(key, "ype")) {            /* type */
+            cfg->forced_mimetype = val;
+        }
+        else {
+            ++error;
         }
+        break;
+
+    default:
+        ++error;
+        break;
     }
 
-    /* write out the request key */
-#ifdef NO_WRITEV
-    nbytes = strlen(key);
-    apr_file_write(fpin, key, &nbytes);
-    nbytes = 1;
-    apr_file_write(fpin, "\n", &nbytes);
-#else
-    iova[0].iov_base = key;
-    iova[0].iov_len = strlen(key);
-    iova[1].iov_base = "\n";
-    iova[1].iov_len = 1;
+    if (error) {
+        return apr_pstrcat(p, "RewriteRule: unknown flag '", --key, "'", NULL);
+    }
 
-    niov = 2;
-    apr_file_writev(fpin, iova, niov, &nbytes);
-#endif
+    return NULL;
+}
 
-    /* read in the response value */
-    i = 0;
-    nbytes = 1;
-    apr_file_read(fpout, &c, &nbytes);
-    while (nbytes == 1 && (i < LONG_STRING_LEN-1)) {
-        if (c == '\n') {
-            break;
-        }
-        buf[i++] = c;
+static const char *cmd_rewriterule(cmd_parms *cmd, void *in_dconf,
+                                   const char *in_str)
+{
+    rewrite_perdir_conf *dconf = in_dconf;
+    char *str = apr_pstrdup(cmd->pool, in_str);
+    rewrite_server_conf *sconf;
+    rewriterule_entry *newrule;
+    ap_regex_t *regexp;
+    char *a1;
+    char *a2;
+    char *a3;
+    const char *err;
 
-        apr_file_read(fpout, &c, &nbytes);
+    sconf = ap_get_module_config(cmd->server->module_config, &rewrite_module);
+
+    /*  make a new entry in the internal rewrite rule list */
+    if (cmd->path == NULL) {   /* is server command */
+        newrule = apr_array_push(sconf->rewriterules);
+    }
+    else {                     /* is per-directory command */
+        newrule = apr_array_push(dconf->rewriterules);
     }
-    buf[i] = '\0';
 
-    /* give the lock back */
-    if (rewrite_mapr_lock_acquire) {
-        rv = apr_global_mutex_unlock(rewrite_mapr_lock_acquire);
-        if (rv != APR_SUCCESS) {
-            ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                          "apr_global_mutex_unlock(rewrite_mapr_lock_acquire) "
-                          "failed");
-            return NULL; /* Maybe this should be fatal? */
-        }
+    /*  parse the argument line ourself */
+    if (parseargline(str, &a1, &a2, &a3)) {
+        return apr_pstrcat(cmd->pool, "RewriteRule: bad argument line '", str,
+                           "'", NULL);
     }
 
-    if (strcasecmp(buf, "NULL") == 0) {
-        return NULL;
+    /* arg3: optional flags field */
+    newrule->forced_mimetype     = NULL;
+    newrule->forced_handler      = NULL;
+    newrule->forced_responsecode = HTTP_MOVED_TEMPORARILY;
+    newrule->flags  = RULEFLAG_NONE;
+    newrule->env = NULL;
+    newrule->cookie = NULL;
+    newrule->skip   = 0;
+    if (a3 != NULL) {
+        if ((err = cmd_parseflagfield(cmd->pool, newrule, a3,
+                                      cmd_rewriterule_setflag)) != NULL) {
+            return err;
+        }
     }
-    else {
-        return apr_pstrdup(r->pool, buf);
+
+    /* arg1: the pattern
+     * try to compile the regexp to test if is ok
+     */
+    if (*a1 == '!') {
+        newrule->flags |= RULEFLAG_NOTMATCH;
+        ++a1;
     }
-}
 
-static void ap_register_rewrite_mapfunc(char *name, rewrite_mapfunc_t *func)
-{
-    apr_hash_set(mapfunc_hash, name, strlen(name), (const void *)func);
-}
+    regexp = ap_pregcomp(cmd->pool, a1, AP_REG_EXTENDED |
+                                        ((newrule->flags & RULEFLAG_NOCASE)
+                                         ? AP_REG_ICASE : 0));
+    if (!regexp) {
+        return apr_pstrcat(cmd->pool,
+                           "RewriteRule: cannot compile regular expression '",
+                           a1, "'", NULL);
+    }
 
-static char *rewrite_mapfunc_toupper(request_rec *r, char *key)
-{
-    char *value, *cp;
+    newrule->pattern = a1;
+    newrule->regexp  = regexp;
 
-    for (cp = value = apr_pstrdup(r->pool, key); cp != NULL && *cp != '\0';
-         cp++) {
-        *cp = apr_toupper(*cp);
+    /* arg2: the output string */
+    newrule->output = a2;
+    if (*a2 == '-' && !a2[1]) {
+        newrule->flags |= RULEFLAG_NOSUB;
     }
-    return value;
-}
 
-static char *rewrite_mapfunc_tolower(request_rec *r, char *key)
-{
-    char *value, *cp;
-
-    for (cp = value = apr_pstrdup(r->pool, key); cp != NULL && *cp != '\0';
-         cp++) {
-        *cp = apr_tolower(*cp);
+    /* now, if the server or per-dir config holds an
+     * array of RewriteCond entries, we take it for us
+     * and clear the array
+     */
+    if (cmd->path == NULL) {  /* is server command */
+        newrule->rewriteconds   = sconf->rewriteconds;
+        sconf->rewriteconds = apr_array_make(cmd->pool, 2,
+                                             sizeof(rewritecond_entry));
     }
-    return value;
+    else {                    /* is per-directory command */
+        newrule->rewriteconds   = dconf->rewriteconds;
+        dconf->rewriteconds = apr_array_make(cmd->pool, 2,
+                                             sizeof(rewritecond_entry));
+    }
+
+    return NULL;
 }
 
-static char *rewrite_mapfunc_escape(request_rec *r, char *key)
-{
-    char *value;
 
-    value = ap_escape_uri(r->pool, key);
-    return value;
-}
+/*
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                  the rewriting engine
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
 
-static char *rewrite_mapfunc_unescape(request_rec *r, char *key)
+/* Lexicographic Compare */
+static APR_INLINE int compare_lexicography(char *a, char *b)
 {
-    char *value;
+    apr_size_t i, lena, lenb;
 
-    value = apr_pstrdup(r->pool, key);
-    ap_unescape_url(value);
-    return value;
-}
+    lena = strlen(a);
+    lenb = strlen(b);
 
-static int rewrite_rand_init_done = 0;
+    if (lena == lenb) {
+        for (i = 0; i < lena; ++i) {
+            if (a[i] != b[i]) {
+                return ((unsigned char)a[i] > (unsigned char)b[i]) ? 1 : -1;
+            }
+        }
 
-static void rewrite_rand_init(void)
-{
-    if (!rewrite_rand_init_done) {
-        srand((unsigned)(getpid()));
-        rewrite_rand_init_done = 1;
+        return 0;
     }
-    return;
+
+    return ((lena > lenb) ? 1 : -1);
 }
 
-static int rewrite_rand(int l, int h)
+/*
+ * Apply a single rewriteCond
+ */
+static int apply_rewrite_cond(rewritecond_entry *p, rewrite_ctx *ctx)
 {
-    rewrite_rand_init();
+    char *input = do_expand(p->input, ctx);
+    apr_finfo_t sb;
+    request_rec *rsub, *r = ctx->r;
+    ap_regmatch_t regmatch[AP_MAX_REG_MATCH];
+    int rc = 0;
+
+    switch (p->ptype) {
+    case CONDPAT_FILE_EXISTS:
+        if (   apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS
+            && sb.filetype == APR_REG) {
+            rc = 1;
+        }
+        break;
 
-    /* Get [0,1) and then scale to the appropriate range. Note that using
-     * a floating point value ensures that we use all bits of the rand()
-     * result. Doing an integer modulus would only use the lower-order bits
-     * which may not be as uniformly random.
-     */
-    return (int)(((double)(rand() % RAND_MAX) / RAND_MAX) * (h - l + 1) + l);
-}
+    case CONDPAT_FILE_SIZE:
+        if (   apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS
+            && sb.filetype == APR_REG && sb.size > 0) {
+            rc = 1;
+        }
+        break;
 
-static char *select_random_value_part(request_rec *r, char *value)
-{
-    char *buf;
-    int n, i, k;
+    case CONDPAT_FILE_LINK:
+#if !defined(OS2)
+        if (   apr_stat(&sb, input, APR_FINFO_MIN | APR_FINFO_LINK,
+                        r->pool) == APR_SUCCESS
+            && sb.filetype == APR_LNK) {
+            rc = 1;
+        }
+#endif
+        break;
 
-    /*  count number of distinct values  */
-    for (n = 1, i = 0; value[i] != '\0'; i++) {
-        if (value[i] == '|') {
-            n++;
+    case CONDPAT_FILE_DIR:
+        if (   apr_stat(&sb, input, APR_FINFO_MIN, r->pool) == APR_SUCCESS
+            && sb.filetype == APR_DIR) {
+            rc = 1;
         }
-    }
+        break;
 
-    /*  when only one value we have no option to choose  */
-    if (n == 1) {
-        return value;
-    }
+    case CONDPAT_FILE_XBIT:
+        if (   apr_stat(&sb, input, APR_FINFO_PROT, r->pool) == APR_SUCCESS
+            && (sb.protection & (APR_UEXECUTE | APR_GEXECUTE | APR_WEXECUTE))) {
+            rc = 1;
+        }
+        break;
 
-    /*  else randomly select one  */
-    k = rewrite_rand(1, n);
+    case CONDPAT_LU_URL:
+        if (*input && subreq_ok(r)) {
+            rsub = ap_sub_req_lookup_uri(input, r, NULL);
+            if (rsub->status < 400) {
+                rc = 1;
+            }
+            rewritelog((r, 5, NULL, "RewriteCond URI (-U) check: "
+                        "path=%s -> status=%d", input, rsub->status));
+            ap_destroy_sub_req(rsub);
+        }
+        break;
 
-    /*  and grep it out  */
-    for (n = 1, i = 0; value[i] != '\0'; i++) {
-        if (n == k) {
-            break;
+    case CONDPAT_LU_FILE:
+        if (*input && subreq_ok(r)) {
+            rsub = ap_sub_req_lookup_file(input, r, NULL);
+            if (rsub->status < 300 &&
+                /* double-check that file exists since default result is 200 */
+                apr_stat(&sb, rsub->filename, APR_FINFO_MIN,
+                         r->pool) == APR_SUCCESS) {
+                rc = 1;
+            }
+            rewritelog((r, 5, NULL, "RewriteCond file (-F) check: path=%s "
+                        "-> file=%s status=%d", input, rsub->filename,
+                        rsub->status));
+            ap_destroy_sub_req(rsub);
+        }
+        break;
+
+    case CONDPAT_STR_GT:
+        rc = (compare_lexicography(input, p->pattern+1) == 1) ? 1 : 0;
+        break;
+
+    case CONDPAT_STR_LT:
+        rc = (compare_lexicography(input, p->pattern+1) == -1) ? 1 : 0;
+        break;
+
+    case CONDPAT_STR_EQ:
+        if (p->flags & CONDFLAG_NOCASE) {
+            rc = !strcasecmp(input, p->pattern);
+        }
+        else {
+            rc = !strcmp(input, p->pattern);
         }
-        if (value[i] == '|') {
-            n++;
+        break;
+
+    default:
+        /* it is really a regexp pattern, so apply it */
+        rc = !ap_regexec(p->regexp, input, AP_MAX_REG_MATCH, regmatch, 0);
+
+        /* update briRC backref info */
+        if (rc && !(p->flags & CONDFLAG_NOTMATCH)) {
+            ctx->briRC.source = input;
+            ctx->briRC.nsub   = p->regexp->re_nsub;
+            memcpy(ctx->briRC.regmatch, regmatch, sizeof(regmatch));
         }
+        break;
     }
-    buf = apr_pstrdup(r->pool, &value[i]);
-    for (i = 0; buf[i] != '\0' && buf[i] != '|'; i++)
-        ;
-    buf[i] = '\0';
-    return buf;
-}
 
+    if (p->flags & CONDFLAG_NOTMATCH) {
+        rc = !rc;
+    }
 
-/*
-** +-------------------------------------------------------+
-** |                                                       |
-** |              rewriting logfile support
-** |                                                       |
-** +-------------------------------------------------------+
-*/
+    rewritelog((r, 4, ctx->perdir, "RewriteCond: input='%s' pattern='%s%s%s'%s "
+                "=> %s", input, (p->flags & CONDFLAG_NOTMATCH) ? "!" : "",
+                (p->ptype == CONDPAT_STR_EQ) ? "=" : "", p->pattern,
+                (p->flags & CONDFLAG_NOCASE) ? " [NC]" : "",
+                rc ? "matched" : "not-matched"));
 
+    return rc;
+}
 
-static int open_rewritelog(server_rec *s, apr_pool_t *p)
+/* check for forced type and handler */
+static APR_INLINE void force_type_handler(rewriterule_entry *p,
+                                          rewrite_ctx *ctx)
 {
-    rewrite_server_conf *conf;
-    const char *fname;
-    apr_status_t rc;
-    piped_log *pl;
-    int rewritelog_flags = ( APR_WRITE | APR_APPEND | APR_CREATE );
-    apr_fileperms_t rewritelog_mode = ( APR_UREAD | APR_UWRITE |
-                                        APR_GREAD | APR_WREAD );
+    char *expanded;
 
-    conf = ap_get_module_config(s->module_config, &rewrite_module);
+    if (p->forced_mimetype) {
+        expanded = do_expand(p->forced_mimetype, ctx);
 
-    /* - no logfile configured
-     * - logfilename empty
-     * - virtual log shared w/ main server
-     */
-    if (!conf->rewritelogfile || !*conf->rewritelogfile || conf->rewritelogfp) {
-        return 1;
-    }
+        if (*expanded) {
+            ap_str_tolower(expanded);
 
-    if (*conf->rewritelogfile == '|') {
-        if ((pl = ap_open_piped_log(p, conf->rewritelogfile+1)) == NULL) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, 0, s,
-                         "mod_rewrite: could not open reliable pipe "
-                         "to RewriteLog filter %s", conf->rewritelogfile+1);
-            return 0;
+            rewritelog((ctx->r, 2, ctx->perdir, "remember %s to have MIME-type "
+                        "'%s'", ctx->r->filename, expanded));
+
+            apr_table_setn(ctx->r->notes, REWRITE_FORCED_MIMETYPE_NOTEVAR,
+                           expanded);
         }
-        conf->rewritelogfp = ap_piped_log_write_fd(pl);
     }
-    else if (*conf->rewritelogfile != '\0') {
-        fname = ap_server_root_relative(p, conf->rewritelogfile);
-        if (!fname) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, APR_EBADPATH, s,
-                         "mod_rewrite: Invalid RewriteLog "
-                         "path %s", conf->rewritelogfile);
-            return 0;
-        }
-        if ((rc = apr_file_open(&conf->rewritelogfp, fname,
-                                rewritelog_flags, rewritelog_mode, p))
-                != APR_SUCCESS) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
-                         "mod_rewrite: could not open RewriteLog "
-                         "file %s", fname);
-            return 0;
+
+    if (p->forced_handler) {
+        expanded = do_expand(p->forced_handler, ctx);
+
+        if (*expanded) {
+            ap_str_tolower(expanded);
+
+            rewritelog((ctx->r, 2, ctx->perdir, "remember %s to have "
+                        "Content-handler '%s'", ctx->r->filename, expanded));
+
+            apr_table_setn(ctx->r->notes, REWRITE_FORCED_HANDLER_NOTEVAR,
+                           expanded);
         }
     }
-
-    return 1;
 }
 
-static void rewritelog(request_rec *r, int level, const char *text, ...)
+/*
+ * Apply a single RewriteRule
+ */
+static int apply_rewrite_rule(rewriterule_entry *p, rewrite_ctx *ctx)
 {
-    rewrite_server_conf *conf;
-    conn_rec *conn;
-    char *str1;
-    char str2[512];
-    char str3[1024];
-    const char *type;
-    char redir[20]; /* enough for "/redir#%d" if int is 32 bit */
-    va_list ap;
-    int i;
-    apr_size_t nbytes;
-    request_rec *req;
-    char *ruser;
-    const char *rhost;
-    apr_status_t rv;
+    ap_regmatch_t regmatch[AP_MAX_REG_MATCH];
+    apr_array_header_t *rewriteconds;
+    rewritecond_entry *conds;
+    int i, rc;
+    char *newuri = NULL;
+    request_rec *r = ctx->r;
+    int is_proxyreq = 0;
 
-    va_start(ap, text);
-    conf = ap_get_module_config(r->server->module_config, &rewrite_module);
-    conn = r->connection;
+    ctx->uri = r->filename;
 
-    if (conf->rewritelogfp == NULL) {
-        return;
-    }
-    if (conf->rewritelogfile == NULL) {
-        return;
-    }
-    if (*(conf->rewritelogfile) == '\0') {
-        return;
-    }
+    if (ctx->perdir) {
+        apr_size_t dirlen = strlen(ctx->perdir);
+
+        /*
+         * Proxy request?
+         */
+        is_proxyreq = (   r->proxyreq && r->filename
+                       && !strncmp(r->filename, "proxy:", 6));
+
+        /* Since we want to match against the (so called) full URL, we have
+         * to re-add the PATH_INFO postfix
+         */
+        if (r->path_info && *r->path_info) {
+            rewritelog((r, 3, ctx->perdir, "add path info postfix: %s -> %s%s",
+                        ctx->uri, ctx->uri, r->path_info));
+            ctx->uri = apr_pstrcat(r->pool, ctx->uri, r->path_info, NULL);
+        }
+
+        /* Additionally we strip the physical path from the url to match
+         * it independent from the underlaying filesystem.
+         */
+        if (!is_proxyreq && strlen(ctx->uri) >= dirlen &&
+            !strncmp(ctx->uri, ctx->perdir, dirlen)) {
 
-    if (level > conf->rewriteloglevel) {
-        return;
+            rewritelog((r, 3, ctx->perdir, "strip per-dir prefix: %s -> %s",
+                        ctx->uri, ctx->uri + dirlen));
+            ctx->uri = ctx->uri + dirlen;
+        }
     }
 
-    if (r->user == NULL) {
-        ruser = "-";
-    }
-    else if (strlen(r->user) != 0) {
-        ruser = r->user;
-    }
-    else {
-        ruser = "\"\"";
-    }
+    /* Try to match the URI against the RewriteRule pattern
+     * and exit immediately if it didn't apply.
+     */
+    rewritelog((r, 3, ctx->perdir, "applying pattern '%s' to uri '%s'",
+                p->pattern, ctx->uri));
 
-    rhost = ap_get_remote_host(conn, r->per_dir_config,
-                               REMOTE_NOLOOKUP, NULL);
-    if (rhost == NULL) {
-        rhost = "UNKNOWN-HOST";
+    rc = !ap_regexec(p->regexp, ctx->uri, AP_MAX_REG_MATCH, regmatch, 0);
+    if (! (( rc && !(p->flags & RULEFLAG_NOTMATCH)) ||
+           (!rc &&  (p->flags & RULEFLAG_NOTMATCH))   ) ) {
+        return 0;
     }
 
-    str1 = apr_pstrcat(r->pool, ap_escape_logitem(r->pool, rhost), " ",
-                       (conn->remote_logname != NULL
-                            ? ap_escape_logitem(r->pool, conn->remote_logname)
-                            : "-"),
-                       " ", ap_escape_logitem(r->pool, ruser), NULL);
-    apr_vsnprintf(str2, sizeof(str2), text, ap);
+    /* It matched, wow! Now it's time to prepare the context structure for
+     * further processing
+     */
+    ctx->vary_this = NULL;
+    ctx->briRC.source = NULL;
 
-    if (r->main == NULL) {
-        type = "initial";
+    if (p->flags & RULEFLAG_NOTMATCH) {
+        ctx->briRR.source = NULL;
     }
     else {
-        type = "subreq";
+        ctx->briRR.source = apr_pstrdup(r->pool, ctx->uri);
+        ctx->briRR.nsub   = p->regexp->re_nsub;
+        memcpy(ctx->briRR.regmatch, regmatch, sizeof(regmatch));
     }
 
-    for (i = 0, req = r; req->prev != NULL; req = req->prev) {
-        i++;
-    }
-    if (i == 0) {
-        redir[0] = '\0';
-    }
-    else {
-        apr_snprintf(redir, sizeof(redir), "/redir#%d", i);
-    }
+    /* Ok, we already know the pattern has matched, but we now
+     * additionally have to check for all existing preconditions
+     * (RewriteCond) which have to be also true. We do this at
+     * this very late stage to avoid unnessesary checks which
+     * would slow down the rewriting engine.
+     */
+    rewriteconds = p->rewriteconds;
+    conds = (rewritecond_entry *)rewriteconds->elts;
 
-    apr_snprintf(str3, sizeof(str3),
-                "%s %s [%s/sid#%lx][rid#%lx/%s%s] (%d) %s" APR_EOL_STR, str1,
-                current_logtime(r),
-                ap_escape_logitem(r->pool, ap_get_server_name(r)),
-                (unsigned long)(r->server), (unsigned long)r,
-                type, redir, level, ap_escape_logitem(r->pool, str2));
+    for (i = 0; i < rewriteconds->nelts; ++i) {
+        rewritecond_entry *c = &conds[i];
 
-    rv = apr_global_mutex_lock(rewrite_log_lock);
-    if (rv != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                      "apr_global_mutex_lock(rewrite_log_lock) failed");
-        /* XXX: Maybe this should be fatal? */
+        rc = apply_rewrite_cond(c, ctx);
+        if (c->flags & CONDFLAG_ORNEXT) {
+            if (!rc) {
+                /* One condition is false, but another can be still true. */
+                ctx->vary_this = NULL;
+                continue;
+            }
+            else {
+                /* skip the rest of the chained OR conditions */
+                while (   i < rewriteconds->nelts
+                       && c->flags & CONDFLAG_ORNEXT) {
+                    c = &conds[++i];
+                }
+                continue;
+            }
+        }
+        else if (!rc) {
+            return 0;
+        }
+
+        /* If some HTTP header was involved in the condition, remember it
+         * for later use
+         */
+        if (ctx->vary_this) {
+            ctx->vary = ctx->vary
+                        ? apr_pstrcat(r->pool, ctx->vary, ", ", ctx->vary_this,
+                                      NULL)
+                        : ctx->vary_this;
+            ctx->vary_this = NULL;
+        }
     }
-    nbytes = strlen(str3);
-    apr_file_write(conf->rewritelogfp, str3, &nbytes);
-    rv = apr_global_mutex_unlock(rewrite_log_lock);
-    if (rv != APR_SUCCESS) {
-        ap_log_rerror(APLOG_MARK, APLOG_ERR, rv, r,
-                      "apr_global_mutex_unlock(rewrite_log_lock) failed");
-        /* XXX: Maybe this should be fatal? */
+
+    /* expand the result */
+    if (!(p->flags & RULEFLAG_NOSUB)) {
+        newuri = do_expand(p->output, ctx);
+        rewritelog((r, 2, ctx->perdir, "rewrite '%s' -> '%s'", ctx->uri,
+                    newuri));
     }
 
-    va_end(ap);
-    return;
-}
+    /* expand [E=var:val] and [CO=<cookie>] */
+    do_expand_env(p->env, ctx);
+    do_expand_cookie(p->cookie, ctx);
 
-static char *current_logtime(request_rec *r)
-{
-    apr_time_exp_t t;
-    char tstr[80];
-    apr_size_t len;
+    /* non-substitution rules ('RewriteRule <pat> -') end here. */
+    if (p->flags & RULEFLAG_NOSUB) {
+        force_type_handler(p, ctx);
 
-    apr_time_exp_lt(&t, apr_time_now());
+        if (p->flags & RULEFLAG_STATUS) {
+            rewritelog((r, 2, ctx->perdir, "forcing responsecode %d for %s",
+                        p->forced_responsecode, r->filename));
 
-    apr_strftime(tstr, &len, 80, "[%d/%b/%Y:%H:%M:%S ", &t);
-    apr_snprintf(tstr + strlen(tstr), 80-strlen(tstr), "%c%.2d%.2d]",
-                 t.tm_gmtoff < 0 ? '-' : '+',
-                 t.tm_gmtoff / (60*60), t.tm_gmtoff % (60*60));
-    return apr_pstrdup(r->pool, tstr);
-}
+            r->status = p->forced_responsecode;
+        }
 
+        return 2;
+    }
 
+    /* Now adjust API's knowledge about r->filename and r->args */
+    r->filename = newuri;
+    splitout_queryargs(r, p->flags & RULEFLAG_QSAPPEND);
 
+    /* Add the previously stripped per-directory location prefix, unless
+     * (1) it's an absolute URL path and
+     * (2) it's a full qualified URL
+     */
+    if (   ctx->perdir && !is_proxyreq && *r->filename != '/'
+        && !is_absolute_uri(r->filename)) {
+        rewritelog((r, 3, ctx->perdir, "add per-dir prefix: %s -> %s%s",
+                    r->filename, ctx->perdir, r->filename));
 
-/*
-** +-------------------------------------------------------+
-** |                                                       |
-** |              rewriting lockfile support
-** |                                                       |
-** +-------------------------------------------------------+
-*/
+        r->filename = apr_pstrcat(r->pool, ctx->perdir, r->filename, NULL);
+    }
 
-#define REWRITELOCK_MODE ( APR_UREAD | APR_UWRITE | APR_GREAD | APR_WREAD )
+    /* If this rule is forced for proxy throughput
+     * (`RewriteRule ... ... [P]') then emulate mod_proxy's
+     * URL-to-filename handler to be sure mod_proxy is triggered
+     * for this URL later in the Apache API. But make sure it is
+     * a fully-qualified URL. (If not it is qualified with
+     * ourself).
+     */
+    if (p->flags & RULEFLAG_PROXY) {
+        fully_qualify_uri(r);
 
-static apr_status_t rewritelock_create(server_rec *s, apr_pool_t *p)
-{
-    apr_status_t rc;
+        rewritelog((r, 2, ctx->perdir, "forcing proxy-throughput with %s",
+                    r->filename));
 
-    /* only operate if a lockfile is used */
-    if (lockname == NULL || *(lockname) == '\0') {
-        return APR_SUCCESS;
+        r->filename = apr_pstrcat(r->pool, "proxy:", r->filename, NULL);
+        return 1;
     }
 
-    /* create the lockfile */
-    rc = apr_global_mutex_create(&rewrite_mapr_lock_acquire, lockname,
-                                 APR_LOCK_DEFAULT, p);
-    if (rc != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rc, s,
-                     "mod_rewrite: Parent could not create RewriteLock "
-                     "file %s", lockname);
-        return rc;
-    }
+    /* If this rule is explicitly forced for HTTP redirection
+     * (`RewriteRule .. .. [R]') then force an external HTTP
+     * redirect. But make sure it is a fully-qualified URL. (If
+     * not it is qualified with ourself).
+     */
+    if (p->flags & RULEFLAG_FORCEREDIRECT) {
+        fully_qualify_uri(r);
 
-#ifdef MOD_REWRITE_SET_MUTEX_PERMS
-    rc = unixd_set_global_mutex_perms(rewrite_mapr_lock_acquire);
-    if (rc != APR_SUCCESS) {
-        ap_log_error(APLOG_MARK, APLOG_CRIT, rc, s,
-                     "mod_rewrite: Parent could not set permissions "
-                     "on RewriteLock; check User and Group directives");
-        return rc;
+        rewritelog((r, 2, ctx->perdir, "explicitly forcing redirect with %s",
+                    r->filename));
+
+        r->status = p->forced_responsecode;
+        return 1;
     }
-#endif
 
-    return APR_SUCCESS;
-}
+    /* Special Rewriting Feature: Self-Reduction
+     * We reduce the URL by stripping a possible
+     * http[s]://<ourhost>[:<port>] prefix, i.e. a prefix which
+     * corresponds to ourself. This is to simplify rewrite maps
+     * and to avoid recursion, etc. When this prefix is not a
+     * coincidence then the user has to use [R] explicitly (see
+     * above).
+     */
+    reduce_uri(r);
 
-static apr_status_t rewritelock_remove(void *data)
-{
-    /* only operate if a lockfile is used */
-    if (lockname == NULL || *(lockname) == '\0') {
-        return APR_SUCCESS;
+    /* If this rule is still implicitly forced for HTTP
+     * redirection (`RewriteRule .. <scheme>://...') then
+     * directly force an external HTTP redirect.
+     */
+    if (is_absolute_uri(r->filename)) {
+        rewritelog((r, 2, ctx->perdir, "implicitly forcing redirect (rc=%d) "
+                    "with %s", p->forced_responsecode, r->filename));
+
+        r->status = p->forced_responsecode;
+        return 1;
     }
 
-    /* destroy the rewritelock */
-    apr_global_mutex_destroy (rewrite_mapr_lock_acquire);
-    rewrite_mapr_lock_acquire = NULL;
-    lockname = NULL;
-    return(0);
-}
+    /* Finally remember the forced mime-type */
+    force_type_handler(p, ctx);
 
+    /* Puuhhhhhhhh... WHAT COMPLICATED STUFF ;_)
+     * But now we're done for this particular rule.
+     */
+    return 1;
+}
 
 /*
-** +-------------------------------------------------------+
-** |                                                       |
-** |                  program map support
-** |                                                       |
-** +-------------------------------------------------------+
-*/
-
-static apr_status_t run_rewritemap_programs(server_rec *s, apr_pool_t *p)
+ * Apply a complete rule set,
+ * i.e. a list of rewrite rules
+ */
+static int apply_rewrite_list(request_rec *r, apr_array_header_t *rewriterules,
+                              char *perdir)
 {
-    rewrite_server_conf *conf;
-    apr_array_header_t *rewritemaps;
-    rewritemap_entry *entries;
+    rewriterule_entry *entries;
+    rewriterule_entry *p;
     int i;
-    apr_status_t rc;
+    int changed;
+    int rc;
+    int s;
+    rewrite_ctx *ctx;
 
-    conf = ap_get_module_config(s->module_config, &rewrite_module);
+    ctx = apr_palloc(r->pool, sizeof(*ctx));
+    ctx->perdir = perdir;
+    ctx->r = r;
 
-    /*  If the engine isn't turned on,
-     *  don't even try to do anything.
+    /*
+     *  Iterate over all existing rules
      */
-    if (conf->state == ENGINE_DISABLED) {
-        return APR_SUCCESS;
-    }
-
-    rewritemaps = conf->rewritemaps;
-    entries = (rewritemap_entry *)rewritemaps->elts;
-    for (i = 0; i < rewritemaps->nelts; i++) {
-        apr_file_t *fpin = NULL;
-        apr_file_t *fpout = NULL;
-        rewritemap_entry *map = &entries[i];
+    entries = (rewriterule_entry *)rewriterules->elts;
+    changed = 0;
+    loop:
+    for (i = 0; i < rewriterules->nelts; i++) {
+        p = &entries[i];
 
-        if (map->type != MAPTYPE_PRG) {
-            continue;
-        }
-        if (map->argv[0] == NULL
-            || *(map->argv[0]) == '\0'
-            || map->fpin  != NULL
-            || map->fpout != NULL        ) {
+        /*
+         *  Ignore this rule on subrequests if we are explicitly
+         *  asked to do so or this is a proxy-throughput or a
+         *  forced redirect rule.
+         */
+        if (r->main != NULL &&
+            (p->flags & RULEFLAG_IGNOREONSUBREQ ||
+             p->flags & RULEFLAG_FORCEREDIRECT    )) {
             continue;
         }
-        rc = rewritemap_program_child(p, map->argv[0], map->argv,
-                                      &fpout, &fpin);
-        if (rc != APR_SUCCESS || fpin == NULL || fpout == NULL) {
-            ap_log_error(APLOG_MARK, APLOG_ERR, rc, s,
-                         "mod_rewrite: could not startup RewriteMap "
-                         "program %s", map->datafile);
-            return rc;
-        }
-        map->fpin  = fpin;
-        map->fpout = fpout;
-    }
-    return APR_SUCCESS;
-}
 
-/* child process code */
-static apr_status_t rewritemap_program_child(apr_pool_t *p,
-                                             const char *progname, char **argv,
-                                             apr_file_t **fpout,
-                                             apr_file_t **fpin)
-{
-    apr_status_t rc;
-    apr_procattr_t *procattr;
-    apr_proc_t *procnew;
+        /*
+         *  Apply the current rule.
+         */
+        ctx->vary = NULL;
+        rc = apply_rewrite_rule(p, ctx);
 
-    if (((rc = apr_procattr_create(&procattr, p)) != APR_SUCCESS) ||
-        ((rc = apr_procattr_io_set(procattr, APR_FULL_BLOCK, APR_FULL_BLOCK,
-                                   APR_NO_PIPE)) != APR_SUCCESS) ||
-        ((rc = apr_procattr_dir_set(procattr,
-                                   ap_make_dirstr_parent(p, argv[0])))
-         != APR_SUCCESS) ||
-        ((rc = apr_procattr_cmdtype_set(procattr, APR_PROGRAM))
-         != APR_SUCCESS)) {
-        /* Something bad happened, give up and go away. */
-    }
-    else {
-        procnew = apr_pcalloc(p, sizeof(*procnew));
-        rc = apr_proc_create(procnew, argv[0], (const char **)argv, NULL,
-                             procattr, p);
+        if (rc) {
+            /* Regardless of what we do next, we've found a match. Check to see
+             * if any of the request header fields were involved, and add them
+             * to the Vary field of the response.
+             */
+            if (ctx->vary) {
+                apr_table_merge(r->headers_out, "Vary", ctx->vary);
+            }
 
-        if (rc == APR_SUCCESS) {
-            apr_pool_note_subprocess(p, procnew, APR_KILL_AFTER_TIMEOUT);
+            /*
+             * The rule sets the response code (implies match-only)
+             */
+            if (p->flags & RULEFLAG_STATUS) {
+                return ACTION_STATUS;
+            }
 
-            if (fpin) {
-                (*fpin) = procnew->in;
+            /*
+             * Indicate a change if this was not a match-only rule.
+             */
+            if (rc != 2) {
+                changed = ((p->flags & RULEFLAG_NOESCAPE)
+                           ? ACTION_NOESCAPE : ACTION_NORMAL);
             }
 
-            if (fpout) {
-                (*fpout) = procnew->out;
+            /*
+             *  Pass-Through Feature (`RewriteRule .. .. [PT]'):
+             *  Because the Apache 1.x API is very limited we
+             *  need this hack to pass the rewritten URL to other
+             *  modules like mod_alias, mod_userdir, etc.
+             */
+            if (p->flags & RULEFLAG_PASSTHROUGH) {
+                rewritelog((r, 2, perdir, "forcing '%s' to get passed through "
+                           "to next API URI-to-filename handler", r->filename));
+                r->filename = apr_pstrcat(r->pool, "passthrough:",
+                                         r->filename, NULL);
+                changed = ACTION_NORMAL;
+                break;
+            }
+
+            /*
+             *  Stop processing also on proxy pass-through and
+             *  last-rule and new-round flags.
+             */
+            if (p->flags & (RULEFLAG_PROXY | RULEFLAG_LASTRULE)) {
+                break;
+            }
+
+            /*
+             *  On "new-round" flag we just start from the top of
+             *  the rewriting ruleset again.
+             */
+            if (p->flags & RULEFLAG_NEWROUND) {
+                goto loop;
+            }
+
+            /*
+             *  If we are forced to skip N next rules, do it now.
+             */
+            if (p->skip > 0) {
+                s = p->skip;
+                while (   i < rewriterules->nelts
+                       && s > 0) {
+                    i++;
+                    p = &entries[i];
+                    s--;
+                }
+            }
+        }
+        else {
+            /*
+             *  If current rule is chained with next rule(s),
+             *  skip all this next rule(s)
+             */
+            while (   i < rewriterules->nelts
+                   && p->flags & RULEFLAG_CHAIN) {
+                i++;
+                p = &entries[i];
             }
         }
     }
-
-    return (rc);
+    return changed;
 }
 
 
-
-
 /*
-** +-------------------------------------------------------+
-** |                                                       |
-** |             environment variable support
-** |                                                       |
-** +-------------------------------------------------------+
-*/
-
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |             Module Initialization Hooks
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
 
-static char *lookup_variable(request_rec *r, char *var)
+static int pre_config(apr_pool_t *pconf,
+                      apr_pool_t *plog,
+                      apr_pool_t *ptemp)
 {
-    const char *result;
-    char resultbuf[LONG_STRING_LEN];
-    apr_time_exp_t tm;
-    request_rec *rsub;
-
-    result = NULL;
+    APR_OPTIONAL_FN_TYPE(ap_register_rewrite_mapfunc) *map_pfn_register;
 
-    /* HTTP headers */
-    if (strcasecmp(var, "HTTP_USER_AGENT") == 0) {
-        result = lookup_header(r, "User-Agent");
-    }
-    else if (strcasecmp(var, "HTTP_REFERER") == 0) {
-        result = lookup_header(r, "Referer");
-    }
-    else if (strcasecmp(var, "HTTP_COOKIE") == 0) {
-        result = lookup_header(r, "Cookie");
-    }
-    else if (strcasecmp(var, "HTTP_FORWARDED") == 0) {
-        result = lookup_header(r, "Forwarded");
-    }
-    else if (strcasecmp(var, "HTTP_HOST") == 0) {
-        result = lookup_header(r, "Host");
-    }
-    else if (strcasecmp(var, "HTTP_PROXY_CONNECTION") == 0) {
-        result = lookup_header(r, "Proxy-Connection");
-    }
-    else if (strcasecmp(var, "HTTP_ACCEPT") == 0) {
-        result = lookup_header(r, "Accept");
-    }
-    /* all other headers from which we are still not know about */
-    else if (strlen(var) > 5 && strncasecmp(var, "HTTP:", 5) == 0) {
-        result = lookup_header(r, var+5);
+    /* register int: rewritemap handlers */
+    mapfunc_hash = apr_hash_make(pconf);
+    map_pfn_register = APR_RETRIEVE_OPTIONAL_FN(ap_register_rewrite_mapfunc);
+    if (map_pfn_register) {
+        map_pfn_register("tolower", rewrite_mapfunc_tolower);
+        map_pfn_register("toupper", rewrite_mapfunc_toupper);
+        map_pfn_register("escape", rewrite_mapfunc_escape);
+        map_pfn_register("unescape", rewrite_mapfunc_unescape);
     }
+    return OK;
+}
 
-    /* connection stuff */
-    else if (strcasecmp(var, "REMOTE_ADDR") == 0) {
-        result = r->connection->remote_ip;
-    }
-    else if (strcasecmp(var, "REMOTE_PORT") == 0) {
-        return apr_itoa(r->pool, r->connection->remote_addr->port);
-    }
-    else if (strcasecmp(var, "REMOTE_HOST") == 0) {
-        result = (char *)ap_get_remote_host(r->connection,
-                                            r->per_dir_config, REMOTE_NAME, NULL);
-    }
-    else if (strcasecmp(var, "REMOTE_USER") == 0) {
-        result = r->user;
-    }
-    else if (strcasecmp(var, "REMOTE_IDENT") == 0) {
-        result = (char *)ap_get_remote_logname(r);
-    }
+static int post_config(apr_pool_t *p,
+                       apr_pool_t *plog,
+                       apr_pool_t *ptemp,
+                       server_rec *s)
+{
+    apr_status_t rv;
+    void *data;
+    int first_time = 0;
+    const char *userdata_key = "rewrite_init_module";
 
-    /* request stuff */
-    else if (strcasecmp(var, "THE_REQUEST") == 0) { /* non-standard */
-        result = r->the_request;
-    }
-    else if (strcasecmp(var, "REQUEST_METHOD") == 0) {
-        result = r->method;
-    }
-    else if (strcasecmp(var, "REQUEST_URI") == 0) { /* non-standard */
-        result = r->uri;
-    }
-    else if (strcasecmp(var, "SCRIPT_FILENAME") == 0 ||
-             strcasecmp(var, "REQUEST_FILENAME") == 0  ) {
-        result = r->filename;
-    }
-    else if (strcasecmp(var, "PATH_INFO") == 0) {
-        result = r->path_info;
-    }
-    else if (strcasecmp(var, "QUERY_STRING") == 0) {
-        result = r->args;
-    }
-    else if (strcasecmp(var, "AUTH_TYPE") == 0) {
-        result = r->ap_auth_type;
-    }
-    else if (strcasecmp(var, "IS_SUBREQ") == 0) { /* non-standard */
-        result = (r->main != NULL ? "true" : "false");
+    apr_pool_userdata_get(&data, userdata_key, s->process->pool);
+    if (!data) {
+        first_time = 1;
+        apr_pool_userdata_set((const void *)1, userdata_key,
+                              apr_pool_cleanup_null, s->process->pool);
     }
 
-    /* internal server stuff */
-    else if (strcasecmp(var, "DOCUMENT_ROOT") == 0) {
-        result = ap_document_root(r);
-    }
-    else if (strcasecmp(var, "SERVER_ADMIN") == 0) {
-        result = r->server->server_admin;
-    }
-    else if (strcasecmp(var, "SERVER_NAME") == 0) {
-        result = ap_get_server_name(r);
-    }
-    else if (strcasecmp(var, "SERVER_ADDR") == 0) { /* non-standard */
-        result = r->connection->local_ip;
-    }
-    else if (strcasecmp(var, "SERVER_PORT") == 0) {
-        apr_snprintf(resultbuf, sizeof(resultbuf), "%u", ap_get_server_port(r));
-        result = resultbuf;
-    }
-    else if (strcasecmp(var, "SERVER_PROTOCOL") == 0) {
-        result = r->protocol;
-    }
-    else if (strcasecmp(var, "SERVER_SOFTWARE") == 0) {
-        result = ap_get_server_version();
-    }
-    else if (strcasecmp(var, "API_VERSION") == 0) { /* non-standard */
-        apr_snprintf(resultbuf, sizeof(resultbuf), "%d:%d",
-                     MODULE_MAGIC_NUMBER_MAJOR, MODULE_MAGIC_NUMBER_MINOR);
-        result = resultbuf;
-    }
+    /* check if proxy module is available */
+    proxy_available = (ap_find_linked_module("mod_proxy.c") != NULL);
 
-/* XXX: wow this has gotta be slow if you actually use it for a lot, recalculates exploded time for each variable */
-    /* underlaying Unix system stuff */
-    else if (strcasecmp(var, "TIME_YEAR") == 0) {
-        apr_time_exp_lt(&tm, apr_time_now());
-        apr_snprintf(resultbuf, sizeof(resultbuf), "%04d", tm.tm_year + 1900);
-        result = resultbuf;
-    }
-#define MKTIMESTR(format, tmfield) \
-    apr_time_exp_lt(&tm, apr_time_now()); \
-    apr_snprintf(resultbuf, sizeof(resultbuf), format, tm.tmfield); \
-    result = resultbuf;
-    else if (strcasecmp(var, "TIME_MON") == 0) {
-        MKTIMESTR("%02d", tm_mon+1)
-    }
-    else if (strcasecmp(var, "TIME_DAY") == 0) {
-        MKTIMESTR("%02d", tm_mday)
-    }
-    else if (strcasecmp(var, "TIME_HOUR") == 0) {
-        MKTIMESTR("%02d", tm_hour)
-    }
-    else if (strcasecmp(var, "TIME_MIN") == 0) {
-        MKTIMESTR("%02d", tm_min)
-    }
-    else if (strcasecmp(var, "TIME_SEC") == 0) {
-        MKTIMESTR("%02d", tm_sec)
-    }
-    else if (strcasecmp(var, "TIME_WDAY") == 0) {
-        MKTIMESTR("%d", tm_wday)
-    }
-    else if (strcasecmp(var, "TIME") == 0) {
-        apr_time_exp_lt(&tm, apr_time_now());
-        apr_snprintf(resultbuf, sizeof(resultbuf),
-                     "%04d%02d%02d%02d%02d%02d", tm.tm_year + 1900,
-                     tm.tm_mon+1, tm.tm_mday,
-                     tm.tm_hour, tm.tm_min, tm.tm_sec);
-        result = resultbuf;
-        rewritelog(r, 1, "RESULT='%s'", result);
+#ifndef REWRITELOG_DISABLED
+    /* create the rewriting lockfiles in the parent */
+    if ((rv = apr_global_mutex_create(&rewrite_log_lock, NULL,
+                                      APR_LOCK_DEFAULT, p)) != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
+                     "mod_rewrite: could not create rewrite_log_lock");
+        return HTTP_INTERNAL_SERVER_ERROR;
     }
 
-    /* all other env-variables from the parent Apache process */
-    else if (strlen(var) > 4 && strncasecmp(var, "ENV:", 4) == 0) {
-        /* first try the internal Apache notes structure */
-        result = apr_table_get(r->notes, var+4);
-        /* second try the internal Apache env structure  */
-        if (result == NULL) {
-            result = apr_table_get(r->subprocess_env, var+4);
-        }
-        /* third try the external OS env */
-        if (result == NULL) {
-            result = getenv(var+4);
-        }
-    }
-    else if (strlen(var) > 4 && !strncasecmp(var, "SSL:", 4) 
-             && rewrite_ssl_lookup) {
-        result = rewrite_ssl_lookup(r->pool, r->server, r->connection, r, 
-                                    var + 4);
+#ifdef AP_NEED_SET_MUTEX_PERMS
+    rv = unixd_set_global_mutex_perms(rewrite_log_lock);
+    if (rv != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
+                     "mod_rewrite: Could not set permissions on "
+                     "rewrite_log_lock; check User and Group directives");
+        return HTTP_INTERNAL_SERVER_ERROR;
     }
+#endif /* perms */
+#endif /* rewritelog */
 
-#define LOOKAHEAD(subrecfunc) \
-        if ( \
-          /* filename is safe to use */ \
-          r->filename != NULL \
-              /* - and we're either not in a subrequest */ \
-              && ( r->main == NULL \
-                  /* - or in a subrequest where paths are non-NULL... */ \
-                    || ( r->main->uri != NULL && r->uri != NULL \
-                        /*   ...and sub and main paths differ */ \
-                        && strcmp(r->main->uri, r->uri) != 0))) { \
-            /* process a file-based subrequest */ \
-            rsub = subrecfunc(r->filename, r, NULL); \
-            /* now recursively lookup the variable in the sub_req */ \
-            result = lookup_variable(rsub, var+5); \
-            /* copy it up to our scope before we destroy sub_req's apr_pool_t */ \
-            result = apr_pstrdup(r->pool, result); \
-            /* cleanup by destroying the subrequest */ \
-            ap_destroy_sub_req(rsub); \
-            /* log it */ \
-            rewritelog(r, 5, "lookahead: path=%s var=%s -> val=%s", \
-                       r->filename, var+5, result); \
-            /* return ourself to prevent re-pstrdup */ \
-            return (char *)result; \
-        }
-
-    /* look-ahead for parameter through URI-based sub-request */
-    else if (strlen(var) > 5 && strncasecmp(var, "LA-U:", 5) == 0) {
-        LOOKAHEAD(ap_sub_req_lookup_uri)
-    }
-    /* look-ahead for parameter through file-based sub-request */
-    else if (strlen(var) > 5 && strncasecmp(var, "LA-F:", 5) == 0) {
-        LOOKAHEAD(ap_sub_req_lookup_file)
+    rv = rewritelock_create(s, p);
+    if (rv != APR_SUCCESS) {
+        return HTTP_INTERNAL_SERVER_ERROR;
     }
 
-    /* file stuff */
-    else if (strcasecmp(var, "SCRIPT_USER") == 0) {
-        result = "<unknown>";
-        if (r->finfo.valid & APR_FINFO_USER) {
-            apr_get_username((char **)&result, r->finfo.user, r->pool);
+    apr_pool_cleanup_register(p, (void *)s, rewritelock_remove,
+                              apr_pool_cleanup_null);
+
+    /* step through the servers and
+     * - open each rewriting logfile
+     * - open the RewriteMap prg:xxx programs
+     */
+    for (; s; s = s->next) {
+#ifndef REWRITELOG_DISABLED
+        if (!open_rewritelog(s, p)) {
+            return HTTP_INTERNAL_SERVER_ERROR;
         }
-    }
-    else if (strcasecmp(var, "SCRIPT_GROUP") == 0) {
-        result = "<unknown>";
-        if (r->finfo.valid & APR_FINFO_GROUP) {
-            apr_group_name_get((char **)&result, r->finfo.group, r->pool);
+#endif
+
+        if (!first_time) {
+            if (run_rewritemap_programs(s, p) != APR_SUCCESS) {
+                return HTTP_INTERNAL_SERVER_ERROR;
+            }
         }
-    } else if (strcasecmp(var, "HTTPS") == 0) {
-        int flag = rewrite_is_https && rewrite_is_https(r->connection);
-        result = flag ? "on" : "off";
     }
 
-    if (result == NULL) {
-        return apr_pstrdup(r->pool, "");
-    }
-    else {
-        return apr_pstrdup(r->pool, result);
-    }
+    rewrite_ssl_lookup = APR_RETRIEVE_OPTIONAL_FN(ssl_var_lookup);
+    rewrite_is_https = APR_RETRIEVE_OPTIONAL_FN(ssl_is_https);
+
+    return OK;
 }
 
-static char *lookup_header(request_rec *r, const char *name)
+static void init_child(apr_pool_t *p, server_rec *s)
 {
-    const apr_array_header_t *hdrs_arr;
-    const apr_table_entry_t *hdrs;
-    int i;
+    apr_status_t rv = 0; /* get a rid of gcc warning (REWRITELOG_DISABLED) */
 
-    hdrs_arr = apr_table_elts(r->headers_in);
-    hdrs = (const apr_table_entry_t *)hdrs_arr->elts;
-    for (i = 0; i < hdrs_arr->nelts; ++i) {
-        if (hdrs[i].key == NULL) {
-            continue;
-        }
-        if (strcasecmp(hdrs[i].key, name) == 0) {
-            apr_table_merge(r->notes, VARY_KEY_THIS, name);
-            return hdrs[i].val;
+    if (lockname != NULL && *(lockname) != '\0') {
+        rv = apr_global_mutex_child_init(&rewrite_mapr_lock_acquire,
+                                         lockname, p);
+        if (rv != APR_SUCCESS) {
+            ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
+                         "mod_rewrite: could not init rewrite_mapr_lock_acquire"
+                         " in child");
         }
     }
-    return NULL;
-}
 
+#ifndef REWRITELOG_DISABLED
+    rv = apr_global_mutex_child_init(&rewrite_log_lock, NULL, p);
+    if (rv != APR_SUCCESS) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
+                     "mod_rewrite: could not init rewrite log lock in child");
+    }
+#endif
 
+    /* create the lookup cache */
+    if (!init_cache(p)) {
+        ap_log_error(APLOG_MARK, APLOG_CRIT, rv, s,
+                     "mod_rewrite: could not init map cache in child");
+    }
+}
 
 
 /*
-** +-------------------------------------------------------+
-** |                                                       |
-** |                    caching support
-** |                                                       |
-** +-------------------------------------------------------+
-*/
-
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                     runtime hooks
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
 
-static cache *init_cache(apr_pool_t *p)
+/*
+ * URI-to-filename hook
+ * [deals with RewriteRules in server context]
+ */
+static int hook_uri2file(request_rec *r)
 {
-    cache *c;
+    rewrite_server_conf *conf;
+    const char *saved_rulestatus;
+    const char *var;
+    const char *thisserver;
+    char *thisport;
+    const char *thisurl;
+    unsigned int port;
+    int rulestatus;
 
-    c = (cache *)apr_palloc(p, sizeof(cache));
-    if (apr_pool_create(&c->pool, p) != APR_SUCCESS) {
-        return NULL;
+    /*
+     *  retrieve the config structures
+     */
+    conf = ap_get_module_config(r->server->module_config, &rewrite_module);
+
+    /*
+     *  only do something under runtime if the engine is really enabled,
+     *  else return immediately!
+     */
+    if (conf->state == ENGINE_DISABLED) {
+        return DECLINED;
     }
-    c->lists = apr_array_make(c->pool, 2, sizeof(cachelist));
-#if APR_HAS_THREADS
-    (void)apr_thread_mutex_create(&(c->lock), APR_THREAD_MUTEX_DEFAULT, p);
-#endif
-    return c;
-}
 
-static void set_cache_string(cache *c, const char *res, int mode, apr_time_t t,
-                             char *key, char *value)
-{
-    cacheentry ce;
+    /*
+     *  check for the ugly API case of a virtual host section where no
+     *  mod_rewrite directives exists. In this situation we became no chance
+     *  by the API to setup our default per-server config so we have to
+     *  on-the-fly assume we have the default config. But because the default
+     *  config has a disabled rewriting engine we are lucky because can
+     *  just stop operating now.
+     */
+    if (conf->server != r->server) {
+        return DECLINED;
+    }
 
-    ce.time  = t;
-    ce.key   = key;
-    ce.value = value;
-    store_cache_string(c, res, &ce);
-    return;
-}
+    /*
+     *  add the SCRIPT_URL variable to the env. this is a bit complicated
+     *  due to the fact that apache uses subrequests and internal redirects
+     */
 
-static char *get_cache_string(cache *c, const char *res, int mode,
-                              apr_time_t t, char *key)
-{
-    cacheentry *ce;
+    if (r->main == NULL) {
+         var = apr_table_get(r->subprocess_env, REDIRECT_ENVVAR_SCRIPT_URL);
+         if (var == NULL) {
+             apr_table_setn(r->subprocess_env, ENVVAR_SCRIPT_URL, r->uri);
+         }
+         else {
+             apr_table_setn(r->subprocess_env, ENVVAR_SCRIPT_URL, var);
+         }
+    }
+    else {
+         var = apr_table_get(r->main->subprocess_env, ENVVAR_SCRIPT_URL);
+         apr_table_setn(r->subprocess_env, ENVVAR_SCRIPT_URL, var);
+    }
 
-    ce = retrieve_cache_string(c, res, key);
-    if (ce == NULL) {
-        return NULL;
+    /*
+     *  create the SCRIPT_URI variable for the env
+     */
+
+    /* add the canonical URI of this URL */
+    thisserver = ap_get_server_name(r);
+    port = ap_get_server_port(r);
+    if (ap_is_default_port(port, r)) {
+        thisport = "";
     }
-    if (mode & CACHEMODE_TS) {
-        if (t != ce->time) {
-            return NULL;
-        }
+    else {
+        thisport = apr_psprintf(r->pool, ":%u", port);
     }
-    else if (mode & CACHEMODE_TTL) {
-        if (t > ce->time) {
-            return NULL;
+    thisurl = apr_table_get(r->subprocess_env, ENVVAR_SCRIPT_URL);
+
+    /* set the variable */
+    var = apr_pstrcat(r->pool, ap_http_scheme(r), "://", thisserver, thisport,
+                      thisurl, NULL);
+    apr_table_setn(r->subprocess_env, ENVVAR_SCRIPT_URI, var);
+
+    if (!(saved_rulestatus = apr_table_get(r->notes,"mod_rewrite_rewritten"))) {
+        /* if filename was not initially set,
+         * we start with the requested URI
+         */
+        if (r->filename == NULL) {
+            r->filename = apr_pstrdup(r->pool, r->uri);
+            rewritelog((r, 2, NULL, "init rewrite engine with requested uri %s",
+                        r->filename));
+        }
+        else {
+            rewritelog((r, 2, NULL, "init rewrite engine with passed filename "
+                        "%s. Original uri = %s", r->filename, r->uri));
         }
-    }
-    return ce->value;
-}
 
-static int cache_tlb_hash(char *key)
-{
-    unsigned long n;
-    char *p;
+        /*
+         *  now apply the rules ...
+         */
+        rulestatus = apply_rewrite_list(r, conf->rewriterules, NULL);
+        apr_table_set(r->notes,"mod_rewrite_rewritten",
+                      apr_psprintf(r->pool,"%d",rulestatus));
+    }
+    else {
+        rewritelog((r, 2, NULL, "uri already rewritten. Status %s, Uri %s, "
+                    "r->filename %s", saved_rulestatus, r->uri, r->filename));
 
-    n = 0;
-    for (p = key; *p != '\0'; p++) {
-        n = ((n << 5) + n) ^ (unsigned long)(*p++);
+        rulestatus = atoi(saved_rulestatus);
     }
 
-    return n % CACHE_TLB_ROWS;
-}
+    if (rulestatus) {
+        unsigned skip;
+        apr_size_t flen;
 
-static cacheentry *cache_tlb_lookup(cachetlbentry *tlb, cacheentry *elt,
-                                    char *key)
-{
-    int ix = cache_tlb_hash(key);
-    int i;
-    int j;
+        if (ACTION_STATUS == rulestatus) {
+            int n = r->status;
 
-    for (i=0; i < CACHE_TLB_COLS; ++i) {
-        j = tlb[ix].t[i];
-        if (j < 0)
-            return NULL;
-        if (strcmp(elt[j].key, key) == 0)
-            return &elt[j];
-    }
-    return NULL;
-}
+            r->status = HTTP_OK;
+            return n;
+        }
+
+        flen = r->filename ? strlen(r->filename) : 0;
+        if (flen > 6 && strncmp(r->filename, "proxy:", 6) == 0) {
+            /* it should be go on as an internal proxy request */
 
-static void cache_tlb_replace(cachetlbentry *tlb, cacheentry *elt,
-                              cacheentry *e)
-{
-    int ix = cache_tlb_hash(e->key);
-    int i;
+            /* check if the proxy module is enabled, so
+             * we can actually use it!
+             */
+            if (!proxy_available) {
+                ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                              "attempt to make remote request from mod_rewrite "
+                              "without proxy enabled: %s", r->filename);
+                return HTTP_FORBIDDEN;
+            }
 
-    tlb = &tlb[ix];
+            /* make sure the QUERY_STRING and
+             * PATH_INFO parts get incorporated
+             */
+            if (r->path_info != NULL) {
+                r->filename = apr_pstrcat(r->pool, r->filename,
+                                          r->path_info, NULL);
+            }
+            if (r->args != NULL &&
+                r->uri == r->unparsed_uri) {
+                /* see proxy_http:proxy_http_canon() */
+                r->filename = apr_pstrcat(r->pool, r->filename,
+                                          "?", r->args, NULL);
+            }
 
-    for (i=1; i < CACHE_TLB_COLS; ++i)
-        tlb->t[i] = tlb->t[i-1];
+            /* now make sure the request gets handled by the proxy handler */
+            if (PROXYREQ_NONE == r->proxyreq) {
+                r->proxyreq = PROXYREQ_REVERSE;
+            }
+            r->handler  = "proxy-server";
 
-    tlb->t[0] = e - elt;
-}
+            rewritelog((r, 1, NULL, "go-ahead with proxy request %s [OK]",
+                        r->filename));
+            return OK;
+        }
+        else if ((skip = is_absolute_uri(r->filename)) > 0) {
+            int n;
 
-static void store_cache_string(cache *c, const char *res, cacheentry *ce)
-{
-    int i;
-    int j;
-    cachelist *l;
-    cacheentry *e;
-    cachetlbentry *t;
-    int found_list;
+            /* it was finally rewritten to a remote URL */
 
-#if APR_HAS_THREADS
-    apr_thread_mutex_lock(c->lock);
-#endif
+            if (rulestatus != ACTION_NOESCAPE) {
+                rewritelog((r, 1, NULL, "escaping %s for redirect",
+                            r->filename));
+                r->filename = escape_absolute_uri(r->pool, r->filename, skip);
+            }
 
-    found_list = 0;
-    /* first try to edit an existing entry */
-    for (i = 0; i < c->lists->nelts; i++) {
-        l = &(((cachelist *)c->lists->elts)[i]);
-        if (strcmp(l->resource, res) == 0) {
-            found_list = 1;
-
-            e = cache_tlb_lookup((cachetlbentry *)l->tlb->elts,
-                                 (cacheentry *)l->entries->elts, ce->key);
-            if (e != NULL) {
-                e->time  = ce->time;
-                e->value = apr_pstrdup(c->pool, ce->value);
-#if APR_HAS_THREADS
-                apr_thread_mutex_unlock(c->lock);
-#endif
-                return;
+            /* append the QUERY_STRING part */
+            if (r->args) {
+                r->filename = apr_pstrcat(r->pool, r->filename, "?",
+                                          (rulestatus == ACTION_NOESCAPE)
+                                            ? r->args
+                                            : ap_escape_uri(r->pool, r->args),
+                                          NULL);
             }
 
-            for (j = 0; j < l->entries->nelts; j++) {
-                e = &(((cacheentry *)l->entries->elts)[j]);
-                if (strcmp(e->key, ce->key) == 0) {
-                    e->time  = ce->time;
-                    e->value = apr_pstrdup(c->pool, ce->value);
-                    cache_tlb_replace((cachetlbentry *)l->tlb->elts,
-                                      (cacheentry *)l->entries->elts, e);
-#if APR_HAS_THREADS
-                    apr_thread_mutex_unlock(c->lock);
-#endif
-                    return;
-                }
+            /* determine HTTP redirect response code */
+            if (ap_is_HTTP_REDIRECT(r->status)) {
+                n = r->status;
+                r->status = HTTP_OK; /* make Apache kernel happy */
+            }
+            else {
+                n = HTTP_MOVED_TEMPORARILY;
             }
-        }
-    }
 
-    /* create a needed new list */
-    if (!found_list) {
-        l = apr_array_push(c->lists);
-        l->resource = apr_pstrdup(c->pool, res);
-        l->entries  = apr_array_make(c->pool, 2, sizeof(cacheentry));
-        l->tlb      = apr_array_make(c->pool, CACHE_TLB_ROWS,
-                                    sizeof(cachetlbentry));
-        for (i=0; i<CACHE_TLB_ROWS; ++i) {
-            t = &((cachetlbentry *)l->tlb->elts)[i];
-                for (j=0; j<CACHE_TLB_COLS; ++j)
-                    t->t[j] = -1;
-        }
-    }
+            /* now do the redirection */
+            apr_table_setn(r->headers_out, "Location", r->filename);
+            rewritelog((r, 1, NULL, "redirect to %s [REDIRECT/%d]", r->filename,
+                        n));
 
-    /* create the new entry */
-    for (i = 0; i < c->lists->nelts; i++) {
-        l = &(((cachelist *)c->lists->elts)[i]);
-        if (strcmp(l->resource, res) == 0) {
-            e = apr_array_push(l->entries);
-            e->time  = ce->time;
-            e->key   = apr_pstrdup(c->pool, ce->key);
-            e->value = apr_pstrdup(c->pool, ce->value);
-            cache_tlb_replace((cachetlbentry *)l->tlb->elts,
-                              (cacheentry *)l->entries->elts, e);
-#if APR_HAS_THREADS
-            apr_thread_mutex_unlock(c->lock);
-#endif
-            return;
+            return n;
         }
-    }
-
-    /* not reached, but when it is no problem... */
-#if APR_HAS_THREADS
-    apr_thread_mutex_unlock(c->lock);
-#endif
-    return;
-}
-
-static cacheentry *retrieve_cache_string(cache *c, const char *res, char *key)
-{
-    int i;
-    int j;
-    cachelist *l;
-    cacheentry *e;
+        else if (flen > 12 && strncmp(r->filename, "passthrough:", 12) == 0) {
+            /*
+             * Hack because of underpowered API: passing the current
+             * rewritten filename through to other URL-to-filename handlers
+             * just as it were the requested URL. This is to enable
+             * post-processing by mod_alias, etc.  which always act on
+             * r->uri! The difference here is: We do not try to
+             * add the document root
+             */
+            r->uri = apr_pstrdup(r->pool, r->filename+12);
+            return DECLINED;
+        }
+        else {
+            /* it was finally rewritten to a local path */
 
-#if APR_HAS_THREADS
-    apr_thread_mutex_lock(c->lock);
+            /* expand "/~user" prefix */
+#if APR_HAS_USER
+            r->filename = expand_tildepaths(r, r->filename);
 #endif
+            rewritelog((r, 2, NULL, "local path result: %s", r->filename));
 
-    for (i = 0; i < c->lists->nelts; i++) {
-        l = &(((cachelist *)c->lists->elts)[i]);
-        if (strcmp(l->resource, res) == 0) {
-
-            e = cache_tlb_lookup((cachetlbentry *)l->tlb->elts,
-                                 (cacheentry *)l->entries->elts, key);
-            if (e != NULL) {
-#if APR_HAS_THREADS
-                apr_thread_mutex_unlock(c->lock);
-#endif
-                return e;
+            /* the filename must be either an absolute local path or an
+             * absolute local URL.
+             */
+            if (   *r->filename != '/'
+                && !ap_os_is_path_absolute(r->pool, r->filename)) {
+                return HTTP_BAD_REQUEST;
             }
 
-            for (j = 0; j < l->entries->nelts; j++) {
-                e = &(((cacheentry *)l->entries->elts)[j]);
-                if (strcmp(e->key, key) == 0) {
-#if APR_HAS_THREADS
-                    apr_thread_mutex_unlock(c->lock);
-#endif
-                    return e;
+            /* if there is no valid prefix, we call
+             * the translator from the core and
+             * prefix the filename with document_root
+             *
+             * NOTICE:
+             * We cannot leave out the prefix_stat because
+             * - when we always prefix with document_root
+             *   then no absolute path can be created, e.g. via
+             *   emulating a ScriptAlias directive, etc.
+             * - when we always NOT prefix with document_root
+             *   then the files under document_root have to
+             *   be references directly and document_root
+             *   gets never used and will be a dummy parameter -
+             *   this is also bad
+             *
+             * BUT:
+             * Under real Unix systems this is no problem,
+             * because we only do stat() on the first directory
+             * and this gets cached by the kernel for along time!
+             */
+            if (!prefix_stat(r->filename, r->pool)) {
+                int res;
+                char *tmp = r->uri;
+
+                r->uri = r->filename;
+                res = ap_core_translate(r);
+                r->uri = tmp;
+
+                if (res != OK) {
+                    rewritelog((r, 1, NULL, "prefixing with document_root of %s"
+                                " FAILED", r->filename));
+
+                    return res;
                 }
+
+                rewritelog((r, 2, NULL, "prefixed with document_root to %s",
+                            r->filename));
             }
+
+            rewritelog((r, 1, NULL, "go-ahead with %s [OK]", r->filename));
+            return OK;
         }
     }
-#if APR_HAS_THREADS
-    apr_thread_mutex_unlock(c->lock);
-#endif
-    return NULL;
+    else {
+        rewritelog((r, 1, NULL, "pass through %s", r->filename));
+        return DECLINED;
+    }
 }
 
-
-
-
-/*
-** +-------------------------------------------------------+
-** |                                                       |
-** |                    misc functions
-** |                                                       |
-** +-------------------------------------------------------+
-*/
-
 /*
- * substitute the prefix path 'match' in 'input' with 'subst'
- * (think of RewriteBase which substitutes the physical path with
- *  the virtual path)
+ * Fixup hook
+ * [RewriteRules in directory context]
  */
-
-static char *subst_prefix_path(request_rec *r, char *input, char *match,
-                               const char *subst)
+static int hook_fixup(request_rec *r)
 {
-    apr_size_t len = strlen(match);
+    rewrite_perdir_conf *dconf;
+    char *cp;
+    char *cp2;
+    const char *ccp;
+    apr_size_t l;
+    int rulestatus;
+    int n;
+    char *ofilename;
+    int is_proxyreq;
 
-    if (len && match[len - 1] == '/') {
-        --len;
+    dconf = (rewrite_perdir_conf *)ap_get_module_config(r->per_dir_config,
+                                                        &rewrite_module);
+
+    /* if there is no per-dir config we return immediately */
+    if (dconf == NULL) {
+        return DECLINED;
     }
 
-    if (!strncmp(input, match, len) && input[len++] == '/') {
-        apr_size_t slen, outlen;
-        char *output;
+    /* if there are no real (i.e. no RewriteRule directives!)
+       per-dir config of us, we return also immediately */
+    if (dconf->directory == NULL) {
+        return DECLINED;
+    }
 
-        rewritelog(r, 5, "strip matching prefix: %s -> %s", input, input+len);
+    /*
+     * Proxy request?
+     */
+    is_proxyreq = (   r->proxyreq && r->filename
+                   && !strncmp(r->filename, "proxy:", 6));
 
-        slen = strlen(subst);
-        if (slen && subst[slen - 1] != '/') {
-            ++slen;
+    /*
+     *  .htaccess file is called before really entering the directory, i.e.:
+     *  URL: http://localhost/foo  and .htaccess is located in foo directory
+     *  Ignore such attempts, since they may lead to undefined behaviour.
+     */
+    if (!is_proxyreq) {
+        l = strlen(dconf->directory) - 1;
+        if (r->filename && strlen(r->filename) == l &&
+            (dconf->directory)[l] == '/' &&
+            !strncmp(r->filename, dconf->directory, l)) {
+            return DECLINED;
         }
+    }
 
-        outlen = strlen(input) + slen - len;
-        output = apr_palloc(r->pool, outlen + 1); /* don't forget the \0 */
+    /*
+     *  only do something under runtime if the engine is really enabled,
+     *  for this directory, else return immediately!
+     */
+    if (dconf->state == ENGINE_DISABLED) {
+        return DECLINED;
+    }
 
-        memcpy(output, subst, slen);
-        if (slen && !output[slen-1]) {
-            output[slen-1] = '/';
-        }
-        memcpy(output+slen, input+len, outlen - slen);
-        output[outlen] = '\0';
+    /*
+     *  Do the Options check after engine check, so
+     *  the user is able to explicitely turn RewriteEngine Off.
+     */
+    if (!(ap_allow_options(r) & (OPT_SYM_LINKS | OPT_SYM_OWNER))) {
+        /* FollowSymLinks is mandatory! */
+        ap_log_rerror(APLOG_MARK, APLOG_ERR, 0, r,
+                     "Options FollowSymLinks or SymLinksIfOwnerMatch is off "
+                     "which implies that RewriteRule directive is forbidden: "
+                     "%s", r->filename);
+        return HTTP_FORBIDDEN;
+    }
 
-        rewritelog(r, 4, "add subst prefix: %s -> %s", input+len, output);
+    /*
+     *  remember the current filename before rewriting for later check
+     *  to prevent deadlooping because of internal redirects
+     *  on final URL/filename which can be equal to the inital one.
+     *  also, we'll restore original r->filename if we decline this
+     *  request
+     */
+    ofilename = r->filename;
 
-        return output;
+    if (r->filename == NULL) {
+        r->filename = apr_pstrdup(r->pool, r->uri);
+        rewritelog((r, 2, "init rewrite engine with requested uri %s",
+                    r->filename));
     }
 
-    /* prefix didn't match */
-    return input;
-}
+    /*
+     *  now apply the rules ...
+     */
+    rulestatus = apply_rewrite_list(r, dconf->rewriterules, dconf->directory);
+    if (rulestatus) {
+        unsigned skip;
 
+        if (ACTION_STATUS == rulestatus) {
+            int n = r->status;
 
-/*
-**
-**  own command line parser which don't have the '\\' problem
-**
-*/
+            r->status = HTTP_OK;
+            return n;
+        }
 
-static int parseargline(char *str, char **a1, char **a2, char **a3)
-{
-    char *cp;
-    int isquoted;
+        l = strlen(r->filename);
+        if (l > 6 && strncmp(r->filename, "proxy:", 6) == 0) {
+            /* it should go on as an internal proxy request */
 
-#define SKIP_WHITESPACE(cp) \
-    for ( ; *cp == ' ' || *cp == '\t'; ) { \
-        cp++; \
-    };
-
-#define CHECK_QUOTATION(cp,isquoted) \
-    isquoted = 0; \
-    if (*cp == '"') { \
-        isquoted = 1; \
-        cp++; \
-    }
-
-#define DETERMINE_NEXTSTRING(cp,isquoted) \
-    for ( ; *cp != '\0'; cp++) { \
-        if (   (isquoted    && (*cp     == ' ' || *cp     == '\t')) \
-            || (*cp == '\\' && (*(cp+1) == ' ' || *(cp+1) == '\t'))) { \
-            cp++; \
-            continue; \
-        } \
-        if (   (!isquoted && (*cp == ' ' || *cp == '\t')) \
-            || (isquoted  && *cp == '"')                  ) { \
-            break; \
-        } \
-    }
-
-    cp = str;
-    SKIP_WHITESPACE(cp);
-
-    /*  determine first argument */
-    CHECK_QUOTATION(cp, isquoted);
-    *a1 = cp;
-    DETERMINE_NEXTSTRING(cp, isquoted);
-    if (*cp == '\0') {
-        return 1;
-    }
-    *cp++ = '\0';
+            /* make sure the QUERY_STRING and
+             * PATH_INFO parts get incorporated
+             * (r->path_info was already appended by the
+             * rewriting engine because of the per-dir context!)
+             */
+            if (r->args != NULL) {
+                r->filename = apr_pstrcat(r->pool, r->filename,
+                                          "?", r->args, NULL);
+            }
+
+            /* now make sure the request gets handled by the proxy handler */
+            if (PROXYREQ_NONE == r->proxyreq) {
+                r->proxyreq = PROXYREQ_REVERSE;
+            }
+            r->handler  = "proxy-server";
 
-    SKIP_WHITESPACE(cp);
+            rewritelog((r, 1, dconf->directory, "go-ahead with proxy request "
+                        "%s [OK]", r->filename));
+            return OK;
+        }
+        else if ((skip = is_absolute_uri(r->filename)) > 0) {
+            /* it was finally rewritten to a remote URL */
 
-    /*  determine second argument */
-    CHECK_QUOTATION(cp, isquoted);
-    *a2 = cp;
-    DETERMINE_NEXTSTRING(cp, isquoted);
-    if (*cp == '\0') {
-        *cp++ = '\0';
-        *a3 = NULL;
-        return 0;
-    }
-    *cp++ = '\0';
+            /* because we are in a per-dir context
+             * first try to replace the directory with its base-URL
+             * if there is a base-URL available
+             */
+            if (dconf->baseurl != NULL) {
+                /* skip 'scheme://' */
+                cp = r->filename + skip;
 
-    SKIP_WHITESPACE(cp);
+                if ((cp = ap_strchr(cp, '/')) != NULL && *(++cp)) {
+                    rewritelog((r, 2, dconf->directory,
+                                "trying to replace prefix %s with %s",
+                                dconf->directory, dconf->baseurl));
 
-    /* again check if there are only two arguments */
-    if (*cp == '\0') {
-        *cp++ = '\0';
-        *a3 = NULL;
-        return 0;
-    }
+                    /* I think, that hack needs an explanation:
+                     * well, here is it:
+                     * mod_rewrite was written for unix systems, were
+                     * absolute file-system paths start with a slash.
+                     * URL-paths _also_ start with slashes, so they
+                     * can be easily compared with system paths.
+                     *
+                     * the following assumes, that the actual url-path
+                     * may be prefixed by the current directory path and
+                     * tries to replace the system path with the RewriteBase
+                     * URL.
+                     * That assumption is true if we use a RewriteRule like
+                     *
+                     * RewriteRule ^foo bar [R]
+                     *
+                     * (see apply_rewrite_rule function)
+                     * However on systems that don't have a / as system
+                     * root this will never match, so we skip the / after the
+                     * hostname and compare/substitute only the stuff after it.
+                     *
+                     * (note that cp was already increased to the right value)
+                     */
+                    cp2 = subst_prefix_path(r, cp, (*dconf->directory == '/')
+                                                   ? dconf->directory + 1
+                                                   : dconf->directory,
+                                            dconf->baseurl + 1);
+                    if (strcmp(cp2, cp) != 0) {
+                        *cp = '\0';
+                        r->filename = apr_pstrcat(r->pool, r->filename,
+                                                  cp2, NULL);
+                    }
+                }
+            }
 
-    /*  determine second argument */
-    CHECK_QUOTATION(cp, isquoted);
-    *a3 = cp;
-    DETERMINE_NEXTSTRING(cp, isquoted);
-    *cp++ = '\0';
+            /* now prepare the redirect... */
+            if (rulestatus != ACTION_NOESCAPE) {
+                rewritelog((r, 1, dconf->directory, "escaping %s for redirect",
+                            r->filename));
+                r->filename = escape_absolute_uri(r->pool, r->filename, skip);
+            }
 
-    return 0;
-}
+            /* append the QUERY_STRING part */
+            if (r->args) {
+                r->filename = apr_pstrcat(r->pool, r->filename, "?",
+                                          (rulestatus == ACTION_NOESCAPE)
+                                            ? r->args
+                                            : ap_escape_uri(r->pool, r->args),
+                                          NULL);
+            }
 
+            /* determine HTTP redirect response code */
+            if (ap_is_HTTP_REDIRECT(r->status)) {
+                n = r->status;
+                r->status = HTTP_OK; /* make Apache kernel happy */
+            }
+            else {
+                n = HTTP_MOVED_TEMPORARILY;
+            }
 
-static void add_env_variable(request_rec *r, char *s)
-{
-    char var[MAX_STRING_LEN];
-    char val[MAX_STRING_LEN];
-    char *cp;
-    int n;
+            /* now do the redirection */
+            apr_table_setn(r->headers_out, "Location", r->filename);
+            rewritelog((r, 1, dconf->directory, "redirect to %s [REDIRECT/%d]",
+                        r->filename, n));
+            return n;
+        }
+        else {
+            /* it was finally rewritten to a local path */
 
-    if ((cp = strchr(s, ':')) != NULL) {
-        n = ((cp-s) > MAX_STRING_LEN-1 ? MAX_STRING_LEN-1 : (cp-s));
-        memcpy(var, s, n);
-        var[n] = '\0';
-        apr_cpystrn(val, cp+1, sizeof(val));
-        apr_table_set(r->subprocess_env, var, val);
-        rewritelog(r, 5, "setting env variable '%s' to '%s'", var, val);
-    }
-}
+            /* if someone used the PASSTHROUGH flag in per-dir
+             * context we just ignore it. It is only useful
+             * in per-server context
+             */
+            if (l > 12 && strncmp(r->filename, "passthrough:", 12) == 0) {
+                r->filename = apr_pstrdup(r->pool, r->filename+12);
+            }
 
-static void add_cookie(request_rec *r, char *s)
-{
-    char *var;
-    char *val;
-    char *domain;
-    char *expires;
-    char *path;
+            /* the filename must be either an absolute local path or an
+             * absolute local URL.
+             */
+            if (   *r->filename != '/'
+                && !ap_os_is_path_absolute(r->pool, r->filename)) {
+                return HTTP_BAD_REQUEST;
+            }
 
-    char *tok_cntx;
-    char *cookie;
+            /* Check for deadlooping:
+             * At this point we KNOW that at least one rewriting
+             * rule was applied, but when the resulting URL is
+             * the same as the initial URL, we are not allowed to
+             * use the following internal redirection stuff because
+             * this would lead to a deadloop.
+             */
+            if (ofilename != NULL && strcmp(r->filename, ofilename) == 0) {
+                rewritelog((r, 1, dconf->directory, "initial URL equal rewritten"
+                            " URL: %s [IGNORING REWRITE]", r->filename));
+                return OK;
+            }
 
-    if (s) {
-        var = apr_strtok(s, ":", &tok_cntx);
-        val = apr_strtok(NULL, ":", &tok_cntx);
-        domain = apr_strtok(NULL, ":", &tok_cntx);
-        /** the line below won't hit the token ever **/
-        expires = apr_strtok(NULL, ":", &tok_cntx);
-        if (expires) {
-            path = apr_strtok(NULL,":", &tok_cntx);
-        }
-        else {
-            path = NULL;
-        }
+            /* if there is a valid base-URL then substitute
+             * the per-dir prefix with this base-URL if the
+             * current filename still is inside this per-dir
+             * context. If not then treat the result as a
+             * plain URL
+             */
+            if (dconf->baseurl != NULL) {
+                rewritelog((r, 2, dconf->directory, "trying to replace prefix "
+                            "%s with %s", dconf->directory, dconf->baseurl));
 
-        if (var && val && domain) {
-            /* FIX: use cached time similar to how logging does it */
-            request_rec *rmain = r;
-            char *notename;
-            void *data;
-            while (rmain->main) {
-                rmain = rmain->main;
-            }
-
-            notename = apr_pstrcat(rmain->pool, var, "_rewrite", NULL);
-            apr_pool_userdata_get(&data, notename, rmain->pool);
-            if (data == NULL) {
-                cookie = apr_pstrcat(rmain->pool,
-                                     var, "=", val,
-                                     "; path=", (path)? path : "/",
-                                     "; domain=", domain,
-                                     (expires)? "; expires=" : NULL,
-                                     (expires)?
-                                     ap_ht_time(r->pool,
-                                                r->request_time +
-                                                apr_time_from_sec((60 *
-                                                               atol(expires))),
-                                                "%a, %d-%b-%Y %T GMT", 1)
-                                              : NULL,
-                                     NULL);
-                /*
-                 * XXX: should we add it to err_headers_out as well ?
-                 * if we do we need to be careful that only ONE gets sent out
-                 */
-                apr_table_add(rmain->err_headers_out, "Set-Cookie", cookie);
-                apr_pool_userdata_set("set", notename, NULL, rmain->pool);
-                rewritelog(rmain, 5, "setting cookie '%s'", cookie);
+                r->filename = subst_prefix_path(r, r->filename,
+                                                dconf->directory,
+                                                dconf->baseurl);
             }
             else {
-                rewritelog(rmain, 5, "skipping already set cookie '%s'", var);
+                /* if no explicit base-URL exists we assume
+                 * that the directory prefix is also a valid URL
+                 * for this webserver and only try to remove the
+                 * document_root if it is prefix
+                 */
+                if ((ccp = ap_document_root(r)) != NULL) {
+                    /* strip trailing slash */
+                    l = strlen(ccp);
+                    if (ccp[l-1] == '/') {
+                        --l;
+                    }
+                    if (!strncmp(r->filename, ccp, l) &&
+                        r->filename[l] == '/') {
+                        rewritelog((r, 2,dconf->directory, "strip document_root"
+                                    " prefix: %s -> %s", r->filename,
+                                    r->filename+l));
+
+                        r->filename = apr_pstrdup(r->pool, r->filename+l);
+                    }
+                }
             }
+
+            /* now initiate the internal redirect */
+            rewritelog((r, 1, dconf->directory, "internal redirect with %s "
+                        "[INTERNAL REDIRECT]", r->filename));
+            r->filename = apr_pstrcat(r->pool, "redirect:", r->filename, NULL);
+            r->handler = "redirect-handler";
+            return OK;
         }
     }
+    else {
+        rewritelog((r, 1, dconf->directory, "pass through %s", r->filename));
+        r->filename = ofilename;
+        return DECLINED;
+    }
 }
 
-
-/*
-**
-**  check that a subrequest won't cause infinite recursion
-**
-*/
-
-static int subreq_ok(request_rec *r)
-{
-    /*
-     * either not in a subrequest, or in a subrequest
-     * and URIs aren't NULL and sub/main URIs differ
-     */
-    return (r->main == NULL
-            || (r->main->uri != NULL
-                && r->uri != NULL
-                && strcmp(r->main->uri, r->uri) != 0));
-}
-
-
 /*
-**
-**  stat() for only the prefix of a path
-**
-*/
-
-static int prefix_stat(const char *path, apr_pool_t *pool)
+ * MIME-type hook
+ * [T=...,H=...] execution
+ */
+static int hook_mimetype(request_rec *r)
 {
-    const char *curpath = path;
-    const char *root;
-    const char *slash;
-    char *statpath;
-    apr_status_t rv;
+    const char *t;
 
-    rv = apr_filepath_root(&root, &curpath, APR_FILEPATH_TRUENAME, pool);
+    /* type */
+    t = apr_table_get(r->notes, REWRITE_FORCED_MIMETYPE_NOTEVAR);
+    if (t && *t) {
+        rewritelog((r, 1, NULL, "force filename %s to have MIME-type '%s'",
+                    r->filename, t));
 
-    if (rv != APR_SUCCESS) {
-        return 0;
+        ap_set_content_type(r, t);
     }
 
-    /* let's recognize slashes only, the mod_rewrite semantics are opaque
-     * enough.
-     */
-    if ((slash = ap_strchr_c(curpath, '/')) != NULL) {
-        rv = apr_filepath_merge(&statpath, root,
-                                apr_pstrndup(pool, curpath,
-                                             (apr_size_t)(slash - curpath)),
-                                APR_FILEPATH_NOTABOVEROOT |
-                                APR_FILEPATH_NOTRELATIVE, pool);
-    }
-    else {
-        rv = apr_filepath_merge(&statpath, root, curpath,
-                                APR_FILEPATH_NOTABOVEROOT |
-                                APR_FILEPATH_NOTRELATIVE, pool);
-    }
+    /* handler */
+    t = apr_table_get(r->notes, REWRITE_FORCED_HANDLER_NOTEVAR);
+    if (t && *t) {
+        rewritelog((r, 1, NULL, "force filename %s to have the "
+                    "Content-handler '%s'", r->filename, t));
 
-    if (rv == APR_SUCCESS) {
-        apr_finfo_t sb;
-        
-        if (apr_stat(&sb, statpath, APR_FINFO_MIN, pool) == APR_SUCCESS) {
-            return 1;
-        }
+        r->handler = t;
     }
 
-    return 0;
+    return OK;
 }
 
 
 /*
-**
-**  Lexicographic Compare
-**
-*/
-
-static int compare_lexicography(char *cpNum1, char *cpNum2)
+ * "content" handler for internal redirects
+ */
+static int handler_redirect(request_rec *r)
 {
-    int i;
-    int n1, n2;
-
-    n1 = strlen(cpNum1);
-    n2 = strlen(cpNum2);
-    if (n1 > n2) {
-        return 1;
-    }
-    if (n1 < n2) {
-        return -1;
-    }
-    for (i = 0; i < n1; i++) {
-        if (cpNum1[i] > cpNum2[i]) {
-            return 1;
-        }
-        if (cpNum1[i] < cpNum2[i]) {
-            return -1;
-        }
+    if (strcmp(r->handler, "redirect-handler")) {
+        return DECLINED;
     }
-    return 0;
-}
-
-/*
-**
-**  Bracketed expression handling
-**  s points after the opening bracket
-**
-*/
-
-static char *find_closing_bracket(char *s, int left, int right)
-{
-    int depth;
 
-    for (depth = 1; *s; ++s) {
-        if (*s == right && --depth == 0) {
-            return s;
-        }
-        else if (*s == left) {
-            ++depth;
-        }
+    /* just make sure that we are really meant! */
+    if (strncmp(r->filename, "redirect:", 9) != 0) {
+        return DECLINED;
     }
-    return NULL;
-}
 
-static char *find_char_in_brackets(char *s, int c, int left, int right)
-{
-    int depth;
+    /* now do the internal redirect */
+    ap_internal_redirect(apr_pstrcat(r->pool, r->filename+9,
+                                     r->args ? "?" : NULL, r->args, NULL), r);
 
-    for (depth = 1; *s; ++s) {
-        if (*s == c && depth == 1) {
-            return s;
-        }
-        else if (*s == right && --depth == 0) {
-            return NULL;
-        }
-        else if (*s == left) {
-            ++depth;
-        }
-    }
-    return NULL;
+    /* and return gracefully */
+    return OK;
 }
 
+
 /*
-**
-** Module paraphernalia
-**
-*/
+ * +-------------------------------------------------------+
+ * |                                                       |
+ * |                Module paraphernalia
+ * |                                                       |
+ * +-------------------------------------------------------+
+ */
+
+#ifdef REWRITELOG_DISABLED
+static const char *fake_rewritelog(cmd_parms *cmd, void *dummy, const char *a1)
+{
+    return "RewriteLog and RewriteLogLevel are not supported by this build "
+           "of mod_rewrite because it was compiled using the "
+           "-DREWRITELOG_DISABLED compiler option. You have to recompile "
+           "mod_rewrite WITHOUT this option in order to use the rewrite log.";
+}
+#endif
 
-    /* the apr_table_t of commands we provide */
 static const command_rec command_table[] = {
     AP_INIT_FLAG(    "RewriteEngine",   cmd_rewriteengine,  NULL, OR_FILEINFO,
                      "On or Off to enable or disable (default) the whole "
                      "rewriting engine"),
     AP_INIT_ITERATE( "RewriteOptions",  cmd_rewriteoptions,  NULL, OR_FILEINFO,
                      "List of option strings to set"),
