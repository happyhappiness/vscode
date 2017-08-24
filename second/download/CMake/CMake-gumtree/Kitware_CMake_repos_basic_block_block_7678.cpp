(!dtd->hasParamEntityRefs || dtd->standalone) {
          if (!entity)
            return XML_ERROR_UNDEFINED_ENTITY;
          else if (!entity->is_internal)
            return XML_ERROR_ENTITY_DECLARED_IN_PE;
        }
        else if (!entity) {
          if (skippedEntityHandler)
            skippedEntityHandler(handlerArg, name, 0);
          else if (defaultHandler)
            reportDefault(parser, enc, s, next);
          break;
        }