fprintf (stderr,
"Error:\tApache has not been designed to serve pages while running\n"
"\tas root.  There are known race conditions that will allow any\n"
"\tlocal user to read any file on the system.  Should you still\n"
"\tdesire to serve pages as root then add -DBIG_SECURITY_HOLE to\n"
"\tthe EXTRA_CFLAGS line in your src/Configuration file and rebuild\n"
"\tthe server.  It is strongly suggested that you instead modify the\n"
"\tUser directive in your httpd.conf file to list a non-root user.\n");