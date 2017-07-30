; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/file.c'
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
%struct.Curl_handler = type { i8*, {}*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32, i1)*, i32 (%struct.connectdata*, i32*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i1)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i64, i32, i32 }
%struct.dynamically_allocated_data = type { i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8* }
%struct.curl_llist = type { %struct.curl_llist_element*, %struct.curl_llist_element*, void (i8*, i8*)*, i64 }
%struct.curl_llist_element = type { i8*, %struct.curl_llist_element*, %struct.curl_llist_element* }
%union.anon.0 = type { %struct.ftp_conn }
%struct.ftp_conn = type { %struct.pingpong, i8*, i8**, i32, i32, i8*, i8, i8, i8, i8, i8, i8*, i8, i32, i32, i32, i32, i32, i64, i8*, i64, i8*, i16 }
%struct.pingpong = type { i8*, i64, i64, i8*, i8, i8*, i64, i64, %struct.timeval, i64, %struct.connectdata*, {}*, i1 (%struct.connectdata*, i8*, i64, i32*)* }
%struct.connectbundle = type { i32, i64, %struct.curl_llist }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%struct.FILEPROTO = type { i8*, i8*, i32 }
%struct.tm = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i64, i8* }

@.str = private unnamed_addr constant [5 x i8] c"FILE\00", align 1
@Curl_handler_file = constant { i8*, i32 (%struct.connectdata*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32, i1)*, i32 (%struct.connectdata*, i32*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i1)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i64, i32, i32 } { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0), i32 (%struct.connectdata*)* @file_setup_connection, i32 (%struct.connectdata*, i8*)* @file_do, i32 (%struct.connectdata*, i32, i1)* @file_done, i32 (%struct.connectdata*, i32*)* null, i32 (%struct.connectdata*, i8*)* @file_connect, i32 (%struct.connectdata*, i8*)* null, i32 (%struct.connectdata*, i8*)* null, i32 (%struct.connectdata*, i32*, i32)* null, i32 (%struct.connectdata*, i32*, i32)* null, i32 (%struct.connectdata*, i32*, i32)* null, i32 (%struct.connectdata*, i32*, i32)* null, i32 (%struct.connectdata*, i1)* @file_disconnect, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)* null, i64 0, i32 1024, i32 80 }, align 8
@Curl_ccalloc = external global i8* (i64, i64)*, align 8
@Curl_cfree = external global void (i8*)*, align 8
@.str.1 = private unnamed_addr constant [22 x i8] c"Couldn't open file %s\00", align 1
@.str.2 = private unnamed_addr constant [22 x i8] c"Content-Length: %ld\0D\0A\00", align 1
@.str.3 = private unnamed_addr constant [23 x i8] c"Accept-ranges: bytes\0D\0A\00", align 1
@.str.4 = private unnamed_addr constant [52 x i8] c"Last-Modified: %s, %02d %s %4d %02d:%02d:%02d GMT\0D\0A\00", align 1
@Curl_wkday = external constant [7 x i8*], align 16
@Curl_month = external constant [12 x i8*], align 16
@.str.5 = private unnamed_addr constant [28 x i8] c"Can't get the size of file.\00", align 1
@.str.6 = private unnamed_addr constant [34 x i8] c"failed to resume file:// transfer\00", align 1
@.str.7 = private unnamed_addr constant [26 x i8] c"Can't open %s for writing\00", align 1
@.str.8 = private unnamed_addr constant [25 x i8] c"Can't get the size of %s\00", align 1

; Function Attrs: nounwind uwtable
define internal i32 @file_setup_connection(%struct.connectdata* %conn) #0 !dbg !1710 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !1723, metadata !1724), !dbg !1725
  %0 = load i8* (i64, i64)*, i8* (i64, i64)** @Curl_ccalloc, align 8, !dbg !1726
  %call = call i8* %0(i64 1, i64 24), !dbg !1726
  %1 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1727
  %data = getelementptr inbounds %struct.connectdata, %struct.connectdata* %1, i32 0, i32 0, !dbg !1728
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1728
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 12, !dbg !1729
  %protop = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 43, !dbg !1730
  store i8* %call, i8** %protop, align 8, !dbg !1731
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1732
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %3, i32 0, i32 0, !dbg !1734
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !1734
  %req2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 12, !dbg !1735
  %protop3 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req2, i32 0, i32 43, !dbg !1736
  %5 = load i8*, i8** %protop3, align 8, !dbg !1736
  %tobool = icmp ne i8* %5, null, !dbg !1732
  br i1 %tobool, label %if.end, label %if.then, !dbg !1737

if.then:                                          ; preds = %entry
  store i32 27, i32* %retval, align 4, !dbg !1738
  br label %return, !dbg !1738

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1739
  br label %return, !dbg !1739

return:                                           ; preds = %if.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !1740
  ret i32 %6, !dbg !1740
}

; Function Attrs: nounwind uwtable
define internal i32 @file_do(%struct.connectdata* %conn, i8* %done) #0 !dbg !1715 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %done.addr = alloca i8*, align 8
  %result = alloca i32, align 4
  %statbuf = alloca %struct.stat, align 8
  %expected_size = alloca i64, align 8
  %size_known = alloca i8, align 1
  %fstated = alloca i8, align 1
  %nread = alloca i64, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %buf = alloca i8*, align 8
  %bytecount = alloca i64, align 8
  %fd = alloca i32, align 4
  %now = alloca %struct.timeval, align 8
  %file = alloca %struct.FILEPROTO*, align 8
  %filetime30 = alloca i64, align 8
  %buffer31 = alloca %struct.tm, align 8
  %tm = alloca %struct.tm*, align 8
  %bytestoread = alloca i64, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !1741, metadata !1724), !dbg !1742
  store i8* %done, i8** %done.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %done.addr, metadata !1743, metadata !1724), !dbg !1744
  call void @llvm.dbg.declare(metadata i32* %result, metadata !1745, metadata !1724), !dbg !1746
  store i32 0, i32* %result, align 4, !dbg !1746
  call void @llvm.dbg.declare(metadata %struct.stat* %statbuf, metadata !1747, metadata !1724), !dbg !1780
  call void @llvm.dbg.declare(metadata i64* %expected_size, metadata !1781, metadata !1724), !dbg !1782
  store i64 0, i64* %expected_size, align 8, !dbg !1782
  call void @llvm.dbg.declare(metadata i8* %size_known, metadata !1783, metadata !1724), !dbg !1784
  call void @llvm.dbg.declare(metadata i8* %fstated, metadata !1785, metadata !1724), !dbg !1786
  store i8 0, i8* %fstated, align 1, !dbg !1786
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !1787, metadata !1724), !dbg !1788
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !1789, metadata !1724), !dbg !1790
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1791
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !1792
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !1792
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !1790
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !1793, metadata !1724), !dbg !1794
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1795
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 17, !dbg !1796
  %buffer = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 6, !dbg !1797
  %3 = load i8*, i8** %buffer, align 8, !dbg !1797
  store i8* %3, i8** %buf, align 8, !dbg !1794
  call void @llvm.dbg.declare(metadata i64* %bytecount, metadata !1798, metadata !1724), !dbg !1799
  store i64 0, i64* %bytecount, align 8, !dbg !1799
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1800, metadata !1724), !dbg !1801
  call void @llvm.dbg.declare(metadata %struct.timeval* %now, metadata !1802, metadata !1724), !dbg !1803
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !1804
  %4 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !1804
  %5 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %4, i32 0, i32 0, !dbg !1804
  %6 = extractvalue { i64, i64 } %call, 0, !dbg !1804
  store i64 %6, i64* %5, align 8, !dbg !1804
  %7 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %4, i32 0, i32 1, !dbg !1804
  %8 = extractvalue { i64, i64 } %call, 1, !dbg !1804
  store i64 %8, i64* %7, align 8, !dbg !1804
  call void @llvm.dbg.declare(metadata %struct.FILEPROTO** %file, metadata !1805, metadata !1724), !dbg !1813
  %9 = load i8*, i8** %done.addr, align 8, !dbg !1814
  store i8 1, i8* %9, align 1, !dbg !1815
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1816
  %call2 = call i32 @Curl_initinfo(%struct.Curl_easy* %10), !dbg !1817
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1818
  call void @Curl_pgrsStartNow(%struct.Curl_easy* %11), !dbg !1819
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1820
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 13, !dbg !1822
  %upload = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 104, !dbg !1823
  %13 = load i8, i8* %upload, align 1, !dbg !1823
  %tobool = trunc i8 %13 to i1, !dbg !1823
  br i1 %tobool, label %if.then, label %if.end, !dbg !1824

if.then:                                          ; preds = %entry
  %14 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1825
  %call3 = call i32 @file_upload(%struct.connectdata* %14), !dbg !1826
  store i32 %call3, i32* %retval, align 4, !dbg !1827
  br label %return, !dbg !1827

if.end:                                           ; preds = %entry
  %15 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1828
  %data4 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %15, i32 0, i32 0, !dbg !1829
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data4, align 8, !dbg !1829
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %16, i32 0, i32 12, !dbg !1830
  %protop = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 43, !dbg !1831
  %17 = load i8*, i8** %protop, align 8, !dbg !1831
  %18 = bitcast i8* %17 to %struct.FILEPROTO*, !dbg !1828
  store %struct.FILEPROTO* %18, %struct.FILEPROTO** %file, align 8, !dbg !1832
  %19 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !1833
  %fd5 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %19, i32 0, i32 2, !dbg !1834
  %20 = load i32, i32* %fd5, align 8, !dbg !1834
  store i32 %20, i32* %fd, align 4, !dbg !1835
  %21 = load i32, i32* %fd, align 4, !dbg !1836
  %call6 = call i32 @fstat64(i32 %21, %struct.stat* %statbuf) #6, !dbg !1838
  %cmp = icmp ne i32 -1, %call6, !dbg !1839
  br i1 %cmp, label %if.then7, label %if.end8, !dbg !1840

if.then7:                                         ; preds = %if.end
  %st_size = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 8, !dbg !1841
  %22 = load i64, i64* %st_size, align 8, !dbg !1841
  store i64 %22, i64* %expected_size, align 8, !dbg !1843
  %st_mtim = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 12, !dbg !1844
  %tv_sec = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim, i32 0, i32 0, !dbg !1844
  %23 = load i64, i64* %tv_sec, align 8, !dbg !1844
  %24 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1845
  %info = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %24, i32 0, i32 19, !dbg !1846
  %filetime = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info, i32 0, i32 3, !dbg !1847
  store i64 %23, i64* %filetime, align 8, !dbg !1848
  store i8 1, i8* %fstated, align 1, !dbg !1849
  br label %if.end8, !dbg !1850

if.end8:                                          ; preds = %if.then7, %if.end
  %25 = load i8, i8* %fstated, align 1, !dbg !1851
  %tobool9 = trunc i8 %25 to i1, !dbg !1851
  br i1 %tobool9, label %land.lhs.true, label %if.end21, !dbg !1853

land.lhs.true:                                    ; preds = %if.end8
  %26 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1854
  %state10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %26, i32 0, i32 17, !dbg !1856
  %range = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state10, i32 0, i32 42, !dbg !1857
  %27 = load i8*, i8** %range, align 8, !dbg !1857
  %tobool11 = icmp ne i8* %27, null, !dbg !1854
  br i1 %tobool11, label %if.end21, label %land.lhs.true12, !dbg !1858

land.lhs.true12:                                  ; preds = %land.lhs.true
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1859
  %set13 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %28, i32 0, i32 13, !dbg !1861
  %timecondition = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set13, i32 0, i32 69, !dbg !1862
  %29 = load i32, i32* %timecondition, align 8, !dbg !1862
  %tobool14 = icmp ne i32 %29, 0, !dbg !1859
  br i1 %tobool14, label %if.then15, label %if.end21, !dbg !1863

if.then15:                                        ; preds = %land.lhs.true12
  %30 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1864
  %31 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1867
  %info16 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %31, i32 0, i32 19, !dbg !1868
  %filetime17 = getelementptr inbounds %struct.PureInfo, %struct.PureInfo* %info16, i32 0, i32 3, !dbg !1869
  %32 = load i64, i64* %filetime17, align 8, !dbg !1869
  %call18 = call zeroext i1 @Curl_meets_timecondition(%struct.Curl_easy* %30, i64 %32), !dbg !1870
  br i1 %call18, label %if.end20, label %if.then19, !dbg !1871

if.then19:                                        ; preds = %if.then15
  %33 = load i8*, i8** %done.addr, align 8, !dbg !1872
  store i8 1, i8* %33, align 1, !dbg !1874
  store i32 0, i32* %retval, align 4, !dbg !1875
  br label %return, !dbg !1875

if.end20:                                         ; preds = %if.then15
  br label %if.end21, !dbg !1876

if.end21:                                         ; preds = %if.end20, %land.lhs.true12, %land.lhs.true, %if.end8
  %34 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1877
  %set22 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %34, i32 0, i32 13, !dbg !1879
  %opt_no_body = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set22, i32 0, i32 103, !dbg !1880
  %35 = load i8, i8* %opt_no_body, align 8, !dbg !1880
  %tobool23 = trunc i8 %35 to i1, !dbg !1880
  br i1 %tobool23, label %land.lhs.true24, label %if.end64, !dbg !1881

land.lhs.true24:                                  ; preds = %if.end21
  %36 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1882
  %set25 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %36, i32 0, i32 13, !dbg !1884
  %include_header = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set25, i32 0, i32 100, !dbg !1885
  %37 = load i8, i8* %include_header, align 1, !dbg !1885
  %tobool26 = trunc i8 %37 to i1, !dbg !1885
  br i1 %tobool26, label %land.lhs.true27, label %if.end64, !dbg !1886

land.lhs.true27:                                  ; preds = %land.lhs.true24
  %38 = load i8, i8* %fstated, align 1, !dbg !1887
  %tobool28 = trunc i8 %38 to i1, !dbg !1887
  br i1 %tobool28, label %if.then29, label %if.end64, !dbg !1889

if.then29:                                        ; preds = %land.lhs.true27
  call void @llvm.dbg.declare(metadata i64* %filetime30, metadata !1890, metadata !1724), !dbg !1892
  call void @llvm.dbg.declare(metadata %struct.tm* %buffer31, metadata !1893, metadata !1724), !dbg !1907
  call void @llvm.dbg.declare(metadata %struct.tm** %tm, metadata !1908, metadata !1724), !dbg !1911
  store %struct.tm* %buffer31, %struct.tm** %tm, align 8, !dbg !1911
  %39 = load i8*, i8** %buf, align 8, !dbg !1912
  %40 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1913
  %set32 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %40, i32 0, i32 13, !dbg !1913
  %buffer_size = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set32, i32 0, i32 78, !dbg !1913
  %41 = load i64, i64* %buffer_size, align 8, !dbg !1913
  %tobool33 = icmp ne i64 %41, 0, !dbg !1913
  br i1 %tobool33, label %cond.true, label %cond.false, !dbg !1913

cond.true:                                        ; preds = %if.then29
  %42 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1914
  %set34 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %42, i32 0, i32 13, !dbg !1914
  %buffer_size35 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set34, i32 0, i32 78, !dbg !1914
  %43 = load i64, i64* %buffer_size35, align 8, !dbg !1914
  br label %cond.end, !dbg !1914

cond.false:                                       ; preds = %if.then29
  br label %cond.end, !dbg !1916

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %43, %cond.true ], [ 16384, %cond.false ], !dbg !1918
  %44 = load i64, i64* %expected_size, align 8, !dbg !1920
  %call36 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %39, i64 %cond, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.2, i32 0, i32 0), i64 %44), !dbg !1921
  %45 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1922
  %46 = load i8*, i8** %buf, align 8, !dbg !1923
  %call37 = call i32 @Curl_client_write(%struct.connectdata* %45, i32 3, i8* %46, i64 0), !dbg !1924
  store i32 %call37, i32* %result, align 4, !dbg !1925
  %47 = load i32, i32* %result, align 4, !dbg !1926
  %tobool38 = icmp ne i32 %47, 0, !dbg !1926
  br i1 %tobool38, label %if.then39, label %if.end40, !dbg !1928

if.then39:                                        ; preds = %cond.end
  %48 = load i32, i32* %result, align 4, !dbg !1929
  store i32 %48, i32* %retval, align 4, !dbg !1930
  br label %return, !dbg !1930

if.end40:                                         ; preds = %cond.end
  %49 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1931
  %call41 = call i32 @Curl_client_write(%struct.connectdata* %49, i32 3, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.3, i32 0, i32 0), i64 0), !dbg !1932
  store i32 %call41, i32* %result, align 4, !dbg !1933
  %50 = load i32, i32* %result, align 4, !dbg !1934
  %tobool42 = icmp ne i32 %50, 0, !dbg !1934
  br i1 %tobool42, label %if.then43, label %if.end44, !dbg !1936

if.then43:                                        ; preds = %if.end40
  %51 = load i32, i32* %result, align 4, !dbg !1937
  store i32 %51, i32* %retval, align 4, !dbg !1938
  br label %return, !dbg !1938

if.end44:                                         ; preds = %if.end40
  %st_mtim45 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 12, !dbg !1939
  %tv_sec46 = getelementptr inbounds %struct.timespec, %struct.timespec* %st_mtim45, i32 0, i32 0, !dbg !1939
  %52 = load i64, i64* %tv_sec46, align 8, !dbg !1939
  store i64 %52, i64* %filetime30, align 8, !dbg !1940
  %53 = load i64, i64* %filetime30, align 8, !dbg !1941
  %call47 = call i32 @Curl_gmtime(i64 %53, %struct.tm* %buffer31), !dbg !1942
  store i32 %call47, i32* %result, align 4, !dbg !1943
  %54 = load i32, i32* %result, align 4, !dbg !1944
  %tobool48 = icmp ne i32 %54, 0, !dbg !1944
  br i1 %tobool48, label %if.then49, label %if.end50, !dbg !1946

if.then49:                                        ; preds = %if.end44
  %55 = load i32, i32* %result, align 4, !dbg !1947
  store i32 %55, i32* %retval, align 4, !dbg !1948
  br label %return, !dbg !1948

if.end50:                                         ; preds = %if.end44
  %56 = load i8*, i8** %buf, align 8, !dbg !1949
  %57 = load %struct.tm*, %struct.tm** %tm, align 8, !dbg !1950
  %tm_wday = getelementptr inbounds %struct.tm, %struct.tm* %57, i32 0, i32 6, !dbg !1951
  %58 = load i32, i32* %tm_wday, align 8, !dbg !1951
  %tobool51 = icmp ne i32 %58, 0, !dbg !1950
  br i1 %tobool51, label %cond.true52, label %cond.false54, !dbg !1950

cond.true52:                                      ; preds = %if.end50
  %59 = load %struct.tm*, %struct.tm** %tm, align 8, !dbg !1952
  %tm_wday53 = getelementptr inbounds %struct.tm, %struct.tm* %59, i32 0, i32 6, !dbg !1953
  %60 = load i32, i32* %tm_wday53, align 8, !dbg !1953
  %sub = sub nsw i32 %60, 1, !dbg !1954
  br label %cond.end55, !dbg !1955

cond.false54:                                     ; preds = %if.end50
  br label %cond.end55, !dbg !1956

