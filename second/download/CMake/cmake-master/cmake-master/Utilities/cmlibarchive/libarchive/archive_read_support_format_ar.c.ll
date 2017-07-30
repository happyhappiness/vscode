; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_ar.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_read = type { %struct.archive, %struct.archive_entry*, i32, i64, i64, %struct.archive_read_client, [16 x %struct.archive_read_filter_bidder], %struct.archive_read_filter*, i32, i64, i32, i32, [16 x %struct.archive_format_descriptor], %struct.archive_format_descriptor*, %struct.archive_read_extract*, i32 (%struct.archive_read*)*, %struct.anon }
%struct.archive_read_client = type { i32 (%struct.archive*, i8*)*, i64 (%struct.archive*, i8*, i8**)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i32)*, i32 (%struct.archive*, i8*)*, i32 (%struct.archive*, i8*, i8*)*, i32, i32, i64, %struct.archive_read_data_node* }
%struct.archive_read_data_node = type { i64, i64, i8* }
%struct.archive_read_filter_bidder = type { i8*, i8*, i32 (%struct.archive_read_filter_bidder*, %struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter_bidder*, i8*, i8*)*, i32 (%struct.archive_read_filter_bidder*)* }
%struct.archive_read_filter = type { i64, %struct.archive_read_filter_bidder*, %struct.archive_read_filter*, %struct.archive_read*, i32 (%struct.archive_read_filter*)*, i64 (%struct.archive_read_filter*, i8**)*, i64 (%struct.archive_read_filter*, i64)*, i64 (%struct.archive_read_filter*, i64, i32)*, i32 (%struct.archive_read_filter*)*, i32 (%struct.archive_read_filter*, i32)*, i8*, i8*, i32, i8*, i64, i8*, i64, i8*, i64, i8*, i64, i8, i8, i8 }
%struct.archive_format_descriptor = type { i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)* }
%struct.archive_read_extract = type { %struct.archive*, void (i8*)*, i8* }
%struct.anon = type { %struct.archive_read_passphrase*, %struct.archive_read_passphrase**, i32, i8* (%struct.archive*, i8*)*, i8* }
%struct.archive_read_passphrase = type { i8*, %struct.archive_read_passphrase* }
%struct.ar = type { i64, i64, i64, i64, i8*, i64, i8 }

@.str = private unnamed_addr constant [31 x i8] c"archive_read_support_format_ar\00", align 1
@.str.1 = private unnamed_addr constant [23 x i8] c"Can't allocate ar data\00", align 1
@.str.2 = private unnamed_addr constant [3 x i8] c"ar\00", align 1
@.str.3 = private unnamed_addr constant [9 x i8] c"!<arch>\0A\00", align 1
@.str.4 = private unnamed_addr constant [3 x i8] c"`\0A\00", align 1
@.str.5 = private unnamed_addr constant [32 x i8] c"Incorrect file header signature\00", align 1
@.str.6 = private unnamed_addr constant [4 x i8] c"#1/\00", align 1
@.str.7 = private unnamed_addr constant [10 x i8] c"__.SYMDEF\00", align 1
@.str.8 = private unnamed_addr constant [14 x i8] c"ar (GNU/SVR4)\00", align 1
@.str.9 = private unnamed_addr constant [9 x i8] c"ar (BSD)\00", align 1
@.str.10 = private unnamed_addr constant [32 x i8] c"Found entry with empty filename\00", align 1
@.str.11 = private unnamed_addr constant [3 x i8] c"//\00", align 1
@.str.12 = private unnamed_addr constant [25 x i8] c"Filename table too large\00", align 1
@.str.13 = private unnamed_addr constant [21 x i8] c"Invalid string table\00", align 1
@.str.14 = private unnamed_addr constant [34 x i8] c"More than one string tables exist\00", align 1
@.str.15 = private unnamed_addr constant [37 x i8] c"Can't allocate filename table buffer\00", align 1
@.str.16 = private unnamed_addr constant [52 x i8] c"Can't find long filename for GNU/SVR4 archive entry\00", align 1
@.str.17 = private unnamed_addr constant [20 x i8] c"Bad input file size\00", align 1
@.str.18 = private unnamed_addr constant [21 x i8] c"Truncated input file\00", align 1
@.str.19 = private unnamed_addr constant [28 x i8] c"Can't allocate fname buffer\00", align 1
@.str.20 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.21 = private unnamed_addr constant [21 x i8] c"Truncated ar archive\00", align 1
@.str.22 = private unnamed_addr constant [47 x i8] c"Truncated ar archive- failed consuming padding\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_format_ar(%struct.archive* %_a) #0 !dbg !312 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %ar = alloca %struct.ar*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !333, metadata !334), !dbg !335
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !336, metadata !334), !dbg !337
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !338
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !339
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !337
  call void @llvm.dbg.declare(metadata %struct.ar** %ar, metadata !340, metadata !334), !dbg !341
  call void @llvm.dbg.declare(metadata i32* %r, metadata !342, metadata !334), !dbg !343
  br label %do.body, !dbg !344

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !345, metadata !334), !dbg !347
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !348
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0)), !dbg !348
  store i32 %call, i32* %magic_test, align 4, !dbg !348
  %3 = load i32, i32* %magic_test, align 4, !dbg !348
  %cmp = icmp eq i32 %3, -30, !dbg !348
  br i1 %cmp, label %if.then, label %if.end, !dbg !348

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !350
  br label %return, !dbg !350

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !353

do.end:                                           ; preds = %if.end
  %call1 = call noalias i8* @calloc(i64 1, i64 56) #6, !dbg !355
  %4 = bitcast i8* %call1 to %struct.ar*, !dbg !356
  store %struct.ar* %4, %struct.ar** %ar, align 8, !dbg !357
  %5 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !358
  %cmp2 = icmp eq %struct.ar* %5, null, !dbg !360
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !361

if.then3:                                         ; preds = %do.end
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !362
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !364
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.1, i32 0, i32 0)), !dbg !365
  store i32 -30, i32* %retval, align 4, !dbg !366
  br label %return, !dbg !366

if.end4:                                          ; preds = %do.end
  %7 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !367
  %strtab = getelementptr inbounds %struct.ar, %struct.ar* %7, i32 0, i32 4, !dbg !368
  store i8* null, i8** %strtab, align 8, !dbg !369
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !370
  %9 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !371
  %10 = bitcast %struct.ar* %9 to i8*, !dbg !371
  %call5 = call i32 @__archive_read_register_format(%struct.archive_read* %8, i8* %10, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.2, i32 0, i32 0), i32 (%struct.archive_read*, i32)* @archive_read_format_ar_bid, i32 (%struct.archive_read*, i8*, i8*)* null, i32 (%struct.archive_read*, %struct.archive_entry*)* @archive_read_format_ar_read_header, i32 (%struct.archive_read*, i8**, i64*, i64*)* @archive_read_format_ar_read_data, i32 (%struct.archive_read*)* @archive_read_format_ar_skip, i64 (%struct.archive_read*, i64, i32)* null, i32 (%struct.archive_read*)* @archive_read_format_ar_cleanup, i32 (%struct.archive_read*)* null, i32 (%struct.archive_read*)* null), !dbg !372
  store i32 %call5, i32* %r, align 4, !dbg !373
  %11 = load i32, i32* %r, align 4, !dbg !374
  %cmp6 = icmp ne i32 %11, 0, !dbg !376
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !377

if.then7:                                         ; preds = %if.end4
  %12 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !378
  %13 = bitcast %struct.ar* %12 to i8*, !dbg !378
  call void @free(i8* %13) #6, !dbg !380
  %14 = load i32, i32* %r, align 4, !dbg !381
  store i32 %14, i32* %retval, align 4, !dbg !382
  br label %return, !dbg !382

if.end8:                                          ; preds = %if.end4
  store i32 0, i32* %retval, align 4, !dbg !383
  br label %return, !dbg !383

return:                                           ; preds = %if.end8, %if.then7, %if.then3, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !384
  ret i32 %15, !dbg !384
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare i32 @__archive_read_register_format(%struct.archive_read*, i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_ar_bid(%struct.archive_read* %a, i32 %best_bid) #0 !dbg !314 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %best_bid.addr = alloca i32, align 4
  %h = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !385, metadata !334), !dbg !386
  store i32 %best_bid, i32* %best_bid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %best_bid.addr, metadata !387, metadata !334), !dbg !388
  call void @llvm.dbg.declare(metadata i8** %h, metadata !389, metadata !334), !dbg !390
  %0 = load i32, i32* %best_bid.addr, align 4, !dbg !391
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !392
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %1, i64 8, i64* null), !dbg !394
  store i8* %call, i8** %h, align 8, !dbg !395
  %cmp = icmp eq i8* %call, null, !dbg !396
  br i1 %cmp, label %if.then, label %if.end, !dbg !397

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !398
  br label %return, !dbg !398

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %h, align 8, !dbg !399
  %call1 = call i32 @memcmp(i8* %2, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.3, i32 0, i32 0), i64 8) #7, !dbg !401
  %cmp2 = icmp eq i32 %call1, 0, !dbg !402
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !403

if.then3:                                         ; preds = %if.end
  store i32 64, i32* %retval, align 4, !dbg !404
  br label %return, !dbg !404

if.end4:                                          ; preds = %if.end
  store i32 -1, i32* %retval, align 4, !dbg !406
  br label %return, !dbg !406

return:                                           ; preds = %if.end4, %if.then3, %if.then
  %3 = load i32, i32* %retval, align 4, !dbg !407
  ret i32 %3, !dbg !407
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_ar_read_header(%struct.archive_read* %a, %struct.archive_entry* %entry1) #0 !dbg !315 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %ar = alloca %struct.ar*, align 8
  %unconsumed = alloca i64, align 8
  %header_data = alloca i8*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !408, metadata !334), !dbg !409
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !410, metadata !334), !dbg !411
  call void @llvm.dbg.declare(metadata %struct.ar** %ar, metadata !412, metadata !334), !dbg !413
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !414
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !415
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !415
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !416
  %2 = load i8*, i8** %data, align 8, !dbg !416
  %3 = bitcast i8* %2 to %struct.ar*, !dbg !417
  store %struct.ar* %3, %struct.ar** %ar, align 8, !dbg !413
  call void @llvm.dbg.declare(metadata i64* %unconsumed, metadata !418, metadata !334), !dbg !419
  call void @llvm.dbg.declare(metadata i8** %header_data, metadata !420, metadata !334), !dbg !421
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !422, metadata !334), !dbg !423
  %4 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !424
  %read_global_header = getelementptr inbounds %struct.ar, %struct.ar* %4, i32 0, i32 6, !dbg !426
  %5 = load i8, i8* %read_global_header, align 8, !dbg !426
  %tobool = icmp ne i8 %5, 0, !dbg !424
  br i1 %tobool, label %if.end, label %if.then, !dbg !427

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !428
  %call = call i64 @__archive_read_consume(%struct.archive_read* %6, i64 8), !dbg !430
  %7 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !431
  %read_global_header2 = getelementptr inbounds %struct.ar, %struct.ar* %7, i32 0, i32 6, !dbg !432
  store i8 1, i8* %read_global_header2, align 8, !dbg !433
  %8 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !434
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 0, !dbg !435
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !436
  store i32 458752, i32* %archive_format, align 8, !dbg !437
  br label %if.end, !dbg !438

if.end:                                           ; preds = %if.then, %entry
  %9 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !439
  %call3 = call i8* @__archive_read_ahead(%struct.archive_read* %9, i64 60, i64* null), !dbg !441
  store i8* %call3, i8** %header_data, align 8, !dbg !442
  %cmp = icmp eq i8* %call3, null, !dbg !443
  br i1 %cmp, label %if.then4, label %if.end5, !dbg !444

if.then4:                                         ; preds = %if.end
  store i32 1, i32* %retval, align 4, !dbg !445
  br label %return, !dbg !445

if.end5:                                          ; preds = %if.end
  store i64 60, i64* %unconsumed, align 8, !dbg !446
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !447
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !448
  %12 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !449
  %13 = load i8*, i8** %header_data, align 8, !dbg !450
  %call6 = call i32 @_ar_read_header(%struct.archive_read* %10, %struct.archive_entry* %11, %struct.ar* %12, i8* %13, i64* %unconsumed), !dbg !451
  store i32 %call6, i32* %ret, align 4, !dbg !452
  %14 = load i64, i64* %unconsumed, align 8, !dbg !453
  %tobool7 = icmp ne i64 %14, 0, !dbg !453
  br i1 %tobool7, label %if.then8, label %if.end10, !dbg !455

if.then8:                                         ; preds = %if.end5
  %15 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !456
  %16 = load i64, i64* %unconsumed, align 8, !dbg !457
  %call9 = call i64 @__archive_read_consume(%struct.archive_read* %15, i64 %16), !dbg !458
  br label %if.end10, !dbg !458

if.end10:                                         ; preds = %if.then8, %if.end5
  %17 = load i32, i32* %ret, align 4, !dbg !459
  store i32 %17, i32* %retval, align 4, !dbg !460
  br label %return, !dbg !460

return:                                           ; preds = %if.end10, %if.then4
  %18 = load i32, i32* %retval, align 4, !dbg !461
  ret i32 %18, !dbg !461
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_ar_read_data(%struct.archive_read* %a, i8** %buff, i64* %size, i64* %offset) #0 !dbg !328 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %buff.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  %offset.addr = alloca i64*, align 8
  %bytes_read = alloca i64, align 8
  %ar = alloca %struct.ar*, align 8
  %skipped = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !462, metadata !334), !dbg !463
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !464, metadata !334), !dbg !465
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !466, metadata !334), !dbg !467
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !468, metadata !334), !dbg !469
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !470, metadata !334), !dbg !471
  call void @llvm.dbg.declare(metadata %struct.ar** %ar, metadata !472, metadata !334), !dbg !473
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !474
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !475
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !475
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !476
  %2 = load i8*, i8** %data, align 8, !dbg !476
  %3 = bitcast i8* %2 to %struct.ar*, !dbg !477
  store %struct.ar* %3, %struct.ar** %ar, align 8, !dbg !478
  %4 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !479
  %entry_bytes_unconsumed = getelementptr inbounds %struct.ar, %struct.ar* %4, i32 0, i32 1, !dbg !481
  %5 = load i64, i64* %entry_bytes_unconsumed, align 8, !dbg !481
  %tobool = icmp ne i64 %5, 0, !dbg !479
  br i1 %tobool, label %if.then, label %if.end, !dbg !482

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !483
  %7 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !485
  %entry_bytes_unconsumed1 = getelementptr inbounds %struct.ar, %struct.ar* %7, i32 0, i32 1, !dbg !486
  %8 = load i64, i64* %entry_bytes_unconsumed1, align 8, !dbg !486
  %call = call i64 @__archive_read_consume(%struct.archive_read* %6, i64 %8), !dbg !487
  %9 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !488
  %entry_bytes_unconsumed2 = getelementptr inbounds %struct.ar, %struct.ar* %9, i32 0, i32 1, !dbg !489
  store i64 0, i64* %entry_bytes_unconsumed2, align 8, !dbg !490
  br label %if.end, !dbg !491

if.end:                                           ; preds = %if.then, %entry
  %10 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !492
  %entry_bytes_remaining = getelementptr inbounds %struct.ar, %struct.ar* %10, i32 0, i32 0, !dbg !494
  %11 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !494
  %cmp = icmp sgt i64 %11, 0, !dbg !495
  br i1 %cmp, label %if.then3, label %if.else, !dbg !496

if.then3:                                         ; preds = %if.end
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !497
  %call4 = call i8* @__archive_read_ahead(%struct.archive_read* %12, i64 1, i64* %bytes_read), !dbg !499
  %13 = load i8**, i8*** %buff.addr, align 8, !dbg !500
  store i8* %call4, i8** %13, align 8, !dbg !501
  %14 = load i64, i64* %bytes_read, align 8, !dbg !502
  %cmp5 = icmp eq i64 %14, 0, !dbg !504
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !505

if.then6:                                         ; preds = %if.then3
  %15 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !506
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %15, i32 0, i32 0, !dbg !508
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.21, i32 0, i32 0)), !dbg !509
  store i32 -30, i32* %retval, align 4, !dbg !510
  br label %return, !dbg !510

if.end7:                                          ; preds = %if.then3
  %16 = load i64, i64* %bytes_read, align 8, !dbg !511
  %cmp8 = icmp slt i64 %16, 0, !dbg !513
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !514

if.then9:                                         ; preds = %if.end7
  store i32 -30, i32* %retval, align 4, !dbg !515
  br label %return, !dbg !515

if.end10:                                         ; preds = %if.end7
  %17 = load i64, i64* %bytes_read, align 8, !dbg !516
  %18 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !518
  %entry_bytes_remaining11 = getelementptr inbounds %struct.ar, %struct.ar* %18, i32 0, i32 0, !dbg !519
  %19 = load i64, i64* %entry_bytes_remaining11, align 8, !dbg !519
  %cmp12 = icmp sgt i64 %17, %19, !dbg !520
  br i1 %cmp12, label %if.then13, label %if.end15, !dbg !521

if.then13:                                        ; preds = %if.end10
  %20 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !522
  %entry_bytes_remaining14 = getelementptr inbounds %struct.ar, %struct.ar* %20, i32 0, i32 0, !dbg !523
  %21 = load i64, i64* %entry_bytes_remaining14, align 8, !dbg !523
  store i64 %21, i64* %bytes_read, align 8, !dbg !524
  br label %if.end15, !dbg !525

if.end15:                                         ; preds = %if.then13, %if.end10
  %22 = load i64, i64* %bytes_read, align 8, !dbg !526
  %23 = load i64*, i64** %size.addr, align 8, !dbg !527
  store i64 %22, i64* %23, align 8, !dbg !528
  %24 = load i64, i64* %bytes_read, align 8, !dbg !529
  %25 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !530
  %entry_bytes_unconsumed16 = getelementptr inbounds %struct.ar, %struct.ar* %25, i32 0, i32 1, !dbg !531
  store i64 %24, i64* %entry_bytes_unconsumed16, align 8, !dbg !532
  %26 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !533
  %entry_offset = getelementptr inbounds %struct.ar, %struct.ar* %26, i32 0, i32 2, !dbg !534
  %27 = load i64, i64* %entry_offset, align 8, !dbg !534
  %28 = load i64*, i64** %offset.addr, align 8, !dbg !535
  store i64 %27, i64* %28, align 8, !dbg !536
  %29 = load i64, i64* %bytes_read, align 8, !dbg !537
  %30 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !538
  %entry_offset17 = getelementptr inbounds %struct.ar, %struct.ar* %30, i32 0, i32 2, !dbg !539
  %31 = load i64, i64* %entry_offset17, align 8, !dbg !540
  %add = add nsw i64 %31, %29, !dbg !540
  store i64 %add, i64* %entry_offset17, align 8, !dbg !540
  %32 = load i64, i64* %bytes_read, align 8, !dbg !541
  %33 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !542
  %entry_bytes_remaining18 = getelementptr inbounds %struct.ar, %struct.ar* %33, i32 0, i32 0, !dbg !543
  %34 = load i64, i64* %entry_bytes_remaining18, align 8, !dbg !544
  %sub = sub nsw i64 %34, %32, !dbg !544
  store i64 %sub, i64* %entry_bytes_remaining18, align 8, !dbg !544
  store i32 0, i32* %retval, align 4, !dbg !545
  br label %return, !dbg !545

if.else:                                          ; preds = %if.end
  call void @llvm.dbg.declare(metadata i64* %skipped, metadata !546, metadata !334), !dbg !548
  %35 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !549
  %36 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !550
  %entry_padding = getelementptr inbounds %struct.ar, %struct.ar* %36, i32 0, i32 3, !dbg !551
  %37 = load i64, i64* %entry_padding, align 8, !dbg !551
  %call19 = call i64 @__archive_read_consume(%struct.archive_read* %35, i64 %37), !dbg !552
  store i64 %call19, i64* %skipped, align 8, !dbg !548
  %38 = load i64, i64* %skipped, align 8, !dbg !553
  %cmp20 = icmp sge i64 %38, 0, !dbg !555
  br i1 %cmp20, label %if.then21, label %if.end24, !dbg !556

if.then21:                                        ; preds = %if.else
  %39 = load i64, i64* %skipped, align 8, !dbg !557
  %40 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !559
  %entry_padding22 = getelementptr inbounds %struct.ar, %struct.ar* %40, i32 0, i32 3, !dbg !560
  %41 = load i64, i64* %entry_padding22, align 8, !dbg !561
  %sub23 = sub nsw i64 %41, %39, !dbg !561
  store i64 %sub23, i64* %entry_padding22, align 8, !dbg !561
  br label %if.end24, !dbg !562

if.end24:                                         ; preds = %if.then21, %if.else
  %42 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !563
  %entry_padding25 = getelementptr inbounds %struct.ar, %struct.ar* %42, i32 0, i32 3, !dbg !565
  %43 = load i64, i64* %entry_padding25, align 8, !dbg !565
  %tobool26 = icmp ne i64 %43, 0, !dbg !563
  br i1 %tobool26, label %if.then27, label %if.end32, !dbg !566

if.then27:                                        ; preds = %if.end24
  %44 = load i64, i64* %skipped, align 8, !dbg !567
  %cmp28 = icmp sge i64 %44, 0, !dbg !570
  br i1 %cmp28, label %if.then29, label %if.end31, !dbg !571

if.then29:                                        ; preds = %if.then27
  %45 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !572
  %archive30 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %45, i32 0, i32 0, !dbg !574
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive30, i32 -1, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.22, i32 0, i32 0)), !dbg !575
  br label %if.end31, !dbg !576

