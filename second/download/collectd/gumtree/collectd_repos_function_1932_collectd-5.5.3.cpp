static char *
uuid_parse_dmidecode(FILE *file)
{
    char line[1024];

    while (fgets (line, sizeof (line), file) != NULL)
    {
        char *fields[4];
        int fields_num;

        strstripnewline (line);

        /* Look for a line reading:
         *   UUID: XXXXXXXX-XXXX-XXXX-XXXX-XXXXXXXXXXXX
         */
        fields_num = strsplit (line, fields, STATIC_ARRAY_SIZE (fields));
        if (fields_num != 2)
            continue;

        if (strcmp("UUID:", fields[0]) != 0)
            continue;

        if (!looks_like_a_uuid (fields[1]))
            continue;

        return strdup (fields[1]);
    }
    return NULL;
}