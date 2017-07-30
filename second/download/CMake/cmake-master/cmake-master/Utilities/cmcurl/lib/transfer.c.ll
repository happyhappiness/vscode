; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/transfer.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.connectdata = type { %struct.Curl_easy*, %struct.Curl_chunker, i32 (i8*, i32)*, i8*, i8, i64, %struct.Curl_dns_entry*, %struct.Curl_addrinfo*, [2 x %struct.Curl_addrinfo*], [46 x i8], i32, i32, %struct.hostname, i8*, %struct.hostname, %struct.proxy_info, %struct.proxy_info, i64, i32, i32, i16, [46 x i8], i64, [46 x i8], i64, i8*, i8*, i8*, i8*, i32, i32, %struct.timeval, %struct.timeval, [2 x i32], [2 x i32], [2 x i8], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x %struct.ssl_connect_data], [2 x %struct.ssl_connect_data], %struct.ssl_primary_config, %struct.ssl_primary_config, i8, %struct.ConnectBits, %struct.timeval, i32, i64, %struct.Curl_handler*, %struct.Curl_handler*, i64, i32, i32, %struct.dynamically_allocated_data, i8, i8, %struct.curl_llist, %struct.curl_llist, i8*, i64, i64, i32 (i8*, i64, i32)*, i8*, [256 x i8], i8*, i32, i32, %union.anon.0, i32, i32, i8*, i16, i32, [2 x i32], %struct.connectbundle*, i32 }
%struct.Curl_easy = type { %struct.Curl_easy*, %struct.Curl_easy*, %struct.connectdata*, i32, i32, %struct.Curl_message, [5 x i32], i32, %struct.Names, %struct.Curl_multi*, %struct.Curl_multi*, %struct.Curl_share*, %struct.SingleRequest, %struct.UserDefined, %struct.DynamicStatic, %struct.CookieInfo*, %struct.Progress, %struct.UrlState, %struct.WildcardData, %struct.PureInfo, %struct.curl_tlssessioninfo, i32 }
%struct.Curl_message = type { %struct.CURLMsg }
%struct.CURLMsg = type { i32, %struct.Curl_easy*, %union.anon }
%union.anon = type { i8* }
%struct.Names = type { %struct.curl_hash*, i32 }
%struct.curl_hash = type { %struct.curl_llist*, i64 (i8*, i64, i64)*, i64 (i8*, i64, i8*, i64)*, void (i8*)*, i32, i64 }
%struct.Curl_multi = type { i64, %struct.Curl_easy*, %struct.Curl_easy*, i32, i32, %struct.curl_llist, %struct.curl_llist, i32 (%struct.Curl_easy*, i32, i32, i8*, i8*)*, i8*, i32 (%struct.Curl_easy*, %struct.Curl_easy*, i64, %struct.curl_pushheaders*, i8*)*, i8*, %struct.curl_hash, %struct.Curl_tree*, %struct.curl_hash, i64, i8, %struct.conncache, %struct.Curl_easy*, i64, i64, i64, i64, i64, i64, %struct.curl_llist, %struct.curl_llist, i32 (%struct.Curl_multi*, i64, i8*)*, i8*, %struct.timeval }
%struct.curl_pushheaders = type opaque
%struct.Curl_tree = type { %struct.Curl_tree*, %struct.Curl_tree*, %struct.Curl_tree*, %struct.Curl_tree*, %struct.timeval, i8* }
%struct.conncache = type { %struct.curl_hash, i64, i64, %struct.timeval }
%struct.Curl_share = type opaque
%struct.SingleRequest = type { i64, i64*, i64, i64*, i64, i64, i64, i64, %struct.timeval, %struct.timeval, i8, i32, i32, i8*, i64, i8*, i8*, i8*, i8*, i8, i64, i32, %struct.timeval, i32, i32, i32, i64, i64, i8*, i8*, i32, i32, i8, i8, i8, i8*, i8*, i64, i8*, i8, i8, i8, i8, i8* }
%struct.UserDefined = type { %struct._IO_FILE*, i8*, i8*, i64, i8*, i8*, i8*, i8*, i64, i64, i64, i64, i64, i32, i8, i8*, i32 (i8*, i64, i32)*, i64, i16, i32, i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)*, i32, i32, i32 (i8*, double, double, double, double)*, i32 (i8*, i64, i64, i64, i64)*, i32 (%struct.Curl_easy*, i32, i8*, i64, i8*)*, i32 (%struct.Curl_easy*, i32, i8*)*, i32 (i8*, i32, i32)*, i8*, i32 (i8*, i32, %struct.curl_sockaddr*)*, i8*, i32 (i8*, i32)*, i8*, i8*, i32 (i8*, i64)*, i32 (i8*, i64)*, i32 (i8*, i64)*, i8*, i8*, i64, i64, i64, i64, i64, i8, i64, i64, i64, i64, i64, i64, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_httppost*, i8, i8, i8, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, %struct.curl_slist*, i32, i64, i32, i64, %struct.ssl_config_data, %struct.ssl_config_data, %struct.ssl_general_config, i32, i64, i64, i8*, %struct.curl_slist*, i64, i64, i32, i32, i32 (%struct.Curl_easy*, %struct.curl_khkey*, %struct.curl_khkey*, i32, i8*)*, i8*, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i32, i8, i8, i8, i8, i8, i8, i8, i32, i32, i32, i8, i8, i8, i8, i8, i8, i64, i8, i8, i64, i64, i8, [56 x i8*], i32, i64, i64, %struct.curl_slist*, i8, i32, i64, i8, i64 (i8*, i8*, i32)*, i64 (i8*)*, i32 (i8*, i8*, i8*)*, i8*, i64, i8, i64, i64, i8, i64, i8, i8, i8, i8, i64, i8, %struct.Curl_easy*, i8, i32, %struct.Curl_http2_dep*, i8 }
%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.curl_sockaddr = type { i32, i32, i32, i32, %struct.sockaddr }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.curl_httppost = type { %struct.curl_httppost*, i8*, i64, i8*, i64, i8*, i64, i8*, %struct.curl_slist*, %struct.curl_httppost*, i64, i8*, i8*, i64 }
%struct.ssl_config_data = type { %struct.ssl_primary_config, i8, i8, i64, i8*, i8*, i32 (%struct.Curl_easy*, i8*, i8*)*, i8*, i8, i8, i8*, i8*, i8*, i8*, i8* }
%struct.ssl_general_config = type { i64 }
%struct.curl_khkey = type { i8*, i64, i32 }
%struct.curl_slist = type { i8*, %struct.curl_slist* }
%struct.Curl_http2_dep = type { %struct.Curl_http2_dep*, %struct.Curl_easy* }
%struct.DynamicStatic = type { i8*, i8, i8*, i8, %struct.curl_slist*, %struct.curl_slist* }
%struct.CookieInfo = type { %struct.Cookie*, i8*, i8, i64, i8 }
%struct.Cookie = type { %struct.Cookie*, i8*, i8*, i8*, i8*, i8*, i64, i8*, i8, i8*, i8*, i8, i8, i8 }
%struct.Progress = type { i64, i64, i64, i64, i64, i64, i8, i32, i32, double, i64, i64, double, double, double, double, double, double, %struct.timeval, %struct.timeval, %struct.timeval, %struct.timeval, %struct.timeval, i64, %struct.timeval, i64, [6 x i64], [6 x %struct.timeval], i32 }
%struct.UrlState = type { %struct.conncache*, i8, %struct.timeval, %struct.connectdata*, i8*, i64, i8*, [16385 x i8], i64, i8, i8*, i32, %struct.curl_ssl_session*, i64, i32, [3 x %struct.tempbuf], i8*, i8, i32, void (i32)*, i8, %struct.digestdata, %struct.digestdata, %struct.auth, %struct.auth, i8, i8*, %struct.timeval, %struct.Curl_tree, %struct.curl_llist, i8*, i8, i32, i8, i8, i8, i64, i8*, i8*, i8, i8, i8, i8*, i64, i64, i64, i64, i64, i64, i8, i64 (i8*, i64, i64, i8*)*, i8*, %struct.Curl_easy*, i8, i32 }
%struct.curl_ssl_session = type { i8*, i8*, i8*, i8*, i64, i64, i32, i32, %struct.ssl_primary_config }
%struct.tempbuf = type { i8*, i64, i32 }
%struct.digestdata = type { i8*, i8*, i8*, i32, i8, i8*, i8*, i8*, i32 }
%struct.auth = type { i64, i64, i64, i8, i8, i8 }
%struct.WildcardData = type { i32, i8*, i8*, %struct.curl_llist, i8*, void (i8*)*, i8* }
%struct.PureInfo = type { i32, i32, i32, i64, i8, i64, i64, i64, i64, i64, i8*, i8*, [46 x i8], i64, [46 x i8], i64, i8*, i32, %struct.curl_certinfo }
%struct.curl_certinfo = type { i32, %struct.curl_slist** }
%struct.curl_tlssessioninfo = type { i32, i8* }
%struct.Curl_chunker = type { [17 x i8], i32, i32, i64, i64 }
%struct.Curl_dns_entry = type { %struct.Curl_addrinfo*, i64, i64 }
%struct.Curl_addrinfo = type { i32, i32, i32, i32, i32, i8*, %struct.sockaddr*, %struct.Curl_addrinfo* }
%struct.hostname = type { i8*, i8*, i8*, i8* }
%struct.proxy_info = type { %struct.hostname, i64, i32, i8*, i8* }
%struct.ssl_connect_data = type { i8, i32, i32 }
%struct.ssl_primary_config = type { i64, i64, i8, i8, i8, i8*, i8*, i8*, i8*, i8*, i8*, i8 }
%struct.ConnectBits = type { i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, [2 x i8], i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, [2 x i8], i8 }
%struct.timeval = type { i64, i64 }
%struct.Curl_handler = type { i8*, i32 (%struct.connectdata*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32, i1)*, i32 (%struct.connectdata*, i32*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i1)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i64, i32, i32 }
%struct.dynamically_allocated_data = type { i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8* }
%struct.curl_llist = type { %struct.curl_llist_element*, %struct.curl_llist_element*, void (i8*, i8*)*, i64 }
%struct.curl_llist_element = type { i8*, %struct.curl_llist_element*, %struct.curl_llist_element* }
%union.anon.0 = type { %struct.ftp_conn }
%struct.ftp_conn = type { %struct.pingpong, i8*, i8**, i32, i32, i8*, i8, i8, i8, i8, i8, i8*, i8, i32, i32, i32, i32, i32, i64, i8*, i64, i8*, i16 }
%struct.pingpong = type { i8*, i64, i64, i8*, i8, i8*, i64, i64, %struct.timeval, i64, %struct.connectdata*, i32 (%struct.connectdata*)*, i1 (%struct.connectdata*, i8*, i64, i32*)* }
%struct.connectbundle = type { i32, i64, %struct.curl_llist }
%struct.HTTP = type { %struct.FormData*, i64, i8*, i8*, i8*, i64, i64, %struct.Form, %struct.back, i32, i8* }
%struct.FormData = type { %struct.FormData*, i32, i8*, i64 }
%struct.Form = type { %struct.FormData*, i64, %struct._IO_FILE*, i64 (i8*, i64, i64, i8*)* }
%struct.back = type { i64 (i8*, i64, i64, i8*)*, i8*, i8*, i64 }

@.str = private unnamed_addr constant [30 x i8] c"operation aborted by callback\00", align 1
@.str.1 = private unnamed_addr constant [50 x i8] c"Read callback asked for PAUSE when not supported!\00", align 1
@.str.2 = private unnamed_addr constant [35 x i8] c"read function returned funny value\00", align 1
@.str.3 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.4 = private unnamed_addr constant [3 x i8] c"\0D\0A\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"%x%s\00", align 1
@.str.6 = private unnamed_addr constant [32 x i8] c"seek callback returned error %d\00", align 1
@.str.7 = private unnamed_addr constant [32 x i8] c"the ioctl callback returned %d\0A\00", align 1
@.str.8 = private unnamed_addr constant [33 x i8] c"ioctl callback returned error %d\00", align 1
@.str.9 = private unnamed_addr constant [38 x i8] c"necessary data rewind wasn't possible\00", align 1
@.str.10 = private unnamed_addr constant [42 x i8] c"The requested document is not new enough\0A\00", align 1
@.str.11 = private unnamed_addr constant [42 x i8] c"The requested document is not old enough\0A\00", align 1
@.str.12 = private unnamed_addr constant [27 x i8] c"select/poll returned error\00", align 1
@.str.13 = private unnamed_addr constant [31 x i8] c"Done waiting for 100-continue\0A\00", align 1
@.str.14 = private unnamed_addr constant [78 x i8] c"Operation timed out after %ld milliseconds with %ld out of %ld bytes received\00", align 1
@.str.15 = private unnamed_addr constant [67 x i8] c"Operation timed out after %ld milliseconds with %ld bytes received\00", align 1
@.str.16 = private unnamed_addr constant [49 x i8] c"transfer closed with %ld bytes remaining to read\00", align 1
@.str.17 = private unnamed_addr constant [53 x i8] c"transfer closed with outstanding read data remaining\00", align 1
@.str.18 = private unnamed_addr constant [12 x i8] c"No URL set!\00", align 1
@Curl_cfree = external global void (i8*)*, align 8
@.str.19 = private unnamed_addr constant [33 x i8] c"Maximum (%ld) redirects followed\00", align 1
@Curl_cstrdup = external global i8* (i8*)*, align 8
@Curl_cmalloc = external global i8* (i64)*, align 8
@.str.20 = private unnamed_addr constant [41 x i8] c"Issue another request to this URL: '%s'\0A\00", align 1
@.str.21 = private unnamed_addr constant [25 x i8] c"Switch from POST to GET\0A\00", align 1
@.str.22 = private unnamed_addr constant [29 x i8] c"Disables POST, goes with %s\0A\00", align 1
@.str.23 = private unnamed_addr constant [5 x i8] c"HEAD\00", align 1
@.str.24 = private unnamed_addr constant [4 x i8] c"GET\00", align 1
@.str.25 = private unnamed_addr constant [43 x i8] c"Connection died, retrying a fresh connect\0A\00", align 1
@.str.26 = private unnamed_addr constant [62 x i8] c"Rewinding stream by : %zd bytes on url %s (zero-length body)\0A\00", align 1
@.str.27 = private unnamed_addr constant [80 x i8] c"Excess found in a non pipelined read: excess = %zd url = %s (zero-length body)\0A\00", align 1
@.str.28 = private unnamed_addr constant [28 x i8] c"Ignoring the response-body\0A\00", align 1
@.str.29 = private unnamed_addr constant [42 x i8] c"The entire document is already downloaded\00", align 1
@.str.30 = private unnamed_addr constant [64 x i8] c"HTTP server doesn't seem to support byte ranges. Cannot resume.\00", align 1
@.str.31 = private unnamed_addr constant [31 x i8] c"Simulate a HTTP 304 response!\0A\00", align 1
@.str.32 = private unnamed_addr constant [20 x i8] c"Failed writing data\00", align 1
@.str.33 = private unnamed_addr constant [23 x i8] c"%s in chunked-encoding\00", align 1
@.str.34 = private unnamed_addr constant [37 x i8] c"Leftovers after chunking: %zu bytes\0A\00", align 1
@.str.35 = private unnamed_addr constant [21 x i8] c"Rewinding %zu bytes\0A\00", align 1
@.str.36 = private unnamed_addr constant [105 x i8] c"Rewinding stream by : %zu bytes on url %s (size = %ld, maxdownload = %ld, bytecount = %ld, nread = %zd)\0A\00", align 1
@.str.37 = private unnamed_addr constant [100 x i8] c"Excess found in a non pipelined read: excess = %zu, size = %ld, maxdownload = %ld, bytecount = %ld\0A\00", align 1
@.str.38 = private unnamed_addr constant [57 x i8] c"we are done reading and this is set to close, stop send\0A\00", align 1
@.str.39 = private unnamed_addr constant [32 x i8] c"Failed to alloc scratch buffer!\00", align 1
@.str.40 = private unnamed_addr constant [37 x i8] c"We are completely uploaded and fine\0A\00", align 1
@.str.41 = private unnamed_addr constant [16 x i8] c"%15[^?&/:]://%c\00", align 1
@.str.42 = private unnamed_addr constant [3 x i8] c"//\00", align 1
@.str.43 = private unnamed_addr constant [7 x i8] c"%%%02x\00", align 1

; Function Attrs: nounwind uwtable
define i32 @Curl_fillreadbuffer(%struct.connectdata* %conn, i32 %bytes, i32* %nreadp) #0 !dbg !1766 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %bytes.addr = alloca i32, align 4
  %nreadp.addr = alloca i32*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %buffersize = alloca i64, align 8
  %nread = alloca i32, align 4
  %k = alloca %struct.SingleRequest*, align 8
  %hexbuffer = alloca [11 x i8], align 1
  %endofline_native = alloca i8*, align 8
  %endofline_network = alloca i8*, align 8
  %hexlen = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !1826, metadata !1827), !dbg !1828
  store i32 %bytes, i32* %bytes.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %bytes.addr, metadata !1829, metadata !1827), !dbg !1830
  store i32* %nreadp, i32** %nreadp.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %nreadp.addr, metadata !1831, metadata !1827), !dbg !1832
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !1833, metadata !1827), !dbg !1834
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1835
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !1836
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !1836
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !1834
  call void @llvm.dbg.declare(metadata i64* %buffersize, metadata !1837, metadata !1827), !dbg !1838
  %2 = load i32, i32* %bytes.addr, align 4, !dbg !1839
  %conv = sext i32 %2 to i64, !dbg !1840
  store i64 %conv, i64* %buffersize, align 8, !dbg !1838
  call void @llvm.dbg.declare(metadata i32* %nread, metadata !1841, metadata !1827), !dbg !1842
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1843
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 12, !dbg !1845
  %upload_chunky = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 40, !dbg !1846
  %4 = load i8, i8* %upload_chunky, align 1, !dbg !1846
  %tobool = trunc i8 %4 to i1, !dbg !1846
  br i1 %tobool, label %if.then, label %if.end, !dbg !1847

if.then:                                          ; preds = %entry
  %5 = load i64, i64* %buffersize, align 8, !dbg !1848
  %sub = sub i64 %5, 12, !dbg !1848
  store i64 %sub, i64* %buffersize, align 8, !dbg !1848
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1850
  %req2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 12, !dbg !1851
  %upload_fromhere = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req2, i32 0, i32 38, !dbg !1852
  %7 = load i8*, i8** %upload_fromhere, align 8, !dbg !1853
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 10, !dbg !1853
  store i8* %add.ptr, i8** %upload_fromhere, align 8, !dbg !1853
  br label %if.end, !dbg !1854

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1855
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %8, i32 0, i32 17, !dbg !1856
  %fread_func = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 50, !dbg !1857
  %9 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %fread_func, align 8, !dbg !1857
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1858
  %req3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 12, !dbg !1859
  %upload_fromhere4 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req3, i32 0, i32 38, !dbg !1860
  %11 = load i8*, i8** %upload_fromhere4, align 8, !dbg !1860
  %12 = load i64, i64* %buffersize, align 8, !dbg !1861
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1862
  %state5 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 17, !dbg !1863
  %in = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state5, i32 0, i32 51, !dbg !1864
  %14 = load i8*, i8** %in, align 8, !dbg !1864
  %call = call i64 %9(i8* %11, i64 1, i64 %12, i8* %14), !dbg !1855
  %conv6 = trunc i64 %call to i32, !dbg !1865
  store i32 %conv6, i32* %nread, align 4, !dbg !1866
  %15 = load i32, i32* %nread, align 4, !dbg !1867
  %cmp = icmp eq i32 %15, 268435456, !dbg !1869
  br i1 %cmp, label %if.then8, label %if.end9, !dbg !1870

if.then8:                                         ; preds = %if.end
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1871
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %16, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str, i32 0, i32 0)), !dbg !1873
  %17 = load i32*, i32** %nreadp.addr, align 8, !dbg !1874
  store i32 0, i32* %17, align 4, !dbg !1875
  store i32 42, i32* %retval, align 4, !dbg !1876
  br label %return, !dbg !1876

if.end9:                                          ; preds = %if.end
  %18 = load i32, i32* %nread, align 4, !dbg !1877
  %cmp10 = icmp eq i32 %18, 268435457, !dbg !1879
  br i1 %cmp10, label %if.then12, label %if.else, !dbg !1880

if.then12:                                        ; preds = %if.end9
  call void @llvm.dbg.declare(metadata %struct.SingleRequest** %k, metadata !1881, metadata !1827), !dbg !1883
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1884
  %req13 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %19, i32 0, i32 12, !dbg !1885
  store %struct.SingleRequest* %req13, %struct.SingleRequest** %k, align 8, !dbg !1883
  %20 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1886
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %20, i32 0, i32 47, !dbg !1888
  %21 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !1888
  %flags = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %21, i32 0, i32 16, !dbg !1889
  %22 = load i32, i32* %flags, align 4, !dbg !1889
  %and = and i32 %22, 16, !dbg !1890
  %tobool14 = icmp ne i32 %and, 0, !dbg !1890
  br i1 %tobool14, label %if.then15, label %if.end16, !dbg !1891

if.then15:                                        ; preds = %if.then12
  %23 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1892
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %23, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.1, i32 0, i32 0)), !dbg !1894
  store i32 26, i32* %retval, align 4, !dbg !1895
  br label %return, !dbg !1895

if.end16:                                         ; preds = %if.then12
  %24 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !1896
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %24, i32 0, i32 31, !dbg !1897
  %25 = load i32, i32* %keepon, align 4, !dbg !1898
  %or = or i32 %25, 32, !dbg !1898
  store i32 %or, i32* %keepon, align 4, !dbg !1898
  %26 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1899
  %req17 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %26, i32 0, i32 12, !dbg !1901
  %upload_chunky18 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req17, i32 0, i32 40, !dbg !1902
  %27 = load i8, i8* %upload_chunky18, align 1, !dbg !1902
  %tobool19 = trunc i8 %27 to i1, !dbg !1902
  br i1 %tobool19, label %if.then20, label %if.end24, !dbg !1903

if.then20:                                        ; preds = %if.end16
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1904
  %req21 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %28, i32 0, i32 12, !dbg !1906
  %upload_fromhere22 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req21, i32 0, i32 38, !dbg !1907
  %29 = load i8*, i8** %upload_fromhere22, align 8, !dbg !1908
  %add.ptr23 = getelementptr inbounds i8, i8* %29, i64 -10, !dbg !1908
  store i8* %add.ptr23, i8** %upload_fromhere22, align 8, !dbg !1908
  br label %if.end24, !dbg !1909

if.end24:                                         ; preds = %if.then20, %if.end16
  %30 = load i32*, i32** %nreadp.addr, align 8, !dbg !1910
  store i32 0, i32* %30, align 4, !dbg !1911
  store i32 0, i32* %retval, align 4, !dbg !1912
  br label %return, !dbg !1912

if.else:                                          ; preds = %if.end9
  %31 = load i32, i32* %nread, align 4, !dbg !1913
  %conv25 = sext i32 %31 to i64, !dbg !1915
  %32 = load i64, i64* %buffersize, align 8, !dbg !1916
  %cmp26 = icmp ugt i64 %conv25, %32, !dbg !1917
  br i1 %cmp26, label %if.then28, label %if.end29, !dbg !1918

if.then28:                                        ; preds = %if.else
  %33 = load i32*, i32** %nreadp.addr, align 8, !dbg !1919
  store i32 0, i32* %33, align 4, !dbg !1921
  %34 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1922
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %34, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.2, i32 0, i32 0)), !dbg !1923
  store i32 26, i32* %retval, align 4, !dbg !1924
  br label %return, !dbg !1924

if.end29:                                         ; preds = %if.else
  br label %if.end30

if.end30:                                         ; preds = %if.end29
  %35 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1925
  %req31 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %35, i32 0, i32 12, !dbg !1927
  %forbidchunk = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req31, i32 0, i32 42, !dbg !1928
  %36 = load i8, i8* %forbidchunk, align 1, !dbg !1928
  %tobool32 = trunc i8 %36 to i1, !dbg !1928
  br i1 %tobool32, label %if.end68, label %land.lhs.true, !dbg !1929

land.lhs.true:                                    ; preds = %if.end30
  %37 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1930
  %req33 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %37, i32 0, i32 12, !dbg !1932
  %upload_chunky34 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req33, i32 0, i32 40, !dbg !1933
  %38 = load i8, i8* %upload_chunky34, align 1, !dbg !1933
  %tobool35 = trunc i8 %38 to i1, !dbg !1933
  br i1 %tobool35, label %if.then37, label %if.end68, !dbg !1934

if.then37:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata [11 x i8]* %hexbuffer, metadata !1935, metadata !1827), !dbg !1940
  call void @llvm.dbg.declare(metadata i8** %endofline_native, metadata !1941, metadata !1827), !dbg !1942
  call void @llvm.dbg.declare(metadata i8** %endofline_network, metadata !1943, metadata !1827), !dbg !1944
  call void @llvm.dbg.declare(metadata i32* %hexlen, metadata !1945, metadata !1827), !dbg !1946
  %39 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1947
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %39, i32 0, i32 13, !dbg !1949
  %prefer_ascii = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 90, !dbg !1950
  %40 = load i8, i8* %prefer_ascii, align 1, !dbg !1950
  %tobool38 = trunc i8 %40 to i1, !dbg !1950
  br i1 %tobool38, label %if.then43, label %lor.lhs.false, !dbg !1951

lor.lhs.false:                                    ; preds = %if.then37
  %41 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1952
  %set40 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %41, i32 0, i32 13, !dbg !1953
  %crlf = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set40, i32 0, i32 59, !dbg !1954
  %42 = load i8, i8* %crlf, align 2, !dbg !1954
  %tobool41 = trunc i8 %42 to i1, !dbg !1954
  br i1 %tobool41, label %if.then43, label %if.else44, !dbg !1955

if.then43:                                        ; preds = %lor.lhs.false, %if.then37
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.3, i32 0, i32 0), i8** %endofline_native, align 8, !dbg !1957
  store i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.3, i32 0, i32 0), i8** %endofline_network, align 8, !dbg !1959
  br label %if.end45, !dbg !1960

if.else44:                                        ; preds = %lor.lhs.false
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.4, i32 0, i32 0), i8** %endofline_native, align 8, !dbg !1961
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.4, i32 0, i32 0), i8** %endofline_network, align 8, !dbg !1963
  br label %if.end45

if.end45:                                         ; preds = %if.else44, %if.then43
  %arraydecay = getelementptr inbounds [11 x i8], [11 x i8]* %hexbuffer, i32 0, i32 0, !dbg !1964
  %43 = load i32, i32* %nread, align 4, !dbg !1965
  %44 = load i8*, i8** %endofline_native, align 8, !dbg !1966
  %call46 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %arraydecay, i64 11, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i32 %43, i8* %44), !dbg !1967
  store i32 %call46, i32* %hexlen, align 4, !dbg !1968
  %45 = load i32, i32* %hexlen, align 4, !dbg !1969
  %46 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1970
  %req47 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %46, i32 0, i32 12, !dbg !1971
  %upload_fromhere48 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req47, i32 0, i32 38, !dbg !1972
  %47 = load i8*, i8** %upload_fromhere48, align 8, !dbg !1973
  %idx.ext = sext i32 %45 to i64, !dbg !1973
  %idx.neg = sub i64 0, %idx.ext, !dbg !1973
  %add.ptr49 = getelementptr inbounds i8, i8* %47, i64 %idx.neg, !dbg !1973
  store i8* %add.ptr49, i8** %upload_fromhere48, align 8, !dbg !1973
  %48 = load i32, i32* %hexlen, align 4, !dbg !1974
  %49 = load i32, i32* %nread, align 4, !dbg !1975
  %add = add nsw i32 %49, %48, !dbg !1975
  store i32 %add, i32* %nread, align 4, !dbg !1975
  %50 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1976
  %req50 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %50, i32 0, i32 12, !dbg !1977
  %upload_fromhere51 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req50, i32 0, i32 38, !dbg !1978
  %51 = load i8*, i8** %upload_fromhere51, align 8, !dbg !1978
  %arraydecay52 = getelementptr inbounds [11 x i8], [11 x i8]* %hexbuffer, i32 0, i32 0, !dbg !1979
  %52 = load i32, i32* %hexlen, align 4, !dbg !1980
  %conv53 = sext i32 %52 to i64, !dbg !1980
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %51, i8* %arraydecay52, i64 %conv53, i32 1, i1 false), !dbg !1979
  %53 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1981
  %req54 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %53, i32 0, i32 12, !dbg !1982
  %upload_fromhere55 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req54, i32 0, i32 38, !dbg !1983
  %54 = load i8*, i8** %upload_fromhere55, align 8, !dbg !1983
  %55 = load i32, i32* %nread, align 4, !dbg !1984
  %idx.ext56 = sext i32 %55 to i64, !dbg !1985
  %add.ptr57 = getelementptr inbounds i8, i8* %54, i64 %idx.ext56, !dbg !1985
  %56 = load i8*, i8** %endofline_network, align 8, !dbg !1986
  %57 = load i8*, i8** %endofline_network, align 8, !dbg !1987
  %call58 = call i64 @strlen(i8* %57) #6, !dbg !1988
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr57, i8* %56, i64 %call58, i32 1, i1 false), !dbg !1989
  %58 = load i32, i32* %nread, align 4, !dbg !1990
  %59 = load i32, i32* %hexlen, align 4, !dbg !1992
  %sub59 = sub nsw i32 %58, %59, !dbg !1993
  %cmp60 = icmp eq i32 %sub59, 0, !dbg !1994
  br i1 %cmp60, label %if.then62, label %if.end64, !dbg !1995

if.then62:                                        ; preds = %if.end45
  %60 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1996
  %req63 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %60, i32 0, i32 12, !dbg !1997
  %upload_done = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req63, i32 0, i32 32, !dbg !1998
  store i8 1, i8* %upload_done, align 8, !dbg !1999
  br label %if.end64, !dbg !1996

if.end64:                                         ; preds = %if.then62, %if.end45
  %61 = load i8*, i8** %endofline_native, align 8, !dbg !2000
  %call65 = call i64 @strlen(i8* %61) #6, !dbg !2001
  %conv66 = trunc i64 %call65 to i32, !dbg !2002
  %62 = load i32, i32* %nread, align 4, !dbg !2003
  %add67 = add nsw i32 %62, %conv66, !dbg !2003
  store i32 %add67, i32* %nread, align 4, !dbg !2003
  br label %if.end68, !dbg !2004

if.end68:                                         ; preds = %if.end64, %land.lhs.true, %if.end30
  %63 = load i32, i32* %nread, align 4, !dbg !2005
  %64 = load i32*, i32** %nreadp.addr, align 8, !dbg !2006
  store i32 %63, i32* %64, align 4, !dbg !2007
  store i32 0, i32* %retval, align 4, !dbg !2008
  br label %return, !dbg !2008

return:                                           ; preds = %if.end68, %if.then28, %if.end24, %if.then15, %if.then8
  %65 = load i32, i32* %retval, align 4, !dbg !2009
  ret i32 %65, !dbg !2009
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @Curl_failf(%struct.Curl_easy*, i8*, ...) #2

declare i32 @curl_msnprintf(i8*, i64, i8*, ...) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: nounwind uwtable
define i32 @Curl_readrewind(%struct.connectdata* %conn) #0 !dbg !1770 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %err = alloca i32, align 4
  %err15 = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2010, metadata !1827), !dbg !2011
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2012, metadata !1827), !dbg !2013
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2014
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2015
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2015
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2013
  %2 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2016
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 43, !dbg !2017
  %rewindaftersend = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 17, !dbg !2018
  store i8 0, i8* %rewindaftersend, align 1, !dbg !2019
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2020
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 12, !dbg !2021
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 31, !dbg !2022
  %4 = load i32, i32* %keepon, align 4, !dbg !2023
  %and = and i32 %4, -3, !dbg !2023
  store i32 %and, i32* %keepon, align 4, !dbg !2023
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2024
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %5, i32 0, i32 13, !dbg !2026
  %postfields = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 15, !dbg !2027
  %6 = load i8*, i8** %postfields, align 8, !dbg !2027
  %tobool = icmp ne i8* %6, null, !dbg !2024
  br i1 %tobool, label %if.then, label %lor.lhs.false, !dbg !2028

lor.lhs.false:                                    ; preds = %entry
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2029
  %set2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 13, !dbg !2030
  %httpreq = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set2, i32 0, i32 71, !dbg !2031
  %8 = load i32, i32* %httpreq, align 8, !dbg !2031
  %cmp = icmp eq i32 %8, 3, !dbg !2032
  br i1 %cmp, label %if.then, label %if.else, !dbg !2033

if.then:                                          ; preds = %lor.lhs.false, %entry
  br label %if.end34, !dbg !2035

if.else:                                          ; preds = %lor.lhs.false
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2037
  %set3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 13, !dbg !2040
  %seek_func = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set3, i32 0, i32 16, !dbg !2041
  %10 = load i32 (i8*, i64, i32)*, i32 (i8*, i64, i32)** %seek_func, align 8, !dbg !2041
  %tobool4 = icmp ne i32 (i8*, i64, i32)* %10, null, !dbg !2037
  br i1 %tobool4, label %if.then5, label %if.else11, !dbg !2042

if.then5:                                         ; preds = %if.else
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2043, metadata !1827), !dbg !2045
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2046
  %set6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 13, !dbg !2047
  %seek_func7 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set6, i32 0, i32 16, !dbg !2048
  %12 = load i32 (i8*, i64, i32)*, i32 (i8*, i64, i32)** %seek_func7, align 8, !dbg !2048
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2049
  %set8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 13, !dbg !2050
  %seek_client = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set8, i32 0, i32 36, !dbg !2051
  %14 = load i8*, i8** %seek_client, align 8, !dbg !2051
  %call = call i32 %12(i8* %14, i64 0, i32 0), !dbg !2052
  store i32 %call, i32* %err, align 4, !dbg !2053
  %15 = load i32, i32* %err, align 4, !dbg !2054
  %tobool9 = icmp ne i32 %15, 0, !dbg !2054
  br i1 %tobool9, label %if.then10, label %if.end, !dbg !2056

if.then10:                                        ; preds = %if.then5
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2057
  %17 = load i32, i32* %err, align 4, !dbg !2059
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %16, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.6, i32 0, i32 0), i32 %17), !dbg !2060
  store i32 65, i32* %retval, align 4, !dbg !2061
  br label %return, !dbg !2061

if.end:                                           ; preds = %if.then5
  br label %if.end33, !dbg !2062

if.else11:                                        ; preds = %if.else
  %18 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2063
  %set12 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %18, i32 0, i32 13, !dbg !2065
  %ioctl_func = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set12, i32 0, i32 29, !dbg !2066
  %19 = load i32 (%struct.Curl_easy*, i32, i8*)*, i32 (%struct.Curl_easy*, i32, i8*)** %ioctl_func, align 8, !dbg !2066
  %tobool13 = icmp ne i32 (%struct.Curl_easy*, i32, i8*)* %19, null, !dbg !2063
  br i1 %tobool13, label %if.then14, label %if.else23, !dbg !2067

if.then14:                                        ; preds = %if.else11
  call void @llvm.dbg.declare(metadata i32* %err15, metadata !2068, metadata !1827), !dbg !2070
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2071
  %set16 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %20, i32 0, i32 13, !dbg !2072
  %ioctl_func17 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set16, i32 0, i32 29, !dbg !2073
  %21 = load i32 (%struct.Curl_easy*, i32, i8*)*, i32 (%struct.Curl_easy*, i32, i8*)** %ioctl_func17, align 8, !dbg !2073
  %22 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2074
  %23 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2075
  %set18 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %23, i32 0, i32 13, !dbg !2076
  %ioctl_client = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set18, i32 0, i32 41, !dbg !2077
  %24 = load i8*, i8** %ioctl_client, align 8, !dbg !2077
  %call19 = call i32 %21(%struct.Curl_easy* %22, i32 1, i8* %24), !dbg !2078
  store i32 %call19, i32* %err15, align 4, !dbg !2079
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2080
  %26 = load i32, i32* %err15, align 4, !dbg !2081
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %25, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.7, i32 0, i32 0), i32 %26), !dbg !2082
  %27 = load i32, i32* %err15, align 4, !dbg !2083
  %tobool20 = icmp ne i32 %27, 0, !dbg !2083
  br i1 %tobool20, label %if.then21, label %if.end22, !dbg !2085

if.then21:                                        ; preds = %if.then14
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2086
  %29 = load i32, i32* %err15, align 4, !dbg !2088
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %28, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.8, i32 0, i32 0), i32 %29), !dbg !2089
  store i32 65, i32* %retval, align 4, !dbg !2090
  br label %return, !dbg !2090

if.end22:                                         ; preds = %if.then14
  br label %if.end32, !dbg !2091

if.else23:                                        ; preds = %if.else11
  %30 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2092
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %30, i32 0, i32 17, !dbg !2095
  %fread_func = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 50, !dbg !2096
  %31 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %fread_func, align 8, !dbg !2096
  %cmp24 = icmp eq i64 (i8*, i64, i64, i8*)* %31, bitcast (i64 (i8*, i64, i64, %struct._IO_FILE*)* @fread to i64 (i8*, i64, i64, i8*)*), !dbg !2097
  br i1 %cmp24, label %if.then25, label %if.end31, !dbg !2098

if.then25:                                        ; preds = %if.else23
  %32 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2099
  %state26 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %32, i32 0, i32 17, !dbg !2102
  %in = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state26, i32 0, i32 51, !dbg !2103
  %33 = load i8*, i8** %in, align 8, !dbg !2103
  %34 = bitcast i8* %33 to %struct._IO_FILE*, !dbg !2099
  %call27 = call i32 @fseek(%struct._IO_FILE* %34, i64 0, i32 0), !dbg !2104
  %cmp28 = icmp ne i32 -1, %call27, !dbg !2105
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !2106

if.then29:                                        ; preds = %if.then25
  store i32 0, i32* %retval, align 4, !dbg !2107
  br label %return, !dbg !2107

if.end30:                                         ; preds = %if.then25
  br label %if.end31, !dbg !2108

if.end31:                                         ; preds = %if.end30, %if.else23
  %35 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2109
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %35, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.9, i32 0, i32 0)), !dbg !2110
  store i32 65, i32* %retval, align 4, !dbg !2111
  br label %return, !dbg !2111

if.end32:                                         ; preds = %if.end22
  br label %if.end33

if.end33:                                         ; preds = %if.end32, %if.end
  br label %if.end34

if.end34:                                         ; preds = %if.end33, %if.then
  store i32 0, i32* %retval, align 4, !dbg !2112
  br label %return, !dbg !2112

return:                                           ; preds = %if.end34, %if.end31, %if.then29, %if.then21, %if.then10
  %36 = load i32, i32* %retval, align 4, !dbg !2113
  ret i32 %36, !dbg !2113
}

declare void @Curl_infof(%struct.Curl_easy*, i8*, ...) #2

declare i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #2

declare i32 @fseek(%struct._IO_FILE*, i64, i32) #2

; Function Attrs: nounwind uwtable
define zeroext i1 @Curl_meets_timecondition(%struct.Curl_easy* %data, i64 %timeofdoc) #0 !dbg !1771 {
entry:
  %retval = alloca i1, align 1
  %data.addr = alloca %struct.Curl_easy*, align 8
  %timeofdoc.addr = alloca i64, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2114, metadata !1827), !dbg !2115
  store i64 %timeofdoc, i64* %timeofdoc.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %timeofdoc.addr, metadata !2116, metadata !1827), !dbg !2117
  %0 = load i64, i64* %timeofdoc.addr, align 8, !dbg !2118
  %cmp = icmp eq i64 %0, 0, !dbg !2120
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2121

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2122
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 13, !dbg !2124
  %timevalue = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 70, !dbg !2125
  %2 = load i64, i64* %timevalue, align 8, !dbg !2125
  %cmp1 = icmp eq i64 %2, 0, !dbg !2126
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2127

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i1 true, i1* %retval, align 1, !dbg !2128
  br label %return, !dbg !2128

if.end:                                           ; preds = %lor.lhs.false
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2129
  %set2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 13, !dbg !2130
  %timecondition = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set2, i32 0, i32 69, !dbg !2131
  %4 = load i32, i32* %timecondition, align 8, !dbg !2131
  switch i32 %4, label %sw.default [
    i32 1, label %sw.bb
    i32 2, label %sw.bb8
  ], !dbg !2132

sw.bb:                                            ; preds = %if.end
  br label %sw.default, !dbg !2133

sw.default:                                       ; preds = %if.end, %sw.bb
  %5 = load i64, i64* %timeofdoc.addr, align 8, !dbg !2135
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2138
  %set3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 13, !dbg !2139
  %timevalue4 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set3, i32 0, i32 70, !dbg !2140
  %7 = load i64, i64* %timevalue4, align 8, !dbg !2140
  %cmp5 = icmp sle i64 %5, %7, !dbg !2141
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !2142

if.then6:                                         ; preds = %sw.default
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2143
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %8, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.10, i32 0, i32 0)), !dbg !2145
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2146
  %info = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 19, !dbg !2147
  %timecond = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info, i32 0, i32 4, !dbg !2148
  store i8 1, i8* %timecond, align 8, !dbg !2149
  store i1 false, i1* %retval, align 1, !dbg !2150
  br label %return, !dbg !2150

if.end7:                                          ; preds = %sw.default
  br label %sw.epilog, !dbg !2151

sw.bb8:                                           ; preds = %if.end
  %10 = load i64, i64* %timeofdoc.addr, align 8, !dbg !2152
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2154
  %set9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 13, !dbg !2155
  %timevalue10 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set9, i32 0, i32 70, !dbg !2156
  %12 = load i64, i64* %timevalue10, align 8, !dbg !2156
  %cmp11 = icmp sge i64 %10, %12, !dbg !2157
  br i1 %cmp11, label %if.then12, label %if.end15, !dbg !2158

if.then12:                                        ; preds = %sw.bb8
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2159
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %13, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.11, i32 0, i32 0)), !dbg !2161
  %14 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2162
  %info13 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %14, i32 0, i32 19, !dbg !2163
  %timecond14 = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info13, i32 0, i32 4, !dbg !2164
  store i8 1, i8* %timecond14, align 8, !dbg !2165
  store i1 false, i1* %retval, align 1, !dbg !2166
  br label %return, !dbg !2166

if.end15:                                         ; preds = %sw.bb8
  br label %sw.epilog, !dbg !2167

sw.epilog:                                        ; preds = %if.end15, %if.end7
  store i1 true, i1* %retval, align 1, !dbg !2168
  br label %return, !dbg !2168

return:                                           ; preds = %sw.epilog, %if.then12, %if.then6, %if.then
  %15 = load i1, i1* %retval, align 1, !dbg !2169
  ret i1 %15, !dbg !2169
}

; Function Attrs: nounwind uwtable
define i32 @Curl_readwrite(%struct.connectdata* %conn, %struct.Curl_easy* %data, i8* %done, i8* %comeback) #0 !dbg !1774 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %data.addr = alloca %struct.Curl_easy*, align 8
  %done.addr = alloca i8*, align 8
  %comeback.addr = alloca i8*, align 8
  %k = alloca %struct.SingleRequest*, align 8
  %result = alloca i32, align 4
  %didwhat = alloca i32, align 4
  %fd_read = alloca i32, align 4
  %fd_write = alloca i32, align 4
  %select_res = alloca i32, align 4
  %coerce = alloca %struct.timeval, align 8
  %ms = alloca i64, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2170, metadata !1827), !dbg !2171
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2172, metadata !1827), !dbg !2173
  store i8* %done, i8** %done.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %done.addr, metadata !2174, metadata !1827), !dbg !2175
  store i8* %comeback, i8** %comeback.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %comeback.addr, metadata !2176, metadata !1827), !dbg !2177
  call void @llvm.dbg.declare(metadata %struct.SingleRequest** %k, metadata !2178, metadata !1827), !dbg !2179
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2180
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 12, !dbg !2181
  store %struct.SingleRequest* %req, %struct.SingleRequest** %k, align 8, !dbg !2179
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2182, metadata !1827), !dbg !2183
  call void @llvm.dbg.declare(metadata i32* %didwhat, metadata !2184, metadata !1827), !dbg !2185
  store i32 0, i32* %didwhat, align 4, !dbg !2185
  call void @llvm.dbg.declare(metadata i32* %fd_read, metadata !2186, metadata !1827), !dbg !2187
  call void @llvm.dbg.declare(metadata i32* %fd_write, metadata !2188, metadata !1827), !dbg !2189
  call void @llvm.dbg.declare(metadata i32* %select_res, metadata !2190, metadata !1827), !dbg !2191
  %1 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2192
  %cselect_bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %1, i32 0, i32 67, !dbg !2193
  %2 = load i32, i32* %cselect_bits, align 8, !dbg !2193
  store i32 %2, i32* %select_res, align 4, !dbg !2191
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2194
  %cselect_bits1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %3, i32 0, i32 67, !dbg !2195
  store i32 0, i32* %cselect_bits1, align 8, !dbg !2196
  %4 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2197
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %4, i32 0, i32 31, !dbg !2199
  %5 = load i32, i32* %keepon, align 4, !dbg !2199
  %and = and i32 %5, 21, !dbg !2200
  %cmp = icmp eq i32 %and, 1, !dbg !2201
  br i1 %cmp, label %if.then, label %if.else, !dbg !2202

if.then:                                          ; preds = %entry
  %6 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2203
  %sockfd = getelementptr inbounds %struct.connectdata, %struct.connectdata* %6, i32 0, i32 50, !dbg !2204
  %7 = load i32, i32* %sockfd, align 8, !dbg !2204
  store i32 %7, i32* %fd_read, align 4, !dbg !2205
  br label %if.end, !dbg !2206

if.else:                                          ; preds = %entry
  store i32 -1, i32* %fd_read, align 4, !dbg !2207
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %8 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2208
  %keepon2 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %8, i32 0, i32 31, !dbg !2210
  %9 = load i32, i32* %keepon2, align 4, !dbg !2210
  %and3 = and i32 %9, 42, !dbg !2211
  %cmp4 = icmp eq i32 %and3, 2, !dbg !2212
  br i1 %cmp4, label %if.then5, label %if.else6, !dbg !2213

if.then5:                                         ; preds = %if.end
  %10 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2214
  %writesockfd = getelementptr inbounds %struct.connectdata, %struct.connectdata* %10, i32 0, i32 51, !dbg !2215
  %11 = load i32, i32* %writesockfd, align 4, !dbg !2215
  store i32 %11, i32* %fd_write, align 4, !dbg !2216
  br label %if.end7, !dbg !2217

if.else6:                                         ; preds = %if.end
  store i32 -1, i32* %fd_write, align 4, !dbg !2218
  br label %if.end7

if.end7:                                          ; preds = %if.else6, %if.then5
  %12 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2219
  %data8 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %12, i32 0, i32 0, !dbg !2221
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data8, align 8, !dbg !2221
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 17, !dbg !2222
  %drain = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 48, !dbg !2223
  %14 = load i64, i64* %drain, align 8, !dbg !2223
  %tobool = icmp ne i64 %14, 0, !dbg !2219
  br i1 %tobool, label %if.then9, label %if.end10, !dbg !2224

if.then9:                                         ; preds = %if.end7
  %15 = load i32, i32* %select_res, align 4, !dbg !2225
  %or = or i32 %15, 1, !dbg !2225
  store i32 %or, i32* %select_res, align 4, !dbg !2225
  br label %do.body, !dbg !2227

do.body:                                          ; preds = %if.then9
  br label %do.end, !dbg !2228

do.end:                                           ; preds = %do.body
  br label %if.end10, !dbg !2231

if.end10:                                         ; preds = %do.end, %if.end7
  %16 = load i32, i32* %select_res, align 4, !dbg !2232
  %tobool11 = icmp ne i32 %16, 0, !dbg !2232
  br i1 %tobool11, label %if.end13, label %if.then12, !dbg !2234

if.then12:                                        ; preds = %if.end10
  %17 = load i32, i32* %fd_read, align 4, !dbg !2235
  %18 = load i32, i32* %fd_write, align 4, !dbg !2236
  %call = call i32 @Curl_socket_check(i32 %17, i32 -1, i32 %18, i64 0), !dbg !2237
  store i32 %call, i32* %select_res, align 4, !dbg !2238
  br label %if.end13, !dbg !2239

if.end13:                                         ; preds = %if.then12, %if.end10
  %19 = load i32, i32* %select_res, align 4, !dbg !2240
  %cmp14 = icmp eq i32 %19, 4, !dbg !2242
  br i1 %cmp14, label %if.then15, label %if.end16, !dbg !2243

if.then15:                                        ; preds = %if.end13
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2244
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %20, i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.12, i32 0, i32 0)), !dbg !2246
  store i32 55, i32* %retval, align 4, !dbg !2247
  br label %return, !dbg !2247

if.end16:                                         ; preds = %if.end13
  %21 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2248
  %keepon17 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %21, i32 0, i32 31, !dbg !2250
  %22 = load i32, i32* %keepon17, align 4, !dbg !2250
  %and18 = and i32 %22, 1, !dbg !2251
  %tobool19 = icmp ne i32 %and18, 0, !dbg !2251
  br i1 %tobool19, label %land.lhs.true, label %if.end30, !dbg !2252

land.lhs.true:                                    ; preds = %if.end16
  %23 = load i32, i32* %select_res, align 4, !dbg !2253
  %and20 = and i32 %23, 1, !dbg !2254
  %tobool21 = icmp ne i32 %and20, 0, !dbg !2254
  br i1 %tobool21, label %if.then23, label %lor.lhs.false, !dbg !2255

lor.lhs.false:                                    ; preds = %land.lhs.true
  %24 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2256
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %24, i32 0, i32 43, !dbg !2258
  %stream_was_rewound = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 23, !dbg !2259
  %25 = load i8, i8* %stream_was_rewound, align 1, !dbg !2259
  %tobool22 = trunc i8 %25 to i1, !dbg !2259
  br i1 %tobool22, label %if.then23, label %if.end30, !dbg !2260

if.then23:                                        ; preds = %lor.lhs.false, %land.lhs.true
  %26 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2262
  %27 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2264
  %28 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2265
  %29 = load i8*, i8** %done.addr, align 8, !dbg !2266
  %30 = load i8*, i8** %comeback.addr, align 8, !dbg !2267
  %call24 = call i32 @readwrite_data(%struct.Curl_easy* %26, %struct.connectdata* %27, %struct.SingleRequest* %28, i32* %didwhat, i8* %29, i8* %30), !dbg !2268
  store i32 %call24, i32* %result, align 4, !dbg !2269
  %31 = load i32, i32* %result, align 4, !dbg !2270
  %tobool25 = icmp ne i32 %31, 0, !dbg !2270
  br i1 %tobool25, label %if.then28, label %lor.lhs.false26, !dbg !2272

lor.lhs.false26:                                  ; preds = %if.then23
  %32 = load i8*, i8** %done.addr, align 8, !dbg !2273
  %33 = load i8, i8* %32, align 1, !dbg !2275
  %tobool27 = trunc i8 %33 to i1, !dbg !2275
  br i1 %tobool27, label %if.then28, label %if.end29, !dbg !2276

if.then28:                                        ; preds = %lor.lhs.false26, %if.then23
  %34 = load i32, i32* %result, align 4, !dbg !2277
  store i32 %34, i32* %retval, align 4, !dbg !2278
  br label %return, !dbg !2278

if.end29:                                         ; preds = %lor.lhs.false26
  br label %if.end30, !dbg !2279

if.end30:                                         ; preds = %if.end29, %lor.lhs.false, %if.end16
  %35 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2280
  %keepon31 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %35, i32 0, i32 31, !dbg !2282
  %36 = load i32, i32* %keepon31, align 4, !dbg !2282
  %and32 = and i32 %36, 2, !dbg !2283
  %tobool33 = icmp ne i32 %and32, 0, !dbg !2283
  br i1 %tobool33, label %land.lhs.true34, label %if.end42, !dbg !2284

land.lhs.true34:                                  ; preds = %if.end30
  %37 = load i32, i32* %select_res, align 4, !dbg !2285
  %and35 = and i32 %37, 2, !dbg !2287
  %tobool36 = icmp ne i32 %and35, 0, !dbg !2287
  br i1 %tobool36, label %if.then37, label %if.end42, !dbg !2288

if.then37:                                        ; preds = %land.lhs.true34
  %38 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2289
  %39 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2291
  %40 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2292
  %call38 = call i32 @readwrite_upload(%struct.Curl_easy* %38, %struct.connectdata* %39, %struct.SingleRequest* %40, i32* %didwhat), !dbg !2293
  store i32 %call38, i32* %result, align 4, !dbg !2294
  %41 = load i32, i32* %result, align 4, !dbg !2295
  %tobool39 = icmp ne i32 %41, 0, !dbg !2295
  br i1 %tobool39, label %if.then40, label %if.end41, !dbg !2297

if.then40:                                        ; preds = %if.then37
  %42 = load i32, i32* %result, align 4, !dbg !2298
  store i32 %42, i32* %retval, align 4, !dbg !2299
  br label %return, !dbg !2299

if.end41:                                         ; preds = %if.then37
  br label %if.end42, !dbg !2300

if.end42:                                         ; preds = %if.end41, %land.lhs.true34, %if.end30
  %43 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2301
  %now = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %43, i32 0, i32 9, !dbg !2302
  %call43 = call { i64, i64 } @curlx_tvnow(), !dbg !2303
  %44 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !2303
  %45 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %44, i32 0, i32 0, !dbg !2303
  %46 = extractvalue { i64, i64 } %call43, 0, !dbg !2303
  store i64 %46, i64* %45, align 8, !dbg !2303
  %47 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %44, i32 0, i32 1, !dbg !2303
  %48 = extractvalue { i64, i64 } %call43, 1, !dbg !2303
  store i64 %48, i64* %47, align 8, !dbg !2303
  %49 = bitcast %struct.timeval* %now to i8*, !dbg !2303
  %50 = bitcast %struct.timeval* %coerce to i8*, !dbg !2303
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %49, i8* %50, i64 16, i32 8, i1 false), !dbg !2304
  %51 = load i32, i32* %didwhat, align 4, !dbg !2305
  %tobool44 = icmp ne i32 %51, 0, !dbg !2305
  br i1 %tobool44, label %if.then45, label %if.else54, !dbg !2307

if.then45:                                        ; preds = %if.end42
  %52 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2308
  %bytecountp = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %52, i32 0, i32 1, !dbg !2311
  %53 = load i64*, i64** %bytecountp, align 8, !dbg !2311
  %tobool46 = icmp ne i64* %53, null, !dbg !2308
  br i1 %tobool46, label %if.then47, label %if.end49, !dbg !2312

if.then47:                                        ; preds = %if.then45
  %54 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2313
  %bytecount = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %54, i32 0, i32 4, !dbg !2314
  %55 = load i64, i64* %bytecount, align 8, !dbg !2314
  %56 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2315
  %bytecountp48 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %56, i32 0, i32 1, !dbg !2316
  %57 = load i64*, i64** %bytecountp48, align 8, !dbg !2316
  store i64 %55, i64* %57, align 8, !dbg !2317
  br label %if.end49, !dbg !2318

if.end49:                                         ; preds = %if.then47, %if.then45
  %58 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2319
  %writebytecountp = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %58, i32 0, i32 3, !dbg !2321
  %59 = load i64*, i64** %writebytecountp, align 8, !dbg !2321
  %tobool50 = icmp ne i64* %59, null, !dbg !2319
  br i1 %tobool50, label %if.then51, label %if.end53, !dbg !2322

if.then51:                                        ; preds = %if.end49
  %60 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2323
  %writebytecount = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %60, i32 0, i32 5, !dbg !2324
  %61 = load i64, i64* %writebytecount, align 8, !dbg !2324
  %62 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2325
  %writebytecountp52 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %62, i32 0, i32 3, !dbg !2326
  %63 = load i64*, i64** %writebytecountp52, align 8, !dbg !2326
  store i64 %61, i64* %63, align 8, !dbg !2327
  br label %if.end53, !dbg !2328

if.end53:                                         ; preds = %if.then51, %if.end49
  br label %if.end66, !dbg !2329

if.else54:                                        ; preds = %if.end42
  %64 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2330
  %exp100 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %64, i32 0, i32 23, !dbg !2333
  %65 = load i32, i32* %exp100, align 8, !dbg !2333
  %cmp55 = icmp eq i32 %65, 1, !dbg !2334
  br i1 %cmp55, label %if.then56, label %if.end65, !dbg !2335

if.then56:                                        ; preds = %if.else54
  call void @llvm.dbg.declare(metadata i64* %ms, metadata !2336, metadata !1827), !dbg !2338
  %66 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2339
  %now57 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %66, i32 0, i32 9, !dbg !2339
  %67 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2339
  %start100 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %67, i32 0, i32 22, !dbg !2339
  %68 = bitcast %struct.timeval* %now57 to { i64, i64 }*, !dbg !2339
  %69 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %68, i32 0, i32 0, !dbg !2339
  %70 = load i64, i64* %69, align 8, !dbg !2339
  %71 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %68, i32 0, i32 1, !dbg !2339
  %72 = load i64, i64* %71, align 8, !dbg !2339
  %73 = bitcast %struct.timeval* %start100 to { i64, i64 }*, !dbg !2339
  %74 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %73, i32 0, i32 0, !dbg !2339
  %75 = load i64, i64* %74, align 8, !dbg !2339
  %76 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %73, i32 0, i32 1, !dbg !2339
  %77 = load i64, i64* %76, align 8, !dbg !2339
  %call58 = call i64 @curlx_tvdiff(i64 %70, i64 %72, i64 %75, i64 %77), !dbg !2339
  store i64 %call58, i64* %ms, align 8, !dbg !2338
  %78 = load i64, i64* %ms, align 8, !dbg !2340
  %79 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2342
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %79, i32 0, i32 13, !dbg !2343
  %expect_100_timeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 151, !dbg !2344
  %80 = load i64, i64* %expect_100_timeout, align 8, !dbg !2344
  %cmp59 = icmp sge i64 %78, %80, !dbg !2345
  br i1 %cmp59, label %if.then60, label %if.end64, !dbg !2346

if.then60:                                        ; preds = %if.then56
  %81 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2347
  %exp10061 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %81, i32 0, i32 23, !dbg !2349
  store i32 0, i32* %exp10061, align 8, !dbg !2350
  %82 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2351
  %keepon62 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %82, i32 0, i32 31, !dbg !2352
  %83 = load i32, i32* %keepon62, align 4, !dbg !2353
  %or63 = or i32 %83, 2, !dbg !2353
  store i32 %or63, i32* %keepon62, align 4, !dbg !2353
  %84 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2354
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %84, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.13, i32 0, i32 0)), !dbg !2355
  br label %if.end64, !dbg !2356

if.end64:                                         ; preds = %if.then60, %if.then56
  br label %if.end65, !dbg !2357

if.end65:                                         ; preds = %if.end64, %if.else54
  br label %if.end66

if.end66:                                         ; preds = %if.end65, %if.end53
  %85 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2358
  %call67 = call i32 @Curl_pgrsUpdate(%struct.connectdata* %85), !dbg !2360
  %tobool68 = icmp ne i32 %call67, 0, !dbg !2360
  br i1 %tobool68, label %if.then69, label %if.else70, !dbg !2361

if.then69:                                        ; preds = %if.end66
  store i32 42, i32* %result, align 4, !dbg !2362
  br label %if.end73, !dbg !2363

if.else70:                                        ; preds = %if.end66
  %86 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2364
  %87 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2365
  %now71 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %87, i32 0, i32 9, !dbg !2366
  %88 = bitcast %struct.timeval* %now71 to { i64, i64 }*, !dbg !2367
  %89 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %88, i32 0, i32 0, !dbg !2367
  %90 = load i64, i64* %89, align 8, !dbg !2367
  %91 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %88, i32 0, i32 1, !dbg !2367
  %92 = load i64, i64* %91, align 8, !dbg !2367
  %call72 = call i32 @Curl_speedcheck(%struct.Curl_easy* %86, i64 %90, i64 %92), !dbg !2367
  store i32 %call72, i32* %result, align 4, !dbg !2368
  br label %if.end73

if.end73:                                         ; preds = %if.else70, %if.then69
  %93 = load i32, i32* %result, align 4, !dbg !2369
  %tobool74 = icmp ne i32 %93, 0, !dbg !2369
  br i1 %tobool74, label %if.then75, label %if.end76, !dbg !2371

if.then75:                                        ; preds = %if.end73
  %94 = load i32, i32* %result, align 4, !dbg !2372
  store i32 %94, i32* %retval, align 4, !dbg !2373
  br label %return, !dbg !2373

if.end76:                                         ; preds = %if.end73
  %95 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2374
  %keepon77 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %95, i32 0, i32 31, !dbg !2376
  %96 = load i32, i32* %keepon77, align 4, !dbg !2376
  %tobool78 = icmp ne i32 %96, 0, !dbg !2374
  br i1 %tobool78, label %if.then79, label %if.else98, !dbg !2377

if.then79:                                        ; preds = %if.end76
  %97 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2378
  %98 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2381
  %now80 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %98, i32 0, i32 9, !dbg !2382
  %call81 = call i64 @Curl_timeleft(%struct.Curl_easy* %97, %struct.timeval* %now80, i1 zeroext false), !dbg !2383
  %cmp82 = icmp sgt i64 0, %call81, !dbg !2384
  br i1 %cmp82, label %if.then83, label %if.end97, !dbg !2385

if.then83:                                        ; preds = %if.then79
  %99 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2386
  %size = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %99, i32 0, i32 0, !dbg !2389
  %100 = load i64, i64* %size, align 8, !dbg !2389
  %cmp84 = icmp ne i64 %100, -1, !dbg !2390
  br i1 %cmp84, label %if.then85, label %if.else90, !dbg !2391

if.then85:                                        ; preds = %if.then83
  %101 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2392
  %102 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2394
  %now86 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %102, i32 0, i32 9, !dbg !2394
  %103 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2394
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %103, i32 0, i32 16, !dbg !2394
  %t_startsingle = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 19, !dbg !2394
  %104 = bitcast %struct.timeval* %now86 to { i64, i64 }*, !dbg !2394
  %105 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %104, i32 0, i32 0, !dbg !2394
  %106 = load i64, i64* %105, align 8, !dbg !2394
  %107 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %104, i32 0, i32 1, !dbg !2394
  %108 = load i64, i64* %107, align 8, !dbg !2394
  %109 = bitcast %struct.timeval* %t_startsingle to { i64, i64 }*, !dbg !2394
  %110 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %109, i32 0, i32 0, !dbg !2394
  %111 = load i64, i64* %110, align 8, !dbg !2394
  %112 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %109, i32 0, i32 1, !dbg !2394
  %113 = load i64, i64* %112, align 8, !dbg !2394
  %call87 = call i64 @curlx_tvdiff(i64 %106, i64 %108, i64 %111, i64 %113), !dbg !2394
  %114 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2395
  %bytecount88 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %114, i32 0, i32 4, !dbg !2396
  %115 = load i64, i64* %bytecount88, align 8, !dbg !2396
  %116 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2397
  %size89 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %116, i32 0, i32 0, !dbg !2398
  %117 = load i64, i64* %size89, align 8, !dbg !2398
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %101, i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.14, i32 0, i32 0), i64 %call87, i64 %115, i64 %117), !dbg !2399
  br label %if.end96, !dbg !2400

if.else90:                                        ; preds = %if.then83
  %118 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2401
  %119 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2403
  %now91 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %119, i32 0, i32 9, !dbg !2403
  %120 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2403
  %progress92 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %120, i32 0, i32 16, !dbg !2403
  %t_startsingle93 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress92, i32 0, i32 19, !dbg !2403
  %121 = bitcast %struct.timeval* %now91 to { i64, i64 }*, !dbg !2403
  %122 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %121, i32 0, i32 0, !dbg !2403
  %123 = load i64, i64* %122, align 8, !dbg !2403
  %124 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %121, i32 0, i32 1, !dbg !2403
  %125 = load i64, i64* %124, align 8, !dbg !2403
  %126 = bitcast %struct.timeval* %t_startsingle93 to { i64, i64 }*, !dbg !2403
  %127 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %126, i32 0, i32 0, !dbg !2403
  %128 = load i64, i64* %127, align 8, !dbg !2403
  %129 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %126, i32 0, i32 1, !dbg !2403
  %130 = load i64, i64* %129, align 8, !dbg !2403
  %call94 = call i64 @curlx_tvdiff(i64 %123, i64 %125, i64 %128, i64 %130), !dbg !2403
  %131 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2404
  %bytecount95 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %131, i32 0, i32 4, !dbg !2405
  %132 = load i64, i64* %bytecount95, align 8, !dbg !2405
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %118, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.15, i32 0, i32 0), i64 %call94, i64 %132), !dbg !2406
  br label %if.end96

if.end96:                                         ; preds = %if.else90, %if.then85
  store i32 28, i32* %retval, align 4, !dbg !2407
  br label %return, !dbg !2407

if.end97:                                         ; preds = %if.then79
  br label %if.end135, !dbg !2408

if.else98:                                        ; preds = %if.end76
  %133 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2409
  %set99 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %133, i32 0, i32 13, !dbg !2412
  %opt_no_body = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set99, i32 0, i32 103, !dbg !2413
  %134 = load i8, i8* %opt_no_body, align 8, !dbg !2413
  %tobool100 = trunc i8 %134 to i1, !dbg !2413
  br i1 %tobool100, label %if.end119, label %land.lhs.true101, !dbg !2414

land.lhs.true101:                                 ; preds = %if.else98
  %135 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2415
  %size102 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %135, i32 0, i32 0, !dbg !2417
  %136 = load i64, i64* %size102, align 8, !dbg !2417
  %cmp103 = icmp ne i64 %136, -1, !dbg !2418
  br i1 %cmp103, label %land.lhs.true104, label %if.end119, !dbg !2419

land.lhs.true104:                                 ; preds = %land.lhs.true101
  %137 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2420
  %bytecount105 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %137, i32 0, i32 4, !dbg !2421
  %138 = load i64, i64* %bytecount105, align 8, !dbg !2421
  %139 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2422
  %size106 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %139, i32 0, i32 0, !dbg !2423
  %140 = load i64, i64* %size106, align 8, !dbg !2423
  %cmp107 = icmp ne i64 %138, %140, !dbg !2424
  br i1 %cmp107, label %land.lhs.true108, label %if.end119, !dbg !2425

land.lhs.true108:                                 ; preds = %land.lhs.true104
  %141 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2426
  %bytecount109 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %141, i32 0, i32 4, !dbg !2427
  %142 = load i64, i64* %bytecount109, align 8, !dbg !2427
  %143 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2428
  %size110 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %143, i32 0, i32 0, !dbg !2429
  %144 = load i64, i64* %size110, align 8, !dbg !2429
  %145 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2430
  %state111 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %145, i32 0, i32 17, !dbg !2431
  %crlf_conversions = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state111, i32 0, i32 36, !dbg !2432
  %146 = load i64, i64* %crlf_conversions, align 8, !dbg !2432
  %add = add nsw i64 %144, %146, !dbg !2433
  %cmp112 = icmp ne i64 %142, %add, !dbg !2434
  br i1 %cmp112, label %land.lhs.true113, label %if.end119, !dbg !2435

land.lhs.true113:                                 ; preds = %land.lhs.true108
  %147 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2436
  %req114 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %147, i32 0, i32 12, !dbg !2437
  %newurl = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req114, i32 0, i32 36, !dbg !2438
  %148 = load i8*, i8** %newurl, align 8, !dbg !2438
  %tobool115 = icmp ne i8* %148, null, !dbg !2436
  br i1 %tobool115, label %if.end119, label %if.then116, !dbg !2439

if.then116:                                       ; preds = %land.lhs.true113
  %149 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2441
  %150 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2443
  %size117 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %150, i32 0, i32 0, !dbg !2444
  %151 = load i64, i64* %size117, align 8, !dbg !2444
  %152 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2445
  %bytecount118 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %152, i32 0, i32 4, !dbg !2446
  %153 = load i64, i64* %bytecount118, align 8, !dbg !2446
  %sub = sub nsw i64 %151, %153, !dbg !2447
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %149, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.16, i32 0, i32 0), i64 %sub), !dbg !2448
  store i32 18, i32* %retval, align 4, !dbg !2449
  br label %return, !dbg !2449

if.end119:                                        ; preds = %land.lhs.true113, %land.lhs.true108, %land.lhs.true104, %land.lhs.true101, %if.else98
  %154 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2450
  %set120 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %154, i32 0, i32 13, !dbg !2452
  %opt_no_body121 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set120, i32 0, i32 103, !dbg !2453
  %155 = load i8, i8* %opt_no_body121, align 8, !dbg !2453
  %tobool122 = trunc i8 %155 to i1, !dbg !2453
  br i1 %tobool122, label %if.end130, label %land.lhs.true123, !dbg !2454

land.lhs.true123:                                 ; preds = %if.end119
  %156 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2455
  %chunk = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %156, i32 0, i32 39, !dbg !2456
  %157 = load i8, i8* %chunk, align 8, !dbg !2456
  %tobool124 = trunc i8 %157 to i1, !dbg !2456
  br i1 %tobool124, label %land.lhs.true125, label %if.end130, !dbg !2457

land.lhs.true125:                                 ; preds = %land.lhs.true123
  %158 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2458
  %chunk126 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %158, i32 0, i32 1, !dbg !2459
  %state127 = getelementptr inbounds %struct.Curl_chunker, %struct.Curl_chunker* %chunk126, i32 0, i32 2, !dbg !2460
  %159 = load i32, i32* %state127, align 8, !dbg !2460
  %cmp128 = icmp ne i32 %159, 4, !dbg !2461
  br i1 %cmp128, label %if.then129, label %if.end130, !dbg !2462

if.then129:                                       ; preds = %land.lhs.true125
  %160 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2464
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %160, i8* getelementptr inbounds ([53 x i8], [53 x i8]* @.str.17, i32 0, i32 0)), !dbg !2466
  store i32 18, i32* %retval, align 4, !dbg !2467
  br label %return, !dbg !2467

if.end130:                                        ; preds = %land.lhs.true125, %land.lhs.true123, %if.end119
  %161 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2468
  %call131 = call i32 @Curl_pgrsUpdate(%struct.connectdata* %161), !dbg !2470
  %tobool132 = icmp ne i32 %call131, 0, !dbg !2470
  br i1 %tobool132, label %if.then133, label %if.end134, !dbg !2471

if.then133:                                       ; preds = %if.end130
  store i32 42, i32* %retval, align 4, !dbg !2472
  br label %return, !dbg !2472

if.end134:                                        ; preds = %if.end130
  br label %if.end135

if.end135:                                        ; preds = %if.end134, %if.end97
  %162 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2473
  %keepon136 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %162, i32 0, i32 31, !dbg !2474
  %163 = load i32, i32* %keepon136, align 4, !dbg !2474
  %and137 = and i32 %163, 51, !dbg !2475
  %cmp138 = icmp eq i32 0, %and137, !dbg !2476
  %cond = select i1 %cmp138, i32 1, i32 0, !dbg !2477
  %tobool139 = icmp ne i32 %cond, 0, !dbg !2477
  %164 = load i8*, i8** %done.addr, align 8, !dbg !2478
  %frombool = zext i1 %tobool139 to i8, !dbg !2479
  store i8 %frombool, i8* %164, align 1, !dbg !2479
  store i32 0, i32* %retval, align 4, !dbg !2480
  br label %return, !dbg !2480

return:                                           ; preds = %if.end135, %if.then133, %if.then129, %if.then116, %if.end96, %if.then75, %if.then40, %if.then28, %if.then15
  %165 = load i32, i32* %retval, align 4, !dbg !2481
  ret i32 %165, !dbg !2481
}

declare i32 @Curl_socket_check(i32, i32, i32, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @readwrite_data(%struct.Curl_easy* %data, %struct.connectdata* %conn, %struct.SingleRequest* %k, i32* %didwhat, i8* %done, i8* %comeback) #0 !dbg !1795 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %conn.addr = alloca %struct.connectdata*, align 8
  %k.addr = alloca %struct.SingleRequest*, align 8
  %didwhat.addr = alloca i32*, align 8
  %done.addr = alloca i8*, align 8
  %comeback.addr = alloca i8*, align 8
  %result = alloca i32, align 4
  %nread = alloca i64, align 8
  %excess = alloca i64, align 8
  %is_empty_data = alloca i8, align 1
  %readmore = alloca i8, align 1
  %maxloops = alloca i32, align 4
  %buffersize = alloca i64, align 8
  %bytestoread = alloca i64, align 8
  %totalleft = alloca i64, align 8
  %coerce = alloca %struct.timeval, align 8
  %stop_reading = alloca i8, align 1
  %res = alloca i32, align 4
  %dataleft = alloca i64, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2482, metadata !1827), !dbg !2483
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2484, metadata !1827), !dbg !2485
  store %struct.SingleRequest* %k, %struct.SingleRequest** %k.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.SingleRequest** %k.addr, metadata !2486, metadata !1827), !dbg !2487
  store i32* %didwhat, i32** %didwhat.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %didwhat.addr, metadata !2488, metadata !1827), !dbg !2489
  store i8* %done, i8** %done.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %done.addr, metadata !2490, metadata !1827), !dbg !2491
  store i8* %comeback, i8** %comeback.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %comeback.addr, metadata !2492, metadata !1827), !dbg !2493
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2494, metadata !1827), !dbg !2495
  store i32 0, i32* %result, align 4, !dbg !2495
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !2496, metadata !1827), !dbg !2497
  call void @llvm.dbg.declare(metadata i64* %excess, metadata !2498, metadata !1827), !dbg !2499
  store i64 0, i64* %excess, align 8, !dbg !2499
  call void @llvm.dbg.declare(metadata i8* %is_empty_data, metadata !2500, metadata !1827), !dbg !2501
  store i8 0, i8* %is_empty_data, align 1, !dbg !2501
  call void @llvm.dbg.declare(metadata i8* %readmore, metadata !2502, metadata !1827), !dbg !2503
  store i8 0, i8* %readmore, align 1, !dbg !2503
  call void @llvm.dbg.declare(metadata i32* %maxloops, metadata !2504, metadata !1827), !dbg !2505
  store i32 100, i32* %maxloops, align 4, !dbg !2505
  %0 = load i8*, i8** %done.addr, align 8, !dbg !2506
  store i8 0, i8* %0, align 1, !dbg !2507
  %1 = load i8*, i8** %comeback.addr, align 8, !dbg !2508
  store i8 0, i8* %1, align 1, !dbg !2509
  br label %do.body, !dbg !2510

do.body:                                          ; preds = %land.end345, %entry
  call void @llvm.dbg.declare(metadata i64* %buffersize, metadata !2511, metadata !1827), !dbg !2513
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2514
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 13, !dbg !2515
  %buffer_size = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 78, !dbg !2516
  %3 = load i64, i64* %buffer_size, align 8, !dbg !2516
  %tobool = icmp ne i64 %3, 0, !dbg !2514
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !2514

cond.true:                                        ; preds = %do.body
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2517
  %set1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 13, !dbg !2518
  %buffer_size2 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set1, i32 0, i32 78, !dbg !2519
  %5 = load i64, i64* %buffer_size2, align 8, !dbg !2519
  br label %cond.end, !dbg !2520

cond.false:                                       ; preds = %do.body
  br label %cond.end, !dbg !2522

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %5, %cond.true ], [ 16384, %cond.false ], !dbg !2524
  store i64 %cond, i64* %buffersize, align 8, !dbg !2526
  call void @llvm.dbg.declare(metadata i64* %bytestoread, metadata !2527, metadata !1827), !dbg !2528
  %6 = load i64, i64* %buffersize, align 8, !dbg !2529
  store i64 %6, i64* %bytestoread, align 8, !dbg !2528
  %7 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2530
  %size = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %7, i32 0, i32 0, !dbg !2532
  %8 = load i64, i64* %size, align 8, !dbg !2532
  %cmp = icmp ne i64 %8, -1, !dbg !2533
  br i1 %cmp, label %land.lhs.true, label %if.end7, !dbg !2534

land.lhs.true:                                    ; preds = %cond.end
  %9 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2535
  %header = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %9, i32 0, i32 10, !dbg !2537
  %10 = load i8, i8* %header, align 8, !dbg !2537
  %tobool3 = trunc i8 %10 to i1, !dbg !2537
  br i1 %tobool3, label %if.end7, label %if.then, !dbg !2538

if.then:                                          ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i64* %totalleft, metadata !2539, metadata !1827), !dbg !2541
  %11 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2542
  %size4 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %11, i32 0, i32 0, !dbg !2543
  %12 = load i64, i64* %size4, align 8, !dbg !2543
  %13 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2544
  %bytecount = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %13, i32 0, i32 4, !dbg !2545
  %14 = load i64, i64* %bytecount, align 8, !dbg !2545
  %sub = sub nsw i64 %12, %14, !dbg !2546
  store i64 %sub, i64* %totalleft, align 8, !dbg !2541
  %15 = load i64, i64* %totalleft, align 8, !dbg !2547
  %16 = load i64, i64* %bytestoread, align 8, !dbg !2549
  %cmp5 = icmp slt i64 %15, %16, !dbg !2550
  br i1 %cmp5, label %if.then6, label %if.end, !dbg !2551

if.then6:                                         ; preds = %if.then
  %17 = load i64, i64* %totalleft, align 8, !dbg !2552
  store i64 %17, i64* %bytestoread, align 8, !dbg !2553
  br label %if.end, !dbg !2554

if.end:                                           ; preds = %if.then6, %if.then
  br label %if.end7, !dbg !2555

if.end7:                                          ; preds = %if.end, %land.lhs.true, %cond.end
  %18 = load i64, i64* %bytestoread, align 8, !dbg !2556
  %tobool8 = icmp ne i64 %18, 0, !dbg !2556
  br i1 %tobool8, label %if.then9, label %if.else, !dbg !2558

if.then9:                                         ; preds = %if.end7
  %19 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2559
  %20 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2561
  %sockfd = getelementptr inbounds %struct.connectdata, %struct.connectdata* %20, i32 0, i32 50, !dbg !2562
  %21 = load i32, i32* %sockfd, align 8, !dbg !2562
  %22 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2563
  %buf = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %22, i32 0, i32 28, !dbg !2564
  %23 = load i8*, i8** %buf, align 8, !dbg !2564
  %24 = load i64, i64* %bytestoread, align 8, !dbg !2565
  %call = call i32 @Curl_read(%struct.connectdata* %19, i32 %21, i8* %23, i64 %24, i64* %nread), !dbg !2566
  store i32 %call, i32* %result, align 4, !dbg !2567
  %25 = load i32, i32* %result, align 4, !dbg !2568
  %cmp10 = icmp eq i32 81, %25, !dbg !2570
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !2571

if.then11:                                        ; preds = %if.then9
  br label %do.end346, !dbg !2572

if.end12:                                         ; preds = %if.then9
  %26 = load i32, i32* %result, align 4, !dbg !2573
  %cmp13 = icmp ugt i32 %26, 0, !dbg !2575
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !2576

if.then14:                                        ; preds = %if.end12
  %27 = load i32, i32* %result, align 4, !dbg !2577
  store i32 %27, i32* %retval, align 4, !dbg !2578
  br label %return, !dbg !2578

if.end15:                                         ; preds = %if.end12
  br label %if.end17, !dbg !2579

if.else:                                          ; preds = %if.end7
  br label %do.body16, !dbg !2580

do.body16:                                        ; preds = %if.else
  br label %do.end, !dbg !2582

do.end:                                           ; preds = %do.body16
  store i64 0, i64* %nread, align 8, !dbg !2585
  br label %if.end17

if.end17:                                         ; preds = %do.end, %if.end15
  %28 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2586
  %bytecount18 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %28, i32 0, i32 4, !dbg !2588
  %29 = load i64, i64* %bytecount18, align 8, !dbg !2588
  %cmp19 = icmp eq i64 %29, 0, !dbg !2589
  br i1 %cmp19, label %land.lhs.true20, label %if.end27, !dbg !2590

land.lhs.true20:                                  ; preds = %if.end17
  %30 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2591
  %writebytecount = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %30, i32 0, i32 5, !dbg !2593
  %31 = load i64, i64* %writebytecount, align 8, !dbg !2593
  %cmp21 = icmp eq i64 %31, 0, !dbg !2594
  br i1 %cmp21, label %if.then22, label %if.end27, !dbg !2595

if.then22:                                        ; preds = %land.lhs.true20
  %32 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2596
  call void @Curl_pgrsTime(%struct.Curl_easy* %32, i32 7), !dbg !2598
  %33 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2599
  %exp100 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %33, i32 0, i32 23, !dbg !2601
  %34 = load i32, i32* %exp100, align 8, !dbg !2601
  %cmp23 = icmp ugt i32 %34, 0, !dbg !2602
  br i1 %cmp23, label %if.then24, label %if.end26, !dbg !2603

if.then24:                                        ; preds = %if.then22
  %35 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2604
  %start100 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %35, i32 0, i32 22, !dbg !2605
  %call25 = call { i64, i64 } @curlx_tvnow(), !dbg !2606
  %36 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !2606
  %37 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %36, i32 0, i32 0, !dbg !2606
  %38 = extractvalue { i64, i64 } %call25, 0, !dbg !2606
  store i64 %38, i64* %37, align 8, !dbg !2606
  %39 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %36, i32 0, i32 1, !dbg !2606
  %40 = extractvalue { i64, i64 } %call25, 1, !dbg !2606
  store i64 %40, i64* %39, align 8, !dbg !2606
  %41 = bitcast %struct.timeval* %start100 to i8*, !dbg !2606
  %42 = bitcast %struct.timeval* %coerce to i8*, !dbg !2606
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %41, i8* %42, i64 16, i32 8, i1 false), !dbg !2607
  br label %if.end26, !dbg !2604

if.end26:                                         ; preds = %if.then24, %if.then22
  br label %if.end27, !dbg !2609

if.end27:                                         ; preds = %if.end26, %land.lhs.true20, %if.end17
  %43 = load i32*, i32** %didwhat.addr, align 8, !dbg !2610
  %44 = load i32, i32* %43, align 4, !dbg !2611
  %or = or i32 %44, 1, !dbg !2611
  store i32 %or, i32* %43, align 4, !dbg !2611
  %45 = load i64, i64* %nread, align 8, !dbg !2612
  %cmp28 = icmp eq i64 %45, 0, !dbg !2613
  br i1 %cmp28, label %land.rhs, label %land.end, !dbg !2614

land.rhs:                                         ; preds = %if.end27
  %46 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2615
  %bodywrites = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %46, i32 0, i32 27, !dbg !2616
  %47 = load i64, i64* %bodywrites, align 8, !dbg !2616
  %cmp29 = icmp eq i64 %47, 0, !dbg !2617
  br label %land.end

land.end:                                         ; preds = %land.rhs, %if.end27
  %48 = phi i1 [ false, %if.end27 ], [ %cmp29, %land.rhs ]
  %cond30 = select i1 %48, i32 1, i32 0, !dbg !2618
  %tobool31 = icmp ne i32 %cond30, 0, !dbg !2618
  %frombool = zext i1 %tobool31 to i8, !dbg !2619
  store i8 %frombool, i8* %is_empty_data, align 1, !dbg !2619
  %49 = load i64, i64* %nread, align 8, !dbg !2620
  %cmp32 = icmp slt i64 0, %49, !dbg !2622
  br i1 %cmp32, label %if.then34, label %lor.lhs.false, !dbg !2623

lor.lhs.false:                                    ; preds = %land.end
  %50 = load i8, i8* %is_empty_data, align 1, !dbg !2624
  %tobool33 = trunc i8 %50 to i1, !dbg !2624
  br i1 %tobool33, label %if.then34, label %if.else36, !dbg !2626

if.then34:                                        ; preds = %lor.lhs.false, %land.end
  %51 = load i64, i64* %nread, align 8, !dbg !2627
  %52 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2629
  %buf35 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %52, i32 0, i32 28, !dbg !2630
  %53 = load i8*, i8** %buf35, align 8, !dbg !2630
  %arrayidx = getelementptr inbounds i8, i8* %53, i64 %51, !dbg !2629
  store i8 0, i8* %arrayidx, align 1, !dbg !2631
  br label %if.end42, !dbg !2632

if.else36:                                        ; preds = %lor.lhs.false
  %54 = load i64, i64* %nread, align 8, !dbg !2633
  %cmp37 = icmp sge i64 0, %54, !dbg !2635
  br i1 %cmp37, label %if.then38, label %if.end41, !dbg !2636

if.then38:                                        ; preds = %if.else36
  br label %do.body39, !dbg !2637

do.body39:                                        ; preds = %if.then38
  br label %do.end40, !dbg !2639

do.end40:                                         ; preds = %do.body39
  %55 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2642
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %55, i32 0, i32 31, !dbg !2643
  %56 = load i32, i32* %keepon, align 4, !dbg !2644
  %and = and i32 %56, -2, !dbg !2644
  store i32 %and, i32* %keepon, align 4, !dbg !2644
  br label %do.end346, !dbg !2645

if.end41:                                         ; preds = %if.else36
  br label %if.end42

if.end42:                                         ; preds = %if.end41, %if.then34
  %57 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2646
  %buf43 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %57, i32 0, i32 28, !dbg !2647
  %58 = load i8*, i8** %buf43, align 8, !dbg !2647
  %59 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2648
  %str = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %59, i32 0, i32 15, !dbg !2649
  store i8* %58, i8** %str, align 8, !dbg !2650
  %60 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2651
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %60, i32 0, i32 47, !dbg !2653
  %61 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !2653
  %readwrite = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %61, i32 0, i32 13, !dbg !2654
  %62 = load i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)** %readwrite, align 8, !dbg !2654
  %tobool44 = icmp ne i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)* %62, null, !dbg !2651
  br i1 %tobool44, label %if.then45, label %if.end55, !dbg !2655

if.then45:                                        ; preds = %if.end42
  %63 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2656
  %handler46 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %63, i32 0, i32 47, !dbg !2658
  %64 = load %struct.Curl_handler*, %struct.Curl_handler** %handler46, align 8, !dbg !2658
  %readwrite47 = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %64, i32 0, i32 13, !dbg !2659
  %65 = load i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)** %readwrite47, align 8, !dbg !2659
  %66 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2660
  %67 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2661
  %call48 = call i32 %65(%struct.Curl_easy* %66, %struct.connectdata* %67, i64* %nread, i8* %readmore), !dbg !2656
  store i32 %call48, i32* %result, align 4, !dbg !2662
  %68 = load i32, i32* %result, align 4, !dbg !2663
  %tobool49 = icmp ne i32 %68, 0, !dbg !2663
  br i1 %tobool49, label %if.then50, label %if.end51, !dbg !2665

if.then50:                                        ; preds = %if.then45
  %69 = load i32, i32* %result, align 4, !dbg !2666
  store i32 %69, i32* %retval, align 4, !dbg !2667
  br label %return, !dbg !2667

if.end51:                                         ; preds = %if.then45
  %70 = load i8, i8* %readmore, align 1, !dbg !2668
  %tobool52 = trunc i8 %70 to i1, !dbg !2668
  br i1 %tobool52, label %if.then53, label %if.end54, !dbg !2670

if.then53:                                        ; preds = %if.end51
  br label %do.end346, !dbg !2671

if.end54:                                         ; preds = %if.end51
  br label %if.end55, !dbg !2672

if.end55:                                         ; preds = %if.end54, %if.end42
  %71 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2673
  %header56 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %71, i32 0, i32 10, !dbg !2675
  %72 = load i8, i8* %header56, align 8, !dbg !2675
  %tobool57 = trunc i8 %72 to i1, !dbg !2675
  br i1 %tobool57, label %if.then58, label %if.end94, !dbg !2676

if.then58:                                        ; preds = %if.end55
  call void @llvm.dbg.declare(metadata i8* %stop_reading, metadata !2677, metadata !1827), !dbg !2679
  store i8 0, i8* %stop_reading, align 1, !dbg !2679
  %73 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2680
  %74 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2681
  %call59 = call i32 @Curl_http_readwrite_headers(%struct.Curl_easy* %73, %struct.connectdata* %74, i64* %nread, i8* %stop_reading), !dbg !2682
  store i32 %call59, i32* %result, align 4, !dbg !2683
  %75 = load i32, i32* %result, align 4, !dbg !2684
  %tobool60 = icmp ne i32 %75, 0, !dbg !2684
  br i1 %tobool60, label %if.then61, label %if.end62, !dbg !2686

if.then61:                                        ; preds = %if.then58
  %76 = load i32, i32* %result, align 4, !dbg !2687
  store i32 %76, i32* %retval, align 4, !dbg !2688
  br label %return, !dbg !2688

if.end62:                                         ; preds = %if.then58
  %77 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2689
  %handler63 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %77, i32 0, i32 47, !dbg !2691
  %78 = load %struct.Curl_handler*, %struct.Curl_handler** %handler63, align 8, !dbg !2691
  %readwrite64 = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %78, i32 0, i32 13, !dbg !2692
  %79 = load i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)** %readwrite64, align 8, !dbg !2692
  %tobool65 = icmp ne i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)* %79, null, !dbg !2689
  br i1 %tobool65, label %land.lhs.true66, label %if.end80, !dbg !2693

land.lhs.true66:                                  ; preds = %if.end62
  %80 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2694
  %maxdownload = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %80, i32 0, i32 2, !dbg !2695
  %81 = load i64, i64* %maxdownload, align 8, !dbg !2695
  %cmp67 = icmp sle i64 %81, 0, !dbg !2696
  br i1 %cmp67, label %land.lhs.true68, label %if.end80, !dbg !2697

land.lhs.true68:                                  ; preds = %land.lhs.true66
  %82 = load i64, i64* %nread, align 8, !dbg !2698
  %cmp69 = icmp sgt i64 %82, 0, !dbg !2700
  br i1 %cmp69, label %if.then70, label %if.end80, !dbg !2701

if.then70:                                        ; preds = %land.lhs.true68
  %83 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2703
  %handler71 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %83, i32 0, i32 47, !dbg !2705
  %84 = load %struct.Curl_handler*, %struct.Curl_handler** %handler71, align 8, !dbg !2705
  %readwrite72 = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %84, i32 0, i32 13, !dbg !2706
  %85 = load i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)** %readwrite72, align 8, !dbg !2706
  %86 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2707
  %87 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2708
  %call73 = call i32 %85(%struct.Curl_easy* %86, %struct.connectdata* %87, i64* %nread, i8* %readmore), !dbg !2703
  store i32 %call73, i32* %result, align 4, !dbg !2709
  %88 = load i32, i32* %result, align 4, !dbg !2710
  %tobool74 = icmp ne i32 %88, 0, !dbg !2710
  br i1 %tobool74, label %if.then75, label %if.end76, !dbg !2712

if.then75:                                        ; preds = %if.then70
  %89 = load i32, i32* %result, align 4, !dbg !2713
  store i32 %89, i32* %retval, align 4, !dbg !2714
  br label %return, !dbg !2714

if.end76:                                         ; preds = %if.then70
  %90 = load i8, i8* %readmore, align 1, !dbg !2715
  %tobool77 = trunc i8 %90 to i1, !dbg !2715
  br i1 %tobool77, label %if.then78, label %if.end79, !dbg !2717

if.then78:                                        ; preds = %if.end76
  br label %do.end346, !dbg !2718

if.end79:                                         ; preds = %if.end76
  br label %if.end80, !dbg !2719

if.end80:                                         ; preds = %if.end79, %land.lhs.true68, %land.lhs.true66, %if.end62
  %91 = load i8, i8* %stop_reading, align 1, !dbg !2720
  %tobool81 = trunc i8 %91 to i1, !dbg !2720
  br i1 %tobool81, label %if.then82, label %if.end93, !dbg !2722

if.then82:                                        ; preds = %if.end80
  %92 = load i64, i64* %nread, align 8, !dbg !2723
  %cmp83 = icmp sgt i64 %92, 0, !dbg !2726
  br i1 %cmp83, label %if.then84, label %if.end92, !dbg !2727

if.then84:                                        ; preds = %if.then82
  %93 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2728
  %data85 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %93, i32 0, i32 0, !dbg !2731
  %94 = load %struct.Curl_easy*, %struct.Curl_easy** %data85, align 8, !dbg !2731
  %multi = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %94, i32 0, i32 9, !dbg !2732
  %95 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !2732
  %call86 = call zeroext i1 @Curl_pipeline_wanted(%struct.Curl_multi* %95, i32 1), !dbg !2733
  br i1 %call86, label %if.then87, label %if.else88, !dbg !2734

if.then87:                                        ; preds = %if.then84
  %96 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2735
  %97 = load i64, i64* %nread, align 8, !dbg !2737
  %98 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2738
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %98, i32 0, i32 17, !dbg !2739
  %path = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 38, !dbg !2740
  %99 = load i8*, i8** %path, align 8, !dbg !2740
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %96, i8* getelementptr inbounds ([62 x i8], [62 x i8]* @.str.26, i32 0, i32 0), i64 %97, i8* %99), !dbg !2741
  %100 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2742
  %101 = load i64, i64* %nread, align 8, !dbg !2743
  call void @read_rewind(%struct.connectdata* %100, i64 %101), !dbg !2744
  br label %if.end91, !dbg !2745

if.else88:                                        ; preds = %if.then84
  %102 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2746
  %103 = load i64, i64* %nread, align 8, !dbg !2748
  %104 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2749
  %state89 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %104, i32 0, i32 17, !dbg !2750
  %path90 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state89, i32 0, i32 38, !dbg !2751
  %105 = load i8*, i8** %path90, align 8, !dbg !2751
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %102, i8* getelementptr inbounds ([80 x i8], [80 x i8]* @.str.27, i32 0, i32 0), i64 %103, i8* %105), !dbg !2752
  br label %if.end91

if.end91:                                         ; preds = %if.else88, %if.then87
  br label %if.end92, !dbg !2753

if.end92:                                         ; preds = %if.end91, %if.then82
  br label %do.end346, !dbg !2754

if.end93:                                         ; preds = %if.end80
  br label %if.end94, !dbg !2755

if.end94:                                         ; preds = %if.end93, %if.end55
  %106 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2756
  %str95 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %106, i32 0, i32 15, !dbg !2758
  %107 = load i8*, i8** %str95, align 8, !dbg !2758
  %tobool96 = icmp ne i8* %107, null, !dbg !2756
  br i1 %tobool96, label %land.lhs.true97, label %if.end313, !dbg !2759

land.lhs.true97:                                  ; preds = %if.end94
  %108 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2760
  %header98 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %108, i32 0, i32 10, !dbg !2762
  %109 = load i8, i8* %header98, align 8, !dbg !2762
  %tobool99 = trunc i8 %109 to i1, !dbg !2762
  br i1 %tobool99, label %if.end313, label %land.lhs.true100, !dbg !2763

land.lhs.true100:                                 ; preds = %land.lhs.true97
  %110 = load i64, i64* %nread, align 8, !dbg !2764
  %cmp101 = icmp sgt i64 %110, 0, !dbg !2766
  br i1 %cmp101, label %if.then104, label %lor.lhs.false102, !dbg !2767

lor.lhs.false102:                                 ; preds = %land.lhs.true100
  %111 = load i8, i8* %is_empty_data, align 1, !dbg !2768
  %tobool103 = trunc i8 %111 to i1, !dbg !2768
  br i1 %tobool103, label %if.then104, label %if.end313, !dbg !2770

if.then104:                                       ; preds = %lor.lhs.false102, %land.lhs.true100
  %112 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2771
  %set105 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %112, i32 0, i32 13, !dbg !2774
  %opt_no_body = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set105, i32 0, i32 103, !dbg !2775
  %113 = load i8, i8* %opt_no_body, align 8, !dbg !2775
  %tobool106 = trunc i8 %113 to i1, !dbg !2775
  br i1 %tobool106, label %if.then107, label %if.end108, !dbg !2776

if.then107:                                       ; preds = %if.then104
  %114 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2777
  call void @Curl_conncontrol(%struct.connectdata* %114, i32 2), !dbg !2777
  %115 = load i8*, i8** %done.addr, align 8, !dbg !2779
  store i8 1, i8* %115, align 1, !dbg !2780
  store i32 8, i32* %retval, align 4, !dbg !2781
  br label %return, !dbg !2781

if.end108:                                        ; preds = %if.then104
  %116 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2782
  %bodywrites109 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %116, i32 0, i32 27, !dbg !2784
  %117 = load i64, i64* %bodywrites109, align 8, !dbg !2784
  %cmp110 = icmp eq i64 0, %117, !dbg !2785
  br i1 %cmp110, label %land.lhs.true111, label %if.end157, !dbg !2786

land.lhs.true111:                                 ; preds = %if.end108
  %118 = load i8, i8* %is_empty_data, align 1, !dbg !2787
  %tobool112 = trunc i8 %118 to i1, !dbg !2787
  br i1 %tobool112, label %if.end157, label %if.then113, !dbg !2789

if.then113:                                       ; preds = %land.lhs.true111
  %119 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2790
  %handler114 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %119, i32 0, i32 47, !dbg !2793
  %120 = load %struct.Curl_handler*, %struct.Curl_handler** %handler114, align 8, !dbg !2793
  %protocol = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %120, i32 0, i32 15, !dbg !2794
  %121 = load i32, i32* %protocol, align 8, !dbg !2794
  %and115 = and i32 %121, 262147, !dbg !2795
  %tobool116 = icmp ne i32 %and115, 0, !dbg !2795
  br i1 %tobool116, label %if.then117, label %if.end156, !dbg !2796

if.then117:                                       ; preds = %if.then113
  %122 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2797
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %122, i32 0, i32 12, !dbg !2800
  %newurl = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 36, !dbg !2801
  %123 = load i8*, i8** %newurl, align 8, !dbg !2801
  %tobool118 = icmp ne i8* %123, null, !dbg !2797
  br i1 %tobool118, label %if.then119, label %if.end125, !dbg !2802

if.then119:                                       ; preds = %if.then117
  %124 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2803
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %124, i32 0, i32 43, !dbg !2806
  %close = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 0, !dbg !2807
  %125 = load i8, i8* %close, align 1, !dbg !2807
  %tobool120 = trunc i8 %125 to i1, !dbg !2807
  br i1 %tobool120, label %if.then121, label %if.end124, !dbg !2808

if.then121:                                       ; preds = %if.then119
  %126 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2809
  %keepon122 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %126, i32 0, i32 31, !dbg !2811
  %127 = load i32, i32* %keepon122, align 4, !dbg !2812
  %and123 = and i32 %127, -2, !dbg !2812
  store i32 %and123, i32* %keepon122, align 4, !dbg !2812
  %128 = load i8*, i8** %done.addr, align 8, !dbg !2813
  store i8 1, i8* %128, align 1, !dbg !2814
  store i32 0, i32* %retval, align 4, !dbg !2815
  br label %return, !dbg !2815

if.end124:                                        ; preds = %if.then119
  %129 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2816
  %ignorebody = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %129, i32 0, i32 33, !dbg !2817
  store i8 1, i8* %ignorebody, align 1, !dbg !2818
  %130 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2819
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %130, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.28, i32 0, i32 0)), !dbg !2820
  br label %if.end125, !dbg !2821

if.end125:                                        ; preds = %if.end124, %if.then117
  %131 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2822
  %state126 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %131, i32 0, i32 17, !dbg !2824
  %resume_from = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state126, i32 0, i32 43, !dbg !2825
  %132 = load i64, i64* %resume_from, align 8, !dbg !2825
  %tobool127 = icmp ne i64 %132, 0, !dbg !2822
  br i1 %tobool127, label %land.lhs.true128, label %if.end145, !dbg !2826

land.lhs.true128:                                 ; preds = %if.end125
  %133 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2827
  %content_range = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %133, i32 0, i32 19, !dbg !2829
  %134 = load i8, i8* %content_range, align 8, !dbg !2829
  %tobool129 = trunc i8 %134 to i1, !dbg !2829
  br i1 %tobool129, label %if.end145, label %land.lhs.true130, !dbg !2830

land.lhs.true130:                                 ; preds = %land.lhs.true128
  %135 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2831
  %set131 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %135, i32 0, i32 13, !dbg !2832
  %httpreq = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set131, i32 0, i32 71, !dbg !2833
  %136 = load i32, i32* %httpreq, align 8, !dbg !2833
  %cmp132 = icmp eq i32 %136, 1, !dbg !2834
  br i1 %cmp132, label %land.lhs.true133, label %if.end145, !dbg !2835

land.lhs.true133:                                 ; preds = %land.lhs.true130
  %137 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2836
  %ignorebody134 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %137, i32 0, i32 33, !dbg !2837
  %138 = load i8, i8* %ignorebody134, align 1, !dbg !2837
  %tobool135 = trunc i8 %138 to i1, !dbg !2837
  br i1 %tobool135, label %if.end145, label %if.then136, !dbg !2838

if.then136:                                       ; preds = %land.lhs.true133
  %139 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2840
  %size137 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %139, i32 0, i32 0, !dbg !2843
  %140 = load i64, i64* %size137, align 8, !dbg !2843
  %141 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2844
  %state138 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %141, i32 0, i32 17, !dbg !2845
  %resume_from139 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state138, i32 0, i32 43, !dbg !2846
  %142 = load i64, i64* %resume_from139, align 8, !dbg !2846
  %cmp140 = icmp eq i64 %140, %142, !dbg !2847
  br i1 %cmp140, label %if.then141, label %if.end144, !dbg !2848

if.then141:                                       ; preds = %if.then136
  %143 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2849
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %143, i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.29, i32 0, i32 0)), !dbg !2851
  %144 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2852
  call void @Curl_conncontrol(%struct.connectdata* %144, i32 1), !dbg !2852
  %145 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2853
  %keepon142 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %145, i32 0, i32 31, !dbg !2854
  %146 = load i32, i32* %keepon142, align 4, !dbg !2855
  %and143 = and i32 %146, -2, !dbg !2855
  store i32 %and143, i32* %keepon142, align 4, !dbg !2855
  %147 = load i8*, i8** %done.addr, align 8, !dbg !2856
  store i8 1, i8* %147, align 1, !dbg !2857
  store i32 0, i32* %retval, align 4, !dbg !2858
  br label %return, !dbg !2858

if.end144:                                        ; preds = %if.then136
  %148 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2859
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %148, i8* getelementptr inbounds ([64 x i8], [64 x i8]* @.str.30, i32 0, i32 0)), !dbg !2860
  store i32 33, i32* %retval, align 4, !dbg !2861
  br label %return, !dbg !2861

if.end145:                                        ; preds = %land.lhs.true133, %land.lhs.true130, %land.lhs.true128, %if.end125
  %149 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2862
  %set146 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %149, i32 0, i32 13, !dbg !2864
  %timecondition = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set146, i32 0, i32 69, !dbg !2865
  %150 = load i32, i32* %timecondition, align 8, !dbg !2865
  %tobool147 = icmp ne i32 %150, 0, !dbg !2862
  br i1 %tobool147, label %land.lhs.true148, label %if.end155, !dbg !2866

land.lhs.true148:                                 ; preds = %if.end145
  %151 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2867
  %state149 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %151, i32 0, i32 17, !dbg !2869
  %range = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state149, i32 0, i32 42, !dbg !2870
  %152 = load i8*, i8** %range, align 8, !dbg !2870
  %tobool150 = icmp ne i8* %152, null, !dbg !2867
  br i1 %tobool150, label %if.end155, label %if.then151, !dbg !2871

if.then151:                                       ; preds = %land.lhs.true148
  %153 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2872
  %154 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2875
  %timeofdoc = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %154, i32 0, i32 26, !dbg !2876
  %155 = load i64, i64* %timeofdoc, align 8, !dbg !2876
  %call152 = call zeroext i1 @Curl_meets_timecondition(%struct.Curl_easy* %153, i64 %155), !dbg !2877
  br i1 %call152, label %if.end154, label %if.then153, !dbg !2878

if.then153:                                       ; preds = %if.then151
  %156 = load i8*, i8** %done.addr, align 8, !dbg !2879
  store i8 1, i8* %156, align 1, !dbg !2881
  %157 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2882
  %info = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %157, i32 0, i32 19, !dbg !2883
  %httpcode = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info, i32 0, i32 0, !dbg !2884
  store i32 304, i32* %httpcode, align 8, !dbg !2885
  %158 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2886
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %158, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.31, i32 0, i32 0)), !dbg !2887
  %159 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2888
  call void @Curl_conncontrol(%struct.connectdata* %159, i32 1), !dbg !2888
  store i32 0, i32* %retval, align 4, !dbg !2889
  br label %return, !dbg !2889

if.end154:                                        ; preds = %if.then151
  br label %if.end155, !dbg !2890

if.end155:                                        ; preds = %if.end154, %land.lhs.true148, %if.end145
  br label %if.end156, !dbg !2891

if.end156:                                        ; preds = %if.end155, %if.then113
  br label %if.end157, !dbg !2892

if.end157:                                        ; preds = %if.end156, %land.lhs.true111, %if.end108
  %160 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2893
  %bodywrites158 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %160, i32 0, i32 27, !dbg !2894
  %161 = load i64, i64* %bodywrites158, align 8, !dbg !2895
  %inc = add nsw i64 %161, 1, !dbg !2895
  store i64 %inc, i64* %bodywrites158, align 8, !dbg !2895
  %162 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2896
  %set159 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %162, i32 0, i32 13, !dbg !2898
  %verbose = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set159, i32 0, i32 106, !dbg !2899
  %163 = load i8, i8* %verbose, align 8, !dbg !2899
  %tobool160 = trunc i8 %163 to i1, !dbg !2899
  br i1 %tobool160, label %if.then161, label %if.end176, !dbg !2900

if.then161:                                       ; preds = %if.end157
  %164 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2901
  %badheader = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %164, i32 0, i32 11, !dbg !2904
  %165 = load i32, i32* %badheader, align 4, !dbg !2904
  %tobool162 = icmp ne i32 %165, 0, !dbg !2901
  br i1 %tobool162, label %if.then163, label %if.else172, !dbg !2905

if.then163:                                       ; preds = %if.then161
  %166 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2906
  %167 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2908
  %state164 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %167, i32 0, i32 17, !dbg !2909
  %headerbuff = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state164, i32 0, i32 4, !dbg !2910
  %168 = load i8*, i8** %headerbuff, align 8, !dbg !2910
  %169 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2911
  %hbuflen = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %169, i32 0, i32 14, !dbg !2912
  %170 = load i64, i64* %hbuflen, align 8, !dbg !2912
  %171 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2913
  %call165 = call i32 @Curl_debug(%struct.Curl_easy* %166, i32 3, i8* %168, i64 %170, %struct.connectdata* %171), !dbg !2914
  %172 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2915
  %badheader166 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %172, i32 0, i32 11, !dbg !2917
  %173 = load i32, i32* %badheader166, align 4, !dbg !2917
  %cmp167 = icmp eq i32 %173, 1, !dbg !2918
  br i1 %cmp167, label %if.then168, label %if.end171, !dbg !2919

if.then168:                                       ; preds = %if.then163
  %174 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2920
  %175 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2921
  %str169 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %175, i32 0, i32 15, !dbg !2922
  %176 = load i8*, i8** %str169, align 8, !dbg !2922
  %177 = load i64, i64* %nread, align 8, !dbg !2923
  %178 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2924
  %call170 = call i32 @Curl_debug(%struct.Curl_easy* %174, i32 3, i8* %176, i64 %177, %struct.connectdata* %178), !dbg !2925
  br label %if.end171, !dbg !2925

if.end171:                                        ; preds = %if.then168, %if.then163
  br label %if.end175, !dbg !2926

if.else172:                                       ; preds = %if.then161
  %179 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2927
  %180 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2928
  %str173 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %180, i32 0, i32 15, !dbg !2929
  %181 = load i8*, i8** %str173, align 8, !dbg !2929
  %182 = load i64, i64* %nread, align 8, !dbg !2930
  %183 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2931
  %call174 = call i32 @Curl_debug(%struct.Curl_easy* %179, i32 3, i8* %181, i64 %182, %struct.connectdata* %183), !dbg !2932
  br label %if.end175

if.end175:                                        ; preds = %if.else172, %if.end171
  br label %if.end176, !dbg !2933

if.end176:                                        ; preds = %if.end175, %if.end157
  %184 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2934
  %chunk = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %184, i32 0, i32 39, !dbg !2936
  %185 = load i8, i8* %chunk, align 8, !dbg !2936
  %tobool177 = trunc i8 %185 to i1, !dbg !2936
  br i1 %tobool177, label %if.then178, label %if.end205, !dbg !2937

if.then178:                                       ; preds = %if.end176
  call void @llvm.dbg.declare(metadata i32* %res, metadata !2938, metadata !1827), !dbg !2941
  %186 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2942
  %187 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2943
  %str179 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %187, i32 0, i32 15, !dbg !2944
  %188 = load i8*, i8** %str179, align 8, !dbg !2944
  %189 = load i64, i64* %nread, align 8, !dbg !2945
  %call180 = call i32 @Curl_httpchunk_read(%struct.connectdata* %186, i8* %188, i64 %189, i64* %nread), !dbg !2946
  store i32 %call180, i32* %res, align 4, !dbg !2941
  %190 = load i32, i32* %res, align 4, !dbg !2947
  %cmp181 = icmp slt i32 0, %190, !dbg !2949
  br i1 %cmp181, label %if.then182, label %if.end187, !dbg !2950

if.then182:                                       ; preds = %if.then178
  %191 = load i32, i32* %res, align 4, !dbg !2951
  %cmp183 = icmp eq i32 4, %191, !dbg !2954
  br i1 %cmp183, label %if.then184, label %if.end185, !dbg !2955

if.then184:                                       ; preds = %if.then182
  %192 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2956
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %192, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.32, i32 0, i32 0)), !dbg !2958
  store i32 23, i32* %retval, align 4, !dbg !2959
  br label %return, !dbg !2959

if.end185:                                        ; preds = %if.then182
  %193 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2960
  %194 = load i32, i32* %res, align 4, !dbg !2961
  %call186 = call i8* @Curl_chunked_strerror(i32 %194), !dbg !2962
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %193, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.33, i32 0, i32 0), i8* %call186), !dbg !2963
  store i32 56, i32* %retval, align 4, !dbg !2965
  br label %return, !dbg !2965

if.end187:                                        ; preds = %if.then178
  %195 = load i32, i32* %res, align 4, !dbg !2966
  %cmp188 = icmp eq i32 -1, %195, !dbg !2968
  br i1 %cmp188, label %if.then189, label %if.end204, !dbg !2969

if.then189:                                       ; preds = %if.end187
  call void @llvm.dbg.declare(metadata i64* %dataleft, metadata !2970, metadata !1827), !dbg !2972
  %196 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !2973
  %keepon190 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %196, i32 0, i32 31, !dbg !2974
  %197 = load i32, i32* %keepon190, align 4, !dbg !2975
  %and191 = and i32 %197, -2, !dbg !2975
  store i32 %and191, i32* %keepon190, align 4, !dbg !2975
  %198 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2976
  %chunk192 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %198, i32 0, i32 1, !dbg !2977
  %dataleft193 = getelementptr inbounds %struct.Curl_chunker, %struct.Curl_chunker* %chunk192, i32 0, i32 4, !dbg !2978
  %199 = load i64, i64* %dataleft193, align 8, !dbg !2978
  store i64 %199, i64* %dataleft, align 8, !dbg !2979
  %200 = load i64, i64* %dataleft, align 8, !dbg !2980
  %cmp194 = icmp ne i64 %200, 0, !dbg !2982
  br i1 %cmp194, label %if.then195, label %if.end203, !dbg !2983

if.then195:                                       ; preds = %if.then189
  %201 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2984
  %data196 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %201, i32 0, i32 0, !dbg !2986
  %202 = load %struct.Curl_easy*, %struct.Curl_easy** %data196, align 8, !dbg !2986
  %203 = load i64, i64* %dataleft, align 8, !dbg !2987
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %202, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.34, i32 0, i32 0), i64 %203), !dbg !2988
  %204 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2989
  %data197 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %204, i32 0, i32 0, !dbg !2991
  %205 = load %struct.Curl_easy*, %struct.Curl_easy** %data197, align 8, !dbg !2991
  %multi198 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %205, i32 0, i32 9, !dbg !2992
  %206 = load %struct.Curl_multi*, %struct.Curl_multi** %multi198, align 8, !dbg !2992
  %call199 = call zeroext i1 @Curl_pipeline_wanted(%struct.Curl_multi* %206, i32 1), !dbg !2993
  br i1 %call199, label %if.then200, label %if.end202, !dbg !2994

if.then200:                                       ; preds = %if.then195
  %207 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2995
  %data201 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %207, i32 0, i32 0, !dbg !2997
  %208 = load %struct.Curl_easy*, %struct.Curl_easy** %data201, align 8, !dbg !2997
  %209 = load i64, i64* %dataleft, align 8, !dbg !2998
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %208, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.35, i32 0, i32 0), i64 %209), !dbg !2999
  %210 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3000
  %211 = load i64, i64* %dataleft, align 8, !dbg !3001
  call void @read_rewind(%struct.connectdata* %210, i64 %211), !dbg !3002
  br label %if.end202, !dbg !3003

if.end202:                                        ; preds = %if.then200, %if.then195
  br label %if.end203, !dbg !3004

if.end203:                                        ; preds = %if.end202, %if.then189
  br label %if.end204, !dbg !3005

if.end204:                                        ; preds = %if.end203, %if.end187
  br label %if.end205, !dbg !3006

if.end205:                                        ; preds = %if.end204, %if.end176
  %212 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3007
  %badheader206 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %212, i32 0, i32 11, !dbg !3009
  %213 = load i32, i32* %badheader206, align 4, !dbg !3009
  %tobool207 = icmp ne i32 %213, 0, !dbg !3007
  br i1 %tobool207, label %land.lhs.true208, label %if.end216, !dbg !3010

land.lhs.true208:                                 ; preds = %if.end205
  %214 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3011
  %ignorebody209 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %214, i32 0, i32 33, !dbg !3013
  %215 = load i8, i8* %ignorebody209, align 1, !dbg !3013
  %tobool210 = trunc i8 %215 to i1, !dbg !3013
  br i1 %tobool210, label %if.end216, label %if.then211, !dbg !3014

if.then211:                                       ; preds = %land.lhs.true208
  br label %do.body212, !dbg !3015

do.body212:                                       ; preds = %if.then211
  br label %do.end213, !dbg !3017

do.end213:                                        ; preds = %do.body212
  %216 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3020
  %hbuflen214 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %216, i32 0, i32 14, !dbg !3021
  %217 = load i64, i64* %hbuflen214, align 8, !dbg !3021
  %218 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3022
  %bytecount215 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %218, i32 0, i32 4, !dbg !3023
  %219 = load i64, i64* %bytecount215, align 8, !dbg !3024
  %add = add i64 %219, %217, !dbg !3024
  store i64 %add, i64* %bytecount215, align 8, !dbg !3024
  br label %if.end216, !dbg !3025

if.end216:                                        ; preds = %do.end213, %land.lhs.true208, %if.end205
  %220 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3026
  %maxdownload217 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %220, i32 0, i32 2, !dbg !3028
  %221 = load i64, i64* %maxdownload217, align 8, !dbg !3028
  %cmp218 = icmp ne i64 -1, %221, !dbg !3029
  br i1 %cmp218, label %land.lhs.true219, label %if.end257, !dbg !3030

land.lhs.true219:                                 ; preds = %if.end216
  %222 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3031
  %bytecount220 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %222, i32 0, i32 4, !dbg !3032
  %223 = load i64, i64* %bytecount220, align 8, !dbg !3032
  %224 = load i64, i64* %nread, align 8, !dbg !3033
  %add221 = add nsw i64 %223, %224, !dbg !3034
  %225 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3035
  %maxdownload222 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %225, i32 0, i32 2, !dbg !3036
  %226 = load i64, i64* %maxdownload222, align 8, !dbg !3036
  %cmp223 = icmp sge i64 %add221, %226, !dbg !3037
  br i1 %cmp223, label %if.then224, label %if.end257, !dbg !3038

if.then224:                                       ; preds = %land.lhs.true219
  %227 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3040
  %bytecount225 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %227, i32 0, i32 4, !dbg !3042
  %228 = load i64, i64* %bytecount225, align 8, !dbg !3042
  %229 = load i64, i64* %nread, align 8, !dbg !3043
  %add226 = add nsw i64 %228, %229, !dbg !3044
  %230 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3045
  %maxdownload227 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %230, i32 0, i32 2, !dbg !3046
  %231 = load i64, i64* %maxdownload227, align 8, !dbg !3046
  %sub228 = sub nsw i64 %add226, %231, !dbg !3047
  store i64 %sub228, i64* %excess, align 8, !dbg !3048
  %232 = load i64, i64* %excess, align 8, !dbg !3049
  %cmp229 = icmp ugt i64 %232, 0, !dbg !3051
  br i1 %cmp229, label %land.lhs.true230, label %if.end248, !dbg !3052

land.lhs.true230:                                 ; preds = %if.then224
  %233 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3053
  %ignorebody231 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %233, i32 0, i32 33, !dbg !3055
  %234 = load i8, i8* %ignorebody231, align 1, !dbg !3055
  %tobool232 = trunc i8 %234 to i1, !dbg !3055
  br i1 %tobool232, label %if.end248, label %if.then233, !dbg !3056

if.then233:                                       ; preds = %land.lhs.true230
  %235 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3057
  %data234 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %235, i32 0, i32 0, !dbg !3060
  %236 = load %struct.Curl_easy*, %struct.Curl_easy** %data234, align 8, !dbg !3060
  %multi235 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %236, i32 0, i32 9, !dbg !3061
  %237 = load %struct.Curl_multi*, %struct.Curl_multi** %multi235, align 8, !dbg !3061
  %call236 = call zeroext i1 @Curl_pipeline_wanted(%struct.Curl_multi* %237, i32 1), !dbg !3062
  br i1 %call236, label %if.then237, label %if.else243, !dbg !3063

if.then237:                                       ; preds = %if.then233
  %238 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3064
  %239 = load i64, i64* %excess, align 8, !dbg !3066
  %240 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3067
  %state238 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %240, i32 0, i32 17, !dbg !3068
  %path239 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state238, i32 0, i32 38, !dbg !3069
  %241 = load i8*, i8** %path239, align 8, !dbg !3069
  %242 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3070
  %size240 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %242, i32 0, i32 0, !dbg !3071
  %243 = load i64, i64* %size240, align 8, !dbg !3071
  %244 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3072
  %maxdownload241 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %244, i32 0, i32 2, !dbg !3073
  %245 = load i64, i64* %maxdownload241, align 8, !dbg !3073
  %246 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3074
  %bytecount242 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %246, i32 0, i32 4, !dbg !3075
  %247 = load i64, i64* %bytecount242, align 8, !dbg !3075
  %248 = load i64, i64* %nread, align 8, !dbg !3076
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %238, i8* getelementptr inbounds ([105 x i8], [105 x i8]* @.str.36, i32 0, i32 0), i64 %239, i8* %241, i64 %243, i64 %245, i64 %247, i64 %248), !dbg !3077
  %249 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3078
  %250 = load i64, i64* %excess, align 8, !dbg !3079
  call void @read_rewind(%struct.connectdata* %249, i64 %250), !dbg !3080
  br label %if.end247, !dbg !3081

if.else243:                                       ; preds = %if.then233
  %251 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3082
  %252 = load i64, i64* %excess, align 8, !dbg !3084
  %253 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3085
  %size244 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %253, i32 0, i32 0, !dbg !3086
  %254 = load i64, i64* %size244, align 8, !dbg !3086
  %255 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3087
  %maxdownload245 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %255, i32 0, i32 2, !dbg !3088
  %256 = load i64, i64* %maxdownload245, align 8, !dbg !3088
  %257 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3089
  %bytecount246 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %257, i32 0, i32 4, !dbg !3090
  %258 = load i64, i64* %bytecount246, align 8, !dbg !3090
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %251, i8* getelementptr inbounds ([100 x i8], [100 x i8]* @.str.37, i32 0, i32 0), i64 %252, i64 %254, i64 %256, i64 %258), !dbg !3091
  br label %if.end247

if.end247:                                        ; preds = %if.else243, %if.then237
  br label %if.end248, !dbg !3092

if.end248:                                        ; preds = %if.end247, %land.lhs.true230, %if.then224
  %259 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3093
  %maxdownload249 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %259, i32 0, i32 2, !dbg !3094
  %260 = load i64, i64* %maxdownload249, align 8, !dbg !3094
  %261 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3095
  %bytecount250 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %261, i32 0, i32 4, !dbg !3096
  %262 = load i64, i64* %bytecount250, align 8, !dbg !3096
  %sub251 = sub nsw i64 %260, %262, !dbg !3097
  store i64 %sub251, i64* %nread, align 8, !dbg !3098
  %263 = load i64, i64* %nread, align 8, !dbg !3099
  %cmp252 = icmp slt i64 %263, 0, !dbg !3101
  br i1 %cmp252, label %if.then253, label %if.end254, !dbg !3102

if.then253:                                       ; preds = %if.end248
  store i64 0, i64* %nread, align 8, !dbg !3103
  br label %if.end254, !dbg !3104

if.end254:                                        ; preds = %if.then253, %if.end248
  %264 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3105
  %keepon255 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %264, i32 0, i32 31, !dbg !3106
  %265 = load i32, i32* %keepon255, align 4, !dbg !3107
  %and256 = and i32 %265, -2, !dbg !3107
  store i32 %and256, i32* %keepon255, align 4, !dbg !3107
  br label %if.end257, !dbg !3108

if.end257:                                        ; preds = %if.end254, %land.lhs.true219, %if.end216
  %266 = load i64, i64* %nread, align 8, !dbg !3109
  %267 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3110
  %bytecount258 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %267, i32 0, i32 4, !dbg !3111
  %268 = load i64, i64* %bytecount258, align 8, !dbg !3112
  %add259 = add nsw i64 %268, %266, !dbg !3112
  store i64 %add259, i64* %bytecount258, align 8, !dbg !3112
  %269 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3113
  %270 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3114
  %bytecount260 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %270, i32 0, i32 4, !dbg !3115
  %271 = load i64, i64* %bytecount260, align 8, !dbg !3115
  call void @Curl_pgrsSetDownloadCounter(%struct.Curl_easy* %269, i64 %271), !dbg !3116
  %272 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3117
  %chunk261 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %272, i32 0, i32 39, !dbg !3119
  %273 = load i8, i8* %chunk261, align 8, !dbg !3119
  %tobool262 = trunc i8 %273 to i1, !dbg !3119
  br i1 %tobool262, label %if.end312, label %land.lhs.true263, !dbg !3120

land.lhs.true263:                                 ; preds = %if.end257
  %274 = load i64, i64* %nread, align 8, !dbg !3121
  %tobool264 = icmp ne i64 %274, 0, !dbg !3121
  br i1 %tobool264, label %if.then270, label %lor.lhs.false265, !dbg !3123

lor.lhs.false265:                                 ; preds = %land.lhs.true263
  %275 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3124
  %badheader266 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %275, i32 0, i32 11, !dbg !3126
  %276 = load i32, i32* %badheader266, align 4, !dbg !3126
  %tobool267 = icmp ne i32 %276, 0, !dbg !3124
  br i1 %tobool267, label %if.then270, label %lor.lhs.false268, !dbg !3127

lor.lhs.false268:                                 ; preds = %lor.lhs.false265
  %277 = load i8, i8* %is_empty_data, align 1, !dbg !3128
  %tobool269 = trunc i8 %277 to i1, !dbg !3128
  br i1 %tobool269, label %if.then270, label %if.end312, !dbg !3130

if.then270:                                       ; preds = %lor.lhs.false268, %lor.lhs.false265, %land.lhs.true263
  %278 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3131
  %badheader271 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %278, i32 0, i32 11, !dbg !3134
  %279 = load i32, i32* %badheader271, align 4, !dbg !3134
  %tobool272 = icmp ne i32 %279, 0, !dbg !3131
  br i1 %tobool272, label %land.lhs.true273, label %if.end297, !dbg !3135

land.lhs.true273:                                 ; preds = %if.then270
  %280 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3136
  %ignorebody274 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %280, i32 0, i32 33, !dbg !3138
  %281 = load i8, i8* %ignorebody274, align 1, !dbg !3138
  %tobool275 = trunc i8 %281 to i1, !dbg !3138
  br i1 %tobool275, label %if.end297, label %if.then276, !dbg !3139

if.then276:                                       ; preds = %land.lhs.true273
  %282 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3140
  %maxdownload277 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %282, i32 0, i32 2, !dbg !3143
  %283 = load i64, i64* %maxdownload277, align 8, !dbg !3143
  %cmp278 = icmp eq i64 %283, -1, !dbg !3144
  br i1 %cmp278, label %if.then283, label %lor.lhs.false279, !dbg !3145

lor.lhs.false279:                                 ; preds = %if.then276
  %284 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3146
  %hbuflen280 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %284, i32 0, i32 14, !dbg !3148
  %285 = load i64, i64* %hbuflen280, align 8, !dbg !3148
  %286 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3149
  %maxdownload281 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %286, i32 0, i32 2, !dbg !3150
  %287 = load i64, i64* %maxdownload281, align 8, !dbg !3150
  %cmp282 = icmp sle i64 %285, %287, !dbg !3151
  br i1 %cmp282, label %if.then283, label %if.else288, !dbg !3152

if.then283:                                       ; preds = %lor.lhs.false279, %if.then276
  %288 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3153
  %289 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3154
  %state284 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %289, i32 0, i32 17, !dbg !3155
  %headerbuff285 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state284, i32 0, i32 4, !dbg !3156
  %290 = load i8*, i8** %headerbuff285, align 8, !dbg !3156
  %291 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3157
  %hbuflen286 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %291, i32 0, i32 14, !dbg !3158
  %292 = load i64, i64* %hbuflen286, align 8, !dbg !3158
  %call287 = call i32 @Curl_client_write(%struct.connectdata* %288, i32 1, i8* %290, i64 %292), !dbg !3159
  store i32 %call287, i32* %result, align 4, !dbg !3160
  br label %if.end293, !dbg !3161

if.else288:                                       ; preds = %lor.lhs.false279
  %293 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3162
  %294 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3163
  %state289 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %294, i32 0, i32 17, !dbg !3164
  %headerbuff290 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state289, i32 0, i32 4, !dbg !3165
  %295 = load i8*, i8** %headerbuff290, align 8, !dbg !3165
  %296 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3166
  %maxdownload291 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %296, i32 0, i32 2, !dbg !3167
  %297 = load i64, i64* %maxdownload291, align 8, !dbg !3167
  %call292 = call i32 @Curl_client_write(%struct.connectdata* %293, i32 1, i8* %295, i64 %297), !dbg !3168
  store i32 %call292, i32* %result, align 4, !dbg !3169
  br label %if.end293

if.end293:                                        ; preds = %if.else288, %if.then283
  %298 = load i32, i32* %result, align 4, !dbg !3170
  %tobool294 = icmp ne i32 %298, 0, !dbg !3170
  br i1 %tobool294, label %if.then295, label %if.end296, !dbg !3172

if.then295:                                       ; preds = %if.end293
  %299 = load i32, i32* %result, align 4, !dbg !3173
  store i32 %299, i32* %retval, align 4, !dbg !3174
  br label %return, !dbg !3174

if.end296:                                        ; preds = %if.end293
  br label %if.end297, !dbg !3175

if.end297:                                        ; preds = %if.end296, %land.lhs.true273, %if.then270
  %300 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3176
  %badheader298 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %300, i32 0, i32 11, !dbg !3178
  %301 = load i32, i32* %badheader298, align 4, !dbg !3178
  %cmp299 = icmp ult i32 %301, 2, !dbg !3179
  br i1 %cmp299, label %if.then300, label %if.end307, !dbg !3180

if.then300:                                       ; preds = %if.end297
  %302 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3181
  %ignorebody301 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %302, i32 0, i32 33, !dbg !3184
  %303 = load i8, i8* %ignorebody301, align 1, !dbg !3184
  %tobool302 = trunc i8 %303 to i1, !dbg !3184
  br i1 %tobool302, label %if.end306, label %if.then303, !dbg !3185

if.then303:                                       ; preds = %if.then300
  %304 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3186
  %305 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3188
  %str304 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %305, i32 0, i32 15, !dbg !3189
  %306 = load i8*, i8** %str304, align 8, !dbg !3189
  %307 = load i64, i64* %nread, align 8, !dbg !3190
  %call305 = call i32 @Curl_client_write(%struct.connectdata* %304, i32 1, i8* %306, i64 %307), !dbg !3191
  store i32 %call305, i32* %result, align 4, !dbg !3192
  br label %if.end306, !dbg !3193

if.end306:                                        ; preds = %if.then303, %if.then300
  br label %if.end307, !dbg !3194

if.end307:                                        ; preds = %if.end306, %if.end297
  %308 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3195
  %badheader308 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %308, i32 0, i32 11, !dbg !3196
  store i32 0, i32* %badheader308, align 4, !dbg !3197
  %309 = load i32, i32* %result, align 4, !dbg !3198
  %tobool309 = icmp ne i32 %309, 0, !dbg !3198
  br i1 %tobool309, label %if.then310, label %if.end311, !dbg !3200

if.then310:                                       ; preds = %if.end307
  %310 = load i32, i32* %result, align 4, !dbg !3201
  store i32 %310, i32* %retval, align 4, !dbg !3202
  br label %return, !dbg !3202

if.end311:                                        ; preds = %if.end307
  br label %if.end312, !dbg !3203

if.end312:                                        ; preds = %if.end311, %lor.lhs.false268, %if.end257
  br label %if.end313, !dbg !3204

if.end313:                                        ; preds = %if.end312, %lor.lhs.false102, %land.lhs.true97, %if.end94
  %311 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3205
  %handler314 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %311, i32 0, i32 47, !dbg !3207
  %312 = load %struct.Curl_handler*, %struct.Curl_handler** %handler314, align 8, !dbg !3207
  %readwrite315 = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %312, i32 0, i32 13, !dbg !3208
  %313 = load i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)** %readwrite315, align 8, !dbg !3208
  %tobool316 = icmp ne i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)* %313, null, !dbg !3205
  br i1 %tobool316, label %land.lhs.true317, label %if.end335, !dbg !3209

land.lhs.true317:                                 ; preds = %if.end313
  %314 = load i64, i64* %excess, align 8, !dbg !3210
  %cmp318 = icmp ugt i64 %314, 0, !dbg !3211
  br i1 %cmp318, label %land.lhs.true319, label %if.end335, !dbg !3212

land.lhs.true319:                                 ; preds = %land.lhs.true317
  %315 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3213
  %bits320 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %315, i32 0, i32 43, !dbg !3215
  %stream_was_rewound = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits320, i32 0, i32 23, !dbg !3216
  %316 = load i8, i8* %stream_was_rewound, align 1, !dbg !3216
  %tobool321 = trunc i8 %316 to i1, !dbg !3216
  br i1 %tobool321, label %if.end335, label %if.then322, !dbg !3217

if.then322:                                       ; preds = %land.lhs.true319
  %317 = load i64, i64* %nread, align 8, !dbg !3218
  %318 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3220
  %str323 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %318, i32 0, i32 15, !dbg !3221
  %319 = load i8*, i8** %str323, align 8, !dbg !3222
  %add.ptr = getelementptr inbounds i8, i8* %319, i64 %317, !dbg !3222
  store i8* %add.ptr, i8** %str323, align 8, !dbg !3222
  %320 = load i64, i64* %excess, align 8, !dbg !3223
  store i64 %320, i64* %nread, align 8, !dbg !3224
  %321 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3225
  %handler324 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %321, i32 0, i32 47, !dbg !3226
  %322 = load %struct.Curl_handler*, %struct.Curl_handler** %handler324, align 8, !dbg !3226
  %readwrite325 = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %322, i32 0, i32 13, !dbg !3227
  %323 = load i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)** %readwrite325, align 8, !dbg !3227
  %324 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3228
  %325 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3229
  %call326 = call i32 %323(%struct.Curl_easy* %324, %struct.connectdata* %325, i64* %nread, i8* %readmore), !dbg !3225
  store i32 %call326, i32* %result, align 4, !dbg !3230
  %326 = load i32, i32* %result, align 4, !dbg !3231
  %tobool327 = icmp ne i32 %326, 0, !dbg !3231
  br i1 %tobool327, label %if.then328, label %if.end329, !dbg !3233

if.then328:                                       ; preds = %if.then322
  %327 = load i32, i32* %result, align 4, !dbg !3234
  store i32 %327, i32* %retval, align 4, !dbg !3235
  br label %return, !dbg !3235

if.end329:                                        ; preds = %if.then322
  %328 = load i8, i8* %readmore, align 1, !dbg !3236
  %tobool330 = trunc i8 %328 to i1, !dbg !3236
  br i1 %tobool330, label %if.then331, label %if.end334, !dbg !3238

if.then331:                                       ; preds = %if.end329
  %329 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3239
  %keepon332 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %329, i32 0, i32 31, !dbg !3240
  %330 = load i32, i32* %keepon332, align 4, !dbg !3241
  %or333 = or i32 %330, 1, !dbg !3241
  store i32 %or333, i32* %keepon332, align 4, !dbg !3241
  br label %if.end334, !dbg !3239

if.end334:                                        ; preds = %if.then331, %if.end329
  br label %do.end346, !dbg !3242

if.end335:                                        ; preds = %land.lhs.true319, %land.lhs.true317, %if.end313
  %331 = load i8, i8* %is_empty_data, align 1, !dbg !3243
  %tobool336 = trunc i8 %331 to i1, !dbg !3243
  br i1 %tobool336, label %if.then337, label %if.end340, !dbg !3245

if.then337:                                       ; preds = %if.end335
  %332 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3246
  %keepon338 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %332, i32 0, i32 31, !dbg !3248
  %333 = load i32, i32* %keepon338, align 4, !dbg !3249
  %and339 = and i32 %333, -2, !dbg !3249
  store i32 %and339, i32* %keepon338, align 4, !dbg !3249
  br label %if.end340, !dbg !3250

if.end340:                                        ; preds = %if.then337, %if.end335
  br label %do.cond, !dbg !3251

do.cond:                                          ; preds = %if.end340
  %334 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3252
  %call341 = call i32 @data_pending(%struct.connectdata* %334), !dbg !3254
  %tobool342 = icmp ne i32 %call341, 0, !dbg !3254
  br i1 %tobool342, label %land.rhs343, label %land.end345, !dbg !3255

land.rhs343:                                      ; preds = %do.cond
  %335 = load i32, i32* %maxloops, align 4, !dbg !3256
  %dec = add nsw i32 %335, -1, !dbg !3256
  store i32 %dec, i32* %maxloops, align 4, !dbg !3256
  %tobool344 = icmp ne i32 %335, 0, !dbg !3258
  br label %land.end345

land.end345:                                      ; preds = %land.rhs343, %do.cond
  %336 = phi i1 [ false, %do.cond ], [ %tobool344, %land.rhs343 ]
  br i1 %336, label %do.body, label %do.end346, !dbg !3259

do.end346:                                        ; preds = %land.end345, %if.end334, %if.end92, %if.then78, %if.then53, %do.end40, %if.then11
  %337 = load i32, i32* %maxloops, align 4, !dbg !3260
  %cmp347 = icmp sle i32 %337, 0, !dbg !3262
  br i1 %cmp347, label %if.then348, label %if.end349, !dbg !3263

if.then348:                                       ; preds = %do.end346
  %338 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3264
  %cselect_bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %338, i32 0, i32 67, !dbg !3266
  store i32 1, i32* %cselect_bits, align 8, !dbg !3267
  %339 = load i8*, i8** %comeback.addr, align 8, !dbg !3268
  store i8 1, i8* %339, align 1, !dbg !3269
  br label %if.end349, !dbg !3270

if.end349:                                        ; preds = %if.then348, %do.end346
  %340 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3271
  %keepon350 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %340, i32 0, i32 31, !dbg !3273
  %341 = load i32, i32* %keepon350, align 4, !dbg !3273
  %and351 = and i32 %341, 3, !dbg !3274
  %cmp352 = icmp eq i32 %and351, 2, !dbg !3275
  br i1 %cmp352, label %land.lhs.true353, label %if.end360, !dbg !3276

land.lhs.true353:                                 ; preds = %if.end349
  %342 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3277
  %bits354 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %342, i32 0, i32 43, !dbg !3278
  %close355 = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits354, i32 0, i32 0, !dbg !3279
  %343 = load i8, i8* %close355, align 1, !dbg !3279
  %tobool356 = trunc i8 %343 to i1, !dbg !3279
  br i1 %tobool356, label %if.then357, label %if.end360, !dbg !3280

if.then357:                                       ; preds = %land.lhs.true353
  %344 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3281
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %344, i8* getelementptr inbounds ([57 x i8], [57 x i8]* @.str.38, i32 0, i32 0)), !dbg !3283
  %345 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3284
  %keepon358 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %345, i32 0, i32 31, !dbg !3285
  %346 = load i32, i32* %keepon358, align 4, !dbg !3286
  %and359 = and i32 %346, -3, !dbg !3286
  store i32 %and359, i32* %keepon358, align 4, !dbg !3286
  br label %if.end360, !dbg !3287

if.end360:                                        ; preds = %if.then357, %land.lhs.true353, %if.end349
  store i32 0, i32* %retval, align 4, !dbg !3288
  br label %return, !dbg !3288

return:                                           ; preds = %if.end360, %if.then328, %if.then310, %if.then295, %if.end185, %if.then184, %if.then153, %if.end144, %if.then141, %if.then121, %if.then107, %if.then75, %if.then61, %if.then50, %if.then14
  %347 = load i32, i32* %retval, align 4, !dbg !3289
  ret i32 %347, !dbg !3289
}

; Function Attrs: nounwind uwtable
define internal i32 @readwrite_upload(%struct.Curl_easy* %data, %struct.connectdata* %conn, %struct.SingleRequest* %k, i32* %didwhat) #0 !dbg !1805 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %conn.addr = alloca %struct.connectdata*, align 8
  %k.addr = alloca %struct.SingleRequest*, align 8
  %didwhat.addr = alloca i32*, align 8
  %i = alloca i64, align 8
  %si = alloca i64, align 8
  %bytes_written = alloca i64, align 8
  %result = alloca i32, align 4
  %nread = alloca i64, align 8
  %sending_http_headers = alloca i8, align 1
  %fillcount = alloca i32, align 4
  %http = alloca %struct.HTTP*, align 8
  %coerce = alloca %struct.timeval, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !3290, metadata !1827), !dbg !3291
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !3292, metadata !1827), !dbg !3293
  store %struct.SingleRequest* %k, %struct.SingleRequest** %k.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.SingleRequest** %k.addr, metadata !3294, metadata !1827), !dbg !3295
  store i32* %didwhat, i32** %didwhat.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %didwhat.addr, metadata !3296, metadata !1827), !dbg !3297
  call void @llvm.dbg.declare(metadata i64* %i, metadata !3298, metadata !1827), !dbg !3299
  call void @llvm.dbg.declare(metadata i64* %si, metadata !3300, metadata !1827), !dbg !3301
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !3302, metadata !1827), !dbg !3303
  call void @llvm.dbg.declare(metadata i32* %result, metadata !3304, metadata !1827), !dbg !3305
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !3306, metadata !1827), !dbg !3307
  call void @llvm.dbg.declare(metadata i8* %sending_http_headers, metadata !3308, metadata !1827), !dbg !3309
  store i8 0, i8* %sending_http_headers, align 1, !dbg !3309
  %0 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3310
  %bytecount = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %0, i32 0, i32 4, !dbg !3312
  %1 = load i64, i64* %bytecount, align 8, !dbg !3312
  %cmp = icmp eq i64 %1, 0, !dbg !3313
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !3314

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3315
  %writebytecount = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %2, i32 0, i32 5, !dbg !3317
  %3 = load i64, i64* %writebytecount, align 8, !dbg !3317
  %cmp1 = icmp eq i64 %3, 0, !dbg !3318
  br i1 %cmp1, label %if.then, label %if.end, !dbg !3319

if.then:                                          ; preds = %land.lhs.true
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3320
  call void @Curl_pgrsTime(%struct.Curl_easy* %4, i32 7), !dbg !3321
  br label %if.end, !dbg !3321

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  %5 = load i32*, i32** %didwhat.addr, align 8, !dbg !3322
  %6 = load i32, i32* %5, align 4, !dbg !3323
  %or = or i32 %6, 2, !dbg !3323
  store i32 %or, i32* %5, align 4, !dbg !3323
  br label %do.body, !dbg !3324

do.body:                                          ; preds = %if.end
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3325
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 12, !dbg !3328
  %upload_present = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 37, !dbg !3329
  %8 = load i64, i64* %upload_present, align 8, !dbg !3329
  %cmp2 = icmp eq i64 0, %8, !dbg !3330
  br i1 %cmp2, label %if.then3, label %if.else113, !dbg !3331

if.then3:                                         ; preds = %do.body
  %9 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3332
  %uploadbuf = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %9, i32 0, i32 29, !dbg !3334
  %10 = load i8*, i8** %uploadbuf, align 8, !dbg !3334
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3335
  %req4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 12, !dbg !3336
  %upload_fromhere = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req4, i32 0, i32 38, !dbg !3337
  store i8* %10, i8** %upload_fromhere, align 8, !dbg !3338
  %12 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3339
  %upload_done = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %12, i32 0, i32 32, !dbg !3341
  %13 = load i8, i8* %upload_done, align 8, !dbg !3341
  %tobool = trunc i8 %13 to i1, !dbg !3341
  br i1 %tobool, label %if.else26, label %if.then5, !dbg !3342

if.then5:                                         ; preds = %if.then3
  call void @llvm.dbg.declare(metadata i32* %fillcount, metadata !3343, metadata !1827), !dbg !3345
  call void @llvm.dbg.declare(metadata %struct.HTTP** %http, metadata !3346, metadata !1827), !dbg !3348
  %14 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3349
  %req6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %14, i32 0, i32 12, !dbg !3350
  %protop = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req6, i32 0, i32 43, !dbg !3351
  %15 = load i8*, i8** %protop, align 8, !dbg !3351
  %16 = bitcast i8* %15 to %struct.HTTP*, !dbg !3349
  store %struct.HTTP* %16, %struct.HTTP** %http, align 8, !dbg !3348
  %17 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3352
  %exp100 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %17, i32 0, i32 23, !dbg !3354
  %18 = load i32, i32* %exp100, align 8, !dbg !3354
  %cmp7 = icmp eq i32 %18, 2, !dbg !3355
  br i1 %cmp7, label %land.lhs.true8, label %if.end13, !dbg !3356

land.lhs.true8:                                   ; preds = %if.then5
  %19 = load %struct.HTTP*, %struct.HTTP** %http, align 8, !dbg !3357
  %sending = getelementptr inbounds %struct.HTTP, %struct.HTTP* %19, i32 0, i32 9, !dbg !3358
  %20 = load i32, i32* %sending, align 8, !dbg !3358
  %cmp9 = icmp eq i32 %20, 2, !dbg !3359
  br i1 %cmp9, label %if.then10, label %if.end13, !dbg !3360

if.then10:                                        ; preds = %land.lhs.true8
  %21 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3362
  %exp10011 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %21, i32 0, i32 23, !dbg !3364
  store i32 1, i32* %exp10011, align 8, !dbg !3365
  %22 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3366
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %22, i32 0, i32 31, !dbg !3367
  %23 = load i32, i32* %keepon, align 4, !dbg !3368
  %and = and i32 %23, -3, !dbg !3368
  store i32 %and, i32* %keepon, align 4, !dbg !3368
  %24 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3369
  %start100 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %24, i32 0, i32 22, !dbg !3370
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !3371
  %25 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !3371
  %26 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %25, i32 0, i32 0, !dbg !3371
  %27 = extractvalue { i64, i64 } %call, 0, !dbg !3371
  store i64 %27, i64* %26, align 8, !dbg !3371
  %28 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %25, i32 0, i32 1, !dbg !3371
  %29 = extractvalue { i64, i64 } %call, 1, !dbg !3371
  store i64 %29, i64* %28, align 8, !dbg !3371
  %30 = bitcast %struct.timeval* %start100 to i8*, !dbg !3371
  %31 = bitcast %struct.timeval* %coerce to i8*, !dbg !3371
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %30, i8* %31, i64 16, i32 8, i1 false), !dbg !3372
  %32 = load i32*, i32** %didwhat.addr, align 8, !dbg !3374
  %33 = load i32, i32* %32, align 4, !dbg !3375
  %and12 = and i32 %33, -3, !dbg !3375
  store i32 %and12, i32* %32, align 4, !dbg !3375
  %34 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3376
  %35 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3377
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %35, i32 0, i32 13, !dbg !3378
  %expect_100_timeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 151, !dbg !3379
  %36 = load i64, i64* %expect_100_timeout, align 8, !dbg !3379
  call void @Curl_expire(%struct.Curl_easy* %34, i64 %36), !dbg !3380
  br label %do.end, !dbg !3381

if.end13:                                         ; preds = %land.lhs.true8, %if.then5
  %37 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3382
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %37, i32 0, i32 47, !dbg !3384
  %38 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !3384
  %protocol = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %38, i32 0, i32 15, !dbg !3385
  %39 = load i32, i32* %protocol, align 8, !dbg !3385
  %and14 = and i32 %39, 262147, !dbg !3386
  %tobool15 = icmp ne i32 %and14, 0, !dbg !3386
  br i1 %tobool15, label %if.then16, label %if.end21, !dbg !3387

if.then16:                                        ; preds = %if.end13
  %40 = load %struct.HTTP*, %struct.HTTP** %http, align 8, !dbg !3388
  %sending17 = getelementptr inbounds %struct.HTTP, %struct.HTTP* %40, i32 0, i32 9, !dbg !3391
  %41 = load i32, i32* %sending17, align 8, !dbg !3391
  %cmp18 = icmp eq i32 %41, 1, !dbg !3392
  br i1 %cmp18, label %if.then19, label %if.else, !dbg !3393

if.then19:                                        ; preds = %if.then16
  store i8 1, i8* %sending_http_headers, align 1, !dbg !3394
  br label %if.end20, !dbg !3395

if.else:                                          ; preds = %if.then16
  store i8 0, i8* %sending_http_headers, align 1, !dbg !3396
  br label %if.end20

if.end20:                                         ; preds = %if.else, %if.then19
  br label %if.end21, !dbg !3397

if.end21:                                         ; preds = %if.end20, %if.end13
  %42 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3398
  %call22 = call i32 @Curl_fillreadbuffer(%struct.connectdata* %42, i32 16384, i32* %fillcount), !dbg !3399
  store i32 %call22, i32* %result, align 4, !dbg !3400
  %43 = load i32, i32* %result, align 4, !dbg !3401
  %tobool23 = icmp ne i32 %43, 0, !dbg !3401
  br i1 %tobool23, label %if.then24, label %if.end25, !dbg !3403

if.then24:                                        ; preds = %if.end21
  %44 = load i32, i32* %result, align 4, !dbg !3404
  store i32 %44, i32* %retval, align 4, !dbg !3405
  br label %return, !dbg !3405

if.end25:                                         ; preds = %if.end21
  %45 = load i32, i32* %fillcount, align 4, !dbg !3406
  %conv = sext i32 %45 to i64, !dbg !3407
  store i64 %conv, i64* %nread, align 8, !dbg !3408
  br label %if.end27, !dbg !3409

if.else26:                                        ; preds = %if.then3
  store i64 0, i64* %nread, align 8, !dbg !3410
  br label %if.end27

if.end27:                                         ; preds = %if.else26, %if.end25
  %46 = load i64, i64* %nread, align 8, !dbg !3411
  %tobool28 = icmp ne i64 %46, 0, !dbg !3411
  br i1 %tobool28, label %if.end34, label %land.lhs.true29, !dbg !3413

land.lhs.true29:                                  ; preds = %if.end27
  %47 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3414
  %keepon30 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %47, i32 0, i32 31, !dbg !3416
  %48 = load i32, i32* %keepon30, align 4, !dbg !3416
  %and31 = and i32 %48, 32, !dbg !3417
  %tobool32 = icmp ne i32 %and31, 0, !dbg !3417
  br i1 %tobool32, label %if.then33, label %if.end34, !dbg !3418

if.then33:                                        ; preds = %land.lhs.true29
  br label %do.end, !dbg !3419

if.end34:                                         ; preds = %land.lhs.true29, %if.end27
  %49 = load i64, i64* %nread, align 8, !dbg !3421
  %cmp35 = icmp sle i64 %49, 0, !dbg !3423
  br i1 %cmp35, label %if.then37, label %if.end42, !dbg !3424

if.then37:                                        ; preds = %if.end34
  %50 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3425
  %51 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3427
  %call38 = call i32 @done_sending(%struct.connectdata* %50, %struct.SingleRequest* %51), !dbg !3428
  store i32 %call38, i32* %result, align 4, !dbg !3429
  %52 = load i32, i32* %result, align 4, !dbg !3430
  %tobool39 = icmp ne i32 %52, 0, !dbg !3430
  br i1 %tobool39, label %if.then40, label %if.end41, !dbg !3432

if.then40:                                        ; preds = %if.then37
  %53 = load i32, i32* %result, align 4, !dbg !3433
  store i32 %53, i32* %retval, align 4, !dbg !3434
  br label %return, !dbg !3434

if.end41:                                         ; preds = %if.then37
  br label %do.end, !dbg !3435

if.end42:                                         ; preds = %if.end34
  %54 = load i64, i64* %nread, align 8, !dbg !3436
  %55 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3437
  %req43 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %55, i32 0, i32 12, !dbg !3438
  %upload_present44 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req43, i32 0, i32 37, !dbg !3439
  store i64 %54, i64* %upload_present44, align 8, !dbg !3440
  %56 = load i8, i8* %sending_http_headers, align 1, !dbg !3441
  %tobool45 = trunc i8 %56 to i1, !dbg !3441
  br i1 %tobool45, label %if.end112, label %land.lhs.true46, !dbg !3443

land.lhs.true46:                                  ; preds = %if.end42
  %57 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3444
  %set47 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %57, i32 0, i32 13, !dbg !3445
  %prefer_ascii = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set47, i32 0, i32 90, !dbg !3446
  %58 = load i8, i8* %prefer_ascii, align 1, !dbg !3446
  %tobool48 = trunc i8 %58 to i1, !dbg !3446
  br i1 %tobool48, label %if.then53, label %lor.lhs.false, !dbg !3447

lor.lhs.false:                                    ; preds = %land.lhs.true46
  %59 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3448
  %set50 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %59, i32 0, i32 13, !dbg !3449
  %crlf = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set50, i32 0, i32 59, !dbg !3450
  %60 = load i8, i8* %crlf, align 2, !dbg !3450
  %tobool51 = trunc i8 %60 to i1, !dbg !3450
  br i1 %tobool51, label %if.then53, label %if.end112, !dbg !3451

if.then53:                                        ; preds = %lor.lhs.false, %land.lhs.true46
  %61 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3453
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %61, i32 0, i32 17, !dbg !3456
  %scratch = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 16, !dbg !3457
  %62 = load i8*, i8** %scratch, align 8, !dbg !3457
  %tobool54 = icmp ne i8* %62, null, !dbg !3453
  br i1 %tobool54, label %if.end64, label %if.then55, !dbg !3458

if.then55:                                        ; preds = %if.then53
  %63 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !3459
  %call56 = call i8* %63(i64 32768), !dbg !3459
  %64 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3461
  %state57 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %64, i32 0, i32 17, !dbg !3462
  %scratch58 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state57, i32 0, i32 16, !dbg !3463
  store i8* %call56, i8** %scratch58, align 8, !dbg !3464
  %65 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3465
  %state59 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %65, i32 0, i32 17, !dbg !3467
  %scratch60 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state59, i32 0, i32 16, !dbg !3468
  %66 = load i8*, i8** %scratch60, align 8, !dbg !3468
  %tobool61 = icmp ne i8* %66, null, !dbg !3465
  br i1 %tobool61, label %if.end63, label %if.then62, !dbg !3469

if.then62:                                        ; preds = %if.then55
  %67 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3470
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %67, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.39, i32 0, i32 0)), !dbg !3472
  store i32 27, i32* %retval, align 4, !dbg !3473
  br label %return, !dbg !3473

if.end63:                                         ; preds = %if.then55
  br label %if.end64, !dbg !3474

if.end64:                                         ; preds = %if.end63, %if.then53
  store i64 0, i64* %i, align 8, !dbg !3475
  store i64 0, i64* %si, align 8, !dbg !3477
  br label %for.cond, !dbg !3478

for.cond:                                         ; preds = %for.inc, %if.end64
  %68 = load i64, i64* %i, align 8, !dbg !3479
  %69 = load i64, i64* %nread, align 8, !dbg !3482
  %cmp65 = icmp slt i64 %68, %69, !dbg !3483
  br i1 %cmp65, label %for.body, label %for.end, !dbg !3484

for.body:                                         ; preds = %for.cond
  %70 = load i64, i64* %i, align 8, !dbg !3485
  %71 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3488
  %req67 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %71, i32 0, i32 12, !dbg !3489
  %upload_fromhere68 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req67, i32 0, i32 38, !dbg !3490
  %72 = load i8*, i8** %upload_fromhere68, align 8, !dbg !3490
  %arrayidx = getelementptr inbounds i8, i8* %72, i64 %70, !dbg !3488
  %73 = load i8, i8* %arrayidx, align 1, !dbg !3488
  %conv69 = sext i8 %73 to i32, !dbg !3488
  %cmp70 = icmp eq i32 %conv69, 10, !dbg !3491
  br i1 %cmp70, label %if.then72, label %if.else92, !dbg !3492

if.then72:                                        ; preds = %for.body
  %74 = load i64, i64* %si, align 8, !dbg !3493
  %inc = add nsw i64 %74, 1, !dbg !3493
  store i64 %inc, i64* %si, align 8, !dbg !3493
  %75 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3495
  %state73 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %75, i32 0, i32 17, !dbg !3496
  %scratch74 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state73, i32 0, i32 16, !dbg !3497
  %76 = load i8*, i8** %scratch74, align 8, !dbg !3497
  %arrayidx75 = getelementptr inbounds i8, i8* %76, i64 %74, !dbg !3495
  store i8 13, i8* %arrayidx75, align 1, !dbg !3498
  %77 = load i64, i64* %si, align 8, !dbg !3499
  %78 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3500
  %state76 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %78, i32 0, i32 17, !dbg !3501
  %scratch77 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state76, i32 0, i32 16, !dbg !3502
  %79 = load i8*, i8** %scratch77, align 8, !dbg !3502
  %arrayidx78 = getelementptr inbounds i8, i8* %79, i64 %77, !dbg !3500
  store i8 10, i8* %arrayidx78, align 1, !dbg !3503
  %80 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3504
  %set79 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %80, i32 0, i32 13, !dbg !3506
  %crlf80 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set79, i32 0, i32 59, !dbg !3507
  %81 = load i8, i8* %crlf80, align 2, !dbg !3507
  %tobool81 = trunc i8 %81 to i1, !dbg !3507
  br i1 %tobool81, label %if.end91, label %if.then82, !dbg !3508

if.then82:                                        ; preds = %if.then72
  %82 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3509
  %state83 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %82, i32 0, i32 17, !dbg !3512
  %infilesize = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state83, i32 0, i32 47, !dbg !3513
  %83 = load i64, i64* %infilesize, align 8, !dbg !3513
  %cmp84 = icmp ne i64 %83, -1, !dbg !3514
  br i1 %cmp84, label %if.then86, label %if.end90, !dbg !3515

if.then86:                                        ; preds = %if.then82
  %84 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3516
  %state87 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %84, i32 0, i32 17, !dbg !3517
  %infilesize88 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state87, i32 0, i32 47, !dbg !3518
  %85 = load i64, i64* %infilesize88, align 8, !dbg !3519
  %inc89 = add nsw i64 %85, 1, !dbg !3519
  store i64 %inc89, i64* %infilesize88, align 8, !dbg !3519
  br label %if.end90, !dbg !3516

if.end90:                                         ; preds = %if.then86, %if.then82
  br label %if.end91, !dbg !3520

if.end91:                                         ; preds = %if.end90, %if.then72
  br label %if.end99, !dbg !3521

if.else92:                                        ; preds = %for.body
  %86 = load i64, i64* %i, align 8, !dbg !3522
  %87 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3523
  %req93 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %87, i32 0, i32 12, !dbg !3524
  %upload_fromhere94 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req93, i32 0, i32 38, !dbg !3525
  %88 = load i8*, i8** %upload_fromhere94, align 8, !dbg !3525
  %arrayidx95 = getelementptr inbounds i8, i8* %88, i64 %86, !dbg !3523
  %89 = load i8, i8* %arrayidx95, align 1, !dbg !3523
  %90 = load i64, i64* %si, align 8, !dbg !3526
  %91 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3527
  %state96 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %91, i32 0, i32 17, !dbg !3528
  %scratch97 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state96, i32 0, i32 16, !dbg !3529
  %92 = load i8*, i8** %scratch97, align 8, !dbg !3529
  %arrayidx98 = getelementptr inbounds i8, i8* %92, i64 %90, !dbg !3527
  store i8 %89, i8* %arrayidx98, align 1, !dbg !3530
  br label %if.end99

if.end99:                                         ; preds = %if.else92, %if.end91
  br label %for.inc, !dbg !3531

for.inc:                                          ; preds = %if.end99
  %93 = load i64, i64* %i, align 8, !dbg !3532
  %inc100 = add nsw i64 %93, 1, !dbg !3532
  store i64 %inc100, i64* %i, align 8, !dbg !3532
  %94 = load i64, i64* %si, align 8, !dbg !3534
  %inc101 = add nsw i64 %94, 1, !dbg !3534
  store i64 %inc101, i64* %si, align 8, !dbg !3534
  br label %for.cond, !dbg !3535

for.end:                                          ; preds = %for.cond
  %95 = load i64, i64* %si, align 8, !dbg !3536
  %96 = load i64, i64* %nread, align 8, !dbg !3538
  %cmp102 = icmp ne i64 %95, %96, !dbg !3539
  br i1 %cmp102, label %if.then104, label %if.end111, !dbg !3540

if.then104:                                       ; preds = %for.end
  %97 = load i64, i64* %si, align 8, !dbg !3541
  store i64 %97, i64* %nread, align 8, !dbg !3543
  %98 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3544
  %state105 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %98, i32 0, i32 17, !dbg !3545
  %scratch106 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state105, i32 0, i32 16, !dbg !3546
  %99 = load i8*, i8** %scratch106, align 8, !dbg !3546
  %100 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3547
  %req107 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %100, i32 0, i32 12, !dbg !3548
  %upload_fromhere108 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req107, i32 0, i32 38, !dbg !3549
  store i8* %99, i8** %upload_fromhere108, align 8, !dbg !3550
  %101 = load i64, i64* %nread, align 8, !dbg !3551
  %102 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3552
  %req109 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %102, i32 0, i32 12, !dbg !3553
  %upload_present110 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req109, i32 0, i32 37, !dbg !3554
  store i64 %101, i64* %upload_present110, align 8, !dbg !3555
  br label %if.end111, !dbg !3556

if.end111:                                        ; preds = %if.then104, %for.end
  br label %if.end112, !dbg !3557

if.end112:                                        ; preds = %if.end111, %lor.lhs.false, %if.end42
  br label %if.end114, !dbg !3558

if.else113:                                       ; preds = %do.body
  br label %if.end114

if.end114:                                        ; preds = %if.else113, %if.end112
  %103 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3559
  %104 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3560
  %writesockfd = getelementptr inbounds %struct.connectdata, %struct.connectdata* %104, i32 0, i32 51, !dbg !3561
  %105 = load i32, i32* %writesockfd, align 4, !dbg !3561
  %106 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3562
  %req115 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %106, i32 0, i32 12, !dbg !3563
  %upload_fromhere116 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req115, i32 0, i32 38, !dbg !3564
  %107 = load i8*, i8** %upload_fromhere116, align 8, !dbg !3564
  %108 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3565
  %req117 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %108, i32 0, i32 12, !dbg !3566
  %upload_present118 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req117, i32 0, i32 37, !dbg !3567
  %109 = load i64, i64* %upload_present118, align 8, !dbg !3567
  %call119 = call i32 @Curl_write(%struct.connectdata* %103, i32 %105, i8* %107, i64 %109, i64* %bytes_written), !dbg !3568
  store i32 %call119, i32* %result, align 4, !dbg !3569
  %110 = load i32, i32* %result, align 4, !dbg !3570
  %tobool120 = icmp ne i32 %110, 0, !dbg !3570
  br i1 %tobool120, label %if.then121, label %if.end122, !dbg !3572

if.then121:                                       ; preds = %if.end114
  %111 = load i32, i32* %result, align 4, !dbg !3573
  store i32 %111, i32* %retval, align 4, !dbg !3574
  br label %return, !dbg !3574

if.end122:                                        ; preds = %if.end114
  %112 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3575
  %set123 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %112, i32 0, i32 13, !dbg !3577
  %verbose = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set123, i32 0, i32 106, !dbg !3578
  %113 = load i8, i8* %verbose, align 8, !dbg !3578
  %tobool124 = trunc i8 %113 to i1, !dbg !3578
  br i1 %tobool124, label %if.then125, label %if.end129, !dbg !3579

if.then125:                                       ; preds = %if.end122
  %114 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3580
  %115 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3581
  %req126 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %115, i32 0, i32 12, !dbg !3582
  %upload_fromhere127 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req126, i32 0, i32 38, !dbg !3583
  %116 = load i8*, i8** %upload_fromhere127, align 8, !dbg !3583
  %117 = load i64, i64* %bytes_written, align 8, !dbg !3584
  %118 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3585
  %call128 = call i32 @Curl_debug(%struct.Curl_easy* %114, i32 4, i8* %116, i64 %117, %struct.connectdata* %118), !dbg !3586
  br label %if.end129, !dbg !3586

if.end129:                                        ; preds = %if.then125, %if.end122
  %119 = load i64, i64* %bytes_written, align 8, !dbg !3587
  %120 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3588
  %writebytecount130 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %120, i32 0, i32 5, !dbg !3589
  %121 = load i64, i64* %writebytecount130, align 8, !dbg !3590
  %add = add nsw i64 %121, %119, !dbg !3590
  store i64 %add, i64* %writebytecount130, align 8, !dbg !3590
  %122 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3591
  %writebytecount131 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %122, i32 0, i32 5, !dbg !3593
  %123 = load i64, i64* %writebytecount131, align 8, !dbg !3593
  %124 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3594
  %state132 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %124, i32 0, i32 17, !dbg !3595
  %infilesize133 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state132, i32 0, i32 47, !dbg !3596
  %125 = load i64, i64* %infilesize133, align 8, !dbg !3596
  %cmp134 = icmp eq i64 %123, %125, !dbg !3597
  br i1 %cmp134, label %if.then136, label %if.end138, !dbg !3598

if.then136:                                       ; preds = %if.end129
  %126 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3599
  %upload_done137 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %126, i32 0, i32 32, !dbg !3601
  store i8 1, i8* %upload_done137, align 8, !dbg !3602
  %127 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3603
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %127, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.40, i32 0, i32 0)), !dbg !3604
  br label %if.end138, !dbg !3605

if.end138:                                        ; preds = %if.then136, %if.end129
  %128 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3606
  %req139 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %128, i32 0, i32 12, !dbg !3608
  %upload_present140 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req139, i32 0, i32 37, !dbg !3609
  %129 = load i64, i64* %upload_present140, align 8, !dbg !3609
  %130 = load i64, i64* %bytes_written, align 8, !dbg !3610
  %cmp141 = icmp ne i64 %129, %130, !dbg !3611
  br i1 %cmp141, label %if.then143, label %if.else148, !dbg !3612

if.then143:                                       ; preds = %if.end138
  %131 = load i64, i64* %bytes_written, align 8, !dbg !3613
  %132 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3615
  %req144 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %132, i32 0, i32 12, !dbg !3616
  %upload_present145 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req144, i32 0, i32 37, !dbg !3617
  %133 = load i64, i64* %upload_present145, align 8, !dbg !3618
  %sub = sub nsw i64 %133, %131, !dbg !3618
  store i64 %sub, i64* %upload_present145, align 8, !dbg !3618
  %134 = load i64, i64* %bytes_written, align 8, !dbg !3619
  %135 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3620
  %req146 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %135, i32 0, i32 12, !dbg !3621
  %upload_fromhere147 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req146, i32 0, i32 38, !dbg !3622
  %136 = load i8*, i8** %upload_fromhere147, align 8, !dbg !3623
  %add.ptr = getelementptr inbounds i8, i8* %136, i64 %134, !dbg !3623
  store i8* %add.ptr, i8** %upload_fromhere147, align 8, !dbg !3623
  br label %if.end162, !dbg !3624

if.else148:                                       ; preds = %if.end138
  %137 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3625
  %uploadbuf149 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %137, i32 0, i32 29, !dbg !3627
  %138 = load i8*, i8** %uploadbuf149, align 8, !dbg !3627
  %139 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3628
  %req150 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %139, i32 0, i32 12, !dbg !3629
  %upload_fromhere151 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req150, i32 0, i32 38, !dbg !3630
  store i8* %138, i8** %upload_fromhere151, align 8, !dbg !3631
  %140 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3632
  %req152 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %140, i32 0, i32 12, !dbg !3633
  %upload_present153 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req152, i32 0, i32 37, !dbg !3634
  store i64 0, i64* %upload_present153, align 8, !dbg !3635
  %141 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3636
  %upload_done154 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %141, i32 0, i32 32, !dbg !3638
  %142 = load i8, i8* %upload_done154, align 8, !dbg !3638
  %tobool155 = trunc i8 %142 to i1, !dbg !3638
  br i1 %tobool155, label %if.then156, label %if.end161, !dbg !3639

if.then156:                                       ; preds = %if.else148
  %143 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3640
  %144 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3642
  %call157 = call i32 @done_sending(%struct.connectdata* %143, %struct.SingleRequest* %144), !dbg !3643
  store i32 %call157, i32* %result, align 4, !dbg !3644
  %145 = load i32, i32* %result, align 4, !dbg !3645
  %tobool158 = icmp ne i32 %145, 0, !dbg !3645
  br i1 %tobool158, label %if.then159, label %if.end160, !dbg !3647

if.then159:                                       ; preds = %if.then156
  %146 = load i32, i32* %result, align 4, !dbg !3648
  store i32 %146, i32* %retval, align 4, !dbg !3649
  br label %return, !dbg !3649

if.end160:                                        ; preds = %if.then156
  br label %if.end161, !dbg !3650

if.end161:                                        ; preds = %if.end160, %if.else148
  br label %if.end162

if.end162:                                        ; preds = %if.end161, %if.then143
  %147 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3651
  %148 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !3652
  %writebytecount163 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %148, i32 0, i32 5, !dbg !3653
  %149 = load i64, i64* %writebytecount163, align 8, !dbg !3653
  call void @Curl_pgrsSetUploadCounter(%struct.Curl_easy* %147, i64 %149), !dbg !3654
  br label %do.end, !dbg !3655

do.end:                                           ; preds = %if.end162, %if.end41, %if.then33, %if.then10
  store i32 0, i32* %retval, align 4, !dbg !3656
  br label %return, !dbg !3656

return:                                           ; preds = %do.end, %if.then159, %if.then121, %if.then62, %if.then40, %if.then24
  %150 = load i32, i32* %retval, align 4, !dbg !3657
  ret i32 %150, !dbg !3657
}

declare { i64, i64 } @curlx_tvnow() #2

declare i64 @curlx_tvdiff(i64, i64, i64, i64) #2

declare i32 @Curl_pgrsUpdate(%struct.connectdata*) #2

declare i32 @Curl_speedcheck(%struct.Curl_easy*, i64, i64) #2

declare i64 @Curl_timeleft(%struct.Curl_easy*, %struct.timeval*, i1 zeroext) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_single_getsock(%struct.connectdata* %conn, i32* %sock, i32 %numsocks) #0 !dbg !1777 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %sock.addr = alloca i32*, align 8
  %numsocks.addr = alloca i32, align 4
  %data = alloca %struct.Curl_easy*, align 8
  %bitmap = alloca i32, align 4
  %sockindex = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !3658, metadata !1827), !dbg !3659
  store i32* %sock, i32** %sock.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %sock.addr, metadata !3660, metadata !1827), !dbg !3661
  store i32 %numsocks, i32* %numsocks.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %numsocks.addr, metadata !3662, metadata !1827), !dbg !3663
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !3664, metadata !1827), !dbg !3667
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3668
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !3669
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !3669
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !3667
  call void @llvm.dbg.declare(metadata i32* %bitmap, metadata !3670, metadata !1827), !dbg !3671
  store i32 0, i32* %bitmap, align 4, !dbg !3671
  call void @llvm.dbg.declare(metadata i32* %sockindex, metadata !3672, metadata !1827), !dbg !3673
  store i32 0, i32* %sockindex, align 4, !dbg !3673
  %2 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3674
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 47, !dbg !3676
  %3 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !3676
  %perform_getsock = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %3, i32 0, i32 11, !dbg !3677
  %4 = load i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)** %perform_getsock, align 8, !dbg !3677
  %tobool = icmp ne i32 (%struct.connectdata*, i32*, i32)* %4, null, !dbg !3674
  br i1 %tobool, label %if.then, label %if.end, !dbg !3678

if.then:                                          ; preds = %entry
  %5 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3679
  %handler2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %5, i32 0, i32 47, !dbg !3680
  %6 = load %struct.Curl_handler*, %struct.Curl_handler** %handler2, align 8, !dbg !3680
  %perform_getsock3 = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %6, i32 0, i32 11, !dbg !3681
  %7 = load i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)** %perform_getsock3, align 8, !dbg !3681
  %8 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3682
  %9 = load i32*, i32** %sock.addr, align 8, !dbg !3683
  %10 = load i32, i32* %numsocks.addr, align 4, !dbg !3684
  %call = call i32 %7(%struct.connectdata* %8, i32* %9, i32 %10), !dbg !3679
  store i32 %call, i32* %retval, align 4, !dbg !3685
  br label %return, !dbg !3685

if.end:                                           ; preds = %entry
  %11 = load i32, i32* %numsocks.addr, align 4, !dbg !3686
  %cmp = icmp slt i32 %11, 2, !dbg !3688
  br i1 %cmp, label %if.then4, label %if.end5, !dbg !3689

if.then4:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !3690
  br label %return, !dbg !3690

if.end5:                                          ; preds = %if.end
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3691
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 12, !dbg !3693
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 31, !dbg !3694
  %13 = load i32, i32* %keepon, align 4, !dbg !3694
  %and = and i32 %13, 21, !dbg !3695
  %cmp6 = icmp eq i32 %and, 1, !dbg !3696
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !3697

if.then7:                                         ; preds = %if.end5
  br label %do.body, !dbg !3698

do.body:                                          ; preds = %if.then7
  br label %do.end, !dbg !3700

do.end:                                           ; preds = %do.body
  %14 = load i32, i32* %sockindex, align 4, !dbg !3703
  %shl = shl i32 1, %14, !dbg !3703
  %15 = load i32, i32* %bitmap, align 4, !dbg !3704
  %or = or i32 %15, %shl, !dbg !3704
  store i32 %or, i32* %bitmap, align 4, !dbg !3704
  %16 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3705
  %sockfd = getelementptr inbounds %struct.connectdata, %struct.connectdata* %16, i32 0, i32 50, !dbg !3706
  %17 = load i32, i32* %sockfd, align 8, !dbg !3706
  %18 = load i32, i32* %sockindex, align 4, !dbg !3707
  %idxprom = zext i32 %18 to i64, !dbg !3708
  %19 = load i32*, i32** %sock.addr, align 8, !dbg !3708
  %arrayidx = getelementptr inbounds i32, i32* %19, i64 %idxprom, !dbg !3708
  store i32 %17, i32* %arrayidx, align 4, !dbg !3709
  br label %if.end8, !dbg !3710

if.end8:                                          ; preds = %do.end, %if.end5
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3711
  %req9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %20, i32 0, i32 12, !dbg !3713
  %keepon10 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req9, i32 0, i32 31, !dbg !3714
  %21 = load i32, i32* %keepon10, align 4, !dbg !3714
  %and11 = and i32 %21, 42, !dbg !3715
  %cmp12 = icmp eq i32 %and11, 2, !dbg !3716
  br i1 %cmp12, label %if.then13, label %if.end29, !dbg !3717

if.then13:                                        ; preds = %if.end8
  %22 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3718
  %sockfd14 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %22, i32 0, i32 50, !dbg !3721
  %23 = load i32, i32* %sockfd14, align 8, !dbg !3721
  %24 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3722
  %writesockfd = getelementptr inbounds %struct.connectdata, %struct.connectdata* %24, i32 0, i32 51, !dbg !3723
  %25 = load i32, i32* %writesockfd, align 4, !dbg !3723
  %cmp15 = icmp ne i32 %23, %25, !dbg !3724
  br i1 %cmp15, label %if.then17, label %lor.lhs.false, !dbg !3725

lor.lhs.false:                                    ; preds = %if.then13
  %26 = load i32, i32* %bitmap, align 4, !dbg !3726
  %cmp16 = icmp eq i32 %26, 0, !dbg !3727
  br i1 %cmp16, label %if.then17, label %if.end26, !dbg !3728

if.then17:                                        ; preds = %lor.lhs.false, %if.then13
  %27 = load i32, i32* %bitmap, align 4, !dbg !3730
  %cmp18 = icmp ne i32 %27, 0, !dbg !3733
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !3734

if.then19:                                        ; preds = %if.then17
  %28 = load i32, i32* %sockindex, align 4, !dbg !3735
  %inc = add i32 %28, 1, !dbg !3735
  store i32 %inc, i32* %sockindex, align 4, !dbg !3735
  br label %if.end20, !dbg !3736

if.end20:                                         ; preds = %if.then19, %if.then17
  br label %do.body21, !dbg !3737

do.body21:                                        ; preds = %if.end20
  br label %do.end22, !dbg !3738

do.end22:                                         ; preds = %do.body21
  %29 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3741
  %writesockfd23 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %29, i32 0, i32 51, !dbg !3742
  %30 = load i32, i32* %writesockfd23, align 4, !dbg !3742
  %31 = load i32, i32* %sockindex, align 4, !dbg !3743
  %idxprom24 = zext i32 %31 to i64, !dbg !3744
  %32 = load i32*, i32** %sock.addr, align 8, !dbg !3744
  %arrayidx25 = getelementptr inbounds i32, i32* %32, i64 %idxprom24, !dbg !3744
  store i32 %30, i32* %arrayidx25, align 4, !dbg !3745
  br label %if.end26, !dbg !3746

if.end26:                                         ; preds = %do.end22, %lor.lhs.false
  %33 = load i32, i32* %sockindex, align 4, !dbg !3747
  %add = add i32 16, %33, !dbg !3747
  %shl27 = shl i32 1, %add, !dbg !3747
  %34 = load i32, i32* %bitmap, align 4, !dbg !3748
  %or28 = or i32 %34, %shl27, !dbg !3748
  store i32 %or28, i32* %bitmap, align 4, !dbg !3748
  br label %if.end29, !dbg !3749

if.end29:                                         ; preds = %if.end26, %if.end8
  %35 = load i32, i32* %bitmap, align 4, !dbg !3750
  store i32 %35, i32* %retval, align 4, !dbg !3751
  br label %return, !dbg !3751

return:                                           ; preds = %if.end29, %if.then4, %if.then
  %36 = load i32, i32* %retval, align 4, !dbg !3752
  ret i32 %36, !dbg !3752
}

; Function Attrs: nounwind uwtable
define void @Curl_init_CONNECT(%struct.Curl_easy* %data) #0 !dbg !1778 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !3753, metadata !1827), !dbg !3754
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3755
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 13, !dbg !3756
  %fread_func_set = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 23, !dbg !3757
  %1 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %fread_func_set, align 8, !dbg !3757
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3758
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 17, !dbg !3759
  %fread_func = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 50, !dbg !3760
  store i64 (i8*, i64, i64, i8*)* %1, i64 (i8*, i64, i64, i8*)** %fread_func, align 8, !dbg !3761
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3762
  %set1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 13, !dbg !3763
  %in_set = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set1, i32 0, i32 5, !dbg !3764
  %4 = load i8*, i8** %in_set, align 8, !dbg !3764
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3765
  %state2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %5, i32 0, i32 17, !dbg !3766
  %in = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state2, i32 0, i32 51, !dbg !3767
  store i8* %4, i8** %in, align 8, !dbg !3768
  ret void, !dbg !3769
}

; Function Attrs: nounwind uwtable
define i32 @Curl_pretransfer(%struct.Curl_easy* %data) #0 !dbg !1781 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %result = alloca i32, align 4
  %wc = alloca %struct.WildcardData*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !3770, metadata !1827), !dbg !3771
  call void @llvm.dbg.declare(metadata i32* %result, metadata !3772, metadata !1827), !dbg !3773
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3774
  %change = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 14, !dbg !3776
  %url = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change, i32 0, i32 0, !dbg !3777
  %1 = load i8*, i8** %url, align 8, !dbg !3777
  %tobool = icmp ne i8* %1, null, !dbg !3774
  br i1 %tobool, label %if.end, label %if.then, !dbg !3778

if.then:                                          ; preds = %entry
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3779
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %2, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.18, i32 0, i32 0)), !dbg !3781
  store i32 3, i32* %retval, align 4, !dbg !3782
  br label %return, !dbg !3782

if.end:                                           ; preds = %entry
  store i32 0, i32* %result, align 4, !dbg !3783
  %3 = load i32, i32* %result, align 4, !dbg !3784
  %tobool1 = icmp ne i32 %3, 0, !dbg !3784
  br i1 %tobool1, label %if.then2, label %if.end3, !dbg !3786

if.then2:                                         ; preds = %if.end
  %4 = load i32, i32* %result, align 4, !dbg !3787
  store i32 %4, i32* %retval, align 4, !dbg !3788
  br label %return, !dbg !3788

if.end3:                                          ; preds = %if.end
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3789
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %5, i32 0, i32 13, !dbg !3790
  %followlocation = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 11, !dbg !3791
  store i64 0, i64* %followlocation, align 8, !dbg !3792
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3793
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 17, !dbg !3794
  %this_is_a_follow = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 9, !dbg !3795
  store i8 0, i8* %this_is_a_follow, align 8, !dbg !3796
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3797
  %state4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 17, !dbg !3798
  %errorbuf = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state4, i32 0, i32 17, !dbg !3799
  store i8 0, i8* %errorbuf, align 8, !dbg !3800
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3801
  %state5 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %8, i32 0, i32 17, !dbg !3802
  %httpversion = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state5, i32 0, i32 32, !dbg !3803
  store i32 0, i32* %httpversion, align 4, !dbg !3804
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3805
  %state6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 17, !dbg !3806
  %authproblem = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state6, i32 0, i32 25, !dbg !3807
  store i8 0, i8* %authproblem, align 8, !dbg !3808
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3809
  %set7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 13, !dbg !3810
  %httpauth = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set7, i32 0, i32 9, !dbg !3811
  %11 = load i64, i64* %httpauth, align 8, !dbg !3811
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3812
  %state8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 17, !dbg !3813
  %authhost = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state8, i32 0, i32 23, !dbg !3814
  %want = getelementptr inbounds %struct.auth, %struct.auth* %authhost, i32 0, i32 0, !dbg !3815
  store i64 %11, i64* %want, align 8, !dbg !3816
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3817
  %set9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 13, !dbg !3818
  %proxyauth = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set9, i32 0, i32 10, !dbg !3819
  %14 = load i64, i64* %proxyauth, align 8, !dbg !3819
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3820
  %state10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 17, !dbg !3821
  %authproxy = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state10, i32 0, i32 24, !dbg !3822
  %want11 = getelementptr inbounds %struct.auth, %struct.auth* %authproxy, i32 0, i32 0, !dbg !3823
  store i64 %14, i64* %want11, align 8, !dbg !3824
  br label %do.body, !dbg !3825

do.body:                                          ; preds = %if.end3
  %16 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !3826
  %17 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3826
  %info = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %17, i32 0, i32 19, !dbg !3826
  %wouldredirect = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info, i32 0, i32 11, !dbg !3826
  %18 = load i8*, i8** %wouldredirect, align 8, !dbg !3826
  call void %16(i8* %18), !dbg !3826
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3826
  %info12 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %19, i32 0, i32 19, !dbg !3826
  %wouldredirect13 = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info12, i32 0, i32 11, !dbg !3826
  store i8* null, i8** %wouldredirect13, align 8, !dbg !3826
  br label %do.end, !dbg !3826

do.end:                                           ; preds = %do.body
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3829
  %info14 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %20, i32 0, i32 19, !dbg !3830
  %wouldredirect15 = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info14, i32 0, i32 11, !dbg !3831
  store i8* null, i8** %wouldredirect15, align 8, !dbg !3832
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3833
  %set16 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %21, i32 0, i32 13, !dbg !3835
  %httpreq = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set16, i32 0, i32 71, !dbg !3836
  %22 = load i32, i32* %httpreq, align 8, !dbg !3836
  %cmp = icmp eq i32 %22, 4, !dbg !3837
  br i1 %cmp, label %if.then17, label %if.else, !dbg !3838

if.then17:                                        ; preds = %do.end
  %23 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3839
  %set18 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %23, i32 0, i32 13, !dbg !3840
  %filesize = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set18, i32 0, i32 48, !dbg !3841
  %24 = load i64, i64* %filesize, align 8, !dbg !3841
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3842
  %state19 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 17, !dbg !3843
  %infilesize = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state19, i32 0, i32 47, !dbg !3844
  store i64 %24, i64* %infilesize, align 8, !dbg !3845
  br label %if.end23, !dbg !3842

if.else:                                          ; preds = %do.end
  %26 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3846
  %set20 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %26, i32 0, i32 13, !dbg !3847
  %postfieldsize = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set20, i32 0, i32 17, !dbg !3848
  %27 = load i64, i64* %postfieldsize, align 8, !dbg !3848
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3849
  %state21 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %28, i32 0, i32 17, !dbg !3850
  %infilesize22 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state21, i32 0, i32 47, !dbg !3851
  store i64 %27, i64* %infilesize22, align 8, !dbg !3852
  br label %if.end23

if.end23:                                         ; preds = %if.else, %if.then17
  %29 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3853
  %change24 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %29, i32 0, i32 14, !dbg !3855
  %cookielist = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change24, i32 0, i32 4, !dbg !3856
  %30 = load %struct.curl_slist*, %struct.curl_slist** %cookielist, align 8, !dbg !3856
  %tobool25 = icmp ne %struct.curl_slist* %30, null, !dbg !3853
  br i1 %tobool25, label %if.then26, label %if.end27, !dbg !3857

if.then26:                                        ; preds = %if.end23
  %31 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3858
  call void @Curl_cookie_loadfiles(%struct.Curl_easy* %31), !dbg !3859
  br label %if.end27, !dbg !3859

if.end27:                                         ; preds = %if.then26, %if.end23
  %32 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3860
  %change28 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %32, i32 0, i32 14, !dbg !3862
  %resolve = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change28, i32 0, i32 5, !dbg !3863
  %33 = load %struct.curl_slist*, %struct.curl_slist** %resolve, align 8, !dbg !3863
  %tobool29 = icmp ne %struct.curl_slist* %33, null, !dbg !3860
  br i1 %tobool29, label %if.then30, label %if.end31, !dbg !3864

if.then30:                                        ; preds = %if.end27
  %34 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3865
  %call = call i32 @Curl_loadhostpairs(%struct.Curl_easy* %34), !dbg !3866
  store i32 %call, i32* %result, align 4, !dbg !3867
  br label %if.end31, !dbg !3868

if.end31:                                         ; preds = %if.then30, %if.end27
  %35 = load i32, i32* %result, align 4, !dbg !3869
  %tobool32 = icmp ne i32 %35, 0, !dbg !3869
  br i1 %tobool32, label %if.end72, label %if.then33, !dbg !3871

if.then33:                                        ; preds = %if.end31
  %36 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3872
  %state34 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %36, i32 0, i32 17, !dbg !3874
  %allow_port = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state34, i32 0, i32 20, !dbg !3875
  store i8 1, i8* %allow_port, align 8, !dbg !3876
  %37 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3877
  %call35 = call i32 @Curl_initinfo(%struct.Curl_easy* %37), !dbg !3878
  %38 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3879
  call void @Curl_pgrsResetTimesSizes(%struct.Curl_easy* %38), !dbg !3880
  %39 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3881
  call void @Curl_pgrsStartNow(%struct.Curl_easy* %39), !dbg !3882
  %40 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3883
  %set36 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %40, i32 0, i32 13, !dbg !3885
  %timeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set36, i32 0, i32 42, !dbg !3886
  %41 = load i64, i64* %timeout, align 8, !dbg !3886
  %tobool37 = icmp ne i64 %41, 0, !dbg !3883
  br i1 %tobool37, label %if.then38, label %if.end41, !dbg !3887

if.then38:                                        ; preds = %if.then33
  %42 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3888
  %43 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3889
  %set39 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %43, i32 0, i32 13, !dbg !3890
  %timeout40 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set39, i32 0, i32 42, !dbg !3891
  %44 = load i64, i64* %timeout40, align 8, !dbg !3891
  call void @Curl_expire(%struct.Curl_easy* %42, i64 %44), !dbg !3892
  br label %if.end41, !dbg !3892

if.end41:                                         ; preds = %if.then38, %if.then33
  %45 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3893
  %set42 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %45, i32 0, i32 13, !dbg !3895
  %connecttimeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set42, i32 0, i32 43, !dbg !3896
  %46 = load i64, i64* %connecttimeout, align 8, !dbg !3896
  %tobool43 = icmp ne i64 %46, 0, !dbg !3893
  br i1 %tobool43, label %if.then44, label %if.end47, !dbg !3897

if.then44:                                        ; preds = %if.end41
  %47 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3898
  %48 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3899
  %set45 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %48, i32 0, i32 13, !dbg !3900
  %connecttimeout46 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set45, i32 0, i32 43, !dbg !3901
  %49 = load i64, i64* %connecttimeout46, align 8, !dbg !3901
  call void @Curl_expire(%struct.Curl_easy* %47, i64 %49), !dbg !3902
  br label %if.end47, !dbg !3902

if.end47:                                         ; preds = %if.then44, %if.end41
  %50 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3903
  %state48 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %50, i32 0, i32 17, !dbg !3904
  %authhost49 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state48, i32 0, i32 23, !dbg !3905
  %want50 = getelementptr inbounds %struct.auth, %struct.auth* %authhost49, i32 0, i32 0, !dbg !3906
  %51 = load i64, i64* %want50, align 8, !dbg !3906
  %52 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3907
  %state51 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %52, i32 0, i32 17, !dbg !3908
  %authhost52 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state51, i32 0, i32 23, !dbg !3909
  %picked = getelementptr inbounds %struct.auth, %struct.auth* %authhost52, i32 0, i32 1, !dbg !3910
  %53 = load i64, i64* %picked, align 8, !dbg !3911
  %and = and i64 %53, %51, !dbg !3911
  store i64 %and, i64* %picked, align 8, !dbg !3911
  %54 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3912
  %state53 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %54, i32 0, i32 17, !dbg !3913
  %authproxy54 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state53, i32 0, i32 24, !dbg !3914
  %want55 = getelementptr inbounds %struct.auth, %struct.auth* %authproxy54, i32 0, i32 0, !dbg !3915
  %55 = load i64, i64* %want55, align 8, !dbg !3915
  %56 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3916
  %state56 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %56, i32 0, i32 17, !dbg !3917
  %authproxy57 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state56, i32 0, i32 24, !dbg !3918
  %picked58 = getelementptr inbounds %struct.auth, %struct.auth* %authproxy57, i32 0, i32 1, !dbg !3919
  %57 = load i64, i64* %picked58, align 8, !dbg !3920
  %and59 = and i64 %57, %55, !dbg !3920
  store i64 %and59, i64* %picked58, align 8, !dbg !3920
  %58 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3921
  %set60 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %58, i32 0, i32 13, !dbg !3923
  %wildcardmatch = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set60, i32 0, i32 136, !dbg !3924
  %59 = load i8, i8* %wildcardmatch, align 8, !dbg !3924
  %tobool61 = trunc i8 %59 to i1, !dbg !3924
  br i1 %tobool61, label %if.then62, label %if.end71, !dbg !3925

if.then62:                                        ; preds = %if.end47
  call void @llvm.dbg.declare(metadata %struct.WildcardData** %wc, metadata !3926, metadata !1827), !dbg !3929
  %60 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3930
  %wildcard = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %60, i32 0, i32 18, !dbg !3931
  store %struct.WildcardData* %wildcard, %struct.WildcardData** %wc, align 8, !dbg !3929
  %61 = load %struct.WildcardData*, %struct.WildcardData** %wc, align 8, !dbg !3932
  %state63 = getelementptr inbounds %struct.WildcardData, %struct.WildcardData* %61, i32 0, i32 0, !dbg !3934
  %62 = load i32, i32* %state63, align 8, !dbg !3934
  %cmp64 = icmp ult i32 %62, 1, !dbg !3935
  br i1 %cmp64, label %if.then65, label %if.end70, !dbg !3936

if.then65:                                        ; preds = %if.then62
  %63 = load %struct.WildcardData*, %struct.WildcardData** %wc, align 8, !dbg !3937
  %call66 = call i32 @Curl_wildcard_init(%struct.WildcardData* %63), !dbg !3939
  store i32 %call66, i32* %result, align 4, !dbg !3940
  %64 = load i32, i32* %result, align 4, !dbg !3941
  %tobool67 = icmp ne i32 %64, 0, !dbg !3941
  br i1 %tobool67, label %if.then68, label %if.end69, !dbg !3943

if.then68:                                        ; preds = %if.then65
  store i32 27, i32* %retval, align 4, !dbg !3944
  br label %return, !dbg !3944

if.end69:                                         ; preds = %if.then65
  br label %if.end70, !dbg !3945

if.end70:                                         ; preds = %if.end69, %if.then62
  br label %if.end71, !dbg !3946

if.end71:                                         ; preds = %if.end70, %if.end47
  br label %if.end72, !dbg !3947

if.end72:                                         ; preds = %if.end71, %if.end31
  %65 = load i32, i32* %result, align 4, !dbg !3948
  store i32 %65, i32* %retval, align 4, !dbg !3949
  br label %return, !dbg !3949

return:                                           ; preds = %if.end72, %if.then68, %if.then2, %if.then
  %66 = load i32, i32* %retval, align 4, !dbg !3950
  ret i32 %66, !dbg !3950
}

declare void @Curl_cookie_loadfiles(%struct.Curl_easy*) #2

declare i32 @Curl_loadhostpairs(%struct.Curl_easy*) #2

declare i32 @Curl_initinfo(%struct.Curl_easy*) #2

declare void @Curl_pgrsResetTimesSizes(%struct.Curl_easy*) #2

declare void @Curl_pgrsStartNow(%struct.Curl_easy*) #2

declare void @Curl_expire(%struct.Curl_easy*, i64) #2

declare i32 @Curl_wildcard_init(%struct.WildcardData*) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_posttransfer(%struct.Curl_easy* %data) #0 !dbg !1784 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !3951, metadata !1827), !dbg !3952
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3953
  ret i32 0, !dbg !3954
}

; Function Attrs: nounwind uwtable
define i32 @Curl_follow(%struct.Curl_easy* %data, i8* %newurl, i32 %type) #0 !dbg !1785 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %newurl.addr = alloca i8*, align 8
  %type.addr = alloca i32, align 4
  %disallowport = alloca i8, align 1
  %absolute = alloca i8*, align 8
  %newest = alloca i8*, align 8
  %newlen = alloca i64, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !3955, metadata !1827), !dbg !3956
  store i8* %newurl, i8** %newurl.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %newurl.addr, metadata !3957, metadata !1827), !dbg !3958
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !3959, metadata !1827), !dbg !3960
  call void @llvm.dbg.declare(metadata i8* %disallowport, metadata !3961, metadata !1827), !dbg !3962
  store i8 0, i8* %disallowport, align 1, !dbg !3962
  %0 = load i32, i32* %type.addr, align 4, !dbg !3963
  %cmp = icmp eq i32 %0, 3, !dbg !3965
  br i1 %cmp, label %if.then, label %if.end32, !dbg !3966

if.then:                                          ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3967
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 13, !dbg !3970
  %maxredirs = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 12, !dbg !3971
  %2 = load i64, i64* %maxredirs, align 8, !dbg !3971
  %cmp1 = icmp ne i64 %2, -1, !dbg !3972
  br i1 %cmp1, label %land.lhs.true, label %if.end, !dbg !3973

land.lhs.true:                                    ; preds = %if.then
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3974
  %set2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 13, !dbg !3975
  %followlocation = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set2, i32 0, i32 11, !dbg !3976
  %4 = load i64, i64* %followlocation, align 8, !dbg !3976
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3977
  %set3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %5, i32 0, i32 13, !dbg !3978
  %maxredirs4 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set3, i32 0, i32 12, !dbg !3979
  %6 = load i64, i64* %maxredirs4, align 8, !dbg !3979
  %cmp5 = icmp sge i64 %4, %6, !dbg !3980
  br i1 %cmp5, label %if.then6, label %if.end, !dbg !3981

if.then6:                                         ; preds = %land.lhs.true
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3983
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3985
  %set7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %8, i32 0, i32 13, !dbg !3986
  %maxredirs8 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set7, i32 0, i32 12, !dbg !3987
  %9 = load i64, i64* %maxredirs8, align 8, !dbg !3987
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %7, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.19, i32 0, i32 0), i64 %9), !dbg !3988
  store i32 47, i32* %retval, align 4, !dbg !3989
  br label %return, !dbg !3989

if.end:                                           ; preds = %land.lhs.true, %if.then
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3990
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 17, !dbg !3991
  %this_is_a_follow = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 9, !dbg !3992
  store i8 1, i8* %this_is_a_follow, align 8, !dbg !3993
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3994
  %set9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 13, !dbg !3995
  %followlocation10 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set9, i32 0, i32 11, !dbg !3996
  %12 = load i64, i64* %followlocation10, align 8, !dbg !3997
  %inc = add nsw i64 %12, 1, !dbg !3997
  store i64 %inc, i64* %followlocation10, align 8, !dbg !3997
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3998
  %set11 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 13, !dbg !4000
  %http_auto_referer = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set11, i32 0, i32 102, !dbg !4001
  %14 = load i8, i8* %http_auto_referer, align 1, !dbg !4001
  %tobool = trunc i8 %14 to i1, !dbg !4001
  br i1 %tobool, label %if.then12, label %if.end31, !dbg !4002

if.then12:                                        ; preds = %if.end
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4003
  %change = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 14, !dbg !4006
  %referer_alloc = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change, i32 0, i32 3, !dbg !4007
  %16 = load i8, i8* %referer_alloc, align 8, !dbg !4007
  %tobool13 = trunc i8 %16 to i1, !dbg !4007
  br i1 %tobool13, label %if.then14, label %if.end20, !dbg !4008

if.then14:                                        ; preds = %if.then12
  br label %do.body, !dbg !4009

do.body:                                          ; preds = %if.then14
  %17 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !4011
  %18 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4011
  %change15 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %18, i32 0, i32 14, !dbg !4011
  %referer = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change15, i32 0, i32 2, !dbg !4011
  %19 = load i8*, i8** %referer, align 8, !dbg !4011
  call void %17(i8* %19), !dbg !4011
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4011
  %change16 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %20, i32 0, i32 14, !dbg !4011
  %referer17 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change16, i32 0, i32 2, !dbg !4011
  store i8* null, i8** %referer17, align 8, !dbg !4011
  br label %do.end, !dbg !4011

do.end:                                           ; preds = %do.body
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4014
  %change18 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %21, i32 0, i32 14, !dbg !4015
  %referer_alloc19 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change18, i32 0, i32 3, !dbg !4016
  store i8 0, i8* %referer_alloc19, align 8, !dbg !4017
  br label %if.end20, !dbg !4018

if.end20:                                         ; preds = %do.end, %if.then12
  %22 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !4019
  %23 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4019
  %change21 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %23, i32 0, i32 14, !dbg !4019
  %url = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change21, i32 0, i32 0, !dbg !4019
  %24 = load i8*, i8** %url, align 8, !dbg !4019
  %call = call i8* %22(i8* %24), !dbg !4019
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4020
  %change22 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 14, !dbg !4021
  %referer23 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change22, i32 0, i32 2, !dbg !4022
  store i8* %call, i8** %referer23, align 8, !dbg !4023
  %26 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4024
  %change24 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %26, i32 0, i32 14, !dbg !4026
  %referer25 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change24, i32 0, i32 2, !dbg !4027
  %27 = load i8*, i8** %referer25, align 8, !dbg !4027
  %tobool26 = icmp ne i8* %27, null, !dbg !4024
  br i1 %tobool26, label %if.end28, label %if.then27, !dbg !4028

if.then27:                                        ; preds = %if.end20
  store i32 27, i32* %retval, align 4, !dbg !4029
  br label %return, !dbg !4029

if.end28:                                         ; preds = %if.end20
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4030
  %change29 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %28, i32 0, i32 14, !dbg !4031
  %referer_alloc30 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change29, i32 0, i32 3, !dbg !4032
  store i8 1, i8* %referer_alloc30, align 8, !dbg !4033
  br label %if.end31, !dbg !4034

if.end31:                                         ; preds = %if.end28, %if.end
  br label %if.end32, !dbg !4035

if.end32:                                         ; preds = %if.end31, %entry
  %29 = load i8*, i8** %newurl.addr, align 8, !dbg !4036
  %call33 = call zeroext i1 @is_absolute_url(i8* %29), !dbg !4038
  br i1 %call33, label %if.else, label %if.then34, !dbg !4039

if.then34:                                        ; preds = %if.end32
  call void @llvm.dbg.declare(metadata i8** %absolute, metadata !4040, metadata !1827), !dbg !4042
  %30 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4043
  %change35 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %30, i32 0, i32 14, !dbg !4044
  %url36 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change35, i32 0, i32 0, !dbg !4045
  %31 = load i8*, i8** %url36, align 8, !dbg !4045
  %32 = load i8*, i8** %newurl.addr, align 8, !dbg !4046
  %call37 = call i8* @concat_url(i8* %31, i8* %32), !dbg !4047
  store i8* %call37, i8** %absolute, align 8, !dbg !4042
  %33 = load i8*, i8** %absolute, align 8, !dbg !4048
  %tobool38 = icmp ne i8* %33, null, !dbg !4048
  br i1 %tobool38, label %if.end40, label %if.then39, !dbg !4050

if.then39:                                        ; preds = %if.then34
  store i32 27, i32* %retval, align 4, !dbg !4051
  br label %return, !dbg !4051

if.end40:                                         ; preds = %if.then34
  %34 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !4052
  %35 = load i8*, i8** %newurl.addr, align 8, !dbg !4052
  call void %34(i8* %35), !dbg !4052
  %36 = load i8*, i8** %absolute, align 8, !dbg !4053
  store i8* %36, i8** %newurl.addr, align 8, !dbg !4054
  br label %if.end46, !dbg !4055

if.else:                                          ; preds = %if.end32
  call void @llvm.dbg.declare(metadata i8** %newest, metadata !4056, metadata !1827), !dbg !4058
  call void @llvm.dbg.declare(metadata i64* %newlen, metadata !4059, metadata !1827), !dbg !4060
  %37 = load i8*, i8** %newurl.addr, align 8, !dbg !4061
  %call41 = call i64 @strlen_url(i8* %37), !dbg !4062
  store i64 %call41, i64* %newlen, align 8, !dbg !4060
  store i8 1, i8* %disallowport, align 1, !dbg !4063
  %38 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !4064
  %39 = load i64, i64* %newlen, align 8, !dbg !4064
  %add = add i64 %39, 1, !dbg !4064
  %call42 = call i8* %38(i64 %add), !dbg !4064
  store i8* %call42, i8** %newest, align 8, !dbg !4065
  %40 = load i8*, i8** %newest, align 8, !dbg !4066
  %tobool43 = icmp ne i8* %40, null, !dbg !4066
  br i1 %tobool43, label %if.end45, label %if.then44, !dbg !4068

if.then44:                                        ; preds = %if.else
  store i32 27, i32* %retval, align 4, !dbg !4069
  br label %return, !dbg !4069

if.end45:                                         ; preds = %if.else
  %41 = load i8*, i8** %newest, align 8, !dbg !4070
  %42 = load i8*, i8** %newurl.addr, align 8, !dbg !4071
  call void @strcpy_url(i8* %41, i8* %42), !dbg !4072
  %43 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !4073
  %44 = load i8*, i8** %newurl.addr, align 8, !dbg !4073
  call void %43(i8* %44), !dbg !4073
  %45 = load i8*, i8** %newest, align 8, !dbg !4074
  store i8* %45, i8** %newurl.addr, align 8, !dbg !4075
  br label %if.end46

if.end46:                                         ; preds = %if.end45, %if.end40
  %46 = load i32, i32* %type.addr, align 4, !dbg !4076
  %cmp47 = icmp eq i32 %46, 1, !dbg !4078
  br i1 %cmp47, label %if.then48, label %if.end49, !dbg !4079

if.then48:                                        ; preds = %if.end46
  %47 = load i8*, i8** %newurl.addr, align 8, !dbg !4080
  %48 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4082
  %info = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %48, i32 0, i32 19, !dbg !4083
  %wouldredirect = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info, i32 0, i32 11, !dbg !4084
  store i8* %47, i8** %wouldredirect, align 8, !dbg !4085
  store i32 0, i32* %retval, align 4, !dbg !4086
  br label %return, !dbg !4086

if.end49:                                         ; preds = %if.end46
  %49 = load i8, i8* %disallowport, align 1, !dbg !4087
  %tobool50 = trunc i8 %49 to i1, !dbg !4087
  br i1 %tobool50, label %if.then51, label %if.end53, !dbg !4089

if.then51:                                        ; preds = %if.end49
  %50 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4090
  %state52 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %50, i32 0, i32 17, !dbg !4091
  %allow_port = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state52, i32 0, i32 20, !dbg !4092
  store i8 0, i8* %allow_port, align 8, !dbg !4093
  br label %if.end53, !dbg !4090

if.end53:                                         ; preds = %if.then51, %if.end49
  %51 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4094
  %change54 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %51, i32 0, i32 14, !dbg !4096
  %url_alloc = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change54, i32 0, i32 1, !dbg !4097
  %52 = load i8, i8* %url_alloc, align 8, !dbg !4097
  %tobool55 = trunc i8 %52 to i1, !dbg !4097
  br i1 %tobool55, label %if.then56, label %if.end65, !dbg !4098

if.then56:                                        ; preds = %if.end53
  br label %do.body57, !dbg !4099

do.body57:                                        ; preds = %if.then56
  %53 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !4101
  %54 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4101
  %change58 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %54, i32 0, i32 14, !dbg !4101
  %url59 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change58, i32 0, i32 0, !dbg !4101
  %55 = load i8*, i8** %url59, align 8, !dbg !4101
  call void %53(i8* %55), !dbg !4101
  %56 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4101
  %change60 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %56, i32 0, i32 14, !dbg !4101
  %url61 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change60, i32 0, i32 0, !dbg !4101
  store i8* null, i8** %url61, align 8, !dbg !4101
  br label %do.end62, !dbg !4101

do.end62:                                         ; preds = %do.body57
  %57 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4104
  %change63 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %57, i32 0, i32 14, !dbg !4105
  %url_alloc64 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change63, i32 0, i32 1, !dbg !4106
  store i8 0, i8* %url_alloc64, align 8, !dbg !4107
  br label %if.end65, !dbg !4108

if.end65:                                         ; preds = %do.end62, %if.end53
  %58 = load i8*, i8** %newurl.addr, align 8, !dbg !4109
  %59 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4110
  %change66 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %59, i32 0, i32 14, !dbg !4111
  %url67 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change66, i32 0, i32 0, !dbg !4112
  store i8* %58, i8** %url67, align 8, !dbg !4113
  %60 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4114
  %change68 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %60, i32 0, i32 14, !dbg !4115
  %url_alloc69 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change68, i32 0, i32 1, !dbg !4116
  store i8 1, i8* %url_alloc69, align 8, !dbg !4117
  store i8* null, i8** %newurl.addr, align 8, !dbg !4118
  %61 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4119
  %62 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4120
  %change70 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %62, i32 0, i32 14, !dbg !4121
  %url71 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change70, i32 0, i32 0, !dbg !4122
  %63 = load i8*, i8** %url71, align 8, !dbg !4122
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %61, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.20, i32 0, i32 0), i8* %63), !dbg !4123
  %64 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4124
  %info72 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %64, i32 0, i32 19, !dbg !4125
  %httpcode = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info72, i32 0, i32 0, !dbg !4126
  %65 = load i32, i32* %httpcode, align 8, !dbg !4126
  switch i32 %65, label %sw.default [
    i32 301, label %sw.bb
    i32 302, label %sw.bb85
    i32 303, label %sw.bb102
    i32 304, label %sw.bb117
    i32 305, label %sw.bb118
  ], !dbg !4127

sw.default:                                       ; preds = %if.end65
  br label %sw.epilog, !dbg !4128

sw.bb:                                            ; preds = %if.end65
  %66 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4130
  %set73 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %66, i32 0, i32 13, !dbg !4132
  %httpreq = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set73, i32 0, i32 71, !dbg !4133
  %67 = load i32, i32* %httpreq, align 8, !dbg !4133
  %cmp74 = icmp eq i32 %67, 2, !dbg !4134
  br i1 %cmp74, label %land.lhs.true78, label %lor.lhs.false, !dbg !4135

lor.lhs.false:                                    ; preds = %sw.bb
  %68 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4136
  %set75 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %68, i32 0, i32 13, !dbg !4138
  %httpreq76 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set75, i32 0, i32 71, !dbg !4139
  %69 = load i32, i32* %httpreq76, align 8, !dbg !4139
  %cmp77 = icmp eq i32 %69, 3, !dbg !4140
  br i1 %cmp77, label %land.lhs.true78, label %if.end84, !dbg !4141

land.lhs.true78:                                  ; preds = %lor.lhs.false, %sw.bb
  %70 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4142
  %set79 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %70, i32 0, i32 13, !dbg !4143
  %keep_post = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set79, i32 0, i32 13, !dbg !4144
  %71 = load i32, i32* %keep_post, align 8, !dbg !4144
  %and = and i32 %71, 1, !dbg !4145
  %tobool80 = icmp ne i32 %and, 0, !dbg !4145
  br i1 %tobool80, label %if.end84, label %if.then81, !dbg !4146

if.then81:                                        ; preds = %land.lhs.true78
  %72 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4148
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %72, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.21, i32 0, i32 0)), !dbg !4150
  %73 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4151
  %set82 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %73, i32 0, i32 13, !dbg !4152
  %httpreq83 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set82, i32 0, i32 71, !dbg !4153
  store i32 1, i32* %httpreq83, align 8, !dbg !4154
  br label %if.end84, !dbg !4155

if.end84:                                         ; preds = %if.then81, %land.lhs.true78, %lor.lhs.false
  br label %sw.epilog, !dbg !4156

sw.bb85:                                          ; preds = %if.end65
  %74 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4157
  %set86 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %74, i32 0, i32 13, !dbg !4159
  %httpreq87 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set86, i32 0, i32 71, !dbg !4160
  %75 = load i32, i32* %httpreq87, align 8, !dbg !4160
  %cmp88 = icmp eq i32 %75, 2, !dbg !4161
  br i1 %cmp88, label %land.lhs.true93, label %lor.lhs.false89, !dbg !4162

lor.lhs.false89:                                  ; preds = %sw.bb85
  %76 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4163
  %set90 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %76, i32 0, i32 13, !dbg !4165
  %httpreq91 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set90, i32 0, i32 71, !dbg !4166
  %77 = load i32, i32* %httpreq91, align 8, !dbg !4166
  %cmp92 = icmp eq i32 %77, 3, !dbg !4167
  br i1 %cmp92, label %land.lhs.true93, label %if.end101, !dbg !4168

land.lhs.true93:                                  ; preds = %lor.lhs.false89, %sw.bb85
  %78 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4169
  %set94 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %78, i32 0, i32 13, !dbg !4170
  %keep_post95 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set94, i32 0, i32 13, !dbg !4171
  %79 = load i32, i32* %keep_post95, align 8, !dbg !4171
  %and96 = and i32 %79, 2, !dbg !4172
  %tobool97 = icmp ne i32 %and96, 0, !dbg !4172
  br i1 %tobool97, label %if.end101, label %if.then98, !dbg !4173

if.then98:                                        ; preds = %land.lhs.true93
  %80 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4174
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %80, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.21, i32 0, i32 0)), !dbg !4176
  %81 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4177
  %set99 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %81, i32 0, i32 13, !dbg !4178
  %httpreq100 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set99, i32 0, i32 71, !dbg !4179
  store i32 1, i32* %httpreq100, align 8, !dbg !4180
  br label %if.end101, !dbg !4181

if.end101:                                        ; preds = %if.then98, %land.lhs.true93, %lor.lhs.false89
  br label %sw.epilog, !dbg !4182

sw.bb102:                                         ; preds = %if.end65
  %82 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4183
  %set103 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %82, i32 0, i32 13, !dbg !4185
  %httpreq104 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set103, i32 0, i32 71, !dbg !4186
  %83 = load i32, i32* %httpreq104, align 8, !dbg !4186
  %cmp105 = icmp ne i32 %83, 1, !dbg !4187
  br i1 %cmp105, label %land.lhs.true106, label %if.end116, !dbg !4188

land.lhs.true106:                                 ; preds = %sw.bb102
  %84 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4189
  %set107 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %84, i32 0, i32 13, !dbg !4191
  %keep_post108 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set107, i32 0, i32 13, !dbg !4192
  %85 = load i32, i32* %keep_post108, align 8, !dbg !4192
  %and109 = and i32 %85, 4, !dbg !4193
  %tobool110 = icmp ne i32 %and109, 0, !dbg !4193
  br i1 %tobool110, label %if.end116, label %if.then111, !dbg !4194

if.then111:                                       ; preds = %land.lhs.true106
  %86 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4195
  %set112 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %86, i32 0, i32 13, !dbg !4197
  %httpreq113 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set112, i32 0, i32 71, !dbg !4198
  store i32 1, i32* %httpreq113, align 8, !dbg !4199
  %87 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4200
  %88 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4201
  %set114 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %88, i32 0, i32 13, !dbg !4202
  %opt_no_body = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set114, i32 0, i32 103, !dbg !4203
  %89 = load i8, i8* %opt_no_body, align 8, !dbg !4203
  %tobool115 = trunc i8 %89 to i1, !dbg !4203
  %cond = select i1 %tobool115, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.23, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.24, i32 0, i32 0), !dbg !4201
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %87, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.22, i32 0, i32 0), i8* %cond), !dbg !4204
  br label %if.end116, !dbg !4205

if.end116:                                        ; preds = %if.then111, %land.lhs.true106, %sw.bb102
  br label %sw.epilog, !dbg !4206

sw.bb117:                                         ; preds = %if.end65
  br label %sw.epilog, !dbg !4207

sw.bb118:                                         ; preds = %if.end65
  br label %sw.epilog, !dbg !4208

sw.epilog:                                        ; preds = %sw.bb118, %sw.bb117, %if.end116, %if.end101, %if.end84, %sw.default
  %90 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4209
  call void @Curl_pgrsTime(%struct.Curl_easy* %90, i32 10), !dbg !4210
  %91 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !4211
  call void @Curl_pgrsResetTimesSizes(%struct.Curl_easy* %91), !dbg !4212
  store i32 0, i32* %retval, align 4, !dbg !4213
  br label %return, !dbg !4213

return:                                           ; preds = %sw.epilog, %if.then48, %if.then44, %if.then39, %if.then27, %if.then6
  %92 = load i32, i32* %retval, align 4, !dbg !4214
  ret i32 %92, !dbg !4214
}

; Function Attrs: nounwind uwtable
define internal zeroext i1 @is_absolute_url(i8* %url) #0 !dbg !1811 {
entry:
  %url.addr = alloca i8*, align 8
  %prot = alloca [16 x i8], align 16
  %letter = alloca i8, align 1
  store i8* %url, i8** %url.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %url.addr, metadata !4215, metadata !1827), !dbg !4216
  call void @llvm.dbg.declare(metadata [16 x i8]* %prot, metadata !4217, metadata !1827), !dbg !4221
  call void @llvm.dbg.declare(metadata i8* %letter, metadata !4222, metadata !1827), !dbg !4223
  %0 = load i8*, i8** %url.addr, align 8, !dbg !4224
  %arraydecay = getelementptr inbounds [16 x i8], [16 x i8]* %prot, i32 0, i32 0, !dbg !4225
  %call = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %0, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.41, i32 0, i32 0), i8* %arraydecay, i8* %letter) #7, !dbg !4226
  %cmp = icmp eq i32 2, %call, !dbg !4227
  %cond = select i1 %cmp, i32 1, i32 0, !dbg !4228
  %tobool = icmp ne i32 %cond, 0, !dbg !4228
  ret i1 %tobool, !dbg !4229
}

; Function Attrs: nounwind uwtable
define internal i8* @concat_url(i8* %base, i8* %relurl) #0 !dbg !1814 {
entry:
  %retval = alloca i8*, align 8
  %base.addr = alloca i8*, align 8
  %relurl.addr = alloca i8*, align 8
  %newest = alloca i8*, align 8
  %protsep = alloca i8*, align 8
  %pathsep = alloca i8*, align 8
  %newlen = alloca i64, align 8
  %useurl = alloca i8*, align 8
  %urllen = alloca i64, align 8
  %url_clone = alloca i8*, align 8
  %level = alloca i32, align 4
  %sep = alloca i8*, align 8
  store i8* %base, i8** %base.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %base.addr, metadata !4230, metadata !1827), !dbg !4231
  store i8* %relurl, i8** %relurl.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %relurl.addr, metadata !4232, metadata !1827), !dbg !4233
  call void @llvm.dbg.declare(metadata i8** %newest, metadata !4234, metadata !1827), !dbg !4235
  call void @llvm.dbg.declare(metadata i8** %protsep, metadata !4236, metadata !1827), !dbg !4237
  call void @llvm.dbg.declare(metadata i8** %pathsep, metadata !4238, metadata !1827), !dbg !4239
  call void @llvm.dbg.declare(metadata i64* %newlen, metadata !4240, metadata !1827), !dbg !4241
  call void @llvm.dbg.declare(metadata i8** %useurl, metadata !4242, metadata !1827), !dbg !4243
  %0 = load i8*, i8** %relurl.addr, align 8, !dbg !4244
  store i8* %0, i8** %useurl, align 8, !dbg !4243
  call void @llvm.dbg.declare(metadata i64* %urllen, metadata !4245, metadata !1827), !dbg !4246
  call void @llvm.dbg.declare(metadata i8** %url_clone, metadata !4247, metadata !1827), !dbg !4248
  %1 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !4249
  %2 = load i8*, i8** %base.addr, align 8, !dbg !4249
  %call = call i8* %1(i8* %2), !dbg !4249
  store i8* %call, i8** %url_clone, align 8, !dbg !4248
  %3 = load i8*, i8** %url_clone, align 8, !dbg !4250
  %tobool = icmp ne i8* %3, null, !dbg !4250
  br i1 %tobool, label %if.end, label %if.then, !dbg !4252

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !4253
  br label %return, !dbg !4253

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %url_clone, align 8, !dbg !4254
  %call1 = call i8* @strstr(i8* %4, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.42, i32 0, i32 0)) #6, !dbg !4255
  store i8* %call1, i8** %protsep, align 8, !dbg !4256
  %5 = load i8*, i8** %protsep, align 8, !dbg !4257
  %tobool2 = icmp ne i8* %5, null, !dbg !4257
  br i1 %tobool2, label %if.else, label %if.then3, !dbg !4259

if.then3:                                         ; preds = %if.end
  %6 = load i8*, i8** %url_clone, align 8, !dbg !4260
  store i8* %6, i8** %protsep, align 8, !dbg !4261
  br label %if.end4, !dbg !4262

if.else:                                          ; preds = %if.end
  %7 = load i8*, i8** %protsep, align 8, !dbg !4263
  %add.ptr = getelementptr inbounds i8, i8* %7, i64 2, !dbg !4263
  store i8* %add.ptr, i8** %protsep, align 8, !dbg !4263
  br label %if.end4

if.end4:                                          ; preds = %if.else, %if.then3
  %8 = load i8*, i8** %relurl.addr, align 8, !dbg !4264
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 0, !dbg !4264
  %9 = load i8, i8* %arrayidx, align 1, !dbg !4264
  %conv = sext i8 %9 to i32, !dbg !4264
  %cmp = icmp ne i32 47, %conv, !dbg !4266
  br i1 %cmp, label %if.then6, label %if.else64, !dbg !4267

if.then6:                                         ; preds = %if.end4
  call void @llvm.dbg.declare(metadata i32* %level, metadata !4268, metadata !1827), !dbg !4270
  store i32 0, i32* %level, align 4, !dbg !4270
  %10 = load i8*, i8** %protsep, align 8, !dbg !4271
  %call7 = call i8* @strchr(i8* %10, i32 63) #6, !dbg !4272
  store i8* %call7, i8** %pathsep, align 8, !dbg !4273
  %11 = load i8*, i8** %pathsep, align 8, !dbg !4274
  %tobool8 = icmp ne i8* %11, null, !dbg !4274
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !4276

if.then9:                                         ; preds = %if.then6
  %12 = load i8*, i8** %pathsep, align 8, !dbg !4277
  store i8 0, i8* %12, align 1, !dbg !4278
  br label %if.end10, !dbg !4279

if.end10:                                         ; preds = %if.then9, %if.then6
  %13 = load i8*, i8** %useurl, align 8, !dbg !4280
  %arrayidx11 = getelementptr inbounds i8, i8* %13, i64 0, !dbg !4280
  %14 = load i8, i8* %arrayidx11, align 1, !dbg !4280
  %conv12 = sext i8 %14 to i32, !dbg !4280
  %cmp13 = icmp ne i32 %conv12, 63, !dbg !4282
  br i1 %cmp13, label %if.then15, label %if.end20, !dbg !4283

if.then15:                                        ; preds = %if.end10
  %15 = load i8*, i8** %protsep, align 8, !dbg !4284
  %call16 = call i8* @strrchr(i8* %15, i32 47) #6, !dbg !4286
  store i8* %call16, i8** %pathsep, align 8, !dbg !4287
  %16 = load i8*, i8** %pathsep, align 8, !dbg !4288
  %tobool17 = icmp ne i8* %16, null, !dbg !4288
  br i1 %tobool17, label %if.then18, label %if.end19, !dbg !4290

if.then18:                                        ; preds = %if.then15
  %17 = load i8*, i8** %pathsep, align 8, !dbg !4291
  store i8 0, i8* %17, align 1, !dbg !4292
  br label %if.end19, !dbg !4293

if.end19:                                         ; preds = %if.then18, %if.then15
  br label %if.end20, !dbg !4294

if.end20:                                         ; preds = %if.end19, %if.end10
  %18 = load i8*, i8** %protsep, align 8, !dbg !4295
  %call21 = call i8* @strchr(i8* %18, i32 47) #6, !dbg !4296
  store i8* %call21, i8** %pathsep, align 8, !dbg !4297
  %19 = load i8*, i8** %pathsep, align 8, !dbg !4298
  %tobool22 = icmp ne i8* %19, null, !dbg !4298
  br i1 %tobool22, label %if.then23, label %if.else25, !dbg !4300

if.then23:                                        ; preds = %if.end20
  %20 = load i8*, i8** %pathsep, align 8, !dbg !4301
  %add.ptr24 = getelementptr inbounds i8, i8* %20, i64 1, !dbg !4302
  store i8* %add.ptr24, i8** %protsep, align 8, !dbg !4303
  br label %if.end26, !dbg !4304

if.else25:                                        ; preds = %if.end20
  store i8* null, i8** %protsep, align 8, !dbg !4305
  br label %if.end26

if.end26:                                         ; preds = %if.else25, %if.then23
  %21 = load i8*, i8** %useurl, align 8, !dbg !4306
  %arrayidx27 = getelementptr inbounds i8, i8* %21, i64 0, !dbg !4306
  %22 = load i8, i8* %arrayidx27, align 1, !dbg !4306
  %conv28 = sext i8 %22 to i32, !dbg !4306
  %cmp29 = icmp eq i32 %conv28, 46, !dbg !4308
  br i1 %cmp29, label %land.lhs.true, label %if.end37, !dbg !4309

land.lhs.true:                                    ; preds = %if.end26
  %23 = load i8*, i8** %useurl, align 8, !dbg !4310
  %arrayidx31 = getelementptr inbounds i8, i8* %23, i64 1, !dbg !4310
  %24 = load i8, i8* %arrayidx31, align 1, !dbg !4310
  %conv32 = sext i8 %24 to i32, !dbg !4310
  %cmp33 = icmp eq i32 %conv32, 47, !dbg !4312
  br i1 %cmp33, label %if.then35, label %if.end37, !dbg !4313

if.then35:                                        ; preds = %land.lhs.true
  %25 = load i8*, i8** %useurl, align 8, !dbg !4314
  %add.ptr36 = getelementptr inbounds i8, i8* %25, i64 2, !dbg !4314
  store i8* %add.ptr36, i8** %useurl, align 8, !dbg !4314
  br label %if.end37, !dbg !4315

if.end37:                                         ; preds = %if.then35, %land.lhs.true, %if.end26
  br label %while.cond, !dbg !4316

while.cond:                                       ; preds = %while.body, %if.end37
  %26 = load i8*, i8** %useurl, align 8, !dbg !4317
  %arrayidx38 = getelementptr inbounds i8, i8* %26, i64 0, !dbg !4317
  %27 = load i8, i8* %arrayidx38, align 1, !dbg !4317
  %conv39 = sext i8 %27 to i32, !dbg !4317
  %cmp40 = icmp eq i32 %conv39, 46, !dbg !4319
  br i1 %cmp40, label %land.lhs.true42, label %land.end, !dbg !4320

land.lhs.true42:                                  ; preds = %while.cond
  %28 = load i8*, i8** %useurl, align 8, !dbg !4321
  %arrayidx43 = getelementptr inbounds i8, i8* %28, i64 1, !dbg !4321
  %29 = load i8, i8* %arrayidx43, align 1, !dbg !4321
  %conv44 = sext i8 %29 to i32, !dbg !4321
  %cmp45 = icmp eq i32 %conv44, 46, !dbg !4322
  br i1 %cmp45, label %land.rhs, label %land.end, !dbg !4323

land.rhs:                                         ; preds = %land.lhs.true42
  %30 = load i8*, i8** %useurl, align 8, !dbg !4324
  %arrayidx47 = getelementptr inbounds i8, i8* %30, i64 2, !dbg !4324
  %31 = load i8, i8* %arrayidx47, align 1, !dbg !4324
  %conv48 = sext i8 %31 to i32, !dbg !4324
  %cmp49 = icmp eq i32 %conv48, 47, !dbg !4325
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true42, %while.cond
  %32 = phi i1 [ false, %land.lhs.true42 ], [ false, %while.cond ], [ %cmp49, %land.rhs ]
  br i1 %32, label %while.body, label %while.end, !dbg !4326

while.body:                                       ; preds = %land.end
  %33 = load i32, i32* %level, align 4, !dbg !4328
  %inc = add nsw i32 %33, 1, !dbg !4328
  store i32 %inc, i32* %level, align 4, !dbg !4328
  %34 = load i8*, i8** %useurl, align 8, !dbg !4330
  %add.ptr51 = getelementptr inbounds i8, i8* %34, i64 3, !dbg !4330
  store i8* %add.ptr51, i8** %useurl, align 8, !dbg !4330
  br label %while.cond, !dbg !4331

while.end:                                        ; preds = %land.end
  %35 = load i8*, i8** %protsep, align 8, !dbg !4333
  %tobool52 = icmp ne i8* %35, null, !dbg !4333
  br i1 %tobool52, label %if.then53, label %if.end63, !dbg !4335

if.then53:                                        ; preds = %while.end
  br label %while.cond54, !dbg !4336

while.cond54:                                     ; preds = %if.end61, %if.then53
  %36 = load i32, i32* %level, align 4, !dbg !4338
  %dec = add nsw i32 %36, -1, !dbg !4338
  store i32 %dec, i32* %level, align 4, !dbg !4338
  %tobool55 = icmp ne i32 %36, 0, !dbg !4340
  br i1 %tobool55, label %while.body56, label %while.end62, !dbg !4340

while.body56:                                     ; preds = %while.cond54
  %37 = load i8*, i8** %protsep, align 8, !dbg !4341
  %call57 = call i8* @strrchr(i8* %37, i32 47) #6, !dbg !4343
  store i8* %call57, i8** %pathsep, align 8, !dbg !4344
  %38 = load i8*, i8** %pathsep, align 8, !dbg !4345
  %tobool58 = icmp ne i8* %38, null, !dbg !4345
  br i1 %tobool58, label %if.then59, label %if.else60, !dbg !4347

if.then59:                                        ; preds = %while.body56
  %39 = load i8*, i8** %pathsep, align 8, !dbg !4348
  store i8 0, i8* %39, align 1, !dbg !4349
  br label %if.end61, !dbg !4350

if.else60:                                        ; preds = %while.body56
  %40 = load i8*, i8** %protsep, align 8, !dbg !4351
  store i8 0, i8* %40, align 1, !dbg !4353
  br label %while.end62, !dbg !4354

if.end61:                                         ; preds = %if.then59
  br label %while.cond54, !dbg !4355

while.end62:                                      ; preds = %if.else60, %while.cond54
  br label %if.end63, !dbg !4357

if.end63:                                         ; preds = %while.end62, %while.end
  br label %if.end94, !dbg !4358

if.else64:                                        ; preds = %if.end4
  %41 = load i8*, i8** %relurl.addr, align 8, !dbg !4359
  %arrayidx65 = getelementptr inbounds i8, i8* %41, i64 0, !dbg !4359
  %42 = load i8, i8* %arrayidx65, align 1, !dbg !4359
  %conv66 = sext i8 %42 to i32, !dbg !4359
  %cmp67 = icmp eq i32 %conv66, 47, !dbg !4362
  br i1 %cmp67, label %land.lhs.true69, label %if.else76, !dbg !4363

land.lhs.true69:                                  ; preds = %if.else64
  %43 = load i8*, i8** %relurl.addr, align 8, !dbg !4364
  %arrayidx70 = getelementptr inbounds i8, i8* %43, i64 1, !dbg !4364
  %44 = load i8, i8* %arrayidx70, align 1, !dbg !4364
  %conv71 = sext i8 %44 to i32, !dbg !4364
  %cmp72 = icmp eq i32 %conv71, 47, !dbg !4366
  br i1 %cmp72, label %if.then74, label %if.else76, !dbg !4367

if.then74:                                        ; preds = %land.lhs.true69
  %45 = load i8*, i8** %protsep, align 8, !dbg !4368
  store i8 0, i8* %45, align 1, !dbg !4370
  %46 = load i8*, i8** %relurl.addr, align 8, !dbg !4371
  %arrayidx75 = getelementptr inbounds i8, i8* %46, i64 2, !dbg !4371
  store i8* %arrayidx75, i8** %useurl, align 8, !dbg !4372
  br label %if.end93, !dbg !4373

if.else76:                                        ; preds = %land.lhs.true69, %if.else64
  %47 = load i8*, i8** %protsep, align 8, !dbg !4374
  %call77 = call i8* @strchr(i8* %47, i32 47) #6, !dbg !4376
  store i8* %call77, i8** %pathsep, align 8, !dbg !4377
  %48 = load i8*, i8** %pathsep, align 8, !dbg !4378
  %tobool78 = icmp ne i8* %48, null, !dbg !4378
  br i1 %tobool78, label %if.then79, label %if.else87, !dbg !4380

if.then79:                                        ; preds = %if.else76
  call void @llvm.dbg.declare(metadata i8** %sep, metadata !4381, metadata !1827), !dbg !4383
  %49 = load i8*, i8** %protsep, align 8, !dbg !4384
  %call80 = call i8* @strchr(i8* %49, i32 63) #6, !dbg !4385
  store i8* %call80, i8** %sep, align 8, !dbg !4383
  %50 = load i8*, i8** %sep, align 8, !dbg !4386
  %tobool81 = icmp ne i8* %50, null, !dbg !4386
  br i1 %tobool81, label %land.lhs.true82, label %if.end86, !dbg !4388

land.lhs.true82:                                  ; preds = %if.then79
  %51 = load i8*, i8** %sep, align 8, !dbg !4389
  %52 = load i8*, i8** %pathsep, align 8, !dbg !4391
  %cmp83 = icmp ult i8* %51, %52, !dbg !4392
  br i1 %cmp83, label %if.then85, label %if.end86, !dbg !4393

if.then85:                                        ; preds = %land.lhs.true82
  %53 = load i8*, i8** %sep, align 8, !dbg !4394
  store i8* %53, i8** %pathsep, align 8, !dbg !4395
  br label %if.end86, !dbg !4396

if.end86:                                         ; preds = %if.then85, %land.lhs.true82, %if.then79
  %54 = load i8*, i8** %pathsep, align 8, !dbg !4397
  store i8 0, i8* %54, align 1, !dbg !4398
  br label %if.end92, !dbg !4399

if.else87:                                        ; preds = %if.else76
  %55 = load i8*, i8** %protsep, align 8, !dbg !4400
  %call88 = call i8* @strchr(i8* %55, i32 63) #6, !dbg !4402
  store i8* %call88, i8** %pathsep, align 8, !dbg !4403
  %56 = load i8*, i8** %pathsep, align 8, !dbg !4404
  %tobool89 = icmp ne i8* %56, null, !dbg !4404
  br i1 %tobool89, label %if.then90, label %if.end91, !dbg !4406

if.then90:                                        ; preds = %if.else87
  %57 = load i8*, i8** %pathsep, align 8, !dbg !4407
  store i8 0, i8* %57, align 1, !dbg !4408
  br label %if.end91, !dbg !4409

if.end91:                                         ; preds = %if.then90, %if.else87
  br label %if.end92

if.end92:                                         ; preds = %if.end91, %if.end86
  br label %if.end93

if.end93:                                         ; preds = %if.end92, %if.then74
  br label %if.end94

if.end94:                                         ; preds = %if.end93, %if.end63
  %58 = load i8*, i8** %useurl, align 8, !dbg !4410
  %call95 = call i64 @strlen_url(i8* %58), !dbg !4411
  store i64 %call95, i64* %newlen, align 8, !dbg !4412
  %59 = load i8*, i8** %url_clone, align 8, !dbg !4413
  %call96 = call i64 @strlen(i8* %59) #6, !dbg !4414
  store i64 %call96, i64* %urllen, align 8, !dbg !4415
  %60 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !4416
  %61 = load i64, i64* %urllen, align 8, !dbg !4416
  %add = add i64 %61, 1, !dbg !4416
  %62 = load i64, i64* %newlen, align 8, !dbg !4416
  %add97 = add i64 %add, %62, !dbg !4416
  %add98 = add i64 %add97, 1, !dbg !4416
  %call99 = call i8* %60(i64 %add98), !dbg !4416
  store i8* %call99, i8** %newest, align 8, !dbg !4417
  %63 = load i8*, i8** %newest, align 8, !dbg !4418
  %tobool100 = icmp ne i8* %63, null, !dbg !4418
  br i1 %tobool100, label %if.end102, label %if.then101, !dbg !4420

if.then101:                                       ; preds = %if.end94
  %64 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !4421
  %65 = load i8*, i8** %url_clone, align 8, !dbg !4421
  call void %64(i8* %65), !dbg !4421
  store i8* null, i8** %retval, align 8, !dbg !4423
  br label %return, !dbg !4423

if.end102:                                        ; preds = %if.end94
  %66 = load i8*, i8** %newest, align 8, !dbg !4424
  %67 = load i8*, i8** %url_clone, align 8, !dbg !4425
  %68 = load i64, i64* %urllen, align 8, !dbg !4426
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %66, i8* %67, i64 %68, i32 1, i1 false), !dbg !4427
  %69 = load i8*, i8** %useurl, align 8, !dbg !4428
  %arrayidx103 = getelementptr inbounds i8, i8* %69, i64 0, !dbg !4428
  %70 = load i8, i8* %arrayidx103, align 1, !dbg !4428
  %conv104 = sext i8 %70 to i32, !dbg !4428
  %cmp105 = icmp eq i32 47, %conv104, !dbg !4430
  br i1 %cmp105, label %if.then115, label %lor.lhs.false, !dbg !4431

lor.lhs.false:                                    ; preds = %if.end102
  %71 = load i8*, i8** %protsep, align 8, !dbg !4432
  %tobool107 = icmp ne i8* %71, null, !dbg !4432
  br i1 %tobool107, label %land.lhs.true108, label %lor.lhs.false110, !dbg !4434

land.lhs.true108:                                 ; preds = %lor.lhs.false
  %72 = load i8*, i8** %protsep, align 8, !dbg !4435
  %73 = load i8, i8* %72, align 1, !dbg !4437
  %tobool109 = icmp ne i8 %73, 0, !dbg !4437
  br i1 %tobool109, label %lor.lhs.false110, label %if.then115, !dbg !4438

lor.lhs.false110:                                 ; preds = %land.lhs.true108, %lor.lhs.false
  %74 = load i8*, i8** %useurl, align 8, !dbg !4439
  %arrayidx111 = getelementptr inbounds i8, i8* %74, i64 0, !dbg !4439
  %75 = load i8, i8* %arrayidx111, align 1, !dbg !4439
  %conv112 = sext i8 %75 to i32, !dbg !4439
  %cmp113 = icmp eq i32 63, %conv112, !dbg !4441
  br i1 %cmp113, label %if.then115, label %if.else116, !dbg !4442

if.then115:                                       ; preds = %lor.lhs.false110, %land.lhs.true108, %if.end102
  br label %if.end119, !dbg !4443

if.else116:                                       ; preds = %lor.lhs.false110
  %76 = load i64, i64* %urllen, align 8, !dbg !4445
  %inc117 = add i64 %76, 1, !dbg !4445
  store i64 %inc117, i64* %urllen, align 8, !dbg !4445
  %77 = load i8*, i8** %newest, align 8, !dbg !4446
  %arrayidx118 = getelementptr inbounds i8, i8* %77, i64 %76, !dbg !4446
  store i8 47, i8* %arrayidx118, align 1, !dbg !4447
  br label %if.end119

if.end119:                                        ; preds = %if.else116, %if.then115
  %78 = load i64, i64* %urllen, align 8, !dbg !4448
  %79 = load i8*, i8** %newest, align 8, !dbg !4449
  %arrayidx120 = getelementptr inbounds i8, i8* %79, i64 %78, !dbg !4449
  %80 = load i8*, i8** %useurl, align 8, !dbg !4450
  call void @strcpy_url(i8* %arrayidx120, i8* %80), !dbg !4451
  %81 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !4452
  %82 = load i8*, i8** %url_clone, align 8, !dbg !4452
  call void %81(i8* %82), !dbg !4452
  %83 = load i8*, i8** %newest, align 8, !dbg !4453
  store i8* %83, i8** %retval, align 8, !dbg !4454
  br label %return, !dbg !4454

return:                                           ; preds = %if.end119, %if.then101, %if.then
  %84 = load i8*, i8** %retval, align 8, !dbg !4455
  ret i8* %84, !dbg !4455
}

; Function Attrs: nounwind uwtable
define internal i64 @strlen_url(i8* %url) #0 !dbg !1817 {
entry:
  %url.addr = alloca i8*, align 8
  %ptr = alloca i8*, align 8
  %newlen = alloca i64, align 8
  %left = alloca i8, align 1
  store i8* %url, i8** %url.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %url.addr, metadata !4456, metadata !1827), !dbg !4457
  call void @llvm.dbg.declare(metadata i8** %ptr, metadata !4458, metadata !1827), !dbg !4461
  call void @llvm.dbg.declare(metadata i64* %newlen, metadata !4462, metadata !1827), !dbg !4463
  store i64 0, i64* %newlen, align 8, !dbg !4463
  call void @llvm.dbg.declare(metadata i8* %left, metadata !4464, metadata !1827), !dbg !4465
  store i8 1, i8* %left, align 1, !dbg !4465
  %0 = load i8*, i8** %url.addr, align 8, !dbg !4466
  store i8* %0, i8** %ptr, align 8, !dbg !4468
  br label %for.cond, !dbg !4469

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i8*, i8** %ptr, align 8, !dbg !4470
  %2 = load i8, i8* %1, align 1, !dbg !4473
  %tobool = icmp ne i8 %2, 0, !dbg !4474
  br i1 %tobool, label %for.body, label %for.end, !dbg !4474

for.body:                                         ; preds = %for.cond
  %3 = load i8*, i8** %ptr, align 8, !dbg !4475
  %4 = load i8, i8* %3, align 1, !dbg !4477
  %conv = zext i8 %4 to i32, !dbg !4477
  switch i32 %conv, label %sw.default [
    i32 63, label %sw.bb
    i32 32, label %sw.bb3
  ], !dbg !4478

sw.bb:                                            ; preds = %for.body
  store i8 0, i8* %left, align 1, !dbg !4479
  br label %sw.default, !dbg !4481

sw.default:                                       ; preds = %for.body, %sw.bb
  %5 = load i8*, i8** %ptr, align 8, !dbg !4482
  %6 = load i8, i8* %5, align 1, !dbg !4484
  %conv1 = zext i8 %6 to i32, !dbg !4484
  %cmp = icmp sge i32 %conv1, 128, !dbg !4485
  br i1 %cmp, label %if.then, label %if.end, !dbg !4486

if.then:                                          ; preds = %sw.default
  %7 = load i64, i64* %newlen, align 8, !dbg !4487
  %add = add i64 %7, 2, !dbg !4487
  store i64 %add, i64* %newlen, align 8, !dbg !4487
  br label %if.end, !dbg !4488

if.end:                                           ; preds = %if.then, %sw.default
  %8 = load i64, i64* %newlen, align 8, !dbg !4489
  %inc = add i64 %8, 1, !dbg !4489
  store i64 %inc, i64* %newlen, align 8, !dbg !4489
  br label %sw.epilog, !dbg !4490

sw.bb3:                                           ; preds = %for.body
  %9 = load i8, i8* %left, align 1, !dbg !4491
  %tobool4 = trunc i8 %9 to i1, !dbg !4491
  br i1 %tobool4, label %if.then5, label %if.else, !dbg !4493

if.then5:                                         ; preds = %sw.bb3
  %10 = load i64, i64* %newlen, align 8, !dbg !4494
  %add6 = add i64 %10, 3, !dbg !4494
  store i64 %add6, i64* %newlen, align 8, !dbg !4494
  br label %if.end8, !dbg !4495

if.else:                                          ; preds = %sw.bb3
  %11 = load i64, i64* %newlen, align 8, !dbg !4496
  %inc7 = add i64 %11, 1, !dbg !4496
  store i64 %inc7, i64* %newlen, align 8, !dbg !4496
  br label %if.end8

if.end8:                                          ; preds = %if.else, %if.then5
  br label %sw.epilog, !dbg !4497

sw.epilog:                                        ; preds = %if.end8, %if.end
  br label %for.inc, !dbg !4498

for.inc:                                          ; preds = %sw.epilog
  %12 = load i8*, i8** %ptr, align 8, !dbg !4499
  %incdec.ptr = getelementptr inbounds i8, i8* %12, i32 1, !dbg !4499
  store i8* %incdec.ptr, i8** %ptr, align 8, !dbg !4499
  br label %for.cond, !dbg !4501

for.end:                                          ; preds = %for.cond
  %13 = load i64, i64* %newlen, align 8, !dbg !4502
  ret i64 %13, !dbg !4503
}

; Function Attrs: nounwind uwtable
define internal void @strcpy_url(i8* %output, i8* %url) #0 !dbg !1820 {
entry:
  %output.addr = alloca i8*, align 8
  %url.addr = alloca i8*, align 8
  %left = alloca i8, align 1
  %iptr = alloca i8*, align 8
  %optr = alloca i8*, align 8
  store i8* %output, i8** %output.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %output.addr, metadata !4504, metadata !1827), !dbg !4505
  store i8* %url, i8** %url.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %url.addr, metadata !4506, metadata !1827), !dbg !4507
  call void @llvm.dbg.declare(metadata i8* %left, metadata !4508, metadata !1827), !dbg !4509
  store i8 1, i8* %left, align 1, !dbg !4509
  call void @llvm.dbg.declare(metadata i8** %iptr, metadata !4510, metadata !1827), !dbg !4511
  call void @llvm.dbg.declare(metadata i8** %optr, metadata !4512, metadata !1827), !dbg !4513
  %0 = load i8*, i8** %output.addr, align 8, !dbg !4514
  store i8* %0, i8** %optr, align 8, !dbg !4513
  %1 = load i8*, i8** %url.addr, align 8, !dbg !4515
  store i8* %1, i8** %iptr, align 8, !dbg !4517
  br label %for.cond, !dbg !4518

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i8*, i8** %iptr, align 8, !dbg !4519
  %3 = load i8, i8* %2, align 1, !dbg !4521
  %tobool = icmp ne i8 %3, 0, !dbg !4522
  br i1 %tobool, label %for.body, label %for.end, !dbg !4522

for.body:                                         ; preds = %for.cond
  %4 = load i8*, i8** %iptr, align 8, !dbg !4524
  %5 = load i8, i8* %4, align 1, !dbg !4526
  %conv = zext i8 %5 to i32, !dbg !4526
  switch i32 %conv, label %sw.default [
    i32 63, label %sw.bb
    i32 32, label %sw.bb4
  ], !dbg !4527

sw.bb:                                            ; preds = %for.body
  store i8 0, i8* %left, align 1, !dbg !4528
  br label %sw.default, !dbg !4530

sw.default:                                       ; preds = %for.body, %sw.bb
  %6 = load i8*, i8** %iptr, align 8, !dbg !4531
  %7 = load i8, i8* %6, align 1, !dbg !4533
  %conv1 = zext i8 %7 to i32, !dbg !4533
  %cmp = icmp sge i32 %conv1, 128, !dbg !4534
  br i1 %cmp, label %if.then, label %if.else, !dbg !4535

if.then:                                          ; preds = %sw.default
  %8 = load i8*, i8** %optr, align 8, !dbg !4536
  %9 = load i8*, i8** %iptr, align 8, !dbg !4538
  %10 = load i8, i8* %9, align 1, !dbg !4539
  %conv3 = zext i8 %10 to i32, !dbg !4539
  %call = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %8, i64 4, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.43, i32 0, i32 0), i32 %conv3), !dbg !4540
  %11 = load i8*, i8** %optr, align 8, !dbg !4541
  %add.ptr = getelementptr inbounds i8, i8* %11, i64 3, !dbg !4541
  store i8* %add.ptr, i8** %optr, align 8, !dbg !4541
  br label %if.end, !dbg !4542

if.else:                                          ; preds = %sw.default
  %12 = load i8*, i8** %iptr, align 8, !dbg !4543
  %13 = load i8, i8* %12, align 1, !dbg !4544
  %14 = load i8*, i8** %optr, align 8, !dbg !4545
  %incdec.ptr = getelementptr inbounds i8, i8* %14, i32 1, !dbg !4545
  store i8* %incdec.ptr, i8** %optr, align 8, !dbg !4545
  store i8 %13, i8* %14, align 1, !dbg !4546
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %sw.epilog, !dbg !4547

sw.bb4:                                           ; preds = %for.body
  %15 = load i8, i8* %left, align 1, !dbg !4548
  %tobool5 = trunc i8 %15 to i1, !dbg !4548
  br i1 %tobool5, label %if.then6, label %if.else10, !dbg !4550

if.then6:                                         ; preds = %sw.bb4
  %16 = load i8*, i8** %optr, align 8, !dbg !4551
  %incdec.ptr7 = getelementptr inbounds i8, i8* %16, i32 1, !dbg !4551
  store i8* %incdec.ptr7, i8** %optr, align 8, !dbg !4551
  store i8 37, i8* %16, align 1, !dbg !4553
  %17 = load i8*, i8** %optr, align 8, !dbg !4554
  %incdec.ptr8 = getelementptr inbounds i8, i8* %17, i32 1, !dbg !4554
  store i8* %incdec.ptr8, i8** %optr, align 8, !dbg !4554
  store i8 50, i8* %17, align 1, !dbg !4555
  %18 = load i8*, i8** %optr, align 8, !dbg !4556
  %incdec.ptr9 = getelementptr inbounds i8, i8* %18, i32 1, !dbg !4556
  store i8* %incdec.ptr9, i8** %optr, align 8, !dbg !4556
  store i8 48, i8* %18, align 1, !dbg !4557
  br label %if.end12, !dbg !4558

if.else10:                                        ; preds = %sw.bb4
  %19 = load i8*, i8** %optr, align 8, !dbg !4559
  %incdec.ptr11 = getelementptr inbounds i8, i8* %19, i32 1, !dbg !4559
  store i8* %incdec.ptr11, i8** %optr, align 8, !dbg !4559
  store i8 43, i8* %19, align 1, !dbg !4560
  br label %if.end12

if.end12:                                         ; preds = %if.else10, %if.then6
  br label %sw.epilog, !dbg !4561

sw.epilog:                                        ; preds = %if.end12, %if.end
  br label %for.inc, !dbg !4562

for.inc:                                          ; preds = %sw.epilog
  %20 = load i8*, i8** %iptr, align 8, !dbg !4563
  %incdec.ptr13 = getelementptr inbounds i8, i8* %20, i32 1, !dbg !4563
  store i8* %incdec.ptr13, i8** %iptr, align 8, !dbg !4563
  br label %for.cond, !dbg !4564

for.end:                                          ; preds = %for.cond
  %21 = load i8*, i8** %optr, align 8, !dbg !4566
  store i8 0, i8* %21, align 1, !dbg !4567
  ret void, !dbg !4568
}

declare void @Curl_pgrsTime(%struct.Curl_easy*, i32) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_retry_request(%struct.connectdata* %conn, i8** %url) #0 !dbg !1789 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %url.addr = alloca i8**, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %http = alloca %struct.HTTP*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !4569, metadata !1827), !dbg !4570
  store i8** %url, i8*** %url.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %url.addr, metadata !4571, metadata !1827), !dbg !4572
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !4573, metadata !1827), !dbg !4574
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4575
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !4576
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !4576
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !4574
  %2 = load i8**, i8*** %url.addr, align 8, !dbg !4577
  store i8* null, i8** %2, align 8, !dbg !4578
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4579
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 13, !dbg !4581
  %upload = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 104, !dbg !4582
  %4 = load i8, i8* %upload, align 1, !dbg !4582
  %tobool = trunc i8 %4 to i1, !dbg !4582
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !4583

land.lhs.true:                                    ; preds = %entry
  %5 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4584
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %5, i32 0, i32 47, !dbg !4585
  %6 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !4585
  %protocol = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %6, i32 0, i32 15, !dbg !4586
  %7 = load i32, i32* %protocol, align 8, !dbg !4586
  %and = and i32 %7, 262147, !dbg !4587
  %tobool2 = icmp ne i32 %and, 0, !dbg !4587
  br i1 %tobool2, label %if.end, label %if.then, !dbg !4588

if.then:                                          ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !4590
  br label %return, !dbg !4590

if.end:                                           ; preds = %land.lhs.true, %entry
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4591
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %8, i32 0, i32 12, !dbg !4593
  %bytecount = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 4, !dbg !4594
  %9 = load i64, i64* %bytecount, align 8, !dbg !4594
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4595
  %req3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 12, !dbg !4596
  %headerbytecount = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req3, i32 0, i32 6, !dbg !4597
  %11 = load i64, i64* %headerbytecount, align 8, !dbg !4597
  %add = add nsw i64 %9, %11, !dbg !4598
  %cmp = icmp eq i64 %add, 0, !dbg !4599
  br i1 %cmp, label %land.lhs.true4, label %if.end35, !dbg !4600

land.lhs.true4:                                   ; preds = %if.end
  %12 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4601
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %12, i32 0, i32 43, !dbg !4602
  %reuse = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 1, !dbg !4603
  %13 = load i8, i8* %reuse, align 1, !dbg !4603
  %tobool5 = trunc i8 %13 to i1, !dbg !4603
  br i1 %tobool5, label %land.lhs.true6, label %if.end35, !dbg !4604

land.lhs.true6:                                   ; preds = %land.lhs.true4
  %14 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4605
  %set7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %14, i32 0, i32 13, !dbg !4606
  %opt_no_body = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set7, i32 0, i32 103, !dbg !4607
  %15 = load i8, i8* %opt_no_body, align 8, !dbg !4607
  %tobool8 = trunc i8 %15 to i1, !dbg !4607
  br i1 %tobool8, label %lor.lhs.false, label %land.lhs.true13, !dbg !4608

lor.lhs.false:                                    ; preds = %land.lhs.true6
  %16 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4609
  %handler9 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %16, i32 0, i32 47, !dbg !4611
  %17 = load %struct.Curl_handler*, %struct.Curl_handler** %handler9, align 8, !dbg !4611
  %protocol10 = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %17, i32 0, i32 15, !dbg !4612
  %18 = load i32, i32* %protocol10, align 8, !dbg !4612
  %and11 = and i32 %18, 3, !dbg !4613
  %tobool12 = icmp ne i32 %and11, 0, !dbg !4613
  br i1 %tobool12, label %land.lhs.true13, label %if.end35, !dbg !4614

land.lhs.true13:                                  ; preds = %lor.lhs.false, %land.lhs.true6
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4615
  %set14 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %19, i32 0, i32 13, !dbg !4616
  %rtspreq = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set14, i32 0, i32 134, !dbg !4617
  %20 = load i32, i32* %rtspreq, align 4, !dbg !4617
  %cmp15 = icmp ne i32 %20, 11, !dbg !4618
  br i1 %cmp15, label %if.then16, label %if.end35, !dbg !4619

if.then16:                                        ; preds = %land.lhs.true13
  %21 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4620
  %data17 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %21, i32 0, i32 0, !dbg !4622
  %22 = load %struct.Curl_easy*, %struct.Curl_easy** %data17, align 8, !dbg !4622
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %22, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.25, i32 0, i32 0)), !dbg !4623
  %23 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !4624
  %24 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4624
  %data18 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %24, i32 0, i32 0, !dbg !4624
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data18, align 8, !dbg !4624
  %change = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 14, !dbg !4624
  %url19 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change, i32 0, i32 0, !dbg !4624
  %26 = load i8*, i8** %url19, align 8, !dbg !4624
  %call = call i8* %23(i8* %26), !dbg !4624
  %27 = load i8**, i8*** %url.addr, align 8, !dbg !4625
  store i8* %call, i8** %27, align 8, !dbg !4626
  %28 = load i8**, i8*** %url.addr, align 8, !dbg !4627
  %29 = load i8*, i8** %28, align 8, !dbg !4629
  %tobool20 = icmp ne i8* %29, null, !dbg !4629
  br i1 %tobool20, label %if.end22, label %if.then21, !dbg !4630

if.then21:                                        ; preds = %if.then16
  store i32 27, i32* %retval, align 4, !dbg !4631
  br label %return, !dbg !4631

if.end22:                                         ; preds = %if.then16
  %30 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4632
  call void @Curl_conncontrol(%struct.connectdata* %30, i32 1), !dbg !4632
  %31 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4633
  %bits23 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %31, i32 0, i32 43, !dbg !4634
  %retry = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits23, i32 0, i32 14, !dbg !4635
  store i8 1, i8* %retry, align 1, !dbg !4636
  %32 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4637
  %handler24 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %32, i32 0, i32 47, !dbg !4639
  %33 = load %struct.Curl_handler*, %struct.Curl_handler** %handler24, align 8, !dbg !4639
  %protocol25 = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %33, i32 0, i32 15, !dbg !4640
  %34 = load i32, i32* %protocol25, align 8, !dbg !4640
  %and26 = and i32 %34, 3, !dbg !4641
  %tobool27 = icmp ne i32 %and26, 0, !dbg !4641
  br i1 %tobool27, label %if.then28, label %if.end34, !dbg !4642

if.then28:                                        ; preds = %if.end22
  call void @llvm.dbg.declare(metadata %struct.HTTP** %http, metadata !4643, metadata !1827), !dbg !4645
  %35 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4646
  %req29 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %35, i32 0, i32 12, !dbg !4647
  %protop = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req29, i32 0, i32 43, !dbg !4648
  %36 = load i8*, i8** %protop, align 8, !dbg !4648
  %37 = bitcast i8* %36 to %struct.HTTP*, !dbg !4646
  store %struct.HTTP* %37, %struct.HTTP** %http, align 8, !dbg !4645
  %38 = load %struct.HTTP*, %struct.HTTP** %http, align 8, !dbg !4649
  %writebytecount = getelementptr inbounds %struct.HTTP, %struct.HTTP* %38, i32 0, i32 6, !dbg !4651
  %39 = load i64, i64* %writebytecount, align 8, !dbg !4651
  %tobool30 = icmp ne i64 %39, 0, !dbg !4649
  br i1 %tobool30, label %if.then31, label %if.end33, !dbg !4652

if.then31:                                        ; preds = %if.then28
  %40 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4653
  %call32 = call i32 @Curl_readrewind(%struct.connectdata* %40), !dbg !4654
  store i32 %call32, i32* %retval, align 4, !dbg !4655
  br label %return, !dbg !4655

if.end33:                                         ; preds = %if.then28
  br label %if.end34, !dbg !4656

if.end34:                                         ; preds = %if.end33, %if.end22
  br label %if.end35, !dbg !4657

if.end35:                                         ; preds = %if.end34, %land.lhs.true13, %lor.lhs.false, %land.lhs.true4, %if.end
  store i32 0, i32* %retval, align 4, !dbg !4658
  br label %return, !dbg !4658

return:                                           ; preds = %if.end35, %if.then31, %if.then21, %if.then
  %41 = load i32, i32* %retval, align 4, !dbg !4659
  ret i32 %41, !dbg !4659
}

declare void @Curl_conncontrol(%struct.connectdata*, i32) #2

; Function Attrs: nounwind uwtable
define void @Curl_setup_transfer(%struct.connectdata* %conn, i32 %sockindex, i64 %size, i1 zeroext %getheader, i64* %bytecountp, i32 %writesockindex, i64* %writecountp) #0 !dbg !1792 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockindex.addr = alloca i32, align 4
  %size.addr = alloca i64, align 8
  %getheader.addr = alloca i8, align 1
  %bytecountp.addr = alloca i64*, align 8
  %writesockindex.addr = alloca i32, align 4
  %writecountp.addr = alloca i64*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %k = alloca %struct.SingleRequest*, align 8
  %http = alloca %struct.HTTP*, align 8
  %coerce = alloca %struct.timeval, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !4660, metadata !1827), !dbg !4661
  store i32 %sockindex, i32* %sockindex.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockindex.addr, metadata !4662, metadata !1827), !dbg !4663
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !4664, metadata !1827), !dbg !4665
  %frombool = zext i1 %getheader to i8
  store i8 %frombool, i8* %getheader.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %getheader.addr, metadata !4666, metadata !1827), !dbg !4667
  store i64* %bytecountp, i64** %bytecountp.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %bytecountp.addr, metadata !4668, metadata !1827), !dbg !4669
  store i32 %writesockindex, i32* %writesockindex.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %writesockindex.addr, metadata !4670, metadata !1827), !dbg !4671
  store i64* %writecountp, i64** %writecountp.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %writecountp.addr, metadata !4672, metadata !1827), !dbg !4673
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !4674, metadata !1827), !dbg !4675
  call void @llvm.dbg.declare(metadata %struct.SingleRequest** %k, metadata !4676, metadata !1827), !dbg !4677
  br label %do.body, !dbg !4678

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !4679

do.end:                                           ; preds = %do.body
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4682
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !4683
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !4683
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !4684
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4685
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 12, !dbg !4686
  store %struct.SingleRequest* %req, %struct.SingleRequest** %k, align 8, !dbg !4687
  br label %do.body2, !dbg !4688

do.body2:                                         ; preds = %do.end
  br label %do.end3, !dbg !4689

do.end3:                                          ; preds = %do.body2
  %3 = load i32, i32* %sockindex.addr, align 4, !dbg !4692
  %cmp = icmp eq i32 %3, -1, !dbg !4693
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !4692

cond.true:                                        ; preds = %do.end3
  br label %cond.end, !dbg !4694

cond.false:                                       ; preds = %do.end3
  %4 = load i32, i32* %sockindex.addr, align 4, !dbg !4696
  %idxprom = sext i32 %4 to i64, !dbg !4697
  %5 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4697
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %5, i32 0, i32 33, !dbg !4698
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 %idxprom, !dbg !4697
  %6 = load i32, i32* %arrayidx, align 4, !dbg !4697
  br label %cond.end, !dbg !4699

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ -1, %cond.true ], [ %6, %cond.false ], !dbg !4701
  %7 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4703
  %sockfd = getelementptr inbounds %struct.connectdata, %struct.connectdata* %7, i32 0, i32 50, !dbg !4704
  store i32 %cond, i32* %sockfd, align 8, !dbg !4705
  %8 = load i32, i32* %writesockindex.addr, align 4, !dbg !4706
  %cmp4 = icmp eq i32 %8, -1, !dbg !4707
  br i1 %cmp4, label %cond.true5, label %cond.false6, !dbg !4706

cond.true5:                                       ; preds = %cond.end
  br label %cond.end10, !dbg !4708

cond.false6:                                      ; preds = %cond.end
  %9 = load i32, i32* %writesockindex.addr, align 4, !dbg !4709
  %idxprom7 = sext i32 %9 to i64, !dbg !4710
  %10 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4710
  %sock8 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %10, i32 0, i32 33, !dbg !4711
  %arrayidx9 = getelementptr inbounds [2 x i32], [2 x i32]* %sock8, i64 0, i64 %idxprom7, !dbg !4710
  %11 = load i32, i32* %arrayidx9, align 4, !dbg !4710
  br label %cond.end10, !dbg !4712

cond.end10:                                       ; preds = %cond.false6, %cond.true5
  %cond11 = phi i32 [ -1, %cond.true5 ], [ %11, %cond.false6 ], !dbg !4713
  %12 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4714
  %writesockfd = getelementptr inbounds %struct.connectdata, %struct.connectdata* %12, i32 0, i32 51, !dbg !4715
  store i32 %cond11, i32* %writesockfd, align 4, !dbg !4716
  %13 = load i8, i8* %getheader.addr, align 1, !dbg !4717
  %tobool = trunc i8 %13 to i1, !dbg !4717
  %14 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4718
  %getheader12 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %14, i32 0, i32 41, !dbg !4719
  %frombool13 = zext i1 %tobool to i8, !dbg !4720
  store i8 %frombool13, i8* %getheader12, align 2, !dbg !4720
  %15 = load i64, i64* %size.addr, align 8, !dbg !4721
  %16 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4722
  %size14 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %16, i32 0, i32 0, !dbg !4723
  store i64 %15, i64* %size14, align 8, !dbg !4724
  %17 = load i64*, i64** %bytecountp.addr, align 8, !dbg !4725
  %18 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4726
  %bytecountp15 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %18, i32 0, i32 1, !dbg !4727
  store i64* %17, i64** %bytecountp15, align 8, !dbg !4728
  %19 = load i64*, i64** %writecountp.addr, align 8, !dbg !4729
  %20 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4730
  %writebytecountp = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %20, i32 0, i32 3, !dbg !4731
  store i64* %19, i64** %writebytecountp, align 8, !dbg !4732
  %21 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4733
  %getheader16 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %21, i32 0, i32 41, !dbg !4735
  %22 = load i8, i8* %getheader16, align 2, !dbg !4735
  %tobool17 = trunc i8 %22 to i1, !dbg !4735
  br i1 %tobool17, label %if.end20, label %if.then, !dbg !4736

if.then:                                          ; preds = %cond.end10
  %23 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4737
  %header = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %23, i32 0, i32 10, !dbg !4739
  store i8 0, i8* %header, align 8, !dbg !4740
  %24 = load i64, i64* %size.addr, align 8, !dbg !4741
  %cmp18 = icmp sgt i64 %24, 0, !dbg !4743
  br i1 %cmp18, label %if.then19, label %if.end, !dbg !4744

if.then19:                                        ; preds = %if.then
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4745
  %26 = load i64, i64* %size.addr, align 8, !dbg !4746
  call void @Curl_pgrsSetDownloadSize(%struct.Curl_easy* %25, i64 %26), !dbg !4747
  br label %if.end, !dbg !4747

if.end:                                           ; preds = %if.then19, %if.then
  br label %if.end20, !dbg !4748

if.end20:                                         ; preds = %if.end, %cond.end10
  %27 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4749
  %getheader21 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %27, i32 0, i32 41, !dbg !4751
  %28 = load i8, i8* %getheader21, align 2, !dbg !4751
  %tobool22 = trunc i8 %28 to i1, !dbg !4751
  br i1 %tobool22, label %if.then24, label %lor.lhs.false, !dbg !4752

lor.lhs.false:                                    ; preds = %if.end20
  %29 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4753
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %29, i32 0, i32 13, !dbg !4755
  %opt_no_body = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 103, !dbg !4756
  %30 = load i8, i8* %opt_no_body, align 8, !dbg !4756
  %tobool23 = trunc i8 %30 to i1, !dbg !4756
  br i1 %tobool23, label %if.end49, label %if.then24, !dbg !4757

if.then24:                                        ; preds = %lor.lhs.false, %if.end20
  %31 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4758
  %sockfd25 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %31, i32 0, i32 50, !dbg !4761
  %32 = load i32, i32* %sockfd25, align 8, !dbg !4761
  %cmp26 = icmp ne i32 %32, -1, !dbg !4762
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !4763

if.then27:                                        ; preds = %if.then24
  %33 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4764
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %33, i32 0, i32 31, !dbg !4765
  %34 = load i32, i32* %keepon, align 4, !dbg !4766
  %or = or i32 %34, 1, !dbg !4766
  store i32 %or, i32* %keepon, align 4, !dbg !4766
  br label %if.end28, !dbg !4764

if.end28:                                         ; preds = %if.then27, %if.then24
  %35 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4767
  %writesockfd29 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %35, i32 0, i32 51, !dbg !4769
  %36 = load i32, i32* %writesockfd29, align 4, !dbg !4769
  %cmp30 = icmp ne i32 %36, -1, !dbg !4770
  br i1 %cmp30, label %if.then31, label %if.end48, !dbg !4771

if.then31:                                        ; preds = %if.end28
  call void @llvm.dbg.declare(metadata %struct.HTTP** %http, metadata !4772, metadata !1827), !dbg !4774
  %37 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4775
  %req32 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %37, i32 0, i32 12, !dbg !4776
  %protop = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req32, i32 0, i32 43, !dbg !4777
  %38 = load i8*, i8** %protop, align 8, !dbg !4777
  %39 = bitcast i8* %38 to %struct.HTTP*, !dbg !4775
  store %struct.HTTP* %39, %struct.HTTP** %http, align 8, !dbg !4774
  %40 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4778
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %40, i32 0, i32 17, !dbg !4780
  %expect100header = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 33, !dbg !4781
  %41 = load i8, i8* %expect100header, align 8, !dbg !4781
  %tobool33 = trunc i8 %41 to i1, !dbg !4781
  br i1 %tobool33, label %land.lhs.true, label %if.else, !dbg !4782

land.lhs.true:                                    ; preds = %if.then31
  %42 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4783
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %42, i32 0, i32 47, !dbg !4784
  %43 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !4784
  %protocol = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %43, i32 0, i32 15, !dbg !4785
  %44 = load i32, i32* %protocol, align 8, !dbg !4785
  %and = and i32 %44, 3, !dbg !4786
  %tobool34 = icmp ne i32 %and, 0, !dbg !4786
  br i1 %tobool34, label %land.lhs.true35, label %if.else, !dbg !4787

land.lhs.true35:                                  ; preds = %land.lhs.true
  %45 = load %struct.HTTP*, %struct.HTTP** %http, align 8, !dbg !4788
  %sending = getelementptr inbounds %struct.HTTP, %struct.HTTP* %45, i32 0, i32 9, !dbg !4789
  %46 = load i32, i32* %sending, align 8, !dbg !4789
  %cmp36 = icmp eq i32 %46, 2, !dbg !4790
  br i1 %cmp36, label %if.then37, label %if.else, !dbg !4791

if.then37:                                        ; preds = %land.lhs.true35
  %47 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4793
  %exp100 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %47, i32 0, i32 23, !dbg !4795
  store i32 1, i32* %exp100, align 8, !dbg !4796
  %48 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4797
  %start100 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %48, i32 0, i32 22, !dbg !4798
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !4799
  %49 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !4799
  %50 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %49, i32 0, i32 0, !dbg !4799
  %51 = extractvalue { i64, i64 } %call, 0, !dbg !4799
  store i64 %51, i64* %50, align 8, !dbg !4799
  %52 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %49, i32 0, i32 1, !dbg !4799
  %53 = extractvalue { i64, i64 } %call, 1, !dbg !4799
  store i64 %53, i64* %52, align 8, !dbg !4799
  %54 = bitcast %struct.timeval* %start100 to i8*, !dbg !4799
  %55 = bitcast %struct.timeval* %coerce to i8*, !dbg !4799
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %54, i8* %55, i64 16, i32 8, i1 false), !dbg !4800
  %56 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4802
  %57 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4803
  %set38 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %57, i32 0, i32 13, !dbg !4804
  %expect_100_timeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set38, i32 0, i32 151, !dbg !4805
  %58 = load i64, i64* %expect_100_timeout, align 8, !dbg !4805
  call void @Curl_expire(%struct.Curl_easy* %56, i64 %58), !dbg !4806
  br label %if.end47, !dbg !4807

if.else:                                          ; preds = %land.lhs.true35, %land.lhs.true, %if.then31
  %59 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !4808
  %state39 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %59, i32 0, i32 17, !dbg !4811
  %expect100header40 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state39, i32 0, i32 33, !dbg !4812
  %60 = load i8, i8* %expect100header40, align 8, !dbg !4812
  %tobool41 = trunc i8 %60 to i1, !dbg !4812
  br i1 %tobool41, label %if.then42, label %if.end44, !dbg !4813

if.then42:                                        ; preds = %if.else
  %61 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4814
  %exp10043 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %61, i32 0, i32 23, !dbg !4815
  store i32 2, i32* %exp10043, align 8, !dbg !4816
  br label %if.end44, !dbg !4814

if.end44:                                         ; preds = %if.then42, %if.else
  %62 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !4817
  %keepon45 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %62, i32 0, i32 31, !dbg !4818
  %63 = load i32, i32* %keepon45, align 4, !dbg !4819
  %or46 = or i32 %63, 2, !dbg !4819
  store i32 %or46, i32* %keepon45, align 4, !dbg !4819
  br label %if.end47

if.end47:                                         ; preds = %if.end44, %if.then37
  br label %if.end48, !dbg !4820

if.end48:                                         ; preds = %if.end47, %if.end28
  br label %if.end49, !dbg !4821

if.end49:                                         ; preds = %if.end48, %lor.lhs.false
  ret void, !dbg !4822
}

declare void @Curl_pgrsSetDownloadSize(%struct.Curl_easy*, i64) #2

declare i32 @Curl_read(%struct.connectdata*, i32, i8*, i64, i64*) #2

declare i32 @Curl_http_readwrite_headers(%struct.Curl_easy*, %struct.connectdata*, i64*, i8*) #2

declare zeroext i1 @Curl_pipeline_wanted(%struct.Curl_multi*, i32) #2

; Function Attrs: nounwind uwtable
define internal void @read_rewind(%struct.connectdata* %conn, i64 %thismuch) #0 !dbg !1799 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %thismuch.addr = alloca i64, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !4823, metadata !1827), !dbg !4824
  store i64 %thismuch, i64* %thismuch.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %thismuch.addr, metadata !4825, metadata !1827), !dbg !4826
  br label %do.body, !dbg !4827

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !4828

do.end:                                           ; preds = %do.body
  %0 = load i64, i64* %thismuch.addr, align 8, !dbg !4831
  %1 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4832
  %read_pos = getelementptr inbounds %struct.connectdata, %struct.connectdata* %1, i32 0, i32 58, !dbg !4833
  %2 = load i64, i64* %read_pos, align 8, !dbg !4834
  %sub = sub i64 %2, %0, !dbg !4834
  store i64 %sub, i64* %read_pos, align 8, !dbg !4834
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4835
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %3, i32 0, i32 43, !dbg !4836
  %stream_was_rewound = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 23, !dbg !4837
  store i8 1, i8* %stream_was_rewound, align 1, !dbg !4838
  ret void, !dbg !4839
}

declare i32 @Curl_debug(%struct.Curl_easy*, i32, i8*, i64, %struct.connectdata*) #2

declare i32 @Curl_httpchunk_read(%struct.connectdata*, i8*, i64, i64*) #2

declare i8* @Curl_chunked_strerror(i32) #2

declare void @Curl_pgrsSetDownloadCounter(%struct.Curl_easy*, i64) #2

declare i32 @Curl_client_write(%struct.connectdata*, i32, i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @data_pending(%struct.connectdata* %conn) #0 !dbg !1802 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !4840, metadata !1827), !dbg !4841
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4842
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 47, !dbg !4843
  %1 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !4843
  %protocol = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %1, i32 0, i32 15, !dbg !4844
  %2 = load i32, i32* %protocol, align 8, !dbg !4844
  %and = and i32 %2, 48, !dbg !4845
  %tobool = icmp ne i32 %and, 0, !dbg !4845
  br i1 %tobool, label %lor.end, label %lor.rhs, !dbg !4846

lor.rhs:                                          ; preds = %entry
  br label %lor.end, !dbg !4847

lor.end:                                          ; preds = %lor.rhs, %entry
  %3 = phi i1 [ true, %entry ], [ false, %lor.rhs ]
  %lor.ext = zext i1 %3 to i32, !dbg !4849
  ret i32 %lor.ext, !dbg !4851
}

; Function Attrs: nounwind uwtable
define internal i32 @done_sending(%struct.connectdata* %conn, %struct.SingleRequest* %k) #0 !dbg !1808 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %k.addr = alloca %struct.SingleRequest*, align 8
  %result = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !4852, metadata !1827), !dbg !4853
  store %struct.SingleRequest* %k, %struct.SingleRequest** %k.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.SingleRequest** %k.addr, metadata !4854, metadata !1827), !dbg !4855
  %0 = load %struct.SingleRequest*, %struct.SingleRequest** %k.addr, align 8, !dbg !4856
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %0, i32 0, i32 31, !dbg !4857
  %1 = load i32, i32* %keepon, align 4, !dbg !4858
  %and = and i32 %1, -3, !dbg !4858
  store i32 %and, i32* %keepon, align 4, !dbg !4858
  %2 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4859
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 43, !dbg !4861
  %rewindaftersend = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 17, !dbg !4862
  %3 = load i8, i8* %rewindaftersend, align 1, !dbg !4862
  %tobool = trunc i8 %3 to i1, !dbg !4862
  br i1 %tobool, label %if.then, label %if.end3, !dbg !4863

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %result, metadata !4864, metadata !1827), !dbg !4866
  %4 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !4867
  %call = call i32 @Curl_readrewind(%struct.connectdata* %4), !dbg !4868
  store i32 %call, i32* %result, align 4, !dbg !4866
  %5 = load i32, i32* %result, align 4, !dbg !4869
  %tobool1 = icmp ne i32 %5, 0, !dbg !4869
  br i1 %tobool1, label %if.then2, label %if.end, !dbg !4871

if.then2:                                         ; preds = %if.then
  %6 = load i32, i32* %result, align 4, !dbg !4872
  store i32 %6, i32* %retval, align 4, !dbg !4873
  br label %return, !dbg !4873

if.end:                                           ; preds = %if.then
  br label %if.end3, !dbg !4874

if.end3:                                          ; preds = %if.end, %entry
  store i32 0, i32* %retval, align 4, !dbg !4875
  br label %return, !dbg !4875

return:                                           ; preds = %if.end3, %if.then2
  %7 = load i32, i32* %retval, align 4, !dbg !4876
  ret i32 %7, !dbg !4876
}

declare i32 @Curl_write(%struct.connectdata*, i32, i8*, i64, i64*) #2

declare void @Curl_pgrsSetUploadCounter(%struct.Curl_easy*, i64) #2

; Function Attrs: nounwind
declare i32 @__isoc99_sscanf(i8*, i8*, ...) #5

; Function Attrs: nounwind readonly
declare i8* @strstr(i8*, i8*) #4

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #4

; Function Attrs: nounwind readonly
declare i8* @strrchr(i8*, i32) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly }
attributes #7 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!1823, !1824}
!llvm.ident = !{!1825}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !1763, subprograms: !1765)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/transfer.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !100, !123, !129, !185, !227, !234, !269, !279, !285, !290, !297, !307, !316, !322, !328, !334, !340, !347, !353, !359, !374, !385, !399, !410, !415, !423, !461, !480, !500, !515, !532, !540, !1678, !1683, !1691, !1706, !1714, !1752}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 434, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99}
!6 = !DIEnumerator(name: "CURLE_OK", value: 0)
!7 = !DIEnumerator(name: "CURLE_UNSUPPORTED_PROTOCOL", value: 1)
!8 = !DIEnumerator(name: "CURLE_FAILED_INIT", value: 2)
!9 = !DIEnumerator(name: "CURLE_URL_MALFORMAT", value: 3)
!10 = !DIEnumerator(name: "CURLE_NOT_BUILT_IN", value: 4)
!11 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_PROXY", value: 5)
!12 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_HOST", value: 6)
!13 = !DIEnumerator(name: "CURLE_COULDNT_CONNECT", value: 7)
!14 = !DIEnumerator(name: "CURLE_WEIRD_SERVER_REPLY", value: 8)
!15 = !DIEnumerator(name: "CURLE_REMOTE_ACCESS_DENIED", value: 9)
!16 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_FAILED", value: 10)
!17 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASS_REPLY", value: 11)
!18 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_TIMEOUT", value: 12)
!19 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASV_REPLY", value: 13)
!20 = !DIEnumerator(name: "CURLE_FTP_WEIRD_227_FORMAT", value: 14)
!21 = !DIEnumerator(name: "CURLE_FTP_CANT_GET_HOST", value: 15)
!22 = !DIEnumerator(name: "CURLE_HTTP2", value: 16)
!23 = !DIEnumerator(name: "CURLE_FTP_COULDNT_SET_TYPE", value: 17)
!24 = !DIEnumerator(name: "CURLE_PARTIAL_FILE", value: 18)
!25 = !DIEnumerator(name: "CURLE_FTP_COULDNT_RETR_FILE", value: 19)
!26 = !DIEnumerator(name: "CURLE_OBSOLETE20", value: 20)
!27 = !DIEnumerator(name: "CURLE_QUOTE_ERROR", value: 21)
!28 = !DIEnumerator(name: "CURLE_HTTP_RETURNED_ERROR", value: 22)
!29 = !DIEnumerator(name: "CURLE_WRITE_ERROR", value: 23)
!30 = !DIEnumerator(name: "CURLE_OBSOLETE24", value: 24)
!31 = !DIEnumerator(name: "CURLE_UPLOAD_FAILED", value: 25)
!32 = !DIEnumerator(name: "CURLE_READ_ERROR", value: 26)
!33 = !DIEnumerator(name: "CURLE_OUT_OF_MEMORY", value: 27)
!34 = !DIEnumerator(name: "CURLE_OPERATION_TIMEDOUT", value: 28)
!35 = !DIEnumerator(name: "CURLE_OBSOLETE29", value: 29)
!36 = !DIEnumerator(name: "CURLE_FTP_PORT_FAILED", value: 30)
!37 = !DIEnumerator(name: "CURLE_FTP_COULDNT_USE_REST", value: 31)
!38 = !DIEnumerator(name: "CURLE_OBSOLETE32", value: 32)
!39 = !DIEnumerator(name: "CURLE_RANGE_ERROR", value: 33)
!40 = !DIEnumerator(name: "CURLE_HTTP_POST_ERROR", value: 34)
!41 = !DIEnumerator(name: "CURLE_SSL_CONNECT_ERROR", value: 35)
!42 = !DIEnumerator(name: "CURLE_BAD_DOWNLOAD_RESUME", value: 36)
!43 = !DIEnumerator(name: "CURLE_FILE_COULDNT_READ_FILE", value: 37)
!44 = !DIEnumerator(name: "CURLE_LDAP_CANNOT_BIND", value: 38)
!45 = !DIEnumerator(name: "CURLE_LDAP_SEARCH_FAILED", value: 39)
!46 = !DIEnumerator(name: "CURLE_OBSOLETE40", value: 40)
!47 = !DIEnumerator(name: "CURLE_FUNCTION_NOT_FOUND", value: 41)
!48 = !DIEnumerator(name: "CURLE_ABORTED_BY_CALLBACK", value: 42)
!49 = !DIEnumerator(name: "CURLE_BAD_FUNCTION_ARGUMENT", value: 43)
!50 = !DIEnumerator(name: "CURLE_OBSOLETE44", value: 44)
!51 = !DIEnumerator(name: "CURLE_INTERFACE_FAILED", value: 45)
!52 = !DIEnumerator(name: "CURLE_OBSOLETE46", value: 46)
!53 = !DIEnumerator(name: "CURLE_TOO_MANY_REDIRECTS", value: 47)
!54 = !DIEnumerator(name: "CURLE_UNKNOWN_OPTION", value: 48)
!55 = !DIEnumerator(name: "CURLE_TELNET_OPTION_SYNTAX", value: 49)
!56 = !DIEnumerator(name: "CURLE_OBSOLETE50", value: 50)
!57 = !DIEnumerator(name: "CURLE_PEER_FAILED_VERIFICATION", value: 51)
!58 = !DIEnumerator(name: "CURLE_GOT_NOTHING", value: 52)
!59 = !DIEnumerator(name: "CURLE_SSL_ENGINE_NOTFOUND", value: 53)
!60 = !DIEnumerator(name: "CURLE_SSL_ENGINE_SETFAILED", value: 54)
!61 = !DIEnumerator(name: "CURLE_SEND_ERROR", value: 55)
!62 = !DIEnumerator(name: "CURLE_RECV_ERROR", value: 56)
!63 = !DIEnumerator(name: "CURLE_OBSOLETE57", value: 57)
!64 = !DIEnumerator(name: "CURLE_SSL_CERTPROBLEM", value: 58)
!65 = !DIEnumerator(name: "CURLE_SSL_CIPHER", value: 59)
!66 = !DIEnumerator(name: "CURLE_SSL_CACERT", value: 60)
!67 = !DIEnumerator(name: "CURLE_BAD_CONTENT_ENCODING", value: 61)
!68 = !DIEnumerator(name: "CURLE_LDAP_INVALID_URL", value: 62)
!69 = !DIEnumerator(name: "CURLE_FILESIZE_EXCEEDED", value: 63)
!70 = !DIEnumerator(name: "CURLE_USE_SSL_FAILED", value: 64)
!71 = !DIEnumerator(name: "CURLE_SEND_FAIL_REWIND", value: 65)
!72 = !DIEnumerator(name: "CURLE_SSL_ENGINE_INITFAILED", value: 66)
!73 = !DIEnumerator(name: "CURLE_LOGIN_DENIED", value: 67)
!74 = !DIEnumerator(name: "CURLE_TFTP_NOTFOUND", value: 68)
!75 = !DIEnumerator(name: "CURLE_TFTP_PERM", value: 69)
!76 = !DIEnumerator(name: "CURLE_REMOTE_DISK_FULL", value: 70)
!77 = !DIEnumerator(name: "CURLE_TFTP_ILLEGAL", value: 71)
!78 = !DIEnumerator(name: "CURLE_TFTP_UNKNOWNID", value: 72)
!79 = !DIEnumerator(name: "CURLE_REMOTE_FILE_EXISTS", value: 73)
!80 = !DIEnumerator(name: "CURLE_TFTP_NOSUCHUSER", value: 74)
!81 = !DIEnumerator(name: "CURLE_CONV_FAILED", value: 75)
!82 = !DIEnumerator(name: "CURLE_CONV_REQD", value: 76)
!83 = !DIEnumerator(name: "CURLE_SSL_CACERT_BADFILE", value: 77)
!84 = !DIEnumerator(name: "CURLE_REMOTE_FILE_NOT_FOUND", value: 78)
!85 = !DIEnumerator(name: "CURLE_SSH", value: 79)
!86 = !DIEnumerator(name: "CURLE_SSL_SHUTDOWN_FAILED", value: 80)
!87 = !DIEnumerator(name: "CURLE_AGAIN", value: 81)
!88 = !DIEnumerator(name: "CURLE_SSL_CRL_BADFILE", value: 82)
!89 = !DIEnumerator(name: "CURLE_SSL_ISSUER_ERROR", value: 83)
!90 = !DIEnumerator(name: "CURLE_FTP_PRET_FAILED", value: 84)
!91 = !DIEnumerator(name: "CURLE_RTSP_CSEQ_ERROR", value: 85)
!92 = !DIEnumerator(name: "CURLE_RTSP_SESSION_ERROR", value: 86)
!93 = !DIEnumerator(name: "CURLE_FTP_BAD_FILE_LIST", value: 87)
!94 = !DIEnumerator(name: "CURLE_CHUNK_FAILED", value: 88)
!95 = !DIEnumerator(name: "CURLE_NO_CONNECTION_AVAILABLE", value: 89)
!96 = !DIEnumerator(name: "CURLE_SSL_PINNEDPUBKEYNOTMATCH", value: 90)
!97 = !DIEnumerator(name: "CURLE_SSL_INVALIDCERTSTATUS", value: 91)
!98 = !DIEnumerator(name: "CURLE_HTTP2_STREAM", value: 92)
!99 = !DIEnumerator(name: "CURL_LAST", value: 93)
!100 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !101, line: 35, size: 32, align: 32, elements: !102)
!101 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/multihandle.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!102 = !{!103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122}
!103 = !DIEnumerator(name: "CURLM_STATE_INIT", value: 0)
!104 = !DIEnumerator(name: "CURLM_STATE_CONNECT_PEND", value: 1)
!105 = !DIEnumerator(name: "CURLM_STATE_CONNECT", value: 2)
!106 = !DIEnumerator(name: "CURLM_STATE_WAITRESOLVE", value: 3)
!107 = !DIEnumerator(name: "CURLM_STATE_WAITCONNECT", value: 4)
!108 = !DIEnumerator(name: "CURLM_STATE_WAITPROXYCONNECT", value: 5)
!109 = !DIEnumerator(name: "CURLM_STATE_SENDPROTOCONNECT", value: 6)
!110 = !DIEnumerator(name: "CURLM_STATE_PROTOCONNECT", value: 7)
!111 = !DIEnumerator(name: "CURLM_STATE_WAITDO", value: 8)
!112 = !DIEnumerator(name: "CURLM_STATE_DO", value: 9)
!113 = !DIEnumerator(name: "CURLM_STATE_DOING", value: 10)
!114 = !DIEnumerator(name: "CURLM_STATE_DO_MORE", value: 11)
!115 = !DIEnumerator(name: "CURLM_STATE_DO_DONE", value: 12)
!116 = !DIEnumerator(name: "CURLM_STATE_WAITPERFORM", value: 13)
!117 = !DIEnumerator(name: "CURLM_STATE_PERFORM", value: 14)
!118 = !DIEnumerator(name: "CURLM_STATE_TOOFAST", value: 15)
!119 = !DIEnumerator(name: "CURLM_STATE_DONE", value: 16)
!120 = !DIEnumerator(name: "CURLM_STATE_COMPLETED", value: 17)
!121 = !DIEnumerator(name: "CURLM_STATE_MSGSENT", value: 18)
!122 = !DIEnumerator(name: "CURLM_STATE_LAST", value: 19)
!123 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !124, line: 86, size: 32, align: 32, elements: !125)
!124 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/multi.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!125 = !{!126, !127, !128}
!126 = !DIEnumerator(name: "CURLMSG_NONE", value: 0)
!127 = !DIEnumerator(name: "CURLMSG_DONE", value: 1)
!128 = !DIEnumerator(name: "CURLMSG_LAST", value: 2)
!129 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !131, file: !130, line: 1783, size: 32, align: 32, elements: !180)
!130 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/urldata.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!131 = !DICompositeType(tag: DW_TAG_structure_type, name: "Names", file: !130, line: 1781, size: 128, align: 64, elements: !132)
!132 = !{!133, !179}
!133 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !131, file: !130, line: 1782, baseType: !134, size: 64, align: 64)
!134 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !135, size: 64, align: 64)
!135 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_hash", file: !136, line: 46, size: 384, align: 64, elements: !137)
!136 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hash.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!137 = !{!138, !161, !166, !171, !176, !178}
!138 = !DIDerivedType(tag: DW_TAG_member, name: "table", scope: !135, file: !136, line: 47, baseType: !139, size: 64, align: 64)
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !140, size: 64, align: 64)
!140 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist", file: !141, line: 37, size: 256, align: 64, elements: !142)
!141 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/llist.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!142 = !{!143, !151, !152, !157}
!143 = !DIDerivedType(tag: DW_TAG_member, name: "head", scope: !140, file: !141, line: 38, baseType: !144, size: 64, align: 64)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist_element", file: !141, line: 30, size: 192, align: 64, elements: !146)
!146 = !{!147, !149, !150}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !145, file: !141, line: 31, baseType: !148, size: 64, align: 64)
!148 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !145, file: !141, line: 33, baseType: !144, size: 64, align: 64, offset: 64)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !145, file: !141, line: 34, baseType: !144, size: 64, align: 64, offset: 128)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "tail", scope: !140, file: !141, line: 39, baseType: !144, size: 64, align: 64, offset: 64)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !140, file: !141, line: 41, baseType: !153, size: 64, align: 64, offset: 128)
!153 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_llist_dtor", file: !141, line: 28, baseType: !154)
!154 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !155, size: 64, align: 64)
!155 = !DISubroutineType(types: !156)
!156 = !{null, !148, !148}
!157 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !140, file: !141, line: 43, baseType: !158, size: 64, align: 64, offset: 192)
!158 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !159, line: 62, baseType: !160)
!159 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!160 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "hash_func", scope: !135, file: !136, line: 50, baseType: !162, size: 64, align: 64, offset: 64)
!162 = !DIDerivedType(tag: DW_TAG_typedef, name: "hash_function", file: !136, line: 32, baseType: !163)
!163 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !164, size: 64, align: 64)
!164 = !DISubroutineType(types: !165)
!165 = !{!158, !148, !158, !158}
!166 = !DIDerivedType(tag: DW_TAG_member, name: "comp_func", scope: !135, file: !136, line: 53, baseType: !167, size: 64, align: 64, offset: 128)
!167 = !DIDerivedType(tag: DW_TAG_typedef, name: "comp_function", file: !136, line: 39, baseType: !168)
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !169, size: 64, align: 64)
!169 = !DISubroutineType(types: !170)
!170 = !{!158, !148, !158, !148, !158}
!171 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !135, file: !136, line: 54, baseType: !172, size: 64, align: 64, offset: 192)
!172 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_hash_dtor", file: !136, line: 44, baseType: !173)
!173 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !174, size: 64, align: 64)
!174 = !DISubroutineType(types: !175)
!175 = !{null, !148}
!176 = !DIDerivedType(tag: DW_TAG_member, name: "slots", scope: !135, file: !136, line: 55, baseType: !177, size: 32, align: 32, offset: 256)
!177 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !135, file: !136, line: 56, baseType: !158, size: 64, align: 64, offset: 320)
!179 = !DIDerivedType(tag: DW_TAG_member, name: "hostcachetype", scope: !131, file: !130, line: 1788, baseType: !129, size: 32, align: 32, offset: 64)
!180 = !{!181, !182, !183, !184}
!181 = !DIEnumerator(name: "HCACHE_NONE", value: 0)
!182 = !DIEnumerator(name: "HCACHE_GLOBAL", value: 1)
!183 = !DIEnumerator(name: "HCACHE_MULTI", value: 2)
!184 = !DIEnumerator(name: "HCACHE_SHARED", value: 3)
!185 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !186, file: !130, line: 679, size: 32, align: 32, elements: !265)
!186 = !DICompositeType(tag: DW_TAG_structure_type, name: "SingleRequest", file: !130, line: 658, size: 2496, align: 64, elements: !187)
!187 = !{!188, !192, !194, !195, !196, !197, !198, !199, !200, !209, !210, !212, !213, !214, !217, !218, !219, !220, !221, !222, !223, !224, !225, !226, !233, !240, !241, !244, !245, !246, !247, !249, !250, !251, !252, !253, !254, !255, !259, !260, !261, !262, !263, !264}
!188 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !186, file: !130, line: 659, baseType: !189, size: 64, align: 64)
!189 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_off_t", file: !190, line: 216, baseType: !191)
!190 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curlbuild.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!191 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "bytecountp", scope: !186, file: !130, line: 660, baseType: !193, size: 64, align: 64, offset: 64)
!193 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "maxdownload", scope: !186, file: !130, line: 662, baseType: !189, size: 64, align: 64, offset: 128)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecountp", scope: !186, file: !130, line: 664, baseType: !193, size: 64, align: 64, offset: 192)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "bytecount", scope: !186, file: !130, line: 666, baseType: !189, size: 64, align: 64, offset: 256)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecount", scope: !186, file: !130, line: 667, baseType: !189, size: 64, align: 64, offset: 320)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "headerbytecount", scope: !186, file: !130, line: 669, baseType: !191, size: 64, align: 64, offset: 384)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "deductheadercount", scope: !186, file: !130, line: 670, baseType: !191, size: 64, align: 64, offset: 448)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !186, file: !130, line: 676, baseType: !201, size: 128, align: 64, offset: 512)
!201 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !202, line: 30, size: 128, align: 64, elements: !203)
!202 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!203 = !{!204, !207}
!204 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !201, file: !202, line: 32, baseType: !205, size: 64, align: 64)
!205 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !206, line: 139, baseType: !191)
!206 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!207 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !201, file: !202, line: 33, baseType: !208, size: 64, align: 64, offset: 64)
!208 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !206, line: 141, baseType: !191)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !186, file: !130, line: 677, baseType: !201, size: 128, align: 64, offset: 640)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "header", scope: !186, file: !130, line: 678, baseType: !211, size: 8, align: 8, offset: 768)
!211 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "badheader", scope: !186, file: !130, line: 684, baseType: !185, size: 32, align: 32, offset: 800)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "headerline", scope: !186, file: !130, line: 686, baseType: !177, size: 32, align: 32, offset: 832)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "hbufp", scope: !186, file: !130, line: 688, baseType: !215, size: 64, align: 64, offset: 896)
!215 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !216, size: 64, align: 64)
!216 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "hbuflen", scope: !186, file: !130, line: 689, baseType: !158, size: 64, align: 64, offset: 960)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !186, file: !130, line: 690, baseType: !215, size: 64, align: 64, offset: 1024)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "str_start", scope: !186, file: !130, line: 691, baseType: !215, size: 64, align: 64, offset: 1088)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "end_ptr", scope: !186, file: !130, line: 692, baseType: !215, size: 64, align: 64, offset: 1152)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !186, file: !130, line: 693, baseType: !215, size: 64, align: 64, offset: 1216)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "content_range", scope: !186, file: !130, line: 694, baseType: !211, size: 8, align: 8, offset: 1280)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !186, file: !130, line: 695, baseType: !189, size: 64, align: 64, offset: 1344)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !186, file: !130, line: 697, baseType: !177, size: 32, align: 32, offset: 1408)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "start100", scope: !186, file: !130, line: 699, baseType: !201, size: 128, align: 64, offset: 1472)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "exp100", scope: !186, file: !130, line: 700, baseType: !227, size: 32, align: 32, offset: 1600)
!227 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "expect100", file: !130, line: 636, size: 32, align: 32, elements: !228)
!228 = !{!229, !230, !231, !232}
!229 = !DIEnumerator(name: "EXP100_SEND_DATA", value: 0)
!230 = !DIEnumerator(name: "EXP100_AWAITING_CONTINUE", value: 1)
!231 = !DIEnumerator(name: "EXP100_SENDING_REQUEST", value: 2)
!232 = !DIEnumerator(name: "EXP100_FAILED", value: 3)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "upgr101", scope: !186, file: !130, line: 701, baseType: !234, size: 32, align: 32, offset: 1632)
!234 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "upgrade101", file: !130, line: 644, size: 32, align: 32, elements: !235)
!235 = !{!236, !237, !238, !239}
!236 = !DIEnumerator(name: "UPGR101_INIT", value: 0)
!237 = !DIEnumerator(name: "UPGR101_REQUESTED", value: 1)
!238 = !DIEnumerator(name: "UPGR101_RECEIVED", value: 2)
!239 = !DIEnumerator(name: "UPGR101_WORKING", value: 3)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "auto_decoding", scope: !186, file: !130, line: 703, baseType: !177, size: 32, align: 32, offset: 1664)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "timeofdoc", scope: !186, file: !130, line: 715, baseType: !242, size: 64, align: 64, offset: 1728)
!242 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !243, line: 75, baseType: !205)
!243 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!244 = !DIDerivedType(tag: DW_TAG_member, name: "bodywrites", scope: !186, file: !130, line: 716, baseType: !191, size: 64, align: 64, offset: 1792)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !186, file: !130, line: 718, baseType: !215, size: 64, align: 64, offset: 1856)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuf", scope: !186, file: !130, line: 719, baseType: !215, size: 64, align: 64, offset: 1920)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "maxfd", scope: !186, file: !130, line: 720, baseType: !248, size: 32, align: 32, offset: 1984)
!248 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_t", file: !4, line: 131, baseType: !177)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "keepon", scope: !186, file: !130, line: 722, baseType: !177, size: 32, align: 32, offset: 2016)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "upload_done", scope: !186, file: !130, line: 724, baseType: !211, size: 8, align: 8, offset: 2048)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "ignorebody", scope: !186, file: !130, line: 727, baseType: !211, size: 8, align: 8, offset: 2056)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !186, file: !130, line: 728, baseType: !211, size: 8, align: 8, offset: 2064)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "location", scope: !186, file: !130, line: 731, baseType: !215, size: 64, align: 64, offset: 2112)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "newurl", scope: !186, file: !130, line: 733, baseType: !215, size: 64, align: 64, offset: 2176)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "upload_present", scope: !186, file: !130, line: 738, baseType: !256, size: 64, align: 64, offset: 2240)
!256 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !257, line: 109, baseType: !258)
!257 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!258 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !206, line: 172, baseType: !191)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "upload_fromhere", scope: !186, file: !130, line: 744, baseType: !215, size: 64, align: 64, offset: 2304)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !186, file: !130, line: 746, baseType: !211, size: 8, align: 8, offset: 2368)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "upload_chunky", scope: !186, file: !130, line: 747, baseType: !211, size: 8, align: 8, offset: 2376)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "getheader", scope: !186, file: !130, line: 749, baseType: !211, size: 8, align: 8, offset: 2384)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "forbidchunk", scope: !186, file: !130, line: 751, baseType: !211, size: 8, align: 8, offset: 2392)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "protop", scope: !186, file: !130, line: 755, baseType: !148, size: 64, align: 64, offset: 2432)
!265 = !{!266, !267, !268}
!266 = !DIEnumerator(name: "HEADER_NORMAL", value: 0)
!267 = !DIEnumerator(name: "HEADER_PARTHEADER", value: 1)
!268 = !DIEnumerator(name: "HEADER_ALLBAD", value: 2)
!269 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 409, size: 32, align: 32, elements: !270)
!270 = !{!271, !272, !273, !274, !275, !276, !277, !278}
!271 = !DIEnumerator(name: "CURLINFO_TEXT", value: 0)
!272 = !DIEnumerator(name: "CURLINFO_HEADER_IN", value: 1)
!273 = !DIEnumerator(name: "CURLINFO_HEADER_OUT", value: 2)
!274 = !DIEnumerator(name: "CURLINFO_DATA_IN", value: 3)
!275 = !DIEnumerator(name: "CURLINFO_DATA_OUT", value: 4)
!276 = !DIEnumerator(name: "CURLINFO_SSL_DATA_IN", value: 5)
!277 = !DIEnumerator(name: "CURLINFO_SSL_DATA_OUT", value: 6)
!278 = !DIEnumerator(name: "CURLINFO_END", value: 7)
!279 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 375, size: 32, align: 32, elements: !280)
!280 = !{!281, !282, !283, !284}
!281 = !DIEnumerator(name: "CURLIOE_OK", value: 0)
!282 = !DIEnumerator(name: "CURLIOE_UNKNOWNCMD", value: 1)
!283 = !DIEnumerator(name: "CURLIOE_FAILRESTART", value: 2)
!284 = !DIEnumerator(name: "CURLIOE_LAST", value: 3)
!285 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 340, size: 32, align: 32, elements: !286)
!286 = !{!287, !288, !289}
!287 = !DIEnumerator(name: "CURLSOCKTYPE_IPCXN", value: 0)
!288 = !DIEnumerator(name: "CURLSOCKTYPE_ACCEPT", value: 1)
!289 = !DIEnumerator(name: "CURLSOCKTYPE_LAST", value: 2)
!290 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 1921, size: 32, align: 32, elements: !291)
!291 = !{!292, !293, !294, !295, !296}
!292 = !DIEnumerator(name: "CURL_TIMECOND_NONE", value: 0)
!293 = !DIEnumerator(name: "CURL_TIMECOND_IFMODSINCE", value: 1)
!294 = !DIEnumerator(name: "CURL_TIMECOND_IFUNMODSINCE", value: 2)
!295 = !DIEnumerator(name: "CURL_TIMECOND_LASTMOD", value: 3)
!296 = !DIEnumerator(name: "CURL_TIMECOND_LAST", value: 4)
!297 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !130, line: 1240, size: 32, align: 32, elements: !298)
!298 = !{!299, !300, !301, !302, !303, !304, !305, !306}
!299 = !DIEnumerator(name: "HTTPREQ_NONE", value: 0)
!300 = !DIEnumerator(name: "HTTPREQ_GET", value: 1)
!301 = !DIEnumerator(name: "HTTPREQ_POST", value: 2)
!302 = !DIEnumerator(name: "HTTPREQ_POST_FORM", value: 3)
!303 = !DIEnumerator(name: "HTTPREQ_PUT", value: 4)
!304 = !DIEnumerator(name: "HTTPREQ_HEAD", value: 5)
!305 = !DIEnumerator(name: "HTTPREQ_CUSTOM", value: 6)
!306 = !DIEnumerator(name: "HTTPREQ_LAST", value: 7)
!307 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 644, size: 32, align: 32, elements: !308)
!308 = !{!309, !310, !311, !312, !313, !314, !315}
!309 = !DIEnumerator(name: "CURLPROXY_HTTP", value: 0)
!310 = !DIEnumerator(name: "CURLPROXY_HTTP_1_0", value: 1)
!311 = !DIEnumerator(name: "CURLPROXY_HTTPS", value: 2)
!312 = !DIEnumerator(name: "CURLPROXY_SOCKS4", value: 4)
!313 = !DIEnumerator(name: "CURLPROXY_SOCKS5", value: 5)
!314 = !DIEnumerator(name: "CURLPROXY_SOCKS4A", value: 6)
!315 = !DIEnumerator(name: "CURLPROXY_SOCKS5_HOSTNAME", value: 7)
!316 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !317, line: 93, size: 32, align: 32, elements: !318)
!317 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/ftp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!318 = !{!319, !320, !321}
!319 = !DIEnumerator(name: "FTPFILE_MULTICWD", value: 1)
!320 = !DIEnumerator(name: "FTPFILE_NOCWD", value: 2)
!321 = !DIEnumerator(name: "FTPFILE_SINGLECWD", value: 3)
!322 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khtype", file: !4, line: 704, size: 32, align: 32, elements: !323)
!323 = !{!324, !325, !326, !327}
!324 = !DIEnumerator(name: "CURLKHTYPE_UNKNOWN", value: 0)
!325 = !DIEnumerator(name: "CURLKHTYPE_RSA1", value: 1)
!326 = !DIEnumerator(name: "CURLKHTYPE_RSA", value: 2)
!327 = !DIEnumerator(name: "CURLKHTYPE_DSS", value: 3)
!328 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khmatch", file: !4, line: 731, size: 32, align: 32, elements: !329)
!329 = !{!330, !331, !332, !333}
!330 = !DIEnumerator(name: "CURLKHMATCH_OK", value: 0)
!331 = !DIEnumerator(name: "CURLKHMATCH_MISMATCH", value: 1)
!332 = !DIEnumerator(name: "CURLKHMATCH_MISSING", value: 2)
!333 = !DIEnumerator(name: "CURLKHMATCH_LAST", value: 3)
!334 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "CURL_NETRC_OPTION", file: !4, line: 1867, size: 32, align: 32, elements: !335)
!335 = !{!336, !337, !338, !339}
!336 = !DIEnumerator(name: "CURL_NETRC_IGNORED", value: 0)
!337 = !DIEnumerator(name: "CURL_NETRC_OPTIONAL", value: 1)
!338 = !DIEnumerator(name: "CURL_NETRC_REQUIRED", value: 2)
!339 = !DIEnumerator(name: "CURL_NETRC_LAST", value: 3)
!340 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 746, size: 32, align: 32, elements: !341)
!341 = !{!342, !343, !344, !345, !346}
!342 = !DIEnumerator(name: "CURLUSESSL_NONE", value: 0)
!343 = !DIEnumerator(name: "CURLUSESSL_TRY", value: 1)
!344 = !DIEnumerator(name: "CURLUSESSL_CONTROL", value: 2)
!345 = !DIEnumerator(name: "CURLUSESSL_ALL", value: 3)
!346 = !DIEnumerator(name: "CURLUSESSL_LAST", value: 4)
!347 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 790, size: 32, align: 32, elements: !348)
!348 = !{!349, !350, !351, !352}
!349 = !DIEnumerator(name: "CURLFTPAUTH_DEFAULT", value: 0)
!350 = !DIEnumerator(name: "CURLFTPAUTH_SSL", value: 1)
!351 = !DIEnumerator(name: "CURLFTPAUTH_TLS", value: 2)
!352 = !DIEnumerator(name: "CURLFTPAUTH_LAST", value: 3)
!353 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 782, size: 32, align: 32, elements: !354)
!354 = !{!355, !356, !357, !358}
!355 = !DIEnumerator(name: "CURLFTPSSL_CCC_NONE", value: 0)
!356 = !DIEnumerator(name: "CURLFTPSSL_CCC_PASSIVE", value: 1)
!357 = !DIEnumerator(name: "CURLFTPSSL_CCC_ACTIVE", value: 2)
!358 = !DIEnumerator(name: "CURLFTPSSL_CCC_LAST", value: 3)
!359 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !130, line: 1251, size: 32, align: 32, elements: !360)
!360 = !{!361, !362, !363, !364, !365, !366, !367, !368, !369, !370, !371, !372, !373}
!361 = !DIEnumerator(name: "RTSPREQ_NONE", value: 0)
!362 = !DIEnumerator(name: "RTSPREQ_OPTIONS", value: 1)
!363 = !DIEnumerator(name: "RTSPREQ_DESCRIBE", value: 2)
!364 = !DIEnumerator(name: "RTSPREQ_ANNOUNCE", value: 3)
!365 = !DIEnumerator(name: "RTSPREQ_SETUP", value: 4)
!366 = !DIEnumerator(name: "RTSPREQ_PLAY", value: 5)
!367 = !DIEnumerator(name: "RTSPREQ_PAUSE", value: 6)
!368 = !DIEnumerator(name: "RTSPREQ_TEARDOWN", value: 7)
!369 = !DIEnumerator(name: "RTSPREQ_GET_PARAMETER", value: 8)
!370 = !DIEnumerator(name: "RTSPREQ_SET_PARAMETER", value: 9)
!371 = !DIEnumerator(name: "RTSPREQ_RECORD", value: 10)
!372 = !DIEnumerator(name: "RTSPREQ_RECEIVE", value: 11)
!373 = !DIEnumerator(name: "RTSPREQ_LAST", value: 12)
!374 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !375, line: 30, size: 32, align: 32, elements: !376)
!375 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/wildcard.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!376 = !{!377, !378, !379, !380, !381, !382, !383, !384}
!377 = !DIEnumerator(name: "CURLWC_CLEAR", value: 0)
!378 = !DIEnumerator(name: "CURLWC_INIT", value: 1)
!379 = !DIEnumerator(name: "CURLWC_MATCHING", value: 2)
!380 = !DIEnumerator(name: "CURLWC_DOWNLOADING", value: 3)
!381 = !DIEnumerator(name: "CURLWC_CLEAN", value: 4)
!382 = !DIEnumerator(name: "CURLWC_SKIP", value: 5)
!383 = !DIEnumerator(name: "CURLWC_ERROR", value: 6)
!384 = !DIEnumerator(name: "CURLWC_DONE", value: 7)
!385 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 2222, size: 32, align: 32, elements: !386)
!386 = !{!387, !388, !389, !390, !391, !392, !393, !394, !395, !396, !397, !398}
!387 = !DIEnumerator(name: "CURLSSLBACKEND_NONE", value: 0)
!388 = !DIEnumerator(name: "CURLSSLBACKEND_OPENSSL", value: 1)
!389 = !DIEnumerator(name: "CURLSSLBACKEND_GNUTLS", value: 2)
!390 = !DIEnumerator(name: "CURLSSLBACKEND_NSS", value: 3)
!391 = !DIEnumerator(name: "CURLSSLBACKEND_OBSOLETE4", value: 4)
!392 = !DIEnumerator(name: "CURLSSLBACKEND_GSKIT", value: 5)
!393 = !DIEnumerator(name: "CURLSSLBACKEND_POLARSSL", value: 6)
!394 = !DIEnumerator(name: "CURLSSLBACKEND_CYASSL", value: 7)
!395 = !DIEnumerator(name: "CURLSSLBACKEND_SCHANNEL", value: 8)
!396 = !DIEnumerator(name: "CURLSSLBACKEND_DARWINSSL", value: 9)
!397 = !DIEnumerator(name: "CURLSSLBACKEND_AXTLS", value: 10)
!398 = !DIEnumerator(name: "CURLSSLBACKEND_MBEDTLS", value: 11)
!399 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !400, line: 31, size: 32, align: 32, elements: !401)
!400 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http_chunks.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!401 = !{!402, !403, !404, !405, !406, !407, !408, !409}
!402 = !DIEnumerator(name: "CHUNK_HEX", value: 0)
!403 = !DIEnumerator(name: "CHUNK_LF", value: 1)
!404 = !DIEnumerator(name: "CHUNK_DATA", value: 2)
!405 = !DIEnumerator(name: "CHUNK_POSTLF", value: 3)
!406 = !DIEnumerator(name: "CHUNK_STOP", value: 4)
!407 = !DIEnumerator(name: "CHUNK_TRAILER", value: 5)
!408 = !DIEnumerator(name: "CHUNK_TRAILER_CR", value: 6)
!409 = !DIEnumerator(name: "CHUNK_TRAILER_POSTCR", value: 7)
!410 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !130, line: 267, size: 32, align: 32, elements: !411)
!411 = !{!412, !413, !414}
!412 = !DIEnumerator(name: "ssl_connection_none", value: 0)
!413 = !DIEnumerator(name: "ssl_connection_negotiating", value: 1)
!414 = !DIEnumerator(name: "ssl_connection_complete", value: 2)
!415 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !130, line: 258, size: 32, align: 32, elements: !416)
!416 = !{!417, !418, !419, !420, !421, !422}
!417 = !DIEnumerator(name: "ssl_connect_1", value: 0)
!418 = !DIEnumerator(name: "ssl_connect_2", value: 1)
!419 = !DIEnumerator(name: "ssl_connect_2_reading", value: 2)
!420 = !DIEnumerator(name: "ssl_connect_2_writing", value: 3)
!421 = !DIEnumerator(name: "ssl_connect_3", value: 4)
!422 = !DIEnumerator(name: "ssl_connect_done", value: 5)
!423 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !317, line: 42, size: 32, align: 32, elements: !424)
!424 = !{!425, !426, !427, !428, !429, !430, !431, !432, !433, !434, !435, !436, !437, !438, !439, !440, !441, !442, !443, !444, !445, !446, !447, !448, !449, !450, !451, !452, !453, !454, !455, !456, !457, !458, !459, !460}
!425 = !DIEnumerator(name: "FTP_STOP", value: 0)
!426 = !DIEnumerator(name: "FTP_WAIT220", value: 1)
!427 = !DIEnumerator(name: "FTP_AUTH", value: 2)
!428 = !DIEnumerator(name: "FTP_USER", value: 3)
!429 = !DIEnumerator(name: "FTP_PASS", value: 4)
!430 = !DIEnumerator(name: "FTP_ACCT", value: 5)
!431 = !DIEnumerator(name: "FTP_PBSZ", value: 6)
!432 = !DIEnumerator(name: "FTP_PROT", value: 7)
!433 = !DIEnumerator(name: "FTP_CCC", value: 8)
!434 = !DIEnumerator(name: "FTP_PWD", value: 9)
!435 = !DIEnumerator(name: "FTP_SYST", value: 10)
!436 = !DIEnumerator(name: "FTP_NAMEFMT", value: 11)
!437 = !DIEnumerator(name: "FTP_QUOTE", value: 12)
!438 = !DIEnumerator(name: "FTP_RETR_PREQUOTE", value: 13)
!439 = !DIEnumerator(name: "FTP_STOR_PREQUOTE", value: 14)
!440 = !DIEnumerator(name: "FTP_POSTQUOTE", value: 15)
!441 = !DIEnumerator(name: "FTP_CWD", value: 16)
!442 = !DIEnumerator(name: "FTP_MKD", value: 17)
!443 = !DIEnumerator(name: "FTP_MDTM", value: 18)
!444 = !DIEnumerator(name: "FTP_TYPE", value: 19)
!445 = !DIEnumerator(name: "FTP_LIST_TYPE", value: 20)
!446 = !DIEnumerator(name: "FTP_RETR_TYPE", value: 21)
!447 = !DIEnumerator(name: "FTP_STOR_TYPE", value: 22)
!448 = !DIEnumerator(name: "FTP_SIZE", value: 23)
!449 = !DIEnumerator(name: "FTP_RETR_SIZE", value: 24)
!450 = !DIEnumerator(name: "FTP_STOR_SIZE", value: 25)
!451 = !DIEnumerator(name: "FTP_REST", value: 26)
!452 = !DIEnumerator(name: "FTP_RETR_REST", value: 27)
!453 = !DIEnumerator(name: "FTP_PORT", value: 28)
!454 = !DIEnumerator(name: "FTP_PRET", value: 29)
!455 = !DIEnumerator(name: "FTP_PASV", value: 30)
!456 = !DIEnumerator(name: "FTP_LIST", value: 31)
!457 = !DIEnumerator(name: "FTP_RETR", value: 32)
!458 = !DIEnumerator(name: "FTP_STOR", value: 33)
!459 = !DIEnumerator(name: "FTP_QUIT", value: 34)
!460 = !DIEnumerator(name: "FTP_LAST", value: 35)
!461 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !462, line: 31, size: 32, align: 32, elements: !463)
!462 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/imap.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!463 = !{!464, !465, !466, !467, !468, !469, !470, !471, !472, !473, !474, !475, !476, !477, !478, !479}
!464 = !DIEnumerator(name: "IMAP_STOP", value: 0)
!465 = !DIEnumerator(name: "IMAP_SERVERGREET", value: 1)
!466 = !DIEnumerator(name: "IMAP_CAPABILITY", value: 2)
!467 = !DIEnumerator(name: "IMAP_STARTTLS", value: 3)
!468 = !DIEnumerator(name: "IMAP_UPGRADETLS", value: 4)
!469 = !DIEnumerator(name: "IMAP_AUTHENTICATE", value: 5)
!470 = !DIEnumerator(name: "IMAP_LOGIN", value: 6)
!471 = !DIEnumerator(name: "IMAP_LIST", value: 7)
!472 = !DIEnumerator(name: "IMAP_SELECT", value: 8)
!473 = !DIEnumerator(name: "IMAP_FETCH", value: 9)
!474 = !DIEnumerator(name: "IMAP_FETCH_FINAL", value: 10)
!475 = !DIEnumerator(name: "IMAP_APPEND", value: 11)
!476 = !DIEnumerator(name: "IMAP_APPEND_FINAL", value: 12)
!477 = !DIEnumerator(name: "IMAP_SEARCH", value: 13)
!478 = !DIEnumerator(name: "IMAP_LOGOUT", value: 14)
!479 = !DIEnumerator(name: "IMAP_LAST", value: 15)
!480 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !481, line: 58, size: 32, align: 32, elements: !482)
!481 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_sasl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!482 = !{!483, !484, !485, !486, !487, !488, !489, !490, !491, !492, !493, !494, !495, !496, !497, !498, !499}
!483 = !DIEnumerator(name: "SASL_STOP", value: 0)
!484 = !DIEnumerator(name: "SASL_PLAIN", value: 1)
!485 = !DIEnumerator(name: "SASL_LOGIN", value: 2)
!486 = !DIEnumerator(name: "SASL_LOGIN_PASSWD", value: 3)
!487 = !DIEnumerator(name: "SASL_EXTERNAL", value: 4)
!488 = !DIEnumerator(name: "SASL_CRAMMD5", value: 5)
!489 = !DIEnumerator(name: "SASL_DIGESTMD5", value: 6)
!490 = !DIEnumerator(name: "SASL_DIGESTMD5_RESP", value: 7)
!491 = !DIEnumerator(name: "SASL_NTLM", value: 8)
!492 = !DIEnumerator(name: "SASL_NTLM_TYPE2MSG", value: 9)
!493 = !DIEnumerator(name: "SASL_GSSAPI", value: 10)
!494 = !DIEnumerator(name: "SASL_GSSAPI_TOKEN", value: 11)
!495 = !DIEnumerator(name: "SASL_GSSAPI_NO_DATA", value: 12)
!496 = !DIEnumerator(name: "SASL_OAUTH2", value: 13)
!497 = !DIEnumerator(name: "SASL_OAUTH2_RESP", value: 14)
!498 = !DIEnumerator(name: "SASL_CANCEL", value: 15)
!499 = !DIEnumerator(name: "SASL_FINAL", value: 16)
!500 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !501, line: 31, size: 32, align: 32, elements: !502)
!501 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pop3.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!502 = !{!503, !504, !505, !506, !507, !508, !509, !510, !511, !512, !513, !514}
!503 = !DIEnumerator(name: "POP3_STOP", value: 0)
!504 = !DIEnumerator(name: "POP3_SERVERGREET", value: 1)
!505 = !DIEnumerator(name: "POP3_CAPA", value: 2)
!506 = !DIEnumerator(name: "POP3_STARTTLS", value: 3)
!507 = !DIEnumerator(name: "POP3_UPGRADETLS", value: 4)
!508 = !DIEnumerator(name: "POP3_AUTH", value: 5)
!509 = !DIEnumerator(name: "POP3_APOP", value: 6)
!510 = !DIEnumerator(name: "POP3_USER", value: 7)
!511 = !DIEnumerator(name: "POP3_PASS", value: 8)
!512 = !DIEnumerator(name: "POP3_COMMAND", value: 9)
!513 = !DIEnumerator(name: "POP3_QUIT", value: 10)
!514 = !DIEnumerator(name: "POP3_LAST", value: 11)
!515 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !516, line: 31, size: 32, align: 32, elements: !517)
!516 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/smtp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!517 = !{!518, !519, !520, !521, !522, !523, !524, !525, !526, !527, !528, !529, !530, !531}
!518 = !DIEnumerator(name: "SMTP_STOP", value: 0)
!519 = !DIEnumerator(name: "SMTP_SERVERGREET", value: 1)
!520 = !DIEnumerator(name: "SMTP_EHLO", value: 2)
!521 = !DIEnumerator(name: "SMTP_HELO", value: 3)
!522 = !DIEnumerator(name: "SMTP_STARTTLS", value: 4)
!523 = !DIEnumerator(name: "SMTP_UPGRADETLS", value: 5)
!524 = !DIEnumerator(name: "SMTP_AUTH", value: 6)
!525 = !DIEnumerator(name: "SMTP_COMMAND", value: 7)
!526 = !DIEnumerator(name: "SMTP_MAIL", value: 8)
!527 = !DIEnumerator(name: "SMTP_RCPT", value: 9)
!528 = !DIEnumerator(name: "SMTP_DATA", value: 10)
!529 = !DIEnumerator(name: "SMTP_POSTDATA", value: 11)
!530 = !DIEnumerator(name: "SMTP_QUIT", value: 12)
!531 = !DIEnumerator(name: "SMTP_LAST", value: 13)
!532 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "smb_conn_state", file: !533, line: 25, size: 32, align: 32, elements: !534)
!533 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/smb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!534 = !{!535, !536, !537, !538, !539}
!535 = !DIEnumerator(name: "SMB_NOT_CONNECTED", value: 0)
!536 = !DIEnumerator(name: "SMB_CONNECTING", value: 1)
!537 = !DIEnumerator(name: "SMB_NEGOTIATE", value: 2)
!538 = !DIEnumerator(name: "SMB_SETUP", value: 3)
!539 = !DIEnumerator(name: "SMB_CONNECTED", value: 4)
!540 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !541, file: !130, line: 1133, size: 32, align: 32, elements: !1674)
!541 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectdata", file: !130, line: 895, size: 13440, align: 64, elements: !542)
!542 = !{!543, !1255, !1267, !1268, !1269, !1270, !1271, !1297, !1298, !1302, !1303, !1304, !1305, !1312, !1313, !1314, !1322, !1323, !1324, !1325, !1326, !1327, !1328, !1329, !1330, !1331, !1332, !1333, !1334, !1335, !1336, !1337, !1338, !1339, !1341, !1342, !1344, !1351, !1357, !1366, !1367, !1368, !1369, !1370, !1406, !1407, !1408, !1409, !1463, !1464, !1465, !1466, !1467, !1480, !1481, !1482, !1483, !1484, !1485, !1486, !1487, !1488, !1489, !1493, !1494, !1495, !1496, !1659, !1660, !1661, !1662, !1663, !1664, !1666, !1673}
!543 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !541, file: !130, line: 899, baseType: !544, size: 64, align: 64)
!544 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !545, size: 64, align: 64)
!545 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_easy", file: !130, line: 1801, size: 160192, align: 64, elements: !546)
!546 = !{!547, !548, !549, !551, !553, !555, !571, !575, !576, !577, !643, !644, !647, !648, !1030, !1039, !1066, !1102, !1206, !1218, !1248, !1254}
!547 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !545, file: !130, line: 1803, baseType: !544, size: 64, align: 64)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !545, file: !130, line: 1804, baseType: !544, size: 64, align: 64, offset: 64)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "easy_conn", scope: !545, file: !130, line: 1806, baseType: !550, size: 64, align: 64, offset: 128)
!550 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !541, size: 64, align: 64)
!551 = !DIDerivedType(tag: DW_TAG_member, name: "mstate", scope: !545, file: !130, line: 1808, baseType: !552, size: 32, align: 32, offset: 192)
!552 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMstate", file: !101, line: 59, baseType: !100)
!553 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !545, file: !130, line: 1809, baseType: !554, size: 32, align: 32, offset: 224)
!554 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLcode", file: !4, line: 561, baseType: !3)
!555 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !545, file: !130, line: 1811, baseType: !556, size: 192, align: 64, offset: 256)
!556 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_message", file: !101, line: 27, size: 192, align: 64, elements: !557)
!557 = !{!558}
!558 = !DIDerivedType(tag: DW_TAG_member, name: "extmsg", scope: !556, file: !101, line: 29, baseType: !559, size: 192, align: 64)
!559 = !DICompositeType(tag: DW_TAG_structure_type, name: "CURLMsg", file: !124, line: 93, size: 192, align: 64, elements: !560)
!560 = !{!561, !563, !566}
!561 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !559, file: !124, line: 94, baseType: !562, size: 32, align: 32)
!562 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMSG", file: !124, line: 91, baseType: !123)
!563 = !DIDerivedType(tag: DW_TAG_member, name: "easy_handle", scope: !559, file: !124, line: 95, baseType: !564, size: 64, align: 64, offset: 64)
!564 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !565, size: 64, align: 64)
!565 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURL", file: !4, line: 100, baseType: !545)
!566 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !559, file: !124, line: 99, baseType: !567, size: 64, align: 64, offset: 128)
!567 = !DICompositeType(tag: DW_TAG_union_type, scope: !559, file: !124, line: 96, size: 64, align: 64, elements: !568)
!568 = !{!569, !570}
!569 = !DIDerivedType(tag: DW_TAG_member, name: "whatever", scope: !567, file: !124, line: 97, baseType: !148, size: 64, align: 64)
!570 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !567, file: !124, line: 98, baseType: !554, size: 32, align: 32)
!571 = !DIDerivedType(tag: DW_TAG_member, name: "sockets", scope: !545, file: !130, line: 1817, baseType: !572, size: 160, align: 32, offset: 448)
!572 = !DICompositeType(tag: DW_TAG_array_type, baseType: !248, size: 160, align: 32, elements: !573)
!573 = !{!574}
!574 = !DISubrange(count: 5)
!575 = !DIDerivedType(tag: DW_TAG_member, name: "numsocks", scope: !545, file: !130, line: 1818, baseType: !177, size: 32, align: 32, offset: 608)
!576 = !DIDerivedType(tag: DW_TAG_member, name: "dns", scope: !545, file: !130, line: 1820, baseType: !131, size: 128, align: 64, offset: 640)
!577 = !DIDerivedType(tag: DW_TAG_member, name: "multi", scope: !545, file: !130, line: 1821, baseType: !578, size: 64, align: 64, offset: 768)
!578 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !579, size: 64, align: 64)
!579 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_multi", file: !101, line: 70, size: 3840, align: 64, elements: !580)
!580 = !{!581, !582, !583, !584, !585, !586, !587, !588, !593, !594, !601, !602, !603, !614, !615, !616, !617, !625, !626, !627, !628, !629, !630, !631, !632, !633, !634, !641, !642}
!581 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !579, file: !101, line: 73, baseType: !191, size: 64, align: 64)
!582 = !DIDerivedType(tag: DW_TAG_member, name: "easyp", scope: !579, file: !101, line: 76, baseType: !544, size: 64, align: 64, offset: 64)
!583 = !DIDerivedType(tag: DW_TAG_member, name: "easylp", scope: !579, file: !101, line: 77, baseType: !544, size: 64, align: 64, offset: 128)
!584 = !DIDerivedType(tag: DW_TAG_member, name: "num_easy", scope: !579, file: !101, line: 79, baseType: !177, size: 32, align: 32, offset: 192)
!585 = !DIDerivedType(tag: DW_TAG_member, name: "num_alive", scope: !579, file: !101, line: 80, baseType: !177, size: 32, align: 32, offset: 224)
!586 = !DIDerivedType(tag: DW_TAG_member, name: "msglist", scope: !579, file: !101, line: 83, baseType: !140, size: 256, align: 64, offset: 256)
!587 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !579, file: !101, line: 85, baseType: !140, size: 256, align: 64, offset: 512)
!588 = !DIDerivedType(tag: DW_TAG_member, name: "socket_cb", scope: !579, file: !101, line: 89, baseType: !589, size: 64, align: 64, offset: 768)
!589 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_callback", file: !124, line: 268, baseType: !590)
!590 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !591, size: 64, align: 64)
!591 = !DISubroutineType(types: !592)
!592 = !{!177, !564, !248, !177, !148, !148}
!593 = !DIDerivedType(tag: DW_TAG_member, name: "socket_userp", scope: !579, file: !101, line: 90, baseType: !148, size: 64, align: 64, offset: 832)
!594 = !DIDerivedType(tag: DW_TAG_member, name: "push_cb", scope: !579, file: !101, line: 93, baseType: !595, size: 64, align: 64, offset: 896)
!595 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_push_callback", file: !124, line: 429, baseType: !596)
!596 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !597, size: 64, align: 64)
!597 = !DISubroutineType(types: !598)
!598 = !{!177, !564, !564, !158, !599, !148}
!599 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !600, size: 64, align: 64)
!600 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_pushheaders", file: !124, line: 422, flags: DIFlagFwdDecl)
!601 = !DIDerivedType(tag: DW_TAG_member, name: "push_userp", scope: !579, file: !101, line: 94, baseType: !148, size: 64, align: 64, offset: 960)
!602 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !579, file: !101, line: 97, baseType: !135, size: 384, align: 64, offset: 1024)
!603 = !DIDerivedType(tag: DW_TAG_member, name: "timetree", scope: !579, file: !101, line: 101, baseType: !604, size: 64, align: 64, offset: 1408)
!604 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !605, size: 64, align: 64)
!605 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_tree", file: !606, line: 26, size: 448, align: 64, elements: !607)
!606 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/splay.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!607 = !{!608, !609, !610, !611, !612, !613}
!608 = !DIDerivedType(tag: DW_TAG_member, name: "smaller", scope: !605, file: !606, line: 27, baseType: !604, size: 64, align: 64)
!609 = !DIDerivedType(tag: DW_TAG_member, name: "larger", scope: !605, file: !606, line: 28, baseType: !604, size: 64, align: 64, offset: 64)
!610 = !DIDerivedType(tag: DW_TAG_member, name: "samen", scope: !605, file: !606, line: 29, baseType: !604, size: 64, align: 64, offset: 128)
!611 = !DIDerivedType(tag: DW_TAG_member, name: "samep", scope: !605, file: !606, line: 30, baseType: !604, size: 64, align: 64, offset: 192)
!612 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !605, file: !606, line: 31, baseType: !201, size: 128, align: 64, offset: 256)
!613 = !DIDerivedType(tag: DW_TAG_member, name: "payload", scope: !605, file: !606, line: 32, baseType: !148, size: 64, align: 64, offset: 384)
!614 = !DIDerivedType(tag: DW_TAG_member, name: "sockhash", scope: !579, file: !101, line: 106, baseType: !135, size: 384, align: 64, offset: 1472)
!615 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining", scope: !579, file: !101, line: 109, baseType: !191, size: 64, align: 64, offset: 1856)
!616 = !DIDerivedType(tag: DW_TAG_member, name: "recheckstate", scope: !579, file: !101, line: 111, baseType: !211, size: 8, align: 8, offset: 1920)
!617 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !579, file: !101, line: 114, baseType: !618, size: 640, align: 64, offset: 1984)
!618 = !DICompositeType(tag: DW_TAG_structure_type, name: "conncache", file: !619, line: 26, size: 640, align: 64, elements: !620)
!619 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/conncache.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!620 = !{!621, !622, !623, !624}
!621 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !618, file: !619, line: 27, baseType: !135, size: 384, align: 64)
!622 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !618, file: !619, line: 28, baseType: !158, size: 64, align: 64, offset: 384)
!623 = !DIDerivedType(tag: DW_TAG_member, name: "next_connection_id", scope: !618, file: !619, line: 29, baseType: !191, size: 64, align: 64, offset: 448)
!624 = !DIDerivedType(tag: DW_TAG_member, name: "last_cleanup", scope: !618, file: !619, line: 30, baseType: !201, size: 128, align: 64, offset: 512)
!625 = !DIDerivedType(tag: DW_TAG_member, name: "closure_handle", scope: !579, file: !101, line: 118, baseType: !544, size: 64, align: 64, offset: 2624)
!626 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !579, file: !101, line: 120, baseType: !191, size: 64, align: 64, offset: 2688)
!627 = !DIDerivedType(tag: DW_TAG_member, name: "max_host_connections", scope: !579, file: !101, line: 123, baseType: !191, size: 64, align: 64, offset: 2752)
!628 = !DIDerivedType(tag: DW_TAG_member, name: "max_total_connections", scope: !579, file: !101, line: 126, baseType: !191, size: 64, align: 64, offset: 2816)
!629 = !DIDerivedType(tag: DW_TAG_member, name: "max_pipeline_length", scope: !579, file: !101, line: 129, baseType: !191, size: 64, align: 64, offset: 2880)
!630 = !DIDerivedType(tag: DW_TAG_member, name: "content_length_penalty_size", scope: !579, file: !101, line: 132, baseType: !191, size: 64, align: 64, offset: 2944)
!631 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_length_penalty_size", scope: !579, file: !101, line: 137, baseType: !191, size: 64, align: 64, offset: 3008)
!632 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining_site_bl", scope: !579, file: !101, line: 141, baseType: !140, size: 256, align: 64, offset: 3072)
!633 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining_server_bl", scope: !579, file: !101, line: 144, baseType: !140, size: 256, align: 64, offset: 3328)
!634 = !DIDerivedType(tag: DW_TAG_member, name: "timer_cb", scope: !579, file: !101, line: 148, baseType: !635, size: 64, align: 64, offset: 3584)
!635 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_multi_timer_callback", file: !124, line: 285, baseType: !636)
!636 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !637, size: 64, align: 64)
!637 = !DISubroutineType(types: !638)
!638 = !{!177, !639, !191, !148}
!639 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !640, size: 64, align: 64)
!640 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLM", file: !124, line: 56, baseType: !579)
!641 = !DIDerivedType(tag: DW_TAG_member, name: "timer_userp", scope: !579, file: !101, line: 149, baseType: !148, size: 64, align: 64, offset: 3648)
!642 = !DIDerivedType(tag: DW_TAG_member, name: "timer_lastcall", scope: !579, file: !101, line: 150, baseType: !201, size: 128, align: 64, offset: 3712)
!643 = !DIDerivedType(tag: DW_TAG_member, name: "multi_easy", scope: !545, file: !130, line: 1824, baseType: !578, size: 64, align: 64, offset: 832)
!644 = !DIDerivedType(tag: DW_TAG_member, name: "share", scope: !545, file: !130, line: 1827, baseType: !645, size: 64, align: 64, offset: 896)
!645 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !646, size: 64, align: 64)
!646 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_share", file: !4, line: 101, flags: DIFlagFwdDecl)
!647 = !DIDerivedType(tag: DW_TAG_member, name: "req", scope: !545, file: !130, line: 1828, baseType: !186, size: 2496, align: 64, offset: 960)
!648 = !DIDerivedType(tag: DW_TAG_member, name: "set", scope: !545, file: !130, line: 1829, baseType: !649, size: 13760, align: 64, offset: 3456)
!649 = !DICompositeType(tag: DW_TAG_structure_type, name: "UserDefined", file: !130, line: 1558, size: 13760, align: 64, elements: !650)
!650 = !{!651, !706, !707, !708, !709, !710, !711, !712, !713, !714, !715, !716, !717, !718, !719, !720, !721, !726, !727, !728, !729, !734, !735, !736, !738, !739, !740, !746, !751, !757, !763, !769, !770, !794, !795, !800, !801, !802, !807, !808, !809, !810, !811, !812, !813, !814, !815, !816, !817, !818, !819, !820, !821, !822, !823, !829, !830, !848, !849, !850, !851, !852, !853, !854, !855, !856, !857, !858, !859, !860, !862, !863, !865, !866, !902, !903, !907, !909, !910, !911, !912, !913, !914, !915, !917, !918, !932, !933, !934, !935, !936, !937, !938, !939, !940, !941, !942, !943, !944, !945, !946, !947, !948, !949, !950, !951, !952, !953, !954, !955, !956, !957, !958, !959, !961, !963, !965, !966, !967, !968, !969, !970, !971, !972, !973, !974, !975, !976, !977, !981, !982, !983, !984, !985, !986, !988, !989, !990, !997, !1002, !1007, !1008, !1009, !1010, !1011, !1012, !1013, !1014, !1015, !1016, !1017, !1018, !1019, !1020, !1021, !1022, !1023, !1029}
!651 = !DIDerivedType(tag: DW_TAG_member, name: "err", scope: !649, file: !130, line: 1559, baseType: !652, size: 64, align: 64)
!652 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !653, size: 64, align: 64)
!653 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !654, line: 48, baseType: !655)
!654 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!655 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !656, line: 245, size: 1728, align: 64, elements: !657)
!656 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!657 = !{!658, !659, !660, !661, !662, !663, !664, !665, !666, !667, !668, !669, !670, !678, !679, !680, !681, !683, !685, !687, !691, !694, !696, !697, !698, !699, !700, !701, !702}
!658 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !655, file: !656, line: 246, baseType: !177, size: 32, align: 32)
!659 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !655, file: !656, line: 251, baseType: !215, size: 64, align: 64, offset: 64)
!660 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !655, file: !656, line: 252, baseType: !215, size: 64, align: 64, offset: 128)
!661 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !655, file: !656, line: 253, baseType: !215, size: 64, align: 64, offset: 192)
!662 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !655, file: !656, line: 254, baseType: !215, size: 64, align: 64, offset: 256)
!663 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !655, file: !656, line: 255, baseType: !215, size: 64, align: 64, offset: 320)
!664 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !655, file: !656, line: 256, baseType: !215, size: 64, align: 64, offset: 384)
!665 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !655, file: !656, line: 257, baseType: !215, size: 64, align: 64, offset: 448)
!666 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !655, file: !656, line: 258, baseType: !215, size: 64, align: 64, offset: 512)
!667 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !655, file: !656, line: 260, baseType: !215, size: 64, align: 64, offset: 576)
!668 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !655, file: !656, line: 261, baseType: !215, size: 64, align: 64, offset: 640)
!669 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !655, file: !656, line: 262, baseType: !215, size: 64, align: 64, offset: 704)
!670 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !655, file: !656, line: 264, baseType: !671, size: 64, align: 64, offset: 768)
!671 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !672, size: 64, align: 64)
!672 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !656, line: 160, size: 192, align: 64, elements: !673)
!673 = !{!674, !675, !677}
!674 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !672, file: !656, line: 161, baseType: !671, size: 64, align: 64)
!675 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !672, file: !656, line: 162, baseType: !676, size: 64, align: 64, offset: 64)
!676 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !655, size: 64, align: 64)
!677 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !672, file: !656, line: 166, baseType: !177, size: 32, align: 32, offset: 128)
!678 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !655, file: !656, line: 266, baseType: !676, size: 64, align: 64, offset: 832)
!679 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !655, file: !656, line: 268, baseType: !177, size: 32, align: 32, offset: 896)
!680 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !655, file: !656, line: 272, baseType: !177, size: 32, align: 32, offset: 928)
!681 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !655, file: !656, line: 274, baseType: !682, size: 64, align: 64, offset: 960)
!682 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !206, line: 131, baseType: !191)
!683 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !655, file: !656, line: 278, baseType: !684, size: 16, align: 16, offset: 1024)
!684 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!685 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !655, file: !656, line: 279, baseType: !686, size: 8, align: 8, offset: 1040)
!686 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!687 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !655, file: !656, line: 280, baseType: !688, size: 8, align: 8, offset: 1048)
!688 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 8, align: 8, elements: !689)
!689 = !{!690}
!690 = !DISubrange(count: 1)
!691 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !655, file: !656, line: 284, baseType: !692, size: 64, align: 64, offset: 1088)
!692 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !693, size: 64, align: 64)
!693 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !656, line: 154, baseType: null)
!694 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !655, file: !656, line: 293, baseType: !695, size: 64, align: 64, offset: 1152)
!695 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !206, line: 132, baseType: !191)
!696 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !655, file: !656, line: 302, baseType: !148, size: 64, align: 64, offset: 1216)
!697 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !655, file: !656, line: 303, baseType: !148, size: 64, align: 64, offset: 1280)
!698 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !655, file: !656, line: 304, baseType: !148, size: 64, align: 64, offset: 1344)
!699 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !655, file: !656, line: 305, baseType: !148, size: 64, align: 64, offset: 1408)
!700 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !655, file: !656, line: 306, baseType: !158, size: 64, align: 64, offset: 1472)
!701 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !655, file: !656, line: 308, baseType: !177, size: 32, align: 32, offset: 1536)
!702 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !655, file: !656, line: 310, baseType: !703, size: 160, align: 8, offset: 1568)
!703 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 160, align: 8, elements: !704)
!704 = !{!705}
!705 = !DISubrange(count: 20)
!706 = !DIDerivedType(tag: DW_TAG_member, name: "debugdata", scope: !649, file: !130, line: 1560, baseType: !148, size: 64, align: 64, offset: 64)
!707 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuffer", scope: !649, file: !130, line: 1561, baseType: !215, size: 64, align: 64, offset: 128)
!708 = !DIDerivedType(tag: DW_TAG_member, name: "proxyport", scope: !649, file: !130, line: 1562, baseType: !191, size: 64, align: 64, offset: 192)
!709 = !DIDerivedType(tag: DW_TAG_member, name: "out", scope: !649, file: !130, line: 1565, baseType: !148, size: 64, align: 64, offset: 256)
!710 = !DIDerivedType(tag: DW_TAG_member, name: "in_set", scope: !649, file: !130, line: 1566, baseType: !148, size: 64, align: 64, offset: 320)
!711 = !DIDerivedType(tag: DW_TAG_member, name: "writeheader", scope: !649, file: !130, line: 1567, baseType: !148, size: 64, align: 64, offset: 384)
!712 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_out", scope: !649, file: !130, line: 1568, baseType: !148, size: 64, align: 64, offset: 448)
!713 = !DIDerivedType(tag: DW_TAG_member, name: "use_port", scope: !649, file: !130, line: 1569, baseType: !191, size: 64, align: 64, offset: 512)
!714 = !DIDerivedType(tag: DW_TAG_member, name: "httpauth", scope: !649, file: !130, line: 1570, baseType: !160, size: 64, align: 64, offset: 576)
!715 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauth", scope: !649, file: !130, line: 1571, baseType: !160, size: 64, align: 64, offset: 640)
!716 = !DIDerivedType(tag: DW_TAG_member, name: "followlocation", scope: !649, file: !130, line: 1572, baseType: !191, size: 64, align: 64, offset: 704)
!717 = !DIDerivedType(tag: DW_TAG_member, name: "maxredirs", scope: !649, file: !130, line: 1573, baseType: !191, size: 64, align: 64, offset: 768)
!718 = !DIDerivedType(tag: DW_TAG_member, name: "keep_post", scope: !649, file: !130, line: 1576, baseType: !177, size: 32, align: 32, offset: 832)
!719 = !DIDerivedType(tag: DW_TAG_member, name: "free_referer", scope: !649, file: !130, line: 1578, baseType: !211, size: 8, align: 8, offset: 864)
!720 = !DIDerivedType(tag: DW_TAG_member, name: "postfields", scope: !649, file: !130, line: 1580, baseType: !148, size: 64, align: 64, offset: 896)
!721 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !649, file: !130, line: 1581, baseType: !722, size: 64, align: 64, offset: 960)
!722 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_seek_callback", file: !4, line: 324, baseType: !723)
!723 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !724, size: 64, align: 64)
!724 = !DISubroutineType(types: !725)
!725 = !{!177, !148, !189, !177}
!726 = !DIDerivedType(tag: DW_TAG_member, name: "postfieldsize", scope: !649, file: !130, line: 1582, baseType: !189, size: 64, align: 64, offset: 1024)
!727 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !649, file: !130, line: 1585, baseType: !684, size: 16, align: 16, offset: 1088)
!728 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !649, file: !130, line: 1586, baseType: !177, size: 32, align: 32, offset: 1120)
!729 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_func", scope: !649, file: !130, line: 1588, baseType: !730, size: 64, align: 64, offset: 1152)
!730 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_write_callback", file: !4, line: 223, baseType: !731)
!731 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !732, size: 64, align: 64)
!732 = !DISubroutineType(types: !733)
!733 = !{!158, !215, !158, !158, !148}
!734 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_header", scope: !649, file: !130, line: 1589, baseType: !730, size: 64, align: 64, offset: 1216)
!735 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_rtp", scope: !649, file: !130, line: 1590, baseType: !730, size: 64, align: 64, offset: 1280)
!736 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func_set", scope: !649, file: !130, line: 1591, baseType: !737, size: 64, align: 64, offset: 1344)
!737 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_read_callback", file: !4, line: 335, baseType: !731)
!738 = !DIDerivedType(tag: DW_TAG_member, name: "is_fread_set", scope: !649, file: !130, line: 1592, baseType: !177, size: 32, align: 32, offset: 1408)
!739 = !DIDerivedType(tag: DW_TAG_member, name: "is_fwrite_set", scope: !649, file: !130, line: 1593, baseType: !177, size: 32, align: 32, offset: 1440)
!740 = !DIDerivedType(tag: DW_TAG_member, name: "fprogress", scope: !649, file: !130, line: 1594, baseType: !741, size: 64, align: 64, offset: 1472)
!741 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_progress_callback", file: !4, line: 183, baseType: !742)
!742 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !743, size: 64, align: 64)
!743 = !DISubroutineType(types: !744)
!744 = !{!177, !148, !745, !745, !745, !745}
!745 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!746 = !DIDerivedType(tag: DW_TAG_member, name: "fxferinfo", scope: !649, file: !130, line: 1595, baseType: !747, size: 64, align: 64, offset: 1536)
!747 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_xferinfo_callback", file: !4, line: 191, baseType: !748)
!748 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !749, size: 64, align: 64)
!749 = !DISubroutineType(types: !750)
!750 = !{!177, !148, !189, !189, !189, !189}
!751 = !DIDerivedType(tag: DW_TAG_member, name: "fdebug", scope: !649, file: !130, line: 1596, baseType: !752, size: 64, align: 64, offset: 1600)
!752 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_debug_callback", file: !4, line: 420, baseType: !753)
!753 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !754, size: 64, align: 64)
!754 = !DISubroutineType(types: !755)
!755 = !{!177, !564, !756, !215, !158, !148}
!756 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_infotype", file: !4, line: 418, baseType: !269)
!757 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_func", scope: !649, file: !130, line: 1597, baseType: !758, size: 64, align: 64, offset: 1664)
!758 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ioctl_callback", file: !4, line: 388, baseType: !759)
!759 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !760, size: 64, align: 64)
!760 = !DISubroutineType(types: !761)
!761 = !{!762, !564, !177, !148}
!762 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlioerr", file: !4, line: 380, baseType: !279)
!763 = !DIDerivedType(tag: DW_TAG_member, name: "fsockopt", scope: !649, file: !130, line: 1598, baseType: !764, size: 64, align: 64, offset: 1728)
!764 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sockopt_callback", file: !4, line: 353, baseType: !765)
!765 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !766, size: 64, align: 64)
!766 = !DISubroutineType(types: !767)
!767 = !{!177, !148, !248, !768}
!768 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlsocktype", file: !4, line: 344, baseType: !285)
!769 = !DIDerivedType(tag: DW_TAG_member, name: "sockopt_client", scope: !649, file: !130, line: 1599, baseType: !148, size: 64, align: 64, offset: 1792)
!770 = !DIDerivedType(tag: DW_TAG_member, name: "fopensocket", scope: !649, file: !130, line: 1600, baseType: !771, size: 64, align: 64, offset: 1856)
!771 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_opensocket_callback", file: !4, line: 368, baseType: !772)
!772 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !773, size: 64, align: 64)
!773 = !DISubroutineType(types: !774)
!774 = !{!248, !148, !768, !775}
!775 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !776, size: 64, align: 64)
!776 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_sockaddr", file: !4, line: 357, size: 256, align: 32, elements: !777)
!777 = !{!778, !779, !780, !781, !783}
!778 = !DIDerivedType(tag: DW_TAG_member, name: "family", scope: !776, file: !4, line: 358, baseType: !177, size: 32, align: 32)
!779 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !776, file: !4, line: 359, baseType: !177, size: 32, align: 32, offset: 32)
!780 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !776, file: !4, line: 360, baseType: !177, size: 32, align: 32, offset: 64)
!781 = !DIDerivedType(tag: DW_TAG_member, name: "addrlen", scope: !776, file: !4, line: 361, baseType: !782, size: 32, align: 32, offset: 96)
!782 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!783 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !776, file: !4, line: 364, baseType: !784, size: 128, align: 16, offset: 128)
!784 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !785, line: 149, size: 128, align: 16, elements: !786)
!785 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!786 = !{!787, !790}
!787 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !784, file: !785, line: 151, baseType: !788, size: 16, align: 16)
!788 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !789, line: 28, baseType: !684)
!789 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!790 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !784, file: !785, line: 152, baseType: !791, size: 112, align: 8, offset: 16)
!791 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 112, align: 8, elements: !792)
!792 = !{!793}
!793 = !DISubrange(count: 14)
!794 = !DIDerivedType(tag: DW_TAG_member, name: "opensocket_client", scope: !649, file: !130, line: 1603, baseType: !148, size: 64, align: 64, offset: 1920)
!795 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !649, file: !130, line: 1604, baseType: !796, size: 64, align: 64, offset: 1984)
!796 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_closesocket_callback", file: !4, line: 373, baseType: !797)
!797 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !798, size: 64, align: 64)
!798 = !DISubroutineType(types: !799)
!799 = !{!177, !148, !248}
!800 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !649, file: !130, line: 1606, baseType: !148, size: 64, align: 64, offset: 2048)
!801 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !649, file: !130, line: 1608, baseType: !148, size: 64, align: 64, offset: 2112)
!802 = !DIDerivedType(tag: DW_TAG_member, name: "convfromnetwork", scope: !649, file: !130, line: 1611, baseType: !803, size: 64, align: 64, offset: 2176)
!803 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_conv_callback", file: !4, line: 637, baseType: !804)
!804 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !805, size: 64, align: 64)
!805 = !DISubroutineType(types: !806)
!806 = !{!554, !215, !158}
!807 = !DIDerivedType(tag: DW_TAG_member, name: "convtonetwork", scope: !649, file: !130, line: 1613, baseType: !803, size: 64, align: 64, offset: 2240)
!808 = !DIDerivedType(tag: DW_TAG_member, name: "convfromutf8", scope: !649, file: !130, line: 1615, baseType: !803, size: 64, align: 64, offset: 2304)
!809 = !DIDerivedType(tag: DW_TAG_member, name: "progress_client", scope: !649, file: !130, line: 1617, baseType: !148, size: 64, align: 64, offset: 2368)
!810 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_client", scope: !649, file: !130, line: 1618, baseType: !148, size: 64, align: 64, offset: 2432)
!811 = !DIDerivedType(tag: DW_TAG_member, name: "timeout", scope: !649, file: !130, line: 1619, baseType: !191, size: 64, align: 64, offset: 2496)
!812 = !DIDerivedType(tag: DW_TAG_member, name: "connecttimeout", scope: !649, file: !130, line: 1620, baseType: !191, size: 64, align: 64, offset: 2560)
!813 = !DIDerivedType(tag: DW_TAG_member, name: "accepttimeout", scope: !649, file: !130, line: 1621, baseType: !191, size: 64, align: 64, offset: 2624)
!814 = !DIDerivedType(tag: DW_TAG_member, name: "server_response_timeout", scope: !649, file: !130, line: 1622, baseType: !191, size: 64, align: 64, offset: 2688)
!815 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_blksize", scope: !649, file: !130, line: 1623, baseType: !191, size: 64, align: 64, offset: 2752)
!816 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_no_options", scope: !649, file: !130, line: 1624, baseType: !211, size: 8, align: 8, offset: 2816)
!817 = !DIDerivedType(tag: DW_TAG_member, name: "filesize", scope: !649, file: !130, line: 1625, baseType: !189, size: 64, align: 64, offset: 2880)
!818 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_limit", scope: !649, file: !130, line: 1626, baseType: !191, size: 64, align: 64, offset: 2944)
!819 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_time", scope: !649, file: !130, line: 1627, baseType: !191, size: 64, align: 64, offset: 3008)
!820 = !DIDerivedType(tag: DW_TAG_member, name: "max_send_speed", scope: !649, file: !130, line: 1628, baseType: !189, size: 64, align: 64, offset: 3072)
!821 = !DIDerivedType(tag: DW_TAG_member, name: "max_recv_speed", scope: !649, file: !130, line: 1629, baseType: !189, size: 64, align: 64, offset: 3136)
!822 = !DIDerivedType(tag: DW_TAG_member, name: "set_resume_from", scope: !649, file: !130, line: 1631, baseType: !189, size: 64, align: 64, offset: 3200)
!823 = !DIDerivedType(tag: DW_TAG_member, name: "headers", scope: !649, file: !130, line: 1632, baseType: !824, size: 64, align: 64, offset: 3264)
!824 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !825, size: 64, align: 64)
!825 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_slist", file: !4, line: 2176, size: 128, align: 64, elements: !826)
!826 = !{!827, !828}
!827 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !825, file: !4, line: 2177, baseType: !215, size: 64, align: 64)
!828 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !825, file: !4, line: 2178, baseType: !824, size: 64, align: 64, offset: 64)
!829 = !DIDerivedType(tag: DW_TAG_member, name: "proxyheaders", scope: !649, file: !130, line: 1633, baseType: !824, size: 64, align: 64, offset: 3328)
!830 = !DIDerivedType(tag: DW_TAG_member, name: "httppost", scope: !649, file: !130, line: 1634, baseType: !831, size: 64, align: 64, offset: 3392)
!831 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !832, size: 64, align: 64)
!832 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_httppost", file: !4, line: 137, size: 896, align: 64, elements: !833)
!833 = !{!834, !835, !836, !837, !838, !839, !840, !841, !842, !843, !844, !845, !846, !847}
!834 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !832, file: !4, line: 138, baseType: !831, size: 64, align: 64)
!835 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !832, file: !4, line: 139, baseType: !215, size: 64, align: 64, offset: 64)
!836 = !DIDerivedType(tag: DW_TAG_member, name: "namelength", scope: !832, file: !4, line: 140, baseType: !191, size: 64, align: 64, offset: 128)
!837 = !DIDerivedType(tag: DW_TAG_member, name: "contents", scope: !832, file: !4, line: 141, baseType: !215, size: 64, align: 64, offset: 192)
!838 = !DIDerivedType(tag: DW_TAG_member, name: "contentslength", scope: !832, file: !4, line: 142, baseType: !191, size: 64, align: 64, offset: 256)
!839 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !832, file: !4, line: 144, baseType: !215, size: 64, align: 64, offset: 320)
!840 = !DIDerivedType(tag: DW_TAG_member, name: "bufferlength", scope: !832, file: !4, line: 145, baseType: !191, size: 64, align: 64, offset: 384)
!841 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !832, file: !4, line: 146, baseType: !215, size: 64, align: 64, offset: 448)
!842 = !DIDerivedType(tag: DW_TAG_member, name: "contentheader", scope: !832, file: !4, line: 147, baseType: !824, size: 64, align: 64, offset: 512)
!843 = !DIDerivedType(tag: DW_TAG_member, name: "more", scope: !832, file: !4, line: 148, baseType: !831, size: 64, align: 64, offset: 576)
!844 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !832, file: !4, line: 151, baseType: !191, size: 64, align: 64, offset: 640)
!845 = !DIDerivedType(tag: DW_TAG_member, name: "showfilename", scope: !832, file: !4, line: 171, baseType: !215, size: 64, align: 64, offset: 704)
!846 = !DIDerivedType(tag: DW_TAG_member, name: "userp", scope: !832, file: !4, line: 174, baseType: !148, size: 64, align: 64, offset: 768)
!847 = !DIDerivedType(tag: DW_TAG_member, name: "contentlen", scope: !832, file: !4, line: 176, baseType: !189, size: 64, align: 64, offset: 832)
!848 = !DIDerivedType(tag: DW_TAG_member, name: "sep_headers", scope: !649, file: !130, line: 1635, baseType: !211, size: 8, align: 8, offset: 3456)
!849 = !DIDerivedType(tag: DW_TAG_member, name: "cookiesession", scope: !649, file: !130, line: 1636, baseType: !211, size: 8, align: 8, offset: 3464)
!850 = !DIDerivedType(tag: DW_TAG_member, name: "crlf", scope: !649, file: !130, line: 1637, baseType: !211, size: 8, align: 8, offset: 3472)
!851 = !DIDerivedType(tag: DW_TAG_member, name: "quote", scope: !649, file: !130, line: 1638, baseType: !824, size: 64, align: 64, offset: 3520)
!852 = !DIDerivedType(tag: DW_TAG_member, name: "postquote", scope: !649, file: !130, line: 1639, baseType: !824, size: 64, align: 64, offset: 3584)
!853 = !DIDerivedType(tag: DW_TAG_member, name: "prequote", scope: !649, file: !130, line: 1640, baseType: !824, size: 64, align: 64, offset: 3648)
!854 = !DIDerivedType(tag: DW_TAG_member, name: "source_quote", scope: !649, file: !130, line: 1641, baseType: !824, size: 64, align: 64, offset: 3712)
!855 = !DIDerivedType(tag: DW_TAG_member, name: "source_prequote", scope: !649, file: !130, line: 1642, baseType: !824, size: 64, align: 64, offset: 3776)
!856 = !DIDerivedType(tag: DW_TAG_member, name: "source_postquote", scope: !649, file: !130, line: 1644, baseType: !824, size: 64, align: 64, offset: 3840)
!857 = !DIDerivedType(tag: DW_TAG_member, name: "telnet_options", scope: !649, file: !130, line: 1646, baseType: !824, size: 64, align: 64, offset: 3904)
!858 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !649, file: !130, line: 1647, baseType: !824, size: 64, align: 64, offset: 3968)
!859 = !DIDerivedType(tag: DW_TAG_member, name: "connect_to", scope: !649, file: !130, line: 1649, baseType: !824, size: 64, align: 64, offset: 4032)
!860 = !DIDerivedType(tag: DW_TAG_member, name: "timecondition", scope: !649, file: !130, line: 1651, baseType: !861, size: 32, align: 32, offset: 4096)
!861 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_TimeCond", file: !4, line: 1929, baseType: !290)
!862 = !DIDerivedType(tag: DW_TAG_member, name: "timevalue", scope: !649, file: !130, line: 1652, baseType: !242, size: 64, align: 64, offset: 4160)
!863 = !DIDerivedType(tag: DW_TAG_member, name: "httpreq", scope: !649, file: !130, line: 1653, baseType: !864, size: 32, align: 32, offset: 4224)
!864 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_HttpReq", file: !130, line: 1249, baseType: !297)
!865 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !649, file: !130, line: 1654, baseType: !191, size: 64, align: 64, offset: 4288)
!866 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !649, file: !130, line: 1656, baseType: !867, size: 1408, align: 64, offset: 4352)
!867 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_config_data", file: !130, line: 366, size: 1408, align: 64, elements: !868)
!868 = !{!869, !884, !885, !886, !887, !888, !889, !894, !895, !896, !897, !898, !899, !900, !901}
!869 = !DIDerivedType(tag: DW_TAG_member, name: "primary", scope: !867, file: !130, line: 367, baseType: !870, size: 640, align: 64)
!870 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_primary_config", file: !130, line: 351, size: 640, align: 64, elements: !871)
!871 = !{!872, !873, !874, !875, !876, !877, !878, !879, !880, !881, !882, !883}
!872 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !870, file: !130, line: 352, baseType: !191, size: 64, align: 64)
!873 = !DIDerivedType(tag: DW_TAG_member, name: "version_max", scope: !870, file: !130, line: 353, baseType: !191, size: 64, align: 64, offset: 64)
!874 = !DIDerivedType(tag: DW_TAG_member, name: "verifypeer", scope: !870, file: !130, line: 354, baseType: !211, size: 8, align: 8, offset: 128)
!875 = !DIDerivedType(tag: DW_TAG_member, name: "verifyhost", scope: !870, file: !130, line: 355, baseType: !211, size: 8, align: 8, offset: 136)
!876 = !DIDerivedType(tag: DW_TAG_member, name: "verifystatus", scope: !870, file: !130, line: 356, baseType: !211, size: 8, align: 8, offset: 144)
!877 = !DIDerivedType(tag: DW_TAG_member, name: "CApath", scope: !870, file: !130, line: 357, baseType: !215, size: 64, align: 64, offset: 192)
!878 = !DIDerivedType(tag: DW_TAG_member, name: "CAfile", scope: !870, file: !130, line: 358, baseType: !215, size: 64, align: 64, offset: 256)
!879 = !DIDerivedType(tag: DW_TAG_member, name: "clientcert", scope: !870, file: !130, line: 359, baseType: !215, size: 64, align: 64, offset: 320)
!880 = !DIDerivedType(tag: DW_TAG_member, name: "random_file", scope: !870, file: !130, line: 360, baseType: !215, size: 64, align: 64, offset: 384)
!881 = !DIDerivedType(tag: DW_TAG_member, name: "egdsocket", scope: !870, file: !130, line: 361, baseType: !215, size: 64, align: 64, offset: 448)
!882 = !DIDerivedType(tag: DW_TAG_member, name: "cipher_list", scope: !870, file: !130, line: 362, baseType: !215, size: 64, align: 64, offset: 512)
!883 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !870, file: !130, line: 363, baseType: !211, size: 8, align: 8, offset: 576)
!884 = !DIDerivedType(tag: DW_TAG_member, name: "enable_beast", scope: !867, file: !130, line: 368, baseType: !211, size: 8, align: 8, offset: 640)
!885 = !DIDerivedType(tag: DW_TAG_member, name: "no_revoke", scope: !867, file: !130, line: 370, baseType: !211, size: 8, align: 8, offset: 648)
!886 = !DIDerivedType(tag: DW_TAG_member, name: "certverifyresult", scope: !867, file: !130, line: 371, baseType: !191, size: 64, align: 64, offset: 704)
!887 = !DIDerivedType(tag: DW_TAG_member, name: "CRLfile", scope: !867, file: !130, line: 372, baseType: !215, size: 64, align: 64, offset: 768)
!888 = !DIDerivedType(tag: DW_TAG_member, name: "issuercert", scope: !867, file: !130, line: 373, baseType: !215, size: 64, align: 64, offset: 832)
!889 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctx", scope: !867, file: !130, line: 374, baseType: !890, size: 64, align: 64, offset: 896)
!890 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ssl_ctx_callback", file: !4, line: 639, baseType: !891)
!891 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !892, size: 64, align: 64)
!892 = !DISubroutineType(types: !893)
!893 = !{!554, !564, !148, !148}
!894 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctxp", scope: !867, file: !130, line: 375, baseType: !148, size: 64, align: 64, offset: 960)
!895 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !867, file: !130, line: 376, baseType: !211, size: 8, align: 8, offset: 1024)
!896 = !DIDerivedType(tag: DW_TAG_member, name: "falsestart", scope: !867, file: !130, line: 377, baseType: !211, size: 8, align: 8, offset: 1032)
!897 = !DIDerivedType(tag: DW_TAG_member, name: "cert", scope: !867, file: !130, line: 379, baseType: !215, size: 64, align: 64, offset: 1088)
!898 = !DIDerivedType(tag: DW_TAG_member, name: "cert_type", scope: !867, file: !130, line: 380, baseType: !215, size: 64, align: 64, offset: 1152)
!899 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !867, file: !130, line: 381, baseType: !215, size: 64, align: 64, offset: 1216)
!900 = !DIDerivedType(tag: DW_TAG_member, name: "key_type", scope: !867, file: !130, line: 382, baseType: !215, size: 64, align: 64, offset: 1280)
!901 = !DIDerivedType(tag: DW_TAG_member, name: "key_passwd", scope: !867, file: !130, line: 383, baseType: !215, size: 64, align: 64, offset: 1344)
!902 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !649, file: !130, line: 1657, baseType: !867, size: 1408, align: 64, offset: 5760)
!903 = !DIDerivedType(tag: DW_TAG_member, name: "general_ssl", scope: !649, file: !130, line: 1658, baseType: !904, size: 64, align: 64, offset: 7168)
!904 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_general_config", file: !130, line: 392, size: 64, align: 64, elements: !905)
!905 = !{!906}
!906 = !DIDerivedType(tag: DW_TAG_member, name: "max_ssl_sessions", scope: !904, file: !130, line: 393, baseType: !158, size: 64, align: 64)
!907 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !649, file: !130, line: 1659, baseType: !908, size: 32, align: 32, offset: 7232)
!908 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_proxytype", file: !4, line: 657, baseType: !307)
!909 = !DIDerivedType(tag: DW_TAG_member, name: "dns_cache_timeout", scope: !649, file: !130, line: 1660, baseType: !191, size: 64, align: 64, offset: 7296)
!910 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !649, file: !130, line: 1661, baseType: !191, size: 64, align: 64, offset: 7360)
!911 = !DIDerivedType(tag: DW_TAG_member, name: "private_data", scope: !649, file: !130, line: 1662, baseType: !148, size: 64, align: 64, offset: 7424)
!912 = !DIDerivedType(tag: DW_TAG_member, name: "http200aliases", scope: !649, file: !130, line: 1664, baseType: !824, size: 64, align: 64, offset: 7488)
!913 = !DIDerivedType(tag: DW_TAG_member, name: "ipver", scope: !649, file: !130, line: 1666, baseType: !191, size: 64, align: 64, offset: 7552)
!914 = !DIDerivedType(tag: DW_TAG_member, name: "max_filesize", scope: !649, file: !130, line: 1669, baseType: !189, size: 64, align: 64, offset: 7616)
!915 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_filemethod", scope: !649, file: !130, line: 1671, baseType: !916, size: 32, align: 32, offset: 7680)
!916 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpfile", file: !317, line: 98, baseType: !316)
!917 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_create_missing_dirs", scope: !649, file: !130, line: 1673, baseType: !177, size: 32, align: 32, offset: 7712)
!918 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc", scope: !649, file: !130, line: 1677, baseType: !919, size: 64, align: 64, offset: 7744)
!919 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sshkeycallback", file: !4, line: 739, baseType: !920)
!920 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !921, size: 64, align: 64)
!921 = !DISubroutineType(types: !922)
!922 = !{!177, !564, !923, !923, !328, !148}
!923 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !924, size: 64, align: 64)
!924 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !925)
!925 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_khkey", file: !4, line: 711, size: 192, align: 64, elements: !926)
!926 = !{!927, !930, !931}
!927 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !925, file: !4, line: 712, baseType: !928, size: 64, align: 64)
!928 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !929, size: 64, align: 64)
!929 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !216)
!930 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !925, file: !4, line: 714, baseType: !158, size: 64, align: 64, offset: 64)
!931 = !DIDerivedType(tag: DW_TAG_member, name: "keytype", scope: !925, file: !4, line: 715, baseType: !322, size: 32, align: 32, offset: 128)
!932 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc_userp", scope: !649, file: !130, line: 1678, baseType: !148, size: 64, align: 64, offset: 7808)
!933 = !DIDerivedType(tag: DW_TAG_member, name: "printhost", scope: !649, file: !130, line: 1684, baseType: !211, size: 8, align: 8, offset: 7872)
!934 = !DIDerivedType(tag: DW_TAG_member, name: "get_filetime", scope: !649, file: !130, line: 1685, baseType: !211, size: 8, align: 8, offset: 7880)
!935 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_thru_httpproxy", scope: !649, file: !130, line: 1686, baseType: !211, size: 8, align: 8, offset: 7888)
!936 = !DIDerivedType(tag: DW_TAG_member, name: "prefer_ascii", scope: !649, file: !130, line: 1687, baseType: !211, size: 8, align: 8, offset: 7896)
!937 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_append", scope: !649, file: !130, line: 1688, baseType: !211, size: 8, align: 8, offset: 7904)
!938 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_list_only", scope: !649, file: !130, line: 1689, baseType: !211, size: 8, align: 8, offset: 7912)
!939 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_port", scope: !649, file: !130, line: 1690, baseType: !211, size: 8, align: 8, offset: 7920)
!940 = !DIDerivedType(tag: DW_TAG_member, name: "hide_progress", scope: !649, file: !130, line: 1691, baseType: !211, size: 8, align: 8, offset: 7928)
!941 = !DIDerivedType(tag: DW_TAG_member, name: "http_fail_on_error", scope: !649, file: !130, line: 1692, baseType: !211, size: 8, align: 8, offset: 7936)
!942 = !DIDerivedType(tag: DW_TAG_member, name: "http_keep_sending_on_error", scope: !649, file: !130, line: 1693, baseType: !211, size: 8, align: 8, offset: 7944)
!943 = !DIDerivedType(tag: DW_TAG_member, name: "http_follow_location", scope: !649, file: !130, line: 1694, baseType: !211, size: 8, align: 8, offset: 7952)
!944 = !DIDerivedType(tag: DW_TAG_member, name: "http_transfer_encoding", scope: !649, file: !130, line: 1695, baseType: !211, size: 8, align: 8, offset: 7960)
!945 = !DIDerivedType(tag: DW_TAG_member, name: "http_disable_hostname_check_before_authentication", scope: !649, file: !130, line: 1696, baseType: !211, size: 8, align: 8, offset: 7968)
!946 = !DIDerivedType(tag: DW_TAG_member, name: "include_header", scope: !649, file: !130, line: 1697, baseType: !211, size: 8, align: 8, offset: 7976)
!947 = !DIDerivedType(tag: DW_TAG_member, name: "http_set_referer", scope: !649, file: !130, line: 1698, baseType: !211, size: 8, align: 8, offset: 7984)
!948 = !DIDerivedType(tag: DW_TAG_member, name: "http_auto_referer", scope: !649, file: !130, line: 1699, baseType: !211, size: 8, align: 8, offset: 7992)
!949 = !DIDerivedType(tag: DW_TAG_member, name: "opt_no_body", scope: !649, file: !130, line: 1700, baseType: !211, size: 8, align: 8, offset: 8000)
!950 = !DIDerivedType(tag: DW_TAG_member, name: "upload", scope: !649, file: !130, line: 1701, baseType: !211, size: 8, align: 8, offset: 8008)
!951 = !DIDerivedType(tag: DW_TAG_member, name: "use_netrc", scope: !649, file: !130, line: 1703, baseType: !334, size: 32, align: 32, offset: 8032)
!952 = !DIDerivedType(tag: DW_TAG_member, name: "verbose", scope: !649, file: !130, line: 1704, baseType: !211, size: 8, align: 8, offset: 8064)
!953 = !DIDerivedType(tag: DW_TAG_member, name: "krb", scope: !649, file: !130, line: 1705, baseType: !211, size: 8, align: 8, offset: 8072)
!954 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_forbid", scope: !649, file: !130, line: 1706, baseType: !211, size: 8, align: 8, offset: 8080)
!955 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_fresh", scope: !649, file: !130, line: 1707, baseType: !211, size: 8, align: 8, offset: 8088)
!956 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !649, file: !130, line: 1708, baseType: !211, size: 8, align: 8, offset: 8096)
!957 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !649, file: !130, line: 1709, baseType: !211, size: 8, align: 8, offset: 8104)
!958 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_pret", scope: !649, file: !130, line: 1710, baseType: !211, size: 8, align: 8, offset: 8112)
!959 = !DIDerivedType(tag: DW_TAG_member, name: "use_ssl", scope: !649, file: !130, line: 1712, baseType: !960, size: 32, align: 32, offset: 8128)
!960 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_usessl", file: !4, line: 752, baseType: !340)
!961 = !DIDerivedType(tag: DW_TAG_member, name: "ftpsslauth", scope: !649, file: !130, line: 1714, baseType: !962, size: 32, align: 32, offset: 8160)
!962 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpauth", file: !4, line: 795, baseType: !347)
!963 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_ccc", scope: !649, file: !130, line: 1715, baseType: !964, size: 32, align: 32, offset: 8192)
!964 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpccc", file: !4, line: 787, baseType: !353)
!965 = !DIDerivedType(tag: DW_TAG_member, name: "no_signal", scope: !649, file: !130, line: 1716, baseType: !211, size: 8, align: 8, offset: 8224)
!966 = !DIDerivedType(tag: DW_TAG_member, name: "global_dns_cache", scope: !649, file: !130, line: 1717, baseType: !211, size: 8, align: 8, offset: 8232)
!967 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_nodelay", scope: !649, file: !130, line: 1718, baseType: !211, size: 8, align: 8, offset: 8240)
!968 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !649, file: !130, line: 1719, baseType: !211, size: 8, align: 8, offset: 8248)
!969 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_skip_ip", scope: !649, file: !130, line: 1720, baseType: !211, size: 8, align: 8, offset: 8256)
!970 = !DIDerivedType(tag: DW_TAG_member, name: "connect_only", scope: !649, file: !130, line: 1722, baseType: !211, size: 8, align: 8, offset: 8264)
!971 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_auth_types", scope: !649, file: !130, line: 1723, baseType: !191, size: 64, align: 64, offset: 8320)
!972 = !DIDerivedType(tag: DW_TAG_member, name: "http_te_skip", scope: !649, file: !130, line: 1724, baseType: !211, size: 8, align: 8, offset: 8384)
!973 = !DIDerivedType(tag: DW_TAG_member, name: "http_ce_skip", scope: !649, file: !130, line: 1726, baseType: !211, size: 8, align: 8, offset: 8392)
!974 = !DIDerivedType(tag: DW_TAG_member, name: "new_file_perms", scope: !649, file: !130, line: 1728, baseType: !191, size: 64, align: 64, offset: 8448)
!975 = !DIDerivedType(tag: DW_TAG_member, name: "new_directory_perms", scope: !649, file: !130, line: 1729, baseType: !191, size: 64, align: 64, offset: 8512)
!976 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_transfer_mode", scope: !649, file: !130, line: 1730, baseType: !211, size: 8, align: 8, offset: 8576)
!977 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !649, file: !130, line: 1732, baseType: !978, size: 3584, align: 64, offset: 8640)
!978 = !DICompositeType(tag: DW_TAG_array_type, baseType: !215, size: 3584, align: 64, elements: !979)
!979 = !{!980}
!980 = !DISubrange(count: 56)
!981 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !649, file: !130, line: 1733, baseType: !782, size: 32, align: 32, offset: 12224)
!982 = !DIDerivedType(tag: DW_TAG_member, name: "allowed_protocols", scope: !649, file: !130, line: 1734, baseType: !191, size: 64, align: 64, offset: 12288)
!983 = !DIDerivedType(tag: DW_TAG_member, name: "redir_protocols", scope: !649, file: !130, line: 1735, baseType: !191, size: 64, align: 64, offset: 12352)
!984 = !DIDerivedType(tag: DW_TAG_member, name: "mail_rcpt", scope: !649, file: !130, line: 1739, baseType: !824, size: 64, align: 64, offset: 12416)
!985 = !DIDerivedType(tag: DW_TAG_member, name: "sasl_ir", scope: !649, file: !130, line: 1740, baseType: !211, size: 8, align: 8, offset: 12480)
!986 = !DIDerivedType(tag: DW_TAG_member, name: "rtspreq", scope: !649, file: !130, line: 1742, baseType: !987, size: 32, align: 32, offset: 12512)
!987 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_RtspReq", file: !130, line: 1265, baseType: !359)
!988 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !649, file: !130, line: 1743, baseType: !191, size: 64, align: 64, offset: 12544)
!989 = !DIDerivedType(tag: DW_TAG_member, name: "wildcardmatch", scope: !649, file: !130, line: 1744, baseType: !211, size: 8, align: 8, offset: 12608)
!990 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_bgn", scope: !649, file: !130, line: 1745, baseType: !991, size: 64, align: 64, offset: 12672)
!991 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_bgn_callback", file: !4, line: 292, baseType: !992)
!992 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !993, size: 64, align: 64)
!993 = !DISubroutineType(types: !994)
!994 = !{!191, !995, !148, !177}
!995 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !996, size: 64, align: 64)
!996 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!997 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_end", scope: !649, file: !130, line: 1747, baseType: !998, size: 64, align: 64, offset: 12736)
!998 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_end_callback", file: !4, line: 306, baseType: !999)
!999 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1000, size: 64, align: 64)
!1000 = !DISubroutineType(types: !1001)
!1001 = !{!191, !148}
!1002 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch", scope: !649, file: !130, line: 1749, baseType: !1003, size: 64, align: 64, offset: 12800)
!1003 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_fnmatch_callback", file: !4, line: 315, baseType: !1004)
!1004 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1005, size: 64, align: 64)
!1005 = !DISubroutineType(types: !1006)
!1006 = !{!177, !148, !928, !928}
!1007 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch_data", scope: !649, file: !130, line: 1751, baseType: !148, size: 64, align: 64, offset: 12864)
!1008 = !DIDerivedType(tag: DW_TAG_member, name: "gssapi_delegation", scope: !649, file: !130, line: 1753, baseType: !191, size: 64, align: 64, offset: 12928)
!1009 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepalive", scope: !649, file: !130, line: 1756, baseType: !211, size: 8, align: 8, offset: 12992)
!1010 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepidle", scope: !649, file: !130, line: 1757, baseType: !191, size: 64, align: 64, offset: 13056)
!1011 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepintvl", scope: !649, file: !130, line: 1758, baseType: !191, size: 64, align: 64, offset: 13120)
!1012 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !649, file: !130, line: 1759, baseType: !211, size: 8, align: 8, offset: 13184)
!1013 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !649, file: !130, line: 1761, baseType: !158, size: 64, align: 64, offset: 13248)
!1014 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_npn", scope: !649, file: !130, line: 1763, baseType: !211, size: 8, align: 8, offset: 13312)
!1015 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_alpn", scope: !649, file: !130, line: 1764, baseType: !211, size: 8, align: 8, offset: 13320)
!1016 = !DIDerivedType(tag: DW_TAG_member, name: "path_as_is", scope: !649, file: !130, line: 1765, baseType: !211, size: 8, align: 8, offset: 13328)
!1017 = !DIDerivedType(tag: DW_TAG_member, name: "pipewait", scope: !649, file: !130, line: 1766, baseType: !211, size: 8, align: 8, offset: 13336)
!1018 = !DIDerivedType(tag: DW_TAG_member, name: "expect_100_timeout", scope: !649, file: !130, line: 1768, baseType: !191, size: 64, align: 64, offset: 13376)
!1019 = !DIDerivedType(tag: DW_TAG_member, name: "suppress_connect_headers", scope: !649, file: !130, line: 1769, baseType: !211, size: 8, align: 8, offset: 13440)
!1020 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !649, file: !130, line: 1772, baseType: !544, size: 64, align: 64, offset: 13504)
!1021 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !649, file: !130, line: 1773, baseType: !211, size: 8, align: 8, offset: 13568)
!1022 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !649, file: !130, line: 1774, baseType: !177, size: 32, align: 32, offset: 13600)
!1023 = !DIDerivedType(tag: DW_TAG_member, name: "stream_dependents", scope: !649, file: !130, line: 1776, baseType: !1024, size: 64, align: 64, offset: 13632)
!1024 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1025, size: 64, align: 64)
!1025 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_http2_dep", file: !130, line: 1292, size: 128, align: 64, elements: !1026)
!1026 = !{!1027, !1028}
!1027 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1025, file: !130, line: 1293, baseType: !1024, size: 64, align: 64)
!1028 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !1025, file: !130, line: 1294, baseType: !544, size: 64, align: 64, offset: 64)
!1029 = !DIDerivedType(tag: DW_TAG_member, name: "abstract_unix_socket", scope: !649, file: !130, line: 1778, baseType: !211, size: 8, align: 8, offset: 13696)
!1030 = !DIDerivedType(tag: DW_TAG_member, name: "change", scope: !545, file: !130, line: 1830, baseType: !1031, size: 384, align: 64, offset: 17216)
!1031 = !DICompositeType(tag: DW_TAG_structure_type, name: "DynamicStatic", file: !130, line: 1444, size: 384, align: 64, elements: !1032)
!1032 = !{!1033, !1034, !1035, !1036, !1037, !1038}
!1033 = !DIDerivedType(tag: DW_TAG_member, name: "url", scope: !1031, file: !130, line: 1445, baseType: !215, size: 64, align: 64)
!1034 = !DIDerivedType(tag: DW_TAG_member, name: "url_alloc", scope: !1031, file: !130, line: 1446, baseType: !211, size: 8, align: 8, offset: 64)
!1035 = !DIDerivedType(tag: DW_TAG_member, name: "referer", scope: !1031, file: !130, line: 1447, baseType: !215, size: 64, align: 64, offset: 128)
!1036 = !DIDerivedType(tag: DW_TAG_member, name: "referer_alloc", scope: !1031, file: !130, line: 1448, baseType: !211, size: 8, align: 8, offset: 192)
!1037 = !DIDerivedType(tag: DW_TAG_member, name: "cookielist", scope: !1031, file: !130, line: 1449, baseType: !824, size: 64, align: 64, offset: 256)
!1038 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !1031, file: !130, line: 1451, baseType: !824, size: 64, align: 64, offset: 320)
!1039 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !545, file: !130, line: 1831, baseType: !1040, size: 64, align: 64, offset: 17600)
!1040 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1041, size: 64, align: 64)
!1041 = !DICompositeType(tag: DW_TAG_structure_type, name: "CookieInfo", file: !1042, line: 48, size: 320, align: 64, elements: !1043)
!1042 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/cookie.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1043 = !{!1044, !1062, !1063, !1064, !1065}
!1044 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !1041, file: !1042, line: 50, baseType: !1045, size: 64, align: 64)
!1045 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1046, size: 64, align: 64)
!1046 = !DICompositeType(tag: DW_TAG_structure_type, name: "Cookie", file: !1042, line: 28, size: 768, align: 64, elements: !1047)
!1047 = !{!1048, !1049, !1050, !1051, !1052, !1053, !1054, !1055, !1056, !1057, !1058, !1059, !1060, !1061}
!1048 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1046, file: !1042, line: 29, baseType: !1045, size: 64, align: 64)
!1049 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1046, file: !1042, line: 30, baseType: !215, size: 64, align: 64, offset: 64)
!1050 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !1046, file: !1042, line: 31, baseType: !215, size: 64, align: 64, offset: 128)
!1051 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1046, file: !1042, line: 32, baseType: !215, size: 64, align: 64, offset: 192)
!1052 = !DIDerivedType(tag: DW_TAG_member, name: "spath", scope: !1046, file: !1042, line: 33, baseType: !215, size: 64, align: 64, offset: 256)
!1053 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1046, file: !1042, line: 34, baseType: !215, size: 64, align: 64, offset: 320)
!1054 = !DIDerivedType(tag: DW_TAG_member, name: "expires", scope: !1046, file: !1042, line: 35, baseType: !189, size: 64, align: 64, offset: 384)
!1055 = !DIDerivedType(tag: DW_TAG_member, name: "expirestr", scope: !1046, file: !1042, line: 36, baseType: !215, size: 64, align: 64, offset: 448)
!1056 = !DIDerivedType(tag: DW_TAG_member, name: "tailmatch", scope: !1046, file: !1042, line: 37, baseType: !211, size: 8, align: 8, offset: 512)
!1057 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !1046, file: !1042, line: 40, baseType: !215, size: 64, align: 64, offset: 576)
!1058 = !DIDerivedType(tag: DW_TAG_member, name: "maxage", scope: !1046, file: !1042, line: 41, baseType: !215, size: 64, align: 64, offset: 640)
!1059 = !DIDerivedType(tag: DW_TAG_member, name: "secure", scope: !1046, file: !1042, line: 43, baseType: !211, size: 8, align: 8, offset: 704)
!1060 = !DIDerivedType(tag: DW_TAG_member, name: "livecookie", scope: !1046, file: !1042, line: 44, baseType: !211, size: 8, align: 8, offset: 712)
!1061 = !DIDerivedType(tag: DW_TAG_member, name: "httponly", scope: !1046, file: !1042, line: 45, baseType: !211, size: 8, align: 8, offset: 720)
!1062 = !DIDerivedType(tag: DW_TAG_member, name: "filename", scope: !1041, file: !1042, line: 52, baseType: !215, size: 64, align: 64, offset: 64)
!1063 = !DIDerivedType(tag: DW_TAG_member, name: "running", scope: !1041, file: !1042, line: 53, baseType: !211, size: 8, align: 8, offset: 128)
!1064 = !DIDerivedType(tag: DW_TAG_member, name: "numcookies", scope: !1041, file: !1042, line: 54, baseType: !191, size: 64, align: 64, offset: 192)
!1065 = !DIDerivedType(tag: DW_TAG_member, name: "newsession", scope: !1041, file: !1042, line: 55, baseType: !211, size: 8, align: 8, offset: 256)
!1066 = !DIDerivedType(tag: DW_TAG_member, name: "progress", scope: !545, file: !130, line: 1835, baseType: !1067, size: 3200, align: 64, offset: 17664)
!1067 = !DICompositeType(tag: DW_TAG_structure_type, name: "Progress", file: !130, line: 1195, size: 3200, align: 64, elements: !1068)
!1068 = !{!1069, !1070, !1071, !1072, !1073, !1074, !1075, !1076, !1077, !1078, !1079, !1080, !1081, !1082, !1083, !1084, !1085, !1086, !1087, !1088, !1089, !1090, !1091, !1092, !1093, !1094, !1095, !1099, !1101}
!1069 = !DIDerivedType(tag: DW_TAG_member, name: "lastshow", scope: !1067, file: !130, line: 1196, baseType: !242, size: 64, align: 64)
!1070 = !DIDerivedType(tag: DW_TAG_member, name: "size_dl", scope: !1067, file: !130, line: 1198, baseType: !189, size: 64, align: 64, offset: 64)
!1071 = !DIDerivedType(tag: DW_TAG_member, name: "size_ul", scope: !1067, file: !130, line: 1199, baseType: !189, size: 64, align: 64, offset: 128)
!1072 = !DIDerivedType(tag: DW_TAG_member, name: "downloaded", scope: !1067, file: !130, line: 1200, baseType: !189, size: 64, align: 64, offset: 192)
!1073 = !DIDerivedType(tag: DW_TAG_member, name: "uploaded", scope: !1067, file: !130, line: 1201, baseType: !189, size: 64, align: 64, offset: 256)
!1074 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1067, file: !130, line: 1203, baseType: !189, size: 64, align: 64, offset: 320)
!1075 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !1067, file: !130, line: 1205, baseType: !211, size: 8, align: 8, offset: 384)
!1076 = !DIDerivedType(tag: DW_TAG_member, name: "width", scope: !1067, file: !130, line: 1206, baseType: !177, size: 32, align: 32, offset: 416)
!1077 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1067, file: !130, line: 1207, baseType: !177, size: 32, align: 32, offset: 448)
!1078 = !DIDerivedType(tag: DW_TAG_member, name: "timespent", scope: !1067, file: !130, line: 1209, baseType: !745, size: 64, align: 64, offset: 512)
!1079 = !DIDerivedType(tag: DW_TAG_member, name: "dlspeed", scope: !1067, file: !130, line: 1211, baseType: !189, size: 64, align: 64, offset: 576)
!1080 = !DIDerivedType(tag: DW_TAG_member, name: "ulspeed", scope: !1067, file: !130, line: 1212, baseType: !189, size: 64, align: 64, offset: 640)
!1081 = !DIDerivedType(tag: DW_TAG_member, name: "t_nslookup", scope: !1067, file: !130, line: 1214, baseType: !745, size: 64, align: 64, offset: 704)
!1082 = !DIDerivedType(tag: DW_TAG_member, name: "t_connect", scope: !1067, file: !130, line: 1215, baseType: !745, size: 64, align: 64, offset: 768)
!1083 = !DIDerivedType(tag: DW_TAG_member, name: "t_appconnect", scope: !1067, file: !130, line: 1216, baseType: !745, size: 64, align: 64, offset: 832)
!1084 = !DIDerivedType(tag: DW_TAG_member, name: "t_pretransfer", scope: !1067, file: !130, line: 1217, baseType: !745, size: 64, align: 64, offset: 896)
!1085 = !DIDerivedType(tag: DW_TAG_member, name: "t_starttransfer", scope: !1067, file: !130, line: 1218, baseType: !745, size: 64, align: 64, offset: 960)
!1086 = !DIDerivedType(tag: DW_TAG_member, name: "t_redirect", scope: !1067, file: !130, line: 1219, baseType: !745, size: 64, align: 64, offset: 1024)
!1087 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !1067, file: !130, line: 1221, baseType: !201, size: 128, align: 64, offset: 1088)
!1088 = !DIDerivedType(tag: DW_TAG_member, name: "t_startsingle", scope: !1067, file: !130, line: 1222, baseType: !201, size: 128, align: 64, offset: 1216)
!1089 = !DIDerivedType(tag: DW_TAG_member, name: "t_startop", scope: !1067, file: !130, line: 1223, baseType: !201, size: 128, align: 64, offset: 1344)
!1090 = !DIDerivedType(tag: DW_TAG_member, name: "t_acceptdata", scope: !1067, file: !130, line: 1224, baseType: !201, size: 128, align: 64, offset: 1472)
!1091 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_start", scope: !1067, file: !130, line: 1227, baseType: !201, size: 128, align: 64, offset: 1600)
!1092 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_size", scope: !1067, file: !130, line: 1228, baseType: !189, size: 64, align: 64, offset: 1728)
!1093 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_start", scope: !1067, file: !130, line: 1230, baseType: !201, size: 128, align: 64, offset: 1792)
!1094 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_size", scope: !1067, file: !130, line: 1231, baseType: !189, size: 64, align: 64, offset: 1920)
!1095 = !DIDerivedType(tag: DW_TAG_member, name: "speeder", scope: !1067, file: !130, line: 1235, baseType: !1096, size: 384, align: 64, offset: 1984)
!1096 = !DICompositeType(tag: DW_TAG_array_type, baseType: !189, size: 384, align: 64, elements: !1097)
!1097 = !{!1098}
!1098 = !DISubrange(count: 6)
!1099 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_time", scope: !1067, file: !130, line: 1236, baseType: !1100, size: 768, align: 64, offset: 2368)
!1100 = !DICompositeType(tag: DW_TAG_array_type, baseType: !201, size: 768, align: 64, elements: !1097)
!1101 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_c", scope: !1067, file: !130, line: 1237, baseType: !177, size: 32, align: 32, offset: 3136)
!1102 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !545, file: !130, line: 1836, baseType: !1103, size: 136640, align: 64, offset: 20864)
!1103 = !DICompositeType(tag: DW_TAG_structure_type, name: "UrlState", file: !130, line: 1310, size: 136640, align: 64, elements: !1104)
!1104 = !{!1105, !1107, !1108, !1109, !1110, !1111, !1112, !1113, !1117, !1118, !1119, !1120, !1121, !1134, !1135, !1136, !1145, !1146, !1147, !1148, !1152, !1153, !1165, !1166, !1175, !1176, !1177, !1178, !1179, !1180, !1181, !1182, !1183, !1184, !1185, !1186, !1187, !1188, !1189, !1190, !1191, !1192, !1193, !1194, !1195, !1196, !1197, !1198, !1199, !1200, !1201, !1202, !1203, !1204, !1205}
!1105 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !1103, file: !130, line: 1313, baseType: !1106, size: 64, align: 64)
!1106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !618, size: 64, align: 64)
!1107 = !DIDerivedType(tag: DW_TAG_member, name: "multi_owned_by_easy", scope: !1103, file: !130, line: 1318, baseType: !211, size: 8, align: 8, offset: 64)
!1108 = !DIDerivedType(tag: DW_TAG_member, name: "keeps_speed", scope: !1103, file: !130, line: 1321, baseType: !201, size: 128, align: 64, offset: 128)
!1109 = !DIDerivedType(tag: DW_TAG_member, name: "lastconnect", scope: !1103, file: !130, line: 1323, baseType: !550, size: 64, align: 64, offset: 256)
!1110 = !DIDerivedType(tag: DW_TAG_member, name: "headerbuff", scope: !1103, file: !130, line: 1325, baseType: !215, size: 64, align: 64, offset: 320)
!1111 = !DIDerivedType(tag: DW_TAG_member, name: "headersize", scope: !1103, file: !130, line: 1326, baseType: !158, size: 64, align: 64, offset: 384)
!1112 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !1103, file: !130, line: 1328, baseType: !215, size: 64, align: 64, offset: 448)
!1113 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuffer", scope: !1103, file: !130, line: 1329, baseType: !1114, size: 131080, align: 8, offset: 512)
!1114 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 131080, align: 8, elements: !1115)
!1115 = !{!1116}
!1116 = !DISubrange(count: 16385)
!1117 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1103, file: !130, line: 1330, baseType: !189, size: 64, align: 64, offset: 131648)
!1118 = !DIDerivedType(tag: DW_TAG_member, name: "this_is_a_follow", scope: !1103, file: !130, line: 1332, baseType: !211, size: 8, align: 8, offset: 131712)
!1119 = !DIDerivedType(tag: DW_TAG_member, name: "first_host", scope: !1103, file: !130, line: 1334, baseType: !215, size: 64, align: 64, offset: 131776)
!1120 = !DIDerivedType(tag: DW_TAG_member, name: "first_remote_port", scope: !1103, file: !130, line: 1340, baseType: !177, size: 32, align: 32, offset: 131840)
!1121 = !DIDerivedType(tag: DW_TAG_member, name: "session", scope: !1103, file: !130, line: 1341, baseType: !1122, size: 64, align: 64, offset: 131904)
!1122 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1123, size: 64, align: 64)
!1123 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_ssl_session", file: !130, line: 397, size: 1088, align: 64, elements: !1124)
!1124 = !{!1125, !1126, !1127, !1128, !1129, !1130, !1131, !1132, !1133}
!1125 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1123, file: !130, line: 398, baseType: !215, size: 64, align: 64)
!1126 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !1123, file: !130, line: 399, baseType: !215, size: 64, align: 64, offset: 64)
!1127 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !1123, file: !130, line: 400, baseType: !928, size: 64, align: 64, offset: 128)
!1128 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !1123, file: !130, line: 401, baseType: !148, size: 64, align: 64, offset: 192)
!1129 = !DIDerivedType(tag: DW_TAG_member, name: "idsize", scope: !1123, file: !130, line: 402, baseType: !158, size: 64, align: 64, offset: 256)
!1130 = !DIDerivedType(tag: DW_TAG_member, name: "age", scope: !1123, file: !130, line: 403, baseType: !191, size: 64, align: 64, offset: 320)
!1131 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !1123, file: !130, line: 404, baseType: !177, size: 32, align: 32, offset: 384)
!1132 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !1123, file: !130, line: 405, baseType: !177, size: 32, align: 32, offset: 416)
!1133 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !1123, file: !130, line: 406, baseType: !870, size: 640, align: 64, offset: 448)
!1134 = !DIDerivedType(tag: DW_TAG_member, name: "sessionage", scope: !1103, file: !130, line: 1342, baseType: !191, size: 64, align: 64, offset: 131968)
!1135 = !DIDerivedType(tag: DW_TAG_member, name: "tempcount", scope: !1103, file: !130, line: 1343, baseType: !782, size: 32, align: 32, offset: 132032)
!1136 = !DIDerivedType(tag: DW_TAG_member, name: "tempwrite", scope: !1103, file: !130, line: 1344, baseType: !1137, size: 576, align: 64, offset: 132096)
!1137 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1138, size: 576, align: 64, elements: !1143)
!1138 = !DICompositeType(tag: DW_TAG_structure_type, name: "tempbuf", file: !130, line: 1302, size: 192, align: 64, elements: !1139)
!1139 = !{!1140, !1141, !1142}
!1140 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !1138, file: !130, line: 1303, baseType: !215, size: 64, align: 64)
!1141 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !1138, file: !130, line: 1305, baseType: !158, size: 64, align: 64, offset: 64)
!1142 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !1138, file: !130, line: 1306, baseType: !177, size: 32, align: 32, offset: 128)
!1143 = !{!1144}
!1144 = !DISubrange(count: 3)
!1145 = !DIDerivedType(tag: DW_TAG_member, name: "scratch", scope: !1103, file: !130, line: 1345, baseType: !215, size: 64, align: 64, offset: 132672)
!1146 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuf", scope: !1103, file: !130, line: 1346, baseType: !211, size: 8, align: 8, offset: 132736)
!1147 = !DIDerivedType(tag: DW_TAG_member, name: "os_errno", scope: !1103, file: !130, line: 1349, baseType: !177, size: 32, align: 32, offset: 132768)
!1148 = !DIDerivedType(tag: DW_TAG_member, name: "prev_signal", scope: !1103, file: !130, line: 1352, baseType: !1149, size: 64, align: 64, offset: 132800)
!1149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1150, size: 64, align: 64)
!1150 = !DISubroutineType(types: !1151)
!1151 = !{null, !177}
!1152 = !DIDerivedType(tag: DW_TAG_member, name: "allow_port", scope: !1103, file: !130, line: 1354, baseType: !211, size: 8, align: 8, offset: 132864)
!1153 = !DIDerivedType(tag: DW_TAG_member, name: "digest", scope: !1103, file: !130, line: 1356, baseType: !1154, size: 512, align: 64, offset: 132928)
!1154 = !DICompositeType(tag: DW_TAG_structure_type, name: "digestdata", file: !130, line: 410, size: 512, align: 64, elements: !1155)
!1155 = !{!1156, !1157, !1158, !1159, !1160, !1161, !1162, !1163, !1164}
!1156 = !DIDerivedType(tag: DW_TAG_member, name: "nonce", scope: !1154, file: !130, line: 416, baseType: !215, size: 64, align: 64)
!1157 = !DIDerivedType(tag: DW_TAG_member, name: "cnonce", scope: !1154, file: !130, line: 417, baseType: !215, size: 64, align: 64, offset: 64)
!1158 = !DIDerivedType(tag: DW_TAG_member, name: "realm", scope: !1154, file: !130, line: 418, baseType: !215, size: 64, align: 64, offset: 128)
!1159 = !DIDerivedType(tag: DW_TAG_member, name: "algo", scope: !1154, file: !130, line: 419, baseType: !177, size: 32, align: 32, offset: 192)
!1160 = !DIDerivedType(tag: DW_TAG_member, name: "stale", scope: !1154, file: !130, line: 420, baseType: !211, size: 8, align: 8, offset: 224)
!1161 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !1154, file: !130, line: 421, baseType: !215, size: 64, align: 64, offset: 256)
!1162 = !DIDerivedType(tag: DW_TAG_member, name: "qop", scope: !1154, file: !130, line: 422, baseType: !215, size: 64, align: 64, offset: 320)
!1163 = !DIDerivedType(tag: DW_TAG_member, name: "algorithm", scope: !1154, file: !130, line: 423, baseType: !215, size: 64, align: 64, offset: 384)
!1164 = !DIDerivedType(tag: DW_TAG_member, name: "nc", scope: !1154, file: !130, line: 424, baseType: !177, size: 32, align: 32, offset: 448)
!1165 = !DIDerivedType(tag: DW_TAG_member, name: "proxydigest", scope: !1103, file: !130, line: 1357, baseType: !1154, size: 512, align: 64, offset: 133440)
!1166 = !DIDerivedType(tag: DW_TAG_member, name: "authhost", scope: !1103, file: !130, line: 1364, baseType: !1167, size: 256, align: 64, offset: 133952)
!1167 = !DICompositeType(tag: DW_TAG_structure_type, name: "auth", file: !130, line: 1278, size: 256, align: 64, elements: !1168)
!1168 = !{!1169, !1170, !1171, !1172, !1173, !1174}
!1169 = !DIDerivedType(tag: DW_TAG_member, name: "want", scope: !1167, file: !130, line: 1279, baseType: !160, size: 64, align: 64)
!1170 = !DIDerivedType(tag: DW_TAG_member, name: "picked", scope: !1167, file: !130, line: 1281, baseType: !160, size: 64, align: 64, offset: 64)
!1171 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !1167, file: !130, line: 1282, baseType: !160, size: 64, align: 64, offset: 128)
!1172 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1167, file: !130, line: 1284, baseType: !211, size: 8, align: 8, offset: 192)
!1173 = !DIDerivedType(tag: DW_TAG_member, name: "multipass", scope: !1167, file: !130, line: 1286, baseType: !211, size: 8, align: 8, offset: 200)
!1174 = !DIDerivedType(tag: DW_TAG_member, name: "iestyle", scope: !1167, file: !130, line: 1288, baseType: !211, size: 8, align: 8, offset: 208)
!1175 = !DIDerivedType(tag: DW_TAG_member, name: "authproxy", scope: !1103, file: !130, line: 1365, baseType: !1167, size: 256, align: 64, offset: 134208)
!1176 = !DIDerivedType(tag: DW_TAG_member, name: "authproblem", scope: !1103, file: !130, line: 1367, baseType: !211, size: 8, align: 8, offset: 134464)
!1177 = !DIDerivedType(tag: DW_TAG_member, name: "resolver", scope: !1103, file: !130, line: 1369, baseType: !148, size: 64, align: 64, offset: 134528)
!1178 = !DIDerivedType(tag: DW_TAG_member, name: "expiretime", scope: !1103, file: !130, line: 1375, baseType: !201, size: 128, align: 64, offset: 134592)
!1179 = !DIDerivedType(tag: DW_TAG_member, name: "timenode", scope: !1103, file: !130, line: 1376, baseType: !605, size: 448, align: 64, offset: 134720)
!1180 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutlist", scope: !1103, file: !130, line: 1377, baseType: !140, size: 256, align: 64, offset: 135168)
!1181 = !DIDerivedType(tag: DW_TAG_member, name: "most_recent_ftp_entrypath", scope: !1103, file: !130, line: 1380, baseType: !215, size: 64, align: 64, offset: 135424)
!1182 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_trying_alternative", scope: !1103, file: !130, line: 1383, baseType: !211, size: 8, align: 8, offset: 135488)
!1183 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1103, file: !130, line: 1385, baseType: !177, size: 32, align: 32, offset: 135520)
!1184 = !DIDerivedType(tag: DW_TAG_member, name: "expect100header", scope: !1103, file: !130, line: 1387, baseType: !211, size: 8, align: 8, offset: 135552)
!1185 = !DIDerivedType(tag: DW_TAG_member, name: "pipe_broke", scope: !1103, file: !130, line: 1389, baseType: !211, size: 8, align: 8, offset: 135560)
!1186 = !DIDerivedType(tag: DW_TAG_member, name: "prev_block_had_trailing_cr", scope: !1103, file: !130, line: 1397, baseType: !211, size: 8, align: 8, offset: 135568)
!1187 = !DIDerivedType(tag: DW_TAG_member, name: "crlf_conversions", scope: !1103, file: !130, line: 1399, baseType: !189, size: 64, align: 64, offset: 135616)
!1188 = !DIDerivedType(tag: DW_TAG_member, name: "pathbuffer", scope: !1103, file: !130, line: 1401, baseType: !215, size: 64, align: 64, offset: 135680)
!1189 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1103, file: !130, line: 1402, baseType: !215, size: 64, align: 64, offset: 135744)
!1190 = !DIDerivedType(tag: DW_TAG_member, name: "slash_removed", scope: !1103, file: !130, line: 1404, baseType: !211, size: 8, align: 8, offset: 135808)
!1191 = !DIDerivedType(tag: DW_TAG_member, name: "use_range", scope: !1103, file: !130, line: 1406, baseType: !211, size: 8, align: 8, offset: 135816)
!1192 = !DIDerivedType(tag: DW_TAG_member, name: "rangestringalloc", scope: !1103, file: !130, line: 1407, baseType: !211, size: 8, align: 8, offset: 135824)
!1193 = !DIDerivedType(tag: DW_TAG_member, name: "range", scope: !1103, file: !130, line: 1409, baseType: !215, size: 64, align: 64, offset: 135872)
!1194 = !DIDerivedType(tag: DW_TAG_member, name: "resume_from", scope: !1103, file: !130, line: 1411, baseType: !189, size: 64, align: 64, offset: 135936)
!1195 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_client_CSeq", scope: !1103, file: !130, line: 1414, baseType: !191, size: 64, align: 64, offset: 136000)
!1196 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_server_CSeq", scope: !1103, file: !130, line: 1415, baseType: !191, size: 64, align: 64, offset: 136064)
!1197 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_CSeq_recv", scope: !1103, file: !130, line: 1416, baseType: !191, size: 64, align: 64, offset: 136128)
!1198 = !DIDerivedType(tag: DW_TAG_member, name: "infilesize", scope: !1103, file: !130, line: 1418, baseType: !189, size: 64, align: 64, offset: 136192)
!1199 = !DIDerivedType(tag: DW_TAG_member, name: "drain", scope: !1103, file: !130, line: 1421, baseType: !158, size: 64, align: 64, offset: 136256)
!1200 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1103, file: !130, line: 1424, baseType: !211, size: 8, align: 8, offset: 136320)
!1201 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func", scope: !1103, file: !130, line: 1428, baseType: !737, size: 64, align: 64, offset: 136384)
!1202 = !DIDerivedType(tag: DW_TAG_member, name: "in", scope: !1103, file: !130, line: 1429, baseType: !148, size: 64, align: 64, offset: 136448)
!1203 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !1103, file: !130, line: 1431, baseType: !544, size: 64, align: 64, offset: 136512)
!1204 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !1103, file: !130, line: 1432, baseType: !211, size: 8, align: 8, offset: 136576)
!1205 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !1103, file: !130, line: 1433, baseType: !177, size: 32, align: 32, offset: 136608)
!1206 = !DIDerivedType(tag: DW_TAG_member, name: "wildcard", scope: !545, file: !130, line: 1838, baseType: !1207, size: 640, align: 64, offset: 157504)
!1207 = !DICompositeType(tag: DW_TAG_structure_type, name: "WildcardData", file: !375, line: 46, size: 640, align: 64, elements: !1208)
!1208 = !{!1209, !1211, !1212, !1213, !1214, !1215, !1217}
!1209 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1207, file: !375, line: 47, baseType: !1210, size: 32, align: 32)
!1210 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_states", file: !375, line: 41, baseType: !374)
!1211 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1207, file: !375, line: 48, baseType: !215, size: 64, align: 64, offset: 64)
!1212 = !DIDerivedType(tag: DW_TAG_member, name: "pattern", scope: !1207, file: !375, line: 49, baseType: !215, size: 64, align: 64, offset: 128)
!1213 = !DIDerivedType(tag: DW_TAG_member, name: "filelist", scope: !1207, file: !375, line: 50, baseType: !140, size: 256, align: 64, offset: 192)
!1214 = !DIDerivedType(tag: DW_TAG_member, name: "tmp", scope: !1207, file: !375, line: 51, baseType: !148, size: 64, align: 64, offset: 448)
!1215 = !DIDerivedType(tag: DW_TAG_member, name: "tmp_dtor", scope: !1207, file: !375, line: 52, baseType: !1216, size: 64, align: 64, offset: 512)
!1216 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_tmp_dtor", file: !375, line: 43, baseType: !173)
!1217 = !DIDerivedType(tag: DW_TAG_member, name: "customptr", scope: !1207, file: !375, line: 53, baseType: !148, size: 64, align: 64, offset: 576)
!1218 = !DIDerivedType(tag: DW_TAG_member, name: "info", scope: !545, file: !130, line: 1839, baseType: !1219, size: 1856, align: 64, offset: 158144)
!1219 = !DICompositeType(tag: DW_TAG_structure_type, name: "PureInfo", file: !130, line: 1154, size: 1856, align: 64, elements: !1220)
!1220 = !{!1221, !1222, !1223, !1224, !1225, !1226, !1227, !1228, !1229, !1230, !1231, !1232, !1233, !1237, !1238, !1239, !1240, !1241, !1242}
!1221 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !1219, file: !130, line: 1155, baseType: !177, size: 32, align: 32)
!1222 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxycode", scope: !1219, file: !130, line: 1156, baseType: !177, size: 32, align: 32, offset: 32)
!1223 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1219, file: !130, line: 1157, baseType: !177, size: 32, align: 32, offset: 64)
!1224 = !DIDerivedType(tag: DW_TAG_member, name: "filetime", scope: !1219, file: !130, line: 1158, baseType: !191, size: 64, align: 64, offset: 128)
!1225 = !DIDerivedType(tag: DW_TAG_member, name: "timecond", scope: !1219, file: !130, line: 1162, baseType: !211, size: 8, align: 8, offset: 192)
!1226 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !1219, file: !130, line: 1164, baseType: !191, size: 64, align: 64, offset: 256)
!1227 = !DIDerivedType(tag: DW_TAG_member, name: "request_size", scope: !1219, file: !130, line: 1165, baseType: !191, size: 64, align: 64, offset: 320)
!1228 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauthavail", scope: !1219, file: !130, line: 1166, baseType: !160, size: 64, align: 64, offset: 384)
!1229 = !DIDerivedType(tag: DW_TAG_member, name: "httpauthavail", scope: !1219, file: !130, line: 1167, baseType: !160, size: 64, align: 64, offset: 448)
!1230 = !DIDerivedType(tag: DW_TAG_member, name: "numconnects", scope: !1219, file: !130, line: 1168, baseType: !191, size: 64, align: 64, offset: 512)
!1231 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !1219, file: !130, line: 1169, baseType: !215, size: 64, align: 64, offset: 576)
!1232 = !DIDerivedType(tag: DW_TAG_member, name: "wouldredirect", scope: !1219, file: !130, line: 1170, baseType: !215, size: 64, align: 64, offset: 640)
!1233 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_ip", scope: !1219, file: !130, line: 1180, baseType: !1234, size: 368, align: 8, offset: 704)
!1234 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 368, align: 8, elements: !1235)
!1235 = !{!1236}
!1236 = !DISubrange(count: 46)
!1237 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_port", scope: !1219, file: !130, line: 1181, baseType: !191, size: 64, align: 64, offset: 1088)
!1238 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_ip", scope: !1219, file: !130, line: 1183, baseType: !1234, size: 368, align: 8, offset: 1152)
!1239 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_port", scope: !1219, file: !130, line: 1184, baseType: !191, size: 64, align: 64, offset: 1536)
!1240 = !DIDerivedType(tag: DW_TAG_member, name: "conn_scheme", scope: !1219, file: !130, line: 1186, baseType: !928, size: 64, align: 64, offset: 1600)
!1241 = !DIDerivedType(tag: DW_TAG_member, name: "conn_protocol", scope: !1219, file: !130, line: 1187, baseType: !782, size: 32, align: 32, offset: 1664)
!1242 = !DIDerivedType(tag: DW_TAG_member, name: "certs", scope: !1219, file: !130, line: 1189, baseType: !1243, size: 128, align: 64, offset: 1728)
!1243 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_certinfo", file: !4, line: 2214, size: 128, align: 64, elements: !1244)
!1244 = !{!1245, !1246}
!1245 = !DIDerivedType(tag: DW_TAG_member, name: "num_of_certs", scope: !1243, file: !4, line: 2215, baseType: !177, size: 32, align: 32)
!1246 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !1243, file: !4, line: 2216, baseType: !1247, size: 64, align: 64, offset: 64)
!1247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !824, size: 64, align: 64)
!1248 = !DIDerivedType(tag: DW_TAG_member, name: "tsi", scope: !545, file: !130, line: 1840, baseType: !1249, size: 128, align: 64, offset: 160000)
!1249 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_tlssessioninfo", file: !4, line: 2245, size: 128, align: 64, elements: !1250)
!1250 = !{!1251, !1253}
!1251 = !DIDerivedType(tag: DW_TAG_member, name: "backend", scope: !1249, file: !4, line: 2246, baseType: !1252, size: 32, align: 32)
!1252 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sslbackend", file: !4, line: 2235, baseType: !385)
!1253 = !DIDerivedType(tag: DW_TAG_member, name: "internals", scope: !1249, file: !4, line: 2247, baseType: !148, size: 64, align: 64, offset: 64)
!1254 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !545, file: !130, line: 1847, baseType: !782, size: 32, align: 32, offset: 160128)
!1255 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !541, file: !130, line: 904, baseType: !1256, size: 384, align: 64, offset: 64)
!1256 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_chunker", file: !400, line: 82, size: 384, align: 64, elements: !1257)
!1257 = !{!1258, !1262, !1263, !1265, !1266}
!1258 = !DIDerivedType(tag: DW_TAG_member, name: "hexbuffer", scope: !1256, file: !400, line: 83, baseType: !1259, size: 136, align: 8)
!1259 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 136, align: 8, elements: !1260)
!1260 = !{!1261}
!1261 = !DISubrange(count: 17)
!1262 = !DIDerivedType(tag: DW_TAG_member, name: "hexindex", scope: !1256, file: !400, line: 84, baseType: !177, size: 32, align: 32, offset: 160)
!1263 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1256, file: !400, line: 85, baseType: !1264, size: 32, align: 32, offset: 192)
!1264 = !DIDerivedType(tag: DW_TAG_typedef, name: "ChunkyState", file: !400, line: 66, baseType: !399)
!1265 = !DIDerivedType(tag: DW_TAG_member, name: "datasize", scope: !1256, file: !400, line: 86, baseType: !189, size: 64, align: 64, offset: 256)
!1266 = !DIDerivedType(tag: DW_TAG_member, name: "dataleft", scope: !1256, file: !400, line: 87, baseType: !158, size: 64, align: 64, offset: 320)
!1267 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !541, file: !130, line: 906, baseType: !796, size: 64, align: 64, offset: 448)
!1268 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !541, file: !130, line: 907, baseType: !148, size: 64, align: 64, offset: 512)
!1269 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !541, file: !130, line: 909, baseType: !211, size: 8, align: 8, offset: 576)
!1270 = !DIDerivedType(tag: DW_TAG_member, name: "connection_id", scope: !541, file: !130, line: 915, baseType: !191, size: 64, align: 64, offset: 640)
!1271 = !DIDerivedType(tag: DW_TAG_member, name: "dns_entry", scope: !541, file: !130, line: 922, baseType: !1272, size: 64, align: 64, offset: 704)
!1272 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1273, size: 64, align: 64)
!1273 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_dns_entry", file: !1274, line: 66, size: 192, align: 64, elements: !1275)
!1274 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hostip.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1275 = !{!1276, !1295, !1296}
!1276 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !1273, file: !1274, line: 67, baseType: !1277, size: 64, align: 64)
!1277 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1278, size: 64, align: 64)
!1278 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_addrinfo", file: !1279, line: 61, baseType: !1280)
!1279 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_addrinfo.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1280 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_addrinfo", file: !1279, line: 51, size: 384, align: 64, elements: !1281)
!1281 = !{!1282, !1283, !1284, !1285, !1286, !1290, !1291, !1293}
!1282 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !1280, file: !1279, line: 52, baseType: !177, size: 32, align: 32)
!1283 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !1280, file: !1279, line: 53, baseType: !177, size: 32, align: 32, offset: 32)
!1284 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !1280, file: !1279, line: 54, baseType: !177, size: 32, align: 32, offset: 64)
!1285 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !1280, file: !1279, line: 55, baseType: !177, size: 32, align: 32, offset: 96)
!1286 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !1280, file: !1279, line: 56, baseType: !1287, size: 32, align: 32, offset: 128)
!1287 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socklen_t", file: !190, line: 186, baseType: !1288)
!1288 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !785, line: 33, baseType: !1289)
!1289 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !206, line: 189, baseType: !782)
!1290 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !1280, file: !1279, line: 57, baseType: !215, size: 64, align: 64, offset: 192)
!1291 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !1280, file: !1279, line: 58, baseType: !1292, size: 64, align: 64, offset: 256)
!1292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !784, size: 64, align: 64)
!1293 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !1280, file: !1279, line: 59, baseType: !1294, size: 64, align: 64, offset: 320)
!1294 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1280, size: 64, align: 64)
!1295 = !DIDerivedType(tag: DW_TAG_member, name: "timestamp", scope: !1273, file: !1274, line: 69, baseType: !242, size: 64, align: 64, offset: 64)
!1296 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !1273, file: !1274, line: 71, baseType: !191, size: 64, align: 64, offset: 128)
!1297 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr", scope: !541, file: !130, line: 927, baseType: !1277, size: 64, align: 64, offset: 768)
!1298 = !DIDerivedType(tag: DW_TAG_member, name: "tempaddr", scope: !541, file: !130, line: 928, baseType: !1299, size: 128, align: 64, offset: 832)
!1299 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1277, size: 128, align: 64, elements: !1300)
!1300 = !{!1301}
!1301 = !DISubrange(count: 2)
!1302 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr_str", scope: !541, file: !130, line: 933, baseType: !1234, size: 368, align: 8, offset: 960)
!1303 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !541, file: !130, line: 935, baseType: !782, size: 32, align: 32, offset: 1344)
!1304 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !541, file: !130, line: 937, baseType: !177, size: 32, align: 32, offset: 1376)
!1305 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !541, file: !130, line: 939, baseType: !1306, size: 256, align: 64, offset: 1408)
!1306 = !DICompositeType(tag: DW_TAG_structure_type, name: "hostname", file: !130, line: 581, size: 256, align: 64, elements: !1307)
!1307 = !{!1308, !1309, !1310, !1311}
!1308 = !DIDerivedType(tag: DW_TAG_member, name: "rawalloc", scope: !1306, file: !130, line: 582, baseType: !215, size: 64, align: 64)
!1309 = !DIDerivedType(tag: DW_TAG_member, name: "encalloc", scope: !1306, file: !130, line: 583, baseType: !215, size: 64, align: 64, offset: 64)
!1310 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1306, file: !130, line: 584, baseType: !215, size: 64, align: 64, offset: 128)
!1311 = !DIDerivedType(tag: DW_TAG_member, name: "dispname", scope: !1306, file: !130, line: 585, baseType: !928, size: 64, align: 64, offset: 192)
!1312 = !DIDerivedType(tag: DW_TAG_member, name: "secondaryhostname", scope: !541, file: !130, line: 940, baseType: !215, size: 64, align: 64, offset: 1664)
!1313 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !541, file: !130, line: 941, baseType: !1306, size: 256, align: 64, offset: 1728)
!1314 = !DIDerivedType(tag: DW_TAG_member, name: "socks_proxy", scope: !541, file: !130, line: 944, baseType: !1315, size: 512, align: 64, offset: 1984)
!1315 = !DICompositeType(tag: DW_TAG_structure_type, name: "proxy_info", file: !130, line: 883, size: 512, align: 64, elements: !1316)
!1316 = !{!1317, !1318, !1319, !1320, !1321}
!1317 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1315, file: !130, line: 884, baseType: !1306, size: 256, align: 64)
!1318 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !1315, file: !130, line: 885, baseType: !191, size: 64, align: 64, offset: 256)
!1319 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !1315, file: !130, line: 886, baseType: !908, size: 32, align: 32, offset: 320)
!1320 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1315, file: !130, line: 887, baseType: !215, size: 64, align: 64, offset: 384)
!1321 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !1315, file: !130, line: 888, baseType: !215, size: 64, align: 64, offset: 448)
!1322 = !DIDerivedType(tag: DW_TAG_member, name: "http_proxy", scope: !541, file: !130, line: 945, baseType: !1315, size: 512, align: 64, offset: 2496)
!1323 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !541, file: !130, line: 947, baseType: !191, size: 64, align: 64, offset: 3008)
!1324 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !541, file: !130, line: 948, baseType: !177, size: 32, align: 32, offset: 3072)
!1325 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !541, file: !130, line: 949, baseType: !177, size: 32, align: 32, offset: 3104)
!1326 = !DIDerivedType(tag: DW_TAG_member, name: "secondary_port", scope: !541, file: !130, line: 951, baseType: !684, size: 16, align: 16, offset: 3136)
!1327 = !DIDerivedType(tag: DW_TAG_member, name: "primary_ip", scope: !541, file: !130, line: 961, baseType: !1234, size: 368, align: 8, offset: 3152)
!1328 = !DIDerivedType(tag: DW_TAG_member, name: "primary_port", scope: !541, file: !130, line: 962, baseType: !191, size: 64, align: 64, offset: 3520)
!1329 = !DIDerivedType(tag: DW_TAG_member, name: "local_ip", scope: !541, file: !130, line: 968, baseType: !1234, size: 368, align: 8, offset: 3584)
!1330 = !DIDerivedType(tag: DW_TAG_member, name: "local_port", scope: !541, file: !130, line: 969, baseType: !191, size: 64, align: 64, offset: 3968)
!1331 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !541, file: !130, line: 971, baseType: !215, size: 64, align: 64, offset: 4032)
!1332 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !541, file: !130, line: 972, baseType: !215, size: 64, align: 64, offset: 4096)
!1333 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !541, file: !130, line: 973, baseType: !215, size: 64, align: 64, offset: 4160)
!1334 = !DIDerivedType(tag: DW_TAG_member, name: "oauth_bearer", scope: !541, file: !130, line: 975, baseType: !215, size: 64, align: 64, offset: 4224)
!1335 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !541, file: !130, line: 977, baseType: !177, size: 32, align: 32, offset: 4288)
!1336 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !541, file: !130, line: 978, baseType: !177, size: 32, align: 32, offset: 4320)
!1337 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !541, file: !130, line: 980, baseType: !201, size: 128, align: 64, offset: 4352)
!1338 = !DIDerivedType(tag: DW_TAG_member, name: "created", scope: !541, file: !130, line: 981, baseType: !201, size: 128, align: 64, offset: 4480)
!1339 = !DIDerivedType(tag: DW_TAG_member, name: "sock", scope: !541, file: !130, line: 982, baseType: !1340, size: 64, align: 32, offset: 4608)
!1340 = !DICompositeType(tag: DW_TAG_array_type, baseType: !248, size: 64, align: 32, elements: !1300)
!1341 = !DIDerivedType(tag: DW_TAG_member, name: "tempsock", scope: !541, file: !130, line: 984, baseType: !1340, size: 64, align: 32, offset: 4672)
!1342 = !DIDerivedType(tag: DW_TAG_member, name: "sock_accepted", scope: !541, file: !130, line: 985, baseType: !1343, size: 16, align: 8, offset: 4736)
!1343 = !DICompositeType(tag: DW_TAG_array_type, baseType: !211, size: 16, align: 8, elements: !1300)
!1344 = !DIDerivedType(tag: DW_TAG_member, name: "recv", scope: !541, file: !130, line: 987, baseType: !1345, size: 128, align: 64, offset: 4800)
!1345 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1346, size: 128, align: 64, elements: !1300)
!1346 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1347, size: 64, align: 64)
!1347 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_recv", file: !130, line: 863, baseType: !1348)
!1348 = !DISubroutineType(types: !1349)
!1349 = !{!256, !550, !177, !215, !158, !1350}
!1350 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !554, size: 64, align: 64)
!1351 = !DIDerivedType(tag: DW_TAG_member, name: "send", scope: !541, file: !130, line: 988, baseType: !1352, size: 128, align: 64, offset: 4928)
!1352 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1353, size: 128, align: 64, elements: !1300)
!1353 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1354, size: 64, align: 64)
!1354 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_send", file: !130, line: 856, baseType: !1355)
!1355 = !DISubroutineType(types: !1356)
!1356 = !{!256, !550, !177, !995, !158, !1350}
!1357 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !541, file: !130, line: 993, baseType: !1358, size: 192, align: 32, offset: 5056)
!1358 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1359, size: 192, align: 32, elements: !1300)
!1359 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_connect_data", file: !130, line: 274, size: 96, align: 32, elements: !1360)
!1360 = !{!1361, !1362, !1364}
!1361 = !DIDerivedType(tag: DW_TAG_member, name: "use", scope: !1359, file: !130, line: 278, baseType: !211, size: 8, align: 8)
!1362 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1359, file: !130, line: 279, baseType: !1363, size: 32, align: 32, offset: 32)
!1363 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connection_state", file: !130, line: 271, baseType: !410)
!1364 = !DIDerivedType(tag: DW_TAG_member, name: "connecting_state", scope: !1359, file: !130, line: 280, baseType: !1365, size: 32, align: 32, offset: 64)
!1365 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connect_state", file: !130, line: 265, baseType: !415)
!1366 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !541, file: !130, line: 994, baseType: !1358, size: 192, align: 32, offset: 5248)
!1367 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !541, file: !130, line: 995, baseType: !870, size: 640, align: 64, offset: 5440)
!1368 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_config", scope: !541, file: !130, line: 996, baseType: !870, size: 640, align: 64, offset: 6080)
!1369 = !DIDerivedType(tag: DW_TAG_member, name: "tls_upgraded", scope: !541, file: !130, line: 997, baseType: !211, size: 8, align: 8, offset: 6720)
!1370 = !DIDerivedType(tag: DW_TAG_member, name: "bits", scope: !541, file: !130, line: 999, baseType: !1371, size: 280, align: 8, offset: 6728)
!1371 = !DICompositeType(tag: DW_TAG_structure_type, name: "ConnectBits", file: !130, line: 514, size: 280, align: 8, elements: !1372)
!1372 = !{!1373, !1374, !1375, !1376, !1377, !1378, !1379, !1380, !1381, !1382, !1383, !1384, !1385, !1386, !1387, !1388, !1389, !1390, !1391, !1392, !1393, !1394, !1395, !1396, !1397, !1398, !1399, !1400, !1401, !1402, !1403, !1404, !1405}
!1373 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !1371, file: !130, line: 516, baseType: !211, size: 8, align: 8)
!1374 = !DIDerivedType(tag: DW_TAG_member, name: "reuse", scope: !1371, file: !130, line: 517, baseType: !211, size: 8, align: 8, offset: 8)
!1375 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !1371, file: !130, line: 518, baseType: !211, size: 8, align: 8, offset: 16)
!1376 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !1371, file: !130, line: 520, baseType: !211, size: 8, align: 8, offset: 24)
!1377 = !DIDerivedType(tag: DW_TAG_member, name: "proxy", scope: !1371, file: !130, line: 522, baseType: !211, size: 8, align: 8, offset: 32)
!1378 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxy", scope: !1371, file: !130, line: 523, baseType: !211, size: 8, align: 8, offset: 40)
!1379 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy", scope: !1371, file: !130, line: 524, baseType: !211, size: 8, align: 8, offset: 48)
!1380 = !DIDerivedType(tag: DW_TAG_member, name: "user_passwd", scope: !1371, file: !130, line: 525, baseType: !211, size: 8, align: 8, offset: 56)
!1381 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_user_passwd", scope: !1371, file: !130, line: 526, baseType: !211, size: 8, align: 8, offset: 64)
!1382 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6_ip", scope: !1371, file: !130, line: 527, baseType: !211, size: 8, align: 8, offset: 72)
!1383 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6", scope: !1371, file: !130, line: 529, baseType: !211, size: 8, align: 8, offset: 80)
!1384 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1371, file: !130, line: 531, baseType: !211, size: 8, align: 8, offset: 88)
!1385 = !DIDerivedType(tag: DW_TAG_member, name: "tcpconnect", scope: !1371, file: !130, line: 533, baseType: !1343, size: 16, align: 8, offset: 96)
!1386 = !DIDerivedType(tag: DW_TAG_member, name: "protoconnstart", scope: !1371, file: !130, line: 535, baseType: !211, size: 8, align: 8, offset: 112)
!1387 = !DIDerivedType(tag: DW_TAG_member, name: "retry", scope: !1371, file: !130, line: 538, baseType: !211, size: 8, align: 8, offset: 120)
!1388 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_proxy", scope: !1371, file: !130, line: 540, baseType: !211, size: 8, align: 8, offset: 128)
!1389 = !DIDerivedType(tag: DW_TAG_member, name: "authneg", scope: !1371, file: !130, line: 544, baseType: !211, size: 8, align: 8, offset: 136)
!1390 = !DIDerivedType(tag: DW_TAG_member, name: "rewindaftersend", scope: !1371, file: !130, line: 548, baseType: !211, size: 8, align: 8, offset: 144)
!1391 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !1371, file: !130, line: 552, baseType: !211, size: 8, align: 8, offset: 152)
!1392 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !1371, file: !130, line: 556, baseType: !211, size: 8, align: 8, offset: 160)
!1393 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_data_ssl", scope: !1371, file: !130, line: 559, baseType: !211, size: 8, align: 8, offset: 168)
!1394 = !DIDerivedType(tag: DW_TAG_member, name: "netrc", scope: !1371, file: !130, line: 560, baseType: !211, size: 8, align: 8, offset: 176)
!1395 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd_in_url", scope: !1371, file: !130, line: 561, baseType: !211, size: 8, align: 8, offset: 184)
!1396 = !DIDerivedType(tag: DW_TAG_member, name: "stream_was_rewound", scope: !1371, file: !130, line: 562, baseType: !211, size: 8, align: 8, offset: 192)
!1397 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_connect_closed", scope: !1371, file: !130, line: 565, baseType: !211, size: 8, align: 8, offset: 200)
!1398 = !DIDerivedType(tag: DW_TAG_member, name: "bound", scope: !1371, file: !130, line: 568, baseType: !211, size: 8, align: 8, offset: 208)
!1399 = !DIDerivedType(tag: DW_TAG_member, name: "type_set", scope: !1371, file: !130, line: 570, baseType: !211, size: 8, align: 8, offset: 216)
!1400 = !DIDerivedType(tag: DW_TAG_member, name: "multiplex", scope: !1371, file: !130, line: 571, baseType: !211, size: 8, align: 8, offset: 224)
!1401 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !1371, file: !130, line: 573, baseType: !211, size: 8, align: 8, offset: 232)
!1402 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_npn", scope: !1371, file: !130, line: 574, baseType: !211, size: 8, align: 8, offset: 240)
!1403 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_alpn", scope: !1371, file: !130, line: 575, baseType: !211, size: 8, align: 8, offset: 248)
!1404 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_connected", scope: !1371, file: !130, line: 576, baseType: !1343, size: 16, align: 8, offset: 256)
!1405 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy_connecting", scope: !1371, file: !130, line: 578, baseType: !211, size: 8, align: 8, offset: 272)
!1406 = !DIDerivedType(tag: DW_TAG_member, name: "connecttime", scope: !541, file: !130, line: 1004, baseType: !201, size: 128, align: 64, offset: 7040)
!1407 = !DIDerivedType(tag: DW_TAG_member, name: "num_addr", scope: !541, file: !130, line: 1006, baseType: !177, size: 32, align: 32, offset: 7168)
!1408 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutms_per_addr", scope: !541, file: !130, line: 1007, baseType: !242, size: 64, align: 64, offset: 7232)
!1409 = !DIDerivedType(tag: DW_TAG_member, name: "handler", scope: !541, file: !130, line: 1010, baseType: !1410, size: 64, align: 64, offset: 7296)
!1410 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1411, size: 64, align: 64)
!1411 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1412)
!1412 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_handler", file: !130, line: 763, size: 1024, align: 64, elements: !1413)
!1413 = !{!1414, !1415, !1419, !1424, !1429, !1435, !1436, !1437, !1438, !1443, !1444, !1445, !1451, !1455, !1460, !1461, !1462}
!1414 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !1412, file: !130, line: 764, baseType: !928, size: 64, align: 64)
!1415 = !DIDerivedType(tag: DW_TAG_member, name: "setup_connection", scope: !1412, file: !130, line: 767, baseType: !1416, size: 64, align: 64, offset: 64)
!1416 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1417, size: 64, align: 64)
!1417 = !DISubroutineType(types: !1418)
!1418 = !{!554, !550}
!1419 = !DIDerivedType(tag: DW_TAG_member, name: "do_it", scope: !1412, file: !130, line: 770, baseType: !1420, size: 64, align: 64, offset: 128)
!1420 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1421, size: 64, align: 64)
!1421 = !DISubroutineType(types: !1422)
!1422 = !{!554, !550, !1423}
!1423 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !211, size: 64, align: 64)
!1424 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1412, file: !130, line: 771, baseType: !1425, size: 64, align: 64, offset: 192)
!1425 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_done_func", file: !130, line: 634, baseType: !1426)
!1426 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1427, size: 64, align: 64)
!1427 = !DISubroutineType(types: !1428)
!1428 = !{!554, !550, !554, !211}
!1429 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1412, file: !130, line: 777, baseType: !1430, size: 64, align: 64, offset: 256)
!1430 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_do_more_func", file: !130, line: 633, baseType: !1431)
!1431 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1432, size: 64, align: 64)
!1432 = !DISubroutineType(types: !1433)
!1433 = !{!554, !550, !1434}
!1434 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!1435 = !DIDerivedType(tag: DW_TAG_member, name: "connect_it", scope: !1412, file: !130, line: 785, baseType: !1420, size: 64, align: 64, offset: 320)
!1436 = !DIDerivedType(tag: DW_TAG_member, name: "connecting", scope: !1412, file: !130, line: 788, baseType: !1420, size: 64, align: 64, offset: 384)
!1437 = !DIDerivedType(tag: DW_TAG_member, name: "doing", scope: !1412, file: !130, line: 789, baseType: !1420, size: 64, align: 64, offset: 448)
!1438 = !DIDerivedType(tag: DW_TAG_member, name: "proto_getsock", scope: !1412, file: !130, line: 793, baseType: !1439, size: 64, align: 64, offset: 512)
!1439 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1440, size: 64, align: 64)
!1440 = !DISubroutineType(types: !1441)
!1441 = !{!177, !550, !1442, !177}
!1442 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!1443 = !DIDerivedType(tag: DW_TAG_member, name: "doing_getsock", scope: !1412, file: !130, line: 799, baseType: !1439, size: 64, align: 64, offset: 576)
!1444 = !DIDerivedType(tag: DW_TAG_member, name: "domore_getsock", scope: !1412, file: !130, line: 805, baseType: !1439, size: 64, align: 64, offset: 640)
!1445 = !DIDerivedType(tag: DW_TAG_member, name: "perform_getsock", scope: !1412, file: !130, line: 812, baseType: !1446, size: 64, align: 64, offset: 704)
!1446 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1447, size: 64, align: 64)
!1447 = !DISubroutineType(types: !1448)
!1448 = !{!177, !1449, !1442, !177}
!1449 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1450, size: 64, align: 64)
!1450 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !541)
!1451 = !DIDerivedType(tag: DW_TAG_member, name: "disconnect", scope: !1412, file: !130, line: 821, baseType: !1452, size: 64, align: 64, offset: 768)
!1452 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1453, size: 64, align: 64)
!1453 = !DISubroutineType(types: !1454)
!1454 = !{!554, !550, !211}
!1455 = !DIDerivedType(tag: DW_TAG_member, name: "readwrite", scope: !1412, file: !130, line: 825, baseType: !1456, size: 64, align: 64, offset: 832)
!1456 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1457, size: 64, align: 64)
!1457 = !DISubroutineType(types: !1458)
!1458 = !{!554, !544, !550, !1459, !1423}
!1459 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !256, size: 64, align: 64)
!1460 = !DIDerivedType(tag: DW_TAG_member, name: "defport", scope: !1412, file: !130, line: 828, baseType: !191, size: 64, align: 64, offset: 896)
!1461 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !1412, file: !130, line: 829, baseType: !782, size: 32, align: 32, offset: 960)
!1462 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1412, file: !130, line: 831, baseType: !782, size: 32, align: 32, offset: 992)
!1463 = !DIDerivedType(tag: DW_TAG_member, name: "given", scope: !541, file: !130, line: 1011, baseType: !1410, size: 64, align: 64, offset: 7360)
!1464 = !DIDerivedType(tag: DW_TAG_member, name: "ip_version", scope: !541, file: !130, line: 1013, baseType: !191, size: 64, align: 64, offset: 7424)
!1465 = !DIDerivedType(tag: DW_TAG_member, name: "sockfd", scope: !541, file: !130, line: 1017, baseType: !248, size: 32, align: 32, offset: 7488)
!1466 = !DIDerivedType(tag: DW_TAG_member, name: "writesockfd", scope: !541, file: !130, line: 1018, baseType: !248, size: 32, align: 32, offset: 7520)
!1467 = !DIDerivedType(tag: DW_TAG_member, name: "allocptr", scope: !541, file: !130, line: 1035, baseType: !1468, size: 640, align: 64, offset: 7552)
!1468 = !DICompositeType(tag: DW_TAG_structure_type, name: "dynamically_allocated_data", file: !130, line: 1024, size: 640, align: 64, elements: !1469)
!1469 = !{!1470, !1471, !1472, !1473, !1474, !1475, !1476, !1477, !1478, !1479}
!1470 = !DIDerivedType(tag: DW_TAG_member, name: "proxyuserpwd", scope: !1468, file: !130, line: 1025, baseType: !215, size: 64, align: 64)
!1471 = !DIDerivedType(tag: DW_TAG_member, name: "uagent", scope: !1468, file: !130, line: 1026, baseType: !215, size: 64, align: 64, offset: 64)
!1472 = !DIDerivedType(tag: DW_TAG_member, name: "accept_encoding", scope: !1468, file: !130, line: 1027, baseType: !215, size: 64, align: 64, offset: 128)
!1473 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd", scope: !1468, file: !130, line: 1028, baseType: !215, size: 64, align: 64, offset: 192)
!1474 = !DIDerivedType(tag: DW_TAG_member, name: "rangeline", scope: !1468, file: !130, line: 1029, baseType: !215, size: 64, align: 64, offset: 256)
!1475 = !DIDerivedType(tag: DW_TAG_member, name: "ref", scope: !1468, file: !130, line: 1030, baseType: !215, size: 64, align: 64, offset: 320)
!1476 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1468, file: !130, line: 1031, baseType: !215, size: 64, align: 64, offset: 384)
!1477 = !DIDerivedType(tag: DW_TAG_member, name: "cookiehost", scope: !1468, file: !130, line: 1032, baseType: !215, size: 64, align: 64, offset: 448)
!1478 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_transport", scope: !1468, file: !130, line: 1033, baseType: !215, size: 64, align: 64, offset: 512)
!1479 = !DIDerivedType(tag: DW_TAG_member, name: "te", scope: !1468, file: !130, line: 1034, baseType: !215, size: 64, align: 64, offset: 576)
!1480 = !DIDerivedType(tag: DW_TAG_member, name: "readchannel_inuse", scope: !541, file: !130, line: 1057, baseType: !211, size: 8, align: 8, offset: 8192)
!1481 = !DIDerivedType(tag: DW_TAG_member, name: "writechannel_inuse", scope: !541, file: !130, line: 1059, baseType: !211, size: 8, align: 8, offset: 8200)
!1482 = !DIDerivedType(tag: DW_TAG_member, name: "send_pipe", scope: !541, file: !130, line: 1061, baseType: !140, size: 256, align: 64, offset: 8256)
!1483 = !DIDerivedType(tag: DW_TAG_member, name: "recv_pipe", scope: !541, file: !130, line: 1063, baseType: !140, size: 256, align: 64, offset: 8512)
!1484 = !DIDerivedType(tag: DW_TAG_member, name: "master_buffer", scope: !541, file: !130, line: 1065, baseType: !215, size: 64, align: 64, offset: 8768)
!1485 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !541, file: !130, line: 1067, baseType: !158, size: 64, align: 64, offset: 8832)
!1486 = !DIDerivedType(tag: DW_TAG_member, name: "buf_len", scope: !541, file: !130, line: 1068, baseType: !158, size: 64, align: 64, offset: 8896)
!1487 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !541, file: !130, line: 1071, baseType: !722, size: 64, align: 64, offset: 8960)
!1488 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !541, file: !130, line: 1072, baseType: !148, size: 64, align: 64, offset: 9024)
!1489 = !DIDerivedType(tag: DW_TAG_member, name: "syserr_buf", scope: !541, file: !130, line: 1091, baseType: !1490, size: 2048, align: 8, offset: 9088)
!1490 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 2048, align: 8, elements: !1491)
!1491 = !{!1492}
!1492 = !DISubrange(count: 256)
!1493 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !541, file: !130, line: 1099, baseType: !215, size: 64, align: 64, offset: 11136)
!1494 = !DIDerivedType(tag: DW_TAG_member, name: "trlMax", scope: !541, file: !130, line: 1100, baseType: !177, size: 32, align: 32, offset: 11200)
!1495 = !DIDerivedType(tag: DW_TAG_member, name: "trlPos", scope: !541, file: !130, line: 1101, baseType: !177, size: 32, align: 32, offset: 11232)
!1496 = !DIDerivedType(tag: DW_TAG_member, name: "proto", scope: !541, file: !130, line: 1114, baseType: !1497, size: 1792, align: 64, offset: 11264)
!1497 = !DICompositeType(tag: DW_TAG_union_type, scope: !541, file: !130, line: 1103, size: 1792, align: 64, elements: !1498)
!1498 = !{!1499, !1546, !1551, !1556, !1559, !1607, !1621, !1633, !1640, !1658}
!1499 = !DIDerivedType(tag: DW_TAG_member, name: "ftpc", scope: !1497, file: !130, line: 1104, baseType: !1500, size: 1792, align: 64)
!1500 = !DICompositeType(tag: DW_TAG_structure_type, name: "ftp_conn", file: !317, line: 118, size: 1792, align: 64, elements: !1501)
!1501 = !{!1502, !1522, !1523, !1525, !1526, !1527, !1528, !1529, !1530, !1531, !1532, !1533, !1534, !1535, !1536, !1537, !1538, !1540, !1541, !1542, !1543, !1544, !1545}
!1502 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1500, file: !317, line: 119, baseType: !1503, size: 896, align: 64)
!1503 = !DICompositeType(tag: DW_TAG_structure_type, name: "pingpong", file: !1504, line: 48, size: 896, align: 64, elements: !1505)
!1504 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pingpong.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1505 = !{!1506, !1507, !1508, !1509, !1510, !1511, !1512, !1513, !1514, !1515, !1516, !1517, !1518}
!1506 = !DIDerivedType(tag: DW_TAG_member, name: "cache", scope: !1503, file: !1504, line: 49, baseType: !215, size: 64, align: 64)
!1507 = !DIDerivedType(tag: DW_TAG_member, name: "cache_size", scope: !1503, file: !1504, line: 50, baseType: !158, size: 64, align: 64, offset: 64)
!1508 = !DIDerivedType(tag: DW_TAG_member, name: "nread_resp", scope: !1503, file: !1504, line: 51, baseType: !158, size: 64, align: 64, offset: 128)
!1509 = !DIDerivedType(tag: DW_TAG_member, name: "linestart_resp", scope: !1503, file: !1504, line: 52, baseType: !215, size: 64, align: 64, offset: 192)
!1510 = !DIDerivedType(tag: DW_TAG_member, name: "pending_resp", scope: !1503, file: !1504, line: 54, baseType: !211, size: 8, align: 8, offset: 256)
!1511 = !DIDerivedType(tag: DW_TAG_member, name: "sendthis", scope: !1503, file: !1504, line: 57, baseType: !215, size: 64, align: 64, offset: 320)
!1512 = !DIDerivedType(tag: DW_TAG_member, name: "sendleft", scope: !1503, file: !1504, line: 59, baseType: !158, size: 64, align: 64, offset: 384)
!1513 = !DIDerivedType(tag: DW_TAG_member, name: "sendsize", scope: !1503, file: !1504, line: 60, baseType: !158, size: 64, align: 64, offset: 448)
!1514 = !DIDerivedType(tag: DW_TAG_member, name: "response", scope: !1503, file: !1504, line: 61, baseType: !201, size: 128, align: 64, offset: 512)
!1515 = !DIDerivedType(tag: DW_TAG_member, name: "response_time", scope: !1503, file: !1504, line: 63, baseType: !191, size: 64, align: 64, offset: 640)
!1516 = !DIDerivedType(tag: DW_TAG_member, name: "conn", scope: !1503, file: !1504, line: 66, baseType: !550, size: 64, align: 64, offset: 704)
!1517 = !DIDerivedType(tag: DW_TAG_member, name: "statemach_act", scope: !1503, file: !1504, line: 72, baseType: !1416, size: 64, align: 64, offset: 768)
!1518 = !DIDerivedType(tag: DW_TAG_member, name: "endofresp", scope: !1503, file: !1504, line: 74, baseType: !1519, size: 64, align: 64, offset: 832)
!1519 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1520, size: 64, align: 64)
!1520 = !DISubroutineType(types: !1521)
!1521 = !{!211, !550, !215, !158, !1434}
!1522 = !DIDerivedType(tag: DW_TAG_member, name: "entrypath", scope: !1500, file: !317, line: 120, baseType: !215, size: 64, align: 64, offset: 896)
!1523 = !DIDerivedType(tag: DW_TAG_member, name: "dirs", scope: !1500, file: !317, line: 121, baseType: !1524, size: 64, align: 64, offset: 960)
!1524 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !215, size: 64, align: 64)
!1525 = !DIDerivedType(tag: DW_TAG_member, name: "dirdepth", scope: !1500, file: !317, line: 122, baseType: !177, size: 32, align: 32, offset: 1024)
!1526 = !DIDerivedType(tag: DW_TAG_member, name: "diralloc", scope: !1500, file: !317, line: 123, baseType: !177, size: 32, align: 32, offset: 1056)
!1527 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !1500, file: !317, line: 124, baseType: !215, size: 64, align: 64, offset: 1088)
!1528 = !DIDerivedType(tag: DW_TAG_member, name: "dont_check", scope: !1500, file: !317, line: 125, baseType: !211, size: 8, align: 8, offset: 1152)
!1529 = !DIDerivedType(tag: DW_TAG_member, name: "ctl_valid", scope: !1500, file: !317, line: 128, baseType: !211, size: 8, align: 8, offset: 1160)
!1530 = !DIDerivedType(tag: DW_TAG_member, name: "cwddone", scope: !1500, file: !317, line: 131, baseType: !211, size: 8, align: 8, offset: 1168)
!1531 = !DIDerivedType(tag: DW_TAG_member, name: "cwdfail", scope: !1500, file: !317, line: 133, baseType: !211, size: 8, align: 8, offset: 1176)
!1532 = !DIDerivedType(tag: DW_TAG_member, name: "wait_data_conn", scope: !1500, file: !317, line: 135, baseType: !211, size: 8, align: 8, offset: 1184)
!1533 = !DIDerivedType(tag: DW_TAG_member, name: "prevpath", scope: !1500, file: !317, line: 136, baseType: !215, size: 64, align: 64, offset: 1216)
!1534 = !DIDerivedType(tag: DW_TAG_member, name: "transfertype", scope: !1500, file: !317, line: 137, baseType: !216, size: 8, align: 8, offset: 1280)
!1535 = !DIDerivedType(tag: DW_TAG_member, name: "count1", scope: !1500, file: !317, line: 139, baseType: !177, size: 32, align: 32, offset: 1312)
!1536 = !DIDerivedType(tag: DW_TAG_member, name: "count2", scope: !1500, file: !317, line: 140, baseType: !177, size: 32, align: 32, offset: 1344)
!1537 = !DIDerivedType(tag: DW_TAG_member, name: "count3", scope: !1500, file: !317, line: 141, baseType: !177, size: 32, align: 32, offset: 1376)
!1538 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1500, file: !317, line: 142, baseType: !1539, size: 32, align: 32, offset: 1408)
!1539 = !DIDerivedType(tag: DW_TAG_typedef, name: "ftpstate", file: !317, line: 80, baseType: !423)
!1540 = !DIDerivedType(tag: DW_TAG_member, name: "state_saved", scope: !1500, file: !317, line: 143, baseType: !1539, size: 32, align: 32, offset: 1440)
!1541 = !DIDerivedType(tag: DW_TAG_member, name: "retr_size_saved", scope: !1500, file: !317, line: 145, baseType: !189, size: 64, align: 64, offset: 1472)
!1542 = !DIDerivedType(tag: DW_TAG_member, name: "server_os", scope: !1500, file: !317, line: 146, baseType: !215, size: 64, align: 64, offset: 1536)
!1543 = !DIDerivedType(tag: DW_TAG_member, name: "known_filesize", scope: !1500, file: !317, line: 147, baseType: !189, size: 64, align: 64, offset: 1600)
!1544 = !DIDerivedType(tag: DW_TAG_member, name: "newhost", scope: !1500, file: !317, line: 152, baseType: !215, size: 64, align: 64, offset: 1664)
!1545 = !DIDerivedType(tag: DW_TAG_member, name: "newport", scope: !1500, file: !317, line: 153, baseType: !684, size: 16, align: 16, offset: 1728)
!1546 = !DIDerivedType(tag: DW_TAG_member, name: "httpc", scope: !1497, file: !130, line: 1105, baseType: !1547, size: 32, align: 32)
!1547 = !DICompositeType(tag: DW_TAG_structure_type, name: "http_conn", file: !1548, line: 200, size: 32, align: 32, elements: !1549)
!1548 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1549 = !{!1550}
!1550 = !DIDerivedType(tag: DW_TAG_member, name: "unused", scope: !1547, file: !1548, line: 227, baseType: !177, size: 32, align: 32)
!1551 = !DIDerivedType(tag: DW_TAG_member, name: "sshc", scope: !1497, file: !130, line: 1106, baseType: !1552, size: 64, align: 64)
!1552 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssh_conn", file: !1553, line: 110, size: 64, align: 64, elements: !1554)
!1553 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/ssh.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1554 = !{!1555}
!1555 = !DIDerivedType(tag: DW_TAG_member, name: "authlist", scope: !1552, file: !1553, line: 111, baseType: !928, size: 64, align: 64)
!1556 = !DIDerivedType(tag: DW_TAG_member, name: "tftpc", scope: !1497, file: !130, line: 1107, baseType: !1557, size: 64, align: 64)
!1557 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1558, size: 64, align: 64)
!1558 = !DICompositeType(tag: DW_TAG_structure_type, name: "tftp_state_data", file: !130, line: 1107, flags: DIFlagFwdDecl)
!1559 = !DIDerivedType(tag: DW_TAG_member, name: "imapc", scope: !1497, file: !130, line: 1108, baseType: !1560, size: 1472, align: 64)
!1560 = !DICompositeType(tag: DW_TAG_structure_type, name: "imap_conn", file: !462, line: 70, size: 1472, align: 64, elements: !1561)
!1561 = !{!1562, !1563, !1565, !1566, !1598, !1599, !1600, !1602, !1603, !1604, !1605, !1606}
!1562 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1560, file: !462, line: 71, baseType: !1503, size: 896, align: 64)
!1563 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1560, file: !462, line: 72, baseType: !1564, size: 32, align: 32, offset: 896)
!1564 = !DIDerivedType(tag: DW_TAG_typedef, name: "imapstate", file: !462, line: 50, baseType: !461)
!1565 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1560, file: !462, line: 73, baseType: !211, size: 8, align: 8, offset: 928)
!1566 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1560, file: !462, line: 74, baseType: !1567, size: 256, align: 64, offset: 960)
!1567 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASL", file: !481, line: 101, size: 256, align: 64, elements: !1568)
!1568 = !{!1569, !1590, !1592, !1593, !1594, !1595, !1596, !1597}
!1569 = !DIDerivedType(tag: DW_TAG_member, name: "params", scope: !1567, file: !481, line: 102, baseType: !1570, size: 64, align: 64)
!1570 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1571, size: 64, align: 64)
!1571 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1572)
!1572 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASLproto", file: !481, line: 86, size: 384, align: 64, elements: !1573)
!1573 = !{!1574, !1575, !1576, !1577, !1578, !1582, !1586}
!1574 = !DIDerivedType(tag: DW_TAG_member, name: "service", scope: !1572, file: !481, line: 87, baseType: !928, size: 64, align: 64)
!1575 = !DIDerivedType(tag: DW_TAG_member, name: "contcode", scope: !1572, file: !481, line: 88, baseType: !177, size: 32, align: 32, offset: 64)
!1576 = !DIDerivedType(tag: DW_TAG_member, name: "finalcode", scope: !1572, file: !481, line: 89, baseType: !177, size: 32, align: 32, offset: 96)
!1577 = !DIDerivedType(tag: DW_TAG_member, name: "maxirlen", scope: !1572, file: !481, line: 90, baseType: !158, size: 64, align: 64, offset: 128)
!1578 = !DIDerivedType(tag: DW_TAG_member, name: "sendauth", scope: !1572, file: !481, line: 91, baseType: !1579, size: 64, align: 64, offset: 192)
!1579 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1580, size: 64, align: 64)
!1580 = !DISubroutineType(types: !1581)
!1581 = !{!554, !550, !928, !928}
!1582 = !DIDerivedType(tag: DW_TAG_member, name: "sendcont", scope: !1572, file: !481, line: 94, baseType: !1583, size: 64, align: 64, offset: 256)
!1583 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1584, size: 64, align: 64)
!1584 = !DISubroutineType(types: !1585)
!1585 = !{!554, !550, !928}
!1586 = !DIDerivedType(tag: DW_TAG_member, name: "getmessage", scope: !1572, file: !481, line: 96, baseType: !1587, size: 64, align: 64, offset: 320)
!1587 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1588, size: 64, align: 64)
!1588 = !DISubroutineType(types: !1589)
!1589 = !{null, !215, !1524}
!1590 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1567, file: !481, line: 103, baseType: !1591, size: 32, align: 32, offset: 64)
!1591 = !DIDerivedType(tag: DW_TAG_typedef, name: "saslstate", file: !481, line: 76, baseType: !480)
!1592 = !DIDerivedType(tag: DW_TAG_member, name: "authmechs", scope: !1567, file: !481, line: 104, baseType: !782, size: 32, align: 32, offset: 96)
!1593 = !DIDerivedType(tag: DW_TAG_member, name: "prefmech", scope: !1567, file: !481, line: 105, baseType: !782, size: 32, align: 32, offset: 128)
!1594 = !DIDerivedType(tag: DW_TAG_member, name: "authused", scope: !1567, file: !481, line: 106, baseType: !782, size: 32, align: 32, offset: 160)
!1595 = !DIDerivedType(tag: DW_TAG_member, name: "resetprefs", scope: !1567, file: !481, line: 107, baseType: !211, size: 8, align: 8, offset: 192)
!1596 = !DIDerivedType(tag: DW_TAG_member, name: "mutual_auth", scope: !1567, file: !481, line: 108, baseType: !211, size: 8, align: 8, offset: 200)
!1597 = !DIDerivedType(tag: DW_TAG_member, name: "force_ir", scope: !1567, file: !481, line: 109, baseType: !211, size: 8, align: 8, offset: 208)
!1598 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1560, file: !462, line: 75, baseType: !782, size: 32, align: 32, offset: 1216)
!1599 = !DIDerivedType(tag: DW_TAG_member, name: "cmdid", scope: !1560, file: !462, line: 76, baseType: !177, size: 32, align: 32, offset: 1248)
!1600 = !DIDerivedType(tag: DW_TAG_member, name: "resptag", scope: !1560, file: !462, line: 77, baseType: !1601, size: 40, align: 8, offset: 1280)
!1601 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 40, align: 8, elements: !573)
!1602 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1560, file: !462, line: 78, baseType: !211, size: 8, align: 8, offset: 1320)
!1603 = !DIDerivedType(tag: DW_TAG_member, name: "login_disabled", scope: !1560, file: !462, line: 79, baseType: !211, size: 8, align: 8, offset: 1328)
!1604 = !DIDerivedType(tag: DW_TAG_member, name: "ir_supported", scope: !1560, file: !462, line: 80, baseType: !211, size: 8, align: 8, offset: 1336)
!1605 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox", scope: !1560, file: !462, line: 81, baseType: !215, size: 64, align: 64, offset: 1344)
!1606 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox_uidvalidity", scope: !1560, file: !462, line: 82, baseType: !215, size: 64, align: 64, offset: 1408)
!1607 = !DIDerivedType(tag: DW_TAG_member, name: "pop3c", scope: !1497, file: !130, line: 1109, baseType: !1608, size: 1536, align: 64)
!1608 = !DICompositeType(tag: DW_TAG_structure_type, name: "pop3_conn", file: !501, line: 60, size: 1536, align: 64, elements: !1609)
!1609 = !{!1610, !1611, !1613, !1614, !1615, !1616, !1617, !1618, !1619, !1620}
!1610 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1608, file: !501, line: 61, baseType: !1503, size: 896, align: 64)
!1611 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1608, file: !501, line: 62, baseType: !1612, size: 32, align: 32, offset: 896)
!1612 = !DIDerivedType(tag: DW_TAG_typedef, name: "pop3state", file: !501, line: 46, baseType: !500)
!1613 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1608, file: !501, line: 63, baseType: !211, size: 8, align: 8, offset: 928)
!1614 = !DIDerivedType(tag: DW_TAG_member, name: "eob", scope: !1608, file: !501, line: 64, baseType: !158, size: 64, align: 64, offset: 960)
!1615 = !DIDerivedType(tag: DW_TAG_member, name: "strip", scope: !1608, file: !501, line: 66, baseType: !158, size: 64, align: 64, offset: 1024)
!1616 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1608, file: !501, line: 68, baseType: !1567, size: 256, align: 64, offset: 1088)
!1617 = !DIDerivedType(tag: DW_TAG_member, name: "authtypes", scope: !1608, file: !501, line: 69, baseType: !782, size: 32, align: 32, offset: 1344)
!1618 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1608, file: !501, line: 70, baseType: !782, size: 32, align: 32, offset: 1376)
!1619 = !DIDerivedType(tag: DW_TAG_member, name: "apoptimestamp", scope: !1608, file: !501, line: 71, baseType: !215, size: 64, align: 64, offset: 1408)
!1620 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1608, file: !501, line: 72, baseType: !211, size: 8, align: 8, offset: 1472)
!1621 = !DIDerivedType(tag: DW_TAG_member, name: "smtpc", scope: !1497, file: !130, line: 1110, baseType: !1622, size: 1344, align: 64)
!1622 = !DICompositeType(tag: DW_TAG_structure_type, name: "smtp_conn", file: !516, line: 65, size: 1344, align: 64, elements: !1623)
!1623 = !{!1624, !1625, !1627, !1628, !1629, !1630, !1631, !1632}
!1624 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1622, file: !516, line: 66, baseType: !1503, size: 896, align: 64)
!1625 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1622, file: !516, line: 67, baseType: !1626, size: 32, align: 32, offset: 896)
!1626 = !DIDerivedType(tag: DW_TAG_typedef, name: "smtpstate", file: !516, line: 48, baseType: !515)
!1627 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1622, file: !516, line: 68, baseType: !211, size: 8, align: 8, offset: 928)
!1628 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1622, file: !516, line: 69, baseType: !215, size: 64, align: 64, offset: 960)
!1629 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1622, file: !516, line: 70, baseType: !1567, size: 256, align: 64, offset: 1024)
!1630 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1622, file: !516, line: 71, baseType: !211, size: 8, align: 8, offset: 1280)
!1631 = !DIDerivedType(tag: DW_TAG_member, name: "size_supported", scope: !1622, file: !516, line: 72, baseType: !211, size: 8, align: 8, offset: 1288)
!1632 = !DIDerivedType(tag: DW_TAG_member, name: "auth_supported", scope: !1622, file: !516, line: 74, baseType: !211, size: 8, align: 8, offset: 1296)
!1633 = !DIDerivedType(tag: DW_TAG_member, name: "rtspc", scope: !1497, file: !130, line: 1111, baseType: !1634, size: 192, align: 64)
!1634 = !DICompositeType(tag: DW_TAG_structure_type, name: "rtsp_conn", file: !1635, line: 43, size: 192, align: 64, elements: !1636)
!1635 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/rtsp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1636 = !{!1637, !1638, !1639}
!1637 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_buf", scope: !1634, file: !1635, line: 44, baseType: !215, size: 64, align: 64)
!1638 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_bufsize", scope: !1634, file: !1635, line: 45, baseType: !256, size: 64, align: 64, offset: 64)
!1639 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_channel", scope: !1634, file: !1635, line: 46, baseType: !177, size: 32, align: 32, offset: 128)
!1640 = !DIDerivedType(tag: DW_TAG_member, name: "smbc", scope: !1497, file: !130, line: 1112, baseType: !1641, size: 640, align: 64)
!1641 = !DICompositeType(tag: DW_TAG_structure_type, name: "smb_conn", file: !533, line: 33, size: 640, align: 64, elements: !1642)
!1642 = !{!1643, !1644, !1645, !1646, !1651, !1652, !1653, !1654, !1655, !1656, !1657}
!1643 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1641, file: !533, line: 34, baseType: !532, size: 32, align: 32)
!1644 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1641, file: !533, line: 35, baseType: !215, size: 64, align: 64, offset: 64)
!1645 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1641, file: !533, line: 36, baseType: !215, size: 64, align: 64, offset: 128)
!1646 = !DIDerivedType(tag: DW_TAG_member, name: "challenge", scope: !1641, file: !533, line: 37, baseType: !1647, size: 64, align: 8, offset: 192)
!1647 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1648, size: 64, align: 8, elements: !1649)
!1648 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!1649 = !{!1650}
!1650 = !DISubrange(count: 8)
!1651 = !DIDerivedType(tag: DW_TAG_member, name: "session_key", scope: !1641, file: !533, line: 38, baseType: !782, size: 32, align: 32, offset: 256)
!1652 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !1641, file: !533, line: 39, baseType: !684, size: 16, align: 16, offset: 288)
!1653 = !DIDerivedType(tag: DW_TAG_member, name: "recv_buf", scope: !1641, file: !533, line: 40, baseType: !215, size: 64, align: 64, offset: 320)
!1654 = !DIDerivedType(tag: DW_TAG_member, name: "upload_size", scope: !1641, file: !533, line: 41, baseType: !158, size: 64, align: 64, offset: 384)
!1655 = !DIDerivedType(tag: DW_TAG_member, name: "send_size", scope: !1641, file: !533, line: 42, baseType: !158, size: 64, align: 64, offset: 448)
!1656 = !DIDerivedType(tag: DW_TAG_member, name: "sent", scope: !1641, file: !533, line: 43, baseType: !158, size: 64, align: 64, offset: 512)
!1657 = !DIDerivedType(tag: DW_TAG_member, name: "got", scope: !1641, file: !533, line: 44, baseType: !158, size: 64, align: 64, offset: 576)
!1658 = !DIDerivedType(tag: DW_TAG_member, name: "generic", scope: !1497, file: !130, line: 1113, baseType: !148, size: 64, align: 64)
!1659 = !DIDerivedType(tag: DW_TAG_member, name: "cselect_bits", scope: !541, file: !130, line: 1116, baseType: !177, size: 32, align: 32, offset: 13056)
!1660 = !DIDerivedType(tag: DW_TAG_member, name: "waitfor", scope: !541, file: !130, line: 1117, baseType: !177, size: 32, align: 32, offset: 13088)
!1661 = !DIDerivedType(tag: DW_TAG_member, name: "localdev", scope: !541, file: !130, line: 1128, baseType: !215, size: 64, align: 64, offset: 13120)
!1662 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !541, file: !130, line: 1129, baseType: !684, size: 16, align: 16, offset: 13184)
!1663 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !541, file: !130, line: 1130, baseType: !177, size: 32, align: 32, offset: 13216)
!1664 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_state", scope: !541, file: !130, line: 1137, baseType: !1665, size: 64, align: 32, offset: 13248)
!1665 = !DICompositeType(tag: DW_TAG_array_type, baseType: !540, size: 64, align: 32, elements: !1300)
!1666 = !DIDerivedType(tag: DW_TAG_member, name: "bundle", scope: !541, file: !130, line: 1138, baseType: !1667, size: 64, align: 64, offset: 13312)
!1667 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1668, size: 64, align: 64)
!1668 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectbundle", file: !619, line: 38, size: 384, align: 64, elements: !1669)
!1669 = !{!1670, !1671, !1672}
!1670 = !DIDerivedType(tag: DW_TAG_member, name: "multiuse", scope: !1668, file: !619, line: 39, baseType: !177, size: 32, align: 32)
!1671 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !1668, file: !619, line: 40, baseType: !158, size: 64, align: 64, offset: 64)
!1672 = !DIDerivedType(tag: DW_TAG_member, name: "conn_list", scope: !1668, file: !619, line: 41, baseType: !140, size: 256, align: 64, offset: 128)
!1673 = !DIDerivedType(tag: DW_TAG_member, name: "negnpn", scope: !541, file: !130, line: 1140, baseType: !177, size: 32, align: 32, offset: 13376)
!1674 = !{!1675, !1676, !1677}
!1675 = !DIEnumerator(name: "TUNNEL_INIT", value: 0)
!1676 = !DIEnumerator(name: "TUNNEL_CONNECT", value: 1)
!1677 = !DIEnumerator(name: "TUNNEL_COMPLETE", value: 2)
!1678 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 382, size: 32, align: 32, elements: !1679)
!1679 = !{!1680, !1681, !1682}
!1680 = !DIEnumerator(name: "CURLIOCMD_NOP", value: 0)
!1681 = !DIEnumerator(name: "CURLIOCMD_RESTARTREAD", value: 1)
!1682 = !DIEnumerator(name: "CURLIOCMD_LAST", value: 2)
!1683 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1684, line: 31, size: 32, align: 32, elements: !1685)
!1684 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/transfer.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1685 = !{!1686, !1687, !1688, !1689, !1690}
!1686 = !DIEnumerator(name: "FOLLOW_NONE", value: 0)
!1687 = !DIEnumerator(name: "FOLLOW_FAKE", value: 1)
!1688 = !DIEnumerator(name: "FOLLOW_RETRY", value: 2)
!1689 = !DIEnumerator(name: "FOLLOW_REDIR", value: 3)
!1690 = !DIEnumerator(name: "FOLLOW_LAST", value: 4)
!1691 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1692, line: 28, size: 32, align: 32, elements: !1693)
!1692 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/progress.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1693 = !{!1694, !1695, !1696, !1697, !1698, !1699, !1700, !1701, !1702, !1703, !1704, !1705}
!1694 = !DIEnumerator(name: "TIMER_NONE", value: 0)
!1695 = !DIEnumerator(name: "TIMER_STARTOP", value: 1)
!1696 = !DIEnumerator(name: "TIMER_STARTSINGLE", value: 2)
!1697 = !DIEnumerator(name: "TIMER_NAMELOOKUP", value: 3)
!1698 = !DIEnumerator(name: "TIMER_CONNECT", value: 4)
!1699 = !DIEnumerator(name: "TIMER_APPCONNECT", value: 5)
!1700 = !DIEnumerator(name: "TIMER_PRETRANSFER", value: 6)
!1701 = !DIEnumerator(name: "TIMER_STARTTRANSFER", value: 7)
!1702 = !DIEnumerator(name: "TIMER_POSTRANSFER", value: 8)
!1703 = !DIEnumerator(name: "TIMER_STARTACCEPT", value: 9)
!1704 = !DIEnumerator(name: "TIMER_REDIRECT", value: 10)
!1705 = !DIEnumerator(name: "TIMER_LAST", value: 11)
!1706 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "formtype", file: !1707, line: 25, size: 32, align: 32, elements: !1708)
!1707 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/formdata.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1708 = !{!1709, !1710, !1711, !1712, !1713}
!1709 = !DIEnumerator(name: "FORM_DATAMEM", value: 0)
!1710 = !DIEnumerator(name: "FORM_DATA", value: 1)
!1711 = !DIEnumerator(name: "FORM_CONTENT", value: 2)
!1712 = !DIEnumerator(name: "FORM_CALLBACK", value: 3)
!1713 = !DIEnumerator(name: "FORM_FILE", value: 4)
!1714 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !1715, file: !1548, line: 147, size: 32, align: 32, elements: !1747)
!1715 = !DICompositeType(tag: DW_TAG_structure_type, name: "HTTP", file: !1548, line: 127, size: 1088, align: 64, elements: !1716)
!1716 = !{!1717, !1725, !1726, !1727, !1728, !1729, !1730, !1731, !1738, !1745, !1746}
!1717 = !DIDerivedType(tag: DW_TAG_member, name: "sendit", scope: !1715, file: !1548, line: 128, baseType: !1718, size: 64, align: 64)
!1718 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1719, size: 64, align: 64)
!1719 = !DICompositeType(tag: DW_TAG_structure_type, name: "FormData", file: !1707, line: 36, size: 256, align: 64, elements: !1720)
!1720 = !{!1721, !1722, !1723, !1724}
!1721 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1719, file: !1707, line: 37, baseType: !1718, size: 64, align: 64)
!1722 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !1719, file: !1707, line: 38, baseType: !1706, size: 32, align: 32, offset: 64)
!1723 = !DIDerivedType(tag: DW_TAG_member, name: "line", scope: !1719, file: !1707, line: 39, baseType: !215, size: 64, align: 64, offset: 128)
!1724 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !1719, file: !1707, line: 40, baseType: !158, size: 64, align: 64, offset: 192)
!1725 = !DIDerivedType(tag: DW_TAG_member, name: "postsize", scope: !1715, file: !1548, line: 129, baseType: !189, size: 64, align: 64, offset: 64)
!1726 = !DIDerivedType(tag: DW_TAG_member, name: "postdata", scope: !1715, file: !1548, line: 130, baseType: !928, size: 64, align: 64, offset: 128)
!1727 = !DIDerivedType(tag: DW_TAG_member, name: "p_pragma", scope: !1715, file: !1548, line: 132, baseType: !928, size: 64, align: 64, offset: 192)
!1728 = !DIDerivedType(tag: DW_TAG_member, name: "p_accept", scope: !1715, file: !1548, line: 133, baseType: !928, size: 64, align: 64, offset: 256)
!1729 = !DIDerivedType(tag: DW_TAG_member, name: "readbytecount", scope: !1715, file: !1548, line: 134, baseType: !189, size: 64, align: 64, offset: 320)
!1730 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecount", scope: !1715, file: !1548, line: 135, baseType: !189, size: 64, align: 64, offset: 384)
!1731 = !DIDerivedType(tag: DW_TAG_member, name: "form", scope: !1715, file: !1548, line: 138, baseType: !1732, size: 256, align: 64, offset: 448)
!1732 = !DICompositeType(tag: DW_TAG_structure_type, name: "Form", file: !1707, line: 43, size: 256, align: 64, elements: !1733)
!1733 = !{!1734, !1735, !1736, !1737}
!1734 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !1732, file: !1707, line: 44, baseType: !1718, size: 64, align: 64)
!1735 = !DIDerivedType(tag: DW_TAG_member, name: "sent", scope: !1732, file: !1707, line: 45, baseType: !158, size: 64, align: 64, offset: 64)
!1736 = !DIDerivedType(tag: DW_TAG_member, name: "fp", scope: !1732, file: !1707, line: 47, baseType: !652, size: 64, align: 64, offset: 128)
!1737 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func", scope: !1732, file: !1707, line: 48, baseType: !737, size: 64, align: 64, offset: 192)
!1738 = !DIDerivedType(tag: DW_TAG_member, name: "backup", scope: !1715, file: !1548, line: 145, baseType: !1739, size: 256, align: 64, offset: 704)
!1739 = !DICompositeType(tag: DW_TAG_structure_type, name: "back", file: !1548, line: 140, size: 256, align: 64, elements: !1740)
!1740 = !{!1741, !1742, !1743, !1744}
!1741 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func", scope: !1739, file: !1548, line: 141, baseType: !737, size: 64, align: 64)
!1742 = !DIDerivedType(tag: DW_TAG_member, name: "fread_in", scope: !1739, file: !1548, line: 142, baseType: !148, size: 64, align: 64, offset: 64)
!1743 = !DIDerivedType(tag: DW_TAG_member, name: "postdata", scope: !1739, file: !1548, line: 143, baseType: !928, size: 64, align: 64, offset: 128)
!1744 = !DIDerivedType(tag: DW_TAG_member, name: "postsize", scope: !1739, file: !1548, line: 144, baseType: !189, size: 64, align: 64, offset: 192)
!1745 = !DIDerivedType(tag: DW_TAG_member, name: "sending", scope: !1715, file: !1548, line: 152, baseType: !1714, size: 32, align: 32, offset: 960)
!1746 = !DIDerivedType(tag: DW_TAG_member, name: "send_buffer", scope: !1715, file: !1548, line: 154, baseType: !148, size: 64, align: 64, offset: 1024)
!1747 = !{!1748, !1749, !1750, !1751}
!1748 = !DIEnumerator(name: "HTTPSEND_NADA", value: 0)
!1749 = !DIEnumerator(name: "HTTPSEND_REQUEST", value: 1)
!1750 = !DIEnumerator(name: "HTTPSEND_BODY", value: 2)
!1751 = !DIEnumerator(name: "HTTPSEND_LAST", value: 3)
!1752 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !400, line: 68, size: 32, align: 32, elements: !1753)
!1753 = !{!1754, !1755, !1756, !1757, !1758, !1759, !1760, !1761, !1762}
!1754 = !DIEnumerator(name: "CHUNKE_STOP", value: -1)
!1755 = !DIEnumerator(name: "CHUNKE_OK", value: 0)
!1756 = !DIEnumerator(name: "CHUNKE_TOO_LONG_HEX", value: 1)
!1757 = !DIEnumerator(name: "CHUNKE_ILLEGAL_HEX", value: 2)
!1758 = !DIEnumerator(name: "CHUNKE_BAD_CHUNK", value: 3)
!1759 = !DIEnumerator(name: "CHUNKE_WRITE_ERROR", value: 4)
!1760 = !DIEnumerator(name: "CHUNKE_BAD_ENCODING", value: 5)
!1761 = !DIEnumerator(name: "CHUNKE_OUT_OF_MEMORY", value: 6)
!1762 = !DIEnumerator(name: "CHUNKE_LAST", value: 7)
!1763 = !{!158, !177, !737, !189, !256, !1764}
!1764 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1648, size: 64, align: 64)
!1765 = !{!1766, !1770, !1771, !1774, !1777, !1778, !1781, !1784, !1785, !1789, !1792, !1795, !1799, !1802, !1805, !1808, !1811, !1814, !1817, !1820}
!1766 = distinct !DISubprogram(name: "Curl_fillreadbuffer", scope: !1, file: !1, line: 86, type: !1767, isLocal: false, isDefinition: true, scopeLine: 87, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1767 = !DISubroutineType(types: !1768)
!1768 = !{!554, !550, !177, !1434}
!1769 = !{}
!1770 = distinct !DISubprogram(name: "Curl_readrewind", scope: !1, file: !1, line: 241, type: !1417, isLocal: false, isDefinition: true, scopeLine: 242, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1771 = distinct !DISubprogram(name: "Curl_meets_timecondition", scope: !1, file: !1, line: 353, type: !1772, isLocal: false, isDefinition: true, scopeLine: 354, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1772 = !DISubroutineType(types: !1773)
!1773 = !{!211, !544, !242}
!1774 = distinct !DISubprogram(name: "Curl_readwrite", scope: !1, file: !1, line: 1054, type: !1775, isLocal: false, isDefinition: true, scopeLine: 1058, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1775 = !DISubroutineType(types: !1776)
!1776 = !{!554, !550, !544, !1423, !1423}
!1777 = distinct !DISubprogram(name: "Curl_single_getsock", scope: !1, file: !1, line: 1228, type: !1447, isLocal: false, isDefinition: true, scopeLine: 1232, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1778 = distinct !DISubprogram(name: "Curl_init_CONNECT", scope: !1, file: !1, line: 1276, type: !1779, isLocal: false, isDefinition: true, scopeLine: 1277, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1779 = !DISubroutineType(types: !1780)
!1780 = !{null, !544}
!1781 = distinct !DISubprogram(name: "Curl_pretransfer", scope: !1, file: !1, line: 1287, type: !1782, isLocal: false, isDefinition: true, scopeLine: 1288, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1782 = !DISubroutineType(types: !1783)
!1783 = !{!554, !544}
!1784 = distinct !DISubprogram(name: "Curl_posttransfer", scope: !1, file: !1, line: 1373, type: !1782, isLocal: false, isDefinition: true, scopeLine: 1374, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1785 = distinct !DISubprogram(name: "Curl_follow", scope: !1, file: !1, line: 1630, type: !1786, isLocal: false, isDefinition: true, scopeLine: 1635, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1786 = !DISubroutineType(types: !1787)
!1787 = !{!554, !544, !215, !1788}
!1788 = !DIDerivedType(tag: DW_TAG_typedef, name: "followtype", file: !1684, line: 39, baseType: !1683)
!1789 = distinct !DISubprogram(name: "Curl_retry_request", scope: !1, file: !1, line: 1831, type: !1790, isLocal: false, isDefinition: true, scopeLine: 1833, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1790 = !DISubroutineType(types: !1791)
!1791 = !{!554, !550, !1524}
!1792 = distinct !DISubprogram(name: "Curl_setup_transfer", scope: !1, file: !1, line: 1883, type: !1793, isLocal: false, isDefinition: true, scopeLine: 1893, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1793 = !DISubroutineType(types: !1794)
!1794 = !{null, !550, !177, !189, !211, !193, !177, !193}
!1795 = distinct !DISubprogram(name: "readwrite_data", scope: !1, file: !1, line: 389, type: !1796, isLocal: true, isDefinition: true, scopeLine: 394, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1796 = !DISubroutineType(types: !1797)
!1797 = !{!554, !544, !550, !1798, !1434, !1423, !1423}
!1798 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !186, size: 64, align: 64)
!1799 = distinct !DISubprogram(name: "read_rewind", scope: !1, file: !1, line: 320, type: !1800, isLocal: true, isDefinition: true, scopeLine: 322, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1800 = !DISubroutineType(types: !1801)
!1801 = !{null, !550, !158}
!1802 = distinct !DISubprogram(name: "data_pending", scope: !1, file: !1, line: 300, type: !1803, isLocal: true, isDefinition: true, scopeLine: 301, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1803 = !DISubroutineType(types: !1804)
!1804 = !{!177, !1449}
!1805 = distinct !DISubprogram(name: "readwrite_upload", scope: !1, file: !1, line: 854, type: !1806, isLocal: true, isDefinition: true, scopeLine: 858, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1806 = !DISubroutineType(types: !1807)
!1807 = !{!554, !544, !550, !1798, !1434}
!1808 = distinct !DISubprogram(name: "done_sending", scope: !1, file: !1, line: 835, type: !1809, isLocal: true, isDefinition: true, scopeLine: 837, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1809 = !DISubroutineType(types: !1810)
!1810 = !{!554, !550, !1798}
!1811 = distinct !DISubprogram(name: "is_absolute_url", scope: !1, file: !1, line: 1460, type: !1812, isLocal: true, isDefinition: true, scopeLine: 1461, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1812 = !DISubroutineType(types: !1813)
!1813 = !{!211, !928}
!1814 = distinct !DISubprogram(name: "concat_url", scope: !1, file: !1, line: 1474, type: !1815, isLocal: true, isDefinition: true, scopeLine: 1475, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1815 = !DISubroutineType(types: !1816)
!1816 = !{!215, !928, !928}
!1817 = distinct !DISubprogram(name: "strlen_url", scope: !1, file: !1, line: 1391, type: !1818, isLocal: true, isDefinition: true, scopeLine: 1392, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1818 = !DISubroutineType(types: !1819)
!1819 = !{!158, !928}
!1820 = distinct !DISubprogram(name: "strcpy_url", scope: !1, file: !1, line: 1421, type: !1821, isLocal: true, isDefinition: true, scopeLine: 1422, flags: DIFlagPrototyped, isOptimized: false, variables: !1769)
!1821 = !DISubroutineType(types: !1822)
!1822 = !{null, !215, !928}
!1823 = !{i32 2, !"Dwarf Version", i32 4}
!1824 = !{i32 2, !"Debug Info Version", i32 3}
!1825 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!1826 = !DILocalVariable(name: "conn", arg: 1, scope: !1766, file: !1, line: 86, type: !550)
!1827 = !DIExpression()
!1828 = !DILocation(line: 86, column: 50, scope: !1766)
!1829 = !DILocalVariable(name: "bytes", arg: 2, scope: !1766, file: !1, line: 86, type: !177)
!1830 = !DILocation(line: 86, column: 60, scope: !1766)
!1831 = !DILocalVariable(name: "nreadp", arg: 3, scope: !1766, file: !1, line: 86, type: !1434)
!1832 = !DILocation(line: 86, column: 72, scope: !1766)
!1833 = !DILocalVariable(name: "data", scope: !1766, file: !1, line: 88, type: !544)
!1834 = !DILocation(line: 88, column: 21, scope: !1766)
!1835 = !DILocation(line: 88, column: 28, scope: !1766)
!1836 = !DILocation(line: 88, column: 34, scope: !1766)
!1837 = !DILocalVariable(name: "buffersize", scope: !1766, file: !1, line: 89, type: !158)
!1838 = !DILocation(line: 89, column: 10, scope: !1766)
!1839 = !DILocation(line: 89, column: 31, scope: !1766)
!1840 = !DILocation(line: 89, column: 23, scope: !1766)
!1841 = !DILocalVariable(name: "nread", scope: !1766, file: !1, line: 90, type: !177)
!1842 = !DILocation(line: 90, column: 7, scope: !1766)
!1843 = !DILocation(line: 104, column: 6, scope: !1844)
!1844 = distinct !DILexicalBlock(scope: !1766, file: !1, line: 104, column: 6)
!1845 = !DILocation(line: 104, column: 12, scope: !1844)
!1846 = !DILocation(line: 104, column: 16, scope: !1844)
!1847 = !DILocation(line: 104, column: 6, scope: !1766)
!1848 = !DILocation(line: 106, column: 16, scope: !1849)
!1849 = distinct !DILexicalBlock(scope: !1844, file: !1, line: 104, column: 31)
!1850 = !DILocation(line: 107, column: 5, scope: !1849)
!1851 = !DILocation(line: 107, column: 11, scope: !1849)
!1852 = !DILocation(line: 107, column: 15, scope: !1849)
!1853 = !DILocation(line: 107, column: 31, scope: !1849)
!1854 = !DILocation(line: 108, column: 3, scope: !1849)
!1855 = !DILocation(line: 112, column: 16, scope: !1766)
!1856 = !DILocation(line: 112, column: 22, scope: !1766)
!1857 = !DILocation(line: 112, column: 28, scope: !1766)
!1858 = !DILocation(line: 112, column: 39, scope: !1766)
!1859 = !DILocation(line: 112, column: 45, scope: !1766)
!1860 = !DILocation(line: 112, column: 49, scope: !1766)
!1861 = !DILocation(line: 113, column: 39, scope: !1766)
!1862 = !DILocation(line: 113, column: 51, scope: !1766)
!1863 = !DILocation(line: 113, column: 57, scope: !1766)
!1864 = !DILocation(line: 113, column: 63, scope: !1766)
!1865 = !DILocation(line: 112, column: 11, scope: !1766)
!1866 = !DILocation(line: 112, column: 9, scope: !1766)
!1867 = !DILocation(line: 115, column: 6, scope: !1868)
!1868 = distinct !DILexicalBlock(scope: !1766, file: !1, line: 115, column: 6)
!1869 = !DILocation(line: 115, column: 12, scope: !1868)
!1870 = !DILocation(line: 115, column: 6, scope: !1766)
!1871 = !DILocation(line: 116, column: 11, scope: !1872)
!1872 = distinct !DILexicalBlock(scope: !1868, file: !1, line: 115, column: 36)
!1873 = !DILocation(line: 116, column: 5, scope: !1872)
!1874 = !DILocation(line: 117, column: 6, scope: !1872)
!1875 = !DILocation(line: 117, column: 13, scope: !1872)
!1876 = !DILocation(line: 118, column: 5, scope: !1872)
!1877 = !DILocation(line: 120, column: 6, scope: !1878)
!1878 = distinct !DILexicalBlock(scope: !1766, file: !1, line: 120, column: 6)
!1879 = !DILocation(line: 120, column: 12, scope: !1878)
!1880 = !DILocation(line: 120, column: 6, scope: !1766)
!1881 = !DILocalVariable(name: "k", scope: !1882, file: !1, line: 121, type: !1798)
!1882 = distinct !DILexicalBlock(scope: !1878, file: !1, line: 120, column: 36)
!1883 = !DILocation(line: 121, column: 27, scope: !1882)
!1884 = !DILocation(line: 121, column: 32, scope: !1882)
!1885 = !DILocation(line: 121, column: 38, scope: !1882)
!1886 = !DILocation(line: 123, column: 8, scope: !1887)
!1887 = distinct !DILexicalBlock(scope: !1882, file: !1, line: 123, column: 8)
!1888 = !DILocation(line: 123, column: 14, scope: !1887)
!1889 = !DILocation(line: 123, column: 23, scope: !1887)
!1890 = !DILocation(line: 123, column: 29, scope: !1887)
!1891 = !DILocation(line: 123, column: 8, scope: !1882)
!1892 = !DILocation(line: 127, column: 13, scope: !1893)
!1893 = distinct !DILexicalBlock(scope: !1887, file: !1, line: 123, column: 50)
!1894 = !DILocation(line: 127, column: 7, scope: !1893)
!1895 = !DILocation(line: 128, column: 7, scope: !1893)
!1896 = !DILocation(line: 132, column: 5, scope: !1882)
!1897 = !DILocation(line: 132, column: 8, scope: !1882)
!1898 = !DILocation(line: 132, column: 15, scope: !1882)
!1899 = !DILocation(line: 133, column: 8, scope: !1900)
!1900 = distinct !DILexicalBlock(scope: !1882, file: !1, line: 133, column: 8)
!1901 = !DILocation(line: 133, column: 14, scope: !1900)
!1902 = !DILocation(line: 133, column: 18, scope: !1900)
!1903 = !DILocation(line: 133, column: 8, scope: !1882)
!1904 = !DILocation(line: 135, column: 7, scope: !1905)
!1905 = distinct !DILexicalBlock(scope: !1900, file: !1, line: 133, column: 33)
!1906 = !DILocation(line: 135, column: 13, scope: !1905)
!1907 = !DILocation(line: 135, column: 17, scope: !1905)
!1908 = !DILocation(line: 135, column: 33, scope: !1905)
!1909 = !DILocation(line: 136, column: 5, scope: !1905)
!1910 = !DILocation(line: 137, column: 6, scope: !1882)
!1911 = !DILocation(line: 137, column: 13, scope: !1882)
!1912 = !DILocation(line: 139, column: 5, scope: !1882)
!1913 = !DILocation(line: 141, column: 19, scope: !1914)
!1914 = distinct !DILexicalBlock(scope: !1878, file: !1, line: 141, column: 11)
!1915 = !DILocation(line: 141, column: 11, scope: !1914)
!1916 = !DILocation(line: 141, column: 27, scope: !1914)
!1917 = !DILocation(line: 141, column: 25, scope: !1914)
!1918 = !DILocation(line: 141, column: 11, scope: !1878)
!1919 = !DILocation(line: 143, column: 6, scope: !1920)
!1920 = distinct !DILexicalBlock(scope: !1914, file: !1, line: 141, column: 39)
!1921 = !DILocation(line: 143, column: 13, scope: !1920)
!1922 = !DILocation(line: 144, column: 11, scope: !1920)
!1923 = !DILocation(line: 144, column: 5, scope: !1920)
!1924 = !DILocation(line: 145, column: 5, scope: !1920)
!1925 = !DILocation(line: 148, column: 7, scope: !1926)
!1926 = distinct !DILexicalBlock(scope: !1766, file: !1, line: 148, column: 6)
!1927 = !DILocation(line: 148, column: 13, scope: !1926)
!1928 = !DILocation(line: 148, column: 17, scope: !1926)
!1929 = !DILocation(line: 148, column: 29, scope: !1926)
!1930 = !DILocation(line: 148, column: 32, scope: !1931)
!1931 = !DILexicalBlockFile(scope: !1926, file: !1, discriminator: 1)
!1932 = !DILocation(line: 148, column: 38, scope: !1931)
!1933 = !DILocation(line: 148, column: 42, scope: !1931)
!1934 = !DILocation(line: 148, column: 6, scope: !1931)
!1935 = !DILocalVariable(name: "hexbuffer", scope: !1936, file: !1, line: 164, type: !1937)
!1936 = distinct !DILexicalBlock(scope: !1926, file: !1, line: 148, column: 57)
!1937 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 88, align: 8, elements: !1938)
!1938 = !{!1939}
!1939 = !DISubrange(count: 11)
!1940 = !DILocation(line: 164, column: 10, scope: !1936)
!1941 = !DILocalVariable(name: "endofline_native", scope: !1936, file: !1, line: 165, type: !928)
!1942 = !DILocation(line: 165, column: 17, scope: !1936)
!1943 = !DILocalVariable(name: "endofline_network", scope: !1936, file: !1, line: 166, type: !928)
!1944 = !DILocation(line: 166, column: 17, scope: !1936)
!1945 = !DILocalVariable(name: "hexlen", scope: !1936, file: !1, line: 167, type: !177)
!1946 = !DILocation(line: 167, column: 9, scope: !1936)
!1947 = !DILocation(line: 171, column: 9, scope: !1948)
!1948 = distinct !DILexicalBlock(scope: !1936, file: !1, line: 171, column: 8)
!1949 = !DILocation(line: 171, column: 15, scope: !1948)
!1950 = !DILocation(line: 171, column: 19, scope: !1948)
!1951 = !DILocation(line: 171, column: 33, scope: !1948)
!1952 = !DILocation(line: 173, column: 9, scope: !1948)
!1953 = !DILocation(line: 173, column: 15, scope: !1948)
!1954 = !DILocation(line: 173, column: 19, scope: !1948)
!1955 = !DILocation(line: 171, column: 8, scope: !1956)
!1956 = !DILexicalBlockFile(scope: !1936, file: !1, discriminator: 1)
!1957 = !DILocation(line: 175, column: 25, scope: !1958)
!1958 = distinct !DILexicalBlock(scope: !1948, file: !1, line: 173, column: 26)
!1959 = !DILocation(line: 176, column: 25, scope: !1958)
!1960 = !DILocation(line: 177, column: 5, scope: !1958)
!1961 = !DILocation(line: 179, column: 25, scope: !1962)
!1962 = distinct !DILexicalBlock(scope: !1948, file: !1, line: 178, column: 10)
!1963 = !DILocation(line: 180, column: 25, scope: !1962)
!1964 = !DILocation(line: 182, column: 23, scope: !1936)
!1965 = !DILocation(line: 183, column: 31, scope: !1936)
!1966 = !DILocation(line: 183, column: 38, scope: !1936)
!1967 = !DILocation(line: 182, column: 14, scope: !1936)
!1968 = !DILocation(line: 182, column: 12, scope: !1936)
!1969 = !DILocation(line: 186, column: 34, scope: !1936)
!1970 = !DILocation(line: 186, column: 5, scope: !1936)
!1971 = !DILocation(line: 186, column: 11, scope: !1936)
!1972 = !DILocation(line: 186, column: 15, scope: !1936)
!1973 = !DILocation(line: 186, column: 31, scope: !1936)
!1974 = !DILocation(line: 187, column: 14, scope: !1936)
!1975 = !DILocation(line: 187, column: 11, scope: !1936)
!1976 = !DILocation(line: 190, column: 12, scope: !1936)
!1977 = !DILocation(line: 190, column: 18, scope: !1936)
!1978 = !DILocation(line: 190, column: 22, scope: !1936)
!1979 = !DILocation(line: 190, column: 5, scope: !1936)
!1980 = !DILocation(line: 190, column: 50, scope: !1936)
!1981 = !DILocation(line: 193, column: 12, scope: !1936)
!1982 = !DILocation(line: 193, column: 18, scope: !1936)
!1983 = !DILocation(line: 193, column: 22, scope: !1936)
!1984 = !DILocation(line: 193, column: 40, scope: !1936)
!1985 = !DILocation(line: 193, column: 38, scope: !1936)
!1986 = !DILocation(line: 194, column: 12, scope: !1936)
!1987 = !DILocation(line: 195, column: 19, scope: !1936)
!1988 = !DILocation(line: 195, column: 12, scope: !1936)
!1989 = !DILocation(line: 193, column: 5, scope: !1936)
!1990 = !DILocation(line: 214, column: 9, scope: !1991)
!1991 = distinct !DILexicalBlock(scope: !1936, file: !1, line: 214, column: 8)
!1992 = !DILocation(line: 214, column: 17, scope: !1991)
!1993 = !DILocation(line: 214, column: 15, scope: !1991)
!1994 = !DILocation(line: 214, column: 25, scope: !1991)
!1995 = !DILocation(line: 214, column: 8, scope: !1936)
!1996 = !DILocation(line: 216, column: 7, scope: !1991)
!1997 = !DILocation(line: 216, column: 13, scope: !1991)
!1998 = !DILocation(line: 216, column: 17, scope: !1991)
!1999 = !DILocation(line: 216, column: 29, scope: !1991)
!2000 = !DILocation(line: 218, column: 24, scope: !1936)
!2001 = !DILocation(line: 218, column: 17, scope: !1936)
!2002 = !DILocation(line: 218, column: 12, scope: !1936)
!2003 = !DILocation(line: 218, column: 10, scope: !1936)
!2004 = !DILocation(line: 219, column: 3, scope: !1936)
!2005 = !DILocation(line: 230, column: 13, scope: !1766)
!2006 = !DILocation(line: 230, column: 4, scope: !1766)
!2007 = !DILocation(line: 230, column: 11, scope: !1766)
!2008 = !DILocation(line: 232, column: 3, scope: !1766)
!2009 = !DILocation(line: 233, column: 1, scope: !1766)
!2010 = !DILocalVariable(name: "conn", arg: 1, scope: !1770, file: !1, line: 241, type: !550)
!2011 = !DILocation(line: 241, column: 46, scope: !1770)
!2012 = !DILocalVariable(name: "data", scope: !1770, file: !1, line: 243, type: !544)
!2013 = !DILocation(line: 243, column: 21, scope: !1770)
!2014 = !DILocation(line: 243, column: 28, scope: !1770)
!2015 = !DILocation(line: 243, column: 34, scope: !1770)
!2016 = !DILocation(line: 245, column: 3, scope: !1770)
!2017 = !DILocation(line: 245, column: 9, scope: !1770)
!2018 = !DILocation(line: 245, column: 14, scope: !1770)
!2019 = !DILocation(line: 245, column: 30, scope: !1770)
!2020 = !DILocation(line: 251, column: 3, scope: !1770)
!2021 = !DILocation(line: 251, column: 9, scope: !1770)
!2022 = !DILocation(line: 251, column: 13, scope: !1770)
!2023 = !DILocation(line: 251, column: 20, scope: !1770)
!2024 = !DILocation(line: 256, column: 6, scope: !2025)
!2025 = distinct !DILexicalBlock(scope: !1770, file: !1, line: 256, column: 6)
!2026 = !DILocation(line: 256, column: 12, scope: !2025)
!2027 = !DILocation(line: 256, column: 16, scope: !2025)
!2028 = !DILocation(line: 256, column: 27, scope: !2025)
!2029 = !DILocation(line: 257, column: 7, scope: !2025)
!2030 = !DILocation(line: 257, column: 13, scope: !2025)
!2031 = !DILocation(line: 257, column: 17, scope: !2025)
!2032 = !DILocation(line: 257, column: 25, scope: !2025)
!2033 = !DILocation(line: 256, column: 6, scope: !2034)
!2034 = !DILexicalBlockFile(scope: !1770, file: !1, discriminator: 1)
!2035 = !DILocation(line: 256, column: 6, scope: !2036)
!2036 = !DILexicalBlockFile(scope: !1770, file: !1, discriminator: 2)
!2037 = !DILocation(line: 260, column: 8, scope: !2038)
!2038 = distinct !DILexicalBlock(scope: !2039, file: !1, line: 260, column: 8)
!2039 = distinct !DILexicalBlock(scope: !2025, file: !1, line: 259, column: 8)
!2040 = !DILocation(line: 260, column: 14, scope: !2038)
!2041 = !DILocation(line: 260, column: 18, scope: !2038)
!2042 = !DILocation(line: 260, column: 8, scope: !2039)
!2043 = !DILocalVariable(name: "err", scope: !2044, file: !1, line: 261, type: !177)
!2044 = distinct !DILexicalBlock(scope: !2038, file: !1, line: 260, column: 29)
!2045 = !DILocation(line: 261, column: 11, scope: !2044)
!2046 = !DILocation(line: 263, column: 14, scope: !2044)
!2047 = !DILocation(line: 263, column: 20, scope: !2044)
!2048 = !DILocation(line: 263, column: 24, scope: !2044)
!2049 = !DILocation(line: 263, column: 35, scope: !2044)
!2050 = !DILocation(line: 263, column: 41, scope: !2044)
!2051 = !DILocation(line: 263, column: 45, scope: !2044)
!2052 = !DILocation(line: 263, column: 13, scope: !2044)
!2053 = !DILocation(line: 263, column: 11, scope: !2044)
!2054 = !DILocation(line: 264, column: 10, scope: !2055)
!2055 = distinct !DILexicalBlock(scope: !2044, file: !1, line: 264, column: 10)
!2056 = !DILocation(line: 264, column: 10, scope: !2044)
!2057 = !DILocation(line: 265, column: 15, scope: !2058)
!2058 = distinct !DILexicalBlock(scope: !2055, file: !1, line: 264, column: 15)
!2059 = !DILocation(line: 265, column: 61, scope: !2058)
!2060 = !DILocation(line: 265, column: 9, scope: !2058)
!2061 = !DILocation(line: 266, column: 9, scope: !2058)
!2062 = !DILocation(line: 268, column: 5, scope: !2044)
!2063 = !DILocation(line: 269, column: 13, scope: !2064)
!2064 = distinct !DILexicalBlock(scope: !2038, file: !1, line: 269, column: 13)
!2065 = !DILocation(line: 269, column: 19, scope: !2064)
!2066 = !DILocation(line: 269, column: 23, scope: !2064)
!2067 = !DILocation(line: 269, column: 13, scope: !2038)
!2068 = !DILocalVariable(name: "err", scope: !2069, file: !1, line: 270, type: !762)
!2069 = distinct !DILexicalBlock(scope: !2064, file: !1, line: 269, column: 35)
!2070 = !DILocation(line: 270, column: 17, scope: !2069)
!2071 = !DILocation(line: 272, column: 14, scope: !2069)
!2072 = !DILocation(line: 272, column: 20, scope: !2069)
!2073 = !DILocation(line: 272, column: 24, scope: !2069)
!2074 = !DILocation(line: 272, column: 36, scope: !2069)
!2075 = !DILocation(line: 273, column: 36, scope: !2069)
!2076 = !DILocation(line: 273, column: 42, scope: !2069)
!2077 = !DILocation(line: 273, column: 46, scope: !2069)
!2078 = !DILocation(line: 272, column: 13, scope: !2069)
!2079 = !DILocation(line: 272, column: 11, scope: !2069)
!2080 = !DILocation(line: 274, column: 13, scope: !2069)
!2081 = !DILocation(line: 274, column: 60, scope: !2069)
!2082 = !DILocation(line: 274, column: 7, scope: !2069)
!2083 = !DILocation(line: 276, column: 10, scope: !2084)
!2084 = distinct !DILexicalBlock(scope: !2069, file: !1, line: 276, column: 10)
!2085 = !DILocation(line: 276, column: 10, scope: !2069)
!2086 = !DILocation(line: 278, column: 15, scope: !2087)
!2087 = distinct !DILexicalBlock(scope: !2084, file: !1, line: 276, column: 15)
!2088 = !DILocation(line: 278, column: 62, scope: !2087)
!2089 = !DILocation(line: 278, column: 9, scope: !2087)
!2090 = !DILocation(line: 279, column: 9, scope: !2087)
!2091 = !DILocation(line: 281, column: 5, scope: !2069)
!2092 = !DILocation(line: 286, column: 10, scope: !2093)
!2093 = distinct !DILexicalBlock(scope: !2094, file: !1, line: 286, column: 10)
!2094 = distinct !DILexicalBlock(scope: !2064, file: !1, line: 282, column: 10)
!2095 = !DILocation(line: 286, column: 16, scope: !2093)
!2096 = !DILocation(line: 286, column: 22, scope: !2093)
!2097 = !DILocation(line: 286, column: 33, scope: !2093)
!2098 = !DILocation(line: 286, column: 10, scope: !2094)
!2099 = !DILocation(line: 287, column: 24, scope: !2100)
!2100 = distinct !DILexicalBlock(scope: !2101, file: !1, line: 287, column: 12)
!2101 = distinct !DILexicalBlock(scope: !2093, file: !1, line: 286, column: 63)
!2102 = !DILocation(line: 287, column: 30, scope: !2100)
!2103 = !DILocation(line: 287, column: 36, scope: !2100)
!2104 = !DILocation(line: 287, column: 18, scope: !2100)
!2105 = !DILocation(line: 287, column: 15, scope: !2100)
!2106 = !DILocation(line: 287, column: 12, scope: !2101)
!2107 = !DILocation(line: 289, column: 11, scope: !2100)
!2108 = !DILocation(line: 290, column: 7, scope: !2101)
!2109 = !DILocation(line: 293, column: 13, scope: !2094)
!2110 = !DILocation(line: 293, column: 7, scope: !2094)
!2111 = !DILocation(line: 294, column: 7, scope: !2094)
!2112 = !DILocation(line: 297, column: 3, scope: !1770)
!2113 = !DILocation(line: 298, column: 1, scope: !1770)
!2114 = !DILocalVariable(name: "data", arg: 1, scope: !1771, file: !1, line: 353, type: !544)
!2115 = !DILocation(line: 353, column: 49, scope: !1771)
!2116 = !DILocalVariable(name: "timeofdoc", arg: 2, scope: !1771, file: !1, line: 353, type: !242)
!2117 = !DILocation(line: 353, column: 62, scope: !1771)
!2118 = !DILocation(line: 355, column: 7, scope: !2119)
!2119 = distinct !DILexicalBlock(scope: !1771, file: !1, line: 355, column: 6)
!2120 = !DILocation(line: 355, column: 17, scope: !2119)
!2121 = !DILocation(line: 355, column: 23, scope: !2119)
!2122 = !DILocation(line: 355, column: 27, scope: !2123)
!2123 = !DILexicalBlockFile(scope: !2119, file: !1, discriminator: 1)
!2124 = !DILocation(line: 355, column: 33, scope: !2123)
!2125 = !DILocation(line: 355, column: 37, scope: !2123)
!2126 = !DILocation(line: 355, column: 47, scope: !2123)
!2127 = !DILocation(line: 355, column: 6, scope: !2123)
!2128 = !DILocation(line: 356, column: 5, scope: !2119)
!2129 = !DILocation(line: 358, column: 10, scope: !1771)
!2130 = !DILocation(line: 358, column: 16, scope: !1771)
!2131 = !DILocation(line: 358, column: 20, scope: !1771)
!2132 = !DILocation(line: 358, column: 3, scope: !1771)
!2133 = !DILocation(line: 358, column: 35, scope: !2134)
!2134 = !DILexicalBlockFile(scope: !1771, file: !1, discriminator: 1)
!2135 = !DILocation(line: 361, column: 8, scope: !2136)
!2136 = distinct !DILexicalBlock(scope: !2137, file: !1, line: 361, column: 8)
!2137 = distinct !DILexicalBlock(scope: !1771, file: !1, line: 358, column: 35)
!2138 = !DILocation(line: 361, column: 21, scope: !2136)
!2139 = !DILocation(line: 361, column: 27, scope: !2136)
!2140 = !DILocation(line: 361, column: 31, scope: !2136)
!2141 = !DILocation(line: 361, column: 18, scope: !2136)
!2142 = !DILocation(line: 361, column: 8, scope: !2137)
!2143 = !DILocation(line: 362, column: 13, scope: !2144)
!2144 = distinct !DILexicalBlock(scope: !2136, file: !1, line: 361, column: 42)
!2145 = !DILocation(line: 362, column: 7, scope: !2144)
!2146 = !DILocation(line: 364, column: 7, scope: !2144)
!2147 = !DILocation(line: 364, column: 13, scope: !2144)
!2148 = !DILocation(line: 364, column: 18, scope: !2144)
!2149 = !DILocation(line: 364, column: 27, scope: !2144)
!2150 = !DILocation(line: 365, column: 7, scope: !2144)
!2151 = !DILocation(line: 367, column: 5, scope: !2137)
!2152 = !DILocation(line: 369, column: 8, scope: !2153)
!2153 = distinct !DILexicalBlock(scope: !2137, file: !1, line: 369, column: 8)
!2154 = !DILocation(line: 369, column: 21, scope: !2153)
!2155 = !DILocation(line: 369, column: 27, scope: !2153)
!2156 = !DILocation(line: 369, column: 31, scope: !2153)
!2157 = !DILocation(line: 369, column: 18, scope: !2153)
!2158 = !DILocation(line: 369, column: 8, scope: !2137)
!2159 = !DILocation(line: 370, column: 13, scope: !2160)
!2160 = distinct !DILexicalBlock(scope: !2153, file: !1, line: 369, column: 42)
!2161 = !DILocation(line: 370, column: 7, scope: !2160)
!2162 = !DILocation(line: 372, column: 7, scope: !2160)
!2163 = !DILocation(line: 372, column: 13, scope: !2160)
!2164 = !DILocation(line: 372, column: 18, scope: !2160)
!2165 = !DILocation(line: 372, column: 27, scope: !2160)
!2166 = !DILocation(line: 373, column: 7, scope: !2160)
!2167 = !DILocation(line: 375, column: 5, scope: !2137)
!2168 = !DILocation(line: 378, column: 3, scope: !1771)
!2169 = !DILocation(line: 379, column: 1, scope: !1771)
!2170 = !DILocalVariable(name: "conn", arg: 1, scope: !1774, file: !1, line: 1054, type: !550)
!2171 = !DILocation(line: 1054, column: 45, scope: !1774)
!2172 = !DILocalVariable(name: "data", arg: 2, scope: !1774, file: !1, line: 1055, type: !544)
!2173 = !DILocation(line: 1055, column: 43, scope: !1774)
!2174 = !DILocalVariable(name: "done", arg: 3, scope: !1774, file: !1, line: 1056, type: !1423)
!2175 = !DILocation(line: 1056, column: 31, scope: !1774)
!2176 = !DILocalVariable(name: "comeback", arg: 4, scope: !1774, file: !1, line: 1057, type: !1423)
!2177 = !DILocation(line: 1057, column: 31, scope: !1774)
!2178 = !DILocalVariable(name: "k", scope: !1774, file: !1, line: 1059, type: !1798)
!2179 = !DILocation(line: 1059, column: 25, scope: !1774)
!2180 = !DILocation(line: 1059, column: 30, scope: !1774)
!2181 = !DILocation(line: 1059, column: 36, scope: !1774)
!2182 = !DILocalVariable(name: "result", scope: !1774, file: !1, line: 1060, type: !554)
!2183 = !DILocation(line: 1060, column: 12, scope: !1774)
!2184 = !DILocalVariable(name: "didwhat", scope: !1774, file: !1, line: 1061, type: !177)
!2185 = !DILocation(line: 1061, column: 7, scope: !1774)
!2186 = !DILocalVariable(name: "fd_read", scope: !1774, file: !1, line: 1063, type: !248)
!2187 = !DILocation(line: 1063, column: 17, scope: !1774)
!2188 = !DILocalVariable(name: "fd_write", scope: !1774, file: !1, line: 1064, type: !248)
!2189 = !DILocation(line: 1064, column: 17, scope: !1774)
!2190 = !DILocalVariable(name: "select_res", scope: !1774, file: !1, line: 1065, type: !177)
!2191 = !DILocation(line: 1065, column: 7, scope: !1774)
!2192 = !DILocation(line: 1065, column: 20, scope: !1774)
!2193 = !DILocation(line: 1065, column: 26, scope: !1774)
!2194 = !DILocation(line: 1067, column: 3, scope: !1774)
!2195 = !DILocation(line: 1067, column: 9, scope: !1774)
!2196 = !DILocation(line: 1067, column: 22, scope: !1774)
!2197 = !DILocation(line: 1072, column: 7, scope: !2198)
!2198 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1072, column: 6)
!2199 = !DILocation(line: 1072, column: 10, scope: !2198)
!2200 = !DILocation(line: 1072, column: 17, scope: !2198)
!2201 = !DILocation(line: 1072, column: 34, scope: !2198)
!2202 = !DILocation(line: 1072, column: 6, scope: !1774)
!2203 = !DILocation(line: 1073, column: 15, scope: !2198)
!2204 = !DILocation(line: 1073, column: 21, scope: !2198)
!2205 = !DILocation(line: 1073, column: 13, scope: !2198)
!2206 = !DILocation(line: 1073, column: 5, scope: !2198)
!2207 = !DILocation(line: 1075, column: 13, scope: !2198)
!2208 = !DILocation(line: 1077, column: 7, scope: !2209)
!2209 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1077, column: 6)
!2210 = !DILocation(line: 1077, column: 10, scope: !2209)
!2211 = !DILocation(line: 1077, column: 17, scope: !2209)
!2212 = !DILocation(line: 1077, column: 34, scope: !2209)
!2213 = !DILocation(line: 1077, column: 6, scope: !1774)
!2214 = !DILocation(line: 1078, column: 16, scope: !2209)
!2215 = !DILocation(line: 1078, column: 22, scope: !2209)
!2216 = !DILocation(line: 1078, column: 14, scope: !2209)
!2217 = !DILocation(line: 1078, column: 5, scope: !2209)
!2218 = !DILocation(line: 1080, column: 14, scope: !2209)
!2219 = !DILocation(line: 1082, column: 6, scope: !2220)
!2220 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1082, column: 6)
!2221 = !DILocation(line: 1082, column: 12, scope: !2220)
!2222 = !DILocation(line: 1082, column: 18, scope: !2220)
!2223 = !DILocation(line: 1082, column: 24, scope: !2220)
!2224 = !DILocation(line: 1082, column: 6, scope: !1774)
!2225 = !DILocation(line: 1083, column: 16, scope: !2226)
!2226 = distinct !DILexicalBlock(scope: !2220, file: !1, line: 1082, column: 31)
!2227 = !DILocation(line: 1084, column: 5, scope: !2226)
!2228 = !DILocation(line: 1084, column: 5, scope: !2229)
!2229 = !DILexicalBlockFile(scope: !2230, file: !1, discriminator: 1)
!2230 = distinct !DILexicalBlock(scope: !2226, file: !1, line: 1084, column: 5)
!2231 = !DILocation(line: 1085, column: 3, scope: !2226)
!2232 = !DILocation(line: 1087, column: 7, scope: !2233)
!2233 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1087, column: 6)
!2234 = !DILocation(line: 1087, column: 6, scope: !1774)
!2235 = !DILocation(line: 1089, column: 36, scope: !2233)
!2236 = !DILocation(line: 1089, column: 62, scope: !2233)
!2237 = !DILocation(line: 1089, column: 18, scope: !2233)
!2238 = !DILocation(line: 1089, column: 16, scope: !2233)
!2239 = !DILocation(line: 1089, column: 5, scope: !2233)
!2240 = !DILocation(line: 1091, column: 6, scope: !2241)
!2241 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1091, column: 6)
!2242 = !DILocation(line: 1091, column: 17, scope: !2241)
!2243 = !DILocation(line: 1091, column: 6, scope: !1774)
!2244 = !DILocation(line: 1092, column: 11, scope: !2245)
!2245 = distinct !DILexicalBlock(scope: !2241, file: !1, line: 1091, column: 38)
!2246 = !DILocation(line: 1092, column: 5, scope: !2245)
!2247 = !DILocation(line: 1093, column: 5, scope: !2245)
!2248 = !DILocation(line: 1099, column: 7, scope: !2249)
!2249 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1099, column: 6)
!2250 = !DILocation(line: 1099, column: 10, scope: !2249)
!2251 = !DILocation(line: 1099, column: 17, scope: !2249)
!2252 = !DILocation(line: 1099, column: 30, scope: !2249)
!2253 = !DILocation(line: 1100, column: 8, scope: !2249)
!2254 = !DILocation(line: 1100, column: 19, scope: !2249)
!2255 = !DILocation(line: 1100, column: 38, scope: !2249)
!2256 = !DILocation(line: 1100, column: 41, scope: !2257)
!2257 = !DILexicalBlockFile(scope: !2249, file: !1, discriminator: 1)
!2258 = !DILocation(line: 1100, column: 47, scope: !2257)
!2259 = !DILocation(line: 1100, column: 52, scope: !2257)
!2260 = !DILocation(line: 1099, column: 6, scope: !2261)
!2261 = !DILexicalBlockFile(scope: !1774, file: !1, discriminator: 1)
!2262 = !DILocation(line: 1102, column: 29, scope: !2263)
!2263 = distinct !DILexicalBlock(scope: !2249, file: !1, line: 1100, column: 73)
!2264 = !DILocation(line: 1102, column: 35, scope: !2263)
!2265 = !DILocation(line: 1102, column: 41, scope: !2263)
!2266 = !DILocation(line: 1102, column: 54, scope: !2263)
!2267 = !DILocation(line: 1102, column: 60, scope: !2263)
!2268 = !DILocation(line: 1102, column: 14, scope: !2263)
!2269 = !DILocation(line: 1102, column: 12, scope: !2263)
!2270 = !DILocation(line: 1103, column: 8, scope: !2271)
!2271 = distinct !DILexicalBlock(scope: !2263, file: !1, line: 1103, column: 8)
!2272 = !DILocation(line: 1103, column: 15, scope: !2271)
!2273 = !DILocation(line: 1103, column: 19, scope: !2274)
!2274 = !DILexicalBlockFile(scope: !2271, file: !1, discriminator: 1)
!2275 = !DILocation(line: 1103, column: 18, scope: !2274)
!2276 = !DILocation(line: 1103, column: 8, scope: !2274)
!2277 = !DILocation(line: 1104, column: 14, scope: !2271)
!2278 = !DILocation(line: 1104, column: 7, scope: !2271)
!2279 = !DILocation(line: 1105, column: 3, scope: !2263)
!2280 = !DILocation(line: 1108, column: 7, scope: !2281)
!2281 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1108, column: 6)
!2282 = !DILocation(line: 1108, column: 10, scope: !2281)
!2283 = !DILocation(line: 1108, column: 17, scope: !2281)
!2284 = !DILocation(line: 1108, column: 30, scope: !2281)
!2285 = !DILocation(line: 1108, column: 34, scope: !2286)
!2286 = !DILexicalBlockFile(scope: !2281, file: !1, discriminator: 1)
!2287 = !DILocation(line: 1108, column: 45, scope: !2286)
!2288 = !DILocation(line: 1108, column: 6, scope: !2286)
!2289 = !DILocation(line: 1111, column: 31, scope: !2290)
!2290 = distinct !DILexicalBlock(scope: !2281, file: !1, line: 1108, column: 66)
!2291 = !DILocation(line: 1111, column: 37, scope: !2290)
!2292 = !DILocation(line: 1111, column: 43, scope: !2290)
!2293 = !DILocation(line: 1111, column: 14, scope: !2290)
!2294 = !DILocation(line: 1111, column: 12, scope: !2290)
!2295 = !DILocation(line: 1112, column: 8, scope: !2296)
!2296 = distinct !DILexicalBlock(scope: !2290, file: !1, line: 1112, column: 8)
!2297 = !DILocation(line: 1112, column: 8, scope: !2290)
!2298 = !DILocation(line: 1113, column: 14, scope: !2296)
!2299 = !DILocation(line: 1113, column: 7, scope: !2296)
!2300 = !DILocation(line: 1114, column: 3, scope: !2290)
!2301 = !DILocation(line: 1116, column: 3, scope: !1774)
!2302 = !DILocation(line: 1116, column: 6, scope: !1774)
!2303 = !DILocation(line: 1116, column: 12, scope: !1774)
!2304 = !DILocation(line: 1116, column: 12, scope: !2261)
!2305 = !DILocation(line: 1117, column: 6, scope: !2306)
!2306 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1117, column: 6)
!2307 = !DILocation(line: 1117, column: 6, scope: !1774)
!2308 = !DILocation(line: 1119, column: 8, scope: !2309)
!2309 = distinct !DILexicalBlock(scope: !2310, file: !1, line: 1119, column: 8)
!2310 = distinct !DILexicalBlock(scope: !2306, file: !1, line: 1117, column: 15)
!2311 = !DILocation(line: 1119, column: 11, scope: !2309)
!2312 = !DILocation(line: 1119, column: 8, scope: !2310)
!2313 = !DILocation(line: 1120, column: 24, scope: !2309)
!2314 = !DILocation(line: 1120, column: 27, scope: !2309)
!2315 = !DILocation(line: 1120, column: 8, scope: !2309)
!2316 = !DILocation(line: 1120, column: 11, scope: !2309)
!2317 = !DILocation(line: 1120, column: 22, scope: !2309)
!2318 = !DILocation(line: 1120, column: 7, scope: !2309)
!2319 = !DILocation(line: 1121, column: 8, scope: !2320)
!2320 = distinct !DILexicalBlock(scope: !2310, file: !1, line: 1121, column: 8)
!2321 = !DILocation(line: 1121, column: 11, scope: !2320)
!2322 = !DILocation(line: 1121, column: 8, scope: !2310)
!2323 = !DILocation(line: 1122, column: 29, scope: !2320)
!2324 = !DILocation(line: 1122, column: 32, scope: !2320)
!2325 = !DILocation(line: 1122, column: 8, scope: !2320)
!2326 = !DILocation(line: 1122, column: 11, scope: !2320)
!2327 = !DILocation(line: 1122, column: 27, scope: !2320)
!2328 = !DILocation(line: 1122, column: 7, scope: !2320)
!2329 = !DILocation(line: 1123, column: 3, scope: !2310)
!2330 = !DILocation(line: 1126, column: 8, scope: !2331)
!2331 = distinct !DILexicalBlock(scope: !2332, file: !1, line: 1126, column: 8)
!2332 = distinct !DILexicalBlock(scope: !2306, file: !1, line: 1124, column: 8)
!2333 = !DILocation(line: 1126, column: 11, scope: !2331)
!2334 = !DILocation(line: 1126, column: 18, scope: !2331)
!2335 = !DILocation(line: 1126, column: 8, scope: !2332)
!2336 = !DILocalVariable(name: "ms", scope: !2337, file: !1, line: 1140, type: !242)
!2337 = distinct !DILexicalBlock(scope: !2331, file: !1, line: 1126, column: 47)
!2338 = !DILocation(line: 1140, column: 14, scope: !2337)
!2339 = !DILocation(line: 1140, column: 19, scope: !2337)
!2340 = !DILocation(line: 1141, column: 10, scope: !2341)
!2341 = distinct !DILexicalBlock(scope: !2337, file: !1, line: 1141, column: 10)
!2342 = !DILocation(line: 1141, column: 16, scope: !2341)
!2343 = !DILocation(line: 1141, column: 22, scope: !2341)
!2344 = !DILocation(line: 1141, column: 26, scope: !2341)
!2345 = !DILocation(line: 1141, column: 13, scope: !2341)
!2346 = !DILocation(line: 1141, column: 10, scope: !2337)
!2347 = !DILocation(line: 1143, column: 9, scope: !2348)
!2348 = distinct !DILexicalBlock(scope: !2341, file: !1, line: 1141, column: 46)
!2349 = !DILocation(line: 1143, column: 12, scope: !2348)
!2350 = !DILocation(line: 1143, column: 19, scope: !2348)
!2351 = !DILocation(line: 1144, column: 9, scope: !2348)
!2352 = !DILocation(line: 1144, column: 12, scope: !2348)
!2353 = !DILocation(line: 1144, column: 19, scope: !2348)
!2354 = !DILocation(line: 1145, column: 15, scope: !2348)
!2355 = !DILocation(line: 1145, column: 9, scope: !2348)
!2356 = !DILocation(line: 1146, column: 7, scope: !2348)
!2357 = !DILocation(line: 1147, column: 5, scope: !2337)
!2358 = !DILocation(line: 1150, column: 22, scope: !2359)
!2359 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1150, column: 6)
!2360 = !DILocation(line: 1150, column: 6, scope: !2359)
!2361 = !DILocation(line: 1150, column: 6, scope: !1774)
!2362 = !DILocation(line: 1151, column: 12, scope: !2359)
!2363 = !DILocation(line: 1151, column: 5, scope: !2359)
!2364 = !DILocation(line: 1153, column: 30, scope: !2359)
!2365 = !DILocation(line: 1153, column: 36, scope: !2359)
!2366 = !DILocation(line: 1153, column: 39, scope: !2359)
!2367 = !DILocation(line: 1153, column: 14, scope: !2359)
!2368 = !DILocation(line: 1153, column: 12, scope: !2359)
!2369 = !DILocation(line: 1154, column: 6, scope: !2370)
!2370 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1154, column: 6)
!2371 = !DILocation(line: 1154, column: 6, scope: !1774)
!2372 = !DILocation(line: 1155, column: 12, scope: !2370)
!2373 = !DILocation(line: 1155, column: 5, scope: !2370)
!2374 = !DILocation(line: 1157, column: 6, scope: !2375)
!2375 = distinct !DILexicalBlock(scope: !1774, file: !1, line: 1157, column: 6)
!2376 = !DILocation(line: 1157, column: 9, scope: !2375)
!2377 = !DILocation(line: 1157, column: 6, scope: !1774)
!2378 = !DILocation(line: 1158, column: 26, scope: !2379)
!2379 = distinct !DILexicalBlock(scope: !2380, file: !1, line: 1158, column: 8)
!2380 = distinct !DILexicalBlock(scope: !2375, file: !1, line: 1157, column: 17)
!2381 = !DILocation(line: 1158, column: 33, scope: !2379)
!2382 = !DILocation(line: 1158, column: 36, scope: !2379)
!2383 = !DILocation(line: 1158, column: 12, scope: !2379)
!2384 = !DILocation(line: 1158, column: 10, scope: !2379)
!2385 = !DILocation(line: 1158, column: 8, scope: !2380)
!2386 = !DILocation(line: 1159, column: 10, scope: !2387)
!2387 = distinct !DILexicalBlock(scope: !2388, file: !1, line: 1159, column: 10)
!2388 = distinct !DILexicalBlock(scope: !2379, file: !1, line: 1158, column: 49)
!2389 = !DILocation(line: 1159, column: 13, scope: !2387)
!2390 = !DILocation(line: 1159, column: 18, scope: !2387)
!2391 = !DILocation(line: 1159, column: 10, scope: !2388)
!2392 = !DILocation(line: 1160, column: 15, scope: !2393)
!2393 = distinct !DILexicalBlock(scope: !2387, file: !1, line: 1159, column: 25)
!2394 = !DILocation(line: 1163, column: 15, scope: !2393)
!2395 = !DILocation(line: 1163, column: 66, scope: !2393)
!2396 = !DILocation(line: 1163, column: 69, scope: !2393)
!2397 = !DILocation(line: 1164, column: 15, scope: !2393)
!2398 = !DILocation(line: 1164, column: 18, scope: !2393)
!2399 = !DILocation(line: 1160, column: 9, scope: !2393)
!2400 = !DILocation(line: 1165, column: 7, scope: !2393)
!2401 = !DILocation(line: 1167, column: 15, scope: !2402)
!2402 = distinct !DILexicalBlock(scope: !2387, file: !1, line: 1166, column: 12)
!2403 = !DILocation(line: 1169, column: 15, scope: !2402)
!2404 = !DILocation(line: 1169, column: 66, scope: !2402)
!2405 = !DILocation(line: 1169, column: 69, scope: !2402)
!2406 = !DILocation(line: 1167, column: 9, scope: !2402)
!2407 = !DILocation(line: 1171, column: 7, scope: !2388)
!2408 = !DILocation(line: 1173, column: 3, scope: !2380)
!2409 = !DILocation(line: 1180, column: 10, scope: !2410)
!2410 = distinct !DILexicalBlock(scope: !2411, file: !1, line: 1180, column: 8)
!2411 = distinct !DILexicalBlock(scope: !2375, file: !1, line: 1174, column: 8)
!2412 = !DILocation(line: 1180, column: 16, scope: !2410)
!2413 = !DILocation(line: 1180, column: 20, scope: !2410)
!2414 = !DILocation(line: 1180, column: 33, scope: !2410)
!2415 = !DILocation(line: 1180, column: 37, scope: !2416)
!2416 = !DILexicalBlockFile(scope: !2410, file: !1, discriminator: 1)
!2417 = !DILocation(line: 1180, column: 40, scope: !2416)
!2418 = !DILocation(line: 1180, column: 45, scope: !2416)
!2419 = !DILocation(line: 1180, column: 52, scope: !2416)
!2420 = !DILocation(line: 1181, column: 9, scope: !2410)
!2421 = !DILocation(line: 1181, column: 12, scope: !2410)
!2422 = !DILocation(line: 1181, column: 25, scope: !2410)
!2423 = !DILocation(line: 1181, column: 28, scope: !2410)
!2424 = !DILocation(line: 1181, column: 22, scope: !2410)
!2425 = !DILocation(line: 1181, column: 34, scope: !2410)
!2426 = !DILocation(line: 1187, column: 9, scope: !2410)
!2427 = !DILocation(line: 1187, column: 12, scope: !2410)
!2428 = !DILocation(line: 1187, column: 26, scope: !2410)
!2429 = !DILocation(line: 1187, column: 29, scope: !2410)
!2430 = !DILocation(line: 1187, column: 36, scope: !2410)
!2431 = !DILocation(line: 1187, column: 42, scope: !2410)
!2432 = !DILocation(line: 1187, column: 48, scope: !2410)
!2433 = !DILocation(line: 1187, column: 34, scope: !2410)
!2434 = !DILocation(line: 1187, column: 22, scope: !2410)
!2435 = !DILocation(line: 1187, column: 67, scope: !2410)
!2436 = !DILocation(line: 1189, column: 9, scope: !2410)
!2437 = !DILocation(line: 1189, column: 15, scope: !2410)
!2438 = !DILocation(line: 1189, column: 19, scope: !2410)
!2439 = !DILocation(line: 1180, column: 8, scope: !2440)
!2440 = !DILexicalBlockFile(scope: !2411, file: !1, discriminator: 2)
!2441 = !DILocation(line: 1190, column: 13, scope: !2442)
!2442 = distinct !DILexicalBlock(scope: !2410, file: !1, line: 1189, column: 27)
!2443 = !DILocation(line: 1192, column: 13, scope: !2442)
!2444 = !DILocation(line: 1192, column: 16, scope: !2442)
!2445 = !DILocation(line: 1192, column: 23, scope: !2442)
!2446 = !DILocation(line: 1192, column: 26, scope: !2442)
!2447 = !DILocation(line: 1192, column: 21, scope: !2442)
!2448 = !DILocation(line: 1190, column: 7, scope: !2442)
!2449 = !DILocation(line: 1193, column: 7, scope: !2442)
!2450 = !DILocation(line: 1195, column: 10, scope: !2451)
!2451 = distinct !DILexicalBlock(scope: !2411, file: !1, line: 1195, column: 8)
!2452 = !DILocation(line: 1195, column: 16, scope: !2451)
!2453 = !DILocation(line: 1195, column: 20, scope: !2451)
!2454 = !DILocation(line: 1195, column: 33, scope: !2451)
!2455 = !DILocation(line: 1196, column: 13, scope: !2451)
!2456 = !DILocation(line: 1196, column: 16, scope: !2451)
!2457 = !DILocation(line: 1196, column: 22, scope: !2451)
!2458 = !DILocation(line: 1197, column: 14, scope: !2451)
!2459 = !DILocation(line: 1197, column: 20, scope: !2451)
!2460 = !DILocation(line: 1197, column: 26, scope: !2451)
!2461 = !DILocation(line: 1197, column: 32, scope: !2451)
!2462 = !DILocation(line: 1195, column: 8, scope: !2463)
!2463 = !DILexicalBlockFile(scope: !2411, file: !1, discriminator: 1)
!2464 = !DILocation(line: 1207, column: 13, scope: !2465)
!2465 = distinct !DILexicalBlock(scope: !2451, file: !1, line: 1197, column: 48)
!2466 = !DILocation(line: 1207, column: 7, scope: !2465)
!2467 = !DILocation(line: 1208, column: 7, scope: !2465)
!2468 = !DILocation(line: 1210, column: 24, scope: !2469)
!2469 = distinct !DILexicalBlock(scope: !2411, file: !1, line: 1210, column: 8)
!2470 = !DILocation(line: 1210, column: 8, scope: !2469)
!2471 = !DILocation(line: 1210, column: 8, scope: !2411)
!2472 = !DILocation(line: 1211, column: 7, scope: !2469)
!2473 = !DILocation(line: 1215, column: 18, scope: !1774)
!2474 = !DILocation(line: 1215, column: 21, scope: !1774)
!2475 = !DILocation(line: 1215, column: 27, scope: !1774)
!2476 = !DILocation(line: 1215, column: 14, scope: !1774)
!2477 = !DILocation(line: 1215, column: 11, scope: !1774)
!2478 = !DILocation(line: 1215, column: 4, scope: !1774)
!2479 = !DILocation(line: 1215, column: 9, scope: !1774)
!2480 = !DILocation(line: 1218, column: 3, scope: !1774)
!2481 = !DILocation(line: 1219, column: 1, scope: !1774)
!2482 = !DILocalVariable(name: "data", arg: 1, scope: !1795, file: !1, line: 389, type: !544)
!2483 = !DILocation(line: 389, column: 50, scope: !1795)
!2484 = !DILocalVariable(name: "conn", arg: 2, scope: !1795, file: !1, line: 390, type: !550)
!2485 = !DILocation(line: 390, column: 52, scope: !1795)
!2486 = !DILocalVariable(name: "k", arg: 3, scope: !1795, file: !1, line: 391, type: !1798)
!2487 = !DILocation(line: 391, column: 54, scope: !1795)
!2488 = !DILocalVariable(name: "didwhat", arg: 4, scope: !1795, file: !1, line: 392, type: !1434)
!2489 = !DILocation(line: 392, column: 37, scope: !1795)
!2490 = !DILocalVariable(name: "done", arg: 5, scope: !1795, file: !1, line: 392, type: !1423)
!2491 = !DILocation(line: 392, column: 52, scope: !1795)
!2492 = !DILocalVariable(name: "comeback", arg: 6, scope: !1795, file: !1, line: 393, type: !1423)
!2493 = !DILocation(line: 393, column: 38, scope: !1795)
!2494 = !DILocalVariable(name: "result", scope: !1795, file: !1, line: 395, type: !554)
!2495 = !DILocation(line: 395, column: 12, scope: !1795)
!2496 = !DILocalVariable(name: "nread", scope: !1795, file: !1, line: 396, type: !256)
!2497 = !DILocation(line: 396, column: 11, scope: !1795)
!2498 = !DILocalVariable(name: "excess", scope: !1795, file: !1, line: 397, type: !158)
!2499 = !DILocation(line: 397, column: 10, scope: !1795)
!2500 = !DILocalVariable(name: "is_empty_data", scope: !1795, file: !1, line: 398, type: !211)
!2501 = !DILocation(line: 398, column: 8, scope: !1795)
!2502 = !DILocalVariable(name: "readmore", scope: !1795, file: !1, line: 399, type: !211)
!2503 = !DILocation(line: 399, column: 8, scope: !1795)
!2504 = !DILocalVariable(name: "maxloops", scope: !1795, file: !1, line: 400, type: !177)
!2505 = !DILocation(line: 400, column: 7, scope: !1795)
!2506 = !DILocation(line: 402, column: 4, scope: !1795)
!2507 = !DILocation(line: 402, column: 9, scope: !1795)
!2508 = !DILocation(line: 403, column: 4, scope: !1795)
!2509 = !DILocation(line: 403, column: 13, scope: !1795)
!2510 = !DILocation(line: 407, column: 3, scope: !1795)
!2511 = !DILocalVariable(name: "buffersize", scope: !2512, file: !1, line: 408, type: !158)
!2512 = distinct !DILexicalBlock(scope: !1795, file: !1, line: 407, column: 6)
!2513 = !DILocation(line: 408, column: 12, scope: !2512)
!2514 = !DILocation(line: 408, column: 25, scope: !2512)
!2515 = !DILocation(line: 408, column: 31, scope: !2512)
!2516 = !DILocation(line: 408, column: 35, scope: !2512)
!2517 = !DILocation(line: 409, column: 7, scope: !2512)
!2518 = !DILocation(line: 409, column: 13, scope: !2512)
!2519 = !DILocation(line: 409, column: 17, scope: !2512)
!2520 = !DILocation(line: 408, column: 25, scope: !2521)
!2521 = !DILexicalBlockFile(scope: !2512, file: !1, discriminator: 1)
!2522 = !DILocation(line: 408, column: 25, scope: !2523)
!2523 = !DILexicalBlockFile(scope: !2512, file: !1, discriminator: 2)
!2524 = !DILocation(line: 408, column: 25, scope: !2525)
!2525 = !DILexicalBlockFile(scope: !2512, file: !1, discriminator: 3)
!2526 = !DILocation(line: 408, column: 12, scope: !2525)
!2527 = !DILocalVariable(name: "bytestoread", scope: !2512, file: !1, line: 410, type: !158)
!2528 = !DILocation(line: 410, column: 12, scope: !2512)
!2529 = !DILocation(line: 410, column: 26, scope: !2512)
!2530 = !DILocation(line: 423, column: 8, scope: !2531)
!2531 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 423, column: 8)
!2532 = !DILocation(line: 423, column: 11, scope: !2531)
!2533 = !DILocation(line: 423, column: 16, scope: !2531)
!2534 = !DILocation(line: 423, column: 22, scope: !2531)
!2535 = !DILocation(line: 423, column: 26, scope: !2536)
!2536 = !DILexicalBlockFile(scope: !2531, file: !1, discriminator: 1)
!2537 = !DILocation(line: 423, column: 29, scope: !2536)
!2538 = !DILocation(line: 423, column: 8, scope: !2536)
!2539 = !DILocalVariable(name: "totalleft", scope: !2540, file: !1, line: 427, type: !189)
!2540 = distinct !DILexicalBlock(scope: !2531, file: !1, line: 423, column: 37)
!2541 = !DILocation(line: 427, column: 18, scope: !2540)
!2542 = !DILocation(line: 427, column: 30, scope: !2540)
!2543 = !DILocation(line: 427, column: 33, scope: !2540)
!2544 = !DILocation(line: 427, column: 40, scope: !2540)
!2545 = !DILocation(line: 427, column: 43, scope: !2540)
!2546 = !DILocation(line: 427, column: 38, scope: !2540)
!2547 = !DILocation(line: 428, column: 10, scope: !2548)
!2548 = distinct !DILexicalBlock(scope: !2540, file: !1, line: 428, column: 10)
!2549 = !DILocation(line: 428, column: 34, scope: !2548)
!2550 = !DILocation(line: 428, column: 20, scope: !2548)
!2551 = !DILocation(line: 428, column: 10, scope: !2540)
!2552 = !DILocation(line: 429, column: 31, scope: !2548)
!2553 = !DILocation(line: 429, column: 21, scope: !2548)
!2554 = !DILocation(line: 429, column: 9, scope: !2548)
!2555 = !DILocation(line: 430, column: 5, scope: !2540)
!2556 = !DILocation(line: 432, column: 8, scope: !2557)
!2557 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 432, column: 8)
!2558 = !DILocation(line: 432, column: 8, scope: !2512)
!2559 = !DILocation(line: 434, column: 26, scope: !2560)
!2560 = distinct !DILexicalBlock(scope: !2557, file: !1, line: 432, column: 21)
!2561 = !DILocation(line: 434, column: 32, scope: !2560)
!2562 = !DILocation(line: 434, column: 38, scope: !2560)
!2563 = !DILocation(line: 434, column: 46, scope: !2560)
!2564 = !DILocation(line: 434, column: 49, scope: !2560)
!2565 = !DILocation(line: 434, column: 54, scope: !2560)
!2566 = !DILocation(line: 434, column: 16, scope: !2560)
!2567 = !DILocation(line: 434, column: 14, scope: !2560)
!2568 = !DILocation(line: 437, column: 25, scope: !2569)
!2569 = distinct !DILexicalBlock(scope: !2560, file: !1, line: 437, column: 10)
!2570 = !DILocation(line: 437, column: 22, scope: !2569)
!2571 = !DILocation(line: 437, column: 10, scope: !2560)
!2572 = !DILocation(line: 438, column: 9, scope: !2569)
!2573 = !DILocation(line: 440, column: 10, scope: !2574)
!2574 = distinct !DILexicalBlock(scope: !2560, file: !1, line: 440, column: 10)
!2575 = !DILocation(line: 440, column: 16, scope: !2574)
!2576 = !DILocation(line: 440, column: 10, scope: !2560)
!2577 = !DILocation(line: 441, column: 16, scope: !2574)
!2578 = !DILocation(line: 441, column: 9, scope: !2574)
!2579 = !DILocation(line: 442, column: 5, scope: !2560)
!2580 = !DILocation(line: 446, column: 7, scope: !2581)
!2581 = distinct !DILexicalBlock(scope: !2557, file: !1, line: 443, column: 10)
!2582 = !DILocation(line: 446, column: 7, scope: !2583)
!2583 = !DILexicalBlockFile(scope: !2584, file: !1, discriminator: 1)
!2584 = distinct !DILexicalBlock(scope: !2581, file: !1, line: 446, column: 7)
!2585 = !DILocation(line: 447, column: 13, scope: !2581)
!2586 = !DILocation(line: 450, column: 9, scope: !2587)
!2587 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 450, column: 8)
!2588 = !DILocation(line: 450, column: 12, scope: !2587)
!2589 = !DILocation(line: 450, column: 22, scope: !2587)
!2590 = !DILocation(line: 450, column: 28, scope: !2587)
!2591 = !DILocation(line: 450, column: 32, scope: !2592)
!2592 = !DILexicalBlockFile(scope: !2587, file: !1, discriminator: 1)
!2593 = !DILocation(line: 450, column: 35, scope: !2592)
!2594 = !DILocation(line: 450, column: 50, scope: !2592)
!2595 = !DILocation(line: 450, column: 8, scope: !2592)
!2596 = !DILocation(line: 451, column: 21, scope: !2597)
!2597 = distinct !DILexicalBlock(scope: !2587, file: !1, line: 450, column: 57)
!2598 = !DILocation(line: 451, column: 7, scope: !2597)
!2599 = !DILocation(line: 452, column: 10, scope: !2600)
!2600 = distinct !DILexicalBlock(scope: !2597, file: !1, line: 452, column: 10)
!2601 = !DILocation(line: 452, column: 13, scope: !2600)
!2602 = !DILocation(line: 452, column: 20, scope: !2600)
!2603 = !DILocation(line: 452, column: 10, scope: !2597)
!2604 = !DILocation(line: 454, column: 9, scope: !2600)
!2605 = !DILocation(line: 454, column: 12, scope: !2600)
!2606 = !DILocation(line: 454, column: 23, scope: !2600)
!2607 = !DILocation(line: 454, column: 23, scope: !2608)
!2608 = !DILexicalBlockFile(scope: !2600, file: !1, discriminator: 1)
!2609 = !DILocation(line: 455, column: 5, scope: !2597)
!2610 = !DILocation(line: 457, column: 6, scope: !2512)
!2611 = !DILocation(line: 457, column: 14, scope: !2512)
!2612 = !DILocation(line: 459, column: 23, scope: !2512)
!2613 = !DILocation(line: 459, column: 29, scope: !2512)
!2614 = !DILocation(line: 459, column: 35, scope: !2512)
!2615 = !DILocation(line: 459, column: 39, scope: !2521)
!2616 = !DILocation(line: 459, column: 42, scope: !2521)
!2617 = !DILocation(line: 459, column: 53, scope: !2521)
!2618 = !DILocation(line: 459, column: 21, scope: !2523)
!2619 = !DILocation(line: 459, column: 19, scope: !2523)
!2620 = !DILocation(line: 462, column: 12, scope: !2621)
!2621 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 462, column: 8)
!2622 = !DILocation(line: 462, column: 10, scope: !2621)
!2623 = !DILocation(line: 462, column: 18, scope: !2621)
!2624 = !DILocation(line: 462, column: 21, scope: !2625)
!2625 = !DILexicalBlockFile(scope: !2621, file: !1, discriminator: 1)
!2626 = !DILocation(line: 462, column: 8, scope: !2625)
!2627 = !DILocation(line: 463, column: 14, scope: !2628)
!2628 = distinct !DILexicalBlock(scope: !2621, file: !1, line: 462, column: 36)
!2629 = !DILocation(line: 463, column: 7, scope: !2628)
!2630 = !DILocation(line: 463, column: 10, scope: !2628)
!2631 = !DILocation(line: 463, column: 21, scope: !2628)
!2632 = !DILocation(line: 464, column: 5, scope: !2628)
!2633 = !DILocation(line: 465, column: 18, scope: !2634)
!2634 = distinct !DILexicalBlock(scope: !2621, file: !1, line: 465, column: 13)
!2635 = !DILocation(line: 465, column: 15, scope: !2634)
!2636 = !DILocation(line: 465, column: 13, scope: !2621)
!2637 = !DILocation(line: 468, column: 7, scope: !2638)
!2638 = distinct !DILexicalBlock(scope: !2634, file: !1, line: 465, column: 25)
!2639 = !DILocation(line: 468, column: 7, scope: !2640)
!2640 = !DILexicalBlockFile(scope: !2641, file: !1, discriminator: 1)
!2641 = distinct !DILexicalBlock(scope: !2638, file: !1, line: 468, column: 7)
!2642 = !DILocation(line: 469, column: 7, scope: !2638)
!2643 = !DILocation(line: 469, column: 10, scope: !2638)
!2644 = !DILocation(line: 469, column: 17, scope: !2638)
!2645 = !DILocation(line: 470, column: 7, scope: !2638)
!2646 = !DILocation(line: 475, column: 14, scope: !2512)
!2647 = !DILocation(line: 475, column: 17, scope: !2512)
!2648 = !DILocation(line: 475, column: 5, scope: !2512)
!2649 = !DILocation(line: 475, column: 8, scope: !2512)
!2650 = !DILocation(line: 475, column: 12, scope: !2512)
!2651 = !DILocation(line: 477, column: 8, scope: !2652)
!2652 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 477, column: 8)
!2653 = !DILocation(line: 477, column: 14, scope: !2652)
!2654 = !DILocation(line: 477, column: 23, scope: !2652)
!2655 = !DILocation(line: 477, column: 8, scope: !2512)
!2656 = !DILocation(line: 478, column: 16, scope: !2657)
!2657 = distinct !DILexicalBlock(scope: !2652, file: !1, line: 477, column: 34)
!2658 = !DILocation(line: 478, column: 22, scope: !2657)
!2659 = !DILocation(line: 478, column: 31, scope: !2657)
!2660 = !DILocation(line: 478, column: 41, scope: !2657)
!2661 = !DILocation(line: 478, column: 47, scope: !2657)
!2662 = !DILocation(line: 478, column: 14, scope: !2657)
!2663 = !DILocation(line: 479, column: 10, scope: !2664)
!2664 = distinct !DILexicalBlock(scope: !2657, file: !1, line: 479, column: 10)
!2665 = !DILocation(line: 479, column: 10, scope: !2657)
!2666 = !DILocation(line: 480, column: 16, scope: !2664)
!2667 = !DILocation(line: 480, column: 9, scope: !2664)
!2668 = !DILocation(line: 481, column: 10, scope: !2669)
!2669 = distinct !DILexicalBlock(scope: !2657, file: !1, line: 481, column: 10)
!2670 = !DILocation(line: 481, column: 10, scope: !2657)
!2671 = !DILocation(line: 482, column: 9, scope: !2669)
!2672 = !DILocation(line: 483, column: 5, scope: !2657)
!2673 = !DILocation(line: 488, column: 8, scope: !2674)
!2674 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 488, column: 8)
!2675 = !DILocation(line: 488, column: 11, scope: !2674)
!2676 = !DILocation(line: 488, column: 8, scope: !2512)
!2677 = !DILocalVariable(name: "stop_reading", scope: !2678, file: !1, line: 490, type: !211)
!2678 = distinct !DILexicalBlock(scope: !2674, file: !1, line: 488, column: 19)
!2679 = !DILocation(line: 490, column: 12, scope: !2678)
!2680 = !DILocation(line: 491, column: 44, scope: !2678)
!2681 = !DILocation(line: 491, column: 50, scope: !2678)
!2682 = !DILocation(line: 491, column: 16, scope: !2678)
!2683 = !DILocation(line: 491, column: 14, scope: !2678)
!2684 = !DILocation(line: 492, column: 10, scope: !2685)
!2685 = distinct !DILexicalBlock(scope: !2678, file: !1, line: 492, column: 10)
!2686 = !DILocation(line: 492, column: 10, scope: !2678)
!2687 = !DILocation(line: 493, column: 16, scope: !2685)
!2688 = !DILocation(line: 493, column: 9, scope: !2685)
!2689 = !DILocation(line: 495, column: 10, scope: !2690)
!2690 = distinct !DILexicalBlock(scope: !2678, file: !1, line: 495, column: 10)
!2691 = !DILocation(line: 495, column: 16, scope: !2690)
!2692 = !DILocation(line: 495, column: 25, scope: !2690)
!2693 = !DILocation(line: 495, column: 35, scope: !2690)
!2694 = !DILocation(line: 496, column: 11, scope: !2690)
!2695 = !DILocation(line: 496, column: 14, scope: !2690)
!2696 = !DILocation(line: 496, column: 26, scope: !2690)
!2697 = !DILocation(line: 496, column: 31, scope: !2690)
!2698 = !DILocation(line: 496, column: 34, scope: !2699)
!2699 = !DILexicalBlockFile(scope: !2690, file: !1, discriminator: 1)
!2700 = !DILocation(line: 496, column: 40, scope: !2699)
!2701 = !DILocation(line: 495, column: 10, scope: !2702)
!2702 = !DILexicalBlockFile(scope: !2678, file: !1, discriminator: 1)
!2703 = !DILocation(line: 497, column: 18, scope: !2704)
!2704 = distinct !DILexicalBlock(scope: !2690, file: !1, line: 496, column: 46)
!2705 = !DILocation(line: 497, column: 24, scope: !2704)
!2706 = !DILocation(line: 497, column: 33, scope: !2704)
!2707 = !DILocation(line: 497, column: 43, scope: !2704)
!2708 = !DILocation(line: 497, column: 49, scope: !2704)
!2709 = !DILocation(line: 497, column: 16, scope: !2704)
!2710 = !DILocation(line: 498, column: 12, scope: !2711)
!2711 = distinct !DILexicalBlock(scope: !2704, file: !1, line: 498, column: 12)
!2712 = !DILocation(line: 498, column: 12, scope: !2704)
!2713 = !DILocation(line: 499, column: 18, scope: !2711)
!2714 = !DILocation(line: 499, column: 11, scope: !2711)
!2715 = !DILocation(line: 500, column: 12, scope: !2716)
!2716 = distinct !DILexicalBlock(scope: !2704, file: !1, line: 500, column: 12)
!2717 = !DILocation(line: 500, column: 12, scope: !2704)
!2718 = !DILocation(line: 501, column: 11, scope: !2716)
!2719 = !DILocation(line: 502, column: 7, scope: !2704)
!2720 = !DILocation(line: 504, column: 10, scope: !2721)
!2721 = distinct !DILexicalBlock(scope: !2678, file: !1, line: 504, column: 10)
!2722 = !DILocation(line: 504, column: 10, scope: !2678)
!2723 = !DILocation(line: 507, column: 12, scope: !2724)
!2724 = distinct !DILexicalBlock(scope: !2725, file: !1, line: 507, column: 12)
!2725 = distinct !DILexicalBlock(scope: !2721, file: !1, line: 504, column: 24)
!2726 = !DILocation(line: 507, column: 18, scope: !2724)
!2727 = !DILocation(line: 507, column: 12, scope: !2725)
!2728 = !DILocation(line: 508, column: 35, scope: !2729)
!2729 = distinct !DILexicalBlock(scope: !2730, file: !1, line: 508, column: 14)
!2730 = distinct !DILexicalBlock(scope: !2724, file: !1, line: 507, column: 23)
!2731 = !DILocation(line: 508, column: 41, scope: !2729)
!2732 = !DILocation(line: 508, column: 47, scope: !2729)
!2733 = !DILocation(line: 508, column: 14, scope: !2729)
!2734 = !DILocation(line: 508, column: 14, scope: !2730)
!2735 = !DILocation(line: 509, column: 19, scope: !2736)
!2736 = distinct !DILexicalBlock(scope: !2729, file: !1, line: 508, column: 71)
!2737 = !DILocation(line: 512, column: 19, scope: !2736)
!2738 = !DILocation(line: 512, column: 26, scope: !2736)
!2739 = !DILocation(line: 512, column: 32, scope: !2736)
!2740 = !DILocation(line: 512, column: 38, scope: !2736)
!2741 = !DILocation(line: 509, column: 13, scope: !2736)
!2742 = !DILocation(line: 513, column: 25, scope: !2736)
!2743 = !DILocation(line: 513, column: 39, scope: !2736)
!2744 = !DILocation(line: 513, column: 13, scope: !2736)
!2745 = !DILocation(line: 514, column: 11, scope: !2736)
!2746 = !DILocation(line: 516, column: 19, scope: !2747)
!2747 = distinct !DILexicalBlock(scope: !2729, file: !1, line: 515, column: 16)
!2748 = !DILocation(line: 520, column: 19, scope: !2747)
!2749 = !DILocation(line: 520, column: 26, scope: !2747)
!2750 = !DILocation(line: 520, column: 32, scope: !2747)
!2751 = !DILocation(line: 520, column: 38, scope: !2747)
!2752 = !DILocation(line: 516, column: 13, scope: !2747)
!2753 = !DILocation(line: 522, column: 9, scope: !2730)
!2754 = !DILocation(line: 524, column: 9, scope: !2725)
!2755 = !DILocation(line: 526, column: 5, scope: !2678)
!2756 = !DILocation(line: 533, column: 8, scope: !2757)
!2757 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 533, column: 8)
!2758 = !DILocation(line: 533, column: 11, scope: !2757)
!2759 = !DILocation(line: 533, column: 15, scope: !2757)
!2760 = !DILocation(line: 533, column: 19, scope: !2761)
!2761 = !DILexicalBlockFile(scope: !2757, file: !1, discriminator: 1)
!2762 = !DILocation(line: 533, column: 22, scope: !2761)
!2763 = !DILocation(line: 533, column: 29, scope: !2761)
!2764 = !DILocation(line: 533, column: 33, scope: !2765)
!2765 = !DILexicalBlockFile(scope: !2757, file: !1, discriminator: 2)
!2766 = !DILocation(line: 533, column: 39, scope: !2765)
!2767 = !DILocation(line: 533, column: 43, scope: !2765)
!2768 = !DILocation(line: 533, column: 46, scope: !2769)
!2769 = !DILexicalBlockFile(scope: !2757, file: !1, discriminator: 3)
!2770 = !DILocation(line: 533, column: 8, scope: !2769)
!2771 = !DILocation(line: 535, column: 10, scope: !2772)
!2772 = distinct !DILexicalBlock(scope: !2773, file: !1, line: 535, column: 10)
!2773 = distinct !DILexicalBlock(scope: !2757, file: !1, line: 533, column: 62)
!2774 = !DILocation(line: 535, column: 16, scope: !2772)
!2775 = !DILocation(line: 535, column: 20, scope: !2772)
!2776 = !DILocation(line: 535, column: 10, scope: !2773)
!2777 = !DILocation(line: 537, column: 9, scope: !2778)
!2778 = distinct !DILexicalBlock(scope: !2772, file: !1, line: 535, column: 33)
!2779 = !DILocation(line: 538, column: 10, scope: !2778)
!2780 = !DILocation(line: 538, column: 15, scope: !2778)
!2781 = !DILocation(line: 539, column: 9, scope: !2778)
!2782 = !DILocation(line: 543, column: 15, scope: !2783)
!2783 = distinct !DILexicalBlock(scope: !2773, file: !1, line: 543, column: 10)
!2784 = !DILocation(line: 543, column: 18, scope: !2783)
!2785 = !DILocation(line: 543, column: 12, scope: !2783)
!2786 = !DILocation(line: 543, column: 29, scope: !2783)
!2787 = !DILocation(line: 543, column: 33, scope: !2788)
!2788 = !DILexicalBlockFile(scope: !2783, file: !1, discriminator: 1)
!2789 = !DILocation(line: 543, column: 10, scope: !2788)
!2790 = !DILocation(line: 546, column: 12, scope: !2791)
!2791 = distinct !DILexicalBlock(scope: !2792, file: !1, line: 546, column: 12)
!2792 = distinct !DILexicalBlock(scope: !2783, file: !1, line: 543, column: 48)
!2793 = !DILocation(line: 546, column: 18, scope: !2791)
!2794 = !DILocation(line: 546, column: 27, scope: !2791)
!2795 = !DILocation(line: 546, column: 35, scope: !2791)
!2796 = !DILocation(line: 546, column: 12, scope: !2792)
!2797 = !DILocation(line: 549, column: 14, scope: !2798)
!2798 = distinct !DILexicalBlock(scope: !2799, file: !1, line: 549, column: 14)
!2799 = distinct !DILexicalBlock(scope: !2791, file: !1, line: 546, column: 72)
!2800 = !DILocation(line: 549, column: 20, scope: !2798)
!2801 = !DILocation(line: 549, column: 24, scope: !2798)
!2802 = !DILocation(line: 549, column: 14, scope: !2799)
!2803 = !DILocation(line: 550, column: 16, scope: !2804)
!2804 = distinct !DILexicalBlock(scope: !2805, file: !1, line: 550, column: 16)
!2805 = distinct !DILexicalBlock(scope: !2798, file: !1, line: 549, column: 32)
!2806 = !DILocation(line: 550, column: 22, scope: !2804)
!2807 = !DILocation(line: 550, column: 27, scope: !2804)
!2808 = !DILocation(line: 550, column: 16, scope: !2805)
!2809 = !DILocation(line: 553, column: 15, scope: !2810)
!2810 = distinct !DILexicalBlock(scope: !2804, file: !1, line: 550, column: 34)
!2811 = !DILocation(line: 553, column: 18, scope: !2810)
!2812 = !DILocation(line: 553, column: 25, scope: !2810)
!2813 = !DILocation(line: 554, column: 16, scope: !2810)
!2814 = !DILocation(line: 554, column: 21, scope: !2810)
!2815 = !DILocation(line: 555, column: 15, scope: !2810)
!2816 = !DILocation(line: 560, column: 13, scope: !2805)
!2817 = !DILocation(line: 560, column: 16, scope: !2805)
!2818 = !DILocation(line: 560, column: 27, scope: !2805)
!2819 = !DILocation(line: 561, column: 19, scope: !2805)
!2820 = !DILocation(line: 561, column: 13, scope: !2805)
!2821 = !DILocation(line: 562, column: 11, scope: !2805)
!2822 = !DILocation(line: 563, column: 14, scope: !2823)
!2823 = distinct !DILexicalBlock(scope: !2799, file: !1, line: 563, column: 14)
!2824 = !DILocation(line: 563, column: 20, scope: !2823)
!2825 = !DILocation(line: 563, column: 26, scope: !2823)
!2826 = !DILocation(line: 563, column: 38, scope: !2823)
!2827 = !DILocation(line: 563, column: 42, scope: !2828)
!2828 = !DILexicalBlockFile(scope: !2823, file: !1, discriminator: 1)
!2829 = !DILocation(line: 563, column: 45, scope: !2828)
!2830 = !DILocation(line: 563, column: 59, scope: !2828)
!2831 = !DILocation(line: 564, column: 15, scope: !2823)
!2832 = !DILocation(line: 564, column: 21, scope: !2823)
!2833 = !DILocation(line: 564, column: 25, scope: !2823)
!2834 = !DILocation(line: 564, column: 32, scope: !2823)
!2835 = !DILocation(line: 564, column: 47, scope: !2823)
!2836 = !DILocation(line: 565, column: 15, scope: !2823)
!2837 = !DILocation(line: 565, column: 18, scope: !2823)
!2838 = !DILocation(line: 563, column: 14, scope: !2839)
!2839 = !DILexicalBlockFile(scope: !2799, file: !1, discriminator: 2)
!2840 = !DILocation(line: 567, column: 16, scope: !2841)
!2841 = distinct !DILexicalBlock(scope: !2842, file: !1, line: 567, column: 16)
!2842 = distinct !DILexicalBlock(scope: !2823, file: !1, line: 565, column: 30)
!2843 = !DILocation(line: 567, column: 19, scope: !2841)
!2844 = !DILocation(line: 567, column: 27, scope: !2841)
!2845 = !DILocation(line: 567, column: 33, scope: !2841)
!2846 = !DILocation(line: 567, column: 39, scope: !2841)
!2847 = !DILocation(line: 567, column: 24, scope: !2841)
!2848 = !DILocation(line: 567, column: 16, scope: !2842)
!2849 = !DILocation(line: 570, column: 21, scope: !2850)
!2850 = distinct !DILexicalBlock(scope: !2841, file: !1, line: 567, column: 52)
!2851 = !DILocation(line: 570, column: 15, scope: !2850)
!2852 = !DILocation(line: 571, column: 15, scope: !2850)
!2853 = !DILocation(line: 573, column: 15, scope: !2850)
!2854 = !DILocation(line: 573, column: 18, scope: !2850)
!2855 = !DILocation(line: 573, column: 25, scope: !2850)
!2856 = !DILocation(line: 574, column: 16, scope: !2850)
!2857 = !DILocation(line: 574, column: 21, scope: !2850)
!2858 = !DILocation(line: 575, column: 15, scope: !2850)
!2859 = !DILocation(line: 581, column: 19, scope: !2842)
!2860 = !DILocation(line: 581, column: 13, scope: !2842)
!2861 = !DILocation(line: 583, column: 13, scope: !2842)
!2862 = !DILocation(line: 586, column: 14, scope: !2863)
!2863 = distinct !DILexicalBlock(scope: !2799, file: !1, line: 586, column: 14)
!2864 = !DILocation(line: 586, column: 20, scope: !2863)
!2865 = !DILocation(line: 586, column: 24, scope: !2863)
!2866 = !DILocation(line: 586, column: 38, scope: !2863)
!2867 = !DILocation(line: 586, column: 42, scope: !2868)
!2868 = !DILexicalBlockFile(scope: !2863, file: !1, discriminator: 1)
!2869 = !DILocation(line: 586, column: 48, scope: !2868)
!2870 = !DILocation(line: 586, column: 54, scope: !2868)
!2871 = !DILocation(line: 586, column: 14, scope: !2868)
!2872 = !DILocation(line: 592, column: 42, scope: !2873)
!2873 = distinct !DILexicalBlock(scope: !2874, file: !1, line: 592, column: 16)
!2874 = distinct !DILexicalBlock(scope: !2863, file: !1, line: 586, column: 61)
!2875 = !DILocation(line: 592, column: 48, scope: !2873)
!2876 = !DILocation(line: 592, column: 51, scope: !2873)
!2877 = !DILocation(line: 592, column: 17, scope: !2873)
!2878 = !DILocation(line: 592, column: 16, scope: !2874)
!2879 = !DILocation(line: 593, column: 16, scope: !2880)
!2880 = distinct !DILexicalBlock(scope: !2873, file: !1, line: 592, column: 63)
!2881 = !DILocation(line: 593, column: 21, scope: !2880)
!2882 = !DILocation(line: 596, column: 15, scope: !2880)
!2883 = !DILocation(line: 596, column: 21, scope: !2880)
!2884 = !DILocation(line: 596, column: 26, scope: !2880)
!2885 = !DILocation(line: 596, column: 35, scope: !2880)
!2886 = !DILocation(line: 597, column: 21, scope: !2880)
!2887 = !DILocation(line: 597, column: 15, scope: !2880)
!2888 = !DILocation(line: 600, column: 15, scope: !2880)
!2889 = !DILocation(line: 601, column: 15, scope: !2880)
!2890 = !DILocation(line: 603, column: 11, scope: !2874)
!2891 = !DILocation(line: 605, column: 9, scope: !2799)
!2892 = !DILocation(line: 606, column: 7, scope: !2792)
!2893 = !DILocation(line: 609, column: 7, scope: !2773)
!2894 = !DILocation(line: 609, column: 10, scope: !2773)
!2895 = !DILocation(line: 609, column: 20, scope: !2773)
!2896 = !DILocation(line: 612, column: 10, scope: !2897)
!2897 = distinct !DILexicalBlock(scope: !2773, file: !1, line: 612, column: 10)
!2898 = !DILocation(line: 612, column: 16, scope: !2897)
!2899 = !DILocation(line: 612, column: 20, scope: !2897)
!2900 = !DILocation(line: 612, column: 10, scope: !2773)
!2901 = !DILocation(line: 613, column: 12, scope: !2902)
!2902 = distinct !DILexicalBlock(scope: !2903, file: !1, line: 613, column: 12)
!2903 = distinct !DILexicalBlock(scope: !2897, file: !1, line: 612, column: 29)
!2904 = !DILocation(line: 613, column: 15, scope: !2902)
!2905 = !DILocation(line: 613, column: 12, scope: !2903)
!2906 = !DILocation(line: 614, column: 22, scope: !2907)
!2907 = distinct !DILexicalBlock(scope: !2902, file: !1, line: 613, column: 26)
!2908 = !DILocation(line: 614, column: 46, scope: !2907)
!2909 = !DILocation(line: 614, column: 52, scope: !2907)
!2910 = !DILocation(line: 614, column: 58, scope: !2907)
!2911 = !DILocation(line: 615, column: 30, scope: !2907)
!2912 = !DILocation(line: 615, column: 33, scope: !2907)
!2913 = !DILocation(line: 615, column: 42, scope: !2907)
!2914 = !DILocation(line: 614, column: 11, scope: !2907)
!2915 = !DILocation(line: 616, column: 14, scope: !2916)
!2916 = distinct !DILexicalBlock(scope: !2907, file: !1, line: 616, column: 14)
!2917 = !DILocation(line: 616, column: 17, scope: !2916)
!2918 = !DILocation(line: 616, column: 27, scope: !2916)
!2919 = !DILocation(line: 616, column: 14, scope: !2907)
!2920 = !DILocation(line: 617, column: 24, scope: !2916)
!2921 = !DILocation(line: 618, column: 24, scope: !2916)
!2922 = !DILocation(line: 618, column: 27, scope: !2916)
!2923 = !DILocation(line: 618, column: 40, scope: !2916)
!2924 = !DILocation(line: 618, column: 47, scope: !2916)
!2925 = !DILocation(line: 617, column: 13, scope: !2916)
!2926 = !DILocation(line: 619, column: 9, scope: !2907)
!2927 = !DILocation(line: 621, column: 22, scope: !2902)
!2928 = !DILocation(line: 622, column: 22, scope: !2902)
!2929 = !DILocation(line: 622, column: 25, scope: !2902)
!2930 = !DILocation(line: 622, column: 38, scope: !2902)
!2931 = !DILocation(line: 622, column: 45, scope: !2902)
!2932 = !DILocation(line: 621, column: 11, scope: !2902)
!2933 = !DILocation(line: 623, column: 7, scope: !2903)
!2934 = !DILocation(line: 626, column: 10, scope: !2935)
!2935 = distinct !DILexicalBlock(scope: !2773, file: !1, line: 626, column: 10)
!2936 = !DILocation(line: 626, column: 13, scope: !2935)
!2937 = !DILocation(line: 626, column: 10, scope: !2773)
!2938 = !DILocalVariable(name: "res", scope: !2939, file: !1, line: 634, type: !2940)
!2939 = distinct !DILexicalBlock(scope: !2935, file: !1, line: 626, column: 20)
!2940 = !DIDerivedType(tag: DW_TAG_typedef, name: "CHUNKcode", file: !400, line: 78, baseType: !1752)
!2941 = !DILocation(line: 634, column: 19, scope: !2939)
!2942 = !DILocation(line: 635, column: 31, scope: !2939)
!2943 = !DILocation(line: 635, column: 37, scope: !2939)
!2944 = !DILocation(line: 635, column: 40, scope: !2939)
!2945 = !DILocation(line: 635, column: 45, scope: !2939)
!2946 = !DILocation(line: 635, column: 11, scope: !2939)
!2947 = !DILocation(line: 637, column: 24, scope: !2948)
!2948 = distinct !DILexicalBlock(scope: !2939, file: !1, line: 637, column: 12)
!2949 = !DILocation(line: 637, column: 22, scope: !2948)
!2950 = !DILocation(line: 637, column: 12, scope: !2939)
!2951 = !DILocation(line: 638, column: 36, scope: !2952)
!2952 = distinct !DILexicalBlock(scope: !2953, file: !1, line: 638, column: 14)
!2953 = distinct !DILexicalBlock(scope: !2948, file: !1, line: 637, column: 29)
!2954 = !DILocation(line: 638, column: 33, scope: !2952)
!2955 = !DILocation(line: 638, column: 14, scope: !2953)
!2956 = !DILocation(line: 639, column: 19, scope: !2957)
!2957 = distinct !DILexicalBlock(scope: !2952, file: !1, line: 638, column: 41)
!2958 = !DILocation(line: 639, column: 13, scope: !2957)
!2959 = !DILocation(line: 640, column: 13, scope: !2957)
!2960 = !DILocation(line: 642, column: 17, scope: !2953)
!2961 = !DILocation(line: 642, column: 71, scope: !2953)
!2962 = !DILocation(line: 642, column: 49, scope: !2953)
!2963 = !DILocation(line: 642, column: 11, scope: !2964)
!2964 = !DILexicalBlockFile(scope: !2953, file: !1, discriminator: 1)
!2965 = !DILocation(line: 643, column: 11, scope: !2953)
!2966 = !DILocation(line: 645, column: 27, scope: !2967)
!2967 = distinct !DILexicalBlock(scope: !2939, file: !1, line: 645, column: 12)
!2968 = !DILocation(line: 645, column: 24, scope: !2967)
!2969 = !DILocation(line: 645, column: 12, scope: !2939)
!2970 = !DILocalVariable(name: "dataleft", scope: !2971, file: !1, line: 646, type: !158)
!2971 = distinct !DILexicalBlock(scope: !2967, file: !1, line: 645, column: 32)
!2972 = !DILocation(line: 646, column: 18, scope: !2971)
!2973 = !DILocation(line: 648, column: 11, scope: !2971)
!2974 = !DILocation(line: 648, column: 14, scope: !2971)
!2975 = !DILocation(line: 648, column: 21, scope: !2971)
!2976 = !DILocation(line: 656, column: 22, scope: !2971)
!2977 = !DILocation(line: 656, column: 28, scope: !2971)
!2978 = !DILocation(line: 656, column: 34, scope: !2971)
!2979 = !DILocation(line: 656, column: 20, scope: !2971)
!2980 = !DILocation(line: 657, column: 14, scope: !2981)
!2981 = distinct !DILexicalBlock(scope: !2971, file: !1, line: 657, column: 14)
!2982 = !DILocation(line: 657, column: 23, scope: !2981)
!2983 = !DILocation(line: 657, column: 14, scope: !2971)
!2984 = !DILocation(line: 658, column: 19, scope: !2985)
!2985 = distinct !DILexicalBlock(scope: !2981, file: !1, line: 657, column: 29)
!2986 = !DILocation(line: 658, column: 25, scope: !2985)
!2987 = !DILocation(line: 659, column: 19, scope: !2985)
!2988 = !DILocation(line: 658, column: 13, scope: !2985)
!2989 = !DILocation(line: 660, column: 37, scope: !2990)
!2990 = distinct !DILexicalBlock(scope: !2985, file: !1, line: 660, column: 16)
!2991 = !DILocation(line: 660, column: 43, scope: !2990)
!2992 = !DILocation(line: 660, column: 49, scope: !2990)
!2993 = !DILocation(line: 660, column: 16, scope: !2990)
!2994 = !DILocation(line: 660, column: 16, scope: !2985)
!2995 = !DILocation(line: 662, column: 21, scope: !2996)
!2996 = distinct !DILexicalBlock(scope: !2990, file: !1, line: 660, column: 73)
!2997 = !DILocation(line: 662, column: 27, scope: !2996)
!2998 = !DILocation(line: 662, column: 57, scope: !2996)
!2999 = !DILocation(line: 662, column: 15, scope: !2996)
!3000 = !DILocation(line: 663, column: 27, scope: !2996)
!3001 = !DILocation(line: 663, column: 33, scope: !2996)
!3002 = !DILocation(line: 663, column: 15, scope: !2996)
!3003 = !DILocation(line: 664, column: 13, scope: !2996)
!3004 = !DILocation(line: 665, column: 11, scope: !2985)
!3005 = !DILocation(line: 666, column: 9, scope: !2971)
!3006 = !DILocation(line: 668, column: 7, scope: !2939)
!3007 = !DILocation(line: 672, column: 10, scope: !3008)
!3008 = distinct !DILexicalBlock(scope: !2773, file: !1, line: 672, column: 10)
!3009 = !DILocation(line: 672, column: 13, scope: !3008)
!3010 = !DILocation(line: 672, column: 23, scope: !3008)
!3011 = !DILocation(line: 672, column: 27, scope: !3012)
!3012 = !DILexicalBlockFile(scope: !3008, file: !1, discriminator: 1)
!3013 = !DILocation(line: 672, column: 30, scope: !3012)
!3014 = !DILocation(line: 672, column: 10, scope: !3012)
!3015 = !DILocation(line: 673, column: 9, scope: !3016)
!3016 = distinct !DILexicalBlock(scope: !3008, file: !1, line: 672, column: 42)
!3017 = !DILocation(line: 673, column: 9, scope: !3018)
!3018 = !DILexicalBlockFile(scope: !3019, file: !1, discriminator: 1)
!3019 = distinct !DILexicalBlock(scope: !3016, file: !1, line: 673, column: 9)
!3020 = !DILocation(line: 675, column: 25, scope: !3016)
!3021 = !DILocation(line: 675, column: 28, scope: !3016)
!3022 = !DILocation(line: 675, column: 9, scope: !3016)
!3023 = !DILocation(line: 675, column: 12, scope: !3016)
!3024 = !DILocation(line: 675, column: 22, scope: !3016)
!3025 = !DILocation(line: 676, column: 7, scope: !3016)
!3026 = !DILocation(line: 678, column: 17, scope: !3027)
!3027 = distinct !DILexicalBlock(scope: !2773, file: !1, line: 678, column: 10)
!3028 = !DILocation(line: 678, column: 20, scope: !3027)
!3029 = !DILocation(line: 678, column: 14, scope: !3027)
!3030 = !DILocation(line: 678, column: 33, scope: !3027)
!3031 = !DILocation(line: 679, column: 11, scope: !3027)
!3032 = !DILocation(line: 679, column: 14, scope: !3027)
!3033 = !DILocation(line: 679, column: 26, scope: !3027)
!3034 = !DILocation(line: 679, column: 24, scope: !3027)
!3035 = !DILocation(line: 679, column: 35, scope: !3027)
!3036 = !DILocation(line: 679, column: 38, scope: !3027)
!3037 = !DILocation(line: 679, column: 32, scope: !3027)
!3038 = !DILocation(line: 678, column: 10, scope: !3039)
!3039 = !DILexicalBlockFile(scope: !2773, file: !1, discriminator: 1)
!3040 = !DILocation(line: 681, column: 27, scope: !3041)
!3041 = distinct !DILexicalBlock(scope: !3027, file: !1, line: 679, column: 52)
!3042 = !DILocation(line: 681, column: 30, scope: !3041)
!3043 = !DILocation(line: 681, column: 42, scope: !3041)
!3044 = !DILocation(line: 681, column: 40, scope: !3041)
!3045 = !DILocation(line: 681, column: 50, scope: !3041)
!3046 = !DILocation(line: 681, column: 53, scope: !3041)
!3047 = !DILocation(line: 681, column: 48, scope: !3041)
!3048 = !DILocation(line: 681, column: 16, scope: !3041)
!3049 = !DILocation(line: 682, column: 12, scope: !3050)
!3050 = distinct !DILexicalBlock(scope: !3041, file: !1, line: 682, column: 12)
!3051 = !DILocation(line: 682, column: 19, scope: !3050)
!3052 = !DILocation(line: 682, column: 23, scope: !3050)
!3053 = !DILocation(line: 682, column: 27, scope: !3054)
!3054 = !DILexicalBlockFile(scope: !3050, file: !1, discriminator: 1)
!3055 = !DILocation(line: 682, column: 30, scope: !3054)
!3056 = !DILocation(line: 682, column: 12, scope: !3054)
!3057 = !DILocation(line: 683, column: 35, scope: !3058)
!3058 = distinct !DILexicalBlock(scope: !3059, file: !1, line: 683, column: 14)
!3059 = distinct !DILexicalBlock(scope: !3050, file: !1, line: 682, column: 42)
!3060 = !DILocation(line: 683, column: 41, scope: !3058)
!3061 = !DILocation(line: 683, column: 47, scope: !3058)
!3062 = !DILocation(line: 683, column: 14, scope: !3058)
!3063 = !DILocation(line: 683, column: 14, scope: !3059)
!3064 = !DILocation(line: 686, column: 19, scope: !3065)
!3065 = distinct !DILexicalBlock(scope: !3058, file: !1, line: 683, column: 71)
!3066 = !DILocation(line: 691, column: 19, scope: !3065)
!3067 = !DILocation(line: 691, column: 27, scope: !3065)
!3068 = !DILocation(line: 691, column: 33, scope: !3065)
!3069 = !DILocation(line: 691, column: 39, scope: !3065)
!3070 = !DILocation(line: 692, column: 19, scope: !3065)
!3071 = !DILocation(line: 692, column: 22, scope: !3065)
!3072 = !DILocation(line: 692, column: 28, scope: !3065)
!3073 = !DILocation(line: 692, column: 31, scope: !3065)
!3074 = !DILocation(line: 692, column: 44, scope: !3065)
!3075 = !DILocation(line: 692, column: 47, scope: !3065)
!3076 = !DILocation(line: 692, column: 58, scope: !3065)
!3077 = !DILocation(line: 686, column: 13, scope: !3065)
!3078 = !DILocation(line: 693, column: 25, scope: !3065)
!3079 = !DILocation(line: 693, column: 31, scope: !3065)
!3080 = !DILocation(line: 693, column: 13, scope: !3065)
!3081 = !DILocation(line: 694, column: 11, scope: !3065)
!3082 = !DILocation(line: 696, column: 19, scope: !3083)
!3083 = distinct !DILexicalBlock(scope: !3058, file: !1, line: 695, column: 16)
!3084 = !DILocation(line: 702, column: 19, scope: !3083)
!3085 = !DILocation(line: 702, column: 27, scope: !3083)
!3086 = !DILocation(line: 702, column: 30, scope: !3083)
!3087 = !DILocation(line: 702, column: 36, scope: !3083)
!3088 = !DILocation(line: 702, column: 39, scope: !3083)
!3089 = !DILocation(line: 702, column: 52, scope: !3083)
!3090 = !DILocation(line: 702, column: 55, scope: !3083)
!3091 = !DILocation(line: 696, column: 13, scope: !3083)
!3092 = !DILocation(line: 704, column: 9, scope: !3059)
!3093 = !DILocation(line: 706, column: 28, scope: !3041)
!3094 = !DILocation(line: 706, column: 31, scope: !3041)
!3095 = !DILocation(line: 706, column: 45, scope: !3041)
!3096 = !DILocation(line: 706, column: 48, scope: !3041)
!3097 = !DILocation(line: 706, column: 43, scope: !3041)
!3098 = !DILocation(line: 706, column: 15, scope: !3041)
!3099 = !DILocation(line: 707, column: 12, scope: !3100)
!3100 = distinct !DILexicalBlock(scope: !3041, file: !1, line: 707, column: 12)
!3101 = !DILocation(line: 707, column: 18, scope: !3100)
!3102 = !DILocation(line: 707, column: 12, scope: !3041)
!3103 = !DILocation(line: 708, column: 17, scope: !3100)
!3104 = !DILocation(line: 708, column: 11, scope: !3100)
!3105 = !DILocation(line: 710, column: 9, scope: !3041)
!3106 = !DILocation(line: 710, column: 12, scope: !3041)
!3107 = !DILocation(line: 710, column: 19, scope: !3041)
!3108 = !DILocation(line: 711, column: 7, scope: !3041)
!3109 = !DILocation(line: 713, column: 23, scope: !2773)
!3110 = !DILocation(line: 713, column: 7, scope: !2773)
!3111 = !DILocation(line: 713, column: 10, scope: !2773)
!3112 = !DILocation(line: 713, column: 20, scope: !2773)
!3113 = !DILocation(line: 715, column: 35, scope: !2773)
!3114 = !DILocation(line: 715, column: 41, scope: !2773)
!3115 = !DILocation(line: 715, column: 44, scope: !2773)
!3116 = !DILocation(line: 715, column: 7, scope: !2773)
!3117 = !DILocation(line: 717, column: 11, scope: !3118)
!3118 = distinct !DILexicalBlock(scope: !2773, file: !1, line: 717, column: 10)
!3119 = !DILocation(line: 717, column: 14, scope: !3118)
!3120 = !DILocation(line: 717, column: 20, scope: !3118)
!3121 = !DILocation(line: 717, column: 24, scope: !3122)
!3122 = !DILexicalBlockFile(scope: !3118, file: !1, discriminator: 1)
!3123 = !DILocation(line: 717, column: 30, scope: !3122)
!3124 = !DILocation(line: 717, column: 33, scope: !3125)
!3125 = !DILexicalBlockFile(scope: !3118, file: !1, discriminator: 2)
!3126 = !DILocation(line: 717, column: 36, scope: !3125)
!3127 = !DILocation(line: 717, column: 46, scope: !3125)
!3128 = !DILocation(line: 717, column: 49, scope: !3129)
!3129 = !DILexicalBlockFile(scope: !3118, file: !1, discriminator: 3)
!3130 = !DILocation(line: 717, column: 10, scope: !3129)
!3131 = !DILocation(line: 720, column: 12, scope: !3132)
!3132 = distinct !DILexicalBlock(scope: !3133, file: !1, line: 720, column: 12)
!3133 = distinct !DILexicalBlock(scope: !3118, file: !1, line: 717, column: 65)
!3134 = !DILocation(line: 720, column: 15, scope: !3132)
!3135 = !DILocation(line: 720, column: 25, scope: !3132)
!3136 = !DILocation(line: 720, column: 29, scope: !3137)
!3137 = !DILexicalBlockFile(scope: !3132, file: !1, discriminator: 1)
!3138 = !DILocation(line: 720, column: 32, scope: !3137)
!3139 = !DILocation(line: 720, column: 12, scope: !3137)
!3140 = !DILocation(line: 725, column: 14, scope: !3141)
!3141 = distinct !DILexicalBlock(scope: !3142, file: !1, line: 725, column: 14)
!3142 = distinct !DILexicalBlock(scope: !3132, file: !1, line: 720, column: 44)
!3143 = !DILocation(line: 725, column: 17, scope: !3141)
!3144 = !DILocation(line: 725, column: 29, scope: !3141)
!3145 = !DILocation(line: 725, column: 35, scope: !3141)
!3146 = !DILocation(line: 725, column: 50, scope: !3147)
!3147 = !DILexicalBlockFile(scope: !3141, file: !1, discriminator: 1)
!3148 = !DILocation(line: 725, column: 53, scope: !3147)
!3149 = !DILocation(line: 725, column: 64, scope: !3147)
!3150 = !DILocation(line: 725, column: 67, scope: !3147)
!3151 = !DILocation(line: 725, column: 61, scope: !3147)
!3152 = !DILocation(line: 725, column: 14, scope: !3147)
!3153 = !DILocation(line: 726, column: 40, scope: !3141)
!3154 = !DILocation(line: 727, column: 40, scope: !3141)
!3155 = !DILocation(line: 727, column: 46, scope: !3141)
!3156 = !DILocation(line: 727, column: 52, scope: !3141)
!3157 = !DILocation(line: 728, column: 40, scope: !3141)
!3158 = !DILocation(line: 728, column: 43, scope: !3141)
!3159 = !DILocation(line: 726, column: 22, scope: !3141)
!3160 = !DILocation(line: 726, column: 20, scope: !3141)
!3161 = !DILocation(line: 726, column: 13, scope: !3141)
!3162 = !DILocation(line: 730, column: 40, scope: !3141)
!3163 = !DILocation(line: 731, column: 40, scope: !3141)
!3164 = !DILocation(line: 731, column: 46, scope: !3141)
!3165 = !DILocation(line: 731, column: 52, scope: !3141)
!3166 = !DILocation(line: 732, column: 48, scope: !3141)
!3167 = !DILocation(line: 732, column: 51, scope: !3141)
!3168 = !DILocation(line: 730, column: 22, scope: !3141)
!3169 = !DILocation(line: 730, column: 20, scope: !3141)
!3170 = !DILocation(line: 734, column: 14, scope: !3171)
!3171 = distinct !DILexicalBlock(scope: !3142, file: !1, line: 734, column: 14)
!3172 = !DILocation(line: 734, column: 14, scope: !3142)
!3173 = !DILocation(line: 735, column: 20, scope: !3171)
!3174 = !DILocation(line: 735, column: 13, scope: !3171)
!3175 = !DILocation(line: 736, column: 9, scope: !3142)
!3176 = !DILocation(line: 737, column: 12, scope: !3177)
!3177 = distinct !DILexicalBlock(scope: !3133, file: !1, line: 737, column: 12)
!3178 = !DILocation(line: 737, column: 15, scope: !3177)
!3179 = !DILocation(line: 737, column: 25, scope: !3177)
!3180 = !DILocation(line: 737, column: 12, scope: !3133)
!3181 = !DILocation(line: 751, column: 17, scope: !3182)
!3182 = distinct !DILexicalBlock(scope: !3183, file: !1, line: 751, column: 16)
!3183 = distinct !DILexicalBlock(scope: !3177, file: !1, line: 737, column: 42)
!3184 = !DILocation(line: 751, column: 20, scope: !3182)
!3185 = !DILocation(line: 751, column: 16, scope: !3183)
!3186 = !DILocation(line: 759, column: 44, scope: !3187)
!3187 = distinct !DILexicalBlock(scope: !3182, file: !1, line: 751, column: 32)
!3188 = !DILocation(line: 759, column: 68, scope: !3187)
!3189 = !DILocation(line: 759, column: 71, scope: !3187)
!3190 = !DILocation(line: 760, column: 44, scope: !3187)
!3191 = !DILocation(line: 759, column: 26, scope: !3187)
!3192 = !DILocation(line: 759, column: 24, scope: !3187)
!3193 = !DILocation(line: 761, column: 13, scope: !3187)
!3194 = !DILocation(line: 785, column: 9, scope: !3183)
!3195 = !DILocation(line: 786, column: 9, scope: !3133)
!3196 = !DILocation(line: 786, column: 12, scope: !3133)
!3197 = !DILocation(line: 786, column: 22, scope: !3133)
!3198 = !DILocation(line: 788, column: 12, scope: !3199)
!3199 = distinct !DILexicalBlock(scope: !3133, file: !1, line: 788, column: 12)
!3200 = !DILocation(line: 788, column: 12, scope: !3133)
!3201 = !DILocation(line: 789, column: 18, scope: !3199)
!3202 = !DILocation(line: 789, column: 11, scope: !3199)
!3203 = !DILocation(line: 790, column: 7, scope: !3133)
!3204 = !DILocation(line: 792, column: 5, scope: !2773)
!3205 = !DILocation(line: 794, column: 8, scope: !3206)
!3206 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 794, column: 8)
!3207 = !DILocation(line: 794, column: 14, scope: !3206)
!3208 = !DILocation(line: 794, column: 23, scope: !3206)
!3209 = !DILocation(line: 794, column: 33, scope: !3206)
!3210 = !DILocation(line: 795, column: 9, scope: !3206)
!3211 = !DILocation(line: 795, column: 16, scope: !3206)
!3212 = !DILocation(line: 795, column: 20, scope: !3206)
!3213 = !DILocation(line: 795, column: 24, scope: !3214)
!3214 = !DILexicalBlockFile(scope: !3206, file: !1, discriminator: 1)
!3215 = !DILocation(line: 795, column: 30, scope: !3214)
!3216 = !DILocation(line: 795, column: 35, scope: !3214)
!3217 = !DILocation(line: 794, column: 8, scope: !2521)
!3218 = !DILocation(line: 797, column: 17, scope: !3219)
!3219 = distinct !DILexicalBlock(scope: !3206, file: !1, line: 795, column: 56)
!3220 = !DILocation(line: 797, column: 7, scope: !3219)
!3221 = !DILocation(line: 797, column: 10, scope: !3219)
!3222 = !DILocation(line: 797, column: 14, scope: !3219)
!3223 = !DILocation(line: 798, column: 24, scope: !3219)
!3224 = !DILocation(line: 798, column: 13, scope: !3219)
!3225 = !DILocation(line: 800, column: 16, scope: !3219)
!3226 = !DILocation(line: 800, column: 22, scope: !3219)
!3227 = !DILocation(line: 800, column: 31, scope: !3219)
!3228 = !DILocation(line: 800, column: 41, scope: !3219)
!3229 = !DILocation(line: 800, column: 47, scope: !3219)
!3230 = !DILocation(line: 800, column: 14, scope: !3219)
!3231 = !DILocation(line: 801, column: 10, scope: !3232)
!3232 = distinct !DILexicalBlock(scope: !3219, file: !1, line: 801, column: 10)
!3233 = !DILocation(line: 801, column: 10, scope: !3219)
!3234 = !DILocation(line: 802, column: 16, scope: !3232)
!3235 = !DILocation(line: 802, column: 9, scope: !3232)
!3236 = !DILocation(line: 804, column: 10, scope: !3237)
!3237 = distinct !DILexicalBlock(scope: !3219, file: !1, line: 804, column: 10)
!3238 = !DILocation(line: 804, column: 10, scope: !3219)
!3239 = !DILocation(line: 805, column: 9, scope: !3237)
!3240 = !DILocation(line: 805, column: 12, scope: !3237)
!3241 = !DILocation(line: 805, column: 19, scope: !3237)
!3242 = !DILocation(line: 806, column: 7, scope: !3219)
!3243 = !DILocation(line: 809, column: 8, scope: !3244)
!3244 = distinct !DILexicalBlock(scope: !2512, file: !1, line: 809, column: 8)
!3245 = !DILocation(line: 809, column: 8, scope: !2512)
!3246 = !DILocation(line: 812, column: 7, scope: !3247)
!3247 = distinct !DILexicalBlock(scope: !3244, file: !1, line: 809, column: 23)
!3248 = !DILocation(line: 812, column: 10, scope: !3247)
!3249 = !DILocation(line: 812, column: 17, scope: !3247)
!3250 = !DILocation(line: 813, column: 5, scope: !3247)
!3251 = !DILocation(line: 815, column: 3, scope: !2512)
!3252 = !DILocation(line: 815, column: 24, scope: !3253)
!3253 = !DILexicalBlockFile(scope: !1795, file: !1, discriminator: 1)
!3254 = !DILocation(line: 815, column: 11, scope: !3253)
!3255 = !DILocation(line: 815, column: 30, scope: !3253)
!3256 = !DILocation(line: 815, column: 41, scope: !3257)
!3257 = !DILexicalBlockFile(scope: !1795, file: !1, discriminator: 2)
!3258 = !DILocation(line: 815, column: 30, scope: !3257)
!3259 = !DILocation(line: 815, column: 3, scope: !2525)
!3260 = !DILocation(line: 817, column: 6, scope: !3261)
!3261 = distinct !DILexicalBlock(scope: !1795, file: !1, line: 817, column: 6)
!3262 = !DILocation(line: 817, column: 15, scope: !3261)
!3263 = !DILocation(line: 817, column: 6, scope: !1795)
!3264 = !DILocation(line: 819, column: 5, scope: !3265)
!3265 = distinct !DILexicalBlock(scope: !3261, file: !1, line: 817, column: 21)
!3266 = !DILocation(line: 819, column: 11, scope: !3265)
!3267 = !DILocation(line: 819, column: 24, scope: !3265)
!3268 = !DILocation(line: 820, column: 6, scope: !3265)
!3269 = !DILocation(line: 820, column: 15, scope: !3265)
!3270 = !DILocation(line: 821, column: 3, scope: !3265)
!3271 = !DILocation(line: 823, column: 8, scope: !3272)
!3272 = distinct !DILexicalBlock(scope: !1795, file: !1, line: 823, column: 6)
!3273 = !DILocation(line: 823, column: 11, scope: !3272)
!3274 = !DILocation(line: 823, column: 18, scope: !3272)
!3275 = !DILocation(line: 823, column: 43, scope: !3272)
!3276 = !DILocation(line: 823, column: 57, scope: !3272)
!3277 = !DILocation(line: 824, column: 6, scope: !3272)
!3278 = !DILocation(line: 824, column: 12, scope: !3272)
!3279 = !DILocation(line: 824, column: 17, scope: !3272)
!3280 = !DILocation(line: 823, column: 6, scope: !3253)
!3281 = !DILocation(line: 828, column: 11, scope: !3282)
!3282 = distinct !DILexicalBlock(scope: !3272, file: !1, line: 824, column: 24)
!3283 = !DILocation(line: 828, column: 5, scope: !3282)
!3284 = !DILocation(line: 829, column: 5, scope: !3282)
!3285 = !DILocation(line: 829, column: 8, scope: !3282)
!3286 = !DILocation(line: 829, column: 15, scope: !3282)
!3287 = !DILocation(line: 830, column: 3, scope: !3282)
!3288 = !DILocation(line: 832, column: 3, scope: !1795)
!3289 = !DILocation(line: 833, column: 1, scope: !1795)
!3290 = !DILocalVariable(name: "data", arg: 1, scope: !1805, file: !1, line: 854, type: !544)
!3291 = !DILocation(line: 854, column: 52, scope: !1805)
!3292 = !DILocalVariable(name: "conn", arg: 2, scope: !1805, file: !1, line: 855, type: !550)
!3293 = !DILocation(line: 855, column: 54, scope: !1805)
!3294 = !DILocalVariable(name: "k", arg: 3, scope: !1805, file: !1, line: 856, type: !1798)
!3295 = !DILocation(line: 856, column: 56, scope: !1805)
!3296 = !DILocalVariable(name: "didwhat", arg: 4, scope: !1805, file: !1, line: 857, type: !1434)
!3297 = !DILocation(line: 857, column: 39, scope: !1805)
!3298 = !DILocalVariable(name: "i", scope: !1805, file: !1, line: 859, type: !256)
!3299 = !DILocation(line: 859, column: 11, scope: !1805)
!3300 = !DILocalVariable(name: "si", scope: !1805, file: !1, line: 859, type: !256)
!3301 = !DILocation(line: 859, column: 14, scope: !1805)
!3302 = !DILocalVariable(name: "bytes_written", scope: !1805, file: !1, line: 860, type: !256)
!3303 = !DILocation(line: 860, column: 11, scope: !1805)
!3304 = !DILocalVariable(name: "result", scope: !1805, file: !1, line: 861, type: !554)
!3305 = !DILocation(line: 861, column: 12, scope: !1805)
!3306 = !DILocalVariable(name: "nread", scope: !1805, file: !1, line: 862, type: !256)
!3307 = !DILocation(line: 862, column: 11, scope: !1805)
!3308 = !DILocalVariable(name: "sending_http_headers", scope: !1805, file: !1, line: 863, type: !211)
!3309 = !DILocation(line: 863, column: 8, scope: !1805)
!3310 = !DILocation(line: 865, column: 7, scope: !3311)
!3311 = distinct !DILexicalBlock(scope: !1805, file: !1, line: 865, column: 6)
!3312 = !DILocation(line: 865, column: 10, scope: !3311)
!3313 = !DILocation(line: 865, column: 20, scope: !3311)
!3314 = !DILocation(line: 865, column: 26, scope: !3311)
!3315 = !DILocation(line: 865, column: 30, scope: !3316)
!3316 = !DILexicalBlockFile(scope: !3311, file: !1, discriminator: 1)
!3317 = !DILocation(line: 865, column: 33, scope: !3316)
!3318 = !DILocation(line: 865, column: 48, scope: !3316)
!3319 = !DILocation(line: 865, column: 6, scope: !3316)
!3320 = !DILocation(line: 866, column: 19, scope: !3311)
!3321 = !DILocation(line: 866, column: 5, scope: !3311)
!3322 = !DILocation(line: 868, column: 4, scope: !1805)
!3323 = !DILocation(line: 868, column: 12, scope: !1805)
!3324 = !DILocation(line: 870, column: 3, scope: !1805)
!3325 = !DILocation(line: 874, column: 13, scope: !3326)
!3326 = distinct !DILexicalBlock(scope: !3327, file: !1, line: 874, column: 8)
!3327 = distinct !DILexicalBlock(scope: !1805, file: !1, line: 870, column: 6)
!3328 = !DILocation(line: 874, column: 19, scope: !3326)
!3329 = !DILocation(line: 874, column: 23, scope: !3326)
!3330 = !DILocation(line: 874, column: 10, scope: !3326)
!3331 = !DILocation(line: 874, column: 8, scope: !3327)
!3332 = !DILocation(line: 876, column: 35, scope: !3333)
!3333 = distinct !DILexicalBlock(scope: !3326, file: !1, line: 874, column: 39)
!3334 = !DILocation(line: 876, column: 38, scope: !3333)
!3335 = !DILocation(line: 876, column: 7, scope: !3333)
!3336 = !DILocation(line: 876, column: 13, scope: !3333)
!3337 = !DILocation(line: 876, column: 17, scope: !3333)
!3338 = !DILocation(line: 876, column: 33, scope: !3333)
!3339 = !DILocation(line: 878, column: 11, scope: !3340)
!3340 = distinct !DILexicalBlock(scope: !3333, file: !1, line: 878, column: 10)
!3341 = !DILocation(line: 878, column: 14, scope: !3340)
!3342 = !DILocation(line: 878, column: 10, scope: !3333)
!3343 = !DILocalVariable(name: "fillcount", scope: !3344, file: !1, line: 881, type: !177)
!3344 = distinct !DILexicalBlock(scope: !3340, file: !1, line: 878, column: 27)
!3345 = !DILocation(line: 881, column: 13, scope: !3344)
!3346 = !DILocalVariable(name: "http", scope: !3344, file: !1, line: 882, type: !3347)
!3347 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1715, size: 64, align: 64)
!3348 = !DILocation(line: 882, column: 22, scope: !3344)
!3349 = !DILocation(line: 882, column: 29, scope: !3344)
!3350 = !DILocation(line: 882, column: 35, scope: !3344)
!3351 = !DILocation(line: 882, column: 39, scope: !3344)
!3352 = !DILocation(line: 884, column: 13, scope: !3353)
!3353 = distinct !DILexicalBlock(scope: !3344, file: !1, line: 884, column: 12)
!3354 = !DILocation(line: 884, column: 16, scope: !3353)
!3355 = !DILocation(line: 884, column: 23, scope: !3353)
!3356 = !DILocation(line: 884, column: 50, scope: !3353)
!3357 = !DILocation(line: 885, column: 13, scope: !3353)
!3358 = !DILocation(line: 885, column: 19, scope: !3353)
!3359 = !DILocation(line: 885, column: 27, scope: !3353)
!3360 = !DILocation(line: 884, column: 12, scope: !3361)
!3361 = !DILexicalBlockFile(scope: !3344, file: !1, discriminator: 1)
!3362 = !DILocation(line: 889, column: 11, scope: !3363)
!3363 = distinct !DILexicalBlock(scope: !3353, file: !1, line: 885, column: 46)
!3364 = !DILocation(line: 889, column: 14, scope: !3363)
!3365 = !DILocation(line: 889, column: 21, scope: !3363)
!3366 = !DILocation(line: 890, column: 11, scope: !3363)
!3367 = !DILocation(line: 890, column: 14, scope: !3363)
!3368 = !DILocation(line: 890, column: 21, scope: !3363)
!3369 = !DILocation(line: 891, column: 11, scope: !3363)
!3370 = !DILocation(line: 891, column: 14, scope: !3363)
!3371 = !DILocation(line: 891, column: 25, scope: !3363)
!3372 = !DILocation(line: 891, column: 25, scope: !3373)
!3373 = !DILexicalBlockFile(scope: !3363, file: !1, discriminator: 1)
!3374 = !DILocation(line: 892, column: 12, scope: !3363)
!3375 = !DILocation(line: 892, column: 20, scope: !3363)
!3376 = !DILocation(line: 895, column: 23, scope: !3363)
!3377 = !DILocation(line: 895, column: 29, scope: !3363)
!3378 = !DILocation(line: 895, column: 35, scope: !3363)
!3379 = !DILocation(line: 895, column: 39, scope: !3363)
!3380 = !DILocation(line: 895, column: 11, scope: !3363)
!3381 = !DILocation(line: 896, column: 11, scope: !3363)
!3382 = !DILocation(line: 899, column: 12, scope: !3383)
!3383 = distinct !DILexicalBlock(scope: !3344, file: !1, line: 899, column: 12)
!3384 = !DILocation(line: 899, column: 18, scope: !3383)
!3385 = !DILocation(line: 899, column: 27, scope: !3383)
!3386 = !DILocation(line: 899, column: 35, scope: !3383)
!3387 = !DILocation(line: 899, column: 12, scope: !3344)
!3388 = !DILocation(line: 900, column: 14, scope: !3389)
!3389 = distinct !DILexicalBlock(scope: !3390, file: !1, line: 900, column: 14)
!3390 = distinct !DILexicalBlock(scope: !3383, file: !1, line: 899, column: 72)
!3391 = !DILocation(line: 900, column: 20, scope: !3389)
!3392 = !DILocation(line: 900, column: 28, scope: !3389)
!3393 = !DILocation(line: 900, column: 14, scope: !3390)
!3394 = !DILocation(line: 903, column: 34, scope: !3389)
!3395 = !DILocation(line: 903, column: 13, scope: !3389)
!3396 = !DILocation(line: 905, column: 34, scope: !3389)
!3397 = !DILocation(line: 906, column: 9, scope: !3390)
!3398 = !DILocation(line: 908, column: 38, scope: !3344)
!3399 = !DILocation(line: 908, column: 18, scope: !3344)
!3400 = !DILocation(line: 908, column: 16, scope: !3344)
!3401 = !DILocation(line: 909, column: 12, scope: !3402)
!3402 = distinct !DILexicalBlock(scope: !3344, file: !1, line: 909, column: 12)
!3403 = !DILocation(line: 909, column: 12, scope: !3344)
!3404 = !DILocation(line: 910, column: 18, scope: !3402)
!3405 = !DILocation(line: 910, column: 11, scope: !3402)
!3406 = !DILocation(line: 912, column: 26, scope: !3344)
!3407 = !DILocation(line: 912, column: 17, scope: !3344)
!3408 = !DILocation(line: 912, column: 15, scope: !3344)
!3409 = !DILocation(line: 913, column: 7, scope: !3344)
!3410 = !DILocation(line: 915, column: 15, scope: !3340)
!3411 = !DILocation(line: 917, column: 11, scope: !3412)
!3412 = distinct !DILexicalBlock(scope: !3333, file: !1, line: 917, column: 10)
!3413 = !DILocation(line: 917, column: 17, scope: !3412)
!3414 = !DILocation(line: 917, column: 21, scope: !3415)
!3415 = !DILexicalBlockFile(scope: !3412, file: !1, discriminator: 1)
!3416 = !DILocation(line: 917, column: 24, scope: !3415)
!3417 = !DILocation(line: 917, column: 31, scope: !3415)
!3418 = !DILocation(line: 917, column: 10, scope: !3415)
!3419 = !DILocation(line: 919, column: 9, scope: !3420)
!3420 = distinct !DILexicalBlock(scope: !3412, file: !1, line: 917, column: 51)
!3421 = !DILocation(line: 921, column: 10, scope: !3422)
!3422 = distinct !DILexicalBlock(scope: !3333, file: !1, line: 921, column: 10)
!3423 = !DILocation(line: 921, column: 15, scope: !3422)
!3424 = !DILocation(line: 921, column: 10, scope: !3333)
!3425 = !DILocation(line: 922, column: 31, scope: !3426)
!3426 = distinct !DILexicalBlock(scope: !3422, file: !1, line: 921, column: 20)
!3427 = !DILocation(line: 922, column: 37, scope: !3426)
!3428 = !DILocation(line: 922, column: 18, scope: !3426)
!3429 = !DILocation(line: 922, column: 16, scope: !3426)
!3430 = !DILocation(line: 923, column: 12, scope: !3431)
!3431 = distinct !DILexicalBlock(scope: !3426, file: !1, line: 923, column: 12)
!3432 = !DILocation(line: 923, column: 12, scope: !3426)
!3433 = !DILocation(line: 924, column: 18, scope: !3431)
!3434 = !DILocation(line: 924, column: 11, scope: !3431)
!3435 = !DILocation(line: 925, column: 9, scope: !3426)
!3436 = !DILocation(line: 929, column: 34, scope: !3333)
!3437 = !DILocation(line: 929, column: 7, scope: !3333)
!3438 = !DILocation(line: 929, column: 13, scope: !3333)
!3439 = !DILocation(line: 929, column: 17, scope: !3333)
!3440 = !DILocation(line: 929, column: 32, scope: !3333)
!3441 = !DILocation(line: 932, column: 12, scope: !3442)
!3442 = distinct !DILexicalBlock(scope: !3333, file: !1, line: 932, column: 10)
!3443 = !DILocation(line: 932, column: 34, scope: !3442)
!3444 = !DILocation(line: 935, column: 11, scope: !3442)
!3445 = !DILocation(line: 935, column: 17, scope: !3442)
!3446 = !DILocation(line: 935, column: 21, scope: !3442)
!3447 = !DILocation(line: 935, column: 35, scope: !3442)
!3448 = !DILocation(line: 937, column: 11, scope: !3442)
!3449 = !DILocation(line: 937, column: 17, scope: !3442)
!3450 = !DILocation(line: 937, column: 21, scope: !3442)
!3451 = !DILocation(line: 932, column: 10, scope: !3452)
!3452 = !DILexicalBlockFile(scope: !3333, file: !1, discriminator: 1)
!3453 = !DILocation(line: 939, column: 13, scope: !3454)
!3454 = distinct !DILexicalBlock(scope: !3455, file: !1, line: 939, column: 12)
!3455 = distinct !DILexicalBlock(scope: !3442, file: !1, line: 937, column: 29)
!3456 = !DILocation(line: 939, column: 19, scope: !3454)
!3457 = !DILocation(line: 939, column: 25, scope: !3454)
!3458 = !DILocation(line: 939, column: 12, scope: !3455)
!3459 = !DILocation(line: 940, column: 33, scope: !3460)
!3460 = distinct !DILexicalBlock(scope: !3454, file: !1, line: 939, column: 34)
!3461 = !DILocation(line: 940, column: 11, scope: !3460)
!3462 = !DILocation(line: 940, column: 17, scope: !3460)
!3463 = !DILocation(line: 940, column: 23, scope: !3460)
!3464 = !DILocation(line: 940, column: 31, scope: !3460)
!3465 = !DILocation(line: 941, column: 15, scope: !3466)
!3466 = distinct !DILexicalBlock(scope: !3460, file: !1, line: 941, column: 14)
!3467 = !DILocation(line: 941, column: 21, scope: !3466)
!3468 = !DILocation(line: 941, column: 27, scope: !3466)
!3469 = !DILocation(line: 941, column: 14, scope: !3460)
!3470 = !DILocation(line: 942, column: 19, scope: !3471)
!3471 = distinct !DILexicalBlock(scope: !3466, file: !1, line: 941, column: 36)
!3472 = !DILocation(line: 942, column: 13, scope: !3471)
!3473 = !DILocation(line: 944, column: 13, scope: !3471)
!3474 = !DILocation(line: 946, column: 9, scope: !3460)
!3475 = !DILocation(line: 954, column: 15, scope: !3476)
!3476 = distinct !DILexicalBlock(scope: !3455, file: !1, line: 954, column: 9)
!3477 = !DILocation(line: 954, column: 23, scope: !3476)
!3478 = !DILocation(line: 954, column: 13, scope: !3476)
!3479 = !DILocation(line: 954, column: 28, scope: !3480)
!3480 = !DILexicalBlockFile(scope: !3481, file: !1, discriminator: 1)
!3481 = distinct !DILexicalBlock(scope: !3476, file: !1, line: 954, column: 9)
!3482 = !DILocation(line: 954, column: 32, scope: !3480)
!3483 = !DILocation(line: 954, column: 30, scope: !3480)
!3484 = !DILocation(line: 954, column: 9, scope: !3480)
!3485 = !DILocation(line: 955, column: 40, scope: !3486)
!3486 = distinct !DILexicalBlock(scope: !3487, file: !1, line: 955, column: 14)
!3487 = distinct !DILexicalBlock(scope: !3481, file: !1, line: 954, column: 50)
!3488 = !DILocation(line: 955, column: 14, scope: !3486)
!3489 = !DILocation(line: 955, column: 20, scope: !3486)
!3490 = !DILocation(line: 955, column: 24, scope: !3486)
!3491 = !DILocation(line: 955, column: 43, scope: !3486)
!3492 = !DILocation(line: 955, column: 14, scope: !3487)
!3493 = !DILocation(line: 956, column: 35, scope: !3494)
!3494 = distinct !DILexicalBlock(scope: !3486, file: !1, line: 955, column: 52)
!3495 = !DILocation(line: 956, column: 13, scope: !3494)
!3496 = !DILocation(line: 956, column: 19, scope: !3494)
!3497 = !DILocation(line: 956, column: 25, scope: !3494)
!3498 = !DILocation(line: 956, column: 39, scope: !3494)
!3499 = !DILocation(line: 957, column: 33, scope: !3494)
!3500 = !DILocation(line: 957, column: 13, scope: !3494)
!3501 = !DILocation(line: 957, column: 19, scope: !3494)
!3502 = !DILocation(line: 957, column: 25, scope: !3494)
!3503 = !DILocation(line: 957, column: 37, scope: !3494)
!3504 = !DILocation(line: 958, column: 17, scope: !3505)
!3505 = distinct !DILexicalBlock(scope: !3494, file: !1, line: 958, column: 16)
!3506 = !DILocation(line: 958, column: 23, scope: !3505)
!3507 = !DILocation(line: 958, column: 27, scope: !3505)
!3508 = !DILocation(line: 958, column: 16, scope: !3494)
!3509 = !DILocation(line: 961, column: 18, scope: !3510)
!3510 = distinct !DILexicalBlock(scope: !3511, file: !1, line: 961, column: 18)
!3511 = distinct !DILexicalBlock(scope: !3505, file: !1, line: 958, column: 33)
!3512 = !DILocation(line: 961, column: 24, scope: !3510)
!3513 = !DILocation(line: 961, column: 30, scope: !3510)
!3514 = !DILocation(line: 961, column: 41, scope: !3510)
!3515 = !DILocation(line: 961, column: 18, scope: !3511)
!3516 = !DILocation(line: 962, column: 17, scope: !3510)
!3517 = !DILocation(line: 962, column: 23, scope: !3510)
!3518 = !DILocation(line: 962, column: 29, scope: !3510)
!3519 = !DILocation(line: 962, column: 39, scope: !3510)
!3520 = !DILocation(line: 963, column: 13, scope: !3511)
!3521 = !DILocation(line: 964, column: 11, scope: !3494)
!3522 = !DILocation(line: 966, column: 65, scope: !3486)
!3523 = !DILocation(line: 966, column: 39, scope: !3486)
!3524 = !DILocation(line: 966, column: 45, scope: !3486)
!3525 = !DILocation(line: 966, column: 49, scope: !3486)
!3526 = !DILocation(line: 966, column: 33, scope: !3486)
!3527 = !DILocation(line: 966, column: 13, scope: !3486)
!3528 = !DILocation(line: 966, column: 19, scope: !3486)
!3529 = !DILocation(line: 966, column: 25, scope: !3486)
!3530 = !DILocation(line: 966, column: 37, scope: !3486)
!3531 = !DILocation(line: 967, column: 9, scope: !3487)
!3532 = !DILocation(line: 954, column: 40, scope: !3533)
!3533 = !DILexicalBlockFile(scope: !3481, file: !1, discriminator: 2)
!3534 = !DILocation(line: 954, column: 46, scope: !3533)
!3535 = !DILocation(line: 954, column: 9, scope: !3533)
!3536 = !DILocation(line: 969, column: 12, scope: !3537)
!3537 = distinct !DILexicalBlock(scope: !3455, file: !1, line: 969, column: 12)
!3538 = !DILocation(line: 969, column: 18, scope: !3537)
!3539 = !DILocation(line: 969, column: 15, scope: !3537)
!3540 = !DILocation(line: 969, column: 12, scope: !3455)
!3541 = !DILocation(line: 972, column: 19, scope: !3542)
!3542 = distinct !DILexicalBlock(scope: !3537, file: !1, line: 969, column: 25)
!3543 = !DILocation(line: 972, column: 17, scope: !3542)
!3544 = !DILocation(line: 975, column: 39, scope: !3542)
!3545 = !DILocation(line: 975, column: 45, scope: !3542)
!3546 = !DILocation(line: 975, column: 51, scope: !3542)
!3547 = !DILocation(line: 975, column: 11, scope: !3542)
!3548 = !DILocation(line: 975, column: 17, scope: !3542)
!3549 = !DILocation(line: 975, column: 21, scope: !3542)
!3550 = !DILocation(line: 975, column: 37, scope: !3542)
!3551 = !DILocation(line: 978, column: 38, scope: !3542)
!3552 = !DILocation(line: 978, column: 11, scope: !3542)
!3553 = !DILocation(line: 978, column: 17, scope: !3542)
!3554 = !DILocation(line: 978, column: 21, scope: !3542)
!3555 = !DILocation(line: 978, column: 36, scope: !3542)
!3556 = !DILocation(line: 979, column: 9, scope: !3542)
!3557 = !DILocation(line: 980, column: 7, scope: !3455)
!3558 = !DILocation(line: 989, column: 5, scope: !3333)
!3559 = !DILocation(line: 996, column: 25, scope: !3327)
!3560 = !DILocation(line: 997, column: 25, scope: !3327)
!3561 = !DILocation(line: 997, column: 31, scope: !3327)
!3562 = !DILocation(line: 998, column: 25, scope: !3327)
!3563 = !DILocation(line: 998, column: 31, scope: !3327)
!3564 = !DILocation(line: 998, column: 35, scope: !3327)
!3565 = !DILocation(line: 999, column: 25, scope: !3327)
!3566 = !DILocation(line: 999, column: 31, scope: !3327)
!3567 = !DILocation(line: 999, column: 35, scope: !3327)
!3568 = !DILocation(line: 996, column: 14, scope: !3327)
!3569 = !DILocation(line: 996, column: 12, scope: !3327)
!3570 = !DILocation(line: 1002, column: 8, scope: !3571)
!3571 = distinct !DILexicalBlock(scope: !3327, file: !1, line: 1002, column: 8)
!3572 = !DILocation(line: 1002, column: 8, scope: !3327)
!3573 = !DILocation(line: 1003, column: 14, scope: !3571)
!3574 = !DILocation(line: 1003, column: 7, scope: !3571)
!3575 = !DILocation(line: 1005, column: 8, scope: !3576)
!3576 = distinct !DILexicalBlock(scope: !3327, file: !1, line: 1005, column: 8)
!3577 = !DILocation(line: 1005, column: 14, scope: !3576)
!3578 = !DILocation(line: 1005, column: 18, scope: !3576)
!3579 = !DILocation(line: 1005, column: 8, scope: !3327)
!3580 = !DILocation(line: 1007, column: 18, scope: !3576)
!3581 = !DILocation(line: 1007, column: 43, scope: !3576)
!3582 = !DILocation(line: 1007, column: 49, scope: !3576)
!3583 = !DILocation(line: 1007, column: 53, scope: !3576)
!3584 = !DILocation(line: 1008, column: 26, scope: !3576)
!3585 = !DILocation(line: 1008, column: 41, scope: !3576)
!3586 = !DILocation(line: 1007, column: 7, scope: !3576)
!3587 = !DILocation(line: 1010, column: 26, scope: !3327)
!3588 = !DILocation(line: 1010, column: 5, scope: !3327)
!3589 = !DILocation(line: 1010, column: 8, scope: !3327)
!3590 = !DILocation(line: 1010, column: 23, scope: !3327)
!3591 = !DILocation(line: 1012, column: 8, scope: !3592)
!3592 = distinct !DILexicalBlock(scope: !3327, file: !1, line: 1012, column: 8)
!3593 = !DILocation(line: 1012, column: 11, scope: !3592)
!3594 = !DILocation(line: 1012, column: 29, scope: !3592)
!3595 = !DILocation(line: 1012, column: 35, scope: !3592)
!3596 = !DILocation(line: 1012, column: 41, scope: !3592)
!3597 = !DILocation(line: 1012, column: 26, scope: !3592)
!3598 = !DILocation(line: 1012, column: 8, scope: !3327)
!3599 = !DILocation(line: 1014, column: 7, scope: !3600)
!3600 = distinct !DILexicalBlock(scope: !3592, file: !1, line: 1012, column: 53)
!3601 = !DILocation(line: 1014, column: 10, scope: !3600)
!3602 = !DILocation(line: 1014, column: 22, scope: !3600)
!3603 = !DILocation(line: 1015, column: 13, scope: !3600)
!3604 = !DILocation(line: 1015, column: 7, scope: !3600)
!3605 = !DILocation(line: 1016, column: 5, scope: !3600)
!3606 = !DILocation(line: 1018, column: 8, scope: !3607)
!3607 = distinct !DILexicalBlock(scope: !3327, file: !1, line: 1018, column: 8)
!3608 = !DILocation(line: 1018, column: 14, scope: !3607)
!3609 = !DILocation(line: 1018, column: 18, scope: !3607)
!3610 = !DILocation(line: 1018, column: 36, scope: !3607)
!3611 = !DILocation(line: 1018, column: 33, scope: !3607)
!3612 = !DILocation(line: 1018, column: 8, scope: !3327)
!3613 = !DILocation(line: 1022, column: 35, scope: !3614)
!3614 = distinct !DILexicalBlock(scope: !3607, file: !1, line: 1018, column: 51)
!3615 = !DILocation(line: 1022, column: 7, scope: !3614)
!3616 = !DILocation(line: 1022, column: 13, scope: !3614)
!3617 = !DILocation(line: 1022, column: 17, scope: !3614)
!3618 = !DILocation(line: 1022, column: 32, scope: !3614)
!3619 = !DILocation(line: 1026, column: 36, scope: !3614)
!3620 = !DILocation(line: 1026, column: 7, scope: !3614)
!3621 = !DILocation(line: 1026, column: 13, scope: !3614)
!3622 = !DILocation(line: 1026, column: 17, scope: !3614)
!3623 = !DILocation(line: 1026, column: 33, scope: !3614)
!3624 = !DILocation(line: 1027, column: 5, scope: !3614)
!3625 = !DILocation(line: 1030, column: 35, scope: !3626)
!3626 = distinct !DILexicalBlock(scope: !3607, file: !1, line: 1028, column: 10)
!3627 = !DILocation(line: 1030, column: 38, scope: !3626)
!3628 = !DILocation(line: 1030, column: 7, scope: !3626)
!3629 = !DILocation(line: 1030, column: 13, scope: !3626)
!3630 = !DILocation(line: 1030, column: 17, scope: !3626)
!3631 = !DILocation(line: 1030, column: 33, scope: !3626)
!3632 = !DILocation(line: 1031, column: 7, scope: !3626)
!3633 = !DILocation(line: 1031, column: 13, scope: !3626)
!3634 = !DILocation(line: 1031, column: 17, scope: !3626)
!3635 = !DILocation(line: 1031, column: 32, scope: !3626)
!3636 = !DILocation(line: 1033, column: 10, scope: !3637)
!3637 = distinct !DILexicalBlock(scope: !3626, file: !1, line: 1033, column: 10)
!3638 = !DILocation(line: 1033, column: 13, scope: !3637)
!3639 = !DILocation(line: 1033, column: 10, scope: !3626)
!3640 = !DILocation(line: 1034, column: 31, scope: !3641)
!3641 = distinct !DILexicalBlock(scope: !3637, file: !1, line: 1033, column: 26)
!3642 = !DILocation(line: 1034, column: 37, scope: !3641)
!3643 = !DILocation(line: 1034, column: 18, scope: !3641)
!3644 = !DILocation(line: 1034, column: 16, scope: !3641)
!3645 = !DILocation(line: 1035, column: 12, scope: !3646)
!3646 = distinct !DILexicalBlock(scope: !3641, file: !1, line: 1035, column: 12)
!3647 = !DILocation(line: 1035, column: 12, scope: !3641)
!3648 = !DILocation(line: 1036, column: 18, scope: !3646)
!3649 = !DILocation(line: 1036, column: 11, scope: !3646)
!3650 = !DILocation(line: 1037, column: 7, scope: !3641)
!3651 = !DILocation(line: 1040, column: 31, scope: !3327)
!3652 = !DILocation(line: 1040, column: 37, scope: !3327)
!3653 = !DILocation(line: 1040, column: 40, scope: !3327)
!3654 = !DILocation(line: 1040, column: 5, scope: !3327)
!3655 = !DILocation(line: 1042, column: 3, scope: !3327)
!3656 = !DILocation(line: 1044, column: 3, scope: !1805)
!3657 = !DILocation(line: 1045, column: 1, scope: !1805)
!3658 = !DILocalVariable(name: "conn", arg: 1, scope: !1777, file: !1, line: 1228, type: !1449)
!3659 = !DILocation(line: 1228, column: 51, scope: !1777)
!3660 = !DILocalVariable(name: "sock", arg: 2, scope: !1777, file: !1, line: 1229, type: !1442)
!3661 = !DILocation(line: 1229, column: 40, scope: !1777)
!3662 = !DILocalVariable(name: "numsocks", arg: 3, scope: !1777, file: !1, line: 1231, type: !177)
!3663 = !DILocation(line: 1231, column: 29, scope: !1777)
!3664 = !DILocalVariable(name: "data", scope: !1777, file: !1, line: 1233, type: !3665)
!3665 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !3666, size: 64, align: 64)
!3666 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !545)
!3667 = !DILocation(line: 1233, column: 27, scope: !1777)
!3668 = !DILocation(line: 1233, column: 34, scope: !1777)
!3669 = !DILocation(line: 1233, column: 40, scope: !1777)
!3670 = !DILocalVariable(name: "bitmap", scope: !1777, file: !1, line: 1234, type: !177)
!3671 = !DILocation(line: 1234, column: 7, scope: !1777)
!3672 = !DILocalVariable(name: "sockindex", scope: !1777, file: !1, line: 1235, type: !782)
!3673 = !DILocation(line: 1235, column: 12, scope: !1777)
!3674 = !DILocation(line: 1237, column: 6, scope: !3675)
!3675 = distinct !DILexicalBlock(scope: !1777, file: !1, line: 1237, column: 6)
!3676 = !DILocation(line: 1237, column: 12, scope: !3675)
!3677 = !DILocation(line: 1237, column: 21, scope: !3675)
!3678 = !DILocation(line: 1237, column: 6, scope: !1777)
!3679 = !DILocation(line: 1238, column: 12, scope: !3675)
!3680 = !DILocation(line: 1238, column: 18, scope: !3675)
!3681 = !DILocation(line: 1238, column: 27, scope: !3675)
!3682 = !DILocation(line: 1238, column: 43, scope: !3675)
!3683 = !DILocation(line: 1238, column: 49, scope: !3675)
!3684 = !DILocation(line: 1238, column: 55, scope: !3675)
!3685 = !DILocation(line: 1238, column: 5, scope: !3675)
!3686 = !DILocation(line: 1240, column: 6, scope: !3687)
!3687 = distinct !DILexicalBlock(scope: !1777, file: !1, line: 1240, column: 6)
!3688 = !DILocation(line: 1240, column: 15, scope: !3687)
!3689 = !DILocation(line: 1240, column: 6, scope: !1777)
!3690 = !DILocation(line: 1242, column: 5, scope: !3687)
!3691 = !DILocation(line: 1245, column: 7, scope: !3692)
!3692 = distinct !DILexicalBlock(scope: !1777, file: !1, line: 1245, column: 6)
!3693 = !DILocation(line: 1245, column: 13, scope: !3692)
!3694 = !DILocation(line: 1245, column: 17, scope: !3692)
!3695 = !DILocation(line: 1245, column: 24, scope: !3692)
!3696 = !DILocation(line: 1245, column: 41, scope: !3692)
!3697 = !DILocation(line: 1245, column: 6, scope: !1777)
!3698 = !DILocation(line: 1247, column: 5, scope: !3699)
!3699 = distinct !DILexicalBlock(scope: !3692, file: !1, line: 1245, column: 55)
!3700 = !DILocation(line: 1247, column: 5, scope: !3701)
!3701 = !DILexicalBlockFile(scope: !3702, file: !1, discriminator: 1)
!3702 = distinct !DILexicalBlock(scope: !3699, file: !1, line: 1247, column: 5)
!3703 = !DILocation(line: 1249, column: 15, scope: !3699)
!3704 = !DILocation(line: 1249, column: 12, scope: !3699)
!3705 = !DILocation(line: 1250, column: 23, scope: !3699)
!3706 = !DILocation(line: 1250, column: 29, scope: !3699)
!3707 = !DILocation(line: 1250, column: 10, scope: !3699)
!3708 = !DILocation(line: 1250, column: 5, scope: !3699)
!3709 = !DILocation(line: 1250, column: 21, scope: !3699)
!3710 = !DILocation(line: 1251, column: 3, scope: !3699)
!3711 = !DILocation(line: 1254, column: 7, scope: !3712)
!3712 = distinct !DILexicalBlock(scope: !1777, file: !1, line: 1254, column: 6)
!3713 = !DILocation(line: 1254, column: 13, scope: !3712)
!3714 = !DILocation(line: 1254, column: 17, scope: !3712)
!3715 = !DILocation(line: 1254, column: 24, scope: !3712)
!3716 = !DILocation(line: 1254, column: 41, scope: !3712)
!3717 = !DILocation(line: 1254, column: 6, scope: !1777)
!3718 = !DILocation(line: 1256, column: 9, scope: !3719)
!3719 = distinct !DILexicalBlock(scope: !3720, file: !1, line: 1256, column: 8)
!3720 = distinct !DILexicalBlock(scope: !3712, file: !1, line: 1254, column: 55)
!3721 = !DILocation(line: 1256, column: 15, scope: !3719)
!3722 = !DILocation(line: 1256, column: 25, scope: !3719)
!3723 = !DILocation(line: 1256, column: 31, scope: !3719)
!3724 = !DILocation(line: 1256, column: 22, scope: !3719)
!3725 = !DILocation(line: 1256, column: 44, scope: !3719)
!3726 = !DILocation(line: 1257, column: 8, scope: !3719)
!3727 = !DILocation(line: 1257, column: 15, scope: !3719)
!3728 = !DILocation(line: 1256, column: 8, scope: !3729)
!3729 = !DILexicalBlockFile(scope: !3720, file: !1, discriminator: 1)
!3730 = !DILocation(line: 1260, column: 10, scope: !3731)
!3731 = distinct !DILexicalBlock(scope: !3732, file: !1, line: 1260, column: 10)
!3732 = distinct !DILexicalBlock(scope: !3719, file: !1, line: 1257, column: 33)
!3733 = !DILocation(line: 1260, column: 17, scope: !3731)
!3734 = !DILocation(line: 1260, column: 10, scope: !3732)
!3735 = !DILocation(line: 1261, column: 18, scope: !3731)
!3736 = !DILocation(line: 1261, column: 9, scope: !3731)
!3737 = !DILocation(line: 1263, column: 7, scope: !3732)
!3738 = !DILocation(line: 1263, column: 7, scope: !3739)
!3739 = !DILexicalBlockFile(scope: !3740, file: !1, discriminator: 1)
!3740 = distinct !DILexicalBlock(scope: !3732, file: !1, line: 1263, column: 7)
!3741 = !DILocation(line: 1265, column: 25, scope: !3732)
!3742 = !DILocation(line: 1265, column: 31, scope: !3732)
!3743 = !DILocation(line: 1265, column: 12, scope: !3732)
!3744 = !DILocation(line: 1265, column: 7, scope: !3732)
!3745 = !DILocation(line: 1265, column: 23, scope: !3732)
!3746 = !DILocation(line: 1266, column: 5, scope: !3732)
!3747 = !DILocation(line: 1268, column: 15, scope: !3720)
!3748 = !DILocation(line: 1268, column: 12, scope: !3720)
!3749 = !DILocation(line: 1269, column: 3, scope: !3720)
!3750 = !DILocation(line: 1271, column: 10, scope: !1777)
!3751 = !DILocation(line: 1271, column: 3, scope: !1777)
!3752 = !DILocation(line: 1272, column: 1, scope: !1777)
!3753 = !DILocalVariable(name: "data", arg: 1, scope: !1778, file: !1, line: 1276, type: !544)
!3754 = !DILocation(line: 1276, column: 42, scope: !1778)
!3755 = !DILocation(line: 1278, column: 28, scope: !1778)
!3756 = !DILocation(line: 1278, column: 34, scope: !1778)
!3757 = !DILocation(line: 1278, column: 38, scope: !1778)
!3758 = !DILocation(line: 1278, column: 3, scope: !1778)
!3759 = !DILocation(line: 1278, column: 9, scope: !1778)
!3760 = !DILocation(line: 1278, column: 15, scope: !1778)
!3761 = !DILocation(line: 1278, column: 26, scope: !1778)
!3762 = !DILocation(line: 1279, column: 20, scope: !1778)
!3763 = !DILocation(line: 1279, column: 26, scope: !1778)
!3764 = !DILocation(line: 1279, column: 30, scope: !1778)
!3765 = !DILocation(line: 1279, column: 3, scope: !1778)
!3766 = !DILocation(line: 1279, column: 9, scope: !1778)
!3767 = !DILocation(line: 1279, column: 15, scope: !1778)
!3768 = !DILocation(line: 1279, column: 18, scope: !1778)
!3769 = !DILocation(line: 1280, column: 1, scope: !1778)
!3770 = !DILocalVariable(name: "data", arg: 1, scope: !1781, file: !1, line: 1287, type: !544)
!3771 = !DILocation(line: 1287, column: 45, scope: !1781)
!3772 = !DILocalVariable(name: "result", scope: !1781, file: !1, line: 1289, type: !554)
!3773 = !DILocation(line: 1289, column: 12, scope: !1781)
!3774 = !DILocation(line: 1290, column: 7, scope: !3775)
!3775 = distinct !DILexicalBlock(scope: !1781, file: !1, line: 1290, column: 6)
!3776 = !DILocation(line: 1290, column: 13, scope: !3775)
!3777 = !DILocation(line: 1290, column: 20, scope: !3775)
!3778 = !DILocation(line: 1290, column: 6, scope: !1781)
!3779 = !DILocation(line: 1292, column: 11, scope: !3780)
!3780 = distinct !DILexicalBlock(scope: !3775, file: !1, line: 1290, column: 25)
!3781 = !DILocation(line: 1292, column: 5, scope: !3780)
!3782 = !DILocation(line: 1293, column: 5, scope: !3780)
!3783 = !DILocation(line: 1299, column: 10, scope: !1781)
!3784 = !DILocation(line: 1300, column: 6, scope: !3785)
!3785 = distinct !DILexicalBlock(scope: !1781, file: !1, line: 1300, column: 6)
!3786 = !DILocation(line: 1300, column: 6, scope: !1781)
!3787 = !DILocation(line: 1301, column: 12, scope: !3785)
!3788 = !DILocation(line: 1301, column: 5, scope: !3785)
!3789 = !DILocation(line: 1303, column: 3, scope: !1781)
!3790 = !DILocation(line: 1303, column: 9, scope: !1781)
!3791 = !DILocation(line: 1303, column: 13, scope: !1781)
!3792 = !DILocation(line: 1303, column: 27, scope: !1781)
!3793 = !DILocation(line: 1304, column: 3, scope: !1781)
!3794 = !DILocation(line: 1304, column: 9, scope: !1781)
!3795 = !DILocation(line: 1304, column: 15, scope: !1781)
!3796 = !DILocation(line: 1304, column: 32, scope: !1781)
!3797 = !DILocation(line: 1305, column: 3, scope: !1781)
!3798 = !DILocation(line: 1305, column: 9, scope: !1781)
!3799 = !DILocation(line: 1305, column: 15, scope: !1781)
!3800 = !DILocation(line: 1305, column: 24, scope: !1781)
!3801 = !DILocation(line: 1306, column: 3, scope: !1781)
!3802 = !DILocation(line: 1306, column: 9, scope: !1781)
!3803 = !DILocation(line: 1306, column: 15, scope: !1781)
!3804 = !DILocation(line: 1306, column: 27, scope: !1781)
!3805 = !DILocation(line: 1308, column: 3, scope: !1781)
!3806 = !DILocation(line: 1308, column: 9, scope: !1781)
!3807 = !DILocation(line: 1308, column: 15, scope: !1781)
!3808 = !DILocation(line: 1308, column: 27, scope: !1781)
!3809 = !DILocation(line: 1309, column: 31, scope: !1781)
!3810 = !DILocation(line: 1309, column: 37, scope: !1781)
!3811 = !DILocation(line: 1309, column: 41, scope: !1781)
!3812 = !DILocation(line: 1309, column: 3, scope: !1781)
!3813 = !DILocation(line: 1309, column: 9, scope: !1781)
!3814 = !DILocation(line: 1309, column: 15, scope: !1781)
!3815 = !DILocation(line: 1309, column: 24, scope: !1781)
!3816 = !DILocation(line: 1309, column: 29, scope: !1781)
!3817 = !DILocation(line: 1310, column: 32, scope: !1781)
!3818 = !DILocation(line: 1310, column: 38, scope: !1781)
!3819 = !DILocation(line: 1310, column: 42, scope: !1781)
!3820 = !DILocation(line: 1310, column: 3, scope: !1781)
!3821 = !DILocation(line: 1310, column: 9, scope: !1781)
!3822 = !DILocation(line: 1310, column: 15, scope: !1781)
!3823 = !DILocation(line: 1310, column: 25, scope: !1781)
!3824 = !DILocation(line: 1310, column: 30, scope: !1781)
!3825 = !DILocation(line: 1311, column: 3, scope: !1781)
!3826 = !DILocation(line: 1311, column: 3, scope: !3827)
!3827 = !DILexicalBlockFile(scope: !3828, file: !1, discriminator: 1)
!3828 = distinct !DILexicalBlock(scope: !1781, file: !1, line: 1311, column: 3)
!3829 = !DILocation(line: 1312, column: 3, scope: !1781)
!3830 = !DILocation(line: 1312, column: 9, scope: !1781)
!3831 = !DILocation(line: 1312, column: 14, scope: !1781)
!3832 = !DILocation(line: 1312, column: 28, scope: !1781)
!3833 = !DILocation(line: 1314, column: 6, scope: !3834)
!3834 = distinct !DILexicalBlock(scope: !1781, file: !1, line: 1314, column: 6)
!3835 = !DILocation(line: 1314, column: 12, scope: !3834)
!3836 = !DILocation(line: 1314, column: 16, scope: !3834)
!3837 = !DILocation(line: 1314, column: 24, scope: !3834)
!3838 = !DILocation(line: 1314, column: 6, scope: !1781)
!3839 = !DILocation(line: 1315, column: 30, scope: !3834)
!3840 = !DILocation(line: 1315, column: 36, scope: !3834)
!3841 = !DILocation(line: 1315, column: 40, scope: !3834)
!3842 = !DILocation(line: 1315, column: 5, scope: !3834)
!3843 = !DILocation(line: 1315, column: 11, scope: !3834)
!3844 = !DILocation(line: 1315, column: 17, scope: !3834)
!3845 = !DILocation(line: 1315, column: 28, scope: !3834)
!3846 = !DILocation(line: 1317, column: 30, scope: !3834)
!3847 = !DILocation(line: 1317, column: 36, scope: !3834)
!3848 = !DILocation(line: 1317, column: 40, scope: !3834)
!3849 = !DILocation(line: 1317, column: 5, scope: !3834)
!3850 = !DILocation(line: 1317, column: 11, scope: !3834)
!3851 = !DILocation(line: 1317, column: 17, scope: !3834)
!3852 = !DILocation(line: 1317, column: 28, scope: !3834)
!3853 = !DILocation(line: 1320, column: 6, scope: !3854)
!3854 = distinct !DILexicalBlock(scope: !1781, file: !1, line: 1320, column: 6)
!3855 = !DILocation(line: 1320, column: 12, scope: !3854)
!3856 = !DILocation(line: 1320, column: 19, scope: !3854)
!3857 = !DILocation(line: 1320, column: 6, scope: !1781)
!3858 = !DILocation(line: 1321, column: 27, scope: !3854)
!3859 = !DILocation(line: 1321, column: 5, scope: !3854)
!3860 = !DILocation(line: 1324, column: 6, scope: !3861)
!3861 = distinct !DILexicalBlock(scope: !1781, file: !1, line: 1324, column: 6)
!3862 = !DILocation(line: 1324, column: 12, scope: !3861)
!3863 = !DILocation(line: 1324, column: 19, scope: !3861)
!3864 = !DILocation(line: 1324, column: 6, scope: !1781)
!3865 = !DILocation(line: 1325, column: 33, scope: !3861)
!3866 = !DILocation(line: 1325, column: 14, scope: !3861)
!3867 = !DILocation(line: 1325, column: 12, scope: !3861)
!3868 = !DILocation(line: 1325, column: 5, scope: !3861)
!3869 = !DILocation(line: 1327, column: 7, scope: !3870)
!3870 = distinct !DILexicalBlock(scope: !1781, file: !1, line: 1327, column: 6)
!3871 = !DILocation(line: 1327, column: 6, scope: !1781)
!3872 = !DILocation(line: 1331, column: 5, scope: !3873)
!3873 = distinct !DILexicalBlock(scope: !3870, file: !1, line: 1327, column: 15)
!3874 = !DILocation(line: 1331, column: 11, scope: !3873)
!3875 = !DILocation(line: 1331, column: 17, scope: !3873)
!3876 = !DILocation(line: 1331, column: 28, scope: !3873)
!3877 = !DILocation(line: 1341, column: 19, scope: !3873)
!3878 = !DILocation(line: 1341, column: 5, scope: !3873)
!3879 = !DILocation(line: 1342, column: 30, scope: !3873)
!3880 = !DILocation(line: 1342, column: 5, scope: !3873)
!3881 = !DILocation(line: 1343, column: 23, scope: !3873)
!3882 = !DILocation(line: 1343, column: 5, scope: !3873)
!3883 = !DILocation(line: 1345, column: 8, scope: !3884)
!3884 = distinct !DILexicalBlock(scope: !3873, file: !1, line: 1345, column: 8)
!3885 = !DILocation(line: 1345, column: 14, scope: !3884)
!3886 = !DILocation(line: 1345, column: 18, scope: !3884)
!3887 = !DILocation(line: 1345, column: 8, scope: !3873)
!3888 = !DILocation(line: 1346, column: 19, scope: !3884)
!3889 = !DILocation(line: 1346, column: 25, scope: !3884)
!3890 = !DILocation(line: 1346, column: 31, scope: !3884)
!3891 = !DILocation(line: 1346, column: 35, scope: !3884)
!3892 = !DILocation(line: 1346, column: 7, scope: !3884)
!3893 = !DILocation(line: 1348, column: 8, scope: !3894)
!3894 = distinct !DILexicalBlock(scope: !3873, file: !1, line: 1348, column: 8)
!3895 = !DILocation(line: 1348, column: 14, scope: !3894)
!3896 = !DILocation(line: 1348, column: 18, scope: !3894)
!3897 = !DILocation(line: 1348, column: 8, scope: !3873)
!3898 = !DILocation(line: 1349, column: 19, scope: !3894)
!3899 = !DILocation(line: 1349, column: 25, scope: !3894)
!3900 = !DILocation(line: 1349, column: 31, scope: !3894)
!3901 = !DILocation(line: 1349, column: 35, scope: !3894)
!3902 = !DILocation(line: 1349, column: 7, scope: !3894)
!3903 = !DILocation(line: 1354, column: 36, scope: !3873)
!3904 = !DILocation(line: 1354, column: 42, scope: !3873)
!3905 = !DILocation(line: 1354, column: 48, scope: !3873)
!3906 = !DILocation(line: 1354, column: 57, scope: !3873)
!3907 = !DILocation(line: 1354, column: 5, scope: !3873)
!3908 = !DILocation(line: 1354, column: 11, scope: !3873)
!3909 = !DILocation(line: 1354, column: 17, scope: !3873)
!3910 = !DILocation(line: 1354, column: 26, scope: !3873)
!3911 = !DILocation(line: 1354, column: 33, scope: !3873)
!3912 = !DILocation(line: 1355, column: 37, scope: !3873)
!3913 = !DILocation(line: 1355, column: 43, scope: !3873)
!3914 = !DILocation(line: 1355, column: 49, scope: !3873)
!3915 = !DILocation(line: 1355, column: 59, scope: !3873)
!3916 = !DILocation(line: 1355, column: 5, scope: !3873)
!3917 = !DILocation(line: 1355, column: 11, scope: !3873)
!3918 = !DILocation(line: 1355, column: 17, scope: !3873)
!3919 = !DILocation(line: 1355, column: 27, scope: !3873)
!3920 = !DILocation(line: 1355, column: 34, scope: !3873)
!3921 = !DILocation(line: 1357, column: 8, scope: !3922)
!3922 = distinct !DILexicalBlock(scope: !3873, file: !1, line: 1357, column: 8)
!3923 = !DILocation(line: 1357, column: 14, scope: !3922)
!3924 = !DILocation(line: 1357, column: 18, scope: !3922)
!3925 = !DILocation(line: 1357, column: 8, scope: !3873)
!3926 = !DILocalVariable(name: "wc", scope: !3927, file: !1, line: 1358, type: !3928)
!3927 = distinct !DILexicalBlock(scope: !3922, file: !1, line: 1357, column: 33)
!3928 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1207, size: 64, align: 64)
!3929 = !DILocation(line: 1358, column: 28, scope: !3927)
!3930 = !DILocation(line: 1358, column: 34, scope: !3927)
!3931 = !DILocation(line: 1358, column: 40, scope: !3927)
!3932 = !DILocation(line: 1359, column: 10, scope: !3933)
!3933 = distinct !DILexicalBlock(scope: !3927, file: !1, line: 1359, column: 10)
!3934 = !DILocation(line: 1359, column: 14, scope: !3933)
!3935 = !DILocation(line: 1359, column: 20, scope: !3933)
!3936 = !DILocation(line: 1359, column: 10, scope: !3927)
!3937 = !DILocation(line: 1360, column: 37, scope: !3938)
!3938 = distinct !DILexicalBlock(scope: !3933, file: !1, line: 1359, column: 35)
!3939 = !DILocation(line: 1360, column: 18, scope: !3938)
!3940 = !DILocation(line: 1360, column: 16, scope: !3938)
!3941 = !DILocation(line: 1361, column: 12, scope: !3942)
!3942 = distinct !DILexicalBlock(scope: !3938, file: !1, line: 1361, column: 12)
!3943 = !DILocation(line: 1361, column: 12, scope: !3938)
!3944 = !DILocation(line: 1362, column: 11, scope: !3942)
!3945 = !DILocation(line: 1363, column: 7, scope: !3938)
!3946 = !DILocation(line: 1364, column: 5, scope: !3927)
!3947 = !DILocation(line: 1365, column: 3, scope: !3873)
!3948 = !DILocation(line: 1367, column: 10, scope: !1781)
!3949 = !DILocation(line: 1367, column: 3, scope: !1781)
!3950 = !DILocation(line: 1368, column: 1, scope: !1781)
!3951 = !DILocalVariable(name: "data", arg: 1, scope: !1784, file: !1, line: 1373, type: !544)
!3952 = !DILocation(line: 1373, column: 46, scope: !1784)
!3953 = !DILocation(line: 1380, column: 9, scope: !1784)
!3954 = !DILocation(line: 1383, column: 3, scope: !1784)
!3955 = !DILocalVariable(name: "data", arg: 1, scope: !1785, file: !1, line: 1630, type: !544)
!3956 = !DILocation(line: 1630, column: 40, scope: !1785)
!3957 = !DILocalVariable(name: "newurl", arg: 2, scope: !1785, file: !1, line: 1631, type: !215)
!3958 = !DILocation(line: 1631, column: 28, scope: !1785)
!3959 = !DILocalVariable(name: "type", arg: 3, scope: !1785, file: !1, line: 1634, type: !1788)
!3960 = !DILocation(line: 1634, column: 33, scope: !1785)
!3961 = !DILocalVariable(name: "disallowport", scope: !1785, file: !1, line: 1645, type: !211)
!3962 = !DILocation(line: 1645, column: 8, scope: !1785)
!3963 = !DILocation(line: 1647, column: 6, scope: !3964)
!3964 = distinct !DILexicalBlock(scope: !1785, file: !1, line: 1647, column: 6)
!3965 = !DILocation(line: 1647, column: 11, scope: !3964)
!3966 = !DILocation(line: 1647, column: 6, scope: !1785)
!3967 = !DILocation(line: 1648, column: 9, scope: !3968)
!3968 = distinct !DILexicalBlock(scope: !3969, file: !1, line: 1648, column: 8)
!3969 = distinct !DILexicalBlock(scope: !3964, file: !1, line: 1647, column: 28)
!3970 = !DILocation(line: 1648, column: 15, scope: !3968)
!3971 = !DILocation(line: 1648, column: 19, scope: !3968)
!3972 = !DILocation(line: 1648, column: 29, scope: !3968)
!3973 = !DILocation(line: 1648, column: 36, scope: !3968)
!3974 = !DILocation(line: 1649, column: 10, scope: !3968)
!3975 = !DILocation(line: 1649, column: 16, scope: !3968)
!3976 = !DILocation(line: 1649, column: 20, scope: !3968)
!3977 = !DILocation(line: 1649, column: 38, scope: !3968)
!3978 = !DILocation(line: 1649, column: 44, scope: !3968)
!3979 = !DILocation(line: 1649, column: 48, scope: !3968)
!3980 = !DILocation(line: 1649, column: 35, scope: !3968)
!3981 = !DILocation(line: 1648, column: 8, scope: !3982)
!3982 = !DILexicalBlockFile(scope: !3969, file: !1, discriminator: 1)
!3983 = !DILocation(line: 1650, column: 13, scope: !3984)
!3984 = distinct !DILexicalBlock(scope: !3968, file: !1, line: 1649, column: 60)
!3985 = !DILocation(line: 1650, column: 55, scope: !3984)
!3986 = !DILocation(line: 1650, column: 61, scope: !3984)
!3987 = !DILocation(line: 1650, column: 65, scope: !3984)
!3988 = !DILocation(line: 1650, column: 7, scope: !3984)
!3989 = !DILocation(line: 1651, column: 7, scope: !3984)
!3990 = !DILocation(line: 1655, column: 5, scope: !3969)
!3991 = !DILocation(line: 1655, column: 11, scope: !3969)
!3992 = !DILocation(line: 1655, column: 17, scope: !3969)
!3993 = !DILocation(line: 1655, column: 34, scope: !3969)
!3994 = !DILocation(line: 1657, column: 5, scope: !3969)
!3995 = !DILocation(line: 1657, column: 11, scope: !3969)
!3996 = !DILocation(line: 1657, column: 15, scope: !3969)
!3997 = !DILocation(line: 1657, column: 29, scope: !3969)
!3998 = !DILocation(line: 1659, column: 8, scope: !3999)
!3999 = distinct !DILexicalBlock(scope: !3969, file: !1, line: 1659, column: 8)
!4000 = !DILocation(line: 1659, column: 14, scope: !3999)
!4001 = !DILocation(line: 1659, column: 18, scope: !3999)
!4002 = !DILocation(line: 1659, column: 8, scope: !3969)
!4003 = !DILocation(line: 1664, column: 10, scope: !4004)
!4004 = distinct !DILexicalBlock(scope: !4005, file: !1, line: 1664, column: 10)
!4005 = distinct !DILexicalBlock(scope: !3999, file: !1, line: 1659, column: 37)
!4006 = !DILocation(line: 1664, column: 16, scope: !4004)
!4007 = !DILocation(line: 1664, column: 23, scope: !4004)
!4008 = !DILocation(line: 1664, column: 10, scope: !4005)
!4009 = !DILocation(line: 1665, column: 9, scope: !4010)
!4010 = distinct !DILexicalBlock(scope: !4004, file: !1, line: 1664, column: 38)
!4011 = !DILocation(line: 1665, column: 9, scope: !4012)
!4012 = !DILexicalBlockFile(scope: !4013, file: !1, discriminator: 1)
!4013 = distinct !DILexicalBlock(scope: !4010, file: !1, line: 1665, column: 9)
!4014 = !DILocation(line: 1666, column: 9, scope: !4010)
!4015 = !DILocation(line: 1666, column: 15, scope: !4010)
!4016 = !DILocation(line: 1666, column: 22, scope: !4010)
!4017 = !DILocation(line: 1666, column: 36, scope: !4010)
!4018 = !DILocation(line: 1667, column: 7, scope: !4010)
!4019 = !DILocation(line: 1669, column: 30, scope: !4005)
!4020 = !DILocation(line: 1669, column: 7, scope: !4005)
!4021 = !DILocation(line: 1669, column: 13, scope: !4005)
!4022 = !DILocation(line: 1669, column: 20, scope: !4005)
!4023 = !DILocation(line: 1669, column: 28, scope: !4005)
!4024 = !DILocation(line: 1670, column: 11, scope: !4025)
!4025 = distinct !DILexicalBlock(scope: !4005, file: !1, line: 1670, column: 10)
!4026 = !DILocation(line: 1670, column: 17, scope: !4025)
!4027 = !DILocation(line: 1670, column: 24, scope: !4025)
!4028 = !DILocation(line: 1670, column: 10, scope: !4005)
!4029 = !DILocation(line: 1671, column: 9, scope: !4025)
!4030 = !DILocation(line: 1672, column: 7, scope: !4005)
!4031 = !DILocation(line: 1672, column: 13, scope: !4005)
!4032 = !DILocation(line: 1672, column: 20, scope: !4005)
!4033 = !DILocation(line: 1672, column: 34, scope: !4005)
!4034 = !DILocation(line: 1673, column: 5, scope: !4005)
!4035 = !DILocation(line: 1674, column: 3, scope: !3969)
!4036 = !DILocation(line: 1676, column: 23, scope: !4037)
!4037 = distinct !DILexicalBlock(scope: !1785, file: !1, line: 1676, column: 6)
!4038 = !DILocation(line: 1676, column: 7, scope: !4037)
!4039 = !DILocation(line: 1676, column: 6, scope: !1785)
!4040 = !DILocalVariable(name: "absolute", scope: !4041, file: !1, line: 1681, type: !215)
!4041 = distinct !DILexicalBlock(scope: !4037, file: !1, line: 1676, column: 33)
!4042 = !DILocation(line: 1681, column: 11, scope: !4041)
!4043 = !DILocation(line: 1681, column: 33, scope: !4041)
!4044 = !DILocation(line: 1681, column: 39, scope: !4041)
!4045 = !DILocation(line: 1681, column: 46, scope: !4041)
!4046 = !DILocation(line: 1681, column: 51, scope: !4041)
!4047 = !DILocation(line: 1681, column: 22, scope: !4041)
!4048 = !DILocation(line: 1682, column: 9, scope: !4049)
!4049 = distinct !DILexicalBlock(scope: !4041, file: !1, line: 1682, column: 8)
!4050 = !DILocation(line: 1682, column: 8, scope: !4041)
!4051 = !DILocation(line: 1683, column: 7, scope: !4049)
!4052 = !DILocation(line: 1684, column: 5, scope: !4041)
!4053 = !DILocation(line: 1685, column: 14, scope: !4041)
!4054 = !DILocation(line: 1685, column: 12, scope: !4041)
!4055 = !DILocation(line: 1686, column: 3, scope: !4041)
!4056 = !DILocalVariable(name: "newest", scope: !4057, file: !1, line: 1690, type: !215)
!4057 = distinct !DILexicalBlock(scope: !4037, file: !1, line: 1687, column: 8)
!4058 = !DILocation(line: 1690, column: 11, scope: !4057)
!4059 = !DILocalVariable(name: "newlen", scope: !4057, file: !1, line: 1691, type: !158)
!4060 = !DILocation(line: 1691, column: 12, scope: !4057)
!4061 = !DILocation(line: 1691, column: 32, scope: !4057)
!4062 = !DILocation(line: 1691, column: 21, scope: !4057)
!4063 = !DILocation(line: 1694, column: 18, scope: !4057)
!4064 = !DILocation(line: 1696, column: 14, scope: !4057)
!4065 = !DILocation(line: 1696, column: 12, scope: !4057)
!4066 = !DILocation(line: 1697, column: 9, scope: !4067)
!4067 = distinct !DILexicalBlock(scope: !4057, file: !1, line: 1697, column: 8)
!4068 = !DILocation(line: 1697, column: 8, scope: !4057)
!4069 = !DILocation(line: 1698, column: 7, scope: !4067)
!4070 = !DILocation(line: 1699, column: 16, scope: !4057)
!4071 = !DILocation(line: 1699, column: 24, scope: !4057)
!4072 = !DILocation(line: 1699, column: 5, scope: !4057)
!4073 = !DILocation(line: 1701, column: 5, scope: !4057)
!4074 = !DILocation(line: 1702, column: 14, scope: !4057)
!4075 = !DILocation(line: 1702, column: 12, scope: !4057)
!4076 = !DILocation(line: 1706, column: 6, scope: !4077)
!4077 = distinct !DILexicalBlock(scope: !1785, file: !1, line: 1706, column: 6)
!4078 = !DILocation(line: 1706, column: 11, scope: !4077)
!4079 = !DILocation(line: 1706, column: 6, scope: !1785)
!4080 = !DILocation(line: 1709, column: 32, scope: !4081)
!4081 = distinct !DILexicalBlock(scope: !4077, file: !1, line: 1706, column: 27)
!4082 = !DILocation(line: 1709, column: 5, scope: !4081)
!4083 = !DILocation(line: 1709, column: 11, scope: !4081)
!4084 = !DILocation(line: 1709, column: 16, scope: !4081)
!4085 = !DILocation(line: 1709, column: 30, scope: !4081)
!4086 = !DILocation(line: 1710, column: 5, scope: !4081)
!4087 = !DILocation(line: 1713, column: 6, scope: !4088)
!4088 = distinct !DILexicalBlock(scope: !1785, file: !1, line: 1713, column: 6)
!4089 = !DILocation(line: 1713, column: 6, scope: !1785)
!4090 = !DILocation(line: 1714, column: 5, scope: !4088)
!4091 = !DILocation(line: 1714, column: 11, scope: !4088)
!4092 = !DILocation(line: 1714, column: 17, scope: !4088)
!4093 = !DILocation(line: 1714, column: 28, scope: !4088)
!4094 = !DILocation(line: 1716, column: 6, scope: !4095)
!4095 = distinct !DILexicalBlock(scope: !1785, file: !1, line: 1716, column: 6)
!4096 = !DILocation(line: 1716, column: 12, scope: !4095)
!4097 = !DILocation(line: 1716, column: 19, scope: !4095)
!4098 = !DILocation(line: 1716, column: 6, scope: !1785)
!4099 = !DILocation(line: 1717, column: 5, scope: !4100)
!4100 = distinct !DILexicalBlock(scope: !4095, file: !1, line: 1716, column: 30)
!4101 = !DILocation(line: 1717, column: 5, scope: !4102)
!4102 = !DILexicalBlockFile(scope: !4103, file: !1, discriminator: 1)
!4103 = distinct !DILexicalBlock(scope: !4100, file: !1, line: 1717, column: 5)
!4104 = !DILocation(line: 1718, column: 5, scope: !4100)
!4105 = !DILocation(line: 1718, column: 11, scope: !4100)
!4106 = !DILocation(line: 1718, column: 18, scope: !4100)
!4107 = !DILocation(line: 1718, column: 28, scope: !4100)
!4108 = !DILocation(line: 1719, column: 3, scope: !4100)
!4109 = !DILocation(line: 1721, column: 22, scope: !1785)
!4110 = !DILocation(line: 1721, column: 3, scope: !1785)
!4111 = !DILocation(line: 1721, column: 9, scope: !1785)
!4112 = !DILocation(line: 1721, column: 16, scope: !1785)
!4113 = !DILocation(line: 1721, column: 20, scope: !1785)
!4114 = !DILocation(line: 1722, column: 3, scope: !1785)
!4115 = !DILocation(line: 1722, column: 9, scope: !1785)
!4116 = !DILocation(line: 1722, column: 16, scope: !1785)
!4117 = !DILocation(line: 1722, column: 26, scope: !1785)
!4118 = !DILocation(line: 1723, column: 10, scope: !1785)
!4119 = !DILocation(line: 1725, column: 9, scope: !1785)
!4120 = !DILocation(line: 1725, column: 60, scope: !1785)
!4121 = !DILocation(line: 1725, column: 66, scope: !1785)
!4122 = !DILocation(line: 1725, column: 73, scope: !1785)
!4123 = !DILocation(line: 1725, column: 3, scope: !1785)
!4124 = !DILocation(line: 1734, column: 10, scope: !1785)
!4125 = !DILocation(line: 1734, column: 16, scope: !1785)
!4126 = !DILocation(line: 1734, column: 21, scope: !1785)
!4127 = !DILocation(line: 1734, column: 3, scope: !1785)
!4128 = !DILocation(line: 1746, column: 5, scope: !4129)
!4129 = distinct !DILexicalBlock(scope: !1785, file: !1, line: 1734, column: 31)
!4130 = !DILocation(line: 1764, column: 9, scope: !4131)
!4131 = distinct !DILexicalBlock(scope: !4129, file: !1, line: 1764, column: 8)
!4132 = !DILocation(line: 1764, column: 15, scope: !4131)
!4133 = !DILocation(line: 1764, column: 19, scope: !4131)
!4134 = !DILocation(line: 1764, column: 27, scope: !4131)
!4135 = !DILocation(line: 1765, column: 9, scope: !4131)
!4136 = !DILocation(line: 1765, column: 12, scope: !4137)
!4137 = !DILexicalBlockFile(scope: !4131, file: !1, discriminator: 1)
!4138 = !DILocation(line: 1765, column: 18, scope: !4137)
!4139 = !DILocation(line: 1765, column: 22, scope: !4137)
!4140 = !DILocation(line: 1765, column: 30, scope: !4137)
!4141 = !DILocation(line: 1766, column: 8, scope: !4131)
!4142 = !DILocation(line: 1766, column: 13, scope: !4137)
!4143 = !DILocation(line: 1766, column: 19, scope: !4137)
!4144 = !DILocation(line: 1766, column: 23, scope: !4137)
!4145 = !DILocation(line: 1766, column: 33, scope: !4137)
!4146 = !DILocation(line: 1764, column: 8, scope: !4147)
!4147 = !DILexicalBlockFile(scope: !4129, file: !1, discriminator: 1)
!4148 = !DILocation(line: 1767, column: 13, scope: !4149)
!4149 = distinct !DILexicalBlock(scope: !4131, file: !1, line: 1766, column: 57)
!4150 = !DILocation(line: 1767, column: 7, scope: !4149)
!4151 = !DILocation(line: 1768, column: 7, scope: !4149)
!4152 = !DILocation(line: 1768, column: 13, scope: !4149)
!4153 = !DILocation(line: 1768, column: 17, scope: !4149)
!4154 = !DILocation(line: 1768, column: 25, scope: !4149)
!4155 = !DILocation(line: 1769, column: 5, scope: !4149)
!4156 = !DILocation(line: 1770, column: 5, scope: !4129)
!4157 = !DILocation(line: 1788, column: 9, scope: !4158)
!4158 = distinct !DILexicalBlock(scope: !4129, file: !1, line: 1788, column: 8)
!4159 = !DILocation(line: 1788, column: 15, scope: !4158)
!4160 = !DILocation(line: 1788, column: 19, scope: !4158)
!4161 = !DILocation(line: 1788, column: 27, scope: !4158)
!4162 = !DILocation(line: 1789, column: 9, scope: !4158)
!4163 = !DILocation(line: 1789, column: 12, scope: !4164)
!4164 = !DILexicalBlockFile(scope: !4158, file: !1, discriminator: 1)
!4165 = !DILocation(line: 1789, column: 18, scope: !4164)
!4166 = !DILocation(line: 1789, column: 22, scope: !4164)
!4167 = !DILocation(line: 1789, column: 30, scope: !4164)
!4168 = !DILocation(line: 1790, column: 8, scope: !4158)
!4169 = !DILocation(line: 1790, column: 13, scope: !4164)
!4170 = !DILocation(line: 1790, column: 19, scope: !4164)
!4171 = !DILocation(line: 1790, column: 23, scope: !4164)
!4172 = !DILocation(line: 1790, column: 33, scope: !4164)
!4173 = !DILocation(line: 1788, column: 8, scope: !4147)
!4174 = !DILocation(line: 1791, column: 13, scope: !4175)
!4175 = distinct !DILexicalBlock(scope: !4158, file: !1, line: 1790, column: 57)
!4176 = !DILocation(line: 1791, column: 7, scope: !4175)
!4177 = !DILocation(line: 1792, column: 7, scope: !4175)
!4178 = !DILocation(line: 1792, column: 13, scope: !4175)
!4179 = !DILocation(line: 1792, column: 17, scope: !4175)
!4180 = !DILocation(line: 1792, column: 25, scope: !4175)
!4181 = !DILocation(line: 1793, column: 5, scope: !4175)
!4182 = !DILocation(line: 1794, column: 5, scope: !4129)
!4183 = !DILocation(line: 1799, column: 8, scope: !4184)
!4184 = distinct !DILexicalBlock(scope: !4129, file: !1, line: 1799, column: 8)
!4185 = !DILocation(line: 1799, column: 14, scope: !4184)
!4186 = !DILocation(line: 1799, column: 18, scope: !4184)
!4187 = !DILocation(line: 1799, column: 26, scope: !4184)
!4188 = !DILocation(line: 1800, column: 7, scope: !4184)
!4189 = !DILocation(line: 1800, column: 12, scope: !4190)
!4190 = !DILexicalBlockFile(scope: !4184, file: !1, discriminator: 1)
!4191 = !DILocation(line: 1800, column: 18, scope: !4190)
!4192 = !DILocation(line: 1800, column: 22, scope: !4190)
!4193 = !DILocation(line: 1800, column: 32, scope: !4190)
!4194 = !DILocation(line: 1799, column: 8, scope: !4147)
!4195 = !DILocation(line: 1801, column: 7, scope: !4196)
!4196 = distinct !DILexicalBlock(scope: !4184, file: !1, line: 1800, column: 56)
!4197 = !DILocation(line: 1801, column: 13, scope: !4196)
!4198 = !DILocation(line: 1801, column: 17, scope: !4196)
!4199 = !DILocation(line: 1801, column: 25, scope: !4196)
!4200 = !DILocation(line: 1802, column: 13, scope: !4196)
!4201 = !DILocation(line: 1803, column: 13, scope: !4196)
!4202 = !DILocation(line: 1803, column: 19, scope: !4196)
!4203 = !DILocation(line: 1803, column: 23, scope: !4196)
!4204 = !DILocation(line: 1802, column: 7, scope: !4196)
!4205 = !DILocation(line: 1804, column: 5, scope: !4196)
!4206 = !DILocation(line: 1805, column: 5, scope: !4129)
!4207 = !DILocation(line: 1810, column: 5, scope: !4129)
!4208 = !DILocation(line: 1819, column: 5, scope: !4129)
!4209 = !DILocation(line: 1821, column: 17, scope: !1785)
!4210 = !DILocation(line: 1821, column: 3, scope: !1785)
!4211 = !DILocation(line: 1822, column: 28, scope: !1785)
!4212 = !DILocation(line: 1822, column: 3, scope: !1785)
!4213 = !DILocation(line: 1824, column: 3, scope: !1785)
!4214 = !DILocation(line: 1826, column: 1, scope: !1785)
!4215 = !DILocalVariable(name: "url", arg: 1, scope: !1811, file: !1, line: 1460, type: !928)
!4216 = !DILocation(line: 1460, column: 41, scope: !1811)
!4217 = !DILocalVariable(name: "prot", scope: !1811, file: !1, line: 1462, type: !4218)
!4218 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 128, align: 8, elements: !4219)
!4219 = !{!4220}
!4220 = !DISubrange(count: 16)
!4221 = !DILocation(line: 1462, column: 8, scope: !1811)
!4222 = !DILocalVariable(name: "letter", scope: !1811, file: !1, line: 1463, type: !216)
!4223 = !DILocation(line: 1463, column: 8, scope: !1811)
!4224 = !DILocation(line: 1465, column: 23, scope: !1811)
!4225 = !DILocation(line: 1465, column: 47, scope: !1811)
!4226 = !DILocation(line: 1465, column: 16, scope: !1811)
!4227 = !DILocation(line: 1465, column: 13, scope: !1811)
!4228 = !DILocation(line: 1465, column: 10, scope: !1811)
!4229 = !DILocation(line: 1465, column: 3, scope: !1811)
!4230 = !DILocalVariable(name: "base", arg: 1, scope: !1814, file: !1, line: 1474, type: !928)
!4231 = !DILocation(line: 1474, column: 37, scope: !1814)
!4232 = !DILocalVariable(name: "relurl", arg: 2, scope: !1814, file: !1, line: 1474, type: !928)
!4233 = !DILocation(line: 1474, column: 55, scope: !1814)
!4234 = !DILocalVariable(name: "newest", scope: !1814, file: !1, line: 1481, type: !215)
!4235 = !DILocation(line: 1481, column: 9, scope: !1814)
!4236 = !DILocalVariable(name: "protsep", scope: !1814, file: !1, line: 1482, type: !215)
!4237 = !DILocation(line: 1482, column: 9, scope: !1814)
!4238 = !DILocalVariable(name: "pathsep", scope: !1814, file: !1, line: 1483, type: !215)
!4239 = !DILocation(line: 1483, column: 9, scope: !1814)
!4240 = !DILocalVariable(name: "newlen", scope: !1814, file: !1, line: 1484, type: !158)
!4241 = !DILocation(line: 1484, column: 10, scope: !1814)
!4242 = !DILocalVariable(name: "useurl", scope: !1814, file: !1, line: 1486, type: !928)
!4243 = !DILocation(line: 1486, column: 15, scope: !1814)
!4244 = !DILocation(line: 1486, column: 24, scope: !1814)
!4245 = !DILocalVariable(name: "urllen", scope: !1814, file: !1, line: 1487, type: !158)
!4246 = !DILocation(line: 1487, column: 10, scope: !1814)
!4247 = !DILocalVariable(name: "url_clone", scope: !1814, file: !1, line: 1491, type: !215)
!4248 = !DILocation(line: 1491, column: 9, scope: !1814)
!4249 = !DILocation(line: 1491, column: 19, scope: !1814)
!4250 = !DILocation(line: 1493, column: 7, scope: !4251)
!4251 = distinct !DILexicalBlock(scope: !1814, file: !1, line: 1493, column: 6)
!4252 = !DILocation(line: 1493, column: 6, scope: !1814)
!4253 = !DILocation(line: 1494, column: 5, scope: !4251)
!4254 = !DILocation(line: 1497, column: 18, scope: !1814)
!4255 = !DILocation(line: 1497, column: 11, scope: !1814)
!4256 = !DILocation(line: 1497, column: 10, scope: !1814)
!4257 = !DILocation(line: 1498, column: 7, scope: !4258)
!4258 = distinct !DILexicalBlock(scope: !1814, file: !1, line: 1498, column: 6)
!4259 = !DILocation(line: 1498, column: 6, scope: !1814)
!4260 = !DILocation(line: 1499, column: 13, scope: !4258)
!4261 = !DILocation(line: 1499, column: 12, scope: !4258)
!4262 = !DILocation(line: 1499, column: 5, scope: !4258)
!4263 = !DILocation(line: 1501, column: 12, scope: !4258)
!4264 = !DILocation(line: 1503, column: 13, scope: !4265)
!4265 = distinct !DILexicalBlock(scope: !1814, file: !1, line: 1503, column: 6)
!4266 = !DILocation(line: 1503, column: 10, scope: !4265)
!4267 = !DILocation(line: 1503, column: 6, scope: !1814)
!4268 = !DILocalVariable(name: "level", scope: !4269, file: !1, line: 1504, type: !177)
!4269 = distinct !DILexicalBlock(scope: !4265, file: !1, line: 1503, column: 24)
!4270 = !DILocation(line: 1504, column: 9, scope: !4269)
!4271 = !DILocation(line: 1508, column: 22, scope: !4269)
!4272 = !DILocation(line: 1508, column: 15, scope: !4269)
!4273 = !DILocation(line: 1508, column: 13, scope: !4269)
!4274 = !DILocation(line: 1509, column: 8, scope: !4275)
!4275 = distinct !DILexicalBlock(scope: !4269, file: !1, line: 1509, column: 8)
!4276 = !DILocation(line: 1509, column: 8, scope: !4269)
!4277 = !DILocation(line: 1510, column: 8, scope: !4275)
!4278 = !DILocation(line: 1510, column: 15, scope: !4275)
!4279 = !DILocation(line: 1510, column: 7, scope: !4275)
!4280 = !DILocation(line: 1516, column: 8, scope: !4281)
!4281 = distinct !DILexicalBlock(scope: !4269, file: !1, line: 1516, column: 8)
!4282 = !DILocation(line: 1516, column: 18, scope: !4281)
!4283 = !DILocation(line: 1516, column: 8, scope: !4269)
!4284 = !DILocation(line: 1517, column: 25, scope: !4285)
!4285 = distinct !DILexicalBlock(scope: !4281, file: !1, line: 1516, column: 26)
!4286 = !DILocation(line: 1517, column: 17, scope: !4285)
!4287 = !DILocation(line: 1517, column: 15, scope: !4285)
!4288 = !DILocation(line: 1518, column: 10, scope: !4289)
!4289 = distinct !DILexicalBlock(scope: !4285, file: !1, line: 1518, column: 10)
!4290 = !DILocation(line: 1518, column: 10, scope: !4285)
!4291 = !DILocation(line: 1519, column: 10, scope: !4289)
!4292 = !DILocation(line: 1519, column: 17, scope: !4289)
!4293 = !DILocation(line: 1519, column: 9, scope: !4289)
!4294 = !DILocation(line: 1520, column: 5, scope: !4285)
!4295 = !DILocation(line: 1524, column: 22, scope: !4269)
!4296 = !DILocation(line: 1524, column: 15, scope: !4269)
!4297 = !DILocation(line: 1524, column: 13, scope: !4269)
!4298 = !DILocation(line: 1525, column: 8, scope: !4299)
!4299 = distinct !DILexicalBlock(scope: !4269, file: !1, line: 1525, column: 8)
!4300 = !DILocation(line: 1525, column: 8, scope: !4269)
!4301 = !DILocation(line: 1526, column: 17, scope: !4299)
!4302 = !DILocation(line: 1526, column: 24, scope: !4299)
!4303 = !DILocation(line: 1526, column: 15, scope: !4299)
!4304 = !DILocation(line: 1526, column: 7, scope: !4299)
!4305 = !DILocation(line: 1528, column: 15, scope: !4299)
!4306 = !DILocation(line: 1533, column: 9, scope: !4307)
!4307 = distinct !DILexicalBlock(scope: !4269, file: !1, line: 1533, column: 8)
!4308 = !DILocation(line: 1533, column: 19, scope: !4307)
!4309 = !DILocation(line: 1533, column: 27, scope: !4307)
!4310 = !DILocation(line: 1533, column: 31, scope: !4311)
!4311 = !DILexicalBlockFile(scope: !4307, file: !1, discriminator: 1)
!4312 = !DILocation(line: 1533, column: 41, scope: !4311)
!4313 = !DILocation(line: 1533, column: 8, scope: !4311)
!4314 = !DILocation(line: 1534, column: 13, scope: !4307)
!4315 = !DILocation(line: 1534, column: 7, scope: !4307)
!4316 = !DILocation(line: 1536, column: 5, scope: !4269)
!4317 = !DILocation(line: 1536, column: 12, scope: !4318)
!4318 = !DILexicalBlockFile(scope: !4269, file: !1, discriminator: 1)
!4319 = !DILocation(line: 1536, column: 22, scope: !4318)
!4320 = !DILocation(line: 1536, column: 30, scope: !4318)
!4321 = !DILocation(line: 1537, column: 12, scope: !4269)
!4322 = !DILocation(line: 1537, column: 22, scope: !4269)
!4323 = !DILocation(line: 1537, column: 30, scope: !4269)
!4324 = !DILocation(line: 1538, column: 12, scope: !4269)
!4325 = !DILocation(line: 1538, column: 22, scope: !4269)
!4326 = !DILocation(line: 1536, column: 5, scope: !4327)
!4327 = !DILexicalBlockFile(scope: !4269, file: !1, discriminator: 2)
!4328 = !DILocation(line: 1539, column: 12, scope: !4329)
!4329 = distinct !DILexicalBlock(scope: !4269, file: !1, line: 1538, column: 31)
!4330 = !DILocation(line: 1540, column: 13, scope: !4329)
!4331 = !DILocation(line: 1536, column: 5, scope: !4332)
!4332 = !DILexicalBlockFile(scope: !4269, file: !1, discriminator: 3)
!4333 = !DILocation(line: 1543, column: 8, scope: !4334)
!4334 = distinct !DILexicalBlock(scope: !4269, file: !1, line: 1543, column: 8)
!4335 = !DILocation(line: 1543, column: 8, scope: !4269)
!4336 = !DILocation(line: 1544, column: 7, scope: !4337)
!4337 = distinct !DILexicalBlock(scope: !4334, file: !1, line: 1543, column: 17)
!4338 = !DILocation(line: 1544, column: 18, scope: !4339)
!4339 = !DILexicalBlockFile(scope: !4337, file: !1, discriminator: 1)
!4340 = !DILocation(line: 1544, column: 7, scope: !4339)
!4341 = !DILocation(line: 1546, column: 27, scope: !4342)
!4342 = distinct !DILexicalBlock(scope: !4337, file: !1, line: 1544, column: 22)
!4343 = !DILocation(line: 1546, column: 19, scope: !4342)
!4344 = !DILocation(line: 1546, column: 17, scope: !4342)
!4345 = !DILocation(line: 1547, column: 12, scope: !4346)
!4346 = distinct !DILexicalBlock(scope: !4342, file: !1, line: 1547, column: 12)
!4347 = !DILocation(line: 1547, column: 12, scope: !4342)
!4348 = !DILocation(line: 1548, column: 12, scope: !4346)
!4349 = !DILocation(line: 1548, column: 19, scope: !4346)
!4350 = !DILocation(line: 1548, column: 11, scope: !4346)
!4351 = !DILocation(line: 1550, column: 12, scope: !4352)
!4352 = distinct !DILexicalBlock(scope: !4346, file: !1, line: 1549, column: 14)
!4353 = !DILocation(line: 1550, column: 19, scope: !4352)
!4354 = !DILocation(line: 1551, column: 11, scope: !4352)
!4355 = !DILocation(line: 1544, column: 7, scope: !4356)
!4356 = !DILexicalBlockFile(scope: !4337, file: !1, discriminator: 2)
!4357 = !DILocation(line: 1554, column: 5, scope: !4337)
!4358 = !DILocation(line: 1555, column: 3, scope: !4269)
!4359 = !DILocation(line: 1559, column: 9, scope: !4360)
!4360 = distinct !DILexicalBlock(scope: !4361, file: !1, line: 1559, column: 8)
!4361 = distinct !DILexicalBlock(scope: !4265, file: !1, line: 1556, column: 8)
!4362 = !DILocation(line: 1559, column: 19, scope: !4360)
!4363 = !DILocation(line: 1559, column: 27, scope: !4360)
!4364 = !DILocation(line: 1559, column: 31, scope: !4365)
!4365 = !DILexicalBlockFile(scope: !4360, file: !1, discriminator: 1)
!4366 = !DILocation(line: 1559, column: 41, scope: !4365)
!4367 = !DILocation(line: 1559, column: 8, scope: !4365)
!4368 = !DILocation(line: 1562, column: 8, scope: !4369)
!4369 = distinct !DILexicalBlock(scope: !4360, file: !1, line: 1559, column: 50)
!4370 = !DILocation(line: 1562, column: 15, scope: !4369)
!4371 = !DILocation(line: 1563, column: 17, scope: !4369)
!4372 = !DILocation(line: 1563, column: 14, scope: !4369)
!4373 = !DILocation(line: 1565, column: 5, scope: !4369)
!4374 = !DILocation(line: 1569, column: 24, scope: !4375)
!4375 = distinct !DILexicalBlock(scope: !4360, file: !1, line: 1566, column: 10)
!4376 = !DILocation(line: 1569, column: 17, scope: !4375)
!4377 = !DILocation(line: 1569, column: 15, scope: !4375)
!4378 = !DILocation(line: 1570, column: 10, scope: !4379)
!4379 = distinct !DILexicalBlock(scope: !4375, file: !1, line: 1570, column: 10)
!4380 = !DILocation(line: 1570, column: 10, scope: !4375)
!4381 = !DILocalVariable(name: "sep", scope: !4382, file: !1, line: 1574, type: !215)
!4382 = distinct !DILexicalBlock(scope: !4379, file: !1, line: 1570, column: 19)
!4383 = !DILocation(line: 1574, column: 15, scope: !4382)
!4384 = !DILocation(line: 1574, column: 28, scope: !4382)
!4385 = !DILocation(line: 1574, column: 21, scope: !4382)
!4386 = !DILocation(line: 1575, column: 12, scope: !4387)
!4387 = distinct !DILexicalBlock(scope: !4382, file: !1, line: 1575, column: 12)
!4388 = !DILocation(line: 1575, column: 16, scope: !4387)
!4389 = !DILocation(line: 1575, column: 20, scope: !4390)
!4390 = !DILexicalBlockFile(scope: !4387, file: !1, discriminator: 1)
!4391 = !DILocation(line: 1575, column: 26, scope: !4390)
!4392 = !DILocation(line: 1575, column: 24, scope: !4390)
!4393 = !DILocation(line: 1575, column: 12, scope: !4390)
!4394 = !DILocation(line: 1576, column: 21, scope: !4387)
!4395 = !DILocation(line: 1576, column: 19, scope: !4387)
!4396 = !DILocation(line: 1576, column: 11, scope: !4387)
!4397 = !DILocation(line: 1577, column: 10, scope: !4382)
!4398 = !DILocation(line: 1577, column: 17, scope: !4382)
!4399 = !DILocation(line: 1578, column: 7, scope: !4382)
!4400 = !DILocation(line: 1584, column: 26, scope: !4401)
!4401 = distinct !DILexicalBlock(scope: !4379, file: !1, line: 1579, column: 12)
!4402 = !DILocation(line: 1584, column: 19, scope: !4401)
!4403 = !DILocation(line: 1584, column: 17, scope: !4401)
!4404 = !DILocation(line: 1585, column: 12, scope: !4405)
!4405 = distinct !DILexicalBlock(scope: !4401, file: !1, line: 1585, column: 12)
!4406 = !DILocation(line: 1585, column: 12, scope: !4401)
!4407 = !DILocation(line: 1586, column: 12, scope: !4405)
!4408 = !DILocation(line: 1586, column: 19, scope: !4405)
!4409 = !DILocation(line: 1586, column: 11, scope: !4405)
!4410 = !DILocation(line: 1596, column: 23, scope: !1814)
!4411 = !DILocation(line: 1596, column: 12, scope: !1814)
!4412 = !DILocation(line: 1596, column: 10, scope: !1814)
!4413 = !DILocation(line: 1598, column: 19, scope: !1814)
!4414 = !DILocation(line: 1598, column: 12, scope: !1814)
!4415 = !DILocation(line: 1598, column: 10, scope: !1814)
!4416 = !DILocation(line: 1600, column: 12, scope: !1814)
!4417 = !DILocation(line: 1600, column: 10, scope: !1814)
!4418 = !DILocation(line: 1603, column: 7, scope: !4419)
!4419 = distinct !DILexicalBlock(scope: !1814, file: !1, line: 1603, column: 6)
!4420 = !DILocation(line: 1603, column: 6, scope: !1814)
!4421 = !DILocation(line: 1604, column: 5, scope: !4422)
!4422 = distinct !DILexicalBlock(scope: !4419, file: !1, line: 1603, column: 15)
!4423 = !DILocation(line: 1605, column: 5, scope: !4422)
!4424 = !DILocation(line: 1609, column: 10, scope: !1814)
!4425 = !DILocation(line: 1609, column: 18, scope: !1814)
!4426 = !DILocation(line: 1609, column: 29, scope: !1814)
!4427 = !DILocation(line: 1609, column: 3, scope: !1814)
!4428 = !DILocation(line: 1612, column: 14, scope: !4429)
!4429 = distinct !DILexicalBlock(scope: !1814, file: !1, line: 1612, column: 6)
!4430 = !DILocation(line: 1612, column: 11, scope: !4429)
!4431 = !DILocation(line: 1612, column: 25, scope: !4429)
!4432 = !DILocation(line: 1612, column: 29, scope: !4433)
!4433 = !DILexicalBlockFile(scope: !4429, file: !1, discriminator: 1)
!4434 = !DILocation(line: 1612, column: 37, scope: !4433)
!4435 = !DILocation(line: 1612, column: 42, scope: !4436)
!4436 = !DILexicalBlockFile(scope: !4429, file: !1, discriminator: 2)
!4437 = !DILocation(line: 1612, column: 41, scope: !4436)
!4438 = !DILocation(line: 1612, column: 51, scope: !4436)
!4439 = !DILocation(line: 1612, column: 62, scope: !4440)
!4440 = !DILexicalBlockFile(scope: !4429, file: !1, discriminator: 3)
!4441 = !DILocation(line: 1612, column: 59, scope: !4440)
!4442 = !DILocation(line: 1612, column: 6, scope: !4440)
!4443 = !DILocation(line: 1612, column: 6, scope: !4444)
!4444 = !DILexicalBlockFile(scope: !1814, file: !1, discriminator: 4)
!4445 = !DILocation(line: 1615, column: 18, scope: !4429)
!4446 = !DILocation(line: 1615, column: 5, scope: !4429)
!4447 = !DILocation(line: 1615, column: 21, scope: !4429)
!4448 = !DILocation(line: 1618, column: 22, scope: !1814)
!4449 = !DILocation(line: 1618, column: 15, scope: !1814)
!4450 = !DILocation(line: 1618, column: 31, scope: !1814)
!4451 = !DILocation(line: 1618, column: 3, scope: !1814)
!4452 = !DILocation(line: 1620, column: 3, scope: !1814)
!4453 = !DILocation(line: 1622, column: 10, scope: !1814)
!4454 = !DILocation(line: 1622, column: 3, scope: !1814)
!4455 = !DILocation(line: 1623, column: 1, scope: !1814)
!4456 = !DILocalVariable(name: "url", arg: 1, scope: !1817, file: !1, line: 1391, type: !928)
!4457 = !DILocation(line: 1391, column: 38, scope: !1817)
!4458 = !DILocalVariable(name: "ptr", scope: !1817, file: !1, line: 1393, type: !4459)
!4459 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !4460, size: 64, align: 64)
!4460 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1648)
!4461 = !DILocation(line: 1393, column: 24, scope: !1817)
!4462 = !DILocalVariable(name: "newlen", scope: !1817, file: !1, line: 1394, type: !158)
!4463 = !DILocation(line: 1394, column: 10, scope: !1817)
!4464 = !DILocalVariable(name: "left", scope: !1817, file: !1, line: 1395, type: !211)
!4465 = !DILocation(line: 1395, column: 8, scope: !1817)
!4466 = !DILocation(line: 1397, column: 28, scope: !4467)
!4467 = distinct !DILexicalBlock(scope: !1817, file: !1, line: 1397, column: 3)
!4468 = !DILocation(line: 1397, column: 10, scope: !4467)
!4469 = !DILocation(line: 1397, column: 7, scope: !4467)
!4470 = !DILocation(line: 1397, column: 34, scope: !4471)
!4471 = !DILexicalBlockFile(scope: !4472, file: !1, discriminator: 1)
!4472 = distinct !DILexicalBlock(scope: !4467, file: !1, line: 1397, column: 3)
!4473 = !DILocation(line: 1397, column: 33, scope: !4471)
!4474 = !DILocation(line: 1397, column: 3, scope: !4471)
!4475 = !DILocation(line: 1398, column: 13, scope: !4476)
!4476 = distinct !DILexicalBlock(scope: !4472, file: !1, line: 1397, column: 46)
!4477 = !DILocation(line: 1398, column: 12, scope: !4476)
!4478 = !DILocation(line: 1398, column: 5, scope: !4476)
!4479 = !DILocation(line: 1400, column: 11, scope: !4480)
!4480 = distinct !DILexicalBlock(scope: !4476, file: !1, line: 1398, column: 18)
!4481 = !DILocation(line: 1400, column: 7, scope: !4480)
!4482 = !DILocation(line: 1403, column: 11, scope: !4483)
!4483 = distinct !DILexicalBlock(scope: !4480, file: !1, line: 1403, column: 10)
!4484 = !DILocation(line: 1403, column: 10, scope: !4483)
!4485 = !DILocation(line: 1403, column: 15, scope: !4483)
!4486 = !DILocation(line: 1403, column: 10, scope: !4480)
!4487 = !DILocation(line: 1404, column: 16, scope: !4483)
!4488 = !DILocation(line: 1404, column: 9, scope: !4483)
!4489 = !DILocation(line: 1405, column: 13, scope: !4480)
!4490 = !DILocation(line: 1406, column: 7, scope: !4480)
!4491 = !DILocation(line: 1408, column: 10, scope: !4492)
!4492 = distinct !DILexicalBlock(scope: !4480, file: !1, line: 1408, column: 10)
!4493 = !DILocation(line: 1408, column: 10, scope: !4480)
!4494 = !DILocation(line: 1409, column: 15, scope: !4492)
!4495 = !DILocation(line: 1409, column: 9, scope: !4492)
!4496 = !DILocation(line: 1411, column: 15, scope: !4492)
!4497 = !DILocation(line: 1412, column: 7, scope: !4480)
!4498 = !DILocation(line: 1414, column: 3, scope: !4476)
!4499 = !DILocation(line: 1397, column: 42, scope: !4500)
!4500 = !DILexicalBlockFile(scope: !4472, file: !1, discriminator: 2)
!4501 = !DILocation(line: 1397, column: 3, scope: !4500)
!4502 = !DILocation(line: 1415, column: 10, scope: !1817)
!4503 = !DILocation(line: 1415, column: 3, scope: !1817)
!4504 = !DILocalVariable(name: "output", arg: 1, scope: !1820, file: !1, line: 1421, type: !215)
!4505 = !DILocation(line: 1421, column: 30, scope: !1820)
!4506 = !DILocalVariable(name: "url", arg: 2, scope: !1820, file: !1, line: 1421, type: !928)
!4507 = !DILocation(line: 1421, column: 50, scope: !1820)
!4508 = !DILocalVariable(name: "left", scope: !1820, file: !1, line: 1424, type: !211)
!4509 = !DILocation(line: 1424, column: 8, scope: !1820)
!4510 = !DILocalVariable(name: "iptr", scope: !1820, file: !1, line: 1425, type: !4459)
!4511 = !DILocation(line: 1425, column: 24, scope: !1820)
!4512 = !DILocalVariable(name: "optr", scope: !1820, file: !1, line: 1426, type: !215)
!4513 = !DILocation(line: 1426, column: 9, scope: !1820)
!4514 = !DILocation(line: 1426, column: 16, scope: !1820)
!4515 = !DILocation(line: 1427, column: 31, scope: !4516)
!4516 = distinct !DILexicalBlock(scope: !1820, file: !1, line: 1427, column: 3)
!4517 = !DILocation(line: 1427, column: 12, scope: !4516)
!4518 = !DILocation(line: 1427, column: 7, scope: !4516)
!4519 = !DILocation(line: 1428, column: 8, scope: !4520)
!4520 = distinct !DILexicalBlock(scope: !4516, file: !1, line: 1427, column: 3)
!4521 = !DILocation(line: 1428, column: 7, scope: !4520)
!4522 = !DILocation(line: 1427, column: 3, scope: !4523)
!4523 = !DILexicalBlockFile(scope: !4516, file: !1, discriminator: 1)
!4524 = !DILocation(line: 1430, column: 13, scope: !4525)
!4525 = distinct !DILexicalBlock(scope: !4520, file: !1, line: 1429, column: 15)
!4526 = !DILocation(line: 1430, column: 12, scope: !4525)
!4527 = !DILocation(line: 1430, column: 5, scope: !4525)
!4528 = !DILocation(line: 1432, column: 11, scope: !4529)
!4529 = distinct !DILexicalBlock(scope: !4525, file: !1, line: 1430, column: 19)
!4530 = !DILocation(line: 1432, column: 7, scope: !4529)
!4531 = !DILocation(line: 1435, column: 11, scope: !4532)
!4532 = distinct !DILexicalBlock(scope: !4529, file: !1, line: 1435, column: 10)
!4533 = !DILocation(line: 1435, column: 10, scope: !4532)
!4534 = !DILocation(line: 1435, column: 16, scope: !4532)
!4535 = !DILocation(line: 1435, column: 10, scope: !4529)
!4536 = !DILocation(line: 1436, column: 18, scope: !4537)
!4537 = distinct !DILexicalBlock(scope: !4532, file: !1, line: 1435, column: 25)
!4538 = !DILocation(line: 1436, column: 38, scope: !4537)
!4539 = !DILocation(line: 1436, column: 37, scope: !4537)
!4540 = !DILocation(line: 1436, column: 9, scope: !4537)
!4541 = !DILocation(line: 1437, column: 14, scope: !4537)
!4542 = !DILocation(line: 1438, column: 7, scope: !4537)
!4543 = !DILocation(line: 1440, column: 18, scope: !4532)
!4544 = !DILocation(line: 1440, column: 17, scope: !4532)
!4545 = !DILocation(line: 1440, column: 14, scope: !4532)
!4546 = !DILocation(line: 1440, column: 16, scope: !4532)
!4547 = !DILocation(line: 1441, column: 7, scope: !4529)
!4548 = !DILocation(line: 1443, column: 10, scope: !4549)
!4549 = distinct !DILexicalBlock(scope: !4529, file: !1, line: 1443, column: 10)
!4550 = !DILocation(line: 1443, column: 10, scope: !4529)
!4551 = !DILocation(line: 1444, column: 14, scope: !4552)
!4552 = distinct !DILexicalBlock(scope: !4549, file: !1, line: 1443, column: 16)
!4553 = !DILocation(line: 1444, column: 16, scope: !4552)
!4554 = !DILocation(line: 1445, column: 14, scope: !4552)
!4555 = !DILocation(line: 1445, column: 16, scope: !4552)
!4556 = !DILocation(line: 1446, column: 14, scope: !4552)
!4557 = !DILocation(line: 1446, column: 16, scope: !4552)
!4558 = !DILocation(line: 1447, column: 7, scope: !4552)
!4559 = !DILocation(line: 1449, column: 14, scope: !4549)
!4560 = !DILocation(line: 1449, column: 16, scope: !4549)
!4561 = !DILocation(line: 1450, column: 7, scope: !4529)
!4562 = !DILocation(line: 1452, column: 3, scope: !4525)
!4563 = !DILocation(line: 1429, column: 11, scope: !4520)
!4564 = !DILocation(line: 1427, column: 3, scope: !4565)
!4565 = !DILexicalBlockFile(scope: !4520, file: !1, discriminator: 2)
!4566 = !DILocation(line: 1453, column: 4, scope: !1820)
!4567 = !DILocation(line: 1453, column: 8, scope: !1820)
!4568 = !DILocation(line: 1455, column: 1, scope: !1820)
!4569 = !DILocalVariable(name: "conn", arg: 1, scope: !1789, file: !1, line: 1831, type: !550)
!4570 = !DILocation(line: 1831, column: 49, scope: !1789)
!4571 = !DILocalVariable(name: "url", arg: 2, scope: !1789, file: !1, line: 1832, type: !1524)
!4572 = !DILocation(line: 1832, column: 36, scope: !1789)
!4573 = !DILocalVariable(name: "data", scope: !1789, file: !1, line: 1834, type: !544)
!4574 = !DILocation(line: 1834, column: 21, scope: !1789)
!4575 = !DILocation(line: 1834, column: 28, scope: !1789)
!4576 = !DILocation(line: 1834, column: 34, scope: !1789)
!4577 = !DILocation(line: 1836, column: 4, scope: !1789)
!4578 = !DILocation(line: 1836, column: 8, scope: !1789)
!4579 = !DILocation(line: 1840, column: 6, scope: !4580)
!4580 = distinct !DILexicalBlock(scope: !1789, file: !1, line: 1840, column: 6)
!4581 = !DILocation(line: 1840, column: 12, scope: !4580)
!4582 = !DILocation(line: 1840, column: 16, scope: !4580)
!4583 = !DILocation(line: 1840, column: 23, scope: !4580)
!4584 = !DILocation(line: 1841, column: 8, scope: !4580)
!4585 = !DILocation(line: 1841, column: 14, scope: !4580)
!4586 = !DILocation(line: 1841, column: 23, scope: !4580)
!4587 = !DILocation(line: 1841, column: 31, scope: !4580)
!4588 = !DILocation(line: 1840, column: 6, scope: !4589)
!4589 = !DILexicalBlockFile(scope: !1789, file: !1, discriminator: 1)
!4590 = !DILocation(line: 1842, column: 5, scope: !4580)
!4591 = !DILocation(line: 1844, column: 7, scope: !4592)
!4592 = distinct !DILexicalBlock(scope: !1789, file: !1, line: 1844, column: 6)
!4593 = !DILocation(line: 1844, column: 13, scope: !4592)
!4594 = !DILocation(line: 1844, column: 17, scope: !4592)
!4595 = !DILocation(line: 1844, column: 29, scope: !4592)
!4596 = !DILocation(line: 1844, column: 35, scope: !4592)
!4597 = !DILocation(line: 1844, column: 39, scope: !4592)
!4598 = !DILocation(line: 1844, column: 27, scope: !4592)
!4599 = !DILocation(line: 1844, column: 55, scope: !4592)
!4600 = !DILocation(line: 1844, column: 61, scope: !4592)
!4601 = !DILocation(line: 1845, column: 7, scope: !4592)
!4602 = !DILocation(line: 1845, column: 13, scope: !4592)
!4603 = !DILocation(line: 1845, column: 18, scope: !4592)
!4604 = !DILocation(line: 1845, column: 24, scope: !4592)
!4605 = !DILocation(line: 1846, column: 9, scope: !4592)
!4606 = !DILocation(line: 1846, column: 15, scope: !4592)
!4607 = !DILocation(line: 1846, column: 19, scope: !4592)
!4608 = !DILocation(line: 1847, column: 9, scope: !4592)
!4609 = !DILocation(line: 1847, column: 13, scope: !4610)
!4610 = !DILexicalBlockFile(scope: !4592, file: !1, discriminator: 1)
!4611 = !DILocation(line: 1847, column: 19, scope: !4610)
!4612 = !DILocation(line: 1847, column: 28, scope: !4610)
!4613 = !DILocation(line: 1847, column: 37, scope: !4610)
!4614 = !DILocation(line: 1847, column: 59, scope: !4610)
!4615 = !DILocation(line: 1848, column: 8, scope: !4592)
!4616 = !DILocation(line: 1848, column: 14, scope: !4592)
!4617 = !DILocation(line: 1848, column: 18, scope: !4592)
!4618 = !DILocation(line: 1848, column: 26, scope: !4592)
!4619 = !DILocation(line: 1844, column: 6, scope: !4589)
!4620 = !DILocation(line: 1856, column: 11, scope: !4621)
!4621 = distinct !DILexicalBlock(scope: !4592, file: !1, line: 1848, column: 47)
!4622 = !DILocation(line: 1856, column: 17, scope: !4621)
!4623 = !DILocation(line: 1856, column: 5, scope: !4621)
!4624 = !DILocation(line: 1857, column: 12, scope: !4621)
!4625 = !DILocation(line: 1857, column: 6, scope: !4621)
!4626 = !DILocation(line: 1857, column: 10, scope: !4621)
!4627 = !DILocation(line: 1858, column: 10, scope: !4628)
!4628 = distinct !DILexicalBlock(scope: !4621, file: !1, line: 1858, column: 8)
!4629 = !DILocation(line: 1858, column: 9, scope: !4628)
!4630 = !DILocation(line: 1858, column: 8, scope: !4621)
!4631 = !DILocation(line: 1859, column: 7, scope: !4628)
!4632 = !DILocation(line: 1861, column: 5, scope: !4621)
!4633 = !DILocation(line: 1862, column: 5, scope: !4621)
!4634 = !DILocation(line: 1862, column: 11, scope: !4621)
!4635 = !DILocation(line: 1862, column: 16, scope: !4621)
!4636 = !DILocation(line: 1862, column: 22, scope: !4621)
!4637 = !DILocation(line: 1869, column: 8, scope: !4638)
!4638 = distinct !DILexicalBlock(scope: !4621, file: !1, line: 1869, column: 8)
!4639 = !DILocation(line: 1869, column: 14, scope: !4638)
!4640 = !DILocation(line: 1869, column: 23, scope: !4638)
!4641 = !DILocation(line: 1869, column: 31, scope: !4638)
!4642 = !DILocation(line: 1869, column: 8, scope: !4621)
!4643 = !DILocalVariable(name: "http", scope: !4644, file: !1, line: 1870, type: !3347)
!4644 = distinct !DILexicalBlock(scope: !4638, file: !1, line: 1869, column: 51)
!4645 = !DILocation(line: 1870, column: 20, scope: !4644)
!4646 = !DILocation(line: 1870, column: 27, scope: !4644)
!4647 = !DILocation(line: 1870, column: 33, scope: !4644)
!4648 = !DILocation(line: 1870, column: 37, scope: !4644)
!4649 = !DILocation(line: 1871, column: 10, scope: !4650)
!4650 = distinct !DILexicalBlock(scope: !4644, file: !1, line: 1871, column: 10)
!4651 = !DILocation(line: 1871, column: 16, scope: !4650)
!4652 = !DILocation(line: 1871, column: 10, scope: !4644)
!4653 = !DILocation(line: 1872, column: 32, scope: !4650)
!4654 = !DILocation(line: 1872, column: 16, scope: !4650)
!4655 = !DILocation(line: 1872, column: 9, scope: !4650)
!4656 = !DILocation(line: 1873, column: 5, scope: !4644)
!4657 = !DILocation(line: 1874, column: 3, scope: !4621)
!4658 = !DILocation(line: 1875, column: 3, scope: !1789)
!4659 = !DILocation(line: 1876, column: 1, scope: !1789)
!4660 = !DILocalVariable(name: "conn", arg: 1, scope: !1792, file: !1, line: 1884, type: !550)
!4661 = !DILocation(line: 1884, column: 23, scope: !1792)
!4662 = !DILocalVariable(name: "sockindex", arg: 2, scope: !1792, file: !1, line: 1885, type: !177)
!4663 = !DILocation(line: 1885, column: 7, scope: !1792)
!4664 = !DILocalVariable(name: "size", arg: 3, scope: !1792, file: !1, line: 1886, type: !189)
!4665 = !DILocation(line: 1886, column: 14, scope: !1792)
!4666 = !DILocalVariable(name: "getheader", arg: 4, scope: !1792, file: !1, line: 1887, type: !211)
!4667 = !DILocation(line: 1887, column: 8, scope: !1792)
!4668 = !DILocalVariable(name: "bytecountp", arg: 5, scope: !1792, file: !1, line: 1888, type: !193)
!4669 = !DILocation(line: 1888, column: 15, scope: !1792)
!4670 = !DILocalVariable(name: "writesockindex", arg: 6, scope: !1792, file: !1, line: 1889, type: !177)
!4671 = !DILocation(line: 1889, column: 7, scope: !1792)
!4672 = !DILocalVariable(name: "writecountp", arg: 7, scope: !1792, file: !1, line: 1891, type: !193)
!4673 = !DILocation(line: 1891, column: 15, scope: !1792)
!4674 = !DILocalVariable(name: "data", scope: !1792, file: !1, line: 1894, type: !544)
!4675 = !DILocation(line: 1894, column: 21, scope: !1792)
!4676 = !DILocalVariable(name: "k", scope: !1792, file: !1, line: 1895, type: !1798)
!4677 = !DILocation(line: 1895, column: 25, scope: !1792)
!4678 = !DILocation(line: 1897, column: 3, scope: !1792)
!4679 = !DILocation(line: 1897, column: 3, scope: !4680)
!4680 = !DILexicalBlockFile(scope: !4681, file: !1, discriminator: 1)
!4681 = distinct !DILexicalBlock(scope: !1792, file: !1, line: 1897, column: 3)
!4682 = !DILocation(line: 1899, column: 10, scope: !1792)
!4683 = !DILocation(line: 1899, column: 16, scope: !1792)
!4684 = !DILocation(line: 1899, column: 8, scope: !1792)
!4685 = !DILocation(line: 1900, column: 8, scope: !1792)
!4686 = !DILocation(line: 1900, column: 14, scope: !1792)
!4687 = !DILocation(line: 1900, column: 5, scope: !1792)
!4688 = !DILocation(line: 1902, column: 3, scope: !1792)
!4689 = !DILocation(line: 1902, column: 3, scope: !4690)
!4690 = !DILexicalBlockFile(scope: !4691, file: !1, discriminator: 1)
!4691 = distinct !DILexicalBlock(scope: !1792, file: !1, line: 1902, column: 3)
!4692 = !DILocation(line: 1905, column: 18, scope: !1792)
!4693 = !DILocation(line: 1905, column: 28, scope: !1792)
!4694 = !DILocation(line: 1905, column: 18, scope: !4695)
!4695 = !DILexicalBlockFile(scope: !1792, file: !1, discriminator: 1)
!4696 = !DILocation(line: 1906, column: 36, scope: !1792)
!4697 = !DILocation(line: 1906, column: 25, scope: !1792)
!4698 = !DILocation(line: 1906, column: 31, scope: !1792)
!4699 = !DILocation(line: 1905, column: 18, scope: !4700)
!4700 = !DILexicalBlockFile(scope: !1792, file: !1, discriminator: 2)
!4701 = !DILocation(line: 1905, column: 18, scope: !4702)
!4702 = !DILexicalBlockFile(scope: !1792, file: !1, discriminator: 3)
!4703 = !DILocation(line: 1905, column: 3, scope: !4702)
!4704 = !DILocation(line: 1905, column: 9, scope: !4702)
!4705 = !DILocation(line: 1905, column: 16, scope: !4702)
!4706 = !DILocation(line: 1907, column: 23, scope: !1792)
!4707 = !DILocation(line: 1907, column: 38, scope: !1792)
!4708 = !DILocation(line: 1907, column: 23, scope: !4695)
!4709 = !DILocation(line: 1908, column: 34, scope: !1792)
!4710 = !DILocation(line: 1908, column: 23, scope: !1792)
!4711 = !DILocation(line: 1908, column: 29, scope: !1792)
!4712 = !DILocation(line: 1907, column: 23, scope: !4700)
!4713 = !DILocation(line: 1907, column: 23, scope: !4702)
!4714 = !DILocation(line: 1907, column: 3, scope: !4702)
!4715 = !DILocation(line: 1907, column: 9, scope: !4702)
!4716 = !DILocation(line: 1907, column: 21, scope: !4702)
!4717 = !DILocation(line: 1909, column: 18, scope: !1792)
!4718 = !DILocation(line: 1909, column: 3, scope: !1792)
!4719 = !DILocation(line: 1909, column: 6, scope: !1792)
!4720 = !DILocation(line: 1909, column: 16, scope: !1792)
!4721 = !DILocation(line: 1911, column: 13, scope: !1792)
!4722 = !DILocation(line: 1911, column: 3, scope: !1792)
!4723 = !DILocation(line: 1911, column: 6, scope: !1792)
!4724 = !DILocation(line: 1911, column: 11, scope: !1792)
!4725 = !DILocation(line: 1912, column: 19, scope: !1792)
!4726 = !DILocation(line: 1912, column: 3, scope: !1792)
!4727 = !DILocation(line: 1912, column: 6, scope: !1792)
!4728 = !DILocation(line: 1912, column: 17, scope: !1792)
!4729 = !DILocation(line: 1913, column: 24, scope: !1792)
!4730 = !DILocation(line: 1913, column: 3, scope: !1792)
!4731 = !DILocation(line: 1913, column: 6, scope: !1792)
!4732 = !DILocation(line: 1913, column: 22, scope: !1792)
!4733 = !DILocation(line: 1919, column: 7, scope: !4734)
!4734 = distinct !DILexicalBlock(scope: !1792, file: !1, line: 1919, column: 6)
!4735 = !DILocation(line: 1919, column: 10, scope: !4734)
!4736 = !DILocation(line: 1919, column: 6, scope: !1792)
!4737 = !DILocation(line: 1920, column: 5, scope: !4738)
!4738 = distinct !DILexicalBlock(scope: !4734, file: !1, line: 1919, column: 21)
!4739 = !DILocation(line: 1920, column: 8, scope: !4738)
!4740 = !DILocation(line: 1920, column: 15, scope: !4738)
!4741 = !DILocation(line: 1921, column: 8, scope: !4742)
!4742 = distinct !DILexicalBlock(scope: !4738, file: !1, line: 1921, column: 8)
!4743 = !DILocation(line: 1921, column: 13, scope: !4742)
!4744 = !DILocation(line: 1921, column: 8, scope: !4738)
!4745 = !DILocation(line: 1922, column: 32, scope: !4742)
!4746 = !DILocation(line: 1922, column: 38, scope: !4742)
!4747 = !DILocation(line: 1922, column: 7, scope: !4742)
!4748 = !DILocation(line: 1923, column: 3, scope: !4738)
!4749 = !DILocation(line: 1925, column: 6, scope: !4750)
!4750 = distinct !DILexicalBlock(scope: !1792, file: !1, line: 1925, column: 6)
!4751 = !DILocation(line: 1925, column: 9, scope: !4750)
!4752 = !DILocation(line: 1925, column: 19, scope: !4750)
!4753 = !DILocation(line: 1925, column: 23, scope: !4754)
!4754 = !DILexicalBlockFile(scope: !4750, file: !1, discriminator: 1)
!4755 = !DILocation(line: 1925, column: 29, scope: !4754)
!4756 = !DILocation(line: 1925, column: 33, scope: !4754)
!4757 = !DILocation(line: 1925, column: 6, scope: !4754)
!4758 = !DILocation(line: 1927, column: 8, scope: !4759)
!4759 = distinct !DILexicalBlock(scope: !4760, file: !1, line: 1927, column: 8)
!4760 = distinct !DILexicalBlock(scope: !4750, file: !1, line: 1925, column: 46)
!4761 = !DILocation(line: 1927, column: 14, scope: !4759)
!4762 = !DILocation(line: 1927, column: 21, scope: !4759)
!4763 = !DILocation(line: 1927, column: 8, scope: !4760)
!4764 = !DILocation(line: 1928, column: 7, scope: !4759)
!4765 = !DILocation(line: 1928, column: 10, scope: !4759)
!4766 = !DILocation(line: 1928, column: 17, scope: !4759)
!4767 = !DILocation(line: 1930, column: 8, scope: !4768)
!4768 = distinct !DILexicalBlock(scope: !4760, file: !1, line: 1930, column: 8)
!4769 = !DILocation(line: 1930, column: 14, scope: !4768)
!4770 = !DILocation(line: 1930, column: 26, scope: !4768)
!4771 = !DILocation(line: 1930, column: 8, scope: !4760)
!4772 = !DILocalVariable(name: "http", scope: !4773, file: !1, line: 1931, type: !3347)
!4773 = distinct !DILexicalBlock(scope: !4768, file: !1, line: 1930, column: 46)
!4774 = !DILocation(line: 1931, column: 20, scope: !4773)
!4775 = !DILocation(line: 1931, column: 27, scope: !4773)
!4776 = !DILocation(line: 1931, column: 33, scope: !4773)
!4777 = !DILocation(line: 1931, column: 37, scope: !4773)
!4778 = !DILocation(line: 1941, column: 11, scope: !4779)
!4779 = distinct !DILexicalBlock(scope: !4773, file: !1, line: 1941, column: 10)
!4780 = !DILocation(line: 1941, column: 17, scope: !4779)
!4781 = !DILocation(line: 1941, column: 23, scope: !4779)
!4782 = !DILocation(line: 1941, column: 40, scope: !4779)
!4783 = !DILocation(line: 1942, column: 11, scope: !4779)
!4784 = !DILocation(line: 1942, column: 17, scope: !4779)
!4785 = !DILocation(line: 1942, column: 26, scope: !4779)
!4786 = !DILocation(line: 1942, column: 34, scope: !4779)
!4787 = !DILocation(line: 1942, column: 54, scope: !4779)
!4788 = !DILocation(line: 1943, column: 11, scope: !4779)
!4789 = !DILocation(line: 1943, column: 17, scope: !4779)
!4790 = !DILocation(line: 1943, column: 25, scope: !4779)
!4791 = !DILocation(line: 1941, column: 10, scope: !4792)
!4792 = !DILexicalBlockFile(scope: !4773, file: !1, discriminator: 1)
!4793 = !DILocation(line: 1945, column: 9, scope: !4794)
!4794 = distinct !DILexicalBlock(scope: !4779, file: !1, line: 1943, column: 44)
!4795 = !DILocation(line: 1945, column: 12, scope: !4794)
!4796 = !DILocation(line: 1945, column: 19, scope: !4794)
!4797 = !DILocation(line: 1946, column: 9, scope: !4794)
!4798 = !DILocation(line: 1946, column: 12, scope: !4794)
!4799 = !DILocation(line: 1946, column: 23, scope: !4794)
!4800 = !DILocation(line: 1946, column: 23, scope: !4801)
!4801 = !DILexicalBlockFile(scope: !4794, file: !1, discriminator: 1)
!4802 = !DILocation(line: 1950, column: 21, scope: !4794)
!4803 = !DILocation(line: 1950, column: 27, scope: !4794)
!4804 = !DILocation(line: 1950, column: 33, scope: !4794)
!4805 = !DILocation(line: 1950, column: 37, scope: !4794)
!4806 = !DILocation(line: 1950, column: 9, scope: !4794)
!4807 = !DILocation(line: 1951, column: 7, scope: !4794)
!4808 = !DILocation(line: 1953, column: 12, scope: !4809)
!4809 = distinct !DILexicalBlock(scope: !4810, file: !1, line: 1953, column: 12)
!4810 = distinct !DILexicalBlock(scope: !4779, file: !1, line: 1952, column: 12)
!4811 = !DILocation(line: 1953, column: 18, scope: !4809)
!4812 = !DILocation(line: 1953, column: 24, scope: !4809)
!4813 = !DILocation(line: 1953, column: 12, scope: !4810)
!4814 = !DILocation(line: 1956, column: 11, scope: !4809)
!4815 = !DILocation(line: 1956, column: 14, scope: !4809)
!4816 = !DILocation(line: 1956, column: 21, scope: !4809)
!4817 = !DILocation(line: 1959, column: 9, scope: !4810)
!4818 = !DILocation(line: 1959, column: 12, scope: !4810)
!4819 = !DILocation(line: 1959, column: 19, scope: !4810)
!4820 = !DILocation(line: 1961, column: 5, scope: !4773)
!4821 = !DILocation(line: 1962, column: 3, scope: !4760)
!4822 = !DILocation(line: 1964, column: 1, scope: !1792)
!4823 = !DILocalVariable(name: "conn", arg: 1, scope: !1799, file: !1, line: 320, type: !550)
!4824 = !DILocation(line: 320, column: 45, scope: !1799)
!4825 = !DILocalVariable(name: "thismuch", arg: 2, scope: !1799, file: !1, line: 321, type: !158)
!4826 = !DILocation(line: 321, column: 32, scope: !1799)
!4827 = !DILocation(line: 323, column: 3, scope: !1799)
!4828 = !DILocation(line: 323, column: 3, scope: !4829)
!4829 = !DILexicalBlockFile(scope: !4830, file: !1, discriminator: 1)
!4830 = distinct !DILexicalBlock(scope: !1799, file: !1, line: 323, column: 3)
!4831 = !DILocation(line: 325, column: 21, scope: !1799)
!4832 = !DILocation(line: 325, column: 3, scope: !1799)
!4833 = !DILocation(line: 325, column: 9, scope: !1799)
!4834 = !DILocation(line: 325, column: 18, scope: !1799)
!4835 = !DILocation(line: 326, column: 3, scope: !1799)
!4836 = !DILocation(line: 326, column: 9, scope: !1799)
!4837 = !DILocation(line: 326, column: 14, scope: !1799)
!4838 = !DILocation(line: 326, column: 33, scope: !1799)
!4839 = !DILocation(line: 347, column: 1, scope: !1799)
!4840 = !DILocalVariable(name: "conn", arg: 1, scope: !1802, file: !1, line: 300, type: !1449)
!4841 = !DILocation(line: 300, column: 51, scope: !1802)
!4842 = !DILocation(line: 304, column: 10, scope: !1802)
!4843 = !DILocation(line: 304, column: 16, scope: !1802)
!4844 = !DILocation(line: 304, column: 25, scope: !1802)
!4845 = !DILocation(line: 304, column: 33, scope: !1802)
!4846 = !DILocation(line: 304, column: 65, scope: !1802)
!4847 = !DILocation(line: 304, column: 65, scope: !4848)
!4848 = !DILexicalBlockFile(scope: !1802, file: !1, discriminator: 1)
!4849 = !DILocation(line: 304, column: 65, scope: !4850)
!4850 = !DILexicalBlockFile(scope: !1802, file: !1, discriminator: 2)
!4851 = !DILocation(line: 304, column: 3, scope: !4850)
!4852 = !DILocalVariable(name: "conn", arg: 1, scope: !1808, file: !1, line: 835, type: !550)
!4853 = !DILocation(line: 835, column: 50, scope: !1808)
!4854 = !DILocalVariable(name: "k", arg: 2, scope: !1808, file: !1, line: 836, type: !1798)
!4855 = !DILocation(line: 836, column: 52, scope: !1808)
!4856 = !DILocation(line: 838, column: 3, scope: !1808)
!4857 = !DILocation(line: 838, column: 6, scope: !1808)
!4858 = !DILocation(line: 838, column: 13, scope: !1808)
!4859 = !DILocation(line: 842, column: 6, scope: !4860)
!4860 = distinct !DILexicalBlock(scope: !1808, file: !1, line: 842, column: 6)
!4861 = !DILocation(line: 842, column: 12, scope: !4860)
!4862 = !DILocation(line: 842, column: 17, scope: !4860)
!4863 = !DILocation(line: 842, column: 6, scope: !1808)
!4864 = !DILocalVariable(name: "result", scope: !4865, file: !1, line: 843, type: !554)
!4865 = distinct !DILexicalBlock(scope: !4860, file: !1, line: 842, column: 34)
!4866 = !DILocation(line: 843, column: 14, scope: !4865)
!4867 = !DILocation(line: 843, column: 39, scope: !4865)
!4868 = !DILocation(line: 843, column: 23, scope: !4865)
!4869 = !DILocation(line: 844, column: 8, scope: !4870)
!4870 = distinct !DILexicalBlock(scope: !4865, file: !1, line: 844, column: 8)
!4871 = !DILocation(line: 844, column: 8, scope: !4865)
!4872 = !DILocation(line: 845, column: 14, scope: !4870)
!4873 = !DILocation(line: 845, column: 7, scope: !4870)
!4874 = !DILocation(line: 846, column: 3, scope: !4865)
!4875 = !DILocation(line: 847, column: 3, scope: !1808)
!4876 = !DILocation(line: 848, column: 1, scope: !1808)
