  */
 void
 see_deflate_token(char *buf, int len)
 {
     int r;
 
-    rx_strm.next_in = buf;
+    rx_strm.next_in = (Bytef *)buf;
     rx_strm.avail_in = len;
     r = inflateIncomp(&rx_strm);
     if (r != Z_OK) {
 	fprintf(FERROR, "inflateIncomp returned %d\n", r);
 	exit_cleanup(1);
     }
