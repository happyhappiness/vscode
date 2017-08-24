{
        startDoctypeDeclHandler(handlerArg, doctypeName, doctypeSysid,
                                doctypePubid, 1);
        doctypeName = NULL;
        poolClear(&tempPool);
        handleDefault = XML_FALSE;
      }