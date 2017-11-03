void mutt_menu_init (void)
{
  int i;

  for (i = 0; i < MENU_MAX; i++)
    SearchBuffers[i] = NULL;
}