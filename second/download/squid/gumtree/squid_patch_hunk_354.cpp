  *
  * NP: this should probably be made Async now.
  */
 void
 ACLChecklist::nonBlockingCheck(ACLCB * callback_, void *callback_data_)
 {
+    preCheck("slow rules");
     callback = callback_;
     callback_data = cbdataReference(callback_data_);
     matchNonBlocking();
 }
 
 allow_t const &
 ACLChecklist::fastCheck(const ACLList * list)
 {
     PROF_start(aclCheckFast);
-    currentAnswer(ACCESS_DUNNO);
-    matchAclList(list, true);
-    // assume ALLOWED on matches due to not having an acl_access object
-    if (finished())
-        currentAnswer(ACCESS_ALLOWED);
+
+    preCheck("fast ACLs");
+
+    // assume DENY/ALLOW on mis/matches due to not having acl_access object
+    if (matchAclList(list, true))
+        markFinished(ACCESS_ALLOWED, "all ACLs matched");
+    else if (!finished())
+        markFinished(ACCESS_DENIED, "ACL mismatched");
     PROF_stop(aclCheckFast);
     return currentAnswer();
 }
 
 /* Warning: do not cbdata lock this here - it
  * may be static or on the stack
  */
 allow_t const &
 ACLChecklist::fastCheck()
 {
     PROF_start(aclCheckFast);
-    currentAnswer(ACCESS_DUNNO);
 
+    preCheck("fast rules");
+
+    allow_t lastSeenKeyword = ACCESS_DUNNO;
     debugs(28, 5, "aclCheckFast: list: " << accessList);
     const acl_access *acl = cbdataReference(accessList);
     while (acl != NULL && cbdataReferenceValid(acl)) {
-        matchAclList(acl->aclList, true);
+        // on a match, finish
+        if (matchAclList(acl->aclList, true))
+            markFinished(acl->allow, "first matching rule won");
+
+        // if finished (on a match or in exceptional cases), stop
         if (finished()) {
-            currentAnswer(acl->allow);
-            PROF_stop(aclCheckFast);
             cbdataReferenceDone(acl);
+            PROF_stop(aclCheckFast);
             return currentAnswer();
         }
 
-        /*
-         * Reference the next access entry
-         */
+        // on a mismatch, try the next access rule
+        lastSeenKeyword = acl->allow;
         const acl_access *A = acl;
         acl = cbdataReference(acl->next);
         cbdataReferenceDone(A);
     }
 
-    debugs(28, 5, "aclCheckFast: no matches, returning: " << currentAnswer());
+    // There were no rules to match or no rules matched
+    calcImplicitAnswer(lastSeenKeyword);
     PROF_stop(aclCheckFast);
 
     return currentAnswer();
 }
 
+/// When no rules matched, the answer is the inversion of the last seen rule
+/// action (or ACCESS_DUNNO if the reversal is not possible). The caller
+/// should set lastSeenAction to ACCESS_DUNNO if there were no rules to see.
+void
+ACLChecklist::calcImplicitAnswer(const allow_t &lastSeenAction)
+{
+    allow_t implicitRuleAnswer = ACCESS_DUNNO;
+    if (lastSeenAction == ACCESS_DENIED) // reverse last seen "deny"
+        implicitRuleAnswer = ACCESS_ALLOWED;
+    else if (lastSeenAction == ACCESS_ALLOWED) // reverse last seen "allow"
+        implicitRuleAnswer = ACCESS_DENIED;
+    // else we saw no rules and will respond with ACCESS_DUNNO
+
+    debugs(28, 3, HERE << this << " NO match found, last action " <<
+           lastSeenAction << " so returning " << implicitRuleAnswer);
+    markFinished(implicitRuleAnswer, "implicit rule won");
+}
 
 bool
 ACLChecklist::checking() const
 {
     return checking_;
 }
