int
Read_usersfile(const char *path, usersfile * uf)
{
    FILE *fp;
    struct stat FileBuf;
    char buf[1024];

    free_names(uf);

    if (NULL == path) {
        path = uf->path;
    } else {
        if (uf->path)
            free(uf->path);
        uf->path = xstrdup(path);
    }

    /* Open the users file. Report any errors. */
    fp = fopen(path, "r");
    if (NULL == fp) {
        uf->LMT = 0;
        if (errno == ENOENT)
            return 0;
        syslog(LOG_ERR, "%s: %s", path, strerror(errno));
        return 1;
    }
    /* Stat the file. If it does not exist, save the size as zero.
     * Clear the allowed user string. Return. */
    if (fstat(fileno(fp), &FileBuf) < 0) {
        syslog(LOG_ERR, "%s: %s", path, strerror(errno));
        fclose(fp);
        return 1;
    }
    /* If it exists, save the modification time and size */
    uf->LMT = FileBuf.st_mtime;

    /* Handle the special case of a zero length file */
    if (FileBuf.st_size == 0) {
        fclose(fp);
        return 0;
    }

    /*
     * Read the file into memory
     * XXX assumes one username per input line
     */
    while (fgets(buf, 1024, fp) != NULL) {
        /* ensure no names longer than our limit */
        buf[NAMELEN] = '\0';
        /* skip bad input lines */
        if (NULL == strtok(buf, "\r\n"))
            continue;
        /* grow the list if necessary */
        if (0 == uf->Alloc) {
            uf->Alloc = 256;
            uf->names = static_cast<char**>(calloc(uf->Alloc, sizeof(*uf->names)));
        } else if (uf->Inuse == uf->Alloc) {
            uf->Alloc = uf->Alloc << 1;
            uf->names = static_cast<char**>(realloc(uf->names, uf->Alloc * sizeof(*uf->names)));
            /* zero out the newly allocated memory */
            memset(&uf->names[uf->Alloc >> 1],
                   '\0',
                   (uf->Alloc >> 1) * sizeof(*uf->names));
        }
        uf->names[uf->Inuse] = xstrdup(buf);
        ++uf->Inuse;
    }
    fclose(fp);
    fp = NULL;

    /* sort the names for searching */
    qsort(uf->names, uf->Inuse, sizeof(*uf->names), name_cmp);

    return 0;
}