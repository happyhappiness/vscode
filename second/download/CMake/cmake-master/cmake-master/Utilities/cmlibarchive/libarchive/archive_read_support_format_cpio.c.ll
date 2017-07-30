; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_cpio.c'
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
%struct.cpio = type { i32, i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)*, %struct.links_entry*, i64, i64, i64, i64, %struct.archive_string_conv*, %struct.archive_string_conv*, i32 }
%struct.links_entry = type { %struct.links_entry*, %struct.links_entry*, i32, i64, i64, i8* }

@.str = private unnamed_addr constant [33 x i8] c"archive_read_support_format_cpio\00", align 1
@.str.1 = private unnamed_addr constant [25 x i8] c"Can't allocate cpio data\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"cpio\00", align 1
@.str.3 = private unnamed_addr constant [7 x i8] c"070707\00", align 1
@.str.4 = private unnamed_addr constant [7 x i8] c"070727\00", align 1
@.str.5 = private unnamed_addr constant [7 x i8] c"070701\00", align 1
@.str.6 = private unnamed_addr constant [7 x i8] c"070702\00", align 1
@.str.7 = private unnamed_addr constant [26 x i8] c"POSIX octet-oriented cpio\00", align 1
@.str.8 = private unnamed_addr constant [45 x i8] c"Skipped %d bytes before finding valid header\00", align 1
@.str.9 = private unnamed_addr constant [17 x i8] c"afio large ASCII\00", align 1
@.str.10 = private unnamed_addr constant [30 x i8] c"ASCII cpio (SVR4 with no CRC)\00", align 1
@.str.11 = private unnamed_addr constant [27 x i8] c"ASCII cpio (SVR4 with CRC)\00", align 1
@.str.12 = private unnamed_addr constant [6 x i8] c"07070\00", align 1
@.str.13 = private unnamed_addr constant [25 x i8] c"cpio (big-endian binary)\00", align 1
@.str.14 = private unnamed_addr constant [44 x i8] c"End of file trying to read next cpio header\00", align 1
@.str.15 = private unnamed_addr constant [28 x i8] c"cpio (little-endian binary)\00", align 1
@.str.16 = private unnamed_addr constant [10 x i8] c"compat-2x\00", align 1
@.str.17 = private unnamed_addr constant [11 x i8] c"hdrcharset\00", align 1
@.str.18 = private unnamed_addr constant [51 x i8] c"cpio: hdrcharset option needs a character-set name\00", align 1
@.str.19 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Pathname\00", align 1
@.str.20 = private unnamed_addr constant [55 x i8] c"Pathname can't be converted from %s to current locale.\00", align 1
@.str.21 = private unnamed_addr constant [69 x i8] c"Rejecting malformed cpio archive: symlink contents exceed 1 megabyte\00", align 1
@.str.22 = private unnamed_addr constant [35 x i8] c"Can't allocate memory for Linkname\00", align 1
@.str.23 = private unnamed_addr constant [55 x i8] c"Linkname can't be converted from %s to current locale.\00", align 1
@.str.24 = private unnamed_addr constant [11 x i8] c"TRAILER!!!\00", align 1
@.str.25 = private unnamed_addr constant [34 x i8] c"Out of memory adding file to list\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_read_support_format_cpio(%struct.archive* %_a) #0 !dbg !325 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %a = alloca %struct.archive_read*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %r = alloca i32, align 4
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !358, metadata !359), !dbg !360
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a, metadata !361, metadata !359), !dbg !362
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !363
  %1 = bitcast %struct.archive* %0 to %struct.archive_read*, !dbg !364
  store %struct.archive_read* %1, %struct.archive_read** %a, align 8, !dbg !362
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !365, metadata !359), !dbg !366
  call void @llvm.dbg.declare(metadata i32* %r, metadata !367, metadata !359), !dbg !368
  br label %do.body, !dbg !369

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !370, metadata !359), !dbg !372
  %2 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !373
  %call = call i32 @__archive_check_magic(%struct.archive* %2, i32 14594245, i32 1, i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str, i32 0, i32 0)), !dbg !373
  store i32 %call, i32* %magic_test, align 4, !dbg !373
  %3 = load i32, i32* %magic_test, align 4, !dbg !373
  %cmp = icmp eq i32 %3, -30, !dbg !373
  br i1 %cmp, label %if.then, label %if.end, !dbg !373

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !375
  br label %return, !dbg !375

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !378

do.end:                                           ; preds = %if.end
  %call1 = call noalias i8* @calloc(i64 1, i64 80) #6, !dbg !380
  %4 = bitcast i8* %call1 to %struct.cpio*, !dbg !381
  store %struct.cpio* %4, %struct.cpio** %cpio, align 8, !dbg !382
  %5 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !383
  %cmp2 = icmp eq %struct.cpio* %5, null, !dbg !385
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !386

if.then3:                                         ; preds = %do.end
  %6 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !387
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %6, i32 0, i32 0, !dbg !389
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.1, i32 0, i32 0)), !dbg !390
  store i32 -30, i32* %retval, align 4, !dbg !391
  br label %return, !dbg !391

if.end4:                                          ; preds = %do.end
  %7 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !392
  %magic = getelementptr inbounds %struct.cpio, %struct.cpio* %7, i32 0, i32 0, !dbg !393
  store i32 320083222, i32* %magic, align 8, !dbg !394
  %8 = load %struct.archive_read*, %struct.archive_read** %a, align 8, !dbg !395
  %9 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !396
  %10 = bitcast %struct.cpio* %9 to i8*, !dbg !396
  %call5 = call i32 @__archive_read_register_format(%struct.archive_read* %8, i8* %10, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i32 (%struct.archive_read*, i32)* @archive_read_format_cpio_bid, i32 (%struct.archive_read*, i8*, i8*)* @archive_read_format_cpio_options, i32 (%struct.archive_read*, %struct.archive_entry*)* @archive_read_format_cpio_read_header, i32 (%struct.archive_read*, i8**, i64*, i64*)* @archive_read_format_cpio_read_data, i32 (%struct.archive_read*)* @archive_read_format_cpio_skip, i64 (%struct.archive_read*, i64, i32)* null, i32 (%struct.archive_read*)* @archive_read_format_cpio_cleanup, i32 (%struct.archive_read*)* null, i32 (%struct.archive_read*)* null), !dbg !397
  store i32 %call5, i32* %r, align 4, !dbg !398
  %11 = load i32, i32* %r, align 4, !dbg !399
  %cmp6 = icmp ne i32 %11, 0, !dbg !401
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !402

if.then7:                                         ; preds = %if.end4
  %12 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !403
  %13 = bitcast %struct.cpio* %12 to i8*, !dbg !403
  call void @free(i8* %13) #6, !dbg !404
  br label %if.end8, !dbg !404

if.end8:                                          ; preds = %if.then7, %if.end4
  store i32 0, i32* %retval, align 4, !dbg !405
  br label %return, !dbg !405

return:                                           ; preds = %if.end8, %if.then3, %if.then
  %14 = load i32, i32* %retval, align 4, !dbg !406
  ret i32 %14, !dbg !406
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare i32 @__archive_read_register_format(%struct.archive_read*, i8*, i8*, i32 (%struct.archive_read*, i32)*, i32 (%struct.archive_read*, i8*, i8*)*, i32 (%struct.archive_read*, %struct.archive_entry*)*, i32 (%struct.archive_read*, i8**, i64*, i64*)*, i32 (%struct.archive_read*)*, i64 (%struct.archive_read*, i64, i32)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*, i32 (%struct.archive_read*)*) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_cpio_bid(%struct.archive_read* %a, i32 %best_bid) #0 !dbg !326 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %best_bid.addr = alloca i32, align 4
  %p = alloca i8*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %bid = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !407, metadata !359), !dbg !408
  store i32 %best_bid, i32* %best_bid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %best_bid.addr, metadata !409, metadata !359), !dbg !410
  call void @llvm.dbg.declare(metadata i8** %p, metadata !411, metadata !359), !dbg !412
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !413, metadata !359), !dbg !414
  call void @llvm.dbg.declare(metadata i32* %bid, metadata !415, metadata !359), !dbg !416
  %0 = load i32, i32* %best_bid.addr, align 4, !dbg !417
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !418
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 13, !dbg !419
  %2 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !419
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %2, i32 0, i32 0, !dbg !420
  %3 = load i8*, i8** %data, align 8, !dbg !420
  %4 = bitcast i8* %3 to %struct.cpio*, !dbg !421
  store %struct.cpio* %4, %struct.cpio** %cpio, align 8, !dbg !422
  %5 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !423
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %5, i64 6, i64* null), !dbg !425
  store i8* %call, i8** %p, align 8, !dbg !426
  %cmp = icmp eq i8* %call, null, !dbg !427
  br i1 %cmp, label %if.then, label %if.end, !dbg !428

if.then:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !429
  br label %return, !dbg !429

if.end:                                           ; preds = %entry
  store i32 0, i32* %bid, align 4, !dbg !430
  %6 = load i8*, i8** %p, align 8, !dbg !431
  %call1 = call i32 @memcmp(i8* %6, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i32 0, i32 0), i64 6) #7, !dbg !433
  %cmp2 = icmp eq i32 %call1, 0, !dbg !434
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !435

if.then3:                                         ; preds = %if.end
  %7 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !436
  %read_header = getelementptr inbounds %struct.cpio, %struct.cpio* %7, i32 0, i32 1, !dbg !438
  store i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)* @header_odc, i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)** %read_header, align 8, !dbg !439
  %8 = load i32, i32* %bid, align 4, !dbg !440
  %add = add nsw i32 %8, 48, !dbg !440
  store i32 %add, i32* %bid, align 4, !dbg !440
  br label %if.end48, !dbg !441

if.else:                                          ; preds = %if.end
  %9 = load i8*, i8** %p, align 8, !dbg !442
  %call4 = call i32 @memcmp(i8* %9, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.4, i32 0, i32 0), i64 6) #7, !dbg !445
  %cmp5 = icmp eq i32 %call4, 0, !dbg !446
  br i1 %cmp5, label %if.then6, label %if.else9, !dbg !445

if.then6:                                         ; preds = %if.else
  %10 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !447
  %read_header7 = getelementptr inbounds %struct.cpio, %struct.cpio* %10, i32 0, i32 1, !dbg !449
  store i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)* @header_odc, i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)** %read_header7, align 8, !dbg !450
  %11 = load i32, i32* %bid, align 4, !dbg !451
  %add8 = add nsw i32 %11, 48, !dbg !451
  store i32 %add8, i32* %bid, align 4, !dbg !451
  br label %if.end47, !dbg !452

if.else9:                                         ; preds = %if.else
  %12 = load i8*, i8** %p, align 8, !dbg !453
  %call10 = call i32 @memcmp(i8* %12, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.5, i32 0, i32 0), i64 6) #7, !dbg !456
  %cmp11 = icmp eq i32 %call10, 0, !dbg !457
  br i1 %cmp11, label %if.then12, label %if.else15, !dbg !456

if.then12:                                        ; preds = %if.else9
  %13 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !458
  %read_header13 = getelementptr inbounds %struct.cpio, %struct.cpio* %13, i32 0, i32 1, !dbg !460
  store i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)* @header_newc, i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)** %read_header13, align 8, !dbg !461
  %14 = load i32, i32* %bid, align 4, !dbg !462
  %add14 = add nsw i32 %14, 48, !dbg !462
  store i32 %add14, i32* %bid, align 4, !dbg !462
  br label %if.end46, !dbg !463

if.else15:                                        ; preds = %if.else9
  %15 = load i8*, i8** %p, align 8, !dbg !464
  %call16 = call i32 @memcmp(i8* %15, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i32 0, i32 0), i64 6) #7, !dbg !467
  %cmp17 = icmp eq i32 %call16, 0, !dbg !468
  br i1 %cmp17, label %if.then18, label %if.else21, !dbg !467

if.then18:                                        ; preds = %if.else15
  %16 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !469
  %read_header19 = getelementptr inbounds %struct.cpio, %struct.cpio* %16, i32 0, i32 1, !dbg !471
  store i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)* @header_newc, i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)** %read_header19, align 8, !dbg !472
  %17 = load i32, i32* %bid, align 4, !dbg !473
  %add20 = add nsw i32 %17, 48, !dbg !473
  store i32 %add20, i32* %bid, align 4, !dbg !473
  br label %if.end45, !dbg !474

if.else21:                                        ; preds = %if.else15
  %18 = load i8*, i8** %p, align 8, !dbg !475
  %arrayidx = getelementptr inbounds i8, i8* %18, i64 0, !dbg !475
  %19 = load i8, i8* %arrayidx, align 1, !dbg !475
  %conv = zext i8 %19 to i32, !dbg !475
  %mul = mul nsw i32 %conv, 256, !dbg !478
  %20 = load i8*, i8** %p, align 8, !dbg !479
  %arrayidx22 = getelementptr inbounds i8, i8* %20, i64 1, !dbg !479
  %21 = load i8, i8* %arrayidx22, align 1, !dbg !479
  %conv23 = zext i8 %21 to i32, !dbg !479
  %add24 = add nsw i32 %mul, %conv23, !dbg !480
  %cmp25 = icmp eq i32 %add24, 29127, !dbg !481
  br i1 %cmp25, label %if.then27, label %if.else30, !dbg !475

if.then27:                                        ; preds = %if.else21
  %22 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !482
  %read_header28 = getelementptr inbounds %struct.cpio, %struct.cpio* %22, i32 0, i32 1, !dbg !484
  store i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)* @header_bin_be, i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)** %read_header28, align 8, !dbg !485
  %23 = load i32, i32* %bid, align 4, !dbg !486
  %add29 = add nsw i32 %23, 16, !dbg !486
  store i32 %add29, i32* %bid, align 4, !dbg !486
  br label %if.end44, !dbg !487

if.else30:                                        ; preds = %if.else21
  %24 = load i8*, i8** %p, align 8, !dbg !488
  %arrayidx31 = getelementptr inbounds i8, i8* %24, i64 0, !dbg !488
  %25 = load i8, i8* %arrayidx31, align 1, !dbg !488
  %conv32 = zext i8 %25 to i32, !dbg !488
  %26 = load i8*, i8** %p, align 8, !dbg !491
  %arrayidx33 = getelementptr inbounds i8, i8* %26, i64 1, !dbg !491
  %27 = load i8, i8* %arrayidx33, align 1, !dbg !491
  %conv34 = zext i8 %27 to i32, !dbg !491
  %mul35 = mul nsw i32 %conv34, 256, !dbg !492
  %add36 = add nsw i32 %conv32, %mul35, !dbg !493
  %cmp37 = icmp eq i32 %add36, 29127, !dbg !494
  br i1 %cmp37, label %if.then39, label %if.else42, !dbg !488

if.then39:                                        ; preds = %if.else30
  %28 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !495
  %read_header40 = getelementptr inbounds %struct.cpio, %struct.cpio* %28, i32 0, i32 1, !dbg !497
  store i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)* @header_bin_le, i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)** %read_header40, align 8, !dbg !498
  %29 = load i32, i32* %bid, align 4, !dbg !499
  %add41 = add nsw i32 %29, 16, !dbg !499
  store i32 %add41, i32* %bid, align 4, !dbg !499
  br label %if.end43, !dbg !500

if.else42:                                        ; preds = %if.else30
  store i32 -20, i32* %retval, align 4, !dbg !501
  br label %return, !dbg !501

if.end43:                                         ; preds = %if.then39
  br label %if.end44

if.end44:                                         ; preds = %if.end43, %if.then27
  br label %if.end45

if.end45:                                         ; preds = %if.end44, %if.then18
  br label %if.end46

if.end46:                                         ; preds = %if.end45, %if.then12
  br label %if.end47

if.end47:                                         ; preds = %if.end46, %if.then6
  br label %if.end48

if.end48:                                         ; preds = %if.end47, %if.then3
  %30 = load i32, i32* %bid, align 4, !dbg !502
  store i32 %30, i32* %retval, align 4, !dbg !503
  br label %return, !dbg !503

return:                                           ; preds = %if.end48, %if.else42, %if.then
  %31 = load i32, i32* %retval, align 4, !dbg !504
  ret i32 %31, !dbg !504
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_cpio_options(%struct.archive_read* %a, i8* %key, i8* %val) #0 !dbg !347 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %key.addr = alloca i8*, align 8
  %val.addr = alloca i8*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %ret = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !505, metadata !359), !dbg !506
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !507, metadata !359), !dbg !508
  store i8* %val, i8** %val.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %val.addr, metadata !509, metadata !359), !dbg !510
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !511, metadata !359), !dbg !512
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !513, metadata !359), !dbg !514
  store i32 -25, i32* %ret, align 4, !dbg !514
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !515
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !516
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !516
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !517
  %2 = load i8*, i8** %data, align 8, !dbg !517
  %3 = bitcast i8* %2 to %struct.cpio*, !dbg !518
  store %struct.cpio* %3, %struct.cpio** %cpio, align 8, !dbg !519
  %4 = load i8*, i8** %key.addr, align 8, !dbg !520
  %call = call i32 @strcmp(i8* %4, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.16, i32 0, i32 0)) #7, !dbg !522
  %cmp = icmp eq i32 %call, 0, !dbg !523
  br i1 %cmp, label %if.then, label %if.else, !dbg !524

if.then:                                          ; preds = %entry
  %5 = load i8*, i8** %val.addr, align 8, !dbg !525
  %cmp1 = icmp ne i8* %5, null, !dbg !527
  %cond = select i1 %cmp1, i32 1, i32 0, !dbg !528
  %6 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !529
  %init_default_conversion = getelementptr inbounds %struct.cpio, %struct.cpio* %6, i32 0, i32 9, !dbg !530
  store i32 %cond, i32* %init_default_conversion, align 8, !dbg !531
  store i32 0, i32* %retval, align 4, !dbg !532
  br label %return, !dbg !532

if.else:                                          ; preds = %entry
  %7 = load i8*, i8** %key.addr, align 8, !dbg !533
  %call2 = call i32 @strcmp(i8* %7, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.17, i32 0, i32 0)) #7, !dbg !535
  %cmp3 = icmp eq i32 %call2, 0, !dbg !536
  br i1 %cmp3, label %if.then4, label %if.end18, !dbg !537

if.then4:                                         ; preds = %if.else
  %8 = load i8*, i8** %val.addr, align 8, !dbg !538
  %cmp5 = icmp eq i8* %8, null, !dbg !541
  br i1 %cmp5, label %if.then8, label %lor.lhs.false, !dbg !542

lor.lhs.false:                                    ; preds = %if.then4
  %9 = load i8*, i8** %val.addr, align 8, !dbg !543
  %arrayidx = getelementptr inbounds i8, i8* %9, i64 0, !dbg !543
  %10 = load i8, i8* %arrayidx, align 1, !dbg !543
  %conv = sext i8 %10 to i32, !dbg !543
  %cmp6 = icmp eq i32 %conv, 0, !dbg !545
  br i1 %cmp6, label %if.then8, label %if.else9, !dbg !546

if.then8:                                         ; preds = %lor.lhs.false, %if.then4
  %11 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !547
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 0, !dbg !548
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 -1, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.18, i32 0, i32 0)), !dbg !549
  br label %if.end17, !dbg !549

if.else9:                                         ; preds = %lor.lhs.false
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !550
  %archive10 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %12, i32 0, i32 0, !dbg !552
  %13 = load i8*, i8** %val.addr, align 8, !dbg !553
  %call11 = call %struct.archive_string_conv* @archive_string_conversion_from_charset(%struct.archive* %archive10, i8* %13, i32 0), !dbg !554
  %14 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !555
  %opt_sconv = getelementptr inbounds %struct.cpio, %struct.cpio* %14, i32 0, i32 7, !dbg !556
  store %struct.archive_string_conv* %call11, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !557
  %15 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !558
  %opt_sconv12 = getelementptr inbounds %struct.cpio, %struct.cpio* %15, i32 0, i32 7, !dbg !560
  %16 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv12, align 8, !dbg !560
  %cmp13 = icmp ne %struct.archive_string_conv* %16, null, !dbg !561
  br i1 %cmp13, label %if.then15, label %if.else16, !dbg !562

if.then15:                                        ; preds = %if.else9
  store i32 0, i32* %ret, align 4, !dbg !563
  br label %if.end, !dbg !564

if.else16:                                        ; preds = %if.else9
  store i32 -30, i32* %ret, align 4, !dbg !565
  br label %if.end

if.end:                                           ; preds = %if.else16, %if.then15
  br label %if.end17

if.end17:                                         ; preds = %if.end, %if.then8
  %17 = load i32, i32* %ret, align 4, !dbg !566
  store i32 %17, i32* %retval, align 4, !dbg !567
  br label %return, !dbg !567

if.end18:                                         ; preds = %if.else
  br label %if.end19

if.end19:                                         ; preds = %if.end18
  store i32 -20, i32* %retval, align 4, !dbg !568
  br label %return, !dbg !568

return:                                           ; preds = %if.end19, %if.end17, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !569
  ret i32 %18, !dbg !569
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_cpio_read_header(%struct.archive_read* %a, %struct.archive_entry* %entry1) #0 !dbg !348 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %h = alloca i8*, align 8
  %hl = alloca i8*, align 8
  %sconv = alloca %struct.archive_string_conv*, align 8
  %namelength = alloca i64, align 8
  %name_pad = alloca i64, align 8
  %r = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !570, metadata !359), !dbg !571
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !572, metadata !359), !dbg !573
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !574, metadata !359), !dbg !575
  call void @llvm.dbg.declare(metadata i8** %h, metadata !576, metadata !359), !dbg !577
  call void @llvm.dbg.declare(metadata i8** %hl, metadata !578, metadata !359), !dbg !579
  call void @llvm.dbg.declare(metadata %struct.archive_string_conv** %sconv, metadata !580, metadata !359), !dbg !581
  call void @llvm.dbg.declare(metadata i64* %namelength, metadata !582, metadata !359), !dbg !583
  call void @llvm.dbg.declare(metadata i64* %name_pad, metadata !584, metadata !359), !dbg !585
  call void @llvm.dbg.declare(metadata i32* %r, metadata !586, metadata !359), !dbg !587
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !588
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !589
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !589
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !590
  %2 = load i8*, i8** %data, align 8, !dbg !590
  %3 = bitcast i8* %2 to %struct.cpio*, !dbg !591
  store %struct.cpio* %3, %struct.cpio** %cpio, align 8, !dbg !592
  %4 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !593
  %opt_sconv = getelementptr inbounds %struct.cpio, %struct.cpio* %4, i32 0, i32 7, !dbg !594
  %5 = load %struct.archive_string_conv*, %struct.archive_string_conv** %opt_sconv, align 8, !dbg !594
  store %struct.archive_string_conv* %5, %struct.archive_string_conv** %sconv, align 8, !dbg !595
  %6 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !596
  %cmp = icmp eq %struct.archive_string_conv* %6, null, !dbg !598
  br i1 %cmp, label %if.then, label %if.end5, !dbg !599

if.then:                                          ; preds = %entry
  %7 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !600
  %init_default_conversion = getelementptr inbounds %struct.cpio, %struct.cpio* %7, i32 0, i32 9, !dbg !603
  %8 = load i32, i32* %init_default_conversion, align 8, !dbg !603
  %tobool = icmp ne i32 %8, 0, !dbg !600
  br i1 %tobool, label %if.end, label %if.then2, !dbg !604

if.then2:                                         ; preds = %if.then
  %9 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !605
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %9, i32 0, i32 0, !dbg !607
  %call = call %struct.archive_string_conv* @archive_string_default_conversion_for_read(%struct.archive* %archive), !dbg !608
  %10 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !609
  %sconv_default = getelementptr inbounds %struct.cpio, %struct.cpio* %10, i32 0, i32 8, !dbg !610
  store %struct.archive_string_conv* %call, %struct.archive_string_conv** %sconv_default, align 8, !dbg !611
  %11 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !612
  %init_default_conversion3 = getelementptr inbounds %struct.cpio, %struct.cpio* %11, i32 0, i32 9, !dbg !613
  store i32 1, i32* %init_default_conversion3, align 8, !dbg !614
  br label %if.end, !dbg !615

if.end:                                           ; preds = %if.then2, %if.then
  %12 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !616
  %sconv_default4 = getelementptr inbounds %struct.cpio, %struct.cpio* %12, i32 0, i32 8, !dbg !617
  %13 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv_default4, align 8, !dbg !617
  store %struct.archive_string_conv* %13, %struct.archive_string_conv** %sconv, align 8, !dbg !618
  br label %if.end5, !dbg !619

if.end5:                                          ; preds = %if.end, %entry
  %14 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !620
  %read_header = getelementptr inbounds %struct.cpio, %struct.cpio* %14, i32 0, i32 1, !dbg !621
  %15 = load i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)*, i32 (%struct.archive_read*, %struct.cpio*, %struct.archive_entry*, i64*, i64*)** %read_header, align 8, !dbg !621
  %16 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !622
  %17 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !623
  %18 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !624
  %call6 = call i32 %15(%struct.archive_read* %16, %struct.cpio* %17, %struct.archive_entry* %18, i64* %namelength, i64* %name_pad), !dbg !620
  store i32 %call6, i32* %r, align 4, !dbg !625
  %19 = load i32, i32* %r, align 4, !dbg !626
  %cmp7 = icmp slt i32 %19, -20, !dbg !628
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !629

if.then8:                                         ; preds = %if.end5
  %20 = load i32, i32* %r, align 4, !dbg !630
  store i32 %20, i32* %retval, align 4, !dbg !631
  br label %return, !dbg !631

if.end9:                                          ; preds = %if.end5
  %21 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !632
  %22 = load i64, i64* %namelength, align 8, !dbg !633
  %23 = load i64, i64* %name_pad, align 8, !dbg !634
  %add = add i64 %22, %23, !dbg !635
  %call10 = call i8* @__archive_read_ahead(%struct.archive_read* %21, i64 %add, i64* null), !dbg !636
  store i8* %call10, i8** %h, align 8, !dbg !637
  %24 = load i8*, i8** %h, align 8, !dbg !638
  %cmp11 = icmp eq i8* %24, null, !dbg !640
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !641

if.then12:                                        ; preds = %if.end9
  store i32 -30, i32* %retval, align 4, !dbg !642
  br label %return, !dbg !642

if.end13:                                         ; preds = %if.end9
  %25 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !643
  %26 = load i8*, i8** %h, align 8, !dbg !645
  %27 = load i64, i64* %namelength, align 8, !dbg !646
  %28 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !647
  %call14 = call i32 @_archive_entry_copy_pathname_l(%struct.archive_entry* %25, i8* %26, i64 %27, %struct.archive_string_conv* %28), !dbg !648
  %cmp15 = icmp ne i32 %call14, 0, !dbg !649
  br i1 %cmp15, label %if.then16, label %if.end24, !dbg !650

if.then16:                                        ; preds = %if.end13
  %call17 = call i32* @__errno_location() #1, !dbg !651
  %29 = load i32, i32* %call17, align 4, !dbg !651
  %cmp18 = icmp eq i32 %29, 12, !dbg !654
  br i1 %cmp18, label %if.then19, label %if.end21, !dbg !655

if.then19:                                        ; preds = %if.then16
  %30 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !656
  %archive20 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %30, i32 0, i32 0, !dbg !658
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive20, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.19, i32 0, i32 0)), !dbg !659
  store i32 -30, i32* %retval, align 4, !dbg !660
  br label %return, !dbg !660

if.end21:                                         ; preds = %if.then16
  %31 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !661
  %archive22 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %31, i32 0, i32 0, !dbg !662
  %32 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !663
  %call23 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %32), !dbg !664
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive22, i32 84, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @.str.20, i32 0, i32 0), i8* %call23), !dbg !665
  store i32 -20, i32* %r, align 4, !dbg !666
  br label %if.end24, !dbg !667

if.end24:                                         ; preds = %if.end21, %if.end13
  %33 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !668
  %entry_offset = getelementptr inbounds %struct.cpio, %struct.cpio* %33, i32 0, i32 5, !dbg !669
  store i64 0, i64* %entry_offset, align 8, !dbg !670
  %34 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !671
  %35 = load i64, i64* %namelength, align 8, !dbg !672
  %36 = load i64, i64* %name_pad, align 8, !dbg !673
  %add25 = add i64 %35, %36, !dbg !674
  %call26 = call i64 @__archive_read_consume(%struct.archive_read* %34, i64 %add25), !dbg !675
  %37 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !676
  %call27 = call i32 @archive_entry_filetype(%struct.archive_entry* %37), !dbg !678
  %cmp28 = icmp eq i32 %call27, 40960, !dbg !679
  br i1 %cmp28, label %if.then29, label %if.end54, !dbg !680

if.then29:                                        ; preds = %if.end24
  %38 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !681
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %38, i32 0, i32 3, !dbg !684
  %39 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !684
  %cmp30 = icmp sgt i64 %39, 1048576, !dbg !685
  br i1 %cmp30, label %if.then31, label %if.end33, !dbg !686

if.then31:                                        ; preds = %if.then29
  %40 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !687
  %archive32 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %40, i32 0, i32 0, !dbg !689
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive32, i32 12, i8* getelementptr inbounds ([69 x i8], [69 x i8]* @.str.21, i32 0, i32 0)), !dbg !690
  store i32 -30, i32* %retval, align 4, !dbg !691
  br label %return, !dbg !691

if.end33:                                         ; preds = %if.then29
  %41 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !692
  %42 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !693
  %entry_bytes_remaining34 = getelementptr inbounds %struct.cpio, %struct.cpio* %42, i32 0, i32 3, !dbg !694
  %43 = load i64, i64* %entry_bytes_remaining34, align 8, !dbg !694
  %call35 = call i8* @__archive_read_ahead(%struct.archive_read* %41, i64 %43, i64* null), !dbg !695
  store i8* %call35, i8** %hl, align 8, !dbg !696
  %44 = load i8*, i8** %hl, align 8, !dbg !697
  %cmp36 = icmp eq i8* %44, null, !dbg !699
  br i1 %cmp36, label %if.then37, label %if.end38, !dbg !700

if.then37:                                        ; preds = %if.end33
  store i32 -30, i32* %retval, align 4, !dbg !701
  br label %return, !dbg !701

if.end38:                                         ; preds = %if.end33
  %45 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !702
  %46 = load i8*, i8** %hl, align 8, !dbg !704
  %47 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !705
  %entry_bytes_remaining39 = getelementptr inbounds %struct.cpio, %struct.cpio* %47, i32 0, i32 3, !dbg !706
  %48 = load i64, i64* %entry_bytes_remaining39, align 8, !dbg !706
  %49 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !707
  %call40 = call i32 @_archive_entry_copy_symlink_l(%struct.archive_entry* %45, i8* %46, i64 %48, %struct.archive_string_conv* %49), !dbg !708
  %cmp41 = icmp ne i32 %call40, 0, !dbg !709
  br i1 %cmp41, label %if.then42, label %if.end50, !dbg !710

if.then42:                                        ; preds = %if.end38
  %call43 = call i32* @__errno_location() #1, !dbg !711
  %50 = load i32, i32* %call43, align 4, !dbg !711
  %cmp44 = icmp eq i32 %50, 12, !dbg !714
  br i1 %cmp44, label %if.then45, label %if.end47, !dbg !715

if.then45:                                        ; preds = %if.then42
  %51 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !716
  %archive46 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %51, i32 0, i32 0, !dbg !718
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive46, i32 12, i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.22, i32 0, i32 0)), !dbg !719
  store i32 -30, i32* %retval, align 4, !dbg !720
  br label %return, !dbg !720

if.end47:                                         ; preds = %if.then42
  %52 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !721
  %archive48 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %52, i32 0, i32 0, !dbg !722
  %53 = load %struct.archive_string_conv*, %struct.archive_string_conv** %sconv, align 8, !dbg !723
  %call49 = call i8* @archive_string_conversion_charset_name(%struct.archive_string_conv* %53), !dbg !724
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive48, i32 84, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @.str.23, i32 0, i32 0), i8* %call49), !dbg !725
  store i32 -20, i32* %r, align 4, !dbg !726
  br label %if.end50, !dbg !727

if.end50:                                         ; preds = %if.end47, %if.end38
  %54 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !728
  %55 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !729
  %entry_bytes_remaining51 = getelementptr inbounds %struct.cpio, %struct.cpio* %55, i32 0, i32 3, !dbg !730
  %56 = load i64, i64* %entry_bytes_remaining51, align 8, !dbg !730
  %call52 = call i64 @__archive_read_consume(%struct.archive_read* %54, i64 %56), !dbg !731
  %57 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !732
  %entry_bytes_remaining53 = getelementptr inbounds %struct.cpio, %struct.cpio* %57, i32 0, i32 3, !dbg !733
  store i64 0, i64* %entry_bytes_remaining53, align 8, !dbg !734
  br label %if.end54, !dbg !735

if.end54:                                         ; preds = %if.end50, %if.end24
  %58 = load i64, i64* %namelength, align 8, !dbg !736
  %cmp55 = icmp eq i64 %58, 11, !dbg !738
  br i1 %cmp55, label %land.lhs.true, label %if.end60, !dbg !739

land.lhs.true:                                    ; preds = %if.end54
  %59 = load i8*, i8** %h, align 8, !dbg !740
  %call56 = call i32 @strncmp(i8* %59, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.24, i32 0, i32 0), i64 11) #7, !dbg !742
  %cmp57 = icmp eq i32 %call56, 0, !dbg !743
  br i1 %cmp57, label %if.then58, label %if.end60, !dbg !744

if.then58:                                        ; preds = %land.lhs.true
  %60 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !745
  %archive59 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %60, i32 0, i32 0, !dbg !747
  call void @archive_clear_error(%struct.archive* %archive59), !dbg !748
  store i32 1, i32* %retval, align 4, !dbg !749
  br label %return, !dbg !749

if.end60:                                         ; preds = %land.lhs.true, %if.end54
  %61 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !750
  %62 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !752
  %63 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !753
  %call61 = call i32 @record_hardlink(%struct.archive_read* %61, %struct.cpio* %62, %struct.archive_entry* %63), !dbg !754
  %cmp62 = icmp ne i32 %call61, 0, !dbg !755
  br i1 %cmp62, label %if.then63, label %if.end64, !dbg !756

if.then63:                                        ; preds = %if.end60
  store i32 -30, i32* %retval, align 4, !dbg !757
  br label %return, !dbg !757

if.end64:                                         ; preds = %if.end60
  %64 = load i32, i32* %r, align 4, !dbg !759
  store i32 %64, i32* %retval, align 4, !dbg !760
  br label %return, !dbg !760

return:                                           ; preds = %if.end64, %if.then63, %if.then58, %if.then45, %if.then37, %if.then31, %if.then19, %if.then12, %if.then8
  %65 = load i32, i32* %retval, align 4, !dbg !761
  ret i32 %65, !dbg !761
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_cpio_read_data(%struct.archive_read* %a, i8** %buff, i64* %size, i64* %offset) #0 !dbg !352 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %buff.addr = alloca i8**, align 8
  %size.addr = alloca i64*, align 8
  %offset.addr = alloca i64*, align 8
  %bytes_read = alloca i64, align 8
  %cpio = alloca %struct.cpio*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !762, metadata !359), !dbg !763
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !764, metadata !359), !dbg !765
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !766, metadata !359), !dbg !767
  store i64* %offset, i64** %offset.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %offset.addr, metadata !768, metadata !359), !dbg !769
  call void @llvm.dbg.declare(metadata i64* %bytes_read, metadata !770, metadata !359), !dbg !771
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !772, metadata !359), !dbg !773
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !774
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !775
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !775
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !776
  %2 = load i8*, i8** %data, align 8, !dbg !776
  %3 = bitcast i8* %2 to %struct.cpio*, !dbg !777
  store %struct.cpio* %3, %struct.cpio** %cpio, align 8, !dbg !778
  %4 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !779
  %entry_bytes_unconsumed = getelementptr inbounds %struct.cpio, %struct.cpio* %4, i32 0, i32 4, !dbg !781
  %5 = load i64, i64* %entry_bytes_unconsumed, align 8, !dbg !781
  %tobool = icmp ne i64 %5, 0, !dbg !779
  br i1 %tobool, label %if.then, label %if.end, !dbg !782

if.then:                                          ; preds = %entry
  %6 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !783
  %7 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !785
  %entry_bytes_unconsumed1 = getelementptr inbounds %struct.cpio, %struct.cpio* %7, i32 0, i32 4, !dbg !786
  %8 = load i64, i64* %entry_bytes_unconsumed1, align 8, !dbg !786
  %call = call i64 @__archive_read_consume(%struct.archive_read* %6, i64 %8), !dbg !787
  %9 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !788
  %entry_bytes_unconsumed2 = getelementptr inbounds %struct.cpio, %struct.cpio* %9, i32 0, i32 4, !dbg !789
  store i64 0, i64* %entry_bytes_unconsumed2, align 8, !dbg !790
  br label %if.end, !dbg !791

if.end:                                           ; preds = %if.then, %entry
  %10 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !792
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %10, i32 0, i32 3, !dbg !794
  %11 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !794
  %cmp = icmp sgt i64 %11, 0, !dbg !795
  br i1 %cmp, label %if.then3, label %if.else, !dbg !796

if.then3:                                         ; preds = %if.end
  %12 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !797
  %call4 = call i8* @__archive_read_ahead(%struct.archive_read* %12, i64 1, i64* %bytes_read), !dbg !799
  %13 = load i8**, i8*** %buff.addr, align 8, !dbg !800
  store i8* %call4, i8** %13, align 8, !dbg !801
  %14 = load i64, i64* %bytes_read, align 8, !dbg !802
  %cmp5 = icmp sle i64 %14, 0, !dbg !804
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !805

if.then6:                                         ; preds = %if.then3
  store i32 -30, i32* %retval, align 4, !dbg !806
  br label %return, !dbg !806

if.end7:                                          ; preds = %if.then3
  %15 = load i64, i64* %bytes_read, align 8, !dbg !807
  %16 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !809
  %entry_bytes_remaining8 = getelementptr inbounds %struct.cpio, %struct.cpio* %16, i32 0, i32 3, !dbg !810
  %17 = load i64, i64* %entry_bytes_remaining8, align 8, !dbg !810
  %cmp9 = icmp sgt i64 %15, %17, !dbg !811
  br i1 %cmp9, label %if.then10, label %if.end12, !dbg !812

if.then10:                                        ; preds = %if.end7
  %18 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !813
  %entry_bytes_remaining11 = getelementptr inbounds %struct.cpio, %struct.cpio* %18, i32 0, i32 3, !dbg !814
  %19 = load i64, i64* %entry_bytes_remaining11, align 8, !dbg !814
  store i64 %19, i64* %bytes_read, align 8, !dbg !815
  br label %if.end12, !dbg !816

if.end12:                                         ; preds = %if.then10, %if.end7
  %20 = load i64, i64* %bytes_read, align 8, !dbg !817
  %21 = load i64*, i64** %size.addr, align 8, !dbg !818
  store i64 %20, i64* %21, align 8, !dbg !819
  %22 = load i64, i64* %bytes_read, align 8, !dbg !820
  %23 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !821
  %entry_bytes_unconsumed13 = getelementptr inbounds %struct.cpio, %struct.cpio* %23, i32 0, i32 4, !dbg !822
  store i64 %22, i64* %entry_bytes_unconsumed13, align 8, !dbg !823
  %24 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !824
  %entry_offset = getelementptr inbounds %struct.cpio, %struct.cpio* %24, i32 0, i32 5, !dbg !825
  %25 = load i64, i64* %entry_offset, align 8, !dbg !825
  %26 = load i64*, i64** %offset.addr, align 8, !dbg !826
  store i64 %25, i64* %26, align 8, !dbg !827
  %27 = load i64, i64* %bytes_read, align 8, !dbg !828
  %28 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !829
  %entry_offset14 = getelementptr inbounds %struct.cpio, %struct.cpio* %28, i32 0, i32 5, !dbg !830
  %29 = load i64, i64* %entry_offset14, align 8, !dbg !831
  %add = add nsw i64 %29, %27, !dbg !831
  store i64 %add, i64* %entry_offset14, align 8, !dbg !831
  %30 = load i64, i64* %bytes_read, align 8, !dbg !832
  %31 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !833
  %entry_bytes_remaining15 = getelementptr inbounds %struct.cpio, %struct.cpio* %31, i32 0, i32 3, !dbg !834
  %32 = load i64, i64* %entry_bytes_remaining15, align 8, !dbg !835
  %sub = sub nsw i64 %32, %30, !dbg !835
  store i64 %sub, i64* %entry_bytes_remaining15, align 8, !dbg !835
  store i32 0, i32* %retval, align 4, !dbg !836
  br label %return, !dbg !836

if.else:                                          ; preds = %if.end
  %33 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !837
  %entry_padding = getelementptr inbounds %struct.cpio, %struct.cpio* %33, i32 0, i32 6, !dbg !840
  %34 = load i64, i64* %entry_padding, align 8, !dbg !840
  %35 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !841
  %36 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !842
  %entry_padding16 = getelementptr inbounds %struct.cpio, %struct.cpio* %36, i32 0, i32 6, !dbg !843
  %37 = load i64, i64* %entry_padding16, align 8, !dbg !843
  %call17 = call i64 @__archive_read_consume(%struct.archive_read* %35, i64 %37), !dbg !844
  %cmp18 = icmp ne i64 %34, %call17, !dbg !845
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !846

if.then19:                                        ; preds = %if.else
  store i32 -30, i32* %retval, align 4, !dbg !847
  br label %return, !dbg !847

if.end20:                                         ; preds = %if.else
  %38 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !849
  %entry_padding21 = getelementptr inbounds %struct.cpio, %struct.cpio* %38, i32 0, i32 6, !dbg !850
  store i64 0, i64* %entry_padding21, align 8, !dbg !851
  %39 = load i8**, i8*** %buff.addr, align 8, !dbg !852
  store i8* null, i8** %39, align 8, !dbg !853
  %40 = load i64*, i64** %size.addr, align 8, !dbg !854
  store i64 0, i64* %40, align 8, !dbg !855
  %41 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !856
  %entry_offset22 = getelementptr inbounds %struct.cpio, %struct.cpio* %41, i32 0, i32 5, !dbg !857
  %42 = load i64, i64* %entry_offset22, align 8, !dbg !857
  %43 = load i64*, i64** %offset.addr, align 8, !dbg !858
  store i64 %42, i64* %43, align 8, !dbg !859
  store i32 1, i32* %retval, align 4, !dbg !860
  br label %return, !dbg !860

return:                                           ; preds = %if.end20, %if.then19, %if.end12, %if.then6
  %44 = load i32, i32* %retval, align 4, !dbg !861
  ret i32 %44, !dbg !861
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_cpio_skip(%struct.archive_read* %a) #0 !dbg !353 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %to_skip = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !862, metadata !359), !dbg !863
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !864, metadata !359), !dbg !865
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !866
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !867
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !867
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !868
  %2 = load i8*, i8** %data, align 8, !dbg !868
  %3 = bitcast i8* %2 to %struct.cpio*, !dbg !869
  store %struct.cpio* %3, %struct.cpio** %cpio, align 8, !dbg !865
  call void @llvm.dbg.declare(metadata i64* %to_skip, metadata !870, metadata !359), !dbg !871
  %4 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !872
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %4, i32 0, i32 3, !dbg !873
  %5 = load i64, i64* %entry_bytes_remaining, align 8, !dbg !873
  %6 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !874
  %entry_padding = getelementptr inbounds %struct.cpio, %struct.cpio* %6, i32 0, i32 6, !dbg !875
  %7 = load i64, i64* %entry_padding, align 8, !dbg !875
  %add = add nsw i64 %5, %7, !dbg !876
  %8 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !877
  %entry_bytes_unconsumed = getelementptr inbounds %struct.cpio, %struct.cpio* %8, i32 0, i32 4, !dbg !878
  %9 = load i64, i64* %entry_bytes_unconsumed, align 8, !dbg !878
  %add1 = add nsw i64 %add, %9, !dbg !879
  store i64 %add1, i64* %to_skip, align 8, !dbg !871
  %10 = load i64, i64* %to_skip, align 8, !dbg !880
  %11 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !882
  %12 = load i64, i64* %to_skip, align 8, !dbg !883
  %call = call i64 @__archive_read_consume(%struct.archive_read* %11, i64 %12), !dbg !884
  %cmp = icmp ne i64 %10, %call, !dbg !885
  br i1 %cmp, label %if.then, label %if.end, !dbg !886

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !887
  br label %return, !dbg !887

if.end:                                           ; preds = %entry
  %13 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !889
  %entry_bytes_remaining2 = getelementptr inbounds %struct.cpio, %struct.cpio* %13, i32 0, i32 3, !dbg !890
  store i64 0, i64* %entry_bytes_remaining2, align 8, !dbg !891
  %14 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !892
  %entry_padding3 = getelementptr inbounds %struct.cpio, %struct.cpio* %14, i32 0, i32 6, !dbg !893
  store i64 0, i64* %entry_padding3, align 8, !dbg !894
  %15 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !895
  %entry_bytes_unconsumed4 = getelementptr inbounds %struct.cpio, %struct.cpio* %15, i32 0, i32 4, !dbg !896
  store i64 0, i64* %entry_bytes_unconsumed4, align 8, !dbg !897
  store i32 0, i32* %retval, align 4, !dbg !898
  br label %return, !dbg !898

return:                                           ; preds = %if.end, %if.then
  %16 = load i32, i32* %retval, align 4, !dbg !899
  ret i32 %16, !dbg !899
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_read_format_cpio_cleanup(%struct.archive_read* %a) #0 !dbg !354 {
entry:
  %a.addr = alloca %struct.archive_read*, align 8
  %cpio = alloca %struct.cpio*, align 8
  %lp = alloca %struct.links_entry*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !900, metadata !359), !dbg !901
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio, metadata !902, metadata !359), !dbg !903
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !904
  %format = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 13, !dbg !905
  %1 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format, align 8, !dbg !905
  %data = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %1, i32 0, i32 0, !dbg !906
  %2 = load i8*, i8** %data, align 8, !dbg !906
  %3 = bitcast i8* %2 to %struct.cpio*, !dbg !907
  store %struct.cpio* %3, %struct.cpio** %cpio, align 8, !dbg !908
  br label %while.cond, !dbg !909

while.cond:                                       ; preds = %if.end, %entry
  %4 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !910
  %links_head = getelementptr inbounds %struct.cpio, %struct.cpio* %4, i32 0, i32 2, !dbg !912
  %5 = load %struct.links_entry*, %struct.links_entry** %links_head, align 8, !dbg !912
  %cmp = icmp ne %struct.links_entry* %5, null, !dbg !913
  br i1 %cmp, label %while.body, label %while.end, !dbg !914

while.body:                                       ; preds = %while.cond
  call void @llvm.dbg.declare(metadata %struct.links_entry** %lp, metadata !915, metadata !359), !dbg !917
  %6 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !918
  %links_head1 = getelementptr inbounds %struct.cpio, %struct.cpio* %6, i32 0, i32 2, !dbg !919
  %7 = load %struct.links_entry*, %struct.links_entry** %links_head1, align 8, !dbg !919
  %next = getelementptr inbounds %struct.links_entry, %struct.links_entry* %7, i32 0, i32 0, !dbg !920
  %8 = load %struct.links_entry*, %struct.links_entry** %next, align 8, !dbg !920
  store %struct.links_entry* %8, %struct.links_entry** %lp, align 8, !dbg !917
  %9 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !921
  %links_head2 = getelementptr inbounds %struct.cpio, %struct.cpio* %9, i32 0, i32 2, !dbg !923
  %10 = load %struct.links_entry*, %struct.links_entry** %links_head2, align 8, !dbg !923
  %name = getelementptr inbounds %struct.links_entry, %struct.links_entry* %10, i32 0, i32 5, !dbg !924
  %11 = load i8*, i8** %name, align 8, !dbg !924
  %tobool = icmp ne i8* %11, null, !dbg !921
  br i1 %tobool, label %if.then, label %if.end, !dbg !925

if.then:                                          ; preds = %while.body
  %12 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !926
  %links_head3 = getelementptr inbounds %struct.cpio, %struct.cpio* %12, i32 0, i32 2, !dbg !927
  %13 = load %struct.links_entry*, %struct.links_entry** %links_head3, align 8, !dbg !927
  %name4 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %13, i32 0, i32 5, !dbg !928
  %14 = load i8*, i8** %name4, align 8, !dbg !928
  call void @free(i8* %14) #6, !dbg !929
  br label %if.end, !dbg !929

if.end:                                           ; preds = %if.then, %while.body
  %15 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !930
  %links_head5 = getelementptr inbounds %struct.cpio, %struct.cpio* %15, i32 0, i32 2, !dbg !931
  %16 = load %struct.links_entry*, %struct.links_entry** %links_head5, align 8, !dbg !931
  %17 = bitcast %struct.links_entry* %16 to i8*, !dbg !930
  call void @free(i8* %17) #6, !dbg !932
  %18 = load %struct.links_entry*, %struct.links_entry** %lp, align 8, !dbg !933
  %19 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !934
  %links_head6 = getelementptr inbounds %struct.cpio, %struct.cpio* %19, i32 0, i32 2, !dbg !935
  store %struct.links_entry* %18, %struct.links_entry** %links_head6, align 8, !dbg !936
  br label %while.cond, !dbg !937

while.end:                                        ; preds = %while.cond
  %20 = load %struct.cpio*, %struct.cpio** %cpio, align 8, !dbg !939
  %21 = bitcast %struct.cpio* %20 to i8*, !dbg !939
  call void @free(i8* %21) #6, !dbg !940
  %22 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !941
  %format7 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %22, i32 0, i32 13, !dbg !942
  %23 = load %struct.archive_format_descriptor*, %struct.archive_format_descriptor** %format7, align 8, !dbg !942
  %data8 = getelementptr inbounds %struct.archive_format_descriptor, %struct.archive_format_descriptor* %23, i32 0, i32 0, !dbg !943
  store i8* null, i8** %data8, align 8, !dbg !944
  ret i32 0, !dbg !945
}

; Function Attrs: nounwind
declare void @free(i8*) #3

declare i8* @__archive_read_ahead(%struct.archive_read*, i64, i64*) #2

; Function Attrs: nounwind readonly
declare i32 @memcmp(i8*, i8*, i64) #4

; Function Attrs: nounwind uwtable
define internal i32 @header_odc(%struct.archive_read* %a, %struct.cpio* %cpio, %struct.archive_entry* %entry1, i64* %namelength, i64* %name_pad) #0 !dbg !327 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %cpio.addr = alloca %struct.cpio*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %namelength.addr = alloca i64*, align 8
  %name_pad.addr = alloca i64*, align 8
  %h = alloca i8*, align 8
  %r = alloca i32, align 4
  %header = alloca i8*, align 8
  %r2 = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !946, metadata !359), !dbg !947
  store %struct.cpio* %cpio, %struct.cpio** %cpio.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio.addr, metadata !948, metadata !359), !dbg !949
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !950, metadata !359), !dbg !951
  store i64* %namelength, i64** %namelength.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %namelength.addr, metadata !952, metadata !359), !dbg !953
  store i64* %name_pad, i64** %name_pad.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %name_pad.addr, metadata !954, metadata !359), !dbg !955
  call void @llvm.dbg.declare(metadata i8** %h, metadata !956, metadata !359), !dbg !957
  call void @llvm.dbg.declare(metadata i32* %r, metadata !958, metadata !359), !dbg !959
  call void @llvm.dbg.declare(metadata i8** %header, metadata !960, metadata !359), !dbg !961
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !962
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 0, !dbg !963
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !964
  store i32 65537, i32* %archive_format, align 8, !dbg !965
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !966
  %archive2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 0, !dbg !967
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive2, i32 0, i32 4, !dbg !968
  store i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.7, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !969
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !970
  %call = call i32 @find_odc_header(%struct.archive_read* %2), !dbg !971
  store i32 %call, i32* %r, align 4, !dbg !972
  %3 = load i32, i32* %r, align 4, !dbg !973
  %cmp = icmp slt i32 %3, -20, !dbg !975
  br i1 %cmp, label %if.then, label %if.end, !dbg !976

if.then:                                          ; preds = %entry
  %4 = load i32, i32* %r, align 4, !dbg !977
  store i32 %4, i32* %retval, align 4, !dbg !978
  br label %return, !dbg !978

if.end:                                           ; preds = %entry
  %5 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !979
  %archive3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %5, i32 0, i32 0, !dbg !981
  %archive_format4 = getelementptr inbounds %struct.archive, %struct.archive* %archive3, i32 0, i32 3, !dbg !982
  %6 = load i32, i32* %archive_format4, align 8, !dbg !982
  %cmp5 = icmp eq i32 %6, 65542, !dbg !983
  br i1 %cmp5, label %if.then6, label %if.end10, !dbg !984

if.then6:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %r2, metadata !985, metadata !359), !dbg !987
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !988
  %8 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !989
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !990
  %10 = load i64*, i64** %namelength.addr, align 8, !dbg !991
  %11 = load i64*, i64** %name_pad.addr, align 8, !dbg !992
  %call7 = call i32 @header_afiol(%struct.archive_read* %7, %struct.cpio* %8, %struct.archive_entry* %9, i64* %10, i64* %11), !dbg !993
  store i32 %call7, i32* %r2, align 4, !dbg !987
  %12 = load i32, i32* %r2, align 4, !dbg !994
  %cmp8 = icmp eq i32 %12, 0, !dbg !996
  br i1 %cmp8, label %if.then9, label %if.else, !dbg !997

if.then9:                                         ; preds = %if.then6
  %13 = load i32, i32* %r, align 4, !dbg !998
  store i32 %13, i32* %retval, align 4, !dbg !999
  br label %return, !dbg !999

if.else:                                          ; preds = %if.then6
  %14 = load i32, i32* %r2, align 4, !dbg !1000
  store i32 %14, i32* %retval, align 4, !dbg !1001
  br label %return, !dbg !1001

if.end10:                                         ; preds = %if.end
  %15 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1002
  %call11 = call i8* @__archive_read_ahead(%struct.archive_read* %15, i64 76, i64* null), !dbg !1003
  store i8* %call11, i8** %h, align 8, !dbg !1004
  %16 = load i8*, i8** %h, align 8, !dbg !1005
  %cmp12 = icmp eq i8* %16, null, !dbg !1007
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !1008

if.then13:                                        ; preds = %if.end10
  store i32 -30, i32* %retval, align 4, !dbg !1009
  br label %return, !dbg !1009

if.end14:                                         ; preds = %if.end10
  %17 = load i8*, i8** %h, align 8, !dbg !1010
  store i8* %17, i8** %header, align 8, !dbg !1011
  %18 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1012
  %19 = load i8*, i8** %header, align 8, !dbg !1013
  %add.ptr = getelementptr inbounds i8, i8* %19, i64 6, !dbg !1014
  %call15 = call i64 @atol8(i8* %add.ptr, i32 6), !dbg !1015
  call void @archive_entry_set_dev(%struct.archive_entry* %18, i64 %call15), !dbg !1016
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1017
  %21 = load i8*, i8** %header, align 8, !dbg !1018
  %add.ptr16 = getelementptr inbounds i8, i8* %21, i64 12, !dbg !1019
  %call17 = call i64 @atol8(i8* %add.ptr16, i32 6), !dbg !1020
  call void @archive_entry_set_ino(%struct.archive_entry* %20, i64 %call17), !dbg !1021
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1023
  %23 = load i8*, i8** %header, align 8, !dbg !1024
  %add.ptr18 = getelementptr inbounds i8, i8* %23, i64 18, !dbg !1025
  %call19 = call i64 @atol8(i8* %add.ptr18, i32 6), !dbg !1026
  %conv = trunc i64 %call19 to i32, !dbg !1027
  call void @archive_entry_set_mode(%struct.archive_entry* %22, i32 %conv), !dbg !1028
  %24 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1029
  %25 = load i8*, i8** %header, align 8, !dbg !1030
  %add.ptr20 = getelementptr inbounds i8, i8* %25, i64 24, !dbg !1031
  %call21 = call i64 @atol8(i8* %add.ptr20, i32 6), !dbg !1032
  call void @archive_entry_set_uid(%struct.archive_entry* %24, i64 %call21), !dbg !1033
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1034
  %27 = load i8*, i8** %header, align 8, !dbg !1035
  %add.ptr22 = getelementptr inbounds i8, i8* %27, i64 30, !dbg !1036
  %call23 = call i64 @atol8(i8* %add.ptr22, i32 6), !dbg !1037
  call void @archive_entry_set_gid(%struct.archive_entry* %26, i64 %call23), !dbg !1038
  %28 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1039
  %29 = load i8*, i8** %header, align 8, !dbg !1040
  %add.ptr24 = getelementptr inbounds i8, i8* %29, i64 36, !dbg !1041
  %call25 = call i64 @atol8(i8* %add.ptr24, i32 6), !dbg !1042
  %conv26 = trunc i64 %call25 to i32, !dbg !1043
  call void @archive_entry_set_nlink(%struct.archive_entry* %28, i32 %conv26), !dbg !1044
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1045
  %31 = load i8*, i8** %header, align 8, !dbg !1046
  %add.ptr27 = getelementptr inbounds i8, i8* %31, i64 42, !dbg !1047
  %call28 = call i64 @atol8(i8* %add.ptr27, i32 6), !dbg !1048
  call void @archive_entry_set_rdev(%struct.archive_entry* %30, i64 %call28), !dbg !1049
  %32 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1050
  %33 = load i8*, i8** %header, align 8, !dbg !1051
  %add.ptr29 = getelementptr inbounds i8, i8* %33, i64 48, !dbg !1052
  %call30 = call i64 @atol8(i8* %add.ptr29, i32 11), !dbg !1053
  call void @archive_entry_set_mtime(%struct.archive_entry* %32, i64 %call30, i64 0), !dbg !1054
  %34 = load i8*, i8** %header, align 8, !dbg !1055
  %add.ptr31 = getelementptr inbounds i8, i8* %34, i64 59, !dbg !1056
  %call32 = call i64 @atol8(i8* %add.ptr31, i32 6), !dbg !1057
  %35 = load i64*, i64** %namelength.addr, align 8, !dbg !1058
  store i64 %call32, i64* %35, align 8, !dbg !1059
  %36 = load i64*, i64** %name_pad.addr, align 8, !dbg !1060
  store i64 0, i64* %36, align 8, !dbg !1061
  %37 = load i8*, i8** %header, align 8, !dbg !1062
  %add.ptr33 = getelementptr inbounds i8, i8* %37, i64 65, !dbg !1063
  %call34 = call i64 @atol8(i8* %add.ptr33, i32 11), !dbg !1064
  %38 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1065
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %38, i32 0, i32 3, !dbg !1066
  store i64 %call34, i64* %entry_bytes_remaining, align 8, !dbg !1067
  %39 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1068
  %40 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1069
  %entry_bytes_remaining35 = getelementptr inbounds %struct.cpio, %struct.cpio* %40, i32 0, i32 3, !dbg !1070
  %41 = load i64, i64* %entry_bytes_remaining35, align 8, !dbg !1070
  call void @archive_entry_set_size(%struct.archive_entry* %39, i64 %41), !dbg !1071
  %42 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1072
  %entry_padding = getelementptr inbounds %struct.cpio, %struct.cpio* %42, i32 0, i32 6, !dbg !1073
  store i64 0, i64* %entry_padding, align 8, !dbg !1074
  %43 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1075
  %call36 = call i64 @__archive_read_consume(%struct.archive_read* %43, i64 76), !dbg !1076
  %44 = load i32, i32* %r, align 4, !dbg !1077
  store i32 %44, i32* %retval, align 4, !dbg !1078
  br label %return, !dbg !1078

return:                                           ; preds = %if.end14, %if.then13, %if.else, %if.then9, %if.then
  %45 = load i32, i32* %retval, align 4, !dbg !1079
  ret i32 %45, !dbg !1079
}

; Function Attrs: nounwind uwtable
define internal i32 @header_newc(%struct.archive_read* %a, %struct.cpio* %cpio, %struct.archive_entry* %entry1, i64* %namelength, i64* %name_pad) #0 !dbg !339 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %cpio.addr = alloca %struct.cpio*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %namelength.addr = alloca i64*, align 8
  %name_pad.addr = alloca i64*, align 8
  %h = alloca i8*, align 8
  %header = alloca i8*, align 8
  %r = alloca i32, align 4
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1080, metadata !359), !dbg !1081
  store %struct.cpio* %cpio, %struct.cpio** %cpio.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio.addr, metadata !1082, metadata !359), !dbg !1083
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1084, metadata !359), !dbg !1085
  store i64* %namelength, i64** %namelength.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %namelength.addr, metadata !1086, metadata !359), !dbg !1087
  store i64* %name_pad, i64** %name_pad.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %name_pad.addr, metadata !1088, metadata !359), !dbg !1089
  call void @llvm.dbg.declare(metadata i8** %h, metadata !1090, metadata !359), !dbg !1091
  call void @llvm.dbg.declare(metadata i8** %header, metadata !1092, metadata !359), !dbg !1093
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1094, metadata !359), !dbg !1095
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1096
  %call = call i32 @find_newc_header(%struct.archive_read* %0), !dbg !1097
  store i32 %call, i32* %r, align 4, !dbg !1098
  %1 = load i32, i32* %r, align 4, !dbg !1099
  %cmp = icmp slt i32 %1, -20, !dbg !1101
  br i1 %cmp, label %if.then, label %if.end, !dbg !1102

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %r, align 4, !dbg !1103
  store i32 %2, i32* %retval, align 4, !dbg !1104
  br label %return, !dbg !1104

if.end:                                           ; preds = %entry
  %3 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1105
  %call2 = call i8* @__archive_read_ahead(%struct.archive_read* %3, i64 110, i64* null), !dbg !1106
  store i8* %call2, i8** %h, align 8, !dbg !1107
  %4 = load i8*, i8** %h, align 8, !dbg !1108
  %cmp3 = icmp eq i8* %4, null, !dbg !1110
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1111

if.then4:                                         ; preds = %if.end
  store i32 -30, i32* %retval, align 4, !dbg !1112
  br label %return, !dbg !1112

if.end5:                                          ; preds = %if.end
  %5 = load i8*, i8** %h, align 8, !dbg !1113
  store i8* %5, i8** %header, align 8, !dbg !1114
  %6 = load i8*, i8** %header, align 8, !dbg !1115
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 0, !dbg !1117
  %call6 = call i32 @memcmp(i8* %add.ptr, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.5, i32 0, i32 0), i64 6) #7, !dbg !1118
  %cmp7 = icmp eq i32 %call6, 0, !dbg !1119
  br i1 %cmp7, label %if.then8, label %if.else, !dbg !1120

if.then8:                                         ; preds = %if.end5
  %7 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1121
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %7, i32 0, i32 0, !dbg !1123
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !1124
  store i32 65540, i32* %archive_format, align 8, !dbg !1125
  %8 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1126
  %archive9 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %8, i32 0, i32 0, !dbg !1127
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive9, i32 0, i32 4, !dbg !1128
  store i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.10, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !1129
  br label %if.end20, !dbg !1130

if.else:                                          ; preds = %if.end5
  %9 = load i8*, i8** %header, align 8, !dbg !1131
  %add.ptr10 = getelementptr inbounds i8, i8* %9, i64 0, !dbg !1134
  %call11 = call i32 @memcmp(i8* %add.ptr10, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.6, i32 0, i32 0), i64 6) #7, !dbg !1135
  %cmp12 = icmp eq i32 %call11, 0, !dbg !1136
  br i1 %cmp12, label %if.then13, label %if.else18, !dbg !1135

if.then13:                                        ; preds = %if.else
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1137
  %archive14 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 0, !dbg !1139
  %archive_format15 = getelementptr inbounds %struct.archive, %struct.archive* %archive14, i32 0, i32 3, !dbg !1140
  store i32 65541, i32* %archive_format15, align 8, !dbg !1141
  %11 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1142
  %archive16 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %11, i32 0, i32 0, !dbg !1143
  %archive_format_name17 = getelementptr inbounds %struct.archive, %struct.archive* %archive16, i32 0, i32 4, !dbg !1144
  store i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.11, i32 0, i32 0), i8** %archive_format_name17, align 8, !dbg !1145
  br label %if.end19, !dbg !1146

if.else18:                                        ; preds = %if.else
  br label %if.end19

if.end19:                                         ; preds = %if.else18, %if.then13
  br label %if.end20

if.end20:                                         ; preds = %if.end19, %if.then8
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1147
  %13 = load i8*, i8** %header, align 8, !dbg !1148
  %add.ptr21 = getelementptr inbounds i8, i8* %13, i64 62, !dbg !1149
  %call22 = call i64 @atol16(i8* %add.ptr21, i32 8), !dbg !1150
  call void @archive_entry_set_devmajor(%struct.archive_entry* %12, i64 %call22), !dbg !1151
  %14 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1152
  %15 = load i8*, i8** %header, align 8, !dbg !1153
  %add.ptr23 = getelementptr inbounds i8, i8* %15, i64 70, !dbg !1154
  %call24 = call i64 @atol16(i8* %add.ptr23, i32 8), !dbg !1155
  call void @archive_entry_set_devminor(%struct.archive_entry* %14, i64 %call24), !dbg !1156
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1157
  %17 = load i8*, i8** %header, align 8, !dbg !1158
  %add.ptr25 = getelementptr inbounds i8, i8* %17, i64 6, !dbg !1159
  %call26 = call i64 @atol16(i8* %add.ptr25, i32 8), !dbg !1160
  call void @archive_entry_set_ino(%struct.archive_entry* %16, i64 %call26), !dbg !1161
  %18 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1163
  %19 = load i8*, i8** %header, align 8, !dbg !1164
  %add.ptr27 = getelementptr inbounds i8, i8* %19, i64 14, !dbg !1165
  %call28 = call i64 @atol16(i8* %add.ptr27, i32 8), !dbg !1166
  %conv = trunc i64 %call28 to i32, !dbg !1167
  call void @archive_entry_set_mode(%struct.archive_entry* %18, i32 %conv), !dbg !1168
  %20 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1169
  %21 = load i8*, i8** %header, align 8, !dbg !1170
  %add.ptr29 = getelementptr inbounds i8, i8* %21, i64 22, !dbg !1171
  %call30 = call i64 @atol16(i8* %add.ptr29, i32 8), !dbg !1172
  call void @archive_entry_set_uid(%struct.archive_entry* %20, i64 %call30), !dbg !1173
  %22 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1174
  %23 = load i8*, i8** %header, align 8, !dbg !1175
  %add.ptr31 = getelementptr inbounds i8, i8* %23, i64 30, !dbg !1176
  %call32 = call i64 @atol16(i8* %add.ptr31, i32 8), !dbg !1177
  call void @archive_entry_set_gid(%struct.archive_entry* %22, i64 %call32), !dbg !1178
  %24 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1179
  %25 = load i8*, i8** %header, align 8, !dbg !1180
  %add.ptr33 = getelementptr inbounds i8, i8* %25, i64 38, !dbg !1181
  %call34 = call i64 @atol16(i8* %add.ptr33, i32 8), !dbg !1182
  %conv35 = trunc i64 %call34 to i32, !dbg !1183
  call void @archive_entry_set_nlink(%struct.archive_entry* %24, i32 %conv35), !dbg !1184
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1185
  %27 = load i8*, i8** %header, align 8, !dbg !1186
  %add.ptr36 = getelementptr inbounds i8, i8* %27, i64 78, !dbg !1187
  %call37 = call i64 @atol16(i8* %add.ptr36, i32 8), !dbg !1188
  call void @archive_entry_set_rdevmajor(%struct.archive_entry* %26, i64 %call37), !dbg !1189
  %28 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1190
  %29 = load i8*, i8** %header, align 8, !dbg !1191
  %add.ptr38 = getelementptr inbounds i8, i8* %29, i64 86, !dbg !1192
  %call39 = call i64 @atol16(i8* %add.ptr38, i32 8), !dbg !1193
  call void @archive_entry_set_rdevminor(%struct.archive_entry* %28, i64 %call39), !dbg !1194
  %30 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1195
  %31 = load i8*, i8** %header, align 8, !dbg !1196
  %add.ptr40 = getelementptr inbounds i8, i8* %31, i64 46, !dbg !1197
  %call41 = call i64 @atol16(i8* %add.ptr40, i32 8), !dbg !1198
  call void @archive_entry_set_mtime(%struct.archive_entry* %30, i64 %call41, i64 0), !dbg !1199
  %32 = load i8*, i8** %header, align 8, !dbg !1200
  %add.ptr42 = getelementptr inbounds i8, i8* %32, i64 94, !dbg !1201
  %call43 = call i64 @atol16(i8* %add.ptr42, i32 8), !dbg !1202
  %33 = load i64*, i64** %namelength.addr, align 8, !dbg !1203
  store i64 %call43, i64* %33, align 8, !dbg !1204
  %34 = load i64*, i64** %namelength.addr, align 8, !dbg !1205
  %35 = load i64, i64* %34, align 8, !dbg !1206
  %sub = sub i64 2, %35, !dbg !1207
  %and = and i64 %sub, 3, !dbg !1208
  %36 = load i64*, i64** %name_pad.addr, align 8, !dbg !1209
  store i64 %and, i64* %36, align 8, !dbg !1210
  %37 = load i8*, i8** %header, align 8, !dbg !1211
  %add.ptr44 = getelementptr inbounds i8, i8* %37, i64 54, !dbg !1212
  %call45 = call i64 @atol16(i8* %add.ptr44, i32 8), !dbg !1213
  %38 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1214
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %38, i32 0, i32 3, !dbg !1215
  store i64 %call45, i64* %entry_bytes_remaining, align 8, !dbg !1216
  %39 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1217
  %40 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1218
  %entry_bytes_remaining46 = getelementptr inbounds %struct.cpio, %struct.cpio* %40, i32 0, i32 3, !dbg !1219
  %41 = load i64, i64* %entry_bytes_remaining46, align 8, !dbg !1219
  call void @archive_entry_set_size(%struct.archive_entry* %39, i64 %41), !dbg !1220
  %42 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1221
  %entry_bytes_remaining47 = getelementptr inbounds %struct.cpio, %struct.cpio* %42, i32 0, i32 3, !dbg !1222
  %43 = load i64, i64* %entry_bytes_remaining47, align 8, !dbg !1222
  %sub48 = sub nsw i64 0, %43, !dbg !1223
  %and49 = and i64 3, %sub48, !dbg !1224
  %44 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1225
  %entry_padding = getelementptr inbounds %struct.cpio, %struct.cpio* %44, i32 0, i32 6, !dbg !1226
  store i64 %and49, i64* %entry_padding, align 8, !dbg !1227
  %45 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1228
  %call50 = call i64 @__archive_read_consume(%struct.archive_read* %45, i64 110), !dbg !1229
  %46 = load i32, i32* %r, align 4, !dbg !1230
  store i32 %46, i32* %retval, align 4, !dbg !1231
  br label %return, !dbg !1231

return:                                           ; preds = %if.end20, %if.then4, %if.then
  %47 = load i32, i32* %retval, align 4, !dbg !1232
  ret i32 %47, !dbg !1232
}

; Function Attrs: nounwind uwtable
define internal i32 @header_bin_be(%struct.archive_read* %a, %struct.cpio* %cpio, %struct.archive_entry* %entry1, i64* %namelength, i64* %name_pad) #0 !dbg !341 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %cpio.addr = alloca %struct.cpio*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %namelength.addr = alloca i64*, align 8
  %name_pad.addr = alloca i64*, align 8
  %h = alloca i8*, align 8
  %header = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1233, metadata !359), !dbg !1234
  store %struct.cpio* %cpio, %struct.cpio** %cpio.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio.addr, metadata !1235, metadata !359), !dbg !1236
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1237, metadata !359), !dbg !1238
  store i64* %namelength, i64** %namelength.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %namelength.addr, metadata !1239, metadata !359), !dbg !1240
  store i64* %name_pad, i64** %name_pad.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %name_pad.addr, metadata !1241, metadata !359), !dbg !1242
  call void @llvm.dbg.declare(metadata i8** %h, metadata !1243, metadata !359), !dbg !1244
  call void @llvm.dbg.declare(metadata i8** %header, metadata !1245, metadata !359), !dbg !1246
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1247
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 0, !dbg !1248
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !1249
  store i32 65539, i32* %archive_format, align 8, !dbg !1250
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1251
  %archive2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 0, !dbg !1252
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive2, i32 0, i32 4, !dbg !1253
  store i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.13, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !1254
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1255
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %2, i64 26, i64* null), !dbg !1256
  store i8* %call, i8** %h, align 8, !dbg !1257
  %3 = load i8*, i8** %h, align 8, !dbg !1258
  %cmp = icmp eq i8* %3, null, !dbg !1260
  br i1 %cmp, label %if.then, label %if.end, !dbg !1261

if.then:                                          ; preds = %entry
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1262
  %archive3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 0, !dbg !1264
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive3, i32 0, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.14, i32 0, i32 0)), !dbg !1265
  store i32 -30, i32* %retval, align 4, !dbg !1266
  br label %return, !dbg !1266

if.end:                                           ; preds = %entry
  %5 = load i8*, i8** %h, align 8, !dbg !1267
  store i8* %5, i8** %header, align 8, !dbg !1268
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1269
  %7 = load i8*, i8** %header, align 8, !dbg !1270
  %arrayidx = getelementptr inbounds i8, i8* %7, i64 2, !dbg !1270
  %8 = load i8, i8* %arrayidx, align 1, !dbg !1270
  %conv = zext i8 %8 to i32, !dbg !1270
  %mul = mul nsw i32 %conv, 256, !dbg !1271
  %9 = load i8*, i8** %header, align 8, !dbg !1272
  %arrayidx4 = getelementptr inbounds i8, i8* %9, i64 3, !dbg !1272
  %10 = load i8, i8* %arrayidx4, align 1, !dbg !1272
  %conv5 = zext i8 %10 to i32, !dbg !1272
  %add = add nsw i32 %mul, %conv5, !dbg !1273
  %conv6 = sext i32 %add to i64, !dbg !1270
  call void @archive_entry_set_dev(%struct.archive_entry* %6, i64 %conv6), !dbg !1274
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1275
  %12 = load i8*, i8** %header, align 8, !dbg !1276
  %arrayidx7 = getelementptr inbounds i8, i8* %12, i64 4, !dbg !1276
  %13 = load i8, i8* %arrayidx7, align 1, !dbg !1276
  %conv8 = zext i8 %13 to i32, !dbg !1276
  %mul9 = mul nsw i32 %conv8, 256, !dbg !1277
  %14 = load i8*, i8** %header, align 8, !dbg !1278
  %arrayidx10 = getelementptr inbounds i8, i8* %14, i64 5, !dbg !1278
  %15 = load i8, i8* %arrayidx10, align 1, !dbg !1278
  %conv11 = zext i8 %15 to i32, !dbg !1278
  %add12 = add nsw i32 %mul9, %conv11, !dbg !1279
  %conv13 = sext i32 %add12 to i64, !dbg !1276
  call void @archive_entry_set_ino(%struct.archive_entry* %11, i64 %conv13), !dbg !1280
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1281
  %17 = load i8*, i8** %header, align 8, !dbg !1282
  %arrayidx14 = getelementptr inbounds i8, i8* %17, i64 6, !dbg !1282
  %18 = load i8, i8* %arrayidx14, align 1, !dbg !1282
  %conv15 = zext i8 %18 to i32, !dbg !1282
  %mul16 = mul nsw i32 %conv15, 256, !dbg !1283
  %19 = load i8*, i8** %header, align 8, !dbg !1284
  %arrayidx17 = getelementptr inbounds i8, i8* %19, i64 7, !dbg !1284
  %20 = load i8, i8* %arrayidx17, align 1, !dbg !1284
  %conv18 = zext i8 %20 to i32, !dbg !1284
  %add19 = add nsw i32 %mul16, %conv18, !dbg !1285
  call void @archive_entry_set_mode(%struct.archive_entry* %16, i32 %add19), !dbg !1286
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1287
  %22 = load i8*, i8** %header, align 8, !dbg !1288
  %arrayidx20 = getelementptr inbounds i8, i8* %22, i64 8, !dbg !1288
  %23 = load i8, i8* %arrayidx20, align 1, !dbg !1288
  %conv21 = zext i8 %23 to i32, !dbg !1288
  %mul22 = mul nsw i32 %conv21, 256, !dbg !1289
  %24 = load i8*, i8** %header, align 8, !dbg !1290
  %arrayidx23 = getelementptr inbounds i8, i8* %24, i64 9, !dbg !1290
  %25 = load i8, i8* %arrayidx23, align 1, !dbg !1290
  %conv24 = zext i8 %25 to i32, !dbg !1290
  %add25 = add nsw i32 %mul22, %conv24, !dbg !1291
  %conv26 = sext i32 %add25 to i64, !dbg !1288
  call void @archive_entry_set_uid(%struct.archive_entry* %21, i64 %conv26), !dbg !1292
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1293
  %27 = load i8*, i8** %header, align 8, !dbg !1294
  %arrayidx27 = getelementptr inbounds i8, i8* %27, i64 10, !dbg !1294
  %28 = load i8, i8* %arrayidx27, align 1, !dbg !1294
  %conv28 = zext i8 %28 to i32, !dbg !1294
  %mul29 = mul nsw i32 %conv28, 256, !dbg !1295
  %29 = load i8*, i8** %header, align 8, !dbg !1296
  %arrayidx30 = getelementptr inbounds i8, i8* %29, i64 11, !dbg !1296
  %30 = load i8, i8* %arrayidx30, align 1, !dbg !1296
  %conv31 = zext i8 %30 to i32, !dbg !1296
  %add32 = add nsw i32 %mul29, %conv31, !dbg !1297
  %conv33 = sext i32 %add32 to i64, !dbg !1294
  call void @archive_entry_set_gid(%struct.archive_entry* %26, i64 %conv33), !dbg !1298
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1299
  %32 = load i8*, i8** %header, align 8, !dbg !1300
  %arrayidx34 = getelementptr inbounds i8, i8* %32, i64 12, !dbg !1300
  %33 = load i8, i8* %arrayidx34, align 1, !dbg !1300
  %conv35 = zext i8 %33 to i32, !dbg !1300
  %mul36 = mul nsw i32 %conv35, 256, !dbg !1301
  %34 = load i8*, i8** %header, align 8, !dbg !1302
  %arrayidx37 = getelementptr inbounds i8, i8* %34, i64 13, !dbg !1302
  %35 = load i8, i8* %arrayidx37, align 1, !dbg !1302
  %conv38 = zext i8 %35 to i32, !dbg !1302
  %add39 = add nsw i32 %mul36, %conv38, !dbg !1303
  call void @archive_entry_set_nlink(%struct.archive_entry* %31, i32 %add39), !dbg !1304
  %36 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1305
  %37 = load i8*, i8** %header, align 8, !dbg !1306
  %arrayidx40 = getelementptr inbounds i8, i8* %37, i64 14, !dbg !1306
  %38 = load i8, i8* %arrayidx40, align 1, !dbg !1306
  %conv41 = zext i8 %38 to i32, !dbg !1306
  %mul42 = mul nsw i32 %conv41, 256, !dbg !1307
  %39 = load i8*, i8** %header, align 8, !dbg !1308
  %arrayidx43 = getelementptr inbounds i8, i8* %39, i64 15, !dbg !1308
  %40 = load i8, i8* %arrayidx43, align 1, !dbg !1308
  %conv44 = zext i8 %40 to i32, !dbg !1308
  %add45 = add nsw i32 %mul42, %conv44, !dbg !1309
  %conv46 = sext i32 %add45 to i64, !dbg !1306
  call void @archive_entry_set_rdev(%struct.archive_entry* %36, i64 %conv46), !dbg !1310
  %41 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1311
  %42 = load i8*, i8** %header, align 8, !dbg !1312
  %add.ptr = getelementptr inbounds i8, i8* %42, i64 16, !dbg !1313
  %call47 = call i64 @be4(i8* %add.ptr), !dbg !1314
  call void @archive_entry_set_mtime(%struct.archive_entry* %41, i64 %call47, i64 0), !dbg !1315
  %43 = load i8*, i8** %header, align 8, !dbg !1317
  %arrayidx48 = getelementptr inbounds i8, i8* %43, i64 20, !dbg !1317
  %44 = load i8, i8* %arrayidx48, align 1, !dbg !1317
  %conv49 = zext i8 %44 to i32, !dbg !1317
  %mul50 = mul nsw i32 %conv49, 256, !dbg !1318
  %45 = load i8*, i8** %header, align 8, !dbg !1319
  %arrayidx51 = getelementptr inbounds i8, i8* %45, i64 21, !dbg !1319
  %46 = load i8, i8* %arrayidx51, align 1, !dbg !1319
  %conv52 = zext i8 %46 to i32, !dbg !1319
  %add53 = add nsw i32 %mul50, %conv52, !dbg !1320
  %conv54 = sext i32 %add53 to i64, !dbg !1317
  %47 = load i64*, i64** %namelength.addr, align 8, !dbg !1321
  store i64 %conv54, i64* %47, align 8, !dbg !1322
  %48 = load i64*, i64** %namelength.addr, align 8, !dbg !1323
  %49 = load i64, i64* %48, align 8, !dbg !1324
  %and = and i64 %49, 1, !dbg !1325
  %50 = load i64*, i64** %name_pad.addr, align 8, !dbg !1326
  store i64 %and, i64* %50, align 8, !dbg !1327
  %51 = load i8*, i8** %header, align 8, !dbg !1328
  %add.ptr55 = getelementptr inbounds i8, i8* %51, i64 22, !dbg !1329
  %call56 = call i64 @be4(i8* %add.ptr55), !dbg !1330
  %52 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1331
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %52, i32 0, i32 3, !dbg !1332
  store i64 %call56, i64* %entry_bytes_remaining, align 8, !dbg !1333
  %53 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1334
  %54 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1335
  %entry_bytes_remaining57 = getelementptr inbounds %struct.cpio, %struct.cpio* %54, i32 0, i32 3, !dbg !1336
  %55 = load i64, i64* %entry_bytes_remaining57, align 8, !dbg !1336
  call void @archive_entry_set_size(%struct.archive_entry* %53, i64 %55), !dbg !1337
  %56 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1338
  %entry_bytes_remaining58 = getelementptr inbounds %struct.cpio, %struct.cpio* %56, i32 0, i32 3, !dbg !1339
  %57 = load i64, i64* %entry_bytes_remaining58, align 8, !dbg !1339
  %and59 = and i64 %57, 1, !dbg !1340
  %58 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1341
  %entry_padding = getelementptr inbounds %struct.cpio, %struct.cpio* %58, i32 0, i32 6, !dbg !1342
  store i64 %and59, i64* %entry_padding, align 8, !dbg !1343
  %59 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1344
  %call60 = call i64 @__archive_read_consume(%struct.archive_read* %59, i64 26), !dbg !1345
  store i32 0, i32* %retval, align 4, !dbg !1346
  br label %return, !dbg !1346

return:                                           ; preds = %if.end, %if.then
  %60 = load i32, i32* %retval, align 4, !dbg !1347
  ret i32 %60, !dbg !1347
}

; Function Attrs: nounwind uwtable
define internal i32 @header_bin_le(%struct.archive_read* %a, %struct.cpio* %cpio, %struct.archive_entry* %entry1, i64* %namelength, i64* %name_pad) #0 !dbg !345 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %cpio.addr = alloca %struct.cpio*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %namelength.addr = alloca i64*, align 8
  %name_pad.addr = alloca i64*, align 8
  %h = alloca i8*, align 8
  %header = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1348, metadata !359), !dbg !1349
  store %struct.cpio* %cpio, %struct.cpio** %cpio.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio.addr, metadata !1350, metadata !359), !dbg !1351
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1352, metadata !359), !dbg !1353
  store i64* %namelength, i64** %namelength.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %namelength.addr, metadata !1354, metadata !359), !dbg !1355
  store i64* %name_pad, i64** %name_pad.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %name_pad.addr, metadata !1356, metadata !359), !dbg !1357
  call void @llvm.dbg.declare(metadata i8** %h, metadata !1358, metadata !359), !dbg !1359
  call void @llvm.dbg.declare(metadata i8** %header, metadata !1360, metadata !359), !dbg !1361
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1362
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 0, !dbg !1363
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !1364
  store i32 65538, i32* %archive_format, align 8, !dbg !1365
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1366
  %archive2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 0, !dbg !1367
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive2, i32 0, i32 4, !dbg !1368
  store i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.15, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !1369
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1370
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %2, i64 26, i64* null), !dbg !1371
  store i8* %call, i8** %h, align 8, !dbg !1372
  %3 = load i8*, i8** %h, align 8, !dbg !1373
  %cmp = icmp eq i8* %3, null, !dbg !1375
  br i1 %cmp, label %if.then, label %if.end, !dbg !1376

if.then:                                          ; preds = %entry
  %4 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1377
  %archive3 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %4, i32 0, i32 0, !dbg !1379
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive3, i32 0, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.14, i32 0, i32 0)), !dbg !1380
  store i32 -30, i32* %retval, align 4, !dbg !1381
  br label %return, !dbg !1381

if.end:                                           ; preds = %entry
  %5 = load i8*, i8** %h, align 8, !dbg !1382
  store i8* %5, i8** %header, align 8, !dbg !1383
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1384
  %7 = load i8*, i8** %header, align 8, !dbg !1385
  %arrayidx = getelementptr inbounds i8, i8* %7, i64 2, !dbg !1385
  %8 = load i8, i8* %arrayidx, align 1, !dbg !1385
  %conv = zext i8 %8 to i32, !dbg !1385
  %9 = load i8*, i8** %header, align 8, !dbg !1386
  %arrayidx4 = getelementptr inbounds i8, i8* %9, i64 3, !dbg !1386
  %10 = load i8, i8* %arrayidx4, align 1, !dbg !1386
  %conv5 = zext i8 %10 to i32, !dbg !1386
  %mul = mul nsw i32 %conv5, 256, !dbg !1387
  %add = add nsw i32 %conv, %mul, !dbg !1388
  %conv6 = sext i32 %add to i64, !dbg !1385
  call void @archive_entry_set_dev(%struct.archive_entry* %6, i64 %conv6), !dbg !1389
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1390
  %12 = load i8*, i8** %header, align 8, !dbg !1391
  %arrayidx7 = getelementptr inbounds i8, i8* %12, i64 4, !dbg !1391
  %13 = load i8, i8* %arrayidx7, align 1, !dbg !1391
  %conv8 = zext i8 %13 to i32, !dbg !1391
  %14 = load i8*, i8** %header, align 8, !dbg !1392
  %arrayidx9 = getelementptr inbounds i8, i8* %14, i64 5, !dbg !1392
  %15 = load i8, i8* %arrayidx9, align 1, !dbg !1392
  %conv10 = zext i8 %15 to i32, !dbg !1392
  %mul11 = mul nsw i32 %conv10, 256, !dbg !1393
  %add12 = add nsw i32 %conv8, %mul11, !dbg !1394
  %conv13 = sext i32 %add12 to i64, !dbg !1391
  call void @archive_entry_set_ino(%struct.archive_entry* %11, i64 %conv13), !dbg !1395
  %16 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1396
  %17 = load i8*, i8** %header, align 8, !dbg !1397
  %arrayidx14 = getelementptr inbounds i8, i8* %17, i64 6, !dbg !1397
  %18 = load i8, i8* %arrayidx14, align 1, !dbg !1397
  %conv15 = zext i8 %18 to i32, !dbg !1397
  %19 = load i8*, i8** %header, align 8, !dbg !1398
  %arrayidx16 = getelementptr inbounds i8, i8* %19, i64 7, !dbg !1398
  %20 = load i8, i8* %arrayidx16, align 1, !dbg !1398
  %conv17 = zext i8 %20 to i32, !dbg !1398
  %mul18 = mul nsw i32 %conv17, 256, !dbg !1399
  %add19 = add nsw i32 %conv15, %mul18, !dbg !1400
  call void @archive_entry_set_mode(%struct.archive_entry* %16, i32 %add19), !dbg !1401
  %21 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1402
  %22 = load i8*, i8** %header, align 8, !dbg !1403
  %arrayidx20 = getelementptr inbounds i8, i8* %22, i64 8, !dbg !1403
  %23 = load i8, i8* %arrayidx20, align 1, !dbg !1403
  %conv21 = zext i8 %23 to i32, !dbg !1403
  %24 = load i8*, i8** %header, align 8, !dbg !1404
  %arrayidx22 = getelementptr inbounds i8, i8* %24, i64 9, !dbg !1404
  %25 = load i8, i8* %arrayidx22, align 1, !dbg !1404
  %conv23 = zext i8 %25 to i32, !dbg !1404
  %mul24 = mul nsw i32 %conv23, 256, !dbg !1405
  %add25 = add nsw i32 %conv21, %mul24, !dbg !1406
  %conv26 = sext i32 %add25 to i64, !dbg !1403
  call void @archive_entry_set_uid(%struct.archive_entry* %21, i64 %conv26), !dbg !1407
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1408
  %27 = load i8*, i8** %header, align 8, !dbg !1409
  %arrayidx27 = getelementptr inbounds i8, i8* %27, i64 10, !dbg !1409
  %28 = load i8, i8* %arrayidx27, align 1, !dbg !1409
  %conv28 = zext i8 %28 to i32, !dbg !1409
  %29 = load i8*, i8** %header, align 8, !dbg !1410
  %arrayidx29 = getelementptr inbounds i8, i8* %29, i64 11, !dbg !1410
  %30 = load i8, i8* %arrayidx29, align 1, !dbg !1410
  %conv30 = zext i8 %30 to i32, !dbg !1410
  %mul31 = mul nsw i32 %conv30, 256, !dbg !1411
  %add32 = add nsw i32 %conv28, %mul31, !dbg !1412
  %conv33 = sext i32 %add32 to i64, !dbg !1409
  call void @archive_entry_set_gid(%struct.archive_entry* %26, i64 %conv33), !dbg !1413
  %31 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1414
  %32 = load i8*, i8** %header, align 8, !dbg !1415
  %arrayidx34 = getelementptr inbounds i8, i8* %32, i64 12, !dbg !1415
  %33 = load i8, i8* %arrayidx34, align 1, !dbg !1415
  %conv35 = zext i8 %33 to i32, !dbg !1415
  %34 = load i8*, i8** %header, align 8, !dbg !1416
  %arrayidx36 = getelementptr inbounds i8, i8* %34, i64 13, !dbg !1416
  %35 = load i8, i8* %arrayidx36, align 1, !dbg !1416
  %conv37 = zext i8 %35 to i32, !dbg !1416
  %mul38 = mul nsw i32 %conv37, 256, !dbg !1417
  %add39 = add nsw i32 %conv35, %mul38, !dbg !1418
  call void @archive_entry_set_nlink(%struct.archive_entry* %31, i32 %add39), !dbg !1419
  %36 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1420
  %37 = load i8*, i8** %header, align 8, !dbg !1421
  %arrayidx40 = getelementptr inbounds i8, i8* %37, i64 14, !dbg !1421
  %38 = load i8, i8* %arrayidx40, align 1, !dbg !1421
  %conv41 = zext i8 %38 to i32, !dbg !1421
  %39 = load i8*, i8** %header, align 8, !dbg !1422
  %arrayidx42 = getelementptr inbounds i8, i8* %39, i64 15, !dbg !1422
  %40 = load i8, i8* %arrayidx42, align 1, !dbg !1422
  %conv43 = zext i8 %40 to i32, !dbg !1422
  %mul44 = mul nsw i32 %conv43, 256, !dbg !1423
  %add45 = add nsw i32 %conv41, %mul44, !dbg !1424
  %conv46 = sext i32 %add45 to i64, !dbg !1421
  call void @archive_entry_set_rdev(%struct.archive_entry* %36, i64 %conv46), !dbg !1425
  %41 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1426
  %42 = load i8*, i8** %header, align 8, !dbg !1427
  %add.ptr = getelementptr inbounds i8, i8* %42, i64 16, !dbg !1428
  %call47 = call i64 @le4(i8* %add.ptr), !dbg !1429
  call void @archive_entry_set_mtime(%struct.archive_entry* %41, i64 %call47, i64 0), !dbg !1430
  %43 = load i8*, i8** %header, align 8, !dbg !1432
  %arrayidx48 = getelementptr inbounds i8, i8* %43, i64 20, !dbg !1432
  %44 = load i8, i8* %arrayidx48, align 1, !dbg !1432
  %conv49 = zext i8 %44 to i32, !dbg !1432
  %45 = load i8*, i8** %header, align 8, !dbg !1433
  %arrayidx50 = getelementptr inbounds i8, i8* %45, i64 21, !dbg !1433
  %46 = load i8, i8* %arrayidx50, align 1, !dbg !1433
  %conv51 = zext i8 %46 to i32, !dbg !1433
  %mul52 = mul nsw i32 %conv51, 256, !dbg !1434
  %add53 = add nsw i32 %conv49, %mul52, !dbg !1435
  %conv54 = sext i32 %add53 to i64, !dbg !1432
  %47 = load i64*, i64** %namelength.addr, align 8, !dbg !1436
  store i64 %conv54, i64* %47, align 8, !dbg !1437
  %48 = load i64*, i64** %namelength.addr, align 8, !dbg !1438
  %49 = load i64, i64* %48, align 8, !dbg !1439
  %and = and i64 %49, 1, !dbg !1440
  %50 = load i64*, i64** %name_pad.addr, align 8, !dbg !1441
  store i64 %and, i64* %50, align 8, !dbg !1442
  %51 = load i8*, i8** %header, align 8, !dbg !1443
  %add.ptr55 = getelementptr inbounds i8, i8* %51, i64 22, !dbg !1444
  %call56 = call i64 @le4(i8* %add.ptr55), !dbg !1445
  %52 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1446
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %52, i32 0, i32 3, !dbg !1447
  store i64 %call56, i64* %entry_bytes_remaining, align 8, !dbg !1448
  %53 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1449
  %54 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1450
  %entry_bytes_remaining57 = getelementptr inbounds %struct.cpio, %struct.cpio* %54, i32 0, i32 3, !dbg !1451
  %55 = load i64, i64* %entry_bytes_remaining57, align 8, !dbg !1451
  call void @archive_entry_set_size(%struct.archive_entry* %53, i64 %55), !dbg !1452
  %56 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1453
  %entry_bytes_remaining58 = getelementptr inbounds %struct.cpio, %struct.cpio* %56, i32 0, i32 3, !dbg !1454
  %57 = load i64, i64* %entry_bytes_remaining58, align 8, !dbg !1454
  %and59 = and i64 %57, 1, !dbg !1455
  %58 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1456
  %entry_padding = getelementptr inbounds %struct.cpio, %struct.cpio* %58, i32 0, i32 6, !dbg !1457
  store i64 %and59, i64* %entry_padding, align 8, !dbg !1458
  %59 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1459
  %call60 = call i64 @__archive_read_consume(%struct.archive_read* %59, i64 26), !dbg !1460
  store i32 0, i32* %retval, align 4, !dbg !1461
  br label %return, !dbg !1461

return:                                           ; preds = %if.end, %if.then
  %60 = load i32, i32* %retval, align 4, !dbg !1462
  ret i32 %60, !dbg !1462
}

; Function Attrs: nounwind uwtable
define internal i32 @find_odc_header(%struct.archive_read* %a) #0 !dbg !328 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %h = alloca i8*, align 8
  %p = alloca i8*, align 8
  %q = alloca i8*, align 8
  %skip = alloca i64, align 8
  %skipped = alloca i64, align 8
  %bytes = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1463, metadata !359), !dbg !1464
  call void @llvm.dbg.declare(metadata i8** %h, metadata !1465, metadata !359), !dbg !1466
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1467, metadata !359), !dbg !1468
  call void @llvm.dbg.declare(metadata i8** %q, metadata !1469, metadata !359), !dbg !1470
  call void @llvm.dbg.declare(metadata i64* %skip, metadata !1471, metadata !359), !dbg !1472
  call void @llvm.dbg.declare(metadata i64* %skipped, metadata !1473, metadata !359), !dbg !1474
  store i64 0, i64* %skipped, align 8, !dbg !1474
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !1475, metadata !359), !dbg !1476
  br label %for.cond, !dbg !1477

for.cond:                                         ; preds = %while.end, %entry
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1478
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %0, i64 76, i64* %bytes), !dbg !1482
  store i8* %call, i8** %h, align 8, !dbg !1483
  %1 = load i8*, i8** %h, align 8, !dbg !1484
  %cmp = icmp eq i8* %1, null, !dbg !1486
  br i1 %cmp, label %if.then, label %if.end, !dbg !1487

if.then:                                          ; preds = %for.cond
  store i32 -30, i32* %retval, align 4, !dbg !1488
  br label %return, !dbg !1488

if.end:                                           ; preds = %for.cond
  %2 = load i8*, i8** %h, align 8, !dbg !1489
  store i8* %2, i8** %p, align 8, !dbg !1490
  %3 = load i8*, i8** %p, align 8, !dbg !1491
  %4 = load i64, i64* %bytes, align 8, !dbg !1492
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 %4, !dbg !1493
  store i8* %add.ptr, i8** %q, align 8, !dbg !1494
  %5 = load i8*, i8** %p, align 8, !dbg !1495
  %call1 = call i32 @memcmp(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i32 0, i32 0), i8* %5, i64 6) #7, !dbg !1497
  %cmp2 = icmp eq i32 %call1, 0, !dbg !1498
  br i1 %cmp2, label %land.lhs.true, label %if.end5, !dbg !1499

land.lhs.true:                                    ; preds = %if.end
  %6 = load i8*, i8** %p, align 8, !dbg !1500
  %call3 = call i32 @is_octal(i8* %6, i64 76), !dbg !1502
  %tobool = icmp ne i32 %call3, 0, !dbg !1502
  br i1 %tobool, label %if.then4, label %if.end5, !dbg !1503

if.then4:                                         ; preds = %land.lhs.true
  store i32 0, i32* %retval, align 4, !dbg !1504
  br label %return, !dbg !1504

if.end5:                                          ; preds = %land.lhs.true, %if.end
  %7 = load i8*, i8** %p, align 8, !dbg !1505
  %call6 = call i32 @memcmp(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.4, i32 0, i32 0), i8* %7, i64 6) #7, !dbg !1507
  %cmp7 = icmp eq i32 %call6, 0, !dbg !1508
  br i1 %cmp7, label %land.lhs.true8, label %if.end12, !dbg !1509

land.lhs.true8:                                   ; preds = %if.end5
  %8 = load i8*, i8** %p, align 8, !dbg !1510
  %9 = load i64, i64* %bytes, align 8, !dbg !1512
  %call9 = call i32 @is_afio_large(i8* %8, i64 %9), !dbg !1513
  %tobool10 = icmp ne i32 %call9, 0, !dbg !1513
  br i1 %tobool10, label %if.then11, label %if.end12, !dbg !1514

if.then11:                                        ; preds = %land.lhs.true8
  %10 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1515
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %10, i32 0, i32 0, !dbg !1517
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !1518
  store i32 65542, i32* %archive_format, align 8, !dbg !1519
  store i32 0, i32* %retval, align 4, !dbg !1520
  br label %return, !dbg !1520

if.end12:                                         ; preds = %land.lhs.true8, %if.end5
  br label %while.cond, !dbg !1521

while.cond:                                       ; preds = %sw.epilog, %if.end12
  %11 = load i8*, i8** %p, align 8, !dbg !1522
  %add.ptr13 = getelementptr inbounds i8, i8* %11, i64 76, !dbg !1524
  %12 = load i8*, i8** %q, align 8, !dbg !1525
  %cmp14 = icmp ule i8* %add.ptr13, %12, !dbg !1526
  br i1 %cmp14, label %while.body, label %while.end, !dbg !1527

while.body:                                       ; preds = %while.cond
  %13 = load i8*, i8** %p, align 8, !dbg !1528
  %arrayidx = getelementptr inbounds i8, i8* %13, i64 5, !dbg !1528
  %14 = load i8, i8* %arrayidx, align 1, !dbg !1528
  %conv = sext i8 %14 to i32, !dbg !1528
  switch i32 %conv, label %sw.default [
    i32 55, label %sw.bb
    i32 48, label %sw.bb48
  ], !dbg !1530

sw.bb:                                            ; preds = %while.body
  %15 = load i8*, i8** %p, align 8, !dbg !1531
  %call15 = call i32 @memcmp(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.3, i32 0, i32 0), i8* %15, i64 6) #7, !dbg !1534
  %cmp16 = icmp eq i32 %call15, 0, !dbg !1535
  br i1 %cmp16, label %land.lhs.true18, label %lor.lhs.false, !dbg !1536

land.lhs.true18:                                  ; preds = %sw.bb
  %16 = load i8*, i8** %p, align 8, !dbg !1537
  %call19 = call i32 @is_octal(i8* %16, i64 76), !dbg !1539
  %tobool20 = icmp ne i32 %call19, 0, !dbg !1539
  br i1 %tobool20, label %if.then27, label %lor.lhs.false, !dbg !1540

lor.lhs.false:                                    ; preds = %land.lhs.true18, %sw.bb
  %17 = load i8*, i8** %p, align 8, !dbg !1541
  %call21 = call i32 @memcmp(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.4, i32 0, i32 0), i8* %17, i64 6) #7, !dbg !1542
  %cmp22 = icmp eq i32 %call21, 0, !dbg !1543
  br i1 %cmp22, label %land.lhs.true24, label %if.end46, !dbg !1544

land.lhs.true24:                                  ; preds = %lor.lhs.false
  %18 = load i8*, i8** %p, align 8, !dbg !1545
  %19 = load i8*, i8** %q, align 8, !dbg !1546
  %20 = load i8*, i8** %p, align 8, !dbg !1547
  %sub.ptr.lhs.cast = ptrtoint i8* %19 to i64, !dbg !1548
  %sub.ptr.rhs.cast = ptrtoint i8* %20 to i64, !dbg !1548
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !1548
  %call25 = call i32 @is_afio_large(i8* %18, i64 %sub.ptr.sub), !dbg !1549
  %tobool26 = icmp ne i32 %call25, 0, !dbg !1549
  br i1 %tobool26, label %if.then27, label %if.end46, !dbg !1550

if.then27:                                        ; preds = %land.lhs.true24, %land.lhs.true18
  %21 = load i8*, i8** %p, align 8, !dbg !1552
  %22 = load i8*, i8** %h, align 8, !dbg !1554
  %sub.ptr.lhs.cast28 = ptrtoint i8* %21 to i64, !dbg !1555
  %sub.ptr.rhs.cast29 = ptrtoint i8* %22 to i64, !dbg !1555
  %sub.ptr.sub30 = sub i64 %sub.ptr.lhs.cast28, %sub.ptr.rhs.cast29, !dbg !1555
  store i64 %sub.ptr.sub30, i64* %skip, align 8, !dbg !1556
  %23 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1557
  %24 = load i64, i64* %skip, align 8, !dbg !1558
  %call31 = call i64 @__archive_read_consume(%struct.archive_read* %23, i64 %24), !dbg !1559
  %25 = load i64, i64* %skip, align 8, !dbg !1560
  %26 = load i64, i64* %skipped, align 8, !dbg !1561
  %add = add i64 %26, %25, !dbg !1561
  store i64 %add, i64* %skipped, align 8, !dbg !1561
  %27 = load i8*, i8** %p, align 8, !dbg !1562
  %arrayidx32 = getelementptr inbounds i8, i8* %27, i64 4, !dbg !1562
  %28 = load i8, i8* %arrayidx32, align 1, !dbg !1562
  %conv33 = sext i8 %28 to i32, !dbg !1562
  %cmp34 = icmp eq i32 %conv33, 50, !dbg !1564
  br i1 %cmp34, label %if.then36, label %if.end39, !dbg !1565

if.then36:                                        ; preds = %if.then27
  %29 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1566
  %archive37 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %29, i32 0, i32 0, !dbg !1567
  %archive_format38 = getelementptr inbounds %struct.archive, %struct.archive* %archive37, i32 0, i32 3, !dbg !1568
  store i32 65542, i32* %archive_format38, align 8, !dbg !1569
  br label %if.end39, !dbg !1566

if.end39:                                         ; preds = %if.then36, %if.then27
  %30 = load i64, i64* %skipped, align 8, !dbg !1570
  %cmp40 = icmp ugt i64 %30, 0, !dbg !1572
  br i1 %cmp40, label %if.then42, label %if.end45, !dbg !1573

if.then42:                                        ; preds = %if.end39
  %31 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1574
  %archive43 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %31, i32 0, i32 0, !dbg !1576
  %32 = load i64, i64* %skipped, align 8, !dbg !1577
  %conv44 = trunc i64 %32 to i32, !dbg !1578
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive43, i32 0, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.8, i32 0, i32 0), i32 %conv44), !dbg !1579
  store i32 -20, i32* %retval, align 4, !dbg !1580
  br label %return, !dbg !1580

if.end45:                                         ; preds = %if.end39
  store i32 0, i32* %retval, align 4, !dbg !1581
  br label %return, !dbg !1581

if.end46:                                         ; preds = %land.lhs.true24, %lor.lhs.false
  %33 = load i8*, i8** %p, align 8, !dbg !1582
  %add.ptr47 = getelementptr inbounds i8, i8* %33, i64 2, !dbg !1582
  store i8* %add.ptr47, i8** %p, align 8, !dbg !1582
  br label %sw.epilog, !dbg !1583

sw.bb48:                                          ; preds = %while.body
  %34 = load i8*, i8** %p, align 8, !dbg !1584
  %incdec.ptr = getelementptr inbounds i8, i8* %34, i32 1, !dbg !1584
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !1584
  br label %sw.epilog, !dbg !1585

sw.default:                                       ; preds = %while.body
  %35 = load i8*, i8** %p, align 8, !dbg !1586
  %add.ptr49 = getelementptr inbounds i8, i8* %35, i64 6, !dbg !1586
  store i8* %add.ptr49, i8** %p, align 8, !dbg !1586
  br label %sw.epilog, !dbg !1587

sw.epilog:                                        ; preds = %sw.default, %sw.bb48, %if.end46
  br label %while.cond, !dbg !1588

while.end:                                        ; preds = %while.cond
  %36 = load i8*, i8** %p, align 8, !dbg !1590
  %37 = load i8*, i8** %h, align 8, !dbg !1591
  %sub.ptr.lhs.cast50 = ptrtoint i8* %36 to i64, !dbg !1592
  %sub.ptr.rhs.cast51 = ptrtoint i8* %37 to i64, !dbg !1592
  %sub.ptr.sub52 = sub i64 %sub.ptr.lhs.cast50, %sub.ptr.rhs.cast51, !dbg !1592
  store i64 %sub.ptr.sub52, i64* %skip, align 8, !dbg !1593
  %38 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1594
  %39 = load i64, i64* %skip, align 8, !dbg !1595
  %call53 = call i64 @__archive_read_consume(%struct.archive_read* %38, i64 %39), !dbg !1596
  %40 = load i64, i64* %skip, align 8, !dbg !1597
  %41 = load i64, i64* %skipped, align 8, !dbg !1598
  %add54 = add i64 %41, %40, !dbg !1598
  store i64 %add54, i64* %skipped, align 8, !dbg !1598
  br label %for.cond, !dbg !1599

return:                                           ; preds = %if.end45, %if.then42, %if.then11, %if.then4, %if.then
  %42 = load i32, i32* %retval, align 4, !dbg !1601
  ret i32 %42, !dbg !1601
}

; Function Attrs: nounwind uwtable
define internal i32 @header_afiol(%struct.archive_read* %a, %struct.cpio* %cpio, %struct.archive_entry* %entry1, i64* %namelength, i64* %name_pad) #0 !dbg !334 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %cpio.addr = alloca %struct.cpio*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %namelength.addr = alloca i64*, align 8
  %name_pad.addr = alloca i64*, align 8
  %h = alloca i8*, align 8
  %header = alloca i8*, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1602, metadata !359), !dbg !1603
  store %struct.cpio* %cpio, %struct.cpio** %cpio.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio.addr, metadata !1604, metadata !359), !dbg !1605
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !1606, metadata !359), !dbg !1607
  store i64* %namelength, i64** %namelength.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %namelength.addr, metadata !1608, metadata !359), !dbg !1609
  store i64* %name_pad, i64** %name_pad.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %name_pad.addr, metadata !1610, metadata !359), !dbg !1611
  call void @llvm.dbg.declare(metadata i8** %h, metadata !1612, metadata !359), !dbg !1613
  call void @llvm.dbg.declare(metadata i8** %header, metadata !1614, metadata !359), !dbg !1615
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1616
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %0, i32 0, i32 0, !dbg !1617
  %archive_format = getelementptr inbounds %struct.archive, %struct.archive* %archive, i32 0, i32 3, !dbg !1618
  store i32 65542, i32* %archive_format, align 8, !dbg !1619
  %1 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1620
  %archive2 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %1, i32 0, i32 0, !dbg !1621
  %archive_format_name = getelementptr inbounds %struct.archive, %struct.archive* %archive2, i32 0, i32 4, !dbg !1622
  store i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.9, i32 0, i32 0), i8** %archive_format_name, align 8, !dbg !1623
  %2 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1624
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %2, i64 116, i64* null), !dbg !1625
  store i8* %call, i8** %h, align 8, !dbg !1626
  %3 = load i8*, i8** %h, align 8, !dbg !1627
  %cmp = icmp eq i8* %3, null, !dbg !1629
  br i1 %cmp, label %if.then, label %if.end, !dbg !1630

if.then:                                          ; preds = %entry
  store i32 -30, i32* %retval, align 4, !dbg !1631
  br label %return, !dbg !1631

if.end:                                           ; preds = %entry
  %4 = load i8*, i8** %h, align 8, !dbg !1632
  store i8* %4, i8** %header, align 8, !dbg !1633
  %5 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1634
  %6 = load i8*, i8** %header, align 8, !dbg !1635
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 6, !dbg !1636
  %call3 = call i64 @atol16(i8* %add.ptr, i32 8), !dbg !1637
  call void @archive_entry_set_dev(%struct.archive_entry* %5, i64 %call3), !dbg !1638
  %7 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1639
  %8 = load i8*, i8** %header, align 8, !dbg !1640
  %add.ptr4 = getelementptr inbounds i8, i8* %8, i64 14, !dbg !1641
  %call5 = call i64 @atol16(i8* %add.ptr4, i32 16), !dbg !1642
  call void @archive_entry_set_ino(%struct.archive_entry* %7, i64 %call5), !dbg !1643
  %9 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1645
  %10 = load i8*, i8** %header, align 8, !dbg !1646
  %add.ptr6 = getelementptr inbounds i8, i8* %10, i64 31, !dbg !1647
  %call7 = call i64 @atol8(i8* %add.ptr6, i32 6), !dbg !1648
  %conv = trunc i64 %call7 to i32, !dbg !1649
  call void @archive_entry_set_mode(%struct.archive_entry* %9, i32 %conv), !dbg !1650
  %11 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1651
  %12 = load i8*, i8** %header, align 8, !dbg !1652
  %add.ptr8 = getelementptr inbounds i8, i8* %12, i64 37, !dbg !1653
  %call9 = call i64 @atol16(i8* %add.ptr8, i32 8), !dbg !1654
  call void @archive_entry_set_uid(%struct.archive_entry* %11, i64 %call9), !dbg !1655
  %13 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1656
  %14 = load i8*, i8** %header, align 8, !dbg !1657
  %add.ptr10 = getelementptr inbounds i8, i8* %14, i64 45, !dbg !1658
  %call11 = call i64 @atol16(i8* %add.ptr10, i32 8), !dbg !1659
  call void @archive_entry_set_gid(%struct.archive_entry* %13, i64 %call11), !dbg !1660
  %15 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1661
  %16 = load i8*, i8** %header, align 8, !dbg !1662
  %add.ptr12 = getelementptr inbounds i8, i8* %16, i64 53, !dbg !1663
  %call13 = call i64 @atol16(i8* %add.ptr12, i32 8), !dbg !1664
  %conv14 = trunc i64 %call13 to i32, !dbg !1665
  call void @archive_entry_set_nlink(%struct.archive_entry* %15, i32 %conv14), !dbg !1666
  %17 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1667
  %18 = load i8*, i8** %header, align 8, !dbg !1668
  %add.ptr15 = getelementptr inbounds i8, i8* %18, i64 61, !dbg !1669
  %call16 = call i64 @atol16(i8* %add.ptr15, i32 8), !dbg !1670
  call void @archive_entry_set_rdev(%struct.archive_entry* %17, i64 %call16), !dbg !1671
  %19 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1672
  %20 = load i8*, i8** %header, align 8, !dbg !1673
  %add.ptr17 = getelementptr inbounds i8, i8* %20, i64 69, !dbg !1674
  %call18 = call i64 @atol16(i8* %add.ptr17, i32 16), !dbg !1675
  call void @archive_entry_set_mtime(%struct.archive_entry* %19, i64 %call18, i64 0), !dbg !1676
  %21 = load i8*, i8** %header, align 8, !dbg !1677
  %add.ptr19 = getelementptr inbounds i8, i8* %21, i64 86, !dbg !1678
  %call20 = call i64 @atol16(i8* %add.ptr19, i32 4), !dbg !1679
  %22 = load i64*, i64** %namelength.addr, align 8, !dbg !1680
  store i64 %call20, i64* %22, align 8, !dbg !1681
  %23 = load i64*, i64** %name_pad.addr, align 8, !dbg !1682
  store i64 0, i64* %23, align 8, !dbg !1683
  %24 = load i8*, i8** %header, align 8, !dbg !1684
  %add.ptr21 = getelementptr inbounds i8, i8* %24, i64 99, !dbg !1685
  %call22 = call i64 @atol16(i8* %add.ptr21, i32 16), !dbg !1686
  %25 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1687
  %entry_bytes_remaining = getelementptr inbounds %struct.cpio, %struct.cpio* %25, i32 0, i32 3, !dbg !1688
  store i64 %call22, i64* %entry_bytes_remaining, align 8, !dbg !1689
  %26 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !1690
  %27 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1691
  %entry_bytes_remaining23 = getelementptr inbounds %struct.cpio, %struct.cpio* %27, i32 0, i32 3, !dbg !1692
  %28 = load i64, i64* %entry_bytes_remaining23, align 8, !dbg !1692
  call void @archive_entry_set_size(%struct.archive_entry* %26, i64 %28), !dbg !1693
  %29 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !1694
  %entry_padding = getelementptr inbounds %struct.cpio, %struct.cpio* %29, i32 0, i32 6, !dbg !1695
  store i64 0, i64* %entry_padding, align 8, !dbg !1696
  %30 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1697
  %call24 = call i64 @__archive_read_consume(%struct.archive_read* %30, i64 116), !dbg !1698
  store i32 0, i32* %retval, align 4, !dbg !1699
  br label %return, !dbg !1699

return:                                           ; preds = %if.end, %if.then
  %31 = load i32, i32* %retval, align 4, !dbg !1700
  ret i32 %31, !dbg !1700
}

declare void @archive_entry_set_dev(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind uwtable
define internal i64 @atol8(i8* %p, i32 %char_cnt) #0 !dbg !338 {
entry:
  %retval = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %char_cnt.addr = alloca i32, align 4
  %l = alloca i64, align 8
  %digit = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1701, metadata !359), !dbg !1702
  store i32 %char_cnt, i32* %char_cnt.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %char_cnt.addr, metadata !1703, metadata !359), !dbg !1704
  call void @llvm.dbg.declare(metadata i64* %l, metadata !1705, metadata !359), !dbg !1706
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !1707, metadata !359), !dbg !1708
  store i64 0, i64* %l, align 8, !dbg !1709
  br label %while.cond, !dbg !1710

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i32, i32* %char_cnt.addr, align 4, !dbg !1711
  %dec = add i32 %0, -1, !dbg !1711
  store i32 %dec, i32* %char_cnt.addr, align 4, !dbg !1711
  %cmp = icmp ugt i32 %0, 0, !dbg !1713
  br i1 %cmp, label %while.body, label %while.end, !dbg !1714

while.body:                                       ; preds = %while.cond
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1715
  %2 = load i8, i8* %1, align 1, !dbg !1718
  %conv = sext i8 %2 to i32, !dbg !1718
  %cmp1 = icmp sge i32 %conv, 48, !dbg !1719
  br i1 %cmp1, label %land.lhs.true, label %if.else, !dbg !1720

land.lhs.true:                                    ; preds = %while.body
  %3 = load i8*, i8** %p.addr, align 8, !dbg !1721
  %4 = load i8, i8* %3, align 1, !dbg !1723
  %conv3 = sext i8 %4 to i32, !dbg !1723
  %cmp4 = icmp sle i32 %conv3, 55, !dbg !1724
  br i1 %cmp4, label %if.then, label %if.else, !dbg !1725

if.then:                                          ; preds = %land.lhs.true
  %5 = load i8*, i8** %p.addr, align 8, !dbg !1726
  %6 = load i8, i8* %5, align 1, !dbg !1727
  %conv6 = sext i8 %6 to i32, !dbg !1727
  %sub = sub nsw i32 %conv6, 48, !dbg !1728
  store i32 %sub, i32* %digit, align 4, !dbg !1729
  br label %if.end, !dbg !1730

if.else:                                          ; preds = %land.lhs.true, %while.body
  %7 = load i64, i64* %l, align 8, !dbg !1731
  store i64 %7, i64* %retval, align 8, !dbg !1732
  br label %return, !dbg !1732

if.end:                                           ; preds = %if.then
  %8 = load i8*, i8** %p.addr, align 8, !dbg !1733
  %incdec.ptr = getelementptr inbounds i8, i8* %8, i32 1, !dbg !1733
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1733
  %9 = load i64, i64* %l, align 8, !dbg !1734
  %shl = shl i64 %9, 3, !dbg !1734
  store i64 %shl, i64* %l, align 8, !dbg !1734
  %10 = load i32, i32* %digit, align 4, !dbg !1735
  %conv7 = sext i32 %10 to i64, !dbg !1735
  %11 = load i64, i64* %l, align 8, !dbg !1736
  %or = or i64 %11, %conv7, !dbg !1736
  store i64 %or, i64* %l, align 8, !dbg !1736
  br label %while.cond, !dbg !1737

while.end:                                        ; preds = %while.cond
  %12 = load i64, i64* %l, align 8, !dbg !1739
  store i64 %12, i64* %retval, align 8, !dbg !1740
  br label %return, !dbg !1740

return:                                           ; preds = %while.end, %if.else
  %13 = load i64, i64* %retval, align 8, !dbg !1741
  ret i64 %13, !dbg !1741
}

declare void @archive_entry_set_ino(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_mode(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_uid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_gid(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_nlink(%struct.archive_entry*, i32) #2

declare void @archive_entry_set_rdev(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_mtime(%struct.archive_entry*, i64, i64) #2

declare void @archive_entry_set_size(%struct.archive_entry*, i64) #2

declare i64 @__archive_read_consume(%struct.archive_read*, i64) #2

; Function Attrs: nounwind uwtable
define internal i32 @is_octal(i8* %p, i64 %len) #0 !dbg !329 {
entry:
  %retval = alloca i32, align 4
  %p.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1742, metadata !359), !dbg !1743
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !1744, metadata !359), !dbg !1745
  br label %while.cond, !dbg !1746

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i64, i64* %len.addr, align 8, !dbg !1747
  %dec = add i64 %0, -1, !dbg !1747
  store i64 %dec, i64* %len.addr, align 8, !dbg !1747
  %cmp = icmp ugt i64 %0, 0, !dbg !1749
  br i1 %cmp, label %while.body, label %while.end, !dbg !1750

while.body:                                       ; preds = %while.cond
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1751
  %2 = load i8, i8* %1, align 1, !dbg !1754
  %conv = sext i8 %2 to i32, !dbg !1754
  %cmp1 = icmp slt i32 %conv, 48, !dbg !1755
  br i1 %cmp1, label %if.then, label %lor.lhs.false, !dbg !1756

lor.lhs.false:                                    ; preds = %while.body
  %3 = load i8*, i8** %p.addr, align 8, !dbg !1757
  %4 = load i8, i8* %3, align 1, !dbg !1759
  %conv3 = sext i8 %4 to i32, !dbg !1759
  %cmp4 = icmp sgt i32 %conv3, 55, !dbg !1760
  br i1 %cmp4, label %if.then, label %if.end, !dbg !1761

if.then:                                          ; preds = %lor.lhs.false, %while.body
  store i32 0, i32* %retval, align 4, !dbg !1762
  br label %return, !dbg !1762

if.end:                                           ; preds = %lor.lhs.false
  %5 = load i8*, i8** %p.addr, align 8, !dbg !1763
  %incdec.ptr = getelementptr inbounds i8, i8* %5, i32 1, !dbg !1763
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1763
  br label %while.cond, !dbg !1764

while.end:                                        ; preds = %while.cond
  store i32 1, i32* %retval, align 4, !dbg !1766
  br label %return, !dbg !1766

return:                                           ; preds = %while.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !1767
  ret i32 %6, !dbg !1767
}

; Function Attrs: nounwind uwtable
define internal i32 @is_afio_large(i8* %h, i64 %len) #0 !dbg !332 {
entry:
  %retval = alloca i32, align 4
  %h.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  store i8* %h, i8** %h.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %h.addr, metadata !1768, metadata !359), !dbg !1769
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !1770, metadata !359), !dbg !1771
  %0 = load i64, i64* %len.addr, align 8, !dbg !1772
  %cmp = icmp ult i64 %0, 116, !dbg !1774
  br i1 %cmp, label %if.then, label %if.end, !dbg !1775

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1776
  br label %return, !dbg !1776

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %h.addr, align 8, !dbg !1777
  %arrayidx = getelementptr inbounds i8, i8* %1, i64 30, !dbg !1777
  %2 = load i8, i8* %arrayidx, align 1, !dbg !1777
  %conv = sext i8 %2 to i32, !dbg !1777
  %cmp1 = icmp ne i32 %conv, 109, !dbg !1779
  br i1 %cmp1, label %if.then17, label %lor.lhs.false, !dbg !1780

lor.lhs.false:                                    ; preds = %if.end
  %3 = load i8*, i8** %h.addr, align 8, !dbg !1781
  %arrayidx3 = getelementptr inbounds i8, i8* %3, i64 85, !dbg !1781
  %4 = load i8, i8* %arrayidx3, align 1, !dbg !1781
  %conv4 = sext i8 %4 to i32, !dbg !1781
  %cmp5 = icmp ne i32 %conv4, 110, !dbg !1783
  br i1 %cmp5, label %if.then17, label %lor.lhs.false7, !dbg !1784

lor.lhs.false7:                                   ; preds = %lor.lhs.false
  %5 = load i8*, i8** %h.addr, align 8, !dbg !1785
  %arrayidx8 = getelementptr inbounds i8, i8* %5, i64 98, !dbg !1785
  %6 = load i8, i8* %arrayidx8, align 1, !dbg !1785
  %conv9 = sext i8 %6 to i32, !dbg !1785
  %cmp10 = icmp ne i32 %conv9, 115, !dbg !1786
  br i1 %cmp10, label %if.then17, label %lor.lhs.false12, !dbg !1787

lor.lhs.false12:                                  ; preds = %lor.lhs.false7
  %7 = load i8*, i8** %h.addr, align 8, !dbg !1788
  %arrayidx13 = getelementptr inbounds i8, i8* %7, i64 115, !dbg !1788
  %8 = load i8, i8* %arrayidx13, align 1, !dbg !1788
  %conv14 = sext i8 %8 to i32, !dbg !1788
  %cmp15 = icmp ne i32 %conv14, 58, !dbg !1789
  br i1 %cmp15, label %if.then17, label %if.end18, !dbg !1790

if.then17:                                        ; preds = %lor.lhs.false12, %lor.lhs.false7, %lor.lhs.false, %if.end
  store i32 0, i32* %retval, align 4, !dbg !1792
  br label %return, !dbg !1792

if.end18:                                         ; preds = %lor.lhs.false12
  %9 = load i8*, i8** %h.addr, align 8, !dbg !1793
  %add.ptr = getelementptr inbounds i8, i8* %9, i64 6, !dbg !1795
  %call = call i32 @is_hex(i8* %add.ptr, i64 24), !dbg !1796
  %tobool = icmp ne i32 %call, 0, !dbg !1796
  br i1 %tobool, label %if.end20, label %if.then19, !dbg !1797

if.then19:                                        ; preds = %if.end18
  store i32 0, i32* %retval, align 4, !dbg !1798
  br label %return, !dbg !1798

if.end20:                                         ; preds = %if.end18
  %10 = load i8*, i8** %h.addr, align 8, !dbg !1799
  %add.ptr21 = getelementptr inbounds i8, i8* %10, i64 31, !dbg !1801
  %call22 = call i32 @is_hex(i8* %add.ptr21, i64 54), !dbg !1802
  %tobool23 = icmp ne i32 %call22, 0, !dbg !1802
  br i1 %tobool23, label %if.end25, label %if.then24, !dbg !1803

if.then24:                                        ; preds = %if.end20
  store i32 0, i32* %retval, align 4, !dbg !1804
  br label %return, !dbg !1804

if.end25:                                         ; preds = %if.end20
  %11 = load i8*, i8** %h.addr, align 8, !dbg !1805
  %add.ptr26 = getelementptr inbounds i8, i8* %11, i64 86, !dbg !1807
  %call27 = call i32 @is_hex(i8* %add.ptr26, i64 12), !dbg !1808
  %tobool28 = icmp ne i32 %call27, 0, !dbg !1808
  br i1 %tobool28, label %if.end30, label %if.then29, !dbg !1809

if.then29:                                        ; preds = %if.end25
  store i32 0, i32* %retval, align 4, !dbg !1810
  br label %return, !dbg !1810

if.end30:                                         ; preds = %if.end25
  %12 = load i8*, i8** %h.addr, align 8, !dbg !1811
  %add.ptr31 = getelementptr inbounds i8, i8* %12, i64 99, !dbg !1813
  %call32 = call i32 @is_hex(i8* %add.ptr31, i64 16), !dbg !1814
  %tobool33 = icmp ne i32 %call32, 0, !dbg !1814
  br i1 %tobool33, label %if.end35, label %if.then34, !dbg !1815

if.then34:                                        ; preds = %if.end30
  store i32 0, i32* %retval, align 4, !dbg !1816
  br label %return, !dbg !1816

if.end35:                                         ; preds = %if.end30
  store i32 1, i32* %retval, align 4, !dbg !1817
  br label %return, !dbg !1817

return:                                           ; preds = %if.end35, %if.then34, %if.then29, %if.then24, %if.then19, %if.then17, %if.then
  %13 = load i32, i32* %retval, align 4, !dbg !1818
  ret i32 %13, !dbg !1818
}

; Function Attrs: nounwind uwtable
define internal i32 @is_hex(i8* %p, i64 %len) #0 !dbg !333 {
entry:
  %retval = alloca i32, align 4
  %p.addr = alloca i8*, align 8
  %len.addr = alloca i64, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1819, metadata !359), !dbg !1820
  store i64 %len, i64* %len.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %len.addr, metadata !1821, metadata !359), !dbg !1822
  br label %while.cond, !dbg !1823

while.cond:                                       ; preds = %if.end, %entry
  %0 = load i64, i64* %len.addr, align 8, !dbg !1824
  %dec = add i64 %0, -1, !dbg !1824
  store i64 %dec, i64* %len.addr, align 8, !dbg !1824
  %cmp = icmp ugt i64 %0, 0, !dbg !1826
  br i1 %cmp, label %while.body, label %while.end, !dbg !1827

while.body:                                       ; preds = %while.cond
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1828
  %2 = load i8, i8* %1, align 1, !dbg !1831
  %conv = sext i8 %2 to i32, !dbg !1831
  %cmp1 = icmp sge i32 %conv, 48, !dbg !1832
  br i1 %cmp1, label %land.lhs.true, label %lor.lhs.false, !dbg !1833

land.lhs.true:                                    ; preds = %while.body
  %3 = load i8*, i8** %p.addr, align 8, !dbg !1834
  %4 = load i8, i8* %3, align 1, !dbg !1836
  %conv3 = sext i8 %4 to i32, !dbg !1836
  %cmp4 = icmp sle i32 %conv3, 57, !dbg !1837
  br i1 %cmp4, label %if.then, label %lor.lhs.false, !dbg !1838

lor.lhs.false:                                    ; preds = %land.lhs.true, %while.body
  %5 = load i8*, i8** %p.addr, align 8, !dbg !1839
  %6 = load i8, i8* %5, align 1, !dbg !1840
  %conv6 = sext i8 %6 to i32, !dbg !1840
  %cmp7 = icmp sge i32 %conv6, 97, !dbg !1841
  br i1 %cmp7, label %land.lhs.true9, label %lor.lhs.false13, !dbg !1842

land.lhs.true9:                                   ; preds = %lor.lhs.false
  %7 = load i8*, i8** %p.addr, align 8, !dbg !1843
  %8 = load i8, i8* %7, align 1, !dbg !1845
  %conv10 = sext i8 %8 to i32, !dbg !1845
  %cmp11 = icmp sle i32 %conv10, 102, !dbg !1846
  br i1 %cmp11, label %if.then, label %lor.lhs.false13, !dbg !1847

lor.lhs.false13:                                  ; preds = %land.lhs.true9, %lor.lhs.false
  %9 = load i8*, i8** %p.addr, align 8, !dbg !1848
  %10 = load i8, i8* %9, align 1, !dbg !1849
  %conv14 = sext i8 %10 to i32, !dbg !1849
  %cmp15 = icmp sge i32 %conv14, 65, !dbg !1850
  br i1 %cmp15, label %land.lhs.true17, label %if.else, !dbg !1851

land.lhs.true17:                                  ; preds = %lor.lhs.false13
  %11 = load i8*, i8** %p.addr, align 8, !dbg !1852
  %12 = load i8, i8* %11, align 1, !dbg !1853
  %conv18 = sext i8 %12 to i32, !dbg !1853
  %cmp19 = icmp sle i32 %conv18, 70, !dbg !1854
  br i1 %cmp19, label %if.then, label %if.else, !dbg !1855

if.then:                                          ; preds = %land.lhs.true17, %land.lhs.true9, %land.lhs.true
  %13 = load i8*, i8** %p.addr, align 8, !dbg !1857
  %incdec.ptr = getelementptr inbounds i8, i8* %13, i32 1, !dbg !1857
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1857
  br label %if.end, !dbg !1857

if.else:                                          ; preds = %land.lhs.true17, %lor.lhs.false13
  store i32 0, i32* %retval, align 4, !dbg !1858
  br label %return, !dbg !1858

if.end:                                           ; preds = %if.then
  br label %while.cond, !dbg !1859

while.end:                                        ; preds = %while.cond
  store i32 1, i32* %retval, align 4, !dbg !1861
  br label %return, !dbg !1861

return:                                           ; preds = %while.end, %if.else
  %14 = load i32, i32* %retval, align 4, !dbg !1862
  ret i32 %14, !dbg !1862
}

; Function Attrs: nounwind uwtable
define internal i64 @atol16(i8* %p, i32 %char_cnt) #0 !dbg !335 {
entry:
  %retval = alloca i64, align 8
  %p.addr = alloca i8*, align 8
  %char_cnt.addr = alloca i32, align 4
  %l = alloca i64, align 8
  %digit = alloca i32, align 4
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !1863, metadata !359), !dbg !1864
  store i32 %char_cnt, i32* %char_cnt.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %char_cnt.addr, metadata !1865, metadata !359), !dbg !1866
  call void @llvm.dbg.declare(metadata i64* %l, metadata !1867, metadata !359), !dbg !1868
  call void @llvm.dbg.declare(metadata i32* %digit, metadata !1869, metadata !359), !dbg !1870
  store i64 0, i64* %l, align 8, !dbg !1871
  br label %while.cond, !dbg !1872

while.cond:                                       ; preds = %if.end31, %entry
  %0 = load i32, i32* %char_cnt.addr, align 4, !dbg !1873
  %dec = add i32 %0, -1, !dbg !1873
  store i32 %dec, i32* %char_cnt.addr, align 4, !dbg !1873
  %cmp = icmp ugt i32 %0, 0, !dbg !1875
  br i1 %cmp, label %while.body, label %while.end, !dbg !1876

while.body:                                       ; preds = %while.cond
  %1 = load i8*, i8** %p.addr, align 8, !dbg !1877
  %2 = load i8, i8* %1, align 1, !dbg !1880
  %conv = sext i8 %2 to i32, !dbg !1880
  %cmp1 = icmp sge i32 %conv, 97, !dbg !1881
  br i1 %cmp1, label %land.lhs.true, label %if.else, !dbg !1882

land.lhs.true:                                    ; preds = %while.body
  %3 = load i8*, i8** %p.addr, align 8, !dbg !1883
  %4 = load i8, i8* %3, align 1, !dbg !1885
  %conv3 = sext i8 %4 to i32, !dbg !1885
  %cmp4 = icmp sle i32 %conv3, 102, !dbg !1886
  br i1 %cmp4, label %if.then, label %if.else, !dbg !1887

if.then:                                          ; preds = %land.lhs.true
  %5 = load i8*, i8** %p.addr, align 8, !dbg !1888
  %6 = load i8, i8* %5, align 1, !dbg !1889
  %conv6 = sext i8 %6 to i32, !dbg !1889
  %sub = sub nsw i32 %conv6, 97, !dbg !1890
  %add = add nsw i32 %sub, 10, !dbg !1891
  store i32 %add, i32* %digit, align 4, !dbg !1892
  br label %if.end31, !dbg !1893

if.else:                                          ; preds = %land.lhs.true, %while.body
  %7 = load i8*, i8** %p.addr, align 8, !dbg !1894
  %8 = load i8, i8* %7, align 1, !dbg !1896
  %conv7 = sext i8 %8 to i32, !dbg !1896
  %cmp8 = icmp sge i32 %conv7, 65, !dbg !1897
  br i1 %cmp8, label %land.lhs.true10, label %if.else18, !dbg !1898

land.lhs.true10:                                  ; preds = %if.else
  %9 = load i8*, i8** %p.addr, align 8, !dbg !1899
  %10 = load i8, i8* %9, align 1, !dbg !1901
  %conv11 = sext i8 %10 to i32, !dbg !1901
  %cmp12 = icmp sle i32 %conv11, 70, !dbg !1902
  br i1 %cmp12, label %if.then14, label %if.else18, !dbg !1903

if.then14:                                        ; preds = %land.lhs.true10
  %11 = load i8*, i8** %p.addr, align 8, !dbg !1904
  %12 = load i8, i8* %11, align 1, !dbg !1905
  %conv15 = sext i8 %12 to i32, !dbg !1905
  %sub16 = sub nsw i32 %conv15, 65, !dbg !1906
  %add17 = add nsw i32 %sub16, 10, !dbg !1907
  store i32 %add17, i32* %digit, align 4, !dbg !1908
  br label %if.end30, !dbg !1909

if.else18:                                        ; preds = %land.lhs.true10, %if.else
  %13 = load i8*, i8** %p.addr, align 8, !dbg !1910
  %14 = load i8, i8* %13, align 1, !dbg !1912
  %conv19 = sext i8 %14 to i32, !dbg !1912
  %cmp20 = icmp sge i32 %conv19, 48, !dbg !1913
  br i1 %cmp20, label %land.lhs.true22, label %if.else29, !dbg !1914

land.lhs.true22:                                  ; preds = %if.else18
  %15 = load i8*, i8** %p.addr, align 8, !dbg !1915
  %16 = load i8, i8* %15, align 1, !dbg !1917
  %conv23 = sext i8 %16 to i32, !dbg !1917
  %cmp24 = icmp sle i32 %conv23, 57, !dbg !1918
  br i1 %cmp24, label %if.then26, label %if.else29, !dbg !1919

if.then26:                                        ; preds = %land.lhs.true22
  %17 = load i8*, i8** %p.addr, align 8, !dbg !1920
  %18 = load i8, i8* %17, align 1, !dbg !1921
  %conv27 = sext i8 %18 to i32, !dbg !1921
  %sub28 = sub nsw i32 %conv27, 48, !dbg !1922
  store i32 %sub28, i32* %digit, align 4, !dbg !1923
  br label %if.end, !dbg !1924

if.else29:                                        ; preds = %land.lhs.true22, %if.else18
  %19 = load i64, i64* %l, align 8, !dbg !1925
  store i64 %19, i64* %retval, align 8, !dbg !1926
  br label %return, !dbg !1926

if.end:                                           ; preds = %if.then26
  br label %if.end30

if.end30:                                         ; preds = %if.end, %if.then14
  br label %if.end31

if.end31:                                         ; preds = %if.end30, %if.then
  %20 = load i8*, i8** %p.addr, align 8, !dbg !1927
  %incdec.ptr = getelementptr inbounds i8, i8* %20, i32 1, !dbg !1927
  store i8* %incdec.ptr, i8** %p.addr, align 8, !dbg !1927
  %21 = load i64, i64* %l, align 8, !dbg !1928
  %shl = shl i64 %21, 4, !dbg !1928
  store i64 %shl, i64* %l, align 8, !dbg !1928
  %22 = load i32, i32* %digit, align 4, !dbg !1929
  %conv32 = sext i32 %22 to i64, !dbg !1929
  %23 = load i64, i64* %l, align 8, !dbg !1930
  %or = or i64 %23, %conv32, !dbg !1930
  store i64 %or, i64* %l, align 8, !dbg !1930
  br label %while.cond, !dbg !1931

while.end:                                        ; preds = %while.cond
  %24 = load i64, i64* %l, align 8, !dbg !1933
  store i64 %24, i64* %retval, align 8, !dbg !1934
  br label %return, !dbg !1934

return:                                           ; preds = %while.end, %if.else29
  %25 = load i64, i64* %retval, align 8, !dbg !1935
  ret i64 %25, !dbg !1935
}

; Function Attrs: nounwind uwtable
define internal i32 @find_newc_header(%struct.archive_read* %a) #0 !dbg !340 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %h = alloca i8*, align 8
  %p = alloca i8*, align 8
  %q = alloca i8*, align 8
  %skip = alloca i64, align 8
  %skipped = alloca i64, align 8
  %bytes = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !1936, metadata !359), !dbg !1937
  call void @llvm.dbg.declare(metadata i8** %h, metadata !1938, metadata !359), !dbg !1939
  call void @llvm.dbg.declare(metadata i8** %p, metadata !1940, metadata !359), !dbg !1941
  call void @llvm.dbg.declare(metadata i8** %q, metadata !1942, metadata !359), !dbg !1943
  call void @llvm.dbg.declare(metadata i64* %skip, metadata !1944, metadata !359), !dbg !1945
  call void @llvm.dbg.declare(metadata i64* %skipped, metadata !1946, metadata !359), !dbg !1947
  store i64 0, i64* %skipped, align 8, !dbg !1947
  call void @llvm.dbg.declare(metadata i64* %bytes, metadata !1948, metadata !359), !dbg !1949
  br label %for.cond, !dbg !1950

for.cond:                                         ; preds = %while.end, %entry
  %0 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !1951
  %call = call i8* @__archive_read_ahead(%struct.archive_read* %0, i64 110, i64* %bytes), !dbg !1955
  store i8* %call, i8** %h, align 8, !dbg !1956
  %1 = load i8*, i8** %h, align 8, !dbg !1957
  %cmp = icmp eq i8* %1, null, !dbg !1959
  br i1 %cmp, label %if.then, label %if.end, !dbg !1960

if.then:                                          ; preds = %for.cond
  store i32 -30, i32* %retval, align 4, !dbg !1961
  br label %return, !dbg !1961

if.end:                                           ; preds = %for.cond
  %2 = load i8*, i8** %h, align 8, !dbg !1962
  store i8* %2, i8** %p, align 8, !dbg !1963
  %3 = load i8*, i8** %p, align 8, !dbg !1964
  %4 = load i64, i64* %bytes, align 8, !dbg !1965
  %add.ptr = getelementptr inbounds i8, i8* %3, i64 %4, !dbg !1966
  store i8* %add.ptr, i8** %q, align 8, !dbg !1967
  %5 = load i8*, i8** %p, align 8, !dbg !1968
  %call1 = call i32 @memcmp(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.12, i32 0, i32 0), i8* %5, i64 5) #7, !dbg !1970
  %cmp2 = icmp eq i32 %call1, 0, !dbg !1971
  br i1 %cmp2, label %land.lhs.true, label %if.end12, !dbg !1972

land.lhs.true:                                    ; preds = %if.end
  %6 = load i8*, i8** %p, align 8, !dbg !1973
  %arrayidx = getelementptr inbounds i8, i8* %6, i64 5, !dbg !1973
  %7 = load i8, i8* %arrayidx, align 1, !dbg !1973
  %conv = sext i8 %7 to i32, !dbg !1973
  %cmp3 = icmp eq i32 %conv, 49, !dbg !1975
  br i1 %cmp3, label %land.lhs.true9, label %lor.lhs.false, !dbg !1976

lor.lhs.false:                                    ; preds = %land.lhs.true
  %8 = load i8*, i8** %p, align 8, !dbg !1977
  %arrayidx5 = getelementptr inbounds i8, i8* %8, i64 5, !dbg !1977
  %9 = load i8, i8* %arrayidx5, align 1, !dbg !1977
  %conv6 = sext i8 %9 to i32, !dbg !1977
  %cmp7 = icmp eq i32 %conv6, 50, !dbg !1979
  br i1 %cmp7, label %land.lhs.true9, label %if.end12, !dbg !1980

land.lhs.true9:                                   ; preds = %lor.lhs.false, %land.lhs.true
  %10 = load i8*, i8** %p, align 8, !dbg !1981
  %call10 = call i32 @is_hex(i8* %10, i64 110), !dbg !1982
  %tobool = icmp ne i32 %call10, 0, !dbg !1982
  br i1 %tobool, label %if.then11, label %if.end12, !dbg !1983

if.then11:                                        ; preds = %land.lhs.true9
  store i32 0, i32* %retval, align 4, !dbg !1985
  br label %return, !dbg !1985

if.end12:                                         ; preds = %land.lhs.true9, %lor.lhs.false, %if.end
  br label %while.cond, !dbg !1986

while.cond:                                       ; preds = %sw.epilog, %if.end12
  %11 = load i8*, i8** %p, align 8, !dbg !1987
  %add.ptr13 = getelementptr inbounds i8, i8* %11, i64 110, !dbg !1988
  %12 = load i8*, i8** %q, align 8, !dbg !1989
  %cmp14 = icmp ule i8* %add.ptr13, %12, !dbg !1990
  br i1 %cmp14, label %while.body, label %while.end, !dbg !1991

while.body:                                       ; preds = %while.cond
  %13 = load i8*, i8** %p, align 8, !dbg !1992
  %arrayidx16 = getelementptr inbounds i8, i8* %13, i64 5, !dbg !1992
  %14 = load i8, i8* %arrayidx16, align 1, !dbg !1992
  %conv17 = sext i8 %14 to i32, !dbg !1992
  switch i32 %conv17, label %sw.default [
    i32 49, label %sw.bb
    i32 50, label %sw.bb
    i32 48, label %sw.bb33
  ], !dbg !1994

sw.bb:                                            ; preds = %while.body, %while.body
  %15 = load i8*, i8** %p, align 8, !dbg !1995
  %call18 = call i32 @memcmp(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.12, i32 0, i32 0), i8* %15, i64 5) #7, !dbg !1998
  %cmp19 = icmp eq i32 %call18, 0, !dbg !1999
  br i1 %cmp19, label %land.lhs.true21, label %if.end31, !dbg !2000

land.lhs.true21:                                  ; preds = %sw.bb
  %16 = load i8*, i8** %p, align 8, !dbg !2001
  %call22 = call i32 @is_hex(i8* %16, i64 110), !dbg !2003
  %tobool23 = icmp ne i32 %call22, 0, !dbg !2003
  br i1 %tobool23, label %if.then24, label %if.end31, !dbg !2004

if.then24:                                        ; preds = %land.lhs.true21
  %17 = load i8*, i8** %p, align 8, !dbg !2006
  %18 = load i8*, i8** %h, align 8, !dbg !2008
  %sub.ptr.lhs.cast = ptrtoint i8* %17 to i64, !dbg !2009
  %sub.ptr.rhs.cast = ptrtoint i8* %18 to i64, !dbg !2009
  %sub.ptr.sub = sub i64 %sub.ptr.lhs.cast, %sub.ptr.rhs.cast, !dbg !2009
  store i64 %sub.ptr.sub, i64* %skip, align 8, !dbg !2010
  %19 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2011
  %20 = load i64, i64* %skip, align 8, !dbg !2012
  %call25 = call i64 @__archive_read_consume(%struct.archive_read* %19, i64 %20), !dbg !2013
  %21 = load i64, i64* %skip, align 8, !dbg !2014
  %22 = load i64, i64* %skipped, align 8, !dbg !2015
  %add = add i64 %22, %21, !dbg !2015
  store i64 %add, i64* %skipped, align 8, !dbg !2015
  %23 = load i64, i64* %skipped, align 8, !dbg !2016
  %cmp26 = icmp ugt i64 %23, 0, !dbg !2018
  br i1 %cmp26, label %if.then28, label %if.end30, !dbg !2019

if.then28:                                        ; preds = %if.then24
  %24 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2020
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %24, i32 0, i32 0, !dbg !2022
  %25 = load i64, i64* %skipped, align 8, !dbg !2023
  %conv29 = trunc i64 %25 to i32, !dbg !2024
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 0, i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.8, i32 0, i32 0), i32 %conv29), !dbg !2025
  store i32 -20, i32* %retval, align 4, !dbg !2026
  br label %return, !dbg !2026

if.end30:                                         ; preds = %if.then24
  store i32 0, i32* %retval, align 4, !dbg !2027
  br label %return, !dbg !2027

if.end31:                                         ; preds = %land.lhs.true21, %sw.bb
  %26 = load i8*, i8** %p, align 8, !dbg !2028
  %add.ptr32 = getelementptr inbounds i8, i8* %26, i64 2, !dbg !2028
  store i8* %add.ptr32, i8** %p, align 8, !dbg !2028
  br label %sw.epilog, !dbg !2029

sw.bb33:                                          ; preds = %while.body
  %27 = load i8*, i8** %p, align 8, !dbg !2030
  %incdec.ptr = getelementptr inbounds i8, i8* %27, i32 1, !dbg !2030
  store i8* %incdec.ptr, i8** %p, align 8, !dbg !2030
  br label %sw.epilog, !dbg !2031

sw.default:                                       ; preds = %while.body
  %28 = load i8*, i8** %p, align 8, !dbg !2032
  %add.ptr34 = getelementptr inbounds i8, i8* %28, i64 6, !dbg !2032
  store i8* %add.ptr34, i8** %p, align 8, !dbg !2032
  br label %sw.epilog, !dbg !2033

sw.epilog:                                        ; preds = %sw.default, %sw.bb33, %if.end31
  br label %while.cond, !dbg !2034

while.end:                                        ; preds = %while.cond
  %29 = load i8*, i8** %p, align 8, !dbg !2036
  %30 = load i8*, i8** %h, align 8, !dbg !2037
  %sub.ptr.lhs.cast35 = ptrtoint i8* %29 to i64, !dbg !2038
  %sub.ptr.rhs.cast36 = ptrtoint i8* %30 to i64, !dbg !2038
  %sub.ptr.sub37 = sub i64 %sub.ptr.lhs.cast35, %sub.ptr.rhs.cast36, !dbg !2038
  store i64 %sub.ptr.sub37, i64* %skip, align 8, !dbg !2039
  %31 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2040
  %32 = load i64, i64* %skip, align 8, !dbg !2041
  %call38 = call i64 @__archive_read_consume(%struct.archive_read* %31, i64 %32), !dbg !2042
  %33 = load i64, i64* %skip, align 8, !dbg !2043
  %34 = load i64, i64* %skipped, align 8, !dbg !2044
  %add39 = add i64 %34, %33, !dbg !2044
  store i64 %add39, i64* %skipped, align 8, !dbg !2044
  br label %for.cond, !dbg !2045

return:                                           ; preds = %if.end30, %if.then28, %if.then11, %if.then
  %35 = load i32, i32* %retval, align 4, !dbg !2047
  ret i32 %35, !dbg !2047
}

declare void @archive_entry_set_devmajor(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_devminor(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_rdevmajor(%struct.archive_entry*, i64) #2

declare void @archive_entry_set_rdevminor(%struct.archive_entry*, i64) #2

; Function Attrs: nounwind uwtable
define internal i64 @be4(i8* %p) #0 !dbg !342 {
entry:
  %p.addr = alloca i8*, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !2048, metadata !359), !dbg !2049
  %0 = load i8*, i8** %p.addr, align 8, !dbg !2050
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !2050
  %1 = load i8, i8* %arrayidx, align 1, !dbg !2050
  %conv = zext i8 %1 to i64, !dbg !2051
  %shl = shl i64 %conv, 24, !dbg !2052
  %2 = load i8*, i8** %p.addr, align 8, !dbg !2053
  %arrayidx1 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !2053
  %3 = load i8, i8* %arrayidx1, align 1, !dbg !2053
  %conv2 = zext i8 %3 to i32, !dbg !2053
  %shl3 = shl i32 %conv2, 16, !dbg !2054
  %conv4 = sext i32 %shl3 to i64, !dbg !2055
  %add = add nsw i64 %shl, %conv4, !dbg !2056
  %4 = load i8*, i8** %p.addr, align 8, !dbg !2057
  %arrayidx5 = getelementptr inbounds i8, i8* %4, i64 2, !dbg !2057
  %5 = load i8, i8* %arrayidx5, align 1, !dbg !2057
  %conv6 = zext i8 %5 to i32, !dbg !2057
  %shl7 = shl i32 %conv6, 8, !dbg !2058
  %conv8 = sext i32 %shl7 to i64, !dbg !2059
  %add9 = add nsw i64 %add, %conv8, !dbg !2060
  %6 = load i8*, i8** %p.addr, align 8, !dbg !2061
  %arrayidx10 = getelementptr inbounds i8, i8* %6, i64 3, !dbg !2061
  %7 = load i8, i8* %arrayidx10, align 1, !dbg !2061
  %conv11 = zext i8 %7 to i64, !dbg !2062
  %add12 = add nsw i64 %add9, %conv11, !dbg !2063
  ret i64 %add12, !dbg !2064
}

; Function Attrs: nounwind uwtable
define internal i64 @le4(i8* %p) #0 !dbg !346 {
entry:
  %p.addr = alloca i8*, align 8
  store i8* %p, i8** %p.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %p.addr, metadata !2065, metadata !359), !dbg !2066
  %0 = load i8*, i8** %p.addr, align 8, !dbg !2067
  %arrayidx = getelementptr inbounds i8, i8* %0, i64 0, !dbg !2067
  %1 = load i8, i8* %arrayidx, align 1, !dbg !2067
  %conv = zext i8 %1 to i32, !dbg !2067
  %shl = shl i32 %conv, 16, !dbg !2068
  %conv1 = sext i32 %shl to i64, !dbg !2069
  %2 = load i8*, i8** %p.addr, align 8, !dbg !2070
  %arrayidx2 = getelementptr inbounds i8, i8* %2, i64 1, !dbg !2070
  %3 = load i8, i8* %arrayidx2, align 1, !dbg !2070
  %conv3 = zext i8 %3 to i64, !dbg !2071
  %shl4 = shl i64 %conv3, 24, !dbg !2072
  %add = add nsw i64 %conv1, %shl4, !dbg !2073
  %4 = load i8*, i8** %p.addr, align 8, !dbg !2074
  %arrayidx5 = getelementptr inbounds i8, i8* %4, i64 2, !dbg !2074
  %5 = load i8, i8* %arrayidx5, align 1, !dbg !2074
  %conv6 = zext i8 %5 to i32, !dbg !2074
  %shl7 = shl i32 %conv6, 0, !dbg !2075
  %conv8 = sext i32 %shl7 to i64, !dbg !2076
  %add9 = add nsw i64 %add, %conv8, !dbg !2077
  %6 = load i8*, i8** %p.addr, align 8, !dbg !2078
  %arrayidx10 = getelementptr inbounds i8, i8* %6, i64 3, !dbg !2078
  %7 = load i8, i8* %arrayidx10, align 1, !dbg !2078
  %conv11 = zext i8 %7 to i32, !dbg !2078
  %shl12 = shl i32 %conv11, 8, !dbg !2079
  %conv13 = sext i32 %shl12 to i64, !dbg !2080
  %add14 = add nsw i64 %add9, %conv13, !dbg !2081
  ret i64 %add14, !dbg !2082
}

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string_conv* @archive_string_conversion_from_charset(%struct.archive*, i8*, i32) #2

declare %struct.archive_string_conv* @archive_string_default_conversion_for_read(%struct.archive*) #2

declare i32 @_archive_entry_copy_pathname_l(%struct.archive_entry*, i8*, i64, %struct.archive_string_conv*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare i8* @archive_string_conversion_charset_name(%struct.archive_string_conv*) #2

declare i32 @archive_entry_filetype(%struct.archive_entry*) #2

declare i32 @_archive_entry_copy_symlink_l(%struct.archive_entry*, i8*, i64, %struct.archive_string_conv*) #2

; Function Attrs: nounwind readonly
declare i32 @strncmp(i8*, i8*, i64) #4

declare void @archive_clear_error(%struct.archive*) #2

; Function Attrs: nounwind uwtable
define internal i32 @record_hardlink(%struct.archive_read* %a, %struct.cpio* %cpio, %struct.archive_entry* %entry1) #0 !dbg !349 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive_read*, align 8
  %cpio.addr = alloca %struct.cpio*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  %le = alloca %struct.links_entry*, align 8
  %dev = alloca i64, align 8
  %ino = alloca i64, align 8
  store %struct.archive_read* %a, %struct.archive_read** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_read** %a.addr, metadata !2083, metadata !359), !dbg !2084
  store %struct.cpio* %cpio, %struct.cpio** %cpio.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.cpio** %cpio.addr, metadata !2085, metadata !359), !dbg !2086
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !2087, metadata !359), !dbg !2088
  call void @llvm.dbg.declare(metadata %struct.links_entry** %le, metadata !2089, metadata !359), !dbg !2090
  call void @llvm.dbg.declare(metadata i64* %dev, metadata !2091, metadata !359), !dbg !2092
  call void @llvm.dbg.declare(metadata i64* %ino, metadata !2093, metadata !359), !dbg !2094
  %0 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2095
  %call = call i32 @archive_entry_nlink(%struct.archive_entry* %0), !dbg !2097
  %cmp = icmp ule i32 %call, 1, !dbg !2098
  br i1 %cmp, label %if.then, label %if.end, !dbg !2099

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !2100
  br label %return, !dbg !2100

if.end:                                           ; preds = %entry
  %1 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2101
  %call2 = call i64 @archive_entry_dev(%struct.archive_entry* %1), !dbg !2102
  store i64 %call2, i64* %dev, align 8, !dbg !2103
  %2 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2104
  %call3 = call i64 @archive_entry_ino64(%struct.archive_entry* %2), !dbg !2105
  store i64 %call3, i64* %ino, align 8, !dbg !2106
  %3 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !2107
  %links_head = getelementptr inbounds %struct.cpio, %struct.cpio* %3, i32 0, i32 2, !dbg !2109
  %4 = load %struct.links_entry*, %struct.links_entry** %links_head, align 8, !dbg !2109
  store %struct.links_entry* %4, %struct.links_entry** %le, align 8, !dbg !2110
  br label %for.cond, !dbg !2111

for.cond:                                         ; preds = %for.inc, %if.end
  %5 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2112
  %tobool = icmp ne %struct.links_entry* %5, null, !dbg !2115
  br i1 %tobool, label %for.body, label %for.end, !dbg !2115

for.body:                                         ; preds = %for.cond
  %6 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2116
  %dev4 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %6, i32 0, i32 3, !dbg !2119
  %7 = load i64, i64* %dev4, align 8, !dbg !2119
  %8 = load i64, i64* %dev, align 8, !dbg !2120
  %cmp5 = icmp eq i64 %7, %8, !dbg !2121
  br i1 %cmp5, label %land.lhs.true, label %if.end31, !dbg !2122

land.lhs.true:                                    ; preds = %for.body
  %9 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2123
  %ino6 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %9, i32 0, i32 4, !dbg !2125
  %10 = load i64, i64* %ino6, align 8, !dbg !2125
  %11 = load i64, i64* %ino, align 8, !dbg !2126
  %cmp7 = icmp eq i64 %10, %11, !dbg !2127
  br i1 %cmp7, label %if.then8, label %if.end31, !dbg !2128

if.then8:                                         ; preds = %land.lhs.true
  %12 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2129
  %13 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2131
  %name = getelementptr inbounds %struct.links_entry, %struct.links_entry* %13, i32 0, i32 5, !dbg !2132
  %14 = load i8*, i8** %name, align 8, !dbg !2132
  call void @archive_entry_copy_hardlink(%struct.archive_entry* %12, i8* %14), !dbg !2133
  %15 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2134
  %links = getelementptr inbounds %struct.links_entry, %struct.links_entry* %15, i32 0, i32 2, !dbg !2136
  %16 = load i32, i32* %links, align 8, !dbg !2137
  %dec = add nsw i32 %16, -1, !dbg !2137
  store i32 %dec, i32* %links, align 8, !dbg !2137
  %cmp9 = icmp sle i32 %dec, 0, !dbg !2138
  br i1 %cmp9, label %if.then10, label %if.end30, !dbg !2139

if.then10:                                        ; preds = %if.then8
  %17 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2140
  %previous = getelementptr inbounds %struct.links_entry, %struct.links_entry* %17, i32 0, i32 1, !dbg !2143
  %18 = load %struct.links_entry*, %struct.links_entry** %previous, align 8, !dbg !2143
  %cmp11 = icmp ne %struct.links_entry* %18, null, !dbg !2144
  br i1 %cmp11, label %if.then12, label %if.end15, !dbg !2145

if.then12:                                        ; preds = %if.then10
  %19 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2146
  %next = getelementptr inbounds %struct.links_entry, %struct.links_entry* %19, i32 0, i32 0, !dbg !2147
  %20 = load %struct.links_entry*, %struct.links_entry** %next, align 8, !dbg !2147
  %21 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2148
  %previous13 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %21, i32 0, i32 1, !dbg !2149
  %22 = load %struct.links_entry*, %struct.links_entry** %previous13, align 8, !dbg !2149
  %next14 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %22, i32 0, i32 0, !dbg !2150
  store %struct.links_entry* %20, %struct.links_entry** %next14, align 8, !dbg !2151
  br label %if.end15, !dbg !2148

if.end15:                                         ; preds = %if.then12, %if.then10
  %23 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2152
  %next16 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %23, i32 0, i32 0, !dbg !2154
  %24 = load %struct.links_entry*, %struct.links_entry** %next16, align 8, !dbg !2154
  %cmp17 = icmp ne %struct.links_entry* %24, null, !dbg !2155
  br i1 %cmp17, label %if.then18, label %if.end22, !dbg !2156

if.then18:                                        ; preds = %if.end15
  %25 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2157
  %previous19 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %25, i32 0, i32 1, !dbg !2158
  %26 = load %struct.links_entry*, %struct.links_entry** %previous19, align 8, !dbg !2158
  %27 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2159
  %next20 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %27, i32 0, i32 0, !dbg !2160
  %28 = load %struct.links_entry*, %struct.links_entry** %next20, align 8, !dbg !2160
  %previous21 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %28, i32 0, i32 1, !dbg !2161
  store %struct.links_entry* %26, %struct.links_entry** %previous21, align 8, !dbg !2162
  br label %if.end22, !dbg !2159

if.end22:                                         ; preds = %if.then18, %if.end15
  %29 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !2163
  %links_head23 = getelementptr inbounds %struct.cpio, %struct.cpio* %29, i32 0, i32 2, !dbg !2165
  %30 = load %struct.links_entry*, %struct.links_entry** %links_head23, align 8, !dbg !2165
  %31 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2166
  %cmp24 = icmp eq %struct.links_entry* %30, %31, !dbg !2167
  br i1 %cmp24, label %if.then25, label %if.end28, !dbg !2168

if.then25:                                        ; preds = %if.end22
  %32 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2169
  %next26 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %32, i32 0, i32 0, !dbg !2170
  %33 = load %struct.links_entry*, %struct.links_entry** %next26, align 8, !dbg !2170
  %34 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !2171
  %links_head27 = getelementptr inbounds %struct.cpio, %struct.cpio* %34, i32 0, i32 2, !dbg !2172
  store %struct.links_entry* %33, %struct.links_entry** %links_head27, align 8, !dbg !2173
  br label %if.end28, !dbg !2171

if.end28:                                         ; preds = %if.then25, %if.end22
  %35 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2174
  %name29 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %35, i32 0, i32 5, !dbg !2175
  %36 = load i8*, i8** %name29, align 8, !dbg !2175
  call void @free(i8* %36) #6, !dbg !2176
  %37 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2177
  %38 = bitcast %struct.links_entry* %37 to i8*, !dbg !2177
  call void @free(i8* %38) #6, !dbg !2178
  br label %if.end30, !dbg !2179

if.end30:                                         ; preds = %if.end28, %if.then8
  store i32 0, i32* %retval, align 4, !dbg !2180
  br label %return, !dbg !2180

if.end31:                                         ; preds = %land.lhs.true, %for.body
  br label %for.inc, !dbg !2181

for.inc:                                          ; preds = %if.end31
  %39 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2182
  %next32 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %39, i32 0, i32 0, !dbg !2184
  %40 = load %struct.links_entry*, %struct.links_entry** %next32, align 8, !dbg !2184
  store %struct.links_entry* %40, %struct.links_entry** %le, align 8, !dbg !2185
  br label %for.cond, !dbg !2186

for.end:                                          ; preds = %for.cond
  %call33 = call noalias i8* @malloc(i64 48) #6, !dbg !2187
  %41 = bitcast i8* %call33 to %struct.links_entry*, !dbg !2188
  store %struct.links_entry* %41, %struct.links_entry** %le, align 8, !dbg !2189
  %42 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2190
  %cmp34 = icmp eq %struct.links_entry* %42, null, !dbg !2192
  br i1 %cmp34, label %if.then35, label %if.end36, !dbg !2193

if.then35:                                        ; preds = %for.end
  %43 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2194
  %archive = getelementptr inbounds %struct.archive_read, %struct.archive_read* %43, i32 0, i32 0, !dbg !2196
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive, i32 12, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.25, i32 0, i32 0)), !dbg !2197
  store i32 -30, i32* %retval, align 4, !dbg !2198
  br label %return, !dbg !2198

if.end36:                                         ; preds = %for.end
  %44 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !2199
  %links_head37 = getelementptr inbounds %struct.cpio, %struct.cpio* %44, i32 0, i32 2, !dbg !2201
  %45 = load %struct.links_entry*, %struct.links_entry** %links_head37, align 8, !dbg !2201
  %cmp38 = icmp ne %struct.links_entry* %45, null, !dbg !2202
  br i1 %cmp38, label %if.then39, label %if.end42, !dbg !2203

if.then39:                                        ; preds = %if.end36
  %46 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2204
  %47 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !2205
  %links_head40 = getelementptr inbounds %struct.cpio, %struct.cpio* %47, i32 0, i32 2, !dbg !2206
  %48 = load %struct.links_entry*, %struct.links_entry** %links_head40, align 8, !dbg !2206
  %previous41 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %48, i32 0, i32 1, !dbg !2207
  store %struct.links_entry* %46, %struct.links_entry** %previous41, align 8, !dbg !2208
  br label %if.end42, !dbg !2205

if.end42:                                         ; preds = %if.then39, %if.end36
  %49 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !2209
  %links_head43 = getelementptr inbounds %struct.cpio, %struct.cpio* %49, i32 0, i32 2, !dbg !2210
  %50 = load %struct.links_entry*, %struct.links_entry** %links_head43, align 8, !dbg !2210
  %51 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2211
  %next44 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %51, i32 0, i32 0, !dbg !2212
  store %struct.links_entry* %50, %struct.links_entry** %next44, align 8, !dbg !2213
  %52 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2214
  %previous45 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %52, i32 0, i32 1, !dbg !2215
  store %struct.links_entry* null, %struct.links_entry** %previous45, align 8, !dbg !2216
  %53 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2217
  %54 = load %struct.cpio*, %struct.cpio** %cpio.addr, align 8, !dbg !2218
  %links_head46 = getelementptr inbounds %struct.cpio, %struct.cpio* %54, i32 0, i32 2, !dbg !2219
  store %struct.links_entry* %53, %struct.links_entry** %links_head46, align 8, !dbg !2220
  %55 = load i64, i64* %dev, align 8, !dbg !2221
  %56 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2222
  %dev47 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %56, i32 0, i32 3, !dbg !2223
  store i64 %55, i64* %dev47, align 8, !dbg !2224
  %57 = load i64, i64* %ino, align 8, !dbg !2225
  %58 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2226
  %ino48 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %58, i32 0, i32 4, !dbg !2227
  store i64 %57, i64* %ino48, align 8, !dbg !2228
  %59 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2229
  %call49 = call i32 @archive_entry_nlink(%struct.archive_entry* %59), !dbg !2230
  %sub = sub i32 %call49, 1, !dbg !2231
  %60 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2232
  %links50 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %60, i32 0, i32 2, !dbg !2233
  store i32 %sub, i32* %links50, align 8, !dbg !2234
  %61 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !2235
  %call51 = call i8* @archive_entry_pathname(%struct.archive_entry* %61), !dbg !2236
  %call52 = call noalias i8* @strdup(i8* %call51) #6, !dbg !2237
  %62 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2239
  %name53 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %62, i32 0, i32 5, !dbg !2240
  store i8* %call52, i8** %name53, align 8, !dbg !2241
  %63 = load %struct.links_entry*, %struct.links_entry** %le, align 8, !dbg !2242
  %name54 = getelementptr inbounds %struct.links_entry, %struct.links_entry* %63, i32 0, i32 5, !dbg !2244
  %64 = load i8*, i8** %name54, align 8, !dbg !2244
  %cmp55 = icmp eq i8* %64, null, !dbg !2245
  br i1 %cmp55, label %if.then56, label %if.end58, !dbg !2246

if.then56:                                        ; preds = %if.end42
  %65 = load %struct.archive_read*, %struct.archive_read** %a.addr, align 8, !dbg !2247
  %archive57 = getelementptr inbounds %struct.archive_read, %struct.archive_read* %65, i32 0, i32 0, !dbg !2249
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %archive57, i32 12, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.25, i32 0, i32 0)), !dbg !2250
  store i32 -30, i32* %retval, align 4, !dbg !2251
  br label %return, !dbg !2251

if.end58:                                         ; preds = %if.end42
  store i32 0, i32* %retval, align 4, !dbg !2252
  br label %return, !dbg !2252

return:                                           ; preds = %if.end58, %if.then56, %if.then35, %if.end30, %if.then
  %66 = load i32, i32* %retval, align 4, !dbg !2253
  ret i32 %66, !dbg !2253
}

declare i32 @archive_entry_nlink(%struct.archive_entry*) #2

declare i64 @archive_entry_dev(%struct.archive_entry*) #2

declare i64 @archive_entry_ino64(%struct.archive_entry*) #2

declare void @archive_entry_copy_hardlink(%struct.archive_entry*, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #3

; Function Attrs: nounwind
declare noalias i8* @strdup(i8*) #3

declare i8* @archive_entry_pathname(%struct.archive_entry*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!355, !356}
!llvm.ident = !{!357}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !324)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_support_format_cpio.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !292, !123, !80, !308, !319, !13, !45, !23, !321, !52, !301, !38}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !5, size: 64, align: 64)
!5 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read", file: !6, line: 159, size: 20288, align: 64, elements: !7)
!6 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_read_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!7 = !{!8, !111, !112, !113, !114, !115, !159, !223, !224, !225, !226, !227, !228, !261, !263, !273, !274}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !5, file: !6, line: 160, baseType: !9, size: 1280, align: 64)
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
!111 = !DIDerivedType(tag: DW_TAG_member, name: "entry", scope: !5, file: !6, line: 162, baseType: !30, size: 64, align: 64, offset: 1280)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_set", scope: !5, file: !6, line: 165, baseType: !23, size: 32, align: 32, offset: 1344)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_dev", scope: !5, file: !6, line: 166, baseType: !52, size: 64, align: 64, offset: 1408)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "skip_file_ino", scope: !5, file: !6, line: 167, baseType: !52, size: 64, align: 64, offset: 1472)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "client", scope: !5, file: !6, line: 170, baseType: !116, size: 576, align: 64, offset: 1536)
!116 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_client", file: !6, line: 134, size: 576, align: 64, elements: !117)
!117 = !{!118, !124, !130, !136, !141, !144, !149, !150, !151, !152}
!118 = !DIDerivedType(tag: DW_TAG_member, name: "opener", scope: !116, file: !6, line: 135, baseType: !119, size: 64, align: 64)
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_open_callback", file: !32, line: 241, baseType: !121)
!121 = !DISubroutineType(types: !122)
!122 = !{!23, !24, !123}
!123 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "reader", scope: !116, file: !6, line: 136, baseType: !125, size: 64, align: 64, offset: 64)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !126, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_read_callback", file: !32, line: 218, baseType: !127)
!127 = !DISubroutineType(types: !128)
!128 = !{!129, !24, !123, !64}
!129 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!130 = !DIDerivedType(tag: DW_TAG_member, name: "skipper", scope: !116, file: !6, line: 137, baseType: !131, size: 64, align: 64, offset: 128)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_skip_callback", file: !32, line: 226, baseType: !133)
!133 = !DISubroutineType(types: !134)
!134 = !{!135, !24, !123, !135}
!135 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !32, line: 73, baseType: !52)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "seeker", scope: !116, file: !6, line: 138, baseType: !137, size: 64, align: 64, offset: 192)
!137 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !138, size: 64, align: 64)
!138 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_seek_callback", file: !32, line: 233, baseType: !139)
!139 = !DISubroutineType(types: !140)
!140 = !{!135, !24, !123, !135, !23}
!141 = !DIDerivedType(tag: DW_TAG_member, name: "closer", scope: !116, file: !6, line: 139, baseType: !142, size: 64, align: 64, offset: 256)
!142 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !143, size: 64, align: 64)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_close_callback", file: !32, line: 243, baseType: !121)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "switcher", scope: !116, file: !6, line: 140, baseType: !145, size: 64, align: 64, offset: 320)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !146, size: 64, align: 64)
!146 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_switch_callback", file: !32, line: 249, baseType: !147)
!147 = !DISubroutineType(types: !148)
!148 = !{!23, !24, !123, !123}
!149 = !DIDerivedType(tag: DW_TAG_member, name: "nodes", scope: !116, file: !6, line: 141, baseType: !13, size: 32, align: 32, offset: 384)
!150 = !DIDerivedType(tag: DW_TAG_member, name: "cursor", scope: !116, file: !6, line: 142, baseType: !13, size: 32, align: 32, offset: 416)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !116, file: !6, line: 143, baseType: !52, size: 64, align: 64, offset: 448)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "dataset", scope: !116, file: !6, line: 144, baseType: !153, size: 64, align: 64, offset: 512)
!153 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !154, size: 64, align: 64)
!154 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_data_node", file: !6, line: 129, size: 192, align: 64, elements: !155)
!155 = !{!156, !157, !158}
!156 = !DIDerivedType(tag: DW_TAG_member, name: "begin_position", scope: !154, file: !6, line: 130, baseType: !52, size: 64, align: 64)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "total_size", scope: !154, file: !6, line: 131, baseType: !52, size: 64, align: 64, offset: 64)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !154, file: !6, line: 132, baseType: !123, size: 64, align: 64, offset: 128)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "bidders", scope: !5, file: !6, line: 173, baseType: !160, size: 6144, align: 64, offset: 2112)
!160 = !DICompositeType(tag: DW_TAG_array_type, baseType: !161, size: 6144, align: 64, elements: !221)
!161 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter_bidder", file: !6, line: 60, size: 384, align: 64, elements: !162)
!162 = !{!163, !164, !165, !212, !213, !217}
!163 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !161, file: !6, line: 62, baseType: !123, size: 64, align: 64)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !161, file: !6, line: 64, baseType: !80, size: 64, align: 64, offset: 64)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !161, file: !6, line: 66, baseType: !166, size: 64, align: 64, offset: 128)
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!167 = !DISubroutineType(types: !168)
!168 = !{!23, !169, !170}
!169 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !161, size: 64, align: 64)
!170 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !171, size: 64, align: 64)
!171 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_filter", file: !6, line: 82, size: 1408, align: 64, elements: !172)
!172 = !{!173, !174, !175, !176, !177, !181, !185, !189, !193, !194, !198, !199, !200, !201, !202, !203, !204, !205, !206, !207, !208, !209, !210, !211}
!173 = !DIDerivedType(tag: DW_TAG_member, name: "position", scope: !171, file: !6, line: 83, baseType: !52, size: 64, align: 64)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "bidder", scope: !171, file: !6, line: 86, baseType: !169, size: 64, align: 64, offset: 64)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "upstream", scope: !171, file: !6, line: 87, baseType: !170, size: 64, align: 64, offset: 128)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !171, file: !6, line: 88, baseType: !4, size: 64, align: 64, offset: 192)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !171, file: !6, line: 90, baseType: !178, size: 64, align: 64, offset: 256)
!178 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !179, size: 64, align: 64)
!179 = !DISubroutineType(types: !180)
!180 = !{!23, !170}
!181 = !DIDerivedType(tag: DW_TAG_member, name: "read", scope: !171, file: !6, line: 92, baseType: !182, size: 64, align: 64, offset: 320)
!182 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !183, size: 64, align: 64)
!183 = !DISubroutineType(types: !184)
!184 = !{!38, !170, !64}
!185 = !DIDerivedType(tag: DW_TAG_member, name: "skip", scope: !171, file: !6, line: 94, baseType: !186, size: 64, align: 64, offset: 384)
!186 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !187, size: 64, align: 64)
!187 = !DISubroutineType(types: !188)
!188 = !{!52, !170, !52}
!189 = !DIDerivedType(tag: DW_TAG_member, name: "seek", scope: !171, file: !6, line: 96, baseType: !190, size: 64, align: 64, offset: 448)
!190 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !191, size: 64, align: 64)
!191 = !DISubroutineType(types: !192)
!192 = !{!52, !170, !52, !23}
!193 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !171, file: !6, line: 98, baseType: !178, size: 64, align: 64, offset: 512)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "sswitch", scope: !171, file: !6, line: 100, baseType: !195, size: 64, align: 64, offset: 576)
!195 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !196, size: 64, align: 64)
!196 = !DISubroutineType(types: !197)
!197 = !{!23, !170, !13}
!198 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !171, file: !6, line: 102, baseType: !123, size: 64, align: 64, offset: 640)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !171, file: !6, line: 104, baseType: !80, size: 64, align: 64, offset: 704)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !171, file: !6, line: 105, baseType: !23, size: 32, align: 32, offset: 768)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "buffer", scope: !171, file: !6, line: 108, baseType: !95, size: 64, align: 64, offset: 832)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_size", scope: !171, file: !6, line: 109, baseType: !45, size: 64, align: 64, offset: 896)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !171, file: !6, line: 110, baseType: !95, size: 64, align: 64, offset: 960)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "avail", scope: !171, file: !6, line: 111, baseType: !45, size: 64, align: 64, offset: 1024)
!205 = !DIDerivedType(tag: DW_TAG_member, name: "client_buff", scope: !171, file: !6, line: 112, baseType: !43, size: 64, align: 64, offset: 1088)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "client_total", scope: !171, file: !6, line: 113, baseType: !45, size: 64, align: 64, offset: 1152)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "client_next", scope: !171, file: !6, line: 114, baseType: !80, size: 64, align: 64, offset: 1216)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "client_avail", scope: !171, file: !6, line: 115, baseType: !45, size: 64, align: 64, offset: 1280)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "end_of_file", scope: !171, file: !6, line: 116, baseType: !82, size: 8, align: 8, offset: 1344)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "closed", scope: !171, file: !6, line: 117, baseType: !82, size: 8, align: 8, offset: 1352)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "fatal", scope: !171, file: !6, line: 118, baseType: !82, size: 8, align: 8, offset: 1360)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "init", scope: !161, file: !6, line: 69, baseType: !178, size: 64, align: 64, offset: 192)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !161, file: !6, line: 71, baseType: !214, size: 64, align: 64, offset: 256)
!214 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !215, size: 64, align: 64)
!215 = !DISubroutineType(types: !216)
!216 = !{!23, !169, !80, !80}
!217 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !161, file: !6, line: 74, baseType: !218, size: 64, align: 64, offset: 320)
!218 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !219, size: 64, align: 64)
!219 = !DISubroutineType(types: !220)
!220 = !{!23, !169}
!221 = !{!222}
!222 = !DISubrange(count: 16)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !5, file: !6, line: 176, baseType: !170, size: 64, align: 64, offset: 8256)
!224 = !DIDerivedType(tag: DW_TAG_member, name: "bypass_filter_bidding", scope: !5, file: !6, line: 179, baseType: !23, size: 32, align: 32, offset: 8320)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "header_position", scope: !5, file: !6, line: 182, baseType: !52, size: 64, align: 64, offset: 8384)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "data_start_node", scope: !5, file: !6, line: 185, baseType: !13, size: 32, align: 32, offset: 8448)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "data_end_node", scope: !5, file: !6, line: 186, baseType: !13, size: 32, align: 32, offset: 8480)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "formats", scope: !5, file: !6, line: 209, baseType: !229, size: 11264, align: 64, offset: 8512)
!229 = !DICompositeType(tag: DW_TAG_array_type, baseType: !230, size: 11264, align: 64, elements: !221)
!230 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_format_descriptor", file: !6, line: 196, size: 704, align: 64, elements: !231)
!231 = !{!232, !233, !234, !238, !242, !246, !250, !254, !258, !259, !260}
!232 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !230, file: !6, line: 197, baseType: !123, size: 64, align: 64)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !230, file: !6, line: 198, baseType: !80, size: 64, align: 64, offset: 64)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "bid", scope: !230, file: !6, line: 199, baseType: !235, size: 64, align: 64, offset: 128)
!235 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !236, size: 64, align: 64)
!236 = !DISubroutineType(types: !237)
!237 = !{!23, !4, !23}
!238 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !230, file: !6, line: 200, baseType: !239, size: 64, align: 64, offset: 192)
!239 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !240, size: 64, align: 64)
!240 = !DISubroutineType(types: !241)
!241 = !{!23, !4, !80, !80}
!242 = !DIDerivedType(tag: DW_TAG_member, name: "read_header", scope: !230, file: !6, line: 202, baseType: !243, size: 64, align: 64, offset: 256)
!243 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !244, size: 64, align: 64)
!244 = !DISubroutineType(types: !245)
!245 = !{!23, !4, !30}
!246 = !DIDerivedType(tag: DW_TAG_member, name: "read_data", scope: !230, file: !6, line: 203, baseType: !247, size: 64, align: 64, offset: 320)
!247 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !248, size: 64, align: 64)
!248 = !DISubroutineType(types: !249)
!249 = !{!23, !4, !64, !65, !66}
!250 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_skip", scope: !230, file: !6, line: 204, baseType: !251, size: 64, align: 64, offset: 384)
!251 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !252, size: 64, align: 64)
!252 = !DISubroutineType(types: !253)
!253 = !{!23, !4}
!254 = !DIDerivedType(tag: DW_TAG_member, name: "seek_data", scope: !230, file: !6, line: 205, baseType: !255, size: 64, align: 64, offset: 448)
!255 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !256, size: 64, align: 64)
!256 = !DISubroutineType(types: !257)
!257 = !{!52, !4, !52, !23}
!258 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup", scope: !230, file: !6, line: 206, baseType: !251, size: 64, align: 64, offset: 512)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "format_capabilties", scope: !230, file: !6, line: 207, baseType: !251, size: 64, align: 64, offset: 576)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "has_encrypted_entries", scope: !230, file: !6, line: 208, baseType: !251, size: 64, align: 64, offset: 640)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "format", scope: !5, file: !6, line: 210, baseType: !262, size: 64, align: 64, offset: 19776)
!262 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !230, size: 64, align: 64)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "extract", scope: !5, file: !6, line: 215, baseType: !264, size: 64, align: 64, offset: 19840)
!264 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !265, size: 64, align: 64)
!265 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_extract", file: !6, line: 151, size: 192, align: 64, elements: !266)
!266 = !{!267, !268, !272}
!267 = !DIDerivedType(tag: DW_TAG_member, name: "ad", scope: !265, file: !6, line: 152, baseType: !24, size: 64, align: 64)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress", scope: !265, file: !6, line: 155, baseType: !269, size: 64, align: 64, offset: 64)
!269 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !270, size: 64, align: 64)
!270 = !DISubroutineType(types: !271)
!271 = !{null, !123}
!272 = !DIDerivedType(tag: DW_TAG_member, name: "extract_progress_user_data", scope: !265, file: !6, line: 156, baseType: !123, size: 64, align: 64, offset: 128)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "cleanup_archive_extract", scope: !5, file: !6, line: 216, baseType: !251, size: 64, align: 64, offset: 19904)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "passphrases", scope: !5, file: !6, line: 227, baseType: !275, size: 320, align: 64, offset: 19968)
!275 = !DICompositeType(tag: DW_TAG_structure_type, scope: !5, file: !6, line: 221, size: 320, align: 64, elements: !276)
!276 = !{!277, !283, !285, !286, !291}
!277 = !DIDerivedType(tag: DW_TAG_member, name: "first", scope: !275, file: !6, line: 222, baseType: !278, size: 64, align: 64)
!278 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !279, size: 64, align: 64)
!279 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_read_passphrase", file: !6, line: 146, size: 128, align: 64, elements: !280)
!280 = !{!281, !282}
!281 = !DIDerivedType(tag: DW_TAG_member, name: "passphrase", scope: !279, file: !6, line: 147, baseType: !95, size: 64, align: 64)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !279, file: !6, line: 148, baseType: !278, size: 64, align: 64, offset: 64)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "last", scope: !275, file: !6, line: 223, baseType: !284, size: 64, align: 64, offset: 64)
!284 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !278, size: 64, align: 64)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "candidate", scope: !275, file: !6, line: 224, baseType: !23, size: 32, align: 32, offset: 128)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "callback", scope: !275, file: !6, line: 225, baseType: !287, size: 64, align: 64, offset: 192)
!287 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !288, size: 64, align: 64)
!288 = !DIDerivedType(tag: DW_TAG_typedef, name: "archive_passphrase_callback", file: !32, line: 256, baseType: !289)
!289 = !DISubroutineType(types: !290)
!290 = !{!80, !24, !123}
!291 = !DIDerivedType(tag: DW_TAG_member, name: "client_data", scope: !275, file: !6, line: 226, baseType: !123, size: 64, align: 64, offset: 256)
!292 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !293, size: 64, align: 64)
!293 = !DICompositeType(tag: DW_TAG_structure_type, name: "cpio", file: !1, line: 175, size: 640, align: 64, elements: !294)
!294 = !{!295, !296, !300, !312, !313, !314, !315, !316, !317, !318}
!295 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !293, file: !1, line: 176, baseType: !23, size: 32, align: 32)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "read_header", scope: !293, file: !1, line: 177, baseType: !297, size: 64, align: 64, offset: 64)
!297 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !298, size: 64, align: 64)
!298 = !DISubroutineType(types: !299)
!299 = !{!23, !4, !292, !30, !65, !65}
!300 = !DIDerivedType(tag: DW_TAG_member, name: "links_head", scope: !293, file: !1, line: 179, baseType: !301, size: 64, align: 64, offset: 128)
!301 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !302, size: 64, align: 64)
!302 = !DICompositeType(tag: DW_TAG_structure_type, name: "links_entry", file: !1, line: 165, size: 384, align: 64, elements: !303)
!303 = !{!304, !305, !306, !307, !310, !311}
!304 = !DIDerivedType(tag: DW_TAG_member, name: "next", scope: !302, file: !1, line: 166, baseType: !301, size: 64, align: 64)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "previous", scope: !302, file: !1, line: 167, baseType: !301, size: 64, align: 64, offset: 64)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "links", scope: !302, file: !1, line: 168, baseType: !23, size: 32, align: 32, offset: 128)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "dev", scope: !302, file: !1, line: 169, baseType: !308, size: 64, align: 64, offset: 192)
!308 = !DIDerivedType(tag: DW_TAG_typedef, name: "dev_t", file: !39, line: 60, baseType: !309)
!309 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !41, line: 124, baseType: !47)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "ino", scope: !302, file: !1, line: 170, baseType: !52, size: 64, align: 64, offset: 256)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !302, file: !1, line: 171, baseType: !95, size: 64, align: 64, offset: 320)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_remaining", scope: !293, file: !1, line: 180, baseType: !52, size: 64, align: 64, offset: 192)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "entry_bytes_unconsumed", scope: !293, file: !1, line: 181, baseType: !52, size: 64, align: 64, offset: 256)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "entry_offset", scope: !293, file: !1, line: 182, baseType: !52, size: 64, align: 64, offset: 320)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "entry_padding", scope: !293, file: !1, line: 183, baseType: !52, size: 64, align: 64, offset: 384)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "opt_sconv", scope: !293, file: !1, line: 185, baseType: !102, size: 64, align: 64, offset: 448)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "sconv_default", scope: !293, file: !1, line: 186, baseType: !102, size: 64, align: 64, offset: 512)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "init_default_conversion", scope: !293, file: !1, line: 187, baseType: !23, size: 32, align: 32, offset: 576)
!319 = !DIDerivedType(tag: DW_TAG_typedef, name: "mode_t", file: !39, line: 70, baseType: !320)
!320 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !41, line: 129, baseType: !13)
!321 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !322, size: 64, align: 64)
!322 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !323)
!323 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!324 = !{!325, !326, !327, !328, !329, !332, !333, !334, !335, !338, !339, !340, !341, !342, !345, !346, !347, !348, !349, !352, !353, !354}
!325 = distinct !DISubprogram(name: "archive_read_support_format_cpio", scope: !1, file: !1, line: 221, type: !21, isLocal: false, isDefinition: true, scopeLine: 222, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!326 = distinct !DISubprogram(name: "archive_read_format_cpio_bid", scope: !1, file: !1, line: 257, type: !236, isLocal: true, isDefinition: true, scopeLine: 258, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!327 = distinct !DISubprogram(name: "header_odc", scope: !1, file: !1, line: 755, type: !298, isLocal: true, isDefinition: true, scopeLine: 757, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!328 = distinct !DISubprogram(name: "find_odc_header", scope: !1, file: !1, line: 689, type: !252, isLocal: true, isDefinition: true, scopeLine: 690, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!329 = distinct !DISubprogram(name: "is_octal", scope: !1, file: !1, line: 657, type: !330, isLocal: true, isDefinition: true, scopeLine: 658, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!330 = !DISubroutineType(types: !331)
!331 = !{!23, !80, !45}
!332 = distinct !DISubprogram(name: "is_afio_large", scope: !1, file: !1, line: 668, type: !330, isLocal: true, isDefinition: true, scopeLine: 669, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!333 = distinct !DISubprogram(name: "is_hex", scope: !1, file: !1, line: 513, type: !330, isLocal: true, isDefinition: true, scopeLine: 514, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!334 = distinct !DISubprogram(name: "header_afiol", scope: !1, file: !1, line: 822, type: !298, isLocal: true, isDefinition: true, scopeLine: 824, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!335 = distinct !DISubprogram(name: "atol16", scope: !1, file: !1, line: 999, type: !336, isLocal: true, isDefinition: true, scopeLine: 1000, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!336 = !DISubroutineType(types: !337)
!337 = !{!52, !80, !13}
!338 = distinct !DISubprogram(name: "atol8", scope: !1, file: !1, line: 980, type: !336, isLocal: true, isDefinition: true, scopeLine: 981, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!339 = distinct !DISubprogram(name: "header_newc", scope: !1, file: !1, line: 587, type: !298, isLocal: true, isDefinition: true, scopeLine: 589, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!340 = distinct !DISubprogram(name: "find_newc_header", scope: !1, file: !1, line: 527, type: !252, isLocal: true, isDefinition: true, scopeLine: 528, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!341 = distinct !DISubprogram(name: "header_bin_be", scope: !1, file: !1, line: 903, type: !298, isLocal: true, isDefinition: true, scopeLine: 905, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!342 = distinct !DISubprogram(name: "be4", scope: !1, file: !1, line: 969, type: !343, isLocal: true, isDefinition: true, scopeLine: 970, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!343 = !DISubroutineType(types: !344)
!344 = !{!52, !321}
!345 = distinct !DISubprogram(name: "header_bin_le", scope: !1, file: !1, line: 864, type: !298, isLocal: true, isDefinition: true, scopeLine: 866, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!346 = distinct !DISubprogram(name: "le4", scope: !1, file: !1, line: 962, type: !343, isLocal: true, isDefinition: true, scopeLine: 963, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!347 = distinct !DISubprogram(name: "archive_read_format_cpio_options", scope: !1, file: !1, line: 321, type: !240, isLocal: true, isDefinition: true, scopeLine: 323, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!348 = distinct !DISubprogram(name: "archive_read_format_cpio_read_header", scope: !1, file: !1, line: 355, type: !244, isLocal: true, isDefinition: true, scopeLine: 357, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!349 = distinct !DISubprogram(name: "record_hardlink", scope: !1, file: !1, line: 1022, type: !350, isLocal: true, isDefinition: true, scopeLine: 1024, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!350 = !DISubroutineType(types: !351)
!351 = !{!23, !4, !292, !30}
!352 = distinct !DISubprogram(name: "archive_read_format_cpio_read_data", scope: !1, file: !1, line: 453, type: !248, isLocal: true, isDefinition: true, scopeLine: 455, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!353 = distinct !DISubprogram(name: "archive_read_format_cpio_skip", scope: !1, file: !1, line: 492, type: !252, isLocal: true, isDefinition: true, scopeLine: 493, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!354 = distinct !DISubprogram(name: "archive_read_format_cpio_cleanup", scope: !1, file: !1, line: 942, type: !252, isLocal: true, isDefinition: true, scopeLine: 943, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!355 = !{i32 2, !"Dwarf Version", i32 4}
!356 = !{i32 2, !"Debug Info Version", i32 3}
!357 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!358 = !DILocalVariable(name: "_a", arg: 1, scope: !325, file: !1, line: 221, type: !24)
!359 = !DIExpression()
!360 = !DILocation(line: 221, column: 50, scope: !325)
!361 = !DILocalVariable(name: "a", scope: !325, file: !1, line: 223, type: !4)
!362 = !DILocation(line: 223, column: 23, scope: !325)
!363 = !DILocation(line: 223, column: 50, scope: !325)
!364 = !DILocation(line: 223, column: 27, scope: !325)
!365 = !DILocalVariable(name: "cpio", scope: !325, file: !1, line: 224, type: !292)
!366 = !DILocation(line: 224, column: 15, scope: !325)
!367 = !DILocalVariable(name: "r", scope: !325, file: !1, line: 225, type: !23)
!368 = !DILocation(line: 225, column: 6, scope: !325)
!369 = !DILocation(line: 227, column: 2, scope: !325)
!370 = !DILocalVariable(name: "magic_test", scope: !371, file: !1, line: 227, type: !23)
!371 = distinct !DILexicalBlock(scope: !325, file: !1, line: 227, column: 2)
!372 = !DILocation(line: 227, column: 2, scope: !371)
!373 = !DILocation(line: 227, column: 2, scope: !374)
!374 = !DILexicalBlockFile(scope: !371, file: !1, discriminator: 1)
!375 = !DILocation(line: 227, column: 2, scope: !376)
!376 = !DILexicalBlockFile(scope: !377, file: !1, discriminator: 2)
!377 = distinct !DILexicalBlock(scope: !371, file: !1, line: 227, column: 2)
!378 = !DILocation(line: 227, column: 2, scope: !379)
!379 = !DILexicalBlockFile(scope: !371, file: !1, discriminator: 3)
!380 = !DILocation(line: 230, column: 24, scope: !325)
!381 = !DILocation(line: 230, column: 9, scope: !325)
!382 = !DILocation(line: 230, column: 7, scope: !325)
!383 = !DILocation(line: 231, column: 6, scope: !384)
!384 = distinct !DILexicalBlock(scope: !325, file: !1, line: 231, column: 6)
!385 = !DILocation(line: 231, column: 11, scope: !384)
!386 = !DILocation(line: 231, column: 6, scope: !325)
!387 = !DILocation(line: 232, column: 22, scope: !388)
!388 = distinct !DILexicalBlock(scope: !384, file: !1, line: 231, column: 20)
!389 = !DILocation(line: 232, column: 25, scope: !388)
!390 = !DILocation(line: 232, column: 3, scope: !388)
!391 = !DILocation(line: 233, column: 3, scope: !388)
!392 = !DILocation(line: 235, column: 2, scope: !325)
!393 = !DILocation(line: 235, column: 8, scope: !325)
!394 = !DILocation(line: 235, column: 14, scope: !325)
!395 = !DILocation(line: 237, column: 37, scope: !325)
!396 = !DILocation(line: 238, column: 6, scope: !325)
!397 = !DILocation(line: 237, column: 6, scope: !325)
!398 = !DILocation(line: 237, column: 4, scope: !325)
!399 = !DILocation(line: 250, column: 6, scope: !400)
!400 = distinct !DILexicalBlock(scope: !325, file: !1, line: 250, column: 6)
!401 = !DILocation(line: 250, column: 8, scope: !400)
!402 = !DILocation(line: 250, column: 6, scope: !325)
!403 = !DILocation(line: 251, column: 8, scope: !400)
!404 = !DILocation(line: 251, column: 3, scope: !400)
!405 = !DILocation(line: 252, column: 2, scope: !325)
!406 = !DILocation(line: 253, column: 1, scope: !325)
!407 = !DILocalVariable(name: "a", arg: 1, scope: !326, file: !1, line: 257, type: !4)
!408 = !DILocation(line: 257, column: 51, scope: !326)
!409 = !DILocalVariable(name: "best_bid", arg: 2, scope: !326, file: !1, line: 257, type: !23)
!410 = !DILocation(line: 257, column: 58, scope: !326)
!411 = !DILocalVariable(name: "p", scope: !326, file: !1, line: 259, type: !321)
!412 = !DILocation(line: 259, column: 23, scope: !326)
!413 = !DILocalVariable(name: "cpio", scope: !326, file: !1, line: 260, type: !292)
!414 = !DILocation(line: 260, column: 15, scope: !326)
!415 = !DILocalVariable(name: "bid", scope: !326, file: !1, line: 261, type: !23)
!416 = !DILocation(line: 261, column: 6, scope: !326)
!417 = !DILocation(line: 263, column: 8, scope: !326)
!418 = !DILocation(line: 265, column: 25, scope: !326)
!419 = !DILocation(line: 265, column: 28, scope: !326)
!420 = !DILocation(line: 265, column: 36, scope: !326)
!421 = !DILocation(line: 265, column: 9, scope: !326)
!422 = !DILocation(line: 265, column: 7, scope: !326)
!423 = !DILocation(line: 267, column: 32, scope: !424)
!424 = distinct !DILexicalBlock(scope: !326, file: !1, line: 267, column: 6)
!425 = !DILocation(line: 267, column: 11, scope: !424)
!426 = !DILocation(line: 267, column: 9, scope: !424)
!427 = !DILocation(line: 267, column: 45, scope: !424)
!428 = !DILocation(line: 267, column: 6, scope: !326)
!429 = !DILocation(line: 268, column: 3, scope: !424)
!430 = !DILocation(line: 270, column: 6, scope: !326)
!431 = !DILocation(line: 271, column: 13, scope: !432)
!432 = distinct !DILexicalBlock(scope: !326, file: !1, line: 271, column: 6)
!433 = !DILocation(line: 271, column: 6, scope: !432)
!434 = !DILocation(line: 271, column: 29, scope: !432)
!435 = !DILocation(line: 271, column: 6, scope: !326)
!436 = !DILocation(line: 273, column: 3, scope: !437)
!437 = distinct !DILexicalBlock(scope: !432, file: !1, line: 271, column: 35)
!438 = !DILocation(line: 273, column: 9, scope: !437)
!439 = !DILocation(line: 273, column: 21, scope: !437)
!440 = !DILocation(line: 274, column: 7, scope: !437)
!441 = !DILocation(line: 279, column: 2, scope: !437)
!442 = !DILocation(line: 279, column: 20, scope: !443)
!443 = !DILexicalBlockFile(scope: !444, file: !1, discriminator: 1)
!444 = distinct !DILexicalBlock(scope: !432, file: !1, line: 279, column: 13)
!445 = !DILocation(line: 279, column: 13, scope: !443)
!446 = !DILocation(line: 279, column: 36, scope: !443)
!447 = !DILocation(line: 281, column: 3, scope: !448)
!448 = distinct !DILexicalBlock(scope: !444, file: !1, line: 279, column: 42)
!449 = !DILocation(line: 281, column: 9, scope: !448)
!450 = !DILocation(line: 281, column: 21, scope: !448)
!451 = !DILocation(line: 282, column: 7, scope: !448)
!452 = !DILocation(line: 287, column: 2, scope: !448)
!453 = !DILocation(line: 287, column: 20, scope: !454)
!454 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 1)
!455 = distinct !DILexicalBlock(scope: !444, file: !1, line: 287, column: 13)
!456 = !DILocation(line: 287, column: 13, scope: !454)
!457 = !DILocation(line: 287, column: 36, scope: !454)
!458 = !DILocation(line: 289, column: 3, scope: !459)
!459 = distinct !DILexicalBlock(scope: !455, file: !1, line: 287, column: 42)
!460 = !DILocation(line: 289, column: 9, scope: !459)
!461 = !DILocation(line: 289, column: 21, scope: !459)
!462 = !DILocation(line: 290, column: 7, scope: !459)
!463 = !DILocation(line: 295, column: 2, scope: !459)
!464 = !DILocation(line: 295, column: 20, scope: !465)
!465 = !DILexicalBlockFile(scope: !466, file: !1, discriminator: 1)
!466 = distinct !DILexicalBlock(scope: !455, file: !1, line: 295, column: 13)
!467 = !DILocation(line: 295, column: 13, scope: !465)
!468 = !DILocation(line: 295, column: 36, scope: !465)
!469 = !DILocation(line: 298, column: 3, scope: !470)
!470 = distinct !DILexicalBlock(scope: !466, file: !1, line: 295, column: 42)
!471 = !DILocation(line: 298, column: 9, scope: !470)
!472 = !DILocation(line: 298, column: 21, scope: !470)
!473 = !DILocation(line: 299, column: 7, scope: !470)
!474 = !DILocation(line: 304, column: 2, scope: !470)
!475 = !DILocation(line: 304, column: 13, scope: !476)
!476 = !DILexicalBlockFile(scope: !477, file: !1, discriminator: 1)
!477 = distinct !DILexicalBlock(scope: !466, file: !1, line: 304, column: 13)
!478 = !DILocation(line: 304, column: 18, scope: !476)
!479 = !DILocation(line: 304, column: 26, scope: !476)
!480 = !DILocation(line: 304, column: 24, scope: !476)
!481 = !DILocation(line: 304, column: 31, scope: !476)
!482 = !DILocation(line: 306, column: 3, scope: !483)
!483 = distinct !DILexicalBlock(scope: !477, file: !1, line: 304, column: 42)
!484 = !DILocation(line: 306, column: 9, scope: !483)
!485 = !DILocation(line: 306, column: 21, scope: !483)
!486 = !DILocation(line: 307, column: 7, scope: !483)
!487 = !DILocation(line: 309, column: 2, scope: !483)
!488 = !DILocation(line: 309, column: 13, scope: !489)
!489 = !DILexicalBlockFile(scope: !490, file: !1, discriminator: 1)
!490 = distinct !DILexicalBlock(scope: !477, file: !1, line: 309, column: 13)
!491 = !DILocation(line: 309, column: 20, scope: !489)
!492 = !DILocation(line: 309, column: 25, scope: !489)
!493 = !DILocation(line: 309, column: 18, scope: !489)
!494 = !DILocation(line: 309, column: 31, scope: !489)
!495 = !DILocation(line: 311, column: 3, scope: !496)
!496 = distinct !DILexicalBlock(scope: !490, file: !1, line: 309, column: 42)
!497 = !DILocation(line: 311, column: 9, scope: !496)
!498 = !DILocation(line: 311, column: 21, scope: !496)
!499 = !DILocation(line: 312, column: 7, scope: !496)
!500 = !DILocation(line: 314, column: 2, scope: !496)
!501 = !DILocation(line: 315, column: 3, scope: !490)
!502 = !DILocation(line: 317, column: 10, scope: !326)
!503 = !DILocation(line: 317, column: 2, scope: !326)
!504 = !DILocation(line: 318, column: 1, scope: !326)
!505 = !DILocalVariable(name: "a", arg: 1, scope: !347, file: !1, line: 321, type: !4)
!506 = !DILocation(line: 321, column: 55, scope: !347)
!507 = !DILocalVariable(name: "key", arg: 2, scope: !347, file: !1, line: 322, type: !80)
!508 = !DILocation(line: 322, column: 17, scope: !347)
!509 = !DILocalVariable(name: "val", arg: 3, scope: !347, file: !1, line: 322, type: !80)
!510 = !DILocation(line: 322, column: 34, scope: !347)
!511 = !DILocalVariable(name: "cpio", scope: !347, file: !1, line: 324, type: !292)
!512 = !DILocation(line: 324, column: 15, scope: !347)
!513 = !DILocalVariable(name: "ret", scope: !347, file: !1, line: 325, type: !23)
!514 = !DILocation(line: 325, column: 6, scope: !347)
!515 = !DILocation(line: 327, column: 25, scope: !347)
!516 = !DILocation(line: 327, column: 28, scope: !347)
!517 = !DILocation(line: 327, column: 36, scope: !347)
!518 = !DILocation(line: 327, column: 9, scope: !347)
!519 = !DILocation(line: 327, column: 7, scope: !347)
!520 = !DILocation(line: 328, column: 13, scope: !521)
!521 = distinct !DILexicalBlock(scope: !347, file: !1, line: 328, column: 6)
!522 = !DILocation(line: 328, column: 6, scope: !521)
!523 = !DILocation(line: 328, column: 32, scope: !521)
!524 = !DILocation(line: 328, column: 6, scope: !347)
!525 = !DILocation(line: 330, column: 36, scope: !526)
!526 = distinct !DILexicalBlock(scope: !521, file: !1, line: 328, column: 38)
!527 = !DILocation(line: 330, column: 40, scope: !526)
!528 = !DILocation(line: 330, column: 35, scope: !526)
!529 = !DILocation(line: 330, column: 3, scope: !526)
!530 = !DILocation(line: 330, column: 9, scope: !526)
!531 = !DILocation(line: 330, column: 33, scope: !526)
!532 = !DILocation(line: 331, column: 3, scope: !526)
!533 = !DILocation(line: 332, column: 20, scope: !534)
!534 = distinct !DILexicalBlock(scope: !521, file: !1, line: 332, column: 13)
!535 = !DILocation(line: 332, column: 13, scope: !534)
!536 = !DILocation(line: 332, column: 40, scope: !534)
!537 = !DILocation(line: 332, column: 13, scope: !521)
!538 = !DILocation(line: 333, column: 7, scope: !539)
!539 = distinct !DILexicalBlock(scope: !540, file: !1, line: 333, column: 7)
!540 = distinct !DILexicalBlock(scope: !534, file: !1, line: 332, column: 46)
!541 = !DILocation(line: 333, column: 11, scope: !539)
!542 = !DILocation(line: 333, column: 19, scope: !539)
!543 = !DILocation(line: 333, column: 22, scope: !544)
!544 = !DILexicalBlockFile(scope: !539, file: !1, discriminator: 1)
!545 = !DILocation(line: 333, column: 29, scope: !544)
!546 = !DILocation(line: 333, column: 7, scope: !544)
!547 = !DILocation(line: 334, column: 23, scope: !539)
!548 = !DILocation(line: 334, column: 26, scope: !539)
!549 = !DILocation(line: 334, column: 4, scope: !539)
!550 = !DILocation(line: 339, column: 6, scope: !551)
!551 = distinct !DILexicalBlock(scope: !539, file: !1, line: 336, column: 8)
!552 = !DILocation(line: 339, column: 9, scope: !551)
!553 = !DILocation(line: 339, column: 18, scope: !551)
!554 = !DILocation(line: 338, column: 8, scope: !551)
!555 = !DILocation(line: 337, column: 4, scope: !551)
!556 = !DILocation(line: 337, column: 10, scope: !551)
!557 = !DILocation(line: 337, column: 20, scope: !551)
!558 = !DILocation(line: 340, column: 8, scope: !559)
!559 = distinct !DILexicalBlock(scope: !551, file: !1, line: 340, column: 8)
!560 = !DILocation(line: 340, column: 14, scope: !559)
!561 = !DILocation(line: 340, column: 24, scope: !559)
!562 = !DILocation(line: 340, column: 8, scope: !551)
!563 = !DILocation(line: 341, column: 9, scope: !559)
!564 = !DILocation(line: 341, column: 5, scope: !559)
!565 = !DILocation(line: 343, column: 9, scope: !559)
!566 = !DILocation(line: 345, column: 11, scope: !540)
!567 = !DILocation(line: 345, column: 3, scope: !540)
!568 = !DILocation(line: 351, column: 2, scope: !347)
!569 = !DILocation(line: 352, column: 1, scope: !347)
!570 = !DILocalVariable(name: "a", arg: 1, scope: !348, file: !1, line: 355, type: !4)
!571 = !DILocation(line: 355, column: 59, scope: !348)
!572 = !DILocalVariable(name: "entry", arg: 2, scope: !348, file: !1, line: 356, type: !30)
!573 = !DILocation(line: 356, column: 27, scope: !348)
!574 = !DILocalVariable(name: "cpio", scope: !348, file: !1, line: 358, type: !292)
!575 = !DILocation(line: 358, column: 15, scope: !348)
!576 = !DILocalVariable(name: "h", scope: !348, file: !1, line: 359, type: !43)
!577 = !DILocation(line: 359, column: 14, scope: !348)
!578 = !DILocalVariable(name: "hl", scope: !348, file: !1, line: 359, type: !43)
!579 = !DILocation(line: 359, column: 18, scope: !348)
!580 = !DILocalVariable(name: "sconv", scope: !348, file: !1, line: 360, type: !102)
!581 = !DILocation(line: 360, column: 30, scope: !348)
!582 = !DILocalVariable(name: "namelength", scope: !348, file: !1, line: 361, type: !45)
!583 = !DILocation(line: 361, column: 9, scope: !348)
!584 = !DILocalVariable(name: "name_pad", scope: !348, file: !1, line: 362, type: !45)
!585 = !DILocation(line: 362, column: 9, scope: !348)
!586 = !DILocalVariable(name: "r", scope: !348, file: !1, line: 363, type: !23)
!587 = !DILocation(line: 363, column: 6, scope: !348)
!588 = !DILocation(line: 365, column: 25, scope: !348)
!589 = !DILocation(line: 365, column: 28, scope: !348)
!590 = !DILocation(line: 365, column: 36, scope: !348)
!591 = !DILocation(line: 365, column: 9, scope: !348)
!592 = !DILocation(line: 365, column: 7, scope: !348)
!593 = !DILocation(line: 366, column: 10, scope: !348)
!594 = !DILocation(line: 366, column: 16, scope: !348)
!595 = !DILocation(line: 366, column: 8, scope: !348)
!596 = !DILocation(line: 367, column: 6, scope: !597)
!597 = distinct !DILexicalBlock(scope: !348, file: !1, line: 367, column: 6)
!598 = !DILocation(line: 367, column: 12, scope: !597)
!599 = !DILocation(line: 367, column: 6, scope: !348)
!600 = !DILocation(line: 368, column: 8, scope: !601)
!601 = distinct !DILexicalBlock(scope: !602, file: !1, line: 368, column: 7)
!602 = distinct !DILexicalBlock(scope: !597, file: !1, line: 367, column: 21)
!603 = !DILocation(line: 368, column: 14, scope: !601)
!604 = !DILocation(line: 368, column: 7, scope: !602)
!605 = !DILocation(line: 371, column: 12, scope: !606)
!606 = distinct !DILexicalBlock(scope: !601, file: !1, line: 368, column: 39)
!607 = !DILocation(line: 371, column: 15, scope: !606)
!608 = !DILocation(line: 370, column: 8, scope: !606)
!609 = !DILocation(line: 369, column: 4, scope: !606)
!610 = !DILocation(line: 369, column: 10, scope: !606)
!611 = !DILocation(line: 369, column: 24, scope: !606)
!612 = !DILocation(line: 372, column: 4, scope: !606)
!613 = !DILocation(line: 372, column: 10, scope: !606)
!614 = !DILocation(line: 372, column: 34, scope: !606)
!615 = !DILocation(line: 373, column: 3, scope: !606)
!616 = !DILocation(line: 374, column: 11, scope: !602)
!617 = !DILocation(line: 374, column: 17, scope: !602)
!618 = !DILocation(line: 374, column: 9, scope: !602)
!619 = !DILocation(line: 375, column: 2, scope: !602)
!620 = !DILocation(line: 377, column: 7, scope: !348)
!621 = !DILocation(line: 377, column: 13, scope: !348)
!622 = !DILocation(line: 377, column: 25, scope: !348)
!623 = !DILocation(line: 377, column: 28, scope: !348)
!624 = !DILocation(line: 377, column: 34, scope: !348)
!625 = !DILocation(line: 377, column: 4, scope: !348)
!626 = !DILocation(line: 379, column: 6, scope: !627)
!627 = distinct !DILexicalBlock(scope: !348, file: !1, line: 379, column: 6)
!628 = !DILocation(line: 379, column: 8, scope: !627)
!629 = !DILocation(line: 379, column: 6, scope: !348)
!630 = !DILocation(line: 380, column: 11, scope: !627)
!631 = !DILocation(line: 380, column: 3, scope: !627)
!632 = !DILocation(line: 383, column: 27, scope: !348)
!633 = !DILocation(line: 383, column: 30, scope: !348)
!634 = !DILocation(line: 383, column: 43, scope: !348)
!635 = !DILocation(line: 383, column: 41, scope: !348)
!636 = !DILocation(line: 383, column: 6, scope: !348)
!637 = !DILocation(line: 383, column: 4, scope: !348)
!638 = !DILocation(line: 384, column: 6, scope: !639)
!639 = distinct !DILexicalBlock(scope: !348, file: !1, line: 384, column: 6)
!640 = !DILocation(line: 384, column: 8, scope: !639)
!641 = !DILocation(line: 384, column: 6, scope: !348)
!642 = !DILocation(line: 385, column: 6, scope: !639)
!643 = !DILocation(line: 386, column: 36, scope: !644)
!644 = distinct !DILexicalBlock(scope: !348, file: !1, line: 386, column: 6)
!645 = !DILocation(line: 387, column: 20, scope: !644)
!646 = !DILocation(line: 387, column: 23, scope: !644)
!647 = !DILocation(line: 387, column: 35, scope: !644)
!648 = !DILocation(line: 386, column: 6, scope: !644)
!649 = !DILocation(line: 387, column: 42, scope: !644)
!650 = !DILocation(line: 386, column: 6, scope: !348)
!651 = !DILocation(line: 388, column: 7, scope: !652)
!652 = distinct !DILexicalBlock(scope: !653, file: !1, line: 388, column: 7)
!653 = distinct !DILexicalBlock(scope: !644, file: !1, line: 387, column: 48)
!654 = !DILocation(line: 388, column: 13, scope: !652)
!655 = !DILocation(line: 388, column: 7, scope: !653)
!656 = !DILocation(line: 389, column: 23, scope: !657)
!657 = distinct !DILexicalBlock(scope: !652, file: !1, line: 388, column: 24)
!658 = !DILocation(line: 389, column: 26, scope: !657)
!659 = !DILocation(line: 389, column: 4, scope: !657)
!660 = !DILocation(line: 391, column: 4, scope: !657)
!661 = !DILocation(line: 393, column: 22, scope: !653)
!662 = !DILocation(line: 393, column: 25, scope: !653)
!663 = !DILocation(line: 395, column: 46, scope: !653)
!664 = !DILocation(line: 395, column: 7, scope: !653)
!665 = !DILocation(line: 393, column: 3, scope: !653)
!666 = !DILocation(line: 396, column: 5, scope: !653)
!667 = !DILocation(line: 397, column: 2, scope: !653)
!668 = !DILocation(line: 398, column: 2, scope: !348)
!669 = !DILocation(line: 398, column: 8, scope: !348)
!670 = !DILocation(line: 398, column: 21, scope: !348)
!671 = !DILocation(line: 400, column: 25, scope: !348)
!672 = !DILocation(line: 400, column: 28, scope: !348)
!673 = !DILocation(line: 400, column: 41, scope: !348)
!674 = !DILocation(line: 400, column: 39, scope: !348)
!675 = !DILocation(line: 400, column: 2, scope: !348)
!676 = !DILocation(line: 403, column: 29, scope: !677)
!677 = distinct !DILexicalBlock(scope: !348, file: !1, line: 403, column: 6)
!678 = !DILocation(line: 403, column: 6, scope: !677)
!679 = !DILocation(line: 403, column: 36, scope: !677)
!680 = !DILocation(line: 403, column: 6, scope: !348)
!681 = !DILocation(line: 404, column: 7, scope: !682)
!682 = distinct !DILexicalBlock(scope: !683, file: !1, line: 404, column: 7)
!683 = distinct !DILexicalBlock(scope: !677, file: !1, line: 403, column: 49)
!684 = !DILocation(line: 404, column: 13, scope: !682)
!685 = !DILocation(line: 404, column: 35, scope: !682)
!686 = !DILocation(line: 404, column: 7, scope: !683)
!687 = !DILocation(line: 405, column: 23, scope: !688)
!688 = distinct !DILexicalBlock(scope: !682, file: !1, line: 404, column: 50)
!689 = !DILocation(line: 405, column: 26, scope: !688)
!690 = !DILocation(line: 405, column: 4, scope: !688)
!691 = !DILocation(line: 407, column: 4, scope: !688)
!692 = !DILocation(line: 409, column: 29, scope: !683)
!693 = !DILocation(line: 410, column: 12, scope: !683)
!694 = !DILocation(line: 410, column: 18, scope: !683)
!695 = !DILocation(line: 409, column: 8, scope: !683)
!696 = !DILocation(line: 409, column: 6, scope: !683)
!697 = !DILocation(line: 411, column: 7, scope: !698)
!698 = distinct !DILexicalBlock(scope: !683, file: !1, line: 411, column: 7)
!699 = !DILocation(line: 411, column: 10, scope: !698)
!700 = !DILocation(line: 411, column: 7, scope: !683)
!701 = !DILocation(line: 412, column: 4, scope: !698)
!702 = !DILocation(line: 413, column: 36, scope: !703)
!703 = distinct !DILexicalBlock(scope: !683, file: !1, line: 413, column: 7)
!704 = !DILocation(line: 413, column: 57, scope: !703)
!705 = !DILocation(line: 414, column: 15, scope: !703)
!706 = !DILocation(line: 414, column: 21, scope: !703)
!707 = !DILocation(line: 414, column: 44, scope: !703)
!708 = !DILocation(line: 413, column: 7, scope: !703)
!709 = !DILocation(line: 414, column: 51, scope: !703)
!710 = !DILocation(line: 413, column: 7, scope: !683)
!711 = !DILocation(line: 415, column: 8, scope: !712)
!712 = distinct !DILexicalBlock(scope: !713, file: !1, line: 415, column: 8)
!713 = distinct !DILexicalBlock(scope: !703, file: !1, line: 414, column: 57)
!714 = !DILocation(line: 415, column: 14, scope: !712)
!715 = !DILocation(line: 415, column: 8, scope: !713)
!716 = !DILocation(line: 416, column: 24, scope: !717)
!717 = distinct !DILexicalBlock(scope: !712, file: !1, line: 415, column: 25)
!718 = !DILocation(line: 416, column: 27, scope: !717)
!719 = !DILocation(line: 416, column: 5, scope: !717)
!720 = !DILocation(line: 418, column: 5, scope: !717)
!721 = !DILocation(line: 420, column: 23, scope: !713)
!722 = !DILocation(line: 420, column: 26, scope: !713)
!723 = !DILocation(line: 424, column: 47, scope: !713)
!724 = !DILocation(line: 424, column: 8, scope: !713)
!725 = !DILocation(line: 420, column: 4, scope: !713)
!726 = !DILocation(line: 425, column: 6, scope: !713)
!727 = !DILocation(line: 426, column: 3, scope: !713)
!728 = !DILocation(line: 427, column: 26, scope: !683)
!729 = !DILocation(line: 427, column: 29, scope: !683)
!730 = !DILocation(line: 427, column: 35, scope: !683)
!731 = !DILocation(line: 427, column: 3, scope: !683)
!732 = !DILocation(line: 428, column: 3, scope: !683)
!733 = !DILocation(line: 428, column: 9, scope: !683)
!734 = !DILocation(line: 428, column: 31, scope: !683)
!735 = !DILocation(line: 429, column: 2, scope: !683)
!736 = !DILocation(line: 437, column: 6, scope: !737)
!737 = distinct !DILexicalBlock(scope: !348, file: !1, line: 437, column: 6)
!738 = !DILocation(line: 437, column: 17, scope: !737)
!739 = !DILocation(line: 437, column: 23, scope: !737)
!740 = !DILocation(line: 437, column: 48, scope: !741)
!741 = !DILexicalBlockFile(scope: !737, file: !1, discriminator: 1)
!742 = !DILocation(line: 437, column: 26, scope: !741)
!743 = !DILocation(line: 438, column: 10, scope: !737)
!744 = !DILocation(line: 437, column: 6, scope: !741)
!745 = !DILocation(line: 440, column: 24, scope: !746)
!746 = distinct !DILexicalBlock(scope: !737, file: !1, line: 438, column: 16)
!747 = !DILocation(line: 440, column: 27, scope: !746)
!748 = !DILocation(line: 440, column: 3, scope: !746)
!749 = !DILocation(line: 441, column: 3, scope: !746)
!750 = !DILocation(line: 445, column: 22, scope: !751)
!751 = distinct !DILexicalBlock(scope: !348, file: !1, line: 445, column: 6)
!752 = !DILocation(line: 445, column: 25, scope: !751)
!753 = !DILocation(line: 445, column: 31, scope: !751)
!754 = !DILocation(line: 445, column: 6, scope: !751)
!755 = !DILocation(line: 445, column: 38, scope: !751)
!756 = !DILocation(line: 445, column: 6, scope: !348)
!757 = !DILocation(line: 446, column: 3, scope: !758)
!758 = distinct !DILexicalBlock(scope: !751, file: !1, line: 445, column: 53)
!759 = !DILocation(line: 449, column: 10, scope: !348)
!760 = !DILocation(line: 449, column: 2, scope: !348)
!761 = !DILocation(line: 450, column: 1, scope: !348)
!762 = !DILocalVariable(name: "a", arg: 1, scope: !352, file: !1, line: 453, type: !4)
!763 = !DILocation(line: 453, column: 57, scope: !352)
!764 = !DILocalVariable(name: "buff", arg: 2, scope: !352, file: !1, line: 454, type: !64)
!765 = !DILocation(line: 454, column: 18, scope: !352)
!766 = !DILocalVariable(name: "size", arg: 3, scope: !352, file: !1, line: 454, type: !65)
!767 = !DILocation(line: 454, column: 32, scope: !352)
!768 = !DILocalVariable(name: "offset", arg: 4, scope: !352, file: !1, line: 454, type: !66)
!769 = !DILocation(line: 454, column: 47, scope: !352)
!770 = !DILocalVariable(name: "bytes_read", scope: !352, file: !1, line: 456, type: !38)
!771 = !DILocation(line: 456, column: 10, scope: !352)
!772 = !DILocalVariable(name: "cpio", scope: !352, file: !1, line: 457, type: !292)
!773 = !DILocation(line: 457, column: 15, scope: !352)
!774 = !DILocation(line: 459, column: 25, scope: !352)
!775 = !DILocation(line: 459, column: 28, scope: !352)
!776 = !DILocation(line: 459, column: 36, scope: !352)
!777 = !DILocation(line: 459, column: 9, scope: !352)
!778 = !DILocation(line: 459, column: 7, scope: !352)
!779 = !DILocation(line: 461, column: 6, scope: !780)
!780 = distinct !DILexicalBlock(scope: !352, file: !1, line: 461, column: 6)
!781 = !DILocation(line: 461, column: 12, scope: !780)
!782 = !DILocation(line: 461, column: 6, scope: !352)
!783 = !DILocation(line: 462, column: 26, scope: !784)
!784 = distinct !DILexicalBlock(scope: !780, file: !1, line: 461, column: 36)
!785 = !DILocation(line: 462, column: 29, scope: !784)
!786 = !DILocation(line: 462, column: 35, scope: !784)
!787 = !DILocation(line: 462, column: 3, scope: !784)
!788 = !DILocation(line: 463, column: 3, scope: !784)
!789 = !DILocation(line: 463, column: 9, scope: !784)
!790 = !DILocation(line: 463, column: 32, scope: !784)
!791 = !DILocation(line: 464, column: 2, scope: !784)
!792 = !DILocation(line: 466, column: 6, scope: !793)
!793 = distinct !DILexicalBlock(scope: !352, file: !1, line: 466, column: 6)
!794 = !DILocation(line: 466, column: 12, scope: !793)
!795 = !DILocation(line: 466, column: 34, scope: !793)
!796 = !DILocation(line: 466, column: 6, scope: !352)
!797 = !DILocation(line: 467, column: 32, scope: !798)
!798 = distinct !DILexicalBlock(scope: !793, file: !1, line: 466, column: 39)
!799 = !DILocation(line: 467, column: 11, scope: !798)
!800 = !DILocation(line: 467, column: 4, scope: !798)
!801 = !DILocation(line: 467, column: 9, scope: !798)
!802 = !DILocation(line: 468, column: 7, scope: !803)
!803 = distinct !DILexicalBlock(scope: !798, file: !1, line: 468, column: 7)
!804 = !DILocation(line: 468, column: 18, scope: !803)
!805 = !DILocation(line: 468, column: 7, scope: !798)
!806 = !DILocation(line: 469, column: 4, scope: !803)
!807 = !DILocation(line: 470, column: 7, scope: !808)
!808 = distinct !DILexicalBlock(scope: !798, file: !1, line: 470, column: 7)
!809 = !DILocation(line: 470, column: 20, scope: !808)
!810 = !DILocation(line: 470, column: 26, scope: !808)
!811 = !DILocation(line: 470, column: 18, scope: !808)
!812 = !DILocation(line: 470, column: 7, scope: !798)
!813 = !DILocation(line: 471, column: 26, scope: !808)
!814 = !DILocation(line: 471, column: 32, scope: !808)
!815 = !DILocation(line: 471, column: 15, scope: !808)
!816 = !DILocation(line: 471, column: 4, scope: !808)
!817 = !DILocation(line: 472, column: 11, scope: !798)
!818 = !DILocation(line: 472, column: 4, scope: !798)
!819 = !DILocation(line: 472, column: 9, scope: !798)
!820 = !DILocation(line: 473, column: 34, scope: !798)
!821 = !DILocation(line: 473, column: 3, scope: !798)
!822 = !DILocation(line: 473, column: 9, scope: !798)
!823 = !DILocation(line: 473, column: 32, scope: !798)
!824 = !DILocation(line: 474, column: 13, scope: !798)
!825 = !DILocation(line: 474, column: 19, scope: !798)
!826 = !DILocation(line: 474, column: 4, scope: !798)
!827 = !DILocation(line: 474, column: 11, scope: !798)
!828 = !DILocation(line: 475, column: 25, scope: !798)
!829 = !DILocation(line: 475, column: 3, scope: !798)
!830 = !DILocation(line: 475, column: 9, scope: !798)
!831 = !DILocation(line: 475, column: 22, scope: !798)
!832 = !DILocation(line: 476, column: 34, scope: !798)
!833 = !DILocation(line: 476, column: 3, scope: !798)
!834 = !DILocation(line: 476, column: 9, scope: !798)
!835 = !DILocation(line: 476, column: 31, scope: !798)
!836 = !DILocation(line: 477, column: 3, scope: !798)
!837 = !DILocation(line: 479, column: 7, scope: !838)
!838 = distinct !DILexicalBlock(scope: !839, file: !1, line: 479, column: 7)
!839 = distinct !DILexicalBlock(scope: !793, file: !1, line: 478, column: 9)
!840 = !DILocation(line: 479, column: 13, scope: !838)
!841 = !DILocation(line: 480, column: 27, scope: !838)
!842 = !DILocation(line: 480, column: 30, scope: !838)
!843 = !DILocation(line: 480, column: 36, scope: !838)
!844 = !DILocation(line: 480, column: 4, scope: !838)
!845 = !DILocation(line: 479, column: 27, scope: !838)
!846 = !DILocation(line: 479, column: 7, scope: !839)
!847 = !DILocation(line: 481, column: 4, scope: !848)
!848 = distinct !DILexicalBlock(scope: !838, file: !1, line: 480, column: 52)
!849 = !DILocation(line: 483, column: 3, scope: !839)
!850 = !DILocation(line: 483, column: 9, scope: !839)
!851 = !DILocation(line: 483, column: 23, scope: !839)
!852 = !DILocation(line: 484, column: 4, scope: !839)
!853 = !DILocation(line: 484, column: 9, scope: !839)
!854 = !DILocation(line: 485, column: 4, scope: !839)
!855 = !DILocation(line: 485, column: 9, scope: !839)
!856 = !DILocation(line: 486, column: 13, scope: !839)
!857 = !DILocation(line: 486, column: 19, scope: !839)
!858 = !DILocation(line: 486, column: 4, scope: !839)
!859 = !DILocation(line: 486, column: 11, scope: !839)
!860 = !DILocation(line: 487, column: 3, scope: !839)
!861 = !DILocation(line: 489, column: 1, scope: !352)
!862 = !DILocalVariable(name: "a", arg: 1, scope: !353, file: !1, line: 492, type: !4)
!863 = !DILocation(line: 492, column: 52, scope: !353)
!864 = !DILocalVariable(name: "cpio", scope: !353, file: !1, line: 494, type: !292)
!865 = !DILocation(line: 494, column: 15, scope: !353)
!866 = !DILocation(line: 494, column: 38, scope: !353)
!867 = !DILocation(line: 494, column: 41, scope: !353)
!868 = !DILocation(line: 494, column: 49, scope: !353)
!869 = !DILocation(line: 494, column: 22, scope: !353)
!870 = !DILocalVariable(name: "to_skip", scope: !353, file: !1, line: 495, type: !52)
!871 = !DILocation(line: 495, column: 10, scope: !353)
!872 = !DILocation(line: 495, column: 20, scope: !353)
!873 = !DILocation(line: 495, column: 26, scope: !353)
!874 = !DILocation(line: 495, column: 50, scope: !353)
!875 = !DILocation(line: 495, column: 56, scope: !353)
!876 = !DILocation(line: 495, column: 48, scope: !353)
!877 = !DILocation(line: 496, column: 3, scope: !353)
!878 = !DILocation(line: 496, column: 9, scope: !353)
!879 = !DILocation(line: 495, column: 70, scope: !353)
!880 = !DILocation(line: 498, column: 6, scope: !881)
!881 = distinct !DILexicalBlock(scope: !353, file: !1, line: 498, column: 6)
!882 = !DILocation(line: 498, column: 40, scope: !881)
!883 = !DILocation(line: 498, column: 43, scope: !881)
!884 = !DILocation(line: 498, column: 17, scope: !881)
!885 = !DILocation(line: 498, column: 14, scope: !881)
!886 = !DILocation(line: 498, column: 6, scope: !353)
!887 = !DILocation(line: 499, column: 3, scope: !888)
!888 = distinct !DILexicalBlock(scope: !881, file: !1, line: 498, column: 53)
!889 = !DILocation(line: 501, column: 2, scope: !353)
!890 = !DILocation(line: 501, column: 8, scope: !353)
!891 = !DILocation(line: 501, column: 30, scope: !353)
!892 = !DILocation(line: 502, column: 2, scope: !353)
!893 = !DILocation(line: 502, column: 8, scope: !353)
!894 = !DILocation(line: 502, column: 22, scope: !353)
!895 = !DILocation(line: 503, column: 2, scope: !353)
!896 = !DILocation(line: 503, column: 8, scope: !353)
!897 = !DILocation(line: 503, column: 31, scope: !353)
!898 = !DILocation(line: 504, column: 2, scope: !353)
!899 = !DILocation(line: 505, column: 1, scope: !353)
!900 = !DILocalVariable(name: "a", arg: 1, scope: !354, file: !1, line: 942, type: !4)
!901 = !DILocation(line: 942, column: 55, scope: !354)
!902 = !DILocalVariable(name: "cpio", scope: !354, file: !1, line: 944, type: !292)
!903 = !DILocation(line: 944, column: 15, scope: !354)
!904 = !DILocation(line: 946, column: 25, scope: !354)
!905 = !DILocation(line: 946, column: 28, scope: !354)
!906 = !DILocation(line: 946, column: 36, scope: !354)
!907 = !DILocation(line: 946, column: 9, scope: !354)
!908 = !DILocation(line: 946, column: 7, scope: !354)
!909 = !DILocation(line: 948, column: 9, scope: !354)
!910 = !DILocation(line: 948, column: 16, scope: !911)
!911 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 1)
!912 = !DILocation(line: 948, column: 22, scope: !911)
!913 = !DILocation(line: 948, column: 33, scope: !911)
!914 = !DILocation(line: 948, column: 9, scope: !911)
!915 = !DILocalVariable(name: "lp", scope: !916, file: !1, line: 949, type: !301)
!916 = distinct !DILexicalBlock(scope: !354, file: !1, line: 948, column: 42)
!917 = !DILocation(line: 949, column: 37, scope: !916)
!918 = !DILocation(line: 949, column: 42, scope: !916)
!919 = !DILocation(line: 949, column: 48, scope: !916)
!920 = !DILocation(line: 949, column: 60, scope: !916)
!921 = !DILocation(line: 951, column: 21, scope: !922)
!922 = distinct !DILexicalBlock(scope: !916, file: !1, line: 951, column: 21)
!923 = !DILocation(line: 951, column: 27, scope: !922)
!924 = !DILocation(line: 951, column: 39, scope: !922)
!925 = !DILocation(line: 951, column: 21, scope: !916)
!926 = !DILocation(line: 952, column: 30, scope: !922)
!927 = !DILocation(line: 952, column: 36, scope: !922)
!928 = !DILocation(line: 952, column: 48, scope: !922)
!929 = !DILocation(line: 952, column: 25, scope: !922)
!930 = !DILocation(line: 953, column: 22, scope: !916)
!931 = !DILocation(line: 953, column: 28, scope: !916)
!932 = !DILocation(line: 953, column: 17, scope: !916)
!933 = !DILocation(line: 954, column: 36, scope: !916)
!934 = !DILocation(line: 954, column: 17, scope: !916)
!935 = !DILocation(line: 954, column: 23, scope: !916)
!936 = !DILocation(line: 954, column: 34, scope: !916)
!937 = !DILocation(line: 948, column: 9, scope: !938)
!938 = !DILexicalBlockFile(scope: !354, file: !1, discriminator: 2)
!939 = !DILocation(line: 956, column: 7, scope: !354)
!940 = !DILocation(line: 956, column: 2, scope: !354)
!941 = !DILocation(line: 957, column: 3, scope: !354)
!942 = !DILocation(line: 957, column: 6, scope: !354)
!943 = !DILocation(line: 957, column: 14, scope: !354)
!944 = !DILocation(line: 957, column: 20, scope: !354)
!945 = !DILocation(line: 958, column: 2, scope: !354)
!946 = !DILocalVariable(name: "a", arg: 1, scope: !327, file: !1, line: 755, type: !4)
!947 = !DILocation(line: 755, column: 33, scope: !327)
!948 = !DILocalVariable(name: "cpio", arg: 2, scope: !327, file: !1, line: 755, type: !292)
!949 = !DILocation(line: 755, column: 49, scope: !327)
!950 = !DILocalVariable(name: "entry", arg: 3, scope: !327, file: !1, line: 756, type: !30)
!951 = !DILocation(line: 756, column: 27, scope: !327)
!952 = !DILocalVariable(name: "namelength", arg: 4, scope: !327, file: !1, line: 756, type: !65)
!953 = !DILocation(line: 756, column: 42, scope: !327)
!954 = !DILocalVariable(name: "name_pad", arg: 5, scope: !327, file: !1, line: 756, type: !65)
!955 = !DILocation(line: 756, column: 62, scope: !327)
!956 = !DILocalVariable(name: "h", scope: !327, file: !1, line: 758, type: !43)
!957 = !DILocation(line: 758, column: 14, scope: !327)
!958 = !DILocalVariable(name: "r", scope: !327, file: !1, line: 759, type: !23)
!959 = !DILocation(line: 759, column: 6, scope: !327)
!960 = !DILocalVariable(name: "header", scope: !327, file: !1, line: 760, type: !80)
!961 = !DILocation(line: 760, column: 14, scope: !327)
!962 = !DILocation(line: 762, column: 2, scope: !327)
!963 = !DILocation(line: 762, column: 5, scope: !327)
!964 = !DILocation(line: 762, column: 13, scope: !327)
!965 = !DILocation(line: 762, column: 28, scope: !327)
!966 = !DILocation(line: 763, column: 2, scope: !327)
!967 = !DILocation(line: 763, column: 5, scope: !327)
!968 = !DILocation(line: 763, column: 13, scope: !327)
!969 = !DILocation(line: 763, column: 33, scope: !327)
!970 = !DILocation(line: 766, column: 22, scope: !327)
!971 = !DILocation(line: 766, column: 6, scope: !327)
!972 = !DILocation(line: 766, column: 4, scope: !327)
!973 = !DILocation(line: 767, column: 6, scope: !974)
!974 = distinct !DILexicalBlock(scope: !327, file: !1, line: 767, column: 6)
!975 = !DILocation(line: 767, column: 8, scope: !974)
!976 = !DILocation(line: 767, column: 6, scope: !327)
!977 = !DILocation(line: 768, column: 11, scope: !974)
!978 = !DILocation(line: 768, column: 3, scope: !974)
!979 = !DILocation(line: 770, column: 6, scope: !980)
!980 = distinct !DILexicalBlock(scope: !327, file: !1, line: 770, column: 6)
!981 = !DILocation(line: 770, column: 9, scope: !980)
!982 = !DILocation(line: 770, column: 17, scope: !980)
!983 = !DILocation(line: 770, column: 32, scope: !980)
!984 = !DILocation(line: 770, column: 6, scope: !327)
!985 = !DILocalVariable(name: "r2", scope: !986, file: !1, line: 771, type: !23)
!986 = distinct !DILexicalBlock(scope: !980, file: !1, line: 770, column: 67)
!987 = !DILocation(line: 771, column: 7, scope: !986)
!988 = !DILocation(line: 771, column: 26, scope: !986)
!989 = !DILocation(line: 771, column: 29, scope: !986)
!990 = !DILocation(line: 771, column: 35, scope: !986)
!991 = !DILocation(line: 771, column: 42, scope: !986)
!992 = !DILocation(line: 771, column: 54, scope: !986)
!993 = !DILocation(line: 771, column: 13, scope: !986)
!994 = !DILocation(line: 772, column: 7, scope: !995)
!995 = distinct !DILexicalBlock(scope: !986, file: !1, line: 772, column: 7)
!996 = !DILocation(line: 772, column: 10, scope: !995)
!997 = !DILocation(line: 772, column: 7, scope: !986)
!998 = !DILocation(line: 773, column: 12, scope: !995)
!999 = !DILocation(line: 773, column: 4, scope: !995)
!1000 = !DILocation(line: 775, column: 12, scope: !995)
!1001 = !DILocation(line: 775, column: 4, scope: !995)
!1002 = !DILocation(line: 779, column: 27, scope: !327)
!1003 = !DILocation(line: 779, column: 6, scope: !327)
!1004 = !DILocation(line: 779, column: 4, scope: !327)
!1005 = !DILocation(line: 780, column: 6, scope: !1006)
!1006 = distinct !DILexicalBlock(scope: !327, file: !1, line: 780, column: 6)
!1007 = !DILocation(line: 780, column: 8, scope: !1006)
!1008 = !DILocation(line: 780, column: 6, scope: !327)
!1009 = !DILocation(line: 781, column: 6, scope: !1006)
!1010 = !DILocation(line: 784, column: 25, scope: !327)
!1011 = !DILocation(line: 784, column: 9, scope: !327)
!1012 = !DILocation(line: 786, column: 24, scope: !327)
!1013 = !DILocation(line: 787, column: 16, scope: !327)
!1014 = !DILocation(line: 787, column: 23, scope: !327)
!1015 = !DILocation(line: 787, column: 10, scope: !327)
!1016 = !DILocation(line: 786, column: 2, scope: !327)
!1017 = !DILocation(line: 788, column: 24, scope: !327)
!1018 = !DILocation(line: 788, column: 37, scope: !327)
!1019 = !DILocation(line: 788, column: 44, scope: !327)
!1020 = !DILocation(line: 788, column: 31, scope: !327)
!1021 = !DILocation(line: 788, column: 2, scope: !1022)
!1022 = !DILexicalBlockFile(scope: !327, file: !1, discriminator: 1)
!1023 = !DILocation(line: 789, column: 25, scope: !327)
!1024 = !DILocation(line: 790, column: 17, scope: !327)
!1025 = !DILocation(line: 790, column: 24, scope: !327)
!1026 = !DILocation(line: 790, column: 11, scope: !327)
!1027 = !DILocation(line: 790, column: 3, scope: !327)
!1028 = !DILocation(line: 789, column: 2, scope: !327)
!1029 = !DILocation(line: 791, column: 24, scope: !327)
!1030 = !DILocation(line: 791, column: 37, scope: !327)
!1031 = !DILocation(line: 791, column: 44, scope: !327)
!1032 = !DILocation(line: 791, column: 31, scope: !327)
!1033 = !DILocation(line: 791, column: 2, scope: !1022)
!1034 = !DILocation(line: 792, column: 24, scope: !327)
!1035 = !DILocation(line: 792, column: 37, scope: !327)
!1036 = !DILocation(line: 792, column: 44, scope: !327)
!1037 = !DILocation(line: 792, column: 31, scope: !327)
!1038 = !DILocation(line: 792, column: 2, scope: !1022)
!1039 = !DILocation(line: 793, column: 26, scope: !327)
!1040 = !DILocation(line: 794, column: 23, scope: !327)
!1041 = !DILocation(line: 794, column: 30, scope: !327)
!1042 = !DILocation(line: 794, column: 17, scope: !327)
!1043 = !DILocation(line: 794, column: 3, scope: !327)
!1044 = !DILocation(line: 793, column: 2, scope: !327)
!1045 = !DILocation(line: 795, column: 25, scope: !327)
!1046 = !DILocation(line: 796, column: 16, scope: !327)
!1047 = !DILocation(line: 796, column: 23, scope: !327)
!1048 = !DILocation(line: 796, column: 10, scope: !327)
!1049 = !DILocation(line: 795, column: 2, scope: !327)
!1050 = !DILocation(line: 797, column: 26, scope: !327)
!1051 = !DILocation(line: 797, column: 39, scope: !327)
!1052 = !DILocation(line: 797, column: 46, scope: !327)
!1053 = !DILocation(line: 797, column: 33, scope: !327)
!1054 = !DILocation(line: 797, column: 2, scope: !1022)
!1055 = !DILocation(line: 798, column: 30, scope: !327)
!1056 = !DILocation(line: 798, column: 37, scope: !327)
!1057 = !DILocation(line: 798, column: 24, scope: !327)
!1058 = !DILocation(line: 798, column: 3, scope: !327)
!1059 = !DILocation(line: 798, column: 14, scope: !327)
!1060 = !DILocation(line: 799, column: 3, scope: !327)
!1061 = !DILocation(line: 799, column: 12, scope: !327)
!1062 = !DILocation(line: 807, column: 12, scope: !327)
!1063 = !DILocation(line: 807, column: 19, scope: !327)
!1064 = !DILocation(line: 807, column: 6, scope: !327)
!1065 = !DILocation(line: 806, column: 2, scope: !327)
!1066 = !DILocation(line: 806, column: 8, scope: !327)
!1067 = !DILocation(line: 806, column: 30, scope: !327)
!1068 = !DILocation(line: 808, column: 25, scope: !327)
!1069 = !DILocation(line: 808, column: 32, scope: !327)
!1070 = !DILocation(line: 808, column: 38, scope: !327)
!1071 = !DILocation(line: 808, column: 2, scope: !327)
!1072 = !DILocation(line: 809, column: 2, scope: !327)
!1073 = !DILocation(line: 809, column: 8, scope: !327)
!1074 = !DILocation(line: 809, column: 22, scope: !327)
!1075 = !DILocation(line: 810, column: 25, scope: !327)
!1076 = !DILocation(line: 810, column: 2, scope: !327)
!1077 = !DILocation(line: 811, column: 10, scope: !327)
!1078 = !DILocation(line: 811, column: 2, scope: !327)
!1079 = !DILocation(line: 812, column: 1, scope: !327)
!1080 = !DILocalVariable(name: "a", arg: 1, scope: !339, file: !1, line: 587, type: !4)
!1081 = !DILocation(line: 587, column: 34, scope: !339)
!1082 = !DILocalVariable(name: "cpio", arg: 2, scope: !339, file: !1, line: 587, type: !292)
!1083 = !DILocation(line: 587, column: 50, scope: !339)
!1084 = !DILocalVariable(name: "entry", arg: 3, scope: !339, file: !1, line: 588, type: !30)
!1085 = !DILocation(line: 588, column: 27, scope: !339)
!1086 = !DILocalVariable(name: "namelength", arg: 4, scope: !339, file: !1, line: 588, type: !65)
!1087 = !DILocation(line: 588, column: 42, scope: !339)
!1088 = !DILocalVariable(name: "name_pad", arg: 5, scope: !339, file: !1, line: 588, type: !65)
!1089 = !DILocation(line: 588, column: 62, scope: !339)
!1090 = !DILocalVariable(name: "h", scope: !339, file: !1, line: 590, type: !43)
!1091 = !DILocation(line: 590, column: 14, scope: !339)
!1092 = !DILocalVariable(name: "header", scope: !339, file: !1, line: 591, type: !80)
!1093 = !DILocation(line: 591, column: 14, scope: !339)
!1094 = !DILocalVariable(name: "r", scope: !339, file: !1, line: 592, type: !23)
!1095 = !DILocation(line: 592, column: 6, scope: !339)
!1096 = !DILocation(line: 594, column: 23, scope: !339)
!1097 = !DILocation(line: 594, column: 6, scope: !339)
!1098 = !DILocation(line: 594, column: 4, scope: !339)
!1099 = !DILocation(line: 595, column: 6, scope: !1100)
!1100 = distinct !DILexicalBlock(scope: !339, file: !1, line: 595, column: 6)
!1101 = !DILocation(line: 595, column: 8, scope: !1100)
!1102 = !DILocation(line: 595, column: 6, scope: !339)
!1103 = !DILocation(line: 596, column: 11, scope: !1100)
!1104 = !DILocation(line: 596, column: 3, scope: !1100)
!1105 = !DILocation(line: 599, column: 27, scope: !339)
!1106 = !DILocation(line: 599, column: 6, scope: !339)
!1107 = !DILocation(line: 599, column: 4, scope: !339)
!1108 = !DILocation(line: 600, column: 6, scope: !1109)
!1109 = distinct !DILexicalBlock(scope: !339, file: !1, line: 600, column: 6)
!1110 = !DILocation(line: 600, column: 8, scope: !1109)
!1111 = !DILocation(line: 600, column: 6, scope: !339)
!1112 = !DILocation(line: 601, column: 6, scope: !1109)
!1113 = !DILocation(line: 604, column: 25, scope: !339)
!1114 = !DILocation(line: 604, column: 9, scope: !339)
!1115 = !DILocation(line: 606, column: 13, scope: !1116)
!1116 = distinct !DILexicalBlock(scope: !339, file: !1, line: 606, column: 6)
!1117 = !DILocation(line: 606, column: 20, scope: !1116)
!1118 = !DILocation(line: 606, column: 6, scope: !1116)
!1119 = !DILocation(line: 606, column: 54, scope: !1116)
!1120 = !DILocation(line: 606, column: 6, scope: !339)
!1121 = !DILocation(line: 607, column: 3, scope: !1122)
!1122 = distinct !DILexicalBlock(scope: !1116, file: !1, line: 606, column: 60)
!1123 = !DILocation(line: 607, column: 6, scope: !1122)
!1124 = !DILocation(line: 607, column: 14, scope: !1122)
!1125 = !DILocation(line: 607, column: 29, scope: !1122)
!1126 = !DILocation(line: 608, column: 3, scope: !1122)
!1127 = !DILocation(line: 608, column: 6, scope: !1122)
!1128 = !DILocation(line: 608, column: 14, scope: !1122)
!1129 = !DILocation(line: 608, column: 34, scope: !1122)
!1130 = !DILocation(line: 609, column: 2, scope: !1122)
!1131 = !DILocation(line: 609, column: 20, scope: !1132)
!1132 = !DILexicalBlockFile(scope: !1133, file: !1, discriminator: 1)
!1133 = distinct !DILexicalBlock(scope: !1116, file: !1, line: 609, column: 13)
!1134 = !DILocation(line: 609, column: 27, scope: !1132)
!1135 = !DILocation(line: 609, column: 13, scope: !1132)
!1136 = !DILocation(line: 609, column: 61, scope: !1132)
!1137 = !DILocation(line: 610, column: 3, scope: !1138)
!1138 = distinct !DILexicalBlock(scope: !1133, file: !1, line: 609, column: 67)
!1139 = !DILocation(line: 610, column: 6, scope: !1138)
!1140 = !DILocation(line: 610, column: 14, scope: !1138)
!1141 = !DILocation(line: 610, column: 29, scope: !1138)
!1142 = !DILocation(line: 611, column: 3, scope: !1138)
!1143 = !DILocation(line: 611, column: 6, scope: !1138)
!1144 = !DILocation(line: 611, column: 14, scope: !1138)
!1145 = !DILocation(line: 611, column: 34, scope: !1138)
!1146 = !DILocation(line: 612, column: 2, scope: !1138)
!1147 = !DILocation(line: 616, column: 29, scope: !339)
!1148 = !DILocation(line: 617, column: 17, scope: !339)
!1149 = !DILocation(line: 617, column: 24, scope: !339)
!1150 = !DILocation(line: 617, column: 10, scope: !339)
!1151 = !DILocation(line: 616, column: 2, scope: !339)
!1152 = !DILocation(line: 618, column: 29, scope: !339)
!1153 = !DILocation(line: 619, column: 17, scope: !339)
!1154 = !DILocation(line: 619, column: 24, scope: !339)
!1155 = !DILocation(line: 619, column: 10, scope: !339)
!1156 = !DILocation(line: 618, column: 2, scope: !339)
!1157 = !DILocation(line: 620, column: 24, scope: !339)
!1158 = !DILocation(line: 620, column: 38, scope: !339)
!1159 = !DILocation(line: 620, column: 45, scope: !339)
!1160 = !DILocation(line: 620, column: 31, scope: !339)
!1161 = !DILocation(line: 620, column: 2, scope: !1162)
!1162 = !DILexicalBlockFile(scope: !339, file: !1, discriminator: 1)
!1163 = !DILocation(line: 621, column: 25, scope: !339)
!1164 = !DILocation(line: 622, column: 18, scope: !339)
!1165 = !DILocation(line: 622, column: 25, scope: !339)
!1166 = !DILocation(line: 622, column: 11, scope: !339)
!1167 = !DILocation(line: 622, column: 3, scope: !339)
!1168 = !DILocation(line: 621, column: 2, scope: !339)
!1169 = !DILocation(line: 623, column: 24, scope: !339)
!1170 = !DILocation(line: 623, column: 38, scope: !339)
!1171 = !DILocation(line: 623, column: 45, scope: !339)
!1172 = !DILocation(line: 623, column: 31, scope: !339)
!1173 = !DILocation(line: 623, column: 2, scope: !1162)
!1174 = !DILocation(line: 624, column: 24, scope: !339)
!1175 = !DILocation(line: 624, column: 38, scope: !339)
!1176 = !DILocation(line: 624, column: 45, scope: !339)
!1177 = !DILocation(line: 624, column: 31, scope: !339)
!1178 = !DILocation(line: 624, column: 2, scope: !1162)
!1179 = !DILocation(line: 625, column: 26, scope: !339)
!1180 = !DILocation(line: 626, column: 24, scope: !339)
!1181 = !DILocation(line: 626, column: 31, scope: !339)
!1182 = !DILocation(line: 626, column: 17, scope: !339)
!1183 = !DILocation(line: 626, column: 3, scope: !339)
!1184 = !DILocation(line: 625, column: 2, scope: !339)
!1185 = !DILocation(line: 627, column: 30, scope: !339)
!1186 = !DILocation(line: 628, column: 17, scope: !339)
!1187 = !DILocation(line: 628, column: 24, scope: !339)
!1188 = !DILocation(line: 628, column: 10, scope: !339)
!1189 = !DILocation(line: 627, column: 2, scope: !339)
!1190 = !DILocation(line: 629, column: 30, scope: !339)
!1191 = !DILocation(line: 630, column: 17, scope: !339)
!1192 = !DILocation(line: 630, column: 24, scope: !339)
!1193 = !DILocation(line: 630, column: 10, scope: !339)
!1194 = !DILocation(line: 629, column: 2, scope: !339)
!1195 = !DILocation(line: 631, column: 26, scope: !339)
!1196 = !DILocation(line: 631, column: 40, scope: !339)
!1197 = !DILocation(line: 631, column: 47, scope: !339)
!1198 = !DILocation(line: 631, column: 33, scope: !339)
!1199 = !DILocation(line: 631, column: 2, scope: !1162)
!1200 = !DILocation(line: 632, column: 31, scope: !339)
!1201 = !DILocation(line: 632, column: 38, scope: !339)
!1202 = !DILocation(line: 632, column: 24, scope: !339)
!1203 = !DILocation(line: 632, column: 3, scope: !339)
!1204 = !DILocation(line: 632, column: 14, scope: !339)
!1205 = !DILocation(line: 634, column: 20, scope: !339)
!1206 = !DILocation(line: 634, column: 19, scope: !339)
!1207 = !DILocation(line: 634, column: 17, scope: !339)
!1208 = !DILocation(line: 634, column: 32, scope: !339)
!1209 = !DILocation(line: 634, column: 3, scope: !339)
!1210 = !DILocation(line: 634, column: 12, scope: !339)
!1211 = !DILocation(line: 642, column: 13, scope: !339)
!1212 = !DILocation(line: 642, column: 20, scope: !339)
!1213 = !DILocation(line: 642, column: 6, scope: !339)
!1214 = !DILocation(line: 641, column: 2, scope: !339)
!1215 = !DILocation(line: 641, column: 8, scope: !339)
!1216 = !DILocation(line: 641, column: 30, scope: !339)
!1217 = !DILocation(line: 643, column: 25, scope: !339)
!1218 = !DILocation(line: 643, column: 32, scope: !339)
!1219 = !DILocation(line: 643, column: 38, scope: !339)
!1220 = !DILocation(line: 643, column: 2, scope: !339)
!1221 = !DILocation(line: 645, column: 29, scope: !339)
!1222 = !DILocation(line: 645, column: 35, scope: !339)
!1223 = !DILocation(line: 645, column: 28, scope: !339)
!1224 = !DILocation(line: 645, column: 26, scope: !339)
!1225 = !DILocation(line: 645, column: 2, scope: !339)
!1226 = !DILocation(line: 645, column: 8, scope: !339)
!1227 = !DILocation(line: 645, column: 22, scope: !339)
!1228 = !DILocation(line: 646, column: 25, scope: !339)
!1229 = !DILocation(line: 646, column: 2, scope: !339)
!1230 = !DILocation(line: 647, column: 10, scope: !339)
!1231 = !DILocation(line: 647, column: 2, scope: !339)
!1232 = !DILocation(line: 648, column: 1, scope: !339)
!1233 = !DILocalVariable(name: "a", arg: 1, scope: !341, file: !1, line: 903, type: !4)
!1234 = !DILocation(line: 903, column: 36, scope: !341)
!1235 = !DILocalVariable(name: "cpio", arg: 2, scope: !341, file: !1, line: 903, type: !292)
!1236 = !DILocation(line: 903, column: 52, scope: !341)
!1237 = !DILocalVariable(name: "entry", arg: 3, scope: !341, file: !1, line: 904, type: !30)
!1238 = !DILocation(line: 904, column: 27, scope: !341)
!1239 = !DILocalVariable(name: "namelength", arg: 4, scope: !341, file: !1, line: 904, type: !65)
!1240 = !DILocation(line: 904, column: 42, scope: !341)
!1241 = !DILocalVariable(name: "name_pad", arg: 5, scope: !341, file: !1, line: 904, type: !65)
!1242 = !DILocation(line: 904, column: 62, scope: !341)
!1243 = !DILocalVariable(name: "h", scope: !341, file: !1, line: 906, type: !43)
!1244 = !DILocation(line: 906, column: 14, scope: !341)
!1245 = !DILocalVariable(name: "header", scope: !341, file: !1, line: 907, type: !321)
!1246 = !DILocation(line: 907, column: 23, scope: !341)
!1247 = !DILocation(line: 909, column: 2, scope: !341)
!1248 = !DILocation(line: 909, column: 5, scope: !341)
!1249 = !DILocation(line: 909, column: 13, scope: !341)
!1250 = !DILocation(line: 909, column: 28, scope: !341)
!1251 = !DILocation(line: 910, column: 2, scope: !341)
!1252 = !DILocation(line: 910, column: 5, scope: !341)
!1253 = !DILocation(line: 910, column: 13, scope: !341)
!1254 = !DILocation(line: 910, column: 33, scope: !341)
!1255 = !DILocation(line: 913, column: 27, scope: !341)
!1256 = !DILocation(line: 913, column: 6, scope: !341)
!1257 = !DILocation(line: 913, column: 4, scope: !341)
!1258 = !DILocation(line: 914, column: 6, scope: !1259)
!1259 = distinct !DILexicalBlock(scope: !341, file: !1, line: 914, column: 6)
!1260 = !DILocation(line: 914, column: 8, scope: !1259)
!1261 = !DILocation(line: 914, column: 6, scope: !341)
!1262 = !DILocation(line: 915, column: 25, scope: !1263)
!1263 = distinct !DILexicalBlock(scope: !1259, file: !1, line: 914, column: 17)
!1264 = !DILocation(line: 915, column: 28, scope: !1263)
!1265 = !DILocation(line: 915, column: 6, scope: !1263)
!1266 = !DILocation(line: 917, column: 6, scope: !1263)
!1267 = !DILocation(line: 921, column: 34, scope: !341)
!1268 = !DILocation(line: 921, column: 9, scope: !341)
!1269 = !DILocation(line: 923, column: 24, scope: !341)
!1270 = !DILocation(line: 923, column: 31, scope: !341)
!1271 = !DILocation(line: 923, column: 54, scope: !341)
!1272 = !DILocation(line: 923, column: 62, scope: !341)
!1273 = !DILocation(line: 923, column: 60, scope: !341)
!1274 = !DILocation(line: 923, column: 2, scope: !341)
!1275 = !DILocation(line: 924, column: 24, scope: !341)
!1276 = !DILocation(line: 924, column: 31, scope: !341)
!1277 = !DILocation(line: 924, column: 54, scope: !341)
!1278 = !DILocation(line: 924, column: 62, scope: !341)
!1279 = !DILocation(line: 924, column: 60, scope: !341)
!1280 = !DILocation(line: 924, column: 2, scope: !341)
!1281 = !DILocation(line: 925, column: 25, scope: !341)
!1282 = !DILocation(line: 925, column: 32, scope: !341)
!1283 = !DILocation(line: 925, column: 56, scope: !341)
!1284 = !DILocation(line: 925, column: 64, scope: !341)
!1285 = !DILocation(line: 925, column: 62, scope: !341)
!1286 = !DILocation(line: 925, column: 2, scope: !341)
!1287 = !DILocation(line: 926, column: 24, scope: !341)
!1288 = !DILocation(line: 926, column: 31, scope: !341)
!1289 = !DILocation(line: 926, column: 54, scope: !341)
!1290 = !DILocation(line: 926, column: 62, scope: !341)
!1291 = !DILocation(line: 926, column: 60, scope: !341)
!1292 = !DILocation(line: 926, column: 2, scope: !341)
!1293 = !DILocation(line: 927, column: 24, scope: !341)
!1294 = !DILocation(line: 927, column: 31, scope: !341)
!1295 = !DILocation(line: 927, column: 54, scope: !341)
!1296 = !DILocation(line: 927, column: 62, scope: !341)
!1297 = !DILocation(line: 927, column: 60, scope: !341)
!1298 = !DILocation(line: 927, column: 2, scope: !341)
!1299 = !DILocation(line: 928, column: 26, scope: !341)
!1300 = !DILocation(line: 928, column: 33, scope: !341)
!1301 = !DILocation(line: 928, column: 58, scope: !341)
!1302 = !DILocation(line: 928, column: 66, scope: !341)
!1303 = !DILocation(line: 928, column: 64, scope: !341)
!1304 = !DILocation(line: 928, column: 2, scope: !341)
!1305 = !DILocation(line: 929, column: 25, scope: !341)
!1306 = !DILocation(line: 929, column: 32, scope: !341)
!1307 = !DILocation(line: 929, column: 56, scope: !341)
!1308 = !DILocation(line: 929, column: 64, scope: !341)
!1309 = !DILocation(line: 929, column: 62, scope: !341)
!1310 = !DILocation(line: 929, column: 2, scope: !341)
!1311 = !DILocation(line: 930, column: 26, scope: !341)
!1312 = !DILocation(line: 930, column: 37, scope: !341)
!1313 = !DILocation(line: 930, column: 44, scope: !341)
!1314 = !DILocation(line: 930, column: 33, scope: !341)
!1315 = !DILocation(line: 930, column: 2, scope: !1316)
!1316 = !DILexicalBlockFile(scope: !341, file: !1, discriminator: 1)
!1317 = !DILocation(line: 931, column: 16, scope: !341)
!1318 = !DILocation(line: 931, column: 44, scope: !341)
!1319 = !DILocation(line: 931, column: 52, scope: !341)
!1320 = !DILocation(line: 931, column: 50, scope: !341)
!1321 = !DILocation(line: 931, column: 3, scope: !341)
!1322 = !DILocation(line: 931, column: 14, scope: !341)
!1323 = !DILocation(line: 932, column: 15, scope: !341)
!1324 = !DILocation(line: 932, column: 14, scope: !341)
!1325 = !DILocation(line: 932, column: 26, scope: !341)
!1326 = !DILocation(line: 932, column: 3, scope: !341)
!1327 = !DILocation(line: 932, column: 12, scope: !341)
!1328 = !DILocation(line: 934, column: 36, scope: !341)
!1329 = !DILocation(line: 934, column: 43, scope: !341)
!1330 = !DILocation(line: 934, column: 32, scope: !341)
!1331 = !DILocation(line: 934, column: 2, scope: !341)
!1332 = !DILocation(line: 934, column: 8, scope: !341)
!1333 = !DILocation(line: 934, column: 30, scope: !341)
!1334 = !DILocation(line: 935, column: 25, scope: !341)
!1335 = !DILocation(line: 935, column: 32, scope: !341)
!1336 = !DILocation(line: 935, column: 38, scope: !341)
!1337 = !DILocation(line: 935, column: 2, scope: !341)
!1338 = !DILocation(line: 936, column: 24, scope: !341)
!1339 = !DILocation(line: 936, column: 30, scope: !341)
!1340 = !DILocation(line: 936, column: 52, scope: !341)
!1341 = !DILocation(line: 936, column: 2, scope: !341)
!1342 = !DILocation(line: 936, column: 8, scope: !341)
!1343 = !DILocation(line: 936, column: 22, scope: !341)
!1344 = !DILocation(line: 937, column: 29, scope: !341)
!1345 = !DILocation(line: 937, column: 6, scope: !341)
!1346 = !DILocation(line: 938, column: 2, scope: !341)
!1347 = !DILocation(line: 939, column: 1, scope: !341)
!1348 = !DILocalVariable(name: "a", arg: 1, scope: !345, file: !1, line: 864, type: !4)
!1349 = !DILocation(line: 864, column: 36, scope: !345)
!1350 = !DILocalVariable(name: "cpio", arg: 2, scope: !345, file: !1, line: 864, type: !292)
!1351 = !DILocation(line: 864, column: 52, scope: !345)
!1352 = !DILocalVariable(name: "entry", arg: 3, scope: !345, file: !1, line: 865, type: !30)
!1353 = !DILocation(line: 865, column: 27, scope: !345)
!1354 = !DILocalVariable(name: "namelength", arg: 4, scope: !345, file: !1, line: 865, type: !65)
!1355 = !DILocation(line: 865, column: 42, scope: !345)
!1356 = !DILocalVariable(name: "name_pad", arg: 5, scope: !345, file: !1, line: 865, type: !65)
!1357 = !DILocation(line: 865, column: 62, scope: !345)
!1358 = !DILocalVariable(name: "h", scope: !345, file: !1, line: 867, type: !43)
!1359 = !DILocation(line: 867, column: 14, scope: !345)
!1360 = !DILocalVariable(name: "header", scope: !345, file: !1, line: 868, type: !321)
!1361 = !DILocation(line: 868, column: 23, scope: !345)
!1362 = !DILocation(line: 870, column: 2, scope: !345)
!1363 = !DILocation(line: 870, column: 5, scope: !345)
!1364 = !DILocation(line: 870, column: 13, scope: !345)
!1365 = !DILocation(line: 870, column: 28, scope: !345)
!1366 = !DILocation(line: 871, column: 2, scope: !345)
!1367 = !DILocation(line: 871, column: 5, scope: !345)
!1368 = !DILocation(line: 871, column: 13, scope: !345)
!1369 = !DILocation(line: 871, column: 33, scope: !345)
!1370 = !DILocation(line: 874, column: 27, scope: !345)
!1371 = !DILocation(line: 874, column: 6, scope: !345)
!1372 = !DILocation(line: 874, column: 4, scope: !345)
!1373 = !DILocation(line: 875, column: 6, scope: !1374)
!1374 = distinct !DILexicalBlock(scope: !345, file: !1, line: 875, column: 6)
!1375 = !DILocation(line: 875, column: 8, scope: !1374)
!1376 = !DILocation(line: 875, column: 6, scope: !345)
!1377 = !DILocation(line: 876, column: 25, scope: !1378)
!1378 = distinct !DILexicalBlock(scope: !1374, file: !1, line: 875, column: 17)
!1379 = !DILocation(line: 876, column: 28, scope: !1378)
!1380 = !DILocation(line: 876, column: 6, scope: !1378)
!1381 = !DILocation(line: 878, column: 6, scope: !1378)
!1382 = !DILocation(line: 882, column: 34, scope: !345)
!1383 = !DILocation(line: 882, column: 9, scope: !345)
!1384 = !DILocation(line: 884, column: 24, scope: !345)
!1385 = !DILocation(line: 884, column: 31, scope: !345)
!1386 = !DILocation(line: 884, column: 56, scope: !345)
!1387 = !DILocation(line: 884, column: 83, scope: !345)
!1388 = !DILocation(line: 884, column: 54, scope: !345)
!1389 = !DILocation(line: 884, column: 2, scope: !345)
!1390 = !DILocation(line: 885, column: 24, scope: !345)
!1391 = !DILocation(line: 885, column: 31, scope: !345)
!1392 = !DILocation(line: 885, column: 56, scope: !345)
!1393 = !DILocation(line: 885, column: 83, scope: !345)
!1394 = !DILocation(line: 885, column: 54, scope: !345)
!1395 = !DILocation(line: 885, column: 2, scope: !345)
!1396 = !DILocation(line: 886, column: 25, scope: !345)
!1397 = !DILocation(line: 886, column: 32, scope: !345)
!1398 = !DILocation(line: 886, column: 58, scope: !345)
!1399 = !DILocation(line: 886, column: 86, scope: !345)
!1400 = !DILocation(line: 886, column: 56, scope: !345)
!1401 = !DILocation(line: 886, column: 2, scope: !345)
!1402 = !DILocation(line: 887, column: 24, scope: !345)
!1403 = !DILocation(line: 887, column: 31, scope: !345)
!1404 = !DILocation(line: 887, column: 56, scope: !345)
!1405 = !DILocation(line: 887, column: 83, scope: !345)
!1406 = !DILocation(line: 887, column: 54, scope: !345)
!1407 = !DILocation(line: 887, column: 2, scope: !345)
!1408 = !DILocation(line: 888, column: 24, scope: !345)
!1409 = !DILocation(line: 888, column: 31, scope: !345)
!1410 = !DILocation(line: 888, column: 56, scope: !345)
!1411 = !DILocation(line: 888, column: 83, scope: !345)
!1412 = !DILocation(line: 888, column: 54, scope: !345)
!1413 = !DILocation(line: 888, column: 2, scope: !345)
!1414 = !DILocation(line: 889, column: 26, scope: !345)
!1415 = !DILocation(line: 889, column: 33, scope: !345)
!1416 = !DILocation(line: 889, column: 60, scope: !345)
!1417 = !DILocation(line: 889, column: 89, scope: !345)
!1418 = !DILocation(line: 889, column: 58, scope: !345)
!1419 = !DILocation(line: 889, column: 2, scope: !345)
!1420 = !DILocation(line: 890, column: 25, scope: !345)
!1421 = !DILocation(line: 890, column: 32, scope: !345)
!1422 = !DILocation(line: 890, column: 58, scope: !345)
!1423 = !DILocation(line: 890, column: 86, scope: !345)
!1424 = !DILocation(line: 890, column: 56, scope: !345)
!1425 = !DILocation(line: 890, column: 2, scope: !345)
!1426 = !DILocation(line: 891, column: 26, scope: !345)
!1427 = !DILocation(line: 891, column: 37, scope: !345)
!1428 = !DILocation(line: 891, column: 44, scope: !345)
!1429 = !DILocation(line: 891, column: 33, scope: !345)
!1430 = !DILocation(line: 891, column: 2, scope: !1431)
!1431 = !DILexicalBlockFile(scope: !345, file: !1, discriminator: 1)
!1432 = !DILocation(line: 892, column: 16, scope: !345)
!1433 = !DILocation(line: 892, column: 46, scope: !345)
!1434 = !DILocation(line: 892, column: 78, scope: !345)
!1435 = !DILocation(line: 892, column: 44, scope: !345)
!1436 = !DILocation(line: 892, column: 3, scope: !345)
!1437 = !DILocation(line: 892, column: 14, scope: !345)
!1438 = !DILocation(line: 893, column: 15, scope: !345)
!1439 = !DILocation(line: 893, column: 14, scope: !345)
!1440 = !DILocation(line: 893, column: 26, scope: !345)
!1441 = !DILocation(line: 893, column: 3, scope: !345)
!1442 = !DILocation(line: 893, column: 12, scope: !345)
!1443 = !DILocation(line: 895, column: 36, scope: !345)
!1444 = !DILocation(line: 895, column: 43, scope: !345)
!1445 = !DILocation(line: 895, column: 32, scope: !345)
!1446 = !DILocation(line: 895, column: 2, scope: !345)
!1447 = !DILocation(line: 895, column: 8, scope: !345)
!1448 = !DILocation(line: 895, column: 30, scope: !345)
!1449 = !DILocation(line: 896, column: 25, scope: !345)
!1450 = !DILocation(line: 896, column: 32, scope: !345)
!1451 = !DILocation(line: 896, column: 38, scope: !345)
!1452 = !DILocation(line: 896, column: 2, scope: !345)
!1453 = !DILocation(line: 897, column: 24, scope: !345)
!1454 = !DILocation(line: 897, column: 30, scope: !345)
!1455 = !DILocation(line: 897, column: 52, scope: !345)
!1456 = !DILocation(line: 897, column: 2, scope: !345)
!1457 = !DILocation(line: 897, column: 8, scope: !345)
!1458 = !DILocation(line: 897, column: 22, scope: !345)
!1459 = !DILocation(line: 898, column: 25, scope: !345)
!1460 = !DILocation(line: 898, column: 2, scope: !345)
!1461 = !DILocation(line: 899, column: 2, scope: !345)
!1462 = !DILocation(line: 900, column: 1, scope: !345)
!1463 = !DILocalVariable(name: "a", arg: 1, scope: !328, file: !1, line: 689, type: !4)
!1464 = !DILocation(line: 689, column: 38, scope: !328)
!1465 = !DILocalVariable(name: "h", scope: !328, file: !1, line: 691, type: !43)
!1466 = !DILocation(line: 691, column: 14, scope: !328)
!1467 = !DILocalVariable(name: "p", scope: !328, file: !1, line: 692, type: !80)
!1468 = !DILocation(line: 692, column: 14, scope: !328)
!1469 = !DILocalVariable(name: "q", scope: !328, file: !1, line: 692, type: !80)
!1470 = !DILocation(line: 692, column: 18, scope: !328)
!1471 = !DILocalVariable(name: "skip", scope: !328, file: !1, line: 693, type: !45)
!1472 = !DILocation(line: 693, column: 9, scope: !328)
!1473 = !DILocalVariable(name: "skipped", scope: !328, file: !1, line: 693, type: !45)
!1474 = !DILocation(line: 693, column: 15, scope: !328)
!1475 = !DILocalVariable(name: "bytes", scope: !328, file: !1, line: 694, type: !38)
!1476 = !DILocation(line: 694, column: 10, scope: !328)
!1477 = !DILocation(line: 696, column: 2, scope: !328)
!1478 = !DILocation(line: 697, column: 28, scope: !1479)
!1479 = distinct !DILexicalBlock(scope: !1480, file: !1, line: 696, column: 11)
!1480 = distinct !DILexicalBlock(scope: !1481, file: !1, line: 696, column: 2)
!1481 = distinct !DILexicalBlock(scope: !328, file: !1, line: 696, column: 2)
!1482 = !DILocation(line: 697, column: 7, scope: !1479)
!1483 = !DILocation(line: 697, column: 5, scope: !1479)
!1484 = !DILocation(line: 698, column: 7, scope: !1485)
!1485 = distinct !DILexicalBlock(scope: !1479, file: !1, line: 698, column: 7)
!1486 = !DILocation(line: 698, column: 9, scope: !1485)
!1487 = !DILocation(line: 698, column: 7, scope: !1479)
!1488 = !DILocation(line: 699, column: 4, scope: !1485)
!1489 = !DILocation(line: 700, column: 7, scope: !1479)
!1490 = !DILocation(line: 700, column: 5, scope: !1479)
!1491 = !DILocation(line: 701, column: 7, scope: !1479)
!1492 = !DILocation(line: 701, column: 11, scope: !1479)
!1493 = !DILocation(line: 701, column: 9, scope: !1479)
!1494 = !DILocation(line: 701, column: 5, scope: !1479)
!1495 = !DILocation(line: 704, column: 24, scope: !1496)
!1496 = distinct !DILexicalBlock(scope: !1479, file: !1, line: 704, column: 7)
!1497 = !DILocation(line: 704, column: 7, scope: !1496)
!1498 = !DILocation(line: 704, column: 30, scope: !1496)
!1499 = !DILocation(line: 704, column: 35, scope: !1496)
!1500 = !DILocation(line: 704, column: 47, scope: !1501)
!1501 = !DILexicalBlockFile(scope: !1496, file: !1, discriminator: 1)
!1502 = !DILocation(line: 704, column: 38, scope: !1501)
!1503 = !DILocation(line: 704, column: 7, scope: !1501)
!1504 = !DILocation(line: 705, column: 4, scope: !1496)
!1505 = !DILocation(line: 706, column: 24, scope: !1506)
!1506 = distinct !DILexicalBlock(scope: !1479, file: !1, line: 706, column: 7)
!1507 = !DILocation(line: 706, column: 7, scope: !1506)
!1508 = !DILocation(line: 706, column: 30, scope: !1506)
!1509 = !DILocation(line: 706, column: 35, scope: !1506)
!1510 = !DILocation(line: 706, column: 52, scope: !1511)
!1511 = !DILexicalBlockFile(scope: !1506, file: !1, discriminator: 1)
!1512 = !DILocation(line: 706, column: 55, scope: !1511)
!1513 = !DILocation(line: 706, column: 38, scope: !1511)
!1514 = !DILocation(line: 706, column: 7, scope: !1511)
!1515 = !DILocation(line: 707, column: 4, scope: !1516)
!1516 = distinct !DILexicalBlock(scope: !1506, file: !1, line: 706, column: 63)
!1517 = !DILocation(line: 707, column: 7, scope: !1516)
!1518 = !DILocation(line: 707, column: 15, scope: !1516)
!1519 = !DILocation(line: 707, column: 30, scope: !1516)
!1520 = !DILocation(line: 708, column: 4, scope: !1516)
!1521 = !DILocation(line: 715, column: 3, scope: !1479)
!1522 = !DILocation(line: 715, column: 10, scope: !1523)
!1523 = !DILexicalBlockFile(scope: !1479, file: !1, discriminator: 1)
!1524 = !DILocation(line: 715, column: 12, scope: !1523)
!1525 = !DILocation(line: 715, column: 33, scope: !1523)
!1526 = !DILocation(line: 715, column: 30, scope: !1523)
!1527 = !DILocation(line: 715, column: 3, scope: !1523)
!1528 = !DILocation(line: 716, column: 12, scope: !1529)
!1529 = distinct !DILexicalBlock(scope: !1479, file: !1, line: 715, column: 36)
!1530 = !DILocation(line: 716, column: 4, scope: !1529)
!1531 = !DILocation(line: 718, column: 27, scope: !1532)
!1532 = distinct !DILexicalBlock(scope: !1533, file: !1, line: 718, column: 9)
!1533 = distinct !DILexicalBlock(scope: !1529, file: !1, line: 716, column: 18)
!1534 = !DILocation(line: 718, column: 10, scope: !1532)
!1535 = !DILocation(line: 718, column: 33, scope: !1532)
!1536 = !DILocation(line: 719, column: 9, scope: !1532)
!1537 = !DILocation(line: 719, column: 21, scope: !1538)
!1538 = !DILexicalBlockFile(scope: !1532, file: !1, discriminator: 1)
!1539 = !DILocation(line: 719, column: 12, scope: !1538)
!1540 = !DILocation(line: 720, column: 9, scope: !1532)
!1541 = !DILocation(line: 720, column: 30, scope: !1538)
!1542 = !DILocation(line: 720, column: 13, scope: !1538)
!1543 = !DILocation(line: 720, column: 36, scope: !1538)
!1544 = !DILocation(line: 721, column: 13, scope: !1532)
!1545 = !DILocation(line: 721, column: 30, scope: !1538)
!1546 = !DILocation(line: 721, column: 33, scope: !1538)
!1547 = !DILocation(line: 721, column: 37, scope: !1538)
!1548 = !DILocation(line: 721, column: 35, scope: !1538)
!1549 = !DILocation(line: 721, column: 16, scope: !1538)
!1550 = !DILocation(line: 718, column: 9, scope: !1551)
!1551 = !DILexicalBlockFile(scope: !1533, file: !1, discriminator: 1)
!1552 = !DILocation(line: 722, column: 13, scope: !1553)
!1553 = distinct !DILexicalBlock(scope: !1532, file: !1, line: 721, column: 42)
!1554 = !DILocation(line: 722, column: 31, scope: !1553)
!1555 = !DILocation(line: 722, column: 15, scope: !1553)
!1556 = !DILocation(line: 722, column: 11, scope: !1553)
!1557 = !DILocation(line: 723, column: 29, scope: !1553)
!1558 = !DILocation(line: 723, column: 32, scope: !1553)
!1559 = !DILocation(line: 723, column: 6, scope: !1553)
!1560 = !DILocation(line: 724, column: 17, scope: !1553)
!1561 = !DILocation(line: 724, column: 14, scope: !1553)
!1562 = !DILocation(line: 725, column: 10, scope: !1563)
!1563 = distinct !DILexicalBlock(scope: !1553, file: !1, line: 725, column: 10)
!1564 = !DILocation(line: 725, column: 15, scope: !1563)
!1565 = !DILocation(line: 725, column: 10, scope: !1553)
!1566 = !DILocation(line: 726, column: 7, scope: !1563)
!1567 = !DILocation(line: 726, column: 10, scope: !1563)
!1568 = !DILocation(line: 726, column: 18, scope: !1563)
!1569 = !DILocation(line: 726, column: 33, scope: !1563)
!1570 = !DILocation(line: 728, column: 10, scope: !1571)
!1571 = distinct !DILexicalBlock(scope: !1553, file: !1, line: 728, column: 10)
!1572 = !DILocation(line: 728, column: 18, scope: !1571)
!1573 = !DILocation(line: 728, column: 10, scope: !1553)
!1574 = !DILocation(line: 729, column: 26, scope: !1575)
!1575 = distinct !DILexicalBlock(scope: !1571, file: !1, line: 728, column: 23)
!1576 = !DILocation(line: 729, column: 29, scope: !1575)
!1577 = !DILocation(line: 733, column: 16, scope: !1575)
!1578 = !DILocation(line: 733, column: 11, scope: !1575)
!1579 = !DILocation(line: 729, column: 7, scope: !1575)
!1580 = !DILocation(line: 734, column: 7, scope: !1575)
!1581 = !DILocation(line: 736, column: 6, scope: !1553)
!1582 = !DILocation(line: 738, column: 7, scope: !1533)
!1583 = !DILocation(line: 739, column: 5, scope: !1533)
!1584 = !DILocation(line: 741, column: 6, scope: !1533)
!1585 = !DILocation(line: 742, column: 5, scope: !1533)
!1586 = !DILocation(line: 744, column: 7, scope: !1533)
!1587 = !DILocation(line: 745, column: 5, scope: !1533)
!1588 = !DILocation(line: 715, column: 3, scope: !1589)
!1589 = !DILexicalBlockFile(scope: !1479, file: !1, discriminator: 2)
!1590 = !DILocation(line: 748, column: 10, scope: !1479)
!1591 = !DILocation(line: 748, column: 28, scope: !1479)
!1592 = !DILocation(line: 748, column: 12, scope: !1479)
!1593 = !DILocation(line: 748, column: 8, scope: !1479)
!1594 = !DILocation(line: 749, column: 26, scope: !1479)
!1595 = !DILocation(line: 749, column: 29, scope: !1479)
!1596 = !DILocation(line: 749, column: 3, scope: !1479)
!1597 = !DILocation(line: 750, column: 14, scope: !1479)
!1598 = !DILocation(line: 750, column: 11, scope: !1479)
!1599 = !DILocation(line: 696, column: 2, scope: !1600)
!1600 = !DILexicalBlockFile(scope: !1480, file: !1, discriminator: 1)
!1601 = !DILocation(line: 752, column: 1, scope: !328)
!1602 = !DILocalVariable(name: "a", arg: 1, scope: !334, file: !1, line: 822, type: !4)
!1603 = !DILocation(line: 822, column: 35, scope: !334)
!1604 = !DILocalVariable(name: "cpio", arg: 2, scope: !334, file: !1, line: 822, type: !292)
!1605 = !DILocation(line: 822, column: 51, scope: !334)
!1606 = !DILocalVariable(name: "entry", arg: 3, scope: !334, file: !1, line: 823, type: !30)
!1607 = !DILocation(line: 823, column: 27, scope: !334)
!1608 = !DILocalVariable(name: "namelength", arg: 4, scope: !334, file: !1, line: 823, type: !65)
!1609 = !DILocation(line: 823, column: 42, scope: !334)
!1610 = !DILocalVariable(name: "name_pad", arg: 5, scope: !334, file: !1, line: 823, type: !65)
!1611 = !DILocation(line: 823, column: 62, scope: !334)
!1612 = !DILocalVariable(name: "h", scope: !334, file: !1, line: 825, type: !43)
!1613 = !DILocation(line: 825, column: 14, scope: !334)
!1614 = !DILocalVariable(name: "header", scope: !334, file: !1, line: 826, type: !80)
!1615 = !DILocation(line: 826, column: 14, scope: !334)
!1616 = !DILocation(line: 828, column: 2, scope: !334)
!1617 = !DILocation(line: 828, column: 5, scope: !334)
!1618 = !DILocation(line: 828, column: 13, scope: !334)
!1619 = !DILocation(line: 828, column: 28, scope: !334)
!1620 = !DILocation(line: 829, column: 2, scope: !334)
!1621 = !DILocation(line: 829, column: 5, scope: !334)
!1622 = !DILocation(line: 829, column: 13, scope: !334)
!1623 = !DILocation(line: 829, column: 33, scope: !334)
!1624 = !DILocation(line: 832, column: 27, scope: !334)
!1625 = !DILocation(line: 832, column: 6, scope: !334)
!1626 = !DILocation(line: 832, column: 4, scope: !334)
!1627 = !DILocation(line: 833, column: 6, scope: !1628)
!1628 = distinct !DILexicalBlock(scope: !334, file: !1, line: 833, column: 6)
!1629 = !DILocation(line: 833, column: 8, scope: !1628)
!1630 = !DILocation(line: 833, column: 6, scope: !334)
!1631 = !DILocation(line: 834, column: 6, scope: !1628)
!1632 = !DILocation(line: 837, column: 25, scope: !334)
!1633 = !DILocation(line: 837, column: 9, scope: !334)
!1634 = !DILocation(line: 839, column: 24, scope: !334)
!1635 = !DILocation(line: 840, column: 17, scope: !334)
!1636 = !DILocation(line: 840, column: 24, scope: !334)
!1637 = !DILocation(line: 840, column: 10, scope: !334)
!1638 = !DILocation(line: 839, column: 2, scope: !334)
!1639 = !DILocation(line: 841, column: 24, scope: !334)
!1640 = !DILocation(line: 841, column: 38, scope: !334)
!1641 = !DILocation(line: 841, column: 45, scope: !334)
!1642 = !DILocation(line: 841, column: 31, scope: !334)
!1643 = !DILocation(line: 841, column: 2, scope: !1644)
!1644 = !DILexicalBlockFile(scope: !334, file: !1, discriminator: 1)
!1645 = !DILocation(line: 842, column: 25, scope: !334)
!1646 = !DILocation(line: 843, column: 17, scope: !334)
!1647 = !DILocation(line: 843, column: 24, scope: !334)
!1648 = !DILocation(line: 843, column: 11, scope: !334)
!1649 = !DILocation(line: 843, column: 3, scope: !334)
!1650 = !DILocation(line: 842, column: 2, scope: !334)
!1651 = !DILocation(line: 844, column: 24, scope: !334)
!1652 = !DILocation(line: 844, column: 38, scope: !334)
!1653 = !DILocation(line: 844, column: 45, scope: !334)
!1654 = !DILocation(line: 844, column: 31, scope: !334)
!1655 = !DILocation(line: 844, column: 2, scope: !1644)
!1656 = !DILocation(line: 845, column: 24, scope: !334)
!1657 = !DILocation(line: 845, column: 38, scope: !334)
!1658 = !DILocation(line: 845, column: 45, scope: !334)
!1659 = !DILocation(line: 845, column: 31, scope: !334)
!1660 = !DILocation(line: 845, column: 2, scope: !1644)
!1661 = !DILocation(line: 846, column: 26, scope: !334)
!1662 = !DILocation(line: 847, column: 24, scope: !334)
!1663 = !DILocation(line: 847, column: 31, scope: !334)
!1664 = !DILocation(line: 847, column: 17, scope: !334)
!1665 = !DILocation(line: 847, column: 3, scope: !334)
!1666 = !DILocation(line: 846, column: 2, scope: !334)
!1667 = !DILocation(line: 848, column: 25, scope: !334)
!1668 = !DILocation(line: 849, column: 17, scope: !334)
!1669 = !DILocation(line: 849, column: 24, scope: !334)
!1670 = !DILocation(line: 849, column: 10, scope: !334)
!1671 = !DILocation(line: 848, column: 2, scope: !334)
!1672 = !DILocation(line: 850, column: 26, scope: !334)
!1673 = !DILocation(line: 850, column: 40, scope: !334)
!1674 = !DILocation(line: 850, column: 47, scope: !334)
!1675 = !DILocation(line: 850, column: 33, scope: !334)
!1676 = !DILocation(line: 850, column: 2, scope: !1644)
!1677 = !DILocation(line: 851, column: 31, scope: !334)
!1678 = !DILocation(line: 851, column: 38, scope: !334)
!1679 = !DILocation(line: 851, column: 24, scope: !334)
!1680 = !DILocation(line: 851, column: 3, scope: !334)
!1681 = !DILocation(line: 851, column: 14, scope: !334)
!1682 = !DILocation(line: 852, column: 3, scope: !334)
!1683 = !DILocation(line: 852, column: 12, scope: !334)
!1684 = !DILocation(line: 855, column: 13, scope: !334)
!1685 = !DILocation(line: 855, column: 20, scope: !334)
!1686 = !DILocation(line: 855, column: 6, scope: !334)
!1687 = !DILocation(line: 854, column: 2, scope: !334)
!1688 = !DILocation(line: 854, column: 8, scope: !334)
!1689 = !DILocation(line: 854, column: 30, scope: !334)
!1690 = !DILocation(line: 856, column: 25, scope: !334)
!1691 = !DILocation(line: 856, column: 32, scope: !334)
!1692 = !DILocation(line: 856, column: 38, scope: !334)
!1693 = !DILocation(line: 856, column: 2, scope: !334)
!1694 = !DILocation(line: 857, column: 2, scope: !334)
!1695 = !DILocation(line: 857, column: 8, scope: !334)
!1696 = !DILocation(line: 857, column: 22, scope: !334)
!1697 = !DILocation(line: 858, column: 25, scope: !334)
!1698 = !DILocation(line: 858, column: 2, scope: !334)
!1699 = !DILocation(line: 859, column: 2, scope: !334)
!1700 = !DILocation(line: 860, column: 1, scope: !334)
!1701 = !DILocalVariable(name: "p", arg: 1, scope: !338, file: !1, line: 980, type: !80)
!1702 = !DILocation(line: 980, column: 19, scope: !338)
!1703 = !DILocalVariable(name: "char_cnt", arg: 2, scope: !338, file: !1, line: 980, type: !13)
!1704 = !DILocation(line: 980, column: 31, scope: !338)
!1705 = !DILocalVariable(name: "l", scope: !338, file: !1, line: 982, type: !52)
!1706 = !DILocation(line: 982, column: 10, scope: !338)
!1707 = !DILocalVariable(name: "digit", scope: !338, file: !1, line: 983, type: !23)
!1708 = !DILocation(line: 983, column: 6, scope: !338)
!1709 = !DILocation(line: 985, column: 4, scope: !338)
!1710 = !DILocation(line: 986, column: 2, scope: !338)
!1711 = !DILocation(line: 986, column: 17, scope: !1712)
!1712 = !DILexicalBlockFile(scope: !338, file: !1, discriminator: 1)
!1713 = !DILocation(line: 986, column: 20, scope: !1712)
!1714 = !DILocation(line: 986, column: 2, scope: !1712)
!1715 = !DILocation(line: 987, column: 8, scope: !1716)
!1716 = distinct !DILexicalBlock(scope: !1717, file: !1, line: 987, column: 7)
!1717 = distinct !DILexicalBlock(scope: !338, file: !1, line: 986, column: 25)
!1718 = !DILocation(line: 987, column: 7, scope: !1716)
!1719 = !DILocation(line: 987, column: 10, scope: !1716)
!1720 = !DILocation(line: 987, column: 17, scope: !1716)
!1721 = !DILocation(line: 987, column: 21, scope: !1722)
!1722 = !DILexicalBlockFile(scope: !1716, file: !1, discriminator: 1)
!1723 = !DILocation(line: 987, column: 20, scope: !1722)
!1724 = !DILocation(line: 987, column: 23, scope: !1722)
!1725 = !DILocation(line: 987, column: 7, scope: !1722)
!1726 = !DILocation(line: 988, column: 13, scope: !1716)
!1727 = !DILocation(line: 988, column: 12, scope: !1716)
!1728 = !DILocation(line: 988, column: 15, scope: !1716)
!1729 = !DILocation(line: 988, column: 10, scope: !1716)
!1730 = !DILocation(line: 988, column: 4, scope: !1716)
!1731 = !DILocation(line: 990, column: 12, scope: !1716)
!1732 = !DILocation(line: 990, column: 4, scope: !1716)
!1733 = !DILocation(line: 991, column: 4, scope: !1717)
!1734 = !DILocation(line: 992, column: 5, scope: !1717)
!1735 = !DILocation(line: 993, column: 8, scope: !1717)
!1736 = !DILocation(line: 993, column: 5, scope: !1717)
!1737 = !DILocation(line: 986, column: 2, scope: !1738)
!1738 = !DILexicalBlockFile(scope: !338, file: !1, discriminator: 2)
!1739 = !DILocation(line: 995, column: 10, scope: !338)
!1740 = !DILocation(line: 995, column: 2, scope: !338)
!1741 = !DILocation(line: 996, column: 1, scope: !338)
!1742 = !DILocalVariable(name: "p", arg: 1, scope: !329, file: !1, line: 657, type: !80)
!1743 = !DILocation(line: 657, column: 22, scope: !329)
!1744 = !DILocalVariable(name: "len", arg: 2, scope: !329, file: !1, line: 657, type: !45)
!1745 = !DILocation(line: 657, column: 32, scope: !329)
!1746 = !DILocation(line: 659, column: 2, scope: !329)
!1747 = !DILocation(line: 659, column: 12, scope: !1748)
!1748 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 1)
!1749 = !DILocation(line: 659, column: 15, scope: !1748)
!1750 = !DILocation(line: 659, column: 2, scope: !1748)
!1751 = !DILocation(line: 660, column: 8, scope: !1752)
!1752 = distinct !DILexicalBlock(scope: !1753, file: !1, line: 660, column: 7)
!1753 = distinct !DILexicalBlock(scope: !329, file: !1, line: 659, column: 20)
!1754 = !DILocation(line: 660, column: 7, scope: !1752)
!1755 = !DILocation(line: 660, column: 10, scope: !1752)
!1756 = !DILocation(line: 660, column: 16, scope: !1752)
!1757 = !DILocation(line: 660, column: 20, scope: !1758)
!1758 = !DILexicalBlockFile(scope: !1752, file: !1, discriminator: 1)
!1759 = !DILocation(line: 660, column: 19, scope: !1758)
!1760 = !DILocation(line: 660, column: 22, scope: !1758)
!1761 = !DILocation(line: 660, column: 7, scope: !1758)
!1762 = !DILocation(line: 661, column: 4, scope: !1752)
!1763 = !DILocation(line: 662, column: 10, scope: !1753)
!1764 = !DILocation(line: 659, column: 2, scope: !1765)
!1765 = !DILexicalBlockFile(scope: !329, file: !1, discriminator: 2)
!1766 = !DILocation(line: 664, column: 2, scope: !329)
!1767 = !DILocation(line: 665, column: 1, scope: !329)
!1768 = !DILocalVariable(name: "h", arg: 1, scope: !332, file: !1, line: 668, type: !80)
!1769 = !DILocation(line: 668, column: 27, scope: !332)
!1770 = !DILocalVariable(name: "len", arg: 2, scope: !332, file: !1, line: 668, type: !45)
!1771 = !DILocation(line: 668, column: 37, scope: !332)
!1772 = !DILocation(line: 670, column: 6, scope: !1773)
!1773 = distinct !DILexicalBlock(scope: !332, file: !1, line: 670, column: 6)
!1774 = !DILocation(line: 670, column: 10, scope: !1773)
!1775 = !DILocation(line: 670, column: 6, scope: !332)
!1776 = !DILocation(line: 671, column: 3, scope: !1773)
!1777 = !DILocation(line: 672, column: 6, scope: !1778)
!1778 = distinct !DILexicalBlock(scope: !332, file: !1, line: 672, column: 6)
!1779 = !DILocation(line: 672, column: 28, scope: !1778)
!1780 = !DILocation(line: 673, column: 6, scope: !1778)
!1781 = !DILocation(line: 673, column: 9, scope: !1782)
!1782 = !DILexicalBlockFile(scope: !1778, file: !1, discriminator: 1)
!1783 = !DILocation(line: 673, column: 33, scope: !1782)
!1784 = !DILocation(line: 674, column: 6, scope: !1778)
!1785 = !DILocation(line: 674, column: 9, scope: !1782)
!1786 = !DILocation(line: 674, column: 33, scope: !1782)
!1787 = !DILocation(line: 675, column: 6, scope: !1778)
!1788 = !DILocation(line: 675, column: 9, scope: !1782)
!1789 = !DILocation(line: 675, column: 36, scope: !1782)
!1790 = !DILocation(line: 672, column: 6, scope: !1791)
!1791 = !DILexicalBlockFile(scope: !332, file: !1, discriminator: 1)
!1792 = !DILocation(line: 676, column: 3, scope: !1778)
!1793 = !DILocation(line: 677, column: 14, scope: !1794)
!1794 = distinct !DILexicalBlock(scope: !332, file: !1, line: 677, column: 6)
!1795 = !DILocation(line: 677, column: 16, scope: !1794)
!1796 = !DILocation(line: 677, column: 7, scope: !1794)
!1797 = !DILocation(line: 677, column: 6, scope: !332)
!1798 = !DILocation(line: 678, column: 3, scope: !1794)
!1799 = !DILocation(line: 679, column: 14, scope: !1800)
!1800 = distinct !DILexicalBlock(scope: !332, file: !1, line: 679, column: 6)
!1801 = !DILocation(line: 679, column: 16, scope: !1800)
!1802 = !DILocation(line: 679, column: 7, scope: !1800)
!1803 = !DILocation(line: 679, column: 6, scope: !332)
!1804 = !DILocation(line: 680, column: 3, scope: !1800)
!1805 = !DILocation(line: 681, column: 14, scope: !1806)
!1806 = distinct !DILexicalBlock(scope: !332, file: !1, line: 681, column: 6)
!1807 = !DILocation(line: 681, column: 16, scope: !1806)
!1808 = !DILocation(line: 681, column: 7, scope: !1806)
!1809 = !DILocation(line: 681, column: 6, scope: !332)
!1810 = !DILocation(line: 682, column: 3, scope: !1806)
!1811 = !DILocation(line: 683, column: 14, scope: !1812)
!1812 = distinct !DILexicalBlock(scope: !332, file: !1, line: 683, column: 6)
!1813 = !DILocation(line: 683, column: 16, scope: !1812)
!1814 = !DILocation(line: 683, column: 7, scope: !1812)
!1815 = !DILocation(line: 683, column: 6, scope: !332)
!1816 = !DILocation(line: 684, column: 3, scope: !1812)
!1817 = !DILocation(line: 685, column: 2, scope: !332)
!1818 = !DILocation(line: 686, column: 1, scope: !332)
!1819 = !DILocalVariable(name: "p", arg: 1, scope: !333, file: !1, line: 513, type: !80)
!1820 = !DILocation(line: 513, column: 20, scope: !333)
!1821 = !DILocalVariable(name: "len", arg: 2, scope: !333, file: !1, line: 513, type: !45)
!1822 = !DILocation(line: 513, column: 30, scope: !333)
!1823 = !DILocation(line: 515, column: 2, scope: !333)
!1824 = !DILocation(line: 515, column: 12, scope: !1825)
!1825 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 1)
!1826 = !DILocation(line: 515, column: 15, scope: !1825)
!1827 = !DILocation(line: 515, column: 2, scope: !1825)
!1828 = !DILocation(line: 516, column: 9, scope: !1829)
!1829 = distinct !DILexicalBlock(scope: !1830, file: !1, line: 516, column: 7)
!1830 = distinct !DILexicalBlock(scope: !333, file: !1, line: 515, column: 20)
!1831 = !DILocation(line: 516, column: 8, scope: !1829)
!1832 = !DILocation(line: 516, column: 11, scope: !1829)
!1833 = !DILocation(line: 516, column: 18, scope: !1829)
!1834 = !DILocation(line: 516, column: 22, scope: !1835)
!1835 = !DILexicalBlockFile(scope: !1829, file: !1, discriminator: 1)
!1836 = !DILocation(line: 516, column: 21, scope: !1835)
!1837 = !DILocation(line: 516, column: 24, scope: !1835)
!1838 = !DILocation(line: 517, column: 7, scope: !1829)
!1839 = !DILocation(line: 517, column: 12, scope: !1835)
!1840 = !DILocation(line: 517, column: 11, scope: !1835)
!1841 = !DILocation(line: 517, column: 14, scope: !1835)
!1842 = !DILocation(line: 517, column: 21, scope: !1835)
!1843 = !DILocation(line: 517, column: 25, scope: !1844)
!1844 = !DILexicalBlockFile(scope: !1829, file: !1, discriminator: 2)
!1845 = !DILocation(line: 517, column: 24, scope: !1844)
!1846 = !DILocation(line: 517, column: 27, scope: !1844)
!1847 = !DILocation(line: 518, column: 7, scope: !1829)
!1848 = !DILocation(line: 518, column: 12, scope: !1835)
!1849 = !DILocation(line: 518, column: 11, scope: !1835)
!1850 = !DILocation(line: 518, column: 14, scope: !1835)
!1851 = !DILocation(line: 518, column: 21, scope: !1835)
!1852 = !DILocation(line: 518, column: 25, scope: !1844)
!1853 = !DILocation(line: 518, column: 24, scope: !1844)
!1854 = !DILocation(line: 518, column: 27, scope: !1844)
!1855 = !DILocation(line: 516, column: 7, scope: !1856)
!1856 = !DILexicalBlockFile(scope: !1830, file: !1, discriminator: 2)
!1857 = !DILocation(line: 519, column: 4, scope: !1829)
!1858 = !DILocation(line: 521, column: 4, scope: !1829)
!1859 = !DILocation(line: 515, column: 2, scope: !1860)
!1860 = !DILexicalBlockFile(scope: !333, file: !1, discriminator: 2)
!1861 = !DILocation(line: 523, column: 2, scope: !333)
!1862 = !DILocation(line: 524, column: 1, scope: !333)
!1863 = !DILocalVariable(name: "p", arg: 1, scope: !335, file: !1, line: 999, type: !80)
!1864 = !DILocation(line: 999, column: 20, scope: !335)
!1865 = !DILocalVariable(name: "char_cnt", arg: 2, scope: !335, file: !1, line: 999, type: !13)
!1866 = !DILocation(line: 999, column: 32, scope: !335)
!1867 = !DILocalVariable(name: "l", scope: !335, file: !1, line: 1001, type: !52)
!1868 = !DILocation(line: 1001, column: 10, scope: !335)
!1869 = !DILocalVariable(name: "digit", scope: !335, file: !1, line: 1002, type: !23)
!1870 = !DILocation(line: 1002, column: 6, scope: !335)
!1871 = !DILocation(line: 1004, column: 4, scope: !335)
!1872 = !DILocation(line: 1005, column: 2, scope: !335)
!1873 = !DILocation(line: 1005, column: 17, scope: !1874)
!1874 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 1)
!1875 = !DILocation(line: 1005, column: 20, scope: !1874)
!1876 = !DILocation(line: 1005, column: 2, scope: !1874)
!1877 = !DILocation(line: 1006, column: 8, scope: !1878)
!1878 = distinct !DILexicalBlock(scope: !1879, file: !1, line: 1006, column: 7)
!1879 = distinct !DILexicalBlock(scope: !335, file: !1, line: 1005, column: 25)
!1880 = !DILocation(line: 1006, column: 7, scope: !1878)
!1881 = !DILocation(line: 1006, column: 10, scope: !1878)
!1882 = !DILocation(line: 1006, column: 17, scope: !1878)
!1883 = !DILocation(line: 1006, column: 21, scope: !1884)
!1884 = !DILexicalBlockFile(scope: !1878, file: !1, discriminator: 1)
!1885 = !DILocation(line: 1006, column: 20, scope: !1884)
!1886 = !DILocation(line: 1006, column: 23, scope: !1884)
!1887 = !DILocation(line: 1006, column: 7, scope: !1884)
!1888 = !DILocation(line: 1007, column: 13, scope: !1878)
!1889 = !DILocation(line: 1007, column: 12, scope: !1878)
!1890 = !DILocation(line: 1007, column: 15, scope: !1878)
!1891 = !DILocation(line: 1007, column: 21, scope: !1878)
!1892 = !DILocation(line: 1007, column: 10, scope: !1878)
!1893 = !DILocation(line: 1007, column: 4, scope: !1878)
!1894 = !DILocation(line: 1008, column: 13, scope: !1895)
!1895 = distinct !DILexicalBlock(scope: !1878, file: !1, line: 1008, column: 12)
!1896 = !DILocation(line: 1008, column: 12, scope: !1895)
!1897 = !DILocation(line: 1008, column: 15, scope: !1895)
!1898 = !DILocation(line: 1008, column: 22, scope: !1895)
!1899 = !DILocation(line: 1008, column: 26, scope: !1900)
!1900 = !DILexicalBlockFile(scope: !1895, file: !1, discriminator: 1)
!1901 = !DILocation(line: 1008, column: 25, scope: !1900)
!1902 = !DILocation(line: 1008, column: 28, scope: !1900)
!1903 = !DILocation(line: 1008, column: 12, scope: !1900)
!1904 = !DILocation(line: 1009, column: 13, scope: !1895)
!1905 = !DILocation(line: 1009, column: 12, scope: !1895)
!1906 = !DILocation(line: 1009, column: 15, scope: !1895)
!1907 = !DILocation(line: 1009, column: 21, scope: !1895)
!1908 = !DILocation(line: 1009, column: 10, scope: !1895)
!1909 = !DILocation(line: 1009, column: 4, scope: !1895)
!1910 = !DILocation(line: 1010, column: 13, scope: !1911)
!1911 = distinct !DILexicalBlock(scope: !1895, file: !1, line: 1010, column: 12)
!1912 = !DILocation(line: 1010, column: 12, scope: !1911)
!1913 = !DILocation(line: 1010, column: 15, scope: !1911)
!1914 = !DILocation(line: 1010, column: 22, scope: !1911)
!1915 = !DILocation(line: 1010, column: 26, scope: !1916)
!1916 = !DILexicalBlockFile(scope: !1911, file: !1, discriminator: 1)
!1917 = !DILocation(line: 1010, column: 25, scope: !1916)
!1918 = !DILocation(line: 1010, column: 28, scope: !1916)
!1919 = !DILocation(line: 1010, column: 12, scope: !1916)
!1920 = !DILocation(line: 1011, column: 13, scope: !1911)
!1921 = !DILocation(line: 1011, column: 12, scope: !1911)
!1922 = !DILocation(line: 1011, column: 15, scope: !1911)
!1923 = !DILocation(line: 1011, column: 10, scope: !1911)
!1924 = !DILocation(line: 1011, column: 4, scope: !1911)
!1925 = !DILocation(line: 1013, column: 12, scope: !1911)
!1926 = !DILocation(line: 1013, column: 4, scope: !1911)
!1927 = !DILocation(line: 1014, column: 4, scope: !1879)
!1928 = !DILocation(line: 1015, column: 5, scope: !1879)
!1929 = !DILocation(line: 1016, column: 8, scope: !1879)
!1930 = !DILocation(line: 1016, column: 5, scope: !1879)
!1931 = !DILocation(line: 1005, column: 2, scope: !1932)
!1932 = !DILexicalBlockFile(scope: !335, file: !1, discriminator: 2)
!1933 = !DILocation(line: 1018, column: 10, scope: !335)
!1934 = !DILocation(line: 1018, column: 2, scope: !335)
!1935 = !DILocation(line: 1019, column: 1, scope: !335)
!1936 = !DILocalVariable(name: "a", arg: 1, scope: !340, file: !1, line: 527, type: !4)
!1937 = !DILocation(line: 527, column: 39, scope: !340)
!1938 = !DILocalVariable(name: "h", scope: !340, file: !1, line: 529, type: !43)
!1939 = !DILocation(line: 529, column: 14, scope: !340)
!1940 = !DILocalVariable(name: "p", scope: !340, file: !1, line: 530, type: !80)
!1941 = !DILocation(line: 530, column: 14, scope: !340)
!1942 = !DILocalVariable(name: "q", scope: !340, file: !1, line: 530, type: !80)
!1943 = !DILocation(line: 530, column: 18, scope: !340)
!1944 = !DILocalVariable(name: "skip", scope: !340, file: !1, line: 531, type: !45)
!1945 = !DILocation(line: 531, column: 9, scope: !340)
!1946 = !DILocalVariable(name: "skipped", scope: !340, file: !1, line: 531, type: !45)
!1947 = !DILocation(line: 531, column: 15, scope: !340)
!1948 = !DILocalVariable(name: "bytes", scope: !340, file: !1, line: 532, type: !38)
!1949 = !DILocation(line: 532, column: 10, scope: !340)
!1950 = !DILocation(line: 534, column: 2, scope: !340)
!1951 = !DILocation(line: 535, column: 28, scope: !1952)
!1952 = distinct !DILexicalBlock(scope: !1953, file: !1, line: 534, column: 11)
!1953 = distinct !DILexicalBlock(scope: !1954, file: !1, line: 534, column: 2)
!1954 = distinct !DILexicalBlock(scope: !340, file: !1, line: 534, column: 2)
!1955 = !DILocation(line: 535, column: 7, scope: !1952)
!1956 = !DILocation(line: 535, column: 5, scope: !1952)
!1957 = !DILocation(line: 536, column: 7, scope: !1958)
!1958 = distinct !DILexicalBlock(scope: !1952, file: !1, line: 536, column: 7)
!1959 = !DILocation(line: 536, column: 9, scope: !1958)
!1960 = !DILocation(line: 536, column: 7, scope: !1952)
!1961 = !DILocation(line: 537, column: 4, scope: !1958)
!1962 = !DILocation(line: 538, column: 7, scope: !1952)
!1963 = !DILocation(line: 538, column: 5, scope: !1952)
!1964 = !DILocation(line: 539, column: 7, scope: !1952)
!1965 = !DILocation(line: 539, column: 11, scope: !1952)
!1966 = !DILocation(line: 539, column: 9, scope: !1952)
!1967 = !DILocation(line: 539, column: 5, scope: !1952)
!1968 = !DILocation(line: 542, column: 23, scope: !1969)
!1969 = distinct !DILexicalBlock(scope: !1952, file: !1, line: 542, column: 7)
!1970 = !DILocation(line: 542, column: 7, scope: !1969)
!1971 = !DILocation(line: 542, column: 29, scope: !1969)
!1972 = !DILocation(line: 543, column: 7, scope: !1969)
!1973 = !DILocation(line: 543, column: 11, scope: !1974)
!1974 = !DILexicalBlockFile(scope: !1969, file: !1, discriminator: 1)
!1975 = !DILocation(line: 543, column: 16, scope: !1974)
!1976 = !DILocation(line: 543, column: 23, scope: !1974)
!1977 = !DILocation(line: 543, column: 26, scope: !1978)
!1978 = !DILexicalBlockFile(scope: !1969, file: !1, discriminator: 2)
!1979 = !DILocation(line: 543, column: 31, scope: !1978)
!1980 = !DILocation(line: 544, column: 7, scope: !1969)
!1981 = !DILocation(line: 544, column: 17, scope: !1974)
!1982 = !DILocation(line: 544, column: 10, scope: !1974)
!1983 = !DILocation(line: 542, column: 7, scope: !1984)
!1984 = !DILexicalBlockFile(scope: !1952, file: !1, discriminator: 1)
!1985 = !DILocation(line: 545, column: 4, scope: !1969)
!1986 = !DILocation(line: 551, column: 3, scope: !1952)
!1987 = !DILocation(line: 551, column: 10, scope: !1984)
!1988 = !DILocation(line: 551, column: 12, scope: !1984)
!1989 = !DILocation(line: 551, column: 34, scope: !1984)
!1990 = !DILocation(line: 551, column: 31, scope: !1984)
!1991 = !DILocation(line: 551, column: 3, scope: !1984)
!1992 = !DILocation(line: 552, column: 12, scope: !1993)
!1993 = distinct !DILexicalBlock(scope: !1952, file: !1, line: 551, column: 37)
!1994 = !DILocation(line: 552, column: 4, scope: !1993)
!1995 = !DILocation(line: 555, column: 25, scope: !1996)
!1996 = distinct !DILexicalBlock(scope: !1997, file: !1, line: 555, column: 9)
!1997 = distinct !DILexicalBlock(scope: !1993, file: !1, line: 552, column: 18)
!1998 = !DILocation(line: 555, column: 9, scope: !1996)
!1999 = !DILocation(line: 555, column: 31, scope: !1996)
!2000 = !DILocation(line: 556, column: 9, scope: !1996)
!2001 = !DILocation(line: 556, column: 19, scope: !2002)
!2002 = !DILexicalBlockFile(scope: !1996, file: !1, discriminator: 1)
!2003 = !DILocation(line: 556, column: 12, scope: !2002)
!2004 = !DILocation(line: 555, column: 9, scope: !2005)
!2005 = !DILexicalBlockFile(scope: !1997, file: !1, discriminator: 1)
!2006 = !DILocation(line: 557, column: 13, scope: !2007)
!2007 = distinct !DILexicalBlock(scope: !1996, file: !1, line: 556, column: 41)
!2008 = !DILocation(line: 557, column: 31, scope: !2007)
!2009 = !DILocation(line: 557, column: 15, scope: !2007)
!2010 = !DILocation(line: 557, column: 11, scope: !2007)
!2011 = !DILocation(line: 558, column: 29, scope: !2007)
!2012 = !DILocation(line: 558, column: 32, scope: !2007)
!2013 = !DILocation(line: 558, column: 6, scope: !2007)
!2014 = !DILocation(line: 559, column: 17, scope: !2007)
!2015 = !DILocation(line: 559, column: 14, scope: !2007)
!2016 = !DILocation(line: 560, column: 10, scope: !2017)
!2017 = distinct !DILexicalBlock(scope: !2007, file: !1, line: 560, column: 10)
!2018 = !DILocation(line: 560, column: 18, scope: !2017)
!2019 = !DILocation(line: 560, column: 10, scope: !2007)
!2020 = !DILocation(line: 561, column: 26, scope: !2021)
!2021 = distinct !DILexicalBlock(scope: !2017, file: !1, line: 560, column: 23)
!2022 = !DILocation(line: 561, column: 29, scope: !2021)
!2023 = !DILocation(line: 565, column: 16, scope: !2021)
!2024 = !DILocation(line: 565, column: 11, scope: !2021)
!2025 = !DILocation(line: 561, column: 7, scope: !2021)
!2026 = !DILocation(line: 566, column: 7, scope: !2021)
!2027 = !DILocation(line: 568, column: 6, scope: !2007)
!2028 = !DILocation(line: 570, column: 7, scope: !1997)
!2029 = !DILocation(line: 571, column: 5, scope: !1997)
!2030 = !DILocation(line: 573, column: 6, scope: !1997)
!2031 = !DILocation(line: 574, column: 5, scope: !1997)
!2032 = !DILocation(line: 576, column: 7, scope: !1997)
!2033 = !DILocation(line: 577, column: 5, scope: !1997)
!2034 = !DILocation(line: 551, column: 3, scope: !2035)
!2035 = !DILexicalBlockFile(scope: !1952, file: !1, discriminator: 2)
!2036 = !DILocation(line: 580, column: 10, scope: !1952)
!2037 = !DILocation(line: 580, column: 28, scope: !1952)
!2038 = !DILocation(line: 580, column: 12, scope: !1952)
!2039 = !DILocation(line: 580, column: 8, scope: !1952)
!2040 = !DILocation(line: 581, column: 26, scope: !1952)
!2041 = !DILocation(line: 581, column: 29, scope: !1952)
!2042 = !DILocation(line: 581, column: 3, scope: !1952)
!2043 = !DILocation(line: 582, column: 14, scope: !1952)
!2044 = !DILocation(line: 582, column: 11, scope: !1952)
!2045 = !DILocation(line: 534, column: 2, scope: !2046)
!2046 = !DILexicalBlockFile(scope: !1953, file: !1, discriminator: 1)
!2047 = !DILocation(line: 584, column: 1, scope: !340)
!2048 = !DILocalVariable(name: "p", arg: 1, scope: !342, file: !1, line: 969, type: !321)
!2049 = !DILocation(line: 969, column: 26, scope: !342)
!2050 = !DILocation(line: 971, column: 21, scope: !342)
!2051 = !DILocation(line: 971, column: 12, scope: !342)
!2052 = !DILocation(line: 971, column: 27, scope: !342)
!2053 = !DILocation(line: 971, column: 37, scope: !342)
!2054 = !DILocation(line: 971, column: 42, scope: !342)
!2055 = !DILocation(line: 971, column: 36, scope: !342)
!2056 = !DILocation(line: 971, column: 34, scope: !342)
!2057 = !DILocation(line: 971, column: 52, scope: !342)
!2058 = !DILocation(line: 971, column: 57, scope: !342)
!2059 = !DILocation(line: 971, column: 51, scope: !342)
!2060 = !DILocation(line: 971, column: 49, scope: !342)
!2061 = !DILocation(line: 971, column: 66, scope: !342)
!2062 = !DILocation(line: 971, column: 65, scope: !342)
!2063 = !DILocation(line: 971, column: 63, scope: !342)
!2064 = !DILocation(line: 971, column: 2, scope: !342)
!2065 = !DILocalVariable(name: "p", arg: 1, scope: !346, file: !1, line: 962, type: !321)
!2066 = !DILocation(line: 962, column: 26, scope: !346)
!2067 = !DILocation(line: 964, column: 11, scope: !346)
!2068 = !DILocation(line: 964, column: 16, scope: !346)
!2069 = !DILocation(line: 964, column: 10, scope: !346)
!2070 = !DILocation(line: 964, column: 36, scope: !346)
!2071 = !DILocation(line: 964, column: 27, scope: !346)
!2072 = !DILocation(line: 964, column: 42, scope: !346)
!2073 = !DILocation(line: 964, column: 23, scope: !346)
!2074 = !DILocation(line: 964, column: 52, scope: !346)
!2075 = !DILocation(line: 964, column: 57, scope: !346)
!2076 = !DILocation(line: 964, column: 51, scope: !346)
!2077 = !DILocation(line: 964, column: 49, scope: !346)
!2078 = !DILocation(line: 964, column: 66, scope: !346)
!2079 = !DILocation(line: 964, column: 71, scope: !346)
!2080 = !DILocation(line: 964, column: 65, scope: !346)
!2081 = !DILocation(line: 964, column: 63, scope: !346)
!2082 = !DILocation(line: 964, column: 2, scope: !346)
!2083 = !DILocalVariable(name: "a", arg: 1, scope: !349, file: !1, line: 1022, type: !4)
!2084 = !DILocation(line: 1022, column: 38, scope: !349)
!2085 = !DILocalVariable(name: "cpio", arg: 2, scope: !349, file: !1, line: 1023, type: !292)
!2086 = !DILocation(line: 1023, column: 18, scope: !349)
!2087 = !DILocalVariable(name: "entry", arg: 3, scope: !349, file: !1, line: 1023, type: !30)
!2088 = !DILocation(line: 1023, column: 46, scope: !349)
!2089 = !DILocalVariable(name: "le", scope: !349, file: !1, line: 1025, type: !301)
!2090 = !DILocation(line: 1025, column: 27, scope: !349)
!2091 = !DILocalVariable(name: "dev", scope: !349, file: !1, line: 1026, type: !308)
!2092 = !DILocation(line: 1026, column: 8, scope: !349)
!2093 = !DILocalVariable(name: "ino", scope: !349, file: !1, line: 1027, type: !52)
!2094 = !DILocation(line: 1027, column: 10, scope: !349)
!2095 = !DILocation(line: 1029, column: 26, scope: !2096)
!2096 = distinct !DILexicalBlock(scope: !349, file: !1, line: 1029, column: 6)
!2097 = !DILocation(line: 1029, column: 6, scope: !2096)
!2098 = !DILocation(line: 1029, column: 33, scope: !2096)
!2099 = !DILocation(line: 1029, column: 6, scope: !349)
!2100 = !DILocation(line: 1030, column: 3, scope: !2096)
!2101 = !DILocation(line: 1032, column: 26, scope: !349)
!2102 = !DILocation(line: 1032, column: 8, scope: !349)
!2103 = !DILocation(line: 1032, column: 6, scope: !349)
!2104 = !DILocation(line: 1033, column: 28, scope: !349)
!2105 = !DILocation(line: 1033, column: 8, scope: !349)
!2106 = !DILocation(line: 1033, column: 6, scope: !349)
!2107 = !DILocation(line: 1039, column: 12, scope: !2108)
!2108 = distinct !DILexicalBlock(scope: !349, file: !1, line: 1039, column: 2)
!2109 = !DILocation(line: 1039, column: 18, scope: !2108)
!2110 = !DILocation(line: 1039, column: 10, scope: !2108)
!2111 = !DILocation(line: 1039, column: 7, scope: !2108)
!2112 = !DILocation(line: 1039, column: 30, scope: !2113)
!2113 = !DILexicalBlockFile(scope: !2114, file: !1, discriminator: 1)
!2114 = distinct !DILexicalBlock(scope: !2108, file: !1, line: 1039, column: 2)
!2115 = !DILocation(line: 1039, column: 2, scope: !2113)
!2116 = !DILocation(line: 1040, column: 7, scope: !2117)
!2117 = distinct !DILexicalBlock(scope: !2118, file: !1, line: 1040, column: 7)
!2118 = distinct !DILexicalBlock(scope: !2114, file: !1, line: 1039, column: 49)
!2119 = !DILocation(line: 1040, column: 11, scope: !2117)
!2120 = !DILocation(line: 1040, column: 18, scope: !2117)
!2121 = !DILocation(line: 1040, column: 15, scope: !2117)
!2122 = !DILocation(line: 1040, column: 22, scope: !2117)
!2123 = !DILocation(line: 1040, column: 25, scope: !2124)
!2124 = !DILexicalBlockFile(scope: !2117, file: !1, discriminator: 1)
!2125 = !DILocation(line: 1040, column: 29, scope: !2124)
!2126 = !DILocation(line: 1040, column: 36, scope: !2124)
!2127 = !DILocation(line: 1040, column: 33, scope: !2124)
!2128 = !DILocation(line: 1040, column: 7, scope: !2124)
!2129 = !DILocation(line: 1041, column: 32, scope: !2130)
!2130 = distinct !DILexicalBlock(scope: !2117, file: !1, line: 1040, column: 41)
!2131 = !DILocation(line: 1041, column: 39, scope: !2130)
!2132 = !DILocation(line: 1041, column: 43, scope: !2130)
!2133 = !DILocation(line: 1041, column: 4, scope: !2130)
!2134 = !DILocation(line: 1043, column: 10, scope: !2135)
!2135 = distinct !DILexicalBlock(scope: !2130, file: !1, line: 1043, column: 8)
!2136 = !DILocation(line: 1043, column: 14, scope: !2135)
!2137 = !DILocation(line: 1043, column: 8, scope: !2135)
!2138 = !DILocation(line: 1043, column: 20, scope: !2135)
!2139 = !DILocation(line: 1043, column: 8, scope: !2130)
!2140 = !DILocation(line: 1044, column: 9, scope: !2141)
!2141 = distinct !DILexicalBlock(scope: !2142, file: !1, line: 1044, column: 9)
!2142 = distinct !DILexicalBlock(scope: !2135, file: !1, line: 1043, column: 26)
!2143 = !DILocation(line: 1044, column: 13, scope: !2141)
!2144 = !DILocation(line: 1044, column: 22, scope: !2141)
!2145 = !DILocation(line: 1044, column: 9, scope: !2142)
!2146 = !DILocation(line: 1045, column: 27, scope: !2141)
!2147 = !DILocation(line: 1045, column: 31, scope: !2141)
!2148 = !DILocation(line: 1045, column: 6, scope: !2141)
!2149 = !DILocation(line: 1045, column: 10, scope: !2141)
!2150 = !DILocation(line: 1045, column: 20, scope: !2141)
!2151 = !DILocation(line: 1045, column: 25, scope: !2141)
!2152 = !DILocation(line: 1046, column: 9, scope: !2153)
!2153 = distinct !DILexicalBlock(scope: !2142, file: !1, line: 1046, column: 9)
!2154 = !DILocation(line: 1046, column: 13, scope: !2153)
!2155 = !DILocation(line: 1046, column: 18, scope: !2153)
!2156 = !DILocation(line: 1046, column: 9, scope: !2142)
!2157 = !DILocation(line: 1047, column: 27, scope: !2153)
!2158 = !DILocation(line: 1047, column: 31, scope: !2153)
!2159 = !DILocation(line: 1047, column: 6, scope: !2153)
!2160 = !DILocation(line: 1047, column: 10, scope: !2153)
!2161 = !DILocation(line: 1047, column: 16, scope: !2153)
!2162 = !DILocation(line: 1047, column: 25, scope: !2153)
!2163 = !DILocation(line: 1048, column: 9, scope: !2164)
!2164 = distinct !DILexicalBlock(scope: !2142, file: !1, line: 1048, column: 9)
!2165 = !DILocation(line: 1048, column: 15, scope: !2164)
!2166 = !DILocation(line: 1048, column: 29, scope: !2164)
!2167 = !DILocation(line: 1048, column: 26, scope: !2164)
!2168 = !DILocation(line: 1048, column: 9, scope: !2142)
!2169 = !DILocation(line: 1049, column: 25, scope: !2164)
!2170 = !DILocation(line: 1049, column: 29, scope: !2164)
!2171 = !DILocation(line: 1049, column: 6, scope: !2164)
!2172 = !DILocation(line: 1049, column: 12, scope: !2164)
!2173 = !DILocation(line: 1049, column: 23, scope: !2164)
!2174 = !DILocation(line: 1050, column: 10, scope: !2142)
!2175 = !DILocation(line: 1050, column: 14, scope: !2142)
!2176 = !DILocation(line: 1050, column: 5, scope: !2142)
!2177 = !DILocation(line: 1051, column: 10, scope: !2142)
!2178 = !DILocation(line: 1051, column: 5, scope: !2142)
!2179 = !DILocation(line: 1052, column: 4, scope: !2142)
!2180 = !DILocation(line: 1054, column: 4, scope: !2130)
!2181 = !DILocation(line: 1056, column: 2, scope: !2118)
!2182 = !DILocation(line: 1039, column: 39, scope: !2183)
!2183 = !DILexicalBlockFile(scope: !2114, file: !1, discriminator: 2)
!2184 = !DILocation(line: 1039, column: 43, scope: !2183)
!2185 = !DILocation(line: 1039, column: 37, scope: !2183)
!2186 = !DILocation(line: 1039, column: 2, scope: !2183)
!2187 = !DILocation(line: 1058, column: 29, scope: !349)
!2188 = !DILocation(line: 1058, column: 7, scope: !349)
!2189 = !DILocation(line: 1058, column: 5, scope: !349)
!2190 = !DILocation(line: 1059, column: 6, scope: !2191)
!2191 = distinct !DILexicalBlock(scope: !349, file: !1, line: 1059, column: 6)
!2192 = !DILocation(line: 1059, column: 9, scope: !2191)
!2193 = !DILocation(line: 1059, column: 6, scope: !349)
!2194 = !DILocation(line: 1060, column: 22, scope: !2195)
!2195 = distinct !DILexicalBlock(scope: !2191, file: !1, line: 1059, column: 18)
!2196 = !DILocation(line: 1060, column: 25, scope: !2195)
!2197 = !DILocation(line: 1060, column: 3, scope: !2195)
!2198 = !DILocation(line: 1062, column: 3, scope: !2195)
!2199 = !DILocation(line: 1064, column: 6, scope: !2200)
!2200 = distinct !DILexicalBlock(scope: !349, file: !1, line: 1064, column: 6)
!2201 = !DILocation(line: 1064, column: 12, scope: !2200)
!2202 = !DILocation(line: 1064, column: 23, scope: !2200)
!2203 = !DILocation(line: 1064, column: 6, scope: !349)
!2204 = !DILocation(line: 1065, column: 32, scope: !2200)
!2205 = !DILocation(line: 1065, column: 3, scope: !2200)
!2206 = !DILocation(line: 1065, column: 9, scope: !2200)
!2207 = !DILocation(line: 1065, column: 21, scope: !2200)
!2208 = !DILocation(line: 1065, column: 30, scope: !2200)
!2209 = !DILocation(line: 1066, column: 13, scope: !349)
!2210 = !DILocation(line: 1066, column: 19, scope: !349)
!2211 = !DILocation(line: 1066, column: 2, scope: !349)
!2212 = !DILocation(line: 1066, column: 6, scope: !349)
!2213 = !DILocation(line: 1066, column: 11, scope: !349)
!2214 = !DILocation(line: 1067, column: 2, scope: !349)
!2215 = !DILocation(line: 1067, column: 6, scope: !349)
!2216 = !DILocation(line: 1067, column: 15, scope: !349)
!2217 = !DILocation(line: 1068, column: 21, scope: !349)
!2218 = !DILocation(line: 1068, column: 2, scope: !349)
!2219 = !DILocation(line: 1068, column: 8, scope: !349)
!2220 = !DILocation(line: 1068, column: 19, scope: !349)
!2221 = !DILocation(line: 1069, column: 12, scope: !349)
!2222 = !DILocation(line: 1069, column: 2, scope: !349)
!2223 = !DILocation(line: 1069, column: 6, scope: !349)
!2224 = !DILocation(line: 1069, column: 10, scope: !349)
!2225 = !DILocation(line: 1070, column: 12, scope: !349)
!2226 = !DILocation(line: 1070, column: 2, scope: !349)
!2227 = !DILocation(line: 1070, column: 6, scope: !349)
!2228 = !DILocation(line: 1070, column: 10, scope: !349)
!2229 = !DILocation(line: 1071, column: 34, scope: !349)
!2230 = !DILocation(line: 1071, column: 14, scope: !349)
!2231 = !DILocation(line: 1071, column: 41, scope: !349)
!2232 = !DILocation(line: 1071, column: 2, scope: !349)
!2233 = !DILocation(line: 1071, column: 6, scope: !349)
!2234 = !DILocation(line: 1071, column: 12, scope: !349)
!2235 = !DILocation(line: 1072, column: 43, scope: !349)
!2236 = !DILocation(line: 1072, column: 20, scope: !349)
!2237 = !DILocation(line: 1072, column: 13, scope: !2238)
!2238 = !DILexicalBlockFile(scope: !349, file: !1, discriminator: 1)
!2239 = !DILocation(line: 1072, column: 2, scope: !349)
!2240 = !DILocation(line: 1072, column: 6, scope: !349)
!2241 = !DILocation(line: 1072, column: 11, scope: !349)
!2242 = !DILocation(line: 1073, column: 6, scope: !2243)
!2243 = distinct !DILexicalBlock(scope: !349, file: !1, line: 1073, column: 6)
!2244 = !DILocation(line: 1073, column: 10, scope: !2243)
!2245 = !DILocation(line: 1073, column: 15, scope: !2243)
!2246 = !DILocation(line: 1073, column: 6, scope: !349)
!2247 = !DILocation(line: 1074, column: 22, scope: !2248)
!2248 = distinct !DILexicalBlock(scope: !2243, file: !1, line: 1073, column: 24)
!2249 = !DILocation(line: 1074, column: 25, scope: !2248)
!2250 = !DILocation(line: 1074, column: 3, scope: !2248)
!2251 = !DILocation(line: 1076, column: 3, scope: !2248)
!2252 = !DILocation(line: 1079, column: 2, scope: !349)
!2253 = !DILocation(line: 1080, column: 1, scope: !349)