cond.end55:                                       ; preds = %cond.false54, %cond.true52
  %cond56 = phi i32 [ %sub, %cond.true52 ], [ 6, %cond.false54 ], !dbg !1957
  %idxprom = sext i32 %cond56 to i64, !dbg !1958
  %arrayidx = getelementptr inbounds [7 x i8*], [7 x i8*]* @Curl_wkday, i64 0, i64 %idxprom, !dbg !1958
  %61 = load i8*, i8** %arrayidx, align 8, !dbg !1958
  %62 = load %struct.tm*, %struct.tm** %tm, align 8, !dbg !1959
  %tm_mday = getelementptr inbounds %struct.tm, %struct.tm* %62, i32 0, i32 3, !dbg !1960
  %63 = load i32, i32* %tm_mday, align 4, !dbg !1960
  %64 = load %struct.tm*, %struct.tm** %tm, align 8, !dbg !1961
  %tm_mon = getelementptr inbounds %struct.tm, %struct.tm* %64, i32 0, i32 4, !dbg !1962
  %65 = load i32, i32* %tm_mon, align 8, !dbg !1962
  %idxprom57 = sext i32 %65 to i64, !dbg !1963
  %arrayidx58 = getelementptr inbounds [12 x i8*], [12 x i8*]* @Curl_month, i64 0, i64 %idxprom57, !dbg !1963
  %66 = load i8*, i8** %arrayidx58, align 8, !dbg !1963
  %67 = load %struct.tm*, %struct.tm** %tm, align 8, !dbg !1964
  %tm_year = getelementptr inbounds %struct.tm, %struct.tm* %67, i32 0, i32 5, !dbg !1965
  %68 = load i32, i32* %tm_year, align 4, !dbg !1965
  %add = add nsw i32 %68, 1900, !dbg !1966
  %69 = load %struct.tm*, %struct.tm** %tm, align 8, !dbg !1967
  %tm_hour = getelementptr inbounds %struct.tm, %struct.tm* %69, i32 0, i32 2, !dbg !1968
  %70 = load i32, i32* %tm_hour, align 8, !dbg !1968
  %71 = load %struct.tm*, %struct.tm** %tm, align 8, !dbg !1969
  %tm_min = getelementptr inbounds %struct.tm, %struct.tm* %71, i32 0, i32 1, !dbg !1970
  %72 = load i32, i32* %tm_min, align 4, !dbg !1970
  %73 = load %struct.tm*, %struct.tm** %tm, align 8, !dbg !1971
  %tm_sec = getelementptr inbounds %struct.tm, %struct.tm* %73, i32 0, i32 0, !dbg !1972
  %74 = load i32, i32* %tm_sec, align 8, !dbg !1972
  %call59 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %56, i64 16383, i8* getelementptr inbounds ([52 x i8], [52 x i8]* @.str.4, i32 0, i32 0), i8* %61, i32 %63, i8* %66, i32 %add, i32 %70, i32 %72, i32 %74), !dbg !1973
  %75 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1974
  %76 = load i8*, i8** %buf, align 8, !dbg !1975
  %call60 = call i32 @Curl_client_write(%struct.connectdata* %75, i32 3, i8* %76, i64 0), !dbg !1976
  store i32 %call60, i32* %result, align 4, !dbg !1977
  %77 = load i32, i32* %result, align 4, !dbg !1978
  %tobool61 = icmp ne i32 %77, 0, !dbg !1978
  br i1 %tobool61, label %if.end63, label %if.then62, !dbg !1980

if.then62:                                        ; preds = %cond.end55
  %78 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1981
  %79 = load i64, i64* %expected_size, align 8, !dbg !1982
  call void @Curl_pgrsSetDownloadSize(%struct.Curl_easy* %78, i64 %79), !dbg !1983
  br label %if.end63, !dbg !1983

if.end63:                                         ; preds = %if.then62, %cond.end55
  %80 = load i32, i32* %result, align 4, !dbg !1984
  store i32 %80, i32* %retval, align 4, !dbg !1985
  br label %return, !dbg !1985

if.end64:                                         ; preds = %land.lhs.true27, %land.lhs.true24, %if.end21
  %81 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1986
  %call65 = call i32 @file_range(%struct.connectdata* %81), !dbg !1987
  %82 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1988
  %state66 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %82, i32 0, i32 17, !dbg !1990
  %resume_from = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state66, i32 0, i32 43, !dbg !1991
  %83 = load i64, i64* %resume_from, align 8, !dbg !1991
  %cmp67 = icmp slt i64 %83, 0, !dbg !1992
  br i1 %cmp67, label %if.then68, label %if.end76, !dbg !1993

if.then68:                                        ; preds = %if.end64
  %84 = load i8, i8* %fstated, align 1, !dbg !1994
  %tobool69 = trunc i8 %84 to i1, !dbg !1994
  br i1 %tobool69, label %if.end71, label %if.then70, !dbg !1997

if.then70:                                        ; preds = %if.then68
  %85 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1998
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %85, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.5, i32 0, i32 0)), !dbg !2000
  store i32 26, i32* %retval, align 4, !dbg !2001
  br label %return, !dbg !2001

if.end71:                                         ; preds = %if.then68
  %st_size72 = getelementptr inbounds %struct.stat, %struct.stat* %statbuf, i32 0, i32 8, !dbg !2002
  %86 = load i64, i64* %st_size72, align 8, !dbg !2002
  %87 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2003
  %state73 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %87, i32 0, i32 17, !dbg !2004
  %resume_from74 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state73, i32 0, i32 43, !dbg !2005
  %88 = load i64, i64* %resume_from74, align 8, !dbg !2006
  %add75 = add nsw i64 %88, %86, !dbg !2006
  store i64 %add75, i64* %resume_from74, align 8, !dbg !2006
  br label %if.end76, !dbg !2007

if.end76:                                         ; preds = %if.end71, %if.end64
  %89 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2008
  %state77 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %89, i32 0, i32 17, !dbg !2010
  %resume_from78 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state77, i32 0, i32 43, !dbg !2011
  %90 = load i64, i64* %resume_from78, align 8, !dbg !2011
  %91 = load i64, i64* %expected_size, align 8, !dbg !2012
  %cmp79 = icmp sle i64 %90, %91, !dbg !2013
  br i1 %cmp79, label %if.then80, label %if.else, !dbg !2014

if.then80:                                        ; preds = %if.end76
  %92 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2015
  %state81 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %92, i32 0, i32 17, !dbg !2016
  %resume_from82 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state81, i32 0, i32 43, !dbg !2017
  %93 = load i64, i64* %resume_from82, align 8, !dbg !2017
  %94 = load i64, i64* %expected_size, align 8, !dbg !2018
  %sub83 = sub nsw i64 %94, %93, !dbg !2018
  store i64 %sub83, i64* %expected_size, align 8, !dbg !2018
  br label %if.end84, !dbg !2019

if.else:                                          ; preds = %if.end76
  %95 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2020
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %95, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.6, i32 0, i32 0)), !dbg !2022
  store i32 36, i32* %retval, align 4, !dbg !2023
  br label %return, !dbg !2023

if.end84:                                         ; preds = %if.then80
  %96 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2024
  %req85 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %96, i32 0, i32 12, !dbg !2026
  %maxdownload = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req85, i32 0, i32 2, !dbg !2027
  %97 = load i64, i64* %maxdownload, align 8, !dbg !2027
  %cmp86 = icmp sgt i64 %97, 0, !dbg !2028
  br i1 %cmp86, label %if.then87, label %if.end90, !dbg !2029

if.then87:                                        ; preds = %if.end84
  %98 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2030
  %req88 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %98, i32 0, i32 12, !dbg !2031
  %maxdownload89 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req88, i32 0, i32 2, !dbg !2032
  %99 = load i64, i64* %maxdownload89, align 8, !dbg !2032
  store i64 %99, i64* %expected_size, align 8, !dbg !2033
  br label %if.end90, !dbg !2034

if.end90:                                         ; preds = %if.then87, %if.end84
  %100 = load i8, i8* %fstated, align 1, !dbg !2035
  %tobool91 = trunc i8 %100 to i1, !dbg !2035
  br i1 %tobool91, label %lor.lhs.false, label %if.then93, !dbg !2037

lor.lhs.false:                                    ; preds = %if.end90
  %101 = load i64, i64* %expected_size, align 8, !dbg !2038
  %cmp92 = icmp eq i64 %101, 0, !dbg !2040
  br i1 %cmp92, label %if.then93, label %if.else94, !dbg !2041

if.then93:                                        ; preds = %lor.lhs.false, %if.end90
  store i8 0, i8* %size_known, align 1, !dbg !2042
  br label %if.end95, !dbg !2043

if.else94:                                        ; preds = %lor.lhs.false
  store i8 1, i8* %size_known, align 1, !dbg !2044
  br label %if.end95

if.end95:                                         ; preds = %if.else94, %if.then93
  %102 = load i8, i8* %fstated, align 1, !dbg !2045
  %tobool96 = trunc i8 %102 to i1, !dbg !2045
  br i1 %tobool96, label %if.then97, label %if.end98, !dbg !2047

if.then97:                                        ; preds = %if.end95
  %103 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2048
  %104 = load i64, i64* %expected_size, align 8, !dbg !2049
  call void @Curl_pgrsSetDownloadSize(%struct.Curl_easy* %103, i64 %104), !dbg !2050
  br label %if.end98, !dbg !2050

if.end98:                                         ; preds = %if.then97, %if.end95
  %105 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2051
  %state99 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %105, i32 0, i32 17, !dbg !2053
  %resume_from100 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state99, i32 0, i32 43, !dbg !2054
  %106 = load i64, i64* %resume_from100, align 8, !dbg !2054
  %tobool101 = icmp ne i64 %106, 0, !dbg !2051
  br i1 %tobool101, label %if.then102, label %if.end111, !dbg !2055

if.then102:                                       ; preds = %if.end98
  %107 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2056
  %state103 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %107, i32 0, i32 17, !dbg !2059
  %resume_from104 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state103, i32 0, i32 43, !dbg !2060
  %108 = load i64, i64* %resume_from104, align 8, !dbg !2060
  %109 = load i32, i32* %fd, align 4, !dbg !2061
  %110 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2062
  %state105 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %110, i32 0, i32 17, !dbg !2063
  %resume_from106 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state105, i32 0, i32 43, !dbg !2064
  %111 = load i64, i64* %resume_from106, align 8, !dbg !2064
  %call107 = call i64 @lseek64(i32 %109, i64 %111, i32 0) #6, !dbg !2065
  %cmp108 = icmp ne i64 %108, %call107, !dbg !2066
  br i1 %cmp108, label %if.then109, label %if.end110, !dbg !2067

if.then109:                                       ; preds = %if.then102
  store i32 36, i32* %retval, align 4, !dbg !2068
  br label %return, !dbg !2068

if.end110:                                        ; preds = %if.then102
  br label %if.end111, !dbg !2069

if.end111:                                        ; preds = %if.end110, %if.end98
  %112 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2070
  call void @Curl_pgrsTime(%struct.Curl_easy* %112, i32 7), !dbg !2071
  br label %while.cond, !dbg !2072

while.cond:                                       ; preds = %if.end149, %if.end111
  %113 = load i32, i32* %result, align 4, !dbg !2073
  %tobool112 = icmp ne i32 %113, 0, !dbg !2075
  %lnot = xor i1 %tobool112, true, !dbg !2075
  br i1 %lnot, label %while.body, label %while.end, !dbg !2076

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i64* %bytestoread, metadata !2077, metadata !1724), !dbg !2079
  %114 = load i8, i8* %size_known, align 1, !dbg !2080
  %tobool113 = trunc i8 %114 to i1, !dbg !2080
  br i1 %tobool113, label %if.then114, label %if.else121, !dbg !2082

if.then114:                                       ; preds = %while.body
  %115 = load i64, i64* %expected_size, align 8, !dbg !2083
  %cmp115 = icmp slt i64 %115, 16383, !dbg !2085
  br i1 %cmp115, label %cond.true116, label %cond.false118, !dbg !2086

cond.true116:                                     ; preds = %if.then114
  %116 = load i64, i64* %expected_size, align 8, !dbg !2087
  %call117 = call i64 @curlx_sotouz(i64 %116), !dbg !2088
  br label %cond.end119, !dbg !2089

cond.false118:                                    ; preds = %if.then114
  br label %cond.end119, !dbg !2091

cond.end119:                                      ; preds = %cond.false118, %cond.true116
  %cond120 = phi i64 [ %call117, %cond.true116 ], [ 16383, %cond.false118 ], !dbg !2093
  store i64 %cond120, i64* %bytestoread, align 8, !dbg !2095
  br label %if.end122, !dbg !2096

if.else121:                                       ; preds = %while.body
  store i64 16383, i64* %bytestoread, align 8, !dbg !2097
  br label %if.end122

if.end122:                                        ; preds = %if.else121, %cond.end119
  %117 = load i32, i32* %fd, align 4, !dbg !2098
  %118 = load i8*, i8** %buf, align 8, !dbg !2099
  %119 = load i64, i64* %bytestoread, align 8, !dbg !2100
  %call123 = call i64 @read(i32 %117, i8* %118, i64 %119), !dbg !2101
  store i64 %call123, i64* %nread, align 8, !dbg !2102
  %120 = load i64, i64* %nread, align 8, !dbg !2103
  %cmp124 = icmp sgt i64 %120, 0, !dbg !2105
  br i1 %cmp124, label %if.then125, label %if.end127, !dbg !2106

if.then125:                                       ; preds = %if.end122
  %121 = load i64, i64* %nread, align 8, !dbg !2107
  %122 = load i8*, i8** %buf, align 8, !dbg !2108
  %arrayidx126 = getelementptr inbounds i8, i8* %122, i64 %121, !dbg !2108
  store i8 0, i8* %arrayidx126, align 1, !dbg !2109
  br label %if.end127, !dbg !2108

if.end127:                                        ; preds = %if.then125, %if.end122
  %123 = load i64, i64* %nread, align 8, !dbg !2110
  %cmp128 = icmp sle i64 %123, 0, !dbg !2112
  br i1 %cmp128, label %if.then133, label %lor.lhs.false129, !dbg !2113

lor.lhs.false129:                                 ; preds = %if.end127
  %124 = load i8, i8* %size_known, align 1, !dbg !2114
  %tobool130 = trunc i8 %124 to i1, !dbg !2114
  br i1 %tobool130, label %land.lhs.true131, label %if.end134, !dbg !2116

land.lhs.true131:                                 ; preds = %lor.lhs.false129
  %125 = load i64, i64* %expected_size, align 8, !dbg !2117
  %cmp132 = icmp eq i64 %125, 0, !dbg !2119
  br i1 %cmp132, label %if.then133, label %if.end134, !dbg !2120

if.then133:                                       ; preds = %land.lhs.true131, %if.end127
  br label %while.end, !dbg !2121

if.end134:                                        ; preds = %land.lhs.true131, %lor.lhs.false129
  %126 = load i64, i64* %nread, align 8, !dbg !2122
  %127 = load i64, i64* %bytecount, align 8, !dbg !2123
  %add135 = add nsw i64 %127, %126, !dbg !2123
  store i64 %add135, i64* %bytecount, align 8, !dbg !2123
  %128 = load i8, i8* %size_known, align 1, !dbg !2124
  %tobool136 = trunc i8 %128 to i1, !dbg !2124
  br i1 %tobool136, label %if.then137, label %if.end139, !dbg !2126

if.then137:                                       ; preds = %if.end134
  %129 = load i64, i64* %nread, align 8, !dbg !2127
  %130 = load i64, i64* %expected_size, align 8, !dbg !2128
  %sub138 = sub nsw i64 %130, %129, !dbg !2128
  store i64 %sub138, i64* %expected_size, align 8, !dbg !2128
  br label %if.end139, !dbg !2129

if.end139:                                        ; preds = %if.then137, %if.end134
  %131 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2130
  %132 = load i8*, i8** %buf, align 8, !dbg !2131
  %133 = load i64, i64* %nread, align 8, !dbg !2132
  %call140 = call i32 @Curl_client_write(%struct.connectdata* %131, i32 1, i8* %132, i64 %133), !dbg !2133
  store i32 %call140, i32* %result, align 4, !dbg !2134
  %134 = load i32, i32* %result, align 4, !dbg !2135
  %tobool141 = icmp ne i32 %134, 0, !dbg !2135
  br i1 %tobool141, label %if.then142, label %if.end143, !dbg !2137

if.then142:                                       ; preds = %if.end139
  %135 = load i32, i32* %result, align 4, !dbg !2138
  store i32 %135, i32* %retval, align 4, !dbg !2139
  br label %return, !dbg !2139

if.end143:                                        ; preds = %if.end139
  %136 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2140
  %137 = load i64, i64* %bytecount, align 8, !dbg !2141
  call void @Curl_pgrsSetDownloadCounter(%struct.Curl_easy* %136, i64 %137), !dbg !2142
  %138 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2143
  %call144 = call i32 @Curl_pgrsUpdate(%struct.connectdata* %138), !dbg !2145
  %tobool145 = icmp ne i32 %call144, 0, !dbg !2145
  br i1 %tobool145, label %if.then146, label %if.else147, !dbg !2146

if.then146:                                       ; preds = %if.end143
  store i32 42, i32* %result, align 4, !dbg !2147
  br label %if.end149, !dbg !2148

if.else147:                                       ; preds = %if.end143
  %139 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2149
  %140 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2150
  %141 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %140, i32 0, i32 0, !dbg !2150
  %142 = load i64, i64* %141, align 8, !dbg !2150
  %143 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %140, i32 0, i32 1, !dbg !2150
  %144 = load i64, i64* %143, align 8, !dbg !2150
  %call148 = call i32 @Curl_speedcheck(%struct.Curl_easy* %139, i64 %142, i64 %144), !dbg !2150
  store i32 %call148, i32* %result, align 4, !dbg !2151
  br label %if.end149

if.end149:                                        ; preds = %if.else147, %if.then146
  br label %while.cond, !dbg !2152

while.end:                                        ; preds = %if.then133, %while.cond
  %145 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2154
  %call150 = call i32 @Curl_pgrsUpdate(%struct.connectdata* %145), !dbg !2156
  %tobool151 = icmp ne i32 %call150, 0, !dbg !2156
  br i1 %tobool151, label %if.then152, label %if.end153, !dbg !2157

if.then152:                                       ; preds = %while.end
  store i32 42, i32* %result, align 4, !dbg !2158
  br label %if.end153, !dbg !2159

if.end153:                                        ; preds = %if.then152, %while.end
  %146 = load i32, i32* %result, align 4, !dbg !2160
  store i32 %146, i32* %retval, align 4, !dbg !2161
  br label %return, !dbg !2161

return:                                           ; preds = %if.end153, %if.then142, %if.then109, %if.else, %if.then70, %if.end63, %if.then49, %if.then43, %if.then39, %if.then19, %if.then
  %147 = load i32, i32* %retval, align 4, !dbg !2162
  ret i32 %147, !dbg !2162
}

; Function Attrs: nounwind uwtable
define internal i32 @file_done(%struct.connectdata* %conn, i32 %status, i1 zeroext %premature) #0 !dbg !1713 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %status.addr = alloca i32, align 4
  %premature.addr = alloca i8, align 1
  %file = alloca %struct.FILEPROTO*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2163, metadata !1724), !dbg !2164
  store i32 %status, i32* %status.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %status.addr, metadata !2165, metadata !1724), !dbg !2166
  %frombool = zext i1 %premature to i8
  store i8 %frombool, i8* %premature.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %premature.addr, metadata !2167, metadata !1724), !dbg !2168
  call void @llvm.dbg.declare(metadata %struct.FILEPROTO** %file, metadata !2169, metadata !1724), !dbg !2170
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2171
  %data = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2172
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2172
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 12, !dbg !2173
  %protop = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 43, !dbg !2174
  %2 = load i8*, i8** %protop, align 8, !dbg !2174
  %3 = bitcast i8* %2 to %struct.FILEPROTO*, !dbg !2171
  store %struct.FILEPROTO* %3, %struct.FILEPROTO** %file, align 8, !dbg !2170
  %4 = load i32, i32* %status.addr, align 4, !dbg !2175
  %5 = load i8, i8* %premature.addr, align 1, !dbg !2176
  %tobool = trunc i8 %5 to i1, !dbg !2176
  %6 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2177
  %tobool1 = icmp ne %struct.FILEPROTO* %6, null, !dbg !2177
  br i1 %tobool1, label %if.then, label %if.end6, !dbg !2179

