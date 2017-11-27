static char *
uuid_get_from_file(const char *path)
{
    FILE *file;
    char uuid[UUID_PRINTABLE_NORMAL_LENGTH + 1] = "";

    file = fopen (path, "r");
    if (file == NULL)
        return NULL;

    if (!fgets(uuid, sizeof(uuid), file)) {
        fclose(file);
        return NULL;
    }
    fclose(file);
    strstripnewline (uuid);

    return strdup (uuid);
}