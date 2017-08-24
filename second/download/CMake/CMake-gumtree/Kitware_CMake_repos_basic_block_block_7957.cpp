(!dtd->standalone &&
                notStandaloneHandler &&
                !notStandaloneHandler(handlerArg))
              return XML_ERROR_NOT_STANDALONE;