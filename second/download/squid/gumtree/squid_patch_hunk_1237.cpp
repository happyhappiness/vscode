         // With the WNOHANG option, we could check whether WaitForAnyPid() was
         // aborted by a dying kid or a signal, but it is not required: The
         // next do/while loop will check again for any dying kids.
         int waitFlag = 0;
         if (masterSignaled())
             waitFlag = WNOHANG;
+        PidStatus status;
         pid = WaitForAnyPid(status, waitFlag);
 
         // check for a stopped kid
         Kid* kid = pid > 0 ? TheKids.find(pid) : NULL;
         if (kid) {
             kid->stop(status);
