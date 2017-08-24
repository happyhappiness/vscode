{
          declEntity->textPtr = poolStart(&dtd->entityValuePool);
          declEntity->textLen = (int)(poolLength(&dtd->entityValuePool));
          poolFinish(&dtd->entityValuePool);
          if (entityDeclHandler) {
            *eventEndPP = s;
            entityDeclHandler(handlerArg,
                              declEntity->name,
                              declEntity->is_param,
                              declEntity->textPtr,
                              declEntity->textLen,
                              curBase, 0, 0, 0);
            handleDefault = XML_FALSE;
          }
        }