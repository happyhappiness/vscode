{
        storedEncName = poolStoreString(
          &temp2Pool, encoding, encodingName,
          encodingName + XmlNameLength(encoding, encodingName));
        if (!storedEncName)
          return XML_ERROR_NO_MEMORY;
      }