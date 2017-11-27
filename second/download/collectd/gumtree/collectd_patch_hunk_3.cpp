 #if COLLECT_PING
 		ping_update ();
 #endif
 #if COLLECT_SENSORS
 		sensors_update ();
 #endif
+#if COLLECT_SWAP
+		swap_update ();
+#endif
 #if COLLECT_TRAFFIC
 		traffic_update ();
 #endif
 
 #if DEBUG
 		fputs ("Sleeping for 10 seconds\n", stdout);
