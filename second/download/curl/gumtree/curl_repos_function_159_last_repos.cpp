static void StartElement(void *voidContext,
                         const xmlChar *name,
                         const xmlChar **attributes)
{
  Context *context = (Context *)voidContext;

  if(COMPARE((char *)name, "TITLE")) {
    context->title = "";
    context->addTitle = true;
  }
  (void) attributes;
}