{
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