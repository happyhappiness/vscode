int wcwidth_ja (wchar_t ucs)
{
  if (ucs >= 0x3021)
    return -1; /* continue with the normal check */
  /* a rough range for quick check */
  if ((ucs >= 0x00a1 && ucs <= 0x00fe) || /* Latin-1 Supplement */
      (ucs >= 0x0391 && ucs <= 0x0451) || /* Greek and Cyrillic */
      (ucs >= 0x2010 && ucs <= 0x266f) || /* Symbols */
      (ucs >= 0x3000 && ucs <= 0x3020))   /* CJK Symbols and Punctuation */
    return 2;
  else
    return -1;
}