             decrRefCount(keyobj);
         }
         dictReleaseIterator(di);
     }
 }
 
-#if defined(USE_JEMALLOC)
-void inputCatSds(void *result, const char *str) {
-    /* result is actually a (sds *), so re-cast it here */
-    sds *info = (sds *)result;
-    *info = sdscat(*info, str);
-}
-#endif
-
 void debugCommand(client *c) {
     if (c->argc == 1) {
         addReplyError(c,"You must specify a subcommand for DEBUG. Try DEBUG HELP for info.");
         return;
     }
 
