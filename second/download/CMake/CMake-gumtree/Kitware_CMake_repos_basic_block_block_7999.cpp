(textEnd != next && ps_parsing == XML_SUSPENDED) {
      entity->processed = (int)(next - textStart);
      processor = internalEntityProcessor;
    }
    else {
      entity->open = XML_FALSE;
      openInternalEntities = openEntity->next;
      /* put openEntity back in list of free instances */
      openEntity->next = freeInternalEntities;
      freeInternalEntities = openEntity;
    }