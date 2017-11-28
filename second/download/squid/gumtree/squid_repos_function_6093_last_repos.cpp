File *
File::Optional(const SBuf &filename, const FileOpeningConfig &cfg)
{
    try {
        return new File(filename, cfg);
    }
    catch (const std::exception &ex) {
        debugs(54, 5, "will not lock: " << ex.what());
    }
    return nullptr;
}