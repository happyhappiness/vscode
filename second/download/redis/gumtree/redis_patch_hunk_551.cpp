         if (latency > max_latency) {
             max_latency = latency;
             printf("Max latency so far: %lld microseconds.\n", max_latency);
         }
 
         double avg_us = (double)run_time/runs;
-        double avg_ns = avg_us * 10e3;
+        double avg_ns = avg_us * 1e3;
         if (force_cancel_loop || end > test_end) {
             printf("\n%lld total runs "
                 "(avg latency: "
                 "%.4f microseconds / %.2f nanoseconds per run).\n",
                 runs, avg_us, avg_ns);
             printf("Worst run took %.0fx longer than the average latency.\n",
