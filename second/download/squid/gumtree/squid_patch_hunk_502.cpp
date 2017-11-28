                         0,
                         NULL);
                     if (ErrorMessage[strlen(ErrorMessage) - 1] == '\n')
                         ErrorMessage[strlen(ErrorMessage) - 1] = '\0';
                     if (ErrorMessage[strlen(ErrorMessage) - 1] == '\r')
                         ErrorMessage[strlen(ErrorMessage) - 1] = '\0';
-                    SEND2("NA %s", ErrorMessage);
+                    SEND_ERR(ErrorMessage); // TODO update to new syntax
                     LocalFree(ErrorMessage);
                     return 1;
                 default:
-                    SEND("NA Unknown Error");
+                    SEND_ERR("message=\"Unknown Error\"");
                     return 1;
                 }
             }
             /* let's lowercase them for our convenience */
-            SEND3("AF %s\\%s", lc(domain), lc(user));
+            lc(domain);
+            lc(user);
+            fprintf(stdout, "OK user=\"%s\\%s\"", domain, user);
             return 1;
+        }
         default:
-            helperfail("unknown authentication packet type");
+            helperfail("message=\"unknown authentication packet type\"");
             return 1;
         }
         return 1;
     } else {	/* not an auth-request */
-        helperfail("illegal request received");
+        helperfail("message=\"illegal request received\"");
         fprintf(stderr, "Illegal request received: '%s'\n", buf);
         return 1;
     }
-    helperfail("detected protocol error");
+    helperfail("message=\"detected protocol error\"");
     return 1;
     /********* END ********/
 }
 
 int
 main(int argc, char *argv[])
