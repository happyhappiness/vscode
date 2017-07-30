; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_append_filter.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, {}*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_read_filter_bidder = type { i8*, i8*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)*, i32 (%struct.archive_read_filter_bidder*)* }
%struct.archive_read_filter = type { i64, %struct.archive_read_filter_bidder*, %struct.archive_read_filter*, %struct.archive_read*, i32 (%struct.archive_read_filter*)*, i64 (%struct.archive_read_filter*, i8**)*, i64 (%struct.archive_read_filter*, i64)*, i64 (%struct.archive_read_filter*, i64, i32)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*, i32)*, i8*, i8*, i32, i8*, i64, i8*, i64, i8*, i64, i8*, i64, i8, i8, i8 }
%struct.archive_read = type { %struct.archive, %struct.archive_entry*, i32, i64, i64, %struct.archive_read_client, [16 x %struct.archive_read_filter_bidder], %struct.archive_read_filter*, i32, i64, i32, i32, [16 x %struct.archive_format_descriptor], %struct.archive_format_descriptor*, %struct.archive_read_extract*, i32 (%struct.archive_read*)*, %struct.anon }
%struct.archive_read_client = type { i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i32)*, i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*, i8*)*, i32, i32, i64, %struct.archive_read_data_node* }
%struct.archive_read_data_node = type { i64, i64, i8* }
%struct.archive_format_descriptor = type { i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)* }
%struct.archive_read_extract = type { %struct.archive*, void (i8*)*, i8* }
%struct.anon = type { %struct.archive_read_passphrase*, %struct.archive_read_passphrase**, i32, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_read_passphrase = type { i8*, %struct.archive_read_passphrase* }

@.str = private unnamed_addr constant [5 x i8] c"gzip\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"bzip2\00", align 1
@.str.2 = private unnamed_addr constant [14 x i8] c"compress (.Z)\00", align 1
@.str.3 = private unnamed_addr constant [62 x i8] c"Cannot append program filter using archive_read_append_filter\00", align 1
@.str.4 = private unnamed_addr constant [5 x i8] c"lzma\00", align 1
@.str.5 = private unnamed_addr constant [3 x i8] c"xz\00", align 1
@.str.6 = private unnamed_addr constant [3 x i8] c"uu\00", align 1
@.str.7 = private unnamed_addr constant [4 x i8] c"rpm\00", align 1
@.str.8 = private unnamed_addr constant [4 x i8] c"lz4\00", align 1
@.str.9 = private unnamed_addr constant [5 x i8] c"lzip\00", align 1
@.str.10 = private unnamed_addr constant [6 x i8] c"lrzip\00", align 1
@.str.11 = private unnamed_addr constant [30 x i8] c"Invalid filter code specified\00", align 1
@.str.12 = private unnamed_addr constant [40 x i8] c"Internal error: Unable to append filter\00", align 1
@.str.13 = private unnamed_addr constant [14 x i8] c"Out of memory\00", align 1
@.str.14 = private unnamed_addr constant [48 x i8] c"Internal error: Unable to append program filter\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_append_filter(%struct.archive* %_a, i32 %code) #0 !dbg !292 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %code.addr = alloca i32, align 4
  %r1 = alloca i32, align 4
  %r2 = alloca i32, align 4
  %number_bidders = alloca i32, align 4
  %i = alloca i32, align 4
  %str = alloca [20 x i8], align 16
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %filter = alloca %struct.archive_read_filter*, align 8
  %a = alloca %struct.archive_read*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !302, metadata !303), !dbg !304
  store i32 %code, i32* %code.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %code.addr, metadata !305, metadata !303), !dbg !306
  call void @llvm.dbg.declare(metadata i32* %r1, metadata !307, metadata !303), !dbg !308
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !309, metadata !303), !dbg !310
  call void @llvm.dbg.declare(metadata i32* %number_bidders, metadata !311, metadata !303), !dbg !312
  call void @llvm.dbg.declare(metadata i32* %i, metadata !313, metadata !303), !dbg !314
  call void @llvm.dbg.declare(metadata [20 x i8]* %str, metadata !315, metadata !303), !dbg !319
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !320, metadata !303), !dbg !321
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter, metadata !322, metadata !303), !dbg !323
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !324, metadata !303), !dbg !325
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !326
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !327
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !325
  store i32 0, i32* %r2, align 4, !dbg !328
  %2 = load i32, i32* %code.addr, align 4, !dbg !329
  switch i32 %2, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb1
    i32 2, label %sw.bb3
    i32 3, label %sw.bb7
    i32 4, label %sw.bb11
    i32 5, label %sw.bb12
    i32 6, label %sw.bb16
    i32 7, label %sw.bb20
    i32 8, label %sw.bb24
    i32 13, label %sw.bb28
    i32 9, label %sw.bb32
    i32 10, label %sw.bb36
  ], !dbg !330

sw.bb:                                            ; preds = %entry
  store i32 0, i32* %r1, align 4, !dbg !331
  br label %sw.epilog, !dbg !333

sw.bb1:                                           ; preds = %entry
  %arraydecay = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !334
  %call = call i8* @strcpy(i8* %arraydecay, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i32 0, i32 0)) #5, !dbg !335
  %3 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !336
  %call2 = call i32 @archive_read_support_filter_gzip(%struct.archive* %3), !dbg !337
  store i32 %call2, i32* %r1, align 4, !dbg !338
  br label %sw.epilog, !dbg !339

sw.bb3:                                           ; preds = %entry
  %arraydecay4 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !340
  %call5 = call i8* @strcpy(i8* %arraydecay4, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0)) #5, !dbg !341
  %4 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !342
  %call6 = call i32 @archive_read_support_filter_bzip2(%struct.archive* %4), !dbg !343
  store i32 %call6, i32* %r1, align 4, !dbg !344
  br label %sw.epilog, !dbg !345

sw.bb7:                                           ; preds = %entry
  %arraydecay8 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !346
  %call9 = call i8* @strcpy(i8* %arraydecay8, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i32 0, i32 0)) #5, !dbg !347
  %5 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !348
  %call10 = call i32 @archive_read_support_filter_compress(%struct.archive* %5), !dbg !349
  store i32 %call10, i32* %r1, align 4, !dbg !350
  br label %sw.epilog, !dbg !351

sw.bb11:                                          ; preds = %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !352
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !353
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([62 x i8], [62 x i8]* @.str.3, i32 0, i32 0)), !dbg !354
  store i32 -30, i32* %retval, align 4, !dbg !355
  br label %return, !dbg !355

sw.bb12:                                          ; preds = %entry
  %arraydecay13 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !356
  %call14 = call i8* @strcpy(i8* %arraydecay13, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.4, i32 0, i32 0)) #5, !dbg !357
  %7 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !358
  %call15 = call i32 @archive_read_support_filter_lzma(%struct.archive* %7), !dbg !359
  store i32 %call15, i32* %r1, align 4, !dbg !360
  br label %sw.epilog, !dbg !361

sw.bb16:                                          ; preds = %entry
  %arraydecay17 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !362
  %call18 = call i8* @strcpy(i8* %arraydecay17, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.5, i32 0, i32 0)) #5, !dbg !363
  %8 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !364
  %call19 = call i32 @archive_read_support_filter_xz(%struct.archive* %8), !dbg !365
  store i32 %call19, i32* %r1, align 4, !dbg !366
  br label %sw.epilog, !dbg !367

sw.bb20:                                          ; preds = %entry
  %arraydecay21 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !368
  %call22 = call i8* @strcpy(i8* %arraydecay21, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.6, i32 0, i32 0)) #5, !dbg !369
  %9 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !370
  %call23 = call i32 @archive_read_support_filter_uu(%struct.archive* %9), !dbg !371
  store i32 %call23, i32* %r1, align 4, !dbg !372
  br label %sw.epilog, !dbg !373

sw.bb24:                                          ; preds = %entry
  %arraydecay25 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !374
  %call26 = call i8* @strcpy(i8* %arraydecay25, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0)) #5, !dbg !375
  %10 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !376
  %call27 = call i32 @archive_read_support_filter_rpm(%struct.archive* %10), !dbg !377
  store i32 %call27, i32* %r1, align 4, !dbg !378
  br label %sw.epilog, !dbg !379

sw.bb28:                                          ; preds = %entry
  %arraydecay29 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !380
  %call30 = call i8* @strcpy(i8* %arraydecay29, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.8, i32 0, i32 0)) #5, !dbg !381
  %11 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !382
  %call31 = call i32 @archive_read_support_filter_lz4(%struct.archive* %11), !dbg !383
  store i32 %call31, i32* %r1, align 4, !dbg !384
  br label %sw.epilog, !dbg !385

