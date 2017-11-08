int main(int argc, char **argv)
{
  GtkWidget *top_window, *outside_frame, *inside_frame, *progress_bar;

  /* Must initialize libcurl before any threads are started */
  curl_global_init(CURL_GLOBAL_ALL);

  /* Init thread */
  g_thread_init(NULL);
  gdk_threads_init ();
  gdk_threads_enter ();

  gtk_init(&argc, &argv);

  /* Base window */
  top_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  /* Frame */
  outside_frame = gtk_frame_new(NULL);
  gtk_frame_set_shadow_type(GTK_FRAME(outside_frame), GTK_SHADOW_OUT);
  gtk_container_add(GTK_CONTAINER(top_window), outside_frame);

  /* Frame */
  inside_frame = gtk_frame_new(NULL);
  gtk_frame_set_shadow_type(GTK_FRAME(inside_frame), GTK_SHADOW_IN);
  gtk_container_set_border_width(GTK_CONTAINER(inside_frame), 5);
  gtk_container_add(GTK_CONTAINER(outside_frame), inside_frame);

  /* Progress bar */
  progress_bar = gtk_progress_bar_new();
  gtk_progress_bar_pulse (GTK_PROGRESS_BAR (progress_bar));
  /* Make uniform pulsing */
  gint pulse_ref = g_timeout_add (300, pulse_bar, progress_bar);
  g_object_set_data(G_OBJECT(progress_bar), "pulse_id",
                    GINT_TO_POINTER(pulse_ref));
  gtk_container_add(GTK_CONTAINER(inside_frame), progress_bar);

  gtk_widget_show_all(top_window);
  printf("gtk_widget_show_all\n");

  g_signal_connect(G_OBJECT (top_window), "delete-event",
                   G_CALLBACK(cb_delete), NULL);

  if (!g_thread_create(&create_thread, progress_bar, FALSE, NULL) != 0)
    g_warning("can't create the thread");

  gtk_main();
  gdk_threads_leave();
  printf("gdk_threads_leave\n");

  return 0;
}