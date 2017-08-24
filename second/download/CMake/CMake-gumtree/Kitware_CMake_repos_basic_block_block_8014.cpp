{
          enum XML_Error result;
          const XML_Char *textEnd = entity->textPtr + entity->textLen;
          entity->open = XML_TRUE;
          result = appendAttributeValue(parser, internalEncoding, isCdata,
                                        (char *)entity->textPtr,
                                        (char *)textEnd, pool);
          entity->open = XML_FALSE;
          if (result)
            return result;
        }