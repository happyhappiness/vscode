; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/easy.c'
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
%struct.__va_list_tag = type { i32, i32, i8*, i8* }
%struct.curl_waitfd = type { i32, i16, i16 }

@Curl_cmalloc = global i8* (i64)* @malloc, align 8
@Curl_cfree = global void (i8*)* @free, align 8
@Curl_crealloc = global i8* (i8*, i64)* @realloc, align 8
@Curl_cstrdup = global i8* (i8*)* @strdup, align 8
@Curl_ccalloc = global i8* (i64, i64)* @calloc, align 8
@initialized = internal global i32 0, align 4
@init_flags = internal global i64 0, align 8
@Curl_ack_eintr = external global i32, align 4
@.str = private unnamed_addr constant [41 x i8] c"easy handle already used in multi handle\00", align 1
@.str.1 = private unnamed_addr constant [26 x i8] c"CONNECT_ONLY is required!\00", align 1
@.str.2 = private unnamed_addr constant [28 x i8] c"Failed to get recent socket\00", align 1

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #0

; Function Attrs: nounwind
declare void @free(i8*) #0

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #0

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #0

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #0

; Function Attrs: nounwind uwtable
define i32 @curl_global_init(i64 %flags) #1 !dbg !2068 {
entry:
  %flags.addr = alloca i64, align 8
  store i64 %flags, i64* %flags.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %flags.addr, metadata !2137, metadata !2138), !dbg !2139
  %0 = load i64, i64* %flags.addr, align 8, !dbg !2140
  %call = call i32 @global_init(i64 %0, i1 zeroext true), !dbg !2141
  ret i32 %call, !dbg !2142
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #2

; Function Attrs: nounwind uwtable
define internal i32 @global_init(i64 %flags, i1 zeroext %memoryfuncs) #1 !dbg !2109 {
entry:
  %retval = alloca i32, align 4
  %flags.addr = alloca i64, align 8
  %memoryfuncs.addr = alloca i8, align 1
  store i64 %flags, i64* %flags.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %flags.addr, metadata !2143, metadata !2138), !dbg !2144
  %frombool = zext i1 %memoryfuncs to i8
  store i8 %frombool, i8* %memoryfuncs.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %memoryfuncs.addr, metadata !2145, metadata !2138), !dbg !2146
  %0 = load i32, i32* @initialized, align 4, !dbg !2147
  %inc = add i32 %0, 1, !dbg !2147
  store i32 %inc, i32* @initialized, align 4, !dbg !2147
  %tobool = icmp ne i32 %0, 0, !dbg !2147
  br i1 %tobool, label %if.then, label %if.end, !dbg !2149

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2150
  br label %return, !dbg !2150

if.end:                                           ; preds = %entry
  %1 = load i8, i8* %memoryfuncs.addr, align 1, !dbg !2151
  %tobool1 = trunc i8 %1 to i1, !dbg !2151
  br i1 %tobool1, label %if.then2, label %if.end3, !dbg !2153

if.then2:                                         ; preds = %if.end
  store i8* (i64)* @malloc, i8* (i64)** @Curl_cmalloc, align 8, !dbg !2154
  store void (i8*)* @free, void (i8*)** @Curl_cfree, align 8, !dbg !2156
  store i8* (i8*, i64)* @realloc, i8* (i8*, i64)** @Curl_crealloc, align 8, !dbg !2157
  store i8* (i8*)* @strdup, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !2158
  store i8* (i64, i64)* @calloc, i8* (i64, i64)** @Curl_ccalloc, align 8, !dbg !2159
  br label %if.end3, !dbg !2160

if.end3:                                          ; preds = %if.then2, %if.end
  %2 = load i64, i64* %flags.addr, align 8, !dbg !2161
  %and = and i64 %2, 1, !dbg !2163
  %tobool4 = icmp ne i64 %and, 0, !dbg !2163
  br i1 %tobool4, label %if.then5, label %if.end6, !dbg !2164

if.then5:                                         ; preds = %if.end3
  br label %if.end6, !dbg !2165

if.end6:                                          ; preds = %if.then5, %if.end3
  %3 = load i64, i64* %flags.addr, align 8, !dbg !2167
  %and7 = and i64 %3, 2, !dbg !2169
  %tobool8 = icmp ne i64 %and7, 0, !dbg !2169
  br i1 %tobool8, label %if.then9, label %if.end13, !dbg !2170

if.then9:                                         ; preds = %if.end6
  %call = call i32 @win32_init(), !dbg !2171
  %tobool10 = icmp ne i32 %call, 0, !dbg !2171
  br i1 %tobool10, label %if.then11, label %if.end12, !dbg !2173

if.then11:                                        ; preds = %if.then9
  br label %do.body, !dbg !2174

do.body:                                          ; preds = %if.then11
  br label %do.end, !dbg !2176

do.end:                                           ; preds = %do.body
  store i32 2, i32* %retval, align 4, !dbg !2179
  br label %return, !dbg !2179

if.end12:                                         ; preds = %if.then9
  br label %if.end13, !dbg !2180

if.end13:                                         ; preds = %if.end12, %if.end6
  %4 = load i64, i64* %flags.addr, align 8, !dbg !2182
  %and14 = and i64 %4, 4, !dbg !2184
  %tobool15 = icmp ne i64 %and14, 0, !dbg !2184
  br i1 %tobool15, label %if.then16, label %if.end17, !dbg !2185

if.then16:                                        ; preds = %if.end13
  store i32 1, i32* @Curl_ack_eintr, align 4, !dbg !2186
  br label %if.end17, !dbg !2187

if.end17:                                         ; preds = %if.then16, %if.end13
  %5 = load i64, i64* %flags.addr, align 8, !dbg !2188
  store i64 %5, i64* @init_flags, align 8, !dbg !2189
  call void @Curl_version_init(), !dbg !2190
  store i32 0, i32* %retval, align 4, !dbg !2191
  br label %return, !dbg !2191

return:                                           ; preds = %if.end17, %do.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !2192
  ret i32 %6, !dbg !2192
}

; Function Attrs: nounwind uwtable
define i32 @curl_global_init_mem(i64 %flags, i8* (i64)* %m, void (i8*)* %f, i8* (i8*, i64)* %r, i8* (i8*)* %s, i8* (i64, i64)* %c) #1 !dbg !2072 {
entry:
  %retval = alloca i32, align 4
  %flags.addr = alloca i64, align 8
  %m.addr = alloca i8* (i64)*, align 8
  %f.addr = alloca void (i8*)*, align 8
  %r.addr = alloca i8* (i8*, i64)*, align 8
  %s.addr = alloca i8* (i8*)*, align 8
  %c.addr = alloca i8* (i64, i64)*, align 8
  store i64 %flags, i64* %flags.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %flags.addr, metadata !2193, metadata !2138), !dbg !2194
  store i8* (i64)* %m, i8* (i64)** %m.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (i64)** %m.addr, metadata !2195, metadata !2138), !dbg !2196
  store void (i8*)* %f, void (i8*)** %f.addr, align 8
  call void @llvm.dbg.declare(metadata void (i8*)** %f.addr, metadata !2197, metadata !2138), !dbg !2198
  store i8* (i8*, i64)* %r, i8* (i8*, i64)** %r.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (i8*, i64)** %r.addr, metadata !2199, metadata !2138), !dbg !2200
  store i8* (i8*)* %s, i8* (i8*)** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (i8*)** %s.addr, metadata !2201, metadata !2138), !dbg !2202
  store i8* (i64, i64)* %c, i8* (i64, i64)** %c.addr, align 8
  call void @llvm.dbg.declare(metadata i8* (i64, i64)** %c.addr, metadata !2203, metadata !2138), !dbg !2204
  %0 = load i8* (i64)*, i8* (i64)** %m.addr, align 8, !dbg !2205
  %tobool = icmp ne i8* (i64)* %0, null, !dbg !2205
  br i1 %tobool, label %lor.lhs.false, label %if.then, !dbg !2207

lor.lhs.false:                                    ; preds = %entry
  %1 = load void (i8*)*, void (i8*)** %f.addr, align 8, !dbg !2208
  %tobool1 = icmp ne void (i8*)* %1, null, !dbg !2208
  br i1 %tobool1, label %lor.lhs.false2, label %if.then, !dbg !2210

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i8* (i8*, i64)*, i8* (i8*, i64)** %r.addr, align 8, !dbg !2211
  %tobool3 = icmp ne i8* (i8*, i64)* %2, null, !dbg !2211
  br i1 %tobool3, label %lor.lhs.false4, label %if.then, !dbg !2213

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %3 = load i8* (i8*)*, i8* (i8*)** %s.addr, align 8, !dbg !2214
  %tobool5 = icmp ne i8* (i8*)* %3, null, !dbg !2214
  br i1 %tobool5, label %lor.lhs.false6, label %if.then, !dbg !2216

lor.lhs.false6:                                   ; preds = %lor.lhs.false4
  %4 = load i8* (i64, i64)*, i8* (i64, i64)** %c.addr, align 8, !dbg !2217
  %tobool7 = icmp ne i8* (i64, i64)* %4, null, !dbg !2217
  br i1 %tobool7, label %if.end, label %if.then, !dbg !2219

if.then:                                          ; preds = %lor.lhs.false6, %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 2, i32* %retval, align 4, !dbg !2220
  br label %return, !dbg !2220

if.end:                                           ; preds = %lor.lhs.false6
  %5 = load i32, i32* @initialized, align 4, !dbg !2221
  %tobool8 = icmp ne i32 %5, 0, !dbg !2221
  br i1 %tobool8, label %if.then9, label %if.end10, !dbg !2223

if.then9:                                         ; preds = %if.end
  %6 = load i32, i32* @initialized, align 4, !dbg !2224
  %inc = add i32 %6, 1, !dbg !2224
  store i32 %inc, i32* @initialized, align 4, !dbg !2224
  store i32 0, i32* %retval, align 4, !dbg !2226
  br label %return, !dbg !2226

if.end10:                                         ; preds = %if.end
  %7 = load i8* (i64)*, i8* (i64)** %m.addr, align 8, !dbg !2227
  store i8* (i64)* %7, i8* (i64)** @Curl_cmalloc, align 8, !dbg !2228
  %8 = load void (i8*)*, void (i8*)** %f.addr, align 8, !dbg !2229
  store void (i8*)* %8, void (i8*)** @Curl_cfree, align 8, !dbg !2230
  %9 = load i8* (i8*)*, i8* (i8*)** %s.addr, align 8, !dbg !2231
  store i8* (i8*)* %9, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !2232
  %10 = load i8* (i8*, i64)*, i8* (i8*, i64)** %r.addr, align 8, !dbg !2233
  store i8* (i8*, i64)* %10, i8* (i8*, i64)** @Curl_crealloc, align 8, !dbg !2234
  %11 = load i8* (i64, i64)*, i8* (i64, i64)** %c.addr, align 8, !dbg !2235
  store i8* (i64, i64)* %11, i8* (i64, i64)** @Curl_ccalloc, align 8, !dbg !2236
  %12 = load i64, i64* %flags.addr, align 8, !dbg !2237
  %call = call i32 @global_init(i64 %12, i1 zeroext false), !dbg !2238
  store i32 %call, i32* %retval, align 4, !dbg !2239
  br label %return, !dbg !2239

return:                                           ; preds = %if.end10, %if.then9, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !2240
  ret i32 %13, !dbg !2240
}

; Function Attrs: nounwind uwtable
define void @curl_global_cleanup() #1 !dbg !2075 {
entry:
  %0 = load i32, i32* @initialized, align 4, !dbg !2241
  %tobool = icmp ne i32 %0, 0, !dbg !2241
  br i1 %tobool, label %if.end, label %if.then, !dbg !2243

if.then:                                          ; preds = %entry
  br label %return, !dbg !2244

if.end:                                           ; preds = %entry
  %1 = load i32, i32* @initialized, align 4, !dbg !2245
  %dec = add i32 %1, -1, !dbg !2245
  store i32 %dec, i32* @initialized, align 4, !dbg !2245
  %tobool1 = icmp ne i32 %dec, 0, !dbg !2245
  br i1 %tobool1, label %if.then2, label %if.end3, !dbg !2247

if.then2:                                         ; preds = %if.end
  br label %return, !dbg !2248

if.end3:                                          ; preds = %if.end
  call void @Curl_global_host_cache_dtor(), !dbg !2249
  %2 = load i64, i64* @init_flags, align 8, !dbg !2250
  %and = and i64 %2, 1, !dbg !2252
  %tobool4 = icmp ne i64 %and, 0, !dbg !2252
  br i1 %tobool4, label %if.then5, label %if.end6, !dbg !2253

if.then5:                                         ; preds = %if.end3
  br label %do.body, !dbg !2254

do.body:                                          ; preds = %if.then5
  br label %do.end, !dbg !2255

do.end:                                           ; preds = %do.body
  br label %if.end6, !dbg !2258

if.end6:                                          ; preds = %do.end, %if.end3
  br label %do.body7, !dbg !2260

do.body7:                                         ; preds = %if.end6
  br label %do.end8, !dbg !2261

do.end8:                                          ; preds = %do.body7
  %3 = load i64, i64* @init_flags, align 8, !dbg !2264
  %and9 = and i64 %3, 2, !dbg !2266
  %tobool10 = icmp ne i64 %and9, 0, !dbg !2266
  br i1 %tobool10, label %if.then11, label %if.end12, !dbg !2267

if.then11:                                        ; preds = %do.end8
  call void @win32_cleanup(), !dbg !2268
  br label %if.end12, !dbg !2268

if.end12:                                         ; preds = %if.then11, %do.end8
  br label %do.body13, !dbg !2269

do.body13:                                        ; preds = %if.end12
  br label %do.end14, !dbg !2270

do.end14:                                         ; preds = %do.body13
  store i64 0, i64* @init_flags, align 8, !dbg !2273
  br label %return, !dbg !2274

return:                                           ; preds = %do.end14, %if.then2, %if.then
  ret void, !dbg !2275
}

declare void @Curl_global_host_cache_dtor() #3

; Function Attrs: nounwind uwtable
define internal void @win32_cleanup() #1 !dbg !2115 {
entry:
  ret void, !dbg !2277
}

; Function Attrs: nounwind uwtable
define %struct.Curl_easy* @curl_easy_init() #1 !dbg !2078 {
entry:
  %retval = alloca %struct.Curl_easy*, align 8
  %result = alloca i32, align 4
  %data = alloca %struct.Curl_easy*, align 8
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2278, metadata !2138), !dbg !2279
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data, metadata !2280, metadata !2138), !dbg !2281
  %0 = load i32, i32* @initialized, align 4, !dbg !2282
  %tobool = icmp ne i32 %0, 0, !dbg !2282
  br i1 %tobool, label %if.end3, label %if.then, !dbg !2284

if.then:                                          ; preds = %entry
  %call = call i32 @curl_global_init(i64 3), !dbg !2285
  store i32 %call, i32* %result, align 4, !dbg !2287
  %1 = load i32, i32* %result, align 4, !dbg !2288
  %tobool1 = icmp ne i32 %1, 0, !dbg !2288
  br i1 %tobool1, label %if.then2, label %if.end, !dbg !2290

if.then2:                                         ; preds = %if.then
  br label %do.body, !dbg !2291

do.body:                                          ; preds = %if.then2
  br label %do.end, !dbg !2293

do.end:                                           ; preds = %do.body
  store %struct.Curl_easy* null, %struct.Curl_easy** %retval, align 8, !dbg !2296
  br label %return, !dbg !2296

if.end:                                           ; preds = %if.then
  br label %if.end3, !dbg !2297

if.end3:                                          ; preds = %if.end, %entry
  %call4 = call i32 @Curl_open(%struct.Curl_easy** %data), !dbg !2298
  store i32 %call4, i32* %result, align 4, !dbg !2299
  %2 = load i32, i32* %result, align 4, !dbg !2300
  %tobool5 = icmp ne i32 %2, 0, !dbg !2300
  br i1 %tobool5, label %if.then6, label %if.end9, !dbg !2302

if.then6:                                         ; preds = %if.end3
  br label %do.body7, !dbg !2303

do.body7:                                         ; preds = %if.then6
  br label %do.end8, !dbg !2305

do.end8:                                          ; preds = %do.body7
  store %struct.Curl_easy* null, %struct.Curl_easy** %retval, align 8, !dbg !2308
  br label %return, !dbg !2308

if.end9:                                          ; preds = %if.end3
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data, align 8, !dbg !2309
  store %struct.Curl_easy* %3, %struct.Curl_easy** %retval, align 8, !dbg !2310
  br label %return, !dbg !2310

return:                                           ; preds = %if.end9, %do.end8, %do.end
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %retval, align 8, !dbg !2311
  ret %struct.Curl_easy* %4, !dbg !2311
}

declare i32 @Curl_open(%struct.Curl_easy**) #3

; Function Attrs: nounwind uwtable
define i32 @curl_easy_setopt(%struct.Curl_easy* %data, i32 %tag, ...) #1 !dbg !2081 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %tag.addr = alloca i32, align 4
  %arg = alloca [1 x %struct.__va_list_tag], align 16
  %result = alloca i32, align 4
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2312, metadata !2138), !dbg !2313
  store i32 %tag, i32* %tag.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %tag.addr, metadata !2314, metadata !2138), !dbg !2315
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %arg, metadata !2316, metadata !2138), !dbg !2328
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2329, metadata !2138), !dbg !2330
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2331
  %tobool = icmp ne %struct.Curl_easy* %0, null, !dbg !2331
  br i1 %tobool, label %if.end, label %if.then, !dbg !2333

if.then:                                          ; preds = %entry
  store i32 43, i32* %retval, align 4, !dbg !2334
  br label %return, !dbg !2334

if.end:                                           ; preds = %entry
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !2335
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !2335
  call void @llvm.va_start(i8* %arraydecay1), !dbg !2335
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2336
  %2 = load i32, i32* %tag.addr, align 4, !dbg !2337
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !2338
  %call = call i32 @Curl_setopt(%struct.Curl_easy* %1, i32 %2, %struct.__va_list_tag* %arraydecay2), !dbg !2339
  store i32 %call, i32* %result, align 4, !dbg !2340
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !2341
  %arraydecay34 = bitcast %struct.__va_list_tag* %arraydecay3 to i8*, !dbg !2341
  call void @llvm.va_end(i8* %arraydecay34), !dbg !2341
  %3 = load i32, i32* %result, align 4, !dbg !2342
  store i32 %3, i32* %retval, align 4, !dbg !2343
  br label %return, !dbg !2343

return:                                           ; preds = %if.end, %if.then
  %4 = load i32, i32* %retval, align 4, !dbg !2344
  ret i32 %4, !dbg !2344
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #4

declare i32 @Curl_setopt(%struct.Curl_easy*, i32, %struct.__va_list_tag*) #3

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #4

; Function Attrs: nounwind uwtable
define i32 @curl_easy_perform(%struct.Curl_easy* %data) #1 !dbg !2085 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2345, metadata !2138), !dbg !2346
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2347
  %call = call i32 @easy_perform(%struct.Curl_easy* %0, i1 zeroext false), !dbg !2348
  ret i32 %call, !dbg !2349
}

; Function Attrs: nounwind uwtable
define internal i32 @easy_perform(%struct.Curl_easy* %data, i1 zeroext %events) #1 !dbg !2116 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %events.addr = alloca i8, align 1
  %multi = alloca %struct.Curl_multi*, align 8
  %mcode = alloca i32, align 4
  %result = alloca i32, align 4
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2350, metadata !2138), !dbg !2351
  %frombool = zext i1 %events to i8
  store i8 %frombool, i8* %events.addr, align 1
  call void @llvm.dbg.declare(metadata i8* %events.addr, metadata !2352, metadata !2138), !dbg !2353
  call void @llvm.dbg.declare(metadata %struct.Curl_multi** %multi, metadata !2354, metadata !2138), !dbg !2355
  call void @llvm.dbg.declare(metadata i32* %mcode, metadata !2356, metadata !2138), !dbg !2358
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2359, metadata !2138), !dbg !2360
  store i32 0, i32* %result, align 4, !dbg !2360
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2361
  %tobool = icmp ne %struct.Curl_easy* %0, null, !dbg !2361
  br i1 %tobool, label %if.end, label %if.then, !dbg !2363

if.then:                                          ; preds = %entry
  store i32 43, i32* %retval, align 4, !dbg !2364
  br label %return, !dbg !2364

if.end:                                           ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2365
  %multi1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 9, !dbg !2367
  %2 = load %struct.Curl_multi*, %struct.Curl_multi** %multi1, align 8, !dbg !2367
  %tobool2 = icmp ne %struct.Curl_multi* %2, null, !dbg !2365
  br i1 %tobool2, label %if.then3, label %if.end4, !dbg !2368

if.then3:                                         ; preds = %if.end
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2369
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %3, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str, i32 0, i32 0)), !dbg !2371
  store i32 2, i32* %retval, align 4, !dbg !2372
  br label %return, !dbg !2372

if.end4:                                          ; preds = %if.end
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2373
  %multi_easy = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 10, !dbg !2375
  %5 = load %struct.Curl_multi*, %struct.Curl_multi** %multi_easy, align 8, !dbg !2375
  %tobool5 = icmp ne %struct.Curl_multi* %5, null, !dbg !2373
  br i1 %tobool5, label %if.then6, label %if.else, !dbg !2376

if.then6:                                         ; preds = %if.end4
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2377
  %multi_easy7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %6, i32 0, i32 10, !dbg !2378
  %7 = load %struct.Curl_multi*, %struct.Curl_multi** %multi_easy7, align 8, !dbg !2378
  store %struct.Curl_multi* %7, %struct.Curl_multi** %multi, align 8, !dbg !2379
  br label %if.end12, !dbg !2380

if.else:                                          ; preds = %if.end4
  %call = call %struct.Curl_multi* @Curl_multi_handle(i32 1, i32 3), !dbg !2381
  store %struct.Curl_multi* %call, %struct.Curl_multi** %multi, align 8, !dbg !2383
  %8 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !2384
  %tobool8 = icmp ne %struct.Curl_multi* %8, null, !dbg !2384
  br i1 %tobool8, label %if.end10, label %if.then9, !dbg !2386

if.then9:                                         ; preds = %if.else
  store i32 27, i32* %retval, align 4, !dbg !2387
  br label %return, !dbg !2387

if.end10:                                         ; preds = %if.else
  %9 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !2388
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2389
  %multi_easy11 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 10, !dbg !2390
  store %struct.Curl_multi* %9, %struct.Curl_multi** %multi_easy11, align 8, !dbg !2391
  br label %if.end12

if.end12:                                         ; preds = %if.end10, %if.then6
  %11 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !2392
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2393
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 13, !dbg !2394
  %maxconnects = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 146, !dbg !2395
  %13 = load i64, i64* %maxconnects, align 8, !dbg !2395
  %call13 = call i32 (%struct.Curl_multi*, i32, ...) @curl_multi_setopt(%struct.Curl_multi* %11, i32 6, i64 %13), !dbg !2396
  %14 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !2397
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2398
  %call14 = call i32 @curl_multi_add_handle(%struct.Curl_multi* %14, %struct.Curl_easy* %15), !dbg !2399
  store i32 %call14, i32* %mcode, align 4, !dbg !2400
  %16 = load i32, i32* %mcode, align 4, !dbg !2401
  %tobool15 = icmp ne i32 %16, 0, !dbg !2401
  br i1 %tobool15, label %if.then16, label %if.end20, !dbg !2403

if.then16:                                        ; preds = %if.end12
  %17 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !2404
  %call17 = call i32 @curl_multi_cleanup(%struct.Curl_multi* %17), !dbg !2406
  %18 = load i32, i32* %mcode, align 4, !dbg !2407
  %cmp = icmp eq i32 %18, 3, !dbg !2409
  br i1 %cmp, label %if.then18, label %if.end19, !dbg !2410

if.then18:                                        ; preds = %if.then16
  store i32 27, i32* %retval, align 4, !dbg !2411
  br label %return, !dbg !2411

if.end19:                                         ; preds = %if.then16
  store i32 2, i32* %retval, align 4, !dbg !2412
  br label %return, !dbg !2412

if.end20:                                         ; preds = %if.end12
  br label %do.body, !dbg !2413

do.body:                                          ; preds = %if.end20
  br label %do.end, !dbg !2414

do.end:                                           ; preds = %do.body
  %19 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !2417
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2418
  %multi21 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %20, i32 0, i32 9, !dbg !2419
  store %struct.Curl_multi* %19, %struct.Curl_multi** %multi21, align 8, !dbg !2420
  %21 = load i8, i8* %events.addr, align 1, !dbg !2421
  %tobool22 = trunc i8 %21 to i1, !dbg !2421
  br i1 %tobool22, label %cond.true, label %cond.false, !dbg !2421

cond.true:                                        ; preds = %do.end
  br label %cond.end, !dbg !2422

cond.false:                                       ; preds = %do.end
  %22 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !2424
  %call23 = call i32 @easy_transfer(%struct.Curl_multi* %22), !dbg !2426
  br label %cond.end, !dbg !2427

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ 4, %cond.true ], [ %call23, %cond.false ], !dbg !2428
  store i32 %cond, i32* %result, align 4, !dbg !2430
  %23 = load %struct.Curl_multi*, %struct.Curl_multi** %multi, align 8, !dbg !2431
  %24 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2432
  %call24 = call i32 @curl_multi_remove_handle(%struct.Curl_multi* %23, %struct.Curl_easy* %24), !dbg !2433
  br label %do.body25, !dbg !2434

do.body25:                                        ; preds = %cond.end
  br label %do.end26, !dbg !2435

do.end26:                                         ; preds = %do.body25
  %25 = load i32, i32* %result, align 4, !dbg !2438
  store i32 %25, i32* %retval, align 4, !dbg !2439
  br label %return, !dbg !2439

return:                                           ; preds = %do.end26, %if.end19, %if.then18, %if.then9, %if.then3, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !2440
  ret i32 %26, !dbg !2440
}

; Function Attrs: nounwind uwtable
define void @curl_easy_cleanup(%struct.Curl_easy* %data) #1 !dbg !2088 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2441, metadata !2138), !dbg !2442
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2443
  %tobool = icmp ne %struct.Curl_easy* %0, null, !dbg !2443
  br i1 %tobool, label %if.end, label %if.then, !dbg !2445

if.then:                                          ; preds = %entry
  br label %do.end2, !dbg !2446

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !2447

do.body:                                          ; preds = %if.end
  br label %do.end, !dbg !2448

do.end:                                           ; preds = %do.body
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2451
  %call = call i32 @Curl_close(%struct.Curl_easy* %1), !dbg !2452
  br label %do.body1, !dbg !2453

do.body1:                                         ; preds = %do.end
  br label %do.end2, !dbg !2454

do.end2:                                          ; preds = %if.then, %do.body1
  ret void, !dbg !2457
}

declare i32 @Curl_close(%struct.Curl_easy*) #3

; Function Attrs: nounwind uwtable
define i32 @curl_easy_getinfo(%struct.Curl_easy* %data, i32 %info, ...) #1 !dbg !2091 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  %info.addr = alloca i32, align 4
  %arg = alloca [1 x %struct.__va_list_tag], align 16
  %paramp = alloca i8*, align 8
  %result = alloca i32, align 4
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2458, metadata !2138), !dbg !2459
  store i32 %info, i32* %info.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %info.addr, metadata !2460, metadata !2138), !dbg !2461
  call void @llvm.dbg.declare(metadata [1 x %struct.__va_list_tag]* %arg, metadata !2462, metadata !2138), !dbg !2463
  call void @llvm.dbg.declare(metadata i8** %paramp, metadata !2464, metadata !2138), !dbg !2465
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2466, metadata !2138), !dbg !2467
  %arraydecay = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !2468
  %arraydecay1 = bitcast %struct.__va_list_tag* %arraydecay to i8*, !dbg !2468
  call void @llvm.va_start(i8* %arraydecay1), !dbg !2468
  %arraydecay2 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !2469
  %gp_offset_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay2, i32 0, i32 0, !dbg !2469
  %gp_offset = load i32, i32* %gp_offset_p, align 16, !dbg !2469
  %fits_in_gp = icmp ule i32 %gp_offset, 40, !dbg !2469
  br i1 %fits_in_gp, label %vaarg.in_reg, label %vaarg.in_mem, !dbg !2469

vaarg.in_reg:                                     ; preds = %entry
  %0 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay2, i32 0, i32 3, !dbg !2470
  %reg_save_area = load i8*, i8** %0, align 16, !dbg !2470
  %1 = getelementptr i8, i8* %reg_save_area, i32 %gp_offset, !dbg !2470
  %2 = bitcast i8* %1 to i8**, !dbg !2470
  %3 = add i32 %gp_offset, 8, !dbg !2470
  store i32 %3, i32* %gp_offset_p, align 16, !dbg !2470
  br label %vaarg.end, !dbg !2470

vaarg.in_mem:                                     ; preds = %entry
  %overflow_arg_area_p = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %arraydecay2, i32 0, i32 2, !dbg !2472
  %overflow_arg_area = load i8*, i8** %overflow_arg_area_p, align 8, !dbg !2472
  %4 = bitcast i8* %overflow_arg_area to i8**, !dbg !2472
  %overflow_arg_area.next = getelementptr i8, i8* %overflow_arg_area, i32 8, !dbg !2472
  store i8* %overflow_arg_area.next, i8** %overflow_arg_area_p, align 8, !dbg !2472
  br label %vaarg.end, !dbg !2472

