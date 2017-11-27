 	return;
 }
 #endif /* HAVE_LIBKSTAT */
 
 void exit_usage (char *name)
 {
-	printf ("\nUsage: %s [OPTIONS]\n\n"
+	printf ("Usage: %s [OPTIONS]\n\n"
 			
 			"Available options:\n"
 			"  General:\n"
 			"    -d <dir>        Base directory to use\n"
 			"                    Default: /var/lib/collectd\n\n"
 
 #if COLLECT_CPU
 			"  CPU:\n"
-			"    -c <file>       RRD filename-template for\n"
-			"                    cpu accounting\n"
+			"    -c <file>       RRD filename-template for CPU accounting\n"
 			"                    Default: cpu%%d.rrd\n\n"
 #endif
 #if COLLECT_DISK
 			"  Diskstats:\n"
-			"    -k <file>       RRD filename-template for\n"
-			"                    disk accounting\n"
+			"    -k <file>       RRD filename-template for disk accounting\n"
 			"                    Default: disk-%%s.rrd\n"
-			"    -K <file>       RRD filename-template for\n"
-			"                    partition accounting\n"
+			"    -K <file>       RRD filename-template for partition accounting\n"
 			"                    Default: partition-%%s.rrd\n\n"
 #endif /* COLLECT_DISK */
 #if COLLECT_LOAD
 			"  Load:\n"
 			"    -l <file>       RRD file for load accounting\n"
 			"                    Default: load.rrd\n\n"
