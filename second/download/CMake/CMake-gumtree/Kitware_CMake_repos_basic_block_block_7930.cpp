{
        *eventEndPP = s;
        entityDeclHandler(handlerArg,
                          declEntity->name,
                          declEntity->is_param,
                          0,0,
                          declEntity->base,
                          declEntity->systemId,
                          declEntity->publicId,
                          0);
        handleDefault = XML_FALSE;
      }