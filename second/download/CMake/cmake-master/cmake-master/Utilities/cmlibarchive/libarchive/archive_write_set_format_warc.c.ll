; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_warc.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.warc_s = type { i8, i64, i32, i32, i64 }
%struct.warc_essential_hdr_t = type { i32, i8*, i8*, i64, i64, i8*, i64 }
%struct.warc_uuid_t = type { [4 x i32] }
%struct.tm = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i64, i8* }

@.str = private unnamed_addr constant [30 x i8] c"archive_write_set_format_warc\00", align 1
@.str.1 = private unnamed_addr constant [25 x i8] c"Can't allocate warc data\00", align 1
@.str.2 = private unnamed_addr constant [9 x i8] c"WARC/1.0\00", align 1
@.str.3 = private unnamed_addr constant [14 x i8] c"omit-warcinfo\00", align 1
@.str.4 = private unnamed_addr constant [5 x i8] c"true\00", align 1
@.str.5 = private unnamed_addr constant [24 x i8] c"application/warc-fields\00", align 1
@warcinfo = internal constant [60 x i8] c"software: libarchive/3.3.1\0D\0Aformat: WARC file version 1.0\0D\0A\00", align 16
@.str.6 = private unnamed_addr constant [5 x i8] c"\0D\0A\0D\0A\00", align 1
@.str.7 = private unnamed_addr constant [17 x i8] c"Invalid filename\00", align 1
@.str.8 = private unnamed_addr constant [20 x i8] c"cannot archive file\00", align 1
@.str.9 = private unnamed_addr constant [36 x i8] c"WARC can only process regular files\00", align 1
@_popul_ehdr._ver = internal constant [11 x i8] c"WARC/1.0\0D\0A\00", align 1
@_popul_ehdr._typ = internal global [9 x i8*] [i8* null, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.12, i32 0, i32 0), i8* null, i8* null, i8* null, i8* null, i8* null], align 16
@.str.10 = private unnamed_addr constant [9 x i8] c"warcinfo\00", align 1
@.str.11 = private unnamed_addr constant [9 x i8] c"metadata\00", align 1
@.str.12 = private unnamed_addr constant [9 x i8] c"resource\00", align 1
@.str.13 = private unnamed_addr constant [16 x i8] c"WARC-Type: %s\0D\0A\00", align 1
@_popul_ehdr._uri = internal constant [1 x i8] zeroinitializer, align 1
@_popul_ehdr._fil = internal constant [8 x i8] c"file://\00", align 1
@.str.14 = private unnamed_addr constant [24 x i8] c"WARC-Target-URI: %s%s\0D\0A\00", align 1
@.str.15 = private unnamed_addr constant [32 x i8] c"WARC-Date: %Y-%m-%dT%H:%M:%SZ\0D\0A\00", align 1
@.str.16 = private unnamed_addr constant [36 x i8] c"Last-Modified: %Y-%m-%dT%H:%M:%SZ\0D\0A\00", align 1
@.str.17 = private unnamed_addr constant [40 x i8] c"<urn:uuid:%08x-%04x-%04x-%04x-%04x%08x>\00", align 1
@.str.18 = private unnamed_addr constant [21 x i8] c"WARC-Record-ID: %s\0D\0A\00", align 1
@.str.19 = private unnamed_addr constant [19 x i8] c"Content-Type: %s\0D\0A\00", align 1
@.str.20 = private unnamed_addr constant [22 x i8] c"Content-Length: %ju\0D\0A\00", align 1
@.str.21 = private unnamed_addr constant [3 x i8] c"\0D\0A\00", align 1
@_warc_finish_entry._eor = internal constant [5 x i8] c"\0D\0A\0D\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_warc(%struct.archive* %_a) #0 !dbg !209 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %w = alloca %struct.warc_s*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !278, metadata !279), !dbg !280
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !281, metadata !279), !dbg !282
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !283
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !284
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !282
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !285, metadata !279), !dbg !294
  br label %do.body, !dbg !295

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !296, metadata !279), !dbg !298
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !299
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str, i32 0, i32 0)), !dbg !299
  store i32 %call, i32* %magic_test, align 4, !dbg !299
  %3 = load i32, i32* %magic_test, align 4, !dbg !299
  %cmp = icmp eq i32 %3, -30, !dbg !299
  br i1 %cmp, label %if.then, label %if.end, !dbg !299

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !301
  br label %return, !dbg !301

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !304

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !306
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 22, !dbg !308
  %5 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !308
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %5, null, !dbg !309
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !310

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !311
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 22, !dbg !313
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !313
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !314
  %call4 = call i32 %7(%struct.archive_write* %8), !dbg !315
  br label %if.end5, !dbg !316

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @malloc(i64 32) #6, !dbg !317
  %9 = bitcast i8* %call6 to %struct.warc_s*, !dbg !317
  store %struct.warc_s* %9, %struct.warc_s** %w, align 8, !dbg !318
  %10 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !319
  %cmp7 = icmp eq %struct.warc_s* %10, null, !dbg !321
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !322

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !323
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !325
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.1, i32 0, i32 0)), !dbg !326
  store i32 -30, i32* %retval, align 4, !dbg !327
  br label %return, !dbg !327

if.end9:                                          ; preds = %if.end5
  %12 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !328
  %13 = bitcast %struct.warc_s* %12 to i8*, !dbg !329
  %bf.load = load i8, i8* %13, align 8, !dbg !330
  %bf.clear = and i8 %bf.load, -2, !dbg !330
  store i8 %bf.clear, i8* %13, align 8, !dbg !330
  %call10 = call i64 @time(i64* null) #6, !dbg !331
  %14 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !332
  %now = getelementptr inbounds %struct.warc_s, %struct.warc_s* %14, i32 0, i32 1, !dbg !333
  store i64 %call10, i64* %now, align 8, !dbg !334
  %15 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !335
  %typ = getelementptr inbounds %struct.warc_s, %struct.warc_s* %15, i32 0, i32 2, !dbg !336
  store i32 0, i32* %typ, align 8, !dbg !337
  %16 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !338
  %now11 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %16, i32 0, i32 1, !dbg !339
  %17 = load i64, i64* %now11, align 8, !dbg !339
  %conv = trunc i64 %17 to i32, !dbg !340
  %18 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !341
  %rng = getelementptr inbounds %struct.warc_s, %struct.warc_s* %18, i32 0, i32 3, !dbg !342
  store i32 %conv, i32* %rng, align 4, !dbg !343
  %19 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !344
  %20 = bitcast %struct.warc_s* %19 to i8*, !dbg !344
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !345
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 14, !dbg !346
  store i8* %20, i8** %format_data, align 8, !dbg !347
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !348
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 15, !dbg !349
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.2, i32 0, i32 0), i8** %format_name, align 8, !dbg !350
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !351
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 17, !dbg !352
  store i32 (%struct.archive_write*, i8*, i8*)* @_warc_options, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !353
  %24 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !354
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %24, i32 0, i32 19, !dbg !355
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @_warc_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !356
  %25 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !357
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %25, i32 0, i32 20, !dbg !358
  store i64 (%struct.archive_write*, i8*, i64)* @_warc_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !359
  %26 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !360
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %26, i32 0, i32 21, !dbg !361
  store i32 (%struct.archive_write*)* @_warc_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !362
  %27 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !363
  %format_free12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %27, i32 0, i32 22, !dbg !364
  store i32 (%struct.archive_write*)* @_warc_free, i32 (%struct.archive_write*)** %format_free12, align 8, !dbg !365
  %28 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !366
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %28, i32 0, i32 18, !dbg !367
  store i32 (%struct.archive_write*)* @_warc_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !368
  %29 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !369
  %archive13 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %29, i32 0, i32 0, !dbg !370
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive13, i32 0, i32 3, !dbg !371
  store i32 983040, i32* %archive_format, align 8, !dbg !372
  %30 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !373
  %archive14 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %30, i32 0, i32 0, !dbg !374
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive14, i32 0, i32 4, !dbg !375
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.2, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !376
  store i32 0, i32* %retval, align 4, !dbg !377
  br label %return, !dbg !377

return:                                           ; preds = %if.end9, %if.then8, %if.then
  %31 = load i32, i32* %retval, align 4, !dbg !378
  ret i32 %31, !dbg !378
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind
declare i64 @time(i64*) #3

; Function Attrs: nounwind uwtable
define internal i32 @_warc_options(%struct.archive_write* %a, i8* %key, i8* %val) #0 !dbg !211 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %w = alloca %struct.warc_s*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !379, metadata !279), !dbg !380
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !381, metadata !279), !dbg !382
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !383, metadata !279), !dbg !384
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !385, metadata !279), !dbg !386
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !387
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !388
  %1 = load i8*, i8** %format_data, align 8, !dbg !388
  %2 = bitcast i8* %1 to %struct.warc_s*, !dbg !387
  store %struct.warc_s* %2, %struct.warc_s** %w, align 8, !dbg !386
  %3 = load i8*, i8** %key.addr, align 8, !dbg !389
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.3, i32 0, i32 0)) #7, !dbg !391
  %cmp = icmp eq i32 %call, 0, !dbg !392
  br i1 %cmp, label %if.then, label %if.end5, !dbg !393

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %val.addr, align 8, !dbg !394
  %cmp1 = icmp eq i8* %4, null, !dbg !397
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !398

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %val.addr, align 8, !dbg !399
  %call2 = call i32 @strcmp(i8* %5, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.4, i32 0, i32 0)) #7, !dbg !401
  %cmp3 = icmp eq i32 %call2, 0, !dbg !402
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !403

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %6 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !404
  %7 = bitcast %struct.warc_s* %6 to i8*, !dbg !406
  %bf.load = load i8, i8* %7, align 8, !dbg !407
  %bf.clear = and i8 %bf.load, -2, !dbg !407
  %bf.set = or i8 %bf.clear, 1, !dbg !407
  store i8 %bf.set, i8* %7, align 8, !dbg !407
  store i32 0, i32* %retval, align 4, !dbg !408
  br label %return, !dbg !408

if.end:                                           ; preds = %lor.lhs.false
  br label %if.end5, !dbg !409

if.end5:                                          ; preds = %if.end, %entry
  store i32 -20, i32* %retval, align 4, !dbg !410
  br label %return, !dbg !410

return:                                           ; preds = %if.end5, %if.then4
  %8 = load i32, i32* %retval, align 4, !dbg !411
  ret i32 %8, !dbg !411
}

; Function Attrs: nounwind uwtable
define internal i32 @_warc_header(%struct.archive_write* %a, %struct.archive_entry* %entry1) #0 !dbg !212 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %w = alloca %struct.warc_s*, align 8
  %hdr = alloca %struct.archive_string, align 8
  %r = alloca i64, align 8
  %wi = alloca %struct.warc_essential_hdr_t, align 8
  %rh = alloca %struct.warc_essential_hdr_t, align 8
  %r20 = alloca i64, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !412, metadata !279), !dbg !413
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !414, metadata !279), !dbg !415
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !416, metadata !279), !dbg !417
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !418
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !419
  %1 = load i8*, i8** %format_data, align 8, !dbg !419
  %2 = bitcast i8* %1 to %struct.warc_s*, !dbg !418
  store %struct.warc_s* %2, %struct.warc_s** %w, align 8, !dbg !417
  call void @llvm.dbg.declare(metadata %struct.archive_string* %hdr, metadata !420, metadata !279), !dbg !421
  %3 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !422
  %4 = bitcast %struct.warc_s* %3 to i8*, !dbg !424
  %bf.load = load i8, i8* %4, align 8, !dbg !424
  %bf.clear = and i8 %bf.load, 1, !dbg !424
  %bf.cast = zext i8 %bf.clear to i32, !dbg !424
  %tobool = icmp ne i32 %bf.cast, 0, !dbg !422
  br i1 %tobool, label %if.end11, label %if.then, !dbg !425

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i64* %r, metadata !426, metadata !279), !dbg !428
  call void @llvm.dbg.declare(metadata %struct.warc_essential_hdr_t* %wi, metadata !429, metadata !279), !dbg !430
  %5 = bitcast %struct.warc_essential_hdr_t* %wi to i8*, !dbg !430
  call void @llvm.memset.p0i8.i64(i8* %5, i8 0, i64 56, i32 8, i1 false), !dbg !430
  %6 = bitcast i8* %5 to %struct.warc_essential_hdr_t*, !dbg !430
  %7 = getelementptr %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %6, i32 0, i32 0, !dbg !430
  store i32 1, i32* %7, !dbg !430
  %8 = getelementptr %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %6, i32 0, i32 5, !dbg !430
  store i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.5, i32 0, i32 0), i8** %8, !dbg !430
  %9 = getelementptr %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %6, i32 0, i32 6, !dbg !430
  store i64 59, i64* %9, !dbg !430
  %10 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !431
  %now = getelementptr inbounds %struct.warc_s, %struct.warc_s* %10, i32 0, i32 1, !dbg !432
  %11 = load i64, i64* %now, align 8, !dbg !432
  %rtime = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %wi, i32 0, i32 3, !dbg !433
  store i64 %11, i64* %rtime, align 8, !dbg !434
  %12 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !435
  %now2 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %12, i32 0, i32 1, !dbg !436
  %13 = load i64, i64* %now2, align 8, !dbg !436
  %mtime = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %wi, i32 0, i32 4, !dbg !437
  store i64 %13, i64* %mtime, align 8, !dbg !438
  br label %do.body, !dbg !439

