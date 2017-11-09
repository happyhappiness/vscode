int litmatch_array(const char *string, const char*const *texts, int where)
{
    const uchar *s = (const uchar*)string;
    const uchar*const *a = (const uchar* const*)texts;
    const uchar *text;

    if (where > 0)
	text = trailing_N_elements(&a, where);
    else
	text = *a++;
    if (!text)
	return FALSE;

    return doliteral(s, text, a) == TRUE;
}