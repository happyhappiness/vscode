static char crypt_flags (int flags)
{
  if (flags & KEYFLAG_REVOKED)
    return 'R';
  else if (flags & KEYFLAG_EXPIRED)
    return 'X';
  else if (flags & KEYFLAG_DISABLED)
    return 'd';
  else if (flags & KEYFLAG_CRITICAL)
    return 'c';
  else 
    return ' ';
}