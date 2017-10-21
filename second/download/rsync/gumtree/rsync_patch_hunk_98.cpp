 	}
 	j++;
       } while (j<s->count && targets[j].t == t);
     }
 
     /* Trim off the first byte from the checksum */
-    s1 -= buf[offset];
-    s2 -= k * buf[offset];
+    map = map_ptr(buf,offset,k+1);
+    s1 -= map[0];
+    s2 -= k * map[0];
 
     /* Add on the next byte (if there is one) to the checksum */
     if (k < (len-offset)) {
-      s1 += buf[offset+k];
+      s1 += map[k];
       s2 += s1;
     } else {
       --k;
     }
 
-    if (verbose > 3) 
-      fprintf(stderr,"s2:s1 = %.4x%.4x sum=%.8x k=%d offset=%d took %x added %x\n",
-	      s2&0xffff, s1&0xffff, get_checksum1(buf+offset+1,k),
-	      k, (int)offset, buf[offset], buf[offset+k]);
   } while (++offset < end);
 
   matched(f,s,buf,len,len,-1);
 }
 
 
