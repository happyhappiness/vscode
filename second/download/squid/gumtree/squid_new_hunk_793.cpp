                    mb2.clean();
                }

                first = 0;
            }
            break;
        case Format::LFT_PERCENT:
            str = "%";
            break;

        default:
            // TODO: replace this function with Format::assemble()
            // For now die on unsupported logformat codes.
            fatalf("ERROR: unknown external_acl_type format %u", (uint8_t)format->type);
            break;
        }

        if (str)
            if (!*str)
                str = NULL;
