int init_fifo(void)
{
 struct stat st;
 const char *fifo = "hiper.fifo";
 int socket;

 if (lstat (fifo, &st) == 0) {
  if ((st.st_mode & S_IFMT) == S_IFREG) {
   errno = EEXIST;
   perror("lstat");
   exit (1);
  }
 }

 unlink (fifo);
 if (mkfifo (fifo, 0600) == -1) {
  perror("mkfifo");
  exit (1);
 }

 socket = open (fifo, O_RDWR | O_NONBLOCK, 0);

 if (socket == -1) {
  perror("open");
  exit (1);
 }
 MSG_OUT("Now, pipe some URL's into > %s\n", fifo);

 return socket;

}