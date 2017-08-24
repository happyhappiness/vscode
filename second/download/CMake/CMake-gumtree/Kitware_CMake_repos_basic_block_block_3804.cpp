{
    next = co->next;
    freecookie(co);
    co = next;
  }