vaarg.end:                                        ; preds = %vaarg.in_mem, %vaarg.in_reg
  %vaarg.addr = phi i8** [ %2, %vaarg.in_reg ], [ %4, %vaarg.in_mem ], !dbg !2474
  %5 = load i8*, i8** %vaarg.addr, align 8, !dbg !2474
  store i8* %5, i8** %paramp, align 8, !dbg !2476
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2477
  %7 = load i32, i32* %info.addr, align 4, !dbg !2478
  %8 = load i8*, i8** %paramp, align 8, !dbg !2479
  %call = call i32 (%struct.Curl_easy*, i32, ...) @Curl_getinfo(%struct.Curl_easy* %6, i32 %7, i8* %8), !dbg !2480
  store i32 %call, i32* %result, align 4, !dbg !2481
  %arraydecay3 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %arg, i32 0, i32 0, !dbg !2482
  %arraydecay34 = bitcast %struct.__va_list_tag* %arraydecay3 to i8*, !dbg !2482
  call void @llvm.va_end(i8* %arraydecay34), !dbg !2482
  %9 = load i32, i32* %result, align 4, !dbg !2483
  ret i32 %9, !dbg !2484
}

declare i32 @Curl_getinfo(%struct.Curl_easy*, i32, ...) #3

; Function Attrs: nounwind uwtable
define %struct.Curl_easy* @curl_easy_duphandle(%struct.Curl_easy* %data) #1 !dbg !2095 {
entry:
  %retval = alloca %struct.Curl_easy*, align 8
  %data.addr = alloca %struct.Curl_easy*, align 8
  %outcurl = alloca %struct.Curl_easy*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2485, metadata !2138), !dbg !2486
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %outcurl, metadata !2487, metadata !2138), !dbg !2488
  %0 = load i8* (i64, i64)*, i8* (i64, i64)** @Curl_ccalloc, align 8, !dbg !2489
  %call = call i8* %0(i64 1, i64 20024), !dbg !2489
  %1 = bitcast i8* %call to %struct.Curl_easy*, !dbg !2489
  store %struct.Curl_easy* %1, %struct.Curl_easy** %outcurl, align 8, !dbg !2488
  %2 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2490
  %cmp = icmp eq %struct.Curl_easy* null, %2, !dbg !2492
  br i1 %cmp, label %if.then, label %if.end, !dbg !2493

if.then:                                          ; preds = %entry
  br label %fail, !dbg !2494

if.end:                                           ; preds = %entry
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2495
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 13, !dbg !2496
  %buffer_size = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 78, !dbg !2497
  %4 = load i64, i64* %buffer_size, align 8, !dbg !2497
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2498
  %set1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %5, i32 0, i32 13, !dbg !2499
  %buffer_size2 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set1, i32 0, i32 78, !dbg !2500
  store i64 %4, i64* %buffer_size2, align 8, !dbg !2501
  %6 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !2502
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2502
  %set3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 13, !dbg !2502
  %buffer_size4 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set3, i32 0, i32 78, !dbg !2502
  %8 = load i64, i64* %buffer_size4, align 8, !dbg !2502
  %tobool = icmp ne i64 %8, 0, !dbg !2502
  br i1 %tobool, label %cond.true, label %cond.false, !dbg !2502

cond.true:                                        ; preds = %if.end
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2503
  %set5 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 13, !dbg !2503
  %buffer_size6 = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set5, i32 0, i32 78, !dbg !2503
  %10 = load i64, i64* %buffer_size6, align 8, !dbg !2503
  br label %cond.end, !dbg !2503

cond.false:                                       ; preds = %if.end
  br label %cond.end, !dbg !2505

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ %10, %cond.true ], [ 16384, %cond.false ], !dbg !2507
  %add = add nsw i64 %cond, 1, !dbg !2507
  %call7 = call i8* %6(i64 %add), !dbg !2507
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2509
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 17, !dbg !2510
  %buffer = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 6, !dbg !2511
  store i8* %call7, i8** %buffer, align 8, !dbg !2512
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2513
  %state8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %12, i32 0, i32 17, !dbg !2515
  %buffer9 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state8, i32 0, i32 6, !dbg !2516
  %13 = load i8*, i8** %buffer9, align 8, !dbg !2516
  %tobool10 = icmp ne i8* %13, null, !dbg !2513
  br i1 %tobool10, label %if.end12, label %if.then11, !dbg !2517

if.then11:                                        ; preds = %cond.end
  br label %fail, !dbg !2518

if.end12:                                         ; preds = %cond.end
  %14 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !2519
  %call13 = call i8* %14(i64 256), !dbg !2519
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2520
  %state14 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 17, !dbg !2521
  %headerbuff = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state14, i32 0, i32 4, !dbg !2522
  store i8* %call13, i8** %headerbuff, align 8, !dbg !2523
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2524
  %state15 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %16, i32 0, i32 17, !dbg !2526
  %headerbuff16 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state15, i32 0, i32 4, !dbg !2527
  %17 = load i8*, i8** %headerbuff16, align 8, !dbg !2527
  %tobool17 = icmp ne i8* %17, null, !dbg !2524
  br i1 %tobool17, label %if.end19, label %if.then18, !dbg !2528

if.then18:                                        ; preds = %if.end12
  br label %fail, !dbg !2529

if.end19:                                         ; preds = %if.end12
  %18 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2530
  %state20 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %18, i32 0, i32 17, !dbg !2531
  %headersize = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state20, i32 0, i32 5, !dbg !2532
  store i64 256, i64* %headersize, align 8, !dbg !2533
  %19 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2534
  %20 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2536
  %call21 = call i32 @Curl_dupset(%struct.Curl_easy* %19, %struct.Curl_easy* %20), !dbg !2537
  %tobool22 = icmp ne i32 %call21, 0, !dbg !2537
  br i1 %tobool22, label %if.then23, label %if.end24, !dbg !2538

if.then23:                                        ; preds = %if.end19
  br label %fail, !dbg !2539

if.end24:                                         ; preds = %if.end19
  %21 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2540
  %state25 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %21, i32 0, i32 17, !dbg !2541
  %conn_cache = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state25, i32 0, i32 0, !dbg !2542
  store %struct.conncache* null, %struct.conncache** %conn_cache, align 8, !dbg !2543
  %22 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2544
  %state26 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %22, i32 0, i32 17, !dbg !2545
  %lastconnect = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state26, i32 0, i32 3, !dbg !2546
  store %struct.connectdata* null, %struct.connectdata** %lastconnect, align 8, !dbg !2547
  %23 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2548
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %23, i32 0, i32 16, !dbg !2549
  %flags = getelementptr inbounds %struct.Progress, %struct.Progress* %progress, i32 0, i32 8, !dbg !2550
  %24 = load i32, i32* %flags, align 8, !dbg !2550
  %25 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2551
  %progress27 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %25, i32 0, i32 16, !dbg !2552
  %flags28 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress27, i32 0, i32 8, !dbg !2553
  store i32 %24, i32* %flags28, align 8, !dbg !2554
  %26 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2555
  %progress29 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %26, i32 0, i32 16, !dbg !2556
  %callback = getelementptr inbounds %struct.Progress, %struct.Progress* %progress29, i32 0, i32 6, !dbg !2557
  %27 = load i8, i8* %callback, align 8, !dbg !2557
  %tobool30 = trunc i8 %27 to i1, !dbg !2557
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2558
  %progress31 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %28, i32 0, i32 16, !dbg !2559
  %callback32 = getelementptr inbounds %struct.Progress, %struct.Progress* %progress31, i32 0, i32 6, !dbg !2560
  %frombool = zext i1 %tobool30 to i8, !dbg !2561
  store i8 %frombool, i8* %callback32, align 8, !dbg !2561
  %29 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2562
  %cookies = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %29, i32 0, i32 15, !dbg !2564
  %30 = load %struct.CookieInfo*, %struct.CookieInfo** %cookies, align 8, !dbg !2564
  %tobool33 = icmp ne %struct.CookieInfo* %30, null, !dbg !2562
  br i1 %tobool33, label %if.then34, label %if.end45, !dbg !2565

if.then34:                                        ; preds = %if.end24
  %31 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2566
  %32 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2568
  %cookies35 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %32, i32 0, i32 15, !dbg !2569
  %33 = load %struct.CookieInfo*, %struct.CookieInfo** %cookies35, align 8, !dbg !2569
  %filename = getelementptr inbounds %struct.CookieInfo, %struct.CookieInfo* %33, i32 0, i32 1, !dbg !2570
  %34 = load i8*, i8** %filename, align 8, !dbg !2570
  %35 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2571
  %cookies36 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %35, i32 0, i32 15, !dbg !2572
  %36 = load %struct.CookieInfo*, %struct.CookieInfo** %cookies36, align 8, !dbg !2572
  %37 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2573
  %set37 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %37, i32 0, i32 13, !dbg !2574
  %cookiesession = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set37, i32 0, i32 58, !dbg !2575
  %38 = load i8, i8* %cookiesession, align 1, !dbg !2575
  %tobool38 = trunc i8 %38 to i1, !dbg !2575
  %call39 = call %struct.CookieInfo* @Curl_cookie_init(%struct.Curl_easy* %31, i8* %34, %struct.CookieInfo* %36, i1 zeroext %tobool38), !dbg !2576
  %39 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2577
  %cookies40 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %39, i32 0, i32 15, !dbg !2578
  store %struct.CookieInfo* %call39, %struct.CookieInfo** %cookies40, align 8, !dbg !2579
  %40 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2580
  %cookies41 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %40, i32 0, i32 15, !dbg !2582
  %41 = load %struct.CookieInfo*, %struct.CookieInfo** %cookies41, align 8, !dbg !2582
  %tobool42 = icmp ne %struct.CookieInfo* %41, null, !dbg !2580
  br i1 %tobool42, label %if.end44, label %if.then43, !dbg !2583

if.then43:                                        ; preds = %if.then34
  br label %fail, !dbg !2584

if.end44:                                         ; preds = %if.then34
  br label %if.end45, !dbg !2585

if.end45:                                         ; preds = %if.end44, %if.end24
  %42 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2586
  %change = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %42, i32 0, i32 14, !dbg !2588
  %cookielist = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change, i32 0, i32 4, !dbg !2589
  %43 = load %struct.curl_slist*, %struct.curl_slist** %cookielist, align 8, !dbg !2589
  %tobool46 = icmp ne %struct.curl_slist* %43, null, !dbg !2586
  br i1 %tobool46, label %if.then47, label %if.end58, !dbg !2590

if.then47:                                        ; preds = %if.end45
  %44 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2591
  %change48 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %44, i32 0, i32 14, !dbg !2593
  %cookielist49 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change48, i32 0, i32 4, !dbg !2594
  %45 = load %struct.curl_slist*, %struct.curl_slist** %cookielist49, align 8, !dbg !2594
  %call50 = call %struct.curl_slist* @Curl_slist_duplicate(%struct.curl_slist* %45), !dbg !2595
  %46 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2596
  %change51 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %46, i32 0, i32 14, !dbg !2597
  %cookielist52 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change51, i32 0, i32 4, !dbg !2598
  store %struct.curl_slist* %call50, %struct.curl_slist** %cookielist52, align 8, !dbg !2599
  %47 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2600
  %change53 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %47, i32 0, i32 14, !dbg !2602
  %cookielist54 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change53, i32 0, i32 4, !dbg !2603
  %48 = load %struct.curl_slist*, %struct.curl_slist** %cookielist54, align 8, !dbg !2603
  %tobool55 = icmp ne %struct.curl_slist* %48, null, !dbg !2600
  br i1 %tobool55, label %if.end57, label %if.then56, !dbg !2604

if.then56:                                        ; preds = %if.then47
  br label %fail, !dbg !2605

if.end57:                                         ; preds = %if.then47
  br label %if.end58, !dbg !2606

if.end58:                                         ; preds = %if.end57, %if.end45
  %49 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2607
  %change59 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %49, i32 0, i32 14, !dbg !2609
  %url = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change59, i32 0, i32 0, !dbg !2610
  %50 = load i8*, i8** %url, align 8, !dbg !2610
  %tobool60 = icmp ne i8* %50, null, !dbg !2607
  br i1 %tobool60, label %if.then61, label %if.end73, !dbg !2611

if.then61:                                        ; preds = %if.end58
  %51 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !2612
  %52 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2612
  %change62 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %52, i32 0, i32 14, !dbg !2612
  %url63 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change62, i32 0, i32 0, !dbg !2612
  %53 = load i8*, i8** %url63, align 8, !dbg !2612
  %call64 = call i8* %51(i8* %53), !dbg !2612
  %54 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2614
  %change65 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %54, i32 0, i32 14, !dbg !2615
  %url66 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change65, i32 0, i32 0, !dbg !2616
  store i8* %call64, i8** %url66, align 8, !dbg !2617
  %55 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2618
  %change67 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %55, i32 0, i32 14, !dbg !2620
  %url68 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change67, i32 0, i32 0, !dbg !2621
  %56 = load i8*, i8** %url68, align 8, !dbg !2621
  %tobool69 = icmp ne i8* %56, null, !dbg !2618
  br i1 %tobool69, label %if.end71, label %if.then70, !dbg !2622

if.then70:                                        ; preds = %if.then61
  br label %fail, !dbg !2623

if.end71:                                         ; preds = %if.then61
  %57 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2624
  %change72 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %57, i32 0, i32 14, !dbg !2625
  %url_alloc = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change72, i32 0, i32 1, !dbg !2626
  store i8 1, i8* %url_alloc, align 8, !dbg !2627
  br label %if.end73, !dbg !2628

if.end73:                                         ; preds = %if.end71, %if.end58
  %58 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2629
  %change74 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %58, i32 0, i32 14, !dbg !2631
  %referer = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change74, i32 0, i32 2, !dbg !2632
  %59 = load i8*, i8** %referer, align 8, !dbg !2632
  %tobool75 = icmp ne i8* %59, null, !dbg !2629
  br i1 %tobool75, label %if.then76, label %if.end88, !dbg !2633

if.then76:                                        ; preds = %if.end73
  %60 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !2634
  %61 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2634
  %change77 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %61, i32 0, i32 14, !dbg !2634
  %referer78 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change77, i32 0, i32 2, !dbg !2634
  %62 = load i8*, i8** %referer78, align 8, !dbg !2634
  %call79 = call i8* %60(i8* %62), !dbg !2634
  %63 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2636
  %change80 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %63, i32 0, i32 14, !dbg !2637
  %referer81 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change80, i32 0, i32 2, !dbg !2638
  store i8* %call79, i8** %referer81, align 8, !dbg !2639
  %64 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2640
  %change82 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %64, i32 0, i32 14, !dbg !2642
  %referer83 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change82, i32 0, i32 2, !dbg !2643
  %65 = load i8*, i8** %referer83, align 8, !dbg !2643
  %tobool84 = icmp ne i8* %65, null, !dbg !2640
  br i1 %tobool84, label %if.end86, label %if.then85, !dbg !2644

if.then85:                                        ; preds = %if.then76
  br label %fail, !dbg !2645

if.end86:                                         ; preds = %if.then76
  %66 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2646
  %change87 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %66, i32 0, i32 14, !dbg !2647
  %referer_alloc = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change87, i32 0, i32 3, !dbg !2648
  store i8 1, i8* %referer_alloc, align 8, !dbg !2649
  br label %if.end88, !dbg !2650

if.end88:                                         ; preds = %if.end86, %if.end73
  br label %do.body, !dbg !2651

do.body:                                          ; preds = %if.end88
  br label %do.end, !dbg !2652

do.end:                                           ; preds = %do.body
  %67 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2655
  %call89 = call i32 @Curl_initinfo(%struct.Curl_easy* %67), !dbg !2656
  %68 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2657
  %magic = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %68, i32 0, i32 21, !dbg !2658
  store i32 -1059136595, i32* %magic, align 8, !dbg !2659
  %69 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2660
  store %struct.Curl_easy* %69, %struct.Curl_easy** %retval, align 8, !dbg !2661
  br label %return, !dbg !2661

fail:                                             ; preds = %if.then85, %if.then70, %if.then56, %if.then43, %if.then23, %if.then18, %if.then11, %if.then
  %70 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2662
  %tobool90 = icmp ne %struct.Curl_easy* %70, null, !dbg !2662
  br i1 %tobool90, label %if.then91, label %if.end120, !dbg !2664

if.then91:                                        ; preds = %fail
  %71 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2665
  %change92 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %71, i32 0, i32 14, !dbg !2667
  %cookielist93 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change92, i32 0, i32 4, !dbg !2668
  %72 = load %struct.curl_slist*, %struct.curl_slist** %cookielist93, align 8, !dbg !2668
  call void @curl_slist_free_all(%struct.curl_slist* %72), !dbg !2669
  %73 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2670
  %change94 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %73, i32 0, i32 14, !dbg !2671
  %cookielist95 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change94, i32 0, i32 4, !dbg !2672
  store %struct.curl_slist* null, %struct.curl_slist** %cookielist95, align 8, !dbg !2673
  br label %do.body96, !dbg !2674

do.body96:                                        ; preds = %if.then91
  %74 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2675
  %75 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2675
  %state97 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %75, i32 0, i32 17, !dbg !2675
  %buffer98 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state97, i32 0, i32 6, !dbg !2675
  %76 = load i8*, i8** %buffer98, align 8, !dbg !2675
  call void %74(i8* %76), !dbg !2675
  %77 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2675
  %state99 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %77, i32 0, i32 17, !dbg !2675
  %buffer100 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state99, i32 0, i32 6, !dbg !2675
  store i8* null, i8** %buffer100, align 8, !dbg !2675
  br label %do.end101, !dbg !2675

do.end101:                                        ; preds = %do.body96
  br label %do.body102, !dbg !2678

do.body102:                                       ; preds = %do.end101
  %78 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2679
  %79 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2679
  %state103 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %79, i32 0, i32 17, !dbg !2679
  %headerbuff104 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state103, i32 0, i32 4, !dbg !2679
  %80 = load i8*, i8** %headerbuff104, align 8, !dbg !2679
  call void %78(i8* %80), !dbg !2679
  %81 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2679
  %state105 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %81, i32 0, i32 17, !dbg !2679
  %headerbuff106 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state105, i32 0, i32 4, !dbg !2679
  store i8* null, i8** %headerbuff106, align 8, !dbg !2679
  br label %do.end107, !dbg !2679

do.end107:                                        ; preds = %do.body102
  br label %do.body108, !dbg !2682

do.body108:                                       ; preds = %do.end107
  %82 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2683
  %83 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2683
  %change109 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %83, i32 0, i32 14, !dbg !2683
  %url110 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change109, i32 0, i32 0, !dbg !2683
  %84 = load i8*, i8** %url110, align 8, !dbg !2683
  call void %82(i8* %84), !dbg !2683
  %85 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2683
  %change111 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %85, i32 0, i32 14, !dbg !2683
  %url112 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change111, i32 0, i32 0, !dbg !2683
  store i8* null, i8** %url112, align 8, !dbg !2683
  br label %do.end113, !dbg !2683

do.end113:                                        ; preds = %do.body108
  br label %do.body114, !dbg !2686

do.body114:                                       ; preds = %do.end113
  %86 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2687
  %87 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2687
  %change115 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %87, i32 0, i32 14, !dbg !2687
  %referer116 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change115, i32 0, i32 2, !dbg !2687
  %88 = load i8*, i8** %referer116, align 8, !dbg !2687
  call void %86(i8* %88), !dbg !2687
  %89 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2687
  %change117 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %89, i32 0, i32 14, !dbg !2687
  %referer118 = getelementptr inbounds %struct.DynamicStatic, %struct.DynamicStatic* %change117, i32 0, i32 2, !dbg !2687
  store i8* null, i8** %referer118, align 8, !dbg !2687
  br label %do.end119, !dbg !2687

do.end119:                                        ; preds = %do.body114
  %90 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2690
  call void @Curl_freeset(%struct.Curl_easy* %90), !dbg !2691
  %91 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2692
  %92 = load %struct.Curl_easy*, %struct.Curl_easy** %outcurl, align 8, !dbg !2692
  %93 = bitcast %struct.Curl_easy* %92 to i8*, !dbg !2692
  call void %91(i8* %93), !dbg !2692
  br label %if.end120, !dbg !2693

if.end120:                                        ; preds = %do.end119, %fail
  store %struct.Curl_easy* null, %struct.Curl_easy** %retval, align 8, !dbg !2694
  br label %return, !dbg !2694

return:                                           ; preds = %if.end120, %do.end
  %94 = load %struct.Curl_easy*, %struct.Curl_easy** %retval, align 8, !dbg !2695
  ret %struct.Curl_easy* %94, !dbg !2695
}

declare i32 @Curl_dupset(%struct.Curl_easy*, %struct.Curl_easy*) #3

declare %struct.CookieInfo* @Curl_cookie_init(%struct.Curl_easy*, i8*, %struct.CookieInfo*, i1 zeroext) #3

declare %struct.curl_slist* @Curl_slist_duplicate(%struct.curl_slist*) #3

declare i32 @Curl_initinfo(%struct.Curl_easy*) #3

declare void @curl_slist_free_all(%struct.curl_slist*) #3

declare void @Curl_freeset(%struct.Curl_easy*) #3

; Function Attrs: nounwind uwtable
define void @curl_easy_reset(%struct.Curl_easy* %data) #1 !dbg !2098 {
entry:
  %data.addr = alloca %struct.Curl_easy*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2696, metadata !2138), !dbg !2697
  br label %do.body, !dbg !2698

do.body:                                          ; preds = %entry
  %0 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2699
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2699
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 17, !dbg !2699
  %pathbuffer = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 37, !dbg !2699
  %2 = load i8*, i8** %pathbuffer, align 8, !dbg !2699
  call void %0(i8* %2), !dbg !2699
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2699
  %state1 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %3, i32 0, i32 17, !dbg !2699
  %pathbuffer2 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state1, i32 0, i32 37, !dbg !2699
  store i8* null, i8** %pathbuffer2, align 8, !dbg !2699
  br label %do.end, !dbg !2699

do.end:                                           ; preds = %do.body
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2702
  %state3 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %4, i32 0, i32 17, !dbg !2703
  %path = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state3, i32 0, i32 38, !dbg !2704
  store i8* null, i8** %path, align 8, !dbg !2705
  %5 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2706
  call void @Curl_free_request_state(%struct.Curl_easy* %5), !dbg !2707
  %6 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2708
  call void @Curl_freeset(%struct.Curl_easy* %6), !dbg !2709
  %7 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2710
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %7, i32 0, i32 13, !dbg !2711
  %8 = bitcast %struct.UserDefined* %set to i8*, !dbg !2712
  call void @llvm.memset.p0i8.i64(i8* %8, i8 0, i64 1720, i32 8, i1 false), !dbg !2712
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2713
  %set4 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 13, !dbg !2714
  %call = call i32 @Curl_init_userdefined(%struct.UserDefined* %set4), !dbg !2715
  %10 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2716
  %progress = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %10, i32 0, i32 16, !dbg !2717
  %11 = bitcast %struct.Progress* %progress to i8*, !dbg !2718
  call void @llvm.memset.p0i8.i64(i8* %11, i8 0, i64 400, i32 8, i1 false), !dbg !2718
  %12 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2719
  %call5 = call i32 @Curl_initinfo(%struct.Curl_easy* %12), !dbg !2720
  %13 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2721
  %progress6 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %13, i32 0, i32 16, !dbg !2722
  %flags = getelementptr inbounds %struct.Progress, %struct.Progress* %progress6, i32 0, i32 8, !dbg !2723
  %14 = load i32, i32* %flags, align 8, !dbg !2724
  %or = or i32 %14, 16, !dbg !2724
  store i32 %or, i32* %flags, align 8, !dbg !2724
  %15 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2725
  %state7 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %15, i32 0, i32 17, !dbg !2726
  %current_speed = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state7, i32 0, i32 8, !dbg !2727
  store i64 -1, i64* %current_speed, align 8, !dbg !2728
  %16 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2729
  %state8 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %16, i32 0, i32 17, !dbg !2730
  %authhost = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state8, i32 0, i32 23, !dbg !2731
  %17 = bitcast %struct.auth* %authhost to i8*, !dbg !2732
  call void @llvm.memset.p0i8.i64(i8* %17, i8 0, i64 32, i32 8, i1 false), !dbg !2732
  %18 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2733
  %state9 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %18, i32 0, i32 17, !dbg !2734
  %authproxy = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state9, i32 0, i32 24, !dbg !2735
  %19 = bitcast %struct.auth* %authproxy to i8*, !dbg !2736
  call void @llvm.memset.p0i8.i64(i8* %19, i8 0, i64 32, i32 8, i1 false), !dbg !2736
  ret void, !dbg !2737
}

declare void @Curl_free_request_state(%struct.Curl_easy*) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

declare i32 @Curl_init_userdefined(%struct.UserDefined*) #3

; Function Attrs: nounwind uwtable
define i32 @curl_easy_pause(%struct.Curl_easy* %data, i32 %action) #1 !dbg !2099 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %action.addr = alloca i32, align 4
  %k = alloca %struct.SingleRequest*, align 8
  %result = alloca i32, align 4
  %newstate = alloca i32, align 4
  %i = alloca i32, align 4
  %count = alloca i32, align 4
  %writebuf = alloca [3 x %struct.tempbuf], align 16
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2738, metadata !2138), !dbg !2739
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !2740, metadata !2138), !dbg !2741
  call void @llvm.dbg.declare(metadata %struct.SingleRequest** %k, metadata !2742, metadata !2138), !dbg !2744
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2745
  %req = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %0, i32 0, i32 12, !dbg !2746
  store %struct.SingleRequest* %req, %struct.SingleRequest** %k, align 8, !dbg !2744
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2747, metadata !2138), !dbg !2748
  store i32 0, i32* %result, align 4, !dbg !2748
  call void @llvm.dbg.declare(metadata i32* %newstate, metadata !2749, metadata !2138), !dbg !2750
  %1 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2751
  %keepon = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %1, i32 0, i32 31, !dbg !2752
  %2 = load i32, i32* %keepon, align 4, !dbg !2752
  %and = and i32 %2, -49, !dbg !2753
  store i32 %and, i32* %newstate, align 4, !dbg !2750
  %3 = load i32, i32* %action.addr, align 4, !dbg !2754
  %and1 = and i32 %3, 1, !dbg !2755
  %tobool = icmp ne i32 %and1, 0, !dbg !2756
  %cond = select i1 %tobool, i32 16, i32 0, !dbg !2756
  %4 = load i32, i32* %action.addr, align 4, !dbg !2757
  %and2 = and i32 %4, 4, !dbg !2758
  %tobool3 = icmp ne i32 %and2, 0, !dbg !2759
  %cond4 = select i1 %tobool3, i32 32, i32 0, !dbg !2759
  %or = or i32 %cond, %cond4, !dbg !2760
  %5 = load i32, i32* %newstate, align 4, !dbg !2761
  %or5 = or i32 %5, %or, !dbg !2761
  store i32 %or5, i32* %newstate, align 4, !dbg !2761
  %6 = load i32, i32* %newstate, align 4, !dbg !2762
  %7 = load %struct.SingleRequest*, %struct.SingleRequest** %k, align 8, !dbg !2763
  %keepon6 = getelementptr inbounds %struct.SingleRequest, %struct.SingleRequest* %7, i32 0, i32 31, !dbg !2764
  store i32 %6, i32* %keepon6, align 4, !dbg !2765
  %8 = load i32, i32* %newstate, align 4, !dbg !2766
  %and7 = and i32 %8, 16, !dbg !2768
  %tobool8 = icmp ne i32 %and7, 0, !dbg !2768
  br i1 %tobool8, label %if.end44, label %land.lhs.true, !dbg !2769

land.lhs.true:                                    ; preds = %entry
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2770
  %state = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %9, i32 0, i32 17, !dbg !2772
  %tempcount = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state, i32 0, i32 14, !dbg !2773
  %10 = load i32, i32* %tempcount, align 8, !dbg !2773
  %tobool9 = icmp ne i32 %10, 0, !dbg !2770
  br i1 %tobool9, label %if.then, label %if.end44, !dbg !2774

if.then:                                          ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2775, metadata !2138), !dbg !2777
  call void @llvm.dbg.declare(metadata i32* %count, metadata !2778, metadata !2138), !dbg !2779
  %11 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2780
  %state10 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %11, i32 0, i32 17, !dbg !2781
  %tempcount11 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state10, i32 0, i32 14, !dbg !2782
  %12 = load i32, i32* %tempcount11, align 8, !dbg !2782
  store i32 %12, i32* %count, align 4, !dbg !2779
  call void @llvm.dbg.declare(metadata [3 x %struct.tempbuf]* %writebuf, metadata !2783, metadata !2138), !dbg !2784
  store i32 0, i32* %i, align 4, !dbg !2785
  br label %for.cond, !dbg !2787

for.cond:                                         ; preds = %for.inc, %if.then
  %13 = load i32, i32* %i, align 4, !dbg !2788
  %14 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2791
  %state12 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %14, i32 0, i32 17, !dbg !2792
  %tempcount13 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state12, i32 0, i32 14, !dbg !2793
  %15 = load i32, i32* %tempcount13, align 8, !dbg !2793
  %cmp = icmp ult i32 %13, %15, !dbg !2794
  br i1 %cmp, label %for.body, label %for.end, !dbg !2795

