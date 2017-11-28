     if (!ranges.empty())
         fatal("ACLIntRange::clone: attempt to clone used ACL");
 
     return new ACLIntRange (*this);
 }
 
-ACLIntRange::~ACLIntRange ()
+ACLIntRange::~ACLIntRange()
 {}
 
-wordlist *
-ACLIntRange::dump ()
+SBufList
+ACLIntRange::dump() const
 {
-    wordlist *W = NULL;
-    char buf[32];
+    SBufList sl;
     CbDataListIterator<RangeType> iter(ranges);
 
     while (!iter.end()) {
+        SBuf sb;
         const RangeType & element = iter.next();
 
         if (element.size() == 1)
-            snprintf(buf, sizeof(buf), "%d", element.start);
+            sb.Printf("%d", element.start);
         else
-            snprintf(buf, sizeof(buf), "%d-%d", element.start, element.end-1);
+            sb.Printf("%d-%d", element.start, element.end-1);
 
-        wordlistAdd(&W, buf);
+        sl.push_back(sb);
     }
 
-    return W;
+    return sl;
 }
 