do.body:                                          ; preds = %if.then
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %hdr, i32 0, i32 0, !dbg !440
  store i8* null, i8** %s, align 8, !dbg !440
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %hdr, i32 0, i32 1, !dbg !440
  store i64 0, i64* %length, align 8, !dbg !440
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %hdr, i32 0, i32 2, !dbg !440
  store i64 0, i64* %buffer_length, align 8, !dbg !440
  br label %do.end, !dbg !440

do.end:                                           ; preds = %do.body
  %call = call i64 @_popul_ehdr(%struct.archive_string* %hdr, i64 512, %struct.warc_essential_hdr_t* byval align 8 %wi), !dbg !443
  store i64 %call, i64* %r, align 8, !dbg !444
  %14 = load i64, i64* %r, align 8, !dbg !445
  %cmp = icmp sge i64 %14, 0, !dbg !447
  br i1 %cmp, label %if.then3, label %if.end, !dbg !448

if.then3:                                         ; preds = %do.end
  %call4 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %hdr, i8* getelementptr inbounds ([60 x i8], [60 x i8]* @warcinfo, i32 0, i32 0), i64 59), !dbg !449
  %call5 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %hdr, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.6, i32 0, i32 0), i64 4), !dbg !451
  %15 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !452
  %s6 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %hdr, i32 0, i32 0, !dbg !453
  %16 = load i8*, i8** %s6, align 8, !dbg !453
  %length7 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %hdr, i32 0, i32 1, !dbg !454
  %17 = load i64, i64* %length7, align 8, !dbg !454
  %call8 = call i32 @__archive_write_output(%struct.archive_write* %15, i8* %16, i64 %17), !dbg !455
  br label %if.end, !dbg !456

if.end:                                           ; preds = %if.then3, %do.end
  %18 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !457
  %19 = bitcast %struct.warc_s* %18 to i8*, !dbg !458
  %bf.load9 = load i8, i8* %19, align 8, !dbg !459
  %bf.clear10 = and i8 %bf.load9, -2, !dbg !459
  %bf.set = or i8 %bf.clear10, 1, !dbg !459
  store i8 %bf.set, i8* %19, align 8, !dbg !459
  call void @archive_string_free(%struct.archive_string* %hdr), !dbg !460
  br label %if.end11, !dbg !461

if.end11:                                         ; preds = %if.end, %entry
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !462
  %call12 = call i8* @archive_entry_pathname(%struct.archive_entry* %20), !dbg !464
  %cmp13 = icmp eq i8* %call12, null, !dbg !465
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !466

if.then14:                                        ; preds = %if.end11
  %21 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !467
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 0, !dbg !469
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.7, i32 0, i32 0)), !dbg !470
  store i32 -20, i32* %retval, align 4, !dbg !471
  br label %return, !dbg !471

if.end15:                                         ; preds = %if.end11
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !472
  %call16 = call i32 @archive_entry_filetype(%struct.archive_entry* %22), !dbg !473
  %23 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !474
  %typ = getelementptr inbounds %struct.warc_s, %struct.warc_s* %23, i32 0, i32 2, !dbg !475
  store i32 %call16, i32* %typ, align 8, !dbg !476
  %24 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !477
  %populz = getelementptr inbounds %struct.warc_s, %struct.warc_s* %24, i32 0, i32 4, !dbg !478
  store i64 0, i64* %populz, align 8, !dbg !479
  %25 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !480
  %typ17 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %25, i32 0, i32 2, !dbg !482
  %26 = load i32, i32* %typ17, align 8, !dbg !482
  %cmp18 = icmp eq i32 %26, 32768, !dbg !483
  br i1 %cmp18, label %if.then19, label %if.end41, !dbg !484

if.then19:                                        ; preds = %if.end15
  call void @llvm.dbg.declare(metadata %struct.warc_essential_hdr_t* %rh, metadata !485, metadata !279), !dbg !487
  %27 = bitcast %struct.warc_essential_hdr_t* %rh to i8*, !dbg !487
  call void @llvm.memset.p0i8.i64(i8* %27, i8 0, i64 56, i32 8, i1 false), !dbg !487
  %28 = bitcast i8* %27 to %struct.warc_essential_hdr_t*, !dbg !487
  %29 = getelementptr %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %28, i32 0, i32 0, !dbg !487
  store i32 3, i32* %29, !dbg !487
  call void @llvm.dbg.declare(metadata i64* %r20, metadata !488, metadata !279), !dbg !489
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !490
  %call21 = call i8* @archive_entry_pathname(%struct.archive_entry* %30), !dbg !491
  %tgturi = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %rh, i32 0, i32 1, !dbg !492
  store i8* %call21, i8** %tgturi, align 8, !dbg !493
  %31 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !494
  %now22 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %31, i32 0, i32 1, !dbg !495
  %32 = load i64, i64* %now22, align 8, !dbg !495
  %rtime23 = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %rh, i32 0, i32 3, !dbg !496
  store i64 %32, i64* %rtime23, align 8, !dbg !497
  %33 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !498
  %call24 = call i64 @archive_entry_mtime(%struct.archive_entry* %33), !dbg !499
  %mtime25 = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %rh, i32 0, i32 4, !dbg !500
  store i64 %call24, i64* %mtime25, align 8, !dbg !501
  %34 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !502
  %call26 = call i64 @archive_entry_size(%struct.archive_entry* %34), !dbg !503
  %cntlen = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %rh, i32 0, i32 6, !dbg !504
  store i64 %call26, i64* %cntlen, align 8, !dbg !505
  br label %do.body27, !dbg !506

do.body27:                                        ; preds = %if.then19
  %s28 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %hdr, i32 0, i32 0, !dbg !507
  store i8* null, i8** %s28, align 8, !dbg !507
  %length29 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %hdr, i32 0, i32 1, !dbg !507
  store i64 0, i64* %length29, align 8, !dbg !507
  %buffer_length30 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %hdr, i32 0, i32 2, !dbg !507
  store i64 0, i64* %buffer_length30, align 8, !dbg !507
  br label %do.end31, !dbg !507

do.end31:                                         ; preds = %do.body27
  %call32 = call i64 @_popul_ehdr(%struct.archive_string* %hdr, i64 512, %struct.warc_essential_hdr_t* byval align 8 %rh), !dbg !510
  store i64 %call32, i64* %r20, align 8, !dbg !511
  %35 = load i64, i64* %r20, align 8, !dbg !512
  %cmp33 = icmp slt i64 %35, 0, !dbg !514
  br i1 %cmp33, label %if.then34, label %if.end36, !dbg !515

if.then34:                                        ; preds = %do.end31
  %36 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !516
  %archive35 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %36, i32 0, i32 0, !dbg !518
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive35, i32 84, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.8, i32 0, i32 0)), !dbg !519
  store i32 -20, i32* %retval, align 4, !dbg !520
  br label %return, !dbg !520

if.end36:                                         ; preds = %do.end31
  %37 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !521
  %s37 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %hdr, i32 0, i32 0, !dbg !522
  %38 = load i8*, i8** %s37, align 8, !dbg !522
  %39 = load i64, i64* %r20, align 8, !dbg !523
  %call38 = call i32 @__archive_write_output(%struct.archive_write* %37, i8* %38, i64 %39), !dbg !524
  %cntlen39 = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %rh, i32 0, i32 6, !dbg !525
  %40 = load i64, i64* %cntlen39, align 8, !dbg !525
  %41 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !526
  %populz40 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %41, i32 0, i32 4, !dbg !527
  store i64 %40, i64* %populz40, align 8, !dbg !528
  call void @archive_string_free(%struct.archive_string* %hdr), !dbg !529
  store i32 0, i32* %retval, align 4, !dbg !530
  br label %return, !dbg !530

if.end41:                                         ; preds = %if.end15
  %42 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !531
  %archive42 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %42, i32 0, i32 0, !dbg !532
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive42, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.9, i32 0, i32 0)), !dbg !533
  store i32 -25, i32* %retval, align 4, !dbg !534
  br label %return, !dbg !534

return:                                           ; preds = %if.end41, %if.end36, %if.then34, %if.then14
  %43 = load i32, i32* %retval, align 4, !dbg !535
  ret i32 %43, !dbg !535
}

; Function Attrs: nounwind uwtable
define internal i64 @_warc_data(%struct.archive_write* %a, i8* %buf, i64 %len) #0 !dbg !246 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buf.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %w = alloca %struct.warc_s*, align 8
  %rc = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !536, metadata !279), !dbg !537
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !538, metadata !279), !dbg !539
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !540, metadata !279), !dbg !541
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !542, metadata !279), !dbg !543
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !544
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !545
  %1 = load i8*, i8** %format_data, align 8, !dbg !545
  %2 = bitcast i8* %1 to %struct.warc_s*, !dbg !544
  store %struct.warc_s* %2, %struct.warc_s** %w, align 8, !dbg !543
  %3 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !546
  %typ = getelementptr inbounds %struct.warc_s, %struct.warc_s* %3, i32 0, i32 2, !dbg !548
  %4 = load i32, i32* %typ, align 8, !dbg !548
  %cmp = icmp eq i32 %4, 32768, !dbg !549
  br i1 %cmp, label %if.then, label %if.end7, !dbg !550

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !551, metadata !279), !dbg !553
  %5 = load i64, i64* %len.addr, align 8, !dbg !554
  %6 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !556
  %populz = getelementptr inbounds %struct.warc_s, %struct.warc_s* %6, i32 0, i32 4, !dbg !557
  %7 = load i64, i64* %populz, align 8, !dbg !557
  %cmp1 = icmp ugt i64 %5, %7, !dbg !558
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !559

if.then2:                                         ; preds = %if.then
  %8 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !560
  %populz3 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %8, i32 0, i32 4, !dbg !562
  %9 = load i64, i64* %populz3, align 8, !dbg !562
  store i64 %9, i64* %len.addr, align 8, !dbg !563
  br label %if.end, !dbg !564

if.end:                                           ; preds = %if.then2, %if.then
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !565
  %11 = load i8*, i8** %buf.addr, align 8, !dbg !566
  %12 = load i64, i64* %len.addr, align 8, !dbg !567
  %call = call i32 @__archive_write_output(%struct.archive_write* %10, i8* %11, i64 %12), !dbg !568
  store i32 %call, i32* %rc, align 4, !dbg !569
  %13 = load i32, i32* %rc, align 4, !dbg !570
  %cmp4 = icmp ne i32 %13, 0, !dbg !572
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !573

if.then5:                                         ; preds = %if.end
  %14 = load i32, i32* %rc, align 4, !dbg !574
  %conv = sext i32 %14 to i64, !dbg !574
  store i64 %conv, i64* %retval, align 8, !dbg !576
  br label %return, !dbg !576

if.end6:                                          ; preds = %if.end
  br label %if.end7, !dbg !577

if.end7:                                          ; preds = %if.end6, %entry
  %15 = load i64, i64* %len.addr, align 8, !dbg !578
  store i64 %15, i64* %retval, align 8, !dbg !579
  br label %return, !dbg !579

return:                                           ; preds = %if.end7, %if.then5
  %16 = load i64, i64* %retval, align 8, !dbg !580
  ret i64 %16, !dbg !580
}

; Function Attrs: nounwind uwtable
define internal i32 @_warc_close(%struct.archive_write* %a) #0 !dbg !248 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !581, metadata !279), !dbg !582
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !583
  ret i32 0, !dbg !584
}

; Function Attrs: nounwind uwtable
define internal i32 @_warc_free(%struct.archive_write* %a) #0 !dbg !249 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %w = alloca %struct.warc_s*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !585, metadata !279), !dbg !586
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !587, metadata !279), !dbg !588
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !589
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !590
  %1 = load i8*, i8** %format_data, align 8, !dbg !590
  %2 = bitcast i8* %1 to %struct.warc_s*, !dbg !589
  store %struct.warc_s* %2, %struct.warc_s** %w, align 8, !dbg !588
  %3 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !591
  %4 = bitcast %struct.warc_s* %3 to i8*, !dbg !591
  call void @free(i8* %4) #6, !dbg !592
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !593
  %format_data1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 14, !dbg !594
  store i8* null, i8** %format_data1, align 8, !dbg !595
  ret i32 0, !dbg !596
}

; Function Attrs: nounwind uwtable
define internal i32 @_warc_finish_entry(%struct.archive_write* %a) #0 !dbg !247 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %w = alloca %struct.warc_s*, align 8
  %rc = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !597, metadata !279), !dbg !598
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !599, metadata !279), !dbg !600
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !601
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !602
  %1 = load i8*, i8** %format_data, align 8, !dbg !602
  %2 = bitcast i8* %1 to %struct.warc_s*, !dbg !601
  store %struct.warc_s* %2, %struct.warc_s** %w, align 8, !dbg !600
  %3 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !603
  %typ = getelementptr inbounds %struct.warc_s, %struct.warc_s* %3, i32 0, i32 2, !dbg !605
  %4 = load i32, i32* %typ, align 8, !dbg !605
  %cmp = icmp eq i32 %4, 32768, !dbg !606
  br i1 %cmp, label %if.then, label %if.end3, !dbg !607

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %rc, metadata !608, metadata !279), !dbg !610
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !611
  %call = call i32 @__archive_write_output(%struct.archive_write* %5, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @_warc_finish_entry._eor, i32 0, i32 0), i64 4), !dbg !612
  store i32 %call, i32* %rc, align 4, !dbg !610
  %6 = load i32, i32* %rc, align 4, !dbg !613
  %cmp1 = icmp ne i32 %6, 0, !dbg !615
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !616

