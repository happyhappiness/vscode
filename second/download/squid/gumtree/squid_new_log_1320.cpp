hdr->putStr(Http::HdrType::X_REQUEST_URI,
                http->memOjbect()->url ? http->memObject()->url : http->uri);