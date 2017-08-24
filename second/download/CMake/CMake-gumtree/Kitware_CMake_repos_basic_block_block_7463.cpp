{
    OPEN_INTERNAL_ENTITY *openEntity = openEntityList;
    openEntityList = openEntity->next;
    openEntity->next = freeInternalEntities;
    freeInternalEntities = openEntity;
  }