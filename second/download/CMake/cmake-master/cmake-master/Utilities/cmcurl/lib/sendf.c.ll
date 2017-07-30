; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/sendf.c'
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
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@.str = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@Curl_cfree = external global void (i8*)*, align 8
@.str.1 = private unnamed_addr constant [17 x i8] c"Send failure: %s\00", align 1
@.str.2 = private unnamed_addr constant [17 x i8] c"Recv failure: %s\00", align 1
@.str.3 = private unnamed_addr constant [51 x i8] c"Write callback asked for PAUSE when not supported!\00", align 1
@.str.4 = private unnamed_addr constant [33 x i8] c"Failed writing body (%zu != %zu)\00", align 1
@.str.5 = private unnamed_addr constant [22 x i8] c"Failed writing header\00", align 1
@.str.6 = private unnamed_addr constant [5 x i8] c"Data\00", align 1
@.str.7 = private unnamed_addr constant [7 x i8] c"Header\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"from\00", align 1
@.str.9 = private unnamed_addr constant [3 x i8] c"to\00", align 1
@.str.10 = private unnamed_addr constant [11 x i8] c"[%s %s %s]\00", align 1
@Curl_crealloc = external global i8* (i8*, i64)*, align 8
@.str.11 = private unnamed_addr constant [3 x i8] c"\0D\0A\00", align 1
@showit.s_infotype = internal constant [7 x [3 x i8]] [[3 x i8] c"* \00", [3 x i8] c"< \00", [3 x i8] c"> \00", [3 x i8] c"{ \00", [3 x i8] c"} \00", [3 x i8] c"{ \00", [3 x i8] c"} \00"], align 16

; Function Attrs: nounwind uwtable
define zeroext i1 @Curl_recv_has_postponed_data(%struct.connectdata* %conn, i32 %sockindex) #0 !dbg !1701 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockindex.addr = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !1748, metadata !1749), !dbg !1750
  store i32 %sockindex, i32* %sockindex.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockindex.addr, metadata !1751, metadata !1749), !dbg !1752
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1753
  %1 = load i32, i32* %sockindex.addr, align 4, !dbg !1754
  ret i1 false, !dbg !1755
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define void @Curl_infof(%struct.Curl_easy* %data, i8* %fmt, ...) #0 !dbg !1705 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %fmt.addr = alloca i8*, align 8
  %ap = alloca [1 x %struct.__va_list_tag], align 16
  %len = alloca i64, align 8
  %print_buffer = alloca [2049 x i8], align 16
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !1756, metadata !1749), !dbg !1757
  store i8* %fmt, i8** %fmt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fmt.addr, metadata !1758, metadata !1749), !dbg !1759
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1760
  %tobool = icmp ne %struct.Curl_easy* %0, null, !dbg !1760
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !1762

land.lhs.true:                                    ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1763
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 13, !dbg !1765
  %verbose = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 106, !dbg !1766
  %2 = load i8, i8* %verbose, align 8, !dbg !1766
  %tobool1 = trunc i8 %2 to i1, !dbg !1766
  br i1 %tobool1, label %if.then, label %if.end, !dbg !1767

if.then:                                          ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap, metadata !1768, metadata !1749), !dbg !1781
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1782, metadata !1749), !dbg !1783
  call void @llvm.dbg.declare(metadata [2049 x i8]* %print_buffer, metadata !1784, metadata !1749), !dbg !1788
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !1789
  %arraydecay2 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1789
  call void @llvm.va_start(i8* %arraydecay2), !dbg !1789
  %arraydecay3 = getelementptr inbounds [2049 x i8], [2049 x i8]* %print_buffer, i32 0, i32 0, !dbg !1790
  %3 = load i8*, i8** %fmt.addr, align 8, !dbg !1791
  %arraydecay4 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !1792
  %call = call i32 @curl_mvsnprintf(i8* %arraydecay3, i64 2049, i8* %3, %struct.__va_list_tag* %arraydecay4), !dbg !1793
  %arraydecay5 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !1794
  %arraydecay56 = bitcast %struct.__va_list_tag* %arraydecay5 to i8*, !dbg !1794
  call void @llvm.va_end(i8* %arraydecay56), !dbg !1794
  %arraydecay7 = getelementptr inbounds [2049 x i8], [2049 x i8]* %print_buffer, i32 0, i32 0, !dbg !1795
  %call8 = call i64 @strlen(i8* %arraydecay7) #7, !dbg !1796
  store i64 %call8, i64* %len, align 8, !dbg !1797
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1798
  %arraydecay9 = getelementptr inbounds [2049 x i8], [2049 x i8]* %print_buffer, i32 0, i32 0, !dbg !1799
  %5 = load i64, i64* %len, align 8, !dbg !1800
  %call10 = call i32 @Curl_debug(%struct.Curl_easy* %4, i32 0, i8* %arraydecay9, i64 %5, %struct.connectdata* null), !dbg !1801
  br label %if.end, !dbg !1802

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  ret void, !dbg !1803
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #2

declare i32 @curl_mvsnprintf(i8*, i64, i8*, %struct.__va_list_tag*) #3

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

; Function Attrs: nounwind uwtable
define i32 @Curl_debug(%struct.Curl_easy* %data, i32 %type, i8* %ptr, i64 %size, %struct.connectdata* %conn) #0 !dbg !1728 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %type.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %conn.addr = alloca %struct.connectdata*, align 8
  %rc = alloca i32, align 4
  %buffer = alloca [160 x i8], align 16
  %t = alloca i8*, align 8
  %w = alloca i8*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !1804, metadata !1749), !dbg !1805
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !1806, metadata !1749), !dbg !1807
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !1808, metadata !1749), !dbg !1809
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !1810, metadata !1749), !dbg !1811
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !1812, metadata !1749), !dbg !1813
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !1814, metadata !1749), !dbg !1815
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1816
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 13, !dbg !1818
  %printhost = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 87, !dbg !1819
  %1 = load i8, i8* %printhost, align 8, !dbg !1819
  %tobool = trunc i8 %1 to i1, !dbg !1819
  br i1 %tobool, label %land.lhs.true, label %if.end18, !dbg !1820

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1821
  %tobool1 = icmp ne %struct.connectdata* %2, null, !dbg !1821
  br i1 %tobool1, label %land.lhs.true2, label %if.end18, !dbg !1823

land.lhs.true2:                                   ; preds = %land.lhs.true
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1824
  %host = getelementptr inbounds %struct.connectdata, %struct.connectdata* %3, i32 0, i32 12, !dbg !1826
  %dispname = getelementptr inbounds %struct.hostname, %struct.hostname* %host, i32 0, i32 3, !dbg !1827
  %4 = load i8*, i8** %dispname, align 8, !dbg !1827
  %tobool3 = icmp ne i8* %4, null, !dbg !1824
  br i1 %tobool3, label %if.then, label %if.end18, !dbg !1828

if.then:                                          ; preds = %land.lhs.true2
  call void @llvm.dbg.declare(metadata [160 x i8]* %buffer, metadata !1829, metadata !1749), !dbg !1834
  call void @llvm.dbg.declare(metadata i8** %t, metadata !1835, metadata !1749), !dbg !1836
  store i8* null, i8** %t, align 8, !dbg !1836
  call void @llvm.dbg.declare(metadata i8** %w, metadata !1837, metadata !1749), !dbg !1838
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.6, i32 0, i32 0), i8** %w, align 8, !dbg !1838
  %5 = load i32, i32* %type.addr, align 4, !dbg !1839
  switch i32 %5, label %sw.default [
    i32 1, label %sw.bb
    i32 3, label %sw.bb4
    i32 2, label %sw.bb5
    i32 4, label %sw.bb6
  ], !dbg !1840

sw.bb:                                            ; preds = %if.then
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0), i8** %w, align 8, !dbg !1841
  br label %sw.bb4, !dbg !1843

sw.bb4:                                           ; preds = %if.then, %sw.bb
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i32 0, i32 0), i8** %t, align 8, !dbg !1844
  br label %sw.epilog, !dbg !1845

sw.bb5:                                           ; preds = %if.then
  store i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0), i8** %w, align 8, !dbg !1846
  br label %sw.bb6, !dbg !1847

sw.bb6:                                           ; preds = %if.then, %sw.bb5
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.9, i32 0, i32 0), i8** %t, align 8, !dbg !1848
  br label %sw.epilog, !dbg !1849

sw.default:                                       ; preds = %if.then
  br label %sw.epilog, !dbg !1850

sw.epilog:                                        ; preds = %sw.default, %sw.bb6, %sw.bb4
  %6 = load i8*, i8** %t, align 8, !dbg !1851
  %tobool7 = icmp ne i8* %6, null, !dbg !1851
  br i1 %tobool7, label %if.then8, label %if.end17, !dbg !1853

if.then8:                                         ; preds = %sw.epilog
  %arraydecay = getelementptr inbounds [160 x i8], [160 x i8]* %buffer, i32 0, i32 0, !dbg !1854
  %7 = load i8*, i8** %w, align 8, !dbg !1856
  %8 = load i8*, i8** %t, align 8, !dbg !1857
  %9 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1858
  %host9 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %9, i32 0, i32 12, !dbg !1859
  %dispname10 = getelementptr inbounds %struct.hostname, %struct.hostname* %host9, i32 0, i32 3, !dbg !1860
  %10 = load i8*, i8** %dispname10, align 8, !dbg !1860
  %call = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %arraydecay, i64 160, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.10, i32 0, i32 0), i8* %7, i8* %8, i8* %10), !dbg !1861
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1862
  %arraydecay11 = getelementptr inbounds [160 x i8], [160 x i8]* %buffer, i32 0, i32 0, !dbg !1863
  %arraydecay12 = getelementptr inbounds [160 x i8], [160 x i8]* %buffer, i32 0, i32 0, !dbg !1864
  %call13 = call i64 @strlen(i8* %arraydecay12) #7, !dbg !1865
  %call14 = call i32 @showit(%struct.Curl_easy* %11, i32 0, i8* %arraydecay11, i64 %call13), !dbg !1866
  store i32 %call14, i32* %rc, align 4, !dbg !1868
  %12 = load i32, i32* %rc, align 4, !dbg !1869
  %tobool15 = icmp ne i32 %12, 0, !dbg !1869
  br i1 %tobool15, label %if.then16, label %if.end, !dbg !1871

if.then16:                                        ; preds = %if.then8
  %13 = load i32, i32* %rc, align 4, !dbg !1872
  store i32 %13, i32* %retval, align 4, !dbg !1873
  br label %return, !dbg !1873

if.end:                                           ; preds = %if.then8
  br label %if.end17, !dbg !1874

if.end17:                                         ; preds = %if.end, %sw.epilog
  br label %if.end18, !dbg !1875

if.end18:                                         ; preds = %if.end17, %land.lhs.true2, %land.lhs.true, %entry
  %14 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1876
  %15 = load i32, i32* %type.addr, align 4, !dbg !1877
  %16 = load i8*, i8** %ptr.addr, align 8, !dbg !1878
  %17 = load i64, i64* %size.addr, align 8, !dbg !1879
  %call19 = call i32 @showit(%struct.Curl_easy* %14, i32 %15, i8* %16, i64 %17), !dbg !1880
  store i32 %call19, i32* %rc, align 4, !dbg !1881
  %18 = load i32, i32* %rc, align 4, !dbg !1882
  store i32 %18, i32* %retval, align 4, !dbg !1883
  br label %return, !dbg !1883

return:                                           ; preds = %if.end18, %if.then16
  %19 = load i32, i32* %retval, align 4, !dbg !1884
  ret i32 %19, !dbg !1884
}

; Function Attrs: nounwind uwtable
define void @Curl_failf(%struct.Curl_easy* %data, i8* %fmt, ...) #0 !dbg !1708 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %fmt.addr = alloca i8*, align 8
  %ap = alloca [1 x %struct.__va_list_tag], align 16
  %len = alloca i64, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !1885, metadata !1749), !dbg !1886
  store i8* %fmt, i8** %fmt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fmt.addr, metadata !1887, metadata !1749), !dbg !1888
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap, metadata !1889, metadata !1749), !dbg !1890
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1891, metadata !1749), !dbg !1892
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !1893
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1893
  call void @llvm.va_start(i8* %arraydecay1), !dbg !1893
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1894
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 17, !dbg !1895
  %buffer = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 6, !dbg !1896
  %1 = load i8*, i8** %buffer, align 8, !dbg !1896
  %2 = load i8*, i8** %fmt.addr, align 8, !dbg !1897
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !1898
  %call = call i32 @curl_mvsnprintf(i8* %1, i64 16384, i8* %2, %struct.__va_list_tag* %arraydecay2), !dbg !1899
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1900
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 13, !dbg !1902
  %errorbuffer = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 2, !dbg !1903
  %4 = load i8*, i8** %errorbuffer, align 8, !dbg !1903
  %tobool = icmp ne i8* %4, null, !dbg !1900
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !1904

land.lhs.true:                                    ; preds = %entry
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1905
  %state3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %5, i32 0, i32 17, !dbg !1907
  %errorbuf = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state3, i32 0, i32 17, !dbg !1908
  %6 = load i8, i8* %errorbuf, align 8, !dbg !1908
  %tobool4 = trunc i8 %6 to i1, !dbg !1908
  br i1 %tobool4, label %if.end, label %if.then, !dbg !1909

if.then:                                          ; preds = %land.lhs.true
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1910
  %set5 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 13, !dbg !1912
  %errorbuffer6 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set5, i32 0, i32 2, !dbg !1913
  %8 = load i8*, i8** %errorbuffer6, align 8, !dbg !1913
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1914
  %state7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 17, !dbg !1915
  %buffer8 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state7, i32 0, i32 6, !dbg !1916
  %10 = load i8*, i8** %buffer8, align 8, !dbg !1916
  %call9 = call i32 (i8*, i64, i8*, ...) @curl_msnprintf(i8* %8, i64 256, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i8* %10), !dbg !1917
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1918
  %state10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 17, !dbg !1919
  %errorbuf11 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state10, i32 0, i32 17, !dbg !1920
  store i8 1, i8* %errorbuf11, align 8, !dbg !1921
  br label %if.end, !dbg !1922

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1923
  %set12 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 13, !dbg !1925
  %verbose = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set12, i32 0, i32 106, !dbg !1926
  %13 = load i8, i8* %verbose, align 8, !dbg !1926
  %tobool13 = trunc i8 %13 to i1, !dbg !1926
  br i1 %tobool13, label %if.then14, label %if.end28, !dbg !1927

if.then14:                                        ; preds = %if.end
  %14 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1928
  %state15 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %14, i32 0, i32 17, !dbg !1930
  %buffer16 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state15, i32 0, i32 6, !dbg !1931
  %15 = load i8*, i8** %buffer16, align 8, !dbg !1931
  %call17 = call i64 @strlen(i8* %15) #7, !dbg !1932
  store i64 %call17, i64* %len, align 8, !dbg !1933
  %16 = load i64, i64* %len, align 8, !dbg !1934
  %cmp = icmp ult i64 %16, 16383, !dbg !1936
  br i1 %cmp, label %if.then18, label %if.end24, !dbg !1937

if.then18:                                        ; preds = %if.then14
  %17 = load i64, i64* %len, align 8, !dbg !1938
  %18 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1940
  %state19 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %18, i32 0, i32 17, !dbg !1941
  %buffer20 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state19, i32 0, i32 6, !dbg !1942
  %19 = load i8*, i8** %buffer20, align 8, !dbg !1942
  %arrayidx = getelementptr inbounds i8, i8* %19, i64 %17, !dbg !1940
  store i8 10, i8* %arrayidx, align 1, !dbg !1943
  %20 = load i64, i64* %len, align 8, !dbg !1944
  %inc = add i64 %20, 1, !dbg !1944
  store i64 %inc, i64* %len, align 8, !dbg !1944
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1945
  %state21 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %21, i32 0, i32 17, !dbg !1946
  %buffer22 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state21, i32 0, i32 6, !dbg !1947
  %22 = load i8*, i8** %buffer22, align 8, !dbg !1947
  %arrayidx23 = getelementptr inbounds i8, i8* %22, i64 %inc, !dbg !1945
  store i8 0, i8* %arrayidx23, align 1, !dbg !1948
  br label %if.end24, !dbg !1949

if.end24:                                         ; preds = %if.then18, %if.then14
  %23 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1950
  %24 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1951
  %state25 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %24, i32 0, i32 17, !dbg !1952
  %buffer26 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state25, i32 0, i32 6, !dbg !1953
  %25 = load i8*, i8** %buffer26, align 8, !dbg !1953
  %26 = load i64, i64* %len, align 8, !dbg !1954
  %call27 = call i32 @Curl_debug(%struct.Curl_easy* %23, i32 0, i8* %25, i64 %26, %struct.connectdata* null), !dbg !1955
  br label %if.end28, !dbg !1956

if.end28:                                         ; preds = %if.end24, %if.end
  %arraydecay29 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !1957
  %arraydecay2930 = bitcast %struct.__va_list_tag* %arraydecay29 to i8*, !dbg !1957
  call void @llvm.va_end(i8* %arraydecay2930), !dbg !1957
  ret void, !dbg !1958
}

declare i32 @curl_msnprintf(i8*, i64, i8*, ...) #3

; Function Attrs: nounwind uwtable
define i32 @Curl_sendf(i32 %sockfd, %struct.connectdata* %conn, i8* %fmt, ...) #0 !dbg !1709 {
entry:
  %retval = alloca i32, align 4
  %sockfd.addr = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %fmt.addr = alloca i8*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %bytes_written = alloca i64, align 8
  %write_len = alloca i64, align 8
  %result = alloca i32, align 4
  %s = alloca i8*, align 8
  %sptr = alloca i8*, align 8
  %ap = alloca [1 x %struct.__va_list_tag], align 16
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !1959, metadata !1749), !dbg !1960
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !1961, metadata !1749), !dbg !1962
  store i8* %fmt, i8** %fmt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fmt.addr, metadata !1963, metadata !1749), !dbg !1964
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !1965, metadata !1749), !dbg !1966
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1967
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !1968
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !1968
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !1966
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !1969, metadata !1749), !dbg !1970
  call void @llvm.dbg.declare(metadata i64* %write_len, metadata !1971, metadata !1749), !dbg !1972
  call void @llvm.dbg.declare(metadata i32* %result, metadata !1973, metadata !1749), !dbg !1974
  store i32 0, i32* %result, align 4, !dbg !1974
  call void @llvm.dbg.declare(metadata i8** %s, metadata !1975, metadata !1749), !dbg !1976
  call void @llvm.dbg.declare(metadata i8** %sptr, metadata !1977, metadata !1749), !dbg !1978
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %ap, metadata !1979, metadata !1749), !dbg !1980
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !1981
  %arraydecay2 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !1981
  call void @llvm.va_start(i8* %arraydecay2), !dbg !1981
  %2 = load i8*, i8** %fmt.addr, align 8, !dbg !1982
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !1983
  %call = call i8* @curl_mvaprintf(i8* %2, %struct.__va_list_tag* %arraydecay3), !dbg !1984
  store i8* %call, i8** %s, align 8, !dbg !1985
  %arraydecay4 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %ap, i32 0, i32 0, !dbg !1986
  %arraydecay45 = bitcast %struct.__va_list_tag* %arraydecay4 to i8*, !dbg !1986
  call void @llvm.va_end(i8* %arraydecay45), !dbg !1986
  %3 = load i8*, i8** %s, align 8, !dbg !1987
  %tobool = icmp ne i8* %3, null, !dbg !1987
  br i1 %tobool, label %if.end, label %if.then, !dbg !1989

if.then:                                          ; preds = %entry
  store i32 27, i32* %retval, align 4, !dbg !1990
  br label %return, !dbg !1990

if.end:                                           ; preds = %entry
  store i64 0, i64* %bytes_written, align 8, !dbg !1991
  %4 = load i8*, i8** %s, align 8, !dbg !1992
  %call6 = call i64 @strlen(i8* %4) #7, !dbg !1993
  store i64 %call6, i64* %write_len, align 8, !dbg !1994
  %5 = load i8*, i8** %s, align 8, !dbg !1995
  store i8* %5, i8** %sptr, align 8, !dbg !1996
  br label %for.cond, !dbg !1997

for.cond:                                         ; preds = %if.end16, %if.end
  %6 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1998
  %7 = load i32, i32* %sockfd.addr, align 4, !dbg !2002
  %8 = load i8*, i8** %sptr, align 8, !dbg !2003
  %9 = load i64, i64* %write_len, align 8, !dbg !2004
  %call7 = call i32 @Curl_write(%struct.connectdata* %6, i32 %7, i8* %8, i64 %9, i64* %bytes_written), !dbg !2005
  store i32 %call7, i32* %result, align 4, !dbg !2006
  %10 = load i32, i32* %result, align 4, !dbg !2007
  %tobool8 = icmp ne i32 %10, 0, !dbg !2007
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !2009

if.then9:                                         ; preds = %for.cond
  br label %for.end, !dbg !2010

if.end10:                                         ; preds = %for.cond
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2011
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 13, !dbg !2013
  %verbose = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 106, !dbg !2014
  %12 = load i8, i8* %verbose, align 8, !dbg !2014
  %tobool11 = trunc i8 %12 to i1, !dbg !2014
  br i1 %tobool11, label %if.then12, label %if.end14, !dbg !2015

if.then12:                                        ; preds = %if.end10
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2016
  %14 = load i8*, i8** %sptr, align 8, !dbg !2017
  %15 = load i64, i64* %bytes_written, align 8, !dbg !2018
  %16 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2019
  %call13 = call i32 @Curl_debug(%struct.Curl_easy* %13, i32 4, i8* %14, i64 %15, %struct.connectdata* %16), !dbg !2020
  br label %if.end14, !dbg !2020

if.end14:                                         ; preds = %if.then12, %if.end10
  %17 = load i64, i64* %bytes_written, align 8, !dbg !2021
  %18 = load i64, i64* %write_len, align 8, !dbg !2023
  %cmp = icmp ne i64 %17, %18, !dbg !2024
  br i1 %cmp, label %if.then15, label %if.else, !dbg !2025

if.then15:                                        ; preds = %if.end14
  %19 = load i64, i64* %bytes_written, align 8, !dbg !2026
  %20 = load i64, i64* %write_len, align 8, !dbg !2028
  %sub = sub i64 %20, %19, !dbg !2028
  store i64 %sub, i64* %write_len, align 8, !dbg !2028
  %21 = load i64, i64* %bytes_written, align 8, !dbg !2029
  %22 = load i8*, i8** %sptr, align 8, !dbg !2030
  %add.ptr = getelementptr inbounds i8, i8* %22, i64 %21, !dbg !2030
  store i8* %add.ptr, i8** %sptr, align 8, !dbg !2030
  br label %if.end16, !dbg !2031

if.else:                                          ; preds = %if.end14
  br label %for.end, !dbg !2032

if.end16:                                         ; preds = %if.then15
  br label %for.cond, !dbg !2033

for.end:                                          ; preds = %if.else, %if.then9
  %23 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2035
  %24 = load i8*, i8** %s, align 8, !dbg !2035
  call void %23(i8* %24), !dbg !2035
  %25 = load i32, i32* %result, align 4, !dbg !2036
  store i32 %25, i32* %retval, align 4, !dbg !2037
  br label %return, !dbg !2037

return:                                           ; preds = %for.end, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !2038
  ret i32 %26, !dbg !2038
}

declare i8* @curl_mvaprintf(i8*, %struct.__va_list_tag*) #3

; Function Attrs: nounwind uwtable
define i32 @Curl_write(%struct.connectdata* %conn, i32 %sockfd, i8* %mem, i64 %len, i64* %written) #0 !dbg !1712 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockfd.addr = alloca i32, align 4
  %mem.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %written.addr = alloca i64*, align 8
  %bytes_written = alloca i64, align 8
  %result = alloca i32, align 4
  %num = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2039, metadata !1749), !dbg !2040
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !2041, metadata !1749), !dbg !2042
  store i8* %mem, i8** %mem.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %mem.addr, metadata !2043, metadata !1749), !dbg !2044
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2045, metadata !1749), !dbg !2046
  store i64* %written, i64** %written.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %written.addr, metadata !2047, metadata !1749), !dbg !2048
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !2049, metadata !1749), !dbg !2050
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2051, metadata !1749), !dbg !2052
  store i32 0, i32* %result, align 4, !dbg !2052
  call void @llvm.dbg.declare(metadata i32* %num, metadata !2053, metadata !1749), !dbg !2054
  %0 = load i32, i32* %sockfd.addr, align 4, !dbg !2055
  %1 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2056
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %1, i32 0, i32 33, !dbg !2057
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 1, !dbg !2056
  %2 = load i32, i32* %arrayidx, align 4, !dbg !2056
  %cmp = icmp eq i32 %0, %2, !dbg !2058
  %conv = zext i1 %cmp to i32, !dbg !2058
  store i32 %conv, i32* %num, align 4, !dbg !2054
  %3 = load i32, i32* %num, align 4, !dbg !2059
  %idxprom = sext i32 %3 to i64, !dbg !2060
  %4 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2060
  %send = getelementptr inbounds %struct.connectdata, %struct.connectdata* %4, i32 0, i32 37, !dbg !2061
  %arrayidx1 = getelementptr inbounds [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*]* %send, i64 0, i64 %idxprom, !dbg !2060
  %5 = load i64 (%struct.connectdata*, i32, i8*, i64, i32*)*, i64 (%struct.connectdata*, i32, i8*, i64, i32*)** %arrayidx1, align 8, !dbg !2060
  %6 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2062
  %7 = load i32, i32* %num, align 4, !dbg !2063
  %8 = load i8*, i8** %mem.addr, align 8, !dbg !2064
  %9 = load i64, i64* %len.addr, align 8, !dbg !2065
  %call = call i64 %5(%struct.connectdata* %6, i32 %7, i8* %8, i64 %9, i32* %result), !dbg !2060
  store i64 %call, i64* %bytes_written, align 8, !dbg !2066
  %10 = load i64, i64* %bytes_written, align 8, !dbg !2067
  %11 = load i64*, i64** %written.addr, align 8, !dbg !2068
  store i64 %10, i64* %11, align 8, !dbg !2069
  %12 = load i64, i64* %bytes_written, align 8, !dbg !2070
  %cmp2 = icmp sge i64 %12, 0, !dbg !2072
  br i1 %cmp2, label %if.then, label %if.end, !dbg !2073

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2074
  br label %return, !dbg !2074

if.end:                                           ; preds = %entry
  %13 = load i32, i32* %result, align 4, !dbg !2075
  switch i32 %13, label %sw.default [
    i32 81, label %sw.bb
    i32 0, label %sw.bb4
  ], !dbg !2076

sw.bb:                                            ; preds = %if.end
  %14 = load i64*, i64** %written.addr, align 8, !dbg !2077
  store i64 0, i64* %14, align 8, !dbg !2079
  store i32 0, i32* %retval, align 4, !dbg !2080
  br label %return, !dbg !2080

sw.bb4:                                           ; preds = %if.end
  store i32 55, i32* %retval, align 4, !dbg !2081
  br label %return, !dbg !2081

sw.default:                                       ; preds = %if.end
  %15 = load i32, i32* %result, align 4, !dbg !2082
  store i32 %15, i32* %retval, align 4, !dbg !2083
  br label %return, !dbg !2083

return:                                           ; preds = %sw.default, %sw.bb4, %sw.bb, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !2084
  ret i32 %16, !dbg !2084
}

; Function Attrs: nounwind uwtable
define i64 @Curl_send_plain(%struct.connectdata* %conn, i32 %num, i8* %mem, i64 %len, i32* %code) #0 !dbg !1715 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %num.addr = alloca i32, align 4
  %mem.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %code.addr = alloca i32*, align 8
  %sockfd = alloca i32, align 4
  %bytes_written = alloca i64, align 8
  %err = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2085, metadata !1749), !dbg !2086
  store i32 %num, i32* %num.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %num.addr, metadata !2087, metadata !1749), !dbg !2088
  store i8* %mem, i8** %mem.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %mem.addr, metadata !2089, metadata !1749), !dbg !2090
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2091, metadata !1749), !dbg !2092
  store i32* %code, i32** %code.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %code.addr, metadata !2093, metadata !1749), !dbg !2094
  call void @llvm.dbg.declare(metadata i32* %sockfd, metadata !2095, metadata !1749), !dbg !2096
  %0 = load i32, i32* %num.addr, align 4, !dbg !2097
  %idxprom = sext i32 %0 to i64, !dbg !2098
  %1 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2098
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %1, i32 0, i32 33, !dbg !2099
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 %idxprom, !dbg !2098
  %2 = load i32, i32* %arrayidx, align 4, !dbg !2098
  store i32 %2, i32* %sockfd, align 4, !dbg !2096
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !2100, metadata !1749), !dbg !2101
  br label %do.body, !dbg !2102

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !2103

do.end:                                           ; preds = %do.body
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2106
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %3, i32 0, i32 43, !dbg !2108
  %tcp_fastopen = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 28, !dbg !2109
  %4 = load i8, i8* %tcp_fastopen, align 1, !dbg !2109
  %tobool = trunc i8 %4 to i1, !dbg !2109
  br i1 %tobool, label %if.then, label %if.else, !dbg !2110

if.then:                                          ; preds = %do.end
  %5 = load i32, i32* %sockfd, align 4, !dbg !2111
  %6 = load i8*, i8** %mem.addr, align 8, !dbg !2113
  %7 = load i64, i64* %len.addr, align 8, !dbg !2114
  %8 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2115
  %ip_addr = getelementptr inbounds %struct.connectdata, %struct.connectdata* %8, i32 0, i32 7, !dbg !2116
  %9 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ip_addr, align 8, !dbg !2116
  %ai_addr = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %9, i32 0, i32 6, !dbg !2117
  %10 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr, align 8, !dbg !2117
  %11 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2118
  %ip_addr1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %11, i32 0, i32 7, !dbg !2119
  %12 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ip_addr1, align 8, !dbg !2119
  %ai_addrlen = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %12, i32 0, i32 4, !dbg !2120
  %13 = load i32, i32* %ai_addrlen, align 8, !dbg !2120
  %call = call i64 @sendto(i32 %5, i8* %6, i64 %7, i32 536870912, %struct.sockaddr* %10, i32 %13), !dbg !2121
  store i64 %call, i64* %bytes_written, align 8, !dbg !2122
  %14 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2123
  %bits2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %14, i32 0, i32 43, !dbg !2124
  %tcp_fastopen3 = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits2, i32 0, i32 28, !dbg !2125
  store i8 0, i8* %tcp_fastopen3, align 1, !dbg !2126
  br label %if.end, !dbg !2127

if.else:                                          ; preds = %do.end
  %15 = load i32, i32* %sockfd, align 4, !dbg !2128
  %16 = load i8*, i8** %mem.addr, align 8, !dbg !2128
  %17 = load i64, i64* %len.addr, align 8, !dbg !2128
  %call4 = call i64 @send(i32 %15, i8* %16, i64 %17, i32 16384), !dbg !2128
  store i64 %call4, i64* %bytes_written, align 8, !dbg !2129
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %18 = load i32*, i32** %code.addr, align 8, !dbg !2130
  store i32 0, i32* %18, align 4, !dbg !2131
  %19 = load i64, i64* %bytes_written, align 8, !dbg !2132
  %cmp = icmp eq i64 -1, %19, !dbg !2134
  br i1 %cmp, label %if.then5, label %if.end18, !dbg !2135

if.then5:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2136, metadata !1749), !dbg !2138
  %call6 = call i32* @__errno_location() #1, !dbg !2139
  %20 = load i32, i32* %call6, align 4, !dbg !2139
  store i32 %20, i32* %err, align 4, !dbg !2138
  %21 = load i32, i32* %err, align 4, !dbg !2140
  %cmp7 = icmp eq i32 11, %21, !dbg !2142
  br i1 %cmp7, label %if.then13, label %lor.lhs.false, !dbg !2143

