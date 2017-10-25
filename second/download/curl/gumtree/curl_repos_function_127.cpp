char *GetEnv(char *variable)
{
#ifdef WIN32
  /* This shit requires windows.h (HUGE) to be included */
  char env[MAX_PATH]; /* MAX_PATH is from windef.h */
  char *temp = getenv(variable);
  env[0] = '\0';
  ExpandEnvironmentStrings(temp, env, sizeof(env));
#else
  /* no length control */
  char *env = getenv(variable);
#endif
  return env?strdup(env):NULL;
}