(dtd->keepProcessing && declEntity) {
        declEntity->notation = poolStoreString(&dtd->pool, enc, s, next);
        if (!declEntity->notation)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&dtd->pool);
        if (unparsedEntityDeclHandler) {
          *eventEndPP = s;
          unparsedEntityDeclHandler(handlerArg,
                                    declEntity->name,
                                    declEntity->base,
                                    declEntity->systemId,
                                    declEntity->publicId,
                                    declEntity->notation);
          handleDefault = XML_FALSE;
        }
        else if (entityDeclHandler) {
          *eventEndPP = s;
          entityDeclHandler(handlerArg,
                            declEntity->name,
                            0,0,0,
                            declEntity->base,
                            declEntity->systemId,
                            declEntity->publicId,
                            declEntity->notation);
          handleDefault = XML_FALSE;
        }
      }