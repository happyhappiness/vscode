static bool safe_strequal(char* str1, char* str2)
{
  if(str1 && str2)
    /* both pointers point to something then compare them */
    return (0 != Curl_raw_equal(str1, str2)) ? TRUE : FALSE;
  else
    /* if both pointers are NULL then treat them as equal */
    return (!str1 && !str2) ? TRUE : FALSE;
}