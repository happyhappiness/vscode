(i = 0; i < table->size; i++) {
    table->mem->free_fcn(table->v[i]);
    table->v[i] = NULL;
  }