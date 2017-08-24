(dtd->paramEntityRead) {
            if (!dtd->standalone &&
                notStandaloneHandler &&
                !notStandaloneHandler(handlerArg))
              return XML_ERROR_NOT_STANDALONE;
          }
          /* if we didn't read the foreign DTD then this means that there
             is no external subset and we must reset dtd->hasParamEntityRefs
          */
          else if (!doctypeSysid)
            dtd->hasParamEntityRefs = hadParamEntityRefs