sw.bb32:                                          ; preds = %entry
  %arraydecay33 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !386
  %call34 = call i8* @strcpy(i8* %arraydecay33, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.9, i32 0, i32 0)) #5, !dbg !387
  %12 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !388
  %call35 = call i32 @archive_read_support_filter_lzip(%struct.archive* %12), !dbg !389
  store i32 %call35, i32* %r1, align 4, !dbg !390
  br label %sw.epilog, !dbg !391

sw.bb36:                                          ; preds = %entry
  %arraydecay37 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !392
  %call38 = call i8* @strcpy(i8* %arraydecay37, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.10, i32 0, i32 0)) #5, !dbg !393
  %13 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !394
  %call39 = call i32 @archive_read_support_filter_lrzip(%struct.archive* %13), !dbg !395
  store i32 %call39, i32* %r1, align 4, !dbg !396
  br label %sw.epilog, !dbg !397

sw.default:                                       ; preds = %entry
  %14 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !398
  %archive40 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %14, i32 0, i32 0, !dbg !399
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive40, i32 22, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.11, i32 0, i32 0)), !dbg !400
  store i32 -30, i32* %retval, align 4, !dbg !401
  br label %return, !dbg !401

sw.epilog:                                        ; preds = %sw.bb36, %sw.bb32, %sw.bb28, %sw.bb24, %sw.bb20, %sw.bb16, %sw.bb12, %sw.bb7, %sw.bb3, %sw.bb1, %sw.bb
  %15 = load i32, i32* %code.addr, align 4, !dbg !402
  %cmp = icmp ne i32 %15, 0, !dbg !404
  br i1 %cmp, label %if.then, label %if.end72, !dbg !405

if.then:                                          ; preds = %sw.epilog
  store i32 16, i32* %number_bidders, align 4, !dbg !406
  %16 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !408
  %bidders = getelementptr inbounds %struct.archive_read, %struct.archive_read* %16, i32 0, i32 6, !dbg !409
  %arraydecay41 = getelementptr inbounds [16 x %struct.archive_read_filter_bidder], [16 x %struct.archive_read_filter_bidder]* %bidders, i32 0, i32 0, !dbg !408
  store %struct.archive_read_filter_bidder* %arraydecay41, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !410
  store i32 0, i32* %i, align 4, !dbg !411
  br label %for.cond, !dbg !413

for.cond:                                         ; preds = %for.inc, %if.then
  %17 = load i32, i32* %i, align 4, !dbg !414
  %18 = load i32, i32* %number_bidders, align 4, !dbg !417
  %cmp42 = icmp slt i32 %17, %18, !dbg !418
  br i1 %cmp42, label %for.body, label %for.end, !dbg !419

for.body:                                         ; preds = %for.cond
  %19 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !420
  %name = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %19, i32 0, i32 1, !dbg !423
  %20 = load i8*, i8** %name, align 8, !dbg !423
  %tobool = icmp ne i8* %20, null, !dbg !420
  br i1 %tobool, label %lor.lhs.false, label %if.then47, !dbg !424

lor.lhs.false:                                    ; preds = %for.body
  %21 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !425
  %name43 = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %21, i32 0, i32 1, !dbg !427
  %22 = load i8*, i8** %name43, align 8, !dbg !427
  %arraydecay44 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !428
  %call45 = call i32 @strcmp(i8* %22, i8* %arraydecay44) #6, !dbg !429
  %tobool46 = icmp ne i32 %call45, 0, !dbg !429
  br i1 %tobool46, label %if.end, label %if.then47, !dbg !430

if.then47:                                        ; preds = %lor.lhs.false, %for.body
  br label %for.end, !dbg !431

if.end:                                           ; preds = %lor.lhs.false
  br label %for.inc, !dbg !432

for.inc:                                          ; preds = %if.end
  %23 = load i32, i32* %i, align 4, !dbg !433
  %inc = add nsw i32 %23, 1, !dbg !433
  store i32 %inc, i32* %i, align 4, !dbg !433
  %24 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !435
  %incdec.ptr = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %24, i32 1, !dbg !435
  store %struct.archive_read_filter_bidder* %incdec.ptr, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !435
  br label %for.cond, !dbg !436

for.end:                                          ; preds = %if.then47, %for.cond
  %25 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !437
  %name48 = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %25, i32 0, i32 1, !dbg !439
  %26 = load i8*, i8** %name48, align 8, !dbg !439
  %tobool49 = icmp ne i8* %26, null, !dbg !437
  br i1 %tobool49, label %lor.lhs.false50, label %if.then55, !dbg !440

lor.lhs.false50:                                  ; preds = %for.end
  %27 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !441
  %name51 = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %27, i32 0, i32 1, !dbg !443
  %28 = load i8*, i8** %name51, align 8, !dbg !443
  %arraydecay52 = getelementptr inbounds [20 x i8], [20 x i8]* %str, i32 0, i32 0, !dbg !444
  %call53 = call i32 @strcmp(i8* %28, i8* %arraydecay52) #6, !dbg !445
  %tobool54 = icmp ne i32 %call53, 0, !dbg !445
  br i1 %tobool54, label %if.then55, label %if.end57, !dbg !446

if.then55:                                        ; preds = %lor.lhs.false50, %for.end
  %29 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !447
  %archive56 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %29, i32 0, i32 0, !dbg !449
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive56, i32 22, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @.str.12, i32 0, i32 0)), !dbg !450
  store i32 -30, i32* %retval, align 4, !dbg !451
  br label %return, !dbg !451

if.end57:                                         ; preds = %lor.lhs.false50
  %call58 = call noalias i8* @calloc(i64 1, i64 176) #5, !dbg !452
  %30 = bitcast i8* %call58 to %struct.archive_read_filter*, !dbg !453
  store %struct.archive_read_filter* %30, %struct.archive_read_filter** %filter, align 8, !dbg !454
  %31 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !455
  %cmp59 = icmp eq %struct.archive_read_filter* %31, null, !dbg !457
  br i1 %cmp59, label %if.then60, label %if.end62, !dbg !458

if.then60:                                        ; preds = %if.end57
  %32 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !459
  %archive61 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %32, i32 0, i32 0, !dbg !461
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive61, i32 12, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.13, i32 0, i32 0)), !dbg !462
  store i32 -30, i32* %retval, align 4, !dbg !463
  br label %return, !dbg !463

if.end62:                                         ; preds = %if.end57
  %33 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !464
  %34 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !465
  %bidder63 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %34, i32 0, i32 1, !dbg !466
  store %struct.archive_read_filter_bidder* %33, %struct.archive_read_filter_bidder** %bidder63, align 8, !dbg !467
  %35 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !468
  %36 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !469
  %archive64 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %36, i32 0, i32 3, !dbg !470
  store %struct.archive_read* %35, %struct.archive_read** %archive64, align 8, !dbg !471
  %37 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !472
  %filter65 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %37, i32 0, i32 7, !dbg !473
  %38 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter65, align 8, !dbg !473
  %39 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !474
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %39, i32 0, i32 2, !dbg !475
  store %struct.archive_read_filter* %38, %struct.archive_read_filter** %upstream, align 8, !dbg !476
  %40 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !477
  %41 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !478
  %filter66 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %41, i32 0, i32 7, !dbg !479
  store %struct.archive_read_filter* %40, %struct.archive_read_filter** %filter66, align 8, !dbg !480
  %42 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !481
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %42, i32 0, i32 3, !dbg !482
  %43 = load i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !482
  %44 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !483
  %filter67 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %44, i32 0, i32 7, !dbg !484
  %45 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter67, align 8, !dbg !484
  %call68 = call i32 %43(%struct.archive_read_filter* %45), !dbg !485
  store i32 %call68, i32* %r2, align 4, !dbg !486
  %46 = load i32, i32* %r2, align 4, !dbg !487
  %cmp69 = icmp ne i32 %46, 0, !dbg !489
  br i1 %cmp69, label %if.then70, label %if.end71, !dbg !490

if.then70:                                        ; preds = %if.end62
  %47 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !491
  call void @__archive_read_free_filters(%struct.archive_read* %47), !dbg !493
  store i32 -30, i32* %retval, align 4, !dbg !494
  br label %return, !dbg !494

if.end71:                                         ; preds = %if.end62
  br label %if.end72, !dbg !495

if.end72:                                         ; preds = %if.end71, %sw.epilog
  %48 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !496
  %bypass_filter_bidding = getelementptr inbounds %struct.archive_read, %struct.archive_read* %48, i32 0, i32 8, !dbg !497
  store i32 1, i32* %bypass_filter_bidding, align 8, !dbg !498
  %49 = load i32, i32* %r1, align 4, !dbg !499
  %50 = load i32, i32* %r2, align 4, !dbg !500
  %cmp73 = icmp slt i32 %49, %50, !dbg !501
  br i1 %cmp73, label %cond.true, label %cond.false, !dbg !502

