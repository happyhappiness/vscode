{
      entity->open = XML_FALSE;
      openInternalEntities = openEntity->next;
      /* put openEntity back in list of free instances */
      openEntity->next = freeInternalEntities;
      freeInternalEntities = openEntity;
    }