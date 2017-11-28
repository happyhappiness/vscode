void operator()(StoreMeta const &x) {
        switch (x.getType()) {

        case STORE_META_KEY:
            std::cout << "MD5: " << storeKeyText((const cache_key *)x.value) << std::endl;
            break;

        case STORE_META_STD:
            std::cout << "STD, Size:" << ((struct MetaStd*)x.value)->swap_file_sz <<
                      " Flags: 0x" << std::hex << ((struct MetaStd*)x.value)->flags << std::dec <<
                      " Refcount: " << ((struct MetaStd*)x.value)->refcount <<
                      std::endl;
            break;

        case STORE_META_STD_LFS:
            std::cout << "STD_LFS, Size: " << ((struct MetaStdLfs*)x.value)->swap_file_sz <<
                      " Flags: 0x" << std::hex << ((struct MetaStdLfs*)x.value)->flags << std::dec <<
                      " Refcount: " << ((struct MetaStdLfs*)x.value)->refcount <<
                      std::endl;
            break;

        case STORE_META_URL:
            assert (((char *)x.value)[x.length - 1] == 0);
            std::cout << "URL: " << (char *)x.value << std::endl;
            break;

        default:
            std::cout << "Unknown store meta type: " << (int)x.getType() <<
                      " of length " << x.length << std::endl;
            break;
        }
    }