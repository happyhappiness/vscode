    EBIT_CLR(entry->flags, ENTRY_FWD_HDR_WAIT);

    HttpReply *reply = new HttpReply;
    entry->buffer();
    reply->setHeaders(Http::scOkay, "Gatewaying", mime_type, -1, -1, -2);
    if (mime_enc)
        reply->header.putStr(Http::HdrType::CONTENT_ENCODING, mime_enc);

    entry->replaceHttpReply(reply);
    gopherState->reply_ = reply;
}

/**
 * Parse a gopher request into components.  By Anawat.
 */
static void
gopher_request_parse(const HttpRequest * req, char *type_id, char *request)
{
    ::Parser::Tokenizer tok(req->url.path());

    if (request)
        *request = 0;

    tok.skip('/'); // ignore failures? path could be ab-empty

    if (tok.atEnd()) {
        *type_id = GOPHER_DIRECTORY;
        return;
    }

    static const CharacterSet anyByte("UTF-8",0x00, 0xFF);

    SBuf typeId;
    (void)tok.prefix(typeId, anyByte, 1); // never fails since !atEnd()
    *type_id = typeId[0];

    if (request) {
        SBufToCstring(request, tok.remaining().substr(0, MAX_URL-1));
        /* convert %xx to char */
        rfc1738_unescape(request);
    }
}

/**
 * Parse the request to determine whether it is cachable.
 *
 * \param req   Request data.
 * \retval 0    Not cachable.
 * \retval 1    Cachable.
 */
int
gopherCachable(const HttpRequest * req)
{
    int cachable = 1;
    char type_id;
