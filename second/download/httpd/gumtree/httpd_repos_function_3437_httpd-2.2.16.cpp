const char *nameof(const char *fullpath)
{
    const char *name;
    const char *ext;

    name = jlibtool_basename(fullpath);
    ext = strrchr(name, '.');

    if (ext) {
        char *trimmed;
        trimmed = malloc(ext - name + 1);
        strncpy(trimmed, name, ext - name);
        trimmed[ext-name] = 0;
        return trimmed;
    }

    return name;
}