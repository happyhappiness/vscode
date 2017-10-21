 
 static int write_sparse(int f,char *buf,size_t len)
 {
 	size_t l1=0, l2=0;
 	int ret;
 
-	for (l1=0;l1<len && buf[l1]==0;l1++) ;
-	for (l2=0;l2<(len-l1) && buf[len-(l2+1)]==0;l2++) ;
+	for (l1 = 0; l1 < len && buf[l1] == 0; l1++) {}
+	for (l2 = 0; l2 < len-l1 && buf[len-(l2+1)] == 0; l2++) {}
 
 	last_byte = buf[len-1];
 
 	if (l1 == len || l2 > 0)
 		last_sparse=1;
 
 	if (l1 > 0) {
-		do_lseek(f,l1,SEEK_CUR);  
+		do_lseek(f,l1,SEEK_CUR);
 	}
 
-	if (l1 == len) 
+	if (l1 == len)
 		return len;
 
 	ret = write(f, buf + l1, len - (l1+l2));
 	if (ret == -1 || ret == 0)
 		return ret;
-	else if (ret != (int) (len - (l1+l2))) 
+	else if (ret != (int) (len - (l1+l2)))
 		return (l1+ret);
 
 	if (l2 > 0)
 		do_lseek(f,l2,SEEK_CUR);
-	
+
 	return len;
 }
 
+
+static char *wf_writeBuf;
+static size_t wf_writeBufSize;
+static size_t wf_writeBufCnt;
+
+int flush_write_file(int f)
+{
+	int ret = 0;
+	char *bp = wf_writeBuf;
+
+	while (wf_writeBufCnt > 0) {
+		if ((ret = write(f, bp, wf_writeBufCnt)) < 0) {
+			if (errno == EINTR)
+				continue;
+			return ret;
+		}
+		wf_writeBufCnt -= ret;
+		bp += ret;
+	}
+	return ret;
+}
+
 /*
  * write_file does not allow incomplete writes.  It loops internally
  * until len bytes are written or errno is set.
  */
 int write_file(int f,char *buf,size_t len)
 {
 	int ret = 0;
 
-	while (len>0) {
+	while (len > 0) {
 		int r1;
 		if (sparse_files) {
 			int len1 = MIN(len, SPARSE_WRITE_SIZE);
 			r1 = write_sparse(f, buf, len1);
 		} else {
-			r1 = write(f, buf, len);
+			if (!wf_writeBuf) {
+				wf_writeBufSize = MAX_MAP_SIZE;
+				wf_writeBufCnt  = 0;
+				wf_writeBuf = new_array(char, MAX_MAP_SIZE);
+				if (!wf_writeBuf)
+					out_of_memory("write_file");
+			}
+			r1 = MIN(len, wf_writeBufSize - wf_writeBufCnt);
+			if (r1) {
+				memcpy(wf_writeBuf + wf_writeBufCnt, buf, r1);
+				wf_writeBufCnt += r1;
+			}
+			if (wf_writeBufCnt == wf_writeBufSize) {
+				if (flush_write_file(f) < 0)
+					return -1;
+				if (!r1 && len)
+					continue;
+			}
 		}
 		if (r1 <= 0) {
 			if (ret > 0) return ret;
 			return r1;
 		}
 		len -= r1;
