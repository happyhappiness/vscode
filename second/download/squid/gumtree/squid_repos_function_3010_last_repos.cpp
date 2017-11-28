void
ConnStateData::afterClientWrite(size_t size)
{
    if (pipeline.empty())
        return;

    auto ctx = pipeline.front();
    if (size) {
        statCounter.client_http.kbytes_out += size;
        if (ctx->http->logType.isTcpHit())
            statCounter.client_http.hit_kbytes_out += size;
    }
    ctx->writeComplete(size);
}