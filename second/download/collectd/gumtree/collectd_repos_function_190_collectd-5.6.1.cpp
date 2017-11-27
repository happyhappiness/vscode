static srrd_create_args_t *srrd_create_args_create (const char *filename,
    unsigned long pdp_step, time_t last_up,
    int argc, const char **argv)
{
  srrd_create_args_t *args;

  args = calloc (1, sizeof (*args));
  if (args == NULL)
  {
    ERROR ("srrd_create_args_create: calloc failed.");
    return (NULL);
  }
  args->filename = NULL;
  args->pdp_step = pdp_step;
  args->last_up = last_up;
  args->argv = NULL;

  args->filename = strdup (filename);
  if (args->filename == NULL)
  {
    ERROR ("srrd_create_args_create: strdup failed.");
    srrd_create_args_destroy (args);
    return (NULL);
  }

  args->argv = calloc ((size_t) (argc + 1), sizeof (*args->argv));
  if (args->argv == NULL)
  {
    ERROR ("srrd_create_args_create: calloc failed.");
    srrd_create_args_destroy (args);
    return (NULL);
  }

  for (args->argc = 0; args->argc < argc; args->argc++)
  {
    args->argv[args->argc] = strdup (argv[args->argc]);
    if (args->argv[args->argc] == NULL)
    {
      ERROR ("srrd_create_args_create: strdup failed.");
      srrd_create_args_destroy (args);
      return (NULL);
    }
  }
  assert (args->argc == argc);
  args->argv[args->argc] = NULL;

  return (args);
}