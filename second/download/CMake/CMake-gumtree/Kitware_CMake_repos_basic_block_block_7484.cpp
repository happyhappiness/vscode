{
    TAG *p;
    if (tagList == NULL) {
      if (freeTagList == NULL)
        break;
      tagList = freeTagList;
      freeTagList = NULL;
    }
    p = tagList;
    tagList = tagList->parent;
    FREE(p->buf);
    destroyBindings(p->bindings, parser);
    FREE(p);
  }