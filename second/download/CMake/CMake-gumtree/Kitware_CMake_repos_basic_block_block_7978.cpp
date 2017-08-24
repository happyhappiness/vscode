{
        doctypeName = poolStoreString(&tempPool, enc, s, next);
        if (!doctypeName)
          return XML_ERROR_NO_MEMORY;
        poolFinish(&tempPool);
        doctypePubid = NULL;
        handleDefault = XML_FALSE;
      }