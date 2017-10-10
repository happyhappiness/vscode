 
 /*
  * Mutex and conditional variable can't be statically-initialized on Windows.
  */
 static void init_thread(void)
 {
+	int i;
 	init_recursive_mutex(&read_mutex);
 	pthread_mutex_init(&counter_mutex, NULL);
 	pthread_mutex_init(&work_mutex, NULL);
 	if (show_stat)
 		pthread_mutex_init(&deepest_delta_mutex, NULL);
 	pthread_key_create(&key, NULL);
 	thread_data = xcalloc(nr_threads, sizeof(*thread_data));
+	for (i = 0; i < nr_threads; i++) {
+		thread_data[i].pack_fd = open(curr_pack, O_RDONLY);
+		if (thread_data[i].pack_fd == -1)
+			die_errno(_("unable to open %s"), curr_pack);
+	}
+
 	threads_active = 1;
 }
 
 static void cleanup_thread(void)
 {
+	int i;
 	if (!threads_active)
 		return;
 	threads_active = 0;
 	pthread_mutex_destroy(&read_mutex);
 	pthread_mutex_destroy(&counter_mutex);
 	pthread_mutex_destroy(&work_mutex);
 	if (show_stat)
 		pthread_mutex_destroy(&deepest_delta_mutex);
+	for (i = 0; i < nr_threads; i++)
+		close(thread_data[i].pack_fd);
 	pthread_key_delete(key);
 	free(thread_data);
 }
 
 #else
 