if.then:                                          ; preds = %entry
  br label %do.body, !dbg !2180

do.body:                                          ; preds = %if.then
  %7 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2182
  %8 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2182
  %freepath = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %8, i32 0, i32 1, !dbg !2182
  %9 = load i8*, i8** %freepath, align 8, !dbg !2182
  call void %7(i8* %9), !dbg !2182
  %10 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2182
  %freepath2 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %10, i32 0, i32 1, !dbg !2182
  store i8* null, i8** %freepath2, align 8, !dbg !2182
  br label %do.end, !dbg !2182

do.end:                                           ; preds = %do.body
  %11 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2185
  %path = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %11, i32 0, i32 0, !dbg !2186
  store i8* null, i8** %path, align 8, !dbg !2187
  %12 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2188
  %fd = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %12, i32 0, i32 2, !dbg !2190
  %13 = load i32, i32* %fd, align 8, !dbg !2190
  %cmp = icmp ne i32 %13, -1, !dbg !2191
  br i1 %cmp, label %if.then3, label %if.end, !dbg !2192

if.then3:                                         ; preds = %do.end
  %14 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2193
  %fd4 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %14, i32 0, i32 2, !dbg !2194
  %15 = load i32, i32* %fd4, align 8, !dbg !2194
  %call = call i32 @close(i32 %15), !dbg !2195
  br label %if.end, !dbg !2195

if.end:                                           ; preds = %if.then3, %do.end
  %16 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2196
  %fd5 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %16, i32 0, i32 2, !dbg !2197
  store i32 -1, i32* %fd5, align 8, !dbg !2198
  br label %if.end6, !dbg !2199

if.end6:                                          ; preds = %if.end, %entry
  ret i32 0, !dbg !2200
}

; Function Attrs: nounwind uwtable
define internal i32 @file_connect(%struct.connectdata* %conn, i8* %done) #0 !dbg !1712 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %done.addr = alloca i8*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %real_path = alloca i8*, align 8
  %file = alloca %struct.FILEPROTO*, align 8
  %fd = alloca i32, align 4
  %real_path_len = alloca i64, align 8
  %result = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2201, metadata !1724), !dbg !2202
  store i8* %done, i8** %done.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %done.addr, metadata !2203, metadata !1724), !dbg !2204
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2205, metadata !1724), !dbg !2206
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2207
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2208
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2208
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2206
  call void @llvm.dbg.declare(metadata i8** %real_path, metadata !2209, metadata !1724), !dbg !2210
  call void @llvm.dbg.declare(metadata %struct.FILEPROTO** %file, metadata !2211, metadata !1724), !dbg !2212
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2213
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 12, !dbg !2214
  %protop = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 43, !dbg !2215
  %3 = load i8*, i8** %protop, align 8, !dbg !2215
  %4 = bitcast i8* %3 to %struct.FILEPROTO*, !dbg !2213
  store %struct.FILEPROTO* %4, %struct.FILEPROTO** %file, align 8, !dbg !2212
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !2216, metadata !1724), !dbg !2217
  call void @llvm.dbg.declare(metadata i64* %real_path_len, metadata !2218, metadata !1724), !dbg !2219
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2220, metadata !1724), !dbg !2221
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2222
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2223
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 17, !dbg !2224
  %path = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 38, !dbg !2225
  %7 = load i8*, i8** %path, align 8, !dbg !2225
  %call = call i32 @Curl_urldecode(%struct.Curl_easy* %5, i8* %7, i64 0, i8** %real_path, i64* %real_path_len, i1 zeroext false), !dbg !2226
  store i32 %call, i32* %result, align 4, !dbg !2221
  %8 = load i32, i32* %result, align 4, !dbg !2227
  %tobool = icmp ne i32 %8, 0, !dbg !2227
  br i1 %tobool, label %if.then, label %if.end, !dbg !2229

if.then:                                          ; preds = %entry
  %9 = load i32, i32* %result, align 4, !dbg !2230
  store i32 %9, i32* %retval, align 4, !dbg !2231
  br label %return, !dbg !2231

if.end:                                           ; preds = %entry
  %10 = load i8*, i8** %real_path, align 8, !dbg !2232
  %11 = load i64, i64* %real_path_len, align 8, !dbg !2234
  %call2 = call i8* @memchr(i8* %10, i32 0, i64 %11) #7, !dbg !2235
  %tobool3 = icmp ne i8* %call2, null, !dbg !2235
  br i1 %tobool3, label %if.then4, label %if.end5, !dbg !2236

if.then4:                                         ; preds = %if.end
  br label %do.body, !dbg !2237

do.body:                                          ; preds = %if.then4
  %12 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2239
  %13 = load i8*, i8** %real_path, align 8, !dbg !2239
  call void %12(i8* %13), !dbg !2239
  store i8* null, i8** %real_path, align 8, !dbg !2239
  br label %do.end, !dbg !2239

do.end:                                           ; preds = %do.body
  store i32 3, i32* %retval, align 4, !dbg !2242
  br label %return, !dbg !2242

if.end5:                                          ; preds = %if.end
  %14 = load i8*, i8** %real_path, align 8, !dbg !2243
  %call6 = call i32 (i8*, i32, ...) @open64(i8* %14, i32 0), !dbg !2243
  store i32 %call6, i32* %fd, align 4, !dbg !2244
  %15 = load i8*, i8** %real_path, align 8, !dbg !2245
  %16 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2246
  %path7 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %16, i32 0, i32 0, !dbg !2247
  store i8* %15, i8** %path7, align 8, !dbg !2248
  %17 = load i8*, i8** %real_path, align 8, !dbg !2249
  %18 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2250
  %freepath = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %18, i32 0, i32 1, !dbg !2251
  store i8* %17, i8** %freepath, align 8, !dbg !2252
  %19 = load i32, i32* %fd, align 4, !dbg !2253
  %20 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2254
  %fd8 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %20, i32 0, i32 2, !dbg !2255
  store i32 %19, i32* %fd8, align 8, !dbg !2256
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2257
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %21, i32 0, i32 13, !dbg !2259
  %upload = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 104, !dbg !2260
  %22 = load i8, i8* %upload, align 1, !dbg !2260
  %tobool9 = trunc i8 %22 to i1, !dbg !2260
  br i1 %tobool9, label %if.end14, label %land.lhs.true, !dbg !2261

land.lhs.true:                                    ; preds = %if.end5
  %23 = load i32, i32* %fd, align 4, !dbg !2262
  %cmp = icmp eq i32 %23, -1, !dbg !2264
  br i1 %cmp, label %if.then10, label %if.end14, !dbg !2265

if.then10:                                        ; preds = %land.lhs.true
  %24 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2266
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2268
  %state11 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 17, !dbg !2269
  %path12 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state11, i32 0, i32 38, !dbg !2270
  %26 = load i8*, i8** %path12, align 8, !dbg !2270
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %24, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.1, i32 0, i32 0), i8* %26), !dbg !2271
  %27 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2272
  %call13 = call i32 @file_done(%struct.connectdata* %27, i32 37, i1 zeroext false), !dbg !2273
  store i32 37, i32* %retval, align 4, !dbg !2274
  br label %return, !dbg !2274

if.end14:                                         ; preds = %land.lhs.true, %if.end5
  %28 = load i8*, i8** %done.addr, align 8, !dbg !2275
  store i8 1, i8* %28, align 1, !dbg !2276
  store i32 0, i32* %retval, align 4, !dbg !2277
  br label %return, !dbg !2277

return:                                           ; preds = %if.end14, %if.then10, %do.end, %if.then
  %29 = load i32, i32* %retval, align 4, !dbg !2278
  ret i32 %29, !dbg !2278
}

; Function Attrs: nounwind uwtable
define internal i32 @file_disconnect(%struct.connectdata* %conn, i1 zeroext %dead_connection) #0 !dbg !1714 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %dead_connection.addr = alloca i8, align 1
  %file = alloca %struct.FILEPROTO*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2279, metadata !1724), !dbg !2280
  %frombool = zext i1 %dead_connection to i8
  store i8 %frombool, i8* %dead_connection.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %dead_connection.addr, metadata !2281, metadata !1724), !dbg !2282
  call void @llvm.dbg.declare(metadata %struct.FILEPROTO** %file, metadata !2283, metadata !1724), !dbg !2284
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2285
  %data = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2286
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2286
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 12, !dbg !2287
  %protop = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 43, !dbg !2288
  %2 = load i8*, i8** %protop, align 8, !dbg !2288
  %3 = bitcast i8* %2 to %struct.FILEPROTO*, !dbg !2285
  store %struct.FILEPROTO* %3, %struct.FILEPROTO** %file, align 8, !dbg !2284
  %4 = load i8, i8* %dead_connection.addr, align 1, !dbg !2289
  %tobool = trunc i8 %4 to i1, !dbg !2289
  %5 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2290
  %tobool1 = icmp ne %struct.FILEPROTO* %5, null, !dbg !2290
  br i1 %tobool1, label %if.then, label %if.end6, !dbg !2292

if.then:                                          ; preds = %entry
  br label %do.body, !dbg !2293

do.body:                                          ; preds = %if.then
  %6 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2295
  %7 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2295
  %freepath = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %7, i32 0, i32 1, !dbg !2295
  %8 = load i8*, i8** %freepath, align 8, !dbg !2295
  call void %6(i8* %8), !dbg !2295
  %9 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2295
  %freepath2 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %9, i32 0, i32 1, !dbg !2295
  store i8* null, i8** %freepath2, align 8, !dbg !2295
  br label %do.end, !dbg !2295

do.end:                                           ; preds = %do.body
  %10 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2298
  %path = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %10, i32 0, i32 0, !dbg !2299
  store i8* null, i8** %path, align 8, !dbg !2300
  %11 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2301
  %fd = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %11, i32 0, i32 2, !dbg !2303
  %12 = load i32, i32* %fd, align 8, !dbg !2303
  %cmp = icmp ne i32 %12, -1, !dbg !2304
  br i1 %cmp, label %if.then3, label %if.end, !dbg !2305

if.then3:                                         ; preds = %do.end
  %13 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2306
  %fd4 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %13, i32 0, i32 2, !dbg !2307
  %14 = load i32, i32* %fd4, align 8, !dbg !2307
  %call = call i32 @close(i32 %14), !dbg !2308
  br label %if.end, !dbg !2308

if.end:                                           ; preds = %if.then3, %do.end
  %15 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2309
  %fd5 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %15, i32 0, i32 2, !dbg !2310
  store i32 -1, i32* %fd5, align 8, !dbg !2311
  br label %if.end6, !dbg !2312

if.end6:                                          ; preds = %if.end, %entry
  ret i32 0, !dbg !2313
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @Curl_urldecode(%struct.Curl_easy*, i8*, i64, i8**, i64*, i1 zeroext) #2

; Function Attrs: nounwind readonly
declare i8* @memchr(i8*, i32, i64) #3

declare i32 @open64(i8*, i32, ...) #2

declare void @Curl_failf(%struct.Curl_easy*, i8*, ...) #2

declare i32 @close(i32) #2

declare { i64, i64 } @curlx_tvnow() #2

declare i32 @Curl_initinfo(%struct.Curl_easy*) #2

declare void @Curl_pgrsStartNow(%struct.Curl_easy*) #2

; Function Attrs: nounwind uwtable
define internal i32 @file_upload(%struct.connectdata* %conn) #0 !dbg !1716 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %file = alloca %struct.FILEPROTO*, align 8
  %dir = alloca i8*, align 8
  %fd = alloca i32, align 4
  %mode = alloca i32, align 4
  %result = alloca i32, align 4
  %data1 = alloca %struct.Curl_easy*, align 8
  %buf = alloca i8*, align 8
  %nread = alloca i64, align 8
  %nwrite = alloca i64, align 8
  %bytecount = alloca i64, align 8
  %now = alloca %struct.timeval, align 8
  %file_stat = alloca %struct.stat, align 8
  %buf2 = alloca i8*, align 8
  %readcount = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2314, metadata !1724), !dbg !2315
  call void @llvm.dbg.declare(metadata %struct.FILEPROTO** %file, metadata !2316, metadata !1724), !dbg !2317
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2318
  %data = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2319
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2319
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 12, !dbg !2320
  %protop = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 43, !dbg !2321
  %2 = load i8*, i8** %protop, align 8, !dbg !2321
  %3 = bitcast i8* %2 to %struct.FILEPROTO*, !dbg !2318
  store %struct.FILEPROTO* %3, %struct.FILEPROTO** %file, align 8, !dbg !2317
  call void @llvm.dbg.declare(metadata i8** %dir, metadata !2322, metadata !1724), !dbg !2323
  %4 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2324
  %path = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %4, i32 0, i32 0, !dbg !2325
  %5 = load i8*, i8** %path, align 8, !dbg !2325
  %call = call i8* @strchr(i8* %5, i32 47) #7, !dbg !2326
  store i8* %call, i8** %dir, align 8, !dbg !2323
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !2327, metadata !1724), !dbg !2328
  call void @llvm.dbg.declare(metadata i32* %mode, metadata !2329, metadata !1724), !dbg !2330
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2331, metadata !1724), !dbg !2332
  store i32 0, i32* %result, align 4, !dbg !2332
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data1, metadata !2333, metadata !1724), !dbg !2334
  %6 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2335
  %data2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %6, i32 0, i32 0, !dbg !2336
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data2, align 8, !dbg !2336
  store %struct.Curl_easy* %7, %struct.Curl_easy** %data1, align 8, !dbg !2334
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !2337, metadata !1724), !dbg !2338
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2339
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %8, i32 0, i32 17, !dbg !2340
  %buffer = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 6, !dbg !2341
  %9 = load i8*, i8** %buffer, align 8, !dbg !2341
  store i8* %9, i8** %buf, align 8, !dbg !2338
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !2342, metadata !1724), !dbg !2343
  call void @llvm.dbg.declare(metadata i64* %nwrite, metadata !2344, metadata !1724), !dbg !2345
  call void @llvm.dbg.declare(metadata i64* %bytecount, metadata !2346, metadata !1724), !dbg !2347
  store i64 0, i64* %bytecount, align 8, !dbg !2347
  call void @llvm.dbg.declare(metadata %struct.timeval* %now, metadata !2348, metadata !1724), !dbg !2349
  %call3 = call { i64, i64 } @curlx_tvnow(), !dbg !2350
  %10 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2350
  %11 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %10, i32 0, i32 0, !dbg !2350
  %12 = extractvalue { i64, i64 } %call3, 0, !dbg !2350
  store i64 %12, i64* %11, align 8, !dbg !2350
  %13 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %10, i32 0, i32 1, !dbg !2350
  %14 = extractvalue { i64, i64 } %call3, 1, !dbg !2350
  store i64 %14, i64* %13, align 8, !dbg !2350
  call void @llvm.dbg.declare(metadata %struct.stat* %file_stat, metadata !2351, metadata !1724), !dbg !2352
  call void @llvm.dbg.declare(metadata i8** %buf2, metadata !2353, metadata !1724), !dbg !2354
  %15 = load i8*, i8** %buf, align 8, !dbg !2355
  %16 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2356
  %data4 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %16, i32 0, i32 0, !dbg !2357
  %17 = load %struct.Curl_easy*, %struct.Curl_easy** %data4, align 8, !dbg !2357
  %req5 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %17, i32 0, i32 12, !dbg !2358
  %upload_fromhere = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req5, i32 0, i32 38, !dbg !2359
  store i8* %15, i8** %upload_fromhere, align 8, !dbg !2360
  %18 = load i8*, i8** %dir, align 8, !dbg !2361
  %tobool = icmp ne i8* %18, null, !dbg !2361
  br i1 %tobool, label %if.end, label %if.then, !dbg !2363

if.then:                                          ; preds = %entry
  store i32 37, i32* %retval, align 4, !dbg !2364
  br label %return, !dbg !2364

if.end:                                           ; preds = %entry
  %19 = load i8*, i8** %dir, align 8, !dbg !2365
  %arrayidx = getelementptr inbounds i8, i8* %19, i64 1, !dbg !2365
  %20 = load i8, i8* %arrayidx, align 1, !dbg !2365
  %tobool6 = icmp ne i8 %20, 0, !dbg !2365
  br i1 %tobool6, label %if.end8, label %if.then7, !dbg !2367

if.then7:                                         ; preds = %if.end
  store i32 37, i32* %retval, align 4, !dbg !2368
  br label %return, !dbg !2368

if.end8:                                          ; preds = %if.end
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2369
  %state9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %21, i32 0, i32 17, !dbg !2371
  %resume_from = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state9, i32 0, i32 43, !dbg !2372
  %22 = load i64, i64* %resume_from, align 8, !dbg !2372
  %tobool10 = icmp ne i64 %22, 0, !dbg !2369
  br i1 %tobool10, label %if.then11, label %if.else, !dbg !2373

if.then11:                                        ; preds = %if.end8
  store i32 1089, i32* %mode, align 4, !dbg !2374
  br label %if.end12, !dbg !2375

if.else:                                          ; preds = %if.end8
  store i32 577, i32* %mode, align 4, !dbg !2376
  br label %if.end12

if.end12:                                         ; preds = %if.else, %if.then11
  %23 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2377
  %path13 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %23, i32 0, i32 0, !dbg !2378
  %24 = load i8*, i8** %path13, align 8, !dbg !2378
  %25 = load i32, i32* %mode, align 4, !dbg !2379
  %26 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2380
  %data14 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %26, i32 0, i32 0, !dbg !2381
  %27 = load %struct.Curl_easy*, %struct.Curl_easy** %data14, align 8, !dbg !2381
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %27, i32 0, i32 13, !dbg !2382
  %new_file_perms = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 125, !dbg !2383
  %28 = load i64, i64* %new_file_perms, align 8, !dbg !2383
  %call15 = call i32 (i8*, i32, ...) @open64(i8* %24, i32 %25, i64 %28), !dbg !2384
  store i32 %call15, i32* %fd, align 4, !dbg !2385
  %29 = load i32, i32* %fd, align 4, !dbg !2386
  %cmp = icmp slt i32 %29, 0, !dbg !2388
  br i1 %cmp, label %if.then16, label %if.end18, !dbg !2389

if.then16:                                        ; preds = %if.end12
  %30 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2390
  %31 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2392
  %path17 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %31, i32 0, i32 0, !dbg !2393
  %32 = load i8*, i8** %path17, align 8, !dbg !2393
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %30, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.7, i32 0, i32 0), i8* %32), !dbg !2394
  store i32 23, i32* %retval, align 4, !dbg !2395
  br label %return, !dbg !2395

if.end18:                                         ; preds = %if.end12
  %33 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2396
  %state19 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %33, i32 0, i32 17, !dbg !2398
  %infilesize = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state19, i32 0, i32 47, !dbg !2399
  %34 = load i64, i64* %infilesize, align 8, !dbg !2399
  %cmp20 = icmp ne i64 -1, %34, !dbg !2400
  br i1 %cmp20, label %if.then21, label %if.end24, !dbg !2401

if.then21:                                        ; preds = %if.end18
  %35 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2402
  %36 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2403
  %state22 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %36, i32 0, i32 17, !dbg !2404
  %infilesize23 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state22, i32 0, i32 47, !dbg !2405
  %37 = load i64, i64* %infilesize23, align 8, !dbg !2405
  call void @Curl_pgrsSetUploadSize(%struct.Curl_easy* %35, i64 %37), !dbg !2406
  br label %if.end24, !dbg !2406

if.end24:                                         ; preds = %if.then21, %if.end18
  %38 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2407
  %state25 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %38, i32 0, i32 17, !dbg !2409
  %resume_from26 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state25, i32 0, i32 43, !dbg !2410
  %39 = load i64, i64* %resume_from26, align 8, !dbg !2410
  %cmp27 = icmp slt i64 %39, 0, !dbg !2411
  br i1 %cmp27, label %if.then28, label %if.end37, !dbg !2412

