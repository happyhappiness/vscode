int
mutt_comp_can_read (const char *path)
{
  if (!path)
    return 0;

  if (find_hook (MUTT_OPENHOOK, path))
    return 1;
  else
    return 0;
}