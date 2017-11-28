           min_rtt  );

    return min_u;
}

char *
UrnState::getHost (String &urlpath)
{
    char * result;
    size_t p;

    /** FIXME: this appears to be parsing the URL. *very* badly. */
    /*   a proper encapsulated URI/URL type needs to clear this up. */
    if ((p=urlpath.find(':')) != String::npos) {
        result=xstrndup(urlpath.rawBuf(),p-1);
    } else {
        result = xstrndup(urlpath.rawBuf(),urlpath.size());
    }
    return result;
}

bool
UrnState::RequestNeedsMenu(HttpRequest *r)
{
    if (r->urlpath.size() < 5)
        return false;
    //now we're sure it's long enough
    return strncasecmp(r->urlpath.rawBuf(), "menu.", 5) == 0;
}

void
UrnState::updateRequestURL(HttpRequest *r, char const *newPath, const size_t newPath_len)
{
    char *new_path = xstrndup (newPath, newPath_len);
    r->urlpath = new_path;
    xfree(new_path);
}

void
UrnState::createUriResRequest (String &uri)
{
    LOCAL_ARRAY(char, local_urlres, 4096);
    char *host = getHost (uri);
    snprintf(local_urlres, 4096, "http://%s/uri-res/N2L?urn:" SQUIDSTRINGPH,
             host, SQUIDSTRINGPRINT(uri));
    safe_free(host);
    safe_free(urlres);
    urlres = xstrdup(local_urlres);
    urlres_r = HttpRequest::CreateFromUrl(urlres);
}

void
UrnState::setUriResFromRequest(HttpRequest *r)
{
    if (RequestNeedsMenu(r)) {
        updateRequestURL(r, r->urlpath.rawBuf() + 5, r->urlpath.size() - 5 );
        flags.force_menu = true;
    }

    createUriResRequest (r->urlpath);

    if (urlres_r == NULL) {
        debugs(52, 3, "urnStart: Bad uri-res URL " << urlres);
        ErrorState *err = new ErrorState(ERR_URN_RESOLVE, Http::scNotFound, r);
        err->url = urlres;
        urlres = NULL;
        errorAppendEntry(entry, err);
        return;
    }

    urlres_r->header.putStr(HDR_ACCEPT, "text/plain");
}

void
UrnState::start(HttpRequest * r, StoreEntry * e)
{
    debugs(52, 3, "urnStart: '" << e->url() << "'" );