if.then2:                                         ; preds = %if.then
  %7 = load i32, i32* %rc, align 4, !dbg !617
  store i32 %7, i32* %retval, align 4, !dbg !619
  br label %return, !dbg !619

if.end:                                           ; preds = %if.then
  br label %if.end3, !dbg !620

if.end3:                                          ; preds = %if.end, %entry
  %8 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !621
  %typ4 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %8, i32 0, i32 2, !dbg !622
  store i32 0, i32* %typ4, align 8, !dbg !623
  store i32 0, i32* %retval, align 4, !dbg !624
  br label %return, !dbg !624

return:                                           ; preds = %if.end3, %if.then2
  %9 = load i32, i32* %retval, align 4, !dbg !625
  ret i32 %9, !dbg !625
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #5

; Function Attrs: nounwind uwtable
define internal i64 @_popul_ehdr(%struct.archive_string* %tgt, i64 %tsz, %struct.warc_essential_hdr_t* byval align 8 %hdr) #0 !dbg !213 {
entry:
  %retval = alloca i64, align 8
  %tgt.addr = alloca %struct.archive_string*, align 8
  %tsz.addr = alloca i64, align 8
  %std_uuid = alloca [48 x i8], align 16
  %u = alloca i8*, align 8
  %chk = alloca i8*, align 8
  %u25 = alloca %struct.warc_uuid_t, align 4
  store %struct.archive_string* %tgt, %struct.archive_string** %tgt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %tgt.addr, metadata !626, metadata !279), !dbg !627
  store i64 %tsz, i64* %tsz.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %tsz.addr, metadata !628, metadata !279), !dbg !629
  call void @llvm.dbg.declare(metadata %struct.warc_essential_hdr_t* %hdr, metadata !630, metadata !279), !dbg !631
  call void @llvm.dbg.declare(metadata [48 x i8]* %std_uuid, metadata !632, metadata !279), !dbg !636
  %type = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 0, !dbg !637
  %0 = load i32, i32* %type, align 8, !dbg !637
  %cmp = icmp eq i32 %0, 0, !dbg !639
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !640

lor.lhs.false:                                    ; preds = %entry
  %type1 = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 0, !dbg !641
  %1 = load i32, i32* %type1, align 8, !dbg !641
  %cmp2 = icmp ugt i32 %1, 3, !dbg !643
  br i1 %cmp2, label %if.then, label %if.end, !dbg !644

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i64 -1, i64* %retval, align 8, !dbg !645
  br label %return, !dbg !645

if.end:                                           ; preds = %lor.lhs.false
  %2 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !647
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %2, i32 0, i32 1, !dbg !647
  store i64 0, i64* %length, align 8, !dbg !647
  %3 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !647
  %call = call i64 @strlen(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @_popul_ehdr._ver, i32 0, i32 0)) #7, !dbg !647
  %call3 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %3, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @_popul_ehdr._ver, i32 0, i32 0), i64 %call), !dbg !648
  %4 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !650
  %type4 = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 0, !dbg !651
  %5 = load i32, i32* %type4, align 8, !dbg !651
  %idxprom = zext i32 %5 to i64, !dbg !652
  %arrayidx = getelementptr inbounds [9 x i8*], [9 x i8*]* @_popul_ehdr._typ, i64 0, i64 %idxprom, !dbg !652
  %6 = load i8*, i8** %arrayidx, align 8, !dbg !652
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %4, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.13, i32 0, i32 0), i8* %6), !dbg !653
  %tgturi = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 1, !dbg !654
  %7 = load i8*, i8** %tgturi, align 8, !dbg !654
  %cmp5 = icmp ne i8* %7, null, !dbg !656
  br i1 %cmp5, label %if.then6, label %if.end21, !dbg !657

if.then6:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i8** %u, metadata !658, metadata !279), !dbg !660
  call void @llvm.dbg.declare(metadata i8** %chk, metadata !661, metadata !279), !dbg !662
  %tgturi7 = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 1, !dbg !663
  %8 = load i8*, i8** %tgturi7, align 8, !dbg !663
  %call8 = call i8* @strchr(i8* %8, i32 58) #7, !dbg !664
  store i8* %call8, i8** %chk, align 8, !dbg !662
  %9 = load i8*, i8** %chk, align 8, !dbg !665
  %cmp9 = icmp ne i8* %9, null, !dbg !667
  br i1 %cmp9, label %land.lhs.true, label %if.else, !dbg !668

land.lhs.true:                                    ; preds = %if.then6
  %10 = load i8*, i8** %chk, align 8, !dbg !669
  %arrayidx10 = getelementptr inbounds i8, i8* %10, i64 1, !dbg !669
  %11 = load i8, i8* %arrayidx10, align 1, !dbg !669
  %conv = sext i8 %11 to i32, !dbg !669
  %cmp11 = icmp eq i32 %conv, 47, !dbg !671
  br i1 %cmp11, label %land.lhs.true13, label %if.else, !dbg !672

land.lhs.true13:                                  ; preds = %land.lhs.true
  %12 = load i8*, i8** %chk, align 8, !dbg !673
  %arrayidx14 = getelementptr inbounds i8, i8* %12, i64 2, !dbg !673
  %13 = load i8, i8* %arrayidx14, align 1, !dbg !673
  %conv15 = sext i8 %13 to i32, !dbg !673
  %cmp16 = icmp eq i32 %conv15, 47, !dbg !675
  br i1 %cmp16, label %if.then18, label %if.else, !dbg !676

if.then18:                                        ; preds = %land.lhs.true13
  store i8* getelementptr inbounds ([1 x i8], [1 x i8]* @_popul_ehdr._uri, i32 0, i32 0), i8** %u, align 8, !dbg !677
  br label %if.end19, !dbg !679

if.else:                                          ; preds = %land.lhs.true13, %land.lhs.true, %if.then6
  store i8* getelementptr inbounds ([8 x i8], [8 x i8]* @_popul_ehdr._fil, i32 0, i32 0), i8** %u, align 8, !dbg !680
  br label %if.end19

if.end19:                                         ; preds = %if.else, %if.then18
  %14 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !682
  %15 = load i8*, i8** %u, align 8, !dbg !683
  %tgturi20 = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 1, !dbg !684
  %16 = load i8*, i8** %tgturi20, align 8, !dbg !684
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %14, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.14, i32 0, i32 0), i8* %15, i8* %16), !dbg !685
  br label %if.end21, !dbg !686

if.end21:                                         ; preds = %if.end19, %if.end
  %17 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !687
  %rtime = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 3, !dbg !688
  %18 = load i64, i64* %rtime, align 8, !dbg !688
  call void @xstrftime(%struct.archive_string* %17, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.15, i32 0, i32 0), i64 %18), !dbg !689
  %19 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !690
  %mtime = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 4, !dbg !691
  %20 = load i64, i64* %mtime, align 8, !dbg !691
  call void @xstrftime(%struct.archive_string* %19, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.16, i32 0, i32 0), i64 %20), !dbg !692
  %recid = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 2, !dbg !693
  %21 = load i8*, i8** %recid, align 8, !dbg !693
  %cmp22 = icmp eq i8* %21, null, !dbg !695
  br i1 %cmp22, label %if.then24, label %if.end44, !dbg !696

if.then24:                                        ; preds = %if.end21
  call void @llvm.dbg.declare(metadata %struct.warc_uuid_t* %u25, metadata !697, metadata !279), !dbg !699
  %call26 = call i32 @_gen_uuid(%struct.warc_uuid_t* %u25), !dbg !700
  %arraydecay = getelementptr inbounds [48 x i8], [48 x i8]* %std_uuid, i32 0, i32 0, !dbg !701
  %u27 = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %u25, i32 0, i32 0, !dbg !702
  %arrayidx28 = getelementptr inbounds [4 x i32], [4 x i32]* %u27, i64 0, i64 0, !dbg !703
  %22 = load i32, i32* %arrayidx28, align 4, !dbg !703
  %u29 = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %u25, i32 0, i32 0, !dbg !704
  %arrayidx30 = getelementptr inbounds [4 x i32], [4 x i32]* %u29, i64 0, i64 1, !dbg !705
  %23 = load i32, i32* %arrayidx30, align 4, !dbg !705
  %shr = lshr i32 %23, 16, !dbg !706
  %u31 = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %u25, i32 0, i32 0, !dbg !707
  %arrayidx32 = getelementptr inbounds [4 x i32], [4 x i32]* %u31, i64 0, i64 1, !dbg !708
  %24 = load i32, i32* %arrayidx32, align 4, !dbg !708
  %and = and i32 %24, 65535, !dbg !709
  %u33 = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %u25, i32 0, i32 0, !dbg !710
  %arrayidx34 = getelementptr inbounds [4 x i32], [4 x i32]* %u33, i64 0, i64 2, !dbg !711
  %25 = load i32, i32* %arrayidx34, align 4, !dbg !711
  %shr35 = lshr i32 %25, 16, !dbg !712
  %u36 = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %u25, i32 0, i32 0, !dbg !713
  %arrayidx37 = getelementptr inbounds [4 x i32], [4 x i32]* %u36, i64 0, i64 2, !dbg !714
  %26 = load i32, i32* %arrayidx37, align 4, !dbg !714
  %and38 = and i32 %26, 65535, !dbg !715
  %u39 = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %u25, i32 0, i32 0, !dbg !716
  %arrayidx40 = getelementptr inbounds [4 x i32], [4 x i32]* %u39, i64 0, i64 3, !dbg !717
  %27 = load i32, i32* %arrayidx40, align 4, !dbg !717
  %call41 = call i32 (i8*, i64, i8*, ...) @snprintf(i8* %arraydecay, i64 48, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.17, i32 0, i32 0), i32 %22, i32 %shr, i32 %and, i32 %shr35, i32 %and38, i32 %27) #6, !dbg !718
  %arraydecay42 = getelementptr inbounds [48 x i8], [48 x i8]* %std_uuid, i32 0, i32 0, !dbg !719
  %recid43 = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 2, !dbg !720
  store i8* %arraydecay42, i8** %recid43, align 8, !dbg !721
  br label %if.end44, !dbg !722

if.end44:                                         ; preds = %if.then24, %if.end21
  %28 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !723
  %recid45 = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 2, !dbg !724
  %29 = load i8*, i8** %recid45, align 8, !dbg !724
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %28, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.18, i32 0, i32 0), i8* %29), !dbg !725
  %cnttyp = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 5, !dbg !726
  %30 = load i8*, i8** %cnttyp, align 8, !dbg !726
  %cmp46 = icmp ne i8* %30, null, !dbg !728
  br i1 %cmp46, label %if.then48, label %if.end50, !dbg !729

if.then48:                                        ; preds = %if.end44
  %31 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !730
  %cnttyp49 = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 5, !dbg !732
  %32 = load i8*, i8** %cnttyp49, align 8, !dbg !732
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %31, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.19, i32 0, i32 0), i8* %32), !dbg !733
  br label %if.end50, !dbg !734

if.end50:                                         ; preds = %if.then48, %if.end44
  %33 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !735
  %cntlen = getelementptr inbounds %struct.warc_essential_hdr_t, %struct.warc_essential_hdr_t* %hdr, i32 0, i32 6, !dbg !736
  %34 = load i64, i64* %cntlen, align 8, !dbg !736
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %33, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.20, i32 0, i32 0), i64 %34), !dbg !737
  %35 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !738
  %call51 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %35, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.21, i32 0, i32 0), i64 2), !dbg !739
  %36 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !740
  %length52 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %36, i32 0, i32 1, !dbg !740
  %37 = load i64, i64* %length52, align 8, !dbg !740
  %38 = load i64, i64* %tsz.addr, align 8, !dbg !741
  %cmp53 = icmp uge i64 %37, %38, !dbg !742
  br i1 %cmp53, label %cond.true, label %cond.false, !dbg !743

cond.true:                                        ; preds = %if.end50
  br label %cond.end, !dbg !744

cond.false:                                       ; preds = %if.end50
  %39 = load %struct.archive_string*, %struct.archive_string** %tgt.addr, align 8, !dbg !745
  %length55 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %39, i32 0, i32 1, !dbg !745
  %40 = load i64, i64* %length55, align 8, !dbg !745
  br label %cond.end, !dbg !747

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ -1, %cond.true ], [ %40, %cond.false ], !dbg !748
  store i64 %cond, i64* %retval, align 8, !dbg !750
  br label %return, !dbg !750

return:                                           ; preds = %cond.end, %if.then
  %41 = load i64, i64* %retval, align 8, !dbg !751
  ret i64 %41, !dbg !751
}

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

declare void @archive_string_free(%struct.archive_string*) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare void @archive_string_sprintf(%struct.archive_string*, i8*, ...) #2

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #4

