{
          XML_Content * content = (XML_Content *) MALLOC(sizeof(XML_Content));
          if (!content)
            return XML_ERROR_NO_MEMORY;
          content->quant = XML_CQUANT_NONE;
          content->name = NULL;
          content->numchildren = 0;
          content->children = NULL;
          content->type = ((role == XML_ROLE_CONTENT_ANY) ?
                           XML_CTYPE_ANY :
                           XML_CTYPE_EMPTY);
          *eventEndPP = s;
          elementDeclHandler(handlerArg, declElementType->name, content);
          handleDefault = XML_FALSE;
        }