if.end31:                                         ; preds = %if.then29, %if.then27
  store i32 -30, i32* %retval, align 4, !dbg !577
  br label %return, !dbg !577

if.end32:                                         ; preds = %if.end24
  %46 = load i8**, i8*** %buff.addr, align 8, !dbg !578
  store i8* null, i8** %46, align 8, !dbg !579
  %47 = load i64*, i64** %size.addr, align 8, !dbg !580
  store i64 0, i64* %47, align 8, !dbg !581
  %48 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !582
  %entry_offset33 = getelementptr inbounds %struct.ar, %struct.ar* %48, i32 0, i32 2, !dbg !583
  %49 = load i64, i64* %entry_offset33, align 8, !dbg !583
  %50 = load i64*, i64** %offset.addr, align 8, !dbg !584
  store i64 %49, i64* %50, align 8, !dbg !585
  store i32 1, i32* %retval, align 4, !dbg !586
  br label %return, !dbg !586

return:                                           ; preds = %if.end32, %if.end31, %if.end15, %if.then9, %if.then6
  %51 = load i32, i32* %retval, align 4, !dbg !587
  ret i32 %51, !dbg !587
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_ar_skip(%struct.archive_read* %a) #0 !dbg !329 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %bytes_skipped = alloca i64, align 8
  %ar = alloca %struct.ar*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !588, metadata !334), !dbg !589
  call void @llvm.dbg.declare(metadata i64* %bytes_skipped, metadata !590, metadata !334), !dbg !591
  call void @llvm.dbg.declare(metadata %struct.ar** %ar, metadata !592, metadata !334), !dbg !593
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !594
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !595
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !595
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !596
  %2 = load i8*, i8** %data, align 8, !dbg !596
  %3 = bitcast i8* %2 to %struct.ar*, !dbg !597
  store %struct.ar* %3, %struct.ar** %ar, align 8, !dbg !598
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !599
  %5 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !600
  %entry_bytes_remaining = getelementptr inbounds %struct.ar, %struct.ar* %5, i32 0, i32 0, !dbg !601
  %6 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !601
  %7 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !602
  %entry_padding = getelementptr inbounds %struct.ar, %struct.ar* %7, i32 0, i32 3, !dbg !603
  %8 = load i64, i64* %entry_padding, align 8, !dbg !603
  %add = add nsw i64 %6, %8, !dbg !604
  %9 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !605
  %entry_bytes_unconsumed = getelementptr inbounds %struct.ar, %struct.ar* %9, i32 0, i32 1, !dbg !606
  %10 = load i64, i64* %entry_bytes_unconsumed, align 8, !dbg !606
  %add1 = add i64 %add, %10, !dbg !607
  %call = call i64 @__archive_read_consume(%struct.archive_read* %4, i64 %add1), !dbg !608
  store i64 %call, i64* %bytes_skipped, align 8, !dbg !609
  %11 = load i64, i64* %bytes_skipped, align 8, !dbg !610
  %cmp = icmp slt i64 %11, 0, !dbg !612
  br i1 %cmp, label %if.then, label %if.end, !dbg !613

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !614
  br label %return, !dbg !614

if.end:                                           ; preds = %entry
  %12 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !615
  %entry_bytes_remaining2 = getelementptr inbounds %struct.ar, %struct.ar* %12, i32 0, i32 0, !dbg !616
  store i64 0, i64* %entry_bytes_remaining2, align 8, !dbg !617
  %13 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !618
  %entry_bytes_unconsumed3 = getelementptr inbounds %struct.ar, %struct.ar* %13, i32 0, i32 1, !dbg !619
  store i64 0, i64* %entry_bytes_unconsumed3, align 8, !dbg !620
  %14 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !621
  %entry_padding4 = getelementptr inbounds %struct.ar, %struct.ar* %14, i32 0, i32 3, !dbg !622
  store i64 0, i64* %entry_padding4, align 8, !dbg !623
  store i32 0, i32* %retval, align 4, !dbg !624
  br label %return, !dbg !624

return:                                           ; preds = %if.end, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !625
  ret i32 %15, !dbg !625
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_ar_cleanup(%struct.archive_read* %a) #0 !dbg !313 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %ar = alloca %struct.ar*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !626, metadata !334), !dbg !627
  call void @llvm.dbg.declare(metadata %struct.ar** %ar, metadata !628, metadata !334), !dbg !629
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !630
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !631
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !631
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !632
  %2 = load i8*, i8** %data, align 8, !dbg !632
  %3 = bitcast i8* %2 to %struct.ar*, !dbg !633
  store %struct.ar* %3, %struct.ar** %ar, align 8, !dbg !634
  %4 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !635
  %strtab = getelementptr inbounds %struct.ar, %struct.ar* %4, i32 0, i32 4, !dbg !637
  %5 = load i8*, i8** %strtab, align 8, !dbg !637
  %tobool = icmp ne i8* %5, null, !dbg !635
  br i1 %tobool, label %if.then, label %if.end, !dbg !638

if.then:                                          ; preds = %entry
  %6 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !639
  %strtab1 = getelementptr inbounds %struct.ar, %struct.ar* %6, i32 0, i32 4, !dbg !640
  %7 = load i8*, i8** %strtab1, align 8, !dbg !640
  call void @free(i8* %7) #6, !dbg !641
  br label %if.end, !dbg !641

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !642
  %9 = bitcast %struct.ar* %8 to i8*, !dbg !642
  call void @free(i8* %9) #6, !dbg !643
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !644
  %format2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 13, !dbg !645
  %11 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format2, align 8, !dbg !645
  %data3 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %11, i32 0, i32 0, !dbg !646
  store i8* null, i8** %data3, align 8, !dbg !647
  ret i32 0, !dbg !648
}

; Function Attrs: nounwind
declare void @free(i8*) #3

declare i8* @__archive_read_ahead(%struct.archive_read*, i64, i64*) #2

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #4

declare i64 @__archive_read_consume(%struct.archive_read*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @_ar_read_header(%struct.archive_read* %a, %struct.archive_entry* %entry1, %struct.ar* %ar, i8* %h, i64* %unconsumed) #0 !dbg !316 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %ar.addr = alloca %struct.ar*, align 8
  %h.addr = alloca i8*, align 8
  %unconsumed.addr = alloca i64*, align 8
  %filename = alloca [17 x i8], align 16
  %number = alloca i64, align 8
  %bsd_name_length = alloca i64, align 8
  %entry_size = alloca i64, align 8
  %p = alloca i8*, align 8
  %st = alloca i8*, align 8
  %b = alloca i8*, align 8
  %r = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !649, metadata !334), !dbg !650
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !651, metadata !334), !dbg !652
  store %struct.ar* %ar, %struct.ar** %ar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.ar** %ar.addr, metadata !653, metadata !334), !dbg !654
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !655, metadata !334), !dbg !656
  store i64* %unconsumed, i64** %unconsumed.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %unconsumed.addr, metadata !657, metadata !334), !dbg !658
  call void @llvm.dbg.declare(metadata [17 x i8]* %filename, metadata !659, metadata !334), !dbg !663
  call void @llvm.dbg.declare(metadata i64* %number, metadata !664, metadata !334), !dbg !665
  call void @llvm.dbg.declare(metadata i64* %bsd_name_length, metadata !666, metadata !334), !dbg !667
  call void @llvm.dbg.declare(metadata i64* %entry_size, metadata !668, metadata !334), !dbg !669
  call void @llvm.dbg.declare(metadata i8** %p, metadata !670, metadata !334), !dbg !671
  call void @llvm.dbg.declare(metadata i8** %st, metadata !672, metadata !334), !dbg !673
  call void @llvm.dbg.declare(metadata i8** %b, metadata !674, metadata !334), !dbg !675
  call void @llvm.dbg.declare(metadata i32* %r, metadata !676, metadata !334), !dbg !677
  %0 = load i8*, i8** %h.addr, align 8, !dbg !678
  %add.ptr = getelementptr inbounds i8, i8* %0, i64 58, !dbg !680
  %call = call i32 @strncmp(i8* %add.ptr, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.4, i32 0, i32 0), i64 2) #7, !dbg !681
  %cmp = icmp ne i32 %call, 0, !dbg !682
  br i1 %cmp, label %if.then, label %if.end, !dbg !683

if.then:                                          ; preds = %entry
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !684
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 0, !dbg !686
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.5, i32 0, i32 0)), !dbg !687
  store i32 -30, i32* %retval, align 4, !dbg !688
  br label %return, !dbg !688

if.end:                                           ; preds = %entry
  %arraydecay = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !689
  %2 = load i8*, i8** %h.addr, align 8, !dbg !690
  %add.ptr2 = getelementptr inbounds i8, i8* %2, i64 0, !dbg !691
  %call3 = call i8* @strncpy(i8* %arraydecay, i8* %add.ptr2, i64 16) #6, !dbg !692
  %arrayidx = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i64 0, i64 16, !dbg !693
  store i8 0, i8* %arrayidx, align 16, !dbg !694
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !695
  %archive4 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %3, i32 0, i32 0, !dbg !697
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive4, i32 0, i32 3, !dbg !698
  %4 = load i32, i32* %archive_format, align 8, !dbg !698
  %cmp5 = icmp eq i32 %4, 458752, !dbg !699
  br i1 %cmp5, label %if.then6, label %if.end29, !dbg !700

if.then6:                                         ; preds = %if.end
  %arraydecay7 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !701
  %call8 = call i32 @strncmp(i8* %arraydecay7, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0), i64 3) #7, !dbg !704
  %cmp9 = icmp eq i32 %call8, 0, !dbg !705
  br i1 %cmp9, label %if.then10, label %if.else, !dbg !706

if.then10:                                        ; preds = %if.then6
  %5 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !707
  %archive11 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 0, !dbg !708
  %archive_format12 = getelementptr inbounds %struct.archive, %struct.archive* %archive11, i32 0, i32 3, !dbg !709
  store i32 458754, i32* %archive_format12, align 8, !dbg !710
  br label %if.end28, !dbg !707

if.else:                                          ; preds = %if.then6
  %arraydecay13 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !711
  %call14 = call i8* @strchr(i8* %arraydecay13, i32 47) #7, !dbg !713
  %cmp15 = icmp ne i8* %call14, null, !dbg !714
  br i1 %cmp15, label %if.then16, label %if.else19, !dbg !715

if.then16:                                        ; preds = %if.else
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !716
  %archive17 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !717
  %archive_format18 = getelementptr inbounds %struct.archive, %struct.archive* %archive17, i32 0, i32 3, !dbg !718
  store i32 458753, i32* %archive_format18, align 8, !dbg !719
  br label %if.end27, !dbg !716

if.else19:                                        ; preds = %if.else
  %arraydecay20 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !720
  %call21 = call i32 @strncmp(i8* %arraydecay20, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.7, i32 0, i32 0), i64 9) #7, !dbg !722
  %cmp22 = icmp eq i32 %call21, 0, !dbg !723
  br i1 %cmp22, label %if.then23, label %if.end26, !dbg !724

if.then23:                                        ; preds = %if.else19
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !725
  %archive24 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !726
  %archive_format25 = getelementptr inbounds %struct.archive, %struct.archive* %archive24, i32 0, i32 3, !dbg !727
  store i32 458754, i32* %archive_format25, align 8, !dbg !728
  br label %if.end26, !dbg !725

if.end26:                                         ; preds = %if.then23, %if.else19
  br label %if.end27

if.end27:                                         ; preds = %if.end26, %if.then16
  br label %if.end28

if.end28:                                         ; preds = %if.end27, %if.then10
  br label %if.end29, !dbg !729

if.end29:                                         ; preds = %if.end28, %if.end
  %8 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !730
  %archive30 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 0, !dbg !732
  %archive_format31 = getelementptr inbounds %struct.archive, %struct.archive* %archive30, i32 0, i32 3, !dbg !733
  %9 = load i32, i32* %archive_format31, align 8, !dbg !733
  %cmp32 = icmp eq i32 %9, 458753, !dbg !734
  br i1 %cmp32, label %if.then33, label %if.else35, !dbg !735

if.then33:                                        ; preds = %if.end29
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !736
  %archive34 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 0, !dbg !737
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive34, i32 0, i32 4, !dbg !738
  store i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.8, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !739
  br label %if.end46, !dbg !736

if.else35:                                        ; preds = %if.end29
  %11 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !740
  %archive36 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 0, !dbg !742
  %archive_format37 = getelementptr inbounds %struct.archive, %struct.archive* %archive36, i32 0, i32 3, !dbg !743
  %12 = load i32, i32* %archive_format37, align 8, !dbg !743
  %cmp38 = icmp eq i32 %12, 458754, !dbg !744
  br i1 %cmp38, label %if.then39, label %if.else42, !dbg !745

if.then39:                                        ; preds = %if.else35
  %13 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !746
  %archive40 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %13, i32 0, i32 0, !dbg !747
  %archive_format_name41 = getelementptr inbounds %struct.archive, %struct.archive* %archive40, i32 0, i32 4, !dbg !748
  store i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.9, i32 0, i32 0), i8** %archive_format_name41, align 8, !dbg !749
  br label %if.end45, !dbg !746

if.else42:                                        ; preds = %if.else35
  %14 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !750
  %archive43 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %14, i32 0, i32 0, !dbg !751
  %archive_format_name44 = getelementptr inbounds %struct.archive, %struct.archive* %archive43, i32 0, i32 4, !dbg !752
  store i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.2, i32 0, i32 0), i8** %archive_format_name44, align 8, !dbg !753
  br label %if.end45

if.end45:                                         ; preds = %if.else42, %if.then39
  br label %if.end46

if.end46:                                         ; preds = %if.end45, %if.then33
  %arraydecay47 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !754
  %add.ptr48 = getelementptr inbounds i8, i8* %arraydecay47, i64 16, !dbg !755
  %add.ptr49 = getelementptr inbounds i8, i8* %add.ptr48, i64 -1, !dbg !756
  store i8* %add.ptr49, i8** %p, align 8, !dbg !757
  br label %while.cond, !dbg !758

while.cond:                                       ; preds = %while.body, %if.end46
  %15 = load i8*, i8** %p, align 8, !dbg !759
  %arraydecay50 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !761
  %cmp51 = icmp uge i8* %15, %arraydecay50, !dbg !762
  br i1 %cmp51, label %land.rhs, label %land.end, !dbg !763

land.rhs:                                         ; preds = %while.cond
  %16 = load i8*, i8** %p, align 8, !dbg !764
  %17 = load i8, i8* %16, align 1, !dbg !766
  %conv = sext i8 %17 to i32, !dbg !766
  %cmp52 = icmp eq i32 %conv, 32, !dbg !767
  br label %land.end

land.end:                                         ; preds = %land.rhs, %while.cond
  %18 = phi i1 [ false, %while.cond ], [ %cmp52, %land.rhs ]
  br i1 %18, label %while.body, label %while.end, !dbg !768

while.body:                                       ; preds = %land.end
  %19 = load i8*, i8** %p, align 8, !dbg !770
  store i8 0, i8* %19, align 1, !dbg !772
  %20 = load i8*, i8** %p, align 8, !dbg !773
  %incdec.ptr = getelementptr inbounds i8, i8* %20, i32 -1, !dbg !773
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !773
  br label %while.cond, !dbg !774

while.end:                                        ; preds = %land.end
  %arrayidx54 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i64 0, i64 0, !dbg !776
  %21 = load i8, i8* %arrayidx54, align 16, !dbg !776
  %conv55 = sext i8 %21 to i32, !dbg !776
  %cmp56 = icmp ne i32 %conv55, 47, !dbg !778
  br i1 %cmp56, label %land.lhs.true, label %if.end66, !dbg !779

land.lhs.true:                                    ; preds = %while.end
  %22 = load i8*, i8** %p, align 8, !dbg !780
  %arraydecay58 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !782
  %cmp59 = icmp ugt i8* %22, %arraydecay58, !dbg !783
  br i1 %cmp59, label %land.lhs.true61, label %if.end66, !dbg !784

land.lhs.true61:                                  ; preds = %land.lhs.true
  %23 = load i8*, i8** %p, align 8, !dbg !785
  %24 = load i8, i8* %23, align 1, !dbg !787
  %conv62 = sext i8 %24 to i32, !dbg !787
  %cmp63 = icmp eq i32 %conv62, 47, !dbg !788
  br i1 %cmp63, label %if.then65, label %if.end66, !dbg !789

if.then65:                                        ; preds = %land.lhs.true61
  %25 = load i8*, i8** %p, align 8, !dbg !790
  store i8 0, i8* %25, align 1, !dbg !792
  br label %if.end66, !dbg !793

if.end66:                                         ; preds = %if.then65, %land.lhs.true61, %land.lhs.true, %while.end
  %26 = load i8*, i8** %p, align 8, !dbg !794
  %arraydecay67 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !796
  %cmp68 = icmp ult i8* %26, %arraydecay67, !dbg !797
  br i1 %cmp68, label %if.then70, label %if.end72, !dbg !798

if.then70:                                        ; preds = %if.end66
  %27 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !799
  %archive71 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %27, i32 0, i32 0, !dbg !801
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive71, i32 -1, i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.10, i32 0, i32 0)), !dbg !802
  store i32 -30, i32* %retval, align 4, !dbg !803
  br label %return, !dbg !803

if.end72:                                         ; preds = %if.end66
  %arraydecay73 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !804
  %call74 = call i32 @strcmp(i8* %arraydecay73, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.11, i32 0, i32 0)) #7, !dbg !806
  %cmp75 = icmp eq i32 %call74, 0, !dbg !807
  br i1 %cmp75, label %if.then77, label %if.end117, !dbg !808

if.then77:                                        ; preds = %if.end72
  %28 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !809
  %29 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !811
  %30 = load i8*, i8** %h.addr, align 8, !dbg !812
  %call78 = call i32 @ar_parse_common_header(%struct.ar* %28, %struct.archive_entry* %29, i8* %30), !dbg !813
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !814
  %arraydecay79 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !815
  call void @archive_entry_copy_pathname(%struct.archive_entry* %31, i8* %arraydecay79), !dbg !816
  %32 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !817
  call void @archive_entry_set_filetype(%struct.archive_entry* %32, i32 32768), !dbg !818
  %33 = load i8*, i8** %h.addr, align 8, !dbg !819
  %add.ptr80 = getelementptr inbounds i8, i8* %33, i64 48, !dbg !820
  %call81 = call i64 @ar_atol10(i8* %add.ptr80, i32 10), !dbg !821
  store i64 %call81, i64* %number, align 8, !dbg !822
  %34 = load i64, i64* %number, align 8, !dbg !823
  %cmp82 = icmp ugt i64 %34, -1, !dbg !825
  br i1 %cmp82, label %if.then86, label %lor.lhs.false, !dbg !826

lor.lhs.false:                                    ; preds = %if.then77
  %35 = load i64, i64* %number, align 8, !dbg !827
  %cmp84 = icmp ugt i64 %35, 1073741824, !dbg !829
  br i1 %cmp84, label %if.then86, label %if.end88, !dbg !830

if.then86:                                        ; preds = %lor.lhs.false, %if.then77
  %36 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !831
  %archive87 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %36, i32 0, i32 0, !dbg !833
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive87, i32 -1, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.12, i32 0, i32 0)), !dbg !834
  store i32 -30, i32* %retval, align 4, !dbg !835
  br label %return, !dbg !835

if.end88:                                         ; preds = %lor.lhs.false
  %37 = load i64, i64* %number, align 8, !dbg !836
  store i64 %37, i64* %entry_size, align 8, !dbg !837
  %38 = load i64, i64* %entry_size, align 8, !dbg !838
  %cmp89 = icmp eq i64 %38, 0, !dbg !840
  br i1 %cmp89, label %if.then91, label %if.end93, !dbg !841

if.then91:                                        ; preds = %if.end88
  %39 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !842
  %archive92 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %39, i32 0, i32 0, !dbg !844
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive92, i32 22, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.13, i32 0, i32 0)), !dbg !845
  store i32 -30, i32* %retval, align 4, !dbg !846
  br label %return, !dbg !846

if.end93:                                         ; preds = %if.end88
  %40 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !847
  %strtab = getelementptr inbounds %struct.ar, %struct.ar* %40, i32 0, i32 4, !dbg !849
  %41 = load i8*, i8** %strtab, align 8, !dbg !849
  %cmp94 = icmp ne i8* %41, null, !dbg !850
  br i1 %cmp94, label %if.then96, label %if.end98, !dbg !851

if.then96:                                        ; preds = %if.end93
  %42 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !852
  %archive97 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %42, i32 0, i32 0, !dbg !854
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive97, i32 22, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.14, i32 0, i32 0)), !dbg !855
  store i32 -30, i32* %retval, align 4, !dbg !856
  br label %return, !dbg !856

if.end98:                                         ; preds = %if.end93
  %43 = load i64, i64* %entry_size, align 8, !dbg !857
  %call99 = call noalias i8* @malloc(i64 %43) #6, !dbg !858
  store i8* %call99, i8** %st, align 8, !dbg !859
  %44 = load i8*, i8** %st, align 8, !dbg !860
  %cmp100 = icmp eq i8* %44, null, !dbg !862
  br i1 %cmp100, label %if.then102, label %if.end104, !dbg !863

if.then102:                                       ; preds = %if.end98
  %45 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !864
  %archive103 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %45, i32 0, i32 0, !dbg !866
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive103, i32 12, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.15, i32 0, i32 0)), !dbg !867
  store i32 -30, i32* %retval, align 4, !dbg !868
  br label %return, !dbg !868

