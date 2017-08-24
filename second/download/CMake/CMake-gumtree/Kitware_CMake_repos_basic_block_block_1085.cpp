{
  /* Allocate a process control structure.  */
  kwsysMD5* md5 = (kwsysMD5*)malloc(sizeof(kwsysMD5));
  if (!md5) {
    return 0;
  }
  return md5;
}