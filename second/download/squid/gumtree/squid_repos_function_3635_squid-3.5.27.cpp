int
ConnStateData::pipelinePrefetchMax() const
{
    // TODO: Support pipelined requests through pinned connections.
    if (pinning.pinned)
        return 0;
    return Config.pipeline_max_prefetch;
}