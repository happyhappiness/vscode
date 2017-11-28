 {
     nbufs = (int)(magic2 * 1.3);
     id = shmget((key_t) (ikey + 2),
                 nbufs * SHMBUF_BLKSZ, 0600 | IPC_CREAT);
 
     if (id < 0) {
-        debugs(50, 0, "storeDiskdInit: shmget: " << xstrerror());
+        debugs(50, DBG_CRITICAL, "storeDiskdInit: shmget: " << xstrerror());
         fatal("shmget failed");
     }
 
     buf = (char *)shmat(id, NULL, 0);
 
     if (buf == (void *) -1) {
-        debugs(50, 0, "storeDiskdInit: shmat: " << xstrerror());
+        debugs(50, DBG_CRITICAL, "storeDiskdInit: shmat: " << xstrerror());
         fatal("shmat failed");
     }
 
     inuse_map = (char *)xcalloc((nbufs + 7) / 8, 1);
     diskd_stats.shmbuf_count += nbufs;
 
