 
 /**
  * Async-opener of a Comm connection.
  */
 class ConnOpener : public AsyncJob
 {
-protected:
-    virtual void start();
-    virtual void swanSong();
+    CBDATA_CLASS(ConnOpener);
 
 public:
     void noteAbort() { mustStop("externally aborted"); }
 
     typedef CbcPointer<ConnOpener> Pointer;
 
