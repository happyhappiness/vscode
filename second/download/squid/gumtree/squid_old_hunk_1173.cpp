            if (master->serverState == fssHandleUploadRequest)
                maybeReadUploadData();
            else
                Must(master->serverState == fssHandleDataRequest);
            MemBuf mb;
            mb.init();
            mb.Printf("150 Data connection opened.\r\n");
            Comm::Write(clientConnection, &mb, call);
        }
    }
}

void
