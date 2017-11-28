void
Rock::HeaderUpdater::noteRead(ssize_t result)
{
    debugs(47, 7, result);
    if (!result) { // EOF
        stopReading("eof");
    } else {
        Must(result > 0);
        bytesRead += result;
        readerBuffer.forceSize(readerBuffer.length() + result);
        exchangeBuffer.append(readerBuffer);
        debugs(47, 7, "accumulated " << exchangeBuffer.length());
    }

    parseReadBytes();
}