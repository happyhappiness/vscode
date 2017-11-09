static
char *GetEnv(const char *variable)
{
#if defined(_WIN32_WCE) || defined(CURL_WINDOWS_APP)
  (void)variable;
  return NULL;
#else
#ifdef WIN32
  char env[MAX_PATH]; /* MAX_PATH is from windef.h */
  char *temp = getenv(variable);
  env[0] = '\0';
  if(temp != NULL)
    ExpandEnvironmentStringsA(temp, env, sizeof(env));
  return (env[0] != '\0')?strdup(env):NULL;
#else
  char *env = getenv(variable);
  return (env && env[0])?strdup(env):NULL;
#endif
#endif
}