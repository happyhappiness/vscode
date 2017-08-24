{
  char* new_title;

  /* We cannot free this pointer when libuv shuts down,
   * the process may still be using it.
   */
  new_title = uv__strdup(title);
  if (new_title == NULL)
    return -ENOMEM;

  /* If this is the first time this is set,
   * don't free and set argv[1] to NULL.
   */
  if (process_title_ptr != NULL)
    uv__free(process_title_ptr);

  process_title_ptr = new_title;

  process_argv[0] = process_title_ptr;
  if (process_argc > 1)
     process_argv[1] = NULL;

  return 0;
}