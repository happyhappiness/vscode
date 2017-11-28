     } else  if ( force == AF_INET || (force == AF_UNSPEC && IsIPv4()) ) {
 
         struct in_addr tmp;
         GetInAddr(tmp);
         inet_ntop(AF_INET, &tmp, buf, blen);
     } else {
-        debugs(14,0,"WARNING: Corrupt IP Address details OR required to display in unknown format (" <<
+        debugs(14, DBG_CRITICAL, "WARNING: Corrupt IP Address details OR required to display in unknown format (" <<
                force << "). accepted={" << AF_UNSPEC << "," << AF_INET << "," << AF_INET6 << "}");
         fprintf(stderr,"WARNING: Corrupt IP Address details OR required to display in unknown format (%d). accepted={%d,%d,%d} ",
                 force, AF_UNSPEC, AF_INET, AF_INET6);
         memcpy(buf,"dead:beef::\0", min(static_cast<unsigned int>(13),blen));
         assert(false);
     }
