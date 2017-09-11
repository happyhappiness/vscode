@@ -98,7 +98,7 @@ static struct config {
 } config;
 
 static volatile sig_atomic_t force_cancel_loop = 0;
-static void usage();
+static void usage(void);
 static void slaveMode(void);
 char *redisGitSHA1(void);
 char *redisGitDirty(void);
@@ -158,7 +158,7 @@ typedef struct {
 static helpEntry *helpEntries;
 static int helpEntriesLen;
 
-static sds cliVersion() {
+static sds cliVersion(void) {
     sds version;
     version = sdscatprintf(sdsempty(), "%s", REDIS_VERSION);
 
@@ -172,7 +172,7 @@ static sds cliVersion() {
     return version;
 }
 
-static void cliInitHelp() {
+static void cliInitHelp(void) {
     int commandslen = sizeof(commandHelp)/sizeof(struct commandHelp);
     int groupslen = sizeof(commandGroups)/sizeof(char*);
     int i, len, pos = 0;
@@ -211,7 +211,7 @@ static void cliOutputCommandHelp(struct commandHelp *help, int group) {
 }
 
 /* Print generic help. */
-static void cliOutputGenericHelp() {
+static void cliOutputGenericHelp(void) {
     sds version = cliVersion();
     printf(
         "redis-cli %s\r\n"
@@ -368,7 +368,7 @@ static int cliConnect(int force) {
     return REDIS_OK;
 }
 
-static void cliPrintContextError() {
+static void cliPrintContextError(void) {
     if (context == NULL) return;
     fprintf(stderr,"Error: %s\n",context->errstr);
 }
@@ -805,7 +805,7 @@ static sds readArgFromStdin(void) {
     return arg;
 }
 
-static void usage() {
+static void usage(void) {
     sds version = cliVersion();
     fprintf(stderr,
 "redis-cli %s\n"
@@ -874,7 +874,7 @@ static char **convertToSds(int count, char** args) {
 }
 
 #define LINE_BUFLEN 4096
-static void repl() {
+static void repl(void) {
     sds historyfile = NULL;
     int history = 0;
     char *line;
@@ -1677,7 +1677,7 @@ void bytesToHuman(char *s, long long n) {
     }
 }
 
-static void statMode() {
+static void statMode(void) {
     redisReply *reply;
     long aux, requests = 0;
     int i = 0;
@@ -1763,7 +1763,7 @@ static void statMode() {
  * Scan mode
  *--------------------------------------------------------------------------- */
 
-static void scanMode() {
+static void scanMode(void) {
     redisReply *reply;
     unsigned long long cur = 0;
 