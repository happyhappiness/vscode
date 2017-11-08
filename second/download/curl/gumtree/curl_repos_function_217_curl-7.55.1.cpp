gboolean pulse_bar(gpointer data)
{
  gdk_threads_enter();
  gtk_progress_bar_pulse(GTK_PROGRESS_BAR (data));
  gdk_threads_leave();

  /* Return true so the function will be called again;
   * returning false removes this timeout function.
   */
  return TRUE;
}