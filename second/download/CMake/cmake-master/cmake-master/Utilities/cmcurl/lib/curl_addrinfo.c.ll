; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_addrinfo.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.Curl_addrinfo = type { i32, i32, i32, i32, i32, i8*, %struct.sockaddr*, %struct.Curl_addrinfo* }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.addrinfo = type { i32, i32, i32, i32, i32, %struct.sockaddr*, i8*, %struct.addrinfo* }
%struct.hostent = type { i8*, i8**, i32, i32, i8** }
%struct.sockaddr_in = type { i16, i16, %struct.in_addr, [8 x i8] }
%struct.in_addr = type { i32 }
%struct.namebuff = type { %struct.hostent, %union.anon, [2 x i8*] }
%union.anon = type { %struct.in_addr }

@Curl_cfree = external global void (i8*)*, align 8
@Curl_cmalloc = external global i8* (i64)*, align 8
@Curl_cstrdup = external global i8* (i8*)*, align 8
@Curl_ccalloc = external global i8* (i64, i64)*, align 8

; Function Attrs: nounwind uwtable
define void @Curl_freeaddrinfo(%struct.Curl_addrinfo* %cahead) #0 !dbg !127 {
entry:
  %cahead.addr = alloca %struct.Curl_addrinfo*, align 8
  %canext = alloca %struct.Curl_addrinfo*, align 8
  %ca = alloca %struct.Curl_addrinfo*, align 8
  store %struct.Curl_addrinfo* %cahead, %struct.Curl_addrinfo** %cahead.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %cahead.addr, metadata !202, metadata !203), !dbg !204
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %canext, metadata !205, metadata !203), !dbg !206
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %ca, metadata !207, metadata !203), !dbg !208
  %0 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %cahead.addr, align 8, !dbg !209
  store %struct.Curl_addrinfo* %0, %struct.Curl_addrinfo** %ca, align 8, !dbg !211
  br label %for.cond, !dbg !212

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !213
  %cmp = icmp ne %struct.Curl_addrinfo* %1, null, !dbg !216
  br i1 %cmp, label %for.body, label %for.end, !dbg !217

for.body:                                         ; preds = %for.cond
  %2 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !218
  %3 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !218
  %ai_addr = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %3, i32 0, i32 6, !dbg !218
  %4 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr, align 8, !dbg !218
  %5 = bitcast %struct.sockaddr* %4 to i8*, !dbg !218
  call void %2(i8* %5), !dbg !218
  %6 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !220
  %7 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !220
  %ai_canonname = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %7, i32 0, i32 5, !dbg !220
  %8 = load i8*, i8** %ai_canonname, align 8, !dbg !220
  call void %6(i8* %8), !dbg !220
  %9 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !221
  %ai_next = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %9, i32 0, i32 7, !dbg !222
  %10 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai_next, align 8, !dbg !222
  store %struct.Curl_addrinfo* %10, %struct.Curl_addrinfo** %canext, align 8, !dbg !223
  %11 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !224
  %12 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !224
  %13 = bitcast %struct.Curl_addrinfo* %12 to i8*, !dbg !224
  call void %11(i8* %13), !dbg !224
  br label %for.inc, !dbg !225

for.inc:                                          ; preds = %for.body
  %14 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %canext, align 8, !dbg !226
  store %struct.Curl_addrinfo* %14, %struct.Curl_addrinfo** %ca, align 8, !dbg !228
  br label %for.cond, !dbg !229

for.end:                                          ; preds = %for.cond
  ret void, !dbg !230
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @Curl_getaddrinfo_ex(i8* %nodename, i8* %servname, %struct.addrinfo* %hints, %struct.Curl_addrinfo** %result) #0 !dbg !158 {
entry:
  %retval = alloca i32, align 4
  %nodename.addr = alloca i8*, align 8
  %servname.addr = alloca i8*, align 8
  %hints.addr = alloca %struct.addrinfo*, align 8
  %result.addr = alloca %struct.Curl_addrinfo**, align 8
  %ai = alloca %struct.addrinfo*, align 8
  %aihead = alloca %struct.addrinfo*, align 8
  %cafirst = alloca %struct.Curl_addrinfo*, align 8
  %calast = alloca %struct.Curl_addrinfo*, align 8
  %ca = alloca %struct.Curl_addrinfo*, align 8
  %ss_size = alloca i64, align 8
  %error = alloca i32, align 4
  store i8* %nodename, i8** %nodename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %nodename.addr, metadata !231, metadata !203), !dbg !232
  store i8* %servname, i8** %servname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %servname.addr, metadata !233, metadata !203), !dbg !234
  store %struct.addrinfo* %hints, %struct.addrinfo** %hints.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.addrinfo** %hints.addr, metadata !235, metadata !203), !dbg !236
  store %struct.Curl_addrinfo** %result, %struct.Curl_addrinfo*** %result.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo*** %result.addr, metadata !237, metadata !203), !dbg !238
  call void @llvm.dbg.declare(metadata %struct.addrinfo** %ai, metadata !239, metadata !203), !dbg !240
  call void @llvm.dbg.declare(metadata %struct.addrinfo** %aihead, metadata !241, metadata !203), !dbg !242
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %cafirst, metadata !243, metadata !203), !dbg !244
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %cafirst, align 8, !dbg !244
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %calast, metadata !245, metadata !203), !dbg !246
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %calast, align 8, !dbg !246
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %ca, metadata !247, metadata !203), !dbg !248
  call void @llvm.dbg.declare(metadata i64* %ss_size, metadata !249, metadata !203), !dbg !250
  call void @llvm.dbg.declare(metadata i32* %error, metadata !251, metadata !203), !dbg !252
  %0 = load %struct.Curl_addrinfo**, %struct.Curl_addrinfo*** %result.addr, align 8, !dbg !253
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %0, align 8, !dbg !254
  %1 = load i8*, i8** %nodename.addr, align 8, !dbg !255
  %2 = load i8*, i8** %servname.addr, align 8, !dbg !256
  %3 = load %struct.addrinfo*, %struct.addrinfo** %hints.addr, align 8, !dbg !257
  %call = call i32 @getaddrinfo(i8* %1, i8* %2, %struct.addrinfo* %3, %struct.addrinfo** %aihead), !dbg !258
  store i32 %call, i32* %error, align 4, !dbg !259
  %4 = load i32, i32* %error, align 4, !dbg !260
  %tobool = icmp ne i32 %4, 0, !dbg !260
  br i1 %tobool, label %if.then, label %if.end, !dbg !262

if.then:                                          ; preds = %entry
  %5 = load i32, i32* %error, align 4, !dbg !263
  store i32 %5, i32* %retval, align 4, !dbg !264
  br label %return, !dbg !264

if.end:                                           ; preds = %entry
  %6 = load %struct.addrinfo*, %struct.addrinfo** %aihead, align 8, !dbg !265
  store %struct.addrinfo* %6, %struct.addrinfo** %ai, align 8, !dbg !267
  br label %for.cond, !dbg !268

for.cond:                                         ; preds = %for.inc, %if.end
  %7 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !269
  %cmp = icmp ne %struct.addrinfo* %7, null, !dbg !272
  br i1 %cmp, label %for.body, label %for.end, !dbg !273

for.body:                                         ; preds = %for.cond
  %8 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !274
  %ai_family = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %8, i32 0, i32 1, !dbg !277
  %9 = load i32, i32* %ai_family, align 4, !dbg !277
  %cmp1 = icmp eq i32 %9, 2, !dbg !278
  br i1 %cmp1, label %if.then2, label %if.else, !dbg !279

if.then2:                                         ; preds = %for.body
  store i64 16, i64* %ss_size, align 8, !dbg !280
  br label %if.end3, !dbg !281

if.else:                                          ; preds = %for.body
  br label %for.inc, !dbg !282

if.end3:                                          ; preds = %if.then2
  %10 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !283
  %ai_addr = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %10, i32 0, i32 5, !dbg !285
  %11 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr, align 8, !dbg !285
  %cmp4 = icmp eq %struct.sockaddr* %11, null, !dbg !286
  br i1 %cmp4, label %if.then6, label %lor.lhs.false, !dbg !287

lor.lhs.false:                                    ; preds = %if.end3
  %12 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !288
  %ai_addrlen = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %12, i32 0, i32 4, !dbg !290
  %13 = load i32, i32* %ai_addrlen, align 8, !dbg !290
  %cmp5 = icmp ugt i32 %13, 0, !dbg !291
  br i1 %cmp5, label %if.end7, label %if.then6, !dbg !292

if.then6:                                         ; preds = %lor.lhs.false, %if.end3
  br label %for.inc, !dbg !293

if.end7:                                          ; preds = %lor.lhs.false
  %14 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !294
  %ai_addrlen8 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %14, i32 0, i32 4, !dbg !296
  %15 = load i32, i32* %ai_addrlen8, align 8, !dbg !296
  %conv = zext i32 %15 to i64, !dbg !297
  %16 = load i64, i64* %ss_size, align 8, !dbg !298
  %cmp9 = icmp ult i64 %conv, %16, !dbg !299
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !300

if.then11:                                        ; preds = %if.end7
  br label %for.inc, !dbg !301

if.end12:                                         ; preds = %if.end7
  %17 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !302
  %call13 = call i8* %17(i64 48), !dbg !302
  %18 = bitcast i8* %call13 to %struct.Curl_addrinfo*, !dbg !302
  store %struct.Curl_addrinfo* %18, %struct.Curl_addrinfo** %ca, align 8, !dbg !303
  %19 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !304
  %tobool14 = icmp ne %struct.Curl_addrinfo* %19, null, !dbg !304
  br i1 %tobool14, label %if.end16, label %if.then15, !dbg !306

if.then15:                                        ; preds = %if.end12
  store i32 -10, i32* %error, align 4, !dbg !307
  br label %for.end, !dbg !309

if.end16:                                         ; preds = %if.end12
  %20 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !310
  %ai_flags = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %20, i32 0, i32 0, !dbg !311
  %21 = load i32, i32* %ai_flags, align 8, !dbg !311
  %22 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !312
  %ai_flags17 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %22, i32 0, i32 0, !dbg !313
  store i32 %21, i32* %ai_flags17, align 8, !dbg !314
  %23 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !315
  %ai_family18 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %23, i32 0, i32 1, !dbg !316
  %24 = load i32, i32* %ai_family18, align 4, !dbg !316
  %25 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !317
  %ai_family19 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %25, i32 0, i32 1, !dbg !318
  store i32 %24, i32* %ai_family19, align 4, !dbg !319
  %26 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !320
  %ai_socktype = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %26, i32 0, i32 2, !dbg !321
  %27 = load i32, i32* %ai_socktype, align 8, !dbg !321
  %28 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !322
  %ai_socktype20 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %28, i32 0, i32 2, !dbg !323
  store i32 %27, i32* %ai_socktype20, align 8, !dbg !324
  %29 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !325
  %ai_protocol = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %29, i32 0, i32 3, !dbg !326
  %30 = load i32, i32* %ai_protocol, align 4, !dbg !326
  %31 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !327
  %ai_protocol21 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %31, i32 0, i32 3, !dbg !328
  store i32 %30, i32* %ai_protocol21, align 4, !dbg !329
  %32 = load i64, i64* %ss_size, align 8, !dbg !330
  %conv22 = trunc i64 %32 to i32, !dbg !331
  %33 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !332
  %ai_addrlen23 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %33, i32 0, i32 4, !dbg !333
  store i32 %conv22, i32* %ai_addrlen23, align 8, !dbg !334
  %34 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !335
  %ai_addr24 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %34, i32 0, i32 6, !dbg !336
  store %struct.sockaddr* null, %struct.sockaddr** %ai_addr24, align 8, !dbg !337
  %35 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !338
  %ai_canonname = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %35, i32 0, i32 5, !dbg !339
  store i8* null, i8** %ai_canonname, align 8, !dbg !340
  %36 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !341
  %ai_next = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %36, i32 0, i32 7, !dbg !342
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %ai_next, align 8, !dbg !343
  %37 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !344
  %38 = load i64, i64* %ss_size, align 8, !dbg !344
  %call25 = call i8* %37(i64 %38), !dbg !344
  %39 = bitcast i8* %call25 to %struct.sockaddr*, !dbg !344
  %40 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !345
  %ai_addr26 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %40, i32 0, i32 6, !dbg !346
  store %struct.sockaddr* %39, %struct.sockaddr** %ai_addr26, align 8, !dbg !347
  %41 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !348
  %ai_addr27 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %41, i32 0, i32 6, !dbg !350
  %42 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr27, align 8, !dbg !350
  %tobool28 = icmp ne %struct.sockaddr* %42, null, !dbg !348
  br i1 %tobool28, label %if.end30, label %if.then29, !dbg !351

