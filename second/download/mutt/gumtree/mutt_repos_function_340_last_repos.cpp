static struct keymap_t *allocKeys (int len, keycode_t *keys)
{
  struct keymap_t *p;

  p = safe_calloc (1, sizeof (struct keymap_t));
  p->len = len;
  p->keys = safe_malloc (len * sizeof (keycode_t));
  memcpy (p->keys, keys, len * sizeof (keycode_t));
  return (p);
}