/* --------------------------------------------------------- */



/* simple little function to perror and exit */



static void err(char *s)

{

    if (errno) {

    	perror(s);

    }

    else {

	printf("%s", s);

    }

    exit(errno);

}



/* --------------------------------------------------------- */



/* write out request to a connection - assumes we can write 

   (small) request out in one go into our new socket buffer  */



static void write_request(struct connection *c)

{

    gettimeofday(&c->connect, 0);

    /* XXX: this could use writev for posting -- more efficient -djg */

    write(c->fd, request, reqlen);

    if (posting) {

        write(c->fd,postdata, postlen);

        totalposted += (reqlen + postlen); 

    }



    c->state = STATE_READ;

    FD_SET(c->fd, &readbits);

    FD_CLR(c->fd, &writebits);

}



/* --------------------------------------------------------- */

