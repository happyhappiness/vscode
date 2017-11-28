     if (list == NULL) {
         debugs(48, 3, HERE << "lookup for key {" << aKey << "} failed.");
         // failure notifications resume standby conn creation after fdUsageHigh
         notifyManager("pop failure");
         return Comm::ConnectionPointer();
     } else {
-        debugs(48, 3, HERE << "found " << hashKeyStr(&list->hash) <<
+        debugs(48, 3, "found " << hashKeyStr(list) <<
                (keepOpen ? " to use" : " to kill"));
     }
 
     /* may delete list */
     Comm::ConnectionPointer popped = list->findUseable(dest);
     if (!keepOpen && Comm::IsConnOpen(popped))
