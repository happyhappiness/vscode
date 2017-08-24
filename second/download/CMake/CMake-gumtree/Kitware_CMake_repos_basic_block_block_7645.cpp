{
        int len;
        const char *rawName;
        TAG *tag = tagStack;
        tagStack = tag->parent;
        tag->parent = freeTagList;
        freeTagList = tag;
        rawName = s + enc->minBytesPerChar*2;
        len = XmlNameLength(enc, rawName);
        if (len != tag->rawNameLength
            || memcmp(tag->rawName, rawName, len) != 0) {
          *eventPP = rawName;
          return XML_ERROR_TAG_MISMATCH;
        }
        --tagLevel;
        if (endElementHandler) {
          const XML_Char *localPart;
          const XML_Char *prefix;
          XML_Char *uri;
          localPart = tag->name.localPart;
          if (ns && localPart) {
            /* localPart and prefix may have been overwritten in
               tag->name.str, since this points to the binding->uri
               buffer which gets re-used; so we have to add them again
            */
            uri = (XML_Char *)tag->name.str + tag->name.uriLen;
            /* don't need to check for space - already done in storeAtts() */
            while (*localPart) *uri++ = *localPart++;
            prefix = (XML_Char *)tag->name.prefix;
            if (ns_triplets && prefix) {
              *uri++ = namespaceSeparator;
              while (*prefix) *uri++ = *prefix++;
             }
            *uri = XML_T('\0');
          }
          endElementHandler(handlerArg, tag->name.str);
        }
        else if (defaultHandler)
          reportDefault(parser, enc, s, next);
        while (tag->bindings) {
          BINDING *b = tag->bindings;
          if (endNamespaceDeclHandler)
            endNamespaceDeclHandler(handlerArg, b->prefix->name);
          tag->bindings = tag->bindings->nextTagBinding;
          b->nextTagBinding = freeBindingList;
          freeBindingList = b;
          b->prefix->binding = b->prevPrefixBinding;
        }
        if (tagLevel == 0)
          return epilogProcessor(parser, next, end, nextPtr);
      }