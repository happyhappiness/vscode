void mutt_init_windows ()
{
  MuttHelpWindow = safe_calloc (sizeof (mutt_window_t), 1);
  MuttIndexWindow = safe_calloc (sizeof (mutt_window_t), 1);
  MuttStatusWindow = safe_calloc (sizeof (mutt_window_t), 1);
  MuttMessageWindow = safe_calloc (sizeof (mutt_window_t), 1);
#ifdef USE_SIDEBAR
  MuttSidebarWindow = safe_calloc (sizeof (mutt_window_t), 1);
#endif
}