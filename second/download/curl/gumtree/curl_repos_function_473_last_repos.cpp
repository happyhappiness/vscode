char *custom_strdup(const char *ptr)
{
  if(!seen_strdup && seen_malloc) {
    /* currently (2013.03.13), memory tracking enabled builds do not call
       the strdup callback, in this case malloc callback and memcpy are used
       instead. If some day this is changed the following printf() should be
       uncommented, and a line added to test definition.
    printf("seen custom_strdup()\n");
    */
    seen_strdup = 1;
  }
  return (strdup)(ptr);
}