; Function Attrs: nounwind uwtable
define internal void @xstrftime(%struct.archive_string* %as, i8* %fmt, i64 %t) #0 !dbg !232 {
entry:
  %as.addr = alloca %struct.archive_string*, align 8
  %fmt.addr = alloca i8*, align 8
  %t.addr = alloca i64, align 8
  %rt = alloca %struct.tm*, align 8
  %timeHere = alloca %struct.tm, align 8
  %strtime = alloca [100 x i8], align 16
  %len = alloca i64, align 8
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !752, metadata !279), !dbg !753
  store i8* %fmt, i8** %fmt.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %fmt.addr, metadata !754, metadata !279), !dbg !755
  store i64 %t, i64* %t.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %t.addr, metadata !756, metadata !279), !dbg !757
  call void @llvm.dbg.declare(metadata %struct.tm** %rt, metadata !758, metadata !279), !dbg !773
  call void @llvm.dbg.declare(metadata %struct.tm* %timeHere, metadata !774, metadata !279), !dbg !775
  call void @llvm.dbg.declare(metadata [100 x i8]* %strtime, metadata !776, metadata !279), !dbg !780
  call void @llvm.dbg.declare(metadata i64* %len, metadata !781, metadata !279), !dbg !782
  %call = call %struct.tm* @gmtime_r(i64* %t.addr, %struct.tm* %timeHere) #6, !dbg !783
  store %struct.tm* %call, %struct.tm** %rt, align 8, !dbg !785
  %cmp = icmp eq %struct.tm* %call, null, !dbg !786
  br i1 %cmp, label %if.then, label %if.end, !dbg !787

if.then:                                          ; preds = %entry
  br label %return, !dbg !788

if.end:                                           ; preds = %entry
  %arraydecay = getelementptr inbounds [100 x i8], [100 x i8]* %strtime, i32 0, i32 0, !dbg !789
  %0 = load i8*, i8** %fmt.addr, align 8, !dbg !790
  %1 = load %struct.tm*, %struct.tm** %rt, align 8, !dbg !791
  %call1 = call i64 @strftime(i8* %arraydecay, i64 99, i8* %0, %struct.tm* %1) #6, !dbg !792
  store i64 %call1, i64* %len, align 8, !dbg !793
  %2 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !794
  %arraydecay2 = getelementptr inbounds [100 x i8], [100 x i8]* %strtime, i32 0, i32 0, !dbg !795
  %3 = load i64, i64* %len, align 8, !dbg !796
  %call3 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %2, i8* %arraydecay2, i64 %3), !dbg !797
  br label %return, !dbg !798

return:                                           ; preds = %if.end, %if.then
  ret void, !dbg !799
}

; Function Attrs: nounwind uwtable
define internal i32 @_gen_uuid(%struct.warc_uuid_t* %tgt) #0 !dbg !235 {
entry:
  %tgt.addr = alloca %struct.warc_uuid_t*, align 8
  store %struct.warc_uuid_t* %tgt, %struct.warc_uuid_t** %tgt.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.warc_uuid_t** %tgt.addr, metadata !801, metadata !279), !dbg !802
  %0 = load %struct.warc_uuid_t*, %struct.warc_uuid_t** %tgt.addr, align 8, !dbg !803
  %u = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %0, i32 0, i32 0, !dbg !804
  %arraydecay = getelementptr inbounds [4 x i32], [4 x i32]* %u, i32 0, i32 0, !dbg !803
  %1 = bitcast i32* %arraydecay to i8*, !dbg !803
  %call = call i32 @archive_random(i8* %1, i64 16), !dbg !805
  %2 = load %struct.warc_uuid_t*, %struct.warc_uuid_t** %tgt.addr, align 8, !dbg !806
  %u1 = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %2, i32 0, i32 0, !dbg !807
  %arrayidx = getelementptr inbounds [4 x i32], [4 x i32]* %u1, i64 0, i64 1, !dbg !806
  %3 = load i32, i32* %arrayidx, align 4, !dbg !808
  %and = and i32 %3, -61441, !dbg !808
  store i32 %and, i32* %arrayidx, align 4, !dbg !808
  %4 = load %struct.warc_uuid_t*, %struct.warc_uuid_t** %tgt.addr, align 8, !dbg !809
  %u2 = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %4, i32 0, i32 0, !dbg !810
  %arrayidx3 = getelementptr inbounds [4 x i32], [4 x i32]* %u2, i64 0, i64 1, !dbg !809
  %5 = load i32, i32* %arrayidx3, align 4, !dbg !811
  %or = or i32 %5, 16384, !dbg !811
  store i32 %or, i32* %arrayidx3, align 4, !dbg !811
  %6 = load %struct.warc_uuid_t*, %struct.warc_uuid_t** %tgt.addr, align 8, !dbg !812
  %u4 = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %6, i32 0, i32 0, !dbg !813
  %arrayidx5 = getelementptr inbounds [4 x i32], [4 x i32]* %u4, i64 0, i64 2, !dbg !812
  %7 = load i32, i32* %arrayidx5, align 4, !dbg !814
  %and6 = and i32 %7, 1073741823, !dbg !814
  store i32 %and6, i32* %arrayidx5, align 4, !dbg !814
  %8 = load %struct.warc_uuid_t*, %struct.warc_uuid_t** %tgt.addr, align 8, !dbg !815
  %u7 = getelementptr inbounds %struct.warc_uuid_t, %struct.warc_uuid_t* %8, i32 0, i32 0, !dbg !816
  %arrayidx8 = getelementptr inbounds [4 x i32], [4 x i32]* %u7, i64 0, i64 2, !dbg !815
  %9 = load i32, i32* %arrayidx8, align 4, !dbg !817
  %or9 = or i32 %9, -2147483648, !dbg !817
  store i32 %or9, i32* %arrayidx8, align 4, !dbg !817
  ret i32 0, !dbg !818
}

; Function Attrs: nounwind
declare i32 @snprintf(i8*, i64, i8*, ...) #3

; Function Attrs: nounwind
declare %struct.tm* @gmtime_r(i64*, %struct.tm*) #3

; Function Attrs: nounwind
declare i64 @strftime(i8*, i64, i8*, %struct.tm*) #3

