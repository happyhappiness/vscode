void init_count_chars(count_chars *cc)
{
    cc->vals = (const char**)malloc(PATH_MAX);
    cc->num = 0;
}