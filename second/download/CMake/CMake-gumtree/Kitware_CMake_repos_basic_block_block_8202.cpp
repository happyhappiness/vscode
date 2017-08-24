{
      BLOCK *tem = p->next;
      p->next = pool->freeBlocks;
      pool->freeBlocks = p;
      p = tem;
    }