if.then29:                                        ; preds = %if.end16
  store i32 -10, i32* %error, align 4, !dbg !352
  %43 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !354
  %44 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !354
  %45 = bitcast %struct.Curl_addrinfo* %44 to i8*, !dbg !354
  call void %43(i8* %45), !dbg !354
  br label %for.end, !dbg !355

if.end30:                                         ; preds = %if.end16
  %46 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !356
  %ai_addr31 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %46, i32 0, i32 6, !dbg !357
  %47 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr31, align 8, !dbg !357
  %48 = bitcast %struct.sockaddr* %47 to i8*, !dbg !358
  %49 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !359
  %ai_addr32 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %49, i32 0, i32 5, !dbg !360
  %50 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr32, align 8, !dbg !360
  %51 = bitcast %struct.sockaddr* %50 to i8*, !dbg !358
  %52 = load i64, i64* %ss_size, align 8, !dbg !361
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %48, i8* %51, i64 %52, i32 2, i1 false), !dbg !358
  %53 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !362
  %ai_canonname33 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %53, i32 0, i32 6, !dbg !364
  %54 = load i8*, i8** %ai_canonname33, align 8, !dbg !364
  %cmp34 = icmp ne i8* %54, null, !dbg !365
  br i1 %cmp34, label %if.then36, label %if.end45, !dbg !366

if.then36:                                        ; preds = %if.end30
  %55 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !367
  %56 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !367
  %ai_canonname37 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %56, i32 0, i32 6, !dbg !367
  %57 = load i8*, i8** %ai_canonname37, align 8, !dbg !367
  %call38 = call i8* %55(i8* %57), !dbg !367
  %58 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !369
  %ai_canonname39 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %58, i32 0, i32 5, !dbg !370
  store i8* %call38, i8** %ai_canonname39, align 8, !dbg !371
  %59 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !372
  %ai_canonname40 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %59, i32 0, i32 5, !dbg !374
  %60 = load i8*, i8** %ai_canonname40, align 8, !dbg !374
  %tobool41 = icmp ne i8* %60, null, !dbg !372
  br i1 %tobool41, label %if.end44, label %if.then42, !dbg !375

if.then42:                                        ; preds = %if.then36
  store i32 -10, i32* %error, align 4, !dbg !376
  %61 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !378
  %62 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !378
  %ai_addr43 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %62, i32 0, i32 6, !dbg !378
  %63 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr43, align 8, !dbg !378
  %64 = bitcast %struct.sockaddr* %63 to i8*, !dbg !378
  call void %61(i8* %64), !dbg !378
  %65 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !379
  %66 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !379
  %67 = bitcast %struct.Curl_addrinfo* %66 to i8*, !dbg !379
  call void %65(i8* %67), !dbg !379
  br label %for.end, !dbg !380

if.end44:                                         ; preds = %if.then36
  br label %if.end45, !dbg !381

if.end45:                                         ; preds = %if.end44, %if.end30
  %68 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %cafirst, align 8, !dbg !382
  %tobool46 = icmp ne %struct.Curl_addrinfo* %68, null, !dbg !382
  br i1 %tobool46, label %if.end48, label %if.then47, !dbg !384

if.then47:                                        ; preds = %if.end45
  %69 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !385
  store %struct.Curl_addrinfo* %69, %struct.Curl_addrinfo** %cafirst, align 8, !dbg !386
  br label %if.end48, !dbg !387

if.end48:                                         ; preds = %if.then47, %if.end45
  %70 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %calast, align 8, !dbg !388
  %tobool49 = icmp ne %struct.Curl_addrinfo* %70, null, !dbg !388
  br i1 %tobool49, label %if.then50, label %if.end52, !dbg !390

if.then50:                                        ; preds = %if.end48
  %71 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !391
  %72 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %calast, align 8, !dbg !392
  %ai_next51 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %72, i32 0, i32 7, !dbg !393
  store %struct.Curl_addrinfo* %71, %struct.Curl_addrinfo** %ai_next51, align 8, !dbg !394
  br label %if.end52, !dbg !392

if.end52:                                         ; preds = %if.then50, %if.end48
  %73 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ca, align 8, !dbg !395
  store %struct.Curl_addrinfo* %73, %struct.Curl_addrinfo** %calast, align 8, !dbg !396
  br label %for.inc, !dbg !397

for.inc:                                          ; preds = %if.end52, %if.then11, %if.then6, %if.else
  %74 = load %struct.addrinfo*, %struct.addrinfo** %ai, align 8, !dbg !398
  %ai_next53 = getelementptr inbounds %struct.addrinfo, %struct.addrinfo* %74, i32 0, i32 7, !dbg !400
  %75 = load %struct.addrinfo*, %struct.addrinfo** %ai_next53, align 8, !dbg !400
  store %struct.addrinfo* %75, %struct.addrinfo** %ai, align 8, !dbg !401
  br label %for.cond, !dbg !402

for.end:                                          ; preds = %if.then42, %if.then29, %if.then15, %for.cond
  %76 = load %struct.addrinfo*, %struct.addrinfo** %aihead, align 8, !dbg !403
  %tobool54 = icmp ne %struct.addrinfo* %76, null, !dbg !403
  br i1 %tobool54, label %if.then55, label %if.end56, !dbg !405

if.then55:                                        ; preds = %for.end
  %77 = load %struct.addrinfo*, %struct.addrinfo** %aihead, align 8, !dbg !406
  call void @freeaddrinfo(%struct.addrinfo* %77) #6, !dbg !407
  br label %if.end56, !dbg !407

if.end56:                                         ; preds = %if.then55, %for.end
  %78 = load i32, i32* %error, align 4, !dbg !408
  %tobool57 = icmp ne i32 %78, 0, !dbg !408
  br i1 %tobool57, label %if.then58, label %if.else59, !dbg !410

if.then58:                                        ; preds = %if.end56
  %79 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %cafirst, align 8, !dbg !411
  call void @Curl_freeaddrinfo(%struct.Curl_addrinfo* %79), !dbg !413
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %cafirst, align 8, !dbg !414
  br label %if.end63, !dbg !415

if.else59:                                        ; preds = %if.end56
  %80 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %cafirst, align 8, !dbg !416
  %tobool60 = icmp ne %struct.Curl_addrinfo* %80, null, !dbg !416
  br i1 %tobool60, label %if.end62, label %if.then61, !dbg !418

if.then61:                                        ; preds = %if.else59
  store i32 -2, i32* %error, align 4, !dbg !419
  br label %if.end62, !dbg !421

if.end62:                                         ; preds = %if.then61, %if.else59
  br label %if.end63

if.end63:                                         ; preds = %if.end62, %if.then58
  %81 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %cafirst, align 8, !dbg !422
  %82 = load %struct.Curl_addrinfo**, %struct.Curl_addrinfo*** %result.addr, align 8, !dbg !423
  store %struct.Curl_addrinfo* %81, %struct.Curl_addrinfo** %82, align 8, !dbg !424
  %83 = load i32, i32* %error, align 4, !dbg !425
  store i32 %83, i32* %retval, align 4, !dbg !426
  br label %return, !dbg !426

return:                                           ; preds = %if.end63, %if.then
  %84 = load i32, i32* %retval, align 4, !dbg !427
  ret i32 %84, !dbg !427
}

declare i32 @getaddrinfo(i8*, i8*, %struct.addrinfo*, %struct.addrinfo**) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

; Function Attrs: nounwind
declare void @freeaddrinfo(%struct.addrinfo*) #4

; Function Attrs: nounwind uwtable
define %struct.Curl_addrinfo* @Curl_he2ai(%struct.hostent* %he, i32 %port) #0 !dbg !178 {
entry:
  %retval = alloca %struct.Curl_addrinfo*, align 8
  %he.addr = alloca %struct.hostent*, align 8
  %port.addr = alloca i32, align 4
  %ai = alloca %struct.Curl_addrinfo*, align 8
  %prevai = alloca %struct.Curl_addrinfo*, align 8
  %firstai = alloca %struct.Curl_addrinfo*, align 8
  %addr = alloca %struct.sockaddr_in*, align 8
  %result = alloca i32, align 4
  %i = alloca i32, align 4
  %curr = alloca i8*, align 8
  %ss_size = alloca i64, align 8
  store %struct.hostent* %he, %struct.hostent** %he.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.hostent** %he.addr, metadata !428, metadata !203), !dbg !429
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !430, metadata !203), !dbg !431
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %ai, metadata !432, metadata !203), !dbg !433
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %prevai, metadata !434, metadata !203), !dbg !435
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %prevai, align 8, !dbg !435
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %firstai, metadata !436, metadata !203), !dbg !437
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %firstai, align 8, !dbg !437
  call void @llvm.dbg.declare(metadata %struct.sockaddr_in** %addr, metadata !438, metadata !203), !dbg !459
  call void @llvm.dbg.declare(metadata i32* %result, metadata !460, metadata !203), !dbg !462
  store i32 0, i32* %result, align 4, !dbg !462
  call void @llvm.dbg.declare(metadata i32* %i, metadata !463, metadata !203), !dbg !464
  call void @llvm.dbg.declare(metadata i8** %curr, metadata !465, metadata !203), !dbg !466
  %0 = load %struct.hostent*, %struct.hostent** %he.addr, align 8, !dbg !467
  %tobool = icmp ne %struct.hostent* %0, null, !dbg !467
  br i1 %tobool, label %if.end, label %if.then, !dbg !469

if.then:                                          ; preds = %entry
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %retval, align 8, !dbg !470
  br label %return, !dbg !470

if.end:                                           ; preds = %entry
  br label %do.body, !dbg !471

do.body:                                          ; preds = %if.end
  br label %do.end, !dbg !472

do.end:                                           ; preds = %do.body
  store i32 0, i32* %i, align 4, !dbg !475
  br label %for.cond, !dbg !477

