{
          dtd->keepProcessing = dtd->standalone;
          /* cannot report skipped entities in declarations */
          if ((role == XML_ROLE_PARAM_ENTITY_REF) && skippedEntityHandler) {
            skippedEntityHandler(handlerArg, name, 1);
            handleDefault = XML_FALSE;
          }
          break;
        }