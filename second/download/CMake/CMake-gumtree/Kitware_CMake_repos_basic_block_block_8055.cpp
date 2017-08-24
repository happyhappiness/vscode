(entity->open) {
          if (enc == encoding)
            eventPtr = entityTextPtr;
          result = XML_ERROR_RECURSIVE_ENTITY_REF;
          goto endEntityValue;
        }