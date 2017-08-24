{
          BINDING *b = tag->bindings;
          if (endNamespaceDeclHandler)
            endNamespaceDeclHandler(handlerArg, b->prefix->name);
          tag->bindings = tag->bindings->nextTagBinding;
          b->nextTagBinding = freeBindingList;
          freeBindingList = b;
          b->prefix->binding = b->prevPrefixBinding;
        }