declare i32 @archive_random(i8*, i64) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!275, !276}
!llvm.ident = !{!277}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !15, subprograms: !208, globals: !250)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_warc.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1, line: 66, size: 32, align: 32, elements: !4)
!4 = !{!5, !6, !7, !8, !9, !10, !11, !12, !13, !14}
!5 = !DIEnumerator(name: "WT_NONE", value: 0)
!6 = !DIEnumerator(name: "WT_INFO", value: 1)
!7 = !DIEnumerator(name: "WT_META", value: 2)
!8 = !DIEnumerator(name: "WT_RSRC", value: 3)
!9 = !DIEnumerator(name: "WT_REQ", value: 4)
!10 = !DIEnumerator(name: "WT_RSP", value: 5)
!11 = !DIEnumerator(name: "WT_RVIS", value: 6)
!12 = !DIEnumerator(name: "WT_CONV", value: 7)
!13 = !DIEnumerator(name: "WT_CONT", value: 8)
!14 = !DIEnumerator(name: "LAST_WT", value: 9)
!15 = !{!16, !136, !25, !204, !57, !207, !50}
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !18, line: 72, size: 2816, align: 64, elements: !19)
!18 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!19 = !{!20, !123, !124, !125, !126, !130, !131, !137, !143, !146, !147, !148, !149, !175, !176, !177, !178, !182, !186, !187, !191, !195, !196, !197, !198, !203}
!20 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !17, file: !18, line: 73, baseType: !21, size: 1280, align: 64)
!21 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !22, line: 89, size: 1280, align: 64, elements: !23)
!22 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!23 = !{!24, !26, !27, !95, !96, !97, !98, !99, !100, !101, !102, !110, !111, !112, !113, !117, !118, !119, !120, !121, !122}
!24 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !21, file: !22, line: 96, baseType: !25, size: 32, align: 32)
!25 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !21, file: !22, line: 97, baseType: !25, size: 32, align: 32, offset: 32)
!27 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !21, file: !22, line: 103, baseType: !28, size: 64, align: 64, offset: 64)
!28 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!29 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !22, line: 63, size: 832, align: 64, elements: !30)
!30 = !{!31, !37, !38, !45, !46, !60, !66, !71, !72, !79, !80, !84, !88}
!31 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !29, file: !22, line: 64, baseType: !32, size: 64, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!33 = !DISubroutineType(types: !34)
!34 = !{!35, !36}
!35 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !29, file: !22, line: 65, baseType: !32, size: 64, align: 64, offset: 64)
!38 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !29, file: !22, line: 66, baseType: !39, size: 64, align: 64, offset: 128)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64, align: 64)
!40 = !DISubroutineType(types: !41)
!41 = !{!35, !36, !42}
!42 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!43 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !44, line: 180, flags: DIFlagFwdDecl)
!44 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!45 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !29, file: !22, line: 68, baseType: !32, size: 64, align: 64, offset: 192)
!46 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !29, file: !22, line: 69, baseType: !47, size: 64, align: 64, offset: 256)
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DISubroutineType(types: !49)
!49 = !{!50, !36, !55, !57}
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !51, line: 102, baseType: !52)
!51 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !53, line: 172, baseType: !54)
!53 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!57 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !58, line: 62, baseType: !59)
!58 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!59 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !29, file: !22, line: 71, baseType: !61, size: 64, align: 64, offset: 320)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!50, !36, !55, !57, !64}
!64 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !65, line: 40, baseType: !54)
!65 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!66 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !29, file: !22, line: 74, baseType: !67, size: 64, align: 64, offset: 384)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DISubroutineType(types: !69)
!69 = !{!35, !36, !70}
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !29, file: !22, line: 76, baseType: !39, size: 64, align: 64, offset: 448)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !29, file: !22, line: 78, baseType: !73, size: 64, align: 64, offset: 512)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!35, !36, !76, !77, !78}
!76 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !64, size: 64, align: 64)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !29, file: !22, line: 81, baseType: !32, size: 64, align: 64, offset: 576)
!80 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !29, file: !22, line: 82, baseType: !81, size: 64, align: 64, offset: 640)
!81 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!82 = !DISubroutineType(types: !83)
!83 = !{!64, !36, !35}
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !29, file: !22, line: 83, baseType: !85, size: 64, align: 64, offset: 704)
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DISubroutineType(types: !87)
!87 = !{!35, !36, !35}
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !29, file: !22, line: 84, baseType: !89, size: 64, align: 64, offset: 768)
!89 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !90, size: 64, align: 64)
!90 = !DISubroutineType(types: !91)
!91 = !{!92, !36, !35}
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !93, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !94)
!94 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !21, file: !22, line: 105, baseType: !35, size: 32, align: 32, offset: 128)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !21, file: !22, line: 106, baseType: !92, size: 64, align: 64, offset: 192)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !21, file: !22, line: 108, baseType: !35, size: 32, align: 32, offset: 256)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !21, file: !22, line: 109, baseType: !92, size: 64, align: 64, offset: 320)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !21, file: !22, line: 112, baseType: !35, size: 32, align: 32, offset: 384)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !21, file: !22, line: 114, baseType: !35, size: 32, align: 32, offset: 416)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !21, file: !22, line: 115, baseType: !92, size: 64, align: 64, offset: 448)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !21, file: !22, line: 116, baseType: !103, size: 192, align: 64, offset: 512)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !104, line: 58, size: 192, align: 64, elements: !105)
!104 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!105 = !{!106, !108, !109}
!106 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !103, file: !104, line: 59, baseType: !107, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !94, size: 64, align: 64)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !103, file: !104, line: 60, baseType: !57, size: 64, align: 64, offset: 64)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !103, file: !104, line: 61, baseType: !57, size: 64, align: 64, offset: 128)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !21, file: !22, line: 118, baseType: !107, size: 64, align: 64, offset: 704)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !21, file: !22, line: 119, baseType: !25, size: 32, align: 32, offset: 768)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !21, file: !22, line: 120, baseType: !25, size: 32, align: 32, offset: 800)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !21, file: !22, line: 121, baseType: !114, size: 64, align: 64, offset: 832)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !115, size: 64, align: 64)
!115 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !116, line: 36, flags: DIFlagFwdDecl)
!116 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_locale.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!117 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !21, file: !22, line: 127, baseType: !92, size: 64, align: 64, offset: 896)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !21, file: !22, line: 128, baseType: !64, size: 64, align: 64, offset: 960)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !21, file: !22, line: 129, baseType: !64, size: 64, align: 64, offset: 1024)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !21, file: !22, line: 130, baseType: !57, size: 64, align: 64, offset: 1088)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !21, file: !22, line: 137, baseType: !94, size: 8, align: 8, offset: 1152)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !21, file: !22, line: 138, baseType: !57, size: 64, align: 64, offset: 1216)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !17, file: !18, line: 76, baseType: !35, size: 32, align: 32, offset: 1280)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !17, file: !18, line: 77, baseType: !64, size: 64, align: 64, offset: 1344)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !17, file: !18, line: 78, baseType: !64, size: 64, align: 64, offset: 1408)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !17, file: !18, line: 81, baseType: !127, size: 64, align: 64, offset: 1472)
!127 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !128, size: 64, align: 64)
!128 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !129)
!129 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !17, file: !18, line: 82, baseType: !57, size: 64, align: 64, offset: 1536)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !17, file: !18, line: 85, baseType: !132, size: 64, align: 64, offset: 1600)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !133, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !44, line: 241, baseType: !134)
!134 = !DISubroutineType(types: !135)
!135 = !{!35, !36, !136}
!136 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !17, file: !18, line: 86, baseType: !138, size: 64, align: 64, offset: 1664)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !44, line: 237, baseType: !140)
!140 = !DISubroutineType(types: !141)
!141 = !{!142, !36, !136, !55, !57}
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !44, line: 95, baseType: !50)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !17, file: !18, line: 87, baseType: !144, size: 64, align: 64, offset: 1728)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !44, line: 243, baseType: !134)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !17, file: !18, line: 88, baseType: !136, size: 64, align: 64, offset: 1792)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !17, file: !18, line: 96, baseType: !35, size: 32, align: 32, offset: 1856)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !17, file: !18, line: 97, baseType: !35, size: 32, align: 32, offset: 1888)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !17, file: !18, line: 102, baseType: !150, size: 64, align: 64, offset: 1920)
!150 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !151, size: 64, align: 64)
!151 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !18, line: 43, size: 768, align: 64, elements: !152)
!152 = !{!153, !154, !155, !156, !160, !164, !168, !169, !170, !171, !172, !173, !174}
!153 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !151, file: !18, line: 44, baseType: !64, size: 64, align: 64)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !151, file: !18, line: 45, baseType: !36, size: 64, align: 64, offset: 64)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !151, file: !18, line: 46, baseType: !150, size: 64, align: 64, offset: 128)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !151, file: !18, line: 47, baseType: !157, size: 64, align: 64, offset: 192)
!157 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64, align: 64)
!158 = !DISubroutineType(types: !159)
!159 = !{!35, !150, !92, !92}
!160 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !151, file: !18, line: 49, baseType: !161, size: 64, align: 64, offset: 256)
!161 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !162, size: 64, align: 64)
!162 = !DISubroutineType(types: !163)
!163 = !{!35, !150}
!164 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !151, file: !18, line: 50, baseType: !165, size: 64, align: 64, offset: 320)
!165 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !166, size: 64, align: 64)
!166 = !DISubroutineType(types: !167)
!167 = !{!35, !150, !55, !57}
!168 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !151, file: !18, line: 51, baseType: !161, size: 64, align: 64, offset: 384)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !151, file: !18, line: 52, baseType: !161, size: 64, align: 64, offset: 448)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !151, file: !18, line: 53, baseType: !136, size: 64, align: 64, offset: 512)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !151, file: !18, line: 54, baseType: !92, size: 64, align: 64, offset: 576)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !151, file: !18, line: 55, baseType: !35, size: 32, align: 32, offset: 640)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !151, file: !18, line: 56, baseType: !35, size: 32, align: 32, offset: 672)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !151, file: !18, line: 57, baseType: !35, size: 32, align: 32, offset: 704)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !17, file: !18, line: 103, baseType: !150, size: 64, align: 64, offset: 1984)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !17, file: !18, line: 109, baseType: !136, size: 64, align: 64, offset: 2048)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !17, file: !18, line: 110, baseType: !92, size: 64, align: 64, offset: 2112)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !17, file: !18, line: 111, baseType: !179, size: 64, align: 64, offset: 2176)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!180 = !DISubroutineType(types: !181)
!181 = !{!35, !16}
!182 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !17, file: !18, line: 112, baseType: !183, size: 64, align: 64, offset: 2240)
!183 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !184, size: 64, align: 64)
!184 = !DISubroutineType(types: !185)
!185 = !{!35, !16, !92, !92}
!186 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !17, file: !18, line: 114, baseType: !179, size: 64, align: 64, offset: 2304)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !17, file: !18, line: 115, baseType: !188, size: 64, align: 64, offset: 2368)
!188 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !189, size: 64, align: 64)
!189 = !DISubroutineType(types: !190)
!190 = !{!35, !16, !42}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !17, file: !18, line: 117, baseType: !192, size: 64, align: 64, offset: 2432)
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DISubroutineType(types: !194)
!194 = !{!50, !16, !55, !57}
!195 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !17, file: !18, line: 119, baseType: !179, size: 64, align: 64, offset: 2496)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !17, file: !18, line: 120, baseType: !179, size: 64, align: 64, offset: 2560)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !17, file: !18, line: 126, baseType: !107, size: 64, align: 64, offset: 2624)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !17, file: !18, line: 127, baseType: !199, size: 64, align: 64, offset: 2688)
!199 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !200, size: 64, align: 64)
!200 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !44, line: 256, baseType: !201)
!201 = !DISubroutineType(types: !202)
!202 = !{!92, !36, !136}
!203 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !17, file: !18, line: 128, baseType: !136, size: 64, align: 64, offset: 2752)
!204 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !205, line: 70, baseType: !206)
!205 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!206 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !53, line: 129, baseType: !25)
!207 = !DIDerivedType(tag: DW_TAG_typedef, name: "uintmax_t", file: !65, line: 135, baseType: !59)
!208 = !{!209, !211, !212, !213, !232, !235, !246, !247, !248, !249}
!209 = distinct !DISubprogram(name: "archive_write_set_format_warc", scope: !1, file: !1, line: 118, type: !33, isLocal: false, isDefinition: true, scopeLine: 119, flags: DIFlagPrototyped, isOptimized: false, variables: !210)
!210 = !{}
!211 = distinct !DISubprogram(name: "_warc_options", scope: !1, file: !1, line: 162, type: !184, isLocal: true, isDefinition: true, scopeLine: 163, flags: DIFlagPrototyped, isOptimized: false, variables: !210)
!212 = distinct !DISubprogram(name: "_warc_header", scope: !1, file: !1, line: 181, type: !189, isLocal: true, isDefinition: true, scopeLine: 182, flags: DIFlagPrototyped, isOptimized: false, variables: !210)
!213 = distinct !DISubprogram(name: "_popul_ehdr", scope: !1, file: !1, line: 354, type: !214, isLocal: true, isDefinition: true, scopeLine: 355, flags: DIFlagPrototyped, isOptimized: false, variables: !210)
!214 = !DISubroutineType(types: !215)
!215 = !{!50, !216, !57, !217}
!216 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!217 = !DIDerivedType(tag: DW_TAG_typedef, name: "warc_essential_hdr_t", file: !1, line: 96, baseType: !218)
!218 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 88, size: 448, align: 64, elements: !219)
!219 = !{!220, !222, !223, !224, !228, !229, !230}
!220 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !218, file: !1, line: 89, baseType: !221, size: 32, align: 32)
!221 = !DIDerivedType(tag: DW_TAG_typedef, name: "warc_type_t", file: !1, line: 86, baseType: !3)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "tgturi", scope: !218, file: !1, line: 90, baseType: !92, size: 64, align: 64, offset: 64)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "recid", scope: !218, file: !1, line: 91, baseType: !92, size: 64, align: 64, offset: 128)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "rtime", scope: !218, file: !1, line: 92, baseType: !225, size: 64, align: 64, offset: 192)
!225 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !226, line: 75, baseType: !227)
!226 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!227 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !53, line: 139, baseType: !54)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "mtime", scope: !218, file: !1, line: 93, baseType: !225, size: 64, align: 64, offset: 256)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "cnttyp", scope: !218, file: !1, line: 94, baseType: !92, size: 64, align: 64, offset: 320)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "cntlen", scope: !218, file: !1, line: 95, baseType: !231, size: 64, align: 64, offset: 384)
!231 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !65, line: 55, baseType: !59)
!232 = distinct !DISubprogram(name: "xstrftime", scope: !1, file: !1, line: 329, type: !233, isLocal: true, isDefinition: true, scopeLine: 330, flags: DIFlagPrototyped, isOptimized: false, variables: !210)
!233 = !DISubroutineType(types: !234)
!234 = !{null, !216, !92, !225}
!235 = distinct !DISubprogram(name: "_gen_uuid", scope: !1, file: !1, line: 434, type: !236, isLocal: true, isDefinition: true, scopeLine: 435, flags: DIFlagPrototyped, isOptimized: false, variables: !210)
!236 = !DISubroutineType(types: !237)
!237 = !{!35, !238}
!238 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !239, size: 64, align: 64)
!239 = !DIDerivedType(tag: DW_TAG_typedef, name: "warc_uuid_t", file: !1, line: 100, baseType: !240)
!240 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 98, size: 128, align: 32, elements: !241)
!241 = !{!242}
!242 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !240, file: !1, line: 99, baseType: !243, size: 128, align: 32)
!243 = !DICompositeType(tag: DW_TAG_array_type, baseType: !25, size: 128, align: 32, elements: !244)
!244 = !{!245}
!245 = !DISubrange(count: 4)
!246 = distinct !DISubprogram(name: "_warc_data", scope: !1, file: !1, line: 270, type: !193, isLocal: true, isDefinition: true, scopeLine: 271, flags: DIFlagPrototyped, isOptimized: false, variables: !210)
!247 = distinct !DISubprogram(name: "_warc_finish_entry", scope: !1, file: !1, line: 292, type: !180, isLocal: true, isDefinition: true, scopeLine: 293, flags: DIFlagPrototyped, isOptimized: false, variables: !210)
!248 = distinct !DISubprogram(name: "_warc_close", scope: !1, file: !1, line: 310, type: !180, isLocal: true, isDefinition: true, scopeLine: 311, flags: DIFlagPrototyped, isOptimized: false, variables: !210)
!249 = distinct !DISubprogram(name: "_warc_free", scope: !1, file: !1, line: 317, type: !180, isLocal: true, isDefinition: true, scopeLine: 318, flags: DIFlagPrototyped, isOptimized: false, variables: !210)
!250 = !{!251, !255, !259, !263, !267, !271}
!251 = !DIGlobalVariable(name: "_ver", scope: !213, file: !1, line: 356, type: !252, isLocal: true, isDefinition: true, variable: [11 x i8]* @_popul_ehdr._ver)
!252 = !DICompositeType(tag: DW_TAG_array_type, baseType: !93, size: 88, align: 8, elements: !253)
!253 = !{!254}
!254 = !DISubrange(count: 11)
!255 = !DIGlobalVariable(name: "_typ", scope: !213, file: !1, line: 357, type: !256, isLocal: true, isDefinition: true, variable: [9 x i8*]* @_popul_ehdr._typ)
!256 = !DICompositeType(tag: DW_TAG_array_type, baseType: !92, size: 576, align: 64, elements: !257)
!257 = !{!258}
!258 = !DISubrange(count: 9)
!259 = !DIGlobalVariable(name: "_uri", scope: !213, file: !1, line: 373, type: !260, isLocal: true, isDefinition: true, variable: [1 x i8]* @_popul_ehdr._uri)
!260 = !DICompositeType(tag: DW_TAG_array_type, baseType: !93, size: 8, align: 8, elements: !261)
!261 = !{!262}
!262 = !DISubrange(count: 1)
!263 = !DIGlobalVariable(name: "_fil", scope: !213, file: !1, line: 374, type: !264, isLocal: true, isDefinition: true, variable: [8 x i8]* @_popul_ehdr._fil)
!264 = !DICompositeType(tag: DW_TAG_array_type, baseType: !93, size: 64, align: 8, elements: !265)
!265 = !{!266}
!266 = !DISubrange(count: 8)
!267 = !DIGlobalVariable(name: "warcinfo", scope: !0, file: !1, line: 62, type: !268, isLocal: true, isDefinition: true, variable: [60 x i8]* @warcinfo)
!268 = !DICompositeType(tag: DW_TAG_array_type, baseType: !93, size: 480, align: 8, elements: !269)
!269 = !{!270}
!270 = !DISubrange(count: 60)
!271 = !DIGlobalVariable(name: "_eor", scope: !247, file: !1, line: 294, type: !272, isLocal: true, isDefinition: true, variable: [5 x i8]* @_warc_finish_entry._eor)
!272 = !DICompositeType(tag: DW_TAG_array_type, baseType: !93, size: 40, align: 8, elements: !273)
!273 = !{!274}
!274 = !DISubrange(count: 5)
!275 = !{i32 2, !"Dwarf Version", i32 4}
!276 = !{i32 2, !"Debug Info Version", i32 3}
!277 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!278 = !DILocalVariable(name: "_a", arg: 1, scope: !209, file: !1, line: 118, type: !36)
!279 = !DIExpression()
!280 = !DILocation(line: 118, column: 47, scope: !209)
!281 = !DILocalVariable(name: "a", scope: !209, file: !1, line: 120, type: !16)
!282 = !DILocation(line: 120, column: 24, scope: !209)
!283 = !DILocation(line: 120, column: 52, scope: !209)
!284 = !DILocation(line: 120, column: 28, scope: !209)
!285 = !DILocalVariable(name: "w", scope: !209, file: !1, line: 121, type: !286)
!286 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !287, size: 64, align: 64)
!287 = !DICompositeType(tag: DW_TAG_structure_type, name: "warc_s", file: !1, line: 52, size: 256, align: 64, elements: !288)
!288 = !{!289, !290, !291, !292, !293}
!289 = !DIDerivedType(tag: DW_TAG_member, name: "omit_warcinfo", scope: !287, file: !1, line: 53, baseType: !25, size: 1, align: 32)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "now", scope: !287, file: !1, line: 55, baseType: !225, size: 64, align: 64, offset: 64)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "typ", scope: !287, file: !1, line: 56, baseType: !204, size: 32, align: 32, offset: 128)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "rng", scope: !287, file: !1, line: 57, baseType: !25, size: 32, align: 32, offset: 160)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "populz", scope: !287, file: !1, line: 59, baseType: !231, size: 64, align: 64, offset: 192)
!294 = !DILocation(line: 121, column: 17, scope: !209)
!295 = !DILocation(line: 123, column: 2, scope: !209)
!296 = !DILocalVariable(name: "magic_test", scope: !297, file: !1, line: 123, type: !35)
!297 = distinct !DILexicalBlock(scope: !209, file: !1, line: 123, column: 2)
!298 = !DILocation(line: 123, column: 2, scope: !297)
!299 = !DILocation(line: 123, column: 2, scope: !300)
!300 = !DILexicalBlockFile(scope: !297, file: !1, discriminator: 1)
!301 = !DILocation(line: 123, column: 2, scope: !302)
!302 = !DILexicalBlockFile(scope: !303, file: !1, discriminator: 2)
!303 = distinct !DILexicalBlock(scope: !297, file: !1, line: 123, column: 2)
!304 = !DILocation(line: 123, column: 2, scope: !305)
!305 = !DILexicalBlockFile(scope: !297, file: !1, discriminator: 3)
!306 = !DILocation(line: 127, column: 6, scope: !307)
!307 = distinct !DILexicalBlock(scope: !209, file: !1, line: 127, column: 6)
!308 = !DILocation(line: 127, column: 9, scope: !307)
!309 = !DILocation(line: 127, column: 21, scope: !307)
!310 = !DILocation(line: 127, column: 6, scope: !209)
!311 = !DILocation(line: 128, column: 4, scope: !312)
!312 = distinct !DILexicalBlock(scope: !307, file: !1, line: 127, column: 30)
!313 = !DILocation(line: 128, column: 7, scope: !312)
!314 = !DILocation(line: 128, column: 20, scope: !312)
!315 = !DILocation(line: 128, column: 3, scope: !312)
!316 = !DILocation(line: 129, column: 2, scope: !312)
!317 = !DILocation(line: 131, column: 6, scope: !209)
!318 = !DILocation(line: 131, column: 4, scope: !209)
!319 = !DILocation(line: 132, column: 6, scope: !320)
!320 = distinct !DILexicalBlock(scope: !209, file: !1, line: 132, column: 6)
!321 = !DILocation(line: 132, column: 8, scope: !320)
!322 = !DILocation(line: 132, column: 6, scope: !209)
!323 = !DILocation(line: 133, column: 22, scope: !324)
!324 = distinct !DILexicalBlock(scope: !320, file: !1, line: 132, column: 17)
!325 = !DILocation(line: 133, column: 25, scope: !324)
!326 = !DILocation(line: 133, column: 3, scope: !324)
!327 = !DILocation(line: 135, column: 3, scope: !324)
!328 = !DILocation(line: 138, column: 2, scope: !209)
!329 = !DILocation(line: 138, column: 5, scope: !209)
!330 = !DILocation(line: 138, column: 19, scope: !209)
!331 = !DILocation(line: 140, column: 11, scope: !209)
!332 = !DILocation(line: 140, column: 2, scope: !209)
!333 = !DILocation(line: 140, column: 5, scope: !209)
!334 = !DILocation(line: 140, column: 9, scope: !209)
!335 = !DILocation(line: 142, column: 2, scope: !209)
!336 = !DILocation(line: 142, column: 5, scope: !209)
!337 = !DILocation(line: 142, column: 9, scope: !209)
!338 = !DILocation(line: 144, column: 25, scope: !209)
!339 = !DILocation(line: 144, column: 28, scope: !209)
!340 = !DILocation(line: 144, column: 11, scope: !209)
!341 = !DILocation(line: 144, column: 2, scope: !209)
!342 = !DILocation(line: 144, column: 5, scope: !209)
!343 = !DILocation(line: 144, column: 9, scope: !209)
!344 = !DILocation(line: 146, column: 19, scope: !209)
!345 = !DILocation(line: 146, column: 2, scope: !209)
!346 = !DILocation(line: 146, column: 5, scope: !209)
!347 = !DILocation(line: 146, column: 17, scope: !209)
!348 = !DILocation(line: 147, column: 2, scope: !209)
!349 = !DILocation(line: 147, column: 5, scope: !209)
!350 = !DILocation(line: 147, column: 17, scope: !209)
!351 = !DILocation(line: 148, column: 2, scope: !209)
!352 = !DILocation(line: 148, column: 5, scope: !209)
!353 = !DILocation(line: 148, column: 20, scope: !209)
!354 = !DILocation(line: 149, column: 2, scope: !209)
!355 = !DILocation(line: 149, column: 5, scope: !209)
!356 = !DILocation(line: 149, column: 25, scope: !209)
!357 = !DILocation(line: 150, column: 2, scope: !209)
!358 = !DILocation(line: 150, column: 5, scope: !209)
!359 = !DILocation(line: 150, column: 23, scope: !209)
!360 = !DILocation(line: 151, column: 2, scope: !209)
!361 = !DILocation(line: 151, column: 5, scope: !209)
!362 = !DILocation(line: 151, column: 18, scope: !209)
!363 = !DILocation(line: 152, column: 2, scope: !209)
!364 = !DILocation(line: 152, column: 5, scope: !209)
!365 = !DILocation(line: 152, column: 17, scope: !209)
!366 = !DILocation(line: 153, column: 2, scope: !209)
!367 = !DILocation(line: 153, column: 5, scope: !209)
!368 = !DILocation(line: 153, column: 25, scope: !209)
!369 = !DILocation(line: 154, column: 2, scope: !209)
!370 = !DILocation(line: 154, column: 5, scope: !209)
!371 = !DILocation(line: 154, column: 13, scope: !209)
!372 = !DILocation(line: 154, column: 28, scope: !209)
!373 = !DILocation(line: 155, column: 2, scope: !209)
!374 = !DILocation(line: 155, column: 5, scope: !209)
!375 = !DILocation(line: 155, column: 13, scope: !209)
!376 = !DILocation(line: 155, column: 33, scope: !209)
!377 = !DILocation(line: 156, column: 2, scope: !209)
!378 = !DILocation(line: 157, column: 1, scope: !209)
!379 = !DILocalVariable(name: "a", arg: 1, scope: !211, file: !1, line: 162, type: !16)
!380 = !DILocation(line: 162, column: 37, scope: !211)
!381 = !DILocalVariable(name: "key", arg: 2, scope: !211, file: !1, line: 162, type: !92)
!382 = !DILocation(line: 162, column: 52, scope: !211)
!383 = !DILocalVariable(name: "val", arg: 3, scope: !211, file: !1, line: 162, type: !92)
!384 = !DILocation(line: 162, column: 69, scope: !211)
!385 = !DILocalVariable(name: "w", scope: !211, file: !1, line: 164, type: !286)
!386 = !DILocation(line: 164, column: 17, scope: !211)
!387 = !DILocation(line: 164, column: 21, scope: !211)
!388 = !DILocation(line: 164, column: 24, scope: !211)
!389 = !DILocation(line: 166, column: 13, scope: !390)
!390 = distinct !DILexicalBlock(scope: !211, file: !1, line: 166, column: 6)
!391 = !DILocation(line: 166, column: 6, scope: !390)
!392 = !DILocation(line: 166, column: 35, scope: !390)
!393 = !DILocation(line: 166, column: 6, scope: !211)
!394 = !DILocation(line: 167, column: 7, scope: !395)
!395 = distinct !DILexicalBlock(scope: !396, file: !1, line: 167, column: 7)
!396 = distinct !DILexicalBlock(scope: !390, file: !1, line: 166, column: 41)
!397 = !DILocation(line: 167, column: 11, scope: !395)
!398 = !DILocation(line: 167, column: 19, scope: !395)
!399 = !DILocation(line: 167, column: 29, scope: !400)
!400 = !DILexicalBlockFile(scope: !395, file: !1, discriminator: 1)
!401 = !DILocation(line: 167, column: 22, scope: !400)
!402 = !DILocation(line: 167, column: 42, scope: !400)
!403 = !DILocation(line: 167, column: 7, scope: !400)
!404 = !DILocation(line: 169, column: 4, scope: !405)
!405 = distinct !DILexicalBlock(scope: !395, file: !1, line: 167, column: 48)
!406 = !DILocation(line: 169, column: 7, scope: !405)
!407 = !DILocation(line: 169, column: 21, scope: !405)
!408 = !DILocation(line: 170, column: 4, scope: !405)
!409 = !DILocation(line: 172, column: 2, scope: !396)
!410 = !DILocation(line: 177, column: 2, scope: !211)
!411 = !DILocation(line: 178, column: 1, scope: !211)
!412 = !DILocalVariable(name: "a", arg: 1, scope: !212, file: !1, line: 181, type: !16)
!413 = !DILocation(line: 181, column: 36, scope: !212)
!414 = !DILocalVariable(name: "entry", arg: 2, scope: !212, file: !1, line: 181, type: !42)
!415 = !DILocation(line: 181, column: 61, scope: !212)
!416 = !DILocalVariable(name: "w", scope: !212, file: !1, line: 183, type: !286)
!417 = !DILocation(line: 183, column: 17, scope: !212)
!418 = !DILocation(line: 183, column: 21, scope: !212)
!419 = !DILocation(line: 183, column: 24, scope: !212)
!420 = !DILocalVariable(name: "hdr", scope: !212, file: !1, line: 184, type: !103)
!421 = !DILocation(line: 184, column: 24, scope: !212)
!422 = !DILocation(line: 188, column: 7, scope: !423)
!423 = distinct !DILexicalBlock(scope: !212, file: !1, line: 188, column: 6)
!424 = !DILocation(line: 188, column: 10, scope: !423)
!425 = !DILocation(line: 188, column: 6, scope: !212)
!426 = !DILocalVariable(name: "r", scope: !427, file: !1, line: 189, type: !50)
!427 = distinct !DILexicalBlock(scope: !423, file: !1, line: 188, column: 25)
!428 = !DILocation(line: 189, column: 11, scope: !427)
!429 = !DILocalVariable(name: "wi", scope: !427, file: !1, line: 190, type: !217)
!430 = !DILocation(line: 190, column: 24, scope: !427)
!431 = !DILocation(line: 199, column: 14, scope: !427)
!432 = !DILocation(line: 199, column: 17, scope: !427)
!433 = !DILocation(line: 199, column: 6, scope: !427)
!434 = !DILocation(line: 199, column: 12, scope: !427)
!435 = !DILocation(line: 200, column: 14, scope: !427)
!436 = !DILocation(line: 200, column: 17, scope: !427)
!437 = !DILocation(line: 200, column: 6, scope: !427)
!438 = !DILocation(line: 200, column: 12, scope: !427)
!439 = !DILocation(line: 202, column: 3, scope: !427)
!440 = !DILocation(line: 202, column: 3, scope: !441)
!441 = !DILexicalBlockFile(scope: !442, file: !1, discriminator: 1)
!442 = distinct !DILexicalBlock(scope: !427, file: !1, line: 202, column: 3)
!443 = !DILocation(line: 203, column: 7, scope: !427)
!444 = !DILocation(line: 203, column: 5, scope: !427)
!445 = !DILocation(line: 204, column: 7, scope: !446)
!446 = distinct !DILexicalBlock(scope: !427, file: !1, line: 204, column: 7)
!447 = !DILocation(line: 204, column: 9, scope: !446)
!448 = !DILocation(line: 204, column: 7, scope: !427)
!449 = !DILocation(line: 207, column: 4, scope: !450)
!450 = distinct !DILexicalBlock(scope: !446, file: !1, line: 204, column: 15)
!451 = !DILocation(line: 210, column: 4, scope: !450)
!452 = !DILocation(line: 213, column: 27, scope: !450)
!453 = !DILocation(line: 213, column: 34, scope: !450)
!454 = !DILocation(line: 213, column: 37, scope: !450)
!455 = !DILocation(line: 213, column: 4, scope: !450)
!456 = !DILocation(line: 214, column: 3, scope: !450)
!457 = !DILocation(line: 216, column: 3, scope: !427)
!458 = !DILocation(line: 216, column: 6, scope: !427)
!459 = !DILocation(line: 216, column: 20, scope: !427)
!460 = !DILocation(line: 217, column: 3, scope: !427)
!461 = !DILocation(line: 218, column: 2, scope: !427)
!462 = !DILocation(line: 220, column: 29, scope: !463)
!463 = distinct !DILexicalBlock(scope: !212, file: !1, line: 220, column: 6)
!464 = !DILocation(line: 220, column: 6, scope: !463)
!465 = !DILocation(line: 220, column: 36, scope: !463)
!466 = !DILocation(line: 220, column: 6, scope: !212)
!467 = !DILocation(line: 221, column: 22, scope: !468)
!468 = distinct !DILexicalBlock(scope: !463, file: !1, line: 220, column: 45)
!469 = !DILocation(line: 221, column: 25, scope: !468)
!470 = !DILocation(line: 221, column: 3, scope: !468)
!471 = !DILocation(line: 223, column: 3, scope: !468)
!472 = !DILocation(line: 226, column: 34, scope: !212)
!473 = !DILocation(line: 226, column: 11, scope: !212)
!474 = !DILocation(line: 226, column: 2, scope: !212)
!475 = !DILocation(line: 226, column: 5, scope: !212)
!476 = !DILocation(line: 226, column: 9, scope: !212)
!477 = !DILocation(line: 227, column: 2, scope: !212)
!478 = !DILocation(line: 227, column: 5, scope: !212)
!479 = !DILocation(line: 227, column: 12, scope: !212)
!480 = !DILocation(line: 228, column: 6, scope: !481)
!481 = distinct !DILexicalBlock(scope: !212, file: !1, line: 228, column: 6)
!482 = !DILocation(line: 228, column: 9, scope: !481)
!483 = !DILocation(line: 228, column: 13, scope: !481)
!484 = !DILocation(line: 228, column: 6, scope: !212)
!485 = !DILocalVariable(name: "rh", scope: !486, file: !1, line: 229, type: !217)
!486 = distinct !DILexicalBlock(scope: !481, file: !1, line: 228, column: 26)
!487 = !DILocation(line: 229, column: 24, scope: !486)
!488 = !DILocalVariable(name: "r", scope: !486, file: !1, line: 238, type: !50)
!489 = !DILocation(line: 238, column: 11, scope: !486)
!490 = !DILocation(line: 239, column: 38, scope: !486)
!491 = !DILocation(line: 239, column: 15, scope: !486)
!492 = !DILocation(line: 239, column: 6, scope: !486)
!493 = !DILocation(line: 239, column: 13, scope: !486)
!494 = !DILocation(line: 240, column: 14, scope: !486)
!495 = !DILocation(line: 240, column: 17, scope: !486)
!496 = !DILocation(line: 240, column: 6, scope: !486)
!497 = !DILocation(line: 240, column: 12, scope: !486)
!498 = !DILocation(line: 241, column: 34, scope: !486)
!499 = !DILocation(line: 241, column: 14, scope: !486)
!500 = !DILocation(line: 241, column: 6, scope: !486)
!501 = !DILocation(line: 241, column: 12, scope: !486)
!502 = !DILocation(line: 242, column: 42, scope: !486)
!503 = !DILocation(line: 242, column: 23, scope: !486)
!504 = !DILocation(line: 242, column: 6, scope: !486)
!505 = !DILocation(line: 242, column: 13, scope: !486)
!506 = !DILocation(line: 244, column: 3, scope: !486)
!507 = !DILocation(line: 244, column: 3, scope: !508)
!508 = !DILexicalBlockFile(scope: !509, file: !1, discriminator: 1)
!509 = distinct !DILexicalBlock(scope: !486, file: !1, line: 244, column: 3)
!510 = !DILocation(line: 245, column: 7, scope: !486)
!511 = !DILocation(line: 245, column: 5, scope: !486)
!512 = !DILocation(line: 246, column: 7, scope: !513)
!513 = distinct !DILexicalBlock(scope: !486, file: !1, line: 246, column: 7)
!514 = !DILocation(line: 246, column: 9, scope: !513)
!515 = !DILocation(line: 246, column: 7, scope: !486)
!516 = !DILocation(line: 249, column: 6, scope: !517)
!517 = distinct !DILexicalBlock(scope: !513, file: !1, line: 246, column: 14)
!518 = !DILocation(line: 249, column: 9, scope: !517)
!519 = !DILocation(line: 248, column: 4, scope: !517)
!520 = !DILocation(line: 252, column: 4, scope: !517)
!521 = !DILocation(line: 255, column: 26, scope: !486)
!522 = !DILocation(line: 255, column: 33, scope: !486)
!523 = !DILocation(line: 255, column: 36, scope: !486)
!524 = !DILocation(line: 255, column: 3, scope: !486)
!525 = !DILocation(line: 257, column: 18, scope: !486)
!526 = !DILocation(line: 257, column: 3, scope: !486)
!527 = !DILocation(line: 257, column: 6, scope: !486)
!528 = !DILocation(line: 257, column: 13, scope: !486)
!529 = !DILocation(line: 258, column: 3, scope: !486)
!530 = !DILocation(line: 259, column: 3, scope: !486)
!531 = !DILocation(line: 263, column: 4, scope: !212)
!532 = !DILocation(line: 263, column: 7, scope: !212)
!533 = !DILocation(line: 262, column: 2, scope: !212)
!534 = !DILocation(line: 266, column: 2, scope: !212)
!535 = !DILocation(line: 267, column: 1, scope: !212)
!536 = !DILocalVariable(name: "a", arg: 1, scope: !246, file: !1, line: 270, type: !16)
!537 = !DILocation(line: 270, column: 34, scope: !246)
!538 = !DILocalVariable(name: "buf", arg: 2, scope: !246, file: !1, line: 270, type: !55)
!539 = !DILocation(line: 270, column: 49, scope: !246)
!540 = !DILocalVariable(name: "len", arg: 3, scope: !246, file: !1, line: 270, type: !57)
!541 = !DILocation(line: 270, column: 61, scope: !246)
!542 = !DILocalVariable(name: "w", scope: !246, file: !1, line: 272, type: !286)
!543 = !DILocation(line: 272, column: 17, scope: !246)
!544 = !DILocation(line: 272, column: 21, scope: !246)
!545 = !DILocation(line: 272, column: 24, scope: !246)
!546 = !DILocation(line: 274, column: 6, scope: !547)
!547 = distinct !DILexicalBlock(scope: !246, file: !1, line: 274, column: 6)
!548 = !DILocation(line: 274, column: 9, scope: !547)
!549 = !DILocation(line: 274, column: 13, scope: !547)
!550 = !DILocation(line: 274, column: 6, scope: !246)
!551 = !DILocalVariable(name: "rc", scope: !552, file: !1, line: 275, type: !35)
!552 = distinct !DILexicalBlock(scope: !547, file: !1, line: 274, column: 26)
!553 = !DILocation(line: 275, column: 7, scope: !552)
!554 = !DILocation(line: 278, column: 7, scope: !555)
!555 = distinct !DILexicalBlock(scope: !552, file: !1, line: 278, column: 7)
!556 = !DILocation(line: 278, column: 13, scope: !555)
!557 = !DILocation(line: 278, column: 16, scope: !555)
!558 = !DILocation(line: 278, column: 11, scope: !555)
!559 = !DILocation(line: 278, column: 7, scope: !552)
!560 = !DILocation(line: 279, column: 18, scope: !561)
!561 = distinct !DILexicalBlock(scope: !555, file: !1, line: 278, column: 24)
!562 = !DILocation(line: 279, column: 21, scope: !561)
!563 = !DILocation(line: 279, column: 8, scope: !561)
!564 = !DILocation(line: 280, column: 3, scope: !561)
!565 = !DILocation(line: 283, column: 31, scope: !552)
!566 = !DILocation(line: 283, column: 34, scope: !552)
!567 = !DILocation(line: 283, column: 39, scope: !552)
!568 = !DILocation(line: 283, column: 8, scope: !552)
!569 = !DILocation(line: 283, column: 6, scope: !552)
!570 = !DILocation(line: 284, column: 7, scope: !571)
!571 = distinct !DILexicalBlock(scope: !552, file: !1, line: 284, column: 7)
!572 = !DILocation(line: 284, column: 10, scope: !571)
!573 = !DILocation(line: 284, column: 7, scope: !552)
!574 = !DILocation(line: 285, column: 11, scope: !575)
!575 = distinct !DILexicalBlock(scope: !571, file: !1, line: 284, column: 25)
!576 = !DILocation(line: 285, column: 4, scope: !575)
!577 = !DILocation(line: 287, column: 2, scope: !552)
!578 = !DILocation(line: 288, column: 9, scope: !246)
!579 = !DILocation(line: 288, column: 2, scope: !246)
!580 = !DILocation(line: 289, column: 1, scope: !246)
!581 = !DILocalVariable(name: "a", arg: 1, scope: !248, file: !1, line: 310, type: !16)
!582 = !DILocation(line: 310, column: 35, scope: !248)
!583 = !DILocation(line: 312, column: 8, scope: !248)
!584 = !DILocation(line: 313, column: 2, scope: !248)
!585 = !DILocalVariable(name: "a", arg: 1, scope: !249, file: !1, line: 317, type: !16)
!586 = !DILocation(line: 317, column: 34, scope: !249)
!587 = !DILocalVariable(name: "w", scope: !249, file: !1, line: 319, type: !286)
!588 = !DILocation(line: 319, column: 17, scope: !249)
!589 = !DILocation(line: 319, column: 21, scope: !249)
!590 = !DILocation(line: 319, column: 24, scope: !249)
!591 = !DILocation(line: 321, column: 7, scope: !249)
!592 = !DILocation(line: 321, column: 2, scope: !249)
!593 = !DILocation(line: 322, column: 2, scope: !249)
!594 = !DILocation(line: 322, column: 5, scope: !249)
!595 = !DILocation(line: 322, column: 17, scope: !249)
!596 = !DILocation(line: 323, column: 2, scope: !249)
!597 = !DILocalVariable(name: "a", arg: 1, scope: !247, file: !1, line: 292, type: !16)
!598 = !DILocation(line: 292, column: 42, scope: !247)
!599 = !DILocalVariable(name: "w", scope: !247, file: !1, line: 295, type: !286)
!600 = !DILocation(line: 295, column: 17, scope: !247)
!601 = !DILocation(line: 295, column: 21, scope: !247)
!602 = !DILocation(line: 295, column: 24, scope: !247)
!603 = !DILocation(line: 297, column: 6, scope: !604)
!604 = distinct !DILexicalBlock(scope: !247, file: !1, line: 297, column: 6)
!605 = !DILocation(line: 297, column: 9, scope: !604)
!606 = !DILocation(line: 297, column: 13, scope: !604)
!607 = !DILocation(line: 297, column: 6, scope: !247)
!608 = !DILocalVariable(name: "rc", scope: !609, file: !1, line: 298, type: !35)
!609 = distinct !DILexicalBlock(scope: !604, file: !1, line: 297, column: 26)
!610 = !DILocation(line: 298, column: 7, scope: !609)
!611 = !DILocation(line: 298, column: 35, scope: !609)
!612 = !DILocation(line: 298, column: 12, scope: !609)
!613 = !DILocation(line: 300, column: 7, scope: !614)
!614 = distinct !DILexicalBlock(scope: !609, file: !1, line: 300, column: 7)
!615 = !DILocation(line: 300, column: 10, scope: !614)
!616 = !DILocation(line: 300, column: 7, scope: !609)
!617 = !DILocation(line: 301, column: 11, scope: !618)
!618 = distinct !DILexicalBlock(scope: !614, file: !1, line: 300, column: 25)
!619 = !DILocation(line: 301, column: 4, scope: !618)
!620 = !DILocation(line: 303, column: 2, scope: !609)
!621 = !DILocation(line: 305, column: 2, scope: !247)
!622 = !DILocation(line: 305, column: 5, scope: !247)
!623 = !DILocation(line: 305, column: 9, scope: !247)
!624 = !DILocation(line: 306, column: 2, scope: !247)
!625 = !DILocation(line: 307, column: 1, scope: !247)
!626 = !DILocalVariable(name: "tgt", arg: 1, scope: !213, file: !1, line: 354, type: !216)
!627 = !DILocation(line: 354, column: 36, scope: !213)
!628 = !DILocalVariable(name: "tsz", arg: 2, scope: !213, file: !1, line: 354, type: !57)
!629 = !DILocation(line: 354, column: 48, scope: !213)
!630 = !DILocalVariable(name: "hdr", arg: 3, scope: !213, file: !1, line: 354, type: !217)
!631 = !DILocation(line: 354, column: 74, scope: !213)
!632 = !DILocalVariable(name: "std_uuid", scope: !213, file: !1, line: 360, type: !633)
!633 = !DICompositeType(tag: DW_TAG_array_type, baseType: !94, size: 384, align: 8, elements: !634)
!634 = !{!635}
!635 = !DISubrange(count: 48)
!636 = !DILocation(line: 360, column: 7, scope: !213)
!637 = !DILocation(line: 362, column: 10, scope: !638)
!638 = distinct !DILexicalBlock(scope: !213, file: !1, line: 362, column: 6)
!639 = !DILocation(line: 362, column: 15, scope: !638)
!640 = !DILocation(line: 362, column: 26, scope: !638)
!641 = !DILocation(line: 362, column: 33, scope: !642)
!642 = !DILexicalBlockFile(scope: !638, file: !1, discriminator: 1)
!643 = !DILocation(line: 362, column: 38, scope: !642)
!644 = !DILocation(line: 362, column: 6, scope: !642)
!645 = !DILocation(line: 364, column: 3, scope: !646)
!646 = distinct !DILexicalBlock(scope: !638, file: !1, line: 362, column: 49)
!647 = !DILocation(line: 367, column: 2, scope: !213)
!648 = !DILocation(line: 367, column: 2, scope: !649)
!649 = !DILexicalBlockFile(scope: !213, file: !1, discriminator: 1)
!650 = !DILocation(line: 369, column: 25, scope: !213)
!651 = !DILocation(line: 369, column: 60, scope: !213)
!652 = !DILocation(line: 369, column: 51, scope: !213)
!653 = !DILocation(line: 369, column: 2, scope: !213)
!654 = !DILocation(line: 371, column: 10, scope: !655)
!655 = distinct !DILexicalBlock(scope: !213, file: !1, line: 371, column: 6)
!656 = !DILocation(line: 371, column: 17, scope: !655)
!657 = !DILocation(line: 371, column: 6, scope: !213)
!658 = !DILocalVariable(name: "u", scope: !659, file: !1, line: 375, type: !92)
!659 = distinct !DILexicalBlock(scope: !655, file: !1, line: 371, column: 26)
!660 = !DILocation(line: 375, column: 15, scope: !659)
!661 = !DILocalVariable(name: "chk", scope: !659, file: !1, line: 376, type: !107)
!662 = !DILocation(line: 376, column: 9, scope: !659)
!663 = !DILocation(line: 376, column: 26, scope: !659)
!664 = !DILocation(line: 376, column: 15, scope: !659)
!665 = !DILocation(line: 378, column: 7, scope: !666)
!666 = distinct !DILexicalBlock(scope: !659, file: !1, line: 378, column: 7)
!667 = !DILocation(line: 378, column: 11, scope: !666)
!668 = !DILocation(line: 378, column: 19, scope: !666)
!669 = !DILocation(line: 378, column: 22, scope: !670)
!670 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 1)
!671 = !DILocation(line: 378, column: 30, scope: !670)
!672 = !DILocation(line: 378, column: 37, scope: !670)
!673 = !DILocation(line: 378, column: 40, scope: !674)
!674 = !DILexicalBlockFile(scope: !666, file: !1, discriminator: 2)
!675 = !DILocation(line: 378, column: 48, scope: !674)
!676 = !DILocation(line: 378, column: 7, scope: !674)
!677 = !DILocation(line: 380, column: 6, scope: !678)
!678 = distinct !DILexicalBlock(scope: !666, file: !1, line: 378, column: 56)
!679 = !DILocation(line: 381, column: 3, scope: !678)
!680 = !DILocation(line: 383, column: 6, scope: !681)
!681 = distinct !DILexicalBlock(scope: !666, file: !1, line: 381, column: 10)
!682 = !DILocation(line: 385, column: 26, scope: !659)
!683 = !DILocation(line: 386, column: 33, scope: !659)
!684 = !DILocation(line: 386, column: 40, scope: !659)
!685 = !DILocation(line: 385, column: 3, scope: !659)
!686 = !DILocation(line: 387, column: 2, scope: !659)
!687 = !DILocation(line: 391, column: 12, scope: !213)
!688 = !DILocation(line: 391, column: 58, scope: !213)
!689 = !DILocation(line: 391, column: 2, scope: !213)
!690 = !DILocation(line: 394, column: 12, scope: !213)
!691 = !DILocation(line: 394, column: 62, scope: !213)
!692 = !DILocation(line: 394, column: 2, scope: !213)
!693 = !DILocation(line: 396, column: 10, scope: !694)
!694 = distinct !DILexicalBlock(scope: !213, file: !1, line: 396, column: 6)
!695 = !DILocation(line: 396, column: 16, scope: !694)
!696 = !DILocation(line: 396, column: 6, scope: !213)
!697 = !DILocalVariable(name: "u", scope: !698, file: !1, line: 398, type: !239)
!698 = distinct !DILexicalBlock(scope: !694, file: !1, line: 396, column: 25)
!699 = !DILocation(line: 398, column: 15, scope: !698)
!700 = !DILocation(line: 400, column: 3, scope: !698)
!701 = !DILocation(line: 409, column: 4, scope: !698)
!702 = !DILocation(line: 411, column: 6, scope: !698)
!703 = !DILocation(line: 411, column: 4, scope: !698)
!704 = !DILocation(line: 412, column: 6, scope: !698)
!705 = !DILocation(line: 412, column: 4, scope: !698)
!706 = !DILocation(line: 412, column: 12, scope: !698)
!707 = !DILocation(line: 412, column: 22, scope: !698)
!708 = !DILocation(line: 412, column: 20, scope: !698)
!709 = !DILocation(line: 412, column: 28, scope: !698)
!710 = !DILocation(line: 413, column: 6, scope: !698)
!711 = !DILocation(line: 413, column: 4, scope: !698)
!712 = !DILocation(line: 413, column: 12, scope: !698)
!713 = !DILocation(line: 413, column: 22, scope: !698)
!714 = !DILocation(line: 413, column: 20, scope: !698)
!715 = !DILocation(line: 413, column: 28, scope: !698)
!716 = !DILocation(line: 414, column: 6, scope: !698)
!717 = !DILocation(line: 414, column: 4, scope: !698)
!718 = !DILocation(line: 408, column: 3, scope: !698)
!719 = !DILocation(line: 415, column: 15, scope: !698)
!720 = !DILocation(line: 415, column: 7, scope: !698)
!721 = !DILocation(line: 415, column: 13, scope: !698)
!722 = !DILocation(line: 416, column: 2, scope: !698)
!723 = !DILocation(line: 419, column: 25, scope: !213)
!724 = !DILocation(line: 419, column: 60, scope: !213)
!725 = !DILocation(line: 419, column: 2, scope: !213)
!726 = !DILocation(line: 421, column: 10, scope: !727)
!727 = distinct !DILexicalBlock(scope: !213, file: !1, line: 421, column: 6)
!728 = !DILocation(line: 421, column: 17, scope: !727)
!729 = !DILocation(line: 421, column: 6, scope: !213)
!730 = !DILocation(line: 422, column: 26, scope: !731)
!731 = distinct !DILexicalBlock(scope: !727, file: !1, line: 421, column: 26)
!732 = !DILocation(line: 422, column: 59, scope: !731)
!733 = !DILocation(line: 422, column: 3, scope: !731)
!734 = !DILocation(line: 423, column: 2, scope: !731)
!735 = !DILocation(line: 426, column: 25, scope: !213)
!736 = !DILocation(line: 426, column: 72, scope: !213)
!737 = !DILocation(line: 426, column: 2, scope: !213)
!738 = !DILocation(line: 428, column: 18, scope: !213)
!739 = !DILocation(line: 428, column: 2, scope: !213)
!740 = !DILocation(line: 430, column: 10, scope: !213)
!741 = !DILocation(line: 430, column: 33, scope: !213)
!742 = !DILocation(line: 430, column: 30, scope: !213)
!743 = !DILocation(line: 430, column: 9, scope: !213)
!744 = !DILocation(line: 430, column: 9, scope: !649)
!745 = !DILocation(line: 430, column: 52, scope: !746)
!746 = !DILexicalBlockFile(scope: !213, file: !1, discriminator: 2)
!747 = !DILocation(line: 430, column: 9, scope: !746)
!748 = !DILocation(line: 430, column: 9, scope: !749)
!749 = !DILexicalBlockFile(scope: !213, file: !1, discriminator: 3)
!750 = !DILocation(line: 430, column: 2, scope: !749)
!751 = !DILocation(line: 431, column: 1, scope: !213)
!752 = !DILocalVariable(name: "as", arg: 1, scope: !232, file: !1, line: 329, type: !216)
!753 = !DILocation(line: 329, column: 34, scope: !232)
!754 = !DILocalVariable(name: "fmt", arg: 2, scope: !232, file: !1, line: 329, type: !92)
!755 = !DILocation(line: 329, column: 50, scope: !232)
!756 = !DILocalVariable(name: "t", arg: 3, scope: !232, file: !1, line: 329, type: !225)
!757 = !DILocation(line: 329, column: 62, scope: !232)
!758 = !DILocalVariable(name: "rt", scope: !232, file: !1, line: 332, type: !759)
!759 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !760, size: 64, align: 64)
!760 = !DICompositeType(tag: DW_TAG_structure_type, name: "tm", file: !226, line: 133, size: 448, align: 64, elements: !761)
!761 = !{!762, !763, !764, !765, !766, !767, !768, !769, !770, !771, !772}
!762 = !DIDerivedType(tag: DW_TAG_member, name: "tm_sec", scope: !760, file: !226, line: 135, baseType: !35, size: 32, align: 32)
!763 = !DIDerivedType(tag: DW_TAG_member, name: "tm_min", scope: !760, file: !226, line: 136, baseType: !35, size: 32, align: 32, offset: 32)
!764 = !DIDerivedType(tag: DW_TAG_member, name: "tm_hour", scope: !760, file: !226, line: 137, baseType: !35, size: 32, align: 32, offset: 64)
!765 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mday", scope: !760, file: !226, line: 138, baseType: !35, size: 32, align: 32, offset: 96)
!766 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mon", scope: !760, file: !226, line: 139, baseType: !35, size: 32, align: 32, offset: 128)
!767 = !DIDerivedType(tag: DW_TAG_member, name: "tm_year", scope: !760, file: !226, line: 140, baseType: !35, size: 32, align: 32, offset: 160)
!768 = !DIDerivedType(tag: DW_TAG_member, name: "tm_wday", scope: !760, file: !226, line: 141, baseType: !35, size: 32, align: 32, offset: 192)
!769 = !DIDerivedType(tag: DW_TAG_member, name: "tm_yday", scope: !760, file: !226, line: 142, baseType: !35, size: 32, align: 32, offset: 224)
!770 = !DIDerivedType(tag: DW_TAG_member, name: "tm_isdst", scope: !760, file: !226, line: 143, baseType: !35, size: 32, align: 32, offset: 256)
!771 = !DIDerivedType(tag: DW_TAG_member, name: "tm_gmtoff", scope: !760, file: !226, line: 146, baseType: !54, size: 64, align: 64, offset: 320)
!772 = !DIDerivedType(tag: DW_TAG_member, name: "tm_zone", scope: !760, file: !226, line: 147, baseType: !92, size: 64, align: 64, offset: 384)
!773 = !DILocation(line: 332, column: 13, scope: !232)
!774 = !DILocalVariable(name: "timeHere", scope: !232, file: !1, line: 334, type: !760)
!775 = !DILocation(line: 334, column: 12, scope: !232)
!776 = !DILocalVariable(name: "strtime", scope: !232, file: !1, line: 336, type: !777)
!777 = !DICompositeType(tag: DW_TAG_array_type, baseType: !94, size: 800, align: 8, elements: !778)
!778 = !{!779}
!779 = !DISubrange(count: 100)
!780 = !DILocation(line: 336, column: 7, scope: !232)
!781 = !DILocalVariable(name: "len", scope: !232, file: !1, line: 337, type: !57)
!782 = !DILocation(line: 337, column: 9, scope: !232)
!783 = !DILocation(line: 340, column: 12, scope: !784)
!784 = distinct !DILexicalBlock(scope: !232, file: !1, line: 340, column: 6)
!785 = !DILocation(line: 340, column: 10, scope: !784)
!786 = !DILocation(line: 340, column: 37, scope: !784)
!787 = !DILocation(line: 340, column: 6, scope: !232)
!788 = !DILocation(line: 341, column: 3, scope: !784)
!789 = !DILocation(line: 349, column: 17, scope: !232)
!790 = !DILocation(line: 349, column: 45, scope: !232)
!791 = !DILocation(line: 349, column: 50, scope: !232)
!792 = !DILocation(line: 349, column: 8, scope: !232)
!793 = !DILocation(line: 349, column: 6, scope: !232)
!794 = !DILocation(line: 350, column: 18, scope: !232)
!795 = !DILocation(line: 350, column: 22, scope: !232)
!796 = !DILocation(line: 350, column: 31, scope: !232)
!797 = !DILocation(line: 350, column: 2, scope: !232)
!798 = !DILocation(line: 351, column: 1, scope: !232)
!799 = !DILocation(line: 351, column: 1, scope: !800)
!800 = !DILexicalBlockFile(scope: !232, file: !1, discriminator: 1)
!801 = !DILocalVariable(name: "tgt", arg: 1, scope: !235, file: !1, line: 434, type: !238)
!802 = !DILocation(line: 434, column: 24, scope: !235)
!803 = !DILocation(line: 436, column: 17, scope: !235)
!804 = !DILocation(line: 436, column: 22, scope: !235)
!805 = !DILocation(line: 436, column: 2, scope: !235)
!806 = !DILocation(line: 438, column: 2, scope: !235)
!807 = !DILocation(line: 438, column: 7, scope: !235)
!808 = !DILocation(line: 438, column: 13, scope: !235)
!809 = !DILocation(line: 439, column: 2, scope: !235)
!810 = !DILocation(line: 439, column: 7, scope: !235)
!811 = !DILocation(line: 439, column: 13, scope: !235)
!812 = !DILocation(line: 440, column: 2, scope: !235)
!813 = !DILocation(line: 440, column: 7, scope: !235)
!814 = !DILocation(line: 440, column: 13, scope: !235)
!815 = !DILocation(line: 441, column: 2, scope: !235)
!816 = !DILocation(line: 441, column: 7, scope: !235)
!817 = !DILocation(line: 441, column: 13, scope: !235)
!818 = !DILocation(line: 442, column: 2, scope: !235)
