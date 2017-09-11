@@ -765,6 +765,7 @@ static void latencyMode(void) {
         } else {
             if (latency < min) min = latency;
             if (latency > max) max = latency;
+            tot += latency;
             avg = (double) tot/count;
         }
         printf("\x1b[0G\x1b[2Kmin: %lld, max: %lld, avg: %.2f (%lld samples)",