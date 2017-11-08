static bool safe_strequal(char* str1, char* str2)
{
  if(str1 && str2)
    /* both pointers point to something then compare them */
    return (bool)(0 != strequal(str1, str2));
  else
    /* if both pointers are NULL then treat them as equal */
    return (bool)(!str1 && !str2);
}