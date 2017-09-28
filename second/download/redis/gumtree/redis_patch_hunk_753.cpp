     char buf[128], *eptr;
     epos = ftello(fp);
     if (fgets(buf,sizeof(buf),fp) == NULL) {
         return 0;
     }
     if (buf[0] != prefix) {
-        ERROR("Expected prefix '%c', got: '%c'",buf[0],prefix);
+        ERROR("Expected prefix '%c', got: '%c'",prefix,buf[0]);
         return 0;
     }
     *target = strtol(buf+1,&eptr,10);
     return consumeNewline(eptr);
 }
 
