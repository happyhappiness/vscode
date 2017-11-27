static int tcsv_read (user_data_t *ud) {
    instance_definition_t *id;
    id = ud->data;

    if (id->tail == NULL)
    {
        id->tail = cu_tail_create (id->path);
        if (id->tail == NULL)
        {
            ERROR ("tail_csv plugin: cu_tail_create (\"%s\") failed.",
                    id->path);
            return (-1);
        }
    }

    while (42)
    {
        char buffer[1024];
        size_t buffer_len;
        int status;

        status = cu_tail_readline (id->tail, buffer, (int) sizeof (buffer));
        if (status != 0)
        {
            ERROR ("tail_csv plugin: File \"%s\": cu_tail_readline failed "
                    "with status %i.", id->path, status);
            return (-1);
        }

        buffer_len = strlen (buffer);
        if (buffer_len == 0)
            break;

        tcsv_read_buffer (id, buffer, buffer_len);
    }

    return (0);
}