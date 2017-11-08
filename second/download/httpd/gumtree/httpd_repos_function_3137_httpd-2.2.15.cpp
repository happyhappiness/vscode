static
void hashTableDestroy(HASH_TABLE *table)
{
  size_t i;
  for (i = 0; i < table->size; i++) {
    NAMED *p = table->v[i];
    if (p)
      table->mem->free_fcn(p);
  }
  if (table->v)
    table->mem->free_fcn(table->v);
}