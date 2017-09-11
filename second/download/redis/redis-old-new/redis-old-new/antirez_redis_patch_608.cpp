@@ -44,6 +44,7 @@
 #include <assert.h>
 #include <fcntl.h>
 #include <limits.h>
+#include <math.h>
 
 #include "hiredis.h"
 #include "sds.h"
@@ -76,6 +77,7 @@ static struct config {
     int monitor_mode;
     int pubsub_mode;
     int latency_mode;
+    int latency_dist_mode;
     int latency_history;
     int cluster_mode;
     int cluster_reissue_command;
@@ -770,6 +772,8 @@ static int parseOptions(int argc, char **argv) {
             config.output = OUTPUT_CSV;
         } else if (!strcmp(argv[i],"--latency")) {
             config.latency_mode = 1;
+        } else if (!strcmp(argv[i],"--latency-dist")) {
+            config.latency_dist_mode = 1;
         } else if (!strcmp(argv[i],"--latency-history")) {
             config.latency_mode = 1;
             config.latency_history = 1;
@@ -862,6 +866,8 @@ static void usage(void) {
 "  --latency          Enter a special mode continuously sampling latency.\n"
 "  --latency-history  Like --latency but tracking latency changes over time.\n"
 "                     Default time interval is 15 sec. Change it using -i.\n"
+"  --latency-dist     Shows latency as a spectrum, requires xterm 256 colors.\n"
+"                     Default time interval is 1 sec. Change it using -i.\n"
 "  --slave            Simulate a slave showing commands received from the master.\n"
 "  --rdb <filename>   Transfer an RDB dump from remote server to local file.\n"
 "  --pipe             Transfer raw Redis protocol from stdin to server.\n"
@@ -1108,6 +1114,146 @@ static void latencyMode(void) {
 }
 
 /*------------------------------------------------------------------------------
+ * Latency distribution mode -- requires 256 colors xterm
+ *--------------------------------------------------------------------------- */
+
+#define LATENCY_DIST_DEFAULT_INTERVAL 1000 /* milliseconds. */
+#define LATENCY_DIST_MIN_GRAY 233 /* Less than that is too hard to see gray. */
+#define LATENCY_DIST_MAX_GRAY 255
+#define LATENCY_DIST_GRAYS (LATENCY_DIST_MAX_GRAY-LATENCY_DIST_MIN_GRAY+1)
+
+/* Structure to store samples distribution. */
+struct distsamples {
+    long long max;   /* Max latency to fit into this interval (usec). */
+    long long count; /* Number of samples in this interval. */
+    int character;   /* Associated character in visualization. */
+};
+
+/* Helper function for latencyDistMode(). Performs the spectrum visualization
+ * of the collected samples targeting an xterm 256 terminal.
+ *
+ * Takes an array of distsamples structures, ordered from smaller to bigger
+ * 'max' value. Last sample max must be 0, to mean that it olds all the
+ * samples greater than the previous one, and is also the stop sentinel.
+ *
+ * "tot' is the total number of samples in the different buckets, so it
+ * is the SUM(samples[i].conut) for i to 0 up to the max sample.
+ *
+ * As a side effect the function sets all the buckets count to 0. */
+void showLatencyDistSamples(struct distsamples *samples, long long tot) {
+    int j;
+
+    /* We convert samples into a number between 0 and DIST_GRAYS,
+     * proportional to the percentage a given bucket represents.
+     * This way intensity of the different parts of the spectrum
+     * don't change relative to the number of requests, which avoids to
+     * pollute the visualization with non-latency related info. */
+    printf("\033[38;5;0m"); /* Set foreground color to black. */
+    for (j = 0; ; j++) {
+        float color = (float) samples[j].count / tot * LATENCY_DIST_GRAYS;
+        color = ceil(color) + (LATENCY_DIST_MIN_GRAY-1);
+        if (color == LATENCY_DIST_MIN_GRAY-1) {
+            printf("\033[48;5;0m ");
+        } else {
+            printf("\033[48;5;%dm%c", (int)color, samples[j].character);
+        }
+        samples[j].count = 0;
+        if (samples[j].max == 0) break; /* Last sample. */
+    }
+    printf("\033[0m\n");
+    fflush(stdout);
+}
+
+/* Show the legend: different buckets values and colors meaning, so
+ * that the spectrum is more easily readable. */
+void showLatencyDistLegend(void) {
+    printf(". - *            0.01 0.125 0.5  milliseconds\n");
+    printf("1,2,3,...,9      from 1 to 9     milliseconds\n");
+    printf("A,B,C,D,E        10,20,30,40,50  milliseconds\n");
+    printf("F,G,H,I,J        .1,.2,.3,.4,.5       seconds\n");
+    printf("K,L,M,N,O,P,Q,?  1,2,4,8,16,30,60,>60 seconds\n");
+    printf("---------------------------------------------\n");
+}
+
+static void latencyDistMode(void) {
+    redisReply *reply;
+    long long start, latency, count = 0;
+    long long history_interval =
+        config.interval ? config.interval/1000 :
+                          LATENCY_DIST_DEFAULT_INTERVAL;
+    long long history_start = ustime();
+    int j, outputs = 0;
+
+    struct distsamples samples[] = {
+        /* We use a mostly logarithmic scale, with certain linear intervals
+         * which are more interesting than others, like 1-10 milliseconds
+         * range. */
+        {10,0,'.'},         /* 0.01 ms */
+        {125,0,'-'},        /* 0.125 ms */
+        {250,0,'*'},        /* 0.25 ms */
+        {500,0,'#'},        /* 0.5 ms */
+        {1000,0,'1'},       /* 1 ms */
+        {2000,0,'2'},       /* 2 ms */
+        {3000,0,'3'},       /* 3 ms */
+        {4000,0,'4'},       /* 4 ms */
+        {5000,0,'5'},       /* 5 ms */
+        {6000,0,'6'},       /* 6 ms */
+        {7000,0,'7'},       /* 7 ms */
+        {8000,0,'8'},       /* 8 ms */
+        {9000,0,'9'},       /* 9 ms */
+        {10000,0,'A'},      /* 10 ms */
+        {20000,0,'B'},      /* 20 ms */
+        {30000,0,'C'},      /* 30 ms */
+        {40000,0,'D'},      /* 40 ms */
+        {50000,0,'E'},      /* 50 ms */
+        {100000,0,'F'},     /* 0.1 s */
+        {200000,0,'G'},     /* 0.2 s */
+        {300000,0,'H'},     /* 0.3 s */
+        {400000,0,'I'},     /* 0.4 s */
+        {500000,0,'J'},     /* 0.5 s */
+        {1000000,0,'K'},    /* 1 s */
+        {2000000,0,'L'},    /* 2 s */
+        {4000000,0,'M'},    /* 4 s */
+        {8000000,0,'N'},    /* 8 s */
+        {16000000,0,'O'},   /* 16 s */
+        {30000000,0,'P'},   /* 30 s */
+        {60000000,0,'Q'},   /* 1 minute */
+        {0,0,'?'},          /* > 1 minute */
+    };
+
+    if (!context) exit(1);
+    while(1) {
+        start = ustime();
+        reply = redisCommand(context,"PING");
+        if (reply == NULL) {
+            fprintf(stderr,"\nI/O error\n");
+            exit(1);
+        }
+        latency = ustime()-start;
+        freeReplyObject(reply);
+        count++;
+
+        /* Populate the relevant bucket. */
+        for (j = 0; ; j++) {
+            if (samples[j].max == 0 || latency <= samples[j].max) {
+                samples[j].count++;
+                break;
+            }
+        }
+
+        /* From time to time show the spectrum. */
+        if (count && (ustime()-history_start)/1000 > history_interval) {
+            if ((outputs++ % 20) == 0)
+                showLatencyDistLegend();
+            showLatencyDistSamples(samples,count);
+            history_start = ustime();
+            count = 0;
+        }
+        usleep(LATENCY_SAMPLE_RATE * 1000);
+    }
+}
+
+/*------------------------------------------------------------------------------
  * Slave mode
  *--------------------------------------------------------------------------- */
 
@@ -1923,6 +2069,7 @@ int main(int argc, char **argv) {
     config.monitor_mode = 0;
     config.pubsub_mode = 0;
     config.latency_mode = 0;
+    config.latency_dist_mode = 0;
     config.latency_history = 0;
     config.cluster_mode = 0;
     config.slave_mode = 0;
@@ -1957,6 +2104,12 @@ int main(int argc, char **argv) {
         latencyMode();
     }
 
+    /* Latency distribution mode */
+    if (config.latency_dist_mode) {
+        if (cliConnect(0) == REDIS_ERR) exit(1);
+        latencyDistMode();
+    }
+
     /* Slave mode */
     if (config.slave_mode) {
         if (cliConnect(0) == REDIS_ERR) exit(1);