cond.true:                                        ; preds = %if.end72
  %51 = load i32, i32* %r1, align 4, !dbg !503
  br label %cond.end, !dbg !505

cond.false:                                       ; preds = %if.end72
  %52 = load i32, i32* %r2, align 4, !dbg !506
  br label %cond.end, !dbg !508

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %51, %cond.true ], [ %52, %cond.false ], !dbg !509
  store i32 %cond, i32* %retval, align 4, !dbg !511
  br label %return, !dbg !511

return:                                           ; preds = %cond.end, %if.then70, %if.then60, %if.then55, %sw.default, %sw.bb11
  %53 = load i32, i32* %retval, align 4, !dbg !512
  ret i32 %53, !dbg !512
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i8* @strcpy(i8*, i8*) #2

declare i32 @archive_read_support_filter_gzip(%struct.archive*) #3

declare i32 @archive_read_support_filter_bzip2(%struct.archive*) #3

declare i32 @archive_read_support_filter_compress(%struct.archive*) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #3

declare i32 @archive_read_support_filter_lzma(%struct.archive*) #3

declare i32 @archive_read_support_filter_xz(%struct.archive*) #3

declare i32 @archive_read_support_filter_uu(%struct.archive*) #3

declare i32 @archive_read_support_filter_rpm(%struct.archive*) #3

declare i32 @archive_read_support_filter_lz4(%struct.archive*) #3

declare i32 @archive_read_support_filter_lzip(%struct.archive*) #3

declare i32 @archive_read_support_filter_lrzip(%struct.archive*) #3

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #2

declare void @__archive_read_free_filters(%struct.archive_read*) #3

; Function Attrs: nounwind uwtable
define i32 @archive_read_append_filter_program(%struct.archive* %_a, i8* %cmd) #0 !dbg !293 {
entry:
  %_a.addr = alloca %struct.archive*, align 8
  %cmd.addr = alloca i8*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !513, metadata !303), !dbg !514
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !515, metadata !303), !dbg !516
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !517
  %1 = load i8*, i8** %cmd.addr, align 8, !dbg !518
  %call = call i32 @archive_read_append_filter_program_signature(%struct.archive* %0, i8* %1, i8* null, i64 0), !dbg !519
  ret i32 %call, !dbg !520
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_append_filter_program_signature(%struct.archive* %_a, i8* %cmd, i8* %signature, i64 %signature_len) #0 !dbg !296 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %cmd.addr = alloca i8*, align 8
  %signature.addr = alloca i8*, align 8
  %signature_len.addr = alloca i64, align 8
  %r = alloca i32, align 4
  %number_bidders = alloca i32, align 4
  %i = alloca i32, align 4
  %bidder = alloca %struct.archive_read_filter_bidder*, align 8
  %filter = alloca %struct.archive_read_filter*, align 8
  %a = alloca %struct.archive_read*, align 8
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !521, metadata !303), !dbg !522
  store i8* %cmd, i8** %cmd.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %cmd.addr, metadata !523, metadata !303), !dbg !524
  store i8* %signature, i8** %signature.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %signature.addr, metadata !525, metadata !303), !dbg !526
  store i64 %signature_len, i64* %signature_len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %signature_len.addr, metadata !527, metadata !303), !dbg !528
  call void @llvm.dbg.declare(metadata i32* %r, metadata !529, metadata !303), !dbg !530
  call void @llvm.dbg.declare(metadata i32* %number_bidders, metadata !531, metadata !303), !dbg !532
  call void @llvm.dbg.declare(metadata i32* %i, metadata !533, metadata !303), !dbg !534
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter_bidder** %bidder, metadata !535, metadata !303), !dbg !536
  call void @llvm.dbg.declare(metadata %struct.archive_read_filter** %filter, metadata !537, metadata !303), !dbg !538
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !539, metadata !303), !dbg !540
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !541
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !542
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !540
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !543
  %3 = load i8*, i8** %cmd.addr, align 8, !dbg !545
  %4 = load i8*, i8** %signature.addr, align 8, !dbg !546
  %5 = load i64, i64* %signature_len.addr, align 8, !dbg !547
  %call = call i32 @archive_read_support_filter_program_signature(%struct.archive* %2, i8* %3, i8* %4, i64 %5), !dbg !548
  %cmp = icmp ne i32 %call, 0, !dbg !549
  br i1 %cmp, label %if.then, label %if.end, !dbg !550

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !551
  br label %return, !dbg !551

if.end:                                           ; preds = %entry
  store i32 16, i32* %number_bidders, align 4, !dbg !552
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !553
  %bidders = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 6, !dbg !554
  %arraydecay = getelementptr inbounds [16 x %struct.archive_read_filter_bidder], [16 x %struct.archive_read_filter_bidder]* %bidders, i32 0, i32 0, !dbg !553
  store %struct.archive_read_filter_bidder* %arraydecay, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !555
  store i32 0, i32* %i, align 4, !dbg !556
  br label %for.cond, !dbg !558

for.cond:                                         ; preds = %for.inc, %if.end
  %7 = load i32, i32* %i, align 4, !dbg !559
  %8 = load i32, i32* %number_bidders, align 4, !dbg !562
  %cmp1 = icmp slt i32 %7, %8, !dbg !563
  br i1 %cmp1, label %for.body, label %for.end, !dbg !564

for.body:                                         ; preds = %for.cond
  %9 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !565
  %data = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %9, i32 0, i32 0, !dbg !568
  %10 = load i8*, i8** %data, align 8, !dbg !568
  %tobool = icmp ne i8* %10, null, !dbg !565
  br i1 %tobool, label %land.lhs.true, label %if.end4, !dbg !569

land.lhs.true:                                    ; preds = %for.body
  %11 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !570
  %name = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %11, i32 0, i32 1, !dbg !572
  %12 = load i8*, i8** %name, align 8, !dbg !572
  %tobool2 = icmp ne i8* %12, null, !dbg !570
  br i1 %tobool2, label %if.end4, label %if.then3, !dbg !573

if.then3:                                         ; preds = %land.lhs.true
  br label %for.end, !dbg !574

if.end4:                                          ; preds = %land.lhs.true, %for.body
  br label %for.inc, !dbg !575

for.inc:                                          ; preds = %if.end4
  %13 = load i32, i32* %i, align 4, !dbg !576
  %inc = add nsw i32 %13, 1, !dbg !576
  store i32 %inc, i32* %i, align 4, !dbg !576
  %14 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !578
  %incdec.ptr = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %14, i32 1, !dbg !578
  store %struct.archive_read_filter_bidder* %incdec.ptr, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !578
  br label %for.cond, !dbg !579

for.end:                                          ; preds = %if.then3, %for.cond
  %15 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !580
  %data5 = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %15, i32 0, i32 0, !dbg !582
  %16 = load i8*, i8** %data5, align 8, !dbg !582
  %tobool6 = icmp ne i8* %16, null, !dbg !580
  br i1 %tobool6, label %if.end8, label %if.then7, !dbg !583

if.then7:                                         ; preds = %for.end
  %17 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !584
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %17, i32 0, i32 0, !dbg !586
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.14, i32 0, i32 0)), !dbg !587
  store i32 -30, i32* %retval, align 4, !dbg !588
  br label %return, !dbg !588

if.end8:                                          ; preds = %for.end
  %call9 = call noalias i8* @calloc(i64 1, i64 176) #5, !dbg !589
  %18 = bitcast i8* %call9 to %struct.archive_read_filter*, !dbg !590
  store %struct.archive_read_filter* %18, %struct.archive_read_filter** %filter, align 8, !dbg !591
  %19 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !592
  %cmp10 = icmp eq %struct.archive_read_filter* %19, null, !dbg !594
  br i1 %cmp10, label %if.then11, label %if.end13, !dbg !595

if.then11:                                        ; preds = %if.end8
  %20 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !596
  %archive12 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %20, i32 0, i32 0, !dbg !598
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive12, i32 12, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.13, i32 0, i32 0)), !dbg !599
  store i32 -30, i32* %retval, align 4, !dbg !600
  br label %return, !dbg !600

