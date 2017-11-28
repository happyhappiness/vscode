 {
     DelayPools::MemoryUsed += sizeof (DelayUserBucket);
     return ::operator new (size);
 }
 
 void
-DelayUserBucket::operator delete (void *address)
+DelayUserBucket::operator delete(void *address)
 {
-    DelayPools::MemoryUsed -= sizeof (DelayUserBucket);
-    ::operator delete (address);
+    DelayPools::MemoryUsed -= sizeof(DelayUserBucket);
+    ::operator delete(address);
 }
 
-DelayUserBucket::DelayUserBucket(AuthUser *aUser) : authUser (aUser)
+DelayUserBucket::DelayUserBucket(Auth::User::Pointer aUser) : authUser(aUser)
 {
     debugs(77, 3, "DelayUserBucket::DelayUserBucket");
-
-    authUser->lock();
 }
 
 DelayUserBucket::~DelayUserBucket()
 {
-    authUser->unlock();
+    authUser = NULL;
     debugs(77, 3, "DelayUserBucket::~DelayUserBucket");
 }
 
 void
 DelayUserBucket::stats (StoreEntry *entry) const
 {
     storeAppendPrintf(entry, " %s:", authUser->username());
-    theBucket.stats (entry);
+    theBucket.stats(entry);
 }
 
-DelayUser::Id::Id(DelayUser::Pointer aDelayUser,AuthUser *aUser) : theUser(aDelayUser)
+DelayUser::Id::Id(DelayUser::Pointer aDelayUser, Auth::User::Pointer aUser) : theUser(aDelayUser)
 {
     theBucket = new DelayUserBucket(aUser);
     DelayUserBucket::Pointer const *existing = theUser->buckets.find(theBucket, DelayUserCmp);
 
     if (existing) {
         theBucket = *existing;
