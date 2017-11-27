static void escape_graphite_string (char *buffer, char escape_char)
{
	char *head;

	assert (strchr(GRAPHITE_FORBIDDEN, escape_char) == NULL);

	for (head = buffer + strcspn(buffer, GRAPHITE_FORBIDDEN);
	     *head != '\0';
	     head += strcspn(head, GRAPHITE_FORBIDDEN))
		*head = escape_char;
}