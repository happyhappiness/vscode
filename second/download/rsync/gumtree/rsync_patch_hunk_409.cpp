 		return;
 	}
 
 	t = time(NULL);
 
 	if (last_io && io_timeout && (t-last_io)>io_timeout) {
-		fprintf(FERROR,"read timeout after %d second - exiting\n", 
+		rprintf(FERROR,"read timeout after %d second - exiting\n", 
 			(int)(t-last_io));
 		exit_cleanup(1);
 	}
 }
 
 static int readfd(int fd,char *buffer,int N)
