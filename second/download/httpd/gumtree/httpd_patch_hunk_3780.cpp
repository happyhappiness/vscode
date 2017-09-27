             FILE *out = fopen(csvperc, "w");
             if (!out) {
                 perror("Cannot open CSV output file");
                 exit(1);
             }
             fprintf(out, "" "Percentage served" "," "Time in ms" "\n");
-            for (i = 0; i < 100; i++) {
+            for (i = 0; i <= 100; i++) {
                 double t;
                 if (i == 0)
                     t = ap_double_ms(stats[0].time);
                 else if (i == 100)
                     t = ap_double_ms(stats[done - 1].time);
                 else
