void
getustr(RPC_UNICODE_STRING *string)
{

    string->length = (uint16_t)((p[bpos]<<0) | (p[bpos+1]<<8));
    string->maxlength = (uint16_t)((p[bpos+2]<<0) | (p[bpos+2+1]<<8));
    string->pointer = (uint32_t)((p[bpos+4]<<0) | (p[bpos+4+1]<<8) | (p[bpos+4+2]<<16) | (p[bpos+4+3]<<24));
    bpos = bpos+8;

}