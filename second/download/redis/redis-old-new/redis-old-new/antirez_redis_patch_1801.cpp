@@ -530,6 +530,10 @@ static int parseOptions(int argc, char **argv) {
             i++;
         } else if (!strcmp(argv[i],"--raw")) {
             config.raw_output = 1;
+        } else if (!strcmp(argv[i],"-d") && !lastarg) {
+            sdsfree(config.mb_delim);
+            config.mb_delim = sdsnew(argv[i+1]);
+            i++;
         } else if (!strcmp(argv[i],"-v") || !strcmp(argv[i], "--version")) {
             sds version = cliVersion();
             printf("redis-cli %s\n", version);
@@ -572,6 +576,7 @@ static void usage() {
 "  -r <repeat>      Execute specified command N times\n"
 "  -n <db>          Database number\n"
 "  -x               Read last argument from STDIN\n"
+"  -d <delimiter>   Multi-bulk delimiter in for raw formatting (default: \\n)\n"
 "  --raw            Use raw formatting for replies (default when STDOUT is not a tty)\n"
 "  --help           Output this help and exit\n"
 "  --version        Output version and exit\n"