; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_warc.c'
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
%struct.warc_s = type { i64, i64, i64, %struct.warc_strbuf_t, i32, %struct.archive_string }
%struct.warc_strbuf_t = type { i64, i8* }
%struct.warc_string_t = type { i64, i8* }
%struct.tm = type { i32, i32, i32, i32, i32, i32, i32, i32, i32, i64, i8* }

@.str = private unnamed_addr constant [33 x i8] c"archive_read_support_format_warc\00", align 1
@.str.1 = private unnamed_addr constant [25 x i8] c"Can't allocate warc data\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"warc\00", align 1
@_warc_rdver.magic = internal constant [6 x i8] c"WARC/\00", align 1
@.str.3 = private unnamed_addr constant [3 x i8] c"\0D\0A\00", align 1
@.str.4 = private unnamed_addr constant [18 x i8] c"Bad record header\00", align 1
@.str.5 = private unnamed_addr constant [23 x i8] c"Invalid record version\00", align 1
@.str.6 = private unnamed_addr constant [34 x i8] c"Unsupported record version: %u.%u\00", align 1
@.str.7 = private unnamed_addr constant [19 x i8] c"Bad content length\00", align 1
@.str.8 = private unnamed_addr constant [16 x i8] c"Bad record time\00", align 1
@.str.9 = private unnamed_addr constant [11 x i8] c"WARC/%u.%u\00", align 1
@_warc_find_eoh._marker = internal constant [5 x i8] c"\0D\0A\0D\0A\00", align 1
@_warc_rdlen._key = internal constant [18 x i8] c"\0D\0AContent-Length:\00", align 16
@_warc_find_eol._marker = internal constant [3 x i8] c"\0D\0A\00", align 1
@_warc_rdrtm._key = internal constant [13 x i8] c"\0D\0AWARC-Date:\00", align 1
@_warc_rdtyp._key = internal constant [13 x i8] c"\0D\0AWARC-Type:\00", align 1
@.str.10 = private unnamed_addr constant [9 x i8] c"resource\00", align 1
@.str.11 = private unnamed_addr constant [9 x i8] c"response\00", align 1
@_warc_rduri._key = internal constant [19 x i8] c"\0D\0AWARC-Target-URI:\00", align 16
@.str.12 = private unnamed_addr constant [4 x i8] c"://\00", align 1
@.str.13 = private unnamed_addr constant [5 x i8] c"file\00", align 1
@.str.14 = private unnamed_addr constant [5 x i8] c"http\00", align 1
@.str.15 = private unnamed_addr constant [4 x i8] c"ftp\00", align 1
@_warc_rdmtm._key = internal constant [17 x i8] c"\0D\0ALast-Modified:\00", align 16

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_format_warc(%struct.archive* %_a) #0 !dbg !326 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %w = alloca %struct.warc_s*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !421, metadata !422), !dbg !423
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !424, metadata !422), !dbg !425
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !426
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !427
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !425
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !428, metadata !422), !dbg !443
  call void @llvm.dbg.declare(metadata i32* %r, metadata !444, metadata !422), !dbg !445
  br label %do.body, !dbg !446

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !447, metadata !422), !dbg !449
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !450
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str, i32 0, i32 0)), !dbg !450
  store i32 %call, i32* %magic_test, align 4, !dbg !450
  %3 = load i32, i32* %magic_test, align 4, !dbg !450
  %cmp = icmp eq i32 %3, -30, !dbg !450
  br i1 %cmp, label %if.then, label %if.end, !dbg !450

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !452
  br label %return, !dbg !452

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !455

do.end:                                           ; preds = %if.end
  %call1 = call noalias i8* @calloc(i64 1, i64 72) #7, !dbg !457
  %4 = bitcast i8* %call1 to %struct.warc_s*, !dbg !457
  store %struct.warc_s* %4, %struct.warc_s** %w, align 8, !dbg !459
  %cmp2 = icmp eq %struct.warc_s* %4, null, !dbg !460
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !461

if.then3:                                         ; preds = %do.end
  %5 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !462
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 0, !dbg !464
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.1, i32 0, i32 0)), !dbg !465
  store i32 -30, i32* %retval, align 4, !dbg !466
  br label %return, !dbg !466

if.end4:                                          ; preds = %do.end
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !467
  %7 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !468
  %8 = bitcast %struct.warc_s* %7 to i8*, !dbg !468
  %call5 = call i32 @__archive_read_register_format(%struct.archive_read* %6, i8* %8, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i32 (%struct.archive_read*, i32)* @_warc_bid, i32 (%struct.archive_read*, i8*, i8*)* null, i32 (%struct.archive_read*, %struct.archive_entry*)* @_warc_rdhdr, i32 (%struct.archive_read*, i8**, i64*, i64*)* @_warc_read, i32 (%struct.archive_read*)* @_warc_skip, i64 (%struct.archive_read*, i64, i32)* null, i32 (%struct.archive_read*)* @_warc_cleanup, i32 (%struct.archive_read*)* null, i32 (%struct.archive_read*)* null), !dbg !469
  store i32 %call5, i32* %r, align 4, !dbg !470
  %9 = load i32, i32* %r, align 4, !dbg !471
  %cmp6 = icmp ne i32 %9, 0, !dbg !473
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !474

if.then7:                                         ; preds = %if.end4
  %10 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !475
  %11 = bitcast %struct.warc_s* %10 to i8*, !dbg !475
  call void @free(i8* %11) #7, !dbg !477
  %12 = load i32, i32* %r, align 4, !dbg !478
  store i32 %12, i32* %retval, align 4, !dbg !479
  br label %return, !dbg !479

if.end8:                                          ; preds = %if.end4
  store i32 0, i32* %retval, align 4, !dbg !480
  br label %return, !dbg !480

return:                                           ; preds = %if.end8, %if.then7, %if.then3, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !481
  ret i32 %13, !dbg !481
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare i32 @__archive_read_register_format(%struct.archive_read*, i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @_warc_bid(%struct.archive_read* %a, i32 %best_bid) #0 !dbg !329 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %best_bid.addr = alloca i32, align 4
  %hdr = alloca i8*, align 8
  %nrd = alloca i64, align 8
  %ver = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !482, metadata !422), !dbg !483
  store i32 %best_bid, i32* %best_bid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %best_bid.addr, metadata !484, metadata !422), !dbg !485
  call void @llvm.dbg.declare(metadata i8** %hdr, metadata !486, metadata !422), !dbg !487
  call void @llvm.dbg.declare(metadata i64* %nrd, metadata !488, metadata !422), !dbg !489
  call void @llvm.dbg.declare(metadata i32* %ver, metadata !490, metadata !422), !dbg !491
  %0 = load i32, i32* %best_bid.addr, align 4, !dbg !492
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !493
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %1, i64 12, i64* %nrd), !dbg !495
  store i8* %call, i8** %hdr, align 8, !dbg !496
  %cmp = icmp eq i8* %call, null, !dbg !497
  br i1 %cmp, label %if.then, label %if.else, !dbg !498

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !499
  br label %return, !dbg !499

if.else:                                          ; preds = %entry
  %2 = load i64, i64* %nrd, align 8, !dbg !501
  %cmp1 = icmp slt i64 %2, 12, !dbg !503
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !504

if.then2:                                         ; preds = %if.else
  store i32 -1, i32* %retval, align 4, !dbg !505
  br label %return, !dbg !505

if.end:                                           ; preds = %if.else
  br label %if.end3

if.end3:                                          ; preds = %if.end
  %3 = load i8*, i8** %hdr, align 8, !dbg !507
  %4 = load i64, i64* %nrd, align 8, !dbg !508
  %call4 = call i32 @_warc_rdver(i8* %3, i64 %4), !dbg !509
  store i32 %call4, i32* %ver, align 4, !dbg !510
  %5 = load i32, i32* %ver, align 4, !dbg !511
  %cmp5 = icmp ult i32 %5, 1200, !dbg !513
  br i1 %cmp5, label %if.then7, label %lor.lhs.false, !dbg !514

lor.lhs.false:                                    ; preds = %if.end3
  %6 = load i32, i32* %ver, align 4, !dbg !515
  %cmp6 = icmp ugt i32 %6, 10000, !dbg !517
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !518

if.then7:                                         ; preds = %lor.lhs.false, %if.end3
  store i32 -1, i32* %retval, align 4, !dbg !519
  br label %return, !dbg !519

if.end8:                                          ; preds = %lor.lhs.false
  store i32 64, i32* %retval, align 4, !dbg !521
  br label %return, !dbg !521

return:                                           ; preds = %if.end8, %if.then7, %if.then2, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !522
  ret i32 %7, !dbg !522
}

; Function Attrs: nounwind uwtable
define internal i32 @_warc_rdhdr(%struct.archive_read* %a, %struct.archive_entry* %entry1) #0 !dbg !333 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %w = alloca %struct.warc_s*, align 8
  %ver = alloca i32, align 4
  %buf = alloca i8*, align 8
  %nrd = alloca i64, align 8
  %eoh = alloca i8*, align 8
  %fnam = alloca %struct.warc_string_t, align 8
  %ftyp = alloca i32, align 4
  %cntlen = alloca i64, align 8
  %rtime = alloca i64, align 8
  %mtime = alloca i64, align 8
  %coerce = alloca %struct.warc_string_t, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !523, metadata !422), !dbg !524
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !525, metadata !422), !dbg !526
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !527, metadata !422), !dbg !528
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !529
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !530
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !530
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !531
  %2 = load i8*, i8** %data, align 8, !dbg !531
  %3 = bitcast i8* %2 to %struct.warc_s*, !dbg !529
  store %struct.warc_s* %3, %struct.warc_s** %w, align 8, !dbg !528
  call void @llvm.dbg.declare(metadata i32* %ver, metadata !532, metadata !422), !dbg !533
  call void @llvm.dbg.declare(metadata i8** %buf, metadata !534, metadata !422), !dbg !535
  call void @llvm.dbg.declare(metadata i64* %nrd, metadata !536, metadata !422), !dbg !537
  call void @llvm.dbg.declare(metadata i8** %eoh, metadata !538, metadata !422), !dbg !539
  call void @llvm.dbg.declare(metadata %struct.warc_string_t* %fnam, metadata !540, metadata !422), !dbg !541
  call void @llvm.dbg.declare(metadata i32* %ftyp, metadata !542, metadata !422), !dbg !544
  call void @llvm.dbg.declare(metadata i64* %cntlen, metadata !545, metadata !422), !dbg !546
  call void @llvm.dbg.declare(metadata i64* %rtime, metadata !547, metadata !422), !dbg !548
  call void @llvm.dbg.declare(metadata i64* %mtime, metadata !549, metadata !422), !dbg !550
  br label %start_over, !dbg !551

start_over:                                       ; preds = %sw.default114, %entry
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !552
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %4, i64 12, i64* %nrd), !dbg !553
  store i8* %call, i8** %buf, align 8, !dbg !554
  %5 = load i64, i64* %nrd, align 8, !dbg !555
  %cmp = icmp slt i64 %5, 0, !dbg !557
  br i1 %cmp, label %if.then, label %if.else, !dbg !558

if.then:                                          ; preds = %start_over
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !559
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !561
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.4, i32 0, i32 0)), !dbg !562
  store i32 -30, i32* %retval, align 4, !dbg !563
  br label %return, !dbg !563

if.else:                                          ; preds = %start_over
  %7 = load i8*, i8** %buf, align 8, !dbg !564
  %cmp2 = icmp eq i8* %7, null, !dbg !566
  br i1 %cmp2, label %if.then3, label %if.end, !dbg !567

if.then3:                                         ; preds = %if.else
  store i32 1, i32* %retval, align 4, !dbg !568
  br label %return, !dbg !568

if.end:                                           ; preds = %if.else
  br label %if.end4

if.end4:                                          ; preds = %if.end
  %8 = load i8*, i8** %buf, align 8, !dbg !570
  %9 = load i64, i64* %nrd, align 8, !dbg !571
  %call5 = call i8* @_warc_find_eoh(i8* %8, i64 %9), !dbg !572
  store i8* %call5, i8** %eoh, align 8, !dbg !573
  %10 = load i8*, i8** %eoh, align 8, !dbg !574
  %cmp6 = icmp eq i8* %10, null, !dbg !576
  br i1 %cmp6, label %if.then7, label %if.end9, !dbg !577

if.then7:                                         ; preds = %if.end4
  %11 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !578
  %archive8 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 0, !dbg !580
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive8, i32 -1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.4, i32 0, i32 0)), !dbg !581
  store i32 -30, i32* %retval, align 4, !dbg !582
  br label %return, !dbg !582

if.end9:                                          ; preds = %if.end4
  %12 = load i8*, i8** %buf, align 8, !dbg !583
  %13 = load i8*, i8** %eoh, align 8, !dbg !584
  %14 = load i8*, i8** %buf, align 8, !dbg !585
  %sub.ptr.lhs.cast = ptrtoint i8* %13 to i64, !dbg !586
  %sub.ptr.rhs.cast = ptrtoint i8* %14 to i64, !dbg !586
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !586
  %call10 = call i32 @_warc_rdver(i8* %12, i64 %sub.ptr.sub), !dbg !587
  store i32 %call10, i32* %ver, align 4, !dbg !588
  %15 = load i32, i32* %ver, align 4, !dbg !589
  %cmp11 = icmp eq i32 %15, 0, !dbg !591
  br i1 %cmp11, label %if.then12, label %if.else14, !dbg !592

if.then12:                                        ; preds = %if.end9
  %16 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !593
  %archive13 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %16, i32 0, i32 0, !dbg !595
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive13, i32 -1, i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.5, i32 0, i32 0)), !dbg !596
  store i32 -30, i32* %retval, align 4, !dbg !597
  br label %return, !dbg !597

if.else14:                                        ; preds = %if.end9
  %17 = load i32, i32* %ver, align 4, !dbg !598
  %cmp15 = icmp ult i32 %17, 1200, !dbg !600
  br i1 %cmp15, label %if.then17, label %lor.lhs.false, !dbg !601

lor.lhs.false:                                    ; preds = %if.else14
  %18 = load i32, i32* %ver, align 4, !dbg !602
  %cmp16 = icmp ugt i32 %18, 10000, !dbg !604
  br i1 %cmp16, label %if.then17, label %if.end20, !dbg !605

if.then17:                                        ; preds = %lor.lhs.false, %if.else14
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !606
  %archive18 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %19, i32 0, i32 0, !dbg !608
  %20 = load i32, i32* %ver, align 4, !dbg !609
  %div = udiv i32 %20, 10000, !dbg !610
  %21 = load i32, i32* %ver, align 4, !dbg !611
  %rem = urem i32 %21, 10000, !dbg !612
  %div19 = udiv i32 %rem, 100, !dbg !613
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive18, i32 -1, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.6, i32 0, i32 0), i32 %div, i32 %div19), !dbg !614
  store i32 -30, i32* %retval, align 4, !dbg !615
  br label %return, !dbg !615

if.end20:                                         ; preds = %lor.lhs.false
  br label %if.end21

if.end21:                                         ; preds = %if.end20
  %22 = load i8*, i8** %buf, align 8, !dbg !616
  %23 = load i8*, i8** %eoh, align 8, !dbg !617
  %24 = load i8*, i8** %buf, align 8, !dbg !618
  %sub.ptr.lhs.cast22 = ptrtoint i8* %23 to i64, !dbg !619
  %sub.ptr.rhs.cast23 = ptrtoint i8* %24 to i64, !dbg !619
  %sub.ptr.sub24 = sub i64 %sub.ptr.lhs.cast22, %sub.ptr.rhs.cast23, !dbg !619
  %call25 = call i64 @_warc_rdlen(i8* %22, i64 %sub.ptr.sub24), !dbg !620
  store i64 %call25, i64* %cntlen, align 8, !dbg !621
  %25 = load i64, i64* %cntlen, align 8, !dbg !622
  %cmp26 = icmp slt i64 %25, 0, !dbg !624
  br i1 %cmp26, label %if.then27, label %if.end29, !dbg !625

if.then27:                                        ; preds = %if.end21
  %26 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !626
  %archive28 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %26, i32 0, i32 0, !dbg !628
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive28, i32 22, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.7, i32 0, i32 0)), !dbg !629
  store i32 -30, i32* %retval, align 4, !dbg !630
  br label %return, !dbg !630

if.end29:                                         ; preds = %if.end21
  %27 = load i8*, i8** %buf, align 8, !dbg !631
  %28 = load i8*, i8** %eoh, align 8, !dbg !632
  %29 = load i8*, i8** %buf, align 8, !dbg !633
  %sub.ptr.lhs.cast30 = ptrtoint i8* %28 to i64, !dbg !634
  %sub.ptr.rhs.cast31 = ptrtoint i8* %29 to i64, !dbg !634
  %sub.ptr.sub32 = sub i64 %sub.ptr.lhs.cast30, %sub.ptr.rhs.cast31, !dbg !634
  %call33 = call i64 @_warc_rdrtm(i8* %27, i64 %sub.ptr.sub32), !dbg !635
  store i64 %call33, i64* %rtime, align 8, !dbg !636
  %30 = load i64, i64* %rtime, align 8, !dbg !637
  %cmp34 = icmp eq i64 %30, -1, !dbg !639
  br i1 %cmp34, label %if.then35, label %if.end37, !dbg !640

if.then35:                                        ; preds = %if.end29
  %31 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !641
  %archive36 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %31, i32 0, i32 0, !dbg !643
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive36, i32 22, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.8, i32 0, i32 0)), !dbg !644
  store i32 -30, i32* %retval, align 4, !dbg !645
  br label %return, !dbg !645

if.end37:                                         ; preds = %if.end29
  %32 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !646
  %archive38 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %32, i32 0, i32 0, !dbg !647
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive38, i32 0, i32 3, !dbg !648
  store i32 983040, i32* %archive_format, align 8, !dbg !649
  %33 = load i32, i32* %ver, align 4, !dbg !650
  %34 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !652
  %pver = getelementptr inbounds %struct.warc_s, %struct.warc_s* %34, i32 0, i32 4, !dbg !653
  %35 = load i32, i32* %pver, align 8, !dbg !653
  %cmp39 = icmp ne i32 %33, %35, !dbg !654
  br i1 %cmp39, label %if.then40, label %if.end45, !dbg !655

if.then40:                                        ; preds = %if.end37
  %36 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !656
  %sver = getelementptr inbounds %struct.warc_s, %struct.warc_s* %36, i32 0, i32 5, !dbg !658
  %37 = load i32, i32* %ver, align 4, !dbg !659
  %div41 = udiv i32 %37, 10000, !dbg !660
  %38 = load i32, i32* %ver, align 4, !dbg !661
  %rem42 = urem i32 %38, 10000, !dbg !662
  %div43 = udiv i32 %rem42, 100, !dbg !663
  call void (%struct.archive_string*, i8*, ...) @archive_string_sprintf(%struct.archive_string* %sver, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.9, i32 0, i32 0), i32 %div41, i32 %div43), !dbg !664
  %39 = load i32, i32* %ver, align 4, !dbg !665
  %40 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !666
  %pver44 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %40, i32 0, i32 4, !dbg !667
  store i32 %39, i32* %pver44, align 8, !dbg !668
  br label %if.end45, !dbg !669

if.end45:                                         ; preds = %if.then40, %if.end37
  %41 = load i8*, i8** %buf, align 8, !dbg !670
  %42 = load i8*, i8** %eoh, align 8, !dbg !671
  %43 = load i8*, i8** %buf, align 8, !dbg !672
  %sub.ptr.lhs.cast46 = ptrtoint i8* %42 to i64, !dbg !673
  %sub.ptr.rhs.cast47 = ptrtoint i8* %43 to i64, !dbg !673
  %sub.ptr.sub48 = sub i64 %sub.ptr.lhs.cast46, %sub.ptr.rhs.cast47, !dbg !673
  %call49 = call i32 @_warc_rdtyp(i8* %41, i64 %sub.ptr.sub48), !dbg !674
  store i32 %call49, i32* %ftyp, align 4, !dbg !675
  %44 = load i64, i64* %cntlen, align 8, !dbg !676
  %45 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !677
  %cntlen50 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %45, i32 0, i32 0, !dbg !678
  store i64 %44, i64* %cntlen50, align 8, !dbg !679
  %46 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !680
  %cntoff = getelementptr inbounds %struct.warc_s, %struct.warc_s* %46, i32 0, i32 1, !dbg !681
  store i64 0, i64* %cntoff, align 8, !dbg !682
  store i64 0, i64* %mtime, align 8, !dbg !683
  %47 = load i32, i32* %ftyp, align 4, !dbg !684
  switch i32 %47, label %sw.default [
    i32 3, label %sw.bb
    i32 5, label %sw.bb
  ], !dbg !685

sw.bb:                                            ; preds = %if.end45, %if.end45
  %48 = load i8*, i8** %buf, align 8, !dbg !686
  %49 = load i8*, i8** %eoh, align 8, !dbg !688
  %50 = load i8*, i8** %buf, align 8, !dbg !689
  %sub.ptr.lhs.cast51 = ptrtoint i8* %49 to i64, !dbg !690
  %sub.ptr.rhs.cast52 = ptrtoint i8* %50 to i64, !dbg !690
  %sub.ptr.sub53 = sub i64 %sub.ptr.lhs.cast51, %sub.ptr.rhs.cast52, !dbg !690
  %call54 = call { i64, i8* } @_warc_rduri(i8* %48, i64 %sub.ptr.sub53), !dbg !691
  %51 = bitcast %struct.warc_string_t* %coerce to { i64, i8* }*, !dbg !691
  %52 = getelementptr inbounds { i64, i8* }, { i64, i8* }* %51, i32 0, i32 0, !dbg !691
  %53 = extractvalue { i64, i8* } %call54, 0, !dbg !691
  store i64 %53, i64* %52, align 8, !dbg !691
  %54 = getelementptr inbounds { i64, i8* }, { i64, i8* }* %51, i32 0, i32 1, !dbg !691
  %55 = extractvalue { i64, i8* } %call54, 1, !dbg !691
  store i8* %55, i8** %54, align 8, !dbg !691
  %56 = bitcast %struct.warc_string_t* %fnam to i8*, !dbg !691
  %57 = bitcast %struct.warc_string_t* %coerce to i8*, !dbg !691
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %56, i8* %57, i64 16, i32 8, i1 false), !dbg !692
  %len = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 0, !dbg !694
  %58 = load i64, i64* %len, align 8, !dbg !694
  %cmp55 = icmp eq i64 %58, 0, !dbg !696
  br i1 %cmp55, label %if.then60, label %lor.lhs.false56, !dbg !697

lor.lhs.false56:                                  ; preds = %sw.bb
  %len57 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 0, !dbg !698
  %59 = load i64, i64* %len57, align 8, !dbg !698
  %sub = sub i64 %59, 1, !dbg !700
  %str = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 1, !dbg !701
  %60 = load i8*, i8** %str, align 8, !dbg !701
  %arrayidx = getelementptr inbounds i8, i8* %60, i64 %sub, !dbg !702
  %61 = load i8, i8* %arrayidx, align 1, !dbg !702
  %conv = sext i8 %61 to i32, !dbg !702
  %cmp58 = icmp eq i32 %conv, 47, !dbg !703
  br i1 %cmp58, label %if.then60, label %if.end63, !dbg !704

if.then60:                                        ; preds = %lor.lhs.false56, %sw.bb
  %len61 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 0, !dbg !705
  store i64 0, i64* %len61, align 8, !dbg !707
  %str62 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 1, !dbg !708
  store i8* null, i8** %str62, align 8, !dbg !709
  br label %sw.epilog, !dbg !710

if.end63:                                         ; preds = %lor.lhs.false56
  %len64 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 0, !dbg !711
  %62 = load i64, i64* %len64, align 8, !dbg !711
  %add = add i64 %62, 1, !dbg !713
  %63 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !714
  %pool = getelementptr inbounds %struct.warc_s, %struct.warc_s* %63, i32 0, i32 3, !dbg !715
  %len65 = getelementptr inbounds %struct.warc_strbuf_t, %struct.warc_strbuf_t* %pool, i32 0, i32 0, !dbg !716
  %64 = load i64, i64* %len65, align 8, !dbg !716
  %cmp66 = icmp ugt i64 %add, %64, !dbg !717
  br i1 %cmp66, label %if.then68, label %if.end81, !dbg !718

if.then68:                                        ; preds = %if.end63
  %len69 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 0, !dbg !719
  %65 = load i64, i64* %len69, align 8, !dbg !719
  %add70 = add i64 %65, 64, !dbg !721
  %div71 = udiv i64 %add70, 64, !dbg !722
  %mul = mul i64 %div71, 64, !dbg !723
  %66 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !724
  %pool72 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %66, i32 0, i32 3, !dbg !725
  %len73 = getelementptr inbounds %struct.warc_strbuf_t, %struct.warc_strbuf_t* %pool72, i32 0, i32 0, !dbg !726
  store i64 %mul, i64* %len73, align 8, !dbg !727
  %67 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !728
  %pool74 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %67, i32 0, i32 3, !dbg !729
  %str75 = getelementptr inbounds %struct.warc_strbuf_t, %struct.warc_strbuf_t* %pool74, i32 0, i32 1, !dbg !730
  %68 = load i8*, i8** %str75, align 8, !dbg !730
  %69 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !731
  %pool76 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %69, i32 0, i32 3, !dbg !732
  %len77 = getelementptr inbounds %struct.warc_strbuf_t, %struct.warc_strbuf_t* %pool76, i32 0, i32 0, !dbg !733
  %70 = load i64, i64* %len77, align 8, !dbg !733
  %call78 = call i8* @realloc(i8* %68, i64 %70) #7, !dbg !734
  %71 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !735
  %pool79 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %71, i32 0, i32 3, !dbg !736
  %str80 = getelementptr inbounds %struct.warc_strbuf_t, %struct.warc_strbuf_t* %pool79, i32 0, i32 1, !dbg !737
  store i8* %call78, i8** %str80, align 8, !dbg !738
  br label %if.end81, !dbg !739

if.end81:                                         ; preds = %if.then68, %if.end63
  %72 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !740
  %pool82 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %72, i32 0, i32 3, !dbg !741
  %str83 = getelementptr inbounds %struct.warc_strbuf_t, %struct.warc_strbuf_t* %pool82, i32 0, i32 1, !dbg !742
  %73 = load i8*, i8** %str83, align 8, !dbg !742
  %str84 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 1, !dbg !743
  %74 = load i8*, i8** %str84, align 8, !dbg !743
  %len85 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 0, !dbg !744
  %75 = load i64, i64* %len85, align 8, !dbg !744
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %73, i8* %74, i64 %75, i32 1, i1 false), !dbg !745
  %len86 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 0, !dbg !746
  %76 = load i64, i64* %len86, align 8, !dbg !746
  %77 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !747
  %pool87 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %77, i32 0, i32 3, !dbg !748
  %str88 = getelementptr inbounds %struct.warc_strbuf_t, %struct.warc_strbuf_t* %pool87, i32 0, i32 1, !dbg !749
  %78 = load i8*, i8** %str88, align 8, !dbg !749
  %arrayidx89 = getelementptr inbounds i8, i8* %78, i64 %76, !dbg !747
  store i8 0, i8* %arrayidx89, align 1, !dbg !750
  %79 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !751
  %pool90 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %79, i32 0, i32 3, !dbg !752
  %str91 = getelementptr inbounds %struct.warc_strbuf_t, %struct.warc_strbuf_t* %pool90, i32 0, i32 1, !dbg !753
  %80 = load i8*, i8** %str91, align 8, !dbg !753
  %str92 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 1, !dbg !754
  store i8* %80, i8** %str92, align 8, !dbg !755
  %81 = load i8*, i8** %buf, align 8, !dbg !756
  %82 = load i8*, i8** %eoh, align 8, !dbg !758
  %83 = load i8*, i8** %buf, align 8, !dbg !759
  %sub.ptr.lhs.cast93 = ptrtoint i8* %82 to i64, !dbg !760
  %sub.ptr.rhs.cast94 = ptrtoint i8* %83 to i64, !dbg !760
  %sub.ptr.sub95 = sub i64 %sub.ptr.lhs.cast93, %sub.ptr.rhs.cast94, !dbg !760
  %call96 = call i64 @_warc_rdmtm(i8* %81, i64 %sub.ptr.sub95), !dbg !761
  store i64 %call96, i64* %mtime, align 8, !dbg !762
  %cmp97 = icmp eq i64 %call96, -1, !dbg !763
  br i1 %cmp97, label %if.then99, label %if.end100, !dbg !764

if.then99:                                        ; preds = %if.end81
  %84 = load i64, i64* %rtime, align 8, !dbg !765
  store i64 %84, i64* %mtime, align 8, !dbg !767
  br label %if.end100, !dbg !768

if.end100:                                        ; preds = %if.then99, %if.end81
  br label %sw.epilog, !dbg !769

sw.default:                                       ; preds = %if.end45
  %len101 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 0, !dbg !770
  store i64 0, i64* %len101, align 8, !dbg !771
  %str102 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 1, !dbg !772
  store i8* null, i8** %str102, align 8, !dbg !773
  br label %sw.epilog, !dbg !774

sw.epilog:                                        ; preds = %sw.default, %if.end100, %if.then60
  %85 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !775
  %86 = load i8*, i8** %eoh, align 8, !dbg !776
  %87 = load i8*, i8** %buf, align 8, !dbg !777
  %sub.ptr.lhs.cast103 = ptrtoint i8* %86 to i64, !dbg !778
  %sub.ptr.rhs.cast104 = ptrtoint i8* %87 to i64, !dbg !778
  %sub.ptr.sub105 = sub i64 %sub.ptr.lhs.cast103, %sub.ptr.rhs.cast104, !dbg !778
  %call106 = call i64 @__archive_read_consume(%struct.archive_read* %85, i64 %sub.ptr.sub105), !dbg !779
  %88 = load i32, i32* %ftyp, align 4, !dbg !780
  switch i32 %88, label %sw.default114 [
    i32 3, label %sw.bb107
    i32 5, label %sw.bb107
  ], !dbg !781

sw.bb107:                                         ; preds = %sw.epilog, %sw.epilog
  %len108 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 0, !dbg !782
  %89 = load i64, i64* %len108, align 8, !dbg !782
  %cmp109 = icmp ugt i64 %89, 0, !dbg !785
  br i1 %cmp109, label %if.then111, label %if.end113, !dbg !786

if.then111:                                       ; preds = %sw.bb107
  %90 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !787
  call void @archive_entry_set_filetype(%struct.archive_entry* %90, i32 32768), !dbg !789
  %91 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !790
  %str112 = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %fnam, i32 0, i32 1, !dbg !791
  %92 = load i8*, i8** %str112, align 8, !dbg !791
  call void @archive_entry_copy_pathname(%struct.archive_entry* %91, i8* %92), !dbg !792
  %93 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !793
  %94 = load i64, i64* %cntlen, align 8, !dbg !794
  call void @archive_entry_set_size(%struct.archive_entry* %93, i64 %94), !dbg !795
  %95 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !796
  call void @archive_entry_set_perm(%struct.archive_entry* %95, i32 420), !dbg !797
  %96 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !798
  %97 = load i64, i64* %rtime, align 8, !dbg !799
  call void @archive_entry_set_ctime(%struct.archive_entry* %96, i64 %97, i64 0), !dbg !800
  %98 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !801
  %99 = load i64, i64* %mtime, align 8, !dbg !802
  call void @archive_entry_set_mtime(%struct.archive_entry* %98, i64 %99, i64 0), !dbg !803
  br label %sw.epilog116, !dbg !804

if.end113:                                        ; preds = %sw.bb107
  br label %sw.default114, !dbg !805

sw.default114:                                    ; preds = %sw.epilog, %if.end113
  %100 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !807
  %call115 = call i32 @_warc_skip(%struct.archive_read* %100), !dbg !808
  br label %start_over, !dbg !809

sw.epilog116:                                     ; preds = %if.then111
  store i32 0, i32* %retval, align 4, !dbg !810
  br label %return, !dbg !810

return:                                           ; preds = %sw.epilog116, %if.then35, %if.then27, %if.then17, %if.then12, %if.then7, %if.then3, %if.then
  %101 = load i32, i32* %retval, align 4, !dbg !811
  ret i32 %101, !dbg !811
}

