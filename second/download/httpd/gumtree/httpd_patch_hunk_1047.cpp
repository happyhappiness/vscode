 #define ap_min(a,b) ((a)<(b))?(a):(b)
 #define ap_max(a,b) ((a)>(b))?(a):(b)
 #define MAX_CONCURRENCY 20000
 
 /* --------------------- GLOBALS ---------------------------- */
 
-int verbosity = 0;		/* no verbosity by default */
-int posting = 0;		/* GET by default */
-int requests = 1;		/* Number of requests to make */
-int heartbeatres = 100;		/* How often do we say we're alive */
-int concurrency = 1;		/* Number of multiple requests to make */
-int percentile = 1;		/* Show percentile served */
-int confidence = 1;		/* Show confidence estimator and warnings */
-int tlimit = 0;			/* time limit in secs */
-int keepalive = 0;		/* try and do keepalive connections */
-char servername[1024];		/* name that server reports */
-char *hostname;			/* host name from URL */
-char *host_field;		/* value of "Host:" header field */
-char *path;                     /* path name */
-char postfile[1024];		/* name of file containing post data */
-char *postdata;			/* *buffer containing data from postfile */
-apr_size_t postlen = 0;		/* length of data to be POSTed */
-char content_type[1024];	/* content type to put in POST header */
-char *cookie,                   /* optional cookie line */
-     *auth,                     /* optional (basic/uuencoded) auhentication */
-     *hdrs;                     /* optional arbitrary headers */
-apr_port_t port;		/* port number */
-char proxyhost[1024];		/* proxy host name */
-int proxyport = 0;		/* proxy port */
+int verbosity = 0;      /* no verbosity by default */
+int posting = 0;        /* GET by default */
+int requests = 1;       /* Number of requests to make */
+int heartbeatres = 100; /* How often do we say we're alive */
+int concurrency = 1;    /* Number of multiple requests to make */
+int percentile = 1;     /* Show percentile served */
+int confidence = 1;     /* Show confidence estimator and warnings */
+int tlimit = 0;         /* time limit in secs */
+int keepalive = 0;      /* try and do keepalive connections */
+char servername[1024];  /* name that server reports */
+char *hostname;         /* host name from URL */
+char *host_field;       /* value of "Host:" header field */
+char *path;             /* path name */
+char postfile[1024];    /* name of file containing post data */
+char *postdata;         /* *buffer containing data from postfile */
+apr_size_t postlen = 0; /* length of data to be POSTed */
+char content_type[1024];/* content type to put in POST header */
+char *cookie,           /* optional cookie line */
+     *auth,             /* optional (basic/uuencoded) auhentication */
+     *hdrs;             /* optional arbitrary headers */
+apr_port_t port;        /* port number */
+char proxyhost[1024];   /* proxy host name */
+int proxyport = 0;      /* proxy port */
 char *connecthost;
 apr_port_t connectport;
-char *gnuplot;			/* GNUplot file */
-char *csvperc;			/* CSV Percentile file */
+char *gnuplot;          /* GNUplot file */
+char *csvperc;          /* CSV Percentile file */
 char url[1024];
 char * fullurl, * colonhost;
 int isproxy = 0;
 apr_interval_time_t aprtimeout = apr_time_from_sec(30);	/* timeout value */
  /*
   * XXX - this is now a per read/write transact type of value
   */
 
-int use_html = 0;		/* use html in the report */
+int use_html = 0;       /* use html in the report */
 const char *tablestring;
 const char *trstring;
 const char *tdstring;
 
-apr_size_t doclen = 0;		/* the length the document should be */
-long started = 0;		/* number of requests started, so no excess */
-long totalread = 0;		/* total number of bytes read */
-long totalbread = 0;		/* totoal amount of entity body read */
-long totalposted = 0;		/* total number of bytes posted, inc. headers */
-long done = 0;			/* number of requests we have done */
-long doneka = 0;		/* number of keep alive connections done */
-long good = 0, bad = 0;		/* number of good and bad requests */
-long epipe = 0;			/* number of broken pipe writes */
+apr_size_t doclen = 0;      /* the length the document should be */
+long started = 0;           /* number of requests started, so no excess */
+long totalread = 0;         /* total number of bytes read */
+long totalbread = 0;        /* totoal amount of entity body read */
+long totalposted = 0;       /* total number of bytes posted, inc. headers */
+long done = 0;              /* number of requests we have done */
+long doneka = 0;            /* number of keep alive connections done */
+long good = 0, bad = 0;     /* number of good and bad requests */
+long epipe = 0;             /* number of broken pipe writes */
 
 #ifdef USE_SSL
-int ssl = 0;
-SSL_CTX *ctx;
+int is_ssl;
+SSL_CTX *ssl_ctx;
+char *ssl_cipher = NULL;
+char *ssl_info = NULL;
 BIO *bio_out,*bio_err;
-static void write_request(struct connection * c);
 #endif
 
 /* store error cases */
 int err_length = 0, err_conn = 0, err_except = 0;
 int err_response = 0;
 
 apr_time_t start, endtime;
 
 /* global request (and its length) */
-char _request[512];
+char _request[2048];
 char *request = _request;
 apr_size_t reqlen;
 
 /* one global throw-away buffer to read stuff into */
 char buffer[8192];
 
 /* interesting percentiles */
 int percs[] = {50, 66, 75, 80, 90, 95, 98, 99, 100};
 
-struct connection *con;		/* connection array */
-struct data *stats;		/* date for each request */
+struct connection *con;     /* connection array */
+struct data *stats;         /* date for each request */
 apr_pool_t *cntxt;
 
 apr_pollset_t *readbits;
 
 apr_sockaddr_t *destsa;
 
 #ifdef NOT_ASCII
 apr_xlate_t *from_ascii, *to_ascii;
 #endif
 
+static void write_request(struct connection * c);
 static void close_connection(struct connection * c);
+
 /* --------------------------------------------------------- */
 
 /* simple little function to write an error string and exit */
 
 static void err(char *s)
 {
