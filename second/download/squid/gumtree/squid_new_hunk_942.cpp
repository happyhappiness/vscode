                         virgin.cause : dynamic_cast<HttpRequest*>(virgin.header);
        Must(r);

        HttpReply *reply = dynamic_cast<HttpReply*>(virgin.header);

        if (const char *value = (*i)->match(r, reply, alMaster)) {
            buf.appendf("%s: %s\r\n", (*i)->key.termedBuf(), value);
            Adaptation::History::Pointer ah = request->adaptHistory(false);
            if (ah != NULL) {
                if (ah->metaHeaders == NULL)
                    ah->metaHeaders = new NotePairs;
                if (!ah->metaHeaders->hasPair((*i)->key.termedBuf(), value))
                    ah->metaHeaders->add((*i)->key.termedBuf(), value);
