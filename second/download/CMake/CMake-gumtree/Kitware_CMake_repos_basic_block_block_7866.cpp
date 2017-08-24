{
        if (elementDeclHandler)
          handleDefault = XML_FALSE;
        dtd->scaffLevel--;
        dtd->scaffold[dtd->scaffIndex[dtd->scaffLevel]].quant = quant;
        if (dtd->scaffLevel == 0) {
          if (!handleDefault) {
            XML_Content *model = build_model(parser);
            if (!model)
              return XML_ERROR_NO_MEMORY;
            *eventEndPP = s;
            elementDeclHandler(handlerArg, declElementType->name, model);
          }
          dtd->in_eldecl = XML_FALSE;
          dtd->contentStringLen = 0;
        }
      }