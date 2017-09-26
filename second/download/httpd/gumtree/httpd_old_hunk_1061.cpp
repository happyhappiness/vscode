		fprintf(stderr, "Completed %ld requests\n", done);
		fflush(stderr);
	    }
	    c->done = apr_time_now();
	    s.read = c->read;
	    s.starttime = c->start;
	    s.ctime = (c->connect - c->start) / 1000;
	    s.waittime = (c->beginread - c->endwrite) / 1000;
	    s.time = (c->done - c->start) / 1000;
	    stats[done++] = s;
	}
	c->keepalive = 0;
	c->length = 0;
	c->gotheader = 0;
	c->cbx = 0;
