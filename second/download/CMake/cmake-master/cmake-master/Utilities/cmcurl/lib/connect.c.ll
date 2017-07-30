; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/connect.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.Curl_easy = type { %struct.Curl_easy*, %struct.Curl_easy*, %struct.connectdata*, i32, i32, %struct.Curl_message, [5 x i32], i32, %struct.Names, %struct.Curl_multi*, %struct.Curl_multi*, %struct.Curl_share*, %struct.SingleRequest, %struct.UserDefined, %struct.DynamicStatic, %struct.CookieInfo*, %struct.Progress, %struct.UrlState, %struct.WildcardData, %struct.PureInfo, %struct.curl_tlssessioninfo, i32 }
%struct.connectdata = type { %struct.Curl_easy*, %struct.Curl_chunker, i32 (i8*, i32)*, i8*, i8, i64, %struct.Curl_dns_entry*, %struct.Curl_addrinfo*, [2 x %struct.Curl_addrinfo*], [46 x i8], i32, i32, %struct.hostname, i8*, %struct.hostname, %struct.proxy_info, %struct.proxy_info, i64, i32, i32, i16, [46 x i8], i64, [46 x i8], i64, i8*, i8*, i8*, i8*, i32, i32, %struct.timeval, %struct.timeval, [2 x i32], [2 x i32], [2 x i8], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x %struct.ssl_connect_data], [2 x %struct.ssl_connect_data], %struct.ssl_primary_config, %struct.ssl_primary_config, i8, %struct.ConnectBits, %struct.timeval, i32, i64, %struct.Curl_handler*, %struct.Curl_handler*, i64, i32, i32, %struct.dynamically_allocated_data, i8, i8, %struct.curl_llist, %struct.curl_llist, i8*, i64, i64, i32 (i8*, i64, i32)*, i8*, [256 x i8], i8*, i32, i32, %union.anon, i32, i32, i8*, i16, i32, [2 x i32], %struct.connectbundle*, i32 }
%struct.Curl_chunker = type { [17 x i8], i32, i32, i64, i64 }
%struct.Curl_dns_entry = type { %struct.Curl_addrinfo*, i64, i64 }
%struct.Curl_addrinfo = type { i32, i32, i32, i32, i32, i8*, %struct.sockaddr*, %struct.Curl_addrinfo* }
%struct.sockaddr = type { i16, [14 x i8] }
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
%union.anon = type { %struct.ftp_conn }
%struct.ftp_conn = type { %struct.pingpong, i8*, i8**, i32, i32, i8*, i8, i8, i8, i8, i8, i8*, i8, i32, i32, i32, i32, i32, i64, i8*, i64, i8*, i16 }
%struct.pingpong = type { i8*, i64, i64, i8*, i8, i8*, i64, i64, %struct.timeval, i64, %struct.connectdata*, i32 (%struct.connectdata*)*, i1 (%struct.connectdata*, i8*, i64, i32*)* }
%struct.connectbundle = type { i32, i64, %struct.curl_llist }
%struct.Curl_message = type { %struct.CURLMsg }
%struct.CURLMsg = type { i32, %struct.Curl_easy*, %union.anon.0 }
%union.anon.0 = type { i8* }
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
%struct.Curl_sockaddr_storage = type { %union.anon.1 }
%union.anon.1 = type { %struct.sockaddr_storage }
%struct.sockaddr_storage = type { i16, i64, [112 x i8] }
%struct.sockaddr_in = type { i16, i16, %struct.in_addr, [8 x i8] }
%struct.in_addr = type { i32 }
%struct.sockaddr_un = type { i16, [108 x i8] }
%struct.Curl_sockaddr_ex = type { i32, i32, i32, i32, %union.anon.2 }
%union.anon.2 = type { %struct.Curl_sockaddr_storage }
%struct.connfind = type { %struct.connectdata*, i8 }

@.str = private unnamed_addr constant [39 x i8] c"getpeername() failed with errno %d: %s\00", align 1
@.str.1 = private unnamed_addr constant [39 x i8] c"getsockname() failed with errno %d: %s\00", align 1
@.str.2 = private unnamed_addr constant [43 x i8] c"ssrem inet_ntop() failed with errno %d: %s\00", align 1
@.str.3 = private unnamed_addr constant [43 x i8] c"ssloc inet_ntop() failed with errno %d: %s\00", align 1
@.str.4 = private unnamed_addr constant [20 x i8] c"Connection time-out\00", align 1
@.str.5 = private unnamed_addr constant [36 x i8] c"After %ldms connect time, move on!\0A\00", align 1
@.str.6 = private unnamed_addr constant [19 x i8] c"Connection failed\0A\00", align 1
@.str.7 = private unnamed_addr constant [35 x i8] c"connect to %s port %ld failed: %s\0A\00", align 1
@.str.8 = private unnamed_addr constant [37 x i8] c"Failed to connect to %s port %ld: %s\00", align 1
@.str.9 = private unnamed_addr constant [31 x i8] c"Could not set TCP_NODELAY: %s\0A\00", align 1
@.str.10 = private unnamed_addr constant [17 x i8] c"TCP_NODELAY set\0A\00", align 1
@.str.11 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.12 = private unnamed_addr constant [45 x i8] c"sa_addr inet_ntop() failed with errno %d: %s\00", align 1
@.str.13 = private unnamed_addr constant [16 x i8] c"  Trying %s...\0A\00", align 1
@.str.14 = private unnamed_addr constant [35 x i8] c"Immediate connect fail for %s: %s\0A\00", align 1
@.str.15 = private unnamed_addr constant [37 x i8] c"Failed to set SO_KEEPALIVE on fd %d\0A\00", align 1
@.str.16 = private unnamed_addr constant [37 x i8] c"Failed to set TCP_KEEPIDLE on fd %d\0A\00", align 1
@.str.17 = private unnamed_addr constant [38 x i8] c"Failed to set TCP_KEEPINTVL on fd %d\0A\00", align 1
@bindlocal.if_prefix = internal global i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.18, i32 0, i32 0), align 8
@.str.18 = private unnamed_addr constant [4 x i8] c"if!\00", align 1
@bindlocal.host_prefix = internal global i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.19, i32 0, i32 0), align 8
@.str.19 = private unnamed_addr constant [6 x i8] c"host!\00", align 1
@.str.20 = private unnamed_addr constant [32 x i8] c"Couldn't bind to interface '%s'\00", align 1
@.str.21 = private unnamed_addr constant [53 x i8] c"Local Interface %s is ip %s using address family %i\0A\00", align 1
@.str.22 = private unnamed_addr constant [67 x i8] c"SO_BINDTODEVICE %s failed with errno %d: %s; will do regular bind\0A\00", align 1
@.str.23 = private unnamed_addr constant [48 x i8] c"Name '%s' family %i resolved to '%s' family %i\0A\00", align 1
@.str.24 = private unnamed_addr constant [22 x i8] c"Couldn't bind to '%s'\00", align 1
@.str.25 = private unnamed_addr constant [17 x i8] c"Local port: %hu\0A\00", align 1
@.str.26 = private unnamed_addr constant [44 x i8] c"Bind to local port %hu failed, trying next\0A\00", align 1
@.str.27 = private unnamed_addr constant [30 x i8] c"bind failed with errno %d: %s\00", align 1

; Function Attrs: nounwind uwtable
define i64 @Curl_timeleft(%struct.Curl_easy* %data, %struct.timeval* %nowp, i1 zeroext %duringconnect) #0 !dbg !1844 {
entry:
  %retval = alloca i64, align 8
  %data.addr = alloca %struct.Curl_easy*, align 8
  %nowp.addr = alloca %struct.timeval*, align 8
  %duringconnect.addr = alloca i8, align 1
  %timeout_set = alloca i32, align 4
  %timeout_ms = alloca i64, align 8
  %now = alloca %struct.timeval, align 8
  %coerce = alloca %struct.timeval, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !1943, metadata !1944), !dbg !1945
  store %struct.timeval* %nowp, %struct.timeval** %nowp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.timeval** %nowp.addr, metadata !1946, metadata !1944), !dbg !1947
  %frombool = zext i1 %duringconnect to i8
  store i8 %frombool, i8* %duringconnect.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %duringconnect.addr, metadata !1948, metadata !1944), !dbg !1949
  call void @llvm.dbg.declare(metadata i32* %timeout_set, metadata !1950, metadata !1944), !dbg !1951
  store i32 0, i32* %timeout_set, align 4, !dbg !1951
  call void @llvm.dbg.declare(metadata i64* %timeout_ms, metadata !1952, metadata !1944), !dbg !1953
  %0 = load i8, i8* %duringconnect.addr, align 1, !dbg !1954
  %tobool = trunc i8 %0 to i1, !dbg !1954
  %cond = select i1 %tobool, i32 300000, i32 0, !dbg !1954
  %conv = sext i32 %cond to i64, !dbg !1954
  store i64 %conv, i64* %timeout_ms, align 8, !dbg !1953
  call void @llvm.dbg.declare(metadata %struct.timeval* %now, metadata !1955, metadata !1944), !dbg !1956
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1957
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 13, !dbg !1959
  %timeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 42, !dbg !1960
  %2 = load i64, i64* %timeout, align 8, !dbg !1960
  %cmp = icmp sgt i64 %2, 0, !dbg !1961
  br i1 %cmp, label %if.then, label %if.end, !dbg !1962

if.then:                                          ; preds = %entry
  %3 = load i32, i32* %timeout_set, align 4, !dbg !1963
  %or = or i32 %3, 1, !dbg !1963
  store i32 %or, i32* %timeout_set, align 4, !dbg !1963
  br label %if.end, !dbg !1964

if.end:                                           ; preds = %if.then, %entry
  %4 = load i8, i8* %duringconnect.addr, align 1, !dbg !1965
  %tobool2 = trunc i8 %4 to i1, !dbg !1965
  br i1 %tobool2, label %land.lhs.true, label %if.end9, !dbg !1967

land.lhs.true:                                    ; preds = %if.end
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1968
  %set4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %5, i32 0, i32 13, !dbg !1970
  %connecttimeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set4, i32 0, i32 43, !dbg !1971
  %6 = load i64, i64* %connecttimeout, align 8, !dbg !1971
  %cmp5 = icmp sgt i64 %6, 0, !dbg !1972
  br i1 %cmp5, label %if.then7, label %if.end9, !dbg !1973

if.then7:                                         ; preds = %land.lhs.true
  %7 = load i32, i32* %timeout_set, align 4, !dbg !1974
  %or8 = or i32 %7, 2, !dbg !1974
  store i32 %or8, i32* %timeout_set, align 4, !dbg !1974
  br label %if.end9, !dbg !1975

if.end9:                                          ; preds = %if.then7, %land.lhs.true, %if.end
  %8 = load i32, i32* %timeout_set, align 4, !dbg !1976
  switch i32 %8, label %sw.default [
    i32 1, label %sw.bb
    i32 2, label %sw.bb12
    i32 3, label %sw.bb15
  ], !dbg !1977

sw.bb:                                            ; preds = %if.end9
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1978
  %set10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 13, !dbg !1980
  %timeout11 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set10, i32 0, i32 42, !dbg !1981
  %10 = load i64, i64* %timeout11, align 8, !dbg !1981
  store i64 %10, i64* %timeout_ms, align 8, !dbg !1982
  br label %sw.epilog, !dbg !1983

sw.bb12:                                          ; preds = %if.end9
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1984
  %set13 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 13, !dbg !1985
  %connecttimeout14 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set13, i32 0, i32 43, !dbg !1986
  %12 = load i64, i64* %connecttimeout14, align 8, !dbg !1986
  store i64 %12, i64* %timeout_ms, align 8, !dbg !1987
  br label %sw.epilog, !dbg !1988

sw.bb15:                                          ; preds = %if.end9
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1989
  %set16 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 13, !dbg !1991
  %timeout17 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set16, i32 0, i32 42, !dbg !1992
  %14 = load i64, i64* %timeout17, align 8, !dbg !1992
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1993
  %set18 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 13, !dbg !1994
  %connecttimeout19 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set18, i32 0, i32 43, !dbg !1995
  %16 = load i64, i64* %connecttimeout19, align 8, !dbg !1995
  %cmp20 = icmp slt i64 %14, %16, !dbg !1996
  br i1 %cmp20, label %if.then22, label %if.else, !dbg !1997

if.then22:                                        ; preds = %sw.bb15
  %17 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1998
  %set23 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %17, i32 0, i32 13, !dbg !1999
  %timeout24 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set23, i32 0, i32 42, !dbg !2000
  %18 = load i64, i64* %timeout24, align 8, !dbg !2000
  store i64 %18, i64* %timeout_ms, align 8, !dbg !2001
  br label %if.end27, !dbg !2002

if.else:                                          ; preds = %sw.bb15
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2003
  %set25 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %19, i32 0, i32 13, !dbg !2004
  %connecttimeout26 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set25, i32 0, i32 43, !dbg !2005
  %20 = load i64, i64* %connecttimeout26, align 8, !dbg !2005
  store i64 %20, i64* %timeout_ms, align 8, !dbg !2006
  br label %if.end27

if.end27:                                         ; preds = %if.else, %if.then22
  br label %sw.epilog, !dbg !2007

sw.default:                                       ; preds = %if.end9
  %21 = load i8, i8* %duringconnect.addr, align 1, !dbg !2008
  %tobool28 = trunc i8 %21 to i1, !dbg !2008
  br i1 %tobool28, label %if.end30, label %if.then29, !dbg !2010

if.then29:                                        ; preds = %sw.default
  store i64 0, i64* %retval, align 8, !dbg !2011
  br label %return, !dbg !2011

if.end30:                                         ; preds = %sw.default
  br label %sw.epilog, !dbg !2012

sw.epilog:                                        ; preds = %if.end30, %if.end27, %sw.bb12, %sw.bb
  %22 = load %struct.timeval*, %struct.timeval** %nowp.addr, align 8, !dbg !2013
  %tobool31 = icmp ne %struct.timeval* %22, null, !dbg !2013
  br i1 %tobool31, label %if.end33, label %if.then32, !dbg !2015

if.then32:                                        ; preds = %sw.epilog
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !2016
  %23 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !2016
  %24 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %23, i32 0, i32 0, !dbg !2016
  %25 = extractvalue { i64, i64 } %call, 0, !dbg !2016
  store i64 %25, i64* %24, align 8, !dbg !2016
  %26 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %23, i32 0, i32 1, !dbg !2016
  %27 = extractvalue { i64, i64 } %call, 1, !dbg !2016
  store i64 %27, i64* %26, align 8, !dbg !2016
  %28 = bitcast %struct.timeval* %now to i8*, !dbg !2016
  %29 = bitcast %struct.timeval* %coerce to i8*, !dbg !2016
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %28, i8* %29, i64 16, i32 8, i1 false), !dbg !2018
  store %struct.timeval* %now, %struct.timeval** %nowp.addr, align 8, !dbg !2020
  br label %if.end33, !dbg !2021

if.end33:                                         ; preds = %if.then32, %sw.epilog
  %30 = load i8, i8* %duringconnect.addr, align 1, !dbg !2022
  %tobool34 = trunc i8 %30 to i1, !dbg !2022
  br i1 %tobool34, label %if.then35, label %if.else37, !dbg !2024

if.then35:                                        ; preds = %if.end33
  %31 = load %struct.timeval*, %struct.timeval** %nowp.addr, align 8, !dbg !2025
  %32 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2025
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %32, i32 0, i32 16, !dbg !2025
  %t_startsingle = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 19, !dbg !2025
  %33 = bitcast %struct.timeval* %31 to { i64, i64 }*, !dbg !2025
  %34 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %33, i32 0, i32 0, !dbg !2025
  %35 = load i64, i64* %34, align 8, !dbg !2025
  %36 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %33, i32 0, i32 1, !dbg !2025
  %37 = load i64, i64* %36, align 8, !dbg !2025
  %38 = bitcast %struct.timeval* %t_startsingle to { i64, i64 }*, !dbg !2025
  %39 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %38, i32 0, i32 0, !dbg !2025
  %40 = load i64, i64* %39, align 8, !dbg !2025
  %41 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %38, i32 0, i32 1, !dbg !2025
  %42 = load i64, i64* %41, align 8, !dbg !2025
  %call36 = call i64 @curlx_tvdiff(i64 %35, i64 %37, i64 %40, i64 %42), !dbg !2025
  %43 = load i64, i64* %timeout_ms, align 8, !dbg !2026
  %sub = sub nsw i64 %43, %call36, !dbg !2026
  store i64 %sub, i64* %timeout_ms, align 8, !dbg !2026
  br label %if.end41, !dbg !2027

if.else37:                                        ; preds = %if.end33
  %44 = load %struct.timeval*, %struct.timeval** %nowp.addr, align 8, !dbg !2028
  %45 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2028
  %progress38 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %45, i32 0, i32 16, !dbg !2028
  %t_startop = getelementptr inbounds %struct.Progress, %struct.Progress* %progress38, i32 0, i32 20, !dbg !2028
  %46 = bitcast %struct.timeval* %44 to { i64, i64 }*, !dbg !2028
  %47 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %46, i32 0, i32 0, !dbg !2028
  %48 = load i64, i64* %47, align 8, !dbg !2028
  %49 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %46, i32 0, i32 1, !dbg !2028
  %50 = load i64, i64* %49, align 8, !dbg !2028
  %51 = bitcast %struct.timeval* %t_startop to { i64, i64 }*, !dbg !2028
  %52 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %51, i32 0, i32 0, !dbg !2028
  %53 = load i64, i64* %52, align 8, !dbg !2028
  %54 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %51, i32 0, i32 1, !dbg !2028
  %55 = load i64, i64* %54, align 8, !dbg !2028
  %call39 = call i64 @curlx_tvdiff(i64 %48, i64 %50, i64 %53, i64 %55), !dbg !2028
  %56 = load i64, i64* %timeout_ms, align 8, !dbg !2029
  %sub40 = sub nsw i64 %56, %call39, !dbg !2029
  store i64 %sub40, i64* %timeout_ms, align 8, !dbg !2029
  br label %if.end41

if.end41:                                         ; preds = %if.else37, %if.then35
  %57 = load i64, i64* %timeout_ms, align 8, !dbg !2030
  %tobool42 = icmp ne i64 %57, 0, !dbg !2030
  br i1 %tobool42, label %if.end44, label %if.then43, !dbg !2032

if.then43:                                        ; preds = %if.end41
  store i64 -1, i64* %retval, align 8, !dbg !2033
  br label %return, !dbg !2033

if.end44:                                         ; preds = %if.end41
  %58 = load i64, i64* %timeout_ms, align 8, !dbg !2034
  store i64 %58, i64* %retval, align 8, !dbg !2035
  br label %return, !dbg !2035

return:                                           ; preds = %if.end44, %if.then43, %if.then29
  %59 = load i64, i64* %retval, align 8, !dbg !2036
  ret i64 %59, !dbg !2036
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare { i64, i64 } @curlx_tvnow() #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

declare i64 @curlx_tvdiff(i64, i64, i64, i64) #2

; Function Attrs: nounwind uwtable
define void @Curl_persistconninfo(%struct.connectdata* %conn) #0 !dbg !1849 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2037, metadata !1944), !dbg !2038
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2039
  %data = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2040
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2040
  %info = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 19, !dbg !2041
  %conn_primary_ip = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info, i32 0, i32 12, !dbg !2042
  %arraydecay = getelementptr inbounds [46 x i8], [46 x i8]* %conn_primary_ip, i32 0, i32 0, !dbg !2043
  %2 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2044
  %primary_ip = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 21, !dbg !2045
  %arraydecay1 = getelementptr inbounds [46 x i8], [46 x i8]* %primary_ip, i32 0, i32 0, !dbg !2043
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay, i8* %arraydecay1, i64 46, i32 2, i1 false), !dbg !2043
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2046
  %data2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %3, i32 0, i32 0, !dbg !2047
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data2, align 8, !dbg !2047
  %info3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 19, !dbg !2048
  %conn_local_ip = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info3, i32 0, i32 14, !dbg !2049
  %arraydecay4 = getelementptr inbounds [46 x i8], [46 x i8]* %conn_local_ip, i32 0, i32 0, !dbg !2050
  %5 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2051
  %local_ip = getelementptr inbounds %struct.connectdata, %struct.connectdata* %5, i32 0, i32 23, !dbg !2052
  %arraydecay5 = getelementptr inbounds [46 x i8], [46 x i8]* %local_ip, i32 0, i32 0, !dbg !2050
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay4, i8* %arraydecay5, i64 46, i32 8, i1 false), !dbg !2050
  %6 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2053
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %6, i32 0, i32 47, !dbg !2054
  %7 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !2054
  %scheme = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %7, i32 0, i32 0, !dbg !2055
  %8 = load i8*, i8** %scheme, align 8, !dbg !2055
  %9 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2056
  %data6 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %9, i32 0, i32 0, !dbg !2057
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data6, align 8, !dbg !2057
  %info7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 19, !dbg !2058
  %conn_scheme = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info7, i32 0, i32 16, !dbg !2059
  store i8* %8, i8** %conn_scheme, align 8, !dbg !2060
  %11 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2061
  %handler8 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %11, i32 0, i32 47, !dbg !2062
  %12 = load %struct.Curl_handler*, %struct.Curl_handler** %handler8, align 8, !dbg !2062
  %protocol = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %12, i32 0, i32 15, !dbg !2063
  %13 = load i32, i32* %protocol, align 8, !dbg !2063
  %14 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2064
  %data9 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %14, i32 0, i32 0, !dbg !2065
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data9, align 8, !dbg !2065
  %info10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 19, !dbg !2066
  %conn_protocol = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info10, i32 0, i32 17, !dbg !2067
  store i32 %13, i32* %conn_protocol, align 8, !dbg !2068
  %16 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2069
  %primary_port = getelementptr inbounds %struct.connectdata, %struct.connectdata* %16, i32 0, i32 22, !dbg !2070
  %17 = load i64, i64* %primary_port, align 8, !dbg !2070
  %18 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2071
  %data11 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %18, i32 0, i32 0, !dbg !2072
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %data11, align 8, !dbg !2072
  %info12 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %19, i32 0, i32 19, !dbg !2073
  %conn_primary_port = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info12, i32 0, i32 13, !dbg !2074
  store i64 %17, i64* %conn_primary_port, align 8, !dbg !2075
  %20 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2076
  %local_port = getelementptr inbounds %struct.connectdata, %struct.connectdata* %20, i32 0, i32 24, !dbg !2077
  %21 = load i64, i64* %local_port, align 8, !dbg !2077
  %22 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2078
  %data13 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %22, i32 0, i32 0, !dbg !2079
  %23 = load %struct.Curl_easy*, %struct.Curl_easy** %data13, align 8, !dbg !2079
  %info14 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %23, i32 0, i32 19, !dbg !2080
  %conn_local_port = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info14, i32 0, i32 15, !dbg !2081
  store i64 %21, i64* %conn_local_port, align 8, !dbg !2082
  ret void, !dbg !2083
}

; Function Attrs: nounwind uwtable
define void @Curl_updateconninfo(%struct.connectdata* %conn, i32 %sockfd) #0 !dbg !1852 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockfd.addr = alloca i32, align 4
  %len = alloca i32, align 4
  %ssrem = alloca %struct.Curl_sockaddr_storage, align 8
  %ssloc = alloca %struct.Curl_sockaddr_storage, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %error = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2084, metadata !1944), !dbg !2085
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !2086, metadata !1944), !dbg !2087
  call void @llvm.dbg.declare(metadata i32* %len, metadata !2088, metadata !1944), !dbg !2089
  call void @llvm.dbg.declare(metadata %struct.Curl_sockaddr_storage* %ssrem, metadata !2090, metadata !1944), !dbg !2091
  call void @llvm.dbg.declare(metadata %struct.Curl_sockaddr_storage* %ssloc, metadata !2092, metadata !1944), !dbg !2093
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2094, metadata !1944), !dbg !2095
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2096
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2097
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2097
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2095
  %2 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2098
  %socktype = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 11, !dbg !2100
  %3 = load i32, i32* %socktype, align 4, !dbg !2100
  %cmp = icmp eq i32 %3, 2, !dbg !2101
  br i1 %cmp, label %if.then, label %if.end, !dbg !2102

if.then:                                          ; preds = %entry
  br label %return, !dbg !2103

if.end:                                           ; preds = %entry
  %4 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2104
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %4, i32 0, i32 43, !dbg !2106
  %reuse = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 1, !dbg !2107
  %5 = load i8, i8* %reuse, align 1, !dbg !2107
  %tobool = trunc i8 %5 to i1, !dbg !2107
  br i1 %tobool, label %if.end30, label %land.lhs.true, !dbg !2108

land.lhs.true:                                    ; preds = %if.end
  %6 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2109
  %bits2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %6, i32 0, i32 43, !dbg !2111
  %tcp_fastopen = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits2, i32 0, i32 28, !dbg !2112
  %7 = load i8, i8* %tcp_fastopen, align 1, !dbg !2112
  %tobool3 = trunc i8 %7 to i1, !dbg !2112
  br i1 %tobool3, label %if.end30, label %if.then4, !dbg !2113

if.then4:                                         ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i32* %error, metadata !2114, metadata !1944), !dbg !2116
  store i32 128, i32* %len, align 4, !dbg !2117
  %8 = load i32, i32* %sockfd.addr, align 4, !dbg !2118
  %9 = bitcast %struct.Curl_sockaddr_storage* %ssrem to %struct.sockaddr*, !dbg !2120
  %call = call i32 @getpeername(i32 %8, %struct.sockaddr* %9, i32* %len) #7, !dbg !2121
  %tobool5 = icmp ne i32 %call, 0, !dbg !2121
  br i1 %tobool5, label %if.then6, label %if.end9, !dbg !2122

if.then6:                                         ; preds = %if.then4
  %call7 = call i32* @__errno_location() #1, !dbg !2123
  %10 = load i32, i32* %call7, align 4, !dbg !2123
  store i32 %10, i32* %error, align 4, !dbg !2125
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2126
  %12 = load i32, i32* %error, align 4, !dbg !2127
  %13 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2128
  %14 = load i32, i32* %error, align 4, !dbg !2129
  %call8 = call i8* @Curl_strerror(%struct.connectdata* %13, i32 %14), !dbg !2130
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %11, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str, i32 0, i32 0), i32 %12, i8* %call8), !dbg !2131
  br label %return, !dbg !2132

if.end9:                                          ; preds = %if.then4
  store i32 128, i32* %len, align 4, !dbg !2133
  %15 = bitcast %struct.Curl_sockaddr_storage* %ssloc to i8*, !dbg !2134
  call void @llvm.memset.p0i8.i64(i8* %15, i8 0, i64 128, i32 8, i1 false), !dbg !2134
  %16 = load i32, i32* %sockfd.addr, align 4, !dbg !2135
  %17 = bitcast %struct.Curl_sockaddr_storage* %ssloc to %struct.sockaddr*, !dbg !2137
  %call10 = call i32 @getsockname(i32 %16, %struct.sockaddr* %17, i32* %len) #7, !dbg !2138
  %tobool11 = icmp ne i32 %call10, 0, !dbg !2138
  br i1 %tobool11, label %if.then12, label %if.end15, !dbg !2139

if.then12:                                        ; preds = %if.end9
  %call13 = call i32* @__errno_location() #1, !dbg !2140
  %18 = load i32, i32* %call13, align 4, !dbg !2140
  store i32 %18, i32* %error, align 4, !dbg !2142
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2143
  %20 = load i32, i32* %error, align 4, !dbg !2144
  %21 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2145
  %22 = load i32, i32* %error, align 4, !dbg !2146
  %call14 = call i8* @Curl_strerror(%struct.connectdata* %21, i32 %22), !dbg !2147
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %19, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.1, i32 0, i32 0), i32 %20, i8* %call14), !dbg !2148
  br label %return, !dbg !2149

if.end15:                                         ; preds = %if.end9
  %23 = bitcast %struct.Curl_sockaddr_storage* %ssrem to %struct.sockaddr*, !dbg !2150
  %24 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2152
  %primary_ip = getelementptr inbounds %struct.connectdata, %struct.connectdata* %24, i32 0, i32 21, !dbg !2153
  %arraydecay = getelementptr inbounds [46 x i8], [46 x i8]* %primary_ip, i32 0, i32 0, !dbg !2152
  %25 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2154
  %primary_port = getelementptr inbounds %struct.connectdata, %struct.connectdata* %25, i32 0, i32 22, !dbg !2155
  %call16 = call zeroext i1 @getaddressinfo(%struct.sockaddr* %23, i8* %arraydecay, i64* %primary_port), !dbg !2156
  br i1 %call16, label %if.end20, label %if.then17, !dbg !2157

if.then17:                                        ; preds = %if.end15
  %call18 = call i32* @__errno_location() #1, !dbg !2158
  %26 = load i32, i32* %call18, align 4, !dbg !2158
  store i32 %26, i32* %error, align 4, !dbg !2160
  %27 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2161
  %28 = load i32, i32* %error, align 4, !dbg !2162
  %29 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2163
  %30 = load i32, i32* %error, align 4, !dbg !2164
  %call19 = call i8* @Curl_strerror(%struct.connectdata* %29, i32 %30), !dbg !2165
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %27, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.2, i32 0, i32 0), i32 %28, i8* %call19), !dbg !2166
  br label %return, !dbg !2167

if.end20:                                         ; preds = %if.end15
  %31 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2168
  %ip_addr_str = getelementptr inbounds %struct.connectdata, %struct.connectdata* %31, i32 0, i32 9, !dbg !2169
  %arraydecay21 = getelementptr inbounds [46 x i8], [46 x i8]* %ip_addr_str, i32 0, i32 0, !dbg !2170
  %32 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2171
  %primary_ip22 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %32, i32 0, i32 21, !dbg !2172
  %arraydecay23 = getelementptr inbounds [46 x i8], [46 x i8]* %primary_ip22, i32 0, i32 0, !dbg !2170
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %arraydecay21, i8* %arraydecay23, i64 46, i32 2, i1 false), !dbg !2170
  %33 = bitcast %struct.Curl_sockaddr_storage* %ssloc to %struct.sockaddr*, !dbg !2173
  %34 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2175
  %local_ip = getelementptr inbounds %struct.connectdata, %struct.connectdata* %34, i32 0, i32 23, !dbg !2176
  %arraydecay24 = getelementptr inbounds [46 x i8], [46 x i8]* %local_ip, i32 0, i32 0, !dbg !2175
  %35 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2177
  %local_port = getelementptr inbounds %struct.connectdata, %struct.connectdata* %35, i32 0, i32 24, !dbg !2178
  %call25 = call zeroext i1 @getaddressinfo(%struct.sockaddr* %33, i8* %arraydecay24, i64* %local_port), !dbg !2179
  br i1 %call25, label %if.end29, label %if.then26, !dbg !2180

if.then26:                                        ; preds = %if.end20
  %call27 = call i32* @__errno_location() #1, !dbg !2181
  %36 = load i32, i32* %call27, align 4, !dbg !2181
  store i32 %36, i32* %error, align 4, !dbg !2183
  %37 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2184
  %38 = load i32, i32* %error, align 4, !dbg !2185
  %39 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2186
  %40 = load i32, i32* %error, align 4, !dbg !2187
  %call28 = call i8* @Curl_strerror(%struct.connectdata* %39, i32 %40), !dbg !2188
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %37, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.3, i32 0, i32 0), i32 %38, i8* %call28), !dbg !2189
  br label %return, !dbg !2190

if.end29:                                         ; preds = %if.end20
  br label %if.end30, !dbg !2191

if.end30:                                         ; preds = %if.end29, %land.lhs.true, %if.end
  %41 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2192
  call void @Curl_persistconninfo(%struct.connectdata* %41), !dbg !2193
  br label %return, !dbg !2194

return:                                           ; preds = %if.end30, %if.then26, %if.then17, %if.then12, %if.then6, %if.then
  ret void, !dbg !2195
}

; Function Attrs: nounwind
declare i32 @getpeername(i32, %struct.sockaddr*, i32*) #4

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare void @Curl_failf(%struct.Curl_easy*, i8*, ...) #2

declare i8* @Curl_strerror(%struct.connectdata*, i32) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #3

; Function Attrs: nounwind
declare i32 @getsockname(i32, %struct.sockaddr*, i32*) #4

; Function Attrs: nounwind uwtable
define internal zeroext i1 @getaddressinfo(%struct.sockaddr* %sa, i8* %addr, i64* %port) #0 !dbg !1915 {
entry:
  %retval = alloca i1, align 1
  %sa.addr = alloca %struct.sockaddr*, align 8
  %addr.addr = alloca i8*, align 8
  %port.addr = alloca i64*, align 8
  %us_port = alloca i16, align 2
  %si = alloca %struct.sockaddr_in*, align 8
  %su = alloca %struct.sockaddr_un*, align 8
  store %struct.sockaddr* %sa, %struct.sockaddr** %sa.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %sa.addr, metadata !2197, metadata !1944), !dbg !2198
  store i8* %addr, i8** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %addr.addr, metadata !2199, metadata !1944), !dbg !2200
  store i64* %port, i64** %port.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %port.addr, metadata !2201, metadata !1944), !dbg !2202
  call void @llvm.dbg.declare(metadata i16* %us_port, metadata !2203, metadata !1944), !dbg !2204
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in** %si, metadata !2205, metadata !1944), !dbg !2206
  store %struct.sockaddr_in* null, %struct.sockaddr_in** %si, align 8, !dbg !2206
  call void @llvm.dbg.declare(metadata %struct.sockaddr_un** %su, metadata !2207, metadata !1944), !dbg !2208
  store %struct.sockaddr_un* null, %struct.sockaddr_un** %su, align 8, !dbg !2208
  %0 = load %struct.sockaddr*, %struct.sockaddr** %sa.addr, align 8, !dbg !2209
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %0, i32 0, i32 0, !dbg !2210
  %1 = load i16, i16* %sa_family, align 2, !dbg !2210
  %conv = zext i16 %1 to i32, !dbg !2209
  switch i32 %conv, label %sw.default [
    i32 2, label %sw.bb
    i32 1, label %sw.bb5
  ], !dbg !2211

sw.bb:                                            ; preds = %entry
  %2 = load %struct.sockaddr*, %struct.sockaddr** %sa.addr, align 8, !dbg !2212
  %3 = bitcast %struct.sockaddr* %2 to i8*, !dbg !2214
  %4 = bitcast i8* %3 to %struct.sockaddr_in*, !dbg !2215
  store %struct.sockaddr_in* %4, %struct.sockaddr_in** %si, align 8, !dbg !2216
  %5 = load %struct.sockaddr*, %struct.sockaddr** %sa.addr, align 8, !dbg !2217
  %sa_family1 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %5, i32 0, i32 0, !dbg !2219
  %6 = load i16, i16* %sa_family1, align 2, !dbg !2219
  %conv2 = zext i16 %6 to i32, !dbg !2217
  %7 = load %struct.sockaddr_in*, %struct.sockaddr_in** %si, align 8, !dbg !2220
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %7, i32 0, i32 2, !dbg !2221
  %8 = bitcast %struct.in_addr* %sin_addr to i8*, !dbg !2222
  %9 = load i8*, i8** %addr.addr, align 8, !dbg !2223
  %call = call i8* @Curl_inet_ntop(i32 %conv2, i8* %8, i8* %9, i64 46), !dbg !2224
  %tobool = icmp ne i8* %call, null, !dbg !2224
  br i1 %tobool, label %if.then, label %if.end, !dbg !2225

if.then:                                          ; preds = %sw.bb
  %10 = load %struct.sockaddr_in*, %struct.sockaddr_in** %si, align 8, !dbg !2226
  %sin_port = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %10, i32 0, i32 1, !dbg !2228
  %11 = load i16, i16* %sin_port, align 2, !dbg !2228
  %call3 = call zeroext i16 @ntohs(i16 zeroext %11) #1, !dbg !2229
  store i16 %call3, i16* %us_port, align 2, !dbg !2230
  %12 = load i16, i16* %us_port, align 2, !dbg !2231
  %conv4 = zext i16 %12 to i64, !dbg !2231
  %13 = load i64*, i64** %port.addr, align 8, !dbg !2232
  store i64 %conv4, i64* %13, align 8, !dbg !2233
  store i1 true, i1* %retval, align 1, !dbg !2234
  br label %return, !dbg !2234

if.end:                                           ; preds = %sw.bb
  br label %sw.epilog, !dbg !2235

sw.bb5:                                           ; preds = %entry
  %14 = load %struct.sockaddr*, %struct.sockaddr** %sa.addr, align 8, !dbg !2236
  %15 = bitcast %struct.sockaddr* %14 to %struct.sockaddr_un*, !dbg !2237
  store %struct.sockaddr_un* %15, %struct.sockaddr_un** %su, align 8, !dbg !2238
  %16 = load i8*, i8** %addr.addr, align 8, !dbg !2239
  %17 = load %struct.sockaddr_un*, %struct.sockaddr_un** %su, align 8, !dbg !2240
  %sun_path = getelementptr inbounds %struct.sockaddr_un, %struct.sockaddr_un* %17, i32 0, i32 1, !dbg !2241
  %arraydecay = getelementptr inbounds [108 x i8], [108 x i8]* %sun_path, i32 0, i32 0, !dbg !2240
  %call6 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %16, i64 46, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i32 0, i32 0), i8* %arraydecay), !dbg !2242
  %18 = load i64*, i64** %port.addr, align 8, !dbg !2243
  store i64 0, i64* %18, align 8, !dbg !2244
  store i1 true, i1* %retval, align 1, !dbg !2245
  br label %return, !dbg !2245

sw.default:                                       ; preds = %entry
  br label %sw.epilog, !dbg !2246

sw.epilog:                                        ; preds = %sw.default, %if.end
  %19 = load i8*, i8** %addr.addr, align 8, !dbg !2247
  %arrayidx = getelementptr inbounds i8, i8* %19, i64 0, !dbg !2247
  store i8 0, i8* %arrayidx, align 1, !dbg !2248
  %20 = load i64*, i64** %port.addr, align 8, !dbg !2249
  store i64 0, i64* %20, align 8, !dbg !2250
  store i1 false, i1* %retval, align 1, !dbg !2251
  br label %return, !dbg !2251

return:                                           ; preds = %sw.epilog, %sw.bb5, %if.then
  %21 = load i1, i1* %retval, align 1, !dbg !2252
  ret i1 %21, !dbg !2252
}

; Function Attrs: nounwind uwtable
define i32 @Curl_is_connected(%struct.connectdata* %conn, i32 %sockindex, i8* %connected) #0 !dbg !1855 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockindex.addr = alloca i32, align 4
  %connected.addr = alloca i8*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %result = alloca i32, align 4
  %allow = alloca i64, align 8
  %error = alloca i32, align 4
  %now = alloca %struct.timeval, align 8
  %rc = alloca i32, align 4
  %i = alloca i32, align 4
  %coerce = alloca %struct.timeval, align 8
  %other = alloca i32, align 4
  %status = alloca i32, align 4
  %ipaddress = alloca [46 x i8], align 16
  %hostname = alloca i8*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2253, metadata !1944), !dbg !2254
  store i32 %sockindex, i32* %sockindex.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockindex.addr, metadata !2255, metadata !1944), !dbg !2256
  store i8* %connected, i8** %connected.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %connected.addr, metadata !2257, metadata !1944), !dbg !2258
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2259, metadata !1944), !dbg !2260
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2261
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2262
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2262
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2260
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2263, metadata !1944), !dbg !2264
  store i32 0, i32* %result, align 4, !dbg !2264
  call void @llvm.dbg.declare(metadata i64* %allow, metadata !2265, metadata !1944), !dbg !2266
  call void @llvm.dbg.declare(metadata i32* %error, metadata !2267, metadata !1944), !dbg !2268
  store i32 0, i32* %error, align 4, !dbg !2268
  call void @llvm.dbg.declare(metadata %struct.timeval* %now, metadata !2269, metadata !1944), !dbg !2270
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !2271, metadata !1944), !dbg !2272
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2273, metadata !1944), !dbg !2274
  br label %do.body, !dbg !2275

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !2276

do.end:                                           ; preds = %do.body
  %2 = load i8*, i8** %connected.addr, align 8, !dbg !2279
  store i8 0, i8* %2, align 1, !dbg !2280
  %3 = load i32, i32* %sockindex.addr, align 4, !dbg !2281
  %idxprom = sext i32 %3 to i64, !dbg !2283
  %4 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2283
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %4, i32 0, i32 43, !dbg !2284
  %tcpconnect = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 12, !dbg !2285
  %arrayidx = getelementptr inbounds [2 x i8], [2 x i8]* %tcpconnect, i64 0, i64 %idxprom, !dbg !2283
  %5 = load i8, i8* %arrayidx, align 1, !dbg !2283
  %tobool = trunc i8 %5 to i1, !dbg !2283
  br i1 %tobool, label %if.then, label %if.end, !dbg !2286

if.then:                                          ; preds = %do.end
  %6 = load i8*, i8** %connected.addr, align 8, !dbg !2287
  store i8 1, i8* %6, align 1, !dbg !2289
  store i32 0, i32* %retval, align 4, !dbg !2290
  br label %return, !dbg !2290

if.end:                                           ; preds = %do.end
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !2291
  %7 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !2291
  %8 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %7, i32 0, i32 0, !dbg !2291
  %9 = extractvalue { i64, i64 } %call, 0, !dbg !2291
  store i64 %9, i64* %8, align 8, !dbg !2291
  %10 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %7, i32 0, i32 1, !dbg !2291
  %11 = extractvalue { i64, i64 } %call, 1, !dbg !2291
  store i64 %11, i64* %10, align 8, !dbg !2291
  %12 = bitcast %struct.timeval* %now to i8*, !dbg !2291
  %13 = bitcast %struct.timeval* %coerce to i8*, !dbg !2291
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %12, i8* %13, i64 16, i32 8, i1 false), !dbg !2292
  %14 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2294
  %call2 = call i64 @Curl_timeleft(%struct.Curl_easy* %14, %struct.timeval* %now, i1 zeroext true), !dbg !2295
  store i64 %call2, i64* %allow, align 8, !dbg !2296
  %15 = load i64, i64* %allow, align 8, !dbg !2297
  %cmp = icmp slt i64 %15, 0, !dbg !2299
  br i1 %cmp, label %if.then3, label %if.end4, !dbg !2300

if.then3:                                         ; preds = %if.end
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2301
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %16, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.4, i32 0, i32 0)), !dbg !2303
  store i32 28, i32* %retval, align 4, !dbg !2304
  br label %return, !dbg !2304

if.end4:                                          ; preds = %if.end
  store i32 0, i32* %i, align 4, !dbg !2305
  br label %for.cond, !dbg !2307

for.cond:                                         ; preds = %for.inc, %if.end4
  %17 = load i32, i32* %i, align 4, !dbg !2308
  %cmp5 = icmp slt i32 %17, 2, !dbg !2311
  br i1 %cmp5, label %for.body, label %for.end, !dbg !2312

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i32* %other, metadata !2313, metadata !1944), !dbg !2316
  %18 = load i32, i32* %i, align 4, !dbg !2317
  %xor = xor i32 %18, 1, !dbg !2318
  store i32 %xor, i32* %other, align 4, !dbg !2316
  %19 = load i32, i32* %i, align 4, !dbg !2319
  %idxprom6 = sext i32 %19 to i64, !dbg !2321
  %20 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2321
  %tempsock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %20, i32 0, i32 34, !dbg !2322
  %arrayidx7 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock, i64 0, i64 %idxprom6, !dbg !2321
  %21 = load i32, i32* %arrayidx7, align 4, !dbg !2321
  %cmp8 = icmp eq i32 %21, -1, !dbg !2323
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !2324

if.then9:                                         ; preds = %for.body
  br label %for.inc, !dbg !2325

if.end10:                                         ; preds = %for.body
  %22 = load i32, i32* %i, align 4, !dbg !2326
  %idxprom11 = sext i32 %22 to i64, !dbg !2326
  %23 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2326
  %tempsock12 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %23, i32 0, i32 34, !dbg !2326
  %arrayidx13 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock12, i64 0, i64 %idxprom11, !dbg !2326
  %24 = load i32, i32* %arrayidx13, align 4, !dbg !2326
  %call14 = call i32 @Curl_socket_check(i32 -1, i32 -1, i32 %24, i64 0), !dbg !2326
  store i32 %call14, i32* %rc, align 4, !dbg !2327
  %25 = load i32, i32* %rc, align 4, !dbg !2328
  %cmp15 = icmp eq i32 %25, 0, !dbg !2330
  br i1 %cmp15, label %if.then16, label %if.else, !dbg !2331

if.then16:                                        ; preds = %if.end10
  store i32 0, i32* %error, align 4, !dbg !2332
  %26 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2334
  %connecttime = getelementptr inbounds %struct.connectdata, %struct.connectdata* %26, i32 0, i32 44, !dbg !2336
  %27 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2337
  %28 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %27, i32 0, i32 0, !dbg !2337
  %29 = load i64, i64* %28, align 8, !dbg !2337
  %30 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %27, i32 0, i32 1, !dbg !2337
  %31 = load i64, i64* %30, align 8, !dbg !2337
  %32 = bitcast %struct.timeval* %connecttime to { i64, i64 }*, !dbg !2337
  %33 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %32, i32 0, i32 0, !dbg !2337
  %34 = load i64, i64* %33, align 8, !dbg !2337
  %35 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %32, i32 0, i32 1, !dbg !2337
  %36 = load i64, i64* %35, align 8, !dbg !2337
  %call17 = call i64 @curlx_tvdiff(i64 %29, i64 %31, i64 %34, i64 %36), !dbg !2337
  %37 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2338
  %timeoutms_per_addr = getelementptr inbounds %struct.connectdata, %struct.connectdata* %37, i32 0, i32 46, !dbg !2339
  %38 = load i64, i64* %timeoutms_per_addr, align 8, !dbg !2339
  %cmp18 = icmp sge i64 %call17, %38, !dbg !2340
  br i1 %cmp18, label %if.then19, label %if.end21, !dbg !2341

if.then19:                                        ; preds = %if.then16
  %39 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2342
  %40 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2344
  %timeoutms_per_addr20 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %40, i32 0, i32 46, !dbg !2345
  %41 = load i64, i64* %timeoutms_per_addr20, align 8, !dbg !2345
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %39, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.5, i32 0, i32 0), i64 %41), !dbg !2346
  store i32 110, i32* %error, align 4, !dbg !2347
  br label %if.end21, !dbg !2348

if.end21:                                         ; preds = %if.then19, %if.then16
  %42 = load i32, i32* %i, align 4, !dbg !2349
  %cmp22 = icmp eq i32 %42, 0, !dbg !2351
  br i1 %cmp22, label %land.lhs.true, label %if.end31, !dbg !2352

land.lhs.true:                                    ; preds = %if.end21
  %43 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2353
  %tempaddr = getelementptr inbounds %struct.connectdata, %struct.connectdata* %43, i32 0, i32 8, !dbg !2355
  %arrayidx23 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr, i64 0, i64 1, !dbg !2353
  %44 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx23, align 8, !dbg !2353
  %cmp24 = icmp eq %struct.Curl_addrinfo* %44, null, !dbg !2356
  br i1 %cmp24, label %land.lhs.true25, label %if.end31, !dbg !2357

land.lhs.true25:                                  ; preds = %land.lhs.true
  %45 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2358
  %connecttime26 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %45, i32 0, i32 44, !dbg !2359
  %46 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2360
  %47 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %46, i32 0, i32 0, !dbg !2360
  %48 = load i64, i64* %47, align 8, !dbg !2360
  %49 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %46, i32 0, i32 1, !dbg !2360
  %50 = load i64, i64* %49, align 8, !dbg !2360
  %51 = bitcast %struct.timeval* %connecttime26 to { i64, i64 }*, !dbg !2360
  %52 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %51, i32 0, i32 0, !dbg !2360
  %53 = load i64, i64* %52, align 8, !dbg !2360
  %54 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %51, i32 0, i32 1, !dbg !2360
  %55 = load i64, i64* %54, align 8, !dbg !2360
  %call27 = call i64 @curlx_tvdiff(i64 %48, i64 %50, i64 %53, i64 %55), !dbg !2360
  %cmp28 = icmp sge i64 %call27, 200, !dbg !2361
  br i1 %cmp28, label %if.then29, label %if.end31, !dbg !2362

if.then29:                                        ; preds = %land.lhs.true25
  %56 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2364
  %57 = load i32, i32* %sockindex.addr, align 4, !dbg !2366
  %call30 = call i32 @trynextip(%struct.connectdata* %56, i32 %57, i32 1), !dbg !2367
  br label %if.end31, !dbg !2368

if.end31:                                         ; preds = %if.then29, %land.lhs.true25, %land.lhs.true, %if.end21
  br label %if.end89, !dbg !2369

if.else:                                          ; preds = %if.end10
  %58 = load i32, i32* %rc, align 4, !dbg !2370
  %cmp32 = icmp eq i32 %58, 2, !dbg !2372
  br i1 %cmp32, label %if.then35, label %lor.lhs.false, !dbg !2373

lor.lhs.false:                                    ; preds = %if.else
  %59 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2374
  %bits33 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %59, i32 0, i32 43, !dbg !2376
  %tcp_fastopen = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits33, i32 0, i32 28, !dbg !2377
  %60 = load i8, i8* %tcp_fastopen, align 1, !dbg !2377
  %tobool34 = trunc i8 %60 to i1, !dbg !2377
  br i1 %tobool34, label %if.then35, label %if.else80, !dbg !2378

if.then35:                                        ; preds = %lor.lhs.false, %if.else
  %61 = load i32, i32* %i, align 4, !dbg !2379
  %idxprom36 = sext i32 %61 to i64, !dbg !2382
  %62 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2382
  %tempsock37 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %62, i32 0, i32 34, !dbg !2383
  %arrayidx38 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock37, i64 0, i64 %idxprom36, !dbg !2382
  %63 = load i32, i32* %arrayidx38, align 4, !dbg !2382
  %call39 = call zeroext i1 @verifyconnect(i32 %63, i32* %error), !dbg !2384
  br i1 %call39, label %if.then40, label %if.end79, !dbg !2385

if.then40:                                        ; preds = %if.then35
  %64 = load i32, i32* %i, align 4, !dbg !2386
  %idxprom41 = sext i32 %64 to i64, !dbg !2388
  %65 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2388
  %tempsock42 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %65, i32 0, i32 34, !dbg !2389
  %arrayidx43 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock42, i64 0, i64 %idxprom41, !dbg !2388
  %66 = load i32, i32* %arrayidx43, align 4, !dbg !2388
  %67 = load i32, i32* %sockindex.addr, align 4, !dbg !2390
  %idxprom44 = sext i32 %67 to i64, !dbg !2391
  %68 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2391
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %68, i32 0, i32 33, !dbg !2392
  %arrayidx45 = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 %idxprom44, !dbg !2391
  store i32 %66, i32* %arrayidx45, align 4, !dbg !2393
  %69 = load i32, i32* %i, align 4, !dbg !2394
  %idxprom46 = sext i32 %69 to i64, !dbg !2395
  %70 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2395
  %tempaddr47 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %70, i32 0, i32 8, !dbg !2396
  %arrayidx48 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr47, i64 0, i64 %idxprom46, !dbg !2395
  %71 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx48, align 8, !dbg !2395
  %72 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2397
  %ip_addr = getelementptr inbounds %struct.connectdata, %struct.connectdata* %72, i32 0, i32 7, !dbg !2398
  store %struct.Curl_addrinfo* %71, %struct.Curl_addrinfo** %ip_addr, align 8, !dbg !2399
  %73 = load i32, i32* %i, align 4, !dbg !2400
  %idxprom49 = sext i32 %73 to i64, !dbg !2401
  %74 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2401
  %tempsock50 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %74, i32 0, i32 34, !dbg !2402
  %arrayidx51 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock50, i64 0, i64 %idxprom49, !dbg !2401
  store i32 -1, i32* %arrayidx51, align 4, !dbg !2403
  %75 = load i32, i32* %other, align 4, !dbg !2404
  %idxprom52 = sext i32 %75 to i64, !dbg !2406
  %76 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2406
  %tempsock53 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %76, i32 0, i32 34, !dbg !2407
  %arrayidx54 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock53, i64 0, i64 %idxprom52, !dbg !2406
  %77 = load i32, i32* %arrayidx54, align 4, !dbg !2406
  %cmp55 = icmp ne i32 %77, -1, !dbg !2408
  br i1 %cmp55, label %if.then56, label %if.end64, !dbg !2409

if.then56:                                        ; preds = %if.then40
  %78 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2410
  %79 = load i32, i32* %other, align 4, !dbg !2412
  %idxprom57 = sext i32 %79 to i64, !dbg !2413
  %80 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2413
  %tempsock58 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %80, i32 0, i32 34, !dbg !2414
  %arrayidx59 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock58, i64 0, i64 %idxprom57, !dbg !2413
  %81 = load i32, i32* %arrayidx59, align 4, !dbg !2413
  %call60 = call i32 @Curl_closesocket(%struct.connectdata* %78, i32 %81), !dbg !2415
  %82 = load i32, i32* %other, align 4, !dbg !2416
  %idxprom61 = sext i32 %82 to i64, !dbg !2417
  %83 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2417
  %tempsock62 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %83, i32 0, i32 34, !dbg !2418
  %arrayidx63 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock62, i64 0, i64 %idxprom61, !dbg !2417
  store i32 -1, i32* %arrayidx63, align 4, !dbg !2419
  br label %if.end64, !dbg !2420

if.end64:                                         ; preds = %if.then56, %if.then40
  %84 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2421
  %85 = load i32, i32* %sockindex.addr, align 4, !dbg !2422
  %call65 = call i32 @Curl_connected_proxy(%struct.connectdata* %84, i32 %85), !dbg !2423
  store i32 %call65, i32* %result, align 4, !dbg !2424
  %86 = load i32, i32* %result, align 4, !dbg !2425
  %tobool66 = icmp ne i32 %86, 0, !dbg !2425
  br i1 %tobool66, label %if.then67, label %if.end68, !dbg !2427

if.then67:                                        ; preds = %if.end64
  %87 = load i32, i32* %result, align 4, !dbg !2428
  store i32 %87, i32* %retval, align 4, !dbg !2429
  br label %return, !dbg !2429

if.end68:                                         ; preds = %if.end64
  %88 = load i32, i32* %sockindex.addr, align 4, !dbg !2430
  %idxprom69 = sext i32 %88 to i64, !dbg !2431
  %89 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2431
  %bits70 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %89, i32 0, i32 43, !dbg !2432
  %tcpconnect71 = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits70, i32 0, i32 12, !dbg !2433
  %arrayidx72 = getelementptr inbounds [2 x i8], [2 x i8]* %tcpconnect71, i64 0, i64 %idxprom69, !dbg !2431
  store i8 1, i8* %arrayidx72, align 1, !dbg !2434
  %90 = load i8*, i8** %connected.addr, align 8, !dbg !2435
  store i8 1, i8* %90, align 1, !dbg !2436
  %91 = load i32, i32* %sockindex.addr, align 4, !dbg !2437
  %cmp73 = icmp eq i32 %91, 0, !dbg !2439
  br i1 %cmp73, label %if.then74, label %if.end75, !dbg !2440

if.then74:                                        ; preds = %if.end68
  %92 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2441
  call void @Curl_pgrsTime(%struct.Curl_easy* %92, i32 4), !dbg !2442
  br label %if.end75, !dbg !2442

if.end75:                                         ; preds = %if.then74, %if.end68
  %93 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2443
  %94 = load i32, i32* %sockindex.addr, align 4, !dbg !2444
  %idxprom76 = sext i32 %94 to i64, !dbg !2445
  %95 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2445
  %sock77 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %95, i32 0, i32 33, !dbg !2446
  %arrayidx78 = getelementptr inbounds [2 x i32], [2 x i32]* %sock77, i64 0, i64 %idxprom76, !dbg !2445
  %96 = load i32, i32* %arrayidx78, align 4, !dbg !2445
  call void @Curl_updateconninfo(%struct.connectdata* %93, i32 %96), !dbg !2447
  %97 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2448
  call void @Curl_verboseconnect(%struct.connectdata* %97), !dbg !2449
  store i32 0, i32* %retval, align 4, !dbg !2450
  br label %return, !dbg !2450

if.end79:                                         ; preds = %if.then35
  %98 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2451
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %98, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.6, i32 0, i32 0)), !dbg !2452
  br label %if.end88, !dbg !2453

if.else80:                                        ; preds = %lor.lhs.false
  %99 = load i32, i32* %rc, align 4, !dbg !2454
  %and = and i32 %99, 4, !dbg !2456
  %tobool81 = icmp ne i32 %and, 0, !dbg !2456
  br i1 %tobool81, label %if.then82, label %if.end87, !dbg !2457

if.then82:                                        ; preds = %if.else80
  %100 = load i32, i32* %i, align 4, !dbg !2458
  %idxprom83 = sext i32 %100 to i64, !dbg !2459
  %101 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2459
  %tempsock84 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %101, i32 0, i32 34, !dbg !2460
  %arrayidx85 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock84, i64 0, i64 %idxprom83, !dbg !2459
  %102 = load i32, i32* %arrayidx85, align 4, !dbg !2459
  %call86 = call zeroext i1 @verifyconnect(i32 %102, i32* %error), !dbg !2461
  br label %if.end87, !dbg !2462

if.end87:                                         ; preds = %if.then82, %if.else80
  br label %if.end88

if.end88:                                         ; preds = %if.end87, %if.end79
  br label %if.end89

if.end89:                                         ; preds = %if.end88, %if.end31
  %103 = load i32, i32* %error, align 4, !dbg !2463
  %tobool90 = icmp ne i32 %103, 0, !dbg !2463
  br i1 %tobool90, label %if.then91, label %if.end119, !dbg !2465

if.then91:                                        ; preds = %if.end89
  %104 = load i32, i32* %error, align 4, !dbg !2466
  %105 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2468
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %105, i32 0, i32 17, !dbg !2469
  %os_errno = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 18, !dbg !2470
  store i32 %104, i32* %os_errno, align 4, !dbg !2471
  %106 = load i32, i32* %error, align 4, !dbg !2472
  %call92 = call i32* @__errno_location() #1, !dbg !2472
  store i32 %106, i32* %call92, align 4, !dbg !2472
  %107 = load i32, i32* %i, align 4, !dbg !2473
  %idxprom93 = sext i32 %107 to i64, !dbg !2475
  %108 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2475
  %tempaddr94 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %108, i32 0, i32 8, !dbg !2476
  %arrayidx95 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr94, i64 0, i64 %idxprom93, !dbg !2475
  %109 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx95, align 8, !dbg !2475
  %tobool96 = icmp ne %struct.Curl_addrinfo* %109, null, !dbg !2475
  br i1 %tobool96, label %if.then97, label %if.end118, !dbg !2477

if.then97:                                        ; preds = %if.then91
  call void @llvm.dbg.declare(metadata i32* %status, metadata !2478, metadata !1944), !dbg !2480
  call void @llvm.dbg.declare(metadata [46 x i8]* %ipaddress, metadata !2481, metadata !1944), !dbg !2482
  %110 = load i32, i32* %i, align 4, !dbg !2483
  %idxprom98 = sext i32 %110 to i64, !dbg !2484
  %111 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2484
  %tempaddr99 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %111, i32 0, i32 8, !dbg !2485
  %arrayidx100 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr99, i64 0, i64 %idxprom98, !dbg !2484
  %112 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx100, align 8, !dbg !2484
  %arraydecay = getelementptr inbounds [46 x i8], [46 x i8]* %ipaddress, i32 0, i32 0, !dbg !2486
  %call101 = call i8* @Curl_printable_address(%struct.Curl_addrinfo* %112, i8* %arraydecay, i64 46), !dbg !2487
  %113 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2488
  %arraydecay102 = getelementptr inbounds [46 x i8], [46 x i8]* %ipaddress, i32 0, i32 0, !dbg !2489
  %114 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2490
  %port = getelementptr inbounds %struct.connectdata, %struct.connectdata* %114, i32 0, i32 17, !dbg !2491
  %115 = load i64, i64* %port, align 8, !dbg !2491
  %116 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2492
  %117 = load i32, i32* %error, align 4, !dbg !2493
  %call103 = call i8* @Curl_strerror(%struct.connectdata* %116, i32 %117), !dbg !2494
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %113, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.7, i32 0, i32 0), i8* %arraydecay102, i64 %115, i8* %call103), !dbg !2495
  %118 = load i32, i32* %i, align 4, !dbg !2496
  %idxprom104 = sext i32 %118 to i64, !dbg !2497
  %119 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2497
  %tempaddr105 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %119, i32 0, i32 8, !dbg !2498
  %arrayidx106 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr105, i64 0, i64 %idxprom104, !dbg !2497
  %120 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx106, align 8, !dbg !2497
  %ai_next = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %120, i32 0, i32 7, !dbg !2499
  %121 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai_next, align 8, !dbg !2499
  %cmp107 = icmp eq %struct.Curl_addrinfo* %121, null, !dbg !2500
  br i1 %cmp107, label %cond.true, label %cond.false, !dbg !2497

cond.true:                                        ; preds = %if.then97
  %122 = load i64, i64* %allow, align 8, !dbg !2501
  br label %cond.end, !dbg !2502

cond.false:                                       ; preds = %if.then97
  %123 = load i64, i64* %allow, align 8, !dbg !2504
  %div = sdiv i64 %123, 2, !dbg !2505
  br label %cond.end, !dbg !2506

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %122, %cond.true ], [ %div, %cond.false ], !dbg !2508
  %124 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2510
  %timeoutms_per_addr108 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %124, i32 0, i32 46, !dbg !2511
  store i64 %cond, i64* %timeoutms_per_addr108, align 8, !dbg !2512
  %125 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2513
  %126 = load i32, i32* %sockindex.addr, align 4, !dbg !2514
  %127 = load i32, i32* %i, align 4, !dbg !2515
  %call109 = call i32 @trynextip(%struct.connectdata* %125, i32 %126, i32 %127), !dbg !2516
  store i32 %call109, i32* %status, align 4, !dbg !2517
  %128 = load i32, i32* %status, align 4, !dbg !2518
  %cmp110 = icmp ne i32 %128, 7, !dbg !2520
  br i1 %cmp110, label %if.then116, label %lor.lhs.false111, !dbg !2521

lor.lhs.false111:                                 ; preds = %cond.end
  %129 = load i32, i32* %other, align 4, !dbg !2522
  %idxprom112 = sext i32 %129 to i64, !dbg !2524
  %130 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2524
  %tempsock113 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %130, i32 0, i32 34, !dbg !2525
  %arrayidx114 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock113, i64 0, i64 %idxprom112, !dbg !2524
  %131 = load i32, i32* %arrayidx114, align 4, !dbg !2524
  %cmp115 = icmp eq i32 %131, -1, !dbg !2526
  br i1 %cmp115, label %if.then116, label %if.end117, !dbg !2527

if.then116:                                       ; preds = %lor.lhs.false111, %cond.end
  %132 = load i32, i32* %status, align 4, !dbg !2528
  store i32 %132, i32* %result, align 4, !dbg !2529
  br label %if.end117, !dbg !2530

if.end117:                                        ; preds = %if.then116, %lor.lhs.false111
  br label %if.end118, !dbg !2531

if.end118:                                        ; preds = %if.end117, %if.then91
  br label %if.end119, !dbg !2532

if.end119:                                        ; preds = %if.end118, %if.end89
  br label %for.inc, !dbg !2533

for.inc:                                          ; preds = %if.end119, %if.then9
  %133 = load i32, i32* %i, align 4, !dbg !2534
  %inc = add nsw i32 %133, 1, !dbg !2534
  store i32 %inc, i32* %i, align 4, !dbg !2534
  br label %for.cond, !dbg !2536

for.end:                                          ; preds = %for.cond
  %134 = load i32, i32* %result, align 4, !dbg !2537
  %tobool120 = icmp ne i32 %134, 0, !dbg !2537
  br i1 %tobool120, label %if.then121, label %if.end154, !dbg !2539

if.then121:                                       ; preds = %for.end
  call void @llvm.dbg.declare(metadata i8** %hostname, metadata !2540, metadata !1944), !dbg !2542
  %135 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2543
  %tempaddr122 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %135, i32 0, i32 8, !dbg !2545
  %arrayidx123 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr122, i64 0, i64 1, !dbg !2543
  %136 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx123, align 8, !dbg !2543
  %cmp124 = icmp eq %struct.Curl_addrinfo* %136, null, !dbg !2546
  br i1 %cmp124, label %if.then125, label %if.end130, !dbg !2547

if.then125:                                       ; preds = %if.then121
  %137 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2548
  %138 = load i32, i32* %sockindex.addr, align 4, !dbg !2550
  %call126 = call i32 @trynextip(%struct.connectdata* %137, i32 %138, i32 1), !dbg !2551
  store i32 %call126, i32* %result, align 4, !dbg !2552
  %139 = load i32, i32* %result, align 4, !dbg !2553
  %tobool127 = icmp ne i32 %139, 0, !dbg !2553
  br i1 %tobool127, label %if.end129, label %if.then128, !dbg !2555

if.then128:                                       ; preds = %if.then125
  %140 = load i32, i32* %result, align 4, !dbg !2556
  store i32 %140, i32* %retval, align 4, !dbg !2557
  br label %return, !dbg !2557

if.end129:                                        ; preds = %if.then125
  br label %if.end130, !dbg !2558

if.end130:                                        ; preds = %if.end129, %if.then121
  %141 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2559
  %bits131 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %141, i32 0, i32 43, !dbg !2561
  %socksproxy = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits131, i32 0, i32 6, !dbg !2562
  %142 = load i8, i8* %socksproxy, align 1, !dbg !2562
  %tobool132 = trunc i8 %142 to i1, !dbg !2562
  br i1 %tobool132, label %if.then133, label %if.else134, !dbg !2563

if.then133:                                       ; preds = %if.end130
  %143 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2564
  %socks_proxy = getelementptr inbounds %struct.connectdata, %struct.connectdata* %143, i32 0, i32 15, !dbg !2565
  %host = getelementptr inbounds %struct.proxy_info, %struct.proxy_info* %socks_proxy, i32 0, i32 0, !dbg !2566
  %name = getelementptr inbounds %struct.hostname, %struct.hostname* %host, i32 0, i32 2, !dbg !2567
  %144 = load i8*, i8** %name, align 8, !dbg !2567
  store i8* %144, i8** %hostname, align 8, !dbg !2568
  br label %if.end151, !dbg !2569

if.else134:                                       ; preds = %if.end130
  %145 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2570
  %bits135 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %145, i32 0, i32 43, !dbg !2572
  %httpproxy = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits135, i32 0, i32 5, !dbg !2573
  %146 = load i8, i8* %httpproxy, align 1, !dbg !2573
  %tobool136 = trunc i8 %146 to i1, !dbg !2573
  br i1 %tobool136, label %if.then137, label %if.else140, !dbg !2574

if.then137:                                       ; preds = %if.else134
  %147 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2575
  %http_proxy = getelementptr inbounds %struct.connectdata, %struct.connectdata* %147, i32 0, i32 16, !dbg !2576
  %host138 = getelementptr inbounds %struct.proxy_info, %struct.proxy_info* %http_proxy, i32 0, i32 0, !dbg !2577
  %name139 = getelementptr inbounds %struct.hostname, %struct.hostname* %host138, i32 0, i32 2, !dbg !2578
  %148 = load i8*, i8** %name139, align 8, !dbg !2578
  store i8* %148, i8** %hostname, align 8, !dbg !2579
  br label %if.end150, !dbg !2580

if.else140:                                       ; preds = %if.else134
  %149 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2581
  %bits141 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %149, i32 0, i32 43, !dbg !2583
  %conn_to_host = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits141, i32 0, i32 2, !dbg !2584
  %150 = load i8, i8* %conn_to_host, align 1, !dbg !2584
  %tobool142 = trunc i8 %150 to i1, !dbg !2584
  br i1 %tobool142, label %if.then143, label %if.else146, !dbg !2585

if.then143:                                       ; preds = %if.else140
  %151 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2586
  %conn_to_host144 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %151, i32 0, i32 14, !dbg !2587
  %name145 = getelementptr inbounds %struct.hostname, %struct.hostname* %conn_to_host144, i32 0, i32 2, !dbg !2588
  %152 = load i8*, i8** %name145, align 8, !dbg !2588
  store i8* %152, i8** %hostname, align 8, !dbg !2589
  br label %if.end149, !dbg !2590

if.else146:                                       ; preds = %if.else140
  %153 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2591
  %host147 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %153, i32 0, i32 12, !dbg !2592
  %name148 = getelementptr inbounds %struct.hostname, %struct.hostname* %host147, i32 0, i32 2, !dbg !2593
  %154 = load i8*, i8** %name148, align 8, !dbg !2593
  store i8* %154, i8** %hostname, align 8, !dbg !2594
  br label %if.end149

if.end149:                                        ; preds = %if.else146, %if.then143
  br label %if.end150

if.end150:                                        ; preds = %if.end149, %if.then137
  br label %if.end151

if.end151:                                        ; preds = %if.end150, %if.then133
  %155 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2595
  %156 = load i8*, i8** %hostname, align 8, !dbg !2596
  %157 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2597
  %port152 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %157, i32 0, i32 17, !dbg !2598
  %158 = load i64, i64* %port152, align 8, !dbg !2598
  %159 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2599
  %160 = load i32, i32* %error, align 4, !dbg !2600
  %call153 = call i8* @Curl_strerror(%struct.connectdata* %159, i32 %160), !dbg !2601
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %155, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.8, i32 0, i32 0), i8* %156, i64 %158, i8* %call153), !dbg !2602
  br label %if.end154, !dbg !2603

if.end154:                                        ; preds = %if.end151, %for.end
  %161 = load i32, i32* %result, align 4, !dbg !2604
  store i32 %161, i32* %retval, align 4, !dbg !2605
  br label %return, !dbg !2605

return:                                           ; preds = %if.end154, %if.then128, %if.end75, %if.then67, %if.then3, %if.then
  %162 = load i32, i32* %retval, align 4, !dbg !2606
  ret i32 %162, !dbg !2606
}

declare i32 @Curl_socket_check(i32, i32, i32, i64) #2

declare void @Curl_infof(%struct.Curl_easy*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @trynextip(%struct.connectdata* %conn, i32 %sockindex, i32 %tempindex) #0 !dbg !1919 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockindex.addr = alloca i32, align 4
  %tempindex.addr = alloca i32, align 4
  %other = alloca i32, align 4
  %result = alloca i32, align 4
  %fd_to_close = alloca i32, align 4
  %ai = alloca %struct.Curl_addrinfo*, align 8
  %family = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2607, metadata !1944), !dbg !2608
  store i32 %sockindex, i32* %sockindex.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockindex.addr, metadata !2609, metadata !1944), !dbg !2610
  store i32 %tempindex, i32* %tempindex.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tempindex.addr, metadata !2611, metadata !1944), !dbg !2612
  call void @llvm.dbg.declare(metadata i32* %other, metadata !2613, metadata !1944), !dbg !2614
  %0 = load i32, i32* %tempindex.addr, align 4, !dbg !2615
  %xor = xor i32 %0, 1, !dbg !2616
  store i32 %xor, i32* %other, align 4, !dbg !2614
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2617, metadata !1944), !dbg !2618
  store i32 7, i32* %result, align 4, !dbg !2618
  call void @llvm.dbg.declare(metadata i32* %fd_to_close, metadata !2619, metadata !1944), !dbg !2620
  %1 = load i32, i32* %tempindex.addr, align 4, !dbg !2621
  %idxprom = sext i32 %1 to i64, !dbg !2622
  %2 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2622
  %tempsock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 34, !dbg !2623
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock, i64 0, i64 %idxprom, !dbg !2622
  %3 = load i32, i32* %arrayidx, align 4, !dbg !2622
  store i32 %3, i32* %fd_to_close, align 4, !dbg !2620
  %4 = load i32, i32* %tempindex.addr, align 4, !dbg !2624
  %idxprom1 = sext i32 %4 to i64, !dbg !2625
  %5 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2625
  %tempsock2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %5, i32 0, i32 34, !dbg !2626
  %arrayidx3 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock2, i64 0, i64 %idxprom1, !dbg !2625
  store i32 -1, i32* %arrayidx3, align 4, !dbg !2627
  %6 = load i32, i32* %sockindex.addr, align 4, !dbg !2628
  %cmp = icmp eq i32 %6, 0, !dbg !2630
  br i1 %cmp, label %if.then, label %if.end40, !dbg !2631

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %ai, metadata !2632, metadata !1944), !dbg !2634
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %ai, align 8, !dbg !2634
  call void @llvm.dbg.declare(metadata i32* %family, metadata !2635, metadata !1944), !dbg !2636
  store i32 0, i32* %family, align 4, !dbg !2636
  %7 = load i32, i32* %tempindex.addr, align 4, !dbg !2637
  %idxprom4 = sext i32 %7 to i64, !dbg !2639
  %8 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2639
  %tempaddr = getelementptr inbounds %struct.connectdata, %struct.connectdata* %8, i32 0, i32 8, !dbg !2640
  %arrayidx5 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr, i64 0, i64 %idxprom4, !dbg !2639
  %9 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx5, align 8, !dbg !2639
  %tobool = icmp ne %struct.Curl_addrinfo* %9, null, !dbg !2639
  br i1 %tobool, label %if.then6, label %if.end, !dbg !2641

if.then6:                                         ; preds = %if.then
  %10 = load i32, i32* %tempindex.addr, align 4, !dbg !2642
  %idxprom7 = sext i32 %10 to i64, !dbg !2644
  %11 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2644
  %tempaddr8 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %11, i32 0, i32 8, !dbg !2645
  %arrayidx9 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr8, i64 0, i64 %idxprom7, !dbg !2644
  %12 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx9, align 8, !dbg !2644
  %ai_family = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %12, i32 0, i32 1, !dbg !2646
  %13 = load i32, i32* %ai_family, align 4, !dbg !2646
  store i32 %13, i32* %family, align 4, !dbg !2647
  %14 = load i32, i32* %tempindex.addr, align 4, !dbg !2648
  %idxprom10 = sext i32 %14 to i64, !dbg !2649
  %15 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2649
  %tempaddr11 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %15, i32 0, i32 8, !dbg !2650
  %arrayidx12 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr11, i64 0, i64 %idxprom10, !dbg !2649
  %16 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx12, align 8, !dbg !2649
  %ai_next = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %16, i32 0, i32 7, !dbg !2651
  %17 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai_next, align 8, !dbg !2651
  store %struct.Curl_addrinfo* %17, %struct.Curl_addrinfo** %ai, align 8, !dbg !2652
  br label %if.end, !dbg !2653

if.end:                                           ; preds = %if.then6, %if.then
  br label %while.cond, !dbg !2654

while.cond:                                       ; preds = %if.then32, %if.end
  %18 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !2655
  %tobool13 = icmp ne %struct.Curl_addrinfo* %18, null, !dbg !2657
  br i1 %tobool13, label %while.body, label %while.end39, !dbg !2657

while.body:                                       ; preds = %while.cond
  %19 = load i32, i32* %other, align 4, !dbg !2658
  %idxprom14 = sext i32 %19 to i64, !dbg !2661
  %20 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2661
  %tempaddr15 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %20, i32 0, i32 8, !dbg !2662
  %arrayidx16 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr15, i64 0, i64 %idxprom14, !dbg !2661
  %21 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx16, align 8, !dbg !2661
  %tobool17 = icmp ne %struct.Curl_addrinfo* %21, null, !dbg !2661
  br i1 %tobool17, label %if.then18, label %if.end25, !dbg !2663

if.then18:                                        ; preds = %while.body
  br label %while.cond19, !dbg !2664

while.cond19:                                     ; preds = %while.body23, %if.then18
  %22 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !2666
  %tobool20 = icmp ne %struct.Curl_addrinfo* %22, null, !dbg !2666
  br i1 %tobool20, label %land.rhs, label %land.end, !dbg !2668

land.rhs:                                         ; preds = %while.cond19
  %23 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !2669
  %ai_family21 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %23, i32 0, i32 1, !dbg !2671
  %24 = load i32, i32* %ai_family21, align 4, !dbg !2671
  %25 = load i32, i32* %family, align 4, !dbg !2672
  %cmp22 = icmp ne i32 %24, %25, !dbg !2673
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond19
  %26 = phi i1 [ false, %while.cond19 ], [ %cmp22, %land.rhs ]
  br i1 %26, label %while.body23, label %while.end, !dbg !2674

while.body23:                                     ; preds = %land.end
  %27 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !2676
  %ai_next24 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %27, i32 0, i32 7, !dbg !2677
  %28 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai_next24, align 8, !dbg !2677
  store %struct.Curl_addrinfo* %28, %struct.Curl_addrinfo** %ai, align 8, !dbg !2678
  br label %while.cond19, !dbg !2679

while.end:                                        ; preds = %land.end
  br label %if.end25, !dbg !2681

if.end25:                                         ; preds = %while.end, %while.body
  %29 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !2682
  %tobool26 = icmp ne %struct.Curl_addrinfo* %29, null, !dbg !2682
  br i1 %tobool26, label %if.then27, label %if.end38, !dbg !2684

if.then27:                                        ; preds = %if.end25
  %30 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2685
  %31 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !2687
  %32 = load i32, i32* %tempindex.addr, align 4, !dbg !2688
  %idxprom28 = sext i32 %32 to i64, !dbg !2689
  %33 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2689
  %tempsock29 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %33, i32 0, i32 34, !dbg !2690
  %arrayidx30 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock29, i64 0, i64 %idxprom28, !dbg !2689
  %call = call i32 @singleipconnect(%struct.connectdata* %30, %struct.Curl_addrinfo* %31, i32* %arrayidx30), !dbg !2691
  store i32 %call, i32* %result, align 4, !dbg !2692
  %34 = load i32, i32* %result, align 4, !dbg !2693
  %cmp31 = icmp eq i32 %34, 7, !dbg !2695
  br i1 %cmp31, label %if.then32, label %if.end34, !dbg !2696

if.then32:                                        ; preds = %if.then27
  %35 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !2697
  %ai_next33 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %35, i32 0, i32 7, !dbg !2699
  %36 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai_next33, align 8, !dbg !2699
  store %struct.Curl_addrinfo* %36, %struct.Curl_addrinfo** %ai, align 8, !dbg !2700
  br label %while.cond, !dbg !2701

if.end34:                                         ; preds = %if.then27
  %37 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !2702
  %38 = load i32, i32* %tempindex.addr, align 4, !dbg !2703
  %idxprom35 = sext i32 %38 to i64, !dbg !2704
  %39 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2704
  %tempaddr36 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %39, i32 0, i32 8, !dbg !2705
  %arrayidx37 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr36, i64 0, i64 %idxprom35, !dbg !2704
  store %struct.Curl_addrinfo* %37, %struct.Curl_addrinfo** %arrayidx37, align 8, !dbg !2706
  br label %if.end38, !dbg !2707

if.end38:                                         ; preds = %if.end34, %if.end25
  br label %while.end39, !dbg !2708

while.end39:                                      ; preds = %if.end38, %while.cond
  br label %if.end40, !dbg !2709

if.end40:                                         ; preds = %while.end39, %entry
  %40 = load i32, i32* %fd_to_close, align 4, !dbg !2710
  %cmp41 = icmp ne i32 %40, -1, !dbg !2712
  br i1 %cmp41, label %if.then42, label %if.end44, !dbg !2713

if.then42:                                        ; preds = %if.end40
  %41 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2714
  %42 = load i32, i32* %fd_to_close, align 4, !dbg !2715
  %call43 = call i32 @Curl_closesocket(%struct.connectdata* %41, i32 %42), !dbg !2716
  br label %if.end44, !dbg !2716

if.end44:                                         ; preds = %if.then42, %if.end40
  %43 = load i32, i32* %result, align 4, !dbg !2717
  ret i32 %43, !dbg !2718
}

; Function Attrs: nounwind uwtable
define internal zeroext i1 @verifyconnect(i32 %sockfd, i32* %error) #0 !dbg !1922 {
entry:
  %sockfd.addr = alloca i32, align 4
  %error.addr = alloca i32*, align 8
  %rc = alloca i8, align 1
  %err = alloca i32, align 4
  %errSize = alloca i32, align 4
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !2719, metadata !1944), !dbg !2720
  store i32* %error, i32** %error.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %error.addr, metadata !2721, metadata !1944), !dbg !2722
  call void @llvm.dbg.declare(metadata i8* %rc, metadata !2723, metadata !1944), !dbg !2724
  store i8 1, i8* %rc, align 1, !dbg !2724
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2725, metadata !1944), !dbg !2726
  store i32 0, i32* %err, align 4, !dbg !2726
  call void @llvm.dbg.declare(metadata i32* %errSize, metadata !2727, metadata !1944), !dbg !2728
  store i32 4, i32* %errSize, align 4, !dbg !2728
  %0 = load i32, i32* %sockfd.addr, align 4, !dbg !2729
  %1 = bitcast i32* %err to i8*, !dbg !2731
  %call = call i32 @getsockopt(i32 %0, i32 1, i32 4, i8* %1, i32* %errSize) #7, !dbg !2732
  %cmp = icmp ne i32 0, %call, !dbg !2733
  br i1 %cmp, label %if.then, label %if.end, !dbg !2734

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !2735
  %2 = load i32, i32* %call1, align 4, !dbg !2735
  store i32 %2, i32* %err, align 4, !dbg !2736
  br label %if.end, !dbg !2737

if.end:                                           ; preds = %if.then, %entry
  %3 = load i32, i32* %err, align 4, !dbg !2738
  %cmp2 = icmp eq i32 0, %3, !dbg !2740
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !2741

lor.lhs.false:                                    ; preds = %if.end
  %4 = load i32, i32* %err, align 4, !dbg !2742
  %cmp3 = icmp eq i32 106, %4, !dbg !2744
  br i1 %cmp3, label %if.then4, label %if.else, !dbg !2745

if.then4:                                         ; preds = %lor.lhs.false, %if.end
  store i8 1, i8* %rc, align 1, !dbg !2746
  br label %if.end5, !dbg !2747

if.else:                                          ; preds = %lor.lhs.false
  store i8 0, i8* %rc, align 1, !dbg !2748
  br label %if.end5

if.end5:                                          ; preds = %if.else, %if.then4
  %5 = load i32*, i32** %error.addr, align 8, !dbg !2749
  %tobool = icmp ne i32* %5, null, !dbg !2749
  br i1 %tobool, label %if.then6, label %if.end7, !dbg !2751

if.then6:                                         ; preds = %if.end5
  %6 = load i32, i32* %err, align 4, !dbg !2752
  %7 = load i32*, i32** %error.addr, align 8, !dbg !2753
  store i32 %6, i32* %7, align 4, !dbg !2754
  br label %if.end7, !dbg !2755

if.end7:                                          ; preds = %if.then6, %if.end5
  %8 = load i8, i8* %rc, align 1, !dbg !2756
  %tobool8 = trunc i8 %8 to i1, !dbg !2756
  ret i1 %tobool8, !dbg !2757
}

; Function Attrs: nounwind uwtable
define i32 @Curl_closesocket(%struct.connectdata* %conn, i32 %sock) #0 !dbg !1871 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %sock.addr = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2758, metadata !1944), !dbg !2759
  store i32 %sock, i32* %sock.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sock.addr, metadata !2760, metadata !1944), !dbg !2761
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2762
  %tobool = icmp ne %struct.connectdata* %0, null, !dbg !2762
  br i1 %tobool, label %land.lhs.true, label %if.end10, !dbg !2764

land.lhs.true:                                    ; preds = %entry
  %1 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2765
  %fclosesocket = getelementptr inbounds %struct.connectdata, %struct.connectdata* %1, i32 0, i32 2, !dbg !2767
  %2 = load i32 (i8*, i32)*, i32 (i8*, i32)** %fclosesocket, align 8, !dbg !2767
  %tobool1 = icmp ne i32 (i8*, i32)* %2, null, !dbg !2765
  br i1 %tobool1, label %if.then, label %if.end10, !dbg !2768

if.then:                                          ; preds = %land.lhs.true
  %3 = load i32, i32* %sock.addr, align 4, !dbg !2769
  %4 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2772
  %sock2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %4, i32 0, i32 33, !dbg !2773
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock2, i64 0, i64 1, !dbg !2772
  %5 = load i32, i32* %arrayidx, align 4, !dbg !2772
  %cmp = icmp eq i32 %3, %5, !dbg !2774
  br i1 %cmp, label %land.lhs.true3, label %if.else, !dbg !2775

land.lhs.true3:                                   ; preds = %if.then
  %6 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2776
  %sock_accepted = getelementptr inbounds %struct.connectdata, %struct.connectdata* %6, i32 0, i32 35, !dbg !2777
  %arrayidx4 = getelementptr inbounds [2 x i8], [2 x i8]* %sock_accepted, i64 0, i64 1, !dbg !2776
  %7 = load i8, i8* %arrayidx4, align 1, !dbg !2776
  %tobool5 = trunc i8 %7 to i1, !dbg !2776
  br i1 %tobool5, label %if.then6, label %if.else, !dbg !2778

if.then6:                                         ; preds = %land.lhs.true3
  %8 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2780
  %sock_accepted7 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %8, i32 0, i32 35, !dbg !2781
  %arrayidx8 = getelementptr inbounds [2 x i8], [2 x i8]* %sock_accepted7, i64 0, i64 1, !dbg !2780
  store i8 0, i8* %arrayidx8, align 1, !dbg !2782
  br label %if.end, !dbg !2780

if.else:                                          ; preds = %land.lhs.true3, %if.then
  %9 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2783
  %10 = load i32, i32* %sock.addr, align 4, !dbg !2785
  call void @Curl_multi_closed(%struct.connectdata* %9, i32 %10), !dbg !2786
  %11 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2787
  %fclosesocket9 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %11, i32 0, i32 2, !dbg !2788
  %12 = load i32 (i8*, i32)*, i32 (i8*, i32)** %fclosesocket9, align 8, !dbg !2788
  %13 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2789
  %closesocket_client = getelementptr inbounds %struct.connectdata, %struct.connectdata* %13, i32 0, i32 3, !dbg !2790
  %14 = load i8*, i8** %closesocket_client, align 8, !dbg !2790
  %15 = load i32, i32* %sock.addr, align 4, !dbg !2791
  %call = call i32 %12(i8* %14, i32 %15), !dbg !2787
  store i32 %call, i32* %retval, align 4, !dbg !2792
  br label %return, !dbg !2792

if.end:                                           ; preds = %if.then6
  br label %if.end10, !dbg !2793

if.end10:                                         ; preds = %if.end, %land.lhs.true, %entry
  %16 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2794
  %tobool11 = icmp ne %struct.connectdata* %16, null, !dbg !2794
  br i1 %tobool11, label %if.then12, label %if.end13, !dbg !2796

if.then12:                                        ; preds = %if.end10
  %17 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2797
  %18 = load i32, i32* %sock.addr, align 4, !dbg !2798
  call void @Curl_multi_closed(%struct.connectdata* %17, i32 %18), !dbg !2799
  br label %if.end13, !dbg !2799

if.end13:                                         ; preds = %if.then12, %if.end10
  %19 = load i32, i32* %sock.addr, align 4, !dbg !2800
  %call14 = call i32 @close(i32 %19), !dbg !2800
  store i32 0, i32* %retval, align 4, !dbg !2801
  br label %return, !dbg !2801

return:                                           ; preds = %if.end13, %if.else
  %20 = load i32, i32* %retval, align 4, !dbg !2802
  ret i32 %20, !dbg !2802
}

declare i32 @Curl_connected_proxy(%struct.connectdata*, i32) #2

declare void @Curl_pgrsTime(%struct.Curl_easy*, i32) #2

declare void @Curl_verboseconnect(%struct.connectdata*) #2

declare i8* @Curl_printable_address(%struct.Curl_addrinfo*, i8*, i64) #2

; Function Attrs: nounwind uwtable
define void @Curl_tcpnodelay(%struct.connectdata* %conn, i32 %sockfd) #0 !dbg !1858 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockfd.addr = alloca i32, align 4
  %data = alloca %struct.Curl_easy*, align 8
  %onoff = alloca i32, align 4
  %level = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2803, metadata !1944), !dbg !2804
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !2805, metadata !1944), !dbg !2806
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2807, metadata !1944), !dbg !2808
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2809
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2810
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2810
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2808
  call void @llvm.dbg.declare(metadata i32* %onoff, metadata !2811, metadata !1944), !dbg !2812
  store i32 1, i32* %onoff, align 4, !dbg !2812
  call void @llvm.dbg.declare(metadata i32* %level, metadata !2813, metadata !1944), !dbg !2814
  store i32 6, i32* %level, align 4, !dbg !2814
  %2 = load i32, i32* %sockfd.addr, align 4, !dbg !2815
  %3 = load i32, i32* %level, align 4, !dbg !2817
  %4 = bitcast i32* %onoff to i8*, !dbg !2818
  %call = call i32 @setsockopt(i32 %2, i32 %3, i32 1, i8* %4, i32 4) #7, !dbg !2819
  %cmp = icmp slt i32 %call, 0, !dbg !2820
  br i1 %cmp, label %if.then, label %if.else, !dbg !2821

if.then:                                          ; preds = %entry
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2822
  %6 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2823
  %call2 = call i32* @__errno_location() #1, !dbg !2824
  %7 = load i32, i32* %call2, align 4, !dbg !2824
  %call3 = call i8* @Curl_strerror(%struct.connectdata* %6, i32 %7), !dbg !2825
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %5, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.9, i32 0, i32 0), i8* %call3), !dbg !2827
  br label %if.end, !dbg !2827

if.else:                                          ; preds = %entry
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2828
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %8, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.10, i32 0, i32 0)), !dbg !2829
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void, !dbg !2830
}

; Function Attrs: nounwind
declare i32 @setsockopt(i32, i32, i32, i8*, i32) #4

; Function Attrs: nounwind uwtable
define i32 @Curl_connecthost(%struct.connectdata* %conn, %struct.Curl_dns_entry* %remotehost) #0 !dbg !1859 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %remotehost.addr = alloca %struct.Curl_dns_entry*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %before = alloca %struct.timeval, align 8
  %result = alloca i32, align 4
  %timeout_ms = alloca i64, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2831, metadata !1944), !dbg !2832
  store %struct.Curl_dns_entry* %remotehost, %struct.Curl_dns_entry** %remotehost.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %remotehost.addr, metadata !2833, metadata !1944), !dbg !2834
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2835, metadata !1944), !dbg !2836
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2837
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2838
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2838
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2836
  call void @llvm.dbg.declare(metadata %struct.timeval* %before, metadata !2839, metadata !1944), !dbg !2840
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !2841
  %2 = bitcast %struct.timeval* %before to { i64, i64 }*, !dbg !2841
  %3 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %2, i32 0, i32 0, !dbg !2841
  %4 = extractvalue { i64, i64 } %call, 0, !dbg !2841
  store i64 %4, i64* %3, align 8, !dbg !2841
  %5 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %2, i32 0, i32 1, !dbg !2841
  %6 = extractvalue { i64, i64 } %call, 1, !dbg !2841
  store i64 %6, i64* %5, align 8, !dbg !2841
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2842, metadata !1944), !dbg !2843
  store i32 7, i32* %result, align 4, !dbg !2843
  call void @llvm.dbg.declare(metadata i64* %timeout_ms, metadata !2844, metadata !1944), !dbg !2845
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2846
  %call2 = call i64 @Curl_timeleft(%struct.Curl_easy* %7, %struct.timeval* %before, i1 zeroext true), !dbg !2847
  store i64 %call2, i64* %timeout_ms, align 8, !dbg !2845
  %8 = load i64, i64* %timeout_ms, align 8, !dbg !2848
  %cmp = icmp slt i64 %8, 0, !dbg !2850
  br i1 %cmp, label %if.then, label %if.end, !dbg !2851

if.then:                                          ; preds = %entry
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2852
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %9, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.4, i32 0, i32 0)), !dbg !2854
  store i32 28, i32* %retval, align 4, !dbg !2855
  br label %return, !dbg !2855

if.end:                                           ; preds = %entry
  %10 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %remotehost.addr, align 8, !dbg !2856
  %addr = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %10, i32 0, i32 0, !dbg !2857
  %11 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !2857
  %call3 = call i32 @Curl_num_addresses(%struct.Curl_addrinfo* %11), !dbg !2858
  %12 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2859
  %num_addr = getelementptr inbounds %struct.connectdata, %struct.connectdata* %12, i32 0, i32 45, !dbg !2860
  store i32 %call3, i32* %num_addr, align 8, !dbg !2861
  %13 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %remotehost.addr, align 8, !dbg !2862
  %addr4 = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %13, i32 0, i32 0, !dbg !2863
  %14 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr4, align 8, !dbg !2863
  %15 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2864
  %tempaddr = getelementptr inbounds %struct.connectdata, %struct.connectdata* %15, i32 0, i32 8, !dbg !2865
  %arrayidx = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr, i64 0, i64 0, !dbg !2864
  store %struct.Curl_addrinfo* %14, %struct.Curl_addrinfo** %arrayidx, align 8, !dbg !2866
  %16 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2867
  %tempaddr5 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %16, i32 0, i32 8, !dbg !2868
  %arrayidx6 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr5, i64 0, i64 1, !dbg !2867
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %arrayidx6, align 8, !dbg !2869
  %17 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2870
  %tempsock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %17, i32 0, i32 34, !dbg !2871
  %arrayidx7 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock, i64 0, i64 0, !dbg !2870
  store i32 -1, i32* %arrayidx7, align 8, !dbg !2872
  %18 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2873
  %tempsock8 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %18, i32 0, i32 34, !dbg !2874
  %arrayidx9 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock8, i64 0, i64 1, !dbg !2873
  store i32 -1, i32* %arrayidx9, align 4, !dbg !2875
  %19 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2876
  %data10 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %19, i32 0, i32 0, !dbg !2877
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data10, align 8, !dbg !2877
  call void @Curl_expire(%struct.Curl_easy* %20, i64 200), !dbg !2878
  %21 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2879
  %tempaddr11 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %21, i32 0, i32 8, !dbg !2880
  %arrayidx12 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr11, i64 0, i64 0, !dbg !2879
  %22 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx12, align 8, !dbg !2879
  %ai_next = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %22, i32 0, i32 7, !dbg !2881
  %23 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai_next, align 8, !dbg !2881
  %cmp13 = icmp eq %struct.Curl_addrinfo* %23, null, !dbg !2882
  br i1 %cmp13, label %cond.true, label %cond.false, !dbg !2879

cond.true:                                        ; preds = %if.end
  %24 = load i64, i64* %timeout_ms, align 8, !dbg !2883
  br label %cond.end, !dbg !2885

cond.false:                                       ; preds = %if.end
  %25 = load i64, i64* %timeout_ms, align 8, !dbg !2886
  %div = sdiv i64 %25, 2, !dbg !2888
  br label %cond.end, !dbg !2889

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %24, %cond.true ], [ %div, %cond.false ], !dbg !2890
  %26 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2892
  %timeoutms_per_addr = getelementptr inbounds %struct.connectdata, %struct.connectdata* %26, i32 0, i32 46, !dbg !2893
  store i64 %cond, i64* %timeoutms_per_addr, align 8, !dbg !2894
  br label %while.cond, !dbg !2895

while.cond:                                       ; preds = %if.end23, %cond.end
  %27 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2896
  %tempaddr14 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %27, i32 0, i32 8, !dbg !2897
  %arrayidx15 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr14, i64 0, i64 0, !dbg !2896
  %28 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx15, align 8, !dbg !2896
  %tobool = icmp ne %struct.Curl_addrinfo* %28, null, !dbg !2898
  br i1 %tobool, label %while.body, label %while.end, !dbg !2898

while.body:                                       ; preds = %while.cond
  %29 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2899
  %30 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2901
  %tempaddr16 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %30, i32 0, i32 8, !dbg !2902
  %arrayidx17 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr16, i64 0, i64 0, !dbg !2901
  %31 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx17, align 8, !dbg !2901
  %32 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2903
  %tempsock18 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %32, i32 0, i32 34, !dbg !2904
  %arrayidx19 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock18, i64 0, i64 0, !dbg !2903
  %call20 = call i32 @singleipconnect(%struct.connectdata* %29, %struct.Curl_addrinfo* %31, i32* %arrayidx19), !dbg !2905
  store i32 %call20, i32* %result, align 4, !dbg !2906
  %33 = load i32, i32* %result, align 4, !dbg !2907
  %tobool21 = icmp ne i32 %33, 0, !dbg !2907
  br i1 %tobool21, label %if.end23, label %if.then22, !dbg !2909

if.then22:                                        ; preds = %while.body
  br label %while.end, !dbg !2910

if.end23:                                         ; preds = %while.body
  %34 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2911
  %tempaddr24 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %34, i32 0, i32 8, !dbg !2912
  %arrayidx25 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr24, i64 0, i64 0, !dbg !2911
  %35 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %arrayidx25, align 8, !dbg !2911
  %ai_next26 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %35, i32 0, i32 7, !dbg !2913
  %36 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai_next26, align 8, !dbg !2913
  %37 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2914
  %tempaddr27 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %37, i32 0, i32 8, !dbg !2915
  %arrayidx28 = getelementptr inbounds [2 x %struct.Curl_addrinfo*], [2 x %struct.Curl_addrinfo*]* %tempaddr27, i64 0, i64 0, !dbg !2914
  store %struct.Curl_addrinfo* %36, %struct.Curl_addrinfo** %arrayidx28, align 8, !dbg !2916
  br label %while.cond, !dbg !2917

while.end:                                        ; preds = %if.then22, %while.cond
  %38 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2918
  %tempsock29 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %38, i32 0, i32 34, !dbg !2920
  %arrayidx30 = getelementptr inbounds [2 x i32], [2 x i32]* %tempsock29, i64 0, i64 0, !dbg !2918
  %39 = load i32, i32* %arrayidx30, align 8, !dbg !2918
  %cmp31 = icmp eq i32 %39, -1, !dbg !2921
  br i1 %cmp31, label %if.then32, label %if.end36, !dbg !2922

if.then32:                                        ; preds = %while.end
  %40 = load i32, i32* %result, align 4, !dbg !2923
  %tobool33 = icmp ne i32 %40, 0, !dbg !2923
  br i1 %tobool33, label %if.end35, label %if.then34, !dbg !2926

if.then34:                                        ; preds = %if.then32
  store i32 7, i32* %result, align 4, !dbg !2927
  br label %if.end35, !dbg !2928

if.end35:                                         ; preds = %if.then34, %if.then32
  %41 = load i32, i32* %result, align 4, !dbg !2929
  store i32 %41, i32* %retval, align 4, !dbg !2930
  br label %return, !dbg !2930

if.end36:                                         ; preds = %while.end
  %42 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2931
  %info = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %42, i32 0, i32 19, !dbg !2932
  %numconnects = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info, i32 0, i32 9, !dbg !2933
  %43 = load i64, i64* %numconnects, align 8, !dbg !2934
  %inc = add nsw i64 %43, 1, !dbg !2934
  store i64 %inc, i64* %numconnects, align 8, !dbg !2934
  store i32 0, i32* %retval, align 4, !dbg !2935
  br label %return, !dbg !2935

return:                                           ; preds = %if.end36, %if.end35, %if.then
  %44 = load i32, i32* %retval, align 4, !dbg !2936
  ret i32 %44, !dbg !2936
}

declare i32 @Curl_num_addresses(%struct.Curl_addrinfo*) #2

declare void @Curl_expire(%struct.Curl_easy*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @singleipconnect(%struct.connectdata* %conn, %struct.Curl_addrinfo* %ai, i32* %sockp) #0 !dbg !1925 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %ai.addr = alloca %struct.Curl_addrinfo*, align 8
  %sockp.addr = alloca i32*, align 8
  %addr = alloca %struct.Curl_sockaddr_ex, align 8
  %rc = alloca i32, align 4
  %error = alloca i32, align 4
  %isconnected = alloca i8, align 1
  %data = alloca %struct.Curl_easy*, align 8
  %sockfd = alloca i32, align 4
  %result = alloca i32, align 4
  %ipaddress = alloca [46 x i8], align 16
  %port = alloca i64, align 8
  %is_tcp = alloca i8, align 1
  %coerce = alloca %struct.timeval, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2937, metadata !1944), !dbg !2938
  store %struct.Curl_addrinfo* %ai, %struct.Curl_addrinfo** %ai.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %ai.addr, metadata !2939, metadata !1944), !dbg !2940
  store i32* %sockp, i32** %sockp.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %sockp.addr, metadata !2941, metadata !1944), !dbg !2942
  call void @llvm.dbg.declare(metadata %struct.Curl_sockaddr_ex* %addr, metadata !2943, metadata !1944), !dbg !2944
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !2945, metadata !1944), !dbg !2946
  store i32 -1, i32* %rc, align 4, !dbg !2946
  call void @llvm.dbg.declare(metadata i32* %error, metadata !2947, metadata !1944), !dbg !2948
  store i32 0, i32* %error, align 4, !dbg !2948
  call void @llvm.dbg.declare(metadata i8* %isconnected, metadata !2949, metadata !1944), !dbg !2950
  store i8 0, i8* %isconnected, align 1, !dbg !2950
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2951, metadata !1944), !dbg !2952
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2953
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2954
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2954
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2952
  call void @llvm.dbg.declare(metadata i32* %sockfd, metadata !2955, metadata !1944), !dbg !2956
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2957, metadata !1944), !dbg !2958
  call void @llvm.dbg.declare(metadata [46 x i8]* %ipaddress, metadata !2959, metadata !1944), !dbg !2960
  call void @llvm.dbg.declare(metadata i64* %port, metadata !2961, metadata !1944), !dbg !2962
  call void @llvm.dbg.declare(metadata i8* %is_tcp, metadata !2963, metadata !1944), !dbg !2964
  %2 = load i32*, i32** %sockp.addr, align 8, !dbg !2965
  store i32 -1, i32* %2, align 4, !dbg !2966
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2967
  %4 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai.addr, align 8, !dbg !2968
  %call = call i32 @Curl_socket(%struct.connectdata* %3, %struct.Curl_addrinfo* %4, %struct.Curl_sockaddr_ex* %addr, i32* %sockfd), !dbg !2969
  store i32 %call, i32* %result, align 4, !dbg !2970
  %5 = load i32, i32* %result, align 4, !dbg !2971
  %tobool = icmp ne i32 %5, 0, !dbg !2971
  br i1 %tobool, label %if.then, label %if.end, !dbg !2973

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2974
  br label %return, !dbg !2974

if.end:                                           ; preds = %entry
  %_sa_ex_u = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %addr, i32 0, i32 4, !dbg !2975
  %addr2 = bitcast %union.anon.2* %_sa_ex_u to %struct.sockaddr*, !dbg !2975
  %arraydecay = getelementptr inbounds [46 x i8], [46 x i8]* %ipaddress, i32 0, i32 0, !dbg !2977
  %call3 = call zeroext i1 @getaddressinfo(%struct.sockaddr* %addr2, i8* %arraydecay, i64* %port), !dbg !2978
  br i1 %call3, label %if.end8, label %if.then4, !dbg !2979

if.then4:                                         ; preds = %if.end
  %call5 = call i32* @__errno_location() #1, !dbg !2980
  %6 = load i32, i32* %call5, align 4, !dbg !2980
  store i32 %6, i32* %error, align 4, !dbg !2982
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2983
  %8 = load i32, i32* %error, align 4, !dbg !2984
  %9 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2985
  %10 = load i32, i32* %error, align 4, !dbg !2986
  %call6 = call i8* @Curl_strerror(%struct.connectdata* %9, i32 %10), !dbg !2987
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %7, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.12, i32 0, i32 0), i32 %8, i8* %call6), !dbg !2988
  %11 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2989
  %12 = load i32, i32* %sockfd, align 4, !dbg !2990
  %call7 = call i32 @Curl_closesocket(%struct.connectdata* %11, i32 %12), !dbg !2991
  store i32 0, i32* %retval, align 4, !dbg !2992
  br label %return, !dbg !2992

if.end8:                                          ; preds = %if.end
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2993
  %arraydecay9 = getelementptr inbounds [46 x i8], [46 x i8]* %ipaddress, i32 0, i32 0, !dbg !2994
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %13, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.13, i32 0, i32 0), i8* %arraydecay9), !dbg !2995
  %family = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %addr, i32 0, i32 0, !dbg !2996
  %14 = load i32, i32* %family, align 8, !dbg !2996
  %cmp = icmp eq i32 %14, 2, !dbg !2997
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !2998

land.rhs:                                         ; preds = %if.end8
  %socktype = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %addr, i32 0, i32 1, !dbg !2999
  %15 = load i32, i32* %socktype, align 4, !dbg !2999
  %cmp10 = icmp eq i32 %15, 1, !dbg !3001
  br label %land.end

land.end:                                         ; preds = %land.rhs, %if.end8
  %16 = phi i1 [ false, %if.end8 ], [ %cmp10, %land.rhs ]
  %frombool = zext i1 %16 to i8, !dbg !3002
  store i8 %frombool, i8* %is_tcp, align 1, !dbg !3002
  %17 = load i8, i8* %is_tcp, align 1, !dbg !3004
  %tobool11 = trunc i8 %17 to i1, !dbg !3004
  br i1 %tobool11, label %land.lhs.true, label %if.end14, !dbg !3006

land.lhs.true:                                    ; preds = %land.end
  %18 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3007
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %18, i32 0, i32 13, !dbg !3009
  %tcp_nodelay = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 118, !dbg !3010
  %19 = load i8, i8* %tcp_nodelay, align 2, !dbg !3010
  %tobool12 = trunc i8 %19 to i1, !dbg !3010
  br i1 %tobool12, label %if.then13, label %if.end14, !dbg !3011

if.then13:                                        ; preds = %land.lhs.true
  %20 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3012
  %21 = load i32, i32* %sockfd, align 4, !dbg !3013
  call void @Curl_tcpnodelay(%struct.connectdata* %20, i32 %21), !dbg !3014
  br label %if.end14, !dbg !3014

if.end14:                                         ; preds = %if.then13, %land.lhs.true, %land.end
  br label %do.body, !dbg !3015

do.body:                                          ; preds = %if.end14
  br label %do.end, !dbg !3016

do.end:                                           ; preds = %do.body
  br label %do.body15, !dbg !3019

do.body15:                                        ; preds = %do.end
  br label %do.end16, !dbg !3020

do.end16:                                         ; preds = %do.body15
  %22 = load i8, i8* %is_tcp, align 1, !dbg !3023
  %tobool17 = trunc i8 %22 to i1, !dbg !3023
  br i1 %tobool17, label %land.lhs.true18, label %if.end22, !dbg !3025

land.lhs.true18:                                  ; preds = %do.end16
  %23 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3026
  %set19 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %23, i32 0, i32 13, !dbg !3028
  %tcp_keepalive = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set19, i32 0, i32 142, !dbg !3029
  %24 = load i8, i8* %tcp_keepalive, align 8, !dbg !3029
  %tobool20 = trunc i8 %24 to i1, !dbg !3029
  br i1 %tobool20, label %if.then21, label %if.end22, !dbg !3030

if.then21:                                        ; preds = %land.lhs.true18
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3031
  %26 = load i32, i32* %sockfd, align 4, !dbg !3032
  call void @tcpkeepalive(%struct.Curl_easy* %25, i32 %26), !dbg !3033
  br label %if.end22, !dbg !3033

if.end22:                                         ; preds = %if.then21, %land.lhs.true18, %do.end16
  %27 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3034
  %set23 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %27, i32 0, i32 13, !dbg !3036
  %fsockopt = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set23, i32 0, i32 30, !dbg !3037
  %28 = load i32 (i8*, i32, i32)*, i32 (i8*, i32, i32)** %fsockopt, align 8, !dbg !3037
  %tobool24 = icmp ne i32 (i8*, i32, i32)* %28, null, !dbg !3034
  br i1 %tobool24, label %if.then25, label %if.end37, !dbg !3038

if.then25:                                        ; preds = %if.end22
  %29 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3039
  %set26 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %29, i32 0, i32 13, !dbg !3041
  %fsockopt27 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set26, i32 0, i32 30, !dbg !3042
  %30 = load i32 (i8*, i32, i32)*, i32 (i8*, i32, i32)** %fsockopt27, align 8, !dbg !3042
  %31 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3043
  %set28 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %31, i32 0, i32 13, !dbg !3044
  %sockopt_client = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set28, i32 0, i32 31, !dbg !3045
  %32 = load i8*, i8** %sockopt_client, align 8, !dbg !3045
  %33 = load i32, i32* %sockfd, align 4, !dbg !3046
  %call29 = call i32 %30(i8* %32, i32 %33, i32 0), !dbg !3039
  store i32 %call29, i32* %error, align 4, !dbg !3047
  %34 = load i32, i32* %error, align 4, !dbg !3048
  %cmp30 = icmp eq i32 %34, 2, !dbg !3050
  br i1 %cmp30, label %if.then31, label %if.else, !dbg !3051

if.then31:                                        ; preds = %if.then25
  store i8 1, i8* %isconnected, align 1, !dbg !3052
  br label %if.end36, !dbg !3053

if.else:                                          ; preds = %if.then25
  %35 = load i32, i32* %error, align 4, !dbg !3054
  %tobool32 = icmp ne i32 %35, 0, !dbg !3054
  br i1 %tobool32, label %if.then33, label %if.end35, !dbg !3056

if.then33:                                        ; preds = %if.else
  %36 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3057
  %37 = load i32, i32* %sockfd, align 4, !dbg !3059
  %call34 = call i32 @Curl_closesocket(%struct.connectdata* %36, i32 %37), !dbg !3060
  store i32 42, i32* %retval, align 4, !dbg !3061
  br label %return, !dbg !3061

if.end35:                                         ; preds = %if.else
  br label %if.end36

if.end36:                                         ; preds = %if.end35, %if.then31
  br label %if.end37, !dbg !3062

if.end37:                                         ; preds = %if.end36, %if.end22
  %family38 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %addr, i32 0, i32 0, !dbg !3063
  %38 = load i32, i32* %family38, align 8, !dbg !3063
  %cmp39 = icmp eq i32 %38, 2, !dbg !3065
  br i1 %cmp39, label %if.then40, label %if.end53, !dbg !3066

if.then40:                                        ; preds = %if.end37
  %39 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3067
  %40 = load i32, i32* %sockfd, align 4, !dbg !3069
  %family41 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %addr, i32 0, i32 0, !dbg !3070
  %41 = load i32, i32* %family41, align 8, !dbg !3070
  %_sa_ex_u42 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %addr, i32 0, i32 4, !dbg !3071
  %addr43 = bitcast %union.anon.2* %_sa_ex_u42 to %struct.sockaddr*, !dbg !3071
  %call44 = call i32 @Curl_ipv6_scope(%struct.sockaddr* %addr43), !dbg !3072
  %call45 = call i32 @bindlocal(%struct.connectdata* %39, i32 %40, i32 %41, i32 %call44), !dbg !3073
  store i32 %call45, i32* %result, align 4, !dbg !3074
  %42 = load i32, i32* %result, align 4, !dbg !3075
  %tobool46 = icmp ne i32 %42, 0, !dbg !3075
  br i1 %tobool46, label %if.then47, label %if.end52, !dbg !3077

if.then47:                                        ; preds = %if.then40
  %43 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3078
  %44 = load i32, i32* %sockfd, align 4, !dbg !3080
  %call48 = call i32 @Curl_closesocket(%struct.connectdata* %43, i32 %44), !dbg !3081
  %45 = load i32, i32* %result, align 4, !dbg !3082
  %cmp49 = icmp eq i32 %45, 1, !dbg !3084
  br i1 %cmp49, label %if.then50, label %if.end51, !dbg !3085

if.then50:                                        ; preds = %if.then47
  store i32 7, i32* %retval, align 4, !dbg !3086
  br label %return, !dbg !3086

if.end51:                                         ; preds = %if.then47
  %46 = load i32, i32* %result, align 4, !dbg !3088
  store i32 %46, i32* %retval, align 4, !dbg !3089
  br label %return, !dbg !3089

if.end52:                                         ; preds = %if.then40
  br label %if.end53, !dbg !3090

if.end53:                                         ; preds = %if.end52, %if.end37
  %47 = load i32, i32* %sockfd, align 4, !dbg !3091
  %call54 = call i32 @curlx_nonblock(i32 %47, i32 1), !dbg !3092
  %48 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3093
  %connecttime = getelementptr inbounds %struct.connectdata, %struct.connectdata* %48, i32 0, i32 44, !dbg !3094
  %call55 = call { i64, i64 } @curlx_tvnow(), !dbg !3095
  %49 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !3095
  %50 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %49, i32 0, i32 0, !dbg !3095
  %51 = extractvalue { i64, i64 } %call55, 0, !dbg !3095
  store i64 %51, i64* %50, align 8, !dbg !3095
  %52 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %49, i32 0, i32 1, !dbg !3095
  %53 = extractvalue { i64, i64 } %call55, 1, !dbg !3095
  store i64 %53, i64* %52, align 8, !dbg !3095
  %54 = bitcast %struct.timeval* %connecttime to i8*, !dbg !3095
  %55 = bitcast %struct.timeval* %coerce to i8*, !dbg !3095
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %54, i8* %55, i64 16, i32 8, i1 false), !dbg !3096
  %56 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3097
  %num_addr = getelementptr inbounds %struct.connectdata, %struct.connectdata* %56, i32 0, i32 45, !dbg !3099
  %57 = load i32, i32* %num_addr, align 8, !dbg !3099
  %cmp56 = icmp sgt i32 %57, 1, !dbg !3100
  br i1 %cmp56, label %if.then57, label %if.end58, !dbg !3101

if.then57:                                        ; preds = %if.end53
  %58 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3102
  %59 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3103
  %timeoutms_per_addr = getelementptr inbounds %struct.connectdata, %struct.connectdata* %59, i32 0, i32 46, !dbg !3104
  %60 = load i64, i64* %timeoutms_per_addr, align 8, !dbg !3104
  call void @Curl_expire_latest(%struct.Curl_easy* %58, i64 %60), !dbg !3105
  br label %if.end58, !dbg !3105

if.end58:                                         ; preds = %if.then57, %if.end53
  %61 = load i8, i8* %isconnected, align 1, !dbg !3106
  %tobool59 = trunc i8 %61 to i1, !dbg !3106
  br i1 %tobool59, label %if.else83, label %land.lhs.true60, !dbg !3108

land.lhs.true60:                                  ; preds = %if.end58
  %62 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3109
  %socktype61 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %62, i32 0, i32 11, !dbg !3111
  %63 = load i32, i32* %socktype61, align 4, !dbg !3111
  %cmp62 = icmp eq i32 %63, 1, !dbg !3112
  br i1 %cmp62, label %if.then63, label %if.else83, !dbg !3113

if.then63:                                        ; preds = %land.lhs.true60
  %64 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3114
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %64, i32 0, i32 43, !dbg !3117
  %tcp_fastopen = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 28, !dbg !3118
  %65 = load i8, i8* %tcp_fastopen, align 1, !dbg !3118
  %tobool64 = trunc i8 %65 to i1, !dbg !3118
  br i1 %tobool64, label %if.then65, label %if.else73, !dbg !3119

if.then65:                                        ; preds = %if.then63
  %66 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3120
  %given = getelementptr inbounds %struct.connectdata, %struct.connectdata* %66, i32 0, i32 48, !dbg !3123
  %67 = load %struct.Curl_handler*, %struct.Curl_handler** %given, align 8, !dbg !3123
  %flags = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %67, i32 0, i32 16, !dbg !3124
  %68 = load i32, i32* %flags, align 4, !dbg !3124
  %and = and i32 %68, 1, !dbg !3125
  %tobool66 = icmp ne i32 %and, 0, !dbg !3125
  br i1 %tobool66, label %if.then67, label %if.else71, !dbg !3126

if.then67:                                        ; preds = %if.then65
  %69 = load i32, i32* %sockfd, align 4, !dbg !3127
  %_sa_ex_u68 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %addr, i32 0, i32 4, !dbg !3128
  %addr69 = bitcast %union.anon.2* %_sa_ex_u68 to %struct.sockaddr*, !dbg !3128
  %addrlen = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %addr, i32 0, i32 3, !dbg !3129
  %70 = load i32, i32* %addrlen, align 4, !dbg !3129
  %call70 = call i32 @connect(i32 %69, %struct.sockaddr* %addr69, i32 %70), !dbg !3130
  store i32 %call70, i32* %rc, align 4, !dbg !3131
  br label %if.end72, !dbg !3132

if.else71:                                        ; preds = %if.then65
  store i32 0, i32* %rc, align 4, !dbg !3133
  br label %if.end72

if.end72:                                         ; preds = %if.else71, %if.then67
  br label %if.end78, !dbg !3134

if.else73:                                        ; preds = %if.then63
  %71 = load i32, i32* %sockfd, align 4, !dbg !3135
  %_sa_ex_u74 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %addr, i32 0, i32 4, !dbg !3137
  %addr75 = bitcast %union.anon.2* %_sa_ex_u74 to %struct.sockaddr*, !dbg !3137
  %addrlen76 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %addr, i32 0, i32 3, !dbg !3138
  %72 = load i32, i32* %addrlen76, align 4, !dbg !3138
  %call77 = call i32 @connect(i32 %71, %struct.sockaddr* %addr75, i32 %72), !dbg !3139
  store i32 %call77, i32* %rc, align 4, !dbg !3140
  br label %if.end78

if.end78:                                         ; preds = %if.else73, %if.end72
  %73 = load i32, i32* %rc, align 4, !dbg !3141
  %cmp79 = icmp eq i32 -1, %73, !dbg !3143
  br i1 %cmp79, label %if.then80, label %if.end82, !dbg !3144

if.then80:                                        ; preds = %if.end78
  %call81 = call i32* @__errno_location() #1, !dbg !3145
  %74 = load i32, i32* %call81, align 4, !dbg !3145
  store i32 %74, i32* %error, align 4, !dbg !3146
  br label %if.end82, !dbg !3147

if.end82:                                         ; preds = %if.then80, %if.end78
  br label %if.end84, !dbg !3148

if.else83:                                        ; preds = %land.lhs.true60, %if.end58
  %75 = load i32, i32* %sockfd, align 4, !dbg !3149
  %76 = load i32*, i32** %sockp.addr, align 8, !dbg !3151
  store i32 %75, i32* %76, align 4, !dbg !3152
  store i32 0, i32* %retval, align 4, !dbg !3153
  br label %return, !dbg !3153

if.end84:                                         ; preds = %if.end82
  %77 = load i32, i32* %rc, align 4, !dbg !3154
  %cmp85 = icmp eq i32 -1, %77, !dbg !3156
  br i1 %cmp85, label %if.then86, label %if.end90, !dbg !3157

if.then86:                                        ; preds = %if.end84
  %78 = load i32, i32* %error, align 4, !dbg !3158
  switch i32 %78, label %sw.default [
    i32 115, label %sw.bb
    i32 11, label %sw.bb
  ], !dbg !3160

sw.bb:                                            ; preds = %if.then86, %if.then86
  store i32 0, i32* %result, align 4, !dbg !3161
  br label %sw.epilog, !dbg !3163

sw.default:                                       ; preds = %if.then86
  %79 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3164
  %arraydecay87 = getelementptr inbounds [46 x i8], [46 x i8]* %ipaddress, i32 0, i32 0, !dbg !3165
  %80 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3166
  %81 = load i32, i32* %error, align 4, !dbg !3167
  %call88 = call i8* @Curl_strerror(%struct.connectdata* %80, i32 %81), !dbg !3168
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %79, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.14, i32 0, i32 0), i8* %arraydecay87, i8* %call88), !dbg !3169
  %82 = load i32, i32* %error, align 4, !dbg !3170
  %83 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3171
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %83, i32 0, i32 17, !dbg !3172
  %os_errno = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 18, !dbg !3173
  store i32 %82, i32* %os_errno, align 4, !dbg !3174
  %84 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3175
  %85 = load i32, i32* %sockfd, align 4, !dbg !3176
  %call89 = call i32 @Curl_closesocket(%struct.connectdata* %84, i32 %85), !dbg !3177
  store i32 7, i32* %result, align 4, !dbg !3178
  br label %sw.epilog, !dbg !3179

sw.epilog:                                        ; preds = %sw.default, %sw.bb
  br label %if.end90, !dbg !3180

if.end90:                                         ; preds = %sw.epilog, %if.end84
  %86 = load i32, i32* %result, align 4, !dbg !3181
  %tobool91 = icmp ne i32 %86, 0, !dbg !3181
  br i1 %tobool91, label %if.end93, label %if.then92, !dbg !3183

if.then92:                                        ; preds = %if.end90
  %87 = load i32, i32* %sockfd, align 4, !dbg !3184
  %88 = load i32*, i32** %sockp.addr, align 8, !dbg !3185
  store i32 %87, i32* %88, align 4, !dbg !3186
  br label %if.end93, !dbg !3187

if.end93:                                         ; preds = %if.then92, %if.end90
  %89 = load i32, i32* %result, align 4, !dbg !3188
  store i32 %89, i32* %retval, align 4, !dbg !3189
  br label %return, !dbg !3189

return:                                           ; preds = %if.end93, %if.else83, %if.end51, %if.then50, %if.then33, %if.then4, %if.then
  %90 = load i32, i32* %retval, align 4, !dbg !3190
  ret i32 %90, !dbg !3190
}

; Function Attrs: nounwind uwtable
define i32 @Curl_getconnectinfo(%struct.Curl_easy* %data, %struct.connectdata** %connp) #0 !dbg !1864 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %connp.addr = alloca %struct.connectdata**, align 8
  %sockfd = alloca i32, align 4
  %c = alloca %struct.connectdata*, align 8
  %find = alloca %struct.connfind, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !3191, metadata !1944), !dbg !3192
  store %struct.connectdata** %connp, %struct.connectdata*** %connp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata*** %connp.addr, metadata !3193, metadata !1944), !dbg !3194
  call void @llvm.dbg.declare(metadata i32* %sockfd, metadata !3195, metadata !1944), !dbg !3196
  br label %do.body, !dbg !3197

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !3198

do.end:                                           ; preds = %do.body
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3201
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 17, !dbg !3203
  %lastconnect = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 3, !dbg !3204
  %1 = load %struct.connectdata*, %struct.connectdata** %lastconnect, align 8, !dbg !3204
  %tobool = icmp ne %struct.connectdata* %1, null, !dbg !3201
  br i1 %tobool, label %land.lhs.true, label %if.else, !dbg !3205

land.lhs.true:                                    ; preds = %do.end
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3206
  %multi_easy = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 10, !dbg !3208
  %3 = load %struct.Curl_multi*, %struct.Curl_multi** %multi_easy, align 8, !dbg !3208
  %tobool1 = icmp ne %struct.Curl_multi* %3, null, !dbg !3206
  br i1 %tobool1, label %if.then, label %lor.lhs.false, !dbg !3209

lor.lhs.false:                                    ; preds = %land.lhs.true
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3210
  %multi = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 9, !dbg !3212
  %5 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !3212
  %tobool2 = icmp ne %struct.Curl_multi* %5, null, !dbg !3210
  br i1 %tobool2, label %if.then, label %if.else, !dbg !3213

if.then:                                          ; preds = %lor.lhs.false, %land.lhs.true
  call void @llvm.dbg.declare(metadata %struct.connectdata** %c, metadata !3214, metadata !1944), !dbg !3216
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3217
  %state3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 17, !dbg !3218
  %lastconnect4 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state3, i32 0, i32 3, !dbg !3219
  %7 = load %struct.connectdata*, %struct.connectdata** %lastconnect4, align 8, !dbg !3219
  store %struct.connectdata* %7, %struct.connectdata** %c, align 8, !dbg !3216
  call void @llvm.dbg.declare(metadata %struct.connfind* %find, metadata !3220, metadata !1944), !dbg !3221
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3222
  %state5 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %8, i32 0, i32 17, !dbg !3223
  %lastconnect6 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state5, i32 0, i32 3, !dbg !3224
  %9 = load %struct.connectdata*, %struct.connectdata** %lastconnect6, align 8, !dbg !3224
  %tofind = getelementptr inbounds %struct.connfind, %struct.connfind* %find, i32 0, i32 0, !dbg !3225
  store %struct.connectdata* %9, %struct.connectdata** %tofind, align 8, !dbg !3226
  %found = getelementptr inbounds %struct.connfind, %struct.connfind* %find, i32 0, i32 1, !dbg !3227
  store i8 0, i8* %found, align 8, !dbg !3228
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3229
  %multi_easy7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 10, !dbg !3230
  %11 = load %struct.Curl_multi*, %struct.Curl_multi** %multi_easy7, align 8, !dbg !3230
  %tobool8 = icmp ne %struct.Curl_multi* %11, null, !dbg !3229
  br i1 %tobool8, label %cond.true, label %cond.false, !dbg !3229

cond.true:                                        ; preds = %if.then
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3231
  %multi_easy9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 10, !dbg !3232
  %13 = load %struct.Curl_multi*, %struct.Curl_multi** %multi_easy9, align 8, !dbg !3232
  %conn_cache = getelementptr inbounds %struct.Curl_multi, %struct.Curl_multi* %13, i32 0, i32 16, !dbg !3233
  br label %cond.end, !dbg !3234

cond.false:                                       ; preds = %if.then
  %14 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3236
  %multi10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %14, i32 0, i32 9, !dbg !3237
  %15 = load %struct.Curl_multi*, %struct.Curl_multi** %multi10, align 8, !dbg !3237
  %conn_cache11 = getelementptr inbounds %struct.Curl_multi, %struct.Curl_multi* %15, i32 0, i32 16, !dbg !3238
  br label %cond.end, !dbg !3239

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi %struct.conncache* [ %conn_cache, %cond.true ], [ %conn_cache11, %cond.false ], !dbg !3241
  %16 = bitcast %struct.connfind* %find to i8*, !dbg !3243
  call void @Curl_conncache_foreach(%struct.conncache* %cond, i8* %16, i32 (%struct.connectdata*, i8*)* @conn_is_conn), !dbg !3244
  %found12 = getelementptr inbounds %struct.connfind, %struct.connfind* %find, i32 0, i32 1, !dbg !3245
  %17 = load i8, i8* %found12, align 8, !dbg !3245
  %tobool13 = trunc i8 %17 to i1, !dbg !3245
  br i1 %tobool13, label %if.end, label %if.then14, !dbg !3247

if.then14:                                        ; preds = %cond.end
  %18 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3248
  %state15 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %18, i32 0, i32 17, !dbg !3250
  %lastconnect16 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state15, i32 0, i32 3, !dbg !3251
  store %struct.connectdata* null, %struct.connectdata** %lastconnect16, align 8, !dbg !3252
  store i32 -1, i32* %retval, align 4, !dbg !3253
  br label %return, !dbg !3253

if.end:                                           ; preds = %cond.end
  %19 = load %struct.connectdata**, %struct.connectdata*** %connp.addr, align 8, !dbg !3254
  %tobool17 = icmp ne %struct.connectdata** %19, null, !dbg !3254
  br i1 %tobool17, label %if.then18, label %if.end19, !dbg !3256

if.then18:                                        ; preds = %if.end
  %20 = load %struct.connectdata*, %struct.connectdata** %c, align 8, !dbg !3257
  %21 = load %struct.connectdata**, %struct.connectdata*** %connp.addr, align 8, !dbg !3258
  store %struct.connectdata* %20, %struct.connectdata** %21, align 8, !dbg !3259
  br label %if.end19, !dbg !3260

if.end19:                                         ; preds = %if.then18, %if.end
  %22 = load %struct.connectdata*, %struct.connectdata** %c, align 8, !dbg !3261
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %22, i32 0, i32 33, !dbg !3262
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 0, !dbg !3261
  %23 = load i32, i32* %arrayidx, align 8, !dbg !3261
  store i32 %23, i32* %sockfd, align 4, !dbg !3263
  br label %if.end20, !dbg !3264

if.else:                                          ; preds = %lor.lhs.false, %do.end
  store i32 -1, i32* %retval, align 4, !dbg !3265
  br label %return, !dbg !3265

if.end20:                                         ; preds = %if.end19
  %24 = load i32, i32* %sockfd, align 4, !dbg !3266
  store i32 %24, i32* %retval, align 4, !dbg !3267
  br label %return, !dbg !3267

return:                                           ; preds = %if.end20, %if.else, %if.then14
  %25 = load i32, i32* %retval, align 4, !dbg !3268
  ret i32 %25, !dbg !3268
}

declare void @Curl_conncache_foreach(%struct.conncache*, i8*, i32 (%struct.connectdata*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @conn_is_conn(%struct.connectdata* %conn, i8* %param) #0 !dbg !1934 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %param.addr = alloca i8*, align 8
  %f = alloca %struct.connfind*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !3269, metadata !1944), !dbg !3270
  store i8* %param, i8** %param.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %param.addr, metadata !3271, metadata !1944), !dbg !3272
  call void @llvm.dbg.declare(metadata %struct.connfind** %f, metadata !3273, metadata !1944), !dbg !3274
  %0 = load i8*, i8** %param.addr, align 8, !dbg !3275
  %1 = bitcast i8* %0 to %struct.connfind*, !dbg !3276
  store %struct.connfind* %1, %struct.connfind** %f, align 8, !dbg !3274
  %2 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3277
  %3 = load %struct.connfind*, %struct.connfind** %f, align 8, !dbg !3279
  %tofind = getelementptr inbounds %struct.connfind, %struct.connfind* %3, i32 0, i32 0, !dbg !3280
  %4 = load %struct.connectdata*, %struct.connectdata** %tofind, align 8, !dbg !3280
  %cmp = icmp eq %struct.connectdata* %2, %4, !dbg !3281
  br i1 %cmp, label %if.then, label %if.end, !dbg !3282

if.then:                                          ; preds = %entry
  %5 = load %struct.connfind*, %struct.connfind** %f, align 8, !dbg !3283
  %found = getelementptr inbounds %struct.connfind, %struct.connfind* %5, i32 0, i32 1, !dbg !3285
  store i8 1, i8* %found, align 8, !dbg !3286
  store i32 1, i32* %retval, align 4, !dbg !3287
  br label %return, !dbg !3287

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !3288
  br label %return, !dbg !3288

return:                                           ; preds = %if.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !3289
  ret i32 %6, !dbg !3289
}

; Function Attrs: nounwind uwtable
define zeroext i1 @Curl_connalive(%struct.connectdata* %conn) #0 !dbg !1868 {
entry:
  %retval = alloca i1, align 1
  %conn.addr = alloca %struct.connectdata*, align 8
  %buf = alloca i8, align 1
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !3290, metadata !1944), !dbg !3291
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3292
  %ssl = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 38, !dbg !3294
  %arrayidx = getelementptr inbounds [2 x %struct.ssl_connect_data], [2 x %struct.ssl_connect_data]* %ssl, i64 0, i64 0, !dbg !3292
  %use = getelementptr inbounds %struct.ssl_connect_data, %struct.ssl_connect_data* %arrayidx, i32 0, i32 0, !dbg !3295
  %1 = load i8, i8* %use, align 8, !dbg !3295
  %tobool = trunc i8 %1 to i1, !dbg !3295
  br i1 %tobool, label %if.then, label %if.else, !dbg !3296

if.then:                                          ; preds = %entry
  store i1 false, i1* %retval, align 1, !dbg !3297
  br label %return, !dbg !3297

if.else:                                          ; preds = %entry
  %2 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3300
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 33, !dbg !3302
  %arrayidx1 = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 0, !dbg !3300
  %3 = load i32, i32* %arrayidx1, align 8, !dbg !3300
  %cmp = icmp eq i32 %3, -1, !dbg !3303
  br i1 %cmp, label %if.then2, label %if.else3, !dbg !3304

if.then2:                                         ; preds = %if.else
  store i1 false, i1* %retval, align 1, !dbg !3305
  br label %return, !dbg !3305

if.else3:                                         ; preds = %if.else
  call void @llvm.dbg.declare(metadata i8* %buf, metadata !3306, metadata !1944), !dbg !3308
  %4 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3309
  %sock4 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %4, i32 0, i32 33, !dbg !3311
  %arrayidx5 = getelementptr inbounds [2 x i32], [2 x i32]* %sock4, i64 0, i64 0, !dbg !3309
  %5 = load i32, i32* %arrayidx5, align 8, !dbg !3309
  %call = call i64 @recv(i32 %5, i8* %buf, i64 1, i32 2), !dbg !3312
  %cmp6 = icmp eq i64 %call, 0, !dbg !3313
  br i1 %cmp6, label %if.then7, label %if.end, !dbg !3314

if.then7:                                         ; preds = %if.else3
  store i1 false, i1* %retval, align 1, !dbg !3315
  br label %return, !dbg !3315

if.end:                                           ; preds = %if.else3
  br label %if.end8

if.end8:                                          ; preds = %if.end
  br label %if.end9

if.end9:                                          ; preds = %if.end8
  store i1 true, i1* %retval, align 1, !dbg !3317
  br label %return, !dbg !3317

return:                                           ; preds = %if.end9, %if.then7, %if.then2, %if.then
  %6 = load i1, i1* %retval, align 1, !dbg !3318
  ret i1 %6, !dbg !3318
}

declare i64 @recv(i32, i8*, i64, i32) #2

declare void @Curl_multi_closed(%struct.connectdata*, i32) #2

declare i32 @close(i32) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_socket(%struct.connectdata* %conn, %struct.Curl_addrinfo* %ai, %struct.Curl_sockaddr_ex* %addr, i32* %sockfd) #0 !dbg !1874 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %ai.addr = alloca %struct.Curl_addrinfo*, align 8
  %addr.addr = alloca %struct.Curl_sockaddr_ex*, align 8
  %sockfd.addr = alloca i32*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %dummy = alloca %struct.Curl_sockaddr_ex, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !3319, metadata !1944), !dbg !3320
  store %struct.Curl_addrinfo* %ai, %struct.Curl_addrinfo** %ai.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %ai.addr, metadata !3321, metadata !1944), !dbg !3322
  store %struct.Curl_sockaddr_ex* %addr, %struct.Curl_sockaddr_ex** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_sockaddr_ex** %addr.addr, metadata !3323, metadata !1944), !dbg !3324
  store i32* %sockfd, i32** %sockfd.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %sockfd.addr, metadata !3325, metadata !1944), !dbg !3326
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !3327, metadata !1944), !dbg !3328
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3329
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !3330
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !3330
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !3328
  call void @llvm.dbg.declare(metadata %struct.Curl_sockaddr_ex* %dummy, metadata !3331, metadata !1944), !dbg !3332
  %2 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3333
  %tobool = icmp ne %struct.Curl_sockaddr_ex* %2, null, !dbg !3333
  br i1 %tobool, label %if.end, label %if.then, !dbg !3335

if.then:                                          ; preds = %entry
  store %struct.Curl_sockaddr_ex* %dummy, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3336
  br label %if.end, !dbg !3337

if.end:                                           ; preds = %if.then, %entry
  %3 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai.addr, align 8, !dbg !3338
  %ai_family = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %3, i32 0, i32 1, !dbg !3339
  %4 = load i32, i32* %ai_family, align 4, !dbg !3339
  %5 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3340
  %family = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %5, i32 0, i32 0, !dbg !3341
  store i32 %4, i32* %family, align 8, !dbg !3342
  %6 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3343
  %socktype = getelementptr inbounds %struct.connectdata, %struct.connectdata* %6, i32 0, i32 11, !dbg !3344
  %7 = load i32, i32* %socktype, align 4, !dbg !3344
  %8 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3345
  %socktype2 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %8, i32 0, i32 1, !dbg !3346
  store i32 %7, i32* %socktype2, align 4, !dbg !3347
  %9 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3348
  %socktype3 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %9, i32 0, i32 11, !dbg !3349
  %10 = load i32, i32* %socktype3, align 4, !dbg !3349
  %cmp = icmp eq i32 %10, 2, !dbg !3350
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !3348

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !3351

cond.false:                                       ; preds = %if.end
  %11 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai.addr, align 8, !dbg !3353
  %ai_protocol = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %11, i32 0, i32 3, !dbg !3355
  %12 = load i32, i32* %ai_protocol, align 4, !dbg !3355
  br label %cond.end, !dbg !3356

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ 17, %cond.true ], [ %12, %cond.false ], !dbg !3357
  %13 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3359
  %protocol = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %13, i32 0, i32 2, !dbg !3360
  store i32 %cond, i32* %protocol, align 8, !dbg !3361
  %14 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai.addr, align 8, !dbg !3362
  %ai_addrlen = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %14, i32 0, i32 4, !dbg !3363
  %15 = load i32, i32* %ai_addrlen, align 8, !dbg !3363
  %16 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3364
  %addrlen = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %16, i32 0, i32 3, !dbg !3365
  store i32 %15, i32* %addrlen, align 4, !dbg !3366
  %17 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3367
  %addrlen4 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %17, i32 0, i32 3, !dbg !3369
  %18 = load i32, i32* %addrlen4, align 4, !dbg !3369
  %conv = zext i32 %18 to i64, !dbg !3367
  %cmp5 = icmp ugt i64 %conv, 128, !dbg !3370
  br i1 %cmp5, label %if.then7, label %if.end9, !dbg !3371

if.then7:                                         ; preds = %cond.end
  %19 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3372
  %addrlen8 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %19, i32 0, i32 3, !dbg !3373
  store i32 128, i32* %addrlen8, align 4, !dbg !3374
  br label %if.end9, !dbg !3372

if.end9:                                          ; preds = %if.then7, %cond.end
  %20 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3375
  %_sa_ex_u = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %20, i32 0, i32 4, !dbg !3376
  %addr10 = bitcast %union.anon.2* %_sa_ex_u to %struct.sockaddr*, !dbg !3376
  %21 = bitcast %struct.sockaddr* %addr10 to i8*, !dbg !3377
  %22 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai.addr, align 8, !dbg !3378
  %ai_addr = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %22, i32 0, i32 6, !dbg !3379
  %23 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr, align 8, !dbg !3379
  %24 = bitcast %struct.sockaddr* %23 to i8*, !dbg !3377
  %25 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3380
  %addrlen11 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %25, i32 0, i32 3, !dbg !3381
  %26 = load i32, i32* %addrlen11, align 4, !dbg !3381
  %conv12 = zext i32 %26 to i64, !dbg !3380
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %21, i8* %24, i64 %conv12, i32 2, i1 false), !dbg !3377
  %27 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3382
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %27, i32 0, i32 13, !dbg !3384
  %fopensocket = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 32, !dbg !3385
  %28 = load i32 (i8*, i32, %struct.curl_sockaddr*)*, i32 (i8*, i32, %struct.curl_sockaddr*)** %fopensocket, align 8, !dbg !3385
  %tobool13 = icmp ne i32 (i8*, i32, %struct.curl_sockaddr*)* %28, null, !dbg !3382
  br i1 %tobool13, label %if.then14, label %if.else, !dbg !3386

if.then14:                                        ; preds = %if.end9
  %29 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3387
  %set15 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %29, i32 0, i32 13, !dbg !3388
  %fopensocket16 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set15, i32 0, i32 32, !dbg !3389
  %30 = load i32 (i8*, i32, %struct.curl_sockaddr*)*, i32 (i8*, i32, %struct.curl_sockaddr*)** %fopensocket16, align 8, !dbg !3389
  %31 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3390
  %set17 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %31, i32 0, i32 13, !dbg !3391
  %opensocket_client = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set17, i32 0, i32 33, !dbg !3392
  %32 = load i8*, i8** %opensocket_client, align 8, !dbg !3392
  %33 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3393
  %34 = bitcast %struct.Curl_sockaddr_ex* %33 to %struct.curl_sockaddr*, !dbg !3394
  %call = call i32 %30(i8* %32, i32 0, %struct.curl_sockaddr* %34), !dbg !3387
  %35 = load i32*, i32** %sockfd.addr, align 8, !dbg !3395
  store i32 %call, i32* %35, align 4, !dbg !3396
  br label %if.end22, !dbg !3397

if.else:                                          ; preds = %if.end9
  %36 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3398
  %family18 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %36, i32 0, i32 0, !dbg !3399
  %37 = load i32, i32* %family18, align 8, !dbg !3399
  %38 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3400
  %socktype19 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %38, i32 0, i32 1, !dbg !3401
  %39 = load i32, i32* %socktype19, align 4, !dbg !3401
  %40 = load %struct.Curl_sockaddr_ex*, %struct.Curl_sockaddr_ex** %addr.addr, align 8, !dbg !3402
  %protocol20 = getelementptr inbounds %struct.Curl_sockaddr_ex, %struct.Curl_sockaddr_ex* %40, i32 0, i32 2, !dbg !3403
  %41 = load i32, i32* %protocol20, align 8, !dbg !3403
  %call21 = call i32 @socket(i32 %37, i32 %39, i32 %41) #7, !dbg !3404
  %42 = load i32*, i32** %sockfd.addr, align 8, !dbg !3405
  store i32 %call21, i32* %42, align 4, !dbg !3406
  br label %if.end22

if.end22:                                         ; preds = %if.else, %if.then14
  %43 = load i32*, i32** %sockfd.addr, align 8, !dbg !3407
  %44 = load i32, i32* %43, align 4, !dbg !3409
  %cmp23 = icmp eq i32 %44, -1, !dbg !3410
  br i1 %cmp23, label %if.then25, label %if.end26, !dbg !3411

if.then25:                                        ; preds = %if.end22
  store i32 7, i32* %retval, align 4, !dbg !3412
  br label %return, !dbg !3412

if.end26:                                         ; preds = %if.end22
  store i32 0, i32* %retval, align 4, !dbg !3413
  br label %return, !dbg !3413

return:                                           ; preds = %if.end26, %if.then25
  %45 = load i32, i32* %retval, align 4, !dbg !3414
  ret i32 %45, !dbg !3414
}

; Function Attrs: nounwind
declare i32 @socket(i32, i32, i32) #4

; Function Attrs: nounwind uwtable
define void @Curl_conncontrol(%struct.connectdata* %conn, i32 %ctrl) #0 !dbg !1909 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %ctrl.addr = alloca i32, align 4
  %closeit = alloca i8, align 1
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !3415, metadata !1944), !dbg !3416
  store i32 %ctrl, i32* %ctrl.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %ctrl.addr, metadata !3417, metadata !1944), !dbg !3418
  call void @llvm.dbg.declare(metadata i8* %closeit, metadata !3419, metadata !1944), !dbg !3420
  %0 = load i32, i32* %ctrl.addr, align 4, !dbg !3421
  %cmp = icmp eq i32 %0, 1, !dbg !3422
  br i1 %cmp, label %lor.end, label %lor.rhs, !dbg !3423

lor.rhs:                                          ; preds = %entry
  %1 = load i32, i32* %ctrl.addr, align 4, !dbg !3424
  %cmp1 = icmp eq i32 %1, 2, !dbg !3425
  br i1 %cmp1, label %land.rhs, label %land.end, !dbg !3426

land.rhs:                                         ; preds = %lor.rhs
  %2 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3427
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %2, i32 0, i32 47, !dbg !3429
  %3 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !3429
  %flags = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %3, i32 0, i32 16, !dbg !3430
  %4 = load i32, i32* %flags, align 4, !dbg !3430
  %and = and i32 %4, 512, !dbg !3431
  %tobool = icmp ne i32 %and, 0, !dbg !3432
  %lnot = xor i1 %tobool, true, !dbg !3432
  br label %land.end

land.end:                                         ; preds = %land.rhs, %lor.rhs
  %5 = phi i1 [ false, %lor.rhs ], [ %lnot, %land.rhs ]
  br label %lor.end, !dbg !3433

lor.end:                                          ; preds = %land.end, %entry
  %6 = phi i1 [ true, %entry ], [ %5, %land.end ]
  %frombool = zext i1 %6 to i8, !dbg !3434
  store i8 %frombool, i8* %closeit, align 1, !dbg !3434
  %7 = load i32, i32* %ctrl.addr, align 4, !dbg !3436
  %cmp2 = icmp eq i32 %7, 2, !dbg !3438
  br i1 %cmp2, label %land.lhs.true, label %if.else, !dbg !3439

land.lhs.true:                                    ; preds = %lor.end
  %8 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3440
  %handler3 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %8, i32 0, i32 47, !dbg !3441
  %9 = load %struct.Curl_handler*, %struct.Curl_handler** %handler3, align 8, !dbg !3441
  %flags4 = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %9, i32 0, i32 16, !dbg !3442
  %10 = load i32, i32* %flags4, align 4, !dbg !3442
  %and5 = and i32 %10, 512, !dbg !3443
  %tobool6 = icmp ne i32 %and5, 0, !dbg !3443
  br i1 %tobool6, label %if.then, label %if.else, !dbg !3444

if.then:                                          ; preds = %land.lhs.true
  br label %do.body, !dbg !3445

do.body:                                          ; preds = %if.then
  br label %do.end, !dbg !3446

do.end:                                           ; preds = %do.body
  br label %if.end19, !dbg !3449

if.else:                                          ; preds = %land.lhs.true, %lor.end
  %11 = load i8, i8* %closeit, align 1, !dbg !3451
  %tobool7 = trunc i8 %11 to i1, !dbg !3451
  %conv = zext i1 %tobool7 to i32, !dbg !3451
  %12 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3453
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %12, i32 0, i32 43, !dbg !3454
  %close = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 0, !dbg !3455
  %13 = load i8, i8* %close, align 1, !dbg !3455
  %tobool8 = trunc i8 %13 to i1, !dbg !3455
  %conv9 = zext i1 %tobool8 to i32, !dbg !3453
  %cmp10 = icmp ne i32 %conv, %conv9, !dbg !3456
  br i1 %cmp10, label %if.then12, label %if.end, !dbg !3457

if.then12:                                        ; preds = %if.else
  br label %do.body13, !dbg !3458

do.body13:                                        ; preds = %if.then12
  br label %do.end14, !dbg !3460

do.end14:                                         ; preds = %do.body13
  %14 = load i8, i8* %closeit, align 1, !dbg !3463
  %tobool15 = trunc i8 %14 to i1, !dbg !3463
  %15 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3464
  %bits16 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %15, i32 0, i32 43, !dbg !3465
  %close17 = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits16, i32 0, i32 0, !dbg !3466
  %frombool18 = zext i1 %tobool15 to i8, !dbg !3467
  store i8 %frombool18, i8* %close17, align 1, !dbg !3467
  br label %if.end, !dbg !3468

if.end:                                           ; preds = %do.end14, %if.else
  br label %if.end19

if.end19:                                         ; preds = %if.end, %do.end
  ret void, !dbg !3469
}

; Function Attrs: nounwind uwtable
define zeroext i1 @Curl_conn_data_pending(%struct.connectdata* %conn, i32 %sockindex) #0 !dbg !1912 {
entry:
  %retval = alloca i1, align 1
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockindex.addr = alloca i32, align 4
  %readable = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !3470, metadata !1944), !dbg !3471
  store i32 %sockindex, i32* %sockindex.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockindex.addr, metadata !3472, metadata !1944), !dbg !3473
  call void @llvm.dbg.declare(metadata i32* %readable, metadata !3474, metadata !1944), !dbg !3475
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3476
  %1 = load i32, i32* %sockindex.addr, align 4, !dbg !3478
  %call = call zeroext i1 @Curl_recv_has_postponed_data(%struct.connectdata* %0, i32 %1), !dbg !3479
  br i1 %call, label %if.then, label %if.end, !dbg !3480

if.then:                                          ; preds = %entry
  store i1 true, i1* %retval, align 1, !dbg !3481
  br label %return, !dbg !3481

if.end:                                           ; preds = %entry
  %2 = load i32, i32* %sockindex.addr, align 4, !dbg !3482
  %idxprom = sext i32 %2 to i64, !dbg !3482
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3482
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %3, i32 0, i32 33, !dbg !3482
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 %idxprom, !dbg !3482
  %4 = load i32, i32* %arrayidx, align 4, !dbg !3482
  %call1 = call i32 @Curl_socket_check(i32 %4, i32 -1, i32 -1, i64 0), !dbg !3482
  store i32 %call1, i32* %readable, align 4, !dbg !3483
  %5 = load i32, i32* %readable, align 4, !dbg !3484
  %cmp = icmp sgt i32 %5, 0, !dbg !3485
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !3486

land.rhs:                                         ; preds = %if.end
  %6 = load i32, i32* %readable, align 4, !dbg !3487
  %and = and i32 %6, 1, !dbg !3489
  %tobool = icmp ne i32 %and, 0, !dbg !3490
  br label %land.end

land.end:                                         ; preds = %land.rhs, %if.end
  %7 = phi i1 [ false, %if.end ], [ %tobool, %land.rhs ]
  store i1 %7, i1* %retval, align 1, !dbg !3491
  br label %return, !dbg !3491

return:                                           ; preds = %land.end, %if.then
  %8 = load i1, i1* %retval, align 1, !dbg !3493
  ret i1 %8, !dbg !3493
}

declare zeroext i1 @Curl_recv_has_postponed_data(%struct.connectdata*, i32) #2

declare i8* @Curl_inet_ntop(i32, i8*, i8*, i64) #2

; Function Attrs: nounwind readnone
declare zeroext i16 @ntohs(i16 zeroext) #5

declare i32 @curl_msnprintf(i8*, i64, i8*, ...) #2

; Function Attrs: nounwind
declare i32 @getsockopt(i32, i32, i32, i8*, i32*) #4

; Function Attrs: nounwind uwtable
define internal void @tcpkeepalive(%struct.Curl_easy* %data, i32 %sockfd) #0 !dbg !1928 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %sockfd.addr = alloca i32, align 4
  %optval = alloca i32, align 4
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !3494, metadata !1944), !dbg !3495
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !3496, metadata !1944), !dbg !3497
  call void @llvm.dbg.declare(metadata i32* %optval, metadata !3498, metadata !1944), !dbg !3499
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3500
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 13, !dbg !3501
  %tcp_keepalive = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 142, !dbg !3502
  %1 = load i8, i8* %tcp_keepalive, align 8, !dbg !3502
  %tobool = trunc i8 %1 to i1, !dbg !3502
  %cond = select i1 %tobool, i32 1, i32 0, !dbg !3500
  store i32 %cond, i32* %optval, align 4, !dbg !3499
  %2 = load i32, i32* %sockfd.addr, align 4, !dbg !3503
  %3 = bitcast i32* %optval to i8*, !dbg !3505
  %call = call i32 @setsockopt(i32 %2, i32 1, i32 9, i8* %3, i32 4) #7, !dbg !3506
  %cmp = icmp slt i32 %call, 0, !dbg !3507
  br i1 %cmp, label %if.then, label %if.else, !dbg !3508

if.then:                                          ; preds = %entry
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3509
  %5 = load i32, i32* %sockfd.addr, align 4, !dbg !3511
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %4, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.15, i32 0, i32 0), i32 %5), !dbg !3512
  br label %if.end12, !dbg !3513

if.else:                                          ; preds = %entry
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3514
  %set1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 13, !dbg !3516
  %tcp_keepidle = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set1, i32 0, i32 143, !dbg !3517
  %7 = load i64, i64* %tcp_keepidle, align 8, !dbg !3517
  %call2 = call i32 @curlx_sltosi(i64 %7), !dbg !3518
  store i32 %call2, i32* %optval, align 4, !dbg !3519
  %8 = load i32, i32* %sockfd.addr, align 4, !dbg !3520
  %9 = bitcast i32* %optval to i8*, !dbg !3522
  %call3 = call i32 @setsockopt(i32 %8, i32 6, i32 4, i8* %9, i32 4) #7, !dbg !3523
  %cmp4 = icmp slt i32 %call3, 0, !dbg !3524
  br i1 %cmp4, label %if.then5, label %if.end, !dbg !3525

if.then5:                                         ; preds = %if.else
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3526
  %11 = load i32, i32* %sockfd.addr, align 4, !dbg !3528
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %10, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.16, i32 0, i32 0), i32 %11), !dbg !3529
  br label %if.end, !dbg !3530

if.end:                                           ; preds = %if.then5, %if.else
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3531
  %set6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 13, !dbg !3532
  %tcp_keepintvl = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set6, i32 0, i32 144, !dbg !3533
  %13 = load i64, i64* %tcp_keepintvl, align 8, !dbg !3533
  %call7 = call i32 @curlx_sltosi(i64 %13), !dbg !3534
  store i32 %call7, i32* %optval, align 4, !dbg !3535
  %14 = load i32, i32* %sockfd.addr, align 4, !dbg !3536
  %15 = bitcast i32* %optval to i8*, !dbg !3538
  %call8 = call i32 @setsockopt(i32 %14, i32 6, i32 5, i8* %15, i32 4) #7, !dbg !3539
  %cmp9 = icmp slt i32 %call8, 0, !dbg !3540
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !3541

if.then10:                                        ; preds = %if.end
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3542
  %17 = load i32, i32* %sockfd.addr, align 4, !dbg !3544
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %16, i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.17, i32 0, i32 0), i32 %17), !dbg !3545
  br label %if.end11, !dbg !3546

if.end11:                                         ; preds = %if.then10, %if.end
  br label %if.end12

if.end12:                                         ; preds = %if.end11, %if.then
  ret void, !dbg !3547
}

; Function Attrs: nounwind uwtable
define internal i32 @bindlocal(%struct.connectdata* %conn, i32 %sockfd, i32 %af, i32 %scope) #0 !dbg !1931 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockfd.addr = alloca i32, align 4
  %af.addr = alloca i32, align 4
  %scope.addr = alloca i32, align 4
  %data = alloca %struct.Curl_easy*, align 8
  %sa = alloca %struct.Curl_sockaddr_storage, align 8
  %sock = alloca %struct.sockaddr*, align 8
  %sizeof_sa = alloca i32, align 4
  %si4 = alloca %struct.sockaddr_in*, align 8
  %h = alloca %struct.Curl_dns_entry*, align 8
  %port = alloca i16, align 2
  %portnum = alloca i32, align 4
  %dev = alloca i8*, align 8
  %error = alloca i32, align 4
  %myhost = alloca [256 x i8], align 16
  %done = alloca i32, align 4
  %is_interface = alloca i8, align 1
  %is_host = alloca i8, align 1
  %ipver = alloca i64, align 8
  %rc = alloca i32, align 4
  %add92 = alloca %struct.Curl_sockaddr_storage, align 8
  %size = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !3548, metadata !1944), !dbg !3549
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !3550, metadata !1944), !dbg !3551
  store i32 %af, i32* %af.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %af.addr, metadata !3552, metadata !1944), !dbg !3553
  store i32 %scope, i32* %scope.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %scope.addr, metadata !3554, metadata !1944), !dbg !3555
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !3556, metadata !1944), !dbg !3557
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3558
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !3559
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !3559
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !3557
  call void @llvm.dbg.declare(metadata %struct.Curl_sockaddr_storage* %sa, metadata !3560, metadata !1944), !dbg !3561
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %sock, metadata !3562, metadata !1944), !dbg !3563
  %2 = bitcast %struct.Curl_sockaddr_storage* %sa to %struct.sockaddr*, !dbg !3564
  store %struct.sockaddr* %2, %struct.sockaddr** %sock, align 8, !dbg !3563
  call void @llvm.dbg.declare(metadata i32* %sizeof_sa, metadata !3565, metadata !1944), !dbg !3566
  store i32 0, i32* %sizeof_sa, align 4, !dbg !3566
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in** %si4, metadata !3567, metadata !1944), !dbg !3568
  %3 = bitcast %struct.Curl_sockaddr_storage* %sa to %struct.sockaddr_in*, !dbg !3569
  store %struct.sockaddr_in* %3, %struct.sockaddr_in** %si4, align 8, !dbg !3568
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %h, metadata !3570, metadata !1944), !dbg !3571
  store %struct.Curl_dns_entry* null, %struct.Curl_dns_entry** %h, align 8, !dbg !3571
  call void @llvm.dbg.declare(metadata i16* %port, metadata !3572, metadata !1944), !dbg !3573
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3574
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 13, !dbg !3575
  %localport = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 18, !dbg !3576
  %5 = load i16, i16* %localport, align 8, !dbg !3576
  store i16 %5, i16* %port, align 2, !dbg !3573
  call void @llvm.dbg.declare(metadata i32* %portnum, metadata !3577, metadata !1944), !dbg !3578
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3579
  %set2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 13, !dbg !3580
  %localportrange = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set2, i32 0, i32 19, !dbg !3581
  %7 = load i32, i32* %localportrange, align 4, !dbg !3581
  store i32 %7, i32* %portnum, align 4, !dbg !3578
  call void @llvm.dbg.declare(metadata i8** %dev, metadata !3582, metadata !1944), !dbg !3583
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3584
  %set3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %8, i32 0, i32 13, !dbg !3585
  %str = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set3, i32 0, i32 128, !dbg !3586
  %arrayidx = getelementptr inbounds [56 x i8*], [56 x i8*]* %str, i64 0, i64 8, !dbg !3584
  %9 = load i8*, i8** %arrayidx, align 8, !dbg !3584
  store i8* %9, i8** %dev, align 8, !dbg !3583
  call void @llvm.dbg.declare(metadata i32* %error, metadata !3587, metadata !1944), !dbg !3588
  %10 = load i8*, i8** %dev, align 8, !dbg !3589
  %tobool = icmp ne i8* %10, null, !dbg !3589
  br i1 %tobool, label %if.end, label %land.lhs.true, !dbg !3591

land.lhs.true:                                    ; preds = %entry
  %11 = load i16, i16* %port, align 2, !dbg !3592
  %tobool4 = icmp ne i16 %11, 0, !dbg !3592
  br i1 %tobool4, label %if.end, label %if.then, !dbg !3594

if.then:                                          ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !3595
  br label %return, !dbg !3595

if.end:                                           ; preds = %land.lhs.true, %entry
  %12 = bitcast %struct.Curl_sockaddr_storage* %sa to i8*, !dbg !3596
  call void @llvm.memset.p0i8.i64(i8* %12, i8 0, i64 128, i32 8, i1 false), !dbg !3596
  %13 = load i8*, i8** %dev, align 8, !dbg !3597
  %tobool5 = icmp ne i8* %13, null, !dbg !3597
  br i1 %tobool5, label %land.lhs.true6, label %if.else79, !dbg !3599

land.lhs.true6:                                   ; preds = %if.end
  %14 = load i8*, i8** %dev, align 8, !dbg !3600
  %call = call i64 @strlen(i8* %14) #8, !dbg !3602
  %cmp = icmp ult i64 %call, 255, !dbg !3603
  br i1 %cmp, label %if.then7, label %if.else79, !dbg !3604

if.then7:                                         ; preds = %land.lhs.true6
  call void @llvm.dbg.declare(metadata [256 x i8]* %myhost, metadata !3605, metadata !1944), !dbg !3607
  %15 = bitcast [256 x i8]* %myhost to i8*, !dbg !3607
  call void @llvm.memset.p0i8.i64(i8* %15, i8 0, i64 256, i32 16, i1 false), !dbg !3607
  call void @llvm.dbg.declare(metadata i32* %done, metadata !3608, metadata !1944), !dbg !3609
  store i32 0, i32* %done, align 4, !dbg !3609
  call void @llvm.dbg.declare(metadata i8* %is_interface, metadata !3610, metadata !1944), !dbg !3611
  store i8 0, i8* %is_interface, align 1, !dbg !3611
  call void @llvm.dbg.declare(metadata i8* %is_host, metadata !3612, metadata !1944), !dbg !3613
  store i8 0, i8* %is_host, align 1, !dbg !3613
  %16 = load i8*, i8** @bindlocal.if_prefix, align 8, !dbg !3614
  %17 = load i8*, i8** %dev, align 8, !dbg !3616
  %18 = load i8*, i8** @bindlocal.if_prefix, align 8, !dbg !3617
  %call8 = call i64 @strlen(i8* %18) #8, !dbg !3618
  %call9 = call i32 @strncmp(i8* %16, i8* %17, i64 %call8) #8, !dbg !3619
  %cmp10 = icmp eq i32 %call9, 0, !dbg !3621
  br i1 %cmp10, label %if.then11, label %if.else, !dbg !3622

if.then11:                                        ; preds = %if.then7
  %19 = load i8*, i8** @bindlocal.if_prefix, align 8, !dbg !3623
  %call12 = call i64 @strlen(i8* %19) #8, !dbg !3625
  %20 = load i8*, i8** %dev, align 8, !dbg !3626
  %add.ptr = getelementptr inbounds i8, i8* %20, i64 %call12, !dbg !3626
  store i8* %add.ptr, i8** %dev, align 8, !dbg !3626
  store i8 1, i8* %is_interface, align 1, !dbg !3627
  br label %if.end20, !dbg !3628

if.else:                                          ; preds = %if.then7
  %21 = load i8*, i8** @bindlocal.host_prefix, align 8, !dbg !3629
  %22 = load i8*, i8** %dev, align 8, !dbg !3631
  %23 = load i8*, i8** @bindlocal.host_prefix, align 8, !dbg !3632
  %call13 = call i64 @strlen(i8* %23) #8, !dbg !3633
  %call14 = call i32 @strncmp(i8* %21, i8* %22, i64 %call13) #8, !dbg !3634
  %cmp15 = icmp eq i32 %call14, 0, !dbg !3636
  br i1 %cmp15, label %if.then16, label %if.end19, !dbg !3637

if.then16:                                        ; preds = %if.else
  %24 = load i8*, i8** @bindlocal.host_prefix, align 8, !dbg !3638
  %call17 = call i64 @strlen(i8* %24) #8, !dbg !3640
  %25 = load i8*, i8** %dev, align 8, !dbg !3641
  %add.ptr18 = getelementptr inbounds i8, i8* %25, i64 %call17, !dbg !3641
  store i8* %add.ptr18, i8** %dev, align 8, !dbg !3641
  store i8 1, i8* %is_host, align 1, !dbg !3642
  br label %if.end19, !dbg !3643

if.end19:                                         ; preds = %if.then16, %if.else
  br label %if.end20

if.end20:                                         ; preds = %if.end19, %if.then11
  %26 = load i8, i8* %is_host, align 1, !dbg !3644
  %tobool21 = trunc i8 %26 to i1, !dbg !3644
  br i1 %tobool21, label %if.end38, label %if.then22, !dbg !3646

if.then22:                                        ; preds = %if.end20
  %27 = load i32, i32* %af.addr, align 4, !dbg !3647
  %28 = load i32, i32* %scope.addr, align 4, !dbg !3649
  %29 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3650
  %scope_id = getelementptr inbounds %struct.connectdata, %struct.connectdata* %29, i32 0, i32 10, !dbg !3651
  %30 = load i32, i32* %scope_id, align 8, !dbg !3651
  %31 = load i8*, i8** %dev, align 8, !dbg !3652
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %myhost, i32 0, i32 0, !dbg !3653
  %call23 = call i32 @Curl_if2ip(i32 %27, i32 %28, i32 %30, i8* %31, i8* %arraydecay, i32 256), !dbg !3654
  switch i32 %call23, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb27
    i32 2, label %sw.bb28
  ], !dbg !3655

sw.bb:                                            ; preds = %if.then22
  %32 = load i8, i8* %is_interface, align 1, !dbg !3656
  %tobool24 = trunc i8 %32 to i1, !dbg !3656
  br i1 %tobool24, label %if.then25, label %if.end26, !dbg !3659

if.then25:                                        ; preds = %sw.bb
  %33 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3660
  %34 = load i8*, i8** %dev, align 8, !dbg !3662
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %33, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.20, i32 0, i32 0), i8* %34), !dbg !3663
  store i32 45, i32* %retval, align 4, !dbg !3664
  br label %return, !dbg !3664

if.end26:                                         ; preds = %sw.bb
  br label %sw.epilog, !dbg !3665

sw.bb27:                                          ; preds = %if.then22
  store i32 1, i32* %retval, align 4, !dbg !3666
  br label %return, !dbg !3666

sw.bb28:                                          ; preds = %if.then22
  store i8 1, i8* %is_interface, align 1, !dbg !3667
  %35 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3668
  %36 = load i8*, i8** %dev, align 8, !dbg !3669
  %arraydecay29 = getelementptr inbounds [256 x i8], [256 x i8]* %myhost, i32 0, i32 0, !dbg !3670
  %37 = load i32, i32* %af.addr, align 4, !dbg !3671
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %35, i8* getelementptr inbounds ([53 x i8], [53 x i8]* @.str.21, i32 0, i32 0), i8* %36, i8* %arraydecay29, i32 %37), !dbg !3672
  store i32 1, i32* %done, align 4, !dbg !3673
  %38 = load i32, i32* %sockfd.addr, align 4, !dbg !3674
  %39 = load i8*, i8** %dev, align 8, !dbg !3676
  %40 = load i8*, i8** %dev, align 8, !dbg !3677
  %call30 = call i64 @strlen(i8* %40) #8, !dbg !3678
  %conv = trunc i64 %call30 to i32, !dbg !3679
  %add = add i32 %conv, 1, !dbg !3680
  %call31 = call i32 @setsockopt(i32 %38, i32 1, i32 25, i8* %39, i32 %add) #7, !dbg !3681
  %cmp32 = icmp ne i32 %call31, 0, !dbg !3682
  br i1 %cmp32, label %if.then34, label %if.end37, !dbg !3683

if.then34:                                        ; preds = %sw.bb28
  %call35 = call i32* @__errno_location() #1, !dbg !3684
  %41 = load i32, i32* %call35, align 4, !dbg !3684
  store i32 %41, i32* %error, align 4, !dbg !3686
  %42 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3687
  %43 = load i8*, i8** %dev, align 8, !dbg !3688
  %44 = load i32, i32* %error, align 4, !dbg !3689
  %45 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3690
  %46 = load i32, i32* %error, align 4, !dbg !3691
  %call36 = call i8* @Curl_strerror(%struct.connectdata* %45, i32 %46), !dbg !3692
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %42, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.22, i32 0, i32 0), i8* %43, i32 %44, i8* %call36), !dbg !3693
  br label %if.end37, !dbg !3694

if.end37:                                         ; preds = %if.then34, %sw.bb28
  br label %sw.epilog, !dbg !3695

sw.epilog:                                        ; preds = %if.then22, %if.end37, %if.end26
  br label %if.end38, !dbg !3696

if.end38:                                         ; preds = %sw.epilog, %if.end20
  %47 = load i8, i8* %is_interface, align 1, !dbg !3697
  %tobool39 = trunc i8 %47 to i1, !dbg !3697
  br i1 %tobool39, label %if.end60, label %if.then40, !dbg !3699

if.then40:                                        ; preds = %if.end38
  call void @llvm.dbg.declare(metadata i64* %ipver, metadata !3700, metadata !1944), !dbg !3702
  %48 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3703
  %ip_version = getelementptr inbounds %struct.connectdata, %struct.connectdata* %48, i32 0, i32 49, !dbg !3704
  %49 = load i64, i64* %ip_version, align 8, !dbg !3704
  store i64 %49, i64* %ipver, align 8, !dbg !3702
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !3705, metadata !1944), !dbg !3706
  %50 = load i32, i32* %af.addr, align 4, !dbg !3707
  %cmp41 = icmp eq i32 %50, 2, !dbg !3709
  br i1 %cmp41, label %if.then43, label %if.end45, !dbg !3710

if.then43:                                        ; preds = %if.then40
  %51 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3711
  %ip_version44 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %51, i32 0, i32 49, !dbg !3712
  store i64 1, i64* %ip_version44, align 8, !dbg !3713
  br label %if.end45, !dbg !3711

if.end45:                                         ; preds = %if.then43, %if.then40
  %52 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3714
  %53 = load i8*, i8** %dev, align 8, !dbg !3715
  %call46 = call i32 @Curl_resolv(%struct.connectdata* %52, i8* %53, i32 0, %struct.Curl_dns_entry** %h), !dbg !3716
  store i32 %call46, i32* %rc, align 4, !dbg !3717
  %54 = load i32, i32* %rc, align 4, !dbg !3718
  %cmp47 = icmp eq i32 %54, 1, !dbg !3720
  br i1 %cmp47, label %if.then49, label %if.end50, !dbg !3721

if.then49:                                        ; preds = %if.end45
  br label %if.end50, !dbg !3722

if.end50:                                         ; preds = %if.then49, %if.end45
  %55 = load i64, i64* %ipver, align 8, !dbg !3723
  %56 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3724
  %ip_version51 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %56, i32 0, i32 49, !dbg !3725
  store i64 %55, i64* %ip_version51, align 8, !dbg !3726
  %57 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %h, align 8, !dbg !3727
  %tobool52 = icmp ne %struct.Curl_dns_entry* %57, null, !dbg !3727
  br i1 %tobool52, label %if.then53, label %if.else58, !dbg !3729

if.then53:                                        ; preds = %if.end50
  %58 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %h, align 8, !dbg !3730
  %addr = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %58, i32 0, i32 0, !dbg !3732
  %59 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !3732
  %arraydecay54 = getelementptr inbounds [256 x i8], [256 x i8]* %myhost, i32 0, i32 0, !dbg !3733
  %call55 = call i8* @Curl_printable_address(%struct.Curl_addrinfo* %59, i8* %arraydecay54, i64 256), !dbg !3734
  %60 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3735
  %61 = load i8*, i8** %dev, align 8, !dbg !3736
  %62 = load i32, i32* %af.addr, align 4, !dbg !3737
  %arraydecay56 = getelementptr inbounds [256 x i8], [256 x i8]* %myhost, i32 0, i32 0, !dbg !3738
  %63 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %h, align 8, !dbg !3739
  %addr57 = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %63, i32 0, i32 0, !dbg !3740
  %64 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr57, align 8, !dbg !3740
  %ai_family = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %64, i32 0, i32 1, !dbg !3741
  %65 = load i32, i32* %ai_family, align 4, !dbg !3741
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %60, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.23, i32 0, i32 0), i8* %61, i32 %62, i8* %arraydecay56, i32 %65), !dbg !3742
  %66 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3743
  %67 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %h, align 8, !dbg !3744
  call void @Curl_resolv_unlock(%struct.Curl_easy* %66, %struct.Curl_dns_entry* %67), !dbg !3745
  store i32 1, i32* %done, align 4, !dbg !3746
  br label %if.end59, !dbg !3747

if.else58:                                        ; preds = %if.end50
  store i32 -1, i32* %done, align 4, !dbg !3748
  br label %if.end59

if.end59:                                         ; preds = %if.else58, %if.then53
  br label %if.end60, !dbg !3750

if.end60:                                         ; preds = %if.end59, %if.end38
  %68 = load i32, i32* %done, align 4, !dbg !3751
  %cmp61 = icmp sgt i32 %68, 0, !dbg !3753
  br i1 %cmp61, label %if.then63, label %if.end74, !dbg !3754

if.then63:                                        ; preds = %if.end60
  %69 = load i32, i32* %af.addr, align 4, !dbg !3755
  %cmp64 = icmp eq i32 %69, 2, !dbg !3758
  br i1 %cmp64, label %land.lhs.true66, label %if.end73, !dbg !3759

land.lhs.true66:                                  ; preds = %if.then63
  %arraydecay67 = getelementptr inbounds [256 x i8], [256 x i8]* %myhost, i32 0, i32 0, !dbg !3760
  %70 = load %struct.sockaddr_in*, %struct.sockaddr_in** %si4, align 8, !dbg !3760
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %70, i32 0, i32 2, !dbg !3760
  %71 = bitcast %struct.in_addr* %sin_addr to i8*, !dbg !3760
  %call68 = call i32 @inet_pton(i32 2, i8* %arraydecay67, i8* %71) #7, !dbg !3760
  %cmp69 = icmp sgt i32 %call68, 0, !dbg !3761
  br i1 %cmp69, label %if.then71, label %if.end73, !dbg !3762

if.then71:                                        ; preds = %land.lhs.true66
  %72 = load %struct.sockaddr_in*, %struct.sockaddr_in** %si4, align 8, !dbg !3764
  %sin_family = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %72, i32 0, i32 0, !dbg !3766
  store i16 2, i16* %sin_family, align 4, !dbg !3767
  %73 = load i16, i16* %port, align 2, !dbg !3768
  %call72 = call zeroext i16 @htons(i16 zeroext %73) #1, !dbg !3769
  %74 = load %struct.sockaddr_in*, %struct.sockaddr_in** %si4, align 8, !dbg !3770
  %sin_port = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %74, i32 0, i32 1, !dbg !3771
  store i16 %call72, i16* %sin_port, align 2, !dbg !3772
  store i32 16, i32* %sizeof_sa, align 4, !dbg !3773
  br label %if.end73, !dbg !3774

if.end73:                                         ; preds = %if.then71, %land.lhs.true66, %if.then63
  br label %if.end74, !dbg !3775

if.end74:                                         ; preds = %if.end73, %if.end60
  %75 = load i32, i32* %done, align 4, !dbg !3776
  %cmp75 = icmp slt i32 %75, 1, !dbg !3778
  br i1 %cmp75, label %if.then77, label %if.end78, !dbg !3779

if.then77:                                        ; preds = %if.end74
  %76 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3780
  %77 = load i8*, i8** %dev, align 8, !dbg !3782
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %76, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.24, i32 0, i32 0), i8* %77), !dbg !3783
  store i32 45, i32* %retval, align 4, !dbg !3784
  br label %return, !dbg !3784

if.end78:                                         ; preds = %if.end74
  br label %if.end87, !dbg !3785

if.else79:                                        ; preds = %land.lhs.true6, %if.end
  %78 = load i32, i32* %af.addr, align 4, !dbg !3786
  %cmp80 = icmp eq i32 %78, 2, !dbg !3789
  br i1 %cmp80, label %if.then82, label %if.end86, !dbg !3790

if.then82:                                        ; preds = %if.else79
  %79 = load %struct.sockaddr_in*, %struct.sockaddr_in** %si4, align 8, !dbg !3791
  %sin_family83 = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %79, i32 0, i32 0, !dbg !3793
  store i16 2, i16* %sin_family83, align 4, !dbg !3794
  %80 = load i16, i16* %port, align 2, !dbg !3795
  %call84 = call zeroext i16 @htons(i16 zeroext %80) #1, !dbg !3796
  %81 = load %struct.sockaddr_in*, %struct.sockaddr_in** %si4, align 8, !dbg !3797
  %sin_port85 = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %81, i32 0, i32 1, !dbg !3798
  store i16 %call84, i16* %sin_port85, align 2, !dbg !3799
  store i32 16, i32* %sizeof_sa, align 4, !dbg !3800
  br label %if.end86, !dbg !3801

if.end86:                                         ; preds = %if.then82, %if.else79
  br label %if.end87

if.end87:                                         ; preds = %if.end86, %if.end78
  br label %for.cond, !dbg !3802

for.cond:                                         ; preds = %if.end114, %if.end87
  %82 = load i32, i32* %sockfd.addr, align 4, !dbg !3803
  %83 = load %struct.sockaddr*, %struct.sockaddr** %sock, align 8, !dbg !3808
  %84 = load i32, i32* %sizeof_sa, align 4, !dbg !3809
  %call88 = call i32 @bind(i32 %82, %struct.sockaddr* %83, i32 %84) #7, !dbg !3810
  %cmp89 = icmp sge i32 %call88, 0, !dbg !3811
  br i1 %cmp89, label %if.then91, label %if.end101, !dbg !3812

if.then91:                                        ; preds = %for.cond
  call void @llvm.dbg.declare(metadata %struct.Curl_sockaddr_storage* %add92, metadata !3813, metadata !1944), !dbg !3815
  call void @llvm.dbg.declare(metadata i32* %size, metadata !3816, metadata !1944), !dbg !3817
  store i32 128, i32* %size, align 4, !dbg !3817
  %85 = bitcast %struct.Curl_sockaddr_storage* %add92 to i8*, !dbg !3818
  call void @llvm.memset.p0i8.i64(i8* %85, i8 0, i64 128, i32 8, i1 false), !dbg !3818
  %86 = load i32, i32* %sockfd.addr, align 4, !dbg !3819
  %87 = bitcast %struct.Curl_sockaddr_storage* %add92 to %struct.sockaddr*, !dbg !3821
  %call93 = call i32 @getsockname(i32 %86, %struct.sockaddr* %87, i32* %size) #7, !dbg !3822
  %cmp94 = icmp slt i32 %call93, 0, !dbg !3823
  br i1 %cmp94, label %if.then96, label %if.end99, !dbg !3824

if.then96:                                        ; preds = %if.then91
  %call97 = call i32* @__errno_location() #1, !dbg !3825
  %88 = load i32, i32* %call97, align 4, !dbg !3825
  store i32 %88, i32* %error, align 4, !dbg !3827
  %89 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3828
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %89, i32 0, i32 17, !dbg !3829
  %os_errno = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 18, !dbg !3830
  store i32 %88, i32* %os_errno, align 4, !dbg !3831
  %90 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3832
  %91 = load i32, i32* %error, align 4, !dbg !3833
  %92 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3834
  %93 = load i32, i32* %error, align 4, !dbg !3835
  %call98 = call i8* @Curl_strerror(%struct.connectdata* %92, i32 %93), !dbg !3836
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %90, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.1, i32 0, i32 0), i32 %91, i8* %call98), !dbg !3837
  store i32 45, i32* %retval, align 4, !dbg !3838
  br label %return, !dbg !3838

if.end99:                                         ; preds = %if.then91
  %94 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3839
  %95 = load i16, i16* %port, align 2, !dbg !3840
  %conv100 = zext i16 %95 to i32, !dbg !3840
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %94, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.25, i32 0, i32 0), i32 %conv100), !dbg !3841
  %96 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3842
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %96, i32 0, i32 43, !dbg !3843
  %bound = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 25, !dbg !3844
  store i8 1, i8* %bound, align 1, !dbg !3845
  store i32 0, i32* %retval, align 4, !dbg !3846
  br label %return, !dbg !3846

if.end101:                                        ; preds = %for.cond
  %97 = load i32, i32* %portnum, align 4, !dbg !3847
  %dec = add nsw i32 %97, -1, !dbg !3847
  store i32 %dec, i32* %portnum, align 4, !dbg !3847
  %cmp102 = icmp sgt i32 %dec, 0, !dbg !3849
  br i1 %cmp102, label %if.then104, label %if.else113, !dbg !3850

if.then104:                                       ; preds = %if.end101
  %98 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3851
  %99 = load i16, i16* %port, align 2, !dbg !3853
  %conv105 = zext i16 %99 to i32, !dbg !3853
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %98, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.26, i32 0, i32 0), i32 %conv105), !dbg !3854
  %100 = load i16, i16* %port, align 2, !dbg !3855
  %inc = add i16 %100, 1, !dbg !3855
  store i16 %inc, i16* %port, align 2, !dbg !3855
  %101 = load %struct.sockaddr*, %struct.sockaddr** %sock, align 8, !dbg !3856
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %101, i32 0, i32 0, !dbg !3858
  %102 = load i16, i16* %sa_family, align 2, !dbg !3858
  %conv106 = zext i16 %102 to i32, !dbg !3856
  %cmp107 = icmp eq i32 %conv106, 2, !dbg !3859
  br i1 %cmp107, label %if.then109, label %if.end112, !dbg !3860

if.then109:                                       ; preds = %if.then104
  %103 = load i16, i16* %port, align 2, !dbg !3861
  %call110 = call zeroext i16 @ntohs(i16 zeroext %103) #1, !dbg !3862
  %104 = load %struct.sockaddr_in*, %struct.sockaddr_in** %si4, align 8, !dbg !3863
  %sin_port111 = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %104, i32 0, i32 1, !dbg !3864
  store i16 %call110, i16* %sin_port111, align 2, !dbg !3865
  br label %if.end112, !dbg !3863

if.end112:                                        ; preds = %if.then109, %if.then104
  br label %if.end114, !dbg !3866

if.else113:                                       ; preds = %if.end101
  br label %for.end, !dbg !3867

if.end114:                                        ; preds = %if.end112
  br label %for.cond, !dbg !3868

for.end:                                          ; preds = %if.else113
  %call115 = call i32* @__errno_location() #1, !dbg !3870
  %105 = load i32, i32* %call115, align 4, !dbg !3870
  store i32 %105, i32* %error, align 4, !dbg !3871
  %106 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3872
  %state116 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %106, i32 0, i32 17, !dbg !3873
  %os_errno117 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state116, i32 0, i32 18, !dbg !3874
  store i32 %105, i32* %os_errno117, align 4, !dbg !3875
  %107 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !3876
  %108 = load i32, i32* %error, align 4, !dbg !3877
  %109 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !3878
  %110 = load i32, i32* %error, align 4, !dbg !3879
  %call118 = call i8* @Curl_strerror(%struct.connectdata* %109, i32 %110), !dbg !3880
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %107, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.27, i32 0, i32 0), i32 %108, i8* %call118), !dbg !3881
  store i32 45, i32* %retval, align 4, !dbg !3882
  br label %return, !dbg !3882

return:                                           ; preds = %for.end, %if.end99, %if.then96, %if.then77, %sw.bb27, %if.then25, %if.then
  %111 = load i32, i32* %retval, align 4, !dbg !3883
  ret i32 %111, !dbg !3883
}

declare i32 @Curl_ipv6_scope(%struct.sockaddr*) #2

declare i32 @curlx_nonblock(i32, i32) #2

declare void @Curl_expire_latest(%struct.Curl_easy*, i64) #2

declare i32 @connect(i32, %struct.sockaddr*, i32) #2

declare i32 @curlx_sltosi(i64) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #6

; Function Attrs: nounwind readonly
declare i32 @strncmp(i8*, i8*, i64) #6

declare i32 @Curl_if2ip(i32, i32, i32, i8*, i8*, i32) #2

declare i32 @Curl_resolv(%struct.connectdata*, i8*, i32, %struct.Curl_dns_entry**) #2

declare void @Curl_resolv_unlock(%struct.Curl_easy*, %struct.Curl_dns_entry*) #2

; Function Attrs: nounwind
declare i32 @inet_pton(i32, i8*, i8*) #4

; Function Attrs: nounwind readnone
declare zeroext i16 @htons(i16 zeroext) #5

; Function Attrs: nounwind
declare i32 @bind(i32, %struct.sockaddr*, i32) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!1940, !1941}
!llvm.ident = !{!1942}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !1813, subprograms: !1843, globals: !1937)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/connect.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !14, !24, !120, !126, !134, !173, !192, !212, !227, !244, !252, !266, !299, !368, !472, !491, !498, !637, !653, !665, !763, !773, !835, !855, !861, !887, !902, !911, !919, !948, !1187, !1239, !1678, !1690, !1705, !1733, !1754}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 31, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http_chunks.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13}
!6 = !DIEnumerator(name: "CHUNK_HEX", value: 0)
!7 = !DIEnumerator(name: "CHUNK_LF", value: 1)
!8 = !DIEnumerator(name: "CHUNK_DATA", value: 2)
!9 = !DIEnumerator(name: "CHUNK_POSTLF", value: 3)
!10 = !DIEnumerator(name: "CHUNK_STOP", value: 4)
!11 = !DIEnumerator(name: "CHUNK_TRAILER", value: 5)
!12 = !DIEnumerator(name: "CHUNK_TRAILER_CR", value: 6)
!13 = !DIEnumerator(name: "CHUNK_TRAILER_POSTCR", value: 7)
!14 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 644, size: 32, align: 32, elements: !16)
!15 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!16 = !{!17, !18, !19, !20, !21, !22, !23}
!17 = !DIEnumerator(name: "CURLPROXY_HTTP", value: 0)
!18 = !DIEnumerator(name: "CURLPROXY_HTTP_1_0", value: 1)
!19 = !DIEnumerator(name: "CURLPROXY_HTTPS", value: 2)
!20 = !DIEnumerator(name: "CURLPROXY_SOCKS4", value: 4)
!21 = !DIEnumerator(name: "CURLPROXY_SOCKS5", value: 5)
!22 = !DIEnumerator(name: "CURLPROXY_SOCKS4A", value: 6)
!23 = !DIEnumerator(name: "CURLPROXY_SOCKS5_HOSTNAME", value: 7)
!24 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 434, size: 32, align: 32, elements: !25)
!25 = !{!26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119}
!26 = !DIEnumerator(name: "CURLE_OK", value: 0)
!27 = !DIEnumerator(name: "CURLE_UNSUPPORTED_PROTOCOL", value: 1)
!28 = !DIEnumerator(name: "CURLE_FAILED_INIT", value: 2)
!29 = !DIEnumerator(name: "CURLE_URL_MALFORMAT", value: 3)
!30 = !DIEnumerator(name: "CURLE_NOT_BUILT_IN", value: 4)
!31 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_PROXY", value: 5)
!32 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_HOST", value: 6)
!33 = !DIEnumerator(name: "CURLE_COULDNT_CONNECT", value: 7)
!34 = !DIEnumerator(name: "CURLE_WEIRD_SERVER_REPLY", value: 8)
!35 = !DIEnumerator(name: "CURLE_REMOTE_ACCESS_DENIED", value: 9)
!36 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_FAILED", value: 10)
!37 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASS_REPLY", value: 11)
!38 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_TIMEOUT", value: 12)
!39 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASV_REPLY", value: 13)
!40 = !DIEnumerator(name: "CURLE_FTP_WEIRD_227_FORMAT", value: 14)
!41 = !DIEnumerator(name: "CURLE_FTP_CANT_GET_HOST", value: 15)
!42 = !DIEnumerator(name: "CURLE_HTTP2", value: 16)
!43 = !DIEnumerator(name: "CURLE_FTP_COULDNT_SET_TYPE", value: 17)
!44 = !DIEnumerator(name: "CURLE_PARTIAL_FILE", value: 18)
!45 = !DIEnumerator(name: "CURLE_FTP_COULDNT_RETR_FILE", value: 19)
!46 = !DIEnumerator(name: "CURLE_OBSOLETE20", value: 20)
!47 = !DIEnumerator(name: "CURLE_QUOTE_ERROR", value: 21)
!48 = !DIEnumerator(name: "CURLE_HTTP_RETURNED_ERROR", value: 22)
!49 = !DIEnumerator(name: "CURLE_WRITE_ERROR", value: 23)
!50 = !DIEnumerator(name: "CURLE_OBSOLETE24", value: 24)
!51 = !DIEnumerator(name: "CURLE_UPLOAD_FAILED", value: 25)
!52 = !DIEnumerator(name: "CURLE_READ_ERROR", value: 26)
!53 = !DIEnumerator(name: "CURLE_OUT_OF_MEMORY", value: 27)
!54 = !DIEnumerator(name: "CURLE_OPERATION_TIMEDOUT", value: 28)
!55 = !DIEnumerator(name: "CURLE_OBSOLETE29", value: 29)
!56 = !DIEnumerator(name: "CURLE_FTP_PORT_FAILED", value: 30)
!57 = !DIEnumerator(name: "CURLE_FTP_COULDNT_USE_REST", value: 31)
!58 = !DIEnumerator(name: "CURLE_OBSOLETE32", value: 32)
!59 = !DIEnumerator(name: "CURLE_RANGE_ERROR", value: 33)
!60 = !DIEnumerator(name: "CURLE_HTTP_POST_ERROR", value: 34)
!61 = !DIEnumerator(name: "CURLE_SSL_CONNECT_ERROR", value: 35)
!62 = !DIEnumerator(name: "CURLE_BAD_DOWNLOAD_RESUME", value: 36)
!63 = !DIEnumerator(name: "CURLE_FILE_COULDNT_READ_FILE", value: 37)
!64 = !DIEnumerator(name: "CURLE_LDAP_CANNOT_BIND", value: 38)
!65 = !DIEnumerator(name: "CURLE_LDAP_SEARCH_FAILED", value: 39)
!66 = !DIEnumerator(name: "CURLE_OBSOLETE40", value: 40)
!67 = !DIEnumerator(name: "CURLE_FUNCTION_NOT_FOUND", value: 41)
!68 = !DIEnumerator(name: "CURLE_ABORTED_BY_CALLBACK", value: 42)
!69 = !DIEnumerator(name: "CURLE_BAD_FUNCTION_ARGUMENT", value: 43)
!70 = !DIEnumerator(name: "CURLE_OBSOLETE44", value: 44)
!71 = !DIEnumerator(name: "CURLE_INTERFACE_FAILED", value: 45)
!72 = !DIEnumerator(name: "CURLE_OBSOLETE46", value: 46)
!73 = !DIEnumerator(name: "CURLE_TOO_MANY_REDIRECTS", value: 47)
!74 = !DIEnumerator(name: "CURLE_UNKNOWN_OPTION", value: 48)
!75 = !DIEnumerator(name: "CURLE_TELNET_OPTION_SYNTAX", value: 49)
!76 = !DIEnumerator(name: "CURLE_OBSOLETE50", value: 50)
!77 = !DIEnumerator(name: "CURLE_PEER_FAILED_VERIFICATION", value: 51)
!78 = !DIEnumerator(name: "CURLE_GOT_NOTHING", value: 52)
!79 = !DIEnumerator(name: "CURLE_SSL_ENGINE_NOTFOUND", value: 53)
!80 = !DIEnumerator(name: "CURLE_SSL_ENGINE_SETFAILED", value: 54)
!81 = !DIEnumerator(name: "CURLE_SEND_ERROR", value: 55)
!82 = !DIEnumerator(name: "CURLE_RECV_ERROR", value: 56)
!83 = !DIEnumerator(name: "CURLE_OBSOLETE57", value: 57)
!84 = !DIEnumerator(name: "CURLE_SSL_CERTPROBLEM", value: 58)
!85 = !DIEnumerator(name: "CURLE_SSL_CIPHER", value: 59)
!86 = !DIEnumerator(name: "CURLE_SSL_CACERT", value: 60)
!87 = !DIEnumerator(name: "CURLE_BAD_CONTENT_ENCODING", value: 61)
!88 = !DIEnumerator(name: "CURLE_LDAP_INVALID_URL", value: 62)
!89 = !DIEnumerator(name: "CURLE_FILESIZE_EXCEEDED", value: 63)
!90 = !DIEnumerator(name: "CURLE_USE_SSL_FAILED", value: 64)
!91 = !DIEnumerator(name: "CURLE_SEND_FAIL_REWIND", value: 65)
!92 = !DIEnumerator(name: "CURLE_SSL_ENGINE_INITFAILED", value: 66)
!93 = !DIEnumerator(name: "CURLE_LOGIN_DENIED", value: 67)
!94 = !DIEnumerator(name: "CURLE_TFTP_NOTFOUND", value: 68)
!95 = !DIEnumerator(name: "CURLE_TFTP_PERM", value: 69)
!96 = !DIEnumerator(name: "CURLE_REMOTE_DISK_FULL", value: 70)
!97 = !DIEnumerator(name: "CURLE_TFTP_ILLEGAL", value: 71)
!98 = !DIEnumerator(name: "CURLE_TFTP_UNKNOWNID", value: 72)
!99 = !DIEnumerator(name: "CURLE_REMOTE_FILE_EXISTS", value: 73)
!100 = !DIEnumerator(name: "CURLE_TFTP_NOSUCHUSER", value: 74)
!101 = !DIEnumerator(name: "CURLE_CONV_FAILED", value: 75)
!102 = !DIEnumerator(name: "CURLE_CONV_REQD", value: 76)
!103 = !DIEnumerator(name: "CURLE_SSL_CACERT_BADFILE", value: 77)
!104 = !DIEnumerator(name: "CURLE_REMOTE_FILE_NOT_FOUND", value: 78)
!105 = !DIEnumerator(name: "CURLE_SSH", value: 79)
!106 = !DIEnumerator(name: "CURLE_SSL_SHUTDOWN_FAILED", value: 80)
!107 = !DIEnumerator(name: "CURLE_AGAIN", value: 81)
!108 = !DIEnumerator(name: "CURLE_SSL_CRL_BADFILE", value: 82)
!109 = !DIEnumerator(name: "CURLE_SSL_ISSUER_ERROR", value: 83)
!110 = !DIEnumerator(name: "CURLE_FTP_PRET_FAILED", value: 84)
!111 = !DIEnumerator(name: "CURLE_RTSP_CSEQ_ERROR", value: 85)
!112 = !DIEnumerator(name: "CURLE_RTSP_SESSION_ERROR", value: 86)
!113 = !DIEnumerator(name: "CURLE_FTP_BAD_FILE_LIST", value: 87)
!114 = !DIEnumerator(name: "CURLE_CHUNK_FAILED", value: 88)
!115 = !DIEnumerator(name: "CURLE_NO_CONNECTION_AVAILABLE", value: 89)
!116 = !DIEnumerator(name: "CURLE_SSL_PINNEDPUBKEYNOTMATCH", value: 90)
!117 = !DIEnumerator(name: "CURLE_SSL_INVALIDCERTSTATUS", value: 91)
!118 = !DIEnumerator(name: "CURLE_HTTP2_STREAM", value: 92)
!119 = !DIEnumerator(name: "CURL_LAST", value: 93)
!120 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 267, size: 32, align: 32, elements: !122)
!121 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/urldata.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!122 = !{!123, !124, !125}
!123 = !DIEnumerator(name: "ssl_connection_none", value: 0)
!124 = !DIEnumerator(name: "ssl_connection_negotiating", value: 1)
!125 = !DIEnumerator(name: "ssl_connection_complete", value: 2)
!126 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 258, size: 32, align: 32, elements: !127)
!127 = !{!128, !129, !130, !131, !132, !133}
!128 = !DIEnumerator(name: "ssl_connect_1", value: 0)
!129 = !DIEnumerator(name: "ssl_connect_2", value: 1)
!130 = !DIEnumerator(name: "ssl_connect_2_reading", value: 2)
!131 = !DIEnumerator(name: "ssl_connect_2_writing", value: 3)
!132 = !DIEnumerator(name: "ssl_connect_3", value: 4)
!133 = !DIEnumerator(name: "ssl_connect_done", value: 5)
!134 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !135, line: 42, size: 32, align: 32, elements: !136)
!135 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/ftp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!136 = !{!137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147, !148, !149, !150, !151, !152, !153, !154, !155, !156, !157, !158, !159, !160, !161, !162, !163, !164, !165, !166, !167, !168, !169, !170, !171, !172}
!137 = !DIEnumerator(name: "FTP_STOP", value: 0)
!138 = !DIEnumerator(name: "FTP_WAIT220", value: 1)
!139 = !DIEnumerator(name: "FTP_AUTH", value: 2)
!140 = !DIEnumerator(name: "FTP_USER", value: 3)
!141 = !DIEnumerator(name: "FTP_PASS", value: 4)
!142 = !DIEnumerator(name: "FTP_ACCT", value: 5)
!143 = !DIEnumerator(name: "FTP_PBSZ", value: 6)
!144 = !DIEnumerator(name: "FTP_PROT", value: 7)
!145 = !DIEnumerator(name: "FTP_CCC", value: 8)
!146 = !DIEnumerator(name: "FTP_PWD", value: 9)
!147 = !DIEnumerator(name: "FTP_SYST", value: 10)
!148 = !DIEnumerator(name: "FTP_NAMEFMT", value: 11)
!149 = !DIEnumerator(name: "FTP_QUOTE", value: 12)
!150 = !DIEnumerator(name: "FTP_RETR_PREQUOTE", value: 13)
!151 = !DIEnumerator(name: "FTP_STOR_PREQUOTE", value: 14)
!152 = !DIEnumerator(name: "FTP_POSTQUOTE", value: 15)
!153 = !DIEnumerator(name: "FTP_CWD", value: 16)
!154 = !DIEnumerator(name: "FTP_MKD", value: 17)
!155 = !DIEnumerator(name: "FTP_MDTM", value: 18)
!156 = !DIEnumerator(name: "FTP_TYPE", value: 19)
!157 = !DIEnumerator(name: "FTP_LIST_TYPE", value: 20)
!158 = !DIEnumerator(name: "FTP_RETR_TYPE", value: 21)
!159 = !DIEnumerator(name: "FTP_STOR_TYPE", value: 22)
!160 = !DIEnumerator(name: "FTP_SIZE", value: 23)
!161 = !DIEnumerator(name: "FTP_RETR_SIZE", value: 24)
!162 = !DIEnumerator(name: "FTP_STOR_SIZE", value: 25)
!163 = !DIEnumerator(name: "FTP_REST", value: 26)
!164 = !DIEnumerator(name: "FTP_RETR_REST", value: 27)
!165 = !DIEnumerator(name: "FTP_PORT", value: 28)
!166 = !DIEnumerator(name: "FTP_PRET", value: 29)
!167 = !DIEnumerator(name: "FTP_PASV", value: 30)
!168 = !DIEnumerator(name: "FTP_LIST", value: 31)
!169 = !DIEnumerator(name: "FTP_RETR", value: 32)
!170 = !DIEnumerator(name: "FTP_STOR", value: 33)
!171 = !DIEnumerator(name: "FTP_QUIT", value: 34)
!172 = !DIEnumerator(name: "FTP_LAST", value: 35)
!173 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !174, line: 31, size: 32, align: 32, elements: !175)
!174 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/imap.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!175 = !{!176, !177, !178, !179, !180, !181, !182, !183, !184, !185, !186, !187, !188, !189, !190, !191}
!176 = !DIEnumerator(name: "IMAP_STOP", value: 0)
!177 = !DIEnumerator(name: "IMAP_SERVERGREET", value: 1)
!178 = !DIEnumerator(name: "IMAP_CAPABILITY", value: 2)
!179 = !DIEnumerator(name: "IMAP_STARTTLS", value: 3)
!180 = !DIEnumerator(name: "IMAP_UPGRADETLS", value: 4)
!181 = !DIEnumerator(name: "IMAP_AUTHENTICATE", value: 5)
!182 = !DIEnumerator(name: "IMAP_LOGIN", value: 6)
!183 = !DIEnumerator(name: "IMAP_LIST", value: 7)
!184 = !DIEnumerator(name: "IMAP_SELECT", value: 8)
!185 = !DIEnumerator(name: "IMAP_FETCH", value: 9)
!186 = !DIEnumerator(name: "IMAP_FETCH_FINAL", value: 10)
!187 = !DIEnumerator(name: "IMAP_APPEND", value: 11)
!188 = !DIEnumerator(name: "IMAP_APPEND_FINAL", value: 12)
!189 = !DIEnumerator(name: "IMAP_SEARCH", value: 13)
!190 = !DIEnumerator(name: "IMAP_LOGOUT", value: 14)
!191 = !DIEnumerator(name: "IMAP_LAST", value: 15)
!192 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !193, line: 58, size: 32, align: 32, elements: !194)
!193 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_sasl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!194 = !{!195, !196, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211}
!195 = !DIEnumerator(name: "SASL_STOP", value: 0)
!196 = !DIEnumerator(name: "SASL_PLAIN", value: 1)
!197 = !DIEnumerator(name: "SASL_LOGIN", value: 2)
!198 = !DIEnumerator(name: "SASL_LOGIN_PASSWD", value: 3)
!199 = !DIEnumerator(name: "SASL_EXTERNAL", value: 4)
!200 = !DIEnumerator(name: "SASL_CRAMMD5", value: 5)
!201 = !DIEnumerator(name: "SASL_DIGESTMD5", value: 6)
!202 = !DIEnumerator(name: "SASL_DIGESTMD5_RESP", value: 7)
!203 = !DIEnumerator(name: "SASL_NTLM", value: 8)
!204 = !DIEnumerator(name: "SASL_NTLM_TYPE2MSG", value: 9)
!205 = !DIEnumerator(name: "SASL_GSSAPI", value: 10)
!206 = !DIEnumerator(name: "SASL_GSSAPI_TOKEN", value: 11)
!207 = !DIEnumerator(name: "SASL_GSSAPI_NO_DATA", value: 12)
!208 = !DIEnumerator(name: "SASL_OAUTH2", value: 13)
!209 = !DIEnumerator(name: "SASL_OAUTH2_RESP", value: 14)
!210 = !DIEnumerator(name: "SASL_CANCEL", value: 15)
!211 = !DIEnumerator(name: "SASL_FINAL", value: 16)
!212 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !213, line: 31, size: 32, align: 32, elements: !214)
!213 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pop3.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!214 = !{!215, !216, !217, !218, !219, !220, !221, !222, !223, !224, !225, !226}
!215 = !DIEnumerator(name: "POP3_STOP", value: 0)
!216 = !DIEnumerator(name: "POP3_SERVERGREET", value: 1)
!217 = !DIEnumerator(name: "POP3_CAPA", value: 2)
!218 = !DIEnumerator(name: "POP3_STARTTLS", value: 3)
!219 = !DIEnumerator(name: "POP3_UPGRADETLS", value: 4)
!220 = !DIEnumerator(name: "POP3_AUTH", value: 5)
!221 = !DIEnumerator(name: "POP3_APOP", value: 6)
!222 = !DIEnumerator(name: "POP3_USER", value: 7)
!223 = !DIEnumerator(name: "POP3_PASS", value: 8)
!224 = !DIEnumerator(name: "POP3_COMMAND", value: 9)
!225 = !DIEnumerator(name: "POP3_QUIT", value: 10)
!226 = !DIEnumerator(name: "POP3_LAST", value: 11)
!227 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !228, line: 31, size: 32, align: 32, elements: !229)
!228 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/smtp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!229 = !{!230, !231, !232, !233, !234, !235, !236, !237, !238, !239, !240, !241, !242, !243}
!230 = !DIEnumerator(name: "SMTP_STOP", value: 0)
!231 = !DIEnumerator(name: "SMTP_SERVERGREET", value: 1)
!232 = !DIEnumerator(name: "SMTP_EHLO", value: 2)
!233 = !DIEnumerator(name: "SMTP_HELO", value: 3)
!234 = !DIEnumerator(name: "SMTP_STARTTLS", value: 4)
!235 = !DIEnumerator(name: "SMTP_UPGRADETLS", value: 5)
!236 = !DIEnumerator(name: "SMTP_AUTH", value: 6)
!237 = !DIEnumerator(name: "SMTP_COMMAND", value: 7)
!238 = !DIEnumerator(name: "SMTP_MAIL", value: 8)
!239 = !DIEnumerator(name: "SMTP_RCPT", value: 9)
!240 = !DIEnumerator(name: "SMTP_DATA", value: 10)
!241 = !DIEnumerator(name: "SMTP_POSTDATA", value: 11)
!242 = !DIEnumerator(name: "SMTP_QUIT", value: 12)
!243 = !DIEnumerator(name: "SMTP_LAST", value: 13)
!244 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "smb_conn_state", file: !245, line: 25, size: 32, align: 32, elements: !246)
!245 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/smb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!246 = !{!247, !248, !249, !250, !251}
!247 = !DIEnumerator(name: "SMB_NOT_CONNECTED", value: 0)
!248 = !DIEnumerator(name: "SMB_CONNECTING", value: 1)
!249 = !DIEnumerator(name: "SMB_NEGOTIATE", value: 2)
!250 = !DIEnumerator(name: "SMB_SETUP", value: 3)
!251 = !DIEnumerator(name: "SMB_CONNECTED", value: 4)
!252 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !253, file: !121, line: 1133, size: 32, align: 32, elements: !1674)
!253 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectdata", file: !121, line: 895, size: 13440, align: 64, elements: !254)
!254 = !{!255, !1255, !1267, !1268, !1269, !1270, !1271, !1297, !1298, !1302, !1303, !1304, !1305, !1312, !1313, !1314, !1322, !1323, !1324, !1325, !1326, !1327, !1328, !1329, !1330, !1331, !1332, !1333, !1334, !1335, !1336, !1337, !1338, !1339, !1341, !1342, !1344, !1351, !1357, !1366, !1367, !1368, !1369, !1370, !1406, !1407, !1408, !1409, !1463, !1464, !1465, !1466, !1467, !1480, !1481, !1482, !1483, !1484, !1485, !1486, !1487, !1488, !1489, !1493, !1494, !1495, !1496, !1659, !1660, !1661, !1662, !1663, !1664, !1666, !1673}
!255 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !253, file: !121, line: 899, baseType: !256, size: 64, align: 64)
!256 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !257, size: 64, align: 64)
!257 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_easy", file: !121, line: 1801, size: 160192, align: 64, elements: !258)
!258 = !{!259, !260, !261, !263, !288, !290, !313, !319, !320, !374, !450, !451, !454, !528, !1005, !1014, !1041, !1077, !1181, !1204, !1234, !1254}
!259 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !257, file: !121, line: 1803, baseType: !256, size: 64, align: 64)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !257, file: !121, line: 1804, baseType: !256, size: 64, align: 64, offset: 64)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "easy_conn", scope: !257, file: !121, line: 1806, baseType: !262, size: 64, align: 64, offset: 128)
!262 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !253, size: 64, align: 64)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "mstate", scope: !257, file: !121, line: 1808, baseType: !264, size: 32, align: 32, offset: 192)
!264 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMstate", file: !265, line: 59, baseType: !266)
!265 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/multihandle.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!266 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !265, line: 35, size: 32, align: 32, elements: !267)
!267 = !{!268, !269, !270, !271, !272, !273, !274, !275, !276, !277, !278, !279, !280, !281, !282, !283, !284, !285, !286, !287}
!268 = !DIEnumerator(name: "CURLM_STATE_INIT", value: 0)
!269 = !DIEnumerator(name: "CURLM_STATE_CONNECT_PEND", value: 1)
!270 = !DIEnumerator(name: "CURLM_STATE_CONNECT", value: 2)
!271 = !DIEnumerator(name: "CURLM_STATE_WAITRESOLVE", value: 3)
!272 = !DIEnumerator(name: "CURLM_STATE_WAITCONNECT", value: 4)
!273 = !DIEnumerator(name: "CURLM_STATE_WAITPROXYCONNECT", value: 5)
!274 = !DIEnumerator(name: "CURLM_STATE_SENDPROTOCONNECT", value: 6)
!275 = !DIEnumerator(name: "CURLM_STATE_PROTOCONNECT", value: 7)
!276 = !DIEnumerator(name: "CURLM_STATE_WAITDO", value: 8)
!277 = !DIEnumerator(name: "CURLM_STATE_DO", value: 9)
!278 = !DIEnumerator(name: "CURLM_STATE_DOING", value: 10)
!279 = !DIEnumerator(name: "CURLM_STATE_DO_MORE", value: 11)
!280 = !DIEnumerator(name: "CURLM_STATE_DO_DONE", value: 12)
!281 = !DIEnumerator(name: "CURLM_STATE_WAITPERFORM", value: 13)
!282 = !DIEnumerator(name: "CURLM_STATE_PERFORM", value: 14)
!283 = !DIEnumerator(name: "CURLM_STATE_TOOFAST", value: 15)
!284 = !DIEnumerator(name: "CURLM_STATE_DONE", value: 16)
!285 = !DIEnumerator(name: "CURLM_STATE_COMPLETED", value: 17)
!286 = !DIEnumerator(name: "CURLM_STATE_MSGSENT", value: 18)
!287 = !DIEnumerator(name: "CURLM_STATE_LAST", value: 19)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !257, file: !121, line: 1809, baseType: !289, size: 32, align: 32, offset: 224)
!289 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLcode", file: !15, line: 561, baseType: !24)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !257, file: !121, line: 1811, baseType: !291, size: 192, align: 64, offset: 256)
!291 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_message", file: !265, line: 27, size: 192, align: 64, elements: !292)
!292 = !{!293}
!293 = !DIDerivedType(tag: DW_TAG_member, name: "extmsg", scope: !291, file: !265, line: 29, baseType: !294, size: 192, align: 64)
!294 = !DICompositeType(tag: DW_TAG_structure_type, name: "CURLMsg", file: !295, line: 93, size: 192, align: 64, elements: !296)
!295 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/multi.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!296 = !{!297, !304, !307}
!297 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !294, file: !295, line: 94, baseType: !298, size: 32, align: 32)
!298 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMSG", file: !295, line: 91, baseType: !299)
!299 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !295, line: 86, size: 32, align: 32, elements: !300)
!300 = !{!301, !302, !303}
!301 = !DIEnumerator(name: "CURLMSG_NONE", value: 0)
!302 = !DIEnumerator(name: "CURLMSG_DONE", value: 1)
!303 = !DIEnumerator(name: "CURLMSG_LAST", value: 2)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "easy_handle", scope: !294, file: !295, line: 95, baseType: !305, size: 64, align: 64, offset: 64)
!305 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !306, size: 64, align: 64)
!306 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURL", file: !15, line: 100, baseType: !257)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !294, file: !295, line: 99, baseType: !308, size: 64, align: 64, offset: 128)
!308 = !DICompositeType(tag: DW_TAG_union_type, scope: !294, file: !295, line: 96, size: 64, align: 64, elements: !309)
!309 = !{!310, !312}
!310 = !DIDerivedType(tag: DW_TAG_member, name: "whatever", scope: !308, file: !295, line: 97, baseType: !311, size: 64, align: 64)
!311 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !308, file: !295, line: 98, baseType: !289, size: 32, align: 32)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "sockets", scope: !257, file: !121, line: 1817, baseType: !314, size: 160, align: 32, offset: 448)
!314 = !DICompositeType(tag: DW_TAG_array_type, baseType: !315, size: 160, align: 32, elements: !317)
!315 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_t", file: !15, line: 131, baseType: !316)
!316 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!317 = !{!318}
!318 = !DISubrange(count: 5)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "numsocks", scope: !257, file: !121, line: 1818, baseType: !316, size: 32, align: 32, offset: 608)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "dns", scope: !257, file: !121, line: 1820, baseType: !321, size: 128, align: 64, offset: 640)
!321 = !DICompositeType(tag: DW_TAG_structure_type, name: "Names", file: !121, line: 1781, size: 128, align: 64, elements: !322)
!322 = !{!323, !367}
!323 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !321, file: !121, line: 1782, baseType: !324, size: 64, align: 64)
!324 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !325, size: 64, align: 64)
!325 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_hash", file: !326, line: 46, size: 384, align: 64, elements: !327)
!326 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hash.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!327 = !{!328, !350, !355, !360, !365, !366}
!328 = !DIDerivedType(tag: DW_TAG_member, name: "table", scope: !325, file: !326, line: 47, baseType: !329, size: 64, align: 64)
!329 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !330, size: 64, align: 64)
!330 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist", file: !331, line: 37, size: 256, align: 64, elements: !332)
!331 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/llist.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!332 = !{!333, !340, !341, !346}
!333 = !DIDerivedType(tag: DW_TAG_member, name: "head", scope: !330, file: !331, line: 38, baseType: !334, size: 64, align: 64)
!334 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !335, size: 64, align: 64)
!335 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_llist_element", file: !331, line: 30, size: 192, align: 64, elements: !336)
!336 = !{!337, !338, !339}
!337 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !335, file: !331, line: 31, baseType: !311, size: 64, align: 64)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "prev", scope: !335, file: !331, line: 33, baseType: !334, size: 64, align: 64, offset: 64)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !335, file: !331, line: 34, baseType: !334, size: 64, align: 64, offset: 128)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "tail", scope: !330, file: !331, line: 39, baseType: !334, size: 64, align: 64, offset: 64)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !330, file: !331, line: 41, baseType: !342, size: 64, align: 64, offset: 128)
!342 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_llist_dtor", file: !331, line: 28, baseType: !343)
!343 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !344, size: 64, align: 64)
!344 = !DISubroutineType(types: !345)
!345 = !{null, !311, !311}
!346 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !330, file: !331, line: 43, baseType: !347, size: 64, align: 64, offset: 192)
!347 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !348, line: 62, baseType: !349)
!348 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!349 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "hash_func", scope: !325, file: !326, line: 50, baseType: !351, size: 64, align: 64, offset: 64)
!351 = !DIDerivedType(tag: DW_TAG_typedef, name: "hash_function", file: !326, line: 32, baseType: !352)
!352 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !353, size: 64, align: 64)
!353 = !DISubroutineType(types: !354)
!354 = !{!347, !311, !347, !347}
!355 = !DIDerivedType(tag: DW_TAG_member, name: "comp_func", scope: !325, file: !326, line: 53, baseType: !356, size: 64, align: 64, offset: 128)
!356 = !DIDerivedType(tag: DW_TAG_typedef, name: "comp_function", file: !326, line: 39, baseType: !357)
!357 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !358, size: 64, align: 64)
!358 = !DISubroutineType(types: !359)
!359 = !{!347, !311, !347, !311, !347}
!360 = !DIDerivedType(tag: DW_TAG_member, name: "dtor", scope: !325, file: !326, line: 54, baseType: !361, size: 64, align: 64, offset: 192)
!361 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_hash_dtor", file: !326, line: 44, baseType: !362)
!362 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !363, size: 64, align: 64)
!363 = !DISubroutineType(types: !364)
!364 = !{null, !311}
!365 = !DIDerivedType(tag: DW_TAG_member, name: "slots", scope: !325, file: !326, line: 55, baseType: !316, size: 32, align: 32, offset: 256)
!366 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !325, file: !326, line: 56, baseType: !347, size: 64, align: 64, offset: 320)
!367 = !DIDerivedType(tag: DW_TAG_member, name: "hostcachetype", scope: !321, file: !121, line: 1788, baseType: !368, size: 32, align: 32, offset: 64)
!368 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !321, file: !121, line: 1783, size: 32, align: 32, elements: !369)
!369 = !{!370, !371, !372, !373}
!370 = !DIEnumerator(name: "HCACHE_NONE", value: 0)
!371 = !DIEnumerator(name: "HCACHE_GLOBAL", value: 1)
!372 = !DIEnumerator(name: "HCACHE_MULTI", value: 2)
!373 = !DIEnumerator(name: "HCACHE_SHARED", value: 3)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "multi", scope: !257, file: !121, line: 1821, baseType: !375, size: 64, align: 64, offset: 768)
!375 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !376, size: 64, align: 64)
!376 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_multi", file: !265, line: 70, size: 3840, align: 64, elements: !377)
!377 = !{!378, !380, !381, !382, !383, !384, !385, !386, !391, !392, !399, !400, !401, !420, !421, !422, !424, !432, !433, !434, !435, !436, !437, !438, !439, !440, !441, !448, !449}
!378 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !376, file: !265, line: 73, baseType: !379, size: 64, align: 64)
!379 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "easyp", scope: !376, file: !265, line: 76, baseType: !256, size: 64, align: 64, offset: 64)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "easylp", scope: !376, file: !265, line: 77, baseType: !256, size: 64, align: 64, offset: 128)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "num_easy", scope: !376, file: !265, line: 79, baseType: !316, size: 32, align: 32, offset: 192)
!383 = !DIDerivedType(tag: DW_TAG_member, name: "num_alive", scope: !376, file: !265, line: 80, baseType: !316, size: 32, align: 32, offset: 224)
!384 = !DIDerivedType(tag: DW_TAG_member, name: "msglist", scope: !376, file: !265, line: 83, baseType: !330, size: 256, align: 64, offset: 256)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !376, file: !265, line: 85, baseType: !330, size: 256, align: 64, offset: 512)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "socket_cb", scope: !376, file: !265, line: 89, baseType: !387, size: 64, align: 64, offset: 768)
!387 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_callback", file: !295, line: 268, baseType: !388)
!388 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !389, size: 64, align: 64)
!389 = !DISubroutineType(types: !390)
!390 = !{!316, !305, !315, !316, !311, !311}
!391 = !DIDerivedType(tag: DW_TAG_member, name: "socket_userp", scope: !376, file: !265, line: 90, baseType: !311, size: 64, align: 64, offset: 832)
!392 = !DIDerivedType(tag: DW_TAG_member, name: "push_cb", scope: !376, file: !265, line: 93, baseType: !393, size: 64, align: 64, offset: 896)
!393 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_push_callback", file: !295, line: 429, baseType: !394)
!394 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !395, size: 64, align: 64)
!395 = !DISubroutineType(types: !396)
!396 = !{!316, !305, !305, !347, !397, !311}
!397 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !398, size: 64, align: 64)
!398 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_pushheaders", file: !295, line: 422, flags: DIFlagFwdDecl)
!399 = !DIDerivedType(tag: DW_TAG_member, name: "push_userp", scope: !376, file: !265, line: 94, baseType: !311, size: 64, align: 64, offset: 960)
!400 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !376, file: !265, line: 97, baseType: !325, size: 384, align: 64, offset: 1024)
!401 = !DIDerivedType(tag: DW_TAG_member, name: "timetree", scope: !376, file: !265, line: 101, baseType: !402, size: 64, align: 64, offset: 1408)
!402 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !403, size: 64, align: 64)
!403 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_tree", file: !404, line: 26, size: 448, align: 64, elements: !405)
!404 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/splay.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!405 = !{!406, !407, !408, !409, !410, !419}
!406 = !DIDerivedType(tag: DW_TAG_member, name: "smaller", scope: !403, file: !404, line: 27, baseType: !402, size: 64, align: 64)
!407 = !DIDerivedType(tag: DW_TAG_member, name: "larger", scope: !403, file: !404, line: 28, baseType: !402, size: 64, align: 64, offset: 64)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "samen", scope: !403, file: !404, line: 29, baseType: !402, size: 64, align: 64, offset: 128)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "samep", scope: !403, file: !404, line: 30, baseType: !402, size: 64, align: 64, offset: 192)
!410 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !403, file: !404, line: 31, baseType: !411, size: 128, align: 64, offset: 256)
!411 = !DICompositeType(tag: DW_TAG_structure_type, name: "timeval", file: !412, line: 30, size: 128, align: 64, elements: !413)
!412 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!413 = !{!414, !417}
!414 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !411, file: !412, line: 32, baseType: !415, size: 64, align: 64)
!415 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !416, line: 139, baseType: !379)
!416 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!417 = !DIDerivedType(tag: DW_TAG_member, name: "tv_usec", scope: !411, file: !412, line: 33, baseType: !418, size: 64, align: 64, offset: 64)
!418 = !DIDerivedType(tag: DW_TAG_typedef, name: "__suseconds_t", file: !416, line: 141, baseType: !379)
!419 = !DIDerivedType(tag: DW_TAG_member, name: "payload", scope: !403, file: !404, line: 32, baseType: !311, size: 64, align: 64, offset: 384)
!420 = !DIDerivedType(tag: DW_TAG_member, name: "sockhash", scope: !376, file: !265, line: 106, baseType: !325, size: 384, align: 64, offset: 1472)
!421 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining", scope: !376, file: !265, line: 109, baseType: !379, size: 64, align: 64, offset: 1856)
!422 = !DIDerivedType(tag: DW_TAG_member, name: "recheckstate", scope: !376, file: !265, line: 111, baseType: !423, size: 8, align: 8, offset: 1920)
!423 = !DIBasicType(name: "_Bool", size: 8, align: 8, encoding: DW_ATE_boolean)
!424 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !376, file: !265, line: 114, baseType: !425, size: 640, align: 64, offset: 1984)
!425 = !DICompositeType(tag: DW_TAG_structure_type, name: "conncache", file: !426, line: 26, size: 640, align: 64, elements: !427)
!426 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/conncache.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!427 = !{!428, !429, !430, !431}
!428 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !425, file: !426, line: 27, baseType: !325, size: 384, align: 64)
!429 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !425, file: !426, line: 28, baseType: !347, size: 64, align: 64, offset: 384)
!430 = !DIDerivedType(tag: DW_TAG_member, name: "next_connection_id", scope: !425, file: !426, line: 29, baseType: !379, size: 64, align: 64, offset: 448)
!431 = !DIDerivedType(tag: DW_TAG_member, name: "last_cleanup", scope: !425, file: !426, line: 30, baseType: !411, size: 128, align: 64, offset: 512)
!432 = !DIDerivedType(tag: DW_TAG_member, name: "closure_handle", scope: !376, file: !265, line: 118, baseType: !256, size: 64, align: 64, offset: 2624)
!433 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !376, file: !265, line: 120, baseType: !379, size: 64, align: 64, offset: 2688)
!434 = !DIDerivedType(tag: DW_TAG_member, name: "max_host_connections", scope: !376, file: !265, line: 123, baseType: !379, size: 64, align: 64, offset: 2752)
!435 = !DIDerivedType(tag: DW_TAG_member, name: "max_total_connections", scope: !376, file: !265, line: 126, baseType: !379, size: 64, align: 64, offset: 2816)
!436 = !DIDerivedType(tag: DW_TAG_member, name: "max_pipeline_length", scope: !376, file: !265, line: 129, baseType: !379, size: 64, align: 64, offset: 2880)
!437 = !DIDerivedType(tag: DW_TAG_member, name: "content_length_penalty_size", scope: !376, file: !265, line: 132, baseType: !379, size: 64, align: 64, offset: 2944)
!438 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_length_penalty_size", scope: !376, file: !265, line: 137, baseType: !379, size: 64, align: 64, offset: 3008)
!439 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining_site_bl", scope: !376, file: !265, line: 141, baseType: !330, size: 256, align: 64, offset: 3072)
!440 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining_server_bl", scope: !376, file: !265, line: 144, baseType: !330, size: 256, align: 64, offset: 3328)
!441 = !DIDerivedType(tag: DW_TAG_member, name: "timer_cb", scope: !376, file: !265, line: 148, baseType: !442, size: 64, align: 64, offset: 3584)
!442 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_multi_timer_callback", file: !295, line: 285, baseType: !443)
!443 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !444, size: 64, align: 64)
!444 = !DISubroutineType(types: !445)
!445 = !{!316, !446, !379, !311}
!446 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !447, size: 64, align: 64)
!447 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLM", file: !295, line: 56, baseType: !376)
!448 = !DIDerivedType(tag: DW_TAG_member, name: "timer_userp", scope: !376, file: !265, line: 149, baseType: !311, size: 64, align: 64, offset: 3648)
!449 = !DIDerivedType(tag: DW_TAG_member, name: "timer_lastcall", scope: !376, file: !265, line: 150, baseType: !411, size: 128, align: 64, offset: 3712)
!450 = !DIDerivedType(tag: DW_TAG_member, name: "multi_easy", scope: !257, file: !121, line: 1824, baseType: !375, size: 64, align: 64, offset: 832)
!451 = !DIDerivedType(tag: DW_TAG_member, name: "share", scope: !257, file: !121, line: 1827, baseType: !452, size: 64, align: 64, offset: 896)
!452 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !453, size: 64, align: 64)
!453 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_share", file: !15, line: 101, flags: DIFlagFwdDecl)
!454 = !DIDerivedType(tag: DW_TAG_member, name: "req", scope: !257, file: !121, line: 1828, baseType: !455, size: 2496, align: 64, offset: 960)
!455 = !DICompositeType(tag: DW_TAG_structure_type, name: "SingleRequest", file: !121, line: 658, size: 2496, align: 64, elements: !456)
!456 = !{!457, !460, !462, !463, !464, !465, !466, !467, !468, !469, !470, !471, !477, !478, !481, !482, !483, !484, !485, !486, !487, !488, !489, !490, !497, !504, !505, !508, !509, !510, !511, !512, !513, !514, !515, !516, !517, !518, !522, !523, !524, !525, !526, !527}
!457 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !455, file: !121, line: 659, baseType: !458, size: 64, align: 64)
!458 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_off_t", file: !459, line: 216, baseType: !379)
!459 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curlbuild.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!460 = !DIDerivedType(tag: DW_TAG_member, name: "bytecountp", scope: !455, file: !121, line: 660, baseType: !461, size: 64, align: 64, offset: 64)
!461 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !458, size: 64, align: 64)
!462 = !DIDerivedType(tag: DW_TAG_member, name: "maxdownload", scope: !455, file: !121, line: 662, baseType: !458, size: 64, align: 64, offset: 128)
!463 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecountp", scope: !455, file: !121, line: 664, baseType: !461, size: 64, align: 64, offset: 192)
!464 = !DIDerivedType(tag: DW_TAG_member, name: "bytecount", scope: !455, file: !121, line: 666, baseType: !458, size: 64, align: 64, offset: 256)
!465 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecount", scope: !455, file: !121, line: 667, baseType: !458, size: 64, align: 64, offset: 320)
!466 = !DIDerivedType(tag: DW_TAG_member, name: "headerbytecount", scope: !455, file: !121, line: 669, baseType: !379, size: 64, align: 64, offset: 384)
!467 = !DIDerivedType(tag: DW_TAG_member, name: "deductheadercount", scope: !455, file: !121, line: 670, baseType: !379, size: 64, align: 64, offset: 448)
!468 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !455, file: !121, line: 676, baseType: !411, size: 128, align: 64, offset: 512)
!469 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !455, file: !121, line: 677, baseType: !411, size: 128, align: 64, offset: 640)
!470 = !DIDerivedType(tag: DW_TAG_member, name: "header", scope: !455, file: !121, line: 678, baseType: !423, size: 8, align: 8, offset: 768)
!471 = !DIDerivedType(tag: DW_TAG_member, name: "badheader", scope: !455, file: !121, line: 684, baseType: !472, size: 32, align: 32, offset: 800)
!472 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !455, file: !121, line: 679, size: 32, align: 32, elements: !473)
!473 = !{!474, !475, !476}
!474 = !DIEnumerator(name: "HEADER_NORMAL", value: 0)
!475 = !DIEnumerator(name: "HEADER_PARTHEADER", value: 1)
!476 = !DIEnumerator(name: "HEADER_ALLBAD", value: 2)
!477 = !DIDerivedType(tag: DW_TAG_member, name: "headerline", scope: !455, file: !121, line: 686, baseType: !316, size: 32, align: 32, offset: 832)
!478 = !DIDerivedType(tag: DW_TAG_member, name: "hbufp", scope: !455, file: !121, line: 688, baseType: !479, size: 64, align: 64, offset: 896)
!479 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !480, size: 64, align: 64)
!480 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!481 = !DIDerivedType(tag: DW_TAG_member, name: "hbuflen", scope: !455, file: !121, line: 689, baseType: !347, size: 64, align: 64, offset: 960)
!482 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !455, file: !121, line: 690, baseType: !479, size: 64, align: 64, offset: 1024)
!483 = !DIDerivedType(tag: DW_TAG_member, name: "str_start", scope: !455, file: !121, line: 691, baseType: !479, size: 64, align: 64, offset: 1088)
!484 = !DIDerivedType(tag: DW_TAG_member, name: "end_ptr", scope: !455, file: !121, line: 692, baseType: !479, size: 64, align: 64, offset: 1152)
!485 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !455, file: !121, line: 693, baseType: !479, size: 64, align: 64, offset: 1216)
!486 = !DIDerivedType(tag: DW_TAG_member, name: "content_range", scope: !455, file: !121, line: 694, baseType: !423, size: 8, align: 8, offset: 1280)
!487 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !455, file: !121, line: 695, baseType: !458, size: 64, align: 64, offset: 1344)
!488 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !455, file: !121, line: 697, baseType: !316, size: 32, align: 32, offset: 1408)
!489 = !DIDerivedType(tag: DW_TAG_member, name: "start100", scope: !455, file: !121, line: 699, baseType: !411, size: 128, align: 64, offset: 1472)
!490 = !DIDerivedType(tag: DW_TAG_member, name: "exp100", scope: !455, file: !121, line: 700, baseType: !491, size: 32, align: 32, offset: 1600)
!491 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "expect100", file: !121, line: 636, size: 32, align: 32, elements: !492)
!492 = !{!493, !494, !495, !496}
!493 = !DIEnumerator(name: "EXP100_SEND_DATA", value: 0)
!494 = !DIEnumerator(name: "EXP100_AWAITING_CONTINUE", value: 1)
!495 = !DIEnumerator(name: "EXP100_SENDING_REQUEST", value: 2)
!496 = !DIEnumerator(name: "EXP100_FAILED", value: 3)
!497 = !DIDerivedType(tag: DW_TAG_member, name: "upgr101", scope: !455, file: !121, line: 701, baseType: !498, size: 32, align: 32, offset: 1632)
!498 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "upgrade101", file: !121, line: 644, size: 32, align: 32, elements: !499)
!499 = !{!500, !501, !502, !503}
!500 = !DIEnumerator(name: "UPGR101_INIT", value: 0)
!501 = !DIEnumerator(name: "UPGR101_REQUESTED", value: 1)
!502 = !DIEnumerator(name: "UPGR101_RECEIVED", value: 2)
!503 = !DIEnumerator(name: "UPGR101_WORKING", value: 3)
!504 = !DIDerivedType(tag: DW_TAG_member, name: "auto_decoding", scope: !455, file: !121, line: 703, baseType: !316, size: 32, align: 32, offset: 1664)
!505 = !DIDerivedType(tag: DW_TAG_member, name: "timeofdoc", scope: !455, file: !121, line: 715, baseType: !506, size: 64, align: 64, offset: 1728)
!506 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !507, line: 75, baseType: !415)
!507 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!508 = !DIDerivedType(tag: DW_TAG_member, name: "bodywrites", scope: !455, file: !121, line: 716, baseType: !379, size: 64, align: 64, offset: 1792)
!509 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !455, file: !121, line: 718, baseType: !479, size: 64, align: 64, offset: 1856)
!510 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuf", scope: !455, file: !121, line: 719, baseType: !479, size: 64, align: 64, offset: 1920)
!511 = !DIDerivedType(tag: DW_TAG_member, name: "maxfd", scope: !455, file: !121, line: 720, baseType: !315, size: 32, align: 32, offset: 1984)
!512 = !DIDerivedType(tag: DW_TAG_member, name: "keepon", scope: !455, file: !121, line: 722, baseType: !316, size: 32, align: 32, offset: 2016)
!513 = !DIDerivedType(tag: DW_TAG_member, name: "upload_done", scope: !455, file: !121, line: 724, baseType: !423, size: 8, align: 8, offset: 2048)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "ignorebody", scope: !455, file: !121, line: 727, baseType: !423, size: 8, align: 8, offset: 2056)
!515 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !455, file: !121, line: 728, baseType: !423, size: 8, align: 8, offset: 2064)
!516 = !DIDerivedType(tag: DW_TAG_member, name: "location", scope: !455, file: !121, line: 731, baseType: !479, size: 64, align: 64, offset: 2112)
!517 = !DIDerivedType(tag: DW_TAG_member, name: "newurl", scope: !455, file: !121, line: 733, baseType: !479, size: 64, align: 64, offset: 2176)
!518 = !DIDerivedType(tag: DW_TAG_member, name: "upload_present", scope: !455, file: !121, line: 738, baseType: !519, size: 64, align: 64, offset: 2240)
!519 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !520, line: 109, baseType: !521)
!520 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!521 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !416, line: 172, baseType: !379)
!522 = !DIDerivedType(tag: DW_TAG_member, name: "upload_fromhere", scope: !455, file: !121, line: 744, baseType: !479, size: 64, align: 64, offset: 2304)
!523 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !455, file: !121, line: 746, baseType: !423, size: 8, align: 8, offset: 2368)
!524 = !DIDerivedType(tag: DW_TAG_member, name: "upload_chunky", scope: !455, file: !121, line: 747, baseType: !423, size: 8, align: 8, offset: 2376)
!525 = !DIDerivedType(tag: DW_TAG_member, name: "getheader", scope: !455, file: !121, line: 749, baseType: !423, size: 8, align: 8, offset: 2384)
!526 = !DIDerivedType(tag: DW_TAG_member, name: "forbidchunk", scope: !455, file: !121, line: 751, baseType: !423, size: 8, align: 8, offset: 2392)
!527 = !DIDerivedType(tag: DW_TAG_member, name: "protop", scope: !455, file: !121, line: 755, baseType: !311, size: 64, align: 64, offset: 2432)
!528 = !DIDerivedType(tag: DW_TAG_member, name: "set", scope: !257, file: !121, line: 1829, baseType: !529, size: 13760, align: 64, offset: 3456)
!529 = !DICompositeType(tag: DW_TAG_structure_type, name: "UserDefined", file: !121, line: 1558, size: 13760, align: 64, elements: !530)
!530 = !{!531, !586, !587, !588, !589, !590, !591, !592, !593, !594, !595, !596, !597, !598, !599, !600, !601, !606, !607, !608, !609, !614, !615, !616, !618, !619, !620, !626, !631, !647, !659, !670, !671, !695, !696, !701, !702, !703, !708, !709, !710, !711, !712, !713, !714, !715, !716, !717, !718, !719, !720, !721, !722, !723, !724, !730, !731, !749, !750, !751, !752, !753, !754, !755, !756, !757, !758, !759, !760, !761, !770, !771, !783, !784, !820, !821, !825, !827, !828, !829, !830, !831, !832, !833, !840, !841, !867, !868, !869, !870, !871, !872, !873, !874, !875, !876, !877, !878, !879, !880, !881, !882, !883, !884, !885, !886, !893, !894, !895, !896, !897, !898, !899, !900, !909, !917, !925, !926, !927, !928, !929, !930, !931, !932, !933, !934, !935, !936, !937, !941, !942, !943, !944, !945, !946, !963, !964, !965, !972, !977, !982, !983, !984, !985, !986, !987, !988, !989, !990, !991, !992, !993, !994, !995, !996, !997, !998, !1004}
!531 = !DIDerivedType(tag: DW_TAG_member, name: "err", scope: !529, file: !121, line: 1559, baseType: !532, size: 64, align: 64)
!532 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !533, size: 64, align: 64)
!533 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !534, line: 48, baseType: !535)
!534 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!535 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !536, line: 245, size: 1728, align: 64, elements: !537)
!536 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!537 = !{!538, !539, !540, !541, !542, !543, !544, !545, !546, !547, !548, !549, !550, !558, !559, !560, !561, !563, !565, !567, !571, !574, !576, !577, !578, !579, !580, !581, !582}
!538 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !535, file: !536, line: 246, baseType: !316, size: 32, align: 32)
!539 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !535, file: !536, line: 251, baseType: !479, size: 64, align: 64, offset: 64)
!540 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !535, file: !536, line: 252, baseType: !479, size: 64, align: 64, offset: 128)
!541 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !535, file: !536, line: 253, baseType: !479, size: 64, align: 64, offset: 192)
!542 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !535, file: !536, line: 254, baseType: !479, size: 64, align: 64, offset: 256)
!543 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !535, file: !536, line: 255, baseType: !479, size: 64, align: 64, offset: 320)
!544 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !535, file: !536, line: 256, baseType: !479, size: 64, align: 64, offset: 384)
!545 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !535, file: !536, line: 257, baseType: !479, size: 64, align: 64, offset: 448)
!546 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !535, file: !536, line: 258, baseType: !479, size: 64, align: 64, offset: 512)
!547 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !535, file: !536, line: 260, baseType: !479, size: 64, align: 64, offset: 576)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !535, file: !536, line: 261, baseType: !479, size: 64, align: 64, offset: 640)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !535, file: !536, line: 262, baseType: !479, size: 64, align: 64, offset: 704)
!550 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !535, file: !536, line: 264, baseType: !551, size: 64, align: 64, offset: 768)
!551 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !552, size: 64, align: 64)
!552 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !536, line: 160, size: 192, align: 64, elements: !553)
!553 = !{!554, !555, !557}
!554 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !552, file: !536, line: 161, baseType: !551, size: 64, align: 64)
!555 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !552, file: !536, line: 162, baseType: !556, size: 64, align: 64, offset: 64)
!556 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !535, size: 64, align: 64)
!557 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !552, file: !536, line: 166, baseType: !316, size: 32, align: 32, offset: 128)
!558 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !535, file: !536, line: 266, baseType: !556, size: 64, align: 64, offset: 832)
!559 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !535, file: !536, line: 268, baseType: !316, size: 32, align: 32, offset: 896)
!560 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !535, file: !536, line: 272, baseType: !316, size: 32, align: 32, offset: 928)
!561 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !535, file: !536, line: 274, baseType: !562, size: 64, align: 64, offset: 960)
!562 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !416, line: 131, baseType: !379)
!563 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !535, file: !536, line: 278, baseType: !564, size: 16, align: 16, offset: 1024)
!564 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!565 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !535, file: !536, line: 279, baseType: !566, size: 8, align: 8, offset: 1040)
!566 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!567 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !535, file: !536, line: 280, baseType: !568, size: 8, align: 8, offset: 1048)
!568 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 8, align: 8, elements: !569)
!569 = !{!570}
!570 = !DISubrange(count: 1)
!571 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !535, file: !536, line: 284, baseType: !572, size: 64, align: 64, offset: 1088)
!572 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !573, size: 64, align: 64)
!573 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !536, line: 154, baseType: null)
!574 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !535, file: !536, line: 293, baseType: !575, size: 64, align: 64, offset: 1152)
!575 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !416, line: 132, baseType: !379)
!576 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !535, file: !536, line: 302, baseType: !311, size: 64, align: 64, offset: 1216)
!577 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !535, file: !536, line: 303, baseType: !311, size: 64, align: 64, offset: 1280)
!578 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !535, file: !536, line: 304, baseType: !311, size: 64, align: 64, offset: 1344)
!579 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !535, file: !536, line: 305, baseType: !311, size: 64, align: 64, offset: 1408)
!580 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !535, file: !536, line: 306, baseType: !347, size: 64, align: 64, offset: 1472)
!581 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !535, file: !536, line: 308, baseType: !316, size: 32, align: 32, offset: 1536)
!582 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !535, file: !536, line: 310, baseType: !583, size: 160, align: 8, offset: 1568)
!583 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 160, align: 8, elements: !584)
!584 = !{!585}
!585 = !DISubrange(count: 20)
!586 = !DIDerivedType(tag: DW_TAG_member, name: "debugdata", scope: !529, file: !121, line: 1560, baseType: !311, size: 64, align: 64, offset: 64)
!587 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuffer", scope: !529, file: !121, line: 1561, baseType: !479, size: 64, align: 64, offset: 128)
!588 = !DIDerivedType(tag: DW_TAG_member, name: "proxyport", scope: !529, file: !121, line: 1562, baseType: !379, size: 64, align: 64, offset: 192)
!589 = !DIDerivedType(tag: DW_TAG_member, name: "out", scope: !529, file: !121, line: 1565, baseType: !311, size: 64, align: 64, offset: 256)
!590 = !DIDerivedType(tag: DW_TAG_member, name: "in_set", scope: !529, file: !121, line: 1566, baseType: !311, size: 64, align: 64, offset: 320)
!591 = !DIDerivedType(tag: DW_TAG_member, name: "writeheader", scope: !529, file: !121, line: 1567, baseType: !311, size: 64, align: 64, offset: 384)
!592 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_out", scope: !529, file: !121, line: 1568, baseType: !311, size: 64, align: 64, offset: 448)
!593 = !DIDerivedType(tag: DW_TAG_member, name: "use_port", scope: !529, file: !121, line: 1569, baseType: !379, size: 64, align: 64, offset: 512)
!594 = !DIDerivedType(tag: DW_TAG_member, name: "httpauth", scope: !529, file: !121, line: 1570, baseType: !349, size: 64, align: 64, offset: 576)
!595 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauth", scope: !529, file: !121, line: 1571, baseType: !349, size: 64, align: 64, offset: 640)
!596 = !DIDerivedType(tag: DW_TAG_member, name: "followlocation", scope: !529, file: !121, line: 1572, baseType: !379, size: 64, align: 64, offset: 704)
!597 = !DIDerivedType(tag: DW_TAG_member, name: "maxredirs", scope: !529, file: !121, line: 1573, baseType: !379, size: 64, align: 64, offset: 768)
!598 = !DIDerivedType(tag: DW_TAG_member, name: "keep_post", scope: !529, file: !121, line: 1576, baseType: !316, size: 32, align: 32, offset: 832)
!599 = !DIDerivedType(tag: DW_TAG_member, name: "free_referer", scope: !529, file: !121, line: 1578, baseType: !423, size: 8, align: 8, offset: 864)
!600 = !DIDerivedType(tag: DW_TAG_member, name: "postfields", scope: !529, file: !121, line: 1580, baseType: !311, size: 64, align: 64, offset: 896)
!601 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !529, file: !121, line: 1581, baseType: !602, size: 64, align: 64, offset: 960)
!602 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_seek_callback", file: !15, line: 324, baseType: !603)
!603 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !604, size: 64, align: 64)
!604 = !DISubroutineType(types: !605)
!605 = !{!316, !311, !458, !316}
!606 = !DIDerivedType(tag: DW_TAG_member, name: "postfieldsize", scope: !529, file: !121, line: 1582, baseType: !458, size: 64, align: 64, offset: 1024)
!607 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !529, file: !121, line: 1585, baseType: !564, size: 16, align: 16, offset: 1088)
!608 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !529, file: !121, line: 1586, baseType: !316, size: 32, align: 32, offset: 1120)
!609 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_func", scope: !529, file: !121, line: 1588, baseType: !610, size: 64, align: 64, offset: 1152)
!610 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_write_callback", file: !15, line: 223, baseType: !611)
!611 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !612, size: 64, align: 64)
!612 = !DISubroutineType(types: !613)
!613 = !{!347, !479, !347, !347, !311}
!614 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_header", scope: !529, file: !121, line: 1589, baseType: !610, size: 64, align: 64, offset: 1216)
!615 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_rtp", scope: !529, file: !121, line: 1590, baseType: !610, size: 64, align: 64, offset: 1280)
!616 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func_set", scope: !529, file: !121, line: 1591, baseType: !617, size: 64, align: 64, offset: 1344)
!617 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_read_callback", file: !15, line: 335, baseType: !611)
!618 = !DIDerivedType(tag: DW_TAG_member, name: "is_fread_set", scope: !529, file: !121, line: 1592, baseType: !316, size: 32, align: 32, offset: 1408)
!619 = !DIDerivedType(tag: DW_TAG_member, name: "is_fwrite_set", scope: !529, file: !121, line: 1593, baseType: !316, size: 32, align: 32, offset: 1440)
!620 = !DIDerivedType(tag: DW_TAG_member, name: "fprogress", scope: !529, file: !121, line: 1594, baseType: !621, size: 64, align: 64, offset: 1472)
!621 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_progress_callback", file: !15, line: 183, baseType: !622)
!622 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !623, size: 64, align: 64)
!623 = !DISubroutineType(types: !624)
!624 = !{!316, !311, !625, !625, !625, !625}
!625 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!626 = !DIDerivedType(tag: DW_TAG_member, name: "fxferinfo", scope: !529, file: !121, line: 1595, baseType: !627, size: 64, align: 64, offset: 1536)
!627 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_xferinfo_callback", file: !15, line: 191, baseType: !628)
!628 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !629, size: 64, align: 64)
!629 = !DISubroutineType(types: !630)
!630 = !{!316, !311, !458, !458, !458, !458}
!631 = !DIDerivedType(tag: DW_TAG_member, name: "fdebug", scope: !529, file: !121, line: 1596, baseType: !632, size: 64, align: 64, offset: 1600)
!632 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_debug_callback", file: !15, line: 420, baseType: !633)
!633 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !634, size: 64, align: 64)
!634 = !DISubroutineType(types: !635)
!635 = !{!316, !305, !636, !479, !347, !311}
!636 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_infotype", file: !15, line: 418, baseType: !637)
!637 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 409, size: 32, align: 32, elements: !638)
!638 = !{!639, !640, !641, !642, !643, !644, !645, !646}
!639 = !DIEnumerator(name: "CURLINFO_TEXT", value: 0)
!640 = !DIEnumerator(name: "CURLINFO_HEADER_IN", value: 1)
!641 = !DIEnumerator(name: "CURLINFO_HEADER_OUT", value: 2)
!642 = !DIEnumerator(name: "CURLINFO_DATA_IN", value: 3)
!643 = !DIEnumerator(name: "CURLINFO_DATA_OUT", value: 4)
!644 = !DIEnumerator(name: "CURLINFO_SSL_DATA_IN", value: 5)
!645 = !DIEnumerator(name: "CURLINFO_SSL_DATA_OUT", value: 6)
!646 = !DIEnumerator(name: "CURLINFO_END", value: 7)
!647 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_func", scope: !529, file: !121, line: 1597, baseType: !648, size: 64, align: 64, offset: 1664)
!648 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ioctl_callback", file: !15, line: 388, baseType: !649)
!649 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !650, size: 64, align: 64)
!650 = !DISubroutineType(types: !651)
!651 = !{!652, !305, !316, !311}
!652 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlioerr", file: !15, line: 380, baseType: !653)
!653 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 375, size: 32, align: 32, elements: !654)
!654 = !{!655, !656, !657, !658}
!655 = !DIEnumerator(name: "CURLIOE_OK", value: 0)
!656 = !DIEnumerator(name: "CURLIOE_UNKNOWNCMD", value: 1)
!657 = !DIEnumerator(name: "CURLIOE_FAILRESTART", value: 2)
!658 = !DIEnumerator(name: "CURLIOE_LAST", value: 3)
!659 = !DIDerivedType(tag: DW_TAG_member, name: "fsockopt", scope: !529, file: !121, line: 1598, baseType: !660, size: 64, align: 64, offset: 1728)
!660 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sockopt_callback", file: !15, line: 353, baseType: !661)
!661 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !662, size: 64, align: 64)
!662 = !DISubroutineType(types: !663)
!663 = !{!316, !311, !315, !664}
!664 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlsocktype", file: !15, line: 344, baseType: !665)
!665 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 340, size: 32, align: 32, elements: !666)
!666 = !{!667, !668, !669}
!667 = !DIEnumerator(name: "CURLSOCKTYPE_IPCXN", value: 0)
!668 = !DIEnumerator(name: "CURLSOCKTYPE_ACCEPT", value: 1)
!669 = !DIEnumerator(name: "CURLSOCKTYPE_LAST", value: 2)
!670 = !DIDerivedType(tag: DW_TAG_member, name: "sockopt_client", scope: !529, file: !121, line: 1599, baseType: !311, size: 64, align: 64, offset: 1792)
!671 = !DIDerivedType(tag: DW_TAG_member, name: "fopensocket", scope: !529, file: !121, line: 1600, baseType: !672, size: 64, align: 64, offset: 1856)
!672 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_opensocket_callback", file: !15, line: 368, baseType: !673)
!673 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !674, size: 64, align: 64)
!674 = !DISubroutineType(types: !675)
!675 = !{!315, !311, !664, !676}
!676 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !677, size: 64, align: 64)
!677 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_sockaddr", file: !15, line: 357, size: 256, align: 32, elements: !678)
!678 = !{!679, !680, !681, !682, !684}
!679 = !DIDerivedType(tag: DW_TAG_member, name: "family", scope: !677, file: !15, line: 358, baseType: !316, size: 32, align: 32)
!680 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !677, file: !15, line: 359, baseType: !316, size: 32, align: 32, offset: 32)
!681 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !677, file: !15, line: 360, baseType: !316, size: 32, align: 32, offset: 64)
!682 = !DIDerivedType(tag: DW_TAG_member, name: "addrlen", scope: !677, file: !15, line: 361, baseType: !683, size: 32, align: 32, offset: 96)
!683 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!684 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !677, file: !15, line: 364, baseType: !685, size: 128, align: 16, offset: 128)
!685 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !686, line: 149, size: 128, align: 16, elements: !687)
!686 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!687 = !{!688, !691}
!688 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !685, file: !686, line: 151, baseType: !689, size: 16, align: 16)
!689 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !690, line: 28, baseType: !564)
!690 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!691 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !685, file: !686, line: 152, baseType: !692, size: 112, align: 8, offset: 16)
!692 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 112, align: 8, elements: !693)
!693 = !{!694}
!694 = !DISubrange(count: 14)
!695 = !DIDerivedType(tag: DW_TAG_member, name: "opensocket_client", scope: !529, file: !121, line: 1603, baseType: !311, size: 64, align: 64, offset: 1920)
!696 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !529, file: !121, line: 1604, baseType: !697, size: 64, align: 64, offset: 1984)
!697 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_closesocket_callback", file: !15, line: 373, baseType: !698)
!698 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !699, size: 64, align: 64)
!699 = !DISubroutineType(types: !700)
!700 = !{!316, !311, !315}
!701 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !529, file: !121, line: 1606, baseType: !311, size: 64, align: 64, offset: 2048)
!702 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !529, file: !121, line: 1608, baseType: !311, size: 64, align: 64, offset: 2112)
!703 = !DIDerivedType(tag: DW_TAG_member, name: "convfromnetwork", scope: !529, file: !121, line: 1611, baseType: !704, size: 64, align: 64, offset: 2176)
!704 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_conv_callback", file: !15, line: 637, baseType: !705)
!705 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !706, size: 64, align: 64)
!706 = !DISubroutineType(types: !707)
!707 = !{!289, !479, !347}
!708 = !DIDerivedType(tag: DW_TAG_member, name: "convtonetwork", scope: !529, file: !121, line: 1613, baseType: !704, size: 64, align: 64, offset: 2240)
!709 = !DIDerivedType(tag: DW_TAG_member, name: "convfromutf8", scope: !529, file: !121, line: 1615, baseType: !704, size: 64, align: 64, offset: 2304)
!710 = !DIDerivedType(tag: DW_TAG_member, name: "progress_client", scope: !529, file: !121, line: 1617, baseType: !311, size: 64, align: 64, offset: 2368)
!711 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_client", scope: !529, file: !121, line: 1618, baseType: !311, size: 64, align: 64, offset: 2432)
!712 = !DIDerivedType(tag: DW_TAG_member, name: "timeout", scope: !529, file: !121, line: 1619, baseType: !379, size: 64, align: 64, offset: 2496)
!713 = !DIDerivedType(tag: DW_TAG_member, name: "connecttimeout", scope: !529, file: !121, line: 1620, baseType: !379, size: 64, align: 64, offset: 2560)
!714 = !DIDerivedType(tag: DW_TAG_member, name: "accepttimeout", scope: !529, file: !121, line: 1621, baseType: !379, size: 64, align: 64, offset: 2624)
!715 = !DIDerivedType(tag: DW_TAG_member, name: "server_response_timeout", scope: !529, file: !121, line: 1622, baseType: !379, size: 64, align: 64, offset: 2688)
!716 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_blksize", scope: !529, file: !121, line: 1623, baseType: !379, size: 64, align: 64, offset: 2752)
!717 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_no_options", scope: !529, file: !121, line: 1624, baseType: !423, size: 8, align: 8, offset: 2816)
!718 = !DIDerivedType(tag: DW_TAG_member, name: "filesize", scope: !529, file: !121, line: 1625, baseType: !458, size: 64, align: 64, offset: 2880)
!719 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_limit", scope: !529, file: !121, line: 1626, baseType: !379, size: 64, align: 64, offset: 2944)
!720 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_time", scope: !529, file: !121, line: 1627, baseType: !379, size: 64, align: 64, offset: 3008)
!721 = !DIDerivedType(tag: DW_TAG_member, name: "max_send_speed", scope: !529, file: !121, line: 1628, baseType: !458, size: 64, align: 64, offset: 3072)
!722 = !DIDerivedType(tag: DW_TAG_member, name: "max_recv_speed", scope: !529, file: !121, line: 1629, baseType: !458, size: 64, align: 64, offset: 3136)
!723 = !DIDerivedType(tag: DW_TAG_member, name: "set_resume_from", scope: !529, file: !121, line: 1631, baseType: !458, size: 64, align: 64, offset: 3200)
!724 = !DIDerivedType(tag: DW_TAG_member, name: "headers", scope: !529, file: !121, line: 1632, baseType: !725, size: 64, align: 64, offset: 3264)
!725 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !726, size: 64, align: 64)
!726 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_slist", file: !15, line: 2176, size: 128, align: 64, elements: !727)
!727 = !{!728, !729}
!728 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !726, file: !15, line: 2177, baseType: !479, size: 64, align: 64)
!729 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !726, file: !15, line: 2178, baseType: !725, size: 64, align: 64, offset: 64)
!730 = !DIDerivedType(tag: DW_TAG_member, name: "proxyheaders", scope: !529, file: !121, line: 1633, baseType: !725, size: 64, align: 64, offset: 3328)
!731 = !DIDerivedType(tag: DW_TAG_member, name: "httppost", scope: !529, file: !121, line: 1634, baseType: !732, size: 64, align: 64, offset: 3392)
!732 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !733, size: 64, align: 64)
!733 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_httppost", file: !15, line: 137, size: 896, align: 64, elements: !734)
!734 = !{!735, !736, !737, !738, !739, !740, !741, !742, !743, !744, !745, !746, !747, !748}
!735 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !733, file: !15, line: 138, baseType: !732, size: 64, align: 64)
!736 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !733, file: !15, line: 139, baseType: !479, size: 64, align: 64, offset: 64)
!737 = !DIDerivedType(tag: DW_TAG_member, name: "namelength", scope: !733, file: !15, line: 140, baseType: !379, size: 64, align: 64, offset: 128)
!738 = !DIDerivedType(tag: DW_TAG_member, name: "contents", scope: !733, file: !15, line: 141, baseType: !479, size: 64, align: 64, offset: 192)
!739 = !DIDerivedType(tag: DW_TAG_member, name: "contentslength", scope: !733, file: !15, line: 142, baseType: !379, size: 64, align: 64, offset: 256)
!740 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !733, file: !15, line: 144, baseType: !479, size: 64, align: 64, offset: 320)
!741 = !DIDerivedType(tag: DW_TAG_member, name: "bufferlength", scope: !733, file: !15, line: 145, baseType: !379, size: 64, align: 64, offset: 384)
!742 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !733, file: !15, line: 146, baseType: !479, size: 64, align: 64, offset: 448)
!743 = !DIDerivedType(tag: DW_TAG_member, name: "contentheader", scope: !733, file: !15, line: 147, baseType: !725, size: 64, align: 64, offset: 512)
!744 = !DIDerivedType(tag: DW_TAG_member, name: "more", scope: !733, file: !15, line: 148, baseType: !732, size: 64, align: 64, offset: 576)
!745 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !733, file: !15, line: 151, baseType: !379, size: 64, align: 64, offset: 640)
!746 = !DIDerivedType(tag: DW_TAG_member, name: "showfilename", scope: !733, file: !15, line: 171, baseType: !479, size: 64, align: 64, offset: 704)
!747 = !DIDerivedType(tag: DW_TAG_member, name: "userp", scope: !733, file: !15, line: 174, baseType: !311, size: 64, align: 64, offset: 768)
!748 = !DIDerivedType(tag: DW_TAG_member, name: "contentlen", scope: !733, file: !15, line: 176, baseType: !458, size: 64, align: 64, offset: 832)
!749 = !DIDerivedType(tag: DW_TAG_member, name: "sep_headers", scope: !529, file: !121, line: 1635, baseType: !423, size: 8, align: 8, offset: 3456)
!750 = !DIDerivedType(tag: DW_TAG_member, name: "cookiesession", scope: !529, file: !121, line: 1636, baseType: !423, size: 8, align: 8, offset: 3464)
!751 = !DIDerivedType(tag: DW_TAG_member, name: "crlf", scope: !529, file: !121, line: 1637, baseType: !423, size: 8, align: 8, offset: 3472)
!752 = !DIDerivedType(tag: DW_TAG_member, name: "quote", scope: !529, file: !121, line: 1638, baseType: !725, size: 64, align: 64, offset: 3520)
!753 = !DIDerivedType(tag: DW_TAG_member, name: "postquote", scope: !529, file: !121, line: 1639, baseType: !725, size: 64, align: 64, offset: 3584)
!754 = !DIDerivedType(tag: DW_TAG_member, name: "prequote", scope: !529, file: !121, line: 1640, baseType: !725, size: 64, align: 64, offset: 3648)
!755 = !DIDerivedType(tag: DW_TAG_member, name: "source_quote", scope: !529, file: !121, line: 1641, baseType: !725, size: 64, align: 64, offset: 3712)
!756 = !DIDerivedType(tag: DW_TAG_member, name: "source_prequote", scope: !529, file: !121, line: 1642, baseType: !725, size: 64, align: 64, offset: 3776)
!757 = !DIDerivedType(tag: DW_TAG_member, name: "source_postquote", scope: !529, file: !121, line: 1644, baseType: !725, size: 64, align: 64, offset: 3840)
!758 = !DIDerivedType(tag: DW_TAG_member, name: "telnet_options", scope: !529, file: !121, line: 1646, baseType: !725, size: 64, align: 64, offset: 3904)
!759 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !529, file: !121, line: 1647, baseType: !725, size: 64, align: 64, offset: 3968)
!760 = !DIDerivedType(tag: DW_TAG_member, name: "connect_to", scope: !529, file: !121, line: 1649, baseType: !725, size: 64, align: 64, offset: 4032)
!761 = !DIDerivedType(tag: DW_TAG_member, name: "timecondition", scope: !529, file: !121, line: 1651, baseType: !762, size: 32, align: 32, offset: 4096)
!762 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_TimeCond", file: !15, line: 1929, baseType: !763)
!763 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 1921, size: 32, align: 32, elements: !764)
!764 = !{!765, !766, !767, !768, !769}
!765 = !DIEnumerator(name: "CURL_TIMECOND_NONE", value: 0)
!766 = !DIEnumerator(name: "CURL_TIMECOND_IFMODSINCE", value: 1)
!767 = !DIEnumerator(name: "CURL_TIMECOND_IFUNMODSINCE", value: 2)
!768 = !DIEnumerator(name: "CURL_TIMECOND_LASTMOD", value: 3)
!769 = !DIEnumerator(name: "CURL_TIMECOND_LAST", value: 4)
!770 = !DIDerivedType(tag: DW_TAG_member, name: "timevalue", scope: !529, file: !121, line: 1652, baseType: !506, size: 64, align: 64, offset: 4160)
!771 = !DIDerivedType(tag: DW_TAG_member, name: "httpreq", scope: !529, file: !121, line: 1653, baseType: !772, size: 32, align: 32, offset: 4224)
!772 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_HttpReq", file: !121, line: 1249, baseType: !773)
!773 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 1240, size: 32, align: 32, elements: !774)
!774 = !{!775, !776, !777, !778, !779, !780, !781, !782}
!775 = !DIEnumerator(name: "HTTPREQ_NONE", value: 0)
!776 = !DIEnumerator(name: "HTTPREQ_GET", value: 1)
!777 = !DIEnumerator(name: "HTTPREQ_POST", value: 2)
!778 = !DIEnumerator(name: "HTTPREQ_POST_FORM", value: 3)
!779 = !DIEnumerator(name: "HTTPREQ_PUT", value: 4)
!780 = !DIEnumerator(name: "HTTPREQ_HEAD", value: 5)
!781 = !DIEnumerator(name: "HTTPREQ_CUSTOM", value: 6)
!782 = !DIEnumerator(name: "HTTPREQ_LAST", value: 7)
!783 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !529, file: !121, line: 1654, baseType: !379, size: 64, align: 64, offset: 4288)
!784 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !529, file: !121, line: 1656, baseType: !785, size: 1408, align: 64, offset: 4352)
!785 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_config_data", file: !121, line: 366, size: 1408, align: 64, elements: !786)
!786 = !{!787, !802, !803, !804, !805, !806, !807, !812, !813, !814, !815, !816, !817, !818, !819}
!787 = !DIDerivedType(tag: DW_TAG_member, name: "primary", scope: !785, file: !121, line: 367, baseType: !788, size: 640, align: 64)
!788 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_primary_config", file: !121, line: 351, size: 640, align: 64, elements: !789)
!789 = !{!790, !791, !792, !793, !794, !795, !796, !797, !798, !799, !800, !801}
!790 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !788, file: !121, line: 352, baseType: !379, size: 64, align: 64)
!791 = !DIDerivedType(tag: DW_TAG_member, name: "version_max", scope: !788, file: !121, line: 353, baseType: !379, size: 64, align: 64, offset: 64)
!792 = !DIDerivedType(tag: DW_TAG_member, name: "verifypeer", scope: !788, file: !121, line: 354, baseType: !423, size: 8, align: 8, offset: 128)
!793 = !DIDerivedType(tag: DW_TAG_member, name: "verifyhost", scope: !788, file: !121, line: 355, baseType: !423, size: 8, align: 8, offset: 136)
!794 = !DIDerivedType(tag: DW_TAG_member, name: "verifystatus", scope: !788, file: !121, line: 356, baseType: !423, size: 8, align: 8, offset: 144)
!795 = !DIDerivedType(tag: DW_TAG_member, name: "CApath", scope: !788, file: !121, line: 357, baseType: !479, size: 64, align: 64, offset: 192)
!796 = !DIDerivedType(tag: DW_TAG_member, name: "CAfile", scope: !788, file: !121, line: 358, baseType: !479, size: 64, align: 64, offset: 256)
!797 = !DIDerivedType(tag: DW_TAG_member, name: "clientcert", scope: !788, file: !121, line: 359, baseType: !479, size: 64, align: 64, offset: 320)
!798 = !DIDerivedType(tag: DW_TAG_member, name: "random_file", scope: !788, file: !121, line: 360, baseType: !479, size: 64, align: 64, offset: 384)
!799 = !DIDerivedType(tag: DW_TAG_member, name: "egdsocket", scope: !788, file: !121, line: 361, baseType: !479, size: 64, align: 64, offset: 448)
!800 = !DIDerivedType(tag: DW_TAG_member, name: "cipher_list", scope: !788, file: !121, line: 362, baseType: !479, size: 64, align: 64, offset: 512)
!801 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !788, file: !121, line: 363, baseType: !423, size: 8, align: 8, offset: 576)
!802 = !DIDerivedType(tag: DW_TAG_member, name: "enable_beast", scope: !785, file: !121, line: 368, baseType: !423, size: 8, align: 8, offset: 640)
!803 = !DIDerivedType(tag: DW_TAG_member, name: "no_revoke", scope: !785, file: !121, line: 370, baseType: !423, size: 8, align: 8, offset: 648)
!804 = !DIDerivedType(tag: DW_TAG_member, name: "certverifyresult", scope: !785, file: !121, line: 371, baseType: !379, size: 64, align: 64, offset: 704)
!805 = !DIDerivedType(tag: DW_TAG_member, name: "CRLfile", scope: !785, file: !121, line: 372, baseType: !479, size: 64, align: 64, offset: 768)
!806 = !DIDerivedType(tag: DW_TAG_member, name: "issuercert", scope: !785, file: !121, line: 373, baseType: !479, size: 64, align: 64, offset: 832)
!807 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctx", scope: !785, file: !121, line: 374, baseType: !808, size: 64, align: 64, offset: 896)
!808 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ssl_ctx_callback", file: !15, line: 639, baseType: !809)
!809 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !810, size: 64, align: 64)
!810 = !DISubroutineType(types: !811)
!811 = !{!289, !305, !311, !311}
!812 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctxp", scope: !785, file: !121, line: 375, baseType: !311, size: 64, align: 64, offset: 960)
!813 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !785, file: !121, line: 376, baseType: !423, size: 8, align: 8, offset: 1024)
!814 = !DIDerivedType(tag: DW_TAG_member, name: "falsestart", scope: !785, file: !121, line: 377, baseType: !423, size: 8, align: 8, offset: 1032)
!815 = !DIDerivedType(tag: DW_TAG_member, name: "cert", scope: !785, file: !121, line: 379, baseType: !479, size: 64, align: 64, offset: 1088)
!816 = !DIDerivedType(tag: DW_TAG_member, name: "cert_type", scope: !785, file: !121, line: 380, baseType: !479, size: 64, align: 64, offset: 1152)
!817 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !785, file: !121, line: 381, baseType: !479, size: 64, align: 64, offset: 1216)
!818 = !DIDerivedType(tag: DW_TAG_member, name: "key_type", scope: !785, file: !121, line: 382, baseType: !479, size: 64, align: 64, offset: 1280)
!819 = !DIDerivedType(tag: DW_TAG_member, name: "key_passwd", scope: !785, file: !121, line: 383, baseType: !479, size: 64, align: 64, offset: 1344)
!820 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !529, file: !121, line: 1657, baseType: !785, size: 1408, align: 64, offset: 5760)
!821 = !DIDerivedType(tag: DW_TAG_member, name: "general_ssl", scope: !529, file: !121, line: 1658, baseType: !822, size: 64, align: 64, offset: 7168)
!822 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_general_config", file: !121, line: 392, size: 64, align: 64, elements: !823)
!823 = !{!824}
!824 = !DIDerivedType(tag: DW_TAG_member, name: "max_ssl_sessions", scope: !822, file: !121, line: 393, baseType: !347, size: 64, align: 64)
!825 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !529, file: !121, line: 1659, baseType: !826, size: 32, align: 32, offset: 7232)
!826 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_proxytype", file: !15, line: 657, baseType: !14)
!827 = !DIDerivedType(tag: DW_TAG_member, name: "dns_cache_timeout", scope: !529, file: !121, line: 1660, baseType: !379, size: 64, align: 64, offset: 7296)
!828 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !529, file: !121, line: 1661, baseType: !379, size: 64, align: 64, offset: 7360)
!829 = !DIDerivedType(tag: DW_TAG_member, name: "private_data", scope: !529, file: !121, line: 1662, baseType: !311, size: 64, align: 64, offset: 7424)
!830 = !DIDerivedType(tag: DW_TAG_member, name: "http200aliases", scope: !529, file: !121, line: 1664, baseType: !725, size: 64, align: 64, offset: 7488)
!831 = !DIDerivedType(tag: DW_TAG_member, name: "ipver", scope: !529, file: !121, line: 1666, baseType: !379, size: 64, align: 64, offset: 7552)
!832 = !DIDerivedType(tag: DW_TAG_member, name: "max_filesize", scope: !529, file: !121, line: 1669, baseType: !458, size: 64, align: 64, offset: 7616)
!833 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_filemethod", scope: !529, file: !121, line: 1671, baseType: !834, size: 32, align: 32, offset: 7680)
!834 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpfile", file: !135, line: 98, baseType: !835)
!835 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !135, line: 93, size: 32, align: 32, elements: !836)
!836 = !{!837, !838, !839}
!837 = !DIEnumerator(name: "FTPFILE_MULTICWD", value: 1)
!838 = !DIEnumerator(name: "FTPFILE_NOCWD", value: 2)
!839 = !DIEnumerator(name: "FTPFILE_SINGLECWD", value: 3)
!840 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_create_missing_dirs", scope: !529, file: !121, line: 1673, baseType: !316, size: 32, align: 32, offset: 7712)
!841 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc", scope: !529, file: !121, line: 1677, baseType: !842, size: 64, align: 64, offset: 7744)
!842 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sshkeycallback", file: !15, line: 739, baseType: !843)
!843 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !844, size: 64, align: 64)
!844 = !DISubroutineType(types: !845)
!845 = !{!316, !305, !846, !846, !861, !311}
!846 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !847, size: 64, align: 64)
!847 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !848)
!848 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_khkey", file: !15, line: 711, size: 192, align: 64, elements: !849)
!849 = !{!850, !853, !854}
!850 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !848, file: !15, line: 712, baseType: !851, size: 64, align: 64)
!851 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !852, size: 64, align: 64)
!852 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !480)
!853 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !848, file: !15, line: 714, baseType: !347, size: 64, align: 64, offset: 64)
!854 = !DIDerivedType(tag: DW_TAG_member, name: "keytype", scope: !848, file: !15, line: 715, baseType: !855, size: 32, align: 32, offset: 128)
!855 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khtype", file: !15, line: 704, size: 32, align: 32, elements: !856)
!856 = !{!857, !858, !859, !860}
!857 = !DIEnumerator(name: "CURLKHTYPE_UNKNOWN", value: 0)
!858 = !DIEnumerator(name: "CURLKHTYPE_RSA1", value: 1)
!859 = !DIEnumerator(name: "CURLKHTYPE_RSA", value: 2)
!860 = !DIEnumerator(name: "CURLKHTYPE_DSS", value: 3)
!861 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khmatch", file: !15, line: 731, size: 32, align: 32, elements: !862)
!862 = !{!863, !864, !865, !866}
!863 = !DIEnumerator(name: "CURLKHMATCH_OK", value: 0)
!864 = !DIEnumerator(name: "CURLKHMATCH_MISMATCH", value: 1)
!865 = !DIEnumerator(name: "CURLKHMATCH_MISSING", value: 2)
!866 = !DIEnumerator(name: "CURLKHMATCH_LAST", value: 3)
!867 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc_userp", scope: !529, file: !121, line: 1678, baseType: !311, size: 64, align: 64, offset: 7808)
!868 = !DIDerivedType(tag: DW_TAG_member, name: "printhost", scope: !529, file: !121, line: 1684, baseType: !423, size: 8, align: 8, offset: 7872)
!869 = !DIDerivedType(tag: DW_TAG_member, name: "get_filetime", scope: !529, file: !121, line: 1685, baseType: !423, size: 8, align: 8, offset: 7880)
!870 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_thru_httpproxy", scope: !529, file: !121, line: 1686, baseType: !423, size: 8, align: 8, offset: 7888)
!871 = !DIDerivedType(tag: DW_TAG_member, name: "prefer_ascii", scope: !529, file: !121, line: 1687, baseType: !423, size: 8, align: 8, offset: 7896)
!872 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_append", scope: !529, file: !121, line: 1688, baseType: !423, size: 8, align: 8, offset: 7904)
!873 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_list_only", scope: !529, file: !121, line: 1689, baseType: !423, size: 8, align: 8, offset: 7912)
!874 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_port", scope: !529, file: !121, line: 1690, baseType: !423, size: 8, align: 8, offset: 7920)
!875 = !DIDerivedType(tag: DW_TAG_member, name: "hide_progress", scope: !529, file: !121, line: 1691, baseType: !423, size: 8, align: 8, offset: 7928)
!876 = !DIDerivedType(tag: DW_TAG_member, name: "http_fail_on_error", scope: !529, file: !121, line: 1692, baseType: !423, size: 8, align: 8, offset: 7936)
!877 = !DIDerivedType(tag: DW_TAG_member, name: "http_keep_sending_on_error", scope: !529, file: !121, line: 1693, baseType: !423, size: 8, align: 8, offset: 7944)
!878 = !DIDerivedType(tag: DW_TAG_member, name: "http_follow_location", scope: !529, file: !121, line: 1694, baseType: !423, size: 8, align: 8, offset: 7952)
!879 = !DIDerivedType(tag: DW_TAG_member, name: "http_transfer_encoding", scope: !529, file: !121, line: 1695, baseType: !423, size: 8, align: 8, offset: 7960)
!880 = !DIDerivedType(tag: DW_TAG_member, name: "http_disable_hostname_check_before_authentication", scope: !529, file: !121, line: 1696, baseType: !423, size: 8, align: 8, offset: 7968)
!881 = !DIDerivedType(tag: DW_TAG_member, name: "include_header", scope: !529, file: !121, line: 1697, baseType: !423, size: 8, align: 8, offset: 7976)
!882 = !DIDerivedType(tag: DW_TAG_member, name: "http_set_referer", scope: !529, file: !121, line: 1698, baseType: !423, size: 8, align: 8, offset: 7984)
!883 = !DIDerivedType(tag: DW_TAG_member, name: "http_auto_referer", scope: !529, file: !121, line: 1699, baseType: !423, size: 8, align: 8, offset: 7992)
!884 = !DIDerivedType(tag: DW_TAG_member, name: "opt_no_body", scope: !529, file: !121, line: 1700, baseType: !423, size: 8, align: 8, offset: 8000)
!885 = !DIDerivedType(tag: DW_TAG_member, name: "upload", scope: !529, file: !121, line: 1701, baseType: !423, size: 8, align: 8, offset: 8008)
!886 = !DIDerivedType(tag: DW_TAG_member, name: "use_netrc", scope: !529, file: !121, line: 1703, baseType: !887, size: 32, align: 32, offset: 8032)
!887 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "CURL_NETRC_OPTION", file: !15, line: 1867, size: 32, align: 32, elements: !888)
!888 = !{!889, !890, !891, !892}
!889 = !DIEnumerator(name: "CURL_NETRC_IGNORED", value: 0)
!890 = !DIEnumerator(name: "CURL_NETRC_OPTIONAL", value: 1)
!891 = !DIEnumerator(name: "CURL_NETRC_REQUIRED", value: 2)
!892 = !DIEnumerator(name: "CURL_NETRC_LAST", value: 3)
!893 = !DIDerivedType(tag: DW_TAG_member, name: "verbose", scope: !529, file: !121, line: 1704, baseType: !423, size: 8, align: 8, offset: 8064)
!894 = !DIDerivedType(tag: DW_TAG_member, name: "krb", scope: !529, file: !121, line: 1705, baseType: !423, size: 8, align: 8, offset: 8072)
!895 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_forbid", scope: !529, file: !121, line: 1706, baseType: !423, size: 8, align: 8, offset: 8080)
!896 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_fresh", scope: !529, file: !121, line: 1707, baseType: !423, size: 8, align: 8, offset: 8088)
!897 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !529, file: !121, line: 1708, baseType: !423, size: 8, align: 8, offset: 8096)
!898 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !529, file: !121, line: 1709, baseType: !423, size: 8, align: 8, offset: 8104)
!899 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_pret", scope: !529, file: !121, line: 1710, baseType: !423, size: 8, align: 8, offset: 8112)
!900 = !DIDerivedType(tag: DW_TAG_member, name: "use_ssl", scope: !529, file: !121, line: 1712, baseType: !901, size: 32, align: 32, offset: 8128)
!901 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_usessl", file: !15, line: 752, baseType: !902)
!902 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 746, size: 32, align: 32, elements: !903)
!903 = !{!904, !905, !906, !907, !908}
!904 = !DIEnumerator(name: "CURLUSESSL_NONE", value: 0)
!905 = !DIEnumerator(name: "CURLUSESSL_TRY", value: 1)
!906 = !DIEnumerator(name: "CURLUSESSL_CONTROL", value: 2)
!907 = !DIEnumerator(name: "CURLUSESSL_ALL", value: 3)
!908 = !DIEnumerator(name: "CURLUSESSL_LAST", value: 4)
!909 = !DIDerivedType(tag: DW_TAG_member, name: "ftpsslauth", scope: !529, file: !121, line: 1714, baseType: !910, size: 32, align: 32, offset: 8160)
!910 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpauth", file: !15, line: 795, baseType: !911)
!911 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 790, size: 32, align: 32, elements: !912)
!912 = !{!913, !914, !915, !916}
!913 = !DIEnumerator(name: "CURLFTPAUTH_DEFAULT", value: 0)
!914 = !DIEnumerator(name: "CURLFTPAUTH_SSL", value: 1)
!915 = !DIEnumerator(name: "CURLFTPAUTH_TLS", value: 2)
!916 = !DIEnumerator(name: "CURLFTPAUTH_LAST", value: 3)
!917 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_ccc", scope: !529, file: !121, line: 1715, baseType: !918, size: 32, align: 32, offset: 8192)
!918 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpccc", file: !15, line: 787, baseType: !919)
!919 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 782, size: 32, align: 32, elements: !920)
!920 = !{!921, !922, !923, !924}
!921 = !DIEnumerator(name: "CURLFTPSSL_CCC_NONE", value: 0)
!922 = !DIEnumerator(name: "CURLFTPSSL_CCC_PASSIVE", value: 1)
!923 = !DIEnumerator(name: "CURLFTPSSL_CCC_ACTIVE", value: 2)
!924 = !DIEnumerator(name: "CURLFTPSSL_CCC_LAST", value: 3)
!925 = !DIDerivedType(tag: DW_TAG_member, name: "no_signal", scope: !529, file: !121, line: 1716, baseType: !423, size: 8, align: 8, offset: 8224)
!926 = !DIDerivedType(tag: DW_TAG_member, name: "global_dns_cache", scope: !529, file: !121, line: 1717, baseType: !423, size: 8, align: 8, offset: 8232)
!927 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_nodelay", scope: !529, file: !121, line: 1718, baseType: !423, size: 8, align: 8, offset: 8240)
!928 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !529, file: !121, line: 1719, baseType: !423, size: 8, align: 8, offset: 8248)
!929 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_skip_ip", scope: !529, file: !121, line: 1720, baseType: !423, size: 8, align: 8, offset: 8256)
!930 = !DIDerivedType(tag: DW_TAG_member, name: "connect_only", scope: !529, file: !121, line: 1722, baseType: !423, size: 8, align: 8, offset: 8264)
!931 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_auth_types", scope: !529, file: !121, line: 1723, baseType: !379, size: 64, align: 64, offset: 8320)
!932 = !DIDerivedType(tag: DW_TAG_member, name: "http_te_skip", scope: !529, file: !121, line: 1724, baseType: !423, size: 8, align: 8, offset: 8384)
!933 = !DIDerivedType(tag: DW_TAG_member, name: "http_ce_skip", scope: !529, file: !121, line: 1726, baseType: !423, size: 8, align: 8, offset: 8392)
!934 = !DIDerivedType(tag: DW_TAG_member, name: "new_file_perms", scope: !529, file: !121, line: 1728, baseType: !379, size: 64, align: 64, offset: 8448)
!935 = !DIDerivedType(tag: DW_TAG_member, name: "new_directory_perms", scope: !529, file: !121, line: 1729, baseType: !379, size: 64, align: 64, offset: 8512)
!936 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_transfer_mode", scope: !529, file: !121, line: 1730, baseType: !423, size: 8, align: 8, offset: 8576)
!937 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !529, file: !121, line: 1732, baseType: !938, size: 3584, align: 64, offset: 8640)
!938 = !DICompositeType(tag: DW_TAG_array_type, baseType: !479, size: 3584, align: 64, elements: !939)
!939 = !{!940}
!940 = !DISubrange(count: 56)
!941 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !529, file: !121, line: 1733, baseType: !683, size: 32, align: 32, offset: 12224)
!942 = !DIDerivedType(tag: DW_TAG_member, name: "allowed_protocols", scope: !529, file: !121, line: 1734, baseType: !379, size: 64, align: 64, offset: 12288)
!943 = !DIDerivedType(tag: DW_TAG_member, name: "redir_protocols", scope: !529, file: !121, line: 1735, baseType: !379, size: 64, align: 64, offset: 12352)
!944 = !DIDerivedType(tag: DW_TAG_member, name: "mail_rcpt", scope: !529, file: !121, line: 1739, baseType: !725, size: 64, align: 64, offset: 12416)
!945 = !DIDerivedType(tag: DW_TAG_member, name: "sasl_ir", scope: !529, file: !121, line: 1740, baseType: !423, size: 8, align: 8, offset: 12480)
!946 = !DIDerivedType(tag: DW_TAG_member, name: "rtspreq", scope: !529, file: !121, line: 1742, baseType: !947, size: 32, align: 32, offset: 12512)
!947 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_RtspReq", file: !121, line: 1265, baseType: !948)
!948 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 1251, size: 32, align: 32, elements: !949)
!949 = !{!950, !951, !952, !953, !954, !955, !956, !957, !958, !959, !960, !961, !962}
!950 = !DIEnumerator(name: "RTSPREQ_NONE", value: 0)
!951 = !DIEnumerator(name: "RTSPREQ_OPTIONS", value: 1)
!952 = !DIEnumerator(name: "RTSPREQ_DESCRIBE", value: 2)
!953 = !DIEnumerator(name: "RTSPREQ_ANNOUNCE", value: 3)
!954 = !DIEnumerator(name: "RTSPREQ_SETUP", value: 4)
!955 = !DIEnumerator(name: "RTSPREQ_PLAY", value: 5)
!956 = !DIEnumerator(name: "RTSPREQ_PAUSE", value: 6)
!957 = !DIEnumerator(name: "RTSPREQ_TEARDOWN", value: 7)
!958 = !DIEnumerator(name: "RTSPREQ_GET_PARAMETER", value: 8)
!959 = !DIEnumerator(name: "RTSPREQ_SET_PARAMETER", value: 9)
!960 = !DIEnumerator(name: "RTSPREQ_RECORD", value: 10)
!961 = !DIEnumerator(name: "RTSPREQ_RECEIVE", value: 11)
!962 = !DIEnumerator(name: "RTSPREQ_LAST", value: 12)
!963 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !529, file: !121, line: 1743, baseType: !379, size: 64, align: 64, offset: 12544)
!964 = !DIDerivedType(tag: DW_TAG_member, name: "wildcardmatch", scope: !529, file: !121, line: 1744, baseType: !423, size: 8, align: 8, offset: 12608)
!965 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_bgn", scope: !529, file: !121, line: 1745, baseType: !966, size: 64, align: 64, offset: 12672)
!966 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_bgn_callback", file: !15, line: 292, baseType: !967)
!967 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !968, size: 64, align: 64)
!968 = !DISubroutineType(types: !969)
!969 = !{!379, !970, !311, !316}
!970 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !971, size: 64, align: 64)
!971 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!972 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_end", scope: !529, file: !121, line: 1747, baseType: !973, size: 64, align: 64, offset: 12736)
!973 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_end_callback", file: !15, line: 306, baseType: !974)
!974 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !975, size: 64, align: 64)
!975 = !DISubroutineType(types: !976)
!976 = !{!379, !311}
!977 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch", scope: !529, file: !121, line: 1749, baseType: !978, size: 64, align: 64, offset: 12800)
!978 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_fnmatch_callback", file: !15, line: 315, baseType: !979)
!979 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !980, size: 64, align: 64)
!980 = !DISubroutineType(types: !981)
!981 = !{!316, !311, !851, !851}
!982 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch_data", scope: !529, file: !121, line: 1751, baseType: !311, size: 64, align: 64, offset: 12864)
!983 = !DIDerivedType(tag: DW_TAG_member, name: "gssapi_delegation", scope: !529, file: !121, line: 1753, baseType: !379, size: 64, align: 64, offset: 12928)
!984 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepalive", scope: !529, file: !121, line: 1756, baseType: !423, size: 8, align: 8, offset: 12992)
!985 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepidle", scope: !529, file: !121, line: 1757, baseType: !379, size: 64, align: 64, offset: 13056)
!986 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepintvl", scope: !529, file: !121, line: 1758, baseType: !379, size: 64, align: 64, offset: 13120)
!987 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !529, file: !121, line: 1759, baseType: !423, size: 8, align: 8, offset: 13184)
!988 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !529, file: !121, line: 1761, baseType: !347, size: 64, align: 64, offset: 13248)
!989 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_npn", scope: !529, file: !121, line: 1763, baseType: !423, size: 8, align: 8, offset: 13312)
!990 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_alpn", scope: !529, file: !121, line: 1764, baseType: !423, size: 8, align: 8, offset: 13320)
!991 = !DIDerivedType(tag: DW_TAG_member, name: "path_as_is", scope: !529, file: !121, line: 1765, baseType: !423, size: 8, align: 8, offset: 13328)
!992 = !DIDerivedType(tag: DW_TAG_member, name: "pipewait", scope: !529, file: !121, line: 1766, baseType: !423, size: 8, align: 8, offset: 13336)
!993 = !DIDerivedType(tag: DW_TAG_member, name: "expect_100_timeout", scope: !529, file: !121, line: 1768, baseType: !379, size: 64, align: 64, offset: 13376)
!994 = !DIDerivedType(tag: DW_TAG_member, name: "suppress_connect_headers", scope: !529, file: !121, line: 1769, baseType: !423, size: 8, align: 8, offset: 13440)
!995 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !529, file: !121, line: 1772, baseType: !256, size: 64, align: 64, offset: 13504)
!996 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !529, file: !121, line: 1773, baseType: !423, size: 8, align: 8, offset: 13568)
!997 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !529, file: !121, line: 1774, baseType: !316, size: 32, align: 32, offset: 13600)
!998 = !DIDerivedType(tag: DW_TAG_member, name: "stream_dependents", scope: !529, file: !121, line: 1776, baseType: !999, size: 64, align: 64, offset: 13632)
!999 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1000, size: 64, align: 64)
!1000 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_http2_dep", file: !121, line: 1292, size: 128, align: 64, elements: !1001)
!1001 = !{!1002, !1003}
!1002 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1000, file: !121, line: 1293, baseType: !999, size: 64, align: 64)
!1003 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !1000, file: !121, line: 1294, baseType: !256, size: 64, align: 64, offset: 64)
!1004 = !DIDerivedType(tag: DW_TAG_member, name: "abstract_unix_socket", scope: !529, file: !121, line: 1778, baseType: !423, size: 8, align: 8, offset: 13696)
!1005 = !DIDerivedType(tag: DW_TAG_member, name: "change", scope: !257, file: !121, line: 1830, baseType: !1006, size: 384, align: 64, offset: 17216)
!1006 = !DICompositeType(tag: DW_TAG_structure_type, name: "DynamicStatic", file: !121, line: 1444, size: 384, align: 64, elements: !1007)
!1007 = !{!1008, !1009, !1010, !1011, !1012, !1013}
!1008 = !DIDerivedType(tag: DW_TAG_member, name: "url", scope: !1006, file: !121, line: 1445, baseType: !479, size: 64, align: 64)
!1009 = !DIDerivedType(tag: DW_TAG_member, name: "url_alloc", scope: !1006, file: !121, line: 1446, baseType: !423, size: 8, align: 8, offset: 64)
!1010 = !DIDerivedType(tag: DW_TAG_member, name: "referer", scope: !1006, file: !121, line: 1447, baseType: !479, size: 64, align: 64, offset: 128)
!1011 = !DIDerivedType(tag: DW_TAG_member, name: "referer_alloc", scope: !1006, file: !121, line: 1448, baseType: !423, size: 8, align: 8, offset: 192)
!1012 = !DIDerivedType(tag: DW_TAG_member, name: "cookielist", scope: !1006, file: !121, line: 1449, baseType: !725, size: 64, align: 64, offset: 256)
!1013 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !1006, file: !121, line: 1451, baseType: !725, size: 64, align: 64, offset: 320)
!1014 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !257, file: !121, line: 1831, baseType: !1015, size: 64, align: 64, offset: 17600)
!1015 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1016, size: 64, align: 64)
!1016 = !DICompositeType(tag: DW_TAG_structure_type, name: "CookieInfo", file: !1017, line: 48, size: 320, align: 64, elements: !1018)
!1017 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/cookie.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1018 = !{!1019, !1037, !1038, !1039, !1040}
!1019 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !1016, file: !1017, line: 50, baseType: !1020, size: 64, align: 64)
!1020 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1021, size: 64, align: 64)
!1021 = !DICompositeType(tag: DW_TAG_structure_type, name: "Cookie", file: !1017, line: 28, size: 768, align: 64, elements: !1022)
!1022 = !{!1023, !1024, !1025, !1026, !1027, !1028, !1029, !1030, !1031, !1032, !1033, !1034, !1035, !1036}
!1023 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1021, file: !1017, line: 29, baseType: !1020, size: 64, align: 64)
!1024 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1021, file: !1017, line: 30, baseType: !479, size: 64, align: 64, offset: 64)
!1025 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !1021, file: !1017, line: 31, baseType: !479, size: 64, align: 64, offset: 128)
!1026 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1021, file: !1017, line: 32, baseType: !479, size: 64, align: 64, offset: 192)
!1027 = !DIDerivedType(tag: DW_TAG_member, name: "spath", scope: !1021, file: !1017, line: 33, baseType: !479, size: 64, align: 64, offset: 256)
!1028 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1021, file: !1017, line: 34, baseType: !479, size: 64, align: 64, offset: 320)
!1029 = !DIDerivedType(tag: DW_TAG_member, name: "expires", scope: !1021, file: !1017, line: 35, baseType: !458, size: 64, align: 64, offset: 384)
!1030 = !DIDerivedType(tag: DW_TAG_member, name: "expirestr", scope: !1021, file: !1017, line: 36, baseType: !479, size: 64, align: 64, offset: 448)
!1031 = !DIDerivedType(tag: DW_TAG_member, name: "tailmatch", scope: !1021, file: !1017, line: 37, baseType: !423, size: 8, align: 8, offset: 512)
!1032 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !1021, file: !1017, line: 40, baseType: !479, size: 64, align: 64, offset: 576)
!1033 = !DIDerivedType(tag: DW_TAG_member, name: "maxage", scope: !1021, file: !1017, line: 41, baseType: !479, size: 64, align: 64, offset: 640)
!1034 = !DIDerivedType(tag: DW_TAG_member, name: "secure", scope: !1021, file: !1017, line: 43, baseType: !423, size: 8, align: 8, offset: 704)
!1035 = !DIDerivedType(tag: DW_TAG_member, name: "livecookie", scope: !1021, file: !1017, line: 44, baseType: !423, size: 8, align: 8, offset: 712)
!1036 = !DIDerivedType(tag: DW_TAG_member, name: "httponly", scope: !1021, file: !1017, line: 45, baseType: !423, size: 8, align: 8, offset: 720)
!1037 = !DIDerivedType(tag: DW_TAG_member, name: "filename", scope: !1016, file: !1017, line: 52, baseType: !479, size: 64, align: 64, offset: 64)
!1038 = !DIDerivedType(tag: DW_TAG_member, name: "running", scope: !1016, file: !1017, line: 53, baseType: !423, size: 8, align: 8, offset: 128)
!1039 = !DIDerivedType(tag: DW_TAG_member, name: "numcookies", scope: !1016, file: !1017, line: 54, baseType: !379, size: 64, align: 64, offset: 192)
!1040 = !DIDerivedType(tag: DW_TAG_member, name: "newsession", scope: !1016, file: !1017, line: 55, baseType: !423, size: 8, align: 8, offset: 256)
!1041 = !DIDerivedType(tag: DW_TAG_member, name: "progress", scope: !257, file: !121, line: 1835, baseType: !1042, size: 3200, align: 64, offset: 17664)
!1042 = !DICompositeType(tag: DW_TAG_structure_type, name: "Progress", file: !121, line: 1195, size: 3200, align: 64, elements: !1043)
!1043 = !{!1044, !1045, !1046, !1047, !1048, !1049, !1050, !1051, !1052, !1053, !1054, !1055, !1056, !1057, !1058, !1059, !1060, !1061, !1062, !1063, !1064, !1065, !1066, !1067, !1068, !1069, !1070, !1074, !1076}
!1044 = !DIDerivedType(tag: DW_TAG_member, name: "lastshow", scope: !1042, file: !121, line: 1196, baseType: !506, size: 64, align: 64)
!1045 = !DIDerivedType(tag: DW_TAG_member, name: "size_dl", scope: !1042, file: !121, line: 1198, baseType: !458, size: 64, align: 64, offset: 64)
!1046 = !DIDerivedType(tag: DW_TAG_member, name: "size_ul", scope: !1042, file: !121, line: 1199, baseType: !458, size: 64, align: 64, offset: 128)
!1047 = !DIDerivedType(tag: DW_TAG_member, name: "downloaded", scope: !1042, file: !121, line: 1200, baseType: !458, size: 64, align: 64, offset: 192)
!1048 = !DIDerivedType(tag: DW_TAG_member, name: "uploaded", scope: !1042, file: !121, line: 1201, baseType: !458, size: 64, align: 64, offset: 256)
!1049 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1042, file: !121, line: 1203, baseType: !458, size: 64, align: 64, offset: 320)
!1050 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !1042, file: !121, line: 1205, baseType: !423, size: 8, align: 8, offset: 384)
!1051 = !DIDerivedType(tag: DW_TAG_member, name: "width", scope: !1042, file: !121, line: 1206, baseType: !316, size: 32, align: 32, offset: 416)
!1052 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1042, file: !121, line: 1207, baseType: !316, size: 32, align: 32, offset: 448)
!1053 = !DIDerivedType(tag: DW_TAG_member, name: "timespent", scope: !1042, file: !121, line: 1209, baseType: !625, size: 64, align: 64, offset: 512)
!1054 = !DIDerivedType(tag: DW_TAG_member, name: "dlspeed", scope: !1042, file: !121, line: 1211, baseType: !458, size: 64, align: 64, offset: 576)
!1055 = !DIDerivedType(tag: DW_TAG_member, name: "ulspeed", scope: !1042, file: !121, line: 1212, baseType: !458, size: 64, align: 64, offset: 640)
!1056 = !DIDerivedType(tag: DW_TAG_member, name: "t_nslookup", scope: !1042, file: !121, line: 1214, baseType: !625, size: 64, align: 64, offset: 704)
!1057 = !DIDerivedType(tag: DW_TAG_member, name: "t_connect", scope: !1042, file: !121, line: 1215, baseType: !625, size: 64, align: 64, offset: 768)
!1058 = !DIDerivedType(tag: DW_TAG_member, name: "t_appconnect", scope: !1042, file: !121, line: 1216, baseType: !625, size: 64, align: 64, offset: 832)
!1059 = !DIDerivedType(tag: DW_TAG_member, name: "t_pretransfer", scope: !1042, file: !121, line: 1217, baseType: !625, size: 64, align: 64, offset: 896)
!1060 = !DIDerivedType(tag: DW_TAG_member, name: "t_starttransfer", scope: !1042, file: !121, line: 1218, baseType: !625, size: 64, align: 64, offset: 960)
!1061 = !DIDerivedType(tag: DW_TAG_member, name: "t_redirect", scope: !1042, file: !121, line: 1219, baseType: !625, size: 64, align: 64, offset: 1024)
!1062 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !1042, file: !121, line: 1221, baseType: !411, size: 128, align: 64, offset: 1088)
!1063 = !DIDerivedType(tag: DW_TAG_member, name: "t_startsingle", scope: !1042, file: !121, line: 1222, baseType: !411, size: 128, align: 64, offset: 1216)
!1064 = !DIDerivedType(tag: DW_TAG_member, name: "t_startop", scope: !1042, file: !121, line: 1223, baseType: !411, size: 128, align: 64, offset: 1344)
!1065 = !DIDerivedType(tag: DW_TAG_member, name: "t_acceptdata", scope: !1042, file: !121, line: 1224, baseType: !411, size: 128, align: 64, offset: 1472)
!1066 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_start", scope: !1042, file: !121, line: 1227, baseType: !411, size: 128, align: 64, offset: 1600)
!1067 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_size", scope: !1042, file: !121, line: 1228, baseType: !458, size: 64, align: 64, offset: 1728)
!1068 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_start", scope: !1042, file: !121, line: 1230, baseType: !411, size: 128, align: 64, offset: 1792)
!1069 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_size", scope: !1042, file: !121, line: 1231, baseType: !458, size: 64, align: 64, offset: 1920)
!1070 = !DIDerivedType(tag: DW_TAG_member, name: "speeder", scope: !1042, file: !121, line: 1235, baseType: !1071, size: 384, align: 64, offset: 1984)
!1071 = !DICompositeType(tag: DW_TAG_array_type, baseType: !458, size: 384, align: 64, elements: !1072)
!1072 = !{!1073}
!1073 = !DISubrange(count: 6)
!1074 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_time", scope: !1042, file: !121, line: 1236, baseType: !1075, size: 768, align: 64, offset: 2368)
!1075 = !DICompositeType(tag: DW_TAG_array_type, baseType: !411, size: 768, align: 64, elements: !1072)
!1076 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_c", scope: !1042, file: !121, line: 1237, baseType: !316, size: 32, align: 32, offset: 3136)
!1077 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !257, file: !121, line: 1836, baseType: !1078, size: 136640, align: 64, offset: 20864)
!1078 = !DICompositeType(tag: DW_TAG_structure_type, name: "UrlState", file: !121, line: 1310, size: 136640, align: 64, elements: !1079)
!1079 = !{!1080, !1082, !1083, !1084, !1085, !1086, !1087, !1088, !1092, !1093, !1094, !1095, !1096, !1109, !1110, !1111, !1120, !1121, !1122, !1123, !1127, !1128, !1140, !1141, !1150, !1151, !1152, !1153, !1154, !1155, !1156, !1157, !1158, !1159, !1160, !1161, !1162, !1163, !1164, !1165, !1166, !1167, !1168, !1169, !1170, !1171, !1172, !1173, !1174, !1175, !1176, !1177, !1178, !1179, !1180}
!1080 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !1078, file: !121, line: 1313, baseType: !1081, size: 64, align: 64)
!1081 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !425, size: 64, align: 64)
!1082 = !DIDerivedType(tag: DW_TAG_member, name: "multi_owned_by_easy", scope: !1078, file: !121, line: 1318, baseType: !423, size: 8, align: 8, offset: 64)
!1083 = !DIDerivedType(tag: DW_TAG_member, name: "keeps_speed", scope: !1078, file: !121, line: 1321, baseType: !411, size: 128, align: 64, offset: 128)
!1084 = !DIDerivedType(tag: DW_TAG_member, name: "lastconnect", scope: !1078, file: !121, line: 1323, baseType: !262, size: 64, align: 64, offset: 256)
!1085 = !DIDerivedType(tag: DW_TAG_member, name: "headerbuff", scope: !1078, file: !121, line: 1325, baseType: !479, size: 64, align: 64, offset: 320)
!1086 = !DIDerivedType(tag: DW_TAG_member, name: "headersize", scope: !1078, file: !121, line: 1326, baseType: !347, size: 64, align: 64, offset: 384)
!1087 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !1078, file: !121, line: 1328, baseType: !479, size: 64, align: 64, offset: 448)
!1088 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuffer", scope: !1078, file: !121, line: 1329, baseType: !1089, size: 131080, align: 8, offset: 512)
!1089 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 131080, align: 8, elements: !1090)
!1090 = !{!1091}
!1091 = !DISubrange(count: 16385)
!1092 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1078, file: !121, line: 1330, baseType: !458, size: 64, align: 64, offset: 131648)
!1093 = !DIDerivedType(tag: DW_TAG_member, name: "this_is_a_follow", scope: !1078, file: !121, line: 1332, baseType: !423, size: 8, align: 8, offset: 131712)
!1094 = !DIDerivedType(tag: DW_TAG_member, name: "first_host", scope: !1078, file: !121, line: 1334, baseType: !479, size: 64, align: 64, offset: 131776)
!1095 = !DIDerivedType(tag: DW_TAG_member, name: "first_remote_port", scope: !1078, file: !121, line: 1340, baseType: !316, size: 32, align: 32, offset: 131840)
!1096 = !DIDerivedType(tag: DW_TAG_member, name: "session", scope: !1078, file: !121, line: 1341, baseType: !1097, size: 64, align: 64, offset: 131904)
!1097 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1098, size: 64, align: 64)
!1098 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_ssl_session", file: !121, line: 397, size: 1088, align: 64, elements: !1099)
!1099 = !{!1100, !1101, !1102, !1103, !1104, !1105, !1106, !1107, !1108}
!1100 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1098, file: !121, line: 398, baseType: !479, size: 64, align: 64)
!1101 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !1098, file: !121, line: 399, baseType: !479, size: 64, align: 64, offset: 64)
!1102 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !1098, file: !121, line: 400, baseType: !851, size: 64, align: 64, offset: 128)
!1103 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !1098, file: !121, line: 401, baseType: !311, size: 64, align: 64, offset: 192)
!1104 = !DIDerivedType(tag: DW_TAG_member, name: "idsize", scope: !1098, file: !121, line: 402, baseType: !347, size: 64, align: 64, offset: 256)
!1105 = !DIDerivedType(tag: DW_TAG_member, name: "age", scope: !1098, file: !121, line: 403, baseType: !379, size: 64, align: 64, offset: 320)
!1106 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !1098, file: !121, line: 404, baseType: !316, size: 32, align: 32, offset: 384)
!1107 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !1098, file: !121, line: 405, baseType: !316, size: 32, align: 32, offset: 416)
!1108 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !1098, file: !121, line: 406, baseType: !788, size: 640, align: 64, offset: 448)
!1109 = !DIDerivedType(tag: DW_TAG_member, name: "sessionage", scope: !1078, file: !121, line: 1342, baseType: !379, size: 64, align: 64, offset: 131968)
!1110 = !DIDerivedType(tag: DW_TAG_member, name: "tempcount", scope: !1078, file: !121, line: 1343, baseType: !683, size: 32, align: 32, offset: 132032)
!1111 = !DIDerivedType(tag: DW_TAG_member, name: "tempwrite", scope: !1078, file: !121, line: 1344, baseType: !1112, size: 576, align: 64, offset: 132096)
!1112 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1113, size: 576, align: 64, elements: !1118)
!1113 = !DICompositeType(tag: DW_TAG_structure_type, name: "tempbuf", file: !121, line: 1302, size: 192, align: 64, elements: !1114)
!1114 = !{!1115, !1116, !1117}
!1115 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !1113, file: !121, line: 1303, baseType: !479, size: 64, align: 64)
!1116 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !1113, file: !121, line: 1305, baseType: !347, size: 64, align: 64, offset: 64)
!1117 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !1113, file: !121, line: 1306, baseType: !316, size: 32, align: 32, offset: 128)
!1118 = !{!1119}
!1119 = !DISubrange(count: 3)
!1120 = !DIDerivedType(tag: DW_TAG_member, name: "scratch", scope: !1078, file: !121, line: 1345, baseType: !479, size: 64, align: 64, offset: 132672)
!1121 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuf", scope: !1078, file: !121, line: 1346, baseType: !423, size: 8, align: 8, offset: 132736)
!1122 = !DIDerivedType(tag: DW_TAG_member, name: "os_errno", scope: !1078, file: !121, line: 1349, baseType: !316, size: 32, align: 32, offset: 132768)
!1123 = !DIDerivedType(tag: DW_TAG_member, name: "prev_signal", scope: !1078, file: !121, line: 1352, baseType: !1124, size: 64, align: 64, offset: 132800)
!1124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1125, size: 64, align: 64)
!1125 = !DISubroutineType(types: !1126)
!1126 = !{null, !316}
!1127 = !DIDerivedType(tag: DW_TAG_member, name: "allow_port", scope: !1078, file: !121, line: 1354, baseType: !423, size: 8, align: 8, offset: 132864)
!1128 = !DIDerivedType(tag: DW_TAG_member, name: "digest", scope: !1078, file: !121, line: 1356, baseType: !1129, size: 512, align: 64, offset: 132928)
!1129 = !DICompositeType(tag: DW_TAG_structure_type, name: "digestdata", file: !121, line: 410, size: 512, align: 64, elements: !1130)
!1130 = !{!1131, !1132, !1133, !1134, !1135, !1136, !1137, !1138, !1139}
!1131 = !DIDerivedType(tag: DW_TAG_member, name: "nonce", scope: !1129, file: !121, line: 416, baseType: !479, size: 64, align: 64)
!1132 = !DIDerivedType(tag: DW_TAG_member, name: "cnonce", scope: !1129, file: !121, line: 417, baseType: !479, size: 64, align: 64, offset: 64)
!1133 = !DIDerivedType(tag: DW_TAG_member, name: "realm", scope: !1129, file: !121, line: 418, baseType: !479, size: 64, align: 64, offset: 128)
!1134 = !DIDerivedType(tag: DW_TAG_member, name: "algo", scope: !1129, file: !121, line: 419, baseType: !316, size: 32, align: 32, offset: 192)
!1135 = !DIDerivedType(tag: DW_TAG_member, name: "stale", scope: !1129, file: !121, line: 420, baseType: !423, size: 8, align: 8, offset: 224)
!1136 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !1129, file: !121, line: 421, baseType: !479, size: 64, align: 64, offset: 256)
!1137 = !DIDerivedType(tag: DW_TAG_member, name: "qop", scope: !1129, file: !121, line: 422, baseType: !479, size: 64, align: 64, offset: 320)
!1138 = !DIDerivedType(tag: DW_TAG_member, name: "algorithm", scope: !1129, file: !121, line: 423, baseType: !479, size: 64, align: 64, offset: 384)
!1139 = !DIDerivedType(tag: DW_TAG_member, name: "nc", scope: !1129, file: !121, line: 424, baseType: !316, size: 32, align: 32, offset: 448)
!1140 = !DIDerivedType(tag: DW_TAG_member, name: "proxydigest", scope: !1078, file: !121, line: 1357, baseType: !1129, size: 512, align: 64, offset: 133440)
!1141 = !DIDerivedType(tag: DW_TAG_member, name: "authhost", scope: !1078, file: !121, line: 1364, baseType: !1142, size: 256, align: 64, offset: 133952)
!1142 = !DICompositeType(tag: DW_TAG_structure_type, name: "auth", file: !121, line: 1278, size: 256, align: 64, elements: !1143)
!1143 = !{!1144, !1145, !1146, !1147, !1148, !1149}
!1144 = !DIDerivedType(tag: DW_TAG_member, name: "want", scope: !1142, file: !121, line: 1279, baseType: !349, size: 64, align: 64)
!1145 = !DIDerivedType(tag: DW_TAG_member, name: "picked", scope: !1142, file: !121, line: 1281, baseType: !349, size: 64, align: 64, offset: 64)
!1146 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !1142, file: !121, line: 1282, baseType: !349, size: 64, align: 64, offset: 128)
!1147 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1142, file: !121, line: 1284, baseType: !423, size: 8, align: 8, offset: 192)
!1148 = !DIDerivedType(tag: DW_TAG_member, name: "multipass", scope: !1142, file: !121, line: 1286, baseType: !423, size: 8, align: 8, offset: 200)
!1149 = !DIDerivedType(tag: DW_TAG_member, name: "iestyle", scope: !1142, file: !121, line: 1288, baseType: !423, size: 8, align: 8, offset: 208)
!1150 = !DIDerivedType(tag: DW_TAG_member, name: "authproxy", scope: !1078, file: !121, line: 1365, baseType: !1142, size: 256, align: 64, offset: 134208)
!1151 = !DIDerivedType(tag: DW_TAG_member, name: "authproblem", scope: !1078, file: !121, line: 1367, baseType: !423, size: 8, align: 8, offset: 134464)
!1152 = !DIDerivedType(tag: DW_TAG_member, name: "resolver", scope: !1078, file: !121, line: 1369, baseType: !311, size: 64, align: 64, offset: 134528)
!1153 = !DIDerivedType(tag: DW_TAG_member, name: "expiretime", scope: !1078, file: !121, line: 1375, baseType: !411, size: 128, align: 64, offset: 134592)
!1154 = !DIDerivedType(tag: DW_TAG_member, name: "timenode", scope: !1078, file: !121, line: 1376, baseType: !403, size: 448, align: 64, offset: 134720)
!1155 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutlist", scope: !1078, file: !121, line: 1377, baseType: !330, size: 256, align: 64, offset: 135168)
!1156 = !DIDerivedType(tag: DW_TAG_member, name: "most_recent_ftp_entrypath", scope: !1078, file: !121, line: 1380, baseType: !479, size: 64, align: 64, offset: 135424)
!1157 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_trying_alternative", scope: !1078, file: !121, line: 1383, baseType: !423, size: 8, align: 8, offset: 135488)
!1158 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1078, file: !121, line: 1385, baseType: !316, size: 32, align: 32, offset: 135520)
!1159 = !DIDerivedType(tag: DW_TAG_member, name: "expect100header", scope: !1078, file: !121, line: 1387, baseType: !423, size: 8, align: 8, offset: 135552)
!1160 = !DIDerivedType(tag: DW_TAG_member, name: "pipe_broke", scope: !1078, file: !121, line: 1389, baseType: !423, size: 8, align: 8, offset: 135560)
!1161 = !DIDerivedType(tag: DW_TAG_member, name: "prev_block_had_trailing_cr", scope: !1078, file: !121, line: 1397, baseType: !423, size: 8, align: 8, offset: 135568)
!1162 = !DIDerivedType(tag: DW_TAG_member, name: "crlf_conversions", scope: !1078, file: !121, line: 1399, baseType: !458, size: 64, align: 64, offset: 135616)
!1163 = !DIDerivedType(tag: DW_TAG_member, name: "pathbuffer", scope: !1078, file: !121, line: 1401, baseType: !479, size: 64, align: 64, offset: 135680)
!1164 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1078, file: !121, line: 1402, baseType: !479, size: 64, align: 64, offset: 135744)
!1165 = !DIDerivedType(tag: DW_TAG_member, name: "slash_removed", scope: !1078, file: !121, line: 1404, baseType: !423, size: 8, align: 8, offset: 135808)
!1166 = !DIDerivedType(tag: DW_TAG_member, name: "use_range", scope: !1078, file: !121, line: 1406, baseType: !423, size: 8, align: 8, offset: 135816)
!1167 = !DIDerivedType(tag: DW_TAG_member, name: "rangestringalloc", scope: !1078, file: !121, line: 1407, baseType: !423, size: 8, align: 8, offset: 135824)
!1168 = !DIDerivedType(tag: DW_TAG_member, name: "range", scope: !1078, file: !121, line: 1409, baseType: !479, size: 64, align: 64, offset: 135872)
!1169 = !DIDerivedType(tag: DW_TAG_member, name: "resume_from", scope: !1078, file: !121, line: 1411, baseType: !458, size: 64, align: 64, offset: 135936)
!1170 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_client_CSeq", scope: !1078, file: !121, line: 1414, baseType: !379, size: 64, align: 64, offset: 136000)
!1171 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_server_CSeq", scope: !1078, file: !121, line: 1415, baseType: !379, size: 64, align: 64, offset: 136064)
!1172 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_CSeq_recv", scope: !1078, file: !121, line: 1416, baseType: !379, size: 64, align: 64, offset: 136128)
!1173 = !DIDerivedType(tag: DW_TAG_member, name: "infilesize", scope: !1078, file: !121, line: 1418, baseType: !458, size: 64, align: 64, offset: 136192)
!1174 = !DIDerivedType(tag: DW_TAG_member, name: "drain", scope: !1078, file: !121, line: 1421, baseType: !347, size: 64, align: 64, offset: 136256)
!1175 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1078, file: !121, line: 1424, baseType: !423, size: 8, align: 8, offset: 136320)
!1176 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func", scope: !1078, file: !121, line: 1428, baseType: !617, size: 64, align: 64, offset: 136384)
!1177 = !DIDerivedType(tag: DW_TAG_member, name: "in", scope: !1078, file: !121, line: 1429, baseType: !311, size: 64, align: 64, offset: 136448)
!1178 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !1078, file: !121, line: 1431, baseType: !256, size: 64, align: 64, offset: 136512)
!1179 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !1078, file: !121, line: 1432, baseType: !423, size: 8, align: 8, offset: 136576)
!1180 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !1078, file: !121, line: 1433, baseType: !316, size: 32, align: 32, offset: 136608)
!1181 = !DIDerivedType(tag: DW_TAG_member, name: "wildcard", scope: !257, file: !121, line: 1838, baseType: !1182, size: 640, align: 64, offset: 157504)
!1182 = !DICompositeType(tag: DW_TAG_structure_type, name: "WildcardData", file: !1183, line: 46, size: 640, align: 64, elements: !1184)
!1183 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/wildcard.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1184 = !{!1185, !1197, !1198, !1199, !1200, !1201, !1203}
!1185 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1182, file: !1183, line: 47, baseType: !1186, size: 32, align: 32)
!1186 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_states", file: !1183, line: 41, baseType: !1187)
!1187 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1183, line: 30, size: 32, align: 32, elements: !1188)
!1188 = !{!1189, !1190, !1191, !1192, !1193, !1194, !1195, !1196}
!1189 = !DIEnumerator(name: "CURLWC_CLEAR", value: 0)
!1190 = !DIEnumerator(name: "CURLWC_INIT", value: 1)
!1191 = !DIEnumerator(name: "CURLWC_MATCHING", value: 2)
!1192 = !DIEnumerator(name: "CURLWC_DOWNLOADING", value: 3)
!1193 = !DIEnumerator(name: "CURLWC_CLEAN", value: 4)
!1194 = !DIEnumerator(name: "CURLWC_SKIP", value: 5)
!1195 = !DIEnumerator(name: "CURLWC_ERROR", value: 6)
!1196 = !DIEnumerator(name: "CURLWC_DONE", value: 7)
!1197 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1182, file: !1183, line: 48, baseType: !479, size: 64, align: 64, offset: 64)
!1198 = !DIDerivedType(tag: DW_TAG_member, name: "pattern", scope: !1182, file: !1183, line: 49, baseType: !479, size: 64, align: 64, offset: 128)
!1199 = !DIDerivedType(tag: DW_TAG_member, name: "filelist", scope: !1182, file: !1183, line: 50, baseType: !330, size: 256, align: 64, offset: 192)
!1200 = !DIDerivedType(tag: DW_TAG_member, name: "tmp", scope: !1182, file: !1183, line: 51, baseType: !311, size: 64, align: 64, offset: 448)
!1201 = !DIDerivedType(tag: DW_TAG_member, name: "tmp_dtor", scope: !1182, file: !1183, line: 52, baseType: !1202, size: 64, align: 64, offset: 512)
!1202 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_tmp_dtor", file: !1183, line: 43, baseType: !362)
!1203 = !DIDerivedType(tag: DW_TAG_member, name: "customptr", scope: !1182, file: !1183, line: 53, baseType: !311, size: 64, align: 64, offset: 576)
!1204 = !DIDerivedType(tag: DW_TAG_member, name: "info", scope: !257, file: !121, line: 1839, baseType: !1205, size: 1856, align: 64, offset: 158144)
!1205 = !DICompositeType(tag: DW_TAG_structure_type, name: "PureInfo", file: !121, line: 1154, size: 1856, align: 64, elements: !1206)
!1206 = !{!1207, !1208, !1209, !1210, !1211, !1212, !1213, !1214, !1215, !1216, !1217, !1218, !1219, !1223, !1224, !1225, !1226, !1227, !1228}
!1207 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !1205, file: !121, line: 1155, baseType: !316, size: 32, align: 32)
!1208 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxycode", scope: !1205, file: !121, line: 1156, baseType: !316, size: 32, align: 32, offset: 32)
!1209 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1205, file: !121, line: 1157, baseType: !316, size: 32, align: 32, offset: 64)
!1210 = !DIDerivedType(tag: DW_TAG_member, name: "filetime", scope: !1205, file: !121, line: 1158, baseType: !379, size: 64, align: 64, offset: 128)
!1211 = !DIDerivedType(tag: DW_TAG_member, name: "timecond", scope: !1205, file: !121, line: 1162, baseType: !423, size: 8, align: 8, offset: 192)
!1212 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !1205, file: !121, line: 1164, baseType: !379, size: 64, align: 64, offset: 256)
!1213 = !DIDerivedType(tag: DW_TAG_member, name: "request_size", scope: !1205, file: !121, line: 1165, baseType: !379, size: 64, align: 64, offset: 320)
!1214 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauthavail", scope: !1205, file: !121, line: 1166, baseType: !349, size: 64, align: 64, offset: 384)
!1215 = !DIDerivedType(tag: DW_TAG_member, name: "httpauthavail", scope: !1205, file: !121, line: 1167, baseType: !349, size: 64, align: 64, offset: 448)
!1216 = !DIDerivedType(tag: DW_TAG_member, name: "numconnects", scope: !1205, file: !121, line: 1168, baseType: !379, size: 64, align: 64, offset: 512)
!1217 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !1205, file: !121, line: 1169, baseType: !479, size: 64, align: 64, offset: 576)
!1218 = !DIDerivedType(tag: DW_TAG_member, name: "wouldredirect", scope: !1205, file: !121, line: 1170, baseType: !479, size: 64, align: 64, offset: 640)
!1219 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_ip", scope: !1205, file: !121, line: 1180, baseType: !1220, size: 368, align: 8, offset: 704)
!1220 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 368, align: 8, elements: !1221)
!1221 = !{!1222}
!1222 = !DISubrange(count: 46)
!1223 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_port", scope: !1205, file: !121, line: 1181, baseType: !379, size: 64, align: 64, offset: 1088)
!1224 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_ip", scope: !1205, file: !121, line: 1183, baseType: !1220, size: 368, align: 8, offset: 1152)
!1225 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_port", scope: !1205, file: !121, line: 1184, baseType: !379, size: 64, align: 64, offset: 1536)
!1226 = !DIDerivedType(tag: DW_TAG_member, name: "conn_scheme", scope: !1205, file: !121, line: 1186, baseType: !851, size: 64, align: 64, offset: 1600)
!1227 = !DIDerivedType(tag: DW_TAG_member, name: "conn_protocol", scope: !1205, file: !121, line: 1187, baseType: !683, size: 32, align: 32, offset: 1664)
!1228 = !DIDerivedType(tag: DW_TAG_member, name: "certs", scope: !1205, file: !121, line: 1189, baseType: !1229, size: 128, align: 64, offset: 1728)
!1229 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_certinfo", file: !15, line: 2214, size: 128, align: 64, elements: !1230)
!1230 = !{!1231, !1232}
!1231 = !DIDerivedType(tag: DW_TAG_member, name: "num_of_certs", scope: !1229, file: !15, line: 2215, baseType: !316, size: 32, align: 32)
!1232 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !1229, file: !15, line: 2216, baseType: !1233, size: 64, align: 64, offset: 64)
!1233 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !725, size: 64, align: 64)
!1234 = !DIDerivedType(tag: DW_TAG_member, name: "tsi", scope: !257, file: !121, line: 1840, baseType: !1235, size: 128, align: 64, offset: 160000)
!1235 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_tlssessioninfo", file: !15, line: 2245, size: 128, align: 64, elements: !1236)
!1236 = !{!1237, !1253}
!1237 = !DIDerivedType(tag: DW_TAG_member, name: "backend", scope: !1235, file: !15, line: 2246, baseType: !1238, size: 32, align: 32)
!1238 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sslbackend", file: !15, line: 2235, baseType: !1239)
!1239 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 2222, size: 32, align: 32, elements: !1240)
!1240 = !{!1241, !1242, !1243, !1244, !1245, !1246, !1247, !1248, !1249, !1250, !1251, !1252}
!1241 = !DIEnumerator(name: "CURLSSLBACKEND_NONE", value: 0)
!1242 = !DIEnumerator(name: "CURLSSLBACKEND_OPENSSL", value: 1)
!1243 = !DIEnumerator(name: "CURLSSLBACKEND_GNUTLS", value: 2)
!1244 = !DIEnumerator(name: "CURLSSLBACKEND_NSS", value: 3)
!1245 = !DIEnumerator(name: "CURLSSLBACKEND_OBSOLETE4", value: 4)
!1246 = !DIEnumerator(name: "CURLSSLBACKEND_GSKIT", value: 5)
!1247 = !DIEnumerator(name: "CURLSSLBACKEND_POLARSSL", value: 6)
!1248 = !DIEnumerator(name: "CURLSSLBACKEND_CYASSL", value: 7)
!1249 = !DIEnumerator(name: "CURLSSLBACKEND_SCHANNEL", value: 8)
!1250 = !DIEnumerator(name: "CURLSSLBACKEND_DARWINSSL", value: 9)
!1251 = !DIEnumerator(name: "CURLSSLBACKEND_AXTLS", value: 10)
!1252 = !DIEnumerator(name: "CURLSSLBACKEND_MBEDTLS", value: 11)
!1253 = !DIDerivedType(tag: DW_TAG_member, name: "internals", scope: !1235, file: !15, line: 2247, baseType: !311, size: 64, align: 64, offset: 64)
!1254 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !257, file: !121, line: 1847, baseType: !683, size: 32, align: 32, offset: 160128)
!1255 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !253, file: !121, line: 904, baseType: !1256, size: 384, align: 64, offset: 64)
!1256 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_chunker", file: !4, line: 82, size: 384, align: 64, elements: !1257)
!1257 = !{!1258, !1262, !1263, !1265, !1266}
!1258 = !DIDerivedType(tag: DW_TAG_member, name: "hexbuffer", scope: !1256, file: !4, line: 83, baseType: !1259, size: 136, align: 8)
!1259 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 136, align: 8, elements: !1260)
!1260 = !{!1261}
!1261 = !DISubrange(count: 17)
!1262 = !DIDerivedType(tag: DW_TAG_member, name: "hexindex", scope: !1256, file: !4, line: 84, baseType: !316, size: 32, align: 32, offset: 160)
!1263 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1256, file: !4, line: 85, baseType: !1264, size: 32, align: 32, offset: 192)
!1264 = !DIDerivedType(tag: DW_TAG_typedef, name: "ChunkyState", file: !4, line: 66, baseType: !3)
!1265 = !DIDerivedType(tag: DW_TAG_member, name: "datasize", scope: !1256, file: !4, line: 86, baseType: !458, size: 64, align: 64, offset: 256)
!1266 = !DIDerivedType(tag: DW_TAG_member, name: "dataleft", scope: !1256, file: !4, line: 87, baseType: !347, size: 64, align: 64, offset: 320)
!1267 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !253, file: !121, line: 906, baseType: !697, size: 64, align: 64, offset: 448)
!1268 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !253, file: !121, line: 907, baseType: !311, size: 64, align: 64, offset: 512)
!1269 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !253, file: !121, line: 909, baseType: !423, size: 8, align: 8, offset: 576)
!1270 = !DIDerivedType(tag: DW_TAG_member, name: "connection_id", scope: !253, file: !121, line: 915, baseType: !379, size: 64, align: 64, offset: 640)
!1271 = !DIDerivedType(tag: DW_TAG_member, name: "dns_entry", scope: !253, file: !121, line: 922, baseType: !1272, size: 64, align: 64, offset: 704)
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
!1282 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !1280, file: !1279, line: 52, baseType: !316, size: 32, align: 32)
!1283 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !1280, file: !1279, line: 53, baseType: !316, size: 32, align: 32, offset: 32)
!1284 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !1280, file: !1279, line: 54, baseType: !316, size: 32, align: 32, offset: 64)
!1285 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !1280, file: !1279, line: 55, baseType: !316, size: 32, align: 32, offset: 96)
!1286 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !1280, file: !1279, line: 56, baseType: !1287, size: 32, align: 32, offset: 128)
!1287 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socklen_t", file: !459, line: 186, baseType: !1288)
!1288 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !686, line: 33, baseType: !1289)
!1289 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !416, line: 189, baseType: !683)
!1290 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !1280, file: !1279, line: 57, baseType: !479, size: 64, align: 64, offset: 192)
!1291 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !1280, file: !1279, line: 58, baseType: !1292, size: 64, align: 64, offset: 256)
!1292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !685, size: 64, align: 64)
!1293 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !1280, file: !1279, line: 59, baseType: !1294, size: 64, align: 64, offset: 320)
!1294 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1280, size: 64, align: 64)
!1295 = !DIDerivedType(tag: DW_TAG_member, name: "timestamp", scope: !1273, file: !1274, line: 69, baseType: !506, size: 64, align: 64, offset: 64)
!1296 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !1273, file: !1274, line: 71, baseType: !379, size: 64, align: 64, offset: 128)
!1297 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr", scope: !253, file: !121, line: 927, baseType: !1277, size: 64, align: 64, offset: 768)
!1298 = !DIDerivedType(tag: DW_TAG_member, name: "tempaddr", scope: !253, file: !121, line: 928, baseType: !1299, size: 128, align: 64, offset: 832)
!1299 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1277, size: 128, align: 64, elements: !1300)
!1300 = !{!1301}
!1301 = !DISubrange(count: 2)
!1302 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr_str", scope: !253, file: !121, line: 933, baseType: !1220, size: 368, align: 8, offset: 960)
!1303 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !253, file: !121, line: 935, baseType: !683, size: 32, align: 32, offset: 1344)
!1304 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !253, file: !121, line: 937, baseType: !316, size: 32, align: 32, offset: 1376)
!1305 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !253, file: !121, line: 939, baseType: !1306, size: 256, align: 64, offset: 1408)
!1306 = !DICompositeType(tag: DW_TAG_structure_type, name: "hostname", file: !121, line: 581, size: 256, align: 64, elements: !1307)
!1307 = !{!1308, !1309, !1310, !1311}
!1308 = !DIDerivedType(tag: DW_TAG_member, name: "rawalloc", scope: !1306, file: !121, line: 582, baseType: !479, size: 64, align: 64)
!1309 = !DIDerivedType(tag: DW_TAG_member, name: "encalloc", scope: !1306, file: !121, line: 583, baseType: !479, size: 64, align: 64, offset: 64)
!1310 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1306, file: !121, line: 584, baseType: !479, size: 64, align: 64, offset: 128)
!1311 = !DIDerivedType(tag: DW_TAG_member, name: "dispname", scope: !1306, file: !121, line: 585, baseType: !851, size: 64, align: 64, offset: 192)
!1312 = !DIDerivedType(tag: DW_TAG_member, name: "secondaryhostname", scope: !253, file: !121, line: 940, baseType: !479, size: 64, align: 64, offset: 1664)
!1313 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !253, file: !121, line: 941, baseType: !1306, size: 256, align: 64, offset: 1728)
!1314 = !DIDerivedType(tag: DW_TAG_member, name: "socks_proxy", scope: !253, file: !121, line: 944, baseType: !1315, size: 512, align: 64, offset: 1984)
!1315 = !DICompositeType(tag: DW_TAG_structure_type, name: "proxy_info", file: !121, line: 883, size: 512, align: 64, elements: !1316)
!1316 = !{!1317, !1318, !1319, !1320, !1321}
!1317 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1315, file: !121, line: 884, baseType: !1306, size: 256, align: 64)
!1318 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !1315, file: !121, line: 885, baseType: !379, size: 64, align: 64, offset: 256)
!1319 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !1315, file: !121, line: 886, baseType: !826, size: 32, align: 32, offset: 320)
!1320 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1315, file: !121, line: 887, baseType: !479, size: 64, align: 64, offset: 384)
!1321 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !1315, file: !121, line: 888, baseType: !479, size: 64, align: 64, offset: 448)
!1322 = !DIDerivedType(tag: DW_TAG_member, name: "http_proxy", scope: !253, file: !121, line: 945, baseType: !1315, size: 512, align: 64, offset: 2496)
!1323 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !253, file: !121, line: 947, baseType: !379, size: 64, align: 64, offset: 3008)
!1324 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !253, file: !121, line: 948, baseType: !316, size: 32, align: 32, offset: 3072)
!1325 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !253, file: !121, line: 949, baseType: !316, size: 32, align: 32, offset: 3104)
!1326 = !DIDerivedType(tag: DW_TAG_member, name: "secondary_port", scope: !253, file: !121, line: 951, baseType: !564, size: 16, align: 16, offset: 3136)
!1327 = !DIDerivedType(tag: DW_TAG_member, name: "primary_ip", scope: !253, file: !121, line: 961, baseType: !1220, size: 368, align: 8, offset: 3152)
!1328 = !DIDerivedType(tag: DW_TAG_member, name: "primary_port", scope: !253, file: !121, line: 962, baseType: !379, size: 64, align: 64, offset: 3520)
!1329 = !DIDerivedType(tag: DW_TAG_member, name: "local_ip", scope: !253, file: !121, line: 968, baseType: !1220, size: 368, align: 8, offset: 3584)
!1330 = !DIDerivedType(tag: DW_TAG_member, name: "local_port", scope: !253, file: !121, line: 969, baseType: !379, size: 64, align: 64, offset: 3968)
!1331 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !253, file: !121, line: 971, baseType: !479, size: 64, align: 64, offset: 4032)
!1332 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !253, file: !121, line: 972, baseType: !479, size: 64, align: 64, offset: 4096)
!1333 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !253, file: !121, line: 973, baseType: !479, size: 64, align: 64, offset: 4160)
!1334 = !DIDerivedType(tag: DW_TAG_member, name: "oauth_bearer", scope: !253, file: !121, line: 975, baseType: !479, size: 64, align: 64, offset: 4224)
!1335 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !253, file: !121, line: 977, baseType: !316, size: 32, align: 32, offset: 4288)
!1336 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !253, file: !121, line: 978, baseType: !316, size: 32, align: 32, offset: 4320)
!1337 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !253, file: !121, line: 980, baseType: !411, size: 128, align: 64, offset: 4352)
!1338 = !DIDerivedType(tag: DW_TAG_member, name: "created", scope: !253, file: !121, line: 981, baseType: !411, size: 128, align: 64, offset: 4480)
!1339 = !DIDerivedType(tag: DW_TAG_member, name: "sock", scope: !253, file: !121, line: 982, baseType: !1340, size: 64, align: 32, offset: 4608)
!1340 = !DICompositeType(tag: DW_TAG_array_type, baseType: !315, size: 64, align: 32, elements: !1300)
!1341 = !DIDerivedType(tag: DW_TAG_member, name: "tempsock", scope: !253, file: !121, line: 984, baseType: !1340, size: 64, align: 32, offset: 4672)
!1342 = !DIDerivedType(tag: DW_TAG_member, name: "sock_accepted", scope: !253, file: !121, line: 985, baseType: !1343, size: 16, align: 8, offset: 4736)
!1343 = !DICompositeType(tag: DW_TAG_array_type, baseType: !423, size: 16, align: 8, elements: !1300)
!1344 = !DIDerivedType(tag: DW_TAG_member, name: "recv", scope: !253, file: !121, line: 987, baseType: !1345, size: 128, align: 64, offset: 4800)
!1345 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1346, size: 128, align: 64, elements: !1300)
!1346 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1347, size: 64, align: 64)
!1347 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_recv", file: !121, line: 863, baseType: !1348)
!1348 = !DISubroutineType(types: !1349)
!1349 = !{!519, !262, !316, !479, !347, !1350}
!1350 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !289, size: 64, align: 64)
!1351 = !DIDerivedType(tag: DW_TAG_member, name: "send", scope: !253, file: !121, line: 988, baseType: !1352, size: 128, align: 64, offset: 4928)
!1352 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1353, size: 128, align: 64, elements: !1300)
!1353 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1354, size: 64, align: 64)
!1354 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_send", file: !121, line: 856, baseType: !1355)
!1355 = !DISubroutineType(types: !1356)
!1356 = !{!519, !262, !316, !970, !347, !1350}
!1357 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !253, file: !121, line: 993, baseType: !1358, size: 192, align: 32, offset: 5056)
!1358 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1359, size: 192, align: 32, elements: !1300)
!1359 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_connect_data", file: !121, line: 274, size: 96, align: 32, elements: !1360)
!1360 = !{!1361, !1362, !1364}
!1361 = !DIDerivedType(tag: DW_TAG_member, name: "use", scope: !1359, file: !121, line: 278, baseType: !423, size: 8, align: 8)
!1362 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1359, file: !121, line: 279, baseType: !1363, size: 32, align: 32, offset: 32)
!1363 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connection_state", file: !121, line: 271, baseType: !120)
!1364 = !DIDerivedType(tag: DW_TAG_member, name: "connecting_state", scope: !1359, file: !121, line: 280, baseType: !1365, size: 32, align: 32, offset: 64)
!1365 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connect_state", file: !121, line: 265, baseType: !126)
!1366 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !253, file: !121, line: 994, baseType: !1358, size: 192, align: 32, offset: 5248)
!1367 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !253, file: !121, line: 995, baseType: !788, size: 640, align: 64, offset: 5440)
!1368 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_config", scope: !253, file: !121, line: 996, baseType: !788, size: 640, align: 64, offset: 6080)
!1369 = !DIDerivedType(tag: DW_TAG_member, name: "tls_upgraded", scope: !253, file: !121, line: 997, baseType: !423, size: 8, align: 8, offset: 6720)
!1370 = !DIDerivedType(tag: DW_TAG_member, name: "bits", scope: !253, file: !121, line: 999, baseType: !1371, size: 280, align: 8, offset: 6728)
!1371 = !DICompositeType(tag: DW_TAG_structure_type, name: "ConnectBits", file: !121, line: 514, size: 280, align: 8, elements: !1372)
!1372 = !{!1373, !1374, !1375, !1376, !1377, !1378, !1379, !1380, !1381, !1382, !1383, !1384, !1385, !1386, !1387, !1388, !1389, !1390, !1391, !1392, !1393, !1394, !1395, !1396, !1397, !1398, !1399, !1400, !1401, !1402, !1403, !1404, !1405}
!1373 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !1371, file: !121, line: 516, baseType: !423, size: 8, align: 8)
!1374 = !DIDerivedType(tag: DW_TAG_member, name: "reuse", scope: !1371, file: !121, line: 517, baseType: !423, size: 8, align: 8, offset: 8)
!1375 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !1371, file: !121, line: 518, baseType: !423, size: 8, align: 8, offset: 16)
!1376 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !1371, file: !121, line: 520, baseType: !423, size: 8, align: 8, offset: 24)
!1377 = !DIDerivedType(tag: DW_TAG_member, name: "proxy", scope: !1371, file: !121, line: 522, baseType: !423, size: 8, align: 8, offset: 32)
!1378 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxy", scope: !1371, file: !121, line: 523, baseType: !423, size: 8, align: 8, offset: 40)
!1379 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy", scope: !1371, file: !121, line: 524, baseType: !423, size: 8, align: 8, offset: 48)
!1380 = !DIDerivedType(tag: DW_TAG_member, name: "user_passwd", scope: !1371, file: !121, line: 525, baseType: !423, size: 8, align: 8, offset: 56)
!1381 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_user_passwd", scope: !1371, file: !121, line: 526, baseType: !423, size: 8, align: 8, offset: 64)
!1382 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6_ip", scope: !1371, file: !121, line: 527, baseType: !423, size: 8, align: 8, offset: 72)
!1383 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6", scope: !1371, file: !121, line: 529, baseType: !423, size: 8, align: 8, offset: 80)
!1384 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1371, file: !121, line: 531, baseType: !423, size: 8, align: 8, offset: 88)
!1385 = !DIDerivedType(tag: DW_TAG_member, name: "tcpconnect", scope: !1371, file: !121, line: 533, baseType: !1343, size: 16, align: 8, offset: 96)
!1386 = !DIDerivedType(tag: DW_TAG_member, name: "protoconnstart", scope: !1371, file: !121, line: 535, baseType: !423, size: 8, align: 8, offset: 112)
!1387 = !DIDerivedType(tag: DW_TAG_member, name: "retry", scope: !1371, file: !121, line: 538, baseType: !423, size: 8, align: 8, offset: 120)
!1388 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_proxy", scope: !1371, file: !121, line: 540, baseType: !423, size: 8, align: 8, offset: 128)
!1389 = !DIDerivedType(tag: DW_TAG_member, name: "authneg", scope: !1371, file: !121, line: 544, baseType: !423, size: 8, align: 8, offset: 136)
!1390 = !DIDerivedType(tag: DW_TAG_member, name: "rewindaftersend", scope: !1371, file: !121, line: 548, baseType: !423, size: 8, align: 8, offset: 144)
!1391 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !1371, file: !121, line: 552, baseType: !423, size: 8, align: 8, offset: 152)
!1392 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !1371, file: !121, line: 556, baseType: !423, size: 8, align: 8, offset: 160)
!1393 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_data_ssl", scope: !1371, file: !121, line: 559, baseType: !423, size: 8, align: 8, offset: 168)
!1394 = !DIDerivedType(tag: DW_TAG_member, name: "netrc", scope: !1371, file: !121, line: 560, baseType: !423, size: 8, align: 8, offset: 176)
!1395 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd_in_url", scope: !1371, file: !121, line: 561, baseType: !423, size: 8, align: 8, offset: 184)
!1396 = !DIDerivedType(tag: DW_TAG_member, name: "stream_was_rewound", scope: !1371, file: !121, line: 562, baseType: !423, size: 8, align: 8, offset: 192)
!1397 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_connect_closed", scope: !1371, file: !121, line: 565, baseType: !423, size: 8, align: 8, offset: 200)
!1398 = !DIDerivedType(tag: DW_TAG_member, name: "bound", scope: !1371, file: !121, line: 568, baseType: !423, size: 8, align: 8, offset: 208)
!1399 = !DIDerivedType(tag: DW_TAG_member, name: "type_set", scope: !1371, file: !121, line: 570, baseType: !423, size: 8, align: 8, offset: 216)
!1400 = !DIDerivedType(tag: DW_TAG_member, name: "multiplex", scope: !1371, file: !121, line: 571, baseType: !423, size: 8, align: 8, offset: 224)
!1401 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !1371, file: !121, line: 573, baseType: !423, size: 8, align: 8, offset: 232)
!1402 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_npn", scope: !1371, file: !121, line: 574, baseType: !423, size: 8, align: 8, offset: 240)
!1403 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_alpn", scope: !1371, file: !121, line: 575, baseType: !423, size: 8, align: 8, offset: 248)
!1404 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_connected", scope: !1371, file: !121, line: 576, baseType: !1343, size: 16, align: 8, offset: 256)
!1405 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy_connecting", scope: !1371, file: !121, line: 578, baseType: !423, size: 8, align: 8, offset: 272)
!1406 = !DIDerivedType(tag: DW_TAG_member, name: "connecttime", scope: !253, file: !121, line: 1004, baseType: !411, size: 128, align: 64, offset: 7040)
!1407 = !DIDerivedType(tag: DW_TAG_member, name: "num_addr", scope: !253, file: !121, line: 1006, baseType: !316, size: 32, align: 32, offset: 7168)
!1408 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutms_per_addr", scope: !253, file: !121, line: 1007, baseType: !506, size: 64, align: 64, offset: 7232)
!1409 = !DIDerivedType(tag: DW_TAG_member, name: "handler", scope: !253, file: !121, line: 1010, baseType: !1410, size: 64, align: 64, offset: 7296)
!1410 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1411, size: 64, align: 64)
!1411 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1412)
!1412 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_handler", file: !121, line: 763, size: 1024, align: 64, elements: !1413)
!1413 = !{!1414, !1415, !1419, !1424, !1429, !1435, !1436, !1437, !1438, !1443, !1444, !1445, !1451, !1455, !1460, !1461, !1462}
!1414 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !1412, file: !121, line: 764, baseType: !851, size: 64, align: 64)
!1415 = !DIDerivedType(tag: DW_TAG_member, name: "setup_connection", scope: !1412, file: !121, line: 767, baseType: !1416, size: 64, align: 64, offset: 64)
!1416 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1417, size: 64, align: 64)
!1417 = !DISubroutineType(types: !1418)
!1418 = !{!289, !262}
!1419 = !DIDerivedType(tag: DW_TAG_member, name: "do_it", scope: !1412, file: !121, line: 770, baseType: !1420, size: 64, align: 64, offset: 128)
!1420 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1421, size: 64, align: 64)
!1421 = !DISubroutineType(types: !1422)
!1422 = !{!289, !262, !1423}
!1423 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !423, size: 64, align: 64)
!1424 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1412, file: !121, line: 771, baseType: !1425, size: 64, align: 64, offset: 192)
!1425 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_done_func", file: !121, line: 634, baseType: !1426)
!1426 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1427, size: 64, align: 64)
!1427 = !DISubroutineType(types: !1428)
!1428 = !{!289, !262, !289, !423}
!1429 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1412, file: !121, line: 777, baseType: !1430, size: 64, align: 64, offset: 256)
!1430 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_do_more_func", file: !121, line: 633, baseType: !1431)
!1431 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1432, size: 64, align: 64)
!1432 = !DISubroutineType(types: !1433)
!1433 = !{!289, !262, !1434}
!1434 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !316, size: 64, align: 64)
!1435 = !DIDerivedType(tag: DW_TAG_member, name: "connect_it", scope: !1412, file: !121, line: 785, baseType: !1420, size: 64, align: 64, offset: 320)
!1436 = !DIDerivedType(tag: DW_TAG_member, name: "connecting", scope: !1412, file: !121, line: 788, baseType: !1420, size: 64, align: 64, offset: 384)
!1437 = !DIDerivedType(tag: DW_TAG_member, name: "doing", scope: !1412, file: !121, line: 789, baseType: !1420, size: 64, align: 64, offset: 448)
!1438 = !DIDerivedType(tag: DW_TAG_member, name: "proto_getsock", scope: !1412, file: !121, line: 793, baseType: !1439, size: 64, align: 64, offset: 512)
!1439 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1440, size: 64, align: 64)
!1440 = !DISubroutineType(types: !1441)
!1441 = !{!316, !262, !1442, !316}
!1442 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !315, size: 64, align: 64)
!1443 = !DIDerivedType(tag: DW_TAG_member, name: "doing_getsock", scope: !1412, file: !121, line: 799, baseType: !1439, size: 64, align: 64, offset: 576)
!1444 = !DIDerivedType(tag: DW_TAG_member, name: "domore_getsock", scope: !1412, file: !121, line: 805, baseType: !1439, size: 64, align: 64, offset: 640)
!1445 = !DIDerivedType(tag: DW_TAG_member, name: "perform_getsock", scope: !1412, file: !121, line: 812, baseType: !1446, size: 64, align: 64, offset: 704)
!1446 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1447, size: 64, align: 64)
!1447 = !DISubroutineType(types: !1448)
!1448 = !{!316, !1449, !1442, !316}
!1449 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1450, size: 64, align: 64)
!1450 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !253)
!1451 = !DIDerivedType(tag: DW_TAG_member, name: "disconnect", scope: !1412, file: !121, line: 821, baseType: !1452, size: 64, align: 64, offset: 768)
!1452 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1453, size: 64, align: 64)
!1453 = !DISubroutineType(types: !1454)
!1454 = !{!289, !262, !423}
!1455 = !DIDerivedType(tag: DW_TAG_member, name: "readwrite", scope: !1412, file: !121, line: 825, baseType: !1456, size: 64, align: 64, offset: 832)
!1456 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1457, size: 64, align: 64)
!1457 = !DISubroutineType(types: !1458)
!1458 = !{!289, !256, !262, !1459, !1423}
!1459 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !519, size: 64, align: 64)
!1460 = !DIDerivedType(tag: DW_TAG_member, name: "defport", scope: !1412, file: !121, line: 828, baseType: !379, size: 64, align: 64, offset: 896)
!1461 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !1412, file: !121, line: 829, baseType: !683, size: 32, align: 32, offset: 960)
!1462 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1412, file: !121, line: 831, baseType: !683, size: 32, align: 32, offset: 992)
!1463 = !DIDerivedType(tag: DW_TAG_member, name: "given", scope: !253, file: !121, line: 1011, baseType: !1410, size: 64, align: 64, offset: 7360)
!1464 = !DIDerivedType(tag: DW_TAG_member, name: "ip_version", scope: !253, file: !121, line: 1013, baseType: !379, size: 64, align: 64, offset: 7424)
!1465 = !DIDerivedType(tag: DW_TAG_member, name: "sockfd", scope: !253, file: !121, line: 1017, baseType: !315, size: 32, align: 32, offset: 7488)
!1466 = !DIDerivedType(tag: DW_TAG_member, name: "writesockfd", scope: !253, file: !121, line: 1018, baseType: !315, size: 32, align: 32, offset: 7520)
!1467 = !DIDerivedType(tag: DW_TAG_member, name: "allocptr", scope: !253, file: !121, line: 1035, baseType: !1468, size: 640, align: 64, offset: 7552)
!1468 = !DICompositeType(tag: DW_TAG_structure_type, name: "dynamically_allocated_data", file: !121, line: 1024, size: 640, align: 64, elements: !1469)
!1469 = !{!1470, !1471, !1472, !1473, !1474, !1475, !1476, !1477, !1478, !1479}
!1470 = !DIDerivedType(tag: DW_TAG_member, name: "proxyuserpwd", scope: !1468, file: !121, line: 1025, baseType: !479, size: 64, align: 64)
!1471 = !DIDerivedType(tag: DW_TAG_member, name: "uagent", scope: !1468, file: !121, line: 1026, baseType: !479, size: 64, align: 64, offset: 64)
!1472 = !DIDerivedType(tag: DW_TAG_member, name: "accept_encoding", scope: !1468, file: !121, line: 1027, baseType: !479, size: 64, align: 64, offset: 128)
!1473 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd", scope: !1468, file: !121, line: 1028, baseType: !479, size: 64, align: 64, offset: 192)
!1474 = !DIDerivedType(tag: DW_TAG_member, name: "rangeline", scope: !1468, file: !121, line: 1029, baseType: !479, size: 64, align: 64, offset: 256)
!1475 = !DIDerivedType(tag: DW_TAG_member, name: "ref", scope: !1468, file: !121, line: 1030, baseType: !479, size: 64, align: 64, offset: 320)
!1476 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1468, file: !121, line: 1031, baseType: !479, size: 64, align: 64, offset: 384)
!1477 = !DIDerivedType(tag: DW_TAG_member, name: "cookiehost", scope: !1468, file: !121, line: 1032, baseType: !479, size: 64, align: 64, offset: 448)
!1478 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_transport", scope: !1468, file: !121, line: 1033, baseType: !479, size: 64, align: 64, offset: 512)
!1479 = !DIDerivedType(tag: DW_TAG_member, name: "te", scope: !1468, file: !121, line: 1034, baseType: !479, size: 64, align: 64, offset: 576)
!1480 = !DIDerivedType(tag: DW_TAG_member, name: "readchannel_inuse", scope: !253, file: !121, line: 1057, baseType: !423, size: 8, align: 8, offset: 8192)
!1481 = !DIDerivedType(tag: DW_TAG_member, name: "writechannel_inuse", scope: !253, file: !121, line: 1059, baseType: !423, size: 8, align: 8, offset: 8200)
!1482 = !DIDerivedType(tag: DW_TAG_member, name: "send_pipe", scope: !253, file: !121, line: 1061, baseType: !330, size: 256, align: 64, offset: 8256)
!1483 = !DIDerivedType(tag: DW_TAG_member, name: "recv_pipe", scope: !253, file: !121, line: 1063, baseType: !330, size: 256, align: 64, offset: 8512)
!1484 = !DIDerivedType(tag: DW_TAG_member, name: "master_buffer", scope: !253, file: !121, line: 1065, baseType: !479, size: 64, align: 64, offset: 8768)
!1485 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !253, file: !121, line: 1067, baseType: !347, size: 64, align: 64, offset: 8832)
!1486 = !DIDerivedType(tag: DW_TAG_member, name: "buf_len", scope: !253, file: !121, line: 1068, baseType: !347, size: 64, align: 64, offset: 8896)
!1487 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !253, file: !121, line: 1071, baseType: !602, size: 64, align: 64, offset: 8960)
!1488 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !253, file: !121, line: 1072, baseType: !311, size: 64, align: 64, offset: 9024)
!1489 = !DIDerivedType(tag: DW_TAG_member, name: "syserr_buf", scope: !253, file: !121, line: 1091, baseType: !1490, size: 2048, align: 8, offset: 9088)
!1490 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 2048, align: 8, elements: !1491)
!1491 = !{!1492}
!1492 = !DISubrange(count: 256)
!1493 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !253, file: !121, line: 1099, baseType: !479, size: 64, align: 64, offset: 11136)
!1494 = !DIDerivedType(tag: DW_TAG_member, name: "trlMax", scope: !253, file: !121, line: 1100, baseType: !316, size: 32, align: 32, offset: 11200)
!1495 = !DIDerivedType(tag: DW_TAG_member, name: "trlPos", scope: !253, file: !121, line: 1101, baseType: !316, size: 32, align: 32, offset: 11232)
!1496 = !DIDerivedType(tag: DW_TAG_member, name: "proto", scope: !253, file: !121, line: 1114, baseType: !1497, size: 1792, align: 64, offset: 11264)
!1497 = !DICompositeType(tag: DW_TAG_union_type, scope: !253, file: !121, line: 1103, size: 1792, align: 64, elements: !1498)
!1498 = !{!1499, !1546, !1551, !1556, !1559, !1607, !1621, !1633, !1640, !1658}
!1499 = !DIDerivedType(tag: DW_TAG_member, name: "ftpc", scope: !1497, file: !121, line: 1104, baseType: !1500, size: 1792, align: 64)
!1500 = !DICompositeType(tag: DW_TAG_structure_type, name: "ftp_conn", file: !135, line: 118, size: 1792, align: 64, elements: !1501)
!1501 = !{!1502, !1522, !1523, !1525, !1526, !1527, !1528, !1529, !1530, !1531, !1532, !1533, !1534, !1535, !1536, !1537, !1538, !1540, !1541, !1542, !1543, !1544, !1545}
!1502 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1500, file: !135, line: 119, baseType: !1503, size: 896, align: 64)
!1503 = !DICompositeType(tag: DW_TAG_structure_type, name: "pingpong", file: !1504, line: 48, size: 896, align: 64, elements: !1505)
!1504 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pingpong.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1505 = !{!1506, !1507, !1508, !1509, !1510, !1511, !1512, !1513, !1514, !1515, !1516, !1517, !1518}
!1506 = !DIDerivedType(tag: DW_TAG_member, name: "cache", scope: !1503, file: !1504, line: 49, baseType: !479, size: 64, align: 64)
!1507 = !DIDerivedType(tag: DW_TAG_member, name: "cache_size", scope: !1503, file: !1504, line: 50, baseType: !347, size: 64, align: 64, offset: 64)
!1508 = !DIDerivedType(tag: DW_TAG_member, name: "nread_resp", scope: !1503, file: !1504, line: 51, baseType: !347, size: 64, align: 64, offset: 128)
!1509 = !DIDerivedType(tag: DW_TAG_member, name: "linestart_resp", scope: !1503, file: !1504, line: 52, baseType: !479, size: 64, align: 64, offset: 192)
!1510 = !DIDerivedType(tag: DW_TAG_member, name: "pending_resp", scope: !1503, file: !1504, line: 54, baseType: !423, size: 8, align: 8, offset: 256)
!1511 = !DIDerivedType(tag: DW_TAG_member, name: "sendthis", scope: !1503, file: !1504, line: 57, baseType: !479, size: 64, align: 64, offset: 320)
!1512 = !DIDerivedType(tag: DW_TAG_member, name: "sendleft", scope: !1503, file: !1504, line: 59, baseType: !347, size: 64, align: 64, offset: 384)
!1513 = !DIDerivedType(tag: DW_TAG_member, name: "sendsize", scope: !1503, file: !1504, line: 60, baseType: !347, size: 64, align: 64, offset: 448)
!1514 = !DIDerivedType(tag: DW_TAG_member, name: "response", scope: !1503, file: !1504, line: 61, baseType: !411, size: 128, align: 64, offset: 512)
!1515 = !DIDerivedType(tag: DW_TAG_member, name: "response_time", scope: !1503, file: !1504, line: 63, baseType: !379, size: 64, align: 64, offset: 640)
!1516 = !DIDerivedType(tag: DW_TAG_member, name: "conn", scope: !1503, file: !1504, line: 66, baseType: !262, size: 64, align: 64, offset: 704)
!1517 = !DIDerivedType(tag: DW_TAG_member, name: "statemach_act", scope: !1503, file: !1504, line: 72, baseType: !1416, size: 64, align: 64, offset: 768)
!1518 = !DIDerivedType(tag: DW_TAG_member, name: "endofresp", scope: !1503, file: !1504, line: 74, baseType: !1519, size: 64, align: 64, offset: 832)
!1519 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1520, size: 64, align: 64)
!1520 = !DISubroutineType(types: !1521)
!1521 = !{!423, !262, !479, !347, !1434}
!1522 = !DIDerivedType(tag: DW_TAG_member, name: "entrypath", scope: !1500, file: !135, line: 120, baseType: !479, size: 64, align: 64, offset: 896)
!1523 = !DIDerivedType(tag: DW_TAG_member, name: "dirs", scope: !1500, file: !135, line: 121, baseType: !1524, size: 64, align: 64, offset: 960)
!1524 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !479, size: 64, align: 64)
!1525 = !DIDerivedType(tag: DW_TAG_member, name: "dirdepth", scope: !1500, file: !135, line: 122, baseType: !316, size: 32, align: 32, offset: 1024)
!1526 = !DIDerivedType(tag: DW_TAG_member, name: "diralloc", scope: !1500, file: !135, line: 123, baseType: !316, size: 32, align: 32, offset: 1056)
!1527 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !1500, file: !135, line: 124, baseType: !479, size: 64, align: 64, offset: 1088)
!1528 = !DIDerivedType(tag: DW_TAG_member, name: "dont_check", scope: !1500, file: !135, line: 125, baseType: !423, size: 8, align: 8, offset: 1152)
!1529 = !DIDerivedType(tag: DW_TAG_member, name: "ctl_valid", scope: !1500, file: !135, line: 128, baseType: !423, size: 8, align: 8, offset: 1160)
!1530 = !DIDerivedType(tag: DW_TAG_member, name: "cwddone", scope: !1500, file: !135, line: 131, baseType: !423, size: 8, align: 8, offset: 1168)
!1531 = !DIDerivedType(tag: DW_TAG_member, name: "cwdfail", scope: !1500, file: !135, line: 133, baseType: !423, size: 8, align: 8, offset: 1176)
!1532 = !DIDerivedType(tag: DW_TAG_member, name: "wait_data_conn", scope: !1500, file: !135, line: 135, baseType: !423, size: 8, align: 8, offset: 1184)
!1533 = !DIDerivedType(tag: DW_TAG_member, name: "prevpath", scope: !1500, file: !135, line: 136, baseType: !479, size: 64, align: 64, offset: 1216)
!1534 = !DIDerivedType(tag: DW_TAG_member, name: "transfertype", scope: !1500, file: !135, line: 137, baseType: !480, size: 8, align: 8, offset: 1280)
!1535 = !DIDerivedType(tag: DW_TAG_member, name: "count1", scope: !1500, file: !135, line: 139, baseType: !316, size: 32, align: 32, offset: 1312)
!1536 = !DIDerivedType(tag: DW_TAG_member, name: "count2", scope: !1500, file: !135, line: 140, baseType: !316, size: 32, align: 32, offset: 1344)
!1537 = !DIDerivedType(tag: DW_TAG_member, name: "count3", scope: !1500, file: !135, line: 141, baseType: !316, size: 32, align: 32, offset: 1376)
!1538 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1500, file: !135, line: 142, baseType: !1539, size: 32, align: 32, offset: 1408)
!1539 = !DIDerivedType(tag: DW_TAG_typedef, name: "ftpstate", file: !135, line: 80, baseType: !134)
!1540 = !DIDerivedType(tag: DW_TAG_member, name: "state_saved", scope: !1500, file: !135, line: 143, baseType: !1539, size: 32, align: 32, offset: 1440)
!1541 = !DIDerivedType(tag: DW_TAG_member, name: "retr_size_saved", scope: !1500, file: !135, line: 145, baseType: !458, size: 64, align: 64, offset: 1472)
!1542 = !DIDerivedType(tag: DW_TAG_member, name: "server_os", scope: !1500, file: !135, line: 146, baseType: !479, size: 64, align: 64, offset: 1536)
!1543 = !DIDerivedType(tag: DW_TAG_member, name: "known_filesize", scope: !1500, file: !135, line: 147, baseType: !458, size: 64, align: 64, offset: 1600)
!1544 = !DIDerivedType(tag: DW_TAG_member, name: "newhost", scope: !1500, file: !135, line: 152, baseType: !479, size: 64, align: 64, offset: 1664)
!1545 = !DIDerivedType(tag: DW_TAG_member, name: "newport", scope: !1500, file: !135, line: 153, baseType: !564, size: 16, align: 16, offset: 1728)
!1546 = !DIDerivedType(tag: DW_TAG_member, name: "httpc", scope: !1497, file: !121, line: 1105, baseType: !1547, size: 32, align: 32)
!1547 = !DICompositeType(tag: DW_TAG_structure_type, name: "http_conn", file: !1548, line: 200, size: 32, align: 32, elements: !1549)
!1548 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1549 = !{!1550}
!1550 = !DIDerivedType(tag: DW_TAG_member, name: "unused", scope: !1547, file: !1548, line: 227, baseType: !316, size: 32, align: 32)
!1551 = !DIDerivedType(tag: DW_TAG_member, name: "sshc", scope: !1497, file: !121, line: 1106, baseType: !1552, size: 64, align: 64)
!1552 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssh_conn", file: !1553, line: 110, size: 64, align: 64, elements: !1554)
!1553 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/ssh.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1554 = !{!1555}
!1555 = !DIDerivedType(tag: DW_TAG_member, name: "authlist", scope: !1552, file: !1553, line: 111, baseType: !851, size: 64, align: 64)
!1556 = !DIDerivedType(tag: DW_TAG_member, name: "tftpc", scope: !1497, file: !121, line: 1107, baseType: !1557, size: 64, align: 64)
!1557 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1558, size: 64, align: 64)
!1558 = !DICompositeType(tag: DW_TAG_structure_type, name: "tftp_state_data", file: !121, line: 1107, flags: DIFlagFwdDecl)
!1559 = !DIDerivedType(tag: DW_TAG_member, name: "imapc", scope: !1497, file: !121, line: 1108, baseType: !1560, size: 1472, align: 64)
!1560 = !DICompositeType(tag: DW_TAG_structure_type, name: "imap_conn", file: !174, line: 70, size: 1472, align: 64, elements: !1561)
!1561 = !{!1562, !1563, !1565, !1566, !1598, !1599, !1600, !1602, !1603, !1604, !1605, !1606}
!1562 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1560, file: !174, line: 71, baseType: !1503, size: 896, align: 64)
!1563 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1560, file: !174, line: 72, baseType: !1564, size: 32, align: 32, offset: 896)
!1564 = !DIDerivedType(tag: DW_TAG_typedef, name: "imapstate", file: !174, line: 50, baseType: !173)
!1565 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1560, file: !174, line: 73, baseType: !423, size: 8, align: 8, offset: 928)
!1566 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1560, file: !174, line: 74, baseType: !1567, size: 256, align: 64, offset: 960)
!1567 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASL", file: !193, line: 101, size: 256, align: 64, elements: !1568)
!1568 = !{!1569, !1590, !1592, !1593, !1594, !1595, !1596, !1597}
!1569 = !DIDerivedType(tag: DW_TAG_member, name: "params", scope: !1567, file: !193, line: 102, baseType: !1570, size: 64, align: 64)
!1570 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1571, size: 64, align: 64)
!1571 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1572)
!1572 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASLproto", file: !193, line: 86, size: 384, align: 64, elements: !1573)
!1573 = !{!1574, !1575, !1576, !1577, !1578, !1582, !1586}
!1574 = !DIDerivedType(tag: DW_TAG_member, name: "service", scope: !1572, file: !193, line: 87, baseType: !851, size: 64, align: 64)
!1575 = !DIDerivedType(tag: DW_TAG_member, name: "contcode", scope: !1572, file: !193, line: 88, baseType: !316, size: 32, align: 32, offset: 64)
!1576 = !DIDerivedType(tag: DW_TAG_member, name: "finalcode", scope: !1572, file: !193, line: 89, baseType: !316, size: 32, align: 32, offset: 96)
!1577 = !DIDerivedType(tag: DW_TAG_member, name: "maxirlen", scope: !1572, file: !193, line: 90, baseType: !347, size: 64, align: 64, offset: 128)
!1578 = !DIDerivedType(tag: DW_TAG_member, name: "sendauth", scope: !1572, file: !193, line: 91, baseType: !1579, size: 64, align: 64, offset: 192)
!1579 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1580, size: 64, align: 64)
!1580 = !DISubroutineType(types: !1581)
!1581 = !{!289, !262, !851, !851}
!1582 = !DIDerivedType(tag: DW_TAG_member, name: "sendcont", scope: !1572, file: !193, line: 94, baseType: !1583, size: 64, align: 64, offset: 256)
!1583 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1584, size: 64, align: 64)
!1584 = !DISubroutineType(types: !1585)
!1585 = !{!289, !262, !851}
!1586 = !DIDerivedType(tag: DW_TAG_member, name: "getmessage", scope: !1572, file: !193, line: 96, baseType: !1587, size: 64, align: 64, offset: 320)
!1587 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1588, size: 64, align: 64)
!1588 = !DISubroutineType(types: !1589)
!1589 = !{null, !479, !1524}
!1590 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1567, file: !193, line: 103, baseType: !1591, size: 32, align: 32, offset: 64)
!1591 = !DIDerivedType(tag: DW_TAG_typedef, name: "saslstate", file: !193, line: 76, baseType: !192)
!1592 = !DIDerivedType(tag: DW_TAG_member, name: "authmechs", scope: !1567, file: !193, line: 104, baseType: !683, size: 32, align: 32, offset: 96)
!1593 = !DIDerivedType(tag: DW_TAG_member, name: "prefmech", scope: !1567, file: !193, line: 105, baseType: !683, size: 32, align: 32, offset: 128)
!1594 = !DIDerivedType(tag: DW_TAG_member, name: "authused", scope: !1567, file: !193, line: 106, baseType: !683, size: 32, align: 32, offset: 160)
!1595 = !DIDerivedType(tag: DW_TAG_member, name: "resetprefs", scope: !1567, file: !193, line: 107, baseType: !423, size: 8, align: 8, offset: 192)
!1596 = !DIDerivedType(tag: DW_TAG_member, name: "mutual_auth", scope: !1567, file: !193, line: 108, baseType: !423, size: 8, align: 8, offset: 200)
!1597 = !DIDerivedType(tag: DW_TAG_member, name: "force_ir", scope: !1567, file: !193, line: 109, baseType: !423, size: 8, align: 8, offset: 208)
!1598 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1560, file: !174, line: 75, baseType: !683, size: 32, align: 32, offset: 1216)
!1599 = !DIDerivedType(tag: DW_TAG_member, name: "cmdid", scope: !1560, file: !174, line: 76, baseType: !316, size: 32, align: 32, offset: 1248)
!1600 = !DIDerivedType(tag: DW_TAG_member, name: "resptag", scope: !1560, file: !174, line: 77, baseType: !1601, size: 40, align: 8, offset: 1280)
!1601 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 40, align: 8, elements: !317)
!1602 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1560, file: !174, line: 78, baseType: !423, size: 8, align: 8, offset: 1320)
!1603 = !DIDerivedType(tag: DW_TAG_member, name: "login_disabled", scope: !1560, file: !174, line: 79, baseType: !423, size: 8, align: 8, offset: 1328)
!1604 = !DIDerivedType(tag: DW_TAG_member, name: "ir_supported", scope: !1560, file: !174, line: 80, baseType: !423, size: 8, align: 8, offset: 1336)
!1605 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox", scope: !1560, file: !174, line: 81, baseType: !479, size: 64, align: 64, offset: 1344)
!1606 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox_uidvalidity", scope: !1560, file: !174, line: 82, baseType: !479, size: 64, align: 64, offset: 1408)
!1607 = !DIDerivedType(tag: DW_TAG_member, name: "pop3c", scope: !1497, file: !121, line: 1109, baseType: !1608, size: 1536, align: 64)
!1608 = !DICompositeType(tag: DW_TAG_structure_type, name: "pop3_conn", file: !213, line: 60, size: 1536, align: 64, elements: !1609)
!1609 = !{!1610, !1611, !1613, !1614, !1615, !1616, !1617, !1618, !1619, !1620}
!1610 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1608, file: !213, line: 61, baseType: !1503, size: 896, align: 64)
!1611 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1608, file: !213, line: 62, baseType: !1612, size: 32, align: 32, offset: 896)
!1612 = !DIDerivedType(tag: DW_TAG_typedef, name: "pop3state", file: !213, line: 46, baseType: !212)
!1613 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1608, file: !213, line: 63, baseType: !423, size: 8, align: 8, offset: 928)
!1614 = !DIDerivedType(tag: DW_TAG_member, name: "eob", scope: !1608, file: !213, line: 64, baseType: !347, size: 64, align: 64, offset: 960)
!1615 = !DIDerivedType(tag: DW_TAG_member, name: "strip", scope: !1608, file: !213, line: 66, baseType: !347, size: 64, align: 64, offset: 1024)
!1616 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1608, file: !213, line: 68, baseType: !1567, size: 256, align: 64, offset: 1088)
!1617 = !DIDerivedType(tag: DW_TAG_member, name: "authtypes", scope: !1608, file: !213, line: 69, baseType: !683, size: 32, align: 32, offset: 1344)
!1618 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1608, file: !213, line: 70, baseType: !683, size: 32, align: 32, offset: 1376)
!1619 = !DIDerivedType(tag: DW_TAG_member, name: "apoptimestamp", scope: !1608, file: !213, line: 71, baseType: !479, size: 64, align: 64, offset: 1408)
!1620 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1608, file: !213, line: 72, baseType: !423, size: 8, align: 8, offset: 1472)
!1621 = !DIDerivedType(tag: DW_TAG_member, name: "smtpc", scope: !1497, file: !121, line: 1110, baseType: !1622, size: 1344, align: 64)
!1622 = !DICompositeType(tag: DW_TAG_structure_type, name: "smtp_conn", file: !228, line: 65, size: 1344, align: 64, elements: !1623)
!1623 = !{!1624, !1625, !1627, !1628, !1629, !1630, !1631, !1632}
!1624 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1622, file: !228, line: 66, baseType: !1503, size: 896, align: 64)
!1625 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1622, file: !228, line: 67, baseType: !1626, size: 32, align: 32, offset: 896)
!1626 = !DIDerivedType(tag: DW_TAG_typedef, name: "smtpstate", file: !228, line: 48, baseType: !227)
!1627 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1622, file: !228, line: 68, baseType: !423, size: 8, align: 8, offset: 928)
!1628 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1622, file: !228, line: 69, baseType: !479, size: 64, align: 64, offset: 960)
!1629 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1622, file: !228, line: 70, baseType: !1567, size: 256, align: 64, offset: 1024)
!1630 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1622, file: !228, line: 71, baseType: !423, size: 8, align: 8, offset: 1280)
!1631 = !DIDerivedType(tag: DW_TAG_member, name: "size_supported", scope: !1622, file: !228, line: 72, baseType: !423, size: 8, align: 8, offset: 1288)
!1632 = !DIDerivedType(tag: DW_TAG_member, name: "auth_supported", scope: !1622, file: !228, line: 74, baseType: !423, size: 8, align: 8, offset: 1296)
!1633 = !DIDerivedType(tag: DW_TAG_member, name: "rtspc", scope: !1497, file: !121, line: 1111, baseType: !1634, size: 192, align: 64)
!1634 = !DICompositeType(tag: DW_TAG_structure_type, name: "rtsp_conn", file: !1635, line: 43, size: 192, align: 64, elements: !1636)
!1635 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/rtsp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1636 = !{!1637, !1638, !1639}
!1637 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_buf", scope: !1634, file: !1635, line: 44, baseType: !479, size: 64, align: 64)
!1638 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_bufsize", scope: !1634, file: !1635, line: 45, baseType: !519, size: 64, align: 64, offset: 64)
!1639 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_channel", scope: !1634, file: !1635, line: 46, baseType: !316, size: 32, align: 32, offset: 128)
!1640 = !DIDerivedType(tag: DW_TAG_member, name: "smbc", scope: !1497, file: !121, line: 1112, baseType: !1641, size: 640, align: 64)
!1641 = !DICompositeType(tag: DW_TAG_structure_type, name: "smb_conn", file: !245, line: 33, size: 640, align: 64, elements: !1642)
!1642 = !{!1643, !1644, !1645, !1646, !1651, !1652, !1653, !1654, !1655, !1656, !1657}
!1643 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1641, file: !245, line: 34, baseType: !244, size: 32, align: 32)
!1644 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1641, file: !245, line: 35, baseType: !479, size: 64, align: 64, offset: 64)
!1645 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1641, file: !245, line: 36, baseType: !479, size: 64, align: 64, offset: 128)
!1646 = !DIDerivedType(tag: DW_TAG_member, name: "challenge", scope: !1641, file: !245, line: 37, baseType: !1647, size: 64, align: 8, offset: 192)
!1647 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1648, size: 64, align: 8, elements: !1649)
!1648 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!1649 = !{!1650}
!1650 = !DISubrange(count: 8)
!1651 = !DIDerivedType(tag: DW_TAG_member, name: "session_key", scope: !1641, file: !245, line: 38, baseType: !683, size: 32, align: 32, offset: 256)
!1652 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !1641, file: !245, line: 39, baseType: !564, size: 16, align: 16, offset: 288)
!1653 = !DIDerivedType(tag: DW_TAG_member, name: "recv_buf", scope: !1641, file: !245, line: 40, baseType: !479, size: 64, align: 64, offset: 320)
!1654 = !DIDerivedType(tag: DW_TAG_member, name: "upload_size", scope: !1641, file: !245, line: 41, baseType: !347, size: 64, align: 64, offset: 384)
!1655 = !DIDerivedType(tag: DW_TAG_member, name: "send_size", scope: !1641, file: !245, line: 42, baseType: !347, size: 64, align: 64, offset: 448)
!1656 = !DIDerivedType(tag: DW_TAG_member, name: "sent", scope: !1641, file: !245, line: 43, baseType: !347, size: 64, align: 64, offset: 512)
!1657 = !DIDerivedType(tag: DW_TAG_member, name: "got", scope: !1641, file: !245, line: 44, baseType: !347, size: 64, align: 64, offset: 576)
!1658 = !DIDerivedType(tag: DW_TAG_member, name: "generic", scope: !1497, file: !121, line: 1113, baseType: !311, size: 64, align: 64)
!1659 = !DIDerivedType(tag: DW_TAG_member, name: "cselect_bits", scope: !253, file: !121, line: 1116, baseType: !316, size: 32, align: 32, offset: 13056)
!1660 = !DIDerivedType(tag: DW_TAG_member, name: "waitfor", scope: !253, file: !121, line: 1117, baseType: !316, size: 32, align: 32, offset: 13088)
!1661 = !DIDerivedType(tag: DW_TAG_member, name: "localdev", scope: !253, file: !121, line: 1128, baseType: !479, size: 64, align: 64, offset: 13120)
!1662 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !253, file: !121, line: 1129, baseType: !564, size: 16, align: 16, offset: 13184)
!1663 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !253, file: !121, line: 1130, baseType: !316, size: 32, align: 32, offset: 13216)
!1664 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_state", scope: !253, file: !121, line: 1137, baseType: !1665, size: 64, align: 32, offset: 13248)
!1665 = !DICompositeType(tag: DW_TAG_array_type, baseType: !252, size: 64, align: 32, elements: !1300)
!1666 = !DIDerivedType(tag: DW_TAG_member, name: "bundle", scope: !253, file: !121, line: 1138, baseType: !1667, size: 64, align: 64, offset: 13312)
!1667 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1668, size: 64, align: 64)
!1668 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectbundle", file: !426, line: 38, size: 384, align: 64, elements: !1669)
!1669 = !{!1670, !1671, !1672}
!1670 = !DIDerivedType(tag: DW_TAG_member, name: "multiuse", scope: !1668, file: !426, line: 39, baseType: !316, size: 32, align: 32)
!1671 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !1668, file: !426, line: 40, baseType: !347, size: 64, align: 64, offset: 64)
!1672 = !DIDerivedType(tag: DW_TAG_member, name: "conn_list", scope: !1668, file: !426, line: 41, baseType: !330, size: 256, align: 64, offset: 128)
!1673 = !DIDerivedType(tag: DW_TAG_member, name: "negnpn", scope: !253, file: !121, line: 1140, baseType: !316, size: 32, align: 32, offset: 13376)
!1674 = !{!1675, !1676, !1677}
!1675 = !DIEnumerator(name: "TUNNEL_INIT", value: 0)
!1676 = !DIEnumerator(name: "TUNNEL_CONNECT", value: 1)
!1677 = !DIEnumerator(name: "TUNNEL_COMPLETE", value: 2)
!1678 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !1679, line: 24, size: 32, align: 32, elements: !1680)
!1679 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1680 = !{!1681, !1682, !1683, !1684, !1685, !1686, !1687, !1688, !1689}
!1681 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!1682 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!1683 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!1684 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!1685 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!1686 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!1687 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!1688 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!1689 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!1690 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1691, line: 28, size: 32, align: 32, elements: !1692)
!1691 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/progress.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1692 = !{!1693, !1694, !1695, !1696, !1697, !1698, !1699, !1700, !1701, !1702, !1703, !1704}
!1693 = !DIEnumerator(name: "TIMER_NONE", value: 0)
!1694 = !DIEnumerator(name: "TIMER_STARTOP", value: 1)
!1695 = !DIEnumerator(name: "TIMER_STARTSINGLE", value: 2)
!1696 = !DIEnumerator(name: "TIMER_NAMELOOKUP", value: 3)
!1697 = !DIEnumerator(name: "TIMER_CONNECT", value: 4)
!1698 = !DIEnumerator(name: "TIMER_APPCONNECT", value: 5)
!1699 = !DIEnumerator(name: "TIMER_PRETRANSFER", value: 6)
!1700 = !DIEnumerator(name: "TIMER_STARTTRANSFER", value: 7)
!1701 = !DIEnumerator(name: "TIMER_POSTRANSFER", value: 8)
!1702 = !DIEnumerator(name: "TIMER_STARTACCEPT", value: 9)
!1703 = !DIEnumerator(name: "TIMER_REDIRECT", value: 10)
!1704 = !DIEnumerator(name: "TIMER_LAST", value: 11)
!1705 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1706, line: 40, size: 32, align: 32, elements: !1707)
!1706 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1707 = !{!1708, !1709, !1710, !1711, !1712, !1713, !1714, !1715, !1716, !1717, !1718, !1719, !1720, !1721, !1722, !1723, !1724, !1725, !1726, !1727, !1728, !1729, !1730, !1731, !1732}
!1708 = !DIEnumerator(name: "IPPROTO_IP", value: 0)
!1709 = !DIEnumerator(name: "IPPROTO_ICMP", value: 1)
!1710 = !DIEnumerator(name: "IPPROTO_IGMP", value: 2)
!1711 = !DIEnumerator(name: "IPPROTO_IPIP", value: 4)
!1712 = !DIEnumerator(name: "IPPROTO_TCP", value: 6)
!1713 = !DIEnumerator(name: "IPPROTO_EGP", value: 8)
!1714 = !DIEnumerator(name: "IPPROTO_PUP", value: 12)
!1715 = !DIEnumerator(name: "IPPROTO_UDP", value: 17)
!1716 = !DIEnumerator(name: "IPPROTO_IDP", value: 22)
!1717 = !DIEnumerator(name: "IPPROTO_TP", value: 29)
!1718 = !DIEnumerator(name: "IPPROTO_DCCP", value: 33)
!1719 = !DIEnumerator(name: "IPPROTO_IPV6", value: 41)
!1720 = !DIEnumerator(name: "IPPROTO_RSVP", value: 46)
!1721 = !DIEnumerator(name: "IPPROTO_GRE", value: 47)
!1722 = !DIEnumerator(name: "IPPROTO_ESP", value: 50)
!1723 = !DIEnumerator(name: "IPPROTO_AH", value: 51)
!1724 = !DIEnumerator(name: "IPPROTO_MTP", value: 92)
!1725 = !DIEnumerator(name: "IPPROTO_BEETPH", value: 94)
!1726 = !DIEnumerator(name: "IPPROTO_ENCAP", value: 98)
!1727 = !DIEnumerator(name: "IPPROTO_PIM", value: 103)
!1728 = !DIEnumerator(name: "IPPROTO_COMP", value: 108)
!1729 = !DIEnumerator(name: "IPPROTO_SCTP", value: 132)
!1730 = !DIEnumerator(name: "IPPROTO_UDPLITE", value: 136)
!1731 = !DIEnumerator(name: "IPPROTO_RAW", value: 255)
!1732 = !DIEnumerator(name: "IPPROTO_MAX", value: 256)
!1733 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !686, line: 171, size: 32, align: 32, elements: !1734)
!1734 = !{!1735, !1736, !1737, !1738, !1739, !1740, !1741, !1742, !1743, !1744, !1745, !1746, !1747, !1748, !1749, !1750, !1751, !1752, !1753}
!1735 = !DIEnumerator(name: "MSG_OOB", value: 1)
!1736 = !DIEnumerator(name: "MSG_PEEK", value: 2)
!1737 = !DIEnumerator(name: "MSG_DONTROUTE", value: 4)
!1738 = !DIEnumerator(name: "MSG_CTRUNC", value: 8)
!1739 = !DIEnumerator(name: "MSG_PROXY", value: 16)
!1740 = !DIEnumerator(name: "MSG_TRUNC", value: 32)
!1741 = !DIEnumerator(name: "MSG_DONTWAIT", value: 64)
!1742 = !DIEnumerator(name: "MSG_EOR", value: 128)
!1743 = !DIEnumerator(name: "MSG_WAITALL", value: 256)
!1744 = !DIEnumerator(name: "MSG_FIN", value: 512)
!1745 = !DIEnumerator(name: "MSG_SYN", value: 1024)
!1746 = !DIEnumerator(name: "MSG_CONFIRM", value: 2048)
!1747 = !DIEnumerator(name: "MSG_RST", value: 4096)
!1748 = !DIEnumerator(name: "MSG_ERRQUEUE", value: 8192)
!1749 = !DIEnumerator(name: "MSG_NOSIGNAL", value: 16384)
!1750 = !DIEnumerator(name: "MSG_MORE", value: 32768)
!1751 = !DIEnumerator(name: "MSG_WAITFORONE", value: 65536)
!1752 = !DIEnumerator(name: "MSG_FASTOPEN", value: 536870912)
!1753 = !DIEnumerator(name: "MSG_CMSG_CLOEXEC", value: 1073741824)
!1754 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "dupstring", file: !121, line: 1466, size: 32, align: 32, elements: !1755)
!1755 = !{!1756, !1757, !1758, !1759, !1760, !1761, !1762, !1763, !1764, !1765, !1766, !1767, !1768, !1769, !1770, !1771, !1772, !1773, !1774, !1775, !1776, !1777, !1778, !1779, !1780, !1781, !1782, !1783, !1784, !1785, !1786, !1787, !1788, !1789, !1790, !1791, !1792, !1793, !1794, !1795, !1796, !1797, !1798, !1799, !1800, !1801, !1802, !1803, !1804, !1805, !1806, !1807, !1808, !1809, !1810, !1811, !1812}
!1756 = !DIEnumerator(name: "STRING_CERT_ORIG", value: 0)
!1757 = !DIEnumerator(name: "STRING_CERT_PROXY", value: 1)
!1758 = !DIEnumerator(name: "STRING_CERT_TYPE_ORIG", value: 2)
!1759 = !DIEnumerator(name: "STRING_CERT_TYPE_PROXY", value: 3)
!1760 = !DIEnumerator(name: "STRING_COOKIE", value: 4)
!1761 = !DIEnumerator(name: "STRING_COOKIEJAR", value: 5)
!1762 = !DIEnumerator(name: "STRING_CUSTOMREQUEST", value: 6)
!1763 = !DIEnumerator(name: "STRING_DEFAULT_PROTOCOL", value: 7)
!1764 = !DIEnumerator(name: "STRING_DEVICE", value: 8)
!1765 = !DIEnumerator(name: "STRING_ENCODING", value: 9)
!1766 = !DIEnumerator(name: "STRING_FTP_ACCOUNT", value: 10)
!1767 = !DIEnumerator(name: "STRING_FTP_ALTERNATIVE_TO_USER", value: 11)
!1768 = !DIEnumerator(name: "STRING_FTPPORT", value: 12)
!1769 = !DIEnumerator(name: "STRING_KEY_ORIG", value: 13)
!1770 = !DIEnumerator(name: "STRING_KEY_PROXY", value: 14)
!1771 = !DIEnumerator(name: "STRING_KEY_PASSWD_ORIG", value: 15)
!1772 = !DIEnumerator(name: "STRING_KEY_PASSWD_PROXY", value: 16)
!1773 = !DIEnumerator(name: "STRING_KEY_TYPE_ORIG", value: 17)
!1774 = !DIEnumerator(name: "STRING_KEY_TYPE_PROXY", value: 18)
!1775 = !DIEnumerator(name: "STRING_KRB_LEVEL", value: 19)
!1776 = !DIEnumerator(name: "STRING_NETRC_FILE", value: 20)
!1777 = !DIEnumerator(name: "STRING_PROXY", value: 21)
!1778 = !DIEnumerator(name: "STRING_PRE_PROXY", value: 22)
!1779 = !DIEnumerator(name: "STRING_SET_RANGE", value: 23)
!1780 = !DIEnumerator(name: "STRING_SET_REFERER", value: 24)
!1781 = !DIEnumerator(name: "STRING_SET_URL", value: 25)
!1782 = !DIEnumerator(name: "STRING_SSL_CAPATH_ORIG", value: 26)
!1783 = !DIEnumerator(name: "STRING_SSL_CAPATH_PROXY", value: 27)
!1784 = !DIEnumerator(name: "STRING_SSL_CAFILE_ORIG", value: 28)
!1785 = !DIEnumerator(name: "STRING_SSL_CAFILE_PROXY", value: 29)
!1786 = !DIEnumerator(name: "STRING_SSL_PINNEDPUBLICKEY_ORIG", value: 30)
!1787 = !DIEnumerator(name: "STRING_SSL_PINNEDPUBLICKEY_PROXY", value: 31)
!1788 = !DIEnumerator(name: "STRING_SSL_CIPHER_LIST_ORIG", value: 32)
!1789 = !DIEnumerator(name: "STRING_SSL_CIPHER_LIST_PROXY", value: 33)
!1790 = !DIEnumerator(name: "STRING_SSL_EGDSOCKET", value: 34)
!1791 = !DIEnumerator(name: "STRING_SSL_RANDOM_FILE", value: 35)
!1792 = !DIEnumerator(name: "STRING_USERAGENT", value: 36)
!1793 = !DIEnumerator(name: "STRING_SSL_CRLFILE_ORIG", value: 37)
!1794 = !DIEnumerator(name: "STRING_SSL_CRLFILE_PROXY", value: 38)
!1795 = !DIEnumerator(name: "STRING_SSL_ISSUERCERT_ORIG", value: 39)
!1796 = !DIEnumerator(name: "STRING_SSL_ISSUERCERT_PROXY", value: 40)
!1797 = !DIEnumerator(name: "STRING_USERNAME", value: 41)
!1798 = !DIEnumerator(name: "STRING_PASSWORD", value: 42)
!1799 = !DIEnumerator(name: "STRING_OPTIONS", value: 43)
!1800 = !DIEnumerator(name: "STRING_PROXYUSERNAME", value: 44)
!1801 = !DIEnumerator(name: "STRING_PROXYPASSWORD", value: 45)
!1802 = !DIEnumerator(name: "STRING_NOPROXY", value: 46)
!1803 = !DIEnumerator(name: "STRING_RTSP_SESSION_ID", value: 47)
!1804 = !DIEnumerator(name: "STRING_RTSP_STREAM_URI", value: 48)
!1805 = !DIEnumerator(name: "STRING_RTSP_TRANSPORT", value: 49)
!1806 = !DIEnumerator(name: "STRING_SERVICE_NAME", value: 50)
!1807 = !DIEnumerator(name: "STRING_MAIL_FROM", value: 51)
!1808 = !DIEnumerator(name: "STRING_MAIL_AUTH", value: 52)
!1809 = !DIEnumerator(name: "STRING_BEARER", value: 53)
!1810 = !DIEnumerator(name: "STRING_LASTZEROTERMINATED", value: 54)
!1811 = !DIEnumerator(name: "STRING_COPYPOSTFIELDS", value: 55)
!1812 = !DIEnumerator(name: "STRING_LAST", value: 56)
!1813 = !{!1292, !311, !1287, !316, !347, !676, !1814, !1829, !1838}
!1814 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1815, size: 64, align: 64)
!1815 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in", file: !1706, line: 237, size: 128, align: 32, elements: !1816)
!1816 = !{!1817, !1818, !1822, !1828}
!1817 = !DIDerivedType(tag: DW_TAG_member, name: "sin_family", scope: !1815, file: !1706, line: 239, baseType: !689, size: 16, align: 16)
!1818 = !DIDerivedType(tag: DW_TAG_member, name: "sin_port", scope: !1815, file: !1706, line: 240, baseType: !1819, size: 16, align: 16, offset: 16)
!1819 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_port_t", file: !1706, line: 117, baseType: !1820)
!1820 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !1821, line: 49, baseType: !564)
!1821 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1822 = !DIDerivedType(tag: DW_TAG_member, name: "sin_addr", scope: !1815, file: !1706, line: 241, baseType: !1823, size: 32, align: 32, offset: 32)
!1823 = !DICompositeType(tag: DW_TAG_structure_type, name: "in_addr", file: !1706, line: 31, size: 32, align: 32, elements: !1824)
!1824 = !{!1825}
!1825 = !DIDerivedType(tag: DW_TAG_member, name: "s_addr", scope: !1823, file: !1706, line: 33, baseType: !1826, size: 32, align: 32)
!1826 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_addr_t", file: !1706, line: 30, baseType: !1827)
!1827 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !1821, line: 51, baseType: !683)
!1828 = !DIDerivedType(tag: DW_TAG_member, name: "sin_zero", scope: !1815, file: !1706, line: 244, baseType: !1647, size: 64, align: 8, offset: 64)
!1829 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1830, size: 64, align: 64)
!1830 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_un", file: !1831, line: 29, size: 880, align: 16, elements: !1832)
!1831 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/un.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1832 = !{!1833, !1834}
!1833 = !DIDerivedType(tag: DW_TAG_member, name: "sun_family", scope: !1830, file: !1831, line: 31, baseType: !689, size: 16, align: 16)
!1834 = !DIDerivedType(tag: DW_TAG_member, name: "sun_path", scope: !1830, file: !1831, line: 32, baseType: !1835, size: 864, align: 8, offset: 16)
!1835 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 864, align: 8, elements: !1836)
!1836 = !{!1837}
!1837 = !DISubrange(count: 108)
!1838 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1839, size: 64, align: 64)
!1839 = !DICompositeType(tag: DW_TAG_structure_type, name: "connfind", file: !1, line: 1197, size: 128, align: 64, elements: !1840)
!1840 = !{!1841, !1842}
!1841 = !DIDerivedType(tag: DW_TAG_member, name: "tofind", scope: !1839, file: !1, line: 1198, baseType: !262, size: 64, align: 64)
!1842 = !DIDerivedType(tag: DW_TAG_member, name: "found", scope: !1839, file: !1, line: 1199, baseType: !423, size: 8, align: 8, offset: 64)
!1843 = !{!1844, !1849, !1852, !1855, !1858, !1859, !1864, !1868, !1871, !1874, !1909, !1912, !1915, !1919, !1922, !1925, !1928, !1931, !1934}
!1844 = distinct !DISubprogram(name: "Curl_timeleft", scope: !1, file: !1, line: 182, type: !1845, isLocal: false, isDefinition: true, scopeLine: 185, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1845 = !DISubroutineType(types: !1846)
!1846 = !{!506, !256, !1847, !423}
!1847 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !411, size: 64, align: 64)
!1848 = !{}
!1849 = distinct !DISubprogram(name: "Curl_persistconninfo", scope: !1, file: !1, line: 600, type: !1850, isLocal: false, isDefinition: true, scopeLine: 601, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1850 = !DISubroutineType(types: !1851)
!1851 = !{null, !262}
!1852 = distinct !DISubprogram(name: "Curl_updateconninfo", scope: !1, file: !1, line: 663, type: !1853, isLocal: false, isDefinition: true, scopeLine: 664, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1853 = !DISubroutineType(types: !1854)
!1854 = !{null, !262, !315}
!1855 = distinct !DISubprogram(name: "Curl_is_connected", scope: !1, file: !1, line: 721, type: !1856, isLocal: false, isDefinition: true, scopeLine: 724, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1856 = !DISubroutineType(types: !1857)
!1857 = !{!289, !262, !316, !1423}
!1858 = distinct !DISubprogram(name: "Curl_tcpnodelay", scope: !1, file: !1, line: 873, type: !1853, isLocal: false, isDefinition: true, scopeLine: 874, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1859 = distinct !DISubprogram(name: "Curl_connecthost", scope: !1, file: !1, line: 1152, type: !1860, isLocal: false, isDefinition: true, scopeLine: 1154, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1860 = !DISubroutineType(types: !1861)
!1861 = !{!289, !262, !1862}
!1862 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1863, size: 64, align: 64)
!1863 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1273)
!1864 = distinct !DISubprogram(name: "Curl_getconnectinfo", scope: !1, file: !1, line: 1218, type: !1865, isLocal: false, isDefinition: true, scopeLine: 1220, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1865 = !DISubroutineType(types: !1866)
!1866 = !{!315, !256, !1867}
!1867 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !262, size: 64, align: 64)
!1868 = distinct !DISubprogram(name: "Curl_connalive", scope: !1, file: !1, line: 1259, type: !1869, isLocal: false, isDefinition: true, scopeLine: 1260, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1869 = !DISubroutineType(types: !1870)
!1870 = !{!423, !262}
!1871 = distinct !DISubprogram(name: "Curl_closesocket", scope: !1, file: !1, line: 1288, type: !1872, isLocal: false, isDefinition: true, scopeLine: 1290, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1872 = !DISubroutineType(types: !1873)
!1873 = !{!316, !262, !315}
!1874 = distinct !DISubprogram(name: "Curl_socket", scope: !1, file: !1, line: 1322, type: !1875, isLocal: false, isDefinition: true, scopeLine: 1326, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1875 = !DISubroutineType(types: !1876)
!1876 = !{!289, !262, !1877, !1879, !1442}
!1877 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1878, size: 64, align: 64)
!1878 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1278)
!1879 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1880, size: 64, align: 64)
!1880 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_sockaddr_ex", file: !1881, line: 86, size: 1152, align: 64, elements: !1882)
!1881 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/connect.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1882 = !{!1883, !1884, !1885, !1886, !1887}
!1883 = !DIDerivedType(tag: DW_TAG_member, name: "family", scope: !1880, file: !1881, line: 87, baseType: !316, size: 32, align: 32)
!1884 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !1880, file: !1881, line: 88, baseType: !316, size: 32, align: 32, offset: 32)
!1885 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !1880, file: !1881, line: 89, baseType: !316, size: 32, align: 32, offset: 64)
!1886 = !DIDerivedType(tag: DW_TAG_member, name: "addrlen", scope: !1880, file: !1881, line: 90, baseType: !683, size: 32, align: 32, offset: 96)
!1887 = !DIDerivedType(tag: DW_TAG_member, name: "_sa_ex_u", scope: !1880, file: !1881, line: 94, baseType: !1888, size: 1024, align: 64, offset: 128)
!1888 = !DICompositeType(tag: DW_TAG_union_type, scope: !1880, file: !1881, line: 91, size: 1024, align: 64, elements: !1889)
!1889 = !{!1890, !1891}
!1890 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !1888, file: !1881, line: 92, baseType: !685, size: 128, align: 16)
!1891 = !DIDerivedType(tag: DW_TAG_member, name: "buff", scope: !1888, file: !1881, line: 93, baseType: !1892, size: 1024, align: 64)
!1892 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_sockaddr_storage", file: !1893, line: 27, size: 1024, align: 64, elements: !1894)
!1893 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1894 = !{!1895}
!1895 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !1892, file: !1893, line: 39, baseType: !1896, size: 1024, align: 64)
!1896 = !DICompositeType(tag: DW_TAG_union_type, scope: !1892, file: !1893, line: 28, size: 1024, align: 64, elements: !1897)
!1897 = !{!1898, !1899, !1900}
!1898 = !DIDerivedType(tag: DW_TAG_member, name: "sa", scope: !1896, file: !1893, line: 29, baseType: !685, size: 128, align: 16)
!1899 = !DIDerivedType(tag: DW_TAG_member, name: "sa_in", scope: !1896, file: !1893, line: 30, baseType: !1815, size: 128, align: 32)
!1900 = !DIDerivedType(tag: DW_TAG_member, name: "sa_stor", scope: !1896, file: !1893, line: 35, baseType: !1901, size: 1024, align: 64)
!1901 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_storage", file: !686, line: 162, size: 1024, align: 64, elements: !1902)
!1902 = !{!1903, !1904, !1905}
!1903 = !DIDerivedType(tag: DW_TAG_member, name: "ss_family", scope: !1901, file: !686, line: 164, baseType: !689, size: 16, align: 16)
!1904 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_align", scope: !1901, file: !686, line: 165, baseType: !349, size: 64, align: 64, offset: 64)
!1905 = !DIDerivedType(tag: DW_TAG_member, name: "__ss_padding", scope: !1901, file: !686, line: 166, baseType: !1906, size: 896, align: 8, offset: 128)
!1906 = !DICompositeType(tag: DW_TAG_array_type, baseType: !480, size: 896, align: 8, elements: !1907)
!1907 = !{!1908}
!1908 = !DISubrange(count: 112)
!1909 = distinct !DISubprogram(name: "Curl_conncontrol", scope: !1, file: !1, line: 1386, type: !1910, isLocal: false, isDefinition: true, scopeLine: 1392, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1910 = !DISubroutineType(types: !1911)
!1911 = !{null, !262, !316}
!1912 = distinct !DISubprogram(name: "Curl_conn_data_pending", scope: !1, file: !1, line: 1408, type: !1913, isLocal: false, isDefinition: true, scopeLine: 1409, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1913 = !DISubroutineType(types: !1914)
!1914 = !{!423, !262, !316}
!1915 = distinct !DISubprogram(name: "getaddressinfo", scope: !1, file: !1, line: 611, type: !1916, isLocal: true, isDefinition: true, scopeLine: 613, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1916 = !DISubroutineType(types: !1917)
!1917 = !{!423, !1292, !479, !1918}
!1918 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !379, size: 64, align: 64)
!1919 = distinct !DISubprogram(name: "trynextip", scope: !1, file: !1, line: 540, type: !1920, isLocal: true, isDefinition: true, scopeLine: 543, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1920 = !DISubroutineType(types: !1921)
!1921 = !{!289, !262, !316, !316}
!1922 = distinct !DISubprogram(name: "verifyconnect", scope: !1, file: !1, line: 474, type: !1923, isLocal: true, isDefinition: true, scopeLine: 475, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1923 = !DISubroutineType(types: !1924)
!1924 = !{!423, !315, !1434}
!1925 = distinct !DISubprogram(name: "singleipconnect", scope: !1, file: !1, line: 983, type: !1926, isLocal: true, isDefinition: true, scopeLine: 986, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1926 = !DISubroutineType(types: !1927)
!1927 = !{!289, !262, !1877, !1442}
!1928 = distinct !DISubprogram(name: "tcpkeepalive", scope: !1, file: !1, line: 107, type: !1929, isLocal: true, isDefinition: true, scopeLine: 109, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1929 = !DISubroutineType(types: !1930)
!1930 = !{null, !256, !315}
!1931 = distinct !DISubprogram(name: "bindlocal", scope: !1, file: !1, line: 239, type: !1932, isLocal: true, isDefinition: true, scopeLine: 241, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1932 = !DISubroutineType(types: !1933)
!1933 = !{!289, !262, !315, !316, !683}
!1934 = distinct !DISubprogram(name: "conn_is_conn", scope: !1, file: !1, line: 1202, type: !1935, isLocal: true, isDefinition: true, scopeLine: 1203, flags: DIFlagPrototyped, isOptimized: false, variables: !1848)
!1935 = !DISubroutineType(types: !1936)
!1936 = !{!316, !262, !311}
!1937 = !{!1938, !1939}
!1938 = !DIGlobalVariable(name: "if_prefix", scope: !1931, file: !1, line: 274, type: !851, isLocal: true, isDefinition: true, variable: i8** @bindlocal.if_prefix)
!1939 = !DIGlobalVariable(name: "host_prefix", scope: !1931, file: !1, line: 275, type: !851, isLocal: true, isDefinition: true, variable: i8** @bindlocal.host_prefix)
!1940 = !{i32 2, !"Dwarf Version", i32 4}
!1941 = !{i32 2, !"Debug Info Version", i32 3}
!1942 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!1943 = !DILocalVariable(name: "data", arg: 1, scope: !1844, file: !1, line: 182, type: !256)
!1944 = !DIExpression()
!1945 = !DILocation(line: 182, column: 40, scope: !1844)
!1946 = !DILocalVariable(name: "nowp", arg: 2, scope: !1844, file: !1, line: 183, type: !1847)
!1947 = !DILocation(line: 183, column: 38, scope: !1844)
!1948 = !DILocalVariable(name: "duringconnect", arg: 3, scope: !1844, file: !1, line: 184, type: !423)
!1949 = !DILocation(line: 184, column: 27, scope: !1844)
!1950 = !DILocalVariable(name: "timeout_set", scope: !1844, file: !1, line: 186, type: !316)
!1951 = !DILocation(line: 186, column: 7, scope: !1844)
!1952 = !DILocalVariable(name: "timeout_ms", scope: !1844, file: !1, line: 187, type: !506)
!1953 = !DILocation(line: 187, column: 10, scope: !1844)
!1954 = !DILocation(line: 187, column: 23, scope: !1844)
!1955 = !DILocalVariable(name: "now", scope: !1844, file: !1, line: 188, type: !411)
!1956 = !DILocation(line: 188, column: 18, scope: !1844)
!1957 = !DILocation(line: 192, column: 6, scope: !1958)
!1958 = distinct !DILexicalBlock(scope: !1844, file: !1, line: 192, column: 6)
!1959 = !DILocation(line: 192, column: 12, scope: !1958)
!1960 = !DILocation(line: 192, column: 16, scope: !1958)
!1961 = !DILocation(line: 192, column: 24, scope: !1958)
!1962 = !DILocation(line: 192, column: 6, scope: !1844)
!1963 = !DILocation(line: 193, column: 17, scope: !1958)
!1964 = !DILocation(line: 193, column: 5, scope: !1958)
!1965 = !DILocation(line: 194, column: 6, scope: !1966)
!1966 = distinct !DILexicalBlock(scope: !1844, file: !1, line: 194, column: 6)
!1967 = !DILocation(line: 194, column: 20, scope: !1966)
!1968 = !DILocation(line: 194, column: 24, scope: !1969)
!1969 = !DILexicalBlockFile(scope: !1966, file: !1, discriminator: 1)
!1970 = !DILocation(line: 194, column: 30, scope: !1969)
!1971 = !DILocation(line: 194, column: 34, scope: !1969)
!1972 = !DILocation(line: 194, column: 49, scope: !1969)
!1973 = !DILocation(line: 194, column: 6, scope: !1969)
!1974 = !DILocation(line: 195, column: 17, scope: !1966)
!1975 = !DILocation(line: 195, column: 5, scope: !1966)
!1976 = !DILocation(line: 197, column: 10, scope: !1844)
!1977 = !DILocation(line: 197, column: 3, scope: !1844)
!1978 = !DILocation(line: 199, column: 18, scope: !1979)
!1979 = distinct !DILexicalBlock(scope: !1844, file: !1, line: 197, column: 23)
!1980 = !DILocation(line: 199, column: 24, scope: !1979)
!1981 = !DILocation(line: 199, column: 28, scope: !1979)
!1982 = !DILocation(line: 199, column: 16, scope: !1979)
!1983 = !DILocation(line: 200, column: 5, scope: !1979)
!1984 = !DILocation(line: 202, column: 18, scope: !1979)
!1985 = !DILocation(line: 202, column: 24, scope: !1979)
!1986 = !DILocation(line: 202, column: 28, scope: !1979)
!1987 = !DILocation(line: 202, column: 16, scope: !1979)
!1988 = !DILocation(line: 203, column: 5, scope: !1979)
!1989 = !DILocation(line: 205, column: 8, scope: !1990)
!1990 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 205, column: 8)
!1991 = !DILocation(line: 205, column: 14, scope: !1990)
!1992 = !DILocation(line: 205, column: 18, scope: !1990)
!1993 = !DILocation(line: 205, column: 28, scope: !1990)
!1994 = !DILocation(line: 205, column: 34, scope: !1990)
!1995 = !DILocation(line: 205, column: 38, scope: !1990)
!1996 = !DILocation(line: 205, column: 26, scope: !1990)
!1997 = !DILocation(line: 205, column: 8, scope: !1979)
!1998 = !DILocation(line: 206, column: 20, scope: !1990)
!1999 = !DILocation(line: 206, column: 26, scope: !1990)
!2000 = !DILocation(line: 206, column: 30, scope: !1990)
!2001 = !DILocation(line: 206, column: 18, scope: !1990)
!2002 = !DILocation(line: 206, column: 7, scope: !1990)
!2003 = !DILocation(line: 208, column: 20, scope: !1990)
!2004 = !DILocation(line: 208, column: 26, scope: !1990)
!2005 = !DILocation(line: 208, column: 30, scope: !1990)
!2006 = !DILocation(line: 208, column: 18, scope: !1990)
!2007 = !DILocation(line: 209, column: 5, scope: !1979)
!2008 = !DILocation(line: 212, column: 9, scope: !2009)
!2009 = distinct !DILexicalBlock(scope: !1979, file: !1, line: 212, column: 8)
!2010 = !DILocation(line: 212, column: 8, scope: !1979)
!2011 = !DILocation(line: 216, column: 7, scope: !2009)
!2012 = !DILocation(line: 217, column: 5, scope: !1979)
!2013 = !DILocation(line: 220, column: 7, scope: !2014)
!2014 = distinct !DILexicalBlock(scope: !1844, file: !1, line: 220, column: 6)
!2015 = !DILocation(line: 220, column: 6, scope: !1844)
!2016 = !DILocation(line: 221, column: 11, scope: !2017)
!2017 = distinct !DILexicalBlock(scope: !2014, file: !1, line: 220, column: 13)
!2018 = !DILocation(line: 221, column: 11, scope: !2019)
!2019 = !DILexicalBlockFile(scope: !2017, file: !1, discriminator: 1)
!2020 = !DILocation(line: 222, column: 10, scope: !2017)
!2021 = !DILocation(line: 223, column: 3, scope: !2017)
!2022 = !DILocation(line: 226, column: 6, scope: !2023)
!2023 = distinct !DILexicalBlock(scope: !1844, file: !1, line: 226, column: 6)
!2024 = !DILocation(line: 226, column: 6, scope: !1844)
!2025 = !DILocation(line: 228, column: 19, scope: !2023)
!2026 = !DILocation(line: 228, column: 16, scope: !2023)
!2027 = !DILocation(line: 228, column: 5, scope: !2023)
!2028 = !DILocation(line: 231, column: 19, scope: !2023)
!2029 = !DILocation(line: 231, column: 16, scope: !2023)
!2030 = !DILocation(line: 232, column: 7, scope: !2031)
!2031 = distinct !DILexicalBlock(scope: !1844, file: !1, line: 232, column: 6)
!2032 = !DILocation(line: 232, column: 6, scope: !1844)
!2033 = !DILocation(line: 234, column: 5, scope: !2031)
!2034 = !DILocation(line: 236, column: 10, scope: !1844)
!2035 = !DILocation(line: 236, column: 3, scope: !1844)
!2036 = !DILocation(line: 237, column: 1, scope: !1844)
!2037 = !DILocalVariable(name: "conn", arg: 1, scope: !1849, file: !1, line: 600, type: !262)
!2038 = !DILocation(line: 600, column: 47, scope: !1849)
!2039 = !DILocation(line: 602, column: 10, scope: !1849)
!2040 = !DILocation(line: 602, column: 16, scope: !1849)
!2041 = !DILocation(line: 602, column: 22, scope: !1849)
!2042 = !DILocation(line: 602, column: 27, scope: !1849)
!2043 = !DILocation(line: 602, column: 3, scope: !1849)
!2044 = !DILocation(line: 602, column: 44, scope: !1849)
!2045 = !DILocation(line: 602, column: 50, scope: !1849)
!2046 = !DILocation(line: 603, column: 10, scope: !1849)
!2047 = !DILocation(line: 603, column: 16, scope: !1849)
!2048 = !DILocation(line: 603, column: 22, scope: !1849)
!2049 = !DILocation(line: 603, column: 27, scope: !1849)
!2050 = !DILocation(line: 603, column: 3, scope: !1849)
!2051 = !DILocation(line: 603, column: 42, scope: !1849)
!2052 = !DILocation(line: 603, column: 48, scope: !1849)
!2053 = !DILocation(line: 604, column: 34, scope: !1849)
!2054 = !DILocation(line: 604, column: 40, scope: !1849)
!2055 = !DILocation(line: 604, column: 49, scope: !1849)
!2056 = !DILocation(line: 604, column: 3, scope: !1849)
!2057 = !DILocation(line: 604, column: 9, scope: !1849)
!2058 = !DILocation(line: 604, column: 15, scope: !1849)
!2059 = !DILocation(line: 604, column: 20, scope: !1849)
!2060 = !DILocation(line: 604, column: 32, scope: !1849)
!2061 = !DILocation(line: 605, column: 36, scope: !1849)
!2062 = !DILocation(line: 605, column: 42, scope: !1849)
!2063 = !DILocation(line: 605, column: 51, scope: !1849)
!2064 = !DILocation(line: 605, column: 3, scope: !1849)
!2065 = !DILocation(line: 605, column: 9, scope: !1849)
!2066 = !DILocation(line: 605, column: 15, scope: !1849)
!2067 = !DILocation(line: 605, column: 20, scope: !1849)
!2068 = !DILocation(line: 605, column: 34, scope: !1849)
!2069 = !DILocation(line: 606, column: 40, scope: !1849)
!2070 = !DILocation(line: 606, column: 46, scope: !1849)
!2071 = !DILocation(line: 606, column: 3, scope: !1849)
!2072 = !DILocation(line: 606, column: 9, scope: !1849)
!2073 = !DILocation(line: 606, column: 15, scope: !1849)
!2074 = !DILocation(line: 606, column: 20, scope: !1849)
!2075 = !DILocation(line: 606, column: 38, scope: !1849)
!2076 = !DILocation(line: 607, column: 38, scope: !1849)
!2077 = !DILocation(line: 607, column: 44, scope: !1849)
!2078 = !DILocation(line: 607, column: 3, scope: !1849)
!2079 = !DILocation(line: 607, column: 9, scope: !1849)
!2080 = !DILocation(line: 607, column: 15, scope: !1849)
!2081 = !DILocation(line: 607, column: 20, scope: !1849)
!2082 = !DILocation(line: 607, column: 36, scope: !1849)
!2083 = !DILocation(line: 608, column: 1, scope: !1849)
!2084 = !DILocalVariable(name: "conn", arg: 1, scope: !1852, file: !1, line: 663, type: !262)
!2085 = !DILocation(line: 663, column: 46, scope: !1852)
!2086 = !DILocalVariable(name: "sockfd", arg: 2, scope: !1852, file: !1, line: 663, type: !315)
!2087 = !DILocation(line: 663, column: 66, scope: !1852)
!2088 = !DILocalVariable(name: "len", scope: !1852, file: !1, line: 665, type: !1287)
!2089 = !DILocation(line: 665, column: 18, scope: !1852)
!2090 = !DILocalVariable(name: "ssrem", scope: !1852, file: !1, line: 666, type: !1892)
!2091 = !DILocation(line: 666, column: 32, scope: !1852)
!2092 = !DILocalVariable(name: "ssloc", scope: !1852, file: !1, line: 667, type: !1892)
!2093 = !DILocation(line: 667, column: 32, scope: !1852)
!2094 = !DILocalVariable(name: "data", scope: !1852, file: !1, line: 668, type: !256)
!2095 = !DILocation(line: 668, column: 21, scope: !1852)
!2096 = !DILocation(line: 668, column: 28, scope: !1852)
!2097 = !DILocation(line: 668, column: 34, scope: !1852)
!2098 = !DILocation(line: 670, column: 6, scope: !2099)
!2099 = distinct !DILexicalBlock(scope: !1852, file: !1, line: 670, column: 6)
!2100 = !DILocation(line: 670, column: 12, scope: !2099)
!2101 = !DILocation(line: 670, column: 21, scope: !2099)
!2102 = !DILocation(line: 670, column: 6, scope: !1852)
!2103 = !DILocation(line: 672, column: 5, scope: !2099)
!2104 = !DILocation(line: 674, column: 7, scope: !2105)
!2105 = distinct !DILexicalBlock(scope: !1852, file: !1, line: 674, column: 6)
!2106 = !DILocation(line: 674, column: 13, scope: !2105)
!2107 = !DILocation(line: 674, column: 18, scope: !2105)
!2108 = !DILocation(line: 674, column: 24, scope: !2105)
!2109 = !DILocation(line: 674, column: 28, scope: !2110)
!2110 = !DILexicalBlockFile(scope: !2105, file: !1, discriminator: 1)
!2111 = !DILocation(line: 674, column: 34, scope: !2110)
!2112 = !DILocation(line: 674, column: 39, scope: !2110)
!2113 = !DILocation(line: 674, column: 6, scope: !2110)
!2114 = !DILocalVariable(name: "error", scope: !2115, file: !1, line: 675, type: !316)
!2115 = distinct !DILexicalBlock(scope: !2105, file: !1, line: 674, column: 53)
!2116 = !DILocation(line: 675, column: 9, scope: !2115)
!2117 = !DILocation(line: 677, column: 9, scope: !2115)
!2118 = !DILocation(line: 678, column: 20, scope: !2119)
!2119 = distinct !DILexicalBlock(scope: !2115, file: !1, line: 678, column: 8)
!2120 = !DILocation(line: 678, column: 28, scope: !2119)
!2121 = !DILocation(line: 678, column: 8, scope: !2119)
!2122 = !DILocation(line: 678, column: 8, scope: !2115)
!2123 = !DILocation(line: 679, column: 15, scope: !2124)
!2124 = distinct !DILexicalBlock(scope: !2119, file: !1, line: 678, column: 62)
!2125 = !DILocation(line: 679, column: 13, scope: !2124)
!2126 = !DILocation(line: 680, column: 13, scope: !2124)
!2127 = !DILocation(line: 681, column: 13, scope: !2124)
!2128 = !DILocation(line: 681, column: 34, scope: !2124)
!2129 = !DILocation(line: 681, column: 40, scope: !2124)
!2130 = !DILocation(line: 681, column: 20, scope: !2124)
!2131 = !DILocation(line: 680, column: 7, scope: !2124)
!2132 = !DILocation(line: 682, column: 7, scope: !2124)
!2133 = !DILocation(line: 685, column: 9, scope: !2115)
!2134 = !DILocation(line: 686, column: 5, scope: !2115)
!2135 = !DILocation(line: 687, column: 20, scope: !2136)
!2136 = distinct !DILexicalBlock(scope: !2115, file: !1, line: 687, column: 8)
!2137 = !DILocation(line: 687, column: 28, scope: !2136)
!2138 = !DILocation(line: 687, column: 8, scope: !2136)
!2139 = !DILocation(line: 687, column: 8, scope: !2115)
!2140 = !DILocation(line: 688, column: 15, scope: !2141)
!2141 = distinct !DILexicalBlock(scope: !2136, file: !1, line: 687, column: 62)
!2142 = !DILocation(line: 688, column: 13, scope: !2141)
!2143 = !DILocation(line: 689, column: 13, scope: !2141)
!2144 = !DILocation(line: 690, column: 13, scope: !2141)
!2145 = !DILocation(line: 690, column: 34, scope: !2141)
!2146 = !DILocation(line: 690, column: 40, scope: !2141)
!2147 = !DILocation(line: 690, column: 20, scope: !2141)
!2148 = !DILocation(line: 689, column: 7, scope: !2141)
!2149 = !DILocation(line: 691, column: 7, scope: !2141)
!2150 = !DILocation(line: 694, column: 24, scope: !2151)
!2151 = distinct !DILexicalBlock(scope: !2115, file: !1, line: 694, column: 8)
!2152 = !DILocation(line: 695, column: 25, scope: !2151)
!2153 = !DILocation(line: 695, column: 31, scope: !2151)
!2154 = !DILocation(line: 695, column: 44, scope: !2151)
!2155 = !DILocation(line: 695, column: 50, scope: !2151)
!2156 = !DILocation(line: 694, column: 9, scope: !2151)
!2157 = !DILocation(line: 694, column: 8, scope: !2115)
!2158 = !DILocation(line: 696, column: 15, scope: !2159)
!2159 = distinct !DILexicalBlock(scope: !2151, file: !1, line: 695, column: 65)
!2160 = !DILocation(line: 696, column: 13, scope: !2159)
!2161 = !DILocation(line: 697, column: 13, scope: !2159)
!2162 = !DILocation(line: 698, column: 13, scope: !2159)
!2163 = !DILocation(line: 698, column: 34, scope: !2159)
!2164 = !DILocation(line: 698, column: 40, scope: !2159)
!2165 = !DILocation(line: 698, column: 20, scope: !2159)
!2166 = !DILocation(line: 697, column: 7, scope: !2159)
!2167 = !DILocation(line: 699, column: 7, scope: !2159)
!2168 = !DILocation(line: 701, column: 12, scope: !2115)
!2169 = !DILocation(line: 701, column: 18, scope: !2115)
!2170 = !DILocation(line: 701, column: 5, scope: !2115)
!2171 = !DILocation(line: 701, column: 31, scope: !2115)
!2172 = !DILocation(line: 701, column: 37, scope: !2115)
!2173 = !DILocation(line: 703, column: 24, scope: !2174)
!2174 = distinct !DILexicalBlock(scope: !2115, file: !1, line: 703, column: 8)
!2175 = !DILocation(line: 704, column: 24, scope: !2174)
!2176 = !DILocation(line: 704, column: 30, scope: !2174)
!2177 = !DILocation(line: 704, column: 41, scope: !2174)
!2178 = !DILocation(line: 704, column: 47, scope: !2174)
!2179 = !DILocation(line: 703, column: 9, scope: !2174)
!2180 = !DILocation(line: 703, column: 8, scope: !2115)
!2181 = !DILocation(line: 705, column: 15, scope: !2182)
!2182 = distinct !DILexicalBlock(scope: !2174, file: !1, line: 704, column: 60)
!2183 = !DILocation(line: 705, column: 13, scope: !2182)
!2184 = !DILocation(line: 706, column: 13, scope: !2182)
!2185 = !DILocation(line: 707, column: 13, scope: !2182)
!2186 = !DILocation(line: 707, column: 34, scope: !2182)
!2187 = !DILocation(line: 707, column: 40, scope: !2182)
!2188 = !DILocation(line: 707, column: 20, scope: !2182)
!2189 = !DILocation(line: 706, column: 7, scope: !2182)
!2190 = !DILocation(line: 708, column: 7, scope: !2182)
!2191 = !DILocation(line: 711, column: 3, scope: !2115)
!2192 = !DILocation(line: 714, column: 24, scope: !1852)
!2193 = !DILocation(line: 714, column: 3, scope: !1852)
!2194 = !DILocation(line: 715, column: 1, scope: !1852)
!2195 = !DILocation(line: 715, column: 1, scope: !2196)
!2196 = !DILexicalBlockFile(scope: !1852, file: !1, discriminator: 1)
!2197 = !DILocalVariable(name: "sa", arg: 1, scope: !1915, file: !1, line: 611, type: !1292)
!2198 = !DILocation(line: 611, column: 45, scope: !1915)
!2199 = !DILocalVariable(name: "addr", arg: 2, scope: !1915, file: !1, line: 611, type: !479)
!2200 = !DILocation(line: 611, column: 55, scope: !1915)
!2201 = !DILocalVariable(name: "port", arg: 3, scope: !1915, file: !1, line: 612, type: !1918)
!2202 = !DILocation(line: 612, column: 34, scope: !1915)
!2203 = !DILocalVariable(name: "us_port", scope: !1915, file: !1, line: 614, type: !564)
!2204 = !DILocation(line: 614, column: 18, scope: !1915)
!2205 = !DILocalVariable(name: "si", scope: !1915, file: !1, line: 615, type: !1814)
!2206 = !DILocation(line: 615, column: 23, scope: !1915)
!2207 = !DILocalVariable(name: "su", scope: !1915, file: !1, line: 620, type: !1829)
!2208 = !DILocation(line: 620, column: 23, scope: !1915)
!2209 = !DILocation(line: 623, column: 10, scope: !1915)
!2210 = !DILocation(line: 623, column: 14, scope: !1915)
!2211 = !DILocation(line: 623, column: 3, scope: !1915)
!2212 = !DILocation(line: 625, column: 43, scope: !2213)
!2213 = distinct !DILexicalBlock(scope: !1915, file: !1, line: 623, column: 25)
!2214 = !DILocation(line: 625, column: 34, scope: !2213)
!2215 = !DILocation(line: 625, column: 12, scope: !2213)
!2216 = !DILocation(line: 625, column: 10, scope: !2213)
!2217 = !DILocation(line: 626, column: 25, scope: !2218)
!2218 = distinct !DILexicalBlock(scope: !2213, file: !1, line: 626, column: 10)
!2219 = !DILocation(line: 626, column: 29, scope: !2218)
!2220 = !DILocation(line: 626, column: 41, scope: !2218)
!2221 = !DILocation(line: 626, column: 45, scope: !2218)
!2222 = !DILocation(line: 626, column: 40, scope: !2218)
!2223 = !DILocation(line: 627, column: 25, scope: !2218)
!2224 = !DILocation(line: 626, column: 10, scope: !2218)
!2225 = !DILocation(line: 626, column: 10, scope: !2213)
!2226 = !DILocation(line: 628, column: 25, scope: !2227)
!2227 = distinct !DILexicalBlock(scope: !2218, file: !1, line: 627, column: 47)
!2228 = !DILocation(line: 628, column: 29, scope: !2227)
!2229 = !DILocation(line: 628, column: 19, scope: !2227)
!2230 = !DILocation(line: 628, column: 17, scope: !2227)
!2231 = !DILocation(line: 629, column: 17, scope: !2227)
!2232 = !DILocation(line: 629, column: 10, scope: !2227)
!2233 = !DILocation(line: 629, column: 15, scope: !2227)
!2234 = !DILocation(line: 630, column: 9, scope: !2227)
!2235 = !DILocation(line: 632, column: 7, scope: !2213)
!2236 = !DILocation(line: 646, column: 33, scope: !2213)
!2237 = !DILocation(line: 646, column: 12, scope: !2213)
!2238 = !DILocation(line: 646, column: 10, scope: !2213)
!2239 = !DILocation(line: 647, column: 16, scope: !2213)
!2240 = !DILocation(line: 647, column: 43, scope: !2213)
!2241 = !DILocation(line: 647, column: 47, scope: !2213)
!2242 = !DILocation(line: 647, column: 7, scope: !2213)
!2243 = !DILocation(line: 648, column: 8, scope: !2213)
!2244 = !DILocation(line: 648, column: 13, scope: !2213)
!2245 = !DILocation(line: 649, column: 7, scope: !2213)
!2246 = !DILocation(line: 652, column: 7, scope: !2213)
!2247 = !DILocation(line: 655, column: 3, scope: !1915)
!2248 = !DILocation(line: 655, column: 11, scope: !1915)
!2249 = !DILocation(line: 656, column: 4, scope: !1915)
!2250 = !DILocation(line: 656, column: 9, scope: !1915)
!2251 = !DILocation(line: 658, column: 3, scope: !1915)
!2252 = !DILocation(line: 659, column: 1, scope: !1915)
!2253 = !DILocalVariable(name: "conn", arg: 1, scope: !1855, file: !1, line: 721, type: !262)
!2254 = !DILocation(line: 721, column: 48, scope: !1855)
!2255 = !DILocalVariable(name: "sockindex", arg: 2, scope: !1855, file: !1, line: 722, type: !316)
!2256 = !DILocation(line: 722, column: 32, scope: !1855)
!2257 = !DILocalVariable(name: "connected", arg: 3, scope: !1855, file: !1, line: 723, type: !1423)
!2258 = !DILocation(line: 723, column: 34, scope: !1855)
!2259 = !DILocalVariable(name: "data", scope: !1855, file: !1, line: 725, type: !256)
!2260 = !DILocation(line: 725, column: 21, scope: !1855)
!2261 = !DILocation(line: 725, column: 28, scope: !1855)
!2262 = !DILocation(line: 725, column: 34, scope: !1855)
!2263 = !DILocalVariable(name: "result", scope: !1855, file: !1, line: 726, type: !289)
!2264 = !DILocation(line: 726, column: 12, scope: !1855)
!2265 = !DILocalVariable(name: "allow", scope: !1855, file: !1, line: 727, type: !506)
!2266 = !DILocation(line: 727, column: 10, scope: !1855)
!2267 = !DILocalVariable(name: "error", scope: !1855, file: !1, line: 728, type: !316)
!2268 = !DILocation(line: 728, column: 7, scope: !1855)
!2269 = !DILocalVariable(name: "now", scope: !1855, file: !1, line: 729, type: !411)
!2270 = !DILocation(line: 729, column: 18, scope: !1855)
!2271 = !DILocalVariable(name: "rc", scope: !1855, file: !1, line: 730, type: !316)
!2272 = !DILocation(line: 730, column: 7, scope: !1855)
!2273 = !DILocalVariable(name: "i", scope: !1855, file: !1, line: 731, type: !316)
!2274 = !DILocation(line: 731, column: 7, scope: !1855)
!2275 = !DILocation(line: 733, column: 3, scope: !1855)
!2276 = !DILocation(line: 733, column: 3, scope: !2277)
!2277 = !DILexicalBlockFile(scope: !2278, file: !1, discriminator: 1)
!2278 = distinct !DILexicalBlock(scope: !1855, file: !1, line: 733, column: 3)
!2279 = !DILocation(line: 735, column: 4, scope: !1855)
!2280 = !DILocation(line: 735, column: 14, scope: !1855)
!2281 = !DILocation(line: 737, column: 28, scope: !2282)
!2282 = distinct !DILexicalBlock(scope: !1855, file: !1, line: 737, column: 6)
!2283 = !DILocation(line: 737, column: 6, scope: !2282)
!2284 = !DILocation(line: 737, column: 12, scope: !2282)
!2285 = !DILocation(line: 737, column: 17, scope: !2282)
!2286 = !DILocation(line: 737, column: 6, scope: !1855)
!2287 = !DILocation(line: 739, column: 6, scope: !2288)
!2288 = distinct !DILexicalBlock(scope: !2282, file: !1, line: 737, column: 40)
!2289 = !DILocation(line: 739, column: 16, scope: !2288)
!2290 = !DILocation(line: 740, column: 5, scope: !2288)
!2291 = !DILocation(line: 743, column: 9, scope: !1855)
!2292 = !DILocation(line: 743, column: 9, scope: !2293)
!2293 = !DILexicalBlockFile(scope: !1855, file: !1, discriminator: 1)
!2294 = !DILocation(line: 746, column: 25, scope: !1855)
!2295 = !DILocation(line: 746, column: 11, scope: !1855)
!2296 = !DILocation(line: 746, column: 9, scope: !1855)
!2297 = !DILocation(line: 748, column: 6, scope: !2298)
!2298 = distinct !DILexicalBlock(scope: !1855, file: !1, line: 748, column: 6)
!2299 = !DILocation(line: 748, column: 12, scope: !2298)
!2300 = !DILocation(line: 748, column: 6, scope: !1855)
!2301 = !DILocation(line: 750, column: 11, scope: !2302)
!2302 = distinct !DILexicalBlock(scope: !2298, file: !1, line: 748, column: 17)
!2303 = !DILocation(line: 750, column: 5, scope: !2302)
!2304 = !DILocation(line: 751, column: 5, scope: !2302)
!2305 = !DILocation(line: 754, column: 8, scope: !2306)
!2306 = distinct !DILexicalBlock(scope: !1855, file: !1, line: 754, column: 3)
!2307 = !DILocation(line: 754, column: 7, scope: !2306)
!2308 = !DILocation(line: 754, column: 12, scope: !2309)
!2309 = !DILexicalBlockFile(scope: !2310, file: !1, discriminator: 1)
!2310 = distinct !DILexicalBlock(scope: !2306, file: !1, line: 754, column: 3)
!2311 = !DILocation(line: 754, column: 13, scope: !2309)
!2312 = !DILocation(line: 754, column: 3, scope: !2309)
!2313 = !DILocalVariable(name: "other", scope: !2314, file: !1, line: 755, type: !2315)
!2314 = distinct !DILexicalBlock(scope: !2310, file: !1, line: 754, column: 22)
!2315 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !316)
!2316 = !DILocation(line: 755, column: 15, scope: !2314)
!2317 = !DILocation(line: 755, column: 23, scope: !2314)
!2318 = !DILocation(line: 755, column: 25, scope: !2314)
!2319 = !DILocation(line: 756, column: 23, scope: !2320)
!2320 = distinct !DILexicalBlock(scope: !2314, file: !1, line: 756, column: 8)
!2321 = !DILocation(line: 756, column: 8, scope: !2320)
!2322 = !DILocation(line: 756, column: 14, scope: !2320)
!2323 = !DILocation(line: 756, column: 26, scope: !2320)
!2324 = !DILocation(line: 756, column: 8, scope: !2314)
!2325 = !DILocation(line: 757, column: 7, scope: !2320)
!2326 = !DILocation(line: 767, column: 10, scope: !2314)
!2327 = !DILocation(line: 767, column: 8, scope: !2314)
!2328 = !DILocation(line: 769, column: 8, scope: !2329)
!2329 = distinct !DILexicalBlock(scope: !2314, file: !1, line: 769, column: 8)
!2330 = !DILocation(line: 769, column: 11, scope: !2329)
!2331 = !DILocation(line: 769, column: 8, scope: !2314)
!2332 = !DILocation(line: 770, column: 13, scope: !2333)
!2333 = distinct !DILexicalBlock(scope: !2329, file: !1, line: 769, column: 17)
!2334 = !DILocation(line: 771, column: 28, scope: !2335)
!2335 = distinct !DILexicalBlock(scope: !2333, file: !1, line: 771, column: 10)
!2336 = !DILocation(line: 771, column: 34, scope: !2335)
!2337 = !DILocation(line: 771, column: 10, scope: !2335)
!2338 = !DILocation(line: 771, column: 50, scope: !2335)
!2339 = !DILocation(line: 771, column: 56, scope: !2335)
!2340 = !DILocation(line: 771, column: 47, scope: !2335)
!2341 = !DILocation(line: 771, column: 10, scope: !2333)
!2342 = !DILocation(line: 772, column: 15, scope: !2343)
!2343 = distinct !DILexicalBlock(scope: !2335, file: !1, line: 771, column: 76)
!2344 = !DILocation(line: 773, column: 15, scope: !2343)
!2345 = !DILocation(line: 773, column: 21, scope: !2343)
!2346 = !DILocation(line: 772, column: 9, scope: !2343)
!2347 = !DILocation(line: 774, column: 15, scope: !2343)
!2348 = !DILocation(line: 775, column: 7, scope: !2343)
!2349 = !DILocation(line: 778, column: 10, scope: !2350)
!2350 = distinct !DILexicalBlock(scope: !2333, file: !1, line: 778, column: 10)
!2351 = !DILocation(line: 778, column: 12, scope: !2350)
!2352 = !DILocation(line: 778, column: 17, scope: !2350)
!2353 = !DILocation(line: 778, column: 20, scope: !2354)
!2354 = !DILexicalBlockFile(scope: !2350, file: !1, discriminator: 1)
!2355 = !DILocation(line: 778, column: 26, scope: !2354)
!2356 = !DILocation(line: 778, column: 38, scope: !2354)
!2357 = !DILocation(line: 778, column: 46, scope: !2354)
!2358 = !DILocation(line: 779, column: 28, scope: !2350)
!2359 = !DILocation(line: 779, column: 34, scope: !2350)
!2360 = !DILocation(line: 779, column: 10, scope: !2350)
!2361 = !DILocation(line: 779, column: 47, scope: !2350)
!2362 = !DILocation(line: 778, column: 10, scope: !2363)
!2363 = !DILexicalBlockFile(scope: !2333, file: !1, discriminator: 2)
!2364 = !DILocation(line: 780, column: 19, scope: !2365)
!2365 = distinct !DILexicalBlock(scope: !2350, file: !1, line: 779, column: 74)
!2366 = !DILocation(line: 780, column: 25, scope: !2365)
!2367 = !DILocation(line: 780, column: 9, scope: !2365)
!2368 = !DILocation(line: 781, column: 7, scope: !2365)
!2369 = !DILocation(line: 782, column: 5, scope: !2333)
!2370 = !DILocation(line: 783, column: 13, scope: !2371)
!2371 = distinct !DILexicalBlock(scope: !2329, file: !1, line: 783, column: 13)
!2372 = !DILocation(line: 783, column: 16, scope: !2371)
!2373 = !DILocation(line: 783, column: 36, scope: !2371)
!2374 = !DILocation(line: 783, column: 39, scope: !2375)
!2375 = !DILexicalBlockFile(scope: !2371, file: !1, discriminator: 1)
!2376 = !DILocation(line: 783, column: 45, scope: !2375)
!2377 = !DILocation(line: 783, column: 50, scope: !2375)
!2378 = !DILocation(line: 783, column: 13, scope: !2375)
!2379 = !DILocation(line: 784, column: 39, scope: !2380)
!2380 = distinct !DILexicalBlock(scope: !2381, file: !1, line: 784, column: 10)
!2381 = distinct !DILexicalBlock(scope: !2371, file: !1, line: 783, column: 64)
!2382 = !DILocation(line: 784, column: 24, scope: !2380)
!2383 = !DILocation(line: 784, column: 30, scope: !2380)
!2384 = !DILocation(line: 784, column: 10, scope: !2380)
!2385 = !DILocation(line: 784, column: 10, scope: !2381)
!2386 = !DILocation(line: 788, column: 48, scope: !2387)
!2387 = distinct !DILexicalBlock(scope: !2380, file: !1, line: 784, column: 52)
!2388 = !DILocation(line: 788, column: 33, scope: !2387)
!2389 = !DILocation(line: 788, column: 39, scope: !2387)
!2390 = !DILocation(line: 788, column: 20, scope: !2387)
!2391 = !DILocation(line: 788, column: 9, scope: !2387)
!2392 = !DILocation(line: 788, column: 15, scope: !2387)
!2393 = !DILocation(line: 788, column: 31, scope: !2387)
!2394 = !DILocation(line: 789, column: 40, scope: !2387)
!2395 = !DILocation(line: 789, column: 25, scope: !2387)
!2396 = !DILocation(line: 789, column: 31, scope: !2387)
!2397 = !DILocation(line: 789, column: 9, scope: !2387)
!2398 = !DILocation(line: 789, column: 15, scope: !2387)
!2399 = !DILocation(line: 789, column: 23, scope: !2387)
!2400 = !DILocation(line: 790, column: 24, scope: !2387)
!2401 = !DILocation(line: 790, column: 9, scope: !2387)
!2402 = !DILocation(line: 790, column: 15, scope: !2387)
!2403 = !DILocation(line: 790, column: 27, scope: !2387)
!2404 = !DILocation(line: 793, column: 27, scope: !2405)
!2405 = distinct !DILexicalBlock(scope: !2387, file: !1, line: 793, column: 12)
!2406 = !DILocation(line: 793, column: 12, scope: !2405)
!2407 = !DILocation(line: 793, column: 18, scope: !2405)
!2408 = !DILocation(line: 793, column: 34, scope: !2405)
!2409 = !DILocation(line: 793, column: 12, scope: !2387)
!2410 = !DILocation(line: 794, column: 28, scope: !2411)
!2411 = distinct !DILexicalBlock(scope: !2405, file: !1, line: 793, column: 54)
!2412 = !DILocation(line: 794, column: 49, scope: !2411)
!2413 = !DILocation(line: 794, column: 34, scope: !2411)
!2414 = !DILocation(line: 794, column: 40, scope: !2411)
!2415 = !DILocation(line: 794, column: 11, scope: !2411)
!2416 = !DILocation(line: 795, column: 26, scope: !2411)
!2417 = !DILocation(line: 795, column: 11, scope: !2411)
!2418 = !DILocation(line: 795, column: 17, scope: !2411)
!2419 = !DILocation(line: 795, column: 33, scope: !2411)
!2420 = !DILocation(line: 796, column: 9, scope: !2411)
!2421 = !DILocation(line: 799, column: 39, scope: !2387)
!2422 = !DILocation(line: 799, column: 45, scope: !2387)
!2423 = !DILocation(line: 799, column: 18, scope: !2387)
!2424 = !DILocation(line: 799, column: 16, scope: !2387)
!2425 = !DILocation(line: 800, column: 12, scope: !2426)
!2426 = distinct !DILexicalBlock(scope: !2387, file: !1, line: 800, column: 12)
!2427 = !DILocation(line: 800, column: 12, scope: !2387)
!2428 = !DILocation(line: 801, column: 18, scope: !2426)
!2429 = !DILocation(line: 801, column: 11, scope: !2426)
!2430 = !DILocation(line: 803, column: 31, scope: !2387)
!2431 = !DILocation(line: 803, column: 9, scope: !2387)
!2432 = !DILocation(line: 803, column: 15, scope: !2387)
!2433 = !DILocation(line: 803, column: 20, scope: !2387)
!2434 = !DILocation(line: 803, column: 42, scope: !2387)
!2435 = !DILocation(line: 805, column: 10, scope: !2387)
!2436 = !DILocation(line: 805, column: 20, scope: !2387)
!2437 = !DILocation(line: 806, column: 12, scope: !2438)
!2438 = distinct !DILexicalBlock(scope: !2387, file: !1, line: 806, column: 12)
!2439 = !DILocation(line: 806, column: 22, scope: !2438)
!2440 = !DILocation(line: 806, column: 12, scope: !2387)
!2441 = !DILocation(line: 807, column: 25, scope: !2438)
!2442 = !DILocation(line: 807, column: 11, scope: !2438)
!2443 = !DILocation(line: 808, column: 29, scope: !2387)
!2444 = !DILocation(line: 808, column: 46, scope: !2387)
!2445 = !DILocation(line: 808, column: 35, scope: !2387)
!2446 = !DILocation(line: 808, column: 41, scope: !2387)
!2447 = !DILocation(line: 808, column: 9, scope: !2387)
!2448 = !DILocation(line: 809, column: 29, scope: !2387)
!2449 = !DILocation(line: 809, column: 9, scope: !2387)
!2450 = !DILocation(line: 811, column: 9, scope: !2387)
!2451 = !DILocation(line: 813, column: 13, scope: !2381)
!2452 = !DILocation(line: 813, column: 7, scope: !2381)
!2453 = !DILocation(line: 814, column: 5, scope: !2381)
!2454 = !DILocation(line: 815, column: 13, scope: !2455)
!2455 = distinct !DILexicalBlock(scope: !2371, file: !1, line: 815, column: 13)
!2456 = !DILocation(line: 815, column: 16, scope: !2455)
!2457 = !DILocation(line: 815, column: 13, scope: !2371)
!2458 = !DILocation(line: 816, column: 42, scope: !2455)
!2459 = !DILocation(line: 816, column: 27, scope: !2455)
!2460 = !DILocation(line: 816, column: 33, scope: !2455)
!2461 = !DILocation(line: 816, column: 13, scope: !2455)
!2462 = !DILocation(line: 816, column: 7, scope: !2455)
!2463 = !DILocation(line: 822, column: 8, scope: !2464)
!2464 = distinct !DILexicalBlock(scope: !2314, file: !1, line: 822, column: 8)
!2465 = !DILocation(line: 822, column: 8, scope: !2314)
!2466 = !DILocation(line: 823, column: 30, scope: !2467)
!2467 = distinct !DILexicalBlock(scope: !2464, file: !1, line: 822, column: 15)
!2468 = !DILocation(line: 823, column: 7, scope: !2467)
!2469 = !DILocation(line: 823, column: 13, scope: !2467)
!2470 = !DILocation(line: 823, column: 19, scope: !2467)
!2471 = !DILocation(line: 823, column: 28, scope: !2467)
!2472 = !DILocation(line: 824, column: 7, scope: !2467)
!2473 = !DILocation(line: 825, column: 25, scope: !2474)
!2474 = distinct !DILexicalBlock(scope: !2467, file: !1, line: 825, column: 10)
!2475 = !DILocation(line: 825, column: 10, scope: !2474)
!2476 = !DILocation(line: 825, column: 16, scope: !2474)
!2477 = !DILocation(line: 825, column: 10, scope: !2467)
!2478 = !DILocalVariable(name: "status", scope: !2479, file: !1, line: 826, type: !289)
!2479 = distinct !DILexicalBlock(scope: !2474, file: !1, line: 825, column: 29)
!2480 = !DILocation(line: 826, column: 18, scope: !2479)
!2481 = !DILocalVariable(name: "ipaddress", scope: !2479, file: !1, line: 827, type: !1220)
!2482 = !DILocation(line: 827, column: 14, scope: !2479)
!2483 = !DILocation(line: 828, column: 47, scope: !2479)
!2484 = !DILocation(line: 828, column: 32, scope: !2479)
!2485 = !DILocation(line: 828, column: 38, scope: !2479)
!2486 = !DILocation(line: 828, column: 51, scope: !2479)
!2487 = !DILocation(line: 828, column: 9, scope: !2479)
!2488 = !DILocation(line: 829, column: 15, scope: !2479)
!2489 = !DILocation(line: 830, column: 15, scope: !2479)
!2490 = !DILocation(line: 830, column: 26, scope: !2479)
!2491 = !DILocation(line: 830, column: 32, scope: !2479)
!2492 = !DILocation(line: 830, column: 52, scope: !2479)
!2493 = !DILocation(line: 830, column: 58, scope: !2479)
!2494 = !DILocation(line: 830, column: 38, scope: !2479)
!2495 = !DILocation(line: 829, column: 9, scope: !2479)
!2496 = !DILocation(line: 832, column: 51, scope: !2479)
!2497 = !DILocation(line: 832, column: 36, scope: !2479)
!2498 = !DILocation(line: 832, column: 42, scope: !2479)
!2499 = !DILocation(line: 832, column: 55, scope: !2479)
!2500 = !DILocation(line: 832, column: 63, scope: !2479)
!2501 = !DILocation(line: 833, column: 36, scope: !2479)
!2502 = !DILocation(line: 832, column: 36, scope: !2503)
!2503 = !DILexicalBlockFile(scope: !2479, file: !1, discriminator: 1)
!2504 = !DILocation(line: 833, column: 44, scope: !2503)
!2505 = !DILocation(line: 833, column: 50, scope: !2503)
!2506 = !DILocation(line: 832, column: 36, scope: !2507)
!2507 = !DILexicalBlockFile(scope: !2479, file: !1, discriminator: 2)
!2508 = !DILocation(line: 832, column: 36, scope: !2509)
!2509 = !DILexicalBlockFile(scope: !2479, file: !1, discriminator: 3)
!2510 = !DILocation(line: 832, column: 9, scope: !2509)
!2511 = !DILocation(line: 832, column: 15, scope: !2509)
!2512 = !DILocation(line: 832, column: 34, scope: !2509)
!2513 = !DILocation(line: 835, column: 28, scope: !2479)
!2514 = !DILocation(line: 835, column: 34, scope: !2479)
!2515 = !DILocation(line: 835, column: 45, scope: !2479)
!2516 = !DILocation(line: 835, column: 18, scope: !2479)
!2517 = !DILocation(line: 835, column: 16, scope: !2479)
!2518 = !DILocation(line: 836, column: 12, scope: !2519)
!2519 = distinct !DILexicalBlock(scope: !2479, file: !1, line: 836, column: 12)
!2520 = !DILocation(line: 836, column: 19, scope: !2519)
!2521 = !DILocation(line: 837, column: 13, scope: !2519)
!2522 = !DILocation(line: 837, column: 31, scope: !2523)
!2523 = !DILexicalBlockFile(scope: !2519, file: !1, discriminator: 1)
!2524 = !DILocation(line: 837, column: 16, scope: !2523)
!2525 = !DILocation(line: 837, column: 22, scope: !2523)
!2526 = !DILocation(line: 837, column: 38, scope: !2523)
!2527 = !DILocation(line: 836, column: 12, scope: !2503)
!2528 = !DILocation(line: 839, column: 20, scope: !2519)
!2529 = !DILocation(line: 839, column: 18, scope: !2519)
!2530 = !DILocation(line: 839, column: 11, scope: !2519)
!2531 = !DILocation(line: 840, column: 7, scope: !2479)
!2532 = !DILocation(line: 841, column: 5, scope: !2467)
!2533 = !DILocation(line: 842, column: 3, scope: !2314)
!2534 = !DILocation(line: 754, column: 18, scope: !2535)
!2535 = !DILexicalBlockFile(scope: !2310, file: !1, discriminator: 2)
!2536 = !DILocation(line: 754, column: 3, scope: !2535)
!2537 = !DILocation(line: 844, column: 6, scope: !2538)
!2538 = distinct !DILexicalBlock(scope: !1855, file: !1, line: 844, column: 6)
!2539 = !DILocation(line: 844, column: 6, scope: !1855)
!2540 = !DILocalVariable(name: "hostname", scope: !2541, file: !1, line: 847, type: !851)
!2541 = distinct !DILexicalBlock(scope: !2538, file: !1, line: 844, column: 14)
!2542 = !DILocation(line: 847, column: 17, scope: !2541)
!2543 = !DILocation(line: 851, column: 8, scope: !2544)
!2544 = distinct !DILexicalBlock(scope: !2541, file: !1, line: 851, column: 8)
!2545 = !DILocation(line: 851, column: 14, scope: !2544)
!2546 = !DILocation(line: 851, column: 26, scope: !2544)
!2547 = !DILocation(line: 851, column: 8, scope: !2541)
!2548 = !DILocation(line: 852, column: 26, scope: !2549)
!2549 = distinct !DILexicalBlock(scope: !2544, file: !1, line: 851, column: 35)
!2550 = !DILocation(line: 852, column: 32, scope: !2549)
!2551 = !DILocation(line: 852, column: 16, scope: !2549)
!2552 = !DILocation(line: 852, column: 14, scope: !2549)
!2553 = !DILocation(line: 853, column: 11, scope: !2554)
!2554 = distinct !DILexicalBlock(scope: !2549, file: !1, line: 853, column: 10)
!2555 = !DILocation(line: 853, column: 10, scope: !2549)
!2556 = !DILocation(line: 854, column: 16, scope: !2554)
!2557 = !DILocation(line: 854, column: 9, scope: !2554)
!2558 = !DILocation(line: 855, column: 5, scope: !2549)
!2559 = !DILocation(line: 857, column: 8, scope: !2560)
!2560 = distinct !DILexicalBlock(scope: !2541, file: !1, line: 857, column: 8)
!2561 = !DILocation(line: 857, column: 14, scope: !2560)
!2562 = !DILocation(line: 857, column: 19, scope: !2560)
!2563 = !DILocation(line: 857, column: 8, scope: !2541)
!2564 = !DILocation(line: 858, column: 18, scope: !2560)
!2565 = !DILocation(line: 858, column: 24, scope: !2560)
!2566 = !DILocation(line: 858, column: 36, scope: !2560)
!2567 = !DILocation(line: 858, column: 41, scope: !2560)
!2568 = !DILocation(line: 858, column: 16, scope: !2560)
!2569 = !DILocation(line: 858, column: 7, scope: !2560)
!2570 = !DILocation(line: 859, column: 13, scope: !2571)
!2571 = distinct !DILexicalBlock(scope: !2560, file: !1, line: 859, column: 13)
!2572 = !DILocation(line: 859, column: 19, scope: !2571)
!2573 = !DILocation(line: 859, column: 24, scope: !2571)
!2574 = !DILocation(line: 859, column: 13, scope: !2560)
!2575 = !DILocation(line: 860, column: 18, scope: !2571)
!2576 = !DILocation(line: 860, column: 24, scope: !2571)
!2577 = !DILocation(line: 860, column: 35, scope: !2571)
!2578 = !DILocation(line: 860, column: 40, scope: !2571)
!2579 = !DILocation(line: 860, column: 16, scope: !2571)
!2580 = !DILocation(line: 860, column: 7, scope: !2571)
!2581 = !DILocation(line: 861, column: 13, scope: !2582)
!2582 = distinct !DILexicalBlock(scope: !2571, file: !1, line: 861, column: 13)
!2583 = !DILocation(line: 861, column: 19, scope: !2582)
!2584 = !DILocation(line: 861, column: 24, scope: !2582)
!2585 = !DILocation(line: 861, column: 13, scope: !2571)
!2586 = !DILocation(line: 862, column: 18, scope: !2582)
!2587 = !DILocation(line: 862, column: 24, scope: !2582)
!2588 = !DILocation(line: 862, column: 37, scope: !2582)
!2589 = !DILocation(line: 862, column: 16, scope: !2582)
!2590 = !DILocation(line: 862, column: 7, scope: !2582)
!2591 = !DILocation(line: 864, column: 18, scope: !2582)
!2592 = !DILocation(line: 864, column: 24, scope: !2582)
!2593 = !DILocation(line: 864, column: 29, scope: !2582)
!2594 = !DILocation(line: 864, column: 16, scope: !2582)
!2595 = !DILocation(line: 866, column: 11, scope: !2541)
!2596 = !DILocation(line: 867, column: 9, scope: !2541)
!2597 = !DILocation(line: 867, column: 19, scope: !2541)
!2598 = !DILocation(line: 867, column: 25, scope: !2541)
!2599 = !DILocation(line: 867, column: 45, scope: !2541)
!2600 = !DILocation(line: 867, column: 51, scope: !2541)
!2601 = !DILocation(line: 867, column: 31, scope: !2541)
!2602 = !DILocation(line: 866, column: 5, scope: !2541)
!2603 = !DILocation(line: 868, column: 3, scope: !2541)
!2604 = !DILocation(line: 870, column: 10, scope: !1855)
!2605 = !DILocation(line: 870, column: 3, scope: !1855)
!2606 = !DILocation(line: 871, column: 1, scope: !1855)
!2607 = !DILocalVariable(name: "conn", arg: 1, scope: !1919, file: !1, line: 540, type: !262)
!2608 = !DILocation(line: 540, column: 47, scope: !1919)
!2609 = !DILocalVariable(name: "sockindex", arg: 2, scope: !1919, file: !1, line: 541, type: !316)
!2610 = !DILocation(line: 541, column: 31, scope: !1919)
!2611 = !DILocalVariable(name: "tempindex", arg: 3, scope: !1919, file: !1, line: 542, type: !316)
!2612 = !DILocation(line: 542, column: 31, scope: !1919)
!2613 = !DILocalVariable(name: "other", scope: !1919, file: !1, line: 544, type: !2315)
!2614 = !DILocation(line: 544, column: 13, scope: !1919)
!2615 = !DILocation(line: 544, column: 21, scope: !1919)
!2616 = !DILocation(line: 544, column: 31, scope: !1919)
!2617 = !DILocalVariable(name: "result", scope: !1919, file: !1, line: 545, type: !289)
!2618 = !DILocation(line: 545, column: 12, scope: !1919)
!2619 = !DILocalVariable(name: "fd_to_close", scope: !1919, file: !1, line: 551, type: !315)
!2620 = !DILocation(line: 551, column: 17, scope: !1919)
!2621 = !DILocation(line: 551, column: 46, scope: !1919)
!2622 = !DILocation(line: 551, column: 31, scope: !1919)
!2623 = !DILocation(line: 551, column: 37, scope: !1919)
!2624 = !DILocation(line: 552, column: 18, scope: !1919)
!2625 = !DILocation(line: 552, column: 3, scope: !1919)
!2626 = !DILocation(line: 552, column: 9, scope: !1919)
!2627 = !DILocation(line: 552, column: 29, scope: !1919)
!2628 = !DILocation(line: 554, column: 6, scope: !2629)
!2629 = distinct !DILexicalBlock(scope: !1919, file: !1, line: 554, column: 6)
!2630 = !DILocation(line: 554, column: 16, scope: !2629)
!2631 = !DILocation(line: 554, column: 6, scope: !1919)
!2632 = !DILocalVariable(name: "ai", scope: !2633, file: !1, line: 555, type: !1277)
!2633 = distinct !DILexicalBlock(scope: !2629, file: !1, line: 554, column: 32)
!2634 = !DILocation(line: 555, column: 20, scope: !2633)
!2635 = !DILocalVariable(name: "family", scope: !2633, file: !1, line: 556, type: !316)
!2636 = !DILocation(line: 556, column: 9, scope: !2633)
!2637 = !DILocation(line: 558, column: 23, scope: !2638)
!2638 = distinct !DILexicalBlock(scope: !2633, file: !1, line: 558, column: 8)
!2639 = !DILocation(line: 558, column: 8, scope: !2638)
!2640 = !DILocation(line: 558, column: 14, scope: !2638)
!2641 = !DILocation(line: 558, column: 8, scope: !2633)
!2642 = !DILocation(line: 560, column: 31, scope: !2643)
!2643 = distinct !DILexicalBlock(scope: !2638, file: !1, line: 558, column: 35)
!2644 = !DILocation(line: 560, column: 16, scope: !2643)
!2645 = !DILocation(line: 560, column: 22, scope: !2643)
!2646 = !DILocation(line: 560, column: 43, scope: !2643)
!2647 = !DILocation(line: 560, column: 14, scope: !2643)
!2648 = !DILocation(line: 561, column: 27, scope: !2643)
!2649 = !DILocation(line: 561, column: 12, scope: !2643)
!2650 = !DILocation(line: 561, column: 18, scope: !2643)
!2651 = !DILocation(line: 561, column: 39, scope: !2643)
!2652 = !DILocation(line: 561, column: 10, scope: !2643)
!2653 = !DILocation(line: 562, column: 5, scope: !2643)
!2654 = !DILocation(line: 572, column: 5, scope: !2633)
!2655 = !DILocation(line: 572, column: 11, scope: !2656)
!2656 = !DILexicalBlockFile(scope: !2633, file: !1, discriminator: 1)
!2657 = !DILocation(line: 572, column: 5, scope: !2656)
!2658 = !DILocation(line: 573, column: 25, scope: !2659)
!2659 = distinct !DILexicalBlock(scope: !2660, file: !1, line: 573, column: 10)
!2660 = distinct !DILexicalBlock(scope: !2633, file: !1, line: 572, column: 15)
!2661 = !DILocation(line: 573, column: 10, scope: !2659)
!2662 = !DILocation(line: 573, column: 16, scope: !2659)
!2663 = !DILocation(line: 573, column: 10, scope: !2660)
!2664 = !DILocation(line: 575, column: 9, scope: !2665)
!2665 = distinct !DILexicalBlock(scope: !2659, file: !1, line: 573, column: 33)
!2666 = !DILocation(line: 575, column: 15, scope: !2667)
!2667 = !DILexicalBlockFile(scope: !2665, file: !1, discriminator: 1)
!2668 = !DILocation(line: 575, column: 18, scope: !2667)
!2669 = !DILocation(line: 575, column: 21, scope: !2670)
!2670 = !DILexicalBlockFile(scope: !2665, file: !1, discriminator: 2)
!2671 = !DILocation(line: 575, column: 25, scope: !2670)
!2672 = !DILocation(line: 575, column: 38, scope: !2670)
!2673 = !DILocation(line: 575, column: 35, scope: !2670)
!2674 = !DILocation(line: 575, column: 9, scope: !2675)
!2675 = !DILexicalBlockFile(scope: !2665, file: !1, discriminator: 3)
!2676 = !DILocation(line: 576, column: 16, scope: !2665)
!2677 = !DILocation(line: 576, column: 20, scope: !2665)
!2678 = !DILocation(line: 576, column: 14, scope: !2665)
!2679 = !DILocation(line: 575, column: 9, scope: !2680)
!2680 = !DILexicalBlockFile(scope: !2665, file: !1, discriminator: 4)
!2681 = !DILocation(line: 577, column: 7, scope: !2665)
!2682 = !DILocation(line: 579, column: 10, scope: !2683)
!2683 = distinct !DILexicalBlock(scope: !2660, file: !1, line: 579, column: 10)
!2684 = !DILocation(line: 579, column: 10, scope: !2660)
!2685 = !DILocation(line: 580, column: 34, scope: !2686)
!2686 = distinct !DILexicalBlock(scope: !2683, file: !1, line: 579, column: 14)
!2687 = !DILocation(line: 580, column: 40, scope: !2686)
!2688 = !DILocation(line: 580, column: 60, scope: !2686)
!2689 = !DILocation(line: 580, column: 45, scope: !2686)
!2690 = !DILocation(line: 580, column: 51, scope: !2686)
!2691 = !DILocation(line: 580, column: 18, scope: !2686)
!2692 = !DILocation(line: 580, column: 16, scope: !2686)
!2693 = !DILocation(line: 581, column: 12, scope: !2694)
!2694 = distinct !DILexicalBlock(scope: !2686, file: !1, line: 581, column: 12)
!2695 = !DILocation(line: 581, column: 19, scope: !2694)
!2696 = !DILocation(line: 581, column: 12, scope: !2686)
!2697 = !DILocation(line: 582, column: 16, scope: !2698)
!2698 = distinct !DILexicalBlock(scope: !2694, file: !1, line: 581, column: 45)
!2699 = !DILocation(line: 582, column: 20, scope: !2698)
!2700 = !DILocation(line: 582, column: 14, scope: !2698)
!2701 = !DILocation(line: 583, column: 11, scope: !2698)
!2702 = !DILocation(line: 586, column: 37, scope: !2686)
!2703 = !DILocation(line: 586, column: 24, scope: !2686)
!2704 = !DILocation(line: 586, column: 9, scope: !2686)
!2705 = !DILocation(line: 586, column: 15, scope: !2686)
!2706 = !DILocation(line: 586, column: 35, scope: !2686)
!2707 = !DILocation(line: 587, column: 7, scope: !2686)
!2708 = !DILocation(line: 588, column: 7, scope: !2660)
!2709 = !DILocation(line: 590, column: 3, scope: !2633)
!2710 = !DILocation(line: 592, column: 6, scope: !2711)
!2711 = distinct !DILexicalBlock(scope: !1919, file: !1, line: 592, column: 6)
!2712 = !DILocation(line: 592, column: 18, scope: !2711)
!2713 = !DILocation(line: 592, column: 6, scope: !1919)
!2714 = !DILocation(line: 593, column: 22, scope: !2711)
!2715 = !DILocation(line: 593, column: 28, scope: !2711)
!2716 = !DILocation(line: 593, column: 5, scope: !2711)
!2717 = !DILocation(line: 595, column: 10, scope: !1919)
!2718 = !DILocation(line: 595, column: 3, scope: !1919)
!2719 = !DILocalVariable(name: "sockfd", arg: 1, scope: !1922, file: !1, line: 474, type: !315)
!2720 = !DILocation(line: 474, column: 41, scope: !1922)
!2721 = !DILocalVariable(name: "error", arg: 2, scope: !1922, file: !1, line: 474, type: !1434)
!2722 = !DILocation(line: 474, column: 54, scope: !1922)
!2723 = !DILocalVariable(name: "rc", scope: !1922, file: !1, line: 476, type: !423)
!2724 = !DILocation(line: 476, column: 8, scope: !1922)
!2725 = !DILocalVariable(name: "err", scope: !1922, file: !1, line: 478, type: !316)
!2726 = !DILocation(line: 478, column: 7, scope: !1922)
!2727 = !DILocalVariable(name: "errSize", scope: !1922, file: !1, line: 479, type: !1287)
!2728 = !DILocation(line: 479, column: 18, scope: !1922)
!2729 = !DILocation(line: 506, column: 22, scope: !2730)
!2730 = distinct !DILexicalBlock(scope: !1922, file: !1, line: 506, column: 6)
!2731 = !DILocation(line: 506, column: 52, scope: !2730)
!2732 = !DILocation(line: 506, column: 11, scope: !2730)
!2733 = !DILocation(line: 506, column: 8, scope: !2730)
!2734 = !DILocation(line: 506, column: 6, scope: !1922)
!2735 = !DILocation(line: 507, column: 11, scope: !2730)
!2736 = !DILocation(line: 507, column: 9, scope: !2730)
!2737 = !DILocation(line: 507, column: 5, scope: !2730)
!2738 = !DILocation(line: 522, column: 12, scope: !2739)
!2739 = distinct !DILexicalBlock(scope: !1922, file: !1, line: 522, column: 6)
!2740 = !DILocation(line: 522, column: 9, scope: !2739)
!2741 = !DILocation(line: 522, column: 17, scope: !2739)
!2742 = !DILocation(line: 522, column: 32, scope: !2743)
!2743 = !DILexicalBlockFile(scope: !2739, file: !1, discriminator: 1)
!2744 = !DILocation(line: 522, column: 29, scope: !2743)
!2745 = !DILocation(line: 522, column: 6, scope: !2743)
!2746 = !DILocation(line: 524, column: 8, scope: !2739)
!2747 = !DILocation(line: 524, column: 5, scope: !2739)
!2748 = !DILocation(line: 527, column: 8, scope: !2739)
!2749 = !DILocation(line: 528, column: 6, scope: !2750)
!2750 = distinct !DILexicalBlock(scope: !1922, file: !1, line: 528, column: 6)
!2751 = !DILocation(line: 528, column: 6, scope: !1922)
!2752 = !DILocation(line: 529, column: 14, scope: !2750)
!2753 = !DILocation(line: 529, column: 6, scope: !2750)
!2754 = !DILocation(line: 529, column: 12, scope: !2750)
!2755 = !DILocation(line: 529, column: 5, scope: !2750)
!2756 = !DILocation(line: 535, column: 10, scope: !1922)
!2757 = !DILocation(line: 535, column: 3, scope: !1922)
!2758 = !DILocalVariable(name: "conn", arg: 1, scope: !1871, file: !1, line: 1288, type: !262)
!2759 = !DILocation(line: 1288, column: 42, scope: !1871)
!2760 = !DILocalVariable(name: "sock", arg: 2, scope: !1871, file: !1, line: 1289, type: !315)
!2761 = !DILocation(line: 1289, column: 37, scope: !1871)
!2762 = !DILocation(line: 1291, column: 6, scope: !2763)
!2763 = distinct !DILexicalBlock(scope: !1871, file: !1, line: 1291, column: 6)
!2764 = !DILocation(line: 1291, column: 11, scope: !2763)
!2765 = !DILocation(line: 1291, column: 14, scope: !2766)
!2766 = !DILexicalBlockFile(scope: !2763, file: !1, discriminator: 1)
!2767 = !DILocation(line: 1291, column: 20, scope: !2766)
!2768 = !DILocation(line: 1291, column: 6, scope: !2766)
!2769 = !DILocation(line: 1292, column: 9, scope: !2770)
!2770 = distinct !DILexicalBlock(scope: !2771, file: !1, line: 1292, column: 8)
!2771 = distinct !DILexicalBlock(scope: !2763, file: !1, line: 1291, column: 34)
!2772 = !DILocation(line: 1292, column: 17, scope: !2770)
!2773 = !DILocation(line: 1292, column: 23, scope: !2770)
!2774 = !DILocation(line: 1292, column: 14, scope: !2770)
!2775 = !DILocation(line: 1292, column: 46, scope: !2770)
!2776 = !DILocation(line: 1293, column: 8, scope: !2770)
!2777 = !DILocation(line: 1293, column: 14, scope: !2770)
!2778 = !DILocation(line: 1292, column: 8, scope: !2779)
!2779 = !DILexicalBlockFile(scope: !2771, file: !1, discriminator: 1)
!2780 = !DILocation(line: 1297, column: 7, scope: !2770)
!2781 = !DILocation(line: 1297, column: 13, scope: !2770)
!2782 = !DILocation(line: 1297, column: 44, scope: !2770)
!2783 = !DILocation(line: 1299, column: 25, scope: !2784)
!2784 = distinct !DILexicalBlock(scope: !2770, file: !1, line: 1298, column: 10)
!2785 = !DILocation(line: 1299, column: 31, scope: !2784)
!2786 = !DILocation(line: 1299, column: 7, scope: !2784)
!2787 = !DILocation(line: 1300, column: 14, scope: !2784)
!2788 = !DILocation(line: 1300, column: 20, scope: !2784)
!2789 = !DILocation(line: 1300, column: 33, scope: !2784)
!2790 = !DILocation(line: 1300, column: 39, scope: !2784)
!2791 = !DILocation(line: 1300, column: 59, scope: !2784)
!2792 = !DILocation(line: 1300, column: 7, scope: !2784)
!2793 = !DILocation(line: 1302, column: 3, scope: !2771)
!2794 = !DILocation(line: 1304, column: 6, scope: !2795)
!2795 = distinct !DILexicalBlock(scope: !1871, file: !1, line: 1304, column: 6)
!2796 = !DILocation(line: 1304, column: 6, scope: !1871)
!2797 = !DILocation(line: 1306, column: 23, scope: !2795)
!2798 = !DILocation(line: 1306, column: 29, scope: !2795)
!2799 = !DILocation(line: 1306, column: 5, scope: !2795)
!2800 = !DILocation(line: 1308, column: 3, scope: !1871)
!2801 = !DILocation(line: 1310, column: 3, scope: !1871)
!2802 = !DILocation(line: 1311, column: 1, scope: !1871)
!2803 = !DILocalVariable(name: "conn", arg: 1, scope: !1858, file: !1, line: 873, type: !262)
!2804 = !DILocation(line: 873, column: 42, scope: !1858)
!2805 = !DILocalVariable(name: "sockfd", arg: 2, scope: !1858, file: !1, line: 873, type: !315)
!2806 = !DILocation(line: 873, column: 62, scope: !1858)
!2807 = !DILocalVariable(name: "data", scope: !1858, file: !1, line: 877, type: !256)
!2808 = !DILocation(line: 877, column: 21, scope: !1858)
!2809 = !DILocation(line: 877, column: 28, scope: !1858)
!2810 = !DILocation(line: 877, column: 34, scope: !1858)
!2811 = !DILocalVariable(name: "onoff", scope: !1858, file: !1, line: 879, type: !1287)
!2812 = !DILocation(line: 879, column: 18, scope: !1858)
!2813 = !DILocalVariable(name: "level", scope: !1858, file: !1, line: 880, type: !316)
!2814 = !DILocation(line: 880, column: 7, scope: !1858)
!2815 = !DILocation(line: 899, column: 17, scope: !2816)
!2816 = distinct !DILexicalBlock(scope: !1858, file: !1, line: 899, column: 6)
!2817 = !DILocation(line: 899, column: 25, scope: !2816)
!2818 = !DILocation(line: 899, column: 45, scope: !2816)
!2819 = !DILocation(line: 899, column: 6, scope: !2816)
!2820 = !DILocation(line: 900, column: 32, scope: !2816)
!2821 = !DILocation(line: 899, column: 6, scope: !1858)
!2822 = !DILocation(line: 901, column: 11, scope: !2816)
!2823 = !DILocation(line: 902, column: 25, scope: !2816)
!2824 = !DILocation(line: 902, column: 31, scope: !2816)
!2825 = !DILocation(line: 902, column: 11, scope: !2826)
!2826 = !DILexicalBlockFile(scope: !2816, file: !1, discriminator: 1)
!2827 = !DILocation(line: 901, column: 5, scope: !2816)
!2828 = !DILocation(line: 904, column: 11, scope: !2816)
!2829 = !DILocation(line: 904, column: 5, scope: !2816)
!2830 = !DILocation(line: 909, column: 1, scope: !1858)
!2831 = !DILocalVariable(name: "conn", arg: 1, scope: !1859, file: !1, line: 1152, type: !262)
!2832 = !DILocation(line: 1152, column: 47, scope: !1859)
!2833 = !DILocalVariable(name: "remotehost", arg: 2, scope: !1859, file: !1, line: 1153, type: !1862)
!2834 = !DILocation(line: 1153, column: 56, scope: !1859)
!2835 = !DILocalVariable(name: "data", scope: !1859, file: !1, line: 1155, type: !256)
!2836 = !DILocation(line: 1155, column: 21, scope: !1859)
!2837 = !DILocation(line: 1155, column: 28, scope: !1859)
!2838 = !DILocation(line: 1155, column: 34, scope: !1859)
!2839 = !DILocalVariable(name: "before", scope: !1859, file: !1, line: 1156, type: !411)
!2840 = !DILocation(line: 1156, column: 18, scope: !1859)
!2841 = !DILocation(line: 1156, column: 27, scope: !1859)
!2842 = !DILocalVariable(name: "result", scope: !1859, file: !1, line: 1157, type: !289)
!2843 = !DILocation(line: 1157, column: 12, scope: !1859)
!2844 = !DILocalVariable(name: "timeout_ms", scope: !1859, file: !1, line: 1159, type: !506)
!2845 = !DILocation(line: 1159, column: 10, scope: !1859)
!2846 = !DILocation(line: 1159, column: 37, scope: !1859)
!2847 = !DILocation(line: 1159, column: 23, scope: !1859)
!2848 = !DILocation(line: 1161, column: 6, scope: !2849)
!2849 = distinct !DILexicalBlock(scope: !1859, file: !1, line: 1161, column: 6)
!2850 = !DILocation(line: 1161, column: 17, scope: !2849)
!2851 = !DILocation(line: 1161, column: 6, scope: !1859)
!2852 = !DILocation(line: 1163, column: 11, scope: !2853)
!2853 = distinct !DILexicalBlock(scope: !2849, file: !1, line: 1161, column: 22)
!2854 = !DILocation(line: 1163, column: 5, scope: !2853)
!2855 = !DILocation(line: 1164, column: 5, scope: !2853)
!2856 = !DILocation(line: 1167, column: 39, scope: !1859)
!2857 = !DILocation(line: 1167, column: 51, scope: !1859)
!2858 = !DILocation(line: 1167, column: 20, scope: !1859)
!2859 = !DILocation(line: 1167, column: 3, scope: !1859)
!2860 = !DILocation(line: 1167, column: 9, scope: !1859)
!2861 = !DILocation(line: 1167, column: 18, scope: !1859)
!2862 = !DILocation(line: 1168, column: 23, scope: !1859)
!2863 = !DILocation(line: 1168, column: 35, scope: !1859)
!2864 = !DILocation(line: 1168, column: 3, scope: !1859)
!2865 = !DILocation(line: 1168, column: 9, scope: !1859)
!2866 = !DILocation(line: 1168, column: 21, scope: !1859)
!2867 = !DILocation(line: 1169, column: 3, scope: !1859)
!2868 = !DILocation(line: 1169, column: 9, scope: !1859)
!2869 = !DILocation(line: 1169, column: 21, scope: !1859)
!2870 = !DILocation(line: 1170, column: 3, scope: !1859)
!2871 = !DILocation(line: 1170, column: 9, scope: !1859)
!2872 = !DILocation(line: 1170, column: 21, scope: !1859)
!2873 = !DILocation(line: 1171, column: 3, scope: !1859)
!2874 = !DILocation(line: 1171, column: 9, scope: !1859)
!2875 = !DILocation(line: 1171, column: 21, scope: !1859)
!2876 = !DILocation(line: 1172, column: 15, scope: !1859)
!2877 = !DILocation(line: 1172, column: 21, scope: !1859)
!2878 = !DILocation(line: 1172, column: 3, scope: !1859)
!2879 = !DILocation(line: 1176, column: 5, scope: !1859)
!2880 = !DILocation(line: 1176, column: 11, scope: !1859)
!2881 = !DILocation(line: 1176, column: 24, scope: !1859)
!2882 = !DILocation(line: 1176, column: 32, scope: !1859)
!2883 = !DILocation(line: 1176, column: 42, scope: !2884)
!2884 = !DILexicalBlockFile(scope: !1859, file: !1, discriminator: 1)
!2885 = !DILocation(line: 1176, column: 5, scope: !2884)
!2886 = !DILocation(line: 1176, column: 55, scope: !2887)
!2887 = !DILexicalBlockFile(scope: !1859, file: !1, discriminator: 2)
!2888 = !DILocation(line: 1176, column: 66, scope: !2887)
!2889 = !DILocation(line: 1176, column: 5, scope: !2887)
!2890 = !DILocation(line: 1176, column: 5, scope: !2891)
!2891 = !DILexicalBlockFile(scope: !1859, file: !1, discriminator: 3)
!2892 = !DILocation(line: 1175, column: 3, scope: !1859)
!2893 = !DILocation(line: 1175, column: 9, scope: !1859)
!2894 = !DILocation(line: 1175, column: 28, scope: !1859)
!2895 = !DILocation(line: 1179, column: 3, scope: !1859)
!2896 = !DILocation(line: 1179, column: 9, scope: !2884)
!2897 = !DILocation(line: 1179, column: 15, scope: !2884)
!2898 = !DILocation(line: 1179, column: 3, scope: !2884)
!2899 = !DILocation(line: 1180, column: 30, scope: !2900)
!2900 = distinct !DILexicalBlock(scope: !1859, file: !1, line: 1179, column: 28)
!2901 = !DILocation(line: 1180, column: 36, scope: !2900)
!2902 = !DILocation(line: 1180, column: 42, scope: !2900)
!2903 = !DILocation(line: 1180, column: 57, scope: !2900)
!2904 = !DILocation(line: 1180, column: 63, scope: !2900)
!2905 = !DILocation(line: 1180, column: 14, scope: !2900)
!2906 = !DILocation(line: 1180, column: 12, scope: !2900)
!2907 = !DILocation(line: 1181, column: 9, scope: !2908)
!2908 = distinct !DILexicalBlock(scope: !2900, file: !1, line: 1181, column: 8)
!2909 = !DILocation(line: 1181, column: 8, scope: !2900)
!2910 = !DILocation(line: 1182, column: 7, scope: !2908)
!2911 = !DILocation(line: 1183, column: 25, scope: !2900)
!2912 = !DILocation(line: 1183, column: 31, scope: !2900)
!2913 = !DILocation(line: 1183, column: 44, scope: !2900)
!2914 = !DILocation(line: 1183, column: 5, scope: !2900)
!2915 = !DILocation(line: 1183, column: 11, scope: !2900)
!2916 = !DILocation(line: 1183, column: 23, scope: !2900)
!2917 = !DILocation(line: 1179, column: 3, scope: !2887)
!2918 = !DILocation(line: 1186, column: 6, scope: !2919)
!2919 = distinct !DILexicalBlock(scope: !1859, file: !1, line: 1186, column: 6)
!2920 = !DILocation(line: 1186, column: 12, scope: !2919)
!2921 = !DILocation(line: 1186, column: 24, scope: !2919)
!2922 = !DILocation(line: 1186, column: 6, scope: !1859)
!2923 = !DILocation(line: 1187, column: 9, scope: !2924)
!2924 = distinct !DILexicalBlock(scope: !2925, file: !1, line: 1187, column: 8)
!2925 = distinct !DILexicalBlock(scope: !2919, file: !1, line: 1186, column: 44)
!2926 = !DILocation(line: 1187, column: 8, scope: !2925)
!2927 = !DILocation(line: 1188, column: 14, scope: !2924)
!2928 = !DILocation(line: 1188, column: 7, scope: !2924)
!2929 = !DILocation(line: 1189, column: 12, scope: !2925)
!2930 = !DILocation(line: 1189, column: 5, scope: !2925)
!2931 = !DILocation(line: 1192, column: 3, scope: !1859)
!2932 = !DILocation(line: 1192, column: 9, scope: !1859)
!2933 = !DILocation(line: 1192, column: 14, scope: !1859)
!2934 = !DILocation(line: 1192, column: 25, scope: !1859)
!2935 = !DILocation(line: 1194, column: 3, scope: !1859)
!2936 = !DILocation(line: 1195, column: 1, scope: !1859)
!2937 = !DILocalVariable(name: "conn", arg: 1, scope: !1925, file: !1, line: 983, type: !262)
!2938 = !DILocation(line: 983, column: 53, scope: !1925)
!2939 = !DILocalVariable(name: "ai", arg: 2, scope: !1925, file: !1, line: 984, type: !1877)
!2940 = !DILocation(line: 984, column: 54, scope: !1925)
!2941 = !DILocalVariable(name: "sockp", arg: 3, scope: !1925, file: !1, line: 985, type: !1442)
!2942 = !DILocation(line: 985, column: 48, scope: !1925)
!2943 = !DILocalVariable(name: "addr", scope: !1925, file: !1, line: 987, type: !1880)
!2944 = !DILocation(line: 987, column: 27, scope: !1925)
!2945 = !DILocalVariable(name: "rc", scope: !1925, file: !1, line: 988, type: !316)
!2946 = !DILocation(line: 988, column: 7, scope: !1925)
!2947 = !DILocalVariable(name: "error", scope: !1925, file: !1, line: 989, type: !316)
!2948 = !DILocation(line: 989, column: 7, scope: !1925)
!2949 = !DILocalVariable(name: "isconnected", scope: !1925, file: !1, line: 990, type: !423)
!2950 = !DILocation(line: 990, column: 8, scope: !1925)
!2951 = !DILocalVariable(name: "data", scope: !1925, file: !1, line: 991, type: !256)
!2952 = !DILocation(line: 991, column: 21, scope: !1925)
!2953 = !DILocation(line: 991, column: 28, scope: !1925)
!2954 = !DILocation(line: 991, column: 34, scope: !1925)
!2955 = !DILocalVariable(name: "sockfd", scope: !1925, file: !1, line: 992, type: !315)
!2956 = !DILocation(line: 992, column: 17, scope: !1925)
!2957 = !DILocalVariable(name: "result", scope: !1925, file: !1, line: 993, type: !289)
!2958 = !DILocation(line: 993, column: 12, scope: !1925)
!2959 = !DILocalVariable(name: "ipaddress", scope: !1925, file: !1, line: 994, type: !1220)
!2960 = !DILocation(line: 994, column: 8, scope: !1925)
!2961 = !DILocalVariable(name: "port", scope: !1925, file: !1, line: 995, type: !379)
!2962 = !DILocation(line: 995, column: 8, scope: !1925)
!2963 = !DILocalVariable(name: "is_tcp", scope: !1925, file: !1, line: 996, type: !423)
!2964 = !DILocation(line: 996, column: 8, scope: !1925)
!2965 = !DILocation(line: 998, column: 4, scope: !1925)
!2966 = !DILocation(line: 998, column: 10, scope: !1925)
!2967 = !DILocation(line: 1000, column: 24, scope: !1925)
!2968 = !DILocation(line: 1000, column: 30, scope: !1925)
!2969 = !DILocation(line: 1000, column: 12, scope: !1925)
!2970 = !DILocation(line: 1000, column: 10, scope: !1925)
!2971 = !DILocation(line: 1001, column: 6, scope: !2972)
!2972 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1001, column: 6)
!2973 = !DILocation(line: 1001, column: 6, scope: !1925)
!2974 = !DILocation(line: 1005, column: 5, scope: !2972)
!2975 = !DILocation(line: 1008, column: 46, scope: !2976)
!2976 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1008, column: 6)
!2977 = !DILocation(line: 1009, column: 22, scope: !2976)
!2978 = !DILocation(line: 1008, column: 7, scope: !2976)
!2979 = !DILocation(line: 1008, column: 6, scope: !1925)
!2980 = !DILocation(line: 1011, column: 13, scope: !2981)
!2981 = distinct !DILexicalBlock(scope: !2976, file: !1, line: 1009, column: 41)
!2982 = !DILocation(line: 1011, column: 11, scope: !2981)
!2983 = !DILocation(line: 1012, column: 11, scope: !2981)
!2984 = !DILocation(line: 1013, column: 11, scope: !2981)
!2985 = !DILocation(line: 1013, column: 32, scope: !2981)
!2986 = !DILocation(line: 1013, column: 38, scope: !2981)
!2987 = !DILocation(line: 1013, column: 18, scope: !2981)
!2988 = !DILocation(line: 1012, column: 5, scope: !2981)
!2989 = !DILocation(line: 1014, column: 22, scope: !2981)
!2990 = !DILocation(line: 1014, column: 28, scope: !2981)
!2991 = !DILocation(line: 1014, column: 5, scope: !2981)
!2992 = !DILocation(line: 1015, column: 5, scope: !2981)
!2993 = !DILocation(line: 1017, column: 9, scope: !1925)
!2994 = !DILocation(line: 1017, column: 35, scope: !1925)
!2995 = !DILocation(line: 1017, column: 3, scope: !1925)
!2996 = !DILocation(line: 1023, column: 18, scope: !1925)
!2997 = !DILocation(line: 1023, column: 25, scope: !1925)
!2998 = !DILocation(line: 1023, column: 37, scope: !1925)
!2999 = !DILocation(line: 1023, column: 45, scope: !3000)
!3000 = !DILexicalBlockFile(scope: !1925, file: !1, discriminator: 1)
!3001 = !DILocation(line: 1023, column: 54, scope: !3000)
!3002 = !DILocation(line: 1023, column: 10, scope: !3003)
!3003 = !DILexicalBlockFile(scope: !1925, file: !1, discriminator: 2)
!3004 = !DILocation(line: 1025, column: 6, scope: !3005)
!3005 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1025, column: 6)
!3006 = !DILocation(line: 1025, column: 13, scope: !3005)
!3007 = !DILocation(line: 1025, column: 16, scope: !3008)
!3008 = !DILexicalBlockFile(scope: !3005, file: !1, discriminator: 1)
!3009 = !DILocation(line: 1025, column: 22, scope: !3008)
!3010 = !DILocation(line: 1025, column: 26, scope: !3008)
!3011 = !DILocation(line: 1025, column: 6, scope: !3008)
!3012 = !DILocation(line: 1026, column: 21, scope: !3005)
!3013 = !DILocation(line: 1026, column: 27, scope: !3005)
!3014 = !DILocation(line: 1026, column: 5, scope: !3005)
!3015 = !DILocation(line: 1028, column: 3, scope: !1925)
!3016 = !DILocation(line: 1028, column: 3, scope: !3017)
!3017 = !DILexicalBlockFile(scope: !3018, file: !1, discriminator: 1)
!3018 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1028, column: 3)
!3019 = !DILocation(line: 1030, column: 3, scope: !1925)
!3020 = !DILocation(line: 1030, column: 3, scope: !3021)
!3021 = !DILexicalBlockFile(scope: !3022, file: !1, discriminator: 1)
!3022 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1030, column: 3)
!3023 = !DILocation(line: 1032, column: 6, scope: !3024)
!3024 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1032, column: 6)
!3025 = !DILocation(line: 1032, column: 13, scope: !3024)
!3026 = !DILocation(line: 1032, column: 16, scope: !3027)
!3027 = !DILexicalBlockFile(scope: !3024, file: !1, discriminator: 1)
!3028 = !DILocation(line: 1032, column: 22, scope: !3027)
!3029 = !DILocation(line: 1032, column: 26, scope: !3027)
!3030 = !DILocation(line: 1032, column: 6, scope: !3027)
!3031 = !DILocation(line: 1033, column: 18, scope: !3024)
!3032 = !DILocation(line: 1033, column: 24, scope: !3024)
!3033 = !DILocation(line: 1033, column: 5, scope: !3024)
!3034 = !DILocation(line: 1035, column: 6, scope: !3035)
!3035 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1035, column: 6)
!3036 = !DILocation(line: 1035, column: 12, scope: !3035)
!3037 = !DILocation(line: 1035, column: 16, scope: !3035)
!3038 = !DILocation(line: 1035, column: 6, scope: !1925)
!3039 = !DILocation(line: 1037, column: 13, scope: !3040)
!3040 = distinct !DILexicalBlock(scope: !3035, file: !1, line: 1035, column: 26)
!3041 = !DILocation(line: 1037, column: 19, scope: !3040)
!3042 = !DILocation(line: 1037, column: 23, scope: !3040)
!3043 = !DILocation(line: 1037, column: 32, scope: !3040)
!3044 = !DILocation(line: 1037, column: 38, scope: !3040)
!3045 = !DILocation(line: 1037, column: 42, scope: !3040)
!3046 = !DILocation(line: 1038, column: 32, scope: !3040)
!3047 = !DILocation(line: 1037, column: 11, scope: !3040)
!3048 = !DILocation(line: 1041, column: 8, scope: !3049)
!3049 = distinct !DILexicalBlock(scope: !3040, file: !1, line: 1041, column: 8)
!3050 = !DILocation(line: 1041, column: 14, scope: !3049)
!3051 = !DILocation(line: 1041, column: 8, scope: !3040)
!3052 = !DILocation(line: 1042, column: 19, scope: !3049)
!3053 = !DILocation(line: 1042, column: 7, scope: !3049)
!3054 = !DILocation(line: 1043, column: 13, scope: !3055)
!3055 = distinct !DILexicalBlock(scope: !3049, file: !1, line: 1043, column: 13)
!3056 = !DILocation(line: 1043, column: 13, scope: !3049)
!3057 = !DILocation(line: 1044, column: 24, scope: !3058)
!3058 = distinct !DILexicalBlock(scope: !3055, file: !1, line: 1043, column: 20)
!3059 = !DILocation(line: 1044, column: 30, scope: !3058)
!3060 = !DILocation(line: 1044, column: 7, scope: !3058)
!3061 = !DILocation(line: 1045, column: 7, scope: !3058)
!3062 = !DILocation(line: 1047, column: 3, scope: !3040)
!3063 = !DILocation(line: 1050, column: 11, scope: !3064)
!3064 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1050, column: 6)
!3065 = !DILocation(line: 1050, column: 18, scope: !3064)
!3066 = !DILocation(line: 1050, column: 6, scope: !1925)
!3067 = !DILocation(line: 1055, column: 24, scope: !3068)
!3068 = distinct !DILexicalBlock(scope: !3064, file: !1, line: 1054, column: 7)
!3069 = !DILocation(line: 1055, column: 30, scope: !3068)
!3070 = !DILocation(line: 1055, column: 43, scope: !3068)
!3071 = !DILocation(line: 1056, column: 64, scope: !3068)
!3072 = !DILocation(line: 1056, column: 24, scope: !3068)
!3073 = !DILocation(line: 1055, column: 14, scope: !3068)
!3074 = !DILocation(line: 1055, column: 12, scope: !3068)
!3075 = !DILocation(line: 1057, column: 8, scope: !3076)
!3076 = distinct !DILexicalBlock(scope: !3068, file: !1, line: 1057, column: 8)
!3077 = !DILocation(line: 1057, column: 8, scope: !3068)
!3078 = !DILocation(line: 1058, column: 24, scope: !3079)
!3079 = distinct !DILexicalBlock(scope: !3076, file: !1, line: 1057, column: 16)
!3080 = !DILocation(line: 1058, column: 30, scope: !3079)
!3081 = !DILocation(line: 1058, column: 7, scope: !3079)
!3082 = !DILocation(line: 1059, column: 10, scope: !3083)
!3083 = distinct !DILexicalBlock(scope: !3079, file: !1, line: 1059, column: 10)
!3084 = !DILocation(line: 1059, column: 17, scope: !3083)
!3085 = !DILocation(line: 1059, column: 10, scope: !3079)
!3086 = !DILocation(line: 1062, column: 9, scope: !3087)
!3087 = distinct !DILexicalBlock(scope: !3083, file: !1, line: 1059, column: 48)
!3088 = !DILocation(line: 1064, column: 14, scope: !3079)
!3089 = !DILocation(line: 1064, column: 7, scope: !3079)
!3090 = !DILocation(line: 1066, column: 3, scope: !3068)
!3091 = !DILocation(line: 1069, column: 24, scope: !1925)
!3092 = !DILocation(line: 1069, column: 9, scope: !1925)
!3093 = !DILocation(line: 1071, column: 3, scope: !1925)
!3094 = !DILocation(line: 1071, column: 9, scope: !1925)
!3095 = !DILocation(line: 1071, column: 23, scope: !1925)
!3096 = !DILocation(line: 1071, column: 23, scope: !3000)
!3097 = !DILocation(line: 1072, column: 6, scope: !3098)
!3098 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1072, column: 6)
!3099 = !DILocation(line: 1072, column: 12, scope: !3098)
!3100 = !DILocation(line: 1072, column: 21, scope: !3098)
!3101 = !DILocation(line: 1072, column: 6, scope: !1925)
!3102 = !DILocation(line: 1073, column: 24, scope: !3098)
!3103 = !DILocation(line: 1073, column: 30, scope: !3098)
!3104 = !DILocation(line: 1073, column: 36, scope: !3098)
!3105 = !DILocation(line: 1073, column: 5, scope: !3098)
!3106 = !DILocation(line: 1076, column: 7, scope: !3107)
!3107 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1076, column: 6)
!3108 = !DILocation(line: 1076, column: 19, scope: !3107)
!3109 = !DILocation(line: 1076, column: 23, scope: !3110)
!3110 = !DILexicalBlockFile(scope: !3107, file: !1, discriminator: 1)
!3111 = !DILocation(line: 1076, column: 29, scope: !3110)
!3112 = !DILocation(line: 1076, column: 38, scope: !3110)
!3113 = !DILocation(line: 1076, column: 6, scope: !3110)
!3114 = !DILocation(line: 1077, column: 8, scope: !3115)
!3115 = distinct !DILexicalBlock(scope: !3116, file: !1, line: 1077, column: 8)
!3116 = distinct !DILexicalBlock(scope: !3107, file: !1, line: 1076, column: 55)
!3117 = !DILocation(line: 1077, column: 14, scope: !3115)
!3118 = !DILocation(line: 1077, column: 19, scope: !3115)
!3119 = !DILocation(line: 1077, column: 8, scope: !3116)
!3120 = !DILocation(line: 1090, column: 10, scope: !3121)
!3121 = distinct !DILexicalBlock(scope: !3122, file: !1, line: 1090, column: 10)
!3122 = distinct !DILexicalBlock(scope: !3115, file: !1, line: 1077, column: 33)
!3123 = !DILocation(line: 1090, column: 16, scope: !3121)
!3124 = !DILocation(line: 1090, column: 23, scope: !3121)
!3125 = !DILocation(line: 1090, column: 29, scope: !3121)
!3126 = !DILocation(line: 1090, column: 10, scope: !3122)
!3127 = !DILocation(line: 1091, column: 22, scope: !3121)
!3128 = !DILocation(line: 1091, column: 36, scope: !3121)
!3129 = !DILocation(line: 1091, column: 50, scope: !3121)
!3130 = !DILocation(line: 1091, column: 14, scope: !3121)
!3131 = !DILocation(line: 1091, column: 12, scope: !3121)
!3132 = !DILocation(line: 1091, column: 9, scope: !3121)
!3133 = !DILocation(line: 1093, column: 12, scope: !3121)
!3134 = !DILocation(line: 1095, column: 5, scope: !3122)
!3135 = !DILocation(line: 1097, column: 20, scope: !3136)
!3136 = distinct !DILexicalBlock(scope: !3115, file: !1, line: 1096, column: 10)
!3137 = !DILocation(line: 1097, column: 34, scope: !3136)
!3138 = !DILocation(line: 1097, column: 48, scope: !3136)
!3139 = !DILocation(line: 1097, column: 12, scope: !3136)
!3140 = !DILocation(line: 1097, column: 10, scope: !3136)
!3141 = !DILocation(line: 1100, column: 14, scope: !3142)
!3142 = distinct !DILexicalBlock(scope: !3116, file: !1, line: 1100, column: 8)
!3143 = !DILocation(line: 1100, column: 11, scope: !3142)
!3144 = !DILocation(line: 1100, column: 8, scope: !3116)
!3145 = !DILocation(line: 1101, column: 15, scope: !3142)
!3146 = !DILocation(line: 1101, column: 13, scope: !3142)
!3147 = !DILocation(line: 1101, column: 7, scope: !3142)
!3148 = !DILocation(line: 1102, column: 3, scope: !3116)
!3149 = !DILocation(line: 1104, column: 14, scope: !3150)
!3150 = distinct !DILexicalBlock(scope: !3107, file: !1, line: 1103, column: 8)
!3151 = !DILocation(line: 1104, column: 6, scope: !3150)
!3152 = !DILocation(line: 1104, column: 12, scope: !3150)
!3153 = !DILocation(line: 1105, column: 5, scope: !3150)
!3154 = !DILocation(line: 1112, column: 12, scope: !3155)
!3155 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1112, column: 6)
!3156 = !DILocation(line: 1112, column: 9, scope: !3155)
!3157 = !DILocation(line: 1112, column: 6, scope: !1925)
!3158 = !DILocation(line: 1113, column: 12, scope: !3159)
!3159 = distinct !DILexicalBlock(scope: !3155, file: !1, line: 1112, column: 16)
!3160 = !DILocation(line: 1113, column: 5, scope: !3159)
!3161 = !DILocation(line: 1125, column: 14, scope: !3162)
!3162 = distinct !DILexicalBlock(scope: !3159, file: !1, line: 1113, column: 19)
!3163 = !DILocation(line: 1126, column: 7, scope: !3162)
!3164 = !DILocation(line: 1130, column: 13, scope: !3162)
!3165 = !DILocation(line: 1131, column: 13, scope: !3162)
!3166 = !DILocation(line: 1131, column: 38, scope: !3162)
!3167 = !DILocation(line: 1131, column: 44, scope: !3162)
!3168 = !DILocation(line: 1131, column: 24, scope: !3162)
!3169 = !DILocation(line: 1130, column: 7, scope: !3162)
!3170 = !DILocation(line: 1132, column: 30, scope: !3162)
!3171 = !DILocation(line: 1132, column: 7, scope: !3162)
!3172 = !DILocation(line: 1132, column: 13, scope: !3162)
!3173 = !DILocation(line: 1132, column: 19, scope: !3162)
!3174 = !DILocation(line: 1132, column: 28, scope: !3162)
!3175 = !DILocation(line: 1135, column: 24, scope: !3162)
!3176 = !DILocation(line: 1135, column: 30, scope: !3162)
!3177 = !DILocation(line: 1135, column: 7, scope: !3162)
!3178 = !DILocation(line: 1136, column: 14, scope: !3162)
!3179 = !DILocation(line: 1137, column: 5, scope: !3162)
!3180 = !DILocation(line: 1138, column: 3, scope: !3159)
!3181 = !DILocation(line: 1140, column: 7, scope: !3182)
!3182 = distinct !DILexicalBlock(scope: !1925, file: !1, line: 1140, column: 6)
!3183 = !DILocation(line: 1140, column: 6, scope: !1925)
!3184 = !DILocation(line: 1141, column: 14, scope: !3182)
!3185 = !DILocation(line: 1141, column: 6, scope: !3182)
!3186 = !DILocation(line: 1141, column: 12, scope: !3182)
!3187 = !DILocation(line: 1141, column: 5, scope: !3182)
!3188 = !DILocation(line: 1143, column: 10, scope: !1925)
!3189 = !DILocation(line: 1143, column: 3, scope: !1925)
!3190 = !DILocation(line: 1144, column: 1, scope: !1925)
!3191 = !DILocalVariable(name: "data", arg: 1, scope: !1864, file: !1, line: 1218, type: !256)
!3192 = !DILocation(line: 1218, column: 53, scope: !1864)
!3193 = !DILocalVariable(name: "connp", arg: 2, scope: !1864, file: !1, line: 1219, type: !1867)
!3194 = !DILocation(line: 1219, column: 56, scope: !1864)
!3195 = !DILocalVariable(name: "sockfd", scope: !1864, file: !1, line: 1221, type: !315)
!3196 = !DILocation(line: 1221, column: 17, scope: !1864)
!3197 = !DILocation(line: 1223, column: 3, scope: !1864)
!3198 = !DILocation(line: 1223, column: 3, scope: !3199)
!3199 = !DILexicalBlockFile(scope: !3200, file: !1, discriminator: 1)
!3200 = distinct !DILexicalBlock(scope: !1864, file: !1, line: 1223, column: 3)
!3201 = !DILocation(line: 1230, column: 6, scope: !3202)
!3202 = distinct !DILexicalBlock(scope: !1864, file: !1, line: 1230, column: 6)
!3203 = !DILocation(line: 1230, column: 12, scope: !3202)
!3204 = !DILocation(line: 1230, column: 18, scope: !3202)
!3205 = !DILocation(line: 1230, column: 30, scope: !3202)
!3206 = !DILocation(line: 1230, column: 34, scope: !3207)
!3207 = !DILexicalBlockFile(scope: !3202, file: !1, discriminator: 1)
!3208 = !DILocation(line: 1230, column: 40, scope: !3207)
!3209 = !DILocation(line: 1230, column: 51, scope: !3207)
!3210 = !DILocation(line: 1230, column: 54, scope: !3211)
!3211 = !DILexicalBlockFile(scope: !3202, file: !1, discriminator: 2)
!3212 = !DILocation(line: 1230, column: 60, scope: !3211)
!3213 = !DILocation(line: 1230, column: 6, scope: !3211)
!3214 = !DILocalVariable(name: "c", scope: !3215, file: !1, line: 1231, type: !262)
!3215 = distinct !DILexicalBlock(scope: !3202, file: !1, line: 1230, column: 68)
!3216 = !DILocation(line: 1231, column: 25, scope: !3215)
!3217 = !DILocation(line: 1231, column: 29, scope: !3215)
!3218 = !DILocation(line: 1231, column: 35, scope: !3215)
!3219 = !DILocation(line: 1231, column: 41, scope: !3215)
!3220 = !DILocalVariable(name: "find", scope: !3215, file: !1, line: 1232, type: !1839)
!3221 = !DILocation(line: 1232, column: 21, scope: !3215)
!3222 = !DILocation(line: 1233, column: 19, scope: !3215)
!3223 = !DILocation(line: 1233, column: 25, scope: !3215)
!3224 = !DILocation(line: 1233, column: 31, scope: !3215)
!3225 = !DILocation(line: 1233, column: 10, scope: !3215)
!3226 = !DILocation(line: 1233, column: 17, scope: !3215)
!3227 = !DILocation(line: 1234, column: 10, scope: !3215)
!3228 = !DILocation(line: 1234, column: 16, scope: !3215)
!3229 = !DILocation(line: 1236, column: 28, scope: !3215)
!3230 = !DILocation(line: 1236, column: 34, scope: !3215)
!3231 = !DILocation(line: 1237, column: 29, scope: !3215)
!3232 = !DILocation(line: 1237, column: 35, scope: !3215)
!3233 = !DILocation(line: 1237, column: 47, scope: !3215)
!3234 = !DILocation(line: 1236, column: 28, scope: !3235)
!3235 = !DILexicalBlockFile(scope: !3215, file: !1, discriminator: 1)
!3236 = !DILocation(line: 1238, column: 29, scope: !3215)
!3237 = !DILocation(line: 1238, column: 35, scope: !3215)
!3238 = !DILocation(line: 1238, column: 42, scope: !3215)
!3239 = !DILocation(line: 1236, column: 28, scope: !3240)
!3240 = !DILexicalBlockFile(scope: !3215, file: !1, discriminator: 2)
!3241 = !DILocation(line: 1236, column: 28, scope: !3242)
!3242 = !DILexicalBlockFile(scope: !3215, file: !1, discriminator: 3)
!3243 = !DILocation(line: 1238, column: 54, scope: !3235)
!3244 = !DILocation(line: 1236, column: 5, scope: !3242)
!3245 = !DILocation(line: 1240, column: 14, scope: !3246)
!3246 = distinct !DILexicalBlock(scope: !3215, file: !1, line: 1240, column: 8)
!3247 = !DILocation(line: 1240, column: 8, scope: !3215)
!3248 = !DILocation(line: 1241, column: 7, scope: !3249)
!3249 = distinct !DILexicalBlock(scope: !3246, file: !1, line: 1240, column: 21)
!3250 = !DILocation(line: 1241, column: 13, scope: !3249)
!3251 = !DILocation(line: 1241, column: 19, scope: !3249)
!3252 = !DILocation(line: 1241, column: 31, scope: !3249)
!3253 = !DILocation(line: 1242, column: 7, scope: !3249)
!3254 = !DILocation(line: 1245, column: 8, scope: !3255)
!3255 = distinct !DILexicalBlock(scope: !3215, file: !1, line: 1245, column: 8)
!3256 = !DILocation(line: 1245, column: 8, scope: !3215)
!3257 = !DILocation(line: 1247, column: 16, scope: !3255)
!3258 = !DILocation(line: 1247, column: 8, scope: !3255)
!3259 = !DILocation(line: 1247, column: 14, scope: !3255)
!3260 = !DILocation(line: 1247, column: 7, scope: !3255)
!3261 = !DILocation(line: 1248, column: 14, scope: !3215)
!3262 = !DILocation(line: 1248, column: 17, scope: !3215)
!3263 = !DILocation(line: 1248, column: 12, scope: !3215)
!3264 = !DILocation(line: 1249, column: 3, scope: !3215)
!3265 = !DILocation(line: 1251, column: 5, scope: !3202)
!3266 = !DILocation(line: 1253, column: 10, scope: !1864)
!3267 = !DILocation(line: 1253, column: 3, scope: !1864)
!3268 = !DILocation(line: 1254, column: 1, scope: !1864)
!3269 = !DILocalVariable(name: "conn", arg: 1, scope: !1934, file: !1, line: 1202, type: !262)
!3270 = !DILocation(line: 1202, column: 45, scope: !1934)
!3271 = !DILocalVariable(name: "param", arg: 2, scope: !1934, file: !1, line: 1202, type: !311)
!3272 = !DILocation(line: 1202, column: 57, scope: !1934)
!3273 = !DILocalVariable(name: "f", scope: !1934, file: !1, line: 1204, type: !1838)
!3274 = !DILocation(line: 1204, column: 20, scope: !1934)
!3275 = !DILocation(line: 1204, column: 43, scope: !1934)
!3276 = !DILocation(line: 1204, column: 24, scope: !1934)
!3277 = !DILocation(line: 1205, column: 6, scope: !3278)
!3278 = distinct !DILexicalBlock(scope: !1934, file: !1, line: 1205, column: 6)
!3279 = !DILocation(line: 1205, column: 14, scope: !3278)
!3280 = !DILocation(line: 1205, column: 17, scope: !3278)
!3281 = !DILocation(line: 1205, column: 11, scope: !3278)
!3282 = !DILocation(line: 1205, column: 6, scope: !1934)
!3283 = !DILocation(line: 1206, column: 5, scope: !3284)
!3284 = distinct !DILexicalBlock(scope: !3278, file: !1, line: 1205, column: 25)
!3285 = !DILocation(line: 1206, column: 8, scope: !3284)
!3286 = !DILocation(line: 1206, column: 14, scope: !3284)
!3287 = !DILocation(line: 1207, column: 5, scope: !3284)
!3288 = !DILocation(line: 1209, column: 3, scope: !1934)
!3289 = !DILocation(line: 1210, column: 1, scope: !1934)
!3290 = !DILocalVariable(name: "conn", arg: 1, scope: !1868, file: !1, line: 1259, type: !262)
!3291 = !DILocation(line: 1259, column: 41, scope: !1868)
!3292 = !DILocation(line: 1262, column: 6, scope: !3293)
!3293 = distinct !DILexicalBlock(scope: !1868, file: !1, line: 1262, column: 6)
!3294 = !DILocation(line: 1262, column: 12, scope: !3293)
!3295 = !DILocation(line: 1262, column: 29, scope: !3293)
!3296 = !DILocation(line: 1262, column: 6, scope: !1868)
!3297 = !DILocation(line: 1265, column: 7, scope: !3298)
!3298 = distinct !DILexicalBlock(scope: !3299, file: !1, line: 1264, column: 8)
!3299 = distinct !DILexicalBlock(scope: !3293, file: !1, line: 1262, column: 34)
!3300 = !DILocation(line: 1269, column: 11, scope: !3301)
!3301 = distinct !DILexicalBlock(scope: !3293, file: !1, line: 1269, column: 11)
!3302 = !DILocation(line: 1269, column: 17, scope: !3301)
!3303 = !DILocation(line: 1269, column: 35, scope: !3301)
!3304 = !DILocation(line: 1269, column: 11, scope: !3293)
!3305 = !DILocation(line: 1270, column: 5, scope: !3301)
!3306 = !DILocalVariable(name: "buf", scope: !3307, file: !1, line: 1273, type: !480)
!3307 = distinct !DILexicalBlock(scope: !3301, file: !1, line: 1271, column: 8)
!3308 = !DILocation(line: 1273, column: 10, scope: !3307)
!3309 = !DILocation(line: 1274, column: 29, scope: !3310)
!3310 = distinct !DILexicalBlock(scope: !3307, file: !1, line: 1274, column: 8)
!3311 = !DILocation(line: 1274, column: 35, scope: !3310)
!3312 = !DILocation(line: 1274, column: 8, scope: !3310)
!3313 = !DILocation(line: 1275, column: 58, scope: !3310)
!3314 = !DILocation(line: 1274, column: 8, scope: !3307)
!3315 = !DILocation(line: 1276, column: 7, scope: !3316)
!3316 = distinct !DILexicalBlock(scope: !3310, file: !1, line: 1275, column: 64)
!3317 = !DILocation(line: 1280, column: 3, scope: !1868)
!3318 = !DILocation(line: 1281, column: 1, scope: !1868)
!3319 = !DILocalVariable(name: "conn", arg: 1, scope: !1874, file: !1, line: 1322, type: !262)
!3320 = !DILocation(line: 1322, column: 42, scope: !1874)
!3321 = !DILocalVariable(name: "ai", arg: 2, scope: !1874, file: !1, line: 1323, type: !1877)
!3322 = !DILocation(line: 1323, column: 43, scope: !1874)
!3323 = !DILocalVariable(name: "addr", arg: 3, scope: !1874, file: !1, line: 1324, type: !1879)
!3324 = !DILocation(line: 1324, column: 47, scope: !1874)
!3325 = !DILocalVariable(name: "sockfd", arg: 4, scope: !1874, file: !1, line: 1325, type: !1442)
!3326 = !DILocation(line: 1325, column: 37, scope: !1874)
!3327 = !DILocalVariable(name: "data", scope: !1874, file: !1, line: 1327, type: !256)
!3328 = !DILocation(line: 1327, column: 21, scope: !1874)
!3329 = !DILocation(line: 1327, column: 28, scope: !1874)
!3330 = !DILocation(line: 1327, column: 34, scope: !1874)
!3331 = !DILocalVariable(name: "dummy", scope: !1874, file: !1, line: 1328, type: !1880)
!3332 = !DILocation(line: 1328, column: 27, scope: !1874)
!3333 = !DILocation(line: 1330, column: 7, scope: !3334)
!3334 = distinct !DILexicalBlock(scope: !1874, file: !1, line: 1330, column: 6)
!3335 = !DILocation(line: 1330, column: 6, scope: !1874)
!3336 = !DILocation(line: 1332, column: 10, scope: !3334)
!3337 = !DILocation(line: 1332, column: 5, scope: !3334)
!3338 = !DILocation(line: 1342, column: 18, scope: !1874)
!3339 = !DILocation(line: 1342, column: 22, scope: !1874)
!3340 = !DILocation(line: 1342, column: 3, scope: !1874)
!3341 = !DILocation(line: 1342, column: 9, scope: !1874)
!3342 = !DILocation(line: 1342, column: 16, scope: !1874)
!3343 = !DILocation(line: 1343, column: 20, scope: !1874)
!3344 = !DILocation(line: 1343, column: 26, scope: !1874)
!3345 = !DILocation(line: 1343, column: 3, scope: !1874)
!3346 = !DILocation(line: 1343, column: 9, scope: !1874)
!3347 = !DILocation(line: 1343, column: 18, scope: !1874)
!3348 = !DILocation(line: 1344, column: 20, scope: !1874)
!3349 = !DILocation(line: 1344, column: 26, scope: !1874)
!3350 = !DILocation(line: 1344, column: 34, scope: !1874)
!3351 = !DILocation(line: 1344, column: 20, scope: !3352)
!3352 = !DILexicalBlockFile(scope: !1874, file: !1, discriminator: 1)
!3353 = !DILocation(line: 1344, column: 59, scope: !3354)
!3354 = !DILexicalBlockFile(scope: !1874, file: !1, discriminator: 2)
!3355 = !DILocation(line: 1344, column: 63, scope: !3354)
!3356 = !DILocation(line: 1344, column: 20, scope: !3354)
!3357 = !DILocation(line: 1344, column: 20, scope: !3358)
!3358 = !DILexicalBlockFile(scope: !1874, file: !1, discriminator: 3)
!3359 = !DILocation(line: 1344, column: 3, scope: !3358)
!3360 = !DILocation(line: 1344, column: 9, scope: !3358)
!3361 = !DILocation(line: 1344, column: 18, scope: !3358)
!3362 = !DILocation(line: 1345, column: 19, scope: !1874)
!3363 = !DILocation(line: 1345, column: 23, scope: !1874)
!3364 = !DILocation(line: 1345, column: 3, scope: !1874)
!3365 = !DILocation(line: 1345, column: 9, scope: !1874)
!3366 = !DILocation(line: 1345, column: 17, scope: !1874)
!3367 = !DILocation(line: 1347, column: 6, scope: !3368)
!3368 = distinct !DILexicalBlock(scope: !1874, file: !1, line: 1347, column: 6)
!3369 = !DILocation(line: 1347, column: 12, scope: !3368)
!3370 = !DILocation(line: 1347, column: 20, scope: !3368)
!3371 = !DILocation(line: 1347, column: 6, scope: !1874)
!3372 = !DILocation(line: 1348, column: 6, scope: !3368)
!3373 = !DILocation(line: 1348, column: 12, scope: !3368)
!3374 = !DILocation(line: 1348, column: 20, scope: !3368)
!3375 = !DILocation(line: 1349, column: 11, scope: !1874)
!3376 = !DILocation(line: 1349, column: 17, scope: !1874)
!3377 = !DILocation(line: 1349, column: 3, scope: !1874)
!3378 = !DILocation(line: 1349, column: 26, scope: !1874)
!3379 = !DILocation(line: 1349, column: 30, scope: !1874)
!3380 = !DILocation(line: 1349, column: 39, scope: !1874)
!3381 = !DILocation(line: 1349, column: 45, scope: !1874)
!3382 = !DILocation(line: 1351, column: 6, scope: !3383)
!3383 = distinct !DILexicalBlock(scope: !1874, file: !1, line: 1351, column: 6)
!3384 = !DILocation(line: 1351, column: 12, scope: !3383)
!3385 = !DILocation(line: 1351, column: 16, scope: !3383)
!3386 = !DILocation(line: 1351, column: 6, scope: !1874)
!3387 = !DILocation(line: 1361, column: 15, scope: !3383)
!3388 = !DILocation(line: 1361, column: 21, scope: !3383)
!3389 = !DILocation(line: 1361, column: 25, scope: !3383)
!3390 = !DILocation(line: 1361, column: 37, scope: !3383)
!3391 = !DILocation(line: 1361, column: 43, scope: !3383)
!3392 = !DILocation(line: 1361, column: 47, scope: !3383)
!3393 = !DILocation(line: 1363, column: 61, scope: !3383)
!3394 = !DILocation(line: 1363, column: 37, scope: !3383)
!3395 = !DILocation(line: 1361, column: 6, scope: !3383)
!3396 = !DILocation(line: 1361, column: 13, scope: !3383)
!3397 = !DILocation(line: 1361, column: 5, scope: !3383)
!3398 = !DILocation(line: 1366, column: 22, scope: !3383)
!3399 = !DILocation(line: 1366, column: 28, scope: !3383)
!3400 = !DILocation(line: 1366, column: 36, scope: !3383)
!3401 = !DILocation(line: 1366, column: 42, scope: !3383)
!3402 = !DILocation(line: 1366, column: 52, scope: !3383)
!3403 = !DILocation(line: 1366, column: 58, scope: !3383)
!3404 = !DILocation(line: 1366, column: 15, scope: !3383)
!3405 = !DILocation(line: 1366, column: 6, scope: !3383)
!3406 = !DILocation(line: 1366, column: 13, scope: !3383)
!3407 = !DILocation(line: 1368, column: 7, scope: !3408)
!3408 = distinct !DILexicalBlock(scope: !1874, file: !1, line: 1368, column: 6)
!3409 = !DILocation(line: 1368, column: 6, scope: !3408)
!3410 = !DILocation(line: 1368, column: 14, scope: !3408)
!3411 = !DILocation(line: 1368, column: 6, scope: !1874)
!3412 = !DILocation(line: 1370, column: 5, scope: !3408)
!3413 = !DILocation(line: 1379, column: 3, scope: !1874)
!3414 = !DILocation(line: 1381, column: 1, scope: !1874)
!3415 = !DILocalVariable(name: "conn", arg: 1, scope: !1909, file: !1, line: 1386, type: !262)
!3416 = !DILocation(line: 1386, column: 43, scope: !1909)
!3417 = !DILocalVariable(name: "ctrl", arg: 2, scope: !1909, file: !1, line: 1387, type: !316)
!3418 = !DILocation(line: 1387, column: 27, scope: !1909)
!3419 = !DILocalVariable(name: "closeit", scope: !1909, file: !1, line: 1394, type: !423)
!3420 = !DILocation(line: 1394, column: 8, scope: !1909)
!3421 = !DILocation(line: 1394, column: 19, scope: !1909)
!3422 = !DILocation(line: 1394, column: 24, scope: !1909)
!3423 = !DILocation(line: 1394, column: 48, scope: !1909)
!3424 = !DILocation(line: 1395, column: 7, scope: !1909)
!3425 = !DILocation(line: 1395, column: 12, scope: !1909)
!3426 = !DILocation(line: 1395, column: 32, scope: !1909)
!3427 = !DILocation(line: 1395, column: 37, scope: !3428)
!3428 = !DILexicalBlockFile(scope: !1909, file: !1, discriminator: 1)
!3429 = !DILocation(line: 1395, column: 43, scope: !3428)
!3430 = !DILocation(line: 1395, column: 52, scope: !3428)
!3431 = !DILocation(line: 1395, column: 58, scope: !3428)
!3432 = !DILocation(line: 1395, column: 35, scope: !3428)
!3433 = !DILocation(line: 1394, column: 48, scope: !3428)
!3434 = !DILocation(line: 1394, column: 8, scope: !3435)
!3435 = !DILexicalBlockFile(scope: !1909, file: !1, discriminator: 2)
!3436 = !DILocation(line: 1396, column: 7, scope: !3437)
!3437 = distinct !DILexicalBlock(scope: !1909, file: !1, line: 1396, column: 6)
!3438 = !DILocation(line: 1396, column: 12, scope: !3437)
!3439 = !DILocation(line: 1396, column: 32, scope: !3437)
!3440 = !DILocation(line: 1397, column: 7, scope: !3437)
!3441 = !DILocation(line: 1397, column: 13, scope: !3437)
!3442 = !DILocation(line: 1397, column: 22, scope: !3437)
!3443 = !DILocation(line: 1397, column: 28, scope: !3437)
!3444 = !DILocation(line: 1396, column: 6, scope: !3428)
!3445 = !DILocation(line: 1398, column: 5, scope: !3437)
!3446 = !DILocation(line: 1398, column: 5, scope: !3447)
!3447 = !DILexicalBlockFile(scope: !3448, file: !1, discriminator: 1)
!3448 = distinct !DILexicalBlock(scope: !3437, file: !1, line: 1398, column: 5)
!3449 = !DILocation(line: 1398, column: 5, scope: !3450)
!3450 = !DILexicalBlockFile(scope: !3448, file: !1, discriminator: 2)
!3451 = !DILocation(line: 1399, column: 11, scope: !3452)
!3452 = distinct !DILexicalBlock(scope: !3437, file: !1, line: 1399, column: 11)
!3453 = !DILocation(line: 1399, column: 22, scope: !3452)
!3454 = !DILocation(line: 1399, column: 28, scope: !3452)
!3455 = !DILocation(line: 1399, column: 33, scope: !3452)
!3456 = !DILocation(line: 1399, column: 19, scope: !3452)
!3457 = !DILocation(line: 1399, column: 11, scope: !3437)
!3458 = !DILocation(line: 1400, column: 5, scope: !3459)
!3459 = distinct !DILexicalBlock(scope: !3452, file: !1, line: 1399, column: 40)
!3460 = !DILocation(line: 1400, column: 5, scope: !3461)
!3461 = !DILexicalBlockFile(scope: !3462, file: !1, discriminator: 1)
!3462 = distinct !DILexicalBlock(scope: !3459, file: !1, line: 1400, column: 5)
!3463 = !DILocation(line: 1402, column: 24, scope: !3459)
!3464 = !DILocation(line: 1402, column: 5, scope: !3459)
!3465 = !DILocation(line: 1402, column: 11, scope: !3459)
!3466 = !DILocation(line: 1402, column: 16, scope: !3459)
!3467 = !DILocation(line: 1402, column: 22, scope: !3459)
!3468 = !DILocation(line: 1404, column: 3, scope: !3459)
!3469 = !DILocation(line: 1405, column: 1, scope: !1909)
!3470 = !DILocalVariable(name: "conn", arg: 1, scope: !1912, file: !1, line: 1408, type: !262)
!3471 = !DILocation(line: 1408, column: 49, scope: !1912)
!3472 = !DILocalVariable(name: "sockindex", arg: 2, scope: !1912, file: !1, line: 1408, type: !316)
!3473 = !DILocation(line: 1408, column: 59, scope: !1912)
!3474 = !DILocalVariable(name: "readable", scope: !1912, file: !1, line: 1410, type: !316)
!3475 = !DILocation(line: 1410, column: 7, scope: !1912)
!3476 = !DILocation(line: 1413, column: 35, scope: !3477)
!3477 = distinct !DILexicalBlock(scope: !1912, file: !1, line: 1412, column: 6)
!3478 = !DILocation(line: 1413, column: 41, scope: !3477)
!3479 = !DILocation(line: 1413, column: 6, scope: !3477)
!3480 = !DILocation(line: 1412, column: 6, scope: !1912)
!3481 = !DILocation(line: 1414, column: 5, scope: !3477)
!3482 = !DILocation(line: 1416, column: 14, scope: !1912)
!3483 = !DILocation(line: 1416, column: 12, scope: !1912)
!3484 = !DILocation(line: 1417, column: 11, scope: !1912)
!3485 = !DILocation(line: 1417, column: 20, scope: !1912)
!3486 = !DILocation(line: 1417, column: 24, scope: !1912)
!3487 = !DILocation(line: 1417, column: 28, scope: !3488)
!3488 = !DILexicalBlockFile(scope: !1912, file: !1, discriminator: 1)
!3489 = !DILocation(line: 1417, column: 37, scope: !3488)
!3490 = !DILocation(line: 1417, column: 24, scope: !3488)
!3491 = !DILocation(line: 1417, column: 3, scope: !3492)
!3492 = !DILexicalBlockFile(scope: !1912, file: !1, discriminator: 2)
!3493 = !DILocation(line: 1418, column: 1, scope: !1912)
!3494 = !DILocalVariable(name: "data", arg: 1, scope: !1928, file: !1, line: 107, type: !256)
!3495 = !DILocation(line: 107, column: 32, scope: !1928)
!3496 = !DILocalVariable(name: "sockfd", arg: 2, scope: !1928, file: !1, line: 108, type: !315)
!3497 = !DILocation(line: 108, column: 28, scope: !1928)
!3498 = !DILocalVariable(name: "optval", scope: !1928, file: !1, line: 110, type: !316)
!3499 = !DILocation(line: 110, column: 7, scope: !1928)
!3500 = !DILocation(line: 110, column: 16, scope: !1928)
!3501 = !DILocation(line: 110, column: 22, scope: !1928)
!3502 = !DILocation(line: 110, column: 26, scope: !1928)
!3503 = !DILocation(line: 113, column: 17, scope: !3504)
!3504 = distinct !DILexicalBlock(scope: !1928, file: !1, line: 113, column: 6)
!3505 = !DILocation(line: 114, column: 9, scope: !3504)
!3506 = !DILocation(line: 113, column: 6, scope: !3504)
!3507 = !DILocation(line: 114, column: 42, scope: !3504)
!3508 = !DILocation(line: 113, column: 6, scope: !1928)
!3509 = !DILocation(line: 115, column: 11, scope: !3510)
!3510 = distinct !DILexicalBlock(scope: !3504, file: !1, line: 114, column: 47)
!3511 = !DILocation(line: 115, column: 58, scope: !3510)
!3512 = !DILocation(line: 115, column: 5, scope: !3510)
!3513 = !DILocation(line: 116, column: 3, scope: !3510)
!3514 = !DILocation(line: 135, column: 27, scope: !3515)
!3515 = distinct !DILexicalBlock(scope: !3504, file: !1, line: 117, column: 8)
!3516 = !DILocation(line: 135, column: 33, scope: !3515)
!3517 = !DILocation(line: 135, column: 37, scope: !3515)
!3518 = !DILocation(line: 135, column: 14, scope: !3515)
!3519 = !DILocation(line: 135, column: 12, scope: !3515)
!3520 = !DILocation(line: 137, column: 19, scope: !3521)
!3521 = distinct !DILexicalBlock(scope: !3515, file: !1, line: 137, column: 8)
!3522 = !DILocation(line: 138, column: 11, scope: !3521)
!3523 = !DILocation(line: 137, column: 8, scope: !3521)
!3524 = !DILocation(line: 138, column: 44, scope: !3521)
!3525 = !DILocation(line: 137, column: 8, scope: !3515)
!3526 = !DILocation(line: 139, column: 13, scope: !3527)
!3527 = distinct !DILexicalBlock(scope: !3521, file: !1, line: 138, column: 49)
!3528 = !DILocation(line: 139, column: 60, scope: !3527)
!3529 = !DILocation(line: 139, column: 7, scope: !3527)
!3530 = !DILocation(line: 140, column: 5, scope: !3527)
!3531 = !DILocation(line: 143, column: 27, scope: !3515)
!3532 = !DILocation(line: 143, column: 33, scope: !3515)
!3533 = !DILocation(line: 143, column: 37, scope: !3515)
!3534 = !DILocation(line: 143, column: 14, scope: !3515)
!3535 = !DILocation(line: 143, column: 12, scope: !3515)
!3536 = !DILocation(line: 145, column: 19, scope: !3537)
!3537 = distinct !DILexicalBlock(scope: !3515, file: !1, line: 145, column: 8)
!3538 = !DILocation(line: 146, column: 11, scope: !3537)
!3539 = !DILocation(line: 145, column: 8, scope: !3537)
!3540 = !DILocation(line: 146, column: 44, scope: !3537)
!3541 = !DILocation(line: 145, column: 8, scope: !3515)
!3542 = !DILocation(line: 147, column: 13, scope: !3543)
!3543 = distinct !DILexicalBlock(scope: !3537, file: !1, line: 146, column: 49)
!3544 = !DILocation(line: 147, column: 61, scope: !3543)
!3545 = !DILocation(line: 147, column: 7, scope: !3543)
!3546 = !DILocation(line: 148, column: 5, scope: !3543)
!3547 = !DILocation(line: 161, column: 1, scope: !1928)
!3548 = !DILocalVariable(name: "conn", arg: 1, scope: !1931, file: !1, line: 239, type: !262)
!3549 = !DILocation(line: 239, column: 47, scope: !1931)
!3550 = !DILocalVariable(name: "sockfd", arg: 2, scope: !1931, file: !1, line: 240, type: !315)
!3551 = !DILocation(line: 240, column: 41, scope: !1931)
!3552 = !DILocalVariable(name: "af", arg: 3, scope: !1931, file: !1, line: 240, type: !316)
!3553 = !DILocation(line: 240, column: 53, scope: !1931)
!3554 = !DILocalVariable(name: "scope", arg: 4, scope: !1931, file: !1, line: 240, type: !683)
!3555 = !DILocation(line: 240, column: 70, scope: !1931)
!3556 = !DILocalVariable(name: "data", scope: !1931, file: !1, line: 242, type: !256)
!3557 = !DILocation(line: 242, column: 21, scope: !1931)
!3558 = !DILocation(line: 242, column: 28, scope: !1931)
!3559 = !DILocation(line: 242, column: 34, scope: !1931)
!3560 = !DILocalVariable(name: "sa", scope: !1931, file: !1, line: 244, type: !1892)
!3561 = !DILocation(line: 244, column: 32, scope: !1931)
!3562 = !DILocalVariable(name: "sock", scope: !1931, file: !1, line: 245, type: !1292)
!3563 = !DILocation(line: 245, column: 20, scope: !1931)
!3564 = !DILocation(line: 245, column: 27, scope: !1931)
!3565 = !DILocalVariable(name: "sizeof_sa", scope: !1931, file: !1, line: 246, type: !1287)
!3566 = !DILocation(line: 246, column: 18, scope: !1931)
!3567 = !DILocalVariable(name: "si4", scope: !1931, file: !1, line: 247, type: !1814)
!3568 = !DILocation(line: 247, column: 23, scope: !1931)
!3569 = !DILocation(line: 247, column: 29, scope: !1931)
!3570 = !DILocalVariable(name: "h", scope: !1931, file: !1, line: 252, type: !1272)
!3571 = !DILocation(line: 252, column: 26, scope: !1931)
!3572 = !DILocalVariable(name: "port", scope: !1931, file: !1, line: 253, type: !564)
!3573 = !DILocation(line: 253, column: 18, scope: !1931)
!3574 = !DILocation(line: 253, column: 25, scope: !1931)
!3575 = !DILocation(line: 253, column: 31, scope: !1931)
!3576 = !DILocation(line: 253, column: 35, scope: !1931)
!3577 = !DILocalVariable(name: "portnum", scope: !1931, file: !1, line: 256, type: !316)
!3578 = !DILocation(line: 256, column: 7, scope: !1931)
!3579 = !DILocation(line: 256, column: 17, scope: !1931)
!3580 = !DILocation(line: 256, column: 23, scope: !1931)
!3581 = !DILocation(line: 256, column: 27, scope: !1931)
!3582 = !DILocalVariable(name: "dev", scope: !1931, file: !1, line: 257, type: !851)
!3583 = !DILocation(line: 257, column: 15, scope: !1931)
!3584 = !DILocation(line: 257, column: 21, scope: !1931)
!3585 = !DILocation(line: 257, column: 27, scope: !1931)
!3586 = !DILocation(line: 257, column: 31, scope: !1931)
!3587 = !DILocalVariable(name: "error", scope: !1931, file: !1, line: 258, type: !316)
!3588 = !DILocation(line: 258, column: 7, scope: !1931)
!3589 = !DILocation(line: 263, column: 7, scope: !3590)
!3590 = distinct !DILexicalBlock(scope: !1931, file: !1, line: 263, column: 6)
!3591 = !DILocation(line: 263, column: 11, scope: !3590)
!3592 = !DILocation(line: 263, column: 15, scope: !3593)
!3593 = !DILexicalBlockFile(scope: !3590, file: !1, discriminator: 1)
!3594 = !DILocation(line: 263, column: 6, scope: !3593)
!3595 = !DILocation(line: 265, column: 5, scope: !3590)
!3596 = !DILocation(line: 267, column: 3, scope: !1931)
!3597 = !DILocation(line: 269, column: 6, scope: !3598)
!3598 = distinct !DILexicalBlock(scope: !1931, file: !1, line: 269, column: 6)
!3599 = !DILocation(line: 269, column: 10, scope: !3598)
!3600 = !DILocation(line: 269, column: 21, scope: !3601)
!3601 = !DILexicalBlockFile(scope: !3598, file: !1, discriminator: 1)
!3602 = !DILocation(line: 269, column: 14, scope: !3601)
!3603 = !DILocation(line: 269, column: 25, scope: !3601)
!3604 = !DILocation(line: 269, column: 6, scope: !3601)
!3605 = !DILocalVariable(name: "myhost", scope: !3606, file: !1, line: 270, type: !1490)
!3606 = distinct !DILexicalBlock(scope: !3598, file: !1, line: 269, column: 33)
!3607 = !DILocation(line: 270, column: 10, scope: !3606)
!3608 = !DILocalVariable(name: "done", scope: !3606, file: !1, line: 271, type: !316)
!3609 = !DILocation(line: 271, column: 9, scope: !3606)
!3610 = !DILocalVariable(name: "is_interface", scope: !3606, file: !1, line: 272, type: !423)
!3611 = !DILocation(line: 272, column: 10, scope: !3606)
!3612 = !DILocalVariable(name: "is_host", scope: !3606, file: !1, line: 273, type: !423)
!3613 = !DILocation(line: 273, column: 10, scope: !3606)
!3614 = !DILocation(line: 277, column: 16, scope: !3615)
!3615 = distinct !DILexicalBlock(scope: !3606, file: !1, line: 277, column: 8)
!3616 = !DILocation(line: 277, column: 27, scope: !3615)
!3617 = !DILocation(line: 277, column: 39, scope: !3615)
!3618 = !DILocation(line: 277, column: 32, scope: !3615)
!3619 = !DILocation(line: 277, column: 8, scope: !3620)
!3620 = !DILexicalBlockFile(scope: !3615, file: !1, discriminator: 1)
!3621 = !DILocation(line: 277, column: 51, scope: !3615)
!3622 = !DILocation(line: 277, column: 8, scope: !3606)
!3623 = !DILocation(line: 278, column: 21, scope: !3624)
!3624 = distinct !DILexicalBlock(scope: !3615, file: !1, line: 277, column: 57)
!3625 = !DILocation(line: 278, column: 14, scope: !3624)
!3626 = !DILocation(line: 278, column: 11, scope: !3624)
!3627 = !DILocation(line: 279, column: 20, scope: !3624)
!3628 = !DILocation(line: 280, column: 5, scope: !3624)
!3629 = !DILocation(line: 281, column: 21, scope: !3630)
!3630 = distinct !DILexicalBlock(scope: !3615, file: !1, line: 281, column: 13)
!3631 = !DILocation(line: 281, column: 34, scope: !3630)
!3632 = !DILocation(line: 281, column: 46, scope: !3630)
!3633 = !DILocation(line: 281, column: 39, scope: !3630)
!3634 = !DILocation(line: 281, column: 13, scope: !3635)
!3635 = !DILexicalBlockFile(scope: !3630, file: !1, discriminator: 1)
!3636 = !DILocation(line: 281, column: 60, scope: !3630)
!3637 = !DILocation(line: 281, column: 13, scope: !3615)
!3638 = !DILocation(line: 282, column: 21, scope: !3639)
!3639 = distinct !DILexicalBlock(scope: !3630, file: !1, line: 281, column: 66)
!3640 = !DILocation(line: 282, column: 14, scope: !3639)
!3641 = !DILocation(line: 282, column: 11, scope: !3639)
!3642 = !DILocation(line: 283, column: 15, scope: !3639)
!3643 = !DILocation(line: 284, column: 5, scope: !3639)
!3644 = !DILocation(line: 287, column: 9, scope: !3645)
!3645 = distinct !DILexicalBlock(scope: !3606, file: !1, line: 287, column: 8)
!3646 = !DILocation(line: 287, column: 8, scope: !3606)
!3647 = !DILocation(line: 288, column: 25, scope: !3648)
!3648 = distinct !DILexicalBlock(scope: !3645, file: !1, line: 287, column: 18)
!3649 = !DILocation(line: 288, column: 29, scope: !3648)
!3650 = !DILocation(line: 288, column: 36, scope: !3648)
!3651 = !DILocation(line: 288, column: 42, scope: !3648)
!3652 = !DILocation(line: 288, column: 52, scope: !3648)
!3653 = !DILocation(line: 289, column: 25, scope: !3648)
!3654 = !DILocation(line: 288, column: 14, scope: !3648)
!3655 = !DILocation(line: 288, column: 7, scope: !3648)
!3656 = !DILocation(line: 291, column: 14, scope: !3657)
!3657 = distinct !DILexicalBlock(scope: !3658, file: !1, line: 291, column: 14)
!3658 = distinct !DILexicalBlock(scope: !3648, file: !1, line: 289, column: 50)
!3659 = !DILocation(line: 291, column: 14, scope: !3658)
!3660 = !DILocation(line: 293, column: 19, scope: !3661)
!3661 = distinct !DILexicalBlock(scope: !3657, file: !1, line: 291, column: 28)
!3662 = !DILocation(line: 293, column: 60, scope: !3661)
!3663 = !DILocation(line: 293, column: 13, scope: !3661)
!3664 = !DILocation(line: 294, column: 13, scope: !3661)
!3665 = !DILocation(line: 296, column: 11, scope: !3658)
!3666 = !DILocation(line: 299, column: 11, scope: !3658)
!3667 = !DILocation(line: 301, column: 24, scope: !3658)
!3668 = !DILocation(line: 305, column: 17, scope: !3658)
!3669 = !DILocation(line: 306, column: 17, scope: !3658)
!3670 = !DILocation(line: 306, column: 22, scope: !3658)
!3671 = !DILocation(line: 306, column: 30, scope: !3658)
!3672 = !DILocation(line: 305, column: 11, scope: !3658)
!3673 = !DILocation(line: 307, column: 16, scope: !3658)
!3674 = !DILocation(line: 321, column: 25, scope: !3675)
!3675 = distinct !DILexicalBlock(scope: !3658, file: !1, line: 321, column: 14)
!3676 = !DILocation(line: 322, column: 25, scope: !3675)
!3677 = !DILocation(line: 322, column: 53, scope: !3675)
!3678 = !DILocation(line: 322, column: 46, scope: !3675)
!3679 = !DILocation(line: 322, column: 30, scope: !3675)
!3680 = !DILocation(line: 322, column: 57, scope: !3675)
!3681 = !DILocation(line: 321, column: 14, scope: !3675)
!3682 = !DILocation(line: 322, column: 61, scope: !3675)
!3683 = !DILocation(line: 321, column: 14, scope: !3658)
!3684 = !DILocation(line: 323, column: 21, scope: !3685)
!3685 = distinct !DILexicalBlock(scope: !3675, file: !1, line: 322, column: 67)
!3686 = !DILocation(line: 323, column: 19, scope: !3685)
!3687 = !DILocation(line: 324, column: 19, scope: !3685)
!3688 = !DILocation(line: 326, column: 19, scope: !3685)
!3689 = !DILocation(line: 326, column: 24, scope: !3685)
!3690 = !DILocation(line: 326, column: 45, scope: !3685)
!3691 = !DILocation(line: 326, column: 51, scope: !3685)
!3692 = !DILocation(line: 326, column: 31, scope: !3685)
!3693 = !DILocation(line: 324, column: 13, scope: !3685)
!3694 = !DILocation(line: 330, column: 11, scope: !3685)
!3695 = !DILocation(line: 332, column: 11, scope: !3658)
!3696 = !DILocation(line: 334, column: 5, scope: !3648)
!3697 = !DILocation(line: 335, column: 9, scope: !3698)
!3698 = distinct !DILexicalBlock(scope: !3606, file: !1, line: 335, column: 8)
!3699 = !DILocation(line: 335, column: 8, scope: !3606)
!3700 = !DILocalVariable(name: "ipver", scope: !3701, file: !1, line: 344, type: !379)
!3701 = distinct !DILexicalBlock(scope: !3698, file: !1, line: 335, column: 23)
!3702 = !DILocation(line: 344, column: 12, scope: !3701)
!3703 = !DILocation(line: 344, column: 20, scope: !3701)
!3704 = !DILocation(line: 344, column: 26, scope: !3701)
!3705 = !DILocalVariable(name: "rc", scope: !3701, file: !1, line: 345, type: !316)
!3706 = !DILocation(line: 345, column: 11, scope: !3701)
!3707 = !DILocation(line: 347, column: 10, scope: !3708)
!3708 = distinct !DILexicalBlock(scope: !3701, file: !1, line: 347, column: 10)
!3709 = !DILocation(line: 347, column: 13, scope: !3708)
!3710 = !DILocation(line: 347, column: 10, scope: !3701)
!3711 = !DILocation(line: 348, column: 9, scope: !3708)
!3712 = !DILocation(line: 348, column: 15, scope: !3708)
!3713 = !DILocation(line: 348, column: 26, scope: !3708)
!3714 = !DILocation(line: 354, column: 24, scope: !3701)
!3715 = !DILocation(line: 354, column: 30, scope: !3701)
!3716 = !DILocation(line: 354, column: 12, scope: !3701)
!3717 = !DILocation(line: 354, column: 10, scope: !3701)
!3718 = !DILocation(line: 355, column: 10, scope: !3719)
!3719 = distinct !DILexicalBlock(scope: !3701, file: !1, line: 355, column: 10)
!3720 = !DILocation(line: 355, column: 13, scope: !3719)
!3721 = !DILocation(line: 355, column: 10, scope: !3701)
!3722 = !DILocation(line: 356, column: 9, scope: !3719)
!3723 = !DILocation(line: 357, column: 26, scope: !3701)
!3724 = !DILocation(line: 357, column: 7, scope: !3701)
!3725 = !DILocation(line: 357, column: 13, scope: !3701)
!3726 = !DILocation(line: 357, column: 24, scope: !3701)
!3727 = !DILocation(line: 359, column: 10, scope: !3728)
!3728 = distinct !DILexicalBlock(scope: !3701, file: !1, line: 359, column: 10)
!3729 = !DILocation(line: 359, column: 10, scope: !3701)
!3730 = !DILocation(line: 361, column: 32, scope: !3731)
!3731 = distinct !DILexicalBlock(scope: !3728, file: !1, line: 359, column: 13)
!3732 = !DILocation(line: 361, column: 35, scope: !3731)
!3733 = !DILocation(line: 361, column: 41, scope: !3731)
!3734 = !DILocation(line: 361, column: 9, scope: !3731)
!3735 = !DILocation(line: 362, column: 15, scope: !3731)
!3736 = !DILocation(line: 363, column: 15, scope: !3731)
!3737 = !DILocation(line: 363, column: 20, scope: !3731)
!3738 = !DILocation(line: 363, column: 24, scope: !3731)
!3739 = !DILocation(line: 363, column: 32, scope: !3731)
!3740 = !DILocation(line: 363, column: 35, scope: !3731)
!3741 = !DILocation(line: 363, column: 41, scope: !3731)
!3742 = !DILocation(line: 362, column: 9, scope: !3731)
!3743 = !DILocation(line: 364, column: 28, scope: !3731)
!3744 = !DILocation(line: 364, column: 34, scope: !3731)
!3745 = !DILocation(line: 364, column: 9, scope: !3731)
!3746 = !DILocation(line: 365, column: 14, scope: !3731)
!3747 = !DILocation(line: 366, column: 7, scope: !3731)
!3748 = !DILocation(line: 372, column: 14, scope: !3749)
!3749 = distinct !DILexicalBlock(scope: !3728, file: !1, line: 367, column: 12)
!3750 = !DILocation(line: 374, column: 5, scope: !3701)
!3751 = !DILocation(line: 376, column: 8, scope: !3752)
!3752 = distinct !DILexicalBlock(scope: !3606, file: !1, line: 376, column: 8)
!3753 = !DILocation(line: 376, column: 13, scope: !3752)
!3754 = !DILocation(line: 376, column: 8, scope: !3606)
!3755 = !DILocation(line: 402, column: 11, scope: !3756)
!3756 = distinct !DILexicalBlock(scope: !3757, file: !1, line: 402, column: 10)
!3757 = distinct !DILexicalBlock(scope: !3752, file: !1, line: 376, column: 18)
!3758 = !DILocation(line: 402, column: 14, scope: !3756)
!3759 = !DILocation(line: 402, column: 26, scope: !3756)
!3760 = !DILocation(line: 403, column: 11, scope: !3756)
!3761 = !DILocation(line: 403, column: 59, scope: !3756)
!3762 = !DILocation(line: 402, column: 10, scope: !3763)
!3763 = !DILexicalBlockFile(scope: !3757, file: !1, discriminator: 1)
!3764 = !DILocation(line: 404, column: 9, scope: !3765)
!3765 = distinct !DILexicalBlock(scope: !3756, file: !1, line: 403, column: 65)
!3766 = !DILocation(line: 404, column: 14, scope: !3765)
!3767 = !DILocation(line: 404, column: 25, scope: !3765)
!3768 = !DILocation(line: 405, column: 31, scope: !3765)
!3769 = !DILocation(line: 405, column: 25, scope: !3765)
!3770 = !DILocation(line: 405, column: 9, scope: !3765)
!3771 = !DILocation(line: 405, column: 14, scope: !3765)
!3772 = !DILocation(line: 405, column: 23, scope: !3765)
!3773 = !DILocation(line: 406, column: 19, scope: !3765)
!3774 = !DILocation(line: 407, column: 7, scope: !3765)
!3775 = !DILocation(line: 408, column: 5, scope: !3757)
!3776 = !DILocation(line: 410, column: 8, scope: !3777)
!3777 = distinct !DILexicalBlock(scope: !3606, file: !1, line: 410, column: 8)
!3778 = !DILocation(line: 410, column: 13, scope: !3777)
!3779 = !DILocation(line: 410, column: 8, scope: !3606)
!3780 = !DILocation(line: 411, column: 13, scope: !3781)
!3781 = distinct !DILexicalBlock(scope: !3777, file: !1, line: 410, column: 18)
!3782 = !DILocation(line: 411, column: 44, scope: !3781)
!3783 = !DILocation(line: 411, column: 7, scope: !3781)
!3784 = !DILocation(line: 412, column: 7, scope: !3781)
!3785 = !DILocation(line: 414, column: 3, scope: !3606)
!3786 = !DILocation(line: 425, column: 8, scope: !3787)
!3787 = distinct !DILexicalBlock(scope: !3788, file: !1, line: 425, column: 8)
!3788 = distinct !DILexicalBlock(scope: !3598, file: !1, line: 415, column: 8)
!3789 = !DILocation(line: 425, column: 11, scope: !3787)
!3790 = !DILocation(line: 425, column: 8, scope: !3788)
!3791 = !DILocation(line: 426, column: 7, scope: !3792)
!3792 = distinct !DILexicalBlock(scope: !3787, file: !1, line: 425, column: 23)
!3793 = !DILocation(line: 426, column: 12, scope: !3792)
!3794 = !DILocation(line: 426, column: 23, scope: !3792)
!3795 = !DILocation(line: 427, column: 29, scope: !3792)
!3796 = !DILocation(line: 427, column: 23, scope: !3792)
!3797 = !DILocation(line: 427, column: 7, scope: !3792)
!3798 = !DILocation(line: 427, column: 12, scope: !3792)
!3799 = !DILocation(line: 427, column: 21, scope: !3792)
!3800 = !DILocation(line: 428, column: 17, scope: !3792)
!3801 = !DILocation(line: 429, column: 5, scope: !3792)
!3802 = !DILocation(line: 432, column: 3, scope: !1931)
!3803 = !DILocation(line: 433, column: 13, scope: !3804)
!3804 = distinct !DILexicalBlock(scope: !3805, file: !1, line: 433, column: 8)
!3805 = distinct !DILexicalBlock(scope: !3806, file: !1, line: 432, column: 11)
!3806 = distinct !DILexicalBlock(scope: !3807, file: !1, line: 432, column: 3)
!3807 = distinct !DILexicalBlock(scope: !1931, file: !1, line: 432, column: 3)
!3808 = !DILocation(line: 433, column: 21, scope: !3804)
!3809 = !DILocation(line: 433, column: 27, scope: !3804)
!3810 = !DILocation(line: 433, column: 8, scope: !3804)
!3811 = !DILocation(line: 433, column: 38, scope: !3804)
!3812 = !DILocation(line: 433, column: 8, scope: !3805)
!3813 = !DILocalVariable(name: "add", scope: !3814, file: !1, line: 435, type: !1892)
!3814 = distinct !DILexicalBlock(scope: !3804, file: !1, line: 433, column: 44)
!3815 = !DILocation(line: 435, column: 36, scope: !3814)
!3816 = !DILocalVariable(name: "size", scope: !3814, file: !1, line: 436, type: !1287)
!3817 = !DILocation(line: 436, column: 22, scope: !3814)
!3818 = !DILocation(line: 437, column: 7, scope: !3814)
!3819 = !DILocation(line: 438, column: 22, scope: !3820)
!3820 = distinct !DILexicalBlock(scope: !3814, file: !1, line: 438, column: 10)
!3821 = !DILocation(line: 438, column: 30, scope: !3820)
!3822 = !DILocation(line: 438, column: 10, scope: !3820)
!3823 = !DILocation(line: 438, column: 63, scope: !3820)
!3824 = !DILocation(line: 438, column: 10, scope: !3814)
!3825 = !DILocation(line: 439, column: 40, scope: !3826)
!3826 = distinct !DILexicalBlock(scope: !3820, file: !1, line: 438, column: 68)
!3827 = !DILocation(line: 439, column: 38, scope: !3826)
!3828 = !DILocation(line: 439, column: 9, scope: !3826)
!3829 = !DILocation(line: 439, column: 15, scope: !3826)
!3830 = !DILocation(line: 439, column: 21, scope: !3826)
!3831 = !DILocation(line: 439, column: 30, scope: !3826)
!3832 = !DILocation(line: 440, column: 15, scope: !3826)
!3833 = !DILocation(line: 441, column: 15, scope: !3826)
!3834 = !DILocation(line: 441, column: 36, scope: !3826)
!3835 = !DILocation(line: 441, column: 42, scope: !3826)
!3836 = !DILocation(line: 441, column: 22, scope: !3826)
!3837 = !DILocation(line: 440, column: 9, scope: !3826)
!3838 = !DILocation(line: 442, column: 9, scope: !3826)
!3839 = !DILocation(line: 444, column: 13, scope: !3814)
!3840 = !DILocation(line: 444, column: 40, scope: !3814)
!3841 = !DILocation(line: 444, column: 7, scope: !3814)
!3842 = !DILocation(line: 445, column: 7, scope: !3814)
!3843 = !DILocation(line: 445, column: 13, scope: !3814)
!3844 = !DILocation(line: 445, column: 18, scope: !3814)
!3845 = !DILocation(line: 445, column: 24, scope: !3814)
!3846 = !DILocation(line: 446, column: 7, scope: !3814)
!3847 = !DILocation(line: 449, column: 8, scope: !3848)
!3848 = distinct !DILexicalBlock(scope: !3805, file: !1, line: 449, column: 8)
!3849 = !DILocation(line: 449, column: 18, scope: !3848)
!3850 = !DILocation(line: 449, column: 8, scope: !3805)
!3851 = !DILocation(line: 450, column: 13, scope: !3852)
!3852 = distinct !DILexicalBlock(scope: !3848, file: !1, line: 449, column: 23)
!3853 = !DILocation(line: 450, column: 67, scope: !3852)
!3854 = !DILocation(line: 450, column: 7, scope: !3852)
!3855 = !DILocation(line: 451, column: 11, scope: !3852)
!3856 = !DILocation(line: 453, column: 10, scope: !3857)
!3857 = distinct !DILexicalBlock(scope: !3852, file: !1, line: 453, column: 10)
!3858 = !DILocation(line: 453, column: 16, scope: !3857)
!3859 = !DILocation(line: 453, column: 26, scope: !3857)
!3860 = !DILocation(line: 453, column: 10, scope: !3852)
!3861 = !DILocation(line: 454, column: 31, scope: !3857)
!3862 = !DILocation(line: 454, column: 25, scope: !3857)
!3863 = !DILocation(line: 454, column: 9, scope: !3857)
!3864 = !DILocation(line: 454, column: 14, scope: !3857)
!3865 = !DILocation(line: 454, column: 23, scope: !3857)
!3866 = !DILocation(line: 459, column: 5, scope: !3852)
!3867 = !DILocation(line: 461, column: 7, scope: !3848)
!3868 = !DILocation(line: 432, column: 3, scope: !3869)
!3869 = !DILexicalBlockFile(scope: !3806, file: !1, discriminator: 1)
!3870 = !DILocation(line: 464, column: 34, scope: !1931)
!3871 = !DILocation(line: 464, column: 32, scope: !1931)
!3872 = !DILocation(line: 464, column: 3, scope: !1931)
!3873 = !DILocation(line: 464, column: 9, scope: !1931)
!3874 = !DILocation(line: 464, column: 15, scope: !1931)
!3875 = !DILocation(line: 464, column: 24, scope: !1931)
!3876 = !DILocation(line: 465, column: 9, scope: !1931)
!3877 = !DILocation(line: 466, column: 9, scope: !1931)
!3878 = !DILocation(line: 466, column: 30, scope: !1931)
!3879 = !DILocation(line: 466, column: 36, scope: !1931)
!3880 = !DILocation(line: 466, column: 16, scope: !1931)
!3881 = !DILocation(line: 465, column: 3, scope: !1931)
!3882 = !DILocation(line: 468, column: 3, scope: !1931)
!3883 = !DILocation(line: 469, column: 1, scope: !1931)
