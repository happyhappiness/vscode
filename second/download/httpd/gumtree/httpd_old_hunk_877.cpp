		ap_log_error(APLOG_MARK, APLOG_ERR, r->server,

			     "proxy gc: unlink(%s)", filename);

	}

	else

#endif

	{

	    curblocks -= fent->len >> 10;

	    curbytes -= fent->len & 0x3FF;

	    if (curbytes < 0) {

		curbytes += 1024;

		curblocks--;

	    }

	    if (curblocks < cachesize || curblocks + curbytes <= cachesize)

		break;

	}

    }

    ap_unblock_alarms();

}



static int sub_garbage_coll(request_rec *r, array_header *files,

			  const char *cachebasedir, const char *cachesubdir)

{

