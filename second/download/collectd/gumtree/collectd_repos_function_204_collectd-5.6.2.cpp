static void escape_graphite_string(char *buffer, char escape_char) {
  assert(strchr(GRAPHITE_FORBIDDEN, escape_char) == NULL);

  for (char *head = buffer + strcspn(buffer, GRAPHITE_FORBIDDEN); *head != '\0';
       head += strcspn(head, GRAPHITE_FORBIDDEN))
    *head = escape_char;
}