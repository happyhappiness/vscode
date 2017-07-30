; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hostip.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.curl_hash = type { %struct.curl_llist*, i64 (i8*, i64, i64)*, i64 (i8*, i64, i8*, i64)*, void (i8*)*, i32, i64 }
%struct.curl_llist = type { %struct.curl_llist_element*, %struct.curl_llist_element*, void (i8*, i8*)*, i64 }
%struct.curl_llist_element = type { i8*, %struct.curl_llist_element*, %struct.curl_llist_element* }
%struct.__jmp_buf_tag = type { [8 x i64], i32, %struct.__sigset_t }
%struct.__sigset_t = type { [16 x i64] }
%struct.Curl_dns_entry = type { %struct.Curl_addrinfo*, i64, i64 }
%struct.Curl_addrinfo = type { i32, i32, i32, i32, i32, i8*, %struct.sockaddr*, %struct.Curl_addrinfo* }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.sockaddr_in = type { i16, i16, %struct.in_addr, [8 x i8] }
%struct.in_addr = type { i32 }
%struct.Curl_easy = type { %struct.Curl_easy*, %struct.Curl_easy*, %struct.connectdata*, i32, i32, %struct.Curl_message, [5 x i32], i32, %struct.Names, %struct.Curl_multi*, %struct.Curl_multi*, %struct.Curl_share*, %struct.SingleRequest, %struct.UserDefined, %struct.DynamicStatic, %struct.CookieInfo*, %struct.Progress, %struct.UrlState, %struct.WildcardData, %struct.PureInfo, %struct.curl_tlssessioninfo, i32 }
%struct.connectdata = type { %struct.Curl_easy*, %struct.Curl_chunker, i32 (i8*, i32)*, i8*, i8, i64, %struct.Curl_dns_entry*, %struct.Curl_addrinfo*, [2 x %struct.Curl_addrinfo*], [46 x i8], i32, i32, %struct.hostname, i8*, %struct.hostname, %struct.proxy_info, %struct.proxy_info, i64, i32, i32, i16, [46 x i8], i64, [46 x i8], i64, i8*, i8*, i8*, i8*, i32, i32, %struct.timeval, %struct.timeval, [2 x i32], [2 x i32], [2 x i8], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x i64 (%struct.connectdata*, i32, i8*, i64, i32*)*], [2 x %struct.ssl_connect_data], [2 x %struct.ssl_connect_data], %struct.ssl_primary_config, %struct.ssl_primary_config, i8, %struct.ConnectBits, %struct.timeval, i32, i64, %struct.Curl_handler*, %struct.Curl_handler*, i64, i32, i32, %struct.dynamically_allocated_data, i8, i8, %struct.curl_llist, %struct.curl_llist, i8*, i64, i64, i32 (i8*, i64, i32)*, i8*, [256 x i8], i8*, i32, i32, %union.anon, i32, i32, i8*, i16, i32, [2 x i32], %struct.connectbundle*, i32 }
%struct.Curl_chunker = type { [17 x i8], i32, i32, i64, i64 }
%struct.hostname = type { i8*, i8*, i8*, i8* }
%struct.proxy_info = type { %struct.hostname, i64, i32, i8*, i8* }
%struct.ssl_connect_data = type { i8, i32, i32 }
%struct.ssl_primary_config = type { i64, i64, i8, i8, i8, i8*, i8*, i8*, i8*, i8*, i8*, i8 }
%struct.ConnectBits = type { i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, [2 x i8], i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, i8, [2 x i8], i8 }
%struct.timeval = type { i64, i64 }
%struct.Curl_handler = type { i8*, i32 (%struct.connectdata*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32, i1)*, i32 (%struct.connectdata*, i32*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i8*)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i32*, i32)*, i32 (%struct.connectdata*, i1)*, i32 (%struct.Curl_easy*, %struct.connectdata*, i64*, i8*)*, i64, i32, i32 }
%struct.dynamically_allocated_data = type { i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8* }
%union.anon = type { %struct.ftp_conn }
%struct.ftp_conn = type { %struct.pingpong, i8*, i8**, i32, i32, i8*, i8, i8, i8, i8, i8, i8*, i8, i32, i32, i32, i32, i32, i64, i8*, i64, i8*, i16 }
%struct.pingpong = type { i8*, i64, i64, i8*, i8, i8*, i64, i64, %struct.timeval, i64, %struct.connectdata*, i32 (%struct.connectdata*)*, i1 (%struct.connectdata*, i8*, i64, i32*)* }
%struct.connectbundle = type { i32, i64, %struct.curl_llist }
%struct.Curl_message = type { %struct.CURLMsg }
%struct.CURLMsg = type { i32, %struct.Curl_easy*, %union.anon.0 }
%union.anon.0 = type { i8* }
%struct.Names = type { %struct.curl_hash*, i32 }
%struct.Curl_multi = type { i64, %struct.Curl_easy*, %struct.Curl_easy*, i32, i32, %struct.curl_llist, %struct.curl_llist, i32 (%struct.Curl_easy*, i32, i32, i8*, i8*)*, i8*, i32 (%struct.Curl_easy*, %struct.Curl_easy*, i64, %struct.curl_pushheaders*, i8*)*, i8*, %struct.curl_hash, %struct.Curl_tree*, %struct.curl_hash, i64, i8, %struct.conncache, %struct.Curl_easy*, i64, i64, i64, i64, i64, i64, %struct.curl_llist, %struct.curl_llist, i32 (%struct.Curl_multi*, i64, i8*)*, i8*, %struct.timeval }
%struct.curl_pushheaders = type opaque
%struct.Curl_tree = type { %struct.Curl_tree*, %struct.Curl_tree*, %struct.Curl_tree*, %struct.Curl_tree*, %struct.timeval, i8* }
%struct.conncache = type { %struct.curl_hash, i64, i64, %struct.timeval }
%struct.Curl_share = type { i32, i32, void (%struct.Curl_easy*, i32, i32, i8*)*, void (%struct.Curl_easy*, i32, i8*)*, i8*, %struct.curl_hash, %struct.CookieInfo*, %struct.curl_ssl_session*, i64, i64 }
%struct.curl_ssl_session = type { i8*, i8*, i8*, i8*, i64, i64, i32, i32, %struct.ssl_primary_config }
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
%struct.tempbuf = type { i8*, i64, i32 }
%struct.digestdata = type { i8*, i8*, i8*, i32, i8, i8*, i8*, i8*, i32 }
%struct.auth = type { i64, i64, i64, i8, i8, i8 }
%struct.WildcardData = type { i32, i8*, i8*, %struct.curl_llist, i8*, void (i8*)*, i8* }
%struct.PureInfo = type { i32, i32, i32, i64, i8, i64, i64, i64, i64, i64, i8*, i8*, [46 x i8], i64, [46 x i8], i64, i8*, i32, %struct.curl_certinfo }
%struct.curl_certinfo = type { i32, %struct.curl_slist** }
%struct.curl_tlssessioninfo = type { i32, i8* }
%struct.hostcache_prune_data = type { i64, i64 }
%struct.sigaction = type { %union.anon.1, %struct.__sigset_t, i32, void ()* }
%union.anon.1 = type { void (i32)* }

@host_cache_initialized = internal global i32 0, align 4
@hostname_cache = internal global %struct.curl_hash zeroinitializer, align 8
@Curl_ccalloc = external global i8* (i64, i64)*, align 8
@Curl_cfree = external global void (i8*)*, align 8
@.str = private unnamed_addr constant [36 x i8] c"Hostname %s was found in DNS cache\0A\00", align 1
@.str.1 = private unnamed_addr constant [65 x i8] c"remaining timeout of %ld too small to resolve via SIGALRM method\00", align 1
@curl_jmpenv = common global [1 x %struct.__jmp_buf_tag] zeroinitializer, align 16
@.str.2 = private unnamed_addr constant [22 x i8] c"name lookup timed out\00", align 1
@.str.3 = private unnamed_addr constant [26 x i8] c"Previous alarm fired off!\00", align 1
@.str.4 = private unnamed_addr constant [12 x i8] c"%255[^:]:%d\00", align 1
@.str.5 = private unnamed_addr constant [52 x i8] c"Couldn't parse CURLOPT_RESOLVE removal entry '%s'!\0A\00", align 1
@.str.6 = private unnamed_addr constant [18 x i8] c"%255[^:]:%d:%255s\00", align 1
@.str.7 = private unnamed_addr constant [44 x i8] c"Couldn't parse CURLOPT_RESOLVE entry '%s'!\0A\00", align 1
@.str.8 = private unnamed_addr constant [32 x i8] c"Address in '%s' found illegal!\0A\00", align 1
@.str.9 = private unnamed_addr constant [29 x i8] c"Added %s:%d:%s to DNS cache\0A\00", align 1
@.str.10 = private unnamed_addr constant [41 x i8] c"Hostname in DNS cache was stale, zapped\0A\00", align 1
@.str.11 = private unnamed_addr constant [6 x i8] c"%s:%d\00", align 1

; Function Attrs: nounwind uwtable
define %struct.curl_hash* @Curl_global_host_cache_init() #0 !dbg !1723 {
entry:
  %rc = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !1804, metadata !1805), !dbg !1806
  store i32 0, i32* %rc, align 4, !dbg !1806
  %0 = load i32, i32* @host_cache_initialized, align 4, !dbg !1807
  %tobool = icmp ne i32 %0, 0, !dbg !1807
  br i1 %tobool, label %if.end3, label %if.then, !dbg !1809

if.then:                                          ; preds = %entry
  %call = call i32 @Curl_hash_init(%struct.curl_hash* @hostname_cache, i32 7, i64 (i8*, i64, i64)* @Curl_hash_str, i64 (i8*, i64, i8*, i64)* @Curl_str_key_compare, void (i8*)* @freednsentry), !dbg !1810
  store i32 %call, i32* %rc, align 4, !dbg !1812
  %1 = load i32, i32* %rc, align 4, !dbg !1813
  %tobool1 = icmp ne i32 %1, 0, !dbg !1813
  br i1 %tobool1, label %if.end, label %if.then2, !dbg !1815

if.then2:                                         ; preds = %if.then
  store i32 1, i32* @host_cache_initialized, align 4, !dbg !1816
  br label %if.end, !dbg !1817

if.end:                                           ; preds = %if.then2, %if.then
  br label %if.end3, !dbg !1818

if.end3:                                          ; preds = %if.end, %entry
  %2 = load i32, i32* %rc, align 4, !dbg !1819
  %tobool4 = icmp ne i32 %2, 0, !dbg !1819
  %cond = select i1 %tobool4, %struct.curl_hash* null, %struct.curl_hash* @hostname_cache, !dbg !1819
  ret %struct.curl_hash* %cond, !dbg !1820
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @Curl_hash_init(%struct.curl_hash*, i32, i64 (i8*, i64, i64)*, i64 (i8*, i64, i8*, i64)*, void (i8*)*) #2

declare i64 @Curl_hash_str(i8*, i64, i64) #2

declare i64 @Curl_str_key_compare(i8*, i64, i8*, i64) #2

; Function Attrs: nounwind uwtable
define internal void @freednsentry(i8* %freethis) #0 !dbg !1777 {
entry:
  %freethis.addr = alloca i8*, align 8
  %dns = alloca %struct.Curl_dns_entry*, align 8
  store i8* %freethis, i8** %freethis.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %freethis.addr, metadata !1821, metadata !1805), !dbg !1822
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %dns, metadata !1823, metadata !1805), !dbg !1824
  %0 = load i8*, i8** %freethis.addr, align 8, !dbg !1825
  %1 = bitcast i8* %0 to %struct.Curl_dns_entry*, !dbg !1826
  store %struct.Curl_dns_entry* %1, %struct.Curl_dns_entry** %dns, align 8, !dbg !1824
  br label %do.body, !dbg !1827

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !1828

do.end:                                           ; preds = %do.body
  %2 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !1831
  %inuse = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %2, i32 0, i32 2, !dbg !1832
  %3 = load i64, i64* %inuse, align 8, !dbg !1833
  %dec = add nsw i64 %3, -1, !dbg !1833
  store i64 %dec, i64* %inuse, align 8, !dbg !1833
  %4 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !1834
  %inuse1 = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %4, i32 0, i32 2, !dbg !1836
  %5 = load i64, i64* %inuse1, align 8, !dbg !1836
  %cmp = icmp eq i64 %5, 0, !dbg !1837
  br i1 %cmp, label %if.then, label %if.end, !dbg !1838

if.then:                                          ; preds = %do.end
  %6 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !1839
  %addr = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %6, i32 0, i32 0, !dbg !1841
  %7 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !1841
  call void @Curl_freeaddrinfo(%struct.Curl_addrinfo* %7), !dbg !1842
  %8 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !1843
  %9 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !1843
  %10 = bitcast %struct.Curl_dns_entry* %9 to i8*, !dbg !1843
  call void %8(i8* %10), !dbg !1843
  br label %if.end, !dbg !1844

if.end:                                           ; preds = %if.then, %do.end
  ret void, !dbg !1845
}

; Function Attrs: nounwind uwtable
define void @Curl_global_host_cache_dtor() #0 !dbg !1727 {
entry:
  %0 = load i32, i32* @host_cache_initialized, align 4, !dbg !1846
  %tobool = icmp ne i32 %0, 0, !dbg !1846
  br i1 %tobool, label %if.then, label %if.end, !dbg !1848

if.then:                                          ; preds = %entry
  call void @Curl_hash_destroy(%struct.curl_hash* @hostname_cache), !dbg !1849
  store i32 0, i32* @host_cache_initialized, align 4, !dbg !1851
  br label %if.end, !dbg !1852

if.end:                                           ; preds = %if.then, %entry
  ret void, !dbg !1853
}

declare void @Curl_hash_destroy(%struct.curl_hash*) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_num_addresses(%struct.Curl_addrinfo* %addr) #0 !dbg !1730 {
entry:
  %addr.addr = alloca %struct.Curl_addrinfo*, align 8
  %i = alloca i32, align 4
  store %struct.Curl_addrinfo* %addr, %struct.Curl_addrinfo** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %addr.addr, metadata !1854, metadata !1805), !dbg !1855
  call void @llvm.dbg.declare(metadata i32* %i, metadata !1856, metadata !1805), !dbg !1857
  store i32 0, i32* %i, align 4, !dbg !1857
  br label %while.cond, !dbg !1858

while.cond:                                       ; preds = %while.body, %entry
  %0 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr.addr, align 8, !dbg !1859
  %tobool = icmp ne %struct.Curl_addrinfo* %0, null, !dbg !1861
  br i1 %tobool, label %while.body, label %while.end, !dbg !1861

while.body:                                       ; preds = %while.cond
  %1 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr.addr, align 8, !dbg !1862
  %ai_next = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %1, i32 0, i32 7, !dbg !1864
  %2 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai_next, align 8, !dbg !1864
  store %struct.Curl_addrinfo* %2, %struct.Curl_addrinfo** %addr.addr, align 8, !dbg !1865
  %3 = load i32, i32* %i, align 4, !dbg !1866
  %inc = add nsw i32 %3, 1, !dbg !1866
  store i32 %inc, i32* %i, align 4, !dbg !1866
  br label %while.cond, !dbg !1867

while.end:                                        ; preds = %while.cond
  %4 = load i32, i32* %i, align 4, !dbg !1869
  ret i32 %4, !dbg !1870
}

; Function Attrs: nounwind uwtable
define i8* @Curl_printable_address(%struct.Curl_addrinfo* %ai, i8* %buf, i64 %bufsize) #0 !dbg !1735 {
entry:
  %retval = alloca i8*, align 8
  %ai.addr = alloca %struct.Curl_addrinfo*, align 8
  %buf.addr = alloca i8*, align 8
  %bufsize.addr = alloca i64, align 8
  %sa4 = alloca %struct.sockaddr_in*, align 8
  %ipaddr4 = alloca %struct.in_addr*, align 8
  store %struct.Curl_addrinfo* %ai, %struct.Curl_addrinfo** %ai.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %ai.addr, metadata !1871, metadata !1805), !dbg !1872
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1873, metadata !1805), !dbg !1874
  store i64 %bufsize, i64* %bufsize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bufsize.addr, metadata !1875, metadata !1805), !dbg !1876
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in** %sa4, metadata !1877, metadata !1805), !dbg !1895
  call void @llvm.dbg.declare(metadata %struct.in_addr** %ipaddr4, metadata !1896, metadata !1805), !dbg !1899
  %0 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai.addr, align 8, !dbg !1900
  %ai_family = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %0, i32 0, i32 1, !dbg !1901
  %1 = load i32, i32* %ai_family, align 4, !dbg !1901
  switch i32 %1, label %sw.default [
    i32 2, label %sw.bb
  ], !dbg !1902

sw.bb:                                            ; preds = %entry
  %2 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai.addr, align 8, !dbg !1903
  %ai_addr = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %2, i32 0, i32 6, !dbg !1905
  %3 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr, align 8, !dbg !1905
  %4 = bitcast %struct.sockaddr* %3 to i8*, !dbg !1906
  %5 = bitcast i8* %4 to %struct.sockaddr_in*, !dbg !1906
  store %struct.sockaddr_in* %5, %struct.sockaddr_in** %sa4, align 8, !dbg !1907
  %6 = load %struct.sockaddr_in*, %struct.sockaddr_in** %sa4, align 8, !dbg !1908
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %6, i32 0, i32 2, !dbg !1909
  store %struct.in_addr* %sin_addr, %struct.in_addr** %ipaddr4, align 8, !dbg !1910
  %7 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai.addr, align 8, !dbg !1911
  %ai_family1 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %7, i32 0, i32 1, !dbg !1912
  %8 = load i32, i32* %ai_family1, align 4, !dbg !1912
  %9 = load %struct.in_addr*, %struct.in_addr** %ipaddr4, align 8, !dbg !1913
  %10 = bitcast %struct.in_addr* %9 to i8*, !dbg !1914
  %11 = load i8*, i8** %buf.addr, align 8, !dbg !1915
  %12 = load i64, i64* %bufsize.addr, align 8, !dbg !1916
  %call = call i8* @Curl_inet_ntop(i32 %8, i8* %10, i8* %11, i64 %12), !dbg !1917
  store i8* %call, i8** %retval, align 8, !dbg !1918
  br label %return, !dbg !1918

sw.default:                                       ; preds = %entry
  br label %sw.epilog, !dbg !1919

sw.epilog:                                        ; preds = %sw.default
  store i8* null, i8** %retval, align 8, !dbg !1920
  br label %return, !dbg !1920

return:                                           ; preds = %sw.epilog, %sw.bb
  %13 = load i8*, i8** %retval, align 8, !dbg !1921
  ret i8* %13, !dbg !1921
}

declare i8* @Curl_inet_ntop(i32, i8*, i8*, i64) #2

; Function Attrs: nounwind uwtable
define void @Curl_hostcache_prune(%struct.Curl_easy* %data) #0 !dbg !1738 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %now = alloca i64, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !1922, metadata !1805), !dbg !1923
  call void @llvm.dbg.declare(metadata i64* %now, metadata !1924, metadata !1805), !dbg !1925
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1926
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 13, !dbg !1928
  %dns_cache_timeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 77, !dbg !1929
  %1 = load i64, i64* %dns_cache_timeout, align 8, !dbg !1929
  %cmp = icmp eq i64 %1, -1, !dbg !1930
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !1931

lor.lhs.false:                                    ; preds = %entry
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1932
  %dns = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 8, !dbg !1934
  %hostcache = getelementptr inbounds %struct.Names, %struct.Names* %dns, i32 0, i32 0, !dbg !1935
  %3 = load %struct.curl_hash*, %struct.curl_hash** %hostcache, align 8, !dbg !1935
  %tobool = icmp ne %struct.curl_hash* %3, null, !dbg !1932
  br i1 %tobool, label %if.end, label %if.then, !dbg !1936

if.then:                                          ; preds = %lor.lhs.false, %entry
  br label %if.end13, !dbg !1937

if.end:                                           ; preds = %lor.lhs.false
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1938
  %share = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 11, !dbg !1940
  %5 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !1940
  %tobool1 = icmp ne %struct.Curl_share* %5, null, !dbg !1938
  br i1 %tobool1, label %if.then2, label %if.end3, !dbg !1941

if.then2:                                         ; preds = %if.end
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1942
  %call = call i32 @Curl_share_lock(%struct.Curl_easy* %6, i32 3, i32 2), !dbg !1943
  br label %if.end3, !dbg !1943

if.end3:                                          ; preds = %if.then2, %if.end
  %call4 = call i64 @time(i64* %now) #8, !dbg !1944
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1945
  %dns5 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 8, !dbg !1946
  %hostcache6 = getelementptr inbounds %struct.Names, %struct.Names* %dns5, i32 0, i32 0, !dbg !1947
  %8 = load %struct.curl_hash*, %struct.curl_hash** %hostcache6, align 8, !dbg !1947
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1948
  %set7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 13, !dbg !1949
  %dns_cache_timeout8 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set7, i32 0, i32 77, !dbg !1950
  %10 = load i64, i64* %dns_cache_timeout8, align 8, !dbg !1950
  %11 = load i64, i64* %now, align 8, !dbg !1951
  call void @hostcache_prune(%struct.curl_hash* %8, i64 %10, i64 %11), !dbg !1952
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1953
  %share9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 11, !dbg !1955
  %13 = load %struct.Curl_share*, %struct.Curl_share** %share9, align 8, !dbg !1955
  %tobool10 = icmp ne %struct.Curl_share* %13, null, !dbg !1953
  br i1 %tobool10, label %if.then11, label %if.end13, !dbg !1956

if.then11:                                        ; preds = %if.end3
  %14 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !1957
  %call12 = call i32 @Curl_share_unlock(%struct.Curl_easy* %14, i32 3), !dbg !1958
  br label %if.end13, !dbg !1958

if.end13:                                         ; preds = %if.then, %if.then11, %if.end3
  ret void, !dbg !1959
}

declare i32 @Curl_share_lock(%struct.Curl_easy*, i32, i32) #2

; Function Attrs: nounwind
declare i64 @time(i64*) #3

; Function Attrs: nounwind uwtable
define internal void @hostcache_prune(%struct.curl_hash* %hostcache, i64 %cache_timeout, i64 %now) #0 !dbg !1766 {
entry:
  %hostcache.addr = alloca %struct.curl_hash*, align 8
  %cache_timeout.addr = alloca i64, align 8
  %now.addr = alloca i64, align 8
  %user = alloca %struct.hostcache_prune_data, align 8
  store %struct.curl_hash* %hostcache, %struct.curl_hash** %hostcache.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %hostcache.addr, metadata !1960, metadata !1805), !dbg !1961
  store i64 %cache_timeout, i64* %cache_timeout.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %cache_timeout.addr, metadata !1962, metadata !1805), !dbg !1963
  store i64 %now, i64* %now.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %now.addr, metadata !1964, metadata !1805), !dbg !1965
  call void @llvm.dbg.declare(metadata %struct.hostcache_prune_data* %user, metadata !1966, metadata !1805), !dbg !1967
  %0 = load i64, i64* %cache_timeout.addr, align 8, !dbg !1968
  %cache_timeout1 = getelementptr inbounds %struct.hostcache_prune_data, %struct.hostcache_prune_data* %user, i32 0, i32 0, !dbg !1969
  store i64 %0, i64* %cache_timeout1, align 8, !dbg !1970
  %1 = load i64, i64* %now.addr, align 8, !dbg !1971
  %now2 = getelementptr inbounds %struct.hostcache_prune_data, %struct.hostcache_prune_data* %user, i32 0, i32 1, !dbg !1972
  store i64 %1, i64* %now2, align 8, !dbg !1973
  %2 = load %struct.curl_hash*, %struct.curl_hash** %hostcache.addr, align 8, !dbg !1974
  %3 = bitcast %struct.hostcache_prune_data* %user to i8*, !dbg !1975
  call void @Curl_hash_clean_with_criterium(%struct.curl_hash* %2, i8* %3, i32 (i8*, i8*)* @hostcache_timestamp_remove), !dbg !1976
  ret void, !dbg !1977
}

declare i32 @Curl_share_unlock(%struct.Curl_easy*, i32) #2

; Function Attrs: nounwind uwtable
define %struct.Curl_dns_entry* @Curl_fetch_addr(%struct.connectdata* %conn, i8* %hostname, i32 %port) #0 !dbg !1741 {
entry:
  %conn.addr = alloca %struct.connectdata*, align 8
  %hostname.addr = alloca i8*, align 8
  %port.addr = alloca i32, align 4
  %data = alloca %struct.Curl_easy*, align 8
  %dns = alloca %struct.Curl_dns_entry*, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !1978, metadata !1805), !dbg !1979
  store i8* %hostname, i8** %hostname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %hostname.addr, metadata !1980, metadata !1805), !dbg !1981
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !1982, metadata !1805), !dbg !1983
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !1984, metadata !1805), !dbg !1985
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1986
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !1987
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !1987
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !1985
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %dns, metadata !1988, metadata !1805), !dbg !1989
  store %struct.Curl_dns_entry* null, %struct.Curl_dns_entry** %dns, align 8, !dbg !1989
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1990
  %share = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %2, i32 0, i32 11, !dbg !1992
  %3 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !1992
  %tobool = icmp ne %struct.Curl_share* %3, null, !dbg !1990
  br i1 %tobool, label %if.then, label %if.end, !dbg !1993

if.then:                                          ; preds = %entry
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !1994
  %call = call i32 @Curl_share_lock(%struct.Curl_easy* %4, i32 3, i32 2), !dbg !1995
  br label %if.end, !dbg !1995

if.end:                                           ; preds = %if.then, %entry
  %5 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !1996
  %6 = load i8*, i8** %hostname.addr, align 8, !dbg !1997
  %7 = load i32, i32* %port.addr, align 4, !dbg !1998
  %call2 = call %struct.Curl_dns_entry* @fetch_addr(%struct.connectdata* %5, i8* %6, i32 %7), !dbg !1999
  store %struct.Curl_dns_entry* %call2, %struct.Curl_dns_entry** %dns, align 8, !dbg !2000
  %8 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2001
  %tobool3 = icmp ne %struct.Curl_dns_entry* %8, null, !dbg !2001
  br i1 %tobool3, label %if.then4, label %if.end5, !dbg !2003

if.then4:                                         ; preds = %if.end
  %9 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2004
  %inuse = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %9, i32 0, i32 2, !dbg !2005
  %10 = load i64, i64* %inuse, align 8, !dbg !2006
  %inc = add nsw i64 %10, 1, !dbg !2006
  store i64 %inc, i64* %inuse, align 8, !dbg !2006
  br label %if.end5, !dbg !2004

if.end5:                                          ; preds = %if.then4, %if.end
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2007
  %share6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 11, !dbg !2009
  %12 = load %struct.Curl_share*, %struct.Curl_share** %share6, align 8, !dbg !2009
  %tobool7 = icmp ne %struct.Curl_share* %12, null, !dbg !2007
  br i1 %tobool7, label %if.then8, label %if.end10, !dbg !2010

if.then8:                                         ; preds = %if.end5
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2011
  %call9 = call i32 @Curl_share_unlock(%struct.Curl_easy* %13, i32 3), !dbg !2012
  br label %if.end10, !dbg !2012

if.end10:                                         ; preds = %if.then8, %if.end5
  %14 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2013
  ret %struct.Curl_dns_entry* %14, !dbg !2014
}

; Function Attrs: nounwind uwtable
define internal %struct.Curl_dns_entry* @fetch_addr(%struct.connectdata* %conn, i8* %hostname, i32 %port) #0 !dbg !1772 {
entry:
  %retval = alloca %struct.Curl_dns_entry*, align 8
  %conn.addr = alloca %struct.connectdata*, align 8
  %hostname.addr = alloca i8*, align 8
  %port.addr = alloca i32, align 4
  %entry_id = alloca i8*, align 8
  %dns = alloca %struct.Curl_dns_entry*, align 8
  %entry_len = alloca i64, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %user = alloca %struct.hostcache_prune_data, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2015, metadata !1805), !dbg !2016
  store i8* %hostname, i8** %hostname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %hostname.addr, metadata !2017, metadata !1805), !dbg !2018
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !2019, metadata !1805), !dbg !2020
  call void @llvm.dbg.declare(metadata i8** %entry_id, metadata !2021, metadata !1805), !dbg !2022
  store i8* null, i8** %entry_id, align 8, !dbg !2022
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %dns, metadata !2023, metadata !1805), !dbg !2024
  store %struct.Curl_dns_entry* null, %struct.Curl_dns_entry** %dns, align 8, !dbg !2024
  call void @llvm.dbg.declare(metadata i64* %entry_len, metadata !2025, metadata !1805), !dbg !2026
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2027, metadata !1805), !dbg !2028
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2029
  %data1 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2030
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data1, align 8, !dbg !2030
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2028
  %2 = load i8*, i8** %hostname.addr, align 8, !dbg !2031
  %3 = load i32, i32* %port.addr, align 4, !dbg !2032
  %call = call i8* @create_hostcache_id(i8* %2, i32 %3), !dbg !2033
  store i8* %call, i8** %entry_id, align 8, !dbg !2034
  %4 = load i8*, i8** %entry_id, align 8, !dbg !2035
  %tobool = icmp ne i8* %4, null, !dbg !2035
  br i1 %tobool, label %if.end, label %if.then, !dbg !2037

if.then:                                          ; preds = %entry
  %5 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2038
  store %struct.Curl_dns_entry* %5, %struct.Curl_dns_entry** %retval, align 8, !dbg !2039
  br label %return, !dbg !2039

if.end:                                           ; preds = %entry
  %6 = load i8*, i8** %entry_id, align 8, !dbg !2040
  %call2 = call i64 @strlen(i8* %6) #9, !dbg !2041
  store i64 %call2, i64* %entry_len, align 8, !dbg !2042
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2043
  %dns3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 8, !dbg !2044
  %hostcache = getelementptr inbounds %struct.Names, %struct.Names* %dns3, i32 0, i32 0, !dbg !2045
  %8 = load %struct.curl_hash*, %struct.curl_hash** %hostcache, align 8, !dbg !2045
  %9 = load i8*, i8** %entry_id, align 8, !dbg !2046
  %10 = load i64, i64* %entry_len, align 8, !dbg !2047
  %add = add i64 %10, 1, !dbg !2048
  %call4 = call i8* @Curl_hash_pick(%struct.curl_hash* %8, i8* %9, i64 %add), !dbg !2049
  %11 = bitcast i8* %call4 to %struct.Curl_dns_entry*, !dbg !2049
  store %struct.Curl_dns_entry* %11, %struct.Curl_dns_entry** %dns, align 8, !dbg !2050
  %12 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2051
  %tobool5 = icmp ne %struct.Curl_dns_entry* %12, null, !dbg !2051
  br i1 %tobool5, label %land.lhs.true, label %if.end18, !dbg !2053

land.lhs.true:                                    ; preds = %if.end
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2054
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 13, !dbg !2056
  %dns_cache_timeout = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 77, !dbg !2057
  %14 = load i64, i64* %dns_cache_timeout, align 8, !dbg !2057
  %cmp = icmp ne i64 %14, -1, !dbg !2058
  br i1 %cmp, label %if.then6, label %if.end18, !dbg !2059

if.then6:                                         ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata %struct.hostcache_prune_data* %user, metadata !2060, metadata !1805), !dbg !2062
  %now = getelementptr inbounds %struct.hostcache_prune_data, %struct.hostcache_prune_data* %user, i32 0, i32 1, !dbg !2063
  %call7 = call i64 @time(i64* %now) #8, !dbg !2064
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2065
  %set8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 13, !dbg !2066
  %dns_cache_timeout9 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set8, i32 0, i32 77, !dbg !2067
  %16 = load i64, i64* %dns_cache_timeout9, align 8, !dbg !2067
  %cache_timeout = getelementptr inbounds %struct.hostcache_prune_data, %struct.hostcache_prune_data* %user, i32 0, i32 0, !dbg !2068
  store i64 %16, i64* %cache_timeout, align 8, !dbg !2069
  %17 = bitcast %struct.hostcache_prune_data* %user to i8*, !dbg !2070
  %18 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2072
  %19 = bitcast %struct.Curl_dns_entry* %18 to i8*, !dbg !2072
  %call10 = call i32 @hostcache_timestamp_remove(i8* %17, i8* %19), !dbg !2073
  %tobool11 = icmp ne i32 %call10, 0, !dbg !2073
  br i1 %tobool11, label %if.then12, label %if.end17, !dbg !2074

if.then12:                                        ; preds = %if.then6
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2075
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %20, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.10, i32 0, i32 0)), !dbg !2077
  store %struct.Curl_dns_entry* null, %struct.Curl_dns_entry** %dns, align 8, !dbg !2078
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2079
  %dns13 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %21, i32 0, i32 8, !dbg !2080
  %hostcache14 = getelementptr inbounds %struct.Names, %struct.Names* %dns13, i32 0, i32 0, !dbg !2081
  %22 = load %struct.curl_hash*, %struct.curl_hash** %hostcache14, align 8, !dbg !2081
  %23 = load i8*, i8** %entry_id, align 8, !dbg !2082
  %24 = load i64, i64* %entry_len, align 8, !dbg !2083
  %add15 = add i64 %24, 1, !dbg !2084
  %call16 = call i32 @Curl_hash_delete(%struct.curl_hash* %22, i8* %23, i64 %add15), !dbg !2085
  br label %if.end17, !dbg !2086

if.end17:                                         ; preds = %if.then12, %if.then6
  br label %if.end18, !dbg !2087

if.end18:                                         ; preds = %if.end17, %land.lhs.true, %if.end
  %25 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2088
  %26 = load i8*, i8** %entry_id, align 8, !dbg !2088
  call void %25(i8* %26), !dbg !2088
  %27 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2089
  store %struct.Curl_dns_entry* %27, %struct.Curl_dns_entry** %retval, align 8, !dbg !2090
  br label %return, !dbg !2090

return:                                           ; preds = %if.end18, %if.then
  %28 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %retval, align 8, !dbg !2091
  ret %struct.Curl_dns_entry* %28, !dbg !2091
}

; Function Attrs: nounwind uwtable
define %struct.Curl_dns_entry* @Curl_cache_addr(%struct.Curl_easy* %data, %struct.Curl_addrinfo* %addr, i8* %hostname, i32 %port) #0 !dbg !1744 {
entry:
  %retval = alloca %struct.Curl_dns_entry*, align 8
  %data.addr = alloca %struct.Curl_easy*, align 8
  %addr.addr = alloca %struct.Curl_addrinfo*, align 8
  %hostname.addr = alloca i8*, align 8
  %port.addr = alloca i32, align 4
  %entry_id = alloca i8*, align 8
  %entry_len = alloca i64, align 8
  %dns = alloca %struct.Curl_dns_entry*, align 8
  %dns2 = alloca %struct.Curl_dns_entry*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2092, metadata !1805), !dbg !2093
  store %struct.Curl_addrinfo* %addr, %struct.Curl_addrinfo** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %addr.addr, metadata !2094, metadata !1805), !dbg !2095
  store i8* %hostname, i8** %hostname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %hostname.addr, metadata !2096, metadata !1805), !dbg !2097
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !2098, metadata !1805), !dbg !2099
  call void @llvm.dbg.declare(metadata i8** %entry_id, metadata !2100, metadata !1805), !dbg !2101
  call void @llvm.dbg.declare(metadata i64* %entry_len, metadata !2102, metadata !1805), !dbg !2103
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %dns, metadata !2104, metadata !1805), !dbg !2105
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %dns2, metadata !2106, metadata !1805), !dbg !2107
  %0 = load i8*, i8** %hostname.addr, align 8, !dbg !2108
  %1 = load i32, i32* %port.addr, align 4, !dbg !2109
  %call = call i8* @create_hostcache_id(i8* %0, i32 %1), !dbg !2110
  store i8* %call, i8** %entry_id, align 8, !dbg !2111
  %2 = load i8*, i8** %entry_id, align 8, !dbg !2112
  %tobool = icmp ne i8* %2, null, !dbg !2112
  br i1 %tobool, label %if.end, label %if.then, !dbg !2114

if.then:                                          ; preds = %entry
  store %struct.Curl_dns_entry* null, %struct.Curl_dns_entry** %retval, align 8, !dbg !2115
  br label %return, !dbg !2115

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %entry_id, align 8, !dbg !2116
  %call1 = call i64 @strlen(i8* %3) #9, !dbg !2117
  store i64 %call1, i64* %entry_len, align 8, !dbg !2118
  %4 = load i8* (i64, i64)*, i8* (i64, i64)** @Curl_ccalloc, align 8, !dbg !2119
  %call2 = call i8* %4(i64 1, i64 24), !dbg !2119
  %5 = bitcast i8* %call2 to %struct.Curl_dns_entry*, !dbg !2119
  store %struct.Curl_dns_entry* %5, %struct.Curl_dns_entry** %dns, align 8, !dbg !2120
  %6 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2121
  %tobool3 = icmp ne %struct.Curl_dns_entry* %6, null, !dbg !2121
  br i1 %tobool3, label %if.end5, label %if.then4, !dbg !2123

if.then4:                                         ; preds = %if.end
  %7 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2124
  %8 = load i8*, i8** %entry_id, align 8, !dbg !2124
  call void %7(i8* %8), !dbg !2124
  store %struct.Curl_dns_entry* null, %struct.Curl_dns_entry** %retval, align 8, !dbg !2126
  br label %return, !dbg !2126

if.end5:                                          ; preds = %if.end
  %9 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2127
  %inuse = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %9, i32 0, i32 2, !dbg !2128
  store i64 1, i64* %inuse, align 8, !dbg !2129
  %10 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr.addr, align 8, !dbg !2130
  %11 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2131
  %addr6 = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %11, i32 0, i32 0, !dbg !2132
  store %struct.Curl_addrinfo* %10, %struct.Curl_addrinfo** %addr6, align 8, !dbg !2133
  %12 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2134
  %timestamp = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %12, i32 0, i32 1, !dbg !2135
  %call7 = call i64 @time(i64* %timestamp) #8, !dbg !2136
  %13 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2137
  %timestamp8 = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %13, i32 0, i32 1, !dbg !2139
  %14 = load i64, i64* %timestamp8, align 8, !dbg !2139
  %cmp = icmp eq i64 %14, 0, !dbg !2140
  br i1 %cmp, label %if.then9, label %if.end11, !dbg !2141

if.then9:                                         ; preds = %if.end5
  %15 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2142
  %timestamp10 = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %15, i32 0, i32 1, !dbg !2143
  store i64 1, i64* %timestamp10, align 8, !dbg !2144
  br label %if.end11, !dbg !2142

if.end11:                                         ; preds = %if.then9, %if.end5
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2145
  %dns12 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %16, i32 0, i32 8, !dbg !2146
  %hostcache = getelementptr inbounds %struct.Names, %struct.Names* %dns12, i32 0, i32 0, !dbg !2147
  %17 = load %struct.curl_hash*, %struct.curl_hash** %hostcache, align 8, !dbg !2147
  %18 = load i8*, i8** %entry_id, align 8, !dbg !2148
  %19 = load i64, i64* %entry_len, align 8, !dbg !2149
  %add = add i64 %19, 1, !dbg !2150
  %20 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2151
  %21 = bitcast %struct.Curl_dns_entry* %20 to i8*, !dbg !2152
  %call13 = call i8* @Curl_hash_add(%struct.curl_hash* %17, i8* %18, i64 %add, i8* %21), !dbg !2153
  %22 = bitcast i8* %call13 to %struct.Curl_dns_entry*, !dbg !2153
  store %struct.Curl_dns_entry* %22, %struct.Curl_dns_entry** %dns2, align 8, !dbg !2154
  %23 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns2, align 8, !dbg !2155
  %tobool14 = icmp ne %struct.Curl_dns_entry* %23, null, !dbg !2155
  br i1 %tobool14, label %if.end16, label %if.then15, !dbg !2157

if.then15:                                        ; preds = %if.end11
  %24 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2158
  %25 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2158
  %26 = bitcast %struct.Curl_dns_entry* %25 to i8*, !dbg !2158
  call void %24(i8* %26), !dbg !2158
  %27 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2160
  %28 = load i8*, i8** %entry_id, align 8, !dbg !2160
  call void %27(i8* %28), !dbg !2160
  store %struct.Curl_dns_entry* null, %struct.Curl_dns_entry** %retval, align 8, !dbg !2161
  br label %return, !dbg !2161

if.end16:                                         ; preds = %if.end11
  %29 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns2, align 8, !dbg !2162
  store %struct.Curl_dns_entry* %29, %struct.Curl_dns_entry** %dns, align 8, !dbg !2163
  %30 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2164
  %inuse17 = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %30, i32 0, i32 2, !dbg !2165
  %31 = load i64, i64* %inuse17, align 8, !dbg !2166
  %inc = add nsw i64 %31, 1, !dbg !2166
  store i64 %inc, i64* %inuse17, align 8, !dbg !2166
  %32 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2167
  %33 = load i8*, i8** %entry_id, align 8, !dbg !2167
  call void %32(i8* %33), !dbg !2167
  %34 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2168
  store %struct.Curl_dns_entry* %34, %struct.Curl_dns_entry** %retval, align 8, !dbg !2169
  br label %return, !dbg !2169

return:                                           ; preds = %if.end16, %if.then15, %if.then4, %if.then
  %35 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %retval, align 8, !dbg !2170
  ret %struct.Curl_dns_entry* %35, !dbg !2170
}

; Function Attrs: nounwind uwtable
define internal i8* @create_hostcache_id(i8* %name, i32 %port) #0 !dbg !1773 {
entry:
  %name.addr = alloca i8*, align 8
  %port.addr = alloca i32, align 4
  %id = alloca i8*, align 8
  %ptr = alloca i8*, align 8
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !2171, metadata !1805), !dbg !2172
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !2173, metadata !1805), !dbg !2174
  call void @llvm.dbg.declare(metadata i8** %id, metadata !2175, metadata !1805), !dbg !2176
  %0 = load i8*, i8** %name.addr, align 8, !dbg !2177
  %1 = load i32, i32* %port.addr, align 4, !dbg !2178
  %call = call i8* (i8*, ...) @curl_maprintf(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.11, i32 0, i32 0), i8* %0, i32 %1), !dbg !2179
  store i8* %call, i8** %id, align 8, !dbg !2176
  call void @llvm.dbg.declare(metadata i8** %ptr, metadata !2180, metadata !1805), !dbg !2181
  %2 = load i8*, i8** %id, align 8, !dbg !2182
  store i8* %2, i8** %ptr, align 8, !dbg !2181
  %3 = load i8*, i8** %ptr, align 8, !dbg !2183
  %tobool = icmp ne i8* %3, null, !dbg !2183
  br i1 %tobool, label %if.then, label %if.end, !dbg !2185

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !2186

while.cond:                                       ; preds = %while.body, %if.then
  %4 = load i8*, i8** %ptr, align 8, !dbg !2188
  %5 = load i8, i8* %4, align 1, !dbg !2190
  %conv = sext i8 %5 to i32, !dbg !2190
  %tobool1 = icmp ne i32 %conv, 0, !dbg !2190
  br i1 %tobool1, label %land.rhs, label %land.end, !dbg !2191

land.rhs:                                         ; preds = %while.cond
  %6 = load i8*, i8** %ptr, align 8, !dbg !2192
  %7 = load i8, i8* %6, align 1, !dbg !2194
  %conv2 = sext i8 %7 to i32, !dbg !2194
  %cmp = icmp ne i32 %conv2, 58, !dbg !2195
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %8 = phi i1 [ false, %while.cond ], [ %cmp, %land.rhs ]
  br i1 %8, label %while.body, label %while.end, !dbg !2196

while.body:                                       ; preds = %land.end
  %9 = load i8*, i8** %ptr, align 8, !dbg !2198
  %10 = load i8, i8* %9, align 1, !dbg !2198
  %conv4 = zext i8 %10 to i32, !dbg !2198
  %call5 = call i32 @tolower(i32 %conv4) #8, !dbg !2198
  %conv6 = trunc i32 %call5 to i8, !dbg !2200
  %11 = load i8*, i8** %ptr, align 8, !dbg !2201
  store i8 %conv6, i8* %11, align 1, !dbg !2202
  %12 = load i8*, i8** %ptr, align 8, !dbg !2203
  %incdec.ptr = getelementptr inbounds i8, i8* %12, i32 1, !dbg !2203
  store i8* %incdec.ptr, i8** %ptr, align 8, !dbg !2203
  br label %while.cond, !dbg !2204

while.end:                                        ; preds = %land.end
  br label %if.end, !dbg !2206

if.end:                                           ; preds = %while.end, %entry
  %13 = load i8*, i8** %id, align 8, !dbg !2207
  ret i8* %13, !dbg !2208
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare i8* @Curl_hash_add(%struct.curl_hash*, i8*, i64, i8*) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_resolv(%struct.connectdata* %conn, i8* %hostname, i32 %port, %struct.Curl_dns_entry** %entry1) #0 !dbg !1747 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %hostname.addr = alloca i8*, align 8
  %port.addr = alloca i32, align 4
  %entry.addr = alloca %struct.Curl_dns_entry**, align 8
  %dns = alloca %struct.Curl_dns_entry*, align 8
  %data = alloca %struct.Curl_easy*, align 8
  %result = alloca i32, align 4
  %rc = alloca i32, align 4
  %addr = alloca %struct.Curl_addrinfo*, align 8
  %respwait = alloca i32, align 4
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2209, metadata !1805), !dbg !2210
  store i8* %hostname, i8** %hostname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %hostname.addr, metadata !2211, metadata !1805), !dbg !2212
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !2213, metadata !1805), !dbg !2214
  store %struct.Curl_dns_entry** %entry1, %struct.Curl_dns_entry*** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry*** %entry.addr, metadata !2215, metadata !1805), !dbg !2216
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %dns, metadata !2217, metadata !1805), !dbg !2218
  store %struct.Curl_dns_entry* null, %struct.Curl_dns_entry** %dns, align 8, !dbg !2218
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2219, metadata !1805), !dbg !2220
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2221
  %data2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2222
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data2, align 8, !dbg !2222
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2220
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2223, metadata !1805), !dbg !2224
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !2225, metadata !1805), !dbg !2226
  store i32 -1, i32* %rc, align 4, !dbg !2226
  %2 = load %struct.Curl_dns_entry**, %struct.Curl_dns_entry*** %entry.addr, align 8, !dbg !2227
  store %struct.Curl_dns_entry* null, %struct.Curl_dns_entry** %2, align 8, !dbg !2228
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2229
  %share = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 11, !dbg !2231
  %4 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2231
  %tobool = icmp ne %struct.Curl_share* %4, null, !dbg !2229
  br i1 %tobool, label %if.then, label %if.end, !dbg !2232

if.then:                                          ; preds = %entry
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2233
  %call = call i32 @Curl_share_lock(%struct.Curl_easy* %5, i32 3, i32 2), !dbg !2234
  br label %if.end, !dbg !2234

if.end:                                           ; preds = %if.then, %entry
  %6 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2235
  %7 = load i8*, i8** %hostname.addr, align 8, !dbg !2236
  %8 = load i32, i32* %port.addr, align 4, !dbg !2237
  %call3 = call %struct.Curl_dns_entry* @fetch_addr(%struct.connectdata* %6, i8* %7, i32 %8), !dbg !2238
  store %struct.Curl_dns_entry* %call3, %struct.Curl_dns_entry** %dns, align 8, !dbg !2239
  %9 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2240
  %tobool4 = icmp ne %struct.Curl_dns_entry* %9, null, !dbg !2240
  br i1 %tobool4, label %if.then5, label %if.end6, !dbg !2242

if.then5:                                         ; preds = %if.end
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2243
  %11 = load i8*, i8** %hostname.addr, align 8, !dbg !2245
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %10, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str, i32 0, i32 0), i8* %11), !dbg !2246
  %12 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2247
  %inuse = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %12, i32 0, i32 2, !dbg !2248
  %13 = load i64, i64* %inuse, align 8, !dbg !2249
  %inc = add nsw i64 %13, 1, !dbg !2249
  store i64 %inc, i64* %inuse, align 8, !dbg !2249
  store i32 0, i32* %rc, align 4, !dbg !2250
  br label %if.end6, !dbg !2251

if.end6:                                          ; preds = %if.then5, %if.end
  %14 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2252
  %share7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %14, i32 0, i32 11, !dbg !2254
  %15 = load %struct.Curl_share*, %struct.Curl_share** %share7, align 8, !dbg !2254
  %tobool8 = icmp ne %struct.Curl_share* %15, null, !dbg !2252
  br i1 %tobool8, label %if.then9, label %if.end11, !dbg !2255

if.then9:                                         ; preds = %if.end6
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2256
  %call10 = call i32 @Curl_share_unlock(%struct.Curl_easy* %16, i32 3), !dbg !2257
  br label %if.end11, !dbg !2257

if.end11:                                         ; preds = %if.then9, %if.end6
  %17 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2258
  %tobool12 = icmp ne %struct.Curl_dns_entry* %17, null, !dbg !2258
  br i1 %tobool12, label %if.end46, label %if.then13, !dbg !2260

if.then13:                                        ; preds = %if.end11
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %addr, metadata !2261, metadata !1805), !dbg !2263
  call void @llvm.dbg.declare(metadata i32* %respwait, metadata !2264, metadata !1805), !dbg !2265
  %18 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2266
  %call14 = call zeroext i1 @Curl_ipvalid(%struct.connectdata* %18), !dbg !2268
  br i1 %call14, label %if.end16, label %if.then15, !dbg !2269

if.then15:                                        ; preds = %if.then13
  store i32 -1, i32* %retval, align 4, !dbg !2270
  br label %return, !dbg !2270

if.end16:                                         ; preds = %if.then13
  %19 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2271
  %20 = load i8*, i8** %hostname.addr, align 8, !dbg !2272
  %21 = load i32, i32* %port.addr, align 4, !dbg !2273
  %call17 = call %struct.Curl_addrinfo* @Curl_getaddrinfo(%struct.connectdata* %19, i8* %20, i32 %21, i32* %respwait), !dbg !2274
  store %struct.Curl_addrinfo* %call17, %struct.Curl_addrinfo** %addr, align 8, !dbg !2275
  %22 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !2276
  %tobool18 = icmp ne %struct.Curl_addrinfo* %22, null, !dbg !2276
  br i1 %tobool18, label %if.else29, label %if.then19, !dbg !2278

if.then19:                                        ; preds = %if.end16
  %23 = load i32, i32* %respwait, align 4, !dbg !2279
  %tobool20 = icmp ne i32 %23, 0, !dbg !2279
  br i1 %tobool20, label %if.then21, label %if.end28, !dbg !2282

if.then21:                                        ; preds = %if.then19
  store i32 6, i32* %result, align 4, !dbg !2283
  %24 = load i32, i32* %result, align 4, !dbg !2285
  %tobool22 = icmp ne i32 %24, 0, !dbg !2285
  br i1 %tobool22, label %if.then23, label %if.end24, !dbg !2287

if.then23:                                        ; preds = %if.then21
  store i32 -1, i32* %retval, align 4, !dbg !2288
  br label %return, !dbg !2288

if.end24:                                         ; preds = %if.then21
  %25 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2289
  %tobool25 = icmp ne %struct.Curl_dns_entry* %25, null, !dbg !2289
  br i1 %tobool25, label %if.then26, label %if.else, !dbg !2291

if.then26:                                        ; preds = %if.end24
  store i32 0, i32* %rc, align 4, !dbg !2292
  br label %if.end27, !dbg !2293

if.else:                                          ; preds = %if.end24
  store i32 1, i32* %rc, align 4, !dbg !2294
  br label %if.end27

if.end27:                                         ; preds = %if.else, %if.then26
  br label %if.end28, !dbg !2295

if.end28:                                         ; preds = %if.end27, %if.then19
  br label %if.end45, !dbg !2296

if.else29:                                        ; preds = %if.end16
  %26 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2297
  %share30 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %26, i32 0, i32 11, !dbg !2300
  %27 = load %struct.Curl_share*, %struct.Curl_share** %share30, align 8, !dbg !2300
  %tobool31 = icmp ne %struct.Curl_share* %27, null, !dbg !2297
  br i1 %tobool31, label %if.then32, label %if.end34, !dbg !2301

if.then32:                                        ; preds = %if.else29
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2302
  %call33 = call i32 @Curl_share_lock(%struct.Curl_easy* %28, i32 3, i32 2), !dbg !2303
  br label %if.end34, !dbg !2303

if.end34:                                         ; preds = %if.then32, %if.else29
  %29 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2304
  %30 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !2305
  %31 = load i8*, i8** %hostname.addr, align 8, !dbg !2306
  %32 = load i32, i32* %port.addr, align 4, !dbg !2307
  %call35 = call %struct.Curl_dns_entry* @Curl_cache_addr(%struct.Curl_easy* %29, %struct.Curl_addrinfo* %30, i8* %31, i32 %32), !dbg !2308
  store %struct.Curl_dns_entry* %call35, %struct.Curl_dns_entry** %dns, align 8, !dbg !2309
  %33 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2310
  %share36 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %33, i32 0, i32 11, !dbg !2312
  %34 = load %struct.Curl_share*, %struct.Curl_share** %share36, align 8, !dbg !2312
  %tobool37 = icmp ne %struct.Curl_share* %34, null, !dbg !2310
  br i1 %tobool37, label %if.then38, label %if.end40, !dbg !2313

if.then38:                                        ; preds = %if.end34
  %35 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2314
  %call39 = call i32 @Curl_share_unlock(%struct.Curl_easy* %35, i32 3), !dbg !2315
  br label %if.end40, !dbg !2315

if.end40:                                         ; preds = %if.then38, %if.end34
  %36 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2316
  %tobool41 = icmp ne %struct.Curl_dns_entry* %36, null, !dbg !2316
  br i1 %tobool41, label %if.else43, label %if.then42, !dbg !2318

if.then42:                                        ; preds = %if.end40
  %37 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !2319
  call void @Curl_freeaddrinfo(%struct.Curl_addrinfo* %37), !dbg !2320
  br label %if.end44, !dbg !2320

if.else43:                                        ; preds = %if.end40
  store i32 0, i32* %rc, align 4, !dbg !2321
  br label %if.end44

if.end44:                                         ; preds = %if.else43, %if.then42
  br label %if.end45

if.end45:                                         ; preds = %if.end44, %if.end28
  br label %if.end46, !dbg !2322

if.end46:                                         ; preds = %if.end45, %if.end11
  %38 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns, align 8, !dbg !2323
  %39 = load %struct.Curl_dns_entry**, %struct.Curl_dns_entry*** %entry.addr, align 8, !dbg !2324
  store %struct.Curl_dns_entry* %38, %struct.Curl_dns_entry** %39, align 8, !dbg !2325
  %40 = load i32, i32* %rc, align 4, !dbg !2326
  store i32 %40, i32* %retval, align 4, !dbg !2327
  br label %return, !dbg !2327

return:                                           ; preds = %if.end46, %if.then23, %if.then15
  %41 = load i32, i32* %retval, align 4, !dbg !2328
  ret i32 %41, !dbg !2328
}

declare void @Curl_infof(%struct.Curl_easy*, i8*, ...) #2

declare zeroext i1 @Curl_ipvalid(%struct.connectdata*) #2

declare %struct.Curl_addrinfo* @Curl_getaddrinfo(%struct.connectdata*, i8*, i32, i32*) #2

declare void @Curl_freeaddrinfo(%struct.Curl_addrinfo*) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_resolv_timeout(%struct.connectdata* %conn, i8* %hostname, i32 %port, %struct.Curl_dns_entry** %entry1, i64 %timeoutms) #0 !dbg !1751 {
entry:
  %retval = alloca i32, align 4
  %conn.addr = alloca %struct.connectdata*, align 8
  %hostname.addr = alloca i8*, align 8
  %port.addr = alloca i32, align 4
  %entry.addr = alloca %struct.Curl_dns_entry**, align 8
  %timeoutms.addr = alloca i64, align 8
  %keep_sigact = alloca %struct.sigaction, align 8
  %keep_copysig = alloca i8, align 1
  %sigact = alloca %struct.sigaction, align 8
  %timeout = alloca i64, align 8
  %prev_alarm = alloca i32, align 4
  %data = alloca %struct.Curl_easy*, align 8
  %rc = alloca i32, align 4
  %elapsed_ms = alloca i64, align 8
  %agg.tmp = alloca %struct.timeval, align 8
  %alarm_set = alloca i64, align 8
  store %struct.connectdata* %conn, %struct.connectdata** %conn.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata** %conn.addr, metadata !2329, metadata !1805), !dbg !2330
  store i8* %hostname, i8** %hostname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %hostname.addr, metadata !2331, metadata !1805), !dbg !2332
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !2333, metadata !1805), !dbg !2334
  store %struct.Curl_dns_entry** %entry1, %struct.Curl_dns_entry*** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry*** %entry.addr, metadata !2335, metadata !1805), !dbg !2336
  store i64 %timeoutms, i64* %timeoutms.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %timeoutms.addr, metadata !2337, metadata !1805), !dbg !2338
  call void @llvm.dbg.declare(metadata %struct.sigaction* %keep_sigact, metadata !2339, metadata !1805), !dbg !2423
  call void @llvm.dbg.declare(metadata i8* %keep_copysig, metadata !2424, metadata !1805), !dbg !2426
  store volatile i8 0, i8* %keep_copysig, align 1, !dbg !2426
  call void @llvm.dbg.declare(metadata %struct.sigaction* %sigact, metadata !2427, metadata !1805), !dbg !2428
  call void @llvm.dbg.declare(metadata i64* %timeout, metadata !2429, metadata !1805), !dbg !2431
  call void @llvm.dbg.declare(metadata i32* %prev_alarm, metadata !2432, metadata !1805), !dbg !2433
  store volatile i32 0, i32* %prev_alarm, align 4, !dbg !2433
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2434, metadata !1805), !dbg !2435
  %0 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2436
  %data2 = getelementptr inbounds %struct.connectdata, %struct.connectdata* %0, i32 0, i32 0, !dbg !2437
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data2, align 8, !dbg !2437
  store %struct.Curl_easy* %1, %struct.Curl_easy** %data, align 8, !dbg !2435
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !2438, metadata !1805), !dbg !2439
  %2 = load %struct.Curl_dns_entry**, %struct.Curl_dns_entry*** %entry.addr, align 8, !dbg !2440
  store %struct.Curl_dns_entry* null, %struct.Curl_dns_entry** %2, align 8, !dbg !2441
  %3 = load i64, i64* %timeoutms.addr, align 8, !dbg !2442
  %cmp = icmp slt i64 %3, 0, !dbg !2444
  br i1 %cmp, label %if.then, label %if.end, !dbg !2445

if.then:                                          ; preds = %entry
  store i32 -2, i32* %retval, align 4, !dbg !2446
  br label %return, !dbg !2446

if.end:                                           ; preds = %entry
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2447
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 13, !dbg !2449
  %no_signal = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 116, !dbg !2450
  %5 = load i8, i8* %no_signal, align 4, !dbg !2450
  %tobool = trunc i8 %5 to i1, !dbg !2450
  br i1 %tobool, label %if.then3, label %if.else, !dbg !2451

if.then3:                                         ; preds = %if.end
  store volatile i64 0, i64* %timeout, align 8, !dbg !2452
  br label %if.end4, !dbg !2453

if.else:                                          ; preds = %if.end
  %6 = load i64, i64* %timeoutms.addr, align 8, !dbg !2454
  store volatile i64 %6, i64* %timeout, align 8, !dbg !2455
  br label %if.end4

if.end4:                                          ; preds = %if.else, %if.then3
  %7 = load volatile i64, i64* %timeout, align 8, !dbg !2456
  %tobool5 = icmp ne i64 %7, 0, !dbg !2456
  br i1 %tobool5, label %if.end7, label %if.then6, !dbg !2458

if.then6:                                         ; preds = %if.end4
  %8 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2459
  %9 = load i8*, i8** %hostname.addr, align 8, !dbg !2460
  %10 = load i32, i32* %port.addr, align 4, !dbg !2461
  %11 = load %struct.Curl_dns_entry**, %struct.Curl_dns_entry*** %entry.addr, align 8, !dbg !2462
  %call = call i32 @Curl_resolv(%struct.connectdata* %8, i8* %9, i32 %10, %struct.Curl_dns_entry** %11), !dbg !2463
  store i32 %call, i32* %retval, align 4, !dbg !2464
  br label %return, !dbg !2464

if.end7:                                          ; preds = %if.end4
  %12 = load volatile i64, i64* %timeout, align 8, !dbg !2465
  %cmp8 = icmp slt i64 %12, 1000, !dbg !2467
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !2468

if.then9:                                         ; preds = %if.end7
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2469
  %14 = load volatile i64, i64* %timeout, align 8, !dbg !2471
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %13, i8* getelementptr inbounds ([65 x i8], [65 x i8]* @.str.1, i32 0, i32 0), i64 %14), !dbg !2472
  store i32 -2, i32* %retval, align 4, !dbg !2473
  br label %return, !dbg !2473

if.end10:                                         ; preds = %if.end7
  %call11 = call i32 @__sigsetjmp(%struct.__jmp_buf_tag* getelementptr inbounds ([1 x %struct.__jmp_buf_tag], [1 x %struct.__jmp_buf_tag]* @curl_jmpenv, i32 0, i32 0), i32 1) #10, !dbg !2474
  %tobool12 = icmp ne i32 %call11, 0, !dbg !2474
  br i1 %tobool12, label %if.then13, label %if.else14, !dbg !2476

if.then13:                                        ; preds = %if.end10
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2477
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %15, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.2, i32 0, i32 0)), !dbg !2479
  store i32 -1, i32* %rc, align 4, !dbg !2480
  br label %clean_up, !dbg !2481

if.else14:                                        ; preds = %if.end10
  %call15 = call i32 @sigaction(i32 14, %struct.sigaction* null, %struct.sigaction* %sigact) #8, !dbg !2482
  %16 = bitcast %struct.sigaction* %keep_sigact to i8*, !dbg !2484
  %17 = bitcast %struct.sigaction* %sigact to i8*, !dbg !2484
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %16, i8* %17, i64 152, i32 8, i1 false), !dbg !2484
  store volatile i8 1, i8* %keep_copysig, align 1, !dbg !2485
  %__sigaction_handler = getelementptr inbounds %struct.sigaction, %struct.sigaction* %sigact, i32 0, i32 0, !dbg !2486
  %sa_handler = bitcast %union.anon.1* %__sigaction_handler to void (i32)**, !dbg !2486
  store void (i32)* @alarmfunc, void (i32)** %sa_handler, align 8, !dbg !2487
  %sa_flags = getelementptr inbounds %struct.sigaction, %struct.sigaction* %sigact, i32 0, i32 2, !dbg !2488
  %18 = load i32, i32* %sa_flags, align 8, !dbg !2489
  %and = and i32 %18, -268435457, !dbg !2489
  store i32 %and, i32* %sa_flags, align 8, !dbg !2489
  %call16 = call i32 @sigaction(i32 14, %struct.sigaction* %sigact, %struct.sigaction* null) #8, !dbg !2490
  %19 = load volatile i64, i64* %timeout, align 8, !dbg !2491
  %div = sdiv i64 %19, 1000, !dbg !2492
  %call17 = call i32 @curlx_sltoui(i64 %div), !dbg !2493
  %call18 = call i32 @alarm(i32 %call17) #8, !dbg !2494
  store volatile i32 %call18, i32* %prev_alarm, align 4, !dbg !2496
  br label %if.end19

if.end19:                                         ; preds = %if.else14
  %20 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2497
  %21 = load i8*, i8** %hostname.addr, align 8, !dbg !2498
  %22 = load i32, i32* %port.addr, align 4, !dbg !2499
  %23 = load %struct.Curl_dns_entry**, %struct.Curl_dns_entry*** %entry.addr, align 8, !dbg !2500
  %call20 = call i32 @Curl_resolv(%struct.connectdata* %20, i8* %21, i32 %22, %struct.Curl_dns_entry** %23), !dbg !2501
  store i32 %call20, i32* %rc, align 4, !dbg !2502
  br label %clean_up, !dbg !2503

clean_up:                                         ; preds = %if.end19, %if.then13
  %24 = load volatile i32, i32* %prev_alarm, align 4, !dbg !2504
  %tobool21 = icmp ne i32 %24, 0, !dbg !2504
  br i1 %tobool21, label %if.end24, label %if.then22, !dbg !2506

if.then22:                                        ; preds = %clean_up
  %call23 = call i32 @alarm(i32 0) #8, !dbg !2507
  br label %if.end24, !dbg !2507

if.end24:                                         ; preds = %if.then22, %clean_up
  %25 = load volatile i8, i8* %keep_copysig, align 1, !dbg !2508
  %tobool25 = trunc i8 %25 to i1, !dbg !2508
  br i1 %tobool25, label %if.then26, label %if.end28, !dbg !2510

if.then26:                                        ; preds = %if.end24
  %call27 = call i32 @sigaction(i32 14, %struct.sigaction* %keep_sigact, %struct.sigaction* null) #8, !dbg !2511
  br label %if.end28, !dbg !2513

if.end28:                                         ; preds = %if.then26, %if.end24
  %26 = load volatile i32, i32* %prev_alarm, align 4, !dbg !2514
  %tobool29 = icmp ne i32 %26, 0, !dbg !2514
  br i1 %tobool29, label %if.then30, label %if.end45, !dbg !2516

if.then30:                                        ; preds = %if.end28
  call void @llvm.dbg.declare(metadata i64* %elapsed_ms, metadata !2517, metadata !1805), !dbg !2519
  %call31 = call { i64, i64 } @curlx_tvnow(), !dbg !2520
  %27 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !2520
  %28 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %27, i32 0, i32 0, !dbg !2520
  %29 = extractvalue { i64, i64 } %call31, 0, !dbg !2520
  store i64 %29, i64* %28, align 8, !dbg !2520
  %30 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %27, i32 0, i32 1, !dbg !2520
  %31 = extractvalue { i64, i64 } %call31, 1, !dbg !2520
  store i64 %31, i64* %30, align 8, !dbg !2520
  %32 = load %struct.connectdata*, %struct.connectdata** %conn.addr, align 8, !dbg !2520
  %created = getelementptr inbounds %struct.connectdata, %struct.connectdata* %32, i32 0, i32 32, !dbg !2520
  %33 = bitcast %struct.timeval* %agg.tmp to { i64, i64 }*, !dbg !2520
  %34 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %33, i32 0, i32 0, !dbg !2520
  %35 = load i64, i64* %34, align 8, !dbg !2520
  %36 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %33, i32 0, i32 1, !dbg !2520
  %37 = load i64, i64* %36, align 8, !dbg !2520
  %38 = bitcast %struct.timeval* %created to { i64, i64 }*, !dbg !2520
  %39 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %38, i32 0, i32 0, !dbg !2520
  %40 = load i64, i64* %39, align 8, !dbg !2520
  %41 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %38, i32 0, i32 1, !dbg !2520
  %42 = load i64, i64* %41, align 8, !dbg !2520
  %call32 = call i64 @curlx_tvdiff(i64 %35, i64 %37, i64 %40, i64 %42), !dbg !2521
  store i64 %call32, i64* %elapsed_ms, align 8, !dbg !2519
  call void @llvm.dbg.declare(metadata i64* %alarm_set, metadata !2523, metadata !1805), !dbg !2524
  %43 = load volatile i32, i32* %prev_alarm, align 4, !dbg !2525
  %conv = zext i32 %43 to i64, !dbg !2525
  %44 = load i64, i64* %elapsed_ms, align 8, !dbg !2526
  %div33 = udiv i64 %44, 1000, !dbg !2527
  %sub = sub i64 %conv, %div33, !dbg !2528
  store i64 %sub, i64* %alarm_set, align 8, !dbg !2524
  %45 = load i64, i64* %alarm_set, align 8, !dbg !2529
  %tobool34 = icmp ne i64 %45, 0, !dbg !2529
  br i1 %tobool34, label %lor.lhs.false, label %if.then39, !dbg !2531

lor.lhs.false:                                    ; preds = %if.then30
  %46 = load i64, i64* %alarm_set, align 8, !dbg !2532
  %cmp35 = icmp uge i64 %46, 2147483648, !dbg !2533
  br i1 %cmp35, label %land.lhs.true, label %if.else41, !dbg !2534

land.lhs.true:                                    ; preds = %lor.lhs.false
  %47 = load volatile i32, i32* %prev_alarm, align 4, !dbg !2535
  %cmp37 = icmp ult i32 %47, -2147483648, !dbg !2537
  br i1 %cmp37, label %if.then39, label %if.else41, !dbg !2538

if.then39:                                        ; preds = %land.lhs.true, %if.then30
  %call40 = call i32 @alarm(i32 1) #8, !dbg !2539
  store i32 -2, i32* %rc, align 4, !dbg !2541
  %48 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2542
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %48, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.3, i32 0, i32 0)), !dbg !2543
  br label %if.end44, !dbg !2544

if.else41:                                        ; preds = %land.lhs.true, %lor.lhs.false
  %49 = load i64, i64* %alarm_set, align 8, !dbg !2545
  %conv42 = trunc i64 %49 to i32, !dbg !2546
  %call43 = call i32 @alarm(i32 %conv42) #8, !dbg !2547
  br label %if.end44

if.end44:                                         ; preds = %if.else41, %if.then39
  br label %if.end45, !dbg !2548

if.end45:                                         ; preds = %if.end44, %if.end28
  %50 = load i32, i32* %rc, align 4, !dbg !2549
  store i32 %50, i32* %retval, align 4, !dbg !2550
  br label %return, !dbg !2550

return:                                           ; preds = %if.end45, %if.then9, %if.then6, %if.then
  %51 = load i32, i32* %retval, align 4, !dbg !2551
  ret i32 %51, !dbg !2551
}

declare void @Curl_failf(%struct.Curl_easy*, i8*, ...) #2

; Function Attrs: nounwind returns_twice
declare i32 @__sigsetjmp(%struct.__jmp_buf_tag*, i32) #5

; Function Attrs: nounwind
declare i32 @sigaction(i32, %struct.sigaction*, %struct.sigaction*) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define internal void @alarmfunc(i32 %sig) #0 !dbg !1776 {
entry:
  %sig.addr = alloca i32, align 4
  store i32 %sig, i32* %sig.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sig.addr, metadata !2552, metadata !1805), !dbg !2553
  %0 = load i32, i32* %sig.addr, align 4, !dbg !2554
  call void @siglongjmp(%struct.__jmp_buf_tag* getelementptr inbounds ([1 x %struct.__jmp_buf_tag], [1 x %struct.__jmp_buf_tag]* @curl_jmpenv, i32 0, i32 0), i32 1) #11, !dbg !2555
  unreachable, !dbg !2555

return:                                           ; No predecessors!
  ret void, !dbg !2556
}

; Function Attrs: nounwind
declare i32 @alarm(i32) #3

declare i32 @curlx_sltoui(i64) #2

declare i64 @curlx_tvdiff(i64, i64, i64, i64) #2

declare { i64, i64 } @curlx_tvnow() #2

; Function Attrs: nounwind uwtable
define void @Curl_resolv_unlock(%struct.Curl_easy* %data, %struct.Curl_dns_entry* %dns) #0 !dbg !1754 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %dns.addr = alloca %struct.Curl_dns_entry*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2557, metadata !1805), !dbg !2558
  store %struct.Curl_dns_entry* %dns, %struct.Curl_dns_entry** %dns.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %dns.addr, metadata !2559, metadata !1805), !dbg !2560
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2561
  %tobool = icmp ne %struct.Curl_easy* %0, null, !dbg !2561
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !2563

land.lhs.true:                                    ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2564
  %share = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 11, !dbg !2566
  %2 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2566
  %tobool1 = icmp ne %struct.Curl_share* %2, null, !dbg !2564
  br i1 %tobool1, label %if.then, label %if.end, !dbg !2567

if.then:                                          ; preds = %land.lhs.true
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2568
  %call = call i32 @Curl_share_lock(%struct.Curl_easy* %3, i32 3, i32 2), !dbg !2569
  br label %if.end, !dbg !2569

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  %4 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns.addr, align 8, !dbg !2570
  %5 = bitcast %struct.Curl_dns_entry* %4 to i8*, !dbg !2570
  call void @freednsentry(i8* %5), !dbg !2571
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2572
  %tobool2 = icmp ne %struct.Curl_easy* %6, null, !dbg !2572
  br i1 %tobool2, label %land.lhs.true3, label %if.end8, !dbg !2574

land.lhs.true3:                                   ; preds = %if.end
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2575
  %share4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 11, !dbg !2577
  %8 = load %struct.Curl_share*, %struct.Curl_share** %share4, align 8, !dbg !2577
  %tobool5 = icmp ne %struct.Curl_share* %8, null, !dbg !2575
  br i1 %tobool5, label %if.then6, label %if.end8, !dbg !2578

if.then6:                                         ; preds = %land.lhs.true3
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2579
  %call7 = call i32 @Curl_share_unlock(%struct.Curl_easy* %9, i32 3), !dbg !2580
  br label %if.end8, !dbg !2580

if.end8:                                          ; preds = %if.then6, %land.lhs.true3, %if.end
  ret void, !dbg !2581
}

; Function Attrs: nounwind uwtable
define i32 @Curl_mk_dnscache(%struct.curl_hash* %hash) #0 !dbg !1757 {
entry:
  %hash.addr = alloca %struct.curl_hash*, align 8
  store %struct.curl_hash* %hash, %struct.curl_hash** %hash.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %hash.addr, metadata !2582, metadata !1805), !dbg !2583
  %0 = load %struct.curl_hash*, %struct.curl_hash** %hash.addr, align 8, !dbg !2584
  %call = call i32 @Curl_hash_init(%struct.curl_hash* %0, i32 7, i64 (i8*, i64, i64)* @Curl_hash_str, i64 (i8*, i64, i8*, i64)* @Curl_str_key_compare, void (i8*)* @freednsentry), !dbg !2585
  ret i32 %call, !dbg !2586
}

; Function Attrs: nounwind uwtable
define void @Curl_hostcache_clean(%struct.Curl_easy* %data, %struct.curl_hash* %hash) #0 !dbg !1760 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %hash.addr = alloca %struct.curl_hash*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2587, metadata !1805), !dbg !2588
  store %struct.curl_hash* %hash, %struct.curl_hash** %hash.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.curl_hash** %hash.addr, metadata !2589, metadata !1805), !dbg !2590
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2591
  %tobool = icmp ne %struct.Curl_easy* %0, null, !dbg !2591
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !2593

land.lhs.true:                                    ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2594
  %share = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 11, !dbg !2596
  %2 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2596
  %tobool1 = icmp ne %struct.Curl_share* %2, null, !dbg !2594
  br i1 %tobool1, label %if.then, label %if.end, !dbg !2597

if.then:                                          ; preds = %land.lhs.true
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2598
  %call = call i32 @Curl_share_lock(%struct.Curl_easy* %3, i32 3, i32 2), !dbg !2599
  br label %if.end, !dbg !2599

if.end:                                           ; preds = %if.then, %land.lhs.true, %entry
  %4 = load %struct.curl_hash*, %struct.curl_hash** %hash.addr, align 8, !dbg !2600
  call void @Curl_hash_clean(%struct.curl_hash* %4), !dbg !2601
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2602
  %tobool2 = icmp ne %struct.Curl_easy* %5, null, !dbg !2602
  br i1 %tobool2, label %land.lhs.true3, label %if.end8, !dbg !2604

land.lhs.true3:                                   ; preds = %if.end
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2605
  %share4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 11, !dbg !2607
  %7 = load %struct.Curl_share*, %struct.Curl_share** %share4, align 8, !dbg !2607
  %tobool5 = icmp ne %struct.Curl_share* %7, null, !dbg !2605
  br i1 %tobool5, label %if.then6, label %if.end8, !dbg !2608

if.then6:                                         ; preds = %land.lhs.true3
  %8 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2609
  %call7 = call i32 @Curl_share_unlock(%struct.Curl_easy* %8, i32 3), !dbg !2610
  br label %if.end8, !dbg !2610

if.end8:                                          ; preds = %if.then6, %land.lhs.true3, %if.end
  ret void, !dbg !2611
}

declare void @Curl_hash_clean(%struct.curl_hash*) #2

; Function Attrs: nounwind uwtable
define i32 @Curl_loadhostpairs(%struct.Curl_easy* %data) #0 !dbg !1763 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %hostp = alloca %struct.curl_slist*, align 8
  %hostname = alloca [256 x i8], align 16
  %address = alloca [256 x i8], align 16
  %port = alloca i32, align 4
  %entry_id = alloca i8*, align 8
  %entry_len = alloca i64, align 8
  %dns28 = alloca %struct.Curl_dns_entry*, align 8
  %addr = alloca %struct.Curl_addrinfo*, align 8
  %entry_id29 = alloca i8*, align 8
  %entry_len30 = alloca i64, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2612, metadata !1805), !dbg !2613
  call void @llvm.dbg.declare(metadata %struct.curl_slist** %hostp, metadata !2614, metadata !1805), !dbg !2615
  call void @llvm.dbg.declare(metadata [256 x i8]* %hostname, metadata !2616, metadata !1805), !dbg !2617
  call void @llvm.dbg.declare(metadata [256 x i8]* %address, metadata !2618, metadata !1805), !dbg !2619
  call void @llvm.dbg.declare(metadata i32* %port, metadata !2620, metadata !1805), !dbg !2621
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2622
  %change = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 14, !dbg !2624
  %resolve = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change, i32 0, i32 5, !dbg !2625
  %1 = load %struct.curl_slist*, %struct.curl_slist** %resolve, align 8, !dbg !2625
  store %struct.curl_slist* %1, %struct.curl_slist** %hostp, align 8, !dbg !2626
  br label %for.cond, !dbg !2627

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load %struct.curl_slist*, %struct.curl_slist** %hostp, align 8, !dbg !2628
  %tobool = icmp ne %struct.curl_slist* %2, null, !dbg !2631
  br i1 %tobool, label %for.body, label %for.end, !dbg !2631

for.body:                                         ; preds = %for.cond
  %3 = load %struct.curl_slist*, %struct.curl_slist** %hostp, align 8, !dbg !2632
  %data1 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %3, i32 0, i32 0, !dbg !2635
  %4 = load i8*, i8** %data1, align 8, !dbg !2635
  %tobool2 = icmp ne i8* %4, null, !dbg !2632
  br i1 %tobool2, label %if.end, label %if.then, !dbg !2636

if.then:                                          ; preds = %for.body
  br label %for.inc, !dbg !2637

if.end:                                           ; preds = %for.body
  %5 = load %struct.curl_slist*, %struct.curl_slist** %hostp, align 8, !dbg !2638
  %data3 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %5, i32 0, i32 0, !dbg !2640
  %6 = load i8*, i8** %data3, align 8, !dbg !2640
  %arrayidx = getelementptr inbounds i8, i8* %6, i64 0, !dbg !2638
  %7 = load i8, i8* %arrayidx, align 1, !dbg !2638
  %conv = sext i8 %7 to i32, !dbg !2638
  %cmp = icmp eq i32 %conv, 45, !dbg !2641
  br i1 %cmp, label %if.then5, label %if.else, !dbg !2642

if.then5:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i8** %entry_id, metadata !2643, metadata !1805), !dbg !2645
  call void @llvm.dbg.declare(metadata i64* %entry_len, metadata !2646, metadata !1805), !dbg !2647
  %8 = load %struct.curl_slist*, %struct.curl_slist** %hostp, align 8, !dbg !2648
  %data6 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %8, i32 0, i32 0, !dbg !2650
  %9 = load i8*, i8** %data6, align 8, !dbg !2650
  %add.ptr = getelementptr inbounds i8, i8* %9, i64 1, !dbg !2651
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %hostname, i32 0, i32 0, !dbg !2652
  %call = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %add.ptr, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.4, i32 0, i32 0), i8* %arraydecay, i32* %port) #8, !dbg !2653
  %cmp7 = icmp ne i32 2, %call, !dbg !2654
  br i1 %cmp7, label %if.then9, label %if.end11, !dbg !2655

if.then9:                                         ; preds = %if.then5
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2656
  %11 = load %struct.curl_slist*, %struct.curl_slist** %hostp, align 8, !dbg !2658
  %data10 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %11, i32 0, i32 0, !dbg !2659
  %12 = load i8*, i8** %data10, align 8, !dbg !2659
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %10, i8* getelementptr inbounds ([52 x i8], [52 x i8]* @.str.5, i32 0, i32 0), i8* %12), !dbg !2660
  br label %for.inc, !dbg !2661

if.end11:                                         ; preds = %if.then5
  %arraydecay12 = getelementptr inbounds [256 x i8], [256 x i8]* %hostname, i32 0, i32 0, !dbg !2662
  %13 = load i32, i32* %port, align 4, !dbg !2663
  %call13 = call i8* @create_hostcache_id(i8* %arraydecay12, i32 %13), !dbg !2664
  store i8* %call13, i8** %entry_id, align 8, !dbg !2665
  %14 = load i8*, i8** %entry_id, align 8, !dbg !2666
  %tobool14 = icmp ne i8* %14, null, !dbg !2666
  br i1 %tobool14, label %if.end16, label %if.then15, !dbg !2668

if.then15:                                        ; preds = %if.end11
  store i32 27, i32* %retval, align 4, !dbg !2669
  br label %return, !dbg !2669

if.end16:                                         ; preds = %if.end11
  %15 = load i8*, i8** %entry_id, align 8, !dbg !2671
  %call17 = call i64 @strlen(i8* %15) #9, !dbg !2672
  store i64 %call17, i64* %entry_len, align 8, !dbg !2673
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2674
  %share = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %16, i32 0, i32 11, !dbg !2676
  %17 = load %struct.Curl_share*, %struct.Curl_share** %share, align 8, !dbg !2676
  %tobool18 = icmp ne %struct.Curl_share* %17, null, !dbg !2674
  br i1 %tobool18, label %if.then19, label %if.end21, !dbg !2677

if.then19:                                        ; preds = %if.end16
  %18 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2678
  %call20 = call i32 @Curl_share_lock(%struct.Curl_easy* %18, i32 3, i32 2), !dbg !2679
  br label %if.end21, !dbg !2679

if.end21:                                         ; preds = %if.then19, %if.end16
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2680
  %dns = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %19, i32 0, i32 8, !dbg !2681
  %hostcache = getelementptr inbounds %struct.Names, %struct.Names* %dns, i32 0, i32 0, !dbg !2682
  %20 = load %struct.curl_hash*, %struct.curl_hash** %hostcache, align 8, !dbg !2682
  %21 = load i8*, i8** %entry_id, align 8, !dbg !2683
  %22 = load i64, i64* %entry_len, align 8, !dbg !2684
  %add = add i64 %22, 1, !dbg !2685
  %call22 = call i32 @Curl_hash_delete(%struct.curl_hash* %20, i8* %21, i64 %add), !dbg !2686
  %23 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2687
  %share23 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %23, i32 0, i32 11, !dbg !2689
  %24 = load %struct.Curl_share*, %struct.Curl_share** %share23, align 8, !dbg !2689
  %tobool24 = icmp ne %struct.Curl_share* %24, null, !dbg !2687
  br i1 %tobool24, label %if.then25, label %if.end27, !dbg !2690

if.then25:                                        ; preds = %if.end21
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2691
  %call26 = call i32 @Curl_share_unlock(%struct.Curl_easy* %25, i32 3), !dbg !2692
  br label %if.end27, !dbg !2692

if.end27:                                         ; preds = %if.then25, %if.end21
  %26 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2693
  %27 = load i8*, i8** %entry_id, align 8, !dbg !2693
  call void %26(i8* %27), !dbg !2693
  br label %if.end80, !dbg !2694

if.else:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %dns28, metadata !2695, metadata !1805), !dbg !2697
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %addr, metadata !2698, metadata !1805), !dbg !2699
  call void @llvm.dbg.declare(metadata i8** %entry_id29, metadata !2700, metadata !1805), !dbg !2701
  call void @llvm.dbg.declare(metadata i64* %entry_len30, metadata !2702, metadata !1805), !dbg !2703
  %28 = load %struct.curl_slist*, %struct.curl_slist** %hostp, align 8, !dbg !2704
  %data31 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %28, i32 0, i32 0, !dbg !2706
  %29 = load i8*, i8** %data31, align 8, !dbg !2706
  %arraydecay32 = getelementptr inbounds [256 x i8], [256 x i8]* %hostname, i32 0, i32 0, !dbg !2707
  %arraydecay33 = getelementptr inbounds [256 x i8], [256 x i8]* %address, i32 0, i32 0, !dbg !2708
  %call34 = call i32 (i8*, i8*, ...) @__isoc99_sscanf(i8* %29, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.6, i32 0, i32 0), i8* %arraydecay32, i32* %port, i8* %arraydecay33) #8, !dbg !2709
  %cmp35 = icmp ne i32 3, %call34, !dbg !2710
  br i1 %cmp35, label %if.then37, label %if.end39, !dbg !2711

if.then37:                                        ; preds = %if.else
  %30 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2712
  %31 = load %struct.curl_slist*, %struct.curl_slist** %hostp, align 8, !dbg !2714
  %data38 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %31, i32 0, i32 0, !dbg !2715
  %32 = load i8*, i8** %data38, align 8, !dbg !2715
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %30, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.7, i32 0, i32 0), i8* %32), !dbg !2716
  br label %for.inc, !dbg !2717

if.end39:                                         ; preds = %if.else
  %arraydecay40 = getelementptr inbounds [256 x i8], [256 x i8]* %address, i32 0, i32 0, !dbg !2718
  %33 = load i32, i32* %port, align 4, !dbg !2719
  %call41 = call %struct.Curl_addrinfo* @Curl_str2addr(i8* %arraydecay40, i32 %33), !dbg !2720
  store %struct.Curl_addrinfo* %call41, %struct.Curl_addrinfo** %addr, align 8, !dbg !2721
  %34 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !2722
  %tobool42 = icmp ne %struct.Curl_addrinfo* %34, null, !dbg !2722
  br i1 %tobool42, label %if.end45, label %if.then43, !dbg !2724

if.then43:                                        ; preds = %if.end39
  %35 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2725
  %36 = load %struct.curl_slist*, %struct.curl_slist** %hostp, align 8, !dbg !2727
  %data44 = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %36, i32 0, i32 0, !dbg !2728
  %37 = load i8*, i8** %data44, align 8, !dbg !2728
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %35, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.8, i32 0, i32 0), i8* %37), !dbg !2729
  br label %for.inc, !dbg !2730

if.end45:                                         ; preds = %if.end39
  %arraydecay46 = getelementptr inbounds [256 x i8], [256 x i8]* %hostname, i32 0, i32 0, !dbg !2731
  %38 = load i32, i32* %port, align 4, !dbg !2732
  %call47 = call i8* @create_hostcache_id(i8* %arraydecay46, i32 %38), !dbg !2733
  store i8* %call47, i8** %entry_id29, align 8, !dbg !2734
  %39 = load i8*, i8** %entry_id29, align 8, !dbg !2735
  %tobool48 = icmp ne i8* %39, null, !dbg !2735
  br i1 %tobool48, label %if.end50, label %if.then49, !dbg !2737

if.then49:                                        ; preds = %if.end45
  %40 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !2738
  call void @Curl_freeaddrinfo(%struct.Curl_addrinfo* %40), !dbg !2740
  store i32 27, i32* %retval, align 4, !dbg !2741
  br label %return, !dbg !2741

if.end50:                                         ; preds = %if.end45
  %41 = load i8*, i8** %entry_id29, align 8, !dbg !2742
  %call51 = call i64 @strlen(i8* %41) #9, !dbg !2743
  store i64 %call51, i64* %entry_len30, align 8, !dbg !2744
  %42 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2745
  %share52 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %42, i32 0, i32 11, !dbg !2747
  %43 = load %struct.Curl_share*, %struct.Curl_share** %share52, align 8, !dbg !2747
  %tobool53 = icmp ne %struct.Curl_share* %43, null, !dbg !2745
  br i1 %tobool53, label %if.then54, label %if.end56, !dbg !2748

if.then54:                                        ; preds = %if.end50
  %44 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2749
  %call55 = call i32 @Curl_share_lock(%struct.Curl_easy* %44, i32 3, i32 2), !dbg !2750
  br label %if.end56, !dbg !2750

if.end56:                                         ; preds = %if.then54, %if.end50
  %45 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2751
  %dns57 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %45, i32 0, i32 8, !dbg !2752
  %hostcache58 = getelementptr inbounds %struct.Names, %struct.Names* %dns57, i32 0, i32 0, !dbg !2753
  %46 = load %struct.curl_hash*, %struct.curl_hash** %hostcache58, align 8, !dbg !2753
  %47 = load i8*, i8** %entry_id29, align 8, !dbg !2754
  %48 = load i64, i64* %entry_len30, align 8, !dbg !2755
  %add59 = add i64 %48, 1, !dbg !2756
  %call60 = call i8* @Curl_hash_pick(%struct.curl_hash* %46, i8* %47, i64 %add59), !dbg !2757
  %49 = bitcast i8* %call60 to %struct.Curl_dns_entry*, !dbg !2757
  store %struct.Curl_dns_entry* %49, %struct.Curl_dns_entry** %dns28, align 8, !dbg !2758
  %50 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2759
  %51 = load i8*, i8** %entry_id29, align 8, !dbg !2759
  call void %50(i8* %51), !dbg !2759
  %52 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns28, align 8, !dbg !2760
  %tobool61 = icmp ne %struct.Curl_dns_entry* %52, null, !dbg !2760
  br i1 %tobool61, label %if.else68, label %if.then62, !dbg !2762

if.then62:                                        ; preds = %if.end56
  %53 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2763
  %54 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !2765
  %arraydecay63 = getelementptr inbounds [256 x i8], [256 x i8]* %hostname, i32 0, i32 0, !dbg !2766
  %55 = load i32, i32* %port, align 4, !dbg !2767
  %call64 = call %struct.Curl_dns_entry* @Curl_cache_addr(%struct.Curl_easy* %53, %struct.Curl_addrinfo* %54, i8* %arraydecay63, i32 %55), !dbg !2768
  store %struct.Curl_dns_entry* %call64, %struct.Curl_dns_entry** %dns28, align 8, !dbg !2769
  %56 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns28, align 8, !dbg !2770
  %tobool65 = icmp ne %struct.Curl_dns_entry* %56, null, !dbg !2770
  br i1 %tobool65, label %if.then66, label %if.end67, !dbg !2772

if.then66:                                        ; preds = %if.then62
  %57 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns28, align 8, !dbg !2773
  %timestamp = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %57, i32 0, i32 1, !dbg !2775
  store i64 0, i64* %timestamp, align 8, !dbg !2776
  %58 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns28, align 8, !dbg !2777
  %inuse = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %58, i32 0, i32 2, !dbg !2778
  %59 = load i64, i64* %inuse, align 8, !dbg !2779
  %dec = add nsw i64 %59, -1, !dbg !2779
  store i64 %dec, i64* %inuse, align 8, !dbg !2779
  br label %if.end67, !dbg !2780

if.end67:                                         ; preds = %if.then66, %if.then62
  br label %if.end69, !dbg !2781

if.else68:                                        ; preds = %if.end56
  %60 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !2782
  call void @Curl_freeaddrinfo(%struct.Curl_addrinfo* %60), !dbg !2783
  br label %if.end69

if.end69:                                         ; preds = %if.else68, %if.end67
  %61 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2784
  %share70 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %61, i32 0, i32 11, !dbg !2786
  %62 = load %struct.Curl_share*, %struct.Curl_share** %share70, align 8, !dbg !2786
  %tobool71 = icmp ne %struct.Curl_share* %62, null, !dbg !2784
  br i1 %tobool71, label %if.then72, label %if.end74, !dbg !2787

if.then72:                                        ; preds = %if.end69
  %63 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2788
  %call73 = call i32 @Curl_share_unlock(%struct.Curl_easy* %63, i32 3), !dbg !2789
  br label %if.end74, !dbg !2789

if.end74:                                         ; preds = %if.then72, %if.end69
  %64 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %dns28, align 8, !dbg !2790
  %tobool75 = icmp ne %struct.Curl_dns_entry* %64, null, !dbg !2790
  br i1 %tobool75, label %if.end77, label %if.then76, !dbg !2792

if.then76:                                        ; preds = %if.end74
  %65 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %addr, align 8, !dbg !2793
  call void @Curl_freeaddrinfo(%struct.Curl_addrinfo* %65), !dbg !2795
  store i32 27, i32* %retval, align 4, !dbg !2796
  br label %return, !dbg !2796

if.end77:                                         ; preds = %if.end74
  %66 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2797
  %arraydecay78 = getelementptr inbounds [256 x i8], [256 x i8]* %hostname, i32 0, i32 0, !dbg !2798
  %67 = load i32, i32* %port, align 4, !dbg !2799
  %arraydecay79 = getelementptr inbounds [256 x i8], [256 x i8]* %address, i32 0, i32 0, !dbg !2800
  call void (%struct.Curl_easy*, i8*, ...) @Curl_infof(%struct.Curl_easy* %66, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.9, i32 0, i32 0), i8* %arraydecay78, i32 %67, i8* %arraydecay79), !dbg !2801
  br label %if.end80

if.end80:                                         ; preds = %if.end77, %if.end27
  br label %for.inc, !dbg !2802

for.inc:                                          ; preds = %if.end80, %if.then43, %if.then37, %if.then9, %if.then
  %68 = load %struct.curl_slist*, %struct.curl_slist** %hostp, align 8, !dbg !2803
  %next = getelementptr inbounds %struct.curl_slist, %struct.curl_slist* %68, i32 0, i32 1, !dbg !2805
  %69 = load %struct.curl_slist*, %struct.curl_slist** %next, align 8, !dbg !2805
  store %struct.curl_slist* %69, %struct.curl_slist** %hostp, align 8, !dbg !2806
  br label %for.cond, !dbg !2807

for.end:                                          ; preds = %for.cond
  %70 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2808
  %change81 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %70, i32 0, i32 14, !dbg !2809
  %resolve82 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change81, i32 0, i32 5, !dbg !2810
  store %struct.curl_slist* null, %struct.curl_slist** %resolve82, align 8, !dbg !2811
  store i32 0, i32* %retval, align 4, !dbg !2812
  br label %return, !dbg !2812

return:                                           ; preds = %for.end, %if.then76, %if.then49, %if.then15
  %71 = load i32, i32* %retval, align 4, !dbg !2813
  ret i32 %71, !dbg !2813
}

; Function Attrs: nounwind
declare i32 @__isoc99_sscanf(i8*, i8*, ...) #3

declare i32 @Curl_hash_delete(%struct.curl_hash*, i8*, i64) #2

declare %struct.Curl_addrinfo* @Curl_str2addr(i8*, i32) #2

declare i8* @Curl_hash_pick(%struct.curl_hash*, i8*, i64) #2

declare void @Curl_hash_clean_with_criterium(%struct.curl_hash*, i8*, i32 (i8*, i8*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @hostcache_timestamp_remove(i8* %datap, i8* %hc) #0 !dbg !1769 {
entry:
  %datap.addr = alloca i8*, align 8
  %hc.addr = alloca i8*, align 8
  %data = alloca %struct.hostcache_prune_data*, align 8
  %c = alloca %struct.Curl_dns_entry*, align 8
  store i8* %datap, i8** %datap.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %datap.addr, metadata !2814, metadata !1805), !dbg !2815
  store i8* %hc, i8** %hc.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %hc.addr, metadata !2816, metadata !1805), !dbg !2817
  call void @llvm.dbg.declare(metadata %struct.hostcache_prune_data** %data, metadata !2818, metadata !1805), !dbg !2819
  %0 = load i8*, i8** %datap.addr, align 8, !dbg !2820
  %1 = bitcast i8* %0 to %struct.hostcache_prune_data*, !dbg !2821
  store %struct.hostcache_prune_data* %1, %struct.hostcache_prune_data** %data, align 8, !dbg !2819
  call void @llvm.dbg.declare(metadata %struct.Curl_dns_entry** %c, metadata !2822, metadata !1805), !dbg !2823
  %2 = load i8*, i8** %hc.addr, align 8, !dbg !2824
  %3 = bitcast i8* %2 to %struct.Curl_dns_entry*, !dbg !2825
  store %struct.Curl_dns_entry* %3, %struct.Curl_dns_entry** %c, align 8, !dbg !2823
  %4 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %c, align 8, !dbg !2826
  %timestamp = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %4, i32 0, i32 1, !dbg !2827
  %5 = load i64, i64* %timestamp, align 8, !dbg !2827
  %cmp = icmp ne i64 0, %5, !dbg !2828
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !2829

land.rhs:                                         ; preds = %entry
  %6 = load %struct.hostcache_prune_data*, %struct.hostcache_prune_data** %data, align 8, !dbg !2830
  %now = getelementptr inbounds %struct.hostcache_prune_data, %struct.hostcache_prune_data* %6, i32 0, i32 1, !dbg !2832
  %7 = load i64, i64* %now, align 8, !dbg !2832
  %8 = load %struct.Curl_dns_entry*, %struct.Curl_dns_entry** %c, align 8, !dbg !2833
  %timestamp1 = getelementptr inbounds %struct.Curl_dns_entry, %struct.Curl_dns_entry* %8, i32 0, i32 1, !dbg !2834
  %9 = load i64, i64* %timestamp1, align 8, !dbg !2834
  %sub = sub nsw i64 %7, %9, !dbg !2835
  %10 = load %struct.hostcache_prune_data*, %struct.hostcache_prune_data** %data, align 8, !dbg !2836
  %cache_timeout = getelementptr inbounds %struct.hostcache_prune_data, %struct.hostcache_prune_data* %10, i32 0, i32 0, !dbg !2837
  %11 = load i64, i64* %cache_timeout, align 8, !dbg !2837
  %cmp2 = icmp sge i64 %sub, %11, !dbg !2838
  br label %land.end

land.end:                                         ; preds = %land.rhs, %entry
  %12 = phi i1 [ false, %entry ], [ %cmp2, %land.rhs ]
  %land.ext = zext i1 %12 to i32, !dbg !2839
  ret i32 %land.ext, !dbg !2841
}

declare i8* @curl_maprintf(i8*, ...) #2

; Function Attrs: nounwind
declare i32 @tolower(i32) #3

; Function Attrs: noreturn nounwind
declare void @siglongjmp(%struct.__jmp_buf_tag*, i32) #7

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind returns_twice "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind }
attributes #9 = { nounwind readonly }
attributes #10 = { nounwind returns_twice }
attributes #11 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!1801, !1802}
!llvm.ident = !{!1803}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !1716, subprograms: !1722, globals: !1778)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hostip.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !14, !24, !120, !126, !134, !173, !192, !212, !227, !244, !252, !266, !299, !368, !466, !476, !567, !584, !591, !730, !746, !758, !855, !865, !913, !931, !937, !963, !978, !987, !995, !1024, !1225, !1277}
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
!252 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !253, file: !121, line: 1133, size: 32, align: 32, elements: !1712)
!253 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectdata", file: !121, line: 895, size: 13440, align: 64, elements: !254)
!254 = !{!255, !1293, !1305, !1306, !1307, !1308, !1309, !1335, !1336, !1340, !1341, !1342, !1343, !1350, !1351, !1352, !1360, !1361, !1362, !1363, !1364, !1365, !1366, !1367, !1368, !1369, !1370, !1371, !1372, !1373, !1374, !1375, !1376, !1377, !1379, !1380, !1382, !1389, !1395, !1404, !1405, !1406, !1407, !1408, !1444, !1445, !1446, !1447, !1501, !1502, !1503, !1504, !1505, !1518, !1519, !1520, !1521, !1522, !1523, !1524, !1525, !1526, !1527, !1531, !1532, !1533, !1534, !1697, !1698, !1699, !1700, !1701, !1702, !1704, !1711}
!255 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !253, file: !121, line: 899, baseType: !256, size: 64, align: 64)
!256 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !257, size: 64, align: 64)
!257 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_easy", file: !121, line: 1801, size: 160192, align: 64, elements: !258)
!258 = !{!259, !260, !261, !263, !288, !290, !313, !319, !320, !374, !450, !451, !551, !621, !1081, !1090, !1091, !1127, !1219, !1242, !1272, !1292}
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
!453 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_share", file: !454, line: 39, size: 896, align: 64, elements: !455)
!454 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/share.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!455 = !{!456, !458, !460, !482, !487, !488, !489, !520, !549, !550}
!456 = !DIDerivedType(tag: DW_TAG_member, name: "specifier", scope: !453, file: !454, line: 40, baseType: !457, size: 32, align: 32)
!457 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!458 = !DIDerivedType(tag: DW_TAG_member, name: "dirty", scope: !453, file: !454, line: 41, baseType: !459, size: 32, align: 32, offset: 32)
!459 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !457)
!460 = !DIDerivedType(tag: DW_TAG_member, name: "lockfunc", scope: !453, file: !454, line: 43, baseType: !461, size: 64, align: 64, offset: 64)
!461 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_lock_function", file: !15, line: 2365, baseType: !462)
!462 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !463, size: 64, align: 64)
!463 = !DISubroutineType(types: !464)
!464 = !{null, !305, !465, !475, !311}
!465 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_lock_data", file: !15, line: 2355, baseType: !466)
!466 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 2343, size: 32, align: 32, elements: !467)
!467 = !{!468, !469, !470, !471, !472, !473, !474}
!468 = !DIEnumerator(name: "CURL_LOCK_DATA_NONE", value: 0)
!469 = !DIEnumerator(name: "CURL_LOCK_DATA_SHARE", value: 1)
!470 = !DIEnumerator(name: "CURL_LOCK_DATA_COOKIE", value: 2)
!471 = !DIEnumerator(name: "CURL_LOCK_DATA_DNS", value: 3)
!472 = !DIEnumerator(name: "CURL_LOCK_DATA_SSL_SESSION", value: 4)
!473 = !DIEnumerator(name: "CURL_LOCK_DATA_CONNECT", value: 5)
!474 = !DIEnumerator(name: "CURL_LOCK_DATA_LAST", value: 6)
!475 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_lock_access", file: !15, line: 2363, baseType: !476)
!476 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 2358, size: 32, align: 32, elements: !477)
!477 = !{!478, !479, !480, !481}
!478 = !DIEnumerator(name: "CURL_LOCK_ACCESS_NONE", value: 0)
!479 = !DIEnumerator(name: "CURL_LOCK_ACCESS_SHARED", value: 1)
!480 = !DIEnumerator(name: "CURL_LOCK_ACCESS_SINGLE", value: 2)
!481 = !DIEnumerator(name: "CURL_LOCK_ACCESS_LAST", value: 3)
!482 = !DIDerivedType(tag: DW_TAG_member, name: "unlockfunc", scope: !453, file: !454, line: 44, baseType: !483, size: 64, align: 64, offset: 128)
!483 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_unlock_function", file: !15, line: 2369, baseType: !484)
!484 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !485, size: 64, align: 64)
!485 = !DISubroutineType(types: !486)
!486 = !{null, !305, !465, !311}
!487 = !DIDerivedType(tag: DW_TAG_member, name: "clientdata", scope: !453, file: !454, line: 45, baseType: !311, size: 64, align: 64, offset: 192)
!488 = !DIDerivedType(tag: DW_TAG_member, name: "hostcache", scope: !453, file: !454, line: 47, baseType: !325, size: 384, align: 64, offset: 256)
!489 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !453, file: !454, line: 49, baseType: !490, size: 64, align: 64, offset: 640)
!490 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !491, size: 64, align: 64)
!491 = !DICompositeType(tag: DW_TAG_structure_type, name: "CookieInfo", file: !492, line: 48, size: 320, align: 64, elements: !493)
!492 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/cookie.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!493 = !{!494, !516, !517, !518, !519}
!494 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !491, file: !492, line: 50, baseType: !495, size: 64, align: 64)
!495 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !496, size: 64, align: 64)
!496 = !DICompositeType(tag: DW_TAG_structure_type, name: "Cookie", file: !492, line: 28, size: 768, align: 64, elements: !497)
!497 = !{!498, !499, !502, !503, !504, !505, !506, !509, !510, !511, !512, !513, !514, !515}
!498 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !496, file: !492, line: 29, baseType: !495, size: 64, align: 64)
!499 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !496, file: !492, line: 30, baseType: !500, size: 64, align: 64, offset: 64)
!500 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !501, size: 64, align: 64)
!501 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!502 = !DIDerivedType(tag: DW_TAG_member, name: "value", scope: !496, file: !492, line: 31, baseType: !500, size: 64, align: 64, offset: 128)
!503 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !496, file: !492, line: 32, baseType: !500, size: 64, align: 64, offset: 192)
!504 = !DIDerivedType(tag: DW_TAG_member, name: "spath", scope: !496, file: !492, line: 33, baseType: !500, size: 64, align: 64, offset: 256)
!505 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !496, file: !492, line: 34, baseType: !500, size: 64, align: 64, offset: 320)
!506 = !DIDerivedType(tag: DW_TAG_member, name: "expires", scope: !496, file: !492, line: 35, baseType: !507, size: 64, align: 64, offset: 384)
!507 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_off_t", file: !508, line: 216, baseType: !379)
!508 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curlbuild.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!509 = !DIDerivedType(tag: DW_TAG_member, name: "expirestr", scope: !496, file: !492, line: 36, baseType: !500, size: 64, align: 64, offset: 448)
!510 = !DIDerivedType(tag: DW_TAG_member, name: "tailmatch", scope: !496, file: !492, line: 37, baseType: !423, size: 8, align: 8, offset: 512)
!511 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !496, file: !492, line: 40, baseType: !500, size: 64, align: 64, offset: 576)
!512 = !DIDerivedType(tag: DW_TAG_member, name: "maxage", scope: !496, file: !492, line: 41, baseType: !500, size: 64, align: 64, offset: 640)
!513 = !DIDerivedType(tag: DW_TAG_member, name: "secure", scope: !496, file: !492, line: 43, baseType: !423, size: 8, align: 8, offset: 704)
!514 = !DIDerivedType(tag: DW_TAG_member, name: "livecookie", scope: !496, file: !492, line: 44, baseType: !423, size: 8, align: 8, offset: 712)
!515 = !DIDerivedType(tag: DW_TAG_member, name: "httponly", scope: !496, file: !492, line: 45, baseType: !423, size: 8, align: 8, offset: 720)
!516 = !DIDerivedType(tag: DW_TAG_member, name: "filename", scope: !491, file: !492, line: 52, baseType: !500, size: 64, align: 64, offset: 64)
!517 = !DIDerivedType(tag: DW_TAG_member, name: "running", scope: !491, file: !492, line: 53, baseType: !423, size: 8, align: 8, offset: 128)
!518 = !DIDerivedType(tag: DW_TAG_member, name: "numcookies", scope: !491, file: !492, line: 54, baseType: !379, size: 64, align: 64, offset: 192)
!519 = !DIDerivedType(tag: DW_TAG_member, name: "newsession", scope: !491, file: !492, line: 55, baseType: !423, size: 8, align: 8, offset: 256)
!520 = !DIDerivedType(tag: DW_TAG_member, name: "sslsession", scope: !453, file: !454, line: 52, baseType: !521, size: 64, align: 64, offset: 704)
!521 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !522, size: 64, align: 64)
!522 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_ssl_session", file: !121, line: 397, size: 1088, align: 64, elements: !523)
!523 = !{!524, !525, !526, !529, !530, !531, !532, !533, !534}
!524 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !522, file: !121, line: 398, baseType: !500, size: 64, align: 64)
!525 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !522, file: !121, line: 399, baseType: !500, size: 64, align: 64, offset: 64)
!526 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !522, file: !121, line: 400, baseType: !527, size: 64, align: 64, offset: 128)
!527 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !528, size: 64, align: 64)
!528 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !501)
!529 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !522, file: !121, line: 401, baseType: !311, size: 64, align: 64, offset: 192)
!530 = !DIDerivedType(tag: DW_TAG_member, name: "idsize", scope: !522, file: !121, line: 402, baseType: !347, size: 64, align: 64, offset: 256)
!531 = !DIDerivedType(tag: DW_TAG_member, name: "age", scope: !522, file: !121, line: 403, baseType: !379, size: 64, align: 64, offset: 320)
!532 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !522, file: !121, line: 404, baseType: !316, size: 32, align: 32, offset: 384)
!533 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !522, file: !121, line: 405, baseType: !316, size: 32, align: 32, offset: 416)
!534 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !522, file: !121, line: 406, baseType: !535, size: 640, align: 64, offset: 448)
!535 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_primary_config", file: !121, line: 351, size: 640, align: 64, elements: !536)
!536 = !{!537, !538, !539, !540, !541, !542, !543, !544, !545, !546, !547, !548}
!537 = !DIDerivedType(tag: DW_TAG_member, name: "version", scope: !535, file: !121, line: 352, baseType: !379, size: 64, align: 64)
!538 = !DIDerivedType(tag: DW_TAG_member, name: "version_max", scope: !535, file: !121, line: 353, baseType: !379, size: 64, align: 64, offset: 64)
!539 = !DIDerivedType(tag: DW_TAG_member, name: "verifypeer", scope: !535, file: !121, line: 354, baseType: !423, size: 8, align: 8, offset: 128)
!540 = !DIDerivedType(tag: DW_TAG_member, name: "verifyhost", scope: !535, file: !121, line: 355, baseType: !423, size: 8, align: 8, offset: 136)
!541 = !DIDerivedType(tag: DW_TAG_member, name: "verifystatus", scope: !535, file: !121, line: 356, baseType: !423, size: 8, align: 8, offset: 144)
!542 = !DIDerivedType(tag: DW_TAG_member, name: "CApath", scope: !535, file: !121, line: 357, baseType: !500, size: 64, align: 64, offset: 192)
!543 = !DIDerivedType(tag: DW_TAG_member, name: "CAfile", scope: !535, file: !121, line: 358, baseType: !500, size: 64, align: 64, offset: 256)
!544 = !DIDerivedType(tag: DW_TAG_member, name: "clientcert", scope: !535, file: !121, line: 359, baseType: !500, size: 64, align: 64, offset: 320)
!545 = !DIDerivedType(tag: DW_TAG_member, name: "random_file", scope: !535, file: !121, line: 360, baseType: !500, size: 64, align: 64, offset: 384)
!546 = !DIDerivedType(tag: DW_TAG_member, name: "egdsocket", scope: !535, file: !121, line: 361, baseType: !500, size: 64, align: 64, offset: 448)
!547 = !DIDerivedType(tag: DW_TAG_member, name: "cipher_list", scope: !535, file: !121, line: 362, baseType: !500, size: 64, align: 64, offset: 512)
!548 = !DIDerivedType(tag: DW_TAG_member, name: "sessionid", scope: !535, file: !121, line: 363, baseType: !423, size: 8, align: 8, offset: 576)
!549 = !DIDerivedType(tag: DW_TAG_member, name: "max_ssl_sessions", scope: !453, file: !454, line: 53, baseType: !347, size: 64, align: 64, offset: 768)
!550 = !DIDerivedType(tag: DW_TAG_member, name: "sessionage", scope: !453, file: !454, line: 54, baseType: !379, size: 64, align: 64, offset: 832)
!551 = !DIDerivedType(tag: DW_TAG_member, name: "req", scope: !257, file: !121, line: 1828, baseType: !552, size: 2496, align: 64, offset: 960)
!552 = !DICompositeType(tag: DW_TAG_structure_type, name: "SingleRequest", file: !121, line: 658, size: 2496, align: 64, elements: !553)
!553 = !{!554, !555, !557, !558, !559, !560, !561, !562, !563, !564, !565, !566, !572, !573, !574, !575, !576, !577, !578, !579, !580, !581, !582, !583, !590, !597, !598, !601, !602, !603, !604, !605, !606, !607, !608, !609, !610, !611, !615, !616, !617, !618, !619, !620}
!554 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !552, file: !121, line: 659, baseType: !507, size: 64, align: 64)
!555 = !DIDerivedType(tag: DW_TAG_member, name: "bytecountp", scope: !552, file: !121, line: 660, baseType: !556, size: 64, align: 64, offset: 64)
!556 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !507, size: 64, align: 64)
!557 = !DIDerivedType(tag: DW_TAG_member, name: "maxdownload", scope: !552, file: !121, line: 662, baseType: !507, size: 64, align: 64, offset: 128)
!558 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecountp", scope: !552, file: !121, line: 664, baseType: !556, size: 64, align: 64, offset: 192)
!559 = !DIDerivedType(tag: DW_TAG_member, name: "bytecount", scope: !552, file: !121, line: 666, baseType: !507, size: 64, align: 64, offset: 256)
!560 = !DIDerivedType(tag: DW_TAG_member, name: "writebytecount", scope: !552, file: !121, line: 667, baseType: !507, size: 64, align: 64, offset: 320)
!561 = !DIDerivedType(tag: DW_TAG_member, name: "headerbytecount", scope: !552, file: !121, line: 669, baseType: !379, size: 64, align: 64, offset: 384)
!562 = !DIDerivedType(tag: DW_TAG_member, name: "deductheadercount", scope: !552, file: !121, line: 670, baseType: !379, size: 64, align: 64, offset: 448)
!563 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !552, file: !121, line: 676, baseType: !411, size: 128, align: 64, offset: 512)
!564 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !552, file: !121, line: 677, baseType: !411, size: 128, align: 64, offset: 640)
!565 = !DIDerivedType(tag: DW_TAG_member, name: "header", scope: !552, file: !121, line: 678, baseType: !423, size: 8, align: 8, offset: 768)
!566 = !DIDerivedType(tag: DW_TAG_member, name: "badheader", scope: !552, file: !121, line: 684, baseType: !567, size: 32, align: 32, offset: 800)
!567 = !DICompositeType(tag: DW_TAG_enumeration_type, scope: !552, file: !121, line: 679, size: 32, align: 32, elements: !568)
!568 = !{!569, !570, !571}
!569 = !DIEnumerator(name: "HEADER_NORMAL", value: 0)
!570 = !DIEnumerator(name: "HEADER_PARTHEADER", value: 1)
!571 = !DIEnumerator(name: "HEADER_ALLBAD", value: 2)
!572 = !DIDerivedType(tag: DW_TAG_member, name: "headerline", scope: !552, file: !121, line: 686, baseType: !316, size: 32, align: 32, offset: 832)
!573 = !DIDerivedType(tag: DW_TAG_member, name: "hbufp", scope: !552, file: !121, line: 688, baseType: !500, size: 64, align: 64, offset: 896)
!574 = !DIDerivedType(tag: DW_TAG_member, name: "hbuflen", scope: !552, file: !121, line: 689, baseType: !347, size: 64, align: 64, offset: 960)
!575 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !552, file: !121, line: 690, baseType: !500, size: 64, align: 64, offset: 1024)
!576 = !DIDerivedType(tag: DW_TAG_member, name: "str_start", scope: !552, file: !121, line: 691, baseType: !500, size: 64, align: 64, offset: 1088)
!577 = !DIDerivedType(tag: DW_TAG_member, name: "end_ptr", scope: !552, file: !121, line: 692, baseType: !500, size: 64, align: 64, offset: 1152)
!578 = !DIDerivedType(tag: DW_TAG_member, name: "p", scope: !552, file: !121, line: 693, baseType: !500, size: 64, align: 64, offset: 1216)
!579 = !DIDerivedType(tag: DW_TAG_member, name: "content_range", scope: !552, file: !121, line: 694, baseType: !423, size: 8, align: 8, offset: 1280)
!580 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !552, file: !121, line: 695, baseType: !507, size: 64, align: 64, offset: 1344)
!581 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !552, file: !121, line: 697, baseType: !316, size: 32, align: 32, offset: 1408)
!582 = !DIDerivedType(tag: DW_TAG_member, name: "start100", scope: !552, file: !121, line: 699, baseType: !411, size: 128, align: 64, offset: 1472)
!583 = !DIDerivedType(tag: DW_TAG_member, name: "exp100", scope: !552, file: !121, line: 700, baseType: !584, size: 32, align: 32, offset: 1600)
!584 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "expect100", file: !121, line: 636, size: 32, align: 32, elements: !585)
!585 = !{!586, !587, !588, !589}
!586 = !DIEnumerator(name: "EXP100_SEND_DATA", value: 0)
!587 = !DIEnumerator(name: "EXP100_AWAITING_CONTINUE", value: 1)
!588 = !DIEnumerator(name: "EXP100_SENDING_REQUEST", value: 2)
!589 = !DIEnumerator(name: "EXP100_FAILED", value: 3)
!590 = !DIDerivedType(tag: DW_TAG_member, name: "upgr101", scope: !552, file: !121, line: 701, baseType: !591, size: 32, align: 32, offset: 1632)
!591 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "upgrade101", file: !121, line: 644, size: 32, align: 32, elements: !592)
!592 = !{!593, !594, !595, !596}
!593 = !DIEnumerator(name: "UPGR101_INIT", value: 0)
!594 = !DIEnumerator(name: "UPGR101_REQUESTED", value: 1)
!595 = !DIEnumerator(name: "UPGR101_RECEIVED", value: 2)
!596 = !DIEnumerator(name: "UPGR101_WORKING", value: 3)
!597 = !DIDerivedType(tag: DW_TAG_member, name: "auto_decoding", scope: !552, file: !121, line: 703, baseType: !316, size: 32, align: 32, offset: 1664)
!598 = !DIDerivedType(tag: DW_TAG_member, name: "timeofdoc", scope: !552, file: !121, line: 715, baseType: !599, size: 64, align: 64, offset: 1728)
!599 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !600, line: 75, baseType: !415)
!600 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!601 = !DIDerivedType(tag: DW_TAG_member, name: "bodywrites", scope: !552, file: !121, line: 716, baseType: !379, size: 64, align: 64, offset: 1792)
!602 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !552, file: !121, line: 718, baseType: !500, size: 64, align: 64, offset: 1856)
!603 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuf", scope: !552, file: !121, line: 719, baseType: !500, size: 64, align: 64, offset: 1920)
!604 = !DIDerivedType(tag: DW_TAG_member, name: "maxfd", scope: !552, file: !121, line: 720, baseType: !315, size: 32, align: 32, offset: 1984)
!605 = !DIDerivedType(tag: DW_TAG_member, name: "keepon", scope: !552, file: !121, line: 722, baseType: !316, size: 32, align: 32, offset: 2016)
!606 = !DIDerivedType(tag: DW_TAG_member, name: "upload_done", scope: !552, file: !121, line: 724, baseType: !423, size: 8, align: 8, offset: 2048)
!607 = !DIDerivedType(tag: DW_TAG_member, name: "ignorebody", scope: !552, file: !121, line: 727, baseType: !423, size: 8, align: 8, offset: 2056)
!608 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !552, file: !121, line: 728, baseType: !423, size: 8, align: 8, offset: 2064)
!609 = !DIDerivedType(tag: DW_TAG_member, name: "location", scope: !552, file: !121, line: 731, baseType: !500, size: 64, align: 64, offset: 2112)
!610 = !DIDerivedType(tag: DW_TAG_member, name: "newurl", scope: !552, file: !121, line: 733, baseType: !500, size: 64, align: 64, offset: 2176)
!611 = !DIDerivedType(tag: DW_TAG_member, name: "upload_present", scope: !552, file: !121, line: 738, baseType: !612, size: 64, align: 64, offset: 2240)
!612 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !613, line: 109, baseType: !614)
!613 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!614 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !416, line: 172, baseType: !379)
!615 = !DIDerivedType(tag: DW_TAG_member, name: "upload_fromhere", scope: !552, file: !121, line: 744, baseType: !500, size: 64, align: 64, offset: 2304)
!616 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !552, file: !121, line: 746, baseType: !423, size: 8, align: 8, offset: 2368)
!617 = !DIDerivedType(tag: DW_TAG_member, name: "upload_chunky", scope: !552, file: !121, line: 747, baseType: !423, size: 8, align: 8, offset: 2376)
!618 = !DIDerivedType(tag: DW_TAG_member, name: "getheader", scope: !552, file: !121, line: 749, baseType: !423, size: 8, align: 8, offset: 2384)
!619 = !DIDerivedType(tag: DW_TAG_member, name: "forbidchunk", scope: !552, file: !121, line: 751, baseType: !423, size: 8, align: 8, offset: 2392)
!620 = !DIDerivedType(tag: DW_TAG_member, name: "protop", scope: !552, file: !121, line: 755, baseType: !311, size: 64, align: 64, offset: 2432)
!621 = !DIDerivedType(tag: DW_TAG_member, name: "set", scope: !257, file: !121, line: 1829, baseType: !622, size: 13760, align: 64, offset: 3456)
!622 = !DICompositeType(tag: DW_TAG_structure_type, name: "UserDefined", file: !121, line: 1558, size: 13760, align: 64, elements: !623)
!623 = !{!624, !679, !680, !681, !682, !683, !684, !685, !686, !687, !688, !689, !690, !691, !692, !693, !694, !699, !700, !701, !702, !707, !708, !709, !711, !712, !713, !719, !724, !740, !752, !763, !764, !787, !788, !793, !794, !795, !800, !801, !802, !803, !804, !805, !806, !807, !808, !809, !810, !811, !812, !813, !814, !815, !816, !822, !823, !841, !842, !843, !844, !845, !846, !847, !848, !849, !850, !851, !852, !853, !862, !863, !875, !876, !898, !899, !903, !905, !906, !907, !908, !909, !910, !911, !918, !919, !943, !944, !945, !946, !947, !948, !949, !950, !951, !952, !953, !954, !955, !956, !957, !958, !959, !960, !961, !962, !969, !970, !971, !972, !973, !974, !975, !976, !985, !993, !1001, !1002, !1003, !1004, !1005, !1006, !1007, !1008, !1009, !1010, !1011, !1012, !1013, !1017, !1018, !1019, !1020, !1021, !1022, !1039, !1040, !1041, !1048, !1053, !1058, !1059, !1060, !1061, !1062, !1063, !1064, !1065, !1066, !1067, !1068, !1069, !1070, !1071, !1072, !1073, !1074, !1080}
!624 = !DIDerivedType(tag: DW_TAG_member, name: "err", scope: !622, file: !121, line: 1559, baseType: !625, size: 64, align: 64)
!625 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !626, size: 64, align: 64)
!626 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !627, line: 48, baseType: !628)
!627 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!628 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !629, line: 245, size: 1728, align: 64, elements: !630)
!629 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!630 = !{!631, !632, !633, !634, !635, !636, !637, !638, !639, !640, !641, !642, !643, !651, !652, !653, !654, !656, !658, !660, !664, !667, !669, !670, !671, !672, !673, !674, !675}
!631 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !628, file: !629, line: 246, baseType: !316, size: 32, align: 32)
!632 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !628, file: !629, line: 251, baseType: !500, size: 64, align: 64, offset: 64)
!633 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !628, file: !629, line: 252, baseType: !500, size: 64, align: 64, offset: 128)
!634 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !628, file: !629, line: 253, baseType: !500, size: 64, align: 64, offset: 192)
!635 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !628, file: !629, line: 254, baseType: !500, size: 64, align: 64, offset: 256)
!636 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !628, file: !629, line: 255, baseType: !500, size: 64, align: 64, offset: 320)
!637 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !628, file: !629, line: 256, baseType: !500, size: 64, align: 64, offset: 384)
!638 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !628, file: !629, line: 257, baseType: !500, size: 64, align: 64, offset: 448)
!639 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !628, file: !629, line: 258, baseType: !500, size: 64, align: 64, offset: 512)
!640 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !628, file: !629, line: 260, baseType: !500, size: 64, align: 64, offset: 576)
!641 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !628, file: !629, line: 261, baseType: !500, size: 64, align: 64, offset: 640)
!642 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !628, file: !629, line: 262, baseType: !500, size: 64, align: 64, offset: 704)
!643 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !628, file: !629, line: 264, baseType: !644, size: 64, align: 64, offset: 768)
!644 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !645, size: 64, align: 64)
!645 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !629, line: 160, size: 192, align: 64, elements: !646)
!646 = !{!647, !648, !650}
!647 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !645, file: !629, line: 161, baseType: !644, size: 64, align: 64)
!648 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !645, file: !629, line: 162, baseType: !649, size: 64, align: 64, offset: 64)
!649 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !628, size: 64, align: 64)
!650 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !645, file: !629, line: 166, baseType: !316, size: 32, align: 32, offset: 128)
!651 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !628, file: !629, line: 266, baseType: !649, size: 64, align: 64, offset: 832)
!652 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !628, file: !629, line: 268, baseType: !316, size: 32, align: 32, offset: 896)
!653 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !628, file: !629, line: 272, baseType: !316, size: 32, align: 32, offset: 928)
!654 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !628, file: !629, line: 274, baseType: !655, size: 64, align: 64, offset: 960)
!655 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !416, line: 131, baseType: !379)
!656 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !628, file: !629, line: 278, baseType: !657, size: 16, align: 16, offset: 1024)
!657 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!658 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !628, file: !629, line: 279, baseType: !659, size: 8, align: 8, offset: 1040)
!659 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!660 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !628, file: !629, line: 280, baseType: !661, size: 8, align: 8, offset: 1048)
!661 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 8, align: 8, elements: !662)
!662 = !{!663}
!663 = !DISubrange(count: 1)
!664 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !628, file: !629, line: 284, baseType: !665, size: 64, align: 64, offset: 1088)
!665 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !666, size: 64, align: 64)
!666 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !629, line: 154, baseType: null)
!667 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !628, file: !629, line: 293, baseType: !668, size: 64, align: 64, offset: 1152)
!668 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !416, line: 132, baseType: !379)
!669 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !628, file: !629, line: 302, baseType: !311, size: 64, align: 64, offset: 1216)
!670 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !628, file: !629, line: 303, baseType: !311, size: 64, align: 64, offset: 1280)
!671 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !628, file: !629, line: 304, baseType: !311, size: 64, align: 64, offset: 1344)
!672 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !628, file: !629, line: 305, baseType: !311, size: 64, align: 64, offset: 1408)
!673 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !628, file: !629, line: 306, baseType: !347, size: 64, align: 64, offset: 1472)
!674 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !628, file: !629, line: 308, baseType: !316, size: 32, align: 32, offset: 1536)
!675 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !628, file: !629, line: 310, baseType: !676, size: 160, align: 8, offset: 1568)
!676 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 160, align: 8, elements: !677)
!677 = !{!678}
!678 = !DISubrange(count: 20)
!679 = !DIDerivedType(tag: DW_TAG_member, name: "debugdata", scope: !622, file: !121, line: 1560, baseType: !311, size: 64, align: 64, offset: 64)
!680 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuffer", scope: !622, file: !121, line: 1561, baseType: !500, size: 64, align: 64, offset: 128)
!681 = !DIDerivedType(tag: DW_TAG_member, name: "proxyport", scope: !622, file: !121, line: 1562, baseType: !379, size: 64, align: 64, offset: 192)
!682 = !DIDerivedType(tag: DW_TAG_member, name: "out", scope: !622, file: !121, line: 1565, baseType: !311, size: 64, align: 64, offset: 256)
!683 = !DIDerivedType(tag: DW_TAG_member, name: "in_set", scope: !622, file: !121, line: 1566, baseType: !311, size: 64, align: 64, offset: 320)
!684 = !DIDerivedType(tag: DW_TAG_member, name: "writeheader", scope: !622, file: !121, line: 1567, baseType: !311, size: 64, align: 64, offset: 384)
!685 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_out", scope: !622, file: !121, line: 1568, baseType: !311, size: 64, align: 64, offset: 448)
!686 = !DIDerivedType(tag: DW_TAG_member, name: "use_port", scope: !622, file: !121, line: 1569, baseType: !379, size: 64, align: 64, offset: 512)
!687 = !DIDerivedType(tag: DW_TAG_member, name: "httpauth", scope: !622, file: !121, line: 1570, baseType: !349, size: 64, align: 64, offset: 576)
!688 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauth", scope: !622, file: !121, line: 1571, baseType: !349, size: 64, align: 64, offset: 640)
!689 = !DIDerivedType(tag: DW_TAG_member, name: "followlocation", scope: !622, file: !121, line: 1572, baseType: !379, size: 64, align: 64, offset: 704)
!690 = !DIDerivedType(tag: DW_TAG_member, name: "maxredirs", scope: !622, file: !121, line: 1573, baseType: !379, size: 64, align: 64, offset: 768)
!691 = !DIDerivedType(tag: DW_TAG_member, name: "keep_post", scope: !622, file: !121, line: 1576, baseType: !316, size: 32, align: 32, offset: 832)
!692 = !DIDerivedType(tag: DW_TAG_member, name: "free_referer", scope: !622, file: !121, line: 1578, baseType: !423, size: 8, align: 8, offset: 864)
!693 = !DIDerivedType(tag: DW_TAG_member, name: "postfields", scope: !622, file: !121, line: 1580, baseType: !311, size: 64, align: 64, offset: 896)
!694 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !622, file: !121, line: 1581, baseType: !695, size: 64, align: 64, offset: 960)
!695 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_seek_callback", file: !15, line: 324, baseType: !696)
!696 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !697, size: 64, align: 64)
!697 = !DISubroutineType(types: !698)
!698 = !{!316, !311, !507, !316}
!699 = !DIDerivedType(tag: DW_TAG_member, name: "postfieldsize", scope: !622, file: !121, line: 1582, baseType: !507, size: 64, align: 64, offset: 1024)
!700 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !622, file: !121, line: 1585, baseType: !657, size: 16, align: 16, offset: 1088)
!701 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !622, file: !121, line: 1586, baseType: !316, size: 32, align: 32, offset: 1120)
!702 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_func", scope: !622, file: !121, line: 1588, baseType: !703, size: 64, align: 64, offset: 1152)
!703 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_write_callback", file: !15, line: 223, baseType: !704)
!704 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !705, size: 64, align: 64)
!705 = !DISubroutineType(types: !706)
!706 = !{!347, !500, !347, !347, !311}
!707 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_header", scope: !622, file: !121, line: 1589, baseType: !703, size: 64, align: 64, offset: 1216)
!708 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_rtp", scope: !622, file: !121, line: 1590, baseType: !703, size: 64, align: 64, offset: 1280)
!709 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func_set", scope: !622, file: !121, line: 1591, baseType: !710, size: 64, align: 64, offset: 1344)
!710 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_read_callback", file: !15, line: 335, baseType: !704)
!711 = !DIDerivedType(tag: DW_TAG_member, name: "is_fread_set", scope: !622, file: !121, line: 1592, baseType: !316, size: 32, align: 32, offset: 1408)
!712 = !DIDerivedType(tag: DW_TAG_member, name: "is_fwrite_set", scope: !622, file: !121, line: 1593, baseType: !316, size: 32, align: 32, offset: 1440)
!713 = !DIDerivedType(tag: DW_TAG_member, name: "fprogress", scope: !622, file: !121, line: 1594, baseType: !714, size: 64, align: 64, offset: 1472)
!714 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_progress_callback", file: !15, line: 183, baseType: !715)
!715 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !716, size: 64, align: 64)
!716 = !DISubroutineType(types: !717)
!717 = !{!316, !311, !718, !718, !718, !718}
!718 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!719 = !DIDerivedType(tag: DW_TAG_member, name: "fxferinfo", scope: !622, file: !121, line: 1595, baseType: !720, size: 64, align: 64, offset: 1536)
!720 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_xferinfo_callback", file: !15, line: 191, baseType: !721)
!721 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !722, size: 64, align: 64)
!722 = !DISubroutineType(types: !723)
!723 = !{!316, !311, !507, !507, !507, !507}
!724 = !DIDerivedType(tag: DW_TAG_member, name: "fdebug", scope: !622, file: !121, line: 1596, baseType: !725, size: 64, align: 64, offset: 1600)
!725 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_debug_callback", file: !15, line: 420, baseType: !726)
!726 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !727, size: 64, align: 64)
!727 = !DISubroutineType(types: !728)
!728 = !{!316, !305, !729, !500, !347, !311}
!729 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_infotype", file: !15, line: 418, baseType: !730)
!730 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 409, size: 32, align: 32, elements: !731)
!731 = !{!732, !733, !734, !735, !736, !737, !738, !739}
!732 = !DIEnumerator(name: "CURLINFO_TEXT", value: 0)
!733 = !DIEnumerator(name: "CURLINFO_HEADER_IN", value: 1)
!734 = !DIEnumerator(name: "CURLINFO_HEADER_OUT", value: 2)
!735 = !DIEnumerator(name: "CURLINFO_DATA_IN", value: 3)
!736 = !DIEnumerator(name: "CURLINFO_DATA_OUT", value: 4)
!737 = !DIEnumerator(name: "CURLINFO_SSL_DATA_IN", value: 5)
!738 = !DIEnumerator(name: "CURLINFO_SSL_DATA_OUT", value: 6)
!739 = !DIEnumerator(name: "CURLINFO_END", value: 7)
!740 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_func", scope: !622, file: !121, line: 1597, baseType: !741, size: 64, align: 64, offset: 1664)
!741 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ioctl_callback", file: !15, line: 388, baseType: !742)
!742 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !743, size: 64, align: 64)
!743 = !DISubroutineType(types: !744)
!744 = !{!745, !305, !316, !311}
!745 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlioerr", file: !15, line: 380, baseType: !746)
!746 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 375, size: 32, align: 32, elements: !747)
!747 = !{!748, !749, !750, !751}
!748 = !DIEnumerator(name: "CURLIOE_OK", value: 0)
!749 = !DIEnumerator(name: "CURLIOE_UNKNOWNCMD", value: 1)
!750 = !DIEnumerator(name: "CURLIOE_FAILRESTART", value: 2)
!751 = !DIEnumerator(name: "CURLIOE_LAST", value: 3)
!752 = !DIDerivedType(tag: DW_TAG_member, name: "fsockopt", scope: !622, file: !121, line: 1598, baseType: !753, size: 64, align: 64, offset: 1728)
!753 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sockopt_callback", file: !15, line: 353, baseType: !754)
!754 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !755, size: 64, align: 64)
!755 = !DISubroutineType(types: !756)
!756 = !{!316, !311, !315, !757}
!757 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlsocktype", file: !15, line: 344, baseType: !758)
!758 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 340, size: 32, align: 32, elements: !759)
!759 = !{!760, !761, !762}
!760 = !DIEnumerator(name: "CURLSOCKTYPE_IPCXN", value: 0)
!761 = !DIEnumerator(name: "CURLSOCKTYPE_ACCEPT", value: 1)
!762 = !DIEnumerator(name: "CURLSOCKTYPE_LAST", value: 2)
!763 = !DIDerivedType(tag: DW_TAG_member, name: "sockopt_client", scope: !622, file: !121, line: 1599, baseType: !311, size: 64, align: 64, offset: 1792)
!764 = !DIDerivedType(tag: DW_TAG_member, name: "fopensocket", scope: !622, file: !121, line: 1600, baseType: !765, size: 64, align: 64, offset: 1856)
!765 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_opensocket_callback", file: !15, line: 368, baseType: !766)
!766 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !767, size: 64, align: 64)
!767 = !DISubroutineType(types: !768)
!768 = !{!315, !311, !757, !769}
!769 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !770, size: 64, align: 64)
!770 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_sockaddr", file: !15, line: 357, size: 256, align: 32, elements: !771)
!771 = !{!772, !773, !774, !775, !776}
!772 = !DIDerivedType(tag: DW_TAG_member, name: "family", scope: !770, file: !15, line: 358, baseType: !316, size: 32, align: 32)
!773 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !770, file: !15, line: 359, baseType: !316, size: 32, align: 32, offset: 32)
!774 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !770, file: !15, line: 360, baseType: !316, size: 32, align: 32, offset: 64)
!775 = !DIDerivedType(tag: DW_TAG_member, name: "addrlen", scope: !770, file: !15, line: 361, baseType: !457, size: 32, align: 32, offset: 96)
!776 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !770, file: !15, line: 364, baseType: !777, size: 128, align: 16, offset: 128)
!777 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !778, line: 149, size: 128, align: 16, elements: !779)
!778 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!779 = !{!780, !783}
!780 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !777, file: !778, line: 151, baseType: !781, size: 16, align: 16)
!781 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !782, line: 28, baseType: !657)
!782 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!783 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !777, file: !778, line: 152, baseType: !784, size: 112, align: 8, offset: 16)
!784 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 112, align: 8, elements: !785)
!785 = !{!786}
!786 = !DISubrange(count: 14)
!787 = !DIDerivedType(tag: DW_TAG_member, name: "opensocket_client", scope: !622, file: !121, line: 1603, baseType: !311, size: 64, align: 64, offset: 1920)
!788 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !622, file: !121, line: 1604, baseType: !789, size: 64, align: 64, offset: 1984)
!789 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_closesocket_callback", file: !15, line: 373, baseType: !790)
!790 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !791, size: 64, align: 64)
!791 = !DISubroutineType(types: !792)
!792 = !{!316, !311, !315}
!793 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !622, file: !121, line: 1606, baseType: !311, size: 64, align: 64, offset: 2048)
!794 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !622, file: !121, line: 1608, baseType: !311, size: 64, align: 64, offset: 2112)
!795 = !DIDerivedType(tag: DW_TAG_member, name: "convfromnetwork", scope: !622, file: !121, line: 1611, baseType: !796, size: 64, align: 64, offset: 2176)
!796 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_conv_callback", file: !15, line: 637, baseType: !797)
!797 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !798, size: 64, align: 64)
!798 = !DISubroutineType(types: !799)
!799 = !{!289, !500, !347}
!800 = !DIDerivedType(tag: DW_TAG_member, name: "convtonetwork", scope: !622, file: !121, line: 1613, baseType: !796, size: 64, align: 64, offset: 2240)
!801 = !DIDerivedType(tag: DW_TAG_member, name: "convfromutf8", scope: !622, file: !121, line: 1615, baseType: !796, size: 64, align: 64, offset: 2304)
!802 = !DIDerivedType(tag: DW_TAG_member, name: "progress_client", scope: !622, file: !121, line: 1617, baseType: !311, size: 64, align: 64, offset: 2368)
!803 = !DIDerivedType(tag: DW_TAG_member, name: "ioctl_client", scope: !622, file: !121, line: 1618, baseType: !311, size: 64, align: 64, offset: 2432)
!804 = !DIDerivedType(tag: DW_TAG_member, name: "timeout", scope: !622, file: !121, line: 1619, baseType: !379, size: 64, align: 64, offset: 2496)
!805 = !DIDerivedType(tag: DW_TAG_member, name: "connecttimeout", scope: !622, file: !121, line: 1620, baseType: !379, size: 64, align: 64, offset: 2560)
!806 = !DIDerivedType(tag: DW_TAG_member, name: "accepttimeout", scope: !622, file: !121, line: 1621, baseType: !379, size: 64, align: 64, offset: 2624)
!807 = !DIDerivedType(tag: DW_TAG_member, name: "server_response_timeout", scope: !622, file: !121, line: 1622, baseType: !379, size: 64, align: 64, offset: 2688)
!808 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_blksize", scope: !622, file: !121, line: 1623, baseType: !379, size: 64, align: 64, offset: 2752)
!809 = !DIDerivedType(tag: DW_TAG_member, name: "tftp_no_options", scope: !622, file: !121, line: 1624, baseType: !423, size: 8, align: 8, offset: 2816)
!810 = !DIDerivedType(tag: DW_TAG_member, name: "filesize", scope: !622, file: !121, line: 1625, baseType: !507, size: 64, align: 64, offset: 2880)
!811 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_limit", scope: !622, file: !121, line: 1626, baseType: !379, size: 64, align: 64, offset: 2944)
!812 = !DIDerivedType(tag: DW_TAG_member, name: "low_speed_time", scope: !622, file: !121, line: 1627, baseType: !379, size: 64, align: 64, offset: 3008)
!813 = !DIDerivedType(tag: DW_TAG_member, name: "max_send_speed", scope: !622, file: !121, line: 1628, baseType: !507, size: 64, align: 64, offset: 3072)
!814 = !DIDerivedType(tag: DW_TAG_member, name: "max_recv_speed", scope: !622, file: !121, line: 1629, baseType: !507, size: 64, align: 64, offset: 3136)
!815 = !DIDerivedType(tag: DW_TAG_member, name: "set_resume_from", scope: !622, file: !121, line: 1631, baseType: !507, size: 64, align: 64, offset: 3200)
!816 = !DIDerivedType(tag: DW_TAG_member, name: "headers", scope: !622, file: !121, line: 1632, baseType: !817, size: 64, align: 64, offset: 3264)
!817 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !818, size: 64, align: 64)
!818 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_slist", file: !15, line: 2176, size: 128, align: 64, elements: !819)
!819 = !{!820, !821}
!820 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !818, file: !15, line: 2177, baseType: !500, size: 64, align: 64)
!821 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !818, file: !15, line: 2178, baseType: !817, size: 64, align: 64, offset: 64)
!822 = !DIDerivedType(tag: DW_TAG_member, name: "proxyheaders", scope: !622, file: !121, line: 1633, baseType: !817, size: 64, align: 64, offset: 3328)
!823 = !DIDerivedType(tag: DW_TAG_member, name: "httppost", scope: !622, file: !121, line: 1634, baseType: !824, size: 64, align: 64, offset: 3392)
!824 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !825, size: 64, align: 64)
!825 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_httppost", file: !15, line: 137, size: 896, align: 64, elements: !826)
!826 = !{!827, !828, !829, !830, !831, !832, !833, !834, !835, !836, !837, !838, !839, !840}
!827 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !825, file: !15, line: 138, baseType: !824, size: 64, align: 64)
!828 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !825, file: !15, line: 139, baseType: !500, size: 64, align: 64, offset: 64)
!829 = !DIDerivedType(tag: DW_TAG_member, name: "namelength", scope: !825, file: !15, line: 140, baseType: !379, size: 64, align: 64, offset: 128)
!830 = !DIDerivedType(tag: DW_TAG_member, name: "contents", scope: !825, file: !15, line: 141, baseType: !500, size: 64, align: 64, offset: 192)
!831 = !DIDerivedType(tag: DW_TAG_member, name: "contentslength", scope: !825, file: !15, line: 142, baseType: !379, size: 64, align: 64, offset: 256)
!832 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !825, file: !15, line: 144, baseType: !500, size: 64, align: 64, offset: 320)
!833 = !DIDerivedType(tag: DW_TAG_member, name: "bufferlength", scope: !825, file: !15, line: 145, baseType: !379, size: 64, align: 64, offset: 384)
!834 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !825, file: !15, line: 146, baseType: !500, size: 64, align: 64, offset: 448)
!835 = !DIDerivedType(tag: DW_TAG_member, name: "contentheader", scope: !825, file: !15, line: 147, baseType: !817, size: 64, align: 64, offset: 512)
!836 = !DIDerivedType(tag: DW_TAG_member, name: "more", scope: !825, file: !15, line: 148, baseType: !824, size: 64, align: 64, offset: 576)
!837 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !825, file: !15, line: 151, baseType: !379, size: 64, align: 64, offset: 640)
!838 = !DIDerivedType(tag: DW_TAG_member, name: "showfilename", scope: !825, file: !15, line: 171, baseType: !500, size: 64, align: 64, offset: 704)
!839 = !DIDerivedType(tag: DW_TAG_member, name: "userp", scope: !825, file: !15, line: 174, baseType: !311, size: 64, align: 64, offset: 768)
!840 = !DIDerivedType(tag: DW_TAG_member, name: "contentlen", scope: !825, file: !15, line: 176, baseType: !507, size: 64, align: 64, offset: 832)
!841 = !DIDerivedType(tag: DW_TAG_member, name: "sep_headers", scope: !622, file: !121, line: 1635, baseType: !423, size: 8, align: 8, offset: 3456)
!842 = !DIDerivedType(tag: DW_TAG_member, name: "cookiesession", scope: !622, file: !121, line: 1636, baseType: !423, size: 8, align: 8, offset: 3464)
!843 = !DIDerivedType(tag: DW_TAG_member, name: "crlf", scope: !622, file: !121, line: 1637, baseType: !423, size: 8, align: 8, offset: 3472)
!844 = !DIDerivedType(tag: DW_TAG_member, name: "quote", scope: !622, file: !121, line: 1638, baseType: !817, size: 64, align: 64, offset: 3520)
!845 = !DIDerivedType(tag: DW_TAG_member, name: "postquote", scope: !622, file: !121, line: 1639, baseType: !817, size: 64, align: 64, offset: 3584)
!846 = !DIDerivedType(tag: DW_TAG_member, name: "prequote", scope: !622, file: !121, line: 1640, baseType: !817, size: 64, align: 64, offset: 3648)
!847 = !DIDerivedType(tag: DW_TAG_member, name: "source_quote", scope: !622, file: !121, line: 1641, baseType: !817, size: 64, align: 64, offset: 3712)
!848 = !DIDerivedType(tag: DW_TAG_member, name: "source_prequote", scope: !622, file: !121, line: 1642, baseType: !817, size: 64, align: 64, offset: 3776)
!849 = !DIDerivedType(tag: DW_TAG_member, name: "source_postquote", scope: !622, file: !121, line: 1644, baseType: !817, size: 64, align: 64, offset: 3840)
!850 = !DIDerivedType(tag: DW_TAG_member, name: "telnet_options", scope: !622, file: !121, line: 1646, baseType: !817, size: 64, align: 64, offset: 3904)
!851 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !622, file: !121, line: 1647, baseType: !817, size: 64, align: 64, offset: 3968)
!852 = !DIDerivedType(tag: DW_TAG_member, name: "connect_to", scope: !622, file: !121, line: 1649, baseType: !817, size: 64, align: 64, offset: 4032)
!853 = !DIDerivedType(tag: DW_TAG_member, name: "timecondition", scope: !622, file: !121, line: 1651, baseType: !854, size: 32, align: 32, offset: 4096)
!854 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_TimeCond", file: !15, line: 1929, baseType: !855)
!855 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 1921, size: 32, align: 32, elements: !856)
!856 = !{!857, !858, !859, !860, !861}
!857 = !DIEnumerator(name: "CURL_TIMECOND_NONE", value: 0)
!858 = !DIEnumerator(name: "CURL_TIMECOND_IFMODSINCE", value: 1)
!859 = !DIEnumerator(name: "CURL_TIMECOND_IFUNMODSINCE", value: 2)
!860 = !DIEnumerator(name: "CURL_TIMECOND_LASTMOD", value: 3)
!861 = !DIEnumerator(name: "CURL_TIMECOND_LAST", value: 4)
!862 = !DIDerivedType(tag: DW_TAG_member, name: "timevalue", scope: !622, file: !121, line: 1652, baseType: !599, size: 64, align: 64, offset: 4160)
!863 = !DIDerivedType(tag: DW_TAG_member, name: "httpreq", scope: !622, file: !121, line: 1653, baseType: !864, size: 32, align: 32, offset: 4224)
!864 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_HttpReq", file: !121, line: 1249, baseType: !865)
!865 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 1240, size: 32, align: 32, elements: !866)
!866 = !{!867, !868, !869, !870, !871, !872, !873, !874}
!867 = !DIEnumerator(name: "HTTPREQ_NONE", value: 0)
!868 = !DIEnumerator(name: "HTTPREQ_GET", value: 1)
!869 = !DIEnumerator(name: "HTTPREQ_POST", value: 2)
!870 = !DIEnumerator(name: "HTTPREQ_POST_FORM", value: 3)
!871 = !DIEnumerator(name: "HTTPREQ_PUT", value: 4)
!872 = !DIEnumerator(name: "HTTPREQ_HEAD", value: 5)
!873 = !DIEnumerator(name: "HTTPREQ_CUSTOM", value: 6)
!874 = !DIEnumerator(name: "HTTPREQ_LAST", value: 7)
!875 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !622, file: !121, line: 1654, baseType: !379, size: 64, align: 64, offset: 4288)
!876 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !622, file: !121, line: 1656, baseType: !877, size: 1408, align: 64, offset: 4352)
!877 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_config_data", file: !121, line: 366, size: 1408, align: 64, elements: !878)
!878 = !{!879, !880, !881, !882, !883, !884, !885, !890, !891, !892, !893, !894, !895, !896, !897}
!879 = !DIDerivedType(tag: DW_TAG_member, name: "primary", scope: !877, file: !121, line: 367, baseType: !535, size: 640, align: 64)
!880 = !DIDerivedType(tag: DW_TAG_member, name: "enable_beast", scope: !877, file: !121, line: 368, baseType: !423, size: 8, align: 8, offset: 640)
!881 = !DIDerivedType(tag: DW_TAG_member, name: "no_revoke", scope: !877, file: !121, line: 370, baseType: !423, size: 8, align: 8, offset: 648)
!882 = !DIDerivedType(tag: DW_TAG_member, name: "certverifyresult", scope: !877, file: !121, line: 371, baseType: !379, size: 64, align: 64, offset: 704)
!883 = !DIDerivedType(tag: DW_TAG_member, name: "CRLfile", scope: !877, file: !121, line: 372, baseType: !500, size: 64, align: 64, offset: 768)
!884 = !DIDerivedType(tag: DW_TAG_member, name: "issuercert", scope: !877, file: !121, line: 373, baseType: !500, size: 64, align: 64, offset: 832)
!885 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctx", scope: !877, file: !121, line: 374, baseType: !886, size: 64, align: 64, offset: 896)
!886 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ssl_ctx_callback", file: !15, line: 639, baseType: !887)
!887 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !888, size: 64, align: 64)
!888 = !DISubroutineType(types: !889)
!889 = !{!289, !305, !311, !311}
!890 = !DIDerivedType(tag: DW_TAG_member, name: "fsslctxp", scope: !877, file: !121, line: 375, baseType: !311, size: 64, align: 64, offset: 960)
!891 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !877, file: !121, line: 376, baseType: !423, size: 8, align: 8, offset: 1024)
!892 = !DIDerivedType(tag: DW_TAG_member, name: "falsestart", scope: !877, file: !121, line: 377, baseType: !423, size: 8, align: 8, offset: 1032)
!893 = !DIDerivedType(tag: DW_TAG_member, name: "cert", scope: !877, file: !121, line: 379, baseType: !500, size: 64, align: 64, offset: 1088)
!894 = !DIDerivedType(tag: DW_TAG_member, name: "cert_type", scope: !877, file: !121, line: 380, baseType: !500, size: 64, align: 64, offset: 1152)
!895 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !877, file: !121, line: 381, baseType: !500, size: 64, align: 64, offset: 1216)
!896 = !DIDerivedType(tag: DW_TAG_member, name: "key_type", scope: !877, file: !121, line: 382, baseType: !500, size: 64, align: 64, offset: 1280)
!897 = !DIDerivedType(tag: DW_TAG_member, name: "key_passwd", scope: !877, file: !121, line: 383, baseType: !500, size: 64, align: 64, offset: 1344)
!898 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !622, file: !121, line: 1657, baseType: !877, size: 1408, align: 64, offset: 5760)
!899 = !DIDerivedType(tag: DW_TAG_member, name: "general_ssl", scope: !622, file: !121, line: 1658, baseType: !900, size: 64, align: 64, offset: 7168)
!900 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_general_config", file: !121, line: 392, size: 64, align: 64, elements: !901)
!901 = !{!902}
!902 = !DIDerivedType(tag: DW_TAG_member, name: "max_ssl_sessions", scope: !900, file: !121, line: 393, baseType: !347, size: 64, align: 64)
!903 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !622, file: !121, line: 1659, baseType: !904, size: 32, align: 32, offset: 7232)
!904 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_proxytype", file: !15, line: 657, baseType: !14)
!905 = !DIDerivedType(tag: DW_TAG_member, name: "dns_cache_timeout", scope: !622, file: !121, line: 1660, baseType: !379, size: 64, align: 64, offset: 7296)
!906 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !622, file: !121, line: 1661, baseType: !379, size: 64, align: 64, offset: 7360)
!907 = !DIDerivedType(tag: DW_TAG_member, name: "private_data", scope: !622, file: !121, line: 1662, baseType: !311, size: 64, align: 64, offset: 7424)
!908 = !DIDerivedType(tag: DW_TAG_member, name: "http200aliases", scope: !622, file: !121, line: 1664, baseType: !817, size: 64, align: 64, offset: 7488)
!909 = !DIDerivedType(tag: DW_TAG_member, name: "ipver", scope: !622, file: !121, line: 1666, baseType: !379, size: 64, align: 64, offset: 7552)
!910 = !DIDerivedType(tag: DW_TAG_member, name: "max_filesize", scope: !622, file: !121, line: 1669, baseType: !507, size: 64, align: 64, offset: 7616)
!911 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_filemethod", scope: !622, file: !121, line: 1671, baseType: !912, size: 32, align: 32, offset: 7680)
!912 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpfile", file: !135, line: 98, baseType: !913)
!913 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !135, line: 93, size: 32, align: 32, elements: !914)
!914 = !{!915, !916, !917}
!915 = !DIEnumerator(name: "FTPFILE_MULTICWD", value: 1)
!916 = !DIEnumerator(name: "FTPFILE_NOCWD", value: 2)
!917 = !DIEnumerator(name: "FTPFILE_SINGLECWD", value: 3)
!918 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_create_missing_dirs", scope: !622, file: !121, line: 1673, baseType: !316, size: 32, align: 32, offset: 7712)
!919 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc", scope: !622, file: !121, line: 1677, baseType: !920, size: 64, align: 64, offset: 7744)
!920 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sshkeycallback", file: !15, line: 739, baseType: !921)
!921 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !922, size: 64, align: 64)
!922 = !DISubroutineType(types: !923)
!923 = !{!316, !305, !924, !924, !937, !311}
!924 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !925, size: 64, align: 64)
!925 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !926)
!926 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_khkey", file: !15, line: 711, size: 192, align: 64, elements: !927)
!927 = !{!928, !929, !930}
!928 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !926, file: !15, line: 712, baseType: !527, size: 64, align: 64)
!929 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !926, file: !15, line: 714, baseType: !347, size: 64, align: 64, offset: 64)
!930 = !DIDerivedType(tag: DW_TAG_member, name: "keytype", scope: !926, file: !15, line: 715, baseType: !931, size: 32, align: 32, offset: 128)
!931 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khtype", file: !15, line: 704, size: 32, align: 32, elements: !932)
!932 = !{!933, !934, !935, !936}
!933 = !DIEnumerator(name: "CURLKHTYPE_UNKNOWN", value: 0)
!934 = !DIEnumerator(name: "CURLKHTYPE_RSA1", value: 1)
!935 = !DIEnumerator(name: "CURLKHTYPE_RSA", value: 2)
!936 = !DIEnumerator(name: "CURLKHTYPE_DSS", value: 3)
!937 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khmatch", file: !15, line: 731, size: 32, align: 32, elements: !938)
!938 = !{!939, !940, !941, !942}
!939 = !DIEnumerator(name: "CURLKHMATCH_OK", value: 0)
!940 = !DIEnumerator(name: "CURLKHMATCH_MISMATCH", value: 1)
!941 = !DIEnumerator(name: "CURLKHMATCH_MISSING", value: 2)
!942 = !DIEnumerator(name: "CURLKHMATCH_LAST", value: 3)
!943 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_keyfunc_userp", scope: !622, file: !121, line: 1678, baseType: !311, size: 64, align: 64, offset: 7808)
!944 = !DIDerivedType(tag: DW_TAG_member, name: "printhost", scope: !622, file: !121, line: 1684, baseType: !423, size: 8, align: 8, offset: 7872)
!945 = !DIDerivedType(tag: DW_TAG_member, name: "get_filetime", scope: !622, file: !121, line: 1685, baseType: !423, size: 8, align: 8, offset: 7880)
!946 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_thru_httpproxy", scope: !622, file: !121, line: 1686, baseType: !423, size: 8, align: 8, offset: 7888)
!947 = !DIDerivedType(tag: DW_TAG_member, name: "prefer_ascii", scope: !622, file: !121, line: 1687, baseType: !423, size: 8, align: 8, offset: 7896)
!948 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_append", scope: !622, file: !121, line: 1688, baseType: !423, size: 8, align: 8, offset: 7904)
!949 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_list_only", scope: !622, file: !121, line: 1689, baseType: !423, size: 8, align: 8, offset: 7912)
!950 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_port", scope: !622, file: !121, line: 1690, baseType: !423, size: 8, align: 8, offset: 7920)
!951 = !DIDerivedType(tag: DW_TAG_member, name: "hide_progress", scope: !622, file: !121, line: 1691, baseType: !423, size: 8, align: 8, offset: 7928)
!952 = !DIDerivedType(tag: DW_TAG_member, name: "http_fail_on_error", scope: !622, file: !121, line: 1692, baseType: !423, size: 8, align: 8, offset: 7936)
!953 = !DIDerivedType(tag: DW_TAG_member, name: "http_keep_sending_on_error", scope: !622, file: !121, line: 1693, baseType: !423, size: 8, align: 8, offset: 7944)
!954 = !DIDerivedType(tag: DW_TAG_member, name: "http_follow_location", scope: !622, file: !121, line: 1694, baseType: !423, size: 8, align: 8, offset: 7952)
!955 = !DIDerivedType(tag: DW_TAG_member, name: "http_transfer_encoding", scope: !622, file: !121, line: 1695, baseType: !423, size: 8, align: 8, offset: 7960)
!956 = !DIDerivedType(tag: DW_TAG_member, name: "http_disable_hostname_check_before_authentication", scope: !622, file: !121, line: 1696, baseType: !423, size: 8, align: 8, offset: 7968)
!957 = !DIDerivedType(tag: DW_TAG_member, name: "include_header", scope: !622, file: !121, line: 1697, baseType: !423, size: 8, align: 8, offset: 7976)
!958 = !DIDerivedType(tag: DW_TAG_member, name: "http_set_referer", scope: !622, file: !121, line: 1698, baseType: !423, size: 8, align: 8, offset: 7984)
!959 = !DIDerivedType(tag: DW_TAG_member, name: "http_auto_referer", scope: !622, file: !121, line: 1699, baseType: !423, size: 8, align: 8, offset: 7992)
!960 = !DIDerivedType(tag: DW_TAG_member, name: "opt_no_body", scope: !622, file: !121, line: 1700, baseType: !423, size: 8, align: 8, offset: 8000)
!961 = !DIDerivedType(tag: DW_TAG_member, name: "upload", scope: !622, file: !121, line: 1701, baseType: !423, size: 8, align: 8, offset: 8008)
!962 = !DIDerivedType(tag: DW_TAG_member, name: "use_netrc", scope: !622, file: !121, line: 1703, baseType: !963, size: 32, align: 32, offset: 8032)
!963 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "CURL_NETRC_OPTION", file: !15, line: 1867, size: 32, align: 32, elements: !964)
!964 = !{!965, !966, !967, !968}
!965 = !DIEnumerator(name: "CURL_NETRC_IGNORED", value: 0)
!966 = !DIEnumerator(name: "CURL_NETRC_OPTIONAL", value: 1)
!967 = !DIEnumerator(name: "CURL_NETRC_REQUIRED", value: 2)
!968 = !DIEnumerator(name: "CURL_NETRC_LAST", value: 3)
!969 = !DIDerivedType(tag: DW_TAG_member, name: "verbose", scope: !622, file: !121, line: 1704, baseType: !423, size: 8, align: 8, offset: 8064)
!970 = !DIDerivedType(tag: DW_TAG_member, name: "krb", scope: !622, file: !121, line: 1705, baseType: !423, size: 8, align: 8, offset: 8072)
!971 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_forbid", scope: !622, file: !121, line: 1706, baseType: !423, size: 8, align: 8, offset: 8080)
!972 = !DIDerivedType(tag: DW_TAG_member, name: "reuse_fresh", scope: !622, file: !121, line: 1707, baseType: !423, size: 8, align: 8, offset: 8088)
!973 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !622, file: !121, line: 1708, baseType: !423, size: 8, align: 8, offset: 8096)
!974 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !622, file: !121, line: 1709, baseType: !423, size: 8, align: 8, offset: 8104)
!975 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_pret", scope: !622, file: !121, line: 1710, baseType: !423, size: 8, align: 8, offset: 8112)
!976 = !DIDerivedType(tag: DW_TAG_member, name: "use_ssl", scope: !622, file: !121, line: 1712, baseType: !977, size: 32, align: 32, offset: 8128)
!977 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_usessl", file: !15, line: 752, baseType: !978)
!978 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 746, size: 32, align: 32, elements: !979)
!979 = !{!980, !981, !982, !983, !984}
!980 = !DIEnumerator(name: "CURLUSESSL_NONE", value: 0)
!981 = !DIEnumerator(name: "CURLUSESSL_TRY", value: 1)
!982 = !DIEnumerator(name: "CURLUSESSL_CONTROL", value: 2)
!983 = !DIEnumerator(name: "CURLUSESSL_ALL", value: 3)
!984 = !DIEnumerator(name: "CURLUSESSL_LAST", value: 4)
!985 = !DIDerivedType(tag: DW_TAG_member, name: "ftpsslauth", scope: !622, file: !121, line: 1714, baseType: !986, size: 32, align: 32, offset: 8160)
!986 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpauth", file: !15, line: 795, baseType: !987)
!987 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 790, size: 32, align: 32, elements: !988)
!988 = !{!989, !990, !991, !992}
!989 = !DIEnumerator(name: "CURLFTPAUTH_DEFAULT", value: 0)
!990 = !DIEnumerator(name: "CURLFTPAUTH_SSL", value: 1)
!991 = !DIEnumerator(name: "CURLFTPAUTH_TLS", value: 2)
!992 = !DIEnumerator(name: "CURLFTPAUTH_LAST", value: 3)
!993 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_ccc", scope: !622, file: !121, line: 1715, baseType: !994, size: 32, align: 32, offset: 8192)
!994 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpccc", file: !15, line: 787, baseType: !995)
!995 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 782, size: 32, align: 32, elements: !996)
!996 = !{!997, !998, !999, !1000}
!997 = !DIEnumerator(name: "CURLFTPSSL_CCC_NONE", value: 0)
!998 = !DIEnumerator(name: "CURLFTPSSL_CCC_PASSIVE", value: 1)
!999 = !DIEnumerator(name: "CURLFTPSSL_CCC_ACTIVE", value: 2)
!1000 = !DIEnumerator(name: "CURLFTPSSL_CCC_LAST", value: 3)
!1001 = !DIDerivedType(tag: DW_TAG_member, name: "no_signal", scope: !622, file: !121, line: 1716, baseType: !423, size: 8, align: 8, offset: 8224)
!1002 = !DIDerivedType(tag: DW_TAG_member, name: "global_dns_cache", scope: !622, file: !121, line: 1717, baseType: !423, size: 8, align: 8, offset: 8232)
!1003 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_nodelay", scope: !622, file: !121, line: 1718, baseType: !423, size: 8, align: 8, offset: 8240)
!1004 = !DIDerivedType(tag: DW_TAG_member, name: "ignorecl", scope: !622, file: !121, line: 1719, baseType: !423, size: 8, align: 8, offset: 8248)
!1005 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_skip_ip", scope: !622, file: !121, line: 1720, baseType: !423, size: 8, align: 8, offset: 8256)
!1006 = !DIDerivedType(tag: DW_TAG_member, name: "connect_only", scope: !622, file: !121, line: 1722, baseType: !423, size: 8, align: 8, offset: 8264)
!1007 = !DIDerivedType(tag: DW_TAG_member, name: "ssh_auth_types", scope: !622, file: !121, line: 1723, baseType: !379, size: 64, align: 64, offset: 8320)
!1008 = !DIDerivedType(tag: DW_TAG_member, name: "http_te_skip", scope: !622, file: !121, line: 1724, baseType: !423, size: 8, align: 8, offset: 8384)
!1009 = !DIDerivedType(tag: DW_TAG_member, name: "http_ce_skip", scope: !622, file: !121, line: 1726, baseType: !423, size: 8, align: 8, offset: 8392)
!1010 = !DIDerivedType(tag: DW_TAG_member, name: "new_file_perms", scope: !622, file: !121, line: 1728, baseType: !379, size: 64, align: 64, offset: 8448)
!1011 = !DIDerivedType(tag: DW_TAG_member, name: "new_directory_perms", scope: !622, file: !121, line: 1729, baseType: !379, size: 64, align: 64, offset: 8512)
!1012 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_transfer_mode", scope: !622, file: !121, line: 1730, baseType: !423, size: 8, align: 8, offset: 8576)
!1013 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !622, file: !121, line: 1732, baseType: !1014, size: 3584, align: 64, offset: 8640)
!1014 = !DICompositeType(tag: DW_TAG_array_type, baseType: !500, size: 3584, align: 64, elements: !1015)
!1015 = !{!1016}
!1016 = !DISubrange(count: 56)
!1017 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !622, file: !121, line: 1733, baseType: !457, size: 32, align: 32, offset: 12224)
!1018 = !DIDerivedType(tag: DW_TAG_member, name: "allowed_protocols", scope: !622, file: !121, line: 1734, baseType: !379, size: 64, align: 64, offset: 12288)
!1019 = !DIDerivedType(tag: DW_TAG_member, name: "redir_protocols", scope: !622, file: !121, line: 1735, baseType: !379, size: 64, align: 64, offset: 12352)
!1020 = !DIDerivedType(tag: DW_TAG_member, name: "mail_rcpt", scope: !622, file: !121, line: 1739, baseType: !817, size: 64, align: 64, offset: 12416)
!1021 = !DIDerivedType(tag: DW_TAG_member, name: "sasl_ir", scope: !622, file: !121, line: 1740, baseType: !423, size: 8, align: 8, offset: 12480)
!1022 = !DIDerivedType(tag: DW_TAG_member, name: "rtspreq", scope: !622, file: !121, line: 1742, baseType: !1023, size: 32, align: 32, offset: 12512)
!1023 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_RtspReq", file: !121, line: 1265, baseType: !1024)
!1024 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !121, line: 1251, size: 32, align: 32, elements: !1025)
!1025 = !{!1026, !1027, !1028, !1029, !1030, !1031, !1032, !1033, !1034, !1035, !1036, !1037, !1038}
!1026 = !DIEnumerator(name: "RTSPREQ_NONE", value: 0)
!1027 = !DIEnumerator(name: "RTSPREQ_OPTIONS", value: 1)
!1028 = !DIEnumerator(name: "RTSPREQ_DESCRIBE", value: 2)
!1029 = !DIEnumerator(name: "RTSPREQ_ANNOUNCE", value: 3)
!1030 = !DIEnumerator(name: "RTSPREQ_SETUP", value: 4)
!1031 = !DIEnumerator(name: "RTSPREQ_PLAY", value: 5)
!1032 = !DIEnumerator(name: "RTSPREQ_PAUSE", value: 6)
!1033 = !DIEnumerator(name: "RTSPREQ_TEARDOWN", value: 7)
!1034 = !DIEnumerator(name: "RTSPREQ_GET_PARAMETER", value: 8)
!1035 = !DIEnumerator(name: "RTSPREQ_SET_PARAMETER", value: 9)
!1036 = !DIEnumerator(name: "RTSPREQ_RECORD", value: 10)
!1037 = !DIEnumerator(name: "RTSPREQ_RECEIVE", value: 11)
!1038 = !DIEnumerator(name: "RTSPREQ_LAST", value: 12)
!1039 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !622, file: !121, line: 1743, baseType: !379, size: 64, align: 64, offset: 12544)
!1040 = !DIDerivedType(tag: DW_TAG_member, name: "wildcardmatch", scope: !622, file: !121, line: 1744, baseType: !423, size: 8, align: 8, offset: 12608)
!1041 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_bgn", scope: !622, file: !121, line: 1745, baseType: !1042, size: 64, align: 64, offset: 12672)
!1042 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_bgn_callback", file: !15, line: 292, baseType: !1043)
!1043 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1044, size: 64, align: 64)
!1044 = !DISubroutineType(types: !1045)
!1045 = !{!379, !1046, !311, !316}
!1046 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1047, size: 64, align: 64)
!1047 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!1048 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_end", scope: !622, file: !121, line: 1747, baseType: !1049, size: 64, align: 64, offset: 12736)
!1049 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_end_callback", file: !15, line: 306, baseType: !1050)
!1050 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1051, size: 64, align: 64)
!1051 = !DISubroutineType(types: !1052)
!1052 = !{!379, !311}
!1053 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch", scope: !622, file: !121, line: 1749, baseType: !1054, size: 64, align: 64, offset: 12800)
!1054 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_fnmatch_callback", file: !15, line: 315, baseType: !1055)
!1055 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1056, size: 64, align: 64)
!1056 = !DISubroutineType(types: !1057)
!1057 = !{!316, !311, !527, !527}
!1058 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch_data", scope: !622, file: !121, line: 1751, baseType: !311, size: 64, align: 64, offset: 12864)
!1059 = !DIDerivedType(tag: DW_TAG_member, name: "gssapi_delegation", scope: !622, file: !121, line: 1753, baseType: !379, size: 64, align: 64, offset: 12928)
!1060 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepalive", scope: !622, file: !121, line: 1756, baseType: !423, size: 8, align: 8, offset: 12992)
!1061 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepidle", scope: !622, file: !121, line: 1757, baseType: !379, size: 64, align: 64, offset: 13056)
!1062 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_keepintvl", scope: !622, file: !121, line: 1758, baseType: !379, size: 64, align: 64, offset: 13120)
!1063 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !622, file: !121, line: 1759, baseType: !423, size: 8, align: 8, offset: 13184)
!1064 = !DIDerivedType(tag: DW_TAG_member, name: "maxconnects", scope: !622, file: !121, line: 1761, baseType: !347, size: 64, align: 64, offset: 13248)
!1065 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_npn", scope: !622, file: !121, line: 1763, baseType: !423, size: 8, align: 8, offset: 13312)
!1066 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_enable_alpn", scope: !622, file: !121, line: 1764, baseType: !423, size: 8, align: 8, offset: 13320)
!1067 = !DIDerivedType(tag: DW_TAG_member, name: "path_as_is", scope: !622, file: !121, line: 1765, baseType: !423, size: 8, align: 8, offset: 13328)
!1068 = !DIDerivedType(tag: DW_TAG_member, name: "pipewait", scope: !622, file: !121, line: 1766, baseType: !423, size: 8, align: 8, offset: 13336)
!1069 = !DIDerivedType(tag: DW_TAG_member, name: "expect_100_timeout", scope: !622, file: !121, line: 1768, baseType: !379, size: 64, align: 64, offset: 13376)
!1070 = !DIDerivedType(tag: DW_TAG_member, name: "suppress_connect_headers", scope: !622, file: !121, line: 1769, baseType: !423, size: 8, align: 8, offset: 13440)
!1071 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !622, file: !121, line: 1772, baseType: !256, size: 64, align: 64, offset: 13504)
!1072 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !622, file: !121, line: 1773, baseType: !423, size: 8, align: 8, offset: 13568)
!1073 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !622, file: !121, line: 1774, baseType: !316, size: 32, align: 32, offset: 13600)
!1074 = !DIDerivedType(tag: DW_TAG_member, name: "stream_dependents", scope: !622, file: !121, line: 1776, baseType: !1075, size: 64, align: 64, offset: 13632)
!1075 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1076, size: 64, align: 64)
!1076 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_http2_dep", file: !121, line: 1292, size: 128, align: 64, elements: !1077)
!1077 = !{!1078, !1079}
!1078 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !1076, file: !121, line: 1293, baseType: !1075, size: 64, align: 64)
!1079 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !1076, file: !121, line: 1294, baseType: !256, size: 64, align: 64, offset: 64)
!1080 = !DIDerivedType(tag: DW_TAG_member, name: "abstract_unix_socket", scope: !622, file: !121, line: 1778, baseType: !423, size: 8, align: 8, offset: 13696)
!1081 = !DIDerivedType(tag: DW_TAG_member, name: "change", scope: !257, file: !121, line: 1830, baseType: !1082, size: 384, align: 64, offset: 17216)
!1082 = !DICompositeType(tag: DW_TAG_structure_type, name: "DynamicStatic", file: !121, line: 1444, size: 384, align: 64, elements: !1083)
!1083 = !{!1084, !1085, !1086, !1087, !1088, !1089}
!1084 = !DIDerivedType(tag: DW_TAG_member, name: "url", scope: !1082, file: !121, line: 1445, baseType: !500, size: 64, align: 64)
!1085 = !DIDerivedType(tag: DW_TAG_member, name: "url_alloc", scope: !1082, file: !121, line: 1446, baseType: !423, size: 8, align: 8, offset: 64)
!1086 = !DIDerivedType(tag: DW_TAG_member, name: "referer", scope: !1082, file: !121, line: 1447, baseType: !500, size: 64, align: 64, offset: 128)
!1087 = !DIDerivedType(tag: DW_TAG_member, name: "referer_alloc", scope: !1082, file: !121, line: 1448, baseType: !423, size: 8, align: 8, offset: 192)
!1088 = !DIDerivedType(tag: DW_TAG_member, name: "cookielist", scope: !1082, file: !121, line: 1449, baseType: !817, size: 64, align: 64, offset: 256)
!1089 = !DIDerivedType(tag: DW_TAG_member, name: "resolve", scope: !1082, file: !121, line: 1451, baseType: !817, size: 64, align: 64, offset: 320)
!1090 = !DIDerivedType(tag: DW_TAG_member, name: "cookies", scope: !257, file: !121, line: 1831, baseType: !490, size: 64, align: 64, offset: 17600)
!1091 = !DIDerivedType(tag: DW_TAG_member, name: "progress", scope: !257, file: !121, line: 1835, baseType: !1092, size: 3200, align: 64, offset: 17664)
!1092 = !DICompositeType(tag: DW_TAG_structure_type, name: "Progress", file: !121, line: 1195, size: 3200, align: 64, elements: !1093)
!1093 = !{!1094, !1095, !1096, !1097, !1098, !1099, !1100, !1101, !1102, !1103, !1104, !1105, !1106, !1107, !1108, !1109, !1110, !1111, !1112, !1113, !1114, !1115, !1116, !1117, !1118, !1119, !1120, !1124, !1126}
!1094 = !DIDerivedType(tag: DW_TAG_member, name: "lastshow", scope: !1092, file: !121, line: 1196, baseType: !599, size: 64, align: 64)
!1095 = !DIDerivedType(tag: DW_TAG_member, name: "size_dl", scope: !1092, file: !121, line: 1198, baseType: !507, size: 64, align: 64, offset: 64)
!1096 = !DIDerivedType(tag: DW_TAG_member, name: "size_ul", scope: !1092, file: !121, line: 1199, baseType: !507, size: 64, align: 64, offset: 128)
!1097 = !DIDerivedType(tag: DW_TAG_member, name: "downloaded", scope: !1092, file: !121, line: 1200, baseType: !507, size: 64, align: 64, offset: 192)
!1098 = !DIDerivedType(tag: DW_TAG_member, name: "uploaded", scope: !1092, file: !121, line: 1201, baseType: !507, size: 64, align: 64, offset: 256)
!1099 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1092, file: !121, line: 1203, baseType: !507, size: 64, align: 64, offset: 320)
!1100 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !1092, file: !121, line: 1205, baseType: !423, size: 8, align: 8, offset: 384)
!1101 = !DIDerivedType(tag: DW_TAG_member, name: "width", scope: !1092, file: !121, line: 1206, baseType: !316, size: 32, align: 32, offset: 416)
!1102 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1092, file: !121, line: 1207, baseType: !316, size: 32, align: 32, offset: 448)
!1103 = !DIDerivedType(tag: DW_TAG_member, name: "timespent", scope: !1092, file: !121, line: 1209, baseType: !718, size: 64, align: 64, offset: 512)
!1104 = !DIDerivedType(tag: DW_TAG_member, name: "dlspeed", scope: !1092, file: !121, line: 1211, baseType: !507, size: 64, align: 64, offset: 576)
!1105 = !DIDerivedType(tag: DW_TAG_member, name: "ulspeed", scope: !1092, file: !121, line: 1212, baseType: !507, size: 64, align: 64, offset: 640)
!1106 = !DIDerivedType(tag: DW_TAG_member, name: "t_nslookup", scope: !1092, file: !121, line: 1214, baseType: !718, size: 64, align: 64, offset: 704)
!1107 = !DIDerivedType(tag: DW_TAG_member, name: "t_connect", scope: !1092, file: !121, line: 1215, baseType: !718, size: 64, align: 64, offset: 768)
!1108 = !DIDerivedType(tag: DW_TAG_member, name: "t_appconnect", scope: !1092, file: !121, line: 1216, baseType: !718, size: 64, align: 64, offset: 832)
!1109 = !DIDerivedType(tag: DW_TAG_member, name: "t_pretransfer", scope: !1092, file: !121, line: 1217, baseType: !718, size: 64, align: 64, offset: 896)
!1110 = !DIDerivedType(tag: DW_TAG_member, name: "t_starttransfer", scope: !1092, file: !121, line: 1218, baseType: !718, size: 64, align: 64, offset: 960)
!1111 = !DIDerivedType(tag: DW_TAG_member, name: "t_redirect", scope: !1092, file: !121, line: 1219, baseType: !718, size: 64, align: 64, offset: 1024)
!1112 = !DIDerivedType(tag: DW_TAG_member, name: "start", scope: !1092, file: !121, line: 1221, baseType: !411, size: 128, align: 64, offset: 1088)
!1113 = !DIDerivedType(tag: DW_TAG_member, name: "t_startsingle", scope: !1092, file: !121, line: 1222, baseType: !411, size: 128, align: 64, offset: 1216)
!1114 = !DIDerivedType(tag: DW_TAG_member, name: "t_startop", scope: !1092, file: !121, line: 1223, baseType: !411, size: 128, align: 64, offset: 1344)
!1115 = !DIDerivedType(tag: DW_TAG_member, name: "t_acceptdata", scope: !1092, file: !121, line: 1224, baseType: !411, size: 128, align: 64, offset: 1472)
!1116 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_start", scope: !1092, file: !121, line: 1227, baseType: !411, size: 128, align: 64, offset: 1600)
!1117 = !DIDerivedType(tag: DW_TAG_member, name: "ul_limit_size", scope: !1092, file: !121, line: 1228, baseType: !507, size: 64, align: 64, offset: 1728)
!1118 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_start", scope: !1092, file: !121, line: 1230, baseType: !411, size: 128, align: 64, offset: 1792)
!1119 = !DIDerivedType(tag: DW_TAG_member, name: "dl_limit_size", scope: !1092, file: !121, line: 1231, baseType: !507, size: 64, align: 64, offset: 1920)
!1120 = !DIDerivedType(tag: DW_TAG_member, name: "speeder", scope: !1092, file: !121, line: 1235, baseType: !1121, size: 384, align: 64, offset: 1984)
!1121 = !DICompositeType(tag: DW_TAG_array_type, baseType: !507, size: 384, align: 64, elements: !1122)
!1122 = !{!1123}
!1123 = !DISubrange(count: 6)
!1124 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_time", scope: !1092, file: !121, line: 1236, baseType: !1125, size: 768, align: 64, offset: 2368)
!1125 = !DICompositeType(tag: DW_TAG_array_type, baseType: !411, size: 768, align: 64, elements: !1122)
!1126 = !DIDerivedType(tag: DW_TAG_member, name: "speeder_c", scope: !1092, file: !121, line: 1237, baseType: !316, size: 32, align: 32, offset: 3136)
!1127 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !257, file: !121, line: 1836, baseType: !1128, size: 136640, align: 64, offset: 20864)
!1128 = !DICompositeType(tag: DW_TAG_structure_type, name: "UrlState", file: !121, line: 1310, size: 136640, align: 64, elements: !1129)
!1129 = !{!1130, !1132, !1133, !1134, !1135, !1136, !1137, !1138, !1142, !1143, !1144, !1145, !1146, !1147, !1148, !1149, !1158, !1159, !1160, !1161, !1165, !1166, !1178, !1179, !1188, !1189, !1190, !1191, !1192, !1193, !1194, !1195, !1196, !1197, !1198, !1199, !1200, !1201, !1202, !1203, !1204, !1205, !1206, !1207, !1208, !1209, !1210, !1211, !1212, !1213, !1214, !1215, !1216, !1217, !1218}
!1130 = !DIDerivedType(tag: DW_TAG_member, name: "conn_cache", scope: !1128, file: !121, line: 1313, baseType: !1131, size: 64, align: 64)
!1131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !425, size: 64, align: 64)
!1132 = !DIDerivedType(tag: DW_TAG_member, name: "multi_owned_by_easy", scope: !1128, file: !121, line: 1318, baseType: !423, size: 8, align: 8, offset: 64)
!1133 = !DIDerivedType(tag: DW_TAG_member, name: "keeps_speed", scope: !1128, file: !121, line: 1321, baseType: !411, size: 128, align: 64, offset: 128)
!1134 = !DIDerivedType(tag: DW_TAG_member, name: "lastconnect", scope: !1128, file: !121, line: 1323, baseType: !262, size: 64, align: 64, offset: 256)
!1135 = !DIDerivedType(tag: DW_TAG_member, name: "headerbuff", scope: !1128, file: !121, line: 1325, baseType: !500, size: 64, align: 64, offset: 320)
!1136 = !DIDerivedType(tag: DW_TAG_member, name: "headersize", scope: !1128, file: !121, line: 1326, baseType: !347, size: 64, align: 64, offset: 384)
!1137 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !1128, file: !121, line: 1328, baseType: !500, size: 64, align: 64, offset: 448)
!1138 = !DIDerivedType(tag: DW_TAG_member, name: "uploadbuffer", scope: !1128, file: !121, line: 1329, baseType: !1139, size: 131080, align: 8, offset: 512)
!1139 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 131080, align: 8, elements: !1140)
!1140 = !{!1141}
!1141 = !DISubrange(count: 16385)
!1142 = !DIDerivedType(tag: DW_TAG_member, name: "current_speed", scope: !1128, file: !121, line: 1330, baseType: !507, size: 64, align: 64, offset: 131648)
!1143 = !DIDerivedType(tag: DW_TAG_member, name: "this_is_a_follow", scope: !1128, file: !121, line: 1332, baseType: !423, size: 8, align: 8, offset: 131712)
!1144 = !DIDerivedType(tag: DW_TAG_member, name: "first_host", scope: !1128, file: !121, line: 1334, baseType: !500, size: 64, align: 64, offset: 131776)
!1145 = !DIDerivedType(tag: DW_TAG_member, name: "first_remote_port", scope: !1128, file: !121, line: 1340, baseType: !316, size: 32, align: 32, offset: 131840)
!1146 = !DIDerivedType(tag: DW_TAG_member, name: "session", scope: !1128, file: !121, line: 1341, baseType: !521, size: 64, align: 64, offset: 131904)
!1147 = !DIDerivedType(tag: DW_TAG_member, name: "sessionage", scope: !1128, file: !121, line: 1342, baseType: !379, size: 64, align: 64, offset: 131968)
!1148 = !DIDerivedType(tag: DW_TAG_member, name: "tempcount", scope: !1128, file: !121, line: 1343, baseType: !457, size: 32, align: 32, offset: 132032)
!1149 = !DIDerivedType(tag: DW_TAG_member, name: "tempwrite", scope: !1128, file: !121, line: 1344, baseType: !1150, size: 576, align: 64, offset: 132096)
!1150 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1151, size: 576, align: 64, elements: !1156)
!1151 = !DICompositeType(tag: DW_TAG_structure_type, name: "tempbuf", file: !121, line: 1302, size: 192, align: 64, elements: !1152)
!1152 = !{!1153, !1154, !1155}
!1153 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !1151, file: !121, line: 1303, baseType: !500, size: 64, align: 64)
!1154 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !1151, file: !121, line: 1305, baseType: !347, size: 64, align: 64, offset: 64)
!1155 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !1151, file: !121, line: 1306, baseType: !316, size: 32, align: 32, offset: 128)
!1156 = !{!1157}
!1157 = !DISubrange(count: 3)
!1158 = !DIDerivedType(tag: DW_TAG_member, name: "scratch", scope: !1128, file: !121, line: 1345, baseType: !500, size: 64, align: 64, offset: 132672)
!1159 = !DIDerivedType(tag: DW_TAG_member, name: "errorbuf", scope: !1128, file: !121, line: 1346, baseType: !423, size: 8, align: 8, offset: 132736)
!1160 = !DIDerivedType(tag: DW_TAG_member, name: "os_errno", scope: !1128, file: !121, line: 1349, baseType: !316, size: 32, align: 32, offset: 132768)
!1161 = !DIDerivedType(tag: DW_TAG_member, name: "prev_signal", scope: !1128, file: !121, line: 1352, baseType: !1162, size: 64, align: 64, offset: 132800)
!1162 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1163, size: 64, align: 64)
!1163 = !DISubroutineType(types: !1164)
!1164 = !{null, !316}
!1165 = !DIDerivedType(tag: DW_TAG_member, name: "allow_port", scope: !1128, file: !121, line: 1354, baseType: !423, size: 8, align: 8, offset: 132864)
!1166 = !DIDerivedType(tag: DW_TAG_member, name: "digest", scope: !1128, file: !121, line: 1356, baseType: !1167, size: 512, align: 64, offset: 132928)
!1167 = !DICompositeType(tag: DW_TAG_structure_type, name: "digestdata", file: !121, line: 410, size: 512, align: 64, elements: !1168)
!1168 = !{!1169, !1170, !1171, !1172, !1173, !1174, !1175, !1176, !1177}
!1169 = !DIDerivedType(tag: DW_TAG_member, name: "nonce", scope: !1167, file: !121, line: 416, baseType: !500, size: 64, align: 64)
!1170 = !DIDerivedType(tag: DW_TAG_member, name: "cnonce", scope: !1167, file: !121, line: 417, baseType: !500, size: 64, align: 64, offset: 64)
!1171 = !DIDerivedType(tag: DW_TAG_member, name: "realm", scope: !1167, file: !121, line: 418, baseType: !500, size: 64, align: 64, offset: 128)
!1172 = !DIDerivedType(tag: DW_TAG_member, name: "algo", scope: !1167, file: !121, line: 419, baseType: !316, size: 32, align: 32, offset: 192)
!1173 = !DIDerivedType(tag: DW_TAG_member, name: "stale", scope: !1167, file: !121, line: 420, baseType: !423, size: 8, align: 8, offset: 224)
!1174 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !1167, file: !121, line: 421, baseType: !500, size: 64, align: 64, offset: 256)
!1175 = !DIDerivedType(tag: DW_TAG_member, name: "qop", scope: !1167, file: !121, line: 422, baseType: !500, size: 64, align: 64, offset: 320)
!1176 = !DIDerivedType(tag: DW_TAG_member, name: "algorithm", scope: !1167, file: !121, line: 423, baseType: !500, size: 64, align: 64, offset: 384)
!1177 = !DIDerivedType(tag: DW_TAG_member, name: "nc", scope: !1167, file: !121, line: 424, baseType: !316, size: 32, align: 32, offset: 448)
!1178 = !DIDerivedType(tag: DW_TAG_member, name: "proxydigest", scope: !1128, file: !121, line: 1357, baseType: !1167, size: 512, align: 64, offset: 133440)
!1179 = !DIDerivedType(tag: DW_TAG_member, name: "authhost", scope: !1128, file: !121, line: 1364, baseType: !1180, size: 256, align: 64, offset: 133952)
!1180 = !DICompositeType(tag: DW_TAG_structure_type, name: "auth", file: !121, line: 1278, size: 256, align: 64, elements: !1181)
!1181 = !{!1182, !1183, !1184, !1185, !1186, !1187}
!1182 = !DIDerivedType(tag: DW_TAG_member, name: "want", scope: !1180, file: !121, line: 1279, baseType: !349, size: 64, align: 64)
!1183 = !DIDerivedType(tag: DW_TAG_member, name: "picked", scope: !1180, file: !121, line: 1281, baseType: !349, size: 64, align: 64, offset: 64)
!1184 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !1180, file: !121, line: 1282, baseType: !349, size: 64, align: 64, offset: 128)
!1185 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1180, file: !121, line: 1284, baseType: !423, size: 8, align: 8, offset: 192)
!1186 = !DIDerivedType(tag: DW_TAG_member, name: "multipass", scope: !1180, file: !121, line: 1286, baseType: !423, size: 8, align: 8, offset: 200)
!1187 = !DIDerivedType(tag: DW_TAG_member, name: "iestyle", scope: !1180, file: !121, line: 1288, baseType: !423, size: 8, align: 8, offset: 208)
!1188 = !DIDerivedType(tag: DW_TAG_member, name: "authproxy", scope: !1128, file: !121, line: 1365, baseType: !1180, size: 256, align: 64, offset: 134208)
!1189 = !DIDerivedType(tag: DW_TAG_member, name: "authproblem", scope: !1128, file: !121, line: 1367, baseType: !423, size: 8, align: 8, offset: 134464)
!1190 = !DIDerivedType(tag: DW_TAG_member, name: "resolver", scope: !1128, file: !121, line: 1369, baseType: !311, size: 64, align: 64, offset: 134528)
!1191 = !DIDerivedType(tag: DW_TAG_member, name: "expiretime", scope: !1128, file: !121, line: 1375, baseType: !411, size: 128, align: 64, offset: 134592)
!1192 = !DIDerivedType(tag: DW_TAG_member, name: "timenode", scope: !1128, file: !121, line: 1376, baseType: !403, size: 448, align: 64, offset: 134720)
!1193 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutlist", scope: !1128, file: !121, line: 1377, baseType: !330, size: 256, align: 64, offset: 135168)
!1194 = !DIDerivedType(tag: DW_TAG_member, name: "most_recent_ftp_entrypath", scope: !1128, file: !121, line: 1380, baseType: !500, size: 64, align: 64, offset: 135424)
!1195 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_trying_alternative", scope: !1128, file: !121, line: 1383, baseType: !423, size: 8, align: 8, offset: 135488)
!1196 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1128, file: !121, line: 1385, baseType: !316, size: 32, align: 32, offset: 135520)
!1197 = !DIDerivedType(tag: DW_TAG_member, name: "expect100header", scope: !1128, file: !121, line: 1387, baseType: !423, size: 8, align: 8, offset: 135552)
!1198 = !DIDerivedType(tag: DW_TAG_member, name: "pipe_broke", scope: !1128, file: !121, line: 1389, baseType: !423, size: 8, align: 8, offset: 135560)
!1199 = !DIDerivedType(tag: DW_TAG_member, name: "prev_block_had_trailing_cr", scope: !1128, file: !121, line: 1397, baseType: !423, size: 8, align: 8, offset: 135568)
!1200 = !DIDerivedType(tag: DW_TAG_member, name: "crlf_conversions", scope: !1128, file: !121, line: 1399, baseType: !507, size: 64, align: 64, offset: 135616)
!1201 = !DIDerivedType(tag: DW_TAG_member, name: "pathbuffer", scope: !1128, file: !121, line: 1401, baseType: !500, size: 64, align: 64, offset: 135680)
!1202 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1128, file: !121, line: 1402, baseType: !500, size: 64, align: 64, offset: 135744)
!1203 = !DIDerivedType(tag: DW_TAG_member, name: "slash_removed", scope: !1128, file: !121, line: 1404, baseType: !423, size: 8, align: 8, offset: 135808)
!1204 = !DIDerivedType(tag: DW_TAG_member, name: "use_range", scope: !1128, file: !121, line: 1406, baseType: !423, size: 8, align: 8, offset: 135816)
!1205 = !DIDerivedType(tag: DW_TAG_member, name: "rangestringalloc", scope: !1128, file: !121, line: 1407, baseType: !423, size: 8, align: 8, offset: 135824)
!1206 = !DIDerivedType(tag: DW_TAG_member, name: "range", scope: !1128, file: !121, line: 1409, baseType: !500, size: 64, align: 64, offset: 135872)
!1207 = !DIDerivedType(tag: DW_TAG_member, name: "resume_from", scope: !1128, file: !121, line: 1411, baseType: !507, size: 64, align: 64, offset: 135936)
!1208 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_client_CSeq", scope: !1128, file: !121, line: 1414, baseType: !379, size: 64, align: 64, offset: 136000)
!1209 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_next_server_CSeq", scope: !1128, file: !121, line: 1415, baseType: !379, size: 64, align: 64, offset: 136064)
!1210 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_CSeq_recv", scope: !1128, file: !121, line: 1416, baseType: !379, size: 64, align: 64, offset: 136128)
!1211 = !DIDerivedType(tag: DW_TAG_member, name: "infilesize", scope: !1128, file: !121, line: 1418, baseType: !507, size: 64, align: 64, offset: 136192)
!1212 = !DIDerivedType(tag: DW_TAG_member, name: "drain", scope: !1128, file: !121, line: 1421, baseType: !347, size: 64, align: 64, offset: 136256)
!1213 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1128, file: !121, line: 1424, baseType: !423, size: 8, align: 8, offset: 136320)
!1214 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func", scope: !1128, file: !121, line: 1428, baseType: !710, size: 64, align: 64, offset: 136384)
!1215 = !DIDerivedType(tag: DW_TAG_member, name: "in", scope: !1128, file: !121, line: 1429, baseType: !311, size: 64, align: 64, offset: 136448)
!1216 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_on", scope: !1128, file: !121, line: 1431, baseType: !256, size: 64, align: 64, offset: 136512)
!1217 = !DIDerivedType(tag: DW_TAG_member, name: "stream_depends_e", scope: !1128, file: !121, line: 1432, baseType: !423, size: 8, align: 8, offset: 136576)
!1218 = !DIDerivedType(tag: DW_TAG_member, name: "stream_weight", scope: !1128, file: !121, line: 1433, baseType: !316, size: 32, align: 32, offset: 136608)
!1219 = !DIDerivedType(tag: DW_TAG_member, name: "wildcard", scope: !257, file: !121, line: 1838, baseType: !1220, size: 640, align: 64, offset: 157504)
!1220 = !DICompositeType(tag: DW_TAG_structure_type, name: "WildcardData", file: !1221, line: 46, size: 640, align: 64, elements: !1222)
!1221 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/wildcard.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1222 = !{!1223, !1235, !1236, !1237, !1238, !1239, !1241}
!1223 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1220, file: !1221, line: 47, baseType: !1224, size: 32, align: 32)
!1224 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_states", file: !1221, line: 41, baseType: !1225)
!1225 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1221, line: 30, size: 32, align: 32, elements: !1226)
!1226 = !{!1227, !1228, !1229, !1230, !1231, !1232, !1233, !1234}
!1227 = !DIEnumerator(name: "CURLWC_CLEAR", value: 0)
!1228 = !DIEnumerator(name: "CURLWC_INIT", value: 1)
!1229 = !DIEnumerator(name: "CURLWC_MATCHING", value: 2)
!1230 = !DIEnumerator(name: "CURLWC_DOWNLOADING", value: 3)
!1231 = !DIEnumerator(name: "CURLWC_CLEAN", value: 4)
!1232 = !DIEnumerator(name: "CURLWC_SKIP", value: 5)
!1233 = !DIEnumerator(name: "CURLWC_ERROR", value: 6)
!1234 = !DIEnumerator(name: "CURLWC_DONE", value: 7)
!1235 = !DIDerivedType(tag: DW_TAG_member, name: "path", scope: !1220, file: !1221, line: 48, baseType: !500, size: 64, align: 64, offset: 64)
!1236 = !DIDerivedType(tag: DW_TAG_member, name: "pattern", scope: !1220, file: !1221, line: 49, baseType: !500, size: 64, align: 64, offset: 128)
!1237 = !DIDerivedType(tag: DW_TAG_member, name: "filelist", scope: !1220, file: !1221, line: 50, baseType: !330, size: 256, align: 64, offset: 192)
!1238 = !DIDerivedType(tag: DW_TAG_member, name: "tmp", scope: !1220, file: !1221, line: 51, baseType: !311, size: 64, align: 64, offset: 448)
!1239 = !DIDerivedType(tag: DW_TAG_member, name: "tmp_dtor", scope: !1220, file: !1221, line: 52, baseType: !1240, size: 64, align: 64, offset: 512)
!1240 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_wildcard_tmp_dtor", file: !1221, line: 43, baseType: !362)
!1241 = !DIDerivedType(tag: DW_TAG_member, name: "customptr", scope: !1220, file: !1221, line: 53, baseType: !311, size: 64, align: 64, offset: 576)
!1242 = !DIDerivedType(tag: DW_TAG_member, name: "info", scope: !257, file: !121, line: 1839, baseType: !1243, size: 1856, align: 64, offset: 158144)
!1243 = !DICompositeType(tag: DW_TAG_structure_type, name: "PureInfo", file: !121, line: 1154, size: 1856, align: 64, elements: !1244)
!1244 = !{!1245, !1246, !1247, !1248, !1249, !1250, !1251, !1252, !1253, !1254, !1255, !1256, !1257, !1261, !1262, !1263, !1264, !1265, !1266}
!1245 = !DIDerivedType(tag: DW_TAG_member, name: "httpcode", scope: !1243, file: !121, line: 1155, baseType: !316, size: 32, align: 32)
!1246 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxycode", scope: !1243, file: !121, line: 1156, baseType: !316, size: 32, align: 32, offset: 32)
!1247 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !1243, file: !121, line: 1157, baseType: !316, size: 32, align: 32, offset: 64)
!1248 = !DIDerivedType(tag: DW_TAG_member, name: "filetime", scope: !1243, file: !121, line: 1158, baseType: !379, size: 64, align: 64, offset: 128)
!1249 = !DIDerivedType(tag: DW_TAG_member, name: "timecond", scope: !1243, file: !121, line: 1162, baseType: !423, size: 8, align: 8, offset: 192)
!1250 = !DIDerivedType(tag: DW_TAG_member, name: "header_size", scope: !1243, file: !121, line: 1164, baseType: !379, size: 64, align: 64, offset: 256)
!1251 = !DIDerivedType(tag: DW_TAG_member, name: "request_size", scope: !1243, file: !121, line: 1165, baseType: !379, size: 64, align: 64, offset: 320)
!1252 = !DIDerivedType(tag: DW_TAG_member, name: "proxyauthavail", scope: !1243, file: !121, line: 1166, baseType: !349, size: 64, align: 64, offset: 384)
!1253 = !DIDerivedType(tag: DW_TAG_member, name: "httpauthavail", scope: !1243, file: !121, line: 1167, baseType: !349, size: 64, align: 64, offset: 448)
!1254 = !DIDerivedType(tag: DW_TAG_member, name: "numconnects", scope: !1243, file: !121, line: 1168, baseType: !379, size: 64, align: 64, offset: 512)
!1255 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !1243, file: !121, line: 1169, baseType: !500, size: 64, align: 64, offset: 576)
!1256 = !DIDerivedType(tag: DW_TAG_member, name: "wouldredirect", scope: !1243, file: !121, line: 1170, baseType: !500, size: 64, align: 64, offset: 640)
!1257 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_ip", scope: !1243, file: !121, line: 1180, baseType: !1258, size: 368, align: 8, offset: 704)
!1258 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 368, align: 8, elements: !1259)
!1259 = !{!1260}
!1260 = !DISubrange(count: 46)
!1261 = !DIDerivedType(tag: DW_TAG_member, name: "conn_primary_port", scope: !1243, file: !121, line: 1181, baseType: !379, size: 64, align: 64, offset: 1088)
!1262 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_ip", scope: !1243, file: !121, line: 1183, baseType: !1258, size: 368, align: 8, offset: 1152)
!1263 = !DIDerivedType(tag: DW_TAG_member, name: "conn_local_port", scope: !1243, file: !121, line: 1184, baseType: !379, size: 64, align: 64, offset: 1536)
!1264 = !DIDerivedType(tag: DW_TAG_member, name: "conn_scheme", scope: !1243, file: !121, line: 1186, baseType: !527, size: 64, align: 64, offset: 1600)
!1265 = !DIDerivedType(tag: DW_TAG_member, name: "conn_protocol", scope: !1243, file: !121, line: 1187, baseType: !457, size: 32, align: 32, offset: 1664)
!1266 = !DIDerivedType(tag: DW_TAG_member, name: "certs", scope: !1243, file: !121, line: 1189, baseType: !1267, size: 128, align: 64, offset: 1728)
!1267 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_certinfo", file: !15, line: 2214, size: 128, align: 64, elements: !1268)
!1268 = !{!1269, !1270}
!1269 = !DIDerivedType(tag: DW_TAG_member, name: "num_of_certs", scope: !1267, file: !15, line: 2215, baseType: !316, size: 32, align: 32)
!1270 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !1267, file: !15, line: 2216, baseType: !1271, size: 64, align: 64, offset: 64)
!1271 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !817, size: 64, align: 64)
!1272 = !DIDerivedType(tag: DW_TAG_member, name: "tsi", scope: !257, file: !121, line: 1840, baseType: !1273, size: 128, align: 64, offset: 160000)
!1273 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_tlssessioninfo", file: !15, line: 2245, size: 128, align: 64, elements: !1274)
!1274 = !{!1275, !1291}
!1275 = !DIDerivedType(tag: DW_TAG_member, name: "backend", scope: !1273, file: !15, line: 2246, baseType: !1276, size: 32, align: 32)
!1276 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sslbackend", file: !15, line: 2235, baseType: !1277)
!1277 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !15, line: 2222, size: 32, align: 32, elements: !1278)
!1278 = !{!1279, !1280, !1281, !1282, !1283, !1284, !1285, !1286, !1287, !1288, !1289, !1290}
!1279 = !DIEnumerator(name: "CURLSSLBACKEND_NONE", value: 0)
!1280 = !DIEnumerator(name: "CURLSSLBACKEND_OPENSSL", value: 1)
!1281 = !DIEnumerator(name: "CURLSSLBACKEND_GNUTLS", value: 2)
!1282 = !DIEnumerator(name: "CURLSSLBACKEND_NSS", value: 3)
!1283 = !DIEnumerator(name: "CURLSSLBACKEND_OBSOLETE4", value: 4)
!1284 = !DIEnumerator(name: "CURLSSLBACKEND_GSKIT", value: 5)
!1285 = !DIEnumerator(name: "CURLSSLBACKEND_POLARSSL", value: 6)
!1286 = !DIEnumerator(name: "CURLSSLBACKEND_CYASSL", value: 7)
!1287 = !DIEnumerator(name: "CURLSSLBACKEND_SCHANNEL", value: 8)
!1288 = !DIEnumerator(name: "CURLSSLBACKEND_DARWINSSL", value: 9)
!1289 = !DIEnumerator(name: "CURLSSLBACKEND_AXTLS", value: 10)
!1290 = !DIEnumerator(name: "CURLSSLBACKEND_MBEDTLS", value: 11)
!1291 = !DIDerivedType(tag: DW_TAG_member, name: "internals", scope: !1273, file: !15, line: 2247, baseType: !311, size: 64, align: 64, offset: 64)
!1292 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !257, file: !121, line: 1847, baseType: !457, size: 32, align: 32, offset: 160128)
!1293 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !253, file: !121, line: 904, baseType: !1294, size: 384, align: 64, offset: 64)
!1294 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_chunker", file: !4, line: 82, size: 384, align: 64, elements: !1295)
!1295 = !{!1296, !1300, !1301, !1303, !1304}
!1296 = !DIDerivedType(tag: DW_TAG_member, name: "hexbuffer", scope: !1294, file: !4, line: 83, baseType: !1297, size: 136, align: 8)
!1297 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 136, align: 8, elements: !1298)
!1298 = !{!1299}
!1299 = !DISubrange(count: 17)
!1300 = !DIDerivedType(tag: DW_TAG_member, name: "hexindex", scope: !1294, file: !4, line: 84, baseType: !316, size: 32, align: 32, offset: 160)
!1301 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1294, file: !4, line: 85, baseType: !1302, size: 32, align: 32, offset: 192)
!1302 = !DIDerivedType(tag: DW_TAG_typedef, name: "ChunkyState", file: !4, line: 66, baseType: !3)
!1303 = !DIDerivedType(tag: DW_TAG_member, name: "datasize", scope: !1294, file: !4, line: 86, baseType: !507, size: 64, align: 64, offset: 256)
!1304 = !DIDerivedType(tag: DW_TAG_member, name: "dataleft", scope: !1294, file: !4, line: 87, baseType: !347, size: 64, align: 64, offset: 320)
!1305 = !DIDerivedType(tag: DW_TAG_member, name: "fclosesocket", scope: !253, file: !121, line: 906, baseType: !789, size: 64, align: 64, offset: 448)
!1306 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !253, file: !121, line: 907, baseType: !311, size: 64, align: 64, offset: 512)
!1307 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !253, file: !121, line: 909, baseType: !423, size: 8, align: 8, offset: 576)
!1308 = !DIDerivedType(tag: DW_TAG_member, name: "connection_id", scope: !253, file: !121, line: 915, baseType: !379, size: 64, align: 64, offset: 640)
!1309 = !DIDerivedType(tag: DW_TAG_member, name: "dns_entry", scope: !253, file: !121, line: 922, baseType: !1310, size: 64, align: 64, offset: 704)
!1310 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1311, size: 64, align: 64)
!1311 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_dns_entry", file: !1312, line: 66, size: 192, align: 64, elements: !1313)
!1312 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/hostip.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1313 = !{!1314, !1333, !1334}
!1314 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !1311, file: !1312, line: 67, baseType: !1315, size: 64, align: 64)
!1315 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1316, size: 64, align: 64)
!1316 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_addrinfo", file: !1317, line: 61, baseType: !1318)
!1317 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_addrinfo.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1318 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_addrinfo", file: !1317, line: 51, size: 384, align: 64, elements: !1319)
!1319 = !{!1320, !1321, !1322, !1323, !1324, !1328, !1329, !1331}
!1320 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !1318, file: !1317, line: 52, baseType: !316, size: 32, align: 32)
!1321 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !1318, file: !1317, line: 53, baseType: !316, size: 32, align: 32, offset: 32)
!1322 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !1318, file: !1317, line: 54, baseType: !316, size: 32, align: 32, offset: 64)
!1323 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !1318, file: !1317, line: 55, baseType: !316, size: 32, align: 32, offset: 96)
!1324 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !1318, file: !1317, line: 56, baseType: !1325, size: 32, align: 32, offset: 128)
!1325 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socklen_t", file: !508, line: 186, baseType: !1326)
!1326 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !778, line: 33, baseType: !1327)
!1327 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !416, line: 189, baseType: !457)
!1328 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !1318, file: !1317, line: 57, baseType: !500, size: 64, align: 64, offset: 192)
!1329 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !1318, file: !1317, line: 58, baseType: !1330, size: 64, align: 64, offset: 256)
!1330 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !777, size: 64, align: 64)
!1331 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !1318, file: !1317, line: 59, baseType: !1332, size: 64, align: 64, offset: 320)
!1332 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1318, size: 64, align: 64)
!1333 = !DIDerivedType(tag: DW_TAG_member, name: "timestamp", scope: !1311, file: !1312, line: 69, baseType: !599, size: 64, align: 64, offset: 64)
!1334 = !DIDerivedType(tag: DW_TAG_member, name: "inuse", scope: !1311, file: !1312, line: 71, baseType: !379, size: 64, align: 64, offset: 128)
!1335 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr", scope: !253, file: !121, line: 927, baseType: !1315, size: 64, align: 64, offset: 768)
!1336 = !DIDerivedType(tag: DW_TAG_member, name: "tempaddr", scope: !253, file: !121, line: 928, baseType: !1337, size: 128, align: 64, offset: 832)
!1337 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1315, size: 128, align: 64, elements: !1338)
!1338 = !{!1339}
!1339 = !DISubrange(count: 2)
!1340 = !DIDerivedType(tag: DW_TAG_member, name: "ip_addr_str", scope: !253, file: !121, line: 933, baseType: !1258, size: 368, align: 8, offset: 960)
!1341 = !DIDerivedType(tag: DW_TAG_member, name: "scope_id", scope: !253, file: !121, line: 935, baseType: !457, size: 32, align: 32, offset: 1344)
!1342 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !253, file: !121, line: 937, baseType: !316, size: 32, align: 32, offset: 1376)
!1343 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !253, file: !121, line: 939, baseType: !1344, size: 256, align: 64, offset: 1408)
!1344 = !DICompositeType(tag: DW_TAG_structure_type, name: "hostname", file: !121, line: 581, size: 256, align: 64, elements: !1345)
!1345 = !{!1346, !1347, !1348, !1349}
!1346 = !DIDerivedType(tag: DW_TAG_member, name: "rawalloc", scope: !1344, file: !121, line: 582, baseType: !500, size: 64, align: 64)
!1347 = !DIDerivedType(tag: DW_TAG_member, name: "encalloc", scope: !1344, file: !121, line: 583, baseType: !500, size: 64, align: 64, offset: 64)
!1348 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !1344, file: !121, line: 584, baseType: !500, size: 64, align: 64, offset: 128)
!1349 = !DIDerivedType(tag: DW_TAG_member, name: "dispname", scope: !1344, file: !121, line: 585, baseType: !527, size: 64, align: 64, offset: 192)
!1350 = !DIDerivedType(tag: DW_TAG_member, name: "secondaryhostname", scope: !253, file: !121, line: 940, baseType: !500, size: 64, align: 64, offset: 1664)
!1351 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !253, file: !121, line: 941, baseType: !1344, size: 256, align: 64, offset: 1728)
!1352 = !DIDerivedType(tag: DW_TAG_member, name: "socks_proxy", scope: !253, file: !121, line: 944, baseType: !1353, size: 512, align: 64, offset: 1984)
!1353 = !DICompositeType(tag: DW_TAG_structure_type, name: "proxy_info", file: !121, line: 883, size: 512, align: 64, elements: !1354)
!1354 = !{!1355, !1356, !1357, !1358, !1359}
!1355 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1353, file: !121, line: 884, baseType: !1344, size: 256, align: 64)
!1356 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !1353, file: !121, line: 885, baseType: !379, size: 64, align: 64, offset: 256)
!1357 = !DIDerivedType(tag: DW_TAG_member, name: "proxytype", scope: !1353, file: !121, line: 886, baseType: !904, size: 32, align: 32, offset: 320)
!1358 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1353, file: !121, line: 887, baseType: !500, size: 64, align: 64, offset: 384)
!1359 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !1353, file: !121, line: 888, baseType: !500, size: 64, align: 64, offset: 448)
!1360 = !DIDerivedType(tag: DW_TAG_member, name: "http_proxy", scope: !253, file: !121, line: 945, baseType: !1353, size: 512, align: 64, offset: 2496)
!1361 = !DIDerivedType(tag: DW_TAG_member, name: "port", scope: !253, file: !121, line: 947, baseType: !379, size: 64, align: 64, offset: 3008)
!1362 = !DIDerivedType(tag: DW_TAG_member, name: "remote_port", scope: !253, file: !121, line: 948, baseType: !316, size: 32, align: 32, offset: 3072)
!1363 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !253, file: !121, line: 949, baseType: !316, size: 32, align: 32, offset: 3104)
!1364 = !DIDerivedType(tag: DW_TAG_member, name: "secondary_port", scope: !253, file: !121, line: 951, baseType: !657, size: 16, align: 16, offset: 3136)
!1365 = !DIDerivedType(tag: DW_TAG_member, name: "primary_ip", scope: !253, file: !121, line: 961, baseType: !1258, size: 368, align: 8, offset: 3152)
!1366 = !DIDerivedType(tag: DW_TAG_member, name: "primary_port", scope: !253, file: !121, line: 962, baseType: !379, size: 64, align: 64, offset: 3520)
!1367 = !DIDerivedType(tag: DW_TAG_member, name: "local_ip", scope: !253, file: !121, line: 968, baseType: !1258, size: 368, align: 8, offset: 3584)
!1368 = !DIDerivedType(tag: DW_TAG_member, name: "local_port", scope: !253, file: !121, line: 969, baseType: !379, size: 64, align: 64, offset: 3968)
!1369 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !253, file: !121, line: 971, baseType: !500, size: 64, align: 64, offset: 4032)
!1370 = !DIDerivedType(tag: DW_TAG_member, name: "passwd", scope: !253, file: !121, line: 972, baseType: !500, size: 64, align: 64, offset: 4096)
!1371 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !253, file: !121, line: 973, baseType: !500, size: 64, align: 64, offset: 4160)
!1372 = !DIDerivedType(tag: DW_TAG_member, name: "oauth_bearer", scope: !253, file: !121, line: 975, baseType: !500, size: 64, align: 64, offset: 4224)
!1373 = !DIDerivedType(tag: DW_TAG_member, name: "httpversion", scope: !253, file: !121, line: 977, baseType: !316, size: 32, align: 32, offset: 4288)
!1374 = !DIDerivedType(tag: DW_TAG_member, name: "rtspversion", scope: !253, file: !121, line: 978, baseType: !316, size: 32, align: 32, offset: 4320)
!1375 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !253, file: !121, line: 980, baseType: !411, size: 128, align: 64, offset: 4352)
!1376 = !DIDerivedType(tag: DW_TAG_member, name: "created", scope: !253, file: !121, line: 981, baseType: !411, size: 128, align: 64, offset: 4480)
!1377 = !DIDerivedType(tag: DW_TAG_member, name: "sock", scope: !253, file: !121, line: 982, baseType: !1378, size: 64, align: 32, offset: 4608)
!1378 = !DICompositeType(tag: DW_TAG_array_type, baseType: !315, size: 64, align: 32, elements: !1338)
!1379 = !DIDerivedType(tag: DW_TAG_member, name: "tempsock", scope: !253, file: !121, line: 984, baseType: !1378, size: 64, align: 32, offset: 4672)
!1380 = !DIDerivedType(tag: DW_TAG_member, name: "sock_accepted", scope: !253, file: !121, line: 985, baseType: !1381, size: 16, align: 8, offset: 4736)
!1381 = !DICompositeType(tag: DW_TAG_array_type, baseType: !423, size: 16, align: 8, elements: !1338)
!1382 = !DIDerivedType(tag: DW_TAG_member, name: "recv", scope: !253, file: !121, line: 987, baseType: !1383, size: 128, align: 64, offset: 4800)
!1383 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1384, size: 128, align: 64, elements: !1338)
!1384 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1385, size: 64, align: 64)
!1385 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_recv", file: !121, line: 863, baseType: !1386)
!1386 = !DISubroutineType(types: !1387)
!1387 = !{!612, !262, !316, !500, !347, !1388}
!1388 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !289, size: 64, align: 64)
!1389 = !DIDerivedType(tag: DW_TAG_member, name: "send", scope: !253, file: !121, line: 988, baseType: !1390, size: 128, align: 64, offset: 4928)
!1390 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1391, size: 128, align: 64, elements: !1338)
!1391 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1392, size: 64, align: 64)
!1392 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_send", file: !121, line: 856, baseType: !1393)
!1393 = !DISubroutineType(types: !1394)
!1394 = !{!612, !262, !316, !1046, !347, !1388}
!1395 = !DIDerivedType(tag: DW_TAG_member, name: "ssl", scope: !253, file: !121, line: 993, baseType: !1396, size: 192, align: 32, offset: 5056)
!1396 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1397, size: 192, align: 32, elements: !1338)
!1397 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssl_connect_data", file: !121, line: 274, size: 96, align: 32, elements: !1398)
!1398 = !{!1399, !1400, !1402}
!1399 = !DIDerivedType(tag: DW_TAG_member, name: "use", scope: !1397, file: !121, line: 278, baseType: !423, size: 8, align: 8)
!1400 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1397, file: !121, line: 279, baseType: !1401, size: 32, align: 32, offset: 32)
!1401 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connection_state", file: !121, line: 271, baseType: !120)
!1402 = !DIDerivedType(tag: DW_TAG_member, name: "connecting_state", scope: !1397, file: !121, line: 280, baseType: !1403, size: 32, align: 32, offset: 64)
!1403 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssl_connect_state", file: !121, line: 265, baseType: !126)
!1404 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl", scope: !253, file: !121, line: 994, baseType: !1396, size: 192, align: 32, offset: 5248)
!1405 = !DIDerivedType(tag: DW_TAG_member, name: "ssl_config", scope: !253, file: !121, line: 995, baseType: !535, size: 640, align: 64, offset: 5440)
!1406 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_config", scope: !253, file: !121, line: 996, baseType: !535, size: 640, align: 64, offset: 6080)
!1407 = !DIDerivedType(tag: DW_TAG_member, name: "tls_upgraded", scope: !253, file: !121, line: 997, baseType: !423, size: 8, align: 8, offset: 6720)
!1408 = !DIDerivedType(tag: DW_TAG_member, name: "bits", scope: !253, file: !121, line: 999, baseType: !1409, size: 280, align: 8, offset: 6728)
!1409 = !DICompositeType(tag: DW_TAG_structure_type, name: "ConnectBits", file: !121, line: 514, size: 280, align: 8, elements: !1410)
!1410 = !{!1411, !1412, !1413, !1414, !1415, !1416, !1417, !1418, !1419, !1420, !1421, !1422, !1423, !1424, !1425, !1426, !1427, !1428, !1429, !1430, !1431, !1432, !1433, !1434, !1435, !1436, !1437, !1438, !1439, !1440, !1441, !1442, !1443}
!1411 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !1409, file: !121, line: 516, baseType: !423, size: 8, align: 8)
!1412 = !DIDerivedType(tag: DW_TAG_member, name: "reuse", scope: !1409, file: !121, line: 517, baseType: !423, size: 8, align: 8, offset: 8)
!1413 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_host", scope: !1409, file: !121, line: 518, baseType: !423, size: 8, align: 8, offset: 16)
!1414 = !DIDerivedType(tag: DW_TAG_member, name: "conn_to_port", scope: !1409, file: !121, line: 520, baseType: !423, size: 8, align: 8, offset: 24)
!1415 = !DIDerivedType(tag: DW_TAG_member, name: "proxy", scope: !1409, file: !121, line: 522, baseType: !423, size: 8, align: 8, offset: 32)
!1416 = !DIDerivedType(tag: DW_TAG_member, name: "httpproxy", scope: !1409, file: !121, line: 523, baseType: !423, size: 8, align: 8, offset: 40)
!1417 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy", scope: !1409, file: !121, line: 524, baseType: !423, size: 8, align: 8, offset: 48)
!1418 = !DIDerivedType(tag: DW_TAG_member, name: "user_passwd", scope: !1409, file: !121, line: 525, baseType: !423, size: 8, align: 8, offset: 56)
!1419 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_user_passwd", scope: !1409, file: !121, line: 526, baseType: !423, size: 8, align: 8, offset: 64)
!1420 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6_ip", scope: !1409, file: !121, line: 527, baseType: !423, size: 8, align: 8, offset: 72)
!1421 = !DIDerivedType(tag: DW_TAG_member, name: "ipv6", scope: !1409, file: !121, line: 529, baseType: !423, size: 8, align: 8, offset: 80)
!1422 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1409, file: !121, line: 531, baseType: !423, size: 8, align: 8, offset: 88)
!1423 = !DIDerivedType(tag: DW_TAG_member, name: "tcpconnect", scope: !1409, file: !121, line: 533, baseType: !1381, size: 16, align: 8, offset: 96)
!1424 = !DIDerivedType(tag: DW_TAG_member, name: "protoconnstart", scope: !1409, file: !121, line: 535, baseType: !423, size: 8, align: 8, offset: 112)
!1425 = !DIDerivedType(tag: DW_TAG_member, name: "retry", scope: !1409, file: !121, line: 538, baseType: !423, size: 8, align: 8, offset: 120)
!1426 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_proxy", scope: !1409, file: !121, line: 540, baseType: !423, size: 8, align: 8, offset: 128)
!1427 = !DIDerivedType(tag: DW_TAG_member, name: "authneg", scope: !1409, file: !121, line: 544, baseType: !423, size: 8, align: 8, offset: 136)
!1428 = !DIDerivedType(tag: DW_TAG_member, name: "rewindaftersend", scope: !1409, file: !121, line: 548, baseType: !423, size: 8, align: 8, offset: 144)
!1429 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_epsv", scope: !1409, file: !121, line: 552, baseType: !423, size: 8, align: 8, offset: 152)
!1430 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_eprt", scope: !1409, file: !121, line: 556, baseType: !423, size: 8, align: 8, offset: 160)
!1431 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_use_data_ssl", scope: !1409, file: !121, line: 559, baseType: !423, size: 8, align: 8, offset: 168)
!1432 = !DIDerivedType(tag: DW_TAG_member, name: "netrc", scope: !1409, file: !121, line: 560, baseType: !423, size: 8, align: 8, offset: 176)
!1433 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd_in_url", scope: !1409, file: !121, line: 561, baseType: !423, size: 8, align: 8, offset: 184)
!1434 = !DIDerivedType(tag: DW_TAG_member, name: "stream_was_rewound", scope: !1409, file: !121, line: 562, baseType: !423, size: 8, align: 8, offset: 192)
!1435 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_connect_closed", scope: !1409, file: !121, line: 565, baseType: !423, size: 8, align: 8, offset: 200)
!1436 = !DIDerivedType(tag: DW_TAG_member, name: "bound", scope: !1409, file: !121, line: 568, baseType: !423, size: 8, align: 8, offset: 208)
!1437 = !DIDerivedType(tag: DW_TAG_member, name: "type_set", scope: !1409, file: !121, line: 570, baseType: !423, size: 8, align: 8, offset: 216)
!1438 = !DIDerivedType(tag: DW_TAG_member, name: "multiplex", scope: !1409, file: !121, line: 571, baseType: !423, size: 8, align: 8, offset: 224)
!1439 = !DIDerivedType(tag: DW_TAG_member, name: "tcp_fastopen", scope: !1409, file: !121, line: 573, baseType: !423, size: 8, align: 8, offset: 232)
!1440 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_npn", scope: !1409, file: !121, line: 574, baseType: !423, size: 8, align: 8, offset: 240)
!1441 = !DIDerivedType(tag: DW_TAG_member, name: "tls_enable_alpn", scope: !1409, file: !121, line: 575, baseType: !423, size: 8, align: 8, offset: 248)
!1442 = !DIDerivedType(tag: DW_TAG_member, name: "proxy_ssl_connected", scope: !1409, file: !121, line: 576, baseType: !1381, size: 16, align: 8, offset: 256)
!1443 = !DIDerivedType(tag: DW_TAG_member, name: "socksproxy_connecting", scope: !1409, file: !121, line: 578, baseType: !423, size: 8, align: 8, offset: 272)
!1444 = !DIDerivedType(tag: DW_TAG_member, name: "connecttime", scope: !253, file: !121, line: 1004, baseType: !411, size: 128, align: 64, offset: 7040)
!1445 = !DIDerivedType(tag: DW_TAG_member, name: "num_addr", scope: !253, file: !121, line: 1006, baseType: !316, size: 32, align: 32, offset: 7168)
!1446 = !DIDerivedType(tag: DW_TAG_member, name: "timeoutms_per_addr", scope: !253, file: !121, line: 1007, baseType: !599, size: 64, align: 64, offset: 7232)
!1447 = !DIDerivedType(tag: DW_TAG_member, name: "handler", scope: !253, file: !121, line: 1010, baseType: !1448, size: 64, align: 64, offset: 7296)
!1448 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1449, size: 64, align: 64)
!1449 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1450)
!1450 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_handler", file: !121, line: 763, size: 1024, align: 64, elements: !1451)
!1451 = !{!1452, !1453, !1457, !1462, !1467, !1473, !1474, !1475, !1476, !1481, !1482, !1483, !1489, !1493, !1498, !1499, !1500}
!1452 = !DIDerivedType(tag: DW_TAG_member, name: "scheme", scope: !1450, file: !121, line: 764, baseType: !527, size: 64, align: 64)
!1453 = !DIDerivedType(tag: DW_TAG_member, name: "setup_connection", scope: !1450, file: !121, line: 767, baseType: !1454, size: 64, align: 64, offset: 64)
!1454 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1455, size: 64, align: 64)
!1455 = !DISubroutineType(types: !1456)
!1456 = !{!289, !262}
!1457 = !DIDerivedType(tag: DW_TAG_member, name: "do_it", scope: !1450, file: !121, line: 770, baseType: !1458, size: 64, align: 64, offset: 128)
!1458 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1459, size: 64, align: 64)
!1459 = !DISubroutineType(types: !1460)
!1460 = !{!289, !262, !1461}
!1461 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !423, size: 64, align: 64)
!1462 = !DIDerivedType(tag: DW_TAG_member, name: "done", scope: !1450, file: !121, line: 771, baseType: !1463, size: 64, align: 64, offset: 192)
!1463 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_done_func", file: !121, line: 634, baseType: !1464)
!1464 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1465, size: 64, align: 64)
!1465 = !DISubroutineType(types: !1466)
!1466 = !{!289, !262, !289, !423}
!1467 = !DIDerivedType(tag: DW_TAG_member, name: "do_more", scope: !1450, file: !121, line: 777, baseType: !1468, size: 64, align: 64, offset: 256)
!1468 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_do_more_func", file: !121, line: 633, baseType: !1469)
!1469 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1470, size: 64, align: 64)
!1470 = !DISubroutineType(types: !1471)
!1471 = !{!289, !262, !1472}
!1472 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !316, size: 64, align: 64)
!1473 = !DIDerivedType(tag: DW_TAG_member, name: "connect_it", scope: !1450, file: !121, line: 785, baseType: !1458, size: 64, align: 64, offset: 320)
!1474 = !DIDerivedType(tag: DW_TAG_member, name: "connecting", scope: !1450, file: !121, line: 788, baseType: !1458, size: 64, align: 64, offset: 384)
!1475 = !DIDerivedType(tag: DW_TAG_member, name: "doing", scope: !1450, file: !121, line: 789, baseType: !1458, size: 64, align: 64, offset: 448)
!1476 = !DIDerivedType(tag: DW_TAG_member, name: "proto_getsock", scope: !1450, file: !121, line: 793, baseType: !1477, size: 64, align: 64, offset: 512)
!1477 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1478, size: 64, align: 64)
!1478 = !DISubroutineType(types: !1479)
!1479 = !{!316, !262, !1480, !316}
!1480 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !315, size: 64, align: 64)
!1481 = !DIDerivedType(tag: DW_TAG_member, name: "doing_getsock", scope: !1450, file: !121, line: 799, baseType: !1477, size: 64, align: 64, offset: 576)
!1482 = !DIDerivedType(tag: DW_TAG_member, name: "domore_getsock", scope: !1450, file: !121, line: 805, baseType: !1477, size: 64, align: 64, offset: 640)
!1483 = !DIDerivedType(tag: DW_TAG_member, name: "perform_getsock", scope: !1450, file: !121, line: 812, baseType: !1484, size: 64, align: 64, offset: 704)
!1484 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1485, size: 64, align: 64)
!1485 = !DISubroutineType(types: !1486)
!1486 = !{!316, !1487, !1480, !316}
!1487 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1488, size: 64, align: 64)
!1488 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !253)
!1489 = !DIDerivedType(tag: DW_TAG_member, name: "disconnect", scope: !1450, file: !121, line: 821, baseType: !1490, size: 64, align: 64, offset: 768)
!1490 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1491, size: 64, align: 64)
!1491 = !DISubroutineType(types: !1492)
!1492 = !{!289, !262, !423}
!1493 = !DIDerivedType(tag: DW_TAG_member, name: "readwrite", scope: !1450, file: !121, line: 825, baseType: !1494, size: 64, align: 64, offset: 832)
!1494 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1495, size: 64, align: 64)
!1495 = !DISubroutineType(types: !1496)
!1496 = !{!289, !256, !262, !1497, !1461}
!1497 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !612, size: 64, align: 64)
!1498 = !DIDerivedType(tag: DW_TAG_member, name: "defport", scope: !1450, file: !121, line: 828, baseType: !379, size: 64, align: 64, offset: 896)
!1499 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !1450, file: !121, line: 829, baseType: !457, size: 32, align: 32, offset: 960)
!1500 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !1450, file: !121, line: 831, baseType: !457, size: 32, align: 32, offset: 992)
!1501 = !DIDerivedType(tag: DW_TAG_member, name: "given", scope: !253, file: !121, line: 1011, baseType: !1448, size: 64, align: 64, offset: 7360)
!1502 = !DIDerivedType(tag: DW_TAG_member, name: "ip_version", scope: !253, file: !121, line: 1013, baseType: !379, size: 64, align: 64, offset: 7424)
!1503 = !DIDerivedType(tag: DW_TAG_member, name: "sockfd", scope: !253, file: !121, line: 1017, baseType: !315, size: 32, align: 32, offset: 7488)
!1504 = !DIDerivedType(tag: DW_TAG_member, name: "writesockfd", scope: !253, file: !121, line: 1018, baseType: !315, size: 32, align: 32, offset: 7520)
!1505 = !DIDerivedType(tag: DW_TAG_member, name: "allocptr", scope: !253, file: !121, line: 1035, baseType: !1506, size: 640, align: 64, offset: 7552)
!1506 = !DICompositeType(tag: DW_TAG_structure_type, name: "dynamically_allocated_data", file: !121, line: 1024, size: 640, align: 64, elements: !1507)
!1507 = !{!1508, !1509, !1510, !1511, !1512, !1513, !1514, !1515, !1516, !1517}
!1508 = !DIDerivedType(tag: DW_TAG_member, name: "proxyuserpwd", scope: !1506, file: !121, line: 1025, baseType: !500, size: 64, align: 64)
!1509 = !DIDerivedType(tag: DW_TAG_member, name: "uagent", scope: !1506, file: !121, line: 1026, baseType: !500, size: 64, align: 64, offset: 64)
!1510 = !DIDerivedType(tag: DW_TAG_member, name: "accept_encoding", scope: !1506, file: !121, line: 1027, baseType: !500, size: 64, align: 64, offset: 128)
!1511 = !DIDerivedType(tag: DW_TAG_member, name: "userpwd", scope: !1506, file: !121, line: 1028, baseType: !500, size: 64, align: 64, offset: 192)
!1512 = !DIDerivedType(tag: DW_TAG_member, name: "rangeline", scope: !1506, file: !121, line: 1029, baseType: !500, size: 64, align: 64, offset: 256)
!1513 = !DIDerivedType(tag: DW_TAG_member, name: "ref", scope: !1506, file: !121, line: 1030, baseType: !500, size: 64, align: 64, offset: 320)
!1514 = !DIDerivedType(tag: DW_TAG_member, name: "host", scope: !1506, file: !121, line: 1031, baseType: !500, size: 64, align: 64, offset: 384)
!1515 = !DIDerivedType(tag: DW_TAG_member, name: "cookiehost", scope: !1506, file: !121, line: 1032, baseType: !500, size: 64, align: 64, offset: 448)
!1516 = !DIDerivedType(tag: DW_TAG_member, name: "rtsp_transport", scope: !1506, file: !121, line: 1033, baseType: !500, size: 64, align: 64, offset: 512)
!1517 = !DIDerivedType(tag: DW_TAG_member, name: "te", scope: !1506, file: !121, line: 1034, baseType: !500, size: 64, align: 64, offset: 576)
!1518 = !DIDerivedType(tag: DW_TAG_member, name: "readchannel_inuse", scope: !253, file: !121, line: 1057, baseType: !423, size: 8, align: 8, offset: 8192)
!1519 = !DIDerivedType(tag: DW_TAG_member, name: "writechannel_inuse", scope: !253, file: !121, line: 1059, baseType: !423, size: 8, align: 8, offset: 8200)
!1520 = !DIDerivedType(tag: DW_TAG_member, name: "send_pipe", scope: !253, file: !121, line: 1061, baseType: !330, size: 256, align: 64, offset: 8256)
!1521 = !DIDerivedType(tag: DW_TAG_member, name: "recv_pipe", scope: !253, file: !121, line: 1063, baseType: !330, size: 256, align: 64, offset: 8512)
!1522 = !DIDerivedType(tag: DW_TAG_member, name: "master_buffer", scope: !253, file: !121, line: 1065, baseType: !500, size: 64, align: 64, offset: 8768)
!1523 = !DIDerivedType(tag: DW_TAG_member, name: "read_pos", scope: !253, file: !121, line: 1067, baseType: !347, size: 64, align: 64, offset: 8832)
!1524 = !DIDerivedType(tag: DW_TAG_member, name: "buf_len", scope: !253, file: !121, line: 1068, baseType: !347, size: 64, align: 64, offset: 8896)
!1525 = !DIDerivedType(tag: DW_TAG_member, name: "seek_func", scope: !253, file: !121, line: 1071, baseType: !695, size: 64, align: 64, offset: 8960)
!1526 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !253, file: !121, line: 1072, baseType: !311, size: 64, align: 64, offset: 9024)
!1527 = !DIDerivedType(tag: DW_TAG_member, name: "syserr_buf", scope: !253, file: !121, line: 1091, baseType: !1528, size: 2048, align: 8, offset: 9088)
!1528 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 2048, align: 8, elements: !1529)
!1529 = !{!1530}
!1530 = !DISubrange(count: 256)
!1531 = !DIDerivedType(tag: DW_TAG_member, name: "trailer", scope: !253, file: !121, line: 1099, baseType: !500, size: 64, align: 64, offset: 11136)
!1532 = !DIDerivedType(tag: DW_TAG_member, name: "trlMax", scope: !253, file: !121, line: 1100, baseType: !316, size: 32, align: 32, offset: 11200)
!1533 = !DIDerivedType(tag: DW_TAG_member, name: "trlPos", scope: !253, file: !121, line: 1101, baseType: !316, size: 32, align: 32, offset: 11232)
!1534 = !DIDerivedType(tag: DW_TAG_member, name: "proto", scope: !253, file: !121, line: 1114, baseType: !1535, size: 1792, align: 64, offset: 11264)
!1535 = !DICompositeType(tag: DW_TAG_union_type, scope: !253, file: !121, line: 1103, size: 1792, align: 64, elements: !1536)
!1536 = !{!1537, !1584, !1589, !1594, !1597, !1645, !1659, !1671, !1678, !1696}
!1537 = !DIDerivedType(tag: DW_TAG_member, name: "ftpc", scope: !1535, file: !121, line: 1104, baseType: !1538, size: 1792, align: 64)
!1538 = !DICompositeType(tag: DW_TAG_structure_type, name: "ftp_conn", file: !135, line: 118, size: 1792, align: 64, elements: !1539)
!1539 = !{!1540, !1560, !1561, !1563, !1564, !1565, !1566, !1567, !1568, !1569, !1570, !1571, !1572, !1573, !1574, !1575, !1576, !1578, !1579, !1580, !1581, !1582, !1583}
!1540 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1538, file: !135, line: 119, baseType: !1541, size: 896, align: 64)
!1541 = !DICompositeType(tag: DW_TAG_structure_type, name: "pingpong", file: !1542, line: 48, size: 896, align: 64, elements: !1543)
!1542 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/pingpong.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1543 = !{!1544, !1545, !1546, !1547, !1548, !1549, !1550, !1551, !1552, !1553, !1554, !1555, !1556}
!1544 = !DIDerivedType(tag: DW_TAG_member, name: "cache", scope: !1541, file: !1542, line: 49, baseType: !500, size: 64, align: 64)
!1545 = !DIDerivedType(tag: DW_TAG_member, name: "cache_size", scope: !1541, file: !1542, line: 50, baseType: !347, size: 64, align: 64, offset: 64)
!1546 = !DIDerivedType(tag: DW_TAG_member, name: "nread_resp", scope: !1541, file: !1542, line: 51, baseType: !347, size: 64, align: 64, offset: 128)
!1547 = !DIDerivedType(tag: DW_TAG_member, name: "linestart_resp", scope: !1541, file: !1542, line: 52, baseType: !500, size: 64, align: 64, offset: 192)
!1548 = !DIDerivedType(tag: DW_TAG_member, name: "pending_resp", scope: !1541, file: !1542, line: 54, baseType: !423, size: 8, align: 8, offset: 256)
!1549 = !DIDerivedType(tag: DW_TAG_member, name: "sendthis", scope: !1541, file: !1542, line: 57, baseType: !500, size: 64, align: 64, offset: 320)
!1550 = !DIDerivedType(tag: DW_TAG_member, name: "sendleft", scope: !1541, file: !1542, line: 59, baseType: !347, size: 64, align: 64, offset: 384)
!1551 = !DIDerivedType(tag: DW_TAG_member, name: "sendsize", scope: !1541, file: !1542, line: 60, baseType: !347, size: 64, align: 64, offset: 448)
!1552 = !DIDerivedType(tag: DW_TAG_member, name: "response", scope: !1541, file: !1542, line: 61, baseType: !411, size: 128, align: 64, offset: 512)
!1553 = !DIDerivedType(tag: DW_TAG_member, name: "response_time", scope: !1541, file: !1542, line: 63, baseType: !379, size: 64, align: 64, offset: 640)
!1554 = !DIDerivedType(tag: DW_TAG_member, name: "conn", scope: !1541, file: !1542, line: 66, baseType: !262, size: 64, align: 64, offset: 704)
!1555 = !DIDerivedType(tag: DW_TAG_member, name: "statemach_act", scope: !1541, file: !1542, line: 72, baseType: !1454, size: 64, align: 64, offset: 768)
!1556 = !DIDerivedType(tag: DW_TAG_member, name: "endofresp", scope: !1541, file: !1542, line: 74, baseType: !1557, size: 64, align: 64, offset: 832)
!1557 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1558, size: 64, align: 64)
!1558 = !DISubroutineType(types: !1559)
!1559 = !{!423, !262, !500, !347, !1472}
!1560 = !DIDerivedType(tag: DW_TAG_member, name: "entrypath", scope: !1538, file: !135, line: 120, baseType: !500, size: 64, align: 64, offset: 896)
!1561 = !DIDerivedType(tag: DW_TAG_member, name: "dirs", scope: !1538, file: !135, line: 121, baseType: !1562, size: 64, align: 64, offset: 960)
!1562 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !500, size: 64, align: 64)
!1563 = !DIDerivedType(tag: DW_TAG_member, name: "dirdepth", scope: !1538, file: !135, line: 122, baseType: !316, size: 32, align: 32, offset: 1024)
!1564 = !DIDerivedType(tag: DW_TAG_member, name: "diralloc", scope: !1538, file: !135, line: 123, baseType: !316, size: 32, align: 32, offset: 1056)
!1565 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !1538, file: !135, line: 124, baseType: !500, size: 64, align: 64, offset: 1088)
!1566 = !DIDerivedType(tag: DW_TAG_member, name: "dont_check", scope: !1538, file: !135, line: 125, baseType: !423, size: 8, align: 8, offset: 1152)
!1567 = !DIDerivedType(tag: DW_TAG_member, name: "ctl_valid", scope: !1538, file: !135, line: 128, baseType: !423, size: 8, align: 8, offset: 1160)
!1568 = !DIDerivedType(tag: DW_TAG_member, name: "cwddone", scope: !1538, file: !135, line: 131, baseType: !423, size: 8, align: 8, offset: 1168)
!1569 = !DIDerivedType(tag: DW_TAG_member, name: "cwdfail", scope: !1538, file: !135, line: 133, baseType: !423, size: 8, align: 8, offset: 1176)
!1570 = !DIDerivedType(tag: DW_TAG_member, name: "wait_data_conn", scope: !1538, file: !135, line: 135, baseType: !423, size: 8, align: 8, offset: 1184)
!1571 = !DIDerivedType(tag: DW_TAG_member, name: "prevpath", scope: !1538, file: !135, line: 136, baseType: !500, size: 64, align: 64, offset: 1216)
!1572 = !DIDerivedType(tag: DW_TAG_member, name: "transfertype", scope: !1538, file: !135, line: 137, baseType: !501, size: 8, align: 8, offset: 1280)
!1573 = !DIDerivedType(tag: DW_TAG_member, name: "count1", scope: !1538, file: !135, line: 139, baseType: !316, size: 32, align: 32, offset: 1312)
!1574 = !DIDerivedType(tag: DW_TAG_member, name: "count2", scope: !1538, file: !135, line: 140, baseType: !316, size: 32, align: 32, offset: 1344)
!1575 = !DIDerivedType(tag: DW_TAG_member, name: "count3", scope: !1538, file: !135, line: 141, baseType: !316, size: 32, align: 32, offset: 1376)
!1576 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1538, file: !135, line: 142, baseType: !1577, size: 32, align: 32, offset: 1408)
!1577 = !DIDerivedType(tag: DW_TAG_typedef, name: "ftpstate", file: !135, line: 80, baseType: !134)
!1578 = !DIDerivedType(tag: DW_TAG_member, name: "state_saved", scope: !1538, file: !135, line: 143, baseType: !1577, size: 32, align: 32, offset: 1440)
!1579 = !DIDerivedType(tag: DW_TAG_member, name: "retr_size_saved", scope: !1538, file: !135, line: 145, baseType: !507, size: 64, align: 64, offset: 1472)
!1580 = !DIDerivedType(tag: DW_TAG_member, name: "server_os", scope: !1538, file: !135, line: 146, baseType: !500, size: 64, align: 64, offset: 1536)
!1581 = !DIDerivedType(tag: DW_TAG_member, name: "known_filesize", scope: !1538, file: !135, line: 147, baseType: !507, size: 64, align: 64, offset: 1600)
!1582 = !DIDerivedType(tag: DW_TAG_member, name: "newhost", scope: !1538, file: !135, line: 152, baseType: !500, size: 64, align: 64, offset: 1664)
!1583 = !DIDerivedType(tag: DW_TAG_member, name: "newport", scope: !1538, file: !135, line: 153, baseType: !657, size: 16, align: 16, offset: 1728)
!1584 = !DIDerivedType(tag: DW_TAG_member, name: "httpc", scope: !1535, file: !121, line: 1105, baseType: !1585, size: 32, align: 32)
!1585 = !DICompositeType(tag: DW_TAG_structure_type, name: "http_conn", file: !1586, line: 200, size: 32, align: 32, elements: !1587)
!1586 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1587 = !{!1588}
!1588 = !DIDerivedType(tag: DW_TAG_member, name: "unused", scope: !1585, file: !1586, line: 227, baseType: !316, size: 32, align: 32)
!1589 = !DIDerivedType(tag: DW_TAG_member, name: "sshc", scope: !1535, file: !121, line: 1106, baseType: !1590, size: 64, align: 64)
!1590 = !DICompositeType(tag: DW_TAG_structure_type, name: "ssh_conn", file: !1591, line: 110, size: 64, align: 64, elements: !1592)
!1591 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/ssh.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1592 = !{!1593}
!1593 = !DIDerivedType(tag: DW_TAG_member, name: "authlist", scope: !1590, file: !1591, line: 111, baseType: !527, size: 64, align: 64)
!1594 = !DIDerivedType(tag: DW_TAG_member, name: "tftpc", scope: !1535, file: !121, line: 1107, baseType: !1595, size: 64, align: 64)
!1595 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1596, size: 64, align: 64)
!1596 = !DICompositeType(tag: DW_TAG_structure_type, name: "tftp_state_data", file: !121, line: 1107, flags: DIFlagFwdDecl)
!1597 = !DIDerivedType(tag: DW_TAG_member, name: "imapc", scope: !1535, file: !121, line: 1108, baseType: !1598, size: 1472, align: 64)
!1598 = !DICompositeType(tag: DW_TAG_structure_type, name: "imap_conn", file: !174, line: 70, size: 1472, align: 64, elements: !1599)
!1599 = !{!1600, !1601, !1603, !1604, !1636, !1637, !1638, !1640, !1641, !1642, !1643, !1644}
!1600 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1598, file: !174, line: 71, baseType: !1541, size: 896, align: 64)
!1601 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1598, file: !174, line: 72, baseType: !1602, size: 32, align: 32, offset: 896)
!1602 = !DIDerivedType(tag: DW_TAG_typedef, name: "imapstate", file: !174, line: 50, baseType: !173)
!1603 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1598, file: !174, line: 73, baseType: !423, size: 8, align: 8, offset: 928)
!1604 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1598, file: !174, line: 74, baseType: !1605, size: 256, align: 64, offset: 960)
!1605 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASL", file: !193, line: 101, size: 256, align: 64, elements: !1606)
!1606 = !{!1607, !1628, !1630, !1631, !1632, !1633, !1634, !1635}
!1607 = !DIDerivedType(tag: DW_TAG_member, name: "params", scope: !1605, file: !193, line: 102, baseType: !1608, size: 64, align: 64)
!1608 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1609, size: 64, align: 64)
!1609 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1610)
!1610 = !DICompositeType(tag: DW_TAG_structure_type, name: "SASLproto", file: !193, line: 86, size: 384, align: 64, elements: !1611)
!1611 = !{!1612, !1613, !1614, !1615, !1616, !1620, !1624}
!1612 = !DIDerivedType(tag: DW_TAG_member, name: "service", scope: !1610, file: !193, line: 87, baseType: !527, size: 64, align: 64)
!1613 = !DIDerivedType(tag: DW_TAG_member, name: "contcode", scope: !1610, file: !193, line: 88, baseType: !316, size: 32, align: 32, offset: 64)
!1614 = !DIDerivedType(tag: DW_TAG_member, name: "finalcode", scope: !1610, file: !193, line: 89, baseType: !316, size: 32, align: 32, offset: 96)
!1615 = !DIDerivedType(tag: DW_TAG_member, name: "maxirlen", scope: !1610, file: !193, line: 90, baseType: !347, size: 64, align: 64, offset: 128)
!1616 = !DIDerivedType(tag: DW_TAG_member, name: "sendauth", scope: !1610, file: !193, line: 91, baseType: !1617, size: 64, align: 64, offset: 192)
!1617 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1618, size: 64, align: 64)
!1618 = !DISubroutineType(types: !1619)
!1619 = !{!289, !262, !527, !527}
!1620 = !DIDerivedType(tag: DW_TAG_member, name: "sendcont", scope: !1610, file: !193, line: 94, baseType: !1621, size: 64, align: 64, offset: 256)
!1621 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1622, size: 64, align: 64)
!1622 = !DISubroutineType(types: !1623)
!1623 = !{!289, !262, !527}
!1624 = !DIDerivedType(tag: DW_TAG_member, name: "getmessage", scope: !1610, file: !193, line: 96, baseType: !1625, size: 64, align: 64, offset: 320)
!1625 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1626, size: 64, align: 64)
!1626 = !DISubroutineType(types: !1627)
!1627 = !{null, !500, !1562}
!1628 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1605, file: !193, line: 103, baseType: !1629, size: 32, align: 32, offset: 64)
!1629 = !DIDerivedType(tag: DW_TAG_typedef, name: "saslstate", file: !193, line: 76, baseType: !192)
!1630 = !DIDerivedType(tag: DW_TAG_member, name: "authmechs", scope: !1605, file: !193, line: 104, baseType: !457, size: 32, align: 32, offset: 96)
!1631 = !DIDerivedType(tag: DW_TAG_member, name: "prefmech", scope: !1605, file: !193, line: 105, baseType: !457, size: 32, align: 32, offset: 128)
!1632 = !DIDerivedType(tag: DW_TAG_member, name: "authused", scope: !1605, file: !193, line: 106, baseType: !457, size: 32, align: 32, offset: 160)
!1633 = !DIDerivedType(tag: DW_TAG_member, name: "resetprefs", scope: !1605, file: !193, line: 107, baseType: !423, size: 8, align: 8, offset: 192)
!1634 = !DIDerivedType(tag: DW_TAG_member, name: "mutual_auth", scope: !1605, file: !193, line: 108, baseType: !423, size: 8, align: 8, offset: 200)
!1635 = !DIDerivedType(tag: DW_TAG_member, name: "force_ir", scope: !1605, file: !193, line: 109, baseType: !423, size: 8, align: 8, offset: 208)
!1636 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1598, file: !174, line: 75, baseType: !457, size: 32, align: 32, offset: 1216)
!1637 = !DIDerivedType(tag: DW_TAG_member, name: "cmdid", scope: !1598, file: !174, line: 76, baseType: !316, size: 32, align: 32, offset: 1248)
!1638 = !DIDerivedType(tag: DW_TAG_member, name: "resptag", scope: !1598, file: !174, line: 77, baseType: !1639, size: 40, align: 8, offset: 1280)
!1639 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 40, align: 8, elements: !317)
!1640 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1598, file: !174, line: 78, baseType: !423, size: 8, align: 8, offset: 1320)
!1641 = !DIDerivedType(tag: DW_TAG_member, name: "login_disabled", scope: !1598, file: !174, line: 79, baseType: !423, size: 8, align: 8, offset: 1328)
!1642 = !DIDerivedType(tag: DW_TAG_member, name: "ir_supported", scope: !1598, file: !174, line: 80, baseType: !423, size: 8, align: 8, offset: 1336)
!1643 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox", scope: !1598, file: !174, line: 81, baseType: !500, size: 64, align: 64, offset: 1344)
!1644 = !DIDerivedType(tag: DW_TAG_member, name: "mailbox_uidvalidity", scope: !1598, file: !174, line: 82, baseType: !500, size: 64, align: 64, offset: 1408)
!1645 = !DIDerivedType(tag: DW_TAG_member, name: "pop3c", scope: !1535, file: !121, line: 1109, baseType: !1646, size: 1536, align: 64)
!1646 = !DICompositeType(tag: DW_TAG_structure_type, name: "pop3_conn", file: !213, line: 60, size: 1536, align: 64, elements: !1647)
!1647 = !{!1648, !1649, !1651, !1652, !1653, !1654, !1655, !1656, !1657, !1658}
!1648 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1646, file: !213, line: 61, baseType: !1541, size: 896, align: 64)
!1649 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1646, file: !213, line: 62, baseType: !1650, size: 32, align: 32, offset: 896)
!1650 = !DIDerivedType(tag: DW_TAG_typedef, name: "pop3state", file: !213, line: 46, baseType: !212)
!1651 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1646, file: !213, line: 63, baseType: !423, size: 8, align: 8, offset: 928)
!1652 = !DIDerivedType(tag: DW_TAG_member, name: "eob", scope: !1646, file: !213, line: 64, baseType: !347, size: 64, align: 64, offset: 960)
!1653 = !DIDerivedType(tag: DW_TAG_member, name: "strip", scope: !1646, file: !213, line: 66, baseType: !347, size: 64, align: 64, offset: 1024)
!1654 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1646, file: !213, line: 68, baseType: !1605, size: 256, align: 64, offset: 1088)
!1655 = !DIDerivedType(tag: DW_TAG_member, name: "authtypes", scope: !1646, file: !213, line: 69, baseType: !457, size: 32, align: 32, offset: 1344)
!1656 = !DIDerivedType(tag: DW_TAG_member, name: "preftype", scope: !1646, file: !213, line: 70, baseType: !457, size: 32, align: 32, offset: 1376)
!1657 = !DIDerivedType(tag: DW_TAG_member, name: "apoptimestamp", scope: !1646, file: !213, line: 71, baseType: !500, size: 64, align: 64, offset: 1408)
!1658 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1646, file: !213, line: 72, baseType: !423, size: 8, align: 8, offset: 1472)
!1659 = !DIDerivedType(tag: DW_TAG_member, name: "smtpc", scope: !1535, file: !121, line: 1110, baseType: !1660, size: 1344, align: 64)
!1660 = !DICompositeType(tag: DW_TAG_structure_type, name: "smtp_conn", file: !228, line: 65, size: 1344, align: 64, elements: !1661)
!1661 = !{!1662, !1663, !1665, !1666, !1667, !1668, !1669, !1670}
!1662 = !DIDerivedType(tag: DW_TAG_member, name: "pp", scope: !1660, file: !228, line: 66, baseType: !1541, size: 896, align: 64)
!1663 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1660, file: !228, line: 67, baseType: !1664, size: 32, align: 32, offset: 896)
!1664 = !DIDerivedType(tag: DW_TAG_typedef, name: "smtpstate", file: !228, line: 48, baseType: !227)
!1665 = !DIDerivedType(tag: DW_TAG_member, name: "ssldone", scope: !1660, file: !228, line: 68, baseType: !423, size: 8, align: 8, offset: 928)
!1666 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1660, file: !228, line: 69, baseType: !500, size: 64, align: 64, offset: 960)
!1667 = !DIDerivedType(tag: DW_TAG_member, name: "sasl", scope: !1660, file: !228, line: 70, baseType: !1605, size: 256, align: 64, offset: 1024)
!1668 = !DIDerivedType(tag: DW_TAG_member, name: "tls_supported", scope: !1660, file: !228, line: 71, baseType: !423, size: 8, align: 8, offset: 1280)
!1669 = !DIDerivedType(tag: DW_TAG_member, name: "size_supported", scope: !1660, file: !228, line: 72, baseType: !423, size: 8, align: 8, offset: 1288)
!1670 = !DIDerivedType(tag: DW_TAG_member, name: "auth_supported", scope: !1660, file: !228, line: 74, baseType: !423, size: 8, align: 8, offset: 1296)
!1671 = !DIDerivedType(tag: DW_TAG_member, name: "rtspc", scope: !1535, file: !121, line: 1111, baseType: !1672, size: 192, align: 64)
!1672 = !DICompositeType(tag: DW_TAG_structure_type, name: "rtsp_conn", file: !1673, line: 43, size: 192, align: 64, elements: !1674)
!1673 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/rtsp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1674 = !{!1675, !1676, !1677}
!1675 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_buf", scope: !1672, file: !1673, line: 44, baseType: !500, size: 64, align: 64)
!1676 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_bufsize", scope: !1672, file: !1673, line: 45, baseType: !612, size: 64, align: 64, offset: 64)
!1677 = !DIDerivedType(tag: DW_TAG_member, name: "rtp_channel", scope: !1672, file: !1673, line: 46, baseType: !316, size: 32, align: 32, offset: 128)
!1678 = !DIDerivedType(tag: DW_TAG_member, name: "smbc", scope: !1535, file: !121, line: 1112, baseType: !1679, size: 640, align: 64)
!1679 = !DICompositeType(tag: DW_TAG_structure_type, name: "smb_conn", file: !245, line: 33, size: 640, align: 64, elements: !1680)
!1680 = !{!1681, !1682, !1683, !1684, !1689, !1690, !1691, !1692, !1693, !1694, !1695}
!1681 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1679, file: !245, line: 34, baseType: !244, size: 32, align: 32)
!1682 = !DIDerivedType(tag: DW_TAG_member, name: "user", scope: !1679, file: !245, line: 35, baseType: !500, size: 64, align: 64, offset: 64)
!1683 = !DIDerivedType(tag: DW_TAG_member, name: "domain", scope: !1679, file: !245, line: 36, baseType: !500, size: 64, align: 64, offset: 128)
!1684 = !DIDerivedType(tag: DW_TAG_member, name: "challenge", scope: !1679, file: !245, line: 37, baseType: !1685, size: 64, align: 8, offset: 192)
!1685 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1686, size: 64, align: 8, elements: !1687)
!1686 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!1687 = !{!1688}
!1688 = !DISubrange(count: 8)
!1689 = !DIDerivedType(tag: DW_TAG_member, name: "session_key", scope: !1679, file: !245, line: 38, baseType: !457, size: 32, align: 32, offset: 256)
!1690 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !1679, file: !245, line: 39, baseType: !657, size: 16, align: 16, offset: 288)
!1691 = !DIDerivedType(tag: DW_TAG_member, name: "recv_buf", scope: !1679, file: !245, line: 40, baseType: !500, size: 64, align: 64, offset: 320)
!1692 = !DIDerivedType(tag: DW_TAG_member, name: "upload_size", scope: !1679, file: !245, line: 41, baseType: !347, size: 64, align: 64, offset: 384)
!1693 = !DIDerivedType(tag: DW_TAG_member, name: "send_size", scope: !1679, file: !245, line: 42, baseType: !347, size: 64, align: 64, offset: 448)
!1694 = !DIDerivedType(tag: DW_TAG_member, name: "sent", scope: !1679, file: !245, line: 43, baseType: !347, size: 64, align: 64, offset: 512)
!1695 = !DIDerivedType(tag: DW_TAG_member, name: "got", scope: !1679, file: !245, line: 44, baseType: !347, size: 64, align: 64, offset: 576)
!1696 = !DIDerivedType(tag: DW_TAG_member, name: "generic", scope: !1535, file: !121, line: 1113, baseType: !311, size: 64, align: 64)
!1697 = !DIDerivedType(tag: DW_TAG_member, name: "cselect_bits", scope: !253, file: !121, line: 1116, baseType: !316, size: 32, align: 32, offset: 13056)
!1698 = !DIDerivedType(tag: DW_TAG_member, name: "waitfor", scope: !253, file: !121, line: 1117, baseType: !316, size: 32, align: 32, offset: 13088)
!1699 = !DIDerivedType(tag: DW_TAG_member, name: "localdev", scope: !253, file: !121, line: 1128, baseType: !500, size: 64, align: 64, offset: 13120)
!1700 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !253, file: !121, line: 1129, baseType: !657, size: 16, align: 16, offset: 13184)
!1701 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !253, file: !121, line: 1130, baseType: !316, size: 32, align: 32, offset: 13216)
!1702 = !DIDerivedType(tag: DW_TAG_member, name: "tunnel_state", scope: !253, file: !121, line: 1137, baseType: !1703, size: 64, align: 32, offset: 13248)
!1703 = !DICompositeType(tag: DW_TAG_array_type, baseType: !252, size: 64, align: 32, elements: !1338)
!1704 = !DIDerivedType(tag: DW_TAG_member, name: "bundle", scope: !253, file: !121, line: 1138, baseType: !1705, size: 64, align: 64, offset: 13312)
!1705 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1706, size: 64, align: 64)
!1706 = !DICompositeType(tag: DW_TAG_structure_type, name: "connectbundle", file: !426, line: 38, size: 384, align: 64, elements: !1707)
!1707 = !{!1708, !1709, !1710}
!1708 = !DIDerivedType(tag: DW_TAG_member, name: "multiuse", scope: !1706, file: !426, line: 39, baseType: !316, size: 32, align: 32)
!1709 = !DIDerivedType(tag: DW_TAG_member, name: "num_connections", scope: !1706, file: !426, line: 40, baseType: !347, size: 64, align: 64, offset: 64)
!1710 = !DIDerivedType(tag: DW_TAG_member, name: "conn_list", scope: !1706, file: !426, line: 41, baseType: !330, size: 256, align: 64, offset: 128)
!1711 = !DIDerivedType(tag: DW_TAG_member, name: "negnpn", scope: !253, file: !121, line: 1140, baseType: !316, size: 32, align: 32, offset: 13376)
!1712 = !{!1713, !1714, !1715}
!1713 = !DIEnumerator(name: "TUNNEL_INIT", value: 0)
!1714 = !DIEnumerator(name: "TUNNEL_CONNECT", value: 1)
!1715 = !DIEnumerator(name: "TUNNEL_COMPLETE", value: 2)
!1716 = !{!1046, !311, !457, !1717, !1310, !501, !316, !1686}
!1717 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1718, size: 64, align: 64)
!1718 = !DICompositeType(tag: DW_TAG_structure_type, name: "hostcache_prune_data", file: !1, line: 214, size: 128, align: 64, elements: !1719)
!1719 = !{!1720, !1721}
!1720 = !DIDerivedType(tag: DW_TAG_member, name: "cache_timeout", scope: !1718, file: !1, line: 215, baseType: !379, size: 64, align: 64)
!1721 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !1718, file: !1, line: 216, baseType: !599, size: 64, align: 64, offset: 64)
!1722 = !{!1723, !1727, !1730, !1735, !1738, !1741, !1744, !1747, !1751, !1754, !1757, !1760, !1763, !1766, !1769, !1772, !1773, !1776, !1777}
!1723 = distinct !DISubprogram(name: "Curl_global_host_cache_init", scope: !1, file: !1, line: 122, type: !1724, isLocal: false, isDefinition: true, scopeLine: 123, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1724 = !DISubroutineType(types: !1725)
!1725 = !{!324}
!1726 = !{}
!1727 = distinct !DISubprogram(name: "Curl_global_host_cache_dtor", scope: !1, file: !1, line: 137, type: !1728, isLocal: false, isDefinition: true, scopeLine: 138, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1728 = !DISubroutineType(types: !1729)
!1729 = !{null}
!1730 = distinct !DISubprogram(name: "Curl_num_addresses", scope: !1, file: !1, line: 148, type: !1731, isLocal: false, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1731 = !DISubroutineType(types: !1732)
!1732 = !{!316, !1733}
!1733 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1734, size: 64, align: 64)
!1734 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1316)
!1735 = distinct !DISubprogram(name: "Curl_printable_address", scope: !1, file: !1, line: 166, type: !1736, isLocal: false, isDefinition: true, scopeLine: 167, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1736 = !DISubroutineType(types: !1737)
!1737 = !{!527, !1733, !500, !347}
!1738 = distinct !DISubprogram(name: "Curl_hostcache_prune", scope: !1, file: !1, line: 257, type: !1739, isLocal: false, isDefinition: true, scopeLine: 258, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1739 = !DISubroutineType(types: !1740)
!1740 = !{null, !256}
!1741 = distinct !DISubprogram(name: "Curl_fetch_addr", scope: !1, file: !1, line: 344, type: !1742, isLocal: false, isDefinition: true, scopeLine: 347, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1742 = !DISubroutineType(types: !1743)
!1743 = !{!1310, !262, !527, !316}
!1744 = distinct !DISubprogram(name: "Curl_cache_addr", scope: !1, file: !1, line: 375, type: !1745, isLocal: false, isDefinition: true, scopeLine: 379, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1745 = !DISubroutineType(types: !1746)
!1746 = !{!1310, !256, !1315, !527, !316}
!1747 = distinct !DISubprogram(name: "Curl_resolv", scope: !1, file: !1, line: 444, type: !1748, isLocal: false, isDefinition: true, scopeLine: 448, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1748 = !DISubroutineType(types: !1749)
!1749 = !{!316, !262, !527, !316, !1750}
!1750 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1310, size: 64, align: 64)
!1751 = distinct !DISubprogram(name: "Curl_resolv_timeout", scope: !1, file: !1, line: 567, type: !1752, isLocal: false, isDefinition: true, scopeLine: 572, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1752 = !DISubroutineType(types: !1753)
!1753 = !{!316, !262, !527, !316, !1750, !599}
!1754 = distinct !DISubprogram(name: "Curl_resolv_unlock", scope: !1, file: !1, line: 722, type: !1755, isLocal: false, isDefinition: true, scopeLine: 723, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1755 = !DISubroutineType(types: !1756)
!1756 = !{null, !256, !1310}
!1757 = distinct !DISubprogram(name: "Curl_mk_dnscache", scope: !1, file: !1, line: 751, type: !1758, isLocal: false, isDefinition: true, scopeLine: 752, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1758 = !DISubroutineType(types: !1759)
!1759 = !{!316, !324}
!1760 = distinct !DISubprogram(name: "Curl_hostcache_clean", scope: !1, file: !1, line: 764, type: !1761, isLocal: false, isDefinition: true, scopeLine: 766, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1761 = !DISubroutineType(types: !1762)
!1762 = !{null, !256, !324}
!1763 = distinct !DISubprogram(name: "Curl_loadhostpairs", scope: !1, file: !1, line: 777, type: !1764, isLocal: false, isDefinition: true, scopeLine: 778, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1764 = !DISubroutineType(types: !1765)
!1765 = !{!289, !256}
!1766 = distinct !DISubprogram(name: "hostcache_prune", scope: !1, file: !1, line: 241, type: !1767, isLocal: true, isDefinition: true, scopeLine: 242, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1767 = !DISubroutineType(types: !1768)
!1768 = !{null, !324, !379, !599}
!1769 = distinct !DISubprogram(name: "hostcache_timestamp_remove", scope: !1, file: !1, line: 227, type: !1770, isLocal: true, isDefinition: true, scopeLine: 228, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1770 = !DISubroutineType(types: !1771)
!1771 = !{!316, !311, !311}
!1772 = distinct !DISubprogram(name: "fetch_addr", scope: !1, file: !1, line: 289, type: !1742, isLocal: true, isDefinition: true, scopeLine: 292, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1773 = distinct !DISubprogram(name: "create_hostcache_id", scope: !1, file: !1, line: 199, type: !1774, isLocal: true, isDefinition: true, scopeLine: 200, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1774 = !DISubroutineType(types: !1775)
!1775 = !{!500, !527, !316}
!1776 = distinct !DISubprogram(name: "alarmfunc", scope: !1, file: !1, line: 536, type: !1163, isLocal: true, isDefinition: true, scopeLine: 537, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1777 = distinct !DISubprogram(name: "freednsentry", scope: !1, file: !1, line: 736, type: !363, isLocal: true, isDefinition: true, scopeLine: 737, flags: DIFlagPrototyped, isOptimized: false, variables: !1726)
!1778 = !{!1779, !1780, !1781}
!1779 = !DIGlobalVariable(name: "hostname_cache", scope: !0, file: !1, line: 110, type: !325, isLocal: true, isDefinition: true, variable: %struct.curl_hash* @hostname_cache)
!1780 = !DIGlobalVariable(name: "host_cache_initialized", scope: !0, file: !1, line: 111, type: !316, isLocal: true, isDefinition: true, variable: i32* @host_cache_initialized)
!1781 = !DIGlobalVariable(name: "curl_jmpenv", scope: !0, file: !1, line: 284, type: !1782, isLocal: false, isDefinition: true, variable: [1 x %struct.__jmp_buf_tag]* @curl_jmpenv)
!1782 = !DIDerivedType(tag: DW_TAG_typedef, name: "sigjmp_buf", file: !1783, line: 92, baseType: !1784)
!1783 = !DIFile(filename: "/usr/include/setjmp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1784 = !DICompositeType(tag: DW_TAG_array_type, baseType: !1785, size: 1600, align: 64, elements: !662)
!1785 = !DICompositeType(tag: DW_TAG_structure_type, name: "__jmp_buf_tag", file: !1783, line: 34, size: 1600, align: 64, elements: !1786)
!1786 = !{!1787, !1791, !1792}
!1787 = !DIDerivedType(tag: DW_TAG_member, name: "__jmpbuf", scope: !1785, file: !1783, line: 40, baseType: !1788, size: 512, align: 64)
!1788 = !DIDerivedType(tag: DW_TAG_typedef, name: "__jmp_buf", file: !1789, line: 31, baseType: !1790)
!1789 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/setjmp.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1790 = !DICompositeType(tag: DW_TAG_array_type, baseType: !379, size: 512, align: 64, elements: !1687)
!1791 = !DIDerivedType(tag: DW_TAG_member, name: "__mask_was_saved", scope: !1785, file: !1783, line: 41, baseType: !316, size: 32, align: 32, offset: 512)
!1792 = !DIDerivedType(tag: DW_TAG_member, name: "__saved_mask", scope: !1785, file: !1783, line: 42, baseType: !1793, size: 1024, align: 64, offset: 576)
!1793 = !DIDerivedType(tag: DW_TAG_typedef, name: "__sigset_t", file: !1794, line: 30, baseType: !1795)
!1794 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sigset.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1795 = !DICompositeType(tag: DW_TAG_structure_type, file: !1794, line: 27, size: 1024, align: 64, elements: !1796)
!1796 = !{!1797}
!1797 = !DIDerivedType(tag: DW_TAG_member, name: "__val", scope: !1795, file: !1794, line: 29, baseType: !1798, size: 1024, align: 64)
!1798 = !DICompositeType(tag: DW_TAG_array_type, baseType: !349, size: 1024, align: 64, elements: !1799)
!1799 = !{!1800}
!1800 = !DISubrange(count: 16)
!1801 = !{i32 2, !"Dwarf Version", i32 4}
!1802 = !{i32 2, !"Debug Info Version", i32 3}
!1803 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!1804 = !DILocalVariable(name: "rc", scope: !1723, file: !1, line: 124, type: !316)
!1805 = !DIExpression()
!1806 = !DILocation(line: 124, column: 7, scope: !1723)
!1807 = !DILocation(line: 125, column: 7, scope: !1808)
!1808 = distinct !DILexicalBlock(scope: !1723, file: !1, line: 125, column: 6)
!1809 = !DILocation(line: 125, column: 6, scope: !1723)
!1810 = !DILocation(line: 126, column: 10, scope: !1811)
!1811 = distinct !DILexicalBlock(scope: !1808, file: !1, line: 125, column: 31)
!1812 = !DILocation(line: 126, column: 8, scope: !1811)
!1813 = !DILocation(line: 128, column: 9, scope: !1814)
!1814 = distinct !DILexicalBlock(scope: !1811, file: !1, line: 128, column: 8)
!1815 = !DILocation(line: 128, column: 8, scope: !1811)
!1816 = !DILocation(line: 129, column: 30, scope: !1814)
!1817 = !DILocation(line: 129, column: 7, scope: !1814)
!1818 = !DILocation(line: 130, column: 3, scope: !1811)
!1819 = !DILocation(line: 131, column: 10, scope: !1723)
!1820 = !DILocation(line: 131, column: 3, scope: !1723)
!1821 = !DILocalVariable(name: "freethis", arg: 1, scope: !1777, file: !1, line: 736, type: !311)
!1822 = !DILocation(line: 736, column: 32, scope: !1777)
!1823 = !DILocalVariable(name: "dns", scope: !1777, file: !1, line: 738, type: !1310)
!1824 = !DILocation(line: 738, column: 26, scope: !1777)
!1825 = !DILocation(line: 738, column: 58, scope: !1777)
!1826 = !DILocation(line: 738, column: 32, scope: !1777)
!1827 = !DILocation(line: 739, column: 3, scope: !1777)
!1828 = !DILocation(line: 739, column: 3, scope: !1829)
!1829 = !DILexicalBlockFile(scope: !1830, file: !1, discriminator: 1)
!1830 = distinct !DILexicalBlock(scope: !1777, file: !1, line: 739, column: 3)
!1831 = !DILocation(line: 741, column: 3, scope: !1777)
!1832 = !DILocation(line: 741, column: 8, scope: !1777)
!1833 = !DILocation(line: 741, column: 13, scope: !1777)
!1834 = !DILocation(line: 742, column: 6, scope: !1835)
!1835 = distinct !DILexicalBlock(scope: !1777, file: !1, line: 742, column: 6)
!1836 = !DILocation(line: 742, column: 11, scope: !1835)
!1837 = !DILocation(line: 742, column: 17, scope: !1835)
!1838 = !DILocation(line: 742, column: 6, scope: !1777)
!1839 = !DILocation(line: 743, column: 23, scope: !1840)
!1840 = distinct !DILexicalBlock(scope: !1835, file: !1, line: 742, column: 23)
!1841 = !DILocation(line: 743, column: 28, scope: !1840)
!1842 = !DILocation(line: 743, column: 5, scope: !1840)
!1843 = !DILocation(line: 744, column: 5, scope: !1840)
!1844 = !DILocation(line: 745, column: 3, scope: !1840)
!1845 = !DILocation(line: 746, column: 1, scope: !1777)
!1846 = !DILocation(line: 139, column: 6, scope: !1847)
!1847 = distinct !DILexicalBlock(scope: !1727, file: !1, line: 139, column: 6)
!1848 = !DILocation(line: 139, column: 6, scope: !1727)
!1849 = !DILocation(line: 140, column: 5, scope: !1850)
!1850 = distinct !DILexicalBlock(scope: !1847, file: !1, line: 139, column: 30)
!1851 = !DILocation(line: 141, column: 28, scope: !1850)
!1852 = !DILocation(line: 142, column: 3, scope: !1850)
!1853 = !DILocation(line: 143, column: 1, scope: !1727)
!1854 = !DILocalVariable(name: "addr", arg: 1, scope: !1730, file: !1, line: 148, type: !1733)
!1855 = !DILocation(line: 148, column: 45, scope: !1730)
!1856 = !DILocalVariable(name: "i", scope: !1730, file: !1, line: 150, type: !316)
!1857 = !DILocation(line: 150, column: 7, scope: !1730)
!1858 = !DILocation(line: 151, column: 3, scope: !1730)
!1859 = !DILocation(line: 151, column: 9, scope: !1860)
!1860 = !DILexicalBlockFile(scope: !1730, file: !1, discriminator: 1)
!1861 = !DILocation(line: 151, column: 3, scope: !1860)
!1862 = !DILocation(line: 152, column: 12, scope: !1863)
!1863 = distinct !DILexicalBlock(scope: !1730, file: !1, line: 151, column: 15)
!1864 = !DILocation(line: 152, column: 18, scope: !1863)
!1865 = !DILocation(line: 152, column: 10, scope: !1863)
!1866 = !DILocation(line: 153, column: 6, scope: !1863)
!1867 = !DILocation(line: 151, column: 3, scope: !1868)
!1868 = !DILexicalBlockFile(scope: !1730, file: !1, discriminator: 2)
!1869 = !DILocation(line: 155, column: 10, scope: !1730)
!1870 = !DILocation(line: 155, column: 3, scope: !1730)
!1871 = !DILocalVariable(name: "ai", arg: 1, scope: !1735, file: !1, line: 166, type: !1733)
!1872 = !DILocation(line: 166, column: 45, scope: !1735)
!1873 = !DILocalVariable(name: "buf", arg: 2, scope: !1735, file: !1, line: 166, type: !500)
!1874 = !DILocation(line: 166, column: 55, scope: !1735)
!1875 = !DILocalVariable(name: "bufsize", arg: 3, scope: !1735, file: !1, line: 166, type: !347)
!1876 = !DILocation(line: 166, column: 67, scope: !1735)
!1877 = !DILocalVariable(name: "sa4", scope: !1735, file: !1, line: 168, type: !1878)
!1878 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1879, size: 64, align: 64)
!1879 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1880)
!1880 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in", file: !1881, line: 237, size: 128, align: 32, elements: !1882)
!1881 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1882 = !{!1883, !1884, !1888, !1894}
!1883 = !DIDerivedType(tag: DW_TAG_member, name: "sin_family", scope: !1880, file: !1881, line: 239, baseType: !781, size: 16, align: 16)
!1884 = !DIDerivedType(tag: DW_TAG_member, name: "sin_port", scope: !1880, file: !1881, line: 240, baseType: !1885, size: 16, align: 16, offset: 16)
!1885 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_port_t", file: !1881, line: 117, baseType: !1886)
!1886 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !1887, line: 49, baseType: !657)
!1887 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!1888 = !DIDerivedType(tag: DW_TAG_member, name: "sin_addr", scope: !1880, file: !1881, line: 241, baseType: !1889, size: 32, align: 32, offset: 32)
!1889 = !DICompositeType(tag: DW_TAG_structure_type, name: "in_addr", file: !1881, line: 31, size: 32, align: 32, elements: !1890)
!1890 = !{!1891}
!1891 = !DIDerivedType(tag: DW_TAG_member, name: "s_addr", scope: !1889, file: !1881, line: 33, baseType: !1892, size: 32, align: 32)
!1892 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_addr_t", file: !1881, line: 30, baseType: !1893)
!1893 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !1887, line: 51, baseType: !457)
!1894 = !DIDerivedType(tag: DW_TAG_member, name: "sin_zero", scope: !1880, file: !1881, line: 244, baseType: !1685, size: 64, align: 8, offset: 64)
!1895 = !DILocation(line: 168, column: 29, scope: !1735)
!1896 = !DILocalVariable(name: "ipaddr4", scope: !1735, file: !1, line: 169, type: !1897)
!1897 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1898, size: 64, align: 64)
!1898 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !1889)
!1899 = !DILocation(line: 169, column: 25, scope: !1735)
!1900 = !DILocation(line: 175, column: 10, scope: !1735)
!1901 = !DILocation(line: 175, column: 14, scope: !1735)
!1902 = !DILocation(line: 175, column: 3, scope: !1735)
!1903 = !DILocation(line: 177, column: 27, scope: !1904)
!1904 = distinct !DILexicalBlock(scope: !1735, file: !1, line: 175, column: 25)
!1905 = !DILocation(line: 177, column: 31, scope: !1904)
!1906 = !DILocation(line: 177, column: 13, scope: !1904)
!1907 = !DILocation(line: 177, column: 11, scope: !1904)
!1908 = !DILocation(line: 178, column: 18, scope: !1904)
!1909 = !DILocation(line: 178, column: 23, scope: !1904)
!1910 = !DILocation(line: 178, column: 15, scope: !1904)
!1911 = !DILocation(line: 179, column: 29, scope: !1904)
!1912 = !DILocation(line: 179, column: 33, scope: !1904)
!1913 = !DILocation(line: 179, column: 58, scope: !1904)
!1914 = !DILocation(line: 179, column: 44, scope: !1904)
!1915 = !DILocation(line: 179, column: 67, scope: !1904)
!1916 = !DILocation(line: 180, column: 29, scope: !1904)
!1917 = !DILocation(line: 179, column: 14, scope: !1904)
!1918 = !DILocation(line: 179, column: 7, scope: !1904)
!1919 = !DILocation(line: 189, column: 7, scope: !1904)
!1920 = !DILocation(line: 191, column: 3, scope: !1735)
!1921 = !DILocation(line: 192, column: 1, scope: !1735)
!1922 = !DILocalVariable(name: "data", arg: 1, scope: !1738, file: !1, line: 257, type: !256)
!1923 = !DILocation(line: 257, column: 45, scope: !1738)
!1924 = !DILocalVariable(name: "now", scope: !1738, file: !1, line: 259, type: !599)
!1925 = !DILocation(line: 259, column: 10, scope: !1738)
!1926 = !DILocation(line: 261, column: 7, scope: !1927)
!1927 = distinct !DILexicalBlock(scope: !1738, file: !1, line: 261, column: 6)
!1928 = !DILocation(line: 261, column: 13, scope: !1927)
!1929 = !DILocation(line: 261, column: 17, scope: !1927)
!1930 = !DILocation(line: 261, column: 35, scope: !1927)
!1931 = !DILocation(line: 261, column: 42, scope: !1927)
!1932 = !DILocation(line: 261, column: 46, scope: !1933)
!1933 = !DILexicalBlockFile(scope: !1927, file: !1, discriminator: 1)
!1934 = !DILocation(line: 261, column: 52, scope: !1933)
!1935 = !DILocation(line: 261, column: 56, scope: !1933)
!1936 = !DILocation(line: 261, column: 6, scope: !1933)
!1937 = !DILocation(line: 264, column: 5, scope: !1927)
!1938 = !DILocation(line: 266, column: 6, scope: !1939)
!1939 = distinct !DILexicalBlock(scope: !1738, file: !1, line: 266, column: 6)
!1940 = !DILocation(line: 266, column: 12, scope: !1939)
!1941 = !DILocation(line: 266, column: 6, scope: !1738)
!1942 = !DILocation(line: 267, column: 21, scope: !1939)
!1943 = !DILocation(line: 267, column: 5, scope: !1939)
!1944 = !DILocation(line: 269, column: 3, scope: !1738)
!1945 = !DILocation(line: 272, column: 19, scope: !1738)
!1946 = !DILocation(line: 272, column: 25, scope: !1738)
!1947 = !DILocation(line: 272, column: 29, scope: !1738)
!1948 = !DILocation(line: 273, column: 19, scope: !1738)
!1949 = !DILocation(line: 273, column: 25, scope: !1738)
!1950 = !DILocation(line: 273, column: 29, scope: !1738)
!1951 = !DILocation(line: 274, column: 19, scope: !1738)
!1952 = !DILocation(line: 272, column: 3, scope: !1738)
!1953 = !DILocation(line: 276, column: 6, scope: !1954)
!1954 = distinct !DILexicalBlock(scope: !1738, file: !1, line: 276, column: 6)
!1955 = !DILocation(line: 276, column: 12, scope: !1954)
!1956 = !DILocation(line: 276, column: 6, scope: !1738)
!1957 = !DILocation(line: 277, column: 23, scope: !1954)
!1958 = !DILocation(line: 277, column: 5, scope: !1954)
!1959 = !DILocation(line: 278, column: 1, scope: !1738)
!1960 = !DILocalVariable(name: "hostcache", arg: 1, scope: !1766, file: !1, line: 241, type: !324)
!1961 = !DILocation(line: 241, column: 35, scope: !1766)
!1962 = !DILocalVariable(name: "cache_timeout", arg: 2, scope: !1766, file: !1, line: 241, type: !379)
!1963 = !DILocation(line: 241, column: 51, scope: !1766)
!1964 = !DILocalVariable(name: "now", arg: 3, scope: !1766, file: !1, line: 241, type: !599)
!1965 = !DILocation(line: 241, column: 73, scope: !1766)
!1966 = !DILocalVariable(name: "user", scope: !1766, file: !1, line: 243, type: !1718)
!1967 = !DILocation(line: 243, column: 31, scope: !1766)
!1968 = !DILocation(line: 245, column: 24, scope: !1766)
!1969 = !DILocation(line: 245, column: 8, scope: !1766)
!1970 = !DILocation(line: 245, column: 22, scope: !1766)
!1971 = !DILocation(line: 246, column: 14, scope: !1766)
!1972 = !DILocation(line: 246, column: 8, scope: !1766)
!1973 = !DILocation(line: 246, column: 12, scope: !1766)
!1974 = !DILocation(line: 248, column: 34, scope: !1766)
!1975 = !DILocation(line: 249, column: 34, scope: !1766)
!1976 = !DILocation(line: 248, column: 3, scope: !1766)
!1977 = !DILocation(line: 251, column: 1, scope: !1766)
!1978 = !DILocalVariable(name: "conn", arg: 1, scope: !1741, file: !1, line: 344, type: !262)
!1979 = !DILocation(line: 344, column: 37, scope: !1741)
!1980 = !DILocalVariable(name: "hostname", arg: 2, scope: !1741, file: !1, line: 345, type: !527)
!1981 = !DILocation(line: 345, column: 29, scope: !1741)
!1982 = !DILocalVariable(name: "port", arg: 3, scope: !1741, file: !1, line: 346, type: !316)
!1983 = !DILocation(line: 346, column: 21, scope: !1741)
!1984 = !DILocalVariable(name: "data", scope: !1741, file: !1, line: 348, type: !256)
!1985 = !DILocation(line: 348, column: 21, scope: !1741)
!1986 = !DILocation(line: 348, column: 28, scope: !1741)
!1987 = !DILocation(line: 348, column: 34, scope: !1741)
!1988 = !DILocalVariable(name: "dns", scope: !1741, file: !1, line: 349, type: !1310)
!1989 = !DILocation(line: 349, column: 26, scope: !1741)
!1990 = !DILocation(line: 351, column: 6, scope: !1991)
!1991 = distinct !DILexicalBlock(scope: !1741, file: !1, line: 351, column: 6)
!1992 = !DILocation(line: 351, column: 12, scope: !1991)
!1993 = !DILocation(line: 351, column: 6, scope: !1741)
!1994 = !DILocation(line: 352, column: 21, scope: !1991)
!1995 = !DILocation(line: 352, column: 5, scope: !1991)
!1996 = !DILocation(line: 354, column: 20, scope: !1741)
!1997 = !DILocation(line: 354, column: 26, scope: !1741)
!1998 = !DILocation(line: 354, column: 36, scope: !1741)
!1999 = !DILocation(line: 354, column: 9, scope: !1741)
!2000 = !DILocation(line: 354, column: 7, scope: !1741)
!2001 = !DILocation(line: 356, column: 6, scope: !2002)
!2002 = distinct !DILexicalBlock(scope: !1741, file: !1, line: 356, column: 6)
!2003 = !DILocation(line: 356, column: 6, scope: !1741)
!2004 = !DILocation(line: 357, column: 5, scope: !2002)
!2005 = !DILocation(line: 357, column: 10, scope: !2002)
!2006 = !DILocation(line: 357, column: 15, scope: !2002)
!2007 = !DILocation(line: 359, column: 6, scope: !2008)
!2008 = distinct !DILexicalBlock(scope: !1741, file: !1, line: 359, column: 6)
!2009 = !DILocation(line: 359, column: 12, scope: !2008)
!2010 = !DILocation(line: 359, column: 6, scope: !1741)
!2011 = !DILocation(line: 360, column: 23, scope: !2008)
!2012 = !DILocation(line: 360, column: 5, scope: !2008)
!2013 = !DILocation(line: 362, column: 10, scope: !1741)
!2014 = !DILocation(line: 362, column: 3, scope: !1741)
!2015 = !DILocalVariable(name: "conn", arg: 1, scope: !1772, file: !1, line: 289, type: !262)
!2016 = !DILocation(line: 289, column: 32, scope: !1772)
!2017 = !DILocalVariable(name: "hostname", arg: 2, scope: !1772, file: !1, line: 290, type: !527)
!2018 = !DILocation(line: 290, column: 29, scope: !1772)
!2019 = !DILocalVariable(name: "port", arg: 3, scope: !1772, file: !1, line: 291, type: !316)
!2020 = !DILocation(line: 291, column: 21, scope: !1772)
!2021 = !DILocalVariable(name: "entry_id", scope: !1772, file: !1, line: 293, type: !500)
!2022 = !DILocation(line: 293, column: 9, scope: !1772)
!2023 = !DILocalVariable(name: "dns", scope: !1772, file: !1, line: 294, type: !1310)
!2024 = !DILocation(line: 294, column: 26, scope: !1772)
!2025 = !DILocalVariable(name: "entry_len", scope: !1772, file: !1, line: 295, type: !347)
!2026 = !DILocation(line: 295, column: 10, scope: !1772)
!2027 = !DILocalVariable(name: "data", scope: !1772, file: !1, line: 296, type: !256)
!2028 = !DILocation(line: 296, column: 21, scope: !1772)
!2029 = !DILocation(line: 296, column: 28, scope: !1772)
!2030 = !DILocation(line: 296, column: 34, scope: !1772)
!2031 = !DILocation(line: 299, column: 34, scope: !1772)
!2032 = !DILocation(line: 299, column: 44, scope: !1772)
!2033 = !DILocation(line: 299, column: 14, scope: !1772)
!2034 = !DILocation(line: 299, column: 12, scope: !1772)
!2035 = !DILocation(line: 301, column: 7, scope: !2036)
!2036 = distinct !DILexicalBlock(scope: !1772, file: !1, line: 301, column: 6)
!2037 = !DILocation(line: 301, column: 6, scope: !1772)
!2038 = !DILocation(line: 302, column: 12, scope: !2036)
!2039 = !DILocation(line: 302, column: 5, scope: !2036)
!2040 = !DILocation(line: 304, column: 22, scope: !1772)
!2041 = !DILocation(line: 304, column: 15, scope: !1772)
!2042 = !DILocation(line: 304, column: 13, scope: !1772)
!2043 = !DILocation(line: 307, column: 24, scope: !1772)
!2044 = !DILocation(line: 307, column: 30, scope: !1772)
!2045 = !DILocation(line: 307, column: 34, scope: !1772)
!2046 = !DILocation(line: 307, column: 45, scope: !1772)
!2047 = !DILocation(line: 307, column: 55, scope: !1772)
!2048 = !DILocation(line: 307, column: 64, scope: !1772)
!2049 = !DILocation(line: 307, column: 9, scope: !1772)
!2050 = !DILocation(line: 307, column: 7, scope: !1772)
!2051 = !DILocation(line: 309, column: 6, scope: !2052)
!2052 = distinct !DILexicalBlock(scope: !1772, file: !1, line: 309, column: 6)
!2053 = !DILocation(line: 309, column: 10, scope: !2052)
!2054 = !DILocation(line: 309, column: 14, scope: !2055)
!2055 = !DILexicalBlockFile(scope: !2052, file: !1, discriminator: 1)
!2056 = !DILocation(line: 309, column: 20, scope: !2055)
!2057 = !DILocation(line: 309, column: 24, scope: !2055)
!2058 = !DILocation(line: 309, column: 42, scope: !2055)
!2059 = !DILocation(line: 309, column: 6, scope: !2055)
!2060 = !DILocalVariable(name: "user", scope: !2061, file: !1, line: 311, type: !1718)
!2061 = distinct !DILexicalBlock(scope: !2052, file: !1, line: 309, column: 51)
!2062 = !DILocation(line: 311, column: 33, scope: !2061)
!2063 = !DILocation(line: 313, column: 16, scope: !2061)
!2064 = !DILocation(line: 313, column: 5, scope: !2061)
!2065 = !DILocation(line: 314, column: 26, scope: !2061)
!2066 = !DILocation(line: 314, column: 32, scope: !2061)
!2067 = !DILocation(line: 314, column: 36, scope: !2061)
!2068 = !DILocation(line: 314, column: 10, scope: !2061)
!2069 = !DILocation(line: 314, column: 24, scope: !2061)
!2070 = !DILocation(line: 316, column: 35, scope: !2071)
!2071 = distinct !DILexicalBlock(scope: !2061, file: !1, line: 316, column: 8)
!2072 = !DILocation(line: 316, column: 42, scope: !2071)
!2073 = !DILocation(line: 316, column: 8, scope: !2071)
!2074 = !DILocation(line: 316, column: 8, scope: !2061)
!2075 = !DILocation(line: 317, column: 13, scope: !2076)
!2076 = distinct !DILexicalBlock(scope: !2071, file: !1, line: 316, column: 48)
!2077 = !DILocation(line: 317, column: 7, scope: !2076)
!2078 = !DILocation(line: 318, column: 11, scope: !2076)
!2079 = !DILocation(line: 319, column: 24, scope: !2076)
!2080 = !DILocation(line: 319, column: 30, scope: !2076)
!2081 = !DILocation(line: 319, column: 34, scope: !2076)
!2082 = !DILocation(line: 319, column: 45, scope: !2076)
!2083 = !DILocation(line: 319, column: 55, scope: !2076)
!2084 = !DILocation(line: 319, column: 64, scope: !2076)
!2085 = !DILocation(line: 319, column: 7, scope: !2076)
!2086 = !DILocation(line: 320, column: 5, scope: !2076)
!2087 = !DILocation(line: 321, column: 3, scope: !2061)
!2088 = !DILocation(line: 324, column: 3, scope: !1772)
!2089 = !DILocation(line: 326, column: 10, scope: !1772)
!2090 = !DILocation(line: 326, column: 3, scope: !1772)
!2091 = !DILocation(line: 327, column: 1, scope: !1772)
!2092 = !DILocalVariable(name: "data", arg: 1, scope: !1744, file: !1, line: 375, type: !256)
!2093 = !DILocation(line: 375, column: 35, scope: !1744)
!2094 = !DILocalVariable(name: "addr", arg: 2, scope: !1744, file: !1, line: 376, type: !1315)
!2095 = !DILocation(line: 376, column: 32, scope: !1744)
!2096 = !DILocalVariable(name: "hostname", arg: 3, scope: !1744, file: !1, line: 377, type: !527)
!2097 = !DILocation(line: 377, column: 29, scope: !1744)
!2098 = !DILocalVariable(name: "port", arg: 4, scope: !1744, file: !1, line: 378, type: !316)
!2099 = !DILocation(line: 378, column: 21, scope: !1744)
!2100 = !DILocalVariable(name: "entry_id", scope: !1744, file: !1, line: 380, type: !500)
!2101 = !DILocation(line: 380, column: 9, scope: !1744)
!2102 = !DILocalVariable(name: "entry_len", scope: !1744, file: !1, line: 381, type: !347)
!2103 = !DILocation(line: 381, column: 10, scope: !1744)
!2104 = !DILocalVariable(name: "dns", scope: !1744, file: !1, line: 382, type: !1310)
!2105 = !DILocation(line: 382, column: 26, scope: !1744)
!2106 = !DILocalVariable(name: "dns2", scope: !1744, file: !1, line: 383, type: !1310)
!2107 = !DILocation(line: 383, column: 26, scope: !1744)
!2108 = !DILocation(line: 386, column: 34, scope: !1744)
!2109 = !DILocation(line: 386, column: 44, scope: !1744)
!2110 = !DILocation(line: 386, column: 14, scope: !1744)
!2111 = !DILocation(line: 386, column: 12, scope: !1744)
!2112 = !DILocation(line: 388, column: 7, scope: !2113)
!2113 = distinct !DILexicalBlock(scope: !1744, file: !1, line: 388, column: 6)
!2114 = !DILocation(line: 388, column: 6, scope: !1744)
!2115 = !DILocation(line: 389, column: 5, scope: !2113)
!2116 = !DILocation(line: 390, column: 22, scope: !1744)
!2117 = !DILocation(line: 390, column: 15, scope: !1744)
!2118 = !DILocation(line: 390, column: 13, scope: !1744)
!2119 = !DILocation(line: 393, column: 9, scope: !1744)
!2120 = !DILocation(line: 393, column: 7, scope: !1744)
!2121 = !DILocation(line: 394, column: 7, scope: !2122)
!2122 = distinct !DILexicalBlock(scope: !1744, file: !1, line: 394, column: 6)
!2123 = !DILocation(line: 394, column: 6, scope: !1744)
!2124 = !DILocation(line: 395, column: 5, scope: !2125)
!2125 = distinct !DILexicalBlock(scope: !2122, file: !1, line: 394, column: 12)
!2126 = !DILocation(line: 396, column: 5, scope: !2125)
!2127 = !DILocation(line: 399, column: 3, scope: !1744)
!2128 = !DILocation(line: 399, column: 8, scope: !1744)
!2129 = !DILocation(line: 399, column: 14, scope: !1744)
!2130 = !DILocation(line: 400, column: 15, scope: !1744)
!2131 = !DILocation(line: 400, column: 3, scope: !1744)
!2132 = !DILocation(line: 400, column: 8, scope: !1744)
!2133 = !DILocation(line: 400, column: 13, scope: !1744)
!2134 = !DILocation(line: 401, column: 9, scope: !1744)
!2135 = !DILocation(line: 401, column: 14, scope: !1744)
!2136 = !DILocation(line: 401, column: 3, scope: !1744)
!2137 = !DILocation(line: 402, column: 6, scope: !2138)
!2138 = distinct !DILexicalBlock(scope: !1744, file: !1, line: 402, column: 6)
!2139 = !DILocation(line: 402, column: 11, scope: !2138)
!2140 = !DILocation(line: 402, column: 21, scope: !2138)
!2141 = !DILocation(line: 402, column: 6, scope: !1744)
!2142 = !DILocation(line: 403, column: 5, scope: !2138)
!2143 = !DILocation(line: 403, column: 10, scope: !2138)
!2144 = !DILocation(line: 403, column: 20, scope: !2138)
!2145 = !DILocation(line: 406, column: 24, scope: !1744)
!2146 = !DILocation(line: 406, column: 30, scope: !1744)
!2147 = !DILocation(line: 406, column: 34, scope: !1744)
!2148 = !DILocation(line: 406, column: 45, scope: !1744)
!2149 = !DILocation(line: 406, column: 55, scope: !1744)
!2150 = !DILocation(line: 406, column: 64, scope: !1744)
!2151 = !DILocation(line: 407, column: 32, scope: !1744)
!2152 = !DILocation(line: 407, column: 24, scope: !1744)
!2153 = !DILocation(line: 406, column: 10, scope: !1744)
!2154 = !DILocation(line: 406, column: 8, scope: !1744)
!2155 = !DILocation(line: 408, column: 7, scope: !2156)
!2156 = distinct !DILexicalBlock(scope: !1744, file: !1, line: 408, column: 6)
!2157 = !DILocation(line: 408, column: 6, scope: !1744)
!2158 = !DILocation(line: 409, column: 5, scope: !2159)
!2159 = distinct !DILexicalBlock(scope: !2156, file: !1, line: 408, column: 13)
!2160 = !DILocation(line: 410, column: 5, scope: !2159)
!2161 = !DILocation(line: 411, column: 5, scope: !2159)
!2162 = !DILocation(line: 414, column: 9, scope: !1744)
!2163 = !DILocation(line: 414, column: 7, scope: !1744)
!2164 = !DILocation(line: 415, column: 3, scope: !1744)
!2165 = !DILocation(line: 415, column: 8, scope: !1744)
!2166 = !DILocation(line: 415, column: 13, scope: !1744)
!2167 = !DILocation(line: 418, column: 3, scope: !1744)
!2168 = !DILocation(line: 420, column: 10, scope: !1744)
!2169 = !DILocation(line: 420, column: 3, scope: !1744)
!2170 = !DILocation(line: 421, column: 1, scope: !1744)
!2171 = !DILocalVariable(name: "name", arg: 1, scope: !1773, file: !1, line: 199, type: !527)
!2172 = !DILocation(line: 199, column: 33, scope: !1773)
!2173 = !DILocalVariable(name: "port", arg: 2, scope: !1773, file: !1, line: 199, type: !316)
!2174 = !DILocation(line: 199, column: 43, scope: !1773)
!2175 = !DILocalVariable(name: "id", scope: !1773, file: !1, line: 202, type: !500)
!2176 = !DILocation(line: 202, column: 9, scope: !1773)
!2177 = !DILocation(line: 202, column: 31, scope: !1773)
!2178 = !DILocation(line: 202, column: 37, scope: !1773)
!2179 = !DILocation(line: 202, column: 14, scope: !1773)
!2180 = !DILocalVariable(name: "ptr", scope: !1773, file: !1, line: 203, type: !500)
!2181 = !DILocation(line: 203, column: 9, scope: !1773)
!2182 = !DILocation(line: 203, column: 15, scope: !1773)
!2183 = !DILocation(line: 204, column: 6, scope: !2184)
!2184 = distinct !DILexicalBlock(scope: !1773, file: !1, line: 204, column: 6)
!2185 = !DILocation(line: 204, column: 6, scope: !1773)
!2186 = !DILocation(line: 206, column: 5, scope: !2187)
!2187 = distinct !DILexicalBlock(scope: !2184, file: !1, line: 204, column: 11)
!2188 = !DILocation(line: 206, column: 12, scope: !2189)
!2189 = !DILexicalBlockFile(scope: !2187, file: !1, discriminator: 1)
!2190 = !DILocation(line: 206, column: 11, scope: !2189)
!2191 = !DILocation(line: 206, column: 16, scope: !2189)
!2192 = !DILocation(line: 206, column: 21, scope: !2193)
!2193 = !DILexicalBlockFile(scope: !2187, file: !1, discriminator: 2)
!2194 = !DILocation(line: 206, column: 20, scope: !2193)
!2195 = !DILocation(line: 206, column: 25, scope: !2193)
!2196 = !DILocation(line: 206, column: 5, scope: !2197)
!2197 = !DILexicalBlockFile(scope: !2187, file: !1, discriminator: 3)
!2198 = !DILocation(line: 207, column: 20, scope: !2199)
!2199 = distinct !DILexicalBlock(scope: !2187, file: !1, line: 206, column: 34)
!2200 = !DILocation(line: 207, column: 14, scope: !2199)
!2201 = !DILocation(line: 207, column: 8, scope: !2199)
!2202 = !DILocation(line: 207, column: 12, scope: !2199)
!2203 = !DILocation(line: 208, column: 10, scope: !2199)
!2204 = !DILocation(line: 206, column: 5, scope: !2205)
!2205 = !DILexicalBlockFile(scope: !2187, file: !1, discriminator: 4)
!2206 = !DILocation(line: 210, column: 3, scope: !2187)
!2207 = !DILocation(line: 211, column: 10, scope: !1773)
!2208 = !DILocation(line: 211, column: 3, scope: !1773)
!2209 = !DILocalVariable(name: "conn", arg: 1, scope: !1747, file: !1, line: 444, type: !262)
!2210 = !DILocation(line: 444, column: 37, scope: !1747)
!2211 = !DILocalVariable(name: "hostname", arg: 2, scope: !1747, file: !1, line: 445, type: !527)
!2212 = !DILocation(line: 445, column: 29, scope: !1747)
!2213 = !DILocalVariable(name: "port", arg: 3, scope: !1747, file: !1, line: 446, type: !316)
!2214 = !DILocation(line: 446, column: 21, scope: !1747)
!2215 = !DILocalVariable(name: "entry", arg: 4, scope: !1747, file: !1, line: 447, type: !1750)
!2216 = !DILocation(line: 447, column: 41, scope: !1747)
!2217 = !DILocalVariable(name: "dns", scope: !1747, file: !1, line: 449, type: !1310)
!2218 = !DILocation(line: 449, column: 26, scope: !1747)
!2219 = !DILocalVariable(name: "data", scope: !1747, file: !1, line: 450, type: !256)
!2220 = !DILocation(line: 450, column: 21, scope: !1747)
!2221 = !DILocation(line: 450, column: 28, scope: !1747)
!2222 = !DILocation(line: 450, column: 34, scope: !1747)
!2223 = !DILocalVariable(name: "result", scope: !1747, file: !1, line: 451, type: !289)
!2224 = !DILocation(line: 451, column: 12, scope: !1747)
!2225 = !DILocalVariable(name: "rc", scope: !1747, file: !1, line: 452, type: !316)
!2226 = !DILocation(line: 452, column: 7, scope: !1747)
!2227 = !DILocation(line: 454, column: 4, scope: !1747)
!2228 = !DILocation(line: 454, column: 10, scope: !1747)
!2229 = !DILocation(line: 456, column: 6, scope: !2230)
!2230 = distinct !DILexicalBlock(scope: !1747, file: !1, line: 456, column: 6)
!2231 = !DILocation(line: 456, column: 12, scope: !2230)
!2232 = !DILocation(line: 456, column: 6, scope: !1747)
!2233 = !DILocation(line: 457, column: 21, scope: !2230)
!2234 = !DILocation(line: 457, column: 5, scope: !2230)
!2235 = !DILocation(line: 459, column: 20, scope: !1747)
!2236 = !DILocation(line: 459, column: 26, scope: !1747)
!2237 = !DILocation(line: 459, column: 36, scope: !1747)
!2238 = !DILocation(line: 459, column: 9, scope: !1747)
!2239 = !DILocation(line: 459, column: 7, scope: !1747)
!2240 = !DILocation(line: 461, column: 6, scope: !2241)
!2241 = distinct !DILexicalBlock(scope: !1747, file: !1, line: 461, column: 6)
!2242 = !DILocation(line: 461, column: 6, scope: !1747)
!2243 = !DILocation(line: 462, column: 11, scope: !2244)
!2244 = distinct !DILexicalBlock(scope: !2241, file: !1, line: 461, column: 11)
!2245 = !DILocation(line: 462, column: 57, scope: !2244)
!2246 = !DILocation(line: 462, column: 5, scope: !2244)
!2247 = !DILocation(line: 463, column: 5, scope: !2244)
!2248 = !DILocation(line: 463, column: 10, scope: !2244)
!2249 = !DILocation(line: 463, column: 15, scope: !2244)
!2250 = !DILocation(line: 464, column: 8, scope: !2244)
!2251 = !DILocation(line: 465, column: 3, scope: !2244)
!2252 = !DILocation(line: 467, column: 6, scope: !2253)
!2253 = distinct !DILexicalBlock(scope: !1747, file: !1, line: 467, column: 6)
!2254 = !DILocation(line: 467, column: 12, scope: !2253)
!2255 = !DILocation(line: 467, column: 6, scope: !1747)
!2256 = !DILocation(line: 468, column: 23, scope: !2253)
!2257 = !DILocation(line: 468, column: 5, scope: !2253)
!2258 = !DILocation(line: 470, column: 7, scope: !2259)
!2259 = distinct !DILexicalBlock(scope: !1747, file: !1, line: 470, column: 6)
!2260 = !DILocation(line: 470, column: 6, scope: !1747)
!2261 = !DILocalVariable(name: "addr", scope: !2262, file: !1, line: 473, type: !1315)
!2262 = distinct !DILexicalBlock(scope: !2259, file: !1, line: 470, column: 12)
!2263 = !DILocation(line: 473, column: 20, scope: !2262)
!2264 = !DILocalVariable(name: "respwait", scope: !2262, file: !1, line: 474, type: !316)
!2265 = !DILocation(line: 474, column: 9, scope: !2262)
!2266 = !DILocation(line: 478, column: 22, scope: !2267)
!2267 = distinct !DILexicalBlock(scope: !2262, file: !1, line: 478, column: 8)
!2268 = !DILocation(line: 478, column: 9, scope: !2267)
!2269 = !DILocation(line: 478, column: 8, scope: !2262)
!2270 = !DILocation(line: 479, column: 7, scope: !2267)
!2271 = !DILocation(line: 484, column: 29, scope: !2262)
!2272 = !DILocation(line: 490, column: 29, scope: !2262)
!2273 = !DILocation(line: 490, column: 39, scope: !2262)
!2274 = !DILocation(line: 484, column: 12, scope: !2262)
!2275 = !DILocation(line: 484, column: 10, scope: !2262)
!2276 = !DILocation(line: 492, column: 9, scope: !2277)
!2277 = distinct !DILexicalBlock(scope: !2262, file: !1, line: 492, column: 8)
!2278 = !DILocation(line: 492, column: 8, scope: !2262)
!2279 = !DILocation(line: 493, column: 10, scope: !2280)
!2280 = distinct !DILexicalBlock(scope: !2281, file: !1, line: 493, column: 10)
!2281 = distinct !DILexicalBlock(scope: !2277, file: !1, line: 492, column: 15)
!2282 = !DILocation(line: 493, column: 10, scope: !2281)
!2283 = !DILocation(line: 497, column: 16, scope: !2284)
!2284 = distinct !DILexicalBlock(scope: !2280, file: !1, line: 493, column: 20)
!2285 = !DILocation(line: 498, column: 12, scope: !2286)
!2286 = distinct !DILexicalBlock(scope: !2284, file: !1, line: 498, column: 12)
!2287 = !DILocation(line: 498, column: 12, scope: !2284)
!2288 = !DILocation(line: 499, column: 11, scope: !2286)
!2289 = !DILocation(line: 500, column: 12, scope: !2290)
!2290 = distinct !DILexicalBlock(scope: !2284, file: !1, line: 500, column: 12)
!2291 = !DILocation(line: 500, column: 12, scope: !2284)
!2292 = !DILocation(line: 501, column: 14, scope: !2290)
!2293 = !DILocation(line: 501, column: 11, scope: !2290)
!2294 = !DILocation(line: 503, column: 14, scope: !2290)
!2295 = !DILocation(line: 504, column: 7, scope: !2284)
!2296 = !DILocation(line: 505, column: 5, scope: !2281)
!2297 = !DILocation(line: 507, column: 10, scope: !2298)
!2298 = distinct !DILexicalBlock(scope: !2299, file: !1, line: 507, column: 10)
!2299 = distinct !DILexicalBlock(scope: !2277, file: !1, line: 506, column: 10)
!2300 = !DILocation(line: 507, column: 16, scope: !2298)
!2301 = !DILocation(line: 507, column: 10, scope: !2299)
!2302 = !DILocation(line: 508, column: 25, scope: !2298)
!2303 = !DILocation(line: 508, column: 9, scope: !2298)
!2304 = !DILocation(line: 511, column: 29, scope: !2299)
!2305 = !DILocation(line: 511, column: 35, scope: !2299)
!2306 = !DILocation(line: 511, column: 41, scope: !2299)
!2307 = !DILocation(line: 511, column: 51, scope: !2299)
!2308 = !DILocation(line: 511, column: 13, scope: !2299)
!2309 = !DILocation(line: 511, column: 11, scope: !2299)
!2310 = !DILocation(line: 513, column: 10, scope: !2311)
!2311 = distinct !DILexicalBlock(scope: !2299, file: !1, line: 513, column: 10)
!2312 = !DILocation(line: 513, column: 16, scope: !2311)
!2313 = !DILocation(line: 513, column: 10, scope: !2299)
!2314 = !DILocation(line: 514, column: 27, scope: !2311)
!2315 = !DILocation(line: 514, column: 9, scope: !2311)
!2316 = !DILocation(line: 516, column: 11, scope: !2317)
!2317 = distinct !DILexicalBlock(scope: !2299, file: !1, line: 516, column: 10)
!2318 = !DILocation(line: 516, column: 10, scope: !2299)
!2319 = !DILocation(line: 518, column: 27, scope: !2317)
!2320 = !DILocation(line: 518, column: 9, scope: !2317)
!2321 = !DILocation(line: 520, column: 12, scope: !2317)
!2322 = !DILocation(line: 522, column: 3, scope: !2262)
!2323 = !DILocation(line: 524, column: 12, scope: !1747)
!2324 = !DILocation(line: 524, column: 4, scope: !1747)
!2325 = !DILocation(line: 524, column: 10, scope: !1747)
!2326 = !DILocation(line: 526, column: 10, scope: !1747)
!2327 = !DILocation(line: 526, column: 3, scope: !1747)
!2328 = !DILocation(line: 527, column: 1, scope: !1747)
!2329 = !DILocalVariable(name: "conn", arg: 1, scope: !1751, file: !1, line: 567, type: !262)
!2330 = !DILocation(line: 567, column: 45, scope: !1751)
!2331 = !DILocalVariable(name: "hostname", arg: 2, scope: !1751, file: !1, line: 568, type: !527)
!2332 = !DILocation(line: 568, column: 37, scope: !1751)
!2333 = !DILocalVariable(name: "port", arg: 3, scope: !1751, file: !1, line: 569, type: !316)
!2334 = !DILocation(line: 569, column: 29, scope: !1751)
!2335 = !DILocalVariable(name: "entry", arg: 4, scope: !1751, file: !1, line: 570, type: !1750)
!2336 = !DILocation(line: 570, column: 49, scope: !1751)
!2337 = !DILocalVariable(name: "timeoutms", arg: 5, scope: !1751, file: !1, line: 571, type: !599)
!2338 = !DILocation(line: 571, column: 32, scope: !1751)
!2339 = !DILocalVariable(name: "keep_sigact", scope: !1751, file: !1, line: 575, type: !2340)
!2340 = !DICompositeType(tag: DW_TAG_structure_type, name: "sigaction", file: !2341, line: 24, size: 1216, align: 64, elements: !2342)
!2341 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sigaction.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2342 = !{!2343, !2419, !2420, !2421}
!2343 = !DIDerivedType(tag: DW_TAG_member, name: "__sigaction_handler", scope: !2340, file: !2341, line: 35, baseType: !2344, size: 64, align: 64)
!2344 = !DICompositeType(tag: DW_TAG_union_type, scope: !2340, file: !2341, line: 28, size: 64, align: 64, elements: !2345)
!2345 = !{!2346, !2349}
!2346 = !DIDerivedType(tag: DW_TAG_member, name: "sa_handler", scope: !2344, file: !2341, line: 31, baseType: !2347, size: 64, align: 64)
!2347 = !DIDerivedType(tag: DW_TAG_typedef, name: "__sighandler_t", file: !2348, line: 85, baseType: !1162)
!2348 = !DIFile(filename: "/usr/include/signal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2349 = !DIDerivedType(tag: DW_TAG_member, name: "sa_sigaction", scope: !2344, file: !2341, line: 33, baseType: !2350, size: 64, align: 64)
!2350 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2351, size: 64, align: 64)
!2351 = !DISubroutineType(types: !2352)
!2352 = !{null, !316, !2353, !311}
!2353 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2354, size: 64, align: 64)
!2354 = !DIDerivedType(tag: DW_TAG_typedef, name: "siginfo_t", file: !2355, line: 128, baseType: !2356)
!2355 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/siginfo.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2356 = !DICompositeType(tag: DW_TAG_structure_type, file: !2355, line: 62, size: 1024, align: 64, elements: !2357)
!2357 = !{!2358, !2359, !2360, !2361}
!2358 = !DIDerivedType(tag: DW_TAG_member, name: "si_signo", scope: !2356, file: !2355, line: 64, baseType: !316, size: 32, align: 32)
!2359 = !DIDerivedType(tag: DW_TAG_member, name: "si_errno", scope: !2356, file: !2355, line: 65, baseType: !316, size: 32, align: 32, offset: 32)
!2360 = !DIDerivedType(tag: DW_TAG_member, name: "si_code", scope: !2356, file: !2355, line: 67, baseType: !316, size: 32, align: 32, offset: 64)
!2361 = !DIDerivedType(tag: DW_TAG_member, name: "_sifields", scope: !2356, file: !2355, line: 127, baseType: !2362, size: 896, align: 64, offset: 128)
!2362 = !DICompositeType(tag: DW_TAG_union_type, scope: !2356, file: !2355, line: 69, size: 896, align: 64, elements: !2363)
!2363 = !{!2364, !2368, !2375, !2386, !2392, !2402, !2408, !2413}
!2364 = !DIDerivedType(tag: DW_TAG_member, name: "_pad", scope: !2362, file: !2355, line: 71, baseType: !2365, size: 896, align: 32)
!2365 = !DICompositeType(tag: DW_TAG_array_type, baseType: !316, size: 896, align: 32, elements: !2366)
!2366 = !{!2367}
!2367 = !DISubrange(count: 28)
!2368 = !DIDerivedType(tag: DW_TAG_member, name: "_kill", scope: !2362, file: !2355, line: 78, baseType: !2369, size: 64, align: 32)
!2369 = !DICompositeType(tag: DW_TAG_structure_type, scope: !2362, file: !2355, line: 74, size: 64, align: 32, elements: !2370)
!2370 = !{!2371, !2373}
!2371 = !DIDerivedType(tag: DW_TAG_member, name: "si_pid", scope: !2369, file: !2355, line: 76, baseType: !2372, size: 32, align: 32)
!2372 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !416, line: 133, baseType: !316)
!2373 = !DIDerivedType(tag: DW_TAG_member, name: "si_uid", scope: !2369, file: !2355, line: 77, baseType: !2374, size: 32, align: 32, offset: 32)
!2374 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !416, line: 125, baseType: !457)
!2375 = !DIDerivedType(tag: DW_TAG_member, name: "_timer", scope: !2362, file: !2355, line: 86, baseType: !2376, size: 128, align: 64)
!2376 = !DICompositeType(tag: DW_TAG_structure_type, scope: !2362, file: !2355, line: 81, size: 128, align: 64, elements: !2377)
!2377 = !{!2378, !2379, !2380}
!2378 = !DIDerivedType(tag: DW_TAG_member, name: "si_tid", scope: !2376, file: !2355, line: 83, baseType: !316, size: 32, align: 32)
!2379 = !DIDerivedType(tag: DW_TAG_member, name: "si_overrun", scope: !2376, file: !2355, line: 84, baseType: !316, size: 32, align: 32, offset: 32)
!2380 = !DIDerivedType(tag: DW_TAG_member, name: "si_sigval", scope: !2376, file: !2355, line: 85, baseType: !2381, size: 64, align: 64, offset: 64)
!2381 = !DIDerivedType(tag: DW_TAG_typedef, name: "sigval_t", file: !2355, line: 36, baseType: !2382)
!2382 = !DICompositeType(tag: DW_TAG_union_type, name: "sigval", file: !2355, line: 32, size: 64, align: 64, elements: !2383)
!2383 = !{!2384, !2385}
!2384 = !DIDerivedType(tag: DW_TAG_member, name: "sival_int", scope: !2382, file: !2355, line: 34, baseType: !316, size: 32, align: 32)
!2385 = !DIDerivedType(tag: DW_TAG_member, name: "sival_ptr", scope: !2382, file: !2355, line: 35, baseType: !311, size: 64, align: 64)
!2386 = !DIDerivedType(tag: DW_TAG_member, name: "_rt", scope: !2362, file: !2355, line: 94, baseType: !2387, size: 128, align: 64)
!2387 = !DICompositeType(tag: DW_TAG_structure_type, scope: !2362, file: !2355, line: 89, size: 128, align: 64, elements: !2388)
!2388 = !{!2389, !2390, !2391}
!2389 = !DIDerivedType(tag: DW_TAG_member, name: "si_pid", scope: !2387, file: !2355, line: 91, baseType: !2372, size: 32, align: 32)
!2390 = !DIDerivedType(tag: DW_TAG_member, name: "si_uid", scope: !2387, file: !2355, line: 92, baseType: !2374, size: 32, align: 32, offset: 32)
!2391 = !DIDerivedType(tag: DW_TAG_member, name: "si_sigval", scope: !2387, file: !2355, line: 93, baseType: !2381, size: 64, align: 64, offset: 64)
!2392 = !DIDerivedType(tag: DW_TAG_member, name: "_sigchld", scope: !2362, file: !2355, line: 104, baseType: !2393, size: 256, align: 64)
!2393 = !DICompositeType(tag: DW_TAG_structure_type, scope: !2362, file: !2355, line: 97, size: 256, align: 64, elements: !2394)
!2394 = !{!2395, !2396, !2397, !2398, !2401}
!2395 = !DIDerivedType(tag: DW_TAG_member, name: "si_pid", scope: !2393, file: !2355, line: 99, baseType: !2372, size: 32, align: 32)
!2396 = !DIDerivedType(tag: DW_TAG_member, name: "si_uid", scope: !2393, file: !2355, line: 100, baseType: !2374, size: 32, align: 32, offset: 32)
!2397 = !DIDerivedType(tag: DW_TAG_member, name: "si_status", scope: !2393, file: !2355, line: 101, baseType: !316, size: 32, align: 32, offset: 64)
!2398 = !DIDerivedType(tag: DW_TAG_member, name: "si_utime", scope: !2393, file: !2355, line: 102, baseType: !2399, size: 64, align: 64, offset: 128)
!2399 = !DIDerivedType(tag: DW_TAG_typedef, name: "__sigchld_clock_t", file: !2355, line: 58, baseType: !2400)
!2400 = !DIDerivedType(tag: DW_TAG_typedef, name: "__clock_t", file: !416, line: 135, baseType: !379)
!2401 = !DIDerivedType(tag: DW_TAG_member, name: "si_stime", scope: !2393, file: !2355, line: 103, baseType: !2399, size: 64, align: 64, offset: 192)
!2402 = !DIDerivedType(tag: DW_TAG_member, name: "_sigfault", scope: !2362, file: !2355, line: 111, baseType: !2403, size: 128, align: 64)
!2403 = !DICompositeType(tag: DW_TAG_structure_type, scope: !2362, file: !2355, line: 107, size: 128, align: 64, elements: !2404)
!2404 = !{!2405, !2406}
!2405 = !DIDerivedType(tag: DW_TAG_member, name: "si_addr", scope: !2403, file: !2355, line: 109, baseType: !311, size: 64, align: 64)
!2406 = !DIDerivedType(tag: DW_TAG_member, name: "si_addr_lsb", scope: !2403, file: !2355, line: 110, baseType: !2407, size: 16, align: 16, offset: 64)
!2407 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!2408 = !DIDerivedType(tag: DW_TAG_member, name: "_sigpoll", scope: !2362, file: !2355, line: 118, baseType: !2409, size: 128, align: 64)
!2409 = !DICompositeType(tag: DW_TAG_structure_type, scope: !2362, file: !2355, line: 114, size: 128, align: 64, elements: !2410)
!2410 = !{!2411, !2412}
!2411 = !DIDerivedType(tag: DW_TAG_member, name: "si_band", scope: !2409, file: !2355, line: 116, baseType: !379, size: 64, align: 64)
!2412 = !DIDerivedType(tag: DW_TAG_member, name: "si_fd", scope: !2409, file: !2355, line: 117, baseType: !316, size: 32, align: 32, offset: 64)
!2413 = !DIDerivedType(tag: DW_TAG_member, name: "_sigsys", scope: !2362, file: !2355, line: 126, baseType: !2414, size: 128, align: 64)
!2414 = !DICompositeType(tag: DW_TAG_structure_type, scope: !2362, file: !2355, line: 121, size: 128, align: 64, elements: !2415)
!2415 = !{!2416, !2417, !2418}
!2416 = !DIDerivedType(tag: DW_TAG_member, name: "_call_addr", scope: !2414, file: !2355, line: 123, baseType: !311, size: 64, align: 64)
!2417 = !DIDerivedType(tag: DW_TAG_member, name: "_syscall", scope: !2414, file: !2355, line: 124, baseType: !316, size: 32, align: 32, offset: 64)
!2418 = !DIDerivedType(tag: DW_TAG_member, name: "_arch", scope: !2414, file: !2355, line: 125, baseType: !457, size: 32, align: 32, offset: 96)
!2419 = !DIDerivedType(tag: DW_TAG_member, name: "sa_mask", scope: !2340, file: !2341, line: 43, baseType: !1793, size: 1024, align: 64, offset: 64)
!2420 = !DIDerivedType(tag: DW_TAG_member, name: "sa_flags", scope: !2340, file: !2341, line: 46, baseType: !316, size: 32, align: 32, offset: 1088)
!2421 = !DIDerivedType(tag: DW_TAG_member, name: "sa_restorer", scope: !2340, file: !2341, line: 49, baseType: !2422, size: 64, align: 64, offset: 1152)
!2422 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1728, size: 64, align: 64)
!2423 = !DILocation(line: 575, column: 20, scope: !1751)
!2424 = !DILocalVariable(name: "keep_copysig", scope: !1751, file: !1, line: 576, type: !2425)
!2425 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !423)
!2426 = !DILocation(line: 576, column: 17, scope: !1751)
!2427 = !DILocalVariable(name: "sigact", scope: !1751, file: !1, line: 577, type: !2340)
!2428 = !DILocation(line: 577, column: 20, scope: !1751)
!2429 = !DILocalVariable(name: "timeout", scope: !1751, file: !1, line: 583, type: !2430)
!2430 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !379)
!2431 = !DILocation(line: 583, column: 17, scope: !1751)
!2432 = !DILocalVariable(name: "prev_alarm", scope: !1751, file: !1, line: 584, type: !459)
!2433 = !DILocation(line: 584, column: 25, scope: !1751)
!2434 = !DILocalVariable(name: "data", scope: !1751, file: !1, line: 585, type: !256)
!2435 = !DILocation(line: 585, column: 21, scope: !1751)
!2436 = !DILocation(line: 585, column: 28, scope: !1751)
!2437 = !DILocation(line: 585, column: 34, scope: !1751)
!2438 = !DILocalVariable(name: "rc", scope: !1751, file: !1, line: 587, type: !316)
!2439 = !DILocation(line: 587, column: 7, scope: !1751)
!2440 = !DILocation(line: 589, column: 4, scope: !1751)
!2441 = !DILocation(line: 589, column: 10, scope: !1751)
!2442 = !DILocation(line: 591, column: 6, scope: !2443)
!2443 = distinct !DILexicalBlock(scope: !1751, file: !1, line: 591, column: 6)
!2444 = !DILocation(line: 591, column: 16, scope: !2443)
!2445 = !DILocation(line: 591, column: 6, scope: !1751)
!2446 = !DILocation(line: 593, column: 5, scope: !2443)
!2447 = !DILocation(line: 596, column: 6, scope: !2448)
!2448 = distinct !DILexicalBlock(scope: !1751, file: !1, line: 596, column: 6)
!2449 = !DILocation(line: 596, column: 12, scope: !2448)
!2450 = !DILocation(line: 596, column: 16, scope: !2448)
!2451 = !DILocation(line: 596, column: 6, scope: !1751)
!2452 = !DILocation(line: 598, column: 13, scope: !2448)
!2453 = !DILocation(line: 598, column: 5, scope: !2448)
!2454 = !DILocation(line: 600, column: 15, scope: !2448)
!2455 = !DILocation(line: 600, column: 13, scope: !2448)
!2456 = !DILocation(line: 602, column: 7, scope: !2457)
!2457 = distinct !DILexicalBlock(scope: !1751, file: !1, line: 602, column: 6)
!2458 = !DILocation(line: 602, column: 6, scope: !1751)
!2459 = !DILocation(line: 604, column: 24, scope: !2457)
!2460 = !DILocation(line: 604, column: 30, scope: !2457)
!2461 = !DILocation(line: 604, column: 40, scope: !2457)
!2462 = !DILocation(line: 604, column: 46, scope: !2457)
!2463 = !DILocation(line: 604, column: 12, scope: !2457)
!2464 = !DILocation(line: 604, column: 5, scope: !2457)
!2465 = !DILocation(line: 606, column: 6, scope: !2466)
!2466 = distinct !DILexicalBlock(scope: !1751, file: !1, line: 606, column: 6)
!2467 = !DILocation(line: 606, column: 14, scope: !2466)
!2468 = !DILocation(line: 606, column: 6, scope: !1751)
!2469 = !DILocation(line: 609, column: 11, scope: !2470)
!2470 = distinct !DILexicalBlock(scope: !2466, file: !1, line: 606, column: 22)
!2471 = !DILocation(line: 611, column: 9, scope: !2470)
!2472 = !DILocation(line: 609, column: 5, scope: !2470)
!2473 = !DILocation(line: 612, column: 5, scope: !2470)
!2474 = !DILocation(line: 620, column: 6, scope: !2475)
!2475 = distinct !DILexicalBlock(scope: !1751, file: !1, line: 620, column: 6)
!2476 = !DILocation(line: 620, column: 6, scope: !1751)
!2477 = !DILocation(line: 622, column: 11, scope: !2478)
!2478 = distinct !DILexicalBlock(scope: !2475, file: !1, line: 620, column: 33)
!2479 = !DILocation(line: 622, column: 5, scope: !2478)
!2480 = !DILocation(line: 623, column: 8, scope: !2478)
!2481 = !DILocation(line: 624, column: 5, scope: !2478)
!2482 = !DILocation(line: 632, column: 5, scope: !2483)
!2483 = distinct !DILexicalBlock(scope: !2475, file: !1, line: 626, column: 8)
!2484 = !DILocation(line: 633, column: 19, scope: !2483)
!2485 = !DILocation(line: 634, column: 18, scope: !2483)
!2486 = !DILocation(line: 635, column: 12, scope: !2483)
!2487 = !DILocation(line: 635, column: 23, scope: !2483)
!2488 = !DILocation(line: 638, column: 12, scope: !2483)
!2489 = !DILocation(line: 638, column: 21, scope: !2483)
!2490 = !DILocation(line: 641, column: 5, scope: !2483)
!2491 = !DILocation(line: 651, column: 37, scope: !2483)
!2492 = !DILocation(line: 651, column: 44, scope: !2483)
!2493 = !DILocation(line: 651, column: 24, scope: !2483)
!2494 = !DILocation(line: 651, column: 18, scope: !2495)
!2495 = !DILexicalBlockFile(scope: !2483, file: !1, discriminator: 1)
!2496 = !DILocation(line: 651, column: 16, scope: !2483)
!2497 = !DILocation(line: 666, column: 20, scope: !1751)
!2498 = !DILocation(line: 666, column: 26, scope: !1751)
!2499 = !DILocation(line: 666, column: 36, scope: !1751)
!2500 = !DILocation(line: 666, column: 42, scope: !1751)
!2501 = !DILocation(line: 666, column: 8, scope: !1751)
!2502 = !DILocation(line: 666, column: 6, scope: !1751)
!2503 = !DILocation(line: 666, column: 3, scope: !1751)
!2504 = !DILocation(line: 671, column: 7, scope: !2505)
!2505 = distinct !DILexicalBlock(scope: !1751, file: !1, line: 671, column: 6)
!2506 = !DILocation(line: 671, column: 6, scope: !1751)
!2507 = !DILocation(line: 673, column: 5, scope: !2505)
!2508 = !DILocation(line: 676, column: 6, scope: !2509)
!2509 = distinct !DILexicalBlock(scope: !1751, file: !1, line: 676, column: 6)
!2510 = !DILocation(line: 676, column: 6, scope: !1751)
!2511 = !DILocation(line: 679, column: 5, scope: !2512)
!2512 = distinct !DILexicalBlock(scope: !2509, file: !1, line: 676, column: 20)
!2513 = !DILocation(line: 680, column: 3, scope: !2512)
!2514 = !DILocation(line: 690, column: 6, scope: !2515)
!2515 = distinct !DILexicalBlock(scope: !1751, file: !1, line: 690, column: 6)
!2516 = !DILocation(line: 690, column: 6, scope: !1751)
!2517 = !DILocalVariable(name: "elapsed_ms", scope: !2518, file: !1, line: 692, type: !349)
!2518 = distinct !DILexicalBlock(scope: !2515, file: !1, line: 690, column: 18)
!2519 = !DILocation(line: 692, column: 19, scope: !2518)
!2520 = !DILocation(line: 692, column: 32, scope: !2518)
!2521 = !DILocation(line: 692, column: 32, scope: !2522)
!2522 = !DILexicalBlockFile(scope: !2518, file: !1, discriminator: 1)
!2523 = !DILocalVariable(name: "alarm_set", scope: !2518, file: !1, line: 695, type: !349)
!2524 = !DILocation(line: 695, column: 19, scope: !2518)
!2525 = !DILocation(line: 695, column: 31, scope: !2518)
!2526 = !DILocation(line: 695, column: 44, scope: !2518)
!2527 = !DILocation(line: 695, column: 54, scope: !2518)
!2528 = !DILocation(line: 695, column: 42, scope: !2518)
!2529 = !DILocation(line: 697, column: 9, scope: !2530)
!2530 = distinct !DILexicalBlock(scope: !2518, file: !1, line: 697, column: 8)
!2531 = !DILocation(line: 697, column: 19, scope: !2530)
!2532 = !DILocation(line: 698, column: 10, scope: !2530)
!2533 = !DILocation(line: 698, column: 20, scope: !2530)
!2534 = !DILocation(line: 698, column: 35, scope: !2530)
!2535 = !DILocation(line: 698, column: 39, scope: !2536)
!2536 = !DILexicalBlockFile(scope: !2530, file: !1, discriminator: 1)
!2537 = !DILocation(line: 698, column: 50, scope: !2536)
!2538 = !DILocation(line: 697, column: 8, scope: !2522)
!2539 = !DILocation(line: 703, column: 7, scope: !2540)
!2540 = distinct !DILexicalBlock(scope: !2530, file: !1, line: 698, column: 67)
!2541 = !DILocation(line: 704, column: 10, scope: !2540)
!2542 = !DILocation(line: 705, column: 13, scope: !2540)
!2543 = !DILocation(line: 705, column: 7, scope: !2540)
!2544 = !DILocation(line: 706, column: 5, scope: !2540)
!2545 = !DILocation(line: 708, column: 27, scope: !2530)
!2546 = !DILocation(line: 708, column: 13, scope: !2530)
!2547 = !DILocation(line: 708, column: 7, scope: !2530)
!2548 = !DILocation(line: 709, column: 3, scope: !2518)
!2549 = !DILocation(line: 712, column: 10, scope: !1751)
!2550 = !DILocation(line: 712, column: 3, scope: !1751)
!2551 = !DILocation(line: 713, column: 1, scope: !1751)
!2552 = !DILocalVariable(name: "sig", arg: 1, scope: !1776, file: !1, line: 536, type: !316)
!2553 = !DILocation(line: 536, column: 26, scope: !1776)
!2554 = !DILocation(line: 539, column: 9, scope: !1776)
!2555 = !DILocation(line: 540, column: 3, scope: !1776)
!2556 = !DILocation(line: 542, column: 1, scope: !1776)
!2557 = !DILocalVariable(name: "data", arg: 1, scope: !1754, file: !1, line: 722, type: !256)
!2558 = !DILocation(line: 722, column: 43, scope: !1754)
!2559 = !DILocalVariable(name: "dns", arg: 2, scope: !1754, file: !1, line: 722, type: !1310)
!2560 = !DILocation(line: 722, column: 72, scope: !1754)
!2561 = !DILocation(line: 724, column: 6, scope: !2562)
!2562 = distinct !DILexicalBlock(scope: !1754, file: !1, line: 724, column: 6)
!2563 = !DILocation(line: 724, column: 11, scope: !2562)
!2564 = !DILocation(line: 724, column: 14, scope: !2565)
!2565 = !DILexicalBlockFile(scope: !2562, file: !1, discriminator: 1)
!2566 = !DILocation(line: 724, column: 20, scope: !2565)
!2567 = !DILocation(line: 724, column: 6, scope: !2565)
!2568 = !DILocation(line: 725, column: 21, scope: !2562)
!2569 = !DILocation(line: 725, column: 5, scope: !2562)
!2570 = !DILocation(line: 727, column: 16, scope: !1754)
!2571 = !DILocation(line: 727, column: 3, scope: !1754)
!2572 = !DILocation(line: 729, column: 6, scope: !2573)
!2573 = distinct !DILexicalBlock(scope: !1754, file: !1, line: 729, column: 6)
!2574 = !DILocation(line: 729, column: 11, scope: !2573)
!2575 = !DILocation(line: 729, column: 14, scope: !2576)
!2576 = !DILexicalBlockFile(scope: !2573, file: !1, discriminator: 1)
!2577 = !DILocation(line: 729, column: 20, scope: !2576)
!2578 = !DILocation(line: 729, column: 6, scope: !2576)
!2579 = !DILocation(line: 730, column: 23, scope: !2573)
!2580 = !DILocation(line: 730, column: 5, scope: !2573)
!2581 = !DILocation(line: 731, column: 1, scope: !1754)
!2582 = !DILocalVariable(name: "hash", arg: 1, scope: !1757, file: !1, line: 751, type: !324)
!2583 = !DILocation(line: 751, column: 40, scope: !1757)
!2584 = !DILocation(line: 753, column: 25, scope: !1757)
!2585 = !DILocation(line: 753, column: 10, scope: !1757)
!2586 = !DILocation(line: 753, column: 3, scope: !1757)
!2587 = !DILocalVariable(name: "data", arg: 1, scope: !1760, file: !1, line: 764, type: !256)
!2588 = !DILocation(line: 764, column: 45, scope: !1760)
!2589 = !DILocalVariable(name: "hash", arg: 2, scope: !1760, file: !1, line: 765, type: !324)
!2590 = !DILocation(line: 765, column: 45, scope: !1760)
!2591 = !DILocation(line: 767, column: 6, scope: !2592)
!2592 = distinct !DILexicalBlock(scope: !1760, file: !1, line: 767, column: 6)
!2593 = !DILocation(line: 767, column: 11, scope: !2592)
!2594 = !DILocation(line: 767, column: 14, scope: !2595)
!2595 = !DILexicalBlockFile(scope: !2592, file: !1, discriminator: 1)
!2596 = !DILocation(line: 767, column: 20, scope: !2595)
!2597 = !DILocation(line: 767, column: 6, scope: !2595)
!2598 = !DILocation(line: 768, column: 21, scope: !2592)
!2599 = !DILocation(line: 768, column: 5, scope: !2592)
!2600 = !DILocation(line: 770, column: 19, scope: !1760)
!2601 = !DILocation(line: 770, column: 3, scope: !1760)
!2602 = !DILocation(line: 772, column: 6, scope: !2603)
!2603 = distinct !DILexicalBlock(scope: !1760, file: !1, line: 772, column: 6)
!2604 = !DILocation(line: 772, column: 11, scope: !2603)
!2605 = !DILocation(line: 772, column: 14, scope: !2606)
!2606 = !DILexicalBlockFile(scope: !2603, file: !1, discriminator: 1)
!2607 = !DILocation(line: 772, column: 20, scope: !2606)
!2608 = !DILocation(line: 772, column: 6, scope: !2606)
!2609 = !DILocation(line: 773, column: 23, scope: !2603)
!2610 = !DILocation(line: 773, column: 5, scope: !2603)
!2611 = !DILocation(line: 774, column: 1, scope: !1760)
!2612 = !DILocalVariable(name: "data", arg: 1, scope: !1763, file: !1, line: 777, type: !256)
!2613 = !DILocation(line: 777, column: 47, scope: !1763)
!2614 = !DILocalVariable(name: "hostp", scope: !1763, file: !1, line: 779, type: !817)
!2615 = !DILocation(line: 779, column: 22, scope: !1763)
!2616 = !DILocalVariable(name: "hostname", scope: !1763, file: !1, line: 780, type: !1528)
!2617 = !DILocation(line: 780, column: 8, scope: !1763)
!2618 = !DILocalVariable(name: "address", scope: !1763, file: !1, line: 781, type: !1528)
!2619 = !DILocation(line: 781, column: 8, scope: !1763)
!2620 = !DILocalVariable(name: "port", scope: !1763, file: !1, line: 782, type: !316)
!2621 = !DILocation(line: 782, column: 7, scope: !1763)
!2622 = !DILocation(line: 784, column: 15, scope: !2623)
!2623 = distinct !DILexicalBlock(scope: !1763, file: !1, line: 784, column: 3)
!2624 = !DILocation(line: 784, column: 21, scope: !2623)
!2625 = !DILocation(line: 784, column: 28, scope: !2623)
!2626 = !DILocation(line: 784, column: 13, scope: !2623)
!2627 = !DILocation(line: 784, column: 7, scope: !2623)
!2628 = !DILocation(line: 784, column: 37, scope: !2629)
!2629 = !DILexicalBlockFile(scope: !2630, file: !1, discriminator: 1)
!2630 = distinct !DILexicalBlock(scope: !2623, file: !1, line: 784, column: 3)
!2631 = !DILocation(line: 784, column: 3, scope: !2629)
!2632 = !DILocation(line: 785, column: 9, scope: !2633)
!2633 = distinct !DILexicalBlock(scope: !2634, file: !1, line: 785, column: 8)
!2634 = distinct !DILexicalBlock(scope: !2630, file: !1, line: 784, column: 65)
!2635 = !DILocation(line: 785, column: 16, scope: !2633)
!2636 = !DILocation(line: 785, column: 8, scope: !2634)
!2637 = !DILocation(line: 786, column: 7, scope: !2633)
!2638 = !DILocation(line: 787, column: 8, scope: !2639)
!2639 = distinct !DILexicalBlock(scope: !2634, file: !1, line: 787, column: 8)
!2640 = !DILocation(line: 787, column: 15, scope: !2639)
!2641 = !DILocation(line: 787, column: 23, scope: !2639)
!2642 = !DILocation(line: 787, column: 8, scope: !2634)
!2643 = !DILocalVariable(name: "entry_id", scope: !2644, file: !1, line: 788, type: !500)
!2644 = distinct !DILexicalBlock(scope: !2639, file: !1, line: 787, column: 31)
!2645 = !DILocation(line: 788, column: 13, scope: !2644)
!2646 = !DILocalVariable(name: "entry_len", scope: !2644, file: !1, line: 789, type: !347)
!2647 = !DILocation(line: 789, column: 14, scope: !2644)
!2648 = !DILocation(line: 791, column: 22, scope: !2649)
!2649 = distinct !DILexicalBlock(scope: !2644, file: !1, line: 791, column: 10)
!2650 = !DILocation(line: 791, column: 29, scope: !2649)
!2651 = !DILocation(line: 791, column: 34, scope: !2649)
!2652 = !DILocation(line: 791, column: 54, scope: !2649)
!2653 = !DILocation(line: 791, column: 15, scope: !2649)
!2654 = !DILocation(line: 791, column: 12, scope: !2649)
!2655 = !DILocation(line: 791, column: 10, scope: !2644)
!2656 = !DILocation(line: 792, column: 15, scope: !2657)
!2657 = distinct !DILexicalBlock(scope: !2649, file: !1, line: 791, column: 72)
!2658 = !DILocation(line: 793, column: 15, scope: !2657)
!2659 = !DILocation(line: 793, column: 22, scope: !2657)
!2660 = !DILocation(line: 792, column: 9, scope: !2657)
!2661 = !DILocation(line: 794, column: 9, scope: !2657)
!2662 = !DILocation(line: 798, column: 38, scope: !2644)
!2663 = !DILocation(line: 798, column: 48, scope: !2644)
!2664 = !DILocation(line: 798, column: 18, scope: !2644)
!2665 = !DILocation(line: 798, column: 16, scope: !2644)
!2666 = !DILocation(line: 800, column: 11, scope: !2667)
!2667 = distinct !DILexicalBlock(scope: !2644, file: !1, line: 800, column: 10)
!2668 = !DILocation(line: 800, column: 10, scope: !2644)
!2669 = !DILocation(line: 801, column: 9, scope: !2670)
!2670 = distinct !DILexicalBlock(scope: !2667, file: !1, line: 800, column: 21)
!2671 = !DILocation(line: 804, column: 26, scope: !2644)
!2672 = !DILocation(line: 804, column: 19, scope: !2644)
!2673 = !DILocation(line: 804, column: 17, scope: !2644)
!2674 = !DILocation(line: 806, column: 10, scope: !2675)
!2675 = distinct !DILexicalBlock(scope: !2644, file: !1, line: 806, column: 10)
!2676 = !DILocation(line: 806, column: 16, scope: !2675)
!2677 = !DILocation(line: 806, column: 10, scope: !2644)
!2678 = !DILocation(line: 807, column: 25, scope: !2675)
!2679 = !DILocation(line: 807, column: 9, scope: !2675)
!2680 = !DILocation(line: 810, column: 24, scope: !2644)
!2681 = !DILocation(line: 810, column: 30, scope: !2644)
!2682 = !DILocation(line: 810, column: 34, scope: !2644)
!2683 = !DILocation(line: 810, column: 45, scope: !2644)
!2684 = !DILocation(line: 810, column: 55, scope: !2644)
!2685 = !DILocation(line: 810, column: 64, scope: !2644)
!2686 = !DILocation(line: 810, column: 7, scope: !2644)
!2687 = !DILocation(line: 812, column: 10, scope: !2688)
!2688 = distinct !DILexicalBlock(scope: !2644, file: !1, line: 812, column: 10)
!2689 = !DILocation(line: 812, column: 16, scope: !2688)
!2690 = !DILocation(line: 812, column: 10, scope: !2644)
!2691 = !DILocation(line: 813, column: 27, scope: !2688)
!2692 = !DILocation(line: 813, column: 9, scope: !2688)
!2693 = !DILocation(line: 816, column: 7, scope: !2644)
!2694 = !DILocation(line: 817, column: 5, scope: !2644)
!2695 = !DILocalVariable(name: "dns", scope: !2696, file: !1, line: 819, type: !1310)
!2696 = distinct !DILexicalBlock(scope: !2639, file: !1, line: 818, column: 10)
!2697 = !DILocation(line: 819, column: 30, scope: !2696)
!2698 = !DILocalVariable(name: "addr", scope: !2696, file: !1, line: 820, type: !1315)
!2699 = !DILocation(line: 820, column: 22, scope: !2696)
!2700 = !DILocalVariable(name: "entry_id", scope: !2696, file: !1, line: 821, type: !500)
!2701 = !DILocation(line: 821, column: 13, scope: !2696)
!2702 = !DILocalVariable(name: "entry_len", scope: !2696, file: !1, line: 822, type: !347)
!2703 = !DILocation(line: 822, column: 14, scope: !2696)
!2704 = !DILocation(line: 824, column: 22, scope: !2705)
!2705 = distinct !DILexicalBlock(scope: !2696, file: !1, line: 824, column: 10)
!2706 = !DILocation(line: 824, column: 29, scope: !2705)
!2707 = !DILocation(line: 824, column: 56, scope: !2705)
!2708 = !DILocation(line: 825, column: 22, scope: !2705)
!2709 = !DILocation(line: 824, column: 15, scope: !2705)
!2710 = !DILocation(line: 824, column: 12, scope: !2705)
!2711 = !DILocation(line: 824, column: 10, scope: !2696)
!2712 = !DILocation(line: 826, column: 15, scope: !2713)
!2713 = distinct !DILexicalBlock(scope: !2705, file: !1, line: 825, column: 32)
!2714 = !DILocation(line: 827, column: 15, scope: !2713)
!2715 = !DILocation(line: 827, column: 22, scope: !2713)
!2716 = !DILocation(line: 826, column: 9, scope: !2713)
!2717 = !DILocation(line: 828, column: 9, scope: !2713)
!2718 = !DILocation(line: 831, column: 28, scope: !2696)
!2719 = !DILocation(line: 831, column: 37, scope: !2696)
!2720 = !DILocation(line: 831, column: 14, scope: !2696)
!2721 = !DILocation(line: 831, column: 12, scope: !2696)
!2722 = !DILocation(line: 832, column: 11, scope: !2723)
!2723 = distinct !DILexicalBlock(scope: !2696, file: !1, line: 832, column: 10)
!2724 = !DILocation(line: 832, column: 10, scope: !2696)
!2725 = !DILocation(line: 833, column: 15, scope: !2726)
!2726 = distinct !DILexicalBlock(scope: !2723, file: !1, line: 832, column: 17)
!2727 = !DILocation(line: 833, column: 57, scope: !2726)
!2728 = !DILocation(line: 833, column: 64, scope: !2726)
!2729 = !DILocation(line: 833, column: 9, scope: !2726)
!2730 = !DILocation(line: 834, column: 9, scope: !2726)
!2731 = !DILocation(line: 838, column: 38, scope: !2696)
!2732 = !DILocation(line: 838, column: 48, scope: !2696)
!2733 = !DILocation(line: 838, column: 18, scope: !2696)
!2734 = !DILocation(line: 838, column: 16, scope: !2696)
!2735 = !DILocation(line: 840, column: 11, scope: !2736)
!2736 = distinct !DILexicalBlock(scope: !2696, file: !1, line: 840, column: 10)
!2737 = !DILocation(line: 840, column: 10, scope: !2696)
!2738 = !DILocation(line: 841, column: 27, scope: !2739)
!2739 = distinct !DILexicalBlock(scope: !2736, file: !1, line: 840, column: 21)
!2740 = !DILocation(line: 841, column: 9, scope: !2739)
!2741 = !DILocation(line: 842, column: 9, scope: !2739)
!2742 = !DILocation(line: 845, column: 26, scope: !2696)
!2743 = !DILocation(line: 845, column: 19, scope: !2696)
!2744 = !DILocation(line: 845, column: 17, scope: !2696)
!2745 = !DILocation(line: 847, column: 10, scope: !2746)
!2746 = distinct !DILexicalBlock(scope: !2696, file: !1, line: 847, column: 10)
!2747 = !DILocation(line: 847, column: 16, scope: !2746)
!2748 = !DILocation(line: 847, column: 10, scope: !2696)
!2749 = !DILocation(line: 848, column: 25, scope: !2746)
!2750 = !DILocation(line: 848, column: 9, scope: !2746)
!2751 = !DILocation(line: 851, column: 28, scope: !2696)
!2752 = !DILocation(line: 851, column: 34, scope: !2696)
!2753 = !DILocation(line: 851, column: 38, scope: !2696)
!2754 = !DILocation(line: 851, column: 49, scope: !2696)
!2755 = !DILocation(line: 851, column: 59, scope: !2696)
!2756 = !DILocation(line: 851, column: 68, scope: !2696)
!2757 = !DILocation(line: 851, column: 13, scope: !2696)
!2758 = !DILocation(line: 851, column: 11, scope: !2696)
!2759 = !DILocation(line: 854, column: 7, scope: !2696)
!2760 = !DILocation(line: 856, column: 11, scope: !2761)
!2761 = distinct !DILexicalBlock(scope: !2696, file: !1, line: 856, column: 10)
!2762 = !DILocation(line: 856, column: 10, scope: !2696)
!2763 = !DILocation(line: 858, column: 31, scope: !2764)
!2764 = distinct !DILexicalBlock(scope: !2761, file: !1, line: 856, column: 16)
!2765 = !DILocation(line: 858, column: 37, scope: !2764)
!2766 = !DILocation(line: 858, column: 43, scope: !2764)
!2767 = !DILocation(line: 858, column: 53, scope: !2764)
!2768 = !DILocation(line: 858, column: 15, scope: !2764)
!2769 = !DILocation(line: 858, column: 13, scope: !2764)
!2770 = !DILocation(line: 859, column: 12, scope: !2771)
!2771 = distinct !DILexicalBlock(scope: !2764, file: !1, line: 859, column: 12)
!2772 = !DILocation(line: 859, column: 12, scope: !2764)
!2773 = !DILocation(line: 860, column: 11, scope: !2774)
!2774 = distinct !DILexicalBlock(scope: !2771, file: !1, line: 859, column: 17)
!2775 = !DILocation(line: 860, column: 16, scope: !2774)
!2776 = !DILocation(line: 860, column: 26, scope: !2774)
!2777 = !DILocation(line: 863, column: 11, scope: !2774)
!2778 = !DILocation(line: 863, column: 16, scope: !2774)
!2779 = !DILocation(line: 863, column: 21, scope: !2774)
!2780 = !DILocation(line: 864, column: 9, scope: !2774)
!2781 = !DILocation(line: 865, column: 7, scope: !2764)
!2782 = !DILocation(line: 868, column: 27, scope: !2761)
!2783 = !DILocation(line: 868, column: 9, scope: !2761)
!2784 = !DILocation(line: 870, column: 10, scope: !2785)
!2785 = distinct !DILexicalBlock(scope: !2696, file: !1, line: 870, column: 10)
!2786 = !DILocation(line: 870, column: 16, scope: !2785)
!2787 = !DILocation(line: 870, column: 10, scope: !2696)
!2788 = !DILocation(line: 871, column: 27, scope: !2785)
!2789 = !DILocation(line: 871, column: 9, scope: !2785)
!2790 = !DILocation(line: 873, column: 11, scope: !2791)
!2791 = distinct !DILexicalBlock(scope: !2696, file: !1, line: 873, column: 10)
!2792 = !DILocation(line: 873, column: 10, scope: !2696)
!2793 = !DILocation(line: 874, column: 27, scope: !2794)
!2794 = distinct !DILexicalBlock(scope: !2791, file: !1, line: 873, column: 16)
!2795 = !DILocation(line: 874, column: 9, scope: !2794)
!2796 = !DILocation(line: 875, column: 9, scope: !2794)
!2797 = !DILocation(line: 877, column: 13, scope: !2696)
!2798 = !DILocation(line: 878, column: 13, scope: !2696)
!2799 = !DILocation(line: 878, column: 23, scope: !2696)
!2800 = !DILocation(line: 878, column: 29, scope: !2696)
!2801 = !DILocation(line: 877, column: 7, scope: !2696)
!2802 = !DILocation(line: 880, column: 3, scope: !2634)
!2803 = !DILocation(line: 784, column: 52, scope: !2804)
!2804 = !DILexicalBlockFile(scope: !2630, file: !1, discriminator: 2)
!2805 = !DILocation(line: 784, column: 59, scope: !2804)
!2806 = !DILocation(line: 784, column: 50, scope: !2804)
!2807 = !DILocation(line: 784, column: 3, scope: !2804)
!2808 = !DILocation(line: 881, column: 3, scope: !1763)
!2809 = !DILocation(line: 881, column: 9, scope: !1763)
!2810 = !DILocation(line: 881, column: 16, scope: !1763)
!2811 = !DILocation(line: 881, column: 24, scope: !1763)
!2812 = !DILocation(line: 883, column: 3, scope: !1763)
!2813 = !DILocation(line: 884, column: 1, scope: !1763)
!2814 = !DILocalVariable(name: "datap", arg: 1, scope: !1769, file: !1, line: 227, type: !311)
!2815 = !DILocation(line: 227, column: 34, scope: !1769)
!2816 = !DILocalVariable(name: "hc", arg: 2, scope: !1769, file: !1, line: 227, type: !311)
!2817 = !DILocation(line: 227, column: 47, scope: !1769)
!2818 = !DILocalVariable(name: "data", scope: !1769, file: !1, line: 229, type: !1717)
!2819 = !DILocation(line: 229, column: 32, scope: !1769)
!2820 = !DILocation(line: 230, column: 37, scope: !1769)
!2821 = !DILocation(line: 230, column: 5, scope: !1769)
!2822 = !DILocalVariable(name: "c", scope: !1769, file: !1, line: 231, type: !1310)
!2823 = !DILocation(line: 231, column: 26, scope: !1769)
!2824 = !DILocation(line: 231, column: 56, scope: !1769)
!2825 = !DILocation(line: 231, column: 30, scope: !1769)
!2826 = !DILocation(line: 233, column: 16, scope: !1769)
!2827 = !DILocation(line: 233, column: 19, scope: !1769)
!2828 = !DILocation(line: 233, column: 13, scope: !1769)
!2829 = !DILocation(line: 234, column: 5, scope: !1769)
!2830 = !DILocation(line: 234, column: 9, scope: !2831)
!2831 = !DILexicalBlockFile(scope: !1769, file: !1, discriminator: 1)
!2832 = !DILocation(line: 234, column: 15, scope: !2831)
!2833 = !DILocation(line: 234, column: 21, scope: !2831)
!2834 = !DILocation(line: 234, column: 24, scope: !2831)
!2835 = !DILocation(line: 234, column: 19, scope: !2831)
!2836 = !DILocation(line: 234, column: 37, scope: !2831)
!2837 = !DILocation(line: 234, column: 43, scope: !2831)
!2838 = !DILocation(line: 234, column: 34, scope: !2831)
!2839 = !DILocation(line: 234, column: 5, scope: !2840)
!2840 = !DILexicalBlockFile(scope: !1769, file: !1, discriminator: 2)
!2841 = !DILocation(line: 233, column: 3, scope: !2831)