for.body:                                         ; preds = %for.cond
  %16 = load i32, i32* %i, align 4, !dbg !2796
  %idxprom = zext i32 %16 to i64, !dbg !2798
  %arrayidx = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %writebuf, i64 0, i64 %idxprom, !dbg !2798
  %17 = load i32, i32* %i, align 4, !dbg !2799
  %idxprom14 = zext i32 %17 to i64, !dbg !2800
  %18 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2800
  %state15 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %18, i32 0, i32 17, !dbg !2801
  %tempwrite = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state15, i32 0, i32 15, !dbg !2802
  %arrayidx16 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite, i64 0, i64 %idxprom14, !dbg !2800
  %19 = bitcast %struct.tempbuf* %arrayidx to i8*, !dbg !2800
  %20 = bitcast %struct.tempbuf* %arrayidx16 to i8*, !dbg !2800
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %19, i8* %20, i64 24, i32 8, i1 false), !dbg !2800
  %21 = load i32, i32* %i, align 4, !dbg !2803
  %idxprom17 = zext i32 %21 to i64, !dbg !2804
  %22 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2804
  %state18 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %22, i32 0, i32 17, !dbg !2805
  %tempwrite19 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state18, i32 0, i32 15, !dbg !2806
  %arrayidx20 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %tempwrite19, i64 0, i64 %idxprom17, !dbg !2804
  %buf = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx20, i32 0, i32 0, !dbg !2807
  store i8* null, i8** %buf, align 8, !dbg !2808
  br label %for.inc, !dbg !2809

for.inc:                                          ; preds = %for.body
  %23 = load i32, i32* %i, align 4, !dbg !2810
  %inc = add i32 %23, 1, !dbg !2810
  store i32 %inc, i32* %i, align 4, !dbg !2810
  br label %for.cond, !dbg !2812

for.end:                                          ; preds = %for.cond
  %24 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2813
  %state21 = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %24, i32 0, i32 17, !dbg !2814
  %tempcount22 = getelementptr inbounds %struct.UrlState, %struct.UrlState* %state21, i32 0, i32 14, !dbg !2815
  store i32 0, i32* %tempcount22, align 8, !dbg !2816
  store i32 0, i32* %i, align 4, !dbg !2817
  br label %for.cond23, !dbg !2819

for.cond23:                                       ; preds = %for.inc38, %for.end
  %25 = load i32, i32* %i, align 4, !dbg !2820
  %26 = load i32, i32* %count, align 4, !dbg !2823
  %cmp24 = icmp ult i32 %25, %26, !dbg !2824
  br i1 %cmp24, label %for.body25, label %for.end40, !dbg !2825

for.body25:                                       ; preds = %for.cond23
  %27 = load i32, i32* %result, align 4, !dbg !2826
  %tobool26 = icmp ne i32 %27, 0, !dbg !2826
  br i1 %tobool26, label %if.end, label %if.then27, !dbg !2829

if.then27:                                        ; preds = %for.body25
  %28 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2830
  %easy_conn = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %28, i32 0, i32 2, !dbg !2831
  %29 = load %struct.connectdata*, %struct.connectdata** %easy_conn, align 8, !dbg !2831
  %30 = load i32, i32* %i, align 4, !dbg !2832
  %idxprom28 = zext i32 %30 to i64, !dbg !2833
  %arrayidx29 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %writebuf, i64 0, i64 %idxprom28, !dbg !2833
  %type = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx29, i32 0, i32 2, !dbg !2834
  %31 = load i32, i32* %type, align 8, !dbg !2834
  %32 = load i32, i32* %i, align 4, !dbg !2835
  %idxprom30 = zext i32 %32 to i64, !dbg !2836
  %arrayidx31 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %writebuf, i64 0, i64 %idxprom30, !dbg !2836
  %buf32 = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx31, i32 0, i32 0, !dbg !2837
  %33 = load i8*, i8** %buf32, align 8, !dbg !2837
  %34 = load i32, i32* %i, align 4, !dbg !2838
  %idxprom33 = zext i32 %34 to i64, !dbg !2839
  %arrayidx34 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %writebuf, i64 0, i64 %idxprom33, !dbg !2839
  %len = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx34, i32 0, i32 1, !dbg !2840
  %35 = load i64, i64* %len, align 8, !dbg !2840
  %call = call i32 @Curl_client_chop_write(%struct.connectdata* %29, i32 %31, i8* %33, i64 %35), !dbg !2841
  store i32 %call, i32* %result, align 4, !dbg !2842
  br label %if.end, !dbg !2843

if.end:                                           ; preds = %if.then27, %for.body25
  %36 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !2844
  %37 = load i32, i32* %i, align 4, !dbg !2844
  %idxprom35 = zext i32 %37 to i64, !dbg !2844
  %arrayidx36 = getelementptr inbounds [3 x %struct.tempbuf], [3 x %struct.tempbuf]* %writebuf, i64 0, i64 %idxprom35, !dbg !2844
  %buf37 = getelementptr inbounds %struct.tempbuf, %struct.tempbuf* %arrayidx36, i32 0, i32 0, !dbg !2844
  %38 = load i8*, i8** %buf37, align 8, !dbg !2844
  call void %36(i8* %38), !dbg !2844
  br label %for.inc38, !dbg !2845

for.inc38:                                        ; preds = %if.end
  %39 = load i32, i32* %i, align 4, !dbg !2846
  %inc39 = add i32 %39, 1, !dbg !2846
  store i32 %inc39, i32* %i, align 4, !dbg !2846
  br label %for.cond23, !dbg !2848

for.end40:                                        ; preds = %for.cond23
  %40 = load i32, i32* %result, align 4, !dbg !2849
  %tobool41 = icmp ne i32 %40, 0, !dbg !2849
  br i1 %tobool41, label %if.then42, label %if.end43, !dbg !2851

if.then42:                                        ; preds = %for.end40
  %41 = load i32, i32* %result, align 4, !dbg !2852
  store i32 %41, i32* %retval, align 4, !dbg !2853
  br label %return, !dbg !2853

if.end43:                                         ; preds = %for.end40
  br label %if.end44, !dbg !2854

if.end44:                                         ; preds = %if.end43, %land.lhs.true, %entry
  %42 = load i32, i32* %result, align 4, !dbg !2855
  %tobool45 = icmp ne i32 %42, 0, !dbg !2855
  br i1 %tobool45, label %if.end50, label %land.lhs.true46, !dbg !2857

land.lhs.true46:                                  ; preds = %if.end44
  %43 = load i32, i32* %newstate, align 4, !dbg !2858
  %and47 = and i32 %43, 48, !dbg !2859
  %cmp48 = icmp ne i32 %and47, 48, !dbg !2860
  br i1 %cmp48, label %if.then49, label %if.end50, !dbg !2861

if.then49:                                        ; preds = %land.lhs.true46
  %44 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2863
  call void @Curl_expire(%struct.Curl_easy* %44, i64 0), !dbg !2864
  br label %if.end50, !dbg !2864

if.end50:                                         ; preds = %if.then49, %land.lhs.true46, %if.end44
  %45 = load i32, i32* %result, align 4, !dbg !2865
  store i32 %45, i32* %retval, align 4, !dbg !2866
  br label %return, !dbg !2866

return:                                           ; preds = %if.end50, %if.then42
  %46 = load i32, i32* %retval, align 4, !dbg !2867
  ret i32 %46, !dbg !2867
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

declare i32 @Curl_client_chop_write(%struct.connectdata*, i32, i8*, i64) #3

declare void @Curl_expire(%struct.Curl_easy*, i64) #3

; Function Attrs: nounwind uwtable
define i32 @curl_easy_recv(%struct.Curl_easy* %data, i8* %buffer, i64 %buflen, i64* %n) #1 !dbg !2102 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %buffer.addr = alloca i8*, align 8
  %buflen.addr = alloca i64, align 8
  %n.addr = alloca i64*, align 8
  %sfd = alloca i32, align 4
  %result = alloca i32, align 4
  %n1 = alloca i64, align 8
  %c = alloca %struct.connectdata*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2868, metadata !2138), !dbg !2869
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !2870, metadata !2138), !dbg !2871
  store i64 %buflen, i64* %buflen.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %buflen.addr, metadata !2872, metadata !2138), !dbg !2873
  store i64* %n, i64** %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %n.addr, metadata !2874, metadata !2138), !dbg !2875
  call void @llvm.dbg.declare(metadata i32* %sfd, metadata !2876, metadata !2138), !dbg !2877
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2878, metadata !2138), !dbg !2879
  call void @llvm.dbg.declare(metadata i64* %n1, metadata !2880, metadata !2138), !dbg !2881
  call void @llvm.dbg.declare(metadata %struct.connectdata** %c, metadata !2882, metadata !2138), !dbg !2883
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2884
  %call = call i32 @easy_connection(%struct.Curl_easy* %0, i32* %sfd, %struct.connectdata** %c), !dbg !2885
  store i32 %call, i32* %result, align 4, !dbg !2886
  %1 = load i32, i32* %result, align 4, !dbg !2887
  %tobool = icmp ne i32 %1, 0, !dbg !2887
  br i1 %tobool, label %if.then, label %if.end, !dbg !2889

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %result, align 4, !dbg !2890
  store i32 %2, i32* %retval, align 4, !dbg !2891
  br label %return, !dbg !2891

if.end:                                           ; preds = %entry
  %3 = load i64*, i64** %n.addr, align 8, !dbg !2892
  store i64 0, i64* %3, align 8, !dbg !2893
  %4 = load %struct.connectdata*, %struct.connectdata** %c, align 8, !dbg !2894
  %5 = load i32, i32* %sfd, align 4, !dbg !2895
  %6 = load i8*, i8** %buffer.addr, align 8, !dbg !2896
  %7 = load i64, i64* %buflen.addr, align 8, !dbg !2897
  %call1 = call i32 @Curl_read(%struct.connectdata* %4, i32 %5, i8* %6, i64 %7, i64* %n1), !dbg !2898
  store i32 %call1, i32* %result, align 4, !dbg !2899
  %8 = load i32, i32* %result, align 4, !dbg !2900
  %tobool2 = icmp ne i32 %8, 0, !dbg !2900
  br i1 %tobool2, label %if.then3, label %if.end4, !dbg !2902

if.then3:                                         ; preds = %if.end
  %9 = load i32, i32* %result, align 4, !dbg !2903
  store i32 %9, i32* %retval, align 4, !dbg !2904
  br label %return, !dbg !2904

if.end4:                                          ; preds = %if.end
  %10 = load i64, i64* %n1, align 8, !dbg !2905
  %11 = load i64*, i64** %n.addr, align 8, !dbg !2906
  store i64 %10, i64* %11, align 8, !dbg !2907
  store i32 0, i32* %retval, align 4, !dbg !2908
  br label %return, !dbg !2908

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !2909
  ret i32 %12, !dbg !2909
}

; Function Attrs: nounwind uwtable
define internal i32 @easy_connection(%struct.Curl_easy* %data, i32* %sfd, %struct.connectdata** %connp) #1 !dbg !2122 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %sfd.addr = alloca i32*, align 8
  %connp.addr = alloca %struct.connectdata**, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2910, metadata !2138), !dbg !2911
  store i32* %sfd, i32** %sfd.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %sfd.addr, metadata !2912, metadata !2138), !dbg !2913
  store %struct.connectdata** %connp, %struct.connectdata*** %connp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.connectdata*** %connp.addr, metadata !2914, metadata !2138), !dbg !2915
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2916
  %cmp = icmp eq %struct.Curl_easy* %0, null, !dbg !2918
  br i1 %cmp, label %if.then, label %if.end, !dbg !2919

if.then:                                          ; preds = %entry
  store i32 43, i32* %retval, align 4, !dbg !2920
  br label %return, !dbg !2920

if.end:                                           ; preds = %entry
  %1 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2921
  %set = getelementptr inbounds %struct.Curl_easy, %struct.Curl_easy* %1, i32 0, i32 13, !dbg !2923
  %connect_only = getelementptr inbounds %struct.UserDefined, %struct.UserDefined* %set, i32 0, i32 121, !dbg !2924
  %2 = load i8, i8* %connect_only, align 1, !dbg !2924
  %tobool = trunc i8 %2 to i1, !dbg !2924
  br i1 %tobool, label %if.end2, label %if.then1, !dbg !2925

if.then1:                                         ; preds = %if.end
  %3 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2926
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %3, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.1, i32 0, i32 0)), !dbg !2928
  store i32 1, i32* %retval, align 4, !dbg !2929
  br label %return, !dbg !2929

if.end2:                                          ; preds = %if.end
  %4 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2930
  %5 = load %struct.connectdata**, %struct.connectdata*** %connp.addr, align 8, !dbg !2931
  %call = call i32 @Curl_getconnectinfo(%struct.Curl_easy* %4, %struct.connectdata** %5), !dbg !2932
  %6 = load i32*, i32** %sfd.addr, align 8, !dbg !2933
  store i32 %call, i32* %6, align 4, !dbg !2934
  %7 = load i32*, i32** %sfd.addr, align 8, !dbg !2935
  %8 = load i32, i32* %7, align 4, !dbg !2937
  %cmp3 = icmp eq i32 %8, -1, !dbg !2938
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !2939

if.then4:                                         ; preds = %if.end2
  %9 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2940
  call void (%struct.Curl_easy*, i8*, ...) @Curl_failf(%struct.Curl_easy* %9, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.2, i32 0, i32 0)), !dbg !2942
  store i32 1, i32* %retval, align 4, !dbg !2943
  br label %return, !dbg !2943

if.end5:                                          ; preds = %if.end2
  store i32 0, i32* %retval, align 4, !dbg !2944
  br label %return, !dbg !2944

return:                                           ; preds = %if.end5, %if.then4, %if.then1, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !2945
  ret i32 %10, !dbg !2945
}

declare i32 @Curl_read(%struct.connectdata*, i32, i8*, i64, i64*) #3

; Function Attrs: nounwind uwtable
define i32 @curl_easy_send(%struct.Curl_easy* %data, i8* %buffer, i64 %buflen, i64* %n) #1 !dbg !2106 {
entry:
  %retval = alloca i32, align 4
  %data.addr = alloca %struct.Curl_easy*, align 8
  %buffer.addr = alloca i8*, align 8
  %buflen.addr = alloca i64, align 8
  %n.addr = alloca i64*, align 8
  %sfd = alloca i32, align 4
  %result = alloca i32, align 4
  %n1 = alloca i64, align 8
  %c = alloca %struct.connectdata*, align 8
  store %struct.Curl_easy* %data, %struct.Curl_easy** %data.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_easy** %data.addr, metadata !2946, metadata !2138), !dbg !2947
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !2948, metadata !2138), !dbg !2949
  store i64 %buflen, i64* %buflen.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %buflen.addr, metadata !2950, metadata !2138), !dbg !2951
  store i64* %n, i64** %n.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %n.addr, metadata !2952, metadata !2138), !dbg !2953
  call void @llvm.dbg.declare(metadata i32* %sfd, metadata !2954, metadata !2138), !dbg !2955
  call void @llvm.dbg.declare(metadata i32* %result, metadata !2956, metadata !2138), !dbg !2957
  call void @llvm.dbg.declare(metadata i64* %n1, metadata !2958, metadata !2138), !dbg !2959
  call void @llvm.dbg.declare(metadata %struct.connectdata** %c, metadata !2960, metadata !2138), !dbg !2961
  store %struct.connectdata* null, %struct.connectdata** %c, align 8, !dbg !2961
  %0 = load %struct.Curl_easy*, %struct.Curl_easy** %data.addr, align 8, !dbg !2962
  %call = call i32 @easy_connection(%struct.Curl_easy* %0, i32* %sfd, %struct.connectdata** %c), !dbg !2963
  store i32 %call, i32* %result, align 4, !dbg !2964
  %1 = load i32, i32* %result, align 4, !dbg !2965
  %tobool = icmp ne i32 %1, 0, !dbg !2965
  br i1 %tobool, label %if.then, label %if.end, !dbg !2967

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %result, align 4, !dbg !2968
  store i32 %2, i32* %retval, align 4, !dbg !2969
  br label %return, !dbg !2969

if.end:                                           ; preds = %entry
  %3 = load i64*, i64** %n.addr, align 8, !dbg !2970
  store i64 0, i64* %3, align 8, !dbg !2971
  %4 = load %struct.connectdata*, %struct.connectdata** %c, align 8, !dbg !2972
  %5 = load i32, i32* %sfd, align 4, !dbg !2973
  %6 = load i8*, i8** %buffer.addr, align 8, !dbg !2974
  %7 = load i64, i64* %buflen.addr, align 8, !dbg !2975
  %call1 = call i32 @Curl_write(%struct.connectdata* %4, i32 %5, i8* %6, i64 %7, i64* %n1), !dbg !2976
  store i32 %call1, i32* %result, align 4, !dbg !2977
  %8 = load i64, i64* %n1, align 8, !dbg !2978
  %cmp = icmp eq i64 %8, -1, !dbg !2980
  br i1 %cmp, label %if.then2, label %if.end3, !dbg !2981

if.then2:                                         ; preds = %if.end
  store i32 55, i32* %retval, align 4, !dbg !2982
  br label %return, !dbg !2982

if.end3:                                          ; preds = %if.end
  %9 = load i32, i32* %result, align 4, !dbg !2983
  %tobool4 = icmp ne i32 %9, 0, !dbg !2983
  br i1 %tobool4, label %if.end7, label %land.lhs.true, !dbg !2985

land.lhs.true:                                    ; preds = %if.end3
  %10 = load i64, i64* %n1, align 8, !dbg !2986
  %tobool5 = icmp ne i64 %10, 0, !dbg !2986
  br i1 %tobool5, label %if.end7, label %if.then6, !dbg !2988

if.then6:                                         ; preds = %land.lhs.true
  store i32 81, i32* %retval, align 4, !dbg !2989
  br label %return, !dbg !2989

if.end7:                                          ; preds = %land.lhs.true, %if.end3
  %11 = load i64, i64* %n1, align 8, !dbg !2990
  %12 = load i64*, i64** %n.addr, align 8, !dbg !2991
  store i64 %11, i64* %12, align 8, !dbg !2992
  %13 = load i32, i32* %result, align 4, !dbg !2993
  store i32 %13, i32* %retval, align 4, !dbg !2994
  br label %return, !dbg !2994

return:                                           ; preds = %if.end7, %if.then6, %if.then2, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !2995
  ret i32 %14, !dbg !2995
}

declare i32 @Curl_write(%struct.connectdata*, i32, i8*, i64, i64*) #3

; Function Attrs: nounwind uwtable
define internal i32 @win32_init() #1 !dbg !2112 {
entry:
  ret i32 0, !dbg !2996
}

declare void @Curl_version_init() #3

declare void @Curl_failf(%struct.Curl_easy*, i8*, ...) #3

declare %struct.Curl_multi* @Curl_multi_handle(i32, i32) #3

declare i32 @curl_multi_setopt(%struct.Curl_multi*, i32, ...) #3

declare i32 @curl_multi_add_handle(%struct.Curl_multi*, %struct.Curl_easy*) #3

declare i32 @curl_multi_cleanup(%struct.Curl_multi*) #3

; Function Attrs: nounwind uwtable
define internal i32 @easy_transfer(%struct.Curl_multi* %multi) #1 !dbg !2119 {
entry:
  %multi.addr = alloca %struct.Curl_multi*, align 8
  %done = alloca i8, align 1
  %mcode = alloca i32, align 4
  %result = alloca i32, align 4
  %before = alloca %struct.timeval, align 8
  %without_fds = alloca i32, align 4
  %still_running = alloca i32, align 4
  %rc = alloca i32, align 4
  %coerce = alloca %struct.timeval, align 8
  %after = alloca %struct.timeval, align 8
  %sleep_ms = alloca i32, align 4
  %msg = alloca %struct.CURLMsg*, align 8
  store %struct.Curl_multi* %multi, %struct.Curl_multi** %multi.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_multi** %multi.addr, metadata !2997, metadata !2138), !dbg !2998
  call void @llvm.dbg.declare(metadata i8* %done, metadata !2999, metadata !2138), !dbg !3000
  store i8 0, i8* %done, align 1, !dbg !3000
  call void @llvm.dbg.declare(metadata i32* %mcode, metadata !3001, metadata !2138), !dbg !3002
  store i32 0, i32* %mcode, align 4, !dbg !3002
  call void @llvm.dbg.declare(metadata i32* %result, metadata !3003, metadata !2138), !dbg !3004
  store i32 0, i32* %result, align 4, !dbg !3004
  call void @llvm.dbg.declare(metadata %struct.timeval* %before, metadata !3005, metadata !2138), !dbg !3006
  call void @llvm.dbg.declare(metadata i32* %without_fds, metadata !3007, metadata !2138), !dbg !3008
  store i32 0, i32* %without_fds, align 4, !dbg !3008
  br label %while.cond, !dbg !3009

while.cond:                                       ; preds = %if.end26, %entry
  %0 = load i8, i8* %done, align 1, !dbg !3010
  %tobool = trunc i8 %0 to i1, !dbg !3010
  br i1 %tobool, label %land.end, label %land.rhs, !dbg !3012

land.rhs:                                         ; preds = %while.cond
  %1 = load i32, i32* %mcode, align 4, !dbg !3013
  %tobool1 = icmp ne i32 %1, 0, !dbg !3015
  %lnot = xor i1 %tobool1, true, !dbg !3015
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %2 = phi i1 [ false, %while.cond ], [ %lnot, %land.rhs ]
  br i1 %2, label %while.body, label %while.end, !dbg !3016

while.body:                                       ; preds = %land.end
  call void @llvm.dbg.declare(metadata i32* %still_running, metadata !3018, metadata !2138), !dbg !3020
  store i32 0, i32* %still_running, align 4, !dbg !3020
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !3021, metadata !2138), !dbg !3022
  %call = call { i64, i64 } @curlx_tvnow(), !dbg !3023
  %3 = bitcast %struct.timeval* %coerce to { i64, i64 }*, !dbg !3023
  %4 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %3, i32 0, i32 0, !dbg !3023
  %5 = extractvalue { i64, i64 } %call, 0, !dbg !3023
  store i64 %5, i64* %4, align 8, !dbg !3023
  %6 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %3, i32 0, i32 1, !dbg !3023
  %7 = extractvalue { i64, i64 } %call, 1, !dbg !3023
  store i64 %7, i64* %6, align 8, !dbg !3023
  %8 = bitcast %struct.timeval* %before to i8*, !dbg !3023
  %9 = bitcast %struct.timeval* %coerce to i8*, !dbg !3023
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %8, i8* %9, i64 16, i32 8, i1 false), !dbg !3024
  %10 = load %struct.Curl_multi*, %struct.Curl_multi** %multi.addr, align 8, !dbg !3026
  %call2 = call i32 @curl_multi_wait(%struct.Curl_multi* %10, %struct.curl_waitfd* null, i32 0, i32 1000, i32* %rc), !dbg !3027
  store i32 %call2, i32* %mcode, align 4, !dbg !3028
  %11 = load i32, i32* %mcode, align 4, !dbg !3029
  %tobool3 = icmp ne i32 %11, 0, !dbg !3029
  br i1 %tobool3, label %if.end17, label %if.then, !dbg !3031

if.then:                                          ; preds = %while.body
  %12 = load i32, i32* %rc, align 4, !dbg !3032
  %tobool4 = icmp ne i32 %12, 0, !dbg !3032
  br i1 %tobool4, label %if.else14, label %if.then5, !dbg !3035

if.then5:                                         ; preds = %if.then
  call void @llvm.dbg.declare(metadata %struct.timeval* %after, metadata !3036, metadata !2138), !dbg !3038
  %call6 = call { i64, i64 } @curlx_tvnow(), !dbg !3039
  %13 = bitcast %struct.timeval* %after to { i64, i64 }*, !dbg !3039
  %14 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %13, i32 0, i32 0, !dbg !3039
  %15 = extractvalue { i64, i64 } %call6, 0, !dbg !3039
  store i64 %15, i64* %14, align 8, !dbg !3039
  %16 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %13, i32 0, i32 1, !dbg !3039
  %17 = extractvalue { i64, i64 } %call6, 1, !dbg !3039
  store i64 %17, i64* %16, align 8, !dbg !3039
  %18 = bitcast %struct.timeval* %after to { i64, i64 }*, !dbg !3040
  %19 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %18, i32 0, i32 0, !dbg !3040
  %20 = load i64, i64* %19, align 8, !dbg !3040
  %21 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %18, i32 0, i32 1, !dbg !3040
  %22 = load i64, i64* %21, align 8, !dbg !3040
  %23 = bitcast %struct.timeval* %before to { i64, i64 }*, !dbg !3040
  %24 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %23, i32 0, i32 0, !dbg !3040
  %25 = load i64, i64* %24, align 8, !dbg !3040
  %26 = getelementptr inbounds { i64, i64 }, { i64, i64 }* %23, i32 0, i32 1, !dbg !3040
  %27 = load i64, i64* %26, align 8, !dbg !3040
  %call7 = call i64 @curlx_tvdiff(i64 %20, i64 %22, i64 %25, i64 %27), !dbg !3040
  %cmp = icmp sle i64 %call7, 10, !dbg !3042
  br i1 %cmp, label %if.then8, label %if.else, !dbg !3043

if.then8:                                         ; preds = %if.then5
  %28 = load i32, i32* %without_fds, align 4, !dbg !3044
  %inc = add nsw i32 %28, 1, !dbg !3044
  store i32 %inc, i32* %without_fds, align 4, !dbg !3044
  %29 = load i32, i32* %without_fds, align 4, !dbg !3046
  %cmp9 = icmp sgt i32 %29, 2, !dbg !3048
  br i1 %cmp9, label %if.then10, label %if.end, !dbg !3049

if.then10:                                        ; preds = %if.then8
  call void @llvm.dbg.declare(metadata i32* %sleep_ms, metadata !3050, metadata !2138), !dbg !3052
  %30 = load i32, i32* %without_fds, align 4, !dbg !3053
  %cmp11 = icmp slt i32 %30, 10, !dbg !3054
  br i1 %cmp11, label %cond.true, label %cond.false, !dbg !3053

cond.true:                                        ; preds = %if.then10
  %31 = load i32, i32* %without_fds, align 4, !dbg !3055
  %sub = sub nsw i32 %31, 1, !dbg !3057
  %shl = shl i32 1, %sub, !dbg !3058
  br label %cond.end, !dbg !3059

cond.false:                                       ; preds = %if.then10
  br label %cond.end, !dbg !3060

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %shl, %cond.true ], [ 1000, %cond.false ], !dbg !3062
  store i32 %cond, i32* %sleep_ms, align 4, !dbg !3064
  %32 = load i32, i32* %sleep_ms, align 4, !dbg !3065
  %call12 = call i32 @Curl_wait_ms(i32 %32), !dbg !3066
  br label %if.end, !dbg !3067

if.end:                                           ; preds = %cond.end, %if.then8
  br label %if.end13, !dbg !3068

if.else:                                          ; preds = %if.then5
  store i32 0, i32* %without_fds, align 4, !dbg !3069
  br label %if.end13

if.end13:                                         ; preds = %if.else, %if.end
  br label %if.end15, !dbg !3070

if.else14:                                        ; preds = %if.then
  store i32 0, i32* %without_fds, align 4, !dbg !3071
  br label %if.end15

if.end15:                                         ; preds = %if.else14, %if.end13
  %33 = load %struct.Curl_multi*, %struct.Curl_multi** %multi.addr, align 8, !dbg !3072
  %call16 = call i32 @curl_multi_perform(%struct.Curl_multi* %33, i32* %still_running), !dbg !3073
  store i32 %call16, i32* %mcode, align 4, !dbg !3074
  br label %if.end17, !dbg !3075

if.end17:                                         ; preds = %if.end15, %while.body
  %34 = load i32, i32* %mcode, align 4, !dbg !3076
  %tobool18 = icmp ne i32 %34, 0, !dbg !3076
  br i1 %tobool18, label %if.end26, label %land.lhs.true, !dbg !3078

land.lhs.true:                                    ; preds = %if.end17
  %35 = load i32, i32* %still_running, align 4, !dbg !3079
  %tobool19 = icmp ne i32 %35, 0, !dbg !3079
  br i1 %tobool19, label %if.end26, label %if.then20, !dbg !3081

if.then20:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata %struct.CURLMsg** %msg, metadata !3082, metadata !2138), !dbg !3086
  %36 = load %struct.Curl_multi*, %struct.Curl_multi** %multi.addr, align 8, !dbg !3087
  %call21 = call %struct.CURLMsg* @curl_multi_info_read(%struct.Curl_multi* %36, i32* %rc), !dbg !3088
  store %struct.CURLMsg* %call21, %struct.CURLMsg** %msg, align 8, !dbg !3086
  %37 = load %struct.CURLMsg*, %struct.CURLMsg** %msg, align 8, !dbg !3089
  %tobool22 = icmp ne %struct.CURLMsg* %37, null, !dbg !3089
  br i1 %tobool22, label %if.then23, label %if.end25, !dbg !3091

