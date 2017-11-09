int is_display_corrupting_utf8 (wchar_t wc)
{
  if (wc == (wchar_t)0x200f ||   /* bidi markers: #3827 */
      wc == (wchar_t)0x200e ||
      wc == (wchar_t)0x00ad ||   /* soft hyphen: #3848 */
      wc == (wchar_t)0xfeff ||   /* zero width no-break space */
      (wc >= (wchar_t)0x2066 &&  /* misc directional markers */
       wc <= (wchar_t)0x2069) ||
      (wc >= (wchar_t)0x202a &&  /* misc directional markers: #3854 */
       wc <= (wchar_t)0x202e))
    return 1;
  else
    return 0;
}