; Function Attrs: nounwind uwtable
define internal i32 @_warc_read(%struct.archive_read* %a, i8** %buf, i64* %bsz, i64* %off) #0 !dbg !386 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %buf.addr = alloca i8**, align 8
  %bsz.addr = alloca i64*, align 8
  %off.addr = alloca i64*, align 8
  %w = alloca %struct.warc_s*, align 8
  %rab = alloca i8*, align 8
  %nrd = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !812, metadata !422), !dbg !813
  store i8** %buf, i8*** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buf.addr, metadata !814, metadata !422), !dbg !815
  store i64* %bsz, i64** %bsz.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %bsz.addr, metadata !816, metadata !422), !dbg !817
  store i64* %off, i64** %off.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %off.addr, metadata !818, metadata !422), !dbg !819
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !820, metadata !422), !dbg !821
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !822
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !823
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !823
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !824
  %2 = load i8*, i8** %data, align 8, !dbg !824
  %3 = bitcast i8* %2 to %struct.warc_s*, !dbg !822
  store %struct.warc_s* %3, %struct.warc_s** %w, align 8, !dbg !821
  call void @llvm.dbg.declare(metadata i8** %rab, metadata !825, metadata !422), !dbg !826
  call void @llvm.dbg.declare(metadata i64* %nrd, metadata !827, metadata !422), !dbg !828
  %4 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !829
  %cntoff = getelementptr inbounds %struct.warc_s, %struct.warc_s* %4, i32 0, i32 1, !dbg !831
  %5 = load i64, i64* %cntoff, align 8, !dbg !831
  %6 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !832
  %cntlen = getelementptr inbounds %struct.warc_s, %struct.warc_s* %6, i32 0, i32 0, !dbg !833
  %7 = load i64, i64* %cntlen, align 8, !dbg !833
  %cmp = icmp uge i64 %5, %7, !dbg !834
  br i1 %cmp, label %if.then, label %if.end, !dbg !835

if.then:                                          ; preds = %entry
  br label %eof, !dbg !836

eof:                                              ; preds = %if.then6, %if.then
  %8 = load i8**, i8*** %buf.addr, align 8, !dbg !838
  store i8* null, i8** %8, align 8, !dbg !840
  %9 = load i64*, i64** %bsz.addr, align 8, !dbg !841
  store i64 0, i64* %9, align 8, !dbg !842
  %10 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !843
  %cntoff1 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %10, i32 0, i32 1, !dbg !844
  %11 = load i64, i64* %cntoff1, align 8, !dbg !844
  %add = add i64 %11, 4, !dbg !845
  %12 = load i64*, i64** %off.addr, align 8, !dbg !846
  store i64 %add, i64* %12, align 8, !dbg !847
  %13 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !848
  %unconsumed = getelementptr inbounds %struct.warc_s, %struct.warc_s* %13, i32 0, i32 2, !dbg !849
  store i64 0, i64* %unconsumed, align 8, !dbg !850
  store i32 1, i32* %retval, align 4, !dbg !851
  br label %return, !dbg !851

if.end:                                           ; preds = %entry
  %14 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !852
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %14, i64 1, i64* %nrd), !dbg !853
  store i8* %call, i8** %rab, align 8, !dbg !854
  %15 = load i64, i64* %nrd, align 8, !dbg !855
  %cmp2 = icmp slt i64 %15, 0, !dbg !857
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !858

if.then3:                                         ; preds = %if.end
  %16 = load i64*, i64** %bsz.addr, align 8, !dbg !859
  store i64 0, i64* %16, align 8, !dbg !861
  %17 = load i64, i64* %nrd, align 8, !dbg !862
  %conv = trunc i64 %17 to i32, !dbg !863
  store i32 %conv, i32* %retval, align 4, !dbg !864
  br label %return, !dbg !864

if.else:                                          ; preds = %if.end
  %18 = load i64, i64* %nrd, align 8, !dbg !865
  %cmp4 = icmp eq i64 %18, 0, !dbg !867
  br i1 %cmp4, label %if.then6, label %if.else7, !dbg !868

if.then6:                                         ; preds = %if.else
  br label %eof, !dbg !869

if.else7:                                         ; preds = %if.else
  %19 = load i64, i64* %nrd, align 8, !dbg !871
  %20 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !873
  %cntlen8 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %20, i32 0, i32 0, !dbg !874
  %21 = load i64, i64* %cntlen8, align 8, !dbg !874
  %22 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !875
  %cntoff9 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %22, i32 0, i32 1, !dbg !876
  %23 = load i64, i64* %cntoff9, align 8, !dbg !876
  %sub = sub i64 %21, %23, !dbg !877
  %cmp10 = icmp ugt i64 %19, %sub, !dbg !878
  br i1 %cmp10, label %if.then12, label %if.end16, !dbg !879

if.then12:                                        ; preds = %if.else7
  %24 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !880
  %cntlen13 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %24, i32 0, i32 0, !dbg !882
  %25 = load i64, i64* %cntlen13, align 8, !dbg !882
  %26 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !883
  %cntoff14 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %26, i32 0, i32 1, !dbg !884
  %27 = load i64, i64* %cntoff14, align 8, !dbg !884
  %sub15 = sub i64 %25, %27, !dbg !885
  store i64 %sub15, i64* %nrd, align 8, !dbg !886
  br label %if.end16, !dbg !887

if.end16:                                         ; preds = %if.then12, %if.else7
  br label %if.end17

if.end17:                                         ; preds = %if.end16
  br label %if.end18

if.end18:                                         ; preds = %if.end17
  %28 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !888
  %cntoff19 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %28, i32 0, i32 1, !dbg !889
  %29 = load i64, i64* %cntoff19, align 8, !dbg !889
  %30 = load i64*, i64** %off.addr, align 8, !dbg !890
  store i64 %29, i64* %30, align 8, !dbg !891
  %31 = load i64, i64* %nrd, align 8, !dbg !892
  %32 = load i64*, i64** %bsz.addr, align 8, !dbg !893
  store i64 %31, i64* %32, align 8, !dbg !894
  %33 = load i8*, i8** %rab, align 8, !dbg !895
  %34 = load i8**, i8*** %buf.addr, align 8, !dbg !896
  store i8* %33, i8** %34, align 8, !dbg !897
  %35 = load i64, i64* %nrd, align 8, !dbg !898
  %36 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !899
  %cntoff20 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %36, i32 0, i32 1, !dbg !900
  %37 = load i64, i64* %cntoff20, align 8, !dbg !901
  %add21 = add i64 %37, %35, !dbg !901
  store i64 %add21, i64* %cntoff20, align 8, !dbg !901
  %38 = load i64, i64* %nrd, align 8, !dbg !902
  %39 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !903
  %unconsumed22 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %39, i32 0, i32 2, !dbg !904
  store i64 %38, i64* %unconsumed22, align 8, !dbg !905
  store i32 0, i32* %retval, align 4, !dbg !906
  br label %return, !dbg !906

return:                                           ; preds = %if.end18, %if.then3, %eof
  %40 = load i32, i32* %retval, align 4, !dbg !907
  ret i32 %40, !dbg !907
}

; Function Attrs: nounwind uwtable
define internal i32 @_warc_skip(%struct.archive_read* %a) #0 !dbg !387 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %w = alloca %struct.warc_s*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !908, metadata !422), !dbg !909
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !910, metadata !422), !dbg !911
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !912
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !913
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !913
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !914
  %2 = load i8*, i8** %data, align 8, !dbg !914
  %3 = bitcast i8* %2 to %struct.warc_s*, !dbg !912
  store %struct.warc_s* %3, %struct.warc_s** %w, align 8, !dbg !911
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !915
  %5 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !916
  %cntlen = getelementptr inbounds %struct.warc_s, %struct.warc_s* %5, i32 0, i32 0, !dbg !917
  %6 = load i64, i64* %cntlen, align 8, !dbg !917
  %add = add i64 %6, 4, !dbg !918
  %call = call i64 @__archive_read_consume(%struct.archive_read* %4, i64 %add), !dbg !919
  %7 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !920
  %cntlen1 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %7, i32 0, i32 0, !dbg !921
  store i64 0, i64* %cntlen1, align 8, !dbg !922
  %8 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !923
  %cntoff = getelementptr inbounds %struct.warc_s, %struct.warc_s* %8, i32 0, i32 1, !dbg !924
  store i64 0, i64* %cntoff, align 8, !dbg !925
  ret i32 0, !dbg !926
}

; Function Attrs: nounwind uwtable
define internal i32 @_warc_cleanup(%struct.archive_read* %a) #0 !dbg !328 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %w = alloca %struct.warc_s*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !927, metadata !422), !dbg !928
  call void @llvm.dbg.declare(metadata %struct.warc_s** %w, metadata !929, metadata !422), !dbg !930
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !931
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !932
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !932
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !933
  %2 = load i8*, i8** %data, align 8, !dbg !933
  %3 = bitcast i8* %2 to %struct.warc_s*, !dbg !931
  store %struct.warc_s* %3, %struct.warc_s** %w, align 8, !dbg !930
  %4 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !934
  %pool = getelementptr inbounds %struct.warc_s, %struct.warc_s* %4, i32 0, i32 3, !dbg !936
  %len = getelementptr inbounds %struct.warc_strbuf_t, %struct.warc_strbuf_t* %pool, i32 0, i32 0, !dbg !937
  %5 = load i64, i64* %len, align 8, !dbg !937
  %cmp = icmp ugt i64 %5, 0, !dbg !938
  br i1 %cmp, label %if.then, label %if.end, !dbg !939

if.then:                                          ; preds = %entry
  %6 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !940
  %pool1 = getelementptr inbounds %struct.warc_s, %struct.warc_s* %6, i32 0, i32 3, !dbg !942
  %str = getelementptr inbounds %struct.warc_strbuf_t, %struct.warc_strbuf_t* %pool1, i32 0, i32 1, !dbg !943
  %7 = load i8*, i8** %str, align 8, !dbg !943
  call void @free(i8* %7) #7, !dbg !944
  br label %if.end, !dbg !945

if.end:                                           ; preds = %if.then, %entry
  %8 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !946
  %sver = getelementptr inbounds %struct.warc_s, %struct.warc_s* %8, i32 0, i32 5, !dbg !947
  call void @archive_string_free(%struct.archive_string* %sver), !dbg !948
  %9 = load %struct.warc_s*, %struct.warc_s** %w, align 8, !dbg !949
  %10 = bitcast %struct.warc_s* %9 to i8*, !dbg !949
  call void @free(i8* %10) #7, !dbg !950
  %11 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !951
  %format2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 13, !dbg !952
  %12 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format2, align 8, !dbg !952
  %data3 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %12, i32 0, i32 0, !dbg !953
  store i8* null, i8** %data3, align 8, !dbg !954
  ret i32 0, !dbg !955
}

; Function Attrs: nounwind
declare void @free(i8*) #3

declare void @archive_string_free(%struct.archive_string*) #2

declare i8* @__archive_read_ahead(%struct.archive_read*, i64, i64*) #2

; Function Attrs: nounwind uwtable
define internal i32 @_warc_rdver(i8* %buf, i64 %bsz) #0 !dbg !330 {
entry:
  %retval = alloca i32, align 4
  %buf.addr = alloca i8*, align 8
  %bsz.addr = alloca i64, align 8
  %c = alloca i8*, align 8
  %ver = alloca i32, align 4
  %end = alloca i32, align 4
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !956, metadata !422), !dbg !957
  store i64 %bsz, i64* %bsz.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bsz.addr, metadata !958, metadata !422), !dbg !959
  call void @llvm.dbg.declare(metadata i8** %c, metadata !960, metadata !422), !dbg !961
  call void @llvm.dbg.declare(metadata i32* %ver, metadata !962, metadata !422), !dbg !963
  store i32 0, i32* %ver, align 4, !dbg !963
  call void @llvm.dbg.declare(metadata i32* %end, metadata !964, metadata !422), !dbg !965
  store i32 0, i32* %end, align 4, !dbg !965
  %0 = load i64, i64* %bsz.addr, align 8, !dbg !966
  %cmp = icmp ult i64 %0, 12, !dbg !968
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !969

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !970
  %call = call i32 @memcmp(i8* %1, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @_warc_rdver.magic, i32 0, i32 0), i64 5) #8, !dbg !972
  %cmp1 = icmp ne i32 %call, 0, !dbg !973
  br i1 %cmp1, label %if.then, label %if.end, !dbg !974

if.then:                                          ; preds = %lor.lhs.false, %entry
  %2 = load i32, i32* %ver, align 4, !dbg !975
  store i32 %2, i32* %retval, align 4, !dbg !977
  br label %return, !dbg !977

if.end:                                           ; preds = %lor.lhs.false
  %3 = load i8*, i8** %buf.addr, align 8, !dbg !978
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 5, !dbg !978
  store i8* %add.ptr, i8** %buf.addr, align 8, !dbg !978
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !979
  %arrayidx = getelementptr inbounds i8, i8* %4, i64 0, !dbg !979
  %5 = load i8, i8* %arrayidx, align 1, !dbg !979
  %conv = sext i8 %5 to i32, !dbg !979
  %idxprom = sext i32 %conv to i64, !dbg !979
  %call2 = call i16** @__ctype_b_loc() #1, !dbg !979
  %6 = load i16*, i16** %call2, align 8, !dbg !979
  %arrayidx3 = getelementptr inbounds i16, i16* %6, i64 %idxprom, !dbg !979
  %7 = load i16, i16* %arrayidx3, align 2, !dbg !979
  %conv4 = zext i16 %7 to i32, !dbg !979
  %and = and i32 %conv4, 2048, !dbg !979
  %tobool = icmp ne i32 %and, 0, !dbg !979
  br i1 %tobool, label %land.lhs.true, label %if.end74, !dbg !981

land.lhs.true:                                    ; preds = %if.end
  %8 = load i8*, i8** %buf.addr, align 8, !dbg !982
  %arrayidx5 = getelementptr inbounds i8, i8* %8, i64 1, !dbg !982
  %9 = load i8, i8* %arrayidx5, align 1, !dbg !982
  %conv6 = sext i8 %9 to i32, !dbg !982
  %cmp7 = icmp eq i32 %conv6, 46, !dbg !984
  br i1 %cmp7, label %land.lhs.true9, label %if.end74, !dbg !985

land.lhs.true9:                                   ; preds = %land.lhs.true
  %10 = load i8*, i8** %buf.addr, align 8, !dbg !986
  %arrayidx10 = getelementptr inbounds i8, i8* %10, i64 2, !dbg !986
  %11 = load i8, i8* %arrayidx10, align 1, !dbg !986
  %conv11 = sext i8 %11 to i32, !dbg !986
  %idxprom12 = sext i32 %conv11 to i64, !dbg !986
  %call13 = call i16** @__ctype_b_loc() #1, !dbg !986
  %12 = load i16*, i16** %call13, align 8, !dbg !986
  %arrayidx14 = getelementptr inbounds i16, i16* %12, i64 %idxprom12, !dbg !986
  %13 = load i16, i16* %arrayidx14, align 2, !dbg !986
  %conv15 = zext i16 %13 to i32, !dbg !986
  %and16 = and i32 %conv15, 2048, !dbg !986
  %tobool17 = icmp ne i32 %and16, 0, !dbg !986
  br i1 %tobool17, label %if.then18, label %if.end74, !dbg !988

if.then18:                                        ; preds = %land.lhs.true9
  %14 = load i8*, i8** %buf.addr, align 8, !dbg !989
  %arrayidx19 = getelementptr inbounds i8, i8* %14, i64 3, !dbg !989
  %15 = load i8, i8* %arrayidx19, align 1, !dbg !989
  %conv20 = sext i8 %15 to i32, !dbg !989
  %idxprom21 = sext i32 %conv20 to i64, !dbg !989
  %call22 = call i16** @__ctype_b_loc() #1, !dbg !989
  %16 = load i16*, i16** %call22, align 8, !dbg !989
  %arrayidx23 = getelementptr inbounds i16, i16* %16, i64 %idxprom21, !dbg !989
  %17 = load i16, i16* %arrayidx23, align 2, !dbg !989
  %conv24 = zext i16 %17 to i32, !dbg !989
  %and25 = and i32 %conv24, 2048, !dbg !989
  %tobool26 = icmp ne i32 %and25, 0, !dbg !989
  br i1 %tobool26, label %if.then27, label %if.end28, !dbg !992

if.then27:                                        ; preds = %if.then18
  store i32 1, i32* %end, align 4, !dbg !993
  br label %if.end28, !dbg !994

if.end28:                                         ; preds = %if.then27, %if.then18
  %18 = load i8*, i8** %buf.addr, align 8, !dbg !995
  %arrayidx29 = getelementptr inbounds i8, i8* %18, i64 0, !dbg !995
  %19 = load i8, i8* %arrayidx29, align 1, !dbg !995
  %conv30 = sext i8 %19 to i32, !dbg !995
  %sub = sub nsw i32 %conv30, 48, !dbg !996
  %mul = mul i32 %sub, 10000, !dbg !997
  store i32 %mul, i32* %ver, align 4, !dbg !998
  %20 = load i32, i32* %end, align 4, !dbg !999
  %cmp31 = icmp eq i32 %20, 1, !dbg !1001
  br i1 %cmp31, label %if.then33, label %if.else, !dbg !1002

if.then33:                                        ; preds = %if.end28
  %21 = load i8*, i8** %buf.addr, align 8, !dbg !1003
  %arrayidx34 = getelementptr inbounds i8, i8* %21, i64 2, !dbg !1003
  %22 = load i8, i8* %arrayidx34, align 1, !dbg !1003
  %conv35 = sext i8 %22 to i32, !dbg !1003
  %sub36 = sub nsw i32 %conv35, 48, !dbg !1005
  %mul37 = mul i32 %sub36, 1000, !dbg !1006
  %23 = load i32, i32* %ver, align 4, !dbg !1007
  %add = add i32 %23, %mul37, !dbg !1007
  store i32 %add, i32* %ver, align 4, !dbg !1007
  %24 = load i8*, i8** %buf.addr, align 8, !dbg !1008
  %arrayidx38 = getelementptr inbounds i8, i8* %24, i64 3, !dbg !1008
  %25 = load i8, i8* %arrayidx38, align 1, !dbg !1008
  %conv39 = sext i8 %25 to i32, !dbg !1008
  %sub40 = sub nsw i32 %conv39, 48, !dbg !1009
  %mul41 = mul i32 %sub40, 100, !dbg !1010
  %26 = load i32, i32* %ver, align 4, !dbg !1011
  %add42 = add i32 %26, %mul41, !dbg !1011
  store i32 %add42, i32* %ver, align 4, !dbg !1011
  br label %if.end48, !dbg !1012

if.else:                                          ; preds = %if.end28
  %27 = load i8*, i8** %buf.addr, align 8, !dbg !1013
  %arrayidx43 = getelementptr inbounds i8, i8* %27, i64 2, !dbg !1013
  %28 = load i8, i8* %arrayidx43, align 1, !dbg !1013
  %conv44 = sext i8 %28 to i32, !dbg !1013
  %sub45 = sub nsw i32 %conv44, 48, !dbg !1014
  %mul46 = mul i32 %sub45, 100, !dbg !1015
  %29 = load i32, i32* %ver, align 4, !dbg !1016
  %add47 = add i32 %29, %mul46, !dbg !1016
  store i32 %add47, i32* %ver, align 4, !dbg !1016
  br label %if.end48

if.end48:                                         ; preds = %if.else, %if.then33
  %30 = load i8*, i8** %buf.addr, align 8, !dbg !1017
  %add.ptr49 = getelementptr inbounds i8, i8* %30, i64 3, !dbg !1018
  %31 = load i32, i32* %end, align 4, !dbg !1019
  %idx.ext = zext i32 %31 to i64, !dbg !1020
  %add.ptr50 = getelementptr inbounds i8, i8* %add.ptr49, i64 %idx.ext, !dbg !1020
  store i8* %add.ptr50, i8** %c, align 8, !dbg !1021
  %32 = load i32, i32* %ver, align 4, !dbg !1022
  %cmp51 = icmp uge i32 %32, 1200, !dbg !1024
  br i1 %cmp51, label %if.then53, label %if.else59, !dbg !1025

if.then53:                                        ; preds = %if.end48
  %33 = load i8*, i8** %c, align 8, !dbg !1026
  %call54 = call i32 @memcmp(i8* %33, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.3, i32 0, i32 0), i64 2) #8, !dbg !1029
  %cmp55 = icmp ne i32 %call54, 0, !dbg !1030
  br i1 %cmp55, label %if.then57, label %if.end58, !dbg !1031

if.then57:                                        ; preds = %if.then53
  store i32 0, i32* %ver, align 4, !dbg !1032
  br label %if.end58, !dbg !1033

if.end58:                                         ; preds = %if.then57, %if.then53
  br label %if.end73, !dbg !1034

if.else59:                                        ; preds = %if.end48
  %34 = load i32, i32* %ver, align 4, !dbg !1035
  %cmp60 = icmp ult i32 %34, 1200, !dbg !1038
  br i1 %cmp60, label %if.then62, label %if.end72, !dbg !1035

if.then62:                                        ; preds = %if.else59
  %35 = load i8*, i8** %c, align 8, !dbg !1039
  %36 = load i8, i8* %35, align 1, !dbg !1042
  %conv63 = sext i8 %36 to i32, !dbg !1042
  %cmp64 = icmp ne i32 %conv63, 32, !dbg !1043
  br i1 %cmp64, label %land.lhs.true66, label %if.end71, !dbg !1044

land.lhs.true66:                                  ; preds = %if.then62
  %37 = load i8*, i8** %c, align 8, !dbg !1045
  %38 = load i8, i8* %37, align 1, !dbg !1047
  %conv67 = sext i8 %38 to i32, !dbg !1047
  %cmp68 = icmp ne i32 %conv67, 9, !dbg !1048
  br i1 %cmp68, label %if.then70, label %if.end71, !dbg !1049

if.then70:                                        ; preds = %land.lhs.true66
  store i32 0, i32* %ver, align 4, !dbg !1050
  br label %if.end71, !dbg !1051

if.end71:                                         ; preds = %if.then70, %land.lhs.true66, %if.then62
  br label %if.end72, !dbg !1052

if.end72:                                         ; preds = %if.end71, %if.else59
  br label %if.end73

if.end73:                                         ; preds = %if.end72, %if.end58
  br label %if.end74, !dbg !1053

if.end74:                                         ; preds = %if.end73, %land.lhs.true9, %land.lhs.true, %if.end
  %39 = load i32, i32* %ver, align 4, !dbg !1054
  store i32 %39, i32* %retval, align 4, !dbg !1055
  br label %return, !dbg !1055

return:                                           ; preds = %if.end74, %if.then
  %40 = load i32, i32* %retval, align 4, !dbg !1056
  ret i32 %40, !dbg !1056
}

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #4

; Function Attrs: nounwind readnone
declare i16** @__ctype_b_loc() #5

; Function Attrs: nounwind uwtable
define internal i8* @_warc_find_eoh(i8* %buf, i64 %bsz) #0 !dbg !334 {
entry:
  %buf.addr = alloca i8*, align 8
  %bsz.addr = alloca i64, align 8
  %hit = alloca i8*, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1057, metadata !422), !dbg !1058
  store i64 %bsz, i64* %bsz.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bsz.addr, metadata !1059, metadata !422), !dbg !1060
  call void @llvm.dbg.declare(metadata i8** %hit, metadata !1061, metadata !422), !dbg !1062
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !1063
  %1 = load i64, i64* %bsz.addr, align 8, !dbg !1064
  %call = call i8* @xmemmem(i8* %0, i64 %1, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @_warc_find_eoh._marker, i32 0, i32 0), i64 4), !dbg !1065
  store i8* %call, i8** %hit, align 8, !dbg !1062
  %2 = load i8*, i8** %hit, align 8, !dbg !1066
  %cmp = icmp ne i8* %2, null, !dbg !1068
  br i1 %cmp, label %if.then, label %if.end, !dbg !1069

if.then:                                          ; preds = %entry
  %3 = load i8*, i8** %hit, align 8, !dbg !1070
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 4, !dbg !1070
  store i8* %add.ptr, i8** %hit, align 8, !dbg !1070
  br label %if.end, !dbg !1072

if.end:                                           ; preds = %if.then, %entry
  %4 = load i8*, i8** %hit, align 8, !dbg !1073
  ret i8* %4, !dbg !1074
}

; Function Attrs: nounwind uwtable
define internal i64 @_warc_rdlen(i8* %buf, i64 %bsz) #0 !dbg !344 {
entry:
  %retval = alloca i64, align 8
  %buf.addr = alloca i8*, align 8
  %bsz.addr = alloca i64, align 8
  %val = alloca i8*, align 8
  %eol = alloca i8*, align 8
  %on = alloca i8*, align 8
  %len = alloca i64, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1075, metadata !422), !dbg !1076
  store i64 %bsz, i64* %bsz.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bsz.addr, metadata !1077, metadata !422), !dbg !1078
  call void @llvm.dbg.declare(metadata i8** %val, metadata !1079, metadata !422), !dbg !1080
  call void @llvm.dbg.declare(metadata i8** %eol, metadata !1081, metadata !422), !dbg !1082
  call void @llvm.dbg.declare(metadata i8** %on, metadata !1083, metadata !422), !dbg !1084
  store i8* null, i8** %on, align 8, !dbg !1084
  call void @llvm.dbg.declare(metadata i64* %len, metadata !1085, metadata !422), !dbg !1086
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !1087
  %1 = load i64, i64* %bsz.addr, align 8, !dbg !1089
  %call = call i8* @xmemmem(i8* %0, i64 %1, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @_warc_rdlen._key, i32 0, i32 0), i64 17), !dbg !1090
  store i8* %call, i8** %val, align 8, !dbg !1091
  %cmp = icmp eq i8* %call, null, !dbg !1092
  br i1 %cmp, label %if.then, label %if.end, !dbg !1093

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !1094
  br label %return, !dbg !1094

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %val, align 8, !dbg !1096
  %add.ptr = getelementptr inbounds i8, i8* %2, i64 17, !dbg !1096
  store i8* %add.ptr, i8** %val, align 8, !dbg !1096
  %3 = load i8*, i8** %val, align 8, !dbg !1097
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !1099
  %5 = load i64, i64* %bsz.addr, align 8, !dbg !1100
  %add.ptr1 = getelementptr inbounds i8, i8* %4, i64 %5, !dbg !1101
  %6 = load i8*, i8** %val, align 8, !dbg !1102
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr1 to i64, !dbg !1103
  %sub.ptr.rhs.cast = ptrtoint i8* %6 to i64, !dbg !1103
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1103
  %call2 = call i8* @_warc_find_eol(i8* %3, i64 %sub.ptr.sub), !dbg !1104
  store i8* %call2, i8** %eol, align 8, !dbg !1105
  %cmp3 = icmp eq i8* %call2, null, !dbg !1106
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1107

if.then4:                                         ; preds = %if.end
  store i64 -1, i64* %retval, align 8, !dbg !1108
  br label %return, !dbg !1108

if.end5:                                          ; preds = %if.end
  br label %while.cond, !dbg !1110

while.cond:                                       ; preds = %while.body, %if.end5
  %7 = load i8*, i8** %val, align 8, !dbg !1111
  %8 = load i8*, i8** %eol, align 8, !dbg !1113
  %cmp6 = icmp ult i8* %7, %8, !dbg !1114
  br i1 %cmp6, label %land.rhs, label %land.end, !dbg !1115

land.rhs:                                         ; preds = %while.cond
  %9 = load i8*, i8** %val, align 8, !dbg !1116
  %10 = load i8, i8* %9, align 1, !dbg !1118
  %conv = sext i8 %10 to i32, !dbg !1118
  %cmp7 = icmp eq i32 %conv, 32, !dbg !1119
  br i1 %cmp7, label %lor.end, label %lor.rhs, !dbg !1120

lor.rhs:                                          ; preds = %land.rhs
  %11 = load i8*, i8** %val, align 8, !dbg !1121
  %12 = load i8, i8* %11, align 1, !dbg !1123
  %conv9 = sext i8 %12 to i32, !dbg !1123
  %cmp10 = icmp eq i32 %conv9, 9, !dbg !1124
  br label %lor.end, !dbg !1125

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %13 = phi i1 [ true, %land.rhs ], [ %cmp10, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond
  %14 = phi i1 [ false, %while.cond ], [ %13, %lor.end ]
  br i1 %14, label %while.body, label %while.end, !dbg !1126

while.body:                                       ; preds = %land.end
  %15 = load i8*, i8** %val, align 8, !dbg !1128
  %incdec.ptr = getelementptr inbounds i8, i8* %15, i32 1, !dbg !1128
  store i8* %incdec.ptr, i8** %val, align 8, !dbg !1128
  br label %while.cond, !dbg !1129

while.end:                                        ; preds = %land.end
  %16 = load i8*, i8** %val, align 8, !dbg !1131
  %17 = load i8, i8* %16, align 1, !dbg !1131
  %conv12 = sext i8 %17 to i32, !dbg !1131
  %idxprom = sext i32 %conv12 to i64, !dbg !1131
  %call13 = call i16** @__ctype_b_loc() #1, !dbg !1131
  %18 = load i16*, i16** %call13, align 8, !dbg !1131
  %arrayidx = getelementptr inbounds i16, i16* %18, i64 %idxprom, !dbg !1131
  %19 = load i16, i16* %arrayidx, align 2, !dbg !1131
  %conv14 = zext i16 %19 to i32, !dbg !1131
  %and = and i32 %conv14, 2048, !dbg !1131
  %tobool = icmp ne i32 %and, 0, !dbg !1131
  br i1 %tobool, label %if.end16, label %if.then15, !dbg !1133

if.then15:                                        ; preds = %while.end
  store i64 -1, i64* %retval, align 8, !dbg !1134
  br label %return, !dbg !1134

if.end16:                                         ; preds = %while.end
  %20 = load i8*, i8** %val, align 8, !dbg !1135
  %call17 = call i64 @strtol(i8* %20, i8** %on, i32 10) #7, !dbg !1136
  store i64 %call17, i64* %len, align 8, !dbg !1137
  %21 = load i8*, i8** %on, align 8, !dbg !1138
  %22 = load i8*, i8** %eol, align 8, !dbg !1140
  %cmp18 = icmp ne i8* %21, %22, !dbg !1141
  br i1 %cmp18, label %if.then20, label %if.end21, !dbg !1142

if.then20:                                        ; preds = %if.end16
  store i64 -1, i64* %retval, align 8, !dbg !1143
  br label %return, !dbg !1143

if.end21:                                         ; preds = %if.end16
  %23 = load i64, i64* %len, align 8, !dbg !1145
  store i64 %23, i64* %retval, align 8, !dbg !1146
  br label %return, !dbg !1146

return:                                           ; preds = %if.end21, %if.then20, %if.then15, %if.then4, %if.then
  %24 = load i64, i64* %retval, align 8, !dbg !1147
  ret i64 %24, !dbg !1147
}

; Function Attrs: nounwind uwtable
define internal i64 @_warc_rdrtm(i8* %buf, i64 %bsz) #0 !dbg !348 {
entry:
  %retval = alloca i64, align 8
  %buf.addr = alloca i8*, align 8
  %bsz.addr = alloca i64, align 8
  %val = alloca i8*, align 8
  %eol = alloca i8*, align 8
  %on = alloca i8*, align 8
  %res = alloca i64, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1148, metadata !422), !dbg !1149
  store i64 %bsz, i64* %bsz.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bsz.addr, metadata !1150, metadata !422), !dbg !1151
  call void @llvm.dbg.declare(metadata i8** %val, metadata !1152, metadata !422), !dbg !1153
  call void @llvm.dbg.declare(metadata i8** %eol, metadata !1154, metadata !422), !dbg !1155
  call void @llvm.dbg.declare(metadata i8** %on, metadata !1156, metadata !422), !dbg !1157
  store i8* null, i8** %on, align 8, !dbg !1157
  call void @llvm.dbg.declare(metadata i64* %res, metadata !1158, metadata !422), !dbg !1159
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !1160
  %1 = load i64, i64* %bsz.addr, align 8, !dbg !1162
  %call = call i8* @xmemmem(i8* %0, i64 %1, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @_warc_rdrtm._key, i32 0, i32 0), i64 12), !dbg !1163
  store i8* %call, i8** %val, align 8, !dbg !1164
  %cmp = icmp eq i8* %call, null, !dbg !1165
  br i1 %cmp, label %if.then, label %if.end, !dbg !1166

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !1167
  br label %return, !dbg !1167

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %val, align 8, !dbg !1169
  %add.ptr = getelementptr inbounds i8, i8* %2, i64 12, !dbg !1169
  store i8* %add.ptr, i8** %val, align 8, !dbg !1169
  %3 = load i8*, i8** %val, align 8, !dbg !1170
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !1172
  %5 = load i64, i64* %bsz.addr, align 8, !dbg !1173
  %add.ptr1 = getelementptr inbounds i8, i8* %4, i64 %5, !dbg !1174
  %6 = load i8*, i8** %val, align 8, !dbg !1175
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr1 to i64, !dbg !1176
  %sub.ptr.rhs.cast = ptrtoint i8* %6 to i64, !dbg !1176
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1176
  %call2 = call i8* @_warc_find_eol(i8* %3, i64 %sub.ptr.sub), !dbg !1177
  store i8* %call2, i8** %eol, align 8, !dbg !1178
  %cmp3 = icmp eq i8* %call2, null, !dbg !1179
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1180

if.then4:                                         ; preds = %if.end
  store i64 -1, i64* %retval, align 8, !dbg !1181
  br label %return, !dbg !1181

if.end5:                                          ; preds = %if.end
  %7 = load i8*, i8** %val, align 8, !dbg !1183
  %call6 = call i64 @xstrpisotime(i8* %7, i8** %on), !dbg !1184
  store i64 %call6, i64* %res, align 8, !dbg !1185
  %8 = load i8*, i8** %on, align 8, !dbg !1186
  %9 = load i8*, i8** %eol, align 8, !dbg !1188
  %cmp7 = icmp ne i8* %8, %9, !dbg !1189
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !1190

