{
    BLOCK *tem = p->next;
    pool->mem->free_fcn(p);
    p = tem;
  }