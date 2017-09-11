            return loadLzfStringObject();
        default:
            /* unknown encoding */
            SHIFT_ERROR(offset, "Unknown string encoding (0x%02x)", len);
            return NULL;
        }
    }
