void
ESIInclude::subRequestDone (ESIStreamContext::Pointer stream, bool success)
{
    assert (this);

    if (!dataNeeded())
        return;

    if (stream == src) {
        debugs(86, 3, "ESIInclude::subRequestDone: " << srcurl);

        if (success) {
            /* copy the lead segment */
            debugs(86, 3, "ESIIncludeSubRequestDone: Src OK - include PASSED.");
            assert (!srccontent.getRaw());
            ESISegment::ListTransfer (stream->localbuffer, srccontent);
            /* we're done! */
            flags.finished = 1;
        } else {
            /* Fail if there is no alt being retrieved */
            debugs(86, 3, "ESIIncludeSubRequestDone: Src FAILED");

            if (!(alt.getRaw() || altcontent.getRaw())) {
                debugs(86, 3, "ESIIncludeSubRequestDone: Include FAILED - No ALT");
                flags.failed = 1;
            } else if (altcontent.getRaw()) {
                debugs(86, 3, "ESIIncludeSubRequestDone: Include PASSED - ALT already Complete");
                /* ALT was already retrieved, we are done */
                flags.finished = 1;
            }
        }

        src = NULL;
    } else if (stream == alt) {
        debugs(86, 3, "ESIInclude::subRequestDone: " << alturl);

        if (success) {
            debugs(86, 3, "ESIIncludeSubRequestDone: ALT OK.");
            /* copy the lead segment */
            assert (!altcontent.getRaw());
            ESISegment::ListTransfer (stream->localbuffer, altcontent);
            /* we're done! */

            if (!(src.getRaw() || srccontent.getRaw())) {
                /* src already failed, kick ESI processor */
                debugs(86, 3, "ESIIncludeSubRequestDone: Include PASSED - SRC already failed.");
                flags.finished = 1;
            }
        } else {
            if (!(src.getRaw() || srccontent.getRaw())) {
                debugs(86, 3, "ESIIncludeSubRequestDone: ALT FAILED, Include FAILED - SRC already failed");
                /* src already failed */
                flags.failed = 1;
            }
        }

        alt = NULL;
    } else {
        fatal ("ESIIncludeSubRequestDone: non-owned stream found!\n");
    }

    if (flags.finished || flags.failed) {
        /* Kick ESI Processor */
        debugs (86, 5, "ESIInclude " << this <<
                " SubRequest " << stream.getRaw() <<
                " completed, kicking processor , status " <<
                (flags.finished ? "OK" : "FAILED"));
        /* There is a race condition - and we have no reproducible test case -
         * during a subrequest the parent will get set to NULL, which is not
         * meant to be possible. Rather than killing squid, we let it leak
         * memory but complain in the log.
         *
         * Someone wanting to debug this could well start by running squid with
         * a hardware breakpoint set to this location.
         * Its probably due to parent being set to null - by a call to
         * 'this.finish' while the subrequest is still not completed.
         */
        if (parent.getRaw() == NULL) {
            debugs (86, 0, "ESIInclude::subRequestDone: Sub request completed "
                    "after finish() called and parent unlinked. Unable to "
                    "continue handling the request, and may be memory leaking. "
                    "See http://www.squid-cache.org/bugs/show_bug.cgi?id=951 - we "
                    "are looking for a reproducible test case. This will require "
                    "an ESI template with includes, probably with alt-options, "
                    "and we're likely to need traffic dumps to allow us to "
                    "reconstruct the exact tcp handling sequences to trigger this "
                    "rather elusive bug.");
            return;
        }
        assert (parent.getRaw());

        if (!flags.failed) {
            sent = true;
            parent->provideData (srccontent.getRaw() ? srccontent:altcontent,this);

            if (srccontent.getRaw())
                srccontent = NULL;
            else
                altcontent = NULL;
        } else if (flags.onerrorcontinue) {
            /* render nothing but inform of completion */

            if (!sent) {
                sent = true;
                parent->provideData (new ESISegment, this);
            } else
                assert (0);
        } else
            parent->fail(this, "esi:include could not be completed.");
    }
}