for.cond:                                         ; preds = %for.inc, %do.end
  %1 = load i32, i32* %i, align 4, !dbg !478
  %idxprom = sext i32 %1 to i64, !dbg !481
  %2 = load %struct.hostent*, %struct.hostent** %he.addr, align 8, !dbg !481
  %h_addr_list = getelementptr inbounds %struct.hostent, %struct.hostent* %2, i32 0, i32 4, !dbg !482
  %3 = load i8**, i8*** %h_addr_list, align 8, !dbg !482
  %arrayidx = getelementptr inbounds i8*, i8** %3, i64 %idxprom, !dbg !481
  %4 = load i8*, i8** %arrayidx, align 8, !dbg !481
  store i8* %4, i8** %curr, align 8, !dbg !483
  %cmp = icmp ne i8* %4, null, !dbg !484
  br i1 %cmp, label %for.body, label %for.end, !dbg !485

for.body:                                         ; preds = %for.cond
  call void @llvm.dbg.declare(metadata i64* %ss_size, metadata !486, metadata !203), !dbg !488
  store i64 16, i64* %ss_size, align 8, !dbg !489
  %5 = load i8* (i64, i64)*, i8* (i64, i64)** @Curl_ccalloc, align 8, !dbg !490
  %call = call i8* %5(i64 1, i64 48), !dbg !490
  %6 = bitcast i8* %call to %struct.Curl_addrinfo*, !dbg !490
  store %struct.Curl_addrinfo* %6, %struct.Curl_addrinfo** %ai, align 8, !dbg !491
  %7 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !492
  %tobool1 = icmp ne %struct.Curl_addrinfo* %7, null, !dbg !492
  br i1 %tobool1, label %if.end3, label %if.then2, !dbg !494

if.then2:                                         ; preds = %for.body
  store i32 27, i32* %result, align 4, !dbg !495
  br label %for.end, !dbg !497

if.end3:                                          ; preds = %for.body
  %8 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !498
  %9 = load %struct.hostent*, %struct.hostent** %he.addr, align 8, !dbg !498
  %h_name = getelementptr inbounds %struct.hostent, %struct.hostent* %9, i32 0, i32 0, !dbg !498
  %10 = load i8*, i8** %h_name, align 8, !dbg !498
  %call4 = call i8* %8(i8* %10), !dbg !498
  %11 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !499
  %ai_canonname = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %11, i32 0, i32 5, !dbg !500
  store i8* %call4, i8** %ai_canonname, align 8, !dbg !501
  %12 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !502
  %ai_canonname5 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %12, i32 0, i32 5, !dbg !504
  %13 = load i8*, i8** %ai_canonname5, align 8, !dbg !504
  %tobool6 = icmp ne i8* %13, null, !dbg !502
  br i1 %tobool6, label %if.end8, label %if.then7, !dbg !505

if.then7:                                         ; preds = %if.end3
  store i32 27, i32* %result, align 4, !dbg !506
  %14 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !508
  %15 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !508
  %16 = bitcast %struct.Curl_addrinfo* %15 to i8*, !dbg !508
  call void %14(i8* %16), !dbg !508
  br label %for.end, !dbg !509

if.end8:                                          ; preds = %if.end3
  %17 = load i8* (i64, i64)*, i8* (i64, i64)** @Curl_ccalloc, align 8, !dbg !510
  %18 = load i64, i64* %ss_size, align 8, !dbg !510
  %call9 = call i8* %17(i64 1, i64 %18), !dbg !510
  %19 = bitcast i8* %call9 to %struct.sockaddr*, !dbg !510
  %20 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !511
  %ai_addr = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %20, i32 0, i32 6, !dbg !512
  store %struct.sockaddr* %19, %struct.sockaddr** %ai_addr, align 8, !dbg !513
  %21 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !514
  %ai_addr10 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %21, i32 0, i32 6, !dbg !516
  %22 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr10, align 8, !dbg !516
  %tobool11 = icmp ne %struct.sockaddr* %22, null, !dbg !514
  br i1 %tobool11, label %if.end14, label %if.then12, !dbg !517

if.then12:                                        ; preds = %if.end8
  store i32 27, i32* %result, align 4, !dbg !518
  %23 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !520
  %24 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !520
  %ai_canonname13 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %24, i32 0, i32 5, !dbg !520
  %25 = load i8*, i8** %ai_canonname13, align 8, !dbg !520
  call void %23(i8* %25), !dbg !520
  %26 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !521
  %27 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !521
  %28 = bitcast %struct.Curl_addrinfo* %27 to i8*, !dbg !521
  call void %26(i8* %28), !dbg !521
  br label %for.end, !dbg !522

if.end14:                                         ; preds = %if.end8
  %29 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %firstai, align 8, !dbg !523
  %tobool15 = icmp ne %struct.Curl_addrinfo* %29, null, !dbg !523
  br i1 %tobool15, label %if.end17, label %if.then16, !dbg !525

if.then16:                                        ; preds = %if.end14
  %30 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !526
  store %struct.Curl_addrinfo* %30, %struct.Curl_addrinfo** %firstai, align 8, !dbg !527
  br label %if.end17, !dbg !528

if.end17:                                         ; preds = %if.then16, %if.end14
  %31 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %prevai, align 8, !dbg !529
  %tobool18 = icmp ne %struct.Curl_addrinfo* %31, null, !dbg !529
  br i1 %tobool18, label %if.then19, label %if.end20, !dbg !531

if.then19:                                        ; preds = %if.end17
  %32 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !532
  %33 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %prevai, align 8, !dbg !533
  %ai_next = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %33, i32 0, i32 7, !dbg !534
  store %struct.Curl_addrinfo* %32, %struct.Curl_addrinfo** %ai_next, align 8, !dbg !535
  br label %if.end20, !dbg !533

if.end20:                                         ; preds = %if.then19, %if.end17
  %34 = load %struct.hostent*, %struct.hostent** %he.addr, align 8, !dbg !536
  %h_addrtype = getelementptr inbounds %struct.hostent, %struct.hostent* %34, i32 0, i32 2, !dbg !537
  %35 = load i32, i32* %h_addrtype, align 8, !dbg !537
  %36 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !538
  %ai_family = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %36, i32 0, i32 1, !dbg !539
  store i32 %35, i32* %ai_family, align 4, !dbg !540
  %37 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !541
  %ai_socktype = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %37, i32 0, i32 2, !dbg !542
  store i32 1, i32* %ai_socktype, align 8, !dbg !543
  %38 = load i64, i64* %ss_size, align 8, !dbg !544
  %conv = trunc i64 %38 to i32, !dbg !545
  %39 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !546
  %ai_addrlen = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %39, i32 0, i32 4, !dbg !547
  store i32 %conv, i32* %ai_addrlen, align 8, !dbg !548
  %40 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !549
  %ai_family21 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %40, i32 0, i32 1, !dbg !550
  %41 = load i32, i32* %ai_family21, align 4, !dbg !550
  switch i32 %41, label %sw.epilog [
    i32 2, label %sw.bb
  ], !dbg !551

sw.bb:                                            ; preds = %if.end20
  %42 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !552
  %ai_addr22 = getelementptr inbounds %struct.Curl_addrinfo, %struct.Curl_addrinfo* %42, i32 0, i32 6, !dbg !554
  %43 = load %struct.sockaddr*, %struct.sockaddr** %ai_addr22, align 8, !dbg !554
  %44 = bitcast %struct.sockaddr* %43 to i8*, !dbg !555
  %45 = bitcast i8* %44 to %struct.sockaddr_in*, !dbg !555
  store %struct.sockaddr_in* %45, %struct.sockaddr_in** %addr, align 8, !dbg !556
  %46 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr, align 8, !dbg !557
  %sin_addr = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %46, i32 0, i32 2, !dbg !558
  %47 = bitcast %struct.in_addr* %sin_addr to i8*, !dbg !559
  %48 = load i8*, i8** %curr, align 8, !dbg !560
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %47, i8* %48, i64 4, i32 1, i1 false), !dbg !559
  %49 = load %struct.hostent*, %struct.hostent** %he.addr, align 8, !dbg !561
  %h_addrtype23 = getelementptr inbounds %struct.hostent, %struct.hostent* %49, i32 0, i32 2, !dbg !562
  %50 = load i32, i32* %h_addrtype23, align 8, !dbg !562
  %conv24 = trunc i32 %50 to i16, !dbg !563
  %51 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr, align 8, !dbg !564
  %sin_family = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %51, i32 0, i32 0, !dbg !565
  store i16 %conv24, i16* %sin_family, align 4, !dbg !566
  %52 = load i32, i32* %port.addr, align 4, !dbg !567
  %conv25 = trunc i32 %52 to i16, !dbg !568
  %call26 = call zeroext i16 @htons(i16 zeroext %conv25) #1, !dbg !569
  %53 = load %struct.sockaddr_in*, %struct.sockaddr_in** %addr, align 8, !dbg !570
  %sin_port = getelementptr inbounds %struct.sockaddr_in, %struct.sockaddr_in* %53, i32 0, i32 1, !dbg !571
  store i16 %call26, i16* %sin_port, align 2, !dbg !572
  br label %sw.epilog, !dbg !573

sw.epilog:                                        ; preds = %if.end20, %sw.bb
  %54 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !574
  store %struct.Curl_addrinfo* %54, %struct.Curl_addrinfo** %prevai, align 8, !dbg !575
  br label %for.inc, !dbg !576

for.inc:                                          ; preds = %sw.epilog
  %55 = load i32, i32* %i, align 4, !dbg !577
  %inc = add nsw i32 %55, 1, !dbg !577
  store i32 %inc, i32* %i, align 4, !dbg !577
  br label %for.cond, !dbg !579

for.end:                                          ; preds = %if.then12, %if.then7, %if.then2, %for.cond
  %56 = load i32, i32* %result, align 4, !dbg !580
  %tobool27 = icmp ne i32 %56, 0, !dbg !580
  br i1 %tobool27, label %if.then28, label %if.end29, !dbg !582

if.then28:                                        ; preds = %for.end
  %57 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %firstai, align 8, !dbg !583
  call void @Curl_freeaddrinfo(%struct.Curl_addrinfo* %57), !dbg !585
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %firstai, align 8, !dbg !586
  br label %if.end29, !dbg !587

if.end29:                                         ; preds = %if.then28, %for.end
  %58 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %firstai, align 8, !dbg !588
  store %struct.Curl_addrinfo* %58, %struct.Curl_addrinfo** %retval, align 8, !dbg !589
  br label %return, !dbg !589

return:                                           ; preds = %if.end29, %if.then
  %59 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %retval, align 8, !dbg !590
  ret %struct.Curl_addrinfo* %59, !dbg !590
}

; Function Attrs: nounwind readnone
declare zeroext i16 @htons(i16 zeroext) #5

