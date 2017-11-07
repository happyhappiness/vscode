int mutt_get_hook_type (const char *name)
{
  const struct command_t *c;

  for (c = Commands ; c->name ; c++)
    if (c->func == mutt_parse_hook && ascii_strcasecmp (c->name, name) == 0)
      return c->data;
  return 0;
}