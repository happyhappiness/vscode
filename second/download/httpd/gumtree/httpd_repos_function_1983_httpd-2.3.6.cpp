static void copy_to_holdbuf(sed_eval_t *eval, const char* sz)
{
    eval->hspend = eval->holdbuf;
    append_to_holdbuf(eval, sz);
}