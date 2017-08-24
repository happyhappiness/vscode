{
  char *result;
  char *vms_path;

  /* first use the DECC getenv() function */
  result = decc$getenv(envvar);
  if(result == NULL) {
    return result;
  }

  vms_path = result;
  result = vms_translate_path(vms_path);

  /* note that if you backport this to use VAX C RTL, that the VAX C RTL */
  /* may do a malloc(2048) for each call to getenv(), so you will need   */
  /* to add a free(vms_path) */
  /* Do not do a free() for DEC C RTL builds, which should be used for */
  /* VMS 5.5-2 and later, even if using GCC */

  return result;
}