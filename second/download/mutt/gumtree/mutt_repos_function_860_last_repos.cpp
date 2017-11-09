static void label_ref_dec(CONTEXT *ctx, char *label)
{
  struct hash_elem *elem;
  uintptr_t count;

  elem = hash_find_elem (ctx->label_hash, label);
  if (!elem)
    return;

  count = (uintptr_t)elem->data;
  if (count <= 1)
  {
    hash_delete(ctx->label_hash, label, NULL, NULL);
    return;
  }

  count--;
  elem->data = (void *)count;
}