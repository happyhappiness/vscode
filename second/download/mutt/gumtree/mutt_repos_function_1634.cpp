void mutt_set_header_color (CONTEXT *ctx, HEADER *curhdr)
{
  COLOR_LINE *color;

  if (!curhdr)
    return;

  for (color = ColorIndexList; color; color = color->next)
   if (mutt_pattern_exec (color->color_pattern, MUTT_MATCH_FULL_ADDRESS, ctx, curhdr))
   {
      curhdr->pair = color->pair;
      return;
   }
  curhdr->pair = ColorDefs[MT_COLOR_NORMAL];
}