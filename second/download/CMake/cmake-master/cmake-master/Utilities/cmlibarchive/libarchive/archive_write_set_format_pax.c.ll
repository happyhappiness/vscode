; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_pax.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write = type { %struct.archive, i32, i64, i64, i8*, i64, i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8*, i64)*, i32 (%struct.archive*, i8*)*, i8*, i32, i32, %struct.archive_write_filter*, %struct.archive_write_filter*, i8*, i8*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, i8*, i8*)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*, %struct.archive_entry*)*, i64 (%struct.archive_write*, i8*, i64)*, i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)*, i8*, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.pax = type { i64, i64, %struct.archive_string, %struct.archive_string, %struct.archive_string, i64, %struct.sparse_block*, %struct.sparse_block*, %struct.archive_string_conv*, i32, i32 }
%struct.sparse_block = type { %struct.sparse_block*, i32, i64, i64 }

@.str = private unnamed_addr constant [40 x i8] c"archive_write_set_format_pax_restricted\00", align 1
@.str.1 = private unnamed_addr constant [33 x i8] c"restricted POSIX pax interchange\00", align 1
@.str.2 = private unnamed_addr constant [29 x i8] c"archive_write_set_format_pax\00", align 1
@.str.3 = private unnamed_addr constant [24 x i8] c"Can't allocate pax data\00", align 1
@.str.4 = private unnamed_addr constant [4 x i8] c"pax\00", align 1
@.str.5 = private unnamed_addr constant [22 x i8] c"POSIX pax interchange\00", align 1
@.str.6 = private unnamed_addr constant [11 x i8] c"hdrcharset\00", align 1
@.str.7 = private unnamed_addr constant [50 x i8] c"pax: hdrcharset option needs a character-set name\00", align 1
@.str.8 = private unnamed_addr constant [7 x i8] c"BINARY\00", align 1
@.str.9 = private unnamed_addr constant [7 x i8] c"binary\00", align 1
@.str.10 = private unnamed_addr constant [6 x i8] c"UTF-8\00", align 1
@.str.11 = private unnamed_addr constant [26 x i8] c"pax: invalid charset name\00", align 1
@.str.12 = private unnamed_addr constant [48 x i8] c"Can't record entry in tar file without pathname\00", align 1
@.str.13 = private unnamed_addr constant [36 x i8] c"Can't translate linkname '%s' to %s\00", align 1
@.str.14 = private unnamed_addr constant [33 x i8] c"tar format cannot archive socket\00", align 1
@.str.15 = private unnamed_addr constant [43 x i8] c"tar format cannot archive this (type=0%lo)\00", align 1
@.str.16 = private unnamed_addr constant [3 x i8] c"._\00", align 1
@.str.17 = private unnamed_addr constant [36 x i8] c"Can't translate pathname '%s' to %s\00", align 1
@.str.18 = private unnamed_addr constant [33 x i8] c"Can't translate uname '%s' to %s\00", align 1
@.str.19 = private unnamed_addr constant [33 x i8] c"Can't translate gname '%s' to %s\00", align 1
@.str.20 = private unnamed_addr constant [5 x i8] c"path\00", align 1
@.str.21 = private unnamed_addr constant [9 x i8] c"linkpath\00", align 1
@.str.22 = private unnamed_addr constant [18 x i8] c"././@LongHardLink\00", align 1
@.str.23 = private unnamed_addr constant [17 x i8] c"././@LongSymLink\00", align 1
@.str.24 = private unnamed_addr constant [5 x i8] c"size\00", align 1
@.str.25 = private unnamed_addr constant [4 x i8] c"gid\00", align 1
@.str.26 = private unnamed_addr constant [6 x i8] c"gname\00", align 1
@.str.27 = private unnamed_addr constant [4 x i8] c"uid\00", align 1
@.str.28 = private unnamed_addr constant [6 x i8] c"uname\00", align 1
@.str.29 = private unnamed_addr constant [16 x i8] c"SCHILY.devmajor\00", align 1
@.str.30 = private unnamed_addr constant [16 x i8] c"SCHILY.devminor\00", align 1
@.str.31 = private unnamed_addr constant [6 x i8] c"ctime\00", align 1
@.str.32 = private unnamed_addr constant [6 x i8] c"atime\00", align 1
@.str.33 = private unnamed_addr constant [24 x i8] c"LIBARCHIVE.creationtime\00", align 1
@.str.34 = private unnamed_addr constant [6 x i8] c"mtime\00", align 1
@.str.35 = private unnamed_addr constant [14 x i8] c"SCHILY.fflags\00", align 1
@.str.36 = private unnamed_addr constant [17 x i8] c"GNU.sparse.major\00", align 1
@.str.37 = private unnamed_addr constant [17 x i8] c"GNU.sparse.minor\00", align 1
@.str.38 = private unnamed_addr constant [16 x i8] c"GNU.sparse.name\00", align 1
@.str.39 = private unnamed_addr constant [20 x i8] c"GNU.sparse.realsize\00", align 1
@.str.40 = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1
@.str.41 = private unnamed_addr constant [9 x i8] c"%jd\0A%jd\0A\00", align 1
@.str.42 = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1
@.str.43 = private unnamed_addr constant [67 x i8] c"archive_write_pax_header: 'x' header failed?!  This can't happen.\0A\00", align 1
@.str.44 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Linkname\00", align 1
@.str.45 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Pathname\00", align 1
@.str.46 = private unnamed_addr constant [32 x i8] c"Can't allocate memory for Uname\00", align 1
@.str.47 = private unnamed_addr constant [32 x i8] c"Can't allocate memory for Gname\00", align 1
@.str.48 = private unnamed_addr constant [11 x i8] c"0123456789\00", align 1
@.str.49 = private unnamed_addr constant [15 x i8] c"SCHILY.acl.ace\00", align 1
@.str.50 = private unnamed_addr constant [18 x i8] c"SCHILY.acl.access\00", align 1
@.str.51 = private unnamed_addr constant [19 x i8] c"SCHILY.acl.default\00", align 1
@.str.52 = private unnamed_addr constant [6 x i8] c"%s %s\00", align 1
@.str.53 = private unnamed_addr constant [27 x i8] c"Can't allocate memory for \00", align 1
@.str.54 = private unnamed_addr constant [9 x i8] c"%s %s %s\00", align 1
@.str.55 = private unnamed_addr constant [17 x i8] c"Can't translate \00", align 1
@.str.56 = private unnamed_addr constant [10 x i8] c" to UTF-8\00", align 1
@.str.57 = private unnamed_addr constant [20 x i8] c"GNUSparseFile/blank\00", align 1
@.str.58 = private unnamed_addr constant [14 x i8] c"GNUSparseFile\00", align 1
@.str.59 = private unnamed_addr constant [17 x i8] c"0123456789ABCDEF\00", align 1
@.str.60 = private unnamed_addr constant [18 x i8] c"LIBARCHIVE.xattr.\00", align 1
@.str.61 = private unnamed_addr constant [14 x i8] c"SCHILY.xattr.\00", align 1
@base64_encode.digits = internal constant [64 x i8] c"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/", align 16
@.str.62 = private unnamed_addr constant [16 x i8] c"PaxHeader/blank\00", align 1
@.str.63 = private unnamed_addr constant [19 x i8] c"/PaxHeader/rootdir\00", align 1
@.str.64 = private unnamed_addr constant [21 x i8] c"PaxHeader/currentdir\00", align 1
@.str.65 = private unnamed_addr constant [10 x i8] c"PaxHeader\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_pax_restricted(%struct.archive* %_a) #0 !dbg !218 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !292, metadata !293), !dbg !294
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !295, metadata !293), !dbg !296
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !297
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !298
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !296
  call void @llvm.dbg.declare(metadata i32* %r, metadata !299, metadata !293), !dbg !300
  br label %do.body, !dbg !301

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !302, metadata !293), !dbg !304
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !305
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str, i32 0, i32 0)), !dbg !305
  store i32 %call, i32* %magic_test, align 4, !dbg !305
  %3 = load i32, i32* %magic_test, align 4, !dbg !305
  %cmp = icmp eq i32 %3, -30, !dbg !305
  br i1 %cmp, label %if.then, label %if.end, !dbg !305

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !307
  br label %return, !dbg !307

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !310

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !312
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !313
  %call1 = call i32 @archive_write_set_format_pax(%struct.archive* %archive), !dbg !314
  store i32 %call1, i32* %r, align 4, !dbg !315
  %5 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !316
  %archive2 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %5, i32 0, i32 0, !dbg !317
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive2, i32 0, i32 3, !dbg !318
  store i32 196611, i32* %archive_format, align 8, !dbg !319
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !320
  %archive3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !321
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive3, i32 0, i32 4, !dbg !322
  store i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.1, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !323
  %7 = load i32, i32* %r, align 4, !dbg !324
  store i32 %7, i32* %retval, align 4, !dbg !325
  br label %return, !dbg !325

return:                                           ; preds = %do.end, %if.then
  %8 = load i32, i32* %retval, align 4, !dbg !326
  ret i32 %8, !dbg !326
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_pax(%struct.archive* %_a) #0 !dbg !219 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_write*, align 8
  %pax = alloca %struct.pax*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !327, metadata !293), !dbg !328
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a, metadata !329, metadata !293), !dbg !330
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !331
  %1 = bitcast %struct.archive* %0 to %struct.archive_write*, !dbg !332
  store %struct.archive_write* %1, %struct.archive_write** %a, align 8, !dbg !330
  call void @llvm.dbg.declare(metadata %struct.pax** %pax, metadata !333, metadata !293), !dbg !334
  br label %do.body, !dbg !335

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !336, metadata !293), !dbg !338
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !339
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 -1329217314, i32 1, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.2, i32 0, i32 0)), !dbg !339
  store i32 %call, i32* %magic_test, align 4, !dbg !339
  %3 = load i32, i32* %magic_test, align 4, !dbg !339
  %cmp = icmp eq i32 %3, -30, !dbg !339
  br i1 %cmp, label %if.then, label %if.end, !dbg !339

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !341
  br label %return, !dbg !341

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !344

do.end:                                           ; preds = %if.end
  %4 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !346
  %format_free = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 22, !dbg !348
  %5 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free, align 8, !dbg !348
  %cmp1 = icmp ne i32 (%struct.archive_write*)* %5, null, !dbg !349
  br i1 %cmp1, label %if.then2, label %if.end5, !dbg !350

if.then2:                                         ; preds = %do.end
  %6 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !351
  %format_free3 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 22, !dbg !352
  %7 = load i32 (%struct.archive_write*)*, i32 (%struct.archive_write*)** %format_free3, align 8, !dbg !352
  %8 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !353
  %call4 = call i32 %7(%struct.archive_write* %8), !dbg !354
  br label %if.end5, !dbg !354

if.end5:                                          ; preds = %if.then2, %do.end
  %call6 = call noalias i8* @calloc(i64 1, i64 128) #7, !dbg !355
  %9 = bitcast i8* %call6 to %struct.pax*, !dbg !356
  store %struct.pax* %9, %struct.pax** %pax, align 8, !dbg !357
  %10 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !358
  %cmp7 = icmp eq %struct.pax* %10, null, !dbg !360
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !361

if.then8:                                         ; preds = %if.end5
  %11 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !362
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %11, i32 0, i32 0, !dbg !364
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.3, i32 0, i32 0)), !dbg !365
  store i32 -30, i32* %retval, align 4, !dbg !366
  br label %return, !dbg !366

if.end9:                                          ; preds = %if.end5
  %12 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !367
  %flags = getelementptr inbounds %struct.pax, %struct.pax* %12, i32 0, i32 10, !dbg !368
  store i32 3, i32* %flags, align 4, !dbg !369
  %13 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !370
  %14 = bitcast %struct.pax* %13 to i8*, !dbg !370
  %15 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !371
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %15, i32 0, i32 14, !dbg !372
  store i8* %14, i8** %format_data, align 8, !dbg !373
  %16 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !374
  %format_name = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 15, !dbg !375
  store i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.4, i32 0, i32 0), i8** %format_name, align 8, !dbg !376
  %17 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !377
  %format_options = getelementptr inbounds %struct.archive_write, %struct.archive_write* %17, i32 0, i32 17, !dbg !378
  store i32 (%struct.archive_write*, i8*, i8*)* @archive_write_pax_options, i32 (%struct.archive_write*, i8*, i8*)** %format_options, align 8, !dbg !379
  %18 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !380
  %format_write_header = getelementptr inbounds %struct.archive_write, %struct.archive_write* %18, i32 0, i32 19, !dbg !381
  store i32 (%struct.archive_write*, %struct.archive_entry*)* @archive_write_pax_header, i32 (%struct.archive_write*, %struct.archive_entry*)** %format_write_header, align 8, !dbg !382
  %19 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !383
  %format_write_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %19, i32 0, i32 20, !dbg !384
  store i64 (%struct.archive_write*, i8*, i64)* @archive_write_pax_data, i64 (%struct.archive_write*, i8*, i64)** %format_write_data, align 8, !dbg !385
  %20 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !386
  %format_close = getelementptr inbounds %struct.archive_write, %struct.archive_write* %20, i32 0, i32 21, !dbg !387
  store i32 (%struct.archive_write*)* @archive_write_pax_close, i32 (%struct.archive_write*)** %format_close, align 8, !dbg !388
  %21 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !389
  %format_free10 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %21, i32 0, i32 22, !dbg !390
  store i32 (%struct.archive_write*)* @archive_write_pax_free, i32 (%struct.archive_write*)** %format_free10, align 8, !dbg !391
  %22 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !392
  %format_finish_entry = getelementptr inbounds %struct.archive_write, %struct.archive_write* %22, i32 0, i32 18, !dbg !393
  store i32 (%struct.archive_write*)* @archive_write_pax_finish_entry, i32 (%struct.archive_write*)** %format_finish_entry, align 8, !dbg !394
  %23 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !395
  %archive11 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %23, i32 0, i32 0, !dbg !396
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive11, i32 0, i32 3, !dbg !397
  store i32 196610, i32* %archive_format, align 8, !dbg !398
  %24 = load %struct.archive_write*, %struct.archive_write** %a, align 8, !dbg !399
  %archive12 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %24, i32 0, i32 0, !dbg !400
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive12, i32 0, i32 4, !dbg !401
  store i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.5, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !402
  store i32 0, i32* %retval, align 4, !dbg !403
  br label %return, !dbg !403

return:                                           ; preds = %if.end9, %if.then8, %if.then
  %25 = load i32, i32* %retval, align 4, !dbg !404
  ret i32 %25, !dbg !404
}

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_pax_options(%struct.archive_write* %a, i8* %key, i8* %val) #0 !dbg !220 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %pax = alloca %struct.pax*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !405, metadata !293), !dbg !406
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !407, metadata !293), !dbg !408
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !409, metadata !293), !dbg !410
  call void @llvm.dbg.declare(metadata %struct.pax** %pax, metadata !411, metadata !293), !dbg !412
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !413
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !414
  %1 = load i8*, i8** %format_data, align 8, !dbg !414
  %2 = bitcast i8* %1 to %struct.pax*, !dbg !415
  store %struct.pax* %2, %struct.pax** %pax, align 8, !dbg !412
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !416, metadata !293), !dbg !417
  store i32 -25, i32* %ret, align 4, !dbg !417
  %3 = load i8*, i8** %key.addr, align 8, !dbg !418
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.6, i32 0, i32 0)) #8, !dbg !420
  %cmp = icmp eq i32 %call, 0, !dbg !421
  br i1 %cmp, label %if.then, label %if.end30, !dbg !422

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %val.addr, align 8, !dbg !423
  %cmp1 = icmp eq i8* %4, null, !dbg !426
  br i1 %cmp1, label %if.then4, label %lor.lhs.false, !dbg !427

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %val.addr, align 8, !dbg !428
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !428
  %6 = load i8, i8* %arrayidx, align 1, !dbg !428
  %conv = sext i8 %6 to i32, !dbg !428
  %cmp2 = icmp eq i32 %conv, 0, !dbg !430
  br i1 %cmp2, label %if.then4, label %if.else, !dbg !431

if.then4:                                         ; preds = %lor.lhs.false, %if.then
  %7 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !432
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %7, i32 0, i32 0, !dbg !433
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([50 x i8], [50 x i8]* @.str.7, i32 0, i32 0)), !dbg !434
  br label %if.end29, !dbg !434

if.else:                                          ; preds = %lor.lhs.false
  %8 = load i8*, i8** %val.addr, align 8, !dbg !435
  %call5 = call i32 @strcmp(i8* %8, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.8, i32 0, i32 0)) #8, !dbg !437
  %cmp6 = icmp eq i32 %call5, 0, !dbg !438
  br i1 %cmp6, label %if.then12, label %lor.lhs.false8, !dbg !439

lor.lhs.false8:                                   ; preds = %if.else
  %9 = load i8*, i8** %val.addr, align 8, !dbg !440
  %call9 = call i32 @strcmp(i8* %9, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.9, i32 0, i32 0)) #8, !dbg !441
  %cmp10 = icmp eq i32 %call9, 0, !dbg !442
  br i1 %cmp10, label %if.then12, label %if.else13, !dbg !443

if.then12:                                        ; preds = %lor.lhs.false8, %if.else
  %10 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !444
  %opt_binary = getelementptr inbounds %struct.pax, %struct.pax* %10, i32 0, i32 9, !dbg !446
  store i32 1, i32* %opt_binary, align 8, !dbg !447
  store i32 0, i32* %ret, align 4, !dbg !448
  br label %if.end28, !dbg !449

if.else13:                                        ; preds = %lor.lhs.false8
  %11 = load i8*, i8** %val.addr, align 8, !dbg !450
  %call14 = call i32 @strcmp(i8* %11, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i32 0, i32 0)) #8, !dbg !453
  %cmp15 = icmp eq i32 %call14, 0, !dbg !454
  br i1 %cmp15, label %if.then17, label %if.else25, !dbg !453

if.then17:                                        ; preds = %if.else13
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !455
  %archive18 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 0, !dbg !457
  %call19 = call %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive* %archive18, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i32 0, i32 0), i32 0), !dbg !458
  %13 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !459
  %sconv_utf8 = getelementptr inbounds %struct.pax, %struct.pax* %13, i32 0, i32 8, !dbg !460
  store %struct.archive_string_conv* %call19, %struct.archive_string_conv** %sconv_utf8, align 8, !dbg !461
  %14 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !462
  %sconv_utf820 = getelementptr inbounds %struct.pax, %struct.pax* %14, i32 0, i32 8, !dbg !464
  %15 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_utf820, align 8, !dbg !464
  %cmp21 = icmp eq %struct.archive_string_conv* %15, null, !dbg !465
  br i1 %cmp21, label %if.then23, label %if.else24, !dbg !466

if.then23:                                        ; preds = %if.then17
  store i32 -30, i32* %ret, align 4, !dbg !467
  br label %if.end, !dbg !468

if.else24:                                        ; preds = %if.then17
  store i32 0, i32* %ret, align 4, !dbg !469
  br label %if.end

if.end:                                           ; preds = %if.else24, %if.then23
  br label %if.end27, !dbg !470

if.else25:                                        ; preds = %if.else13
  %16 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !471
  %archive26 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 0, !dbg !472
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive26, i32 -1, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.11, i32 0, i32 0)), !dbg !473
  br label %if.end27

if.end27:                                         ; preds = %if.else25, %if.end
  br label %if.end28

if.end28:                                         ; preds = %if.end27, %if.then12
  br label %if.end29

if.end29:                                         ; preds = %if.end28, %if.then4
  %17 = load i32, i32* %ret, align 4, !dbg !474
  store i32 %17, i32* %retval, align 4, !dbg !475
  br label %return, !dbg !475

if.end30:                                         ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !476
  br label %return, !dbg !476

return:                                           ; preds = %if.end30, %if.end29
  %18 = load i32, i32* %retval, align 4, !dbg !477
  ret i32 %18, !dbg !477
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_pax_header(%struct.archive_write* %a, %struct.archive_entry* %entry_original) #0 !dbg !221 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry_original.addr = alloca %struct.archive_entry*, align 8
  %entry_main = alloca %struct.archive_entry*, align 8
  %p = alloca i8*, align 8
  %suffix = alloca i8*, align 8
  %need_extension = alloca i32, align 4
  %r = alloca i32, align 4
  %ret = alloca i32, align 4
  %acl_types = alloca i32, align 4
  %sparse_count = alloca i32, align 4
  %sparse_total = alloca i64, align 8
  %real_size = alloca i64, align 8
  %pax = alloca %struct.pax*, align 8
  %hardlink = alloca i8*, align 8
  %path = alloca i8*, align 8
  %linkpath = alloca i8*, align 8
  %uname = alloca i8*, align 8
  %gname = alloca i8*, align 8
  %mac_metadata = alloca i8*, align 8
  %mac_metadata_size = alloca i64, align 8
  %sconv = alloca %struct.archive_string_conv*, align 8
  %hardlink_length = alloca i64, align 8
  %path_length = alloca i64, align 8
  %linkpath_length = alloca i64, align 8
  %uname_length = alloca i64, align 8
  %gname_length = alloca i64, align 8
  %paxbuff = alloca [512 x i8], align 16
  %ustarbuff = alloca [512 x i8], align 16
  %ustar_entry_name = alloca [256 x i8], align 16
  %pax_entry_name = alloca [256 x i8], align 16
  %gnu_sparse_name = alloca [256 x i8], align 16
  %entry_name = alloca %struct.archive_string, align 8
  %as = alloca %struct.archive_string, align 8
  %oname = alloca i8*, align 8
  %name = alloca i8*, align 8
  %bname = alloca i8*, align 8
  %name_length = alloca i64, align 8
  %extra = alloca %struct.archive_entry*, align 8
  %offset = alloca i64, align 8
  %length147 = alloca i64, align 8
  %last_offset = alloca i64, align 8
  %rdevmajor = alloca i32, align 4
  %rdevminor = alloca i32, align 4
  %soffset = alloca i64, align 8
  %slength = alloca i64, align 8
  %mapsize = alloca i64, align 8
  %pax_attr_entry = alloca %struct.archive_entry*, align 8
  %s633 = alloca i64, align 8
  %uid = alloca i64, align 8
  %gid = alloca i64, align 8
  %mode = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !478, metadata !293), !dbg !479
  store %struct.archive_entry* %entry_original, %struct.archive_entry** %entry_original.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry_original.addr, metadata !480, metadata !293), !dbg !481
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry_main, metadata !482, metadata !293), !dbg !483
  call void @llvm.dbg.declare(metadata i8** %p, metadata !484, metadata !293), !dbg !485
  call void @llvm.dbg.declare(metadata i8** %suffix, metadata !486, metadata !293), !dbg !487
  call void @llvm.dbg.declare(metadata i32* %need_extension, metadata !488, metadata !293), !dbg !489
  call void @llvm.dbg.declare(metadata i32* %r, metadata !490, metadata !293), !dbg !491
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !492, metadata !293), !dbg !493
  call void @llvm.dbg.declare(metadata i32* %acl_types, metadata !494, metadata !293), !dbg !495
  call void @llvm.dbg.declare(metadata i32* %sparse_count, metadata !496, metadata !293), !dbg !497
  call void @llvm.dbg.declare(metadata i64* %sparse_total, metadata !498, metadata !293), !dbg !499
  call void @llvm.dbg.declare(metadata i64* %real_size, metadata !500, metadata !293), !dbg !501
  call void @llvm.dbg.declare(metadata %struct.pax** %pax, metadata !502, metadata !293), !dbg !503
  call void @llvm.dbg.declare(metadata i8** %hardlink, metadata !504, metadata !293), !dbg !505
  call void @llvm.dbg.declare(metadata i8** %path, metadata !506, metadata !293), !dbg !507
  store i8* null, i8** %path, align 8, !dbg !507
  call void @llvm.dbg.declare(metadata i8** %linkpath, metadata !508, metadata !293), !dbg !509
  store i8* null, i8** %linkpath, align 8, !dbg !509
  call void @llvm.dbg.declare(metadata i8** %uname, metadata !510, metadata !293), !dbg !511
  store i8* null, i8** %uname, align 8, !dbg !511
  call void @llvm.dbg.declare(metadata i8** %gname, metadata !512, metadata !293), !dbg !513
  store i8* null, i8** %gname, align 8, !dbg !513
  call void @llvm.dbg.declare(metadata i8** %mac_metadata, metadata !514, metadata !293), !dbg !515
  call void @llvm.dbg.declare(metadata i64* %mac_metadata_size, metadata !516, metadata !293), !dbg !517
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !518, metadata !293), !dbg !519
  call void @llvm.dbg.declare(metadata i64* %hardlink_length, metadata !520, metadata !293), !dbg !521
  call void @llvm.dbg.declare(metadata i64* %path_length, metadata !522, metadata !293), !dbg !523
  call void @llvm.dbg.declare(metadata i64* %linkpath_length, metadata !524, metadata !293), !dbg !525
  call void @llvm.dbg.declare(metadata i64* %uname_length, metadata !526, metadata !293), !dbg !527
  call void @llvm.dbg.declare(metadata i64* %gname_length, metadata !528, metadata !293), !dbg !529
  call void @llvm.dbg.declare(metadata [512 x i8]* %paxbuff, metadata !530, metadata !293), !dbg !534
  call void @llvm.dbg.declare(metadata [512 x i8]* %ustarbuff, metadata !535, metadata !293), !dbg !536
  call void @llvm.dbg.declare(metadata [256 x i8]* %ustar_entry_name, metadata !537, metadata !293), !dbg !541
  call void @llvm.dbg.declare(metadata [256 x i8]* %pax_entry_name, metadata !542, metadata !293), !dbg !543
  call void @llvm.dbg.declare(metadata [256 x i8]* %gnu_sparse_name, metadata !544, metadata !293), !dbg !545
  call void @llvm.dbg.declare(metadata %struct.archive_string* %entry_name, metadata !546, metadata !293), !dbg !547
  store i32 0, i32* %ret, align 4, !dbg !548
  store i32 0, i32* %need_extension, align 4, !dbg !549
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !550
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !551
  %1 = load i8*, i8** %format_data, align 8, !dbg !551
  %2 = bitcast i8* %1 to %struct.pax*, !dbg !552
  store %struct.pax* %2, %struct.pax** %pax, align 8, !dbg !553
  %3 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !554
  %call = call i8* @archive_entry_pathname(%struct.archive_entry* %3), !dbg !556
  %cmp = icmp eq i8* %call, null, !dbg !557
  br i1 %cmp, label %if.then, label %if.end, !dbg !558

if.then:                                          ; preds = %entry
  %4 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !559
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %4, i32 0, i32 0, !dbg !561
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.12, i32 0, i32 0)), !dbg !562
  store i32 -25, i32* %retval, align 4, !dbg !563
  br label %return, !dbg !563

if.end:                                           ; preds = %entry
  %5 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !564
  %opt_binary = getelementptr inbounds %struct.pax, %struct.pax* %5, i32 0, i32 9, !dbg !566
  %6 = load i32, i32* %opt_binary, align 8, !dbg !566
  %tobool = icmp ne i32 %6, 0, !dbg !564
  br i1 %tobool, label %if.then1, label %if.else, !dbg !567

if.then1:                                         ; preds = %if.end
  store %struct.archive_string_conv* null, %struct.archive_string_conv** %sconv, align 8, !dbg !568
  br label %if.end13, !dbg !569

if.else:                                          ; preds = %if.end
  %7 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !570
  %sconv_utf8 = getelementptr inbounds %struct.pax, %struct.pax* %7, i32 0, i32 8, !dbg !573
  %8 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_utf8, align 8, !dbg !573
  %cmp2 = icmp eq %struct.archive_string_conv* %8, null, !dbg !574
  br i1 %cmp2, label %if.then3, label %if.end11, !dbg !575

if.then3:                                         ; preds = %if.else
  %9 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !576
  %archive4 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %9, i32 0, i32 0, !dbg !578
  %call5 = call %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive* %archive4, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i32 0, i32 0), i32 1), !dbg !579
  %10 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !580
  %sconv_utf86 = getelementptr inbounds %struct.pax, %struct.pax* %10, i32 0, i32 8, !dbg !581
  store %struct.archive_string_conv* %call5, %struct.archive_string_conv** %sconv_utf86, align 8, !dbg !582
  %11 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !583
  %sconv_utf87 = getelementptr inbounds %struct.pax, %struct.pax* %11, i32 0, i32 8, !dbg !585
  %12 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_utf87, align 8, !dbg !585
  %cmp8 = icmp eq %struct.archive_string_conv* %12, null, !dbg !586
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !587

if.then9:                                         ; preds = %if.then3
  store i32 -25, i32* %retval, align 4, !dbg !588
  br label %return, !dbg !588

if.end10:                                         ; preds = %if.then3
  br label %if.end11, !dbg !589

if.end11:                                         ; preds = %if.end10, %if.else
  %13 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !590
  %sconv_utf812 = getelementptr inbounds %struct.pax, %struct.pax* %13, i32 0, i32 8, !dbg !591
  %14 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_utf812, align 8, !dbg !591
  store %struct.archive_string_conv* %14, %struct.archive_string_conv** %sconv, align 8, !dbg !592
  br label %if.end13

if.end13:                                         ; preds = %if.end11, %if.then1
  %15 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !593
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !594
  %17 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !595
  %call14 = call i32 @get_entry_hardlink(%struct.archive_write* %15, %struct.archive_entry* %16, i8** %hardlink, i64* %hardlink_length, %struct.archive_string_conv* %17), !dbg !596
  store i32 %call14, i32* %r, align 4, !dbg !597
  %18 = load i32, i32* %r, align 4, !dbg !598
  %cmp15 = icmp eq i32 %18, -30, !dbg !600
  br i1 %cmp15, label %if.then16, label %if.else17, !dbg !601

if.then16:                                        ; preds = %if.end13
  %19 = load i32, i32* %r, align 4, !dbg !602
  store i32 %19, i32* %retval, align 4, !dbg !603
  br label %return, !dbg !603

if.else17:                                        ; preds = %if.end13
  %20 = load i32, i32* %r, align 4, !dbg !604
  %cmp18 = icmp ne i32 %20, 0, !dbg !606
  br i1 %cmp18, label %if.then19, label %if.end26, !dbg !607

if.then19:                                        ; preds = %if.else17
  %21 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !608
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !610
  %call20 = call i32 @get_entry_hardlink(%struct.archive_write* %21, %struct.archive_entry* %22, i8** %hardlink, i64* %hardlink_length, %struct.archive_string_conv* null), !dbg !611
  store i32 %call20, i32* %r, align 4, !dbg !612
  %23 = load i32, i32* %r, align 4, !dbg !613
  %cmp21 = icmp eq i32 %23, -30, !dbg !615
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !616

if.then22:                                        ; preds = %if.then19
  %24 = load i32, i32* %r, align 4, !dbg !617
  store i32 %24, i32* %retval, align 4, !dbg !618
  br label %return, !dbg !618

if.end23:                                         ; preds = %if.then19
  %25 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !619
  %archive24 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %25, i32 0, i32 0, !dbg !620
  %26 = load i8*, i8** %hardlink, align 8, !dbg !621
  %27 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !622
  %call25 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %27), !dbg !623
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive24, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.13, i32 0, i32 0), i8* %26, i8* %call25), !dbg !624
  store i32 -20, i32* %ret, align 4, !dbg !625
  store %struct.archive_string_conv* null, %struct.archive_string_conv** %sconv, align 8, !dbg !626
  br label %if.end26, !dbg !627

if.end26:                                         ; preds = %if.end23, %if.else17
  br label %if.end27

if.end27:                                         ; preds = %if.end26
  %28 = load i8*, i8** %hardlink, align 8, !dbg !628
  %cmp28 = icmp eq i8* %28, null, !dbg !630
  br i1 %cmp28, label %if.then29, label %if.end55, !dbg !631

if.then29:                                        ; preds = %if.end27
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !632
  %call30 = call i32 @archive_entry_filetype(%struct.archive_entry* %29), !dbg !634
  switch i32 %call30, label %sw.default [
    i32 24576, label %sw.bb
    i32 8192, label %sw.bb
    i32 4096, label %sw.bb
    i32 40960, label %sw.bb
    i32 32768, label %sw.bb
    i32 16384, label %sw.bb31
    i32 49152, label %sw.bb50
  ], !dbg !635

sw.bb:                                            ; preds = %if.then29, %if.then29, %if.then29, %if.then29, %if.then29
  br label %sw.epilog, !dbg !636

sw.bb31:                                          ; preds = %if.then29
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !638
  %call32 = call i8* @archive_entry_pathname(%struct.archive_entry* %30), !dbg !640
  store i8* %call32, i8** %p, align 8, !dbg !641
  %31 = load i8*, i8** %p, align 8, !dbg !642
  %cmp33 = icmp ne i8* %31, null, !dbg !644
  br i1 %cmp33, label %land.lhs.true, label %if.end49, !dbg !645

land.lhs.true:                                    ; preds = %sw.bb31
  %32 = load i8*, i8** %p, align 8, !dbg !646
  %call34 = call i64 @strlen(i8* %32) #8, !dbg !648
  %sub = sub i64 %call34, 1, !dbg !649
  %33 = load i8*, i8** %p, align 8, !dbg !650
  %arrayidx = getelementptr inbounds i8, i8* %33, i64 %sub, !dbg !650
  %34 = load i8, i8* %arrayidx, align 1, !dbg !650
  %conv = sext i8 %34 to i32, !dbg !650
  %cmp35 = icmp ne i32 %conv, 47, !dbg !651
  br i1 %cmp35, label %if.then37, label %if.end49, !dbg !652

if.then37:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !653, metadata !293), !dbg !655
  br label %do.body, !dbg !656

do.body:                                          ; preds = %if.then37
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !657
  store i8* null, i8** %s, align 8, !dbg !657
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !657
  store i64 0, i64* %length, align 8, !dbg !657
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !657
  store i64 0, i64* %buffer_length, align 8, !dbg !657
  br label %do.end, !dbg !657

do.end:                                           ; preds = %do.body
  %35 = load i8*, i8** %p, align 8, !dbg !660
  %call38 = call i64 @strlen(i8* %35) #8, !dbg !661
  store i64 %call38, i64* %path_length, align 8, !dbg !662
  %36 = load i64, i64* %path_length, align 8, !dbg !663
  %add = add i64 %36, 2, !dbg !665
  %call39 = call %struct.archive_string* @archive_string_ensure(%struct.archive_string* %as, i64 %add), !dbg !666
  %cmp40 = icmp eq %struct.archive_string* %call39, null, !dbg !667
  br i1 %cmp40, label %if.then42, label %if.end44, !dbg !668

if.then42:                                        ; preds = %do.end
  %37 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !669
  %archive43 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %37, i32 0, i32 0, !dbg !671
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive43, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.3, i32 0, i32 0)), !dbg !672
  call void @archive_string_free(%struct.archive_string* %as), !dbg !673
  store i32 -30, i32* %retval, align 4, !dbg !674
  br label %return, !dbg !674

if.end44:                                         ; preds = %do.end
  %length45 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !675
  store i64 0, i64* %length45, align 8, !dbg !675
  %38 = load i8*, i8** %p, align 8, !dbg !675
  %39 = load i64, i64* %path_length, align 8, !dbg !675
  %call46 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* %38, i64 %39), !dbg !675
  %call47 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %as, i8 signext 47), !dbg !676
  %40 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !677
  %s48 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !678
  %41 = load i8*, i8** %s48, align 8, !dbg !678
  call void @archive_entry_copy_pathname(%struct.archive_entry* %40, i8* %41), !dbg !679
  call void @archive_string_free(%struct.archive_string* %as), !dbg !680
  br label %if.end49, !dbg !681

if.end49:                                         ; preds = %if.end44, %land.lhs.true, %sw.bb31
  br label %sw.epilog, !dbg !682

sw.bb50:                                          ; preds = %if.then29
  %42 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !683
  %archive51 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %42, i32 0, i32 0, !dbg !684
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive51, i32 84, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.14, i32 0, i32 0)), !dbg !685
  store i32 -25, i32* %retval, align 4, !dbg !686
  br label %return, !dbg !686

sw.default:                                       ; preds = %if.then29
  %43 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !687
  %archive52 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %43, i32 0, i32 0, !dbg !688
  %44 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !689
  %call53 = call i32 @archive_entry_filetype(%struct.archive_entry* %44), !dbg !690
  %conv54 = zext i32 %call53 to i64, !dbg !691
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive52, i32 84, i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.15, i32 0, i32 0), i64 %conv54), !dbg !692
  store i32 -25, i32* %retval, align 4, !dbg !693
  br label %return, !dbg !693

sw.epilog:                                        ; preds = %if.end49, %sw.bb
  br label %if.end55, !dbg !694

if.end55:                                         ; preds = %sw.epilog, %if.end27
  %45 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !695
  %call56 = call i8* @archive_entry_mac_metadata(%struct.archive_entry* %45, i64* %mac_metadata_size), !dbg !696
  store i8* %call56, i8** %mac_metadata, align 8, !dbg !697
  %46 = load i8*, i8** %mac_metadata, align 8, !dbg !698
  %cmp57 = icmp ne i8* %46, null, !dbg !700
  br i1 %cmp57, label %if.then59, label %if.end126, !dbg !701

if.then59:                                        ; preds = %if.end55
  call void @llvm.dbg.declare(metadata i8** %oname, metadata !702, metadata !293), !dbg !704
  call void @llvm.dbg.declare(metadata i8** %name, metadata !705, metadata !293), !dbg !706
  call void @llvm.dbg.declare(metadata i8** %bname, metadata !707, metadata !293), !dbg !708
  call void @llvm.dbg.declare(metadata i64* %name_length, metadata !709, metadata !293), !dbg !710
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %extra, metadata !711, metadata !293), !dbg !712
  %47 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !713
  %archive60 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %47, i32 0, i32 0, !dbg !714
  %call61 = call %struct.archive_entry* @archive_entry_new2(%struct.archive* %archive60), !dbg !715
  store %struct.archive_entry* %call61, %struct.archive_entry** %extra, align 8, !dbg !712
  %48 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !716
  %call62 = call i8* @archive_entry_pathname(%struct.archive_entry* %48), !dbg !717
  store i8* %call62, i8** %oname, align 8, !dbg !718
  %49 = load i8*, i8** %oname, align 8, !dbg !719
  %call63 = call i64 @strlen(i8* %49) #8, !dbg !720
  store i64 %call63, i64* %name_length, align 8, !dbg !721
  %50 = load i64, i64* %name_length, align 8, !dbg !722
  %add64 = add i64 %50, 3, !dbg !723
  %call65 = call noalias i8* @malloc(i64 %add64) #7, !dbg !724
  store i8* %call65, i8** %name, align 8, !dbg !725
  %51 = load i8*, i8** %name, align 8, !dbg !726
  %cmp66 = icmp eq i8* %51, null, !dbg !728
  br i1 %cmp66, label %if.then70, label %lor.lhs.false, !dbg !729

lor.lhs.false:                                    ; preds = %if.then59
  %52 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !730
  %cmp68 = icmp eq %struct.archive_entry* %52, null, !dbg !732
  br i1 %cmp68, label %if.then70, label %if.end71, !dbg !733

if.then70:                                        ; preds = %lor.lhs.false, %if.then59
  %53 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !734
  call void @archive_entry_free(%struct.archive_entry* %53), !dbg !736
  %54 = load i8*, i8** %name, align 8, !dbg !737
  call void @free(i8* %54) #7, !dbg !738
  store i32 -25, i32* %retval, align 4, !dbg !739
  br label %return, !dbg !739

if.end71:                                         ; preds = %lor.lhs.false
  %55 = load i8*, i8** %name, align 8, !dbg !740
  %56 = load i8*, i8** %oname, align 8, !dbg !741
  %call72 = call i8* @strcpy(i8* %55, i8* %56) #7, !dbg !742
  %57 = load i8*, i8** %name, align 8, !dbg !743
  %call73 = call i8* @strrchr(i8* %57, i32 47) #8, !dbg !744
  store i8* %call73, i8** %bname, align 8, !dbg !745
  br label %while.cond, !dbg !746

while.cond:                                       ; preds = %while.body, %if.end71
  %58 = load i8*, i8** %bname, align 8, !dbg !747
  %cmp74 = icmp ne i8* %58, null, !dbg !749
  br i1 %cmp74, label %land.rhs, label %land.end, !dbg !750

land.rhs:                                         ; preds = %while.cond
  %59 = load i8*, i8** %bname, align 8, !dbg !751
  %arrayidx76 = getelementptr inbounds i8, i8* %59, i64 1, !dbg !751
  %60 = load i8, i8* %arrayidx76, align 1, !dbg !751
  %conv77 = sext i8 %60 to i32, !dbg !751
  %cmp78 = icmp eq i32 %conv77, 0, !dbg !753
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %61 = phi i1 [ false, %while.cond ], [ %cmp78, %land.rhs ]
  br i1 %61, label %while.body, label %while.end, !dbg !754

while.body:                                       ; preds = %land.end
  %62 = load i8*, i8** %bname, align 8, !dbg !756
  store i8 0, i8* %62, align 1, !dbg !758
  %63 = load i8*, i8** %name, align 8, !dbg !759
  %call80 = call i8* @strrchr(i8* %63, i32 47) #8, !dbg !760
  store i8* %call80, i8** %bname, align 8, !dbg !761
  br label %while.cond, !dbg !762

while.end:                                        ; preds = %land.end
  %64 = load i8*, i8** %bname, align 8, !dbg !764
  %cmp81 = icmp eq i8* %64, null, !dbg !766
  br i1 %cmp81, label %if.then83, label %if.else85, !dbg !767

if.then83:                                        ; preds = %while.end
  %65 = load i8*, i8** %name, align 8, !dbg !768
  %add.ptr = getelementptr inbounds i8, i8* %65, i64 2, !dbg !770
  %66 = load i8*, i8** %name, align 8, !dbg !771
  %67 = load i64, i64* %name_length, align 8, !dbg !772
  %add84 = add i64 %67, 1, !dbg !773
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %add.ptr, i8* %66, i64 %add84, i32 1, i1 false), !dbg !774
  %68 = load i8*, i8** %name, align 8, !dbg !775
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %68, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.16, i32 0, i32 0), i64 2, i32 1, i1 false), !dbg !776
  br label %if.end90, !dbg !777

if.else85:                                        ; preds = %while.end
  %69 = load i8*, i8** %bname, align 8, !dbg !778
  %add.ptr86 = getelementptr inbounds i8, i8* %69, i64 1, !dbg !778
  store i8* %add.ptr86, i8** %bname, align 8, !dbg !778
  %70 = load i8*, i8** %bname, align 8, !dbg !780
  %add.ptr87 = getelementptr inbounds i8, i8* %70, i64 2, !dbg !781
  %71 = load i8*, i8** %bname, align 8, !dbg !782
  %72 = load i8*, i8** %bname, align 8, !dbg !783
  %call88 = call i64 @strlen(i8* %72) #8, !dbg !784
  %add89 = add i64 %call88, 1, !dbg !785
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %add.ptr87, i8* %71, i64 %add89, i32 1, i1 false), !dbg !786
  %73 = load i8*, i8** %bname, align 8, !dbg !788
  call void @llvm.memmove.p0i8.p0i8.i64(i8* %73, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.16, i32 0, i32 0), i64 2, i32 1, i1 false), !dbg !789
  br label %if.end90

if.end90:                                         ; preds = %if.else85, %if.then83
  %74 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !790
  %75 = load i8*, i8** %name, align 8, !dbg !791
  call void @archive_entry_copy_pathname(%struct.archive_entry* %74, i8* %75), !dbg !792
  %76 = load i8*, i8** %name, align 8, !dbg !793
  call void @free(i8* %76) #7, !dbg !794
  %77 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !795
  %78 = load i64, i64* %mac_metadata_size, align 8, !dbg !796
  call void @archive_entry_set_size(%struct.archive_entry* %77, i64 %78), !dbg !797
  %79 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !798
  call void @archive_entry_set_filetype(%struct.archive_entry* %79, i32 32768), !dbg !799
  %80 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !800
  %81 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !801
  %call91 = call i32 @archive_entry_perm(%struct.archive_entry* %81), !dbg !802
  call void @archive_entry_set_perm(%struct.archive_entry* %80, i32 %call91), !dbg !803
  %82 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !804
  %83 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !805
  %call92 = call i64 @archive_entry_mtime(%struct.archive_entry* %83), !dbg !806
  %84 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !807
  %call93 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %84), !dbg !808
  call void @archive_entry_set_mtime(%struct.archive_entry* %82, i64 %call92, i64 %call93), !dbg !809
  %85 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !810
  %86 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !811
  %call94 = call i64 @archive_entry_gid(%struct.archive_entry* %86), !dbg !812
  call void @archive_entry_set_gid(%struct.archive_entry* %85, i64 %call94), !dbg !813
  %87 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !814
  %88 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !815
  %call95 = call i8* @archive_entry_gname(%struct.archive_entry* %88), !dbg !816
  call void @archive_entry_set_gname(%struct.archive_entry* %87, i8* %call95), !dbg !817
  %89 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !818
  %90 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !819
  %call96 = call i64 @archive_entry_uid(%struct.archive_entry* %90), !dbg !820
  call void @archive_entry_set_uid(%struct.archive_entry* %89, i64 %call96), !dbg !821
  %91 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !822
  %92 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !823
  %call97 = call i8* @archive_entry_uname(%struct.archive_entry* %92), !dbg !824
  call void @archive_entry_set_uname(%struct.archive_entry* %91, i8* %call97), !dbg !825
  %93 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !826
  %94 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !827
  %call98 = call i32 @archive_write_pax_header(%struct.archive_write* %93, %struct.archive_entry* %94), !dbg !828
  store i32 %call98, i32* %r, align 4, !dbg !829
  %95 = load %struct.archive_entry*, %struct.archive_entry** %extra, align 8, !dbg !830
  call void @archive_entry_free(%struct.archive_entry* %95), !dbg !831
  %96 = load i32, i32* %r, align 4, !dbg !832
  %cmp99 = icmp slt i32 %96, -20, !dbg !834
  br i1 %cmp99, label %if.then101, label %if.end102, !dbg !835

if.then101:                                       ; preds = %if.end90
  %97 = load i32, i32* %r, align 4, !dbg !836
  store i32 %97, i32* %retval, align 4, !dbg !837
  br label %return, !dbg !837

if.end102:                                        ; preds = %if.end90
  %98 = load i32, i32* %r, align 4, !dbg !838
  %99 = load i32, i32* %ret, align 4, !dbg !840
  %cmp103 = icmp slt i32 %98, %99, !dbg !841
  br i1 %cmp103, label %if.then105, label %if.end106, !dbg !842

if.then105:                                       ; preds = %if.end102
  %100 = load i32, i32* %r, align 4, !dbg !843
  store i32 %100, i32* %ret, align 4, !dbg !844
  br label %if.end106, !dbg !845

if.end106:                                        ; preds = %if.then105, %if.end102
  %101 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !846
  %102 = load i8*, i8** %mac_metadata, align 8, !dbg !847
  %103 = load i64, i64* %mac_metadata_size, align 8, !dbg !848
  %call107 = call i64 @archive_write_pax_data(%struct.archive_write* %101, i8* %102, i64 %103), !dbg !849
  %conv108 = trunc i64 %call107 to i32, !dbg !850
  store i32 %conv108, i32* %r, align 4, !dbg !851
  %104 = load i32, i32* %r, align 4, !dbg !852
  %cmp109 = icmp slt i32 %104, -20, !dbg !854
  br i1 %cmp109, label %if.then111, label %if.end112, !dbg !855

if.then111:                                       ; preds = %if.end106
  %105 = load i32, i32* %r, align 4, !dbg !856
  store i32 %105, i32* %retval, align 4, !dbg !857
  br label %return, !dbg !857

if.end112:                                        ; preds = %if.end106
  %106 = load i32, i32* %r, align 4, !dbg !858
  %107 = load i32, i32* %ret, align 4, !dbg !860
  %cmp113 = icmp slt i32 %106, %107, !dbg !861
  br i1 %cmp113, label %if.then115, label %if.end116, !dbg !862

if.then115:                                       ; preds = %if.end112
  %108 = load i32, i32* %r, align 4, !dbg !863
  store i32 %108, i32* %ret, align 4, !dbg !864
  br label %if.end116, !dbg !865

if.end116:                                        ; preds = %if.then115, %if.end112
  %109 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !866
  %call117 = call i32 @archive_write_pax_finish_entry(%struct.archive_write* %109), !dbg !867
  store i32 %call117, i32* %r, align 4, !dbg !868
  %110 = load i32, i32* %r, align 4, !dbg !869
  %cmp118 = icmp slt i32 %110, -20, !dbg !871
  br i1 %cmp118, label %if.then120, label %if.end121, !dbg !872

if.then120:                                       ; preds = %if.end116
  %111 = load i32, i32* %r, align 4, !dbg !873
  store i32 %111, i32* %retval, align 4, !dbg !874
  br label %return, !dbg !874

if.end121:                                        ; preds = %if.end116
  %112 = load i32, i32* %r, align 4, !dbg !875
  %113 = load i32, i32* %ret, align 4, !dbg !877
  %cmp122 = icmp slt i32 %112, %113, !dbg !878
  br i1 %cmp122, label %if.then124, label %if.end125, !dbg !879

if.then124:                                       ; preds = %if.end121
  %114 = load i32, i32* %r, align 4, !dbg !880
  store i32 %114, i32* %ret, align 4, !dbg !881
  br label %if.end125, !dbg !882

if.end125:                                        ; preds = %if.then124, %if.end121
  br label %if.end126, !dbg !883

if.end126:                                        ; preds = %if.end125, %if.end55
  %115 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !884
  %call127 = call %struct.archive_entry* @archive_entry_clone(%struct.archive_entry* %115), !dbg !885
  store %struct.archive_entry* %call127, %struct.archive_entry** %entry_main, align 8, !dbg !886
  %116 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !887
  %cmp128 = icmp eq %struct.archive_entry* %116, null, !dbg !889
  br i1 %cmp128, label %if.then130, label %if.end132, !dbg !890

if.then130:                                       ; preds = %if.end126
  %117 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !891
  %archive131 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %117, i32 0, i32 0, !dbg !893
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive131, i32 12, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.3, i32 0, i32 0)), !dbg !894
  store i32 -30, i32* %retval, align 4, !dbg !895
  br label %return, !dbg !895

if.end132:                                        ; preds = %if.end126
  %118 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !896
  %pax_header = getelementptr inbounds %struct.pax, %struct.pax* %118, i32 0, i32 3, !dbg !896
  %length133 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pax_header, i32 0, i32 1, !dbg !896
  store i64 0, i64* %length133, align 8, !dbg !896
  %119 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !897
  %sparse_map = getelementptr inbounds %struct.pax, %struct.pax* %119, i32 0, i32 4, !dbg !897
  %length134 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %sparse_map, i32 0, i32 1, !dbg !897
  store i64 0, i64* %length134, align 8, !dbg !897
  store i64 0, i64* %sparse_total, align 8, !dbg !898
  %120 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !899
  call void @sparse_list_clear(%struct.pax* %120), !dbg !900
  %121 = load i8*, i8** %hardlink, align 8, !dbg !901
  %cmp135 = icmp eq i8* %121, null, !dbg !903
  br i1 %cmp135, label %land.lhs.true137, label %if.else143, !dbg !904

land.lhs.true137:                                 ; preds = %if.end132
  %122 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !905
  %call138 = call i32 @archive_entry_filetype(%struct.archive_entry* %122), !dbg !906
  %cmp139 = icmp eq i32 %call138, 32768, !dbg !907
  br i1 %cmp139, label %if.then141, label %if.else143, !dbg !908

if.then141:                                       ; preds = %land.lhs.true137
  %123 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !910
  %call142 = call i32 @archive_entry_sparse_reset(%struct.archive_entry* %123), !dbg !911
  store i32 %call142, i32* %sparse_count, align 4, !dbg !912
  br label %if.end144, !dbg !913

if.else143:                                       ; preds = %land.lhs.true137, %if.end132
  store i32 0, i32* %sparse_count, align 4, !dbg !914
  br label %if.end144

if.end144:                                        ; preds = %if.else143, %if.then141
  %124 = load i32, i32* %sparse_count, align 4, !dbg !915
  %tobool145 = icmp ne i32 %124, 0, !dbg !915
  br i1 %tobool145, label %if.then146, label %if.end162, !dbg !917

if.then146:                                       ; preds = %if.end144
  call void @llvm.dbg.declare(metadata i64* %offset, metadata !918, metadata !293), !dbg !920
  call void @llvm.dbg.declare(metadata i64* %length147, metadata !921, metadata !293), !dbg !922
  call void @llvm.dbg.declare(metadata i64* %last_offset, metadata !923, metadata !293), !dbg !924
  store i64 0, i64* %last_offset, align 8, !dbg !924
  br label %while.cond148, !dbg !925

while.cond148:                                    ; preds = %while.body152, %if.then146
  %125 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !926
  %call149 = call i32 @archive_entry_sparse_next(%struct.archive_entry* %125, i64* %offset, i64* %length147), !dbg !927
  %cmp150 = icmp eq i32 %call149, 0, !dbg !929
  br i1 %cmp150, label %while.body152, label %while.end154, !dbg !930

while.body152:                                    ; preds = %while.cond148
  %126 = load i64, i64* %offset, align 8, !dbg !931
  %127 = load i64, i64* %length147, align 8, !dbg !932
  %add153 = add nsw i64 %126, %127, !dbg !933
  store i64 %add153, i64* %last_offset, align 8, !dbg !934
  br label %while.cond148, !dbg !935

while.end154:                                     ; preds = %while.cond148
  %128 = load i64, i64* %last_offset, align 8, !dbg !937
  %129 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !939
  %call155 = call i64 @archive_entry_size(%struct.archive_entry* %129), !dbg !940
  %cmp156 = icmp slt i64 %128, %call155, !dbg !941
  br i1 %cmp156, label %if.then158, label %if.end160, !dbg !942

if.then158:                                       ; preds = %while.end154
  %130 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !943
  %131 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !944
  %call159 = call i64 @archive_entry_size(%struct.archive_entry* %131), !dbg !945
  call void @archive_entry_sparse_add_entry(%struct.archive_entry* %130, i64 %call159, i64 0), !dbg !946
  br label %if.end160, !dbg !946

if.end160:                                        ; preds = %if.then158, %while.end154
  %132 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !947
  %call161 = call i32 @archive_entry_sparse_reset(%struct.archive_entry* %132), !dbg !948
  store i32 %call161, i32* %sparse_count, align 4, !dbg !949
  br label %if.end162, !dbg !950

if.end162:                                        ; preds = %if.end160, %if.end144
  %133 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !951
  %134 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !952
  %135 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !953
  %call163 = call i32 @get_entry_pathname(%struct.archive_write* %133, %struct.archive_entry* %134, i8** %path, i64* %path_length, %struct.archive_string_conv* %135), !dbg !954
  store i32 %call163, i32* %r, align 4, !dbg !955
  %136 = load i32, i32* %r, align 4, !dbg !956
  %cmp164 = icmp eq i32 %136, -30, !dbg !958
  br i1 %cmp164, label %if.then166, label %if.else167, !dbg !959

if.then166:                                       ; preds = %if.end162
  %137 = load i32, i32* %r, align 4, !dbg !960
  store i32 %137, i32* %retval, align 4, !dbg !961
  br label %return, !dbg !961

if.else167:                                       ; preds = %if.end162
  %138 = load i32, i32* %r, align 4, !dbg !962
  %cmp168 = icmp ne i32 %138, 0, !dbg !964
  br i1 %cmp168, label %if.then170, label %if.end178, !dbg !965

if.then170:                                       ; preds = %if.else167
  %139 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !966
  %140 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !968
  %call171 = call i32 @get_entry_pathname(%struct.archive_write* %139, %struct.archive_entry* %140, i8** %path, i64* %path_length, %struct.archive_string_conv* null), !dbg !969
  store i32 %call171, i32* %r, align 4, !dbg !970
  %141 = load i32, i32* %r, align 4, !dbg !971
  %cmp172 = icmp eq i32 %141, -30, !dbg !973
  br i1 %cmp172, label %if.then174, label %if.end175, !dbg !974

if.then174:                                       ; preds = %if.then170
  %142 = load i32, i32* %r, align 4, !dbg !975
  store i32 %142, i32* %retval, align 4, !dbg !976
  br label %return, !dbg !976

if.end175:                                        ; preds = %if.then170
  %143 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !977
  %archive176 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %143, i32 0, i32 0, !dbg !978
  %144 = load i8*, i8** %path, align 8, !dbg !979
  %145 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !980
  %call177 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %145), !dbg !981
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive176, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.17, i32 0, i32 0), i8* %144, i8* %call177), !dbg !982
  store i32 -20, i32* %ret, align 4, !dbg !983
  store %struct.archive_string_conv* null, %struct.archive_string_conv** %sconv, align 8, !dbg !984
  br label %if.end178, !dbg !985

if.end178:                                        ; preds = %if.end175, %if.else167
  br label %if.end179

if.end179:                                        ; preds = %if.end178
  %146 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !986
  %147 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !987
  %148 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !988
  %call180 = call i32 @get_entry_uname(%struct.archive_write* %146, %struct.archive_entry* %147, i8** %uname, i64* %uname_length, %struct.archive_string_conv* %148), !dbg !989
  store i32 %call180, i32* %r, align 4, !dbg !990
  %149 = load i32, i32* %r, align 4, !dbg !991
  %cmp181 = icmp eq i32 %149, -30, !dbg !993
  br i1 %cmp181, label %if.then183, label %if.else184, !dbg !994

if.then183:                                       ; preds = %if.end179
  %150 = load i32, i32* %r, align 4, !dbg !995
  store i32 %150, i32* %retval, align 4, !dbg !996
  br label %return, !dbg !996

if.else184:                                       ; preds = %if.end179
  %151 = load i32, i32* %r, align 4, !dbg !997
  %cmp185 = icmp ne i32 %151, 0, !dbg !999
  br i1 %cmp185, label %if.then187, label %if.end195, !dbg !1000

if.then187:                                       ; preds = %if.else184
  %152 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1001
  %153 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1003
  %call188 = call i32 @get_entry_uname(%struct.archive_write* %152, %struct.archive_entry* %153, i8** %uname, i64* %uname_length, %struct.archive_string_conv* null), !dbg !1004
  store i32 %call188, i32* %r, align 4, !dbg !1005
  %154 = load i32, i32* %r, align 4, !dbg !1006
  %cmp189 = icmp eq i32 %154, -30, !dbg !1008
  br i1 %cmp189, label %if.then191, label %if.end192, !dbg !1009

if.then191:                                       ; preds = %if.then187
  %155 = load i32, i32* %r, align 4, !dbg !1010
  store i32 %155, i32* %retval, align 4, !dbg !1011
  br label %return, !dbg !1011

if.end192:                                        ; preds = %if.then187
  %156 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1012
  %archive193 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %156, i32 0, i32 0, !dbg !1013
  %157 = load i8*, i8** %uname, align 8, !dbg !1014
  %158 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1015
  %call194 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %158), !dbg !1016
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive193, i32 84, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.18, i32 0, i32 0), i8* %157, i8* %call194), !dbg !1017
  store i32 -20, i32* %ret, align 4, !dbg !1018
  store %struct.archive_string_conv* null, %struct.archive_string_conv** %sconv, align 8, !dbg !1019
  br label %if.end195, !dbg !1020

if.end195:                                        ; preds = %if.end192, %if.else184
  br label %if.end196

if.end196:                                        ; preds = %if.end195
  %159 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1021
  %160 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1022
  %161 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1023
  %call197 = call i32 @get_entry_gname(%struct.archive_write* %159, %struct.archive_entry* %160, i8** %gname, i64* %gname_length, %struct.archive_string_conv* %161), !dbg !1024
  store i32 %call197, i32* %r, align 4, !dbg !1025
  %162 = load i32, i32* %r, align 4, !dbg !1026
  %cmp198 = icmp eq i32 %162, -30, !dbg !1028
  br i1 %cmp198, label %if.then200, label %if.else201, !dbg !1029

if.then200:                                       ; preds = %if.end196
  %163 = load i32, i32* %r, align 4, !dbg !1030
  store i32 %163, i32* %retval, align 4, !dbg !1031
  br label %return, !dbg !1031

if.else201:                                       ; preds = %if.end196
  %164 = load i32, i32* %r, align 4, !dbg !1032
  %cmp202 = icmp ne i32 %164, 0, !dbg !1034
  br i1 %cmp202, label %if.then204, label %if.end212, !dbg !1035

if.then204:                                       ; preds = %if.else201
  %165 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1036
  %166 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1038
  %call205 = call i32 @get_entry_gname(%struct.archive_write* %165, %struct.archive_entry* %166, i8** %gname, i64* %gname_length, %struct.archive_string_conv* null), !dbg !1039
  store i32 %call205, i32* %r, align 4, !dbg !1040
  %167 = load i32, i32* %r, align 4, !dbg !1041
  %cmp206 = icmp eq i32 %167, -30, !dbg !1043
  br i1 %cmp206, label %if.then208, label %if.end209, !dbg !1044

if.then208:                                       ; preds = %if.then204
  %168 = load i32, i32* %r, align 4, !dbg !1045
  store i32 %168, i32* %retval, align 4, !dbg !1046
  br label %return, !dbg !1046

if.end209:                                        ; preds = %if.then204
  %169 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1047
  %archive210 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %169, i32 0, i32 0, !dbg !1048
  %170 = load i8*, i8** %gname, align 8, !dbg !1049
  %171 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1050
  %call211 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %171), !dbg !1051
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive210, i32 84, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.19, i32 0, i32 0), i8* %170, i8* %call211), !dbg !1052
  store i32 -20, i32* %ret, align 4, !dbg !1053
  store %struct.archive_string_conv* null, %struct.archive_string_conv** %sconv, align 8, !dbg !1054
  br label %if.end212, !dbg !1055

if.end212:                                        ; preds = %if.end209, %if.else201
  br label %if.end213

if.end213:                                        ; preds = %if.end212
  %172 = load i8*, i8** %hardlink, align 8, !dbg !1056
  store i8* %172, i8** %linkpath, align 8, !dbg !1057
  %173 = load i64, i64* %hardlink_length, align 8, !dbg !1058
  store i64 %173, i64* %linkpath_length, align 8, !dbg !1059
  %174 = load i8*, i8** %linkpath, align 8, !dbg !1060
  %cmp214 = icmp eq i8* %174, null, !dbg !1062
  br i1 %cmp214, label %if.then216, label %if.end234, !dbg !1063

if.then216:                                       ; preds = %if.end213
  %175 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1064
  %176 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1066
  %177 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1067
  %call217 = call i32 @get_entry_symlink(%struct.archive_write* %175, %struct.archive_entry* %176, i8** %linkpath, i64* %linkpath_length, %struct.archive_string_conv* %177), !dbg !1068
  store i32 %call217, i32* %r, align 4, !dbg !1069
  %178 = load i32, i32* %r, align 4, !dbg !1070
  %cmp218 = icmp eq i32 %178, -30, !dbg !1072
  br i1 %cmp218, label %if.then220, label %if.else221, !dbg !1073

if.then220:                                       ; preds = %if.then216
  %179 = load i32, i32* %r, align 4, !dbg !1074
  store i32 %179, i32* %retval, align 4, !dbg !1075
  br label %return, !dbg !1075

if.else221:                                       ; preds = %if.then216
  %180 = load i32, i32* %r, align 4, !dbg !1076
  %cmp222 = icmp ne i32 %180, 0, !dbg !1078
  br i1 %cmp222, label %if.then224, label %if.end232, !dbg !1079

if.then224:                                       ; preds = %if.else221
  %181 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1080
  %182 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1082
  %call225 = call i32 @get_entry_symlink(%struct.archive_write* %181, %struct.archive_entry* %182, i8** %linkpath, i64* %linkpath_length, %struct.archive_string_conv* null), !dbg !1083
  store i32 %call225, i32* %r, align 4, !dbg !1084
  %183 = load i32, i32* %r, align 4, !dbg !1085
  %cmp226 = icmp eq i32 %183, -30, !dbg !1087
  br i1 %cmp226, label %if.then228, label %if.end229, !dbg !1088

if.then228:                                       ; preds = %if.then224
  %184 = load i32, i32* %r, align 4, !dbg !1089
  store i32 %184, i32* %retval, align 4, !dbg !1090
  br label %return, !dbg !1090

if.end229:                                        ; preds = %if.then224
  %185 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1091
  %archive230 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %185, i32 0, i32 0, !dbg !1092
  %186 = load i8*, i8** %linkpath, align 8, !dbg !1093
  %187 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1094
  %call231 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %187), !dbg !1095
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive230, i32 84, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.13, i32 0, i32 0), i8* %186, i8* %call231), !dbg !1096
  store i32 -20, i32* %ret, align 4, !dbg !1097
  store %struct.archive_string_conv* null, %struct.archive_string_conv** %sconv, align 8, !dbg !1098
  br label %if.end232, !dbg !1099

if.end232:                                        ; preds = %if.end229, %if.else221
  br label %if.end233

if.end233:                                        ; preds = %if.end232
  br label %if.end234, !dbg !1100

if.end234:                                        ; preds = %if.end233, %if.end213
  %188 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1101
  %cmp235 = icmp eq %struct.archive_string_conv* %188, null, !dbg !1103
  br i1 %cmp235, label %land.lhs.true237, label %if.end265, !dbg !1104

land.lhs.true237:                                 ; preds = %if.end234
  %189 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1105
  %opt_binary238 = getelementptr inbounds %struct.pax, %struct.pax* %189, i32 0, i32 9, !dbg !1107
  %190 = load i32, i32* %opt_binary238, align 8, !dbg !1107
  %tobool239 = icmp ne i32 %190, 0, !dbg !1105
  br i1 %tobool239, label %if.end265, label %if.then240, !dbg !1108

if.then240:                                       ; preds = %land.lhs.true237
  %191 = load i8*, i8** %hardlink, align 8, !dbg !1109
  %cmp241 = icmp ne i8* %191, null, !dbg !1112
  br i1 %cmp241, label %if.then243, label %if.end249, !dbg !1113

if.then243:                                       ; preds = %if.then240
  %192 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1114
  %193 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1116
  %call244 = call i32 @get_entry_hardlink(%struct.archive_write* %192, %struct.archive_entry* %193, i8** %hardlink, i64* %hardlink_length, %struct.archive_string_conv* null), !dbg !1117
  store i32 %call244, i32* %r, align 4, !dbg !1118
  %194 = load i32, i32* %r, align 4, !dbg !1119
  %cmp245 = icmp eq i32 %194, -30, !dbg !1121
  br i1 %cmp245, label %if.then247, label %if.end248, !dbg !1122

if.then247:                                       ; preds = %if.then243
  %195 = load i32, i32* %r, align 4, !dbg !1123
  store i32 %195, i32* %retval, align 4, !dbg !1124
  br label %return, !dbg !1124

if.end248:                                        ; preds = %if.then243
  %196 = load i8*, i8** %hardlink, align 8, !dbg !1125
  store i8* %196, i8** %linkpath, align 8, !dbg !1126
  %197 = load i64, i64* %hardlink_length, align 8, !dbg !1127
  store i64 %197, i64* %linkpath_length, align 8, !dbg !1128
  br label %if.end249, !dbg !1129

if.end249:                                        ; preds = %if.end248, %if.then240
  %198 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1130
  %199 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1131
  %call250 = call i32 @get_entry_pathname(%struct.archive_write* %198, %struct.archive_entry* %199, i8** %path, i64* %path_length, %struct.archive_string_conv* null), !dbg !1132
  store i32 %call250, i32* %r, align 4, !dbg !1133
  %200 = load i32, i32* %r, align 4, !dbg !1134
  %cmp251 = icmp eq i32 %200, -30, !dbg !1136
  br i1 %cmp251, label %if.then253, label %if.end254, !dbg !1137

if.then253:                                       ; preds = %if.end249
  %201 = load i32, i32* %r, align 4, !dbg !1138
  store i32 %201, i32* %retval, align 4, !dbg !1139
  br label %return, !dbg !1139

if.end254:                                        ; preds = %if.end249
  %202 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1140
  %203 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1141
  %call255 = call i32 @get_entry_uname(%struct.archive_write* %202, %struct.archive_entry* %203, i8** %uname, i64* %uname_length, %struct.archive_string_conv* null), !dbg !1142
  store i32 %call255, i32* %r, align 4, !dbg !1143
  %204 = load i32, i32* %r, align 4, !dbg !1144
  %cmp256 = icmp eq i32 %204, -30, !dbg !1146
  br i1 %cmp256, label %if.then258, label %if.end259, !dbg !1147

if.then258:                                       ; preds = %if.end254
  %205 = load i32, i32* %r, align 4, !dbg !1148
  store i32 %205, i32* %retval, align 4, !dbg !1149
  br label %return, !dbg !1149

if.end259:                                        ; preds = %if.end254
  %206 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1150
  %207 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1151
  %call260 = call i32 @get_entry_gname(%struct.archive_write* %206, %struct.archive_entry* %207, i8** %gname, i64* %gname_length, %struct.archive_string_conv* null), !dbg !1152
  store i32 %call260, i32* %r, align 4, !dbg !1153
  %208 = load i32, i32* %r, align 4, !dbg !1154
  %cmp261 = icmp eq i32 %208, -30, !dbg !1156
  br i1 %cmp261, label %if.then263, label %if.end264, !dbg !1157

if.then263:                                       ; preds = %if.end259
  %209 = load i32, i32* %r, align 4, !dbg !1158
  store i32 %209, i32* %retval, align 4, !dbg !1159
  br label %return, !dbg !1159

if.end264:                                        ; preds = %if.end259
  br label %if.end265, !dbg !1160

if.end265:                                        ; preds = %if.end264, %land.lhs.true237, %if.end234
  %210 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !1161
  %cmp266 = icmp eq %struct.archive_string_conv* %210, null, !dbg !1163
  br i1 %cmp266, label %if.then268, label %if.end270, !dbg !1164

if.then268:                                       ; preds = %if.end265
  %211 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1165
  %pax_header269 = getelementptr inbounds %struct.pax, %struct.pax* %211, i32 0, i32 3, !dbg !1166
  call void @add_pax_attr(%struct.archive_string* %pax_header269, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.8, i32 0, i32 0)), !dbg !1167
  br label %if.end270, !dbg !1167

if.end270:                                        ; preds = %if.then268, %if.end265
  %212 = load i8*, i8** %path, align 8, !dbg !1168
  %call271 = call i32 @has_non_ASCII(i8* %212), !dbg !1170
  %tobool272 = icmp ne i32 %call271, 0, !dbg !1170
  br i1 %tobool272, label %if.then273, label %if.else276, !dbg !1171

if.then273:                                       ; preds = %if.end270
  %213 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1172
  %pax_header274 = getelementptr inbounds %struct.pax, %struct.pax* %213, i32 0, i32 3, !dbg !1174
  %214 = load i8*, i8** %path, align 8, !dbg !1175
  call void @add_pax_attr(%struct.archive_string* %pax_header274, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i32 0, i32 0), i8* %214), !dbg !1176
  %215 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1177
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %ustar_entry_name, i32 0, i32 0, !dbg !1178
  %216 = load i8*, i8** %path, align 8, !dbg !1179
  %217 = load i64, i64* %path_length, align 8, !dbg !1180
  %call275 = call i8* @build_ustar_entry_name(i8* %arraydecay, i8* %216, i64 %217, i8* null), !dbg !1181
  call void @archive_entry_set_pathname(%struct.archive_entry* %215, i8* %call275), !dbg !1182
  store i32 1, i32* %need_extension, align 4, !dbg !1183
  br label %if.end307, !dbg !1184

if.else276:                                       ; preds = %if.end270
  %218 = load i64, i64* %path_length, align 8, !dbg !1185
  %cmp277 = icmp ule i64 %218, 100, !dbg !1188
  br i1 %cmp277, label %if.then279, label %if.else280, !dbg !1189

if.then279:                                       ; preds = %if.else276
  br label %if.end306, !dbg !1190

if.else280:                                       ; preds = %if.else276
  %219 = load i8*, i8** %path, align 8, !dbg !1192
  %220 = load i64, i64* %path_length, align 8, !dbg !1194
  %add.ptr281 = getelementptr inbounds i8, i8* %219, i64 %220, !dbg !1195
  %add.ptr282 = getelementptr inbounds i8, i8* %add.ptr281, i64 -100, !dbg !1196
  %add.ptr283 = getelementptr inbounds i8, i8* %add.ptr282, i64 -1, !dbg !1197
  %call284 = call i8* @strchr(i8* %add.ptr283, i32 47) #8, !dbg !1198
  store i8* %call284, i8** %suffix, align 8, !dbg !1199
  %221 = load i8*, i8** %suffix, align 8, !dbg !1200
  %222 = load i8*, i8** %path, align 8, !dbg !1202
  %cmp285 = icmp eq i8* %221, %222, !dbg !1203
  br i1 %cmp285, label %if.then287, label %if.end290, !dbg !1204

if.then287:                                       ; preds = %if.else280
  %223 = load i8*, i8** %suffix, align 8, !dbg !1205
  %add.ptr288 = getelementptr inbounds i8, i8* %223, i64 1, !dbg !1206
  %call289 = call i8* @strchr(i8* %add.ptr288, i32 47) #8, !dbg !1207
  store i8* %call289, i8** %suffix, align 8, !dbg !1208
  br label %if.end290, !dbg !1209

if.end290:                                        ; preds = %if.then287, %if.else280
  %224 = load i8*, i8** %suffix, align 8, !dbg !1210
  %cmp291 = icmp eq i8* %224, null, !dbg !1212
  br i1 %cmp291, label %if.then301, label %lor.lhs.false293, !dbg !1213

lor.lhs.false293:                                 ; preds = %if.end290
  %225 = load i8*, i8** %suffix, align 8, !dbg !1214
  %arrayidx294 = getelementptr inbounds i8, i8* %225, i64 1, !dbg !1214
  %226 = load i8, i8* %arrayidx294, align 1, !dbg !1214
  %conv295 = sext i8 %226 to i32, !dbg !1214
  %cmp296 = icmp eq i32 %conv295, 0, !dbg !1216
  br i1 %cmp296, label %if.then301, label %lor.lhs.false298, !dbg !1217

lor.lhs.false298:                                 ; preds = %lor.lhs.false293
  %227 = load i8*, i8** %suffix, align 8, !dbg !1218
  %228 = load i8*, i8** %path, align 8, !dbg !1219
  %sub.ptr.lhs.cast = ptrtoint i8* %227 to i64, !dbg !1220
  %sub.ptr.rhs.cast = ptrtoint i8* %228 to i64, !dbg !1220
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1220
  %cmp299 = icmp sgt i64 %sub.ptr.sub, 155, !dbg !1221
  br i1 %cmp299, label %if.then301, label %if.end305, !dbg !1222

if.then301:                                       ; preds = %lor.lhs.false298, %lor.lhs.false293, %if.end290
  %229 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1224
  %pax_header302 = getelementptr inbounds %struct.pax, %struct.pax* %229, i32 0, i32 3, !dbg !1226
  %230 = load i8*, i8** %path, align 8, !dbg !1227
  call void @add_pax_attr(%struct.archive_string* %pax_header302, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i32 0, i32 0), i8* %230), !dbg !1228
  %231 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1229
  %arraydecay303 = getelementptr inbounds [256 x i8], [256 x i8]* %ustar_entry_name, i32 0, i32 0, !dbg !1230
  %232 = load i8*, i8** %path, align 8, !dbg !1231
  %233 = load i64, i64* %path_length, align 8, !dbg !1232
  %call304 = call i8* @build_ustar_entry_name(i8* %arraydecay303, i8* %232, i64 %233, i8* null), !dbg !1233
  call void @archive_entry_set_pathname(%struct.archive_entry* %231, i8* %call304), !dbg !1234
  store i32 1, i32* %need_extension, align 4, !dbg !1235
  br label %if.end305, !dbg !1236

if.end305:                                        ; preds = %if.then301, %lor.lhs.false298
  br label %if.end306

if.end306:                                        ; preds = %if.end305, %if.then279
  br label %if.end307

if.end307:                                        ; preds = %if.end306, %if.then273
  %234 = load i8*, i8** %linkpath, align 8, !dbg !1237
  %cmp308 = icmp ne i8* %234, null, !dbg !1239
  br i1 %cmp308, label %if.then310, label %if.end328, !dbg !1240

if.then310:                                       ; preds = %if.end307
  %235 = load i64, i64* %linkpath_length, align 8, !dbg !1241
  %cmp311 = icmp ugt i64 %235, 100, !dbg !1244
  br i1 %cmp311, label %if.then316, label %lor.lhs.false313, !dbg !1245

lor.lhs.false313:                                 ; preds = %if.then310
  %236 = load i8*, i8** %linkpath, align 8, !dbg !1246
  %call314 = call i32 @has_non_ASCII(i8* %236), !dbg !1248
  %tobool315 = icmp ne i32 %call314, 0, !dbg !1248
  br i1 %tobool315, label %if.then316, label %if.end327, !dbg !1249

if.then316:                                       ; preds = %lor.lhs.false313, %if.then310
  %237 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1250
  %pax_header317 = getelementptr inbounds %struct.pax, %struct.pax* %237, i32 0, i32 3, !dbg !1252
  %238 = load i8*, i8** %linkpath, align 8, !dbg !1253
  call void @add_pax_attr(%struct.archive_string* %pax_header317, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.21, i32 0, i32 0), i8* %238), !dbg !1254
  %239 = load i64, i64* %linkpath_length, align 8, !dbg !1255
  %cmp318 = icmp ugt i64 %239, 100, !dbg !1257
  br i1 %cmp318, label %if.then320, label %if.end326, !dbg !1258

if.then320:                                       ; preds = %if.then316
  %240 = load i8*, i8** %hardlink, align 8, !dbg !1259
  %cmp321 = icmp ne i8* %240, null, !dbg !1262
  br i1 %cmp321, label %if.then323, label %if.else324, !dbg !1263

if.then323:                                       ; preds = %if.then320
  %241 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1264
  call void @archive_entry_set_hardlink(%struct.archive_entry* %241, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.22, i32 0, i32 0)), !dbg !1265
  br label %if.end325, !dbg !1265

if.else324:                                       ; preds = %if.then320
  %242 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1266
  call void @archive_entry_set_symlink(%struct.archive_entry* %242, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.23, i32 0, i32 0)), !dbg !1267
  br label %if.end325

if.end325:                                        ; preds = %if.else324, %if.then323
  br label %if.end326, !dbg !1268

if.end326:                                        ; preds = %if.end325, %if.then316
  store i32 1, i32* %need_extension, align 4, !dbg !1269
  br label %if.end327, !dbg !1270

if.end327:                                        ; preds = %if.end326, %lor.lhs.false313
  br label %if.end328, !dbg !1271

if.end328:                                        ; preds = %if.end327, %if.end307
  br label %do.body329, !dbg !1272

do.body329:                                       ; preds = %if.end328
  %s330 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_name, i32 0, i32 0, !dbg !1273
  store i8* null, i8** %s330, align 8, !dbg !1273
  %length331 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_name, i32 0, i32 1, !dbg !1273
  store i64 0, i64* %length331, align 8, !dbg !1273
  %buffer_length332 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_name, i32 0, i32 2, !dbg !1273
  store i64 0, i64* %buffer_length332, align 8, !dbg !1273
  br label %do.end333, !dbg !1273

do.end333:                                        ; preds = %do.body329
  %length334 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_name, i32 0, i32 1, !dbg !1276
  store i64 0, i64* %length334, align 8, !dbg !1276
  %243 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1276
  %call335 = call i8* @archive_entry_pathname(%struct.archive_entry* %243), !dbg !1276
  %244 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1276
  %call336 = call i8* @archive_entry_pathname(%struct.archive_entry* %244), !dbg !1277
  %cmp337 = icmp eq i8* %call336, null, !dbg !1276
  br i1 %cmp337, label %cond.true, label %cond.false, !dbg !1276

cond.true:                                        ; preds = %do.end333
  br label %cond.end, !dbg !1279

cond.false:                                       ; preds = %do.end333
  %245 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1280
  %call339 = call i8* @archive_entry_pathname(%struct.archive_entry* %245), !dbg !1280
  %call340 = call i64 @strlen(i8* %call339) #8, !dbg !1282
  br label %cond.end, !dbg !1280

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call340, %cond.false ], !dbg !1284
  %call341 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %entry_name, i8* %call335, i64 %cond), !dbg !1284
  %246 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1286
  %call342 = call i64 @archive_entry_size(%struct.archive_entry* %246), !dbg !1288
  %cmp343 = icmp sge i64 %call342, 8589934592, !dbg !1289
  br i1 %cmp343, label %if.then345, label %if.end348, !dbg !1290

if.then345:                                       ; preds = %cond.end
  %247 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1291
  %pax_header346 = getelementptr inbounds %struct.pax, %struct.pax* %247, i32 0, i32 3, !dbg !1293
  %248 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1294
  %call347 = call i64 @archive_entry_size(%struct.archive_entry* %248), !dbg !1295
  call void @add_pax_attr_int(%struct.archive_string* %pax_header346, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.24, i32 0, i32 0), i64 %call347), !dbg !1296
  store i32 1, i32* %need_extension, align 4, !dbg !1297
  br label %if.end348, !dbg !1298

if.end348:                                        ; preds = %if.then345, %cond.end
  %249 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1299
  %call349 = call i64 @archive_entry_gid(%struct.archive_entry* %249), !dbg !1301
  %conv350 = trunc i64 %call349 to i32, !dbg !1302
  %cmp351 = icmp uge i32 %conv350, 262144, !dbg !1303
  br i1 %cmp351, label %if.then353, label %if.end356, !dbg !1304

if.then353:                                       ; preds = %if.end348
  %250 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1305
  %pax_header354 = getelementptr inbounds %struct.pax, %struct.pax* %250, i32 0, i32 3, !dbg !1307
  %251 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1308
  %call355 = call i64 @archive_entry_gid(%struct.archive_entry* %251), !dbg !1309
  call void @add_pax_attr_int(%struct.archive_string* %pax_header354, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.25, i32 0, i32 0), i64 %call355), !dbg !1310
  store i32 1, i32* %need_extension, align 4, !dbg !1311
  br label %if.end356, !dbg !1312

if.end356:                                        ; preds = %if.then353, %if.end348
  %252 = load i8*, i8** %gname, align 8, !dbg !1313
  %cmp357 = icmp ne i8* %252, null, !dbg !1315
  br i1 %cmp357, label %if.then359, label %if.end368, !dbg !1316

if.then359:                                       ; preds = %if.end356
  %253 = load i64, i64* %gname_length, align 8, !dbg !1317
  %cmp360 = icmp ugt i64 %253, 31, !dbg !1320
  br i1 %cmp360, label %if.then365, label %lor.lhs.false362, !dbg !1321

lor.lhs.false362:                                 ; preds = %if.then359
  %254 = load i8*, i8** %gname, align 8, !dbg !1322
  %call363 = call i32 @has_non_ASCII(i8* %254), !dbg !1324
  %tobool364 = icmp ne i32 %call363, 0, !dbg !1324
  br i1 %tobool364, label %if.then365, label %if.end367, !dbg !1325

if.then365:                                       ; preds = %lor.lhs.false362, %if.then359
  %255 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1326
  %pax_header366 = getelementptr inbounds %struct.pax, %struct.pax* %255, i32 0, i32 3, !dbg !1328
  %256 = load i8*, i8** %gname, align 8, !dbg !1329
  call void @add_pax_attr(%struct.archive_string* %pax_header366, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.26, i32 0, i32 0), i8* %256), !dbg !1330
  store i32 1, i32* %need_extension, align 4, !dbg !1331
  br label %if.end367, !dbg !1332

if.end367:                                        ; preds = %if.then365, %lor.lhs.false362
  br label %if.end368, !dbg !1333

if.end368:                                        ; preds = %if.end367, %if.end356
  %257 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1334
  %call369 = call i64 @archive_entry_uid(%struct.archive_entry* %257), !dbg !1336
  %conv370 = trunc i64 %call369 to i32, !dbg !1337
  %cmp371 = icmp uge i32 %conv370, 262144, !dbg !1338
  br i1 %cmp371, label %if.then373, label %if.end376, !dbg !1339

if.then373:                                       ; preds = %if.end368
  %258 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1340
  %pax_header374 = getelementptr inbounds %struct.pax, %struct.pax* %258, i32 0, i32 3, !dbg !1342
  %259 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1343
  %call375 = call i64 @archive_entry_uid(%struct.archive_entry* %259), !dbg !1344
  call void @add_pax_attr_int(%struct.archive_string* %pax_header374, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.27, i32 0, i32 0), i64 %call375), !dbg !1345
  store i32 1, i32* %need_extension, align 4, !dbg !1346
  br label %if.end376, !dbg !1347

if.end376:                                        ; preds = %if.then373, %if.end368
  %260 = load i8*, i8** %uname, align 8, !dbg !1348
  %cmp377 = icmp ne i8* %260, null, !dbg !1350
  br i1 %cmp377, label %if.then379, label %if.end388, !dbg !1351

if.then379:                                       ; preds = %if.end376
  %261 = load i64, i64* %uname_length, align 8, !dbg !1352
  %cmp380 = icmp ugt i64 %261, 31, !dbg !1355
  br i1 %cmp380, label %if.then385, label %lor.lhs.false382, !dbg !1356

lor.lhs.false382:                                 ; preds = %if.then379
  %262 = load i8*, i8** %uname, align 8, !dbg !1357
  %call383 = call i32 @has_non_ASCII(i8* %262), !dbg !1359
  %tobool384 = icmp ne i32 %call383, 0, !dbg !1359
  br i1 %tobool384, label %if.then385, label %if.end387, !dbg !1360

if.then385:                                       ; preds = %lor.lhs.false382, %if.then379
  %263 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1361
  %pax_header386 = getelementptr inbounds %struct.pax, %struct.pax* %263, i32 0, i32 3, !dbg !1363
  %264 = load i8*, i8** %uname, align 8, !dbg !1364
  call void @add_pax_attr(%struct.archive_string* %pax_header386, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.28, i32 0, i32 0), i8* %264), !dbg !1365
  store i32 1, i32* %need_extension, align 4, !dbg !1366
  br label %if.end387, !dbg !1367

if.end387:                                        ; preds = %if.then385, %lor.lhs.false382
  br label %if.end388, !dbg !1368

if.end388:                                        ; preds = %if.end387, %if.end376
  %265 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1369
  %call389 = call i32 @archive_entry_filetype(%struct.archive_entry* %265), !dbg !1371
  %cmp390 = icmp eq i32 %call389, 24576, !dbg !1372
  br i1 %cmp390, label %if.then396, label %lor.lhs.false392, !dbg !1373

lor.lhs.false392:                                 ; preds = %if.end388
  %266 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1374
  %call393 = call i32 @archive_entry_filetype(%struct.archive_entry* %266), !dbg !1376
  %cmp394 = icmp eq i32 %call393, 8192, !dbg !1377
  br i1 %cmp394, label %if.then396, label %if.end413, !dbg !1378

if.then396:                                       ; preds = %lor.lhs.false392, %if.end388
  call void @llvm.dbg.declare(metadata i32* %rdevmajor, metadata !1379, metadata !293), !dbg !1381
  call void @llvm.dbg.declare(metadata i32* %rdevminor, metadata !1382, metadata !293), !dbg !1383
  %267 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1384
  %call397 = call i64 @archive_entry_rdevmajor(%struct.archive_entry* %267), !dbg !1385
  %conv398 = trunc i64 %call397 to i32, !dbg !1385
  store i32 %conv398, i32* %rdevmajor, align 4, !dbg !1386
  %268 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1387
  %call399 = call i64 @archive_entry_rdevminor(%struct.archive_entry* %268), !dbg !1388
  %conv400 = trunc i64 %call399 to i32, !dbg !1388
  store i32 %conv400, i32* %rdevminor, align 4, !dbg !1389
  %269 = load i32, i32* %rdevmajor, align 4, !dbg !1390
  %cmp401 = icmp sge i32 %269, 262144, !dbg !1392
  br i1 %cmp401, label %if.then403, label %if.end406, !dbg !1393

if.then403:                                       ; preds = %if.then396
  %270 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1394
  %pax_header404 = getelementptr inbounds %struct.pax, %struct.pax* %270, i32 0, i32 3, !dbg !1396
  %271 = load i32, i32* %rdevmajor, align 4, !dbg !1397
  %conv405 = sext i32 %271 to i64, !dbg !1397
  call void @add_pax_attr_int(%struct.archive_string* %pax_header404, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.29, i32 0, i32 0), i64 %conv405), !dbg !1398
  store i32 1, i32* %need_extension, align 4, !dbg !1399
  br label %if.end406, !dbg !1400

if.end406:                                        ; preds = %if.then403, %if.then396
  %272 = load i32, i32* %rdevminor, align 4, !dbg !1401
  %cmp407 = icmp sge i32 %272, 262144, !dbg !1403
  br i1 %cmp407, label %if.then409, label %if.end412, !dbg !1404

if.then409:                                       ; preds = %if.end406
  %273 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1405
  %pax_header410 = getelementptr inbounds %struct.pax, %struct.pax* %273, i32 0, i32 3, !dbg !1407
  %274 = load i32, i32* %rdevminor, align 4, !dbg !1408
  %conv411 = sext i32 %274 to i64, !dbg !1408
  call void @add_pax_attr_int(%struct.archive_string* %pax_header410, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.30, i32 0, i32 0), i64 %conv411), !dbg !1409
  store i32 1, i32* %need_extension, align 4, !dbg !1410
  br label %if.end412, !dbg !1411

if.end412:                                        ; preds = %if.then409, %if.end406
  br label %if.end413, !dbg !1412

if.end413:                                        ; preds = %if.end412, %lor.lhs.false392
  %275 = load i32, i32* %need_extension, align 4, !dbg !1413
  %tobool414 = icmp ne i32 %275, 0, !dbg !1413
  br i1 %tobool414, label %if.end424, label %land.lhs.true415, !dbg !1415

land.lhs.true415:                                 ; preds = %if.end413
  %276 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1416
  %call416 = call i64 @archive_entry_mtime(%struct.archive_entry* %276), !dbg !1417
  %cmp417 = icmp slt i64 %call416, 0, !dbg !1418
  br i1 %cmp417, label %if.then423, label %lor.lhs.false419, !dbg !1419

lor.lhs.false419:                                 ; preds = %land.lhs.true415
  %277 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1420
  %call420 = call i64 @archive_entry_mtime(%struct.archive_entry* %277), !dbg !1422
  %cmp421 = icmp sge i64 %call420, 2147483647, !dbg !1423
  br i1 %cmp421, label %if.then423, label %if.end424, !dbg !1424

if.then423:                                       ; preds = %lor.lhs.false419, %land.lhs.true415
  store i32 1, i32* %need_extension, align 4, !dbg !1425
  br label %if.end424, !dbg !1426

if.end424:                                        ; preds = %if.then423, %lor.lhs.false419, %if.end413
  %278 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1427
  %call425 = call i8* @archive_entry_fflags_text(%struct.archive_entry* %278), !dbg !1428
  store i8* %call425, i8** %p, align 8, !dbg !1429
  %279 = load i32, i32* %need_extension, align 4, !dbg !1430
  %tobool426 = icmp ne i32 %279, 0, !dbg !1430
  br i1 %tobool426, label %if.end435, label %land.lhs.true427, !dbg !1432

land.lhs.true427:                                 ; preds = %if.end424
  %280 = load i8*, i8** %p, align 8, !dbg !1433
  %cmp428 = icmp ne i8* %280, null, !dbg !1435
  br i1 %cmp428, label %land.lhs.true430, label %if.end435, !dbg !1436

land.lhs.true430:                                 ; preds = %land.lhs.true427
  %281 = load i8*, i8** %p, align 8, !dbg !1437
  %282 = load i8, i8* %281, align 1, !dbg !1439
  %conv431 = sext i8 %282 to i32, !dbg !1439
  %cmp432 = icmp ne i32 %conv431, 0, !dbg !1440
  br i1 %cmp432, label %if.then434, label %if.end435, !dbg !1441

if.then434:                                       ; preds = %land.lhs.true430
  store i32 1, i32* %need_extension, align 4, !dbg !1442
  br label %if.end435, !dbg !1443

if.end435:                                        ; preds = %if.then434, %land.lhs.true430, %land.lhs.true427, %if.end424
  %283 = load i32, i32* %need_extension, align 4, !dbg !1444
  %tobool436 = icmp ne i32 %283, 0, !dbg !1444
  br i1 %tobool436, label %if.end442, label %land.lhs.true437, !dbg !1446

land.lhs.true437:                                 ; preds = %if.end435
  %284 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !1447
  %call438 = call i32 @archive_entry_xattr_count(%struct.archive_entry* %284), !dbg !1449
  %cmp439 = icmp sgt i32 %call438, 0, !dbg !1450
  br i1 %cmp439, label %if.then441, label %if.end442, !dbg !1451

if.then441:                                       ; preds = %land.lhs.true437
  store i32 1, i32* %need_extension, align 4, !dbg !1452
  br label %if.end442, !dbg !1453

if.end442:                                        ; preds = %if.then441, %land.lhs.true437, %if.end435
  %285 = load i32, i32* %need_extension, align 4, !dbg !1454
  %tobool443 = icmp ne i32 %285, 0, !dbg !1454
  br i1 %tobool443, label %if.end448, label %land.lhs.true444, !dbg !1456

land.lhs.true444:                                 ; preds = %if.end442
  %286 = load i32, i32* %sparse_count, align 4, !dbg !1457
  %cmp445 = icmp sgt i32 %286, 0, !dbg !1459
  br i1 %cmp445, label %if.then447, label %if.end448, !dbg !1460

if.then447:                                       ; preds = %land.lhs.true444
  store i32 1, i32* %need_extension, align 4, !dbg !1461
  br label %if.end448, !dbg !1462

if.end448:                                        ; preds = %if.then447, %land.lhs.true444, %if.end442
  %287 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !1463
  %call449 = call i32 @archive_entry_acl_types(%struct.archive_entry* %287), !dbg !1464
  store i32 %call449, i32* %acl_types, align 4, !dbg !1465
  %288 = load i32, i32* %need_extension, align 4, !dbg !1466
  %tobool450 = icmp ne i32 %288, 0, !dbg !1466
  br i1 %tobool450, label %if.end455, label %land.lhs.true451, !dbg !1468

land.lhs.true451:                                 ; preds = %if.end448
  %289 = load i32, i32* %acl_types, align 4, !dbg !1469
  %cmp452 = icmp ne i32 %289, 0, !dbg !1471
  br i1 %cmp452, label %if.then454, label %if.end455, !dbg !1472

if.then454:                                       ; preds = %land.lhs.true451
  store i32 1, i32* %need_extension, align 4, !dbg !1473
  br label %if.end455, !dbg !1474

if.end455:                                        ; preds = %if.then454, %land.lhs.true451, %if.end448
  %290 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1475
  %archive456 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %290, i32 0, i32 0, !dbg !1477
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive456, i32 0, i32 3, !dbg !1478
  %291 = load i32, i32* %archive_format, align 8, !dbg !1478
  %cmp457 = icmp ne i32 %291, 196611, !dbg !1479
  br i1 %cmp457, label %if.then459, label %if.end496, !dbg !1480

if.then459:                                       ; preds = %if.end455
  %292 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1481
  %call460 = call i64 @archive_entry_ctime(%struct.archive_entry* %292), !dbg !1484
  %cmp461 = icmp ne i64 %call460, 0, !dbg !1485
  br i1 %cmp461, label %if.then467, label %lor.lhs.false463, !dbg !1486

lor.lhs.false463:                                 ; preds = %if.then459
  %293 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1487
  %call464 = call i64 @archive_entry_ctime_nsec(%struct.archive_entry* %293), !dbg !1488
  %cmp465 = icmp ne i64 %call464, 0, !dbg !1489
  br i1 %cmp465, label %if.then467, label %if.end471, !dbg !1490

if.then467:                                       ; preds = %lor.lhs.false463, %if.then459
  %294 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1492
  %pax_header468 = getelementptr inbounds %struct.pax, %struct.pax* %294, i32 0, i32 3, !dbg !1493
  %295 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1494
  %call469 = call i64 @archive_entry_ctime(%struct.archive_entry* %295), !dbg !1495
  %296 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1496
  %call470 = call i64 @archive_entry_ctime_nsec(%struct.archive_entry* %296), !dbg !1497
  call void @add_pax_attr_time(%struct.archive_string* %pax_header468, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.31, i32 0, i32 0), i64 %call469, i64 %call470), !dbg !1498
  br label %if.end471, !dbg !1498

if.end471:                                        ; preds = %if.then467, %lor.lhs.false463
  %297 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1499
  %call472 = call i64 @archive_entry_atime(%struct.archive_entry* %297), !dbg !1501
  %cmp473 = icmp ne i64 %call472, 0, !dbg !1502
  br i1 %cmp473, label %if.then479, label %lor.lhs.false475, !dbg !1503

lor.lhs.false475:                                 ; preds = %if.end471
  %298 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1504
  %call476 = call i64 @archive_entry_atime_nsec(%struct.archive_entry* %298), !dbg !1505
  %cmp477 = icmp ne i64 %call476, 0, !dbg !1506
  br i1 %cmp477, label %if.then479, label %if.end483, !dbg !1507

if.then479:                                       ; preds = %lor.lhs.false475, %if.end471
  %299 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1508
  %pax_header480 = getelementptr inbounds %struct.pax, %struct.pax* %299, i32 0, i32 3, !dbg !1509
  %300 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1510
  %call481 = call i64 @archive_entry_atime(%struct.archive_entry* %300), !dbg !1511
  %301 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1512
  %call482 = call i64 @archive_entry_atime_nsec(%struct.archive_entry* %301), !dbg !1513
  call void @add_pax_attr_time(%struct.archive_string* %pax_header480, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.32, i32 0, i32 0), i64 %call481, i64 %call482), !dbg !1514
  br label %if.end483, !dbg !1514

if.end483:                                        ; preds = %if.then479, %lor.lhs.false475
  %302 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1515
  %call484 = call i32 @archive_entry_birthtime_is_set(%struct.archive_entry* %302), !dbg !1517
  %tobool485 = icmp ne i32 %call484, 0, !dbg !1517
  br i1 %tobool485, label %land.lhs.true486, label %if.end495, !dbg !1518

land.lhs.true486:                                 ; preds = %if.end483
  %303 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1519
  %call487 = call i64 @archive_entry_birthtime(%struct.archive_entry* %303), !dbg !1520
  %304 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1521
  %call488 = call i64 @archive_entry_mtime(%struct.archive_entry* %304), !dbg !1522
  %cmp489 = icmp slt i64 %call487, %call488, !dbg !1523
  br i1 %cmp489, label %if.then491, label %if.end495, !dbg !1524

if.then491:                                       ; preds = %land.lhs.true486
  %305 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1525
  %pax_header492 = getelementptr inbounds %struct.pax, %struct.pax* %305, i32 0, i32 3, !dbg !1526
  %306 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1527
  %call493 = call i64 @archive_entry_birthtime(%struct.archive_entry* %306), !dbg !1528
  %307 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1529
  %call494 = call i64 @archive_entry_birthtime_nsec(%struct.archive_entry* %307), !dbg !1530
  call void @add_pax_attr_time(%struct.archive_string* %pax_header492, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.33, i32 0, i32 0), i64 %call493, i64 %call494), !dbg !1531
  br label %if.end495, !dbg !1531

if.end495:                                        ; preds = %if.then491, %land.lhs.true486, %if.end483
  br label %if.end496, !dbg !1532

if.end496:                                        ; preds = %if.end495, %if.end455
  %308 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1533
  %archive497 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %308, i32 0, i32 0, !dbg !1535
  %archive_format498 = getelementptr inbounds %struct.archive, %struct.archive* %archive497, i32 0, i32 3, !dbg !1536
  %309 = load i32, i32* %archive_format498, align 8, !dbg !1536
  %cmp499 = icmp ne i32 %309, 196611, !dbg !1537
  br i1 %cmp499, label %if.then503, label %lor.lhs.false501, !dbg !1538

lor.lhs.false501:                                 ; preds = %if.end496
  %310 = load i32, i32* %need_extension, align 4, !dbg !1539
  %tobool502 = icmp ne i32 %310, 0, !dbg !1539
  br i1 %tobool502, label %if.then503, label %if.end590, !dbg !1540

if.then503:                                       ; preds = %lor.lhs.false501, %if.end496
  %311 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1541
  %call504 = call i64 @archive_entry_mtime(%struct.archive_entry* %311), !dbg !1544
  %cmp505 = icmp slt i64 %call504, 0, !dbg !1545
  br i1 %cmp505, label %if.then515, label %lor.lhs.false507, !dbg !1546

lor.lhs.false507:                                 ; preds = %if.then503
  %312 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1547
  %call508 = call i64 @archive_entry_mtime(%struct.archive_entry* %312), !dbg !1548
  %cmp509 = icmp sge i64 %call508, 2147483647, !dbg !1549
  br i1 %cmp509, label %if.then515, label %lor.lhs.false511, !dbg !1550

lor.lhs.false511:                                 ; preds = %lor.lhs.false507
  %313 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1551
  %call512 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %313), !dbg !1552
  %cmp513 = icmp ne i64 %call512, 0, !dbg !1553
  br i1 %cmp513, label %if.then515, label %if.end519, !dbg !1554

if.then515:                                       ; preds = %lor.lhs.false511, %lor.lhs.false507, %if.then503
  %314 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1556
  %pax_header516 = getelementptr inbounds %struct.pax, %struct.pax* %314, i32 0, i32 3, !dbg !1557
  %315 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1558
  %call517 = call i64 @archive_entry_mtime(%struct.archive_entry* %315), !dbg !1559
  %316 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1560
  %call518 = call i64 @archive_entry_mtime_nsec(%struct.archive_entry* %316), !dbg !1561
  call void @add_pax_attr_time(%struct.archive_string* %pax_header516, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.34, i32 0, i32 0), i64 %call517, i64 %call518), !dbg !1562
  br label %if.end519, !dbg !1562

if.end519:                                        ; preds = %if.then515, %lor.lhs.false511
  %317 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1563
  %call520 = call i8* @archive_entry_fflags_text(%struct.archive_entry* %317), !dbg !1564
  store i8* %call520, i8** %p, align 8, !dbg !1565
  %318 = load i8*, i8** %p, align 8, !dbg !1566
  %cmp521 = icmp ne i8* %318, null, !dbg !1568
  br i1 %cmp521, label %land.lhs.true523, label %if.end529, !dbg !1569

land.lhs.true523:                                 ; preds = %if.end519
  %319 = load i8*, i8** %p, align 8, !dbg !1570
  %320 = load i8, i8* %319, align 1, !dbg !1572
  %conv524 = sext i8 %320 to i32, !dbg !1572
  %cmp525 = icmp ne i32 %conv524, 0, !dbg !1573
  br i1 %cmp525, label %if.then527, label %if.end529, !dbg !1574

if.then527:                                       ; preds = %land.lhs.true523
  %321 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1575
  %pax_header528 = getelementptr inbounds %struct.pax, %struct.pax* %321, i32 0, i32 3, !dbg !1576
  %322 = load i8*, i8** %p, align 8, !dbg !1577
  call void @add_pax_attr(%struct.archive_string* %pax_header528, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.35, i32 0, i32 0), i8* %322), !dbg !1578
  br label %if.end529, !dbg !1578

if.end529:                                        ; preds = %if.then527, %land.lhs.true523, %if.end519
  %323 = load i32, i32* %acl_types, align 4, !dbg !1579
  %and = and i32 %323, 15360, !dbg !1581
  %cmp530 = icmp ne i32 %and, 0, !dbg !1582
  br i1 %cmp530, label %if.then532, label %if.end538, !dbg !1583

if.then532:                                       ; preds = %if.end529
  %324 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1584
  %325 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !1586
  %326 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1587
  %call533 = call i32 @add_pax_acl(%struct.archive_write* %324, %struct.archive_entry* %325, %struct.pax* %326, i32 25), !dbg !1588
  store i32 %call533, i32* %ret, align 4, !dbg !1589
  %327 = load i32, i32* %ret, align 4, !dbg !1590
  %cmp534 = icmp eq i32 %327, -30, !dbg !1592
  br i1 %cmp534, label %if.then536, label %if.end537, !dbg !1593

if.then536:                                       ; preds = %if.then532
  store i32 -30, i32* %retval, align 4, !dbg !1594
  br label %return, !dbg !1594

if.end537:                                        ; preds = %if.then532
  br label %if.end538, !dbg !1595

if.end538:                                        ; preds = %if.end537, %if.end529
  %328 = load i32, i32* %acl_types, align 4, !dbg !1596
  %and539 = and i32 %328, 256, !dbg !1598
  %tobool540 = icmp ne i32 %and539, 0, !dbg !1598
  br i1 %tobool540, label %if.then541, label %if.end547, !dbg !1599

if.then541:                                       ; preds = %if.end538
  %329 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1600
  %330 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !1602
  %331 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1603
  %call542 = call i32 @add_pax_acl(%struct.archive_write* %329, %struct.archive_entry* %330, %struct.pax* %331, i32 265), !dbg !1604
  store i32 %call542, i32* %ret, align 4, !dbg !1605
  %332 = load i32, i32* %ret, align 4, !dbg !1606
  %cmp543 = icmp eq i32 %332, -30, !dbg !1608
  br i1 %cmp543, label %if.then545, label %if.end546, !dbg !1609

if.then545:                                       ; preds = %if.then541
  store i32 -30, i32* %retval, align 4, !dbg !1610
  br label %return, !dbg !1610

if.end546:                                        ; preds = %if.then541
  br label %if.end547, !dbg !1611

if.end547:                                        ; preds = %if.end546, %if.end538
  %333 = load i32, i32* %acl_types, align 4, !dbg !1612
  %and548 = and i32 %333, 512, !dbg !1614
  %tobool549 = icmp ne i32 %and548, 0, !dbg !1614
  br i1 %tobool549, label %if.then550, label %if.end556, !dbg !1615

if.then550:                                       ; preds = %if.end547
  %334 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1616
  %335 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !1618
  %336 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1619
  %call551 = call i32 @add_pax_acl(%struct.archive_write* %334, %struct.archive_entry* %335, %struct.pax* %336, i32 521), !dbg !1620
  store i32 %call551, i32* %ret, align 4, !dbg !1621
  %337 = load i32, i32* %ret, align 4, !dbg !1622
  %cmp552 = icmp eq i32 %337, -30, !dbg !1624
  br i1 %cmp552, label %if.then554, label %if.end555, !dbg !1625

if.then554:                                       ; preds = %if.then550
  store i32 -30, i32* %retval, align 4, !dbg !1626
  br label %return, !dbg !1626

if.end555:                                        ; preds = %if.then550
  br label %if.end556, !dbg !1627

if.end556:                                        ; preds = %if.end555, %if.end547
  %338 = load i32, i32* %sparse_count, align 4, !dbg !1628
  %cmp557 = icmp sgt i32 %338, 0, !dbg !1630
  br i1 %cmp557, label %if.then559, label %if.end584, !dbg !1631

if.then559:                                       ; preds = %if.end556
  call void @llvm.dbg.declare(metadata i64* %soffset, metadata !1632, metadata !293), !dbg !1634
  call void @llvm.dbg.declare(metadata i64* %slength, metadata !1635, metadata !293), !dbg !1636
  %339 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1637
  %pax_header560 = getelementptr inbounds %struct.pax, %struct.pax* %339, i32 0, i32 3, !dbg !1638
  call void @add_pax_attr_int(%struct.archive_string* %pax_header560, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.36, i32 0, i32 0), i64 1), !dbg !1639
  %340 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1640
  %pax_header561 = getelementptr inbounds %struct.pax, %struct.pax* %340, i32 0, i32 3, !dbg !1641
  call void @add_pax_attr_int(%struct.archive_string* %pax_header561, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.37, i32 0, i32 0), i64 0), !dbg !1642
  %341 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1643
  %pax_header562 = getelementptr inbounds %struct.pax, %struct.pax* %341, i32 0, i32 3, !dbg !1644
  %s563 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_name, i32 0, i32 0, !dbg !1645
  %342 = load i8*, i8** %s563, align 8, !dbg !1645
  call void @add_pax_attr(%struct.archive_string* %pax_header562, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.38, i32 0, i32 0), i8* %342), !dbg !1646
  %343 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1647
  %pax_header564 = getelementptr inbounds %struct.pax, %struct.pax* %343, i32 0, i32 3, !dbg !1648
  %344 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1649
  %call565 = call i64 @archive_entry_size(%struct.archive_entry* %344), !dbg !1650
  call void @add_pax_attr_int(%struct.archive_string* %pax_header564, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.39, i32 0, i32 0), i64 %call565), !dbg !1651
  %345 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1652
  %arraydecay566 = getelementptr inbounds [256 x i8], [256 x i8]* %gnu_sparse_name, i32 0, i32 0, !dbg !1653
  %s567 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_name, i32 0, i32 0, !dbg !1654
  %346 = load i8*, i8** %s567, align 8, !dbg !1654
  %call568 = call i8* @build_gnu_sparse_name(i8* %arraydecay566, i8* %346), !dbg !1655
  call void @archive_entry_set_pathname(%struct.archive_entry* %345, i8* %call568), !dbg !1656
  %347 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1657
  %sparse_map569 = getelementptr inbounds %struct.pax, %struct.pax* %347, i32 0, i32 4, !dbg !1658
  %348 = load i32, i32* %sparse_count, align 4, !dbg !1659
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %sparse_map569, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.40, i32 0, i32 0), i32 %348), !dbg !1660
  br label %while.cond570, !dbg !1661

while.cond570:                                    ; preds = %if.end582, %if.then559
  %349 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1662
  %call571 = call i32 @archive_entry_sparse_next(%struct.archive_entry* %349, i64* %soffset, i64* %slength), !dbg !1664
  %cmp572 = icmp eq i32 %call571, 0, !dbg !1665
  br i1 %cmp572, label %while.body574, label %while.end583, !dbg !1666

while.body574:                                    ; preds = %while.cond570
  %350 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1667
  %sparse_map575 = getelementptr inbounds %struct.pax, %struct.pax* %350, i32 0, i32 4, !dbg !1669
  %351 = load i64, i64* %soffset, align 8, !dbg !1670
  %352 = load i64, i64* %slength, align 8, !dbg !1671
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %sparse_map575, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.41, i32 0, i32 0), i64 %351, i64 %352), !dbg !1672
  %353 = load i64, i64* %slength, align 8, !dbg !1673
  %354 = load i64, i64* %sparse_total, align 8, !dbg !1674
  %add576 = add i64 %354, %353, !dbg !1674
  store i64 %add576, i64* %sparse_total, align 8, !dbg !1674
  %355 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1675
  %356 = load i64, i64* %soffset, align 8, !dbg !1677
  %357 = load i64, i64* %slength, align 8, !dbg !1678
  %call577 = call i32 @sparse_list_add(%struct.pax* %355, i64 %356, i64 %357), !dbg !1679
  %cmp578 = icmp ne i32 %call577, 0, !dbg !1680
  br i1 %cmp578, label %if.then580, label %if.end582, !dbg !1681

if.then580:                                       ; preds = %while.body574
  %358 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1682
  %archive581 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %358, i32 0, i32 0, !dbg !1684
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive581, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.42, i32 0, i32 0)), !dbg !1685
  %359 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1686
  call void @archive_entry_free(%struct.archive_entry* %359), !dbg !1687
  call void @archive_string_free(%struct.archive_string* %entry_name), !dbg !1688
  store i32 -30, i32* %retval, align 4, !dbg !1689
  br label %return, !dbg !1689

if.end582:                                        ; preds = %while.body574
  br label %while.cond570, !dbg !1690

while.end583:                                     ; preds = %while.cond570
  br label %if.end584, !dbg !1692

if.end584:                                        ; preds = %while.end583, %if.end556
  %360 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1693
  %361 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1695
  %362 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !1696
  %call585 = call i32 @archive_write_pax_header_xattrs(%struct.archive_write* %360, %struct.pax* %361, %struct.archive_entry* %362), !dbg !1697
  %cmp586 = icmp eq i32 %call585, -30, !dbg !1698
  br i1 %cmp586, label %if.then588, label %if.end589, !dbg !1699

if.then588:                                       ; preds = %if.end584
  %363 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1700
  call void @archive_entry_free(%struct.archive_entry* %363), !dbg !1702
  call void @archive_string_free(%struct.archive_string* %entry_name), !dbg !1703
  store i32 -30, i32* %retval, align 4, !dbg !1704
  br label %return, !dbg !1704

if.end589:                                        ; preds = %if.end584
  br label %if.end590, !dbg !1705

if.end590:                                        ; preds = %if.end589, %lor.lhs.false501
  %364 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1706
  %call591 = call i32 @archive_entry_filetype(%struct.archive_entry* %364), !dbg !1708
  %cmp592 = icmp ne i32 %call591, 32768, !dbg !1709
  br i1 %cmp592, label %if.then594, label %if.end595, !dbg !1710

if.then594:                                       ; preds = %if.end590
  %365 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1711
  call void @archive_entry_set_size(%struct.archive_entry* %365, i64 0), !dbg !1712
  br label %if.end595, !dbg !1712

if.end595:                                        ; preds = %if.then594, %if.end590
  %366 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1713
  %archive596 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %366, i32 0, i32 0, !dbg !1715
  %archive_format597 = getelementptr inbounds %struct.archive, %struct.archive* %archive596, i32 0, i32 3, !dbg !1716
  %367 = load i32, i32* %archive_format597, align 8, !dbg !1716
  %cmp598 = icmp ne i32 %367, 196610, !dbg !1717
  br i1 %cmp598, label %land.lhs.true600, label %if.end604, !dbg !1718

land.lhs.true600:                                 ; preds = %if.end595
  %368 = load i8*, i8** %hardlink, align 8, !dbg !1719
  %cmp601 = icmp ne i8* %368, null, !dbg !1720
  br i1 %cmp601, label %if.then603, label %if.end604, !dbg !1721

if.then603:                                       ; preds = %land.lhs.true600
  %369 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1722
  call void @archive_entry_set_size(%struct.archive_entry* %369, i64 0), !dbg !1723
  br label %if.end604, !dbg !1723

if.end604:                                        ; preds = %if.then603, %land.lhs.true600, %if.end595
  %370 = load i8*, i8** %hardlink, align 8, !dbg !1724
  %cmp605 = icmp ne i8* %370, null, !dbg !1726
  br i1 %cmp605, label %if.then607, label %if.end608, !dbg !1727

if.then607:                                       ; preds = %if.end604
  %371 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1728
  call void @archive_entry_set_size(%struct.archive_entry* %371, i64 0), !dbg !1729
  br label %if.end608, !dbg !1729

if.end608:                                        ; preds = %if.then607, %if.end604
  %372 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1730
  %call609 = call i64 @archive_entry_size(%struct.archive_entry* %372), !dbg !1731
  store i64 %call609, i64* %real_size, align 8, !dbg !1732
  %373 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1733
  %sparse_map610 = getelementptr inbounds %struct.pax, %struct.pax* %373, i32 0, i32 4, !dbg !1733
  %length611 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %sparse_map610, i32 0, i32 1, !dbg !1733
  %374 = load i64, i64* %length611, align 8, !dbg !1733
  %tobool612 = icmp ne i64 %374, 0, !dbg !1733
  br i1 %tobool612, label %if.then613, label %if.end621, !dbg !1735

if.then613:                                       ; preds = %if.end608
  call void @llvm.dbg.declare(metadata i64* %mapsize, metadata !1736, metadata !293), !dbg !1738
  %375 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1739
  %sparse_map614 = getelementptr inbounds %struct.pax, %struct.pax* %375, i32 0, i32 4, !dbg !1739
  %length615 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %sparse_map614, i32 0, i32 1, !dbg !1739
  %376 = load i64, i64* %length615, align 8, !dbg !1739
  store i64 %376, i64* %mapsize, align 8, !dbg !1738
  %377 = load i64, i64* %mapsize, align 8, !dbg !1740
  %sub616 = sub nsw i64 0, %377, !dbg !1741
  %and617 = and i64 511, %sub616, !dbg !1742
  %378 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1743
  %sparse_map_padding = getelementptr inbounds %struct.pax, %struct.pax* %378, i32 0, i32 5, !dbg !1744
  store i64 %and617, i64* %sparse_map_padding, align 8, !dbg !1745
  %379 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1746
  %380 = load i64, i64* %mapsize, align 8, !dbg !1747
  %381 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1748
  %sparse_map_padding618 = getelementptr inbounds %struct.pax, %struct.pax* %381, i32 0, i32 5, !dbg !1749
  %382 = load i64, i64* %sparse_map_padding618, align 8, !dbg !1749
  %add619 = add i64 %380, %382, !dbg !1750
  %383 = load i64, i64* %sparse_total, align 8, !dbg !1751
  %add620 = add i64 %add619, %383, !dbg !1752
  call void @archive_entry_set_size(%struct.archive_entry* %379, i64 %add620), !dbg !1753
  br label %if.end621, !dbg !1754

if.end621:                                        ; preds = %if.then613, %if.end608
  %384 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1755
  %arraydecay622 = getelementptr inbounds [512 x i8], [512 x i8]* %ustarbuff, i32 0, i32 0, !dbg !1757
  %385 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1758
  %call623 = call i32 @__archive_write_format_header_ustar(%struct.archive_write* %384, i8* %arraydecay622, %struct.archive_entry* %385, i32 -1, i32 0, %struct.archive_string_conv* null), !dbg !1759
  %cmp624 = icmp eq i32 %call623, -30, !dbg !1760
  br i1 %cmp624, label %if.then626, label %if.end627, !dbg !1761

if.then626:                                       ; preds = %if.end621
  store i32 -30, i32* %retval, align 4, !dbg !1762
  br label %return, !dbg !1762

if.end627:                                        ; preds = %if.end621
  %386 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1763
  %pax_header628 = getelementptr inbounds %struct.pax, %struct.pax* %386, i32 0, i32 3, !dbg !1763
  %length629 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pax_header628, i32 0, i32 1, !dbg !1763
  %387 = load i64, i64* %length629, align 8, !dbg !1763
  %cmp630 = icmp ugt i64 %387, 0, !dbg !1765
  br i1 %cmp630, label %if.then632, label %if.end708, !dbg !1766

if.then632:                                       ; preds = %if.end627
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %pax_attr_entry, metadata !1767, metadata !293), !dbg !1769
  call void @llvm.dbg.declare(metadata i64* %s633, metadata !1770, metadata !293), !dbg !1774
  call void @llvm.dbg.declare(metadata i64* %uid, metadata !1775, metadata !293), !dbg !1776
  call void @llvm.dbg.declare(metadata i64* %gid, metadata !1777, metadata !293), !dbg !1778
  call void @llvm.dbg.declare(metadata i32* %mode, metadata !1779, metadata !293), !dbg !1780
  %388 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1781
  %archive634 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %388, i32 0, i32 0, !dbg !1782
  %call635 = call %struct.archive_entry* @archive_entry_new2(%struct.archive* %archive634), !dbg !1783
  store %struct.archive_entry* %call635, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1784
  %s636 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %entry_name, i32 0, i32 0, !dbg !1785
  %389 = load i8*, i8** %s636, align 8, !dbg !1785
  store i8* %389, i8** %p, align 8, !dbg !1786
  %390 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1787
  %arraydecay637 = getelementptr inbounds [256 x i8], [256 x i8]* %pax_entry_name, i32 0, i32 0, !dbg !1788
  %391 = load i8*, i8** %p, align 8, !dbg !1789
  %call638 = call i8* @build_pax_attribute_name(i8* %arraydecay637, i8* %391), !dbg !1790
  call void @archive_entry_set_pathname(%struct.archive_entry* %390, i8* %call638), !dbg !1791
  %392 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1792
  %393 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1793
  %pax_header639 = getelementptr inbounds %struct.pax, %struct.pax* %393, i32 0, i32 3, !dbg !1793
  %length640 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pax_header639, i32 0, i32 1, !dbg !1793
  %394 = load i64, i64* %length640, align 8, !dbg !1793
  call void @archive_entry_set_size(%struct.archive_entry* %392, i64 %394), !dbg !1794
  %395 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1795
  %call641 = call i64 @archive_entry_uid(%struct.archive_entry* %395), !dbg !1796
  store i64 %call641, i64* %uid, align 8, !dbg !1797
  %396 = load i64, i64* %uid, align 8, !dbg !1798
  %cmp642 = icmp sge i64 %396, 262144, !dbg !1800
  br i1 %cmp642, label %if.then644, label %if.end645, !dbg !1801

if.then644:                                       ; preds = %if.then632
  store i64 262143, i64* %uid, align 8, !dbg !1802
  br label %if.end645, !dbg !1803

if.end645:                                        ; preds = %if.then644, %if.then632
  %397 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1804
  %398 = load i64, i64* %uid, align 8, !dbg !1805
  call void @archive_entry_set_uid(%struct.archive_entry* %397, i64 %398), !dbg !1806
  %399 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1807
  %call646 = call i64 @archive_entry_gid(%struct.archive_entry* %399), !dbg !1808
  store i64 %call646, i64* %gid, align 8, !dbg !1809
  %400 = load i64, i64* %gid, align 8, !dbg !1810
  %cmp647 = icmp sge i64 %400, 262144, !dbg !1812
  br i1 %cmp647, label %if.then649, label %if.end650, !dbg !1813

if.then649:                                       ; preds = %if.end645
  store i64 262143, i64* %gid, align 8, !dbg !1814
  br label %if.end650, !dbg !1815

if.end650:                                        ; preds = %if.then649, %if.end645
  %401 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1816
  %402 = load i64, i64* %gid, align 8, !dbg !1817
  call void @archive_entry_set_gid(%struct.archive_entry* %401, i64 %402), !dbg !1818
  %403 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1819
  %call651 = call i32 @archive_entry_mode(%struct.archive_entry* %403), !dbg !1820
  store i32 %call651, i32* %mode, align 4, !dbg !1821
  %404 = load i32, i32* %mode, align 4, !dbg !1822
  %and652 = and i32 %404, -2049, !dbg !1822
  store i32 %and652, i32* %mode, align 4, !dbg !1822
  %405 = load i32, i32* %mode, align 4, !dbg !1823
  %and653 = and i32 %405, -1025, !dbg !1823
  store i32 %and653, i32* %mode, align 4, !dbg !1823
  %406 = load i32, i32* %mode, align 4, !dbg !1824
  %and654 = and i32 %406, -513, !dbg !1824
  store i32 %and654, i32* %mode, align 4, !dbg !1824
  %407 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1825
  %408 = load i32, i32* %mode, align 4, !dbg !1826
  call void @archive_entry_set_mode(%struct.archive_entry* %407, i32 %408), !dbg !1827
  %409 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1828
  %410 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1829
  %call655 = call i8* @archive_entry_uname(%struct.archive_entry* %410), !dbg !1830
  call void @archive_entry_set_uname(%struct.archive_entry* %409, i8* %call655), !dbg !1831
  %411 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1832
  %412 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1833
  %call656 = call i8* @archive_entry_gname(%struct.archive_entry* %412), !dbg !1834
  call void @archive_entry_set_gname(%struct.archive_entry* %411, i8* %call656), !dbg !1835
  %413 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1836
  %call657 = call i64 @archive_entry_mtime(%struct.archive_entry* %413), !dbg !1837
  store i64 %call657, i64* %s633, align 8, !dbg !1838
  %414 = load i64, i64* %s633, align 8, !dbg !1839
  %cmp658 = icmp slt i64 %414, 0, !dbg !1841
  br i1 %cmp658, label %if.then660, label %if.end661, !dbg !1842

if.then660:                                       ; preds = %if.end650
  store i64 0, i64* %s633, align 8, !dbg !1843
  br label %if.end661, !dbg !1846

if.end661:                                        ; preds = %if.then660, %if.end650
  %415 = load i64, i64* %s633, align 8, !dbg !1847
  %cmp662 = icmp sge i64 %415, 2147483647, !dbg !1849
  br i1 %cmp662, label %if.then664, label %if.end665, !dbg !1850

if.then664:                                       ; preds = %if.end661
  store i64 2147483647, i64* %s633, align 8, !dbg !1851
  br label %if.end665, !dbg !1854

if.end665:                                        ; preds = %if.then664, %if.end661
  %416 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1855
  %417 = load i64, i64* %s633, align 8, !dbg !1856
  call void @archive_entry_set_mtime(%struct.archive_entry* %416, i64 %417, i64 0), !dbg !1857
  %418 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1858
  call void @archive_entry_set_atime(%struct.archive_entry* %418, i64 0, i64 0), !dbg !1859
  %419 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1860
  call void @archive_entry_set_ctime(%struct.archive_entry* %419, i64 0, i64 0), !dbg !1861
  %420 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1862
  %arraydecay666 = getelementptr inbounds [512 x i8], [512 x i8]* %paxbuff, i32 0, i32 0, !dbg !1863
  %421 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1864
  %call667 = call i32 @__archive_write_format_header_ustar(%struct.archive_write* %420, i8* %arraydecay666, %struct.archive_entry* %421, i32 120, i32 1, %struct.archive_string_conv* null), !dbg !1865
  store i32 %call667, i32* %r, align 4, !dbg !1866
  %422 = load %struct.archive_entry*, %struct.archive_entry** %pax_attr_entry, align 8, !dbg !1867
  call void @archive_entry_free(%struct.archive_entry* %422), !dbg !1868
  %423 = load i32, i32* %r, align 4, !dbg !1869
  %cmp668 = icmp slt i32 %423, -20, !dbg !1871
  br i1 %cmp668, label %if.then670, label %if.else672, !dbg !1872

if.then670:                                       ; preds = %if.end665
  %424 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1873
  %archive671 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %424, i32 0, i32 0, !dbg !1875
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive671, i32 -1, i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.43, i32 0, i32 0)), !dbg !1876
  store i32 -30, i32* %retval, align 4, !dbg !1877
  br label %return, !dbg !1877

if.else672:                                       ; preds = %if.end665
  %425 = load i32, i32* %r, align 4, !dbg !1878
  %426 = load i32, i32* %ret, align 4, !dbg !1880
  %cmp673 = icmp slt i32 %425, %426, !dbg !1881
  br i1 %cmp673, label %if.then675, label %if.end676, !dbg !1882

if.then675:                                       ; preds = %if.else672
  %427 = load i32, i32* %r, align 4, !dbg !1883
  store i32 %427, i32* %ret, align 4, !dbg !1884
  br label %if.end676, !dbg !1885

if.end676:                                        ; preds = %if.then675, %if.else672
  br label %if.end677

if.end677:                                        ; preds = %if.end676
  %428 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1886
  %arraydecay678 = getelementptr inbounds [512 x i8], [512 x i8]* %paxbuff, i32 0, i32 0, !dbg !1887
  %call679 = call i32 @__archive_write_output(%struct.archive_write* %428, i8* %arraydecay678, i64 512), !dbg !1888
  store i32 %call679, i32* %r, align 4, !dbg !1889
  %429 = load i32, i32* %r, align 4, !dbg !1890
  %cmp680 = icmp ne i32 %429, 0, !dbg !1892
  br i1 %cmp680, label %if.then682, label %if.end683, !dbg !1893

if.then682:                                       ; preds = %if.end677
  %430 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1894
  call void @sparse_list_clear(%struct.pax* %430), !dbg !1896
  %431 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1897
  %entry_bytes_remaining = getelementptr inbounds %struct.pax, %struct.pax* %431, i32 0, i32 0, !dbg !1898
  store i64 0, i64* %entry_bytes_remaining, align 8, !dbg !1899
  %432 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1900
  %entry_padding = getelementptr inbounds %struct.pax, %struct.pax* %432, i32 0, i32 1, !dbg !1901
  store i64 0, i64* %entry_padding, align 8, !dbg !1902
  store i32 -30, i32* %retval, align 4, !dbg !1903
  br label %return, !dbg !1903

if.end683:                                        ; preds = %if.end677
  %433 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1904
  %pax_header684 = getelementptr inbounds %struct.pax, %struct.pax* %433, i32 0, i32 3, !dbg !1904
  %length685 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pax_header684, i32 0, i32 1, !dbg !1904
  %434 = load i64, i64* %length685, align 8, !dbg !1904
  %435 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1905
  %entry_bytes_remaining686 = getelementptr inbounds %struct.pax, %struct.pax* %435, i32 0, i32 0, !dbg !1906
  store i64 %434, i64* %entry_bytes_remaining686, align 8, !dbg !1907
  %436 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1908
  %entry_bytes_remaining687 = getelementptr inbounds %struct.pax, %struct.pax* %436, i32 0, i32 0, !dbg !1909
  %437 = load i64, i64* %entry_bytes_remaining687, align 8, !dbg !1909
  %sub688 = sub nsw i64 0, %437, !dbg !1910
  %and689 = and i64 511, %sub688, !dbg !1911
  %438 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1912
  %entry_padding690 = getelementptr inbounds %struct.pax, %struct.pax* %438, i32 0, i32 1, !dbg !1913
  store i64 %and689, i64* %entry_padding690, align 8, !dbg !1914
  %439 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1915
  %440 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1916
  %pax_header691 = getelementptr inbounds %struct.pax, %struct.pax* %440, i32 0, i32 3, !dbg !1917
  %s692 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pax_header691, i32 0, i32 0, !dbg !1918
  %441 = load i8*, i8** %s692, align 8, !dbg !1918
  %442 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1919
  %pax_header693 = getelementptr inbounds %struct.pax, %struct.pax* %442, i32 0, i32 3, !dbg !1919
  %length694 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %pax_header693, i32 0, i32 1, !dbg !1919
  %443 = load i64, i64* %length694, align 8, !dbg !1919
  %call695 = call i32 @__archive_write_output(%struct.archive_write* %439, i8* %441, i64 %443), !dbg !1920
  store i32 %call695, i32* %r, align 4, !dbg !1921
  %444 = load i32, i32* %r, align 4, !dbg !1922
  %cmp696 = icmp ne i32 %444, 0, !dbg !1924
  br i1 %cmp696, label %if.then698, label %if.end699, !dbg !1925

if.then698:                                       ; preds = %if.end683
  store i32 -30, i32* %retval, align 4, !dbg !1926
  br label %return, !dbg !1926

if.end699:                                        ; preds = %if.end683
  %445 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1928
  %446 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1929
  %entry_padding700 = getelementptr inbounds %struct.pax, %struct.pax* %446, i32 0, i32 1, !dbg !1930
  %447 = load i64, i64* %entry_padding700, align 8, !dbg !1930
  %call701 = call i32 @__archive_write_nulls(%struct.archive_write* %445, i64 %447), !dbg !1931
  store i32 %call701, i32* %r, align 4, !dbg !1932
  %448 = load i32, i32* %r, align 4, !dbg !1933
  %cmp702 = icmp ne i32 %448, 0, !dbg !1935
  br i1 %cmp702, label %if.then704, label %if.end705, !dbg !1936

if.then704:                                       ; preds = %if.end699
  store i32 -30, i32* %retval, align 4, !dbg !1937
  br label %return, !dbg !1937

if.end705:                                        ; preds = %if.end699
  %449 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1939
  %entry_padding706 = getelementptr inbounds %struct.pax, %struct.pax* %449, i32 0, i32 1, !dbg !1940
  store i64 0, i64* %entry_padding706, align 8, !dbg !1941
  %450 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1942
  %entry_bytes_remaining707 = getelementptr inbounds %struct.pax, %struct.pax* %450, i32 0, i32 0, !dbg !1943
  store i64 0, i64* %entry_bytes_remaining707, align 8, !dbg !1944
  br label %if.end708, !dbg !1945

if.end708:                                        ; preds = %if.end705, %if.end627
  %451 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !1946
  %arraydecay709 = getelementptr inbounds [512 x i8], [512 x i8]* %ustarbuff, i32 0, i32 0, !dbg !1947
  %call710 = call i32 @__archive_write_output(%struct.archive_write* %451, i8* %arraydecay709, i64 512), !dbg !1948
  store i32 %call710, i32* %r, align 4, !dbg !1949
  %452 = load i32, i32* %r, align 4, !dbg !1950
  %cmp711 = icmp ne i32 %452, 0, !dbg !1952
  br i1 %cmp711, label %if.then713, label %if.end714, !dbg !1953

if.then713:                                       ; preds = %if.end708
  %453 = load i32, i32* %r, align 4, !dbg !1954
  store i32 %453, i32* %retval, align 4, !dbg !1955
  br label %return, !dbg !1955

if.end714:                                        ; preds = %if.end708
  %454 = load %struct.archive_entry*, %struct.archive_entry** %entry_original.addr, align 8, !dbg !1956
  %455 = load i64, i64* %real_size, align 8, !dbg !1957
  call void @archive_entry_set_size(%struct.archive_entry* %454, i64 %455), !dbg !1958
  %456 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1959
  %sparse_list = getelementptr inbounds %struct.pax, %struct.pax* %456, i32 0, i32 6, !dbg !1961
  %457 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list, align 8, !dbg !1961
  %cmp715 = icmp eq %struct.sparse_block* %457, null, !dbg !1962
  br i1 %cmp715, label %land.lhs.true717, label %if.end722, !dbg !1963

land.lhs.true717:                                 ; preds = %if.end714
  %458 = load i64, i64* %real_size, align 8, !dbg !1964
  %cmp718 = icmp ugt i64 %458, 0, !dbg !1966
  br i1 %cmp718, label %if.then720, label %if.end722, !dbg !1967

if.then720:                                       ; preds = %land.lhs.true717
  %459 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1968
  %460 = load i64, i64* %real_size, align 8, !dbg !1970
  %call721 = call i32 @sparse_list_add(%struct.pax* %459, i64 0, i64 %460), !dbg !1971
  %461 = load i64, i64* %real_size, align 8, !dbg !1972
  store i64 %461, i64* %sparse_total, align 8, !dbg !1973
  br label %if.end722, !dbg !1974

if.end722:                                        ; preds = %if.then720, %land.lhs.true717, %if.end714
  %462 = load i64, i64* %sparse_total, align 8, !dbg !1975
  %sub723 = sub nsw i64 0, %462, !dbg !1976
  %and724 = and i64 511, %sub723, !dbg !1977
  %463 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !1978
  %entry_padding725 = getelementptr inbounds %struct.pax, %struct.pax* %463, i32 0, i32 1, !dbg !1979
  store i64 %and724, i64* %entry_padding725, align 8, !dbg !1980
  %464 = load %struct.archive_entry*, %struct.archive_entry** %entry_main, align 8, !dbg !1981
  call void @archive_entry_free(%struct.archive_entry* %464), !dbg !1982
  call void @archive_string_free(%struct.archive_string* %entry_name), !dbg !1983
  %465 = load i32, i32* %ret, align 4, !dbg !1984
  store i32 %465, i32* %retval, align 4, !dbg !1985
  br label %return, !dbg !1985

return:                                           ; preds = %if.end722, %if.then713, %if.then704, %if.then698, %if.then682, %if.then670, %if.then626, %if.then588, %if.then580, %if.then554, %if.then545, %if.then536, %if.then263, %if.then258, %if.then253, %if.then247, %if.then228, %if.then220, %if.then208, %if.then200, %if.then191, %if.then183, %if.then174, %if.then166, %if.then130, %if.then120, %if.then111, %if.then101, %if.then70, %sw.default, %sw.bb50, %if.then42, %if.then22, %if.then16, %if.then9, %if.then
  %466 = load i32, i32* %retval, align 4, !dbg !1986
  ret i32 %466, !dbg !1986
}

; Function Attrs: nounwind uwtable
define internal i64 @archive_write_pax_data(%struct.archive_write* %a, i8* %buff, i64 %s) #0 !dbg !283 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive_write*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %pax = alloca %struct.pax*, align 8
  %ws = alloca i64, align 8
  %total = alloca i64, align 8
  %ret = alloca i32, align 4
  %p = alloca i8*, align 8
  %sb = alloca %struct.sparse_block*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !1987, metadata !293), !dbg !1988
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !1989, metadata !293), !dbg !1990
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !1991, metadata !293), !dbg !1992
  call void @llvm.dbg.declare(metadata %struct.pax** %pax, metadata !1993, metadata !293), !dbg !1994
  call void @llvm.dbg.declare(metadata i64* %ws, metadata !1995, metadata !293), !dbg !1996
  call void @llvm.dbg.declare(metadata i64* %total, metadata !1997, metadata !293), !dbg !1998
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !1999, metadata !293), !dbg !2000
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2001
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !2002
  %1 = load i8*, i8** %format_data, align 8, !dbg !2002
  %2 = bitcast i8* %1 to %struct.pax*, !dbg !2003
  store %struct.pax* %2, %struct.pax** %pax, align 8, !dbg !2004
  %3 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2005
  %sparse_map = getelementptr inbounds %struct.pax, %struct.pax* %3, i32 0, i32 4, !dbg !2005
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %sparse_map, i32 0, i32 1, !dbg !2005
  %4 = load i64, i64* %length, align 8, !dbg !2005
  %tobool = icmp ne i64 %4, 0, !dbg !2005
  br i1 %tobool, label %if.then, label %if.end14, !dbg !2007

if.then:                                          ; preds = %entry
  %5 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2008
  %6 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2010
  %sparse_map1 = getelementptr inbounds %struct.pax, %struct.pax* %6, i32 0, i32 4, !dbg !2011
  %s2 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %sparse_map1, i32 0, i32 0, !dbg !2012
  %7 = load i8*, i8** %s2, align 8, !dbg !2012
  %8 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2013
  %sparse_map3 = getelementptr inbounds %struct.pax, %struct.pax* %8, i32 0, i32 4, !dbg !2013
  %length4 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %sparse_map3, i32 0, i32 1, !dbg !2013
  %9 = load i64, i64* %length4, align 8, !dbg !2013
  %call = call i32 @__archive_write_output(%struct.archive_write* %5, i8* %7, i64 %9), !dbg !2014
  store i32 %call, i32* %ret, align 4, !dbg !2015
  %10 = load i32, i32* %ret, align 4, !dbg !2016
  %cmp = icmp ne i32 %10, 0, !dbg !2018
  br i1 %cmp, label %if.then5, label %if.end, !dbg !2019

if.then5:                                         ; preds = %if.then
  %11 = load i32, i32* %ret, align 4, !dbg !2020
  %conv = sext i32 %11 to i64, !dbg !2021
  store i64 %conv, i64* %retval, align 8, !dbg !2022
  br label %return, !dbg !2022

if.end:                                           ; preds = %if.then
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2023
  %13 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2024
  %sparse_map_padding = getelementptr inbounds %struct.pax, %struct.pax* %13, i32 0, i32 5, !dbg !2025
  %14 = load i64, i64* %sparse_map_padding, align 8, !dbg !2025
  %call6 = call i32 @__archive_write_nulls(%struct.archive_write* %12, i64 %14), !dbg !2026
  store i32 %call6, i32* %ret, align 4, !dbg !2027
  %15 = load i32, i32* %ret, align 4, !dbg !2028
  %cmp7 = icmp ne i32 %15, 0, !dbg !2030
  br i1 %cmp7, label %if.then9, label %if.end11, !dbg !2031

if.then9:                                         ; preds = %if.end
  %16 = load i32, i32* %ret, align 4, !dbg !2032
  %conv10 = sext i32 %16 to i64, !dbg !2033
  store i64 %conv10, i64* %retval, align 8, !dbg !2034
  br label %return, !dbg !2034

if.end11:                                         ; preds = %if.end
  %17 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2035
  %sparse_map12 = getelementptr inbounds %struct.pax, %struct.pax* %17, i32 0, i32 4, !dbg !2035
  %length13 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %sparse_map12, i32 0, i32 1, !dbg !2035
  store i64 0, i64* %length13, align 8, !dbg !2035
  br label %if.end14, !dbg !2036

if.end14:                                         ; preds = %if.end11, %entry
  store i64 0, i64* %total, align 8, !dbg !2037
  br label %while.cond, !dbg !2038

while.cond:                                       ; preds = %if.end56, %if.then42, %if.end14
  %18 = load i64, i64* %total, align 8, !dbg !2039
  %19 = load i64, i64* %s.addr, align 8, !dbg !2041
  %cmp15 = icmp ult i64 %18, %19, !dbg !2042
  br i1 %cmp15, label %while.body, label %while.end57, !dbg !2043

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2044, metadata !293), !dbg !2046
  br label %while.cond17, !dbg !2047

while.cond17:                                     ; preds = %while.body23, %while.body
  %20 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2048
  %sparse_list = getelementptr inbounds %struct.pax, %struct.pax* %20, i32 0, i32 6, !dbg !2050
  %21 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list, align 8, !dbg !2050
  %cmp18 = icmp ne %struct.sparse_block* %21, null, !dbg !2051
  br i1 %cmp18, label %land.rhs, label %land.end, !dbg !2052

land.rhs:                                         ; preds = %while.cond17
  %22 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2053
  %sparse_list20 = getelementptr inbounds %struct.pax, %struct.pax* %22, i32 0, i32 6, !dbg !2054
  %23 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list20, align 8, !dbg !2054
  %remaining = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %23, i32 0, i32 3, !dbg !2055
  %24 = load i64, i64* %remaining, align 8, !dbg !2055
  %cmp21 = icmp eq i64 %24, 0, !dbg !2056
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond17
  %25 = phi i1 [ false, %while.cond17 ], [ %cmp21, %land.rhs ]
  br i1 %25, label %while.body23, label %while.end, !dbg !2057

while.body23:                                     ; preds = %land.end
  call void @llvm.dbg.declare(metadata %struct.sparse_block** %sb, metadata !2059, metadata !293), !dbg !2061
  %26 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2062
  %sparse_list24 = getelementptr inbounds %struct.pax, %struct.pax* %26, i32 0, i32 6, !dbg !2063
  %27 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list24, align 8, !dbg !2063
  %next = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %27, i32 0, i32 0, !dbg !2064
  %28 = load %struct.sparse_block*, %struct.sparse_block** %next, align 8, !dbg !2064
  store %struct.sparse_block* %28, %struct.sparse_block** %sb, align 8, !dbg !2061
  %29 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2065
  %sparse_list25 = getelementptr inbounds %struct.pax, %struct.pax* %29, i32 0, i32 6, !dbg !2066
  %30 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list25, align 8, !dbg !2066
  %31 = bitcast %struct.sparse_block* %30 to i8*, !dbg !2065
  call void @free(i8* %31) #7, !dbg !2067
  %32 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !2068
  %33 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2069
  %sparse_list26 = getelementptr inbounds %struct.pax, %struct.pax* %33, i32 0, i32 6, !dbg !2070
  store %struct.sparse_block* %32, %struct.sparse_block** %sparse_list26, align 8, !dbg !2071
  br label %while.cond17, !dbg !2072

while.end:                                        ; preds = %land.end
  %34 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2074
  %sparse_list27 = getelementptr inbounds %struct.pax, %struct.pax* %34, i32 0, i32 6, !dbg !2076
  %35 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list27, align 8, !dbg !2076
  %cmp28 = icmp eq %struct.sparse_block* %35, null, !dbg !2077
  br i1 %cmp28, label %if.then30, label %if.end31, !dbg !2078

if.then30:                                        ; preds = %while.end
  %36 = load i64, i64* %total, align 8, !dbg !2079
  store i64 %36, i64* %retval, align 8, !dbg !2080
  br label %return, !dbg !2080

if.end31:                                         ; preds = %while.end
  %37 = load i8*, i8** %buff.addr, align 8, !dbg !2081
  %38 = load i64, i64* %total, align 8, !dbg !2082
  %add.ptr = getelementptr inbounds i8, i8* %37, i64 %38, !dbg !2083
  store i8* %add.ptr, i8** %p, align 8, !dbg !2084
  %39 = load i64, i64* %s.addr, align 8, !dbg !2085
  %40 = load i64, i64* %total, align 8, !dbg !2086
  %sub = sub i64 %39, %40, !dbg !2087
  store i64 %sub, i64* %ws, align 8, !dbg !2088
  %41 = load i64, i64* %ws, align 8, !dbg !2089
  %42 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2091
  %sparse_list32 = getelementptr inbounds %struct.pax, %struct.pax* %42, i32 0, i32 6, !dbg !2092
  %43 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list32, align 8, !dbg !2092
  %remaining33 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %43, i32 0, i32 3, !dbg !2093
  %44 = load i64, i64* %remaining33, align 8, !dbg !2093
  %cmp34 = icmp ugt i64 %41, %44, !dbg !2094
  br i1 %cmp34, label %if.then36, label %if.end39, !dbg !2095

if.then36:                                        ; preds = %if.end31
  %45 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2096
  %sparse_list37 = getelementptr inbounds %struct.pax, %struct.pax* %45, i32 0, i32 6, !dbg !2097
  %46 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list37, align 8, !dbg !2097
  %remaining38 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %46, i32 0, i32 3, !dbg !2098
  %47 = load i64, i64* %remaining38, align 8, !dbg !2098
  store i64 %47, i64* %ws, align 8, !dbg !2099
  br label %if.end39, !dbg !2100

if.end39:                                         ; preds = %if.then36, %if.end31
  %48 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2101
  %sparse_list40 = getelementptr inbounds %struct.pax, %struct.pax* %48, i32 0, i32 6, !dbg !2103
  %49 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list40, align 8, !dbg !2103
  %is_hole = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %49, i32 0, i32 1, !dbg !2104
  %50 = load i32, i32* %is_hole, align 8, !dbg !2104
  %tobool41 = icmp ne i32 %50, 0, !dbg !2101
  br i1 %tobool41, label %if.then42, label %if.end46, !dbg !2105

if.then42:                                        ; preds = %if.end39
  %51 = load i64, i64* %ws, align 8, !dbg !2106
  %52 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2108
  %sparse_list43 = getelementptr inbounds %struct.pax, %struct.pax* %52, i32 0, i32 6, !dbg !2109
  %53 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list43, align 8, !dbg !2109
  %remaining44 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %53, i32 0, i32 3, !dbg !2110
  %54 = load i64, i64* %remaining44, align 8, !dbg !2111
  %sub45 = sub i64 %54, %51, !dbg !2111
  store i64 %sub45, i64* %remaining44, align 8, !dbg !2111
  %55 = load i64, i64* %ws, align 8, !dbg !2112
  %56 = load i64, i64* %total, align 8, !dbg !2113
  %add = add i64 %56, %55, !dbg !2113
  store i64 %add, i64* %total, align 8, !dbg !2113
  br label %while.cond, !dbg !2114

if.end46:                                         ; preds = %if.end39
  %57 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2115
  %58 = load i8*, i8** %p, align 8, !dbg !2116
  %59 = load i64, i64* %ws, align 8, !dbg !2117
  %call47 = call i32 @__archive_write_output(%struct.archive_write* %57, i8* %58, i64 %59), !dbg !2118
  store i32 %call47, i32* %ret, align 4, !dbg !2119
  %60 = load i64, i64* %ws, align 8, !dbg !2120
  %61 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2121
  %sparse_list48 = getelementptr inbounds %struct.pax, %struct.pax* %61, i32 0, i32 6, !dbg !2122
  %62 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list48, align 8, !dbg !2122
  %remaining49 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %62, i32 0, i32 3, !dbg !2123
  %63 = load i64, i64* %remaining49, align 8, !dbg !2124
  %sub50 = sub i64 %63, %60, !dbg !2124
  store i64 %sub50, i64* %remaining49, align 8, !dbg !2124
  %64 = load i64, i64* %ws, align 8, !dbg !2125
  %65 = load i64, i64* %total, align 8, !dbg !2126
  %add51 = add i64 %65, %64, !dbg !2126
  store i64 %add51, i64* %total, align 8, !dbg !2126
  %66 = load i32, i32* %ret, align 4, !dbg !2127
  %cmp52 = icmp ne i32 %66, 0, !dbg !2129
  br i1 %cmp52, label %if.then54, label %if.end56, !dbg !2130

if.then54:                                        ; preds = %if.end46
  %67 = load i32, i32* %ret, align 4, !dbg !2131
  %conv55 = sext i32 %67 to i64, !dbg !2132
  store i64 %conv55, i64* %retval, align 8, !dbg !2133
  br label %return, !dbg !2133

if.end56:                                         ; preds = %if.end46
  br label %while.cond, !dbg !2134

while.end57:                                      ; preds = %while.cond
  %68 = load i64, i64* %total, align 8, !dbg !2136
  store i64 %68, i64* %retval, align 8, !dbg !2137
  br label %return, !dbg !2137

return:                                           ; preds = %while.end57, %if.then54, %if.then30, %if.then9, %if.then5
  %69 = load i64, i64* %retval, align 8, !dbg !2138
  ret i64 %69, !dbg !2138
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_pax_close(%struct.archive_write* %a) #0 !dbg !280 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2139, metadata !293), !dbg !2140
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2141
  %call = call i32 @__archive_write_nulls(%struct.archive_write* %0, i64 1024), !dbg !2142
  ret i32 %call, !dbg !2143
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_pax_free(%struct.archive_write* %a) #0 !dbg !281 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %pax = alloca %struct.pax*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2144, metadata !293), !dbg !2145
  call void @llvm.dbg.declare(metadata %struct.pax** %pax, metadata !2146, metadata !293), !dbg !2147
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2148
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !2149
  %1 = load i8*, i8** %format_data, align 8, !dbg !2149
  %2 = bitcast i8* %1 to %struct.pax*, !dbg !2150
  store %struct.pax* %2, %struct.pax** %pax, align 8, !dbg !2151
  %3 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2152
  %cmp = icmp eq %struct.pax* %3, null, !dbg !2154
  br i1 %cmp, label %if.then, label %if.end, !dbg !2155

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2156
  br label %return, !dbg !2156

if.end:                                           ; preds = %entry
  %4 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2157
  %pax_header = getelementptr inbounds %struct.pax, %struct.pax* %4, i32 0, i32 3, !dbg !2158
  call void @archive_string_free(%struct.archive_string* %pax_header), !dbg !2159
  %5 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2160
  %sparse_map = getelementptr inbounds %struct.pax, %struct.pax* %5, i32 0, i32 4, !dbg !2161
  call void @archive_string_free(%struct.archive_string* %sparse_map), !dbg !2162
  %6 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2163
  %l_url_encoded_name = getelementptr inbounds %struct.pax, %struct.pax* %6, i32 0, i32 2, !dbg !2164
  call void @archive_string_free(%struct.archive_string* %l_url_encoded_name), !dbg !2165
  %7 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2166
  call void @sparse_list_clear(%struct.pax* %7), !dbg !2167
  %8 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2168
  %9 = bitcast %struct.pax* %8 to i8*, !dbg !2168
  call void @free(i8* %9) #7, !dbg !2169
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2170
  %format_data1 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 14, !dbg !2171
  store i8* null, i8** %format_data1, align 8, !dbg !2172
  store i32 0, i32* %retval, align 4, !dbg !2173
  br label %return, !dbg !2173

return:                                           ; preds = %if.end, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !2174
  ret i32 %11, !dbg !2174
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_pax_finish_entry(%struct.archive_write* %a) #0 !dbg !282 {
entry:
  %a.addr = alloca %struct.archive_write*, align 8
  %pax = alloca %struct.pax*, align 8
  %remaining = alloca i64, align 8
  %ret = alloca i32, align 4
  %sb = alloca %struct.sparse_block*, align 8
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2175, metadata !293), !dbg !2176
  call void @llvm.dbg.declare(metadata %struct.pax** %pax, metadata !2177, metadata !293), !dbg !2178
  call void @llvm.dbg.declare(metadata i64* %remaining, metadata !2179, metadata !293), !dbg !2180
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !2181, metadata !293), !dbg !2182
  %0 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2183
  %format_data = getelementptr inbounds %struct.archive_write, %struct.archive_write* %0, i32 0, i32 14, !dbg !2184
  %1 = load i8*, i8** %format_data, align 8, !dbg !2184
  %2 = bitcast i8* %1 to %struct.pax*, !dbg !2185
  store %struct.pax* %2, %struct.pax** %pax, align 8, !dbg !2186
  %3 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2187
  %entry_bytes_remaining = getelementptr inbounds %struct.pax, %struct.pax* %3, i32 0, i32 0, !dbg !2188
  %4 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !2188
  store i64 %4, i64* %remaining, align 8, !dbg !2189
  %5 = load i64, i64* %remaining, align 8, !dbg !2190
  %cmp = icmp eq i64 %5, 0, !dbg !2192
  br i1 %cmp, label %if.then, label %if.end9, !dbg !2193

if.then:                                          ; preds = %entry
  br label %while.cond, !dbg !2194

while.cond:                                       ; preds = %if.end, %if.then
  %6 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2196
  %sparse_list = getelementptr inbounds %struct.pax, %struct.pax* %6, i32 0, i32 6, !dbg !2198
  %7 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list, align 8, !dbg !2198
  %tobool = icmp ne %struct.sparse_block* %7, null, !dbg !2199
  br i1 %tobool, label %while.body, label %while.end, !dbg !2199

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata %struct.sparse_block** %sb, metadata !2200, metadata !293), !dbg !2202
  %8 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2203
  %sparse_list1 = getelementptr inbounds %struct.pax, %struct.pax* %8, i32 0, i32 6, !dbg !2205
  %9 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list1, align 8, !dbg !2205
  %is_hole = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %9, i32 0, i32 1, !dbg !2206
  %10 = load i32, i32* %is_hole, align 8, !dbg !2206
  %tobool2 = icmp ne i32 %10, 0, !dbg !2203
  br i1 %tobool2, label %if.end, label %if.then3, !dbg !2207

if.then3:                                         ; preds = %while.body
  %11 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2208
  %sparse_list4 = getelementptr inbounds %struct.pax, %struct.pax* %11, i32 0, i32 6, !dbg !2209
  %12 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list4, align 8, !dbg !2209
  %remaining5 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %12, i32 0, i32 3, !dbg !2210
  %13 = load i64, i64* %remaining5, align 8, !dbg !2210
  %14 = load i64, i64* %remaining, align 8, !dbg !2211
  %add = add i64 %14, %13, !dbg !2211
  store i64 %add, i64* %remaining, align 8, !dbg !2211
  br label %if.end, !dbg !2212

if.end:                                           ; preds = %if.then3, %while.body
  %15 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2213
  %sparse_list6 = getelementptr inbounds %struct.pax, %struct.pax* %15, i32 0, i32 6, !dbg !2214
  %16 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list6, align 8, !dbg !2214
  %next = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %16, i32 0, i32 0, !dbg !2215
  %17 = load %struct.sparse_block*, %struct.sparse_block** %next, align 8, !dbg !2215
  store %struct.sparse_block* %17, %struct.sparse_block** %sb, align 8, !dbg !2216
  %18 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2217
  %sparse_list7 = getelementptr inbounds %struct.pax, %struct.pax* %18, i32 0, i32 6, !dbg !2218
  %19 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list7, align 8, !dbg !2218
  %20 = bitcast %struct.sparse_block* %19 to i8*, !dbg !2217
  call void @free(i8* %20) #7, !dbg !2219
  %21 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !2220
  %22 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2221
  %sparse_list8 = getelementptr inbounds %struct.pax, %struct.pax* %22, i32 0, i32 6, !dbg !2222
  store %struct.sparse_block* %21, %struct.sparse_block** %sparse_list8, align 8, !dbg !2223
  br label %while.cond, !dbg !2224

while.end:                                        ; preds = %while.cond
  br label %if.end9, !dbg !2226

if.end9:                                          ; preds = %while.end, %entry
  %23 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2227
  %24 = load i64, i64* %remaining, align 8, !dbg !2228
  %25 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2229
  %entry_padding = getelementptr inbounds %struct.pax, %struct.pax* %25, i32 0, i32 1, !dbg !2230
  %26 = load i64, i64* %entry_padding, align 8, !dbg !2230
  %add10 = add i64 %24, %26, !dbg !2231
  %call = call i32 @__archive_write_nulls(%struct.archive_write* %23, i64 %add10), !dbg !2232
  store i32 %call, i32* %ret, align 4, !dbg !2233
  %27 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2234
  %entry_padding11 = getelementptr inbounds %struct.pax, %struct.pax* %27, i32 0, i32 1, !dbg !2235
  store i64 0, i64* %entry_padding11, align 8, !dbg !2236
  %28 = load %struct.pax*, %struct.pax** %pax, align 8, !dbg !2237
  %entry_bytes_remaining12 = getelementptr inbounds %struct.pax, %struct.pax* %28, i32 0, i32 0, !dbg !2238
  store i64 0, i64* %entry_bytes_remaining12, align 8, !dbg !2239
  %29 = load i32, i32* %ret, align 4, !dbg !2240
  ret i32 %29, !dbg !2241
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string_conv* @archive_string_conversion_to_charset(%struct.archive*, i8*, i32) #2

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @get_entry_hardlink(%struct.archive_write* %a, %struct.archive_entry* %entry1, i8** %name, i64* %length, %struct.archive_string_conv* %sc) #0 !dbg !222 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8**, align 8
  %length.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2242, metadata !293), !dbg !2243
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2244, metadata !293), !dbg !2245
  store i8** %name, i8*** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %name.addr, metadata !2246, metadata !293), !dbg !2247
  store i64* %length, i64** %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %length.addr, metadata !2248, metadata !293), !dbg !2249
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !2250, metadata !293), !dbg !2251
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2252, metadata !293), !dbg !2253
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2254
  %1 = load i8**, i8*** %name.addr, align 8, !dbg !2255
  %2 = load i64*, i64** %length.addr, align 8, !dbg !2256
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !2257
  %call = call i32 @_archive_entry_hardlink_l(%struct.archive_entry* %0, i8** %1, i64* %2, %struct.archive_string_conv* %3), !dbg !2258
  store i32 %call, i32* %r, align 4, !dbg !2259
  %4 = load i32, i32* %r, align 4, !dbg !2260
  %cmp = icmp ne i32 %4, 0, !dbg !2262
  br i1 %cmp, label %if.then, label %if.end5, !dbg !2263

if.then:                                          ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !2264
  %5 = load i32, i32* %call2, align 4, !dbg !2264
  %cmp3 = icmp eq i32 %5, 12, !dbg !2267
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !2268

if.then4:                                         ; preds = %if.then
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2269
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !2271
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.44, i32 0, i32 0)), !dbg !2272
  store i32 -30, i32* %retval, align 4, !dbg !2273
  br label %return, !dbg !2273

if.end:                                           ; preds = %if.then
  store i32 -20, i32* %retval, align 4, !dbg !2274
  br label %return, !dbg !2274

if.end5:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2275
  br label %return, !dbg !2275

return:                                           ; preds = %if.end5, %if.end, %if.then4
  %7 = load i32, i32* %retval, align 4, !dbg !2276
  ret i32 %7, !dbg !2276
}

declare i8* @archive_string_conversion_charset_name(%struct.archive_string_conv*) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #4

declare %struct.archive_string* @archive_string_ensure(%struct.archive_string*, i64) #2

declare void @archive_string_free(%struct.archive_string*) #2

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

declare void @archive_entry_copy_pathname(%struct.archive_entry*, i8*) #2

declare i8* @archive_entry_mac_metadata(%struct.archive_entry*, i64*) #2

declare %struct.archive_entry* @archive_entry_new2(%struct.archive*) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

declare void @archive_entry_free(%struct.archive_entry*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #3

; Function Attrs: nounwind readonly
declare i8* @strrchr(i8*, i32) #4

; Function Attrs: argmemonly nounwind
declare void @llvm.memmove.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_filetype(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_perm(%struct.archive_entry*, i32) #2

declare i32 @archive_entry_perm(%struct.archive_entry*) #2

declare void @archive_entry_set_mtime(%struct.archive_entry*, i64, i64) #2

declare i64 @archive_entry_mtime(%struct.archive_entry*) #2

declare i64 @archive_entry_mtime_nsec(%struct.archive_entry*) #2

declare void @archive_entry_set_gid(%struct.archive_entry*, i64) #2

declare i64 @archive_entry_gid(%struct.archive_entry*) #2

declare void @archive_entry_set_gname(%struct.archive_entry*, i8*) #2

declare i8* @archive_entry_gname(%struct.archive_entry*) #2

declare void @archive_entry_set_uid(%struct.archive_entry*, i64) #2

declare i64 @archive_entry_uid(%struct.archive_entry*) #2

declare void @archive_entry_set_uname(%struct.archive_entry*, i8*) #2

declare i8* @archive_entry_uname(%struct.archive_entry*) #2

declare %struct.archive_entry* @archive_entry_clone(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal void @sparse_list_clear(%struct.pax* %pax) #0 !dbg !226 {
entry:
  %pax.addr = alloca %struct.pax*, align 8
  %sb = alloca %struct.sparse_block*, align 8
  store %struct.pax* %pax, %struct.pax** %pax.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pax** %pax.addr, metadata !2277, metadata !293), !dbg !2278
  br label %while.cond, !dbg !2279

while.cond:                                       ; preds = %while.body, %entry
  %0 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !2280
  %sparse_list = getelementptr inbounds %struct.pax, %struct.pax* %0, i32 0, i32 6, !dbg !2282
  %1 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list, align 8, !dbg !2282
  %cmp = icmp ne %struct.sparse_block* %1, null, !dbg !2283
  br i1 %cmp, label %while.body, label %while.end, !dbg !2284

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata %struct.sparse_block** %sb, metadata !2285, metadata !293), !dbg !2287
  %2 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !2288
  %sparse_list1 = getelementptr inbounds %struct.pax, %struct.pax* %2, i32 0, i32 6, !dbg !2289
  %3 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list1, align 8, !dbg !2289
  store %struct.sparse_block* %3, %struct.sparse_block** %sb, align 8, !dbg !2287
  %4 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !2290
  %next = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %4, i32 0, i32 0, !dbg !2291
  %5 = load %struct.sparse_block*, %struct.sparse_block** %next, align 8, !dbg !2291
  %6 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !2292
  %sparse_list2 = getelementptr inbounds %struct.pax, %struct.pax* %6, i32 0, i32 6, !dbg !2293
  store %struct.sparse_block* %5, %struct.sparse_block** %sparse_list2, align 8, !dbg !2294
  %7 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !2295
  %8 = bitcast %struct.sparse_block* %7 to i8*, !dbg !2295
  call void @free(i8* %8) #7, !dbg !2296
  br label %while.cond, !dbg !2297

while.end:                                        ; preds = %while.cond
  %9 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !2299
  %sparse_tail = getelementptr inbounds %struct.pax, %struct.pax* %9, i32 0, i32 7, !dbg !2300
  store %struct.sparse_block* null, %struct.sparse_block** %sparse_tail, align 8, !dbg !2301
  ret void, !dbg !2302
}

declare i32 @archive_entry_sparse_reset(%struct.archive_entry*) #2

declare i32 @archive_entry_sparse_next(%struct.archive_entry*, i64*, i64*) #2

declare i64 @archive_entry_size(%struct.archive_entry*) #2

declare void @archive_entry_sparse_add_entry(%struct.archive_entry*, i64, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @get_entry_pathname(%struct.archive_write* %a, %struct.archive_entry* %entry1, i8** %name, i64* %length, %struct.archive_string_conv* %sc) #0 !dbg !229 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8**, align 8
  %length.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2303, metadata !293), !dbg !2304
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2305, metadata !293), !dbg !2306
  store i8** %name, i8*** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %name.addr, metadata !2307, metadata !293), !dbg !2308
  store i64* %length, i64** %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %length.addr, metadata !2309, metadata !293), !dbg !2310
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !2311, metadata !293), !dbg !2312
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2313, metadata !293), !dbg !2314
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2315
  %1 = load i8**, i8*** %name.addr, align 8, !dbg !2316
  %2 = load i64*, i64** %length.addr, align 8, !dbg !2317
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !2318
  %call = call i32 @_archive_entry_pathname_l(%struct.archive_entry* %0, i8** %1, i64* %2, %struct.archive_string_conv* %3), !dbg !2319
  store i32 %call, i32* %r, align 4, !dbg !2320
  %4 = load i32, i32* %r, align 4, !dbg !2321
  %cmp = icmp ne i32 %4, 0, !dbg !2323
  br i1 %cmp, label %if.then, label %if.end5, !dbg !2324

if.then:                                          ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !2325
  %5 = load i32, i32* %call2, align 4, !dbg !2325
  %cmp3 = icmp eq i32 %5, 12, !dbg !2328
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !2329

if.then4:                                         ; preds = %if.then
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2330
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !2332
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.45, i32 0, i32 0)), !dbg !2333
  store i32 -30, i32* %retval, align 4, !dbg !2334
  br label %return, !dbg !2334

if.end:                                           ; preds = %if.then
  store i32 -20, i32* %retval, align 4, !dbg !2335
  br label %return, !dbg !2335

if.end5:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2336
  br label %return, !dbg !2336

return:                                           ; preds = %if.end5, %if.end, %if.then4
  %7 = load i32, i32* %retval, align 4, !dbg !2337
  ret i32 %7, !dbg !2337
}

; Function Attrs: nounwind uwtable
define internal i32 @get_entry_uname(%struct.archive_write* %a, %struct.archive_entry* %entry1, i8** %name, i64* %length, %struct.archive_string_conv* %sc) #0 !dbg !230 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8**, align 8
  %length.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2338, metadata !293), !dbg !2339
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2340, metadata !293), !dbg !2341
  store i8** %name, i8*** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %name.addr, metadata !2342, metadata !293), !dbg !2343
  store i64* %length, i64** %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %length.addr, metadata !2344, metadata !293), !dbg !2345
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !2346, metadata !293), !dbg !2347
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2348, metadata !293), !dbg !2349
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2350
  %1 = load i8**, i8*** %name.addr, align 8, !dbg !2351
  %2 = load i64*, i64** %length.addr, align 8, !dbg !2352
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !2353
  %call = call i32 @_archive_entry_uname_l(%struct.archive_entry* %0, i8** %1, i64* %2, %struct.archive_string_conv* %3), !dbg !2354
  store i32 %call, i32* %r, align 4, !dbg !2355
  %4 = load i32, i32* %r, align 4, !dbg !2356
  %cmp = icmp ne i32 %4, 0, !dbg !2358
  br i1 %cmp, label %if.then, label %if.end5, !dbg !2359

if.then:                                          ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !2360
  %5 = load i32, i32* %call2, align 4, !dbg !2360
  %cmp3 = icmp eq i32 %5, 12, !dbg !2363
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !2364

if.then4:                                         ; preds = %if.then
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2365
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !2367
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.46, i32 0, i32 0)), !dbg !2368
  store i32 -30, i32* %retval, align 4, !dbg !2369
  br label %return, !dbg !2369

if.end:                                           ; preds = %if.then
  store i32 -20, i32* %retval, align 4, !dbg !2370
  br label %return, !dbg !2370

if.end5:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2371
  br label %return, !dbg !2371

return:                                           ; preds = %if.end5, %if.end, %if.then4
  %7 = load i32, i32* %retval, align 4, !dbg !2372
  ret i32 %7, !dbg !2372
}

; Function Attrs: nounwind uwtable
define internal i32 @get_entry_gname(%struct.archive_write* %a, %struct.archive_entry* %entry1, i8** %name, i64* %length, %struct.archive_string_conv* %sc) #0 !dbg !231 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8**, align 8
  %length.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2373, metadata !293), !dbg !2374
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2375, metadata !293), !dbg !2376
  store i8** %name, i8*** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %name.addr, metadata !2377, metadata !293), !dbg !2378
  store i64* %length, i64** %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %length.addr, metadata !2379, metadata !293), !dbg !2380
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !2381, metadata !293), !dbg !2382
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2383, metadata !293), !dbg !2384
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2385
  %1 = load i8**, i8*** %name.addr, align 8, !dbg !2386
  %2 = load i64*, i64** %length.addr, align 8, !dbg !2387
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !2388
  %call = call i32 @_archive_entry_gname_l(%struct.archive_entry* %0, i8** %1, i64* %2, %struct.archive_string_conv* %3), !dbg !2389
  store i32 %call, i32* %r, align 4, !dbg !2390
  %4 = load i32, i32* %r, align 4, !dbg !2391
  %cmp = icmp ne i32 %4, 0, !dbg !2393
  br i1 %cmp, label %if.then, label %if.end5, !dbg !2394

if.then:                                          ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !2395
  %5 = load i32, i32* %call2, align 4, !dbg !2395
  %cmp3 = icmp eq i32 %5, 12, !dbg !2398
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !2399

if.then4:                                         ; preds = %if.then
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2400
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !2402
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.47, i32 0, i32 0)), !dbg !2403
  store i32 -30, i32* %retval, align 4, !dbg !2404
  br label %return, !dbg !2404

if.end:                                           ; preds = %if.then
  store i32 -20, i32* %retval, align 4, !dbg !2405
  br label %return, !dbg !2405

if.end5:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2406
  br label %return, !dbg !2406

return:                                           ; preds = %if.end5, %if.end, %if.then4
  %7 = load i32, i32* %retval, align 4, !dbg !2407
  ret i32 %7, !dbg !2407
}

; Function Attrs: nounwind uwtable
define internal i32 @get_entry_symlink(%struct.archive_write* %a, %struct.archive_entry* %entry1, i8** %name, i64* %length, %struct.archive_string_conv* %sc) #0 !dbg !232 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %name.addr = alloca i8**, align 8
  %length.addr = alloca i64*, align 8
  %sc.addr = alloca %struct.archive_string_conv*, align 8
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2408, metadata !293), !dbg !2409
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2410, metadata !293), !dbg !2411
  store i8** %name, i8*** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %name.addr, metadata !2412, metadata !293), !dbg !2413
  store i64* %length, i64** %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %length.addr, metadata !2414, metadata !293), !dbg !2415
  store %struct.archive_string_conv* %sc, %struct.archive_string_conv** %sc.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sc.addr, metadata !2416, metadata !293), !dbg !2417
  call void @llvm.dbg.declare(metadata i32* %r, metadata !2418, metadata !293), !dbg !2419
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2420
  %1 = load i8**, i8*** %name.addr, align 8, !dbg !2421
  %2 = load i64*, i64** %length.addr, align 8, !dbg !2422
  %3 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sc.addr, align 8, !dbg !2423
  %call = call i32 @_archive_entry_symlink_l(%struct.archive_entry* %0, i8** %1, i64* %2, %struct.archive_string_conv* %3), !dbg !2424
  store i32 %call, i32* %r, align 4, !dbg !2425
  %4 = load i32, i32* %r, align 4, !dbg !2426
  %cmp = icmp ne i32 %4, 0, !dbg !2428
  br i1 %cmp, label %if.then, label %if.end5, !dbg !2429

if.then:                                          ; preds = %entry
  %call2 = call i32* @__errno_location() #1, !dbg !2430
  %5 = load i32, i32* %call2, align 4, !dbg !2430
  %cmp3 = icmp eq i32 %5, 12, !dbg !2433
  br i1 %cmp3, label %if.then4, label %if.end, !dbg !2434

if.then4:                                         ; preds = %if.then
  %6 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2435
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %6, i32 0, i32 0, !dbg !2437
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.44, i32 0, i32 0)), !dbg !2438
  store i32 -30, i32* %retval, align 4, !dbg !2439
  br label %return, !dbg !2439

if.end:                                           ; preds = %if.then
  store i32 -20, i32* %retval, align 4, !dbg !2440
  br label %return, !dbg !2440

if.end5:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2441
  br label %return, !dbg !2441

return:                                           ; preds = %if.end5, %if.end, %if.then4
  %7 = load i32, i32* %retval, align 4, !dbg !2442
  ret i32 %7, !dbg !2442
}

; Function Attrs: nounwind uwtable
define internal void @add_pax_attr(%struct.archive_string* %as, i8* %key, i8* %value) #0 !dbg !233 {
entry:
  %as.addr = alloca %struct.archive_string*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !2443, metadata !293), !dbg !2444
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !2445, metadata !293), !dbg !2446
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !2447, metadata !293), !dbg !2448
  %0 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !2449
  %1 = load i8*, i8** %key.addr, align 8, !dbg !2450
  %2 = load i8*, i8** %value.addr, align 8, !dbg !2451
  %3 = load i8*, i8** %value.addr, align 8, !dbg !2452
  %call = call i64 @strlen(i8* %3) #8, !dbg !2453
  call void @add_pax_attr_binary(%struct.archive_string* %0, i8* %1, i8* %2, i64 %call), !dbg !2454
  ret void, !dbg !2456
}

; Function Attrs: nounwind uwtable
define internal i32 @has_non_ASCII(i8* %_p) #0 !dbg !243 {
entry:
  %retval = alloca i32, align 4
  %_p.addr = alloca i8*, align 8
  %p = alloca i8*, align 8
  store i8* %_p, i8** %_p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %_p.addr, metadata !2457, metadata !293), !dbg !2458
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2459, metadata !293), !dbg !2460
  %0 = load i8*, i8** %_p.addr, align 8, !dbg !2461
  store i8* %0, i8** %p, align 8, !dbg !2460
  %1 = load i8*, i8** %p, align 8, !dbg !2462
  %cmp = icmp eq i8* %1, null, !dbg !2464
  br i1 %cmp, label %if.then, label %if.end, !dbg !2465

if.then:                                          ; preds = %entry
  store i32 1, i32* %retval, align 4, !dbg !2466
  br label %return, !dbg !2466

if.end:                                           ; preds = %entry
  br label %while.cond, !dbg !2467

while.cond:                                       ; preds = %while.body, %if.end
  %2 = load i8*, i8** %p, align 8, !dbg !2468
  %3 = load i8, i8* %2, align 1, !dbg !2470
  %conv = zext i8 %3 to i32, !dbg !2470
  %cmp1 = icmp ne i32 %conv, 0, !dbg !2471
  br i1 %cmp1, label %land.rhs, label %land.end, !dbg !2472

land.rhs:                                         ; preds = %while.cond
  %4 = load i8*, i8** %p, align 8, !dbg !2473
  %5 = load i8, i8* %4, align 1, !dbg !2475
  %conv3 = zext i8 %5 to i32, !dbg !2475
  %cmp4 = icmp slt i32 %conv3, 128, !dbg !2476
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %6 = phi i1 [ false, %while.cond ], [ %cmp4, %land.rhs ]
  br i1 %6, label %while.body, label %while.end, !dbg !2477

while.body:                                       ; preds = %land.end
  %7 = load i8*, i8** %p, align 8, !dbg !2479
  %incdec.ptr = getelementptr inbounds i8, i8* %7, i32 1, !dbg !2479
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !2479
  br label %while.cond, !dbg !2480

while.end:                                        ; preds = %land.end
  %8 = load i8*, i8** %p, align 8, !dbg !2482
  %9 = load i8, i8* %8, align 1, !dbg !2483
  %conv6 = zext i8 %9 to i32, !dbg !2483
  %cmp7 = icmp ne i32 %conv6, 0, !dbg !2484
  %conv8 = zext i1 %cmp7 to i32, !dbg !2484
  store i32 %conv8, i32* %retval, align 4, !dbg !2485
  br label %return, !dbg !2485

return:                                           ; preds = %while.end, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !2486
  ret i32 %10, !dbg !2486
}

declare void @archive_entry_set_pathname(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind uwtable
define internal i8* @build_ustar_entry_name(i8* %dest, i8* %src, i64 %src_length, i8* %insert) #0 !dbg !246 {
entry:
  %retval = alloca i8*, align 8
  %dest.addr = alloca i8*, align 8
  %src.addr = alloca i8*, align 8
  %src_length.addr = alloca i64, align 8
  %insert.addr = alloca i8*, align 8
  %prefix = alloca i8*, align 8
  %prefix_end = alloca i8*, align 8
  %suffix = alloca i8*, align 8
  %suffix_end = alloca i8*, align 8
  %filename = alloca i8*, align 8
  %filename_end = alloca i8*, align 8
  %p = alloca i8*, align 8
  %need_slash = alloca i32, align 4
  %suffix_length = alloca i64, align 8
  %insert_length = alloca i64, align 8
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !2487, metadata !293), !dbg !2488
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !2489, metadata !293), !dbg !2490
  store i64 %src_length, i64* %src_length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %src_length.addr, metadata !2491, metadata !293), !dbg !2492
  store i8* %insert, i8** %insert.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %insert.addr, metadata !2493, metadata !293), !dbg !2494
  call void @llvm.dbg.declare(metadata i8** %prefix, metadata !2495, metadata !293), !dbg !2496
  call void @llvm.dbg.declare(metadata i8** %prefix_end, metadata !2497, metadata !293), !dbg !2498
  call void @llvm.dbg.declare(metadata i8** %suffix, metadata !2499, metadata !293), !dbg !2500
  call void @llvm.dbg.declare(metadata i8** %suffix_end, metadata !2501, metadata !293), !dbg !2502
  call void @llvm.dbg.declare(metadata i8** %filename, metadata !2503, metadata !293), !dbg !2504
  call void @llvm.dbg.declare(metadata i8** %filename_end, metadata !2505, metadata !293), !dbg !2506
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2507, metadata !293), !dbg !2508
  call void @llvm.dbg.declare(metadata i32* %need_slash, metadata !2509, metadata !293), !dbg !2510
  store i32 0, i32* %need_slash, align 4, !dbg !2510
  call void @llvm.dbg.declare(metadata i64* %suffix_length, metadata !2511, metadata !293), !dbg !2512
  store i64 99, i64* %suffix_length, align 8, !dbg !2512
  call void @llvm.dbg.declare(metadata i64* %insert_length, metadata !2513, metadata !293), !dbg !2514
  %0 = load i8*, i8** %insert.addr, align 8, !dbg !2515
  %cmp = icmp eq i8* %0, null, !dbg !2517
  br i1 %cmp, label %if.then, label %if.else, !dbg !2518

if.then:                                          ; preds = %entry
  store i64 0, i64* %insert_length, align 8, !dbg !2519
  br label %if.end, !dbg !2520

if.else:                                          ; preds = %entry
  %1 = load i8*, i8** %insert.addr, align 8, !dbg !2521
  %call = call i64 @strlen(i8* %1) #8, !dbg !2522
  %add = add i64 %call, 2, !dbg !2523
  store i64 %add, i64* %insert_length, align 8, !dbg !2524
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %2 = load i64, i64* %src_length.addr, align 8, !dbg !2525
  %cmp1 = icmp ult i64 %2, 100, !dbg !2527
  br i1 %cmp1, label %land.lhs.true, label %if.end5, !dbg !2528

land.lhs.true:                                    ; preds = %if.end
  %3 = load i8*, i8** %insert.addr, align 8, !dbg !2529
  %cmp2 = icmp eq i8* %3, null, !dbg !2531
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !2532

if.then3:                                         ; preds = %land.lhs.true
  %4 = load i8*, i8** %dest.addr, align 8, !dbg !2533
  %5 = load i8*, i8** %src.addr, align 8, !dbg !2535
  %6 = load i64, i64* %src_length.addr, align 8, !dbg !2536
  %call4 = call i8* @strncpy(i8* %4, i8* %5, i64 %6) #7, !dbg !2537
  %7 = load i64, i64* %src_length.addr, align 8, !dbg !2538
  %8 = load i8*, i8** %dest.addr, align 8, !dbg !2539
  %arrayidx = getelementptr inbounds i8, i8* %8, i64 %7, !dbg !2539
  store i8 0, i8* %arrayidx, align 1, !dbg !2540
  %9 = load i8*, i8** %dest.addr, align 8, !dbg !2541
  store i8* %9, i8** %retval, align 8, !dbg !2542
  br label %return, !dbg !2542

if.end5:                                          ; preds = %land.lhs.true, %if.end
  %10 = load i8*, i8** %src.addr, align 8, !dbg !2543
  %11 = load i64, i64* %src_length.addr, align 8, !dbg !2544
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 %11, !dbg !2545
  store i8* %add.ptr, i8** %filename_end, align 8, !dbg !2546
  br label %for.cond, !dbg !2547

for.cond:                                         ; preds = %if.then26, %if.then11, %if.end5
  %12 = load i8*, i8** %filename_end, align 8, !dbg !2548
  %13 = load i8*, i8** %src.addr, align 8, !dbg !2553
  %cmp6 = icmp ugt i8* %12, %13, !dbg !2554
  br i1 %cmp6, label %land.lhs.true7, label %if.end12, !dbg !2555

land.lhs.true7:                                   ; preds = %for.cond
  %14 = load i8*, i8** %filename_end, align 8, !dbg !2556
  %arrayidx8 = getelementptr inbounds i8, i8* %14, i64 -1, !dbg !2556
  %15 = load i8, i8* %arrayidx8, align 1, !dbg !2556
  %conv = sext i8 %15 to i32, !dbg !2556
  %cmp9 = icmp eq i32 %conv, 47, !dbg !2558
  br i1 %cmp9, label %if.then11, label %if.end12, !dbg !2559

if.then11:                                        ; preds = %land.lhs.true7
  %16 = load i8*, i8** %filename_end, align 8, !dbg !2560
  %incdec.ptr = getelementptr inbounds i8, i8* %16, i32 -1, !dbg !2560
  store i8* %incdec.ptr, i8** %filename_end, align 8, !dbg !2560
  store i32 1, i32* %need_slash, align 4, !dbg !2562
  br label %for.cond, !dbg !2563

if.end12:                                         ; preds = %land.lhs.true7, %for.cond
  %17 = load i8*, i8** %filename_end, align 8, !dbg !2564
  %18 = load i8*, i8** %src.addr, align 8, !dbg !2566
  %add.ptr13 = getelementptr inbounds i8, i8* %18, i64 1, !dbg !2567
  %cmp14 = icmp ugt i8* %17, %add.ptr13, !dbg !2568
  br i1 %cmp14, label %land.lhs.true16, label %if.end28, !dbg !2569

land.lhs.true16:                                  ; preds = %if.end12
  %19 = load i8*, i8** %filename_end, align 8, !dbg !2570
  %arrayidx17 = getelementptr inbounds i8, i8* %19, i64 -1, !dbg !2570
  %20 = load i8, i8* %arrayidx17, align 1, !dbg !2570
  %conv18 = sext i8 %20 to i32, !dbg !2570
  %cmp19 = icmp eq i32 %conv18, 46, !dbg !2572
  br i1 %cmp19, label %land.lhs.true21, label %if.end28, !dbg !2573

land.lhs.true21:                                  ; preds = %land.lhs.true16
  %21 = load i8*, i8** %filename_end, align 8, !dbg !2574
  %arrayidx22 = getelementptr inbounds i8, i8* %21, i64 -2, !dbg !2574
  %22 = load i8, i8* %arrayidx22, align 1, !dbg !2574
  %conv23 = sext i8 %22 to i32, !dbg !2574
  %cmp24 = icmp eq i32 %conv23, 47, !dbg !2575
  br i1 %cmp24, label %if.then26, label %if.end28, !dbg !2576

if.then26:                                        ; preds = %land.lhs.true21
  %23 = load i8*, i8** %filename_end, align 8, !dbg !2578
  %add.ptr27 = getelementptr inbounds i8, i8* %23, i64 -2, !dbg !2578
  store i8* %add.ptr27, i8** %filename_end, align 8, !dbg !2578
  store i32 1, i32* %need_slash, align 4, !dbg !2580
  br label %for.cond, !dbg !2581

if.end28:                                         ; preds = %land.lhs.true21, %land.lhs.true16, %if.end12
  br label %for.end, !dbg !2582

for.end:                                          ; preds = %if.end28
  %24 = load i32, i32* %need_slash, align 4, !dbg !2583
  %tobool = icmp ne i32 %24, 0, !dbg !2583
  br i1 %tobool, label %if.then29, label %if.end30, !dbg !2585

if.then29:                                        ; preds = %for.end
  %25 = load i64, i64* %suffix_length, align 8, !dbg !2586
  %dec = add i64 %25, -1, !dbg !2586
  store i64 %dec, i64* %suffix_length, align 8, !dbg !2586
  br label %if.end30, !dbg !2587

if.end30:                                         ; preds = %if.then29, %for.end
  %26 = load i8*, i8** %filename_end, align 8, !dbg !2588
  %add.ptr31 = getelementptr inbounds i8, i8* %26, i64 -1, !dbg !2589
  store i8* %add.ptr31, i8** %filename, align 8, !dbg !2590
  br label %while.cond, !dbg !2591

while.cond:                                       ; preds = %while.body, %if.end30
  %27 = load i8*, i8** %filename, align 8, !dbg !2592
  %28 = load i8*, i8** %src.addr, align 8, !dbg !2594
  %cmp32 = icmp ugt i8* %27, %28, !dbg !2595
  br i1 %cmp32, label %land.rhs, label %land.end, !dbg !2596

land.rhs:                                         ; preds = %while.cond
  %29 = load i8*, i8** %filename, align 8, !dbg !2597
  %30 = load i8, i8* %29, align 1, !dbg !2599
  %conv34 = sext i8 %30 to i32, !dbg !2599
  %cmp35 = icmp ne i32 %conv34, 47, !dbg !2600
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %31 = phi i1 [ false, %while.cond ], [ %cmp35, %land.rhs ]
  br i1 %31, label %while.body, label %while.end, !dbg !2601

while.body:                                       ; preds = %land.end
  %32 = load i8*, i8** %filename, align 8, !dbg !2603
  %incdec.ptr37 = getelementptr inbounds i8, i8* %32, i32 -1, !dbg !2603
  store i8* %incdec.ptr37, i8** %filename, align 8, !dbg !2603
  br label %while.cond, !dbg !2604

while.end:                                        ; preds = %land.end
  %33 = load i8*, i8** %filename, align 8, !dbg !2606
  %34 = load i8, i8* %33, align 1, !dbg !2608
  %conv38 = sext i8 %34 to i32, !dbg !2608
  %cmp39 = icmp eq i32 %conv38, 47, !dbg !2609
  br i1 %cmp39, label %land.lhs.true41, label %if.end47, !dbg !2610

land.lhs.true41:                                  ; preds = %while.end
  %35 = load i8*, i8** %filename, align 8, !dbg !2611
  %36 = load i8*, i8** %filename_end, align 8, !dbg !2613
  %add.ptr42 = getelementptr inbounds i8, i8* %36, i64 -1, !dbg !2614
  %cmp43 = icmp ult i8* %35, %add.ptr42, !dbg !2615
  br i1 %cmp43, label %if.then45, label %if.end47, !dbg !2616

if.then45:                                        ; preds = %land.lhs.true41
  %37 = load i8*, i8** %filename, align 8, !dbg !2617
  %incdec.ptr46 = getelementptr inbounds i8, i8* %37, i32 1, !dbg !2617
  store i8* %incdec.ptr46, i8** %filename, align 8, !dbg !2617
  br label %if.end47, !dbg !2618

if.end47:                                         ; preds = %if.then45, %land.lhs.true41, %while.end
  %38 = load i64, i64* %insert_length, align 8, !dbg !2619
  %39 = load i64, i64* %suffix_length, align 8, !dbg !2620
  %sub = sub i64 %39, %38, !dbg !2620
  store i64 %sub, i64* %suffix_length, align 8, !dbg !2620
  %40 = load i8*, i8** %filename_end, align 8, !dbg !2621
  %41 = load i8*, i8** %filename, align 8, !dbg !2623
  %42 = load i64, i64* %suffix_length, align 8, !dbg !2624
  %add.ptr48 = getelementptr inbounds i8, i8* %41, i64 %42, !dbg !2625
  %cmp49 = icmp ugt i8* %40, %add.ptr48, !dbg !2626
  br i1 %cmp49, label %if.then51, label %if.end53, !dbg !2627

if.then51:                                        ; preds = %if.end47
  %43 = load i8*, i8** %filename, align 8, !dbg !2628
  %44 = load i64, i64* %suffix_length, align 8, !dbg !2629
  %add.ptr52 = getelementptr inbounds i8, i8* %43, i64 %44, !dbg !2630
  store i8* %add.ptr52, i8** %filename_end, align 8, !dbg !2631
  br label %if.end53, !dbg !2632

if.end53:                                         ; preds = %if.then51, %if.end47
  %45 = load i8*, i8** %filename_end, align 8, !dbg !2633
  %46 = load i8*, i8** %filename, align 8, !dbg !2634
  %sub.ptr.lhs.cast = ptrtoint i8* %45 to i64, !dbg !2635
  %sub.ptr.rhs.cast = ptrtoint i8* %46 to i64, !dbg !2635
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2635
  %47 = load i64, i64* %suffix_length, align 8, !dbg !2636
  %sub54 = sub i64 %47, %sub.ptr.sub, !dbg !2636
  store i64 %sub54, i64* %suffix_length, align 8, !dbg !2636
  %48 = load i8*, i8** %src.addr, align 8, !dbg !2637
  store i8* %48, i8** %prefix, align 8, !dbg !2638
  %49 = load i8*, i8** %prefix, align 8, !dbg !2639
  %add.ptr55 = getelementptr inbounds i8, i8* %49, i64 155, !dbg !2640
  store i8* %add.ptr55, i8** %prefix_end, align 8, !dbg !2641
  %50 = load i8*, i8** %prefix_end, align 8, !dbg !2642
  %51 = load i8*, i8** %filename, align 8, !dbg !2644
  %cmp56 = icmp ugt i8* %50, %51, !dbg !2645
  br i1 %cmp56, label %if.then58, label %if.end59, !dbg !2646

if.then58:                                        ; preds = %if.end53
  %52 = load i8*, i8** %filename, align 8, !dbg !2647
  store i8* %52, i8** %prefix_end, align 8, !dbg !2648
  br label %if.end59, !dbg !2649

if.end59:                                         ; preds = %if.then58, %if.end53
  br label %while.cond60, !dbg !2650

while.cond60:                                     ; preds = %while.body68, %if.end59
  %53 = load i8*, i8** %prefix_end, align 8, !dbg !2651
  %54 = load i8*, i8** %prefix, align 8, !dbg !2652
  %cmp61 = icmp ugt i8* %53, %54, !dbg !2653
  br i1 %cmp61, label %land.rhs63, label %land.end67, !dbg !2654

land.rhs63:                                       ; preds = %while.cond60
  %55 = load i8*, i8** %prefix_end, align 8, !dbg !2655
  %56 = load i8, i8* %55, align 1, !dbg !2656
  %conv64 = sext i8 %56 to i32, !dbg !2656
  %cmp65 = icmp ne i32 %conv64, 47, !dbg !2657
  br label %land.end67

land.end67:                                       ; preds = %land.rhs63, %while.cond60
  %57 = phi i1 [ false, %while.cond60 ], [ %cmp65, %land.rhs63 ]
  br i1 %57, label %while.body68, label %while.end70, !dbg !2658

while.body68:                                     ; preds = %land.end67
  %58 = load i8*, i8** %prefix_end, align 8, !dbg !2659
  %incdec.ptr69 = getelementptr inbounds i8, i8* %58, i32 -1, !dbg !2659
  store i8* %incdec.ptr69, i8** %prefix_end, align 8, !dbg !2659
  br label %while.cond60, !dbg !2660

while.end70:                                      ; preds = %land.end67
  %59 = load i8*, i8** %prefix_end, align 8, !dbg !2661
  %60 = load i8*, i8** %filename, align 8, !dbg !2663
  %cmp71 = icmp ult i8* %59, %60, !dbg !2664
  br i1 %cmp71, label %land.lhs.true73, label %if.end79, !dbg !2665

land.lhs.true73:                                  ; preds = %while.end70
  %61 = load i8*, i8** %prefix_end, align 8, !dbg !2666
  %62 = load i8, i8* %61, align 1, !dbg !2668
  %conv74 = sext i8 %62 to i32, !dbg !2668
  %cmp75 = icmp eq i32 %conv74, 47, !dbg !2669
  br i1 %cmp75, label %if.then77, label %if.end79, !dbg !2670

if.then77:                                        ; preds = %land.lhs.true73
  %63 = load i8*, i8** %prefix_end, align 8, !dbg !2671
  %incdec.ptr78 = getelementptr inbounds i8, i8* %63, i32 1, !dbg !2671
  store i8* %incdec.ptr78, i8** %prefix_end, align 8, !dbg !2671
  br label %if.end79, !dbg !2672

if.end79:                                         ; preds = %if.then77, %land.lhs.true73, %while.end70
  %64 = load i8*, i8** %prefix_end, align 8, !dbg !2673
  store i8* %64, i8** %suffix, align 8, !dbg !2674
  %65 = load i8*, i8** %suffix, align 8, !dbg !2675
  %66 = load i64, i64* %suffix_length, align 8, !dbg !2676
  %add.ptr80 = getelementptr inbounds i8, i8* %65, i64 %66, !dbg !2677
  store i8* %add.ptr80, i8** %suffix_end, align 8, !dbg !2678
  %67 = load i8*, i8** %suffix_end, align 8, !dbg !2679
  %68 = load i8*, i8** %filename, align 8, !dbg !2681
  %cmp81 = icmp ugt i8* %67, %68, !dbg !2682
  br i1 %cmp81, label %if.then83, label %if.end84, !dbg !2683

if.then83:                                        ; preds = %if.end79
  %69 = load i8*, i8** %filename, align 8, !dbg !2684
  store i8* %69, i8** %suffix_end, align 8, !dbg !2685
  br label %if.end84, !dbg !2686

if.end84:                                         ; preds = %if.then83, %if.end79
  %70 = load i8*, i8** %suffix_end, align 8, !dbg !2687
  %71 = load i8*, i8** %suffix, align 8, !dbg !2689
  %cmp85 = icmp ult i8* %70, %71, !dbg !2690
  br i1 %cmp85, label %if.then87, label %if.end88, !dbg !2691

if.then87:                                        ; preds = %if.end84
  %72 = load i8*, i8** %suffix, align 8, !dbg !2692
  store i8* %72, i8** %suffix_end, align 8, !dbg !2693
  br label %if.end88, !dbg !2694

if.end88:                                         ; preds = %if.then87, %if.end84
  br label %while.cond89, !dbg !2695

while.cond89:                                     ; preds = %while.body97, %if.end88
  %73 = load i8*, i8** %suffix_end, align 8, !dbg !2696
  %74 = load i8*, i8** %suffix, align 8, !dbg !2697
  %cmp90 = icmp ugt i8* %73, %74, !dbg !2698
  br i1 %cmp90, label %land.rhs92, label %land.end96, !dbg !2699

land.rhs92:                                       ; preds = %while.cond89
  %75 = load i8*, i8** %suffix_end, align 8, !dbg !2700
  %76 = load i8, i8* %75, align 1, !dbg !2701
  %conv93 = sext i8 %76 to i32, !dbg !2701
  %cmp94 = icmp ne i32 %conv93, 47, !dbg !2702
  br label %land.end96

land.end96:                                       ; preds = %land.rhs92, %while.cond89
  %77 = phi i1 [ false, %while.cond89 ], [ %cmp94, %land.rhs92 ]
  br i1 %77, label %while.body97, label %while.end99, !dbg !2703

while.body97:                                     ; preds = %land.end96
  %78 = load i8*, i8** %suffix_end, align 8, !dbg !2704
  %incdec.ptr98 = getelementptr inbounds i8, i8* %78, i32 -1, !dbg !2704
  store i8* %incdec.ptr98, i8** %suffix_end, align 8, !dbg !2704
  br label %while.cond89, !dbg !2705

while.end99:                                      ; preds = %land.end96
  %79 = load i8*, i8** %suffix_end, align 8, !dbg !2706
  %80 = load i8*, i8** %filename, align 8, !dbg !2708
  %cmp100 = icmp ult i8* %79, %80, !dbg !2709
  br i1 %cmp100, label %land.lhs.true102, label %if.end108, !dbg !2710

land.lhs.true102:                                 ; preds = %while.end99
  %81 = load i8*, i8** %suffix_end, align 8, !dbg !2711
  %82 = load i8, i8* %81, align 1, !dbg !2713
  %conv103 = sext i8 %82 to i32, !dbg !2713
  %cmp104 = icmp eq i32 %conv103, 47, !dbg !2714
  br i1 %cmp104, label %if.then106, label %if.end108, !dbg !2715

if.then106:                                       ; preds = %land.lhs.true102
  %83 = load i8*, i8** %suffix_end, align 8, !dbg !2716
  %incdec.ptr107 = getelementptr inbounds i8, i8* %83, i32 1, !dbg !2716
  store i8* %incdec.ptr107, i8** %suffix_end, align 8, !dbg !2716
  br label %if.end108, !dbg !2717

if.end108:                                        ; preds = %if.then106, %land.lhs.true102, %while.end99
  %84 = load i8*, i8** %dest.addr, align 8, !dbg !2718
  store i8* %84, i8** %p, align 8, !dbg !2719
  %85 = load i8*, i8** %prefix_end, align 8, !dbg !2720
  %86 = load i8*, i8** %prefix, align 8, !dbg !2722
  %cmp109 = icmp ugt i8* %85, %86, !dbg !2723
  br i1 %cmp109, label %if.then111, label %if.end120, !dbg !2724

if.then111:                                       ; preds = %if.end108
  %87 = load i8*, i8** %p, align 8, !dbg !2725
  %88 = load i8*, i8** %prefix, align 8, !dbg !2727
  %89 = load i8*, i8** %prefix_end, align 8, !dbg !2728
  %90 = load i8*, i8** %prefix, align 8, !dbg !2729
  %sub.ptr.lhs.cast112 = ptrtoint i8* %89 to i64, !dbg !2730
  %sub.ptr.rhs.cast113 = ptrtoint i8* %90 to i64, !dbg !2730
  %sub.ptr.sub114 = sub i64 %sub.ptr.lhs.cast112, %sub.ptr.rhs.cast113, !dbg !2730
  %call115 = call i8* @strncpy(i8* %87, i8* %88, i64 %sub.ptr.sub114) #7, !dbg !2731
  %91 = load i8*, i8** %prefix_end, align 8, !dbg !2732
  %92 = load i8*, i8** %prefix, align 8, !dbg !2733
  %sub.ptr.lhs.cast116 = ptrtoint i8* %91 to i64, !dbg !2734
  %sub.ptr.rhs.cast117 = ptrtoint i8* %92 to i64, !dbg !2734
  %sub.ptr.sub118 = sub i64 %sub.ptr.lhs.cast116, %sub.ptr.rhs.cast117, !dbg !2734
  %93 = load i8*, i8** %p, align 8, !dbg !2735
  %add.ptr119 = getelementptr inbounds i8, i8* %93, i64 %sub.ptr.sub118, !dbg !2735
  store i8* %add.ptr119, i8** %p, align 8, !dbg !2735
  br label %if.end120, !dbg !2736

if.end120:                                        ; preds = %if.then111, %if.end108
  %94 = load i8*, i8** %suffix_end, align 8, !dbg !2737
  %95 = load i8*, i8** %suffix, align 8, !dbg !2739
  %cmp121 = icmp ugt i8* %94, %95, !dbg !2740
  br i1 %cmp121, label %if.then123, label %if.end132, !dbg !2741

if.then123:                                       ; preds = %if.end120
  %96 = load i8*, i8** %p, align 8, !dbg !2742
  %97 = load i8*, i8** %suffix, align 8, !dbg !2744
  %98 = load i8*, i8** %suffix_end, align 8, !dbg !2745
  %99 = load i8*, i8** %suffix, align 8, !dbg !2746
  %sub.ptr.lhs.cast124 = ptrtoint i8* %98 to i64, !dbg !2747
  %sub.ptr.rhs.cast125 = ptrtoint i8* %99 to i64, !dbg !2747
  %sub.ptr.sub126 = sub i64 %sub.ptr.lhs.cast124, %sub.ptr.rhs.cast125, !dbg !2747
  %call127 = call i8* @strncpy(i8* %96, i8* %97, i64 %sub.ptr.sub126) #7, !dbg !2748
  %100 = load i8*, i8** %suffix_end, align 8, !dbg !2749
  %101 = load i8*, i8** %suffix, align 8, !dbg !2750
  %sub.ptr.lhs.cast128 = ptrtoint i8* %100 to i64, !dbg !2751
  %sub.ptr.rhs.cast129 = ptrtoint i8* %101 to i64, !dbg !2751
  %sub.ptr.sub130 = sub i64 %sub.ptr.lhs.cast128, %sub.ptr.rhs.cast129, !dbg !2751
  %102 = load i8*, i8** %p, align 8, !dbg !2752
  %add.ptr131 = getelementptr inbounds i8, i8* %102, i64 %sub.ptr.sub130, !dbg !2752
  store i8* %add.ptr131, i8** %p, align 8, !dbg !2752
  br label %if.end132, !dbg !2753

if.end132:                                        ; preds = %if.then123, %if.end120
  %103 = load i8*, i8** %insert.addr, align 8, !dbg !2754
  %cmp133 = icmp ne i8* %103, null, !dbg !2756
  br i1 %cmp133, label %if.then135, label %if.end140, !dbg !2757

if.then135:                                       ; preds = %if.end132
  %104 = load i8*, i8** %p, align 8, !dbg !2758
  %105 = load i8*, i8** %insert.addr, align 8, !dbg !2760
  %call136 = call i8* @strcpy(i8* %104, i8* %105) #7, !dbg !2761
  %106 = load i8*, i8** %insert.addr, align 8, !dbg !2762
  %call137 = call i64 @strlen(i8* %106) #8, !dbg !2763
  %107 = load i8*, i8** %p, align 8, !dbg !2764
  %add.ptr138 = getelementptr inbounds i8, i8* %107, i64 %call137, !dbg !2764
  store i8* %add.ptr138, i8** %p, align 8, !dbg !2764
  %108 = load i8*, i8** %p, align 8, !dbg !2765
  %incdec.ptr139 = getelementptr inbounds i8, i8* %108, i32 1, !dbg !2765
  store i8* %incdec.ptr139, i8** %p, align 8, !dbg !2765
  store i8 47, i8* %108, align 1, !dbg !2766
  br label %if.end140, !dbg !2767

if.end140:                                        ; preds = %if.then135, %if.end132
  %109 = load i8*, i8** %p, align 8, !dbg !2768
  %110 = load i8*, i8** %filename, align 8, !dbg !2769
  %111 = load i8*, i8** %filename_end, align 8, !dbg !2770
  %112 = load i8*, i8** %filename, align 8, !dbg !2771
  %sub.ptr.lhs.cast141 = ptrtoint i8* %111 to i64, !dbg !2772
  %sub.ptr.rhs.cast142 = ptrtoint i8* %112 to i64, !dbg !2772
  %sub.ptr.sub143 = sub i64 %sub.ptr.lhs.cast141, %sub.ptr.rhs.cast142, !dbg !2772
  %call144 = call i8* @strncpy(i8* %109, i8* %110, i64 %sub.ptr.sub143) #7, !dbg !2773
  %113 = load i8*, i8** %filename_end, align 8, !dbg !2774
  %114 = load i8*, i8** %filename, align 8, !dbg !2775
  %sub.ptr.lhs.cast145 = ptrtoint i8* %113 to i64, !dbg !2776
  %sub.ptr.rhs.cast146 = ptrtoint i8* %114 to i64, !dbg !2776
  %sub.ptr.sub147 = sub i64 %sub.ptr.lhs.cast145, %sub.ptr.rhs.cast146, !dbg !2776
  %115 = load i8*, i8** %p, align 8, !dbg !2777
  %add.ptr148 = getelementptr inbounds i8, i8* %115, i64 %sub.ptr.sub147, !dbg !2777
  store i8* %add.ptr148, i8** %p, align 8, !dbg !2777
  %116 = load i32, i32* %need_slash, align 4, !dbg !2778
  %tobool149 = icmp ne i32 %116, 0, !dbg !2778
  br i1 %tobool149, label %if.then150, label %if.end152, !dbg !2780

if.then150:                                       ; preds = %if.end140
  %117 = load i8*, i8** %p, align 8, !dbg !2781
  %incdec.ptr151 = getelementptr inbounds i8, i8* %117, i32 1, !dbg !2781
  store i8* %incdec.ptr151, i8** %p, align 8, !dbg !2781
  store i8 47, i8* %117, align 1, !dbg !2782
  br label %if.end152, !dbg !2783

if.end152:                                        ; preds = %if.then150, %if.end140
  %118 = load i8*, i8** %p, align 8, !dbg !2784
  store i8 0, i8* %118, align 1, !dbg !2785
  %119 = load i8*, i8** %dest.addr, align 8, !dbg !2786
  store i8* %119, i8** %retval, align 8, !dbg !2787
  br label %return, !dbg !2787

return:                                           ; preds = %if.end152, %if.then3
  %120 = load i8*, i8** %retval, align 8, !dbg !2788
  ret i8* %120, !dbg !2788
}

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #4

declare void @archive_entry_set_hardlink(%struct.archive_entry*, i8*) #2

declare void @archive_entry_set_symlink(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind uwtable
define internal void @add_pax_attr_int(%struct.archive_string* %as, i8* %key, i64 %value) #0 !dbg !249 {
entry:
  %as.addr = alloca %struct.archive_string*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i64, align 8
  %tmp = alloca [25 x i8], align 16
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !2789, metadata !293), !dbg !2790
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !2791, metadata !293), !dbg !2792
  store i64 %value, i64* %value.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %value.addr, metadata !2793, metadata !293), !dbg !2794
  call void @llvm.dbg.declare(metadata [25 x i8]* %tmp, metadata !2795, metadata !293), !dbg !2799
  %arrayidx = getelementptr inbounds [25 x i8], [25 x i8]* %tmp, i64 0, i64 24, !dbg !2800
  store i8 0, i8* %arrayidx, align 8, !dbg !2801
  %0 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !2802
  %1 = load i8*, i8** %key.addr, align 8, !dbg !2803
  %arraydecay = getelementptr inbounds [25 x i8], [25 x i8]* %tmp, i32 0, i32 0, !dbg !2804
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 25, !dbg !2805
  %add.ptr1 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !2806
  %2 = load i64, i64* %value.addr, align 8, !dbg !2807
  %call = call i8* @format_int(i8* %add.ptr1, i64 %2), !dbg !2808
  call void @add_pax_attr(%struct.archive_string* %0, i8* %1, i8* %call), !dbg !2809
  ret void, !dbg !2811
}

declare i64 @archive_entry_rdevmajor(%struct.archive_entry*) #2

declare i64 @archive_entry_rdevminor(%struct.archive_entry*) #2

declare i8* @archive_entry_fflags_text(%struct.archive_entry*) #2

declare i32 @archive_entry_xattr_count(%struct.archive_entry*) #2

declare i32 @archive_entry_acl_types(%struct.archive_entry*) #2

declare i64 @archive_entry_ctime(%struct.archive_entry*) #2

declare i64 @archive_entry_ctime_nsec(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal void @add_pax_attr_time(%struct.archive_string* %as, i8* %key, i64 %sec, i64 %nanos) #0 !dbg !252 {
entry:
  %as.addr = alloca %struct.archive_string*, align 8
  %key.addr = alloca i8*, align 8
  %sec.addr = alloca i64, align 8
  %nanos.addr = alloca i64, align 8
  %digit = alloca i32, align 4
  %i = alloca i32, align 4
  %t = alloca i8*, align 8
  %tmp = alloca [50 x i8], align 16
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !2812, metadata !293), !dbg !2813
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !2814, metadata !293), !dbg !2815
  store i64 %sec, i64* %sec.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %sec.addr, metadata !2816, metadata !293), !dbg !2817
  store i64 %nanos, i64* %nanos.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %nanos.addr, metadata !2818, metadata !293), !dbg !2819
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !2820, metadata !293), !dbg !2821
  call void @llvm.dbg.declare(metadata i32* %i, metadata !2822, metadata !293), !dbg !2823
  call void @llvm.dbg.declare(metadata i8** %t, metadata !2824, metadata !293), !dbg !2825
  call void @llvm.dbg.declare(metadata [50 x i8]* %tmp, metadata !2826, metadata !293), !dbg !2830
  %arrayidx = getelementptr inbounds [50 x i8], [50 x i8]* %tmp, i64 0, i64 49, !dbg !2831
  store i8 0, i8* %arrayidx, align 1, !dbg !2832
  %arraydecay = getelementptr inbounds [50 x i8], [50 x i8]* %tmp, i32 0, i32 0, !dbg !2833
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 50, !dbg !2834
  %add.ptr1 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !2835
  store i8* %add.ptr1, i8** %t, align 8, !dbg !2836
  store i32 0, i32* %digit, align 4, !dbg !2837
  store i32 10, i32* %i, align 4, !dbg !2839
  br label %for.cond, !dbg !2840

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !2841
  %cmp = icmp sgt i32 %0, 0, !dbg !2844
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !2845

land.rhs:                                         ; preds = %for.cond
  %1 = load i32, i32* %digit, align 4, !dbg !2846
  %cmp2 = icmp eq i32 %1, 0, !dbg !2848
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond
  %2 = phi i1 [ false, %for.cond ], [ %cmp2, %land.rhs ]
  br i1 %2, label %for.body, label %for.end, !dbg !2849

for.body:                                         ; preds = %land.end
  %3 = load i64, i64* %nanos.addr, align 8, !dbg !2851
  %rem = urem i64 %3, 10, !dbg !2853
  %conv = trunc i64 %rem to i32, !dbg !2851
  store i32 %conv, i32* %digit, align 4, !dbg !2854
  %4 = load i64, i64* %nanos.addr, align 8, !dbg !2855
  %div = udiv i64 %4, 10, !dbg !2855
  store i64 %div, i64* %nanos.addr, align 8, !dbg !2855
  br label %for.inc, !dbg !2856

for.inc:                                          ; preds = %for.body
  %5 = load i32, i32* %i, align 4, !dbg !2857
  %dec = add nsw i32 %5, -1, !dbg !2857
  store i32 %dec, i32* %i, align 4, !dbg !2857
  br label %for.cond, !dbg !2859

for.end:                                          ; preds = %land.end
  %6 = load i32, i32* %i, align 4, !dbg !2860
  %cmp3 = icmp sgt i32 %6, 0, !dbg !2862
  br i1 %cmp3, label %if.then, label %if.end, !dbg !2863

if.then:                                          ; preds = %for.end
  br label %while.cond, !dbg !2864

while.cond:                                       ; preds = %while.body, %if.then
  %7 = load i32, i32* %i, align 4, !dbg !2866
  %cmp5 = icmp sgt i32 %7, 0, !dbg !2868
  br i1 %cmp5, label %while.body, label %while.end, !dbg !2869

while.body:                                       ; preds = %while.cond
  %8 = load i32, i32* %digit, align 4, !dbg !2870
  %idxprom = sext i32 %8 to i64, !dbg !2872
  %arrayidx7 = getelementptr inbounds [11 x i8], [11 x i8]* @.str.48, i64 0, i64 %idxprom, !dbg !2872
  %9 = load i8, i8* %arrayidx7, align 1, !dbg !2872
  %10 = load i8*, i8** %t, align 8, !dbg !2873
  %incdec.ptr = getelementptr inbounds i8, i8* %10, i32 -1, !dbg !2873
  store i8* %incdec.ptr, i8** %t, align 8, !dbg !2873
  store i8 %9, i8* %incdec.ptr, align 1, !dbg !2874
  %11 = load i64, i64* %nanos.addr, align 8, !dbg !2875
  %rem8 = urem i64 %11, 10, !dbg !2876
  %conv9 = trunc i64 %rem8 to i32, !dbg !2875
  store i32 %conv9, i32* %digit, align 4, !dbg !2877
  %12 = load i64, i64* %nanos.addr, align 8, !dbg !2878
  %div10 = udiv i64 %12, 10, !dbg !2878
  store i64 %div10, i64* %nanos.addr, align 8, !dbg !2878
  %13 = load i32, i32* %i, align 4, !dbg !2879
  %dec11 = add nsw i32 %13, -1, !dbg !2879
  store i32 %dec11, i32* %i, align 4, !dbg !2879
  br label %while.cond, !dbg !2880

while.end:                                        ; preds = %while.cond
  %14 = load i8*, i8** %t, align 8, !dbg !2882
  %incdec.ptr12 = getelementptr inbounds i8, i8* %14, i32 -1, !dbg !2882
  store i8* %incdec.ptr12, i8** %t, align 8, !dbg !2882
  store i8 46, i8* %incdec.ptr12, align 1, !dbg !2883
  br label %if.end, !dbg !2884

if.end:                                           ; preds = %while.end, %for.end
  %15 = load i8*, i8** %t, align 8, !dbg !2885
  %16 = load i64, i64* %sec.addr, align 8, !dbg !2886
  %call = call i8* @format_int(i8* %15, i64 %16), !dbg !2887
  store i8* %call, i8** %t, align 8, !dbg !2888
  %17 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !2889
  %18 = load i8*, i8** %key.addr, align 8, !dbg !2890
  %19 = load i8*, i8** %t, align 8, !dbg !2891
  call void @add_pax_attr(%struct.archive_string* %17, i8* %18, i8* %19), !dbg !2892
  ret void, !dbg !2893
}

declare i64 @archive_entry_atime(%struct.archive_entry*) #2

declare i64 @archive_entry_atime_nsec(%struct.archive_entry*) #2

declare i32 @archive_entry_birthtime_is_set(%struct.archive_entry*) #2

declare i64 @archive_entry_birthtime(%struct.archive_entry*) #2

declare i64 @archive_entry_birthtime_nsec(%struct.archive_entry*) #2

; Function Attrs: nounwind uwtable
define internal i32 @add_pax_acl(%struct.archive_write* %a, %struct.archive_entry* %entry1, %struct.pax* %pax, i32 %flags) #0 !dbg !255 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %pax.addr = alloca %struct.pax*, align 8
  %flags.addr = alloca i32, align 4
  %p = alloca i8*, align 8
  %attr = alloca i8*, align 8
  %acl_types = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !2894, metadata !293), !dbg !2895
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2896, metadata !293), !dbg !2897
  store %struct.pax* %pax, %struct.pax** %pax.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pax** %pax.addr, metadata !2898, metadata !293), !dbg !2899
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !2900, metadata !293), !dbg !2901
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2902, metadata !293), !dbg !2903
  call void @llvm.dbg.declare(metadata i8** %attr, metadata !2904, metadata !293), !dbg !2905
  call void @llvm.dbg.declare(metadata i32* %acl_types, metadata !2906, metadata !293), !dbg !2907
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2908
  %call = call i32 @archive_entry_acl_types(%struct.archive_entry* %0), !dbg !2909
  store i32 %call, i32* %acl_types, align 4, !dbg !2910
  %1 = load i32, i32* %acl_types, align 4, !dbg !2911
  %and = and i32 %1, 15360, !dbg !2913
  %cmp = icmp ne i32 %and, 0, !dbg !2914
  br i1 %cmp, label %if.then, label %if.else, !dbg !2915

if.then:                                          ; preds = %entry
  store i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.49, i32 0, i32 0), i8** %attr, align 8, !dbg !2916
  br label %if.end11, !dbg !2917

if.else:                                          ; preds = %entry
  %2 = load i32, i32* %flags.addr, align 4, !dbg !2918
  %and2 = and i32 %2, 256, !dbg !2920
  %cmp3 = icmp ne i32 %and2, 0, !dbg !2921
  br i1 %cmp3, label %if.then4, label %if.else5, !dbg !2922

if.then4:                                         ; preds = %if.else
  store i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.50, i32 0, i32 0), i8** %attr, align 8, !dbg !2923
  br label %if.end10, !dbg !2924

if.else5:                                         ; preds = %if.else
  %3 = load i32, i32* %flags.addr, align 4, !dbg !2925
  %and6 = and i32 %3, 512, !dbg !2927
  %cmp7 = icmp ne i32 %and6, 0, !dbg !2928
  br i1 %cmp7, label %if.then8, label %if.else9, !dbg !2929

if.then8:                                         ; preds = %if.else5
  store i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.51, i32 0, i32 0), i8** %attr, align 8, !dbg !2930
  br label %if.end, !dbg !2931

if.else9:                                         ; preds = %if.else5
  store i32 -30, i32* %retval, align 4, !dbg !2932
  br label %return, !dbg !2932

if.end:                                           ; preds = %if.then8
  br label %if.end10

if.end10:                                         ; preds = %if.end, %if.then4
  br label %if.end11

if.end11:                                         ; preds = %if.end10, %if.then
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2933
  %5 = load i32, i32* %flags.addr, align 4, !dbg !2934
  %6 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !2935
  %sconv_utf8 = getelementptr inbounds %struct.pax, %struct.pax* %6, i32 0, i32 8, !dbg !2936
  %7 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_utf8, align 8, !dbg !2936
  %call12 = call i8* @_archive_entry_acl_to_text_l(%struct.archive_entry* %4, i64* null, i32 %5, %struct.archive_string_conv* %7), !dbg !2937
  store i8* %call12, i8** %p, align 8, !dbg !2938
  %8 = load i8*, i8** %p, align 8, !dbg !2939
  %cmp13 = icmp eq i8* %8, null, !dbg !2941
  br i1 %cmp13, label %if.then14, label %if.else20, !dbg !2942

if.then14:                                        ; preds = %if.end11
  %call15 = call i32* @__errno_location() #1, !dbg !2943
  %9 = load i32, i32* %call15, align 4, !dbg !2943
  %cmp16 = icmp eq i32 %9, 12, !dbg !2946
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !2947

if.then17:                                        ; preds = %if.then14
  %10 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2948
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %10, i32 0, i32 0, !dbg !2950
  %11 = load i8*, i8** %attr, align 8, !dbg !2951
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.52, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.53, i32 0, i32 0), i8* %11), !dbg !2952
  store i32 -30, i32* %retval, align 4, !dbg !2953
  br label %return, !dbg !2953

if.end18:                                         ; preds = %if.then14
  %12 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !2954
  %archive19 = getelementptr inbounds %struct.archive_write, %struct.archive_write* %12, i32 0, i32 0, !dbg !2955
  %13 = load i8*, i8** %attr, align 8, !dbg !2956
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive19, i32 84, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.54, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.55, i32 0, i32 0), i8* %13, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.56, i32 0, i32 0)), !dbg !2957
  store i32 -20, i32* %retval, align 4, !dbg !2958
  br label %return, !dbg !2958

if.else20:                                        ; preds = %if.end11
  %14 = load i8*, i8** %p, align 8, !dbg !2959
  %15 = load i8, i8* %14, align 1, !dbg !2961
  %conv = sext i8 %15 to i32, !dbg !2961
  %cmp21 = icmp ne i32 %conv, 0, !dbg !2962
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !2963

if.then23:                                        ; preds = %if.else20
  %16 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !2964
  %pax_header = getelementptr inbounds %struct.pax, %struct.pax* %16, i32 0, i32 3, !dbg !2966
  %17 = load i8*, i8** %attr, align 8, !dbg !2967
  %18 = load i8*, i8** %p, align 8, !dbg !2968
  call void @add_pax_attr(%struct.archive_string* %pax_header, i8* %17, i8* %18), !dbg !2969
  %19 = load i8*, i8** %p, align 8, !dbg !2970
  call void @free(i8* %19) #7, !dbg !2971
  br label %if.end24, !dbg !2972

if.end24:                                         ; preds = %if.then23, %if.else20
  br label %if.end25

if.end25:                                         ; preds = %if.end24
  store i32 0, i32* %retval, align 4, !dbg !2973
  br label %return, !dbg !2973

return:                                           ; preds = %if.end25, %if.end18, %if.then17, %if.else9
  %20 = load i32, i32* %retval, align 4, !dbg !2974
  ret i32 %20, !dbg !2974
}

; Function Attrs: nounwind uwtable
define internal i8* @build_gnu_sparse_name(i8* %dest, i8* %src) #0 !dbg !258 {
entry:
  %retval = alloca i8*, align 8
  %dest.addr = alloca i8*, align 8
  %src.addr = alloca i8*, align 8
  %buff = alloca [64 x i8], align 16
  %p = alloca i8*, align 8
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !2975, metadata !293), !dbg !2976
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !2977, metadata !293), !dbg !2978
  call void @llvm.dbg.declare(metadata [64 x i8]* %buff, metadata !2979, metadata !293), !dbg !2981
  call void @llvm.dbg.declare(metadata i8** %p, metadata !2982, metadata !293), !dbg !2983
  %0 = load i8*, i8** %src.addr, align 8, !dbg !2984
  %cmp = icmp eq i8* %0, null, !dbg !2986
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !2987

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %src.addr, align 8, !dbg !2988
  %2 = load i8, i8* %1, align 1, !dbg !2990
  %conv = sext i8 %2 to i32, !dbg !2990
  %cmp1 = icmp eq i32 %conv, 0, !dbg !2991
  br i1 %cmp1, label %if.then, label %if.end, !dbg !2992

if.then:                                          ; preds = %lor.lhs.false, %entry
  %3 = load i8*, i8** %dest.addr, align 8, !dbg !2993
  %call = call i8* @strcpy(i8* %3, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.57, i32 0, i32 0)) #7, !dbg !2995
  %4 = load i8*, i8** %dest.addr, align 8, !dbg !2996
  store i8* %4, i8** %retval, align 8, !dbg !2997
  br label %return, !dbg !2997

if.end:                                           ; preds = %lor.lhs.false
  %5 = load i8*, i8** %src.addr, align 8, !dbg !2998
  %6 = load i8*, i8** %src.addr, align 8, !dbg !2999
  %call3 = call i64 @strlen(i8* %6) #8, !dbg !3000
  %add.ptr = getelementptr inbounds i8, i8* %5, i64 %call3, !dbg !3001
  store i8* %add.ptr, i8** %p, align 8, !dbg !3002
  br label %for.cond, !dbg !3003

for.cond:                                         ; preds = %if.then24, %if.then9, %if.end
  %7 = load i8*, i8** %p, align 8, !dbg !3004
  %8 = load i8*, i8** %src.addr, align 8, !dbg !3009
  %cmp4 = icmp ugt i8* %7, %8, !dbg !3010
  br i1 %cmp4, label %land.lhs.true, label %if.end10, !dbg !3011

land.lhs.true:                                    ; preds = %for.cond
  %9 = load i8*, i8** %p, align 8, !dbg !3012
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 -1, !dbg !3012
  %10 = load i8, i8* %arrayidx, align 1, !dbg !3012
  %conv6 = sext i8 %10 to i32, !dbg !3012
  %cmp7 = icmp eq i32 %conv6, 47, !dbg !3014
  br i1 %cmp7, label %if.then9, label %if.end10, !dbg !3015

if.then9:                                         ; preds = %land.lhs.true
  %11 = load i8*, i8** %p, align 8, !dbg !3016
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 -1, !dbg !3016
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !3016
  br label %for.cond, !dbg !3018

if.end10:                                         ; preds = %land.lhs.true, %for.cond
  %12 = load i8*, i8** %p, align 8, !dbg !3019
  %13 = load i8*, i8** %src.addr, align 8, !dbg !3021
  %add.ptr11 = getelementptr inbounds i8, i8* %13, i64 1, !dbg !3022
  %cmp12 = icmp ugt i8* %12, %add.ptr11, !dbg !3023
  br i1 %cmp12, label %land.lhs.true14, label %if.end26, !dbg !3024

land.lhs.true14:                                  ; preds = %if.end10
  %14 = load i8*, i8** %p, align 8, !dbg !3025
  %arrayidx15 = getelementptr inbounds i8, i8* %14, i64 -1, !dbg !3025
  %15 = load i8, i8* %arrayidx15, align 1, !dbg !3025
  %conv16 = sext i8 %15 to i32, !dbg !3025
  %cmp17 = icmp eq i32 %conv16, 46, !dbg !3027
  br i1 %cmp17, label %land.lhs.true19, label %if.end26, !dbg !3028

land.lhs.true19:                                  ; preds = %land.lhs.true14
  %16 = load i8*, i8** %p, align 8, !dbg !3029
  %arrayidx20 = getelementptr inbounds i8, i8* %16, i64 -2, !dbg !3029
  %17 = load i8, i8* %arrayidx20, align 1, !dbg !3029
  %conv21 = sext i8 %17 to i32, !dbg !3029
  %cmp22 = icmp eq i32 %conv21, 47, !dbg !3030
  br i1 %cmp22, label %if.then24, label %if.end26, !dbg !3031

if.then24:                                        ; preds = %land.lhs.true19
  %18 = load i8*, i8** %p, align 8, !dbg !3033
  %incdec.ptr25 = getelementptr inbounds i8, i8* %18, i32 -1, !dbg !3033
  store i8* %incdec.ptr25, i8** %p, align 8, !dbg !3033
  br label %for.cond, !dbg !3035

if.end26:                                         ; preds = %land.lhs.true19, %land.lhs.true14, %if.end10
  br label %for.end, !dbg !3036

for.end:                                          ; preds = %if.end26
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3037
  %call27 = call i8* @strcpy(i8* %arraydecay, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.58, i32 0, i32 0)) #7, !dbg !3038
  %19 = load i8*, i8** %dest.addr, align 8, !dbg !3039
  %20 = load i8*, i8** %src.addr, align 8, !dbg !3040
  %21 = load i8*, i8** %p, align 8, !dbg !3041
  %22 = load i8*, i8** %src.addr, align 8, !dbg !3042
  %sub.ptr.lhs.cast = ptrtoint i8* %21 to i64, !dbg !3043
  %sub.ptr.rhs.cast = ptrtoint i8* %22 to i64, !dbg !3043
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !3043
  %arraydecay28 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3044
  %call29 = call i8* @build_ustar_entry_name(i8* %19, i8* %20, i64 %sub.ptr.sub, i8* %arraydecay28), !dbg !3045
  %23 = load i8*, i8** %dest.addr, align 8, !dbg !3046
  store i8* %23, i8** %retval, align 8, !dbg !3047
  br label %return, !dbg !3047

return:                                           ; preds = %for.end, %if.then
  %24 = load i8*, i8** %retval, align 8, !dbg !3048
  ret i8* %24, !dbg !3048
}

declare void @archive_string_sprintf(%struct.archive_string*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @sparse_list_add(%struct.pax* %pax, i64 %offset, i64 %length) #0 !dbg !261 {
entry:
  %retval = alloca i32, align 4
  %pax.addr = alloca %struct.pax*, align 8
  %offset.addr = alloca i64, align 8
  %length.addr = alloca i64, align 8
  %last_offset = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.pax* %pax, %struct.pax** %pax.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pax** %pax.addr, metadata !3049, metadata !293), !dbg !3050
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !3051, metadata !293), !dbg !3052
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !3053, metadata !293), !dbg !3054
  call void @llvm.dbg.declare(metadata i64* %last_offset, metadata !3055, metadata !293), !dbg !3056
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3057, metadata !293), !dbg !3058
  %0 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3059
  %sparse_tail = getelementptr inbounds %struct.pax, %struct.pax* %0, i32 0, i32 7, !dbg !3061
  %1 = load %struct.sparse_block*, %struct.sparse_block** %sparse_tail, align 8, !dbg !3061
  %cmp = icmp eq %struct.sparse_block* %1, null, !dbg !3062
  br i1 %cmp, label %if.then, label %if.else, !dbg !3063

if.then:                                          ; preds = %entry
  store i64 0, i64* %last_offset, align 8, !dbg !3064
  br label %if.end, !dbg !3065

if.else:                                          ; preds = %entry
  %2 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3066
  %sparse_tail1 = getelementptr inbounds %struct.pax, %struct.pax* %2, i32 0, i32 7, !dbg !3068
  %3 = load %struct.sparse_block*, %struct.sparse_block** %sparse_tail1, align 8, !dbg !3068
  %offset2 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %3, i32 0, i32 2, !dbg !3069
  %4 = load i64, i64* %offset2, align 8, !dbg !3069
  %5 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3070
  %sparse_tail3 = getelementptr inbounds %struct.pax, %struct.pax* %5, i32 0, i32 7, !dbg !3071
  %6 = load %struct.sparse_block*, %struct.sparse_block** %sparse_tail3, align 8, !dbg !3071
  %remaining = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %6, i32 0, i32 3, !dbg !3072
  %7 = load i64, i64* %remaining, align 8, !dbg !3072
  %add = add i64 %4, %7, !dbg !3073
  store i64 %add, i64* %last_offset, align 8, !dbg !3074
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %8 = load i64, i64* %last_offset, align 8, !dbg !3075
  %9 = load i64, i64* %offset.addr, align 8, !dbg !3077
  %cmp4 = icmp slt i64 %8, %9, !dbg !3078
  br i1 %cmp4, label %if.then5, label %if.end9, !dbg !3079

if.then5:                                         ; preds = %if.end
  %10 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3080
  %11 = load i64, i64* %last_offset, align 8, !dbg !3082
  %12 = load i64, i64* %offset.addr, align 8, !dbg !3083
  %13 = load i64, i64* %last_offset, align 8, !dbg !3084
  %sub = sub nsw i64 %12, %13, !dbg !3085
  %call = call i32 @_sparse_list_add_block(%struct.pax* %10, i64 %11, i64 %sub, i32 1), !dbg !3086
  store i32 %call, i32* %r, align 4, !dbg !3087
  %14 = load i32, i32* %r, align 4, !dbg !3088
  %cmp6 = icmp ne i32 %14, 0, !dbg !3090
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !3091

if.then7:                                         ; preds = %if.then5
  %15 = load i32, i32* %r, align 4, !dbg !3092
  store i32 %15, i32* %retval, align 4, !dbg !3093
  br label %return, !dbg !3093

if.end8:                                          ; preds = %if.then5
  br label %if.end9, !dbg !3094

if.end9:                                          ; preds = %if.end8, %if.end
  %16 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3095
  %17 = load i64, i64* %offset.addr, align 8, !dbg !3096
  %18 = load i64, i64* %length.addr, align 8, !dbg !3097
  %call10 = call i32 @_sparse_list_add_block(%struct.pax* %16, i64 %17, i64 %18, i32 0), !dbg !3098
  store i32 %call10, i32* %retval, align 4, !dbg !3099
  br label %return, !dbg !3099

return:                                           ; preds = %if.end9, %if.then7
  %19 = load i32, i32* %retval, align 4, !dbg !3100
  ret i32 %19, !dbg !3100
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_pax_header_xattrs(%struct.archive_write* %a, %struct.pax* %pax, %struct.archive_entry* %entry1) #0 !dbg !267 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_write*, align 8
  %pax.addr = alloca %struct.pax*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %i = alloca i32, align 4
  %name = alloca i8*, align 8
  %value = alloca i8*, align 8
  %url_encoded_name = alloca i8*, align 8
  %encoded_name = alloca i8*, align 8
  %size = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive_write* %a, %struct.archive_write** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write** %a.addr, metadata !3101, metadata !293), !dbg !3102
  store %struct.pax* %pax, %struct.pax** %pax.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pax** %pax.addr, metadata !3103, metadata !293), !dbg !3104
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !3105, metadata !293), !dbg !3106
  call void @llvm.dbg.declare(metadata i32* %i, metadata !3107, metadata !293), !dbg !3108
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3109
  %call = call i32 @archive_entry_xattr_reset(%struct.archive_entry* %0), !dbg !3110
  store i32 %call, i32* %i, align 4, !dbg !3108
  br label %while.cond, !dbg !3111

while.cond:                                       ; preds = %if.end14, %entry
  %1 = load i32, i32* %i, align 4, !dbg !3112
  %dec = add nsw i32 %1, -1, !dbg !3112
  store i32 %dec, i32* %i, align 4, !dbg !3112
  %tobool = icmp ne i32 %1, 0, !dbg !3114
  br i1 %tobool, label %while.body, label %while.end, !dbg !3114

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata i8** %name, metadata !3115, metadata !293), !dbg !3117
  call void @llvm.dbg.declare(metadata i8** %value, metadata !3118, metadata !293), !dbg !3119
  call void @llvm.dbg.declare(metadata i8** %url_encoded_name, metadata !3120, metadata !293), !dbg !3121
  store i8* null, i8** %url_encoded_name, align 8, !dbg !3121
  call void @llvm.dbg.declare(metadata i8** %encoded_name, metadata !3122, metadata !293), !dbg !3123
  store i8* null, i8** %encoded_name, align 8, !dbg !3123
  call void @llvm.dbg.declare(metadata i64* %size, metadata !3124, metadata !293), !dbg !3125
  call void @llvm.dbg.declare(metadata i32* %r, metadata !3126, metadata !293), !dbg !3127
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !3128
  %call2 = call i32 @archive_entry_xattr_next(%struct.archive_entry* %2, i8** %name, i8** %value, i64* %size), !dbg !3129
  %3 = load i8*, i8** %name, align 8, !dbg !3130
  %call3 = call i8* @url_encode(i8* %3), !dbg !3131
  store i8* %call3, i8** %url_encoded_name, align 8, !dbg !3132
  %4 = load i8*, i8** %url_encoded_name, align 8, !dbg !3133
  %cmp = icmp ne i8* %4, null, !dbg !3135
  br i1 %cmp, label %if.then, label %if.end14, !dbg !3136

if.then:                                          ; preds = %while.body
  %5 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3137
  %l_url_encoded_name = getelementptr inbounds %struct.pax, %struct.pax* %5, i32 0, i32 2, !dbg !3137
  %6 = load i8*, i8** %url_encoded_name, align 8, !dbg !3137
  %7 = load i8*, i8** %url_encoded_name, align 8, !dbg !3137
  %cmp4 = icmp eq i8* %7, null, !dbg !3137
  br i1 %cmp4, label %cond.true, label %cond.false, !dbg !3137

cond.true:                                        ; preds = %if.then
  br label %cond.end, !dbg !3139

cond.false:                                       ; preds = %if.then
  %8 = load i8*, i8** %url_encoded_name, align 8, !dbg !3141
  %call5 = call i64 @strlen(i8* %8) #8, !dbg !3141
  br label %cond.end, !dbg !3141

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ 0, %cond.true ], [ %call5, %cond.false ], !dbg !3143
  %9 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3143
  %sconv_utf8 = getelementptr inbounds %struct.pax, %struct.pax* %9, i32 0, i32 8, !dbg !3143
  %10 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_utf8, align 8, !dbg !3143
  %call6 = call i32 @archive_strncpy_l(%struct.archive_string* %l_url_encoded_name, i8* %6, i64 %cond, %struct.archive_string_conv* %10), !dbg !3143
  store i32 %call6, i32* %r, align 4, !dbg !3145
  %11 = load i8*, i8** %url_encoded_name, align 8, !dbg !3146
  call void @free(i8* %11) #7, !dbg !3147
  %12 = load i32, i32* %r, align 4, !dbg !3148
  %cmp7 = icmp eq i32 %12, 0, !dbg !3150
  br i1 %cmp7, label %if.then8, label %if.else, !dbg !3151

if.then8:                                         ; preds = %cond.end
  %13 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3152
  %l_url_encoded_name9 = getelementptr inbounds %struct.pax, %struct.pax* %13, i32 0, i32 2, !dbg !3153
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %l_url_encoded_name9, i32 0, i32 0, !dbg !3154
  %14 = load i8*, i8** %s, align 8, !dbg !3154
  store i8* %14, i8** %encoded_name, align 8, !dbg !3155
  br label %if.end13, !dbg !3156

if.else:                                          ; preds = %cond.end
  %call10 = call i32* @__errno_location() #1, !dbg !3157
  %15 = load i32, i32* %call10, align 4, !dbg !3157
  %cmp11 = icmp eq i32 %15, 12, !dbg !3159
  br i1 %cmp11, label %if.then12, label %if.end, !dbg !3160

if.then12:                                        ; preds = %if.else
  %16 = load %struct.archive_write*, %struct.archive_write** %a.addr, align 8, !dbg !3161
  %archive = getelementptr inbounds %struct.archive_write, %struct.archive_write* %16, i32 0, i32 0, !dbg !3163
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.44, i32 0, i32 0)), !dbg !3164
  store i32 -30, i32* %retval, align 4, !dbg !3165
  br label %return, !dbg !3165

if.end:                                           ; preds = %if.else
  br label %if.end13

if.end13:                                         ; preds = %if.end, %if.then8
  br label %if.end14, !dbg !3166

if.end14:                                         ; preds = %if.end13, %while.body
  %17 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3167
  %18 = load i8*, i8** %encoded_name, align 8, !dbg !3168
  %19 = load i8*, i8** %value, align 8, !dbg !3169
  %20 = load i64, i64* %size, align 8, !dbg !3170
  call void @archive_write_pax_header_xattr(%struct.pax* %17, i8* %18, i8* %19, i64 %20), !dbg !3171
  br label %while.cond, !dbg !3172

while.end:                                        ; preds = %while.cond
  store i32 0, i32* %retval, align 4, !dbg !3174
  br label %return, !dbg !3174

return:                                           ; preds = %while.end, %if.then12
  %21 = load i32, i32* %retval, align 4, !dbg !3175
  ret i32 %21, !dbg !3175
}

declare i32 @__archive_write_format_header_ustar(%struct.archive_write*, i8*, %struct.archive_entry*, i32, i32, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define internal i8* @build_pax_attribute_name(i8* %dest, i8* %src) #0 !dbg !279 {
entry:
  %retval = alloca i8*, align 8
  %dest.addr = alloca i8*, align 8
  %src.addr = alloca i8*, align 8
  %buff = alloca [64 x i8], align 16
  %p = alloca i8*, align 8
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !3176, metadata !293), !dbg !3177
  store i8* %src, i8** %src.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %src.addr, metadata !3178, metadata !293), !dbg !3179
  call void @llvm.dbg.declare(metadata [64 x i8]* %buff, metadata !3180, metadata !293), !dbg !3181
  call void @llvm.dbg.declare(metadata i8** %p, metadata !3182, metadata !293), !dbg !3183
  %0 = load i8*, i8** %src.addr, align 8, !dbg !3184
  %cmp = icmp eq i8* %0, null, !dbg !3186
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3187

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %src.addr, align 8, !dbg !3188
  %2 = load i8, i8* %1, align 1, !dbg !3190
  %conv = sext i8 %2 to i32, !dbg !3190
  %cmp1 = icmp eq i32 %conv, 0, !dbg !3191
  br i1 %cmp1, label %if.then, label %if.end, !dbg !3192

if.then:                                          ; preds = %lor.lhs.false, %entry
  %3 = load i8*, i8** %dest.addr, align 8, !dbg !3193
  %call = call i8* @strcpy(i8* %3, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.62, i32 0, i32 0)) #7, !dbg !3195
  %4 = load i8*, i8** %dest.addr, align 8, !dbg !3196
  store i8* %4, i8** %retval, align 8, !dbg !3197
  br label %return, !dbg !3197

if.end:                                           ; preds = %lor.lhs.false
  %5 = load i8*, i8** %src.addr, align 8, !dbg !3198
  %6 = load i8*, i8** %src.addr, align 8, !dbg !3199
  %call3 = call i64 @strlen(i8* %6) #8, !dbg !3200
  %add.ptr = getelementptr inbounds i8, i8* %5, i64 %call3, !dbg !3201
  store i8* %add.ptr, i8** %p, align 8, !dbg !3202
  br label %for.cond, !dbg !3203

for.cond:                                         ; preds = %if.then24, %if.then9, %if.end
  %7 = load i8*, i8** %p, align 8, !dbg !3204
  %8 = load i8*, i8** %src.addr, align 8, !dbg !3209
  %cmp4 = icmp ugt i8* %7, %8, !dbg !3210
  br i1 %cmp4, label %land.lhs.true, label %if.end10, !dbg !3211

land.lhs.true:                                    ; preds = %for.cond
  %9 = load i8*, i8** %p, align 8, !dbg !3212
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 -1, !dbg !3212
  %10 = load i8, i8* %arrayidx, align 1, !dbg !3212
  %conv6 = sext i8 %10 to i32, !dbg !3212
  %cmp7 = icmp eq i32 %conv6, 47, !dbg !3214
  br i1 %cmp7, label %if.then9, label %if.end10, !dbg !3215

if.then9:                                         ; preds = %land.lhs.true
  %11 = load i8*, i8** %p, align 8, !dbg !3216
  %incdec.ptr = getelementptr inbounds i8, i8* %11, i32 -1, !dbg !3216
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !3216
  br label %for.cond, !dbg !3218

if.end10:                                         ; preds = %land.lhs.true, %for.cond
  %12 = load i8*, i8** %p, align 8, !dbg !3219
  %13 = load i8*, i8** %src.addr, align 8, !dbg !3221
  %add.ptr11 = getelementptr inbounds i8, i8* %13, i64 1, !dbg !3222
  %cmp12 = icmp ugt i8* %12, %add.ptr11, !dbg !3223
  br i1 %cmp12, label %land.lhs.true14, label %if.end26, !dbg !3224

land.lhs.true14:                                  ; preds = %if.end10
  %14 = load i8*, i8** %p, align 8, !dbg !3225
  %arrayidx15 = getelementptr inbounds i8, i8* %14, i64 -1, !dbg !3225
  %15 = load i8, i8* %arrayidx15, align 1, !dbg !3225
  %conv16 = sext i8 %15 to i32, !dbg !3225
  %cmp17 = icmp eq i32 %conv16, 46, !dbg !3227
  br i1 %cmp17, label %land.lhs.true19, label %if.end26, !dbg !3228

land.lhs.true19:                                  ; preds = %land.lhs.true14
  %16 = load i8*, i8** %p, align 8, !dbg !3229
  %arrayidx20 = getelementptr inbounds i8, i8* %16, i64 -2, !dbg !3229
  %17 = load i8, i8* %arrayidx20, align 1, !dbg !3229
  %conv21 = sext i8 %17 to i32, !dbg !3229
  %cmp22 = icmp eq i32 %conv21, 47, !dbg !3230
  br i1 %cmp22, label %if.then24, label %if.end26, !dbg !3231

if.then24:                                        ; preds = %land.lhs.true19
  %18 = load i8*, i8** %p, align 8, !dbg !3233
  %incdec.ptr25 = getelementptr inbounds i8, i8* %18, i32 -1, !dbg !3233
  store i8* %incdec.ptr25, i8** %p, align 8, !dbg !3233
  br label %for.cond, !dbg !3235

if.end26:                                         ; preds = %land.lhs.true19, %land.lhs.true14, %if.end10
  br label %for.end, !dbg !3236

for.end:                                          ; preds = %if.end26
  %19 = load i8*, i8** %p, align 8, !dbg !3237
  %20 = load i8*, i8** %src.addr, align 8, !dbg !3239
  %cmp27 = icmp eq i8* %19, %20, !dbg !3240
  br i1 %cmp27, label %if.then29, label %if.end31, !dbg !3241

if.then29:                                        ; preds = %for.end
  %21 = load i8*, i8** %dest.addr, align 8, !dbg !3242
  %call30 = call i8* @strcpy(i8* %21, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.63, i32 0, i32 0)) #7, !dbg !3244
  %22 = load i8*, i8** %dest.addr, align 8, !dbg !3245
  store i8* %22, i8** %retval, align 8, !dbg !3246
  br label %return, !dbg !3246

if.end31:                                         ; preds = %for.end
  %23 = load i8*, i8** %src.addr, align 8, !dbg !3247
  %24 = load i8, i8* %23, align 1, !dbg !3249
  %conv32 = sext i8 %24 to i32, !dbg !3249
  %cmp33 = icmp eq i32 %conv32, 46, !dbg !3250
  br i1 %cmp33, label %land.lhs.true35, label %if.end41, !dbg !3251

land.lhs.true35:                                  ; preds = %if.end31
  %25 = load i8*, i8** %p, align 8, !dbg !3252
  %26 = load i8*, i8** %src.addr, align 8, !dbg !3254
  %add.ptr36 = getelementptr inbounds i8, i8* %26, i64 1, !dbg !3255
  %cmp37 = icmp eq i8* %25, %add.ptr36, !dbg !3256
  br i1 %cmp37, label %if.then39, label %if.end41, !dbg !3257

if.then39:                                        ; preds = %land.lhs.true35
  %27 = load i8*, i8** %dest.addr, align 8, !dbg !3258
  %call40 = call i8* @strcpy(i8* %27, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.64, i32 0, i32 0)) #7, !dbg !3260
  %28 = load i8*, i8** %dest.addr, align 8, !dbg !3261
  store i8* %28, i8** %retval, align 8, !dbg !3262
  br label %return, !dbg !3262

if.end41:                                         ; preds = %land.lhs.true35, %if.end31
  %arraydecay = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3263
  %call42 = call i8* @strcpy(i8* %arraydecay, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.65, i32 0, i32 0)) #7, !dbg !3264
  %29 = load i8*, i8** %dest.addr, align 8, !dbg !3265
  %30 = load i8*, i8** %src.addr, align 8, !dbg !3266
  %31 = load i8*, i8** %p, align 8, !dbg !3267
  %32 = load i8*, i8** %src.addr, align 8, !dbg !3268
  %sub.ptr.lhs.cast = ptrtoint i8* %31 to i64, !dbg !3269
  %sub.ptr.rhs.cast = ptrtoint i8* %32 to i64, !dbg !3269
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !3269
  %arraydecay43 = getelementptr inbounds [64 x i8], [64 x i8]* %buff, i32 0, i32 0, !dbg !3270
  %call44 = call i8* @build_ustar_entry_name(i8* %29, i8* %30, i64 %sub.ptr.sub, i8* %arraydecay43), !dbg !3271
  %33 = load i8*, i8** %dest.addr, align 8, !dbg !3272
  store i8* %33, i8** %retval, align 8, !dbg !3273
  br label %return, !dbg !3273

return:                                           ; preds = %if.end41, %if.then39, %if.then29, %if.then
  %34 = load i8*, i8** %retval, align 8, !dbg !3274
  ret i8* %34, !dbg !3274
}

declare i32 @archive_entry_mode(%struct.archive_entry*) #2

declare void @archive_entry_set_mode(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_atime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_ctime(%struct.archive_entry*, i64, i64) #2

declare i32 @__archive_write_output(%struct.archive_write*, i8*, i64) #2

declare i32 @__archive_write_nulls(%struct.archive_write*, i64) #2

declare i32 @_archive_entry_hardlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #6

declare i32 @_archive_entry_pathname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

declare i32 @_archive_entry_uname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

declare i32 @_archive_entry_gname_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

declare i32 @_archive_entry_symlink_l(%struct.archive_entry*, i8**, i64*, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define internal void @add_pax_attr_binary(%struct.archive_string* %as, i8* %key, i8* %value, i64 %value_len) #0 !dbg !237 {
entry:
  %as.addr = alloca %struct.archive_string*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %value_len.addr = alloca i64, align 8
  %digits = alloca i32, align 4
  %i = alloca i32, align 4
  %len = alloca i32, align 4
  %next_ten = alloca i32, align 4
  %tmp = alloca [13 x i8], align 1
  store %struct.archive_string* %as, %struct.archive_string** %as.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_string** %as.addr, metadata !3275, metadata !293), !dbg !3276
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !3277, metadata !293), !dbg !3278
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !3279, metadata !293), !dbg !3280
  store i64 %value_len, i64* %value_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %value_len.addr, metadata !3281, metadata !293), !dbg !3282
  call void @llvm.dbg.declare(metadata i32* %digits, metadata !3283, metadata !293), !dbg !3284
  call void @llvm.dbg.declare(metadata i32* %i, metadata !3285, metadata !293), !dbg !3286
  call void @llvm.dbg.declare(metadata i32* %len, metadata !3287, metadata !293), !dbg !3288
  call void @llvm.dbg.declare(metadata i32* %next_ten, metadata !3289, metadata !293), !dbg !3290
  call void @llvm.dbg.declare(metadata [13 x i8]* %tmp, metadata !3291, metadata !293), !dbg !3295
  %0 = load i8*, i8** %key.addr, align 8, !dbg !3296
  %call = call i64 @strlen(i8* %0) #8, !dbg !3297
  %conv = trunc i64 %call to i32, !dbg !3298
  %add = add nsw i32 1, %conv, !dbg !3299
  %add1 = add nsw i32 %add, 1, !dbg !3300
  %1 = load i64, i64* %value_len.addr, align 8, !dbg !3301
  %conv2 = trunc i64 %1 to i32, !dbg !3302
  %add3 = add nsw i32 %add1, %conv2, !dbg !3303
  %add4 = add nsw i32 %add3, 1, !dbg !3304
  store i32 %add4, i32* %len, align 4, !dbg !3305
  store i32 1, i32* %next_ten, align 4, !dbg !3306
  store i32 0, i32* %digits, align 4, !dbg !3307
  %2 = load i32, i32* %len, align 4, !dbg !3308
  store i32 %2, i32* %i, align 4, !dbg !3309
  br label %while.cond, !dbg !3310

while.cond:                                       ; preds = %while.body, %entry
  %3 = load i32, i32* %i, align 4, !dbg !3311
  %cmp = icmp sgt i32 %3, 0, !dbg !3313
  br i1 %cmp, label %while.body, label %while.end, !dbg !3314

while.body:                                       ; preds = %while.cond
  %4 = load i32, i32* %i, align 4, !dbg !3315
  %div = sdiv i32 %4, 10, !dbg !3317
  store i32 %div, i32* %i, align 4, !dbg !3318
  %5 = load i32, i32* %digits, align 4, !dbg !3319
  %inc = add nsw i32 %5, 1, !dbg !3319
  store i32 %inc, i32* %digits, align 4, !dbg !3319
  %6 = load i32, i32* %next_ten, align 4, !dbg !3320
  %mul = mul nsw i32 %6, 10, !dbg !3321
  store i32 %mul, i32* %next_ten, align 4, !dbg !3322
  br label %while.cond, !dbg !3323

while.end:                                        ; preds = %while.cond
  %7 = load i32, i32* %len, align 4, !dbg !3325
  %8 = load i32, i32* %digits, align 4, !dbg !3327
  %add6 = add nsw i32 %7, %8, !dbg !3328
  %9 = load i32, i32* %next_ten, align 4, !dbg !3329
  %cmp7 = icmp sge i32 %add6, %9, !dbg !3330
  br i1 %cmp7, label %if.then, label %if.end, !dbg !3331

if.then:                                          ; preds = %while.end
  %10 = load i32, i32* %digits, align 4, !dbg !3332
  %inc9 = add nsw i32 %10, 1, !dbg !3332
  store i32 %inc9, i32* %digits, align 4, !dbg !3332
  br label %if.end, !dbg !3333

if.end:                                           ; preds = %if.then, %while.end
  %arrayidx = getelementptr inbounds [13 x i8], [13 x i8]* %tmp, i64 0, i64 12, !dbg !3334
  store i8 0, i8* %arrayidx, align 1, !dbg !3335
  %11 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !3336
  %arraydecay = getelementptr inbounds [13 x i8], [13 x i8]* %tmp, i32 0, i32 0, !dbg !3337
  %add.ptr = getelementptr inbounds i8, i8* %arraydecay, i64 13, !dbg !3338
  %add.ptr10 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !3339
  %12 = load i32, i32* %len, align 4, !dbg !3340
  %13 = load i32, i32* %digits, align 4, !dbg !3341
  %add11 = add nsw i32 %12, %13, !dbg !3342
  %conv12 = sext i32 %add11 to i64, !dbg !3340
  %call13 = call i8* @format_int(i8* %add.ptr10, i64 %conv12), !dbg !3343
  %call14 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %11, i8* %call13), !dbg !3344
  %14 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !3345
  %call15 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %14, i8 signext 32), !dbg !3346
  %15 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !3347
  %16 = load i8*, i8** %key.addr, align 8, !dbg !3348
  %call16 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %15, i8* %16), !dbg !3349
  %17 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !3350
  %call17 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %17, i8 signext 61), !dbg !3351
  %18 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !3352
  %19 = load i8*, i8** %value.addr, align 8, !dbg !3353
  %20 = load i64, i64* %value_len.addr, align 8, !dbg !3354
  %call18 = call %struct.archive_string* @archive_array_append(%struct.archive_string* %18, i8* %19, i64 %20), !dbg !3355
  %21 = load %struct.archive_string*, %struct.archive_string** %as.addr, align 8, !dbg !3356
  %call19 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %21, i8 signext 10), !dbg !3357
  ret void, !dbg !3358
}

declare %struct.archive_string* @archive_strcat(%struct.archive_string*, i8*) #2

; Function Attrs: nounwind uwtable
define internal i8* @format_int(i8* %t, i64 %i) #0 !dbg !240 {
entry:
  %t.addr = alloca i8*, align 8
  %i.addr = alloca i64, align 8
  %ui = alloca i64, align 8
  store i8* %t, i8** %t.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %t.addr, metadata !3359, metadata !293), !dbg !3360
  store i64 %i, i64* %i.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %i.addr, metadata !3361, metadata !293), !dbg !3362
  call void @llvm.dbg.declare(metadata i64* %ui, metadata !3363, metadata !293), !dbg !3364
  %0 = load i64, i64* %i.addr, align 8, !dbg !3365
  %cmp = icmp slt i64 %0, 0, !dbg !3367
  br i1 %cmp, label %if.then, label %if.else, !dbg !3368

if.then:                                          ; preds = %entry
  %1 = load i64, i64* %i.addr, align 8, !dbg !3369
  %cmp1 = icmp eq i64 %1, -9223372036854775808, !dbg !3370
  br i1 %cmp1, label %cond.true, label %cond.false, !dbg !3371

cond.true:                                        ; preds = %if.then
  br label %cond.end, !dbg !3372

cond.false:                                       ; preds = %if.then
  %2 = load i64, i64* %i.addr, align 8, !dbg !3374
  %sub = sub nsw i64 0, %2, !dbg !3376
  br label %cond.end, !dbg !3377

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i64 [ -9223372036854775808, %cond.true ], [ %sub, %cond.false ], !dbg !3378
  store i64 %cond, i64* %ui, align 8, !dbg !3380
  br label %if.end, !dbg !3381

if.else:                                          ; preds = %entry
  %3 = load i64, i64* %i.addr, align 8, !dbg !3382
  store i64 %3, i64* %ui, align 8, !dbg !3383
  br label %if.end

if.end:                                           ; preds = %if.else, %cond.end
  br label %do.body, !dbg !3384

do.body:                                          ; preds = %do.cond, %if.end
  %4 = load i64, i64* %ui, align 8, !dbg !3385
  %rem = urem i64 %4, 10, !dbg !3387
  %arrayidx = getelementptr inbounds [11 x i8], [11 x i8]* @.str.48, i64 0, i64 %rem, !dbg !3388
  %5 = load i8, i8* %arrayidx, align 1, !dbg !3388
  %6 = load i8*, i8** %t.addr, align 8, !dbg !3389
  %incdec.ptr = getelementptr inbounds i8, i8* %6, i32 -1, !dbg !3389
  store i8* %incdec.ptr, i8** %t.addr, align 8, !dbg !3389
  store i8 %5, i8* %incdec.ptr, align 1, !dbg !3390
  br label %do.cond, !dbg !3391

do.cond:                                          ; preds = %do.body
  %7 = load i64, i64* %ui, align 8, !dbg !3392
  %div = udiv i64 %7, 10, !dbg !3392
  store i64 %div, i64* %ui, align 8, !dbg !3392
  %tobool = icmp ne i64 %div, 0, !dbg !3394
  br i1 %tobool, label %do.body, label %do.end, !dbg !3394

do.end:                                           ; preds = %do.cond
  %8 = load i64, i64* %i.addr, align 8, !dbg !3395
  %cmp2 = icmp slt i64 %8, 0, !dbg !3397
  br i1 %cmp2, label %if.then3, label %if.end5, !dbg !3398

if.then3:                                         ; preds = %do.end
  %9 = load i8*, i8** %t.addr, align 8, !dbg !3399
  %incdec.ptr4 = getelementptr inbounds i8, i8* %9, i32 -1, !dbg !3399
  store i8* %incdec.ptr4, i8** %t.addr, align 8, !dbg !3399
  store i8 45, i8* %incdec.ptr4, align 1, !dbg !3400
  br label %if.end5, !dbg !3401

if.end5:                                          ; preds = %if.then3, %do.end
  %10 = load i8*, i8** %t.addr, align 8, !dbg !3402
  ret i8* %10, !dbg !3403
}

declare %struct.archive_string* @archive_array_append(%struct.archive_string*, i8*, i64) #2

; Function Attrs: nounwind
declare i8* @strncpy(i8*, i8*, i64) #3

declare i8* @_archive_entry_acl_to_text_l(%struct.archive_entry*, i64*, i32, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define internal i32 @_sparse_list_add_block(%struct.pax* %pax, i64 %offset, i64 %length, i32 %is_hole) #0 !dbg !264 {
entry:
  %retval = alloca i32, align 4
  %pax.addr = alloca %struct.pax*, align 8
  %offset.addr = alloca i64, align 8
  %length.addr = alloca i64, align 8
  %is_hole.addr = alloca i32, align 4
  %sb = alloca %struct.sparse_block*, align 8
  store %struct.pax* %pax, %struct.pax** %pax.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pax** %pax.addr, metadata !3404, metadata !293), !dbg !3405
  store i64 %offset, i64* %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %offset.addr, metadata !3406, metadata !293), !dbg !3407
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !3408, metadata !293), !dbg !3409
  store i32 %is_hole, i32* %is_hole.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %is_hole.addr, metadata !3410, metadata !293), !dbg !3411
  call void @llvm.dbg.declare(metadata %struct.sparse_block** %sb, metadata !3412, metadata !293), !dbg !3413
  %call = call noalias i8* @malloc(i64 32) #7, !dbg !3414
  %0 = bitcast i8* %call to %struct.sparse_block*, !dbg !3415
  store %struct.sparse_block* %0, %struct.sparse_block** %sb, align 8, !dbg !3416
  %1 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !3417
  %cmp = icmp eq %struct.sparse_block* %1, null, !dbg !3419
  br i1 %cmp, label %if.then, label %if.end, !dbg !3420

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !3421
  br label %return, !dbg !3421

if.end:                                           ; preds = %entry
  %2 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !3422
  %next = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %2, i32 0, i32 0, !dbg !3423
  store %struct.sparse_block* null, %struct.sparse_block** %next, align 8, !dbg !3424
  %3 = load i32, i32* %is_hole.addr, align 4, !dbg !3425
  %4 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !3426
  %is_hole1 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %4, i32 0, i32 1, !dbg !3427
  store i32 %3, i32* %is_hole1, align 8, !dbg !3428
  %5 = load i64, i64* %offset.addr, align 8, !dbg !3429
  %6 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !3430
  %offset2 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %6, i32 0, i32 2, !dbg !3431
  store i64 %5, i64* %offset2, align 8, !dbg !3432
  %7 = load i64, i64* %length.addr, align 8, !dbg !3433
  %8 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !3434
  %remaining = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %8, i32 0, i32 3, !dbg !3435
  store i64 %7, i64* %remaining, align 8, !dbg !3436
  %9 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3437
  %sparse_list = getelementptr inbounds %struct.pax, %struct.pax* %9, i32 0, i32 6, !dbg !3439
  %10 = load %struct.sparse_block*, %struct.sparse_block** %sparse_list, align 8, !dbg !3439
  %cmp3 = icmp eq %struct.sparse_block* %10, null, !dbg !3440
  br i1 %cmp3, label %if.then5, label %lor.lhs.false, !dbg !3441

lor.lhs.false:                                    ; preds = %if.end
  %11 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3442
  %sparse_tail = getelementptr inbounds %struct.pax, %struct.pax* %11, i32 0, i32 7, !dbg !3444
  %12 = load %struct.sparse_block*, %struct.sparse_block** %sparse_tail, align 8, !dbg !3444
  %cmp4 = icmp eq %struct.sparse_block* %12, null, !dbg !3445
  br i1 %cmp4, label %if.then5, label %if.else, !dbg !3446

if.then5:                                         ; preds = %lor.lhs.false, %if.end
  %13 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !3447
  %14 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3448
  %sparse_tail6 = getelementptr inbounds %struct.pax, %struct.pax* %14, i32 0, i32 7, !dbg !3449
  store %struct.sparse_block* %13, %struct.sparse_block** %sparse_tail6, align 8, !dbg !3450
  %15 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3451
  %sparse_list7 = getelementptr inbounds %struct.pax, %struct.pax* %15, i32 0, i32 6, !dbg !3452
  store %struct.sparse_block* %13, %struct.sparse_block** %sparse_list7, align 8, !dbg !3453
  br label %if.end11, !dbg !3451

if.else:                                          ; preds = %lor.lhs.false
  %16 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !3454
  %17 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3456
  %sparse_tail8 = getelementptr inbounds %struct.pax, %struct.pax* %17, i32 0, i32 7, !dbg !3457
  %18 = load %struct.sparse_block*, %struct.sparse_block** %sparse_tail8, align 8, !dbg !3457
  %next9 = getelementptr inbounds %struct.sparse_block, %struct.sparse_block* %18, i32 0, i32 0, !dbg !3458
  store %struct.sparse_block* %16, %struct.sparse_block** %next9, align 8, !dbg !3459
  %19 = load %struct.sparse_block*, %struct.sparse_block** %sb, align 8, !dbg !3460
  %20 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3461
  %sparse_tail10 = getelementptr inbounds %struct.pax, %struct.pax* %20, i32 0, i32 7, !dbg !3462
  store %struct.sparse_block* %19, %struct.sparse_block** %sparse_tail10, align 8, !dbg !3463
  br label %if.end11

if.end11:                                         ; preds = %if.else, %if.then5
  store i32 0, i32* %retval, align 4, !dbg !3464
  br label %return, !dbg !3464

return:                                           ; preds = %if.end11, %if.then
  %21 = load i32, i32* %retval, align 4, !dbg !3465
  ret i32 %21, !dbg !3465
}

declare i32 @archive_entry_xattr_reset(%struct.archive_entry*) #2

declare i32 @archive_entry_xattr_next(%struct.archive_entry*, i8**, i8**, i64*) #2

; Function Attrs: nounwind uwtable
define internal i8* @url_encode(i8* %in) #0 !dbg !270 {
entry:
  %retval = alloca i8*, align 8
  %in.addr = alloca i8*, align 8
  %s = alloca i8*, align 8
  %d = alloca i8*, align 8
  %out_len = alloca i32, align 4
  %out = alloca i8*, align 8
  store i8* %in, i8** %in.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %in.addr, metadata !3466, metadata !293), !dbg !3467
  call void @llvm.dbg.declare(metadata i8** %s, metadata !3468, metadata !293), !dbg !3469
  call void @llvm.dbg.declare(metadata i8** %d, metadata !3470, metadata !293), !dbg !3471
  call void @llvm.dbg.declare(metadata i32* %out_len, metadata !3472, metadata !293), !dbg !3473
  store i32 0, i32* %out_len, align 4, !dbg !3473
  call void @llvm.dbg.declare(metadata i8** %out, metadata !3474, metadata !293), !dbg !3475
  %0 = load i8*, i8** %in.addr, align 8, !dbg !3476
  store i8* %0, i8** %s, align 8, !dbg !3478
  br label %for.cond, !dbg !3479

for.cond:                                         ; preds = %for.inc, %entry
  %1 = load i8*, i8** %s, align 8, !dbg !3480
  %2 = load i8, i8* %1, align 1, !dbg !3483
  %conv = sext i8 %2 to i32, !dbg !3483
  %cmp = icmp ne i32 %conv, 0, !dbg !3484
  br i1 %cmp, label %for.body, label %for.end, !dbg !3485

for.body:                                         ; preds = %for.cond
  %3 = load i8*, i8** %s, align 8, !dbg !3486
  %4 = load i8, i8* %3, align 1, !dbg !3489
  %conv2 = sext i8 %4 to i32, !dbg !3489
  %cmp3 = icmp slt i32 %conv2, 33, !dbg !3490
  br i1 %cmp3, label %if.then, label %lor.lhs.false, !dbg !3491

lor.lhs.false:                                    ; preds = %for.body
  %5 = load i8*, i8** %s, align 8, !dbg !3492
  %6 = load i8, i8* %5, align 1, !dbg !3494
  %conv5 = sext i8 %6 to i32, !dbg !3494
  %cmp6 = icmp sgt i32 %conv5, 126, !dbg !3495
  br i1 %cmp6, label %if.then, label %lor.lhs.false8, !dbg !3496

lor.lhs.false8:                                   ; preds = %lor.lhs.false
  %7 = load i8*, i8** %s, align 8, !dbg !3497
  %8 = load i8, i8* %7, align 1, !dbg !3499
  %conv9 = sext i8 %8 to i32, !dbg !3499
  %cmp10 = icmp eq i32 %conv9, 37, !dbg !3500
  br i1 %cmp10, label %if.then, label %lor.lhs.false12, !dbg !3501

lor.lhs.false12:                                  ; preds = %lor.lhs.false8
  %9 = load i8*, i8** %s, align 8, !dbg !3502
  %10 = load i8, i8* %9, align 1, !dbg !3504
  %conv13 = sext i8 %10 to i32, !dbg !3504
  %cmp14 = icmp eq i32 %conv13, 61, !dbg !3505
  br i1 %cmp14, label %if.then, label %if.else, !dbg !3506

if.then:                                          ; preds = %lor.lhs.false12, %lor.lhs.false8, %lor.lhs.false, %for.body
  %11 = load i32, i32* %out_len, align 4, !dbg !3507
  %add = add nsw i32 %11, 3, !dbg !3507
  store i32 %add, i32* %out_len, align 4, !dbg !3507
  br label %if.end, !dbg !3508

if.else:                                          ; preds = %lor.lhs.false12
  %12 = load i32, i32* %out_len, align 4, !dbg !3509
  %inc = add nsw i32 %12, 1, !dbg !3509
  store i32 %inc, i32* %out_len, align 4, !dbg !3509
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %for.inc, !dbg !3510

for.inc:                                          ; preds = %if.end
  %13 = load i8*, i8** %s, align 8, !dbg !3511
  %incdec.ptr = getelementptr inbounds i8, i8* %13, i32 1, !dbg !3511
  store i8* %incdec.ptr, i8** %s, align 8, !dbg !3511
  br label %for.cond, !dbg !3513

for.end:                                          ; preds = %for.cond
  %14 = load i32, i32* %out_len, align 4, !dbg !3514
  %add16 = add nsw i32 %14, 1, !dbg !3515
  %conv17 = sext i32 %add16 to i64, !dbg !3514
  %call = call noalias i8* @malloc(i64 %conv17) #7, !dbg !3516
  store i8* %call, i8** %out, align 8, !dbg !3517
  %15 = load i8*, i8** %out, align 8, !dbg !3518
  %cmp18 = icmp eq i8* %15, null, !dbg !3520
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !3521

if.then20:                                        ; preds = %for.end
  store i8* null, i8** %retval, align 8, !dbg !3522
  br label %return, !dbg !3522

if.end21:                                         ; preds = %for.end
  %16 = load i8*, i8** %in.addr, align 8, !dbg !3523
  store i8* %16, i8** %s, align 8, !dbg !3525
  %17 = load i8*, i8** %out, align 8, !dbg !3526
  store i8* %17, i8** %d, align 8, !dbg !3527
  br label %for.cond22, !dbg !3528

for.cond22:                                       ; preds = %for.inc54, %if.end21
  %18 = load i8*, i8** %s, align 8, !dbg !3529
  %19 = load i8, i8* %18, align 1, !dbg !3532
  %conv23 = sext i8 %19 to i32, !dbg !3532
  %cmp24 = icmp ne i32 %conv23, 0, !dbg !3533
  br i1 %cmp24, label %for.body26, label %for.end56, !dbg !3534

for.body26:                                       ; preds = %for.cond22
  %20 = load i8*, i8** %s, align 8, !dbg !3535
  %21 = load i8, i8* %20, align 1, !dbg !3538
  %conv27 = sext i8 %21 to i32, !dbg !3538
  %cmp28 = icmp slt i32 %conv27, 33, !dbg !3539
  br i1 %cmp28, label %if.then42, label %lor.lhs.false30, !dbg !3540

lor.lhs.false30:                                  ; preds = %for.body26
  %22 = load i8*, i8** %s, align 8, !dbg !3541
  %23 = load i8, i8* %22, align 1, !dbg !3543
  %conv31 = sext i8 %23 to i32, !dbg !3543
  %cmp32 = icmp sgt i32 %conv31, 126, !dbg !3544
  br i1 %cmp32, label %if.then42, label %lor.lhs.false34, !dbg !3545

lor.lhs.false34:                                  ; preds = %lor.lhs.false30
  %24 = load i8*, i8** %s, align 8, !dbg !3546
  %25 = load i8, i8* %24, align 1, !dbg !3548
  %conv35 = sext i8 %25 to i32, !dbg !3548
  %cmp36 = icmp eq i32 %conv35, 37, !dbg !3549
  br i1 %cmp36, label %if.then42, label %lor.lhs.false38, !dbg !3550

lor.lhs.false38:                                  ; preds = %lor.lhs.false34
  %26 = load i8*, i8** %s, align 8, !dbg !3551
  %27 = load i8, i8* %26, align 1, !dbg !3553
  %conv39 = sext i8 %27 to i32, !dbg !3553
  %cmp40 = icmp eq i32 %conv39, 61, !dbg !3554
  br i1 %cmp40, label %if.then42, label %if.else51, !dbg !3555

if.then42:                                        ; preds = %lor.lhs.false38, %lor.lhs.false34, %lor.lhs.false30, %for.body26
  %28 = load i8*, i8** %d, align 8, !dbg !3556
  %incdec.ptr43 = getelementptr inbounds i8, i8* %28, i32 1, !dbg !3556
  store i8* %incdec.ptr43, i8** %d, align 8, !dbg !3556
  store i8 37, i8* %28, align 1, !dbg !3558
  %29 = load i8*, i8** %s, align 8, !dbg !3559
  %30 = load i8, i8* %29, align 1, !dbg !3560
  %conv44 = sext i8 %30 to i32, !dbg !3560
  %shr = ashr i32 %conv44, 4, !dbg !3561
  %and = and i32 15, %shr, !dbg !3562
  %idxprom = sext i32 %and to i64, !dbg !3563
  %arrayidx = getelementptr inbounds [17 x i8], [17 x i8]* @.str.59, i64 0, i64 %idxprom, !dbg !3563
  %31 = load i8, i8* %arrayidx, align 1, !dbg !3563
  %32 = load i8*, i8** %d, align 8, !dbg !3564
  %incdec.ptr45 = getelementptr inbounds i8, i8* %32, i32 1, !dbg !3564
  store i8* %incdec.ptr45, i8** %d, align 8, !dbg !3564
  store i8 %31, i8* %32, align 1, !dbg !3565
  %33 = load i8*, i8** %s, align 8, !dbg !3566
  %34 = load i8, i8* %33, align 1, !dbg !3567
  %conv46 = sext i8 %34 to i32, !dbg !3567
  %and47 = and i32 15, %conv46, !dbg !3568
  %idxprom48 = sext i32 %and47 to i64, !dbg !3569
  %arrayidx49 = getelementptr inbounds [17 x i8], [17 x i8]* @.str.59, i64 0, i64 %idxprom48, !dbg !3569
  %35 = load i8, i8* %arrayidx49, align 1, !dbg !3569
  %36 = load i8*, i8** %d, align 8, !dbg !3570
  %incdec.ptr50 = getelementptr inbounds i8, i8* %36, i32 1, !dbg !3570
  store i8* %incdec.ptr50, i8** %d, align 8, !dbg !3570
  store i8 %35, i8* %36, align 1, !dbg !3571
  br label %if.end53, !dbg !3572

if.else51:                                        ; preds = %lor.lhs.false38
  %37 = load i8*, i8** %s, align 8, !dbg !3573
  %38 = load i8, i8* %37, align 1, !dbg !3575
  %39 = load i8*, i8** %d, align 8, !dbg !3576
  %incdec.ptr52 = getelementptr inbounds i8, i8* %39, i32 1, !dbg !3576
  store i8* %incdec.ptr52, i8** %d, align 8, !dbg !3576
  store i8 %38, i8* %39, align 1, !dbg !3577
  br label %if.end53

if.end53:                                         ; preds = %if.else51, %if.then42
  br label %for.inc54, !dbg !3578

for.inc54:                                        ; preds = %if.end53
  %40 = load i8*, i8** %s, align 8, !dbg !3579
  %incdec.ptr55 = getelementptr inbounds i8, i8* %40, i32 1, !dbg !3579
  store i8* %incdec.ptr55, i8** %s, align 8, !dbg !3579
  br label %for.cond22, !dbg !3581

for.end56:                                        ; preds = %for.cond22
  %41 = load i8*, i8** %d, align 8, !dbg !3582
  store i8 0, i8* %41, align 1, !dbg !3583
  %42 = load i8*, i8** %out, align 8, !dbg !3584
  store i8* %42, i8** %retval, align 8, !dbg !3585
  br label %return, !dbg !3585

return:                                           ; preds = %for.end56, %if.then20
  %43 = load i8*, i8** %retval, align 8, !dbg !3586
  ret i8* %43, !dbg !3586
}

declare i32 @archive_strncpy_l(%struct.archive_string*, i8*, i64, %struct.archive_string_conv*) #2

; Function Attrs: nounwind uwtable
define internal void @archive_write_pax_header_xattr(%struct.pax* %pax, i8* %encoded_name, i8* %value, i64 %value_len) #0 !dbg !273 {
entry:
  %pax.addr = alloca %struct.pax*, align 8
  %encoded_name.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %value_len.addr = alloca i64, align 8
  %s = alloca %struct.archive_string, align 8
  %encoded_value = alloca i8*, align 8
  store %struct.pax* %pax, %struct.pax** %pax.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.pax** %pax.addr, metadata !3587, metadata !293), !dbg !3588
  store i8* %encoded_name, i8** %encoded_name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %encoded_name.addr, metadata !3589, metadata !293), !dbg !3590
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !3591, metadata !293), !dbg !3592
  store i64 %value_len, i64* %value_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %value_len.addr, metadata !3593, metadata !293), !dbg !3594
  call void @llvm.dbg.declare(metadata %struct.archive_string* %s, metadata !3595, metadata !293), !dbg !3596
  call void @llvm.dbg.declare(metadata i8** %encoded_value, metadata !3597, metadata !293), !dbg !3598
  %0 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3599
  %flags = getelementptr inbounds %struct.pax, %struct.pax* %0, i32 0, i32 10, !dbg !3601
  %1 = load i32, i32* %flags, align 4, !dbg !3601
  %and = and i32 %1, 2, !dbg !3602
  %tobool = icmp ne i32 %and, 0, !dbg !3602
  br i1 %tobool, label %if.then, label %if.end8, !dbg !3603

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %value.addr, align 8, !dbg !3604
  %3 = load i64, i64* %value_len.addr, align 8, !dbg !3606
  %call = call i8* @base64_encode(i8* %2, i64 %3), !dbg !3607
  store i8* %call, i8** %encoded_value, align 8, !dbg !3608
  %4 = load i8*, i8** %encoded_name.addr, align 8, !dbg !3609
  %cmp = icmp ne i8* %4, null, !dbg !3611
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !3612

land.lhs.true:                                    ; preds = %if.then
  %5 = load i8*, i8** %encoded_value, align 8, !dbg !3613
  %cmp1 = icmp ne i8* %5, null, !dbg !3615
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !3616

if.then2:                                         ; preds = %land.lhs.true
  br label %do.body, !dbg !3617

do.body:                                          ; preds = %if.then2
  %s3 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %s, i32 0, i32 0, !dbg !3619
  store i8* null, i8** %s3, align 8, !dbg !3619
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %s, i32 0, i32 1, !dbg !3619
  store i64 0, i64* %length, align 8, !dbg !3619
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %s, i32 0, i32 2, !dbg !3619
  store i64 0, i64* %buffer_length, align 8, !dbg !3619
  br label %do.end, !dbg !3619

do.end:                                           ; preds = %do.body
  %length4 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %s, i32 0, i32 1, !dbg !3622
  store i64 0, i64* %length4, align 8, !dbg !3622
  %call5 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %s, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.60, i32 0, i32 0), i64 17), !dbg !3622
  %6 = load i8*, i8** %encoded_name.addr, align 8, !dbg !3623
  %call6 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %s, i8* %6), !dbg !3624
  %7 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3625
  %pax_header = getelementptr inbounds %struct.pax, %struct.pax* %7, i32 0, i32 3, !dbg !3626
  %s7 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %s, i32 0, i32 0, !dbg !3627
  %8 = load i8*, i8** %s7, align 8, !dbg !3627
  %9 = load i8*, i8** %encoded_value, align 8, !dbg !3628
  call void @add_pax_attr(%struct.archive_string* %pax_header, i8* %8, i8* %9), !dbg !3629
  call void @archive_string_free(%struct.archive_string* %s), !dbg !3630
  br label %if.end, !dbg !3631

if.end:                                           ; preds = %do.end, %land.lhs.true, %if.then
  %10 = load i8*, i8** %encoded_value, align 8, !dbg !3632
  call void @free(i8* %10) #7, !dbg !3633
  br label %if.end8, !dbg !3634

if.end8:                                          ; preds = %if.end, %entry
  %11 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3635
  %flags9 = getelementptr inbounds %struct.pax, %struct.pax* %11, i32 0, i32 10, !dbg !3637
  %12 = load i32, i32* %flags9, align 4, !dbg !3637
  %and10 = and i32 %12, 1, !dbg !3638
  %tobool11 = icmp ne i32 %and10, 0, !dbg !3638
  br i1 %tobool11, label %if.then12, label %if.end23, !dbg !3639

if.then12:                                        ; preds = %if.end8
  br label %do.body13, !dbg !3640

do.body13:                                        ; preds = %if.then12
  %s14 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %s, i32 0, i32 0, !dbg !3642
  store i8* null, i8** %s14, align 8, !dbg !3642
  %length15 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %s, i32 0, i32 1, !dbg !3642
  store i64 0, i64* %length15, align 8, !dbg !3642
  %buffer_length16 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %s, i32 0, i32 2, !dbg !3642
  store i64 0, i64* %buffer_length16, align 8, !dbg !3642
  br label %do.end17, !dbg !3642

do.end17:                                         ; preds = %do.body13
  %length18 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %s, i32 0, i32 1, !dbg !3645
  store i64 0, i64* %length18, align 8, !dbg !3645
  %call19 = call %struct.archive_string* @archive_strncat(%struct.archive_string* %s, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.61, i32 0, i32 0), i64 13), !dbg !3645
  %13 = load i8*, i8** %encoded_name.addr, align 8, !dbg !3646
  %call20 = call %struct.archive_string* @archive_strcat(%struct.archive_string* %s, i8* %13), !dbg !3647
  %14 = load %struct.pax*, %struct.pax** %pax.addr, align 8, !dbg !3648
  %pax_header21 = getelementptr inbounds %struct.pax, %struct.pax* %14, i32 0, i32 3, !dbg !3649
  %s22 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %s, i32 0, i32 0, !dbg !3650
  %15 = load i8*, i8** %s22, align 8, !dbg !3650
  %16 = load i8*, i8** %value.addr, align 8, !dbg !3651
  %17 = load i64, i64* %value_len.addr, align 8, !dbg !3652
  call void @add_pax_attr_binary(%struct.archive_string* %pax_header21, i8* %15, i8* %16, i64 %17), !dbg !3653
  call void @archive_string_free(%struct.archive_string* %s), !dbg !3654
  br label %if.end23, !dbg !3655

if.end23:                                         ; preds = %do.end17, %if.end8
  ret void, !dbg !3656
}

; Function Attrs: nounwind uwtable
define internal i8* @base64_encode(i8* %s, i64 %len) #0 !dbg !276 {
entry:
  %retval = alloca i8*, align 8
  %s.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  %v = alloca i32, align 4
  %d = alloca i8*, align 8
  %out = alloca i8*, align 8
  store i8* %s, i8** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %s.addr, metadata !3657, metadata !293), !dbg !3658
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !3659, metadata !293), !dbg !3660
  call void @llvm.dbg.declare(metadata i32* %v, metadata !3661, metadata !293), !dbg !3662
  call void @llvm.dbg.declare(metadata i8** %d, metadata !3663, metadata !293), !dbg !3664
  call void @llvm.dbg.declare(metadata i8** %out, metadata !3665, metadata !293), !dbg !3666
  %0 = load i64, i64* %len.addr, align 8, !dbg !3667
  %mul = mul i64 %0, 4, !dbg !3668
  %add = add i64 %mul, 2, !dbg !3669
  %div = udiv i64 %add, 3, !dbg !3670
  %add1 = add i64 %div, 1, !dbg !3671
  %call = call noalias i8* @malloc(i64 %add1) #7, !dbg !3672
  store i8* %call, i8** %out, align 8, !dbg !3673
  %1 = load i8*, i8** %out, align 8, !dbg !3674
  %cmp = icmp eq i8* %1, null, !dbg !3676
  br i1 %cmp, label %if.then, label %if.end, !dbg !3677

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !3678
  br label %return, !dbg !3678

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %out, align 8, !dbg !3679
  store i8* %2, i8** %d, align 8, !dbg !3680
  br label %while.cond, !dbg !3681

while.cond:                                       ; preds = %while.body, %if.end
  %3 = load i64, i64* %len.addr, align 8, !dbg !3682
  %cmp2 = icmp uge i64 %3, 3, !dbg !3684
  br i1 %cmp2, label %while.body, label %while.end, !dbg !3685

while.body:                                       ; preds = %while.cond
  %4 = load i8*, i8** %s.addr, align 8, !dbg !3686
  %arrayidx = getelementptr inbounds i8, i8* %4, i64 0, !dbg !3686
  %5 = load i8, i8* %arrayidx, align 1, !dbg !3686
  %conv = sext i8 %5 to i32, !dbg !3688
  %shl = shl i32 %conv, 16, !dbg !3689
  %and = and i32 %shl, 16711680, !dbg !3690
  %6 = load i8*, i8** %s.addr, align 8, !dbg !3691
  %arrayidx3 = getelementptr inbounds i8, i8* %6, i64 1, !dbg !3691
  %7 = load i8, i8* %arrayidx3, align 1, !dbg !3691
  %conv4 = sext i8 %7 to i32, !dbg !3692
  %shl5 = shl i32 %conv4, 8, !dbg !3693
  %and6 = and i32 %shl5, 65280, !dbg !3694
  %or = or i32 %and, %and6, !dbg !3695
  %8 = load i8*, i8** %s.addr, align 8, !dbg !3696
  %arrayidx7 = getelementptr inbounds i8, i8* %8, i64 2, !dbg !3696
  %9 = load i8, i8* %arrayidx7, align 1, !dbg !3696
  %conv8 = sext i8 %9 to i32, !dbg !3697
  %and9 = and i32 %conv8, 255, !dbg !3698
  %or10 = or i32 %or, %and9, !dbg !3699
  store i32 %or10, i32* %v, align 4, !dbg !3700
  %10 = load i8*, i8** %s.addr, align 8, !dbg !3701
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 3, !dbg !3701
  store i8* %add.ptr, i8** %s.addr, align 8, !dbg !3701
  %11 = load i64, i64* %len.addr, align 8, !dbg !3702
  %sub = sub i64 %11, 3, !dbg !3702
  store i64 %sub, i64* %len.addr, align 8, !dbg !3702
  %12 = load i32, i32* %v, align 4, !dbg !3703
  %shr = ashr i32 %12, 18, !dbg !3704
  %and11 = and i32 %shr, 63, !dbg !3705
  %idxprom = sext i32 %and11 to i64, !dbg !3706
  %arrayidx12 = getelementptr inbounds [64 x i8], [64 x i8]* @base64_encode.digits, i64 0, i64 %idxprom, !dbg !3706
  %13 = load i8, i8* %arrayidx12, align 1, !dbg !3706
  %14 = load i8*, i8** %d, align 8, !dbg !3707
  %incdec.ptr = getelementptr inbounds i8, i8* %14, i32 1, !dbg !3707
  store i8* %incdec.ptr, i8** %d, align 8, !dbg !3707
  store i8 %13, i8* %14, align 1, !dbg !3708
  %15 = load i32, i32* %v, align 4, !dbg !3709
  %shr13 = ashr i32 %15, 12, !dbg !3710
  %and14 = and i32 %shr13, 63, !dbg !3711
  %idxprom15 = sext i32 %and14 to i64, !dbg !3712
  %arrayidx16 = getelementptr inbounds [64 x i8], [64 x i8]* @base64_encode.digits, i64 0, i64 %idxprom15, !dbg !3712
  %16 = load i8, i8* %arrayidx16, align 1, !dbg !3712
  %17 = load i8*, i8** %d, align 8, !dbg !3713
  %incdec.ptr17 = getelementptr inbounds i8, i8* %17, i32 1, !dbg !3713
  store i8* %incdec.ptr17, i8** %d, align 8, !dbg !3713
  store i8 %16, i8* %17, align 1, !dbg !3714
  %18 = load i32, i32* %v, align 4, !dbg !3715
  %shr18 = ashr i32 %18, 6, !dbg !3716
  %and19 = and i32 %shr18, 63, !dbg !3717
  %idxprom20 = sext i32 %and19 to i64, !dbg !3718
  %arrayidx21 = getelementptr inbounds [64 x i8], [64 x i8]* @base64_encode.digits, i64 0, i64 %idxprom20, !dbg !3718
  %19 = load i8, i8* %arrayidx21, align 1, !dbg !3718
  %20 = load i8*, i8** %d, align 8, !dbg !3719
  %incdec.ptr22 = getelementptr inbounds i8, i8* %20, i32 1, !dbg !3719
  store i8* %incdec.ptr22, i8** %d, align 8, !dbg !3719
  store i8 %19, i8* %20, align 1, !dbg !3720
  %21 = load i32, i32* %v, align 4, !dbg !3721
  %and23 = and i32 %21, 63, !dbg !3722
  %idxprom24 = sext i32 %and23 to i64, !dbg !3723
  %arrayidx25 = getelementptr inbounds [64 x i8], [64 x i8]* @base64_encode.digits, i64 0, i64 %idxprom24, !dbg !3723
  %22 = load i8, i8* %arrayidx25, align 1, !dbg !3723
  %23 = load i8*, i8** %d, align 8, !dbg !3724
  %incdec.ptr26 = getelementptr inbounds i8, i8* %23, i32 1, !dbg !3724
  store i8* %incdec.ptr26, i8** %d, align 8, !dbg !3724
  store i8 %22, i8* %23, align 1, !dbg !3725
  br label %while.cond, !dbg !3726

while.end:                                        ; preds = %while.cond
  %24 = load i64, i64* %len.addr, align 8, !dbg !3728
  switch i64 %24, label %sw.epilog [
    i64 0, label %sw.bb
    i64 1, label %sw.bb27
    i64 2, label %sw.bb42
  ], !dbg !3729

sw.bb:                                            ; preds = %while.end
  br label %sw.epilog, !dbg !3730

sw.bb27:                                          ; preds = %while.end
  %25 = load i8*, i8** %s.addr, align 8, !dbg !3732
  %arrayidx28 = getelementptr inbounds i8, i8* %25, i64 0, !dbg !3732
  %26 = load i8, i8* %arrayidx28, align 1, !dbg !3732
  %conv29 = sext i8 %26 to i32, !dbg !3733
  %shl30 = shl i32 %conv29, 16, !dbg !3734
  %and31 = and i32 %shl30, 16711680, !dbg !3735
  store i32 %and31, i32* %v, align 4, !dbg !3736
  %27 = load i32, i32* %v, align 4, !dbg !3737
  %shr32 = ashr i32 %27, 18, !dbg !3738
  %and33 = and i32 %shr32, 63, !dbg !3739
  %idxprom34 = sext i32 %and33 to i64, !dbg !3740
  %arrayidx35 = getelementptr inbounds [64 x i8], [64 x i8]* @base64_encode.digits, i64 0, i64 %idxprom34, !dbg !3740
  %28 = load i8, i8* %arrayidx35, align 1, !dbg !3740
  %29 = load i8*, i8** %d, align 8, !dbg !3741
  %incdec.ptr36 = getelementptr inbounds i8, i8* %29, i32 1, !dbg !3741
  store i8* %incdec.ptr36, i8** %d, align 8, !dbg !3741
  store i8 %28, i8* %29, align 1, !dbg !3742
  %30 = load i32, i32* %v, align 4, !dbg !3743
  %shr37 = ashr i32 %30, 12, !dbg !3744
  %and38 = and i32 %shr37, 63, !dbg !3745
  %idxprom39 = sext i32 %and38 to i64, !dbg !3746
  %arrayidx40 = getelementptr inbounds [64 x i8], [64 x i8]* @base64_encode.digits, i64 0, i64 %idxprom39, !dbg !3746
  %31 = load i8, i8* %arrayidx40, align 1, !dbg !3746
  %32 = load i8*, i8** %d, align 8, !dbg !3747
  %incdec.ptr41 = getelementptr inbounds i8, i8* %32, i32 1, !dbg !3747
  store i8* %incdec.ptr41, i8** %d, align 8, !dbg !3747
  store i8 %31, i8* %32, align 1, !dbg !3748
  br label %sw.epilog, !dbg !3749

sw.bb42:                                          ; preds = %while.end
  %33 = load i8*, i8** %s.addr, align 8, !dbg !3750
  %arrayidx43 = getelementptr inbounds i8, i8* %33, i64 0, !dbg !3750
  %34 = load i8, i8* %arrayidx43, align 1, !dbg !3750
  %conv44 = sext i8 %34 to i32, !dbg !3751
  %shl45 = shl i32 %conv44, 16, !dbg !3752
  %and46 = and i32 %shl45, 16711680, !dbg !3753
  %35 = load i8*, i8** %s.addr, align 8, !dbg !3754
  %arrayidx47 = getelementptr inbounds i8, i8* %35, i64 1, !dbg !3754
  %36 = load i8, i8* %arrayidx47, align 1, !dbg !3754
  %conv48 = sext i8 %36 to i32, !dbg !3755
  %shl49 = shl i32 %conv48, 8, !dbg !3756
  %and50 = and i32 %shl49, 65280, !dbg !3757
  %or51 = or i32 %and46, %and50, !dbg !3758
  store i32 %or51, i32* %v, align 4, !dbg !3759
  %37 = load i32, i32* %v, align 4, !dbg !3760
  %shr52 = ashr i32 %37, 18, !dbg !3761
  %and53 = and i32 %shr52, 63, !dbg !3762
  %idxprom54 = sext i32 %and53 to i64, !dbg !3763
  %arrayidx55 = getelementptr inbounds [64 x i8], [64 x i8]* @base64_encode.digits, i64 0, i64 %idxprom54, !dbg !3763
  %38 = load i8, i8* %arrayidx55, align 1, !dbg !3763
  %39 = load i8*, i8** %d, align 8, !dbg !3764
  %incdec.ptr56 = getelementptr inbounds i8, i8* %39, i32 1, !dbg !3764
  store i8* %incdec.ptr56, i8** %d, align 8, !dbg !3764
  store i8 %38, i8* %39, align 1, !dbg !3765
  %40 = load i32, i32* %v, align 4, !dbg !3766
  %shr57 = ashr i32 %40, 12, !dbg !3767
  %and58 = and i32 %shr57, 63, !dbg !3768
  %idxprom59 = sext i32 %and58 to i64, !dbg !3769
  %arrayidx60 = getelementptr inbounds [64 x i8], [64 x i8]* @base64_encode.digits, i64 0, i64 %idxprom59, !dbg !3769
  %41 = load i8, i8* %arrayidx60, align 1, !dbg !3769
  %42 = load i8*, i8** %d, align 8, !dbg !3770
  %incdec.ptr61 = getelementptr inbounds i8, i8* %42, i32 1, !dbg !3770
  store i8* %incdec.ptr61, i8** %d, align 8, !dbg !3770
  store i8 %41, i8* %42, align 1, !dbg !3771
  %43 = load i32, i32* %v, align 4, !dbg !3772
  %shr62 = ashr i32 %43, 6, !dbg !3773
  %and63 = and i32 %shr62, 63, !dbg !3774
  %idxprom64 = sext i32 %and63 to i64, !dbg !3775
  %arrayidx65 = getelementptr inbounds [64 x i8], [64 x i8]* @base64_encode.digits, i64 0, i64 %idxprom64, !dbg !3775
  %44 = load i8, i8* %arrayidx65, align 1, !dbg !3775
  %45 = load i8*, i8** %d, align 8, !dbg !3776
  %incdec.ptr66 = getelementptr inbounds i8, i8* %45, i32 1, !dbg !3776
  store i8* %incdec.ptr66, i8** %d, align 8, !dbg !3776
  store i8 %44, i8* %45, align 1, !dbg !3777
  br label %sw.epilog, !dbg !3778

sw.epilog:                                        ; preds = %while.end, %sw.bb42, %sw.bb27, %sw.bb
  %46 = load i8*, i8** %d, align 8, !dbg !3779
  store i8 0, i8* %46, align 1, !dbg !3780
  %47 = load i8*, i8** %out, align 8, !dbg !3781
  store i8* %47, i8** %retval, align 8, !dbg !3782
  br label %return, !dbg !3782

return:                                           ; preds = %sw.epilog, %if.then
  %48 = load i8*, i8** %retval, align 8, !dbg !3783
  ret i8* %48, !dbg !3783
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!289, !290}
!llvm.ident = !{!291}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !217, globals: !284)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_pax.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !124, !192, !47, !214, !23, !52, !13, !216, !38, !45, !196, !115, !203, !95, !80}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write", file: !6, line: 72, size: 2816, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !111, !112, !113, !114, !118, !119, !125, !131, !134, !135, !136, !137, !163, !164, !165, !166, !170, !174, !175, !179, !183, !184, !185, !186, !191}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 73, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !105, !106, !107, !108, !109, !110}
!12 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !9, file: !10, line: 96, baseType: !13, size: 32, align: 32)
!13 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!14 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !9, file: !10, line: 97, baseType: !13, size: 32, align: 32, offset: 32)
!15 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !9, file: !10, line: 103, baseType: !16, size: 64, align: 64, offset: 64)
!16 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !17, size: 64, align: 64)
!17 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !10, line: 63, size: 832, align: 64, elements: !18)
!18 = !{!19, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !17, file: !10, line: 64, baseType: !20, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !24}
!23 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !9, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !17, file: !10, line: 65, baseType: !20, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !17, file: !10, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!23, !24, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 180, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !17, file: !10, line: 68, baseType: !20, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !17, file: !10, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !24, !43, !45}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 109, baseType: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !41, line: 172, baseType: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!42 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !47)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !17, file: !10, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !24, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !17, file: !10, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!23, !24, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !17, file: !10, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !17, file: !10, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!23, !24, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !17, file: !10, line: 81, baseType: !20, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !17, file: !10, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !24, !23}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !17, file: !10, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!23, !24, !23}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !17, file: !10, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !24, !23}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !9, file: !10, line: 105, baseType: !23, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !9, file: !10, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !9, file: !10, line: 108, baseType: !23, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !9, file: !10, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !9, file: !10, line: 112, baseType: !23, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !9, file: !10, line: 114, baseType: !23, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !9, file: !10, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !9, file: !10, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !9, file: !10, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !9, file: !10, line: 119, baseType: !13, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !9, file: !10, line: 120, baseType: !13, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !9, file: !10, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !104, line: 36, flags: DIFlagFwdDecl)
!104 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_entry_locale.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 76, baseType: !23, size: 32, align: 32, offset: 1280)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 77, baseType: !52, size: 64, align: 64, offset: 1344)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 78, baseType: !52, size: 64, align: 64, offset: 1408)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "nulls", scope: !5, file: !6, line: 81, baseType: !115, size: 64, align: 64, offset: 1472)
!115 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !116, size: 64, align: 64)
!116 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !117)
!117 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "null_length", scope: !5, file: !6, line: 82, baseType: !45, size: 64, align: 64, offset: 1536)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "client_opener", scope: !5, file: !6, line: 85, baseType: !120, size: 64, align: 64, offset: 1600)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !122)
!122 = !DISubroutineType(types: !123)
!123 = !{!23, !24, !124}
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "client_writer", scope: !5, file: !6, line: 86, baseType: !126, size: 64, align: 64, offset: 1664)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_write_callback", file: !32, line: 237, baseType: !128)
!128 = !DISubroutineType(types: !129)
!129 = !{!130, !24, !124, !43, !45}
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "client_closer", scope: !5, file: !6, line: 87, baseType: !132, size: 64, align: 64, offset: 1728)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !133, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !122)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !5, file: !6, line: 88, baseType: !124, size: 64, align: 64, offset: 1792)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !5, file: !6, line: 96, baseType: !23, size: 32, align: 32, offset: 1856)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !5, file: !6, line: 97, baseType: !23, size: 32, align: 32, offset: 1888)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "filter_first", scope: !5, file: !6, line: 102, baseType: !138, size: 64, align: 64, offset: 1920)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !139, size: 64, align: 64)
!139 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !6, line: 43, size: 768, align: 64, elements: !140)
!140 = !{!141, !142, !143, !144, !148, !152, !156, !157, !158, !159, !160, !161, !162}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !139, file: !6, line: 44, baseType: !52, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !139, file: !6, line: 45, baseType: !24, size: 64, align: 64, offset: 64)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !139, file: !6, line: 46, baseType: !138, size: 64, align: 64, offset: 128)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !139, file: !6, line: 47, baseType: !145, size: 64, align: 64, offset: 192)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DISubroutineType(types: !147)
!147 = !{!23, !138, !80, !80}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !139, file: !6, line: 49, baseType: !149, size: 64, align: 64, offset: 256)
!149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !150, size: 64, align: 64)
!150 = !DISubroutineType(types: !151)
!151 = !{!23, !138}
!152 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !139, file: !6, line: 50, baseType: !153, size: 64, align: 64, offset: 320)
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!154 = !DISubroutineType(types: !155)
!155 = !{!23, !138, !43, !45}
!156 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !139, file: !6, line: 51, baseType: !149, size: 64, align: 64, offset: 384)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !139, file: !6, line: 52, baseType: !149, size: 64, align: 64, offset: 448)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !139, file: !6, line: 53, baseType: !124, size: 64, align: 64, offset: 512)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !139, file: !6, line: 54, baseType: !80, size: 64, align: 64, offset: 576)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !139, file: !6, line: 55, baseType: !23, size: 32, align: 32, offset: 640)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !139, file: !6, line: 56, baseType: !23, size: 32, align: 32, offset: 672)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !139, file: !6, line: 57, baseType: !23, size: 32, align: 32, offset: 704)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "filter_last", scope: !5, file: !6, line: 103, baseType: !138, size: 64, align: 64, offset: 1984)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "format_data", scope: !5, file: !6, line: 109, baseType: !124, size: 64, align: 64, offset: 2048)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "format_name", scope: !5, file: !6, line: 110, baseType: !80, size: 64, align: 64, offset: 2112)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "format_init", scope: !5, file: !6, line: 111, baseType: !167, size: 64, align: 64, offset: 2176)
!167 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !168, size: 64, align: 64)
!168 = !DISubroutineType(types: !169)
!169 = !{!23, !4}
!170 = !DIDerivedType(tag: DW_TAG_member, name: "format_options", scope: !5, file: !6, line: 112, baseType: !171, size: 64, align: 64, offset: 2240)
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !172, size: 64, align: 64)
!172 = !DISubroutineType(types: !173)
!173 = !{!23, !4, !80, !80}
!174 = !DIDerivedType(tag: DW_TAG_member, name: "format_finish_entry", scope: !5, file: !6, line: 114, baseType: !167, size: 64, align: 64, offset: 2304)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_header", scope: !5, file: !6, line: 115, baseType: !176, size: 64, align: 64, offset: 2368)
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!177 = !DISubroutineType(types: !178)
!178 = !{!23, !4, !30}
!179 = !DIDerivedType(tag: DW_TAG_member, name: "format_write_data", scope: !5, file: !6, line: 117, baseType: !180, size: 64, align: 64, offset: 2432)
!180 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !181, size: 64, align: 64)
!181 = !DISubroutineType(types: !182)
!182 = !{!38, !4, !43, !45}
!183 = !DIDerivedType(tag: DW_TAG_member, name: "format_close", scope: !5, file: !6, line: 119, baseType: !167, size: 64, align: 64, offset: 2496)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "format_free", scope: !5, file: !6, line: 120, baseType: !167, size: 64, align: 64, offset: 2560)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !5, file: !6, line: 126, baseType: !95, size: 64, align: 64, offset: 2624)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_callback", scope: !5, file: !6, line: 127, baseType: !187, size: 64, align: 64, offset: 2688)
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !188, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !189)
!189 = !DISubroutineType(types: !190)
!190 = !{!80, !24, !124}
!191 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase_client_data", scope: !5, file: !6, line: 128, baseType: !124, size: 64, align: 64, offset: 2752)
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DICompositeType(tag: DW_TAG_structure_type, name: "pax", file: !1, line: 54, size: 1024, align: 64, elements: !194)
!194 = !{!195, !197, !198, !199, !200, !201, !202, !210, !211, !212, !213}
!195 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !193, file: !1, line: 55, baseType: !196, size: 64, align: 64)
!196 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "entry_padding", scope: !193, file: !1, line: 56, baseType: !196, size: 64, align: 64, offset: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "l_url_encoded_name", scope: !193, file: !1, line: 57, baseType: !91, size: 192, align: 64, offset: 128)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "pax_header", scope: !193, file: !1, line: 58, baseType: !91, size: 192, align: 64, offset: 320)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_map", scope: !193, file: !1, line: 59, baseType: !91, size: 192, align: 64, offset: 512)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_map_padding", scope: !193, file: !1, line: 60, baseType: !45, size: 64, align: 64, offset: 704)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_list", scope: !193, file: !1, line: 61, baseType: !203, size: 64, align: 64, offset: 768)
!203 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !204, size: 64, align: 64)
!204 = !DICompositeType(tag: DW_TAG_structure_type, name: "sparse_block", file: !1, line: 47, size: 256, align: 64, elements: !205)
!205 = !{!206, !207, !208, !209}
!206 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !204, file: !1, line: 48, baseType: !203, size: 64, align: 64)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "is_hole", scope: !204, file: !1, line: 49, baseType: !23, size: 32, align: 32, offset: 64)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !204, file: !1, line: 50, baseType: !196, size: 64, align: 64, offset: 128)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "remaining", scope: !204, file: !1, line: 51, baseType: !196, size: 64, align: 64, offset: 192)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "sparse_tail", scope: !193, file: !1, line: 62, baseType: !203, size: 64, align: 64, offset: 832)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "sconv_utf8", scope: !193, file: !1, line: 63, baseType: !102, size: 64, align: 64, offset: 896)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "opt_binary", scope: !193, file: !1, line: 64, baseType: !23, size: 32, align: 32, offset: 960)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !193, file: !1, line: 66, baseType: !13, size: 32, align: 32, offset: 992)
!214 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !39, line: 70, baseType: !215)
!215 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!216 = !DIDerivedType(tag: DW_TAG_typedef, name: "intmax_t", file: !53, line: 134, baseType: !42)
!217 = !{!218, !219, !220, !221, !222, !226, !229, !230, !231, !232, !233, !237, !240, !243, !246, !249, !252, !255, !258, !261, !264, !267, !270, !273, !276, !279, !280, !281, !282, !283}
!218 = distinct !DISubprogram(name: "archive_write_set_format_pax_restricted", scope: !1, file: !1, line: 111, type: !21, isLocal: false, isDefinition: true, scopeLine: 112, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!219 = distinct !DISubprogram(name: "archive_write_set_format_pax", scope: !1, file: !1, line: 129, type: !21, isLocal: false, isDefinition: true, scopeLine: 130, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!220 = distinct !DISubprogram(name: "archive_write_pax_options", scope: !1, file: !1, line: 162, type: !172, isLocal: true, isDefinition: true, scopeLine: 164, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!221 = distinct !DISubprogram(name: "archive_write_pax_header", scope: !1, file: !1, line: 542, type: !177, isLocal: true, isDefinition: true, scopeLine: 544, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!222 = distinct !DISubprogram(name: "get_entry_hardlink", scope: !1, file: !1, line: 405, type: !223, isLocal: true, isDefinition: true, scopeLine: 407, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!223 = !DISubroutineType(types: !224)
!224 = !{!23, !4, !30, !225, !65, !102}
!225 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!226 = distinct !DISubprogram(name: "sparse_list_clear", scope: !1, file: !1, line: 1916, type: !227, isLocal: true, isDefinition: true, scopeLine: 1917, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!227 = !DISubroutineType(types: !228)
!228 = !{null, !192}
!229 = distinct !DISubprogram(name: "get_entry_pathname", scope: !1, file: !1, line: 423, type: !223, isLocal: true, isDefinition: true, scopeLine: 425, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!230 = distinct !DISubprogram(name: "get_entry_uname", scope: !1, file: !1, line: 441, type: !223, isLocal: true, isDefinition: true, scopeLine: 443, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!231 = distinct !DISubprogram(name: "get_entry_gname", scope: !1, file: !1, line: 459, type: !223, isLocal: true, isDefinition: true, scopeLine: 461, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!232 = distinct !DISubprogram(name: "get_entry_symlink", scope: !1, file: !1, line: 477, type: !223, isLocal: true, isDefinition: true, scopeLine: 479, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!233 = distinct !DISubprogram(name: "add_pax_attr", scope: !1, file: !1, line: 285, type: !234, isLocal: true, isDefinition: true, scopeLine: 286, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!234 = !DISubroutineType(types: !235)
!235 = !{null, !236, !80, !80}
!236 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !91, size: 64, align: 64)
!237 = distinct !DISubprogram(name: "add_pax_attr_binary", scope: !1, file: !1, line: 295, type: !238, isLocal: true, isDefinition: true, scopeLine: 297, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!238 = !DISubroutineType(types: !239)
!239 = !{null, !236, !80, !80, !45}
!240 = distinct !DISubprogram(name: "format_int", scope: !1, file: !1, line: 254, type: !241, isLocal: true, isDefinition: true, scopeLine: 255, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!241 = !DISubroutineType(types: !242)
!242 = !{!95, !95, !52}
!243 = distinct !DISubprogram(name: "has_non_ASCII", scope: !1, file: !1, line: 1809, type: !244, isLocal: true, isDefinition: true, scopeLine: 1810, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!244 = !DISubroutineType(types: !245)
!245 = !{!23, !80}
!246 = distinct !DISubprogram(name: "build_ustar_entry_name", scope: !1, file: !1, line: 1458, type: !247, isLocal: true, isDefinition: true, scopeLine: 1460, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!247 = !DISubroutineType(types: !248)
!248 = !{!95, !95, !80, !45, !80}
!249 = distinct !DISubprogram(name: "add_pax_attr_int", scope: !1, file: !1, line: 272, type: !250, isLocal: true, isDefinition: true, scopeLine: 273, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!250 = !DISubroutineType(types: !251)
!251 = !{null, !236, !80, !52}
!252 = distinct !DISubprogram(name: "add_pax_attr_time", scope: !1, file: !1, line: 218, type: !253, isLocal: true, isDefinition: true, scopeLine: 220, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!253 = !DISubroutineType(types: !254)
!254 = !{null, !236, !80, !52, !47}
!255 = distinct !DISubprogram(name: "add_pax_acl", scope: !1, file: !1, line: 496, type: !256, isLocal: true, isDefinition: true, scopeLine: 498, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!256 = !DISubroutineType(types: !257)
!257 = !{!23, !4, !30, !192, !23}
!258 = distinct !DISubprogram(name: "build_gnu_sparse_name", scope: !1, file: !1, line: 1657, type: !259, isLocal: true, isDefinition: true, scopeLine: 1658, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!259 = !DISubroutineType(types: !260)
!260 = !{!95, !95, !80}
!261 = distinct !DISubprogram(name: "sparse_list_add", scope: !1, file: !1, line: 1949, type: !262, isLocal: true, isDefinition: true, scopeLine: 1950, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!262 = !DISubroutineType(types: !263)
!263 = !{!23, !192, !52, !52}
!264 = distinct !DISubprogram(name: "_sparse_list_add_block", scope: !1, file: !1, line: 1927, type: !265, isLocal: true, isDefinition: true, scopeLine: 1929, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!265 = !DISubroutineType(types: !266)
!266 = !{!23, !192, !52, !52, !23}
!267 = distinct !DISubprogram(name: "archive_write_pax_header_xattrs", scope: !1, file: !1, line: 369, type: !268, isLocal: true, isDefinition: true, scopeLine: 371, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!268 = !DISubroutineType(types: !269)
!269 = !{!23, !4, !192, !30}
!270 = distinct !DISubprogram(name: "url_encode", scope: !1, file: !1, line: 1825, type: !271, isLocal: true, isDefinition: true, scopeLine: 1826, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!271 = !DISubroutineType(types: !272)
!272 = !{!95, !80}
!273 = distinct !DISubprogram(name: "archive_write_pax_header_xattr", scope: !1, file: !1, line: 341, type: !274, isLocal: true, isDefinition: true, scopeLine: 343, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!274 = !DISubroutineType(types: !275)
!275 = !{null, !192, !80, !43, !45}
!276 = distinct !DISubprogram(name: "base64_encode", scope: !1, file: !1, line: 1865, type: !277, isLocal: true, isDefinition: true, scopeLine: 1866, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!277 = !DISubroutineType(types: !278)
!278 = !{!95, !80, !45}
!279 = distinct !DISubprogram(name: "build_pax_attribute_name", scope: !1, file: !1, line: 1590, type: !259, isLocal: true, isDefinition: true, scopeLine: 1591, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!280 = distinct !DISubprogram(name: "archive_write_pax_close", scope: !1, file: !1, line: 1700, type: !168, isLocal: true, isDefinition: true, scopeLine: 1701, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!281 = distinct !DISubprogram(name: "archive_write_pax_free", scope: !1, file: !1, line: 1706, type: !168, isLocal: true, isDefinition: true, scopeLine: 1707, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!282 = distinct !DISubprogram(name: "archive_write_pax_finish_entry", scope: !1, file: !1, line: 1724, type: !168, isLocal: true, isDefinition: true, scopeLine: 1725, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!283 = distinct !DISubprogram(name: "archive_write_pax_data", scope: !1, file: !1, line: 1748, type: !181, isLocal: true, isDefinition: true, scopeLine: 1749, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!284 = !{!285}
!285 = !DIGlobalVariable(name: "digits", scope: !276, file: !1, line: 1867, type: !286, isLocal: true, isDefinition: true, variable: [64 x i8]* @base64_encode.digits)
!286 = !DICompositeType(tag: DW_TAG_array_type, baseType: !81, size: 512, align: 8, elements: !287)
!287 = !{!288}
!288 = !DISubrange(count: 64)
!289 = !{i32 2, !"Dwarf Version", i32 4}
!290 = !{i32 2, !"Debug Info Version", i32 3}
!291 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!292 = !DILocalVariable(name: "_a", arg: 1, scope: !218, file: !1, line: 111, type: !24)
!293 = !DIExpression()
!294 = !DILocation(line: 111, column: 57, scope: !218)
!295 = !DILocalVariable(name: "a", scope: !218, file: !1, line: 113, type: !4)
!296 = !DILocation(line: 113, column: 24, scope: !218)
!297 = !DILocation(line: 113, column: 52, scope: !218)
!298 = !DILocation(line: 113, column: 28, scope: !218)
!299 = !DILocalVariable(name: "r", scope: !218, file: !1, line: 114, type: !23)
!300 = !DILocation(line: 114, column: 6, scope: !218)
!301 = !DILocation(line: 116, column: 2, scope: !218)
!302 = !DILocalVariable(name: "magic_test", scope: !303, file: !1, line: 116, type: !23)
!303 = distinct !DILexicalBlock(scope: !218, file: !1, line: 116, column: 2)
!304 = !DILocation(line: 116, column: 2, scope: !303)
!305 = !DILocation(line: 116, column: 2, scope: !306)
!306 = !DILexicalBlockFile(scope: !303, file: !1, discriminator: 1)
!307 = !DILocation(line: 116, column: 2, scope: !308)
!308 = !DILexicalBlockFile(scope: !309, file: !1, discriminator: 2)
!309 = distinct !DILexicalBlock(scope: !303, file: !1, line: 116, column: 2)
!310 = !DILocation(line: 116, column: 2, scope: !311)
!311 = !DILexicalBlockFile(scope: !303, file: !1, discriminator: 3)
!312 = !DILocation(line: 119, column: 36, scope: !218)
!313 = !DILocation(line: 119, column: 39, scope: !218)
!314 = !DILocation(line: 119, column: 6, scope: !218)
!315 = !DILocation(line: 119, column: 4, scope: !218)
!316 = !DILocation(line: 120, column: 2, scope: !218)
!317 = !DILocation(line: 120, column: 5, scope: !218)
!318 = !DILocation(line: 120, column: 13, scope: !218)
!319 = !DILocation(line: 120, column: 28, scope: !218)
!320 = !DILocation(line: 121, column: 2, scope: !218)
!321 = !DILocation(line: 121, column: 5, scope: !218)
!322 = !DILocation(line: 121, column: 13, scope: !218)
!323 = !DILocation(line: 121, column: 33, scope: !218)
!324 = !DILocation(line: 122, column: 10, scope: !218)
!325 = !DILocation(line: 122, column: 2, scope: !218)
!326 = !DILocation(line: 123, column: 1, scope: !218)
!327 = !DILocalVariable(name: "_a", arg: 1, scope: !219, file: !1, line: 129, type: !24)
!328 = !DILocation(line: 129, column: 46, scope: !219)
!329 = !DILocalVariable(name: "a", scope: !219, file: !1, line: 131, type: !4)
!330 = !DILocation(line: 131, column: 24, scope: !219)
!331 = !DILocation(line: 131, column: 52, scope: !219)
!332 = !DILocation(line: 131, column: 28, scope: !219)
!333 = !DILocalVariable(name: "pax", scope: !219, file: !1, line: 132, type: !192)
!334 = !DILocation(line: 132, column: 14, scope: !219)
!335 = !DILocation(line: 134, column: 2, scope: !219)
!336 = !DILocalVariable(name: "magic_test", scope: !337, file: !1, line: 134, type: !23)
!337 = distinct !DILexicalBlock(scope: !219, file: !1, line: 134, column: 2)
!338 = !DILocation(line: 134, column: 2, scope: !337)
!339 = !DILocation(line: 134, column: 2, scope: !340)
!340 = !DILexicalBlockFile(scope: !337, file: !1, discriminator: 1)
!341 = !DILocation(line: 134, column: 2, scope: !342)
!342 = !DILexicalBlockFile(scope: !343, file: !1, discriminator: 2)
!343 = distinct !DILexicalBlock(scope: !337, file: !1, line: 134, column: 2)
!344 = !DILocation(line: 134, column: 2, scope: !345)
!345 = !DILexicalBlockFile(scope: !337, file: !1, discriminator: 3)
!346 = !DILocation(line: 137, column: 6, scope: !347)
!347 = distinct !DILexicalBlock(scope: !219, file: !1, line: 137, column: 6)
!348 = !DILocation(line: 137, column: 9, scope: !347)
!349 = !DILocation(line: 137, column: 21, scope: !347)
!350 = !DILocation(line: 137, column: 6, scope: !219)
!351 = !DILocation(line: 138, column: 4, scope: !347)
!352 = !DILocation(line: 138, column: 7, scope: !347)
!353 = !DILocation(line: 138, column: 20, scope: !347)
!354 = !DILocation(line: 138, column: 3, scope: !347)
!355 = !DILocation(line: 140, column: 22, scope: !219)
!356 = !DILocation(line: 140, column: 8, scope: !219)
!357 = !DILocation(line: 140, column: 6, scope: !219)
!358 = !DILocation(line: 141, column: 6, scope: !359)
!359 = distinct !DILexicalBlock(scope: !219, file: !1, line: 141, column: 6)
!360 = !DILocation(line: 141, column: 10, scope: !359)
!361 = !DILocation(line: 141, column: 6, scope: !219)
!362 = !DILocation(line: 142, column: 22, scope: !363)
!363 = distinct !DILexicalBlock(scope: !359, file: !1, line: 141, column: 19)
!364 = !DILocation(line: 142, column: 25, scope: !363)
!365 = !DILocation(line: 142, column: 3, scope: !363)
!366 = !DILocation(line: 144, column: 3, scope: !363)
!367 = !DILocation(line: 146, column: 2, scope: !219)
!368 = !DILocation(line: 146, column: 7, scope: !219)
!369 = !DILocation(line: 146, column: 13, scope: !219)
!370 = !DILocation(line: 148, column: 19, scope: !219)
!371 = !DILocation(line: 148, column: 2, scope: !219)
!372 = !DILocation(line: 148, column: 5, scope: !219)
!373 = !DILocation(line: 148, column: 17, scope: !219)
!374 = !DILocation(line: 149, column: 2, scope: !219)
!375 = !DILocation(line: 149, column: 5, scope: !219)
!376 = !DILocation(line: 149, column: 17, scope: !219)
!377 = !DILocation(line: 150, column: 2, scope: !219)
!378 = !DILocation(line: 150, column: 5, scope: !219)
!379 = !DILocation(line: 150, column: 20, scope: !219)
!380 = !DILocation(line: 151, column: 2, scope: !219)
!381 = !DILocation(line: 151, column: 5, scope: !219)
!382 = !DILocation(line: 151, column: 25, scope: !219)
!383 = !DILocation(line: 152, column: 2, scope: !219)
!384 = !DILocation(line: 152, column: 5, scope: !219)
!385 = !DILocation(line: 152, column: 23, scope: !219)
!386 = !DILocation(line: 153, column: 2, scope: !219)
!387 = !DILocation(line: 153, column: 5, scope: !219)
!388 = !DILocation(line: 153, column: 18, scope: !219)
!389 = !DILocation(line: 154, column: 2, scope: !219)
!390 = !DILocation(line: 154, column: 5, scope: !219)
!391 = !DILocation(line: 154, column: 17, scope: !219)
!392 = !DILocation(line: 155, column: 2, scope: !219)
!393 = !DILocation(line: 155, column: 5, scope: !219)
!394 = !DILocation(line: 155, column: 25, scope: !219)
!395 = !DILocation(line: 156, column: 2, scope: !219)
!396 = !DILocation(line: 156, column: 5, scope: !219)
!397 = !DILocation(line: 156, column: 13, scope: !219)
!398 = !DILocation(line: 156, column: 28, scope: !219)
!399 = !DILocation(line: 157, column: 2, scope: !219)
!400 = !DILocation(line: 157, column: 5, scope: !219)
!401 = !DILocation(line: 157, column: 13, scope: !219)
!402 = !DILocation(line: 157, column: 33, scope: !219)
!403 = !DILocation(line: 158, column: 2, scope: !219)
!404 = !DILocation(line: 159, column: 1, scope: !219)
!405 = !DILocalVariable(name: "a", arg: 1, scope: !220, file: !1, line: 162, type: !4)
!406 = !DILocation(line: 162, column: 49, scope: !220)
!407 = !DILocalVariable(name: "key", arg: 2, scope: !220, file: !1, line: 162, type: !80)
!408 = !DILocation(line: 162, column: 64, scope: !220)
!409 = !DILocalVariable(name: "val", arg: 3, scope: !220, file: !1, line: 163, type: !80)
!410 = !DILocation(line: 163, column: 17, scope: !220)
!411 = !DILocalVariable(name: "pax", scope: !220, file: !1, line: 165, type: !192)
!412 = !DILocation(line: 165, column: 14, scope: !220)
!413 = !DILocation(line: 165, column: 34, scope: !220)
!414 = !DILocation(line: 165, column: 37, scope: !220)
!415 = !DILocation(line: 165, column: 20, scope: !220)
!416 = !DILocalVariable(name: "ret", scope: !220, file: !1, line: 166, type: !23)
!417 = !DILocation(line: 166, column: 6, scope: !220)
!418 = !DILocation(line: 168, column: 13, scope: !419)
!419 = distinct !DILexicalBlock(scope: !220, file: !1, line: 168, column: 6)
!420 = !DILocation(line: 168, column: 6, scope: !419)
!421 = !DILocation(line: 168, column: 33, scope: !419)
!422 = !DILocation(line: 168, column: 6, scope: !220)
!423 = !DILocation(line: 173, column: 7, scope: !424)
!424 = distinct !DILexicalBlock(scope: !425, file: !1, line: 173, column: 7)
!425 = distinct !DILexicalBlock(scope: !419, file: !1, line: 168, column: 39)
!426 = !DILocation(line: 173, column: 11, scope: !424)
!427 = !DILocation(line: 173, column: 19, scope: !424)
!428 = !DILocation(line: 173, column: 22, scope: !429)
!429 = !DILexicalBlockFile(scope: !424, file: !1, discriminator: 1)
!430 = !DILocation(line: 173, column: 29, scope: !429)
!431 = !DILocation(line: 173, column: 7, scope: !429)
!432 = !DILocation(line: 174, column: 23, scope: !424)
!433 = !DILocation(line: 174, column: 26, scope: !424)
!434 = !DILocation(line: 174, column: 4, scope: !424)
!435 = !DILocation(line: 176, column: 19, scope: !436)
!436 = distinct !DILexicalBlock(scope: !424, file: !1, line: 176, column: 12)
!437 = !DILocation(line: 176, column: 12, scope: !436)
!438 = !DILocation(line: 176, column: 34, scope: !436)
!439 = !DILocation(line: 176, column: 39, scope: !436)
!440 = !DILocation(line: 177, column: 14, scope: !436)
!441 = !DILocation(line: 177, column: 7, scope: !436)
!442 = !DILocation(line: 177, column: 29, scope: !436)
!443 = !DILocation(line: 176, column: 12, scope: !429)
!444 = !DILocation(line: 182, column: 4, scope: !445)
!445 = distinct !DILexicalBlock(scope: !436, file: !1, line: 177, column: 35)
!446 = !DILocation(line: 182, column: 9, scope: !445)
!447 = !DILocation(line: 182, column: 20, scope: !445)
!448 = !DILocation(line: 183, column: 8, scope: !445)
!449 = !DILocation(line: 184, column: 3, scope: !445)
!450 = !DILocation(line: 184, column: 21, scope: !451)
!451 = !DILexicalBlockFile(scope: !452, file: !1, discriminator: 1)
!452 = distinct !DILexicalBlock(scope: !436, file: !1, line: 184, column: 14)
!453 = !DILocation(line: 184, column: 14, scope: !451)
!454 = !DILocation(line: 184, column: 35, scope: !451)
!455 = !DILocation(line: 193, column: 10, scope: !456)
!456 = distinct !DILexicalBlock(scope: !452, file: !1, line: 184, column: 41)
!457 = !DILocation(line: 193, column: 13, scope: !456)
!458 = !DILocation(line: 192, column: 22, scope: !456)
!459 = !DILocation(line: 192, column: 4, scope: !456)
!460 = !DILocation(line: 192, column: 9, scope: !456)
!461 = !DILocation(line: 192, column: 20, scope: !456)
!462 = !DILocation(line: 194, column: 8, scope: !463)
!463 = distinct !DILexicalBlock(scope: !456, file: !1, line: 194, column: 8)
!464 = !DILocation(line: 194, column: 13, scope: !463)
!465 = !DILocation(line: 194, column: 24, scope: !463)
!466 = !DILocation(line: 194, column: 8, scope: !456)
!467 = !DILocation(line: 195, column: 9, scope: !463)
!468 = !DILocation(line: 195, column: 5, scope: !463)
!469 = !DILocation(line: 197, column: 9, scope: !463)
!470 = !DILocation(line: 198, column: 3, scope: !456)
!471 = !DILocation(line: 199, column: 23, scope: !452)
!472 = !DILocation(line: 199, column: 26, scope: !452)
!473 = !DILocation(line: 199, column: 4, scope: !452)
!474 = !DILocation(line: 201, column: 11, scope: !425)
!475 = !DILocation(line: 201, column: 3, scope: !425)
!476 = !DILocation(line: 207, column: 2, scope: !220)
!477 = !DILocation(line: 208, column: 1, scope: !220)
!478 = !DILocalVariable(name: "a", arg: 1, scope: !221, file: !1, line: 542, type: !4)
!479 = !DILocation(line: 542, column: 48, scope: !221)
!480 = !DILocalVariable(name: "entry_original", arg: 2, scope: !221, file: !1, line: 543, type: !30)
!481 = !DILocation(line: 543, column: 27, scope: !221)
!482 = !DILocalVariable(name: "entry_main", scope: !221, file: !1, line: 545, type: !30)
!483 = !DILocation(line: 545, column: 24, scope: !221)
!484 = !DILocalVariable(name: "p", scope: !221, file: !1, line: 546, type: !80)
!485 = !DILocation(line: 546, column: 14, scope: !221)
!486 = !DILocalVariable(name: "suffix", scope: !221, file: !1, line: 547, type: !80)
!487 = !DILocation(line: 547, column: 14, scope: !221)
!488 = !DILocalVariable(name: "need_extension", scope: !221, file: !1, line: 548, type: !23)
!489 = !DILocation(line: 548, column: 6, scope: !221)
!490 = !DILocalVariable(name: "r", scope: !221, file: !1, line: 548, type: !23)
!491 = !DILocation(line: 548, column: 22, scope: !221)
!492 = !DILocalVariable(name: "ret", scope: !221, file: !1, line: 548, type: !23)
!493 = !DILocation(line: 548, column: 25, scope: !221)
!494 = !DILocalVariable(name: "acl_types", scope: !221, file: !1, line: 549, type: !23)
!495 = !DILocation(line: 549, column: 6, scope: !221)
!496 = !DILocalVariable(name: "sparse_count", scope: !221, file: !1, line: 550, type: !23)
!497 = !DILocation(line: 550, column: 6, scope: !221)
!498 = !DILocalVariable(name: "sparse_total", scope: !221, file: !1, line: 551, type: !196)
!499 = !DILocation(line: 551, column: 11, scope: !221)
!500 = !DILocalVariable(name: "real_size", scope: !221, file: !1, line: 551, type: !196)
!501 = !DILocation(line: 551, column: 25, scope: !221)
!502 = !DILocalVariable(name: "pax", scope: !221, file: !1, line: 552, type: !192)
!503 = !DILocation(line: 552, column: 14, scope: !221)
!504 = !DILocalVariable(name: "hardlink", scope: !221, file: !1, line: 553, type: !80)
!505 = !DILocation(line: 553, column: 14, scope: !221)
!506 = !DILocalVariable(name: "path", scope: !221, file: !1, line: 554, type: !80)
!507 = !DILocation(line: 554, column: 14, scope: !221)
!508 = !DILocalVariable(name: "linkpath", scope: !221, file: !1, line: 554, type: !80)
!509 = !DILocation(line: 554, column: 28, scope: !221)
!510 = !DILocalVariable(name: "uname", scope: !221, file: !1, line: 555, type: !80)
!511 = !DILocation(line: 555, column: 14, scope: !221)
!512 = !DILocalVariable(name: "gname", scope: !221, file: !1, line: 555, type: !80)
!513 = !DILocation(line: 555, column: 29, scope: !221)
!514 = !DILocalVariable(name: "mac_metadata", scope: !221, file: !1, line: 556, type: !43)
!515 = !DILocation(line: 556, column: 14, scope: !221)
!516 = !DILocalVariable(name: "mac_metadata_size", scope: !221, file: !1, line: 557, type: !45)
!517 = !DILocation(line: 557, column: 9, scope: !221)
!518 = !DILocalVariable(name: "sconv", scope: !221, file: !1, line: 558, type: !102)
!519 = !DILocation(line: 558, column: 30, scope: !221)
!520 = !DILocalVariable(name: "hardlink_length", scope: !221, file: !1, line: 559, type: !45)
!521 = !DILocation(line: 559, column: 9, scope: !221)
!522 = !DILocalVariable(name: "path_length", scope: !221, file: !1, line: 559, type: !45)
!523 = !DILocation(line: 559, column: 26, scope: !221)
!524 = !DILocalVariable(name: "linkpath_length", scope: !221, file: !1, line: 559, type: !45)
!525 = !DILocation(line: 559, column: 39, scope: !221)
!526 = !DILocalVariable(name: "uname_length", scope: !221, file: !1, line: 560, type: !45)
!527 = !DILocation(line: 560, column: 9, scope: !221)
!528 = !DILocalVariable(name: "gname_length", scope: !221, file: !1, line: 560, type: !45)
!529 = !DILocation(line: 560, column: 23, scope: !221)
!530 = !DILocalVariable(name: "paxbuff", scope: !221, file: !1, line: 562, type: !531)
!531 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 4096, align: 8, elements: !532)
!532 = !{!533}
!533 = !DISubrange(count: 512)
!534 = !DILocation(line: 562, column: 7, scope: !221)
!535 = !DILocalVariable(name: "ustarbuff", scope: !221, file: !1, line: 563, type: !531)
!536 = !DILocation(line: 563, column: 7, scope: !221)
!537 = !DILocalVariable(name: "ustar_entry_name", scope: !221, file: !1, line: 564, type: !538)
!538 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 2048, align: 8, elements: !539)
!539 = !{!540}
!540 = !DISubrange(count: 256)
!541 = !DILocation(line: 564, column: 7, scope: !221)
!542 = !DILocalVariable(name: "pax_entry_name", scope: !221, file: !1, line: 565, type: !538)
!543 = !DILocation(line: 565, column: 7, scope: !221)
!544 = !DILocalVariable(name: "gnu_sparse_name", scope: !221, file: !1, line: 566, type: !538)
!545 = !DILocation(line: 566, column: 7, scope: !221)
!546 = !DILocalVariable(name: "entry_name", scope: !221, file: !1, line: 567, type: !91)
!547 = !DILocation(line: 567, column: 24, scope: !221)
!548 = !DILocation(line: 569, column: 6, scope: !221)
!549 = !DILocation(line: 570, column: 17, scope: !221)
!550 = !DILocation(line: 571, column: 22, scope: !221)
!551 = !DILocation(line: 571, column: 25, scope: !221)
!552 = !DILocation(line: 571, column: 8, scope: !221)
!553 = !DILocation(line: 571, column: 6, scope: !221)
!554 = !DILocation(line: 574, column: 29, scope: !555)
!555 = distinct !DILexicalBlock(scope: !221, file: !1, line: 574, column: 6)
!556 = !DILocation(line: 574, column: 6, scope: !555)
!557 = !DILocation(line: 574, column: 45, scope: !555)
!558 = !DILocation(line: 574, column: 6, scope: !221)
!559 = !DILocation(line: 575, column: 22, scope: !560)
!560 = distinct !DILexicalBlock(scope: !555, file: !1, line: 574, column: 54)
!561 = !DILocation(line: 575, column: 25, scope: !560)
!562 = !DILocation(line: 575, column: 3, scope: !560)
!563 = !DILocation(line: 577, column: 3, scope: !560)
!564 = !DILocation(line: 583, column: 6, scope: !565)
!565 = distinct !DILexicalBlock(scope: !221, file: !1, line: 583, column: 6)
!566 = !DILocation(line: 583, column: 11, scope: !565)
!567 = !DILocation(line: 583, column: 6, scope: !221)
!568 = !DILocation(line: 584, column: 9, scope: !565)
!569 = !DILocation(line: 584, column: 3, scope: !565)
!570 = !DILocation(line: 587, column: 7, scope: !571)
!571 = distinct !DILexicalBlock(scope: !572, file: !1, line: 587, column: 7)
!572 = distinct !DILexicalBlock(scope: !565, file: !1, line: 585, column: 7)
!573 = !DILocation(line: 587, column: 12, scope: !571)
!574 = !DILocation(line: 587, column: 23, scope: !571)
!575 = !DILocation(line: 587, column: 7, scope: !572)
!576 = !DILocation(line: 591, column: 10, scope: !577)
!577 = distinct !DILexicalBlock(scope: !571, file: !1, line: 587, column: 32)
!578 = !DILocation(line: 591, column: 13, scope: !577)
!579 = !DILocation(line: 590, column: 22, scope: !577)
!580 = !DILocation(line: 590, column: 4, scope: !577)
!581 = !DILocation(line: 590, column: 9, scope: !577)
!582 = !DILocation(line: 590, column: 20, scope: !577)
!583 = !DILocation(line: 592, column: 8, scope: !584)
!584 = distinct !DILexicalBlock(scope: !577, file: !1, line: 592, column: 8)
!585 = !DILocation(line: 592, column: 13, scope: !584)
!586 = !DILocation(line: 592, column: 24, scope: !584)
!587 = !DILocation(line: 592, column: 8, scope: !577)
!588 = !DILocation(line: 594, column: 5, scope: !584)
!589 = !DILocation(line: 595, column: 3, scope: !577)
!590 = !DILocation(line: 596, column: 11, scope: !572)
!591 = !DILocation(line: 596, column: 16, scope: !572)
!592 = !DILocation(line: 596, column: 9, scope: !572)
!593 = !DILocation(line: 599, column: 25, scope: !221)
!594 = !DILocation(line: 599, column: 28, scope: !221)
!595 = !DILocation(line: 600, column: 24, scope: !221)
!596 = !DILocation(line: 599, column: 6, scope: !221)
!597 = !DILocation(line: 599, column: 4, scope: !221)
!598 = !DILocation(line: 601, column: 6, scope: !599)
!599 = distinct !DILexicalBlock(scope: !221, file: !1, line: 601, column: 6)
!600 = !DILocation(line: 601, column: 8, scope: !599)
!601 = !DILocation(line: 601, column: 6, scope: !221)
!602 = !DILocation(line: 602, column: 11, scope: !599)
!603 = !DILocation(line: 602, column: 3, scope: !599)
!604 = !DILocation(line: 603, column: 11, scope: !605)
!605 = distinct !DILexicalBlock(scope: !599, file: !1, line: 603, column: 11)
!606 = !DILocation(line: 603, column: 13, scope: !605)
!607 = !DILocation(line: 603, column: 11, scope: !599)
!608 = !DILocation(line: 604, column: 26, scope: !609)
!609 = distinct !DILexicalBlock(scope: !605, file: !1, line: 603, column: 28)
!610 = !DILocation(line: 604, column: 29, scope: !609)
!611 = !DILocation(line: 604, column: 7, scope: !609)
!612 = !DILocation(line: 604, column: 5, scope: !609)
!613 = !DILocation(line: 606, column: 7, scope: !614)
!614 = distinct !DILexicalBlock(scope: !609, file: !1, line: 606, column: 7)
!615 = !DILocation(line: 606, column: 9, scope: !614)
!616 = !DILocation(line: 606, column: 7, scope: !609)
!617 = !DILocation(line: 607, column: 12, scope: !614)
!618 = !DILocation(line: 607, column: 4, scope: !614)
!619 = !DILocation(line: 608, column: 22, scope: !609)
!620 = !DILocation(line: 608, column: 25, scope: !609)
!621 = !DILocation(line: 609, column: 46, scope: !609)
!622 = !DILocation(line: 610, column: 46, scope: !609)
!623 = !DILocation(line: 610, column: 7, scope: !609)
!624 = !DILocation(line: 608, column: 3, scope: !609)
!625 = !DILocation(line: 611, column: 7, scope: !609)
!626 = !DILocation(line: 612, column: 9, scope: !609)
!627 = !DILocation(line: 613, column: 2, scope: !609)
!628 = !DILocation(line: 616, column: 6, scope: !629)
!629 = distinct !DILexicalBlock(scope: !221, file: !1, line: 616, column: 6)
!630 = !DILocation(line: 616, column: 15, scope: !629)
!631 = !DILocation(line: 616, column: 6, scope: !221)
!632 = !DILocation(line: 617, column: 34, scope: !633)
!633 = distinct !DILexicalBlock(scope: !629, file: !1, line: 616, column: 24)
!634 = !DILocation(line: 617, column: 11, scope: !633)
!635 = !DILocation(line: 617, column: 3, scope: !633)
!636 = !DILocation(line: 623, column: 4, scope: !637)
!637 = distinct !DILexicalBlock(scope: !633, file: !1, line: 617, column: 51)
!638 = !DILocation(line: 657, column: 32, scope: !639)
!639 = distinct !DILexicalBlock(scope: !637, file: !1, line: 625, column: 3)
!640 = !DILocation(line: 657, column: 9, scope: !639)
!641 = !DILocation(line: 657, column: 7, scope: !639)
!642 = !DILocation(line: 663, column: 8, scope: !643)
!643 = distinct !DILexicalBlock(scope: !639, file: !1, line: 663, column: 8)
!644 = !DILocation(line: 663, column: 10, scope: !643)
!645 = !DILocation(line: 663, column: 18, scope: !643)
!646 = !DILocation(line: 663, column: 30, scope: !647)
!647 = !DILexicalBlockFile(scope: !643, file: !1, discriminator: 1)
!648 = !DILocation(line: 663, column: 23, scope: !647)
!649 = !DILocation(line: 663, column: 33, scope: !647)
!650 = !DILocation(line: 663, column: 21, scope: !647)
!651 = !DILocation(line: 663, column: 38, scope: !647)
!652 = !DILocation(line: 663, column: 8, scope: !647)
!653 = !DILocalVariable(name: "as", scope: !654, file: !1, line: 664, type: !91)
!654 = distinct !DILexicalBlock(scope: !643, file: !1, line: 663, column: 46)
!655 = !DILocation(line: 664, column: 27, scope: !654)
!656 = !DILocation(line: 666, column: 5, scope: !654)
!657 = !DILocation(line: 666, column: 5, scope: !658)
!658 = !DILexicalBlockFile(scope: !659, file: !1, discriminator: 1)
!659 = distinct !DILexicalBlock(scope: !654, file: !1, line: 666, column: 5)
!660 = !DILocation(line: 667, column: 26, scope: !654)
!661 = !DILocation(line: 667, column: 19, scope: !654)
!662 = !DILocation(line: 667, column: 17, scope: !654)
!663 = !DILocation(line: 669, column: 9, scope: !664)
!664 = distinct !DILexicalBlock(scope: !654, file: !1, line: 668, column: 9)
!665 = !DILocation(line: 669, column: 21, scope: !664)
!666 = !DILocation(line: 668, column: 9, scope: !664)
!667 = !DILocation(line: 669, column: 26, scope: !664)
!668 = !DILocation(line: 668, column: 9, scope: !654)
!669 = !DILocation(line: 670, column: 25, scope: !670)
!670 = distinct !DILexicalBlock(scope: !664, file: !1, line: 669, column: 35)
!671 = !DILocation(line: 670, column: 28, scope: !670)
!672 = !DILocation(line: 670, column: 6, scope: !670)
!673 = !DILocation(line: 672, column: 6, scope: !670)
!674 = !DILocation(line: 673, column: 6, scope: !670)
!675 = !DILocation(line: 684, column: 5, scope: !654)
!676 = !DILocation(line: 685, column: 5, scope: !654)
!677 = !DILocation(line: 687, column: 9, scope: !654)
!678 = !DILocation(line: 687, column: 28, scope: !654)
!679 = !DILocation(line: 686, column: 5, scope: !654)
!680 = !DILocation(line: 688, column: 5, scope: !654)
!681 = !DILocation(line: 689, column: 4, scope: !654)
!682 = !DILocation(line: 690, column: 4, scope: !639)
!683 = !DILocation(line: 693, column: 23, scope: !637)
!684 = !DILocation(line: 693, column: 26, scope: !637)
!685 = !DILocation(line: 693, column: 4, scope: !637)
!686 = !DILocation(line: 696, column: 4, scope: !637)
!687 = !DILocation(line: 698, column: 23, scope: !637)
!688 = !DILocation(line: 698, column: 26, scope: !637)
!689 = !DILocation(line: 702, column: 31, scope: !637)
!690 = !DILocation(line: 702, column: 8, scope: !637)
!691 = !DILocation(line: 701, column: 8, scope: !637)
!692 = !DILocation(line: 698, column: 4, scope: !637)
!693 = !DILocation(line: 703, column: 4, scope: !637)
!694 = !DILocation(line: 705, column: 2, scope: !633)
!695 = !DILocation(line: 721, column: 33, scope: !221)
!696 = !DILocation(line: 721, column: 6, scope: !221)
!697 = !DILocation(line: 720, column: 15, scope: !221)
!698 = !DILocation(line: 722, column: 6, scope: !699)
!699 = distinct !DILexicalBlock(scope: !221, file: !1, line: 722, column: 6)
!700 = !DILocation(line: 722, column: 19, scope: !699)
!701 = !DILocation(line: 722, column: 6, scope: !221)
!702 = !DILocalVariable(name: "oname", scope: !703, file: !1, line: 723, type: !80)
!703 = distinct !DILexicalBlock(scope: !699, file: !1, line: 722, column: 28)
!704 = !DILocation(line: 723, column: 15, scope: !703)
!705 = !DILocalVariable(name: "name", scope: !703, file: !1, line: 724, type: !95)
!706 = !DILocation(line: 724, column: 9, scope: !703)
!707 = !DILocalVariable(name: "bname", scope: !703, file: !1, line: 724, type: !95)
!708 = !DILocation(line: 724, column: 16, scope: !703)
!709 = !DILocalVariable(name: "name_length", scope: !703, file: !1, line: 725, type: !45)
!710 = !DILocation(line: 725, column: 10, scope: !703)
!711 = !DILocalVariable(name: "extra", scope: !703, file: !1, line: 726, type: !30)
!712 = !DILocation(line: 726, column: 25, scope: !703)
!713 = !DILocation(line: 726, column: 53, scope: !703)
!714 = !DILocation(line: 726, column: 56, scope: !703)
!715 = !DILocation(line: 726, column: 33, scope: !703)
!716 = !DILocation(line: 728, column: 34, scope: !703)
!717 = !DILocation(line: 728, column: 11, scope: !703)
!718 = !DILocation(line: 728, column: 9, scope: !703)
!719 = !DILocation(line: 729, column: 24, scope: !703)
!720 = !DILocation(line: 729, column: 17, scope: !703)
!721 = !DILocation(line: 729, column: 15, scope: !703)
!722 = !DILocation(line: 730, column: 17, scope: !703)
!723 = !DILocation(line: 730, column: 29, scope: !703)
!724 = !DILocation(line: 730, column: 10, scope: !703)
!725 = !DILocation(line: 730, column: 8, scope: !703)
!726 = !DILocation(line: 731, column: 7, scope: !727)
!727 = distinct !DILexicalBlock(scope: !703, file: !1, line: 731, column: 7)
!728 = !DILocation(line: 731, column: 12, scope: !727)
!729 = !DILocation(line: 731, column: 20, scope: !727)
!730 = !DILocation(line: 731, column: 23, scope: !731)
!731 = !DILexicalBlockFile(scope: !727, file: !1, discriminator: 1)
!732 = !DILocation(line: 731, column: 29, scope: !731)
!733 = !DILocation(line: 731, column: 7, scope: !731)
!734 = !DILocation(line: 733, column: 23, scope: !735)
!735 = distinct !DILexicalBlock(scope: !727, file: !1, line: 731, column: 38)
!736 = !DILocation(line: 733, column: 4, scope: !735)
!737 = !DILocation(line: 734, column: 9, scope: !735)
!738 = !DILocation(line: 734, column: 4, scope: !735)
!739 = !DILocation(line: 735, column: 4, scope: !735)
!740 = !DILocation(line: 737, column: 10, scope: !703)
!741 = !DILocation(line: 737, column: 16, scope: !703)
!742 = !DILocation(line: 737, column: 3, scope: !703)
!743 = !DILocation(line: 739, column: 19, scope: !703)
!744 = !DILocation(line: 739, column: 11, scope: !703)
!745 = !DILocation(line: 739, column: 9, scope: !703)
!746 = !DILocation(line: 740, column: 3, scope: !703)
!747 = !DILocation(line: 740, column: 10, scope: !748)
!748 = !DILexicalBlockFile(scope: !703, file: !1, discriminator: 1)
!749 = !DILocation(line: 740, column: 16, scope: !748)
!750 = !DILocation(line: 740, column: 24, scope: !748)
!751 = !DILocation(line: 740, column: 27, scope: !752)
!752 = !DILexicalBlockFile(scope: !703, file: !1, discriminator: 2)
!753 = !DILocation(line: 740, column: 36, scope: !752)
!754 = !DILocation(line: 740, column: 3, scope: !755)
!755 = !DILexicalBlockFile(scope: !703, file: !1, discriminator: 3)
!756 = !DILocation(line: 741, column: 5, scope: !757)
!757 = distinct !DILexicalBlock(scope: !703, file: !1, line: 740, column: 45)
!758 = !DILocation(line: 741, column: 11, scope: !757)
!759 = !DILocation(line: 742, column: 20, scope: !757)
!760 = !DILocation(line: 742, column: 12, scope: !757)
!761 = !DILocation(line: 742, column: 10, scope: !757)
!762 = !DILocation(line: 740, column: 3, scope: !763)
!763 = !DILexicalBlockFile(scope: !703, file: !1, discriminator: 4)
!764 = !DILocation(line: 744, column: 7, scope: !765)
!765 = distinct !DILexicalBlock(scope: !703, file: !1, line: 744, column: 7)
!766 = !DILocation(line: 744, column: 13, scope: !765)
!767 = !DILocation(line: 744, column: 7, scope: !703)
!768 = !DILocation(line: 745, column: 12, scope: !769)
!769 = distinct !DILexicalBlock(scope: !765, file: !1, line: 744, column: 22)
!770 = !DILocation(line: 745, column: 17, scope: !769)
!771 = !DILocation(line: 745, column: 22, scope: !769)
!772 = !DILocation(line: 745, column: 28, scope: !769)
!773 = !DILocation(line: 745, column: 40, scope: !769)
!774 = !DILocation(line: 745, column: 4, scope: !769)
!775 = !DILocation(line: 746, column: 12, scope: !769)
!776 = !DILocation(line: 746, column: 4, scope: !769)
!777 = !DILocation(line: 747, column: 3, scope: !769)
!778 = !DILocation(line: 748, column: 10, scope: !779)
!779 = distinct !DILexicalBlock(scope: !765, file: !1, line: 747, column: 10)
!780 = !DILocation(line: 749, column: 12, scope: !779)
!781 = !DILocation(line: 749, column: 18, scope: !779)
!782 = !DILocation(line: 749, column: 23, scope: !779)
!783 = !DILocation(line: 749, column: 37, scope: !779)
!784 = !DILocation(line: 749, column: 30, scope: !779)
!785 = !DILocation(line: 749, column: 44, scope: !779)
!786 = !DILocation(line: 749, column: 4, scope: !787)
!787 = !DILexicalBlockFile(scope: !779, file: !1, discriminator: 1)
!788 = !DILocation(line: 750, column: 12, scope: !779)
!789 = !DILocation(line: 750, column: 4, scope: !779)
!790 = !DILocation(line: 752, column: 31, scope: !703)
!791 = !DILocation(line: 752, column: 38, scope: !703)
!792 = !DILocation(line: 752, column: 3, scope: !703)
!793 = !DILocation(line: 753, column: 8, scope: !703)
!794 = !DILocation(line: 753, column: 3, scope: !703)
!795 = !DILocation(line: 755, column: 26, scope: !703)
!796 = !DILocation(line: 755, column: 33, scope: !703)
!797 = !DILocation(line: 755, column: 3, scope: !703)
!798 = !DILocation(line: 756, column: 30, scope: !703)
!799 = !DILocation(line: 756, column: 3, scope: !703)
!800 = !DILocation(line: 757, column: 26, scope: !703)
!801 = !DILocation(line: 758, column: 26, scope: !703)
!802 = !DILocation(line: 758, column: 7, scope: !703)
!803 = !DILocation(line: 757, column: 3, scope: !703)
!804 = !DILocation(line: 759, column: 27, scope: !703)
!805 = !DILocation(line: 760, column: 27, scope: !703)
!806 = !DILocation(line: 760, column: 7, scope: !703)
!807 = !DILocation(line: 761, column: 32, scope: !703)
!808 = !DILocation(line: 761, column: 7, scope: !703)
!809 = !DILocation(line: 759, column: 3, scope: !703)
!810 = !DILocation(line: 762, column: 25, scope: !703)
!811 = !DILocation(line: 763, column: 25, scope: !703)
!812 = !DILocation(line: 763, column: 7, scope: !703)
!813 = !DILocation(line: 762, column: 3, scope: !703)
!814 = !DILocation(line: 764, column: 27, scope: !703)
!815 = !DILocation(line: 765, column: 27, scope: !703)
!816 = !DILocation(line: 765, column: 7, scope: !703)
!817 = !DILocation(line: 764, column: 3, scope: !703)
!818 = !DILocation(line: 766, column: 25, scope: !703)
!819 = !DILocation(line: 767, column: 25, scope: !703)
!820 = !DILocation(line: 767, column: 7, scope: !703)
!821 = !DILocation(line: 766, column: 3, scope: !703)
!822 = !DILocation(line: 768, column: 27, scope: !703)
!823 = !DILocation(line: 769, column: 27, scope: !703)
!824 = !DILocation(line: 769, column: 7, scope: !703)
!825 = !DILocation(line: 768, column: 3, scope: !703)
!826 = !DILocation(line: 772, column: 32, scope: !703)
!827 = !DILocation(line: 772, column: 35, scope: !703)
!828 = !DILocation(line: 772, column: 7, scope: !703)
!829 = !DILocation(line: 772, column: 5, scope: !703)
!830 = !DILocation(line: 773, column: 22, scope: !703)
!831 = !DILocation(line: 773, column: 3, scope: !703)
!832 = !DILocation(line: 774, column: 7, scope: !833)
!833 = distinct !DILexicalBlock(scope: !703, file: !1, line: 774, column: 7)
!834 = !DILocation(line: 774, column: 9, scope: !833)
!835 = !DILocation(line: 774, column: 7, scope: !703)
!836 = !DILocation(line: 775, column: 12, scope: !833)
!837 = !DILocation(line: 775, column: 4, scope: !833)
!838 = !DILocation(line: 776, column: 7, scope: !839)
!839 = distinct !DILexicalBlock(scope: !703, file: !1, line: 776, column: 7)
!840 = !DILocation(line: 776, column: 11, scope: !839)
!841 = !DILocation(line: 776, column: 9, scope: !839)
!842 = !DILocation(line: 776, column: 7, scope: !703)
!843 = !DILocation(line: 777, column: 10, scope: !839)
!844 = !DILocation(line: 777, column: 8, scope: !839)
!845 = !DILocation(line: 777, column: 4, scope: !839)
!846 = !DILocation(line: 778, column: 35, scope: !703)
!847 = !DILocation(line: 778, column: 38, scope: !703)
!848 = !DILocation(line: 779, column: 7, scope: !703)
!849 = !DILocation(line: 778, column: 12, scope: !703)
!850 = !DILocation(line: 778, column: 7, scope: !703)
!851 = !DILocation(line: 778, column: 5, scope: !703)
!852 = !DILocation(line: 780, column: 7, scope: !853)
!853 = distinct !DILexicalBlock(scope: !703, file: !1, line: 780, column: 7)
!854 = !DILocation(line: 780, column: 9, scope: !853)
!855 = !DILocation(line: 780, column: 7, scope: !703)
!856 = !DILocation(line: 781, column: 12, scope: !853)
!857 = !DILocation(line: 781, column: 4, scope: !853)
!858 = !DILocation(line: 782, column: 7, scope: !859)
!859 = distinct !DILexicalBlock(scope: !703, file: !1, line: 782, column: 7)
!860 = !DILocation(line: 782, column: 11, scope: !859)
!861 = !DILocation(line: 782, column: 9, scope: !859)
!862 = !DILocation(line: 782, column: 7, scope: !703)
!863 = !DILocation(line: 783, column: 10, scope: !859)
!864 = !DILocation(line: 783, column: 8, scope: !859)
!865 = !DILocation(line: 783, column: 4, scope: !859)
!866 = !DILocation(line: 784, column: 38, scope: !703)
!867 = !DILocation(line: 784, column: 7, scope: !703)
!868 = !DILocation(line: 784, column: 5, scope: !703)
!869 = !DILocation(line: 785, column: 7, scope: !870)
!870 = distinct !DILexicalBlock(scope: !703, file: !1, line: 785, column: 7)
!871 = !DILocation(line: 785, column: 9, scope: !870)
!872 = !DILocation(line: 785, column: 7, scope: !703)
!873 = !DILocation(line: 786, column: 12, scope: !870)
!874 = !DILocation(line: 786, column: 4, scope: !870)
!875 = !DILocation(line: 787, column: 7, scope: !876)
!876 = distinct !DILexicalBlock(scope: !703, file: !1, line: 787, column: 7)
!877 = !DILocation(line: 787, column: 11, scope: !876)
!878 = !DILocation(line: 787, column: 9, scope: !876)
!879 = !DILocation(line: 787, column: 7, scope: !703)
!880 = !DILocation(line: 788, column: 10, scope: !876)
!881 = !DILocation(line: 788, column: 8, scope: !876)
!882 = !DILocation(line: 788, column: 4, scope: !876)
!883 = !DILocation(line: 789, column: 2, scope: !703)
!884 = !DILocation(line: 799, column: 35, scope: !221)
!885 = !DILocation(line: 799, column: 15, scope: !221)
!886 = !DILocation(line: 799, column: 13, scope: !221)
!887 = !DILocation(line: 801, column: 6, scope: !888)
!888 = distinct !DILexicalBlock(scope: !221, file: !1, line: 801, column: 6)
!889 = !DILocation(line: 801, column: 17, scope: !888)
!890 = !DILocation(line: 801, column: 6, scope: !221)
!891 = !DILocation(line: 802, column: 22, scope: !892)
!892 = distinct !DILexicalBlock(scope: !888, file: !1, line: 801, column: 26)
!893 = !DILocation(line: 802, column: 25, scope: !892)
!894 = !DILocation(line: 802, column: 3, scope: !892)
!895 = !DILocation(line: 804, column: 3, scope: !892)
!896 = !DILocation(line: 806, column: 2, scope: !221)
!897 = !DILocation(line: 807, column: 2, scope: !221)
!898 = !DILocation(line: 808, column: 15, scope: !221)
!899 = !DILocation(line: 809, column: 20, scope: !221)
!900 = !DILocation(line: 809, column: 2, scope: !221)
!901 = !DILocation(line: 811, column: 6, scope: !902)
!902 = distinct !DILexicalBlock(scope: !221, file: !1, line: 811, column: 6)
!903 = !DILocation(line: 811, column: 15, scope: !902)
!904 = !DILocation(line: 811, column: 23, scope: !902)
!905 = !DILocation(line: 812, column: 29, scope: !902)
!906 = !DILocation(line: 812, column: 6, scope: !902)
!907 = !DILocation(line: 812, column: 41, scope: !902)
!908 = !DILocation(line: 811, column: 6, scope: !909)
!909 = !DILexicalBlockFile(scope: !221, file: !1, discriminator: 1)
!910 = !DILocation(line: 813, column: 45, scope: !902)
!911 = !DILocation(line: 813, column: 18, scope: !902)
!912 = !DILocation(line: 813, column: 16, scope: !902)
!913 = !DILocation(line: 813, column: 3, scope: !902)
!914 = !DILocation(line: 815, column: 16, scope: !902)
!915 = !DILocation(line: 816, column: 6, scope: !916)
!916 = distinct !DILexicalBlock(scope: !221, file: !1, line: 816, column: 6)
!917 = !DILocation(line: 816, column: 6, scope: !221)
!918 = !DILocalVariable(name: "offset", scope: !919, file: !1, line: 817, type: !52)
!919 = distinct !DILexicalBlock(scope: !916, file: !1, line: 816, column: 20)
!920 = !DILocation(line: 817, column: 11, scope: !919)
!921 = !DILocalVariable(name: "length", scope: !919, file: !1, line: 817, type: !52)
!922 = !DILocation(line: 817, column: 19, scope: !919)
!923 = !DILocalVariable(name: "last_offset", scope: !919, file: !1, line: 817, type: !52)
!924 = !DILocation(line: 817, column: 27, scope: !919)
!925 = !DILocation(line: 819, column: 3, scope: !919)
!926 = !DILocation(line: 820, column: 7, scope: !919)
!927 = !DILocation(line: 819, column: 10, scope: !928)
!928 = !DILexicalBlockFile(scope: !919, file: !1, discriminator: 1)
!929 = !DILocation(line: 820, column: 37, scope: !919)
!930 = !DILocation(line: 819, column: 3, scope: !928)
!931 = !DILocation(line: 821, column: 18, scope: !919)
!932 = !DILocation(line: 821, column: 27, scope: !919)
!933 = !DILocation(line: 821, column: 25, scope: !919)
!934 = !DILocation(line: 821, column: 16, scope: !919)
!935 = !DILocation(line: 819, column: 3, scope: !936)
!936 = !DILexicalBlockFile(scope: !919, file: !1, discriminator: 2)
!937 = !DILocation(line: 826, column: 7, scope: !938)
!938 = distinct !DILexicalBlock(scope: !919, file: !1, line: 826, column: 7)
!939 = !DILocation(line: 826, column: 40, scope: !938)
!940 = !DILocation(line: 826, column: 21, scope: !938)
!941 = !DILocation(line: 826, column: 19, scope: !938)
!942 = !DILocation(line: 826, column: 7, scope: !919)
!943 = !DILocation(line: 827, column: 35, scope: !938)
!944 = !DILocation(line: 828, column: 27, scope: !938)
!945 = !DILocation(line: 828, column: 8, scope: !938)
!946 = !DILocation(line: 827, column: 4, scope: !938)
!947 = !DILocation(line: 829, column: 45, scope: !919)
!948 = !DILocation(line: 829, column: 18, scope: !919)
!949 = !DILocation(line: 829, column: 16, scope: !919)
!950 = !DILocation(line: 830, column: 2, scope: !919)
!951 = !DILocation(line: 837, column: 25, scope: !221)
!952 = !DILocation(line: 837, column: 28, scope: !221)
!953 = !DILocation(line: 837, column: 61, scope: !221)
!954 = !DILocation(line: 837, column: 6, scope: !221)
!955 = !DILocation(line: 837, column: 4, scope: !221)
!956 = !DILocation(line: 838, column: 6, scope: !957)
!957 = distinct !DILexicalBlock(scope: !221, file: !1, line: 838, column: 6)
!958 = !DILocation(line: 838, column: 8, scope: !957)
!959 = !DILocation(line: 838, column: 6, scope: !221)
!960 = !DILocation(line: 839, column: 11, scope: !957)
!961 = !DILocation(line: 839, column: 3, scope: !957)
!962 = !DILocation(line: 840, column: 11, scope: !963)
!963 = distinct !DILexicalBlock(scope: !957, file: !1, line: 840, column: 11)
!964 = !DILocation(line: 840, column: 13, scope: !963)
!965 = !DILocation(line: 840, column: 11, scope: !957)
!966 = !DILocation(line: 841, column: 26, scope: !967)
!967 = distinct !DILexicalBlock(scope: !963, file: !1, line: 840, column: 28)
!968 = !DILocation(line: 841, column: 29, scope: !967)
!969 = !DILocation(line: 841, column: 7, scope: !967)
!970 = !DILocation(line: 841, column: 5, scope: !967)
!971 = !DILocation(line: 843, column: 7, scope: !972)
!972 = distinct !DILexicalBlock(scope: !967, file: !1, line: 843, column: 7)
!973 = !DILocation(line: 843, column: 9, scope: !972)
!974 = !DILocation(line: 843, column: 7, scope: !967)
!975 = !DILocation(line: 844, column: 12, scope: !972)
!976 = !DILocation(line: 844, column: 4, scope: !972)
!977 = !DILocation(line: 845, column: 22, scope: !967)
!978 = !DILocation(line: 845, column: 25, scope: !967)
!979 = !DILocation(line: 846, column: 46, scope: !967)
!980 = !DILocation(line: 847, column: 46, scope: !967)
!981 = !DILocation(line: 847, column: 7, scope: !967)
!982 = !DILocation(line: 845, column: 3, scope: !967)
!983 = !DILocation(line: 848, column: 7, scope: !967)
!984 = !DILocation(line: 849, column: 9, scope: !967)
!985 = !DILocation(line: 850, column: 2, scope: !967)
!986 = !DILocation(line: 851, column: 22, scope: !221)
!987 = !DILocation(line: 851, column: 25, scope: !221)
!988 = !DILocation(line: 851, column: 60, scope: !221)
!989 = !DILocation(line: 851, column: 6, scope: !221)
!990 = !DILocation(line: 851, column: 4, scope: !221)
!991 = !DILocation(line: 852, column: 6, scope: !992)
!992 = distinct !DILexicalBlock(scope: !221, file: !1, line: 852, column: 6)
!993 = !DILocation(line: 852, column: 8, scope: !992)
!994 = !DILocation(line: 852, column: 6, scope: !221)
!995 = !DILocation(line: 853, column: 11, scope: !992)
!996 = !DILocation(line: 853, column: 3, scope: !992)
!997 = !DILocation(line: 854, column: 11, scope: !998)
!998 = distinct !DILexicalBlock(scope: !992, file: !1, line: 854, column: 11)
!999 = !DILocation(line: 854, column: 13, scope: !998)
!1000 = !DILocation(line: 854, column: 11, scope: !992)
!1001 = !DILocation(line: 855, column: 23, scope: !1002)
!1002 = distinct !DILexicalBlock(scope: !998, file: !1, line: 854, column: 28)
!1003 = !DILocation(line: 855, column: 26, scope: !1002)
!1004 = !DILocation(line: 855, column: 7, scope: !1002)
!1005 = !DILocation(line: 855, column: 5, scope: !1002)
!1006 = !DILocation(line: 856, column: 7, scope: !1007)
!1007 = distinct !DILexicalBlock(scope: !1002, file: !1, line: 856, column: 7)
!1008 = !DILocation(line: 856, column: 9, scope: !1007)
!1009 = !DILocation(line: 856, column: 7, scope: !1002)
!1010 = !DILocation(line: 857, column: 12, scope: !1007)
!1011 = !DILocation(line: 857, column: 4, scope: !1007)
!1012 = !DILocation(line: 858, column: 22, scope: !1002)
!1013 = !DILocation(line: 858, column: 25, scope: !1002)
!1014 = !DILocation(line: 859, column: 43, scope: !1002)
!1015 = !DILocation(line: 860, column: 46, scope: !1002)
!1016 = !DILocation(line: 860, column: 7, scope: !1002)
!1017 = !DILocation(line: 858, column: 3, scope: !1002)
!1018 = !DILocation(line: 861, column: 7, scope: !1002)
!1019 = !DILocation(line: 862, column: 9, scope: !1002)
!1020 = !DILocation(line: 863, column: 2, scope: !1002)
!1021 = !DILocation(line: 864, column: 22, scope: !221)
!1022 = !DILocation(line: 864, column: 25, scope: !221)
!1023 = !DILocation(line: 864, column: 60, scope: !221)
!1024 = !DILocation(line: 864, column: 6, scope: !221)
!1025 = !DILocation(line: 864, column: 4, scope: !221)
!1026 = !DILocation(line: 865, column: 6, scope: !1027)
!1027 = distinct !DILexicalBlock(scope: !221, file: !1, line: 865, column: 6)
!1028 = !DILocation(line: 865, column: 8, scope: !1027)
!1029 = !DILocation(line: 865, column: 6, scope: !221)
!1030 = !DILocation(line: 866, column: 11, scope: !1027)
!1031 = !DILocation(line: 866, column: 3, scope: !1027)
!1032 = !DILocation(line: 867, column: 11, scope: !1033)
!1033 = distinct !DILexicalBlock(scope: !1027, file: !1, line: 867, column: 11)
!1034 = !DILocation(line: 867, column: 13, scope: !1033)
!1035 = !DILocation(line: 867, column: 11, scope: !1027)
!1036 = !DILocation(line: 868, column: 23, scope: !1037)
!1037 = distinct !DILexicalBlock(scope: !1033, file: !1, line: 867, column: 28)
!1038 = !DILocation(line: 868, column: 26, scope: !1037)
!1039 = !DILocation(line: 868, column: 7, scope: !1037)
!1040 = !DILocation(line: 868, column: 5, scope: !1037)
!1041 = !DILocation(line: 869, column: 7, scope: !1042)
!1042 = distinct !DILexicalBlock(scope: !1037, file: !1, line: 869, column: 7)
!1043 = !DILocation(line: 869, column: 9, scope: !1042)
!1044 = !DILocation(line: 869, column: 7, scope: !1037)
!1045 = !DILocation(line: 870, column: 12, scope: !1042)
!1046 = !DILocation(line: 870, column: 4, scope: !1042)
!1047 = !DILocation(line: 871, column: 22, scope: !1037)
!1048 = !DILocation(line: 871, column: 25, scope: !1037)
!1049 = !DILocation(line: 872, column: 43, scope: !1037)
!1050 = !DILocation(line: 873, column: 46, scope: !1037)
!1051 = !DILocation(line: 873, column: 7, scope: !1037)
!1052 = !DILocation(line: 871, column: 3, scope: !1037)
!1053 = !DILocation(line: 874, column: 7, scope: !1037)
!1054 = !DILocation(line: 875, column: 9, scope: !1037)
!1055 = !DILocation(line: 876, column: 2, scope: !1037)
!1056 = !DILocation(line: 877, column: 13, scope: !221)
!1057 = !DILocation(line: 877, column: 11, scope: !221)
!1058 = !DILocation(line: 878, column: 20, scope: !221)
!1059 = !DILocation(line: 878, column: 18, scope: !221)
!1060 = !DILocation(line: 879, column: 6, scope: !1061)
!1061 = distinct !DILexicalBlock(scope: !221, file: !1, line: 879, column: 6)
!1062 = !DILocation(line: 879, column: 15, scope: !1061)
!1063 = !DILocation(line: 879, column: 6, scope: !221)
!1064 = !DILocation(line: 880, column: 25, scope: !1065)
!1065 = distinct !DILexicalBlock(scope: !1061, file: !1, line: 879, column: 24)
!1066 = !DILocation(line: 880, column: 28, scope: !1065)
!1067 = !DILocation(line: 881, column: 25, scope: !1065)
!1068 = !DILocation(line: 880, column: 7, scope: !1065)
!1069 = !DILocation(line: 880, column: 5, scope: !1065)
!1070 = !DILocation(line: 882, column: 7, scope: !1071)
!1071 = distinct !DILexicalBlock(scope: !1065, file: !1, line: 882, column: 7)
!1072 = !DILocation(line: 882, column: 9, scope: !1071)
!1073 = !DILocation(line: 882, column: 7, scope: !1065)
!1074 = !DILocation(line: 883, column: 12, scope: !1071)
!1075 = !DILocation(line: 883, column: 4, scope: !1071)
!1076 = !DILocation(line: 884, column: 12, scope: !1077)
!1077 = distinct !DILexicalBlock(scope: !1071, file: !1, line: 884, column: 12)
!1078 = !DILocation(line: 884, column: 14, scope: !1077)
!1079 = !DILocation(line: 884, column: 12, scope: !1071)
!1080 = !DILocation(line: 885, column: 26, scope: !1081)
!1081 = distinct !DILexicalBlock(scope: !1077, file: !1, line: 884, column: 29)
!1082 = !DILocation(line: 885, column: 29, scope: !1081)
!1083 = !DILocation(line: 885, column: 8, scope: !1081)
!1084 = !DILocation(line: 885, column: 6, scope: !1081)
!1085 = !DILocation(line: 887, column: 8, scope: !1086)
!1086 = distinct !DILexicalBlock(scope: !1081, file: !1, line: 887, column: 8)
!1087 = !DILocation(line: 887, column: 10, scope: !1086)
!1088 = !DILocation(line: 887, column: 8, scope: !1081)
!1089 = !DILocation(line: 888, column: 13, scope: !1086)
!1090 = !DILocation(line: 888, column: 5, scope: !1086)
!1091 = !DILocation(line: 889, column: 23, scope: !1081)
!1092 = !DILocation(line: 889, column: 26, scope: !1081)
!1093 = !DILocation(line: 891, column: 47, scope: !1081)
!1094 = !DILocation(line: 892, column: 47, scope: !1081)
!1095 = !DILocation(line: 892, column: 8, scope: !1081)
!1096 = !DILocation(line: 889, column: 4, scope: !1081)
!1097 = !DILocation(line: 893, column: 8, scope: !1081)
!1098 = !DILocation(line: 894, column: 10, scope: !1081)
!1099 = !DILocation(line: 895, column: 3, scope: !1081)
!1100 = !DILocation(line: 896, column: 2, scope: !1065)
!1101 = !DILocation(line: 900, column: 6, scope: !1102)
!1102 = distinct !DILexicalBlock(scope: !221, file: !1, line: 900, column: 6)
!1103 = !DILocation(line: 900, column: 12, scope: !1102)
!1104 = !DILocation(line: 900, column: 20, scope: !1102)
!1105 = !DILocation(line: 900, column: 24, scope: !1106)
!1106 = !DILexicalBlockFile(scope: !1102, file: !1, discriminator: 1)
!1107 = !DILocation(line: 900, column: 29, scope: !1106)
!1108 = !DILocation(line: 900, column: 6, scope: !1106)
!1109 = !DILocation(line: 901, column: 7, scope: !1110)
!1110 = distinct !DILexicalBlock(scope: !1111, file: !1, line: 901, column: 7)
!1111 = distinct !DILexicalBlock(scope: !1102, file: !1, line: 900, column: 41)
!1112 = !DILocation(line: 901, column: 16, scope: !1110)
!1113 = !DILocation(line: 901, column: 7, scope: !1111)
!1114 = !DILocation(line: 902, column: 27, scope: !1115)
!1115 = distinct !DILexicalBlock(scope: !1110, file: !1, line: 901, column: 25)
!1116 = !DILocation(line: 902, column: 30, scope: !1115)
!1117 = !DILocation(line: 902, column: 8, scope: !1115)
!1118 = !DILocation(line: 902, column: 6, scope: !1115)
!1119 = !DILocation(line: 904, column: 8, scope: !1120)
!1120 = distinct !DILexicalBlock(scope: !1115, file: !1, line: 904, column: 8)
!1121 = !DILocation(line: 904, column: 10, scope: !1120)
!1122 = !DILocation(line: 904, column: 8, scope: !1115)
!1123 = !DILocation(line: 905, column: 13, scope: !1120)
!1124 = !DILocation(line: 905, column: 5, scope: !1120)
!1125 = !DILocation(line: 906, column: 15, scope: !1115)
!1126 = !DILocation(line: 906, column: 13, scope: !1115)
!1127 = !DILocation(line: 907, column: 22, scope: !1115)
!1128 = !DILocation(line: 907, column: 20, scope: !1115)
!1129 = !DILocation(line: 908, column: 3, scope: !1115)
!1130 = !DILocation(line: 909, column: 26, scope: !1111)
!1131 = !DILocation(line: 909, column: 29, scope: !1111)
!1132 = !DILocation(line: 909, column: 7, scope: !1111)
!1133 = !DILocation(line: 909, column: 5, scope: !1111)
!1134 = !DILocation(line: 911, column: 7, scope: !1135)
!1135 = distinct !DILexicalBlock(scope: !1111, file: !1, line: 911, column: 7)
!1136 = !DILocation(line: 911, column: 9, scope: !1135)
!1137 = !DILocation(line: 911, column: 7, scope: !1111)
!1138 = !DILocation(line: 912, column: 12, scope: !1135)
!1139 = !DILocation(line: 912, column: 4, scope: !1135)
!1140 = !DILocation(line: 913, column: 23, scope: !1111)
!1141 = !DILocation(line: 913, column: 26, scope: !1111)
!1142 = !DILocation(line: 913, column: 7, scope: !1111)
!1143 = !DILocation(line: 913, column: 5, scope: !1111)
!1144 = !DILocation(line: 914, column: 7, scope: !1145)
!1145 = distinct !DILexicalBlock(scope: !1111, file: !1, line: 914, column: 7)
!1146 = !DILocation(line: 914, column: 9, scope: !1145)
!1147 = !DILocation(line: 914, column: 7, scope: !1111)
!1148 = !DILocation(line: 915, column: 12, scope: !1145)
!1149 = !DILocation(line: 915, column: 4, scope: !1145)
!1150 = !DILocation(line: 916, column: 23, scope: !1111)
!1151 = !DILocation(line: 916, column: 26, scope: !1111)
!1152 = !DILocation(line: 916, column: 7, scope: !1111)
!1153 = !DILocation(line: 916, column: 5, scope: !1111)
!1154 = !DILocation(line: 917, column: 7, scope: !1155)
!1155 = distinct !DILexicalBlock(scope: !1111, file: !1, line: 917, column: 7)
!1156 = !DILocation(line: 917, column: 9, scope: !1155)
!1157 = !DILocation(line: 917, column: 7, scope: !1111)
!1158 = !DILocation(line: 918, column: 12, scope: !1155)
!1159 = !DILocation(line: 918, column: 4, scope: !1155)
!1160 = !DILocation(line: 919, column: 2, scope: !1111)
!1161 = !DILocation(line: 922, column: 6, scope: !1162)
!1162 = distinct !DILexicalBlock(scope: !221, file: !1, line: 922, column: 6)
!1163 = !DILocation(line: 922, column: 12, scope: !1162)
!1164 = !DILocation(line: 922, column: 6, scope: !221)
!1165 = !DILocation(line: 923, column: 18, scope: !1162)
!1166 = !DILocation(line: 923, column: 23, scope: !1162)
!1167 = !DILocation(line: 923, column: 3, scope: !1162)
!1168 = !DILocation(line: 931, column: 20, scope: !1169)
!1169 = distinct !DILexicalBlock(scope: !221, file: !1, line: 931, column: 6)
!1170 = !DILocation(line: 931, column: 6, scope: !1169)
!1171 = !DILocation(line: 931, column: 6, scope: !221)
!1172 = !DILocation(line: 933, column: 18, scope: !1173)
!1173 = distinct !DILexicalBlock(scope: !1169, file: !1, line: 931, column: 27)
!1174 = !DILocation(line: 933, column: 23, scope: !1173)
!1175 = !DILocation(line: 933, column: 44, scope: !1173)
!1176 = !DILocation(line: 933, column: 3, scope: !1173)
!1177 = !DILocation(line: 934, column: 30, scope: !1173)
!1178 = !DILocation(line: 935, column: 30, scope: !1173)
!1179 = !DILocation(line: 936, column: 4, scope: !1173)
!1180 = !DILocation(line: 936, column: 10, scope: !1173)
!1181 = !DILocation(line: 935, column: 7, scope: !1173)
!1182 = !DILocation(line: 934, column: 3, scope: !1173)
!1183 = !DILocation(line: 937, column: 18, scope: !1173)
!1184 = !DILocation(line: 938, column: 2, scope: !1173)
!1185 = !DILocation(line: 944, column: 7, scope: !1186)
!1186 = distinct !DILexicalBlock(scope: !1187, file: !1, line: 944, column: 7)
!1187 = distinct !DILexicalBlock(scope: !1169, file: !1, line: 938, column: 9)
!1188 = !DILocation(line: 944, column: 19, scope: !1186)
!1189 = !DILocation(line: 944, column: 7, scope: !1187)
!1190 = !DILocation(line: 946, column: 3, scope: !1191)
!1191 = distinct !DILexicalBlock(scope: !1186, file: !1, line: 944, column: 27)
!1192 = !DILocation(line: 949, column: 20, scope: !1193)
!1193 = distinct !DILexicalBlock(scope: !1186, file: !1, line: 946, column: 10)
!1194 = !DILocation(line: 949, column: 27, scope: !1193)
!1195 = !DILocation(line: 949, column: 25, scope: !1193)
!1196 = !DILocation(line: 949, column: 39, scope: !1193)
!1197 = !DILocation(line: 949, column: 45, scope: !1193)
!1198 = !DILocation(line: 949, column: 13, scope: !1193)
!1199 = !DILocation(line: 949, column: 11, scope: !1193)
!1200 = !DILocation(line: 951, column: 8, scope: !1201)
!1201 = distinct !DILexicalBlock(scope: !1193, file: !1, line: 951, column: 8)
!1202 = !DILocation(line: 951, column: 18, scope: !1201)
!1203 = !DILocation(line: 951, column: 15, scope: !1201)
!1204 = !DILocation(line: 951, column: 8, scope: !1193)
!1205 = !DILocation(line: 952, column: 21, scope: !1201)
!1206 = !DILocation(line: 952, column: 28, scope: !1201)
!1207 = !DILocation(line: 952, column: 14, scope: !1201)
!1208 = !DILocation(line: 952, column: 12, scope: !1201)
!1209 = !DILocation(line: 952, column: 5, scope: !1201)
!1210 = !DILocation(line: 960, column: 8, scope: !1211)
!1211 = distinct !DILexicalBlock(scope: !1193, file: !1, line: 960, column: 8)
!1212 = !DILocation(line: 960, column: 15, scope: !1211)
!1213 = !DILocation(line: 961, column: 8, scope: !1211)
!1214 = !DILocation(line: 961, column: 11, scope: !1215)
!1215 = !DILexicalBlockFile(scope: !1211, file: !1, discriminator: 1)
!1216 = !DILocation(line: 961, column: 21, scope: !1215)
!1217 = !DILocation(line: 962, column: 8, scope: !1211)
!1218 = !DILocation(line: 962, column: 11, scope: !1215)
!1219 = !DILocation(line: 962, column: 20, scope: !1215)
!1220 = !DILocation(line: 962, column: 18, scope: !1215)
!1221 = !DILocation(line: 962, column: 25, scope: !1215)
!1222 = !DILocation(line: 960, column: 8, scope: !1223)
!1223 = !DILexicalBlockFile(scope: !1193, file: !1, discriminator: 1)
!1224 = !DILocation(line: 964, column: 20, scope: !1225)
!1225 = distinct !DILexicalBlock(scope: !1211, file: !1, line: 963, column: 4)
!1226 = !DILocation(line: 964, column: 25, scope: !1225)
!1227 = !DILocation(line: 964, column: 46, scope: !1225)
!1228 = !DILocation(line: 964, column: 5, scope: !1225)
!1229 = !DILocation(line: 965, column: 32, scope: !1225)
!1230 = !DILocation(line: 966, column: 32, scope: !1225)
!1231 = !DILocation(line: 967, column: 6, scope: !1225)
!1232 = !DILocation(line: 967, column: 12, scope: !1225)
!1233 = !DILocation(line: 966, column: 9, scope: !1225)
!1234 = !DILocation(line: 965, column: 5, scope: !1225)
!1235 = !DILocation(line: 968, column: 20, scope: !1225)
!1236 = !DILocation(line: 969, column: 4, scope: !1225)
!1237 = !DILocation(line: 973, column: 6, scope: !1238)
!1238 = distinct !DILexicalBlock(scope: !221, file: !1, line: 973, column: 6)
!1239 = !DILocation(line: 973, column: 15, scope: !1238)
!1240 = !DILocation(line: 973, column: 6, scope: !221)
!1241 = !DILocation(line: 976, column: 7, scope: !1242)
!1242 = distinct !DILexicalBlock(scope: !1243, file: !1, line: 976, column: 7)
!1243 = distinct !DILexicalBlock(scope: !1238, file: !1, line: 973, column: 24)
!1244 = !DILocation(line: 976, column: 23, scope: !1242)
!1245 = !DILocation(line: 976, column: 29, scope: !1242)
!1246 = !DILocation(line: 976, column: 46, scope: !1247)
!1247 = !DILexicalBlockFile(scope: !1242, file: !1, discriminator: 1)
!1248 = !DILocation(line: 976, column: 32, scope: !1247)
!1249 = !DILocation(line: 976, column: 7, scope: !1247)
!1250 = !DILocation(line: 977, column: 19, scope: !1251)
!1251 = distinct !DILexicalBlock(scope: !1242, file: !1, line: 976, column: 57)
!1252 = !DILocation(line: 977, column: 24, scope: !1251)
!1253 = !DILocation(line: 977, column: 49, scope: !1251)
!1254 = !DILocation(line: 977, column: 4, scope: !1251)
!1255 = !DILocation(line: 978, column: 8, scope: !1256)
!1256 = distinct !DILexicalBlock(scope: !1251, file: !1, line: 978, column: 8)
!1257 = !DILocation(line: 978, column: 24, scope: !1256)
!1258 = !DILocation(line: 978, column: 8, scope: !1251)
!1259 = !DILocation(line: 979, column: 9, scope: !1260)
!1260 = distinct !DILexicalBlock(scope: !1261, file: !1, line: 979, column: 9)
!1261 = distinct !DILexicalBlock(scope: !1256, file: !1, line: 978, column: 31)
!1262 = !DILocation(line: 979, column: 18, scope: !1260)
!1263 = !DILocation(line: 979, column: 9, scope: !1261)
!1264 = !DILocation(line: 980, column: 33, scope: !1260)
!1265 = !DILocation(line: 980, column: 6, scope: !1260)
!1266 = !DILocation(line: 983, column: 32, scope: !1260)
!1267 = !DILocation(line: 983, column: 6, scope: !1260)
!1268 = !DILocation(line: 985, column: 4, scope: !1261)
!1269 = !DILocation(line: 986, column: 19, scope: !1251)
!1270 = !DILocation(line: 987, column: 3, scope: !1251)
!1271 = !DILocation(line: 988, column: 2, scope: !1243)
!1272 = !DILocation(line: 991, column: 2, scope: !221)
!1273 = !DILocation(line: 991, column: 2, scope: !1274)
!1274 = !DILexicalBlockFile(scope: !1275, file: !1, discriminator: 1)
!1275 = distinct !DILexicalBlock(scope: !221, file: !1, line: 991, column: 2)
!1276 = !DILocation(line: 992, column: 2, scope: !221)
!1277 = !DILocation(line: 992, column: 2, scope: !1278)
!1278 = !DILexicalBlockFile(scope: !221, file: !1, discriminator: 4)
!1279 = !DILocation(line: 992, column: 2, scope: !909)
!1280 = !DILocation(line: 992, column: 2, scope: !1281)
!1281 = !DILexicalBlockFile(scope: !221, file: !1, discriminator: 2)
!1282 = !DILocation(line: 992, column: 2, scope: !1283)
!1283 = !DILexicalBlockFile(scope: !1281, file: !1, discriminator: 5)
!1284 = !DILocation(line: 992, column: 2, scope: !1285)
!1285 = !DILexicalBlockFile(scope: !221, file: !1, discriminator: 3)
!1286 = !DILocation(line: 995, column: 25, scope: !1287)
!1287 = distinct !DILexicalBlock(scope: !221, file: !1, line: 995, column: 6)
!1288 = !DILocation(line: 995, column: 6, scope: !1287)
!1289 = !DILocation(line: 995, column: 37, scope: !1287)
!1290 = !DILocation(line: 995, column: 6, scope: !221)
!1291 = !DILocation(line: 996, column: 22, scope: !1292)
!1292 = distinct !DILexicalBlock(scope: !1287, file: !1, line: 995, column: 62)
!1293 = !DILocation(line: 996, column: 27, scope: !1292)
!1294 = !DILocation(line: 997, column: 26, scope: !1292)
!1295 = !DILocation(line: 997, column: 7, scope: !1292)
!1296 = !DILocation(line: 996, column: 3, scope: !1292)
!1297 = !DILocation(line: 998, column: 18, scope: !1292)
!1298 = !DILocation(line: 999, column: 2, scope: !1292)
!1299 = !DILocation(line: 1002, column: 38, scope: !1300)
!1300 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1002, column: 6)
!1301 = !DILocation(line: 1002, column: 20, scope: !1300)
!1302 = !DILocation(line: 1002, column: 6, scope: !1300)
!1303 = !DILocation(line: 1002, column: 50, scope: !1300)
!1304 = !DILocation(line: 1002, column: 6, scope: !221)
!1305 = !DILocation(line: 1003, column: 22, scope: !1306)
!1306 = distinct !DILexicalBlock(scope: !1300, file: !1, line: 1002, column: 64)
!1307 = !DILocation(line: 1003, column: 27, scope: !1306)
!1308 = !DILocation(line: 1004, column: 25, scope: !1306)
!1309 = !DILocation(line: 1004, column: 7, scope: !1306)
!1310 = !DILocation(line: 1003, column: 3, scope: !1306)
!1311 = !DILocation(line: 1005, column: 18, scope: !1306)
!1312 = !DILocation(line: 1006, column: 2, scope: !1306)
!1313 = !DILocation(line: 1010, column: 6, scope: !1314)
!1314 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1010, column: 6)
!1315 = !DILocation(line: 1010, column: 12, scope: !1314)
!1316 = !DILocation(line: 1010, column: 6, scope: !221)
!1317 = !DILocation(line: 1011, column: 7, scope: !1318)
!1318 = distinct !DILexicalBlock(scope: !1319, file: !1, line: 1011, column: 7)
!1319 = distinct !DILexicalBlock(scope: !1314, file: !1, line: 1010, column: 21)
!1320 = !DILocation(line: 1011, column: 20, scope: !1318)
!1321 = !DILocation(line: 1011, column: 25, scope: !1318)
!1322 = !DILocation(line: 1011, column: 42, scope: !1323)
!1323 = !DILexicalBlockFile(scope: !1318, file: !1, discriminator: 1)
!1324 = !DILocation(line: 1011, column: 28, scope: !1323)
!1325 = !DILocation(line: 1011, column: 7, scope: !1323)
!1326 = !DILocation(line: 1012, column: 19, scope: !1327)
!1327 = distinct !DILexicalBlock(scope: !1318, file: !1, line: 1011, column: 50)
!1328 = !DILocation(line: 1012, column: 24, scope: !1327)
!1329 = !DILocation(line: 1012, column: 46, scope: !1327)
!1330 = !DILocation(line: 1012, column: 4, scope: !1327)
!1331 = !DILocation(line: 1013, column: 19, scope: !1327)
!1332 = !DILocation(line: 1014, column: 3, scope: !1327)
!1333 = !DILocation(line: 1015, column: 2, scope: !1319)
!1334 = !DILocation(line: 1018, column: 38, scope: !1335)
!1335 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1018, column: 6)
!1336 = !DILocation(line: 1018, column: 20, scope: !1335)
!1337 = !DILocation(line: 1018, column: 6, scope: !1335)
!1338 = !DILocation(line: 1018, column: 50, scope: !1335)
!1339 = !DILocation(line: 1018, column: 6, scope: !221)
!1340 = !DILocation(line: 1019, column: 22, scope: !1341)
!1341 = distinct !DILexicalBlock(scope: !1335, file: !1, line: 1018, column: 64)
!1342 = !DILocation(line: 1019, column: 27, scope: !1341)
!1343 = !DILocation(line: 1020, column: 25, scope: !1341)
!1344 = !DILocation(line: 1020, column: 7, scope: !1341)
!1345 = !DILocation(line: 1019, column: 3, scope: !1341)
!1346 = !DILocation(line: 1021, column: 18, scope: !1341)
!1347 = !DILocation(line: 1022, column: 2, scope: !1341)
!1348 = !DILocation(line: 1025, column: 6, scope: !1349)
!1349 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1025, column: 6)
!1350 = !DILocation(line: 1025, column: 12, scope: !1349)
!1351 = !DILocation(line: 1025, column: 6, scope: !221)
!1352 = !DILocation(line: 1026, column: 7, scope: !1353)
!1353 = distinct !DILexicalBlock(scope: !1354, file: !1, line: 1026, column: 7)
!1354 = distinct !DILexicalBlock(scope: !1349, file: !1, line: 1025, column: 21)
!1355 = !DILocation(line: 1026, column: 20, scope: !1353)
!1356 = !DILocation(line: 1026, column: 25, scope: !1353)
!1357 = !DILocation(line: 1026, column: 42, scope: !1358)
!1358 = !DILexicalBlockFile(scope: !1353, file: !1, discriminator: 1)
!1359 = !DILocation(line: 1026, column: 28, scope: !1358)
!1360 = !DILocation(line: 1026, column: 7, scope: !1358)
!1361 = !DILocation(line: 1027, column: 19, scope: !1362)
!1362 = distinct !DILexicalBlock(scope: !1353, file: !1, line: 1026, column: 50)
!1363 = !DILocation(line: 1027, column: 24, scope: !1362)
!1364 = !DILocation(line: 1027, column: 46, scope: !1362)
!1365 = !DILocation(line: 1027, column: 4, scope: !1362)
!1366 = !DILocation(line: 1028, column: 19, scope: !1362)
!1367 = !DILocation(line: 1029, column: 3, scope: !1362)
!1368 = !DILocation(line: 1030, column: 2, scope: !1354)
!1369 = !DILocation(line: 1043, column: 29, scope: !1370)
!1370 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1043, column: 6)
!1371 = !DILocation(line: 1043, column: 6, scope: !1370)
!1372 = !DILocation(line: 1043, column: 41, scope: !1370)
!1373 = !DILocation(line: 1044, column: 6, scope: !1370)
!1374 = !DILocation(line: 1044, column: 32, scope: !1375)
!1375 = !DILexicalBlockFile(scope: !1370, file: !1, discriminator: 1)
!1376 = !DILocation(line: 1044, column: 9, scope: !1375)
!1377 = !DILocation(line: 1044, column: 44, scope: !1375)
!1378 = !DILocation(line: 1043, column: 6, scope: !909)
!1379 = !DILocalVariable(name: "rdevmajor", scope: !1380, file: !1, line: 1049, type: !23)
!1380 = distinct !DILexicalBlock(scope: !1370, file: !1, line: 1044, column: 57)
!1381 = !DILocation(line: 1049, column: 7, scope: !1380)
!1382 = !DILocalVariable(name: "rdevminor", scope: !1380, file: !1, line: 1049, type: !23)
!1383 = !DILocation(line: 1049, column: 18, scope: !1380)
!1384 = !DILocation(line: 1050, column: 39, scope: !1380)
!1385 = !DILocation(line: 1050, column: 15, scope: !1380)
!1386 = !DILocation(line: 1050, column: 13, scope: !1380)
!1387 = !DILocation(line: 1051, column: 39, scope: !1380)
!1388 = !DILocation(line: 1051, column: 15, scope: !1380)
!1389 = !DILocation(line: 1051, column: 13, scope: !1380)
!1390 = !DILocation(line: 1052, column: 7, scope: !1391)
!1391 = distinct !DILexicalBlock(scope: !1380, file: !1, line: 1052, column: 7)
!1392 = !DILocation(line: 1052, column: 17, scope: !1391)
!1393 = !DILocation(line: 1052, column: 7, scope: !1380)
!1394 = !DILocation(line: 1053, column: 23, scope: !1395)
!1395 = distinct !DILexicalBlock(scope: !1391, file: !1, line: 1052, column: 31)
!1396 = !DILocation(line: 1053, column: 28, scope: !1395)
!1397 = !DILocation(line: 1054, column: 8, scope: !1395)
!1398 = !DILocation(line: 1053, column: 4, scope: !1395)
!1399 = !DILocation(line: 1066, column: 19, scope: !1395)
!1400 = !DILocation(line: 1067, column: 3, scope: !1395)
!1401 = !DILocation(line: 1073, column: 7, scope: !1402)
!1402 = distinct !DILexicalBlock(scope: !1380, file: !1, line: 1073, column: 7)
!1403 = !DILocation(line: 1073, column: 17, scope: !1402)
!1404 = !DILocation(line: 1073, column: 7, scope: !1380)
!1405 = !DILocation(line: 1074, column: 23, scope: !1406)
!1406 = distinct !DILexicalBlock(scope: !1402, file: !1, line: 1073, column: 31)
!1407 = !DILocation(line: 1074, column: 28, scope: !1406)
!1408 = !DILocation(line: 1075, column: 8, scope: !1406)
!1409 = !DILocation(line: 1074, column: 4, scope: !1406)
!1410 = !DILocation(line: 1079, column: 19, scope: !1406)
!1411 = !DILocation(line: 1080, column: 3, scope: !1406)
!1412 = !DILocation(line: 1081, column: 2, scope: !1380)
!1413 = !DILocation(line: 1091, column: 7, scope: !1414)
!1414 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1091, column: 6)
!1415 = !DILocation(line: 1091, column: 22, scope: !1414)
!1416 = !DILocation(line: 1092, column: 28, scope: !1414)
!1417 = !DILocation(line: 1092, column: 8, scope: !1414)
!1418 = !DILocation(line: 1092, column: 40, scope: !1414)
!1419 = !DILocation(line: 1093, column: 3, scope: !1414)
!1420 = !DILocation(line: 1093, column: 27, scope: !1421)
!1421 = !DILexicalBlockFile(scope: !1414, file: !1, discriminator: 1)
!1422 = !DILocation(line: 1093, column: 7, scope: !1421)
!1423 = !DILocation(line: 1093, column: 39, scope: !1421)
!1424 = !DILocation(line: 1091, column: 6, scope: !909)
!1425 = !DILocation(line: 1094, column: 18, scope: !1414)
!1426 = !DILocation(line: 1094, column: 3, scope: !1414)
!1427 = !DILocation(line: 1097, column: 32, scope: !221)
!1428 = !DILocation(line: 1097, column: 6, scope: !221)
!1429 = !DILocation(line: 1097, column: 4, scope: !221)
!1430 = !DILocation(line: 1098, column: 7, scope: !1431)
!1431 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1098, column: 6)
!1432 = !DILocation(line: 1098, column: 22, scope: !1431)
!1433 = !DILocation(line: 1098, column: 25, scope: !1434)
!1434 = !DILexicalBlockFile(scope: !1431, file: !1, discriminator: 1)
!1435 = !DILocation(line: 1098, column: 27, scope: !1434)
!1436 = !DILocation(line: 1098, column: 36, scope: !1434)
!1437 = !DILocation(line: 1098, column: 41, scope: !1438)
!1438 = !DILexicalBlockFile(scope: !1431, file: !1, discriminator: 2)
!1439 = !DILocation(line: 1098, column: 40, scope: !1438)
!1440 = !DILocation(line: 1098, column: 43, scope: !1438)
!1441 = !DILocation(line: 1098, column: 6, scope: !1438)
!1442 = !DILocation(line: 1099, column: 18, scope: !1431)
!1443 = !DILocation(line: 1099, column: 3, scope: !1431)
!1444 = !DILocation(line: 1102, column: 7, scope: !1445)
!1445 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1102, column: 6)
!1446 = !DILocation(line: 1102, column: 22, scope: !1445)
!1447 = !DILocation(line: 1102, column: 51, scope: !1448)
!1448 = !DILexicalBlockFile(scope: !1445, file: !1, discriminator: 1)
!1449 = !DILocation(line: 1102, column: 25, scope: !1448)
!1450 = !DILocation(line: 1102, column: 67, scope: !1448)
!1451 = !DILocation(line: 1102, column: 6, scope: !1448)
!1452 = !DILocation(line: 1103, column: 18, scope: !1445)
!1453 = !DILocation(line: 1103, column: 3, scope: !1445)
!1454 = !DILocation(line: 1106, column: 7, scope: !1455)
!1455 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1106, column: 6)
!1456 = !DILocation(line: 1106, column: 22, scope: !1455)
!1457 = !DILocation(line: 1106, column: 25, scope: !1458)
!1458 = !DILexicalBlockFile(scope: !1455, file: !1, discriminator: 1)
!1459 = !DILocation(line: 1106, column: 38, scope: !1458)
!1460 = !DILocation(line: 1106, column: 6, scope: !1458)
!1461 = !DILocation(line: 1107, column: 18, scope: !1455)
!1462 = !DILocation(line: 1107, column: 3, scope: !1455)
!1463 = !DILocation(line: 1109, column: 38, scope: !221)
!1464 = !DILocation(line: 1109, column: 14, scope: !221)
!1465 = !DILocation(line: 1109, column: 12, scope: !221)
!1466 = !DILocation(line: 1112, column: 7, scope: !1467)
!1467 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1112, column: 6)
!1468 = !DILocation(line: 1112, column: 22, scope: !1467)
!1469 = !DILocation(line: 1112, column: 25, scope: !1470)
!1470 = !DILexicalBlockFile(scope: !1467, file: !1, discriminator: 1)
!1471 = !DILocation(line: 1112, column: 35, scope: !1470)
!1472 = !DILocation(line: 1112, column: 6, scope: !1470)
!1473 = !DILocation(line: 1113, column: 18, scope: !1467)
!1474 = !DILocation(line: 1113, column: 3, scope: !1467)
!1475 = !DILocation(line: 1121, column: 6, scope: !1476)
!1476 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1121, column: 6)
!1477 = !DILocation(line: 1121, column: 9, scope: !1476)
!1478 = !DILocation(line: 1121, column: 17, scope: !1476)
!1479 = !DILocation(line: 1121, column: 32, scope: !1476)
!1480 = !DILocation(line: 1121, column: 6, scope: !221)
!1481 = !DILocation(line: 1122, column: 27, scope: !1482)
!1482 = distinct !DILexicalBlock(scope: !1483, file: !1, line: 1122, column: 7)
!1483 = distinct !DILexicalBlock(scope: !1476, file: !1, line: 1121, column: 70)
!1484 = !DILocation(line: 1122, column: 7, scope: !1482)
!1485 = !DILocation(line: 1122, column: 39, scope: !1482)
!1486 = !DILocation(line: 1122, column: 45, scope: !1482)
!1487 = !DILocation(line: 1123, column: 32, scope: !1482)
!1488 = !DILocation(line: 1123, column: 7, scope: !1482)
!1489 = !DILocation(line: 1123, column: 44, scope: !1482)
!1490 = !DILocation(line: 1122, column: 7, scope: !1491)
!1491 = !DILexicalBlockFile(scope: !1483, file: !1, discriminator: 1)
!1492 = !DILocation(line: 1124, column: 24, scope: !1482)
!1493 = !DILocation(line: 1124, column: 29, scope: !1482)
!1494 = !DILocation(line: 1125, column: 28, scope: !1482)
!1495 = !DILocation(line: 1125, column: 8, scope: !1482)
!1496 = !DILocation(line: 1126, column: 33, scope: !1482)
!1497 = !DILocation(line: 1126, column: 8, scope: !1482)
!1498 = !DILocation(line: 1124, column: 4, scope: !1482)
!1499 = !DILocation(line: 1128, column: 27, scope: !1500)
!1500 = distinct !DILexicalBlock(scope: !1483, file: !1, line: 1128, column: 7)
!1501 = !DILocation(line: 1128, column: 7, scope: !1500)
!1502 = !DILocation(line: 1128, column: 39, scope: !1500)
!1503 = !DILocation(line: 1128, column: 44, scope: !1500)
!1504 = !DILocation(line: 1129, column: 32, scope: !1500)
!1505 = !DILocation(line: 1129, column: 7, scope: !1500)
!1506 = !DILocation(line: 1129, column: 44, scope: !1500)
!1507 = !DILocation(line: 1128, column: 7, scope: !1491)
!1508 = !DILocation(line: 1130, column: 24, scope: !1500)
!1509 = !DILocation(line: 1130, column: 29, scope: !1500)
!1510 = !DILocation(line: 1131, column: 28, scope: !1500)
!1511 = !DILocation(line: 1131, column: 8, scope: !1500)
!1512 = !DILocation(line: 1132, column: 33, scope: !1500)
!1513 = !DILocation(line: 1132, column: 8, scope: !1500)
!1514 = !DILocation(line: 1130, column: 4, scope: !1500)
!1515 = !DILocation(line: 1135, column: 38, scope: !1516)
!1516 = distinct !DILexicalBlock(scope: !1483, file: !1, line: 1135, column: 7)
!1517 = !DILocation(line: 1135, column: 7, scope: !1516)
!1518 = !DILocation(line: 1135, column: 50, scope: !1516)
!1519 = !DILocation(line: 1136, column: 31, scope: !1516)
!1520 = !DILocation(line: 1136, column: 7, scope: !1516)
!1521 = !DILocation(line: 1137, column: 29, scope: !1516)
!1522 = !DILocation(line: 1137, column: 9, scope: !1516)
!1523 = !DILocation(line: 1137, column: 7, scope: !1516)
!1524 = !DILocation(line: 1135, column: 7, scope: !1491)
!1525 = !DILocation(line: 1138, column: 24, scope: !1516)
!1526 = !DILocation(line: 1138, column: 29, scope: !1516)
!1527 = !DILocation(line: 1140, column: 32, scope: !1516)
!1528 = !DILocation(line: 1140, column: 8, scope: !1516)
!1529 = !DILocation(line: 1141, column: 37, scope: !1516)
!1530 = !DILocation(line: 1141, column: 8, scope: !1516)
!1531 = !DILocation(line: 1138, column: 4, scope: !1516)
!1532 = !DILocation(line: 1142, column: 2, scope: !1483)
!1533 = !DILocation(line: 1151, column: 6, scope: !1534)
!1534 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1151, column: 6)
!1535 = !DILocation(line: 1151, column: 9, scope: !1534)
!1536 = !DILocation(line: 1151, column: 17, scope: !1534)
!1537 = !DILocation(line: 1151, column: 32, scope: !1534)
!1538 = !DILocation(line: 1151, column: 69, scope: !1534)
!1539 = !DILocation(line: 1152, column: 6, scope: !1534)
!1540 = !DILocation(line: 1151, column: 6, scope: !909)
!1541 = !DILocation(line: 1153, column: 27, scope: !1542)
!1542 = distinct !DILexicalBlock(scope: !1543, file: !1, line: 1153, column: 7)
!1543 = distinct !DILexicalBlock(scope: !1534, file: !1, line: 1152, column: 22)
!1544 = !DILocation(line: 1153, column: 7, scope: !1542)
!1545 = !DILocation(line: 1153, column: 39, scope: !1542)
!1546 = !DILocation(line: 1153, column: 44, scope: !1542)
!1547 = !DILocation(line: 1154, column: 27, scope: !1542)
!1548 = !DILocation(line: 1154, column: 7, scope: !1542)
!1549 = !DILocation(line: 1154, column: 39, scope: !1542)
!1550 = !DILocation(line: 1154, column: 54, scope: !1542)
!1551 = !DILocation(line: 1155, column: 32, scope: !1542)
!1552 = !DILocation(line: 1155, column: 7, scope: !1542)
!1553 = !DILocation(line: 1155, column: 44, scope: !1542)
!1554 = !DILocation(line: 1153, column: 7, scope: !1555)
!1555 = !DILexicalBlockFile(scope: !1543, file: !1, discriminator: 1)
!1556 = !DILocation(line: 1156, column: 24, scope: !1542)
!1557 = !DILocation(line: 1156, column: 29, scope: !1542)
!1558 = !DILocation(line: 1157, column: 28, scope: !1542)
!1559 = !DILocation(line: 1157, column: 8, scope: !1542)
!1560 = !DILocation(line: 1158, column: 33, scope: !1542)
!1561 = !DILocation(line: 1158, column: 8, scope: !1542)
!1562 = !DILocation(line: 1156, column: 4, scope: !1542)
!1563 = !DILocation(line: 1161, column: 33, scope: !1543)
!1564 = !DILocation(line: 1161, column: 7, scope: !1543)
!1565 = !DILocation(line: 1161, column: 5, scope: !1543)
!1566 = !DILocation(line: 1162, column: 7, scope: !1567)
!1567 = distinct !DILexicalBlock(scope: !1543, file: !1, line: 1162, column: 7)
!1568 = !DILocation(line: 1162, column: 9, scope: !1567)
!1569 = !DILocation(line: 1162, column: 18, scope: !1567)
!1570 = !DILocation(line: 1162, column: 23, scope: !1571)
!1571 = !DILexicalBlockFile(scope: !1567, file: !1, discriminator: 1)
!1572 = !DILocation(line: 1162, column: 22, scope: !1571)
!1573 = !DILocation(line: 1162, column: 25, scope: !1571)
!1574 = !DILocation(line: 1162, column: 7, scope: !1571)
!1575 = !DILocation(line: 1163, column: 19, scope: !1567)
!1576 = !DILocation(line: 1163, column: 24, scope: !1567)
!1577 = !DILocation(line: 1163, column: 54, scope: !1567)
!1578 = !DILocation(line: 1163, column: 4, scope: !1567)
!1579 = !DILocation(line: 1166, column: 8, scope: !1580)
!1580 = distinct !DILexicalBlock(scope: !1543, file: !1, line: 1166, column: 7)
!1581 = !DILocation(line: 1166, column: 18, scope: !1580)
!1582 = !DILocation(line: 1166, column: 49, scope: !1580)
!1583 = !DILocation(line: 1166, column: 7, scope: !1543)
!1584 = !DILocation(line: 1167, column: 22, scope: !1585)
!1585 = distinct !DILexicalBlock(scope: !1580, file: !1, line: 1166, column: 55)
!1586 = !DILocation(line: 1167, column: 25, scope: !1585)
!1587 = !DILocation(line: 1167, column: 41, scope: !1585)
!1588 = !DILocation(line: 1167, column: 10, scope: !1585)
!1589 = !DILocation(line: 1167, column: 8, scope: !1585)
!1590 = !DILocation(line: 1171, column: 8, scope: !1591)
!1591 = distinct !DILexicalBlock(scope: !1585, file: !1, line: 1171, column: 8)
!1592 = !DILocation(line: 1171, column: 12, scope: !1591)
!1593 = !DILocation(line: 1171, column: 8, scope: !1585)
!1594 = !DILocation(line: 1172, column: 5, scope: !1591)
!1595 = !DILocation(line: 1173, column: 3, scope: !1585)
!1596 = !DILocation(line: 1174, column: 7, scope: !1597)
!1597 = distinct !DILexicalBlock(scope: !1543, file: !1, line: 1174, column: 7)
!1598 = !DILocation(line: 1174, column: 17, scope: !1597)
!1599 = !DILocation(line: 1174, column: 7, scope: !1543)
!1600 = !DILocation(line: 1175, column: 22, scope: !1601)
!1601 = distinct !DILexicalBlock(scope: !1597, file: !1, line: 1174, column: 50)
!1602 = !DILocation(line: 1175, column: 25, scope: !1601)
!1603 = !DILocation(line: 1175, column: 41, scope: !1601)
!1604 = !DILocation(line: 1175, column: 10, scope: !1601)
!1605 = !DILocation(line: 1175, column: 8, scope: !1601)
!1606 = !DILocation(line: 1179, column: 8, scope: !1607)
!1607 = distinct !DILexicalBlock(scope: !1601, file: !1, line: 1179, column: 8)
!1608 = !DILocation(line: 1179, column: 12, scope: !1607)
!1609 = !DILocation(line: 1179, column: 8, scope: !1601)
!1610 = !DILocation(line: 1180, column: 5, scope: !1607)
!1611 = !DILocation(line: 1181, column: 3, scope: !1601)
!1612 = !DILocation(line: 1182, column: 7, scope: !1613)
!1613 = distinct !DILexicalBlock(scope: !1543, file: !1, line: 1182, column: 7)
!1614 = !DILocation(line: 1182, column: 17, scope: !1613)
!1615 = !DILocation(line: 1182, column: 7, scope: !1543)
!1616 = !DILocation(line: 1183, column: 22, scope: !1617)
!1617 = distinct !DILexicalBlock(scope: !1613, file: !1, line: 1182, column: 51)
!1618 = !DILocation(line: 1183, column: 25, scope: !1617)
!1619 = !DILocation(line: 1183, column: 41, scope: !1617)
!1620 = !DILocation(line: 1183, column: 10, scope: !1617)
!1621 = !DILocation(line: 1183, column: 8, scope: !1617)
!1622 = !DILocation(line: 1187, column: 8, scope: !1623)
!1623 = distinct !DILexicalBlock(scope: !1617, file: !1, line: 1187, column: 8)
!1624 = !DILocation(line: 1187, column: 12, scope: !1623)
!1625 = !DILocation(line: 1187, column: 8, scope: !1617)
!1626 = !DILocation(line: 1188, column: 5, scope: !1623)
!1627 = !DILocation(line: 1189, column: 3, scope: !1617)
!1628 = !DILocation(line: 1192, column: 7, scope: !1629)
!1629 = distinct !DILexicalBlock(scope: !1543, file: !1, line: 1192, column: 7)
!1630 = !DILocation(line: 1192, column: 20, scope: !1629)
!1631 = !DILocation(line: 1192, column: 7, scope: !1543)
!1632 = !DILocalVariable(name: "soffset", scope: !1633, file: !1, line: 1193, type: !52)
!1633 = distinct !DILexicalBlock(scope: !1629, file: !1, line: 1192, column: 25)
!1634 = !DILocation(line: 1193, column: 12, scope: !1633)
!1635 = !DILocalVariable(name: "slength", scope: !1633, file: !1, line: 1193, type: !52)
!1636 = !DILocation(line: 1193, column: 21, scope: !1633)
!1637 = !DILocation(line: 1195, column: 23, scope: !1633)
!1638 = !DILocation(line: 1195, column: 28, scope: !1633)
!1639 = !DILocation(line: 1195, column: 4, scope: !1633)
!1640 = !DILocation(line: 1197, column: 23, scope: !1633)
!1641 = !DILocation(line: 1197, column: 28, scope: !1633)
!1642 = !DILocation(line: 1197, column: 4, scope: !1633)
!1643 = !DILocation(line: 1199, column: 19, scope: !1633)
!1644 = !DILocation(line: 1199, column: 24, scope: !1633)
!1645 = !DILocation(line: 1200, column: 38, scope: !1633)
!1646 = !DILocation(line: 1199, column: 4, scope: !1633)
!1647 = !DILocation(line: 1201, column: 23, scope: !1633)
!1648 = !DILocation(line: 1201, column: 28, scope: !1633)
!1649 = !DILocation(line: 1203, column: 27, scope: !1633)
!1650 = !DILocation(line: 1203, column: 8, scope: !1633)
!1651 = !DILocation(line: 1201, column: 4, scope: !1633)
!1652 = !DILocation(line: 1208, column: 31, scope: !1633)
!1653 = !DILocation(line: 1209, column: 30, scope: !1633)
!1654 = !DILocation(line: 1210, column: 23, scope: !1633)
!1655 = !DILocation(line: 1209, column: 8, scope: !1633)
!1656 = !DILocation(line: 1208, column: 4, scope: !1633)
!1657 = !DILocation(line: 1216, column: 29, scope: !1633)
!1658 = !DILocation(line: 1216, column: 34, scope: !1633)
!1659 = !DILocation(line: 1217, column: 8, scope: !1633)
!1660 = !DILocation(line: 1216, column: 4, scope: !1633)
!1661 = !DILocation(line: 1218, column: 4, scope: !1633)
!1662 = !DILocation(line: 1218, column: 37, scope: !1663)
!1663 = !DILexicalBlockFile(scope: !1633, file: !1, discriminator: 1)
!1664 = !DILocation(line: 1218, column: 11, scope: !1663)
!1665 = !DILocation(line: 1219, column: 28, scope: !1633)
!1666 = !DILocation(line: 1218, column: 4, scope: !1663)
!1667 = !DILocation(line: 1220, column: 30, scope: !1668)
!1668 = distinct !DILexicalBlock(scope: !1633, file: !1, line: 1219, column: 43)
!1669 = !DILocation(line: 1220, column: 35, scope: !1668)
!1670 = !DILocation(line: 1222, column: 19, scope: !1668)
!1671 = !DILocation(line: 1223, column: 19, scope: !1668)
!1672 = !DILocation(line: 1220, column: 5, scope: !1668)
!1673 = !DILocation(line: 1224, column: 21, scope: !1668)
!1674 = !DILocation(line: 1224, column: 18, scope: !1668)
!1675 = !DILocation(line: 1225, column: 25, scope: !1676)
!1676 = distinct !DILexicalBlock(scope: !1668, file: !1, line: 1225, column: 9)
!1677 = !DILocation(line: 1225, column: 30, scope: !1676)
!1678 = !DILocation(line: 1225, column: 39, scope: !1676)
!1679 = !DILocation(line: 1225, column: 9, scope: !1676)
!1680 = !DILocation(line: 1226, column: 9, scope: !1676)
!1681 = !DILocation(line: 1225, column: 9, scope: !1668)
!1682 = !DILocation(line: 1227, column: 25, scope: !1683)
!1683 = distinct !DILexicalBlock(scope: !1676, file: !1, line: 1226, column: 24)
!1684 = !DILocation(line: 1227, column: 28, scope: !1683)
!1685 = !DILocation(line: 1227, column: 6, scope: !1683)
!1686 = !DILocation(line: 1230, column: 25, scope: !1683)
!1687 = !DILocation(line: 1230, column: 6, scope: !1683)
!1688 = !DILocation(line: 1231, column: 6, scope: !1683)
!1689 = !DILocation(line: 1232, column: 6, scope: !1683)
!1690 = !DILocation(line: 1218, column: 4, scope: !1691)
!1691 = !DILexicalBlockFile(scope: !1633, file: !1, discriminator: 2)
!1692 = !DILocation(line: 1235, column: 3, scope: !1633)
!1693 = !DILocation(line: 1238, column: 39, scope: !1694)
!1694 = distinct !DILexicalBlock(scope: !1543, file: !1, line: 1238, column: 7)
!1695 = !DILocation(line: 1238, column: 42, scope: !1694)
!1696 = !DILocation(line: 1238, column: 47, scope: !1694)
!1697 = !DILocation(line: 1238, column: 7, scope: !1694)
!1698 = !DILocation(line: 1239, column: 7, scope: !1694)
!1699 = !DILocation(line: 1238, column: 7, scope: !1543)
!1700 = !DILocation(line: 1240, column: 23, scope: !1701)
!1701 = distinct !DILexicalBlock(scope: !1694, file: !1, line: 1239, column: 25)
!1702 = !DILocation(line: 1240, column: 4, scope: !1701)
!1703 = !DILocation(line: 1241, column: 4, scope: !1701)
!1704 = !DILocation(line: 1242, column: 4, scope: !1701)
!1705 = !DILocation(line: 1244, column: 2, scope: !1543)
!1706 = !DILocation(line: 1247, column: 29, scope: !1707)
!1707 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1247, column: 6)
!1708 = !DILocation(line: 1247, column: 6, scope: !1707)
!1709 = !DILocation(line: 1247, column: 41, scope: !1707)
!1710 = !DILocation(line: 1247, column: 6, scope: !221)
!1711 = !DILocation(line: 1248, column: 26, scope: !1707)
!1712 = !DILocation(line: 1248, column: 3, scope: !1707)
!1713 = !DILocation(line: 1254, column: 6, scope: !1714)
!1714 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1254, column: 6)
!1715 = !DILocation(line: 1254, column: 9, scope: !1714)
!1716 = !DILocation(line: 1254, column: 17, scope: !1714)
!1717 = !DILocation(line: 1254, column: 32, scope: !1714)
!1718 = !DILocation(line: 1254, column: 70, scope: !1714)
!1719 = !DILocation(line: 1255, column: 6, scope: !1714)
!1720 = !DILocation(line: 1255, column: 15, scope: !1714)
!1721 = !DILocation(line: 1254, column: 6, scope: !909)
!1722 = !DILocation(line: 1256, column: 26, scope: !1714)
!1723 = !DILocation(line: 1256, column: 3, scope: !1714)
!1724 = !DILocation(line: 1268, column: 6, scope: !1725)
!1725 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1268, column: 6)
!1726 = !DILocation(line: 1268, column: 15, scope: !1725)
!1727 = !DILocation(line: 1268, column: 6, scope: !221)
!1728 = !DILocation(line: 1269, column: 26, scope: !1725)
!1729 = !DILocation(line: 1269, column: 3, scope: !1725)
!1730 = !DILocation(line: 1272, column: 33, scope: !221)
!1731 = !DILocation(line: 1272, column: 14, scope: !221)
!1732 = !DILocation(line: 1272, column: 12, scope: !221)
!1733 = !DILocation(line: 1278, column: 6, scope: !1734)
!1734 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1278, column: 6)
!1735 = !DILocation(line: 1278, column: 6, scope: !221)
!1736 = !DILocalVariable(name: "mapsize", scope: !1737, file: !1, line: 1279, type: !45)
!1737 = distinct !DILexicalBlock(scope: !1734, file: !1, line: 1278, column: 42)
!1738 = !DILocation(line: 1279, column: 10, scope: !1737)
!1739 = !DILocation(line: 1279, column: 20, scope: !1737)
!1740 = !DILocation(line: 1280, column: 48, scope: !1737)
!1741 = !DILocation(line: 1280, column: 38, scope: !1737)
!1742 = !DILocation(line: 1280, column: 35, scope: !1737)
!1743 = !DILocation(line: 1280, column: 3, scope: !1737)
!1744 = !DILocation(line: 1280, column: 8, scope: !1737)
!1745 = !DILocation(line: 1280, column: 27, scope: !1737)
!1746 = !DILocation(line: 1281, column: 26, scope: !1737)
!1747 = !DILocation(line: 1282, column: 7, scope: !1737)
!1748 = !DILocation(line: 1282, column: 17, scope: !1737)
!1749 = !DILocation(line: 1282, column: 22, scope: !1737)
!1750 = !DILocation(line: 1282, column: 15, scope: !1737)
!1751 = !DILocation(line: 1282, column: 43, scope: !1737)
!1752 = !DILocation(line: 1282, column: 41, scope: !1737)
!1753 = !DILocation(line: 1281, column: 3, scope: !1737)
!1754 = !DILocation(line: 1283, column: 2, scope: !1737)
!1755 = !DILocation(line: 1311, column: 42, scope: !1756)
!1756 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1311, column: 6)
!1757 = !DILocation(line: 1311, column: 45, scope: !1756)
!1758 = !DILocation(line: 1311, column: 56, scope: !1756)
!1759 = !DILocation(line: 1311, column: 6, scope: !1756)
!1760 = !DILocation(line: 1312, column: 12, scope: !1756)
!1761 = !DILocation(line: 1311, column: 6, scope: !221)
!1762 = !DILocation(line: 1313, column: 3, scope: !1756)
!1763 = !DILocation(line: 1316, column: 6, scope: !1764)
!1764 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1316, column: 6)
!1765 = !DILocation(line: 1316, column: 41, scope: !1764)
!1766 = !DILocation(line: 1316, column: 6, scope: !221)
!1767 = !DILocalVariable(name: "pax_attr_entry", scope: !1768, file: !1, line: 1317, type: !30)
!1768 = distinct !DILexicalBlock(scope: !1764, file: !1, line: 1316, column: 46)
!1769 = !DILocation(line: 1317, column: 25, scope: !1768)
!1770 = !DILocalVariable(name: "s", scope: !1768, file: !1, line: 1318, type: !1771)
!1771 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !1772, line: 75, baseType: !1773)
!1772 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!1773 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !41, line: 139, baseType: !42)
!1774 = !DILocation(line: 1318, column: 10, scope: !1768)
!1775 = !DILocalVariable(name: "uid", scope: !1768, file: !1, line: 1319, type: !52)
!1776 = !DILocation(line: 1319, column: 11, scope: !1768)
!1777 = !DILocalVariable(name: "gid", scope: !1768, file: !1, line: 1319, type: !52)
!1778 = !DILocation(line: 1319, column: 16, scope: !1768)
!1779 = !DILocalVariable(name: "mode", scope: !1768, file: !1, line: 1320, type: !23)
!1780 = !DILocation(line: 1320, column: 7, scope: !1768)
!1781 = !DILocation(line: 1322, column: 40, scope: !1768)
!1782 = !DILocation(line: 1322, column: 43, scope: !1768)
!1783 = !DILocation(line: 1322, column: 20, scope: !1768)
!1784 = !DILocation(line: 1322, column: 18, scope: !1768)
!1785 = !DILocation(line: 1323, column: 18, scope: !1768)
!1786 = !DILocation(line: 1323, column: 5, scope: !1768)
!1787 = !DILocation(line: 1324, column: 30, scope: !1768)
!1788 = !DILocation(line: 1325, column: 32, scope: !1768)
!1789 = !DILocation(line: 1325, column: 48, scope: !1768)
!1790 = !DILocation(line: 1325, column: 7, scope: !1768)
!1791 = !DILocation(line: 1324, column: 3, scope: !1768)
!1792 = !DILocation(line: 1326, column: 26, scope: !1768)
!1793 = !DILocation(line: 1327, column: 7, scope: !1768)
!1794 = !DILocation(line: 1326, column: 3, scope: !1768)
!1795 = !DILocation(line: 1329, column: 27, scope: !1768)
!1796 = !DILocation(line: 1329, column: 9, scope: !1768)
!1797 = !DILocation(line: 1329, column: 7, scope: !1768)
!1798 = !DILocation(line: 1330, column: 7, scope: !1799)
!1799 = distinct !DILexicalBlock(scope: !1768, file: !1, line: 1330, column: 7)
!1800 = !DILocation(line: 1330, column: 11, scope: !1799)
!1801 = !DILocation(line: 1330, column: 7, scope: !1768)
!1802 = !DILocation(line: 1331, column: 8, scope: !1799)
!1803 = !DILocation(line: 1331, column: 4, scope: !1799)
!1804 = !DILocation(line: 1332, column: 25, scope: !1768)
!1805 = !DILocation(line: 1332, column: 41, scope: !1768)
!1806 = !DILocation(line: 1332, column: 3, scope: !1768)
!1807 = !DILocation(line: 1333, column: 27, scope: !1768)
!1808 = !DILocation(line: 1333, column: 9, scope: !1768)
!1809 = !DILocation(line: 1333, column: 7, scope: !1768)
!1810 = !DILocation(line: 1334, column: 7, scope: !1811)
!1811 = distinct !DILexicalBlock(scope: !1768, file: !1, line: 1334, column: 7)
!1812 = !DILocation(line: 1334, column: 11, scope: !1811)
!1813 = !DILocation(line: 1334, column: 7, scope: !1768)
!1814 = !DILocation(line: 1335, column: 8, scope: !1811)
!1815 = !DILocation(line: 1335, column: 4, scope: !1811)
!1816 = !DILocation(line: 1336, column: 25, scope: !1768)
!1817 = !DILocation(line: 1336, column: 41, scope: !1768)
!1818 = !DILocation(line: 1336, column: 3, scope: !1768)
!1819 = !DILocation(line: 1338, column: 29, scope: !1768)
!1820 = !DILocation(line: 1338, column: 10, scope: !1768)
!1821 = !DILocation(line: 1338, column: 8, scope: !1768)
!1822 = !DILocation(line: 1340, column: 8, scope: !1768)
!1823 = !DILocation(line: 1343, column: 8, scope: !1768)
!1824 = !DILocation(line: 1346, column: 8, scope: !1768)
!1825 = !DILocation(line: 1348, column: 26, scope: !1768)
!1826 = !DILocation(line: 1348, column: 42, scope: !1768)
!1827 = !DILocation(line: 1348, column: 3, scope: !1768)
!1828 = !DILocation(line: 1351, column: 27, scope: !1768)
!1829 = !DILocation(line: 1352, column: 27, scope: !1768)
!1830 = !DILocation(line: 1352, column: 7, scope: !1768)
!1831 = !DILocation(line: 1351, column: 3, scope: !1768)
!1832 = !DILocation(line: 1353, column: 27, scope: !1768)
!1833 = !DILocation(line: 1354, column: 27, scope: !1768)
!1834 = !DILocation(line: 1354, column: 7, scope: !1768)
!1835 = !DILocation(line: 1353, column: 3, scope: !1768)
!1836 = !DILocation(line: 1357, column: 27, scope: !1768)
!1837 = !DILocation(line: 1357, column: 7, scope: !1768)
!1838 = !DILocation(line: 1357, column: 5, scope: !1768)
!1839 = !DILocation(line: 1358, column: 7, scope: !1840)
!1840 = distinct !DILexicalBlock(scope: !1768, file: !1, line: 1358, column: 7)
!1841 = !DILocation(line: 1358, column: 9, scope: !1840)
!1842 = !DILocation(line: 1358, column: 7, scope: !1768)
!1843 = !DILocation(line: 1358, column: 18, scope: !1844)
!1844 = !DILexicalBlockFile(scope: !1845, file: !1, discriminator: 1)
!1845 = distinct !DILexicalBlock(scope: !1840, file: !1, line: 1358, column: 14)
!1846 = !DILocation(line: 1358, column: 23, scope: !1844)
!1847 = !DILocation(line: 1359, column: 7, scope: !1848)
!1848 = distinct !DILexicalBlock(scope: !1768, file: !1, line: 1359, column: 7)
!1849 = !DILocation(line: 1359, column: 9, scope: !1848)
!1850 = !DILocation(line: 1359, column: 7, scope: !1768)
!1851 = !DILocation(line: 1359, column: 28, scope: !1852)
!1852 = !DILexicalBlockFile(scope: !1853, file: !1, discriminator: 1)
!1853 = distinct !DILexicalBlock(scope: !1848, file: !1, line: 1359, column: 24)
!1854 = !DILocation(line: 1359, column: 42, scope: !1852)
!1855 = !DILocation(line: 1360, column: 27, scope: !1768)
!1856 = !DILocation(line: 1360, column: 43, scope: !1768)
!1857 = !DILocation(line: 1360, column: 3, scope: !1768)
!1858 = !DILocation(line: 1363, column: 27, scope: !1768)
!1859 = !DILocation(line: 1363, column: 3, scope: !1768)
!1860 = !DILocation(line: 1366, column: 27, scope: !1768)
!1861 = !DILocation(line: 1366, column: 3, scope: !1768)
!1862 = !DILocation(line: 1368, column: 43, scope: !1768)
!1863 = !DILocation(line: 1368, column: 46, scope: !1768)
!1864 = !DILocation(line: 1369, column: 7, scope: !1768)
!1865 = !DILocation(line: 1368, column: 7, scope: !1768)
!1866 = !DILocation(line: 1368, column: 5, scope: !1768)
!1867 = !DILocation(line: 1371, column: 22, scope: !1768)
!1868 = !DILocation(line: 1371, column: 3, scope: !1768)
!1869 = !DILocation(line: 1374, column: 7, scope: !1870)
!1870 = distinct !DILexicalBlock(scope: !1768, file: !1, line: 1374, column: 7)
!1871 = !DILocation(line: 1374, column: 9, scope: !1870)
!1872 = !DILocation(line: 1374, column: 7, scope: !1768)
!1873 = !DILocation(line: 1375, column: 23, scope: !1874)
!1874 = distinct !DILexicalBlock(scope: !1870, file: !1, line: 1374, column: 25)
!1875 = !DILocation(line: 1375, column: 26, scope: !1874)
!1876 = !DILocation(line: 1375, column: 4, scope: !1874)
!1877 = !DILocation(line: 1378, column: 4, scope: !1874)
!1878 = !DILocation(line: 1379, column: 14, scope: !1879)
!1879 = distinct !DILexicalBlock(scope: !1870, file: !1, line: 1379, column: 14)
!1880 = !DILocation(line: 1379, column: 18, scope: !1879)
!1881 = !DILocation(line: 1379, column: 16, scope: !1879)
!1882 = !DILocation(line: 1379, column: 14, scope: !1870)
!1883 = !DILocation(line: 1380, column: 10, scope: !1879)
!1884 = !DILocation(line: 1380, column: 8, scope: !1879)
!1885 = !DILocation(line: 1380, column: 4, scope: !1879)
!1886 = !DILocation(line: 1381, column: 30, scope: !1768)
!1887 = !DILocation(line: 1381, column: 33, scope: !1768)
!1888 = !DILocation(line: 1381, column: 7, scope: !1768)
!1889 = !DILocation(line: 1381, column: 5, scope: !1768)
!1890 = !DILocation(line: 1382, column: 7, scope: !1891)
!1891 = distinct !DILexicalBlock(scope: !1768, file: !1, line: 1382, column: 7)
!1892 = !DILocation(line: 1382, column: 9, scope: !1891)
!1893 = !DILocation(line: 1382, column: 7, scope: !1768)
!1894 = !DILocation(line: 1383, column: 22, scope: !1895)
!1895 = distinct !DILexicalBlock(scope: !1891, file: !1, line: 1382, column: 24)
!1896 = !DILocation(line: 1383, column: 4, scope: !1895)
!1897 = !DILocation(line: 1384, column: 4, scope: !1895)
!1898 = !DILocation(line: 1384, column: 9, scope: !1895)
!1899 = !DILocation(line: 1384, column: 31, scope: !1895)
!1900 = !DILocation(line: 1385, column: 4, scope: !1895)
!1901 = !DILocation(line: 1385, column: 9, scope: !1895)
!1902 = !DILocation(line: 1385, column: 23, scope: !1895)
!1903 = !DILocation(line: 1386, column: 4, scope: !1895)
!1904 = !DILocation(line: 1389, column: 32, scope: !1768)
!1905 = !DILocation(line: 1389, column: 3, scope: !1768)
!1906 = !DILocation(line: 1389, column: 8, scope: !1768)
!1907 = !DILocation(line: 1389, column: 30, scope: !1768)
!1908 = !DILocation(line: 1391, column: 26, scope: !1768)
!1909 = !DILocation(line: 1391, column: 31, scope: !1768)
!1910 = !DILocation(line: 1391, column: 16, scope: !1768)
!1911 = !DILocation(line: 1391, column: 13, scope: !1768)
!1912 = !DILocation(line: 1390, column: 3, scope: !1768)
!1913 = !DILocation(line: 1390, column: 8, scope: !1768)
!1914 = !DILocation(line: 1390, column: 22, scope: !1768)
!1915 = !DILocation(line: 1393, column: 30, scope: !1768)
!1916 = !DILocation(line: 1393, column: 33, scope: !1768)
!1917 = !DILocation(line: 1393, column: 38, scope: !1768)
!1918 = !DILocation(line: 1393, column: 49, scope: !1768)
!1919 = !DILocation(line: 1394, column: 7, scope: !1768)
!1920 = !DILocation(line: 1393, column: 7, scope: !1768)
!1921 = !DILocation(line: 1393, column: 5, scope: !1768)
!1922 = !DILocation(line: 1395, column: 7, scope: !1923)
!1923 = distinct !DILexicalBlock(scope: !1768, file: !1, line: 1395, column: 7)
!1924 = !DILocation(line: 1395, column: 9, scope: !1923)
!1925 = !DILocation(line: 1395, column: 7, scope: !1768)
!1926 = !DILocation(line: 1397, column: 4, scope: !1927)
!1927 = distinct !DILexicalBlock(scope: !1923, file: !1, line: 1395, column: 24)
!1928 = !DILocation(line: 1400, column: 29, scope: !1768)
!1929 = !DILocation(line: 1400, column: 40, scope: !1768)
!1930 = !DILocation(line: 1400, column: 45, scope: !1768)
!1931 = !DILocation(line: 1400, column: 7, scope: !1768)
!1932 = !DILocation(line: 1400, column: 5, scope: !1768)
!1933 = !DILocation(line: 1401, column: 7, scope: !1934)
!1934 = distinct !DILexicalBlock(scope: !1768, file: !1, line: 1401, column: 7)
!1935 = !DILocation(line: 1401, column: 9, scope: !1934)
!1936 = !DILocation(line: 1401, column: 7, scope: !1768)
!1937 = !DILocation(line: 1403, column: 4, scope: !1938)
!1938 = distinct !DILexicalBlock(scope: !1934, file: !1, line: 1401, column: 24)
!1939 = !DILocation(line: 1405, column: 32, scope: !1768)
!1940 = !DILocation(line: 1405, column: 37, scope: !1768)
!1941 = !DILocation(line: 1405, column: 51, scope: !1768)
!1942 = !DILocation(line: 1405, column: 3, scope: !1768)
!1943 = !DILocation(line: 1405, column: 8, scope: !1768)
!1944 = !DILocation(line: 1405, column: 30, scope: !1768)
!1945 = !DILocation(line: 1406, column: 2, scope: !1768)
!1946 = !DILocation(line: 1409, column: 29, scope: !221)
!1947 = !DILocation(line: 1409, column: 32, scope: !221)
!1948 = !DILocation(line: 1409, column: 6, scope: !221)
!1949 = !DILocation(line: 1409, column: 4, scope: !221)
!1950 = !DILocation(line: 1410, column: 6, scope: !1951)
!1951 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1410, column: 6)
!1952 = !DILocation(line: 1410, column: 8, scope: !1951)
!1953 = !DILocation(line: 1410, column: 6, scope: !221)
!1954 = !DILocation(line: 1411, column: 11, scope: !1951)
!1955 = !DILocation(line: 1411, column: 3, scope: !1951)
!1956 = !DILocation(line: 1418, column: 25, scope: !221)
!1957 = !DILocation(line: 1418, column: 41, scope: !221)
!1958 = !DILocation(line: 1418, column: 2, scope: !221)
!1959 = !DILocation(line: 1419, column: 6, scope: !1960)
!1960 = distinct !DILexicalBlock(scope: !221, file: !1, line: 1419, column: 6)
!1961 = !DILocation(line: 1419, column: 11, scope: !1960)
!1962 = !DILocation(line: 1419, column: 23, scope: !1960)
!1963 = !DILocation(line: 1419, column: 31, scope: !1960)
!1964 = !DILocation(line: 1419, column: 34, scope: !1965)
!1965 = !DILexicalBlockFile(scope: !1960, file: !1, discriminator: 1)
!1966 = !DILocation(line: 1419, column: 44, scope: !1965)
!1967 = !DILocation(line: 1419, column: 6, scope: !1965)
!1968 = !DILocation(line: 1422, column: 19, scope: !1969)
!1969 = distinct !DILexicalBlock(scope: !1960, file: !1, line: 1419, column: 49)
!1970 = !DILocation(line: 1422, column: 27, scope: !1969)
!1971 = !DILocation(line: 1422, column: 3, scope: !1969)
!1972 = !DILocation(line: 1423, column: 18, scope: !1969)
!1973 = !DILocation(line: 1423, column: 16, scope: !1969)
!1974 = !DILocation(line: 1424, column: 2, scope: !1969)
!1975 = !DILocation(line: 1425, column: 42, scope: !221)
!1976 = !DILocation(line: 1425, column: 32, scope: !221)
!1977 = !DILocation(line: 1425, column: 29, scope: !221)
!1978 = !DILocation(line: 1425, column: 2, scope: !221)
!1979 = !DILocation(line: 1425, column: 7, scope: !221)
!1980 = !DILocation(line: 1425, column: 21, scope: !221)
!1981 = !DILocation(line: 1426, column: 21, scope: !221)
!1982 = !DILocation(line: 1426, column: 2, scope: !221)
!1983 = !DILocation(line: 1427, column: 2, scope: !221)
!1984 = !DILocation(line: 1429, column: 10, scope: !221)
!1985 = !DILocation(line: 1429, column: 2, scope: !221)
!1986 = !DILocation(line: 1430, column: 1, scope: !221)
!1987 = !DILocalVariable(name: "a", arg: 1, scope: !283, file: !1, line: 1748, type: !4)
!1988 = !DILocation(line: 1748, column: 46, scope: !283)
!1989 = !DILocalVariable(name: "buff", arg: 2, scope: !283, file: !1, line: 1748, type: !43)
!1990 = !DILocation(line: 1748, column: 61, scope: !283)
!1991 = !DILocalVariable(name: "s", arg: 3, scope: !283, file: !1, line: 1748, type: !45)
!1992 = !DILocation(line: 1748, column: 74, scope: !283)
!1993 = !DILocalVariable(name: "pax", scope: !283, file: !1, line: 1750, type: !192)
!1994 = !DILocation(line: 1750, column: 14, scope: !283)
!1995 = !DILocalVariable(name: "ws", scope: !283, file: !1, line: 1751, type: !45)
!1996 = !DILocation(line: 1751, column: 9, scope: !283)
!1997 = !DILocalVariable(name: "total", scope: !283, file: !1, line: 1752, type: !45)
!1998 = !DILocation(line: 1752, column: 9, scope: !283)
!1999 = !DILocalVariable(name: "ret", scope: !283, file: !1, line: 1753, type: !23)
!2000 = !DILocation(line: 1753, column: 6, scope: !283)
!2001 = !DILocation(line: 1755, column: 22, scope: !283)
!2002 = !DILocation(line: 1755, column: 25, scope: !283)
!2003 = !DILocation(line: 1755, column: 8, scope: !283)
!2004 = !DILocation(line: 1755, column: 6, scope: !283)
!2005 = !DILocation(line: 1761, column: 6, scope: !2006)
!2006 = distinct !DILexicalBlock(scope: !283, file: !1, line: 1761, column: 6)
!2007 = !DILocation(line: 1761, column: 6, scope: !283)
!2008 = !DILocation(line: 1762, column: 32, scope: !2009)
!2009 = distinct !DILexicalBlock(scope: !2006, file: !1, line: 1761, column: 42)
!2010 = !DILocation(line: 1762, column: 35, scope: !2009)
!2011 = !DILocation(line: 1762, column: 40, scope: !2009)
!2012 = !DILocation(line: 1762, column: 51, scope: !2009)
!2013 = !DILocation(line: 1763, column: 7, scope: !2009)
!2014 = !DILocation(line: 1762, column: 9, scope: !2009)
!2015 = !DILocation(line: 1762, column: 7, scope: !2009)
!2016 = !DILocation(line: 1764, column: 7, scope: !2017)
!2017 = distinct !DILexicalBlock(scope: !2009, file: !1, line: 1764, column: 7)
!2018 = !DILocation(line: 1764, column: 11, scope: !2017)
!2019 = !DILocation(line: 1764, column: 7, scope: !2009)
!2020 = !DILocation(line: 1765, column: 12, scope: !2017)
!2021 = !DILocation(line: 1765, column: 11, scope: !2017)
!2022 = !DILocation(line: 1765, column: 4, scope: !2017)
!2023 = !DILocation(line: 1766, column: 31, scope: !2009)
!2024 = !DILocation(line: 1766, column: 34, scope: !2009)
!2025 = !DILocation(line: 1766, column: 39, scope: !2009)
!2026 = !DILocation(line: 1766, column: 9, scope: !2009)
!2027 = !DILocation(line: 1766, column: 7, scope: !2009)
!2028 = !DILocation(line: 1767, column: 7, scope: !2029)
!2029 = distinct !DILexicalBlock(scope: !2009, file: !1, line: 1767, column: 7)
!2030 = !DILocation(line: 1767, column: 11, scope: !2029)
!2031 = !DILocation(line: 1767, column: 7, scope: !2009)
!2032 = !DILocation(line: 1768, column: 12, scope: !2029)
!2033 = !DILocation(line: 1768, column: 11, scope: !2029)
!2034 = !DILocation(line: 1768, column: 4, scope: !2029)
!2035 = !DILocation(line: 1769, column: 3, scope: !2009)
!2036 = !DILocation(line: 1770, column: 2, scope: !2009)
!2037 = !DILocation(line: 1772, column: 8, scope: !283)
!2038 = !DILocation(line: 1773, column: 2, scope: !283)
!2039 = !DILocation(line: 1773, column: 9, scope: !2040)
!2040 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 1)
!2041 = !DILocation(line: 1773, column: 17, scope: !2040)
!2042 = !DILocation(line: 1773, column: 15, scope: !2040)
!2043 = !DILocation(line: 1773, column: 2, scope: !2040)
!2044 = !DILocalVariable(name: "p", scope: !2045, file: !1, line: 1774, type: !115)
!2045 = distinct !DILexicalBlock(scope: !283, file: !1, line: 1773, column: 20)
!2046 = !DILocation(line: 1774, column: 24, scope: !2045)
!2047 = !DILocation(line: 1776, column: 3, scope: !2045)
!2048 = !DILocation(line: 1776, column: 10, scope: !2049)
!2049 = !DILexicalBlockFile(scope: !2045, file: !1, discriminator: 1)
!2050 = !DILocation(line: 1776, column: 15, scope: !2049)
!2051 = !DILocation(line: 1776, column: 27, scope: !2049)
!2052 = !DILocation(line: 1776, column: 35, scope: !2049)
!2053 = !DILocation(line: 1777, column: 7, scope: !2045)
!2054 = !DILocation(line: 1777, column: 12, scope: !2045)
!2055 = !DILocation(line: 1777, column: 25, scope: !2045)
!2056 = !DILocation(line: 1777, column: 35, scope: !2045)
!2057 = !DILocation(line: 1776, column: 3, scope: !2058)
!2058 = !DILexicalBlockFile(scope: !2045, file: !1, discriminator: 2)
!2059 = !DILocalVariable(name: "sb", scope: !2060, file: !1, line: 1778, type: !203)
!2060 = distinct !DILexicalBlock(scope: !2045, file: !1, line: 1777, column: 41)
!2061 = !DILocation(line: 1778, column: 25, scope: !2060)
!2062 = !DILocation(line: 1778, column: 30, scope: !2060)
!2063 = !DILocation(line: 1778, column: 35, scope: !2060)
!2064 = !DILocation(line: 1778, column: 48, scope: !2060)
!2065 = !DILocation(line: 1779, column: 9, scope: !2060)
!2066 = !DILocation(line: 1779, column: 14, scope: !2060)
!2067 = !DILocation(line: 1779, column: 4, scope: !2060)
!2068 = !DILocation(line: 1780, column: 23, scope: !2060)
!2069 = !DILocation(line: 1780, column: 4, scope: !2060)
!2070 = !DILocation(line: 1780, column: 9, scope: !2060)
!2071 = !DILocation(line: 1780, column: 21, scope: !2060)
!2072 = !DILocation(line: 1776, column: 3, scope: !2073)
!2073 = !DILexicalBlockFile(scope: !2045, file: !1, discriminator: 3)
!2074 = !DILocation(line: 1783, column: 7, scope: !2075)
!2075 = distinct !DILexicalBlock(scope: !2045, file: !1, line: 1783, column: 7)
!2076 = !DILocation(line: 1783, column: 12, scope: !2075)
!2077 = !DILocation(line: 1783, column: 24, scope: !2075)
!2078 = !DILocation(line: 1783, column: 7, scope: !2045)
!2079 = !DILocation(line: 1784, column: 12, scope: !2075)
!2080 = !DILocation(line: 1784, column: 4, scope: !2075)
!2081 = !DILocation(line: 1786, column: 31, scope: !2045)
!2082 = !DILocation(line: 1786, column: 39, scope: !2045)
!2083 = !DILocation(line: 1786, column: 37, scope: !2045)
!2084 = !DILocation(line: 1786, column: 5, scope: !2045)
!2085 = !DILocation(line: 1787, column: 8, scope: !2045)
!2086 = !DILocation(line: 1787, column: 12, scope: !2045)
!2087 = !DILocation(line: 1787, column: 10, scope: !2045)
!2088 = !DILocation(line: 1787, column: 6, scope: !2045)
!2089 = !DILocation(line: 1788, column: 7, scope: !2090)
!2090 = distinct !DILexicalBlock(scope: !2045, file: !1, line: 1788, column: 7)
!2091 = !DILocation(line: 1788, column: 12, scope: !2090)
!2092 = !DILocation(line: 1788, column: 17, scope: !2090)
!2093 = !DILocation(line: 1788, column: 30, scope: !2090)
!2094 = !DILocation(line: 1788, column: 10, scope: !2090)
!2095 = !DILocation(line: 1788, column: 7, scope: !2045)
!2096 = !DILocation(line: 1789, column: 17, scope: !2090)
!2097 = !DILocation(line: 1789, column: 22, scope: !2090)
!2098 = !DILocation(line: 1789, column: 35, scope: !2090)
!2099 = !DILocation(line: 1789, column: 7, scope: !2090)
!2100 = !DILocation(line: 1789, column: 4, scope: !2090)
!2101 = !DILocation(line: 1791, column: 7, scope: !2102)
!2102 = distinct !DILexicalBlock(scope: !2045, file: !1, line: 1791, column: 7)
!2103 = !DILocation(line: 1791, column: 12, scope: !2102)
!2104 = !DILocation(line: 1791, column: 25, scope: !2102)
!2105 = !DILocation(line: 1791, column: 7, scope: !2045)
!2106 = !DILocation(line: 1794, column: 35, scope: !2107)
!2107 = distinct !DILexicalBlock(scope: !2102, file: !1, line: 1791, column: 34)
!2108 = !DILocation(line: 1794, column: 4, scope: !2107)
!2109 = !DILocation(line: 1794, column: 9, scope: !2107)
!2110 = !DILocation(line: 1794, column: 22, scope: !2107)
!2111 = !DILocation(line: 1794, column: 32, scope: !2107)
!2112 = !DILocation(line: 1795, column: 13, scope: !2107)
!2113 = !DILocation(line: 1795, column: 10, scope: !2107)
!2114 = !DILocation(line: 1796, column: 4, scope: !2107)
!2115 = !DILocation(line: 1799, column: 32, scope: !2045)
!2116 = !DILocation(line: 1799, column: 35, scope: !2045)
!2117 = !DILocation(line: 1799, column: 38, scope: !2045)
!2118 = !DILocation(line: 1799, column: 9, scope: !2045)
!2119 = !DILocation(line: 1799, column: 7, scope: !2045)
!2120 = !DILocation(line: 1800, column: 34, scope: !2045)
!2121 = !DILocation(line: 1800, column: 3, scope: !2045)
!2122 = !DILocation(line: 1800, column: 8, scope: !2045)
!2123 = !DILocation(line: 1800, column: 21, scope: !2045)
!2124 = !DILocation(line: 1800, column: 31, scope: !2045)
!2125 = !DILocation(line: 1801, column: 12, scope: !2045)
!2126 = !DILocation(line: 1801, column: 9, scope: !2045)
!2127 = !DILocation(line: 1802, column: 7, scope: !2128)
!2128 = distinct !DILexicalBlock(scope: !2045, file: !1, line: 1802, column: 7)
!2129 = !DILocation(line: 1802, column: 11, scope: !2128)
!2130 = !DILocation(line: 1802, column: 7, scope: !2045)
!2131 = !DILocation(line: 1803, column: 12, scope: !2128)
!2132 = !DILocation(line: 1803, column: 11, scope: !2128)
!2133 = !DILocation(line: 1803, column: 4, scope: !2128)
!2134 = !DILocation(line: 1773, column: 2, scope: !2135)
!2135 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 2)
!2136 = !DILocation(line: 1805, column: 10, scope: !283)
!2137 = !DILocation(line: 1805, column: 2, scope: !283)
!2138 = !DILocation(line: 1806, column: 1, scope: !283)
!2139 = !DILocalVariable(name: "a", arg: 1, scope: !280, file: !1, line: 1700, type: !4)
!2140 = !DILocation(line: 1700, column: 47, scope: !280)
!2141 = !DILocation(line: 1702, column: 32, scope: !280)
!2142 = !DILocation(line: 1702, column: 10, scope: !280)
!2143 = !DILocation(line: 1702, column: 2, scope: !280)
!2144 = !DILocalVariable(name: "a", arg: 1, scope: !281, file: !1, line: 1706, type: !4)
!2145 = !DILocation(line: 1706, column: 46, scope: !281)
!2146 = !DILocalVariable(name: "pax", scope: !281, file: !1, line: 1708, type: !192)
!2147 = !DILocation(line: 1708, column: 14, scope: !281)
!2148 = !DILocation(line: 1710, column: 22, scope: !281)
!2149 = !DILocation(line: 1710, column: 25, scope: !281)
!2150 = !DILocation(line: 1710, column: 8, scope: !281)
!2151 = !DILocation(line: 1710, column: 6, scope: !281)
!2152 = !DILocation(line: 1711, column: 6, scope: !2153)
!2153 = distinct !DILexicalBlock(scope: !281, file: !1, line: 1711, column: 6)
!2154 = !DILocation(line: 1711, column: 10, scope: !2153)
!2155 = !DILocation(line: 1711, column: 6, scope: !281)
!2156 = !DILocation(line: 1712, column: 3, scope: !2153)
!2157 = !DILocation(line: 1714, column: 23, scope: !281)
!2158 = !DILocation(line: 1714, column: 28, scope: !281)
!2159 = !DILocation(line: 1714, column: 2, scope: !281)
!2160 = !DILocation(line: 1715, column: 23, scope: !281)
!2161 = !DILocation(line: 1715, column: 28, scope: !281)
!2162 = !DILocation(line: 1715, column: 2, scope: !281)
!2163 = !DILocation(line: 1716, column: 23, scope: !281)
!2164 = !DILocation(line: 1716, column: 28, scope: !281)
!2165 = !DILocation(line: 1716, column: 2, scope: !281)
!2166 = !DILocation(line: 1717, column: 20, scope: !281)
!2167 = !DILocation(line: 1717, column: 2, scope: !281)
!2168 = !DILocation(line: 1718, column: 7, scope: !281)
!2169 = !DILocation(line: 1718, column: 2, scope: !281)
!2170 = !DILocation(line: 1719, column: 2, scope: !281)
!2171 = !DILocation(line: 1719, column: 5, scope: !281)
!2172 = !DILocation(line: 1719, column: 17, scope: !281)
!2173 = !DILocation(line: 1720, column: 2, scope: !281)
!2174 = !DILocation(line: 1721, column: 1, scope: !281)
!2175 = !DILocalVariable(name: "a", arg: 1, scope: !282, file: !1, line: 1724, type: !4)
!2176 = !DILocation(line: 1724, column: 54, scope: !282)
!2177 = !DILocalVariable(name: "pax", scope: !282, file: !1, line: 1726, type: !192)
!2178 = !DILocation(line: 1726, column: 14, scope: !282)
!2179 = !DILocalVariable(name: "remaining", scope: !282, file: !1, line: 1727, type: !196)
!2180 = !DILocation(line: 1727, column: 11, scope: !282)
!2181 = !DILocalVariable(name: "ret", scope: !282, file: !1, line: 1728, type: !23)
!2182 = !DILocation(line: 1728, column: 6, scope: !282)
!2183 = !DILocation(line: 1730, column: 22, scope: !282)
!2184 = !DILocation(line: 1730, column: 25, scope: !282)
!2185 = !DILocation(line: 1730, column: 8, scope: !282)
!2186 = !DILocation(line: 1730, column: 6, scope: !282)
!2187 = !DILocation(line: 1731, column: 14, scope: !282)
!2188 = !DILocation(line: 1731, column: 19, scope: !282)
!2189 = !DILocation(line: 1731, column: 12, scope: !282)
!2190 = !DILocation(line: 1732, column: 6, scope: !2191)
!2191 = distinct !DILexicalBlock(scope: !282, file: !1, line: 1732, column: 6)
!2192 = !DILocation(line: 1732, column: 16, scope: !2191)
!2193 = !DILocation(line: 1732, column: 6, scope: !282)
!2194 = !DILocation(line: 1733, column: 3, scope: !2195)
!2195 = distinct !DILexicalBlock(scope: !2191, file: !1, line: 1732, column: 22)
!2196 = !DILocation(line: 1733, column: 10, scope: !2197)
!2197 = !DILexicalBlockFile(scope: !2195, file: !1, discriminator: 1)
!2198 = !DILocation(line: 1733, column: 15, scope: !2197)
!2199 = !DILocation(line: 1733, column: 3, scope: !2197)
!2200 = !DILocalVariable(name: "sb", scope: !2201, file: !1, line: 1734, type: !203)
!2201 = distinct !DILexicalBlock(scope: !2195, file: !1, line: 1733, column: 28)
!2202 = !DILocation(line: 1734, column: 25, scope: !2201)
!2203 = !DILocation(line: 1735, column: 9, scope: !2204)
!2204 = distinct !DILexicalBlock(scope: !2201, file: !1, line: 1735, column: 8)
!2205 = !DILocation(line: 1735, column: 14, scope: !2204)
!2206 = !DILocation(line: 1735, column: 27, scope: !2204)
!2207 = !DILocation(line: 1735, column: 8, scope: !2201)
!2208 = !DILocation(line: 1736, column: 18, scope: !2204)
!2209 = !DILocation(line: 1736, column: 23, scope: !2204)
!2210 = !DILocation(line: 1736, column: 36, scope: !2204)
!2211 = !DILocation(line: 1736, column: 15, scope: !2204)
!2212 = !DILocation(line: 1736, column: 5, scope: !2204)
!2213 = !DILocation(line: 1737, column: 9, scope: !2201)
!2214 = !DILocation(line: 1737, column: 14, scope: !2201)
!2215 = !DILocation(line: 1737, column: 27, scope: !2201)
!2216 = !DILocation(line: 1737, column: 7, scope: !2201)
!2217 = !DILocation(line: 1738, column: 9, scope: !2201)
!2218 = !DILocation(line: 1738, column: 14, scope: !2201)
!2219 = !DILocation(line: 1738, column: 4, scope: !2201)
!2220 = !DILocation(line: 1739, column: 23, scope: !2201)
!2221 = !DILocation(line: 1739, column: 4, scope: !2201)
!2222 = !DILocation(line: 1739, column: 9, scope: !2201)
!2223 = !DILocation(line: 1739, column: 21, scope: !2201)
!2224 = !DILocation(line: 1733, column: 3, scope: !2225)
!2225 = !DILexicalBlockFile(scope: !2195, file: !1, discriminator: 2)
!2226 = !DILocation(line: 1741, column: 2, scope: !2195)
!2227 = !DILocation(line: 1742, column: 30, scope: !282)
!2228 = !DILocation(line: 1742, column: 42, scope: !282)
!2229 = !DILocation(line: 1742, column: 54, scope: !282)
!2230 = !DILocation(line: 1742, column: 59, scope: !282)
!2231 = !DILocation(line: 1742, column: 52, scope: !282)
!2232 = !DILocation(line: 1742, column: 8, scope: !282)
!2233 = !DILocation(line: 1742, column: 6, scope: !282)
!2234 = !DILocation(line: 1743, column: 31, scope: !282)
!2235 = !DILocation(line: 1743, column: 36, scope: !282)
!2236 = !DILocation(line: 1743, column: 50, scope: !282)
!2237 = !DILocation(line: 1743, column: 2, scope: !282)
!2238 = !DILocation(line: 1743, column: 7, scope: !282)
!2239 = !DILocation(line: 1743, column: 29, scope: !282)
!2240 = !DILocation(line: 1744, column: 10, scope: !282)
!2241 = !DILocation(line: 1744, column: 2, scope: !282)
!2242 = !DILocalVariable(name: "a", arg: 1, scope: !222, file: !1, line: 405, type: !4)
!2243 = !DILocation(line: 405, column: 42, scope: !222)
!2244 = !DILocalVariable(name: "entry", arg: 2, scope: !222, file: !1, line: 405, type: !30)
!2245 = !DILocation(line: 405, column: 67, scope: !222)
!2246 = !DILocalVariable(name: "name", arg: 3, scope: !222, file: !1, line: 406, type: !225)
!2247 = !DILocation(line: 406, column: 18, scope: !222)
!2248 = !DILocalVariable(name: "length", arg: 4, scope: !222, file: !1, line: 406, type: !65)
!2249 = !DILocation(line: 406, column: 32, scope: !222)
!2250 = !DILocalVariable(name: "sc", arg: 5, scope: !222, file: !1, line: 406, type: !102)
!2251 = !DILocation(line: 406, column: 68, scope: !222)
!2252 = !DILocalVariable(name: "r", scope: !222, file: !1, line: 408, type: !23)
!2253 = !DILocation(line: 408, column: 6, scope: !222)
!2254 = !DILocation(line: 410, column: 31, scope: !222)
!2255 = !DILocation(line: 410, column: 38, scope: !222)
!2256 = !DILocation(line: 410, column: 44, scope: !222)
!2257 = !DILocation(line: 410, column: 52, scope: !222)
!2258 = !DILocation(line: 410, column: 6, scope: !222)
!2259 = !DILocation(line: 410, column: 4, scope: !222)
!2260 = !DILocation(line: 411, column: 6, scope: !2261)
!2261 = distinct !DILexicalBlock(scope: !222, file: !1, line: 411, column: 6)
!2262 = !DILocation(line: 411, column: 8, scope: !2261)
!2263 = !DILocation(line: 411, column: 6, scope: !222)
!2264 = !DILocation(line: 412, column: 7, scope: !2265)
!2265 = distinct !DILexicalBlock(scope: !2266, file: !1, line: 412, column: 7)
!2266 = distinct !DILexicalBlock(scope: !2261, file: !1, line: 411, column: 14)
!2267 = !DILocation(line: 412, column: 13, scope: !2265)
!2268 = !DILocation(line: 412, column: 7, scope: !2266)
!2269 = !DILocation(line: 413, column: 23, scope: !2270)
!2270 = distinct !DILexicalBlock(scope: !2265, file: !1, line: 412, column: 24)
!2271 = !DILocation(line: 413, column: 26, scope: !2270)
!2272 = !DILocation(line: 413, column: 4, scope: !2270)
!2273 = !DILocation(line: 415, column: 4, scope: !2270)
!2274 = !DILocation(line: 417, column: 3, scope: !2266)
!2275 = !DILocation(line: 419, column: 2, scope: !222)
!2276 = !DILocation(line: 420, column: 1, scope: !222)
!2277 = !DILocalVariable(name: "pax", arg: 1, scope: !226, file: !1, line: 1916, type: !192)
!2278 = !DILocation(line: 1916, column: 31, scope: !226)
!2279 = !DILocation(line: 1918, column: 2, scope: !226)
!2280 = !DILocation(line: 1918, column: 9, scope: !2281)
!2281 = !DILexicalBlockFile(scope: !226, file: !1, discriminator: 1)
!2282 = !DILocation(line: 1918, column: 14, scope: !2281)
!2283 = !DILocation(line: 1918, column: 26, scope: !2281)
!2284 = !DILocation(line: 1918, column: 2, scope: !2281)
!2285 = !DILocalVariable(name: "sb", scope: !2286, file: !1, line: 1919, type: !203)
!2286 = distinct !DILexicalBlock(scope: !226, file: !1, line: 1918, column: 35)
!2287 = !DILocation(line: 1919, column: 24, scope: !2286)
!2288 = !DILocation(line: 1919, column: 29, scope: !2286)
!2289 = !DILocation(line: 1919, column: 34, scope: !2286)
!2290 = !DILocation(line: 1920, column: 22, scope: !2286)
!2291 = !DILocation(line: 1920, column: 26, scope: !2286)
!2292 = !DILocation(line: 1920, column: 3, scope: !2286)
!2293 = !DILocation(line: 1920, column: 8, scope: !2286)
!2294 = !DILocation(line: 1920, column: 20, scope: !2286)
!2295 = !DILocation(line: 1921, column: 8, scope: !2286)
!2296 = !DILocation(line: 1921, column: 3, scope: !2286)
!2297 = !DILocation(line: 1918, column: 2, scope: !2298)
!2298 = !DILexicalBlockFile(scope: !226, file: !1, discriminator: 2)
!2299 = !DILocation(line: 1923, column: 2, scope: !226)
!2300 = !DILocation(line: 1923, column: 7, scope: !226)
!2301 = !DILocation(line: 1923, column: 19, scope: !226)
!2302 = !DILocation(line: 1924, column: 1, scope: !226)
!2303 = !DILocalVariable(name: "a", arg: 1, scope: !229, file: !1, line: 423, type: !4)
!2304 = !DILocation(line: 423, column: 42, scope: !229)
!2305 = !DILocalVariable(name: "entry", arg: 2, scope: !229, file: !1, line: 423, type: !30)
!2306 = !DILocation(line: 423, column: 67, scope: !229)
!2307 = !DILocalVariable(name: "name", arg: 3, scope: !229, file: !1, line: 424, type: !225)
!2308 = !DILocation(line: 424, column: 18, scope: !229)
!2309 = !DILocalVariable(name: "length", arg: 4, scope: !229, file: !1, line: 424, type: !65)
!2310 = !DILocation(line: 424, column: 32, scope: !229)
!2311 = !DILocalVariable(name: "sc", arg: 5, scope: !229, file: !1, line: 424, type: !102)
!2312 = !DILocation(line: 424, column: 68, scope: !229)
!2313 = !DILocalVariable(name: "r", scope: !229, file: !1, line: 426, type: !23)
!2314 = !DILocation(line: 426, column: 6, scope: !229)
!2315 = !DILocation(line: 428, column: 31, scope: !229)
!2316 = !DILocation(line: 428, column: 38, scope: !229)
!2317 = !DILocation(line: 428, column: 44, scope: !229)
!2318 = !DILocation(line: 428, column: 52, scope: !229)
!2319 = !DILocation(line: 428, column: 6, scope: !229)
!2320 = !DILocation(line: 428, column: 4, scope: !229)
!2321 = !DILocation(line: 429, column: 6, scope: !2322)
!2322 = distinct !DILexicalBlock(scope: !229, file: !1, line: 429, column: 6)
!2323 = !DILocation(line: 429, column: 8, scope: !2322)
!2324 = !DILocation(line: 429, column: 6, scope: !229)
!2325 = !DILocation(line: 430, column: 7, scope: !2326)
!2326 = distinct !DILexicalBlock(scope: !2327, file: !1, line: 430, column: 7)
!2327 = distinct !DILexicalBlock(scope: !2322, file: !1, line: 429, column: 14)
!2328 = !DILocation(line: 430, column: 13, scope: !2326)
!2329 = !DILocation(line: 430, column: 7, scope: !2327)
!2330 = !DILocation(line: 431, column: 23, scope: !2331)
!2331 = distinct !DILexicalBlock(scope: !2326, file: !1, line: 430, column: 24)
!2332 = !DILocation(line: 431, column: 26, scope: !2331)
!2333 = !DILocation(line: 431, column: 4, scope: !2331)
!2334 = !DILocation(line: 433, column: 4, scope: !2331)
!2335 = !DILocation(line: 435, column: 3, scope: !2327)
!2336 = !DILocation(line: 437, column: 2, scope: !229)
!2337 = !DILocation(line: 438, column: 1, scope: !229)
!2338 = !DILocalVariable(name: "a", arg: 1, scope: !230, file: !1, line: 441, type: !4)
!2339 = !DILocation(line: 441, column: 39, scope: !230)
!2340 = !DILocalVariable(name: "entry", arg: 2, scope: !230, file: !1, line: 441, type: !30)
!2341 = !DILocation(line: 441, column: 64, scope: !230)
!2342 = !DILocalVariable(name: "name", arg: 3, scope: !230, file: !1, line: 442, type: !225)
!2343 = !DILocation(line: 442, column: 18, scope: !230)
!2344 = !DILocalVariable(name: "length", arg: 4, scope: !230, file: !1, line: 442, type: !65)
!2345 = !DILocation(line: 442, column: 32, scope: !230)
!2346 = !DILocalVariable(name: "sc", arg: 5, scope: !230, file: !1, line: 442, type: !102)
!2347 = !DILocation(line: 442, column: 68, scope: !230)
!2348 = !DILocalVariable(name: "r", scope: !230, file: !1, line: 444, type: !23)
!2349 = !DILocation(line: 444, column: 6, scope: !230)
!2350 = !DILocation(line: 446, column: 28, scope: !230)
!2351 = !DILocation(line: 446, column: 35, scope: !230)
!2352 = !DILocation(line: 446, column: 41, scope: !230)
!2353 = !DILocation(line: 446, column: 49, scope: !230)
!2354 = !DILocation(line: 446, column: 6, scope: !230)
!2355 = !DILocation(line: 446, column: 4, scope: !230)
!2356 = !DILocation(line: 447, column: 6, scope: !2357)
!2357 = distinct !DILexicalBlock(scope: !230, file: !1, line: 447, column: 6)
!2358 = !DILocation(line: 447, column: 8, scope: !2357)
!2359 = !DILocation(line: 447, column: 6, scope: !230)
!2360 = !DILocation(line: 448, column: 7, scope: !2361)
!2361 = distinct !DILexicalBlock(scope: !2362, file: !1, line: 448, column: 7)
!2362 = distinct !DILexicalBlock(scope: !2357, file: !1, line: 447, column: 14)
!2363 = !DILocation(line: 448, column: 13, scope: !2361)
!2364 = !DILocation(line: 448, column: 7, scope: !2362)
!2365 = !DILocation(line: 449, column: 23, scope: !2366)
!2366 = distinct !DILexicalBlock(scope: !2361, file: !1, line: 448, column: 24)
!2367 = !DILocation(line: 449, column: 26, scope: !2366)
!2368 = !DILocation(line: 449, column: 4, scope: !2366)
!2369 = !DILocation(line: 451, column: 4, scope: !2366)
!2370 = !DILocation(line: 453, column: 3, scope: !2362)
!2371 = !DILocation(line: 455, column: 2, scope: !230)
!2372 = !DILocation(line: 456, column: 1, scope: !230)
!2373 = !DILocalVariable(name: "a", arg: 1, scope: !231, file: !1, line: 459, type: !4)
!2374 = !DILocation(line: 459, column: 39, scope: !231)
!2375 = !DILocalVariable(name: "entry", arg: 2, scope: !231, file: !1, line: 459, type: !30)
!2376 = !DILocation(line: 459, column: 64, scope: !231)
!2377 = !DILocalVariable(name: "name", arg: 3, scope: !231, file: !1, line: 460, type: !225)
!2378 = !DILocation(line: 460, column: 18, scope: !231)
!2379 = !DILocalVariable(name: "length", arg: 4, scope: !231, file: !1, line: 460, type: !65)
!2380 = !DILocation(line: 460, column: 32, scope: !231)
!2381 = !DILocalVariable(name: "sc", arg: 5, scope: !231, file: !1, line: 460, type: !102)
!2382 = !DILocation(line: 460, column: 68, scope: !231)
!2383 = !DILocalVariable(name: "r", scope: !231, file: !1, line: 462, type: !23)
!2384 = !DILocation(line: 462, column: 6, scope: !231)
!2385 = !DILocation(line: 464, column: 28, scope: !231)
!2386 = !DILocation(line: 464, column: 35, scope: !231)
!2387 = !DILocation(line: 464, column: 41, scope: !231)
!2388 = !DILocation(line: 464, column: 49, scope: !231)
!2389 = !DILocation(line: 464, column: 6, scope: !231)
!2390 = !DILocation(line: 464, column: 4, scope: !231)
!2391 = !DILocation(line: 465, column: 6, scope: !2392)
!2392 = distinct !DILexicalBlock(scope: !231, file: !1, line: 465, column: 6)
!2393 = !DILocation(line: 465, column: 8, scope: !2392)
!2394 = !DILocation(line: 465, column: 6, scope: !231)
!2395 = !DILocation(line: 466, column: 7, scope: !2396)
!2396 = distinct !DILexicalBlock(scope: !2397, file: !1, line: 466, column: 7)
!2397 = distinct !DILexicalBlock(scope: !2392, file: !1, line: 465, column: 14)
!2398 = !DILocation(line: 466, column: 13, scope: !2396)
!2399 = !DILocation(line: 466, column: 7, scope: !2397)
!2400 = !DILocation(line: 467, column: 23, scope: !2401)
!2401 = distinct !DILexicalBlock(scope: !2396, file: !1, line: 466, column: 24)
!2402 = !DILocation(line: 467, column: 26, scope: !2401)
!2403 = !DILocation(line: 467, column: 4, scope: !2401)
!2404 = !DILocation(line: 469, column: 4, scope: !2401)
!2405 = !DILocation(line: 471, column: 3, scope: !2397)
!2406 = !DILocation(line: 473, column: 2, scope: !231)
!2407 = !DILocation(line: 474, column: 1, scope: !231)
!2408 = !DILocalVariable(name: "a", arg: 1, scope: !232, file: !1, line: 477, type: !4)
!2409 = !DILocation(line: 477, column: 41, scope: !232)
!2410 = !DILocalVariable(name: "entry", arg: 2, scope: !232, file: !1, line: 477, type: !30)
!2411 = !DILocation(line: 477, column: 66, scope: !232)
!2412 = !DILocalVariable(name: "name", arg: 3, scope: !232, file: !1, line: 478, type: !225)
!2413 = !DILocation(line: 478, column: 18, scope: !232)
!2414 = !DILocalVariable(name: "length", arg: 4, scope: !232, file: !1, line: 478, type: !65)
!2415 = !DILocation(line: 478, column: 32, scope: !232)
!2416 = !DILocalVariable(name: "sc", arg: 5, scope: !232, file: !1, line: 478, type: !102)
!2417 = !DILocation(line: 478, column: 68, scope: !232)
!2418 = !DILocalVariable(name: "r", scope: !232, file: !1, line: 480, type: !23)
!2419 = !DILocation(line: 480, column: 6, scope: !232)
!2420 = !DILocation(line: 482, column: 30, scope: !232)
!2421 = !DILocation(line: 482, column: 37, scope: !232)
!2422 = !DILocation(line: 482, column: 43, scope: !232)
!2423 = !DILocation(line: 482, column: 51, scope: !232)
!2424 = !DILocation(line: 482, column: 6, scope: !232)
!2425 = !DILocation(line: 482, column: 4, scope: !232)
!2426 = !DILocation(line: 483, column: 6, scope: !2427)
!2427 = distinct !DILexicalBlock(scope: !232, file: !1, line: 483, column: 6)
!2428 = !DILocation(line: 483, column: 8, scope: !2427)
!2429 = !DILocation(line: 483, column: 6, scope: !232)
!2430 = !DILocation(line: 484, column: 7, scope: !2431)
!2431 = distinct !DILexicalBlock(scope: !2432, file: !1, line: 484, column: 7)
!2432 = distinct !DILexicalBlock(scope: !2427, file: !1, line: 483, column: 14)
!2433 = !DILocation(line: 484, column: 13, scope: !2431)
!2434 = !DILocation(line: 484, column: 7, scope: !2432)
!2435 = !DILocation(line: 485, column: 23, scope: !2436)
!2436 = distinct !DILexicalBlock(scope: !2431, file: !1, line: 484, column: 24)
!2437 = !DILocation(line: 485, column: 26, scope: !2436)
!2438 = !DILocation(line: 485, column: 4, scope: !2436)
!2439 = !DILocation(line: 487, column: 4, scope: !2436)
!2440 = !DILocation(line: 489, column: 3, scope: !2432)
!2441 = !DILocation(line: 491, column: 2, scope: !232)
!2442 = !DILocation(line: 492, column: 1, scope: !232)
!2443 = !DILocalVariable(name: "as", arg: 1, scope: !233, file: !1, line: 285, type: !236)
!2444 = !DILocation(line: 285, column: 37, scope: !233)
!2445 = !DILocalVariable(name: "key", arg: 2, scope: !233, file: !1, line: 285, type: !80)
!2446 = !DILocation(line: 285, column: 53, scope: !233)
!2447 = !DILocalVariable(name: "value", arg: 3, scope: !233, file: !1, line: 285, type: !80)
!2448 = !DILocation(line: 285, column: 70, scope: !233)
!2449 = !DILocation(line: 287, column: 22, scope: !233)
!2450 = !DILocation(line: 287, column: 26, scope: !233)
!2451 = !DILocation(line: 287, column: 31, scope: !233)
!2452 = !DILocation(line: 287, column: 45, scope: !233)
!2453 = !DILocation(line: 287, column: 38, scope: !233)
!2454 = !DILocation(line: 287, column: 2, scope: !2455)
!2455 = !DILexicalBlockFile(scope: !233, file: !1, discriminator: 1)
!2456 = !DILocation(line: 288, column: 1, scope: !233)
!2457 = !DILocalVariable(name: "_p", arg: 1, scope: !243, file: !1, line: 1809, type: !80)
!2458 = !DILocation(line: 1809, column: 27, scope: !243)
!2459 = !DILocalVariable(name: "p", scope: !243, file: !1, line: 1811, type: !115)
!2460 = !DILocation(line: 1811, column: 23, scope: !243)
!2461 = !DILocation(line: 1811, column: 50, scope: !243)
!2462 = !DILocation(line: 1813, column: 6, scope: !2463)
!2463 = distinct !DILexicalBlock(scope: !243, file: !1, line: 1813, column: 6)
!2464 = !DILocation(line: 1813, column: 8, scope: !2463)
!2465 = !DILocation(line: 1813, column: 6, scope: !243)
!2466 = !DILocation(line: 1814, column: 3, scope: !2463)
!2467 = !DILocation(line: 1815, column: 2, scope: !243)
!2468 = !DILocation(line: 1815, column: 10, scope: !2469)
!2469 = !DILexicalBlockFile(scope: !243, file: !1, discriminator: 1)
!2470 = !DILocation(line: 1815, column: 9, scope: !2469)
!2471 = !DILocation(line: 1815, column: 12, scope: !2469)
!2472 = !DILocation(line: 1815, column: 20, scope: !2469)
!2473 = !DILocation(line: 1815, column: 24, scope: !2474)
!2474 = !DILexicalBlockFile(scope: !243, file: !1, discriminator: 2)
!2475 = !DILocation(line: 1815, column: 23, scope: !2474)
!2476 = !DILocation(line: 1815, column: 26, scope: !2474)
!2477 = !DILocation(line: 1815, column: 2, scope: !2478)
!2478 = !DILexicalBlockFile(scope: !243, file: !1, discriminator: 3)
!2479 = !DILocation(line: 1816, column: 4, scope: !243)
!2480 = !DILocation(line: 1815, column: 2, scope: !2481)
!2481 = !DILexicalBlockFile(scope: !243, file: !1, discriminator: 4)
!2482 = !DILocation(line: 1817, column: 11, scope: !243)
!2483 = !DILocation(line: 1817, column: 10, scope: !243)
!2484 = !DILocation(line: 1817, column: 13, scope: !243)
!2485 = !DILocation(line: 1817, column: 2, scope: !243)
!2486 = !DILocation(line: 1818, column: 1, scope: !243)
!2487 = !DILocalVariable(name: "dest", arg: 1, scope: !246, file: !1, line: 1458, type: !95)
!2488 = !DILocation(line: 1458, column: 30, scope: !246)
!2489 = !DILocalVariable(name: "src", arg: 2, scope: !246, file: !1, line: 1458, type: !80)
!2490 = !DILocation(line: 1458, column: 48, scope: !246)
!2491 = !DILocalVariable(name: "src_length", arg: 3, scope: !246, file: !1, line: 1458, type: !45)
!2492 = !DILocation(line: 1458, column: 60, scope: !246)
!2493 = !DILocalVariable(name: "insert", arg: 4, scope: !246, file: !1, line: 1459, type: !80)
!2494 = !DILocation(line: 1459, column: 17, scope: !246)
!2495 = !DILocalVariable(name: "prefix", scope: !246, file: !1, line: 1461, type: !80)
!2496 = !DILocation(line: 1461, column: 14, scope: !246)
!2497 = !DILocalVariable(name: "prefix_end", scope: !246, file: !1, line: 1461, type: !80)
!2498 = !DILocation(line: 1461, column: 23, scope: !246)
!2499 = !DILocalVariable(name: "suffix", scope: !246, file: !1, line: 1462, type: !80)
!2500 = !DILocation(line: 1462, column: 14, scope: !246)
!2501 = !DILocalVariable(name: "suffix_end", scope: !246, file: !1, line: 1462, type: !80)
!2502 = !DILocation(line: 1462, column: 23, scope: !246)
!2503 = !DILocalVariable(name: "filename", scope: !246, file: !1, line: 1463, type: !80)
!2504 = !DILocation(line: 1463, column: 14, scope: !246)
!2505 = !DILocalVariable(name: "filename_end", scope: !246, file: !1, line: 1463, type: !80)
!2506 = !DILocation(line: 1463, column: 25, scope: !246)
!2507 = !DILocalVariable(name: "p", scope: !246, file: !1, line: 1464, type: !95)
!2508 = !DILocation(line: 1464, column: 8, scope: !246)
!2509 = !DILocalVariable(name: "need_slash", scope: !246, file: !1, line: 1465, type: !23)
!2510 = !DILocation(line: 1465, column: 6, scope: !246)
!2511 = !DILocalVariable(name: "suffix_length", scope: !246, file: !1, line: 1466, type: !45)
!2512 = !DILocation(line: 1466, column: 9, scope: !246)
!2513 = !DILocalVariable(name: "insert_length", scope: !246, file: !1, line: 1467, type: !45)
!2514 = !DILocation(line: 1467, column: 9, scope: !246)
!2515 = !DILocation(line: 1470, column: 6, scope: !2516)
!2516 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1470, column: 6)
!2517 = !DILocation(line: 1470, column: 13, scope: !2516)
!2518 = !DILocation(line: 1470, column: 6, scope: !246)
!2519 = !DILocation(line: 1471, column: 17, scope: !2516)
!2520 = !DILocation(line: 1471, column: 3, scope: !2516)
!2521 = !DILocation(line: 1474, column: 26, scope: !2516)
!2522 = !DILocation(line: 1474, column: 19, scope: !2516)
!2523 = !DILocation(line: 1474, column: 34, scope: !2516)
!2524 = !DILocation(line: 1474, column: 17, scope: !2516)
!2525 = !DILocation(line: 1477, column: 6, scope: !2526)
!2526 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1477, column: 6)
!2527 = !DILocation(line: 1477, column: 17, scope: !2526)
!2528 = !DILocation(line: 1477, column: 23, scope: !2526)
!2529 = !DILocation(line: 1477, column: 26, scope: !2530)
!2530 = !DILexicalBlockFile(scope: !2526, file: !1, discriminator: 1)
!2531 = !DILocation(line: 1477, column: 33, scope: !2530)
!2532 = !DILocation(line: 1477, column: 6, scope: !2530)
!2533 = !DILocation(line: 1478, column: 11, scope: !2534)
!2534 = distinct !DILexicalBlock(scope: !2526, file: !1, line: 1477, column: 42)
!2535 = !DILocation(line: 1478, column: 17, scope: !2534)
!2536 = !DILocation(line: 1478, column: 22, scope: !2534)
!2537 = !DILocation(line: 1478, column: 3, scope: !2534)
!2538 = !DILocation(line: 1479, column: 8, scope: !2534)
!2539 = !DILocation(line: 1479, column: 3, scope: !2534)
!2540 = !DILocation(line: 1479, column: 20, scope: !2534)
!2541 = !DILocation(line: 1480, column: 11, scope: !2534)
!2542 = !DILocation(line: 1480, column: 3, scope: !2534)
!2543 = !DILocation(line: 1484, column: 17, scope: !246)
!2544 = !DILocation(line: 1484, column: 23, scope: !246)
!2545 = !DILocation(line: 1484, column: 21, scope: !246)
!2546 = !DILocation(line: 1484, column: 15, scope: !246)
!2547 = !DILocation(line: 1486, column: 2, scope: !246)
!2548 = !DILocation(line: 1487, column: 7, scope: !2549)
!2549 = distinct !DILexicalBlock(scope: !2550, file: !1, line: 1487, column: 7)
!2550 = distinct !DILexicalBlock(scope: !2551, file: !1, line: 1486, column: 11)
!2551 = distinct !DILexicalBlock(scope: !2552, file: !1, line: 1486, column: 2)
!2552 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1486, column: 2)
!2553 = !DILocation(line: 1487, column: 22, scope: !2549)
!2554 = !DILocation(line: 1487, column: 20, scope: !2549)
!2555 = !DILocation(line: 1487, column: 26, scope: !2549)
!2556 = !DILocation(line: 1487, column: 29, scope: !2557)
!2557 = !DILexicalBlockFile(scope: !2549, file: !1, discriminator: 1)
!2558 = !DILocation(line: 1487, column: 46, scope: !2557)
!2559 = !DILocation(line: 1487, column: 7, scope: !2557)
!2560 = !DILocation(line: 1488, column: 17, scope: !2561)
!2561 = distinct !DILexicalBlock(scope: !2549, file: !1, line: 1487, column: 54)
!2562 = !DILocation(line: 1489, column: 15, scope: !2561)
!2563 = !DILocation(line: 1490, column: 4, scope: !2561)
!2564 = !DILocation(line: 1492, column: 7, scope: !2565)
!2565 = distinct !DILexicalBlock(scope: !2550, file: !1, line: 1492, column: 7)
!2566 = !DILocation(line: 1492, column: 22, scope: !2565)
!2567 = !DILocation(line: 1492, column: 26, scope: !2565)
!2568 = !DILocation(line: 1492, column: 20, scope: !2565)
!2569 = !DILocation(line: 1492, column: 30, scope: !2565)
!2570 = !DILocation(line: 1492, column: 33, scope: !2571)
!2571 = !DILexicalBlockFile(scope: !2565, file: !1, discriminator: 1)
!2572 = !DILocation(line: 1492, column: 50, scope: !2571)
!2573 = !DILocation(line: 1493, column: 7, scope: !2565)
!2574 = !DILocation(line: 1493, column: 10, scope: !2571)
!2575 = !DILocation(line: 1493, column: 27, scope: !2571)
!2576 = !DILocation(line: 1492, column: 7, scope: !2577)
!2577 = !DILexicalBlockFile(scope: !2550, file: !1, discriminator: 2)
!2578 = !DILocation(line: 1494, column: 17, scope: !2579)
!2579 = distinct !DILexicalBlock(scope: !2565, file: !1, line: 1493, column: 35)
!2580 = !DILocation(line: 1495, column: 15, scope: !2579)
!2581 = !DILocation(line: 1496, column: 4, scope: !2579)
!2582 = !DILocation(line: 1498, column: 3, scope: !2550)
!2583 = !DILocation(line: 1500, column: 6, scope: !2584)
!2584 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1500, column: 6)
!2585 = !DILocation(line: 1500, column: 6, scope: !246)
!2586 = !DILocation(line: 1501, column: 16, scope: !2584)
!2587 = !DILocation(line: 1501, column: 3, scope: !2584)
!2588 = !DILocation(line: 1503, column: 13, scope: !246)
!2589 = !DILocation(line: 1503, column: 26, scope: !246)
!2590 = !DILocation(line: 1503, column: 11, scope: !246)
!2591 = !DILocation(line: 1504, column: 2, scope: !246)
!2592 = !DILocation(line: 1504, column: 10, scope: !2593)
!2593 = !DILexicalBlockFile(scope: !246, file: !1, discriminator: 1)
!2594 = !DILocation(line: 1504, column: 21, scope: !2593)
!2595 = !DILocation(line: 1504, column: 19, scope: !2593)
!2596 = !DILocation(line: 1504, column: 26, scope: !2593)
!2597 = !DILocation(line: 1504, column: 31, scope: !2598)
!2598 = !DILexicalBlockFile(scope: !246, file: !1, discriminator: 2)
!2599 = !DILocation(line: 1504, column: 30, scope: !2598)
!2600 = !DILocation(line: 1504, column: 40, scope: !2598)
!2601 = !DILocation(line: 1504, column: 2, scope: !2602)
!2602 = !DILexicalBlockFile(scope: !246, file: !1, discriminator: 3)
!2603 = !DILocation(line: 1505, column: 12, scope: !246)
!2604 = !DILocation(line: 1504, column: 2, scope: !2605)
!2605 = !DILexicalBlockFile(scope: !246, file: !1, discriminator: 4)
!2606 = !DILocation(line: 1506, column: 8, scope: !2607)
!2607 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1506, column: 6)
!2608 = !DILocation(line: 1506, column: 7, scope: !2607)
!2609 = !DILocation(line: 1506, column: 17, scope: !2607)
!2610 = !DILocation(line: 1506, column: 25, scope: !2607)
!2611 = !DILocation(line: 1506, column: 29, scope: !2612)
!2612 = !DILexicalBlockFile(scope: !2607, file: !1, discriminator: 1)
!2613 = !DILocation(line: 1506, column: 40, scope: !2612)
!2614 = !DILocation(line: 1506, column: 53, scope: !2612)
!2615 = !DILocation(line: 1506, column: 38, scope: !2612)
!2616 = !DILocation(line: 1506, column: 6, scope: !2612)
!2617 = !DILocation(line: 1507, column: 12, scope: !2607)
!2618 = !DILocation(line: 1507, column: 3, scope: !2607)
!2619 = !DILocation(line: 1509, column: 19, scope: !246)
!2620 = !DILocation(line: 1509, column: 16, scope: !246)
!2621 = !DILocation(line: 1510, column: 6, scope: !2622)
!2622 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1510, column: 6)
!2623 = !DILocation(line: 1510, column: 21, scope: !2622)
!2624 = !DILocation(line: 1510, column: 32, scope: !2622)
!2625 = !DILocation(line: 1510, column: 30, scope: !2622)
!2626 = !DILocation(line: 1510, column: 19, scope: !2622)
!2627 = !DILocation(line: 1510, column: 6, scope: !246)
!2628 = !DILocation(line: 1511, column: 18, scope: !2622)
!2629 = !DILocation(line: 1511, column: 29, scope: !2622)
!2630 = !DILocation(line: 1511, column: 27, scope: !2622)
!2631 = !DILocation(line: 1511, column: 16, scope: !2622)
!2632 = !DILocation(line: 1511, column: 3, scope: !2622)
!2633 = !DILocation(line: 1513, column: 19, scope: !246)
!2634 = !DILocation(line: 1513, column: 34, scope: !246)
!2635 = !DILocation(line: 1513, column: 32, scope: !246)
!2636 = !DILocation(line: 1513, column: 16, scope: !246)
!2637 = !DILocation(line: 1517, column: 11, scope: !246)
!2638 = !DILocation(line: 1517, column: 9, scope: !246)
!2639 = !DILocation(line: 1518, column: 15, scope: !246)
!2640 = !DILocation(line: 1518, column: 22, scope: !246)
!2641 = !DILocation(line: 1518, column: 13, scope: !246)
!2642 = !DILocation(line: 1519, column: 6, scope: !2643)
!2643 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1519, column: 6)
!2644 = !DILocation(line: 1519, column: 19, scope: !2643)
!2645 = !DILocation(line: 1519, column: 17, scope: !2643)
!2646 = !DILocation(line: 1519, column: 6, scope: !246)
!2647 = !DILocation(line: 1520, column: 16, scope: !2643)
!2648 = !DILocation(line: 1520, column: 14, scope: !2643)
!2649 = !DILocation(line: 1520, column: 3, scope: !2643)
!2650 = !DILocation(line: 1521, column: 2, scope: !246)
!2651 = !DILocation(line: 1521, column: 9, scope: !2593)
!2652 = !DILocation(line: 1521, column: 22, scope: !2593)
!2653 = !DILocation(line: 1521, column: 20, scope: !2593)
!2654 = !DILocation(line: 1521, column: 29, scope: !2593)
!2655 = !DILocation(line: 1521, column: 33, scope: !2598)
!2656 = !DILocation(line: 1521, column: 32, scope: !2598)
!2657 = !DILocation(line: 1521, column: 44, scope: !2598)
!2658 = !DILocation(line: 1521, column: 2, scope: !2602)
!2659 = !DILocation(line: 1522, column: 13, scope: !246)
!2660 = !DILocation(line: 1521, column: 2, scope: !2605)
!2661 = !DILocation(line: 1523, column: 7, scope: !2662)
!2662 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1523, column: 6)
!2663 = !DILocation(line: 1523, column: 20, scope: !2662)
!2664 = !DILocation(line: 1523, column: 18, scope: !2662)
!2665 = !DILocation(line: 1523, column: 30, scope: !2662)
!2666 = !DILocation(line: 1523, column: 35, scope: !2667)
!2667 = !DILexicalBlockFile(scope: !2662, file: !1, discriminator: 1)
!2668 = !DILocation(line: 1523, column: 34, scope: !2667)
!2669 = !DILocation(line: 1523, column: 46, scope: !2667)
!2670 = !DILocation(line: 1523, column: 6, scope: !2667)
!2671 = !DILocation(line: 1524, column: 13, scope: !2662)
!2672 = !DILocation(line: 1524, column: 3, scope: !2662)
!2673 = !DILocation(line: 1528, column: 11, scope: !246)
!2674 = !DILocation(line: 1528, column: 9, scope: !246)
!2675 = !DILocation(line: 1529, column: 15, scope: !246)
!2676 = !DILocation(line: 1529, column: 24, scope: !246)
!2677 = !DILocation(line: 1529, column: 22, scope: !246)
!2678 = !DILocation(line: 1529, column: 13, scope: !246)
!2679 = !DILocation(line: 1530, column: 6, scope: !2680)
!2680 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1530, column: 6)
!2681 = !DILocation(line: 1530, column: 19, scope: !2680)
!2682 = !DILocation(line: 1530, column: 17, scope: !2680)
!2683 = !DILocation(line: 1530, column: 6, scope: !246)
!2684 = !DILocation(line: 1531, column: 16, scope: !2680)
!2685 = !DILocation(line: 1531, column: 14, scope: !2680)
!2686 = !DILocation(line: 1531, column: 3, scope: !2680)
!2687 = !DILocation(line: 1532, column: 6, scope: !2688)
!2688 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1532, column: 6)
!2689 = !DILocation(line: 1532, column: 19, scope: !2688)
!2690 = !DILocation(line: 1532, column: 17, scope: !2688)
!2691 = !DILocation(line: 1532, column: 6, scope: !246)
!2692 = !DILocation(line: 1533, column: 16, scope: !2688)
!2693 = !DILocation(line: 1533, column: 14, scope: !2688)
!2694 = !DILocation(line: 1533, column: 3, scope: !2688)
!2695 = !DILocation(line: 1534, column: 2, scope: !246)
!2696 = !DILocation(line: 1534, column: 9, scope: !2593)
!2697 = !DILocation(line: 1534, column: 22, scope: !2593)
!2698 = !DILocation(line: 1534, column: 20, scope: !2593)
!2699 = !DILocation(line: 1534, column: 29, scope: !2593)
!2700 = !DILocation(line: 1534, column: 33, scope: !2598)
!2701 = !DILocation(line: 1534, column: 32, scope: !2598)
!2702 = !DILocation(line: 1534, column: 44, scope: !2598)
!2703 = !DILocation(line: 1534, column: 2, scope: !2602)
!2704 = !DILocation(line: 1535, column: 13, scope: !246)
!2705 = !DILocation(line: 1534, column: 2, scope: !2605)
!2706 = !DILocation(line: 1536, column: 7, scope: !2707)
!2707 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1536, column: 6)
!2708 = !DILocation(line: 1536, column: 20, scope: !2707)
!2709 = !DILocation(line: 1536, column: 18, scope: !2707)
!2710 = !DILocation(line: 1536, column: 30, scope: !2707)
!2711 = !DILocation(line: 1536, column: 35, scope: !2712)
!2712 = !DILexicalBlockFile(scope: !2707, file: !1, discriminator: 1)
!2713 = !DILocation(line: 1536, column: 34, scope: !2712)
!2714 = !DILocation(line: 1536, column: 46, scope: !2712)
!2715 = !DILocation(line: 1536, column: 6, scope: !2712)
!2716 = !DILocation(line: 1537, column: 13, scope: !2707)
!2717 = !DILocation(line: 1537, column: 3, scope: !2707)
!2718 = !DILocation(line: 1542, column: 6, scope: !246)
!2719 = !DILocation(line: 1542, column: 4, scope: !246)
!2720 = !DILocation(line: 1543, column: 6, scope: !2721)
!2721 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1543, column: 6)
!2722 = !DILocation(line: 1543, column: 19, scope: !2721)
!2723 = !DILocation(line: 1543, column: 17, scope: !2721)
!2724 = !DILocation(line: 1543, column: 6, scope: !246)
!2725 = !DILocation(line: 1544, column: 11, scope: !2726)
!2726 = distinct !DILexicalBlock(scope: !2721, file: !1, line: 1543, column: 27)
!2727 = !DILocation(line: 1544, column: 14, scope: !2726)
!2728 = !DILocation(line: 1544, column: 22, scope: !2726)
!2729 = !DILocation(line: 1544, column: 35, scope: !2726)
!2730 = !DILocation(line: 1544, column: 33, scope: !2726)
!2731 = !DILocation(line: 1544, column: 3, scope: !2726)
!2732 = !DILocation(line: 1545, column: 8, scope: !2726)
!2733 = !DILocation(line: 1545, column: 21, scope: !2726)
!2734 = !DILocation(line: 1545, column: 19, scope: !2726)
!2735 = !DILocation(line: 1545, column: 5, scope: !2726)
!2736 = !DILocation(line: 1546, column: 2, scope: !2726)
!2737 = !DILocation(line: 1547, column: 6, scope: !2738)
!2738 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1547, column: 6)
!2739 = !DILocation(line: 1547, column: 19, scope: !2738)
!2740 = !DILocation(line: 1547, column: 17, scope: !2738)
!2741 = !DILocation(line: 1547, column: 6, scope: !246)
!2742 = !DILocation(line: 1548, column: 11, scope: !2743)
!2743 = distinct !DILexicalBlock(scope: !2738, file: !1, line: 1547, column: 27)
!2744 = !DILocation(line: 1548, column: 14, scope: !2743)
!2745 = !DILocation(line: 1548, column: 22, scope: !2743)
!2746 = !DILocation(line: 1548, column: 35, scope: !2743)
!2747 = !DILocation(line: 1548, column: 33, scope: !2743)
!2748 = !DILocation(line: 1548, column: 3, scope: !2743)
!2749 = !DILocation(line: 1549, column: 8, scope: !2743)
!2750 = !DILocation(line: 1549, column: 21, scope: !2743)
!2751 = !DILocation(line: 1549, column: 19, scope: !2743)
!2752 = !DILocation(line: 1549, column: 5, scope: !2743)
!2753 = !DILocation(line: 1550, column: 2, scope: !2743)
!2754 = !DILocation(line: 1551, column: 6, scope: !2755)
!2755 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1551, column: 6)
!2756 = !DILocation(line: 1551, column: 13, scope: !2755)
!2757 = !DILocation(line: 1551, column: 6, scope: !246)
!2758 = !DILocation(line: 1553, column: 10, scope: !2759)
!2759 = distinct !DILexicalBlock(scope: !2755, file: !1, line: 1551, column: 22)
!2760 = !DILocation(line: 1553, column: 13, scope: !2759)
!2761 = !DILocation(line: 1553, column: 3, scope: !2759)
!2762 = !DILocation(line: 1554, column: 15, scope: !2759)
!2763 = !DILocation(line: 1554, column: 8, scope: !2759)
!2764 = !DILocation(line: 1554, column: 5, scope: !2759)
!2765 = !DILocation(line: 1555, column: 5, scope: !2759)
!2766 = !DILocation(line: 1555, column: 8, scope: !2759)
!2767 = !DILocation(line: 1556, column: 2, scope: !2759)
!2768 = !DILocation(line: 1557, column: 10, scope: !246)
!2769 = !DILocation(line: 1557, column: 13, scope: !246)
!2770 = !DILocation(line: 1557, column: 23, scope: !246)
!2771 = !DILocation(line: 1557, column: 38, scope: !246)
!2772 = !DILocation(line: 1557, column: 36, scope: !246)
!2773 = !DILocation(line: 1557, column: 2, scope: !246)
!2774 = !DILocation(line: 1558, column: 7, scope: !246)
!2775 = !DILocation(line: 1558, column: 22, scope: !246)
!2776 = !DILocation(line: 1558, column: 20, scope: !246)
!2777 = !DILocation(line: 1558, column: 4, scope: !246)
!2778 = !DILocation(line: 1559, column: 6, scope: !2779)
!2779 = distinct !DILexicalBlock(scope: !246, file: !1, line: 1559, column: 6)
!2780 = !DILocation(line: 1559, column: 6, scope: !246)
!2781 = !DILocation(line: 1560, column: 5, scope: !2779)
!2782 = !DILocation(line: 1560, column: 8, scope: !2779)
!2783 = !DILocation(line: 1560, column: 3, scope: !2779)
!2784 = !DILocation(line: 1561, column: 3, scope: !246)
!2785 = !DILocation(line: 1561, column: 5, scope: !246)
!2786 = !DILocation(line: 1563, column: 10, scope: !246)
!2787 = !DILocation(line: 1563, column: 2, scope: !246)
!2788 = !DILocation(line: 1564, column: 1, scope: !246)
!2789 = !DILocalVariable(name: "as", arg: 1, scope: !249, file: !1, line: 272, type: !236)
!2790 = !DILocation(line: 272, column: 41, scope: !249)
!2791 = !DILocalVariable(name: "key", arg: 2, scope: !249, file: !1, line: 272, type: !80)
!2792 = !DILocation(line: 272, column: 57, scope: !249)
!2793 = !DILocalVariable(name: "value", arg: 3, scope: !249, file: !1, line: 272, type: !52)
!2794 = !DILocation(line: 272, column: 70, scope: !249)
!2795 = !DILocalVariable(name: "tmp", scope: !249, file: !1, line: 274, type: !2796)
!2796 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 200, align: 8, elements: !2797)
!2797 = !{!2798}
!2798 = !DISubrange(count: 25)
!2799 = !DILocation(line: 274, column: 7, scope: !249)
!2800 = !DILocation(line: 276, column: 2, scope: !249)
!2801 = !DILocation(line: 276, column: 23, scope: !249)
!2802 = !DILocation(line: 277, column: 15, scope: !249)
!2803 = !DILocation(line: 277, column: 19, scope: !249)
!2804 = !DILocation(line: 277, column: 35, scope: !249)
!2805 = !DILocation(line: 277, column: 39, scope: !249)
!2806 = !DILocation(line: 277, column: 53, scope: !249)
!2807 = !DILocation(line: 277, column: 58, scope: !249)
!2808 = !DILocation(line: 277, column: 24, scope: !249)
!2809 = !DILocation(line: 277, column: 2, scope: !2810)
!2810 = !DILexicalBlockFile(scope: !249, file: !1, discriminator: 1)
!2811 = !DILocation(line: 278, column: 1, scope: !249)
!2812 = !DILocalVariable(name: "as", arg: 1, scope: !252, file: !1, line: 218, type: !236)
!2813 = !DILocation(line: 218, column: 42, scope: !252)
!2814 = !DILocalVariable(name: "key", arg: 2, scope: !252, file: !1, line: 218, type: !80)
!2815 = !DILocation(line: 218, column: 58, scope: !252)
!2816 = !DILocalVariable(name: "sec", arg: 3, scope: !252, file: !1, line: 219, type: !52)
!2817 = !DILocation(line: 219, column: 13, scope: !252)
!2818 = !DILocalVariable(name: "nanos", arg: 4, scope: !252, file: !1, line: 219, type: !47)
!2819 = !DILocation(line: 219, column: 32, scope: !252)
!2820 = !DILocalVariable(name: "digit", scope: !252, file: !1, line: 221, type: !23)
!2821 = !DILocation(line: 221, column: 6, scope: !252)
!2822 = !DILocalVariable(name: "i", scope: !252, file: !1, line: 221, type: !23)
!2823 = !DILocation(line: 221, column: 13, scope: !252)
!2824 = !DILocalVariable(name: "t", scope: !252, file: !1, line: 222, type: !95)
!2825 = !DILocation(line: 222, column: 8, scope: !252)
!2826 = !DILocalVariable(name: "tmp", scope: !252, file: !1, line: 227, type: !2827)
!2827 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 400, align: 8, elements: !2828)
!2828 = !{!2829}
!2829 = !DISubrange(count: 50)
!2830 = !DILocation(line: 227, column: 7, scope: !252)
!2831 = !DILocation(line: 229, column: 2, scope: !252)
!2832 = !DILocation(line: 229, column: 23, scope: !252)
!2833 = !DILocation(line: 230, column: 6, scope: !252)
!2834 = !DILocation(line: 230, column: 10, scope: !252)
!2835 = !DILocation(line: 230, column: 24, scope: !252)
!2836 = !DILocation(line: 230, column: 4, scope: !252)
!2837 = !DILocation(line: 233, column: 13, scope: !2838)
!2838 = distinct !DILexicalBlock(scope: !252, file: !1, line: 233, column: 2)
!2839 = !DILocation(line: 233, column: 20, scope: !2838)
!2840 = !DILocation(line: 233, column: 7, scope: !2838)
!2841 = !DILocation(line: 233, column: 26, scope: !2842)
!2842 = !DILexicalBlockFile(scope: !2843, file: !1, discriminator: 1)
!2843 = distinct !DILexicalBlock(scope: !2838, file: !1, line: 233, column: 2)
!2844 = !DILocation(line: 233, column: 28, scope: !2842)
!2845 = !DILocation(line: 233, column: 32, scope: !2842)
!2846 = !DILocation(line: 233, column: 35, scope: !2847)
!2847 = !DILexicalBlockFile(scope: !2843, file: !1, discriminator: 2)
!2848 = !DILocation(line: 233, column: 41, scope: !2847)
!2849 = !DILocation(line: 233, column: 2, scope: !2850)
!2850 = !DILexicalBlockFile(scope: !2838, file: !1, discriminator: 3)
!2851 = !DILocation(line: 234, column: 11, scope: !2852)
!2852 = distinct !DILexicalBlock(scope: !2843, file: !1, line: 233, column: 52)
!2853 = !DILocation(line: 234, column: 17, scope: !2852)
!2854 = !DILocation(line: 234, column: 9, scope: !2852)
!2855 = !DILocation(line: 235, column: 9, scope: !2852)
!2856 = !DILocation(line: 236, column: 2, scope: !2852)
!2857 = !DILocation(line: 233, column: 48, scope: !2858)
!2858 = !DILexicalBlockFile(scope: !2843, file: !1, discriminator: 4)
!2859 = !DILocation(line: 233, column: 2, scope: !2858)
!2860 = !DILocation(line: 239, column: 6, scope: !2861)
!2861 = distinct !DILexicalBlock(scope: !252, file: !1, line: 239, column: 6)
!2862 = !DILocation(line: 239, column: 8, scope: !2861)
!2863 = !DILocation(line: 239, column: 6, scope: !252)
!2864 = !DILocation(line: 240, column: 3, scope: !2865)
!2865 = distinct !DILexicalBlock(scope: !2861, file: !1, line: 239, column: 13)
!2866 = !DILocation(line: 240, column: 10, scope: !2867)
!2867 = !DILexicalBlockFile(scope: !2865, file: !1, discriminator: 1)
!2868 = !DILocation(line: 240, column: 12, scope: !2867)
!2869 = !DILocation(line: 240, column: 3, scope: !2867)
!2870 = !DILocation(line: 241, column: 24, scope: !2871)
!2871 = distinct !DILexicalBlock(scope: !2865, file: !1, line: 240, column: 17)
!2872 = !DILocation(line: 241, column: 11, scope: !2871)
!2873 = !DILocation(line: 241, column: 5, scope: !2871)
!2874 = !DILocation(line: 241, column: 9, scope: !2871)
!2875 = !DILocation(line: 242, column: 12, scope: !2871)
!2876 = !DILocation(line: 242, column: 18, scope: !2871)
!2877 = !DILocation(line: 242, column: 10, scope: !2871)
!2878 = !DILocation(line: 243, column: 10, scope: !2871)
!2879 = !DILocation(line: 244, column: 5, scope: !2871)
!2880 = !DILocation(line: 240, column: 3, scope: !2881)
!2881 = !DILexicalBlockFile(scope: !2865, file: !1, discriminator: 2)
!2882 = !DILocation(line: 246, column: 4, scope: !2865)
!2883 = !DILocation(line: 246, column: 8, scope: !2865)
!2884 = !DILocation(line: 247, column: 2, scope: !2865)
!2885 = !DILocation(line: 248, column: 17, scope: !252)
!2886 = !DILocation(line: 248, column: 20, scope: !252)
!2887 = !DILocation(line: 248, column: 6, scope: !252)
!2888 = !DILocation(line: 248, column: 4, scope: !252)
!2889 = !DILocation(line: 250, column: 15, scope: !252)
!2890 = !DILocation(line: 250, column: 19, scope: !252)
!2891 = !DILocation(line: 250, column: 24, scope: !252)
!2892 = !DILocation(line: 250, column: 2, scope: !252)
!2893 = !DILocation(line: 251, column: 1, scope: !252)
!2894 = !DILocalVariable(name: "a", arg: 1, scope: !255, file: !1, line: 496, type: !4)
!2895 = !DILocation(line: 496, column: 35, scope: !255)
!2896 = !DILocalVariable(name: "entry", arg: 2, scope: !255, file: !1, line: 497, type: !30)
!2897 = !DILocation(line: 497, column: 27, scope: !255)
!2898 = !DILocalVariable(name: "pax", arg: 3, scope: !255, file: !1, line: 497, type: !192)
!2899 = !DILocation(line: 497, column: 46, scope: !255)
!2900 = !DILocalVariable(name: "flags", arg: 4, scope: !255, file: !1, line: 497, type: !23)
!2901 = !DILocation(line: 497, column: 55, scope: !255)
!2902 = !DILocalVariable(name: "p", scope: !255, file: !1, line: 499, type: !95)
!2903 = !DILocation(line: 499, column: 8, scope: !255)
!2904 = !DILocalVariable(name: "attr", scope: !255, file: !1, line: 500, type: !80)
!2905 = !DILocation(line: 500, column: 14, scope: !255)
!2906 = !DILocalVariable(name: "acl_types", scope: !255, file: !1, line: 501, type: !23)
!2907 = !DILocation(line: 501, column: 6, scope: !255)
!2908 = !DILocation(line: 503, column: 38, scope: !255)
!2909 = !DILocation(line: 503, column: 14, scope: !255)
!2910 = !DILocation(line: 503, column: 12, scope: !255)
!2911 = !DILocation(line: 505, column: 7, scope: !2912)
!2912 = distinct !DILexicalBlock(scope: !255, file: !1, line: 505, column: 6)
!2913 = !DILocation(line: 505, column: 17, scope: !2912)
!2914 = !DILocation(line: 505, column: 48, scope: !2912)
!2915 = !DILocation(line: 505, column: 6, scope: !255)
!2916 = !DILocation(line: 506, column: 8, scope: !2912)
!2917 = !DILocation(line: 506, column: 3, scope: !2912)
!2918 = !DILocation(line: 507, column: 12, scope: !2919)
!2919 = distinct !DILexicalBlock(scope: !2912, file: !1, line: 507, column: 11)
!2920 = !DILocation(line: 507, column: 18, scope: !2919)
!2921 = !DILocation(line: 507, column: 51, scope: !2919)
!2922 = !DILocation(line: 507, column: 11, scope: !2912)
!2923 = !DILocation(line: 508, column: 8, scope: !2919)
!2924 = !DILocation(line: 508, column: 3, scope: !2919)
!2925 = !DILocation(line: 509, column: 12, scope: !2926)
!2926 = distinct !DILexicalBlock(scope: !2919, file: !1, line: 509, column: 11)
!2927 = !DILocation(line: 509, column: 18, scope: !2926)
!2928 = !DILocation(line: 509, column: 52, scope: !2926)
!2929 = !DILocation(line: 509, column: 11, scope: !2919)
!2930 = !DILocation(line: 510, column: 8, scope: !2926)
!2931 = !DILocation(line: 510, column: 3, scope: !2926)
!2932 = !DILocation(line: 512, column: 3, scope: !2926)
!2933 = !DILocation(line: 514, column: 34, scope: !255)
!2934 = !DILocation(line: 514, column: 47, scope: !255)
!2935 = !DILocation(line: 514, column: 54, scope: !255)
!2936 = !DILocation(line: 514, column: 59, scope: !255)
!2937 = !DILocation(line: 514, column: 6, scope: !255)
!2938 = !DILocation(line: 514, column: 4, scope: !255)
!2939 = !DILocation(line: 515, column: 6, scope: !2940)
!2940 = distinct !DILexicalBlock(scope: !255, file: !1, line: 515, column: 6)
!2941 = !DILocation(line: 515, column: 8, scope: !2940)
!2942 = !DILocation(line: 515, column: 6, scope: !255)
!2943 = !DILocation(line: 516, column: 7, scope: !2944)
!2944 = distinct !DILexicalBlock(scope: !2945, file: !1, line: 516, column: 7)
!2945 = distinct !DILexicalBlock(scope: !2940, file: !1, line: 515, column: 17)
!2946 = !DILocation(line: 516, column: 13, scope: !2944)
!2947 = !DILocation(line: 516, column: 7, scope: !2945)
!2948 = !DILocation(line: 517, column: 23, scope: !2949)
!2949 = distinct !DILexicalBlock(scope: !2944, file: !1, line: 516, column: 24)
!2950 = !DILocation(line: 517, column: 26, scope: !2949)
!2951 = !DILocation(line: 518, column: 38, scope: !2949)
!2952 = !DILocation(line: 517, column: 4, scope: !2949)
!2953 = !DILocation(line: 519, column: 4, scope: !2949)
!2954 = !DILocation(line: 521, column: 22, scope: !2945)
!2955 = !DILocation(line: 521, column: 25, scope: !2945)
!2956 = !DILocation(line: 523, column: 27, scope: !2945)
!2957 = !DILocation(line: 521, column: 3, scope: !2945)
!2958 = !DILocation(line: 524, column: 3, scope: !2945)
!2959 = !DILocation(line: 525, column: 14, scope: !2960)
!2960 = distinct !DILexicalBlock(scope: !2940, file: !1, line: 525, column: 13)
!2961 = !DILocation(line: 525, column: 13, scope: !2960)
!2962 = !DILocation(line: 525, column: 16, scope: !2960)
!2963 = !DILocation(line: 525, column: 13, scope: !2940)
!2964 = !DILocation(line: 526, column: 18, scope: !2965)
!2965 = distinct !DILexicalBlock(scope: !2960, file: !1, line: 525, column: 25)
!2966 = !DILocation(line: 526, column: 23, scope: !2965)
!2967 = !DILocation(line: 527, column: 7, scope: !2965)
!2968 = !DILocation(line: 527, column: 13, scope: !2965)
!2969 = !DILocation(line: 526, column: 3, scope: !2965)
!2970 = !DILocation(line: 528, column: 8, scope: !2965)
!2971 = !DILocation(line: 528, column: 3, scope: !2965)
!2972 = !DILocation(line: 529, column: 2, scope: !2965)
!2973 = !DILocation(line: 530, column: 2, scope: !255)
!2974 = !DILocation(line: 531, column: 1, scope: !255)
!2975 = !DILocalVariable(name: "dest", arg: 1, scope: !258, file: !1, line: 1657, type: !95)
!2976 = !DILocation(line: 1657, column: 29, scope: !258)
!2977 = !DILocalVariable(name: "src", arg: 2, scope: !258, file: !1, line: 1657, type: !80)
!2978 = !DILocation(line: 1657, column: 47, scope: !258)
!2979 = !DILocalVariable(name: "buff", scope: !258, file: !1, line: 1659, type: !2980)
!2980 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 512, align: 8, elements: !287)
!2981 = !DILocation(line: 1659, column: 7, scope: !258)
!2982 = !DILocalVariable(name: "p", scope: !258, file: !1, line: 1660, type: !80)
!2983 = !DILocation(line: 1660, column: 14, scope: !258)
!2984 = !DILocation(line: 1663, column: 6, scope: !2985)
!2985 = distinct !DILexicalBlock(scope: !258, file: !1, line: 1663, column: 6)
!2986 = !DILocation(line: 1663, column: 10, scope: !2985)
!2987 = !DILocation(line: 1663, column: 18, scope: !2985)
!2988 = !DILocation(line: 1663, column: 22, scope: !2989)
!2989 = !DILexicalBlockFile(scope: !2985, file: !1, discriminator: 1)
!2990 = !DILocation(line: 1663, column: 21, scope: !2989)
!2991 = !DILocation(line: 1663, column: 26, scope: !2989)
!2992 = !DILocation(line: 1663, column: 6, scope: !2989)
!2993 = !DILocation(line: 1664, column: 10, scope: !2994)
!2994 = distinct !DILexicalBlock(scope: !2985, file: !1, line: 1663, column: 35)
!2995 = !DILocation(line: 1664, column: 3, scope: !2994)
!2996 = !DILocation(line: 1665, column: 11, scope: !2994)
!2997 = !DILocation(line: 1665, column: 3, scope: !2994)
!2998 = !DILocation(line: 1669, column: 6, scope: !258)
!2999 = !DILocation(line: 1669, column: 19, scope: !258)
!3000 = !DILocation(line: 1669, column: 12, scope: !258)
!3001 = !DILocation(line: 1669, column: 10, scope: !258)
!3002 = !DILocation(line: 1669, column: 4, scope: !258)
!3003 = !DILocation(line: 1670, column: 2, scope: !258)
!3004 = !DILocation(line: 1672, column: 7, scope: !3005)
!3005 = distinct !DILexicalBlock(scope: !3006, file: !1, line: 1672, column: 7)
!3006 = distinct !DILexicalBlock(scope: !3007, file: !1, line: 1670, column: 11)
!3007 = distinct !DILexicalBlock(scope: !3008, file: !1, line: 1670, column: 2)
!3008 = distinct !DILexicalBlock(scope: !258, file: !1, line: 1670, column: 2)
!3009 = !DILocation(line: 1672, column: 11, scope: !3005)
!3010 = !DILocation(line: 1672, column: 9, scope: !3005)
!3011 = !DILocation(line: 1672, column: 15, scope: !3005)
!3012 = !DILocation(line: 1672, column: 18, scope: !3013)
!3013 = !DILexicalBlockFile(scope: !3005, file: !1, discriminator: 1)
!3014 = !DILocation(line: 1672, column: 24, scope: !3013)
!3015 = !DILocation(line: 1672, column: 7, scope: !3013)
!3016 = !DILocation(line: 1673, column: 4, scope: !3017)
!3017 = distinct !DILexicalBlock(scope: !3005, file: !1, line: 1672, column: 32)
!3018 = !DILocation(line: 1674, column: 4, scope: !3017)
!3019 = !DILocation(line: 1677, column: 7, scope: !3020)
!3020 = distinct !DILexicalBlock(scope: !3006, file: !1, line: 1677, column: 7)
!3021 = !DILocation(line: 1677, column: 11, scope: !3020)
!3022 = !DILocation(line: 1677, column: 15, scope: !3020)
!3023 = !DILocation(line: 1677, column: 9, scope: !3020)
!3024 = !DILocation(line: 1677, column: 19, scope: !3020)
!3025 = !DILocation(line: 1677, column: 22, scope: !3026)
!3026 = !DILexicalBlockFile(scope: !3020, file: !1, discriminator: 1)
!3027 = !DILocation(line: 1677, column: 28, scope: !3026)
!3028 = !DILocation(line: 1678, column: 7, scope: !3020)
!3029 = !DILocation(line: 1678, column: 10, scope: !3026)
!3030 = !DILocation(line: 1678, column: 16, scope: !3026)
!3031 = !DILocation(line: 1677, column: 7, scope: !3032)
!3032 = !DILexicalBlockFile(scope: !3006, file: !1, discriminator: 2)
!3033 = !DILocation(line: 1679, column: 4, scope: !3034)
!3034 = distinct !DILexicalBlock(scope: !3020, file: !1, line: 1678, column: 24)
!3035 = !DILocation(line: 1680, column: 4, scope: !3034)
!3036 = !DILocation(line: 1682, column: 3, scope: !3006)
!3037 = !DILocation(line: 1689, column: 9, scope: !258)
!3038 = !DILocation(line: 1689, column: 2, scope: !258)
!3039 = !DILocation(line: 1693, column: 25, scope: !258)
!3040 = !DILocation(line: 1693, column: 31, scope: !258)
!3041 = !DILocation(line: 1693, column: 36, scope: !258)
!3042 = !DILocation(line: 1693, column: 40, scope: !258)
!3043 = !DILocation(line: 1693, column: 38, scope: !258)
!3044 = !DILocation(line: 1693, column: 45, scope: !258)
!3045 = !DILocation(line: 1693, column: 2, scope: !258)
!3046 = !DILocation(line: 1695, column: 10, scope: !258)
!3047 = !DILocation(line: 1695, column: 2, scope: !258)
!3048 = !DILocation(line: 1696, column: 1, scope: !258)
!3049 = !DILocalVariable(name: "pax", arg: 1, scope: !261, file: !1, line: 1949, type: !192)
!3050 = !DILocation(line: 1949, column: 29, scope: !261)
!3051 = !DILocalVariable(name: "offset", arg: 2, scope: !261, file: !1, line: 1949, type: !52)
!3052 = !DILocation(line: 1949, column: 42, scope: !261)
!3053 = !DILocalVariable(name: "length", arg: 3, scope: !261, file: !1, line: 1949, type: !52)
!3054 = !DILocation(line: 1949, column: 58, scope: !261)
!3055 = !DILocalVariable(name: "last_offset", scope: !261, file: !1, line: 1951, type: !52)
!3056 = !DILocation(line: 1951, column: 10, scope: !261)
!3057 = !DILocalVariable(name: "r", scope: !261, file: !1, line: 1952, type: !23)
!3058 = !DILocation(line: 1952, column: 6, scope: !261)
!3059 = !DILocation(line: 1954, column: 6, scope: !3060)
!3060 = distinct !DILexicalBlock(scope: !261, file: !1, line: 1954, column: 6)
!3061 = !DILocation(line: 1954, column: 11, scope: !3060)
!3062 = !DILocation(line: 1954, column: 23, scope: !3060)
!3063 = !DILocation(line: 1954, column: 6, scope: !261)
!3064 = !DILocation(line: 1955, column: 15, scope: !3060)
!3065 = !DILocation(line: 1955, column: 3, scope: !3060)
!3066 = !DILocation(line: 1957, column: 17, scope: !3067)
!3067 = distinct !DILexicalBlock(scope: !3060, file: !1, line: 1956, column: 7)
!3068 = !DILocation(line: 1957, column: 22, scope: !3067)
!3069 = !DILocation(line: 1957, column: 35, scope: !3067)
!3070 = !DILocation(line: 1958, column: 7, scope: !3067)
!3071 = !DILocation(line: 1958, column: 12, scope: !3067)
!3072 = !DILocation(line: 1958, column: 25, scope: !3067)
!3073 = !DILocation(line: 1957, column: 42, scope: !3067)
!3074 = !DILocation(line: 1957, column: 15, scope: !3067)
!3075 = !DILocation(line: 1960, column: 6, scope: !3076)
!3076 = distinct !DILexicalBlock(scope: !261, file: !1, line: 1960, column: 6)
!3077 = !DILocation(line: 1960, column: 20, scope: !3076)
!3078 = !DILocation(line: 1960, column: 18, scope: !3076)
!3079 = !DILocation(line: 1960, column: 6, scope: !261)
!3080 = !DILocation(line: 1962, column: 30, scope: !3081)
!3081 = distinct !DILexicalBlock(scope: !3076, file: !1, line: 1960, column: 28)
!3082 = !DILocation(line: 1962, column: 35, scope: !3081)
!3083 = !DILocation(line: 1963, column: 7, scope: !3081)
!3084 = !DILocation(line: 1963, column: 16, scope: !3081)
!3085 = !DILocation(line: 1963, column: 14, scope: !3081)
!3086 = !DILocation(line: 1962, column: 7, scope: !3081)
!3087 = !DILocation(line: 1962, column: 5, scope: !3081)
!3088 = !DILocation(line: 1964, column: 7, scope: !3089)
!3089 = distinct !DILexicalBlock(scope: !3081, file: !1, line: 1964, column: 7)
!3090 = !DILocation(line: 1964, column: 9, scope: !3089)
!3091 = !DILocation(line: 1964, column: 7, scope: !3081)
!3092 = !DILocation(line: 1965, column: 12, scope: !3089)
!3093 = !DILocation(line: 1965, column: 4, scope: !3089)
!3094 = !DILocation(line: 1966, column: 2, scope: !3081)
!3095 = !DILocation(line: 1968, column: 33, scope: !261)
!3096 = !DILocation(line: 1968, column: 38, scope: !261)
!3097 = !DILocation(line: 1968, column: 46, scope: !261)
!3098 = !DILocation(line: 1968, column: 10, scope: !261)
!3099 = !DILocation(line: 1968, column: 2, scope: !261)
!3100 = !DILocation(line: 1969, column: 1, scope: !261)
!3101 = !DILocalVariable(name: "a", arg: 1, scope: !267, file: !1, line: 369, type: !4)
!3102 = !DILocation(line: 369, column: 55, scope: !267)
!3103 = !DILocalVariable(name: "pax", arg: 2, scope: !267, file: !1, line: 370, type: !192)
!3104 = !DILocation(line: 370, column: 17, scope: !267)
!3105 = !DILocalVariable(name: "entry", arg: 3, scope: !267, file: !1, line: 370, type: !30)
!3106 = !DILocation(line: 370, column: 44, scope: !267)
!3107 = !DILocalVariable(name: "i", scope: !267, file: !1, line: 372, type: !23)
!3108 = !DILocation(line: 372, column: 6, scope: !267)
!3109 = !DILocation(line: 372, column: 36, scope: !267)
!3110 = !DILocation(line: 372, column: 10, scope: !267)
!3111 = !DILocation(line: 374, column: 2, scope: !267)
!3112 = !DILocation(line: 374, column: 10, scope: !3113)
!3113 = !DILexicalBlockFile(scope: !267, file: !1, discriminator: 1)
!3114 = !DILocation(line: 374, column: 2, scope: !3113)
!3115 = !DILocalVariable(name: "name", scope: !3116, file: !1, line: 375, type: !80)
!3116 = distinct !DILexicalBlock(scope: !267, file: !1, line: 374, column: 14)
!3117 = !DILocation(line: 375, column: 15, scope: !3116)
!3118 = !DILocalVariable(name: "value", scope: !3116, file: !1, line: 376, type: !43)
!3119 = !DILocation(line: 376, column: 15, scope: !3116)
!3120 = !DILocalVariable(name: "url_encoded_name", scope: !3116, file: !1, line: 377, type: !95)
!3121 = !DILocation(line: 377, column: 9, scope: !3116)
!3122 = !DILocalVariable(name: "encoded_name", scope: !3116, file: !1, line: 377, type: !95)
!3123 = !DILocation(line: 377, column: 35, scope: !3116)
!3124 = !DILocalVariable(name: "size", scope: !3116, file: !1, line: 378, type: !45)
!3125 = !DILocation(line: 378, column: 10, scope: !3116)
!3126 = !DILocalVariable(name: "r", scope: !3116, file: !1, line: 379, type: !23)
!3127 = !DILocation(line: 379, column: 7, scope: !3116)
!3128 = !DILocation(line: 381, column: 28, scope: !3116)
!3129 = !DILocation(line: 381, column: 3, scope: !3116)
!3130 = !DILocation(line: 382, column: 33, scope: !3116)
!3131 = !DILocation(line: 382, column: 22, scope: !3116)
!3132 = !DILocation(line: 382, column: 20, scope: !3116)
!3133 = !DILocation(line: 383, column: 7, scope: !3134)
!3134 = distinct !DILexicalBlock(scope: !3116, file: !1, line: 383, column: 7)
!3135 = !DILocation(line: 383, column: 24, scope: !3134)
!3136 = !DILocation(line: 383, column: 7, scope: !3116)
!3137 = !DILocation(line: 385, column: 8, scope: !3138)
!3138 = distinct !DILexicalBlock(scope: !3134, file: !1, line: 383, column: 33)
!3139 = !DILocation(line: 385, column: 8, scope: !3140)
!3140 = !DILexicalBlockFile(scope: !3138, file: !1, discriminator: 1)
!3141 = !DILocation(line: 385, column: 8, scope: !3142)
!3142 = !DILexicalBlockFile(scope: !3138, file: !1, discriminator: 2)
!3143 = !DILocation(line: 385, column: 8, scope: !3144)
!3144 = !DILexicalBlockFile(scope: !3138, file: !1, discriminator: 3)
!3145 = !DILocation(line: 385, column: 6, scope: !3144)
!3146 = !DILocation(line: 387, column: 9, scope: !3138)
!3147 = !DILocation(line: 387, column: 4, scope: !3138)
!3148 = !DILocation(line: 388, column: 8, scope: !3149)
!3149 = distinct !DILexicalBlock(scope: !3138, file: !1, line: 388, column: 8)
!3150 = !DILocation(line: 388, column: 10, scope: !3149)
!3151 = !DILocation(line: 388, column: 8, scope: !3138)
!3152 = !DILocation(line: 389, column: 20, scope: !3149)
!3153 = !DILocation(line: 389, column: 25, scope: !3149)
!3154 = !DILocation(line: 389, column: 44, scope: !3149)
!3155 = !DILocation(line: 389, column: 18, scope: !3149)
!3156 = !DILocation(line: 389, column: 5, scope: !3149)
!3157 = !DILocation(line: 390, column: 13, scope: !3158)
!3158 = distinct !DILexicalBlock(scope: !3149, file: !1, line: 390, column: 13)
!3159 = !DILocation(line: 390, column: 19, scope: !3158)
!3160 = !DILocation(line: 390, column: 13, scope: !3149)
!3161 = !DILocation(line: 391, column: 24, scope: !3162)
!3162 = distinct !DILexicalBlock(scope: !3158, file: !1, line: 390, column: 30)
!3163 = !DILocation(line: 391, column: 27, scope: !3162)
!3164 = !DILocation(line: 391, column: 5, scope: !3162)
!3165 = !DILocation(line: 393, column: 5, scope: !3162)
!3166 = !DILocation(line: 395, column: 3, scope: !3138)
!3167 = !DILocation(line: 397, column: 34, scope: !3116)
!3168 = !DILocation(line: 397, column: 39, scope: !3116)
!3169 = !DILocation(line: 398, column: 7, scope: !3116)
!3170 = !DILocation(line: 398, column: 14, scope: !3116)
!3171 = !DILocation(line: 397, column: 3, scope: !3116)
!3172 = !DILocation(line: 374, column: 2, scope: !3173)
!3173 = !DILexicalBlockFile(scope: !267, file: !1, discriminator: 2)
!3174 = !DILocation(line: 401, column: 2, scope: !267)
!3175 = !DILocation(line: 402, column: 1, scope: !267)
!3176 = !DILocalVariable(name: "dest", arg: 1, scope: !279, file: !1, line: 1590, type: !95)
!3177 = !DILocation(line: 1590, column: 32, scope: !279)
!3178 = !DILocalVariable(name: "src", arg: 2, scope: !279, file: !1, line: 1590, type: !80)
!3179 = !DILocation(line: 1590, column: 50, scope: !279)
!3180 = !DILocalVariable(name: "buff", scope: !279, file: !1, line: 1592, type: !2980)
!3181 = !DILocation(line: 1592, column: 7, scope: !279)
!3182 = !DILocalVariable(name: "p", scope: !279, file: !1, line: 1593, type: !80)
!3183 = !DILocation(line: 1593, column: 14, scope: !279)
!3184 = !DILocation(line: 1596, column: 6, scope: !3185)
!3185 = distinct !DILexicalBlock(scope: !279, file: !1, line: 1596, column: 6)
!3186 = !DILocation(line: 1596, column: 10, scope: !3185)
!3187 = !DILocation(line: 1596, column: 18, scope: !3185)
!3188 = !DILocation(line: 1596, column: 22, scope: !3189)
!3189 = !DILexicalBlockFile(scope: !3185, file: !1, discriminator: 1)
!3190 = !DILocation(line: 1596, column: 21, scope: !3189)
!3191 = !DILocation(line: 1596, column: 26, scope: !3189)
!3192 = !DILocation(line: 1596, column: 6, scope: !3189)
!3193 = !DILocation(line: 1597, column: 10, scope: !3194)
!3194 = distinct !DILexicalBlock(scope: !3185, file: !1, line: 1596, column: 35)
!3195 = !DILocation(line: 1597, column: 3, scope: !3194)
!3196 = !DILocation(line: 1598, column: 11, scope: !3194)
!3197 = !DILocation(line: 1598, column: 3, scope: !3194)
!3198 = !DILocation(line: 1602, column: 6, scope: !279)
!3199 = !DILocation(line: 1602, column: 19, scope: !279)
!3200 = !DILocation(line: 1602, column: 12, scope: !279)
!3201 = !DILocation(line: 1602, column: 10, scope: !279)
!3202 = !DILocation(line: 1602, column: 4, scope: !279)
!3203 = !DILocation(line: 1603, column: 2, scope: !279)
!3204 = !DILocation(line: 1605, column: 7, scope: !3205)
!3205 = distinct !DILexicalBlock(scope: !3206, file: !1, line: 1605, column: 7)
!3206 = distinct !DILexicalBlock(scope: !3207, file: !1, line: 1603, column: 11)
!3207 = distinct !DILexicalBlock(scope: !3208, file: !1, line: 1603, column: 2)
!3208 = distinct !DILexicalBlock(scope: !279, file: !1, line: 1603, column: 2)
!3209 = !DILocation(line: 1605, column: 11, scope: !3205)
!3210 = !DILocation(line: 1605, column: 9, scope: !3205)
!3211 = !DILocation(line: 1605, column: 15, scope: !3205)
!3212 = !DILocation(line: 1605, column: 18, scope: !3213)
!3213 = !DILexicalBlockFile(scope: !3205, file: !1, discriminator: 1)
!3214 = !DILocation(line: 1605, column: 24, scope: !3213)
!3215 = !DILocation(line: 1605, column: 7, scope: !3213)
!3216 = !DILocation(line: 1606, column: 4, scope: !3217)
!3217 = distinct !DILexicalBlock(scope: !3205, file: !1, line: 1605, column: 32)
!3218 = !DILocation(line: 1607, column: 4, scope: !3217)
!3219 = !DILocation(line: 1610, column: 7, scope: !3220)
!3220 = distinct !DILexicalBlock(scope: !3206, file: !1, line: 1610, column: 7)
!3221 = !DILocation(line: 1610, column: 11, scope: !3220)
!3222 = !DILocation(line: 1610, column: 15, scope: !3220)
!3223 = !DILocation(line: 1610, column: 9, scope: !3220)
!3224 = !DILocation(line: 1610, column: 19, scope: !3220)
!3225 = !DILocation(line: 1610, column: 22, scope: !3226)
!3226 = !DILexicalBlockFile(scope: !3220, file: !1, discriminator: 1)
!3227 = !DILocation(line: 1610, column: 28, scope: !3226)
!3228 = !DILocation(line: 1611, column: 7, scope: !3220)
!3229 = !DILocation(line: 1611, column: 10, scope: !3226)
!3230 = !DILocation(line: 1611, column: 16, scope: !3226)
!3231 = !DILocation(line: 1610, column: 7, scope: !3232)
!3232 = !DILexicalBlockFile(scope: !3206, file: !1, discriminator: 2)
!3233 = !DILocation(line: 1612, column: 4, scope: !3234)
!3234 = distinct !DILexicalBlock(scope: !3220, file: !1, line: 1611, column: 24)
!3235 = !DILocation(line: 1613, column: 4, scope: !3234)
!3236 = !DILocation(line: 1615, column: 3, scope: !3206)
!3237 = !DILocation(line: 1620, column: 6, scope: !3238)
!3238 = distinct !DILexicalBlock(scope: !279, file: !1, line: 1620, column: 6)
!3239 = !DILocation(line: 1620, column: 11, scope: !3238)
!3240 = !DILocation(line: 1620, column: 8, scope: !3238)
!3241 = !DILocation(line: 1620, column: 6, scope: !279)
!3242 = !DILocation(line: 1621, column: 10, scope: !3243)
!3243 = distinct !DILexicalBlock(scope: !3238, file: !1, line: 1620, column: 16)
!3244 = !DILocation(line: 1621, column: 3, scope: !3243)
!3245 = !DILocation(line: 1622, column: 11, scope: !3243)
!3246 = !DILocation(line: 1622, column: 3, scope: !3243)
!3247 = !DILocation(line: 1626, column: 7, scope: !3248)
!3248 = distinct !DILexicalBlock(scope: !279, file: !1, line: 1626, column: 6)
!3249 = !DILocation(line: 1626, column: 6, scope: !3248)
!3250 = !DILocation(line: 1626, column: 11, scope: !3248)
!3251 = !DILocation(line: 1626, column: 18, scope: !3248)
!3252 = !DILocation(line: 1626, column: 21, scope: !3253)
!3253 = !DILexicalBlockFile(scope: !3248, file: !1, discriminator: 1)
!3254 = !DILocation(line: 1626, column: 26, scope: !3253)
!3255 = !DILocation(line: 1626, column: 30, scope: !3253)
!3256 = !DILocation(line: 1626, column: 23, scope: !3253)
!3257 = !DILocation(line: 1626, column: 6, scope: !3253)
!3258 = !DILocation(line: 1627, column: 10, scope: !3259)
!3259 = distinct !DILexicalBlock(scope: !3248, file: !1, line: 1626, column: 35)
!3260 = !DILocation(line: 1627, column: 3, scope: !3259)
!3261 = !DILocation(line: 1628, column: 11, scope: !3259)
!3262 = !DILocation(line: 1628, column: 3, scope: !3259)
!3263 = !DILocation(line: 1640, column: 9, scope: !279)
!3264 = !DILocation(line: 1640, column: 2, scope: !279)
!3265 = !DILocation(line: 1644, column: 25, scope: !279)
!3266 = !DILocation(line: 1644, column: 31, scope: !279)
!3267 = !DILocation(line: 1644, column: 36, scope: !279)
!3268 = !DILocation(line: 1644, column: 40, scope: !279)
!3269 = !DILocation(line: 1644, column: 38, scope: !279)
!3270 = !DILocation(line: 1644, column: 45, scope: !279)
!3271 = !DILocation(line: 1644, column: 2, scope: !279)
!3272 = !DILocation(line: 1646, column: 10, scope: !279)
!3273 = !DILocation(line: 1646, column: 2, scope: !279)
!3274 = !DILocation(line: 1647, column: 1, scope: !279)
!3275 = !DILocalVariable(name: "as", arg: 1, scope: !237, file: !1, line: 295, type: !236)
!3276 = !DILocation(line: 295, column: 44, scope: !237)
!3277 = !DILocalVariable(name: "key", arg: 2, scope: !237, file: !1, line: 295, type: !80)
!3278 = !DILocation(line: 295, column: 60, scope: !237)
!3279 = !DILocalVariable(name: "value", arg: 3, scope: !237, file: !1, line: 296, type: !80)
!3280 = !DILocation(line: 296, column: 19, scope: !237)
!3281 = !DILocalVariable(name: "value_len", arg: 4, scope: !237, file: !1, line: 296, type: !45)
!3282 = !DILocation(line: 296, column: 33, scope: !237)
!3283 = !DILocalVariable(name: "digits", scope: !237, file: !1, line: 298, type: !23)
!3284 = !DILocation(line: 298, column: 6, scope: !237)
!3285 = !DILocalVariable(name: "i", scope: !237, file: !1, line: 298, type: !23)
!3286 = !DILocation(line: 298, column: 14, scope: !237)
!3287 = !DILocalVariable(name: "len", scope: !237, file: !1, line: 298, type: !23)
!3288 = !DILocation(line: 298, column: 17, scope: !237)
!3289 = !DILocalVariable(name: "next_ten", scope: !237, file: !1, line: 298, type: !23)
!3290 = !DILocation(line: 298, column: 22, scope: !237)
!3291 = !DILocalVariable(name: "tmp", scope: !237, file: !1, line: 299, type: !3292)
!3292 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 104, align: 8, elements: !3293)
!3293 = !{!3294}
!3294 = !DISubrange(count: 13)
!3295 = !DILocation(line: 299, column: 7, scope: !237)
!3296 = !DILocation(line: 305, column: 24, scope: !237)
!3297 = !DILocation(line: 305, column: 17, scope: !237)
!3298 = !DILocation(line: 305, column: 12, scope: !237)
!3299 = !DILocation(line: 305, column: 10, scope: !237)
!3300 = !DILocation(line: 305, column: 29, scope: !237)
!3301 = !DILocation(line: 305, column: 40, scope: !237)
!3302 = !DILocation(line: 305, column: 35, scope: !237)
!3303 = !DILocation(line: 305, column: 33, scope: !237)
!3304 = !DILocation(line: 305, column: 50, scope: !237)
!3305 = !DILocation(line: 305, column: 6, scope: !237)
!3306 = !DILocation(line: 313, column: 11, scope: !237)
!3307 = !DILocation(line: 314, column: 9, scope: !237)
!3308 = !DILocation(line: 315, column: 6, scope: !237)
!3309 = !DILocation(line: 315, column: 4, scope: !237)
!3310 = !DILocation(line: 316, column: 2, scope: !237)
!3311 = !DILocation(line: 316, column: 9, scope: !3312)
!3312 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 1)
!3313 = !DILocation(line: 316, column: 11, scope: !3312)
!3314 = !DILocation(line: 316, column: 2, scope: !3312)
!3315 = !DILocation(line: 317, column: 7, scope: !3316)
!3316 = distinct !DILexicalBlock(scope: !237, file: !1, line: 316, column: 16)
!3317 = !DILocation(line: 317, column: 9, scope: !3316)
!3318 = !DILocation(line: 317, column: 5, scope: !3316)
!3319 = !DILocation(line: 318, column: 9, scope: !3316)
!3320 = !DILocation(line: 319, column: 14, scope: !3316)
!3321 = !DILocation(line: 319, column: 23, scope: !3316)
!3322 = !DILocation(line: 319, column: 12, scope: !3316)
!3323 = !DILocation(line: 316, column: 2, scope: !3324)
!3324 = !DILexicalBlockFile(scope: !237, file: !1, discriminator: 2)
!3325 = !DILocation(line: 327, column: 6, scope: !3326)
!3326 = distinct !DILexicalBlock(scope: !237, file: !1, line: 327, column: 6)
!3327 = !DILocation(line: 327, column: 12, scope: !3326)
!3328 = !DILocation(line: 327, column: 10, scope: !3326)
!3329 = !DILocation(line: 327, column: 22, scope: !3326)
!3330 = !DILocation(line: 327, column: 19, scope: !3326)
!3331 = !DILocation(line: 327, column: 6, scope: !237)
!3332 = !DILocation(line: 328, column: 9, scope: !3326)
!3333 = !DILocation(line: 328, column: 3, scope: !3326)
!3334 = !DILocation(line: 331, column: 2, scope: !237)
!3335 = !DILocation(line: 331, column: 23, scope: !237)
!3336 = !DILocation(line: 332, column: 17, scope: !237)
!3337 = !DILocation(line: 332, column: 32, scope: !237)
!3338 = !DILocation(line: 332, column: 36, scope: !237)
!3339 = !DILocation(line: 332, column: 50, scope: !237)
!3340 = !DILocation(line: 332, column: 55, scope: !237)
!3341 = !DILocation(line: 332, column: 61, scope: !237)
!3342 = !DILocation(line: 332, column: 59, scope: !237)
!3343 = !DILocation(line: 332, column: 21, scope: !237)
!3344 = !DILocation(line: 332, column: 2, scope: !3312)
!3345 = !DILocation(line: 333, column: 25, scope: !237)
!3346 = !DILocation(line: 333, column: 2, scope: !237)
!3347 = !DILocation(line: 334, column: 17, scope: !237)
!3348 = !DILocation(line: 334, column: 21, scope: !237)
!3349 = !DILocation(line: 334, column: 2, scope: !237)
!3350 = !DILocation(line: 335, column: 25, scope: !237)
!3351 = !DILocation(line: 335, column: 2, scope: !237)
!3352 = !DILocation(line: 336, column: 23, scope: !237)
!3353 = !DILocation(line: 336, column: 27, scope: !237)
!3354 = !DILocation(line: 336, column: 34, scope: !237)
!3355 = !DILocation(line: 336, column: 2, scope: !237)
!3356 = !DILocation(line: 337, column: 25, scope: !237)
!3357 = !DILocation(line: 337, column: 2, scope: !237)
!3358 = !DILocation(line: 338, column: 1, scope: !237)
!3359 = !DILocalVariable(name: "t", arg: 1, scope: !240, file: !1, line: 254, type: !95)
!3360 = !DILocation(line: 254, column: 18, scope: !240)
!3361 = !DILocalVariable(name: "i", arg: 2, scope: !240, file: !1, line: 254, type: !52)
!3362 = !DILocation(line: 254, column: 29, scope: !240)
!3363 = !DILocalVariable(name: "ui", scope: !240, file: !1, line: 256, type: !196)
!3364 = !DILocation(line: 256, column: 11, scope: !240)
!3365 = !DILocation(line: 258, column: 6, scope: !3366)
!3366 = distinct !DILexicalBlock(scope: !240, file: !1, line: 258, column: 6)
!3367 = !DILocation(line: 258, column: 8, scope: !3366)
!3368 = !DILocation(line: 258, column: 6, scope: !240)
!3369 = !DILocation(line: 259, column: 9, scope: !3366)
!3370 = !DILocation(line: 259, column: 11, scope: !3366)
!3371 = !DILocation(line: 259, column: 8, scope: !3366)
!3372 = !DILocation(line: 259, column: 8, scope: !3373)
!3373 = !DILexicalBlockFile(scope: !3366, file: !1, discriminator: 1)
!3374 = !DILocation(line: 259, column: 67, scope: !3375)
!3375 = !DILexicalBlockFile(scope: !3366, file: !1, discriminator: 2)
!3376 = !DILocation(line: 259, column: 66, scope: !3375)
!3377 = !DILocation(line: 259, column: 8, scope: !3375)
!3378 = !DILocation(line: 259, column: 8, scope: !3379)
!3379 = !DILexicalBlockFile(scope: !3366, file: !1, discriminator: 3)
!3380 = !DILocation(line: 259, column: 6, scope: !3379)
!3381 = !DILocation(line: 259, column: 3, scope: !3379)
!3382 = !DILocation(line: 261, column: 8, scope: !3366)
!3383 = !DILocation(line: 261, column: 6, scope: !3366)
!3384 = !DILocation(line: 263, column: 2, scope: !240)
!3385 = !DILocation(line: 264, column: 23, scope: !3386)
!3386 = distinct !DILexicalBlock(scope: !240, file: !1, line: 263, column: 5)
!3387 = !DILocation(line: 264, column: 26, scope: !3386)
!3388 = !DILocation(line: 264, column: 10, scope: !3386)
!3389 = !DILocation(line: 264, column: 4, scope: !3386)
!3390 = !DILocation(line: 264, column: 8, scope: !3386)
!3391 = !DILocation(line: 265, column: 2, scope: !3386)
!3392 = !DILocation(line: 265, column: 14, scope: !3393)
!3393 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 1)
!3394 = !DILocation(line: 265, column: 2, scope: !3393)
!3395 = !DILocation(line: 266, column: 6, scope: !3396)
!3396 = distinct !DILexicalBlock(scope: !240, file: !1, line: 266, column: 6)
!3397 = !DILocation(line: 266, column: 8, scope: !3396)
!3398 = !DILocation(line: 266, column: 6, scope: !240)
!3399 = !DILocation(line: 267, column: 4, scope: !3396)
!3400 = !DILocation(line: 267, column: 8, scope: !3396)
!3401 = !DILocation(line: 267, column: 3, scope: !3396)
!3402 = !DILocation(line: 268, column: 10, scope: !240)
!3403 = !DILocation(line: 268, column: 2, scope: !240)
!3404 = !DILocalVariable(name: "pax", arg: 1, scope: !264, file: !1, line: 1927, type: !192)
!3405 = !DILocation(line: 1927, column: 36, scope: !264)
!3406 = !DILocalVariable(name: "offset", arg: 2, scope: !264, file: !1, line: 1927, type: !52)
!3407 = !DILocation(line: 1927, column: 49, scope: !264)
!3408 = !DILocalVariable(name: "length", arg: 3, scope: !264, file: !1, line: 1927, type: !52)
!3409 = !DILocation(line: 1927, column: 65, scope: !264)
!3410 = !DILocalVariable(name: "is_hole", arg: 4, scope: !264, file: !1, line: 1928, type: !23)
!3411 = !DILocation(line: 1928, column: 9, scope: !264)
!3412 = !DILocalVariable(name: "sb", scope: !264, file: !1, line: 1930, type: !203)
!3413 = !DILocation(line: 1930, column: 23, scope: !264)
!3414 = !DILocation(line: 1932, column: 30, scope: !264)
!3415 = !DILocation(line: 1932, column: 7, scope: !264)
!3416 = !DILocation(line: 1932, column: 5, scope: !264)
!3417 = !DILocation(line: 1933, column: 6, scope: !3418)
!3418 = distinct !DILexicalBlock(scope: !264, file: !1, line: 1933, column: 6)
!3419 = !DILocation(line: 1933, column: 9, scope: !3418)
!3420 = !DILocation(line: 1933, column: 6, scope: !264)
!3421 = !DILocation(line: 1934, column: 3, scope: !3418)
!3422 = !DILocation(line: 1935, column: 2, scope: !264)
!3423 = !DILocation(line: 1935, column: 6, scope: !264)
!3424 = !DILocation(line: 1935, column: 11, scope: !264)
!3425 = !DILocation(line: 1936, column: 16, scope: !264)
!3426 = !DILocation(line: 1936, column: 2, scope: !264)
!3427 = !DILocation(line: 1936, column: 6, scope: !264)
!3428 = !DILocation(line: 1936, column: 14, scope: !264)
!3429 = !DILocation(line: 1937, column: 15, scope: !264)
!3430 = !DILocation(line: 1937, column: 2, scope: !264)
!3431 = !DILocation(line: 1937, column: 6, scope: !264)
!3432 = !DILocation(line: 1937, column: 13, scope: !264)
!3433 = !DILocation(line: 1938, column: 18, scope: !264)
!3434 = !DILocation(line: 1938, column: 2, scope: !264)
!3435 = !DILocation(line: 1938, column: 6, scope: !264)
!3436 = !DILocation(line: 1938, column: 16, scope: !264)
!3437 = !DILocation(line: 1939, column: 6, scope: !3438)
!3438 = distinct !DILexicalBlock(scope: !264, file: !1, line: 1939, column: 6)
!3439 = !DILocation(line: 1939, column: 11, scope: !3438)
!3440 = !DILocation(line: 1939, column: 23, scope: !3438)
!3441 = !DILocation(line: 1939, column: 31, scope: !3438)
!3442 = !DILocation(line: 1939, column: 34, scope: !3443)
!3443 = !DILexicalBlockFile(scope: !3438, file: !1, discriminator: 1)
!3444 = !DILocation(line: 1939, column: 39, scope: !3443)
!3445 = !DILocation(line: 1939, column: 51, scope: !3443)
!3446 = !DILocation(line: 1939, column: 6, scope: !3443)
!3447 = !DILocation(line: 1940, column: 41, scope: !3438)
!3448 = !DILocation(line: 1940, column: 22, scope: !3438)
!3449 = !DILocation(line: 1940, column: 27, scope: !3438)
!3450 = !DILocation(line: 1940, column: 39, scope: !3438)
!3451 = !DILocation(line: 1940, column: 3, scope: !3438)
!3452 = !DILocation(line: 1940, column: 8, scope: !3438)
!3453 = !DILocation(line: 1940, column: 20, scope: !3438)
!3454 = !DILocation(line: 1942, column: 28, scope: !3455)
!3455 = distinct !DILexicalBlock(scope: !3438, file: !1, line: 1941, column: 7)
!3456 = !DILocation(line: 1942, column: 3, scope: !3455)
!3457 = !DILocation(line: 1942, column: 8, scope: !3455)
!3458 = !DILocation(line: 1942, column: 21, scope: !3455)
!3459 = !DILocation(line: 1942, column: 26, scope: !3455)
!3460 = !DILocation(line: 1943, column: 22, scope: !3455)
!3461 = !DILocation(line: 1943, column: 3, scope: !3455)
!3462 = !DILocation(line: 1943, column: 8, scope: !3455)
!3463 = !DILocation(line: 1943, column: 20, scope: !3455)
!3464 = !DILocation(line: 1945, column: 2, scope: !264)
!3465 = !DILocation(line: 1946, column: 1, scope: !264)
!3466 = !DILocalVariable(name: "in", arg: 1, scope: !270, file: !1, line: 1825, type: !80)
!3467 = !DILocation(line: 1825, column: 24, scope: !270)
!3468 = !DILocalVariable(name: "s", scope: !270, file: !1, line: 1827, type: !80)
!3469 = !DILocation(line: 1827, column: 14, scope: !270)
!3470 = !DILocalVariable(name: "d", scope: !270, file: !1, line: 1828, type: !95)
!3471 = !DILocation(line: 1828, column: 8, scope: !270)
!3472 = !DILocalVariable(name: "out_len", scope: !270, file: !1, line: 1829, type: !23)
!3473 = !DILocation(line: 1829, column: 6, scope: !270)
!3474 = !DILocalVariable(name: "out", scope: !270, file: !1, line: 1830, type: !95)
!3475 = !DILocation(line: 1830, column: 8, scope: !270)
!3476 = !DILocation(line: 1832, column: 11, scope: !3477)
!3477 = distinct !DILexicalBlock(scope: !270, file: !1, line: 1832, column: 2)
!3478 = !DILocation(line: 1832, column: 9, scope: !3477)
!3479 = !DILocation(line: 1832, column: 7, scope: !3477)
!3480 = !DILocation(line: 1832, column: 16, scope: !3481)
!3481 = !DILexicalBlockFile(scope: !3482, file: !1, discriminator: 1)
!3482 = distinct !DILexicalBlock(scope: !3477, file: !1, line: 1832, column: 2)
!3483 = !DILocation(line: 1832, column: 15, scope: !3481)
!3484 = !DILocation(line: 1832, column: 18, scope: !3481)
!3485 = !DILocation(line: 1832, column: 2, scope: !3481)
!3486 = !DILocation(line: 1833, column: 8, scope: !3487)
!3487 = distinct !DILexicalBlock(scope: !3488, file: !1, line: 1833, column: 7)
!3488 = distinct !DILexicalBlock(scope: !3482, file: !1, line: 1832, column: 32)
!3489 = !DILocation(line: 1833, column: 7, scope: !3487)
!3490 = !DILocation(line: 1833, column: 10, scope: !3487)
!3491 = !DILocation(line: 1833, column: 15, scope: !3487)
!3492 = !DILocation(line: 1833, column: 19, scope: !3493)
!3493 = !DILexicalBlockFile(scope: !3487, file: !1, discriminator: 1)
!3494 = !DILocation(line: 1833, column: 18, scope: !3493)
!3495 = !DILocation(line: 1833, column: 21, scope: !3493)
!3496 = !DILocation(line: 1833, column: 27, scope: !3493)
!3497 = !DILocation(line: 1833, column: 31, scope: !3498)
!3498 = !DILexicalBlockFile(scope: !3487, file: !1, discriminator: 2)
!3499 = !DILocation(line: 1833, column: 30, scope: !3498)
!3500 = !DILocation(line: 1833, column: 33, scope: !3498)
!3501 = !DILocation(line: 1833, column: 40, scope: !3498)
!3502 = !DILocation(line: 1833, column: 44, scope: !3503)
!3503 = !DILexicalBlockFile(scope: !3487, file: !1, discriminator: 3)
!3504 = !DILocation(line: 1833, column: 43, scope: !3503)
!3505 = !DILocation(line: 1833, column: 46, scope: !3503)
!3506 = !DILocation(line: 1833, column: 7, scope: !3503)
!3507 = !DILocation(line: 1834, column: 12, scope: !3487)
!3508 = !DILocation(line: 1834, column: 4, scope: !3487)
!3509 = !DILocation(line: 1836, column: 11, scope: !3487)
!3510 = !DILocation(line: 1837, column: 2, scope: !3488)
!3511 = !DILocation(line: 1832, column: 28, scope: !3512)
!3512 = !DILexicalBlockFile(scope: !3482, file: !1, discriminator: 2)
!3513 = !DILocation(line: 1832, column: 2, scope: !3512)
!3514 = !DILocation(line: 1839, column: 23, scope: !270)
!3515 = !DILocation(line: 1839, column: 31, scope: !270)
!3516 = !DILocation(line: 1839, column: 16, scope: !270)
!3517 = !DILocation(line: 1839, column: 6, scope: !270)
!3518 = !DILocation(line: 1840, column: 6, scope: !3519)
!3519 = distinct !DILexicalBlock(scope: !270, file: !1, line: 1840, column: 6)
!3520 = !DILocation(line: 1840, column: 10, scope: !3519)
!3521 = !DILocation(line: 1840, column: 6, scope: !270)
!3522 = !DILocation(line: 1841, column: 3, scope: !3519)
!3523 = !DILocation(line: 1843, column: 11, scope: !3524)
!3524 = distinct !DILexicalBlock(scope: !270, file: !1, line: 1843, column: 2)
!3525 = !DILocation(line: 1843, column: 9, scope: !3524)
!3526 = !DILocation(line: 1843, column: 19, scope: !3524)
!3527 = !DILocation(line: 1843, column: 17, scope: !3524)
!3528 = !DILocation(line: 1843, column: 7, scope: !3524)
!3529 = !DILocation(line: 1843, column: 25, scope: !3530)
!3530 = !DILexicalBlockFile(scope: !3531, file: !1, discriminator: 1)
!3531 = distinct !DILexicalBlock(scope: !3524, file: !1, line: 1843, column: 2)
!3532 = !DILocation(line: 1843, column: 24, scope: !3530)
!3533 = !DILocation(line: 1843, column: 27, scope: !3530)
!3534 = !DILocation(line: 1843, column: 2, scope: !3530)
!3535 = !DILocation(line: 1845, column: 8, scope: !3536)
!3536 = distinct !DILexicalBlock(scope: !3537, file: !1, line: 1845, column: 7)
!3537 = distinct !DILexicalBlock(scope: !3531, file: !1, line: 1843, column: 41)
!3538 = !DILocation(line: 1845, column: 7, scope: !3536)
!3539 = !DILocation(line: 1845, column: 10, scope: !3536)
!3540 = !DILocation(line: 1845, column: 15, scope: !3536)
!3541 = !DILocation(line: 1845, column: 19, scope: !3542)
!3542 = !DILexicalBlockFile(scope: !3536, file: !1, discriminator: 1)
!3543 = !DILocation(line: 1845, column: 18, scope: !3542)
!3544 = !DILocation(line: 1845, column: 21, scope: !3542)
!3545 = !DILocation(line: 1845, column: 27, scope: !3542)
!3546 = !DILocation(line: 1845, column: 31, scope: !3547)
!3547 = !DILexicalBlockFile(scope: !3536, file: !1, discriminator: 2)
!3548 = !DILocation(line: 1845, column: 30, scope: !3547)
!3549 = !DILocation(line: 1845, column: 33, scope: !3547)
!3550 = !DILocation(line: 1845, column: 40, scope: !3547)
!3551 = !DILocation(line: 1845, column: 44, scope: !3552)
!3552 = !DILexicalBlockFile(scope: !3536, file: !1, discriminator: 3)
!3553 = !DILocation(line: 1845, column: 43, scope: !3552)
!3554 = !DILocation(line: 1845, column: 46, scope: !3552)
!3555 = !DILocation(line: 1845, column: 7, scope: !3552)
!3556 = !DILocation(line: 1847, column: 6, scope: !3557)
!3557 = distinct !DILexicalBlock(scope: !3536, file: !1, line: 1845, column: 54)
!3558 = !DILocation(line: 1847, column: 9, scope: !3557)
!3559 = !DILocation(line: 1848, column: 39, scope: !3557)
!3560 = !DILocation(line: 1848, column: 38, scope: !3557)
!3561 = !DILocation(line: 1848, column: 41, scope: !3557)
!3562 = !DILocation(line: 1848, column: 35, scope: !3557)
!3563 = !DILocation(line: 1848, column: 11, scope: !3557)
!3564 = !DILocation(line: 1848, column: 6, scope: !3557)
!3565 = !DILocation(line: 1848, column: 9, scope: !3557)
!3566 = !DILocation(line: 1849, column: 38, scope: !3557)
!3567 = !DILocation(line: 1849, column: 37, scope: !3557)
!3568 = !DILocation(line: 1849, column: 35, scope: !3557)
!3569 = !DILocation(line: 1849, column: 11, scope: !3557)
!3570 = !DILocation(line: 1849, column: 6, scope: !3557)
!3571 = !DILocation(line: 1849, column: 9, scope: !3557)
!3572 = !DILocation(line: 1850, column: 3, scope: !3557)
!3573 = !DILocation(line: 1851, column: 12, scope: !3574)
!3574 = distinct !DILexicalBlock(scope: !3536, file: !1, line: 1850, column: 10)
!3575 = !DILocation(line: 1851, column: 11, scope: !3574)
!3576 = !DILocation(line: 1851, column: 6, scope: !3574)
!3577 = !DILocation(line: 1851, column: 9, scope: !3574)
!3578 = !DILocation(line: 1853, column: 2, scope: !3537)
!3579 = !DILocation(line: 1843, column: 37, scope: !3580)
!3580 = !DILexicalBlockFile(scope: !3531, file: !1, discriminator: 2)
!3581 = !DILocation(line: 1843, column: 2, scope: !3580)
!3582 = !DILocation(line: 1854, column: 3, scope: !270)
!3583 = !DILocation(line: 1854, column: 5, scope: !270)
!3584 = !DILocation(line: 1855, column: 10, scope: !270)
!3585 = !DILocation(line: 1855, column: 2, scope: !270)
!3586 = !DILocation(line: 1856, column: 1, scope: !270)
!3587 = !DILocalVariable(name: "pax", arg: 1, scope: !273, file: !1, line: 341, type: !192)
!3588 = !DILocation(line: 341, column: 44, scope: !273)
!3589 = !DILocalVariable(name: "encoded_name", arg: 2, scope: !273, file: !1, line: 341, type: !80)
!3590 = !DILocation(line: 341, column: 61, scope: !273)
!3591 = !DILocalVariable(name: "value", arg: 3, scope: !273, file: !1, line: 342, type: !43)
!3592 = !DILocation(line: 342, column: 17, scope: !273)
!3593 = !DILocalVariable(name: "value_len", arg: 4, scope: !273, file: !1, line: 342, type: !45)
!3594 = !DILocation(line: 342, column: 31, scope: !273)
!3595 = !DILocalVariable(name: "s", scope: !273, file: !1, line: 344, type: !91)
!3596 = !DILocation(line: 344, column: 24, scope: !273)
!3597 = !DILocalVariable(name: "encoded_value", scope: !273, file: !1, line: 345, type: !95)
!3598 = !DILocation(line: 345, column: 8, scope: !273)
!3599 = !DILocation(line: 347, column: 6, scope: !3600)
!3600 = distinct !DILexicalBlock(scope: !273, file: !1, line: 347, column: 6)
!3601 = !DILocation(line: 347, column: 11, scope: !3600)
!3602 = !DILocation(line: 347, column: 17, scope: !3600)
!3603 = !DILocation(line: 347, column: 6, scope: !273)
!3604 = !DILocation(line: 348, column: 47, scope: !3605)
!3605 = distinct !DILexicalBlock(scope: !3600, file: !1, line: 347, column: 43)
!3606 = !DILocation(line: 348, column: 54, scope: !3605)
!3607 = !DILocation(line: 348, column: 19, scope: !3605)
!3608 = !DILocation(line: 348, column: 17, scope: !3605)
!3609 = !DILocation(line: 350, column: 7, scope: !3610)
!3610 = distinct !DILexicalBlock(scope: !3605, file: !1, line: 350, column: 7)
!3611 = !DILocation(line: 350, column: 20, scope: !3610)
!3612 = !DILocation(line: 350, column: 28, scope: !3610)
!3613 = !DILocation(line: 350, column: 31, scope: !3614)
!3614 = !DILexicalBlockFile(scope: !3610, file: !1, discriminator: 1)
!3615 = !DILocation(line: 350, column: 45, scope: !3614)
!3616 = !DILocation(line: 350, column: 7, scope: !3614)
!3617 = !DILocation(line: 351, column: 4, scope: !3618)
!3618 = distinct !DILexicalBlock(scope: !3610, file: !1, line: 350, column: 54)
!3619 = !DILocation(line: 351, column: 4, scope: !3620)
!3620 = !DILexicalBlockFile(scope: !3621, file: !1, discriminator: 1)
!3621 = distinct !DILexicalBlock(scope: !3618, file: !1, line: 351, column: 4)
!3622 = !DILocation(line: 352, column: 4, scope: !3618)
!3623 = !DILocation(line: 353, column: 23, scope: !3618)
!3624 = !DILocation(line: 353, column: 4, scope: !3618)
!3625 = !DILocation(line: 354, column: 19, scope: !3618)
!3626 = !DILocation(line: 354, column: 24, scope: !3618)
!3627 = !DILocation(line: 354, column: 39, scope: !3618)
!3628 = !DILocation(line: 354, column: 42, scope: !3618)
!3629 = !DILocation(line: 354, column: 4, scope: !3618)
!3630 = !DILocation(line: 355, column: 4, scope: !3618)
!3631 = !DILocation(line: 356, column: 3, scope: !3618)
!3632 = !DILocation(line: 357, column: 8, scope: !3605)
!3633 = !DILocation(line: 357, column: 3, scope: !3605)
!3634 = !DILocation(line: 358, column: 2, scope: !3605)
!3635 = !DILocation(line: 359, column: 6, scope: !3636)
!3636 = distinct !DILexicalBlock(scope: !273, file: !1, line: 359, column: 6)
!3637 = !DILocation(line: 359, column: 11, scope: !3636)
!3638 = !DILocation(line: 359, column: 17, scope: !3636)
!3639 = !DILocation(line: 359, column: 6, scope: !273)
!3640 = !DILocation(line: 360, column: 3, scope: !3641)
!3641 = distinct !DILexicalBlock(scope: !3636, file: !1, line: 359, column: 39)
!3642 = !DILocation(line: 360, column: 3, scope: !3643)
!3643 = !DILexicalBlockFile(scope: !3644, file: !1, discriminator: 1)
!3644 = distinct !DILexicalBlock(scope: !3641, file: !1, line: 360, column: 3)
!3645 = !DILocation(line: 361, column: 3, scope: !3641)
!3646 = !DILocation(line: 362, column: 22, scope: !3641)
!3647 = !DILocation(line: 362, column: 3, scope: !3641)
!3648 = !DILocation(line: 363, column: 25, scope: !3641)
!3649 = !DILocation(line: 363, column: 30, scope: !3641)
!3650 = !DILocation(line: 363, column: 45, scope: !3641)
!3651 = !DILocation(line: 363, column: 48, scope: !3641)
!3652 = !DILocation(line: 363, column: 55, scope: !3641)
!3653 = !DILocation(line: 363, column: 3, scope: !3641)
!3654 = !DILocation(line: 364, column: 3, scope: !3641)
!3655 = !DILocation(line: 365, column: 2, scope: !3641)
!3656 = !DILocation(line: 366, column: 1, scope: !273)
!3657 = !DILocalVariable(name: "s", arg: 1, scope: !276, file: !1, line: 1865, type: !80)
!3658 = !DILocation(line: 1865, column: 27, scope: !276)
!3659 = !DILocalVariable(name: "len", arg: 2, scope: !276, file: !1, line: 1865, type: !45)
!3660 = !DILocation(line: 1865, column: 37, scope: !276)
!3661 = !DILocalVariable(name: "v", scope: !276, file: !1, line: 1873, type: !23)
!3662 = !DILocation(line: 1873, column: 6, scope: !276)
!3663 = !DILocalVariable(name: "d", scope: !276, file: !1, line: 1874, type: !95)
!3664 = !DILocation(line: 1874, column: 8, scope: !276)
!3665 = !DILocalVariable(name: "out", scope: !276, file: !1, line: 1874, type: !95)
!3666 = !DILocation(line: 1874, column: 12, scope: !276)
!3667 = !DILocation(line: 1877, column: 24, scope: !276)
!3668 = !DILocation(line: 1877, column: 28, scope: !276)
!3669 = !DILocation(line: 1877, column: 32, scope: !276)
!3670 = !DILocation(line: 1877, column: 37, scope: !276)
!3671 = !DILocation(line: 1877, column: 41, scope: !276)
!3672 = !DILocation(line: 1877, column: 16, scope: !276)
!3673 = !DILocation(line: 1877, column: 6, scope: !276)
!3674 = !DILocation(line: 1878, column: 6, scope: !3675)
!3675 = distinct !DILexicalBlock(scope: !276, file: !1, line: 1878, column: 6)
!3676 = !DILocation(line: 1878, column: 10, scope: !3675)
!3677 = !DILocation(line: 1878, column: 6, scope: !276)
!3678 = !DILocation(line: 1879, column: 3, scope: !3675)
!3679 = !DILocation(line: 1880, column: 6, scope: !276)
!3680 = !DILocation(line: 1880, column: 4, scope: !276)
!3681 = !DILocation(line: 1883, column: 2, scope: !276)
!3682 = !DILocation(line: 1883, column: 9, scope: !3683)
!3683 = !DILexicalBlockFile(scope: !276, file: !1, discriminator: 1)
!3684 = !DILocation(line: 1883, column: 13, scope: !3683)
!3685 = !DILocation(line: 1883, column: 2, scope: !3683)
!3686 = !DILocation(line: 1884, column: 14, scope: !3687)
!3687 = distinct !DILexicalBlock(scope: !276, file: !1, line: 1883, column: 19)
!3688 = !DILocation(line: 1884, column: 9, scope: !3687)
!3689 = !DILocation(line: 1884, column: 19, scope: !3687)
!3690 = !DILocation(line: 1884, column: 26, scope: !3687)
!3691 = !DILocation(line: 1885, column: 16, scope: !3687)
!3692 = !DILocation(line: 1885, column: 11, scope: !3687)
!3693 = !DILocation(line: 1885, column: 21, scope: !3687)
!3694 = !DILocation(line: 1885, column: 27, scope: !3687)
!3695 = !DILocation(line: 1885, column: 7, scope: !3687)
!3696 = !DILocation(line: 1886, column: 16, scope: !3687)
!3697 = !DILocation(line: 1886, column: 11, scope: !3687)
!3698 = !DILocation(line: 1886, column: 22, scope: !3687)
!3699 = !DILocation(line: 1886, column: 7, scope: !3687)
!3700 = !DILocation(line: 1884, column: 5, scope: !3687)
!3701 = !DILocation(line: 1887, column: 5, scope: !3687)
!3702 = !DILocation(line: 1888, column: 7, scope: !3687)
!3703 = !DILocation(line: 1889, column: 18, scope: !3687)
!3704 = !DILocation(line: 1889, column: 20, scope: !3687)
!3705 = !DILocation(line: 1889, column: 27, scope: !3687)
!3706 = !DILocation(line: 1889, column: 10, scope: !3687)
!3707 = !DILocation(line: 1889, column: 5, scope: !3687)
!3708 = !DILocation(line: 1889, column: 8, scope: !3687)
!3709 = !DILocation(line: 1890, column: 18, scope: !3687)
!3710 = !DILocation(line: 1890, column: 20, scope: !3687)
!3711 = !DILocation(line: 1890, column: 27, scope: !3687)
!3712 = !DILocation(line: 1890, column: 10, scope: !3687)
!3713 = !DILocation(line: 1890, column: 5, scope: !3687)
!3714 = !DILocation(line: 1890, column: 8, scope: !3687)
!3715 = !DILocation(line: 1891, column: 18, scope: !3687)
!3716 = !DILocation(line: 1891, column: 20, scope: !3687)
!3717 = !DILocation(line: 1891, column: 26, scope: !3687)
!3718 = !DILocation(line: 1891, column: 10, scope: !3687)
!3719 = !DILocation(line: 1891, column: 5, scope: !3687)
!3720 = !DILocation(line: 1891, column: 8, scope: !3687)
!3721 = !DILocation(line: 1892, column: 18, scope: !3687)
!3722 = !DILocation(line: 1892, column: 21, scope: !3687)
!3723 = !DILocation(line: 1892, column: 10, scope: !3687)
!3724 = !DILocation(line: 1892, column: 5, scope: !3687)
!3725 = !DILocation(line: 1892, column: 8, scope: !3687)
!3726 = !DILocation(line: 1883, column: 2, scope: !3727)
!3727 = !DILexicalBlockFile(scope: !276, file: !1, discriminator: 2)
!3728 = !DILocation(line: 1895, column: 10, scope: !276)
!3729 = !DILocation(line: 1895, column: 2, scope: !276)
!3730 = !DILocation(line: 1896, column: 10, scope: !3731)
!3731 = distinct !DILexicalBlock(scope: !276, file: !1, line: 1895, column: 15)
!3732 = !DILocation(line: 1898, column: 14, scope: !3731)
!3733 = !DILocation(line: 1898, column: 9, scope: !3731)
!3734 = !DILocation(line: 1898, column: 19, scope: !3731)
!3735 = !DILocation(line: 1898, column: 26, scope: !3731)
!3736 = !DILocation(line: 1898, column: 5, scope: !3731)
!3737 = !DILocation(line: 1899, column: 18, scope: !3731)
!3738 = !DILocation(line: 1899, column: 20, scope: !3731)
!3739 = !DILocation(line: 1899, column: 27, scope: !3731)
!3740 = !DILocation(line: 1899, column: 10, scope: !3731)
!3741 = !DILocation(line: 1899, column: 5, scope: !3731)
!3742 = !DILocation(line: 1899, column: 8, scope: !3731)
!3743 = !DILocation(line: 1900, column: 18, scope: !3731)
!3744 = !DILocation(line: 1900, column: 20, scope: !3731)
!3745 = !DILocation(line: 1900, column: 27, scope: !3731)
!3746 = !DILocation(line: 1900, column: 10, scope: !3731)
!3747 = !DILocation(line: 1900, column: 5, scope: !3731)
!3748 = !DILocation(line: 1900, column: 8, scope: !3731)
!3749 = !DILocation(line: 1901, column: 3, scope: !3731)
!3750 = !DILocation(line: 1903, column: 14, scope: !3731)
!3751 = !DILocation(line: 1903, column: 9, scope: !3731)
!3752 = !DILocation(line: 1903, column: 19, scope: !3731)
!3753 = !DILocation(line: 1903, column: 26, scope: !3731)
!3754 = !DILocation(line: 1904, column: 16, scope: !3731)
!3755 = !DILocation(line: 1904, column: 11, scope: !3731)
!3756 = !DILocation(line: 1904, column: 21, scope: !3731)
!3757 = !DILocation(line: 1904, column: 27, scope: !3731)
!3758 = !DILocation(line: 1904, column: 7, scope: !3731)
!3759 = !DILocation(line: 1903, column: 5, scope: !3731)
!3760 = !DILocation(line: 1905, column: 18, scope: !3731)
!3761 = !DILocation(line: 1905, column: 20, scope: !3731)
!3762 = !DILocation(line: 1905, column: 27, scope: !3731)
!3763 = !DILocation(line: 1905, column: 10, scope: !3731)
!3764 = !DILocation(line: 1905, column: 5, scope: !3731)
!3765 = !DILocation(line: 1905, column: 8, scope: !3731)
!3766 = !DILocation(line: 1906, column: 18, scope: !3731)
!3767 = !DILocation(line: 1906, column: 20, scope: !3731)
!3768 = !DILocation(line: 1906, column: 27, scope: !3731)
!3769 = !DILocation(line: 1906, column: 10, scope: !3731)
!3770 = !DILocation(line: 1906, column: 5, scope: !3731)
!3771 = !DILocation(line: 1906, column: 8, scope: !3731)
!3772 = !DILocation(line: 1907, column: 18, scope: !3731)
!3773 = !DILocation(line: 1907, column: 20, scope: !3731)
!3774 = !DILocation(line: 1907, column: 26, scope: !3731)
!3775 = !DILocation(line: 1907, column: 10, scope: !3731)
!3776 = !DILocation(line: 1907, column: 5, scope: !3731)
!3777 = !DILocation(line: 1907, column: 8, scope: !3731)
!3778 = !DILocation(line: 1908, column: 3, scope: !3731)
!3779 = !DILocation(line: 1911, column: 3, scope: !276)
!3780 = !DILocation(line: 1911, column: 5, scope: !276)
!3781 = !DILocation(line: 1912, column: 10, scope: !276)
!3782 = !DILocation(line: 1912, column: 2, scope: !276)
!3783 = !DILocation(line: 1913, column: 1, scope: !276)
