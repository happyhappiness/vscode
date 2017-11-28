     StoreEntry *e;
 
     if (state->theSearch->isDone()) {
         if (UsingSmp())
             storeAppendPrintf(state->sentry, "} by kid%d\n\n", KidIdentifier);
         state->sentry->complete();
-        state->sentry->unlock();
-        cbdataFree(state);
+        state->sentry->unlock("statObjects+isDone");
+        delete state;
         return;
     } else if (EBIT_TEST(state->sentry->flags, ENTRY_ABORTED)) {
-        state->sentry->unlock();
-        cbdataFree(state);
+        state->sentry->unlock("statObjects+aborted");
+        delete state;
         return;
     } else if (state->sentry->checkDeferRead(-1)) {
         state->sentry->flush();
         eventAdd("statObjects", statObjects, state, 0.1, 1);
         return;
     }
