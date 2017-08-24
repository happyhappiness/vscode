{
        declEntity->systemId = poolStoreString(&dtd->pool, enc,
                                               s + enc->minBytesPerChar,
                                               next - enc->minBytesPerChar);
        if (!declEntity->systemId)
          return XML_ERROR_NO_MEMORY;
        declEntity->base = curBase;
        poolFinish(&dtd->pool);
        if (entityDeclHandler)
          handleDefault = XML_FALSE;
      }