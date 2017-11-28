    }

    assert(error != ERR_NONE);
    entry->reset();
    fwd->fail(new ErrorState(error, Http::scBadGateway, fwd->request));
    flags.do_next_read = false;
    serverConnection->close();
    return false; // quit on error
}

/** truncate what we read if we read too much so that writeReplyBody()
    writes no more than what we should have read */
void
