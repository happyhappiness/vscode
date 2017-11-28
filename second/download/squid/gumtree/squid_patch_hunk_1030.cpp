                           );
     devpoll_update.cur = -1;
     devpoll_update.size = DEVPOLL_UPDATESIZE;
 
     /* attempt to open /dev/poll device */
     devpoll_fd = open("/dev/poll", O_RDWR);
-    if (devpoll_fd < 0)
-        fatalf("comm_select_init: can't open /dev/poll: %s\n", xstrerror());
+    if (devpoll_fd < 0) {
+        int xerrno = errno;
+        fatalf("comm_select_init: can't open /dev/poll: %s\n", xstrerr(xerrno));
+    }
 
     fd_open(devpoll_fd, FD_UNKNOWN, "devpoll ctl");
 
     commDevPollRegisterWithCacheManager();
 }
 
