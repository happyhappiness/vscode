int main(int argc, char *argv[])
{
    try {
        int serial = (getCurrentTime() -  1200000000);
        size_t max_db_size = 0;
        size_t fs_block_size = 2048;
        char c;
        bool create_new_db = false;
        bool show_sn = false;
        std::string db_path;
        // proccess options.
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
            case 'n': {
                std::stringstream sn_stream(optarg);
                sn_stream >> std::hex >> serial;
                break;
            }
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
            case 'g':
                show_sn = true;
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
            Ssl::CertificateDb::create(db_path, serial);
            std::cout << "Done" << std::endl;
            exit(0);
        }

        if (show_sn) {
            Ssl::CertificateDb db(db_path, 4096, 0);
            std::cout << db.getSNString() << std::endl;
            exit(0);
        }
        {
            Ssl::CertificateDb::check(db_path, max_db_size);
        }
        // proccess request.
        for (;;) {
            char request[HELPER_INPUT_BUFFER];
            Ssl::CrtdMessage request_message;
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
                proccessNewRequest(request_message, db_path, max_db_size, fs_block_size);
            } else {
                throw std::runtime_error("Unknown request code: \"" + request_message.getCode() + "\".");
            }
            std::cout.flush();
        }
    } catch (std::runtime_error & error) {
        std::cerr << argv[0] << ": " << error.what() << std::endl;
        return 0;
    }
    return 0;
}