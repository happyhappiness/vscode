{
          if (startElementHandler)
            *eventPP = *eventEndPP;
          endElementHandler(handlerArg, name.str);
          noElmHandlers = XML_FALSE;
        }