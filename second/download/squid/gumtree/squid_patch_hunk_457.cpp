                 /* Again, we own this structure layout */
                 rep->header.putStr(HDR_X_ACCELERATOR_VARY, vary.termedBuf());
                 vary.clean();
             }
 
 #endif
-            pe->replaceHttpReply(rep);
+            pe->replaceHttpReply(rep, false); // no write until key is public
 
             pe->timestampsSet();
 
             pe->makePublic();
 
+            pe->startWriting(); // after makePublic()
+
             pe->complete();
 
             pe->unlock();
         }
 
         newkey = storeKeyPublicByRequest(mem_obj->request);
