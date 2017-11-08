int poptStrippedArgv(poptContext con, int argc, char **argv)
{
    int i,j=1, numargs=argc;
    
    for(i=1; i<argc; i++) {
	if(PBM_ISSET(i, con->arg_strip)) {
	    numargs--;
	}
    }
    
    for(i=1; i<argc; i++) {
	if(PBM_ISSET(i, con->arg_strip)) {
	    continue;
	} else {
	    if(j<numargs) {
		argv[j++]=argv[i];
	    } else {
		argv[j++]='\0';
	    }
	}
    }
    
    return(numargs);
}