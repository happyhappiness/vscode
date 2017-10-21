 	if (io_timeout)
 		last_io = time(NULL);
 	return total;
 }
 
 
-int read_int(int f)
+int32 read_int(int f)
 {
   int ret;
   char b[4];
   if ((ret=readfd(f,b,4)) != 4) {
     if (verbose > 1) 
-      fprintf(FERROR,"(%d) Error reading %d bytes : %s\n",
+      rprintf(FERROR,"(%d) Error reading %d bytes : %s\n",
 	      getpid(),4,ret==-1?strerror(errno):"EOF");
     exit_cleanup(1);
   }
   total_read += 4;
   return IVAL(b,0);
 }
