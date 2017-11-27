static void cj_key_free (cj_key_t *key) /* {{{ */
{
  if (key == NULL)
    return;

  sfree (key->path);
  sfree (key->type);
  sfree (key->instance);

  sfree (key);
}