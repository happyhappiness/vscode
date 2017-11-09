void *create_thread(void *progress_bar)
{
  pthread_t tid[NUMT];
  int i;
  int error;

  /* Make sure I don't create more threads than urls. */
  for(i = 0; i < NUMT && i < num_urls ; i++) {
    error = pthread_create(&tid[i],
                           NULL, /* default attributes please */
                           pull_one_url,
                           NULL);
    if(0 != error)
      fprintf(stderr, "Couldn't run thread number %d, errno %d\n", i, error);
    else
      fprintf(stderr, "Thread %d, gets %s\n", i, urls[i]);
  }

  /* Wait for all threads to terminate. */
  for(i = 0; i < NUMT && i < num_urls; i++) {
    error = pthread_join(tid[i], NULL);
    fprintf(stderr, "Thread %d terminated\n", i);
  }

  /* This stops the pulsing if you have it turned on in the progress bar
     section */
  g_source_remove(GPOINTER_TO_INT(g_object_get_data(G_OBJECT(progress_bar),
                                                    "pulse_id")));

  /* This destroys the progress bar */
  gtk_widget_destroy(progress_bar);

  /* [Un]Comment this out to kill the program rather than pushing close. */
  /* gtk_main_quit(); */


  return NULL;

}