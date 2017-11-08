int main(void)
{
  CURL *curl_handle;
  CURLcode res;
  XML_Parser parser;
  struct ParserStruct state;

  /* Initialize the state structure for parsing. */
  memset(&state, 0, sizeof(struct ParserStruct));
  state.ok = 1;

  /* Initialize a namespace-aware parser. */
  parser = XML_ParserCreateNS(NULL, '\0');
  XML_SetUserData(parser, &state);
  XML_SetElementHandler(parser, startElement, endElement);
  XML_SetCharacterDataHandler(parser, characterDataHandler);

  /* Initialize a libcurl handle. */
  curl_global_init(CURL_GLOBAL_ALL ^ CURL_GLOBAL_SSL);
  curl_handle = curl_easy_init();
  curl_easy_setopt(curl_handle, CURLOPT_URL,
                   "http://www.w3schools.com/xml/simple.xml");
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, parseStreamCallback);
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)parser);

  printf("Depth   Characters   Closing Tag\n");

  /* Perform the request and any follow-up parsing. */
  res = curl_easy_perform(curl_handle);
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else if(state.ok) {
    /* Expat requires one final call to finalize parsing. */
    if(XML_Parse(parser, NULL, 0, 1) == 0) {
      int error_code = XML_GetErrorCode(parser);
      fprintf(stderr, "Finalizing parsing failed with error code %d (%s).\n",
              error_code, XML_ErrorString(error_code));
    }
    else {
      printf("                     --------------\n");
      printf("                     %lu tags total\n", state.tags);
    }
  }

  /* Clean up. */
  free(state.characters.memory);
  XML_ParserFree(parser);
  curl_easy_cleanup(curl_handle);
  curl_global_cleanup();

  return 0;
}