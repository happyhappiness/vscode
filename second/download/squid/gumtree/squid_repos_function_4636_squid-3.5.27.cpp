int main(int argc, char *argv[])
{
    try {
        size_t max_db_size = 0;
        size_t fs_block_size = 0;
        int8_t c;
        bool create_new_db = false;
        std::string db_path;
        // process options.
        while ((c = getopt(argc, argv, "dcghvs:M:b:n:")) != -1) {
            switch (c) {
            case 'd':
                debug_enabled = 1;
                break;
            case 'b':
                if (!parseBytesOptionValue(&fs_block_size, optarg)) {
                    throw std::runtime_error("Error when parsing -b options value");
                }
                break;
            case 's':
                db_path = optarg;
                break;
            case 'M':
                if (!parseBytesOptionValue(&max_db_size, optarg)) {
                    throw std::runtime_error("Error when parsing -M options value");
                }
                break;
            case 'v':
                std::cout << "ssl_crtd version " << VERSION << std::endl;
                exit(0);
                break;
            case 'c':
                create_new_db = true;
                break;
            case 'h':
                usage();
                exit(0);
            default:
                exit(0);
            }
        }

        if (create_new_db) {
            std::cout << "Initialization SSL db..." << std::endl;
            Ssl::CertificateDb::create(db_path);
            std::cout << "Done" << std::endl;
            exit(0);
        }

        if (fs_block_size == 0) {
            struct statvfs sfs;

            if (xstatvfs(db_path.c_str(), &sfs)) {
                fs_block_size = 2048;
            } else {
                fs_block_size = sfs.f_frsize;
                // Sanity check; make sure we have a meaningful value.
                if (fs_block_size < 512)
                    fs_block_size = 2048;
            }
        }

        {
            Ssl::CertificateDb::check(db_path, max_db_size, fs_block_size);
        }
        // Initialize SSL subsystem
        SSL_load_error_strings();
        SSLeay_add_ssl_algorithms();
        // process request.
        for (;;) {
            char request[HELPER_INPUT_BUFFER];
            Ssl::CrtdMessage request_message(Ssl::CrtdMessage::REQUEST);
            Ssl::CrtdMessage::ParseResult parse_result = Ssl::CrtdMessage::INCOMPLETE;

            while (parse_result == Ssl::CrtdMessage::INCOMPLETE) {
                if (fgets(request, HELPER_INPUT_BUFFER, stdin) == NULL)
                    return 1;
                size_t gcount = strlen(request);
                parse_result = request_message.parse(request, gcount);
            }

            if (parse_result == Ssl::CrtdMessage::ERROR) {
                throw std::runtime_error("Cannot parse request message.");
            } else if (request_message.getCode() == Ssl::CrtdMessage::code_new_certificate) {
                processNewRequest(request_message, db_path, max_db_size, fs_block_size);
            } else {
                throw std::runtime_error("Unknown request code: \"" + request_message.getCode() + "\".");
            }
            std::cout.flush();
        }
    } catch (std::runtime_error & error) {
        std::cerr << argv[0] << ": " << error.what() << std::endl;
        return -1;
    }
    return 0;
}