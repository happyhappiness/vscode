int ska_base64_encode_len(int len)
{
    return ((len+2)/3*4)+1;
}