 	  strcat(formatbuf, "#");
 
 	fptr=&formatbuf[strlen(formatbuf)];
 
 	if(width >= 0) {
 	  /* RECURSIVE USAGE */
-	  fptr += curl_msprintf(fptr, "%ld", width);
+          len = curl_msnprintf(fptr, left, "%ld", width);
+          fptr += len;
+          left -= len;
 	}
 	if(prec >= 0) {
 	  /* RECURSIVE USAGE */
-	  fptr += curl_msprintf(fptr, ".%ld", prec);
+          len = curl_msnprintf(fptr, left, ".%ld", prec);
+          fptr += len;
+          left -= len;
 	}
 	if (p->flags & FLAGS_LONG)
-	  strcat(fptr, "l");
+          *fptr++ = 'l';
 
 	if (p->flags & FLAGS_FLOATE)
-	  strcat(fptr, p->flags&FLAGS_UPPER?"E":"e");
+          *fptr++ = p->flags&FLAGS_UPPER ? 'E':'e';
 	else if (p->flags & FLAGS_FLOATG)
-	  strcat(fptr, (p->flags & FLAGS_UPPER) ? "G" : "g");
+          *fptr++ = p->flags & FLAGS_UPPER ? 'G' : 'g';
 	else
-	  strcat(fptr, "f");
+          *fptr++ = 'f';
+
+        *fptr = 0; /* and a final zero termination */
 
 	/* NOTE NOTE NOTE!! Not all sprintf() implementations returns number
 	   of output characters */
-#if 0 /*SIZEOF_LONG_DOUBLE*/
-	if (p->flags & FLAGS_LONG)
-	  /* This is for support of the 'long double' type */
-	  (sprintf)(work, formatbuf, p->data.ldnum);
-	else
-#endif
-	  (sprintf)(work, formatbuf, p->data.dnum);
+        (sprintf)(work, formatbuf, p->data.dnum);
 
 	for(fptr=work; *fptr; fptr++)
 	  OUTCHAR(*fptr);
       }
       break;
 