if.end13:                                         ; preds = %if.end8
  %21 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !601
  %22 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !602
  %bidder14 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %22, i32 0, i32 1, !dbg !603
  store %struct.archive_read_filter_bidder* %21, %struct.archive_read_filter_bidder** %bidder14, align 8, !dbg !604
  %23 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !605
  %24 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !606
  %archive15 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %24, i32 0, i32 3, !dbg !607
  store %struct.archive_read* %23, %struct.archive_read** %archive15, align 8, !dbg !608
  %25 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !609
  %filter16 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %25, i32 0, i32 7, !dbg !610
  %26 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter16, align 8, !dbg !610
  %27 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !611
  %upstream = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %27, i32 0, i32 2, !dbg !612
  store %struct.archive_read_filter* %26, %struct.archive_read_filter** %upstream, align 8, !dbg !613
  %28 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter, align 8, !dbg !614
  %29 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !615
  %filter17 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %29, i32 0, i32 7, !dbg !616
  store %struct.archive_read_filter* %28, %struct.archive_read_filter** %filter17, align 8, !dbg !617
  %30 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !618
  %init = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %30, i32 0, i32 3, !dbg !619
  %31 = load i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)** %init, align 8, !dbg !619
  %32 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !620
  %filter18 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %32, i32 0, i32 7, !dbg !621
  %33 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter18, align 8, !dbg !621
  %call19 = call i32 %31(%struct.archive_read_filter* %33), !dbg !622
  store i32 %call19, i32* %r, align 4, !dbg !623
  %34 = load i32, i32* %r, align 4, !dbg !624
  %cmp20 = icmp ne i32 %34, 0, !dbg !626
  br i1 %cmp20, label %if.then21, label %if.end22, !dbg !627

if.then21:                                        ; preds = %if.end13
  %35 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !628
  call void @__archive_read_free_filters(%struct.archive_read* %35), !dbg !630
  store i32 -30, i32* %retval, align 4, !dbg !631
  br label %return, !dbg !631

if.end22:                                         ; preds = %if.end13
  %36 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !632
  %filter23 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %36, i32 0, i32 7, !dbg !633
  %37 = load %struct.archive_read_filter*, %struct.archive_read_filter** %filter23, align 8, !dbg !633
  %name24 = getelementptr inbounds %struct.archive_read_filter, %struct.archive_read_filter* %37, i32 0, i32 11, !dbg !634
  %38 = load i8*, i8** %name24, align 8, !dbg !634
  %39 = load %struct.archive_read_filter_bidder*, %struct.archive_read_filter_bidder** %bidder, align 8, !dbg !635
  %name25 = getelementptr inbounds %struct.archive_read_filter_bidder, %struct.archive_read_filter_bidder* %39, i32 0, i32 1, !dbg !636
  store i8* %38, i8** %name25, align 8, !dbg !637
  %40 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !638
  %bypass_filter_bidding = getelementptr inbounds %struct.archive_read, %struct.archive_read* %40, i32 0, i32 8, !dbg !639
  store i32 1, i32* %bypass_filter_bidding, align 8, !dbg !640
  %41 = load i32, i32* %r, align 4, !dbg !641
  store i32 %41, i32* %retval, align 4, !dbg !642
  br label %return, !dbg !642

return:                                           ; preds = %if.end22, %if.then21, %if.then11, %if.then7, %if.then
  %42 = load i32, i32* %retval, align 4, !dbg !643
  ret i32 %42, !dbg !643
}

