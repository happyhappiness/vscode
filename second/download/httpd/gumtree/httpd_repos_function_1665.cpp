static int is_true(const char *w)
{
    if (strcasecmp(w, "on") == 0 || 
        strcasecmp(w, "1") == 0 ||
        strcasecmp(w, "true") == 0)
    {
        return 1;
    }

    return 0;
}