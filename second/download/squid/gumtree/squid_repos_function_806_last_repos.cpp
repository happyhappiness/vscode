static void
free_string(char **var)
{
    safe_free(*var);
}