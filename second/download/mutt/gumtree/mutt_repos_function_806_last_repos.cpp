static void calc_header_width_padding (int idx, const char *header, int calc_max)
{
  int width;

  HeaderPadding[idx] = mutt_strlen (header);
  width = mutt_strwidth (header);
  if (calc_max && MaxHeaderWidth < width)
    MaxHeaderWidth = width;
  HeaderPadding[idx] -= width;
}