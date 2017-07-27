sshc->readdir_currLen += snprintf(sshc->readdir_line +
                                        sshc->readdir_currLen,
                                        sshc->readdir_totalLen -
                                        sshc->readdir_currLen, "\n");