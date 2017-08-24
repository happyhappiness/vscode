{
        startDoctypeDeclHandler(handlerArg, doctypeName,
                                doctypeSysid, doctypePubid, 0);
        poolClear(&tempPool);
        handleDefault = XML_FALSE;
      }