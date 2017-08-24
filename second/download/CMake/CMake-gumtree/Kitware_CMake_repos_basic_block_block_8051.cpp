{
            dtd->paramEntityRead = XML_FALSE;
            entity->open = XML_TRUE;
            if (!externalEntityRefHandler(externalEntityRefHandlerArg,
                                          0,
                                          entity->base,
                                          entity->systemId,
                                          entity->publicId)) {
              entity->open = XML_FALSE;
              result = XML_ERROR_EXTERNAL_ENTITY_HANDLING;
              goto endEntityValue;
            }
            entity->open = XML_FALSE;
            if (!dtd->paramEntityRead)
              dtd->keepProcessing = dtd->standalone;
          }