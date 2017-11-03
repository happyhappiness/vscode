static char *get_color_name (char *dest, size_t destlen, int val)
{
  static const char * const missing[3] = {"brown", "lightgray", "default"};
  int i;

  switch (val)
  {
    case COLOR_YELLOW:
      strfcpy (dest, missing[0], destlen);
      return dest;

    case COLOR_WHITE:
      strfcpy (dest, missing[1], destlen);
      return dest;
      
    case COLOR_DEFAULT:
      strfcpy (dest, missing[2], destlen);
      return dest;
  }

  for (i = 0; Colors[i].name; i++)
  {
    if (Colors[i].value == val)
    {
      strfcpy (dest, Colors[i].name, destlen);
      return dest;
    }
  }

  /* Sigh. If we got this far, the color is of the form 'colorN'
   * Slang can handle this itself, so just return 'colorN'
   */

  snprintf (dest, destlen, "color%d", val);
  return dest;
}