(!defaultExpandInternalEntities) {
            if (skippedEntityHandler)
              skippedEntityHandler(handlerArg, entity->name, 0);
            else if (defaultHandler)
              reportDefault(parser, enc, s, next);
            break;
          }