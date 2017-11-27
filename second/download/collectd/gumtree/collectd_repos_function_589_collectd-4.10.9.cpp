const char *opcode_str (int o)
{
    static char buf[30];
    switch (o) {
    case 0:
	return "Query";
	break;
    case 1:
	return "Iquery";
	break;
    case 2:
	return "Status";
	break;
    case 4:
	return "Notify";
	break;
    case 5:
	return "Update";
	break;
    default:
	ssnprintf(buf, sizeof (buf), "Opcode%d", o);
	return buf;
    }
    /* NOTREACHED */
}