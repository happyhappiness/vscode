(p->HiUnit != p->LoUnit)
      c1 = (CTX_PTR)(p->HiUnit -= UNIT_SIZE);
    else if (p->FreeList[0] != 0)
      c1 = (CTX_PTR)RemoveNode(p, 0);
    else
    {
      c1 = (CTX_PTR)AllocUnitsRare(p, 0);
      if (!c1)
        return NULL;
    }