@@ -31,6 +31,7 @@ AllreduceBase::AllreduceBase(void) {
   // tracker URL
   task_id = "NULL";
   err_link = NULL;
+  dmlc_role = "worker";
   this->SetParam("rabit_reduce_buffer", "256MB");
   // setup possible enviroment variable of intrest
   env_vars.push_back("rabit_task_id");
@@ -39,6 +40,12 @@ AllreduceBase::AllreduceBase(void) {
   env_vars.push_back("rabit_reduce_ring_mincount");
   env_vars.push_back("rabit_tracker_uri");
   env_vars.push_back("rabit_tracker_port");
+  // also include dmlc support direct variables
+  env_vars.push_back("DMLC_TASK_ID");
+  env_vars.push_back("DMLC_ROLE");
+  env_vars.push_back("DMLC_NUM_ATTEMPT");
+  env_vars.push_back("DMLC_TRACKER_URI");
+  env_vars.push_back("DMLC_TRACKER_PORT");
 }
 
 // initialization function
@@ -86,6 +93,10 @@ void AllreduceBase::Init(void) {
       this->SetParam("rabit_world_size", num_task);
     }
   }
+  if (dmlc_role != "worker") {
+    fprintf(stderr, "Rabit Module currently only work with dmlc worker, quit this program by exit 0\n");
+    exit(0);
+  }
   // clear the setting before start reconnection
   this->rank = -1;
   //---------------------
@@ -150,6 +161,10 @@ void AllreduceBase::SetParam(const char *name, const char *val) {
   if (!strcmp(name, "rabit_tracker_uri")) tracker_uri = val;
   if (!strcmp(name, "rabit_tracker_port")) tracker_port = atoi(val);
   if (!strcmp(name, "rabit_task_id")) task_id = val;
+  if (!strcmp(name, "DMLC_TRACKER_URI")) tracker_uri = val;
+  if (!strcmp(name, "DMLC_TRACKER_PORT")) tracker_port = atoi(val);
+  if (!strcmp(name, "DMLC_TASK_ID")) task_id = val;
+  if (!strcmp(name, "DMLC_ROLE")) dmlc_role = val;
   if (!strcmp(name, "rabit_world_size")) world_size = atoi(val);
   if (!strcmp(name, "rabit_hadoop_mode")) hadoop_mode = atoi(val);
   if (!strcmp(name, "rabit_reduce_ring_mincount")) {