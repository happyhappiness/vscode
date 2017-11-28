int
main(int argc, char *argv[])
{
    int fd = -1;
    StoreMeta *metadata = NULL;

    try {
        if (argc != 2)
            throw std::runtime_error("No filename provided");

        fd = open (argv[1], O_RDONLY | O_BINARY);

        if (fd < 0)
            throw std::runtime_error("Could not open file.");

        char tempbuf[SM_PAGE_SIZE];

        int len = read(fd, tempbuf, SM_PAGE_SIZE);

        if (len < 0)
            throw std::runtime_error("Could not read header into memory.");

        close (fd);

        fd = -1;

        int hdr_len;

        StoreMetaUnpacker aBuilder(tempbuf, len, &hdr_len);

        metadata = aBuilder.createStoreMeta ();

        cache_key key[SQUID_MD5_DIGEST_LENGTH];

        memset(key, '\0', SQUID_MD5_DIGEST_LENGTH);

        DumpStoreMeta dumper;

        for_each(*metadata, dumper);


        return 0;
    } catch (std::runtime_error error) {
        std::cout << "Failed : " << error.what() << std::endl;

        if (fd >= 0)
            close(fd);

        if (metadata)
            StoreMeta::FreeList(&metadata);

        return 1;
    }
}