@@ -243,10 +243,14 @@ static int completeLine(int fd, const char *prompt, char *buf, size_t buflen, si
                     if (i == lc.len) beep();
                     break;
                 case 27: /* escape */
+                    /* Re-show original buffer */
+                    if (i < lc.len) {
+                        refreshLine(fd,prompt,buf,*len,*pos,cols);
+                    }
                     stop = 1;
                     break;
                 default:
-                    /* update buffer and return */
+                    /* Update buffer and return */
                     if (i < lc.len) {
                         nwritten = snprintf(buf,buflen,"%s",lc.cvec[i]);
                         *len = *pos = nwritten;