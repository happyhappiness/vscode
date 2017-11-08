static
NAMED *lookup(HASH_TABLE *table, KEY name, size_t createSize)
{
  size_t i;
  if (table->size == 0) {
    size_t tsize;

    if (!createSize)
      return 0;
    tsize = INIT_SIZE * sizeof(NAMED *);
    table->v = table->mem->malloc_fcn(tsize);
    if (!table->v)
      return 0;
    memset(table->v, 0, tsize);
    table->size = INIT_SIZE;
    table->usedLim = INIT_SIZE / 2;
    i = hash(name) & (table->size - 1);
  }
  else {
    unsigned long h = hash(name);
    for (i = h & (table->size - 1);
         table->v[i];
         i == 0 ? i = table->size - 1 : --i) {
      if (keyeq(name, table->v[i]->name))
	return table->v[i];
    }
    if (!createSize)
      return 0;
    if (table->used == table->usedLim) {
      /* check for overflow */
      size_t newSize = table->size * 2;
      size_t tsize = newSize * sizeof(NAMED *);
      NAMED **newV = table->mem->malloc_fcn(tsize);
      if (!newV)
	return 0;
      memset(newV, 0, tsize);
      for (i = 0; i < table->size; i++)
	if (table->v[i]) {
	  size_t j;
	  for (j = hash(table->v[i]->name) & (newSize - 1);
	       newV[j];
	       j == 0 ? j = newSize - 1 : --j)
	    ;
	  newV[j] = table->v[i];
	}
      table->mem->free_fcn(table->v);
      table->v = newV;
      table->size = newSize;
      table->usedLim = newSize/2;
      for (i = h & (table->size - 1);
	   table->v[i];
	   i == 0 ? i = table->size - 1 : --i)
	;
    }
  }
  table->v[i] = table->mem->malloc_fcn(createSize);
  if (!table->v[i])
    return 0;
  memset(table->v[i], 0, createSize);
  table->v[i]->name = name;
  (table->used)++;
  return table->v[i];
}