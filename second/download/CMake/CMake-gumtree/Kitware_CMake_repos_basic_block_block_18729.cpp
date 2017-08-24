{
    q = p->next_closing;
    uv__finish_close(p);
    p = q;
  }