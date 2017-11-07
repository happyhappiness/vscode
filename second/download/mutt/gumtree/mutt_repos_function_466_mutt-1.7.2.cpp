void mutt_free_windows ()
{
  FREE (&MuttHelpWindow);
  FREE (&MuttIndexWindow);
  FREE (&MuttStatusWindow);
  FREE (&MuttMessageWindow);
#ifdef USE_SIDEBAR
  FREE (&MuttSidebarWindow);
#endif
}