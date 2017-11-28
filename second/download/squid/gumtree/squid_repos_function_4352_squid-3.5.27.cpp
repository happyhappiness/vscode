void
Helper::Reply::parse(char *buf, size_t len)
{
    debugs(84, 3, "Parsing helper buffer");
    // check we have something to parse
    if (!buf || len < 1) {
        // empty line response was the old URL-rewriter interface ERR response.
        result = Helper::Error;
        // for now ensure that legacy handlers are not presented with NULL strings.
        debugs(84, 3, "Reply length is smaller than 1 or none at all ");
        other_.init(1,1);
        other_.terminate();
        return;
    }

    char *p = buf;
    bool sawNA = false;

    // optimization: do not consider parsing result code if the response is short.
    // URL-rewriter may return relative URLs or empty response for a large portion
    // of its replies.
    if (len >= 2) {
        debugs(84, 3, "Buff length is larger than 2");
        // some helper formats (digest auth, URL-rewriter) just send a data string
        // we must also check for the ' ' character after the response token (if anything)
        if (!strncmp(p,"OK",2) && (len == 2 || p[2] == ' ')) {
            debugs(84, 3, "helper Result = OK");
            result = Helper::Okay;
            p+=2;
        } else if (!strncmp(p,"ERR",3) && (len == 3 || p[3] == ' ')) {
            debugs(84, 3, "helper Result = ERR");
            result = Helper::Error;
            p+=3;
        } else if (!strncmp(p,"BH",2) && (len == 2 || p[2] == ' ')) {
            debugs(84, 3, "helper Result = BH");
            result = Helper::BrokenHelper;
            p+=2;
        } else if (!strncmp(p,"TT ",3)) {
            // NTLM challenge token
            result = Helper::TT;
            p+=3;
            // followed by an auth token
            char *w1 = strwordtok(NULL, &p);
            if (w1 != NULL) {
                MemBuf authToken;
                authToken.init();
                authToken.append(w1, strlen(w1));
                notes.add("token",authToken.content());
            } else {
                // token field is mandatory on this response code
                result = Helper::BrokenHelper;
                notes.add("message","Missing 'token' data");
            }

        } else if (!strncmp(p,"AF ",3)) {
            // NTLM/Negotate OK response
            result = Helper::Okay;
            p+=3;
            // followed by:
            //  an optional auth token and user field
            // or, an optional username field
            char *w1 = strwordtok(NULL, &p);
            char *w2 = strwordtok(NULL, &p);
            if (w2 != NULL) {
                // Negotiate "token user"
                MemBuf authToken;
                authToken.init();
                authToken.append(w1, strlen(w1));
                notes.add("token",authToken.content());

                MemBuf user;
                user.init();
                user.append(w2,strlen(w2));
                notes.add("user",user.content());

            } else if (w1 != NULL) {
                // NTLM "user"
                MemBuf user;
                user.init();
                user.append(w1,strlen(w1));
                notes.add("user",user.content());
            }
        } else if (!strncmp(p,"NA ",3)) {
            // NTLM fail-closed ERR response
            result = Helper::Error;
            p+=3;
            sawNA=true;
        }

        for (; xisspace(*p); ++p); // skip whitespace
    }

    const mb_size_t blobSize = (buf+len-p);
    other_.init(blobSize+1, blobSize+1);
    other_.append(p, blobSize); // remainders of the line.

    // NULL-terminate so the helper callback handlers do not buffer-overrun
    other_.terminate();

    // Hack for backward-compatibility: Do not parse for kv-pairs on NA response
    if (!sawNA)
        parseResponseKeys();

    // Hack for backward-compatibility: BH and NA used to be a text message...
    if (other().hasContent() && (sawNA || result == Helper::BrokenHelper)) {
        notes.add("message",other().content());
        modifiableOther().clean();
    }
}