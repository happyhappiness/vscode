static void poptStripArg(poptContext con, int which)
{
    if(con->arg_strip == NULL) {
	con->arg_strip = PBM_ALLOC(con->optionStack[0].argc);
    }
    PBM_SET(which, con->arg_strip);
}