{
    int tok;
    processor = prologProcessor;
    tok = XmlPrologTok(encoding, s, end, &next);
    return doProlog(parser, encoding, s, end, tok, next, nextPtr,
                    (XML_Bool)!ps_finalBuffer);
  }