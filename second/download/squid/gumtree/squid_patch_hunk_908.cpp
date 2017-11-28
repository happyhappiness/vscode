                 reset_auth(req);
                 status = 403;	/* Forbiden, see comments in case isForward: */
             }
 
             /* this is a way to pass HTTP status to the Web server */
             if (statusStr)
-                printf("Status: %d %s", status, statusStr);	/* statusStr has '\n' */
+                printf("Status: %d %s", status, statusStr); /* statusStr has '\n' */
 
             break;
 
         case isHeaders:
             /* forward header field */
-            if (!strcmp(buf, "\r\n")) {		/* end of headers */
+            if (!strcmp(buf, "\r\n")) {     /* end of headers */
                 fputs("Content-Type: text/html\r\n", stdout);	/* add our type */
                 istate = isBodyStart;
             }
 
             if (strncasecmp(buf, "Content-Type:", 13))	/* filter out their type */
                 fputs(buf, stdout);
