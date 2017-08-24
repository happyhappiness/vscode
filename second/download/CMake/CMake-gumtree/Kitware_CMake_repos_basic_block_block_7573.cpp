{
  if (parser == NULL)
    return;
  assert(status != NULL);
  *status = parser->m_parsingStatus;
}