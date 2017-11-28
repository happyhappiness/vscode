         return;
 
     // TODO: bypass if possible
 
     if (entry->isEmpty()) {
         debugs(11,9, HERE << "creating ICAP error entry after ICAP failure");
-        ErrorState *err = errorCon(ERR_ICAP_FAILURE, HTTP_INTERNAL_SERVER_ERROR, request);
-        err->xerrno = errno;
+        ErrorState *err = new ErrorState(ERR_ICAP_FAILURE, HTTP_INTERNAL_SERVER_ERROR, request);
+        err->xerrno = ERR_DETAIL_ICAP_RESPMOD_EARLY;
         fwd->fail(err);
         fwd->dontRetry(true);
+    } else if (request) { // update logged info directly
+        request->detailError(ERR_ICAP_FAILURE, ERR_DETAIL_ICAP_RESPMOD_LATE);
     }
 
     abortTransaction("ICAP failure");
 }
 
+// adaptation service wants us to deny HTTP client access to this response
 void
-ServerStateData::adaptationAclCheckDone(Adaptation::ServiceGroupPointer group)
+ServerStateData::handleAdaptationBlocked(const Adaptation::Answer &answer)
+{
+    debugs(11,5, HERE << answer.ruleId);
+
+    if (abortOnBadEntry("entry went bad while ICAP aborted"))
+        return;
+
+    if (!entry->isEmpty()) { // too late to block (should not really happen)
+        if (request)
+            request->detailError(ERR_ICAP_FAILURE, ERR_DETAIL_RESPMOD_BLOCK_LATE);
+        abortTransaction("late adaptation block");
+        return;
+    }
+
+    debugs(11,7, HERE << "creating adaptation block response");
+
+    err_type page_id =
+        aclGetDenyInfoPage(&Config.denyInfoList, answer.ruleId.termedBuf(), 1);
+    if (page_id == ERR_NONE)
+        page_id = ERR_ACCESS_DENIED;
+
+    ErrorState *err = new ErrorState(page_id, HTTP_FORBIDDEN, request);
+    err->xerrno = ERR_DETAIL_RESPMOD_BLOCK_EARLY;
+    fwd->fail(err);
+    fwd->dontRetry(true);
+
+    abortTransaction("timely adaptation block");
+}
+
+void
+ServerStateData::noteAdaptationAclCheckDone(Adaptation::ServiceGroupPointer group)
 {
     adaptationAccessCheckPending = false;
 
     if (abortOnBadEntry("entry went bad while waiting for ICAP ACL check"))
         return;
 
