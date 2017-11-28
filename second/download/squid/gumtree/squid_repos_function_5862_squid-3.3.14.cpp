void
Snmp::Var::setValue(const void* value, int length, int aType)
{
    clearValue();
    if (value != NULL) {
        Must(length > 0 && aType > 0);
        val.string = static_cast<u_char*>(xmalloc(length));
        memcpy(val.string, value, length);
    }
    val_len = length;
    type = aType;
}