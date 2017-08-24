{
      /* implicit context only set for root parser, since child
         parsers (i.e. external entity parsers) will inherit it
      */
      return setContext(parser, implicitContext);
    }