declare i32 @archive_read_support_filter_program_signature(%struct.archive*, i8*, i8*, i64) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!299, !300}
!llvm.ident = !{!301}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !291)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_append_filter.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !169, !122}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read", file: !6, line: 159, size: 20288, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !110, !111, !112, !113, !114, !158, !222, !223, !224, !225, !226, !227, !260, !262, !272, !273}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 160, baseType: !9, size: 1280, align: 64)
!9 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !10, line: 89, size: 1280, align: 64, elements: !11)
!10 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!11 = !{!12, !14, !15, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !104, !105, !106, !107, !108, !109}
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
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 102, baseType: !40)
!39 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
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
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !92, line: 70, flags: DIFlagFwdDecl)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !9, file: !10, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !9, file: !10, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !9, file: !10, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !9, file: !10, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !9, file: !10, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !9, file: !10, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !5, file: !6, line: 162, baseType: !30, size: 64, align: 64, offset: 1280)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 165, baseType: !23, size: 32, align: 32, offset: 1344)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 166, baseType: !52, size: 64, align: 64, offset: 1408)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 167, baseType: !52, size: 64, align: 64, offset: 1472)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "client", scope: !5, file: !6, line: 170, baseType: !115, size: 576, align: 64, offset: 1536)
!115 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_client", file: !6, line: 134, size: 576, align: 64, elements: !116)
!116 = !{!117, !123, !129, !135, !140, !143, !148, !149, !150, !151}
!117 = !DIDerivedType(tag: DW_TAG_member, name: "opener", scope: !115, file: !6, line: 135, baseType: !118, size: 64, align: 64)
!118 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !119, size: 64, align: 64)
!119 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !120)
!120 = !DISubroutineType(types: !121)
!121 = !{!23, !24, !122}
!122 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "reader", scope: !115, file: !6, line: 136, baseType: !124, size: 64, align: 64, offset: 64)
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_read_callback", file: !32, line: 218, baseType: !126)
!126 = !DISubroutineType(types: !127)
!127 = !{!128, !24, !122, !64}
!128 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "skipper", scope: !115, file: !6, line: 137, baseType: !130, size: 64, align: 64, offset: 128)
!130 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !131, size: 64, align: 64)
!131 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_skip_callback", file: !32, line: 226, baseType: !132)
!132 = !DISubroutineType(types: !133)
!133 = !{!134, !24, !122, !134}
!134 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !32, line: 73, baseType: !52)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "seeker", scope: !115, file: !6, line: 138, baseType: !136, size: 64, align: 64, offset: 192)
!136 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !137, size: 64, align: 64)
!137 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_seek_callback", file: !32, line: 233, baseType: !138)
!138 = !DISubroutineType(types: !139)
!139 = !{!134, !24, !122, !134, !23}
!140 = !DIDerivedType(tag: DW_TAG_member, name: "closer", scope: !115, file: !6, line: 139, baseType: !141, size: 64, align: 64, offset: 256)
!141 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !120)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "switcher", scope: !115, file: !6, line: 140, baseType: !144, size: 64, align: 64, offset: 320)
!144 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !145, size: 64, align: 64)
!145 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_switch_callback", file: !32, line: 249, baseType: !146)
!146 = !DISubroutineType(types: !147)
!147 = !{!23, !24, !122, !122}
!148 = !DIDerivedType(tag: DW_TAG_member, name: "nodes", scope: !115, file: !6, line: 141, baseType: !13, size: 32, align: 32, offset: 384)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "cursor", scope: !115, file: !6, line: 142, baseType: !13, size: 32, align: 32, offset: 416)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !115, file: !6, line: 143, baseType: !52, size: 64, align: 64, offset: 448)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "dataset", scope: !115, file: !6, line: 144, baseType: !152, size: 64, align: 64, offset: 512)
!152 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !153, size: 64, align: 64)
!153 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_data_node", file: !6, line: 129, size: 192, align: 64, elements: !154)
!154 = !{!155, !156, !157}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "begin_position", scope: !153, file: !6, line: 130, baseType: !52, size: 64, align: 64)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !153, file: !6, line: 131, baseType: !52, size: 64, align: 64, offset: 64)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !153, file: !6, line: 132, baseType: !122, size: 64, align: 64, offset: 128)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "bidders", scope: !5, file: !6, line: 173, baseType: !159, size: 6144, align: 64, offset: 2112)
!159 = !DICompositeType(tag: DW_TAG_array_type, baseType: !160, size: 6144, align: 64, elements: !220)
!160 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter_bidder", file: !6, line: 60, size: 384, align: 64, elements: !161)
!161 = !{!162, !163, !164, !211, !212, !216}
!162 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !160, file: !6, line: 62, baseType: !122, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !160, file: !6, line: 64, baseType: !80, size: 64, align: 64, offset: 64)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !160, file: !6, line: 66, baseType: !165, size: 64, align: 64, offset: 128)
!165 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !166, size: 64, align: 64)
!166 = !DISubroutineType(types: !167)
!167 = !{!23, !168, !169}
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !160, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !170, size: 64, align: 64)
!170 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter", file: !6, line: 82, size: 1408, align: 64, elements: !171)
!171 = !{!172, !173, !174, !175, !176, !180, !184, !188, !192, !193, !197, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210}
!172 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !170, file: !6, line: 83, baseType: !52, size: 64, align: 64)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "bidder", scope: !170, file: !6, line: 86, baseType: !168, size: 64, align: 64, offset: 64)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "upstream", scope: !170, file: !6, line: 87, baseType: !169, size: 64, align: 64, offset: 128)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !170, file: !6, line: 88, baseType: !4, size: 64, align: 64, offset: 192)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !170, file: !6, line: 90, baseType: !177, size: 64, align: 64, offset: 256)
!177 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !178, size: 64, align: 64)
!178 = !DISubroutineType(types: !179)
!179 = !{!23, !169}
!180 = !DIDerivedType(tag: DW_TAG_member, name: "read", scope: !170, file: !6, line: 92, baseType: !181, size: 64, align: 64, offset: 320)
!181 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !182, size: 64, align: 64)
!182 = !DISubroutineType(types: !183)
!183 = !{!38, !169, !64}
!184 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !170, file: !6, line: 94, baseType: !185, size: 64, align: 64, offset: 384)
!185 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !186, size: 64, align: 64)
!186 = !DISubroutineType(types: !187)
!187 = !{!52, !169, !52}
!188 = !DIDerivedType(tag: DW_TAG_member, name: "seek", scope: !170, file: !6, line: 96, baseType: !189, size: 64, align: 64, offset: 448)
!189 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !190, size: 64, align: 64)
!190 = !DISubroutineType(types: !191)
!191 = !{!52, !169, !52, !23}
!192 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !170, file: !6, line: 98, baseType: !177, size: 64, align: 64, offset: 512)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "sswitch", scope: !170, file: !6, line: 100, baseType: !194, size: 64, align: 64, offset: 576)
!194 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !195, size: 64, align: 64)
!195 = !DISubroutineType(types: !196)
!196 = !{!23, !169, !13}
!197 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !170, file: !6, line: 102, baseType: !122, size: 64, align: 64, offset: 640)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !170, file: !6, line: 104, baseType: !80, size: 64, align: 64, offset: 704)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !170, file: !6, line: 105, baseType: !23, size: 32, align: 32, offset: 768)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !170, file: !6, line: 108, baseType: !95, size: 64, align: 64, offset: 832)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !170, file: !6, line: 109, baseType: !45, size: 64, align: 64, offset: 896)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !170, file: !6, line: 110, baseType: !95, size: 64, align: 64, offset: 960)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !170, file: !6, line: 111, baseType: !45, size: 64, align: 64, offset: 1024)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "client_buff", scope: !170, file: !6, line: 112, baseType: !43, size: 64, align: 64, offset: 1088)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "client_total", scope: !170, file: !6, line: 113, baseType: !45, size: 64, align: 64, offset: 1152)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "client_next", scope: !170, file: !6, line: 114, baseType: !80, size: 64, align: 64, offset: 1216)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "client_avail", scope: !170, file: !6, line: 115, baseType: !45, size: 64, align: 64, offset: 1280)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_file", scope: !170, file: !6, line: 116, baseType: !82, size: 8, align: 8, offset: 1344)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "closed", scope: !170, file: !6, line: 117, baseType: !82, size: 8, align: 8, offset: 1352)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "fatal", scope: !170, file: !6, line: 118, baseType: !82, size: 8, align: 8, offset: 1360)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !160, file: !6, line: 69, baseType: !177, size: 64, align: 64, offset: 192)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !160, file: !6, line: 71, baseType: !213, size: 64, align: 64, offset: 256)
!213 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !214, size: 64, align: 64)
!214 = !DISubroutineType(types: !215)
!215 = !{!23, !168, !80, !80}
!216 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !160, file: !6, line: 74, baseType: !217, size: 64, align: 64, offset: 320)
!217 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !218, size: 64, align: 64)
!218 = !DISubroutineType(types: !219)
!219 = !{!23, !168}
!220 = !{!221}
!221 = !DISubrange(count: 16)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !5, file: !6, line: 176, baseType: !169, size: 64, align: 64, offset: 8256)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "bypass_filter_bidding", scope: !5, file: !6, line: 179, baseType: !23, size: 32, align: 32, offset: 8320)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "header_position", scope: !5, file: !6, line: 182, baseType: !52, size: 64, align: 64, offset: 8384)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "data_start_node", scope: !5, file: !6, line: 185, baseType: !13, size: 32, align: 32, offset: 8448)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "data_end_node", scope: !5, file: !6, line: 186, baseType: !13, size: 32, align: 32, offset: 8480)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "formats", scope: !5, file: !6, line: 209, baseType: !228, size: 11264, align: 64, offset: 8512)
!228 = !DICompositeType(tag: DW_TAG_array_type, baseType: !229, size: 11264, align: 64, elements: !220)
!229 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_format_descriptor", file: !6, line: 196, size: 704, align: 64, elements: !230)
!230 = !{!231, !232, !233, !237, !241, !245, !249, !253, !257, !258, !259}
!231 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !229, file: !6, line: 197, baseType: !122, size: 64, align: 64)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !229, file: !6, line: 198, baseType: !80, size: 64, align: 64, offset: 64)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !229, file: !6, line: 199, baseType: !234, size: 64, align: 64, offset: 128)
!234 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !235, size: 64, align: 64)
!235 = !DISubroutineType(types: !236)
!236 = !{!23, !4, !23}
!237 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !229, file: !6, line: 200, baseType: !238, size: 64, align: 64, offset: 192)
!238 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !239, size: 64, align: 64)
!239 = !DISubroutineType(types: !240)
!240 = !{!23, !4, !80, !80}
!241 = !DIDerivedType(tag: DW_TAG_member, name: "read_header", scope: !229, file: !6, line: 202, baseType: !242, size: 64, align: 64, offset: 256)
!242 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !243, size: 64, align: 64)
!243 = !DISubroutineType(types: !244)
!244 = !{!23, !4, !30}
!245 = !DIDerivedType(tag: DW_TAG_member, name: "read_data", scope: !229, file: !6, line: 203, baseType: !246, size: 64, align: 64, offset: 320)
!246 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !247, size: 64, align: 64)
!247 = !DISubroutineType(types: !248)
!248 = !{!23, !4, !64, !65, !66}
!249 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_skip", scope: !229, file: !6, line: 204, baseType: !250, size: 64, align: 64, offset: 384)
!250 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !251, size: 64, align: 64)
!251 = !DISubroutineType(types: !252)
!252 = !{!23, !4}
!253 = !DIDerivedType(tag: DW_TAG_member, name: "seek_data", scope: !229, file: !6, line: 205, baseType: !254, size: 64, align: 64, offset: 448)
!254 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !255, size: 64, align: 64)
!255 = !DISubroutineType(types: !256)
!256 = !{!52, !4, !52, !23}
!257 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !229, file: !6, line: 206, baseType: !250, size: 64, align: 64, offset: 512)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "format_capabilties", scope: !229, file: !6, line: 207, baseType: !250, size: 64, align: 64, offset: 576)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "has_encrypted_entries", scope: !229, file: !6, line: 208, baseType: !250, size: 64, align: 64, offset: 640)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "format", scope: !5, file: !6, line: 210, baseType: !261, size: 64, align: 64, offset: 19776)
!261 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !229, size: 64, align: 64)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "extract", scope: !5, file: !6, line: 215, baseType: !263, size: 64, align: 64, offset: 19840)
!263 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !264, size: 64, align: 64)
!264 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_extract", file: !6, line: 151, size: 192, align: 64, elements: !265)
!265 = !{!266, !267, !271}
!266 = !DIDerivedType(tag: DW_TAG_member, name: "ad", scope: !264, file: !6, line: 152, baseType: !24, size: 64, align: 64)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress", scope: !264, file: !6, line: 155, baseType: !268, size: 64, align: 64, offset: 64)
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !269, size: 64, align: 64)
!269 = !DISubroutineType(types: !270)
!270 = !{null, !122}
!271 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress_user_data", scope: !264, file: !6, line: 156, baseType: !122, size: 64, align: 64, offset: 128)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_archive_extract", scope: !5, file: !6, line: 216, baseType: !250, size: 64, align: 64, offset: 19904)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "passphrases", scope: !5, file: !6, line: 227, baseType: !274, size: 320, align: 64, offset: 19968)
!274 = !DICompositeType(tag: DW_TAG_structure_type, scope: !5, file: !6, line: 221, size: 320, align: 64, elements: !275)
!275 = !{!276, !282, !284, !285, !290}
!276 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !274, file: !6, line: 222, baseType: !277, size: 64, align: 64)
!277 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !278, size: 64, align: 64)
!278 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_passphrase", file: !6, line: 146, size: 128, align: 64, elements: !279)
!279 = !{!280, !281}
!280 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !278, file: !6, line: 147, baseType: !95, size: 64, align: 64)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !278, file: !6, line: 148, baseType: !277, size: 64, align: 64, offset: 64)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !274, file: !6, line: 223, baseType: !283, size: 64, align: 64, offset: 64)
!283 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !277, size: 64, align: 64)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "candidate", scope: !274, file: !6, line: 224, baseType: !23, size: 32, align: 32, offset: 128)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !274, file: !6, line: 225, baseType: !286, size: 64, align: 64, offset: 192)
!286 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !287, size: 64, align: 64)
!287 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !288)
!288 = !DISubroutineType(types: !289)
!289 = !{!80, !24, !122}
!290 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !274, file: !6, line: 226, baseType: !122, size: 64, align: 64, offset: 256)
!291 = !{!292, !293, !296}
!292 = distinct !DISubprogram(name: "archive_read_append_filter", scope: !1, file: !1, line: 38, type: !74, isLocal: false, isDefinition: true, scopeLine: 39, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!293 = distinct !DISubprogram(name: "archive_read_append_filter_program", scope: !1, file: !1, line: 146, type: !294, isLocal: false, isDefinition: true, scopeLine: 147, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!294 = !DISubroutineType(types: !295)
!295 = !{!23, !24, !80}
!296 = distinct !DISubprogram(name: "archive_read_append_filter_program_signature", scope: !1, file: !1, line: 152, type: !297, isLocal: false, isDefinition: true, scopeLine: 154, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!297 = !DISubroutineType(types: !298)
!298 = !{!23, !24, !80, !43, !45}
!299 = !{i32 2, !"Dwarf Version", i32 4}
!300 = !{i32 2, !"Debug Info Version", i32 3}
!301 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!302 = !DILocalVariable(name: "_a", arg: 1, scope: !292, file: !1, line: 38, type: !24)
!303 = !DIExpression()
!304 = !DILocation(line: 38, column: 44, scope: !292)
!305 = !DILocalVariable(name: "code", arg: 2, scope: !292, file: !1, line: 38, type: !23)
!306 = !DILocation(line: 38, column: 52, scope: !292)
!307 = !DILocalVariable(name: "r1", scope: !292, file: !1, line: 40, type: !23)
!308 = !DILocation(line: 40, column: 7, scope: !292)
!309 = !DILocalVariable(name: "r2", scope: !292, file: !1, line: 40, type: !23)
!310 = !DILocation(line: 40, column: 11, scope: !292)
!311 = !DILocalVariable(name: "number_bidders", scope: !292, file: !1, line: 40, type: !23)
!312 = !DILocation(line: 40, column: 15, scope: !292)
!313 = !DILocalVariable(name: "i", scope: !292, file: !1, line: 40, type: !23)
!314 = !DILocation(line: 40, column: 31, scope: !292)
!315 = !DILocalVariable(name: "str", scope: !292, file: !1, line: 41, type: !316)
!316 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 160, align: 8, elements: !317)
!317 = !{!318}
!318 = !DISubrange(count: 20)
!319 = !DILocation(line: 41, column: 8, scope: !292)
!320 = !DILocalVariable(name: "bidder", scope: !292, file: !1, line: 42, type: !168)
!321 = !DILocation(line: 42, column: 38, scope: !292)
!322 = !DILocalVariable(name: "filter", scope: !292, file: !1, line: 43, type: !169)
!323 = !DILocation(line: 43, column: 31, scope: !292)
!324 = !DILocalVariable(name: "a", scope: !292, file: !1, line: 44, type: !4)
!325 = !DILocation(line: 44, column: 24, scope: !292)
!326 = !DILocation(line: 44, column: 51, scope: !292)
!327 = !DILocation(line: 44, column: 28, scope: !292)
!328 = !DILocation(line: 46, column: 6, scope: !292)
!329 = !DILocation(line: 47, column: 11, scope: !292)
!330 = !DILocation(line: 47, column: 3, scope: !292)
!331 = !DILocation(line: 54, column: 10, scope: !332)
!332 = distinct !DILexicalBlock(scope: !292, file: !1, line: 48, column: 3)
!333 = !DILocation(line: 55, column: 7, scope: !332)
!334 = !DILocation(line: 57, column: 14, scope: !332)
!335 = !DILocation(line: 57, column: 7, scope: !332)
!336 = !DILocation(line: 58, column: 45, scope: !332)
!337 = !DILocation(line: 58, column: 12, scope: !332)
!338 = !DILocation(line: 58, column: 10, scope: !332)
!339 = !DILocation(line: 59, column: 7, scope: !332)
!340 = !DILocation(line: 61, column: 14, scope: !332)
!341 = !DILocation(line: 61, column: 7, scope: !332)
!342 = !DILocation(line: 62, column: 46, scope: !332)
!343 = !DILocation(line: 62, column: 12, scope: !332)
!344 = !DILocation(line: 62, column: 10, scope: !332)
!345 = !DILocation(line: 63, column: 7, scope: !332)
!346 = !DILocation(line: 65, column: 14, scope: !332)
!347 = !DILocation(line: 65, column: 7, scope: !332)
!348 = !DILocation(line: 66, column: 49, scope: !332)
!349 = !DILocation(line: 66, column: 12, scope: !332)
!350 = !DILocation(line: 66, column: 10, scope: !332)
!351 = !DILocation(line: 67, column: 7, scope: !332)
!352 = !DILocation(line: 69, column: 26, scope: !332)
!353 = !DILocation(line: 69, column: 29, scope: !332)
!354 = !DILocation(line: 69, column: 7, scope: !332)
!355 = !DILocation(line: 71, column: 7, scope: !332)
!356 = !DILocation(line: 73, column: 14, scope: !332)
!357 = !DILocation(line: 73, column: 7, scope: !332)
!358 = !DILocation(line: 74, column: 45, scope: !332)
!359 = !DILocation(line: 74, column: 12, scope: !332)
!360 = !DILocation(line: 74, column: 10, scope: !332)
!361 = !DILocation(line: 75, column: 7, scope: !332)
!362 = !DILocation(line: 77, column: 14, scope: !332)
!363 = !DILocation(line: 77, column: 7, scope: !332)
!364 = !DILocation(line: 78, column: 43, scope: !332)
!365 = !DILocation(line: 78, column: 12, scope: !332)
!366 = !DILocation(line: 78, column: 10, scope: !332)
!367 = !DILocation(line: 79, column: 7, scope: !332)
!368 = !DILocation(line: 81, column: 14, scope: !332)
!369 = !DILocation(line: 81, column: 7, scope: !332)
!370 = !DILocation(line: 82, column: 43, scope: !332)
!371 = !DILocation(line: 82, column: 12, scope: !332)
!372 = !DILocation(line: 82, column: 10, scope: !332)
!373 = !DILocation(line: 83, column: 7, scope: !332)
!374 = !DILocation(line: 85, column: 14, scope: !332)
!375 = !DILocation(line: 85, column: 7, scope: !332)
!376 = !DILocation(line: 86, column: 44, scope: !332)
!377 = !DILocation(line: 86, column: 12, scope: !332)
!378 = !DILocation(line: 86, column: 10, scope: !332)
!379 = !DILocation(line: 87, column: 7, scope: !332)
!380 = !DILocation(line: 89, column: 14, scope: !332)
!381 = !DILocation(line: 89, column: 7, scope: !332)
!382 = !DILocation(line: 90, column: 44, scope: !332)
!383 = !DILocation(line: 90, column: 12, scope: !332)
!384 = !DILocation(line: 90, column: 10, scope: !332)
!385 = !DILocation(line: 91, column: 7, scope: !332)
!386 = !DILocation(line: 93, column: 14, scope: !332)
!387 = !DILocation(line: 93, column: 7, scope: !332)
!388 = !DILocation(line: 94, column: 45, scope: !332)
!389 = !DILocation(line: 94, column: 12, scope: !332)
!390 = !DILocation(line: 94, column: 10, scope: !332)
!391 = !DILocation(line: 95, column: 7, scope: !332)
!392 = !DILocation(line: 97, column: 14, scope: !332)
!393 = !DILocation(line: 97, column: 7, scope: !332)
!394 = !DILocation(line: 98, column: 46, scope: !332)
!395 = !DILocation(line: 98, column: 12, scope: !332)
!396 = !DILocation(line: 98, column: 10, scope: !332)
!397 = !DILocation(line: 99, column: 7, scope: !332)
!398 = !DILocation(line: 101, column: 26, scope: !332)
!399 = !DILocation(line: 101, column: 29, scope: !332)
!400 = !DILocation(line: 101, column: 7, scope: !332)
!401 = !DILocation(line: 103, column: 7, scope: !332)
!402 = !DILocation(line: 106, column: 7, scope: !403)
!403 = distinct !DILexicalBlock(scope: !292, file: !1, line: 106, column: 7)
!404 = !DILocation(line: 106, column: 12, scope: !403)
!405 = !DILocation(line: 106, column: 7, scope: !292)
!406 = !DILocation(line: 108, column: 20, scope: !407)
!407 = distinct !DILexicalBlock(scope: !403, file: !1, line: 107, column: 3)
!408 = !DILocation(line: 110, column: 14, scope: !407)
!409 = !DILocation(line: 110, column: 17, scope: !407)
!410 = !DILocation(line: 110, column: 12, scope: !407)
!411 = !DILocation(line: 111, column: 12, scope: !412)
!412 = distinct !DILexicalBlock(scope: !407, file: !1, line: 111, column: 5)
!413 = !DILocation(line: 111, column: 10, scope: !412)
!414 = !DILocation(line: 111, column: 17, scope: !415)
!415 = !DILexicalBlockFile(scope: !416, file: !1, discriminator: 1)
!416 = distinct !DILexicalBlock(scope: !412, file: !1, line: 111, column: 5)
!417 = !DILocation(line: 111, column: 21, scope: !415)
!418 = !DILocation(line: 111, column: 19, scope: !415)
!419 = !DILocation(line: 111, column: 5, scope: !415)
!420 = !DILocation(line: 113, column: 12, scope: !421)
!421 = distinct !DILexicalBlock(scope: !422, file: !1, line: 113, column: 11)
!422 = distinct !DILexicalBlock(scope: !416, file: !1, line: 112, column: 5)
!423 = !DILocation(line: 113, column: 20, scope: !421)
!424 = !DILocation(line: 113, column: 25, scope: !421)
!425 = !DILocation(line: 113, column: 36, scope: !426)
!426 = !DILexicalBlockFile(scope: !421, file: !1, discriminator: 1)
!427 = !DILocation(line: 113, column: 44, scope: !426)
!428 = !DILocation(line: 113, column: 50, scope: !426)
!429 = !DILocation(line: 113, column: 29, scope: !426)
!430 = !DILocation(line: 113, column: 11, scope: !426)
!431 = !DILocation(line: 114, column: 9, scope: !421)
!432 = !DILocation(line: 115, column: 5, scope: !422)
!433 = !DILocation(line: 111, column: 38, scope: !434)
!434 = !DILexicalBlockFile(scope: !416, file: !1, discriminator: 2)
!435 = !DILocation(line: 111, column: 48, scope: !434)
!436 = !DILocation(line: 111, column: 5, scope: !434)
!437 = !DILocation(line: 116, column: 10, scope: !438)
!438 = distinct !DILexicalBlock(scope: !407, file: !1, line: 116, column: 9)
!439 = !DILocation(line: 116, column: 18, scope: !438)
!440 = !DILocation(line: 116, column: 23, scope: !438)
!441 = !DILocation(line: 116, column: 33, scope: !442)
!442 = !DILexicalBlockFile(scope: !438, file: !1, discriminator: 1)
!443 = !DILocation(line: 116, column: 41, scope: !442)
!444 = !DILocation(line: 116, column: 47, scope: !442)
!445 = !DILocation(line: 116, column: 26, scope: !442)
!446 = !DILocation(line: 116, column: 9, scope: !442)
!447 = !DILocation(line: 118, column: 26, scope: !448)
!448 = distinct !DILexicalBlock(scope: !438, file: !1, line: 117, column: 5)
!449 = !DILocation(line: 118, column: 29, scope: !448)
!450 = !DILocation(line: 118, column: 7, scope: !448)
!451 = !DILocation(line: 120, column: 7, scope: !448)
!452 = !DILocation(line: 124, column: 41, scope: !407)
!453 = !DILocation(line: 124, column: 11, scope: !407)
!454 = !DILocation(line: 124, column: 9, scope: !407)
!455 = !DILocation(line: 125, column: 9, scope: !456)
!456 = distinct !DILexicalBlock(scope: !407, file: !1, line: 125, column: 9)
!457 = !DILocation(line: 125, column: 16, scope: !456)
!458 = !DILocation(line: 125, column: 9, scope: !407)
!459 = !DILocation(line: 127, column: 26, scope: !460)
!460 = distinct !DILexicalBlock(scope: !456, file: !1, line: 126, column: 5)
!461 = !DILocation(line: 127, column: 29, scope: !460)
!462 = !DILocation(line: 127, column: 7, scope: !460)
!463 = !DILocation(line: 128, column: 7, scope: !460)
!464 = !DILocation(line: 130, column: 22, scope: !407)
!465 = !DILocation(line: 130, column: 5, scope: !407)
!466 = !DILocation(line: 130, column: 13, scope: !407)
!467 = !DILocation(line: 130, column: 20, scope: !407)
!468 = !DILocation(line: 131, column: 23, scope: !407)
!469 = !DILocation(line: 131, column: 5, scope: !407)
!470 = !DILocation(line: 131, column: 13, scope: !407)
!471 = !DILocation(line: 131, column: 21, scope: !407)
!472 = !DILocation(line: 132, column: 24, scope: !407)
!473 = !DILocation(line: 132, column: 27, scope: !407)
!474 = !DILocation(line: 132, column: 5, scope: !407)
!475 = !DILocation(line: 132, column: 13, scope: !407)
!476 = !DILocation(line: 132, column: 22, scope: !407)
!477 = !DILocation(line: 133, column: 17, scope: !407)
!478 = !DILocation(line: 133, column: 5, scope: !407)
!479 = !DILocation(line: 133, column: 8, scope: !407)
!480 = !DILocation(line: 133, column: 15, scope: !407)
!481 = !DILocation(line: 134, column: 11, scope: !407)
!482 = !DILocation(line: 134, column: 19, scope: !407)
!483 = !DILocation(line: 134, column: 25, scope: !407)
!484 = !DILocation(line: 134, column: 28, scope: !407)
!485 = !DILocation(line: 134, column: 10, scope: !407)
!486 = !DILocation(line: 134, column: 8, scope: !407)
!487 = !DILocation(line: 135, column: 9, scope: !488)
!488 = distinct !DILexicalBlock(scope: !407, file: !1, line: 135, column: 9)
!489 = !DILocation(line: 135, column: 12, scope: !488)
!490 = !DILocation(line: 135, column: 9, scope: !407)
!491 = !DILocation(line: 136, column: 35, scope: !492)
!492 = distinct !DILexicalBlock(scope: !488, file: !1, line: 135, column: 27)
!493 = !DILocation(line: 136, column: 7, scope: !492)
!494 = !DILocation(line: 137, column: 7, scope: !492)
!495 = !DILocation(line: 139, column: 3, scope: !407)
!496 = !DILocation(line: 141, column: 3, scope: !292)
!497 = !DILocation(line: 141, column: 6, scope: !292)
!498 = !DILocation(line: 141, column: 28, scope: !292)
!499 = !DILocation(line: 142, column: 11, scope: !292)
!500 = !DILocation(line: 142, column: 16, scope: !292)
!501 = !DILocation(line: 142, column: 14, scope: !292)
!502 = !DILocation(line: 142, column: 10, scope: !292)
!503 = !DILocation(line: 142, column: 22, scope: !504)
!504 = !DILexicalBlockFile(scope: !292, file: !1, discriminator: 1)
!505 = !DILocation(line: 142, column: 10, scope: !504)
!506 = !DILocation(line: 142, column: 27, scope: !507)
!507 = !DILexicalBlockFile(scope: !292, file: !1, discriminator: 2)
!508 = !DILocation(line: 142, column: 10, scope: !507)
!509 = !DILocation(line: 142, column: 10, scope: !510)
!510 = !DILexicalBlockFile(scope: !292, file: !1, discriminator: 3)
!511 = !DILocation(line: 142, column: 3, scope: !510)
!512 = !DILocation(line: 143, column: 1, scope: !292)
!513 = !DILocalVariable(name: "_a", arg: 1, scope: !293, file: !1, line: 146, type: !24)
!514 = !DILocation(line: 146, column: 52, scope: !293)
!515 = !DILocalVariable(name: "cmd", arg: 2, scope: !293, file: !1, line: 146, type: !80)
!516 = !DILocation(line: 146, column: 68, scope: !293)
!517 = !DILocation(line: 148, column: 56, scope: !293)
!518 = !DILocation(line: 148, column: 60, scope: !293)
!519 = !DILocation(line: 148, column: 11, scope: !293)
!520 = !DILocation(line: 148, column: 3, scope: !293)
!521 = !DILocalVariable(name: "_a", arg: 1, scope: !296, file: !1, line: 152, type: !24)
!522 = !DILocation(line: 152, column: 62, scope: !296)
!523 = !DILocalVariable(name: "cmd", arg: 2, scope: !296, file: !1, line: 153, type: !80)
!524 = !DILocation(line: 153, column: 15, scope: !296)
!525 = !DILocalVariable(name: "signature", arg: 3, scope: !296, file: !1, line: 153, type: !43)
!526 = !DILocation(line: 153, column: 32, scope: !296)
!527 = !DILocalVariable(name: "signature_len", arg: 4, scope: !296, file: !1, line: 153, type: !45)
!528 = !DILocation(line: 153, column: 50, scope: !296)
!529 = !DILocalVariable(name: "r", scope: !296, file: !1, line: 155, type: !23)
!530 = !DILocation(line: 155, column: 7, scope: !296)
!531 = !DILocalVariable(name: "number_bidders", scope: !296, file: !1, line: 155, type: !23)
!532 = !DILocation(line: 155, column: 10, scope: !296)
!533 = !DILocalVariable(name: "i", scope: !296, file: !1, line: 155, type: !23)
!534 = !DILocation(line: 155, column: 26, scope: !296)
!535 = !DILocalVariable(name: "bidder", scope: !296, file: !1, line: 156, type: !168)
!536 = !DILocation(line: 156, column: 38, scope: !296)
!537 = !DILocalVariable(name: "filter", scope: !296, file: !1, line: 157, type: !169)
!538 = !DILocation(line: 157, column: 31, scope: !296)
!539 = !DILocalVariable(name: "a", scope: !296, file: !1, line: 158, type: !4)
!540 = !DILocation(line: 158, column: 24, scope: !296)
!541 = !DILocation(line: 158, column: 51, scope: !296)
!542 = !DILocation(line: 158, column: 28, scope: !296)
!543 = !DILocation(line: 160, column: 53, scope: !544)
!544 = distinct !DILexicalBlock(scope: !296, file: !1, line: 160, column: 7)
!545 = !DILocation(line: 160, column: 57, scope: !544)
!546 = !DILocation(line: 160, column: 62, scope: !544)
!547 = !DILocation(line: 161, column: 5, scope: !544)
!548 = !DILocation(line: 160, column: 7, scope: !544)
!549 = !DILocation(line: 161, column: 20, scope: !544)
!550 = !DILocation(line: 160, column: 7, scope: !296)
!551 = !DILocation(line: 162, column: 5, scope: !544)
!552 = !DILocation(line: 164, column: 18, scope: !296)
!553 = !DILocation(line: 166, column: 12, scope: !296)
!554 = !DILocation(line: 166, column: 15, scope: !296)
!555 = !DILocation(line: 166, column: 10, scope: !296)
!556 = !DILocation(line: 167, column: 10, scope: !557)
!557 = distinct !DILexicalBlock(scope: !296, file: !1, line: 167, column: 3)
!558 = !DILocation(line: 167, column: 8, scope: !557)
!559 = !DILocation(line: 167, column: 15, scope: !560)
!560 = !DILexicalBlockFile(scope: !561, file: !1, discriminator: 1)
!561 = distinct !DILexicalBlock(scope: !557, file: !1, line: 167, column: 3)
!562 = !DILocation(line: 167, column: 19, scope: !560)
!563 = !DILocation(line: 167, column: 17, scope: !560)
!564 = !DILocation(line: 167, column: 3, scope: !560)
!565 = !DILocation(line: 170, column: 9, scope: !566)
!566 = distinct !DILexicalBlock(scope: !567, file: !1, line: 170, column: 9)
!567 = distinct !DILexicalBlock(scope: !561, file: !1, line: 168, column: 3)
!568 = !DILocation(line: 170, column: 17, scope: !566)
!569 = !DILocation(line: 170, column: 22, scope: !566)
!570 = !DILocation(line: 170, column: 26, scope: !571)
!571 = !DILexicalBlockFile(scope: !566, file: !1, discriminator: 1)
!572 = !DILocation(line: 170, column: 34, scope: !571)
!573 = !DILocation(line: 170, column: 9, scope: !571)
!574 = !DILocation(line: 171, column: 7, scope: !566)
!575 = !DILocation(line: 172, column: 3, scope: !567)
!576 = !DILocation(line: 167, column: 36, scope: !577)
!577 = !DILexicalBlockFile(scope: !561, file: !1, discriminator: 2)
!578 = !DILocation(line: 167, column: 46, scope: !577)
!579 = !DILocation(line: 167, column: 3, scope: !577)
!580 = !DILocation(line: 173, column: 8, scope: !581)
!581 = distinct !DILexicalBlock(scope: !296, file: !1, line: 173, column: 7)
!582 = !DILocation(line: 173, column: 16, scope: !581)
!583 = !DILocation(line: 173, column: 7, scope: !296)
!584 = !DILocation(line: 175, column: 24, scope: !585)
!585 = distinct !DILexicalBlock(scope: !581, file: !1, line: 174, column: 3)
!586 = !DILocation(line: 175, column: 27, scope: !585)
!587 = !DILocation(line: 175, column: 5, scope: !585)
!588 = !DILocation(line: 177, column: 5, scope: !585)
!589 = !DILocation(line: 181, column: 39, scope: !296)
!590 = !DILocation(line: 181, column: 9, scope: !296)
!591 = !DILocation(line: 181, column: 7, scope: !296)
!592 = !DILocation(line: 182, column: 7, scope: !593)
!593 = distinct !DILexicalBlock(scope: !296, file: !1, line: 182, column: 7)
!594 = !DILocation(line: 182, column: 14, scope: !593)
!595 = !DILocation(line: 182, column: 7, scope: !296)
!596 = !DILocation(line: 184, column: 24, scope: !597)
!597 = distinct !DILexicalBlock(scope: !593, file: !1, line: 183, column: 3)
!598 = !DILocation(line: 184, column: 27, scope: !597)
!599 = !DILocation(line: 184, column: 5, scope: !597)
!600 = !DILocation(line: 185, column: 5, scope: !597)
!601 = !DILocation(line: 187, column: 20, scope: !296)
!602 = !DILocation(line: 187, column: 3, scope: !296)
!603 = !DILocation(line: 187, column: 11, scope: !296)
!604 = !DILocation(line: 187, column: 18, scope: !296)
!605 = !DILocation(line: 188, column: 21, scope: !296)
!606 = !DILocation(line: 188, column: 3, scope: !296)
!607 = !DILocation(line: 188, column: 11, scope: !296)
!608 = !DILocation(line: 188, column: 19, scope: !296)
!609 = !DILocation(line: 189, column: 22, scope: !296)
!610 = !DILocation(line: 189, column: 25, scope: !296)
!611 = !DILocation(line: 189, column: 3, scope: !296)
!612 = !DILocation(line: 189, column: 11, scope: !296)
!613 = !DILocation(line: 189, column: 20, scope: !296)
!614 = !DILocation(line: 190, column: 15, scope: !296)
!615 = !DILocation(line: 190, column: 3, scope: !296)
!616 = !DILocation(line: 190, column: 6, scope: !296)
!617 = !DILocation(line: 190, column: 13, scope: !296)
!618 = !DILocation(line: 191, column: 8, scope: !296)
!619 = !DILocation(line: 191, column: 16, scope: !296)
!620 = !DILocation(line: 191, column: 22, scope: !296)
!621 = !DILocation(line: 191, column: 25, scope: !296)
!622 = !DILocation(line: 191, column: 7, scope: !296)
!623 = !DILocation(line: 191, column: 5, scope: !296)
!624 = !DILocation(line: 192, column: 7, scope: !625)
!625 = distinct !DILexicalBlock(scope: !296, file: !1, line: 192, column: 7)
!626 = !DILocation(line: 192, column: 9, scope: !625)
!627 = !DILocation(line: 192, column: 7, scope: !296)
!628 = !DILocation(line: 193, column: 33, scope: !629)
!629 = distinct !DILexicalBlock(scope: !625, file: !1, line: 192, column: 24)
!630 = !DILocation(line: 193, column: 5, scope: !629)
!631 = !DILocation(line: 194, column: 5, scope: !629)
!632 = !DILocation(line: 196, column: 18, scope: !296)
!633 = !DILocation(line: 196, column: 21, scope: !296)
!634 = !DILocation(line: 196, column: 29, scope: !296)
!635 = !DILocation(line: 196, column: 3, scope: !296)
!636 = !DILocation(line: 196, column: 11, scope: !296)
!637 = !DILocation(line: 196, column: 16, scope: !296)
!638 = !DILocation(line: 198, column: 3, scope: !296)
!639 = !DILocation(line: 198, column: 6, scope: !296)
!640 = !DILocation(line: 198, column: 28, scope: !296)
!641 = !DILocation(line: 199, column: 10, scope: !296)
!642 = !DILocation(line: 199, column: 3, scope: !296)
!643 = !DILocation(line: 200, column: 1, scope: !296)
