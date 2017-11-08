static
char *GetEnv(const char *variable)
{
#ifdef _WIN32_WCE
  return NULL;
#else
#ifdef WIN32
  char env[MAX_PATH]; /* MAX_PATH is from windef.h */
  char *temp = getenv(variable);
  env[0] = '\0';
  if(temp != NULL)
    ExpandEnvironmentStrings(temp, env, sizeof(env));
  return (env[0] != '\0')?strdup(env):NULL;
#else
  char *env = getenv(variable);
#ifdef VMS
  if(env && strcmp("HOME",variable) == 0)
    env = decc$translate_vms(env);
#endif
  return (env && env[0])?strdup(env):NULL;
#endif
#endif
}