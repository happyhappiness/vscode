{
          if (*declAttributeType == XML_T(ASCII_LPAREN)
              || (*declAttributeType == XML_T(ASCII_N)
                  && declAttributeType[1] == XML_T(ASCII_O))) {
            /* Enumerated or Notation type */
            if (!poolAppendChar(&tempPool, XML_T(ASCII_RPAREN))
                || !poolAppendChar(&tempPool, XML_T('\0')))
              return XML_ERROR_NO_MEMORY;
            declAttributeType = tempPool.start;
            poolFinish(&tempPool);
          }
          *eventEndPP = s;
          attlistDeclHandler(handlerArg, declElementType->name,
                             declAttributeId->name, declAttributeType,
                             0, role == XML_ROLE_REQUIRED_ATTRIBUTE_VALUE);
          poolClear(&tempPool);
          handleDefault = XML_FALSE;
        }