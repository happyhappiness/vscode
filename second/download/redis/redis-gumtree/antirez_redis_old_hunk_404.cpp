                rdbExitReportCorruptRDB("Unknown encoding");
                break;
        }
    } else {
        rdbExitReportCorruptRDB("Unknown object type");
    }