; Function Attrs: nounwind uwtable
define %struct.Curl_addrinfo* @Curl_ip2addr(i32 %af, i8* %inaddr, i8* %hostname, i32 %port) #0 !dbg !191 {
entry:
  %retval = alloca %struct.Curl_addrinfo*, align 8
  %af.addr = alloca i32, align 4
  %inaddr.addr = alloca i8*, align 8
  %hostname.addr = alloca i8*, align 8
  %port.addr = alloca i32, align 4
  %ai = alloca %struct.Curl_addrinfo*, align 8
  %h = alloca %struct.hostent*, align 8
  %buf = alloca %struct.namebuff*, align 8
  %addrentry = alloca i8*, align 8
  %hoststr = alloca i8*, align 8
  %addrsize = alloca i64, align 8
  store i32 %af, i32* %af.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %af.addr, metadata !591, metadata !203), !dbg !592
  store i8* %inaddr, i8** %inaddr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %inaddr.addr, metadata !593, metadata !203), !dbg !594
  store i8* %hostname, i8** %hostname.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %hostname.addr, metadata !595, metadata !203), !dbg !596
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !597, metadata !203), !dbg !598
  call void @llvm.dbg.declare(metadata %struct.Curl_addrinfo** %ai, metadata !599, metadata !203), !dbg !600
  call void @llvm.dbg.declare(metadata %struct.hostent** %h, metadata !601, metadata !203), !dbg !603
  call void @llvm.dbg.declare(metadata %struct.namebuff** %buf, metadata !604, metadata !203), !dbg !617
  call void @llvm.dbg.declare(metadata i8** %addrentry, metadata !618, metadata !203), !dbg !619
  call void @llvm.dbg.declare(metadata i8** %hoststr, metadata !620, metadata !203), !dbg !621
  call void @llvm.dbg.declare(metadata i64* %addrsize, metadata !622, metadata !203), !dbg !623
  br label %do.body, !dbg !624

do.body:                                          ; preds = %entry
  br label %do.end, !dbg !625

do.end:                                           ; preds = %do.body
  %0 = load i8* (i64)*, i8* (i64)** @Curl_cmalloc, align 8, !dbg !628
  %call = call i8* %0(i64 56), !dbg !628
  %1 = bitcast i8* %call to %struct.namebuff*, !dbg !628
  store %struct.namebuff* %1, %struct.namebuff** %buf, align 8, !dbg !629
  %2 = load %struct.namebuff*, %struct.namebuff** %buf, align 8, !dbg !630
  %tobool = icmp ne %struct.namebuff* %2, null, !dbg !630
  br i1 %tobool, label %if.end, label %if.then, !dbg !632

if.then:                                          ; preds = %do.end
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %retval, align 8, !dbg !633
  br label %return, !dbg !633

if.end:                                           ; preds = %do.end
  %3 = load i8* (i8*)*, i8* (i8*)** @Curl_cstrdup, align 8, !dbg !634
  %4 = load i8*, i8** %hostname.addr, align 8, !dbg !634
  %call1 = call i8* %3(i8* %4), !dbg !634
  store i8* %call1, i8** %hoststr, align 8, !dbg !635
  %5 = load i8*, i8** %hoststr, align 8, !dbg !636
  %tobool2 = icmp ne i8* %5, null, !dbg !636
  br i1 %tobool2, label %if.end4, label %if.then3, !dbg !638

if.then3:                                         ; preds = %if.end
  %6 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !639
  %7 = load %struct.namebuff*, %struct.namebuff** %buf, align 8, !dbg !639
  %8 = bitcast %struct.namebuff* %7 to i8*, !dbg !639
  call void %6(i8* %8), !dbg !639
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %retval, align 8, !dbg !641
  br label %return, !dbg !641

if.end4:                                          ; preds = %if.end
  %9 = load i32, i32* %af.addr, align 4, !dbg !642
  switch i32 %9, label %sw.default [
    i32 2, label %sw.bb
  ], !dbg !643

sw.bb:                                            ; preds = %if.end4
  store i64 4, i64* %addrsize, align 8, !dbg !644
  %10 = load %struct.namebuff*, %struct.namebuff** %buf, align 8, !dbg !646
  %addrentry5 = getelementptr inbounds %struct.namebuff, %struct.namebuff* %10, i32 0, i32 1, !dbg !647
  %ina4 = bitcast %union.anon* %addrentry5 to %struct.in_addr*, !dbg !648
  %11 = bitcast %struct.in_addr* %ina4 to i8*, !dbg !649
  store i8* %11, i8** %addrentry, align 8, !dbg !650
  %12 = load i8*, i8** %addrentry, align 8, !dbg !651
  %13 = load i8*, i8** %inaddr.addr, align 8, !dbg !652
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %12, i8* %13, i64 4, i32 1, i1 false), !dbg !653
  br label %sw.epilog, !dbg !654

sw.default:                                       ; preds = %if.end4
  %14 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !655
  %15 = load i8*, i8** %hoststr, align 8, !dbg !655
  call void %14(i8* %15), !dbg !655
  %16 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !656
  %17 = load %struct.namebuff*, %struct.namebuff** %buf, align 8, !dbg !656
  %18 = bitcast %struct.namebuff* %17 to i8*, !dbg !656
  call void %16(i8* %18), !dbg !656
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %retval, align 8, !dbg !657
  br label %return, !dbg !657

sw.epilog:                                        ; preds = %sw.bb
  %19 = load %struct.namebuff*, %struct.namebuff** %buf, align 8, !dbg !658
  %hostentry = getelementptr inbounds %struct.namebuff, %struct.namebuff* %19, i32 0, i32 0, !dbg !659
  store %struct.hostent* %hostentry, %struct.hostent** %h, align 8, !dbg !660
  %20 = load i8*, i8** %hoststr, align 8, !dbg !661
  %21 = load %struct.hostent*, %struct.hostent** %h, align 8, !dbg !662
  %h_name = getelementptr inbounds %struct.hostent, %struct.hostent* %21, i32 0, i32 0, !dbg !663
  store i8* %20, i8** %h_name, align 8, !dbg !664
  %22 = load %struct.hostent*, %struct.hostent** %h, align 8, !dbg !665
  %h_aliases = getelementptr inbounds %struct.hostent, %struct.hostent* %22, i32 0, i32 1, !dbg !666
  store i8** null, i8*** %h_aliases, align 8, !dbg !667
  %23 = load i32, i32* %af.addr, align 4, !dbg !668
  %conv = trunc i32 %23 to i16, !dbg !669
  %conv6 = sext i16 %conv to i32, !dbg !669
  %24 = load %struct.hostent*, %struct.hostent** %h, align 8, !dbg !670
  %h_addrtype = getelementptr inbounds %struct.hostent, %struct.hostent* %24, i32 0, i32 2, !dbg !671
  store i32 %conv6, i32* %h_addrtype, align 8, !dbg !672
  %25 = load i64, i64* %addrsize, align 8, !dbg !673
  %conv7 = trunc i64 %25 to i16, !dbg !674
  %conv8 = sext i16 %conv7 to i32, !dbg !674
  %26 = load %struct.hostent*, %struct.hostent** %h, align 8, !dbg !675
  %h_length = getelementptr inbounds %struct.hostent, %struct.hostent* %26, i32 0, i32 3, !dbg !676
  store i32 %conv8, i32* %h_length, align 4, !dbg !677
  %27 = load %struct.namebuff*, %struct.namebuff** %buf, align 8, !dbg !678
  %h_addr_list = getelementptr inbounds %struct.namebuff, %struct.namebuff* %27, i32 0, i32 2, !dbg !679
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %h_addr_list, i64 0, i64 0, !dbg !678
  %28 = load %struct.hostent*, %struct.hostent** %h, align 8, !dbg !680
  %h_addr_list9 = getelementptr inbounds %struct.hostent, %struct.hostent* %28, i32 0, i32 4, !dbg !681
  store i8** %arrayidx, i8*** %h_addr_list9, align 8, !dbg !682
  %29 = load i8*, i8** %addrentry, align 8, !dbg !683
  %30 = load %struct.hostent*, %struct.hostent** %h, align 8, !dbg !684
  %h_addr_list10 = getelementptr inbounds %struct.hostent, %struct.hostent* %30, i32 0, i32 4, !dbg !685
  %31 = load i8**, i8*** %h_addr_list10, align 8, !dbg !685
  %arrayidx11 = getelementptr inbounds i8*, i8** %31, i64 0, !dbg !684
  store i8* %29, i8** %arrayidx11, align 8, !dbg !686
  %32 = load %struct.hostent*, %struct.hostent** %h, align 8, !dbg !687
  %h_addr_list12 = getelementptr inbounds %struct.hostent, %struct.hostent* %32, i32 0, i32 4, !dbg !688
  %33 = load i8**, i8*** %h_addr_list12, align 8, !dbg !688
  %arrayidx13 = getelementptr inbounds i8*, i8** %33, i64 1, !dbg !687
  store i8* null, i8** %arrayidx13, align 8, !dbg !689
  %34 = load %struct.hostent*, %struct.hostent** %h, align 8, !dbg !690
  %35 = load i32, i32* %port.addr, align 4, !dbg !691
  %call14 = call %struct.Curl_addrinfo* @Curl_he2ai(%struct.hostent* %34, i32 %35), !dbg !692
  store %struct.Curl_addrinfo* %call14, %struct.Curl_addrinfo** %ai, align 8, !dbg !693
  %36 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !694
  %37 = load i8*, i8** %hoststr, align 8, !dbg !694
  call void %36(i8* %37), !dbg !694
  %38 = load void (i8*)*, void (i8*)** @Curl_cfree, align 8, !dbg !695
  %39 = load %struct.namebuff*, %struct.namebuff** %buf, align 8, !dbg !695
  %40 = bitcast %struct.namebuff* %39 to i8*, !dbg !695
  call void %38(i8* %40), !dbg !695
  %41 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %ai, align 8, !dbg !696
  store %struct.Curl_addrinfo* %41, %struct.Curl_addrinfo** %retval, align 8, !dbg !697
  br label %return, !dbg !697

return:                                           ; preds = %sw.epilog, %sw.default, %if.then3, %if.then
  %42 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %retval, align 8, !dbg !698
  ret %struct.Curl_addrinfo* %42, !dbg !698
}

; Function Attrs: nounwind uwtable
define %struct.Curl_addrinfo* @Curl_str2addr(i8* %address, i32 %port) #0 !dbg !196 {
entry:
  %retval = alloca %struct.Curl_addrinfo*, align 8
  %address.addr = alloca i8*, align 8
  %port.addr = alloca i32, align 4
  %in = alloca %struct.in_addr, align 4
  store i8* %address, i8** %address.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %address.addr, metadata !699, metadata !203), !dbg !700
  store i32 %port, i32* %port.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %port.addr, metadata !701, metadata !203), !dbg !702
  call void @llvm.dbg.declare(metadata %struct.in_addr* %in, metadata !703, metadata !203), !dbg !704
  %0 = load i8*, i8** %address.addr, align 8, !dbg !705
  %1 = bitcast %struct.in_addr* %in to i8*, !dbg !705
  %call = call i32 @inet_pton(i32 2, i8* %0, i8* %1) #6, !dbg !705
  %cmp = icmp sgt i32 %call, 0, !dbg !707
  br i1 %cmp, label %if.then, label %if.end, !dbg !708

if.then:                                          ; preds = %entry
  %2 = bitcast %struct.in_addr* %in to i8*, !dbg !709
  %3 = load i8*, i8** %address.addr, align 8, !dbg !710
  %4 = load i32, i32* %port.addr, align 4, !dbg !711
  %call1 = call %struct.Curl_addrinfo* @Curl_ip2addr(i32 2, i8* %2, i8* %3, i32 %4), !dbg !712
  store %struct.Curl_addrinfo* %call1, %struct.Curl_addrinfo** %retval, align 8, !dbg !713
  br label %return, !dbg !713

if.end:                                           ; preds = %entry
  store %struct.Curl_addrinfo* null, %struct.Curl_addrinfo** %retval, align 8, !dbg !714
  br label %return, !dbg !714