lor.lhs.false:                                    ; preds = %if.then5
  %22 = load i32, i32* %err, align 4, !dbg !2144
  %cmp8 = icmp eq i32 11, %22, !dbg !2146
  br i1 %cmp8, label %if.then13, label %lor.lhs.false9, !dbg !2147

lor.lhs.false9:                                   ; preds = %lor.lhs.false
  %23 = load i32, i32* %err, align 4, !dbg !2148
  %cmp10 = icmp eq i32 4, %23, !dbg !2150
  br i1 %cmp10, label %if.then13, label %lor.lhs.false11, !dbg !2151

lor.lhs.false11:                                  ; preds = %lor.lhs.false9
  %24 = load i32, i32* %err, align 4, !dbg !2152
  %cmp12 = icmp eq i32 115, %24, !dbg !2153
  br i1 %cmp12, label %if.then13, label %if.else14, !dbg !2154

if.then13:                                        ; preds = %lor.lhs.false11, %lor.lhs.false9, %lor.lhs.false, %if.then5
  store i64 0, i64* %bytes_written, align 8, !dbg !2156
  %25 = load i32*, i32** %code.addr, align 8, !dbg !2158
  store i32 81, i32* %25, align 4, !dbg !2159
  br label %if.end17, !dbg !2160

if.else14:                                        ; preds = %lor.lhs.false11
  %26 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2161
  %data = getelementptr inbounds %struct.connectdata, %struct.connectdata* %26, i32 0, i32 0, !dbg !2163
  %27 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2163
  %28 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2164
  %29 = load i32, i32* %err, align 4, !dbg !2165
  %call15 = call i8* @Curl_strerror(%struct.connectdata* %28, i32 %29), !dbg !2166
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %27, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.1, i32 0, i32 0), i8* %call15), !dbg !2167
  %30 = load i32, i32* %err, align 4, !dbg !2168
  %31 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2169
  %data16 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %31, i32 0, i32 0, !dbg !2170
  %32 = load %struct.Curl_easy*, %struct.Curl_easy** %data16, align 8, !dbg !2170
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %32, i32 0, i32 17, !dbg !2171
  %os_errno = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 18, !dbg !2172
  store i32 %30, i32* %os_errno, align 4, !dbg !2173
  %33 = load i32*, i32** %code.addr, align 8, !dbg !2174
  store i32 55, i32* %33, align 4, !dbg !2175
  br label %if.end17

if.end17:                                         ; preds = %if.else14, %if.then13
  br label %if.end18, !dbg !2176

if.end18:                                         ; preds = %if.end17, %if.end
  %34 = load i64, i64* %bytes_written, align 8, !dbg !2177
  ret i64 %34, !dbg !2178
}

declare i64 @sendto(i32, i8*, i64, i32, %struct.sockaddr*, i32) #3

declare i64 @send(i32, i8*, i64, i32) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare i8* @Curl_strerror(%struct.connectdata*, i32) #3

; Function Attrs: nounwind uwtable
define i32 @Curl_write_plain(%struct.connectdata* %conn, i32 %sockfd, i8* %mem, i64 %len, i64* %written) #0 !dbg !1716 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockfd.addr = alloca i32, align 4
  %mem.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %written.addr = alloca i64*, align 8
  %bytes_written = alloca i64, align 8
  %result = alloca i32, align 4
  %num = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2179, metadata !1749), !dbg !2180
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !2181, metadata !1749), !dbg !2182
  store i8* %mem, i8** %mem.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %mem.addr, metadata !2183, metadata !1749), !dbg !2184
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2185, metadata !1749), !dbg !2186
  store i64* %written, i64** %written.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %written.addr, metadata !2187, metadata !1749), !dbg !2188
  call void @llvm.dbg.declare(metadata i64* %bytes_written, metadata !2189, metadata !1749), !dbg !2190
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2191, metadata !1749), !dbg !2192
  call void @llvm.dbg.declare(metadata i32* %num, metadata !2193, metadata !1749), !dbg !2194
  %0 = load i32, i32* %sockfd.addr, align 4, !dbg !2195
  %1 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2196
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %1, i32 0, i32 33, !dbg !2197
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 1, !dbg !2196
  %2 = load i32, i32* %arrayidx, align 4, !dbg !2196
  %cmp = icmp eq i32 %0, %2, !dbg !2198
  %conv = zext i1 %cmp to i32, !dbg !2198
  store i32 %conv, i32* %num, align 4, !dbg !2194
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2199
  %4 = load i32, i32* %num, align 4, !dbg !2200
  %5 = load i8*, i8** %mem.addr, align 8, !dbg !2201
  %6 = load i64, i64* %len.addr, align 8, !dbg !2202
  %call = call i64 @Curl_send_plain(%struct.connectdata* %3, i32 %4, i8* %5, i64 %6, i32* %result), !dbg !2203
  store i64 %call, i64* %bytes_written, align 8, !dbg !2204
  %7 = load i64, i64* %bytes_written, align 8, !dbg !2205
  %8 = load i64*, i64** %written.addr, align 8, !dbg !2206
  store i64 %7, i64* %8, align 8, !dbg !2207
  %9 = load i32, i32* %result, align 4, !dbg !2208
  ret i32 %9, !dbg !2209
}

; Function Attrs: nounwind uwtable
define i64 @Curl_recv_plain(%struct.connectdata* %conn, i32 %num, i8* %buf, i64 %len, i32* %code) #0 !dbg !1717 {
entry:
  %retval = alloca i64, align 8
  %conn.addr = alloca %struct.connectdata*, align 8
  %num.addr = alloca i32, align 4
  %buf.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %code.addr = alloca i32*, align 8
  %sockfd = alloca i32, align 4
  %nread = alloca i64, align 8
  %err = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2210, metadata !1749), !dbg !2211
  store i32 %num, i32* %num.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %num.addr, metadata !2212, metadata !1749), !dbg !2213
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !2214, metadata !1749), !dbg !2215
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2216, metadata !1749), !dbg !2217
  store i32* %code, i32** %code.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %code.addr, metadata !2218, metadata !1749), !dbg !2219
  call void @llvm.dbg.declare(metadata i32* %sockfd, metadata !2220, metadata !1749), !dbg !2221
  %0 = load i32, i32* %num.addr, align 4, !dbg !2222
  %idxprom = sext i32 %0 to i64, !dbg !2223
  %1 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2223
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %1, i32 0, i32 33, !dbg !2224
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 %idxprom, !dbg !2223
  %2 = load i32, i32* %arrayidx, align 4, !dbg !2223
  store i32 %2, i32* %sockfd, align 4, !dbg !2221
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !2225, metadata !1749), !dbg !2226
  store i64 0, i64* %nread, align 8, !dbg !2227
  %3 = load i64, i64* %nread, align 8, !dbg !2228
  %cmp = icmp sgt i64 %3, 0, !dbg !2230
  br i1 %cmp, label %if.then, label %if.end, !dbg !2231

if.then:                                          ; preds = %entry
  %4 = load i32*, i32** %code.addr, align 8, !dbg !2232
  store i32 0, i32* %4, align 4, !dbg !2234
  %5 = load i64, i64* %nread, align 8, !dbg !2235
  store i64 %5, i64* %retval, align 8, !dbg !2236
  br label %return, !dbg !2236

if.end:                                           ; preds = %entry
  %6 = load i32, i32* %sockfd, align 4, !dbg !2237
  %7 = load i8*, i8** %buf.addr, align 8, !dbg !2237
  %8 = load i64, i64* %len.addr, align 8, !dbg !2237
  %call = call i64 @recv(i32 %6, i8* %7, i64 %8, i32 0), !dbg !2237
  store i64 %call, i64* %nread, align 8, !dbg !2238
  %9 = load i32*, i32** %code.addr, align 8, !dbg !2239
  store i32 0, i32* %9, align 4, !dbg !2240
  %10 = load i64, i64* %nread, align 8, !dbg !2241
  %cmp1 = icmp eq i64 -1, %10, !dbg !2243
  br i1 %cmp1, label %if.then2, label %if.end12, !dbg !2244

if.then2:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2245, metadata !1749), !dbg !2247
  %call3 = call i32* @__errno_location() #1, !dbg !2248
  %11 = load i32, i32* %call3, align 4, !dbg !2248
  store i32 %11, i32* %err, align 4, !dbg !2247
  %12 = load i32, i32* %err, align 4, !dbg !2249
  %cmp4 = icmp eq i32 11, %12, !dbg !2251
  br i1 %cmp4, label %if.then8, label %lor.lhs.false, !dbg !2252

lor.lhs.false:                                    ; preds = %if.then2
  %13 = load i32, i32* %err, align 4, !dbg !2253
  %cmp5 = icmp eq i32 11, %13, !dbg !2255
  br i1 %cmp5, label %if.then8, label %lor.lhs.false6, !dbg !2256

lor.lhs.false6:                                   ; preds = %lor.lhs.false
  %14 = load i32, i32* %err, align 4, !dbg !2257
  %cmp7 = icmp eq i32 4, %14, !dbg !2259
  br i1 %cmp7, label %if.then8, label %if.else, !dbg !2260

if.then8:                                         ; preds = %lor.lhs.false6, %lor.lhs.false, %if.then2
  %15 = load i32*, i32** %code.addr, align 8, !dbg !2261
  store i32 81, i32* %15, align 4, !dbg !2263
  br label %if.end11, !dbg !2264

if.else:                                          ; preds = %lor.lhs.false6
  %16 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2265
  %data = getelementptr inbounds %struct.connectdata, %struct.connectdata* %16, i32 0, i32 0, !dbg !2267
  %17 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2267
  %18 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2268
  %19 = load i32, i32* %err, align 4, !dbg !2269
  %call9 = call i8* @Curl_strerror(%struct.connectdata* %18, i32 %19), !dbg !2270
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %17, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.2, i32 0, i32 0), i8* %call9), !dbg !2271
  %20 = load i32, i32* %err, align 4, !dbg !2272
  %21 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2273
  %data10 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %21, i32 0, i32 0, !dbg !2274
  %22 = load %struct.Curl_easy*, %struct.Curl_easy** %data10, align 8, !dbg !2274
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %22, i32 0, i32 17, !dbg !2275
  %os_errno = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 18, !dbg !2276
  store i32 %20, i32* %os_errno, align 4, !dbg !2277
  %23 = load i32*, i32** %code.addr, align 8, !dbg !2278
  store i32 56, i32* %23, align 4, !dbg !2279
  br label %if.end11

if.end11:                                         ; preds = %if.else, %if.then8
  br label %if.end12, !dbg !2280

if.end12:                                         ; preds = %if.end11, %if.end
  %24 = load i64, i64* %nread, align 8, !dbg !2281
  store i64 %24, i64* %retval, align 8, !dbg !2282
  br label %return, !dbg !2282

return:                                           ; preds = %if.end12, %if.then
  %25 = load i64, i64* %retval, align 8, !dbg !2283
  ret i64 %25, !dbg !2283
}

declare i64 @recv(i32, i8*, i64, i32) #3

; Function Attrs: nounwind uwtable
define i32 @Curl_client_chop_write(%struct.connectdata* %conn, i32 %type, i8* %ptr, i64 %len) #0 !dbg !1718 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %type.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %writeheader = alloca i64 (i8*, i64, i64, i8*)*, align 8
  %writebody = alloca i64 (i8*, i64, i64, i8*)*, align 8
  %chunklen = alloca i64, align 8
  %wrote = alloca i64, align 8
  %wrote48 = alloca i64, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2284, metadata !1749), !dbg !2285
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !2286, metadata !1749), !dbg !2287
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !2288, metadata !1749), !dbg !2289
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2290, metadata !1749), !dbg !2291
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2292, metadata !1749), !dbg !2293
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2294
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2295
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2295
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2293
  call void @llvm.dbg.declare(metadata i64 (i8*, i64, i64, i8*)** %writeheader, metadata !2296, metadata !1749), !dbg !2297
  store i64 (i8*, i64, i64, i8*)* null, i64 (i8*, i64, i64, i8*)** %writeheader, align 8, !dbg !2297
  call void @llvm.dbg.declare(metadata i64 (i8*, i64, i64, i8*)** %writebody, metadata !2298, metadata !1749), !dbg !2299
  store i64 (i8*, i64, i64, i8*)* null, i64 (i8*, i64, i64, i8*)** %writebody, align 8, !dbg !2299
  %2 = load i64, i64* %len.addr, align 8, !dbg !2300
  %tobool = icmp ne i64 %2, 0, !dbg !2300
  br i1 %tobool, label %if.end, label %if.then, !dbg !2302

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2303
  br label %return, !dbg !2303

if.end:                                           ; preds = %entry
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2304
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 12, !dbg !2306
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %req, i32 0, i32 31, !dbg !2307
  %4 = load i32, i32* %keepon, align 4, !dbg !2307
  %and = and i32 %4, 16, !dbg !2308
  %tobool2 = icmp ne i32 %and, 0, !dbg !2308
  br i1 %tobool2, label %if.then3, label %if.end4, !dbg !2309

if.then3:                                         ; preds = %if.end
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2310
  %6 = load i32, i32* %type.addr, align 4, !dbg !2311
  %7 = load i8*, i8** %ptr.addr, align 8, !dbg !2312
  %8 = load i64, i64* %len.addr, align 8, !dbg !2313
  %call = call i32 @pausewrite(%struct.Curl_easy* %5, i32 %6, i8* %7, i64 %8), !dbg !2314
  store i32 %call, i32* %retval, align 4, !dbg !2315
  br label %return, !dbg !2315

if.end4:                                          ; preds = %if.end
  %9 = load i32, i32* %type.addr, align 4, !dbg !2316
  %and5 = and i32 %9, 1, !dbg !2318
  %tobool6 = icmp ne i32 %and5, 0, !dbg !2318
  br i1 %tobool6, label %if.then7, label %if.end8, !dbg !2319

if.then7:                                         ; preds = %if.end4
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2320
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 13, !dbg !2321
  %fwrite_func = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 20, !dbg !2322
  %11 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %fwrite_func, align 8, !dbg !2322
  store i64 (i8*, i64, i64, i8*)* %11, i64 (i8*, i64, i64, i8*)** %writebody, align 8, !dbg !2323
  br label %if.end8, !dbg !2324

if.end8:                                          ; preds = %if.then7, %if.end4
  %12 = load i32, i32* %type.addr, align 4, !dbg !2325
  %and9 = and i32 %12, 2, !dbg !2327
  %tobool10 = icmp ne i32 %and9, 0, !dbg !2327
  br i1 %tobool10, label %land.lhs.true, label %if.end24, !dbg !2328

land.lhs.true:                                    ; preds = %if.end8
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2329
  %set11 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 13, !dbg !2330
  %fwrite_header = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set11, i32 0, i32 21, !dbg !2331
  %14 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %fwrite_header, align 8, !dbg !2331
  %tobool12 = icmp ne i64 (i8*, i64, i64, i8*)* %14, null, !dbg !2329
  br i1 %tobool12, label %if.then16, label %lor.lhs.false, !dbg !2332

lor.lhs.false:                                    ; preds = %land.lhs.true
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2333
  %set13 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 13, !dbg !2335
  %writeheader14 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set13, i32 0, i32 6, !dbg !2336
  %16 = load i8*, i8** %writeheader14, align 8, !dbg !2336
  %tobool15 = icmp ne i8* %16, null, !dbg !2333
  br i1 %tobool15, label %if.then16, label %if.end24, !dbg !2337

if.then16:                                        ; preds = %lor.lhs.false, %land.lhs.true
  %17 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2339
  %set17 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %17, i32 0, i32 13, !dbg !2341
  %fwrite_header18 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set17, i32 0, i32 21, !dbg !2342
  %18 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %fwrite_header18, align 8, !dbg !2342
  %tobool19 = icmp ne i64 (i8*, i64, i64, i8*)* %18, null, !dbg !2339
  br i1 %tobool19, label %cond.true, label %cond.false, !dbg !2339

cond.true:                                        ; preds = %if.then16
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2343
  %set20 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %19, i32 0, i32 13, !dbg !2345
  %fwrite_header21 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set20, i32 0, i32 21, !dbg !2346
  %20 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %fwrite_header21, align 8, !dbg !2346
  br label %cond.end, !dbg !2347

cond.false:                                       ; preds = %if.then16
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2348
  %set22 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %21, i32 0, i32 13, !dbg !2350
  %fwrite_func23 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set22, i32 0, i32 20, !dbg !2351
  %22 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %fwrite_func23, align 8, !dbg !2351
  br label %cond.end, !dbg !2352

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 (i8*, i64, i64, i8*)* [ %20, %cond.true ], [ %22, %cond.false ], !dbg !2353
  store i64 (i8*, i64, i64, i8*)* %cond, i64 (i8*, i64, i64, i8*)** %writeheader, align 8, !dbg !2355
  br label %if.end24, !dbg !2356

if.end24:                                         ; preds = %cond.end, %lor.lhs.false, %if.end8
  br label %while.cond, !dbg !2357

while.cond:                                       ; preds = %if.end59, %if.end24
  %23 = load i64, i64* %len.addr, align 8, !dbg !2358
  %tobool25 = icmp ne i64 %23, 0, !dbg !2359
  br i1 %tobool25, label %while.body, label %while.end, !dbg !2359

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i64* %chunklen, metadata !2360, metadata !1749), !dbg !2362
  %24 = load i64, i64* %len.addr, align 8, !dbg !2363
  %cmp = icmp ule i64 %24, 16384, !dbg !2364
  br i1 %cmp, label %cond.true26, label %cond.false27, !dbg !2363

cond.true26:                                      ; preds = %while.body
  %25 = load i64, i64* %len.addr, align 8, !dbg !2365
  br label %cond.end28, !dbg !2367

cond.false27:                                     ; preds = %while.body
  br label %cond.end28, !dbg !2368

cond.end28:                                       ; preds = %cond.false27, %cond.true26
  %cond29 = phi i64 [ %25, %cond.true26 ], [ 16384, %cond.false27 ], !dbg !2370
  store i64 %cond29, i64* %chunklen, align 8, !dbg !2372
  %26 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %writebody, align 8, !dbg !2373
  %tobool30 = icmp ne i64 (i8*, i64, i64, i8*)* %26, null, !dbg !2373
  br i1 %tobool30, label %if.then31, label %if.end45, !dbg !2375

if.then31:                                        ; preds = %cond.end28
  call void @llvm.dbg.declare(metadata i64* %wrote, metadata !2376, metadata !1749), !dbg !2378
  %27 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %writebody, align 8, !dbg !2379
  %28 = load i8*, i8** %ptr.addr, align 8, !dbg !2380
  %29 = load i64, i64* %chunklen, align 8, !dbg !2381
  %30 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2382
  %set32 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %30, i32 0, i32 13, !dbg !2383
  %out = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set32, i32 0, i32 4, !dbg !2384
  %31 = load i8*, i8** %out, align 8, !dbg !2384
  %call33 = call i64 %27(i8* %28, i64 1, i64 %29, i8* %31), !dbg !2379
  store i64 %call33, i64* %wrote, align 8, !dbg !2378
  %32 = load i64, i64* %wrote, align 8, !dbg !2385
  %cmp34 = icmp eq i64 268435457, %32, !dbg !2387
  br i1 %cmp34, label %if.then35, label %if.end41, !dbg !2388

if.then35:                                        ; preds = %if.then31
  %33 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2389
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %33, i32 0, i32 47, !dbg !2392
  %34 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !2392
  %flags = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %34, i32 0, i32 16, !dbg !2393
  %35 = load i32, i32* %flags, align 4, !dbg !2393
  %and36 = and i32 %35, 16, !dbg !2394
  %tobool37 = icmp ne i32 %and36, 0, !dbg !2394
  br i1 %tobool37, label %if.then38, label %if.end39, !dbg !2395

if.then38:                                        ; preds = %if.then35
  %36 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2396
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %36, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.3, i32 0, i32 0)), !dbg !2398
  store i32 23, i32* %retval, align 4, !dbg !2399
  br label %return, !dbg !2399

if.end39:                                         ; preds = %if.then35
  %37 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2400
  %38 = load i32, i32* %type.addr, align 4, !dbg !2401
  %39 = load i8*, i8** %ptr.addr, align 8, !dbg !2402
  %40 = load i64, i64* %len.addr, align 8, !dbg !2403
  %call40 = call i32 @pausewrite(%struct.Curl_easy* %37, i32 %38, i8* %39, i64 %40), !dbg !2404
  store i32 %call40, i32* %retval, align 4, !dbg !2405
  br label %return, !dbg !2405

if.end41:                                         ; preds = %if.then31
  %41 = load i64, i64* %wrote, align 8, !dbg !2406
  %42 = load i64, i64* %chunklen, align 8, !dbg !2408
  %cmp42 = icmp ne i64 %41, %42, !dbg !2409
  br i1 %cmp42, label %if.then43, label %if.end44, !dbg !2410

if.then43:                                        ; preds = %if.end41
  %43 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2411
  %44 = load i64, i64* %wrote, align 8, !dbg !2413
  %45 = load i64, i64* %chunklen, align 8, !dbg !2414
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %43, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.4, i32 0, i32 0), i64 %44, i64 %45), !dbg !2415
  store i32 23, i32* %retval, align 4, !dbg !2416
  br label %return, !dbg !2416

if.end44:                                         ; preds = %if.end41
  br label %if.end45, !dbg !2417

if.end45:                                         ; preds = %if.end44, %cond.end28
  %46 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %writeheader, align 8, !dbg !2418
  %tobool46 = icmp ne i64 (i8*, i64, i64, i8*)* %46, null, !dbg !2418
  br i1 %tobool46, label %if.then47, label %if.end59, !dbg !2420

if.then47:                                        ; preds = %if.end45
  call void @llvm.dbg.declare(metadata i64* %wrote48, metadata !2421, metadata !1749), !dbg !2423
  %47 = load i64 (i8*, i64, i64, i8*)*, i64 (i8*, i64, i64, i8*)** %writeheader, align 8, !dbg !2424
  %48 = load i8*, i8** %ptr.addr, align 8, !dbg !2425
  %49 = load i64, i64* %chunklen, align 8, !dbg !2426
  %50 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2427
  %set49 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %50, i32 0, i32 13, !dbg !2428
  %writeheader50 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set49, i32 0, i32 6, !dbg !2429
  %51 = load i8*, i8** %writeheader50, align 8, !dbg !2429
  %call51 = call i64 %47(i8* %48, i64 1, i64 %49, i8* %51), !dbg !2424
  store i64 %call51, i64* %wrote48, align 8, !dbg !2423
  %52 = load i64, i64* %wrote48, align 8, !dbg !2430
  %cmp52 = icmp eq i64 268435457, %52, !dbg !2432
  br i1 %cmp52, label %if.then53, label %if.end55, !dbg !2433

if.then53:                                        ; preds = %if.then47
  %53 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2434
  %54 = load i8*, i8** %ptr.addr, align 8, !dbg !2435
  %55 = load i64, i64* %len.addr, align 8, !dbg !2436
  %call54 = call i32 @pausewrite(%struct.Curl_easy* %53, i32 2, i8* %54, i64 %55), !dbg !2437
  store i32 %call54, i32* %retval, align 4, !dbg !2438
  br label %return, !dbg !2438

if.end55:                                         ; preds = %if.then47
  %56 = load i64, i64* %wrote48, align 8, !dbg !2439
  %57 = load i64, i64* %chunklen, align 8, !dbg !2441
  %cmp56 = icmp ne i64 %56, %57, !dbg !2442
  br i1 %cmp56, label %if.then57, label %if.end58, !dbg !2443

if.then57:                                        ; preds = %if.end55
  %58 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2444
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %58, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.5, i32 0, i32 0)), !dbg !2446
  store i32 23, i32* %retval, align 4, !dbg !2447
  br label %return, !dbg !2447

if.end58:                                         ; preds = %if.end55
  br label %if.end59, !dbg !2448

if.end59:                                         ; preds = %if.end58, %if.end45
  %59 = load i64, i64* %chunklen, align 8, !dbg !2449
  %60 = load i8*, i8** %ptr.addr, align 8, !dbg !2450
  %add.ptr = getelementptr inbounds i8, i8* %60, i64 %59, !dbg !2450
  store i8* %add.ptr, i8** %ptr.addr, align 8, !dbg !2450
  %61 = load i64, i64* %chunklen, align 8, !dbg !2451
  %62 = load i64, i64* %len.addr, align 8, !dbg !2452
  %sub = sub i64 %62, %61, !dbg !2452
  store i64 %sub, i64* %len.addr, align 8, !dbg !2452
  br label %while.cond, !dbg !2453

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !2455
  br label %return, !dbg !2455

return:                                           ; preds = %while.end, %if.then57, %if.then53, %if.then43, %if.end39, %if.then38, %if.then3, %if.then
  %63 = load i32, i32* %retval, align 4, !dbg !2456
  ret i32 %63, !dbg !2456
}

; Function Attrs: nounwind uwtable
define internal i32 @pausewrite(%struct.Curl_easy* %data, i32 %type, i8* %ptr, i64 %len) #0 !dbg !1731 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %type.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %k = alloca %struct.SingleRequest*, align 8
  %s = alloca %struct.UrlState*, align 8
  %dupl = alloca i8*, align 8
  %i = alloca i32, align 4
  %newtype = alloca i8, align 1
  %newlen = alloca i64, align 8
  %newptr = alloca i8*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2457, metadata !1749), !dbg !2458
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !2459, metadata !1749), !dbg !2460
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !2461, metadata !1749), !dbg !2462
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2463, metadata !1749), !dbg !2464
  call void @llvm.dbg.declare(metadata %struct.SingleRequest** %k, metadata !2465, metadata !1749), !dbg !2467
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2468
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 12, !dbg !2469
  store %struct.SingleRequest* %req, %struct.SingleRequest** %k, align 8, !dbg !2467
  call void @llvm.dbg.declare(metadata %struct.UrlState** %s, metadata !2470, metadata !1749), !dbg !2472
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2473
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 17, !dbg !2474
  store %struct.UrlState* %state, %struct.UrlState** %s, align 8, !dbg !2472
  call void @llvm.dbg.declare(metadata i8** %dupl, metadata !2475, metadata !1749), !dbg !2476
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2477, metadata !1749), !dbg !2478
  call void @llvm.dbg.declare(metadata i8* %newtype, metadata !2479, metadata !1749), !dbg !2480
  store i8 1, i8* %newtype, align 1, !dbg !2480
  %2 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2481
  %tempcount = getelementptr inbounds %struct.UrlState, %struct.UrlState* %2, i32 0, i32 14, !dbg !2483
  %3 = load i32, i32* %tempcount, align 8, !dbg !2483
  %tobool = icmp ne i32 %3, 0, !dbg !2481
  br i1 %tobool, label %if.then, label %if.else, !dbg !2484

if.then:                                          ; preds = %entry
  store i32 0, i32* %i, align 4, !dbg !2485
  br label %for.cond, !dbg !2488

for.cond:                                         ; preds = %for.inc, %if.then
  %4 = load i32, i32* %i, align 4, !dbg !2489
  %5 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2492
  %tempcount1 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %5, i32 0, i32 14, !dbg !2493
  %6 = load i32, i32* %tempcount1, align 8, !dbg !2493
  %cmp = icmp ult i32 %4, %6, !dbg !2494
  br i1 %cmp, label %for.body, label %for.end, !dbg !2495

for.body:                                         ; preds = %for.cond
  %7 = load i32, i32* %i, align 4, !dbg !2496
  %idxprom = zext i32 %7 to i64, !dbg !2499
  %8 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2499
  %tempwrite = getelementptr inbounds %struct.UrlState, %struct.UrlState* %8, i32 0, i32 15, !dbg !2500
  %arrayidx = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite, i64 0, i64 %idxprom, !dbg !2499
  %type2 = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx, i32 0, i32 2, !dbg !2501
  %9 = load i32, i32* %type2, align 8, !dbg !2501
  %10 = load i32, i32* %type.addr, align 4, !dbg !2502
  %cmp3 = icmp eq i32 %9, %10, !dbg !2503
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !2504

if.then4:                                         ; preds = %for.body
  store i8 0, i8* %newtype, align 1, !dbg !2505
  br label %for.end, !dbg !2507

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !2508

for.inc:                                          ; preds = %if.end
  %11 = load i32, i32* %i, align 4, !dbg !2509
  %inc = add i32 %11, 1, !dbg !2509
  store i32 %inc, i32* %i, align 4, !dbg !2509
  br label %for.cond, !dbg !2511

for.end:                                          ; preds = %if.then4, %for.cond
  br label %do.body, !dbg !2512

do.body:                                          ; preds = %for.end
  br label %do.end, !dbg !2513

do.end:                                           ; preds = %do.body
  br label %if.end5, !dbg !2516

if.else:                                          ; preds = %entry
  store i32 0, i32* %i, align 4, !dbg !2517
  br label %if.end5

if.end5:                                          ; preds = %if.else, %do.end
  %12 = load i8, i8* %newtype, align 1, !dbg !2518
  %tobool6 = trunc i8 %12 to i1, !dbg !2518
  br i1 %tobool6, label %if.else30, label %if.then7, !dbg !2520

if.then7:                                         ; preds = %if.end5
  call void @llvm.dbg.declare(metadata i64* %newlen, metadata !2521, metadata !1749), !dbg !2523
  %13 = load i64, i64* %len.addr, align 8, !dbg !2524
  %14 = load i32, i32* %i, align 4, !dbg !2525
  %idxprom8 = zext i32 %14 to i64, !dbg !2526
  %15 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2526
  %tempwrite9 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %15, i32 0, i32 15, !dbg !2527
  %arrayidx10 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite9, i64 0, i64 %idxprom8, !dbg !2526
  %len11 = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx10, i32 0, i32 1, !dbg !2528
  %16 = load i64, i64* %len11, align 8, !dbg !2528
  %add = add i64 %13, %16, !dbg !2529
  store i64 %add, i64* %newlen, align 8, !dbg !2523
  call void @llvm.dbg.declare(metadata i8** %newptr, metadata !2530, metadata !1749), !dbg !2531
  %17 = load i8* (i8*, i64)*, i8* (i8*, i64)** @Curl_crealloc, align 8, !dbg !2532
  %18 = load i32, i32* %i, align 4, !dbg !2532
  %idxprom12 = zext i32 %18 to i64, !dbg !2532
  %19 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2532
  %tempwrite13 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %19, i32 0, i32 15, !dbg !2532
  %arrayidx14 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite13, i64 0, i64 %idxprom12, !dbg !2532
  %buf = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx14, i32 0, i32 0, !dbg !2532
  %20 = load i8*, i8** %buf, align 8, !dbg !2532
  %21 = load i64, i64* %newlen, align 8, !dbg !2532
  %call = call i8* %17(i8* %20, i64 %21), !dbg !2532
  store i8* %call, i8** %newptr, align 8, !dbg !2531
  %22 = load i8*, i8** %newptr, align 8, !dbg !2533
  %tobool15 = icmp ne i8* %22, null, !dbg !2533
  br i1 %tobool15, label %if.end17, label %if.then16, !dbg !2535

if.then16:                                        ; preds = %if.then7
  store i32 27, i32* %retval, align 4, !dbg !2536
  br label %return, !dbg !2536

