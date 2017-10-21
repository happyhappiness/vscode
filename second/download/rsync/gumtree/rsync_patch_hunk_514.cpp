 		else
 			read_buffer = (char *)realloc(read_buffer,read_buffer_size);
 		if (!read_buffer) out_of_memory("read check");      
 		read_buffer_p = read_buffer;      
 	}
 
-	n = read(f,read_buffer+read_buffer_len,n);
+	n = read_unbuffered(f,read_buffer+read_buffer_len,n);
 	if (n > 0) {
 		read_buffer_len += n;
 	}
 }
 
-static time_t last_io;
-
-
-static void check_timeout(void)
-{
-	time_t t;
-	
-	if (!io_timeout) return;
-
-	if (!last_io) {
-		last_io = time(NULL);
-		return;
-	}
-
-	t = time(NULL);
-
-	if (last_io && io_timeout && (t-last_io)>io_timeout) {
-		rprintf(FERROR,"read timeout after %d second - exiting\n", 
-			(int)(t-last_io));
-		exit_cleanup(1);
-	}
-}
-
 static int readfd(int fd,char *buffer,int N)
 {
 	int  ret;
 	int total=0;  
 	struct timeval tv;
 	
