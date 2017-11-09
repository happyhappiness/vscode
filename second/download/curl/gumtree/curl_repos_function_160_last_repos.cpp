static void EndElement(void *voidContext,
                       const xmlChar *name)
{
  Context *context = (Context *)voidContext;

  if(COMPARE((char *)name, "TITLE"))
    context->addTitle = false;
}