{
  char* scan;
  char* temp;
  int offset;

  if (p == &regdummy)
    return;

  // Find last node.
  scan = p;
  for (;;) {
    temp = regnext(scan);
    if (temp == 0)
      break;
    scan = temp;
  }

  if (OP(scan) == BACK)
    offset = int(scan - val);
  else
    offset = int(val - scan);
  *(scan + 1) = static_cast<char>((offset >> 8) & 0377);
  *(scan + 2) = static_cast<char>(offset & 0377);
}