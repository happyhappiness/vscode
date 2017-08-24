{
  enum protection_level l = name_to_level(level);
  if(l == PROT_NONE)
    return -1;
  DEBUGASSERT(l > PROT_NONE && l < PROT_LAST);
  conn->request_data_prot = l;
  return 0;
}