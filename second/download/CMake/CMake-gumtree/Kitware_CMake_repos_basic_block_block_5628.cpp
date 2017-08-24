{
  if(first && second)
    /* both pointers point to something then compare them */
    return Curl_strcasecompare(first, second);

  /* if both pointers are NULL then treat them as equal */
  return (NULL == first && NULL == second);
}