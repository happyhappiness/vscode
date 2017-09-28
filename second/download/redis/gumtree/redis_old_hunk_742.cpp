                    hashTypeConvert(o, OBJ_ENCODING_HT);
                break;
            default:
                rdbExitReportCorruptRDB("Unknown RDB encoding type %d",rdbtype);
                break;
        }
    } else {
        rdbExitReportCorruptRDB("Unknown RDB encoding type %d",rdbtype);
    }
    return o;
}

