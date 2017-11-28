static void
build_translation_table(void)
{
    int count;

    for (count = 0; count < 40; count++) {
        switch (count) {
        case OBJID:
            translation_table[count] = TYPE_OBJID;
            break;
        case OCTETSTR:
            translation_table[count] = TYPE_OCTETSTR;
            break;
        case INTEGER:
            translation_table[count] = TYPE_INTEGER;
            break;
        case NETADDR:
            translation_table[count] = TYPE_IPADDR;
            break;
        case IPADDR:
            translation_table[count] = TYPE_IPADDR;
            break;
        case COUNTER:
            translation_table[count] = TYPE_COUNTER;
            break;
        case GAUGE:
            translation_table[count] = TYPE_GAUGE;
            break;
        case TIMETICKS:
            translation_table[count] = TYPE_TIMETICKS;
            break;
        case SNMP_OPAQUE:
            translation_table[count] = TYPE_OPAQUE;
            break;
        case NUL:
            translation_table[count] = TYPE_NULL;
            break;
        default:
            translation_table[count] = TYPE_OTHER;
            break;
        }
    }
}