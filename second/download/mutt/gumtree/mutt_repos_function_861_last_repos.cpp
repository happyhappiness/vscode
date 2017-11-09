static void label_ref_inc(CONTEXT *ctx, char *label)
{
  struct hash_elem *elem;
  uintptr_t count;

  elem = hash_find_elem (ctx->label_hash, label);
  if (!elem)
  {
    count = 1;
    hash_insert(ctx->label_hash, label, (void *)count);
    return;
  }

  count = (uintptr_t)elem->data;
  count++;
  elem->data = (void *)count;
}