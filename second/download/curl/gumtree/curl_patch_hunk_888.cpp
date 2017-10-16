                 size_t buflen)      /* size of buffer to store password in */
 {
   ssize_t nread;
   bool disabled;
   int fd = open("/dev/tty", O_RDONLY);
   if(-1 == fd)
-    fd = 1; /* use stdin if the tty couldn't be used */
+    fd = STDIN_FILENO; /* use stdin if the tty couldn't be used */
 
   disabled = ttyecho(FALSE, fd); /* disable terminal echo */
 
   fputs(prompt, stderr);
   nread = read(fd, password, buflen);
   if(nread > 0)
