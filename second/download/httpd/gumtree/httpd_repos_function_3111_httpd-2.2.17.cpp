const XML_Feature * XMLCALL
XML_GetFeatureList(void)
{
  static XML_Feature features[] = {
    {XML_FEATURE_SIZEOF_XML_CHAR,  XML_L("sizeof(XML_Char)"), 0},
    {XML_FEATURE_SIZEOF_XML_LCHAR, XML_L("sizeof(XML_LChar)"), 0},
#ifdef XML_UNICODE
    {XML_FEATURE_UNICODE,          XML_L("XML_UNICODE"), 0},
#endif
#ifdef XML_UNICODE_WCHAR_T
    {XML_FEATURE_UNICODE_WCHAR_T,  XML_L("XML_UNICODE_WCHAR_T"), 0},
#endif
#ifdef XML_DTD
    {XML_FEATURE_DTD,              XML_L("XML_DTD"), 0},
#endif
#ifdef XML_CONTEXT_BYTES
    {XML_FEATURE_CONTEXT_BYTES,    XML_L("XML_CONTEXT_BYTES"),
     XML_CONTEXT_BYTES},
#endif
#ifdef XML_MIN_SIZE
    {XML_FEATURE_MIN_SIZE,         XML_L("XML_MIN_SIZE"), 0},
#endif
    {XML_FEATURE_END,              NULL, 0}
  };

  features[0].value = sizeof(XML_Char);
  features[1].value = sizeof(XML_LChar);
  return features;
}