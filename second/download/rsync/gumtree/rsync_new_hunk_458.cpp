    int r;

    rx_strm.next_in = (Bytef *)buf;
    rx_strm.avail_in = len;
    r = inflateIncomp(&rx_strm);
    if (r != Z_OK) {
	rprintf(FERROR, "inflateIncomp returned %d\n", r);
	exit_cleanup(1);
    }
}

/*
 * transmit a verbatim buffer of length n followed by a token 
