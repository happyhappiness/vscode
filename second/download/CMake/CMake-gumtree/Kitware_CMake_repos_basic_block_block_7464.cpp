{
    TAG *tag = tStk;
    tStk = tStk->parent;
    tag->parent = freeTagList;
    moveToFreeBindingList(parser, tag->bindings);
    tag->bindings = NULL;
    freeTagList = tag;
  }