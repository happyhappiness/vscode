static void poll_worker_cleanup(void *arg) {
  mcelog_thread_running = 0;
  FILE *p_file = *((FILE **)arg);
  if (p_file != NULL)
    fclose(p_file);
  free(arg);
}