if.then28:                                        ; preds = %if.end24
  %40 = load i32, i32* %fd, align 4, !dbg !2413
  %call29 = call i32 @fstat64(i32 %40, %struct.stat* %file_stat) #6, !dbg !2416
  %tobool30 = icmp ne i32 %call29, 0, !dbg !2416
  br i1 %tobool30, label %if.then31, label %if.end34, !dbg !2417

if.then31:                                        ; preds = %if.then28
  %41 = load i32, i32* %fd, align 4, !dbg !2418
  %call32 = call i32 @close(i32 %41), !dbg !2420
  %42 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2421
  %43 = load %struct.FILEPROTO*, %struct.FILEPROTO** %file, align 8, !dbg !2422
  %path33 = getelementptr inbounds %struct.FILEPROTO, %struct.FILEPROTO* %43, i32 0, i32 0, !dbg !2423
  %44 = load i8*, i8** %path33, align 8, !dbg !2423
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %42, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.8, i32 0, i32 0), i8* %44), !dbg !2424
  store i32 23, i32* %retval, align 4, !dbg !2425
  br label %return, !dbg !2425

if.end34:                                         ; preds = %if.then28
  %st_size = getelementptr inbounds %struct.stat, %struct.stat* %file_stat, i32 0, i32 8, !dbg !2426
  %45 = load i64, i64* %st_size, align 8, !dbg !2426
  %46 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2427
  %state35 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %46, i32 0, i32 17, !dbg !2428
  %resume_from36 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state35, i32 0, i32 43, !dbg !2429
  store i64 %45, i64* %resume_from36, align 8, !dbg !2430
  br label %if.end37, !dbg !2431

if.end37:                                         ; preds = %if.end34, %if.end24
  br label %while.cond, !dbg !2432

while.cond:                                       ; preds = %if.end78, %if.end37
  %47 = load i32, i32* %result, align 4, !dbg !2433
  %tobool38 = icmp ne i32 %47, 0, !dbg !2435
  %lnot = xor i1 %tobool38, true, !dbg !2435
  br i1 %lnot, label %while.body, label %while.end, !dbg !2436

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i32* %readcount, metadata !2437, metadata !1724), !dbg !2439
  %48 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2440
  %call39 = call i32 @Curl_fillreadbuffer(%struct.connectdata* %48, i32 16384, i32* %readcount), !dbg !2441
  store i32 %call39, i32* %result, align 4, !dbg !2442
  %49 = load i32, i32* %result, align 4, !dbg !2443
  %tobool40 = icmp ne i32 %49, 0, !dbg !2443
  br i1 %tobool40, label %if.then41, label %if.end42, !dbg !2445

if.then41:                                        ; preds = %while.body
  br label %while.end, !dbg !2446

if.end42:                                         ; preds = %while.body
  %50 = load i32, i32* %readcount, align 4, !dbg !2447
  %cmp43 = icmp sle i32 %50, 0, !dbg !2449
  br i1 %cmp43, label %if.then44, label %if.end45, !dbg !2450

if.then44:                                        ; preds = %if.end42
  br label %while.end, !dbg !2451

if.end45:                                         ; preds = %if.end42
  %51 = load i32, i32* %readcount, align 4, !dbg !2452
  %conv = sext i32 %51 to i64, !dbg !2453
  store i64 %conv, i64* %nread, align 8, !dbg !2454
  %52 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2455
  %state46 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %52, i32 0, i32 17, !dbg !2457
  %resume_from47 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state46, i32 0, i32 43, !dbg !2458
  %53 = load i64, i64* %resume_from47, align 8, !dbg !2458
  %tobool48 = icmp ne i64 %53, 0, !dbg !2455
  br i1 %tobool48, label %if.then49, label %if.else66, !dbg !2459

if.then49:                                        ; preds = %if.end45
  %54 = load i64, i64* %nread, align 8, !dbg !2460
  %55 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2463
  %state50 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %55, i32 0, i32 17, !dbg !2464
  %resume_from51 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state50, i32 0, i32 43, !dbg !2465
  %56 = load i64, i64* %resume_from51, align 8, !dbg !2465
  %cmp52 = icmp sle i64 %54, %56, !dbg !2466
  br i1 %cmp52, label %if.then54, label %if.else57, !dbg !2467

if.then54:                                        ; preds = %if.then49
  %57 = load i64, i64* %nread, align 8, !dbg !2468
  %58 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2470
  %state55 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %58, i32 0, i32 17, !dbg !2471
  %resume_from56 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state55, i32 0, i32 43, !dbg !2472
  %59 = load i64, i64* %resume_from56, align 8, !dbg !2473
  %sub = sub i64 %59, %57, !dbg !2473
  store i64 %sub, i64* %resume_from56, align 8, !dbg !2473
  store i64 0, i64* %nread, align 8, !dbg !2474
  %60 = load i8*, i8** %buf, align 8, !dbg !2475
  store i8* %60, i8** %buf2, align 8, !dbg !2476
  br label %if.end65, !dbg !2477

if.else57:                                        ; preds = %if.then49
  %61 = load i8*, i8** %buf, align 8, !dbg !2478
  %62 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2480
  %state58 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %62, i32 0, i32 17, !dbg !2481
  %resume_from59 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state58, i32 0, i32 43, !dbg !2482
  %63 = load i64, i64* %resume_from59, align 8, !dbg !2482
  %add.ptr = getelementptr inbounds i8, i8* %61, i64 %63, !dbg !2483
  store i8* %add.ptr, i8** %buf2, align 8, !dbg !2484
  %64 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2485
  %state60 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %64, i32 0, i32 17, !dbg !2486
  %resume_from61 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state60, i32 0, i32 43, !dbg !2487
  %65 = load i64, i64* %resume_from61, align 8, !dbg !2487
  %66 = load i64, i64* %nread, align 8, !dbg !2488
  %sub62 = sub i64 %66, %65, !dbg !2488
  store i64 %sub62, i64* %nread, align 8, !dbg !2488
  %67 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2489
  %state63 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %67, i32 0, i32 17, !dbg !2490
  %resume_from64 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state63, i32 0, i32 43, !dbg !2491
  store i64 0, i64* %resume_from64, align 8, !dbg !2492
  br label %if.end65

if.end65:                                         ; preds = %if.else57, %if.then54
  br label %if.end67, !dbg !2493

if.else66:                                        ; preds = %if.end45
  %68 = load i8*, i8** %buf, align 8, !dbg !2494
  store i8* %68, i8** %buf2, align 8, !dbg !2495
  br label %if.end67

if.end67:                                         ; preds = %if.else66, %if.end65
  %69 = load i32, i32* %fd, align 4, !dbg !2496
  %70 = load i8*, i8** %buf2, align 8, !dbg !2497
  %71 = load i64, i64* %nread, align 8, !dbg !2498
  %call68 = call i64 @write(i32 %69, i8* %70, i64 %71), !dbg !2499
  store i64 %call68, i64* %nwrite, align 8, !dbg !2500
  %72 = load i64, i64* %nwrite, align 8, !dbg !2501
  %73 = load i64, i64* %nread, align 8, !dbg !2503
  %cmp69 = icmp ne i64 %72, %73, !dbg !2504
  br i1 %cmp69, label %if.then71, label %if.end72, !dbg !2505

if.then71:                                        ; preds = %if.end67
  store i32 55, i32* %result, align 4, !dbg !2506
  br label %while.end, !dbg !2508

if.end72:                                         ; preds = %if.end67
  %74 = load i64, i64* %nread, align 8, !dbg !2509
  %75 = load i64, i64* %bytecount, align 8, !dbg !2510
  %add = add i64 %75, %74, !dbg !2510
  store i64 %add, i64* %bytecount, align 8, !dbg !2510
  %76 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2511
  %77 = load i64, i64* %bytecount, align 8, !dbg !2512
  call void @Curl_pgrsSetUploadCounter(%struct.Curl_easy* %76, i64 %77), !dbg !2513
  %78 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2514
  %call73 = call i32 @Curl_pgrsUpdate(%struct.connectdata* %78), !dbg !2516
  %tobool74 = icmp ne i32 %call73, 0, !dbg !2516
  br i1 %tobool74, label %if.then75, label %if.else76, !dbg !2517

if.then75:                                        ; preds = %if.end72
  store i32 42, i32* %result, align 4, !dbg !2518
  br label %if.end78, !dbg !2519

if.else76:                                        ; preds = %if.end72
  %79 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2520
  %80 = bitcast %struct.timeval* %now to { i64, i64 }*, !dbg !2521
  %81 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %80, i32 0, i32 0, !dbg !2521
  %82 = load i64, i64* %81, align 8, !dbg !2521
  %83 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %80, i32 0, i32 1, !dbg !2521
  %84 = load i64, i64* %83, align 8, !dbg !2521
  %call77 = call i32 @Curl_speedcheck(%struct.Curl_easy* %79, i64 %82, i64 %84), !dbg !2521
  store i32 %call77, i32* %result, align 4, !dbg !2522
  br label %if.end78

if.end78:                                         ; preds = %if.else76, %if.then75
  br label %while.cond, !dbg !2523

while.end:                                        ; preds = %if.then71, %if.then44, %if.then41, %while.cond
  %85 = load i32, i32* %result, align 4, !dbg !2525
  %tobool79 = icmp ne i32 %85, 0, !dbg !2525
  br i1 %tobool79, label %if.end83, label %land.lhs.true, !dbg !2527

land.lhs.true:                                    ; preds = %while.end
  %86 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2528
  %call80 = call i32 @Curl_pgrsUpdate(%struct.connectdata* %86), !dbg !2530
  %tobool81 = icmp ne i32 %call80, 0, !dbg !2530
  br i1 %tobool81, label %if.then82, label %if.end83, !dbg !2531

if.then82:                                        ; preds = %land.lhs.true
  store i32 42, i32* %result, align 4, !dbg !2532
  br label %if.end83, !dbg !2533

if.end83:                                         ; preds = %if.then82, %land.lhs.true, %while.end
  %87 = load i32, i32* %fd, align 4, !dbg !2534
  %call84 = call i32 @close(i32 %87), !dbg !2535
  %88 = load i32, i32* %result, align 4, !dbg !2536
  store i32 %88, i32* %retval, align 4, !dbg !2537
  br label %return, !dbg !2537

return:                                           ; preds = %if.end83, %if.then31, %if.then16, %if.then7, %if.then
  %89 = load i32, i32* %retval, align 4, !dbg !2538
  ret i32 %89, !dbg !2538
}

; Function Attrs: nounwind
declare i32 @fstat64(i32, %struct.stat*) #4

declare zeroext i1 @Curl_meets_timecondition(%struct.Curl_easy*, i64) #2

declare i32 @curl_msnprintf(i8*, i64, i8*, ...) #2

declare i32 @Curl_client_write(%struct.connectdata*, i32, i8*, i64) #2

declare i32 @Curl_gmtime(i64, %struct.tm*) #2

declare void @Curl_pgrsSetDownloadSize(%struct.Curl_easy*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @file_range(%struct.connectdata* %conn) #0 !dbg !1717 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %from = alloca i64, align 8
  %to = alloca i64, align 8
  %totalsize = alloca i64, align 8
  %ptr = alloca i8*, align 8
  %ptr2 = alloca i8*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2539, metadata !1724), !dbg !2540
  call void @llvm.dbg.declare(metadata i64* %from, metadata !2541, metadata !1724), !dbg !2542
  call void @llvm.dbg.declare(metadata i64* %to, metadata !2543, metadata !1724), !dbg !2544
  call void @llvm.dbg.declare(metadata i64* %totalsize, metadata !2545, metadata !1724), !dbg !2546
  store i64 -1, i64* %totalsize, align 8, !dbg !2546
  call void @llvm.dbg.declare(metadata i8** %ptr, metadata !2547, metadata !1724), !dbg !2548
  call void @llvm.dbg.declare(metadata i8** %ptr2, metadata !2549, metadata !1724), !dbg !2550
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2551, metadata !1724), !dbg !2552
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2553
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2554
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2554
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2552
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2555
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 17, !dbg !2557
  %use_range = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 40, !dbg !2558
  %3 = load i8, i8* %use_range, align 1, !dbg !2558
  %tobool = trunc i8 %3 to i1, !dbg !2558
  br i1 %tobool, label %land.lhs.true, label %if.else43, !dbg !2559

land.lhs.true:                                    ; preds = %entry
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2560
  %state2 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 17, !dbg !2562
  %range = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state2, i32 0, i32 42, !dbg !2563
  %5 = load i8*, i8** %range, align 8, !dbg !2563
  %tobool3 = icmp ne i8* %5, null, !dbg !2560
  br i1 %tobool3, label %if.then, label %if.else43, !dbg !2564

if.then:                                          ; preds = %land.lhs.true
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2565
  %state4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 17, !dbg !2567
  %range5 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state4, i32 0, i32 42, !dbg !2568
  %7 = load i8*, i8** %range5, align 8, !dbg !2568
  %call = call i64 @strtol(i8* %7, i8** %ptr, i32 0) #6, !dbg !2569
  store i64 %call, i64* %from, align 8, !dbg !2570
  br label %while.cond, !dbg !2571

while.cond:                                       ; preds = %while.body, %if.then
  %8 = load i8*, i8** %ptr, align 8, !dbg !2572
  %9 = load i8, i8* %8, align 1, !dbg !2574
  %conv = sext i8 %9 to i32, !dbg !2574
  %tobool6 = icmp ne i32 %conv, 0, !dbg !2574
  br i1 %tobool6, label %land.rhs, label %land.end, !dbg !2575

land.rhs:                                         ; preds = %while.cond
  %10 = load i8*, i8** %ptr, align 8, !dbg !2576
  %11 = load i8, i8* %10, align 1, !dbg !2576
  %conv7 = zext i8 %11 to i32, !dbg !2576
  %idxprom = sext i32 %conv7 to i64, !dbg !2576
  %call8 = call i16** @__ctype_b_loc() #1, !dbg !2576
  %12 = load i16*, i16** %call8, align 8, !dbg !2576
  %arrayidx = getelementptr inbounds i16, i16* %12, i64 %idxprom, !dbg !2576
  %13 = load i16, i16* %arrayidx, align 2, !dbg !2576
  %conv9 = zext i16 %13 to i32, !dbg !2576
  %and = and i32 %conv9, 8192, !dbg !2576
  %tobool10 = icmp ne i32 %and, 0, !dbg !2576
  br i1 %tobool10, label %lor.end, label %lor.rhs, !dbg !2578

lor.rhs:                                          ; preds = %land.rhs
  %14 = load i8*, i8** %ptr, align 8, !dbg !2579
  %15 = load i8, i8* %14, align 1, !dbg !2581
  %conv11 = sext i8 %15 to i32, !dbg !2581
  %cmp = icmp eq i32 %conv11, 45, !dbg !2582
  br label %lor.end, !dbg !2583

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %16 = phi i1 [ true, %land.rhs ], [ %cmp, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond
  %17 = phi i1 [ false, %while.cond ], [ %16, %lor.end ]
  br i1 %17, label %while.body, label %while.end, !dbg !2584

while.body:                                       ; preds = %land.end
  %18 = load i8*, i8** %ptr, align 8, !dbg !2586
  %incdec.ptr = getelementptr inbounds i8, i8* %18, i32 1, !dbg !2586
  store i8* %incdec.ptr, i8** %ptr, align 8, !dbg !2586
  br label %while.cond, !dbg !2587

while.end:                                        ; preds = %land.end
  %19 = load i8*, i8** %ptr, align 8, !dbg !2589
  %call13 = call i64 @strtol(i8* %19, i8** %ptr2, i32 0) #6, !dbg !2590
  store i64 %call13, i64* %to, align 8, !dbg !2591
  %20 = load i8*, i8** %ptr, align 8, !dbg !2592
  %21 = load i8*, i8** %ptr2, align 8, !dbg !2594
  %cmp14 = icmp eq i8* %20, %21, !dbg !2595
  br i1 %cmp14, label %if.then16, label %if.end, !dbg !2596

if.then16:                                        ; preds = %while.end
  store i64 -1, i64* %to, align 8, !dbg !2597
  br label %if.end, !dbg !2599

if.end:                                           ; preds = %if.then16, %while.end
  %22 = load i64, i64* %to, align 8, !dbg !2600
  %cmp17 = icmp eq i64 -1, %22, !dbg !2602
  br i1 %cmp17, label %land.lhs.true19, label %if.else, !dbg !2603

land.lhs.true19:                                  ; preds = %if.end
  %23 = load i64, i64* %from, align 8, !dbg !2604
  %cmp20 = icmp sge i64 %23, 0, !dbg !2606
  br i1 %cmp20, label %if.then22, label %if.else, !dbg !2607

if.then22:                                        ; preds = %land.lhs.true19
  %24 = load i64, i64* %from, align 8, !dbg !2608
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2610
  %state23 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 17, !dbg !2611
  %resume_from = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state23, i32 0, i32 43, !dbg !2612
  store i64 %24, i64* %resume_from, align 8, !dbg !2613
  br label %do.body, !dbg !2614

do.body:                                          ; preds = %if.then22
  br label %do.end, !dbg !2615

do.end:                                           ; preds = %do.body
  br label %if.end40, !dbg !2618

if.else:                                          ; preds = %land.lhs.true19, %if.end
  %26 = load i64, i64* %from, align 8, !dbg !2619
  %cmp24 = icmp slt i64 %26, 0, !dbg !2621
  br i1 %cmp24, label %if.then26, label %if.else31, !dbg !2622

if.then26:                                        ; preds = %if.else
  %27 = load i64, i64* %from, align 8, !dbg !2623
  %sub = sub nsw i64 0, %27, !dbg !2625
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2626
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %28, i32 0, i32 12, !dbg !2627
  %maxdownload = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 2, !dbg !2628
  store i64 %sub, i64* %maxdownload, align 8, !dbg !2629
  %29 = load i64, i64* %from, align 8, !dbg !2630
  %30 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2631
  %state27 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %30, i32 0, i32 17, !dbg !2632
  %resume_from28 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state27, i32 0, i32 43, !dbg !2633
  store i64 %29, i64* %resume_from28, align 8, !dbg !2634
  br label %do.body29, !dbg !2635

do.body29:                                        ; preds = %if.then26
  br label %do.end30, !dbg !2636

do.end30:                                         ; preds = %do.body29
  br label %if.end39, !dbg !2639

if.else31:                                        ; preds = %if.else
  %31 = load i64, i64* %to, align 8, !dbg !2640
  %32 = load i64, i64* %from, align 8, !dbg !2642
  %sub32 = sub nsw i64 %31, %32, !dbg !2643
  store i64 %sub32, i64* %totalsize, align 8, !dbg !2644
  %33 = load i64, i64* %totalsize, align 8, !dbg !2645
  %add = add nsw i64 %33, 1, !dbg !2646
  %34 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2647
  %req33 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %34, i32 0, i32 12, !dbg !2648
  %maxdownload34 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req33, i32 0, i32 2, !dbg !2649
  store i64 %add, i64* %maxdownload34, align 8, !dbg !2650
  %35 = load i64, i64* %from, align 8, !dbg !2651
  %36 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2652
  %state35 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %36, i32 0, i32 17, !dbg !2653
  %resume_from36 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state35, i32 0, i32 43, !dbg !2654
  store i64 %35, i64* %resume_from36, align 8, !dbg !2655
  br label %do.body37, !dbg !2656

do.body37:                                        ; preds = %if.else31
  br label %do.end38, !dbg !2657

do.end38:                                         ; preds = %do.body37
  br label %if.end39

if.end39:                                         ; preds = %do.end38, %do.end30
  br label %if.end40

if.end40:                                         ; preds = %if.end39, %do.end
  br label %do.body41, !dbg !2660

do.body41:                                        ; preds = %if.end40
  br label %do.end42, !dbg !2661

do.end42:                                         ; preds = %do.body41
  br label %if.end46, !dbg !2664

if.else43:                                        ; preds = %land.lhs.true, %entry
  %37 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2665
  %req44 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %37, i32 0, i32 12, !dbg !2666
  %maxdownload45 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req44, i32 0, i32 2, !dbg !2667
  store i64 -1, i64* %maxdownload45, align 8, !dbg !2668
  br label %if.end46

if.end46:                                         ; preds = %if.else43, %do.end42
  ret i32 0, !dbg !2669
}

