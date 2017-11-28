 
     qe->aq_e_aiocb.aio_offset =  request->offset;
 
     qe->aq_e_aiocb.aio_buf =  request->buf;
 
     /* Account */
-    strategy->aq.aq_numpending++;
+    ++ strategy->aq.aq_numpending;
 
     /* Initiate aio */
     if (aio_read(&qe->aq_e_aiocb) < 0) {
         fatalf("Aiee! aio_read() returned error (%d)  FIXME and wrap file_read !\n", errno);
         debugs(79, 1, "WARNING: aio_read() returned error: " << xstrerror());
         /* fall back to blocking method */
