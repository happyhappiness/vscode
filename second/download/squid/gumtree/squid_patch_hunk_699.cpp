         data = data->next;
     }
 
     return 0;
 }
 
-wordlist *
-ACLTimeData::dump()
+SBufList
+ACLTimeData::dump() const
 {
-    wordlist *W = NULL;
-    char buf[128];
-    ACLTimeData *t = this;
+    SBufList sl;
+    const ACLTimeData *t = this;
 
     while (t != NULL) {
-        snprintf(buf, sizeof(buf), "%c%c%c%c%c%c%c %02d:%02d-%02d:%02d",
+        SBuf s;
+        s.Printf("%c%c%c%c%c%c%c %02d:%02d-%02d:%02d",
                  t->weekbits & ACL_SUNDAY ? 'S' : '-',
                  t->weekbits & ACL_MONDAY ? 'M' : '-',
                  t->weekbits & ACL_TUESDAY ? 'T' : '-',
                  t->weekbits & ACL_WEDNESDAY ? 'W' : '-',
                  t->weekbits & ACL_THURSDAY ? 'H' : '-',
                  t->weekbits & ACL_FRIDAY ? 'F' : '-',
                  t->weekbits & ACL_SATURDAY ? 'A' : '-',
                  t->start / 60, t->start % 60, t->stop / 60, t->stop % 60);
-        wordlistAdd(&W, buf);
+        sl.push_back(s);
         t = t->next;
     }
 
-    return W;
+    return sl;
 }
 
 void
 ACLTimeData::parse()
 {
     ACLTimeData **Tail;
