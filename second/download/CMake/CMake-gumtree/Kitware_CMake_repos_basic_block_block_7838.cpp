(prologState.inEntityValue) {
    processor = entityValueInitProcessor;
    return entityValueInitProcessor(parser, s, end, nextPtr);
  }
  else {
    processor = externalParEntProcessor;
    return externalParEntProcessor(parser, s, end, nextPtr);
  }