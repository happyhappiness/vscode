void
HttpHeader::updateWarnings()
{
    int count = 0;
    HttpHeaderPos pos = HttpHeaderInitPos;

    // RFC 7234, section 4.3.4: delete 1xx warnings and retain 2xx warnings
    while (HttpHeaderEntry *e = getEntry(&pos)) {
        if (e->id == Http::HdrType::WARNING && (e->getInt()/100 == 1) )
            delAt(pos, count);
    }
}