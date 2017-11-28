     if (!user)
         user = ::Format::QuoteUrlEncodeUsername(al->cache.rfc931);
 
     if (user && !*user)
         safe_free(user);
 
-    logfilePrintf(logfile, "%9ld.%03d %6d %s %s/%03d %" PRId64 " %s %s %s -/%s -\n",
+    logfilePrintf(logfile, "%9ld.%03d %6ld %s %s/%03d %" PRId64 " %s %s %s -/%s -\n",
                   (long int) current_time.tv_sec,
                   (int) current_time.tv_usec / 1000,
-                  al->icap.trTime,
+                  tvToMsec(al->icap.trTime),
                   client,
                   al->icap.outcome,
                   al->icap.resStatus,
                   al->icap.bytesRead,
                   Adaptation::Icap::ICAP::methodStr(al->icap.reqMethod),
                   al->icap.reqUri.termedBuf(),