; Function Attrs: nounwind
declare i64 @lseek64(i32, i64, i32) #4

declare void @Curl_pgrsTime(%struct.Curl_easy*, i32) #2

declare i64 @curlx_sotouz(i64) #2

declare i64 @read(i32, i8*, i64) #2

declare void @Curl_pgrsSetDownloadCounter(%struct.Curl_easy*, i64) #2

declare i32 @Curl_pgrsUpdate(%struct.connectdata*) #2

declare i32 @Curl_speedcheck(%struct.Curl_easy*, i64, i64) #2

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #3

declare void @Curl_pgrsSetUploadSize(%struct.Curl_easy*, i64) #2

declare i32 @Curl_fillreadbuffer(%struct.connectdata*, i32, i32*) #2

declare i64 @write(i32, i8*, i64) #2

declare void @Curl_pgrsSetUploadCounter(%struct.Curl_easy*, i64) #2

; Function Attrs: nounwind
declare i64 @strtol(i8*, i8**, i32) #4

; Function Attrs: nounwind readnone
declare i16** @__ctype_b_loc() #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!1720, !1721}
!llvm.ident = !{!1722}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !1708, subprograms: !1709, globals: !1718)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/file.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !100, !123, !129, !185, !227, !234, !269, !279, !285, !290, !297, !307, !316, !322, !328, !334, !340, !347, !353, !359, !374, !385, !399, !410, !415, !423, !461, !480, !500, !515, !532, !540, !1678, !1693}
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
!1678 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1679, line: 28, size: 32, align: 32, elements: !1680)
!1679 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/progress.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1680 = !{!1681, !1682, !1683, !1684, !1685, !1686, !1687, !1688, !1689, !1690, !1691, !1692}
!1681 = !DIEnumerator(name: "TIMER_NONE", value: 0)
!1682 = !DIEnumerator(name: "TIMER_STARTOP", value: 1)
!1683 = !DIEnumerator(name: "TIMER_STARTSINGLE", value: 2)
!1684 = !DIEnumerator(name: "TIMER_NAMELOOKUP", value: 3)
!1685 = !DIEnumerator(name: "TIMER_CONNECT", value: 4)
!1686 = !DIEnumerator(name: "TIMER_APPCONNECT", value: 5)
!1687 = !DIEnumerator(name: "TIMER_PRETRANSFER", value: 6)
!1688 = !DIEnumerator(name: "TIMER_STARTTRANSFER", value: 7)
!1689 = !DIEnumerator(name: "TIMER_POSTRANSFER", value: 8)
!1690 = !DIEnumerator(name: "TIMER_STARTACCEPT", value: 9)
!1691 = !DIEnumerator(name: "TIMER_REDIRECT", value: 10)
!1692 = !DIEnumerator(name: "TIMER_LAST", value: 11)
!1693 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1694, line: 46, size: 32, align: 32, elements: !1695)
!1694 = !DIFile(filename: "/usr/include/ctype.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1695 = !{!1696, !1697, !1698, !1699, !1700, !1701, !1702, !1703, !1704, !1705, !1706, !1707}
!1696 = !DIEnumerator(name: "_ISupper", value: 256)
!1697 = !DIEnumerator(name: "_ISlower", value: 512)
!1698 = !DIEnumerator(name: "_ISalpha", value: 1024)
!1699 = !DIEnumerator(name: "_ISdigit", value: 2048)
!1700 = !DIEnumerator(name: "_ISxdigit", value: 4096)
!1701 = !DIEnumerator(name: "_ISspace", value: 8192)
!1702 = !DIEnumerator(name: "_ISprint", value: 16384)
!1703 = !DIEnumerator(name: "_ISgraph", value: 32768)
!1704 = !DIEnumerator(name: "_ISblank", value: 1)
!1705 = !DIEnumerator(name: "_IScntrl", value: 2)
!1706 = !DIEnumerator(name: "_ISpunct", value: 4)
!1707 = !DIEnumerator(name: "_ISalnum", value: 8)
!1708 = !{!191, !242, !215, !189, !158, !177, !1648, !684}
!1709 = !{!1710, !1712, !1713, !1714, !1715, !1716, !1717}
!1710 = distinct !DISubprogram(name: "file_setup_connection", scope: !1, file: !1, line: 117, type: !1417, isLocal: true, isDefinition: true, scopeLine: 118, flags: DIFlagPrototyped, isOptimized: false, variables: !1711)
!1711 = !{}
!1712 = distinct !DISubprogram(name: "file_connect", scope: !1, file: !1, line: 186, type: !1421, isLocal: true, isDefinition: true, scopeLine: 187, flags: DIFlagPrototyped, isOptimized: false, variables: !1711)
!1713 = distinct !DISubprogram(name: "file_done", scope: !1, file: !1, line: 261, type: !1427, isLocal: true, isDefinition: true, scopeLine: 263, flags: DIFlagPrototyped, isOptimized: false, variables: !1711)
!1714 = distinct !DISubprogram(name: "file_disconnect", scope: !1, file: !1, line: 279, type: !1453, isLocal: true, isDefinition: true, scopeLine: 281, flags: DIFlagPrototyped, isOptimized: false, variables: !1711)
!1715 = distinct !DISubprogram(name: "file_do", scope: !1, file: !1, line: 420, type: !1421, isLocal: true, isDefinition: true, scopeLine: 421, flags: DIFlagPrototyped, isOptimized: false, variables: !1711)
!1716 = distinct !DISubprogram(name: "file_upload", scope: !1, file: !1, line: 302, type: !1417, isLocal: true, isDefinition: true, scopeLine: 303, flags: DIFlagPrototyped, isOptimized: false, variables: !1711)
!1717 = distinct !DISubprogram(name: "file_range", scope: !1, file: !1, line: 132, type: !1417, isLocal: true, isDefinition: true, scopeLine: 133, flags: DIFlagPrototyped, isOptimized: false, variables: !1711)
!1718 = !{!1719}
!1719 = !DIGlobalVariable(name: "Curl_handler_file", scope: !0, file: !1, line: 96, type: !1411, isLocal: false, isDefinition: true, variable: { i8*, i32 (%struct.connectdata*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32, i1)*, i32 (%struct.connectdata*, i32*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i1)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i64, i32, i32 }* @Curl_handler_file)
!1720 = !{i32 2, !"Dwarf Version", i32 4}
!1721 = !{i32 2, !"Debug Info Version", i32 3}
!1722 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!1723 = !DILocalVariable(name: "conn", arg: 1, scope: !1710, file: !1, line: 117, type: !550)
!1724 = !DIExpression()
!1725 = !DILocation(line: 117, column: 59, scope: !1710)
!1726 = !DILocation(line: 120, column: 28, scope: !1710)
!1727 = !DILocation(line: 120, column: 3, scope: !1710)
!1728 = !DILocation(line: 120, column: 9, scope: !1710)
!1729 = !DILocation(line: 120, column: 15, scope: !1710)
!1730 = !DILocation(line: 120, column: 19, scope: !1710)
!1731 = !DILocation(line: 120, column: 26, scope: !1710)
!1732 = !DILocation(line: 121, column: 7, scope: !1733)
!1733 = distinct !DILexicalBlock(scope: !1710, file: !1, line: 121, column: 6)
!1734 = !DILocation(line: 121, column: 13, scope: !1733)
!1735 = !DILocation(line: 121, column: 19, scope: !1733)
!1736 = !DILocation(line: 121, column: 23, scope: !1733)
!1737 = !DILocation(line: 121, column: 6, scope: !1710)
!1738 = !DILocation(line: 122, column: 5, scope: !1733)
!1739 = !DILocation(line: 124, column: 3, scope: !1710)
!1740 = !DILocation(line: 125, column: 1, scope: !1710)
!1741 = !DILocalVariable(name: "conn", arg: 1, scope: !1715, file: !1, line: 420, type: !550)
!1742 = !DILocation(line: 420, column: 45, scope: !1715)
!1743 = !DILocalVariable(name: "done", arg: 2, scope: !1715, file: !1, line: 420, type: !1423)
!1744 = !DILocation(line: 420, column: 57, scope: !1715)
!1745 = !DILocalVariable(name: "result", scope: !1715, file: !1, line: 427, type: !554)
!1746 = !DILocation(line: 427, column: 12, scope: !1715)
!1747 = !DILocalVariable(name: "statbuf", scope: !1715, file: !1, line: 428, type: !1748)
!1748 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !1749, line: 46, size: 1152, align: 64, elements: !1750)
!1749 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1750 = !{!1751, !1753, !1755, !1757, !1759, !1761, !1763, !1764, !1765, !1766, !1768, !1770, !1776, !1777, !1778}
!1751 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !1748, file: !1749, line: 48, baseType: !1752, size: 64, align: 64)
!1752 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !206, line: 124, baseType: !160)
!1753 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !1748, file: !1749, line: 53, baseType: !1754, size: 64, align: 64, offset: 64)
!1754 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !206, line: 127, baseType: !160)
!1755 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !1748, file: !1749, line: 61, baseType: !1756, size: 64, align: 64, offset: 128)
!1756 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !206, line: 130, baseType: !160)
!1757 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !1748, file: !1749, line: 62, baseType: !1758, size: 32, align: 32, offset: 192)
!1758 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !206, line: 129, baseType: !782)
!1759 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !1748, file: !1749, line: 64, baseType: !1760, size: 32, align: 32, offset: 224)
!1760 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !206, line: 125, baseType: !782)
!1761 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !1748, file: !1749, line: 65, baseType: !1762, size: 32, align: 32, offset: 256)
!1762 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !206, line: 126, baseType: !782)
!1763 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !1748, file: !1749, line: 67, baseType: !177, size: 32, align: 32, offset: 288)
!1764 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !1748, file: !1749, line: 69, baseType: !1752, size: 64, align: 64, offset: 320)
!1765 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !1748, file: !1749, line: 74, baseType: !682, size: 64, align: 64, offset: 384)
!1766 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !1748, file: !1749, line: 78, baseType: !1767, size: 64, align: 64, offset: 448)
!1767 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !206, line: 153, baseType: !191)
!1768 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !1748, file: !1749, line: 80, baseType: !1769, size: 64, align: 64, offset: 512)
!1769 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !206, line: 158, baseType: !191)
!1770 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !1748, file: !1749, line: 91, baseType: !1771, size: 128, align: 64, offset: 576)
!1771 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !243, line: 120, size: 128, align: 64, elements: !1772)
!1772 = !{!1773, !1774}
!1773 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !1771, file: !243, line: 122, baseType: !205, size: 64, align: 64)
!1774 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !1771, file: !243, line: 123, baseType: !1775, size: 64, align: 64, offset: 64)
!1775 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !206, line: 175, baseType: !191)
!1776 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !1748, file: !1749, line: 92, baseType: !1771, size: 128, align: 64, offset: 704)
!1777 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !1748, file: !1749, line: 93, baseType: !1771, size: 128, align: 64, offset: 832)
!1778 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !1748, file: !1749, line: 106, baseType: !1779, size: 192, align: 64, offset: 960)
!1779 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1775, size: 192, align: 64, elements: !1143)
!1780 = !DILocation(line: 428, column: 15, scope: !1715)
!1781 = !DILocalVariable(name: "expected_size", scope: !1715, file: !1, line: 431, type: !189)
!1782 = !DILocation(line: 431, column: 14, scope: !1715)
!1783 = !DILocalVariable(name: "size_known", scope: !1715, file: !1, line: 432, type: !211)
!1784 = !DILocation(line: 432, column: 8, scope: !1715)
!1785 = !DILocalVariable(name: "fstated", scope: !1715, file: !1, line: 433, type: !211)
!1786 = !DILocation(line: 433, column: 8, scope: !1715)
!1787 = !DILocalVariable(name: "nread", scope: !1715, file: !1, line: 434, type: !256)
!1788 = !DILocation(line: 434, column: 11, scope: !1715)
!1789 = !DILocalVariable(name: "data", scope: !1715, file: !1, line: 435, type: !544)
!1790 = !DILocation(line: 435, column: 21, scope: !1715)
!1791 = !DILocation(line: 435, column: 28, scope: !1715)
!1792 = !DILocation(line: 435, column: 34, scope: !1715)
!1793 = !DILocalVariable(name: "buf", scope: !1715, file: !1, line: 436, type: !215)
!1794 = !DILocation(line: 436, column: 9, scope: !1715)
!1795 = !DILocation(line: 436, column: 15, scope: !1715)
!1796 = !DILocation(line: 436, column: 21, scope: !1715)
!1797 = !DILocation(line: 436, column: 27, scope: !1715)
!1798 = !DILocalVariable(name: "bytecount", scope: !1715, file: !1, line: 437, type: !189)
!1799 = !DILocation(line: 437, column: 14, scope: !1715)
!1800 = !DILocalVariable(name: "fd", scope: !1715, file: !1, line: 438, type: !177)
!1801 = !DILocation(line: 438, column: 7, scope: !1715)
!1802 = !DILocalVariable(name: "now", scope: !1715, file: !1, line: 439, type: !201)
!1803 = !DILocation(line: 439, column: 18, scope: !1715)
!1804 = !DILocation(line: 439, column: 24, scope: !1715)
!1805 = !DILocalVariable(name: "file", scope: !1715, file: !1, line: 440, type: !1806)
!1806 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1807, size: 64, align: 64)
!1807 = !DICompositeType(tag: DW_TAG_structure_type, name: "FILEPROTO", file: !1808, line: 29, size: 192, align: 64, elements: !1809)
!1808 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/file.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1809 = !{!1810, !1811, !1812}
!1810 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1807, file: !1808, line: 30, baseType: !215, size: 64, align: 64)
!1811 = !DIDerivedType(tag: DW_TAG_member, name: "freepath", scope: !1807, file: !1808, line: 31, baseType: !215, size: 64, align: 64, offset: 64)
!1812 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !1807, file: !1808, line: 33, baseType: !177, size: 32, align: 32, offset: 128)
!1813 = !DILocation(line: 440, column: 21, scope: !1715)
!1814 = !DILocation(line: 442, column: 4, scope: !1715)
!1815 = !DILocation(line: 442, column: 9, scope: !1715)
!1816 = !DILocation(line: 444, column: 17, scope: !1715)
!1817 = !DILocation(line: 444, column: 3, scope: !1715)
!1818 = !DILocation(line: 445, column: 21, scope: !1715)
!1819 = !DILocation(line: 445, column: 3, scope: !1715)
!1820 = !DILocation(line: 447, column: 6, scope: !1821)
!1821 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 447, column: 6)
!1822 = !DILocation(line: 447, column: 12, scope: !1821)
!1823 = !DILocation(line: 447, column: 16, scope: !1821)
!1824 = !DILocation(line: 447, column: 6, scope: !1715)
!1825 = !DILocation(line: 448, column: 24, scope: !1821)
!1826 = !DILocation(line: 448, column: 12, scope: !1821)
!1827 = !DILocation(line: 448, column: 5, scope: !1821)
!1828 = !DILocation(line: 450, column: 10, scope: !1715)
!1829 = !DILocation(line: 450, column: 16, scope: !1715)
!1830 = !DILocation(line: 450, column: 22, scope: !1715)
!1831 = !DILocation(line: 450, column: 26, scope: !1715)
!1832 = !DILocation(line: 450, column: 8, scope: !1715)
!1833 = !DILocation(line: 453, column: 8, scope: !1715)
!1834 = !DILocation(line: 453, column: 14, scope: !1715)
!1835 = !DILocation(line: 453, column: 6, scope: !1715)
!1836 = !DILocation(line: 456, column: 18, scope: !1837)
!1837 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 456, column: 6)
!1838 = !DILocation(line: 456, column: 12, scope: !1837)
!1839 = !DILocation(line: 456, column: 9, scope: !1837)
!1840 = !DILocation(line: 456, column: 6, scope: !1715)
!1841 = !DILocation(line: 458, column: 29, scope: !1842)
!1842 = distinct !DILexicalBlock(scope: !1837, file: !1, line: 456, column: 33)
!1843 = !DILocation(line: 458, column: 19, scope: !1842)
!1844 = !DILocation(line: 460, column: 41, scope: !1842)
!1845 = !DILocation(line: 460, column: 5, scope: !1842)
!1846 = !DILocation(line: 460, column: 11, scope: !1842)
!1847 = !DILocation(line: 460, column: 16, scope: !1842)
!1848 = !DILocation(line: 460, column: 25, scope: !1842)
!1849 = !DILocation(line: 461, column: 13, scope: !1842)
!1850 = !DILocation(line: 462, column: 3, scope: !1842)
!1851 = !DILocation(line: 464, column: 6, scope: !1852)
!1852 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 464, column: 6)
!1853 = !DILocation(line: 464, column: 14, scope: !1852)
!1854 = !DILocation(line: 464, column: 18, scope: !1855)
!1855 = !DILexicalBlockFile(scope: !1852, file: !1, discriminator: 1)
!1856 = !DILocation(line: 464, column: 24, scope: !1855)
!1857 = !DILocation(line: 464, column: 30, scope: !1855)
!1858 = !DILocation(line: 464, column: 36, scope: !1855)
!1859 = !DILocation(line: 464, column: 39, scope: !1860)
!1860 = !DILexicalBlockFile(scope: !1852, file: !1, discriminator: 2)
!1861 = !DILocation(line: 464, column: 45, scope: !1860)
!1862 = !DILocation(line: 464, column: 49, scope: !1860)
!1863 = !DILocation(line: 464, column: 6, scope: !1860)
!1864 = !DILocation(line: 465, column: 34, scope: !1865)
!1865 = distinct !DILexicalBlock(scope: !1866, file: !1, line: 465, column: 8)
!1866 = distinct !DILexicalBlock(scope: !1852, file: !1, line: 464, column: 64)
!1867 = !DILocation(line: 465, column: 48, scope: !1865)
!1868 = !DILocation(line: 465, column: 54, scope: !1865)
!1869 = !DILocation(line: 465, column: 59, scope: !1865)
!1870 = !DILocation(line: 465, column: 9, scope: !1865)
!1871 = !DILocation(line: 465, column: 8, scope: !1866)
!1872 = !DILocation(line: 466, column: 8, scope: !1873)
!1873 = distinct !DILexicalBlock(scope: !1865, file: !1, line: 465, column: 70)
!1874 = !DILocation(line: 466, column: 13, scope: !1873)
!1875 = !DILocation(line: 467, column: 7, scope: !1873)
!1876 = !DILocation(line: 469, column: 3, scope: !1866)
!1877 = !DILocation(line: 474, column: 6, scope: !1878)
!1878 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 474, column: 6)
!1879 = !DILocation(line: 474, column: 12, scope: !1878)
!1880 = !DILocation(line: 474, column: 16, scope: !1878)
!1881 = !DILocation(line: 474, column: 28, scope: !1878)
!1882 = !DILocation(line: 474, column: 31, scope: !1883)
!1883 = !DILexicalBlockFile(scope: !1878, file: !1, discriminator: 1)
!1884 = !DILocation(line: 474, column: 37, scope: !1883)
!1885 = !DILocation(line: 474, column: 41, scope: !1883)
!1886 = !DILocation(line: 474, column: 56, scope: !1883)
!1887 = !DILocation(line: 474, column: 59, scope: !1888)
!1888 = !DILexicalBlockFile(scope: !1878, file: !1, discriminator: 2)
!1889 = !DILocation(line: 474, column: 6, scope: !1888)
!1890 = !DILocalVariable(name: "filetime", scope: !1891, file: !1, line: 475, type: !242)
!1891 = distinct !DILexicalBlock(scope: !1878, file: !1, line: 474, column: 68)
!1892 = !DILocation(line: 475, column: 12, scope: !1891)
!1893 = !DILocalVariable(name: "buffer", scope: !1891, file: !1, line: 476, type: !1894)
!1894 = !DICompositeType(tag: DW_TAG_structure_type, name: "tm", file: !243, line: 133, size: 448, align: 64, elements: !1895)
!1895 = !{!1896, !1897, !1898, !1899, !1900, !1901, !1902, !1903, !1904, !1905, !1906}
!1896 = !DIDerivedType(tag: DW_TAG_member, name: "tm_sec", scope: !1894, file: !243, line: 135, baseType: !177, size: 32, align: 32)
!1897 = !DIDerivedType(tag: DW_TAG_member, name: "tm_min", scope: !1894, file: !243, line: 136, baseType: !177, size: 32, align: 32, offset: 32)
!1898 = !DIDerivedType(tag: DW_TAG_member, name: "tm_hour", scope: !1894, file: !243, line: 137, baseType: !177, size: 32, align: 32, offset: 64)
!1899 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mday", scope: !1894, file: !243, line: 138, baseType: !177, size: 32, align: 32, offset: 96)
!1900 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mon", scope: !1894, file: !243, line: 139, baseType: !177, size: 32, align: 32, offset: 128)
!1901 = !DIDerivedType(tag: DW_TAG_member, name: "tm_year", scope: !1894, file: !243, line: 140, baseType: !177, size: 32, align: 32, offset: 160)
!1902 = !DIDerivedType(tag: DW_TAG_member, name: "tm_wday", scope: !1894, file: !243, line: 141, baseType: !177, size: 32, align: 32, offset: 192)
!1903 = !DIDerivedType(tag: DW_TAG_member, name: "tm_yday", scope: !1894, file: !243, line: 142, baseType: !177, size: 32, align: 32, offset: 224)
!1904 = !DIDerivedType(tag: DW_TAG_member, name: "tm_isdst", scope: !1894, file: !243, line: 143, baseType: !177, size: 32, align: 32, offset: 256)
!1905 = !DIDerivedType(tag: DW_TAG_member, name: "tm_gmtoff", scope: !1894, file: !243, line: 146, baseType: !191, size: 64, align: 64, offset: 320)
!1906 = !DIDerivedType(tag: DW_TAG_member, name: "tm_zone", scope: !1894, file: !243, line: 147, baseType: !928, size: 64, align: 64, offset: 384)
!1907 = !DILocation(line: 476, column: 15, scope: !1891)
!1908 = !DILocalVariable(name: "tm", scope: !1891, file: !1, line: 477, type: !1909)
!1909 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1910, size: 64, align: 64)
!1910 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1894)
!1911 = !DILocation(line: 477, column: 22, scope: !1891)
!1912 = !DILocation(line: 478, column: 14, scope: !1891)
!1913 = !DILocation(line: 478, column: 19, scope: !1891)
!1914 = !DILocation(line: 478, column: 19, scope: !1915)
!1915 = !DILexicalBlockFile(scope: !1891, file: !1, discriminator: 1)
!1916 = !DILocation(line: 478, column: 19, scope: !1917)
!1917 = !DILexicalBlockFile(scope: !1891, file: !1, discriminator: 2)
!1918 = !DILocation(line: 478, column: 19, scope: !1919)
!1919 = !DILexicalBlockFile(scope: !1891, file: !1, discriminator: 3)
!1920 = !DILocation(line: 479, column: 65, scope: !1891)
!1921 = !DILocation(line: 478, column: 5, scope: !1919)
!1922 = !DILocation(line: 480, column: 32, scope: !1891)
!1923 = !DILocation(line: 480, column: 56, scope: !1891)
!1924 = !DILocation(line: 480, column: 14, scope: !1891)
!1925 = !DILocation(line: 480, column: 12, scope: !1891)
!1926 = !DILocation(line: 481, column: 8, scope: !1927)
!1927 = distinct !DILexicalBlock(scope: !1891, file: !1, line: 481, column: 8)
!1928 = !DILocation(line: 481, column: 8, scope: !1891)
!1929 = !DILocation(line: 482, column: 14, scope: !1927)
!1930 = !DILocation(line: 482, column: 7, scope: !1927)
!1931 = !DILocation(line: 484, column: 32, scope: !1891)
!1932 = !DILocation(line: 484, column: 14, scope: !1891)
!1933 = !DILocation(line: 484, column: 12, scope: !1891)
!1934 = !DILocation(line: 486, column: 8, scope: !1935)
!1935 = distinct !DILexicalBlock(scope: !1891, file: !1, line: 486, column: 8)
!1936 = !DILocation(line: 486, column: 8, scope: !1891)
!1937 = !DILocation(line: 487, column: 14, scope: !1935)
!1938 = !DILocation(line: 487, column: 7, scope: !1935)
!1939 = !DILocation(line: 489, column: 32, scope: !1891)
!1940 = !DILocation(line: 489, column: 14, scope: !1891)
!1941 = !DILocation(line: 490, column: 26, scope: !1891)
!1942 = !DILocation(line: 490, column: 14, scope: !1891)
!1943 = !DILocation(line: 490, column: 12, scope: !1891)
!1944 = !DILocation(line: 491, column: 8, scope: !1945)
!1945 = distinct !DILexicalBlock(scope: !1891, file: !1, line: 491, column: 8)
!1946 = !DILocation(line: 491, column: 8, scope: !1891)
!1947 = !DILocation(line: 492, column: 14, scope: !1945)
!1948 = !DILocation(line: 492, column: 7, scope: !1945)
!1949 = !DILocation(line: 495, column: 14, scope: !1891)
!1950 = !DILocation(line: 497, column: 25, scope: !1891)
!1951 = !DILocation(line: 497, column: 29, scope: !1891)
!1952 = !DILocation(line: 497, column: 37, scope: !1915)
!1953 = !DILocation(line: 497, column: 41, scope: !1915)
!1954 = !DILocation(line: 497, column: 48, scope: !1915)
!1955 = !DILocation(line: 497, column: 25, scope: !1915)
!1956 = !DILocation(line: 497, column: 25, scope: !1917)
!1957 = !DILocation(line: 497, column: 25, scope: !1919)
!1958 = !DILocation(line: 497, column: 14, scope: !1919)
!1959 = !DILocation(line: 498, column: 14, scope: !1891)
!1960 = !DILocation(line: 498, column: 18, scope: !1891)
!1961 = !DILocation(line: 499, column: 25, scope: !1891)
!1962 = !DILocation(line: 499, column: 29, scope: !1891)
!1963 = !DILocation(line: 499, column: 14, scope: !1891)
!1964 = !DILocation(line: 500, column: 14, scope: !1891)
!1965 = !DILocation(line: 500, column: 18, scope: !1891)
!1966 = !DILocation(line: 500, column: 26, scope: !1891)
!1967 = !DILocation(line: 501, column: 14, scope: !1891)
!1968 = !DILocation(line: 501, column: 18, scope: !1891)
!1969 = !DILocation(line: 502, column: 14, scope: !1891)
!1970 = !DILocation(line: 502, column: 18, scope: !1891)
!1971 = !DILocation(line: 503, column: 14, scope: !1891)
!1972 = !DILocation(line: 503, column: 18, scope: !1891)
!1973 = !DILocation(line: 495, column: 5, scope: !1915)
!1974 = !DILocation(line: 504, column: 32, scope: !1891)
!1975 = !DILocation(line: 504, column: 56, scope: !1891)
!1976 = !DILocation(line: 504, column: 14, scope: !1891)
!1977 = !DILocation(line: 504, column: 12, scope: !1891)
!1978 = !DILocation(line: 505, column: 9, scope: !1979)
!1979 = distinct !DILexicalBlock(scope: !1891, file: !1, line: 505, column: 8)
!1980 = !DILocation(line: 505, column: 8, scope: !1891)
!1981 = !DILocation(line: 507, column: 32, scope: !1979)
!1982 = !DILocation(line: 507, column: 38, scope: !1979)
!1983 = !DILocation(line: 507, column: 7, scope: !1979)
!1984 = !DILocation(line: 508, column: 12, scope: !1891)
!1985 = !DILocation(line: 508, column: 5, scope: !1891)
!1986 = !DILocation(line: 512, column: 14, scope: !1715)
!1987 = !DILocation(line: 512, column: 3, scope: !1715)
!1988 = !DILocation(line: 516, column: 6, scope: !1989)
!1989 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 516, column: 6)
!1990 = !DILocation(line: 516, column: 12, scope: !1989)
!1991 = !DILocation(line: 516, column: 18, scope: !1989)
!1992 = !DILocation(line: 516, column: 30, scope: !1989)
!1993 = !DILocation(line: 516, column: 6, scope: !1715)
!1994 = !DILocation(line: 517, column: 9, scope: !1995)
!1995 = distinct !DILexicalBlock(scope: !1996, file: !1, line: 517, column: 8)
!1996 = distinct !DILexicalBlock(scope: !1989, file: !1, line: 516, column: 35)
!1997 = !DILocation(line: 517, column: 8, scope: !1996)
!1998 = !DILocation(line: 518, column: 13, scope: !1999)
!1999 = distinct !DILexicalBlock(scope: !1995, file: !1, line: 517, column: 18)
!2000 = !DILocation(line: 518, column: 7, scope: !1999)
!2001 = !DILocation(line: 519, column: 7, scope: !1999)
!2002 = !DILocation(line: 521, column: 52, scope: !1996)
!2003 = !DILocation(line: 521, column: 5, scope: !1996)
!2004 = !DILocation(line: 521, column: 11, scope: !1996)
!2005 = !DILocation(line: 521, column: 17, scope: !1996)
!2006 = !DILocation(line: 521, column: 29, scope: !1996)
!2007 = !DILocation(line: 522, column: 3, scope: !1996)
!2008 = !DILocation(line: 524, column: 6, scope: !2009)
!2009 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 524, column: 6)
!2010 = !DILocation(line: 524, column: 12, scope: !2009)
!2011 = !DILocation(line: 524, column: 18, scope: !2009)
!2012 = !DILocation(line: 524, column: 33, scope: !2009)
!2013 = !DILocation(line: 524, column: 30, scope: !2009)
!2014 = !DILocation(line: 524, column: 6, scope: !1715)
!2015 = !DILocation(line: 525, column: 22, scope: !2009)
!2016 = !DILocation(line: 525, column: 28, scope: !2009)
!2017 = !DILocation(line: 525, column: 34, scope: !2009)
!2018 = !DILocation(line: 525, column: 19, scope: !2009)
!2019 = !DILocation(line: 525, column: 5, scope: !2009)
!2020 = !DILocation(line: 527, column: 11, scope: !2021)
!2021 = distinct !DILexicalBlock(scope: !2009, file: !1, line: 526, column: 8)
!2022 = !DILocation(line: 527, column: 5, scope: !2021)
!2023 = !DILocation(line: 528, column: 5, scope: !2021)
!2024 = !DILocation(line: 532, column: 6, scope: !2025)
!2025 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 532, column: 6)
!2026 = !DILocation(line: 532, column: 12, scope: !2025)
!2027 = !DILocation(line: 532, column: 16, scope: !2025)
!2028 = !DILocation(line: 532, column: 28, scope: !2025)
!2029 = !DILocation(line: 532, column: 6, scope: !1715)
!2030 = !DILocation(line: 533, column: 21, scope: !2025)
!2031 = !DILocation(line: 533, column: 27, scope: !2025)
!2032 = !DILocation(line: 533, column: 31, scope: !2025)
!2033 = !DILocation(line: 533, column: 19, scope: !2025)
!2034 = !DILocation(line: 533, column: 5, scope: !2025)
!2035 = !DILocation(line: 535, column: 7, scope: !2036)
!2036 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 535, column: 6)
!2037 = !DILocation(line: 535, column: 15, scope: !2036)
!2038 = !DILocation(line: 535, column: 19, scope: !2039)
!2039 = !DILexicalBlockFile(scope: !2036, file: !1, discriminator: 1)
!2040 = !DILocation(line: 535, column: 33, scope: !2039)
!2041 = !DILocation(line: 535, column: 6, scope: !2039)
!2042 = !DILocation(line: 536, column: 16, scope: !2036)
!2043 = !DILocation(line: 536, column: 5, scope: !2036)
!2044 = !DILocation(line: 538, column: 16, scope: !2036)
!2045 = !DILocation(line: 544, column: 6, scope: !2046)
!2046 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 544, column: 6)
!2047 = !DILocation(line: 544, column: 6, scope: !1715)
!2048 = !DILocation(line: 545, column: 30, scope: !2046)
!2049 = !DILocation(line: 545, column: 36, scope: !2046)
!2050 = !DILocation(line: 545, column: 5, scope: !2046)
!2051 = !DILocation(line: 547, column: 6, scope: !2052)
!2052 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 547, column: 6)
!2053 = !DILocation(line: 547, column: 12, scope: !2052)
!2054 = !DILocation(line: 547, column: 18, scope: !2052)
!2055 = !DILocation(line: 547, column: 6, scope: !1715)
!2056 = !DILocation(line: 548, column: 8, scope: !2057)
!2057 = distinct !DILexicalBlock(scope: !2058, file: !1, line: 548, column: 8)
!2058 = distinct !DILexicalBlock(scope: !2052, file: !1, line: 547, column: 31)
!2059 = !DILocation(line: 548, column: 14, scope: !2057)
!2060 = !DILocation(line: 548, column: 20, scope: !2057)
!2061 = !DILocation(line: 549, column: 14, scope: !2057)
!2062 = !DILocation(line: 549, column: 18, scope: !2057)
!2063 = !DILocation(line: 549, column: 24, scope: !2057)
!2064 = !DILocation(line: 549, column: 30, scope: !2057)
!2065 = !DILocation(line: 549, column: 8, scope: !2057)
!2066 = !DILocation(line: 548, column: 32, scope: !2057)
!2067 = !DILocation(line: 548, column: 8, scope: !2058)
!2068 = !DILocation(line: 550, column: 7, scope: !2057)
!2069 = !DILocation(line: 551, column: 3, scope: !2058)
!2070 = !DILocation(line: 553, column: 17, scope: !1715)
!2071 = !DILocation(line: 553, column: 3, scope: !1715)
!2072 = !DILocation(line: 555, column: 3, scope: !1715)
!2073 = !DILocation(line: 555, column: 10, scope: !2074)
!2074 = !DILexicalBlockFile(scope: !1715, file: !1, discriminator: 1)
!2075 = !DILocation(line: 555, column: 9, scope: !2074)
!2076 = !DILocation(line: 555, column: 3, scope: !2074)
!2077 = !DILocalVariable(name: "bytestoread", scope: !2078, file: !1, line: 557, type: !158)
!2078 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 555, column: 18)
!2079 = !DILocation(line: 557, column: 12, scope: !2078)
!2080 = !DILocation(line: 559, column: 8, scope: !2081)
!2081 = distinct !DILexicalBlock(scope: !2078, file: !1, line: 559, column: 8)
!2082 = !DILocation(line: 559, column: 8, scope: !2078)
!2083 = !DILocation(line: 561, column: 10, scope: !2084)
!2084 = distinct !DILexicalBlock(scope: !2081, file: !1, line: 559, column: 20)
!2085 = !DILocation(line: 561, column: 24, scope: !2084)
!2086 = !DILocation(line: 561, column: 9, scope: !2084)
!2087 = !DILocation(line: 562, column: 22, scope: !2084)
!2088 = !DILocation(line: 562, column: 9, scope: !2084)
!2089 = !DILocation(line: 561, column: 9, scope: !2090)
!2090 = !DILexicalBlockFile(scope: !2084, file: !1, discriminator: 1)
!2091 = !DILocation(line: 561, column: 9, scope: !2092)
!2092 = !DILexicalBlockFile(scope: !2084, file: !1, discriminator: 2)
!2093 = !DILocation(line: 561, column: 9, scope: !2094)
!2094 = !DILexicalBlockFile(scope: !2084, file: !1, discriminator: 3)
!2095 = !DILocation(line: 560, column: 19, scope: !2084)
!2096 = !DILocation(line: 563, column: 5, scope: !2084)
!2097 = !DILocation(line: 565, column: 19, scope: !2081)
!2098 = !DILocation(line: 567, column: 18, scope: !2078)
!2099 = !DILocation(line: 567, column: 22, scope: !2078)
!2100 = !DILocation(line: 567, column: 27, scope: !2078)
!2101 = !DILocation(line: 567, column: 13, scope: !2078)
!2102 = !DILocation(line: 567, column: 11, scope: !2078)
!2103 = !DILocation(line: 569, column: 8, scope: !2104)
!2104 = distinct !DILexicalBlock(scope: !2078, file: !1, line: 569, column: 8)
!2105 = !DILocation(line: 569, column: 14, scope: !2104)
!2106 = !DILocation(line: 569, column: 8, scope: !2078)
!2107 = !DILocation(line: 570, column: 11, scope: !2104)
!2108 = !DILocation(line: 570, column: 7, scope: !2104)
!2109 = !DILocation(line: 570, column: 18, scope: !2104)
!2110 = !DILocation(line: 572, column: 8, scope: !2111)
!2111 = distinct !DILexicalBlock(scope: !2078, file: !1, line: 572, column: 8)
!2112 = !DILocation(line: 572, column: 14, scope: !2111)
!2113 = !DILocation(line: 572, column: 19, scope: !2111)
!2114 = !DILocation(line: 572, column: 23, scope: !2115)
!2115 = !DILexicalBlockFile(scope: !2111, file: !1, discriminator: 1)
!2116 = !DILocation(line: 572, column: 34, scope: !2115)
!2117 = !DILocation(line: 572, column: 38, scope: !2118)
!2118 = !DILexicalBlockFile(scope: !2111, file: !1, discriminator: 2)
!2119 = !DILocation(line: 572, column: 52, scope: !2118)
!2120 = !DILocation(line: 572, column: 8, scope: !2118)
!2121 = !DILocation(line: 573, column: 7, scope: !2111)
!2122 = !DILocation(line: 575, column: 18, scope: !2078)
!2123 = !DILocation(line: 575, column: 15, scope: !2078)
!2124 = !DILocation(line: 576, column: 8, scope: !2125)
!2125 = distinct !DILexicalBlock(scope: !2078, file: !1, line: 576, column: 8)
!2126 = !DILocation(line: 576, column: 8, scope: !2078)
!2127 = !DILocation(line: 577, column: 24, scope: !2125)
!2128 = !DILocation(line: 577, column: 21, scope: !2125)
!2129 = !DILocation(line: 577, column: 7, scope: !2125)
!2130 = !DILocation(line: 579, column: 32, scope: !2078)
!2131 = !DILocation(line: 579, column: 56, scope: !2078)
!2132 = !DILocation(line: 579, column: 61, scope: !2078)
!2133 = !DILocation(line: 579, column: 14, scope: !2078)
!2134 = !DILocation(line: 579, column: 12, scope: !2078)
!2135 = !DILocation(line: 580, column: 8, scope: !2136)
!2136 = distinct !DILexicalBlock(scope: !2078, file: !1, line: 580, column: 8)
!2137 = !DILocation(line: 580, column: 8, scope: !2078)
!2138 = !DILocation(line: 581, column: 14, scope: !2136)
!2139 = !DILocation(line: 581, column: 7, scope: !2136)
!2140 = !DILocation(line: 583, column: 33, scope: !2078)
!2141 = !DILocation(line: 583, column: 39, scope: !2078)
!2142 = !DILocation(line: 583, column: 5, scope: !2078)
!2143 = !DILocation(line: 585, column: 24, scope: !2144)
!2144 = distinct !DILexicalBlock(scope: !2078, file: !1, line: 585, column: 8)
!2145 = !DILocation(line: 585, column: 8, scope: !2144)
!2146 = !DILocation(line: 585, column: 8, scope: !2078)
!2147 = !DILocation(line: 586, column: 14, scope: !2144)
!2148 = !DILocation(line: 586, column: 7, scope: !2144)
!2149 = !DILocation(line: 588, column: 32, scope: !2144)
!2150 = !DILocation(line: 588, column: 16, scope: !2144)
!2151 = !DILocation(line: 588, column: 14, scope: !2144)
!2152 = !DILocation(line: 555, column: 3, scope: !2153)
!2153 = !DILexicalBlockFile(scope: !1715, file: !1, discriminator: 2)
!2154 = !DILocation(line: 590, column: 22, scope: !2155)
!2155 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 590, column: 6)
!2156 = !DILocation(line: 590, column: 6, scope: !2155)
!2157 = !DILocation(line: 590, column: 6, scope: !1715)
!2158 = !DILocation(line: 591, column: 12, scope: !2155)
!2159 = !DILocation(line: 591, column: 5, scope: !2155)
!2160 = !DILocation(line: 593, column: 10, scope: !1715)
!2161 = !DILocation(line: 593, column: 3, scope: !1715)
!2162 = !DILocation(line: 594, column: 1, scope: !1715)
!2163 = !DILocalVariable(name: "conn", arg: 1, scope: !1713, file: !1, line: 261, type: !550)
!2164 = !DILocation(line: 261, column: 47, scope: !1713)
!2165 = !DILocalVariable(name: "status", arg: 2, scope: !1713, file: !1, line: 262, type: !554)
!2166 = !DILocation(line: 262, column: 41, scope: !1713)
!2167 = !DILocalVariable(name: "premature", arg: 3, scope: !1713, file: !1, line: 262, type: !211)
!2168 = !DILocation(line: 262, column: 54, scope: !1713)
!2169 = !DILocalVariable(name: "file", scope: !1713, file: !1, line: 264, type: !1806)
!2170 = !DILocation(line: 264, column: 21, scope: !1713)
!2171 = !DILocation(line: 264, column: 28, scope: !1713)
!2172 = !DILocation(line: 264, column: 34, scope: !1713)
!2173 = !DILocation(line: 264, column: 40, scope: !1713)
!2174 = !DILocation(line: 264, column: 44, scope: !1713)
!2175 = !DILocation(line: 265, column: 9, scope: !1713)
!2176 = !DILocation(line: 266, column: 9, scope: !1713)
!2177 = !DILocation(line: 268, column: 6, scope: !2178)
!2178 = distinct !DILexicalBlock(scope: !1713, file: !1, line: 268, column: 6)
!2179 = !DILocation(line: 268, column: 6, scope: !1713)
!2180 = !DILocation(line: 269, column: 5, scope: !2181)
!2181 = distinct !DILexicalBlock(scope: !2178, file: !1, line: 268, column: 12)
!2182 = !DILocation(line: 269, column: 5, scope: !2183)
!2183 = !DILexicalBlockFile(scope: !2184, file: !1, discriminator: 1)
!2184 = distinct !DILexicalBlock(scope: !2181, file: !1, line: 269, column: 5)
!2185 = !DILocation(line: 270, column: 5, scope: !2181)
!2186 = !DILocation(line: 270, column: 11, scope: !2181)
!2187 = !DILocation(line: 270, column: 16, scope: !2181)
!2188 = !DILocation(line: 271, column: 8, scope: !2189)
!2189 = distinct !DILexicalBlock(scope: !2181, file: !1, line: 271, column: 8)
!2190 = !DILocation(line: 271, column: 14, scope: !2189)
!2191 = !DILocation(line: 271, column: 17, scope: !2189)
!2192 = !DILocation(line: 271, column: 8, scope: !2181)
!2193 = !DILocation(line: 272, column: 13, scope: !2189)
!2194 = !DILocation(line: 272, column: 19, scope: !2189)
!2195 = !DILocation(line: 272, column: 7, scope: !2189)
!2196 = !DILocation(line: 273, column: 5, scope: !2181)
!2197 = !DILocation(line: 273, column: 11, scope: !2181)
!2198 = !DILocation(line: 273, column: 14, scope: !2181)
!2199 = !DILocation(line: 274, column: 3, scope: !2181)
!2200 = !DILocation(line: 276, column: 3, scope: !1713)
!2201 = !DILocalVariable(name: "conn", arg: 1, scope: !1712, file: !1, line: 186, type: !550)
!2202 = !DILocation(line: 186, column: 50, scope: !1712)
!2203 = !DILocalVariable(name: "done", arg: 2, scope: !1712, file: !1, line: 186, type: !1423)
!2204 = !DILocation(line: 186, column: 62, scope: !1712)
!2205 = !DILocalVariable(name: "data", scope: !1712, file: !1, line: 188, type: !544)
!2206 = !DILocation(line: 188, column: 21, scope: !1712)
!2207 = !DILocation(line: 188, column: 28, scope: !1712)
!2208 = !DILocation(line: 188, column: 34, scope: !1712)
!2209 = !DILocalVariable(name: "real_path", scope: !1712, file: !1, line: 189, type: !215)
!2210 = !DILocation(line: 189, column: 9, scope: !1712)
!2211 = !DILocalVariable(name: "file", scope: !1712, file: !1, line: 190, type: !1806)
!2212 = !DILocation(line: 190, column: 21, scope: !1712)
!2213 = !DILocation(line: 190, column: 28, scope: !1712)
!2214 = !DILocation(line: 190, column: 34, scope: !1712)
!2215 = !DILocation(line: 190, column: 38, scope: !1712)
!2216 = !DILocalVariable(name: "fd", scope: !1712, file: !1, line: 191, type: !177)
!2217 = !DILocation(line: 191, column: 7, scope: !1712)
!2218 = !DILocalVariable(name: "real_path_len", scope: !1712, file: !1, line: 196, type: !158)
!2219 = !DILocation(line: 196, column: 10, scope: !1712)
!2220 = !DILocalVariable(name: "result", scope: !1712, file: !1, line: 198, type: !554)
!2221 = !DILocation(line: 198, column: 12, scope: !1712)
!2222 = !DILocation(line: 198, column: 36, scope: !1712)
!2223 = !DILocation(line: 198, column: 42, scope: !1712)
!2224 = !DILocation(line: 198, column: 48, scope: !1712)
!2225 = !DILocation(line: 198, column: 54, scope: !1712)
!2226 = !DILocation(line: 198, column: 21, scope: !1712)
!2227 = !DILocation(line: 200, column: 6, scope: !2228)
!2228 = distinct !DILexicalBlock(scope: !1712, file: !1, line: 200, column: 6)
!2229 = !DILocation(line: 200, column: 6, scope: !1712)
!2230 = !DILocation(line: 201, column: 12, scope: !2228)
!2231 = !DILocation(line: 201, column: 5, scope: !2228)
!2232 = !DILocation(line: 239, column: 13, scope: !2233)
!2233 = distinct !DILexicalBlock(scope: !1712, file: !1, line: 239, column: 6)
!2234 = !DILocation(line: 239, column: 27, scope: !2233)
!2235 = !DILocation(line: 239, column: 6, scope: !2233)
!2236 = !DILocation(line: 239, column: 6, scope: !1712)
!2237 = !DILocation(line: 241, column: 5, scope: !2238)
!2238 = distinct !DILexicalBlock(scope: !2233, file: !1, line: 239, column: 43)
!2239 = !DILocation(line: 241, column: 5, scope: !2240)
!2240 = !DILexicalBlockFile(scope: !2241, file: !1, discriminator: 1)
!2241 = distinct !DILexicalBlock(scope: !2238, file: !1, line: 241, column: 5)
!2242 = !DILocation(line: 242, column: 5, scope: !2238)
!2243 = !DILocation(line: 245, column: 8, scope: !1712)
!2244 = !DILocation(line: 245, column: 6, scope: !1712)
!2245 = !DILocation(line: 246, column: 16, scope: !1712)
!2246 = !DILocation(line: 246, column: 3, scope: !1712)
!2247 = !DILocation(line: 246, column: 9, scope: !1712)
!2248 = !DILocation(line: 246, column: 14, scope: !1712)
!2249 = !DILocation(line: 248, column: 20, scope: !1712)
!2250 = !DILocation(line: 248, column: 3, scope: !1712)
!2251 = !DILocation(line: 248, column: 9, scope: !1712)
!2252 = !DILocation(line: 248, column: 18, scope: !1712)
!2253 = !DILocation(line: 250, column: 14, scope: !1712)
!2254 = !DILocation(line: 250, column: 3, scope: !1712)
!2255 = !DILocation(line: 250, column: 9, scope: !1712)
!2256 = !DILocation(line: 250, column: 12, scope: !1712)
!2257 = !DILocation(line: 251, column: 7, scope: !2258)
!2258 = distinct !DILexicalBlock(scope: !1712, file: !1, line: 251, column: 6)
!2259 = !DILocation(line: 251, column: 13, scope: !2258)
!2260 = !DILocation(line: 251, column: 17, scope: !2258)
!2261 = !DILocation(line: 251, column: 24, scope: !2258)
!2262 = !DILocation(line: 251, column: 28, scope: !2263)
!2263 = !DILexicalBlockFile(scope: !2258, file: !1, discriminator: 1)
!2264 = !DILocation(line: 251, column: 31, scope: !2263)
!2265 = !DILocation(line: 251, column: 6, scope: !2263)
!2266 = !DILocation(line: 252, column: 11, scope: !2267)
!2267 = distinct !DILexicalBlock(scope: !2258, file: !1, line: 251, column: 39)
!2268 = !DILocation(line: 252, column: 42, scope: !2267)
!2269 = !DILocation(line: 252, column: 48, scope: !2267)
!2270 = !DILocation(line: 252, column: 54, scope: !2267)
!2271 = !DILocation(line: 252, column: 5, scope: !2267)
!2272 = !DILocation(line: 253, column: 15, scope: !2267)
!2273 = !DILocation(line: 253, column: 5, scope: !2267)
!2274 = !DILocation(line: 254, column: 5, scope: !2267)
!2275 = !DILocation(line: 256, column: 4, scope: !1712)
!2276 = !DILocation(line: 256, column: 9, scope: !1712)
!2277 = !DILocation(line: 258, column: 3, scope: !1712)
!2278 = !DILocation(line: 259, column: 1, scope: !1712)
!2279 = !DILocalVariable(name: "conn", arg: 1, scope: !1714, file: !1, line: 279, type: !550)
!2280 = !DILocation(line: 279, column: 53, scope: !1714)
!2281 = !DILocalVariable(name: "dead_connection", arg: 2, scope: !1714, file: !1, line: 280, type: !211)
!2282 = !DILocation(line: 280, column: 38, scope: !1714)
!2283 = !DILocalVariable(name: "file", scope: !1714, file: !1, line: 282, type: !1806)
!2284 = !DILocation(line: 282, column: 21, scope: !1714)
!2285 = !DILocation(line: 282, column: 28, scope: !1714)
!2286 = !DILocation(line: 282, column: 34, scope: !1714)
!2287 = !DILocation(line: 282, column: 40, scope: !1714)
!2288 = !DILocation(line: 282, column: 44, scope: !1714)
!2289 = !DILocation(line: 283, column: 9, scope: !1714)
!2290 = !DILocation(line: 285, column: 6, scope: !2291)
!2291 = distinct !DILexicalBlock(scope: !1714, file: !1, line: 285, column: 6)
!2292 = !DILocation(line: 285, column: 6, scope: !1714)
!2293 = !DILocation(line: 286, column: 5, scope: !2294)
!2294 = distinct !DILexicalBlock(scope: !2291, file: !1, line: 285, column: 12)
!2295 = !DILocation(line: 286, column: 5, scope: !2296)
!2296 = !DILexicalBlockFile(scope: !2297, file: !1, discriminator: 1)
!2297 = distinct !DILexicalBlock(scope: !2294, file: !1, line: 286, column: 5)
!2298 = !DILocation(line: 287, column: 5, scope: !2294)
!2299 = !DILocation(line: 287, column: 11, scope: !2294)
!2300 = !DILocation(line: 287, column: 16, scope: !2294)
!2301 = !DILocation(line: 288, column: 8, scope: !2302)
!2302 = distinct !DILexicalBlock(scope: !2294, file: !1, line: 288, column: 8)
!2303 = !DILocation(line: 288, column: 14, scope: !2302)
!2304 = !DILocation(line: 288, column: 17, scope: !2302)
!2305 = !DILocation(line: 288, column: 8, scope: !2294)
!2306 = !DILocation(line: 289, column: 13, scope: !2302)
!2307 = !DILocation(line: 289, column: 19, scope: !2302)
!2308 = !DILocation(line: 289, column: 7, scope: !2302)
!2309 = !DILocation(line: 290, column: 5, scope: !2294)
!2310 = !DILocation(line: 290, column: 11, scope: !2294)
!2311 = !DILocation(line: 290, column: 14, scope: !2294)
!2312 = !DILocation(line: 291, column: 3, scope: !2294)
!2313 = !DILocation(line: 293, column: 3, scope: !1714)
!2314 = !DILocalVariable(name: "conn", arg: 1, scope: !1716, file: !1, line: 302, type: !550)
!2315 = !DILocation(line: 302, column: 49, scope: !1716)
!2316 = !DILocalVariable(name: "file", scope: !1716, file: !1, line: 304, type: !1806)
!2317 = !DILocation(line: 304, column: 21, scope: !1716)
!2318 = !DILocation(line: 304, column: 28, scope: !1716)
!2319 = !DILocation(line: 304, column: 34, scope: !1716)
!2320 = !DILocation(line: 304, column: 40, scope: !1716)
!2321 = !DILocation(line: 304, column: 44, scope: !1716)
!2322 = !DILocalVariable(name: "dir", scope: !1716, file: !1, line: 305, type: !928)
!2323 = !DILocation(line: 305, column: 15, scope: !1716)
!2324 = !DILocation(line: 305, column: 28, scope: !1716)
!2325 = !DILocation(line: 305, column: 34, scope: !1716)
!2326 = !DILocation(line: 305, column: 21, scope: !1716)
!2327 = !DILocalVariable(name: "fd", scope: !1716, file: !1, line: 306, type: !177)
!2328 = !DILocation(line: 306, column: 7, scope: !1716)
!2329 = !DILocalVariable(name: "mode", scope: !1716, file: !1, line: 307, type: !177)
!2330 = !DILocation(line: 307, column: 7, scope: !1716)
!2331 = !DILocalVariable(name: "result", scope: !1716, file: !1, line: 308, type: !554)
!2332 = !DILocation(line: 308, column: 12, scope: !1716)
!2333 = !DILocalVariable(name: "data", scope: !1716, file: !1, line: 309, type: !544)
!2334 = !DILocation(line: 309, column: 21, scope: !1716)
!2335 = !DILocation(line: 309, column: 28, scope: !1716)
!2336 = !DILocation(line: 309, column: 34, scope: !1716)
!2337 = !DILocalVariable(name: "buf", scope: !1716, file: !1, line: 310, type: !215)
!2338 = !DILocation(line: 310, column: 9, scope: !1716)
!2339 = !DILocation(line: 310, column: 15, scope: !1716)
!2340 = !DILocation(line: 310, column: 21, scope: !1716)
!2341 = !DILocation(line: 310, column: 27, scope: !1716)
!2342 = !DILocalVariable(name: "nread", scope: !1716, file: !1, line: 311, type: !158)
!2343 = !DILocation(line: 311, column: 10, scope: !1716)
!2344 = !DILocalVariable(name: "nwrite", scope: !1716, file: !1, line: 312, type: !158)
!2345 = !DILocation(line: 312, column: 10, scope: !1716)
!2346 = !DILocalVariable(name: "bytecount", scope: !1716, file: !1, line: 313, type: !189)
!2347 = !DILocation(line: 313, column: 14, scope: !1716)
!2348 = !DILocalVariable(name: "now", scope: !1716, file: !1, line: 314, type: !201)
!2349 = !DILocation(line: 314, column: 18, scope: !1716)
!2350 = !DILocation(line: 314, column: 24, scope: !1716)
!2351 = !DILocalVariable(name: "file_stat", scope: !1716, file: !1, line: 315, type: !1748)
!2352 = !DILocation(line: 315, column: 15, scope: !1716)
!2353 = !DILocalVariable(name: "buf2", scope: !1716, file: !1, line: 316, type: !928)
!2354 = !DILocation(line: 316, column: 15, scope: !1716)
!2355 = !DILocation(line: 322, column: 37, scope: !1716)
!2356 = !DILocation(line: 322, column: 3, scope: !1716)
!2357 = !DILocation(line: 322, column: 9, scope: !1716)
!2358 = !DILocation(line: 322, column: 15, scope: !1716)
!2359 = !DILocation(line: 322, column: 19, scope: !1716)
!2360 = !DILocation(line: 322, column: 35, scope: !1716)
!2361 = !DILocation(line: 324, column: 7, scope: !2362)
!2362 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 324, column: 6)
!2363 = !DILocation(line: 324, column: 6, scope: !1716)
!2364 = !DILocation(line: 325, column: 5, scope: !2362)
!2365 = !DILocation(line: 327, column: 7, scope: !2366)
!2366 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 327, column: 6)
!2367 = !DILocation(line: 327, column: 6, scope: !1716)
!2368 = !DILocation(line: 328, column: 5, scope: !2366)
!2369 = !DILocation(line: 336, column: 6, scope: !2370)
!2370 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 336, column: 6)
!2371 = !DILocation(line: 336, column: 12, scope: !2370)
!2372 = !DILocation(line: 336, column: 18, scope: !2370)
!2373 = !DILocation(line: 336, column: 6, scope: !1716)
!2374 = !DILocation(line: 337, column: 10, scope: !2370)
!2375 = !DILocation(line: 337, column: 5, scope: !2370)
!2376 = !DILocation(line: 339, column: 10, scope: !2370)
!2377 = !DILocation(line: 341, column: 13, scope: !1716)
!2378 = !DILocation(line: 341, column: 19, scope: !1716)
!2379 = !DILocation(line: 341, column: 25, scope: !1716)
!2380 = !DILocation(line: 341, column: 31, scope: !1716)
!2381 = !DILocation(line: 341, column: 37, scope: !1716)
!2382 = !DILocation(line: 341, column: 43, scope: !1716)
!2383 = !DILocation(line: 341, column: 47, scope: !1716)
!2384 = !DILocation(line: 341, column: 8, scope: !1716)
!2385 = !DILocation(line: 341, column: 6, scope: !1716)
!2386 = !DILocation(line: 342, column: 6, scope: !2387)
!2387 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 342, column: 6)
!2388 = !DILocation(line: 342, column: 9, scope: !2387)
!2389 = !DILocation(line: 342, column: 6, scope: !1716)
!2390 = !DILocation(line: 343, column: 11, scope: !2391)
!2391 = distinct !DILexicalBlock(scope: !2387, file: !1, line: 342, column: 14)
!2392 = !DILocation(line: 343, column: 46, scope: !2391)
!2393 = !DILocation(line: 343, column: 52, scope: !2391)
!2394 = !DILocation(line: 343, column: 5, scope: !2391)
!2395 = !DILocation(line: 344, column: 5, scope: !2391)
!2396 = !DILocation(line: 347, column: 12, scope: !2397)
!2397 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 347, column: 6)
!2398 = !DILocation(line: 347, column: 18, scope: !2397)
!2399 = !DILocation(line: 347, column: 24, scope: !2397)
!2400 = !DILocation(line: 347, column: 9, scope: !2397)
!2401 = !DILocation(line: 347, column: 6, scope: !1716)
!2402 = !DILocation(line: 349, column: 28, scope: !2397)
!2403 = !DILocation(line: 349, column: 34, scope: !2397)
!2404 = !DILocation(line: 349, column: 40, scope: !2397)
!2405 = !DILocation(line: 349, column: 46, scope: !2397)
!2406 = !DILocation(line: 349, column: 5, scope: !2397)
!2407 = !DILocation(line: 352, column: 6, scope: !2408)
!2408 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 352, column: 6)
!2409 = !DILocation(line: 352, column: 12, scope: !2408)
!2410 = !DILocation(line: 352, column: 18, scope: !2408)
!2411 = !DILocation(line: 352, column: 30, scope: !2408)
!2412 = !DILocation(line: 352, column: 6, scope: !1716)
!2413 = !DILocation(line: 353, column: 14, scope: !2414)
!2414 = distinct !DILexicalBlock(scope: !2415, file: !1, line: 353, column: 8)
!2415 = distinct !DILexicalBlock(scope: !2408, file: !1, line: 352, column: 35)
!2416 = !DILocation(line: 353, column: 8, scope: !2414)
!2417 = !DILocation(line: 353, column: 8, scope: !2415)
!2418 = !DILocation(line: 354, column: 13, scope: !2419)
!2419 = distinct !DILexicalBlock(scope: !2414, file: !1, line: 353, column: 31)
!2420 = !DILocation(line: 354, column: 7, scope: !2419)
!2421 = !DILocation(line: 355, column: 13, scope: !2419)
!2422 = !DILocation(line: 355, column: 47, scope: !2419)
!2423 = !DILocation(line: 355, column: 53, scope: !2419)
!2424 = !DILocation(line: 355, column: 7, scope: !2419)
!2425 = !DILocation(line: 356, column: 7, scope: !2419)
!2426 = !DILocation(line: 358, column: 53, scope: !2415)
!2427 = !DILocation(line: 358, column: 5, scope: !2415)
!2428 = !DILocation(line: 358, column: 11, scope: !2415)
!2429 = !DILocation(line: 358, column: 17, scope: !2415)
!2430 = !DILocation(line: 358, column: 29, scope: !2415)
!2431 = !DILocation(line: 359, column: 3, scope: !2415)
!2432 = !DILocation(line: 361, column: 3, scope: !1716)
!2433 = !DILocation(line: 361, column: 10, scope: !2434)
!2434 = !DILexicalBlockFile(scope: !1716, file: !1, discriminator: 1)
!2435 = !DILocation(line: 361, column: 9, scope: !2434)
!2436 = !DILocation(line: 361, column: 3, scope: !2434)
!2437 = !DILocalVariable(name: "readcount", scope: !2438, file: !1, line: 362, type: !177)
!2438 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 361, column: 18)
!2439 = !DILocation(line: 362, column: 9, scope: !2438)
!2440 = !DILocation(line: 363, column: 34, scope: !2438)
!2441 = !DILocation(line: 363, column: 14, scope: !2438)
!2442 = !DILocation(line: 363, column: 12, scope: !2438)
!2443 = !DILocation(line: 364, column: 8, scope: !2444)
!2444 = distinct !DILexicalBlock(scope: !2438, file: !1, line: 364, column: 8)
!2445 = !DILocation(line: 364, column: 8, scope: !2438)
!2446 = !DILocation(line: 365, column: 7, scope: !2444)
!2447 = !DILocation(line: 367, column: 8, scope: !2448)
!2448 = distinct !DILexicalBlock(scope: !2438, file: !1, line: 367, column: 8)
!2449 = !DILocation(line: 367, column: 18, scope: !2448)
!2450 = !DILocation(line: 367, column: 8, scope: !2438)
!2451 = !DILocation(line: 368, column: 7, scope: !2448)
!2452 = !DILocation(line: 370, column: 21, scope: !2438)
!2453 = !DILocation(line: 370, column: 13, scope: !2438)
!2454 = !DILocation(line: 370, column: 11, scope: !2438)
!2455 = !DILocation(line: 373, column: 8, scope: !2456)
!2456 = distinct !DILexicalBlock(scope: !2438, file: !1, line: 373, column: 8)
!2457 = !DILocation(line: 373, column: 14, scope: !2456)
!2458 = !DILocation(line: 373, column: 20, scope: !2456)
!2459 = !DILocation(line: 373, column: 8, scope: !2438)
!2460 = !DILocation(line: 374, column: 22, scope: !2461)
!2461 = distinct !DILexicalBlock(scope: !2462, file: !1, line: 374, column: 10)
!2462 = distinct !DILexicalBlock(scope: !2456, file: !1, line: 373, column: 33)
!2463 = !DILocation(line: 374, column: 31, scope: !2461)
!2464 = !DILocation(line: 374, column: 37, scope: !2461)
!2465 = !DILocation(line: 374, column: 43, scope: !2461)
!2466 = !DILocation(line: 374, column: 28, scope: !2461)
!2467 = !DILocation(line: 374, column: 10, scope: !2462)
!2468 = !DILocation(line: 375, column: 36, scope: !2469)
!2469 = distinct !DILexicalBlock(scope: !2461, file: !1, line: 374, column: 56)
!2470 = !DILocation(line: 375, column: 9, scope: !2469)
!2471 = !DILocation(line: 375, column: 15, scope: !2469)
!2472 = !DILocation(line: 375, column: 21, scope: !2469)
!2473 = !DILocation(line: 375, column: 33, scope: !2469)
!2474 = !DILocation(line: 376, column: 15, scope: !2469)
!2475 = !DILocation(line: 377, column: 16, scope: !2469)
!2476 = !DILocation(line: 377, column: 14, scope: !2469)
!2477 = !DILocation(line: 378, column: 7, scope: !2469)
!2478 = !DILocation(line: 380, column: 16, scope: !2479)
!2479 = distinct !DILexicalBlock(scope: !2461, file: !1, line: 379, column: 12)
!2480 = !DILocation(line: 380, column: 22, scope: !2479)
!2481 = !DILocation(line: 380, column: 28, scope: !2479)
!2482 = !DILocation(line: 380, column: 34, scope: !2479)
!2483 = !DILocation(line: 380, column: 20, scope: !2479)
!2484 = !DILocation(line: 380, column: 14, scope: !2479)
!2485 = !DILocation(line: 381, column: 26, scope: !2479)
!2486 = !DILocation(line: 381, column: 32, scope: !2479)
!2487 = !DILocation(line: 381, column: 38, scope: !2479)
!2488 = !DILocation(line: 381, column: 15, scope: !2479)
!2489 = !DILocation(line: 382, column: 9, scope: !2479)
!2490 = !DILocation(line: 382, column: 15, scope: !2479)
!2491 = !DILocation(line: 382, column: 21, scope: !2479)
!2492 = !DILocation(line: 382, column: 33, scope: !2479)
!2493 = !DILocation(line: 384, column: 5, scope: !2462)
!2494 = !DILocation(line: 386, column: 14, scope: !2456)
!2495 = !DILocation(line: 386, column: 12, scope: !2456)
!2496 = !DILocation(line: 389, column: 20, scope: !2438)
!2497 = !DILocation(line: 389, column: 24, scope: !2438)
!2498 = !DILocation(line: 389, column: 30, scope: !2438)
!2499 = !DILocation(line: 389, column: 14, scope: !2438)
!2500 = !DILocation(line: 389, column: 12, scope: !2438)
!2501 = !DILocation(line: 390, column: 8, scope: !2502)
!2502 = distinct !DILexicalBlock(scope: !2438, file: !1, line: 390, column: 8)
!2503 = !DILocation(line: 390, column: 18, scope: !2502)
!2504 = !DILocation(line: 390, column: 15, scope: !2502)
!2505 = !DILocation(line: 390, column: 8, scope: !2438)
!2506 = !DILocation(line: 391, column: 14, scope: !2507)
!2507 = distinct !DILexicalBlock(scope: !2502, file: !1, line: 390, column: 25)
!2508 = !DILocation(line: 392, column: 7, scope: !2507)
!2509 = !DILocation(line: 395, column: 18, scope: !2438)
!2510 = !DILocation(line: 395, column: 15, scope: !2438)
!2511 = !DILocation(line: 397, column: 31, scope: !2438)
!2512 = !DILocation(line: 397, column: 37, scope: !2438)
!2513 = !DILocation(line: 397, column: 5, scope: !2438)
!2514 = !DILocation(line: 399, column: 24, scope: !2515)
!2515 = distinct !DILexicalBlock(scope: !2438, file: !1, line: 399, column: 8)
!2516 = !DILocation(line: 399, column: 8, scope: !2515)
!2517 = !DILocation(line: 399, column: 8, scope: !2438)
!2518 = !DILocation(line: 400, column: 14, scope: !2515)
!2519 = !DILocation(line: 400, column: 7, scope: !2515)
!2520 = !DILocation(line: 402, column: 32, scope: !2515)
!2521 = !DILocation(line: 402, column: 16, scope: !2515)
!2522 = !DILocation(line: 402, column: 14, scope: !2515)
!2523 = !DILocation(line: 361, column: 3, scope: !2524)
!2524 = !DILexicalBlockFile(scope: !1716, file: !1, discriminator: 2)
!2525 = !DILocation(line: 404, column: 7, scope: !2526)
!2526 = distinct !DILexicalBlock(scope: !1716, file: !1, line: 404, column: 6)
!2527 = !DILocation(line: 404, column: 14, scope: !2526)
!2528 = !DILocation(line: 404, column: 33, scope: !2529)
!2529 = !DILexicalBlockFile(scope: !2526, file: !1, discriminator: 1)
!2530 = !DILocation(line: 404, column: 17, scope: !2529)
!2531 = !DILocation(line: 404, column: 6, scope: !2529)
!2532 = !DILocation(line: 405, column: 12, scope: !2526)
!2533 = !DILocation(line: 405, column: 5, scope: !2526)
!2534 = !DILocation(line: 407, column: 9, scope: !1716)
!2535 = !DILocation(line: 407, column: 3, scope: !1716)
!2536 = !DILocation(line: 409, column: 10, scope: !1716)
!2537 = !DILocation(line: 409, column: 3, scope: !1716)
!2538 = !DILocation(line: 410, column: 1, scope: !1716)
!2539 = !DILocalVariable(name: "conn", arg: 1, scope: !1717, file: !1, line: 132, type: !550)
!2540 = !DILocation(line: 132, column: 48, scope: !1717)
!2541 = !DILocalVariable(name: "from", scope: !1717, file: !1, line: 134, type: !189)
!2542 = !DILocation(line: 134, column: 14, scope: !1717)
!2543 = !DILocalVariable(name: "to", scope: !1717, file: !1, line: 134, type: !189)
!2544 = !DILocation(line: 134, column: 20, scope: !1717)
!2545 = !DILocalVariable(name: "totalsize", scope: !1717, file: !1, line: 135, type: !189)
!2546 = !DILocation(line: 135, column: 14, scope: !1717)
!2547 = !DILocalVariable(name: "ptr", scope: !1717, file: !1, line: 136, type: !215)
!2548 = !DILocation(line: 136, column: 9, scope: !1717)
!2549 = !DILocalVariable(name: "ptr2", scope: !1717, file: !1, line: 137, type: !215)
!2550 = !DILocation(line: 137, column: 9, scope: !1717)
!2551 = !DILocalVariable(name: "data", scope: !1717, file: !1, line: 138, type: !544)
!2552 = !DILocation(line: 138, column: 21, scope: !1717)
!2553 = !DILocation(line: 138, column: 28, scope: !1717)
!2554 = !DILocation(line: 138, column: 34, scope: !1717)
!2555 = !DILocation(line: 140, column: 6, scope: !2556)
!2556 = distinct !DILexicalBlock(scope: !1717, file: !1, line: 140, column: 6)
!2557 = !DILocation(line: 140, column: 12, scope: !2556)
!2558 = !DILocation(line: 140, column: 18, scope: !2556)
!2559 = !DILocation(line: 140, column: 28, scope: !2556)
!2560 = !DILocation(line: 140, column: 31, scope: !2561)
!2561 = !DILexicalBlockFile(scope: !2556, file: !1, discriminator: 1)
!2562 = !DILocation(line: 140, column: 37, scope: !2561)
!2563 = !DILocation(line: 140, column: 43, scope: !2561)
!2564 = !DILocation(line: 140, column: 6, scope: !2561)
!2565 = !DILocation(line: 141, column: 26, scope: !2566)
!2566 = distinct !DILexicalBlock(scope: !2556, file: !1, line: 140, column: 50)
!2567 = !DILocation(line: 141, column: 32, scope: !2566)
!2568 = !DILocation(line: 141, column: 38, scope: !2566)
!2569 = !DILocation(line: 141, column: 10, scope: !2566)
!2570 = !DILocation(line: 141, column: 9, scope: !2566)
!2571 = !DILocation(line: 142, column: 5, scope: !2566)
!2572 = !DILocation(line: 142, column: 12, scope: !2573)
!2573 = !DILexicalBlockFile(scope: !2566, file: !1, discriminator: 1)
!2574 = !DILocation(line: 142, column: 11, scope: !2573)
!2575 = !DILocation(line: 142, column: 16, scope: !2573)
!2576 = !DILocation(line: 142, column: 20, scope: !2577)
!2577 = !DILexicalBlockFile(scope: !2566, file: !1, discriminator: 2)
!2578 = !DILocation(line: 142, column: 34, scope: !2577)
!2579 = !DILocation(line: 142, column: 39, scope: !2580)
!2580 = !DILexicalBlockFile(scope: !2566, file: !1, discriminator: 3)
!2581 = !DILocation(line: 142, column: 38, scope: !2580)
!2582 = !DILocation(line: 142, column: 42, scope: !2580)
!2583 = !DILocation(line: 142, column: 34, scope: !2580)
!2584 = !DILocation(line: 142, column: 5, scope: !2585)
!2585 = !DILexicalBlockFile(scope: !2566, file: !1, discriminator: 4)
!2586 = !DILocation(line: 143, column: 10, scope: !2566)
!2587 = !DILocation(line: 142, column: 5, scope: !2588)
!2588 = !DILexicalBlockFile(scope: !2566, file: !1, discriminator: 5)
!2589 = !DILocation(line: 144, column: 24, scope: !2566)
!2590 = !DILocation(line: 144, column: 8, scope: !2566)
!2591 = !DILocation(line: 144, column: 7, scope: !2566)
!2592 = !DILocation(line: 145, column: 8, scope: !2593)
!2593 = distinct !DILexicalBlock(scope: !2566, file: !1, line: 145, column: 8)
!2594 = !DILocation(line: 145, column: 15, scope: !2593)
!2595 = !DILocation(line: 145, column: 12, scope: !2593)
!2596 = !DILocation(line: 145, column: 8, scope: !2566)
!2597 = !DILocation(line: 147, column: 9, scope: !2598)
!2598 = distinct !DILexicalBlock(scope: !2593, file: !1, line: 145, column: 21)
!2599 = !DILocation(line: 148, column: 5, scope: !2598)
!2600 = !DILocation(line: 149, column: 15, scope: !2601)
!2601 = distinct !DILexicalBlock(scope: !2566, file: !1, line: 149, column: 8)
!2602 = !DILocation(line: 149, column: 12, scope: !2601)
!2603 = !DILocation(line: 149, column: 19, scope: !2601)
!2604 = !DILocation(line: 149, column: 23, scope: !2605)
!2605 = !DILexicalBlockFile(scope: !2601, file: !1, discriminator: 1)
!2606 = !DILocation(line: 149, column: 27, scope: !2605)
!2607 = !DILocation(line: 149, column: 8, scope: !2605)
!2608 = !DILocation(line: 151, column: 33, scope: !2609)
!2609 = distinct !DILexicalBlock(scope: !2601, file: !1, line: 149, column: 33)
!2610 = !DILocation(line: 151, column: 7, scope: !2609)
!2611 = !DILocation(line: 151, column: 13, scope: !2609)
!2612 = !DILocation(line: 151, column: 19, scope: !2609)
!2613 = !DILocation(line: 151, column: 31, scope: !2609)
!2614 = !DILocation(line: 152, column: 7, scope: !2609)
!2615 = !DILocation(line: 152, column: 7, scope: !2616)
!2616 = !DILexicalBlockFile(scope: !2617, file: !1, discriminator: 1)
!2617 = distinct !DILexicalBlock(scope: !2609, file: !1, line: 152, column: 7)
!2618 = !DILocation(line: 154, column: 5, scope: !2609)
!2619 = !DILocation(line: 155, column: 13, scope: !2620)
!2620 = distinct !DILexicalBlock(scope: !2601, file: !1, line: 155, column: 13)
!2621 = !DILocation(line: 155, column: 18, scope: !2620)
!2622 = !DILocation(line: 155, column: 13, scope: !2601)
!2623 = !DILocation(line: 157, column: 32, scope: !2624)
!2624 = distinct !DILexicalBlock(scope: !2620, file: !1, line: 155, column: 23)
!2625 = !DILocation(line: 157, column: 31, scope: !2624)
!2626 = !DILocation(line: 157, column: 7, scope: !2624)
!2627 = !DILocation(line: 157, column: 13, scope: !2624)
!2628 = !DILocation(line: 157, column: 17, scope: !2624)
!2629 = !DILocation(line: 157, column: 29, scope: !2624)
!2630 = !DILocation(line: 158, column: 33, scope: !2624)
!2631 = !DILocation(line: 158, column: 7, scope: !2624)
!2632 = !DILocation(line: 158, column: 13, scope: !2624)
!2633 = !DILocation(line: 158, column: 19, scope: !2624)
!2634 = !DILocation(line: 158, column: 31, scope: !2624)
!2635 = !DILocation(line: 159, column: 7, scope: !2624)
!2636 = !DILocation(line: 159, column: 7, scope: !2637)
!2637 = !DILexicalBlockFile(scope: !2638, file: !1, discriminator: 1)
!2638 = distinct !DILexicalBlock(scope: !2624, file: !1, line: 159, column: 7)
!2639 = !DILocation(line: 161, column: 5, scope: !2624)
!2640 = !DILocation(line: 164, column: 19, scope: !2641)
!2641 = distinct !DILexicalBlock(scope: !2620, file: !1, line: 162, column: 10)
!2642 = !DILocation(line: 164, column: 22, scope: !2641)
!2643 = !DILocation(line: 164, column: 21, scope: !2641)
!2644 = !DILocation(line: 164, column: 17, scope: !2641)
!2645 = !DILocation(line: 165, column: 31, scope: !2641)
!2646 = !DILocation(line: 165, column: 40, scope: !2641)
!2647 = !DILocation(line: 165, column: 7, scope: !2641)
!2648 = !DILocation(line: 165, column: 13, scope: !2641)
!2649 = !DILocation(line: 165, column: 17, scope: !2641)
!2650 = !DILocation(line: 165, column: 29, scope: !2641)
!2651 = !DILocation(line: 166, column: 33, scope: !2641)
!2652 = !DILocation(line: 166, column: 7, scope: !2641)
!2653 = !DILocation(line: 166, column: 13, scope: !2641)
!2654 = !DILocation(line: 166, column: 19, scope: !2641)
!2655 = !DILocation(line: 166, column: 31, scope: !2641)
!2656 = !DILocation(line: 167, column: 7, scope: !2641)
!2657 = !DILocation(line: 167, column: 7, scope: !2658)
!2658 = !DILexicalBlockFile(scope: !2659, file: !1, discriminator: 1)
!2659 = distinct !DILexicalBlock(scope: !2641, file: !1, line: 167, column: 7)
!2660 = !DILocation(line: 171, column: 5, scope: !2566)
!2661 = !DILocation(line: 171, column: 5, scope: !2662)
!2662 = !DILexicalBlockFile(scope: !2663, file: !1, discriminator: 1)
!2663 = distinct !DILexicalBlock(scope: !2566, file: !1, line: 171, column: 5)
!2664 = !DILocation(line: 175, column: 3, scope: !2566)
!2665 = !DILocation(line: 177, column: 5, scope: !2556)
!2666 = !DILocation(line: 177, column: 11, scope: !2556)
!2667 = !DILocation(line: 177, column: 15, scope: !2556)
!2668 = !DILocation(line: 177, column: 27, scope: !2556)
!2669 = !DILocation(line: 178, column: 3, scope: !1717)
