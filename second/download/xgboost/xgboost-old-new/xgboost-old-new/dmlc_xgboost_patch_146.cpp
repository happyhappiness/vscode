@@ -158,8 +158,8 @@ void AllreduceRobust::Broadcast(void *sendrecvbuf_, size_t total_size, int root)
  *
  * \sa CheckPoint, VersionNumber
  */
-int AllreduceRobust::LoadCheckPoint(ISerializable *global_model,
-                                    ISerializable *local_model) {
+int AllreduceRobust::LoadCheckPoint(Serializable *global_model,
+                                    Serializable *local_model) {
   // skip action in single node
   if (world_size == 1) return 0;
   this->LocalModelCheck(local_model != NULL);
@@ -175,7 +175,7 @@ int AllreduceRobust::LoadCheckPoint(ISerializable *global_model,
         // load in local model
         utils::MemoryFixSizeBuffer fs(BeginPtr(local_chkpt[local_chkpt_version]),
                                       local_rptr[local_chkpt_version][1]);
-        local_model->Load(fs);
+        local_model->Load(&fs);
       } else {
         utils::Assert(nlocal == 0, "[%d] local model inconsistent, nlocal=%d", rank, nlocal);
       }
@@ -189,7 +189,7 @@ int AllreduceRobust::LoadCheckPoint(ISerializable *global_model,
     } else {
       utils::Assert(fs.Read(&version_number, sizeof(version_number)) != 0,
                     "read in version number");
-      global_model->Load(fs);
+      global_model->Load(&fs);
       utils::Assert(local_model == NULL || nlocal == num_local_replica + 1,
                     "local model inconsistent, nlocal=%d", nlocal);
     }
@@ -241,8 +241,8 @@ void AllreduceRobust::LocalModelCheck(bool with_local) {
  *
  * \sa CheckPoint, LazyCheckPoint
  */
-void AllreduceRobust::CheckPoint_(const ISerializable *global_model,
-                                  const ISerializable *local_model,
+void AllreduceRobust::CheckPoint_(const Serializable *global_model,
+                                  const Serializable *local_model,
                                   bool lazy_checkpt) {
   // never do check point in single machine mode
   if (world_size == 1) {
@@ -261,7 +261,7 @@ void AllreduceRobust::CheckPoint_(const ISerializable *global_model,
       local_chkpt[new_version].clear();
       utils::MemoryBufferStream fs(&local_chkpt[new_version]);
       if (local_model != NULL) {
-        local_model->Save(fs);
+        local_model->Save(&fs);
       }
       local_rptr[new_version].clear();
       local_rptr[new_version].push_back(0);
@@ -287,7 +287,7 @@ void AllreduceRobust::CheckPoint_(const ISerializable *global_model,
     global_checkpoint.resize(0);
     utils::MemoryBufferStream fs(&global_checkpoint);
     fs.Write(&version_number, sizeof(version_number));
-    global_model->Save(fs);
+    global_model->Save(&fs);
     global_lazycheck = NULL;
   }
   // reset result buffer
@@ -748,7 +748,7 @@ AllreduceRobust::ReturnType AllreduceRobust::TryLoadCheckPoint(bool requester) {
     global_checkpoint.resize(0);
     utils::MemoryBufferStream fs(&global_checkpoint);
     fs.Write(&version_number, sizeof(version_number));
-    global_lazycheck->Save(fs);
+    global_lazycheck->Save(&fs);
     global_lazycheck = NULL;
   }
   // recover global checkpoint