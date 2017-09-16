		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

			     "proxy gc: unlink(%s)", filename);

	}

	else

#endif

	{

	    sub_long61(&curbytes, ROUNDUP2BLOCKS(fent->len));

	    if (cmp_long61(&curbytes, &cachesize) < 0)

		break;

	}

    }



    ap_log_error(APLOG_MARK, APLOG_DEBUG|APLOG_NOERRNO, r->server,

			 "proxy GC: Cache is %ld%% full (%d deleted)",

			 (long)(((curbytes.upper<<20)|(curbytes.lower>>10))*100/conf->space), i);

    ap_unblock_alarms();

}



static int sub_garbage_coll(request_rec *r, array_header *files,

			  const char *cachebasedir, const char *cachesubdir)

{