if.then8:                                         ; preds = %if.end5
  store i64 -1, i64* %retval, align 8, !dbg !1191
  br label %return, !dbg !1191

if.end9:                                          ; preds = %if.end5
  %10 = load i64, i64* %res, align 8, !dbg !1193
  store i64 %10, i64* %retval, align 8, !dbg !1194
  br label %return, !dbg !1194

return:                                           ; preds = %if.end9, %if.then8, %if.then4, %if.then
  %11 = load i64, i64* %retval, align 8, !dbg !1195
  ret i64 %11, !dbg !1195
}

declare void @archive_string_sprintf(%struct.archive_string*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @_warc_rdtyp(i8* %buf, i64 %bsz) #0 !dbg !376 {
entry:
  %retval = alloca i32, align 4
  %buf.addr = alloca i8*, align 8
  %bsz.addr = alloca i64, align 8
  %val = alloca i8*, align 8
  %eol = alloca i8*, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1196, metadata !422), !dbg !1197
  store i64 %bsz, i64* %bsz.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bsz.addr, metadata !1198, metadata !422), !dbg !1199
  call void @llvm.dbg.declare(metadata i8** %val, metadata !1200, metadata !422), !dbg !1201
  call void @llvm.dbg.declare(metadata i8** %eol, metadata !1202, metadata !422), !dbg !1203
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !1204
  %1 = load i64, i64* %bsz.addr, align 8, !dbg !1206
  %call = call i8* @xmemmem(i8* %0, i64 %1, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @_warc_rdtyp._key, i32 0, i32 0), i64 12), !dbg !1207
  store i8* %call, i8** %val, align 8, !dbg !1208
  %cmp = icmp eq i8* %call, null, !dbg !1209
  br i1 %cmp, label %if.then, label %if.end, !dbg !1210

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1211
  br label %return, !dbg !1211

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %val, align 8, !dbg !1213
  %add.ptr = getelementptr inbounds i8, i8* %2, i64 12, !dbg !1213
  store i8* %add.ptr, i8** %val, align 8, !dbg !1213
  %3 = load i8*, i8** %val, align 8, !dbg !1214
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !1216
  %5 = load i64, i64* %bsz.addr, align 8, !dbg !1217
  %add.ptr1 = getelementptr inbounds i8, i8* %4, i64 %5, !dbg !1218
  %6 = load i8*, i8** %val, align 8, !dbg !1219
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr1 to i64, !dbg !1220
  %sub.ptr.rhs.cast = ptrtoint i8* %6 to i64, !dbg !1220
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1220
  %call2 = call i8* @_warc_find_eol(i8* %3, i64 %sub.ptr.sub), !dbg !1221
  store i8* %call2, i8** %eol, align 8, !dbg !1222
  %cmp3 = icmp eq i8* %call2, null, !dbg !1223
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1224

if.then4:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !1225
  br label %return, !dbg !1225

if.end5:                                          ; preds = %if.end
  br label %while.cond, !dbg !1227

while.cond:                                       ; preds = %while.body, %if.end5
  %7 = load i8*, i8** %val, align 8, !dbg !1228
  %8 = load i8*, i8** %eol, align 8, !dbg !1230
  %cmp6 = icmp ult i8* %7, %8, !dbg !1231
  br i1 %cmp6, label %land.rhs, label %land.end, !dbg !1232

land.rhs:                                         ; preds = %while.cond
  %9 = load i8*, i8** %val, align 8, !dbg !1233
  %10 = load i8, i8* %9, align 1, !dbg !1235
  %conv = sext i8 %10 to i32, !dbg !1235
  %cmp7 = icmp eq i32 %conv, 32, !dbg !1236
  br i1 %cmp7, label %lor.end, label %lor.rhs, !dbg !1237

lor.rhs:                                          ; preds = %land.rhs
  %11 = load i8*, i8** %val, align 8, !dbg !1238
  %12 = load i8, i8* %11, align 1, !dbg !1240
  %conv9 = sext i8 %12 to i32, !dbg !1240
  %cmp10 = icmp eq i32 %conv9, 9, !dbg !1241
  br label %lor.end, !dbg !1242

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %13 = phi i1 [ true, %land.rhs ], [ %cmp10, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond
  %14 = phi i1 [ false, %while.cond ], [ %13, %lor.end ]
  br i1 %14, label %while.body, label %while.end, !dbg !1243

while.body:                                       ; preds = %land.end
  %15 = load i8*, i8** %val, align 8, !dbg !1245
  %incdec.ptr = getelementptr inbounds i8, i8* %15, i32 1, !dbg !1245
  store i8* %incdec.ptr, i8** %val, align 8, !dbg !1245
  br label %while.cond, !dbg !1246

while.end:                                        ; preds = %land.end
  %16 = load i8*, i8** %val, align 8, !dbg !1248
  %add.ptr12 = getelementptr inbounds i8, i8* %16, i64 8, !dbg !1250
  %17 = load i8*, i8** %eol, align 8, !dbg !1251
  %cmp13 = icmp eq i8* %add.ptr12, %17, !dbg !1252
  br i1 %cmp13, label %if.then15, label %if.end26, !dbg !1253

if.then15:                                        ; preds = %while.end
  %18 = load i8*, i8** %val, align 8, !dbg !1254
  %call16 = call i32 @memcmp(i8* %18, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.10, i32 0, i32 0), i64 8) #8, !dbg !1257
  %cmp17 = icmp eq i32 %call16, 0, !dbg !1258
  br i1 %cmp17, label %if.then19, label %if.else, !dbg !1259

if.then19:                                        ; preds = %if.then15
  store i32 3, i32* %retval, align 4, !dbg !1260
  br label %return, !dbg !1260

if.else:                                          ; preds = %if.then15
  %19 = load i8*, i8** %val, align 8, !dbg !1261
  %call20 = call i32 @memcmp(i8* %19, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.11, i32 0, i32 0), i64 8) #8, !dbg !1263
  %cmp21 = icmp eq i32 %call20, 0, !dbg !1264
  br i1 %cmp21, label %if.then23, label %if.end24, !dbg !1265

if.then23:                                        ; preds = %if.else
  store i32 5, i32* %retval, align 4, !dbg !1266
  br label %return, !dbg !1266

if.end24:                                         ; preds = %if.else
  br label %if.end25

if.end25:                                         ; preds = %if.end24
  br label %if.end26, !dbg !1267

if.end26:                                         ; preds = %if.end25, %while.end
  store i32 0, i32* %retval, align 4, !dbg !1268
  br label %return, !dbg !1268

return:                                           ; preds = %if.end26, %if.then23, %if.then19, %if.then4, %if.then
  %20 = load i32, i32* %retval, align 4, !dbg !1269
  ret i32 %20, !dbg !1269
}

; Function Attrs: nounwind uwtable
define internal { i64, i8* } @_warc_rduri(i8* %buf, i64 %bsz) #0 !dbg !377 {
entry:
  %retval = alloca %struct.warc_string_t, align 8
  %buf.addr = alloca i8*, align 8
  %bsz.addr = alloca i64, align 8
  %val = alloca i8*, align 8
  %uri = alloca i8*, align 8
  %eol = alloca i8*, align 8
  %p = alloca i8*, align 8
  %res = alloca %struct.warc_string_t, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1270, metadata !422), !dbg !1271
  store i64 %bsz, i64* %bsz.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bsz.addr, metadata !1272, metadata !422), !dbg !1273
  call void @llvm.dbg.declare(metadata i8** %val, metadata !1274, metadata !422), !dbg !1275
  call void @llvm.dbg.declare(metadata i8** %uri, metadata !1276, metadata !422), !dbg !1277
  call void @llvm.dbg.declare(metadata i8** %eol, metadata !1278, metadata !422), !dbg !1279
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1280, metadata !422), !dbg !1281
  call void @llvm.dbg.declare(metadata %struct.warc_string_t* %res, metadata !1282, metadata !422), !dbg !1283
  %0 = bitcast %struct.warc_string_t* %res to i8*, !dbg !1283
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 16, i32 8, i1 false), !dbg !1283
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !1284
  %2 = load i64, i64* %bsz.addr, align 8, !dbg !1286
  %call = call i8* @xmemmem(i8* %1, i64 %2, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @_warc_rduri._key, i32 0, i32 0), i64 18), !dbg !1287
  store i8* %call, i8** %val, align 8, !dbg !1288
  %cmp = icmp eq i8* %call, null, !dbg !1289
  br i1 %cmp, label %if.then, label %if.end, !dbg !1290

if.then:                                          ; preds = %entry
  %3 = bitcast %struct.warc_string_t* %retval to i8*, !dbg !1291
  %4 = bitcast %struct.warc_string_t* %res to i8*, !dbg !1291
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 16, i32 8, i1 false), !dbg !1291
  br label %return, !dbg !1293

if.end:                                           ; preds = %entry
  %5 = load i8*, i8** %val, align 8, !dbg !1294
  %add.ptr = getelementptr inbounds i8, i8* %5, i64 18, !dbg !1294
  store i8* %add.ptr, i8** %val, align 8, !dbg !1294
  %6 = load i8*, i8** %val, align 8, !dbg !1295
  %7 = load i8*, i8** %buf.addr, align 8, !dbg !1297
  %8 = load i64, i64* %bsz.addr, align 8, !dbg !1298
  %add.ptr1 = getelementptr inbounds i8, i8* %7, i64 %8, !dbg !1299
  %9 = load i8*, i8** %val, align 8, !dbg !1300
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr1 to i64, !dbg !1301
  %sub.ptr.rhs.cast = ptrtoint i8* %9 to i64, !dbg !1301
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1301
  %call2 = call i8* @_warc_find_eol(i8* %6, i64 %sub.ptr.sub), !dbg !1302
  store i8* %call2, i8** %eol, align 8, !dbg !1303
  %cmp3 = icmp eq i8* %call2, null, !dbg !1304
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1305

if.then4:                                         ; preds = %if.end
  %10 = bitcast %struct.warc_string_t* %retval to i8*, !dbg !1306
  %11 = bitcast %struct.warc_string_t* %res to i8*, !dbg !1306
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %10, i8* %11, i64 16, i32 8, i1 false), !dbg !1306
  br label %return, !dbg !1308

if.end5:                                          ; preds = %if.end
  br label %while.cond, !dbg !1309

while.cond:                                       ; preds = %while.body, %if.end5
  %12 = load i8*, i8** %val, align 8, !dbg !1310
  %13 = load i8*, i8** %eol, align 8, !dbg !1312
  %cmp6 = icmp ult i8* %12, %13, !dbg !1313
  br i1 %cmp6, label %land.rhs, label %land.end, !dbg !1314

land.rhs:                                         ; preds = %while.cond
  %14 = load i8*, i8** %val, align 8, !dbg !1315
  %15 = load i8, i8* %14, align 1, !dbg !1317
  %conv = sext i8 %15 to i32, !dbg !1317
  %cmp7 = icmp eq i32 %conv, 32, !dbg !1318
  br i1 %cmp7, label %lor.end, label %lor.rhs, !dbg !1319

lor.rhs:                                          ; preds = %land.rhs
  %16 = load i8*, i8** %val, align 8, !dbg !1320
  %17 = load i8, i8* %16, align 1, !dbg !1322
  %conv9 = sext i8 %17 to i32, !dbg !1322
  %cmp10 = icmp eq i32 %conv9, 9, !dbg !1323
  br label %lor.end, !dbg !1324

lor.end:                                          ; preds = %lor.rhs, %land.rhs
  %18 = phi i1 [ true, %land.rhs ], [ %cmp10, %lor.rhs ]
  br label %land.end

land.end:                                         ; preds = %lor.end, %while.cond
  %19 = phi i1 [ false, %while.cond ], [ %18, %lor.end ]
  br i1 %19, label %while.body, label %while.end, !dbg !1325

while.body:                                       ; preds = %land.end
  %20 = load i8*, i8** %val, align 8, !dbg !1327
  %incdec.ptr = getelementptr inbounds i8, i8* %20, i32 1, !dbg !1327
  store i8* %incdec.ptr, i8** %val, align 8, !dbg !1327
  br label %while.cond, !dbg !1328

while.end:                                        ; preds = %land.end
  %21 = load i8*, i8** %val, align 8, !dbg !1330
  %22 = load i8*, i8** %eol, align 8, !dbg !1332
  %23 = load i8*, i8** %val, align 8, !dbg !1333
  %sub.ptr.lhs.cast12 = ptrtoint i8* %22 to i64, !dbg !1334
  %sub.ptr.rhs.cast13 = ptrtoint i8* %23 to i64, !dbg !1334
  %sub.ptr.sub14 = sub i64 %sub.ptr.lhs.cast12, %sub.ptr.rhs.cast13, !dbg !1334
  %call15 = call i8* @xmemmem(i8* %21, i64 %sub.ptr.sub14, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.12, i32 0, i32 0), i64 3), !dbg !1335
  store i8* %call15, i8** %uri, align 8, !dbg !1336
  %cmp16 = icmp eq i8* %call15, null, !dbg !1337
  br i1 %cmp16, label %if.then18, label %if.end19, !dbg !1338

if.then18:                                        ; preds = %while.end
  %24 = bitcast %struct.warc_string_t* %retval to i8*, !dbg !1339
  %25 = bitcast %struct.warc_string_t* %res to i8*, !dbg !1339
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %24, i8* %25, i64 16, i32 8, i1 false), !dbg !1339
  br label %return, !dbg !1341

if.end19:                                         ; preds = %while.end
  %26 = load i8*, i8** %val, align 8, !dbg !1342
  store i8* %26, i8** %p, align 8, !dbg !1344
  br label %for.cond, !dbg !1345

for.cond:                                         ; preds = %for.inc, %if.end19
  %27 = load i8*, i8** %p, align 8, !dbg !1346
  %28 = load i8*, i8** %eol, align 8, !dbg !1349
  %cmp20 = icmp ult i8* %27, %28, !dbg !1350
  br i1 %cmp20, label %for.body, label %for.end, !dbg !1351

for.body:                                         ; preds = %for.cond
  %29 = load i8*, i8** %p, align 8, !dbg !1352
  %30 = load i8, i8* %29, align 1, !dbg !1352
  %conv22 = sext i8 %30 to i32, !dbg !1352
  %idxprom = sext i32 %conv22 to i64, !dbg !1352
  %call23 = call i16** @__ctype_b_loc() #1, !dbg !1352
  %31 = load i16*, i16** %call23, align 8, !dbg !1352
  %arrayidx = getelementptr inbounds i16, i16* %31, i64 %idxprom, !dbg !1352
  %32 = load i16, i16* %arrayidx, align 2, !dbg !1352
  %conv24 = zext i16 %32 to i32, !dbg !1352
  %and = and i32 %conv24, 8192, !dbg !1352
  %tobool = icmp ne i32 %and, 0, !dbg !1352
  br i1 %tobool, label %if.then25, label %if.end26, !dbg !1355

if.then25:                                        ; preds = %for.body
  %33 = bitcast %struct.warc_string_t* %retval to i8*, !dbg !1356
  %34 = bitcast %struct.warc_string_t* %res to i8*, !dbg !1356
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %33, i8* %34, i64 16, i32 8, i1 false), !dbg !1356
  br label %return, !dbg !1357

if.end26:                                         ; preds = %for.body
  br label %for.inc, !dbg !1358

for.inc:                                          ; preds = %if.end26
  %35 = load i8*, i8** %p, align 8, !dbg !1359
  %incdec.ptr27 = getelementptr inbounds i8, i8* %35, i32 1, !dbg !1359
  store i8* %incdec.ptr27, i8** %p, align 8, !dbg !1359
  br label %for.cond, !dbg !1361

for.end:                                          ; preds = %for.cond
  %36 = load i8*, i8** %uri, align 8, !dbg !1362
  %37 = load i8*, i8** %val, align 8, !dbg !1364
  %add.ptr28 = getelementptr inbounds i8, i8* %37, i64 3, !dbg !1365
  %cmp29 = icmp ult i8* %36, %add.ptr28, !dbg !1366
  br i1 %cmp29, label %if.then31, label %if.end32, !dbg !1367

if.then31:                                        ; preds = %for.end
  %38 = bitcast %struct.warc_string_t* %retval to i8*, !dbg !1368
  %39 = bitcast %struct.warc_string_t* %res to i8*, !dbg !1368
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %38, i8* %39, i64 16, i32 8, i1 false), !dbg !1368
  br label %return, !dbg !1369

if.end32:                                         ; preds = %for.end
  %40 = load i8*, i8** %uri, align 8, !dbg !1370
  %add.ptr33 = getelementptr inbounds i8, i8* %40, i64 3, !dbg !1370
  store i8* %add.ptr33, i8** %uri, align 8, !dbg !1370
  %41 = load i8*, i8** %val, align 8, !dbg !1371
  %call34 = call i32 @memcmp(i8* %41, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i32 0, i32 0), i64 4) #8, !dbg !1373
  %cmp35 = icmp eq i32 %call34, 0, !dbg !1374
  br i1 %cmp35, label %if.then37, label %if.else, !dbg !1375

if.then37:                                        ; preds = %if.end32
  br label %if.end58, !dbg !1376

if.else:                                          ; preds = %if.end32
  %42 = load i8*, i8** %val, align 8, !dbg !1378
  %call38 = call i32 @memcmp(i8* %42, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.14, i32 0, i32 0), i64 4) #8, !dbg !1381
  %cmp39 = icmp eq i32 %call38, 0, !dbg !1382
  br i1 %cmp39, label %if.then44, label %lor.lhs.false, !dbg !1383

lor.lhs.false:                                    ; preds = %if.else
  %43 = load i8*, i8** %val, align 8, !dbg !1384
  %call41 = call i32 @memcmp(i8* %43, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.15, i32 0, i32 0), i64 3) #8, !dbg !1385
  %cmp42 = icmp eq i32 %call41, 0, !dbg !1386
  br i1 %cmp42, label %if.then44, label %if.else56, !dbg !1387

if.then44:                                        ; preds = %lor.lhs.false, %if.else
  br label %while.cond45, !dbg !1389

while.cond45:                                     ; preds = %while.body54, %if.then44
  %44 = load i8*, i8** %uri, align 8, !dbg !1391
  %45 = load i8*, i8** %eol, align 8, !dbg !1393
  %cmp46 = icmp ult i8* %44, %45, !dbg !1394
  br i1 %cmp46, label %land.rhs48, label %land.end53, !dbg !1395

land.rhs48:                                       ; preds = %while.cond45
  %46 = load i8*, i8** %uri, align 8, !dbg !1396
  %incdec.ptr49 = getelementptr inbounds i8, i8* %46, i32 1, !dbg !1396
  store i8* %incdec.ptr49, i8** %uri, align 8, !dbg !1396
  %47 = load i8, i8* %46, align 1, !dbg !1398
  %conv50 = sext i8 %47 to i32, !dbg !1398
  %cmp51 = icmp ne i32 %conv50, 47, !dbg !1399
  br label %land.end53

land.end53:                                       ; preds = %land.rhs48, %while.cond45
  %48 = phi i1 [ false, %while.cond45 ], [ %cmp51, %land.rhs48 ]
  br i1 %48, label %while.body54, label %while.end55, !dbg !1400

while.body54:                                     ; preds = %land.end53
  br label %while.cond45, !dbg !1402

while.end55:                                      ; preds = %land.end53
  br label %if.end57, !dbg !1404

if.else56:                                        ; preds = %lor.lhs.false
  %49 = bitcast %struct.warc_string_t* %retval to i8*, !dbg !1405
  %50 = bitcast %struct.warc_string_t* %res to i8*, !dbg !1405
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %49, i8* %50, i64 16, i32 8, i1 false), !dbg !1405
  br label %return, !dbg !1407

if.end57:                                         ; preds = %while.end55
  br label %if.end58

if.end58:                                         ; preds = %if.end57, %if.then37
  %51 = load i8*, i8** %uri, align 8, !dbg !1408
  %str = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %res, i32 0, i32 1, !dbg !1409
  store i8* %51, i8** %str, align 8, !dbg !1410
  %52 = load i8*, i8** %eol, align 8, !dbg !1411
  %53 = load i8*, i8** %uri, align 8, !dbg !1412
  %sub.ptr.lhs.cast59 = ptrtoint i8* %52 to i64, !dbg !1413
  %sub.ptr.rhs.cast60 = ptrtoint i8* %53 to i64, !dbg !1413
  %sub.ptr.sub61 = sub i64 %sub.ptr.lhs.cast59, %sub.ptr.rhs.cast60, !dbg !1413
  %len = getelementptr inbounds %struct.warc_string_t, %struct.warc_string_t* %res, i32 0, i32 0, !dbg !1414
  store i64 %sub.ptr.sub61, i64* %len, align 8, !dbg !1415
  %54 = bitcast %struct.warc_string_t* %retval to i8*, !dbg !1416
  %55 = bitcast %struct.warc_string_t* %res to i8*, !dbg !1416
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %54, i8* %55, i64 16, i32 8, i1 false), !dbg !1416
  br label %return, !dbg !1417

return:                                           ; preds = %if.end58, %if.else56, %if.then31, %if.then25, %if.then18, %if.then4, %if.then
  %56 = bitcast %struct.warc_string_t* %retval to { i64, i8* }*, !dbg !1418
  %57 = load { i64, i8* }, { i64, i8* }* %56, align 8, !dbg !1418
  ret { i64, i8* } %57, !dbg !1418
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #6

; Function Attrs: nounwind
declare i8* @realloc(i8*, i64) #3

; Function Attrs: nounwind uwtable
define internal i64 @_warc_rdmtm(i8* %buf, i64 %bsz) #0 !dbg !385 {
entry:
  %retval = alloca i64, align 8
  %buf.addr = alloca i8*, align 8
  %bsz.addr = alloca i64, align 8
  %val = alloca i8*, align 8
  %eol = alloca i8*, align 8
  %on = alloca i8*, align 8
  %res = alloca i64, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1419, metadata !422), !dbg !1420
  store i64 %bsz, i64* %bsz.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bsz.addr, metadata !1421, metadata !422), !dbg !1422
  call void @llvm.dbg.declare(metadata i8** %val, metadata !1423, metadata !422), !dbg !1424
  call void @llvm.dbg.declare(metadata i8** %eol, metadata !1425, metadata !422), !dbg !1426
  call void @llvm.dbg.declare(metadata i8** %on, metadata !1427, metadata !422), !dbg !1428
  store i8* null, i8** %on, align 8, !dbg !1428
  call void @llvm.dbg.declare(metadata i64* %res, metadata !1429, metadata !422), !dbg !1430
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !1431
  %1 = load i64, i64* %bsz.addr, align 8, !dbg !1433
  %call = call i8* @xmemmem(i8* %0, i64 %1, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @_warc_rdmtm._key, i32 0, i32 0), i64 16), !dbg !1434
  store i8* %call, i8** %val, align 8, !dbg !1435
  %cmp = icmp eq i8* %call, null, !dbg !1436
  br i1 %cmp, label %if.then, label %if.end, !dbg !1437

if.then:                                          ; preds = %entry
  store i64 -1, i64* %retval, align 8, !dbg !1438
  br label %return, !dbg !1438

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %val, align 8, !dbg !1440
  %add.ptr = getelementptr inbounds i8, i8* %2, i64 16, !dbg !1440
  store i8* %add.ptr, i8** %val, align 8, !dbg !1440
  %3 = load i8*, i8** %val, align 8, !dbg !1441
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !1443
  %5 = load i64, i64* %bsz.addr, align 8, !dbg !1444
  %add.ptr1 = getelementptr inbounds i8, i8* %4, i64 %5, !dbg !1445
  %6 = load i8*, i8** %val, align 8, !dbg !1446
  %sub.ptr.lhs.cast = ptrtoint i8* %add.ptr1 to i64, !dbg !1447
  %sub.ptr.rhs.cast = ptrtoint i8* %6 to i64, !dbg !1447
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1447
  %call2 = call i8* @_warc_find_eol(i8* %3, i64 %sub.ptr.sub), !dbg !1448
  store i8* %call2, i8** %eol, align 8, !dbg !1449
  %cmp3 = icmp eq i8* %call2, null, !dbg !1450
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1451

if.then4:                                         ; preds = %if.end
  store i64 -1, i64* %retval, align 8, !dbg !1452
  br label %return, !dbg !1452

if.end5:                                          ; preds = %if.end
  %7 = load i8*, i8** %val, align 8, !dbg !1454
  %call6 = call i64 @xstrpisotime(i8* %7, i8** %on), !dbg !1455
  store i64 %call6, i64* %res, align 8, !dbg !1456
  %8 = load i8*, i8** %on, align 8, !dbg !1457
  %9 = load i8*, i8** %eol, align 8, !dbg !1459
  %cmp7 = icmp ne i8* %8, %9, !dbg !1460
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !1461

if.then8:                                         ; preds = %if.end5
  store i64 -1, i64* %retval, align 8, !dbg !1462
  br label %return, !dbg !1462

if.end9:                                          ; preds = %if.end5
  %10 = load i64, i64* %res, align 8, !dbg !1464
  store i64 %10, i64* %retval, align 8, !dbg !1465
  br label %return, !dbg !1465

return:                                           ; preds = %if.end9, %if.then8, %if.then4, %if.then
  %11 = load i64, i64* %retval, align 8, !dbg !1466
  ret i64 %11, !dbg !1466
}

declare i64 @__archive_read_consume(%struct.archive_read*, i64) #2

declare void @archive_entry_set_filetype(%struct.archive_entry*, i32) #2

declare void @archive_entry_copy_pathname(%struct.archive_entry*, i8*) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_perm(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_ctime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_mtime(%struct.archive_entry*, i64, i64) #2

; Function Attrs: nounwind uwtable
define internal i8* @xmemmem(i8* %hay, i64 %haysize, i8* %needle, i64 %needlesize) #0 !dbg !337 {
entry:
  %retval = alloca i8*, align 8
  %hay.addr = alloca i8*, align 8
  %haysize.addr = alloca i64, align 8
  %needle.addr = alloca i8*, align 8
  %needlesize.addr = alloca i64, align 8
  %eoh = alloca i8*, align 8
  %eon = alloca i8*, align 8
  %hp = alloca i8*, align 8
  %np = alloca i8*, align 8
  %cand = alloca i8*, align 8
  %hsum = alloca i32, align 4
  %nsum = alloca i32, align 4
  %eqp = alloca i32, align 4
  store i8* %hay, i8** %hay.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %hay.addr, metadata !1467, metadata !422), !dbg !1468
  store i64 %haysize, i64* %haysize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %haysize.addr, metadata !1469, metadata !422), !dbg !1470
  store i8* %needle, i8** %needle.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %needle.addr, metadata !1471, metadata !422), !dbg !1472
  store i64 %needlesize, i64* %needlesize.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %needlesize.addr, metadata !1473, metadata !422), !dbg !1474
  call void @llvm.dbg.declare(metadata i8** %eoh, metadata !1475, metadata !422), !dbg !1477
  %0 = load i8*, i8** %hay.addr, align 8, !dbg !1478
  %1 = load i64, i64* %haysize.addr, align 8, !dbg !1479
  %add.ptr = getelementptr inbounds i8, i8* %0, i64 %1, !dbg !1480
  store i8* %add.ptr, i8** %eoh, align 8, !dbg !1477
  call void @llvm.dbg.declare(metadata i8** %eon, metadata !1481, metadata !422), !dbg !1482
  %2 = load i8*, i8** %needle.addr, align 8, !dbg !1483
  %3 = load i64, i64* %needlesize.addr, align 8, !dbg !1484
  %add.ptr1 = getelementptr inbounds i8, i8* %2, i64 %3, !dbg !1485
  store i8* %add.ptr1, i8** %eon, align 8, !dbg !1482
  call void @llvm.dbg.declare(metadata i8** %hp, metadata !1486, metadata !422), !dbg !1487
  call void @llvm.dbg.declare(metadata i8** %np, metadata !1488, metadata !422), !dbg !1489
  call void @llvm.dbg.declare(metadata i8** %cand, metadata !1490, metadata !422), !dbg !1491
  call void @llvm.dbg.declare(metadata i32* %hsum, metadata !1492, metadata !422), !dbg !1493
  call void @llvm.dbg.declare(metadata i32* %nsum, metadata !1494, metadata !422), !dbg !1495
  call void @llvm.dbg.declare(metadata i32* %eqp, metadata !1496, metadata !422), !dbg !1497
  %4 = load i64, i64* %needlesize.addr, align 8, !dbg !1498
  %cmp = icmp eq i64 %4, 0, !dbg !1500
  br i1 %cmp, label %if.then, label %if.else, !dbg !1501

if.then:                                          ; preds = %entry
  %5 = load i8*, i8** %hay.addr, align 8, !dbg !1502
  %call = call i8* @deconst(i8* %5), !dbg !1504
  store i8* %call, i8** %retval, align 8, !dbg !1505
  br label %return, !dbg !1505

if.else:                                          ; preds = %entry
  %6 = load i8*, i8** %hay.addr, align 8, !dbg !1506
  %7 = load i8*, i8** %needle.addr, align 8, !dbg !1508
  %8 = load i8, i8* %7, align 1, !dbg !1509
  %conv = sext i8 %8 to i32, !dbg !1509
  %9 = load i64, i64* %haysize.addr, align 8, !dbg !1510
  %call2 = call i8* @memchr(i8* %6, i32 %conv, i64 %9) #8, !dbg !1511
  store i8* %call2, i8** %hay.addr, align 8, !dbg !1512
  %cmp3 = icmp eq i8* %call2, null, !dbg !1513
  br i1 %cmp3, label %if.then5, label %if.end, !dbg !1514

if.then5:                                         ; preds = %if.else
  store i8* null, i8** %retval, align 8, !dbg !1515
  br label %return, !dbg !1515

if.end:                                           ; preds = %if.else
  br label %if.end6

if.end6:                                          ; preds = %if.end
  %10 = load i8*, i8** %hay.addr, align 8, !dbg !1517
  %add.ptr7 = getelementptr inbounds i8, i8* %10, i64 1, !dbg !1519
  store i8* %add.ptr7, i8** %hp, align 8, !dbg !1520
  %11 = load i8*, i8** %needle.addr, align 8, !dbg !1521
  %add.ptr8 = getelementptr inbounds i8, i8* %11, i64 1, !dbg !1522
  store i8* %add.ptr8, i8** %np, align 8, !dbg !1523
  %12 = load i8*, i8** %hay.addr, align 8, !dbg !1524
  %13 = load i8, i8* %12, align 1, !dbg !1525
  %conv9 = sext i8 %13 to i32, !dbg !1525
  store i32 %conv9, i32* %hsum, align 4, !dbg !1526
  %14 = load i8*, i8** %hay.addr, align 8, !dbg !1527
  %15 = load i8, i8* %14, align 1, !dbg !1528
  %conv10 = sext i8 %15 to i32, !dbg !1528
  store i32 %conv10, i32* %nsum, align 4, !dbg !1529
  store i32 1, i32* %eqp, align 4, !dbg !1530
  br label %for.cond, !dbg !1531

for.cond:                                         ; preds = %for.inc, %if.end6
  %16 = load i8*, i8** %hp, align 8, !dbg !1532
  %17 = load i8*, i8** %eoh, align 8, !dbg !1534
  %cmp11 = icmp ult i8* %16, %17, !dbg !1535
  br i1 %cmp11, label %land.rhs, label %land.end, !dbg !1536

land.rhs:                                         ; preds = %for.cond
  %18 = load i8*, i8** %np, align 8, !dbg !1537
  %19 = load i8*, i8** %eon, align 8, !dbg !1539
  %cmp13 = icmp ult i8* %18, %19, !dbg !1540
  br label %land.end

land.end:                                         ; preds = %land.rhs, %for.cond
  %20 = phi i1 [ false, %for.cond ], [ %cmp13, %land.rhs ]
  br i1 %20, label %for.body, label %for.end, !dbg !1541

for.body:                                         ; preds = %land.end
  br label %for.inc, !dbg !1543