if.end104:                                        ; preds = %if.end98
  %46 = load i8*, i8** %st, align 8, !dbg !869
  %47 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !870
  %strtab105 = getelementptr inbounds %struct.ar, %struct.ar* %47, i32 0, i32 4, !dbg !871
  store i8* %46, i8** %strtab105, align 8, !dbg !872
  %48 = load i64, i64* %entry_size, align 8, !dbg !873
  %49 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !874
  %strtab_size = getelementptr inbounds %struct.ar, %struct.ar* %49, i32 0, i32 5, !dbg !875
  store i64 %48, i64* %strtab_size, align 8, !dbg !876
  %50 = load i64*, i64** %unconsumed.addr, align 8, !dbg !877
  %51 = load i64, i64* %50, align 8, !dbg !879
  %tobool = icmp ne i64 %51, 0, !dbg !879
  br i1 %tobool, label %if.then106, label %if.end108, !dbg !880

if.then106:                                       ; preds = %if.end104
  %52 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !881
  %53 = load i64*, i64** %unconsumed.addr, align 8, !dbg !883
  %54 = load i64, i64* %53, align 8, !dbg !884
  %call107 = call i64 @__archive_read_consume(%struct.archive_read* %52, i64 %54), !dbg !885
  %55 = load i64*, i64** %unconsumed.addr, align 8, !dbg !886
  store i64 0, i64* %55, align 8, !dbg !887
  br label %if.end108, !dbg !888

if.end108:                                        ; preds = %if.then106, %if.end104
  %56 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !889
  %57 = load i64, i64* %entry_size, align 8, !dbg !891
  %call109 = call i8* @__archive_read_ahead(%struct.archive_read* %56, i64 %57, i64* null), !dbg !892
  store i8* %call109, i8** %b, align 8, !dbg !893
  %cmp110 = icmp eq i8* %call109, null, !dbg !894
  br i1 %cmp110, label %if.then112, label %if.end113, !dbg !895

if.then112:                                       ; preds = %if.end108
  store i32 -30, i32* %retval, align 4, !dbg !896
  br label %return, !dbg !896

if.end113:                                        ; preds = %if.end108
  %58 = load i8*, i8** %st, align 8, !dbg !897
  %59 = load i8*, i8** %b, align 8, !dbg !898
  %60 = load i64, i64* %entry_size, align 8, !dbg !899
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %58, i8* %59, i64 %60, i32 1, i1 false), !dbg !900
  %61 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !901
  %62 = load i64, i64* %entry_size, align 8, !dbg !902
  %call114 = call i64 @__archive_read_consume(%struct.archive_read* %61, i64 %62), !dbg !903
  %63 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !904
  %entry_bytes_remaining = getelementptr inbounds %struct.ar, %struct.ar* %63, i32 0, i32 0, !dbg !905
  store i64 0, i64* %entry_bytes_remaining, align 8, !dbg !906
  %64 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !907
  %65 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !908
  %entry_bytes_remaining115 = getelementptr inbounds %struct.ar, %struct.ar* %65, i32 0, i32 0, !dbg !909
  %66 = load i64, i64* %entry_bytes_remaining115, align 8, !dbg !909
  call void @archive_entry_set_size(%struct.archive_entry* %64, i64 %66), !dbg !910
  %67 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !911
  %call116 = call i32 @ar_parse_gnu_filename_table(%struct.archive_read* %67), !dbg !912
  store i32 %call116, i32* %retval, align 4, !dbg !913
  br label %return, !dbg !913

if.end117:                                        ; preds = %if.end72
  %arrayidx118 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i64 0, i64 0, !dbg !914
  %68 = load i8, i8* %arrayidx118, align 16, !dbg !914
  %conv119 = sext i8 %68 to i32, !dbg !914
  %cmp120 = icmp eq i32 %conv119, 47, !dbg !916
  br i1 %cmp120, label %land.lhs.true122, label %if.end151, !dbg !917

land.lhs.true122:                                 ; preds = %if.end117
  %arrayidx123 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i64 0, i64 1, !dbg !918
  %69 = load i8, i8* %arrayidx123, align 1, !dbg !918
  %conv124 = sext i8 %69 to i32, !dbg !918
  %cmp125 = icmp sge i32 %conv124, 48, !dbg !920
  br i1 %cmp125, label %land.lhs.true127, label %if.end151, !dbg !921

land.lhs.true127:                                 ; preds = %land.lhs.true122
  %arrayidx128 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i64 0, i64 1, !dbg !922
  %70 = load i8, i8* %arrayidx128, align 1, !dbg !922
  %conv129 = sext i8 %70 to i32, !dbg !922
  %cmp130 = icmp sle i32 %conv129, 57, !dbg !924
  br i1 %cmp130, label %if.then132, label %if.end151, !dbg !925

if.then132:                                       ; preds = %land.lhs.true127
  %71 = load i8*, i8** %h.addr, align 8, !dbg !926
  %add.ptr133 = getelementptr inbounds i8, i8* %71, i64 0, !dbg !928
  %add.ptr134 = getelementptr inbounds i8, i8* %add.ptr133, i64 1, !dbg !929
  %call135 = call i64 @ar_atol10(i8* %add.ptr134, i32 15), !dbg !930
  store i64 %call135, i64* %number, align 8, !dbg !931
  %72 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !932
  %strtab136 = getelementptr inbounds %struct.ar, %struct.ar* %72, i32 0, i32 4, !dbg !934
  %73 = load i8*, i8** %strtab136, align 8, !dbg !934
  %cmp137 = icmp eq i8* %73, null, !dbg !935
  br i1 %cmp137, label %if.then143, label %lor.lhs.false139, !dbg !936

lor.lhs.false139:                                 ; preds = %if.then132
  %74 = load i64, i64* %number, align 8, !dbg !937
  %75 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !939
  %strtab_size140 = getelementptr inbounds %struct.ar, %struct.ar* %75, i32 0, i32 5, !dbg !940
  %76 = load i64, i64* %strtab_size140, align 8, !dbg !940
  %cmp141 = icmp uge i64 %74, %76, !dbg !941
  br i1 %cmp141, label %if.then143, label %if.end147, !dbg !942

if.then143:                                       ; preds = %lor.lhs.false139, %if.then132
  %77 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !943
  %archive144 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %77, i32 0, i32 0, !dbg !945
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive144, i32 22, i8* getelementptr inbounds ([52 x i8], [52 x i8]* @.str.16, i32 0, i32 0)), !dbg !946
  %78 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !947
  %arraydecay145 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !948
  call void @archive_entry_copy_pathname(%struct.archive_entry* %78, i8* %arraydecay145), !dbg !949
  %79 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !950
  %80 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !951
  %81 = load i8*, i8** %h.addr, align 8, !dbg !952
  %call146 = call i32 @ar_parse_common_header(%struct.ar* %79, %struct.archive_entry* %80, i8* %81), !dbg !953
  store i32 -30, i32* %retval, align 4, !dbg !954
  br label %return, !dbg !954

if.end147:                                        ; preds = %lor.lhs.false139
  %82 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !955
  %83 = load i64, i64* %number, align 8, !dbg !956
  %84 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !957
  %strtab148 = getelementptr inbounds %struct.ar, %struct.ar* %84, i32 0, i32 4, !dbg !958
  %85 = load i8*, i8** %strtab148, align 8, !dbg !958
  %arrayidx149 = getelementptr inbounds i8, i8* %85, i64 %83, !dbg !957
  call void @archive_entry_copy_pathname(%struct.archive_entry* %82, i8* %arrayidx149), !dbg !959
  %86 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !960
  %87 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !961
  %88 = load i8*, i8** %h.addr, align 8, !dbg !962
  %call150 = call i32 @ar_parse_common_header(%struct.ar* %86, %struct.archive_entry* %87, i8* %88), !dbg !963
  store i32 %call150, i32* %retval, align 4, !dbg !964
  br label %return, !dbg !964

if.end151:                                        ; preds = %land.lhs.true127, %land.lhs.true122, %if.end117
  %arraydecay152 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !965
  %call153 = call i32 @strncmp(i8* %arraydecay152, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0), i64 3) #7, !dbg !967
  %cmp154 = icmp eq i32 %call153, 0, !dbg !968
  br i1 %cmp154, label %if.then156, label %if.end194, !dbg !969

if.then156:                                       ; preds = %if.end151
  %89 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !970
  %90 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !972
  %91 = load i8*, i8** %h.addr, align 8, !dbg !973
  %call157 = call i32 @ar_parse_common_header(%struct.ar* %89, %struct.archive_entry* %90, i8* %91), !dbg !974
  %92 = load i8*, i8** %h.addr, align 8, !dbg !975
  %add.ptr158 = getelementptr inbounds i8, i8* %92, i64 0, !dbg !976
  %add.ptr159 = getelementptr inbounds i8, i8* %add.ptr158, i64 3, !dbg !977
  %call160 = call i64 @ar_atol10(i8* %add.ptr159, i32 13), !dbg !978
  store i64 %call160, i64* %number, align 8, !dbg !979
  %93 = load i64, i64* %number, align 8, !dbg !980
  %cmp161 = icmp ugt i64 %93, -2, !dbg !982
  br i1 %cmp161, label %if.then170, label %lor.lhs.false163, !dbg !983

lor.lhs.false163:                                 ; preds = %if.then156
  %94 = load i64, i64* %number, align 8, !dbg !984
  %cmp164 = icmp ugt i64 %94, 1048576, !dbg !986
  br i1 %cmp164, label %if.then170, label %lor.lhs.false166, !dbg !987

lor.lhs.false166:                                 ; preds = %lor.lhs.false163
  %95 = load i64, i64* %number, align 8, !dbg !988
  %96 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !989
  %entry_bytes_remaining167 = getelementptr inbounds %struct.ar, %struct.ar* %96, i32 0, i32 0, !dbg !990
  %97 = load i64, i64* %entry_bytes_remaining167, align 8, !dbg !990
  %cmp168 = icmp sgt i64 %95, %97, !dbg !991
  br i1 %cmp168, label %if.then170, label %if.end172, !dbg !992

if.then170:                                       ; preds = %lor.lhs.false166, %lor.lhs.false163, %if.then156
  %98 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !994
  %archive171 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %98, i32 0, i32 0, !dbg !996
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive171, i32 -1, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.17, i32 0, i32 0)), !dbg !997
  store i32 -30, i32* %retval, align 4, !dbg !998
  br label %return, !dbg !998

if.end172:                                        ; preds = %lor.lhs.false166
  %99 = load i64, i64* %number, align 8, !dbg !999
  store i64 %99, i64* %bsd_name_length, align 8, !dbg !1000
  %100 = load i64, i64* %bsd_name_length, align 8, !dbg !1001
  %101 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !1002
  %entry_bytes_remaining173 = getelementptr inbounds %struct.ar, %struct.ar* %101, i32 0, i32 0, !dbg !1003
  %102 = load i64, i64* %entry_bytes_remaining173, align 8, !dbg !1004
  %sub = sub i64 %102, %100, !dbg !1004
  store i64 %sub, i64* %entry_bytes_remaining173, align 8, !dbg !1004
  %103 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1005
  %104 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !1006
  %entry_bytes_remaining174 = getelementptr inbounds %struct.ar, %struct.ar* %104, i32 0, i32 0, !dbg !1007
  %105 = load i64, i64* %entry_bytes_remaining174, align 8, !dbg !1007
  call void @archive_entry_set_size(%struct.archive_entry* %103, i64 %105), !dbg !1008
  %106 = load i64*, i64** %unconsumed.addr, align 8, !dbg !1009
  %107 = load i64, i64* %106, align 8, !dbg !1011
  %tobool175 = icmp ne i64 %107, 0, !dbg !1011
  br i1 %tobool175, label %if.then176, label %if.end178, !dbg !1012

if.then176:                                       ; preds = %if.end172
  %108 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1013
  %109 = load i64*, i64** %unconsumed.addr, align 8, !dbg !1015
  %110 = load i64, i64* %109, align 8, !dbg !1016
  %call177 = call i64 @__archive_read_consume(%struct.archive_read* %108, i64 %110), !dbg !1017
  %111 = load i64*, i64** %unconsumed.addr, align 8, !dbg !1018
  store i64 0, i64* %111, align 8, !dbg !1019
  br label %if.end178, !dbg !1020

if.end178:                                        ; preds = %if.then176, %if.end172
  %112 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1021
  %113 = load i64, i64* %bsd_name_length, align 8, !dbg !1023
  %call179 = call i8* @__archive_read_ahead(%struct.archive_read* %112, i64 %113, i64* null), !dbg !1024
  store i8* %call179, i8** %b, align 8, !dbg !1025
  %cmp180 = icmp eq i8* %call179, null, !dbg !1026
  br i1 %cmp180, label %if.then182, label %if.end184, !dbg !1027

if.then182:                                       ; preds = %if.end178
  %114 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1028
  %archive183 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %114, i32 0, i32 0, !dbg !1030
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive183, i32 -1, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.18, i32 0, i32 0)), !dbg !1031
  store i32 -30, i32* %retval, align 4, !dbg !1032
  br label %return, !dbg !1032

if.end184:                                        ; preds = %if.end178
  %115 = load i64, i64* %bsd_name_length, align 8, !dbg !1033
  %add = add i64 %115, 1, !dbg !1034
  %call185 = call noalias i8* @malloc(i64 %add) #6, !dbg !1035
  store i8* %call185, i8** %p, align 8, !dbg !1036
  %116 = load i8*, i8** %p, align 8, !dbg !1037
  %cmp186 = icmp eq i8* %116, null, !dbg !1039
  br i1 %cmp186, label %if.then188, label %if.end190, !dbg !1040

if.then188:                                       ; preds = %if.end184
  %117 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1041
  %archive189 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %117, i32 0, i32 0, !dbg !1043
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive189, i32 12, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.19, i32 0, i32 0)), !dbg !1044
  store i32 -30, i32* %retval, align 4, !dbg !1045
  br label %return, !dbg !1045

if.end190:                                        ; preds = %if.end184
  %118 = load i8*, i8** %p, align 8, !dbg !1046
  %119 = load i8*, i8** %b, align 8, !dbg !1047
  %120 = load i64, i64* %bsd_name_length, align 8, !dbg !1048
  %call191 = call i8* @strncpy(i8* %118, i8* %119, i64 %120) #6, !dbg !1049
  %121 = load i64, i64* %bsd_name_length, align 8, !dbg !1050
  %122 = load i8*, i8** %p, align 8, !dbg !1051
  %arrayidx192 = getelementptr inbounds i8, i8* %122, i64 %121, !dbg !1051
  store i8 0, i8* %arrayidx192, align 1, !dbg !1052
  %123 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1053
  %124 = load i64, i64* %bsd_name_length, align 8, !dbg !1054
  %call193 = call i64 @__archive_read_consume(%struct.archive_read* %123, i64 %124), !dbg !1055
  %125 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1056
  %126 = load i8*, i8** %p, align 8, !dbg !1057
  call void @archive_entry_copy_pathname(%struct.archive_entry* %125, i8* %126), !dbg !1058
  %127 = load i8*, i8** %p, align 8, !dbg !1059
  call void @free(i8* %127) #6, !dbg !1060
  store i32 0, i32* %retval, align 4, !dbg !1061
  br label %return, !dbg !1061

if.end194:                                        ; preds = %if.end151
  %arraydecay195 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !1062
  %call196 = call i32 @strcmp(i8* %arraydecay195, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.20, i32 0, i32 0)) #7, !dbg !1064
  %cmp197 = icmp eq i32 %call196, 0, !dbg !1065
  br i1 %cmp197, label %if.then199, label %if.end201, !dbg !1066

if.then199:                                       ; preds = %if.end194
  %128 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1067
  call void @archive_entry_copy_pathname(%struct.archive_entry* %128, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.20, i32 0, i32 0)), !dbg !1069
  %129 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !1070
  %130 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1071
  %131 = load i8*, i8** %h.addr, align 8, !dbg !1072
  %call200 = call i32 @ar_parse_common_header(%struct.ar* %129, %struct.archive_entry* %130, i8* %131), !dbg !1073
  store i32 %call200, i32* %r, align 4, !dbg !1074
  %132 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1075
  call void @archive_entry_set_filetype(%struct.archive_entry* %132, i32 32768), !dbg !1076
  %133 = load i32, i32* %r, align 4, !dbg !1077
  store i32 %133, i32* %retval, align 4, !dbg !1078
  br label %return, !dbg !1078

if.end201:                                        ; preds = %if.end194
  %arraydecay202 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !1079
  %call203 = call i32 @strcmp(i8* %arraydecay202, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.7, i32 0, i32 0)) #7, !dbg !1081
  %cmp204 = icmp eq i32 %call203, 0, !dbg !1082
  br i1 %cmp204, label %if.then206, label %if.end209, !dbg !1083

if.then206:                                       ; preds = %if.end201
  %134 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1084
  %arraydecay207 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !1086
  call void @archive_entry_copy_pathname(%struct.archive_entry* %134, i8* %arraydecay207), !dbg !1087
  %135 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !1088
  %136 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1089
  %137 = load i8*, i8** %h.addr, align 8, !dbg !1090
  %call208 = call i32 @ar_parse_common_header(%struct.ar* %135, %struct.archive_entry* %136, i8* %137), !dbg !1091
  store i32 %call208, i32* %retval, align 4, !dbg !1092
  br label %return, !dbg !1092

if.end209:                                        ; preds = %if.end201
  %138 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1093
  %arraydecay210 = getelementptr inbounds [17 x i8], [17 x i8]* %filename, i32 0, i32 0, !dbg !1094
  call void @archive_entry_copy_pathname(%struct.archive_entry* %138, i8* %arraydecay210), !dbg !1095
  %139 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !1096
  %140 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1097
  %141 = load i8*, i8** %h.addr, align 8, !dbg !1098
  %call211 = call i32 @ar_parse_common_header(%struct.ar* %139, %struct.archive_entry* %140, i8* %141), !dbg !1099
  store i32 %call211, i32* %retval, align 4, !dbg !1100
  br label %return, !dbg !1100

return:                                           ; preds = %if.end209, %if.then206, %if.then199, %if.end190, %if.then188, %if.then182, %if.then170, %if.end147, %if.then143, %if.end113, %if.then112, %if.then102, %if.then96, %if.then91, %if.then86, %if.then70, %if.then
  %142 = load i32, i32* %retval, align 4, !dbg !1101
  ret i32 %142, !dbg !1101
}

; Function Attrs: nounwind readonly
declare i32 @strncmp(i8*, i8*, i64) #4

; Function Attrs: nounwind
declare i8* @strncpy(i8*, i8*, i64) #3

; Function Attrs: nounwind readonly
declare i8* @strchr(i8*, i32) #4

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

; Function Attrs: nounwind uwtable
define internal i32 @ar_parse_common_header(%struct.ar* %ar, %struct.archive_entry* %entry1, i8* %h) #0 !dbg !319 {
entry:
  %ar.addr = alloca %struct.ar*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %h.addr = alloca i8*, align 8
  %n = alloca i64, align 8
  store %struct.ar* %ar, %struct.ar** %ar.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.ar** %ar.addr, metadata !1102, metadata !334), !dbg !1103
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1104, metadata !334), !dbg !1105
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !1106, metadata !334), !dbg !1107
  call void @llvm.dbg.declare(metadata i64* %n, metadata !1108, metadata !334), !dbg !1109
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1110
  %1 = load i8*, i8** %h.addr, align 8, !dbg !1111
  %add.ptr = getelementptr inbounds i8, i8* %1, i64 16, !dbg !1112
  %call = call i64 @ar_atol10(i8* %add.ptr, i32 12), !dbg !1113
  call void @archive_entry_set_mtime(%struct.archive_entry* %0, i64 %call, i64 0), !dbg !1114
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1115
  %3 = load i8*, i8** %h.addr, align 8, !dbg !1116
  %add.ptr2 = getelementptr inbounds i8, i8* %3, i64 28, !dbg !1117
  %call3 = call i64 @ar_atol10(i8* %add.ptr2, i32 6), !dbg !1118
  %conv = trunc i64 %call3 to i32, !dbg !1119
  %conv4 = zext i32 %conv to i64, !dbg !1119
  call void @archive_entry_set_uid(%struct.archive_entry* %2, i64 %conv4), !dbg !1120
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1121
  %5 = load i8*, i8** %h.addr, align 8, !dbg !1122
  %add.ptr5 = getelementptr inbounds i8, i8* %5, i64 34, !dbg !1123
  %call6 = call i64 @ar_atol10(i8* %add.ptr5, i32 6), !dbg !1124
  %conv7 = trunc i64 %call6 to i32, !dbg !1125
  %conv8 = zext i32 %conv7 to i64, !dbg !1125
  call void @archive_entry_set_gid(%struct.archive_entry* %4, i64 %conv8), !dbg !1126
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1127
  %7 = load i8*, i8** %h.addr, align 8, !dbg !1128
  %add.ptr9 = getelementptr inbounds i8, i8* %7, i64 40, !dbg !1129
  %call10 = call i64 @ar_atol8(i8* %add.ptr9, i32 8), !dbg !1130
  %conv11 = trunc i64 %call10 to i32, !dbg !1131
  call void @archive_entry_set_mode(%struct.archive_entry* %6, i32 %conv11), !dbg !1132
  %8 = load i8*, i8** %h.addr, align 8, !dbg !1133
  %add.ptr12 = getelementptr inbounds i8, i8* %8, i64 48, !dbg !1134
  %call13 = call i64 @ar_atol10(i8* %add.ptr12, i32 10), !dbg !1135
  store i64 %call13, i64* %n, align 8, !dbg !1136
  %9 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !1137
  %entry_offset = getelementptr inbounds %struct.ar, %struct.ar* %9, i32 0, i32 2, !dbg !1138
  store i64 0, i64* %entry_offset, align 8, !dbg !1139
  %10 = load i64, i64* %n, align 8, !dbg !1140
  %rem = urem i64 %10, 2, !dbg !1141
  %11 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !1142
  %entry_padding = getelementptr inbounds %struct.ar, %struct.ar* %11, i32 0, i32 3, !dbg !1143
  store i64 %rem, i64* %entry_padding, align 8, !dbg !1144
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1145
  %13 = load i64, i64* %n, align 8, !dbg !1146
  call void @archive_entry_set_size(%struct.archive_entry* %12, i64 %13), !dbg !1147
  %14 = load i64, i64* %n, align 8, !dbg !1148
  %15 = load %struct.ar*, %struct.ar** %ar.addr, align 8, !dbg !1149
  %entry_bytes_remaining = getelementptr inbounds %struct.ar, %struct.ar* %15, i32 0, i32 0, !dbg !1150
  store i64 %14, i64* %entry_bytes_remaining, align 8, !dbg !1151
  ret i32 0, !dbg !1152
}

