 allow_t const &
 ACLChecklist::fastCheck()
 {
     PROF_start(aclCheckFast);
 
     preCheck("fast rules");
+    asyncCaller_ = false;
 
-    allow_t lastSeenKeyword = ACCESS_DUNNO;
     debugs(28, 5, "aclCheckFast: list: " << accessList);
-    const acl_access *acl = cbdataReference(accessList);
-    while (acl != NULL && cbdataReferenceValid(acl)) {
-        // on a match, finish
-        if (matchAclList(acl->aclList, true))
-            markFinished(acl->allow, "first matching rule won");
+    const Acl::Tree *acl = cbdataReference(accessList);
+    if (acl != NULL && cbdataReferenceValid(acl)) {
+        matchAndFinish(); // calls markFinished() on success
 
         // if finished (on a match or in exceptional cases), stop
         if (finished()) {
             cbdataReferenceDone(acl);
+            occupied_ = false;
             PROF_stop(aclCheckFast);
             return currentAnswer();
         }
 
-        // on a mismatch, try the next access rule
-        lastSeenKeyword = acl->allow;
-        const acl_access *A = acl;
-        acl = cbdataReference(acl->next);
-        cbdataReferenceDone(A);
+        // fall through for mismatch handling
     }
 
     // There were no rules to match or no rules matched
-    calcImplicitAnswer(lastSeenKeyword);
+    calcImplicitAnswer();
+    cbdataReferenceDone(acl);
+    occupied_ = false;
     PROF_stop(aclCheckFast);
 
     return currentAnswer();
 }
 
-/// When no rules matched, the answer is the inversion of the last seen rule
-/// action (or ACCESS_DUNNO if the reversal is not possible). The caller
-/// should set lastSeenAction to ACCESS_DUNNO if there were no rules to see.
+/// When no rules matched, the answer is the inversion of the last rule
+/// action (or ACCESS_DUNNO if the reversal is not possible).
 void
-ACLChecklist::calcImplicitAnswer(const allow_t &lastSeenAction)
+ACLChecklist::calcImplicitAnswer()
 {
+    const allow_t lastAction = (accessList && cbdataReferenceValid(accessList)) ?
+                               accessList->lastAction() : allow_t(ACCESS_DUNNO);
     allow_t implicitRuleAnswer = ACCESS_DUNNO;
-    if (lastSeenAction == ACCESS_DENIED) // reverse last seen "deny"
+    if (lastAction == ACCESS_DENIED) // reverse last seen "deny"
         implicitRuleAnswer = ACCESS_ALLOWED;
-    else if (lastSeenAction == ACCESS_ALLOWED) // reverse last seen "allow"
+    else if (lastAction == ACCESS_ALLOWED) // reverse last seen "allow"
         implicitRuleAnswer = ACCESS_DENIED;
     // else we saw no rules and will respond with ACCESS_DUNNO
 
     debugs(28, 3, HERE << this << " NO match found, last action " <<
-           lastSeenAction << " so returning " << implicitRuleAnswer);
+           lastAction << " so returning " << implicitRuleAnswer);
     markFinished(implicitRuleAnswer, "implicit rule won");
 }
 
 bool
-ACLChecklist::checking() const
-{
-    return checking_;
-}
-
-void
-ACLChecklist::checking (bool const newValue)
-{
-    checking_ = newValue;
-}
-
-bool
 ACLChecklist::callerGone()
 {
     return !cbdataReferenceValid(callback_data);
 }
