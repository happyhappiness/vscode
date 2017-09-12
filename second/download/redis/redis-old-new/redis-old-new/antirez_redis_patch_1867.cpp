@@ -71,6 +71,7 @@ static struct config {
     aeEventLoop *el;
     char *hostip;
     int hostport;
+    char *hostsocket;
     int keepalive;
     long long start;
     long long totlatency;
@@ -359,7 +360,11 @@ static client createClient(void) {
     client c = zmalloc(sizeof(struct _client));
     char err[ANET_ERR_LEN];
 
-    c->fd = anetTcpNonBlockConnect(err,config.hostip,config.hostport);
+    if (config.hostsocket == NULL)
+        c->fd = anetTcpNonBlockConnect(err,config.hostip,config.hostport);
+    else
+        c->fd = anetUnixNonBlockConnect(err,config.hostsocket);
+
     if (c->fd == ANET_ERR) {
         zfree(c);
         fprintf(stderr,"Connect: %s\n",err);
@@ -455,6 +460,9 @@ void parseOptions(int argc, char **argv) {
         } else if (!strcmp(argv[i],"-p") && !lastarg) {
             config.hostport = atoi(argv[i+1]);
             i++;
+        } else if (!strcmp(argv[i],"-s") && !lastarg) {
+            config.hostsocket = argv[i+1];
+            i++;
         } else if (!strcmp(argv[i],"-d") && !lastarg) {
             config.datasize = atoi(argv[i+1]);
             i++;
@@ -478,7 +486,8 @@ void parseOptions(int argc, char **argv) {
             printf("Wrong option '%s' or option argument missing\n\n",argv[i]);
             printf("Usage: redis-benchmark [-h <host>] [-p <port>] [-c <clients>] [-n <requests]> [-k <boolean>]\n\n");
             printf(" -h <hostname>      Server hostname (default 127.0.0.1)\n");
-            printf(" -p <hostname>      Server port (default 6379)\n");
+            printf(" -p <port>          Server port (default 6379)\n");
+            printf(" -s <socket>        Server socket (overrides host and port)\n");
             printf(" -c <clients>       Number of parallel connections (default 50)\n");
             printf(" -n <requests>      Total number of requests (default 10000)\n");
             printf(" -d <size>          Data size of SET/GET value in bytes (default 2)\n");
@@ -537,6 +546,7 @@ int main(int argc, char **argv) {
 
     config.hostip = "127.0.0.1";
     config.hostport = 6379;
+    config.hostsocket = NULL;
 
     parseOptions(argc,argv);
 