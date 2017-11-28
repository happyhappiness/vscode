static const char *
errorFindHardText(err_type type)
{
    int i;

    for (i = 0; i < error_hard_text_count; i++)
        if (error_hard_text[i].type == type)
            return error_hard_text[i].text;

    return NULL;
}