declare void @archive_entry_copy_pathname(%struct.archive_entry*, i8*) #2

declare void @archive_entry_set_filetype(%struct.archive_entry*, i32) #2

; Function Attrs: nounwind uwtable
define internal i64 @ar_atol10(i8* %p, i32 %char_cnt) #0 !dbg !326 {
entry:
  %p.addr = alloca i8*, align 8
  %char_cnt.addr = alloca i32, align 4
  %l = alloca i64, align 8
  %limit = alloca i64, align 8
  %last_digit_limit = alloca i64, align 8
  %base = alloca i32, align 4
  %digit = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1153, metadata !334), !dbg !1154
  store i32 %char_cnt, i32* %char_cnt.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %char_cnt.addr, metadata !1155, metadata !334), !dbg !1156
  call void @llvm.dbg.declare(metadata i64* %l, metadata !1157, metadata !334), !dbg !1158
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !1159, metadata !334), !dbg !1160
  call void @llvm.dbg.declare(metadata i64* %last_digit_limit, metadata !1161, metadata !334), !dbg !1162
  call void @llvm.dbg.declare(metadata i32* %base, metadata !1163, metadata !334), !dbg !1164
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !1165, metadata !334), !dbg !1166
  store i32 10, i32* %base, align 4, !dbg !1167
  %0 = load i32, i32* %base, align 4, !dbg !1168
  %conv = zext i32 %0 to i64, !dbg !1168
  %div = udiv i64 -1, %conv, !dbg !1169
  store i64 %div, i64* %limit, align 8, !dbg !1170
  %1 = load i32, i32* %base, align 4, !dbg !1171
  %conv1 = zext i32 %1 to i64, !dbg !1171
  %rem = urem i64 -1, %conv1, !dbg !1172
  store i64 %rem, i64* %last_digit_limit, align 8, !dbg !1173
  br label %while.cond, !dbg !1174

while.cond:                                       ; preds = %while.body, %entry
  %2 = load i8*, i8** %p.addr, align 8, !dbg !1175
  %3 = load i8, i8* %2, align 1, !dbg !1177
  %conv2 = sext i8 %3 to i32, !dbg !1177
  %cmp = icmp eq i32 %conv2, 32, !dbg !1178
  br i1 %cmp, label %land.rhs, label %lor.lhs.false, !dbg !1179

lor.lhs.false:                                    ; preds = %while.cond
  %4 = load i8*, i8** %p.addr, align 8, !dbg !1180
  %5 = load i8, i8* %4, align 1, !dbg !1182
  %conv4 = sext i8 %5 to i32, !dbg !1182
  %cmp5 = icmp eq i32 %conv4, 9, !dbg !1183
  br i1 %cmp5, label %land.rhs, label %land.end, !dbg !1184

land.rhs:                                         ; preds = %lor.lhs.false, %while.cond
  %6 = load i32, i32* %char_cnt.addr, align 4, !dbg !1185
  %dec = add i32 %6, -1, !dbg !1185
  store i32 %dec, i32* %char_cnt.addr, align 4, !dbg !1185
  %cmp7 = icmp ugt i32 %6, 0, !dbg !1187
  br label %land.end

land.end:                                         ; preds = %land.rhs, %lor.lhs.false
  %7 = phi i1 [ false, %lor.lhs.false ], [ %cmp7, %land.rhs ]
  br i1 %7, label %while.body, label %while.end, !dbg !1188

while.body:                                       ; preds = %land.end
  %8 = load i8*, i8** %p.addr, align 8, !dbg !1190
  %incdec.ptr = getelementptr inbounds i8, i8* %8, i32 1, !dbg !1190
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1190
  br label %while.cond, !dbg !1191

while.end:                                        ; preds = %land.end
  store i64 0, i64* %l, align 8, !dbg !1193
  %9 = load i8*, i8** %p.addr, align 8, !dbg !1194
  %10 = load i8, i8* %9, align 1, !dbg !1195
  %conv9 = sext i8 %10 to i32, !dbg !1195
  %sub = sub nsw i32 %conv9, 48, !dbg !1196
  store i32 %sub, i32* %digit, align 4, !dbg !1197
  br label %while.cond10, !dbg !1198

while.cond10:                                     ; preds = %if.end, %while.end
  %11 = load i8*, i8** %p.addr, align 8, !dbg !1199
  %12 = load i8, i8* %11, align 1, !dbg !1200
  %conv11 = sext i8 %12 to i32, !dbg !1200
  %cmp12 = icmp sge i32 %conv11, 48, !dbg !1201
  br i1 %cmp12, label %land.lhs.true, label %land.end20, !dbg !1202

land.lhs.true:                                    ; preds = %while.cond10
  %13 = load i32, i32* %digit, align 4, !dbg !1203
  %14 = load i32, i32* %base, align 4, !dbg !1204
  %cmp14 = icmp ult i32 %13, %14, !dbg !1205
  br i1 %cmp14, label %land.rhs16, label %land.end20, !dbg !1206

land.rhs16:                                       ; preds = %land.lhs.true
  %15 = load i32, i32* %char_cnt.addr, align 4, !dbg !1207
  %dec17 = add i32 %15, -1, !dbg !1207
  store i32 %dec17, i32* %char_cnt.addr, align 4, !dbg !1207
  %cmp18 = icmp ugt i32 %15, 0, !dbg !1208
  br label %land.end20

land.end20:                                       ; preds = %land.rhs16, %land.lhs.true, %while.cond10
  %16 = phi i1 [ false, %land.lhs.true ], [ false, %while.cond10 ], [ %cmp18, %land.rhs16 ]
  br i1 %16, label %while.body21, label %while.end36, !dbg !1209

while.body21:                                     ; preds = %land.end20
  %17 = load i64, i64* %l, align 8, !dbg !1210
  %18 = load i64, i64* %limit, align 8, !dbg !1213
  %cmp22 = icmp ugt i64 %17, %18, !dbg !1214
  br i1 %cmp22, label %if.then, label %lor.lhs.false24, !dbg !1215

lor.lhs.false24:                                  ; preds = %while.body21
  %19 = load i64, i64* %l, align 8, !dbg !1216
  %20 = load i64, i64* %limit, align 8, !dbg !1218
  %cmp25 = icmp eq i64 %19, %20, !dbg !1219
  br i1 %cmp25, label %land.lhs.true27, label %if.end, !dbg !1220

land.lhs.true27:                                  ; preds = %lor.lhs.false24
  %21 = load i32, i32* %digit, align 4, !dbg !1221
  %conv28 = zext i32 %21 to i64, !dbg !1221
  %22 = load i64, i64* %last_digit_limit, align 8, !dbg !1223
  %cmp29 = icmp ugt i64 %conv28, %22, !dbg !1224
  br i1 %cmp29, label %if.then, label %if.end, !dbg !1225

if.then:                                          ; preds = %land.lhs.true27, %while.body21
  store i64 -1, i64* %l, align 8, !dbg !1226
  br label %while.end36, !dbg !1228

if.end:                                           ; preds = %land.lhs.true27, %lor.lhs.false24
  %23 = load i64, i64* %l, align 8, !dbg !1229
  %24 = load i32, i32* %base, align 4, !dbg !1230
  %conv31 = zext i32 %24 to i64, !dbg !1230
  %mul = mul i64 %23, %conv31, !dbg !1231
  %25 = load i32, i32* %digit, align 4, !dbg !1232
  %conv32 = zext i32 %25 to i64, !dbg !1232
  %add = add i64 %mul, %conv32, !dbg !1233
  store i64 %add, i64* %l, align 8, !dbg !1234
  %26 = load i8*, i8** %p.addr, align 8, !dbg !1235
  %incdec.ptr33 = getelementptr inbounds i8, i8* %26, i32 1, !dbg !1235
  store i8* %incdec.ptr33, i8** %p.addr, align 8, !dbg !1235
  %27 = load i8, i8* %incdec.ptr33, align 1, !dbg !1236
  %conv34 = sext i8 %27 to i32, !dbg !1236
  %sub35 = sub nsw i32 %conv34, 48, !dbg !1237
  store i32 %sub35, i32* %digit, align 4, !dbg !1238
  br label %while.cond10, !dbg !1239

while.end36:                                      ; preds = %if.then, %land.end20
  %28 = load i64, i64* %l, align 8, !dbg !1240
  ret i64 %28, !dbg !1241
}

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @ar_parse_gnu_filename_table(%struct.archive_read* %a) #0 !dbg !327 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %ar = alloca %struct.ar*, align 8
  %p = alloca i8*, align 8
  %size = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1242, metadata !334), !dbg !1243
  call void @llvm.dbg.declare(metadata %struct.ar** %ar, metadata !1244, metadata !334), !dbg !1245
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1246, metadata !334), !dbg !1247
  call void @llvm.dbg.declare(metadata i64* %size, metadata !1248, metadata !334), !dbg !1249
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1250
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !1251
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !1251
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !1252
  %2 = load i8*, i8** %data, align 8, !dbg !1252
  %3 = bitcast i8* %2 to %struct.ar*, !dbg !1253
  store %struct.ar* %3, %struct.ar** %ar, align 8, !dbg !1254
  %4 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !1255
  %strtab_size = getelementptr inbounds %struct.ar, %struct.ar* %4, i32 0, i32 5, !dbg !1256
  %5 = load i64, i64* %strtab_size, align 8, !dbg !1256
  store i64 %5, i64* %size, align 8, !dbg !1257
  %6 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !1258
  %strtab = getelementptr inbounds %struct.ar, %struct.ar* %6, i32 0, i32 4, !dbg !1260
  %7 = load i8*, i8** %strtab, align 8, !dbg !1260
  store i8* %7, i8** %p, align 8, !dbg !1261
  br label %for.cond, !dbg !1262

for.cond:                                         ; preds = %for.inc, %entry
  %8 = load i8*, i8** %p, align 8, !dbg !1263
  %9 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !1266
  %strtab1 = getelementptr inbounds %struct.ar, %struct.ar* %9, i32 0, i32 4, !dbg !1267
  %10 = load i8*, i8** %strtab1, align 8, !dbg !1267
  %11 = load i64, i64* %size, align 8, !dbg !1268
  %add.ptr = getelementptr inbounds i8, i8* %10, i64 %11, !dbg !1269
  %add.ptr2 = getelementptr inbounds i8, i8* %add.ptr, i64 -1, !dbg !1270
  %cmp = icmp ult i8* %8, %add.ptr2, !dbg !1271
  br i1 %cmp, label %for.body, label %for.end, !dbg !1272

for.body:                                         ; preds = %for.cond
  %12 = load i8*, i8** %p, align 8, !dbg !1273
  %13 = load i8, i8* %12, align 1, !dbg !1276
  %conv = sext i8 %13 to i32, !dbg !1276
  %cmp3 = icmp eq i32 %conv, 47, !dbg !1277
  br i1 %cmp3, label %if.then, label %if.end9, !dbg !1278

if.then:                                          ; preds = %for.body
  %14 = load i8*, i8** %p, align 8, !dbg !1279
  %incdec.ptr = getelementptr inbounds i8, i8* %14, i32 1, !dbg !1279
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !1279
  store i8 0, i8* %14, align 1, !dbg !1281
  %15 = load i8*, i8** %p, align 8, !dbg !1282
  %16 = load i8, i8* %15, align 1, !dbg !1284
  %conv5 = sext i8 %16 to i32, !dbg !1284
  %cmp6 = icmp ne i32 %conv5, 10, !dbg !1285
  br i1 %cmp6, label %if.then8, label %if.end, !dbg !1286

if.then8:                                         ; preds = %if.then
  br label %bad_string_table, !dbg !1287

if.end:                                           ; preds = %if.then
  %17 = load i8*, i8** %p, align 8, !dbg !1288
  store i8 0, i8* %17, align 1, !dbg !1289
  br label %if.end9, !dbg !1290

if.end9:                                          ; preds = %if.end, %for.body
  br label %for.inc, !dbg !1291

for.inc:                                          ; preds = %if.end9
  %18 = load i8*, i8** %p, align 8, !dbg !1292
  %incdec.ptr10 = getelementptr inbounds i8, i8* %18, i32 1, !dbg !1292
  store i8* %incdec.ptr10, i8** %p, align 8, !dbg !1292
  br label %for.cond, !dbg !1294

for.end:                                          ; preds = %for.cond
  %19 = load i8*, i8** %p, align 8, !dbg !1295
  %20 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !1297
  %strtab11 = getelementptr inbounds %struct.ar, %struct.ar* %20, i32 0, i32 4, !dbg !1298
  %21 = load i8*, i8** %strtab11, align 8, !dbg !1298
  %22 = load i64, i64* %size, align 8, !dbg !1299
  %add.ptr12 = getelementptr inbounds i8, i8* %21, i64 %22, !dbg !1300
  %cmp13 = icmp ne i8* %19, %add.ptr12, !dbg !1301
  br i1 %cmp13, label %land.lhs.true, label %if.end23, !dbg !1302

land.lhs.true:                                    ; preds = %for.end
  %23 = load i8*, i8** %p, align 8, !dbg !1303
  %24 = load i8, i8* %23, align 1, !dbg !1305
  %conv15 = sext i8 %24 to i32, !dbg !1305
  %cmp16 = icmp ne i32 %conv15, 10, !dbg !1306
  br i1 %cmp16, label %land.lhs.true18, label %if.end23, !dbg !1307

land.lhs.true18:                                  ; preds = %land.lhs.true
  %25 = load i8*, i8** %p, align 8, !dbg !1308
  %26 = load i8, i8* %25, align 1, !dbg !1310
  %conv19 = sext i8 %26 to i32, !dbg !1310
  %cmp20 = icmp ne i32 %conv19, 96, !dbg !1311
  br i1 %cmp20, label %if.then22, label %if.end23, !dbg !1312

if.then22:                                        ; preds = %land.lhs.true18
  br label %bad_string_table, !dbg !1313

if.end23:                                         ; preds = %land.lhs.true18, %land.lhs.true, %for.end
  %27 = load i64, i64* %size, align 8, !dbg !1314
  %sub = sub i64 %27, 1, !dbg !1315
  %28 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !1316
  %strtab24 = getelementptr inbounds %struct.ar, %struct.ar* %28, i32 0, i32 4, !dbg !1317
  %29 = load i8*, i8** %strtab24, align 8, !dbg !1317
  %arrayidx = getelementptr inbounds i8, i8* %29, i64 %sub, !dbg !1316
  store i8 0, i8* %arrayidx, align 1, !dbg !1318
  store i32 0, i32* %retval, align 4, !dbg !1319
  br label %return, !dbg !1319

bad_string_table:                                 ; preds = %if.then22, %if.then8
  %30 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1320
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %30, i32 0, i32 0, !dbg !1321
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 22, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.13, i32 0, i32 0)), !dbg !1322
  %31 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !1323
  %strtab25 = getelementptr inbounds %struct.ar, %struct.ar* %31, i32 0, i32 4, !dbg !1324
  %32 = load i8*, i8** %strtab25, align 8, !dbg !1324
  call void @free(i8* %32) #6, !dbg !1325
  %33 = load %struct.ar*, %struct.ar** %ar, align 8, !dbg !1326
  %strtab26 = getelementptr inbounds %struct.ar, %struct.ar* %33, i32 0, i32 4, !dbg !1327
  store i8* null, i8** %strtab26, align 8, !dbg !1328
  store i32 -30, i32* %retval, align 4, !dbg !1329
  br label %return, !dbg !1329

return:                                           ; preds = %bad_string_table, %if.end23
  %34 = load i32, i32* %retval, align 4, !dbg !1330
  ret i32 %34, !dbg !1330
}

declare void @archive_entry_set_mtime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_uid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_gid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_mode(%struct.archive_entry*, i32) #2

; Function Attrs: nounwind uwtable
define internal i64 @ar_atol8(i8* %p, i32 %char_cnt) #0 !dbg !322 {
entry:
  %p.addr = alloca i8*, align 8
  %char_cnt.addr = alloca i32, align 4
  %l = alloca i64, align 8
  %limit = alloca i64, align 8
  %last_digit_limit = alloca i64, align 8
  %digit = alloca i32, align 4
  %base = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1331, metadata !334), !dbg !1332
  store i32 %char_cnt, i32* %char_cnt.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %char_cnt.addr, metadata !1333, metadata !334), !dbg !1334
  call void @llvm.dbg.declare(metadata i64* %l, metadata !1335, metadata !334), !dbg !1336
  call void @llvm.dbg.declare(metadata i64* %limit, metadata !1337, metadata !334), !dbg !1338
  call void @llvm.dbg.declare(metadata i64* %last_digit_limit, metadata !1339, metadata !334), !dbg !1340
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !1341, metadata !334), !dbg !1342
  call void @llvm.dbg.declare(metadata i32* %base, metadata !1343, metadata !334), !dbg !1344
  store i32 8, i32* %base, align 4, !dbg !1345
  %0 = load i32, i32* %base, align 4, !dbg !1346
  %conv = zext i32 %0 to i64, !dbg !1346
  %div = udiv i64 -1, %conv, !dbg !1347
  store i64 %div, i64* %limit, align 8, !dbg !1348
  %1 = load i32, i32* %base, align 4, !dbg !1349
  %conv1 = zext i32 %1 to i64, !dbg !1349
  %rem = urem i64 -1, %conv1, !dbg !1350
  store i64 %rem, i64* %last_digit_limit, align 8, !dbg !1351
  br label %while.cond, !dbg !1352

while.cond:                                       ; preds = %while.body, %entry
  %2 = load i8*, i8** %p.addr, align 8, !dbg !1353
  %3 = load i8, i8* %2, align 1, !dbg !1355
  %conv2 = sext i8 %3 to i32, !dbg !1355
  %cmp = icmp eq i32 %conv2, 32, !dbg !1356
  br i1 %cmp, label %land.rhs, label %lor.lhs.false, !dbg !1357

lor.lhs.false:                                    ; preds = %while.cond
  %4 = load i8*, i8** %p.addr, align 8, !dbg !1358
  %5 = load i8, i8* %4, align 1, !dbg !1360
  %conv4 = sext i8 %5 to i32, !dbg !1360
  %cmp5 = icmp eq i32 %conv4, 9, !dbg !1361
  br i1 %cmp5, label %land.rhs, label %land.end, !dbg !1362

land.rhs:                                         ; preds = %lor.lhs.false, %while.cond
  %6 = load i32, i32* %char_cnt.addr, align 4, !dbg !1363
  %dec = add i32 %6, -1, !dbg !1363
  store i32 %dec, i32* %char_cnt.addr, align 4, !dbg !1363
  %cmp7 = icmp ugt i32 %6, 0, !dbg !1365
  br label %land.end

land.end:                                         ; preds = %land.rhs, %lor.lhs.false
  %7 = phi i1 [ false, %lor.lhs.false ], [ %cmp7, %land.rhs ]
  br i1 %7, label %while.body, label %while.end, !dbg !1366

while.body:                                       ; preds = %land.end
  %8 = load i8*, i8** %p.addr, align 8, !dbg !1368
  %incdec.ptr = getelementptr inbounds i8, i8* %8, i32 1, !dbg !1368
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1368
  br label %while.cond, !dbg !1369

while.end:                                        ; preds = %land.end
  store i64 0, i64* %l, align 8, !dbg !1371
  %9 = load i8*, i8** %p.addr, align 8, !dbg !1372
  %10 = load i8, i8* %9, align 1, !dbg !1373
  %conv9 = sext i8 %10 to i32, !dbg !1373
  %sub = sub nsw i32 %conv9, 48, !dbg !1374
  store i32 %sub, i32* %digit, align 4, !dbg !1375
  br label %while.cond10, !dbg !1376

while.cond10:                                     ; preds = %if.end, %while.end
  %11 = load i8*, i8** %p.addr, align 8, !dbg !1377
  %12 = load i8, i8* %11, align 1, !dbg !1378
  %conv11 = sext i8 %12 to i32, !dbg !1378
  %cmp12 = icmp sge i32 %conv11, 48, !dbg !1379
  br i1 %cmp12, label %land.lhs.true, label %land.end20, !dbg !1380

land.lhs.true:                                    ; preds = %while.cond10
  %13 = load i32, i32* %digit, align 4, !dbg !1381
  %14 = load i32, i32* %base, align 4, !dbg !1382
  %cmp14 = icmp ult i32 %13, %14, !dbg !1383
  br i1 %cmp14, label %land.rhs16, label %land.end20, !dbg !1384

