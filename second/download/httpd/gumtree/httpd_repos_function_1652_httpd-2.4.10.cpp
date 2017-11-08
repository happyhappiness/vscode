static apr_status_t array_getch(char *ch, void *param)
{
    array_contents_t *ml = (array_contents_t *) param;
    char **tab = (char **) ml->contents->elts;

    while (ml->char_index >= ml->length) {
        if (ml->index >= ml->contents->nelts) {
            /* maybe update */
            if (ml->next && ml->next->getch && next_one(ml)) {
                apr_status_t rc = ml->next->getch(ch, ml->next->param);
                if (*ch==LF)
                    ml->next->line_number++;
                return rc;
            }
            return APR_EOF;
        }
        ml->index++;
        ml->char_index = 0;
        ml->length = ml->index >= ml->contents->nelts ?
            0 : strlen(tab[ml->index]);
    }

    *ch = tab[ml->index][ml->char_index++];
    return APR_SUCCESS;
}