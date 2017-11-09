static int fgbgattr_to_color(int fg, int bg, int attr)
{
#ifdef HAVE_COLOR
  if(fg != -1 && bg != -1)
    return attr | mutt_alloc_color(fg, bg);
  else
#endif
    return attr;
}