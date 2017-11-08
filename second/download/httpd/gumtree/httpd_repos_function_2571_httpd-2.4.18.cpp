const char *h2_h2_err_description(unsigned int h2_error)
{
    if (h2_error < (sizeof(h2_err_descr)/sizeof(h2_err_descr[0]))) {
        return h2_err_descr[h2_error];
    }
    return "unknown http/2 errotr code";
}