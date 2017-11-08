static int next_one(array_contents_t * ml)
{
    if (ml->next) {
        ap_assert(ml->upper);
        *(ml->upper) = ml->next;
        return 1;
    }
    return 0;
}