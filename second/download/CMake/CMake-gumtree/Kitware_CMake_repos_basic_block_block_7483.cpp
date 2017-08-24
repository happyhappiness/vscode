{
    OPEN_INTERNAL_ENTITY *openEntity;
    if (entityList == NULL) {
      if (freeInternalEntities == NULL)
        break;
      entityList = freeInternalEntities;
      freeInternalEntities = NULL;
    }
    openEntity = entityList;
    entityList = entityList->next;
    FREE(openEntity);
  }