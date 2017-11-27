static int email_shutdown(void) {
  if (connector != ((pthread_t)0)) {
    pthread_kill(connector, SIGTERM);
    connector = (pthread_t)0;
  }

  if (connector_socket >= 0) {
    close(connector_socket);
    connector_socket = -1;
  }

  /* don't allow any more connections to be processed */
  pthread_mutex_lock(&conns_mutex);

  available_collectors = 0;

  if (collectors != NULL) {
    for (int i = 0; i < max_conns; ++i) {
      if (collectors[i] == NULL)
        continue;

      if (collectors[i]->thread != ((pthread_t)0)) {
        pthread_kill(collectors[i]->thread, SIGTERM);
        collectors[i]->thread = (pthread_t)0;
      }

      if (collectors[i]->socket != NULL) {
        fclose(collectors[i]->socket);
        collectors[i]->socket = NULL;
      }

      sfree(collectors[i]);
    }
    sfree(collectors);
  } /* if (collectors != NULL) */

  pthread_mutex_unlock(&conns_mutex);

  type_list_free(&list_count);
  type_list_free(&list_count_copy);
  type_list_free(&list_size);
  type_list_free(&list_size_copy);
  type_list_free(&list_check);
  type_list_free(&list_check_copy);

  unlink((NULL == sock_file) ? SOCK_PATH : sock_file);

  sfree(sock_file);
  sfree(sock_group);
  return (0);
}