if.end17:                                         ; preds = %if.then7
  %23 = load i8*, i8** %newptr, align 8, !dbg !2537
  %24 = load i32, i32* %i, align 4, !dbg !2538
  %idxprom18 = zext i32 %24 to i64, !dbg !2539
  %25 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2539
  %tempwrite19 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %25, i32 0, i32 15, !dbg !2540
  %arrayidx20 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite19, i64 0, i64 %idxprom18, !dbg !2539
  %len21 = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx20, i32 0, i32 1, !dbg !2541
  %26 = load i64, i64* %len21, align 8, !dbg !2541
  %add.ptr = getelementptr inbounds i8, i8* %23, i64 %26, !dbg !2542
  %27 = load i8*, i8** %ptr.addr, align 8, !dbg !2543
  %28 = load i64, i64* %len.addr, align 8, !dbg !2544
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %add.ptr, i8* %27, i64 %28, i32 1, i1 false), !dbg !2545
  %29 = load i8*, i8** %newptr, align 8, !dbg !2546
  %30 = load i32, i32* %i, align 4, !dbg !2547
  %idxprom22 = zext i32 %30 to i64, !dbg !2548
  %31 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2548
  %tempwrite23 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %31, i32 0, i32 15, !dbg !2549
  %arrayidx24 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite23, i64 0, i64 %idxprom22, !dbg !2548
  %buf25 = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx24, i32 0, i32 0, !dbg !2550
  store i8* %29, i8** %buf25, align 8, !dbg !2551
  %32 = load i64, i64* %newlen, align 8, !dbg !2552
  %33 = load i32, i32* %i, align 4, !dbg !2553
  %idxprom26 = zext i32 %33 to i64, !dbg !2554
  %34 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2554
  %tempwrite27 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %34, i32 0, i32 15, !dbg !2555
  %arrayidx28 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite27, i64 0, i64 %idxprom26, !dbg !2554
  %len29 = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx28, i32 0, i32 1, !dbg !2556
  store i64 %32, i64* %len29, align 8, !dbg !2557
  br label %if.end52, !dbg !2558

if.else30:                                        ; preds = %if.end5
  %35 = load i8*, i8** %ptr.addr, align 8, !dbg !2559
  %36 = load i64, i64* %len.addr, align 8, !dbg !2561
  %call31 = call i8* @Curl_memdup(i8* %35, i64 %36), !dbg !2562
  store i8* %call31, i8** %dupl, align 8, !dbg !2563
  %37 = load i8*, i8** %dupl, align 8, !dbg !2564
  %tobool32 = icmp ne i8* %37, null, !dbg !2564
  br i1 %tobool32, label %if.end34, label %if.then33, !dbg !2566

if.then33:                                        ; preds = %if.else30
  store i32 27, i32* %retval, align 4, !dbg !2567
  br label %return, !dbg !2567

if.end34:                                         ; preds = %if.else30
  %38 = load i8*, i8** %dupl, align 8, !dbg !2568
  %39 = load i32, i32* %i, align 4, !dbg !2569
  %idxprom35 = zext i32 %39 to i64, !dbg !2570
  %40 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2570
  %tempwrite36 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %40, i32 0, i32 15, !dbg !2571
  %arrayidx37 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite36, i64 0, i64 %idxprom35, !dbg !2570
  %buf38 = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx37, i32 0, i32 0, !dbg !2572
  store i8* %38, i8** %buf38, align 8, !dbg !2573
  %41 = load i64, i64* %len.addr, align 8, !dbg !2574
  %42 = load i32, i32* %i, align 4, !dbg !2575
  %idxprom39 = zext i32 %42 to i64, !dbg !2576
  %43 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2576
  %tempwrite40 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %43, i32 0, i32 15, !dbg !2577
  %arrayidx41 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite40, i64 0, i64 %idxprom39, !dbg !2576
  %len42 = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx41, i32 0, i32 1, !dbg !2578
  store i64 %41, i64* %len42, align 8, !dbg !2579
  %44 = load i32, i32* %type.addr, align 4, !dbg !2580
  %45 = load i32, i32* %i, align 4, !dbg !2581
  %idxprom43 = zext i32 %45 to i64, !dbg !2582
  %46 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2582
  %tempwrite44 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %46, i32 0, i32 15, !dbg !2583
  %arrayidx45 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite44, i64 0, i64 %idxprom43, !dbg !2582
  %type46 = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx45, i32 0, i32 2, !dbg !2584
  store i32 %44, i32* %type46, align 8, !dbg !2585
  %47 = load i8, i8* %newtype, align 1, !dbg !2586
  %tobool47 = trunc i8 %47 to i1, !dbg !2586
  br i1 %tobool47, label %if.then48, label %if.end51, !dbg !2588

if.then48:                                        ; preds = %if.end34
  %48 = load %struct.UrlState*, %struct.UrlState** %s, align 8, !dbg !2589
  %tempcount49 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %48, i32 0, i32 14, !dbg !2590
  %49 = load i32, i32* %tempcount49, align 8, !dbg !2591
  %inc50 = add i32 %49, 1, !dbg !2591
  store i32 %inc50, i32* %tempcount49, align 8, !dbg !2591
  br label %if.end51, !dbg !2589

if.end51:                                         ; preds = %if.then48, %if.end34
  br label %if.end52

if.end52:                                         ; preds = %if.end51, %if.end17
  %50 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2592
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %50, i32 0, i32 31, !dbg !2593
  %51 = load i32, i32* %keepon, align 4, !dbg !2594
  %or = or i32 %51, 16, !dbg !2594
  store i32 %or, i32* %keepon, align 4, !dbg !2594
  br label %do.body53, !dbg !2595

do.body53:                                        ; preds = %if.end52
  br label %do.end54, !dbg !2596

do.end54:                                         ; preds = %do.body53
  store i32 0, i32* %retval, align 4, !dbg !2599
  br label %return, !dbg !2599

return:                                           ; preds = %do.end54, %if.then33, %if.then16
  %52 = load i32, i32* %retval, align 4, !dbg !2600
  ret i32 %52, !dbg !2600
}

; Function Attrs: nounwind uwtable
define i32 @Curl_client_write(%struct.connectdata* %conn, i32 %type, i8* %ptr, i64 %len) #0 !dbg !1721 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %type.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %result = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2601, metadata !1749), !dbg !2602
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !2603, metadata !1749), !dbg !2604
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !2605, metadata !1749), !dbg !2606
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !2607, metadata !1749), !dbg !2608
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2609, metadata !1749), !dbg !2610
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2611
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2612
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2612
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2610
  %2 = load i64, i64* %len.addr, align 8, !dbg !2613
  %cmp = icmp eq i64 0, %2, !dbg !2615
  br i1 %cmp, label %if.then, label %if.end, !dbg !2616

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %ptr.addr, align 8, !dbg !2617
  %call = call i64 @strlen(i8* %3) #7, !dbg !2618
  store i64 %call, i64* %len.addr, align 8, !dbg !2619
  br label %if.end, !dbg !2620

if.end:                                           ; preds = %if.then, %entry
  br label %do.body, !dbg !2621

do.body:                                          ; preds = %if.end
  br label %do.end, !dbg !2622

do.end:                                           ; preds = %do.body
  %4 = load i32, i32* %type.addr, align 4, !dbg !2625
  %and = and i32 %4, 1, !dbg !2627
  %tobool = icmp ne i32 %and, 0, !dbg !2627
  br i1 %tobool, label %land.lhs.true, label %if.end12, !dbg !2628

land.lhs.true:                                    ; preds = %do.end
  %5 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2629
  %handler = getelementptr inbounds %struct.connectdata, %struct.connectdata* %5, i32 0, i32 47, !dbg !2630
  %6 = load %struct.Curl_handler*, %struct.Curl_handler** %handler, align 8, !dbg !2630
  %protocol = getelementptr inbounds %struct.Curl_handler, %struct.Curl_handler* %6, i32 0, i32 15, !dbg !2631
  %7 = load i32, i32* %protocol, align 8, !dbg !2631
  %and2 = and i32 %7, 12, !dbg !2632
  %tobool3 = icmp ne i32 %and2, 0, !dbg !2632
  br i1 %tobool3, label %land.lhs.true4, label %if.end12, !dbg !2633

land.lhs.true4:                                   ; preds = %land.lhs.true
  %8 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2634
  %proto = getelementptr inbounds %struct.connectdata, %struct.connectdata* %8, i32 0, i32 66, !dbg !2635
  %ftpc = bitcast %union.anon.0* %proto to %struct.ftp_conn*, !dbg !2636
  %transfertype = getelementptr inbounds %struct.ftp_conn, %struct.ftp_conn* %ftpc, i32 0, i32 12, !dbg !2637
  %9 = load i8, i8* %transfertype, align 8, !dbg !2637
  %conv = sext i8 %9 to i32, !dbg !2634
  %cmp5 = icmp eq i32 %conv, 65, !dbg !2638
  br i1 %cmp5, label %if.then7, label %if.end12, !dbg !2639

if.then7:                                         ; preds = %land.lhs.true4
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2641, metadata !1749), !dbg !2643
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2644
  store i32 0, i32* %result, align 4, !dbg !2643
  %11 = load i32, i32* %result, align 4, !dbg !2645
  %tobool8 = icmp ne i32 %11, 0, !dbg !2645
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !2647

if.then9:                                         ; preds = %if.then7
  %12 = load i32, i32* %result, align 4, !dbg !2648
  store i32 %12, i32* %retval, align 4, !dbg !2649
  br label %return, !dbg !2649

if.end10:                                         ; preds = %if.then7
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2650
  %14 = load i8*, i8** %ptr.addr, align 8, !dbg !2651
  %15 = load i64, i64* %len.addr, align 8, !dbg !2652
  %call11 = call i64 @convert_lineends(%struct.Curl_easy* %13, i8* %14, i64 %15), !dbg !2653
  store i64 %call11, i64* %len.addr, align 8, !dbg !2654
  br label %if.end12, !dbg !2655

if.end12:                                         ; preds = %if.end10, %land.lhs.true4, %land.lhs.true, %do.end
  %16 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2656
  %17 = load i32, i32* %type.addr, align 4, !dbg !2657
  %18 = load i8*, i8** %ptr.addr, align 8, !dbg !2658
  %19 = load i64, i64* %len.addr, align 8, !dbg !2659
  %call13 = call i32 @Curl_client_chop_write(%struct.connectdata* %16, i32 %17, i8* %18, i64 %19), !dbg !2660
  store i32 %call13, i32* %retval, align 4, !dbg !2661
  br label %return, !dbg !2661

return:                                           ; preds = %if.end12, %if.then9
  %20 = load i32, i32* %retval, align 4, !dbg !2662
  ret i32 %20, !dbg !2662
}

; Function Attrs: nounwind uwtable
define internal i64 @convert_lineends(%struct.Curl_easy* %data, i8* %startPtr, i64 %size) #0 !dbg !1734 {
entry:
  %retval = alloca i64, align 8
  %data.addr = alloca %struct.Curl_easy*, align 8
  %startPtr.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  %inPtr = alloca i8*, align 8
  %outPtr = alloca i8*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2663, metadata !1749), !dbg !2664
  store i8* %startPtr, i8** %startPtr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %startPtr.addr, metadata !2665, metadata !1749), !dbg !2666
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !2667, metadata !1749), !dbg !2668
  call void @llvm.dbg.declare(metadata i8** %inPtr, metadata !2669, metadata !1749), !dbg !2670
  call void @llvm.dbg.declare(metadata i8** %outPtr, metadata !2671, metadata !1749), !dbg !2672
  %0 = load i8*, i8** %startPtr.addr, align 8, !dbg !2673
  %cmp = icmp eq i8* %0, null, !dbg !2675
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2676

lor.lhs.false:                                    ; preds = %entry
  %1 = load i64, i64* %size.addr, align 8, !dbg !2677
  %cmp1 = icmp ult i64 %1, 1, !dbg !2679
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2680

if.then:                                          ; preds = %lor.lhs.false, %entry
  %2 = load i64, i64* %size.addr, align 8, !dbg !2681
  store i64 %2, i64* %retval, align 8, !dbg !2683
  br label %return, !dbg !2683

if.end:                                           ; preds = %lor.lhs.false
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2684
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 17, !dbg !2686
  %prev_block_had_trailing_cr = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 35, !dbg !2687
  %4 = load i8, i8* %prev_block_had_trailing_cr, align 2, !dbg !2687
  %tobool = trunc i8 %4 to i1, !dbg !2687
  br i1 %tobool, label %if.then2, label %if.end10, !dbg !2688

if.then2:                                         ; preds = %if.end
  %5 = load i8*, i8** %startPtr.addr, align 8, !dbg !2689
  %6 = load i8, i8* %5, align 1, !dbg !2692
  %conv = sext i8 %6 to i32, !dbg !2692
  %cmp3 = icmp eq i32 %conv, 10, !dbg !2693
  br i1 %cmp3, label %if.then5, label %if.end7, !dbg !2694

if.then5:                                         ; preds = %if.then2
  %7 = load i8*, i8** %startPtr.addr, align 8, !dbg !2695
  %8 = load i8*, i8** %startPtr.addr, align 8, !dbg !2697
  %add.ptr = getelementptr inbounds i8, i8* %8, i64 1, !dbg !2698
  %9 = load i64, i64* %size.addr, align 8, !dbg !2699
  %sub = sub i64 %9, 1, !dbg !2700
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %7, i8* %add.ptr, i64 %sub, i32 1, i1 false), !dbg !2701
  %10 = load i64, i64* %size.addr, align 8, !dbg !2702
  %dec = add i64 %10, -1, !dbg !2702
  store i64 %dec, i64* %size.addr, align 8, !dbg !2702
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2703
  %state6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 17, !dbg !2704
  %crlf_conversions = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state6, i32 0, i32 36, !dbg !2705
  %12 = load i64, i64* %crlf_conversions, align 8, !dbg !2706
  %inc = add nsw i64 %12, 1, !dbg !2706
  store i64 %inc, i64* %crlf_conversions, align 8, !dbg !2706
  br label %if.end7, !dbg !2707

if.end7:                                          ; preds = %if.then5, %if.then2
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2708
  %state8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 17, !dbg !2709
  %prev_block_had_trailing_cr9 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state8, i32 0, i32 35, !dbg !2710
  store i8 0, i8* %prev_block_had_trailing_cr9, align 2, !dbg !2711
  br label %if.end10, !dbg !2712

if.end10:                                         ; preds = %if.end7, %if.end
  %14 = load i8*, i8** %startPtr.addr, align 8, !dbg !2713
  %15 = load i64, i64* %size.addr, align 8, !dbg !2714
  %call = call i8* @memchr(i8* %14, i32 13, i64 %15) #7, !dbg !2715
  store i8* %call, i8** %outPtr, align 8, !dbg !2716
  store i8* %call, i8** %inPtr, align 8, !dbg !2717
  %16 = load i8*, i8** %inPtr, align 8, !dbg !2718
  %tobool11 = icmp ne i8* %16, null, !dbg !2718
  br i1 %tobool11, label %if.then12, label %if.end52, !dbg !2720

if.then12:                                        ; preds = %if.end10
  br label %while.cond, !dbg !2721

while.cond:                                       ; preds = %if.end30, %if.then12
  %17 = load i8*, i8** %inPtr, align 8, !dbg !2723
  %18 = load i8*, i8** %startPtr.addr, align 8, !dbg !2725
  %19 = load i64, i64* %size.addr, align 8, !dbg !2726
  %add.ptr13 = getelementptr inbounds i8, i8* %18, i64 %19, !dbg !2727
  %add.ptr14 = getelementptr inbounds i8, i8* %add.ptr13, i64 -1, !dbg !2728
  %cmp15 = icmp ult i8* %17, %add.ptr14, !dbg !2729
  br i1 %cmp15, label %while.body, label %while.end, !dbg !2730

while.body:                                       ; preds = %while.cond
  %20 = load i8*, i8** %inPtr, align 8, !dbg !2731
  %call17 = call i32 @memcmp(i8* %20, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i32 0, i32 0), i64 2) #7, !dbg !2734
  %cmp18 = icmp eq i32 %call17, 0, !dbg !2735
  br i1 %cmp18, label %if.then20, label %if.else, !dbg !2736

if.then20:                                        ; preds = %while.body
  %21 = load i8*, i8** %inPtr, align 8, !dbg !2737
  %incdec.ptr = getelementptr inbounds i8, i8* %21, i32 1, !dbg !2737
  store i8* %incdec.ptr, i8** %inPtr, align 8, !dbg !2737
  %22 = load i8*, i8** %inPtr, align 8, !dbg !2739
  %23 = load i8, i8* %22, align 1, !dbg !2740
  %24 = load i8*, i8** %outPtr, align 8, !dbg !2741
  store i8 %23, i8* %24, align 1, !dbg !2742
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2743
  %state21 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 17, !dbg !2744
  %crlf_conversions22 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state21, i32 0, i32 36, !dbg !2745
  %26 = load i64, i64* %crlf_conversions22, align 8, !dbg !2746
  %inc23 = add nsw i64 %26, 1, !dbg !2746
  store i64 %inc23, i64* %crlf_conversions22, align 8, !dbg !2746
  br label %if.end30, !dbg !2747

if.else:                                          ; preds = %while.body
  %27 = load i8*, i8** %inPtr, align 8, !dbg !2748
  %28 = load i8, i8* %27, align 1, !dbg !2751
  %conv24 = sext i8 %28 to i32, !dbg !2751
  %cmp25 = icmp eq i32 %conv24, 13, !dbg !2752
  br i1 %cmp25, label %if.then27, label %if.else28, !dbg !2753

if.then27:                                        ; preds = %if.else
  %29 = load i8*, i8** %outPtr, align 8, !dbg !2754
  store i8 10, i8* %29, align 1, !dbg !2756
  br label %if.end29, !dbg !2757

if.else28:                                        ; preds = %if.else
  %30 = load i8*, i8** %inPtr, align 8, !dbg !2758
  %31 = load i8, i8* %30, align 1, !dbg !2760
  %32 = load i8*, i8** %outPtr, align 8, !dbg !2761
  store i8 %31, i8* %32, align 1, !dbg !2762
  br label %if.end29

if.end29:                                         ; preds = %if.else28, %if.then27
  br label %if.end30

if.end30:                                         ; preds = %if.end29, %if.then20
  %33 = load i8*, i8** %outPtr, align 8, !dbg !2763
  %incdec.ptr31 = getelementptr inbounds i8, i8* %33, i32 1, !dbg !2763
  store i8* %incdec.ptr31, i8** %outPtr, align 8, !dbg !2763
  %34 = load i8*, i8** %inPtr, align 8, !dbg !2764
  %incdec.ptr32 = getelementptr inbounds i8, i8* %34, i32 1, !dbg !2764
  store i8* %incdec.ptr32, i8** %inPtr, align 8, !dbg !2764
  br label %while.cond, !dbg !2765

while.end:                                        ; preds = %while.cond
  %35 = load i8*, i8** %inPtr, align 8, !dbg !2767
  %36 = load i8*, i8** %startPtr.addr, align 8, !dbg !2769
  %37 = load i64, i64* %size.addr, align 8, !dbg !2770
  %add.ptr33 = getelementptr inbounds i8, i8* %36, i64 %37, !dbg !2771
  %cmp34 = icmp ult i8* %35, %add.ptr33, !dbg !2772
  br i1 %cmp34, label %if.then36, label %if.end46, !dbg !2773

if.then36:                                        ; preds = %while.end
  %38 = load i8*, i8** %inPtr, align 8, !dbg !2774
  %39 = load i8, i8* %38, align 1, !dbg !2777
  %conv37 = sext i8 %39 to i32, !dbg !2777
  %cmp38 = icmp eq i32 %conv37, 13, !dbg !2778
  br i1 %cmp38, label %if.then40, label %if.else43, !dbg !2779

if.then40:                                        ; preds = %if.then36
  %40 = load i8*, i8** %outPtr, align 8, !dbg !2780
  store i8 10, i8* %40, align 1, !dbg !2782
  %41 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2783
  %state41 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %41, i32 0, i32 17, !dbg !2784
  %prev_block_had_trailing_cr42 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state41, i32 0, i32 35, !dbg !2785
  store i8 1, i8* %prev_block_had_trailing_cr42, align 2, !dbg !2786
  br label %if.end44, !dbg !2787

if.else43:                                        ; preds = %if.then36
  %42 = load i8*, i8** %inPtr, align 8, !dbg !2788
  %43 = load i8, i8* %42, align 1, !dbg !2790
  %44 = load i8*, i8** %outPtr, align 8, !dbg !2791
  store i8 %43, i8* %44, align 1, !dbg !2792
  br label %if.end44

if.end44:                                         ; preds = %if.else43, %if.then40
  %45 = load i8*, i8** %outPtr, align 8, !dbg !2793
  %incdec.ptr45 = getelementptr inbounds i8, i8* %45, i32 1, !dbg !2793
  store i8* %incdec.ptr45, i8** %outPtr, align 8, !dbg !2793
  br label %if.end46, !dbg !2794

if.end46:                                         ; preds = %if.end44, %while.end
  %46 = load i8*, i8** %outPtr, align 8, !dbg !2795
  %47 = load i8*, i8** %startPtr.addr, align 8, !dbg !2797
  %48 = load i64, i64* %size.addr, align 8, !dbg !2798
  %add.ptr47 = getelementptr inbounds i8, i8* %47, i64 %48, !dbg !2799
  %cmp48 = icmp ult i8* %46, %add.ptr47, !dbg !2800
  br i1 %cmp48, label %if.then50, label %if.end51, !dbg !2801

if.then50:                                        ; preds = %if.end46
  %49 = load i8*, i8** %outPtr, align 8, !dbg !2802
  store i8 0, i8* %49, align 1, !dbg !2803
  br label %if.end51, !dbg !2804

if.end51:                                         ; preds = %if.then50, %if.end46
  %50 = load i8*, i8** %outPtr, align 8, !dbg !2805
  %51 = load i8*, i8** %startPtr.addr, align 8, !dbg !2806
  %sub.ptr.lhs.cast = ptrtoint i8* %50 to i64, !dbg !2807
  %sub.ptr.rhs.cast = ptrtoint i8* %51 to i64, !dbg !2807
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2807
  store i64 %sub.ptr.sub, i64* %retval, align 8, !dbg !2808
  br label %return, !dbg !2808

if.end52:                                         ; preds = %if.end10
  %52 = load i64, i64* %size.addr, align 8, !dbg !2809
  store i64 %52, i64* %retval, align 8, !dbg !2810
  br label %return, !dbg !2810

return:                                           ; preds = %if.end52, %if.end51, %if.then
  %53 = load i64, i64* %retval, align 8, !dbg !2811
  ret i64 %53, !dbg !2811
}

; Function Attrs: nounwind uwtable
define i32 @Curl_read_plain(i32 %sockfd, i8* %buf, i64 %bytesfromsocket, i64* %n) #0 !dbg !1722 {
entry:
  %retval = alloca i32, align 4
  %sockfd.addr = alloca i32, align 4
  %buf.addr = alloca i8*, align 8
  %bytesfromsocket.addr = alloca i64, align 8
  %n.addr = alloca i64*, align 8
  %nread = alloca i64, align 8
  %err = alloca i32, align 4
  %return_error = alloca i32, align 4
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !2812, metadata !1749), !dbg !2813
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !2814, metadata !1749), !dbg !2815
  store i64 %bytesfromsocket, i64* %bytesfromsocket.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bytesfromsocket.addr, metadata !2816, metadata !1749), !dbg !2817
  store i64* %n, i64** %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %n.addr, metadata !2818, metadata !1749), !dbg !2819
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !2820, metadata !1749), !dbg !2821
  %0 = load i32, i32* %sockfd.addr, align 4, !dbg !2822
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !2822
  %2 = load i64, i64* %bytesfromsocket.addr, align 8, !dbg !2822
  %call = call i64 @recv(i32 %0, i8* %1, i64 %2, i32 0), !dbg !2822
  store i64 %call, i64* %nread, align 8, !dbg !2821
  %3 = load i64, i64* %nread, align 8, !dbg !2823
  %cmp = icmp eq i64 -1, %3, !dbg !2825
  br i1 %cmp, label %if.then, label %if.end6, !dbg !2826

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %err, metadata !2827, metadata !1749), !dbg !2829
  %call1 = call i32* @__errno_location() #1, !dbg !2830
  %4 = load i32, i32* %call1, align 4, !dbg !2830
  store i32 %4, i32* %err, align 4, !dbg !2829
  call void @llvm.dbg.declare(metadata i32* %return_error, metadata !2831, metadata !1749), !dbg !2832
  %5 = load i32, i32* %err, align 4, !dbg !2833
  %cmp2 = icmp eq i32 11, %5, !dbg !2834
  br i1 %cmp2, label %lor.end, label %lor.lhs.false, !dbg !2835

lor.lhs.false:                                    ; preds = %if.then
  %6 = load i32, i32* %err, align 4, !dbg !2836
  %cmp3 = icmp eq i32 11, %6, !dbg !2838
  br i1 %cmp3, label %lor.end, label %lor.rhs, !dbg !2839

lor.rhs:                                          ; preds = %lor.lhs.false
  %7 = load i32, i32* %err, align 4, !dbg !2840
  %cmp4 = icmp eq i32 4, %7, !dbg !2842
  br label %lor.end, !dbg !2843

lor.end:                                          ; preds = %lor.rhs, %lor.lhs.false, %if.then
  %8 = phi i1 [ true, %lor.lhs.false ], [ true, %if.then ], [ %cmp4, %lor.rhs ]
  %lor.ext = zext i1 %8 to i32, !dbg !2844
  store i32 %lor.ext, i32* %return_error, align 4, !dbg !2846
  %9 = load i32, i32* %return_error, align 4, !dbg !2847
  %tobool = icmp ne i32 %9, 0, !dbg !2847
  br i1 %tobool, label %if.then5, label %if.end, !dbg !2849

if.then5:                                         ; preds = %lor.end
  store i32 81, i32* %retval, align 4, !dbg !2850
  br label %return, !dbg !2850

if.end:                                           ; preds = %lor.end
  store i32 56, i32* %retval, align 4, !dbg !2851
  br label %return, !dbg !2851

if.end6:                                          ; preds = %entry
  %10 = load i64, i64* %nread, align 8, !dbg !2852
  %11 = load i64*, i64** %n.addr, align 8, !dbg !2853
  store i64 %10, i64* %11, align 8, !dbg !2854
  store i32 0, i32* %retval, align 4, !dbg !2855
  br label %return, !dbg !2855

return:                                           ; preds = %if.end6, %if.end, %if.then5
  %12 = load i32, i32* %retval, align 4, !dbg !2856
  ret i32 %12, !dbg !2856
}

; Function Attrs: nounwind uwtable
define i32 @Curl_read(%struct.connectdata* %conn, i32 %sockfd, i8* %buf, i64 %sizerequested, i64* %n) #0 !dbg !1725 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %sockfd.addr = alloca i32, align 4
  %buf.addr = alloca i8*, align 8
  %sizerequested.addr = alloca i64, align 8
  %n.addr = alloca i64*, align 8
  %result = alloca i32, align 4
  %nread = alloca i64, align 8
  %bytesfromsocket = alloca i64, align 8
  %buffertofill = alloca i8*, align 8
  %pipelining = alloca i8, align 1
  %num = alloca i32, align 4
  %bytestocopy = alloca i64, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2857, metadata !1749), !dbg !2858
  store i32 %sockfd, i32* %sockfd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sockfd.addr, metadata !2859, metadata !1749), !dbg !2860
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !2861, metadata !1749), !dbg !2862
  store i64 %sizerequested, i64* %sizerequested.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sizerequested.addr, metadata !2863, metadata !1749), !dbg !2864
  store i64* %n, i64** %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %n.addr, metadata !2865, metadata !1749), !dbg !2866
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2867, metadata !1749), !dbg !2868
  store i32 56, i32* %result, align 4, !dbg !2868
  call void @llvm.dbg.declare(metadata i64* %nread, metadata !2869, metadata !1749), !dbg !2870
  store i64 0, i64* %nread, align 8, !dbg !2870
  call void @llvm.dbg.declare(metadata i64* %bytesfromsocket, metadata !2871, metadata !1749), !dbg !2872
  store i64 0, i64* %bytesfromsocket, align 8, !dbg !2872
  call void @llvm.dbg.declare(metadata i8** %buffertofill, metadata !2873, metadata !1749), !dbg !2874
  store i8* null, i8** %buffertofill, align 8, !dbg !2874
  call void @llvm.dbg.declare(metadata i8* %pipelining, metadata !2875, metadata !1749), !dbg !2876
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2877
  %data = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2878
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2878
  %multi = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 9, !dbg !2879
  %2 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !2879
  %call = call zeroext i1 @Curl_pipeline_wanted(%struct.Curl_multi* %2, i32 1), !dbg !2880
  br i1 %call, label %land.rhs, label %land.end, !dbg !2881

land.rhs:                                         ; preds = %entry
  %3 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2882
  %bundle = getelementptr inbounds %struct.connectdata, %struct.connectdata* %3, i32 0, i32 73, !dbg !2883
  %4 = load %struct.connectbundle*, %struct.connectbundle** %bundle, align 8, !dbg !2883
  %multiuse = getelementptr inbounds %struct.connectbundle, %struct.connectbundle* %4, i32 0, i32 0, !dbg !2884
  %5 = load i32, i32* %multiuse, align 8, !dbg !2884
  %cmp = icmp eq i32 %5, 1, !dbg !2885
  br label %land.end

land.end:                                         ; preds = %land.rhs, %entry
  %6 = phi i1 [ false, %entry ], [ %cmp, %land.rhs ]
  %frombool = zext i1 %6 to i8, !dbg !2886
  store i8 %frombool, i8* %pipelining, align 1, !dbg !2886
  call void @llvm.dbg.declare(metadata i32* %num, metadata !2888, metadata !1749), !dbg !2889
  %7 = load i32, i32* %sockfd.addr, align 4, !dbg !2890
  %8 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2891
  %sock = getelementptr inbounds %struct.connectdata, %struct.connectdata* %8, i32 0, i32 33, !dbg !2892
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %sock, i64 0, i64 1, !dbg !2891
  %9 = load i32, i32* %arrayidx, align 4, !dbg !2891
  %cmp1 = icmp eq i32 %7, %9, !dbg !2893
  %conv = zext i1 %cmp1 to i32, !dbg !2893
  store i32 %conv, i32* %num, align 4, !dbg !2889
  %10 = load i64*, i64** %n.addr, align 8, !dbg !2894
  store i64 0, i64* %10, align 8, !dbg !2895
  %11 = load i8, i8* %pipelining, align 1, !dbg !2896
  %tobool = trunc i8 %11 to i1, !dbg !2896
  br i1 %tobool, label %if.then, label %if.else, !dbg !2898

if.then:                                          ; preds = %land.end
  call void @llvm.dbg.declare(metadata i64* %bytestocopy, metadata !2899, metadata !1749), !dbg !2901
  %12 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2902
  %buf_len = getelementptr inbounds %struct.connectdata, %struct.connectdata* %12, i32 0, i32 59, !dbg !2902
  %13 = load i64, i64* %buf_len, align 8, !dbg !2902
  %14 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2902
  %read_pos = getelementptr inbounds %struct.connectdata, %struct.connectdata* %14, i32 0, i32 58, !dbg !2902
  %15 = load i64, i64* %read_pos, align 8, !dbg !2902
  %sub = sub i64 %13, %15, !dbg !2902
  %16 = load i64, i64* %sizerequested.addr, align 8, !dbg !2902
  %cmp2 = icmp ult i64 %sub, %16, !dbg !2902
  br i1 %cmp2, label %cond.true, label %cond.false, !dbg !2902

cond.true:                                        ; preds = %if.then
  %17 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2903
  %buf_len4 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %17, i32 0, i32 59, !dbg !2903
  %18 = load i64, i64* %buf_len4, align 8, !dbg !2903
  %19 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2903
  %read_pos5 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %19, i32 0, i32 58, !dbg !2903
  %20 = load i64, i64* %read_pos5, align 8, !dbg !2903
  %sub6 = sub i64 %18, %20, !dbg !2903
  br label %cond.end, !dbg !2903

cond.false:                                       ; preds = %if.then
  %21 = load i64, i64* %sizerequested.addr, align 8, !dbg !2905
  br label %cond.end, !dbg !2905

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %sub6, %cond.true ], [ %21, %cond.false ], !dbg !2907
  store i64 %cond, i64* %bytestocopy, align 8, !dbg !2909
  %22 = load i64, i64* %bytestocopy, align 8, !dbg !2910
  %cmp7 = icmp ugt i64 %22, 0, !dbg !2912
  br i1 %cmp7, label %if.then9, label %if.end, !dbg !2913

