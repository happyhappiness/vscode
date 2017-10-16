           left -= len;
         }
         if(prec >= 0) {
           /* RECURSIVE USAGE */
           len = curl_msnprintf(fptr, left, ".%ld", prec);
           fptr += len;
-          left -= len;
         }
         if(p->flags & FLAGS_LONG)
           *fptr++ = 'l';
 
         if(p->flags & FLAGS_FLOATE)
           *fptr++ = (char)((p->flags & FLAGS_UPPER) ? 'E':'e');