for.inc:                                          ; preds = %for.body
  %21 = load i8*, i8** %hp, align 8, !dbg !1545
  %22 = load i8, i8* %21, align 1, !dbg !1546
  %conv15 = sext i8 %22 to i32, !dbg !1546
  %23 = load i32, i32* %hsum, align 4, !dbg !1547
  %xor = xor i32 %23, %conv15, !dbg !1547
  store i32 %xor, i32* %hsum, align 4, !dbg !1547
  %24 = load i8*, i8** %np, align 8, !dbg !1548
  %25 = load i8, i8* %24, align 1, !dbg !1549
  %conv16 = sext i8 %25 to i32, !dbg !1549
  %26 = load i32, i32* %nsum, align 4, !dbg !1550
  %xor17 = xor i32 %26, %conv16, !dbg !1550
  store i32 %xor17, i32* %nsum, align 4, !dbg !1550
  %27 = load i8*, i8** %hp, align 8, !dbg !1551
  %28 = load i8, i8* %27, align 1, !dbg !1552
  %conv18 = sext i8 %28 to i32, !dbg !1552
  %29 = load i8*, i8** %np, align 8, !dbg !1553
  %30 = load i8, i8* %29, align 1, !dbg !1554
  %conv19 = sext i8 %30 to i32, !dbg !1554
  %cmp20 = icmp eq i32 %conv18, %conv19, !dbg !1555
  %conv21 = zext i1 %cmp20 to i32, !dbg !1555
  %31 = load i32, i32* %eqp, align 4, !dbg !1556
  %and = and i32 %31, %conv21, !dbg !1556
  store i32 %and, i32* %eqp, align 4, !dbg !1556
  %32 = load i8*, i8** %hp, align 8, !dbg !1557
  %incdec.ptr = getelementptr inbounds i8, i8* %32, i32 1, !dbg !1557
  store i8* %incdec.ptr, i8** %hp, align 8, !dbg !1557
  %33 = load i8*, i8** %np, align 8, !dbg !1558
  %incdec.ptr22 = getelementptr inbounds i8, i8* %33, i32 1, !dbg !1558
  store i8* %incdec.ptr22, i8** %np, align 8, !dbg !1558
  br label %for.cond, !dbg !1559

for.end:                                          ; preds = %land.end
  %34 = load i8*, i8** %np, align 8, !dbg !1561
  %35 = load i8*, i8** %eon, align 8, !dbg !1563
  %cmp23 = icmp ult i8* %34, %35, !dbg !1564
  br i1 %cmp23, label %if.then25, label %if.else26, !dbg !1565

if.then25:                                        ; preds = %for.end
  store i8* null, i8** %retval, align 8, !dbg !1566
  br label %return, !dbg !1566

if.else26:                                        ; preds = %for.end
  %36 = load i32, i32* %eqp, align 4, !dbg !1568
  %tobool = icmp ne i32 %36, 0, !dbg !1568
  br i1 %tobool, label %if.then27, label %if.end29, !dbg !1570

if.then27:                                        ; preds = %if.else26
  %37 = load i8*, i8** %hay.addr, align 8, !dbg !1571
  %call28 = call i8* @deconst(i8* %37), !dbg !1573
  store i8* %call28, i8** %retval, align 8, !dbg !1574
  br label %return, !dbg !1574

if.end29:                                         ; preds = %if.else26
  br label %if.end30

if.end30:                                         ; preds = %if.end29
  %38 = load i8*, i8** %hay.addr, align 8, !dbg !1575
  store i8* %38, i8** %cand, align 8, !dbg !1577
  br label %for.cond31, !dbg !1578

for.cond31:                                       ; preds = %for.inc48, %if.end30
  %39 = load i8*, i8** %hp, align 8, !dbg !1579
  %40 = load i8*, i8** %eoh, align 8, !dbg !1582
  %cmp32 = icmp ult i8* %39, %40, !dbg !1583
  br i1 %cmp32, label %for.body34, label %for.end50, !dbg !1584

for.body34:                                       ; preds = %for.cond31
  %41 = load i8*, i8** %cand, align 8, !dbg !1585
  %incdec.ptr35 = getelementptr inbounds i8, i8* %41, i32 1, !dbg !1585
  store i8* %incdec.ptr35, i8** %cand, align 8, !dbg !1585
  %42 = load i8, i8* %41, align 1, !dbg !1587
  %conv36 = sext i8 %42 to i32, !dbg !1587
  %43 = load i32, i32* %hsum, align 4, !dbg !1588
  %xor37 = xor i32 %43, %conv36, !dbg !1588
  store i32 %xor37, i32* %hsum, align 4, !dbg !1588
  %44 = load i8*, i8** %hp, align 8, !dbg !1589
  %45 = load i8, i8* %44, align 1, !dbg !1590
  %conv38 = sext i8 %45 to i32, !dbg !1590
  %46 = load i32, i32* %hsum, align 4, !dbg !1591
  %xor39 = xor i32 %46, %conv38, !dbg !1591
  store i32 %xor39, i32* %hsum, align 4, !dbg !1591
  %47 = load i32, i32* %hsum, align 4, !dbg !1592
  %48 = load i32, i32* %nsum, align 4, !dbg !1594
  %cmp40 = icmp eq i32 %47, %48, !dbg !1595
  br i1 %cmp40, label %land.lhs.true, label %if.end47, !dbg !1596

land.lhs.true:                                    ; preds = %for.body34
  %49 = load i8*, i8** %cand, align 8, !dbg !1597
  %50 = load i8*, i8** %needle.addr, align 8, !dbg !1599
  %51 = load i64, i64* %needlesize.addr, align 8, !dbg !1600
  %sub = sub i64 %51, 1, !dbg !1601
  %call42 = call i32 @memcmp(i8* %49, i8* %50, i64 %sub) #8, !dbg !1602
  %cmp43 = icmp eq i32 %call42, 0, !dbg !1603
  br i1 %cmp43, label %if.then45, label %if.end47, !dbg !1604

if.then45:                                        ; preds = %land.lhs.true
  %52 = load i8*, i8** %cand, align 8, !dbg !1605
  %call46 = call i8* @deconst(i8* %52), !dbg !1607
  store i8* %call46, i8** %retval, align 8, !dbg !1608
  br label %return, !dbg !1608

if.end47:                                         ; preds = %land.lhs.true, %for.body34
  br label %for.inc48, !dbg !1609

for.inc48:                                        ; preds = %if.end47
  %53 = load i8*, i8** %hp, align 8, !dbg !1610
  %incdec.ptr49 = getelementptr inbounds i8, i8* %53, i32 1, !dbg !1610
  store i8* %incdec.ptr49, i8** %hp, align 8, !dbg !1610
  br label %for.cond31, !dbg !1612

for.end50:                                        ; preds = %for.cond31
  store i8* null, i8** %retval, align 8, !dbg !1613
  br label %return, !dbg !1613

return:                                           ; preds = %for.end50, %if.then45, %if.then27, %if.then25, %if.then5, %if.then
  %54 = load i8*, i8** %retval, align 8, !dbg !1614
  ret i8* %54, !dbg !1614
}

; Function Attrs: nounwind uwtable
define internal i8* @deconst(i8* %c) #0 !dbg !341 {
entry:
  %c.addr = alloca i8*, align 8
  store i8* %c, i8** %c.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %c.addr, metadata !1615, metadata !422), !dbg !1616
  %0 = load i8*, i8** %c.addr, align 8, !dbg !1617
  %sub.ptr.lhs.cast = ptrtoint i8* %0 to i64, !dbg !1618
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, 1, !dbg !1618
  %add.ptr = getelementptr inbounds i8, i8* inttoptr (i64 1 to i8*), i64 %sub.ptr.sub, !dbg !1619
  ret i8* %add.ptr, !dbg !1620
}

; Function Attrs: nounwind readonly
declare i8* @memchr(i8*, i32, i64) #4

; Function Attrs: nounwind uwtable
define internal i8* @_warc_find_eol(i8* %buf, i64 %bsz) #0 !dbg !347 {
entry:
  %buf.addr = alloca i8*, align 8
  %bsz.addr = alloca i64, align 8
  %hit = alloca i8*, align 8
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !1621, metadata !422), !dbg !1622
  store i64 %bsz, i64* %bsz.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %bsz.addr, metadata !1623, metadata !422), !dbg !1624
  call void @llvm.dbg.declare(metadata i8** %hit, metadata !1625, metadata !422), !dbg !1626
  %0 = load i8*, i8** %buf.addr, align 8, !dbg !1627
  %1 = load i64, i64* %bsz.addr, align 8, !dbg !1628
  %call = call i8* @xmemmem(i8* %0, i64 %1, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @_warc_find_eol._marker, i32 0, i32 0), i64 2), !dbg !1629
  store i8* %call, i8** %hit, align 8, !dbg !1626
  %2 = load i8*, i8** %hit, align 8, !dbg !1630
  ret i8* %2, !dbg !1631
}

; Function Attrs: nounwind
declare i64 @strtol(i8*, i8**, i32) #3

; Function Attrs: nounwind uwtable
define internal i64 @xstrpisotime(i8* %s, i8** %endptr) #0 !dbg !351 {
entry:
  %s.addr = alloca i8*, align 8
  %endptr.addr = alloca i8**, align 8
  %tm = alloca %struct.tm, align 8
  %res = alloca i64, align 8
  store i8* %s, i8** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %s.addr, metadata !1632, metadata !422), !dbg !1633
  store i8** %endptr, i8*** %endptr.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %endptr.addr, metadata !1634, metadata !422), !dbg !1635
  call void @llvm.dbg.declare(metadata %struct.tm* %tm, metadata !1636, metadata !422), !dbg !1637
  call void @llvm.dbg.declare(metadata i64* %res, metadata !1638, metadata !422), !dbg !1639
  store i64 -1, i64* %res, align 8, !dbg !1639
  %0 = bitcast %struct.tm* %tm to i8*, !dbg !1640
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 56, i32 8, i1 false), !dbg !1640
  br label %while.cond, !dbg !1641

while.cond:                                       ; preds = %while.body, %entry
  %1 = load i8*, i8** %s.addr, align 8, !dbg !1642
  %2 = load i8, i8* %1, align 1, !dbg !1644
  %conv = sext i8 %2 to i32, !dbg !1644
  %cmp = icmp eq i32 %conv, 32, !dbg !1645
  br i1 %cmp, label %lor.end, label %lor.rhs, !dbg !1646

lor.rhs:                                          ; preds = %while.cond
  %3 = load i8*, i8** %s.addr, align 8, !dbg !1647
  %4 = load i8, i8* %3, align 1, !dbg !1649
  %conv2 = sext i8 %4 to i32, !dbg !1649
  %cmp3 = icmp eq i32 %conv2, 9, !dbg !1650
  br label %lor.end, !dbg !1651

lor.end:                                          ; preds = %lor.rhs, %while.cond
  %5 = phi i1 [ true, %while.cond ], [ %cmp3, %lor.rhs ]
  br i1 %5, label %while.body, label %while.end, !dbg !1652

while.body:                                       ; preds = %lor.end
  %6 = load i8*, i8** %s.addr, align 8, !dbg !1654
  %incdec.ptr = getelementptr inbounds i8, i8* %6, i32 1, !dbg !1654
  store i8* %incdec.ptr, i8** %s.addr, align 8, !dbg !1654
  br label %while.cond, !dbg !1655

while.end:                                        ; preds = %lor.end
  %7 = load i8*, i8** %s.addr, align 8, !dbg !1657
  %call = call i32 @strtoi_lim(i8* %7, i8** %s.addr, i32 1583, i32 4095), !dbg !1659
  %tm_year = getelementptr inbounds %struct.tm, %struct.tm* %tm, i32 0, i32 5, !dbg !1660
  store i32 %call, i32* %tm_year, align 4, !dbg !1661
  %cmp5 = icmp slt i32 %call, 0, !dbg !1662
  br i1 %cmp5, label %if.then, label %lor.lhs.false, !dbg !1663

lor.lhs.false:                                    ; preds = %while.end
  %8 = load i8*, i8** %s.addr, align 8, !dbg !1664
  %incdec.ptr7 = getelementptr inbounds i8, i8* %8, i32 1, !dbg !1664
  store i8* %incdec.ptr7, i8** %s.addr, align 8, !dbg !1664
  %9 = load i8, i8* %8, align 1, !dbg !1666
  %conv8 = sext i8 %9 to i32, !dbg !1666
  %cmp9 = icmp ne i32 %conv8, 45, !dbg !1667
  br i1 %cmp9, label %if.then, label %if.end, !dbg !1668

if.then:                                          ; preds = %lor.lhs.false, %while.end
  br label %out, !dbg !1669

if.end:                                           ; preds = %lor.lhs.false
  %10 = load i8*, i8** %s.addr, align 8, !dbg !1671
  %call11 = call i32 @strtoi_lim(i8* %10, i8** %s.addr, i32 1, i32 12), !dbg !1673
  %tm_mon = getelementptr inbounds %struct.tm, %struct.tm* %tm, i32 0, i32 4, !dbg !1674
  store i32 %call11, i32* %tm_mon, align 8, !dbg !1675
  %cmp12 = icmp slt i32 %call11, 0, !dbg !1676
  br i1 %cmp12, label %if.then19, label %lor.lhs.false14, !dbg !1677

lor.lhs.false14:                                  ; preds = %if.end
  %11 = load i8*, i8** %s.addr, align 8, !dbg !1678
  %incdec.ptr15 = getelementptr inbounds i8, i8* %11, i32 1, !dbg !1678
  store i8* %incdec.ptr15, i8** %s.addr, align 8, !dbg !1678
  %12 = load i8, i8* %11, align 1, !dbg !1680
  %conv16 = sext i8 %12 to i32, !dbg !1680
  %cmp17 = icmp ne i32 %conv16, 45, !dbg !1681
  br i1 %cmp17, label %if.then19, label %if.end20, !dbg !1682

if.then19:                                        ; preds = %lor.lhs.false14, %if.end
  br label %out, !dbg !1683

if.end20:                                         ; preds = %lor.lhs.false14
  %13 = load i8*, i8** %s.addr, align 8, !dbg !1685
  %call21 = call i32 @strtoi_lim(i8* %13, i8** %s.addr, i32 1, i32 31), !dbg !1687
  %tm_mday = getelementptr inbounds %struct.tm, %struct.tm* %tm, i32 0, i32 3, !dbg !1688
  store i32 %call21, i32* %tm_mday, align 4, !dbg !1689
  %cmp22 = icmp slt i32 %call21, 0, !dbg !1690
  br i1 %cmp22, label %if.then29, label %lor.lhs.false24, !dbg !1691

lor.lhs.false24:                                  ; preds = %if.end20
  %14 = load i8*, i8** %s.addr, align 8, !dbg !1692
  %incdec.ptr25 = getelementptr inbounds i8, i8* %14, i32 1, !dbg !1692
  store i8* %incdec.ptr25, i8** %s.addr, align 8, !dbg !1692
  %15 = load i8, i8* %14, align 1, !dbg !1694
  %conv26 = sext i8 %15 to i32, !dbg !1694
  %cmp27 = icmp ne i32 %conv26, 84, !dbg !1695
  br i1 %cmp27, label %if.then29, label %if.end30, !dbg !1696

if.then29:                                        ; preds = %lor.lhs.false24, %if.end20
  br label %out, !dbg !1697

if.end30:                                         ; preds = %lor.lhs.false24
  %16 = load i8*, i8** %s.addr, align 8, !dbg !1699
  %call31 = call i32 @strtoi_lim(i8* %16, i8** %s.addr, i32 0, i32 23), !dbg !1701
  %tm_hour = getelementptr inbounds %struct.tm, %struct.tm* %tm, i32 0, i32 2, !dbg !1702
  store i32 %call31, i32* %tm_hour, align 8, !dbg !1703
  %cmp32 = icmp slt i32 %call31, 0, !dbg !1704
  br i1 %cmp32, label %if.then39, label %lor.lhs.false34, !dbg !1705

lor.lhs.false34:                                  ; preds = %if.end30
  %17 = load i8*, i8** %s.addr, align 8, !dbg !1706
  %incdec.ptr35 = getelementptr inbounds i8, i8* %17, i32 1, !dbg !1706
  store i8* %incdec.ptr35, i8** %s.addr, align 8, !dbg !1706
  %18 = load i8, i8* %17, align 1, !dbg !1708
  %conv36 = sext i8 %18 to i32, !dbg !1708
  %cmp37 = icmp ne i32 %conv36, 58, !dbg !1709
  br i1 %cmp37, label %if.then39, label %if.end40, !dbg !1710

if.then39:                                        ; preds = %lor.lhs.false34, %if.end30
  br label %out, !dbg !1711

if.end40:                                         ; preds = %lor.lhs.false34
  %19 = load i8*, i8** %s.addr, align 8, !dbg !1713
  %call41 = call i32 @strtoi_lim(i8* %19, i8** %s.addr, i32 0, i32 59), !dbg !1715
  %tm_min = getelementptr inbounds %struct.tm, %struct.tm* %tm, i32 0, i32 1, !dbg !1716
  store i32 %call41, i32* %tm_min, align 4, !dbg !1717
  %cmp42 = icmp slt i32 %call41, 0, !dbg !1718
  br i1 %cmp42, label %if.then49, label %lor.lhs.false44, !dbg !1719

lor.lhs.false44:                                  ; preds = %if.end40
  %20 = load i8*, i8** %s.addr, align 8, !dbg !1720
  %incdec.ptr45 = getelementptr inbounds i8, i8* %20, i32 1, !dbg !1720
  store i8* %incdec.ptr45, i8** %s.addr, align 8, !dbg !1720
  %21 = load i8, i8* %20, align 1, !dbg !1722
  %conv46 = sext i8 %21 to i32, !dbg !1722
  %cmp47 = icmp ne i32 %conv46, 58, !dbg !1723
  br i1 %cmp47, label %if.then49, label %if.end50, !dbg !1724

if.then49:                                        ; preds = %lor.lhs.false44, %if.end40
  br label %out, !dbg !1725

if.end50:                                         ; preds = %lor.lhs.false44
  %22 = load i8*, i8** %s.addr, align 8, !dbg !1727
  %call51 = call i32 @strtoi_lim(i8* %22, i8** %s.addr, i32 0, i32 60), !dbg !1729
  %tm_sec = getelementptr inbounds %struct.tm, %struct.tm* %tm, i32 0, i32 0, !dbg !1730
  store i32 %call51, i32* %tm_sec, align 8, !dbg !1731
  %cmp52 = icmp slt i32 %call51, 0, !dbg !1732
  br i1 %cmp52, label %if.then59, label %lor.lhs.false54, !dbg !1733

lor.lhs.false54:                                  ; preds = %if.end50
  %23 = load i8*, i8** %s.addr, align 8, !dbg !1734
  %incdec.ptr55 = getelementptr inbounds i8, i8* %23, i32 1, !dbg !1734
  store i8* %incdec.ptr55, i8** %s.addr, align 8, !dbg !1734
  %24 = load i8, i8* %23, align 1, !dbg !1736
  %conv56 = sext i8 %24 to i32, !dbg !1736
  %cmp57 = icmp ne i32 %conv56, 90, !dbg !1737
  br i1 %cmp57, label %if.then59, label %if.end60, !dbg !1738

if.then59:                                        ; preds = %lor.lhs.false54, %if.end50
  br label %out, !dbg !1739

if.end60:                                         ; preds = %lor.lhs.false54
  %tm_year61 = getelementptr inbounds %struct.tm, %struct.tm* %tm, i32 0, i32 5, !dbg !1741
  %25 = load i32, i32* %tm_year61, align 4, !dbg !1742
  %sub = sub nsw i32 %25, 1900, !dbg !1742
  store i32 %sub, i32* %tm_year61, align 4, !dbg !1742
  %tm_mon62 = getelementptr inbounds %struct.tm, %struct.tm* %tm, i32 0, i32 4, !dbg !1743
  %26 = load i32, i32* %tm_mon62, align 8, !dbg !1744
  %dec = add nsw i32 %26, -1, !dbg !1744
  store i32 %dec, i32* %tm_mon62, align 8, !dbg !1744
  %call63 = call i64 @time_from_tm(%struct.tm* %tm), !dbg !1745
  store i64 %call63, i64* %res, align 8, !dbg !1746
  br label %out, !dbg !1747

out:                                              ; preds = %if.end60, %if.then59, %if.then49, %if.then39, %if.then29, %if.then19, %if.then
  %27 = load i8**, i8*** %endptr.addr, align 8, !dbg !1748
  %cmp64 = icmp ne i8** %27, null, !dbg !1750
  br i1 %cmp64, label %if.then66, label %if.end68, !dbg !1751

if.then66:                                        ; preds = %out
  %28 = load i8*, i8** %s.addr, align 8, !dbg !1752
  %call67 = call i8* @deconst(i8* %28), !dbg !1754
  %29 = load i8**, i8*** %endptr.addr, align 8, !dbg !1755
  store i8* %call67, i8** %29, align 8, !dbg !1756
  br label %if.end68, !dbg !1757

if.end68:                                         ; preds = %if.then66, %out
  %30 = load i64, i64* %res, align 8, !dbg !1758
  ret i64 %30, !dbg !1759
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

; Function Attrs: nounwind uwtable
define internal i32 @strtoi_lim(i8* %str, i8** %ep, i32 %llim, i32 %ulim) #0 !dbg !355 {
entry:
  %str.addr = alloca i8*, align 8
  %ep.addr = alloca i8**, align 8
  %llim.addr = alloca i32, align 4
  %ulim.addr = alloca i32, align 4
  %res = alloca i32, align 4
  %sp = alloca i8*, align 8
  %rulim = alloca i32, align 4
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !1760, metadata !422), !dbg !1761
  store i8** %ep, i8*** %ep.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %ep.addr, metadata !1762, metadata !422), !dbg !1763
  store i32 %llim, i32* %llim.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %llim.addr, metadata !1764, metadata !422), !dbg !1765
  store i32 %ulim, i32* %ulim.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %ulim.addr, metadata !1766, metadata !422), !dbg !1767
  call void @llvm.dbg.declare(metadata i32* %res, metadata !1768, metadata !422), !dbg !1769
  store i32 0, i32* %res, align 4, !dbg !1769
  call void @llvm.dbg.declare(metadata i8** %sp, metadata !1770, metadata !422), !dbg !1771
  call void @llvm.dbg.declare(metadata i32* %rulim, metadata !1772, metadata !422), !dbg !1773
  %0 = load i8*, i8** %str.addr, align 8, !dbg !1774
  store i8* %0, i8** %sp, align 8, !dbg !1776
  %1 = load i32, i32* %ulim.addr, align 4, !dbg !1777
  %cmp = icmp sgt i32 %1, 10, !dbg !1778
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1777

cond.true:                                        ; preds = %entry
  %2 = load i32, i32* %ulim.addr, align 4, !dbg !1779
  br label %cond.end, !dbg !1781

cond.false:                                       ; preds = %entry
  br label %cond.end, !dbg !1782

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi i32 [ %2, %cond.true ], [ 10, %cond.false ], !dbg !1784
  store i32 %cond, i32* %rulim, align 4, !dbg !1786
  br label %for.cond, !dbg !1787

for.cond:                                         ; preds = %for.inc, %cond.end
  %3 = load i32, i32* %res, align 4, !dbg !1788
  %mul = mul nsw i32 %3, 10, !dbg !1790
  %4 = load i32, i32* %ulim.addr, align 4, !dbg !1791
  %cmp1 = icmp sle i32 %mul, %4, !dbg !1792
  br i1 %cmp1, label %land.lhs.true, label %land.end, !dbg !1793

land.lhs.true:                                    ; preds = %for.cond
  %5 = load i32, i32* %rulim, align 4, !dbg !1794
  %tobool = icmp ne i32 %5, 0, !dbg !1794
  br i1 %tobool, label %land.lhs.true2, label %land.end, !dbg !1796

land.lhs.true2:                                   ; preds = %land.lhs.true
  %6 = load i8*, i8** %sp, align 8, !dbg !1797
  %7 = load i8, i8* %6, align 1, !dbg !1799
  %conv = sext i8 %7 to i32, !dbg !1799
  %cmp3 = icmp sge i32 %conv, 48, !dbg !1800
  br i1 %cmp3, label %land.rhs, label %land.end, !dbg !1801

land.rhs:                                         ; preds = %land.lhs.true2
  %8 = load i8*, i8** %sp, align 8, !dbg !1802
  %9 = load i8, i8* %8, align 1, !dbg !1804
  %conv5 = sext i8 %9 to i32, !dbg !1804
  %cmp6 = icmp sle i32 %conv5, 57, !dbg !1805
  br label %land.end

land.end:                                         ; preds = %land.rhs, %land.lhs.true2, %land.lhs.true, %for.cond
  %10 = phi i1 [ false, %land.lhs.true2 ], [ false, %land.lhs.true ], [ false, %for.cond ], [ %cmp6, %land.rhs ]
  br i1 %10, label %for.body, label %for.end, !dbg !1806

for.body:                                         ; preds = %land.end
  %11 = load i32, i32* %res, align 4, !dbg !1808
  %mul8 = mul nsw i32 %11, 10, !dbg !1808
  store i32 %mul8, i32* %res, align 4, !dbg !1808
  %12 = load i8*, i8** %sp, align 8, !dbg !1810
  %13 = load i8, i8* %12, align 1, !dbg !1811
  %conv9 = sext i8 %13 to i32, !dbg !1811
  %sub = sub nsw i32 %conv9, 48, !dbg !1812
  %14 = load i32, i32* %res, align 4, !dbg !1813
  %add = add nsw i32 %14, %sub, !dbg !1813
  store i32 %add, i32* %res, align 4, !dbg !1813
  br label %for.inc, !dbg !1814

for.inc:                                          ; preds = %for.body
  %15 = load i8*, i8** %sp, align 8, !dbg !1815
  %incdec.ptr = getelementptr inbounds i8, i8* %15, i32 1, !dbg !1815
  store i8* %incdec.ptr, i8** %sp, align 8, !dbg !1815
  %16 = load i32, i32* %rulim, align 4, !dbg !1816
  %div = sdiv i32 %16, 10, !dbg !1816
  store i32 %div, i32* %rulim, align 4, !dbg !1816
  br label %for.cond, !dbg !1817

for.end:                                          ; preds = %land.end
  %17 = load i8*, i8** %sp, align 8, !dbg !1819
  %18 = load i8*, i8** %str.addr, align 8, !dbg !1821
  %cmp10 = icmp eq i8* %17, %18, !dbg !1822
  br i1 %cmp10, label %if.then, label %if.else, !dbg !1823

if.then:                                          ; preds = %for.end
  store i32 -1, i32* %res, align 4, !dbg !1824
  br label %if.end17, !dbg !1826

if.else:                                          ; preds = %for.end
  %19 = load i32, i32* %res, align 4, !dbg !1827
  %20 = load i32, i32* %llim.addr, align 4, !dbg !1830
  %cmp12 = icmp slt i32 %19, %20, !dbg !1831
  br i1 %cmp12, label %if.then16, label %lor.lhs.false, !dbg !1832

lor.lhs.false:                                    ; preds = %if.else
  %21 = load i32, i32* %res, align 4, !dbg !1833
  %22 = load i32, i32* %ulim.addr, align 4, !dbg !1835
  %cmp14 = icmp sgt i32 %21, %22, !dbg !1836
  br i1 %cmp14, label %if.then16, label %if.end, !dbg !1837

if.then16:                                        ; preds = %lor.lhs.false, %if.else
  store i32 -2, i32* %res, align 4, !dbg !1838
  br label %if.end, !dbg !1840

if.end:                                           ; preds = %if.then16, %lor.lhs.false
  br label %if.end17

if.end17:                                         ; preds = %if.end, %if.then
  %23 = load i8*, i8** %sp, align 8, !dbg !1841
  %24 = load i8**, i8*** %ep.addr, align 8, !dbg !1842
  store i8* %23, i8** %24, align 8, !dbg !1843
  %25 = load i32, i32* %res, align 4, !dbg !1844
  ret i32 %25, !dbg !1845
}

; Function Attrs: nounwind uwtable
define internal i64 @time_from_tm(%struct.tm* %t) #0 !dbg !359 {
entry:
  %t.addr = alloca %struct.tm*, align 8
  store %struct.tm* %t, %struct.tm** %t.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.tm** %t.addr, metadata !1846, metadata !422), !dbg !1847
  %0 = load %struct.tm*, %struct.tm** %t.addr, align 8, !dbg !1848
  %call = call i64 @timegm(%struct.tm* %0) #7, !dbg !1849
  ret i64 %call, !dbg !1850
}

