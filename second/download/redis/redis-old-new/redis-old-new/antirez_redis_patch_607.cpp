@@ -1167,7 +1167,7 @@ void showLatencyDistSamples(struct distsamples *samples, long long tot) {
 /* Show the legend: different buckets values and colors meaning, so
  * that the spectrum is more easily readable. */
 void showLatencyDistLegend(void) {
-    printf(". - *            0.01 0.125 0.5  milliseconds\n");
+    printf(". - * #          .01 .125 .25 .5 milliseconds\n");
     printf("1,2,3,...,9      from 1 to 9     milliseconds\n");
     printf("A,B,C,D,E        10,20,30,40,50  milliseconds\n");
     printf("F,G,H,I,J        .1,.2,.3,.4,.5       seconds\n");