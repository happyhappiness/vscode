         return my_addr;
     }
 
     hep = gethostbyname(w);
 
     if ((!hep) || (hep->h_addrtype != AF_INET || !hep->h_addr_list[0])) {
-        /* XXX Should be echoing by h_errno the actual failure, no? 
+        /* XXX Should be echoing by h_errno the actual failure, no?
          * ap_log_error would be good here.  Better yet - APRize.
          */
         fprintf(stderr, "Cannot resolve host name %s --- exiting!\n", w);
         exit(1);
     }
 
