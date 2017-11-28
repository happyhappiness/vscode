 /** temporary thunk across to the unrefactored store interface */
 
 class StoreRootEngine : public AsyncEngine
 {
 
 public:
-    int checkEvents(int timeout) {
+    int checkEvents(int) {
         Store::Root().callback();
         return EVENT_IDLE;
     };
 };
 
 class SignalEngine: public AsyncEngine
 {
 
 public:
+#if KILL_PARENT_OPT
+    SignalEngine(): parentKillNotified(false) {
+        parentPid = getppid();
+    }
+#endif
+
     virtual int checkEvents(int timeout);
 
 private:
     static void StopEventLoop(void *) {
         if (EventLoop::Running)
             EventLoop::Running->stop();