land.rhs16:                                       ; preds = %land.lhs.true
  %15 = load i32, i32* %char_cnt.addr, align 4, !dbg !1385
  %dec17 = add i32 %15, -1, !dbg !1385
  store i32 %dec17, i32* %char_cnt.addr, align 4, !dbg !1385
  %cmp18 = icmp ugt i32 %15, 0, !dbg !1386
  br label %land.end20

land.end20:                                       ; preds = %land.rhs16, %land.lhs.true, %while.cond10
  %16 = phi i1 [ false, %land.lhs.true ], [ false, %while.cond10 ], [ %cmp18, %land.rhs16 ]
  br i1 %16, label %while.body21, label %while.end36, !dbg !1387

while.body21:                                     ; preds = %land.end20
  %17 = load i64, i64* %l, align 8, !dbg !1388
  %18 = load i64, i64* %limit, align 8, !dbg !1391
  %cmp22 = icmp ugt i64 %17, %18, !dbg !1392
  br i1 %cmp22, label %if.then, label %lor.lhs.false24, !dbg !1393

lor.lhs.false24:                                  ; preds = %while.body21
  %19 = load i64, i64* %l, align 8, !dbg !1394
  %20 = load i64, i64* %limit, align 8, !dbg !1396
  %cmp25 = icmp eq i64 %19, %20, !dbg !1397
  br i1 %cmp25, label %land.lhs.true27, label %if.end, !dbg !1398

land.lhs.true27:                                  ; preds = %lor.lhs.false24
  %21 = load i32, i32* %digit, align 4, !dbg !1399
  %conv28 = zext i32 %21 to i64, !dbg !1399
  %22 = load i64, i64* %last_digit_limit, align 8, !dbg !1401
  %cmp29 = icmp ugt i64 %conv28, %22, !dbg !1402
  br i1 %cmp29, label %if.then, label %if.end, !dbg !1403

if.then:                                          ; preds = %land.lhs.true27, %while.body21
  store i64 -1, i64* %l, align 8, !dbg !1404
  br label %while.end36, !dbg !1406

if.end:                                           ; preds = %land.lhs.true27, %lor.lhs.false24
  %23 = load i64, i64* %l, align 8, !dbg !1407
  %24 = load i32, i32* %base, align 4, !dbg !1408
  %conv31 = zext i32 %24 to i64, !dbg !1408
  %mul = mul i64 %23, %conv31, !dbg !1409
  %25 = load i32, i32* %digit, align 4, !dbg !1410
  %conv32 = zext i32 %25 to i64, !dbg !1410
  %add = add i64 %mul, %conv32, !dbg !1411
  store i64 %add, i64* %l, align 8, !dbg !1412
  %26 = load i8*, i8** %p.addr, align 8, !dbg !1413
  %incdec.ptr33 = getelementptr inbounds i8, i8* %26, i32 1, !dbg !1413
  store i8* %incdec.ptr33, i8** %p.addr, align 8, !dbg !1413
  %27 = load i8, i8* %incdec.ptr33, align 1, !dbg !1414
  %conv34 = sext i8 %27 to i32, !dbg !1414
  %sub35 = sub nsw i32 %conv34, 48, !dbg !1415
  store i32 %sub35, i32* %digit, align 4, !dbg !1416
  br label %while.cond10, !dbg !1417

