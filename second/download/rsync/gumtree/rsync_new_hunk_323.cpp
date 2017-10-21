      return -1;

    if (ret == -1 && got_select) {
	    /* hmmm, we got a write select on the fd and then failed to write.
	       Why doesn't that mean that the fd is dead? It doesn't on some
	       systems it seems (eg. IRIX) */
	    u_sleep(1000);
#if 0
	    fprintf(FERROR,"write exception\n");
	    exit_cleanup(1);
#endif
    }

