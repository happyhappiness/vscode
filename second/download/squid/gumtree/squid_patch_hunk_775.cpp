 void
 DelayUserStatsWalkee(DelayUserBucket::Pointer const &current, void *state)
 {
     current->stats ((StoreEntry *)state);
 }
 
+struct DelayUserStatsVisitor {
+    StoreEntry *se;
+    explicit DelayUserStatsVisitor(StoreEntry *s) : se(s) {}
+    void operator() (DelayUserBucket::Pointer const &current) {
+        current->stats(se);
+    }
+};
+
 void
 DelayUser::stats(StoreEntry * sentry)
 {
     spec.stats (sentry, "Per User");
 
     if (spec.restore_bps == -1)
         return;
 
     storeAppendPrintf(sentry, "\t\tCurrent: ");
 
-    if (!buckets.head) {
+    if (buckets.empty()) {
         storeAppendPrintf (sentry, "Not used yet.\n\n");
         return;
     }
 
-    buckets.head->walk(DelayUserStatsWalkee, sentry);
+    DelayUserStatsVisitor visitor(sentry);
+    buckets.visit(visitor);
     storeAppendPrintf(sentry, "\n\n");
 }
 
 void
 DelayUser::dump(StoreEntry *entry) const
 {