if.then23:                                        ; preds = %if.then20
  %38 = load %struct.CURLMsg*, %struct.CURLMsg** %msg, align 8, !dbg !3092
  %data = getelementptr inbounds %struct.CURLMsg, %struct.CURLMsg* %38, i32 0, i32 2, !dbg !3094
  %result24 = bitcast %union.anon.0* %data to i32*, !dbg !3095
  %39 = load i32, i32* %result24, align 8, !dbg !3095
  store i32 %39, i32* %result, align 4, !dbg !3096
  store i8 1, i8* %done, align 1, !dbg !3097
  br label %if.end25, !dbg !3098

if.end25:                                         ; preds = %if.then23, %if.then20
  br label %if.end26, !dbg !3099

if.end26:                                         ; preds = %if.end25, %land.lhs.true, %if.end17
  br label %while.cond, !dbg !3100

while.end:                                        ; preds = %land.end
  %40 = load i32, i32* %mcode, align 4, !dbg !3102
  %tobool27 = icmp ne i32 %40, 0, !dbg !3102
  br i1 %tobool27, label %if.then28, label %if.end31, !dbg !3104

if.then28:                                        ; preds = %while.end
  %41 = load i32, i32* %mcode, align 4, !dbg !3105
  %cmp29 = icmp eq i32 %41, 3, !dbg !3107
  %cond30 = select i1 %cmp29, i32 27, i32 43, !dbg !3108
  store i32 %cond30, i32* %result, align 4, !dbg !3109
  br label %if.end31, !dbg !3110

if.end31:                                         ; preds = %if.then28, %while.end
  %42 = load i32, i32* %result, align 4, !dbg !3111
  ret i32 %42, !dbg !3112
}

declare i32 @curl_multi_remove_handle(%struct.Curl_multi*, %struct.Curl_easy*) #3

declare { i64, i64 } @curlx_tvnow() #3

declare i32 @curl_multi_wait(%struct.Curl_multi*, %struct.curl_waitfd*, i32, i32, i32*) #3

declare i64 @curlx_tvdiff(i64, i64, i64, i64) #3

declare i32 @Curl_wait_ms(i32) #3

declare i32 @curl_multi_perform(%struct.Curl_multi*, i32*) #3

declare %struct.CURLMsg* @curl_multi_info_read(%struct.Curl_multi*, i32*) #3

declare i32 @Curl_getconnectinfo(%struct.Curl_easy*, %struct.connectdata**) #3

