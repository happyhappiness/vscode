static int psprintf_flush(apr_vformatter_buff_t *vbuff)
{
    struct psprintf_data *ps = (struct psprintf_data *)vbuff;
    apr_size_t size;

    size = ps->vbuff.curpos - ps->mem;

    ps->size <<= 1;
    if ((ps->mem = realloc(ps->mem, ps->size)) == NULL)
        return -1;

    ps->vbuff.curpos = ps->mem + size;
    ps->vbuff.endpos = ps->mem + ps->size - 1;

    return 0;
}