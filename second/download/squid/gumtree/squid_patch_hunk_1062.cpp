 fatal(const char *message)
 {
     /* suppress secondary errors from the dying */
     shutting_down = 1;
 
     releaseServerSockets();
-    /* check for store_dirs_rebuilding because fatal() is often
-     * used in early initialization phases, long before we ever
-     * get to the store log. */
 
     /* XXX: this should be turned into a callback-on-fatal, or
      * a mandatory-shutdown-event or something like that.
      * - RBC 20060819
      */
 
