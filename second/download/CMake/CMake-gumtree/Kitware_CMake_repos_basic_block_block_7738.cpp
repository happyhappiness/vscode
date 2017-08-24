(i = 0; i < nDefaultAtts; i++) {
    const DEFAULT_ATTRIBUTE *da = elementType->defaultAtts + i;
    if (!(da->id->name)[-1] && da->value) {
      if (da->id->prefix) {
        if (da->id->xmlns) {
          enum XML_Error result = addBinding(parser, da->id->prefix, da->id,
                                             da->value, bindingsPtr);
          if (result)
            return result;
        }
        else {
          (da->id->name)[-1] = 2;
          nPrefixes++;
          appAtts[attIndex++] = da->id->name;
          appAtts[attIndex++] = da->value;
        }
      }
      else {
        (da->id->name)[-1] = 1;
        appAtts[attIndex++] = da->id->name;
        appAtts[attIndex++] = da->value;
      }
    }
  }