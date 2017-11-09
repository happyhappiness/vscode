static void handleCharacters(Context *context,
                             const xmlChar *chars,
                             int length)
{
  if(context->addTitle)
    context->title.append((char *)chars, length);
}