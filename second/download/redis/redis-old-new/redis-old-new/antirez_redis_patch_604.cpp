@@ -1122,14 +1122,9 @@ static void latencyMode(void) {
 #define LATENCY_DIST_MAX_GRAY 255
 #define LATENCY_DIST_GRAYS (LATENCY_DIST_MAX_GRAY-LATENCY_DIST_MIN_GRAY+1)
 
-/* Gray palette. Currently not used.
- * int spectrum_palette_size = 24;
-* int spectrum_palette[] = {0, 233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};
-*/
-
-/* Color palette from https://github.com/draios/sysdig */
-int spectrum_palette[] = {0, 22, 28, 64, 34, 2, 76, 46, 118, 154, 191, 227, 226, 11, 220, 209, 208, 202, 197, 9, 1};
-int spectrum_palette_size = 21;
+/* Gray palette. */
+int spectrum_palette_size = 24;
+int spectrum_palette[] = {0, 233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255};
 
 /* Structure to store samples distribution. */
 struct distsamples {
@@ -1173,12 +1168,19 @@ void showLatencyDistSamples(struct distsamples *samples, long long tot) {
 /* Show the legend: different buckets values and colors meaning, so
  * that the spectrum is more easily readable. */
 void showLatencyDistLegend(void) {
+    int j;
+
     printf("---------------------------------------------\n");
     printf(". - * #          .01 .125 .25 .5 milliseconds\n");
     printf("1,2,3,...,9      from 1 to 9     milliseconds\n");
     printf("A,B,C,D,E        10,20,30,40,50  milliseconds\n");
     printf("F,G,H,I,J        .1,.2,.3,.4,.5       seconds\n");
     printf("K,L,M,N,O,P,Q,?  1,2,4,8,16,30,60,>60 seconds\n");
+    printf("From 0 to 100%%: ");
+    for (j = 0; j < spectrum_palette_size; j++) {
+        printf("\033[48;5;%dm ", spectrum_palette[j]);
+    }
+    printf("\033[0m\n");
     printf("---------------------------------------------\n");
 }
 