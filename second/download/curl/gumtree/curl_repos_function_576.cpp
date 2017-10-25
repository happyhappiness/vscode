static
char *GetEnv(const char *variable)
{
#ifdef _WIN32_WCE
  return NULL;
#else
#ifdef WIN32
  /* This shit requires windows.h (HUGE) to be included */
  char env[MAX_PATH]; /* MAX_PATH is from windef.h */
  char *temp = getenv(variable);
  env[0] = '\0';
  if (temp != NULL)
    ExpandEnvironmentStrings(temp, env, sizeof(env));
#else
#ifdef  VMS
  char *env = getenv(variable);
  if (env && strcmp("HOME",variable) == 0) {
        env = decc$translate_vms(env);
  }
#else
  /* no length control */
  char *env = getenv(variable);
#endif
#endif
  return (env && env[0])?strdup(env):NULL;
#endif
}