attributes #0 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readnone }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }
attributes #5 = { argmemonly nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!2134, !2135}
!llvm.ident = !{!2136}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !2049, subprograms: !2067, globals: !2126)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/easy.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !100, !111, !120, !126, !134, !173, !192, !212, !227, !244, !252, !266, !299, !368, !466, !476, !567, !584, !591, !730, !746, !758, !855, !865, !913, !931, !937, !963, !978, !987, !995, !1024, !1225, !1277, !1716, !1966, !2019, !2031}
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
!100 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !101, line: 31, size: 32, align: 32, elements: !102)
!101 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/http_chunks.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!102 = !{!103, !104, !105, !106, !107, !108, !109, !110}
!103 = !DIEnumerator(name: "CHUNK_HEX", value: 0)
!104 = !DIEnumerator(name: "CHUNK_LF", value: 1)
!105 = !DIEnumerator(name: "CHUNK_DATA", value: 2)
!106 = !DIEnumerator(name: "CHUNK_POSTLF", value: 3)
!107 = !DIEnumerator(name: "CHUNK_STOP", value: 4)
!108 = !DIEnumerator(name: "CHUNK_TRAILER", value: 5)
!109 = !DIEnumerator(name: "CHUNK_TRAILER_CR", value: 6)
!110 = !DIEnumerator(name: "CHUNK_TRAILER_POSTCR", value: 7)
!111 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 644, size: 32, align: 32, elements: !112)
!112 = !{!113, !114, !115, !116, !117, !118, !119}
!113 = !DIEnumerator(name: "CURLPROXY_HTTP", value: 0)
!114 = !DIEnumerator(name: "CURLPROXY_HTTP_1_0", value: 1)
!115 = !DIEnumerator(name: "CURLPROXY_HTTPS", value: 2)
!116 = !DIEnumerator(name: "CURLPROXY_SOCKS4", value: 4)
!117 = !DIEnumerator(name: "CURLPROXY_SOCKS5", value: 5)
!118 = !DIEnumerator(name: "CURLPROXY_SOCKS4A", value: 6)
!119 = !DIEnumerator(name: "CURLPROXY_SOCKS5_HOSTNAME", value: 7)
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
!289 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLcode", file: !4, line: 561, baseType: !3)
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
!306 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURL", file: !4, line: 100, baseType: !257)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !294, file: !295, line: 99, baseType: !308, size: 64, align: 64, offset: 128)
!308 = !DICompositeType(tag: DW_TAG_union_type, scope: !294, file: !295, line: 96, size: 64, align: 64, elements: !309)
!309 = !{!310, !312}
!310 = !DIDerivedType(tag: DW_TAG_member, name: "whatever", scope: !308, file: !295, line: 97, baseType: !311, size: 64, align: 64)
!311 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "result", scope: !308, file: !295, line: 98, baseType: !289, size: 32, align: 32)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "sockets", scope: !257, file: !121, line: 1817, baseType: !314, size: 160, align: 32, offset: 448)
!314 = !DICompositeType(tag: DW_TAG_array_type, baseType: !315, size: 160, align: 32, elements: !317)
!315 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socket_t", file: !4, line: 131, baseType: !316)
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
!461 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_lock_function", file: !4, line: 2365, baseType: !462)
!462 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !463, size: 64, align: 64)
!463 = !DISubroutineType(types: !464)
!464 = !{null, !305, !465, !475, !311}
!465 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_lock_data", file: !4, line: 2355, baseType: !466)
!466 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 2343, size: 32, align: 32, elements: !467)
!467 = !{!468, !469, !470, !471, !472, !473, !474}
!468 = !DIEnumerator(name: "CURL_LOCK_DATA_NONE", value: 0)
!469 = !DIEnumerator(name: "CURL_LOCK_DATA_SHARE", value: 1)
!470 = !DIEnumerator(name: "CURL_LOCK_DATA_COOKIE", value: 2)
!471 = !DIEnumerator(name: "CURL_LOCK_DATA_DNS", value: 3)
!472 = !DIEnumerator(name: "CURL_LOCK_DATA_SSL_SESSION", value: 4)
!473 = !DIEnumerator(name: "CURL_LOCK_DATA_CONNECT", value: 5)
!474 = !DIEnumerator(name: "CURL_LOCK_DATA_LAST", value: 6)
!475 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_lock_access", file: !4, line: 2363, baseType: !476)
!476 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 2358, size: 32, align: 32, elements: !477)
!477 = !{!478, !479, !480, !481}
!478 = !DIEnumerator(name: "CURL_LOCK_ACCESS_NONE", value: 0)
!479 = !DIEnumerator(name: "CURL_LOCK_ACCESS_SHARED", value: 1)
!480 = !DIEnumerator(name: "CURL_LOCK_ACCESS_SINGLE", value: 2)
!481 = !DIEnumerator(name: "CURL_LOCK_ACCESS_LAST", value: 3)
!482 = !DIDerivedType(tag: DW_TAG_member, name: "unlockfunc", scope: !453, file: !454, line: 44, baseType: !483, size: 64, align: 64, offset: 128)
!483 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_unlock_function", file: !4, line: 2369, baseType: !484)
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
!695 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_seek_callback", file: !4, line: 324, baseType: !696)
!696 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !697, size: 64, align: 64)
!697 = !DISubroutineType(types: !698)
!698 = !{!316, !311, !507, !316}
!699 = !DIDerivedType(tag: DW_TAG_member, name: "postfieldsize", scope: !622, file: !121, line: 1582, baseType: !507, size: 64, align: 64, offset: 1024)
!700 = !DIDerivedType(tag: DW_TAG_member, name: "localport", scope: !622, file: !121, line: 1585, baseType: !657, size: 16, align: 16, offset: 1088)
!701 = !DIDerivedType(tag: DW_TAG_member, name: "localportrange", scope: !622, file: !121, line: 1586, baseType: !316, size: 32, align: 32, offset: 1120)
!702 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_func", scope: !622, file: !121, line: 1588, baseType: !703, size: 64, align: 64, offset: 1152)
!703 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_write_callback", file: !4, line: 223, baseType: !704)
!704 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !705, size: 64, align: 64)
!705 = !DISubroutineType(types: !706)
!706 = !{!347, !500, !347, !347, !311}
!707 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_header", scope: !622, file: !121, line: 1589, baseType: !703, size: 64, align: 64, offset: 1216)
!708 = !DIDerivedType(tag: DW_TAG_member, name: "fwrite_rtp", scope: !622, file: !121, line: 1590, baseType: !703, size: 64, align: 64, offset: 1280)
!709 = !DIDerivedType(tag: DW_TAG_member, name: "fread_func_set", scope: !622, file: !121, line: 1591, baseType: !710, size: 64, align: 64, offset: 1344)
!710 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_read_callback", file: !4, line: 335, baseType: !704)
!711 = !DIDerivedType(tag: DW_TAG_member, name: "is_fread_set", scope: !622, file: !121, line: 1592, baseType: !316, size: 32, align: 32, offset: 1408)
!712 = !DIDerivedType(tag: DW_TAG_member, name: "is_fwrite_set", scope: !622, file: !121, line: 1593, baseType: !316, size: 32, align: 32, offset: 1440)
!713 = !DIDerivedType(tag: DW_TAG_member, name: "fprogress", scope: !622, file: !121, line: 1594, baseType: !714, size: 64, align: 64, offset: 1472)
!714 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_progress_callback", file: !4, line: 183, baseType: !715)
!715 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !716, size: 64, align: 64)
!716 = !DISubroutineType(types: !717)
!717 = !{!316, !311, !718, !718, !718, !718}
!718 = !DIBasicType(name: "double", size: 64, align: 64, encoding: DW_ATE_float)
!719 = !DIDerivedType(tag: DW_TAG_member, name: "fxferinfo", scope: !622, file: !121, line: 1595, baseType: !720, size: 64, align: 64, offset: 1536)
!720 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_xferinfo_callback", file: !4, line: 191, baseType: !721)
!721 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !722, size: 64, align: 64)
!722 = !DISubroutineType(types: !723)
!723 = !{!316, !311, !507, !507, !507, !507}
!724 = !DIDerivedType(tag: DW_TAG_member, name: "fdebug", scope: !622, file: !121, line: 1596, baseType: !725, size: 64, align: 64, offset: 1600)
!725 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_debug_callback", file: !4, line: 420, baseType: !726)
!726 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !727, size: 64, align: 64)
!727 = !DISubroutineType(types: !728)
!728 = !{!316, !305, !729, !500, !347, !311}
!729 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_infotype", file: !4, line: 418, baseType: !730)
!730 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 409, size: 32, align: 32, elements: !731)
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
!741 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ioctl_callback", file: !4, line: 388, baseType: !742)
!742 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !743, size: 64, align: 64)
!743 = !DISubroutineType(types: !744)
!744 = !{!745, !305, !316, !311}
!745 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlioerr", file: !4, line: 380, baseType: !746)
!746 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 375, size: 32, align: 32, elements: !747)
!747 = !{!748, !749, !750, !751}
!748 = !DIEnumerator(name: "CURLIOE_OK", value: 0)
!749 = !DIEnumerator(name: "CURLIOE_UNKNOWNCMD", value: 1)
!750 = !DIEnumerator(name: "CURLIOE_FAILRESTART", value: 2)
!751 = !DIEnumerator(name: "CURLIOE_LAST", value: 3)
!752 = !DIDerivedType(tag: DW_TAG_member, name: "fsockopt", scope: !622, file: !121, line: 1598, baseType: !753, size: 64, align: 64, offset: 1728)
!753 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sockopt_callback", file: !4, line: 353, baseType: !754)
!754 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !755, size: 64, align: 64)
!755 = !DISubroutineType(types: !756)
!756 = !{!316, !311, !315, !757}
!757 = !DIDerivedType(tag: DW_TAG_typedef, name: "curlsocktype", file: !4, line: 344, baseType: !758)
!758 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 340, size: 32, align: 32, elements: !759)
!759 = !{!760, !761, !762}
!760 = !DIEnumerator(name: "CURLSOCKTYPE_IPCXN", value: 0)
!761 = !DIEnumerator(name: "CURLSOCKTYPE_ACCEPT", value: 1)
!762 = !DIEnumerator(name: "CURLSOCKTYPE_LAST", value: 2)
!763 = !DIDerivedType(tag: DW_TAG_member, name: "sockopt_client", scope: !622, file: !121, line: 1599, baseType: !311, size: 64, align: 64, offset: 1792)
!764 = !DIDerivedType(tag: DW_TAG_member, name: "fopensocket", scope: !622, file: !121, line: 1600, baseType: !765, size: 64, align: 64, offset: 1856)
!765 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_opensocket_callback", file: !4, line: 368, baseType: !766)
!766 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !767, size: 64, align: 64)
!767 = !DISubroutineType(types: !768)
!768 = !{!315, !311, !757, !769}
!769 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !770, size: 64, align: 64)
!770 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_sockaddr", file: !4, line: 357, size: 256, align: 32, elements: !771)
!771 = !{!772, !773, !774, !775, !776}
!772 = !DIDerivedType(tag: DW_TAG_member, name: "family", scope: !770, file: !4, line: 358, baseType: !316, size: 32, align: 32)
!773 = !DIDerivedType(tag: DW_TAG_member, name: "socktype", scope: !770, file: !4, line: 359, baseType: !316, size: 32, align: 32, offset: 32)
!774 = !DIDerivedType(tag: DW_TAG_member, name: "protocol", scope: !770, file: !4, line: 360, baseType: !316, size: 32, align: 32, offset: 64)
!775 = !DIDerivedType(tag: DW_TAG_member, name: "addrlen", scope: !770, file: !4, line: 361, baseType: !457, size: 32, align: 32, offset: 96)
!776 = !DIDerivedType(tag: DW_TAG_member, name: "addr", scope: !770, file: !4, line: 364, baseType: !777, size: 128, align: 16, offset: 128)
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
!789 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_closesocket_callback", file: !4, line: 373, baseType: !790)
!790 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !791, size: 64, align: 64)
!791 = !DISubroutineType(types: !792)
!792 = !{!316, !311, !315}
!793 = !DIDerivedType(tag: DW_TAG_member, name: "closesocket_client", scope: !622, file: !121, line: 1606, baseType: !311, size: 64, align: 64, offset: 2048)
!794 = !DIDerivedType(tag: DW_TAG_member, name: "seek_client", scope: !622, file: !121, line: 1608, baseType: !311, size: 64, align: 64, offset: 2112)
!795 = !DIDerivedType(tag: DW_TAG_member, name: "convfromnetwork", scope: !622, file: !121, line: 1611, baseType: !796, size: 64, align: 64, offset: 2176)
!796 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_conv_callback", file: !4, line: 637, baseType: !797)
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
!818 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_slist", file: !4, line: 2176, size: 128, align: 64, elements: !819)
!819 = !{!820, !821}
!820 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !818, file: !4, line: 2177, baseType: !500, size: 64, align: 64)
!821 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !818, file: !4, line: 2178, baseType: !817, size: 64, align: 64, offset: 64)
!822 = !DIDerivedType(tag: DW_TAG_member, name: "proxyheaders", scope: !622, file: !121, line: 1633, baseType: !817, size: 64, align: 64, offset: 3328)
!823 = !DIDerivedType(tag: DW_TAG_member, name: "httppost", scope: !622, file: !121, line: 1634, baseType: !824, size: 64, align: 64, offset: 3392)
!824 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !825, size: 64, align: 64)
!825 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_httppost", file: !4, line: 137, size: 896, align: 64, elements: !826)
!826 = !{!827, !828, !829, !830, !831, !832, !833, !834, !835, !836, !837, !838, !839, !840}
!827 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !825, file: !4, line: 138, baseType: !824, size: 64, align: 64)
!828 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !825, file: !4, line: 139, baseType: !500, size: 64, align: 64, offset: 64)
!829 = !DIDerivedType(tag: DW_TAG_member, name: "namelength", scope: !825, file: !4, line: 140, baseType: !379, size: 64, align: 64, offset: 128)
!830 = !DIDerivedType(tag: DW_TAG_member, name: "contents", scope: !825, file: !4, line: 141, baseType: !500, size: 64, align: 64, offset: 192)
!831 = !DIDerivedType(tag: DW_TAG_member, name: "contentslength", scope: !825, file: !4, line: 142, baseType: !379, size: 64, align: 64, offset: 256)
!832 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !825, file: !4, line: 144, baseType: !500, size: 64, align: 64, offset: 320)
!833 = !DIDerivedType(tag: DW_TAG_member, name: "bufferlength", scope: !825, file: !4, line: 145, baseType: !379, size: 64, align: 64, offset: 384)
!834 = !DIDerivedType(tag: DW_TAG_member, name: "contenttype", scope: !825, file: !4, line: 146, baseType: !500, size: 64, align: 64, offset: 448)
!835 = !DIDerivedType(tag: DW_TAG_member, name: "contentheader", scope: !825, file: !4, line: 147, baseType: !817, size: 64, align: 64, offset: 512)
!836 = !DIDerivedType(tag: DW_TAG_member, name: "more", scope: !825, file: !4, line: 148, baseType: !824, size: 64, align: 64, offset: 576)
!837 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !825, file: !4, line: 151, baseType: !379, size: 64, align: 64, offset: 640)
!838 = !DIDerivedType(tag: DW_TAG_member, name: "showfilename", scope: !825, file: !4, line: 171, baseType: !500, size: 64, align: 64, offset: 704)
!839 = !DIDerivedType(tag: DW_TAG_member, name: "userp", scope: !825, file: !4, line: 174, baseType: !311, size: 64, align: 64, offset: 768)
!840 = !DIDerivedType(tag: DW_TAG_member, name: "contentlen", scope: !825, file: !4, line: 176, baseType: !507, size: 64, align: 64, offset: 832)
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
!854 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_TimeCond", file: !4, line: 1929, baseType: !855)
!855 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 1921, size: 32, align: 32, elements: !856)
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
!886 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ssl_ctx_callback", file: !4, line: 639, baseType: !887)
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
!904 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_proxytype", file: !4, line: 657, baseType: !111)
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
!920 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sshkeycallback", file: !4, line: 739, baseType: !921)
!921 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !922, size: 64, align: 64)
!922 = !DISubroutineType(types: !923)
!923 = !{!316, !305, !924, !924, !937, !311}
!924 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !925, size: 64, align: 64)
!925 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !926)
!926 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_khkey", file: !4, line: 711, size: 192, align: 64, elements: !927)
!927 = !{!928, !929, !930}
!928 = !DIDerivedType(tag: DW_TAG_member, name: "key", scope: !926, file: !4, line: 712, baseType: !527, size: 64, align: 64)
!929 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !926, file: !4, line: 714, baseType: !347, size: 64, align: 64, offset: 64)
!930 = !DIDerivedType(tag: DW_TAG_member, name: "keytype", scope: !926, file: !4, line: 715, baseType: !931, size: 32, align: 32, offset: 128)
!931 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khtype", file: !4, line: 704, size: 32, align: 32, elements: !932)
!932 = !{!933, !934, !935, !936}
!933 = !DIEnumerator(name: "CURLKHTYPE_UNKNOWN", value: 0)
!934 = !DIEnumerator(name: "CURLKHTYPE_RSA1", value: 1)
!935 = !DIEnumerator(name: "CURLKHTYPE_RSA", value: 2)
!936 = !DIEnumerator(name: "CURLKHTYPE_DSS", value: 3)
!937 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "curl_khmatch", file: !4, line: 731, size: 32, align: 32, elements: !938)
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
!963 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "CURL_NETRC_OPTION", file: !4, line: 1867, size: 32, align: 32, elements: !964)
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
!977 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_usessl", file: !4, line: 752, baseType: !978)
!978 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 746, size: 32, align: 32, elements: !979)
!979 = !{!980, !981, !982, !983, !984}
!980 = !DIEnumerator(name: "CURLUSESSL_NONE", value: 0)
!981 = !DIEnumerator(name: "CURLUSESSL_TRY", value: 1)
!982 = !DIEnumerator(name: "CURLUSESSL_CONTROL", value: 2)
!983 = !DIEnumerator(name: "CURLUSESSL_ALL", value: 3)
!984 = !DIEnumerator(name: "CURLUSESSL_LAST", value: 4)
!985 = !DIDerivedType(tag: DW_TAG_member, name: "ftpsslauth", scope: !622, file: !121, line: 1714, baseType: !986, size: 32, align: 32, offset: 8160)
!986 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpauth", file: !4, line: 795, baseType: !987)
!987 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 790, size: 32, align: 32, elements: !988)
!988 = !{!989, !990, !991, !992}
!989 = !DIEnumerator(name: "CURLFTPAUTH_DEFAULT", value: 0)
!990 = !DIEnumerator(name: "CURLFTPAUTH_SSL", value: 1)
!991 = !DIEnumerator(name: "CURLFTPAUTH_TLS", value: 2)
!992 = !DIEnumerator(name: "CURLFTPAUTH_LAST", value: 3)
!993 = !DIDerivedType(tag: DW_TAG_member, name: "ftp_ccc", scope: !622, file: !121, line: 1715, baseType: !994, size: 32, align: 32, offset: 8192)
!994 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_ftpccc", file: !4, line: 787, baseType: !995)
!995 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 782, size: 32, align: 32, elements: !996)
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
!1042 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_bgn_callback", file: !4, line: 292, baseType: !1043)
!1043 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1044, size: 64, align: 64)
!1044 = !DISubroutineType(types: !1045)
!1045 = !{!379, !1046, !311, !316}
!1046 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1047, size: 64, align: 64)
!1047 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!1048 = !DIDerivedType(tag: DW_TAG_member, name: "chunk_end", scope: !622, file: !121, line: 1747, baseType: !1049, size: 64, align: 64, offset: 12736)
!1049 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_chunk_end_callback", file: !4, line: 306, baseType: !1050)
!1050 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !1051, size: 64, align: 64)
!1051 = !DISubroutineType(types: !1052)
!1052 = !{!379, !311}
!1053 = !DIDerivedType(tag: DW_TAG_member, name: "fnmatch", scope: !622, file: !121, line: 1749, baseType: !1054, size: 64, align: 64, offset: 12800)
!1054 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_fnmatch_callback", file: !4, line: 315, baseType: !1055)
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
!1267 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_certinfo", file: !4, line: 2214, size: 128, align: 64, elements: !1268)
!1268 = !{!1269, !1270}
!1269 = !DIDerivedType(tag: DW_TAG_member, name: "num_of_certs", scope: !1267, file: !4, line: 2215, baseType: !316, size: 32, align: 32)
!1270 = !DIDerivedType(tag: DW_TAG_member, name: "certinfo", scope: !1267, file: !4, line: 2216, baseType: !1271, size: 64, align: 64, offset: 64)
!1271 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !817, size: 64, align: 64)
!1272 = !DIDerivedType(tag: DW_TAG_member, name: "tsi", scope: !257, file: !121, line: 1840, baseType: !1273, size: 128, align: 64, offset: 160000)
!1273 = !DICompositeType(tag: DW_TAG_structure_type, name: "curl_tlssessioninfo", file: !4, line: 2245, size: 128, align: 64, elements: !1274)
!1274 = !{!1275, !1291}
!1275 = !DIDerivedType(tag: DW_TAG_member, name: "backend", scope: !1273, file: !4, line: 2246, baseType: !1276, size: 32, align: 32)
!1276 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_sslbackend", file: !4, line: 2235, baseType: !1277)
!1277 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 2222, size: 32, align: 32, elements: !1278)
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
!1291 = !DIDerivedType(tag: DW_TAG_member, name: "internals", scope: !1273, file: !4, line: 2247, baseType: !311, size: 64, align: 64, offset: 64)
!1292 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !257, file: !121, line: 1847, baseType: !457, size: 32, align: 32, offset: 160128)
!1293 = !DIDerivedType(tag: DW_TAG_member, name: "chunk", scope: !253, file: !121, line: 904, baseType: !1294, size: 384, align: 64, offset: 64)
!1294 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_chunker", file: !101, line: 82, size: 384, align: 64, elements: !1295)
!1295 = !{!1296, !1300, !1301, !1303, !1304}
!1296 = !DIDerivedType(tag: DW_TAG_member, name: "hexbuffer", scope: !1294, file: !101, line: 83, baseType: !1297, size: 136, align: 8)
!1297 = !DICompositeType(tag: DW_TAG_array_type, baseType: !501, size: 136, align: 8, elements: !1298)
!1298 = !{!1299}
!1299 = !DISubrange(count: 17)
!1300 = !DIDerivedType(tag: DW_TAG_member, name: "hexindex", scope: !1294, file: !101, line: 84, baseType: !316, size: 32, align: 32, offset: 160)
!1301 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !1294, file: !101, line: 85, baseType: !1302, size: 32, align: 32, offset: 192)
!1302 = !DIDerivedType(tag: DW_TAG_typedef, name: "ChunkyState", file: !101, line: 66, baseType: !100)
!1303 = !DIDerivedType(tag: DW_TAG_member, name: "datasize", scope: !1294, file: !101, line: 86, baseType: !507, size: 64, align: 64, offset: 256)
!1304 = !DIDerivedType(tag: DW_TAG_member, name: "dataleft", scope: !1294, file: !101, line: 87, baseType: !347, size: 64, align: 64, offset: 320)
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
!1716 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 888, size: 32, align: 32, elements: !1717)
!1717 = !{!1718, !1719, !1720, !1721, !1722, !1723, !1724, !1725, !1726, !1727, !1728, !1729, !1730, !1731, !1732, !1733, !1734, !1735, !1736, !1737, !1738, !1739, !1740, !1741, !1742, !1743, !1744, !1745, !1746, !1747, !1748, !1749, !1750, !1751, !1752, !1753, !1754, !1755, !1756, !1757, !1758, !1759, !1760, !1761, !1762, !1763, !1764, !1765, !1766, !1767, !1768, !1769, !1770, !1771, !1772, !1773, !1774, !1775, !1776, !1777, !1778, !1779, !1780, !1781, !1782, !1783, !1784, !1785, !1786, !1787, !1788, !1789, !1790, !1791, !1792, !1793, !1794, !1795, !1796, !1797, !1798, !1799, !1800, !1801, !1802, !1803, !1804, !1805, !1806, !1807, !1808, !1809, !1810, !1811, !1812, !1813, !1814, !1815, !1816, !1817, !1818, !1819, !1820, !1821, !1822, !1823, !1824, !1825, !1826, !1827, !1828, !1829, !1830, !1831, !1832, !1833, !1834, !1835, !1836, !1837, !1838, !1839, !1840, !1841, !1842, !1843, !1844, !1845, !1846, !1847, !1848, !1849, !1850, !1851, !1852, !1853, !1854, !1855, !1856, !1857, !1858, !1859, !1860, !1861, !1862, !1863, !1864, !1865, !1866, !1867, !1868, !1869, !1870, !1871, !1872, !1873, !1874, !1875, !1876, !1877, !1878, !1879, !1880, !1881, !1882, !1883, !1884, !1885, !1886, !1887, !1888, !1889, !1890, !1891, !1892, !1893, !1894, !1895, !1896, !1897, !1898, !1899, !1900, !1901, !1902, !1903, !1904, !1905, !1906, !1907, !1908, !1909, !1910, !1911, !1912, !1913, !1914, !1915, !1916, !1917, !1918, !1919, !1920, !1921, !1922, !1923, !1924, !1925, !1926, !1927, !1928, !1929, !1930, !1931, !1932, !1933, !1934, !1935, !1936, !1937, !1938, !1939, !1940, !1941, !1942, !1943, !1944, !1945, !1946, !1947, !1948, !1949, !1950, !1951, !1952, !1953, !1954, !1955, !1956, !1957, !1958, !1959, !1960, !1961, !1962, !1963, !1964, !1965}
!1718 = !DIEnumerator(name: "CURLOPT_WRITEDATA", value: 10001)
!1719 = !DIEnumerator(name: "CURLOPT_URL", value: 10002)
!1720 = !DIEnumerator(name: "CURLOPT_PORT", value: 3)
!1721 = !DIEnumerator(name: "CURLOPT_PROXY", value: 10004)
!1722 = !DIEnumerator(name: "CURLOPT_USERPWD", value: 10005)
!1723 = !DIEnumerator(name: "CURLOPT_PROXYUSERPWD", value: 10006)
!1724 = !DIEnumerator(name: "CURLOPT_RANGE", value: 10007)
!1725 = !DIEnumerator(name: "CURLOPT_READDATA", value: 10009)
!1726 = !DIEnumerator(name: "CURLOPT_ERRORBUFFER", value: 10010)
!1727 = !DIEnumerator(name: "CURLOPT_WRITEFUNCTION", value: 20011)
!1728 = !DIEnumerator(name: "CURLOPT_READFUNCTION", value: 20012)
!1729 = !DIEnumerator(name: "CURLOPT_TIMEOUT", value: 13)
!1730 = !DIEnumerator(name: "CURLOPT_INFILESIZE", value: 14)
!1731 = !DIEnumerator(name: "CURLOPT_POSTFIELDS", value: 10015)
!1732 = !DIEnumerator(name: "CURLOPT_REFERER", value: 10016)
!1733 = !DIEnumerator(name: "CURLOPT_FTPPORT", value: 10017)
!1734 = !DIEnumerator(name: "CURLOPT_USERAGENT", value: 10018)
!1735 = !DIEnumerator(name: "CURLOPT_LOW_SPEED_LIMIT", value: 19)
!1736 = !DIEnumerator(name: "CURLOPT_LOW_SPEED_TIME", value: 20)
!1737 = !DIEnumerator(name: "CURLOPT_RESUME_FROM", value: 21)
!1738 = !DIEnumerator(name: "CURLOPT_COOKIE", value: 10022)
!1739 = !DIEnumerator(name: "CURLOPT_HTTPHEADER", value: 10023)
!1740 = !DIEnumerator(name: "CURLOPT_HTTPPOST", value: 10024)
!1741 = !DIEnumerator(name: "CURLOPT_SSLCERT", value: 10025)
!1742 = !DIEnumerator(name: "CURLOPT_KEYPASSWD", value: 10026)
!1743 = !DIEnumerator(name: "CURLOPT_CRLF", value: 27)
!1744 = !DIEnumerator(name: "CURLOPT_QUOTE", value: 10028)
!1745 = !DIEnumerator(name: "CURLOPT_HEADERDATA", value: 10029)
!1746 = !DIEnumerator(name: "CURLOPT_COOKIEFILE", value: 10031)
!1747 = !DIEnumerator(name: "CURLOPT_SSLVERSION", value: 32)
!1748 = !DIEnumerator(name: "CURLOPT_TIMECONDITION", value: 33)
!1749 = !DIEnumerator(name: "CURLOPT_TIMEVALUE", value: 34)
!1750 = !DIEnumerator(name: "CURLOPT_CUSTOMREQUEST", value: 10036)
!1751 = !DIEnumerator(name: "CURLOPT_STDERR", value: 10037)
!1752 = !DIEnumerator(name: "CURLOPT_POSTQUOTE", value: 10039)
!1753 = !DIEnumerator(name: "CURLOPT_OBSOLETE40", value: 10040)
!1754 = !DIEnumerator(name: "CURLOPT_VERBOSE", value: 41)
!1755 = !DIEnumerator(name: "CURLOPT_HEADER", value: 42)
!1756 = !DIEnumerator(name: "CURLOPT_NOPROGRESS", value: 43)
!1757 = !DIEnumerator(name: "CURLOPT_NOBODY", value: 44)
!1758 = !DIEnumerator(name: "CURLOPT_FAILONERROR", value: 45)
!1759 = !DIEnumerator(name: "CURLOPT_UPLOAD", value: 46)
!1760 = !DIEnumerator(name: "CURLOPT_POST", value: 47)
!1761 = !DIEnumerator(name: "CURLOPT_DIRLISTONLY", value: 48)
!1762 = !DIEnumerator(name: "CURLOPT_APPEND", value: 50)
!1763 = !DIEnumerator(name: "CURLOPT_NETRC", value: 51)
!1764 = !DIEnumerator(name: "CURLOPT_FOLLOWLOCATION", value: 52)
!1765 = !DIEnumerator(name: "CURLOPT_TRANSFERTEXT", value: 53)
!1766 = !DIEnumerator(name: "CURLOPT_PUT", value: 54)
!1767 = !DIEnumerator(name: "CURLOPT_PROGRESSFUNCTION", value: 20056)
!1768 = !DIEnumerator(name: "CURLOPT_PROGRESSDATA", value: 10057)
!1769 = !DIEnumerator(name: "CURLOPT_AUTOREFERER", value: 58)
!1770 = !DIEnumerator(name: "CURLOPT_PROXYPORT", value: 59)
!1771 = !DIEnumerator(name: "CURLOPT_POSTFIELDSIZE", value: 60)
!1772 = !DIEnumerator(name: "CURLOPT_HTTPPROXYTUNNEL", value: 61)
!1773 = !DIEnumerator(name: "CURLOPT_INTERFACE", value: 10062)
!1774 = !DIEnumerator(name: "CURLOPT_KRBLEVEL", value: 10063)
!1775 = !DIEnumerator(name: "CURLOPT_SSL_VERIFYPEER", value: 64)
!1776 = !DIEnumerator(name: "CURLOPT_CAINFO", value: 10065)
!1777 = !DIEnumerator(name: "CURLOPT_MAXREDIRS", value: 68)
!1778 = !DIEnumerator(name: "CURLOPT_FILETIME", value: 69)
!1779 = !DIEnumerator(name: "CURLOPT_TELNETOPTIONS", value: 10070)
!1780 = !DIEnumerator(name: "CURLOPT_MAXCONNECTS", value: 71)
!1781 = !DIEnumerator(name: "CURLOPT_OBSOLETE72", value: 72)
!1782 = !DIEnumerator(name: "CURLOPT_FRESH_CONNECT", value: 74)
!1783 = !DIEnumerator(name: "CURLOPT_FORBID_REUSE", value: 75)
!1784 = !DIEnumerator(name: "CURLOPT_RANDOM_FILE", value: 10076)
!1785 = !DIEnumerator(name: "CURLOPT_EGDSOCKET", value: 10077)
!1786 = !DIEnumerator(name: "CURLOPT_CONNECTTIMEOUT", value: 78)
!1787 = !DIEnumerator(name: "CURLOPT_HEADERFUNCTION", value: 20079)
!1788 = !DIEnumerator(name: "CURLOPT_HTTPGET", value: 80)
!1789 = !DIEnumerator(name: "CURLOPT_SSL_VERIFYHOST", value: 81)
!1790 = !DIEnumerator(name: "CURLOPT_COOKIEJAR", value: 10082)
!1791 = !DIEnumerator(name: "CURLOPT_SSL_CIPHER_LIST", value: 10083)
!1792 = !DIEnumerator(name: "CURLOPT_HTTP_VERSION", value: 84)
!1793 = !DIEnumerator(name: "CURLOPT_FTP_USE_EPSV", value: 85)
!1794 = !DIEnumerator(name: "CURLOPT_SSLCERTTYPE", value: 10086)
!1795 = !DIEnumerator(name: "CURLOPT_SSLKEY", value: 10087)
!1796 = !DIEnumerator(name: "CURLOPT_SSLKEYTYPE", value: 10088)
!1797 = !DIEnumerator(name: "CURLOPT_SSLENGINE", value: 10089)
!1798 = !DIEnumerator(name: "CURLOPT_SSLENGINE_DEFAULT", value: 90)
!1799 = !DIEnumerator(name: "CURLOPT_DNS_USE_GLOBAL_CACHE", value: 91)
!1800 = !DIEnumerator(name: "CURLOPT_DNS_CACHE_TIMEOUT", value: 92)
!1801 = !DIEnumerator(name: "CURLOPT_PREQUOTE", value: 10093)
!1802 = !DIEnumerator(name: "CURLOPT_DEBUGFUNCTION", value: 20094)
!1803 = !DIEnumerator(name: "CURLOPT_DEBUGDATA", value: 10095)
!1804 = !DIEnumerator(name: "CURLOPT_COOKIESESSION", value: 96)
!1805 = !DIEnumerator(name: "CURLOPT_CAPATH", value: 10097)
!1806 = !DIEnumerator(name: "CURLOPT_BUFFERSIZE", value: 98)
!1807 = !DIEnumerator(name: "CURLOPT_NOSIGNAL", value: 99)
!1808 = !DIEnumerator(name: "CURLOPT_SHARE", value: 10100)
!1809 = !DIEnumerator(name: "CURLOPT_PROXYTYPE", value: 101)
!1810 = !DIEnumerator(name: "CURLOPT_ACCEPT_ENCODING", value: 10102)
!1811 = !DIEnumerator(name: "CURLOPT_PRIVATE", value: 10103)
!1812 = !DIEnumerator(name: "CURLOPT_HTTP200ALIASES", value: 10104)
!1813 = !DIEnumerator(name: "CURLOPT_UNRESTRICTED_AUTH", value: 105)
!1814 = !DIEnumerator(name: "CURLOPT_FTP_USE_EPRT", value: 106)
!1815 = !DIEnumerator(name: "CURLOPT_HTTPAUTH", value: 107)
!1816 = !DIEnumerator(name: "CURLOPT_SSL_CTX_FUNCTION", value: 20108)
!1817 = !DIEnumerator(name: "CURLOPT_SSL_CTX_DATA", value: 10109)
!1818 = !DIEnumerator(name: "CURLOPT_FTP_CREATE_MISSING_DIRS", value: 110)
!1819 = !DIEnumerator(name: "CURLOPT_PROXYAUTH", value: 111)
!1820 = !DIEnumerator(name: "CURLOPT_FTP_RESPONSE_TIMEOUT", value: 112)
!1821 = !DIEnumerator(name: "CURLOPT_IPRESOLVE", value: 113)
!1822 = !DIEnumerator(name: "CURLOPT_MAXFILESIZE", value: 114)
!1823 = !DIEnumerator(name: "CURLOPT_INFILESIZE_LARGE", value: 30115)
!1824 = !DIEnumerator(name: "CURLOPT_RESUME_FROM_LARGE", value: 30116)
!1825 = !DIEnumerator(name: "CURLOPT_MAXFILESIZE_LARGE", value: 30117)
!1826 = !DIEnumerator(name: "CURLOPT_NETRC_FILE", value: 10118)
!1827 = !DIEnumerator(name: "CURLOPT_USE_SSL", value: 119)
!1828 = !DIEnumerator(name: "CURLOPT_POSTFIELDSIZE_LARGE", value: 30120)
!1829 = !DIEnumerator(name: "CURLOPT_TCP_NODELAY", value: 121)
!1830 = !DIEnumerator(name: "CURLOPT_FTPSSLAUTH", value: 129)
!1831 = !DIEnumerator(name: "CURLOPT_IOCTLFUNCTION", value: 20130)
!1832 = !DIEnumerator(name: "CURLOPT_IOCTLDATA", value: 10131)
!1833 = !DIEnumerator(name: "CURLOPT_FTP_ACCOUNT", value: 10134)
!1834 = !DIEnumerator(name: "CURLOPT_COOKIELIST", value: 10135)
!1835 = !DIEnumerator(name: "CURLOPT_IGNORE_CONTENT_LENGTH", value: 136)
!1836 = !DIEnumerator(name: "CURLOPT_FTP_SKIP_PASV_IP", value: 137)
!1837 = !DIEnumerator(name: "CURLOPT_FTP_FILEMETHOD", value: 138)
!1838 = !DIEnumerator(name: "CURLOPT_LOCALPORT", value: 139)
!1839 = !DIEnumerator(name: "CURLOPT_LOCALPORTRANGE", value: 140)
!1840 = !DIEnumerator(name: "CURLOPT_CONNECT_ONLY", value: 141)
!1841 = !DIEnumerator(name: "CURLOPT_CONV_FROM_NETWORK_FUNCTION", value: 20142)
!1842 = !DIEnumerator(name: "CURLOPT_CONV_TO_NETWORK_FUNCTION", value: 20143)
!1843 = !DIEnumerator(name: "CURLOPT_CONV_FROM_UTF8_FUNCTION", value: 20144)
!1844 = !DIEnumerator(name: "CURLOPT_MAX_SEND_SPEED_LARGE", value: 30145)
!1845 = !DIEnumerator(name: "CURLOPT_MAX_RECV_SPEED_LARGE", value: 30146)
!1846 = !DIEnumerator(name: "CURLOPT_FTP_ALTERNATIVE_TO_USER", value: 10147)
!1847 = !DIEnumerator(name: "CURLOPT_SOCKOPTFUNCTION", value: 20148)
!1848 = !DIEnumerator(name: "CURLOPT_SOCKOPTDATA", value: 10149)
!1849 = !DIEnumerator(name: "CURLOPT_SSL_SESSIONID_CACHE", value: 150)
!1850 = !DIEnumerator(name: "CURLOPT_SSH_AUTH_TYPES", value: 151)
!1851 = !DIEnumerator(name: "CURLOPT_SSH_PUBLIC_KEYFILE", value: 10152)
!1852 = !DIEnumerator(name: "CURLOPT_SSH_PRIVATE_KEYFILE", value: 10153)
!1853 = !DIEnumerator(name: "CURLOPT_FTP_SSL_CCC", value: 154)
!1854 = !DIEnumerator(name: "CURLOPT_TIMEOUT_MS", value: 155)
!1855 = !DIEnumerator(name: "CURLOPT_CONNECTTIMEOUT_MS", value: 156)
!1856 = !DIEnumerator(name: "CURLOPT_HTTP_TRANSFER_DECODING", value: 157)
!1857 = !DIEnumerator(name: "CURLOPT_HTTP_CONTENT_DECODING", value: 158)
!1858 = !DIEnumerator(name: "CURLOPT_NEW_FILE_PERMS", value: 159)
!1859 = !DIEnumerator(name: "CURLOPT_NEW_DIRECTORY_PERMS", value: 160)
!1860 = !DIEnumerator(name: "CURLOPT_POSTREDIR", value: 161)
!1861 = !DIEnumerator(name: "CURLOPT_SSH_HOST_PUBLIC_KEY_MD5", value: 10162)
!1862 = !DIEnumerator(name: "CURLOPT_OPENSOCKETFUNCTION", value: 20163)
!1863 = !DIEnumerator(name: "CURLOPT_OPENSOCKETDATA", value: 10164)
!1864 = !DIEnumerator(name: "CURLOPT_COPYPOSTFIELDS", value: 10165)
!1865 = !DIEnumerator(name: "CURLOPT_PROXY_TRANSFER_MODE", value: 166)
!1866 = !DIEnumerator(name: "CURLOPT_SEEKFUNCTION", value: 20167)
!1867 = !DIEnumerator(name: "CURLOPT_SEEKDATA", value: 10168)
!1868 = !DIEnumerator(name: "CURLOPT_CRLFILE", value: 10169)
!1869 = !DIEnumerator(name: "CURLOPT_ISSUERCERT", value: 10170)
!1870 = !DIEnumerator(name: "CURLOPT_ADDRESS_SCOPE", value: 171)
!1871 = !DIEnumerator(name: "CURLOPT_CERTINFO", value: 172)
!1872 = !DIEnumerator(name: "CURLOPT_USERNAME", value: 10173)
!1873 = !DIEnumerator(name: "CURLOPT_PASSWORD", value: 10174)
!1874 = !DIEnumerator(name: "CURLOPT_PROXYUSERNAME", value: 10175)
!1875 = !DIEnumerator(name: "CURLOPT_PROXYPASSWORD", value: 10176)
!1876 = !DIEnumerator(name: "CURLOPT_NOPROXY", value: 10177)
!1877 = !DIEnumerator(name: "CURLOPT_TFTP_BLKSIZE", value: 178)
!1878 = !DIEnumerator(name: "CURLOPT_SOCKS5_GSSAPI_SERVICE", value: 10179)
!1879 = !DIEnumerator(name: "CURLOPT_SOCKS5_GSSAPI_NEC", value: 180)
!1880 = !DIEnumerator(name: "CURLOPT_PROTOCOLS", value: 181)
!1881 = !DIEnumerator(name: "CURLOPT_REDIR_PROTOCOLS", value: 182)
!1882 = !DIEnumerator(name: "CURLOPT_SSH_KNOWNHOSTS", value: 10183)
!1883 = !DIEnumerator(name: "CURLOPT_SSH_KEYFUNCTION", value: 20184)
!1884 = !DIEnumerator(name: "CURLOPT_SSH_KEYDATA", value: 10185)
!1885 = !DIEnumerator(name: "CURLOPT_MAIL_FROM", value: 10186)
!1886 = !DIEnumerator(name: "CURLOPT_MAIL_RCPT", value: 10187)
!1887 = !DIEnumerator(name: "CURLOPT_FTP_USE_PRET", value: 188)
!1888 = !DIEnumerator(name: "CURLOPT_RTSP_REQUEST", value: 189)
!1889 = !DIEnumerator(name: "CURLOPT_RTSP_SESSION_ID", value: 10190)
!1890 = !DIEnumerator(name: "CURLOPT_RTSP_STREAM_URI", value: 10191)
!1891 = !DIEnumerator(name: "CURLOPT_RTSP_TRANSPORT", value: 10192)
!1892 = !DIEnumerator(name: "CURLOPT_RTSP_CLIENT_CSEQ", value: 193)
!1893 = !DIEnumerator(name: "CURLOPT_RTSP_SERVER_CSEQ", value: 194)
!1894 = !DIEnumerator(name: "CURLOPT_INTERLEAVEDATA", value: 10195)
!1895 = !DIEnumerator(name: "CURLOPT_INTERLEAVEFUNCTION", value: 20196)
!1896 = !DIEnumerator(name: "CURLOPT_WILDCARDMATCH", value: 197)
!1897 = !DIEnumerator(name: "CURLOPT_CHUNK_BGN_FUNCTION", value: 20198)
!1898 = !DIEnumerator(name: "CURLOPT_CHUNK_END_FUNCTION", value: 20199)
!1899 = !DIEnumerator(name: "CURLOPT_FNMATCH_FUNCTION", value: 20200)
!1900 = !DIEnumerator(name: "CURLOPT_CHUNK_DATA", value: 10201)
!1901 = !DIEnumerator(name: "CURLOPT_FNMATCH_DATA", value: 10202)
!1902 = !DIEnumerator(name: "CURLOPT_RESOLVE", value: 10203)
!1903 = !DIEnumerator(name: "CURLOPT_TLSAUTH_USERNAME", value: 10204)
!1904 = !DIEnumerator(name: "CURLOPT_TLSAUTH_PASSWORD", value: 10205)
!1905 = !DIEnumerator(name: "CURLOPT_TLSAUTH_TYPE", value: 10206)
!1906 = !DIEnumerator(name: "CURLOPT_TRANSFER_ENCODING", value: 207)
!1907 = !DIEnumerator(name: "CURLOPT_CLOSESOCKETFUNCTION", value: 20208)
!1908 = !DIEnumerator(name: "CURLOPT_CLOSESOCKETDATA", value: 10209)
!1909 = !DIEnumerator(name: "CURLOPT_GSSAPI_DELEGATION", value: 210)
!1910 = !DIEnumerator(name: "CURLOPT_DNS_SERVERS", value: 10211)
!1911 = !DIEnumerator(name: "CURLOPT_ACCEPTTIMEOUT_MS", value: 212)
!1912 = !DIEnumerator(name: "CURLOPT_TCP_KEEPALIVE", value: 213)
!1913 = !DIEnumerator(name: "CURLOPT_TCP_KEEPIDLE", value: 214)
!1914 = !DIEnumerator(name: "CURLOPT_TCP_KEEPINTVL", value: 215)
!1915 = !DIEnumerator(name: "CURLOPT_SSL_OPTIONS", value: 216)
!1916 = !DIEnumerator(name: "CURLOPT_MAIL_AUTH", value: 10217)
!1917 = !DIEnumerator(name: "CURLOPT_SASL_IR", value: 218)
!1918 = !DIEnumerator(name: "CURLOPT_XFERINFOFUNCTION", value: 20219)
!1919 = !DIEnumerator(name: "CURLOPT_XOAUTH2_BEARER", value: 10220)
!1920 = !DIEnumerator(name: "CURLOPT_DNS_INTERFACE", value: 10221)
!1921 = !DIEnumerator(name: "CURLOPT_DNS_LOCAL_IP4", value: 10222)
!1922 = !DIEnumerator(name: "CURLOPT_DNS_LOCAL_IP6", value: 10223)
!1923 = !DIEnumerator(name: "CURLOPT_LOGIN_OPTIONS", value: 10224)
!1924 = !DIEnumerator(name: "CURLOPT_SSL_ENABLE_NPN", value: 225)
!1925 = !DIEnumerator(name: "CURLOPT_SSL_ENABLE_ALPN", value: 226)
!1926 = !DIEnumerator(name: "CURLOPT_EXPECT_100_TIMEOUT_MS", value: 227)
!1927 = !DIEnumerator(name: "CURLOPT_PROXYHEADER", value: 10228)
!1928 = !DIEnumerator(name: "CURLOPT_HEADEROPT", value: 229)
!1929 = !DIEnumerator(name: "CURLOPT_PINNEDPUBLICKEY", value: 10230)
!1930 = !DIEnumerator(name: "CURLOPT_UNIX_SOCKET_PATH", value: 10231)
!1931 = !DIEnumerator(name: "CURLOPT_SSL_VERIFYSTATUS", value: 232)
!1932 = !DIEnumerator(name: "CURLOPT_SSL_FALSESTART", value: 233)
!1933 = !DIEnumerator(name: "CURLOPT_PATH_AS_IS", value: 234)
!1934 = !DIEnumerator(name: "CURLOPT_PROXY_SERVICE_NAME", value: 10235)
!1935 = !DIEnumerator(name: "CURLOPT_SERVICE_NAME", value: 10236)
!1936 = !DIEnumerator(name: "CURLOPT_PIPEWAIT", value: 237)
!1937 = !DIEnumerator(name: "CURLOPT_DEFAULT_PROTOCOL", value: 10238)
!1938 = !DIEnumerator(name: "CURLOPT_STREAM_WEIGHT", value: 239)
!1939 = !DIEnumerator(name: "CURLOPT_STREAM_DEPENDS", value: 10240)
!1940 = !DIEnumerator(name: "CURLOPT_STREAM_DEPENDS_E", value: 10241)
!1941 = !DIEnumerator(name: "CURLOPT_TFTP_NO_OPTIONS", value: 242)
!1942 = !DIEnumerator(name: "CURLOPT_CONNECT_TO", value: 10243)
!1943 = !DIEnumerator(name: "CURLOPT_TCP_FASTOPEN", value: 244)
!1944 = !DIEnumerator(name: "CURLOPT_KEEP_SENDING_ON_ERROR", value: 245)
!1945 = !DIEnumerator(name: "CURLOPT_PROXY_CAINFO", value: 10246)
!1946 = !DIEnumerator(name: "CURLOPT_PROXY_CAPATH", value: 10247)
!1947 = !DIEnumerator(name: "CURLOPT_PROXY_SSL_VERIFYPEER", value: 248)
!1948 = !DIEnumerator(name: "CURLOPT_PROXY_SSL_VERIFYHOST", value: 249)
!1949 = !DIEnumerator(name: "CURLOPT_PROXY_SSLVERSION", value: 250)
!1950 = !DIEnumerator(name: "CURLOPT_PROXY_TLSAUTH_USERNAME", value: 10251)
!1951 = !DIEnumerator(name: "CURLOPT_PROXY_TLSAUTH_PASSWORD", value: 10252)
!1952 = !DIEnumerator(name: "CURLOPT_PROXY_TLSAUTH_TYPE", value: 10253)
!1953 = !DIEnumerator(name: "CURLOPT_PROXY_SSLCERT", value: 10254)
!1954 = !DIEnumerator(name: "CURLOPT_PROXY_SSLCERTTYPE", value: 10255)
!1955 = !DIEnumerator(name: "CURLOPT_PROXY_SSLKEY", value: 10256)
!1956 = !DIEnumerator(name: "CURLOPT_PROXY_SSLKEYTYPE", value: 10257)
!1957 = !DIEnumerator(name: "CURLOPT_PROXY_KEYPASSWD", value: 10258)
!1958 = !DIEnumerator(name: "CURLOPT_PROXY_SSL_CIPHER_LIST", value: 10259)
!1959 = !DIEnumerator(name: "CURLOPT_PROXY_CRLFILE", value: 10260)
!1960 = !DIEnumerator(name: "CURLOPT_PROXY_SSL_OPTIONS", value: 261)
!1961 = !DIEnumerator(name: "CURLOPT_PRE_PROXY", value: 10262)
!1962 = !DIEnumerator(name: "CURLOPT_PROXY_PINNEDPUBLICKEY", value: 10263)
!1963 = !DIEnumerator(name: "CURLOPT_ABSTRACT_UNIX_SOCKET", value: 10264)
!1964 = !DIEnumerator(name: "CURLOPT_SUPPRESS_CONNECT_HEADERS", value: 265)
!1965 = !DIEnumerator(name: "CURLOPT_LASTENTRY", value: 266)
!1966 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 2258, size: 32, align: 32, elements: !1967)
!1967 = !{!1968, !1969, !1970, !1971, !1972, !1973, !1974, !1975, !1976, !1977, !1978, !1979, !1980, !1981, !1982, !1983, !1984, !1985, !1986, !1987, !1988, !1989, !1990, !1991, !1992, !1993, !1994, !1995, !1996, !1997, !1998, !1999, !2000, !2001, !2002, !2003, !2004, !2005, !2006, !2007, !2008, !2009, !2010, !2011, !2012, !2013, !2014, !2015, !2016, !2017, !2018}
!1968 = !DIEnumerator(name: "CURLINFO_NONE", value: 0)
!1969 = !DIEnumerator(name: "CURLINFO_EFFECTIVE_URL", value: 1048577)
!1970 = !DIEnumerator(name: "CURLINFO_RESPONSE_CODE", value: 2097154)
!1971 = !DIEnumerator(name: "CURLINFO_TOTAL_TIME", value: 3145731)
!1972 = !DIEnumerator(name: "CURLINFO_NAMELOOKUP_TIME", value: 3145732)
!1973 = !DIEnumerator(name: "CURLINFO_CONNECT_TIME", value: 3145733)
!1974 = !DIEnumerator(name: "CURLINFO_PRETRANSFER_TIME", value: 3145734)
!1975 = !DIEnumerator(name: "CURLINFO_SIZE_UPLOAD", value: 3145735)
!1976 = !DIEnumerator(name: "CURLINFO_SIZE_DOWNLOAD", value: 3145736)
!1977 = !DIEnumerator(name: "CURLINFO_SPEED_DOWNLOAD", value: 3145737)
!1978 = !DIEnumerator(name: "CURLINFO_SPEED_UPLOAD", value: 3145738)
!1979 = !DIEnumerator(name: "CURLINFO_HEADER_SIZE", value: 2097163)
!1980 = !DIEnumerator(name: "CURLINFO_REQUEST_SIZE", value: 2097164)
!1981 = !DIEnumerator(name: "CURLINFO_SSL_VERIFYRESULT", value: 2097165)
!1982 = !DIEnumerator(name: "CURLINFO_FILETIME", value: 2097166)
!1983 = !DIEnumerator(name: "CURLINFO_CONTENT_LENGTH_DOWNLOAD", value: 3145743)
!1984 = !DIEnumerator(name: "CURLINFO_CONTENT_LENGTH_UPLOAD", value: 3145744)
!1985 = !DIEnumerator(name: "CURLINFO_STARTTRANSFER_TIME", value: 3145745)
!1986 = !DIEnumerator(name: "CURLINFO_CONTENT_TYPE", value: 1048594)
!1987 = !DIEnumerator(name: "CURLINFO_REDIRECT_TIME", value: 3145747)
!1988 = !DIEnumerator(name: "CURLINFO_REDIRECT_COUNT", value: 2097172)
!1989 = !DIEnumerator(name: "CURLINFO_PRIVATE", value: 1048597)
!1990 = !DIEnumerator(name: "CURLINFO_HTTP_CONNECTCODE", value: 2097174)
!1991 = !DIEnumerator(name: "CURLINFO_HTTPAUTH_AVAIL", value: 2097175)
!1992 = !DIEnumerator(name: "CURLINFO_PROXYAUTH_AVAIL", value: 2097176)
!1993 = !DIEnumerator(name: "CURLINFO_OS_ERRNO", value: 2097177)
!1994 = !DIEnumerator(name: "CURLINFO_NUM_CONNECTS", value: 2097178)
!1995 = !DIEnumerator(name: "CURLINFO_SSL_ENGINES", value: 4194331)
!1996 = !DIEnumerator(name: "CURLINFO_COOKIELIST", value: 4194332)
!1997 = !DIEnumerator(name: "CURLINFO_LASTSOCKET", value: 2097181)
!1998 = !DIEnumerator(name: "CURLINFO_FTP_ENTRY_PATH", value: 1048606)
!1999 = !DIEnumerator(name: "CURLINFO_REDIRECT_URL", value: 1048607)
!2000 = !DIEnumerator(name: "CURLINFO_PRIMARY_IP", value: 1048608)
!2001 = !DIEnumerator(name: "CURLINFO_APPCONNECT_TIME", value: 3145761)
!2002 = !DIEnumerator(name: "CURLINFO_CERTINFO", value: 4194338)
!2003 = !DIEnumerator(name: "CURLINFO_CONDITION_UNMET", value: 2097187)
!2004 = !DIEnumerator(name: "CURLINFO_RTSP_SESSION_ID", value: 1048612)
!2005 = !DIEnumerator(name: "CURLINFO_RTSP_CLIENT_CSEQ", value: 2097189)
!2006 = !DIEnumerator(name: "CURLINFO_RTSP_SERVER_CSEQ", value: 2097190)
!2007 = !DIEnumerator(name: "CURLINFO_RTSP_CSEQ_RECV", value: 2097191)
!2008 = !DIEnumerator(name: "CURLINFO_PRIMARY_PORT", value: 2097192)
!2009 = !DIEnumerator(name: "CURLINFO_LOCAL_IP", value: 1048617)
!2010 = !DIEnumerator(name: "CURLINFO_LOCAL_PORT", value: 2097194)
!2011 = !DIEnumerator(name: "CURLINFO_TLS_SESSION", value: 4194347)
!2012 = !DIEnumerator(name: "CURLINFO_ACTIVESOCKET", value: 5242924)
!2013 = !DIEnumerator(name: "CURLINFO_TLS_SSL_PTR", value: 4194349)
!2014 = !DIEnumerator(name: "CURLINFO_HTTP_VERSION", value: 2097198)
!2015 = !DIEnumerator(name: "CURLINFO_PROXY_SSL_VERIFYRESULT", value: 2097199)
!2016 = !DIEnumerator(name: "CURLINFO_PROTOCOL", value: 2097200)
!2017 = !DIEnumerator(name: "CURLINFO_SCHEME", value: 1048625)
!2018 = !DIEnumerator(name: "CURLINFO_LASTONE", value: 49)
!2019 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !295, line: 61, size: 32, align: 32, elements: !2020)
!2020 = !{!2021, !2022, !2023, !2024, !2025, !2026, !2027, !2028, !2029, !2030}
!2021 = !DIEnumerator(name: "CURLM_CALL_MULTI_PERFORM", value: -1)
!2022 = !DIEnumerator(name: "CURLM_OK", value: 0)
!2023 = !DIEnumerator(name: "CURLM_BAD_HANDLE", value: 1)
!2024 = !DIEnumerator(name: "CURLM_BAD_EASY_HANDLE", value: 2)
!2025 = !DIEnumerator(name: "CURLM_OUT_OF_MEMORY", value: 3)
!2026 = !DIEnumerator(name: "CURLM_INTERNAL_ERROR", value: 4)
!2027 = !DIEnumerator(name: "CURLM_BAD_SOCKET", value: 5)
!2028 = !DIEnumerator(name: "CURLM_UNKNOWN_OPTION", value: 6)
!2029 = !DIEnumerator(name: "CURLM_ADDED_ALREADY", value: 7)
!2030 = !DIEnumerator(name: "CURLM_LAST", value: 8)
!2031 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !295, line: 333, size: 32, align: 32, elements: !2032)
!2032 = !{!2033, !2034, !2035, !2036, !2037, !2038, !2039, !2040, !2041, !2042, !2043, !2044, !2045, !2046, !2047, !2048}
!2033 = !DIEnumerator(name: "CURLMOPT_SOCKETFUNCTION", value: 20001)
!2034 = !DIEnumerator(name: "CURLMOPT_SOCKETDATA", value: 10002)
!2035 = !DIEnumerator(name: "CURLMOPT_PIPELINING", value: 3)
!2036 = !DIEnumerator(name: "CURLMOPT_TIMERFUNCTION", value: 20004)
!2037 = !DIEnumerator(name: "CURLMOPT_TIMERDATA", value: 10005)
!2038 = !DIEnumerator(name: "CURLMOPT_MAXCONNECTS", value: 6)
!2039 = !DIEnumerator(name: "CURLMOPT_MAX_HOST_CONNECTIONS", value: 7)
!2040 = !DIEnumerator(name: "CURLMOPT_MAX_PIPELINE_LENGTH", value: 8)
!2041 = !DIEnumerator(name: "CURLMOPT_CONTENT_LENGTH_PENALTY_SIZE", value: 30009)
!2042 = !DIEnumerator(name: "CURLMOPT_CHUNK_LENGTH_PENALTY_SIZE", value: 30010)
!2043 = !DIEnumerator(name: "CURLMOPT_PIPELINING_SITE_BL", value: 10011)
!2044 = !DIEnumerator(name: "CURLMOPT_PIPELINING_SERVER_BL", value: 10012)
!2045 = !DIEnumerator(name: "CURLMOPT_MAX_TOTAL_CONNECTIONS", value: 13)
!2046 = !DIEnumerator(name: "CURLMOPT_PUSHFUNCTION", value: 20014)
!2047 = !DIEnumerator(name: "CURLMOPT_PUSHDATA", value: 10015)
!2048 = !DIEnumerator(name: "CURLMOPT_LASTENTRY", value: 10016)
!2049 = !{!311, !347, !2050, !2054, !2055, !2059, !2063}
!2050 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_malloc_callback", file: !4, line: 399, baseType: !2051)
!2051 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2052, size: 64, align: 64)
!2052 = !DISubroutineType(types: !2053)
!2053 = !{!311, !347}
!2054 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_free_callback", file: !4, line: 400, baseType: !362)
!2055 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_realloc_callback", file: !4, line: 401, baseType: !2056)
!2056 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2057, size: 64, align: 64)
!2057 = !DISubroutineType(types: !2058)
!2058 = !{!311, !311, !347}
!2059 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_strdup_callback", file: !4, line: 402, baseType: !2060)
!2060 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2061, size: 64, align: 64)
!2061 = !DISubroutineType(types: !2062)
!2062 = !{!500, !527}
!2063 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_calloc_callback", file: !4, line: 403, baseType: !2064)
!2064 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !2065, size: 64, align: 64)
!2065 = !DISubroutineType(types: !2066)
!2066 = !{!311, !347, !347}
!2067 = !{!2068, !2072, !2075, !2078, !2081, !2085, !2088, !2091, !2095, !2098, !2099, !2102, !2106, !2109, !2112, !2115, !2116, !2119, !2122}
!2068 = distinct !DISubprogram(name: "curl_global_init", scope: !1, file: !1, line: 271, type: !2069, isLocal: false, isDefinition: true, scopeLine: 272, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2069 = !DISubroutineType(types: !2070)
!2070 = !{!289, !379}
!2071 = !{}
!2072 = distinct !DISubprogram(name: "curl_global_init_mem", scope: !1, file: !1, line: 280, type: !2073, isLocal: false, isDefinition: true, scopeLine: 283, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2073 = !DISubroutineType(types: !2074)
!2074 = !{!289, !379, !2050, !2054, !2055, !2059, !2063}
!2075 = distinct !DISubprogram(name: "curl_global_cleanup", scope: !1, file: !1, line: 312, type: !2076, isLocal: false, isDefinition: true, scopeLine: 313, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2076 = !DISubroutineType(types: !2077)
!2077 = !{null}
!2078 = distinct !DISubprogram(name: "curl_easy_init", scope: !1, file: !1, line: 343, type: !2079, isLocal: false, isDefinition: true, scopeLine: 344, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2079 = !DISubroutineType(types: !2080)
!2080 = !{!305}
!2081 = distinct !DISubprogram(name: "curl_easy_setopt", scope: !1, file: !1, line: 374, type: !2082, isLocal: false, isDefinition: true, scopeLine: 375, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2082 = !DISubroutineType(types: !2083)
!2083 = !{!289, !256, !2084, null}
!2084 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLoption", file: !4, line: 1786, baseType: !1716)
!2085 = distinct !DISubprogram(name: "curl_easy_perform", scope: !1, file: !1, line: 803, type: !2086, isLocal: false, isDefinition: true, scopeLine: 804, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2086 = !DISubroutineType(types: !2087)
!2087 = !{!289, !256}
!2088 = distinct !DISubprogram(name: "curl_easy_cleanup", scope: !1, file: !1, line: 824, type: !2089, isLocal: false, isDefinition: true, scopeLine: 825, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2089 = !DISubroutineType(types: !2090)
!2090 = !{null, !256}
!2091 = distinct !DISubprogram(name: "curl_easy_getinfo", scope: !1, file: !1, line: 841, type: !2092, isLocal: false, isDefinition: true, scopeLine: 842, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2092 = !DISubroutineType(types: !2093)
!2093 = !{!289, !256, !2094, null}
!2094 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLINFO", file: !4, line: 2312, baseType: !1966)
!2095 = distinct !DISubprogram(name: "curl_easy_duphandle", scope: !1, file: !1, line: 861, type: !2096, isLocal: false, isDefinition: true, scopeLine: 862, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2096 = !DISubroutineType(types: !2097)
!2097 = !{!305, !256}
!2098 = distinct !DISubprogram(name: "curl_easy_reset", scope: !1, file: !1, line: 962, type: !2089, isLocal: false, isDefinition: true, scopeLine: 963, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2099 = distinct !DISubprogram(name: "curl_easy_pause", scope: !1, file: !1, line: 999, type: !2100, isLocal: false, isDefinition: true, scopeLine: 1000, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2100 = !DISubroutineType(types: !2101)
!2101 = !{!289, !256, !316}
!2102 = distinct !DISubprogram(name: "curl_easy_recv", scope: !1, file: !1, line: 1081, type: !2103, isLocal: false, isDefinition: true, scopeLine: 1083, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2103 = !DISubroutineType(types: !2104)
!2104 = !{!289, !256, !311, !347, !2105}
!2105 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !347, size: 64, align: 64)
!2106 = distinct !DISubprogram(name: "curl_easy_send", scope: !1, file: !1, line: 1108, type: !2107, isLocal: false, isDefinition: true, scopeLine: 1110, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2107 = !DISubroutineType(types: !2108)
!2108 = !{!289, !256, !1046, !347, !2105}
!2109 = distinct !DISubprogram(name: "global_init", scope: !1, file: !1, line: 200, type: !2110, isLocal: true, isDefinition: true, scopeLine: 201, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2110 = !DISubroutineType(types: !2111)
!2111 = !{!289, !379, !423}
!2112 = distinct !DISubprogram(name: "win32_init", scope: !1, file: !1, line: 96, type: !2113, isLocal: true, isDefinition: true, scopeLine: 97, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2113 = !DISubroutineType(types: !2114)
!2114 = !{!289}
!2115 = distinct !DISubprogram(name: "win32_cleanup", scope: !1, file: !1, line: 84, type: !2076, isLocal: true, isDefinition: true, scopeLine: 85, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2116 = distinct !DISubprogram(name: "easy_perform", scope: !1, file: !1, line: 742, type: !2117, isLocal: true, isDefinition: true, scopeLine: 743, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2117 = !DISubroutineType(types: !2118)
!2118 = !{!289, !256, !423}
!2119 = distinct !DISubprogram(name: "easy_transfer", scope: !1, file: !1, line: 662, type: !2120, isLocal: true, isDefinition: true, scopeLine: 663, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2120 = !DISubroutineType(types: !2121)
!2121 = !{!289, !375}
!2122 = distinct !DISubprogram(name: "easy_connection", scope: !1, file: !1, line: 1053, type: !2123, isLocal: true, isDefinition: true, scopeLine: 1056, flags: DIFlagPrototyped, isOptimized: false, variables: !2071)
!2123 = !DISubroutineType(types: !2124)
!2124 = !{!289, !256, !1480, !2125}
!2125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !262, size: 64, align: 64)
!2126 = !{!2127, !2128, !2129, !2130, !2131, !2132, !2133}
!2127 = !DIGlobalVariable(name: "Curl_cmalloc", scope: !0, file: !1, line: 172, type: !2050, isLocal: false, isDefinition: true, variable: i8* (i64)** @Curl_cmalloc)
!2128 = !DIGlobalVariable(name: "Curl_cfree", scope: !0, file: !1, line: 173, type: !2054, isLocal: false, isDefinition: true, variable: void (i8*)** @Curl_cfree)
!2129 = !DIGlobalVariable(name: "Curl_crealloc", scope: !0, file: !1, line: 174, type: !2055, isLocal: false, isDefinition: true, variable: i8* (i8*, i64)** @Curl_crealloc)
!2130 = !DIGlobalVariable(name: "Curl_cstrdup", scope: !0, file: !1, line: 175, type: !2059, isLocal: false, isDefinition: true, variable: i8* (i8*)** @Curl_cstrdup)
!2131 = !DIGlobalVariable(name: "Curl_ccalloc", scope: !0, file: !1, line: 176, type: !2063, isLocal: false, isDefinition: true, variable: i8* (i64, i64)** @Curl_ccalloc)
!2132 = !DIGlobalVariable(name: "initialized", scope: !0, file: !1, line: 147, type: !457, isLocal: true, isDefinition: true, variable: i32* @initialized)
!2133 = !DIGlobalVariable(name: "init_flags", scope: !0, file: !1, line: 148, type: !379, isLocal: true, isDefinition: true, variable: i64* @init_flags)
!2134 = !{i32 2, !"Dwarf Version", i32 4}
!2135 = !{i32 2, !"Debug Info Version", i32 3}
!2136 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!2137 = !DILocalVariable(name: "flags", arg: 1, scope: !2068, file: !1, line: 271, type: !379)
!2138 = !DIExpression()
!2139 = !DILocation(line: 271, column: 32, scope: !2068)
!2140 = !DILocation(line: 273, column: 22, scope: !2068)
!2141 = !DILocation(line: 273, column: 10, scope: !2068)
!2142 = !DILocation(line: 273, column: 3, scope: !2068)
!2143 = !DILocalVariable(name: "flags", arg: 1, scope: !2109, file: !1, line: 200, type: !379)
!2144 = !DILocation(line: 200, column: 34, scope: !2109)
!2145 = !DILocalVariable(name: "memoryfuncs", arg: 2, scope: !2109, file: !1, line: 200, type: !423)
!2146 = !DILocation(line: 200, column: 46, scope: !2109)
!2147 = !DILocation(line: 202, column: 17, scope: !2148)
!2148 = distinct !DILexicalBlock(scope: !2109, file: !1, line: 202, column: 6)
!2149 = !DILocation(line: 202, column: 6, scope: !2109)
!2150 = !DILocation(line: 203, column: 5, scope: !2148)
!2151 = !DILocation(line: 205, column: 6, scope: !2152)
!2152 = distinct !DILexicalBlock(scope: !2109, file: !1, line: 205, column: 6)
!2153 = !DILocation(line: 205, column: 6, scope: !2109)
!2154 = !DILocation(line: 207, column: 18, scope: !2155)
!2155 = distinct !DILexicalBlock(scope: !2152, file: !1, line: 205, column: 19)
!2156 = !DILocation(line: 208, column: 16, scope: !2155)
!2157 = !DILocation(line: 209, column: 19, scope: !2155)
!2158 = !DILocation(line: 210, column: 18, scope: !2155)
!2159 = !DILocation(line: 211, column: 18, scope: !2155)
!2160 = !DILocation(line: 215, column: 3, scope: !2155)
!2161 = !DILocation(line: 217, column: 6, scope: !2162)
!2162 = distinct !DILexicalBlock(scope: !2109, file: !1, line: 217, column: 6)
!2163 = !DILocation(line: 217, column: 12, scope: !2162)
!2164 = !DILocation(line: 217, column: 6, scope: !2109)
!2165 = !DILocation(line: 218, column: 9, scope: !2166)
!2166 = distinct !DILexicalBlock(scope: !2162, file: !1, line: 218, column: 8)
!2167 = !DILocation(line: 223, column: 6, scope: !2168)
!2168 = distinct !DILexicalBlock(scope: !2109, file: !1, line: 223, column: 6)
!2169 = !DILocation(line: 223, column: 12, scope: !2168)
!2170 = !DILocation(line: 223, column: 6, scope: !2109)
!2171 = !DILocation(line: 224, column: 8, scope: !2172)
!2172 = distinct !DILexicalBlock(scope: !2168, file: !1, line: 224, column: 8)
!2173 = !DILocation(line: 224, column: 8, scope: !2168)
!2174 = !DILocation(line: 225, column: 7, scope: !2175)
!2175 = distinct !DILexicalBlock(scope: !2172, file: !1, line: 224, column: 22)
!2176 = !DILocation(line: 225, column: 7, scope: !2177)
!2177 = !DILexicalBlockFile(scope: !2178, file: !1, discriminator: 1)
!2178 = distinct !DILexicalBlock(scope: !2175, file: !1, line: 225, column: 7)
!2179 = !DILocation(line: 226, column: 7, scope: !2175)
!2180 = !DILocation(line: 224, column: 19, scope: !2181)
!2181 = !DILexicalBlockFile(scope: !2172, file: !1, discriminator: 1)
!2182 = !DILocation(line: 256, column: 6, scope: !2183)
!2183 = distinct !DILexicalBlock(scope: !2109, file: !1, line: 256, column: 6)
!2184 = !DILocation(line: 256, column: 12, scope: !2183)
!2185 = !DILocation(line: 256, column: 6, scope: !2109)
!2186 = !DILocation(line: 257, column: 20, scope: !2183)
!2187 = !DILocation(line: 257, column: 5, scope: !2183)
!2188 = !DILocation(line: 259, column: 16, scope: !2109)
!2189 = !DILocation(line: 259, column: 14, scope: !2109)
!2190 = !DILocation(line: 261, column: 3, scope: !2109)
!2191 = !DILocation(line: 263, column: 3, scope: !2109)
!2192 = !DILocation(line: 264, column: 1, scope: !2109)
!2193 = !DILocalVariable(name: "flags", arg: 1, scope: !2072, file: !1, line: 280, type: !379)
!2194 = !DILocation(line: 280, column: 36, scope: !2072)
!2195 = !DILocalVariable(name: "m", arg: 2, scope: !2072, file: !1, line: 280, type: !2050)
!2196 = !DILocation(line: 280, column: 64, scope: !2072)
!2197 = !DILocalVariable(name: "f", arg: 3, scope: !2072, file: !1, line: 281, type: !2054)
!2198 = !DILocation(line: 281, column: 50, scope: !2072)
!2199 = !DILocalVariable(name: "r", arg: 4, scope: !2072, file: !1, line: 281, type: !2055)
!2200 = !DILocation(line: 281, column: 75, scope: !2072)
!2201 = !DILocalVariable(name: "s", arg: 5, scope: !2072, file: !1, line: 282, type: !2059)
!2202 = !DILocation(line: 282, column: 52, scope: !2072)
!2203 = !DILocalVariable(name: "c", arg: 6, scope: !2072, file: !1, line: 282, type: !2063)
!2204 = !DILocation(line: 282, column: 76, scope: !2072)
!2205 = !DILocation(line: 285, column: 7, scope: !2206)
!2206 = distinct !DILexicalBlock(scope: !2072, file: !1, line: 285, column: 6)
!2207 = !DILocation(line: 285, column: 9, scope: !2206)
!2208 = !DILocation(line: 285, column: 13, scope: !2209)
!2209 = !DILexicalBlockFile(scope: !2206, file: !1, discriminator: 1)
!2210 = !DILocation(line: 285, column: 15, scope: !2209)
!2211 = !DILocation(line: 285, column: 19, scope: !2212)
!2212 = !DILexicalBlockFile(scope: !2206, file: !1, discriminator: 2)
!2213 = !DILocation(line: 285, column: 21, scope: !2212)
!2214 = !DILocation(line: 285, column: 25, scope: !2215)
!2215 = !DILexicalBlockFile(scope: !2206, file: !1, discriminator: 3)
!2216 = !DILocation(line: 285, column: 27, scope: !2215)
!2217 = !DILocation(line: 285, column: 31, scope: !2218)
!2218 = !DILexicalBlockFile(scope: !2206, file: !1, discriminator: 4)
!2219 = !DILocation(line: 285, column: 6, scope: !2218)
!2220 = !DILocation(line: 286, column: 5, scope: !2206)
!2221 = !DILocation(line: 288, column: 6, scope: !2222)
!2222 = distinct !DILexicalBlock(scope: !2072, file: !1, line: 288, column: 6)
!2223 = !DILocation(line: 288, column: 6, scope: !2072)
!2224 = !DILocation(line: 292, column: 16, scope: !2225)
!2225 = distinct !DILexicalBlock(scope: !2222, file: !1, line: 288, column: 19)
!2226 = !DILocation(line: 293, column: 5, scope: !2225)
!2227 = !DILocation(line: 298, column: 18, scope: !2072)
!2228 = !DILocation(line: 298, column: 16, scope: !2072)
!2229 = !DILocation(line: 299, column: 16, scope: !2072)
!2230 = !DILocation(line: 299, column: 14, scope: !2072)
!2231 = !DILocation(line: 300, column: 18, scope: !2072)
!2232 = !DILocation(line: 300, column: 16, scope: !2072)
!2233 = !DILocation(line: 301, column: 19, scope: !2072)
!2234 = !DILocation(line: 301, column: 17, scope: !2072)
!2235 = !DILocation(line: 302, column: 18, scope: !2072)
!2236 = !DILocation(line: 302, column: 16, scope: !2072)
!2237 = !DILocation(line: 305, column: 22, scope: !2072)
!2238 = !DILocation(line: 305, column: 10, scope: !2072)
!2239 = !DILocation(line: 305, column: 3, scope: !2072)
!2240 = !DILocation(line: 306, column: 1, scope: !2072)
!2241 = !DILocation(line: 314, column: 7, scope: !2242)
!2242 = distinct !DILexicalBlock(scope: !2075, file: !1, line: 314, column: 6)
!2243 = !DILocation(line: 314, column: 6, scope: !2075)
!2244 = !DILocation(line: 315, column: 5, scope: !2242)
!2245 = !DILocation(line: 317, column: 6, scope: !2246)
!2246 = distinct !DILexicalBlock(scope: !2075, file: !1, line: 317, column: 6)
!2247 = !DILocation(line: 317, column: 6, scope: !2075)
!2248 = !DILocation(line: 318, column: 5, scope: !2246)
!2249 = !DILocation(line: 320, column: 3, scope: !2075)
!2250 = !DILocation(line: 322, column: 6, scope: !2251)
!2251 = distinct !DILexicalBlock(scope: !2075, file: !1, line: 322, column: 6)
!2252 = !DILocation(line: 322, column: 17, scope: !2251)
!2253 = !DILocation(line: 322, column: 6, scope: !2075)
!2254 = !DILocation(line: 323, column: 5, scope: !2251)
!2255 = !DILocation(line: 323, column: 5, scope: !2256)
!2256 = !DILexicalBlockFile(scope: !2257, file: !1, discriminator: 1)
!2257 = distinct !DILexicalBlock(scope: !2251, file: !1, line: 323, column: 5)
!2258 = !DILocation(line: 323, column: 5, scope: !2259)
!2259 = !DILexicalBlockFile(scope: !2257, file: !1, discriminator: 2)
!2260 = !DILocation(line: 325, column: 3, scope: !2075)
!2261 = !DILocation(line: 325, column: 3, scope: !2262)
!2262 = !DILexicalBlockFile(scope: !2263, file: !1, discriminator: 1)
!2263 = distinct !DILexicalBlock(scope: !2075, file: !1, line: 325, column: 3)
!2264 = !DILocation(line: 327, column: 6, scope: !2265)
!2265 = distinct !DILexicalBlock(scope: !2075, file: !1, line: 327, column: 6)
!2266 = !DILocation(line: 327, column: 17, scope: !2265)
!2267 = !DILocation(line: 327, column: 6, scope: !2075)
!2268 = !DILocation(line: 328, column: 5, scope: !2265)
!2269 = !DILocation(line: 330, column: 3, scope: !2075)
!2270 = !DILocation(line: 330, column: 3, scope: !2271)
!2271 = !DILexicalBlockFile(scope: !2272, file: !1, discriminator: 1)
!2272 = distinct !DILexicalBlock(scope: !2075, file: !1, line: 330, column: 3)
!2273 = !DILocation(line: 336, column: 15, scope: !2075)
!2274 = !DILocation(line: 337, column: 1, scope: !2075)
!2275 = !DILocation(line: 337, column: 1, scope: !2276)
!2276 = !DILexicalBlockFile(scope: !2075, file: !1, discriminator: 1)
!2277 = !DILocation(line: 92, column: 1, scope: !2115)
!2278 = !DILocalVariable(name: "result", scope: !2078, file: !1, line: 345, type: !289)
!2279 = !DILocation(line: 345, column: 12, scope: !2078)
!2280 = !DILocalVariable(name: "data", scope: !2078, file: !1, line: 346, type: !256)
!2281 = !DILocation(line: 346, column: 21, scope: !2078)
!2282 = !DILocation(line: 349, column: 7, scope: !2283)
!2283 = distinct !DILexicalBlock(scope: !2078, file: !1, line: 349, column: 6)
!2284 = !DILocation(line: 349, column: 6, scope: !2078)
!2285 = !DILocation(line: 350, column: 14, scope: !2286)
!2286 = distinct !DILexicalBlock(scope: !2283, file: !1, line: 349, column: 20)
!2287 = !DILocation(line: 350, column: 12, scope: !2286)
!2288 = !DILocation(line: 351, column: 8, scope: !2289)
!2289 = distinct !DILexicalBlock(scope: !2286, file: !1, line: 351, column: 8)
!2290 = !DILocation(line: 351, column: 8, scope: !2286)
!2291 = !DILocation(line: 353, column: 7, scope: !2292)
!2292 = distinct !DILexicalBlock(scope: !2289, file: !1, line: 351, column: 16)
!2293 = !DILocation(line: 353, column: 7, scope: !2294)
!2294 = !DILexicalBlockFile(scope: !2295, file: !1, discriminator: 1)
!2295 = distinct !DILexicalBlock(scope: !2292, file: !1, line: 353, column: 7)
!2296 = !DILocation(line: 354, column: 7, scope: !2292)
!2297 = !DILocation(line: 356, column: 3, scope: !2286)
!2298 = !DILocation(line: 359, column: 12, scope: !2078)
!2299 = !DILocation(line: 359, column: 10, scope: !2078)
!2300 = !DILocation(line: 360, column: 6, scope: !2301)
!2301 = distinct !DILexicalBlock(scope: !2078, file: !1, line: 360, column: 6)
!2302 = !DILocation(line: 360, column: 6, scope: !2078)
!2303 = !DILocation(line: 361, column: 5, scope: !2304)
!2304 = distinct !DILexicalBlock(scope: !2301, file: !1, line: 360, column: 14)
!2305 = !DILocation(line: 361, column: 5, scope: !2306)
!2306 = !DILexicalBlockFile(scope: !2307, file: !1, discriminator: 1)
!2307 = distinct !DILexicalBlock(scope: !2304, file: !1, line: 361, column: 5)
!2308 = !DILocation(line: 362, column: 5, scope: !2304)
!2309 = !DILocation(line: 365, column: 10, scope: !2078)
!2310 = !DILocation(line: 365, column: 3, scope: !2078)
!2311 = !DILocation(line: 366, column: 1, scope: !2078)
!2312 = !DILocalVariable(name: "data", arg: 1, scope: !2081, file: !1, line: 374, type: !256)
!2313 = !DILocation(line: 374, column: 45, scope: !2081)
!2314 = !DILocalVariable(name: "tag", arg: 2, scope: !2081, file: !1, line: 374, type: !2084)
!2315 = !DILocation(line: 374, column: 62, scope: !2081)
!2316 = !DILocalVariable(name: "arg", scope: !2081, file: !1, line: 376, type: !2317)
!2317 = !DIDerivedType(tag: DW_TAG_typedef, name: "va_list", file: !627, line: 79, baseType: !2318)
!2318 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gnuc_va_list", file: !2319, line: 50, baseType: !2320)
!2319 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stdarg.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2320 = !DIDerivedType(tag: DW_TAG_typedef, name: "__builtin_va_list", file: !1, line: 376, baseType: !2321)
!2321 = !DICompositeType(tag: DW_TAG_array_type, baseType: !2322, size: 192, align: 64, elements: !662)
!2322 = !DICompositeType(tag: DW_TAG_structure_type, name: "__va_list_tag", file: !1, line: 376, size: 192, align: 64, elements: !2323)
!2323 = !{!2324, !2325, !2326, !2327}
!2324 = !DIDerivedType(tag: DW_TAG_member, name: "gp_offset", scope: !2322, file: !1, line: 376, baseType: !457, size: 32, align: 32)
!2325 = !DIDerivedType(tag: DW_TAG_member, name: "fp_offset", scope: !2322, file: !1, line: 376, baseType: !457, size: 32, align: 32, offset: 32)
!2326 = !DIDerivedType(tag: DW_TAG_member, name: "overflow_arg_area", scope: !2322, file: !1, line: 376, baseType: !311, size: 64, align: 64, offset: 64)
!2327 = !DIDerivedType(tag: DW_TAG_member, name: "reg_save_area", scope: !2322, file: !1, line: 376, baseType: !311, size: 64, align: 64, offset: 128)
!2328 = !DILocation(line: 376, column: 11, scope: !2081)
!2329 = !DILocalVariable(name: "result", scope: !2081, file: !1, line: 377, type: !289)
!2330 = !DILocation(line: 377, column: 12, scope: !2081)
!2331 = !DILocation(line: 379, column: 7, scope: !2332)
!2332 = distinct !DILexicalBlock(scope: !2081, file: !1, line: 379, column: 6)
!2333 = !DILocation(line: 379, column: 6, scope: !2081)
!2334 = !DILocation(line: 380, column: 5, scope: !2332)
!2335 = !DILocation(line: 382, column: 3, scope: !2081)
!2336 = !DILocation(line: 384, column: 24, scope: !2081)
!2337 = !DILocation(line: 384, column: 30, scope: !2081)
!2338 = !DILocation(line: 384, column: 35, scope: !2081)
!2339 = !DILocation(line: 384, column: 12, scope: !2081)
!2340 = !DILocation(line: 384, column: 10, scope: !2081)
!2341 = !DILocation(line: 386, column: 3, scope: !2081)
!2342 = !DILocation(line: 387, column: 10, scope: !2081)
!2343 = !DILocation(line: 387, column: 3, scope: !2081)
!2344 = !DILocation(line: 388, column: 1, scope: !2081)
!2345 = !DILocalVariable(name: "data", arg: 1, scope: !2085, file: !1, line: 803, type: !256)
!2346 = !DILocation(line: 803, column: 46, scope: !2085)
!2347 = !DILocation(line: 805, column: 23, scope: !2085)
!2348 = !DILocation(line: 805, column: 10, scope: !2085)
!2349 = !DILocation(line: 805, column: 3, scope: !2085)
!2350 = !DILocalVariable(name: "data", arg: 1, scope: !2116, file: !1, line: 742, type: !256)
!2351 = !DILocation(line: 742, column: 48, scope: !2116)
!2352 = !DILocalVariable(name: "events", arg: 2, scope: !2116, file: !1, line: 742, type: !423)
!2353 = !DILocation(line: 742, column: 59, scope: !2116)
!2354 = !DILocalVariable(name: "multi", scope: !2116, file: !1, line: 744, type: !375)
!2355 = !DILocation(line: 744, column: 22, scope: !2116)
!2356 = !DILocalVariable(name: "mcode", scope: !2116, file: !1, line: 745, type: !2357)
!2357 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMcode", file: !295, line: 74, baseType: !2019)
!2358 = !DILocation(line: 745, column: 13, scope: !2116)
!2359 = !DILocalVariable(name: "result", scope: !2116, file: !1, line: 746, type: !289)
!2360 = !DILocation(line: 746, column: 12, scope: !2116)
!2361 = !DILocation(line: 749, column: 7, scope: !2362)
!2362 = distinct !DILexicalBlock(scope: !2116, file: !1, line: 749, column: 6)
!2363 = !DILocation(line: 749, column: 6, scope: !2116)
!2364 = !DILocation(line: 750, column: 5, scope: !2362)
!2365 = !DILocation(line: 752, column: 6, scope: !2366)
!2366 = distinct !DILexicalBlock(scope: !2116, file: !1, line: 752, column: 6)
!2367 = !DILocation(line: 752, column: 12, scope: !2366)
!2368 = !DILocation(line: 752, column: 6, scope: !2116)
!2369 = !DILocation(line: 753, column: 11, scope: !2370)
!2370 = distinct !DILexicalBlock(scope: !2366, file: !1, line: 752, column: 19)
!2371 = !DILocation(line: 753, column: 5, scope: !2370)
!2372 = !DILocation(line: 754, column: 5, scope: !2370)
!2373 = !DILocation(line: 757, column: 6, scope: !2374)
!2374 = distinct !DILexicalBlock(scope: !2116, file: !1, line: 757, column: 6)
!2375 = !DILocation(line: 757, column: 12, scope: !2374)
!2376 = !DILocation(line: 757, column: 6, scope: !2116)
!2377 = !DILocation(line: 758, column: 13, scope: !2374)
!2378 = !DILocation(line: 758, column: 19, scope: !2374)
!2379 = !DILocation(line: 758, column: 11, scope: !2374)
!2380 = !DILocation(line: 758, column: 5, scope: !2374)
!2381 = !DILocation(line: 762, column: 13, scope: !2382)
!2382 = distinct !DILexicalBlock(scope: !2374, file: !1, line: 759, column: 8)
!2383 = !DILocation(line: 762, column: 11, scope: !2382)
!2384 = !DILocation(line: 763, column: 9, scope: !2385)
!2385 = distinct !DILexicalBlock(scope: !2382, file: !1, line: 763, column: 8)
!2386 = !DILocation(line: 763, column: 8, scope: !2382)
!2387 = !DILocation(line: 764, column: 7, scope: !2385)
!2388 = !DILocation(line: 765, column: 24, scope: !2382)
!2389 = !DILocation(line: 765, column: 5, scope: !2382)
!2390 = !DILocation(line: 765, column: 11, scope: !2382)
!2391 = !DILocation(line: 765, column: 22, scope: !2382)
!2392 = !DILocation(line: 769, column: 21, scope: !2116)
!2393 = !DILocation(line: 769, column: 50, scope: !2116)
!2394 = !DILocation(line: 769, column: 56, scope: !2116)
!2395 = !DILocation(line: 769, column: 60, scope: !2116)
!2396 = !DILocation(line: 769, column: 3, scope: !2116)
!2397 = !DILocation(line: 771, column: 33, scope: !2116)
!2398 = !DILocation(line: 771, column: 40, scope: !2116)
!2399 = !DILocation(line: 771, column: 11, scope: !2116)
!2400 = !DILocation(line: 771, column: 9, scope: !2116)
!2401 = !DILocation(line: 772, column: 6, scope: !2402)
!2402 = distinct !DILexicalBlock(scope: !2116, file: !1, line: 772, column: 6)
!2403 = !DILocation(line: 772, column: 6, scope: !2116)
!2404 = !DILocation(line: 773, column: 24, scope: !2405)
!2405 = distinct !DILexicalBlock(scope: !2402, file: !1, line: 772, column: 13)
!2406 = !DILocation(line: 773, column: 5, scope: !2405)
!2407 = !DILocation(line: 774, column: 8, scope: !2408)
!2408 = distinct !DILexicalBlock(scope: !2405, file: !1, line: 774, column: 8)
!2409 = !DILocation(line: 774, column: 14, scope: !2408)
!2410 = !DILocation(line: 774, column: 8, scope: !2405)
!2411 = !DILocation(line: 775, column: 7, scope: !2408)
!2412 = !DILocation(line: 776, column: 5, scope: !2405)
!2413 = !DILocation(line: 779, column: 3, scope: !2116)
!2414 = !DILocation(line: 779, column: 3, scope: !2415)
!2415 = !DILexicalBlockFile(scope: !2416, file: !1, discriminator: 1)
!2416 = distinct !DILexicalBlock(scope: !2116, file: !1, line: 779, column: 3)
!2417 = !DILocation(line: 783, column: 17, scope: !2116)
!2418 = !DILocation(line: 783, column: 3, scope: !2116)
!2419 = !DILocation(line: 783, column: 9, scope: !2116)
!2420 = !DILocation(line: 783, column: 15, scope: !2116)
!2421 = !DILocation(line: 786, column: 12, scope: !2116)
!2422 = !DILocation(line: 786, column: 12, scope: !2423)
!2423 = !DILexicalBlockFile(scope: !2116, file: !1, discriminator: 1)
!2424 = !DILocation(line: 786, column: 56, scope: !2425)
!2425 = !DILexicalBlockFile(scope: !2116, file: !1, discriminator: 2)
!2426 = !DILocation(line: 786, column: 42, scope: !2425)
!2427 = !DILocation(line: 786, column: 12, scope: !2425)
!2428 = !DILocation(line: 786, column: 12, scope: !2429)
!2429 = !DILexicalBlockFile(scope: !2116, file: !1, discriminator: 3)
!2430 = !DILocation(line: 786, column: 10, scope: !2429)
!2431 = !DILocation(line: 790, column: 34, scope: !2116)
!2432 = !DILocation(line: 790, column: 41, scope: !2116)
!2433 = !DILocation(line: 790, column: 9, scope: !2116)
!2434 = !DILocation(line: 792, column: 3, scope: !2116)
!2435 = !DILocation(line: 792, column: 3, scope: !2436)
!2436 = !DILexicalBlockFile(scope: !2437, file: !1, discriminator: 1)
!2437 = distinct !DILexicalBlock(scope: !2116, file: !1, line: 792, column: 3)
!2438 = !DILocation(line: 795, column: 10, scope: !2116)
!2439 = !DILocation(line: 795, column: 3, scope: !2116)
!2440 = !DILocation(line: 796, column: 1, scope: !2116)
!2441 = !DILocalVariable(name: "data", arg: 1, scope: !2088, file: !1, line: 824, type: !256)
!2442 = !DILocation(line: 824, column: 42, scope: !2088)
!2443 = !DILocation(line: 828, column: 7, scope: !2444)
!2444 = distinct !DILexicalBlock(scope: !2088, file: !1, line: 828, column: 6)
!2445 = !DILocation(line: 828, column: 6, scope: !2088)
!2446 = !DILocation(line: 829, column: 5, scope: !2444)
!2447 = !DILocation(line: 831, column: 3, scope: !2088)
!2448 = !DILocation(line: 831, column: 3, scope: !2449)
!2449 = !DILexicalBlockFile(scope: !2450, file: !1, discriminator: 1)
!2450 = distinct !DILexicalBlock(scope: !2088, file: !1, line: 831, column: 3)
!2451 = !DILocation(line: 832, column: 14, scope: !2088)
!2452 = !DILocation(line: 832, column: 3, scope: !2088)
!2453 = !DILocation(line: 833, column: 3, scope: !2088)
!2454 = !DILocation(line: 833, column: 3, scope: !2455)
!2455 = !DILexicalBlockFile(scope: !2456, file: !1, discriminator: 1)
!2456 = distinct !DILexicalBlock(scope: !2088, file: !1, line: 833, column: 3)
!2457 = !DILocation(line: 834, column: 1, scope: !2088)
!2458 = !DILocalVariable(name: "data", arg: 1, scope: !2091, file: !1, line: 841, type: !256)
!2459 = !DILocation(line: 841, column: 46, scope: !2091)
!2460 = !DILocalVariable(name: "info", arg: 2, scope: !2091, file: !1, line: 841, type: !2094)
!2461 = !DILocation(line: 841, column: 61, scope: !2091)
!2462 = !DILocalVariable(name: "arg", scope: !2091, file: !1, line: 843, type: !2317)
!2463 = !DILocation(line: 843, column: 11, scope: !2091)
!2464 = !DILocalVariable(name: "paramp", scope: !2091, file: !1, line: 844, type: !311)
!2465 = !DILocation(line: 844, column: 9, scope: !2091)
!2466 = !DILocalVariable(name: "result", scope: !2091, file: !1, line: 845, type: !289)
!2467 = !DILocation(line: 845, column: 12, scope: !2091)
!2468 = !DILocation(line: 847, column: 3, scope: !2091)
!2469 = !DILocation(line: 848, column: 12, scope: !2091)
!2470 = !DILocation(line: 848, column: 12, scope: !2471)
!2471 = !DILexicalBlockFile(scope: !2091, file: !1, discriminator: 1)
!2472 = !DILocation(line: 848, column: 12, scope: !2473)
!2473 = !DILexicalBlockFile(scope: !2091, file: !1, discriminator: 2)
!2474 = !DILocation(line: 848, column: 12, scope: !2475)
!2475 = !DILexicalBlockFile(scope: !2091, file: !1, discriminator: 3)
!2476 = !DILocation(line: 848, column: 10, scope: !2475)
!2477 = !DILocation(line: 850, column: 25, scope: !2091)
!2478 = !DILocation(line: 850, column: 31, scope: !2091)
!2479 = !DILocation(line: 850, column: 37, scope: !2091)
!2480 = !DILocation(line: 850, column: 12, scope: !2091)
!2481 = !DILocation(line: 850, column: 10, scope: !2091)
!2482 = !DILocation(line: 852, column: 3, scope: !2091)
!2483 = !DILocation(line: 853, column: 10, scope: !2091)
!2484 = !DILocation(line: 853, column: 3, scope: !2091)
!2485 = !DILocalVariable(name: "data", arg: 1, scope: !2095, file: !1, line: 861, type: !256)
!2486 = !DILocation(line: 861, column: 57, scope: !2095)
!2487 = !DILocalVariable(name: "outcurl", scope: !2095, file: !1, line: 863, type: !256)
!2488 = !DILocation(line: 863, column: 21, scope: !2095)
!2489 = !DILocation(line: 863, column: 31, scope: !2095)
!2490 = !DILocation(line: 864, column: 14, scope: !2491)
!2491 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 864, column: 6)
!2492 = !DILocation(line: 864, column: 11, scope: !2491)
!2493 = !DILocation(line: 864, column: 6, scope: !2095)
!2494 = !DILocation(line: 865, column: 5, scope: !2491)
!2495 = !DILocation(line: 872, column: 30, scope: !2095)
!2496 = !DILocation(line: 872, column: 36, scope: !2095)
!2497 = !DILocation(line: 872, column: 40, scope: !2095)
!2498 = !DILocation(line: 872, column: 3, scope: !2095)
!2499 = !DILocation(line: 872, column: 12, scope: !2095)
!2500 = !DILocation(line: 872, column: 16, scope: !2095)
!2501 = !DILocation(line: 872, column: 28, scope: !2095)
!2502 = !DILocation(line: 873, column: 27, scope: !2095)
!2503 = !DILocation(line: 873, column: 27, scope: !2504)
!2504 = !DILexicalBlockFile(scope: !2095, file: !1, discriminator: 1)
!2505 = !DILocation(line: 873, column: 27, scope: !2506)
!2506 = !DILexicalBlockFile(scope: !2095, file: !1, discriminator: 2)
!2507 = !DILocation(line: 873, column: 27, scope: !2508)
!2508 = !DILexicalBlockFile(scope: !2095, file: !1, discriminator: 3)
!2509 = !DILocation(line: 873, column: 3, scope: !2508)
!2510 = !DILocation(line: 873, column: 12, scope: !2508)
!2511 = !DILocation(line: 873, column: 18, scope: !2508)
!2512 = !DILocation(line: 873, column: 25, scope: !2508)
!2513 = !DILocation(line: 874, column: 7, scope: !2514)
!2514 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 874, column: 6)
!2515 = !DILocation(line: 874, column: 16, scope: !2514)
!2516 = !DILocation(line: 874, column: 22, scope: !2514)
!2517 = !DILocation(line: 874, column: 6, scope: !2095)
!2518 = !DILocation(line: 875, column: 5, scope: !2514)
!2519 = !DILocation(line: 877, column: 31, scope: !2095)
!2520 = !DILocation(line: 877, column: 3, scope: !2095)
!2521 = !DILocation(line: 877, column: 12, scope: !2095)
!2522 = !DILocation(line: 877, column: 18, scope: !2095)
!2523 = !DILocation(line: 877, column: 29, scope: !2095)
!2524 = !DILocation(line: 878, column: 7, scope: !2525)
!2525 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 878, column: 6)
!2526 = !DILocation(line: 878, column: 16, scope: !2525)
!2527 = !DILocation(line: 878, column: 22, scope: !2525)
!2528 = !DILocation(line: 878, column: 6, scope: !2095)
!2529 = !DILocation(line: 879, column: 5, scope: !2525)
!2530 = !DILocation(line: 880, column: 3, scope: !2095)
!2531 = !DILocation(line: 880, column: 12, scope: !2095)
!2532 = !DILocation(line: 880, column: 18, scope: !2095)
!2533 = !DILocation(line: 880, column: 29, scope: !2095)
!2534 = !DILocation(line: 883, column: 18, scope: !2535)
!2535 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 883, column: 6)
!2536 = !DILocation(line: 883, column: 27, scope: !2535)
!2537 = !DILocation(line: 883, column: 6, scope: !2535)
!2538 = !DILocation(line: 883, column: 6, scope: !2095)
!2539 = !DILocation(line: 884, column: 5, scope: !2535)
!2540 = !DILocation(line: 887, column: 3, scope: !2095)
!2541 = !DILocation(line: 887, column: 12, scope: !2095)
!2542 = !DILocation(line: 887, column: 18, scope: !2095)
!2543 = !DILocation(line: 887, column: 29, scope: !2095)
!2544 = !DILocation(line: 889, column: 3, scope: !2095)
!2545 = !DILocation(line: 889, column: 12, scope: !2095)
!2546 = !DILocation(line: 889, column: 18, scope: !2095)
!2547 = !DILocation(line: 889, column: 30, scope: !2095)
!2548 = !DILocation(line: 891, column: 32, scope: !2095)
!2549 = !DILocation(line: 891, column: 38, scope: !2095)
!2550 = !DILocation(line: 891, column: 47, scope: !2095)
!2551 = !DILocation(line: 891, column: 3, scope: !2095)
!2552 = !DILocation(line: 891, column: 12, scope: !2095)
!2553 = !DILocation(line: 891, column: 21, scope: !2095)
!2554 = !DILocation(line: 891, column: 30, scope: !2095)
!2555 = !DILocation(line: 892, column: 32, scope: !2095)
!2556 = !DILocation(line: 892, column: 38, scope: !2095)
!2557 = !DILocation(line: 892, column: 47, scope: !2095)
!2558 = !DILocation(line: 892, column: 3, scope: !2095)
!2559 = !DILocation(line: 892, column: 12, scope: !2095)
!2560 = !DILocation(line: 892, column: 21, scope: !2095)
!2561 = !DILocation(line: 892, column: 30, scope: !2095)
!2562 = !DILocation(line: 894, column: 6, scope: !2563)
!2563 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 894, column: 6)
!2564 = !DILocation(line: 894, column: 12, scope: !2563)
!2565 = !DILocation(line: 894, column: 6, scope: !2095)
!2566 = !DILocation(line: 897, column: 41, scope: !2567)
!2567 = distinct !DILexicalBlock(scope: !2563, file: !1, line: 894, column: 21)
!2568 = !DILocation(line: 898, column: 41, scope: !2567)
!2569 = !DILocation(line: 898, column: 47, scope: !2567)
!2570 = !DILocation(line: 898, column: 56, scope: !2567)
!2571 = !DILocation(line: 899, column: 41, scope: !2567)
!2572 = !DILocation(line: 899, column: 50, scope: !2567)
!2573 = !DILocation(line: 900, column: 41, scope: !2567)
!2574 = !DILocation(line: 900, column: 47, scope: !2567)
!2575 = !DILocation(line: 900, column: 51, scope: !2567)
!2576 = !DILocation(line: 897, column: 24, scope: !2567)
!2577 = !DILocation(line: 897, column: 5, scope: !2567)
!2578 = !DILocation(line: 897, column: 14, scope: !2567)
!2579 = !DILocation(line: 897, column: 22, scope: !2567)
!2580 = !DILocation(line: 901, column: 9, scope: !2581)
!2581 = distinct !DILexicalBlock(scope: !2567, file: !1, line: 901, column: 8)
!2582 = !DILocation(line: 901, column: 18, scope: !2581)
!2583 = !DILocation(line: 901, column: 8, scope: !2567)
!2584 = !DILocation(line: 902, column: 7, scope: !2581)
!2585 = !DILocation(line: 903, column: 3, scope: !2567)
!2586 = !DILocation(line: 906, column: 6, scope: !2587)
!2587 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 906, column: 6)
!2588 = !DILocation(line: 906, column: 12, scope: !2587)
!2589 = !DILocation(line: 906, column: 19, scope: !2587)
!2590 = !DILocation(line: 906, column: 6, scope: !2095)
!2591 = !DILocation(line: 908, column: 28, scope: !2592)
!2592 = distinct !DILexicalBlock(scope: !2587, file: !1, line: 906, column: 31)
!2593 = !DILocation(line: 908, column: 34, scope: !2592)
!2594 = !DILocation(line: 908, column: 41, scope: !2592)
!2595 = !DILocation(line: 908, column: 7, scope: !2592)
!2596 = !DILocation(line: 907, column: 5, scope: !2592)
!2597 = !DILocation(line: 907, column: 14, scope: !2592)
!2598 = !DILocation(line: 907, column: 21, scope: !2592)
!2599 = !DILocation(line: 907, column: 32, scope: !2592)
!2600 = !DILocation(line: 909, column: 9, scope: !2601)
!2601 = distinct !DILexicalBlock(scope: !2592, file: !1, line: 909, column: 8)
!2602 = !DILocation(line: 909, column: 18, scope: !2601)
!2603 = !DILocation(line: 909, column: 25, scope: !2601)
!2604 = !DILocation(line: 909, column: 8, scope: !2592)
!2605 = !DILocation(line: 910, column: 7, scope: !2601)
!2606 = !DILocation(line: 911, column: 3, scope: !2592)
!2607 = !DILocation(line: 913, column: 6, scope: !2608)
!2608 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 913, column: 6)
!2609 = !DILocation(line: 913, column: 12, scope: !2608)
!2610 = !DILocation(line: 913, column: 19, scope: !2608)
!2611 = !DILocation(line: 913, column: 6, scope: !2095)
!2612 = !DILocation(line: 914, column: 27, scope: !2613)
!2613 = distinct !DILexicalBlock(scope: !2608, file: !1, line: 913, column: 24)
!2614 = !DILocation(line: 914, column: 5, scope: !2613)
!2615 = !DILocation(line: 914, column: 14, scope: !2613)
!2616 = !DILocation(line: 914, column: 21, scope: !2613)
!2617 = !DILocation(line: 914, column: 25, scope: !2613)
!2618 = !DILocation(line: 915, column: 9, scope: !2619)
!2619 = distinct !DILexicalBlock(scope: !2613, file: !1, line: 915, column: 8)
!2620 = !DILocation(line: 915, column: 18, scope: !2619)
!2621 = !DILocation(line: 915, column: 25, scope: !2619)
!2622 = !DILocation(line: 915, column: 8, scope: !2613)
!2623 = !DILocation(line: 916, column: 7, scope: !2619)
!2624 = !DILocation(line: 917, column: 5, scope: !2613)
!2625 = !DILocation(line: 917, column: 14, scope: !2613)
!2626 = !DILocation(line: 917, column: 21, scope: !2613)
!2627 = !DILocation(line: 917, column: 31, scope: !2613)
!2628 = !DILocation(line: 918, column: 3, scope: !2613)
!2629 = !DILocation(line: 920, column: 6, scope: !2630)
!2630 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 920, column: 6)
!2631 = !DILocation(line: 920, column: 12, scope: !2630)
!2632 = !DILocation(line: 920, column: 19, scope: !2630)
!2633 = !DILocation(line: 920, column: 6, scope: !2095)
!2634 = !DILocation(line: 921, column: 31, scope: !2635)
!2635 = distinct !DILexicalBlock(scope: !2630, file: !1, line: 920, column: 28)
!2636 = !DILocation(line: 921, column: 5, scope: !2635)
!2637 = !DILocation(line: 921, column: 14, scope: !2635)
!2638 = !DILocation(line: 921, column: 21, scope: !2635)
!2639 = !DILocation(line: 921, column: 29, scope: !2635)
!2640 = !DILocation(line: 922, column: 9, scope: !2641)
!2641 = distinct !DILexicalBlock(scope: !2635, file: !1, line: 922, column: 8)
!2642 = !DILocation(line: 922, column: 18, scope: !2641)
!2643 = !DILocation(line: 922, column: 25, scope: !2641)
!2644 = !DILocation(line: 922, column: 8, scope: !2635)
!2645 = !DILocation(line: 923, column: 7, scope: !2641)
!2646 = !DILocation(line: 924, column: 5, scope: !2635)
!2647 = !DILocation(line: 924, column: 14, scope: !2635)
!2648 = !DILocation(line: 924, column: 21, scope: !2635)
!2649 = !DILocation(line: 924, column: 35, scope: !2635)
!2650 = !DILocation(line: 925, column: 3, scope: !2635)
!2651 = !DILocation(line: 932, column: 3, scope: !2095)
!2652 = !DILocation(line: 932, column: 3, scope: !2653)
!2653 = !DILexicalBlockFile(scope: !2654, file: !1, discriminator: 1)
!2654 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 932, column: 3)
!2655 = !DILocation(line: 934, column: 17, scope: !2095)
!2656 = !DILocation(line: 934, column: 3, scope: !2095)
!2657 = !DILocation(line: 936, column: 3, scope: !2095)
!2658 = !DILocation(line: 936, column: 12, scope: !2095)
!2659 = !DILocation(line: 936, column: 18, scope: !2095)
!2660 = !DILocation(line: 940, column: 10, scope: !2095)
!2661 = !DILocation(line: 940, column: 3, scope: !2095)
!2662 = !DILocation(line: 944, column: 6, scope: !2663)
!2663 = distinct !DILexicalBlock(scope: !2095, file: !1, line: 944, column: 6)
!2664 = !DILocation(line: 944, column: 6, scope: !2095)
!2665 = !DILocation(line: 945, column: 25, scope: !2666)
!2666 = distinct !DILexicalBlock(scope: !2663, file: !1, line: 944, column: 15)
!2667 = !DILocation(line: 945, column: 34, scope: !2666)
!2668 = !DILocation(line: 945, column: 41, scope: !2666)
!2669 = !DILocation(line: 945, column: 5, scope: !2666)
!2670 = !DILocation(line: 946, column: 5, scope: !2666)
!2671 = !DILocation(line: 946, column: 14, scope: !2666)
!2672 = !DILocation(line: 946, column: 21, scope: !2666)
!2673 = !DILocation(line: 946, column: 32, scope: !2666)
!2674 = !DILocation(line: 947, column: 5, scope: !2666)
!2675 = !DILocation(line: 947, column: 5, scope: !2676)
!2676 = !DILexicalBlockFile(scope: !2677, file: !1, discriminator: 1)
!2677 = distinct !DILexicalBlock(scope: !2666, file: !1, line: 947, column: 5)
!2678 = !DILocation(line: 948, column: 5, scope: !2666)
!2679 = !DILocation(line: 948, column: 5, scope: !2680)
!2680 = !DILexicalBlockFile(scope: !2681, file: !1, discriminator: 1)
!2681 = distinct !DILexicalBlock(scope: !2666, file: !1, line: 948, column: 5)
!2682 = !DILocation(line: 949, column: 5, scope: !2666)
!2683 = !DILocation(line: 949, column: 5, scope: !2684)
!2684 = !DILexicalBlockFile(scope: !2685, file: !1, discriminator: 1)
!2685 = distinct !DILexicalBlock(scope: !2666, file: !1, line: 949, column: 5)
!2686 = !DILocation(line: 950, column: 5, scope: !2666)
!2687 = !DILocation(line: 950, column: 5, scope: !2688)
!2688 = !DILexicalBlockFile(scope: !2689, file: !1, discriminator: 1)
!2689 = distinct !DILexicalBlock(scope: !2666, file: !1, line: 950, column: 5)
!2690 = !DILocation(line: 951, column: 18, scope: !2666)
!2691 = !DILocation(line: 951, column: 5, scope: !2666)
!2692 = !DILocation(line: 952, column: 5, scope: !2666)
!2693 = !DILocation(line: 953, column: 3, scope: !2666)
!2694 = !DILocation(line: 955, column: 3, scope: !2095)
!2695 = !DILocation(line: 956, column: 1, scope: !2095)
!2696 = !DILocalVariable(name: "data", arg: 1, scope: !2098, file: !1, line: 962, type: !256)
!2697 = !DILocation(line: 962, column: 40, scope: !2098)
!2698 = !DILocation(line: 964, column: 3, scope: !2098)
!2699 = !DILocation(line: 964, column: 3, scope: !2700)
!2700 = !DILexicalBlockFile(scope: !2701, file: !1, discriminator: 1)
!2701 = distinct !DILexicalBlock(scope: !2098, file: !1, line: 964, column: 3)
!2702 = !DILocation(line: 966, column: 3, scope: !2098)
!2703 = !DILocation(line: 966, column: 9, scope: !2098)
!2704 = !DILocation(line: 966, column: 15, scope: !2098)
!2705 = !DILocation(line: 966, column: 20, scope: !2098)
!2706 = !DILocation(line: 968, column: 27, scope: !2098)
!2707 = !DILocation(line: 968, column: 3, scope: !2098)
!2708 = !DILocation(line: 971, column: 16, scope: !2098)
!2709 = !DILocation(line: 971, column: 3, scope: !2098)
!2710 = !DILocation(line: 972, column: 11, scope: !2098)
!2711 = !DILocation(line: 972, column: 17, scope: !2098)
!2712 = !DILocation(line: 972, column: 3, scope: !2098)
!2713 = !DILocation(line: 973, column: 32, scope: !2098)
!2714 = !DILocation(line: 973, column: 38, scope: !2098)
!2715 = !DILocation(line: 973, column: 9, scope: !2098)
!2716 = !DILocation(line: 976, column: 11, scope: !2098)
!2717 = !DILocation(line: 976, column: 17, scope: !2098)
!2718 = !DILocation(line: 976, column: 3, scope: !2098)
!2719 = !DILocation(line: 979, column: 17, scope: !2098)
!2720 = !DILocation(line: 979, column: 3, scope: !2098)
!2721 = !DILocation(line: 981, column: 3, scope: !2098)
!2722 = !DILocation(line: 981, column: 9, scope: !2098)
!2723 = !DILocation(line: 981, column: 18, scope: !2098)
!2724 = !DILocation(line: 981, column: 24, scope: !2098)
!2725 = !DILocation(line: 982, column: 3, scope: !2098)
!2726 = !DILocation(line: 982, column: 9, scope: !2098)
!2727 = !DILocation(line: 982, column: 15, scope: !2098)
!2728 = !DILocation(line: 982, column: 29, scope: !2098)
!2729 = !DILocation(line: 985, column: 11, scope: !2098)
!2730 = !DILocation(line: 985, column: 17, scope: !2098)
!2731 = !DILocation(line: 985, column: 23, scope: !2098)
!2732 = !DILocation(line: 985, column: 3, scope: !2098)
!2733 = !DILocation(line: 986, column: 11, scope: !2098)
!2734 = !DILocation(line: 986, column: 17, scope: !2098)
!2735 = !DILocation(line: 986, column: 23, scope: !2098)
!2736 = !DILocation(line: 986, column: 3, scope: !2098)
!2737 = !DILocation(line: 987, column: 1, scope: !2098)
!2738 = !DILocalVariable(name: "data", arg: 1, scope: !2099, file: !1, line: 999, type: !256)
!2739 = !DILocation(line: 999, column: 44, scope: !2099)
!2740 = !DILocalVariable(name: "action", arg: 2, scope: !2099, file: !1, line: 999, type: !316)
!2741 = !DILocation(line: 999, column: 54, scope: !2099)
!2742 = !DILocalVariable(name: "k", scope: !2099, file: !1, line: 1001, type: !2743)
!2743 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !552, size: 64, align: 64)
!2744 = !DILocation(line: 1001, column: 25, scope: !2099)
!2745 = !DILocation(line: 1001, column: 30, scope: !2099)
!2746 = !DILocation(line: 1001, column: 36, scope: !2099)
!2747 = !DILocalVariable(name: "result", scope: !2099, file: !1, line: 1002, type: !289)
!2748 = !DILocation(line: 1002, column: 12, scope: !2099)
!2749 = !DILocalVariable(name: "newstate", scope: !2099, file: !1, line: 1005, type: !316)
!2750 = !DILocation(line: 1005, column: 7, scope: !2099)
!2751 = !DILocation(line: 1005, column: 18, scope: !2099)
!2752 = !DILocation(line: 1005, column: 21, scope: !2099)
!2753 = !DILocation(line: 1005, column: 28, scope: !2099)
!2754 = !DILocation(line: 1008, column: 17, scope: !2099)
!2755 = !DILocation(line: 1008, column: 24, scope: !2099)
!2756 = !DILocation(line: 1008, column: 16, scope: !2099)
!2757 = !DILocation(line: 1009, column: 7, scope: !2099)
!2758 = !DILocation(line: 1009, column: 14, scope: !2099)
!2759 = !DILocation(line: 1009, column: 6, scope: !2099)
!2760 = !DILocation(line: 1008, column: 61, scope: !2099)
!2761 = !DILocation(line: 1008, column: 12, scope: !2099)
!2762 = !DILocation(line: 1012, column: 15, scope: !2099)
!2763 = !DILocation(line: 1012, column: 3, scope: !2099)
!2764 = !DILocation(line: 1012, column: 6, scope: !2099)
!2765 = !DILocation(line: 1012, column: 13, scope: !2099)
!2766 = !DILocation(line: 1014, column: 8, scope: !2767)
!2767 = distinct !DILexicalBlock(scope: !2099, file: !1, line: 1014, column: 6)
!2768 = !DILocation(line: 1014, column: 17, scope: !2767)
!2769 = !DILocation(line: 1014, column: 36, scope: !2767)
!2770 = !DILocation(line: 1014, column: 39, scope: !2771)
!2771 = !DILexicalBlockFile(scope: !2767, file: !1, discriminator: 1)
!2772 = !DILocation(line: 1014, column: 45, scope: !2771)
!2773 = !DILocation(line: 1014, column: 51, scope: !2771)
!2774 = !DILocation(line: 1014, column: 6, scope: !2771)
!2775 = !DILocalVariable(name: "i", scope: !2776, file: !1, line: 1017, type: !457)
!2776 = distinct !DILexicalBlock(scope: !2767, file: !1, line: 1014, column: 62)
!2777 = !DILocation(line: 1017, column: 18, scope: !2776)
!2778 = !DILocalVariable(name: "count", scope: !2776, file: !1, line: 1018, type: !457)
!2779 = !DILocation(line: 1018, column: 18, scope: !2776)
!2780 = !DILocation(line: 1018, column: 26, scope: !2776)
!2781 = !DILocation(line: 1018, column: 32, scope: !2776)
!2782 = !DILocation(line: 1018, column: 38, scope: !2776)
!2783 = !DILocalVariable(name: "writebuf", scope: !2776, file: !1, line: 1019, type: !1150)
!2784 = !DILocation(line: 1019, column: 20, scope: !2776)
!2785 = !DILocation(line: 1022, column: 10, scope: !2786)
!2786 = distinct !DILexicalBlock(scope: !2776, file: !1, line: 1022, column: 5)
!2787 = !DILocation(line: 1022, column: 9, scope: !2786)
!2788 = !DILocation(line: 1022, column: 14, scope: !2789)
!2789 = !DILexicalBlockFile(scope: !2790, file: !1, discriminator: 1)
!2790 = distinct !DILexicalBlock(scope: !2786, file: !1, line: 1022, column: 5)
!2791 = !DILocation(line: 1022, column: 18, scope: !2789)
!2792 = !DILocation(line: 1022, column: 24, scope: !2789)
!2793 = !DILocation(line: 1022, column: 30, scope: !2789)
!2794 = !DILocation(line: 1022, column: 16, scope: !2789)
!2795 = !DILocation(line: 1022, column: 5, scope: !2789)
!2796 = !DILocation(line: 1023, column: 16, scope: !2797)
!2797 = distinct !DILexicalBlock(scope: !2790, file: !1, line: 1022, column: 46)
!2798 = !DILocation(line: 1023, column: 7, scope: !2797)
!2799 = !DILocation(line: 1023, column: 43, scope: !2797)
!2800 = !DILocation(line: 1023, column: 21, scope: !2797)
!2801 = !DILocation(line: 1023, column: 27, scope: !2797)
!2802 = !DILocation(line: 1023, column: 33, scope: !2797)
!2803 = !DILocation(line: 1024, column: 29, scope: !2797)
!2804 = !DILocation(line: 1024, column: 7, scope: !2797)
!2805 = !DILocation(line: 1024, column: 13, scope: !2797)
!2806 = !DILocation(line: 1024, column: 19, scope: !2797)
!2807 = !DILocation(line: 1024, column: 32, scope: !2797)
!2808 = !DILocation(line: 1024, column: 36, scope: !2797)
!2809 = !DILocation(line: 1025, column: 5, scope: !2797)
!2810 = !DILocation(line: 1022, column: 42, scope: !2811)
!2811 = !DILexicalBlockFile(scope: !2790, file: !1, discriminator: 2)
!2812 = !DILocation(line: 1022, column: 5, scope: !2811)
!2813 = !DILocation(line: 1026, column: 5, scope: !2776)
!2814 = !DILocation(line: 1026, column: 11, scope: !2776)
!2815 = !DILocation(line: 1026, column: 17, scope: !2776)
!2816 = !DILocation(line: 1026, column: 27, scope: !2776)
!2817 = !DILocation(line: 1028, column: 10, scope: !2818)
!2818 = distinct !DILexicalBlock(scope: !2776, file: !1, line: 1028, column: 5)
!2819 = !DILocation(line: 1028, column: 9, scope: !2818)
!2820 = !DILocation(line: 1028, column: 14, scope: !2821)
!2821 = !DILexicalBlockFile(scope: !2822, file: !1, discriminator: 1)
!2822 = distinct !DILexicalBlock(scope: !2818, file: !1, line: 1028, column: 5)
!2823 = !DILocation(line: 1028, column: 18, scope: !2821)
!2824 = !DILocation(line: 1028, column: 16, scope: !2821)
!2825 = !DILocation(line: 1028, column: 5, scope: !2821)
!2826 = !DILocation(line: 1031, column: 11, scope: !2827)
!2827 = distinct !DILexicalBlock(scope: !2828, file: !1, line: 1031, column: 10)
!2828 = distinct !DILexicalBlock(scope: !2822, file: !1, line: 1028, column: 30)
!2829 = !DILocation(line: 1031, column: 10, scope: !2828)
!2830 = !DILocation(line: 1032, column: 41, scope: !2827)
!2831 = !DILocation(line: 1032, column: 47, scope: !2827)
!2832 = !DILocation(line: 1033, column: 50, scope: !2827)
!2833 = !DILocation(line: 1033, column: 41, scope: !2827)
!2834 = !DILocation(line: 1033, column: 53, scope: !2827)
!2835 = !DILocation(line: 1034, column: 50, scope: !2827)
!2836 = !DILocation(line: 1034, column: 41, scope: !2827)
!2837 = !DILocation(line: 1034, column: 53, scope: !2827)
!2838 = !DILocation(line: 1035, column: 50, scope: !2827)
!2839 = !DILocation(line: 1035, column: 41, scope: !2827)
!2840 = !DILocation(line: 1035, column: 53, scope: !2827)
!2841 = !DILocation(line: 1032, column: 18, scope: !2827)
!2842 = !DILocation(line: 1032, column: 16, scope: !2827)
!2843 = !DILocation(line: 1032, column: 9, scope: !2827)
!2844 = !DILocation(line: 1036, column: 7, scope: !2828)
!2845 = !DILocation(line: 1037, column: 5, scope: !2828)
!2846 = !DILocation(line: 1028, column: 26, scope: !2847)
!2847 = !DILexicalBlockFile(scope: !2822, file: !1, discriminator: 2)
!2848 = !DILocation(line: 1028, column: 5, scope: !2847)
!2849 = !DILocation(line: 1038, column: 8, scope: !2850)
!2850 = distinct !DILexicalBlock(scope: !2776, file: !1, line: 1038, column: 8)
!2851 = !DILocation(line: 1038, column: 8, scope: !2776)
!2852 = !DILocation(line: 1039, column: 14, scope: !2850)
!2853 = !DILocation(line: 1039, column: 7, scope: !2850)
!2854 = !DILocation(line: 1040, column: 3, scope: !2776)
!2855 = !DILocation(line: 1044, column: 7, scope: !2856)
!2856 = distinct !DILexicalBlock(scope: !2099, file: !1, line: 1044, column: 6)
!2857 = !DILocation(line: 1044, column: 14, scope: !2856)
!2858 = !DILocation(line: 1045, column: 8, scope: !2856)
!2859 = !DILocation(line: 1045, column: 16, scope: !2856)
!2860 = !DILocation(line: 1045, column: 52, scope: !2856)
!2861 = !DILocation(line: 1044, column: 6, scope: !2862)
!2862 = !DILexicalBlockFile(scope: !2099, file: !1, discriminator: 1)
!2863 = !DILocation(line: 1047, column: 17, scope: !2856)
!2864 = !DILocation(line: 1047, column: 5, scope: !2856)
!2865 = !DILocation(line: 1049, column: 10, scope: !2099)
!2866 = !DILocation(line: 1049, column: 3, scope: !2099)
!2867 = !DILocation(line: 1050, column: 1, scope: !2099)
!2868 = !DILocalVariable(name: "data", arg: 1, scope: !2102, file: !1, line: 1081, type: !256)
!2869 = !DILocation(line: 1081, column: 43, scope: !2102)
!2870 = !DILocalVariable(name: "buffer", arg: 2, scope: !2102, file: !1, line: 1081, type: !311)
!2871 = !DILocation(line: 1081, column: 55, scope: !2102)
!2872 = !DILocalVariable(name: "buflen", arg: 3, scope: !2102, file: !1, line: 1081, type: !347)
!2873 = !DILocation(line: 1081, column: 70, scope: !2102)
!2874 = !DILocalVariable(name: "n", arg: 4, scope: !2102, file: !1, line: 1082, type: !2105)
!2875 = !DILocation(line: 1082, column: 33, scope: !2102)
!2876 = !DILocalVariable(name: "sfd", scope: !2102, file: !1, line: 1084, type: !315)
!2877 = !DILocation(line: 1084, column: 17, scope: !2102)
!2878 = !DILocalVariable(name: "result", scope: !2102, file: !1, line: 1085, type: !289)
!2879 = !DILocation(line: 1085, column: 12, scope: !2102)
!2880 = !DILocalVariable(name: "n1", scope: !2102, file: !1, line: 1086, type: !612)
!2881 = !DILocation(line: 1086, column: 11, scope: !2102)
!2882 = !DILocalVariable(name: "c", scope: !2102, file: !1, line: 1087, type: !262)
!2883 = !DILocation(line: 1087, column: 23, scope: !2102)
!2884 = !DILocation(line: 1089, column: 28, scope: !2102)
!2885 = !DILocation(line: 1089, column: 12, scope: !2102)
!2886 = !DILocation(line: 1089, column: 10, scope: !2102)
!2887 = !DILocation(line: 1090, column: 6, scope: !2888)
!2888 = distinct !DILexicalBlock(scope: !2102, file: !1, line: 1090, column: 6)
!2889 = !DILocation(line: 1090, column: 6, scope: !2102)
!2890 = !DILocation(line: 1091, column: 12, scope: !2888)
!2891 = !DILocation(line: 1091, column: 5, scope: !2888)
!2892 = !DILocation(line: 1093, column: 4, scope: !2102)
!2893 = !DILocation(line: 1093, column: 6, scope: !2102)
!2894 = !DILocation(line: 1094, column: 22, scope: !2102)
!2895 = !DILocation(line: 1094, column: 25, scope: !2102)
!2896 = !DILocation(line: 1094, column: 30, scope: !2102)
!2897 = !DILocation(line: 1094, column: 38, scope: !2102)
!2898 = !DILocation(line: 1094, column: 12, scope: !2102)
!2899 = !DILocation(line: 1094, column: 10, scope: !2102)
!2900 = !DILocation(line: 1096, column: 6, scope: !2901)
!2901 = distinct !DILexicalBlock(scope: !2102, file: !1, line: 1096, column: 6)
!2902 = !DILocation(line: 1096, column: 6, scope: !2102)
!2903 = !DILocation(line: 1097, column: 12, scope: !2901)
!2904 = !DILocation(line: 1097, column: 5, scope: !2901)
!2905 = !DILocation(line: 1099, column: 16, scope: !2102)
!2906 = !DILocation(line: 1099, column: 4, scope: !2102)
!2907 = !DILocation(line: 1099, column: 6, scope: !2102)
!2908 = !DILocation(line: 1101, column: 3, scope: !2102)
!2909 = !DILocation(line: 1102, column: 1, scope: !2102)
!2910 = !DILocalVariable(name: "data", arg: 1, scope: !2122, file: !1, line: 1053, type: !256)
!2911 = !DILocation(line: 1053, column: 51, scope: !2122)
!2912 = !DILocalVariable(name: "sfd", arg: 2, scope: !2122, file: !1, line: 1054, type: !1480)
!2913 = !DILocation(line: 1054, column: 48, scope: !2122)
!2914 = !DILocalVariable(name: "connp", arg: 3, scope: !2122, file: !1, line: 1055, type: !2125)
!2915 = !DILocation(line: 1055, column: 54, scope: !2122)
!2916 = !DILocation(line: 1057, column: 6, scope: !2917)
!2917 = distinct !DILexicalBlock(scope: !2122, file: !1, line: 1057, column: 6)
!2918 = !DILocation(line: 1057, column: 11, scope: !2917)
!2919 = !DILocation(line: 1057, column: 6, scope: !2122)
!2920 = !DILocation(line: 1058, column: 5, scope: !2917)
!2921 = !DILocation(line: 1061, column: 7, scope: !2922)
!2922 = distinct !DILexicalBlock(scope: !2122, file: !1, line: 1061, column: 6)
!2923 = !DILocation(line: 1061, column: 13, scope: !2922)
!2924 = !DILocation(line: 1061, column: 17, scope: !2922)
!2925 = !DILocation(line: 1061, column: 6, scope: !2122)
!2926 = !DILocation(line: 1062, column: 11, scope: !2927)
!2927 = distinct !DILexicalBlock(scope: !2922, file: !1, line: 1061, column: 31)
!2928 = !DILocation(line: 1062, column: 5, scope: !2927)
!2929 = !DILocation(line: 1063, column: 5, scope: !2927)
!2930 = !DILocation(line: 1066, column: 30, scope: !2122)
!2931 = !DILocation(line: 1066, column: 36, scope: !2122)
!2932 = !DILocation(line: 1066, column: 10, scope: !2122)
!2933 = !DILocation(line: 1066, column: 4, scope: !2122)
!2934 = !DILocation(line: 1066, column: 8, scope: !2122)
!2935 = !DILocation(line: 1068, column: 7, scope: !2936)
!2936 = distinct !DILexicalBlock(scope: !2122, file: !1, line: 1068, column: 6)
!2937 = !DILocation(line: 1068, column: 6, scope: !2936)
!2938 = !DILocation(line: 1068, column: 11, scope: !2936)
!2939 = !DILocation(line: 1068, column: 6, scope: !2122)
!2940 = !DILocation(line: 1069, column: 11, scope: !2941)
!2941 = distinct !DILexicalBlock(scope: !2936, file: !1, line: 1068, column: 31)
!2942 = !DILocation(line: 1069, column: 5, scope: !2941)
!2943 = !DILocation(line: 1070, column: 5, scope: !2941)
!2944 = !DILocation(line: 1073, column: 3, scope: !2122)
!2945 = !DILocation(line: 1074, column: 1, scope: !2122)
!2946 = !DILocalVariable(name: "data", arg: 1, scope: !2106, file: !1, line: 1108, type: !256)
!2947 = !DILocation(line: 1108, column: 43, scope: !2106)
!2948 = !DILocalVariable(name: "buffer", arg: 2, scope: !2106, file: !1, line: 1108, type: !1046)
!2949 = !DILocation(line: 1108, column: 61, scope: !2106)
!2950 = !DILocalVariable(name: "buflen", arg: 3, scope: !2106, file: !1, line: 1109, type: !347)
!2951 = !DILocation(line: 1109, column: 32, scope: !2106)
!2952 = !DILocalVariable(name: "n", arg: 4, scope: !2106, file: !1, line: 1109, type: !2105)
!2953 = !DILocation(line: 1109, column: 48, scope: !2106)
!2954 = !DILocalVariable(name: "sfd", scope: !2106, file: !1, line: 1111, type: !315)
!2955 = !DILocation(line: 1111, column: 17, scope: !2106)
!2956 = !DILocalVariable(name: "result", scope: !2106, file: !1, line: 1112, type: !289)
!2957 = !DILocation(line: 1112, column: 12, scope: !2106)
!2958 = !DILocalVariable(name: "n1", scope: !2106, file: !1, line: 1113, type: !612)
!2959 = !DILocation(line: 1113, column: 11, scope: !2106)
!2960 = !DILocalVariable(name: "c", scope: !2106, file: !1, line: 1114, type: !262)
!2961 = !DILocation(line: 1114, column: 23, scope: !2106)
!2962 = !DILocation(line: 1116, column: 28, scope: !2106)
!2963 = !DILocation(line: 1116, column: 12, scope: !2106)
!2964 = !DILocation(line: 1116, column: 10, scope: !2106)
!2965 = !DILocation(line: 1117, column: 6, scope: !2966)
!2966 = distinct !DILexicalBlock(scope: !2106, file: !1, line: 1117, column: 6)
!2967 = !DILocation(line: 1117, column: 6, scope: !2106)
!2968 = !DILocation(line: 1118, column: 12, scope: !2966)
!2969 = !DILocation(line: 1118, column: 5, scope: !2966)
!2970 = !DILocation(line: 1120, column: 4, scope: !2106)
!2971 = !DILocation(line: 1120, column: 6, scope: !2106)
!2972 = !DILocation(line: 1121, column: 23, scope: !2106)
!2973 = !DILocation(line: 1121, column: 26, scope: !2106)
!2974 = !DILocation(line: 1121, column: 31, scope: !2106)
!2975 = !DILocation(line: 1121, column: 39, scope: !2106)
!2976 = !DILocation(line: 1121, column: 12, scope: !2106)
!2977 = !DILocation(line: 1121, column: 10, scope: !2106)
!2978 = !DILocation(line: 1123, column: 6, scope: !2979)
!2979 = distinct !DILexicalBlock(scope: !2106, file: !1, line: 1123, column: 6)
!2980 = !DILocation(line: 1123, column: 9, scope: !2979)
!2981 = !DILocation(line: 1123, column: 6, scope: !2106)
!2982 = !DILocation(line: 1124, column: 5, scope: !2979)
!2983 = !DILocation(line: 1127, column: 7, scope: !2984)
!2984 = distinct !DILexicalBlock(scope: !2106, file: !1, line: 1127, column: 6)
!2985 = !DILocation(line: 1127, column: 14, scope: !2984)
!2986 = !DILocation(line: 1127, column: 18, scope: !2987)
!2987 = !DILexicalBlockFile(scope: !2984, file: !1, discriminator: 1)
!2988 = !DILocation(line: 1127, column: 6, scope: !2987)
!2989 = !DILocation(line: 1128, column: 5, scope: !2984)
!2990 = !DILocation(line: 1130, column: 16, scope: !2106)
!2991 = !DILocation(line: 1130, column: 4, scope: !2106)
!2992 = !DILocation(line: 1130, column: 6, scope: !2106)
!2993 = !DILocation(line: 1132, column: 10, scope: !2106)
!2994 = !DILocation(line: 1132, column: 3, scope: !2106)
!2995 = !DILocation(line: 1133, column: 1, scope: !2106)
!2996 = !DILocation(line: 143, column: 3, scope: !2112)
!2997 = !DILocalVariable(name: "multi", arg: 1, scope: !2119, file: !1, line: 662, type: !375)
!2998 = !DILocation(line: 662, column: 50, scope: !2119)
!2999 = !DILocalVariable(name: "done", scope: !2119, file: !1, line: 664, type: !423)
!3000 = !DILocation(line: 664, column: 8, scope: !2119)
!3001 = !DILocalVariable(name: "mcode", scope: !2119, file: !1, line: 665, type: !2357)
!3002 = !DILocation(line: 665, column: 13, scope: !2119)
!3003 = !DILocalVariable(name: "result", scope: !2119, file: !1, line: 666, type: !289)
!3004 = !DILocation(line: 666, column: 12, scope: !2119)
!3005 = !DILocalVariable(name: "before", scope: !2119, file: !1, line: 667, type: !411)
!3006 = !DILocation(line: 667, column: 18, scope: !2119)
!3007 = !DILocalVariable(name: "without_fds", scope: !2119, file: !1, line: 668, type: !316)
!3008 = !DILocation(line: 668, column: 7, scope: !2119)
!3009 = !DILocation(line: 671, column: 3, scope: !2119)
!3010 = !DILocation(line: 671, column: 10, scope: !3011)
!3011 = !DILexicalBlockFile(scope: !2119, file: !1, discriminator: 1)
!3012 = !DILocation(line: 671, column: 15, scope: !3011)
!3013 = !DILocation(line: 671, column: 19, scope: !3014)
!3014 = !DILexicalBlockFile(scope: !2119, file: !1, discriminator: 2)
!3015 = !DILocation(line: 671, column: 18, scope: !3014)
!3016 = !DILocation(line: 671, column: 3, scope: !3017)
!3017 = !DILexicalBlockFile(scope: !2119, file: !1, discriminator: 3)
!3018 = !DILocalVariable(name: "still_running", scope: !3019, file: !1, line: 672, type: !316)
!3019 = distinct !DILexicalBlock(scope: !2119, file: !1, line: 671, column: 26)
!3020 = !DILocation(line: 672, column: 9, scope: !3019)
!3021 = !DILocalVariable(name: "rc", scope: !3019, file: !1, line: 673, type: !316)
!3022 = !DILocation(line: 673, column: 9, scope: !3019)
!3023 = !DILocation(line: 675, column: 14, scope: !3019)
!3024 = !DILocation(line: 675, column: 14, scope: !3025)
!3025 = !DILexicalBlockFile(scope: !3019, file: !1, discriminator: 1)
!3026 = !DILocation(line: 676, column: 29, scope: !3019)
!3027 = !DILocation(line: 676, column: 13, scope: !3019)
!3028 = !DILocation(line: 676, column: 11, scope: !3019)
!3029 = !DILocation(line: 678, column: 9, scope: !3030)
!3030 = distinct !DILexicalBlock(scope: !3019, file: !1, line: 678, column: 8)
!3031 = !DILocation(line: 678, column: 8, scope: !3019)
!3032 = !DILocation(line: 679, column: 11, scope: !3033)
!3033 = distinct !DILexicalBlock(scope: !3034, file: !1, line: 679, column: 10)
!3034 = distinct !DILexicalBlock(scope: !3030, file: !1, line: 678, column: 16)
!3035 = !DILocation(line: 679, column: 10, scope: !3034)
!3036 = !DILocalVariable(name: "after", scope: !3037, file: !1, line: 680, type: !411)
!3037 = distinct !DILexicalBlock(scope: !3033, file: !1, line: 679, column: 15)
!3038 = !DILocation(line: 680, column: 24, scope: !3037)
!3039 = !DILocation(line: 680, column: 32, scope: !3037)
!3040 = !DILocation(line: 685, column: 12, scope: !3041)
!3041 = distinct !DILexicalBlock(scope: !3037, file: !1, line: 685, column: 12)
!3042 = !DILocation(line: 685, column: 40, scope: !3041)
!3043 = !DILocation(line: 685, column: 12, scope: !3037)
!3044 = !DILocation(line: 686, column: 22, scope: !3045)
!3045 = distinct !DILexicalBlock(scope: !3041, file: !1, line: 685, column: 47)
!3046 = !DILocation(line: 687, column: 14, scope: !3047)
!3047 = distinct !DILexicalBlock(scope: !3045, file: !1, line: 687, column: 14)
!3048 = !DILocation(line: 687, column: 26, scope: !3047)
!3049 = !DILocation(line: 687, column: 14, scope: !3045)
!3050 = !DILocalVariable(name: "sleep_ms", scope: !3051, file: !1, line: 688, type: !316)
!3051 = distinct !DILexicalBlock(scope: !3047, file: !1, line: 687, column: 31)
!3052 = !DILocation(line: 688, column: 17, scope: !3051)
!3053 = !DILocation(line: 688, column: 28, scope: !3051)
!3054 = !DILocation(line: 688, column: 40, scope: !3051)
!3055 = !DILocation(line: 688, column: 54, scope: !3056)
!3056 = !DILexicalBlockFile(scope: !3051, file: !1, discriminator: 1)
!3057 = !DILocation(line: 688, column: 66, scope: !3056)
!3058 = !DILocation(line: 688, column: 50, scope: !3056)
!3059 = !DILocation(line: 688, column: 28, scope: !3056)
!3060 = !DILocation(line: 688, column: 28, scope: !3061)
!3061 = !DILexicalBlockFile(scope: !3051, file: !1, discriminator: 2)
!3062 = !DILocation(line: 688, column: 28, scope: !3063)
!3063 = !DILexicalBlockFile(scope: !3051, file: !1, discriminator: 3)
!3064 = !DILocation(line: 688, column: 17, scope: !3063)
!3065 = !DILocation(line: 689, column: 26, scope: !3051)
!3066 = !DILocation(line: 689, column: 13, scope: !3051)
!3067 = !DILocation(line: 690, column: 11, scope: !3051)
!3068 = !DILocation(line: 691, column: 9, scope: !3045)
!3069 = !DILocation(line: 694, column: 23, scope: !3041)
!3070 = !DILocation(line: 695, column: 7, scope: !3037)
!3071 = !DILocation(line: 698, column: 21, scope: !3033)
!3072 = !DILocation(line: 700, column: 34, scope: !3034)
!3073 = !DILocation(line: 700, column: 15, scope: !3034)
!3074 = !DILocation(line: 700, column: 13, scope: !3034)
!3075 = !DILocation(line: 701, column: 5, scope: !3034)
!3076 = !DILocation(line: 704, column: 9, scope: !3077)
!3077 = distinct !DILexicalBlock(scope: !3019, file: !1, line: 704, column: 8)
!3078 = !DILocation(line: 704, column: 15, scope: !3077)
!3079 = !DILocation(line: 704, column: 19, scope: !3080)
!3080 = !DILexicalBlockFile(scope: !3077, file: !1, discriminator: 1)
!3081 = !DILocation(line: 704, column: 8, scope: !3080)
!3082 = !DILocalVariable(name: "msg", scope: !3083, file: !1, line: 705, type: !3084)
!3083 = distinct !DILexicalBlock(scope: !3077, file: !1, line: 704, column: 34)
!3084 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !3085, size: 64, align: 64)
!3085 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLMsg", file: !295, line: 101, baseType: !294)
!3086 = !DILocation(line: 705, column: 16, scope: !3083)
!3087 = !DILocation(line: 705, column: 43, scope: !3083)
!3088 = !DILocation(line: 705, column: 22, scope: !3083)
!3089 = !DILocation(line: 706, column: 10, scope: !3090)
!3090 = distinct !DILexicalBlock(scope: !3083, file: !1, line: 706, column: 10)
!3091 = !DILocation(line: 706, column: 10, scope: !3083)
!3092 = !DILocation(line: 707, column: 18, scope: !3093)
!3093 = distinct !DILexicalBlock(scope: !3090, file: !1, line: 706, column: 15)
!3094 = !DILocation(line: 707, column: 23, scope: !3093)
!3095 = !DILocation(line: 707, column: 28, scope: !3093)
!3096 = !DILocation(line: 707, column: 16, scope: !3093)
!3097 = !DILocation(line: 708, column: 14, scope: !3093)
!3098 = !DILocation(line: 709, column: 7, scope: !3093)
!3099 = !DILocation(line: 710, column: 5, scope: !3083)
!3100 = !DILocation(line: 671, column: 3, scope: !3101)
!3101 = !DILexicalBlockFile(scope: !2119, file: !1, discriminator: 4)
!3102 = !DILocation(line: 714, column: 6, scope: !3103)
!3103 = distinct !DILexicalBlock(scope: !2119, file: !1, line: 714, column: 6)
!3104 = !DILocation(line: 714, column: 6, scope: !2119)
!3105 = !DILocation(line: 715, column: 15, scope: !3106)
!3106 = distinct !DILexicalBlock(scope: !3103, file: !1, line: 714, column: 13)
!3107 = !DILocation(line: 715, column: 21, scope: !3106)
!3108 = !DILocation(line: 715, column: 14, scope: !3106)
!3109 = !DILocation(line: 715, column: 12, scope: !3106)
!3110 = !DILocation(line: 719, column: 3, scope: !3106)
!3111 = !DILocation(line: 721, column: 10, scope: !2119)
!3112 = !DILocation(line: 721, column: 3, scope: !2119)