if.then9:                                         ; preds = %cond.end
  %23 = load i8*, i8** %buf.addr, align 8, !dbg !2914
  %24 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2916
  %master_buffer = getelementptr inbounds %struct.connectdata, %struct.connectdata* %24, i32 0, i32 57, !dbg !2917
  %25 = load i8*, i8** %master_buffer, align 8, !dbg !2917
  %26 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2918
  %read_pos10 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %26, i32 0, i32 58, !dbg !2919
  %27 = load i64, i64* %read_pos10, align 8, !dbg !2919
  %add.ptr = getelementptr inbounds i8, i8* %25, i64 %27, !dbg !2920
  %28 = load i64, i64* %bytestocopy, align 8, !dbg !2921
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %23, i8* %add.ptr, i64 %28, i32 1, i1 false), !dbg !2922
  %29 = load i64, i64* %bytestocopy, align 8, !dbg !2923
  %30 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2924
  %read_pos11 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %30, i32 0, i32 58, !dbg !2925
  %31 = load i64, i64* %read_pos11, align 8, !dbg !2926
  %add = add i64 %31, %29, !dbg !2926
  store i64 %add, i64* %read_pos11, align 8, !dbg !2926
  %32 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2927
  %bits = getelementptr inbounds %struct.connectdata, %struct.connectdata* %32, i32 0, i32 43, !dbg !2928
  %stream_was_rewound = getelementptr inbounds %struct.ConnectBits, %struct.ConnectBits* %bits, i32 0, i32 23, !dbg !2929
  store i8 0, i8* %stream_was_rewound, align 1, !dbg !2930
  %33 = load i64, i64* %bytestocopy, align 8, !dbg !2931
  %34 = load i64*, i64** %n.addr, align 8, !dbg !2932
  store i64 %33, i64* %34, align 8, !dbg !2933
  store i32 0, i32* %retval, align 4, !dbg !2934
  br label %return, !dbg !2934

if.end:                                           ; preds = %cond.end
  %35 = load i64, i64* %sizerequested.addr, align 8, !dbg !2935
  %cmp12 = icmp ult i64 %35, 16384, !dbg !2935
  br i1 %cmp12, label %cond.true14, label %cond.false15, !dbg !2935

cond.true14:                                      ; preds = %if.end
  %36 = load i64, i64* %sizerequested.addr, align 8, !dbg !2936
  br label %cond.end16, !dbg !2936

cond.false15:                                     ; preds = %if.end
  br label %cond.end16, !dbg !2937

cond.end16:                                       ; preds = %cond.false15, %cond.true14
  %cond17 = phi i64 [ %36, %cond.true14 ], [ 16384, %cond.false15 ], !dbg !2938
  store i64 %cond17, i64* %bytesfromsocket, align 8, !dbg !2939
  %37 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2940
  %master_buffer18 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %37, i32 0, i32 57, !dbg !2941
  %38 = load i8*, i8** %master_buffer18, align 8, !dbg !2941
  store i8* %38, i8** %buffertofill, align 8, !dbg !2942
  br label %if.end45, !dbg !2943

if.else:                                          ; preds = %land.end
  %39 = load i64, i64* %sizerequested.addr, align 8, !dbg !2944
  %40 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2944
  %data19 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %40, i32 0, i32 0, !dbg !2944
  %41 = load %struct.Curl_easy*, %struct.Curl_easy** %data19, align 8, !dbg !2944
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %41, i32 0, i32 13, !dbg !2944
  %buffer_size = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 78, !dbg !2944
  %42 = load i64, i64* %buffer_size, align 8, !dbg !2944
  %tobool20 = icmp ne i64 %42, 0, !dbg !2944
  br i1 %tobool20, label %cond.true21, label %cond.false25, !dbg !2944

cond.true21:                                      ; preds = %if.else
  %43 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2946
  %data22 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %43, i32 0, i32 0, !dbg !2946
  %44 = load %struct.Curl_easy*, %struct.Curl_easy** %data22, align 8, !dbg !2946
  %set23 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %44, i32 0, i32 13, !dbg !2946
  %buffer_size24 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set23, i32 0, i32 78, !dbg !2946
  %45 = load i64, i64* %buffer_size24, align 8, !dbg !2946
  br label %cond.end26, !dbg !2946

cond.false25:                                     ; preds = %if.else
  br label %cond.end26, !dbg !2948

cond.end26:                                       ; preds = %cond.false25, %cond.true21
  %cond27 = phi i64 [ %45, %cond.true21 ], [ 16384, %cond.false25 ], !dbg !2950
  %cmp28 = icmp slt i64 %39, %cond27, !dbg !2950
  br i1 %cmp28, label %cond.true30, label %cond.false31, !dbg !2950

cond.true30:                                      ; preds = %cond.end26
  %46 = load i64, i64* %sizerequested.addr, align 8, !dbg !2952
  br label %cond.end43, !dbg !2952

cond.false31:                                     ; preds = %cond.end26
  %47 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2954
  %data32 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %47, i32 0, i32 0, !dbg !2954
  %48 = load %struct.Curl_easy*, %struct.Curl_easy** %data32, align 8, !dbg !2954
  %set33 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %48, i32 0, i32 13, !dbg !2954
  %buffer_size34 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set33, i32 0, i32 78, !dbg !2954
  %49 = load i64, i64* %buffer_size34, align 8, !dbg !2954
  %tobool35 = icmp ne i64 %49, 0, !dbg !2954
  br i1 %tobool35, label %cond.true36, label %cond.false40, !dbg !2954

cond.true36:                                      ; preds = %cond.false31
  %50 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2956
  %data37 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %50, i32 0, i32 0, !dbg !2956
  %51 = load %struct.Curl_easy*, %struct.Curl_easy** %data37, align 8, !dbg !2956
  %set38 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %51, i32 0, i32 13, !dbg !2956
  %buffer_size39 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set38, i32 0, i32 78, !dbg !2956
  %52 = load i64, i64* %buffer_size39, align 8, !dbg !2956
  br label %cond.end41, !dbg !2956

cond.false40:                                     ; preds = %cond.false31
  br label %cond.end41, !dbg !2958

cond.end41:                                       ; preds = %cond.false40, %cond.true36
  %cond42 = phi i64 [ %52, %cond.true36 ], [ 16384, %cond.false40 ], !dbg !2960
  br label %cond.end43, !dbg !2960

cond.end43:                                       ; preds = %cond.end41, %cond.true30
  %cond44 = phi i64 [ %46, %cond.true30 ], [ %cond42, %cond.end41 ], !dbg !2962
  store i64 %cond44, i64* %bytesfromsocket, align 8, !dbg !2964
  %53 = load i8*, i8** %buf.addr, align 8, !dbg !2965
  store i8* %53, i8** %buffertofill, align 8, !dbg !2966
  br label %if.end45

if.end45:                                         ; preds = %cond.end43, %cond.end16
  %54 = load i32, i32* %num, align 4, !dbg !2967
  %idxprom = sext i32 %54 to i64, !dbg !2968
  %55 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2968
  %recv = getelementptr inbounds %struct.connectdata, %struct.connectdata* %55, i32 0, i32 36, !dbg !2969
  %arrayidx46 = getelementptr inbounds [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*]* %recv, i64 0, i64 %idxprom, !dbg !2968
  %56 = load i64 (%struct.connectdata*, i32, i8*, i64, i32*)*, i64 (%struct.connectdata*, i32, i8*, i64, i32*)** %arrayidx46, align 8, !dbg !2968
  %57 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2970
  %58 = load i32, i32* %num, align 4, !dbg !2971
  %59 = load i8*, i8** %buffertofill, align 8, !dbg !2972
  %60 = load i64, i64* %bytesfromsocket, align 8, !dbg !2973
  %call47 = call i64 %56(%struct.connectdata* %57, i32 %58, i8* %59, i64 %60, i32* %result), !dbg !2968
  store i64 %call47, i64* %nread, align 8, !dbg !2974
  %61 = load i64, i64* %nread, align 8, !dbg !2975
  %cmp48 = icmp slt i64 %61, 0, !dbg !2977
  br i1 %cmp48, label %if.then50, label %if.end51, !dbg !2978

if.then50:                                        ; preds = %if.end45
  %62 = load i32, i32* %result, align 4, !dbg !2979
  store i32 %62, i32* %retval, align 4, !dbg !2980
  br label %return, !dbg !2980

if.end51:                                         ; preds = %if.end45
  %63 = load i8, i8* %pipelining, align 1, !dbg !2981
  %tobool52 = trunc i8 %63 to i1, !dbg !2981
  br i1 %tobool52, label %if.then53, label %if.end57, !dbg !2983

if.then53:                                        ; preds = %if.end51
  %64 = load i8*, i8** %buf.addr, align 8, !dbg !2984
  %65 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2986
  %master_buffer54 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %65, i32 0, i32 57, !dbg !2987
  %66 = load i8*, i8** %master_buffer54, align 8, !dbg !2987
  %67 = load i64, i64* %nread, align 8, !dbg !2988
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %64, i8* %66, i64 %67, i32 1, i1 false), !dbg !2989
  %68 = load i64, i64* %nread, align 8, !dbg !2990
  %69 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2991
  %buf_len55 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %69, i32 0, i32 59, !dbg !2992
  store i64 %68, i64* %buf_len55, align 8, !dbg !2993
  %70 = load i64, i64* %nread, align 8, !dbg !2994
  %71 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2995
  %read_pos56 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %71, i32 0, i32 58, !dbg !2996
  store i64 %70, i64* %read_pos56, align 8, !dbg !2997
  br label %if.end57, !dbg !2998

if.end57:                                         ; preds = %if.then53, %if.end51
  %72 = load i64, i64* %nread, align 8, !dbg !2999
  %73 = load i64*, i64** %n.addr, align 8, !dbg !3000
  %74 = load i64, i64* %73, align 8, !dbg !3001
  %add58 = add nsw i64 %74, %72, !dbg !3001
  store i64 %add58, i64* %73, align 8, !dbg !3001
  store i32 0, i32* %retval, align 4, !dbg !3002
  br label %return, !dbg !3002

return:                                           ; preds = %if.end57, %if.then50, %if.then9
  %75 = load i32, i32* %retval, align 4, !dbg !3003
  ret i32 %75, !dbg !3003
}

declare zeroext i1 @Curl_pipeline_wanted(%struct.Curl_multi*, i32) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define internal i32 @showit(%struct.Curl_easy* %data, i32 %type, i8* %ptr, i64 %size) #0 !dbg !1737 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %type.addr = alloca i32, align 4
  %ptr.addr = alloca i8*, align 8
  %size.addr = alloca i64, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !3004, metadata !1749), !dbg !3005
  store i32 %type, i32* %type.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %type.addr, metadata !3006, metadata !1749), !dbg !3007
  store i8* %ptr, i8** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %ptr.addr, metadata !3008, metadata !1749), !dbg !3009
  store i64 %size, i64* %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %size.addr, metadata !3010, metadata !1749), !dbg !3011
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3012
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 13, !dbg !3014
  %fdebug = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 28, !dbg !3015
  %1 = load i32 (%struct.Curl_easy*, i32, i8*, i64, i8*)*, i32 (%struct.Curl_easy*, i32, i8*, i64, i8*)** %fdebug, align 8, !dbg !3015
  %tobool = icmp ne i32 (%struct.Curl_easy*, i32, i8*, i64, i8*)* %1, null, !dbg !3012
  br i1 %tobool, label %if.then, label %if.end, !dbg !3016

if.then:                                          ; preds = %entry
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3017
  %set1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 13, !dbg !3018
  %fdebug2 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set1, i32 0, i32 28, !dbg !3019
  %3 = load i32 (%struct.Curl_easy*, i32, i8*, i64, i8*)*, i32 (%struct.Curl_easy*, i32, i8*, i64, i8*)** %fdebug2, align 8, !dbg !3019
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3020
  %5 = load i32, i32* %type.addr, align 4, !dbg !3021
  %6 = load i8*, i8** %ptr.addr, align 8, !dbg !3022
  %7 = load i64, i64* %size.addr, align 8, !dbg !3023
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3024
  %set3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %8, i32 0, i32 13, !dbg !3025
  %debugdata = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set3, i32 0, i32 1, !dbg !3026
  %9 = load i8*, i8** %debugdata, align 8, !dbg !3026
  %call = call i32 %3(%struct.Curl_easy* %4, i32 %5, i8* %6, i64 %7, i8* %9), !dbg !3027
  store i32 %call, i32* %retval, align 4, !dbg !3028
  br label %return, !dbg !3028

if.end:                                           ; preds = %entry
  %10 = load i32, i32* %type.addr, align 4, !dbg !3029
  switch i32 %10, label %sw.default [
    i32 0, label %sw.bb
    i32 2, label %sw.bb
    i32 1, label %sw.bb
  ], !dbg !3030

sw.bb:                                            ; preds = %if.end, %if.end, %if.end
  %11 = load i32, i32* %type.addr, align 4, !dbg !3031
  %idxprom = zext i32 %11 to i64, !dbg !3033
  %arrayidx = getelementptr inbounds [7 x [3 x i8]], [7 x [3 x i8]]* @showit.s_infotype, i64 0, i64 %idxprom, !dbg !3033
  %arraydecay = getelementptr inbounds [3 x i8], [3 x i8]* %arrayidx, i32 0, i32 0, !dbg !3033
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3034
  %set4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 13, !dbg !3035
  %err = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set4, i32 0, i32 0, !dbg !3036
  %13 = load %struct._IO_FILE*, %struct._IO_FILE** %err, align 8, !dbg !3036
  %call5 = call i64 @fwrite(i8* %arraydecay, i64 2, i64 1, %struct._IO_FILE* %13), !dbg !3037
  %14 = load i8*, i8** %ptr.addr, align 8, !dbg !3038
  %15 = load i64, i64* %size.addr, align 8, !dbg !3039
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !3040
  %set6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %16, i32 0, i32 13, !dbg !3041
  %err7 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set6, i32 0, i32 0, !dbg !3042
  %17 = load %struct._IO_FILE*, %struct._IO_FILE** %err7, align 8, !dbg !3042
  %call8 = call i64 @fwrite(i8* %14, i64 %15, i64 1, %struct._IO_FILE* %17), !dbg !3043
  br label %sw.epilog, !dbg !3044

sw.default:                                       ; preds = %if.end
  br label %sw.epilog, !dbg !3045

sw.epilog:                                        ; preds = %sw.default, %sw.bb
  store i32 0, i32* %retval, align 4, !dbg !3046
  br label %return, !dbg !3046

return:                                           ; preds = %sw.epilog, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !3047
  ret i32 %18, !dbg !3047
}

declare i8* @Curl_memdup(i8*, i64) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

; Function Attrs: nounwind readonly
declare i8* @memchr(i8*, i32, i64) #4

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #4

