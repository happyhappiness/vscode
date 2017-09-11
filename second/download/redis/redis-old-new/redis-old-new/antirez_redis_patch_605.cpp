@@ -1122,6 +1122,15 @@ static void latencyMode(void) {
 #define LATENCY_DIST_MAX_GRAY 255
 #define LATENCY_DIST_GRAYS (LATENCY_DIST_MAX_GRAY-LATENCY_DIST_MIN_GRAY+1)
 
+/* Gray palette. Currently not used.
+ * int spectrum_palette_size = 24;
+* int spectrum_palette[] = {0, 233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};
+*/
+
+/* Color palette from https://github.com/draios/sysdig */
+int spectrum_palette[] = {0, 22, 28, 64, 34, 2, 76, 46, 118, 154, 191, 227, 226, 11, 220, 209, 208, 202, 197, 9, 1};
+int spectrum_palette_size = 21;
+
 /* Structure to store samples distribution. */
 struct distsamples {
     long long max;   /* Max latency to fit into this interval (usec). */
@@ -1143,20 +1152,17 @@ struct distsamples {
 void showLatencyDistSamples(struct distsamples *samples, long long tot) {
     int j;
 
-    /* We convert samples into a number between 0 and DIST_GRAYS,
+     /* We convert samples into a index inside the palette
      * proportional to the percentage a given bucket represents.
      * This way intensity of the different parts of the spectrum
      * don't change relative to the number of requests, which avoids to
      * pollute the visualization with non-latency related info. */
     printf("\033[38;5;0m"); /* Set foreground color to black. */
     for (j = 0; ; j++) {
-        float color = (float) samples[j].count / tot * LATENCY_DIST_GRAYS;
-        color = ceil(color) + (LATENCY_DIST_MIN_GRAY-1);
-        if (color == LATENCY_DIST_MIN_GRAY-1) {
-            printf("\033[48;5;0m ");
-        } else {
-            printf("\033[48;5;%dm%c", (int)color, samples[j].character);
-        }
+        int coloridx =
+            ceil((float) samples[j].count / tot * (spectrum_palette_size-1));
+        int color = spectrum_palette[coloridx];
+        printf("\033[48;5;%dm%c", (int)color, samples[j].character);
         samples[j].count = 0;
         if (samples[j].max == 0) break; /* Last sample. */
     }