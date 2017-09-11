            rdbCheckInfo("RDB file was saved with checksum disabled: no check performed.");
        } else if (cksum != expected) {
            rdbCheckError("RDB CRC error");
        }
    }