declare i64 @fwrite(i8*, i64, i64, %struct._IO_FILE*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!1745, !1746}
!llvm.ident = !{!1747}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !1699, subprograms: !1700, globals: !1740)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/sendf.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !26, !123, !129, !185, !227, !234, !269, !279, !285, !290, !297, !307, !316, !322, !328, !334, !340, !347, !353, !359, !374, !385, !399, !410, !415, !423, !461, !480, !500, !515, !532, !540, !1678}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 35, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/multihandle.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24, !25}
!6 = !DIEnumerator(name: "CURLM_STATE_INIT", value: 0)
!7 = !DIEnumerator(name: "CURLM_STATE_CONNECT_PEND", value: 1)
!8 = !DIEnumerator(name: "CURLM_STATE_CONNECT", value: 2)
!9 = !DIEnumerator(name: "CURLM_STATE_WAITRESOLVE", value: 3)
!10 = !DIEnumerator(name: "CURLM_STATE_WAITCONNECT", value: 4)
!11 = !DIEnumerator(name: "CURLM_STATE_WAITPROXYCONNECT", value: 5)
!12 = !DIEnumerator(name: "CURLM_STATE_SENDPROTOCONNECT", value: 6)
!13 = !DIEnumerator(name: "CURLM_STATE_PROTOCONNECT", value: 7)
!14 = !DIEnumerator(name: "CURLM_STATE_WAITDO", value: 8)
!15 = !DIEnumerator(name: "CURLM_STATE_DO", value: 9)
!16 = !DIEnumerator(name: "CURLM_STATE_DOING", value: 10)
!17 = !DIEnumerator(name: "CURLM_STATE_DO_MORE", value: 11)
!18 = !DIEnumerator(name: "CURLM_STATE_DO_DONE", value: 12)
!19 = !DIEnumerator(name: "CURLM_STATE_WAITPERFORM", value: 13)
!20 = !DIEnumerator(name: "CURLM_STATE_PERFORM", value: 14)
!21 = !DIEnumerator(name: "CURLM_STATE_TOOFAST", value: 15)
!22 = !DIEnumerator(name: "CURLM_STATE_DONE", value: 16)
!23 = !DIEnumerator(name: "CURLM_STATE_COMPLETED", value: 17)
!24 = !DIEnumerator(name: "CURLM_STATE_MSGSENT", value: 18)
!25 = !DIEnumerator(name: "CURLM_STATE_LAST", value: 19)
!26 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 434, size: 32, align: 32, elements: !28)
!27 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curl.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!28 = !{!29, !30, !31, !32, !33, !34, !35, !36, !37, !38, !39, !40, !41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122}
!29 = !DIEnumerator(name: "CURLE_OK", value: 0)
!30 = !DIEnumerator(name: "CURLE_UNSUPPORTED_PROTOCOL", value: 1)
!31 = !DIEnumerator(name: "CURLE_FAILED_INIT", value: 2)
!32 = !DIEnumerator(name: "CURLE_URL_MALFORMAT", value: 3)
!33 = !DIEnumerator(name: "CURLE_NOT_BUILT_IN", value: 4)
!34 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_PROXY", value: 5)
!35 = !DIEnumerator(name: "CURLE_COULDNT_RESOLVE_HOST", value: 6)
!36 = !DIEnumerator(name: "CURLE_COULDNT_CONNECT", value: 7)
!37 = !DIEnumerator(name: "CURLE_WEIRD_SERVER_REPLY", value: 8)
!38 = !DIEnumerator(name: "CURLE_REMOTE_ACCESS_DENIED", value: 9)
!39 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_FAILED", value: 10)
!40 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASS_REPLY", value: 11)
!41 = !DIEnumerator(name: "CURLE_FTP_ACCEPT_TIMEOUT", value: 12)
!42 = !DIEnumerator(name: "CURLE_FTP_WEIRD_PASV_REPLY", value: 13)
!43 = !DIEnumerator(name: "CURLE_FTP_WEIRD_227_FORMAT", value: 14)
!44 = !DIEnumerator(name: "CURLE_FTP_CANT_GET_HOST", value: 15)
!45 = !DIEnumerator(name: "CURLE_HTTP2", value: 16)
!46 = !DIEnumerator(name: "CURLE_FTP_COULDNT_SET_TYPE", value: 17)
!47 = !DIEnumerator(name: "CURLE_PARTIAL_FILE", value: 18)
!48 = !DIEnumerator(name: "CURLE_FTP_COULDNT_RETR_FILE", value: 19)
!49 = !DIEnumerator(name: "CURLE_OBSOLETE20", value: 20)
!50 = !DIEnumerator(name: "CURLE_QUOTE_ERROR", value: 21)
!51 = !DIEnumerator(name: "CURLE_HTTP_RETURNED_ERROR", value: 22)
!52 = !DIEnumerator(name: "CURLE_WRITE_ERROR", value: 23)
!53 = !DIEnumerator(name: "CURLE_OBSOLETE24", value: 24)
!54 = !DIEnumerator(name: "CURLE_UPLOAD_FAILED", value: 25)
!55 = !DIEnumerator(name: "CURLE_READ_ERROR", value: 26)
!56 = !DIEnumerator(name: "CURLE_OUT_OF_MEMORY", value: 27)
!57 = !DIEnumerator(name: "CURLE_OPERATION_TIMEDOUT", value: 28)
!58 = !DIEnumerator(name: "CURLE_OBSOLETE29", value: 29)
!59 = !DIEnumerator(name: "CURLE_FTP_PORT_FAILED", value: 30)
!60 = !DIEnumerator(name: "CURLE_FTP_COULDNT_USE_REST", value: 31)
!61 = !DIEnumerator(name: "CURLE_OBSOLETE32", value: 32)
!62 = !DIEnumerator(name: "CURLE_RANGE_ERROR", value: 33)
!63 = !DIEnumerator(name: "CURLE_HTTP_POST_ERROR", value: 34)
!64 = !DIEnumerator(name: "CURLE_SSL_CONNECT_ERROR", value: 35)
!65 = !DIEnumerator(name: "CURLE_BAD_DOWNLOAD_RESUME", value: 36)
!66 = !DIEnumerator(name: "CURLE_FILE_COULDNT_READ_FILE", value: 37)
!67 = !DIEnumerator(name: "CURLE_LDAP_CANNOT_BIND", value: 38)
!68 = !DIEnumerator(name: "CURLE_LDAP_SEARCH_FAILED", value: 39)
!69 = !DIEnumerator(name: "CURLE_OBSOLETE40", value: 40)
!70 = !DIEnumerator(name: "CURLE_FUNCTION_NOT_FOUND", value: 41)
!71 = !DIEnumerator(name: "CURLE_ABORTED_BY_CALLBACK", value: 42)
!72 = !DIEnumerator(name: "CURLE_BAD_FUNCTION_ARGUMENT", value: 43)
!73 = !DIEnumerator(name: "CURLE_OBSOLETE44", value: 44)
!74 = !DIEnumerator(name: "CURLE_INTERFACE_FAILED", value: 45)
!75 = !DIEnumerator(name: "CURLE_OBSOLETE46", value: 46)
!76 = !DIEnumerator(name: "CURLE_TOO_MANY_REDIRECTS", value: 47)
!77 = !DIEnumerator(name: "CURLE_UNKNOWN_OPTION", value: 48)
!78 = !DIEnumerator(name: "CURLE_TELNET_OPTION_SYNTAX", value: 49)
!79 = !DIEnumerator(name: "CURLE_OBSOLETE50", value: 50)
!80 = !DIEnumerator(name: "CURLE_PEER_FAILED_VERIFICATION", value: 51)
!81 = !DIEnumerator(name: "CURLE_GOT_NOTHING", value: 52)
!82 = !DIEnumerator(name: "CURLE_SSL_ENGINE_NOTFOUND", value: 53)
!83 = !DIEnumerator(name: "CURLE_SSL_ENGINE_SETFAILED", value: 54)
!84 = !DIEnumerator(name: "CURLE_SEND_ERROR", value: 55)
!85 = !DIEnumerator(name: "CURLE_RECV_ERROR", value: 56)
!86 = !DIEnumerator(name: "CURLE_OBSOLETE57", value: 57)
!87 = !DIEnumerator(name: "CURLE_SSL_CERTPROBLEM", value: 58)
!88 = !DIEnumerator(name: "CURLE_SSL_CIPHER", value: 59)
!89 = !DIEnumerator(name: "CURLE_SSL_CACERT", value: 60)
!90 = !DIEnumerator(name: "CURLE_BAD_CONTENT_ENCODING", value: 61)
!91 = !DIEnumerator(name: "CURLE_LDAP_INVALID_URL", value: 62)
!92 = !DIEnumerator(name: "CURLE_FILESIZE_EXCEEDED", value: 63)
!93 = !DIEnumerator(name: "CURLE_USE_SSL_FAILED", value: 64)
!94 = !DIEnumerator(name: "CURLE_SEND_FAIL_REWIND", value: 65)
!95 = !DIEnumerator(name: "CURLE_SSL_ENGINE_INITFAILED", value: 66)
!96 = !DIEnumerator(name: "CURLE_LOGIN_DENIED", value: 67)
!97 = !DIEnumerator(name: "CURLE_TFTP_NOTFOUND", value: 68)
!98 = !DIEnumerator(name: "CURLE_TFTP_PERM", value: 69)
!99 = !DIEnumerator(name: "CURLE_REMOTE_DISK_FULL", value: 70)
!100 = !DIEnumerator(name: "CURLE_TFTP_ILLEGAL", value: 71)
!101 = !DIEnumerator(name: "CURLE_TFTP_UNKNOWNID", value: 72)
!102 = !DIEnumerator(name: "CURLE_REMOTE_FILE_EXISTS", value: 73)
!103 = !DIEnumerator(name: "CURLE_TFTP_NOSUCHUSER", value: 74)
!104 = !DIEnumerator(name: "CURLE_CONV_FAILED", value: 75)
!105 = !DIEnumerator(name: "CURLE_CONV_REQD", value: 76)
!106 = !DIEnumerator(name: "CURLE_SSL_CACERT_BADFILE", value: 77)
!107 = !DIEnumerator(name: "CURLE_REMOTE_FILE_NOT_FOUND", value: 78)
!108 = !DIEnumerator(name: "CURLE_SSH", value: 79)
!109 = !DIEnumerator(name: "CURLE_SSL_SHUTDOWN_FAILED", value: 80)
!110 = !DIEnumerator(name: "CURLE_AGAIN", value: 81)
!111 = !DIEnumerator(name: "CURLE_SSL_CRL_BADFILE", value: 82)
!112 = !DIEnumerator(name: "CURLE_SSL_ISSUER_ERROR", value: 83)
!113 = !DIEnumerator(name: "CURLE_FTP_PRET_FAILED", value: 84)
!114 = !DIEnumerator(name: "CURLE_RTSP_CSEQ_ERROR", value: 85)
!115 = !DIEnumerator(name: "CURLE_RTSP_SESSION_ERROR", value: 86)
!116 = !DIEnumerator(name: "CURLE_FTP_BAD_FILE_LIST", value: 87)
!117 = !DIEnumerator(name: "CURLE_CHUNK_FAILED", value: 88)
!118 = !DIEnumerator(name: "CURLE_NO_CONNECTION_AVAILABLE", value: 89)
!119 = !DIEnumerator(name: "CURLE_SSL_PINNEDPUBKEYNOTMATCH", value: 90)
!120 = !DIEnumerator(name: "CURLE_SSL_INVALIDCERTSTATUS", value: 91)
!121 = !DIEnumerator(name: "CURLE_HTTP2_STREAM", value: 92)
!122 = !DIEnumerator(name: "CURL_LAST", value: 93)
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
!248 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_t", file: !27, line: 131, baseType: !177)
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
!269 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 409, size: 32, align: 32, elements: !270)
!270 = !{!271, !272, !273, !274, !275, !276, !277, !278}
!271 = !DIEnumerator(name: "CURLINFO_TEXT", value: 0)
!272 = !DIEnumerator(name: "CURLINFO_HEADER_IN", value: 1)
!273 = !DIEnumerator(name: "CURLINFO_HEADER_OUT", value: 2)
!274 = !DIEnumerator(name: "CURLINFO_DATA_IN", value: 3)
!275 = !DIEnumerator(name: "CURLINFO_DATA_OUT", value: 4)
!276 = !DIEnumerator(name: "CURLINFO_SSL_DATA_IN", value: 5)
!277 = !DIEnumerator(name: "CURLINFO_SSL_DATA_OUT", value: 6)
!278 = !DIEnumerator(name: "CURLINFO_END", value: 7)
!279 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 375, size: 32, align: 32, elements: !280)
!280 = !{!281, !282, !283, !284}
!281 = !DIEnumerator(name: "CURLIOE_OK", value: 0)
!282 = !DIEnumerator(name: "CURLIOE_UNKNOWNCMD", value: 1)
!283 = !DIEnumerator(name: "CURLIOE_FAILRESTART", value: 2)
!284 = !DIEnumerator(name: "CURLIOE_LAST", value: 3)
!285 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 340, size: 32, align: 32, elements: !286)
!286 = !{!287, !288, !289}
!287 = !DIEnumerator(name: "CURLSOCKTYPE_IPCXN", value: 0)
!288 = !DIEnumerator(name: "CURLSOCKTYPE_ACCEPT", value: 1)
!289 = !DIEnumerator(name: "CURLSOCKTYPE_LAST", value: 2)
!290 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 1921, size: 32, align: 32, elements: !291)
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
!307 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 644, size: 32, align: 32, elements: !308)
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
!322 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khtype", file: !27, line: 704, size: 32, align: 32, elements: !323)
!323 = !{!324, !325, !326, !327}
!324 = !DIEnumerator(name: "CURLKHTYPE_UNKNOWN", value: 0)
!325 = !DIEnumerator(name: "CURLKHTYPE_RSA1", value: 1)
!326 = !DIEnumerator(name: "CURLKHTYPE_RSA", value: 2)
!327 = !DIEnumerator(name: "CURLKHTYPE_DSS", value: 3)
!328 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khmatch", file: !27, line: 731, size: 32, align: 32, elements: !329)
!329 = !{!330, !331, !332, !333}
!330 = !DIEnumerator(name: "CURLKHMATCH_OK", value: 0)
!331 = !DIEnumerator(name: "CURLKHMATCH_MISMATCH", value: 1)
!332 = !DIEnumerator(name: "CURLKHMATCH_MISSING", value: 2)
!333 = !DIEnumerator(name: "CURLKHMATCH_LAST", value: 3)
!334 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "CURL_NETRC_OPTION", file: !27, line: 1867, size: 32, align: 32, elements: !335)
!335 = !{!336, !337, !338, !339}
!336 = !DIEnumerator(name: "CURL_NETRC_IGNORED", value: 0)
!337 = !DIEnumerator(name: "CURL_NETRC_OPTIONAL", value: 1)
!338 = !DIEnumerator(name: "CURL_NETRC_REQUIRED", value: 2)
!339 = !DIEnumerator(name: "CURL_NETRC_LAST", value: 3)
!340 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 746, size: 32, align: 32, elements: !341)
!341 = !{!342, !343, !344, !345, !346}
!342 = !DIEnumerator(name: "CURLUSESSL_NONE", value: 0)
!343 = !DIEnumerator(name: "CURLUSESSL_TRY", value: 1)
!344 = !DIEnumerator(name: "CURLUSESSL_CONTROL", value: 2)
!345 = !DIEnumerator(name: "CURLUSESSL_ALL", value: 3)
!346 = !DIEnumerator(name: "CURLUSESSL_LAST", value: 4)
!347 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 790, size: 32, align: 32, elements: !348)
!348 = !{!349, !350, !351, !352}
!349 = !DIEnumerator(name: "CURLFTPAUTH_DEFAULT", value: 0)
!350 = !DIEnumerator(name: "CURLFTPAUTH_SSL", value: 1)
!351 = !DIEnumerator(name: "CURLFTPAUTH_TLS", value: 2)
!352 = !DIEnumerator(name: "CURLFTPAUTH_LAST", value: 3)
!353 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 782, size: 32, align: 32, elements: !354)
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
!385 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !27, line: 2222, size: 32, align: 32, elements: !386)
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
!552 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMstate", file: !4, line: 59, baseType: !3)
!553 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !545, file: !130, line: 1809, baseType: !554, size: 32, align: 32, offset: 224)
!554 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLcode", file: !27, line: 561, baseType: !26)
!555 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !545, file: !130, line: 1811, baseType: !556, size: 192, align: 64, offset: 256)
!556 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_message", file: !4, line: 27, size: 192, align: 64, elements: !557)
!557 = !{!558}
!558 = !DIDerivedType(tag: DW_TAG_member, name: "extmsg", scope: !556, file: !4, line: 29, baseType: !559, size: 192, align: 64)
!559 = !DICompositeType(tag: DW_TAG_structure_type, name: "CURLMsg", file: !124, line: 93, size: 192, align: 64, elements: !560)
!560 = !{!561, !563, !566}
!561 = !DIDerivedType(tag: DW_TAG_member, name: "msg", scope: !559, file: !124, line: 94, baseType: !562, size: 32, align: 32)
!562 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMSG", file: !124, line: 91, baseType: !123)
!563 = !DIDerivedType(tag: DW_TAG_member, name: "easy_handle", scope: !559, file: !124, line: 95, baseType: !564, size: 64, align: 64, offset: 64)
!564 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !565, size: 64, align: 64)
!565 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURL", file: !27, line: 100, baseType: !545)
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
!579 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_multi", file: !4, line: 70, size: 3840, align: 64, elements: !580)
!580 = !{!581, !582, !583, !584, !585, !586, !587, !588, !593, !594, !601, !602, !603, !614, !615, !616, !617, !625, !626, !627, !628, !629, !630, !631, !632, !633, !634, !641, !642}
!581 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !579, file: !4, line: 73, baseType: !191, size: 64, align: 64)
!582 = !DIDerivedType(tag: DW_TAG_member, name: "easyp", scope: !579, file: !4, line: 76, baseType: !544, size: 64, align: 64, offset: 64)
!583 = !DIDerivedType(tag: DW_TAG_member, name: "easylp", scope: !579, file: !4, line: 77, baseType: !544, size: 64, align: 64, offset: 128)
!584 = !DIDerivedType(tag: DW_TAG_member, name: "num_easy", scope: !579, file: !4, line: 79, baseType: !177, size: 32, align: 32, offset: 192)
!585 = !DIDerivedType(tag: DW_TAG_member, name: "num_alive", scope: !579, file: !4, line: 80, baseType: !177, size: 32, align: 32, offset: 224)
!586 = !DIDerivedType(tag: DW_TAG_member, name: "msglist", scope: !579, file: !4, line: 83, baseType: !140, size: 256, align: 64, offset: 256)
!587 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !579, file: !4, line: 85, baseType: !140, size: 256, align: 64, offset: 512)
!588 = !DIDerivedType(tag: DW_TAG_member, name: "socket_cb", scope: !579, file: !4, line: 89, baseType: !589, size: 64, align: 64, offset: 768)
!589 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_callback", file: !124, line: 268, baseType: !590)
!590 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !591, size: 64, align: 64)
!591 = !DISubroutineType(types: !592)
!592 = !{!177, !564, !248, !177, !148, !148}
!593 = !DIDerivedType(tag: DW_TAG_member, name: "socket_userp", scope: !579, file: !4, line: 90, baseType: !148, size: 64, align: 64, offset: 832)
!594 = !DIDerivedType(tag: DW_TAG_member, name: "push_cb", scope: !579, file: !4, line: 93, baseType: !595, size: 64, align: 64, offset: 896)
!595 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_push_callback", file: !124, line: 429, baseType: !596)
!596 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !597, size: 64, align: 64)
!597 = !DISubroutineType(types: !598)
!598 = !{!177, !564, !564, !158, !599, !148}
!599 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !600, size: 64, align: 64)
!600 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_pushheaders", file: !124, line: 422, flags: DIFlagFwdDecl)
!601 = !DIDerivedType(tag: DW_TAG_member, name: "push_userp", scope: !579, file: !4, line: 94, baseType: !148, size: 64, align: 64, offset: 960)
!602 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !579, file: !4, line: 97, baseType: !135, size: 384, align: 64, offset: 1024)
!603 = !DIDerivedType(tag: DW_TAG_member, name: "timetree", scope: !579, file: !4, line: 101, baseType: !604, size: 64, align: 64, offset: 1408)
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
!614 = !DIDerivedType(tag: DW_TAG_member, name: "sockhash", scope: !579, file: !4, line: 106, baseType: !135, size: 384, align: 64, offset: 1472)
!615 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining", scope: !579, file: !4, line: 109, baseType: !191, size: 64, align: 64, offset: 1856)
!616 = !DIDerivedType(tag: DW_TAG_member, name: "recheckstate", scope: !579, file: !4, line: 111, baseType: !211, size: 8, align: 8, offset: 1920)
!617 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !579, file: !4, line: 114, baseType: !618, size: 640, align: 64, offset: 1984)
!618 = !DICompositeType(tag: DW_TAG_structure_type, name: "conncache", file: !619, line: 26, size: 640, align: 64, elements: !620)
!619 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/conncache.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!620 = !{!621, !622, !623, !624}
!621 = !DIDerivedType(tag: DW_TAG_member, name: "hash", scope: !618, file: !619, line: 27, baseType: !135, size: 384, align: 64)
!622 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !618, file: !619, line: 28, baseType: !158, size: 64, align: 64, offset: 384)
!623 = !DIDerivedType(tag: DW_TAG_member, name: "next_connection_id", scope: !618, file: !619, line: 29, baseType: !191, size: 64, align: 64, offset: 448)
!624 = !DIDerivedType(tag: DW_TAG_member, name: "last_cleanup", scope: !618, file: !619, line: 30, baseType: !201, size: 128, align: 64, offset: 512)
!625 = !DIDerivedType(tag: DW_TAG_member, name: "closure_handle", scope: !579, file: !4, line: 118, baseType: !544, size: 64, align: 64, offset: 2624)
!626 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !579, file: !4, line: 120, baseType: !191, size: 64, align: 64, offset: 2688)
!627 = !DIDerivedType(tag: DW_TAG_member, name: "max_host_connections", scope: !579, file: !4, line: 123, baseType: !191, size: 64, align: 64, offset: 2752)
!628 = !DIDerivedType(tag: DW_TAG_member, name: "max_total_connections", scope: !579, file: !4, line: 126, baseType: !191, size: 64, align: 64, offset: 2816)
!629 = !DIDerivedType(tag: DW_TAG_member, name: "max_pipeline_length", scope: !579, file: !4, line: 129, baseType: !191, size: 64, align: 64, offset: 2880)
!630 = !DIDerivedType(tag: DW_TAG_member, name: "content_length_penalty_size", scope: !579, file: !4, line: 132, baseType: !191, size: 64, align: 64, offset: 2944)
!631 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_length_penalty_size", scope: !579, file: !4, line: 137, baseType: !191, size: 64, align: 64, offset: 3008)
!632 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining_site_bl", scope: !579, file: !4, line: 141, baseType: !140, size: 256, align: 64, offset: 3072)
!633 = !DIDerivedType(tag: DW_TAG_member, name: "pipelining_server_bl", scope: !579, file: !4, line: 144, baseType: !140, size: 256, align: 64, offset: 3328)
!634 = !DIDerivedType(tag: DW_TAG_member, name: "timer_cb", scope: !579, file: !4, line: 148, baseType: !635, size: 64, align: 64, offset: 3584)
!635 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_multi_timer_callback", file: !124, line: 285, baseType: !636)
!636 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !637, size: 64, align: 64)
!637 = !DISubroutineType(types: !638)
!638 = !{!177, !639, !191, !148}
!639 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !640, size: 64, align: 64)
!640 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLM", file: !124, line: 56, baseType: !579)
!641 = !DIDerivedType(tag: DW_TAG_member, name: "timer_userp", scope: !579, file: !4, line: 149, baseType: !148, size: 64, align: 64, offset: 3648)
!642 = !DIDerivedType(tag: DW_TAG_member, name: "timer_lastcall", scope: !579, file: !4, line: 150, baseType: !201, size: 128, align: 64, offset: 3712)
!643 = !DIDerivedType(tag: DW_TAG_member, name: "multi_easy", scope: !545, file: !130, line: 1824, baseType: !578, size: 64, align: 64, offset: 832)
!644 = !DIDerivedType(tag: DW_TAG_member, name: "share", scope: !545, file: !130, line: 1827, baseType: !645, size: 64, align: 64, offset: 896)
!645 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !646, size: 64, align: 64)
!646 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_share", file: !27, line: 101, flags: DIFlagFwdDecl)
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
!722 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_seek_callback", file: !27, line: 324, baseType: !723)
!723 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !724, size: 64, align: 64)
!724 = !DISubroutineType(types: !725)
!725 = !{!177, !148, !189, !177}
!726 = !DIDerivedType(tag: DW_TAG_member, name: "postfieldsize", scope: !649, file: !130, line: 1582, baseType: !189, size: 64, align: 64, offset: 1024)
!727 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !649, file: !130, line: 1585, baseType: !684, size: 16, align: 16, offset: 1088)
!728 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !649, file: !130, line: 1586, baseType: !177, size: 32, align: 32, offset: 1120)
!729 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_func", scope: !649, file: !130, line: 1588, baseType: !730, size: 64, align: 64, offset: 1152)
!730 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_write_callback", file: !27, line: 223, baseType: !731)
!731 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !732, size: 64, align: 64)
!732 = !DISubroutineType(types: !733)
!733 = !{!158, !215, !158, !158, !148}
!734 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_header", scope: !649, file: !130, line: 1589, baseType: !730, size: 64, align: 64, offset: 1216)
!735 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_rtp", scope: !649, file: !130, line: 1590, baseType: !730, size: 64, align: 64, offset: 1280)
!736 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func_set", scope: !649, file: !130, line: 1591, baseType: !737, size: 64, align: 64, offset: 1344)
!737 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_read_callback", file: !27, line: 335, baseType: !731)
!738 = !DIDerivedType(tag: DW_TAG_member, name: "is_fread_set", scope: !649, file: !130, line: 1592, baseType: !177, size: 32, align: 32, offset: 1408)
!739 = !DIDerivedType(tag: DW_TAG_member, name: "is_fwrite_set", scope: !649, file: !130, line: 1593, baseType: !177, size: 32, align: 32, offset: 1440)
!740 = !DIDerivedType(tag: DW_TAG_member, name: "fprogress", scope: !649, file: !130, line: 1594, baseType: !741, size: 64, align: 64, offset: 1472)
!741 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_progress_callback", file: !27, line: 183, baseType: !742)
!742 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !743, size: 64, align: 64)
!743 = !DISubroutineType(types: !744)
!744 = !{!177, !148, !745, !745, !745, !745}
!745 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!746 = !DIDerivedType(tag: DW_TAG_member, name: "fxferinfo", scope: !649, file: !130, line: 1595, baseType: !747, size: 64, align: 64, offset: 1536)
!747 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_xferinfo_callback", file: !27, line: 191, baseType: !748)
!748 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !749, size: 64, align: 64)
!749 = !DISubroutineType(types: !750)
!750 = !{!177, !148, !189, !189, !189, !189}
!751 = !DIDerivedType(tag: DW_TAG_member, name: "fdebug", scope: !649, file: !130, line: 1596, baseType: !752, size: 64, align: 64, offset: 1600)
!752 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_debug_callback", file: !27, line: 420, baseType: !753)
!753 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !754, size: 64, align: 64)
!754 = !DISubroutineType(types: !755)
!755 = !{!177, !564, !756, !215, !158, !148}
!756 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_infotype", file: !27, line: 418, baseType: !269)
!757 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_func", scope: !649, file: !130, line: 1597, baseType: !758, size: 64, align: 64, offset: 1664)
!758 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ioctl_callback", file: !27, line: 388, baseType: !759)
!759 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !760, size: 64, align: 64)
!760 = !DISubroutineType(types: !761)
!761 = !{!762, !564, !177, !148}
!762 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlioerr", file: !27, line: 380, baseType: !279)
!763 = !DIDerivedType(tag: DW_TAG_member, name: "fsockopt", scope: !649, file: !130, line: 1598, baseType: !764, size: 64, align: 64, offset: 1728)
!764 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sockopt_callback", file: !27, line: 353, baseType: !765)
!765 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !766, size: 64, align: 64)
!766 = !DISubroutineType(types: !767)
!767 = !{!177, !148, !248, !768}
!768 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlsocktype", file: !27, line: 344, baseType: !285)
!769 = !DIDerivedType(tag: DW_TAG_member, name: "sockopt_client", scope: !649, file: !130, line: 1599, baseType: !148, size: 64, align: 64, offset: 1792)
!770 = !DIDerivedType(tag: DW_TAG_member, name: "fopensocket", scope: !649, file: !130, line: 1600, baseType: !771, size: 64, align: 64, offset: 1856)
!771 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_opensocket_callback", file: !27, line: 368, baseType: !772)
!772 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !773, size: 64, align: 64)
!773 = !DISubroutineType(types: !774)
!774 = !{!248, !148, !768, !775}
!775 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !776, size: 64, align: 64)
!776 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_sockaddr", file: !27, line: 357, size: 256, align: 32, elements: !777)
!777 = !{!778, !779, !780, !781, !783}
!778 = !DIDerivedType(tag: DW_TAG_member, name: "family", scope: !776, file: !27, line: 358, baseType: !177, size: 32, align: 32)
!779 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !776, file: !27, line: 359, baseType: !177, size: 32, align: 32, offset: 32)
!780 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !776, file: !27, line: 360, baseType: !177, size: 32, align: 32, offset: 64)
!781 = !DIDerivedType(tag: DW_TAG_member, name: "addrlen", scope: !776, file: !27, line: 361, baseType: !782, size: 32, align: 32, offset: 96)
!782 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!783 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !776, file: !27, line: 364, baseType: !784, size: 128, align: 16, offset: 128)
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
!796 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_closesocket_callback", file: !27, line: 373, baseType: !797)
!797 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !798, size: 64, align: 64)
!798 = !DISubroutineType(types: !799)
!799 = !{!177, !148, !248}
!800 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !649, file: !130, line: 1606, baseType: !148, size: 64, align: 64, offset: 2048)
!801 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !649, file: !130, line: 1608, baseType: !148, size: 64, align: 64, offset: 2112)
!802 = !DIDerivedType(tag: DW_TAG_member, name: "convfromnetwork", scope: !649, file: !130, line: 1611, baseType: !803, size: 64, align: 64, offset: 2176)
!803 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_conv_callback", file: !27, line: 637, baseType: !804)
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
!825 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_slist", file: !27, line: 2176, size: 128, align: 64, elements: !826)
!826 = !{!827, !828}
!827 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !825, file: !27, line: 2177, baseType: !215, size: 64, align: 64)
!828 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !825, file: !27, line: 2178, baseType: !824, size: 64, align: 64, offset: 64)
!829 = !DIDerivedType(tag: DW_TAG_member, name: "proxyheaders", scope: !649, file: !130, line: 1633, baseType: !824, size: 64, align: 64, offset: 3328)
!830 = !DIDerivedType(tag: DW_TAG_member, name: "httppost", scope: !649, file: !130, line: 1634, baseType: !831, size: 64, align: 64, offset: 3392)
!831 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !832, size: 64, align: 64)
!832 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_httppost", file: !27, line: 137, size: 896, align: 64, elements: !833)
!833 = !{!834, !835, !836, !837, !838, !839, !840, !841, !842, !843, !844, !845, !846, !847}
!834 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !832, file: !27, line: 138, baseType: !831, size: 64, align: 64)
!835 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !832, file: !27, line: 139, baseType: !215, size: 64, align: 64, offset: 64)
!836 = !DIDerivedType(tag: DW_TAG_member, name: "namelength", scope: !832, file: !27, line: 140, baseType: !191, size: 64, align: 64, offset: 128)
!837 = !DIDerivedType(tag: DW_TAG_member, name: "contents", scope: !832, file: !27, line: 141, baseType: !215, size: 64, align: 64, offset: 192)
!838 = !DIDerivedType(tag: DW_TAG_member, name: "contentslength", scope: !832, file: !27, line: 142, baseType: !191, size: 64, align: 64, offset: 256)
!839 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !832, file: !27, line: 144, baseType: !215, size: 64, align: 64, offset: 320)
!840 = !DIDerivedType(tag: DW_TAG_member, name: "bufferlength", scope: !832, file: !27, line: 145, baseType: !191, size: 64, align: 64, offset: 384)
!841 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !832, file: !27, line: 146, baseType: !215, size: 64, align: 64, offset: 448)
!842 = !DIDerivedType(tag: DW_TAG_member, name: "contentheader", scope: !832, file: !27, line: 147, baseType: !824, size: 64, align: 64, offset: 512)
!843 = !DIDerivedType(tag: DW_TAG_member, name: "more", scope: !832, file: !27, line: 148, baseType: !831, size: 64, align: 64, offset: 576)
!844 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !832, file: !27, line: 151, baseType: !191, size: 64, align: 64, offset: 640)
!845 = !DIDerivedType(tag: DW_TAG_member, name: "showfilename", scope: !832, file: !27, line: 171, baseType: !215, size: 64, align: 64, offset: 704)
!846 = !DIDerivedType(tag: DW_TAG_member, name: "userp", scope: !832, file: !27, line: 174, baseType: !148, size: 64, align: 64, offset: 768)
!847 = !DIDerivedType(tag: DW_TAG_member, name: "contentlen", scope: !832, file: !27, line: 176, baseType: !189, size: 64, align: 64, offset: 832)
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
!861 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_TimeCond", file: !27, line: 1929, baseType: !290)
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
!890 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ssl_ctx_callback", file: !27, line: 639, baseType: !891)
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
!908 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_proxytype", file: !27, line: 657, baseType: !307)
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
!919 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sshkeycallback", file: !27, line: 739, baseType: !920)
!920 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !921, size: 64, align: 64)
!921 = !DISubroutineType(types: !922)
!922 = !{!177, !564, !923, !923, !328, !148}
!923 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !924, size: 64, align: 64)
!924 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !925)
!925 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_khkey", file: !27, line: 711, size: 192, align: 64, elements: !926)
!926 = !{!927, !930, !931}
!927 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !925, file: !27, line: 712, baseType: !928, size: 64, align: 64)
!928 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !929, size: 64, align: 64)
!929 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !216)
!930 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !925, file: !27, line: 714, baseType: !158, size: 64, align: 64, offset: 64)
!931 = !DIDerivedType(tag: DW_TAG_member, name: "keytype", scope: !925, file: !27, line: 715, baseType: !322, size: 32, align: 32, offset: 128)
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
!960 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_usessl", file: !27, line: 752, baseType: !340)
!961 = !DIDerivedType(tag: DW_TAG_member, name: "ftpsslauth", scope: !649, file: !130, line: 1714, baseType: !962, size: 32, align: 32, offset: 8160)
!962 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpauth", file: !27, line: 795, baseType: !347)
!963 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_ccc", scope: !649, file: !130, line: 1715, baseType: !964, size: 32, align: 32, offset: 8192)
!964 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpccc", file: !27, line: 787, baseType: !353)
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
!991 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_bgn_callback", file: !27, line: 292, baseType: !992)
!992 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !993, size: 64, align: 64)
!993 = !DISubroutineType(types: !994)
!994 = !{!191, !995, !148, !177}
!995 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !996, size: 64, align: 64)
!996 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!997 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_end", scope: !649, file: !130, line: 1747, baseType: !998, size: 64, align: 64, offset: 12736)
!998 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_end_callback", file: !27, line: 306, baseType: !999)
!999 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1000, size: 64, align: 64)
!1000 = !DISubroutineType(types: !1001)
!1001 = !{!191, !148}
!1002 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch", scope: !649, file: !130, line: 1749, baseType: !1003, size: 64, align: 64, offset: 12800)
!1003 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_fnmatch_callback", file: !27, line: 315, baseType: !1004)
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
!1243 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_certinfo", file: !27, line: 2214, size: 128, align: 64, elements: !1244)
!1244 = !{!1245, !1246}
!1245 = !DIDerivedType(tag: DW_TAG_member, name: "num_of_certs", scope: !1243, file: !27, line: 2215, baseType: !177, size: 32, align: 32)
!1246 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !1243, file: !27, line: 2216, baseType: !1247, size: 64, align: 64, offset: 64)
!1247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !824, size: 64, align: 64)
!1248 = !DIDerivedType(tag: DW_TAG_member, name: "tsi", scope: !545, file: !130, line: 1840, baseType: !1249, size: 128, align: 64, offset: 160000)
!1249 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_tlssessioninfo", file: !27, line: 2245, size: 128, align: 64, elements: !1250)
!1250 = !{!1251, !1253}
!1251 = !DIDerivedType(tag: DW_TAG_member, name: "backend", scope: !1249, file: !27, line: 2246, baseType: !1252, size: 32, align: 32)
!1252 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sslbackend", file: !27, line: 2235, baseType: !385)
!1253 = !DIDerivedType(tag: DW_TAG_member, name: "internals", scope: !1249, file: !27, line: 2247, baseType: !148, size: 64, align: 64, offset: 64)
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
!1678 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !785, line: 171, size: 32, align: 32, elements: !1679)
!1679 = !{!1680, !1681, !1682, !1683, !1684, !1685, !1686, !1687, !1688, !1689, !1690, !1691, !1692, !1693, !1694, !1695, !1696, !1697, !1698}
!1680 = !DIEnumerator(name: "MSG_OOB", value: 1)
!1681 = !DIEnumerator(name: "MSG_PEEK", value: 2)
!1682 = !DIEnumerator(name: "MSG_DONTROUTE", value: 4)
!1683 = !DIEnumerator(name: "MSG_CTRUNC", value: 8)
!1684 = !DIEnumerator(name: "MSG_PROXY", value: 16)
!1685 = !DIEnumerator(name: "MSG_TRUNC", value: 32)
!1686 = !DIEnumerator(name: "MSG_DONTWAIT", value: 64)
!1687 = !DIEnumerator(name: "MSG_EOR", value: 128)
!1688 = !DIEnumerator(name: "MSG_WAITALL", value: 256)
!1689 = !DIEnumerator(name: "MSG_FIN", value: 512)
!1690 = !DIEnumerator(name: "MSG_SYN", value: 1024)
!1691 = !DIEnumerator(name: "MSG_CONFIRM", value: 2048)
!1692 = !DIEnumerator(name: "MSG_RST", value: 4096)
!1693 = !DIEnumerator(name: "MSG_ERRQUEUE", value: 8192)
!1694 = !DIEnumerator(name: "MSG_NOSIGNAL", value: 16384)
!1695 = !DIEnumerator(name: "MSG_MORE", value: 32768)
!1696 = !DIEnumerator(name: "MSG_WAITFORONE", value: 65536)
!1697 = !DIEnumerator(name: "MSG_FASTOPEN", value: 536870912)
!1698 = !DIEnumerator(name: "MSG_CMSG_CLOEXEC", value: 1073741824)
!1699 = !{!158, !256, !177, !148, !191}
!1700 = !{!1701, !1705, !1708, !1709, !1712, !1715, !1716, !1717, !1718, !1721, !1722, !1725, !1728, !1731, !1734, !1737}
!1701 = distinct !DISubprogram(name: "Curl_recv_has_postponed_data", scope: !1, file: !1, line: 212, type: !1702, isLocal: false, isDefinition: true, scopeLine: 213, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1702 = !DISubroutineType(types: !1703)
!1703 = !{!211, !550, !177}
!1704 = !{}
!1705 = distinct !DISubprogram(name: "Curl_infof", scope: !1, file: !1, line: 224, type: !1706, isLocal: false, isDefinition: true, scopeLine: 225, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1706 = !DISubroutineType(types: !1707)
!1707 = !{null, !544, !928, null}
!1708 = distinct !DISubprogram(name: "Curl_failf", scope: !1, file: !1, line: 242, type: !1706, isLocal: false, isDefinition: true, scopeLine: 243, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1709 = distinct !DISubprogram(name: "Curl_sendf", scope: !1, file: !1, line: 267, type: !1710, isLocal: false, isDefinition: true, scopeLine: 269, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1710 = !DISubroutineType(types: !1711)
!1711 = !{!554, !248, !550, !928, null}
!1712 = distinct !DISubprogram(name: "Curl_write", scope: !1, file: !1, line: 319, type: !1713, isLocal: false, isDefinition: true, scopeLine: 324, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1713 = !DISubroutineType(types: !1714)
!1714 = !{!554, !550, !248, !995, !158, !1459}
!1715 = distinct !DISubprogram(name: "Curl_send_plain", scope: !1, file: !1, line: 352, type: !1355, isLocal: false, isDefinition: true, scopeLine: 354, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1716 = distinct !DISubprogram(name: "Curl_write_plain", scope: !1, file: !1, line: 409, type: !1713, isLocal: false, isDefinition: true, scopeLine: 414, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1717 = distinct !DISubprogram(name: "Curl_recv_plain", scope: !1, file: !1, line: 426, type: !1348, isLocal: false, isDefinition: true, scopeLine: 428, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1718 = distinct !DISubprogram(name: "Curl_client_chop_write", scope: !1, file: !1, line: 540, type: !1719, isLocal: false, isDefinition: true, scopeLine: 544, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1719 = !DISubroutineType(types: !1720)
!1720 = !{!554, !550, !177, !215, !158}
!1721 = distinct !DISubprogram(name: "Curl_client_write", scope: !1, file: !1, line: 625, type: !1719, isLocal: false, isDefinition: true, scopeLine: 629, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1722 = distinct !DISubprogram(name: "Curl_read_plain", scope: !1, file: !1, line: 656, type: !1723, isLocal: false, isDefinition: true, scopeLine: 660, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1723 = !DISubroutineType(types: !1724)
!1724 = !{!554, !248, !215, !158, !1459}
!1725 = distinct !DISubprogram(name: "Curl_read", scope: !1, file: !1, line: 687, type: !1726, isLocal: false, isDefinition: true, scopeLine: 692, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1726 = !DISubroutineType(types: !1727)
!1727 = !{!554, !550, !248, !215, !158, !1459}
!1728 = distinct !DISubprogram(name: "Curl_debug", scope: !1, file: !1, line: 820, type: !1729, isLocal: false, isDefinition: true, scopeLine: 823, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1729 = !DISubroutineType(types: !1730)
!1730 = !{!177, !544, !756, !215, !158, !550}
!1731 = distinct !DISubprogram(name: "pausewrite", scope: !1, file: !1, line: 469, type: !1732, isLocal: true, isDefinition: true, scopeLine: 473, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1732 = !DISubroutineType(types: !1733)
!1733 = !{!554, !544, !177, !928, !158}
!1734 = distinct !DISubprogram(name: "convert_lineends", scope: !1, file: !1, line: 50, type: !1735, isLocal: true, isDefinition: true, scopeLine: 52, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1735 = !DISubroutineType(types: !1736)
!1736 = !{!158, !544, !215, !158}
!1737 = distinct !DISubprogram(name: "showit", scope: !1, file: !1, line: 751, type: !1738, isLocal: true, isDefinition: true, scopeLine: 753, flags: DIFlagPrototyped, isOptimized: false, variables: !1704)
!1738 = !DISubroutineType(types: !1739)
!1739 = !{!177, !544, !756, !215, !158}
!1740 = !{!1741}
!1741 = !DIGlobalVariable(name: "s_infotype", scope: !1737, file: !1, line: 754, type: !1742, isLocal: true, isDefinition: true, variable: [7 x [3 x i8]]* @showit.s_infotype)
!1742 = !DICompositeType(tag: DW_TAG_array_type, baseType: !929, size: 168, align: 8, elements: !1743)
!1743 = !{!1744, !1144}
!1744 = !DISubrange(count: 7)
!1745 = !{i32 2, !"Dwarf Version", i32 4}
!1746 = !{i32 2, !"Debug Info Version", i32 3}
!1747 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!1748 = !DILocalVariable(name: "conn", arg: 1, scope: !1701, file: !1, line: 212, type: !550)
!1749 = !DIExpression()
!1750 = !DILocation(line: 212, column: 55, scope: !1701)
!1751 = !DILocalVariable(name: "sockindex", arg: 2, scope: !1701, file: !1, line: 212, type: !177)
!1752 = !DILocation(line: 212, column: 65, scope: !1701)
!1753 = !DILocation(line: 214, column: 9, scope: !1701)
!1754 = !DILocation(line: 215, column: 9, scope: !1701)
!1755 = !DILocation(line: 216, column: 3, scope: !1701)
!1756 = !DILocalVariable(name: "data", arg: 1, scope: !1705, file: !1, line: 224, type: !544)
!1757 = !DILocation(line: 224, column: 35, scope: !1705)
!1758 = !DILocalVariable(name: "fmt", arg: 2, scope: !1705, file: !1, line: 224, type: !928)
!1759 = !DILocation(line: 224, column: 53, scope: !1705)
!1760 = !DILocation(line: 226, column: 6, scope: !1761)
!1761 = distinct !DILexicalBlock(scope: !1705, file: !1, line: 226, column: 6)
!1762 = !DILocation(line: 226, column: 11, scope: !1761)
!1763 = !DILocation(line: 226, column: 14, scope: !1764)
!1764 = !DILexicalBlockFile(scope: !1761, file: !1, discriminator: 1)
!1765 = !DILocation(line: 226, column: 20, scope: !1764)
!1766 = !DILocation(line: 226, column: 24, scope: !1764)
!1767 = !DILocation(line: 226, column: 6, scope: !1764)
!1768 = !DILocalVariable(name: "ap", scope: !1769, file: !1, line: 227, type: !1770)
!1769 = distinct !DILexicalBlock(scope: !1761, file: !1, line: 226, column: 33)
!1770 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !654, line: 79, baseType: !1771)
!1771 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !1772, line: 50, baseType: !1773)
!1772 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1773 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 227, baseType: !1774)
!1774 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1775, size: 192, align: 64, elements: !689)
!1775 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 227, size: 192, align: 64, elements: !1776)
!1776 = !{!1777, !1778, !1779, !1780}
!1777 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !1775, file: !1, line: 227, baseType: !782, size: 32, align: 32)
!1778 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !1775, file: !1, line: 227, baseType: !782, size: 32, align: 32, offset: 32)
!1779 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !1775, file: !1, line: 227, baseType: !148, size: 64, align: 64, offset: 64)
!1780 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !1775, file: !1, line: 227, baseType: !148, size: 64, align: 64, offset: 128)
!1781 = !DILocation(line: 227, column: 13, scope: !1769)
!1782 = !DILocalVariable(name: "len", scope: !1769, file: !1, line: 228, type: !158)
!1783 = !DILocation(line: 228, column: 12, scope: !1769)
!1784 = !DILocalVariable(name: "print_buffer", scope: !1769, file: !1, line: 229, type: !1785)
!1785 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 16392, align: 8, elements: !1786)
!1786 = !{!1787}
!1787 = !DISubrange(count: 2049)
!1788 = !DILocation(line: 229, column: 10, scope: !1769)
!1789 = !DILocation(line: 230, column: 5, scope: !1769)
!1790 = !DILocation(line: 231, column: 15, scope: !1769)
!1791 = !DILocation(line: 231, column: 51, scope: !1769)
!1792 = !DILocation(line: 231, column: 56, scope: !1769)
!1793 = !DILocation(line: 231, column: 5, scope: !1769)
!1794 = !DILocation(line: 232, column: 5, scope: !1769)
!1795 = !DILocation(line: 233, column: 18, scope: !1769)
!1796 = !DILocation(line: 233, column: 11, scope: !1769)
!1797 = !DILocation(line: 233, column: 9, scope: !1769)
!1798 = !DILocation(line: 234, column: 16, scope: !1769)
!1799 = !DILocation(line: 234, column: 37, scope: !1769)
!1800 = !DILocation(line: 234, column: 51, scope: !1769)
!1801 = !DILocation(line: 234, column: 5, scope: !1769)
!1802 = !DILocation(line: 235, column: 3, scope: !1769)
!1803 = !DILocation(line: 236, column: 1, scope: !1705)
!1804 = !DILocalVariable(name: "data", arg: 1, scope: !1728, file: !1, line: 820, type: !544)
!1805 = !DILocation(line: 820, column: 34, scope: !1728)
!1806 = !DILocalVariable(name: "type", arg: 2, scope: !1728, file: !1, line: 820, type: !756)
!1807 = !DILocation(line: 820, column: 54, scope: !1728)
!1808 = !DILocalVariable(name: "ptr", arg: 3, scope: !1728, file: !1, line: 821, type: !215)
!1809 = !DILocation(line: 821, column: 22, scope: !1728)
!1810 = !DILocalVariable(name: "size", arg: 4, scope: !1728, file: !1, line: 821, type: !158)
!1811 = !DILocation(line: 821, column: 34, scope: !1728)
!1812 = !DILocalVariable(name: "conn", arg: 5, scope: !1728, file: !1, line: 822, type: !550)
!1813 = !DILocation(line: 822, column: 36, scope: !1728)
!1814 = !DILocalVariable(name: "rc", scope: !1728, file: !1, line: 824, type: !177)
!1815 = !DILocation(line: 824, column: 7, scope: !1728)
!1816 = !DILocation(line: 825, column: 6, scope: !1817)
!1817 = distinct !DILexicalBlock(scope: !1728, file: !1, line: 825, column: 6)
!1818 = !DILocation(line: 825, column: 12, scope: !1817)
!1819 = !DILocation(line: 825, column: 16, scope: !1817)
!1820 = !DILocation(line: 825, column: 26, scope: !1817)
!1821 = !DILocation(line: 825, column: 29, scope: !1822)
!1822 = !DILexicalBlockFile(scope: !1817, file: !1, discriminator: 1)
!1823 = !DILocation(line: 825, column: 34, scope: !1822)
!1824 = !DILocation(line: 825, column: 37, scope: !1825)
!1825 = !DILexicalBlockFile(scope: !1817, file: !1, discriminator: 2)
!1826 = !DILocation(line: 825, column: 43, scope: !1825)
!1827 = !DILocation(line: 825, column: 48, scope: !1825)
!1828 = !DILocation(line: 825, column: 6, scope: !1825)
!1829 = !DILocalVariable(name: "buffer", scope: !1830, file: !1, line: 826, type: !1831)
!1830 = distinct !DILexicalBlock(scope: !1817, file: !1, line: 825, column: 58)
!1831 = !DICompositeType(tag: DW_TAG_array_type, baseType: !216, size: 1280, align: 8, elements: !1832)
!1832 = !{!1833}
!1833 = !DISubrange(count: 160)
!1834 = !DILocation(line: 826, column: 10, scope: !1830)
!1835 = !DILocalVariable(name: "t", scope: !1830, file: !1, line: 827, type: !928)
!1836 = !DILocation(line: 827, column: 17, scope: !1830)
!1837 = !DILocalVariable(name: "w", scope: !1830, file: !1, line: 828, type: !928)
!1838 = !DILocation(line: 828, column: 17, scope: !1830)
!1839 = !DILocation(line: 829, column: 12, scope: !1830)
!1840 = !DILocation(line: 829, column: 5, scope: !1830)
!1841 = !DILocation(line: 831, column: 9, scope: !1842)
!1842 = distinct !DILexicalBlock(scope: !1830, file: !1, line: 829, column: 18)
!1843 = !DILocation(line: 831, column: 7, scope: !1842)
!1844 = !DILocation(line: 834, column: 9, scope: !1842)
!1845 = !DILocation(line: 835, column: 7, scope: !1842)
!1846 = !DILocation(line: 837, column: 9, scope: !1842)
!1847 = !DILocation(line: 837, column: 7, scope: !1842)
!1848 = !DILocation(line: 840, column: 9, scope: !1842)
!1849 = !DILocation(line: 841, column: 7, scope: !1842)
!1850 = !DILocation(line: 843, column: 7, scope: !1842)
!1851 = !DILocation(line: 846, column: 8, scope: !1852)
!1852 = distinct !DILexicalBlock(scope: !1830, file: !1, line: 846, column: 8)
!1853 = !DILocation(line: 846, column: 8, scope: !1830)
!1854 = !DILocation(line: 847, column: 16, scope: !1855)
!1855 = distinct !DILexicalBlock(scope: !1852, file: !1, line: 846, column: 11)
!1856 = !DILocation(line: 847, column: 54, scope: !1855)
!1857 = !DILocation(line: 847, column: 57, scope: !1855)
!1858 = !DILocation(line: 848, column: 16, scope: !1855)
!1859 = !DILocation(line: 848, column: 22, scope: !1855)
!1860 = !DILocation(line: 848, column: 27, scope: !1855)
!1861 = !DILocation(line: 847, column: 7, scope: !1855)
!1862 = !DILocation(line: 849, column: 19, scope: !1855)
!1863 = !DILocation(line: 849, column: 40, scope: !1855)
!1864 = !DILocation(line: 849, column: 55, scope: !1855)
!1865 = !DILocation(line: 849, column: 48, scope: !1855)
!1866 = !DILocation(line: 849, column: 12, scope: !1867)
!1867 = !DILexicalBlockFile(scope: !1855, file: !1, discriminator: 1)
!1868 = !DILocation(line: 849, column: 10, scope: !1855)
!1869 = !DILocation(line: 850, column: 10, scope: !1870)
!1870 = distinct !DILexicalBlock(scope: !1855, file: !1, line: 850, column: 10)
!1871 = !DILocation(line: 850, column: 10, scope: !1855)
!1872 = !DILocation(line: 851, column: 16, scope: !1870)
!1873 = !DILocation(line: 851, column: 9, scope: !1870)
!1874 = !DILocation(line: 852, column: 5, scope: !1855)
!1875 = !DILocation(line: 853, column: 3, scope: !1830)
!1876 = !DILocation(line: 854, column: 15, scope: !1728)
!1877 = !DILocation(line: 854, column: 21, scope: !1728)
!1878 = !DILocation(line: 854, column: 27, scope: !1728)
!1879 = !DILocation(line: 854, column: 32, scope: !1728)
!1880 = !DILocation(line: 854, column: 8, scope: !1728)
!1881 = !DILocation(line: 854, column: 6, scope: !1728)
!1882 = !DILocation(line: 855, column: 10, scope: !1728)
!1883 = !DILocation(line: 855, column: 3, scope: !1728)
!1884 = !DILocation(line: 856, column: 1, scope: !1728)
!1885 = !DILocalVariable(name: "data", arg: 1, scope: !1708, file: !1, line: 242, type: !544)
!1886 = !DILocation(line: 242, column: 35, scope: !1708)
!1887 = !DILocalVariable(name: "fmt", arg: 2, scope: !1708, file: !1, line: 242, type: !928)
!1888 = !DILocation(line: 242, column: 53, scope: !1708)
!1889 = !DILocalVariable(name: "ap", scope: !1708, file: !1, line: 244, type: !1770)
!1890 = !DILocation(line: 244, column: 11, scope: !1708)
!1891 = !DILocalVariable(name: "len", scope: !1708, file: !1, line: 245, type: !158)
!1892 = !DILocation(line: 245, column: 10, scope: !1708)
!1893 = !DILocation(line: 246, column: 3, scope: !1708)
!1894 = !DILocation(line: 248, column: 13, scope: !1708)
!1895 = !DILocation(line: 248, column: 19, scope: !1708)
!1896 = !DILocation(line: 248, column: 25, scope: !1708)
!1897 = !DILocation(line: 248, column: 42, scope: !1708)
!1898 = !DILocation(line: 248, column: 47, scope: !1708)
!1899 = !DILocation(line: 248, column: 3, scope: !1708)
!1900 = !DILocation(line: 250, column: 6, scope: !1901)
!1901 = distinct !DILexicalBlock(scope: !1708, file: !1, line: 250, column: 6)
!1902 = !DILocation(line: 250, column: 12, scope: !1901)
!1903 = !DILocation(line: 250, column: 16, scope: !1901)
!1904 = !DILocation(line: 250, column: 28, scope: !1901)
!1905 = !DILocation(line: 250, column: 32, scope: !1906)
!1906 = !DILexicalBlockFile(scope: !1901, file: !1, discriminator: 1)
!1907 = !DILocation(line: 250, column: 38, scope: !1906)
!1908 = !DILocation(line: 250, column: 44, scope: !1906)
!1909 = !DILocation(line: 250, column: 6, scope: !1906)
!1910 = !DILocation(line: 251, column: 14, scope: !1911)
!1911 = distinct !DILexicalBlock(scope: !1901, file: !1, line: 250, column: 54)
!1912 = !DILocation(line: 251, column: 20, scope: !1911)
!1913 = !DILocation(line: 251, column: 24, scope: !1911)
!1914 = !DILocation(line: 251, column: 60, scope: !1911)
!1915 = !DILocation(line: 251, column: 66, scope: !1911)
!1916 = !DILocation(line: 251, column: 72, scope: !1911)
!1917 = !DILocation(line: 251, column: 5, scope: !1911)
!1918 = !DILocation(line: 252, column: 5, scope: !1911)
!1919 = !DILocation(line: 252, column: 11, scope: !1911)
!1920 = !DILocation(line: 252, column: 17, scope: !1911)
!1921 = !DILocation(line: 252, column: 26, scope: !1911)
!1922 = !DILocation(line: 253, column: 3, scope: !1911)
!1923 = !DILocation(line: 254, column: 6, scope: !1924)
!1924 = distinct !DILexicalBlock(scope: !1708, file: !1, line: 254, column: 6)
!1925 = !DILocation(line: 254, column: 12, scope: !1924)
!1926 = !DILocation(line: 254, column: 16, scope: !1924)
!1927 = !DILocation(line: 254, column: 6, scope: !1708)
!1928 = !DILocation(line: 255, column: 18, scope: !1929)
!1929 = distinct !DILexicalBlock(scope: !1924, file: !1, line: 254, column: 25)
!1930 = !DILocation(line: 255, column: 24, scope: !1929)
!1931 = !DILocation(line: 255, column: 30, scope: !1929)
!1932 = !DILocation(line: 255, column: 11, scope: !1929)
!1933 = !DILocation(line: 255, column: 9, scope: !1929)
!1934 = !DILocation(line: 256, column: 8, scope: !1935)
!1935 = distinct !DILexicalBlock(scope: !1929, file: !1, line: 256, column: 8)
!1936 = !DILocation(line: 256, column: 12, scope: !1935)
!1937 = !DILocation(line: 256, column: 8, scope: !1929)
!1938 = !DILocation(line: 257, column: 26, scope: !1939)
!1939 = distinct !DILexicalBlock(scope: !1935, file: !1, line: 256, column: 27)
!1940 = !DILocation(line: 257, column: 7, scope: !1939)
!1941 = !DILocation(line: 257, column: 13, scope: !1939)
!1942 = !DILocation(line: 257, column: 19, scope: !1939)
!1943 = !DILocation(line: 257, column: 31, scope: !1939)
!1944 = !DILocation(line: 258, column: 26, scope: !1939)
!1945 = !DILocation(line: 258, column: 7, scope: !1939)
!1946 = !DILocation(line: 258, column: 13, scope: !1939)
!1947 = !DILocation(line: 258, column: 19, scope: !1939)
!1948 = !DILocation(line: 258, column: 33, scope: !1939)
!1949 = !DILocation(line: 259, column: 5, scope: !1939)
!1950 = !DILocation(line: 260, column: 16, scope: !1929)
!1951 = !DILocation(line: 260, column: 37, scope: !1929)
!1952 = !DILocation(line: 260, column: 43, scope: !1929)
!1953 = !DILocation(line: 260, column: 49, scope: !1929)
!1954 = !DILocation(line: 260, column: 57, scope: !1929)
!1955 = !DILocation(line: 260, column: 5, scope: !1929)
!1956 = !DILocation(line: 261, column: 3, scope: !1929)
!1957 = !DILocation(line: 263, column: 3, scope: !1708)
!1958 = !DILocation(line: 264, column: 1, scope: !1708)
!1959 = !DILocalVariable(name: "sockfd", arg: 1, scope: !1709, file: !1, line: 267, type: !248)
!1960 = !DILocation(line: 267, column: 35, scope: !1709)
!1961 = !DILocalVariable(name: "conn", arg: 2, scope: !1709, file: !1, line: 267, type: !550)
!1962 = !DILocation(line: 267, column: 63, scope: !1709)
!1963 = !DILocalVariable(name: "fmt", arg: 3, scope: !1709, file: !1, line: 268, type: !928)
!1964 = !DILocation(line: 268, column: 33, scope: !1709)
!1965 = !DILocalVariable(name: "data", scope: !1709, file: !1, line: 270, type: !544)
!1966 = !DILocation(line: 270, column: 21, scope: !1709)
!1967 = !DILocation(line: 270, column: 28, scope: !1709)
!1968 = !DILocation(line: 270, column: 34, scope: !1709)
!1969 = !DILocalVariable(name: "bytes_written", scope: !1709, file: !1, line: 271, type: !256)
!1970 = !DILocation(line: 271, column: 11, scope: !1709)
!1971 = !DILocalVariable(name: "write_len", scope: !1709, file: !1, line: 272, type: !158)
!1972 = !DILocation(line: 272, column: 10, scope: !1709)
!1973 = !DILocalVariable(name: "result", scope: !1709, file: !1, line: 273, type: !554)
!1974 = !DILocation(line: 273, column: 12, scope: !1709)
!1975 = !DILocalVariable(name: "s", scope: !1709, file: !1, line: 274, type: !215)
!1976 = !DILocation(line: 274, column: 9, scope: !1709)
!1977 = !DILocalVariable(name: "sptr", scope: !1709, file: !1, line: 275, type: !215)
!1978 = !DILocation(line: 275, column: 9, scope: !1709)
!1979 = !DILocalVariable(name: "ap", scope: !1709, file: !1, line: 276, type: !1770)
!1980 = !DILocation(line: 276, column: 11, scope: !1709)
!1981 = !DILocation(line: 277, column: 3, scope: !1709)
!1982 = !DILocation(line: 278, column: 16, scope: !1709)
!1983 = !DILocation(line: 278, column: 21, scope: !1709)
!1984 = !DILocation(line: 278, column: 7, scope: !1709)
!1985 = !DILocation(line: 278, column: 5, scope: !1709)
!1986 = !DILocation(line: 279, column: 3, scope: !1709)
!1987 = !DILocation(line: 280, column: 7, scope: !1988)
!1988 = distinct !DILexicalBlock(scope: !1709, file: !1, line: 280, column: 6)
!1989 = !DILocation(line: 280, column: 6, scope: !1709)
!1990 = !DILocation(line: 281, column: 5, scope: !1988)
!1991 = !DILocation(line: 283, column: 16, scope: !1709)
!1992 = !DILocation(line: 284, column: 22, scope: !1709)
!1993 = !DILocation(line: 284, column: 15, scope: !1709)
!1994 = !DILocation(line: 284, column: 13, scope: !1709)
!1995 = !DILocation(line: 285, column: 10, scope: !1709)
!1996 = !DILocation(line: 285, column: 8, scope: !1709)
!1997 = !DILocation(line: 287, column: 3, scope: !1709)
!1998 = !DILocation(line: 289, column: 25, scope: !1999)
!1999 = distinct !DILexicalBlock(scope: !2000, file: !1, line: 287, column: 11)
!2000 = distinct !DILexicalBlock(scope: !2001, file: !1, line: 287, column: 3)
!2001 = distinct !DILexicalBlock(scope: !1709, file: !1, line: 287, column: 3)
!2002 = !DILocation(line: 289, column: 31, scope: !1999)
!2003 = !DILocation(line: 289, column: 39, scope: !1999)
!2004 = !DILocation(line: 289, column: 45, scope: !1999)
!2005 = !DILocation(line: 289, column: 14, scope: !1999)
!2006 = !DILocation(line: 289, column: 12, scope: !1999)
!2007 = !DILocation(line: 291, column: 8, scope: !2008)
!2008 = distinct !DILexicalBlock(scope: !1999, file: !1, line: 291, column: 8)
!2009 = !DILocation(line: 291, column: 8, scope: !1999)
!2010 = !DILocation(line: 292, column: 7, scope: !2008)
!2011 = !DILocation(line: 294, column: 8, scope: !2012)
!2012 = distinct !DILexicalBlock(scope: !1999, file: !1, line: 294, column: 8)
!2013 = !DILocation(line: 294, column: 14, scope: !2012)
!2014 = !DILocation(line: 294, column: 18, scope: !2012)
!2015 = !DILocation(line: 294, column: 8, scope: !1999)
!2016 = !DILocation(line: 295, column: 18, scope: !2012)
!2017 = !DILocation(line: 295, column: 43, scope: !2012)
!2018 = !DILocation(line: 295, column: 57, scope: !2012)
!2019 = !DILocation(line: 295, column: 72, scope: !2012)
!2020 = !DILocation(line: 295, column: 7, scope: !2012)
!2021 = !DILocation(line: 297, column: 16, scope: !2022)
!2022 = distinct !DILexicalBlock(scope: !1999, file: !1, line: 297, column: 8)
!2023 = !DILocation(line: 297, column: 33, scope: !2022)
!2024 = !DILocation(line: 297, column: 30, scope: !2022)
!2025 = !DILocation(line: 297, column: 8, scope: !1999)
!2026 = !DILocation(line: 300, column: 20, scope: !2027)
!2027 = distinct !DILexicalBlock(scope: !2022, file: !1, line: 297, column: 44)
!2028 = !DILocation(line: 300, column: 17, scope: !2027)
!2029 = !DILocation(line: 301, column: 15, scope: !2027)
!2030 = !DILocation(line: 301, column: 12, scope: !2027)
!2031 = !DILocation(line: 302, column: 5, scope: !2027)
!2032 = !DILocation(line: 304, column: 7, scope: !2022)
!2033 = !DILocation(line: 287, column: 3, scope: !2034)
!2034 = !DILexicalBlockFile(scope: !2000, file: !1, discriminator: 1)
!2035 = !DILocation(line: 307, column: 3, scope: !1709)
!2036 = !DILocation(line: 309, column: 10, scope: !1709)
!2037 = !DILocation(line: 309, column: 3, scope: !1709)
!2038 = !DILocation(line: 310, column: 1, scope: !1709)
!2039 = !DILocalVariable(name: "conn", arg: 1, scope: !1712, file: !1, line: 319, type: !550)
!2040 = !DILocation(line: 319, column: 41, scope: !1712)
!2041 = !DILocalVariable(name: "sockfd", arg: 2, scope: !1712, file: !1, line: 320, type: !248)
!2042 = !DILocation(line: 320, column: 35, scope: !1712)
!2043 = !DILocalVariable(name: "mem", arg: 3, scope: !1712, file: !1, line: 321, type: !995)
!2044 = !DILocation(line: 321, column: 33, scope: !1712)
!2045 = !DILocalVariable(name: "len", arg: 4, scope: !1712, file: !1, line: 322, type: !158)
!2046 = !DILocation(line: 322, column: 28, scope: !1712)
!2047 = !DILocalVariable(name: "written", arg: 5, scope: !1712, file: !1, line: 323, type: !1459)
!2048 = !DILocation(line: 323, column: 30, scope: !1712)
!2049 = !DILocalVariable(name: "bytes_written", scope: !1712, file: !1, line: 325, type: !256)
!2050 = !DILocation(line: 325, column: 11, scope: !1712)
!2051 = !DILocalVariable(name: "result", scope: !1712, file: !1, line: 326, type: !554)
!2052 = !DILocation(line: 326, column: 12, scope: !1712)
!2053 = !DILocalVariable(name: "num", scope: !1712, file: !1, line: 327, type: !177)
!2054 = !DILocation(line: 327, column: 7, scope: !1712)
!2055 = !DILocation(line: 327, column: 14, scope: !1712)
!2056 = !DILocation(line: 327, column: 24, scope: !1712)
!2057 = !DILocation(line: 327, column: 30, scope: !1712)
!2058 = !DILocation(line: 327, column: 21, scope: !1712)
!2059 = !DILocation(line: 329, column: 30, scope: !1712)
!2060 = !DILocation(line: 329, column: 19, scope: !1712)
!2061 = !DILocation(line: 329, column: 25, scope: !1712)
!2062 = !DILocation(line: 329, column: 35, scope: !1712)
!2063 = !DILocation(line: 329, column: 41, scope: !1712)
!2064 = !DILocation(line: 329, column: 46, scope: !1712)
!2065 = !DILocation(line: 329, column: 51, scope: !1712)
!2066 = !DILocation(line: 329, column: 17, scope: !1712)
!2067 = !DILocation(line: 331, column: 14, scope: !1712)
!2068 = !DILocation(line: 331, column: 4, scope: !1712)
!2069 = !DILocation(line: 331, column: 12, scope: !1712)
!2070 = !DILocation(line: 332, column: 6, scope: !2071)
!2071 = distinct !DILexicalBlock(scope: !1712, file: !1, line: 332, column: 6)
!2072 = !DILocation(line: 332, column: 20, scope: !2071)
!2073 = !DILocation(line: 332, column: 6, scope: !1712)
!2074 = !DILocation(line: 334, column: 5, scope: !2071)
!2075 = !DILocation(line: 337, column: 10, scope: !1712)
!2076 = !DILocation(line: 337, column: 3, scope: !1712)
!2077 = !DILocation(line: 339, column: 6, scope: !2078)
!2078 = distinct !DILexicalBlock(scope: !1712, file: !1, line: 337, column: 18)
!2079 = !DILocation(line: 339, column: 14, scope: !2078)
!2080 = !DILocation(line: 340, column: 5, scope: !2078)
!2081 = !DILocation(line: 344, column: 5, scope: !2078)
!2082 = !DILocation(line: 348, column: 12, scope: !2078)
!2083 = !DILocation(line: 348, column: 5, scope: !2078)
!2084 = !DILocation(line: 350, column: 1, scope: !1712)
!2085 = !DILocalVariable(name: "conn", arg: 1, scope: !1715, file: !1, line: 352, type: !550)
!2086 = !DILocation(line: 352, column: 45, scope: !1715)
!2087 = !DILocalVariable(name: "num", arg: 2, scope: !1715, file: !1, line: 352, type: !177)
!2088 = !DILocation(line: 352, column: 55, scope: !1715)
!2089 = !DILocalVariable(name: "mem", arg: 3, scope: !1715, file: !1, line: 353, type: !995)
!2090 = !DILocation(line: 353, column: 37, scope: !1715)
!2091 = !DILocalVariable(name: "len", arg: 4, scope: !1715, file: !1, line: 353, type: !158)
!2092 = !DILocation(line: 353, column: 49, scope: !1715)
!2093 = !DILocalVariable(name: "code", arg: 5, scope: !1715, file: !1, line: 353, type: !1350)
!2094 = !DILocation(line: 353, column: 64, scope: !1715)
!2095 = !DILocalVariable(name: "sockfd", scope: !1715, file: !1, line: 355, type: !248)
!2096 = !DILocation(line: 355, column: 17, scope: !1715)
!2097 = !DILocation(line: 355, column: 37, scope: !1715)
!2098 = !DILocation(line: 355, column: 26, scope: !1715)
!2099 = !DILocation(line: 355, column: 32, scope: !1715)
!2100 = !DILocalVariable(name: "bytes_written", scope: !1715, file: !1, line: 356, type: !256)
!2101 = !DILocation(line: 356, column: 11, scope: !1715)
!2102 = !DILocation(line: 362, column: 3, scope: !1715)
!2103 = !DILocation(line: 362, column: 3, scope: !2104)
!2104 = !DILexicalBlockFile(scope: !2105, file: !1, discriminator: 1)
!2105 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 362, column: 3)
!2106 = !DILocation(line: 365, column: 6, scope: !2107)
!2107 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 365, column: 6)
!2108 = !DILocation(line: 365, column: 12, scope: !2107)
!2109 = !DILocation(line: 365, column: 17, scope: !2107)
!2110 = !DILocation(line: 365, column: 6, scope: !1715)
!2111 = !DILocation(line: 366, column: 28, scope: !2112)
!2112 = distinct !DILexicalBlock(scope: !2107, file: !1, line: 365, column: 31)
!2113 = !DILocation(line: 366, column: 36, scope: !2112)
!2114 = !DILocation(line: 366, column: 41, scope: !2112)
!2115 = !DILocation(line: 367, column: 28, scope: !2112)
!2116 = !DILocation(line: 367, column: 34, scope: !2112)
!2117 = !DILocation(line: 367, column: 43, scope: !2112)
!2118 = !DILocation(line: 367, column: 52, scope: !2112)
!2119 = !DILocation(line: 367, column: 58, scope: !2112)
!2120 = !DILocation(line: 367, column: 67, scope: !2112)
!2121 = !DILocation(line: 366, column: 21, scope: !2112)
!2122 = !DILocation(line: 366, column: 19, scope: !2112)
!2123 = !DILocation(line: 368, column: 5, scope: !2112)
!2124 = !DILocation(line: 368, column: 11, scope: !2112)
!2125 = !DILocation(line: 368, column: 16, scope: !2112)
!2126 = !DILocation(line: 368, column: 29, scope: !2112)
!2127 = !DILocation(line: 369, column: 3, scope: !2112)
!2128 = !DILocation(line: 372, column: 21, scope: !2107)
!2129 = !DILocation(line: 372, column: 19, scope: !2107)
!2130 = !DILocation(line: 374, column: 4, scope: !1715)
!2131 = !DILocation(line: 374, column: 9, scope: !1715)
!2132 = !DILocation(line: 375, column: 12, scope: !2133)
!2133 = distinct !DILexicalBlock(scope: !1715, file: !1, line: 375, column: 6)
!2134 = !DILocation(line: 375, column: 9, scope: !2133)
!2135 = !DILocation(line: 375, column: 6, scope: !1715)
!2136 = !DILocalVariable(name: "err", scope: !2137, file: !1, line: 376, type: !177)
!2137 = distinct !DILexicalBlock(scope: !2133, file: !1, line: 375, column: 27)
!2138 = !DILocation(line: 376, column: 9, scope: !2137)
!2139 = !DILocation(line: 376, column: 15, scope: !2137)
!2140 = !DILocation(line: 386, column: 23, scope: !2141)
!2141 = distinct !DILexicalBlock(scope: !2137, file: !1, line: 386, column: 7)
!2142 = !DILocation(line: 386, column: 20, scope: !2141)
!2143 = !DILocation(line: 386, column: 28, scope: !2141)
!2144 = !DILocation(line: 386, column: 42, scope: !2145)
!2145 = !DILexicalBlockFile(scope: !2141, file: !1, discriminator: 1)
!2146 = !DILocation(line: 386, column: 39, scope: !2145)
!2147 = !DILocation(line: 386, column: 47, scope: !2145)
!2148 = !DILocation(line: 386, column: 60, scope: !2149)
!2149 = !DILexicalBlockFile(scope: !2141, file: !1, discriminator: 2)
!2150 = !DILocation(line: 386, column: 57, scope: !2149)
!2151 = !DILocation(line: 386, column: 65, scope: !2149)
!2152 = !DILocation(line: 387, column: 23, scope: !2141)
!2153 = !DILocation(line: 387, column: 20, scope: !2141)
!2154 = !DILocation(line: 386, column: 7, scope: !2155)
!2155 = !DILexicalBlockFile(scope: !2137, file: !1, discriminator: 3)
!2156 = !DILocation(line: 391, column: 20, scope: !2157)
!2157 = distinct !DILexicalBlock(scope: !2141, file: !1, line: 389, column: 9)
!2158 = !DILocation(line: 392, column: 8, scope: !2157)
!2159 = !DILocation(line: 392, column: 13, scope: !2157)
!2160 = !DILocation(line: 393, column: 5, scope: !2157)
!2161 = !DILocation(line: 395, column: 13, scope: !2162)
!2162 = distinct !DILexicalBlock(scope: !2141, file: !1, line: 394, column: 10)
!2163 = !DILocation(line: 395, column: 19, scope: !2162)
!2164 = !DILocation(line: 396, column: 27, scope: !2162)
!2165 = !DILocation(line: 396, column: 33, scope: !2162)
!2166 = !DILocation(line: 396, column: 13, scope: !2162)
!2167 = !DILocation(line: 395, column: 7, scope: !2162)
!2168 = !DILocation(line: 397, column: 36, scope: !2162)
!2169 = !DILocation(line: 397, column: 7, scope: !2162)
!2170 = !DILocation(line: 397, column: 13, scope: !2162)
!2171 = !DILocation(line: 397, column: 19, scope: !2162)
!2172 = !DILocation(line: 397, column: 25, scope: !2162)
!2173 = !DILocation(line: 397, column: 34, scope: !2162)
!2174 = !DILocation(line: 398, column: 8, scope: !2162)
!2175 = !DILocation(line: 398, column: 13, scope: !2162)
!2176 = !DILocation(line: 400, column: 3, scope: !2137)
!2177 = !DILocation(line: 401, column: 10, scope: !1715)
!2178 = !DILocation(line: 401, column: 3, scope: !1715)
!2179 = !DILocalVariable(name: "conn", arg: 1, scope: !1716, file: !1, line: 409, type: !550)
!2180 = !DILocation(line: 409, column: 47, scope: !1716)
!2181 = !DILocalVariable(name: "sockfd", arg: 2, scope: !1716, file: !1, line: 410, type: !248)
!2182 = !DILocation(line: 410, column: 41, scope: !1716)
!2183 = !DILocalVariable(name: "mem", arg: 3, scope: !1716, file: !1, line: 411, type: !995)
!2184 = !DILocation(line: 411, column: 39, scope: !1716)
!2185 = !DILocalVariable(name: "len", arg: 4, scope: !1716, file: !1, line: 412, type: !158)
!2186 = !DILocation(line: 412, column: 34, scope: !1716)
!2187 = !DILocalVariable(name: "written", arg: 5, scope: !1716, file: !1, line: 413, type: !1459)
!2188 = !DILocation(line: 413, column: 36, scope: !1716)
!2189 = !DILocalVariable(name: "bytes_written", scope: !1716, file: !1, line: 415, type: !256)
!2190 = !DILocation(line: 415, column: 11, scope: !1716)
!2191 = !DILocalVariable(name: "result", scope: !1716, file: !1, line: 416, type: !554)
!2192 = !DILocation(line: 416, column: 12, scope: !1716)
!2193 = !DILocalVariable(name: "num", scope: !1716, file: !1, line: 417, type: !177)
!2194 = !DILocation(line: 417, column: 7, scope: !1716)
!2195 = !DILocation(line: 417, column: 14, scope: !1716)
!2196 = !DILocation(line: 417, column: 24, scope: !1716)
!2197 = !DILocation(line: 417, column: 30, scope: !1716)
!2198 = !DILocation(line: 417, column: 21, scope: !1716)
!2199 = !DILocation(line: 419, column: 35, scope: !1716)
!2200 = !DILocation(line: 419, column: 41, scope: !1716)
!2201 = !DILocation(line: 419, column: 46, scope: !1716)
!2202 = !DILocation(line: 419, column: 51, scope: !1716)
!2203 = !DILocation(line: 419, column: 19, scope: !1716)
!2204 = !DILocation(line: 419, column: 17, scope: !1716)
!2205 = !DILocation(line: 421, column: 14, scope: !1716)
!2206 = !DILocation(line: 421, column: 4, scope: !1716)
!2207 = !DILocation(line: 421, column: 12, scope: !1716)
!2208 = !DILocation(line: 423, column: 10, scope: !1716)
!2209 = !DILocation(line: 423, column: 3, scope: !1716)
!2210 = !DILocalVariable(name: "conn", arg: 1, scope: !1717, file: !1, line: 426, type: !550)
!2211 = !DILocation(line: 426, column: 45, scope: !1717)
!2212 = !DILocalVariable(name: "num", arg: 2, scope: !1717, file: !1, line: 426, type: !177)
!2213 = !DILocation(line: 426, column: 55, scope: !1717)
!2214 = !DILocalVariable(name: "buf", arg: 3, scope: !1717, file: !1, line: 426, type: !215)
!2215 = !DILocation(line: 426, column: 66, scope: !1717)
!2216 = !DILocalVariable(name: "len", arg: 4, scope: !1717, file: !1, line: 427, type: !158)
!2217 = !DILocation(line: 427, column: 32, scope: !1717)
!2218 = !DILocalVariable(name: "code", arg: 5, scope: !1717, file: !1, line: 427, type: !1350)
!2219 = !DILocation(line: 427, column: 47, scope: !1717)
!2220 = !DILocalVariable(name: "sockfd", scope: !1717, file: !1, line: 429, type: !248)
!2221 = !DILocation(line: 429, column: 17, scope: !1717)
!2222 = !DILocation(line: 429, column: 37, scope: !1717)
!2223 = !DILocation(line: 429, column: 26, scope: !1717)
!2224 = !DILocation(line: 429, column: 32, scope: !1717)
!2225 = !DILocalVariable(name: "nread", scope: !1717, file: !1, line: 430, type: !256)
!2226 = !DILocation(line: 430, column: 11, scope: !1717)
!2227 = !DILocation(line: 433, column: 9, scope: !1717)
!2228 = !DILocation(line: 434, column: 6, scope: !2229)
!2229 = distinct !DILexicalBlock(scope: !1717, file: !1, line: 434, column: 6)
!2230 = !DILocation(line: 434, column: 12, scope: !2229)
!2231 = !DILocation(line: 434, column: 6, scope: !1717)
!2232 = !DILocation(line: 435, column: 6, scope: !2233)
!2233 = distinct !DILexicalBlock(scope: !2229, file: !1, line: 434, column: 17)
!2234 = !DILocation(line: 435, column: 11, scope: !2233)
!2235 = !DILocation(line: 436, column: 12, scope: !2233)
!2236 = !DILocation(line: 436, column: 5, scope: !2233)
!2237 = !DILocation(line: 439, column: 11, scope: !1717)
!2238 = !DILocation(line: 439, column: 9, scope: !1717)
!2239 = !DILocation(line: 441, column: 4, scope: !1717)
!2240 = !DILocation(line: 441, column: 9, scope: !1717)
!2241 = !DILocation(line: 442, column: 12, scope: !2242)
!2242 = distinct !DILexicalBlock(scope: !1717, file: !1, line: 442, column: 6)
!2243 = !DILocation(line: 442, column: 9, scope: !2242)
!2244 = !DILocation(line: 442, column: 6, scope: !1717)
!2245 = !DILocalVariable(name: "err", scope: !2246, file: !1, line: 443, type: !177)
!2246 = distinct !DILexicalBlock(scope: !2242, file: !1, line: 442, column: 19)
!2247 = !DILocation(line: 443, column: 9, scope: !2246)
!2248 = !DILocation(line: 443, column: 15, scope: !2246)
!2249 = !DILocation(line: 453, column: 23, scope: !2250)
!2250 = distinct !DILexicalBlock(scope: !2246, file: !1, line: 453, column: 7)
!2251 = !DILocation(line: 453, column: 20, scope: !2250)
!2252 = !DILocation(line: 453, column: 28, scope: !2250)
!2253 = !DILocation(line: 453, column: 42, scope: !2254)
!2254 = !DILexicalBlockFile(scope: !2250, file: !1, discriminator: 1)
!2255 = !DILocation(line: 453, column: 39, scope: !2254)
!2256 = !DILocation(line: 453, column: 47, scope: !2254)
!2257 = !DILocation(line: 453, column: 60, scope: !2258)
!2258 = !DILexicalBlockFile(scope: !2250, file: !1, discriminator: 2)
!2259 = !DILocation(line: 453, column: 57, scope: !2258)
!2260 = !DILocation(line: 453, column: 7, scope: !2258)
!2261 = !DILocation(line: 457, column: 8, scope: !2262)
!2262 = distinct !DILexicalBlock(scope: !2250, file: !1, line: 455, column: 9)
!2263 = !DILocation(line: 457, column: 13, scope: !2262)
!2264 = !DILocation(line: 458, column: 5, scope: !2262)
!2265 = !DILocation(line: 460, column: 13, scope: !2266)
!2266 = distinct !DILexicalBlock(scope: !2250, file: !1, line: 459, column: 10)
!2267 = !DILocation(line: 460, column: 19, scope: !2266)
!2268 = !DILocation(line: 461, column: 27, scope: !2266)
!2269 = !DILocation(line: 461, column: 33, scope: !2266)
!2270 = !DILocation(line: 461, column: 13, scope: !2266)
!2271 = !DILocation(line: 460, column: 7, scope: !2266)
!2272 = !DILocation(line: 462, column: 36, scope: !2266)
!2273 = !DILocation(line: 462, column: 7, scope: !2266)
!2274 = !DILocation(line: 462, column: 13, scope: !2266)
!2275 = !DILocation(line: 462, column: 19, scope: !2266)
!2276 = !DILocation(line: 462, column: 25, scope: !2266)
!2277 = !DILocation(line: 462, column: 34, scope: !2266)
!2278 = !DILocation(line: 463, column: 8, scope: !2266)
!2279 = !DILocation(line: 463, column: 13, scope: !2266)
!2280 = !DILocation(line: 465, column: 3, scope: !2246)
!2281 = !DILocation(line: 466, column: 10, scope: !1717)
!2282 = !DILocation(line: 466, column: 3, scope: !1717)
!2283 = !DILocation(line: 467, column: 1, scope: !1717)
!2284 = !DILocalVariable(name: "conn", arg: 1, scope: !1718, file: !1, line: 540, type: !550)
!2285 = !DILocation(line: 540, column: 53, scope: !1718)
!2286 = !DILocalVariable(name: "type", arg: 2, scope: !1718, file: !1, line: 541, type: !177)
!2287 = !DILocation(line: 541, column: 37, scope: !1718)
!2288 = !DILocalVariable(name: "ptr", arg: 3, scope: !1718, file: !1, line: 542, type: !215)
!2289 = !DILocation(line: 542, column: 39, scope: !1718)
!2290 = !DILocalVariable(name: "len", arg: 4, scope: !1718, file: !1, line: 543, type: !158)
!2291 = !DILocation(line: 543, column: 40, scope: !1718)
!2292 = !DILocalVariable(name: "data", scope: !1718, file: !1, line: 545, type: !544)
!2293 = !DILocation(line: 545, column: 21, scope: !1718)
!2294 = !DILocation(line: 545, column: 28, scope: !1718)
!2295 = !DILocation(line: 545, column: 34, scope: !1718)
!2296 = !DILocalVariable(name: "writeheader", scope: !1718, file: !1, line: 546, type: !730)
!2297 = !DILocation(line: 546, column: 23, scope: !1718)
!2298 = !DILocalVariable(name: "writebody", scope: !1718, file: !1, line: 547, type: !730)
!2299 = !DILocation(line: 547, column: 23, scope: !1718)
!2300 = !DILocation(line: 549, column: 7, scope: !2301)
!2301 = distinct !DILexicalBlock(scope: !1718, file: !1, line: 549, column: 6)
!2302 = !DILocation(line: 549, column: 6, scope: !1718)
!2303 = !DILocation(line: 550, column: 5, scope: !2301)
!2304 = !DILocation(line: 554, column: 6, scope: !2305)
!2305 = distinct !DILexicalBlock(scope: !1718, file: !1, line: 554, column: 6)
!2306 = !DILocation(line: 554, column: 12, scope: !2305)
!2307 = !DILocation(line: 554, column: 16, scope: !2305)
!2308 = !DILocation(line: 554, column: 23, scope: !2305)
!2309 = !DILocation(line: 554, column: 6, scope: !1718)
!2310 = !DILocation(line: 555, column: 23, scope: !2305)
!2311 = !DILocation(line: 555, column: 29, scope: !2305)
!2312 = !DILocation(line: 555, column: 35, scope: !2305)
!2313 = !DILocation(line: 555, column: 40, scope: !2305)
!2314 = !DILocation(line: 555, column: 12, scope: !2305)
!2315 = !DILocation(line: 555, column: 5, scope: !2305)
!2316 = !DILocation(line: 558, column: 6, scope: !2317)
!2317 = distinct !DILexicalBlock(scope: !1718, file: !1, line: 558, column: 6)
!2318 = !DILocation(line: 558, column: 11, scope: !2317)
!2319 = !DILocation(line: 558, column: 6, scope: !1718)
!2320 = !DILocation(line: 559, column: 17, scope: !2317)
!2321 = !DILocation(line: 559, column: 23, scope: !2317)
!2322 = !DILocation(line: 559, column: 27, scope: !2317)
!2323 = !DILocation(line: 559, column: 15, scope: !2317)
!2324 = !DILocation(line: 559, column: 5, scope: !2317)
!2325 = !DILocation(line: 560, column: 7, scope: !2326)
!2326 = distinct !DILexicalBlock(scope: !1718, file: !1, line: 560, column: 6)
!2327 = !DILocation(line: 560, column: 12, scope: !2326)
!2328 = !DILocation(line: 560, column: 34, scope: !2326)
!2329 = !DILocation(line: 561, column: 7, scope: !2326)
!2330 = !DILocation(line: 561, column: 13, scope: !2326)
!2331 = !DILocation(line: 561, column: 17, scope: !2326)
!2332 = !DILocation(line: 561, column: 31, scope: !2326)
!2333 = !DILocation(line: 561, column: 34, scope: !2334)
!2334 = !DILexicalBlockFile(scope: !2326, file: !1, discriminator: 1)
!2335 = !DILocation(line: 561, column: 40, scope: !2334)
!2336 = !DILocation(line: 561, column: 44, scope: !2334)
!2337 = !DILocation(line: 560, column: 6, scope: !2338)
!2338 = !DILexicalBlockFile(scope: !1718, file: !1, discriminator: 1)
!2339 = !DILocation(line: 567, column: 7, scope: !2340)
!2340 = distinct !DILexicalBlock(scope: !2326, file: !1, line: 561, column: 58)
!2341 = !DILocation(line: 567, column: 13, scope: !2340)
!2342 = !DILocation(line: 567, column: 17, scope: !2340)
!2343 = !DILocation(line: 567, column: 32, scope: !2344)
!2344 = !DILexicalBlockFile(scope: !2340, file: !1, discriminator: 1)
!2345 = !DILocation(line: 567, column: 38, scope: !2344)
!2346 = !DILocation(line: 567, column: 42, scope: !2344)
!2347 = !DILocation(line: 567, column: 7, scope: !2344)
!2348 = !DILocation(line: 567, column: 57, scope: !2349)
!2349 = !DILexicalBlockFile(scope: !2340, file: !1, discriminator: 2)
!2350 = !DILocation(line: 567, column: 63, scope: !2349)
!2351 = !DILocation(line: 567, column: 67, scope: !2349)
!2352 = !DILocation(line: 567, column: 7, scope: !2349)
!2353 = !DILocation(line: 567, column: 7, scope: !2354)
!2354 = !DILexicalBlockFile(scope: !2340, file: !1, discriminator: 3)
!2355 = !DILocation(line: 566, column: 17, scope: !2340)
!2356 = !DILocation(line: 568, column: 3, scope: !2340)
!2357 = !DILocation(line: 571, column: 3, scope: !1718)
!2358 = !DILocation(line: 571, column: 9, scope: !2338)
!2359 = !DILocation(line: 571, column: 3, scope: !2338)
!2360 = !DILocalVariable(name: "chunklen", scope: !2361, file: !1, line: 572, type: !158)
!2361 = distinct !DILexicalBlock(scope: !1718, file: !1, line: 571, column: 14)
!2362 = !DILocation(line: 572, column: 12, scope: !2361)
!2363 = !DILocation(line: 572, column: 23, scope: !2361)
!2364 = !DILocation(line: 572, column: 27, scope: !2361)
!2365 = !DILocation(line: 572, column: 51, scope: !2366)
!2366 = !DILexicalBlockFile(scope: !2361, file: !1, discriminator: 1)
!2367 = !DILocation(line: 572, column: 23, scope: !2366)
!2368 = !DILocation(line: 572, column: 23, scope: !2369)
!2369 = !DILexicalBlockFile(scope: !2361, file: !1, discriminator: 2)
!2370 = !DILocation(line: 572, column: 23, scope: !2371)
!2371 = !DILexicalBlockFile(scope: !2361, file: !1, discriminator: 3)
!2372 = !DILocation(line: 572, column: 12, scope: !2371)
!2373 = !DILocation(line: 574, column: 8, scope: !2374)
!2374 = distinct !DILexicalBlock(scope: !2361, file: !1, line: 574, column: 8)
!2375 = !DILocation(line: 574, column: 8, scope: !2361)
!2376 = !DILocalVariable(name: "wrote", scope: !2377, file: !1, line: 575, type: !158)
!2377 = distinct !DILexicalBlock(scope: !2374, file: !1, line: 574, column: 19)
!2378 = !DILocation(line: 575, column: 14, scope: !2377)
!2379 = !DILocation(line: 575, column: 22, scope: !2377)
!2380 = !DILocation(line: 575, column: 32, scope: !2377)
!2381 = !DILocation(line: 575, column: 40, scope: !2377)
!2382 = !DILocation(line: 575, column: 50, scope: !2377)
!2383 = !DILocation(line: 575, column: 56, scope: !2377)
!2384 = !DILocation(line: 575, column: 60, scope: !2377)
!2385 = !DILocation(line: 577, column: 34, scope: !2386)
!2386 = distinct !DILexicalBlock(scope: !2377, file: !1, line: 577, column: 10)
!2387 = !DILocation(line: 577, column: 31, scope: !2386)
!2388 = !DILocation(line: 577, column: 10, scope: !2377)
!2389 = !DILocation(line: 578, column: 12, scope: !2390)
!2390 = distinct !DILexicalBlock(scope: !2391, file: !1, line: 578, column: 12)
!2391 = distinct !DILexicalBlock(scope: !2386, file: !1, line: 577, column: 41)
!2392 = !DILocation(line: 578, column: 18, scope: !2390)
!2393 = !DILocation(line: 578, column: 27, scope: !2390)
!2394 = !DILocation(line: 578, column: 33, scope: !2390)
!2395 = !DILocation(line: 578, column: 12, scope: !2391)
!2396 = !DILocation(line: 582, column: 17, scope: !2397)
!2397 = distinct !DILexicalBlock(scope: !2390, file: !1, line: 578, column: 54)
!2398 = !DILocation(line: 582, column: 11, scope: !2397)
!2399 = !DILocation(line: 583, column: 11, scope: !2397)
!2400 = !DILocation(line: 585, column: 27, scope: !2391)
!2401 = !DILocation(line: 585, column: 33, scope: !2391)
!2402 = !DILocation(line: 585, column: 39, scope: !2391)
!2403 = !DILocation(line: 585, column: 44, scope: !2391)
!2404 = !DILocation(line: 585, column: 16, scope: !2391)
!2405 = !DILocation(line: 585, column: 9, scope: !2391)
!2406 = !DILocation(line: 587, column: 10, scope: !2407)
!2407 = distinct !DILexicalBlock(scope: !2377, file: !1, line: 587, column: 10)
!2408 = !DILocation(line: 587, column: 19, scope: !2407)
!2409 = !DILocation(line: 587, column: 16, scope: !2407)
!2410 = !DILocation(line: 587, column: 10, scope: !2377)
!2411 = !DILocation(line: 588, column: 15, scope: !2412)
!2412 = distinct !DILexicalBlock(scope: !2407, file: !1, line: 587, column: 29)
!2413 = !DILocation(line: 588, column: 57, scope: !2412)
!2414 = !DILocation(line: 588, column: 64, scope: !2412)
!2415 = !DILocation(line: 588, column: 9, scope: !2412)
!2416 = !DILocation(line: 589, column: 9, scope: !2412)
!2417 = !DILocation(line: 591, column: 5, scope: !2377)
!2418 = !DILocation(line: 593, column: 8, scope: !2419)
!2419 = distinct !DILexicalBlock(scope: !2361, file: !1, line: 593, column: 8)
!2420 = !DILocation(line: 593, column: 8, scope: !2361)
!2421 = !DILocalVariable(name: "wrote", scope: !2422, file: !1, line: 594, type: !158)
!2422 = distinct !DILexicalBlock(scope: !2419, file: !1, line: 593, column: 21)
!2423 = !DILocation(line: 594, column: 14, scope: !2422)
!2424 = !DILocation(line: 594, column: 22, scope: !2422)
!2425 = !DILocation(line: 594, column: 34, scope: !2422)
!2426 = !DILocation(line: 594, column: 42, scope: !2422)
!2427 = !DILocation(line: 594, column: 52, scope: !2422)
!2428 = !DILocation(line: 594, column: 58, scope: !2422)
!2429 = !DILocation(line: 594, column: 62, scope: !2422)
!2430 = !DILocation(line: 596, column: 34, scope: !2431)
!2431 = distinct !DILexicalBlock(scope: !2422, file: !1, line: 596, column: 10)
!2432 = !DILocation(line: 596, column: 31, scope: !2431)
!2433 = !DILocation(line: 596, column: 10, scope: !2422)
!2434 = !DILocation(line: 600, column: 27, scope: !2431)
!2435 = !DILocation(line: 600, column: 53, scope: !2431)
!2436 = !DILocation(line: 600, column: 58, scope: !2431)
!2437 = !DILocation(line: 600, column: 16, scope: !2431)
!2438 = !DILocation(line: 600, column: 9, scope: !2431)
!2439 = !DILocation(line: 602, column: 10, scope: !2440)
!2440 = distinct !DILexicalBlock(scope: !2422, file: !1, line: 602, column: 10)
!2441 = !DILocation(line: 602, column: 19, scope: !2440)
!2442 = !DILocation(line: 602, column: 16, scope: !2440)
!2443 = !DILocation(line: 602, column: 10, scope: !2422)
!2444 = !DILocation(line: 603, column: 15, scope: !2445)
!2445 = distinct !DILexicalBlock(scope: !2440, file: !1, line: 602, column: 29)
!2446 = !DILocation(line: 603, column: 9, scope: !2445)
!2447 = !DILocation(line: 604, column: 9, scope: !2445)
!2448 = !DILocation(line: 606, column: 5, scope: !2422)
!2449 = !DILocation(line: 608, column: 12, scope: !2361)
!2450 = !DILocation(line: 608, column: 9, scope: !2361)
!2451 = !DILocation(line: 609, column: 12, scope: !2361)
!2452 = !DILocation(line: 609, column: 9, scope: !2361)
!2453 = !DILocation(line: 571, column: 3, scope: !2454)
!2454 = !DILexicalBlockFile(scope: !1718, file: !1, discriminator: 2)
!2455 = !DILocation(line: 612, column: 3, scope: !1718)
!2456 = !DILocation(line: 613, column: 1, scope: !1718)
!2457 = !DILocalVariable(name: "data", arg: 1, scope: !1731, file: !1, line: 469, type: !544)
!2458 = !DILocation(line: 469, column: 46, scope: !1731)
!2459 = !DILocalVariable(name: "type", arg: 2, scope: !1731, file: !1, line: 470, type: !177)
!2460 = !DILocation(line: 470, column: 32, scope: !1731)
!2461 = !DILocalVariable(name: "ptr", arg: 3, scope: !1731, file: !1, line: 471, type: !928)
!2462 = !DILocation(line: 471, column: 40, scope: !1731)
!2463 = !DILocalVariable(name: "len", arg: 4, scope: !1731, file: !1, line: 472, type: !158)
!2464 = !DILocation(line: 472, column: 35, scope: !1731)
!2465 = !DILocalVariable(name: "k", scope: !1731, file: !1, line: 477, type: !2466)
!2466 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !186, size: 64, align: 64)
!2467 = !DILocation(line: 477, column: 25, scope: !1731)
!2468 = !DILocation(line: 477, column: 30, scope: !1731)
!2469 = !DILocation(line: 477, column: 36, scope: !1731)
!2470 = !DILocalVariable(name: "s", scope: !1731, file: !1, line: 478, type: !2471)
!2471 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1103, size: 64, align: 64)
!2472 = !DILocation(line: 478, column: 20, scope: !1731)
!2473 = !DILocation(line: 478, column: 25, scope: !1731)
!2474 = !DILocation(line: 478, column: 31, scope: !1731)
!2475 = !DILocalVariable(name: "dupl", scope: !1731, file: !1, line: 479, type: !215)
!2476 = !DILocation(line: 479, column: 9, scope: !1731)
!2477 = !DILocalVariable(name: "i", scope: !1731, file: !1, line: 480, type: !782)
!2478 = !DILocation(line: 480, column: 16, scope: !1731)
!2479 = !DILocalVariable(name: "newtype", scope: !1731, file: !1, line: 481, type: !211)
!2480 = !DILocation(line: 481, column: 8, scope: !1731)
!2481 = !DILocation(line: 483, column: 6, scope: !2482)
!2482 = distinct !DILexicalBlock(scope: !1731, file: !1, line: 483, column: 6)
!2483 = !DILocation(line: 483, column: 9, scope: !2482)
!2484 = !DILocation(line: 483, column: 6, scope: !1731)
!2485 = !DILocation(line: 484, column: 10, scope: !2486)
!2486 = distinct !DILexicalBlock(scope: !2487, file: !1, line: 484, column: 5)
!2487 = distinct !DILexicalBlock(scope: !2482, file: !1, line: 483, column: 20)
!2488 = !DILocation(line: 484, column: 9, scope: !2486)
!2489 = !DILocation(line: 484, column: 14, scope: !2490)
!2490 = !DILexicalBlockFile(scope: !2491, file: !1, discriminator: 1)
!2491 = distinct !DILexicalBlock(scope: !2486, file: !1, line: 484, column: 5)
!2492 = !DILocation(line: 484, column: 17, scope: !2490)
!2493 = !DILocation(line: 484, column: 20, scope: !2490)
!2494 = !DILocation(line: 484, column: 15, scope: !2490)
!2495 = !DILocation(line: 484, column: 5, scope: !2490)
!2496 = !DILocation(line: 485, column: 23, scope: !2497)
!2497 = distinct !DILexicalBlock(scope: !2498, file: !1, line: 485, column: 10)
!2498 = distinct !DILexicalBlock(scope: !2491, file: !1, line: 484, column: 36)
!2499 = !DILocation(line: 485, column: 10, scope: !2497)
!2500 = !DILocation(line: 485, column: 13, scope: !2497)
!2501 = !DILocation(line: 485, column: 26, scope: !2497)
!2502 = !DILocation(line: 485, column: 34, scope: !2497)
!2503 = !DILocation(line: 485, column: 31, scope: !2497)
!2504 = !DILocation(line: 485, column: 10, scope: !2498)
!2505 = !DILocation(line: 487, column: 17, scope: !2506)
!2506 = distinct !DILexicalBlock(scope: !2497, file: !1, line: 485, column: 40)
!2507 = !DILocation(line: 488, column: 9, scope: !2506)
!2508 = !DILocation(line: 490, column: 5, scope: !2498)
!2509 = !DILocation(line: 484, column: 32, scope: !2510)
!2510 = !DILexicalBlockFile(scope: !2491, file: !1, discriminator: 2)
!2511 = !DILocation(line: 484, column: 5, scope: !2510)
!2512 = !DILocation(line: 491, column: 5, scope: !2487)
!2513 = !DILocation(line: 491, column: 5, scope: !2514)
!2514 = !DILexicalBlockFile(scope: !2515, file: !1, discriminator: 1)
!2515 = distinct !DILexicalBlock(scope: !2487, file: !1, line: 491, column: 5)
!2516 = !DILocation(line: 492, column: 3, scope: !2487)
!2517 = !DILocation(line: 494, column: 7, scope: !2482)
!2518 = !DILocation(line: 496, column: 7, scope: !2519)
!2519 = distinct !DILexicalBlock(scope: !1731, file: !1, line: 496, column: 6)
!2520 = !DILocation(line: 496, column: 6, scope: !1731)
!2521 = !DILocalVariable(name: "newlen", scope: !2522, file: !1, line: 500, type: !158)
!2522 = distinct !DILexicalBlock(scope: !2519, file: !1, line: 496, column: 16)
!2523 = !DILocation(line: 500, column: 12, scope: !2522)
!2524 = !DILocation(line: 500, column: 21, scope: !2522)
!2525 = !DILocation(line: 500, column: 40, scope: !2522)
!2526 = !DILocation(line: 500, column: 27, scope: !2522)
!2527 = !DILocation(line: 500, column: 30, scope: !2522)
!2528 = !DILocation(line: 500, column: 43, scope: !2522)
!2529 = !DILocation(line: 500, column: 25, scope: !2522)
!2530 = !DILocalVariable(name: "newptr", scope: !2522, file: !1, line: 502, type: !215)
!2531 = !DILocation(line: 502, column: 11, scope: !2522)
!2532 = !DILocation(line: 502, column: 20, scope: !2522)
!2533 = !DILocation(line: 503, column: 9, scope: !2534)
!2534 = distinct !DILexicalBlock(scope: !2522, file: !1, line: 503, column: 8)
!2535 = !DILocation(line: 503, column: 8, scope: !2522)
!2536 = !DILocation(line: 504, column: 7, scope: !2534)
!2537 = !DILocation(line: 506, column: 12, scope: !2522)
!2538 = !DILocation(line: 506, column: 34, scope: !2522)
!2539 = !DILocation(line: 506, column: 21, scope: !2522)
!2540 = !DILocation(line: 506, column: 24, scope: !2522)
!2541 = !DILocation(line: 506, column: 37, scope: !2522)
!2542 = !DILocation(line: 506, column: 19, scope: !2522)
!2543 = !DILocation(line: 506, column: 42, scope: !2522)
!2544 = !DILocation(line: 506, column: 47, scope: !2522)
!2545 = !DILocation(line: 506, column: 5, scope: !2522)
!2546 = !DILocation(line: 509, column: 27, scope: !2522)
!2547 = !DILocation(line: 509, column: 18, scope: !2522)
!2548 = !DILocation(line: 509, column: 5, scope: !2522)
!2549 = !DILocation(line: 509, column: 8, scope: !2522)
!2550 = !DILocation(line: 509, column: 21, scope: !2522)
!2551 = !DILocation(line: 509, column: 25, scope: !2522)
!2552 = !DILocation(line: 510, column: 27, scope: !2522)
!2553 = !DILocation(line: 510, column: 18, scope: !2522)
!2554 = !DILocation(line: 510, column: 5, scope: !2522)
!2555 = !DILocation(line: 510, column: 8, scope: !2522)
!2556 = !DILocation(line: 510, column: 21, scope: !2522)
!2557 = !DILocation(line: 510, column: 25, scope: !2522)
!2558 = !DILocation(line: 511, column: 3, scope: !2522)
!2559 = !DILocation(line: 513, column: 24, scope: !2560)
!2560 = distinct !DILexicalBlock(scope: !2519, file: !1, line: 512, column: 8)
!2561 = !DILocation(line: 513, column: 29, scope: !2560)
!2562 = !DILocation(line: 513, column: 12, scope: !2560)
!2563 = !DILocation(line: 513, column: 10, scope: !2560)
!2564 = !DILocation(line: 514, column: 9, scope: !2565)
!2565 = distinct !DILexicalBlock(scope: !2560, file: !1, line: 514, column: 8)
!2566 = !DILocation(line: 514, column: 8, scope: !2560)
!2567 = !DILocation(line: 515, column: 7, scope: !2565)
!2568 = !DILocation(line: 518, column: 27, scope: !2560)
!2569 = !DILocation(line: 518, column: 18, scope: !2560)
!2570 = !DILocation(line: 518, column: 5, scope: !2560)
!2571 = !DILocation(line: 518, column: 8, scope: !2560)
!2572 = !DILocation(line: 518, column: 21, scope: !2560)
!2573 = !DILocation(line: 518, column: 25, scope: !2560)
!2574 = !DILocation(line: 519, column: 27, scope: !2560)
!2575 = !DILocation(line: 519, column: 18, scope: !2560)
!2576 = !DILocation(line: 519, column: 5, scope: !2560)
!2577 = !DILocation(line: 519, column: 8, scope: !2560)
!2578 = !DILocation(line: 519, column: 21, scope: !2560)
!2579 = !DILocation(line: 519, column: 25, scope: !2560)
!2580 = !DILocation(line: 520, column: 28, scope: !2560)
!2581 = !DILocation(line: 520, column: 18, scope: !2560)
!2582 = !DILocation(line: 520, column: 5, scope: !2560)
!2583 = !DILocation(line: 520, column: 8, scope: !2560)
!2584 = !DILocation(line: 520, column: 21, scope: !2560)
!2585 = !DILocation(line: 520, column: 26, scope: !2560)
!2586 = !DILocation(line: 522, column: 8, scope: !2587)
!2587 = distinct !DILexicalBlock(scope: !2560, file: !1, line: 522, column: 8)
!2588 = !DILocation(line: 522, column: 8, scope: !2560)
!2589 = !DILocation(line: 523, column: 7, scope: !2587)
!2590 = !DILocation(line: 523, column: 10, scope: !2587)
!2591 = !DILocation(line: 523, column: 19, scope: !2587)
!2592 = !DILocation(line: 527, column: 3, scope: !1731)
!2593 = !DILocation(line: 527, column: 6, scope: !1731)
!2594 = !DILocation(line: 527, column: 13, scope: !1731)
!2595 = !DILocation(line: 529, column: 3, scope: !1731)
!2596 = !DILocation(line: 529, column: 3, scope: !2597)
!2597 = !DILexicalBlockFile(scope: !2598, file: !1, discriminator: 1)
!2598 = distinct !DILexicalBlock(scope: !1731, file: !1, line: 529, column: 3)
!2599 = !DILocation(line: 532, column: 3, scope: !1731)
!2600 = !DILocation(line: 533, column: 1, scope: !1731)
!2601 = !DILocalVariable(name: "conn", arg: 1, scope: !1721, file: !1, line: 625, type: !550)
!2602 = !DILocation(line: 625, column: 48, scope: !1721)
!2603 = !DILocalVariable(name: "type", arg: 2, scope: !1721, file: !1, line: 626, type: !177)
!2604 = !DILocation(line: 626, column: 32, scope: !1721)
!2605 = !DILocalVariable(name: "ptr", arg: 3, scope: !1721, file: !1, line: 627, type: !215)
!2606 = !DILocation(line: 627, column: 34, scope: !1721)
!2607 = !DILocalVariable(name: "len", arg: 4, scope: !1721, file: !1, line: 628, type: !158)
!2608 = !DILocation(line: 628, column: 35, scope: !1721)
!2609 = !DILocalVariable(name: "data", scope: !1721, file: !1, line: 630, type: !544)
!2610 = !DILocation(line: 630, column: 21, scope: !1721)
!2611 = !DILocation(line: 630, column: 28, scope: !1721)
!2612 = !DILocation(line: 630, column: 34, scope: !1721)
!2613 = !DILocation(line: 632, column: 11, scope: !2614)
!2614 = distinct !DILexicalBlock(scope: !1721, file: !1, line: 632, column: 6)
!2615 = !DILocation(line: 632, column: 8, scope: !2614)
!2616 = !DILocation(line: 632, column: 6, scope: !1721)
!2617 = !DILocation(line: 633, column: 18, scope: !2614)
!2618 = !DILocation(line: 633, column: 11, scope: !2614)
!2619 = !DILocation(line: 633, column: 9, scope: !2614)
!2620 = !DILocation(line: 633, column: 5, scope: !2614)
!2621 = !DILocation(line: 635, column: 3, scope: !1721)
!2622 = !DILocation(line: 635, column: 3, scope: !2623)
!2623 = !DILexicalBlockFile(scope: !2624, file: !1, discriminator: 1)
!2624 = distinct !DILexicalBlock(scope: !1721, file: !1, line: 635, column: 3)
!2625 = !DILocation(line: 638, column: 7, scope: !2626)
!2626 = distinct !DILexicalBlock(scope: !1721, file: !1, line: 638, column: 6)
!2627 = !DILocation(line: 638, column: 12, scope: !2626)
!2628 = !DILocation(line: 638, column: 32, scope: !2626)
!2629 = !DILocation(line: 639, column: 6, scope: !2626)
!2630 = !DILocation(line: 639, column: 12, scope: !2626)
!2631 = !DILocation(line: 639, column: 21, scope: !2626)
!2632 = !DILocation(line: 639, column: 30, scope: !2626)
!2633 = !DILocation(line: 639, column: 50, scope: !2626)
!2634 = !DILocation(line: 640, column: 5, scope: !2626)
!2635 = !DILocation(line: 640, column: 11, scope: !2626)
!2636 = !DILocation(line: 640, column: 17, scope: !2626)
!2637 = !DILocation(line: 640, column: 22, scope: !2626)
!2638 = !DILocation(line: 640, column: 35, scope: !2626)
!2639 = !DILocation(line: 638, column: 6, scope: !2640)
!2640 = !DILexicalBlockFile(scope: !1721, file: !1, discriminator: 1)
!2641 = !DILocalVariable(name: "result", scope: !2642, file: !1, line: 642, type: !554)
!2642 = distinct !DILexicalBlock(scope: !2626, file: !1, line: 640, column: 43)
!2643 = !DILocation(line: 642, column: 14, scope: !2642)
!2644 = !DILocation(line: 642, column: 23, scope: !2642)
!2645 = !DILocation(line: 644, column: 8, scope: !2646)
!2646 = distinct !DILexicalBlock(scope: !2642, file: !1, line: 644, column: 8)
!2647 = !DILocation(line: 644, column: 8, scope: !2642)
!2648 = !DILocation(line: 645, column: 14, scope: !2646)
!2649 = !DILocation(line: 645, column: 7, scope: !2646)
!2650 = !DILocation(line: 649, column: 28, scope: !2642)
!2651 = !DILocation(line: 649, column: 34, scope: !2642)
!2652 = !DILocation(line: 649, column: 39, scope: !2642)
!2653 = !DILocation(line: 649, column: 11, scope: !2642)
!2654 = !DILocation(line: 649, column: 9, scope: !2642)
!2655 = !DILocation(line: 651, column: 5, scope: !2642)
!2656 = !DILocation(line: 653, column: 33, scope: !1721)
!2657 = !DILocation(line: 653, column: 39, scope: !1721)
!2658 = !DILocation(line: 653, column: 45, scope: !1721)
!2659 = !DILocation(line: 653, column: 50, scope: !1721)
!2660 = !DILocation(line: 653, column: 10, scope: !1721)
!2661 = !DILocation(line: 653, column: 3, scope: !1721)
!2662 = !DILocation(line: 654, column: 1, scope: !1721)
!2663 = !DILocalVariable(name: "data", arg: 1, scope: !1734, file: !1, line: 50, type: !544)
!2664 = !DILocation(line: 50, column: 50, scope: !1734)
!2665 = !DILocalVariable(name: "startPtr", arg: 2, scope: !1734, file: !1, line: 51, type: !215)
!2666 = !DILocation(line: 51, column: 38, scope: !1734)
!2667 = !DILocalVariable(name: "size", arg: 3, scope: !1734, file: !1, line: 51, type: !158)
!2668 = !DILocation(line: 51, column: 55, scope: !1734)
!2669 = !DILocalVariable(name: "inPtr", scope: !1734, file: !1, line: 53, type: !215)
!2670 = !DILocation(line: 53, column: 9, scope: !1734)
!2671 = !DILocalVariable(name: "outPtr", scope: !1734, file: !1, line: 53, type: !215)
!2672 = !DILocation(line: 53, column: 17, scope: !1734)
!2673 = !DILocation(line: 56, column: 7, scope: !2674)
!2674 = distinct !DILexicalBlock(scope: !1734, file: !1, line: 56, column: 6)
!2675 = !DILocation(line: 56, column: 16, scope: !2674)
!2676 = !DILocation(line: 56, column: 25, scope: !2674)
!2677 = !DILocation(line: 56, column: 29, scope: !2678)
!2678 = !DILexicalBlockFile(scope: !2674, file: !1, discriminator: 1)
!2679 = !DILocation(line: 56, column: 34, scope: !2678)
!2680 = !DILocation(line: 56, column: 6, scope: !2678)
!2681 = !DILocation(line: 57, column: 12, scope: !2682)
!2682 = distinct !DILexicalBlock(scope: !2674, file: !1, line: 56, column: 40)
!2683 = !DILocation(line: 57, column: 5, scope: !2682)
!2684 = !DILocation(line: 60, column: 6, scope: !2685)
!2685 = distinct !DILexicalBlock(scope: !1734, file: !1, line: 60, column: 6)
!2686 = !DILocation(line: 60, column: 12, scope: !2685)
!2687 = !DILocation(line: 60, column: 18, scope: !2685)
!2688 = !DILocation(line: 60, column: 6, scope: !1734)
!2689 = !DILocation(line: 63, column: 9, scope: !2690)
!2690 = distinct !DILexicalBlock(scope: !2691, file: !1, line: 63, column: 8)
!2691 = distinct !DILexicalBlock(scope: !2685, file: !1, line: 60, column: 46)
!2692 = !DILocation(line: 63, column: 8, scope: !2690)
!2693 = !DILocation(line: 63, column: 18, scope: !2690)
!2694 = !DILocation(line: 63, column: 8, scope: !2691)
!2695 = !DILocation(line: 66, column: 15, scope: !2696)
!2696 = distinct !DILexicalBlock(scope: !2690, file: !1, line: 63, column: 27)
!2697 = !DILocation(line: 66, column: 25, scope: !2696)
!2698 = !DILocation(line: 66, column: 33, scope: !2696)
!2699 = !DILocation(line: 66, column: 37, scope: !2696)
!2700 = !DILocation(line: 66, column: 41, scope: !2696)
!2701 = !DILocation(line: 66, column: 7, scope: !2696)
!2702 = !DILocation(line: 67, column: 11, scope: !2696)
!2703 = !DILocation(line: 69, column: 7, scope: !2696)
!2704 = !DILocation(line: 69, column: 13, scope: !2696)
!2705 = !DILocation(line: 69, column: 19, scope: !2696)
!2706 = !DILocation(line: 69, column: 35, scope: !2696)
!2707 = !DILocation(line: 70, column: 5, scope: !2696)
!2708 = !DILocation(line: 71, column: 5, scope: !2691)
!2709 = !DILocation(line: 71, column: 11, scope: !2691)
!2710 = !DILocation(line: 71, column: 17, scope: !2691)
!2711 = !DILocation(line: 71, column: 44, scope: !2691)
!2712 = !DILocation(line: 72, column: 3, scope: !2691)
!2713 = !DILocation(line: 75, column: 27, scope: !1734)
!2714 = !DILocation(line: 75, column: 43, scope: !1734)
!2715 = !DILocation(line: 75, column: 20, scope: !1734)
!2716 = !DILocation(line: 75, column: 18, scope: !1734)
!2717 = !DILocation(line: 75, column: 9, scope: !1734)
!2718 = !DILocation(line: 76, column: 6, scope: !2719)
!2719 = distinct !DILexicalBlock(scope: !1734, file: !1, line: 76, column: 6)
!2720 = !DILocation(line: 76, column: 6, scope: !1734)
!2721 = !DILocation(line: 78, column: 5, scope: !2722)
!2722 = distinct !DILexicalBlock(scope: !2719, file: !1, line: 76, column: 13)
!2723 = !DILocation(line: 78, column: 11, scope: !2724)
!2724 = !DILexicalBlockFile(scope: !2722, file: !1, discriminator: 1)
!2725 = !DILocation(line: 78, column: 20, scope: !2724)
!2726 = !DILocation(line: 78, column: 29, scope: !2724)
!2727 = !DILocation(line: 78, column: 28, scope: !2724)
!2728 = !DILocation(line: 78, column: 33, scope: !2724)
!2729 = !DILocation(line: 78, column: 17, scope: !2724)
!2730 = !DILocation(line: 78, column: 5, scope: !2724)
!2731 = !DILocation(line: 80, column: 17, scope: !2732)
!2732 = distinct !DILexicalBlock(scope: !2733, file: !1, line: 80, column: 10)
!2733 = distinct !DILexicalBlock(scope: !2722, file: !1, line: 78, column: 38)
!2734 = !DILocation(line: 80, column: 10, scope: !2732)
!2735 = !DILocation(line: 80, column: 35, scope: !2732)
!2736 = !DILocation(line: 80, column: 10, scope: !2733)
!2737 = !DILocation(line: 82, column: 14, scope: !2738)
!2738 = distinct !DILexicalBlock(scope: !2732, file: !1, line: 80, column: 41)
!2739 = !DILocation(line: 83, column: 20, scope: !2738)
!2740 = !DILocation(line: 83, column: 19, scope: !2738)
!2741 = !DILocation(line: 83, column: 10, scope: !2738)
!2742 = !DILocation(line: 83, column: 17, scope: !2738)
!2743 = !DILocation(line: 85, column: 9, scope: !2738)
!2744 = !DILocation(line: 85, column: 15, scope: !2738)
!2745 = !DILocation(line: 85, column: 21, scope: !2738)
!2746 = !DILocation(line: 85, column: 37, scope: !2738)
!2747 = !DILocation(line: 86, column: 7, scope: !2738)
!2748 = !DILocation(line: 88, column: 13, scope: !2749)
!2749 = distinct !DILexicalBlock(scope: !2750, file: !1, line: 88, column: 12)
!2750 = distinct !DILexicalBlock(scope: !2732, file: !1, line: 87, column: 12)
!2751 = !DILocation(line: 88, column: 12, scope: !2749)
!2752 = !DILocation(line: 88, column: 19, scope: !2749)
!2753 = !DILocation(line: 88, column: 12, scope: !2750)
!2754 = !DILocation(line: 90, column: 12, scope: !2755)
!2755 = distinct !DILexicalBlock(scope: !2749, file: !1, line: 88, column: 28)
!2756 = !DILocation(line: 90, column: 19, scope: !2755)
!2757 = !DILocation(line: 91, column: 9, scope: !2755)
!2758 = !DILocation(line: 94, column: 22, scope: !2759)
!2759 = distinct !DILexicalBlock(scope: !2749, file: !1, line: 92, column: 14)
!2760 = !DILocation(line: 94, column: 21, scope: !2759)
!2761 = !DILocation(line: 94, column: 12, scope: !2759)
!2762 = !DILocation(line: 94, column: 19, scope: !2759)
!2763 = !DILocation(line: 97, column: 13, scope: !2733)
!2764 = !DILocation(line: 98, column: 12, scope: !2733)
!2765 = !DILocation(line: 78, column: 5, scope: !2766)
!2766 = !DILexicalBlockFile(scope: !2722, file: !1, discriminator: 2)
!2767 = !DILocation(line: 101, column: 8, scope: !2768)
!2768 = distinct !DILexicalBlock(scope: !2722, file: !1, line: 101, column: 8)
!2769 = !DILocation(line: 101, column: 16, scope: !2768)
!2770 = !DILocation(line: 101, column: 25, scope: !2768)
!2771 = !DILocation(line: 101, column: 24, scope: !2768)
!2772 = !DILocation(line: 101, column: 14, scope: !2768)
!2773 = !DILocation(line: 101, column: 8, scope: !2722)
!2774 = !DILocation(line: 103, column: 11, scope: !2775)
!2775 = distinct !DILexicalBlock(scope: !2776, file: !1, line: 103, column: 10)
!2776 = distinct !DILexicalBlock(scope: !2768, file: !1, line: 101, column: 31)
!2777 = !DILocation(line: 103, column: 10, scope: !2775)
!2778 = !DILocation(line: 103, column: 17, scope: !2775)
!2779 = !DILocation(line: 103, column: 10, scope: !2776)
!2780 = !DILocation(line: 105, column: 10, scope: !2781)
!2781 = distinct !DILexicalBlock(scope: !2775, file: !1, line: 103, column: 26)
!2782 = !DILocation(line: 105, column: 17, scope: !2781)
!2783 = !DILocation(line: 107, column: 9, scope: !2781)
!2784 = !DILocation(line: 107, column: 15, scope: !2781)
!2785 = !DILocation(line: 107, column: 21, scope: !2781)
!2786 = !DILocation(line: 107, column: 48, scope: !2781)
!2787 = !DILocation(line: 108, column: 7, scope: !2781)
!2788 = !DILocation(line: 111, column: 20, scope: !2789)
!2789 = distinct !DILexicalBlock(scope: !2775, file: !1, line: 109, column: 12)
!2790 = !DILocation(line: 111, column: 19, scope: !2789)
!2791 = !DILocation(line: 111, column: 10, scope: !2789)
!2792 = !DILocation(line: 111, column: 17, scope: !2789)
!2793 = !DILocation(line: 113, column: 13, scope: !2776)
!2794 = !DILocation(line: 114, column: 5, scope: !2776)
!2795 = !DILocation(line: 115, column: 8, scope: !2796)
!2796 = distinct !DILexicalBlock(scope: !2722, file: !1, line: 115, column: 8)
!2797 = !DILocation(line: 115, column: 17, scope: !2796)
!2798 = !DILocation(line: 115, column: 26, scope: !2796)
!2799 = !DILocation(line: 115, column: 25, scope: !2796)
!2800 = !DILocation(line: 115, column: 15, scope: !2796)
!2801 = !DILocation(line: 115, column: 8, scope: !2722)
!2802 = !DILocation(line: 117, column: 8, scope: !2796)
!2803 = !DILocation(line: 117, column: 15, scope: !2796)
!2804 = !DILocation(line: 117, column: 7, scope: !2796)
!2805 = !DILocation(line: 119, column: 13, scope: !2722)
!2806 = !DILocation(line: 119, column: 22, scope: !2722)
!2807 = !DILocation(line: 119, column: 20, scope: !2722)
!2808 = !DILocation(line: 119, column: 5, scope: !2722)
!2809 = !DILocation(line: 121, column: 10, scope: !1734)
!2810 = !DILocation(line: 121, column: 3, scope: !1734)
!2811 = !DILocation(line: 122, column: 1, scope: !1734)
!2812 = !DILocalVariable(name: "sockfd", arg: 1, scope: !1722, file: !1, line: 656, type: !248)
!2813 = !DILocation(line: 656, column: 40, scope: !1722)
!2814 = !DILocalVariable(name: "buf", arg: 2, scope: !1722, file: !1, line: 657, type: !215)
!2815 = !DILocation(line: 657, column: 32, scope: !1722)
!2816 = !DILocalVariable(name: "bytesfromsocket", arg: 3, scope: !1722, file: !1, line: 658, type: !158)
!2817 = !DILocation(line: 658, column: 33, scope: !1722)
!2818 = !DILocalVariable(name: "n", arg: 4, scope: !1722, file: !1, line: 659, type: !1459)
!2819 = !DILocation(line: 659, column: 35, scope: !1722)
!2820 = !DILocalVariable(name: "nread", scope: !1722, file: !1, line: 661, type: !256)
!2821 = !DILocation(line: 661, column: 11, scope: !1722)
!2822 = !DILocation(line: 661, column: 19, scope: !1722)
!2823 = !DILocation(line: 663, column: 12, scope: !2824)
!2824 = distinct !DILexicalBlock(scope: !1722, file: !1, line: 663, column: 6)
!2825 = !DILocation(line: 663, column: 9, scope: !2824)
!2826 = !DILocation(line: 663, column: 6, scope: !1722)
!2827 = !DILocalVariable(name: "err", scope: !2828, file: !1, line: 664, type: !177)
!2828 = distinct !DILexicalBlock(scope: !2824, file: !1, line: 663, column: 19)
!2829 = !DILocation(line: 664, column: 9, scope: !2828)
!2830 = !DILocation(line: 664, column: 15, scope: !2828)
!2831 = !DILocalVariable(name: "return_error", scope: !2828, file: !1, line: 665, type: !177)
!2832 = !DILocation(line: 665, column: 9, scope: !2828)
!2833 = !DILocation(line: 669, column: 35, scope: !2828)
!2834 = !DILocation(line: 669, column: 32, scope: !2828)
!2835 = !DILocation(line: 669, column: 39, scope: !2828)
!2836 = !DILocation(line: 669, column: 52, scope: !2837)
!2837 = !DILexicalBlockFile(scope: !2828, file: !1, discriminator: 1)
!2838 = !DILocation(line: 669, column: 49, scope: !2837)
!2839 = !DILocation(line: 669, column: 56, scope: !2837)
!2840 = !DILocation(line: 669, column: 68, scope: !2841)
!2841 = !DILexicalBlockFile(scope: !2828, file: !1, discriminator: 2)
!2842 = !DILocation(line: 669, column: 65, scope: !2841)
!2843 = !DILocation(line: 669, column: 56, scope: !2841)
!2844 = !DILocation(line: 669, column: 56, scope: !2845)
!2845 = !DILexicalBlockFile(scope: !2828, file: !1, discriminator: 3)
!2846 = !DILocation(line: 669, column: 18, scope: !2845)
!2847 = !DILocation(line: 671, column: 8, scope: !2848)
!2848 = distinct !DILexicalBlock(scope: !2828, file: !1, line: 671, column: 8)
!2849 = !DILocation(line: 671, column: 8, scope: !2828)
!2850 = !DILocation(line: 672, column: 7, scope: !2848)
!2851 = !DILocation(line: 673, column: 5, scope: !2828)
!2852 = !DILocation(line: 677, column: 8, scope: !1722)
!2853 = !DILocation(line: 677, column: 4, scope: !1722)
!2854 = !DILocation(line: 677, column: 6, scope: !1722)
!2855 = !DILocation(line: 678, column: 3, scope: !1722)
!2856 = !DILocation(line: 679, column: 1, scope: !1722)
!2857 = !DILocalVariable(name: "conn", arg: 1, scope: !1725, file: !1, line: 687, type: !550)
!2858 = !DILocation(line: 687, column: 40, scope: !1725)
!2859 = !DILocalVariable(name: "sockfd", arg: 2, scope: !1725, file: !1, line: 688, type: !248)
!2860 = !DILocation(line: 688, column: 34, scope: !1725)
!2861 = !DILocalVariable(name: "buf", arg: 3, scope: !1725, file: !1, line: 689, type: !215)
!2862 = !DILocation(line: 689, column: 26, scope: !1725)
!2863 = !DILocalVariable(name: "sizerequested", arg: 4, scope: !1725, file: !1, line: 690, type: !158)
!2864 = !DILocation(line: 690, column: 27, scope: !1725)
!2865 = !DILocalVariable(name: "n", arg: 5, scope: !1725, file: !1, line: 691, type: !1459)
!2866 = !DILocation(line: 691, column: 29, scope: !1725)
!2867 = !DILocalVariable(name: "result", scope: !1725, file: !1, line: 693, type: !554)
!2868 = !DILocation(line: 693, column: 12, scope: !1725)
!2869 = !DILocalVariable(name: "nread", scope: !1725, file: !1, line: 694, type: !256)
!2870 = !DILocation(line: 694, column: 11, scope: !1725)
!2871 = !DILocalVariable(name: "bytesfromsocket", scope: !1725, file: !1, line: 695, type: !158)
!2872 = !DILocation(line: 695, column: 10, scope: !1725)
!2873 = !DILocalVariable(name: "buffertofill", scope: !1725, file: !1, line: 696, type: !215)
!2874 = !DILocation(line: 696, column: 9, scope: !1725)
!2875 = !DILocalVariable(name: "pipelining", scope: !1725, file: !1, line: 699, type: !211)
!2876 = !DILocation(line: 699, column: 8, scope: !1725)
!2877 = !DILocation(line: 699, column: 42, scope: !1725)
!2878 = !DILocation(line: 699, column: 48, scope: !1725)
!2879 = !DILocation(line: 699, column: 54, scope: !1725)
!2880 = !DILocation(line: 699, column: 21, scope: !1725)
!2881 = !DILocation(line: 699, column: 77, scope: !1725)
!2882 = !DILocation(line: 700, column: 6, scope: !1725)
!2883 = !DILocation(line: 700, column: 12, scope: !1725)
!2884 = !DILocation(line: 700, column: 20, scope: !1725)
!2885 = !DILocation(line: 700, column: 29, scope: !1725)
!2886 = !DILocation(line: 699, column: 8, scope: !2887)
!2887 = !DILexicalBlockFile(scope: !1725, file: !1, discriminator: 1)
!2888 = !DILocalVariable(name: "num", scope: !1725, file: !1, line: 705, type: !177)
!2889 = !DILocation(line: 705, column: 7, scope: !1725)
!2890 = !DILocation(line: 705, column: 14, scope: !1725)
!2891 = !DILocation(line: 705, column: 24, scope: !1725)
!2892 = !DILocation(line: 705, column: 30, scope: !1725)
!2893 = !DILocation(line: 705, column: 21, scope: !1725)
!2894 = !DILocation(line: 707, column: 4, scope: !1725)
!2895 = !DILocation(line: 707, column: 5, scope: !1725)
!2896 = !DILocation(line: 710, column: 6, scope: !2897)
!2897 = distinct !DILexicalBlock(scope: !1725, file: !1, line: 710, column: 6)
!2898 = !DILocation(line: 710, column: 6, scope: !1725)
!2899 = !DILocalVariable(name: "bytestocopy", scope: !2900, file: !1, line: 711, type: !158)
!2900 = distinct !DILexicalBlock(scope: !2897, file: !1, line: 710, column: 18)
!2901 = !DILocation(line: 711, column: 12, scope: !2900)
!2902 = !DILocation(line: 711, column: 26, scope: !2900)
!2903 = !DILocation(line: 711, column: 26, scope: !2904)
!2904 = !DILexicalBlockFile(scope: !2900, file: !1, discriminator: 1)
!2905 = !DILocation(line: 711, column: 26, scope: !2906)
!2906 = !DILexicalBlockFile(scope: !2900, file: !1, discriminator: 2)
!2907 = !DILocation(line: 711, column: 26, scope: !2908)
!2908 = !DILexicalBlockFile(scope: !2900, file: !1, discriminator: 3)
!2909 = !DILocation(line: 711, column: 12, scope: !2908)
!2910 = !DILocation(line: 715, column: 8, scope: !2911)
!2911 = distinct !DILexicalBlock(scope: !2900, file: !1, line: 715, column: 8)
!2912 = !DILocation(line: 715, column: 20, scope: !2911)
!2913 = !DILocation(line: 715, column: 8, scope: !2900)
!2914 = !DILocation(line: 716, column: 14, scope: !2915)
!2915 = distinct !DILexicalBlock(scope: !2911, file: !1, line: 715, column: 25)
!2916 = !DILocation(line: 716, column: 19, scope: !2915)
!2917 = !DILocation(line: 716, column: 25, scope: !2915)
!2918 = !DILocation(line: 716, column: 41, scope: !2915)
!2919 = !DILocation(line: 716, column: 47, scope: !2915)
!2920 = !DILocation(line: 716, column: 39, scope: !2915)
!2921 = !DILocation(line: 716, column: 57, scope: !2915)
!2922 = !DILocation(line: 716, column: 7, scope: !2915)
!2923 = !DILocation(line: 717, column: 25, scope: !2915)
!2924 = !DILocation(line: 717, column: 7, scope: !2915)
!2925 = !DILocation(line: 717, column: 13, scope: !2915)
!2926 = !DILocation(line: 717, column: 22, scope: !2915)
!2927 = !DILocation(line: 718, column: 7, scope: !2915)
!2928 = !DILocation(line: 718, column: 13, scope: !2915)
!2929 = !DILocation(line: 718, column: 18, scope: !2915)
!2930 = !DILocation(line: 718, column: 37, scope: !2915)
!2931 = !DILocation(line: 720, column: 21, scope: !2915)
!2932 = !DILocation(line: 720, column: 8, scope: !2915)
!2933 = !DILocation(line: 720, column: 10, scope: !2915)
!2934 = !DILocation(line: 721, column: 7, scope: !2915)
!2935 = !DILocation(line: 725, column: 23, scope: !2900)
!2936 = !DILocation(line: 725, column: 23, scope: !2904)
!2937 = !DILocation(line: 725, column: 23, scope: !2906)
!2938 = !DILocation(line: 725, column: 23, scope: !2908)
!2939 = !DILocation(line: 725, column: 21, scope: !2908)
!2940 = !DILocation(line: 726, column: 20, scope: !2900)
!2941 = !DILocation(line: 726, column: 26, scope: !2900)
!2942 = !DILocation(line: 726, column: 18, scope: !2900)
!2943 = !DILocation(line: 727, column: 3, scope: !2900)
!2944 = !DILocation(line: 729, column: 23, scope: !2945)
!2945 = distinct !DILexicalBlock(scope: !2897, file: !1, line: 728, column: 8)
!2946 = !DILocation(line: 729, column: 23, scope: !2947)
!2947 = !DILexicalBlockFile(scope: !2945, file: !1, discriminator: 1)
!2948 = !DILocation(line: 729, column: 23, scope: !2949)
!2949 = !DILexicalBlockFile(scope: !2945, file: !1, discriminator: 2)
!2950 = !DILocation(line: 729, column: 23, scope: !2951)
!2951 = !DILexicalBlockFile(scope: !2945, file: !1, discriminator: 3)
!2952 = !DILocation(line: 729, column: 23, scope: !2953)
!2953 = !DILexicalBlockFile(scope: !2945, file: !1, discriminator: 4)
!2954 = !DILocation(line: 729, column: 23, scope: !2955)
!2955 = !DILexicalBlockFile(scope: !2945, file: !1, discriminator: 5)
!2956 = !DILocation(line: 729, column: 23, scope: !2957)
!2957 = !DILexicalBlockFile(scope: !2945, file: !1, discriminator: 6)
!2958 = !DILocation(line: 729, column: 23, scope: !2959)
!2959 = !DILexicalBlockFile(scope: !2945, file: !1, discriminator: 7)
!2960 = !DILocation(line: 729, column: 23, scope: !2961)
!2961 = !DILexicalBlockFile(scope: !2945, file: !1, discriminator: 8)
!2962 = !DILocation(line: 729, column: 23, scope: !2963)
!2963 = !DILexicalBlockFile(scope: !2945, file: !1, discriminator: 9)
!2964 = !DILocation(line: 729, column: 21, scope: !2963)
!2965 = !DILocation(line: 732, column: 20, scope: !2945)
!2966 = !DILocation(line: 732, column: 18, scope: !2945)
!2967 = !DILocation(line: 735, column: 22, scope: !1725)
!2968 = !DILocation(line: 735, column: 11, scope: !1725)
!2969 = !DILocation(line: 735, column: 17, scope: !1725)
!2970 = !DILocation(line: 735, column: 27, scope: !1725)
!2971 = !DILocation(line: 735, column: 33, scope: !1725)
!2972 = !DILocation(line: 735, column: 38, scope: !1725)
!2973 = !DILocation(line: 735, column: 52, scope: !1725)
!2974 = !DILocation(line: 735, column: 9, scope: !1725)
!2975 = !DILocation(line: 736, column: 6, scope: !2976)
!2976 = distinct !DILexicalBlock(scope: !1725, file: !1, line: 736, column: 6)
!2977 = !DILocation(line: 736, column: 12, scope: !2976)
!2978 = !DILocation(line: 736, column: 6, scope: !1725)
!2979 = !DILocation(line: 737, column: 12, scope: !2976)
!2980 = !DILocation(line: 737, column: 5, scope: !2976)
!2981 = !DILocation(line: 739, column: 6, scope: !2982)
!2982 = distinct !DILexicalBlock(scope: !1725, file: !1, line: 739, column: 6)
!2983 = !DILocation(line: 739, column: 6, scope: !1725)
!2984 = !DILocation(line: 740, column: 12, scope: !2985)
!2985 = distinct !DILexicalBlock(scope: !2982, file: !1, line: 739, column: 18)
!2986 = !DILocation(line: 740, column: 17, scope: !2985)
!2987 = !DILocation(line: 740, column: 23, scope: !2985)
!2988 = !DILocation(line: 740, column: 38, scope: !2985)
!2989 = !DILocation(line: 740, column: 5, scope: !2985)
!2990 = !DILocation(line: 741, column: 21, scope: !2985)
!2991 = !DILocation(line: 741, column: 5, scope: !2985)
!2992 = !DILocation(line: 741, column: 11, scope: !2985)
!2993 = !DILocation(line: 741, column: 19, scope: !2985)
!2994 = !DILocation(line: 742, column: 22, scope: !2985)
!2995 = !DILocation(line: 742, column: 5, scope: !2985)
!2996 = !DILocation(line: 742, column: 11, scope: !2985)
!2997 = !DILocation(line: 742, column: 20, scope: !2985)
!2998 = !DILocation(line: 743, column: 3, scope: !2985)
!2999 = !DILocation(line: 745, column: 9, scope: !1725)
!3000 = !DILocation(line: 745, column: 4, scope: !1725)
!3001 = !DILocation(line: 745, column: 6, scope: !1725)
!3002 = !DILocation(line: 747, column: 3, scope: !1725)
!3003 = !DILocation(line: 748, column: 1, scope: !1725)
!3004 = !DILocalVariable(name: "data", arg: 1, scope: !1737, file: !1, line: 751, type: !544)
!3005 = !DILocation(line: 751, column: 37, scope: !1737)
!3006 = !DILocalVariable(name: "type", arg: 2, scope: !1737, file: !1, line: 751, type: !756)
!3007 = !DILocation(line: 751, column: 57, scope: !1737)
!3008 = !DILocalVariable(name: "ptr", arg: 3, scope: !1737, file: !1, line: 752, type: !215)
!3009 = !DILocation(line: 752, column: 25, scope: !1737)
!3010 = !DILocalVariable(name: "size", arg: 4, scope: !1737, file: !1, line: 752, type: !158)
!3011 = !DILocation(line: 752, column: 37, scope: !1737)
!3012 = !DILocation(line: 797, column: 6, scope: !3013)
!3013 = distinct !DILexicalBlock(scope: !1737, file: !1, line: 797, column: 6)
!3014 = !DILocation(line: 797, column: 12, scope: !3013)
!3015 = !DILocation(line: 797, column: 16, scope: !3013)
!3016 = !DILocation(line: 797, column: 6, scope: !1737)
!3017 = !DILocation(line: 798, column: 14, scope: !3013)
!3018 = !DILocation(line: 798, column: 20, scope: !3013)
!3019 = !DILocation(line: 798, column: 24, scope: !3013)
!3020 = !DILocation(line: 798, column: 32, scope: !3013)
!3021 = !DILocation(line: 798, column: 38, scope: !3013)
!3022 = !DILocation(line: 798, column: 44, scope: !3013)
!3023 = !DILocation(line: 798, column: 49, scope: !3013)
!3024 = !DILocation(line: 799, column: 32, scope: !3013)
!3025 = !DILocation(line: 799, column: 38, scope: !3013)
!3026 = !DILocation(line: 799, column: 42, scope: !3013)
!3027 = !DILocation(line: 798, column: 12, scope: !3013)
!3028 = !DILocation(line: 798, column: 5, scope: !3013)
!3029 = !DILocation(line: 801, column: 10, scope: !1737)
!3030 = !DILocation(line: 801, column: 3, scope: !1737)
!3031 = !DILocation(line: 805, column: 23, scope: !3032)
!3032 = distinct !DILexicalBlock(scope: !1737, file: !1, line: 801, column: 16)
!3033 = !DILocation(line: 805, column: 12, scope: !3032)
!3034 = !DILocation(line: 805, column: 36, scope: !3032)
!3035 = !DILocation(line: 805, column: 42, scope: !3032)
!3036 = !DILocation(line: 805, column: 46, scope: !3032)
!3037 = !DILocation(line: 805, column: 5, scope: !3032)
!3038 = !DILocation(line: 806, column: 12, scope: !3032)
!3039 = !DILocation(line: 806, column: 17, scope: !3032)
!3040 = !DILocation(line: 806, column: 26, scope: !3032)
!3041 = !DILocation(line: 806, column: 32, scope: !3032)
!3042 = !DILocation(line: 806, column: 36, scope: !3032)
!3043 = !DILocation(line: 806, column: 5, scope: !3032)
!3044 = !DILocation(line: 813, column: 5, scope: !3032)
!3045 = !DILocation(line: 815, column: 5, scope: !3032)
!3046 = !DILocation(line: 817, column: 3, scope: !1737)
!3047 = !DILocation(line: 818, column: 1, scope: !1737)
