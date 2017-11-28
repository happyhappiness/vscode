 
     /* Account */
     ++ strategy->aq.aq_numpending;
 
     /* Initiate aio */
     if (aio_read(&qe->aq_e_aiocb) < 0) {
-        fatalf("Aiee! aio_read() returned error (%d)  FIXME and wrap file_read !\n", errno);
-        debugs(79, DBG_IMPORTANT, "WARNING: aio_read() returned error: " << xstrerror());
+        int xerrno = errno;
+        fatalf("Aiee! aio_read() returned error (%d)  FIXME and wrap file_read !\n", xerrno);
+        debugs(79, DBG_IMPORTANT, "WARNING: aio_read() returned error: " << xstrerr(xerrno));
         /* fall back to blocking method */
         //        file_read(fd, request->buf, request->len, request->offset, callback, data);
     }
 
 }
 
