void
FtpStateData::unhack()
{
    debugs(9, 3, HERE);

    if (old_request != NULL) {
        safe_free(old_request);
        safe_free(old_reply);
    }
}