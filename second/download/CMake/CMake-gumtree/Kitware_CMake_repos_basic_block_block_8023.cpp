(checkEntityDecl) {
          if (!entity)
            return XML_ERROR_UNDEFINED_ENTITY;
          else if (!entity->is_internal)
            return XML_ERROR_ENTITY_DECLARED_IN_PE;
        }
        else if (!entity) {
          /* Cannot report skipped entity here - see comments on
             skippedEntityHandler.
          if (skippedEntityHandler)
            skippedEntityHandler(handlerArg, name, 0);
          */
          /* Cannot call the default handler because this would be
             out of sync with the call to the startElementHandler.
          if ((pool == &tempPool) && defaultHandler)
            reportDefault(parser, enc, ptr, next);
          */
          break;
        }