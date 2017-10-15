     control->core()->push_log_std("Could not open XMLRPC log file '" + m_xmlrpcLog + "'.");
     return;
   }
 
   control->core()->push_log_std("Logging XMLRPC events to '" + m_xmlrpcLog + "'.");
 }
-
-void
-ThreadWorker::task_touch_log() {
-  priority_queue_insert(&m_taskScheduler, &m_taskTouchLog, cachedTime + rak::timer::from_seconds(1));
-
-  acquire_global_lock();
-  control->core()->push_log("Tick Tock.");
-  release_global_lock();
-}
