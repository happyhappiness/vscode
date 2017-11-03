static char gnupg_trustletter (int t)
{
  switch (t)
  {
    case 1: return 'n';
    case 2: return 'm';
    case 3: return 'f';
  }
  return 'q';
}