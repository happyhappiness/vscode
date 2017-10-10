 
 int start_async(struct async *async);
 int finish_async(struct async *async);
 int in_async(void);
 void NORETURN async_exit(int code);
 
+/**
+ * This callback should initialize the child process and preload the
+ * error channel if desired. The preloading of is useful if you want to
+ * have a message printed directly before the output of the child process.
+ * pp_cb is the callback cookie as passed to run_processes_parallel.
+ * You can store a child process specific callback cookie in pp_task_cb.
+ *
+ * Even after returning 0 to indicate that there are no more processes,
+ * this function will be called again until there are no more running
+ * child processes.
+ *
+ * Return 1 if the next child is ready to run.
+ * Return 0 if there are currently no more tasks to be processed.
+ * To send a signal to other child processes for abortion,
+ * return the negative signal number.
+ */
+typedef int (*get_next_task_fn)(struct child_process *cp,
+				struct strbuf *err,
+				void *pp_cb,
+				void **pp_task_cb);
+
+/**
+ * This callback is called whenever there are problems starting
+ * a new process.
+ *
+ * You must not write to stdout or stderr in this function. Add your
+ * message to the strbuf err instead, which will be printed without
+ * messing up the output of the other parallel processes.
+ *
+ * pp_cb is the callback cookie as passed into run_processes_parallel,
+ * pp_task_cb is the callback cookie as passed into get_next_task_fn.
+ *
+ * Return 0 to continue the parallel processing. To abort return non zero.
+ * To send a signal to other child processes for abortion, return
+ * the negative signal number.
+ */
+typedef int (*start_failure_fn)(struct strbuf *err,
+				void *pp_cb,
+				void *pp_task_cb);
+
+/**
+ * This callback is called on every child process that finished processing.
+ *
+ * You must not write to stdout or stderr in this function. Add your
+ * message to the strbuf err instead, which will be printed without
+ * messing up the output of the other parallel processes.
+ *
+ * pp_cb is the callback cookie as passed into run_processes_parallel,
+ * pp_task_cb is the callback cookie as passed into get_next_task_fn.
+ *
+ * Return 0 to continue the parallel processing.  To abort return non zero.
+ * To send a signal to other child processes for abortion, return
+ * the negative signal number.
+ */
+typedef int (*task_finished_fn)(int result,
+				struct strbuf *err,
+				void *pp_cb,
+				void *pp_task_cb);
+
+/**
+ * Runs up to n processes at the same time. Whenever a process can be
+ * started, the callback get_next_task_fn is called to obtain the data
+ * required to start another child process.
+ *
+ * The children started via this function run in parallel. Their output
+ * (both stdout and stderr) is routed to stderr in a manner that output
+ * from different tasks does not interleave.
+ *
+ * start_failure_fn and task_finished_fn can be NULL to omit any
+ * special handling.
+ */
+int run_processes_parallel(int n,
+			   get_next_task_fn,
+			   start_failure_fn,
+			   task_finished_fn,
+			   void *pp_cb);
+
 #endif
