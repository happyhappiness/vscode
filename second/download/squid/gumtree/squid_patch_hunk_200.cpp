     unsigned short reason;
 
     switch (stuff->rr) {
     case RR_REQUEST:
         debugs(31, 3, "htcpBuildClrOpData: RR_REQUEST");
         reason = htons((unsigned short)stuff->reason);
-        xmemcpy(buf, &reason, 2);
+        memcpy(buf, &reason, 2);
         return htcpBuildSpecifier(buf + 2, buflen - 2, stuff) + 2;
     case RR_RESPONSE:
         break;
     default:
         fatal_dump("htcpBuildClrOpData: bad RR value");
     }
