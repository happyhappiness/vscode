    }
}

void Adaptation::Icap::ModXact::makeUsernameHeader(const HttpRequest *request, MemBuf &buf)
{
#if USE_AUTH
    if (request->auth_user_request != NULL) {
        char const *name = request->auth_user_request->username();
        if (name) {
            const char *value = TheConfig.client_username_encode ? old_base64_encode(name) : name;
            buf.Printf("%s: %s\r\n", TheConfig.client_username_header, value);
        }
    } else if (request->extacl_user.size() > 0) {
        const char *value = TheConfig.client_username_encode ? old_base64_encode(request->extacl_user.termedBuf()) : request->extacl_user.termedBuf();
        buf.Printf("%s: %s\r\n", TheConfig.client_username_header, value);
    }
#endif
}

void Adaptation::Icap::ModXact::encapsulateHead(MemBuf &icapBuf, const char *section, MemBuf &httpBuf, const HttpMsg *head)
{
    // update ICAP header
    icapBuf.Printf("%s=%d, ", section, (int) httpBuf.contentSize());

    // begin cloning
    HttpMsg::Pointer headClone;

    if (const HttpRequest* old_request = dynamic_cast<const HttpRequest*>(head)) {
        HttpRequest::Pointer new_request(new HttpRequest);
        Must(old_request->canonical);
        urlParse(old_request->method, old_request->canonical, new_request.getRaw());
        new_request->http_ver = old_request->http_ver;
        headClone = new_request.getRaw();
    } else if (const HttpReply *old_reply = dynamic_cast<const HttpReply*>(head)) {
        HttpReply::Pointer new_reply(new HttpReply);
        new_reply->sline = old_reply->sline;
        headClone = new_reply.getRaw();
    }
    Must(headClone != NULL);
    headClone->inheritProperties(head);

    HttpHeaderPos pos = HttpHeaderInitPos;
    HttpHeaderEntry* p_head_entry = NULL;
    while (NULL != (p_head_entry = head->header.getEntry(&pos)) )
        headClone->header.addEntry(p_head_entry->clone());

    // end cloning

    // remove all hop-by-hop headers from the clone
    headClone->header.delById(HDR_PROXY_AUTHENTICATE);
    headClone->header.removeHopByHopEntries();

    // pack polished HTTP header
    packHead(httpBuf, headClone.getRaw());

    // headClone unlocks and, hence, deletes the message we packed
}

void Adaptation::Icap::ModXact::packHead(MemBuf &httpBuf, const HttpMsg *head)
{
    Packer p;
    packerToMemInit(&p, &httpBuf);
    head->packInto(&p, true);
    packerClean(&p);
}

// decides whether to offer a preview and calculates its size
void Adaptation::Icap::ModXact::decideOnPreview()
{
    if (!TheConfig.preview_enable) {
        debugs(93, 5, HERE << "preview disabled by squid.conf");
        return;
    }

    const String urlPath = virginRequest().urlpath;
    size_t wantedSize;
    if (!service().wantsPreview(urlPath, wantedSize)) {
        debugs(93, 5, HERE << "should not offer preview for " << urlPath);
        return;
    }

    // we decided to do preview, now compute its size

    // cannot preview more than we can backup
