int64_t
ConnStateData::mayNeedToReadMoreBody() const
{
    if (!bodyPipe)
        return 0; // request without a body or read/produced all body bytes

    if (!bodyPipe->bodySizeKnown())
        return -1; // probably need to read more, but we cannot be sure

    const int64_t needToProduce = bodyPipe->unproducedSize();
    const int64_t haveAvailable = static_cast<int64_t>(in.buf.length());

    if (needToProduce <= haveAvailable)
        return 0; // we have read what we need (but are waiting for pipe space)

    return needToProduce - haveAvailable;
}