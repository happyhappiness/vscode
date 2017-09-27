 	if (bar != NULL)
 	    printf("%s %s\n", hoststring, bar + 1);
 	else
 	    puts(hoststring);
     }
 
-#ifdef WIN32
+#if defined(WIN32) || defined(NETWARE)
      WSACleanup();
 #endif
 
     if (statfile != NULL) {
 	FILE *fp;
 	fp = fopen(statfile, "w");
