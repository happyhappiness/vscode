 			msg, strerror(errno));
 		return 0;
 	}
 
 	return 1;
 }
-
-int write_or_whine(int fd, const void *buf, size_t count, const char *msg)
-{
-	if (write_in_full(fd, buf, count) < 0) {
-		fprintf(stderr, "%s: write error (%s)\n",
-			msg, strerror(errno));
-		return 0;
-	}
-
-	return 1;
-}
