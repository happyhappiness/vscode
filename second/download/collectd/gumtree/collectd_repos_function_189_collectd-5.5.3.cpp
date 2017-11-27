static void srrd_create_args_destroy (srrd_create_args_t *args)
{
  if (args == NULL)
    return;

  sfree (args->filename);
  if (args->argv != NULL)
  {
    int i;
    for (i = 0; i < args->argc; i++)
      sfree (args->argv[i]);
    sfree (args->argv);
  }
  sfree (args);
}