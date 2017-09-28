     }
 
     if (distance < 0) {
         addReplyError(c,"radius cannot be negative");
         return -1;
     }
-    
+
     double to_meters = extractUnitOrReply(c,argv[1]);
     if (to_meters < 0) {
         return -1;
     }
 
     if (conversion) *conversion = to_meters;
