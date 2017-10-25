void ourWriteEnv(CURL *curl)
{
  unsigned int i;
  char *string, numtext[10];
  long longinfo;
  double doubleinfo;
  
  for (i=0; variables[i].name; i++) {
    switch (variables[i].type) {
    case writeenv_STRING:
      if (curl_easy_getinfo(curl, variables[i].id, &string) == CURLE_OK)
        internalSetEnv(variables[i].name, string);
      else
        internalSetEnv(variables[i].name, NULL);
      break;

    case writeenv_LONG:
      if (curl_easy_getinfo(curl, variables[i].id, &longinfo) == CURLE_OK) {
        sprintf(numtext, "%5ld", longinfo);
        internalSetEnv(variables[i].name, numtext);
      }
      else
        internalSetEnv(variables[i].name, NULL);
      break;
    case writeenv_DOUBLE:
      if (curl_easy_getinfo(curl, variables[i].id, &doubleinfo) == CURLE_OK) {
        sprintf(numtext, "%6.2f", doubleinfo);
        internalSetEnv(variables[i].name, numtext);
      }
      else
        internalSetEnv(variables[i].name, NULL);
      break;
    default:
      break;
    }
  }

  return;
}