; Function Attrs: nounwind
declare i64 @timegm(%struct.tm*) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!418, !419}
!llvm.ident = !{!420}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !30, subprograms: !325, globals: !388)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_warc.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{!3, !18}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 46, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/usr/include/ctype.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17}
!6 = !DIEnumerator(name: "_ISupper", value: 256)
!7 = !DIEnumerator(name: "_ISlower", value: 512)
!8 = !DIEnumerator(name: "_ISalpha", value: 1024)
!9 = !DIEnumerator(name: "_ISdigit", value: 2048)
!10 = !DIEnumerator(name: "_ISxdigit", value: 4096)
!11 = !DIEnumerator(name: "_ISspace", value: 8192)
!12 = !DIEnumerator(name: "_ISprint", value: 16384)
!13 = !DIEnumerator(name: "_ISgraph", value: 32768)
!14 = !DIEnumerator(name: "_ISblank", value: 1)
!15 = !DIEnumerator(name: "_IScntrl", value: 2)
!16 = !DIEnumerator(name: "_ISpunct", value: 4)
!17 = !DIEnumerator(name: "_ISalnum", value: 8)
!18 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !1, line: 75, size: 32, align: 32, elements: !19)
!19 = !{!20, !21, !22, !23, !24, !25, !26, !27, !28, !29}
!20 = !DIEnumerator(name: "WT_NONE", value: 0)
!21 = !DIEnumerator(name: "WT_INFO", value: 1)
!22 = !DIEnumerator(name: "WT_META", value: 2)
!23 = !DIEnumerator(name: "WT_RSRC", value: 3)
!24 = !DIEnumerator(name: "WT_REQ", value: 4)
!25 = !DIEnumerator(name: "WT_RSP", value: 5)
!26 = !DIEnumerator(name: "WT_RVIS", value: 6)
!27 = !DIEnumerator(name: "WT_CONV", value: 7)
!28 = !DIEnumerator(name: "WT_CONT", value: 8)
!29 = !DIEnumerator(name: "LAST_WT", value: 9)
!30 = !{!31, !149, !50, !318, !319, !322, !122, !107, !72}
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read", file: !33, line: 159, size: 20288, align: 64, elements: !34)
!33 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!34 = !{!35, !137, !138, !139, !140, !141, !185, !249, !250, !251, !252, !253, !254, !287, !289, !299, !300}
!35 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !32, file: !33, line: 160, baseType: !36, size: 1280, align: 64)
!36 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !37, line: 89, size: 1280, align: 64, elements: !38)
!37 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!38 = !{!39, !41, !42, !110, !111, !112, !113, !114, !115, !116, !117, !125, !126, !127, !128, !131, !132, !133, !134, !135, !136}
!39 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !36, file: !37, line: 96, baseType: !40, size: 32, align: 32)
!40 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!41 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !36, file: !37, line: 97, baseType: !40, size: 32, align: 32, offset: 32)
!42 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !36, file: !37, line: 103, baseType: !43, size: 64, align: 64, offset: 64)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !37, line: 63, size: 832, align: 64, elements: !45)
!45 = !{!46, !52, !53, !60, !61, !75, !81, !86, !87, !94, !95, !99, !103}
!46 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !44, file: !37, line: 64, baseType: !47, size: 64, align: 64)
!47 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!48 = !DISubroutineType(types: !49)
!49 = !{!50, !51}
!50 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!51 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !44, file: !37, line: 65, baseType: !47, size: 64, align: 64, offset: 64)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !44, file: !37, line: 66, baseType: !54, size: 64, align: 64, offset: 128)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DISubroutineType(types: !56)
!56 = !{!50, !51, !57}
!57 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!58 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !59, line: 180, flags: DIFlagFwdDecl)
!59 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !44, file: !37, line: 68, baseType: !47, size: 64, align: 64, offset: 192)
!61 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !44, file: !37, line: 69, baseType: !62, size: 64, align: 64, offset: 256)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64, align: 64)
!63 = !DISubroutineType(types: !64)
!64 = !{!65, !51, !70, !72}
!65 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !66, line: 109, baseType: !67)
!66 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!67 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !68, line: 172, baseType: !69)
!68 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!69 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !71, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!72 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !73, line: 62, baseType: !74)
!73 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!74 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !44, file: !37, line: 71, baseType: !76, size: 64, align: 64, offset: 320)
!76 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !77, size: 64, align: 64)
!77 = !DISubroutineType(types: !78)
!78 = !{!65, !51, !70, !72, !79}
!79 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !80, line: 40, baseType: !69)
!80 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!81 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !44, file: !37, line: 74, baseType: !82, size: 64, align: 64, offset: 384)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DISubroutineType(types: !84)
!84 = !{!50, !51, !85}
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !44, file: !37, line: 76, baseType: !54, size: 64, align: 64, offset: 448)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !44, file: !37, line: 78, baseType: !88, size: 64, align: 64, offset: 512)
!88 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !89, size: 64, align: 64)
!89 = !DISubroutineType(types: !90)
!90 = !{!50, !51, !91, !92, !93}
!91 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!92 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !72, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !44, file: !37, line: 81, baseType: !47, size: 64, align: 64, offset: 576)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !44, file: !37, line: 82, baseType: !96, size: 64, align: 64, offset: 640)
!96 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !97, size: 64, align: 64)
!97 = !DISubroutineType(types: !98)
!98 = !{!79, !51, !50}
!99 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !44, file: !37, line: 83, baseType: !100, size: 64, align: 64, offset: 704)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DISubroutineType(types: !102)
!102 = !{!50, !51, !50}
!103 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !44, file: !37, line: 84, baseType: !104, size: 64, align: 64, offset: 768)
!104 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !105, size: 64, align: 64)
!105 = !DISubroutineType(types: !106)
!106 = !{!107, !51, !50}
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64, align: 64)
!108 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !109)
!109 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !36, file: !37, line: 105, baseType: !50, size: 32, align: 32, offset: 128)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !36, file: !37, line: 106, baseType: !107, size: 64, align: 64, offset: 192)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !36, file: !37, line: 108, baseType: !50, size: 32, align: 32, offset: 256)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !36, file: !37, line: 109, baseType: !107, size: 64, align: 64, offset: 320)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !36, file: !37, line: 112, baseType: !50, size: 32, align: 32, offset: 384)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !36, file: !37, line: 114, baseType: !50, size: 32, align: 32, offset: 416)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !36, file: !37, line: 115, baseType: !107, size: 64, align: 64, offset: 448)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !36, file: !37, line: 116, baseType: !118, size: 192, align: 64, offset: 512)
!118 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !119, line: 58, size: 192, align: 64, elements: !120)
!119 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!120 = !{!121, !123, !124}
!121 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !118, file: !119, line: 59, baseType: !122, size: 64, align: 64)
!122 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !118, file: !119, line: 60, baseType: !72, size: 64, align: 64, offset: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !118, file: !119, line: 61, baseType: !72, size: 64, align: 64, offset: 128)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !36, file: !37, line: 118, baseType: !122, size: 64, align: 64, offset: 704)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !36, file: !37, line: 119, baseType: !40, size: 32, align: 32, offset: 768)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !36, file: !37, line: 120, baseType: !40, size: 32, align: 32, offset: 800)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !36, file: !37, line: 121, baseType: !129, size: 64, align: 64, offset: 832)
!129 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!130 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !119, line: 70, flags: DIFlagFwdDecl)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !36, file: !37, line: 127, baseType: !107, size: 64, align: 64, offset: 896)
!132 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !36, file: !37, line: 128, baseType: !79, size: 64, align: 64, offset: 960)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !36, file: !37, line: 129, baseType: !79, size: 64, align: 64, offset: 1024)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !36, file: !37, line: 130, baseType: !72, size: 64, align: 64, offset: 1088)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !36, file: !37, line: 137, baseType: !109, size: 8, align: 8, offset: 1152)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !36, file: !37, line: 138, baseType: !72, size: 64, align: 64, offset: 1216)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !32, file: !33, line: 162, baseType: !57, size: 64, align: 64, offset: 1280)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !32, file: !33, line: 165, baseType: !50, size: 32, align: 32, offset: 1344)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !32, file: !33, line: 166, baseType: !79, size: 64, align: 64, offset: 1408)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !32, file: !33, line: 167, baseType: !79, size: 64, align: 64, offset: 1472)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "client", scope: !32, file: !33, line: 170, baseType: !142, size: 576, align: 64, offset: 1536)
!142 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_client", file: !33, line: 134, size: 576, align: 64, elements: !143)
!143 = !{!144, !150, !156, !162, !167, !170, !175, !176, !177, !178}
!144 = !DIDerivedType(tag: DW_TAG_member, name: "opener", scope: !142, file: !33, line: 135, baseType: !145, size: 64, align: 64)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !59, line: 241, baseType: !147)
!147 = !DISubroutineType(types: !148)
!148 = !{!50, !51, !149}
!149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "reader", scope: !142, file: !33, line: 136, baseType: !151, size: 64, align: 64, offset: 64)
!151 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !152, size: 64, align: 64)
!152 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_read_callback", file: !59, line: 218, baseType: !153)
!153 = !DISubroutineType(types: !154)
!154 = !{!155, !51, !149, !91}
!155 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !59, line: 95, baseType: !65)
!156 = !DIDerivedType(tag: DW_TAG_member, name: "skipper", scope: !142, file: !33, line: 137, baseType: !157, size: 64, align: 64, offset: 128)
!157 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64, align: 64)
!158 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_skip_callback", file: !59, line: 226, baseType: !159)
!159 = !DISubroutineType(types: !160)
!160 = !{!161, !51, !149, !161}
!161 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !59, line: 73, baseType: !79)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "seeker", scope: !142, file: !33, line: 138, baseType: !163, size: 64, align: 64, offset: 192)
!163 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !164, size: 64, align: 64)
!164 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_seek_callback", file: !59, line: 233, baseType: !165)
!165 = !DISubroutineType(types: !166)
!166 = !{!161, !51, !149, !161, !50}
!167 = !DIDerivedType(tag: DW_TAG_member, name: "closer", scope: !142, file: !33, line: 139, baseType: !168, size: 64, align: 64, offset: 256)
!168 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !169, size: 64, align: 64)
!169 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !59, line: 243, baseType: !147)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "switcher", scope: !142, file: !33, line: 140, baseType: !171, size: 64, align: 64, offset: 320)
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !172, size: 64, align: 64)
!172 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_switch_callback", file: !59, line: 249, baseType: !173)
!173 = !DISubroutineType(types: !174)
!174 = !{!50, !51, !149, !149}
!175 = !DIDerivedType(tag: DW_TAG_member, name: "nodes", scope: !142, file: !33, line: 141, baseType: !40, size: 32, align: 32, offset: 384)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "cursor", scope: !142, file: !33, line: 142, baseType: !40, size: 32, align: 32, offset: 416)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !142, file: !33, line: 143, baseType: !79, size: 64, align: 64, offset: 448)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "dataset", scope: !142, file: !33, line: 144, baseType: !179, size: 64, align: 64, offset: 512)
!179 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!180 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_data_node", file: !33, line: 129, size: 192, align: 64, elements: !181)
!181 = !{!182, !183, !184}
!182 = !DIDerivedType(tag: DW_TAG_member, name: "begin_position", scope: !180, file: !33, line: 130, baseType: !79, size: 64, align: 64)
!183 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !180, file: !33, line: 131, baseType: !79, size: 64, align: 64, offset: 64)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !180, file: !33, line: 132, baseType: !149, size: 64, align: 64, offset: 128)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "bidders", scope: !32, file: !33, line: 173, baseType: !186, size: 6144, align: 64, offset: 2112)
!186 = !DICompositeType(tag: DW_TAG_array_type, baseType: !187, size: 6144, align: 64, elements: !247)
!187 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter_bidder", file: !33, line: 60, size: 384, align: 64, elements: !188)
!188 = !{!189, !190, !191, !238, !239, !243}
!189 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !187, file: !33, line: 62, baseType: !149, size: 64, align: 64)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !187, file: !33, line: 64, baseType: !107, size: 64, align: 64, offset: 64)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !187, file: !33, line: 66, baseType: !192, size: 64, align: 64, offset: 128)
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DISubroutineType(types: !194)
!194 = !{!50, !195, !196}
!195 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!196 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !197, size: 64, align: 64)
!197 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter", file: !33, line: 82, size: 1408, align: 64, elements: !198)
!198 = !{!199, !200, !201, !202, !203, !207, !211, !215, !219, !220, !224, !225, !226, !227, !228, !229, !230, !231, !232, !233, !234, !235, !236, !237}
!199 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !197, file: !33, line: 83, baseType: !79, size: 64, align: 64)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "bidder", scope: !197, file: !33, line: 86, baseType: !195, size: 64, align: 64, offset: 64)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "upstream", scope: !197, file: !33, line: 87, baseType: !196, size: 64, align: 64, offset: 128)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !197, file: !33, line: 88, baseType: !31, size: 64, align: 64, offset: 192)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !197, file: !33, line: 90, baseType: !204, size: 64, align: 64, offset: 256)
!204 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !205, size: 64, align: 64)
!205 = !DISubroutineType(types: !206)
!206 = !{!50, !196}
!207 = !DIDerivedType(tag: DW_TAG_member, name: "read", scope: !197, file: !33, line: 92, baseType: !208, size: 64, align: 64, offset: 320)
!208 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !209, size: 64, align: 64)
!209 = !DISubroutineType(types: !210)
!210 = !{!65, !196, !91}
!211 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !197, file: !33, line: 94, baseType: !212, size: 64, align: 64, offset: 384)
!212 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !213, size: 64, align: 64)
!213 = !DISubroutineType(types: !214)
!214 = !{!79, !196, !79}
!215 = !DIDerivedType(tag: DW_TAG_member, name: "seek", scope: !197, file: !33, line: 96, baseType: !216, size: 64, align: 64, offset: 448)
!216 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !217, size: 64, align: 64)
!217 = !DISubroutineType(types: !218)
!218 = !{!79, !196, !79, !50}
!219 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !197, file: !33, line: 98, baseType: !204, size: 64, align: 64, offset: 512)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "sswitch", scope: !197, file: !33, line: 100, baseType: !221, size: 64, align: 64, offset: 576)
!221 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !222, size: 64, align: 64)
!222 = !DISubroutineType(types: !223)
!223 = !{!50, !196, !40}
!224 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !197, file: !33, line: 102, baseType: !149, size: 64, align: 64, offset: 640)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !197, file: !33, line: 104, baseType: !107, size: 64, align: 64, offset: 704)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !197, file: !33, line: 105, baseType: !50, size: 32, align: 32, offset: 768)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !197, file: !33, line: 108, baseType: !122, size: 64, align: 64, offset: 832)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !197, file: !33, line: 109, baseType: !72, size: 64, align: 64, offset: 896)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !197, file: !33, line: 110, baseType: !122, size: 64, align: 64, offset: 960)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !197, file: !33, line: 111, baseType: !72, size: 64, align: 64, offset: 1024)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "client_buff", scope: !197, file: !33, line: 112, baseType: !70, size: 64, align: 64, offset: 1088)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "client_total", scope: !197, file: !33, line: 113, baseType: !72, size: 64, align: 64, offset: 1152)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "client_next", scope: !197, file: !33, line: 114, baseType: !107, size: 64, align: 64, offset: 1216)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "client_avail", scope: !197, file: !33, line: 115, baseType: !72, size: 64, align: 64, offset: 1280)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_file", scope: !197, file: !33, line: 116, baseType: !109, size: 8, align: 8, offset: 1344)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "closed", scope: !197, file: !33, line: 117, baseType: !109, size: 8, align: 8, offset: 1352)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "fatal", scope: !197, file: !33, line: 118, baseType: !109, size: 8, align: 8, offset: 1360)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !187, file: !33, line: 69, baseType: !204, size: 64, align: 64, offset: 192)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !187, file: !33, line: 71, baseType: !240, size: 64, align: 64, offset: 256)
!240 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !241, size: 64, align: 64)
!241 = !DISubroutineType(types: !242)
!242 = !{!50, !195, !107, !107}
!243 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !187, file: !33, line: 74, baseType: !244, size: 64, align: 64, offset: 320)
!244 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !245, size: 64, align: 64)
!245 = !DISubroutineType(types: !246)
!246 = !{!50, !195}
!247 = !{!248}
!248 = !DISubrange(count: 16)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !32, file: !33, line: 176, baseType: !196, size: 64, align: 64, offset: 8256)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "bypass_filter_bidding", scope: !32, file: !33, line: 179, baseType: !50, size: 32, align: 32, offset: 8320)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "header_position", scope: !32, file: !33, line: 182, baseType: !79, size: 64, align: 64, offset: 8384)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "data_start_node", scope: !32, file: !33, line: 185, baseType: !40, size: 32, align: 32, offset: 8448)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "data_end_node", scope: !32, file: !33, line: 186, baseType: !40, size: 32, align: 32, offset: 8480)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "formats", scope: !32, file: !33, line: 209, baseType: !255, size: 11264, align: 64, offset: 8512)
!255 = !DICompositeType(tag: DW_TAG_array_type, baseType: !256, size: 11264, align: 64, elements: !247)
!256 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_format_descriptor", file: !33, line: 196, size: 704, align: 64, elements: !257)
!257 = !{!258, !259, !260, !264, !268, !272, !276, !280, !284, !285, !286}
!258 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !256, file: !33, line: 197, baseType: !149, size: 64, align: 64)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !256, file: !33, line: 198, baseType: !107, size: 64, align: 64, offset: 64)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !256, file: !33, line: 199, baseType: !261, size: 64, align: 64, offset: 128)
!261 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !262, size: 64, align: 64)
!262 = !DISubroutineType(types: !263)
!263 = !{!50, !31, !50}
!264 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !256, file: !33, line: 200, baseType: !265, size: 64, align: 64, offset: 192)
!265 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !266, size: 64, align: 64)
!266 = !DISubroutineType(types: !267)
!267 = !{!50, !31, !107, !107}
!268 = !DIDerivedType(tag: DW_TAG_member, name: "read_header", scope: !256, file: !33, line: 202, baseType: !269, size: 64, align: 64, offset: 256)
!269 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !270, size: 64, align: 64)
!270 = !DISubroutineType(types: !271)
!271 = !{!50, !31, !57}
!272 = !DIDerivedType(tag: DW_TAG_member, name: "read_data", scope: !256, file: !33, line: 203, baseType: !273, size: 64, align: 64, offset: 320)
!273 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !274, size: 64, align: 64)
!274 = !DISubroutineType(types: !275)
!275 = !{!50, !31, !91, !92, !93}
!276 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_skip", scope: !256, file: !33, line: 204, baseType: !277, size: 64, align: 64, offset: 384)
!277 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !278, size: 64, align: 64)
!278 = !DISubroutineType(types: !279)
!279 = !{!50, !31}
!280 = !DIDerivedType(tag: DW_TAG_member, name: "seek_data", scope: !256, file: !33, line: 205, baseType: !281, size: 64, align: 64, offset: 448)
!281 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !282, size: 64, align: 64)
!282 = !DISubroutineType(types: !283)
!283 = !{!79, !31, !79, !50}
!284 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !256, file: !33, line: 206, baseType: !277, size: 64, align: 64, offset: 512)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "format_capabilties", scope: !256, file: !33, line: 207, baseType: !277, size: 64, align: 64, offset: 576)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "has_encrypted_entries", scope: !256, file: !33, line: 208, baseType: !277, size: 64, align: 64, offset: 640)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "format", scope: !32, file: !33, line: 210, baseType: !288, size: 64, align: 64, offset: 19776)
!288 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !256, size: 64, align: 64)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "extract", scope: !32, file: !33, line: 215, baseType: !290, size: 64, align: 64, offset: 19840)
!290 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !291, size: 64, align: 64)
!291 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_extract", file: !33, line: 151, size: 192, align: 64, elements: !292)
!292 = !{!293, !294, !298}
!293 = !DIDerivedType(tag: DW_TAG_member, name: "ad", scope: !291, file: !33, line: 152, baseType: !51, size: 64, align: 64)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress", scope: !291, file: !33, line: 155, baseType: !295, size: 64, align: 64, offset: 64)
!295 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !296, size: 64, align: 64)
!296 = !DISubroutineType(types: !297)
!297 = !{null, !149}
!298 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress_user_data", scope: !291, file: !33, line: 156, baseType: !149, size: 64, align: 64, offset: 128)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_archive_extract", scope: !32, file: !33, line: 216, baseType: !277, size: 64, align: 64, offset: 19904)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "passphrases", scope: !32, file: !33, line: 227, baseType: !301, size: 320, align: 64, offset: 19968)
!301 = !DICompositeType(tag: DW_TAG_structure_type, scope: !32, file: !33, line: 221, size: 320, align: 64, elements: !302)
!302 = !{!303, !309, !311, !312, !317}
!303 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !301, file: !33, line: 222, baseType: !304, size: 64, align: 64)
!304 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !305, size: 64, align: 64)
!305 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_passphrase", file: !33, line: 146, size: 128, align: 64, elements: !306)
!306 = !{!307, !308}
!307 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !305, file: !33, line: 147, baseType: !122, size: 64, align: 64)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !305, file: !33, line: 148, baseType: !304, size: 64, align: 64, offset: 64)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !301, file: !33, line: 223, baseType: !310, size: 64, align: 64, offset: 64)
!310 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !304, size: 64, align: 64)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "candidate", scope: !301, file: !33, line: 224, baseType: !50, size: 32, align: 32, offset: 128)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !301, file: !33, line: 225, baseType: !313, size: 64, align: 64, offset: 192)
!313 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !314, size: 64, align: 64)
!314 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !59, line: 256, baseType: !315)
!315 = !DISubroutineType(types: !316)
!316 = !{!107, !51, !149}
!317 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !301, file: !33, line: 226, baseType: !149, size: 64, align: 64, offset: 256)
!318 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!319 = !DIDerivedType(tag: DW_TAG_typedef, name: "time_t", file: !320, line: 75, baseType: !321)
!320 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!321 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !68, line: 139, baseType: !69)
!322 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !323, line: 63, baseType: !324)
!323 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!324 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !68, line: 129, baseType: !40)
!325 = !{!326, !328, !329, !330, !333, !334, !337, !341, !344, !347, !348, !351, !355, !359, !376, !377, !385, !386, !387}
!326 = distinct !DISubprogram(name: "archive_read_support_format_warc", scope: !1, file: !1, line: 140, type: !48, isLocal: false, isDefinition: true, scopeLine: 141, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!327 = !{}
!328 = distinct !DISubprogram(name: "_warc_cleanup", scope: !1, file: !1, line: 168, type: !278, isLocal: true, isDefinition: true, scopeLine: 169, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!329 = distinct !DISubprogram(name: "_warc_bid", scope: !1, file: !1, line: 182, type: !262, isLocal: true, isDefinition: true, scopeLine: 183, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!330 = distinct !DISubprogram(name: "_warc_rdver", scope: !1, file: !1, line: 589, type: !331, isLocal: true, isDefinition: true, scopeLine: 590, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!331 = !DISubroutineType(types: !332)
!332 = !{!40, !107, !72}
!333 = distinct !DISubprogram(name: "_warc_rdhdr", scope: !1, file: !1, line: 211, type: !270, isLocal: true, isDefinition: true, scopeLine: 212, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!334 = distinct !DISubprogram(name: "_warc_find_eoh", scope: !1, file: !1, line: 805, type: !335, isLocal: true, isDefinition: true, scopeLine: 806, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!335 = !DISubroutineType(types: !336)
!336 = !{!107, !107, !72}
!337 = distinct !DISubprogram(name: "xmemmem", scope: !1, file: !1, line: 429, type: !338, isLocal: true, isDefinition: true, scopeLine: 431, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!338 = !DISubroutineType(types: !339)
!339 = !{!122, !107, !340, !107, !340}
!340 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !72)
!341 = distinct !DISubprogram(name: "deconst", scope: !1, file: !1, line: 423, type: !342, isLocal: true, isDefinition: true, scopeLine: 424, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!342 = !DISubroutineType(types: !343)
!343 = !{!149, !70}
!344 = distinct !DISubprogram(name: "_warc_rdlen", scope: !1, file: !1, line: 718, type: !345, isLocal: true, isDefinition: true, scopeLine: 719, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!345 = !DISubroutineType(types: !346)
!346 = !{!65, !107, !72}
!347 = distinct !DISubprogram(name: "_warc_find_eol", scope: !1, file: !1, line: 817, type: !335, isLocal: true, isDefinition: true, scopeLine: 818, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!348 = distinct !DISubprogram(name: "_warc_rdrtm", scope: !1, file: !1, line: 751, type: !349, isLocal: true, isDefinition: true, scopeLine: 752, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!349 = !DISubroutineType(types: !350)
!350 = !{!319, !107, !72}
!351 = distinct !DISubprogram(name: "xstrpisotime", scope: !1, file: !1, line: 535, type: !352, isLocal: true, isDefinition: true, scopeLine: 536, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!352 = !DISubroutineType(types: !353)
!353 = !{!319, !107, !354}
!354 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!355 = distinct !DISubprogram(name: "strtoi_lim", scope: !1, file: !1, line: 487, type: !356, isLocal: true, isDefinition: true, scopeLine: 488, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!356 = !DISubroutineType(types: !357)
!357 = !{!50, !107, !358, !50, !50}
!358 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !107, size: 64, align: 64)
!359 = distinct !DISubprogram(name: "time_from_tm", scope: !1, file: !1, line: 510, type: !360, isLocal: true, isDefinition: true, scopeLine: 511, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!360 = !DISubroutineType(types: !361)
!361 = !{!319, !362}
!362 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !363, size: 64, align: 64)
!363 = !DICompositeType(tag: DW_TAG_structure_type, name: "tm", file: !320, line: 133, size: 448, align: 64, elements: !364)
!364 = !{!365, !366, !367, !368, !369, !370, !371, !372, !373, !374, !375}
!365 = !DIDerivedType(tag: DW_TAG_member, name: "tm_sec", scope: !363, file: !320, line: 135, baseType: !50, size: 32, align: 32)
!366 = !DIDerivedType(tag: DW_TAG_member, name: "tm_min", scope: !363, file: !320, line: 136, baseType: !50, size: 32, align: 32, offset: 32)
!367 = !DIDerivedType(tag: DW_TAG_member, name: "tm_hour", scope: !363, file: !320, line: 137, baseType: !50, size: 32, align: 32, offset: 64)
!368 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mday", scope: !363, file: !320, line: 138, baseType: !50, size: 32, align: 32, offset: 96)
!369 = !DIDerivedType(tag: DW_TAG_member, name: "tm_mon", scope: !363, file: !320, line: 139, baseType: !50, size: 32, align: 32, offset: 128)
!370 = !DIDerivedType(tag: DW_TAG_member, name: "tm_year", scope: !363, file: !320, line: 140, baseType: !50, size: 32, align: 32, offset: 160)
!371 = !DIDerivedType(tag: DW_TAG_member, name: "tm_wday", scope: !363, file: !320, line: 141, baseType: !50, size: 32, align: 32, offset: 192)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "tm_yday", scope: !363, file: !320, line: 142, baseType: !50, size: 32, align: 32, offset: 224)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "tm_isdst", scope: !363, file: !320, line: 143, baseType: !50, size: 32, align: 32, offset: 256)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "tm_gmtoff", scope: !363, file: !320, line: 146, baseType: !69, size: 64, align: 64, offset: 320)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "tm_zone", scope: !363, file: !320, line: 147, baseType: !107, size: 64, align: 64, offset: 384)
!376 = distinct !DISubprogram(name: "_warc_rdtyp", scope: !1, file: !1, line: 632, type: !331, isLocal: true, isDefinition: true, scopeLine: 633, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!377 = distinct !DISubprogram(name: "_warc_rduri", scope: !1, file: !1, line: 661, type: !378, isLocal: true, isDefinition: true, scopeLine: 662, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!378 = !DISubroutineType(types: !379)
!379 = !{!380, !107, !72}
!380 = !DIDerivedType(tag: DW_TAG_typedef, name: "warc_string_t", file: !1, line: 100, baseType: !381)
!381 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 97, size: 128, align: 64, elements: !382)
!382 = !{!383, !384}
!383 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !381, file: !1, line: 98, baseType: !72, size: 64, align: 64)
!384 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !381, file: !1, line: 99, baseType: !107, size: 64, align: 64, offset: 64)
!385 = distinct !DISubprogram(name: "_warc_rdmtm", scope: !1, file: !1, line: 778, type: !349, isLocal: true, isDefinition: true, scopeLine: 779, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!386 = distinct !DISubprogram(name: "_warc_read", scope: !1, file: !1, line: 373, type: !274, isLocal: true, isDefinition: true, scopeLine: 374, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!387 = distinct !DISubprogram(name: "_warc_skip", scope: !1, file: !1, line: 410, type: !278, isLocal: true, isDefinition: true, scopeLine: 411, flags: DIFlagPrototyped, isOptimized: false, variables: !327)
!388 = !{!389, !393, !397, !401, !405, !409, !410, !414}
!389 = !DIGlobalVariable(name: "magic", scope: !330, file: !1, line: 591, type: !390, isLocal: true, isDefinition: true, variable: [6 x i8]* @_warc_rdver.magic)
!390 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 48, align: 8, elements: !391)
!391 = !{!392}
!392 = !DISubrange(count: 6)
!393 = !DIGlobalVariable(name: "_marker", scope: !334, file: !1, line: 807, type: !394, isLocal: true, isDefinition: true, variable: [5 x i8]* @_warc_find_eoh._marker)
!394 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 40, align: 8, elements: !395)
!395 = !{!396}
!396 = !DISubrange(count: 5)
!397 = !DIGlobalVariable(name: "_key", scope: !344, file: !1, line: 720, type: !398, isLocal: true, isDefinition: true, variable: [18 x i8]* @_warc_rdlen._key)
!398 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 144, align: 8, elements: !399)
!399 = !{!400}
!400 = !DISubrange(count: 18)
!401 = !DIGlobalVariable(name: "_marker", scope: !347, file: !1, line: 819, type: !402, isLocal: true, isDefinition: true, variable: [3 x i8]* @_warc_find_eol._marker)
!402 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 24, align: 8, elements: !403)
!403 = !{!404}
!404 = !DISubrange(count: 3)
!405 = !DIGlobalVariable(name: "_key", scope: !348, file: !1, line: 753, type: !406, isLocal: true, isDefinition: true, variable: [13 x i8]* @_warc_rdrtm._key)
!406 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 104, align: 8, elements: !407)
!407 = !{!408}
!408 = !DISubrange(count: 13)
!409 = !DIGlobalVariable(name: "_key", scope: !376, file: !1, line: 634, type: !406, isLocal: true, isDefinition: true, variable: [13 x i8]* @_warc_rdtyp._key)
!410 = !DIGlobalVariable(name: "_key", scope: !377, file: !1, line: 663, type: !411, isLocal: true, isDefinition: true, variable: [19 x i8]* @_warc_rduri._key)
!411 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 152, align: 8, elements: !412)
!412 = !{!413}
!413 = !DISubrange(count: 19)
!414 = !DIGlobalVariable(name: "_key", scope: !385, file: !1, line: 780, type: !415, isLocal: true, isDefinition: true, variable: [17 x i8]* @_warc_rdmtm._key)
!415 = !DICompositeType(tag: DW_TAG_array_type, baseType: !108, size: 136, align: 8, elements: !416)
!416 = !{!417}
!417 = !DISubrange(count: 17)
!418 = !{i32 2, !"Dwarf Version", i32 4}
!419 = !{i32 2, !"Debug Info Version", i32 3}
!420 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!421 = !DILocalVariable(name: "_a", arg: 1, scope: !326, file: !1, line: 140, type: !51)
!422 = !DIExpression()
!423 = !DILocation(line: 140, column: 50, scope: !326)
!424 = !DILocalVariable(name: "a", scope: !326, file: !1, line: 142, type: !31)
!425 = !DILocation(line: 142, column: 23, scope: !326)
!426 = !DILocation(line: 142, column: 50, scope: !326)
!427 = !DILocation(line: 142, column: 27, scope: !326)
!428 = !DILocalVariable(name: "w", scope: !326, file: !1, line: 143, type: !429)
!429 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !430, size: 64, align: 64)
!430 = !DICompositeType(tag: DW_TAG_structure_type, name: "warc_s", file: !1, line: 107, size: 576, align: 64, elements: !431)
!431 = !{!432, !433, !434, !435, !441, !442}
!432 = !DIDerivedType(tag: DW_TAG_member, name: "cntlen", scope: !430, file: !1, line: 109, baseType: !72, size: 64, align: 64)
!433 = !DIDerivedType(tag: DW_TAG_member, name: "cntoff", scope: !430, file: !1, line: 111, baseType: !72, size: 64, align: 64, offset: 64)
!434 = !DIDerivedType(tag: DW_TAG_member, name: "unconsumed", scope: !430, file: !1, line: 113, baseType: !72, size: 64, align: 64, offset: 128)
!435 = !DIDerivedType(tag: DW_TAG_member, name: "pool", scope: !430, file: !1, line: 116, baseType: !436, size: 128, align: 64, offset: 192)
!436 = !DIDerivedType(tag: DW_TAG_typedef, name: "warc_strbuf_t", file: !1, line: 105, baseType: !437)
!437 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 102, size: 128, align: 64, elements: !438)
!438 = !{!439, !440}
!439 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !437, file: !1, line: 103, baseType: !72, size: 64, align: 64)
!440 = !DIDerivedType(tag: DW_TAG_member, name: "str", scope: !437, file: !1, line: 104, baseType: !122, size: 64, align: 64, offset: 64)
!441 = !DIDerivedType(tag: DW_TAG_member, name: "pver", scope: !430, file: !1, line: 118, baseType: !40, size: 32, align: 32, offset: 320)
!442 = !DIDerivedType(tag: DW_TAG_member, name: "sver", scope: !430, file: !1, line: 120, baseType: !118, size: 192, align: 64, offset: 384)
!443 = !DILocation(line: 143, column: 17, scope: !326)
!444 = !DILocalVariable(name: "r", scope: !326, file: !1, line: 144, type: !50)
!445 = !DILocation(line: 144, column: 6, scope: !326)
!446 = !DILocation(line: 146, column: 2, scope: !326)
!447 = !DILocalVariable(name: "magic_test", scope: !448, file: !1, line: 146, type: !50)
!448 = distinct !DILexicalBlock(scope: !326, file: !1, line: 146, column: 2)
!449 = !DILocation(line: 146, column: 2, scope: !448)
!450 = !DILocation(line: 146, column: 2, scope: !451)
!451 = !DILexicalBlockFile(scope: !448, file: !1, discriminator: 1)
!452 = !DILocation(line: 146, column: 2, scope: !453)
!453 = !DILexicalBlockFile(scope: !454, file: !1, discriminator: 2)
!454 = distinct !DILexicalBlock(scope: !448, file: !1, line: 146, column: 2)
!455 = !DILocation(line: 146, column: 2, scope: !456)
!456 = !DILexicalBlockFile(scope: !448, file: !1, discriminator: 3)
!457 = !DILocation(line: 149, column: 11, scope: !458)
!458 = distinct !DILexicalBlock(scope: !326, file: !1, line: 149, column: 6)
!459 = !DILocation(line: 149, column: 9, scope: !458)
!460 = !DILocation(line: 149, column: 34, scope: !458)
!461 = !DILocation(line: 149, column: 6, scope: !326)
!462 = !DILocation(line: 150, column: 22, scope: !463)
!463 = distinct !DILexicalBlock(scope: !458, file: !1, line: 149, column: 43)
!464 = !DILocation(line: 150, column: 25, scope: !463)
!465 = !DILocation(line: 150, column: 3, scope: !463)
!466 = !DILocation(line: 152, column: 3, scope: !463)
!467 = !DILocation(line: 156, column: 3, scope: !326)
!468 = !DILocation(line: 156, column: 6, scope: !326)
!469 = !DILocation(line: 155, column: 6, scope: !326)
!470 = !DILocation(line: 155, column: 4, scope: !326)
!471 = !DILocation(line: 160, column: 6, scope: !472)
!472 = distinct !DILexicalBlock(scope: !326, file: !1, line: 160, column: 6)
!473 = !DILocation(line: 160, column: 8, scope: !472)
!474 = !DILocation(line: 160, column: 6, scope: !326)
!475 = !DILocation(line: 161, column: 8, scope: !476)
!476 = distinct !DILexicalBlock(scope: !472, file: !1, line: 160, column: 23)
!477 = !DILocation(line: 161, column: 3, scope: !476)
!478 = !DILocation(line: 162, column: 11, scope: !476)
!479 = !DILocation(line: 162, column: 3, scope: !476)
!480 = !DILocation(line: 164, column: 2, scope: !326)
!481 = !DILocation(line: 165, column: 1, scope: !326)
!482 = !DILocalVariable(name: "a", arg: 1, scope: !329, file: !1, line: 182, type: !31)
!483 = !DILocation(line: 182, column: 32, scope: !329)
!484 = !DILocalVariable(name: "best_bid", arg: 2, scope: !329, file: !1, line: 182, type: !50)
!485 = !DILocation(line: 182, column: 39, scope: !329)
!486 = !DILocalVariable(name: "hdr", scope: !329, file: !1, line: 184, type: !107)
!487 = !DILocation(line: 184, column: 14, scope: !329)
!488 = !DILocalVariable(name: "nrd", scope: !329, file: !1, line: 185, type: !65)
!489 = !DILocation(line: 185, column: 10, scope: !329)
!490 = !DILocalVariable(name: "ver", scope: !329, file: !1, line: 186, type: !40)
!491 = !DILocation(line: 186, column: 15, scope: !329)
!492 = !DILocation(line: 188, column: 8, scope: !329)
!493 = !DILocation(line: 191, column: 34, scope: !494)
!494 = distinct !DILexicalBlock(scope: !329, file: !1, line: 191, column: 6)
!495 = !DILocation(line: 191, column: 13, scope: !494)
!496 = !DILocation(line: 191, column: 11, scope: !494)
!497 = !DILocation(line: 191, column: 49, scope: !494)
!498 = !DILocation(line: 191, column: 6, scope: !329)
!499 = !DILocation(line: 193, column: 3, scope: !500)
!500 = distinct !DILexicalBlock(scope: !494, file: !1, line: 191, column: 58)
!501 = !DILocation(line: 194, column: 13, scope: !502)
!502 = distinct !DILexicalBlock(scope: !494, file: !1, line: 194, column: 13)
!503 = !DILocation(line: 194, column: 17, scope: !502)
!504 = !DILocation(line: 194, column: 13, scope: !494)
!505 = !DILocation(line: 196, column: 3, scope: !506)
!506 = distinct !DILexicalBlock(scope: !502, file: !1, line: 194, column: 23)
!507 = !DILocation(line: 200, column: 20, scope: !329)
!508 = !DILocation(line: 200, column: 25, scope: !329)
!509 = !DILocation(line: 200, column: 8, scope: !329)
!510 = !DILocation(line: 200, column: 6, scope: !329)
!511 = !DILocation(line: 201, column: 6, scope: !512)
!512 = distinct !DILexicalBlock(scope: !329, file: !1, line: 201, column: 6)
!513 = !DILocation(line: 201, column: 10, scope: !512)
!514 = !DILocation(line: 201, column: 18, scope: !512)
!515 = !DILocation(line: 201, column: 21, scope: !516)
!516 = !DILexicalBlockFile(scope: !512, file: !1, discriminator: 1)
!517 = !DILocation(line: 201, column: 25, scope: !516)
!518 = !DILocation(line: 201, column: 6, scope: !516)
!519 = !DILocation(line: 203, column: 3, scope: !520)
!520 = distinct !DILexicalBlock(scope: !512, file: !1, line: 201, column: 35)
!521 = !DILocation(line: 207, column: 2, scope: !329)
!522 = !DILocation(line: 208, column: 1, scope: !329)
!523 = !DILocalVariable(name: "a", arg: 1, scope: !333, file: !1, line: 211, type: !31)
!524 = !DILocation(line: 211, column: 34, scope: !333)
!525 = !DILocalVariable(name: "entry", arg: 2, scope: !333, file: !1, line: 211, type: !57)
!526 = !DILocation(line: 211, column: 59, scope: !333)
!527 = !DILocalVariable(name: "w", scope: !333, file: !1, line: 214, type: !429)
!528 = !DILocation(line: 214, column: 17, scope: !333)
!529 = !DILocation(line: 214, column: 21, scope: !333)
!530 = !DILocation(line: 214, column: 24, scope: !333)
!531 = !DILocation(line: 214, column: 32, scope: !333)
!532 = !DILocalVariable(name: "ver", scope: !333, file: !1, line: 215, type: !40)
!533 = !DILocation(line: 215, column: 15, scope: !333)
!534 = !DILocalVariable(name: "buf", scope: !333, file: !1, line: 216, type: !107)
!535 = !DILocation(line: 216, column: 14, scope: !333)
!536 = !DILocalVariable(name: "nrd", scope: !333, file: !1, line: 217, type: !65)
!537 = !DILocation(line: 217, column: 10, scope: !333)
!538 = !DILocalVariable(name: "eoh", scope: !333, file: !1, line: 218, type: !107)
!539 = !DILocation(line: 218, column: 14, scope: !333)
!540 = !DILocalVariable(name: "fnam", scope: !333, file: !1, line: 220, type: !380)
!541 = !DILocation(line: 220, column: 16, scope: !333)
!542 = !DILocalVariable(name: "ftyp", scope: !333, file: !1, line: 222, type: !543)
!543 = !DIDerivedType(tag: DW_TAG_typedef, name: "warc_type_t", file: !1, line: 95, baseType: !18)
!544 = !DILocation(line: 222, column: 14, scope: !333)
!545 = !DILocalVariable(name: "cntlen", scope: !333, file: !1, line: 224, type: !65)
!546 = !DILocation(line: 224, column: 10, scope: !333)
!547 = !DILocalVariable(name: "rtime", scope: !333, file: !1, line: 226, type: !319)
!548 = !DILocation(line: 226, column: 9, scope: !333)
!549 = !DILocalVariable(name: "mtime", scope: !333, file: !1, line: 228, type: !319)
!550 = !DILocation(line: 228, column: 9, scope: !333)
!551 = !DILocation(line: 228, column: 2, scope: !333)
!552 = !DILocation(line: 234, column: 29, scope: !333)
!553 = !DILocation(line: 234, column: 8, scope: !333)
!554 = !DILocation(line: 234, column: 6, scope: !333)
!555 = !DILocation(line: 236, column: 6, scope: !556)
!556 = distinct !DILexicalBlock(scope: !333, file: !1, line: 236, column: 6)
!557 = !DILocation(line: 236, column: 10, scope: !556)
!558 = !DILocation(line: 236, column: 6, scope: !333)
!559 = !DILocation(line: 239, column: 5, scope: !560)
!560 = distinct !DILexicalBlock(scope: !556, file: !1, line: 236, column: 15)
!561 = !DILocation(line: 239, column: 8, scope: !560)
!562 = !DILocation(line: 238, column: 3, scope: !560)
!563 = !DILocation(line: 241, column: 3, scope: !560)
!564 = !DILocation(line: 242, column: 13, scope: !565)
!565 = distinct !DILexicalBlock(scope: !556, file: !1, line: 242, column: 13)
!566 = !DILocation(line: 242, column: 17, scope: !565)
!567 = !DILocation(line: 242, column: 13, scope: !556)
!568 = !DILocation(line: 245, column: 3, scope: !569)
!569 = distinct !DILexicalBlock(scope: !565, file: !1, line: 242, column: 26)
!570 = !DILocation(line: 248, column: 23, scope: !333)
!571 = !DILocation(line: 248, column: 28, scope: !333)
!572 = !DILocation(line: 248, column: 8, scope: !333)
!573 = !DILocation(line: 248, column: 6, scope: !333)
!574 = !DILocation(line: 249, column: 6, scope: !575)
!575 = distinct !DILexicalBlock(scope: !333, file: !1, line: 249, column: 6)
!576 = !DILocation(line: 249, column: 10, scope: !575)
!577 = !DILocation(line: 249, column: 6, scope: !333)
!578 = !DILocation(line: 254, column: 5, scope: !579)
!579 = distinct !DILexicalBlock(scope: !575, file: !1, line: 249, column: 19)
!580 = !DILocation(line: 254, column: 8, scope: !579)
!581 = !DILocation(line: 253, column: 3, scope: !579)
!582 = !DILocation(line: 256, column: 3, scope: !579)
!583 = !DILocation(line: 258, column: 20, scope: !333)
!584 = !DILocation(line: 258, column: 25, scope: !333)
!585 = !DILocation(line: 258, column: 31, scope: !333)
!586 = !DILocation(line: 258, column: 29, scope: !333)
!587 = !DILocation(line: 258, column: 8, scope: !333)
!588 = !DILocation(line: 258, column: 6, scope: !333)
!589 = !DILocation(line: 260, column: 6, scope: !590)
!590 = distinct !DILexicalBlock(scope: !333, file: !1, line: 260, column: 6)
!591 = !DILocation(line: 260, column: 10, scope: !590)
!592 = !DILocation(line: 260, column: 6, scope: !333)
!593 = !DILocation(line: 262, column: 5, scope: !594)
!594 = distinct !DILexicalBlock(scope: !590, file: !1, line: 260, column: 17)
!595 = !DILocation(line: 262, column: 8, scope: !594)
!596 = !DILocation(line: 261, column: 3, scope: !594)
!597 = !DILocation(line: 264, column: 3, scope: !594)
!598 = !DILocation(line: 265, column: 13, scope: !599)
!599 = distinct !DILexicalBlock(scope: !590, file: !1, line: 265, column: 13)
!600 = !DILocation(line: 265, column: 17, scope: !599)
!601 = !DILocation(line: 265, column: 25, scope: !599)
!602 = !DILocation(line: 265, column: 28, scope: !603)
!603 = !DILexicalBlockFile(scope: !599, file: !1, discriminator: 1)
!604 = !DILocation(line: 265, column: 32, scope: !603)
!605 = !DILocation(line: 265, column: 13, scope: !603)
!606 = !DILocation(line: 267, column: 5, scope: !607)
!607 = distinct !DILexicalBlock(scope: !599, file: !1, line: 265, column: 42)
!608 = !DILocation(line: 267, column: 8, scope: !607)
!609 = !DILocation(line: 269, column: 4, scope: !607)
!610 = !DILocation(line: 269, column: 8, scope: !607)
!611 = !DILocation(line: 269, column: 18, scope: !607)
!612 = !DILocation(line: 269, column: 22, scope: !607)
!613 = !DILocation(line: 269, column: 31, scope: !607)
!614 = !DILocation(line: 266, column: 3, scope: !607)
!615 = !DILocation(line: 270, column: 3, scope: !607)
!616 = !DILocation(line: 272, column: 23, scope: !333)
!617 = !DILocation(line: 272, column: 28, scope: !333)
!618 = !DILocation(line: 272, column: 34, scope: !333)
!619 = !DILocation(line: 272, column: 32, scope: !333)
!620 = !DILocation(line: 272, column: 11, scope: !333)
!621 = !DILocation(line: 272, column: 9, scope: !333)
!622 = !DILocation(line: 273, column: 6, scope: !623)
!623 = distinct !DILexicalBlock(scope: !333, file: !1, line: 273, column: 6)
!624 = !DILocation(line: 273, column: 13, scope: !623)
!625 = !DILocation(line: 273, column: 6, scope: !333)
!626 = !DILocation(line: 277, column: 5, scope: !627)
!627 = distinct !DILexicalBlock(scope: !623, file: !1, line: 273, column: 18)
!628 = !DILocation(line: 277, column: 8, scope: !627)
!629 = !DILocation(line: 276, column: 3, scope: !627)
!630 = !DILocation(line: 279, column: 3, scope: !627)
!631 = !DILocation(line: 281, column: 22, scope: !333)
!632 = !DILocation(line: 281, column: 27, scope: !333)
!633 = !DILocation(line: 281, column: 33, scope: !333)
!634 = !DILocation(line: 281, column: 31, scope: !333)
!635 = !DILocation(line: 281, column: 10, scope: !333)
!636 = !DILocation(line: 281, column: 8, scope: !333)
!637 = !DILocation(line: 282, column: 6, scope: !638)
!638 = distinct !DILexicalBlock(scope: !333, file: !1, line: 282, column: 6)
!639 = !DILocation(line: 282, column: 12, scope: !638)
!640 = !DILocation(line: 282, column: 6, scope: !333)
!641 = !DILocation(line: 286, column: 5, scope: !642)
!642 = distinct !DILexicalBlock(scope: !638, file: !1, line: 282, column: 27)
!643 = !DILocation(line: 286, column: 8, scope: !642)
!644 = !DILocation(line: 285, column: 3, scope: !642)
!645 = !DILocation(line: 288, column: 3, scope: !642)
!646 = !DILocation(line: 292, column: 2, scope: !333)
!647 = !DILocation(line: 292, column: 5, scope: !333)
!648 = !DILocation(line: 292, column: 13, scope: !333)
!649 = !DILocation(line: 292, column: 28, scope: !333)
!650 = !DILocation(line: 293, column: 6, scope: !651)
!651 = distinct !DILexicalBlock(scope: !333, file: !1, line: 293, column: 6)
!652 = !DILocation(line: 293, column: 13, scope: !651)
!653 = !DILocation(line: 293, column: 16, scope: !651)
!654 = !DILocation(line: 293, column: 10, scope: !651)
!655 = !DILocation(line: 293, column: 6, scope: !333)
!656 = !DILocation(line: 295, column: 27, scope: !657)
!657 = distinct !DILexicalBlock(scope: !651, file: !1, line: 293, column: 22)
!658 = !DILocation(line: 295, column: 30, scope: !657)
!659 = !DILocation(line: 296, column: 18, scope: !657)
!660 = !DILocation(line: 296, column: 22, scope: !657)
!661 = !DILocation(line: 296, column: 32, scope: !657)
!662 = !DILocation(line: 296, column: 36, scope: !657)
!663 = !DILocation(line: 296, column: 45, scope: !657)
!664 = !DILocation(line: 295, column: 3, scope: !657)
!665 = !DILocation(line: 298, column: 13, scope: !657)
!666 = !DILocation(line: 298, column: 3, scope: !657)
!667 = !DILocation(line: 298, column: 6, scope: !657)
!668 = !DILocation(line: 298, column: 11, scope: !657)
!669 = !DILocation(line: 299, column: 2, scope: !657)
!670 = !DILocation(line: 301, column: 21, scope: !333)
!671 = !DILocation(line: 301, column: 26, scope: !333)
!672 = !DILocation(line: 301, column: 32, scope: !333)
!673 = !DILocation(line: 301, column: 30, scope: !333)
!674 = !DILocation(line: 301, column: 9, scope: !333)
!675 = !DILocation(line: 301, column: 7, scope: !333)
!676 = !DILocation(line: 303, column: 14, scope: !333)
!677 = !DILocation(line: 303, column: 2, scope: !333)
!678 = !DILocation(line: 303, column: 5, scope: !333)
!679 = !DILocation(line: 303, column: 12, scope: !333)
!680 = !DILocation(line: 304, column: 2, scope: !333)
!681 = !DILocation(line: 304, column: 5, scope: !333)
!682 = !DILocation(line: 304, column: 12, scope: !333)
!683 = !DILocation(line: 305, column: 8, scope: !333)
!684 = !DILocation(line: 307, column: 10, scope: !333)
!685 = !DILocation(line: 307, column: 2, scope: !333)
!686 = !DILocation(line: 312, column: 22, scope: !687)
!687 = distinct !DILexicalBlock(scope: !333, file: !1, line: 307, column: 16)
!688 = !DILocation(line: 312, column: 27, scope: !687)
!689 = !DILocation(line: 312, column: 33, scope: !687)
!690 = !DILocation(line: 312, column: 31, scope: !687)
!691 = !DILocation(line: 312, column: 10, scope: !687)
!692 = !DILocation(line: 312, column: 10, scope: !693)
!693 = !DILexicalBlockFile(scope: !687, file: !1, discriminator: 1)
!694 = !DILocation(line: 315, column: 12, scope: !695)
!695 = distinct !DILexicalBlock(scope: !687, file: !1, line: 315, column: 7)
!696 = !DILocation(line: 315, column: 16, scope: !695)
!697 = !DILocation(line: 315, column: 21, scope: !695)
!698 = !DILocation(line: 315, column: 38, scope: !699)
!699 = !DILexicalBlockFile(scope: !695, file: !1, discriminator: 1)
!700 = !DILocation(line: 315, column: 42, scope: !699)
!701 = !DILocation(line: 315, column: 29, scope: !699)
!702 = !DILocation(line: 315, column: 24, scope: !699)
!703 = !DILocation(line: 315, column: 47, scope: !699)
!704 = !DILocation(line: 315, column: 7, scope: !699)
!705 = !DILocation(line: 317, column: 9, scope: !706)
!706 = distinct !DILexicalBlock(scope: !695, file: !1, line: 315, column: 55)
!707 = !DILocation(line: 317, column: 13, scope: !706)
!708 = !DILocation(line: 318, column: 9, scope: !706)
!709 = !DILocation(line: 318, column: 13, scope: !706)
!710 = !DILocation(line: 319, column: 4, scope: !706)
!711 = !DILocation(line: 323, column: 12, scope: !712)
!712 = distinct !DILexicalBlock(scope: !687, file: !1, line: 323, column: 7)
!713 = !DILocation(line: 323, column: 16, scope: !712)
!714 = !DILocation(line: 323, column: 23, scope: !712)
!715 = !DILocation(line: 323, column: 26, scope: !712)
!716 = !DILocation(line: 323, column: 31, scope: !712)
!717 = !DILocation(line: 323, column: 21, scope: !712)
!718 = !DILocation(line: 323, column: 7, scope: !687)
!719 = !DILocation(line: 324, column: 25, scope: !720)
!720 = distinct !DILexicalBlock(scope: !712, file: !1, line: 323, column: 36)
!721 = !DILocation(line: 324, column: 29, scope: !720)
!722 = !DILocation(line: 324, column: 36, scope: !720)
!723 = !DILocation(line: 324, column: 43, scope: !720)
!724 = !DILocation(line: 324, column: 4, scope: !720)
!725 = !DILocation(line: 324, column: 7, scope: !720)
!726 = !DILocation(line: 324, column: 12, scope: !720)
!727 = !DILocation(line: 324, column: 16, scope: !720)
!728 = !DILocation(line: 325, column: 26, scope: !720)
!729 = !DILocation(line: 325, column: 29, scope: !720)
!730 = !DILocation(line: 325, column: 34, scope: !720)
!731 = !DILocation(line: 325, column: 39, scope: !720)
!732 = !DILocation(line: 325, column: 42, scope: !720)
!733 = !DILocation(line: 325, column: 47, scope: !720)
!734 = !DILocation(line: 325, column: 18, scope: !720)
!735 = !DILocation(line: 325, column: 4, scope: !720)
!736 = !DILocation(line: 325, column: 7, scope: !720)
!737 = !DILocation(line: 325, column: 12, scope: !720)
!738 = !DILocation(line: 325, column: 16, scope: !720)
!739 = !DILocation(line: 326, column: 3, scope: !720)
!740 = !DILocation(line: 327, column: 10, scope: !687)
!741 = !DILocation(line: 327, column: 13, scope: !687)
!742 = !DILocation(line: 327, column: 18, scope: !687)
!743 = !DILocation(line: 327, column: 28, scope: !687)
!744 = !DILocation(line: 327, column: 38, scope: !687)
!745 = !DILocation(line: 327, column: 3, scope: !687)
!746 = !DILocation(line: 328, column: 20, scope: !687)
!747 = !DILocation(line: 328, column: 3, scope: !687)
!748 = !DILocation(line: 328, column: 6, scope: !687)
!749 = !DILocation(line: 328, column: 11, scope: !687)
!750 = !DILocation(line: 328, column: 25, scope: !687)
!751 = !DILocation(line: 330, column: 14, scope: !687)
!752 = !DILocation(line: 330, column: 17, scope: !687)
!753 = !DILocation(line: 330, column: 22, scope: !687)
!754 = !DILocation(line: 330, column: 8, scope: !687)
!755 = !DILocation(line: 330, column: 12, scope: !687)
!756 = !DILocation(line: 336, column: 28, scope: !757)
!757 = distinct !DILexicalBlock(scope: !687, file: !1, line: 336, column: 7)
!758 = !DILocation(line: 336, column: 33, scope: !757)
!759 = !DILocation(line: 336, column: 39, scope: !757)
!760 = !DILocation(line: 336, column: 37, scope: !757)
!761 = !DILocation(line: 336, column: 16, scope: !757)
!762 = !DILocation(line: 336, column: 14, scope: !757)
!763 = !DILocation(line: 336, column: 45, scope: !757)
!764 = !DILocation(line: 336, column: 7, scope: !687)
!765 = !DILocation(line: 337, column: 12, scope: !766)
!766 = distinct !DILexicalBlock(scope: !757, file: !1, line: 336, column: 60)
!767 = !DILocation(line: 337, column: 10, scope: !766)
!768 = !DILocation(line: 338, column: 3, scope: !766)
!769 = !DILocation(line: 339, column: 3, scope: !687)
!770 = !DILocation(line: 341, column: 8, scope: !687)
!771 = !DILocation(line: 341, column: 12, scope: !687)
!772 = !DILocation(line: 342, column: 8, scope: !687)
!773 = !DILocation(line: 342, column: 12, scope: !687)
!774 = !DILocation(line: 343, column: 3, scope: !687)
!775 = !DILocation(line: 347, column: 25, scope: !333)
!776 = !DILocation(line: 347, column: 28, scope: !333)
!777 = !DILocation(line: 347, column: 34, scope: !333)
!778 = !DILocation(line: 347, column: 32, scope: !333)
!779 = !DILocation(line: 347, column: 2, scope: !333)
!780 = !DILocation(line: 349, column: 10, scope: !333)
!781 = !DILocation(line: 349, column: 2, scope: !333)
!782 = !DILocation(line: 352, column: 12, scope: !783)
!783 = distinct !DILexicalBlock(scope: !784, file: !1, line: 352, column: 7)
!784 = distinct !DILexicalBlock(scope: !333, file: !1, line: 349, column: 16)
!785 = !DILocation(line: 352, column: 16, scope: !783)
!786 = !DILocation(line: 352, column: 7, scope: !784)
!787 = !DILocation(line: 354, column: 31, scope: !788)
!788 = distinct !DILexicalBlock(scope: !783, file: !1, line: 352, column: 22)
!789 = !DILocation(line: 354, column: 4, scope: !788)
!790 = !DILocation(line: 355, column: 32, scope: !788)
!791 = !DILocation(line: 355, column: 44, scope: !788)
!792 = !DILocation(line: 355, column: 4, scope: !788)
!793 = !DILocation(line: 356, column: 27, scope: !788)
!794 = !DILocation(line: 356, column: 34, scope: !788)
!795 = !DILocation(line: 356, column: 4, scope: !788)
!796 = !DILocation(line: 357, column: 27, scope: !788)
!797 = !DILocation(line: 357, column: 4, scope: !788)
!798 = !DILocation(line: 359, column: 28, scope: !788)
!799 = !DILocation(line: 359, column: 35, scope: !788)
!800 = !DILocation(line: 359, column: 4, scope: !788)
!801 = !DILocation(line: 360, column: 28, scope: !788)
!802 = !DILocation(line: 360, column: 35, scope: !788)
!803 = !DILocation(line: 360, column: 4, scope: !788)
!804 = !DILocation(line: 361, column: 4, scope: !788)
!805 = !DILocation(line: 352, column: 18, scope: !806)
!806 = !DILexicalBlockFile(scope: !783, file: !1, discriminator: 1)
!807 = !DILocation(line: 366, column: 14, scope: !784)
!808 = !DILocation(line: 366, column: 3, scope: !784)
!809 = !DILocation(line: 367, column: 3, scope: !784)
!810 = !DILocation(line: 369, column: 2, scope: !333)
!811 = !DILocation(line: 370, column: 1, scope: !333)
!812 = !DILocalVariable(name: "a", arg: 1, scope: !386, file: !1, line: 373, type: !31)
!813 = !DILocation(line: 373, column: 33, scope: !386)
!814 = !DILocalVariable(name: "buf", arg: 2, scope: !386, file: !1, line: 373, type: !91)
!815 = !DILocation(line: 373, column: 49, scope: !386)
!816 = !DILocalVariable(name: "bsz", arg: 3, scope: !386, file: !1, line: 373, type: !92)
!817 = !DILocation(line: 373, column: 62, scope: !386)
!818 = !DILocalVariable(name: "off", arg: 4, scope: !386, file: !1, line: 373, type: !93)
!819 = !DILocation(line: 373, column: 76, scope: !386)
!820 = !DILocalVariable(name: "w", scope: !386, file: !1, line: 375, type: !429)
!821 = !DILocation(line: 375, column: 17, scope: !386)
!822 = !DILocation(line: 375, column: 21, scope: !386)
!823 = !DILocation(line: 375, column: 24, scope: !386)
!824 = !DILocation(line: 375, column: 32, scope: !386)
!825 = !DILocalVariable(name: "rab", scope: !386, file: !1, line: 376, type: !107)
!826 = !DILocation(line: 376, column: 14, scope: !386)
!827 = !DILocalVariable(name: "nrd", scope: !386, file: !1, line: 377, type: !65)
!828 = !DILocation(line: 377, column: 10, scope: !386)
!829 = !DILocation(line: 379, column: 6, scope: !830)
!830 = distinct !DILexicalBlock(scope: !386, file: !1, line: 379, column: 6)
!831 = !DILocation(line: 379, column: 9, scope: !830)
!832 = !DILocation(line: 379, column: 19, scope: !830)
!833 = !DILocation(line: 379, column: 22, scope: !830)
!834 = !DILocation(line: 379, column: 16, scope: !830)
!835 = !DILocation(line: 379, column: 6, scope: !386)
!836 = !DILocation(line: 379, column: 30, scope: !837)
!837 = !DILexicalBlockFile(scope: !830, file: !1, discriminator: 1)
!838 = !DILocation(line: 382, column: 4, scope: !839)
!839 = distinct !DILexicalBlock(scope: !830, file: !1, line: 379, column: 30)
!840 = !DILocation(line: 382, column: 8, scope: !839)
!841 = !DILocation(line: 383, column: 4, scope: !839)
!842 = !DILocation(line: 383, column: 8, scope: !839)
!843 = !DILocation(line: 384, column: 10, scope: !839)
!844 = !DILocation(line: 384, column: 13, scope: !839)
!845 = !DILocation(line: 384, column: 20, scope: !839)
!846 = !DILocation(line: 384, column: 4, scope: !839)
!847 = !DILocation(line: 384, column: 8, scope: !839)
!848 = !DILocation(line: 385, column: 3, scope: !839)
!849 = !DILocation(line: 385, column: 6, scope: !839)
!850 = !DILocation(line: 385, column: 17, scope: !839)
!851 = !DILocation(line: 386, column: 3, scope: !839)
!852 = !DILocation(line: 389, column: 29, scope: !386)
!853 = !DILocation(line: 389, column: 8, scope: !386)
!854 = !DILocation(line: 389, column: 6, scope: !386)
!855 = !DILocation(line: 390, column: 6, scope: !856)
!856 = distinct !DILexicalBlock(scope: !386, file: !1, line: 390, column: 6)
!857 = !DILocation(line: 390, column: 10, scope: !856)
!858 = !DILocation(line: 390, column: 6, scope: !386)
!859 = !DILocation(line: 391, column: 4, scope: !860)
!860 = distinct !DILexicalBlock(scope: !856, file: !1, line: 390, column: 15)
!861 = !DILocation(line: 391, column: 8, scope: !860)
!862 = !DILocation(line: 393, column: 15, scope: !860)
!863 = !DILocation(line: 393, column: 10, scope: !860)
!864 = !DILocation(line: 393, column: 3, scope: !860)
!865 = !DILocation(line: 394, column: 13, scope: !866)
!866 = distinct !DILexicalBlock(scope: !856, file: !1, line: 394, column: 13)
!867 = !DILocation(line: 394, column: 17, scope: !866)
!868 = !DILocation(line: 394, column: 13, scope: !856)
!869 = !DILocation(line: 395, column: 3, scope: !870)
!870 = distinct !DILexicalBlock(scope: !866, file: !1, line: 394, column: 23)
!871 = !DILocation(line: 396, column: 21, scope: !872)
!872 = distinct !DILexicalBlock(scope: !866, file: !1, line: 396, column: 13)
!873 = !DILocation(line: 396, column: 27, scope: !872)
!874 = !DILocation(line: 396, column: 30, scope: !872)
!875 = !DILocation(line: 396, column: 39, scope: !872)
!876 = !DILocation(line: 396, column: 42, scope: !872)
!877 = !DILocation(line: 396, column: 37, scope: !872)
!878 = !DILocation(line: 396, column: 25, scope: !872)
!879 = !DILocation(line: 396, column: 13, scope: !866)
!880 = !DILocation(line: 398, column: 9, scope: !881)
!881 = distinct !DILexicalBlock(scope: !872, file: !1, line: 396, column: 50)
!882 = !DILocation(line: 398, column: 12, scope: !881)
!883 = !DILocation(line: 398, column: 21, scope: !881)
!884 = !DILocation(line: 398, column: 24, scope: !881)
!885 = !DILocation(line: 398, column: 19, scope: !881)
!886 = !DILocation(line: 398, column: 7, scope: !881)
!887 = !DILocation(line: 399, column: 2, scope: !881)
!888 = !DILocation(line: 400, column: 9, scope: !386)
!889 = !DILocation(line: 400, column: 12, scope: !386)
!890 = !DILocation(line: 400, column: 3, scope: !386)
!891 = !DILocation(line: 400, column: 7, scope: !386)
!892 = !DILocation(line: 401, column: 9, scope: !386)
!893 = !DILocation(line: 401, column: 3, scope: !386)
!894 = !DILocation(line: 401, column: 7, scope: !386)
!895 = !DILocation(line: 402, column: 9, scope: !386)
!896 = !DILocation(line: 402, column: 3, scope: !386)
!897 = !DILocation(line: 402, column: 7, scope: !386)
!898 = !DILocation(line: 404, column: 15, scope: !386)
!899 = !DILocation(line: 404, column: 2, scope: !386)
!900 = !DILocation(line: 404, column: 5, scope: !386)
!901 = !DILocation(line: 404, column: 12, scope: !386)
!902 = !DILocation(line: 405, column: 26, scope: !386)
!903 = !DILocation(line: 405, column: 2, scope: !386)
!904 = !DILocation(line: 405, column: 5, scope: !386)
!905 = !DILocation(line: 405, column: 16, scope: !386)
!906 = !DILocation(line: 406, column: 2, scope: !386)
!907 = !DILocation(line: 407, column: 1, scope: !386)
!908 = !DILocalVariable(name: "a", arg: 1, scope: !387, file: !1, line: 410, type: !31)
!909 = !DILocation(line: 410, column: 33, scope: !387)
!910 = !DILocalVariable(name: "w", scope: !387, file: !1, line: 412, type: !429)
!911 = !DILocation(line: 412, column: 17, scope: !387)
!912 = !DILocation(line: 412, column: 21, scope: !387)
!913 = !DILocation(line: 412, column: 24, scope: !387)
!914 = !DILocation(line: 412, column: 32, scope: !387)
!915 = !DILocation(line: 414, column: 25, scope: !387)
!916 = !DILocation(line: 414, column: 28, scope: !387)
!917 = !DILocation(line: 414, column: 31, scope: !387)
!918 = !DILocation(line: 414, column: 38, scope: !387)
!919 = !DILocation(line: 414, column: 2, scope: !387)
!920 = !DILocation(line: 415, column: 2, scope: !387)
!921 = !DILocation(line: 415, column: 5, scope: !387)
!922 = !DILocation(line: 415, column: 12, scope: !387)
!923 = !DILocation(line: 416, column: 2, scope: !387)
!924 = !DILocation(line: 416, column: 5, scope: !387)
!925 = !DILocation(line: 416, column: 12, scope: !387)
!926 = !DILocation(line: 417, column: 2, scope: !387)
!927 = !DILocalVariable(name: "a", arg: 1, scope: !328, file: !1, line: 168, type: !31)
!928 = !DILocation(line: 168, column: 36, scope: !328)
!929 = !DILocalVariable(name: "w", scope: !328, file: !1, line: 170, type: !429)
!930 = !DILocation(line: 170, column: 17, scope: !328)
!931 = !DILocation(line: 170, column: 21, scope: !328)
!932 = !DILocation(line: 170, column: 24, scope: !328)
!933 = !DILocation(line: 170, column: 32, scope: !328)
!934 = !DILocation(line: 172, column: 6, scope: !935)
!935 = distinct !DILexicalBlock(scope: !328, file: !1, line: 172, column: 6)
!936 = !DILocation(line: 172, column: 9, scope: !935)
!937 = !DILocation(line: 172, column: 14, scope: !935)
!938 = !DILocation(line: 172, column: 18, scope: !935)
!939 = !DILocation(line: 172, column: 6, scope: !328)
!940 = !DILocation(line: 173, column: 8, scope: !941)
!941 = distinct !DILexicalBlock(scope: !935, file: !1, line: 172, column: 24)
!942 = !DILocation(line: 173, column: 11, scope: !941)
!943 = !DILocation(line: 173, column: 16, scope: !941)
!944 = !DILocation(line: 173, column: 3, scope: !941)
!945 = !DILocation(line: 174, column: 2, scope: !941)
!946 = !DILocation(line: 175, column: 23, scope: !328)
!947 = !DILocation(line: 175, column: 26, scope: !328)
!948 = !DILocation(line: 175, column: 2, scope: !328)
!949 = !DILocation(line: 176, column: 7, scope: !328)
!950 = !DILocation(line: 176, column: 2, scope: !328)
!951 = !DILocation(line: 177, column: 2, scope: !328)
!952 = !DILocation(line: 177, column: 5, scope: !328)
!953 = !DILocation(line: 177, column: 13, scope: !328)
!954 = !DILocation(line: 177, column: 18, scope: !328)
!955 = !DILocation(line: 178, column: 2, scope: !328)
!956 = !DILocalVariable(name: "buf", arg: 1, scope: !330, file: !1, line: 589, type: !107)
!957 = !DILocation(line: 589, column: 25, scope: !330)
!958 = !DILocalVariable(name: "bsz", arg: 2, scope: !330, file: !1, line: 589, type: !72)
!959 = !DILocation(line: 589, column: 37, scope: !330)
!960 = !DILocalVariable(name: "c", scope: !330, file: !1, line: 592, type: !107)
!961 = !DILocation(line: 592, column: 14, scope: !330)
!962 = !DILocalVariable(name: "ver", scope: !330, file: !1, line: 593, type: !40)
!963 = !DILocation(line: 593, column: 15, scope: !330)
!964 = !DILocalVariable(name: "end", scope: !330, file: !1, line: 594, type: !40)
!965 = !DILocation(line: 594, column: 15, scope: !330)
!966 = !DILocation(line: 596, column: 6, scope: !967)
!967 = distinct !DILexicalBlock(scope: !330, file: !1, line: 596, column: 6)
!968 = !DILocation(line: 596, column: 10, scope: !967)
!969 = !DILocation(line: 596, column: 15, scope: !967)
!970 = !DILocation(line: 596, column: 25, scope: !971)
!971 = !DILexicalBlockFile(scope: !967, file: !1, discriminator: 1)
!972 = !DILocation(line: 596, column: 18, scope: !971)
!973 = !DILocation(line: 596, column: 57, scope: !971)
!974 = !DILocation(line: 596, column: 6, scope: !971)
!975 = !DILocation(line: 598, column: 10, scope: !976)
!976 = distinct !DILexicalBlock(scope: !967, file: !1, line: 596, column: 63)
!977 = !DILocation(line: 598, column: 3, scope: !976)
!978 = !DILocation(line: 601, column: 6, scope: !330)
!979 = !DILocation(line: 603, column: 6, scope: !980)
!980 = distinct !DILexicalBlock(scope: !330, file: !1, line: 603, column: 6)
!981 = !DILocation(line: 603, column: 23, scope: !980)
!982 = !DILocation(line: 603, column: 27, scope: !983)
!983 = !DILexicalBlockFile(scope: !980, file: !1, discriminator: 1)
!984 = !DILocation(line: 603, column: 35, scope: !983)
!985 = !DILocation(line: 603, column: 43, scope: !983)
!986 = !DILocation(line: 603, column: 46, scope: !987)
!987 = !DILexicalBlockFile(scope: !980, file: !1, discriminator: 2)
!988 = !DILocation(line: 603, column: 6, scope: !987)
!989 = !DILocation(line: 605, column: 7, scope: !990)
!990 = distinct !DILexicalBlock(scope: !991, file: !1, line: 605, column: 7)
!991 = distinct !DILexicalBlock(scope: !980, file: !1, line: 603, column: 64)
!992 = !DILocation(line: 605, column: 7, scope: !991)
!993 = !DILocation(line: 606, column: 8, scope: !990)
!994 = !DILocation(line: 606, column: 4, scope: !990)
!995 = !DILocation(line: 608, column: 10, scope: !991)
!996 = !DILocation(line: 608, column: 18, scope: !991)
!997 = !DILocation(line: 608, column: 25, scope: !991)
!998 = !DILocation(line: 608, column: 7, scope: !991)
!999 = !DILocation(line: 610, column: 7, scope: !1000)
!1000 = distinct !DILexicalBlock(scope: !991, file: !1, line: 610, column: 7)
!1001 = !DILocation(line: 610, column: 11, scope: !1000)
!1002 = !DILocation(line: 610, column: 7, scope: !991)
!1003 = !DILocation(line: 611, column: 12, scope: !1004)
!1004 = distinct !DILexicalBlock(scope: !1000, file: !1, line: 610, column: 18)
!1005 = !DILocation(line: 611, column: 20, scope: !1004)
!1006 = !DILocation(line: 611, column: 27, scope: !1004)
!1007 = !DILocation(line: 611, column: 8, scope: !1004)
!1008 = !DILocation(line: 612, column: 12, scope: !1004)
!1009 = !DILocation(line: 612, column: 20, scope: !1004)
!1010 = !DILocation(line: 612, column: 27, scope: !1004)
!1011 = !DILocation(line: 612, column: 8, scope: !1004)
!1012 = !DILocation(line: 613, column: 3, scope: !1004)
!1013 = !DILocation(line: 614, column: 12, scope: !1000)
!1014 = !DILocation(line: 614, column: 20, scope: !1000)
!1015 = !DILocation(line: 614, column: 27, scope: !1000)
!1016 = !DILocation(line: 614, column: 8, scope: !1000)
!1017 = !DILocation(line: 619, column: 7, scope: !991)
!1018 = !DILocation(line: 619, column: 11, scope: !991)
!1019 = !DILocation(line: 619, column: 18, scope: !991)
!1020 = !DILocation(line: 619, column: 16, scope: !991)
!1021 = !DILocation(line: 619, column: 5, scope: !991)
!1022 = !DILocation(line: 620, column: 7, scope: !1023)
!1023 = distinct !DILexicalBlock(scope: !991, file: !1, line: 620, column: 7)
!1024 = !DILocation(line: 620, column: 11, scope: !1023)
!1025 = !DILocation(line: 620, column: 7, scope: !991)
!1026 = !DILocation(line: 621, column: 15, scope: !1027)
!1027 = distinct !DILexicalBlock(scope: !1028, file: !1, line: 621, column: 8)
!1028 = distinct !DILexicalBlock(scope: !1023, file: !1, line: 620, column: 21)
!1029 = !DILocation(line: 621, column: 8, scope: !1027)
!1030 = !DILocation(line: 621, column: 30, scope: !1027)
!1031 = !DILocation(line: 621, column: 8, scope: !1028)
!1032 = !DILocation(line: 622, column: 9, scope: !1027)
!1033 = !DILocation(line: 622, column: 5, scope: !1027)
!1034 = !DILocation(line: 623, column: 3, scope: !1028)
!1035 = !DILocation(line: 623, column: 14, scope: !1036)
!1036 = !DILexicalBlockFile(scope: !1037, file: !1, discriminator: 1)
!1037 = distinct !DILexicalBlock(scope: !1023, file: !1, line: 623, column: 14)
!1038 = !DILocation(line: 623, column: 18, scope: !1036)
!1039 = !DILocation(line: 624, column: 9, scope: !1040)
!1040 = distinct !DILexicalBlock(scope: !1041, file: !1, line: 624, column: 8)
!1041 = distinct !DILexicalBlock(scope: !1037, file: !1, line: 623, column: 27)
!1042 = !DILocation(line: 624, column: 8, scope: !1040)
!1043 = !DILocation(line: 624, column: 11, scope: !1040)
!1044 = !DILocation(line: 624, column: 18, scope: !1040)
!1045 = !DILocation(line: 624, column: 22, scope: !1046)
!1046 = !DILexicalBlockFile(scope: !1040, file: !1, discriminator: 1)
!1047 = !DILocation(line: 624, column: 21, scope: !1046)
!1048 = !DILocation(line: 624, column: 24, scope: !1046)
!1049 = !DILocation(line: 624, column: 8, scope: !1046)
!1050 = !DILocation(line: 625, column: 9, scope: !1040)
!1051 = !DILocation(line: 625, column: 5, scope: !1040)
!1052 = !DILocation(line: 626, column: 3, scope: !1041)
!1053 = !DILocation(line: 627, column: 2, scope: !991)
!1054 = !DILocation(line: 628, column: 9, scope: !330)
!1055 = !DILocation(line: 628, column: 2, scope: !330)
!1056 = !DILocation(line: 629, column: 1, scope: !330)
!1057 = !DILocalVariable(name: "buf", arg: 1, scope: !334, file: !1, line: 805, type: !107)
!1058 = !DILocation(line: 805, column: 28, scope: !334)
!1059 = !DILocalVariable(name: "bsz", arg: 2, scope: !334, file: !1, line: 805, type: !72)
!1060 = !DILocation(line: 805, column: 40, scope: !334)
!1061 = !DILocalVariable(name: "hit", scope: !334, file: !1, line: 808, type: !107)
!1062 = !DILocation(line: 808, column: 14, scope: !334)
!1063 = !DILocation(line: 808, column: 28, scope: !334)
!1064 = !DILocation(line: 808, column: 33, scope: !334)
!1065 = !DILocation(line: 808, column: 20, scope: !334)
!1066 = !DILocation(line: 810, column: 6, scope: !1067)
!1067 = distinct !DILexicalBlock(scope: !334, file: !1, line: 810, column: 6)
!1068 = !DILocation(line: 810, column: 10, scope: !1067)
!1069 = !DILocation(line: 810, column: 6, scope: !334)
!1070 = !DILocation(line: 811, column: 7, scope: !1071)
!1071 = distinct !DILexicalBlock(scope: !1067, file: !1, line: 810, column: 19)
!1072 = !DILocation(line: 812, column: 2, scope: !1071)
!1073 = !DILocation(line: 813, column: 9, scope: !334)
!1074 = !DILocation(line: 813, column: 2, scope: !334)
!1075 = !DILocalVariable(name: "buf", arg: 1, scope: !344, file: !1, line: 718, type: !107)
!1076 = !DILocation(line: 718, column: 25, scope: !344)
!1077 = !DILocalVariable(name: "bsz", arg: 2, scope: !344, file: !1, line: 718, type: !72)
!1078 = !DILocation(line: 718, column: 37, scope: !344)
!1079 = !DILocalVariable(name: "val", scope: !344, file: !1, line: 721, type: !107)
!1080 = !DILocation(line: 721, column: 14, scope: !344)
!1081 = !DILocalVariable(name: "eol", scope: !344, file: !1, line: 721, type: !107)
!1082 = !DILocation(line: 721, column: 20, scope: !344)
!1083 = !DILocalVariable(name: "on", scope: !344, file: !1, line: 722, type: !122)
!1084 = !DILocation(line: 722, column: 8, scope: !344)
!1085 = !DILocalVariable(name: "len", scope: !344, file: !1, line: 723, type: !69)
!1086 = !DILocation(line: 723, column: 11, scope: !344)
!1087 = !DILocation(line: 725, column: 21, scope: !1088)
!1088 = distinct !DILexicalBlock(scope: !344, file: !1, line: 725, column: 6)
!1089 = !DILocation(line: 725, column: 26, scope: !1088)
!1090 = !DILocation(line: 725, column: 13, scope: !1088)
!1091 = !DILocation(line: 725, column: 11, scope: !1088)
!1092 = !DILocation(line: 725, column: 57, scope: !1088)
!1093 = !DILocation(line: 725, column: 6, scope: !344)
!1094 = !DILocation(line: 727, column: 3, scope: !1095)
!1095 = distinct !DILexicalBlock(scope: !1088, file: !1, line: 725, column: 66)
!1096 = !DILocation(line: 729, column: 6, scope: !344)
!1097 = !DILocation(line: 730, column: 28, scope: !1098)
!1098 = distinct !DILexicalBlock(scope: !344, file: !1, line: 730, column: 6)
!1099 = !DILocation(line: 730, column: 33, scope: !1098)
!1100 = !DILocation(line: 730, column: 39, scope: !1098)
!1101 = !DILocation(line: 730, column: 37, scope: !1098)
!1102 = !DILocation(line: 730, column: 45, scope: !1098)
!1103 = !DILocation(line: 730, column: 43, scope: !1098)
!1104 = !DILocation(line: 730, column: 13, scope: !1098)
!1105 = !DILocation(line: 730, column: 11, scope: !1098)
!1106 = !DILocation(line: 730, column: 51, scope: !1098)
!1107 = !DILocation(line: 730, column: 6, scope: !344)
!1108 = !DILocation(line: 732, column: 3, scope: !1109)
!1109 = distinct !DILexicalBlock(scope: !1098, file: !1, line: 730, column: 60)
!1110 = !DILocation(line: 736, column: 2, scope: !344)
!1111 = !DILocation(line: 736, column: 9, scope: !1112)
!1112 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 1)
!1113 = !DILocation(line: 736, column: 15, scope: !1112)
!1114 = !DILocation(line: 736, column: 13, scope: !1112)
!1115 = !DILocation(line: 736, column: 19, scope: !1112)
!1116 = !DILocation(line: 736, column: 24, scope: !1117)
!1117 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 2)
!1118 = !DILocation(line: 736, column: 23, scope: !1117)
!1119 = !DILocation(line: 736, column: 28, scope: !1117)
!1120 = !DILocation(line: 736, column: 35, scope: !1117)
!1121 = !DILocation(line: 736, column: 39, scope: !1122)
!1122 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 3)
!1123 = !DILocation(line: 736, column: 38, scope: !1122)
!1124 = !DILocation(line: 736, column: 43, scope: !1122)
!1125 = !DILocation(line: 736, column: 35, scope: !1122)
!1126 = !DILocation(line: 736, column: 2, scope: !1127)
!1127 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 4)
!1128 = !DILocation(line: 737, column: 6, scope: !344)
!1129 = !DILocation(line: 736, column: 2, scope: !1130)
!1130 = !DILexicalBlockFile(scope: !344, file: !1, discriminator: 5)
!1131 = !DILocation(line: 739, column: 7, scope: !1132)
!1132 = distinct !DILexicalBlock(scope: !344, file: !1, line: 739, column: 6)
!1133 = !DILocation(line: 739, column: 6, scope: !344)
!1134 = !DILocation(line: 740, column: 3, scope: !1132)
!1135 = !DILocation(line: 741, column: 15, scope: !344)
!1136 = !DILocation(line: 741, column: 8, scope: !344)
!1137 = !DILocation(line: 741, column: 6, scope: !344)
!1138 = !DILocation(line: 742, column: 6, scope: !1139)
!1139 = distinct !DILexicalBlock(scope: !344, file: !1, line: 742, column: 6)
!1140 = !DILocation(line: 742, column: 12, scope: !1139)
!1141 = !DILocation(line: 742, column: 9, scope: !1139)
!1142 = !DILocation(line: 742, column: 6, scope: !344)
!1143 = !DILocation(line: 744, column: 3, scope: !1144)
!1144 = distinct !DILexicalBlock(scope: !1139, file: !1, line: 742, column: 17)
!1145 = !DILocation(line: 747, column: 17, scope: !344)
!1146 = !DILocation(line: 747, column: 2, scope: !344)
!1147 = !DILocation(line: 748, column: 1, scope: !344)
!1148 = !DILocalVariable(name: "buf", arg: 1, scope: !348, file: !1, line: 751, type: !107)
!1149 = !DILocation(line: 751, column: 25, scope: !348)
!1150 = !DILocalVariable(name: "bsz", arg: 2, scope: !348, file: !1, line: 751, type: !72)
!1151 = !DILocation(line: 751, column: 37, scope: !348)
!1152 = !DILocalVariable(name: "val", scope: !348, file: !1, line: 754, type: !107)
!1153 = !DILocation(line: 754, column: 14, scope: !348)
!1154 = !DILocalVariable(name: "eol", scope: !348, file: !1, line: 754, type: !107)
!1155 = !DILocation(line: 754, column: 20, scope: !348)
!1156 = !DILocalVariable(name: "on", scope: !348, file: !1, line: 755, type: !122)
!1157 = !DILocation(line: 755, column: 8, scope: !348)
!1158 = !DILocalVariable(name: "res", scope: !348, file: !1, line: 756, type: !319)
!1159 = !DILocation(line: 756, column: 9, scope: !348)
!1160 = !DILocation(line: 758, column: 21, scope: !1161)
!1161 = distinct !DILexicalBlock(scope: !348, file: !1, line: 758, column: 6)
!1162 = !DILocation(line: 758, column: 26, scope: !1161)
!1163 = !DILocation(line: 758, column: 13, scope: !1161)
!1164 = !DILocation(line: 758, column: 11, scope: !1161)
!1165 = !DILocation(line: 758, column: 57, scope: !1161)
!1166 = !DILocation(line: 758, column: 6, scope: !348)
!1167 = !DILocation(line: 760, column: 3, scope: !1168)
!1168 = distinct !DILexicalBlock(scope: !1161, file: !1, line: 758, column: 66)
!1169 = !DILocation(line: 762, column: 6, scope: !348)
!1170 = !DILocation(line: 763, column: 28, scope: !1171)
!1171 = distinct !DILexicalBlock(scope: !348, file: !1, line: 763, column: 6)
!1172 = !DILocation(line: 763, column: 33, scope: !1171)
!1173 = !DILocation(line: 763, column: 39, scope: !1171)
!1174 = !DILocation(line: 763, column: 37, scope: !1171)
!1175 = !DILocation(line: 763, column: 45, scope: !1171)
!1176 = !DILocation(line: 763, column: 43, scope: !1171)
!1177 = !DILocation(line: 763, column: 13, scope: !1171)
!1178 = !DILocation(line: 763, column: 11, scope: !1171)
!1179 = !DILocation(line: 763, column: 51, scope: !1171)
!1180 = !DILocation(line: 763, column: 6, scope: !348)
!1181 = !DILocation(line: 765, column: 3, scope: !1182)
!1182 = distinct !DILexicalBlock(scope: !1171, file: !1, line: 763, column: 61)
!1183 = !DILocation(line: 769, column: 21, scope: !348)
!1184 = !DILocation(line: 769, column: 8, scope: !348)
!1185 = !DILocation(line: 769, column: 6, scope: !348)
!1186 = !DILocation(line: 770, column: 6, scope: !1187)
!1187 = distinct !DILexicalBlock(scope: !348, file: !1, line: 770, column: 6)
!1188 = !DILocation(line: 770, column: 12, scope: !1187)
!1189 = !DILocation(line: 770, column: 9, scope: !1187)
!1190 = !DILocation(line: 770, column: 6, scope: !348)
!1191 = !DILocation(line: 772, column: 3, scope: !1192)
!1192 = distinct !DILexicalBlock(scope: !1187, file: !1, line: 770, column: 17)
!1193 = !DILocation(line: 774, column: 9, scope: !348)
!1194 = !DILocation(line: 774, column: 2, scope: !348)
!1195 = !DILocation(line: 775, column: 1, scope: !348)
!1196 = !DILocalVariable(name: "buf", arg: 1, scope: !376, file: !1, line: 632, type: !107)
!1197 = !DILocation(line: 632, column: 25, scope: !376)
!1198 = !DILocalVariable(name: "bsz", arg: 2, scope: !376, file: !1, line: 632, type: !72)
!1199 = !DILocation(line: 632, column: 37, scope: !376)
!1200 = !DILocalVariable(name: "val", scope: !376, file: !1, line: 635, type: !107)
!1201 = !DILocation(line: 635, column: 14, scope: !376)
!1202 = !DILocalVariable(name: "eol", scope: !376, file: !1, line: 635, type: !107)
!1203 = !DILocation(line: 635, column: 20, scope: !376)
!1204 = !DILocation(line: 637, column: 21, scope: !1205)
!1205 = distinct !DILexicalBlock(scope: !376, file: !1, line: 637, column: 6)
!1206 = !DILocation(line: 637, column: 26, scope: !1205)
!1207 = !DILocation(line: 637, column: 13, scope: !1205)
!1208 = !DILocation(line: 637, column: 11, scope: !1205)
!1209 = !DILocation(line: 637, column: 57, scope: !1205)
!1210 = !DILocation(line: 637, column: 6, scope: !376)
!1211 = !DILocation(line: 639, column: 3, scope: !1212)
!1212 = distinct !DILexicalBlock(scope: !1205, file: !1, line: 637, column: 66)
!1213 = !DILocation(line: 641, column: 6, scope: !376)
!1214 = !DILocation(line: 642, column: 28, scope: !1215)
!1215 = distinct !DILexicalBlock(scope: !376, file: !1, line: 642, column: 6)
!1216 = !DILocation(line: 642, column: 33, scope: !1215)
!1217 = !DILocation(line: 642, column: 39, scope: !1215)
!1218 = !DILocation(line: 642, column: 37, scope: !1215)
!1219 = !DILocation(line: 642, column: 45, scope: !1215)
!1220 = !DILocation(line: 642, column: 43, scope: !1215)
!1221 = !DILocation(line: 642, column: 13, scope: !1215)
!1222 = !DILocation(line: 642, column: 11, scope: !1215)
!1223 = !DILocation(line: 642, column: 51, scope: !1215)
!1224 = !DILocation(line: 642, column: 6, scope: !376)
!1225 = !DILocation(line: 644, column: 3, scope: !1226)
!1226 = distinct !DILexicalBlock(scope: !1215, file: !1, line: 642, column: 60)
!1227 = !DILocation(line: 648, column: 2, scope: !376)
!1228 = !DILocation(line: 648, column: 9, scope: !1229)
!1229 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 1)
!1230 = !DILocation(line: 648, column: 15, scope: !1229)
!1231 = !DILocation(line: 648, column: 13, scope: !1229)
!1232 = !DILocation(line: 648, column: 19, scope: !1229)
!1233 = !DILocation(line: 648, column: 24, scope: !1234)
!1234 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 2)
!1235 = !DILocation(line: 648, column: 23, scope: !1234)
!1236 = !DILocation(line: 648, column: 28, scope: !1234)
!1237 = !DILocation(line: 648, column: 35, scope: !1234)
!1238 = !DILocation(line: 648, column: 39, scope: !1239)
!1239 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 3)
!1240 = !DILocation(line: 648, column: 38, scope: !1239)
!1241 = !DILocation(line: 648, column: 43, scope: !1239)
!1242 = !DILocation(line: 648, column: 35, scope: !1239)
!1243 = !DILocation(line: 648, column: 2, scope: !1244)
!1244 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 4)
!1245 = !DILocation(line: 649, column: 3, scope: !376)
!1246 = !DILocation(line: 648, column: 2, scope: !1247)
!1247 = !DILexicalBlockFile(scope: !376, file: !1, discriminator: 5)
!1248 = !DILocation(line: 651, column: 6, scope: !1249)
!1249 = distinct !DILexicalBlock(scope: !376, file: !1, line: 651, column: 6)
!1250 = !DILocation(line: 651, column: 10, scope: !1249)
!1251 = !DILocation(line: 651, column: 18, scope: !1249)
!1252 = !DILocation(line: 651, column: 15, scope: !1249)
!1253 = !DILocation(line: 651, column: 6, scope: !376)
!1254 = !DILocation(line: 652, column: 14, scope: !1255)
!1255 = distinct !DILexicalBlock(scope: !1256, file: !1, line: 652, column: 7)
!1256 = distinct !DILexicalBlock(scope: !1249, file: !1, line: 651, column: 23)
!1257 = !DILocation(line: 652, column: 7, scope: !1255)
!1258 = !DILocation(line: 652, column: 35, scope: !1255)
!1259 = !DILocation(line: 652, column: 7, scope: !1256)
!1260 = !DILocation(line: 653, column: 4, scope: !1255)
!1261 = !DILocation(line: 654, column: 19, scope: !1262)
!1262 = distinct !DILexicalBlock(scope: !1255, file: !1, line: 654, column: 12)
!1263 = !DILocation(line: 654, column: 12, scope: !1262)
!1264 = !DILocation(line: 654, column: 40, scope: !1262)
!1265 = !DILocation(line: 654, column: 12, scope: !1255)
!1266 = !DILocation(line: 655, column: 4, scope: !1262)
!1267 = !DILocation(line: 656, column: 2, scope: !1256)
!1268 = !DILocation(line: 657, column: 2, scope: !376)
!1269 = !DILocation(line: 658, column: 1, scope: !376)
!1270 = !DILocalVariable(name: "buf", arg: 1, scope: !377, file: !1, line: 661, type: !107)
!1271 = !DILocation(line: 661, column: 25, scope: !377)
!1272 = !DILocalVariable(name: "bsz", arg: 2, scope: !377, file: !1, line: 661, type: !72)
!1273 = !DILocation(line: 661, column: 37, scope: !377)
!1274 = !DILocalVariable(name: "val", scope: !377, file: !1, line: 664, type: !107)
!1275 = !DILocation(line: 664, column: 14, scope: !377)
!1276 = !DILocalVariable(name: "uri", scope: !377, file: !1, line: 664, type: !107)
!1277 = !DILocation(line: 664, column: 20, scope: !377)
!1278 = !DILocalVariable(name: "eol", scope: !377, file: !1, line: 664, type: !107)
!1279 = !DILocation(line: 664, column: 26, scope: !377)
!1280 = !DILocalVariable(name: "p", scope: !377, file: !1, line: 664, type: !107)
!1281 = !DILocation(line: 664, column: 32, scope: !377)
!1282 = !DILocalVariable(name: "res", scope: !377, file: !1, line: 665, type: !380)
!1283 = !DILocation(line: 665, column: 16, scope: !377)
!1284 = !DILocation(line: 667, column: 21, scope: !1285)
!1285 = distinct !DILexicalBlock(scope: !377, file: !1, line: 667, column: 6)
!1286 = !DILocation(line: 667, column: 26, scope: !1285)
!1287 = !DILocation(line: 667, column: 13, scope: !1285)
!1288 = !DILocation(line: 667, column: 11, scope: !1285)
!1289 = !DILocation(line: 667, column: 57, scope: !1285)
!1290 = !DILocation(line: 667, column: 6, scope: !377)
!1291 = !DILocation(line: 669, column: 10, scope: !1292)
!1292 = distinct !DILexicalBlock(scope: !1285, file: !1, line: 667, column: 66)
!1293 = !DILocation(line: 669, column: 3, scope: !1292)
!1294 = !DILocation(line: 672, column: 6, scope: !377)
!1295 = !DILocation(line: 673, column: 28, scope: !1296)
!1296 = distinct !DILexicalBlock(scope: !377, file: !1, line: 673, column: 6)
!1297 = !DILocation(line: 673, column: 33, scope: !1296)
!1298 = !DILocation(line: 673, column: 39, scope: !1296)
!1299 = !DILocation(line: 673, column: 37, scope: !1296)
!1300 = !DILocation(line: 673, column: 45, scope: !1296)
!1301 = !DILocation(line: 673, column: 43, scope: !1296)
!1302 = !DILocation(line: 673, column: 13, scope: !1296)
!1303 = !DILocation(line: 673, column: 11, scope: !1296)
!1304 = !DILocation(line: 673, column: 51, scope: !1296)
!1305 = !DILocation(line: 673, column: 6, scope: !377)
!1306 = !DILocation(line: 675, column: 10, scope: !1307)
!1307 = distinct !DILexicalBlock(scope: !1296, file: !1, line: 673, column: 60)
!1308 = !DILocation(line: 675, column: 3, scope: !1307)
!1309 = !DILocation(line: 678, column: 2, scope: !377)
!1310 = !DILocation(line: 678, column: 9, scope: !1311)
!1311 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 1)
!1312 = !DILocation(line: 678, column: 15, scope: !1311)
!1313 = !DILocation(line: 678, column: 13, scope: !1311)
!1314 = !DILocation(line: 678, column: 19, scope: !1311)
!1315 = !DILocation(line: 678, column: 24, scope: !1316)
!1316 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 2)
!1317 = !DILocation(line: 678, column: 23, scope: !1316)
!1318 = !DILocation(line: 678, column: 28, scope: !1316)
!1319 = !DILocation(line: 678, column: 35, scope: !1316)
!1320 = !DILocation(line: 678, column: 39, scope: !1321)
!1321 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 3)
!1322 = !DILocation(line: 678, column: 38, scope: !1321)
!1323 = !DILocation(line: 678, column: 43, scope: !1321)
!1324 = !DILocation(line: 678, column: 35, scope: !1321)
!1325 = !DILocation(line: 678, column: 2, scope: !1326)
!1326 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 4)
!1327 = !DILocation(line: 679, column: 3, scope: !377)
!1328 = !DILocation(line: 678, column: 2, scope: !1329)
!1329 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 5)
!1330 = !DILocation(line: 682, column: 21, scope: !1331)
!1331 = distinct !DILexicalBlock(scope: !377, file: !1, line: 682, column: 6)
!1332 = !DILocation(line: 682, column: 26, scope: !1331)
!1333 = !DILocation(line: 682, column: 32, scope: !1331)
!1334 = !DILocation(line: 682, column: 30, scope: !1331)
!1335 = !DILocation(line: 682, column: 13, scope: !1331)
!1336 = !DILocation(line: 682, column: 11, scope: !1331)
!1337 = !DILocation(line: 682, column: 49, scope: !1331)
!1338 = !DILocation(line: 682, column: 6, scope: !377)
!1339 = !DILocation(line: 684, column: 10, scope: !1340)
!1340 = distinct !DILexicalBlock(scope: !1331, file: !1, line: 682, column: 58)
!1341 = !DILocation(line: 684, column: 3, scope: !1340)
!1342 = !DILocation(line: 688, column: 11, scope: !1343)
!1343 = distinct !DILexicalBlock(scope: !377, file: !1, line: 688, column: 2)
!1344 = !DILocation(line: 688, column: 9, scope: !1343)
!1345 = !DILocation(line: 688, column: 7, scope: !1343)
!1346 = !DILocation(line: 688, column: 16, scope: !1347)
!1347 = !DILexicalBlockFile(scope: !1348, file: !1, discriminator: 1)
!1348 = distinct !DILexicalBlock(scope: !1343, file: !1, line: 688, column: 2)
!1349 = !DILocation(line: 688, column: 20, scope: !1347)
!1350 = !DILocation(line: 688, column: 18, scope: !1347)
!1351 = !DILocation(line: 688, column: 2, scope: !1347)
!1352 = !DILocation(line: 689, column: 7, scope: !1353)
!1353 = distinct !DILexicalBlock(scope: !1354, file: !1, line: 689, column: 7)
!1354 = distinct !DILexicalBlock(scope: !1348, file: !1, line: 688, column: 30)
!1355 = !DILocation(line: 689, column: 7, scope: !1354)
!1356 = !DILocation(line: 690, column: 11, scope: !1353)
!1357 = !DILocation(line: 690, column: 4, scope: !1353)
!1358 = !DILocation(line: 691, column: 2, scope: !1354)
!1359 = !DILocation(line: 688, column: 26, scope: !1360)
!1360 = !DILexicalBlockFile(scope: !1348, file: !1, discriminator: 2)
!1361 = !DILocation(line: 688, column: 2, scope: !1360)
!1362 = !DILocation(line: 694, column: 6, scope: !1363)
!1363 = distinct !DILexicalBlock(scope: !377, file: !1, line: 694, column: 6)
!1364 = !DILocation(line: 694, column: 13, scope: !1363)
!1365 = !DILocation(line: 694, column: 17, scope: !1363)
!1366 = !DILocation(line: 694, column: 10, scope: !1363)
!1367 = !DILocation(line: 694, column: 6, scope: !377)
!1368 = !DILocation(line: 695, column: 10, scope: !1363)
!1369 = !DILocation(line: 695, column: 3, scope: !1363)
!1370 = !DILocation(line: 698, column: 6, scope: !377)
!1371 = !DILocation(line: 701, column: 13, scope: !1372)
!1372 = distinct !DILexicalBlock(scope: !377, file: !1, line: 701, column: 6)
!1373 = !DILocation(line: 701, column: 6, scope: !1372)
!1374 = !DILocation(line: 701, column: 30, scope: !1372)
!1375 = !DILocation(line: 701, column: 6, scope: !377)
!1376 = !DILocation(line: 704, column: 2, scope: !1377)
!1377 = distinct !DILexicalBlock(scope: !1372, file: !1, line: 701, column: 36)
!1378 = !DILocation(line: 704, column: 20, scope: !1379)
!1379 = !DILexicalBlockFile(scope: !1380, file: !1, discriminator: 1)
!1380 = distinct !DILexicalBlock(scope: !1372, file: !1, line: 704, column: 13)
!1381 = !DILocation(line: 704, column: 13, scope: !1379)
!1382 = !DILocation(line: 704, column: 37, scope: !1379)
!1383 = !DILocation(line: 704, column: 42, scope: !1379)
!1384 = !DILocation(line: 705, column: 13, scope: !1380)
!1385 = !DILocation(line: 705, column: 6, scope: !1380)
!1386 = !DILocation(line: 705, column: 29, scope: !1380)
!1387 = !DILocation(line: 704, column: 13, scope: !1388)
!1388 = !DILexicalBlockFile(scope: !1372, file: !1, discriminator: 2)
!1389 = !DILocation(line: 707, column: 3, scope: !1390)
!1390 = distinct !DILexicalBlock(scope: !1380, file: !1, line: 705, column: 35)
!1391 = !DILocation(line: 707, column: 10, scope: !1392)
!1392 = !DILexicalBlockFile(scope: !1390, file: !1, discriminator: 1)
!1393 = !DILocation(line: 707, column: 16, scope: !1392)
!1394 = !DILocation(line: 707, column: 14, scope: !1392)
!1395 = !DILocation(line: 707, column: 20, scope: !1392)
!1396 = !DILocation(line: 707, column: 27, scope: !1397)
!1397 = !DILexicalBlockFile(scope: !1390, file: !1, discriminator: 2)
!1398 = !DILocation(line: 707, column: 23, scope: !1397)
!1399 = !DILocation(line: 707, column: 30, scope: !1397)
!1400 = !DILocation(line: 707, column: 3, scope: !1401)
!1401 = !DILexicalBlockFile(scope: !1390, file: !1, discriminator: 3)
!1402 = !DILocation(line: 707, column: 3, scope: !1403)
!1403 = !DILexicalBlockFile(scope: !1390, file: !1, discriminator: 4)
!1404 = !DILocation(line: 708, column: 2, scope: !1390)
!1405 = !DILocation(line: 710, column: 10, scope: !1406)
!1406 = distinct !DILexicalBlock(scope: !1380, file: !1, line: 708, column: 9)
!1407 = !DILocation(line: 710, column: 3, scope: !1406)
!1408 = !DILocation(line: 712, column: 12, scope: !377)
!1409 = !DILocation(line: 712, column: 6, scope: !377)
!1410 = !DILocation(line: 712, column: 10, scope: !377)
!1411 = !DILocation(line: 713, column: 12, scope: !377)
!1412 = !DILocation(line: 713, column: 18, scope: !377)
!1413 = !DILocation(line: 713, column: 16, scope: !377)
!1414 = !DILocation(line: 713, column: 6, scope: !377)
!1415 = !DILocation(line: 713, column: 10, scope: !377)
!1416 = !DILocation(line: 714, column: 9, scope: !377)
!1417 = !DILocation(line: 714, column: 2, scope: !377)
!1418 = !DILocation(line: 715, column: 1, scope: !377)
!1419 = !DILocalVariable(name: "buf", arg: 1, scope: !385, file: !1, line: 778, type: !107)
!1420 = !DILocation(line: 778, column: 25, scope: !385)
!1421 = !DILocalVariable(name: "bsz", arg: 2, scope: !385, file: !1, line: 778, type: !72)
!1422 = !DILocation(line: 778, column: 37, scope: !385)
!1423 = !DILocalVariable(name: "val", scope: !385, file: !1, line: 781, type: !107)
!1424 = !DILocation(line: 781, column: 14, scope: !385)
!1425 = !DILocalVariable(name: "eol", scope: !385, file: !1, line: 781, type: !107)
!1426 = !DILocation(line: 781, column: 20, scope: !385)
!1427 = !DILocalVariable(name: "on", scope: !385, file: !1, line: 782, type: !122)
!1428 = !DILocation(line: 782, column: 8, scope: !385)
!1429 = !DILocalVariable(name: "res", scope: !385, file: !1, line: 783, type: !319)
!1430 = !DILocation(line: 783, column: 9, scope: !385)
!1431 = !DILocation(line: 785, column: 21, scope: !1432)
!1432 = distinct !DILexicalBlock(scope: !385, file: !1, line: 785, column: 6)
!1433 = !DILocation(line: 785, column: 26, scope: !1432)
!1434 = !DILocation(line: 785, column: 13, scope: !1432)
!1435 = !DILocation(line: 785, column: 11, scope: !1432)
!1436 = !DILocation(line: 785, column: 57, scope: !1432)
!1437 = !DILocation(line: 785, column: 6, scope: !385)
!1438 = !DILocation(line: 787, column: 3, scope: !1439)
!1439 = distinct !DILexicalBlock(scope: !1432, file: !1, line: 785, column: 66)
!1440 = !DILocation(line: 789, column: 6, scope: !385)
!1441 = !DILocation(line: 790, column: 28, scope: !1442)
!1442 = distinct !DILexicalBlock(scope: !385, file: !1, line: 790, column: 6)
!1443 = !DILocation(line: 790, column: 33, scope: !1442)
!1444 = !DILocation(line: 790, column: 39, scope: !1442)
!1445 = !DILocation(line: 790, column: 37, scope: !1442)
!1446 = !DILocation(line: 790, column: 45, scope: !1442)
!1447 = !DILocation(line: 790, column: 43, scope: !1442)
!1448 = !DILocation(line: 790, column: 13, scope: !1442)
!1449 = !DILocation(line: 790, column: 11, scope: !1442)
!1450 = !DILocation(line: 790, column: 51, scope: !1442)
!1451 = !DILocation(line: 790, column: 6, scope: !385)
!1452 = !DILocation(line: 792, column: 3, scope: !1453)
!1453 = distinct !DILexicalBlock(scope: !1442, file: !1, line: 790, column: 61)
!1454 = !DILocation(line: 796, column: 21, scope: !385)
!1455 = !DILocation(line: 796, column: 8, scope: !385)
!1456 = !DILocation(line: 796, column: 6, scope: !385)
!1457 = !DILocation(line: 797, column: 6, scope: !1458)
!1458 = distinct !DILexicalBlock(scope: !385, file: !1, line: 797, column: 6)
!1459 = !DILocation(line: 797, column: 12, scope: !1458)
!1460 = !DILocation(line: 797, column: 9, scope: !1458)
!1461 = !DILocation(line: 797, column: 6, scope: !385)
!1462 = !DILocation(line: 799, column: 3, scope: !1463)
!1463 = distinct !DILexicalBlock(scope: !1458, file: !1, line: 797, column: 17)
!1464 = !DILocation(line: 801, column: 9, scope: !385)
!1465 = !DILocation(line: 801, column: 2, scope: !385)
!1466 = !DILocation(line: 802, column: 1, scope: !385)
!1467 = !DILocalVariable(name: "hay", arg: 1, scope: !337, file: !1, line: 429, type: !107)
!1468 = !DILocation(line: 429, column: 21, scope: !337)
!1469 = !DILocalVariable(name: "haysize", arg: 2, scope: !337, file: !1, line: 429, type: !340)
!1470 = !DILocation(line: 429, column: 39, scope: !337)
!1471 = !DILocalVariable(name: "needle", arg: 3, scope: !337, file: !1, line: 430, type: !107)
!1472 = !DILocation(line: 430, column: 14, scope: !337)
!1473 = !DILocalVariable(name: "needlesize", arg: 4, scope: !337, file: !1, line: 430, type: !340)
!1474 = !DILocation(line: 430, column: 35, scope: !337)
!1475 = !DILocalVariable(name: "eoh", scope: !337, file: !1, line: 432, type: !1476)
!1476 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !107)
!1477 = !DILocation(line: 432, column: 20, scope: !337)
!1478 = !DILocation(line: 432, column: 26, scope: !337)
!1479 = !DILocation(line: 432, column: 32, scope: !337)
!1480 = !DILocation(line: 432, column: 30, scope: !337)
!1481 = !DILocalVariable(name: "eon", scope: !337, file: !1, line: 433, type: !1476)
!1482 = !DILocation(line: 433, column: 20, scope: !337)
!1483 = !DILocation(line: 433, column: 26, scope: !337)
!1484 = !DILocation(line: 433, column: 35, scope: !337)
!1485 = !DILocation(line: 433, column: 33, scope: !337)
!1486 = !DILocalVariable(name: "hp", scope: !337, file: !1, line: 434, type: !107)
!1487 = !DILocation(line: 434, column: 14, scope: !337)
!1488 = !DILocalVariable(name: "np", scope: !337, file: !1, line: 435, type: !107)
!1489 = !DILocation(line: 435, column: 14, scope: !337)
!1490 = !DILocalVariable(name: "cand", scope: !337, file: !1, line: 436, type: !107)
!1491 = !DILocation(line: 436, column: 14, scope: !337)
!1492 = !DILocalVariable(name: "hsum", scope: !337, file: !1, line: 437, type: !40)
!1493 = !DILocation(line: 437, column: 15, scope: !337)
!1494 = !DILocalVariable(name: "nsum", scope: !337, file: !1, line: 438, type: !40)
!1495 = !DILocation(line: 438, column: 15, scope: !337)
!1496 = !DILocalVariable(name: "eqp", scope: !337, file: !1, line: 439, type: !40)
!1497 = !DILocation(line: 439, column: 15, scope: !337)
!1498 = !DILocation(line: 445, column: 6, scope: !1499)
!1499 = distinct !DILexicalBlock(scope: !337, file: !1, line: 445, column: 6)
!1500 = !DILocation(line: 445, column: 17, scope: !1499)
!1501 = !DILocation(line: 445, column: 6, scope: !337)
!1502 = !DILocation(line: 446, column: 18, scope: !1503)
!1503 = distinct !DILexicalBlock(scope: !1499, file: !1, line: 445, column: 25)
!1504 = !DILocation(line: 446, column: 10, scope: !1503)
!1505 = !DILocation(line: 446, column: 3, scope: !1503)
!1506 = !DILocation(line: 447, column: 27, scope: !1507)
!1507 = distinct !DILexicalBlock(scope: !1499, file: !1, line: 447, column: 13)
!1508 = !DILocation(line: 447, column: 33, scope: !1507)
!1509 = !DILocation(line: 447, column: 32, scope: !1507)
!1510 = !DILocation(line: 447, column: 41, scope: !1507)
!1511 = !DILocation(line: 447, column: 20, scope: !1507)
!1512 = !DILocation(line: 447, column: 18, scope: !1507)
!1513 = !DILocation(line: 447, column: 51, scope: !1507)
!1514 = !DILocation(line: 447, column: 13, scope: !1499)
!1515 = !DILocation(line: 449, column: 3, scope: !1516)
!1516 = distinct !DILexicalBlock(scope: !1507, file: !1, line: 447, column: 60)
!1517 = !DILocation(line: 456, column: 12, scope: !1518)
!1518 = distinct !DILexicalBlock(scope: !337, file: !1, line: 456, column: 2)
!1519 = !DILocation(line: 456, column: 16, scope: !1518)
!1520 = !DILocation(line: 456, column: 10, scope: !1518)
!1521 = !DILocation(line: 456, column: 27, scope: !1518)
!1522 = !DILocation(line: 456, column: 34, scope: !1518)
!1523 = !DILocation(line: 456, column: 25, scope: !1518)
!1524 = !DILocation(line: 456, column: 48, scope: !1518)
!1525 = !DILocation(line: 456, column: 47, scope: !1518)
!1526 = !DILocation(line: 456, column: 45, scope: !1518)
!1527 = !DILocation(line: 456, column: 61, scope: !1518)
!1528 = !DILocation(line: 456, column: 60, scope: !1518)
!1529 = !DILocation(line: 456, column: 58, scope: !1518)
!1530 = !DILocation(line: 456, column: 70, scope: !1518)
!1531 = !DILocation(line: 456, column: 7, scope: !1518)
!1532 = !DILocation(line: 457, column: 7, scope: !1533)
!1533 = distinct !DILexicalBlock(scope: !1518, file: !1, line: 456, column: 2)
!1534 = !DILocation(line: 457, column: 12, scope: !1533)
!1535 = !DILocation(line: 457, column: 10, scope: !1533)
!1536 = !DILocation(line: 457, column: 16, scope: !1533)
!1537 = !DILocation(line: 457, column: 19, scope: !1538)
!1538 = !DILexicalBlockFile(scope: !1533, file: !1, discriminator: 1)
!1539 = !DILocation(line: 457, column: 24, scope: !1538)
!1540 = !DILocation(line: 457, column: 22, scope: !1538)
!1541 = !DILocation(line: 456, column: 2, scope: !1542)
!1542 = !DILexicalBlockFile(scope: !1518, file: !1, discriminator: 1)
!1543 = !DILocation(line: 456, column: 2, scope: !1544)
!1544 = !DILexicalBlockFile(scope: !1518, file: !1, discriminator: 2)
!1545 = !DILocation(line: 458, column: 16, scope: !1533)
!1546 = !DILocation(line: 458, column: 15, scope: !1533)
!1547 = !DILocation(line: 458, column: 12, scope: !1533)
!1548 = !DILocation(line: 458, column: 29, scope: !1533)
!1549 = !DILocation(line: 458, column: 28, scope: !1533)
!1550 = !DILocation(line: 458, column: 25, scope: !1533)
!1551 = !DILocation(line: 458, column: 41, scope: !1533)
!1552 = !DILocation(line: 458, column: 40, scope: !1533)
!1553 = !DILocation(line: 458, column: 48, scope: !1533)
!1554 = !DILocation(line: 458, column: 47, scope: !1533)
!1555 = !DILocation(line: 458, column: 44, scope: !1533)
!1556 = !DILocation(line: 458, column: 37, scope: !1533)
!1557 = !DILocation(line: 458, column: 54, scope: !1533)
!1558 = !DILocation(line: 458, column: 60, scope: !1533)
!1559 = !DILocation(line: 456, column: 2, scope: !1560)
!1560 = !DILexicalBlockFile(scope: !1533, file: !1, discriminator: 3)
!1561 = !DILocation(line: 461, column: 6, scope: !1562)
!1562 = distinct !DILexicalBlock(scope: !337, file: !1, line: 461, column: 6)
!1563 = !DILocation(line: 461, column: 11, scope: !1562)
!1564 = !DILocation(line: 461, column: 9, scope: !1562)
!1565 = !DILocation(line: 461, column: 6, scope: !337)
!1566 = !DILocation(line: 463, column: 3, scope: !1567)
!1567 = distinct !DILexicalBlock(scope: !1562, file: !1, line: 461, column: 16)
!1568 = !DILocation(line: 464, column: 13, scope: !1569)
!1569 = distinct !DILexicalBlock(scope: !1562, file: !1, line: 464, column: 13)
!1570 = !DILocation(line: 464, column: 13, scope: !1562)
!1571 = !DILocation(line: 466, column: 18, scope: !1572)
!1572 = distinct !DILexicalBlock(scope: !1569, file: !1, line: 464, column: 18)
!1573 = !DILocation(line: 466, column: 10, scope: !1572)
!1574 = !DILocation(line: 466, column: 3, scope: !1572)
!1575 = !DILocation(line: 471, column: 14, scope: !1576)
!1576 = distinct !DILexicalBlock(scope: !337, file: !1, line: 471, column: 2)
!1577 = !DILocation(line: 471, column: 12, scope: !1576)
!1578 = !DILocation(line: 471, column: 7, scope: !1576)
!1579 = !DILocation(line: 471, column: 19, scope: !1580)
!1580 = !DILexicalBlockFile(scope: !1581, file: !1, discriminator: 1)
!1581 = distinct !DILexicalBlock(scope: !1576, file: !1, line: 471, column: 2)
!1582 = !DILocation(line: 471, column: 24, scope: !1580)
!1583 = !DILocation(line: 471, column: 22, scope: !1580)
!1584 = !DILocation(line: 471, column: 2, scope: !1580)
!1585 = !DILocation(line: 472, column: 16, scope: !1586)
!1586 = distinct !DILexicalBlock(scope: !1581, file: !1, line: 471, column: 35)
!1587 = !DILocation(line: 472, column: 11, scope: !1586)
!1588 = !DILocation(line: 472, column: 8, scope: !1586)
!1589 = !DILocation(line: 473, column: 12, scope: !1586)
!1590 = !DILocation(line: 473, column: 11, scope: !1586)
!1591 = !DILocation(line: 473, column: 8, scope: !1586)
!1592 = !DILocation(line: 479, column: 7, scope: !1593)
!1593 = distinct !DILexicalBlock(scope: !1586, file: !1, line: 479, column: 7)
!1594 = !DILocation(line: 479, column: 15, scope: !1593)
!1595 = !DILocation(line: 479, column: 12, scope: !1593)
!1596 = !DILocation(line: 479, column: 20, scope: !1593)
!1597 = !DILocation(line: 479, column: 30, scope: !1598)
!1598 = !DILexicalBlockFile(scope: !1593, file: !1, discriminator: 1)
!1599 = !DILocation(line: 479, column: 36, scope: !1598)
!1600 = !DILocation(line: 479, column: 44, scope: !1598)
!1601 = !DILocation(line: 479, column: 55, scope: !1598)
!1602 = !DILocation(line: 479, column: 23, scope: !1598)
!1603 = !DILocation(line: 479, column: 61, scope: !1598)
!1604 = !DILocation(line: 479, column: 7, scope: !1598)
!1605 = !DILocation(line: 480, column: 19, scope: !1606)
!1606 = distinct !DILexicalBlock(scope: !1593, file: !1, line: 479, column: 67)
!1607 = !DILocation(line: 480, column: 11, scope: !1606)
!1608 = !DILocation(line: 480, column: 4, scope: !1606)
!1609 = !DILocation(line: 482, column: 2, scope: !1586)
!1610 = !DILocation(line: 471, column: 31, scope: !1611)
!1611 = !DILexicalBlockFile(scope: !1581, file: !1, discriminator: 2)
!1612 = !DILocation(line: 471, column: 2, scope: !1611)
!1613 = !DILocation(line: 483, column: 2, scope: !337)
!1614 = !DILocation(line: 484, column: 1, scope: !337)
!1615 = !DILocalVariable(name: "c", arg: 1, scope: !341, file: !1, line: 423, type: !70)
!1616 = !DILocation(line: 423, column: 21, scope: !341)
!1617 = !DILocation(line: 425, column: 39, scope: !341)
!1618 = !DILocation(line: 425, column: 42, scope: !341)
!1619 = !DILocation(line: 425, column: 21, scope: !341)
!1620 = !DILocation(line: 425, column: 2, scope: !341)
!1621 = !DILocalVariable(name: "buf", arg: 1, scope: !347, file: !1, line: 817, type: !107)
!1622 = !DILocation(line: 817, column: 28, scope: !347)
!1623 = !DILocalVariable(name: "bsz", arg: 2, scope: !347, file: !1, line: 817, type: !72)
!1624 = !DILocation(line: 817, column: 40, scope: !347)
!1625 = !DILocalVariable(name: "hit", scope: !347, file: !1, line: 820, type: !107)
!1626 = !DILocation(line: 820, column: 14, scope: !347)
!1627 = !DILocation(line: 820, column: 28, scope: !347)
!1628 = !DILocation(line: 820, column: 33, scope: !347)
!1629 = !DILocation(line: 820, column: 20, scope: !347)
!1630 = !DILocation(line: 822, column: 9, scope: !347)
!1631 = !DILocation(line: 822, column: 2, scope: !347)
!1632 = !DILocalVariable(name: "s", arg: 1, scope: !351, file: !1, line: 535, type: !107)
!1633 = !DILocation(line: 535, column: 26, scope: !351)
!1634 = !DILocalVariable(name: "endptr", arg: 2, scope: !351, file: !1, line: 535, type: !354)
!1635 = !DILocation(line: 535, column: 36, scope: !351)
!1636 = !DILocalVariable(name: "tm", scope: !351, file: !1, line: 538, type: !363)
!1637 = !DILocation(line: 538, column: 12, scope: !351)
!1638 = !DILocalVariable(name: "res", scope: !351, file: !1, line: 539, type: !319)
!1639 = !DILocation(line: 539, column: 9, scope: !351)
!1640 = !DILocation(line: 542, column: 2, scope: !351)
!1641 = !DILocation(line: 546, column: 2, scope: !351)
!1642 = !DILocation(line: 546, column: 10, scope: !1643)
!1643 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 1)
!1644 = !DILocation(line: 546, column: 9, scope: !1643)
!1645 = !DILocation(line: 546, column: 12, scope: !1643)
!1646 = !DILocation(line: 546, column: 19, scope: !1643)
!1647 = !DILocation(line: 546, column: 23, scope: !1648)
!1648 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 2)
!1649 = !DILocation(line: 546, column: 22, scope: !1648)
!1650 = !DILocation(line: 546, column: 25, scope: !1648)
!1651 = !DILocation(line: 546, column: 19, scope: !1648)
!1652 = !DILocation(line: 546, column: 2, scope: !1653)
!1653 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 3)
!1654 = !DILocation(line: 547, column: 3, scope: !351)
!1655 = !DILocation(line: 546, column: 2, scope: !1656)
!1656 = !DILexicalBlockFile(scope: !351, file: !1, discriminator: 4)
!1657 = !DILocation(line: 550, column: 31, scope: !1658)
!1658 = distinct !DILexicalBlock(scope: !351, file: !1, line: 550, column: 6)
!1659 = !DILocation(line: 550, column: 20, scope: !1658)
!1660 = !DILocation(line: 550, column: 10, scope: !1658)
!1661 = !DILocation(line: 550, column: 18, scope: !1658)
!1662 = !DILocation(line: 550, column: 51, scope: !1658)
!1663 = !DILocation(line: 550, column: 55, scope: !1658)
!1664 = !DILocation(line: 550, column: 60, scope: !1665)
!1665 = !DILexicalBlockFile(scope: !1658, file: !1, discriminator: 1)
!1666 = !DILocation(line: 550, column: 58, scope: !1665)
!1667 = !DILocation(line: 550, column: 63, scope: !1665)
!1668 = !DILocation(line: 550, column: 6, scope: !1665)
!1669 = !DILocation(line: 551, column: 3, scope: !1670)
!1670 = distinct !DILexicalBlock(scope: !1658, file: !1, line: 550, column: 71)
!1671 = !DILocation(line: 554, column: 30, scope: !1672)
!1672 = distinct !DILexicalBlock(scope: !351, file: !1, line: 554, column: 6)
!1673 = !DILocation(line: 554, column: 19, scope: !1672)
!1674 = !DILocation(line: 554, column: 10, scope: !1672)
!1675 = !DILocation(line: 554, column: 17, scope: !1672)
!1676 = !DILocation(line: 554, column: 45, scope: !1672)
!1677 = !DILocation(line: 554, column: 49, scope: !1672)
!1678 = !DILocation(line: 554, column: 54, scope: !1679)
!1679 = !DILexicalBlockFile(scope: !1672, file: !1, discriminator: 1)
!1680 = !DILocation(line: 554, column: 52, scope: !1679)
!1681 = !DILocation(line: 554, column: 57, scope: !1679)
!1682 = !DILocation(line: 554, column: 6, scope: !1679)
!1683 = !DILocation(line: 555, column: 3, scope: !1684)
!1684 = distinct !DILexicalBlock(scope: !1672, file: !1, line: 554, column: 65)
!1685 = !DILocation(line: 558, column: 31, scope: !1686)
!1686 = distinct !DILexicalBlock(scope: !351, file: !1, line: 558, column: 6)
!1687 = !DILocation(line: 558, column: 20, scope: !1686)
!1688 = !DILocation(line: 558, column: 10, scope: !1686)
!1689 = !DILocation(line: 558, column: 18, scope: !1686)
!1690 = !DILocation(line: 558, column: 46, scope: !1686)
!1691 = !DILocation(line: 558, column: 50, scope: !1686)
!1692 = !DILocation(line: 558, column: 55, scope: !1693)
!1693 = !DILexicalBlockFile(scope: !1686, file: !1, discriminator: 1)
!1694 = !DILocation(line: 558, column: 53, scope: !1693)
!1695 = !DILocation(line: 558, column: 58, scope: !1693)
!1696 = !DILocation(line: 558, column: 6, scope: !1693)
!1697 = !DILocation(line: 559, column: 3, scope: !1698)
!1698 = distinct !DILexicalBlock(scope: !1686, file: !1, line: 558, column: 66)
!1699 = !DILocation(line: 562, column: 31, scope: !1700)
!1700 = distinct !DILexicalBlock(scope: !351, file: !1, line: 562, column: 6)
!1701 = !DILocation(line: 562, column: 20, scope: !1700)
!1702 = !DILocation(line: 562, column: 10, scope: !1700)
!1703 = !DILocation(line: 562, column: 18, scope: !1700)
!1704 = !DILocation(line: 562, column: 46, scope: !1700)
!1705 = !DILocation(line: 562, column: 50, scope: !1700)
!1706 = !DILocation(line: 562, column: 55, scope: !1707)
!1707 = !DILexicalBlockFile(scope: !1700, file: !1, discriminator: 1)
!1708 = !DILocation(line: 562, column: 53, scope: !1707)
!1709 = !DILocation(line: 562, column: 58, scope: !1707)
!1710 = !DILocation(line: 562, column: 6, scope: !1707)
!1711 = !DILocation(line: 563, column: 3, scope: !1712)
!1712 = distinct !DILexicalBlock(scope: !1700, file: !1, line: 562, column: 66)
!1713 = !DILocation(line: 566, column: 30, scope: !1714)
!1714 = distinct !DILexicalBlock(scope: !351, file: !1, line: 566, column: 6)
!1715 = !DILocation(line: 566, column: 19, scope: !1714)
!1716 = !DILocation(line: 566, column: 10, scope: !1714)
!1717 = !DILocation(line: 566, column: 17, scope: !1714)
!1718 = !DILocation(line: 566, column: 45, scope: !1714)
!1719 = !DILocation(line: 566, column: 49, scope: !1714)
!1720 = !DILocation(line: 566, column: 54, scope: !1721)
!1721 = !DILexicalBlockFile(scope: !1714, file: !1, discriminator: 1)
!1722 = !DILocation(line: 566, column: 52, scope: !1721)
!1723 = !DILocation(line: 566, column: 57, scope: !1721)
!1724 = !DILocation(line: 566, column: 6, scope: !1721)
!1725 = !DILocation(line: 567, column: 3, scope: !1726)
!1726 = distinct !DILexicalBlock(scope: !1714, file: !1, line: 566, column: 65)
!1727 = !DILocation(line: 570, column: 30, scope: !1728)
!1728 = distinct !DILexicalBlock(scope: !351, file: !1, line: 570, column: 6)
!1729 = !DILocation(line: 570, column: 19, scope: !1728)
!1730 = !DILocation(line: 570, column: 10, scope: !1728)
!1731 = !DILocation(line: 570, column: 17, scope: !1728)
!1732 = !DILocation(line: 570, column: 45, scope: !1728)
!1733 = !DILocation(line: 570, column: 49, scope: !1728)
!1734 = !DILocation(line: 570, column: 54, scope: !1735)
!1735 = !DILexicalBlockFile(scope: !1728, file: !1, discriminator: 1)
!1736 = !DILocation(line: 570, column: 52, scope: !1735)
!1737 = !DILocation(line: 570, column: 57, scope: !1735)
!1738 = !DILocation(line: 570, column: 6, scope: !1735)
!1739 = !DILocation(line: 571, column: 3, scope: !1740)
!1740 = distinct !DILexicalBlock(scope: !1728, file: !1, line: 570, column: 65)
!1741 = !DILocation(line: 575, column: 5, scope: !351)
!1742 = !DILocation(line: 575, column: 13, scope: !351)
!1743 = !DILocation(line: 576, column: 5, scope: !351)
!1744 = !DILocation(line: 576, column: 11, scope: !351)
!1745 = !DILocation(line: 579, column: 8, scope: !351)
!1746 = !DILocation(line: 579, column: 6, scope: !351)
!1747 = !DILocation(line: 579, column: 2, scope: !351)
!1748 = !DILocation(line: 582, column: 6, scope: !1749)
!1749 = distinct !DILexicalBlock(scope: !351, file: !1, line: 582, column: 6)
!1750 = !DILocation(line: 582, column: 13, scope: !1749)
!1751 = !DILocation(line: 582, column: 6, scope: !351)
!1752 = !DILocation(line: 583, column: 21, scope: !1753)
!1753 = distinct !DILexicalBlock(scope: !1749, file: !1, line: 582, column: 22)
!1754 = !DILocation(line: 583, column: 13, scope: !1753)
!1755 = !DILocation(line: 583, column: 4, scope: !1753)
!1756 = !DILocation(line: 583, column: 11, scope: !1753)
!1757 = !DILocation(line: 584, column: 2, scope: !1753)
!1758 = !DILocation(line: 585, column: 9, scope: !351)
!1759 = !DILocation(line: 585, column: 2, scope: !351)
!1760 = !DILocalVariable(name: "str", arg: 1, scope: !355, file: !1, line: 487, type: !107)
!1761 = !DILocation(line: 487, column: 24, scope: !355)
!1762 = !DILocalVariable(name: "ep", arg: 2, scope: !355, file: !1, line: 487, type: !358)
!1763 = !DILocation(line: 487, column: 42, scope: !355)
!1764 = !DILocalVariable(name: "llim", arg: 3, scope: !355, file: !1, line: 487, type: !50)
!1765 = !DILocation(line: 487, column: 50, scope: !355)
!1766 = !DILocalVariable(name: "ulim", arg: 4, scope: !355, file: !1, line: 487, type: !50)
!1767 = !DILocation(line: 487, column: 60, scope: !355)
!1768 = !DILocalVariable(name: "res", scope: !355, file: !1, line: 489, type: !50)
!1769 = !DILocation(line: 489, column: 6, scope: !355)
!1770 = !DILocalVariable(name: "sp", scope: !355, file: !1, line: 490, type: !107)
!1771 = !DILocation(line: 490, column: 14, scope: !355)
!1772 = !DILocalVariable(name: "rulim", scope: !355, file: !1, line: 492, type: !50)
!1773 = !DILocation(line: 492, column: 6, scope: !355)
!1774 = !DILocation(line: 494, column: 12, scope: !1775)
!1775 = distinct !DILexicalBlock(scope: !355, file: !1, line: 494, column: 2)
!1776 = !DILocation(line: 494, column: 10, scope: !1775)
!1777 = !DILocation(line: 494, column: 25, scope: !1775)
!1778 = !DILocation(line: 494, column: 30, scope: !1775)
!1779 = !DILocation(line: 494, column: 37, scope: !1780)
!1780 = !DILexicalBlockFile(scope: !1775, file: !1, discriminator: 1)
!1781 = !DILocation(line: 494, column: 25, scope: !1780)
!1782 = !DILocation(line: 494, column: 25, scope: !1783)
!1783 = !DILexicalBlockFile(scope: !1775, file: !1, discriminator: 2)
!1784 = !DILocation(line: 494, column: 25, scope: !1785)
!1785 = !DILexicalBlockFile(scope: !1775, file: !1, discriminator: 3)
!1786 = !DILocation(line: 494, column: 23, scope: !1785)
!1787 = !DILocation(line: 494, column: 7, scope: !1785)
!1788 = !DILocation(line: 495, column: 7, scope: !1789)
!1789 = distinct !DILexicalBlock(scope: !1775, file: !1, line: 494, column: 2)
!1790 = !DILocation(line: 495, column: 11, scope: !1789)
!1791 = !DILocation(line: 495, column: 19, scope: !1789)
!1792 = !DILocation(line: 495, column: 16, scope: !1789)
!1793 = !DILocation(line: 495, column: 24, scope: !1789)
!1794 = !DILocation(line: 495, column: 27, scope: !1795)
!1795 = !DILexicalBlockFile(scope: !1789, file: !1, discriminator: 1)
!1796 = !DILocation(line: 495, column: 33, scope: !1795)
!1797 = !DILocation(line: 495, column: 37, scope: !1798)
!1798 = !DILexicalBlockFile(scope: !1789, file: !1, discriminator: 2)
!1799 = !DILocation(line: 495, column: 36, scope: !1798)
!1800 = !DILocation(line: 495, column: 40, scope: !1798)
!1801 = !DILocation(line: 495, column: 47, scope: !1798)
!1802 = !DILocation(line: 495, column: 51, scope: !1803)
!1803 = !DILexicalBlockFile(scope: !1789, file: !1, discriminator: 3)
!1804 = !DILocation(line: 495, column: 50, scope: !1803)
!1805 = !DILocation(line: 495, column: 54, scope: !1803)
!1806 = !DILocation(line: 494, column: 2, scope: !1807)
!1807 = !DILexicalBlockFile(scope: !1775, file: !1, discriminator: 4)
!1808 = !DILocation(line: 497, column: 7, scope: !1809)
!1809 = distinct !DILexicalBlock(scope: !1789, file: !1, line: 496, column: 26)
!1810 = !DILocation(line: 498, column: 11, scope: !1809)
!1811 = !DILocation(line: 498, column: 10, scope: !1809)
!1812 = !DILocation(line: 498, column: 14, scope: !1809)
!1813 = !DILocation(line: 498, column: 7, scope: !1809)
!1814 = !DILocation(line: 499, column: 2, scope: !1809)
!1815 = !DILocation(line: 496, column: 9, scope: !1789)
!1816 = !DILocation(line: 496, column: 19, scope: !1789)
!1817 = !DILocation(line: 494, column: 2, scope: !1818)
!1818 = !DILexicalBlockFile(scope: !1789, file: !1, discriminator: 5)
!1819 = !DILocation(line: 500, column: 6, scope: !1820)
!1820 = distinct !DILexicalBlock(scope: !355, file: !1, line: 500, column: 6)
!1821 = !DILocation(line: 500, column: 12, scope: !1820)
!1822 = !DILocation(line: 500, column: 9, scope: !1820)
!1823 = !DILocation(line: 500, column: 6, scope: !355)
!1824 = !DILocation(line: 501, column: 7, scope: !1825)
!1825 = distinct !DILexicalBlock(scope: !1820, file: !1, line: 500, column: 17)
!1826 = !DILocation(line: 502, column: 2, scope: !1825)
!1827 = !DILocation(line: 502, column: 13, scope: !1828)
!1828 = !DILexicalBlockFile(scope: !1829, file: !1, discriminator: 1)
!1829 = distinct !DILexicalBlock(scope: !1820, file: !1, line: 502, column: 13)
!1830 = !DILocation(line: 502, column: 19, scope: !1828)
!1831 = !DILocation(line: 502, column: 17, scope: !1828)
!1832 = !DILocation(line: 502, column: 24, scope: !1828)
!1833 = !DILocation(line: 502, column: 27, scope: !1834)
!1834 = !DILexicalBlockFile(scope: !1829, file: !1, discriminator: 2)
!1835 = !DILocation(line: 502, column: 33, scope: !1834)
!1836 = !DILocation(line: 502, column: 31, scope: !1834)
!1837 = !DILocation(line: 502, column: 13, scope: !1834)
!1838 = !DILocation(line: 503, column: 7, scope: !1839)
!1839 = distinct !DILexicalBlock(scope: !1829, file: !1, line: 502, column: 39)
!1840 = !DILocation(line: 504, column: 2, scope: !1839)
!1841 = !DILocation(line: 505, column: 21, scope: !355)
!1842 = !DILocation(line: 505, column: 3, scope: !355)
!1843 = !DILocation(line: 505, column: 6, scope: !355)
!1844 = !DILocation(line: 506, column: 9, scope: !355)
!1845 = !DILocation(line: 506, column: 2, scope: !355)
!1846 = !DILocalVariable(name: "t", arg: 1, scope: !359, file: !1, line: 510, type: !362)
!1847 = !DILocation(line: 510, column: 25, scope: !359)
!1848 = !DILocation(line: 514, column: 24, scope: !359)
!1849 = !DILocation(line: 514, column: 17, scope: !359)
!1850 = !DILocation(line: 514, column: 9, scope: !359)
