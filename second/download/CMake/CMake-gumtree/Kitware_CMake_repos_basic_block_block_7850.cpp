(tok == XML_TOK_BOM) {
    s = next;
    tok = XmlPrologTok(encoding, s, end, &next);
  }