return:                                           ; preds = %if.end, %if.then
  %5 = load %struct.Curl_addrinfo*, %struct.Curl_addrinfo** %retval, align 8, !dbg !715
  ret %struct.Curl_addrinfo* %5, !dbg !715
}

; Function Attrs: nounwind
declare i32 @inet_pton(i32, i8*, i8*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!199, !200}
!llvm.ident = !{!201}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !112, subprograms: !126)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_addrinfo.c", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!2 = !{!3, !100}
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
!100 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !101, line: 24, size: 32, align: 32, elements: !102)
!101 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!102 = !{!103, !104, !105, !106, !107, !108, !109, !110, !111}
!103 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!104 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!105 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!106 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!107 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!108 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!109 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!110 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!111 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!112 = !{!113, !114, !117, !124, !125}
!113 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!114 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !115, line: 62, baseType: !116)
!115 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!116 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!117 = !DIDerivedType(tag: DW_TAG_typedef, name: "curl_socklen_t", file: !118, line: 186, baseType: !119)
!118 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/include/curl/curlbuild.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !120, line: 33, baseType: !121)
!120 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !122, line: 189, baseType: !123)
!122 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!123 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!124 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!125 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!126 = !{!127, !158, !178, !191, !196}
!127 = distinct !DISubprogram(name: "Curl_freeaddrinfo", scope: !1, file: !1, line: 78, type: !128, isLocal: false, isDefinition: true, scopeLine: 79, flags: DIFlagPrototyped, isOptimized: false, variables: !157)
!128 = !DISubroutineType(types: !129)
!129 = !{null, !130}
!130 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !131, size: 64, align: 64)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "Curl_addrinfo", file: !132, line: 61, baseType: !133)
!132 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib/curl_addrinfo.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!133 = !DICompositeType(tag: DW_TAG_structure_type, name: "Curl_addrinfo", file: !132, line: 51, size: 384, align: 64, elements: !134)
!134 = !{!135, !137, !138, !139, !140, !141, !144, !155}
!135 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !133, file: !132, line: 52, baseType: !136, size: 32, align: 32)
!136 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !133, file: !132, line: 53, baseType: !136, size: 32, align: 32, offset: 32)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !133, file: !132, line: 54, baseType: !136, size: 32, align: 32, offset: 64)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !133, file: !132, line: 55, baseType: !136, size: 32, align: 32, offset: 96)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !133, file: !132, line: 56, baseType: !117, size: 32, align: 32, offset: 128)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !133, file: !132, line: 57, baseType: !142, size: 64, align: 64, offset: 192)
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !143, size: 64, align: 64)
!143 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !133, file: !132, line: 58, baseType: !145, size: 64, align: 64, offset: 256)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !120, line: 149, size: 128, align: 16, elements: !147)
!147 = !{!148, !151}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !146, file: !120, line: 151, baseType: !149, size: 16, align: 16)
!149 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !150, line: 28, baseType: !124)
!150 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!151 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !146, file: !120, line: 152, baseType: !152, size: 112, align: 8, offset: 16)
!152 = !DICompositeType(tag: DW_TAG_array_type, baseType: !143, size: 112, align: 8, elements: !153)
!153 = !{!154}
!154 = !DISubrange(count: 14)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !133, file: !132, line: 59, baseType: !156, size: 64, align: 64, offset: 320)
!156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !133, size: 64, align: 64)
!157 = !{}
!158 = distinct !DISubprogram(name: "Curl_getaddrinfo_ex", scope: !1, file: !1, line: 109, type: !159, isLocal: false, isDefinition: true, scopeLine: 113, flags: DIFlagPrototyped, isOptimized: false, variables: !157)
!159 = !DISubroutineType(types: !160)
!160 = !{!136, !161, !161, !163, !177}
!161 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !162, size: 64, align: 64)
!162 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !143)
!163 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !164, size: 64, align: 64)
!164 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !165)
!165 = !DICompositeType(tag: DW_TAG_structure_type, name: "addrinfo", file: !166, line: 567, size: 384, align: 64, elements: !167)
!166 = !DIFile(filename: "/usr/include/netdb.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!167 = !{!168, !169, !170, !171, !172, !173, !174, !175}
!168 = !DIDerivedType(tag: DW_TAG_member, name: "ai_flags", scope: !165, file: !166, line: 569, baseType: !136, size: 32, align: 32)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "ai_family", scope: !165, file: !166, line: 570, baseType: !136, size: 32, align: 32, offset: 32)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "ai_socktype", scope: !165, file: !166, line: 571, baseType: !136, size: 32, align: 32, offset: 64)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "ai_protocol", scope: !165, file: !166, line: 572, baseType: !136, size: 32, align: 32, offset: 96)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addrlen", scope: !165, file: !166, line: 573, baseType: !119, size: 32, align: 32, offset: 128)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "ai_addr", scope: !165, file: !166, line: 574, baseType: !145, size: 64, align: 64, offset: 192)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "ai_canonname", scope: !165, file: !166, line: 575, baseType: !142, size: 64, align: 64, offset: 256)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "ai_next", scope: !165, file: !166, line: 576, baseType: !176, size: 64, align: 64, offset: 320)
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !165, size: 64, align: 64)
!177 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!178 = distinct !DISubprogram(name: "Curl_he2ai", scope: !1, file: !1, line: 270, type: !179, isLocal: false, isDefinition: true, scopeLine: 271, flags: DIFlagPrototyped, isOptimized: false, variables: !157)
!179 = !DISubroutineType(types: !180)
!180 = !{!130, !181, !136}
!181 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !182, size: 64, align: 64)
!182 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !183)
!183 = !DICompositeType(tag: DW_TAG_structure_type, name: "hostent", file: !166, line: 100, size: 256, align: 64, elements: !184)
!184 = !{!185, !186, !188, !189, !190}
!185 = !DIDerivedType(tag: DW_TAG_member, name: "h_name", scope: !183, file: !166, line: 102, baseType: !142, size: 64, align: 64)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "h_aliases", scope: !183, file: !166, line: 103, baseType: !187, size: 64, align: 64, offset: 64)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "h_addrtype", scope: !183, file: !166, line: 104, baseType: !136, size: 32, align: 32, offset: 128)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "h_length", scope: !183, file: !166, line: 105, baseType: !136, size: 32, align: 32, offset: 160)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "h_addr_list", scope: !183, file: !166, line: 106, baseType: !187, size: 64, align: 64, offset: 192)
!191 = distinct !DISubprogram(name: "Curl_ip2addr", scope: !1, file: !1, line: 390, type: !192, isLocal: false, isDefinition: true, scopeLine: 391, flags: DIFlagPrototyped, isOptimized: false, variables: !157)
!192 = !DISubroutineType(types: !193)
!193 = !{!130, !136, !194, !161, !136}
!194 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !195, size: 64, align: 64)
!195 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!196 = distinct !DISubprogram(name: "Curl_str2addr", scope: !1, file: !1, line: 465, type: !197, isLocal: false, isDefinition: true, scopeLine: 466, flags: DIFlagPrototyped, isOptimized: false, variables: !157)
!197 = !DISubroutineType(types: !198)
!198 = !{!130, !142, !136}
!199 = !{i32 2, !"Dwarf Version", i32 4}
!200 = !{i32 2, !"Debug Info Version", i32 3}
!201 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!202 = !DILocalVariable(name: "cahead", arg: 1, scope: !127, file: !1, line: 78, type: !130)
!203 = !DIExpression()
!204 = !DILocation(line: 78, column: 34, scope: !127)
!205 = !DILocalVariable(name: "canext", scope: !127, file: !1, line: 80, type: !130)
!206 = !DILocation(line: 80, column: 29, scope: !127)
!207 = !DILocalVariable(name: "ca", scope: !127, file: !1, line: 81, type: !130)
!208 = !DILocation(line: 81, column: 18, scope: !127)
!209 = !DILocation(line: 83, column: 12, scope: !210)
!210 = distinct !DILexicalBlock(scope: !127, file: !1, line: 83, column: 3)
!211 = !DILocation(line: 83, column: 10, scope: !210)
!212 = !DILocation(line: 83, column: 7, scope: !210)
!213 = !DILocation(line: 83, column: 20, scope: !214)
!214 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 1)
!215 = distinct !DILexicalBlock(scope: !210, file: !1, line: 83, column: 3)
!216 = !DILocation(line: 83, column: 23, scope: !214)
!217 = !DILocation(line: 83, column: 3, scope: !214)
!218 = !DILocation(line: 84, column: 5, scope: !219)
!219 = distinct !DILexicalBlock(scope: !215, file: !1, line: 83, column: 45)
!220 = !DILocation(line: 85, column: 5, scope: !219)
!221 = !DILocation(line: 86, column: 14, scope: !219)
!222 = !DILocation(line: 86, column: 18, scope: !219)
!223 = !DILocation(line: 86, column: 12, scope: !219)
!224 = !DILocation(line: 88, column: 5, scope: !219)
!225 = !DILocation(line: 89, column: 3, scope: !219)
!226 = !DILocation(line: 83, column: 37, scope: !227)
!227 = !DILexicalBlockFile(scope: !215, file: !1, discriminator: 2)
!228 = !DILocation(line: 83, column: 35, scope: !227)
!229 = !DILocation(line: 83, column: 3, scope: !227)
!230 = !DILocation(line: 90, column: 1, scope: !127)
!231 = !DILocalVariable(name: "nodename", arg: 1, scope: !158, file: !1, line: 109, type: !161)
!232 = !DILocation(line: 109, column: 33, scope: !158)
!233 = !DILocalVariable(name: "servname", arg: 2, scope: !158, file: !1, line: 110, type: !161)
!234 = !DILocation(line: 110, column: 33, scope: !158)
!235 = !DILocalVariable(name: "hints", arg: 3, scope: !158, file: !1, line: 111, type: !163)
!236 = !DILocation(line: 111, column: 44, scope: !158)
!237 = !DILocalVariable(name: "result", arg: 4, scope: !158, file: !1, line: 112, type: !177)
!238 = !DILocation(line: 112, column: 37, scope: !158)
!239 = !DILocalVariable(name: "ai", scope: !158, file: !1, line: 114, type: !163)
!240 = !DILocation(line: 114, column: 26, scope: !158)
!241 = !DILocalVariable(name: "aihead", scope: !158, file: !1, line: 115, type: !176)
!242 = !DILocation(line: 115, column: 20, scope: !158)
!243 = !DILocalVariable(name: "cafirst", scope: !158, file: !1, line: 116, type: !130)
!244 = !DILocation(line: 116, column: 18, scope: !158)
!245 = !DILocalVariable(name: "calast", scope: !158, file: !1, line: 117, type: !130)
!246 = !DILocation(line: 117, column: 18, scope: !158)
!247 = !DILocalVariable(name: "ca", scope: !158, file: !1, line: 118, type: !130)
!248 = !DILocation(line: 118, column: 18, scope: !158)
!249 = !DILocalVariable(name: "ss_size", scope: !158, file: !1, line: 119, type: !114)
!250 = !DILocation(line: 119, column: 10, scope: !158)
!251 = !DILocalVariable(name: "error", scope: !158, file: !1, line: 120, type: !136)
!252 = !DILocation(line: 120, column: 7, scope: !158)
!253 = !DILocation(line: 122, column: 4, scope: !158)
!254 = !DILocation(line: 122, column: 11, scope: !158)
!255 = !DILocation(line: 124, column: 23, scope: !158)
!256 = !DILocation(line: 124, column: 33, scope: !158)
!257 = !DILocation(line: 124, column: 43, scope: !158)
!258 = !DILocation(line: 124, column: 11, scope: !158)
!259 = !DILocation(line: 124, column: 9, scope: !158)
!260 = !DILocation(line: 125, column: 6, scope: !261)
!261 = distinct !DILexicalBlock(scope: !158, file: !1, line: 125, column: 6)
!262 = !DILocation(line: 125, column: 6, scope: !158)
!263 = !DILocation(line: 126, column: 12, scope: !261)
!264 = !DILocation(line: 126, column: 5, scope: !261)
!265 = !DILocation(line: 130, column: 12, scope: !266)
!266 = distinct !DILexicalBlock(scope: !158, file: !1, line: 130, column: 3)
!267 = !DILocation(line: 130, column: 10, scope: !266)
!268 = !DILocation(line: 130, column: 7, scope: !266)
!269 = !DILocation(line: 130, column: 20, scope: !270)
!270 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 1)
!271 = distinct !DILexicalBlock(scope: !266, file: !1, line: 130, column: 3)
!272 = !DILocation(line: 130, column: 23, scope: !270)
!273 = !DILocation(line: 130, column: 3, scope: !270)
!274 = !DILocation(line: 134, column: 8, scope: !275)
!275 = distinct !DILexicalBlock(scope: !276, file: !1, line: 134, column: 8)
!276 = distinct !DILexicalBlock(scope: !271, file: !1, line: 130, column: 50)
!277 = !DILocation(line: 134, column: 12, scope: !275)
!278 = !DILocation(line: 134, column: 22, scope: !275)
!279 = !DILocation(line: 134, column: 8, scope: !276)
!280 = !DILocation(line: 135, column: 15, scope: !275)
!281 = !DILocation(line: 135, column: 7, scope: !275)
!282 = !DILocation(line: 141, column: 7, scope: !275)
!283 = !DILocation(line: 144, column: 9, scope: !284)
!284 = distinct !DILexicalBlock(scope: !276, file: !1, line: 144, column: 8)
!285 = !DILocation(line: 144, column: 13, scope: !284)
!286 = !DILocation(line: 144, column: 21, scope: !284)
!287 = !DILocation(line: 144, column: 30, scope: !284)
!288 = !DILocation(line: 144, column: 35, scope: !289)
!289 = !DILexicalBlockFile(scope: !284, file: !1, discriminator: 1)
!290 = !DILocation(line: 144, column: 39, scope: !289)
!291 = !DILocation(line: 144, column: 50, scope: !289)
!292 = !DILocation(line: 144, column: 8, scope: !289)
!293 = !DILocation(line: 145, column: 7, scope: !284)
!294 = !DILocation(line: 148, column: 16, scope: !295)
!295 = distinct !DILexicalBlock(scope: !276, file: !1, line: 148, column: 8)
!296 = !DILocation(line: 148, column: 20, scope: !295)
!297 = !DILocation(line: 148, column: 8, scope: !295)
!298 = !DILocation(line: 148, column: 33, scope: !295)
!299 = !DILocation(line: 148, column: 31, scope: !295)
!300 = !DILocation(line: 148, column: 8, scope: !276)
!301 = !DILocation(line: 149, column: 7, scope: !295)
!302 = !DILocation(line: 151, column: 10, scope: !276)
!303 = !DILocation(line: 151, column: 8, scope: !276)
!304 = !DILocation(line: 152, column: 9, scope: !305)
!305 = distinct !DILexicalBlock(scope: !276, file: !1, line: 152, column: 8)
!306 = !DILocation(line: 152, column: 8, scope: !276)
!307 = !DILocation(line: 153, column: 13, scope: !308)
!308 = distinct !DILexicalBlock(scope: !305, file: !1, line: 152, column: 13)
!309 = !DILocation(line: 154, column: 7, scope: !308)
!310 = !DILocation(line: 160, column: 24, scope: !276)
!311 = !DILocation(line: 160, column: 28, scope: !276)
!312 = !DILocation(line: 160, column: 5, scope: !276)
!313 = !DILocation(line: 160, column: 9, scope: !276)
!314 = !DILocation(line: 160, column: 22, scope: !276)
!315 = !DILocation(line: 161, column: 24, scope: !276)
!316 = !DILocation(line: 161, column: 28, scope: !276)
!317 = !DILocation(line: 161, column: 5, scope: !276)
!318 = !DILocation(line: 161, column: 9, scope: !276)
!319 = !DILocation(line: 161, column: 22, scope: !276)
!320 = !DILocation(line: 162, column: 24, scope: !276)
!321 = !DILocation(line: 162, column: 28, scope: !276)
!322 = !DILocation(line: 162, column: 5, scope: !276)
!323 = !DILocation(line: 162, column: 9, scope: !276)
!324 = !DILocation(line: 162, column: 22, scope: !276)
!325 = !DILocation(line: 163, column: 24, scope: !276)
!326 = !DILocation(line: 163, column: 28, scope: !276)
!327 = !DILocation(line: 163, column: 5, scope: !276)
!328 = !DILocation(line: 163, column: 9, scope: !276)
!329 = !DILocation(line: 163, column: 22, scope: !276)
!330 = !DILocation(line: 164, column: 40, scope: !276)
!331 = !DILocation(line: 164, column: 24, scope: !276)
!332 = !DILocation(line: 164, column: 5, scope: !276)
!333 = !DILocation(line: 164, column: 9, scope: !276)
!334 = !DILocation(line: 164, column: 22, scope: !276)
!335 = !DILocation(line: 165, column: 5, scope: !276)
!336 = !DILocation(line: 165, column: 9, scope: !276)
!337 = !DILocation(line: 165, column: 22, scope: !276)
!338 = !DILocation(line: 166, column: 5, scope: !276)
!339 = !DILocation(line: 166, column: 9, scope: !276)
!340 = !DILocation(line: 166, column: 22, scope: !276)
!341 = !DILocation(line: 167, column: 5, scope: !276)
!342 = !DILocation(line: 167, column: 9, scope: !276)
!343 = !DILocation(line: 167, column: 22, scope: !276)
!344 = !DILocation(line: 169, column: 19, scope: !276)
!345 = !DILocation(line: 169, column: 5, scope: !276)
!346 = !DILocation(line: 169, column: 9, scope: !276)
!347 = !DILocation(line: 169, column: 17, scope: !276)
!348 = !DILocation(line: 170, column: 9, scope: !349)
!349 = distinct !DILexicalBlock(scope: !276, file: !1, line: 170, column: 8)
!350 = !DILocation(line: 170, column: 13, scope: !349)
!351 = !DILocation(line: 170, column: 8, scope: !276)
!352 = !DILocation(line: 171, column: 13, scope: !353)
!353 = distinct !DILexicalBlock(scope: !349, file: !1, line: 170, column: 22)
!354 = !DILocation(line: 172, column: 7, scope: !353)
!355 = !DILocation(line: 173, column: 7, scope: !353)
!356 = !DILocation(line: 175, column: 12, scope: !276)
!357 = !DILocation(line: 175, column: 16, scope: !276)
!358 = !DILocation(line: 175, column: 5, scope: !276)
!359 = !DILocation(line: 175, column: 25, scope: !276)
!360 = !DILocation(line: 175, column: 29, scope: !276)
!361 = !DILocation(line: 175, column: 38, scope: !276)
!362 = !DILocation(line: 177, column: 8, scope: !363)
!363 = distinct !DILexicalBlock(scope: !276, file: !1, line: 177, column: 8)
!364 = !DILocation(line: 177, column: 12, scope: !363)
!365 = !DILocation(line: 177, column: 25, scope: !363)
!366 = !DILocation(line: 177, column: 8, scope: !276)
!367 = !DILocation(line: 178, column: 26, scope: !368)
!368 = distinct !DILexicalBlock(scope: !363, file: !1, line: 177, column: 34)
!369 = !DILocation(line: 178, column: 7, scope: !368)
!370 = !DILocation(line: 178, column: 11, scope: !368)
!371 = !DILocation(line: 178, column: 24, scope: !368)
!372 = !DILocation(line: 179, column: 11, scope: !373)
!373 = distinct !DILexicalBlock(scope: !368, file: !1, line: 179, column: 10)
!374 = !DILocation(line: 179, column: 15, scope: !373)
!375 = !DILocation(line: 179, column: 10, scope: !368)
!376 = !DILocation(line: 180, column: 15, scope: !377)
!377 = distinct !DILexicalBlock(scope: !373, file: !1, line: 179, column: 29)
!378 = !DILocation(line: 181, column: 9, scope: !377)
!379 = !DILocation(line: 182, column: 9, scope: !377)
!380 = !DILocation(line: 183, column: 9, scope: !377)
!381 = !DILocation(line: 185, column: 5, scope: !368)
!382 = !DILocation(line: 188, column: 9, scope: !383)
!383 = distinct !DILexicalBlock(scope: !276, file: !1, line: 188, column: 8)
!384 = !DILocation(line: 188, column: 8, scope: !276)
!385 = !DILocation(line: 189, column: 17, scope: !383)
!386 = !DILocation(line: 189, column: 15, scope: !383)
!387 = !DILocation(line: 189, column: 7, scope: !383)
!388 = !DILocation(line: 192, column: 8, scope: !389)
!389 = distinct !DILexicalBlock(scope: !276, file: !1, line: 192, column: 8)
!390 = !DILocation(line: 192, column: 8, scope: !276)
!391 = !DILocation(line: 193, column: 25, scope: !389)
!392 = !DILocation(line: 193, column: 7, scope: !389)
!393 = !DILocation(line: 193, column: 15, scope: !389)
!394 = !DILocation(line: 193, column: 23, scope: !389)
!395 = !DILocation(line: 194, column: 14, scope: !276)
!396 = !DILocation(line: 194, column: 12, scope: !276)
!397 = !DILocation(line: 196, column: 3, scope: !276)
!398 = !DILocation(line: 130, column: 37, scope: !399)
!399 = !DILexicalBlockFile(scope: !271, file: !1, discriminator: 2)
!400 = !DILocation(line: 130, column: 41, scope: !399)
!401 = !DILocation(line: 130, column: 35, scope: !399)
!402 = !DILocation(line: 130, column: 3, scope: !399)
!403 = !DILocation(line: 199, column: 6, scope: !404)
!404 = distinct !DILexicalBlock(scope: !158, file: !1, line: 199, column: 6)
!405 = !DILocation(line: 199, column: 6, scope: !158)
!406 = !DILocation(line: 200, column: 18, scope: !404)
!407 = !DILocation(line: 200, column: 5, scope: !404)
!408 = !DILocation(line: 203, column: 6, scope: !409)
!409 = distinct !DILexicalBlock(scope: !158, file: !1, line: 203, column: 6)
!410 = !DILocation(line: 203, column: 6, scope: !158)
!411 = !DILocation(line: 204, column: 23, scope: !412)
!412 = distinct !DILexicalBlock(scope: !409, file: !1, line: 203, column: 13)
!413 = !DILocation(line: 204, column: 5, scope: !412)
!414 = !DILocation(line: 205, column: 13, scope: !412)
!415 = !DILocation(line: 206, column: 3, scope: !412)
!416 = !DILocation(line: 207, column: 12, scope: !417)
!417 = distinct !DILexicalBlock(scope: !409, file: !1, line: 207, column: 11)
!418 = !DILocation(line: 207, column: 11, scope: !409)
!419 = !DILocation(line: 210, column: 11, scope: !420)
!420 = distinct !DILexicalBlock(scope: !417, file: !1, line: 207, column: 21)
!421 = !DILocation(line: 218, column: 3, scope: !420)
!422 = !DILocation(line: 220, column: 13, scope: !158)
!423 = !DILocation(line: 220, column: 4, scope: !158)
!424 = !DILocation(line: 220, column: 11, scope: !158)
!425 = !DILocation(line: 223, column: 10, scope: !158)
!426 = !DILocation(line: 223, column: 3, scope: !158)
!427 = !DILocation(line: 224, column: 1, scope: !158)
!428 = !DILocalVariable(name: "he", arg: 1, scope: !178, file: !1, line: 270, type: !181)
!429 = !DILocation(line: 270, column: 34, scope: !178)
!430 = !DILocalVariable(name: "port", arg: 2, scope: !178, file: !1, line: 270, type: !136)
!431 = !DILocation(line: 270, column: 42, scope: !178)
!432 = !DILocalVariable(name: "ai", scope: !178, file: !1, line: 272, type: !130)
!433 = !DILocation(line: 272, column: 18, scope: !178)
!434 = !DILocalVariable(name: "prevai", scope: !178, file: !1, line: 273, type: !130)
!435 = !DILocation(line: 273, column: 18, scope: !178)
!436 = !DILocalVariable(name: "firstai", scope: !178, file: !1, line: 274, type: !130)
!437 = !DILocation(line: 274, column: 18, scope: !178)
!438 = !DILocalVariable(name: "addr", scope: !178, file: !1, line: 275, type: !439)
!439 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !440, size: 64, align: 64)
!440 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_in", file: !441, line: 237, size: 128, align: 32, elements: !442)
!441 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!442 = !{!443, !444, !448, !454}
!443 = !DIDerivedType(tag: DW_TAG_member, name: "sin_family", scope: !440, file: !441, line: 239, baseType: !149, size: 16, align: 16)
!444 = !DIDerivedType(tag: DW_TAG_member, name: "sin_port", scope: !440, file: !441, line: 240, baseType: !445, size: 16, align: 16, offset: 16)
!445 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_port_t", file: !441, line: 117, baseType: !446)
!446 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint16_t", file: !447, line: 49, baseType: !124)
!447 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmcurl/lib")
!448 = !DIDerivedType(tag: DW_TAG_member, name: "sin_addr", scope: !440, file: !441, line: 241, baseType: !449, size: 32, align: 32, offset: 32)
!449 = !DICompositeType(tag: DW_TAG_structure_type, name: "in_addr", file: !441, line: 31, size: 32, align: 32, elements: !450)
!450 = !{!451}
!451 = !DIDerivedType(tag: DW_TAG_member, name: "s_addr", scope: !449, file: !441, line: 33, baseType: !452, size: 32, align: 32)
!452 = !DIDerivedType(tag: DW_TAG_typedef, name: "in_addr_t", file: !441, line: 30, baseType: !453)
!453 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint32_t", file: !447, line: 51, baseType: !123)
!454 = !DIDerivedType(tag: DW_TAG_member, name: "sin_zero", scope: !440, file: !441, line: 244, baseType: !455, size: 64, align: 8, offset: 64)
!455 = !DICompositeType(tag: DW_TAG_array_type, baseType: !456, size: 64, align: 8, elements: !457)
!456 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!457 = !{!458}
!458 = !DISubrange(count: 8)
!459 = !DILocation(line: 275, column: 23, scope: !178)
!460 = !DILocalVariable(name: "result", scope: !178, file: !1, line: 279, type: !461)
!461 = !DIDerivedType(tag: DW_TAG_typedef, name: "CURLcode", file: !4, line: 561, baseType: !3)
!462 = !DILocation(line: 279, column: 12, scope: !178)
!463 = !DILocalVariable(name: "i", scope: !178, file: !1, line: 280, type: !136)
!464 = !DILocation(line: 280, column: 7, scope: !178)
!465 = !DILocalVariable(name: "curr", scope: !178, file: !1, line: 281, type: !142)
!466 = !DILocation(line: 281, column: 9, scope: !178)
!467 = !DILocation(line: 283, column: 7, scope: !468)
!468 = distinct !DILexicalBlock(scope: !178, file: !1, line: 283, column: 6)
!469 = !DILocation(line: 283, column: 6, scope: !178)
!470 = !DILocation(line: 285, column: 5, scope: !468)
!471 = !DILocation(line: 287, column: 3, scope: !178)
!472 = !DILocation(line: 287, column: 3, scope: !473)
!473 = !DILexicalBlockFile(scope: !474, file: !1, discriminator: 1)
!474 = distinct !DILexicalBlock(scope: !178, file: !1, line: 287, column: 3)
!475 = !DILocation(line: 289, column: 8, scope: !476)
!476 = distinct !DILexicalBlock(scope: !178, file: !1, line: 289, column: 3)
!477 = !DILocation(line: 289, column: 7, scope: !476)
!478 = !DILocation(line: 289, column: 36, scope: !479)
!479 = !DILexicalBlockFile(scope: !480, file: !1, discriminator: 1)
!480 = distinct !DILexicalBlock(scope: !476, file: !1, line: 289, column: 3)
!481 = !DILocation(line: 289, column: 20, scope: !479)
!482 = !DILocation(line: 289, column: 24, scope: !479)
!483 = !DILocation(line: 289, column: 18, scope: !479)
!484 = !DILocation(line: 289, column: 40, scope: !479)
!485 = !DILocation(line: 289, column: 3, scope: !479)
!486 = !DILocalVariable(name: "ss_size", scope: !487, file: !1, line: 291, type: !114)
!487 = distinct !DILexicalBlock(scope: !480, file: !1, line: 289, column: 54)
!488 = !DILocation(line: 291, column: 12, scope: !487)
!489 = !DILocation(line: 297, column: 15, scope: !487)
!490 = !DILocation(line: 299, column: 10, scope: !487)
!491 = !DILocation(line: 299, column: 8, scope: !487)
!492 = !DILocation(line: 300, column: 9, scope: !493)
!493 = distinct !DILexicalBlock(scope: !487, file: !1, line: 300, column: 8)
!494 = !DILocation(line: 300, column: 8, scope: !487)
!495 = !DILocation(line: 301, column: 14, scope: !496)
!496 = distinct !DILexicalBlock(scope: !493, file: !1, line: 300, column: 13)
!497 = !DILocation(line: 302, column: 7, scope: !496)
!498 = !DILocation(line: 304, column: 24, scope: !487)
!499 = !DILocation(line: 304, column: 5, scope: !487)
!500 = !DILocation(line: 304, column: 9, scope: !487)
!501 = !DILocation(line: 304, column: 22, scope: !487)
!502 = !DILocation(line: 305, column: 9, scope: !503)
!503 = distinct !DILexicalBlock(scope: !487, file: !1, line: 305, column: 8)
!504 = !DILocation(line: 305, column: 13, scope: !503)
!505 = !DILocation(line: 305, column: 8, scope: !487)
!506 = !DILocation(line: 306, column: 14, scope: !507)
!507 = distinct !DILexicalBlock(scope: !503, file: !1, line: 305, column: 27)
!508 = !DILocation(line: 307, column: 7, scope: !507)
!509 = !DILocation(line: 308, column: 7, scope: !507)
!510 = !DILocation(line: 310, column: 19, scope: !487)
!511 = !DILocation(line: 310, column: 5, scope: !487)
!512 = !DILocation(line: 310, column: 9, scope: !487)
!513 = !DILocation(line: 310, column: 17, scope: !487)
!514 = !DILocation(line: 311, column: 9, scope: !515)
!515 = distinct !DILexicalBlock(scope: !487, file: !1, line: 311, column: 8)
!516 = !DILocation(line: 311, column: 13, scope: !515)
!517 = !DILocation(line: 311, column: 8, scope: !487)
!518 = !DILocation(line: 312, column: 14, scope: !519)
!519 = distinct !DILexicalBlock(scope: !515, file: !1, line: 311, column: 22)
!520 = !DILocation(line: 313, column: 7, scope: !519)
!521 = !DILocation(line: 314, column: 7, scope: !519)
!522 = !DILocation(line: 315, column: 7, scope: !519)
!523 = !DILocation(line: 318, column: 9, scope: !524)
!524 = distinct !DILexicalBlock(scope: !487, file: !1, line: 318, column: 8)
!525 = !DILocation(line: 318, column: 8, scope: !487)
!526 = !DILocation(line: 320, column: 17, scope: !524)
!527 = !DILocation(line: 320, column: 15, scope: !524)
!528 = !DILocation(line: 320, column: 7, scope: !524)
!529 = !DILocation(line: 322, column: 8, scope: !530)
!530 = distinct !DILexicalBlock(scope: !487, file: !1, line: 322, column: 8)
!531 = !DILocation(line: 322, column: 8, scope: !487)
!532 = !DILocation(line: 324, column: 25, scope: !530)
!533 = !DILocation(line: 324, column: 7, scope: !530)
!534 = !DILocation(line: 324, column: 15, scope: !530)
!535 = !DILocation(line: 324, column: 23, scope: !530)
!536 = !DILocation(line: 326, column: 21, scope: !487)
!537 = !DILocation(line: 326, column: 25, scope: !487)
!538 = !DILocation(line: 326, column: 5, scope: !487)
!539 = !DILocation(line: 326, column: 9, scope: !487)
!540 = !DILocation(line: 326, column: 19, scope: !487)
!541 = !DILocation(line: 330, column: 5, scope: !487)
!542 = !DILocation(line: 330, column: 9, scope: !487)
!543 = !DILocation(line: 330, column: 21, scope: !487)
!544 = !DILocation(line: 332, column: 38, scope: !487)
!545 = !DILocation(line: 332, column: 22, scope: !487)
!546 = !DILocation(line: 332, column: 5, scope: !487)
!547 = !DILocation(line: 332, column: 9, scope: !487)
!548 = !DILocation(line: 332, column: 20, scope: !487)
!549 = !DILocation(line: 336, column: 12, scope: !487)
!550 = !DILocation(line: 336, column: 16, scope: !487)
!551 = !DILocation(line: 336, column: 5, scope: !487)
!552 = !DILocation(line: 338, column: 22, scope: !553)
!553 = distinct !DILexicalBlock(scope: !487, file: !1, line: 336, column: 27)
!554 = !DILocation(line: 338, column: 26, scope: !553)
!555 = !DILocation(line: 338, column: 14, scope: !553)
!556 = !DILocation(line: 338, column: 12, scope: !553)
!557 = !DILocation(line: 340, column: 15, scope: !553)
!558 = !DILocation(line: 340, column: 21, scope: !553)
!559 = !DILocation(line: 340, column: 7, scope: !553)
!560 = !DILocation(line: 340, column: 31, scope: !553)
!561 = !DILocation(line: 341, column: 43, scope: !553)
!562 = !DILocation(line: 341, column: 47, scope: !553)
!563 = !DILocation(line: 341, column: 26, scope: !553)
!564 = !DILocation(line: 341, column: 7, scope: !553)
!565 = !DILocation(line: 341, column: 13, scope: !553)
!566 = !DILocation(line: 341, column: 24, scope: !553)
!567 = !DILocation(line: 342, column: 46, scope: !553)
!568 = !DILocation(line: 342, column: 30, scope: !553)
!569 = !DILocation(line: 342, column: 24, scope: !553)
!570 = !DILocation(line: 342, column: 7, scope: !553)
!571 = !DILocation(line: 342, column: 13, scope: !553)
!572 = !DILocation(line: 342, column: 22, scope: !553)
!573 = !DILocation(line: 343, column: 7, scope: !553)
!574 = !DILocation(line: 356, column: 14, scope: !487)
!575 = !DILocation(line: 356, column: 12, scope: !487)
!576 = !DILocation(line: 357, column: 3, scope: !487)
!577 = !DILocation(line: 289, column: 50, scope: !578)
!578 = !DILexicalBlockFile(scope: !480, file: !1, discriminator: 2)
!579 = !DILocation(line: 289, column: 3, scope: !578)
!580 = !DILocation(line: 359, column: 6, scope: !581)
!581 = distinct !DILexicalBlock(scope: !178, file: !1, line: 359, column: 6)
!582 = !DILocation(line: 359, column: 6, scope: !178)
!583 = !DILocation(line: 360, column: 23, scope: !584)
!584 = distinct !DILexicalBlock(scope: !581, file: !1, line: 359, column: 14)
!585 = !DILocation(line: 360, column: 5, scope: !584)
!586 = !DILocation(line: 361, column: 13, scope: !584)
!587 = !DILocation(line: 362, column: 3, scope: !584)
!588 = !DILocation(line: 364, column: 10, scope: !178)
!589 = !DILocation(line: 364, column: 3, scope: !178)
!590 = !DILocation(line: 365, column: 1, scope: !178)
!591 = !DILocalVariable(name: "af", arg: 1, scope: !191, file: !1, line: 390, type: !136)
!592 = !DILocation(line: 390, column: 18, scope: !191)
!593 = !DILocalVariable(name: "inaddr", arg: 2, scope: !191, file: !1, line: 390, type: !194)
!594 = !DILocation(line: 390, column: 34, scope: !191)
!595 = !DILocalVariable(name: "hostname", arg: 3, scope: !191, file: !1, line: 390, type: !161)
!596 = !DILocation(line: 390, column: 54, scope: !191)
!597 = !DILocalVariable(name: "port", arg: 4, scope: !191, file: !1, line: 390, type: !136)
!598 = !DILocation(line: 390, column: 68, scope: !191)
!599 = !DILocalVariable(name: "ai", scope: !191, file: !1, line: 392, type: !130)
!600 = !DILocation(line: 392, column: 18, scope: !191)
!601 = !DILocalVariable(name: "h", scope: !191, file: !1, line: 401, type: !602)
!602 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !183, size: 64, align: 64)
!603 = !DILocation(line: 401, column: 20, scope: !191)
!604 = !DILocalVariable(name: "buf", scope: !191, file: !1, line: 402, type: !605)
!605 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !606, size: 64, align: 64)
!606 = !DICompositeType(tag: DW_TAG_structure_type, name: "namebuff", file: !1, line: 368, size: 448, align: 64, elements: !607)
!607 = !{!608, !609, !613}
!608 = !DIDerivedType(tag: DW_TAG_member, name: "hostentry", scope: !606, file: !1, line: 369, baseType: !183, size: 256, align: 64)
!609 = !DIDerivedType(tag: DW_TAG_member, name: "addrentry", scope: !606, file: !1, line: 375, baseType: !610, size: 32, align: 32, offset: 256)
!610 = !DICompositeType(tag: DW_TAG_union_type, scope: !606, file: !1, line: 370, size: 32, align: 32, elements: !611)
!611 = !{!612}
!612 = !DIDerivedType(tag: DW_TAG_member, name: "ina4", scope: !610, file: !1, line: 371, baseType: !449, size: 32, align: 32)
!613 = !DIDerivedType(tag: DW_TAG_member, name: "h_addr_list", scope: !606, file: !1, line: 376, baseType: !614, size: 128, align: 64, offset: 320)
!614 = !DICompositeType(tag: DW_TAG_array_type, baseType: !142, size: 128, align: 64, elements: !615)
!615 = !{!616}
!616 = !DISubrange(count: 2)
!617 = !DILocation(line: 402, column: 20, scope: !191)
!618 = !DILocalVariable(name: "addrentry", scope: !191, file: !1, line: 403, type: !142)
!619 = !DILocation(line: 403, column: 10, scope: !191)
!620 = !DILocalVariable(name: "hoststr", scope: !191, file: !1, line: 404, type: !142)
!621 = !DILocation(line: 404, column: 10, scope: !191)
!622 = !DILocalVariable(name: "addrsize", scope: !191, file: !1, line: 405, type: !114)
!623 = !DILocation(line: 405, column: 10, scope: !191)
!624 = !DILocation(line: 407, column: 3, scope: !191)
!625 = !DILocation(line: 407, column: 3, scope: !626)
!626 = !DILexicalBlockFile(scope: !627, file: !1, discriminator: 1)
!627 = distinct !DILexicalBlock(scope: !191, file: !1, line: 407, column: 3)
!628 = !DILocation(line: 409, column: 9, scope: !191)
!629 = !DILocation(line: 409, column: 7, scope: !191)
!630 = !DILocation(line: 410, column: 7, scope: !631)
!631 = distinct !DILexicalBlock(scope: !191, file: !1, line: 410, column: 6)
!632 = !DILocation(line: 410, column: 6, scope: !191)
!633 = !DILocation(line: 411, column: 5, scope: !631)
!634 = !DILocation(line: 413, column: 13, scope: !191)
!635 = !DILocation(line: 413, column: 11, scope: !191)
!636 = !DILocation(line: 414, column: 7, scope: !637)
!637 = distinct !DILexicalBlock(scope: !191, file: !1, line: 414, column: 6)
!638 = !DILocation(line: 414, column: 6, scope: !191)
!639 = !DILocation(line: 415, column: 5, scope: !640)
!640 = distinct !DILexicalBlock(scope: !637, file: !1, line: 414, column: 16)
!641 = !DILocation(line: 416, column: 5, scope: !640)
!642 = !DILocation(line: 419, column: 10, scope: !191)
!643 = !DILocation(line: 419, column: 3, scope: !191)
!644 = !DILocation(line: 421, column: 14, scope: !645)
!645 = distinct !DILexicalBlock(scope: !191, file: !1, line: 419, column: 14)
!646 = !DILocation(line: 422, column: 26, scope: !645)
!647 = !DILocation(line: 422, column: 31, scope: !645)
!648 = !DILocation(line: 422, column: 41, scope: !645)
!649 = !DILocation(line: 422, column: 17, scope: !645)
!650 = !DILocation(line: 422, column: 15, scope: !645)
!651 = !DILocation(line: 423, column: 12, scope: !645)
!652 = !DILocation(line: 423, column: 23, scope: !645)
!653 = !DILocation(line: 423, column: 5, scope: !645)
!654 = !DILocation(line: 424, column: 5, scope: !645)
!655 = !DILocation(line: 433, column: 5, scope: !645)
!656 = !DILocation(line: 434, column: 5, scope: !645)
!657 = !DILocation(line: 435, column: 5, scope: !645)
!658 = !DILocation(line: 438, column: 8, scope: !191)
!659 = !DILocation(line: 438, column: 13, scope: !191)
!660 = !DILocation(line: 438, column: 5, scope: !191)
!661 = !DILocation(line: 439, column: 15, scope: !191)
!662 = !DILocation(line: 439, column: 3, scope: !191)
!663 = !DILocation(line: 439, column: 6, scope: !191)
!664 = !DILocation(line: 439, column: 13, scope: !191)
!665 = !DILocation(line: 440, column: 3, scope: !191)
!666 = !DILocation(line: 440, column: 6, scope: !191)
!667 = !DILocation(line: 440, column: 16, scope: !191)
!668 = !DILocation(line: 441, column: 26, scope: !191)
!669 = !DILocation(line: 441, column: 19, scope: !191)
!670 = !DILocation(line: 441, column: 3, scope: !191)
!671 = !DILocation(line: 441, column: 6, scope: !191)
!672 = !DILocation(line: 441, column: 17, scope: !191)
!673 = !DILocation(line: 442, column: 24, scope: !191)
!674 = !DILocation(line: 442, column: 17, scope: !191)
!675 = !DILocation(line: 442, column: 3, scope: !191)
!676 = !DILocation(line: 442, column: 6, scope: !191)
!677 = !DILocation(line: 442, column: 15, scope: !191)
!678 = !DILocation(line: 443, column: 21, scope: !191)
!679 = !DILocation(line: 443, column: 26, scope: !191)
!680 = !DILocation(line: 443, column: 3, scope: !191)
!681 = !DILocation(line: 443, column: 6, scope: !191)
!682 = !DILocation(line: 443, column: 18, scope: !191)
!683 = !DILocation(line: 444, column: 23, scope: !191)
!684 = !DILocation(line: 444, column: 3, scope: !191)
!685 = !DILocation(line: 444, column: 6, scope: !191)
!686 = !DILocation(line: 444, column: 21, scope: !191)
!687 = !DILocation(line: 445, column: 3, scope: !191)
!688 = !DILocation(line: 445, column: 6, scope: !191)
!689 = !DILocation(line: 445, column: 21, scope: !191)
!690 = !DILocation(line: 453, column: 19, scope: !191)
!691 = !DILocation(line: 453, column: 22, scope: !191)
!692 = !DILocation(line: 453, column: 8, scope: !191)
!693 = !DILocation(line: 453, column: 6, scope: !191)
!694 = !DILocation(line: 455, column: 3, scope: !191)
!695 = !DILocation(line: 456, column: 3, scope: !191)
!696 = !DILocation(line: 458, column: 10, scope: !191)
!697 = !DILocation(line: 458, column: 3, scope: !191)
!698 = !DILocation(line: 459, column: 1, scope: !191)
!699 = !DILocalVariable(name: "address", arg: 1, scope: !196, file: !1, line: 465, type: !142)
!700 = !DILocation(line: 465, column: 36, scope: !196)
!701 = !DILocalVariable(name: "port", arg: 2, scope: !196, file: !1, line: 465, type: !136)
!702 = !DILocation(line: 465, column: 49, scope: !196)
!703 = !DILocalVariable(name: "in", scope: !196, file: !1, line: 467, type: !449)
!704 = !DILocation(line: 467, column: 18, scope: !196)
!705 = !DILocation(line: 468, column: 6, scope: !706)
!706 = distinct !DILexicalBlock(scope: !196, file: !1, line: 468, column: 6)
!707 = !DILocation(line: 468, column: 44, scope: !706)
!708 = !DILocation(line: 468, column: 6, scope: !196)
!709 = !DILocation(line: 470, column: 34, scope: !706)
!710 = !DILocation(line: 470, column: 39, scope: !706)
!711 = !DILocation(line: 470, column: 48, scope: !706)
!712 = !DILocation(line: 470, column: 12, scope: !706)
!713 = !DILocation(line: 470, column: 5, scope: !706)
!714 = !DILocation(line: 479, column: 3, scope: !196)
!715 = !DILocation(line: 480, column: 1, scope: !196)
