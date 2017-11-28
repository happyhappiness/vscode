         if (checklist->keepMatching())
             checklist->markFinished(answer, "AuthenticateAcl exception");
         return -1; // other
     }
 }
 
-wordlist *
+SBufList
 ACLMaxUserIP::dump() const
 {
+    SBufList sl;
     if (!maximum)
-        return NULL;
-
-    wordlist *W = NULL;
-
-    char buf[128];
-
-    snprintf(buf, sizeof(buf), "%lu", (unsigned long int) maximum);
-
-    wordlistAdd(&W, buf);
-
-    return W;
+        return sl;
+    SBuf s;
+    s.Printf("%d", maximum);
+    sl.push_back(s);
+    return sl;
 }
+
