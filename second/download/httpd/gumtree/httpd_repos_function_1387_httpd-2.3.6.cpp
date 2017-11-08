static int level_cmp(var_rec *var1, var_rec *var2)
{
    /* Levels are only comparable between matching media types */

    if (var1->is_pseudo_html && !var2->is_pseudo_html) {
        return 0;
    }

    if (!var1->is_pseudo_html && strcmp(var1->mime_type, var2->mime_type)) {
        return 0;
    }
    /* The result of the above if statements is that, if we get to
     * here, both variants have the same mime_type or both are
     * pseudo-html.
     */

    /* Take highest level that matched, if either did match. */

    if (var1->level_matched > var2->level_matched) {
        return 1;
    }
    if (var1->level_matched < var2->level_matched) {
        return -1;
    }

    /* Neither matched.  Take lowest level, if there's a difference. */

    if (var1->level < var2->level) {
        return 1;
    }
    if (var1->level > var2->level) {
        return -1;
    }

    /* Tied */

    return 0;
}