char *sanitize_dos_name(char *file_name)
{
  char new_name[PATH_MAX];

  if(!file_name)
    return NULL;

  if(strlen(file_name) >= PATH_MAX)
    file_name[PATH_MAX-1] = '\0'; /* truncate it */

  strcpy(new_name, msdosify(file_name));

  Curl_safefree(file_name);

  return strdup(rename_if_dos_device_name(new_name));
}