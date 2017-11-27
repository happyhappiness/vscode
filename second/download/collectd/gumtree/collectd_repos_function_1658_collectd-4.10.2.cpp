static char *
uuid_get_from_file(const char *path)
{
    FILE *file;
    char uuid[UUID_PRINTABLE_NORMAL_LENGTH+1];

    if (!(file = fopen(path, "r"))) {
        return NULL;
    }

    if (!fgets(uuid, sizeof(uuid), file)) {
        fclose(file);
        return NULL;
    }
    fclose(file);

    return strdup (uuid);
}