while.end36:                                      ; preds = %if.then, %land.end20
  %28 = load i64, i64* %l, align 8, !dbg !1418
  ret i64 %28, !dbg !1419
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!330, !331}
!llvm.ident = !{!332}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !311)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_ar.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !291, !122, !80, !301, !45, !52, !95, !304, !307, !309, !38}
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
!291 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !292, size: 64, align: 64)
!292 = !DICompositeType(tag: DW_TAG_structure_type, name: "ar", file: !1, line: 52, size: 448, align: 64, elements: !293)
!293 = !{!294, !295, !296, !297, !298, !299, !300}
!294 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !292, file: !1, line: 53, baseType: !52, size: 64, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_unconsumed", scope: !292, file: !1, line: 58, baseType: !45, size: 64, align: 64, offset: 64)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "entry_offset", scope: !292, file: !1, line: 59, baseType: !52, size: 64, align: 64, offset: 128)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "entry_padding", scope: !292, file: !1, line: 60, baseType: !52, size: 64, align: 64, offset: 192)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "strtab", scope: !292, file: !1, line: 61, baseType: !95, size: 64, align: 64, offset: 256)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "strtab_size", scope: !292, file: !1, line: 62, baseType: !45, size: 64, align: 64, offset: 320)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "read_global_header", scope: !292, file: !1, line: 63, baseType: !82, size: 8, align: 8, offset: 384)
!301 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !302, line: 63, baseType: !303)
!302 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!303 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!304 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !305, line: 75, baseType: !306)
!305 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!306 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !41, line: 139, baseType: !42)
!307 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !302, line: 82, baseType: !308)
!308 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !41, line: 125, baseType: !13)
!309 = !DIDerivedType(tag: DW_TAG_typedef, name: "gid_t", file: !302, line: 49, baseType: !310)
!310 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !41, line: 126, baseType: !13)
!311 = !{!312, !313, !314, !315, !316, !319, !322, !326, !327, !328, !329}
!312 = distinct !DISubprogram(name: "archive_read_support_format_ar", scope: !1, file: !1, line: 98, type: !21, isLocal: false, isDefinition: true, scopeLine: 99, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!313 = distinct !DISubprogram(name: "archive_read_format_ar_cleanup", scope: !1, file: !1, line: 136, type: !251, isLocal: true, isDefinition: true, scopeLine: 137, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!314 = distinct !DISubprogram(name: "archive_read_format_ar_bid", scope: !1, file: !1, line: 149, type: !235, isLocal: true, isDefinition: true, scopeLine: 150, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!315 = distinct !DISubprogram(name: "archive_read_format_ar_read_header", scope: !1, file: !1, line: 420, type: !243, isLocal: true, isDefinition: true, scopeLine: 422, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!316 = distinct !DISubprogram(name: "_ar_read_header", scope: !1, file: !1, line: 168, type: !317, isLocal: true, isDefinition: true, scopeLine: 170, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!317 = !DISubroutineType(types: !318)
!318 = !{!23, !4, !30, !291, !80, !65}
!319 = distinct !DISubprogram(name: "ar_parse_common_header", scope: !1, file: !1, line: 456, type: !320, isLocal: true, isDefinition: true, scopeLine: 458, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!320 = !DISubroutineType(types: !321)
!321 = !{!23, !291, !30, !80}
!322 = distinct !DISubprogram(name: "ar_atol8", scope: !1, file: !1, line: 589, type: !323, isLocal: true, isDefinition: true, scopeLine: 590, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!323 = !DISubroutineType(types: !324)
!324 = !{!325, !80, !13}
!325 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !53, line: 55, baseType: !47)
!326 = distinct !DISubprogram(name: "ar_atol10", scope: !1, file: !1, line: 615, type: !323, isLocal: true, isDefinition: true, scopeLine: 616, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!327 = distinct !DISubprogram(name: "ar_parse_gnu_filename_table", scope: !1, file: !1, line: 551, type: !251, isLocal: true, isDefinition: true, scopeLine: 552, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!328 = distinct !DISubprogram(name: "archive_read_format_ar_read_data", scope: !1, file: !1, line: 480, type: !247, isLocal: true, isDefinition: true, scopeLine: 482, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!329 = distinct !DISubprogram(name: "archive_read_format_ar_skip", scope: !1, file: !1, line: 530, type: !251, isLocal: true, isDefinition: true, scopeLine: 531, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!330 = !{i32 2, !"Dwarf Version", i32 4}
!331 = !{i32 2, !"Debug Info Version", i32 3}
!332 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!333 = !DILocalVariable(name: "_a", arg: 1, scope: !312, file: !1, line: 98, type: !24)
!334 = !DIExpression()
!335 = !DILocation(line: 98, column: 48, scope: !312)
!336 = !DILocalVariable(name: "a", scope: !312, file: !1, line: 100, type: !4)
!337 = !DILocation(line: 100, column: 23, scope: !312)
!338 = !DILocation(line: 100, column: 50, scope: !312)
!339 = !DILocation(line: 100, column: 27, scope: !312)
!340 = !DILocalVariable(name: "ar", scope: !312, file: !1, line: 101, type: !291)
!341 = !DILocation(line: 101, column: 13, scope: !312)
!342 = !DILocalVariable(name: "r", scope: !312, file: !1, line: 102, type: !23)
!343 = !DILocation(line: 102, column: 6, scope: !312)
!344 = !DILocation(line: 104, column: 2, scope: !312)
!345 = !DILocalVariable(name: "magic_test", scope: !346, file: !1, line: 104, type: !23)
!346 = distinct !DILexicalBlock(scope: !312, file: !1, line: 104, column: 2)
!347 = !DILocation(line: 104, column: 2, scope: !346)
!348 = !DILocation(line: 104, column: 2, scope: !349)
!349 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 1)
!350 = !DILocation(line: 104, column: 2, scope: !351)
!351 = !DILexicalBlockFile(scope: !352, file: !1, discriminator: 2)
!352 = distinct !DILexicalBlock(scope: !346, file: !1, line: 104, column: 2)
!353 = !DILocation(line: 104, column: 2, scope: !354)
!354 = !DILexicalBlockFile(scope: !346, file: !1, discriminator: 3)
!355 = !DILocation(line: 107, column: 20, scope: !312)
!356 = !DILocation(line: 107, column: 7, scope: !312)
!357 = !DILocation(line: 107, column: 5, scope: !312)
!358 = !DILocation(line: 108, column: 6, scope: !359)
!359 = distinct !DILexicalBlock(scope: !312, file: !1, line: 108, column: 6)
!360 = !DILocation(line: 108, column: 9, scope: !359)
!361 = !DILocation(line: 108, column: 6, scope: !312)
!362 = !DILocation(line: 109, column: 22, scope: !363)
!363 = distinct !DILexicalBlock(scope: !359, file: !1, line: 108, column: 18)
!364 = !DILocation(line: 109, column: 25, scope: !363)
!365 = !DILocation(line: 109, column: 3, scope: !363)
!366 = !DILocation(line: 111, column: 3, scope: !363)
!367 = !DILocation(line: 113, column: 2, scope: !312)
!368 = !DILocation(line: 113, column: 6, scope: !312)
!369 = !DILocation(line: 113, column: 13, scope: !312)
!370 = !DILocation(line: 115, column: 37, scope: !312)
!371 = !DILocation(line: 116, column: 6, scope: !312)
!372 = !DILocation(line: 115, column: 6, scope: !312)
!373 = !DILocation(line: 115, column: 4, scope: !312)
!374 = !DILocation(line: 128, column: 6, scope: !375)
!375 = distinct !DILexicalBlock(scope: !312, file: !1, line: 128, column: 6)
!376 = !DILocation(line: 128, column: 8, scope: !375)
!377 = !DILocation(line: 128, column: 6, scope: !312)
!378 = !DILocation(line: 129, column: 8, scope: !379)
!379 = distinct !DILexicalBlock(scope: !375, file: !1, line: 128, column: 23)
!380 = !DILocation(line: 129, column: 3, scope: !379)
!381 = !DILocation(line: 130, column: 11, scope: !379)
!382 = !DILocation(line: 130, column: 3, scope: !379)
!383 = !DILocation(line: 132, column: 2, scope: !312)
!384 = !DILocation(line: 133, column: 1, scope: !312)
!385 = !DILocalVariable(name: "a", arg: 1, scope: !314, file: !1, line: 149, type: !4)
!386 = !DILocation(line: 149, column: 49, scope: !314)
!387 = !DILocalVariable(name: "best_bid", arg: 2, scope: !314, file: !1, line: 149, type: !23)
!388 = !DILocation(line: 149, column: 56, scope: !314)
!389 = !DILocalVariable(name: "h", scope: !314, file: !1, line: 151, type: !43)
!390 = !DILocation(line: 151, column: 14, scope: !314)
!391 = !DILocation(line: 153, column: 8, scope: !314)
!392 = !DILocation(line: 159, column: 32, scope: !393)
!393 = distinct !DILexicalBlock(scope: !314, file: !1, line: 159, column: 6)
!394 = !DILocation(line: 159, column: 11, scope: !393)
!395 = !DILocation(line: 159, column: 9, scope: !393)
!396 = !DILocation(line: 159, column: 45, scope: !393)
!397 = !DILocation(line: 159, column: 6, scope: !314)
!398 = !DILocation(line: 160, column: 3, scope: !393)
!399 = !DILocation(line: 161, column: 13, scope: !400)
!400 = distinct !DILexicalBlock(scope: !314, file: !1, line: 161, column: 6)
!401 = !DILocation(line: 161, column: 6, scope: !400)
!402 = !DILocation(line: 161, column: 32, scope: !400)
!403 = !DILocation(line: 161, column: 6, scope: !314)
!404 = !DILocation(line: 162, column: 3, scope: !405)
!405 = distinct !DILexicalBlock(scope: !400, file: !1, line: 161, column: 38)
!406 = !DILocation(line: 164, column: 2, scope: !314)
!407 = !DILocation(line: 165, column: 1, scope: !314)
!408 = !DILocalVariable(name: "a", arg: 1, scope: !315, file: !1, line: 420, type: !4)
!409 = !DILocation(line: 420, column: 57, scope: !315)
!410 = !DILocalVariable(name: "entry", arg: 2, scope: !315, file: !1, line: 421, type: !30)
!411 = !DILocation(line: 421, column: 27, scope: !315)
!412 = !DILocalVariable(name: "ar", scope: !315, file: !1, line: 423, type: !291)
!413 = !DILocation(line: 423, column: 13, scope: !315)
!414 = !DILocation(line: 423, column: 31, scope: !315)
!415 = !DILocation(line: 423, column: 34, scope: !315)
!416 = !DILocation(line: 423, column: 42, scope: !315)
!417 = !DILocation(line: 423, column: 18, scope: !315)
!418 = !DILocalVariable(name: "unconsumed", scope: !315, file: !1, line: 424, type: !45)
!419 = !DILocation(line: 424, column: 9, scope: !315)
!420 = !DILocalVariable(name: "header_data", scope: !315, file: !1, line: 425, type: !43)
!421 = !DILocation(line: 425, column: 14, scope: !315)
!422 = !DILocalVariable(name: "ret", scope: !315, file: !1, line: 426, type: !23)
!423 = !DILocation(line: 426, column: 6, scope: !315)
!424 = !DILocation(line: 428, column: 7, scope: !425)
!425 = distinct !DILexicalBlock(scope: !315, file: !1, line: 428, column: 6)
!426 = !DILocation(line: 428, column: 11, scope: !425)
!427 = !DILocation(line: 428, column: 6, scope: !315)
!428 = !DILocation(line: 433, column: 26, scope: !429)
!429 = distinct !DILexicalBlock(scope: !425, file: !1, line: 428, column: 31)
!430 = !DILocation(line: 433, column: 3, scope: !429)
!431 = !DILocation(line: 434, column: 3, scope: !429)
!432 = !DILocation(line: 434, column: 7, scope: !429)
!433 = !DILocation(line: 434, column: 26, scope: !429)
!434 = !DILocation(line: 436, column: 3, scope: !429)
!435 = !DILocation(line: 436, column: 6, scope: !429)
!436 = !DILocation(line: 436, column: 14, scope: !429)
!437 = !DILocation(line: 436, column: 29, scope: !429)
!438 = !DILocation(line: 437, column: 2, scope: !429)
!439 = !DILocation(line: 440, column: 42, scope: !440)
!440 = distinct !DILexicalBlock(scope: !315, file: !1, line: 440, column: 6)
!441 = !DILocation(line: 440, column: 21, scope: !440)
!442 = !DILocation(line: 440, column: 19, scope: !440)
!443 = !DILocation(line: 440, column: 56, scope: !440)
!444 = !DILocation(line: 440, column: 6, scope: !315)
!445 = !DILocation(line: 442, column: 3, scope: !440)
!446 = !DILocation(line: 444, column: 13, scope: !315)
!447 = !DILocation(line: 446, column: 24, scope: !315)
!448 = !DILocation(line: 446, column: 27, scope: !315)
!449 = !DILocation(line: 446, column: 34, scope: !315)
!450 = !DILocation(line: 446, column: 52, scope: !315)
!451 = !DILocation(line: 446, column: 8, scope: !315)
!452 = !DILocation(line: 446, column: 6, scope: !315)
!453 = !DILocation(line: 448, column: 6, scope: !454)
!454 = distinct !DILexicalBlock(scope: !315, file: !1, line: 448, column: 6)
!455 = !DILocation(line: 448, column: 6, scope: !315)
!456 = !DILocation(line: 449, column: 26, scope: !454)
!457 = !DILocation(line: 449, column: 29, scope: !454)
!458 = !DILocation(line: 449, column: 3, scope: !454)
!459 = !DILocation(line: 451, column: 9, scope: !315)
!460 = !DILocation(line: 451, column: 2, scope: !315)
!461 = !DILocation(line: 452, column: 1, scope: !315)
!462 = !DILocalVariable(name: "a", arg: 1, scope: !328, file: !1, line: 480, type: !4)
!463 = !DILocation(line: 480, column: 55, scope: !328)
!464 = !DILocalVariable(name: "buff", arg: 2, scope: !328, file: !1, line: 481, type: !64)
!465 = !DILocation(line: 481, column: 18, scope: !328)
!466 = !DILocalVariable(name: "size", arg: 3, scope: !328, file: !1, line: 481, type: !65)
!467 = !DILocation(line: 481, column: 32, scope: !328)
!468 = !DILocalVariable(name: "offset", arg: 4, scope: !328, file: !1, line: 481, type: !66)
!469 = !DILocation(line: 481, column: 47, scope: !328)
!470 = !DILocalVariable(name: "bytes_read", scope: !328, file: !1, line: 483, type: !38)
!471 = !DILocation(line: 483, column: 10, scope: !328)
!472 = !DILocalVariable(name: "ar", scope: !328, file: !1, line: 484, type: !291)
!473 = !DILocation(line: 484, column: 13, scope: !328)
!474 = !DILocation(line: 486, column: 21, scope: !328)
!475 = !DILocation(line: 486, column: 24, scope: !328)
!476 = !DILocation(line: 486, column: 32, scope: !328)
!477 = !DILocation(line: 486, column: 7, scope: !328)
!478 = !DILocation(line: 486, column: 5, scope: !328)
!479 = !DILocation(line: 488, column: 6, scope: !480)
!480 = distinct !DILexicalBlock(scope: !328, file: !1, line: 488, column: 6)
!481 = !DILocation(line: 488, column: 10, scope: !480)
!482 = !DILocation(line: 488, column: 6, scope: !328)
!483 = !DILocation(line: 489, column: 26, scope: !484)
!484 = distinct !DILexicalBlock(scope: !480, file: !1, line: 488, column: 34)
!485 = !DILocation(line: 489, column: 29, scope: !484)
!486 = !DILocation(line: 489, column: 33, scope: !484)
!487 = !DILocation(line: 489, column: 3, scope: !484)
!488 = !DILocation(line: 490, column: 3, scope: !484)
!489 = !DILocation(line: 490, column: 7, scope: !484)
!490 = !DILocation(line: 490, column: 30, scope: !484)
!491 = !DILocation(line: 491, column: 2, scope: !484)
!492 = !DILocation(line: 493, column: 6, scope: !493)
!493 = distinct !DILexicalBlock(scope: !328, file: !1, line: 493, column: 6)
!494 = !DILocation(line: 493, column: 10, scope: !493)
!495 = !DILocation(line: 493, column: 32, scope: !493)
!496 = !DILocation(line: 493, column: 6, scope: !328)
!497 = !DILocation(line: 494, column: 32, scope: !498)
!498 = distinct !DILexicalBlock(scope: !493, file: !1, line: 493, column: 37)
!499 = !DILocation(line: 494, column: 11, scope: !498)
!500 = !DILocation(line: 494, column: 4, scope: !498)
!501 = !DILocation(line: 494, column: 9, scope: !498)
!502 = !DILocation(line: 495, column: 7, scope: !503)
!503 = distinct !DILexicalBlock(scope: !498, file: !1, line: 495, column: 7)
!504 = !DILocation(line: 495, column: 18, scope: !503)
!505 = !DILocation(line: 495, column: 7, scope: !498)
!506 = !DILocation(line: 496, column: 23, scope: !507)
!507 = distinct !DILexicalBlock(scope: !503, file: !1, line: 495, column: 24)
!508 = !DILocation(line: 496, column: 26, scope: !507)
!509 = !DILocation(line: 496, column: 4, scope: !507)
!510 = !DILocation(line: 498, column: 4, scope: !507)
!511 = !DILocation(line: 500, column: 7, scope: !512)
!512 = distinct !DILexicalBlock(scope: !498, file: !1, line: 500, column: 7)
!513 = !DILocation(line: 500, column: 18, scope: !512)
!514 = !DILocation(line: 500, column: 7, scope: !498)
!515 = !DILocation(line: 501, column: 4, scope: !512)
!516 = !DILocation(line: 502, column: 7, scope: !517)
!517 = distinct !DILexicalBlock(scope: !498, file: !1, line: 502, column: 7)
!518 = !DILocation(line: 502, column: 20, scope: !517)
!519 = !DILocation(line: 502, column: 24, scope: !517)
!520 = !DILocation(line: 502, column: 18, scope: !517)
!521 = !DILocation(line: 502, column: 7, scope: !498)
!522 = !DILocation(line: 503, column: 26, scope: !517)
!523 = !DILocation(line: 503, column: 30, scope: !517)
!524 = !DILocation(line: 503, column: 15, scope: !517)
!525 = !DILocation(line: 503, column: 4, scope: !517)
!526 = !DILocation(line: 504, column: 11, scope: !498)
!527 = !DILocation(line: 504, column: 4, scope: !498)
!528 = !DILocation(line: 504, column: 9, scope: !498)
!529 = !DILocation(line: 505, column: 32, scope: !498)
!530 = !DILocation(line: 505, column: 3, scope: !498)
!531 = !DILocation(line: 505, column: 7, scope: !498)
!532 = !DILocation(line: 505, column: 30, scope: !498)
!533 = !DILocation(line: 506, column: 13, scope: !498)
!534 = !DILocation(line: 506, column: 17, scope: !498)
!535 = !DILocation(line: 506, column: 4, scope: !498)
!536 = !DILocation(line: 506, column: 11, scope: !498)
!537 = !DILocation(line: 507, column: 23, scope: !498)
!538 = !DILocation(line: 507, column: 3, scope: !498)
!539 = !DILocation(line: 507, column: 7, scope: !498)
!540 = !DILocation(line: 507, column: 20, scope: !498)
!541 = !DILocation(line: 508, column: 32, scope: !498)
!542 = !DILocation(line: 508, column: 3, scope: !498)
!543 = !DILocation(line: 508, column: 7, scope: !498)
!544 = !DILocation(line: 508, column: 29, scope: !498)
!545 = !DILocation(line: 509, column: 3, scope: !498)
!546 = !DILocalVariable(name: "skipped", scope: !547, file: !1, line: 511, type: !52)
!547 = distinct !DILexicalBlock(scope: !493, file: !1, line: 510, column: 9)
!548 = !DILocation(line: 511, column: 11, scope: !547)
!549 = !DILocation(line: 511, column: 44, scope: !547)
!550 = !DILocation(line: 511, column: 47, scope: !547)
!551 = !DILocation(line: 511, column: 51, scope: !547)
!552 = !DILocation(line: 511, column: 21, scope: !547)
!553 = !DILocation(line: 512, column: 7, scope: !554)
!554 = distinct !DILexicalBlock(scope: !547, file: !1, line: 512, column: 7)
!555 = !DILocation(line: 512, column: 15, scope: !554)
!556 = !DILocation(line: 512, column: 7, scope: !547)
!557 = !DILocation(line: 513, column: 25, scope: !558)
!558 = distinct !DILexicalBlock(scope: !554, file: !1, line: 512, column: 21)
!559 = !DILocation(line: 513, column: 4, scope: !558)
!560 = !DILocation(line: 513, column: 8, scope: !558)
!561 = !DILocation(line: 513, column: 22, scope: !558)
!562 = !DILocation(line: 514, column: 3, scope: !558)
!563 = !DILocation(line: 515, column: 7, scope: !564)
!564 = distinct !DILexicalBlock(scope: !547, file: !1, line: 515, column: 7)
!565 = !DILocation(line: 515, column: 11, scope: !564)
!566 = !DILocation(line: 515, column: 7, scope: !547)
!567 = !DILocation(line: 516, column: 8, scope: !568)
!568 = distinct !DILexicalBlock(scope: !569, file: !1, line: 516, column: 8)
!569 = distinct !DILexicalBlock(scope: !564, file: !1, line: 515, column: 26)
!570 = !DILocation(line: 516, column: 16, scope: !568)
!571 = !DILocation(line: 516, column: 8, scope: !569)
!572 = !DILocation(line: 517, column: 24, scope: !573)
!573 = distinct !DILexicalBlock(scope: !568, file: !1, line: 516, column: 22)
!574 = !DILocation(line: 517, column: 27, scope: !573)
!575 = !DILocation(line: 517, column: 5, scope: !573)
!576 = !DILocation(line: 519, column: 4, scope: !573)
!577 = !DILocation(line: 520, column: 4, scope: !569)
!578 = !DILocation(line: 522, column: 4, scope: !547)
!579 = !DILocation(line: 522, column: 9, scope: !547)
!580 = !DILocation(line: 523, column: 4, scope: !547)
!581 = !DILocation(line: 523, column: 9, scope: !547)
!582 = !DILocation(line: 524, column: 13, scope: !547)
!583 = !DILocation(line: 524, column: 17, scope: !547)
!584 = !DILocation(line: 524, column: 4, scope: !547)
!585 = !DILocation(line: 524, column: 11, scope: !547)
!586 = !DILocation(line: 525, column: 3, scope: !547)
!587 = !DILocation(line: 527, column: 1, scope: !328)
!588 = !DILocalVariable(name: "a", arg: 1, scope: !329, file: !1, line: 530, type: !4)
!589 = !DILocation(line: 530, column: 50, scope: !329)
!590 = !DILocalVariable(name: "bytes_skipped", scope: !329, file: !1, line: 532, type: !52)
!591 = !DILocation(line: 532, column: 10, scope: !329)
!592 = !DILocalVariable(name: "ar", scope: !329, file: !1, line: 533, type: !291)
!593 = !DILocation(line: 533, column: 13, scope: !329)
!594 = !DILocation(line: 535, column: 21, scope: !329)
!595 = !DILocation(line: 535, column: 24, scope: !329)
!596 = !DILocation(line: 535, column: 32, scope: !329)
!597 = !DILocation(line: 535, column: 7, scope: !329)
!598 = !DILocation(line: 535, column: 5, scope: !329)
!599 = !DILocation(line: 537, column: 41, scope: !329)
!600 = !DILocation(line: 538, column: 6, scope: !329)
!601 = !DILocation(line: 538, column: 10, scope: !329)
!602 = !DILocation(line: 538, column: 34, scope: !329)
!603 = !DILocation(line: 538, column: 38, scope: !329)
!604 = !DILocation(line: 538, column: 32, scope: !329)
!605 = !DILocation(line: 539, column: 8, scope: !329)
!606 = !DILocation(line: 539, column: 12, scope: !329)
!607 = !DILocation(line: 539, column: 6, scope: !329)
!608 = !DILocation(line: 537, column: 18, scope: !329)
!609 = !DILocation(line: 537, column: 16, scope: !329)
!610 = !DILocation(line: 540, column: 6, scope: !611)
!611 = distinct !DILexicalBlock(scope: !329, file: !1, line: 540, column: 6)
!612 = !DILocation(line: 540, column: 20, scope: !611)
!613 = !DILocation(line: 540, column: 6, scope: !329)
!614 = !DILocation(line: 541, column: 3, scope: !611)
!615 = !DILocation(line: 543, column: 2, scope: !329)
!616 = !DILocation(line: 543, column: 6, scope: !329)
!617 = !DILocation(line: 543, column: 28, scope: !329)
!618 = !DILocation(line: 544, column: 2, scope: !329)
!619 = !DILocation(line: 544, column: 6, scope: !329)
!620 = !DILocation(line: 544, column: 29, scope: !329)
!621 = !DILocation(line: 545, column: 2, scope: !329)
!622 = !DILocation(line: 545, column: 6, scope: !329)
!623 = !DILocation(line: 545, column: 20, scope: !329)
!624 = !DILocation(line: 547, column: 2, scope: !329)
!625 = !DILocation(line: 548, column: 1, scope: !329)
!626 = !DILocalVariable(name: "a", arg: 1, scope: !313, file: !1, line: 136, type: !4)
!627 = !DILocation(line: 136, column: 53, scope: !313)
!628 = !DILocalVariable(name: "ar", scope: !313, file: !1, line: 138, type: !291)
!629 = !DILocation(line: 138, column: 13, scope: !313)
!630 = !DILocation(line: 140, column: 21, scope: !313)
!631 = !DILocation(line: 140, column: 24, scope: !313)
!632 = !DILocation(line: 140, column: 32, scope: !313)
!633 = !DILocation(line: 140, column: 7, scope: !313)
!634 = !DILocation(line: 140, column: 5, scope: !313)
!635 = !DILocation(line: 141, column: 6, scope: !636)
!636 = distinct !DILexicalBlock(scope: !313, file: !1, line: 141, column: 6)
!637 = !DILocation(line: 141, column: 10, scope: !636)
!638 = !DILocation(line: 141, column: 6, scope: !313)
!639 = !DILocation(line: 142, column: 8, scope: !636)
!640 = !DILocation(line: 142, column: 12, scope: !636)
!641 = !DILocation(line: 142, column: 3, scope: !636)
!642 = !DILocation(line: 143, column: 7, scope: !313)
!643 = !DILocation(line: 143, column: 2, scope: !313)
!644 = !DILocation(line: 144, column: 3, scope: !313)
!645 = !DILocation(line: 144, column: 6, scope: !313)
!646 = !DILocation(line: 144, column: 14, scope: !313)
!647 = !DILocation(line: 144, column: 20, scope: !313)
!648 = !DILocation(line: 145, column: 2, scope: !313)
!649 = !DILocalVariable(name: "a", arg: 1, scope: !316, file: !1, line: 168, type: !4)
!650 = !DILocation(line: 168, column: 38, scope: !316)
!651 = !DILocalVariable(name: "entry", arg: 2, scope: !316, file: !1, line: 168, type: !30)
!652 = !DILocation(line: 168, column: 63, scope: !316)
!653 = !DILocalVariable(name: "ar", arg: 3, scope: !316, file: !1, line: 169, type: !291)
!654 = !DILocation(line: 169, column: 13, scope: !316)
!655 = !DILocalVariable(name: "h", arg: 4, scope: !316, file: !1, line: 169, type: !80)
!656 = !DILocation(line: 169, column: 29, scope: !316)
!657 = !DILocalVariable(name: "unconsumed", arg: 5, scope: !316, file: !1, line: 169, type: !65)
!658 = !DILocation(line: 169, column: 40, scope: !316)
!659 = !DILocalVariable(name: "filename", scope: !316, file: !1, line: 171, type: !660)
!660 = !DICompositeType(tag: DW_TAG_array_type, baseType: !82, size: 136, align: 8, elements: !661)
!661 = !{!662}
!662 = !DISubrange(count: 17)
!663 = !DILocation(line: 171, column: 7, scope: !316)
!664 = !DILocalVariable(name: "number", scope: !316, file: !1, line: 172, type: !325)
!665 = !DILocation(line: 172, column: 11, scope: !316)
!666 = !DILocalVariable(name: "bsd_name_length", scope: !316, file: !1, line: 173, type: !45)
!667 = !DILocation(line: 173, column: 9, scope: !316)
!668 = !DILocalVariable(name: "entry_size", scope: !316, file: !1, line: 173, type: !45)
!669 = !DILocation(line: 173, column: 26, scope: !316)
!670 = !DILocalVariable(name: "p", scope: !316, file: !1, line: 174, type: !95)
!671 = !DILocation(line: 174, column: 8, scope: !316)
!672 = !DILocalVariable(name: "st", scope: !316, file: !1, line: 174, type: !95)
!673 = !DILocation(line: 174, column: 12, scope: !316)
!674 = !DILocalVariable(name: "b", scope: !316, file: !1, line: 175, type: !43)
!675 = !DILocation(line: 175, column: 14, scope: !316)
!676 = !DILocalVariable(name: "r", scope: !316, file: !1, line: 176, type: !23)
!677 = !DILocation(line: 176, column: 6, scope: !316)
!678 = !DILocation(line: 179, column: 14, scope: !679)
!679 = distinct !DILexicalBlock(scope: !316, file: !1, line: 179, column: 6)
!680 = !DILocation(line: 179, column: 16, scope: !679)
!681 = !DILocation(line: 179, column: 6, scope: !679)
!682 = !DILocation(line: 179, column: 44, scope: !679)
!683 = !DILocation(line: 179, column: 6, scope: !316)
!684 = !DILocation(line: 180, column: 22, scope: !685)
!685 = distinct !DILexicalBlock(scope: !679, file: !1, line: 179, column: 50)
!686 = !DILocation(line: 180, column: 25, scope: !685)
!687 = !DILocation(line: 180, column: 3, scope: !685)
!688 = !DILocation(line: 182, column: 3, scope: !685)
!689 = !DILocation(line: 186, column: 10, scope: !316)
!690 = !DILocation(line: 186, column: 20, scope: !316)
!691 = !DILocation(line: 186, column: 22, scope: !316)
!692 = !DILocation(line: 186, column: 2, scope: !316)
!693 = !DILocation(line: 187, column: 2, scope: !316)
!694 = !DILocation(line: 187, column: 25, scope: !316)
!695 = !DILocation(line: 192, column: 6, scope: !696)
!696 = distinct !DILexicalBlock(scope: !316, file: !1, line: 192, column: 6)
!697 = !DILocation(line: 192, column: 9, scope: !696)
!698 = !DILocation(line: 192, column: 17, scope: !696)
!699 = !DILocation(line: 192, column: 32, scope: !696)
!700 = !DILocation(line: 192, column: 6, scope: !316)
!701 = !DILocation(line: 200, column: 15, scope: !702)
!702 = distinct !DILexicalBlock(scope: !703, file: !1, line: 200, column: 7)
!703 = distinct !DILexicalBlock(scope: !696, file: !1, line: 192, column: 54)
!704 = !DILocation(line: 200, column: 7, scope: !702)
!705 = !DILocation(line: 200, column: 35, scope: !702)
!706 = !DILocation(line: 200, column: 7, scope: !703)
!707 = !DILocation(line: 201, column: 4, scope: !702)
!708 = !DILocation(line: 201, column: 7, scope: !702)
!709 = !DILocation(line: 201, column: 15, scope: !702)
!710 = !DILocation(line: 201, column: 30, scope: !702)
!711 = !DILocation(line: 202, column: 19, scope: !712)
!712 = distinct !DILexicalBlock(scope: !702, file: !1, line: 202, column: 12)
!713 = !DILocation(line: 202, column: 12, scope: !712)
!714 = !DILocation(line: 202, column: 34, scope: !712)
!715 = !DILocation(line: 202, column: 12, scope: !702)
!716 = !DILocation(line: 203, column: 4, scope: !712)
!717 = !DILocation(line: 203, column: 7, scope: !712)
!718 = !DILocation(line: 203, column: 15, scope: !712)
!719 = !DILocation(line: 203, column: 30, scope: !712)
!720 = !DILocation(line: 204, column: 20, scope: !721)
!721 = distinct !DILexicalBlock(scope: !712, file: !1, line: 204, column: 12)
!722 = !DILocation(line: 204, column: 12, scope: !721)
!723 = !DILocation(line: 204, column: 46, scope: !721)
!724 = !DILocation(line: 204, column: 12, scope: !712)
!725 = !DILocation(line: 205, column: 4, scope: !721)
!726 = !DILocation(line: 205, column: 7, scope: !721)
!727 = !DILocation(line: 205, column: 15, scope: !721)
!728 = !DILocation(line: 205, column: 30, scope: !721)
!729 = !DILocation(line: 211, column: 2, scope: !703)
!730 = !DILocation(line: 214, column: 6, scope: !731)
!731 = distinct !DILexicalBlock(scope: !316, file: !1, line: 214, column: 6)
!732 = !DILocation(line: 214, column: 9, scope: !731)
!733 = !DILocation(line: 214, column: 17, scope: !731)
!734 = !DILocation(line: 214, column: 32, scope: !731)
!735 = !DILocation(line: 214, column: 6, scope: !316)
!736 = !DILocation(line: 215, column: 3, scope: !731)
!737 = !DILocation(line: 215, column: 6, scope: !731)
!738 = !DILocation(line: 215, column: 14, scope: !731)
!739 = !DILocation(line: 215, column: 34, scope: !731)
!740 = !DILocation(line: 216, column: 11, scope: !741)
!741 = distinct !DILexicalBlock(scope: !731, file: !1, line: 216, column: 11)
!742 = !DILocation(line: 216, column: 14, scope: !741)
!743 = !DILocation(line: 216, column: 22, scope: !741)
!744 = !DILocation(line: 216, column: 37, scope: !741)
!745 = !DILocation(line: 216, column: 11, scope: !731)
!746 = !DILocation(line: 217, column: 3, scope: !741)
!747 = !DILocation(line: 217, column: 6, scope: !741)
!748 = !DILocation(line: 217, column: 14, scope: !741)
!749 = !DILocation(line: 217, column: 34, scope: !741)
!750 = !DILocation(line: 219, column: 3, scope: !741)
!751 = !DILocation(line: 219, column: 6, scope: !741)
!752 = !DILocation(line: 219, column: 14, scope: !741)
!753 = !DILocation(line: 219, column: 34, scope: !741)
!754 = !DILocation(line: 228, column: 6, scope: !316)
!755 = !DILocation(line: 228, column: 15, scope: !316)
!756 = !DILocation(line: 228, column: 30, scope: !316)
!757 = !DILocation(line: 228, column: 4, scope: !316)
!758 = !DILocation(line: 229, column: 2, scope: !316)
!759 = !DILocation(line: 229, column: 9, scope: !760)
!760 = !DILexicalBlockFile(scope: !316, file: !1, discriminator: 1)
!761 = !DILocation(line: 229, column: 14, scope: !760)
!762 = !DILocation(line: 229, column: 11, scope: !760)
!763 = !DILocation(line: 229, column: 23, scope: !760)
!764 = !DILocation(line: 229, column: 27, scope: !765)
!765 = !DILexicalBlockFile(scope: !316, file: !1, discriminator: 2)
!766 = !DILocation(line: 229, column: 26, scope: !765)
!767 = !DILocation(line: 229, column: 29, scope: !765)
!768 = !DILocation(line: 229, column: 2, scope: !769)
!769 = !DILexicalBlockFile(scope: !316, file: !1, discriminator: 3)
!770 = !DILocation(line: 230, column: 4, scope: !771)
!771 = distinct !DILexicalBlock(scope: !316, file: !1, line: 229, column: 37)
!772 = !DILocation(line: 230, column: 6, scope: !771)
!773 = !DILocation(line: 231, column: 4, scope: !771)
!774 = !DILocation(line: 229, column: 2, scope: !775)
!775 = !DILexicalBlockFile(scope: !316, file: !1, discriminator: 4)
!776 = !DILocation(line: 241, column: 6, scope: !777)
!777 = distinct !DILexicalBlock(scope: !316, file: !1, line: 241, column: 6)
!778 = !DILocation(line: 241, column: 18, scope: !777)
!779 = !DILocation(line: 241, column: 25, scope: !777)
!780 = !DILocation(line: 241, column: 28, scope: !781)
!781 = !DILexicalBlockFile(scope: !777, file: !1, discriminator: 1)
!782 = !DILocation(line: 241, column: 32, scope: !781)
!783 = !DILocation(line: 241, column: 30, scope: !781)
!784 = !DILocation(line: 241, column: 41, scope: !781)
!785 = !DILocation(line: 241, column: 45, scope: !786)
!786 = !DILexicalBlockFile(scope: !777, file: !1, discriminator: 2)
!787 = !DILocation(line: 241, column: 44, scope: !786)
!788 = !DILocation(line: 241, column: 47, scope: !786)
!789 = !DILocation(line: 241, column: 6, scope: !786)
!790 = !DILocation(line: 242, column: 4, scope: !791)
!791 = distinct !DILexicalBlock(scope: !777, file: !1, line: 241, column: 55)
!792 = !DILocation(line: 242, column: 6, scope: !791)
!793 = !DILocation(line: 243, column: 2, scope: !791)
!794 = !DILocation(line: 245, column: 6, scope: !795)
!795 = distinct !DILexicalBlock(scope: !316, file: !1, line: 245, column: 6)
!796 = !DILocation(line: 245, column: 10, scope: !795)
!797 = !DILocation(line: 245, column: 8, scope: !795)
!798 = !DILocation(line: 245, column: 6, scope: !316)
!799 = !DILocation(line: 246, column: 22, scope: !800)
!800 = distinct !DILexicalBlock(scope: !795, file: !1, line: 245, column: 20)
!801 = !DILocation(line: 246, column: 25, scope: !800)
!802 = !DILocation(line: 246, column: 3, scope: !800)
!803 = !DILocation(line: 248, column: 3, scope: !800)
!804 = !DILocation(line: 255, column: 13, scope: !805)
!805 = distinct !DILexicalBlock(scope: !316, file: !1, line: 255, column: 6)
!806 = !DILocation(line: 255, column: 6, scope: !805)
!807 = !DILocation(line: 255, column: 29, scope: !805)
!808 = !DILocation(line: 255, column: 6, scope: !316)
!809 = !DILocation(line: 257, column: 26, scope: !810)
!810 = distinct !DILexicalBlock(scope: !805, file: !1, line: 255, column: 35)
!811 = !DILocation(line: 257, column: 30, scope: !810)
!812 = !DILocation(line: 257, column: 37, scope: !810)
!813 = !DILocation(line: 257, column: 3, scope: !810)
!814 = !DILocation(line: 258, column: 31, scope: !810)
!815 = !DILocation(line: 258, column: 38, scope: !810)
!816 = !DILocation(line: 258, column: 3, scope: !810)
!817 = !DILocation(line: 259, column: 30, scope: !810)
!818 = !DILocation(line: 259, column: 3, scope: !810)
!819 = !DILocation(line: 261, column: 22, scope: !810)
!820 = !DILocation(line: 261, column: 24, scope: !810)
!821 = !DILocation(line: 261, column: 12, scope: !810)
!822 = !DILocation(line: 261, column: 10, scope: !810)
!823 = !DILocation(line: 262, column: 7, scope: !824)
!824 = distinct !DILexicalBlock(scope: !810, file: !1, line: 262, column: 7)
!825 = !DILocation(line: 262, column: 14, scope: !824)
!826 = !DILocation(line: 262, column: 25, scope: !824)
!827 = !DILocation(line: 262, column: 28, scope: !828)
!828 = !DILexicalBlockFile(scope: !824, file: !1, discriminator: 1)
!829 = !DILocation(line: 262, column: 35, scope: !828)
!830 = !DILocation(line: 262, column: 7, scope: !828)
!831 = !DILocation(line: 263, column: 23, scope: !832)
!832 = distinct !DILexicalBlock(scope: !824, file: !1, line: 262, column: 57)
!833 = !DILocation(line: 263, column: 26, scope: !832)
!834 = !DILocation(line: 263, column: 4, scope: !832)
!835 = !DILocation(line: 265, column: 4, scope: !832)
!836 = !DILocation(line: 267, column: 24, scope: !810)
!837 = !DILocation(line: 267, column: 14, scope: !810)
!838 = !DILocation(line: 268, column: 7, scope: !839)
!839 = distinct !DILexicalBlock(scope: !810, file: !1, line: 268, column: 7)
!840 = !DILocation(line: 268, column: 18, scope: !839)
!841 = !DILocation(line: 268, column: 7, scope: !810)
!842 = !DILocation(line: 269, column: 23, scope: !843)
!843 = distinct !DILexicalBlock(scope: !839, file: !1, line: 268, column: 24)
!844 = !DILocation(line: 269, column: 26, scope: !843)
!845 = !DILocation(line: 269, column: 4, scope: !843)
!846 = !DILocation(line: 271, column: 4, scope: !843)
!847 = !DILocation(line: 273, column: 7, scope: !848)
!848 = distinct !DILexicalBlock(scope: !810, file: !1, line: 273, column: 7)
!849 = !DILocation(line: 273, column: 11, scope: !848)
!850 = !DILocation(line: 273, column: 18, scope: !848)
!851 = !DILocation(line: 273, column: 7, scope: !810)
!852 = !DILocation(line: 274, column: 23, scope: !853)
!853 = distinct !DILexicalBlock(scope: !848, file: !1, line: 273, column: 27)
!854 = !DILocation(line: 274, column: 26, scope: !853)
!855 = !DILocation(line: 274, column: 4, scope: !853)
!856 = !DILocation(line: 276, column: 4, scope: !853)
!857 = !DILocation(line: 280, column: 15, scope: !810)
!858 = !DILocation(line: 280, column: 8, scope: !810)
!859 = !DILocation(line: 280, column: 6, scope: !810)
!860 = !DILocation(line: 281, column: 7, scope: !861)
!861 = distinct !DILexicalBlock(scope: !810, file: !1, line: 281, column: 7)
!862 = !DILocation(line: 281, column: 10, scope: !861)
!863 = !DILocation(line: 281, column: 7, scope: !810)
!864 = !DILocation(line: 282, column: 23, scope: !865)
!865 = distinct !DILexicalBlock(scope: !861, file: !1, line: 281, column: 19)
!866 = !DILocation(line: 282, column: 26, scope: !865)
!867 = !DILocation(line: 282, column: 4, scope: !865)
!868 = !DILocation(line: 284, column: 4, scope: !865)
!869 = !DILocation(line: 286, column: 16, scope: !810)
!870 = !DILocation(line: 286, column: 3, scope: !810)
!871 = !DILocation(line: 286, column: 7, scope: !810)
!872 = !DILocation(line: 286, column: 14, scope: !810)
!873 = !DILocation(line: 287, column: 21, scope: !810)
!874 = !DILocation(line: 287, column: 3, scope: !810)
!875 = !DILocation(line: 287, column: 7, scope: !810)
!876 = !DILocation(line: 287, column: 19, scope: !810)
!877 = !DILocation(line: 289, column: 8, scope: !878)
!878 = distinct !DILexicalBlock(scope: !810, file: !1, line: 289, column: 7)
!879 = !DILocation(line: 289, column: 7, scope: !878)
!880 = !DILocation(line: 289, column: 7, scope: !810)
!881 = !DILocation(line: 290, column: 27, scope: !882)
!882 = distinct !DILexicalBlock(scope: !878, file: !1, line: 289, column: 20)
!883 = !DILocation(line: 290, column: 31, scope: !882)
!884 = !DILocation(line: 290, column: 30, scope: !882)
!885 = !DILocation(line: 290, column: 4, scope: !882)
!886 = !DILocation(line: 291, column: 5, scope: !882)
!887 = !DILocation(line: 291, column: 16, scope: !882)
!888 = !DILocation(line: 292, column: 3, scope: !882)
!889 = !DILocation(line: 294, column: 33, scope: !890)
!890 = distinct !DILexicalBlock(scope: !810, file: !1, line: 294, column: 7)
!891 = !DILocation(line: 294, column: 36, scope: !890)
!892 = !DILocation(line: 294, column: 12, scope: !890)
!893 = !DILocation(line: 294, column: 10, scope: !890)
!894 = !DILocation(line: 294, column: 55, scope: !890)
!895 = !DILocation(line: 294, column: 7, scope: !810)
!896 = !DILocation(line: 295, column: 4, scope: !890)
!897 = !DILocation(line: 296, column: 10, scope: !810)
!898 = !DILocation(line: 296, column: 14, scope: !810)
!899 = !DILocation(line: 296, column: 17, scope: !810)
!900 = !DILocation(line: 296, column: 3, scope: !810)
!901 = !DILocation(line: 297, column: 26, scope: !810)
!902 = !DILocation(line: 297, column: 29, scope: !810)
!903 = !DILocation(line: 297, column: 3, scope: !810)
!904 = !DILocation(line: 299, column: 3, scope: !810)
!905 = !DILocation(line: 299, column: 7, scope: !810)
!906 = !DILocation(line: 299, column: 29, scope: !810)
!907 = !DILocation(line: 300, column: 26, scope: !810)
!908 = !DILocation(line: 300, column: 33, scope: !810)
!909 = !DILocation(line: 300, column: 37, scope: !810)
!910 = !DILocation(line: 300, column: 3, scope: !810)
!911 = !DILocation(line: 303, column: 39, scope: !810)
!912 = !DILocation(line: 303, column: 11, scope: !810)
!913 = !DILocation(line: 303, column: 3, scope: !810)
!914 = !DILocation(line: 312, column: 6, scope: !915)
!915 = distinct !DILexicalBlock(scope: !316, file: !1, line: 312, column: 6)
!916 = !DILocation(line: 312, column: 18, scope: !915)
!917 = !DILocation(line: 312, column: 25, scope: !915)
!918 = !DILocation(line: 312, column: 28, scope: !919)
!919 = !DILexicalBlockFile(scope: !915, file: !1, discriminator: 1)
!920 = !DILocation(line: 312, column: 40, scope: !919)
!921 = !DILocation(line: 312, column: 47, scope: !919)
!922 = !DILocation(line: 312, column: 50, scope: !923)
!923 = !DILexicalBlockFile(scope: !915, file: !1, discriminator: 2)
!924 = !DILocation(line: 312, column: 62, scope: !923)
!925 = !DILocation(line: 312, column: 6, scope: !923)
!926 = !DILocation(line: 313, column: 22, scope: !927)
!927 = distinct !DILexicalBlock(scope: !915, file: !1, line: 312, column: 70)
!928 = !DILocation(line: 313, column: 24, scope: !927)
!929 = !DILocation(line: 313, column: 41, scope: !927)
!930 = !DILocation(line: 313, column: 12, scope: !927)
!931 = !DILocation(line: 313, column: 10, scope: !927)
!932 = !DILocation(line: 318, column: 7, scope: !933)
!933 = distinct !DILexicalBlock(scope: !927, file: !1, line: 318, column: 7)
!934 = !DILocation(line: 318, column: 11, scope: !933)
!935 = !DILocation(line: 318, column: 18, scope: !933)
!936 = !DILocation(line: 318, column: 26, scope: !933)
!937 = !DILocation(line: 318, column: 29, scope: !938)
!938 = !DILexicalBlockFile(scope: !933, file: !1, discriminator: 1)
!939 = !DILocation(line: 318, column: 39, scope: !938)
!940 = !DILocation(line: 318, column: 43, scope: !938)
!941 = !DILocation(line: 318, column: 36, scope: !938)
!942 = !DILocation(line: 318, column: 7, scope: !938)
!943 = !DILocation(line: 319, column: 23, scope: !944)
!944 = distinct !DILexicalBlock(scope: !933, file: !1, line: 318, column: 56)
!945 = !DILocation(line: 319, column: 26, scope: !944)
!946 = !DILocation(line: 319, column: 4, scope: !944)
!947 = !DILocation(line: 321, column: 32, scope: !944)
!948 = !DILocation(line: 321, column: 39, scope: !944)
!949 = !DILocation(line: 321, column: 4, scope: !944)
!950 = !DILocation(line: 323, column: 27, scope: !944)
!951 = !DILocation(line: 323, column: 31, scope: !944)
!952 = !DILocation(line: 323, column: 38, scope: !944)
!953 = !DILocation(line: 323, column: 4, scope: !944)
!954 = !DILocation(line: 324, column: 4, scope: !944)
!955 = !DILocation(line: 327, column: 31, scope: !927)
!956 = !DILocation(line: 327, column: 58, scope: !927)
!957 = !DILocation(line: 327, column: 39, scope: !927)
!958 = !DILocation(line: 327, column: 43, scope: !927)
!959 = !DILocation(line: 327, column: 3, scope: !927)
!960 = !DILocation(line: 329, column: 34, scope: !927)
!961 = !DILocation(line: 329, column: 38, scope: !927)
!962 = !DILocation(line: 329, column: 45, scope: !927)
!963 = !DILocation(line: 329, column: 11, scope: !927)
!964 = !DILocation(line: 329, column: 3, scope: !927)
!965 = !DILocation(line: 337, column: 14, scope: !966)
!966 = distinct !DILexicalBlock(scope: !316, file: !1, line: 337, column: 6)
!967 = !DILocation(line: 337, column: 6, scope: !966)
!968 = !DILocation(line: 337, column: 34, scope: !966)
!969 = !DILocation(line: 337, column: 6, scope: !316)
!970 = !DILocation(line: 340, column: 26, scope: !971)
!971 = distinct !DILexicalBlock(scope: !966, file: !1, line: 337, column: 40)
!972 = !DILocation(line: 340, column: 30, scope: !971)
!973 = !DILocation(line: 340, column: 37, scope: !971)
!974 = !DILocation(line: 340, column: 3, scope: !971)
!975 = !DILocation(line: 343, column: 22, scope: !971)
!976 = !DILocation(line: 343, column: 24, scope: !971)
!977 = !DILocation(line: 343, column: 41, scope: !971)
!978 = !DILocation(line: 343, column: 12, scope: !971)
!979 = !DILocation(line: 343, column: 10, scope: !971)
!980 = !DILocation(line: 349, column: 7, scope: !981)
!981 = distinct !DILexicalBlock(scope: !971, file: !1, line: 349, column: 7)
!982 = !DILocation(line: 349, column: 14, scope: !981)
!983 = !DILocation(line: 350, column: 7, scope: !981)
!984 = !DILocation(line: 350, column: 10, scope: !985)
!985 = !DILexicalBlockFile(scope: !981, file: !1, discriminator: 1)
!986 = !DILocation(line: 350, column: 17, scope: !985)
!987 = !DILocation(line: 351, column: 7, scope: !981)
!988 = !DILocation(line: 351, column: 19, scope: !985)
!989 = !DILocation(line: 351, column: 28, scope: !985)
!990 = !DILocation(line: 351, column: 32, scope: !985)
!991 = !DILocation(line: 351, column: 26, scope: !985)
!992 = !DILocation(line: 349, column: 7, scope: !993)
!993 = !DILexicalBlockFile(scope: !971, file: !1, discriminator: 1)
!994 = !DILocation(line: 352, column: 23, scope: !995)
!995 = distinct !DILexicalBlock(scope: !981, file: !1, line: 351, column: 55)
!996 = !DILocation(line: 352, column: 26, scope: !995)
!997 = !DILocation(line: 352, column: 4, scope: !995)
!998 = !DILocation(line: 354, column: 4, scope: !995)
!999 = !DILocation(line: 356, column: 29, scope: !971)
!1000 = !DILocation(line: 356, column: 19, scope: !971)
!1001 = !DILocation(line: 357, column: 32, scope: !971)
!1002 = !DILocation(line: 357, column: 3, scope: !971)
!1003 = !DILocation(line: 357, column: 7, scope: !971)
!1004 = !DILocation(line: 357, column: 29, scope: !971)
!1005 = !DILocation(line: 359, column: 26, scope: !971)
!1006 = !DILocation(line: 359, column: 33, scope: !971)
!1007 = !DILocation(line: 359, column: 37, scope: !971)
!1008 = !DILocation(line: 359, column: 3, scope: !971)
!1009 = !DILocation(line: 361, column: 8, scope: !1010)
!1010 = distinct !DILexicalBlock(scope: !971, file: !1, line: 361, column: 7)
!1011 = !DILocation(line: 361, column: 7, scope: !1010)
!1012 = !DILocation(line: 361, column: 7, scope: !971)
!1013 = !DILocation(line: 362, column: 27, scope: !1014)
!1014 = distinct !DILexicalBlock(scope: !1010, file: !1, line: 361, column: 20)
!1015 = !DILocation(line: 362, column: 31, scope: !1014)
!1016 = !DILocation(line: 362, column: 30, scope: !1014)
!1017 = !DILocation(line: 362, column: 4, scope: !1014)
!1018 = !DILocation(line: 363, column: 5, scope: !1014)
!1019 = !DILocation(line: 363, column: 16, scope: !1014)
!1020 = !DILocation(line: 364, column: 3, scope: !1014)
!1021 = !DILocation(line: 367, column: 33, scope: !1022)
!1022 = distinct !DILexicalBlock(scope: !971, file: !1, line: 367, column: 7)
!1023 = !DILocation(line: 367, column: 36, scope: !1022)
!1024 = !DILocation(line: 367, column: 12, scope: !1022)
!1025 = !DILocation(line: 367, column: 10, scope: !1022)
!1026 = !DILocation(line: 367, column: 60, scope: !1022)
!1027 = !DILocation(line: 367, column: 7, scope: !971)
!1028 = !DILocation(line: 368, column: 23, scope: !1029)
!1029 = distinct !DILexicalBlock(scope: !1022, file: !1, line: 367, column: 69)
!1030 = !DILocation(line: 368, column: 26, scope: !1029)
!1031 = !DILocation(line: 368, column: 4, scope: !1029)
!1032 = !DILocation(line: 370, column: 4, scope: !1029)
!1033 = !DILocation(line: 373, column: 22, scope: !971)
!1034 = !DILocation(line: 373, column: 38, scope: !971)
!1035 = !DILocation(line: 373, column: 15, scope: !971)
!1036 = !DILocation(line: 373, column: 5, scope: !971)
!1037 = !DILocation(line: 374, column: 7, scope: !1038)
!1038 = distinct !DILexicalBlock(scope: !971, file: !1, line: 374, column: 7)
!1039 = !DILocation(line: 374, column: 9, scope: !1038)
!1040 = !DILocation(line: 374, column: 7, scope: !971)
!1041 = !DILocation(line: 375, column: 23, scope: !1042)
!1042 = distinct !DILexicalBlock(scope: !1038, file: !1, line: 374, column: 18)
!1043 = !DILocation(line: 375, column: 26, scope: !1042)
!1044 = !DILocation(line: 375, column: 4, scope: !1042)
!1045 = !DILocation(line: 377, column: 4, scope: !1042)
!1046 = !DILocation(line: 379, column: 11, scope: !971)
!1047 = !DILocation(line: 379, column: 14, scope: !971)
!1048 = !DILocation(line: 379, column: 17, scope: !971)
!1049 = !DILocation(line: 379, column: 3, scope: !971)
!1050 = !DILocation(line: 380, column: 5, scope: !971)
!1051 = !DILocation(line: 380, column: 3, scope: !971)
!1052 = !DILocation(line: 380, column: 22, scope: !971)
!1053 = !DILocation(line: 382, column: 26, scope: !971)
!1054 = !DILocation(line: 382, column: 29, scope: !971)
!1055 = !DILocation(line: 382, column: 3, scope: !971)
!1056 = !DILocation(line: 384, column: 31, scope: !971)
!1057 = !DILocation(line: 384, column: 38, scope: !971)
!1058 = !DILocation(line: 384, column: 3, scope: !971)
!1059 = !DILocation(line: 385, column: 8, scope: !971)
!1060 = !DILocation(line: 385, column: 3, scope: !971)
!1061 = !DILocation(line: 386, column: 3, scope: !971)
!1062 = !DILocation(line: 392, column: 13, scope: !1063)
!1063 = distinct !DILexicalBlock(scope: !316, file: !1, line: 392, column: 6)
!1064 = !DILocation(line: 392, column: 6, scope: !1063)
!1065 = !DILocation(line: 392, column: 28, scope: !1063)
!1066 = !DILocation(line: 392, column: 6, scope: !316)
!1067 = !DILocation(line: 393, column: 31, scope: !1068)
!1068 = distinct !DILexicalBlock(scope: !1063, file: !1, line: 392, column: 34)
!1069 = !DILocation(line: 393, column: 3, scope: !1068)
!1070 = !DILocation(line: 395, column: 30, scope: !1068)
!1071 = !DILocation(line: 395, column: 34, scope: !1068)
!1072 = !DILocation(line: 395, column: 41, scope: !1068)
!1073 = !DILocation(line: 395, column: 7, scope: !1068)
!1074 = !DILocation(line: 395, column: 5, scope: !1068)
!1075 = !DILocation(line: 397, column: 30, scope: !1068)
!1076 = !DILocation(line: 397, column: 3, scope: !1068)
!1077 = !DILocation(line: 398, column: 11, scope: !1068)
!1078 = !DILocation(line: 398, column: 3, scope: !1068)
!1079 = !DILocation(line: 404, column: 13, scope: !1080)
!1080 = distinct !DILexicalBlock(scope: !316, file: !1, line: 404, column: 6)
!1081 = !DILocation(line: 404, column: 6, scope: !1080)
!1082 = !DILocation(line: 404, column: 36, scope: !1080)
!1083 = !DILocation(line: 404, column: 6, scope: !316)
!1084 = !DILocation(line: 405, column: 31, scope: !1085)
!1085 = distinct !DILexicalBlock(scope: !1080, file: !1, line: 404, column: 42)
!1086 = !DILocation(line: 405, column: 38, scope: !1085)
!1087 = !DILocation(line: 405, column: 3, scope: !1085)
!1088 = !DILocation(line: 407, column: 34, scope: !1085)
!1089 = !DILocation(line: 407, column: 38, scope: !1085)
!1090 = !DILocation(line: 407, column: 45, scope: !1085)
!1091 = !DILocation(line: 407, column: 11, scope: !1085)
!1092 = !DILocation(line: 407, column: 3, scope: !1085)
!1093 = !DILocation(line: 415, column: 30, scope: !316)
!1094 = !DILocation(line: 415, column: 37, scope: !316)
!1095 = !DILocation(line: 415, column: 2, scope: !316)
!1096 = !DILocation(line: 416, column: 33, scope: !316)
!1097 = !DILocation(line: 416, column: 37, scope: !316)
!1098 = !DILocation(line: 416, column: 44, scope: !316)
!1099 = !DILocation(line: 416, column: 10, scope: !316)
!1100 = !DILocation(line: 416, column: 2, scope: !316)
!1101 = !DILocation(line: 417, column: 1, scope: !316)
!1102 = !DILocalVariable(name: "ar", arg: 1, scope: !319, file: !1, line: 456, type: !291)
!1103 = !DILocation(line: 456, column: 35, scope: !319)
!1104 = !DILocalVariable(name: "entry", arg: 2, scope: !319, file: !1, line: 456, type: !30)
!1105 = !DILocation(line: 456, column: 61, scope: !319)
!1106 = !DILocalVariable(name: "h", arg: 3, scope: !319, file: !1, line: 457, type: !80)
!1107 = !DILocation(line: 457, column: 17, scope: !319)
!1108 = !DILocalVariable(name: "n", scope: !319, file: !1, line: 459, type: !325)
!1109 = !DILocation(line: 459, column: 11, scope: !319)
!1110 = !DILocation(line: 462, column: 26, scope: !319)
!1111 = !DILocation(line: 463, column: 24, scope: !319)
!1112 = !DILocation(line: 463, column: 26, scope: !319)
!1113 = !DILocation(line: 463, column: 14, scope: !319)
!1114 = !DILocation(line: 462, column: 2, scope: !319)
!1115 = !DILocation(line: 464, column: 24, scope: !319)
!1116 = !DILocation(line: 465, column: 23, scope: !319)
!1117 = !DILocation(line: 465, column: 25, scope: !319)
!1118 = !DILocation(line: 465, column: 13, scope: !319)
!1119 = !DILocation(line: 465, column: 6, scope: !319)
!1120 = !DILocation(line: 464, column: 2, scope: !319)
!1121 = !DILocation(line: 466, column: 24, scope: !319)
!1122 = !DILocation(line: 467, column: 23, scope: !319)
!1123 = !DILocation(line: 467, column: 25, scope: !319)
!1124 = !DILocation(line: 467, column: 13, scope: !319)
!1125 = !DILocation(line: 467, column: 6, scope: !319)
!1126 = !DILocation(line: 466, column: 2, scope: !319)
!1127 = !DILocation(line: 468, column: 25, scope: !319)
!1128 = !DILocation(line: 469, column: 23, scope: !319)
!1129 = !DILocation(line: 469, column: 25, scope: !319)
!1130 = !DILocation(line: 469, column: 14, scope: !319)
!1131 = !DILocation(line: 469, column: 6, scope: !319)
!1132 = !DILocation(line: 468, column: 2, scope: !319)
!1133 = !DILocation(line: 470, column: 16, scope: !319)
!1134 = !DILocation(line: 470, column: 18, scope: !319)
!1135 = !DILocation(line: 470, column: 6, scope: !319)
!1136 = !DILocation(line: 470, column: 4, scope: !319)
!1137 = !DILocation(line: 472, column: 2, scope: !319)
!1138 = !DILocation(line: 472, column: 6, scope: !319)
!1139 = !DILocation(line: 472, column: 19, scope: !319)
!1140 = !DILocation(line: 473, column: 22, scope: !319)
!1141 = !DILocation(line: 473, column: 24, scope: !319)
!1142 = !DILocation(line: 473, column: 2, scope: !319)
!1143 = !DILocation(line: 473, column: 6, scope: !319)
!1144 = !DILocation(line: 473, column: 20, scope: !319)
!1145 = !DILocation(line: 474, column: 25, scope: !319)
!1146 = !DILocation(line: 474, column: 32, scope: !319)
!1147 = !DILocation(line: 474, column: 2, scope: !319)
!1148 = !DILocation(line: 475, column: 30, scope: !319)
!1149 = !DILocation(line: 475, column: 2, scope: !319)
!1150 = !DILocation(line: 475, column: 6, scope: !319)
!1151 = !DILocation(line: 475, column: 28, scope: !319)
!1152 = !DILocation(line: 476, column: 2, scope: !319)
!1153 = !DILocalVariable(name: "p", arg: 1, scope: !326, file: !1, line: 615, type: !80)
!1154 = !DILocation(line: 615, column: 23, scope: !326)
!1155 = !DILocalVariable(name: "char_cnt", arg: 2, scope: !326, file: !1, line: 615, type: !13)
!1156 = !DILocation(line: 615, column: 35, scope: !326)
!1157 = !DILocalVariable(name: "l", scope: !326, file: !1, line: 617, type: !325)
!1158 = !DILocation(line: 617, column: 11, scope: !326)
!1159 = !DILocalVariable(name: "limit", scope: !326, file: !1, line: 617, type: !325)
!1160 = !DILocation(line: 617, column: 14, scope: !326)
!1161 = !DILocalVariable(name: "last_digit_limit", scope: !326, file: !1, line: 617, type: !325)
!1162 = !DILocation(line: 617, column: 21, scope: !326)
!1163 = !DILocalVariable(name: "base", scope: !326, file: !1, line: 618, type: !13)
!1164 = !DILocation(line: 618, column: 15, scope: !326)
!1165 = !DILocalVariable(name: "digit", scope: !326, file: !1, line: 618, type: !13)
!1166 = !DILocation(line: 618, column: 21, scope: !326)
!1167 = !DILocation(line: 620, column: 7, scope: !326)
!1168 = !DILocation(line: 621, column: 23, scope: !326)
!1169 = !DILocation(line: 621, column: 21, scope: !326)
!1170 = !DILocation(line: 621, column: 8, scope: !326)
!1171 = !DILocation(line: 622, column: 34, scope: !326)
!1172 = !DILocation(line: 622, column: 32, scope: !326)
!1173 = !DILocation(line: 622, column: 19, scope: !326)
!1174 = !DILocation(line: 624, column: 2, scope: !326)
!1175 = !DILocation(line: 624, column: 11, scope: !1176)
!1176 = !DILexicalBlockFile(scope: !326, file: !1, discriminator: 1)
!1177 = !DILocation(line: 624, column: 10, scope: !1176)
!1178 = !DILocation(line: 624, column: 13, scope: !1176)
!1179 = !DILocation(line: 624, column: 20, scope: !1176)
!1180 = !DILocation(line: 624, column: 24, scope: !1181)
!1181 = !DILexicalBlockFile(scope: !326, file: !1, discriminator: 2)
!1182 = !DILocation(line: 624, column: 23, scope: !1181)
!1183 = !DILocation(line: 624, column: 26, scope: !1181)
!1184 = !DILocation(line: 624, column: 35, scope: !1181)
!1185 = !DILocation(line: 624, column: 46, scope: !1186)
!1186 = !DILexicalBlockFile(scope: !326, file: !1, discriminator: 3)
!1187 = !DILocation(line: 624, column: 49, scope: !1186)
!1188 = !DILocation(line: 624, column: 2, scope: !1189)
!1189 = !DILexicalBlockFile(scope: !326, file: !1, discriminator: 4)
!1190 = !DILocation(line: 625, column: 4, scope: !326)
!1191 = !DILocation(line: 624, column: 2, scope: !1192)
!1192 = !DILexicalBlockFile(scope: !326, file: !1, discriminator: 5)
!1193 = !DILocation(line: 626, column: 4, scope: !326)
!1194 = !DILocation(line: 627, column: 11, scope: !326)
!1195 = !DILocation(line: 627, column: 10, scope: !326)
!1196 = !DILocation(line: 627, column: 13, scope: !326)
!1197 = !DILocation(line: 627, column: 8, scope: !326)
!1198 = !DILocation(line: 628, column: 2, scope: !326)
!1199 = !DILocation(line: 628, column: 10, scope: !1176)
!1200 = !DILocation(line: 628, column: 9, scope: !1176)
!1201 = !DILocation(line: 628, column: 12, scope: !1176)
!1202 = !DILocation(line: 628, column: 19, scope: !1176)
!1203 = !DILocation(line: 628, column: 22, scope: !1181)
!1204 = !DILocation(line: 628, column: 30, scope: !1181)
!1205 = !DILocation(line: 628, column: 28, scope: !1181)
!1206 = !DILocation(line: 628, column: 36, scope: !1181)
!1207 = !DILocation(line: 628, column: 47, scope: !1186)
!1208 = !DILocation(line: 628, column: 50, scope: !1186)
!1209 = !DILocation(line: 628, column: 2, scope: !1189)
!1210 = !DILocation(line: 629, column: 7, scope: !1211)
!1211 = distinct !DILexicalBlock(scope: !1212, file: !1, line: 629, column: 7)
!1212 = distinct !DILexicalBlock(scope: !326, file: !1, line: 628, column: 55)
!1213 = !DILocation(line: 629, column: 11, scope: !1211)
!1214 = !DILocation(line: 629, column: 9, scope: !1211)
!1215 = !DILocation(line: 629, column: 17, scope: !1211)
!1216 = !DILocation(line: 629, column: 21, scope: !1217)
!1217 = !DILexicalBlockFile(scope: !1211, file: !1, discriminator: 1)
!1218 = !DILocation(line: 629, column: 26, scope: !1217)
!1219 = !DILocation(line: 629, column: 23, scope: !1217)
!1220 = !DILocation(line: 629, column: 32, scope: !1217)
!1221 = !DILocation(line: 629, column: 35, scope: !1222)
!1222 = !DILexicalBlockFile(scope: !1211, file: !1, discriminator: 2)
!1223 = !DILocation(line: 629, column: 43, scope: !1222)
!1224 = !DILocation(line: 629, column: 41, scope: !1222)
!1225 = !DILocation(line: 629, column: 7, scope: !1222)
!1226 = !DILocation(line: 630, column: 6, scope: !1227)
!1227 = distinct !DILexicalBlock(scope: !1211, file: !1, line: 629, column: 62)
!1228 = !DILocation(line: 631, column: 4, scope: !1227)
!1229 = !DILocation(line: 633, column: 8, scope: !1212)
!1230 = !DILocation(line: 633, column: 12, scope: !1212)
!1231 = !DILocation(line: 633, column: 10, scope: !1212)
!1232 = !DILocation(line: 633, column: 20, scope: !1212)
!1233 = !DILocation(line: 633, column: 18, scope: !1212)
!1234 = !DILocation(line: 633, column: 5, scope: !1212)
!1235 = !DILocation(line: 634, column: 12, scope: !1212)
!1236 = !DILocation(line: 634, column: 11, scope: !1212)
!1237 = !DILocation(line: 634, column: 16, scope: !1212)
!1238 = !DILocation(line: 634, column: 9, scope: !1212)
!1239 = !DILocation(line: 628, column: 2, scope: !1192)
!1240 = !DILocation(line: 636, column: 10, scope: !326)
!1241 = !DILocation(line: 636, column: 2, scope: !326)
!1242 = !DILocalVariable(name: "a", arg: 1, scope: !327, file: !1, line: 551, type: !4)
!1243 = !DILocation(line: 551, column: 50, scope: !327)
!1244 = !DILocalVariable(name: "ar", scope: !327, file: !1, line: 553, type: !291)
!1245 = !DILocation(line: 553, column: 13, scope: !327)
!1246 = !DILocalVariable(name: "p", scope: !327, file: !1, line: 554, type: !95)
!1247 = !DILocation(line: 554, column: 8, scope: !327)
!1248 = !DILocalVariable(name: "size", scope: !327, file: !1, line: 555, type: !45)
!1249 = !DILocation(line: 555, column: 9, scope: !327)
!1250 = !DILocation(line: 557, column: 20, scope: !327)
!1251 = !DILocation(line: 557, column: 23, scope: !327)
!1252 = !DILocation(line: 557, column: 31, scope: !327)
!1253 = !DILocation(line: 557, column: 7, scope: !327)
!1254 = !DILocation(line: 557, column: 5, scope: !327)
!1255 = !DILocation(line: 558, column: 9, scope: !327)
!1256 = !DILocation(line: 558, column: 13, scope: !327)
!1257 = !DILocation(line: 558, column: 7, scope: !327)
!1258 = !DILocation(line: 560, column: 11, scope: !1259)
!1259 = distinct !DILexicalBlock(scope: !327, file: !1, line: 560, column: 2)
!1260 = !DILocation(line: 560, column: 15, scope: !1259)
!1261 = !DILocation(line: 560, column: 9, scope: !1259)
!1262 = !DILocation(line: 560, column: 7, scope: !1259)
!1263 = !DILocation(line: 560, column: 23, scope: !1264)
!1264 = !DILexicalBlockFile(scope: !1265, file: !1, discriminator: 1)
!1265 = distinct !DILexicalBlock(scope: !1259, file: !1, line: 560, column: 2)
!1266 = !DILocation(line: 560, column: 27, scope: !1264)
!1267 = !DILocation(line: 560, column: 31, scope: !1264)
!1268 = !DILocation(line: 560, column: 40, scope: !1264)
!1269 = !DILocation(line: 560, column: 38, scope: !1264)
!1270 = !DILocation(line: 560, column: 45, scope: !1264)
!1271 = !DILocation(line: 560, column: 25, scope: !1264)
!1272 = !DILocation(line: 560, column: 2, scope: !1264)
!1273 = !DILocation(line: 561, column: 8, scope: !1274)
!1274 = distinct !DILexicalBlock(scope: !1275, file: !1, line: 561, column: 7)
!1275 = distinct !DILexicalBlock(scope: !1265, file: !1, line: 560, column: 55)
!1276 = !DILocation(line: 561, column: 7, scope: !1274)
!1277 = !DILocation(line: 561, column: 10, scope: !1274)
!1278 = !DILocation(line: 561, column: 7, scope: !1275)
!1279 = !DILocation(line: 562, column: 6, scope: !1280)
!1280 = distinct !DILexicalBlock(scope: !1274, file: !1, line: 561, column: 18)
!1281 = !DILocation(line: 562, column: 9, scope: !1280)
!1282 = !DILocation(line: 563, column: 9, scope: !1283)
!1283 = distinct !DILexicalBlock(scope: !1280, file: !1, line: 563, column: 8)
!1284 = !DILocation(line: 563, column: 8, scope: !1283)
!1285 = !DILocation(line: 563, column: 11, scope: !1283)
!1286 = !DILocation(line: 563, column: 8, scope: !1280)
!1287 = !DILocation(line: 564, column: 5, scope: !1283)
!1288 = !DILocation(line: 565, column: 5, scope: !1280)
!1289 = !DILocation(line: 565, column: 7, scope: !1280)
!1290 = !DILocation(line: 566, column: 3, scope: !1280)
!1291 = !DILocation(line: 567, column: 2, scope: !1275)
!1292 = !DILocation(line: 560, column: 50, scope: !1293)
!1293 = !DILexicalBlockFile(scope: !1265, file: !1, discriminator: 2)
!1294 = !DILocation(line: 560, column: 2, scope: !1293)
!1295 = !DILocation(line: 572, column: 6, scope: !1296)
!1296 = distinct !DILexicalBlock(scope: !327, file: !1, line: 572, column: 6)
!1297 = !DILocation(line: 572, column: 11, scope: !1296)
!1298 = !DILocation(line: 572, column: 15, scope: !1296)
!1299 = !DILocation(line: 572, column: 24, scope: !1296)
!1300 = !DILocation(line: 572, column: 22, scope: !1296)
!1301 = !DILocation(line: 572, column: 8, scope: !1296)
!1302 = !DILocation(line: 572, column: 29, scope: !1296)
!1303 = !DILocation(line: 572, column: 33, scope: !1304)
!1304 = !DILexicalBlockFile(scope: !1296, file: !1, discriminator: 1)
!1305 = !DILocation(line: 572, column: 32, scope: !1304)
!1306 = !DILocation(line: 572, column: 35, scope: !1304)
!1307 = !DILocation(line: 572, column: 43, scope: !1304)
!1308 = !DILocation(line: 572, column: 47, scope: !1309)
!1309 = !DILexicalBlockFile(scope: !1296, file: !1, discriminator: 2)
!1310 = !DILocation(line: 572, column: 46, scope: !1309)
!1311 = !DILocation(line: 572, column: 49, scope: !1309)
!1312 = !DILocation(line: 572, column: 6, scope: !1309)
!1313 = !DILocation(line: 573, column: 3, scope: !1296)
!1314 = !DILocation(line: 576, column: 13, scope: !327)
!1315 = !DILocation(line: 576, column: 18, scope: !327)
!1316 = !DILocation(line: 576, column: 2, scope: !327)
!1317 = !DILocation(line: 576, column: 6, scope: !327)
!1318 = !DILocation(line: 576, column: 23, scope: !327)
!1319 = !DILocation(line: 578, column: 2, scope: !327)
!1320 = !DILocation(line: 581, column: 21, scope: !327)
!1321 = !DILocation(line: 581, column: 24, scope: !327)
!1322 = !DILocation(line: 581, column: 2, scope: !327)
!1323 = !DILocation(line: 583, column: 7, scope: !327)
!1324 = !DILocation(line: 583, column: 11, scope: !327)
!1325 = !DILocation(line: 583, column: 2, scope: !327)
!1326 = !DILocation(line: 584, column: 2, scope: !327)
!1327 = !DILocation(line: 584, column: 6, scope: !327)
!1328 = !DILocation(line: 584, column: 13, scope: !327)
!1329 = !DILocation(line: 585, column: 2, scope: !327)
!1330 = !DILocation(line: 586, column: 1, scope: !327)
!1331 = !DILocalVariable(name: "p", arg: 1, scope: !322, file: !1, line: 589, type: !80)
!1332 = !DILocation(line: 589, column: 22, scope: !322)
!1333 = !DILocalVariable(name: "char_cnt", arg: 2, scope: !322, file: !1, line: 589, type: !13)
!1334 = !DILocation(line: 589, column: 34, scope: !322)
!1335 = !DILocalVariable(name: "l", scope: !322, file: !1, line: 591, type: !325)
!1336 = !DILocation(line: 591, column: 11, scope: !322)
!1337 = !DILocalVariable(name: "limit", scope: !322, file: !1, line: 591, type: !325)
!1338 = !DILocation(line: 591, column: 14, scope: !322)
!1339 = !DILocalVariable(name: "last_digit_limit", scope: !322, file: !1, line: 591, type: !325)
!1340 = !DILocation(line: 591, column: 21, scope: !322)
!1341 = !DILocalVariable(name: "digit", scope: !322, file: !1, line: 592, type: !13)
!1342 = !DILocation(line: 592, column: 15, scope: !322)
!1343 = !DILocalVariable(name: "base", scope: !322, file: !1, line: 592, type: !13)
!1344 = !DILocation(line: 592, column: 22, scope: !322)
!1345 = !DILocation(line: 594, column: 7, scope: !322)
!1346 = !DILocation(line: 595, column: 23, scope: !322)
!1347 = !DILocation(line: 595, column: 21, scope: !322)
!1348 = !DILocation(line: 595, column: 8, scope: !322)
!1349 = !DILocation(line: 596, column: 34, scope: !322)
!1350 = !DILocation(line: 596, column: 32, scope: !322)
!1351 = !DILocation(line: 596, column: 19, scope: !322)
!1352 = !DILocation(line: 598, column: 2, scope: !322)
!1353 = !DILocation(line: 598, column: 11, scope: !1354)
!1354 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 1)
!1355 = !DILocation(line: 598, column: 10, scope: !1354)
!1356 = !DILocation(line: 598, column: 13, scope: !1354)
!1357 = !DILocation(line: 598, column: 20, scope: !1354)
!1358 = !DILocation(line: 598, column: 24, scope: !1359)
!1359 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 2)
!1360 = !DILocation(line: 598, column: 23, scope: !1359)
!1361 = !DILocation(line: 598, column: 26, scope: !1359)
!1362 = !DILocation(line: 598, column: 35, scope: !1359)
!1363 = !DILocation(line: 598, column: 46, scope: !1364)
!1364 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 3)
!1365 = !DILocation(line: 598, column: 49, scope: !1364)
!1366 = !DILocation(line: 598, column: 2, scope: !1367)
!1367 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 4)
!1368 = !DILocation(line: 599, column: 4, scope: !322)
!1369 = !DILocation(line: 598, column: 2, scope: !1370)
!1370 = !DILexicalBlockFile(scope: !322, file: !1, discriminator: 5)
!1371 = !DILocation(line: 601, column: 4, scope: !322)
!1372 = !DILocation(line: 602, column: 11, scope: !322)
!1373 = !DILocation(line: 602, column: 10, scope: !322)
!1374 = !DILocation(line: 602, column: 13, scope: !322)
!1375 = !DILocation(line: 602, column: 8, scope: !322)
!1376 = !DILocation(line: 603, column: 2, scope: !322)
!1377 = !DILocation(line: 603, column: 10, scope: !1354)
!1378 = !DILocation(line: 603, column: 9, scope: !1354)
!1379 = !DILocation(line: 603, column: 12, scope: !1354)
!1380 = !DILocation(line: 603, column: 19, scope: !1354)
!1381 = !DILocation(line: 603, column: 22, scope: !1359)
!1382 = !DILocation(line: 603, column: 30, scope: !1359)
!1383 = !DILocation(line: 603, column: 28, scope: !1359)
!1384 = !DILocation(line: 603, column: 36, scope: !1359)
!1385 = !DILocation(line: 603, column: 47, scope: !1364)
!1386 = !DILocation(line: 603, column: 50, scope: !1364)
!1387 = !DILocation(line: 603, column: 2, scope: !1367)
!1388 = !DILocation(line: 604, column: 7, scope: !1389)
!1389 = distinct !DILexicalBlock(scope: !1390, file: !1, line: 604, column: 7)
!1390 = distinct !DILexicalBlock(scope: !322, file: !1, line: 603, column: 55)
!1391 = !DILocation(line: 604, column: 9, scope: !1389)
!1392 = !DILocation(line: 604, column: 8, scope: !1389)
!1393 = !DILocation(line: 604, column: 15, scope: !1389)
!1394 = !DILocation(line: 604, column: 19, scope: !1395)
!1395 = !DILexicalBlockFile(scope: !1389, file: !1, discriminator: 1)
!1396 = !DILocation(line: 604, column: 24, scope: !1395)
!1397 = !DILocation(line: 604, column: 21, scope: !1395)
!1398 = !DILocation(line: 604, column: 30, scope: !1395)
!1399 = !DILocation(line: 604, column: 33, scope: !1400)
!1400 = !DILexicalBlockFile(scope: !1389, file: !1, discriminator: 2)
!1401 = !DILocation(line: 604, column: 41, scope: !1400)
!1402 = !DILocation(line: 604, column: 39, scope: !1400)
!1403 = !DILocation(line: 604, column: 7, scope: !1400)
!1404 = !DILocation(line: 605, column: 6, scope: !1405)
!1405 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 604, column: 60)
!1406 = !DILocation(line: 606, column: 4, scope: !1405)
!1407 = !DILocation(line: 608, column: 8, scope: !1390)
!1408 = !DILocation(line: 608, column: 12, scope: !1390)
!1409 = !DILocation(line: 608, column: 10, scope: !1390)
!1410 = !DILocation(line: 608, column: 20, scope: !1390)
!1411 = !DILocation(line: 608, column: 18, scope: !1390)
!1412 = !DILocation(line: 608, column: 5, scope: !1390)
!1413 = !DILocation(line: 609, column: 12, scope: !1390)
!1414 = !DILocation(line: 609, column: 11, scope: !1390)
!1415 = !DILocation(line: 609, column: 16, scope: !1390)
!1416 = !DILocation(line: 609, column: 9, scope: !1390)
!1417 = !DILocation(line: 603, column: 2, scope: !1370)
!1418 = !DILocation(line: 611, column: 10, scope: !322)
!1419 = !DILocation(line: 611, column: 2, scope: !322)
