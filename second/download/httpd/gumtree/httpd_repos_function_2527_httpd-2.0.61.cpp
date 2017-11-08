const XML_LChar *XML_ErrorString(int code)
{
  static const XML_LChar *message[] = {
    0,
    XML_T("out of memory"),
    XML_T("syntax error"),
    XML_T("no element found"),
    XML_T("not well-formed (invalid token)"),
    XML_T("unclosed token"),
    XML_T("unclosed token"),
    XML_T("mismatched tag"),
    XML_T("duplicate attribute"),
    XML_T("junk after document element"),
    XML_T("illegal parameter entity reference"),
    XML_T("undefined entity"),
    XML_T("recursive entity reference"),
    XML_T("asynchronous entity"),
    XML_T("reference to invalid character number"),
    XML_T("reference to binary entity"),
    XML_T("reference to external entity in attribute"),
    XML_T("xml processing instruction not at start of external entity"),
    XML_T("unknown encoding"),
    XML_T("encoding specified in XML declaration is incorrect"),
    XML_T("unclosed CDATA section"),
    XML_T("error in processing external entity reference"),
    XML_T("document is not standalone"),
    XML_T("unexpected parser state - please send a bug report")
  };
  if (code > 0 && code < sizeof(message)/sizeof(message[0]))
    return message[code];
  return 0;
}