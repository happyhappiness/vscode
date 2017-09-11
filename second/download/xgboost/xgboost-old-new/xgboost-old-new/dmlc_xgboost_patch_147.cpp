@@ -37,15 +37,15 @@ class MPIEngine : public IEngine {
   virtual void InitAfterException(void) {
     utils::Error("MPI is not fault tolerant");
   }
-  virtual int LoadCheckPoint(ISerializable *global_model,
-                             ISerializable *local_model = NULL) {
+  virtual int LoadCheckPoint(Serializable *global_model,
+                             Serializable *local_model = NULL) {
     return 0;
   }
-  virtual void CheckPoint(const ISerializable *global_model,
-                          const ISerializable *local_model = NULL) {
+  virtual void CheckPoint(const Serializable *global_model,
+                          const Serializable *local_model = NULL) {
     version_number += 1;
   }
-  virtual void LazyCheckPoint(const ISerializable *global_model) {
+  virtual void LazyCheckPoint(const Serializable *global_model) {
     version_number += 1;
   }
   virtual int VersionNumber(void) const {