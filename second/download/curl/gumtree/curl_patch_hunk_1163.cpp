           while(val >= 10.0) {
             val /= 10;
             maxprec--;
           }
 
           if(prec > (long)maxprec)
-            prec = maxprec-1;
+            prec = (long)maxprec-1;
           /* RECURSIVE USAGE */
           len = curl_msnprintf(fptr, left, ".%ld", prec);
           fptr += len;
         }
         if(p->flags & FLAGS_LONG)
           *fptr++ = 'l';
