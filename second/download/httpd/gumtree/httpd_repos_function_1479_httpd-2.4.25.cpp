static int sort_by_quality(const void *left, const void *rite)
{
    return (int) (((misspelled_file *) left)->quality)
        - (int) (((misspelled_file *) rite)->quality);
}