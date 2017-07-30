; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmbzip2/bzlib.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct._IO_FILE = type { i32, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, i8*, %struct._IO_marker*, %struct._IO_FILE*, i32, i32, i64, i16, i8, [1 x i8], i8*, i64, i8*, i8*, i8*, i8*, i64, i32, [20 x i8] }
%struct._IO_marker = type { %struct._IO_marker*, %struct._IO_FILE*, i32 }
%struct.bz_stream = type { i8*, i32, i32, i32, i8*, i32, i32, i32, i8*, i8* (i8*, i32, i32)*, void (i8*, i8*)*, i8* }
%struct.EState = type { %struct.bz_stream*, i32, i32, i32, i32*, i32*, i32*, i32, i32*, i8*, i16*, i8*, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, [256 x i8], [256 x i8], i32, i32, i32, i32, i32, i32, i32, i32, [258 x i32], [18002 x i8], [18002 x i8], [6 x [258 x i8]], [6 x [258 x i32]], [6 x [258 x i32]], [258 x [4 x i32]] }
%struct.DState = type { %struct.bz_stream*, i32, i8, i32, i8, i32, i32, i32, i32, i32, i8, i32, i32, i32, i32, i32, [256 x i32], i32, [257 x i32], [257 x i32], i32*, i16*, i8*, i32, i32, i32, i32, i32, [256 x i8], [16 x i8], [256 x i8], [4096 x i8], [16 x i32], [18002 x i8], [18002 x i8], [6 x [258 x i8]], [6 x [258 x i32]], [6 x [258 x i32]], [6 x [258 x i32]], [6 x i32], i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32*, i32*, i32* }
%struct.bzFile = type { %struct._IO_FILE*, [5000 x i8], i32, i8, %struct.bz_stream, i32, i8 }

@stderr = external global %struct._IO_FILE*, align 8
@.str = private unnamed_addr constant [443 x i8] c"\0A\0Abzip2/libbzip2: internal error number %d.\0AThis is a bug in bzip2/libbzip2, %s.\0APlease report it to me at: jseward@bzip.org.  If this happened\0Awhen you were using some program which uses libbzip2 as a\0Acomponent, you should also report this bug to the author(s)\0Aof that program.  Please make an effort to report this bug;\0Atimely and accurate bug reports eventually lead to higher\0Aquality software.  Thanks.  Julian Seward, 10 December 2007.\0A\0A\00", align 1
@.str.1 = private unnamed_addr constant [1057 x i8] c"\0A*** A special note about internal error number 1007 ***\0A\0AExperience suggests that a common cause of i.e. 1007\0Ais unreliable memory or other hardware.  The 1007 assertion\0Ajust happens to cross-check the results of huge numbers of\0Amemory reads/writes, and so acts (unintendedly) as a stress\0Atest of your memory system.\0A\0AI suggest the following: try compressing the file again,\0Apossibly monitoring progress in detail with the -vv flag.\0A\0A* If the error cannot be reproduced, and/or happens at different\0A  points in compression, you may have a flaky memory system.\0A  Try a memory-test program.  I have used Memtest86\0A  (www.memtest86.com).  At the time of writing it is free (GPLd).\0A  Memtest86 tests memory much more thorougly than your BIOSs\0A  power-on test, and may find failures that the BIOS doesn't.\0A\0A* If the error can be repeatably reproduced, this is a bug in\0A  bzip2, and I would very much like to hear about it.  Please\0A  let me know, and, ideally, save a copy of the file causing the\0A  problem -- without which I will be unable to investigate it.\0A\0A\00", align 1
@.str.2 = private unnamed_addr constant [18 x i8] c" {0x%08x, 0x%08x}\00", align 1
@.str.3 = private unnamed_addr constant [2 x i8] c"]\00", align 1
@.str.4 = private unnamed_addr constant [55 x i8] c"\0A    combined CRCs: stored = 0x%08x, computed = 0x%08x\00", align 1
@.str.5 = private unnamed_addr constant [19 x i8] c"1.0.5, 10-Dec-2007\00", align 1
@stdin = external global %struct._IO_FILE*, align 8
@stdout = external global %struct._IO_FILE*, align 8
@bzerrorstrings = internal global [16 x i8*] [i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.15, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.17, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.18, i32 0, i32 0), i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.19, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.20, i32 0, i32 0)], align 16
@BZ2_crc32Table = external global [256 x i32], align 16
@BZ2_rNums = external global [512 x i32], align 16
@.str.6 = private unnamed_addr constant [2 x i8] c"w\00", align 1
@.str.7 = private unnamed_addr constant [2 x i8] c"r\00", align 1
@.str.8 = private unnamed_addr constant [2 x i8] c"b\00", align 1
@.str.9 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.10 = private unnamed_addr constant [3 x i8] c"OK\00", align 1
@.str.11 = private unnamed_addr constant [15 x i8] c"SEQUENCE_ERROR\00", align 1
@.str.12 = private unnamed_addr constant [12 x i8] c"PARAM_ERROR\00", align 1
@.str.13 = private unnamed_addr constant [10 x i8] c"MEM_ERROR\00", align 1
@.str.14 = private unnamed_addr constant [11 x i8] c"DATA_ERROR\00", align 1
@.str.15 = private unnamed_addr constant [17 x i8] c"DATA_ERROR_MAGIC\00", align 1
@.str.16 = private unnamed_addr constant [9 x i8] c"IO_ERROR\00", align 1
@.str.17 = private unnamed_addr constant [15 x i8] c"UNEXPECTED_EOF\00", align 1
@.str.18 = private unnamed_addr constant [13 x i8] c"OUTBUFF_FULL\00", align 1
@.str.19 = private unnamed_addr constant [13 x i8] c"CONFIG_ERROR\00", align 1
@.str.20 = private unnamed_addr constant [4 x i8] c"???\00", align 1

; Function Attrs: nounwind uwtable
define void @BZ2_bz__AssertH__fail(i32 %errcode) #0 !dbg !131 {
entry:
  %errcode.addr = alloca i32, align 4
  store i32 %errcode, i32* %errcode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %errcode.addr, metadata !391, metadata !392), !dbg !393
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !394
  %1 = load i32, i32* %errcode.addr, align 4, !dbg !395
  %call = call i8* @BZ2_bzlibVersion(), !dbg !396
  %call1 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %0, i8* getelementptr inbounds ([443 x i8], [443 x i8]* @.str, i32 0, i32 0), i32 %1, i8* %call), !dbg !397
  %2 = load i32, i32* %errcode.addr, align 4, !dbg !398
  %cmp = icmp eq i32 %2, 1007, !dbg !400
  br i1 %cmp, label %if.then, label %if.end, !dbg !401

if.then:                                          ; preds = %entry
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !402
  %call2 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %3, i8* getelementptr inbounds ([1057 x i8], [1057 x i8]* @.str.1, i32 0, i32 0)), !dbg !404
  br label %if.end, !dbg !405

if.end:                                           ; preds = %if.then, %entry
  call void @exit(i32 3) #9, !dbg !406
  unreachable, !dbg !406

return:                                           ; No predecessors!
  ret void, !dbg !407
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare i32 @fprintf(%struct._IO_FILE*, i8*, ...) #2

; Function Attrs: nounwind uwtable
define i8* @BZ2_bzlibVersion() #0 !dbg !189 {
entry:
  ret i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.5, i32 0, i32 0), !dbg !408
}

; Function Attrs: noreturn nounwind
declare void @exit(i32) #3

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzCompressInit(%struct.bz_stream* %strm, i32 %blockSize100k, i32 %verbosity, i32 %workFactor) #0 !dbg !135 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.bz_stream*, align 8
  %blockSize100k.addr = alloca i32, align 4
  %verbosity.addr = alloca i32, align 4
  %workFactor.addr = alloca i32, align 4
  %n = alloca i32, align 4
  %s = alloca %struct.EState*, align 8
  store %struct.bz_stream* %strm, %struct.bz_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.bz_stream** %strm.addr, metadata !409, metadata !392), !dbg !410
  store i32 %blockSize100k, i32* %blockSize100k.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %blockSize100k.addr, metadata !411, metadata !392), !dbg !412
  store i32 %verbosity, i32* %verbosity.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %verbosity.addr, metadata !413, metadata !392), !dbg !414
  store i32 %workFactor, i32* %workFactor.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %workFactor.addr, metadata !415, metadata !392), !dbg !416
  call void @llvm.dbg.declare(metadata i32* %n, metadata !417, metadata !392), !dbg !418
  call void @llvm.dbg.declare(metadata %struct.EState** %s, metadata !419, metadata !392), !dbg !420
  %call = call i32 @bz_config_ok(), !dbg !421
  %tobool = icmp ne i32 %call, 0, !dbg !421
  br i1 %tobool, label %if.end, label %if.then, !dbg !423

if.then:                                          ; preds = %entry
  store i32 -9, i32* %retval, align 4, !dbg !424
  br label %return, !dbg !424

if.end:                                           ; preds = %entry
  %0 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !426
  %cmp = icmp eq %struct.bz_stream* %0, null, !dbg !428
  br i1 %cmp, label %if.then8, label %lor.lhs.false, !dbg !429

lor.lhs.false:                                    ; preds = %if.end
  %1 = load i32, i32* %blockSize100k.addr, align 4, !dbg !430
  %cmp1 = icmp slt i32 %1, 1, !dbg !431
  br i1 %cmp1, label %if.then8, label %lor.lhs.false2, !dbg !432

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i32, i32* %blockSize100k.addr, align 4, !dbg !433
  %cmp3 = icmp sgt i32 %2, 9, !dbg !435
  br i1 %cmp3, label %if.then8, label %lor.lhs.false4, !dbg !436

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %3 = load i32, i32* %workFactor.addr, align 4, !dbg !437
  %cmp5 = icmp slt i32 %3, 0, !dbg !438
  br i1 %cmp5, label %if.then8, label %lor.lhs.false6, !dbg !439

lor.lhs.false6:                                   ; preds = %lor.lhs.false4
  %4 = load i32, i32* %workFactor.addr, align 4, !dbg !440
  %cmp7 = icmp sgt i32 %4, 250, !dbg !441
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !442

if.then8:                                         ; preds = %lor.lhs.false6, %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %if.end
  store i32 -2, i32* %retval, align 4, !dbg !444
  br label %return, !dbg !444

if.end9:                                          ; preds = %lor.lhs.false6
  %5 = load i32, i32* %workFactor.addr, align 4, !dbg !445
  %cmp10 = icmp eq i32 %5, 0, !dbg !447
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !448

if.then11:                                        ; preds = %if.end9
  store i32 30, i32* %workFactor.addr, align 4, !dbg !449
  br label %if.end12, !dbg !451

if.end12:                                         ; preds = %if.then11, %if.end9
  %6 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !452
  %bzalloc = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %6, i32 0, i32 9, !dbg !454
  %7 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %bzalloc, align 8, !dbg !454
  %cmp13 = icmp eq i8* (i8*, i32, i32)* %7, null, !dbg !455
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !456

if.then14:                                        ; preds = %if.end12
  %8 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !457
  %bzalloc15 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %8, i32 0, i32 9, !dbg !459
  store i8* (i8*, i32, i32)* @default_bzalloc, i8* (i8*, i32, i32)** %bzalloc15, align 8, !dbg !460
  br label %if.end16, !dbg !457

if.end16:                                         ; preds = %if.then14, %if.end12
  %9 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !461
  %bzfree = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %9, i32 0, i32 10, !dbg !463
  %10 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree, align 8, !dbg !463
  %cmp17 = icmp eq void (i8*, i8*)* %10, null, !dbg !464
  br i1 %cmp17, label %if.then18, label %if.end20, !dbg !465

if.then18:                                        ; preds = %if.end16
  %11 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !466
  %bzfree19 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %11, i32 0, i32 10, !dbg !468
  store void (i8*, i8*)* @default_bzfree, void (i8*, i8*)** %bzfree19, align 8, !dbg !469
  br label %if.end20, !dbg !466

if.end20:                                         ; preds = %if.then18, %if.end16
  %12 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !470
  %bzalloc21 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %12, i32 0, i32 9, !dbg !470
  %13 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %bzalloc21, align 8, !dbg !470
  %14 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !470
  %opaque = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %14, i32 0, i32 11, !dbg !470
  %15 = load i8*, i8** %opaque, align 8, !dbg !470
  %call22 = call i8* %13(i8* %15, i32 55768, i32 1), !dbg !470
  %16 = bitcast i8* %call22 to %struct.EState*, !dbg !470
  store %struct.EState* %16, %struct.EState** %s, align 8, !dbg !471
  %17 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !472
  %cmp23 = icmp eq %struct.EState* %17, null, !dbg !474
  br i1 %cmp23, label %if.then24, label %if.end25, !dbg !475

if.then24:                                        ; preds = %if.end20
  store i32 -3, i32* %retval, align 4, !dbg !476
  br label %return, !dbg !476

if.end25:                                         ; preds = %if.end20
  %18 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !478
  %19 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !479
  %strm26 = getelementptr inbounds %struct.EState, %struct.EState* %19, i32 0, i32 0, !dbg !480
  store %struct.bz_stream* %18, %struct.bz_stream** %strm26, align 8, !dbg !481
  %20 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !482
  %arr1 = getelementptr inbounds %struct.EState, %struct.EState* %20, i32 0, i32 4, !dbg !483
  store i32* null, i32** %arr1, align 8, !dbg !484
  %21 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !485
  %arr2 = getelementptr inbounds %struct.EState, %struct.EState* %21, i32 0, i32 5, !dbg !486
  store i32* null, i32** %arr2, align 8, !dbg !487
  %22 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !488
  %ftab = getelementptr inbounds %struct.EState, %struct.EState* %22, i32 0, i32 6, !dbg !489
  store i32* null, i32** %ftab, align 8, !dbg !490
  %23 = load i32, i32* %blockSize100k.addr, align 4, !dbg !491
  %mul = mul nsw i32 100000, %23, !dbg !492
  store i32 %mul, i32* %n, align 4, !dbg !493
  %24 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !494
  %bzalloc27 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %24, i32 0, i32 9, !dbg !494
  %25 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %bzalloc27, align 8, !dbg !494
  %26 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !494
  %opaque28 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %26, i32 0, i32 11, !dbg !494
  %27 = load i8*, i8** %opaque28, align 8, !dbg !494
  %28 = load i32, i32* %n, align 4, !dbg !494
  %conv = sext i32 %28 to i64, !dbg !494
  %mul29 = mul i64 %conv, 4, !dbg !494
  %conv30 = trunc i64 %mul29 to i32, !dbg !494
  %call31 = call i8* %25(i8* %27, i32 %conv30, i32 1), !dbg !494
  %29 = bitcast i8* %call31 to i32*, !dbg !494
  %30 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !495
  %arr132 = getelementptr inbounds %struct.EState, %struct.EState* %30, i32 0, i32 4, !dbg !496
  store i32* %29, i32** %arr132, align 8, !dbg !497
  %31 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !498
  %bzalloc33 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %31, i32 0, i32 9, !dbg !498
  %32 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %bzalloc33, align 8, !dbg !498
  %33 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !498
  %opaque34 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %33, i32 0, i32 11, !dbg !498
  %34 = load i8*, i8** %opaque34, align 8, !dbg !498
  %35 = load i32, i32* %n, align 4, !dbg !498
  %add = add nsw i32 %35, 34, !dbg !498
  %conv35 = sext i32 %add to i64, !dbg !498
  %mul36 = mul i64 %conv35, 4, !dbg !498
  %conv37 = trunc i64 %mul36 to i32, !dbg !498
  %call38 = call i8* %32(i8* %34, i32 %conv37, i32 1), !dbg !498
  %36 = bitcast i8* %call38 to i32*, !dbg !498
  %37 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !499
  %arr239 = getelementptr inbounds %struct.EState, %struct.EState* %37, i32 0, i32 5, !dbg !500
  store i32* %36, i32** %arr239, align 8, !dbg !501
  %38 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !502
  %bzalloc40 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %38, i32 0, i32 9, !dbg !502
  %39 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %bzalloc40, align 8, !dbg !502
  %40 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !502
  %opaque41 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %40, i32 0, i32 11, !dbg !502
  %41 = load i8*, i8** %opaque41, align 8, !dbg !502
  %call42 = call i8* %39(i8* %41, i32 262148, i32 1), !dbg !502
  %42 = bitcast i8* %call42 to i32*, !dbg !502
  %43 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !503
  %ftab43 = getelementptr inbounds %struct.EState, %struct.EState* %43, i32 0, i32 6, !dbg !504
  store i32* %42, i32** %ftab43, align 8, !dbg !505
  %44 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !506
  %arr144 = getelementptr inbounds %struct.EState, %struct.EState* %44, i32 0, i32 4, !dbg !508
  %45 = load i32*, i32** %arr144, align 8, !dbg !508
  %cmp45 = icmp eq i32* %45, null, !dbg !509
  br i1 %cmp45, label %if.then55, label %lor.lhs.false47, !dbg !510

lor.lhs.false47:                                  ; preds = %if.end25
  %46 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !511
  %arr248 = getelementptr inbounds %struct.EState, %struct.EState* %46, i32 0, i32 5, !dbg !513
  %47 = load i32*, i32** %arr248, align 8, !dbg !513
  %cmp49 = icmp eq i32* %47, null, !dbg !514
  br i1 %cmp49, label %if.then55, label %lor.lhs.false51, !dbg !515

lor.lhs.false51:                                  ; preds = %lor.lhs.false47
  %48 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !516
  %ftab52 = getelementptr inbounds %struct.EState, %struct.EState* %48, i32 0, i32 6, !dbg !518
  %49 = load i32*, i32** %ftab52, align 8, !dbg !518
  %cmp53 = icmp eq i32* %49, null, !dbg !519
  br i1 %cmp53, label %if.then55, label %if.end86, !dbg !520

if.then55:                                        ; preds = %lor.lhs.false51, %lor.lhs.false47, %if.end25
  %50 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !521
  %arr156 = getelementptr inbounds %struct.EState, %struct.EState* %50, i32 0, i32 4, !dbg !524
  %51 = load i32*, i32** %arr156, align 8, !dbg !524
  %cmp57 = icmp ne i32* %51, null, !dbg !525
  br i1 %cmp57, label %if.then59, label %if.end63, !dbg !526

if.then59:                                        ; preds = %if.then55
  %52 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !527
  %bzfree60 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %52, i32 0, i32 10, !dbg !527
  %53 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree60, align 8, !dbg !527
  %54 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !527
  %opaque61 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %54, i32 0, i32 11, !dbg !527
  %55 = load i8*, i8** %opaque61, align 8, !dbg !527
  %56 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !527
  %arr162 = getelementptr inbounds %struct.EState, %struct.EState* %56, i32 0, i32 4, !dbg !527
  %57 = load i32*, i32** %arr162, align 8, !dbg !527
  %58 = bitcast i32* %57 to i8*, !dbg !527
  call void %53(i8* %55, i8* %58), !dbg !527
  br label %if.end63, !dbg !527

if.end63:                                         ; preds = %if.then59, %if.then55
  %59 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !529
  %arr264 = getelementptr inbounds %struct.EState, %struct.EState* %59, i32 0, i32 5, !dbg !531
  %60 = load i32*, i32** %arr264, align 8, !dbg !531
  %cmp65 = icmp ne i32* %60, null, !dbg !532
  br i1 %cmp65, label %if.then67, label %if.end71, !dbg !533

if.then67:                                        ; preds = %if.end63
  %61 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !534
  %bzfree68 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %61, i32 0, i32 10, !dbg !534
  %62 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree68, align 8, !dbg !534
  %63 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !534
  %opaque69 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %63, i32 0, i32 11, !dbg !534
  %64 = load i8*, i8** %opaque69, align 8, !dbg !534
  %65 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !534
  %arr270 = getelementptr inbounds %struct.EState, %struct.EState* %65, i32 0, i32 5, !dbg !534
  %66 = load i32*, i32** %arr270, align 8, !dbg !534
  %67 = bitcast i32* %66 to i8*, !dbg !534
  call void %62(i8* %64, i8* %67), !dbg !534
  br label %if.end71, !dbg !534

if.end71:                                         ; preds = %if.then67, %if.end63
  %68 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !536
  %ftab72 = getelementptr inbounds %struct.EState, %struct.EState* %68, i32 0, i32 6, !dbg !538
  %69 = load i32*, i32** %ftab72, align 8, !dbg !538
  %cmp73 = icmp ne i32* %69, null, !dbg !539
  br i1 %cmp73, label %if.then75, label %if.end79, !dbg !540

if.then75:                                        ; preds = %if.end71
  %70 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !541
  %bzfree76 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %70, i32 0, i32 10, !dbg !541
  %71 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree76, align 8, !dbg !541
  %72 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !541
  %opaque77 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %72, i32 0, i32 11, !dbg !541
  %73 = load i8*, i8** %opaque77, align 8, !dbg !541
  %74 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !541
  %ftab78 = getelementptr inbounds %struct.EState, %struct.EState* %74, i32 0, i32 6, !dbg !541
  %75 = load i32*, i32** %ftab78, align 8, !dbg !541
  %76 = bitcast i32* %75 to i8*, !dbg !541
  call void %71(i8* %73, i8* %76), !dbg !541
  br label %if.end79, !dbg !541

if.end79:                                         ; preds = %if.then75, %if.end71
  %77 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !543
  %cmp80 = icmp ne %struct.EState* %77, null, !dbg !545
  br i1 %cmp80, label %if.then82, label %if.end85, !dbg !546

if.then82:                                        ; preds = %if.end79
  %78 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !547
  %bzfree83 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %78, i32 0, i32 10, !dbg !547
  %79 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree83, align 8, !dbg !547
  %80 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !547
  %opaque84 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %80, i32 0, i32 11, !dbg !547
  %81 = load i8*, i8** %opaque84, align 8, !dbg !547
  %82 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !547
  %83 = bitcast %struct.EState* %82 to i8*, !dbg !547
  call void %79(i8* %81, i8* %83), !dbg !547
  br label %if.end85, !dbg !547

if.end85:                                         ; preds = %if.then82, %if.end79
  store i32 -3, i32* %retval, align 4, !dbg !549
  br label %return, !dbg !549

if.end86:                                         ; preds = %lor.lhs.false51
  %84 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !550
  %blockNo = getelementptr inbounds %struct.EState, %struct.EState* %84, i32 0, i32 29, !dbg !551
  store i32 0, i32* %blockNo, align 4, !dbg !552
  %85 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !553
  %state = getelementptr inbounds %struct.EState, %struct.EState* %85, i32 0, i32 2, !dbg !554
  store i32 2, i32* %state, align 4, !dbg !555
  %86 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !556
  %mode = getelementptr inbounds %struct.EState, %struct.EState* %86, i32 0, i32 1, !dbg !557
  store i32 2, i32* %mode, align 8, !dbg !558
  %87 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !559
  %combinedCRC = getelementptr inbounds %struct.EState, %struct.EState* %87, i32 0, i32 27, !dbg !560
  store i32 0, i32* %combinedCRC, align 4, !dbg !561
  %88 = load i32, i32* %blockSize100k.addr, align 4, !dbg !562
  %89 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !563
  %blockSize100k87 = getelementptr inbounds %struct.EState, %struct.EState* %89, i32 0, i32 30, !dbg !564
  store i32 %88, i32* %blockSize100k87, align 8, !dbg !565
  %90 = load i32, i32* %blockSize100k.addr, align 4, !dbg !566
  %mul88 = mul nsw i32 100000, %90, !dbg !567
  %sub = sub nsw i32 %mul88, 19, !dbg !568
  %91 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !569
  %nblockMAX = getelementptr inbounds %struct.EState, %struct.EState* %91, i32 0, i32 18, !dbg !570
  store i32 %sub, i32* %nblockMAX, align 8, !dbg !571
  %92 = load i32, i32* %verbosity.addr, align 4, !dbg !572
  %93 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !573
  %verbosity89 = getelementptr inbounds %struct.EState, %struct.EState* %93, i32 0, i32 28, !dbg !574
  store i32 %92, i32* %verbosity89, align 8, !dbg !575
  %94 = load i32, i32* %workFactor.addr, align 4, !dbg !576
  %95 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !577
  %workFactor90 = getelementptr inbounds %struct.EState, %struct.EState* %95, i32 0, i32 12, !dbg !578
  store i32 %94, i32* %workFactor90, align 8, !dbg !579
  %96 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !580
  %arr291 = getelementptr inbounds %struct.EState, %struct.EState* %96, i32 0, i32 5, !dbg !581
  %97 = load i32*, i32** %arr291, align 8, !dbg !581
  %98 = bitcast i32* %97 to i8*, !dbg !582
  %99 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !583
  %block = getelementptr inbounds %struct.EState, %struct.EState* %99, i32 0, i32 9, !dbg !584
  store i8* %98, i8** %block, align 8, !dbg !585
  %100 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !586
  %arr192 = getelementptr inbounds %struct.EState, %struct.EState* %100, i32 0, i32 4, !dbg !587
  %101 = load i32*, i32** %arr192, align 8, !dbg !587
  %102 = bitcast i32* %101 to i16*, !dbg !588
  %103 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !589
  %mtfv = getelementptr inbounds %struct.EState, %struct.EState* %103, i32 0, i32 10, !dbg !590
  store i16* %102, i16** %mtfv, align 8, !dbg !591
  %104 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !592
  %zbits = getelementptr inbounds %struct.EState, %struct.EState* %104, i32 0, i32 11, !dbg !593
  store i8* null, i8** %zbits, align 8, !dbg !594
  %105 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !595
  %arr193 = getelementptr inbounds %struct.EState, %struct.EState* %105, i32 0, i32 4, !dbg !596
  %106 = load i32*, i32** %arr193, align 8, !dbg !596
  %107 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !597
  %ptr = getelementptr inbounds %struct.EState, %struct.EState* %107, i32 0, i32 8, !dbg !598
  store i32* %106, i32** %ptr, align 8, !dbg !599
  %108 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !600
  %109 = bitcast %struct.EState* %108 to i8*, !dbg !600
  %110 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !601
  %state94 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %110, i32 0, i32 8, !dbg !602
  store i8* %109, i8** %state94, align 8, !dbg !603
  %111 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !604
  %total_in_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %111, i32 0, i32 2, !dbg !605
  store i32 0, i32* %total_in_lo32, align 4, !dbg !606
  %112 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !607
  %total_in_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %112, i32 0, i32 3, !dbg !608
  store i32 0, i32* %total_in_hi32, align 8, !dbg !609
  %113 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !610
  %total_out_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %113, i32 0, i32 6, !dbg !611
  store i32 0, i32* %total_out_lo32, align 4, !dbg !612
  %114 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !613
  %total_out_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %114, i32 0, i32 7, !dbg !614
  store i32 0, i32* %total_out_hi32, align 8, !dbg !615
  %115 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !616
  call void @init_RL(%struct.EState* %115), !dbg !617
  %116 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !618
  call void @prepare_new_block(%struct.EState* %116), !dbg !619
  store i32 0, i32* %retval, align 4, !dbg !620
  br label %return, !dbg !620

return:                                           ; preds = %if.end86, %if.end85, %if.then24, %if.then8, %if.then
  %117 = load i32, i32* %retval, align 4, !dbg !621
  ret i32 %117, !dbg !621
}

; Function Attrs: nounwind uwtable
define internal i32 @bz_config_ok() #0 !dbg !213 {
entry:
  ret i32 1, !dbg !622
}

; Function Attrs: nounwind uwtable
define internal i8* @default_bzalloc(i8* %opaque, i32 %items, i32 %size) #0 !dbg !216 {
entry:
  %opaque.addr = alloca i8*, align 8
  %items.addr = alloca i32, align 4
  %size.addr = alloca i32, align 4
  %v = alloca i8*, align 8
  store i8* %opaque, i8** %opaque.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %opaque.addr, metadata !623, metadata !392), !dbg !624
  store i32 %items, i32* %items.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %items.addr, metadata !625, metadata !392), !dbg !626
  store i32 %size, i32* %size.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %size.addr, metadata !627, metadata !392), !dbg !628
  call void @llvm.dbg.declare(metadata i8** %v, metadata !629, metadata !392), !dbg !630
  %0 = load i32, i32* %items.addr, align 4, !dbg !631
  %1 = load i32, i32* %size.addr, align 4, !dbg !632
  %mul = mul nsw i32 %0, %1, !dbg !633
  %conv = sext i32 %mul to i64, !dbg !631
  %call = call noalias i8* @malloc(i64 %conv) #10, !dbg !634
  store i8* %call, i8** %v, align 8, !dbg !630
  %2 = load i8*, i8** %opaque.addr, align 8, !dbg !635
  %3 = load i8*, i8** %v, align 8, !dbg !636
  ret i8* %3, !dbg !637
}

; Function Attrs: nounwind uwtable
define internal void @default_bzfree(i8* %opaque, i8* %addr) #0 !dbg !219 {
entry:
  %opaque.addr = alloca i8*, align 8
  %addr.addr = alloca i8*, align 8
  store i8* %opaque, i8** %opaque.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %opaque.addr, metadata !638, metadata !392), !dbg !639
  store i8* %addr, i8** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %addr.addr, metadata !640, metadata !392), !dbg !641
  %0 = load i8*, i8** %addr.addr, align 8, !dbg !642
  %cmp = icmp ne i8* %0, null, !dbg !644
  br i1 %cmp, label %if.then, label %if.end, !dbg !645

if.then:                                          ; preds = %entry
  %1 = load i8*, i8** %addr.addr, align 8, !dbg !646
  call void @free(i8* %1) #10, !dbg !648
  br label %if.end, !dbg !648

if.end:                                           ; preds = %if.then, %entry
  %2 = load i8*, i8** %opaque.addr, align 8, !dbg !649
  ret void, !dbg !650
}

; Function Attrs: nounwind uwtable
define internal void @init_RL(%struct.EState* %s) #0 !dbg !220 {
entry:
  %s.addr = alloca %struct.EState*, align 8
  store %struct.EState* %s, %struct.EState** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.EState** %s.addr, metadata !651, metadata !392), !dbg !652
  %0 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !653
  %state_in_ch = getelementptr inbounds %struct.EState, %struct.EState* %0, i32 0, i32 13, !dbg !654
  store i32 256, i32* %state_in_ch, align 4, !dbg !655
  %1 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !656
  %state_in_len = getelementptr inbounds %struct.EState, %struct.EState* %1, i32 0, i32 14, !dbg !657
  store i32 0, i32* %state_in_len, align 8, !dbg !658
  ret void, !dbg !659
}

; Function Attrs: nounwind uwtable
define internal void @prepare_new_block(%struct.EState* %s) #0 !dbg !283 {
entry:
  %s.addr = alloca %struct.EState*, align 8
  %i = alloca i32, align 4
  store %struct.EState* %s, %struct.EState** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.EState** %s.addr, metadata !660, metadata !392), !dbg !661
  call void @llvm.dbg.declare(metadata i32* %i, metadata !662, metadata !392), !dbg !663
  %0 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !664
  %nblock = getelementptr inbounds %struct.EState, %struct.EState* %0, i32 0, i32 17, !dbg !665
  store i32 0, i32* %nblock, align 4, !dbg !666
  %1 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !667
  %numZ = getelementptr inbounds %struct.EState, %struct.EState* %1, i32 0, i32 19, !dbg !668
  store i32 0, i32* %numZ, align 4, !dbg !669
  %2 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !670
  %state_out_pos = getelementptr inbounds %struct.EState, %struct.EState* %2, i32 0, i32 20, !dbg !671
  store i32 0, i32* %state_out_pos, align 8, !dbg !672
  %3 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !673
  %blockCRC = getelementptr inbounds %struct.EState, %struct.EState* %3, i32 0, i32 26, !dbg !673
  store i32 -1, i32* %blockCRC, align 8, !dbg !673
  store i32 0, i32* %i, align 4, !dbg !675
  br label %for.cond, !dbg !677

for.cond:                                         ; preds = %for.inc, %entry
  %4 = load i32, i32* %i, align 4, !dbg !678
  %cmp = icmp slt i32 %4, 256, !dbg !681
  br i1 %cmp, label %for.body, label %for.end, !dbg !682

for.body:                                         ; preds = %for.cond
  %5 = load i32, i32* %i, align 4, !dbg !683
  %idxprom = sext i32 %5 to i64, !dbg !685
  %6 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !685
  %inUse = getelementptr inbounds %struct.EState, %struct.EState* %6, i32 0, i32 22, !dbg !686
  %arrayidx = getelementptr inbounds [256 x i8], [256 x i8]* %inUse, i64 0, i64 %idxprom, !dbg !685
  store i8 0, i8* %arrayidx, align 1, !dbg !687
  br label %for.inc, !dbg !685

for.inc:                                          ; preds = %for.body
  %7 = load i32, i32* %i, align 4, !dbg !688
  %inc = add nsw i32 %7, 1, !dbg !688
  store i32 %inc, i32* %i, align 4, !dbg !688
  br label %for.cond, !dbg !690

for.end:                                          ; preds = %for.cond
  %8 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !691
  %blockNo = getelementptr inbounds %struct.EState, %struct.EState* %8, i32 0, i32 29, !dbg !692
  %9 = load i32, i32* %blockNo, align 4, !dbg !693
  %inc1 = add nsw i32 %9, 1, !dbg !693
  store i32 %inc1, i32* %blockNo, align 4, !dbg !693
  ret void, !dbg !694
}

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzCompress(%struct.bz_stream* %strm, i32 %action) #0 !dbg !139 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.bz_stream*, align 8
  %action.addr = alloca i32, align 4
  %progress = alloca i8, align 1
  %s = alloca %struct.EState*, align 8
  store %struct.bz_stream* %strm, %struct.bz_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.bz_stream** %strm.addr, metadata !695, metadata !392), !dbg !696
  store i32 %action, i32* %action.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %action.addr, metadata !697, metadata !392), !dbg !698
  call void @llvm.dbg.declare(metadata i8* %progress, metadata !699, metadata !392), !dbg !700
  call void @llvm.dbg.declare(metadata %struct.EState** %s, metadata !701, metadata !392), !dbg !702
  %0 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !703
  %cmp = icmp eq %struct.bz_stream* %0, null, !dbg !705
  br i1 %cmp, label %if.then, label %if.end, !dbg !706

if.then:                                          ; preds = %entry
  store i32 -2, i32* %retval, align 4, !dbg !707
  br label %return, !dbg !707

if.end:                                           ; preds = %entry
  %1 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !709
  %state = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %1, i32 0, i32 8, !dbg !710
  %2 = load i8*, i8** %state, align 8, !dbg !710
  %3 = bitcast i8* %2 to %struct.EState*, !dbg !709
  store %struct.EState* %3, %struct.EState** %s, align 8, !dbg !711
  %4 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !712
  %cmp1 = icmp eq %struct.EState* %4, null, !dbg !714
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !715

if.then2:                                         ; preds = %if.end
  store i32 -2, i32* %retval, align 4, !dbg !716
  br label %return, !dbg !716

if.end3:                                          ; preds = %if.end
  %5 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !718
  %strm4 = getelementptr inbounds %struct.EState, %struct.EState* %5, i32 0, i32 0, !dbg !720
  %6 = load %struct.bz_stream*, %struct.bz_stream** %strm4, align 8, !dbg !720
  %7 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !721
  %cmp5 = icmp ne %struct.bz_stream* %6, %7, !dbg !722
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !723

if.then6:                                         ; preds = %if.end3
  store i32 -2, i32* %retval, align 4, !dbg !724
  br label %return, !dbg !724

if.end7:                                          ; preds = %if.end3
  br label %preswitch, !dbg !726

preswitch:                                        ; preds = %if.then18, %if.then13, %if.end7
  %8 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !728
  %mode = getelementptr inbounds %struct.EState, %struct.EState* %8, i32 0, i32 1, !dbg !729
  %9 = load i32, i32* %mode, align 8, !dbg !729
  switch i32 %9, label %sw.epilog [
    i32 1, label %sw.bb
    i32 2, label %sw.bb8
    i32 3, label %sw.bb23
    i32 4, label %sw.bb47
  ], !dbg !730

sw.bb:                                            ; preds = %preswitch
  store i32 -1, i32* %retval, align 4, !dbg !731
  br label %return, !dbg !731

sw.bb8:                                           ; preds = %preswitch
  %10 = load i32, i32* %action.addr, align 4, !dbg !733
  %cmp9 = icmp eq i32 %10, 0, !dbg !735
  br i1 %cmp9, label %if.then10, label %if.else, !dbg !736

if.then10:                                        ; preds = %sw.bb8
  %11 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !737
  %call = call zeroext i8 @handle_compress(%struct.bz_stream* %11), !dbg !739
  store i8 %call, i8* %progress, align 1, !dbg !740
  %12 = load i8, i8* %progress, align 1, !dbg !741
  %conv = zext i8 %12 to i32, !dbg !741
  %tobool = icmp ne i32 %conv, 0, !dbg !741
  %cond = select i1 %tobool, i32 1, i32 -2, !dbg !741
  store i32 %cond, i32* %retval, align 4, !dbg !742
  br label %return, !dbg !742

if.else:                                          ; preds = %sw.bb8
  %13 = load i32, i32* %action.addr, align 4, !dbg !743
  %cmp11 = icmp eq i32 %13, 1, !dbg !745
  br i1 %cmp11, label %if.then13, label %if.else15, !dbg !746

if.then13:                                        ; preds = %if.else
  %14 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !747
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %14, i32 0, i32 1, !dbg !749
  %15 = load i32, i32* %avail_in, align 8, !dbg !749
  %16 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !750
  %avail_in_expect = getelementptr inbounds %struct.EState, %struct.EState* %16, i32 0, i32 3, !dbg !751
  store i32 %15, i32* %avail_in_expect, align 8, !dbg !752
  %17 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !753
  %mode14 = getelementptr inbounds %struct.EState, %struct.EState* %17, i32 0, i32 1, !dbg !754
  store i32 3, i32* %mode14, align 8, !dbg !755
  br label %preswitch, !dbg !756

if.else15:                                        ; preds = %if.else
  %18 = load i32, i32* %action.addr, align 4, !dbg !757
  %cmp16 = icmp eq i32 %18, 2, !dbg !759
  br i1 %cmp16, label %if.then18, label %if.else22, !dbg !760

if.then18:                                        ; preds = %if.else15
  %19 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !761
  %avail_in19 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %19, i32 0, i32 1, !dbg !763
  %20 = load i32, i32* %avail_in19, align 8, !dbg !763
  %21 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !764
  %avail_in_expect20 = getelementptr inbounds %struct.EState, %struct.EState* %21, i32 0, i32 3, !dbg !765
  store i32 %20, i32* %avail_in_expect20, align 8, !dbg !766
  %22 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !767
  %mode21 = getelementptr inbounds %struct.EState, %struct.EState* %22, i32 0, i32 1, !dbg !768
  store i32 4, i32* %mode21, align 8, !dbg !769
  br label %preswitch, !dbg !770

if.else22:                                        ; preds = %if.else15
  store i32 -2, i32* %retval, align 4, !dbg !771
  br label %return, !dbg !771

sw.bb23:                                          ; preds = %preswitch
  %23 = load i32, i32* %action.addr, align 4, !dbg !772
  %cmp24 = icmp ne i32 %23, 1, !dbg !774
  br i1 %cmp24, label %if.then26, label %if.end27, !dbg !775

if.then26:                                        ; preds = %sw.bb23
  store i32 -1, i32* %retval, align 4, !dbg !776
  br label %return, !dbg !776

if.end27:                                         ; preds = %sw.bb23
  %24 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !778
  %avail_in_expect28 = getelementptr inbounds %struct.EState, %struct.EState* %24, i32 0, i32 3, !dbg !780
  %25 = load i32, i32* %avail_in_expect28, align 8, !dbg !780
  %26 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !781
  %strm29 = getelementptr inbounds %struct.EState, %struct.EState* %26, i32 0, i32 0, !dbg !782
  %27 = load %struct.bz_stream*, %struct.bz_stream** %strm29, align 8, !dbg !782
  %avail_in30 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %27, i32 0, i32 1, !dbg !783
  %28 = load i32, i32* %avail_in30, align 8, !dbg !783
  %cmp31 = icmp ne i32 %25, %28, !dbg !784
  br i1 %cmp31, label %if.then33, label %if.end34, !dbg !785

if.then33:                                        ; preds = %if.end27
  store i32 -1, i32* %retval, align 4, !dbg !786
  br label %return, !dbg !786

if.end34:                                         ; preds = %if.end27
  %29 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !787
  %call35 = call zeroext i8 @handle_compress(%struct.bz_stream* %29), !dbg !788
  store i8 %call35, i8* %progress, align 1, !dbg !789
  %30 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !790
  %avail_in_expect36 = getelementptr inbounds %struct.EState, %struct.EState* %30, i32 0, i32 3, !dbg !792
  %31 = load i32, i32* %avail_in_expect36, align 8, !dbg !792
  %cmp37 = icmp ugt i32 %31, 0, !dbg !793
  br i1 %cmp37, label %if.then44, label %lor.lhs.false, !dbg !794

lor.lhs.false:                                    ; preds = %if.end34
  %32 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !795
  %call39 = call zeroext i8 @isempty_RL(%struct.EState* %32), !dbg !797
  %tobool40 = icmp ne i8 %call39, 0, !dbg !797
  br i1 %tobool40, label %lor.lhs.false41, label %if.then44, !dbg !798

lor.lhs.false41:                                  ; preds = %lor.lhs.false
  %33 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !799
  %state_out_pos = getelementptr inbounds %struct.EState, %struct.EState* %33, i32 0, i32 20, !dbg !800
  %34 = load i32, i32* %state_out_pos, align 8, !dbg !800
  %35 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !801
  %numZ = getelementptr inbounds %struct.EState, %struct.EState* %35, i32 0, i32 19, !dbg !802
  %36 = load i32, i32* %numZ, align 4, !dbg !802
  %cmp42 = icmp slt i32 %34, %36, !dbg !803
  br i1 %cmp42, label %if.then44, label %if.end45, !dbg !804

if.then44:                                        ; preds = %lor.lhs.false41, %lor.lhs.false, %if.end34
  store i32 2, i32* %retval, align 4, !dbg !806
  br label %return, !dbg !806

if.end45:                                         ; preds = %lor.lhs.false41
  %37 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !807
  %mode46 = getelementptr inbounds %struct.EState, %struct.EState* %37, i32 0, i32 1, !dbg !808
  store i32 2, i32* %mode46, align 8, !dbg !809
  store i32 1, i32* %retval, align 4, !dbg !810
  br label %return, !dbg !810

sw.bb47:                                          ; preds = %preswitch
  %38 = load i32, i32* %action.addr, align 4, !dbg !811
  %cmp48 = icmp ne i32 %38, 2, !dbg !813
  br i1 %cmp48, label %if.then50, label %if.end51, !dbg !814

if.then50:                                        ; preds = %sw.bb47
  store i32 -1, i32* %retval, align 4, !dbg !815
  br label %return, !dbg !815

if.end51:                                         ; preds = %sw.bb47
  %39 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !817
  %avail_in_expect52 = getelementptr inbounds %struct.EState, %struct.EState* %39, i32 0, i32 3, !dbg !819
  %40 = load i32, i32* %avail_in_expect52, align 8, !dbg !819
  %41 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !820
  %strm53 = getelementptr inbounds %struct.EState, %struct.EState* %41, i32 0, i32 0, !dbg !821
  %42 = load %struct.bz_stream*, %struct.bz_stream** %strm53, align 8, !dbg !821
  %avail_in54 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %42, i32 0, i32 1, !dbg !822
  %43 = load i32, i32* %avail_in54, align 8, !dbg !822
  %cmp55 = icmp ne i32 %40, %43, !dbg !823
  br i1 %cmp55, label %if.then57, label %if.end58, !dbg !824

if.then57:                                        ; preds = %if.end51
  store i32 -1, i32* %retval, align 4, !dbg !825
  br label %return, !dbg !825

if.end58:                                         ; preds = %if.end51
  %44 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !826
  %call59 = call zeroext i8 @handle_compress(%struct.bz_stream* %44), !dbg !827
  store i8 %call59, i8* %progress, align 1, !dbg !828
  %45 = load i8, i8* %progress, align 1, !dbg !829
  %tobool60 = icmp ne i8 %45, 0, !dbg !829
  br i1 %tobool60, label %if.end62, label %if.then61, !dbg !831

if.then61:                                        ; preds = %if.end58
  store i32 -1, i32* %retval, align 4, !dbg !832
  br label %return, !dbg !832

if.end62:                                         ; preds = %if.end58
  %46 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !834
  %avail_in_expect63 = getelementptr inbounds %struct.EState, %struct.EState* %46, i32 0, i32 3, !dbg !836
  %47 = load i32, i32* %avail_in_expect63, align 8, !dbg !836
  %cmp64 = icmp ugt i32 %47, 0, !dbg !837
  br i1 %cmp64, label %if.then74, label %lor.lhs.false66, !dbg !838

lor.lhs.false66:                                  ; preds = %if.end62
  %48 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !839
  %call67 = call zeroext i8 @isempty_RL(%struct.EState* %48), !dbg !841
  %tobool68 = icmp ne i8 %call67, 0, !dbg !841
  br i1 %tobool68, label %lor.lhs.false69, label %if.then74, !dbg !842

lor.lhs.false69:                                  ; preds = %lor.lhs.false66
  %49 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !843
  %state_out_pos70 = getelementptr inbounds %struct.EState, %struct.EState* %49, i32 0, i32 20, !dbg !844
  %50 = load i32, i32* %state_out_pos70, align 8, !dbg !844
  %51 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !845
  %numZ71 = getelementptr inbounds %struct.EState, %struct.EState* %51, i32 0, i32 19, !dbg !846
  %52 = load i32, i32* %numZ71, align 4, !dbg !846
  %cmp72 = icmp slt i32 %50, %52, !dbg !847
  br i1 %cmp72, label %if.then74, label %if.end75, !dbg !848

if.then74:                                        ; preds = %lor.lhs.false69, %lor.lhs.false66, %if.end62
  store i32 3, i32* %retval, align 4, !dbg !849
  br label %return, !dbg !849

if.end75:                                         ; preds = %lor.lhs.false69
  %53 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !850
  %mode76 = getelementptr inbounds %struct.EState, %struct.EState* %53, i32 0, i32 1, !dbg !851
  store i32 1, i32* %mode76, align 8, !dbg !852
  store i32 4, i32* %retval, align 4, !dbg !853
  br label %return, !dbg !853

sw.epilog:                                        ; preds = %preswitch
  store i32 0, i32* %retval, align 4, !dbg !854
  br label %return, !dbg !854

return:                                           ; preds = %sw.epilog, %if.end75, %if.then74, %if.then61, %if.then57, %if.then50, %if.end45, %if.then44, %if.then33, %if.then26, %if.else22, %if.then10, %sw.bb, %if.then6, %if.then2, %if.then
  %54 = load i32, i32* %retval, align 4, !dbg !855
  ret i32 %54, !dbg !855
}

; Function Attrs: nounwind uwtable
define internal zeroext i8 @handle_compress(%struct.bz_stream* %strm) #0 !dbg !284 {
entry:
  %strm.addr = alloca %struct.bz_stream*, align 8
  %progress_in = alloca i8, align 1
  %progress_out = alloca i8, align 1
  %s = alloca %struct.EState*, align 8
  store %struct.bz_stream* %strm, %struct.bz_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.bz_stream** %strm.addr, metadata !856, metadata !392), !dbg !857
  call void @llvm.dbg.declare(metadata i8* %progress_in, metadata !858, metadata !392), !dbg !859
  store i8 0, i8* %progress_in, align 1, !dbg !859
  call void @llvm.dbg.declare(metadata i8* %progress_out, metadata !860, metadata !392), !dbg !861
  store i8 0, i8* %progress_out, align 1, !dbg !861
  call void @llvm.dbg.declare(metadata %struct.EState** %s, metadata !862, metadata !392), !dbg !863
  %0 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !864
  %state = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %0, i32 0, i32 8, !dbg !865
  %1 = load i8*, i8** %state, align 8, !dbg !865
  %2 = bitcast i8* %1 to %struct.EState*, !dbg !864
  store %struct.EState* %2, %struct.EState** %s, align 8, !dbg !863
  br label %while.body, !dbg !866

while.body:                                       ; preds = %entry, %if.end65
  %3 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !867
  %state1 = getelementptr inbounds %struct.EState, %struct.EState* %3, i32 0, i32 2, !dbg !870
  %4 = load i32, i32* %state1, align 4, !dbg !870
  %cmp = icmp eq i32 %4, 1, !dbg !871
  br i1 %cmp, label %if.then, label %if.end30, !dbg !872

if.then:                                          ; preds = %while.body
  %5 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !873
  %call = call zeroext i8 @copy_output_until_stop(%struct.EState* %5), !dbg !875
  %conv = zext i8 %call to i32, !dbg !875
  %6 = load i8, i8* %progress_out, align 1, !dbg !876
  %conv2 = zext i8 %6 to i32, !dbg !876
  %or = or i32 %conv2, %conv, !dbg !876
  %conv3 = trunc i32 %or to i8, !dbg !876
  store i8 %conv3, i8* %progress_out, align 1, !dbg !876
  %7 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !877
  %state_out_pos = getelementptr inbounds %struct.EState, %struct.EState* %7, i32 0, i32 20, !dbg !879
  %8 = load i32, i32* %state_out_pos, align 8, !dbg !879
  %9 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !880
  %numZ = getelementptr inbounds %struct.EState, %struct.EState* %9, i32 0, i32 19, !dbg !881
  %10 = load i32, i32* %numZ, align 4, !dbg !881
  %cmp4 = icmp slt i32 %8, %10, !dbg !882
  br i1 %cmp4, label %if.then6, label %if.end, !dbg !883

if.then6:                                         ; preds = %if.then
  br label %while.end, !dbg !884

if.end:                                           ; preds = %if.then
  %11 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !886
  %mode = getelementptr inbounds %struct.EState, %struct.EState* %11, i32 0, i32 1, !dbg !888
  %12 = load i32, i32* %mode, align 8, !dbg !888
  %cmp7 = icmp eq i32 %12, 4, !dbg !889
  br i1 %cmp7, label %land.lhs.true, label %if.end15, !dbg !890

land.lhs.true:                                    ; preds = %if.end
  %13 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !891
  %avail_in_expect = getelementptr inbounds %struct.EState, %struct.EState* %13, i32 0, i32 3, !dbg !892
  %14 = load i32, i32* %avail_in_expect, align 8, !dbg !892
  %cmp9 = icmp eq i32 %14, 0, !dbg !893
  br i1 %cmp9, label %land.lhs.true11, label %if.end15, !dbg !894

land.lhs.true11:                                  ; preds = %land.lhs.true
  %15 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !895
  %call12 = call zeroext i8 @isempty_RL(%struct.EState* %15), !dbg !896
  %conv13 = zext i8 %call12 to i32, !dbg !896
  %tobool = icmp ne i32 %conv13, 0, !dbg !896
  br i1 %tobool, label %if.then14, label %if.end15, !dbg !897

if.then14:                                        ; preds = %land.lhs.true11
  br label %while.end, !dbg !899

if.end15:                                         ; preds = %land.lhs.true11, %land.lhs.true, %if.end
  %16 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !901
  call void @prepare_new_block(%struct.EState* %16), !dbg !902
  %17 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !903
  %state16 = getelementptr inbounds %struct.EState, %struct.EState* %17, i32 0, i32 2, !dbg !904
  store i32 2, i32* %state16, align 4, !dbg !905
  %18 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !906
  %mode17 = getelementptr inbounds %struct.EState, %struct.EState* %18, i32 0, i32 1, !dbg !908
  %19 = load i32, i32* %mode17, align 8, !dbg !908
  %cmp18 = icmp eq i32 %19, 3, !dbg !909
  br i1 %cmp18, label %land.lhs.true20, label %if.end29, !dbg !910

land.lhs.true20:                                  ; preds = %if.end15
  %20 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !911
  %avail_in_expect21 = getelementptr inbounds %struct.EState, %struct.EState* %20, i32 0, i32 3, !dbg !912
  %21 = load i32, i32* %avail_in_expect21, align 8, !dbg !912
  %cmp22 = icmp eq i32 %21, 0, !dbg !913
  br i1 %cmp22, label %land.lhs.true24, label %if.end29, !dbg !914

land.lhs.true24:                                  ; preds = %land.lhs.true20
  %22 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !915
  %call25 = call zeroext i8 @isempty_RL(%struct.EState* %22), !dbg !916
  %conv26 = zext i8 %call25 to i32, !dbg !916
  %tobool27 = icmp ne i32 %conv26, 0, !dbg !916
  br i1 %tobool27, label %if.then28, label %if.end29, !dbg !917

if.then28:                                        ; preds = %land.lhs.true24
  br label %while.end, !dbg !918

if.end29:                                         ; preds = %land.lhs.true24, %land.lhs.true20, %if.end15
  br label %if.end30, !dbg !920

if.end30:                                         ; preds = %if.end29, %while.body
  %23 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !921
  %state31 = getelementptr inbounds %struct.EState, %struct.EState* %23, i32 0, i32 2, !dbg !923
  %24 = load i32, i32* %state31, align 4, !dbg !923
  %cmp32 = icmp eq i32 %24, 2, !dbg !924
  br i1 %cmp32, label %if.then34, label %if.end65, !dbg !925

if.then34:                                        ; preds = %if.end30
  %25 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !926
  %call35 = call zeroext i8 @copy_input_until_stop(%struct.EState* %25), !dbg !928
  %conv36 = zext i8 %call35 to i32, !dbg !928
  %26 = load i8, i8* %progress_in, align 1, !dbg !929
  %conv37 = zext i8 %26 to i32, !dbg !929
  %or38 = or i32 %conv37, %conv36, !dbg !929
  %conv39 = trunc i32 %or38 to i8, !dbg !929
  store i8 %conv39, i8* %progress_in, align 1, !dbg !929
  %27 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !930
  %mode40 = getelementptr inbounds %struct.EState, %struct.EState* %27, i32 0, i32 1, !dbg !932
  %28 = load i32, i32* %mode40, align 8, !dbg !932
  %cmp41 = icmp ne i32 %28, 2, !dbg !933
  br i1 %cmp41, label %land.lhs.true43, label %if.else, !dbg !934

land.lhs.true43:                                  ; preds = %if.then34
  %29 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !935
  %avail_in_expect44 = getelementptr inbounds %struct.EState, %struct.EState* %29, i32 0, i32 3, !dbg !937
  %30 = load i32, i32* %avail_in_expect44, align 8, !dbg !937
  %cmp45 = icmp eq i32 %30, 0, !dbg !938
  br i1 %cmp45, label %if.then47, label %if.else, !dbg !939

if.then47:                                        ; preds = %land.lhs.true43
  %31 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !940
  call void @flush_RL(%struct.EState* %31), !dbg !942
  %32 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !943
  %33 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !944
  %mode48 = getelementptr inbounds %struct.EState, %struct.EState* %33, i32 0, i32 1, !dbg !945
  %34 = load i32, i32* %mode48, align 8, !dbg !945
  %cmp49 = icmp eq i32 %34, 4, !dbg !946
  %conv50 = zext i1 %cmp49 to i32, !dbg !946
  %conv51 = trunc i32 %conv50 to i8, !dbg !947
  call void @BZ2_compressBlock(%struct.EState* %32, i8 zeroext %conv51), !dbg !948
  %35 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !949
  %state52 = getelementptr inbounds %struct.EState, %struct.EState* %35, i32 0, i32 2, !dbg !950
  store i32 1, i32* %state52, align 4, !dbg !951
  br label %if.end64, !dbg !952

if.else:                                          ; preds = %land.lhs.true43, %if.then34
  %36 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !953
  %nblock = getelementptr inbounds %struct.EState, %struct.EState* %36, i32 0, i32 17, !dbg !955
  %37 = load i32, i32* %nblock, align 4, !dbg !955
  %38 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !956
  %nblockMAX = getelementptr inbounds %struct.EState, %struct.EState* %38, i32 0, i32 18, !dbg !957
  %39 = load i32, i32* %nblockMAX, align 8, !dbg !957
  %cmp53 = icmp sge i32 %37, %39, !dbg !958
  br i1 %cmp53, label %if.then55, label %if.else57, !dbg !959

if.then55:                                        ; preds = %if.else
  %40 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !960
  call void @BZ2_compressBlock(%struct.EState* %40, i8 zeroext 0), !dbg !962
  %41 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !963
  %state56 = getelementptr inbounds %struct.EState, %struct.EState* %41, i32 0, i32 2, !dbg !964
  store i32 1, i32* %state56, align 4, !dbg !965
  br label %if.end63, !dbg !966

if.else57:                                        ; preds = %if.else
  %42 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !967
  %strm58 = getelementptr inbounds %struct.EState, %struct.EState* %42, i32 0, i32 0, !dbg !969
  %43 = load %struct.bz_stream*, %struct.bz_stream** %strm58, align 8, !dbg !969
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %43, i32 0, i32 1, !dbg !970
  %44 = load i32, i32* %avail_in, align 8, !dbg !970
  %cmp59 = icmp eq i32 %44, 0, !dbg !971
  br i1 %cmp59, label %if.then61, label %if.end62, !dbg !972

if.then61:                                        ; preds = %if.else57
  br label %while.end, !dbg !973

if.end62:                                         ; preds = %if.else57
  br label %if.end63

if.end63:                                         ; preds = %if.end62, %if.then55
  br label %if.end64

if.end64:                                         ; preds = %if.end63, %if.then47
  br label %if.end65, !dbg !975

if.end65:                                         ; preds = %if.end64, %if.end30
  br label %while.body, !dbg !976

while.end:                                        ; preds = %if.then61, %if.then28, %if.then14, %if.then6
  %45 = load i8, i8* %progress_in, align 1, !dbg !978
  %conv66 = zext i8 %45 to i32, !dbg !978
  %tobool67 = icmp ne i32 %conv66, 0, !dbg !978
  br i1 %tobool67, label %lor.end, label %lor.rhs, !dbg !979

lor.rhs:                                          ; preds = %while.end
  %46 = load i8, i8* %progress_out, align 1, !dbg !980
  %conv68 = zext i8 %46 to i32, !dbg !980
  %tobool69 = icmp ne i32 %conv68, 0, !dbg !981
  br label %lor.end, !dbg !981

lor.end:                                          ; preds = %lor.rhs, %while.end
  %47 = phi i1 [ true, %while.end ], [ %tobool69, %lor.rhs ]
  %lor.ext = zext i1 %47 to i32, !dbg !982
  %conv70 = trunc i32 %lor.ext to i8, !dbg !984
  ret i8 %conv70, !dbg !985
}

; Function Attrs: nounwind uwtable
define internal zeroext i8 @isempty_RL(%struct.EState* %s) #0 !dbg !293 {
entry:
  %retval = alloca i8, align 1
  %s.addr = alloca %struct.EState*, align 8
  store %struct.EState* %s, %struct.EState** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.EState** %s.addr, metadata !986, metadata !392), !dbg !987
  %0 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !988
  %state_in_ch = getelementptr inbounds %struct.EState, %struct.EState* %0, i32 0, i32 13, !dbg !990
  %1 = load i32, i32* %state_in_ch, align 4, !dbg !990
  %cmp = icmp ult i32 %1, 256, !dbg !991
  br i1 %cmp, label %land.lhs.true, label %if.else, !dbg !992

land.lhs.true:                                    ; preds = %entry
  %2 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !993
  %state_in_len = getelementptr inbounds %struct.EState, %struct.EState* %2, i32 0, i32 14, !dbg !995
  %3 = load i32, i32* %state_in_len, align 8, !dbg !995
  %cmp1 = icmp sgt i32 %3, 0, !dbg !996
  br i1 %cmp1, label %if.then, label %if.else, !dbg !997

if.then:                                          ; preds = %land.lhs.true
  store i8 0, i8* %retval, align 1, !dbg !998
  br label %return, !dbg !998

if.else:                                          ; preds = %land.lhs.true, %entry
  store i8 1, i8* %retval, align 1, !dbg !999
  br label %return, !dbg !999

return:                                           ; preds = %if.else, %if.then
  %4 = load i8, i8* %retval, align 1, !dbg !1000
  ret i8 %4, !dbg !1000
}

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzCompressEnd(%struct.bz_stream* %strm) #0 !dbg !142 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.bz_stream*, align 8
  %s = alloca %struct.EState*, align 8
  store %struct.bz_stream* %strm, %struct.bz_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.bz_stream** %strm.addr, metadata !1001, metadata !392), !dbg !1002
  call void @llvm.dbg.declare(metadata %struct.EState** %s, metadata !1003, metadata !392), !dbg !1004
  %0 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1005
  %cmp = icmp eq %struct.bz_stream* %0, null, !dbg !1007
  br i1 %cmp, label %if.then, label %if.end, !dbg !1008

if.then:                                          ; preds = %entry
  store i32 -2, i32* %retval, align 4, !dbg !1009
  br label %return, !dbg !1009

if.end:                                           ; preds = %entry
  %1 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1011
  %state = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %1, i32 0, i32 8, !dbg !1012
  %2 = load i8*, i8** %state, align 8, !dbg !1012
  %3 = bitcast i8* %2 to %struct.EState*, !dbg !1011
  store %struct.EState* %3, %struct.EState** %s, align 8, !dbg !1013
  %4 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !1014
  %cmp1 = icmp eq %struct.EState* %4, null, !dbg !1016
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1017

if.then2:                                         ; preds = %if.end
  store i32 -2, i32* %retval, align 4, !dbg !1018
  br label %return, !dbg !1018

if.end3:                                          ; preds = %if.end
  %5 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !1020
  %strm4 = getelementptr inbounds %struct.EState, %struct.EState* %5, i32 0, i32 0, !dbg !1022
  %6 = load %struct.bz_stream*, %struct.bz_stream** %strm4, align 8, !dbg !1022
  %7 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1023
  %cmp5 = icmp ne %struct.bz_stream* %6, %7, !dbg !1024
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !1025

if.then6:                                         ; preds = %if.end3
  store i32 -2, i32* %retval, align 4, !dbg !1026
  br label %return, !dbg !1026

if.end7:                                          ; preds = %if.end3
  %8 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !1028
  %arr1 = getelementptr inbounds %struct.EState, %struct.EState* %8, i32 0, i32 4, !dbg !1030
  %9 = load i32*, i32** %arr1, align 8, !dbg !1030
  %cmp8 = icmp ne i32* %9, null, !dbg !1031
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !1032

if.then9:                                         ; preds = %if.end7
  %10 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1033
  %bzfree = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %10, i32 0, i32 10, !dbg !1033
  %11 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree, align 8, !dbg !1033
  %12 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1033
  %opaque = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %12, i32 0, i32 11, !dbg !1033
  %13 = load i8*, i8** %opaque, align 8, !dbg !1033
  %14 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !1033
  %arr110 = getelementptr inbounds %struct.EState, %struct.EState* %14, i32 0, i32 4, !dbg !1033
  %15 = load i32*, i32** %arr110, align 8, !dbg !1033
  %16 = bitcast i32* %15 to i8*, !dbg !1033
  call void %11(i8* %13, i8* %16), !dbg !1033
  br label %if.end11, !dbg !1033

if.end11:                                         ; preds = %if.then9, %if.end7
  %17 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !1035
  %arr2 = getelementptr inbounds %struct.EState, %struct.EState* %17, i32 0, i32 5, !dbg !1037
  %18 = load i32*, i32** %arr2, align 8, !dbg !1037
  %cmp12 = icmp ne i32* %18, null, !dbg !1038
  br i1 %cmp12, label %if.then13, label %if.end17, !dbg !1039

if.then13:                                        ; preds = %if.end11
  %19 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1040
  %bzfree14 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %19, i32 0, i32 10, !dbg !1040
  %20 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree14, align 8, !dbg !1040
  %21 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1040
  %opaque15 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %21, i32 0, i32 11, !dbg !1040
  %22 = load i8*, i8** %opaque15, align 8, !dbg !1040
  %23 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !1040
  %arr216 = getelementptr inbounds %struct.EState, %struct.EState* %23, i32 0, i32 5, !dbg !1040
  %24 = load i32*, i32** %arr216, align 8, !dbg !1040
  %25 = bitcast i32* %24 to i8*, !dbg !1040
  call void %20(i8* %22, i8* %25), !dbg !1040
  br label %if.end17, !dbg !1040

if.end17:                                         ; preds = %if.then13, %if.end11
  %26 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !1042
  %ftab = getelementptr inbounds %struct.EState, %struct.EState* %26, i32 0, i32 6, !dbg !1044
  %27 = load i32*, i32** %ftab, align 8, !dbg !1044
  %cmp18 = icmp ne i32* %27, null, !dbg !1045
  br i1 %cmp18, label %if.then19, label %if.end23, !dbg !1046

if.then19:                                        ; preds = %if.end17
  %28 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1047
  %bzfree20 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %28, i32 0, i32 10, !dbg !1047
  %29 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree20, align 8, !dbg !1047
  %30 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1047
  %opaque21 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %30, i32 0, i32 11, !dbg !1047
  %31 = load i8*, i8** %opaque21, align 8, !dbg !1047
  %32 = load %struct.EState*, %struct.EState** %s, align 8, !dbg !1047
  %ftab22 = getelementptr inbounds %struct.EState, %struct.EState* %32, i32 0, i32 6, !dbg !1047
  %33 = load i32*, i32** %ftab22, align 8, !dbg !1047
  %34 = bitcast i32* %33 to i8*, !dbg !1047
  call void %29(i8* %31, i8* %34), !dbg !1047
  br label %if.end23, !dbg !1047

if.end23:                                         ; preds = %if.then19, %if.end17
  %35 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1049
  %bzfree24 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %35, i32 0, i32 10, !dbg !1049
  %36 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree24, align 8, !dbg !1049
  %37 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1049
  %opaque25 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %37, i32 0, i32 11, !dbg !1049
  %38 = load i8*, i8** %opaque25, align 8, !dbg !1049
  %39 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1049
  %state26 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %39, i32 0, i32 8, !dbg !1049
  %40 = load i8*, i8** %state26, align 8, !dbg !1049
  call void %36(i8* %38, i8* %40), !dbg !1049
  %41 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1050
  %state27 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %41, i32 0, i32 8, !dbg !1051
  store i8* null, i8** %state27, align 8, !dbg !1052
  store i32 0, i32* %retval, align 4, !dbg !1053
  br label %return, !dbg !1053

return:                                           ; preds = %if.end23, %if.then6, %if.then2, %if.then
  %42 = load i32, i32* %retval, align 4, !dbg !1054
  ret i32 %42, !dbg !1054
}

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzDecompressInit(%struct.bz_stream* %strm, i32 %verbosity, i32 %small) #0 !dbg !145 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.bz_stream*, align 8
  %verbosity.addr = alloca i32, align 4
  %small.addr = alloca i32, align 4
  %s = alloca %struct.DState*, align 8
  store %struct.bz_stream* %strm, %struct.bz_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.bz_stream** %strm.addr, metadata !1055, metadata !392), !dbg !1056
  store i32 %verbosity, i32* %verbosity.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %verbosity.addr, metadata !1057, metadata !392), !dbg !1058
  store i32 %small, i32* %small.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %small.addr, metadata !1059, metadata !392), !dbg !1060
  call void @llvm.dbg.declare(metadata %struct.DState** %s, metadata !1061, metadata !392), !dbg !1062
  %call = call i32 @bz_config_ok(), !dbg !1063
  %tobool = icmp ne i32 %call, 0, !dbg !1063
  br i1 %tobool, label %if.end, label %if.then, !dbg !1065

if.then:                                          ; preds = %entry
  store i32 -9, i32* %retval, align 4, !dbg !1066
  br label %return, !dbg !1066

if.end:                                           ; preds = %entry
  %0 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1068
  %cmp = icmp eq %struct.bz_stream* %0, null, !dbg !1070
  br i1 %cmp, label %if.then1, label %if.end2, !dbg !1071

if.then1:                                         ; preds = %if.end
  store i32 -2, i32* %retval, align 4, !dbg !1072
  br label %return, !dbg !1072

if.end2:                                          ; preds = %if.end
  %1 = load i32, i32* %small.addr, align 4, !dbg !1074
  %cmp3 = icmp ne i32 %1, 0, !dbg !1076
  br i1 %cmp3, label %land.lhs.true, label %if.end6, !dbg !1077

land.lhs.true:                                    ; preds = %if.end2
  %2 = load i32, i32* %small.addr, align 4, !dbg !1078
  %cmp4 = icmp ne i32 %2, 1, !dbg !1080
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !1081

if.then5:                                         ; preds = %land.lhs.true
  store i32 -2, i32* %retval, align 4, !dbg !1082
  br label %return, !dbg !1082

if.end6:                                          ; preds = %land.lhs.true, %if.end2
  %3 = load i32, i32* %verbosity.addr, align 4, !dbg !1084
  %cmp7 = icmp slt i32 %3, 0, !dbg !1086
  br i1 %cmp7, label %if.then9, label %lor.lhs.false, !dbg !1087

lor.lhs.false:                                    ; preds = %if.end6
  %4 = load i32, i32* %verbosity.addr, align 4, !dbg !1088
  %cmp8 = icmp sgt i32 %4, 4, !dbg !1090
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !1091

if.then9:                                         ; preds = %lor.lhs.false, %if.end6
  store i32 -2, i32* %retval, align 4, !dbg !1092
  br label %return, !dbg !1092

if.end10:                                         ; preds = %lor.lhs.false
  %5 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1094
  %bzalloc = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %5, i32 0, i32 9, !dbg !1096
  %6 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %bzalloc, align 8, !dbg !1096
  %cmp11 = icmp eq i8* (i8*, i32, i32)* %6, null, !dbg !1097
  br i1 %cmp11, label %if.then12, label %if.end14, !dbg !1098

if.then12:                                        ; preds = %if.end10
  %7 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1099
  %bzalloc13 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %7, i32 0, i32 9, !dbg !1101
  store i8* (i8*, i32, i32)* @default_bzalloc, i8* (i8*, i32, i32)** %bzalloc13, align 8, !dbg !1102
  br label %if.end14, !dbg !1099

if.end14:                                         ; preds = %if.then12, %if.end10
  %8 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1103
  %bzfree = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %8, i32 0, i32 10, !dbg !1105
  %9 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree, align 8, !dbg !1105
  %cmp15 = icmp eq void (i8*, i8*)* %9, null, !dbg !1106
  br i1 %cmp15, label %if.then16, label %if.end18, !dbg !1107

if.then16:                                        ; preds = %if.end14
  %10 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1108
  %bzfree17 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %10, i32 0, i32 10, !dbg !1110
  store void (i8*, i8*)* @default_bzfree, void (i8*, i8*)** %bzfree17, align 8, !dbg !1111
  br label %if.end18, !dbg !1108

if.end18:                                         ; preds = %if.then16, %if.end14
  %11 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1112
  %bzalloc19 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %11, i32 0, i32 9, !dbg !1112
  %12 = load i8* (i8*, i32, i32)*, i8* (i8*, i32, i32)** %bzalloc19, align 8, !dbg !1112
  %13 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1112
  %opaque = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %13, i32 0, i32 11, !dbg !1112
  %14 = load i8*, i8** %opaque, align 8, !dbg !1112
  %call20 = call i8* %12(i8* %14, i32 64144, i32 1), !dbg !1112
  %15 = bitcast i8* %call20 to %struct.DState*, !dbg !1112
  store %struct.DState* %15, %struct.DState** %s, align 8, !dbg !1113
  %16 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1114
  %cmp21 = icmp eq %struct.DState* %16, null, !dbg !1116
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !1117

if.then22:                                        ; preds = %if.end18
  store i32 -3, i32* %retval, align 4, !dbg !1118
  br label %return, !dbg !1118

if.end23:                                         ; preds = %if.end18
  %17 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1120
  %18 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1121
  %strm24 = getelementptr inbounds %struct.DState, %struct.DState* %18, i32 0, i32 0, !dbg !1122
  store %struct.bz_stream* %17, %struct.bz_stream** %strm24, align 8, !dbg !1123
  %19 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1124
  %20 = bitcast %struct.DState* %19 to i8*, !dbg !1124
  %21 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1125
  %state = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %21, i32 0, i32 8, !dbg !1126
  store i8* %20, i8** %state, align 8, !dbg !1127
  %22 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1128
  %state25 = getelementptr inbounds %struct.DState, %struct.DState* %22, i32 0, i32 1, !dbg !1129
  store i32 10, i32* %state25, align 8, !dbg !1130
  %23 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1131
  %bsLive = getelementptr inbounds %struct.DState, %struct.DState* %23, i32 0, i32 8, !dbg !1132
  store i32 0, i32* %bsLive, align 4, !dbg !1133
  %24 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1134
  %bsBuff = getelementptr inbounds %struct.DState, %struct.DState* %24, i32 0, i32 7, !dbg !1135
  store i32 0, i32* %bsBuff, align 8, !dbg !1136
  %25 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1137
  %calculatedCombinedCRC = getelementptr inbounds %struct.DState, %struct.DState* %25, i32 0, i32 26, !dbg !1138
  store i32 0, i32* %calculatedCombinedCRC, align 4, !dbg !1139
  %26 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1140
  %total_in_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %26, i32 0, i32 2, !dbg !1141
  store i32 0, i32* %total_in_lo32, align 4, !dbg !1142
  %27 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1143
  %total_in_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %27, i32 0, i32 3, !dbg !1144
  store i32 0, i32* %total_in_hi32, align 8, !dbg !1145
  %28 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1146
  %total_out_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %28, i32 0, i32 6, !dbg !1147
  store i32 0, i32* %total_out_lo32, align 4, !dbg !1148
  %29 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1149
  %total_out_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %29, i32 0, i32 7, !dbg !1150
  store i32 0, i32* %total_out_hi32, align 8, !dbg !1151
  %30 = load i32, i32* %small.addr, align 4, !dbg !1152
  %conv = trunc i32 %30 to i8, !dbg !1153
  %31 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1154
  %smallDecompress = getelementptr inbounds %struct.DState, %struct.DState* %31, i32 0, i32 10, !dbg !1155
  store i8 %conv, i8* %smallDecompress, align 4, !dbg !1156
  %32 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1157
  %ll4 = getelementptr inbounds %struct.DState, %struct.DState* %32, i32 0, i32 22, !dbg !1158
  store i8* null, i8** %ll4, align 8, !dbg !1159
  %33 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1160
  %ll16 = getelementptr inbounds %struct.DState, %struct.DState* %33, i32 0, i32 21, !dbg !1161
  store i16* null, i16** %ll16, align 8, !dbg !1162
  %34 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1163
  %tt = getelementptr inbounds %struct.DState, %struct.DState* %34, i32 0, i32 20, !dbg !1164
  store i32* null, i32** %tt, align 8, !dbg !1165
  %35 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1166
  %currBlockNo = getelementptr inbounds %struct.DState, %struct.DState* %35, i32 0, i32 11, !dbg !1167
  store i32 0, i32* %currBlockNo, align 8, !dbg !1168
  %36 = load i32, i32* %verbosity.addr, align 4, !dbg !1169
  %37 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1170
  %verbosity26 = getelementptr inbounds %struct.DState, %struct.DState* %37, i32 0, i32 12, !dbg !1171
  store i32 %36, i32* %verbosity26, align 4, !dbg !1172
  store i32 0, i32* %retval, align 4, !dbg !1173
  br label %return, !dbg !1173

return:                                           ; preds = %if.end23, %if.then22, %if.then9, %if.then5, %if.then1, %if.then
  %38 = load i32, i32* %retval, align 4, !dbg !1174
  ret i32 %38, !dbg !1174
}

; Function Attrs: inlinehint nounwind uwtable
define i32 @BZ2_indexIntoF(i32 %indx, i32* %cftab) #4 !dbg !148 {
entry:
  %indx.addr = alloca i32, align 4
  %cftab.addr = alloca i32*, align 8
  %nb = alloca i32, align 4
  %na = alloca i32, align 4
  %mid = alloca i32, align 4
  store i32 %indx, i32* %indx.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %indx.addr, metadata !1175, metadata !392), !dbg !1176
  store i32* %cftab, i32** %cftab.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %cftab.addr, metadata !1177, metadata !392), !dbg !1178
  call void @llvm.dbg.declare(metadata i32* %nb, metadata !1179, metadata !392), !dbg !1180
  call void @llvm.dbg.declare(metadata i32* %na, metadata !1181, metadata !392), !dbg !1182
  call void @llvm.dbg.declare(metadata i32* %mid, metadata !1183, metadata !392), !dbg !1184
  store i32 0, i32* %nb, align 4, !dbg !1185
  store i32 256, i32* %na, align 4, !dbg !1186
  br label %do.body, !dbg !1187

do.body:                                          ; preds = %do.cond, %entry
  %0 = load i32, i32* %nb, align 4, !dbg !1188
  %1 = load i32, i32* %na, align 4, !dbg !1190
  %add = add nsw i32 %0, %1, !dbg !1191
  %shr = ashr i32 %add, 1, !dbg !1192
  store i32 %shr, i32* %mid, align 4, !dbg !1193
  %2 = load i32, i32* %indx.addr, align 4, !dbg !1194
  %3 = load i32, i32* %mid, align 4, !dbg !1196
  %idxprom = sext i32 %3 to i64, !dbg !1197
  %4 = load i32*, i32** %cftab.addr, align 8, !dbg !1197
  %arrayidx = getelementptr inbounds i32, i32* %4, i64 %idxprom, !dbg !1197
  %5 = load i32, i32* %arrayidx, align 4, !dbg !1197
  %cmp = icmp sge i32 %2, %5, !dbg !1198
  br i1 %cmp, label %if.then, label %if.else, !dbg !1199

if.then:                                          ; preds = %do.body
  %6 = load i32, i32* %mid, align 4, !dbg !1200
  store i32 %6, i32* %nb, align 4, !dbg !1202
  br label %if.end, !dbg !1203

if.else:                                          ; preds = %do.body
  %7 = load i32, i32* %mid, align 4, !dbg !1204
  store i32 %7, i32* %na, align 4, !dbg !1206
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %do.cond, !dbg !1207

do.cond:                                          ; preds = %if.end
  %8 = load i32, i32* %na, align 4, !dbg !1208
  %9 = load i32, i32* %nb, align 4, !dbg !1209
  %sub = sub nsw i32 %8, %9, !dbg !1210
  %cmp1 = icmp ne i32 %sub, 1, !dbg !1211
  br i1 %cmp1, label %do.body, label %do.end, !dbg !1212

do.end:                                           ; preds = %do.cond
  %10 = load i32, i32* %nb, align 4, !dbg !1214
  ret i32 %10, !dbg !1215
}

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzDecompress(%struct.bz_stream* %strm) #0 !dbg !152 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.bz_stream*, align 8
  %corrupt = alloca i8, align 1
  %s = alloca %struct.DState*, align 8
  %r = alloca i32, align 4
  store %struct.bz_stream* %strm, %struct.bz_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.bz_stream** %strm.addr, metadata !1216, metadata !392), !dbg !1217
  call void @llvm.dbg.declare(metadata i8* %corrupt, metadata !1218, metadata !392), !dbg !1219
  call void @llvm.dbg.declare(metadata %struct.DState** %s, metadata !1220, metadata !392), !dbg !1221
  %0 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1222
  %cmp = icmp eq %struct.bz_stream* %0, null, !dbg !1224
  br i1 %cmp, label %if.then, label %if.end, !dbg !1225

if.then:                                          ; preds = %entry
  store i32 -2, i32* %retval, align 4, !dbg !1226
  br label %return, !dbg !1226

if.end:                                           ; preds = %entry
  %1 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1228
  %state = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %1, i32 0, i32 8, !dbg !1229
  %2 = load i8*, i8** %state, align 8, !dbg !1229
  %3 = bitcast i8* %2 to %struct.DState*, !dbg !1228
  store %struct.DState* %3, %struct.DState** %s, align 8, !dbg !1230
  %4 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1231
  %cmp1 = icmp eq %struct.DState* %4, null, !dbg !1233
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !1234

if.then2:                                         ; preds = %if.end
  store i32 -2, i32* %retval, align 4, !dbg !1235
  br label %return, !dbg !1235

if.end3:                                          ; preds = %if.end
  %5 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1237
  %strm4 = getelementptr inbounds %struct.DState, %struct.DState* %5, i32 0, i32 0, !dbg !1239
  %6 = load %struct.bz_stream*, %struct.bz_stream** %strm4, align 8, !dbg !1239
  %7 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !1240
  %cmp5 = icmp ne %struct.bz_stream* %6, %7, !dbg !1241
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !1242

if.then6:                                         ; preds = %if.end3
  store i32 -2, i32* %retval, align 4, !dbg !1243
  br label %return, !dbg !1243

if.end7:                                          ; preds = %if.end3
  br label %while.body, !dbg !1245

while.body:                                       ; preds = %if.end7, %if.end70
  %8 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1246
  %state8 = getelementptr inbounds %struct.DState, %struct.DState* %8, i32 0, i32 1, !dbg !1249
  %9 = load i32, i32* %state8, align 8, !dbg !1249
  %cmp9 = icmp eq i32 %9, 1, !dbg !1250
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !1251

if.then10:                                        ; preds = %while.body
  store i32 -1, i32* %retval, align 4, !dbg !1252
  br label %return, !dbg !1252

if.end11:                                         ; preds = %while.body
  %10 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1254
  %state12 = getelementptr inbounds %struct.DState, %struct.DState* %10, i32 0, i32 1, !dbg !1256
  %11 = load i32, i32* %state12, align 8, !dbg !1256
  %cmp13 = icmp eq i32 %11, 2, !dbg !1257
  br i1 %cmp13, label %if.then14, label %if.end47, !dbg !1258

if.then14:                                        ; preds = %if.end11
  %12 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1259
  %smallDecompress = getelementptr inbounds %struct.DState, %struct.DState* %12, i32 0, i32 10, !dbg !1262
  %13 = load i8, i8* %smallDecompress, align 4, !dbg !1262
  %tobool = icmp ne i8 %13, 0, !dbg !1259
  br i1 %tobool, label %if.then15, label %if.else, !dbg !1263

if.then15:                                        ; preds = %if.then14
  %14 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1264
  %call = call zeroext i8 @unRLE_obuf_to_output_SMALL(%struct.DState* %14), !dbg !1265
  store i8 %call, i8* %corrupt, align 1, !dbg !1266
  br label %if.end17, !dbg !1267

if.else:                                          ; preds = %if.then14
  %15 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1268
  %call16 = call zeroext i8 @unRLE_obuf_to_output_FAST(%struct.DState* %15), !dbg !1269
  store i8 %call16, i8* %corrupt, align 1, !dbg !1270
  br label %if.end17

if.end17:                                         ; preds = %if.else, %if.then15
  %16 = load i8, i8* %corrupt, align 1, !dbg !1271
  %tobool18 = icmp ne i8 %16, 0, !dbg !1271
  br i1 %tobool18, label %if.then19, label %if.end20, !dbg !1273

if.then19:                                        ; preds = %if.end17
  store i32 -4, i32* %retval, align 4, !dbg !1274
  br label %return, !dbg !1274

if.end20:                                         ; preds = %if.end17
  %17 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1276
  %nblock_used = getelementptr inbounds %struct.DState, %struct.DState* %17, i32 0, i32 17, !dbg !1278
  %18 = load i32, i32* %nblock_used, align 4, !dbg !1278
  %19 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1279
  %save_nblock = getelementptr inbounds %struct.DState, %struct.DState* %19, i32 0, i32 51, !dbg !1280
  %20 = load i32, i32* %save_nblock, align 8, !dbg !1280
  %add = add nsw i32 %20, 1, !dbg !1281
  %cmp21 = icmp eq i32 %18, %add, !dbg !1282
  br i1 %cmp21, label %land.lhs.true, label %if.else45, !dbg !1283

land.lhs.true:                                    ; preds = %if.end20
  %21 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1284
  %state_out_len = getelementptr inbounds %struct.DState, %struct.DState* %21, i32 0, i32 3, !dbg !1286
  %22 = load i32, i32* %state_out_len, align 8, !dbg !1286
  %cmp22 = icmp eq i32 %22, 0, !dbg !1287
  br i1 %cmp22, label %if.then23, label %if.else45, !dbg !1288

if.then23:                                        ; preds = %land.lhs.true
  %23 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1289
  %calculatedBlockCRC = getelementptr inbounds %struct.DState, %struct.DState* %23, i32 0, i32 25, !dbg !1289
  %24 = load i32, i32* %calculatedBlockCRC, align 8, !dbg !1289
  %neg = xor i32 %24, -1, !dbg !1289
  %25 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1289
  %calculatedBlockCRC24 = getelementptr inbounds %struct.DState, %struct.DState* %25, i32 0, i32 25, !dbg !1289
  store i32 %neg, i32* %calculatedBlockCRC24, align 8, !dbg !1289
  %26 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1292
  %verbosity = getelementptr inbounds %struct.DState, %struct.DState* %26, i32 0, i32 12, !dbg !1294
  %27 = load i32, i32* %verbosity, align 4, !dbg !1294
  %cmp25 = icmp sge i32 %27, 3, !dbg !1295
  br i1 %cmp25, label %if.then26, label %if.end29, !dbg !1296

if.then26:                                        ; preds = %if.then23
  %28 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1297
  %29 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1297
  %storedBlockCRC = getelementptr inbounds %struct.DState, %struct.DState* %29, i32 0, i32 23, !dbg !1297
  %30 = load i32, i32* %storedBlockCRC, align 8, !dbg !1297
  %31 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1297
  %calculatedBlockCRC27 = getelementptr inbounds %struct.DState, %struct.DState* %31, i32 0, i32 25, !dbg !1297
  %32 = load i32, i32* %calculatedBlockCRC27, align 8, !dbg !1297
  %call28 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %28, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.2, i32 0, i32 0), i32 %30, i32 %32), !dbg !1297
  br label %if.end29, !dbg !1297

if.end29:                                         ; preds = %if.then26, %if.then23
  %33 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1298
  %verbosity30 = getelementptr inbounds %struct.DState, %struct.DState* %33, i32 0, i32 12, !dbg !1300
  %34 = load i32, i32* %verbosity30, align 4, !dbg !1300
  %cmp31 = icmp sge i32 %34, 2, !dbg !1301
  br i1 %cmp31, label %if.then32, label %if.end34, !dbg !1302

if.then32:                                        ; preds = %if.end29
  %35 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1303
  %call33 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %35, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.3, i32 0, i32 0)), !dbg !1303
  br label %if.end34, !dbg !1303

if.end34:                                         ; preds = %if.then32, %if.end29
  %36 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1305
  %calculatedBlockCRC35 = getelementptr inbounds %struct.DState, %struct.DState* %36, i32 0, i32 25, !dbg !1307
  %37 = load i32, i32* %calculatedBlockCRC35, align 8, !dbg !1307
  %38 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1308
  %storedBlockCRC36 = getelementptr inbounds %struct.DState, %struct.DState* %38, i32 0, i32 23, !dbg !1309
  %39 = load i32, i32* %storedBlockCRC36, align 8, !dbg !1309
  %cmp37 = icmp ne i32 %37, %39, !dbg !1310
  br i1 %cmp37, label %if.then38, label %if.end39, !dbg !1311

if.then38:                                        ; preds = %if.end34
  store i32 -4, i32* %retval, align 4, !dbg !1312
  br label %return, !dbg !1312

if.end39:                                         ; preds = %if.end34
  %40 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1313
  %calculatedCombinedCRC = getelementptr inbounds %struct.DState, %struct.DState* %40, i32 0, i32 26, !dbg !1314
  %41 = load i32, i32* %calculatedCombinedCRC, align 4, !dbg !1314
  %shl = shl i32 %41, 1, !dbg !1315
  %42 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1316
  %calculatedCombinedCRC40 = getelementptr inbounds %struct.DState, %struct.DState* %42, i32 0, i32 26, !dbg !1317
  %43 = load i32, i32* %calculatedCombinedCRC40, align 4, !dbg !1317
  %shr = lshr i32 %43, 31, !dbg !1318
  %or = or i32 %shl, %shr, !dbg !1319
  %44 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1320
  %calculatedCombinedCRC41 = getelementptr inbounds %struct.DState, %struct.DState* %44, i32 0, i32 26, !dbg !1321
  store i32 %or, i32* %calculatedCombinedCRC41, align 4, !dbg !1322
  %45 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1323
  %calculatedBlockCRC42 = getelementptr inbounds %struct.DState, %struct.DState* %45, i32 0, i32 25, !dbg !1324
  %46 = load i32, i32* %calculatedBlockCRC42, align 8, !dbg !1324
  %47 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1325
  %calculatedCombinedCRC43 = getelementptr inbounds %struct.DState, %struct.DState* %47, i32 0, i32 26, !dbg !1326
  %48 = load i32, i32* %calculatedCombinedCRC43, align 4, !dbg !1327
  %xor = xor i32 %48, %46, !dbg !1327
  store i32 %xor, i32* %calculatedCombinedCRC43, align 4, !dbg !1327
  %49 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1328
  %state44 = getelementptr inbounds %struct.DState, %struct.DState* %49, i32 0, i32 1, !dbg !1329
  store i32 14, i32* %state44, align 8, !dbg !1330
  br label %if.end46, !dbg !1331

if.else45:                                        ; preds = %land.lhs.true, %if.end20
  store i32 0, i32* %retval, align 4, !dbg !1332
  br label %return, !dbg !1332

if.end46:                                         ; preds = %if.end39
  br label %if.end47, !dbg !1334

if.end47:                                         ; preds = %if.end46, %if.end11
  %50 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1335
  %state48 = getelementptr inbounds %struct.DState, %struct.DState* %50, i32 0, i32 1, !dbg !1337
  %51 = load i32, i32* %state48, align 8, !dbg !1337
  %cmp49 = icmp sge i32 %51, 10, !dbg !1338
  br i1 %cmp49, label %if.then50, label %if.end70, !dbg !1339

if.then50:                                        ; preds = %if.end47
  call void @llvm.dbg.declare(metadata i32* %r, metadata !1340, metadata !392), !dbg !1342
  %52 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1343
  %call51 = call i32 @BZ2_decompress(%struct.DState* %52), !dbg !1344
  store i32 %call51, i32* %r, align 4, !dbg !1342
  %53 = load i32, i32* %r, align 4, !dbg !1345
  %cmp52 = icmp eq i32 %53, 4, !dbg !1347
  br i1 %cmp52, label %if.then53, label %if.end65, !dbg !1348

if.then53:                                        ; preds = %if.then50
  %54 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1349
  %verbosity54 = getelementptr inbounds %struct.DState, %struct.DState* %54, i32 0, i32 12, !dbg !1352
  %55 = load i32, i32* %verbosity54, align 4, !dbg !1352
  %cmp55 = icmp sge i32 %55, 3, !dbg !1353
  br i1 %cmp55, label %if.then56, label %if.end59, !dbg !1354

if.then56:                                        ; preds = %if.then53
  %56 = load %struct._IO_FILE*, %struct._IO_FILE** @stderr, align 8, !dbg !1355
  %57 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1355
  %storedCombinedCRC = getelementptr inbounds %struct.DState, %struct.DState* %57, i32 0, i32 24, !dbg !1355
  %58 = load i32, i32* %storedCombinedCRC, align 4, !dbg !1355
  %59 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1355
  %calculatedCombinedCRC57 = getelementptr inbounds %struct.DState, %struct.DState* %59, i32 0, i32 26, !dbg !1355
  %60 = load i32, i32* %calculatedCombinedCRC57, align 4, !dbg !1355
  %call58 = call i32 (%struct._IO_FILE*, i8*, ...) @fprintf(%struct._IO_FILE* %56, i8* getelementptr inbounds ([55 x i8], [55 x i8]* @.str.4, i32 0, i32 0), i32 %58, i32 %60), !dbg !1355
  br label %if.end59, !dbg !1355

if.end59:                                         ; preds = %if.then56, %if.then53
  %61 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1356
  %calculatedCombinedCRC60 = getelementptr inbounds %struct.DState, %struct.DState* %61, i32 0, i32 26, !dbg !1358
  %62 = load i32, i32* %calculatedCombinedCRC60, align 4, !dbg !1358
  %63 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1359
  %storedCombinedCRC61 = getelementptr inbounds %struct.DState, %struct.DState* %63, i32 0, i32 24, !dbg !1360
  %64 = load i32, i32* %storedCombinedCRC61, align 4, !dbg !1360
  %cmp62 = icmp ne i32 %62, %64, !dbg !1361
  br i1 %cmp62, label %if.then63, label %if.end64, !dbg !1362

if.then63:                                        ; preds = %if.end59
  store i32 -4, i32* %retval, align 4, !dbg !1363
  br label %return, !dbg !1363

if.end64:                                         ; preds = %if.end59
  %65 = load i32, i32* %r, align 4, !dbg !1364
  store i32 %65, i32* %retval, align 4, !dbg !1365
  br label %return, !dbg !1365

if.end65:                                         ; preds = %if.then50
  %66 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !1366
  %state66 = getelementptr inbounds %struct.DState, %struct.DState* %66, i32 0, i32 1, !dbg !1368
  %67 = load i32, i32* %state66, align 8, !dbg !1368
  %cmp67 = icmp ne i32 %67, 2, !dbg !1369
  br i1 %cmp67, label %if.then68, label %if.end69, !dbg !1370

if.then68:                                        ; preds = %if.end65
  %68 = load i32, i32* %r, align 4, !dbg !1371
  store i32 %68, i32* %retval, align 4, !dbg !1373
  br label %return, !dbg !1373

if.end69:                                         ; preds = %if.end65
  br label %if.end70, !dbg !1374

if.end70:                                         ; preds = %if.end69, %if.end47
  br label %while.body, !dbg !1375

return:                                           ; preds = %if.then68, %if.end64, %if.then63, %if.else45, %if.then38, %if.then19, %if.then10, %if.then6, %if.then2, %if.then
  %69 = load i32, i32* %retval, align 4, !dbg !1377
  ret i32 %69, !dbg !1377
}

; Function Attrs: nounwind uwtable
define internal zeroext i8 @unRLE_obuf_to_output_SMALL(%struct.DState* %s) #0 !dbg !294 {
entry:
  %retval = alloca i8, align 1
  %s.addr = alloca %struct.DState*, align 8
  %k1 = alloca i8, align 1
  store %struct.DState* %s, %struct.DState** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.DState** %s.addr, metadata !1378, metadata !392), !dbg !1379
  call void @llvm.dbg.declare(metadata i8* %k1, metadata !1380, metadata !392), !dbg !1381
  %0 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1382
  %blockRandomised = getelementptr inbounds %struct.DState, %struct.DState* %0, i32 0, i32 4, !dbg !1384
  %1 = load i8, i8* %blockRandomised, align 4, !dbg !1384
  %tobool = icmp ne i8 %1, 0, !dbg !1382
  br i1 %tobool, label %if.then, label %if.else, !dbg !1385

if.then:                                          ; preds = %entry
  br label %while.body, !dbg !1386

while.body:                                       ; preds = %if.then, %if.then92, %if.then98, %if.then167, %if.then173, %if.then242, %if.then248, %if.end361
  br label %while.body2, !dbg !1388

while.body2:                                      ; preds = %while.body, %if.end26
  %2 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1390
  %strm = getelementptr inbounds %struct.DState, %struct.DState* %2, i32 0, i32 0, !dbg !1393
  %3 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !1393
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %3, i32 0, i32 5, !dbg !1394
  %4 = load i32, i32* %avail_out, align 8, !dbg !1394
  %cmp = icmp eq i32 %4, 0, !dbg !1395
  br i1 %cmp, label %if.then3, label %if.end, !dbg !1396

if.then3:                                         ; preds = %while.body2
  store i8 0, i8* %retval, align 1, !dbg !1397
  br label %return, !dbg !1397

if.end:                                           ; preds = %while.body2
  %5 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1399
  %state_out_len = getelementptr inbounds %struct.DState, %struct.DState* %5, i32 0, i32 3, !dbg !1401
  %6 = load i32, i32* %state_out_len, align 8, !dbg !1401
  %cmp4 = icmp eq i32 %6, 0, !dbg !1402
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !1403

if.then5:                                         ; preds = %if.end
  br label %while.end, !dbg !1404

if.end6:                                          ; preds = %if.end
  %7 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1406
  %state_out_ch = getelementptr inbounds %struct.DState, %struct.DState* %7, i32 0, i32 2, !dbg !1407
  %8 = load i8, i8* %state_out_ch, align 4, !dbg !1407
  %9 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1408
  %strm7 = getelementptr inbounds %struct.DState, %struct.DState* %9, i32 0, i32 0, !dbg !1409
  %10 = load %struct.bz_stream*, %struct.bz_stream** %strm7, align 8, !dbg !1409
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %10, i32 0, i32 4, !dbg !1410
  %11 = load i8*, i8** %next_out, align 8, !dbg !1410
  store i8 %8, i8* %11, align 1, !dbg !1411
  %12 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1412
  %calculatedBlockCRC = getelementptr inbounds %struct.DState, %struct.DState* %12, i32 0, i32 25, !dbg !1412
  %13 = load i32, i32* %calculatedBlockCRC, align 8, !dbg !1412
  %shl = shl i32 %13, 8, !dbg !1412
  %14 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1412
  %calculatedBlockCRC8 = getelementptr inbounds %struct.DState, %struct.DState* %14, i32 0, i32 25, !dbg !1412
  %15 = load i32, i32* %calculatedBlockCRC8, align 8, !dbg !1412
  %shr = lshr i32 %15, 24, !dbg !1412
  %16 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1412
  %state_out_ch9 = getelementptr inbounds %struct.DState, %struct.DState* %16, i32 0, i32 2, !dbg !1412
  %17 = load i8, i8* %state_out_ch9, align 4, !dbg !1412
  %conv = zext i8 %17 to i32, !dbg !1412
  %xor = xor i32 %shr, %conv, !dbg !1412
  %idxprom = zext i32 %xor to i64, !dbg !1412
  %arrayidx = getelementptr inbounds [256 x i32], [256 x i32]* @BZ2_crc32Table, i64 0, i64 %idxprom, !dbg !1412
  %18 = load i32, i32* %arrayidx, align 4, !dbg !1412
  %xor10 = xor i32 %shl, %18, !dbg !1412
  %19 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1412
  %calculatedBlockCRC11 = getelementptr inbounds %struct.DState, %struct.DState* %19, i32 0, i32 25, !dbg !1412
  store i32 %xor10, i32* %calculatedBlockCRC11, align 8, !dbg !1412
  %20 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1414
  %state_out_len12 = getelementptr inbounds %struct.DState, %struct.DState* %20, i32 0, i32 3, !dbg !1415
  %21 = load i32, i32* %state_out_len12, align 8, !dbg !1416
  %dec = add nsw i32 %21, -1, !dbg !1416
  store i32 %dec, i32* %state_out_len12, align 8, !dbg !1416
  %22 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1417
  %strm13 = getelementptr inbounds %struct.DState, %struct.DState* %22, i32 0, i32 0, !dbg !1418
  %23 = load %struct.bz_stream*, %struct.bz_stream** %strm13, align 8, !dbg !1418
  %next_out14 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %23, i32 0, i32 4, !dbg !1419
  %24 = load i8*, i8** %next_out14, align 8, !dbg !1420
  %incdec.ptr = getelementptr inbounds i8, i8* %24, i32 1, !dbg !1420
  store i8* %incdec.ptr, i8** %next_out14, align 8, !dbg !1420
  %25 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1421
  %strm15 = getelementptr inbounds %struct.DState, %struct.DState* %25, i32 0, i32 0, !dbg !1422
  %26 = load %struct.bz_stream*, %struct.bz_stream** %strm15, align 8, !dbg !1422
  %avail_out16 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %26, i32 0, i32 5, !dbg !1423
  %27 = load i32, i32* %avail_out16, align 8, !dbg !1424
  %dec17 = add i32 %27, -1, !dbg !1424
  store i32 %dec17, i32* %avail_out16, align 8, !dbg !1424
  %28 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1425
  %strm18 = getelementptr inbounds %struct.DState, %struct.DState* %28, i32 0, i32 0, !dbg !1426
  %29 = load %struct.bz_stream*, %struct.bz_stream** %strm18, align 8, !dbg !1426
  %total_out_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %29, i32 0, i32 6, !dbg !1427
  %30 = load i32, i32* %total_out_lo32, align 4, !dbg !1428
  %inc = add i32 %30, 1, !dbg !1428
  store i32 %inc, i32* %total_out_lo32, align 4, !dbg !1428
  %31 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1429
  %strm19 = getelementptr inbounds %struct.DState, %struct.DState* %31, i32 0, i32 0, !dbg !1431
  %32 = load %struct.bz_stream*, %struct.bz_stream** %strm19, align 8, !dbg !1431
  %total_out_lo3220 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %32, i32 0, i32 6, !dbg !1432
  %33 = load i32, i32* %total_out_lo3220, align 4, !dbg !1432
  %cmp21 = icmp eq i32 %33, 0, !dbg !1433
  br i1 %cmp21, label %if.then23, label %if.end26, !dbg !1434

if.then23:                                        ; preds = %if.end6
  %34 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1435
  %strm24 = getelementptr inbounds %struct.DState, %struct.DState* %34, i32 0, i32 0, !dbg !1437
  %35 = load %struct.bz_stream*, %struct.bz_stream** %strm24, align 8, !dbg !1437
  %total_out_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %35, i32 0, i32 7, !dbg !1438
  %36 = load i32, i32* %total_out_hi32, align 8, !dbg !1439
  %inc25 = add i32 %36, 1, !dbg !1439
  store i32 %inc25, i32* %total_out_hi32, align 8, !dbg !1439
  br label %if.end26, !dbg !1435

if.end26:                                         ; preds = %if.then23, %if.end6
  br label %while.body2, !dbg !1440

while.end:                                        ; preds = %if.then5
  %37 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1442
  %nblock_used = getelementptr inbounds %struct.DState, %struct.DState* %37, i32 0, i32 17, !dbg !1444
  %38 = load i32, i32* %nblock_used, align 4, !dbg !1444
  %39 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1445
  %save_nblock = getelementptr inbounds %struct.DState, %struct.DState* %39, i32 0, i32 51, !dbg !1446
  %40 = load i32, i32* %save_nblock, align 8, !dbg !1446
  %add = add nsw i32 %40, 1, !dbg !1447
  %cmp27 = icmp eq i32 %38, %add, !dbg !1448
  br i1 %cmp27, label %if.then29, label %if.end30, !dbg !1449

if.then29:                                        ; preds = %while.end
  store i8 0, i8* %retval, align 1, !dbg !1450
  br label %return, !dbg !1450

if.end30:                                         ; preds = %while.end
  %41 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1452
  %nblock_used31 = getelementptr inbounds %struct.DState, %struct.DState* %41, i32 0, i32 17, !dbg !1454
  %42 = load i32, i32* %nblock_used31, align 4, !dbg !1454
  %43 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1455
  %save_nblock32 = getelementptr inbounds %struct.DState, %struct.DState* %43, i32 0, i32 51, !dbg !1456
  %44 = load i32, i32* %save_nblock32, align 8, !dbg !1456
  %add33 = add nsw i32 %44, 1, !dbg !1457
  %cmp34 = icmp sgt i32 %42, %add33, !dbg !1458
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !1459

if.then36:                                        ; preds = %if.end30
  store i8 1, i8* %retval, align 1, !dbg !1460
  br label %return, !dbg !1460

if.end37:                                         ; preds = %if.end30
  %45 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1461
  %state_out_len38 = getelementptr inbounds %struct.DState, %struct.DState* %45, i32 0, i32 3, !dbg !1462
  store i32 1, i32* %state_out_len38, align 8, !dbg !1463
  %46 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1464
  %k0 = getelementptr inbounds %struct.DState, %struct.DState* %46, i32 0, i32 15, !dbg !1465
  %47 = load i32, i32* %k0, align 8, !dbg !1465
  %conv39 = trunc i32 %47 to i8, !dbg !1464
  %48 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1466
  %state_out_ch40 = getelementptr inbounds %struct.DState, %struct.DState* %48, i32 0, i32 2, !dbg !1467
  store i8 %conv39, i8* %state_out_ch40, align 4, !dbg !1468
  %49 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1469
  %tPos = getelementptr inbounds %struct.DState, %struct.DState* %49, i32 0, i32 14, !dbg !1469
  %50 = load i32, i32* %tPos, align 4, !dbg !1469
  %51 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1469
  %blockSize100k = getelementptr inbounds %struct.DState, %struct.DState* %51, i32 0, i32 9, !dbg !1469
  %52 = load i32, i32* %blockSize100k, align 8, !dbg !1469
  %mul = mul i32 100000, %52, !dbg !1469
  %cmp41 = icmp uge i32 %50, %mul, !dbg !1469
  br i1 %cmp41, label %if.then43, label %if.end44, !dbg !1471

if.then43:                                        ; preds = %if.end37
  store i8 1, i8* %retval, align 1, !dbg !1472
  br label %return, !dbg !1472

if.end44:                                         ; preds = %if.end37
  %53 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1474
  %tPos45 = getelementptr inbounds %struct.DState, %struct.DState* %53, i32 0, i32 14, !dbg !1474
  %54 = load i32, i32* %tPos45, align 4, !dbg !1474
  %55 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1474
  %cftab = getelementptr inbounds %struct.DState, %struct.DState* %55, i32 0, i32 18, !dbg !1474
  %arraydecay = getelementptr inbounds [257 x i32], [257 x i32]* %cftab, i32 0, i32 0, !dbg !1474
  %call = call i32 @BZ2_indexIntoF(i32 %54, i32* %arraydecay), !dbg !1474
  %conv46 = trunc i32 %call to i8, !dbg !1474
  store i8 %conv46, i8* %k1, align 1, !dbg !1474
  %56 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1474
  %tPos47 = getelementptr inbounds %struct.DState, %struct.DState* %56, i32 0, i32 14, !dbg !1474
  %57 = load i32, i32* %tPos47, align 4, !dbg !1474
  %idxprom48 = zext i32 %57 to i64, !dbg !1474
  %58 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1474
  %ll16 = getelementptr inbounds %struct.DState, %struct.DState* %58, i32 0, i32 21, !dbg !1474
  %59 = load i16*, i16** %ll16, align 8, !dbg !1474
  %arrayidx49 = getelementptr inbounds i16, i16* %59, i64 %idxprom48, !dbg !1474
  %60 = load i16, i16* %arrayidx49, align 2, !dbg !1474
  %conv50 = zext i16 %60 to i32, !dbg !1474
  %61 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1474
  %tPos51 = getelementptr inbounds %struct.DState, %struct.DState* %61, i32 0, i32 14, !dbg !1474
  %62 = load i32, i32* %tPos51, align 4, !dbg !1474
  %shr52 = lshr i32 %62, 1, !dbg !1474
  %idxprom53 = zext i32 %shr52 to i64, !dbg !1474
  %63 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1474
  %ll4 = getelementptr inbounds %struct.DState, %struct.DState* %63, i32 0, i32 22, !dbg !1474
  %64 = load i8*, i8** %ll4, align 8, !dbg !1474
  %arrayidx54 = getelementptr inbounds i8, i8* %64, i64 %idxprom53, !dbg !1474
  %65 = load i8, i8* %arrayidx54, align 1, !dbg !1474
  %conv55 = zext i8 %65 to i32, !dbg !1474
  %66 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1474
  %tPos56 = getelementptr inbounds %struct.DState, %struct.DState* %66, i32 0, i32 14, !dbg !1474
  %67 = load i32, i32* %tPos56, align 4, !dbg !1474
  %shl57 = shl i32 %67, 2, !dbg !1474
  %and = and i32 %shl57, 4, !dbg !1474
  %shr58 = lshr i32 %conv55, %and, !dbg !1474
  %and59 = and i32 %shr58, 15, !dbg !1474
  %shl60 = shl i32 %and59, 16, !dbg !1474
  %or = or i32 %conv50, %shl60, !dbg !1474
  %68 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1474
  %tPos61 = getelementptr inbounds %struct.DState, %struct.DState* %68, i32 0, i32 14, !dbg !1474
  store i32 %or, i32* %tPos61, align 4, !dbg !1474
  %69 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1476
  %rNToGo = getelementptr inbounds %struct.DState, %struct.DState* %69, i32 0, i32 5, !dbg !1476
  %70 = load i32, i32* %rNToGo, align 8, !dbg !1476
  %cmp62 = icmp eq i32 %70, 0, !dbg !1476
  br i1 %cmp62, label %if.then64, label %if.end76, !dbg !1476

if.then64:                                        ; preds = %if.end44
  %71 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1477
  %rTPos = getelementptr inbounds %struct.DState, %struct.DState* %71, i32 0, i32 6, !dbg !1477
  %72 = load i32, i32* %rTPos, align 4, !dbg !1477
  %idxprom65 = sext i32 %72 to i64, !dbg !1477
  %arrayidx66 = getelementptr inbounds [512 x i32], [512 x i32]* @BZ2_rNums, i64 0, i64 %idxprom65, !dbg !1477
  %73 = load i32, i32* %arrayidx66, align 4, !dbg !1477
  %74 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1477
  %rNToGo67 = getelementptr inbounds %struct.DState, %struct.DState* %74, i32 0, i32 5, !dbg !1477
  store i32 %73, i32* %rNToGo67, align 8, !dbg !1477
  %75 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1477
  %rTPos68 = getelementptr inbounds %struct.DState, %struct.DState* %75, i32 0, i32 6, !dbg !1477
  %76 = load i32, i32* %rTPos68, align 4, !dbg !1477
  %inc69 = add nsw i32 %76, 1, !dbg !1477
  store i32 %inc69, i32* %rTPos68, align 4, !dbg !1477
  %77 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1477
  %rTPos70 = getelementptr inbounds %struct.DState, %struct.DState* %77, i32 0, i32 6, !dbg !1477
  %78 = load i32, i32* %rTPos70, align 4, !dbg !1477
  %cmp71 = icmp eq i32 %78, 512, !dbg !1477
  br i1 %cmp71, label %if.then73, label %if.end75, !dbg !1477

if.then73:                                        ; preds = %if.then64
  %79 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1481
  %rTPos74 = getelementptr inbounds %struct.DState, %struct.DState* %79, i32 0, i32 6, !dbg !1481
  store i32 0, i32* %rTPos74, align 4, !dbg !1481
  br label %if.end75, !dbg !1481

if.end75:                                         ; preds = %if.then73, %if.then64
  br label %if.end76, !dbg !1484

if.end76:                                         ; preds = %if.end75, %if.end44
  %80 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1486
  %rNToGo77 = getelementptr inbounds %struct.DState, %struct.DState* %80, i32 0, i32 5, !dbg !1486
  %81 = load i32, i32* %rNToGo77, align 8, !dbg !1486
  %dec78 = add nsw i32 %81, -1, !dbg !1486
  store i32 %dec78, i32* %rNToGo77, align 8, !dbg !1486
  %82 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1488
  %rNToGo79 = getelementptr inbounds %struct.DState, %struct.DState* %82, i32 0, i32 5, !dbg !1488
  %83 = load i32, i32* %rNToGo79, align 8, !dbg !1488
  %cmp80 = icmp eq i32 %83, 1, !dbg !1488
  %cond = select i1 %cmp80, i32 1, i32 0, !dbg !1488
  %84 = load i8, i8* %k1, align 1, !dbg !1489
  %conv82 = zext i8 %84 to i32, !dbg !1489
  %xor83 = xor i32 %conv82, %cond, !dbg !1489
  %conv84 = trunc i32 %xor83 to i8, !dbg !1489
  store i8 %conv84, i8* %k1, align 1, !dbg !1489
  %85 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1490
  %nblock_used85 = getelementptr inbounds %struct.DState, %struct.DState* %85, i32 0, i32 17, !dbg !1491
  %86 = load i32, i32* %nblock_used85, align 4, !dbg !1492
  %inc86 = add nsw i32 %86, 1, !dbg !1492
  store i32 %inc86, i32* %nblock_used85, align 4, !dbg !1492
  %87 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1493
  %nblock_used87 = getelementptr inbounds %struct.DState, %struct.DState* %87, i32 0, i32 17, !dbg !1495
  %88 = load i32, i32* %nblock_used87, align 4, !dbg !1495
  %89 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1496
  %save_nblock88 = getelementptr inbounds %struct.DState, %struct.DState* %89, i32 0, i32 51, !dbg !1497
  %90 = load i32, i32* %save_nblock88, align 8, !dbg !1497
  %add89 = add nsw i32 %90, 1, !dbg !1498
  %cmp90 = icmp eq i32 %88, %add89, !dbg !1499
  br i1 %cmp90, label %if.then92, label %if.end93, !dbg !1500

if.then92:                                        ; preds = %if.end76
  br label %while.body, !dbg !1501

if.end93:                                         ; preds = %if.end76
  %91 = load i8, i8* %k1, align 1, !dbg !1503
  %conv94 = zext i8 %91 to i32, !dbg !1503
  %92 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1505
  %k095 = getelementptr inbounds %struct.DState, %struct.DState* %92, i32 0, i32 15, !dbg !1506
  %93 = load i32, i32* %k095, align 8, !dbg !1506
  %cmp96 = icmp ne i32 %conv94, %93, !dbg !1507
  br i1 %cmp96, label %if.then98, label %if.end101, !dbg !1508

if.then98:                                        ; preds = %if.end93
  %94 = load i8, i8* %k1, align 1, !dbg !1509
  %conv99 = zext i8 %94 to i32, !dbg !1509
  %95 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1512
  %k0100 = getelementptr inbounds %struct.DState, %struct.DState* %95, i32 0, i32 15, !dbg !1513
  store i32 %conv99, i32* %k0100, align 8, !dbg !1514
  br label %while.body, !dbg !1515

if.end101:                                        ; preds = %if.end93
  %96 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1516
  %state_out_len102 = getelementptr inbounds %struct.DState, %struct.DState* %96, i32 0, i32 3, !dbg !1517
  store i32 2, i32* %state_out_len102, align 8, !dbg !1518
  %97 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1519
  %tPos103 = getelementptr inbounds %struct.DState, %struct.DState* %97, i32 0, i32 14, !dbg !1519
  %98 = load i32, i32* %tPos103, align 4, !dbg !1519
  %99 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1519
  %blockSize100k104 = getelementptr inbounds %struct.DState, %struct.DState* %99, i32 0, i32 9, !dbg !1519
  %100 = load i32, i32* %blockSize100k104, align 8, !dbg !1519
  %mul105 = mul i32 100000, %100, !dbg !1519
  %cmp106 = icmp uge i32 %98, %mul105, !dbg !1519
  br i1 %cmp106, label %if.then108, label %if.end109, !dbg !1521

if.then108:                                       ; preds = %if.end101
  store i8 1, i8* %retval, align 1, !dbg !1522
  br label %return, !dbg !1522

if.end109:                                        ; preds = %if.end101
  %101 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1524
  %tPos110 = getelementptr inbounds %struct.DState, %struct.DState* %101, i32 0, i32 14, !dbg !1524
  %102 = load i32, i32* %tPos110, align 4, !dbg !1524
  %103 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1524
  %cftab111 = getelementptr inbounds %struct.DState, %struct.DState* %103, i32 0, i32 18, !dbg !1524
  %arraydecay112 = getelementptr inbounds [257 x i32], [257 x i32]* %cftab111, i32 0, i32 0, !dbg !1524
  %call113 = call i32 @BZ2_indexIntoF(i32 %102, i32* %arraydecay112), !dbg !1524
  %conv114 = trunc i32 %call113 to i8, !dbg !1524
  store i8 %conv114, i8* %k1, align 1, !dbg !1524
  %104 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1524
  %tPos115 = getelementptr inbounds %struct.DState, %struct.DState* %104, i32 0, i32 14, !dbg !1524
  %105 = load i32, i32* %tPos115, align 4, !dbg !1524
  %idxprom116 = zext i32 %105 to i64, !dbg !1524
  %106 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1524
  %ll16117 = getelementptr inbounds %struct.DState, %struct.DState* %106, i32 0, i32 21, !dbg !1524
  %107 = load i16*, i16** %ll16117, align 8, !dbg !1524
  %arrayidx118 = getelementptr inbounds i16, i16* %107, i64 %idxprom116, !dbg !1524
  %108 = load i16, i16* %arrayidx118, align 2, !dbg !1524
  %conv119 = zext i16 %108 to i32, !dbg !1524
  %109 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1524
  %tPos120 = getelementptr inbounds %struct.DState, %struct.DState* %109, i32 0, i32 14, !dbg !1524
  %110 = load i32, i32* %tPos120, align 4, !dbg !1524
  %shr121 = lshr i32 %110, 1, !dbg !1524
  %idxprom122 = zext i32 %shr121 to i64, !dbg !1524
  %111 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1524
  %ll4123 = getelementptr inbounds %struct.DState, %struct.DState* %111, i32 0, i32 22, !dbg !1524
  %112 = load i8*, i8** %ll4123, align 8, !dbg !1524
  %arrayidx124 = getelementptr inbounds i8, i8* %112, i64 %idxprom122, !dbg !1524
  %113 = load i8, i8* %arrayidx124, align 1, !dbg !1524
  %conv125 = zext i8 %113 to i32, !dbg !1524
  %114 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1524
  %tPos126 = getelementptr inbounds %struct.DState, %struct.DState* %114, i32 0, i32 14, !dbg !1524
  %115 = load i32, i32* %tPos126, align 4, !dbg !1524
  %shl127 = shl i32 %115, 2, !dbg !1524
  %and128 = and i32 %shl127, 4, !dbg !1524
  %shr129 = lshr i32 %conv125, %and128, !dbg !1524
  %and130 = and i32 %shr129, 15, !dbg !1524
  %shl131 = shl i32 %and130, 16, !dbg !1524
  %or132 = or i32 %conv119, %shl131, !dbg !1524
  %116 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1524
  %tPos133 = getelementptr inbounds %struct.DState, %struct.DState* %116, i32 0, i32 14, !dbg !1524
  store i32 %or132, i32* %tPos133, align 4, !dbg !1524
  %117 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1525
  %rNToGo134 = getelementptr inbounds %struct.DState, %struct.DState* %117, i32 0, i32 5, !dbg !1525
  %118 = load i32, i32* %rNToGo134, align 8, !dbg !1525
  %cmp135 = icmp eq i32 %118, 0, !dbg !1525
  br i1 %cmp135, label %if.then137, label %if.end150, !dbg !1525

if.then137:                                       ; preds = %if.end109
  %119 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1526
  %rTPos138 = getelementptr inbounds %struct.DState, %struct.DState* %119, i32 0, i32 6, !dbg !1526
  %120 = load i32, i32* %rTPos138, align 4, !dbg !1526
  %idxprom139 = sext i32 %120 to i64, !dbg !1526
  %arrayidx140 = getelementptr inbounds [512 x i32], [512 x i32]* @BZ2_rNums, i64 0, i64 %idxprom139, !dbg !1526
  %121 = load i32, i32* %arrayidx140, align 4, !dbg !1526
  %122 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1526
  %rNToGo141 = getelementptr inbounds %struct.DState, %struct.DState* %122, i32 0, i32 5, !dbg !1526
  store i32 %121, i32* %rNToGo141, align 8, !dbg !1526
  %123 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1526
  %rTPos142 = getelementptr inbounds %struct.DState, %struct.DState* %123, i32 0, i32 6, !dbg !1526
  %124 = load i32, i32* %rTPos142, align 4, !dbg !1526
  %inc143 = add nsw i32 %124, 1, !dbg !1526
  store i32 %inc143, i32* %rTPos142, align 4, !dbg !1526
  %125 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1526
  %rTPos144 = getelementptr inbounds %struct.DState, %struct.DState* %125, i32 0, i32 6, !dbg !1526
  %126 = load i32, i32* %rTPos144, align 4, !dbg !1526
  %cmp145 = icmp eq i32 %126, 512, !dbg !1526
  br i1 %cmp145, label %if.then147, label %if.end149, !dbg !1526

if.then147:                                       ; preds = %if.then137
  %127 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1530
  %rTPos148 = getelementptr inbounds %struct.DState, %struct.DState* %127, i32 0, i32 6, !dbg !1530
  store i32 0, i32* %rTPos148, align 4, !dbg !1530
  br label %if.end149, !dbg !1530

if.end149:                                        ; preds = %if.then147, %if.then137
  br label %if.end150, !dbg !1533

if.end150:                                        ; preds = %if.end149, %if.end109
  %128 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1535
  %rNToGo151 = getelementptr inbounds %struct.DState, %struct.DState* %128, i32 0, i32 5, !dbg !1535
  %129 = load i32, i32* %rNToGo151, align 8, !dbg !1535
  %dec152 = add nsw i32 %129, -1, !dbg !1535
  store i32 %dec152, i32* %rNToGo151, align 8, !dbg !1535
  %130 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1536
  %rNToGo153 = getelementptr inbounds %struct.DState, %struct.DState* %130, i32 0, i32 5, !dbg !1536
  %131 = load i32, i32* %rNToGo153, align 8, !dbg !1536
  %cmp154 = icmp eq i32 %131, 1, !dbg !1536
  %cond156 = select i1 %cmp154, i32 1, i32 0, !dbg !1536
  %132 = load i8, i8* %k1, align 1, !dbg !1537
  %conv157 = zext i8 %132 to i32, !dbg !1537
  %xor158 = xor i32 %conv157, %cond156, !dbg !1537
  %conv159 = trunc i32 %xor158 to i8, !dbg !1537
  store i8 %conv159, i8* %k1, align 1, !dbg !1537
  %133 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1538
  %nblock_used160 = getelementptr inbounds %struct.DState, %struct.DState* %133, i32 0, i32 17, !dbg !1539
  %134 = load i32, i32* %nblock_used160, align 4, !dbg !1540
  %inc161 = add nsw i32 %134, 1, !dbg !1540
  store i32 %inc161, i32* %nblock_used160, align 4, !dbg !1540
  %135 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1541
  %nblock_used162 = getelementptr inbounds %struct.DState, %struct.DState* %135, i32 0, i32 17, !dbg !1543
  %136 = load i32, i32* %nblock_used162, align 4, !dbg !1543
  %137 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1544
  %save_nblock163 = getelementptr inbounds %struct.DState, %struct.DState* %137, i32 0, i32 51, !dbg !1545
  %138 = load i32, i32* %save_nblock163, align 8, !dbg !1545
  %add164 = add nsw i32 %138, 1, !dbg !1546
  %cmp165 = icmp eq i32 %136, %add164, !dbg !1547
  br i1 %cmp165, label %if.then167, label %if.end168, !dbg !1548

if.then167:                                       ; preds = %if.end150
  br label %while.body, !dbg !1549

if.end168:                                        ; preds = %if.end150
  %139 = load i8, i8* %k1, align 1, !dbg !1551
  %conv169 = zext i8 %139 to i32, !dbg !1551
  %140 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1553
  %k0170 = getelementptr inbounds %struct.DState, %struct.DState* %140, i32 0, i32 15, !dbg !1554
  %141 = load i32, i32* %k0170, align 8, !dbg !1554
  %cmp171 = icmp ne i32 %conv169, %141, !dbg !1555
  br i1 %cmp171, label %if.then173, label %if.end176, !dbg !1556

if.then173:                                       ; preds = %if.end168
  %142 = load i8, i8* %k1, align 1, !dbg !1557
  %conv174 = zext i8 %142 to i32, !dbg !1557
  %143 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1560
  %k0175 = getelementptr inbounds %struct.DState, %struct.DState* %143, i32 0, i32 15, !dbg !1561
  store i32 %conv174, i32* %k0175, align 8, !dbg !1562
  br label %while.body, !dbg !1563

if.end176:                                        ; preds = %if.end168
  %144 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1564
  %state_out_len177 = getelementptr inbounds %struct.DState, %struct.DState* %144, i32 0, i32 3, !dbg !1565
  store i32 3, i32* %state_out_len177, align 8, !dbg !1566
  %145 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1567
  %tPos178 = getelementptr inbounds %struct.DState, %struct.DState* %145, i32 0, i32 14, !dbg !1567
  %146 = load i32, i32* %tPos178, align 4, !dbg !1567
  %147 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1567
  %blockSize100k179 = getelementptr inbounds %struct.DState, %struct.DState* %147, i32 0, i32 9, !dbg !1567
  %148 = load i32, i32* %blockSize100k179, align 8, !dbg !1567
  %mul180 = mul i32 100000, %148, !dbg !1567
  %cmp181 = icmp uge i32 %146, %mul180, !dbg !1567
  br i1 %cmp181, label %if.then183, label %if.end184, !dbg !1569

if.then183:                                       ; preds = %if.end176
  store i8 1, i8* %retval, align 1, !dbg !1570
  br label %return, !dbg !1570

if.end184:                                        ; preds = %if.end176
  %149 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1572
  %tPos185 = getelementptr inbounds %struct.DState, %struct.DState* %149, i32 0, i32 14, !dbg !1572
  %150 = load i32, i32* %tPos185, align 4, !dbg !1572
  %151 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1572
  %cftab186 = getelementptr inbounds %struct.DState, %struct.DState* %151, i32 0, i32 18, !dbg !1572
  %arraydecay187 = getelementptr inbounds [257 x i32], [257 x i32]* %cftab186, i32 0, i32 0, !dbg !1572
  %call188 = call i32 @BZ2_indexIntoF(i32 %150, i32* %arraydecay187), !dbg !1572
  %conv189 = trunc i32 %call188 to i8, !dbg !1572
  store i8 %conv189, i8* %k1, align 1, !dbg !1572
  %152 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1572
  %tPos190 = getelementptr inbounds %struct.DState, %struct.DState* %152, i32 0, i32 14, !dbg !1572
  %153 = load i32, i32* %tPos190, align 4, !dbg !1572
  %idxprom191 = zext i32 %153 to i64, !dbg !1572
  %154 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1572
  %ll16192 = getelementptr inbounds %struct.DState, %struct.DState* %154, i32 0, i32 21, !dbg !1572
  %155 = load i16*, i16** %ll16192, align 8, !dbg !1572
  %arrayidx193 = getelementptr inbounds i16, i16* %155, i64 %idxprom191, !dbg !1572
  %156 = load i16, i16* %arrayidx193, align 2, !dbg !1572
  %conv194 = zext i16 %156 to i32, !dbg !1572
  %157 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1572
  %tPos195 = getelementptr inbounds %struct.DState, %struct.DState* %157, i32 0, i32 14, !dbg !1572
  %158 = load i32, i32* %tPos195, align 4, !dbg !1572
  %shr196 = lshr i32 %158, 1, !dbg !1572
  %idxprom197 = zext i32 %shr196 to i64, !dbg !1572
  %159 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1572
  %ll4198 = getelementptr inbounds %struct.DState, %struct.DState* %159, i32 0, i32 22, !dbg !1572
  %160 = load i8*, i8** %ll4198, align 8, !dbg !1572
  %arrayidx199 = getelementptr inbounds i8, i8* %160, i64 %idxprom197, !dbg !1572
  %161 = load i8, i8* %arrayidx199, align 1, !dbg !1572
  %conv200 = zext i8 %161 to i32, !dbg !1572
  %162 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1572
  %tPos201 = getelementptr inbounds %struct.DState, %struct.DState* %162, i32 0, i32 14, !dbg !1572
  %163 = load i32, i32* %tPos201, align 4, !dbg !1572
  %shl202 = shl i32 %163, 2, !dbg !1572
  %and203 = and i32 %shl202, 4, !dbg !1572
  %shr204 = lshr i32 %conv200, %and203, !dbg !1572
  %and205 = and i32 %shr204, 15, !dbg !1572
  %shl206 = shl i32 %and205, 16, !dbg !1572
  %or207 = or i32 %conv194, %shl206, !dbg !1572
  %164 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1572
  %tPos208 = getelementptr inbounds %struct.DState, %struct.DState* %164, i32 0, i32 14, !dbg !1572
  store i32 %or207, i32* %tPos208, align 4, !dbg !1572
  %165 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1573
  %rNToGo209 = getelementptr inbounds %struct.DState, %struct.DState* %165, i32 0, i32 5, !dbg !1573
  %166 = load i32, i32* %rNToGo209, align 8, !dbg !1573
  %cmp210 = icmp eq i32 %166, 0, !dbg !1573
  br i1 %cmp210, label %if.then212, label %if.end225, !dbg !1573

if.then212:                                       ; preds = %if.end184
  %167 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1574
  %rTPos213 = getelementptr inbounds %struct.DState, %struct.DState* %167, i32 0, i32 6, !dbg !1574
  %168 = load i32, i32* %rTPos213, align 4, !dbg !1574
  %idxprom214 = sext i32 %168 to i64, !dbg !1574
  %arrayidx215 = getelementptr inbounds [512 x i32], [512 x i32]* @BZ2_rNums, i64 0, i64 %idxprom214, !dbg !1574
  %169 = load i32, i32* %arrayidx215, align 4, !dbg !1574
  %170 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1574
  %rNToGo216 = getelementptr inbounds %struct.DState, %struct.DState* %170, i32 0, i32 5, !dbg !1574
  store i32 %169, i32* %rNToGo216, align 8, !dbg !1574
  %171 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1574
  %rTPos217 = getelementptr inbounds %struct.DState, %struct.DState* %171, i32 0, i32 6, !dbg !1574
  %172 = load i32, i32* %rTPos217, align 4, !dbg !1574
  %inc218 = add nsw i32 %172, 1, !dbg !1574
  store i32 %inc218, i32* %rTPos217, align 4, !dbg !1574
  %173 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1574
  %rTPos219 = getelementptr inbounds %struct.DState, %struct.DState* %173, i32 0, i32 6, !dbg !1574
  %174 = load i32, i32* %rTPos219, align 4, !dbg !1574
  %cmp220 = icmp eq i32 %174, 512, !dbg !1574
  br i1 %cmp220, label %if.then222, label %if.end224, !dbg !1574

if.then222:                                       ; preds = %if.then212
  %175 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1578
  %rTPos223 = getelementptr inbounds %struct.DState, %struct.DState* %175, i32 0, i32 6, !dbg !1578
  store i32 0, i32* %rTPos223, align 4, !dbg !1578
  br label %if.end224, !dbg !1578

if.end224:                                        ; preds = %if.then222, %if.then212
  br label %if.end225, !dbg !1581

if.end225:                                        ; preds = %if.end224, %if.end184
  %176 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1583
  %rNToGo226 = getelementptr inbounds %struct.DState, %struct.DState* %176, i32 0, i32 5, !dbg !1583
  %177 = load i32, i32* %rNToGo226, align 8, !dbg !1583
  %dec227 = add nsw i32 %177, -1, !dbg !1583
  store i32 %dec227, i32* %rNToGo226, align 8, !dbg !1583
  %178 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1584
  %rNToGo228 = getelementptr inbounds %struct.DState, %struct.DState* %178, i32 0, i32 5, !dbg !1584
  %179 = load i32, i32* %rNToGo228, align 8, !dbg !1584
  %cmp229 = icmp eq i32 %179, 1, !dbg !1584
  %cond231 = select i1 %cmp229, i32 1, i32 0, !dbg !1584
  %180 = load i8, i8* %k1, align 1, !dbg !1585
  %conv232 = zext i8 %180 to i32, !dbg !1585
  %xor233 = xor i32 %conv232, %cond231, !dbg !1585
  %conv234 = trunc i32 %xor233 to i8, !dbg !1585
  store i8 %conv234, i8* %k1, align 1, !dbg !1585
  %181 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1586
  %nblock_used235 = getelementptr inbounds %struct.DState, %struct.DState* %181, i32 0, i32 17, !dbg !1587
  %182 = load i32, i32* %nblock_used235, align 4, !dbg !1588
  %inc236 = add nsw i32 %182, 1, !dbg !1588
  store i32 %inc236, i32* %nblock_used235, align 4, !dbg !1588
  %183 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1589
  %nblock_used237 = getelementptr inbounds %struct.DState, %struct.DState* %183, i32 0, i32 17, !dbg !1591
  %184 = load i32, i32* %nblock_used237, align 4, !dbg !1591
  %185 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1592
  %save_nblock238 = getelementptr inbounds %struct.DState, %struct.DState* %185, i32 0, i32 51, !dbg !1593
  %186 = load i32, i32* %save_nblock238, align 8, !dbg !1593
  %add239 = add nsw i32 %186, 1, !dbg !1594
  %cmp240 = icmp eq i32 %184, %add239, !dbg !1595
  br i1 %cmp240, label %if.then242, label %if.end243, !dbg !1596

if.then242:                                       ; preds = %if.end225
  br label %while.body, !dbg !1597

if.end243:                                        ; preds = %if.end225
  %187 = load i8, i8* %k1, align 1, !dbg !1599
  %conv244 = zext i8 %187 to i32, !dbg !1599
  %188 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1601
  %k0245 = getelementptr inbounds %struct.DState, %struct.DState* %188, i32 0, i32 15, !dbg !1602
  %189 = load i32, i32* %k0245, align 8, !dbg !1602
  %cmp246 = icmp ne i32 %conv244, %189, !dbg !1603
  br i1 %cmp246, label %if.then248, label %if.end251, !dbg !1604

if.then248:                                       ; preds = %if.end243
  %190 = load i8, i8* %k1, align 1, !dbg !1605
  %conv249 = zext i8 %190 to i32, !dbg !1605
  %191 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1608
  %k0250 = getelementptr inbounds %struct.DState, %struct.DState* %191, i32 0, i32 15, !dbg !1609
  store i32 %conv249, i32* %k0250, align 8, !dbg !1610
  br label %while.body, !dbg !1611

if.end251:                                        ; preds = %if.end243
  %192 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1612
  %tPos252 = getelementptr inbounds %struct.DState, %struct.DState* %192, i32 0, i32 14, !dbg !1612
  %193 = load i32, i32* %tPos252, align 4, !dbg !1612
  %194 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1612
  %blockSize100k253 = getelementptr inbounds %struct.DState, %struct.DState* %194, i32 0, i32 9, !dbg !1612
  %195 = load i32, i32* %blockSize100k253, align 8, !dbg !1612
  %mul254 = mul i32 100000, %195, !dbg !1612
  %cmp255 = icmp uge i32 %193, %mul254, !dbg !1612
  br i1 %cmp255, label %if.then257, label %if.end258, !dbg !1614

if.then257:                                       ; preds = %if.end251
  store i8 1, i8* %retval, align 1, !dbg !1615
  br label %return, !dbg !1615

if.end258:                                        ; preds = %if.end251
  %196 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1617
  %tPos259 = getelementptr inbounds %struct.DState, %struct.DState* %196, i32 0, i32 14, !dbg !1617
  %197 = load i32, i32* %tPos259, align 4, !dbg !1617
  %198 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1617
  %cftab260 = getelementptr inbounds %struct.DState, %struct.DState* %198, i32 0, i32 18, !dbg !1617
  %arraydecay261 = getelementptr inbounds [257 x i32], [257 x i32]* %cftab260, i32 0, i32 0, !dbg !1617
  %call262 = call i32 @BZ2_indexIntoF(i32 %197, i32* %arraydecay261), !dbg !1617
  %conv263 = trunc i32 %call262 to i8, !dbg !1617
  store i8 %conv263, i8* %k1, align 1, !dbg !1617
  %199 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1617
  %tPos264 = getelementptr inbounds %struct.DState, %struct.DState* %199, i32 0, i32 14, !dbg !1617
  %200 = load i32, i32* %tPos264, align 4, !dbg !1617
  %idxprom265 = zext i32 %200 to i64, !dbg !1617
  %201 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1617
  %ll16266 = getelementptr inbounds %struct.DState, %struct.DState* %201, i32 0, i32 21, !dbg !1617
  %202 = load i16*, i16** %ll16266, align 8, !dbg !1617
  %arrayidx267 = getelementptr inbounds i16, i16* %202, i64 %idxprom265, !dbg !1617
  %203 = load i16, i16* %arrayidx267, align 2, !dbg !1617
  %conv268 = zext i16 %203 to i32, !dbg !1617
  %204 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1617
  %tPos269 = getelementptr inbounds %struct.DState, %struct.DState* %204, i32 0, i32 14, !dbg !1617
  %205 = load i32, i32* %tPos269, align 4, !dbg !1617
  %shr270 = lshr i32 %205, 1, !dbg !1617
  %idxprom271 = zext i32 %shr270 to i64, !dbg !1617
  %206 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1617
  %ll4272 = getelementptr inbounds %struct.DState, %struct.DState* %206, i32 0, i32 22, !dbg !1617
  %207 = load i8*, i8** %ll4272, align 8, !dbg !1617
  %arrayidx273 = getelementptr inbounds i8, i8* %207, i64 %idxprom271, !dbg !1617
  %208 = load i8, i8* %arrayidx273, align 1, !dbg !1617
  %conv274 = zext i8 %208 to i32, !dbg !1617
  %209 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1617
  %tPos275 = getelementptr inbounds %struct.DState, %struct.DState* %209, i32 0, i32 14, !dbg !1617
  %210 = load i32, i32* %tPos275, align 4, !dbg !1617
  %shl276 = shl i32 %210, 2, !dbg !1617
  %and277 = and i32 %shl276, 4, !dbg !1617
  %shr278 = lshr i32 %conv274, %and277, !dbg !1617
  %and279 = and i32 %shr278, 15, !dbg !1617
  %shl280 = shl i32 %and279, 16, !dbg !1617
  %or281 = or i32 %conv268, %shl280, !dbg !1617
  %211 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1617
  %tPos282 = getelementptr inbounds %struct.DState, %struct.DState* %211, i32 0, i32 14, !dbg !1617
  store i32 %or281, i32* %tPos282, align 4, !dbg !1617
  %212 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1618
  %rNToGo283 = getelementptr inbounds %struct.DState, %struct.DState* %212, i32 0, i32 5, !dbg !1618
  %213 = load i32, i32* %rNToGo283, align 8, !dbg !1618
  %cmp284 = icmp eq i32 %213, 0, !dbg !1618
  br i1 %cmp284, label %if.then286, label %if.end299, !dbg !1618

if.then286:                                       ; preds = %if.end258
  %214 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1619
  %rTPos287 = getelementptr inbounds %struct.DState, %struct.DState* %214, i32 0, i32 6, !dbg !1619
  %215 = load i32, i32* %rTPos287, align 4, !dbg !1619
  %idxprom288 = sext i32 %215 to i64, !dbg !1619
  %arrayidx289 = getelementptr inbounds [512 x i32], [512 x i32]* @BZ2_rNums, i64 0, i64 %idxprom288, !dbg !1619
  %216 = load i32, i32* %arrayidx289, align 4, !dbg !1619
  %217 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1619
  %rNToGo290 = getelementptr inbounds %struct.DState, %struct.DState* %217, i32 0, i32 5, !dbg !1619
  store i32 %216, i32* %rNToGo290, align 8, !dbg !1619
  %218 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1619
  %rTPos291 = getelementptr inbounds %struct.DState, %struct.DState* %218, i32 0, i32 6, !dbg !1619
  %219 = load i32, i32* %rTPos291, align 4, !dbg !1619
  %inc292 = add nsw i32 %219, 1, !dbg !1619
  store i32 %inc292, i32* %rTPos291, align 4, !dbg !1619
  %220 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1619
  %rTPos293 = getelementptr inbounds %struct.DState, %struct.DState* %220, i32 0, i32 6, !dbg !1619
  %221 = load i32, i32* %rTPos293, align 4, !dbg !1619
  %cmp294 = icmp eq i32 %221, 512, !dbg !1619
  br i1 %cmp294, label %if.then296, label %if.end298, !dbg !1619

if.then296:                                       ; preds = %if.then286
  %222 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1623
  %rTPos297 = getelementptr inbounds %struct.DState, %struct.DState* %222, i32 0, i32 6, !dbg !1623
  store i32 0, i32* %rTPos297, align 4, !dbg !1623
  br label %if.end298, !dbg !1623

if.end298:                                        ; preds = %if.then296, %if.then286
  br label %if.end299, !dbg !1626

if.end299:                                        ; preds = %if.end298, %if.end258
  %223 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1628
  %rNToGo300 = getelementptr inbounds %struct.DState, %struct.DState* %223, i32 0, i32 5, !dbg !1628
  %224 = load i32, i32* %rNToGo300, align 8, !dbg !1628
  %dec301 = add nsw i32 %224, -1, !dbg !1628
  store i32 %dec301, i32* %rNToGo300, align 8, !dbg !1628
  %225 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1629
  %rNToGo302 = getelementptr inbounds %struct.DState, %struct.DState* %225, i32 0, i32 5, !dbg !1629
  %226 = load i32, i32* %rNToGo302, align 8, !dbg !1629
  %cmp303 = icmp eq i32 %226, 1, !dbg !1629
  %cond305 = select i1 %cmp303, i32 1, i32 0, !dbg !1629
  %227 = load i8, i8* %k1, align 1, !dbg !1630
  %conv306 = zext i8 %227 to i32, !dbg !1630
  %xor307 = xor i32 %conv306, %cond305, !dbg !1630
  %conv308 = trunc i32 %xor307 to i8, !dbg !1630
  store i8 %conv308, i8* %k1, align 1, !dbg !1630
  %228 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1631
  %nblock_used309 = getelementptr inbounds %struct.DState, %struct.DState* %228, i32 0, i32 17, !dbg !1632
  %229 = load i32, i32* %nblock_used309, align 4, !dbg !1633
  %inc310 = add nsw i32 %229, 1, !dbg !1633
  store i32 %inc310, i32* %nblock_used309, align 4, !dbg !1633
  %230 = load i8, i8* %k1, align 1, !dbg !1634
  %conv311 = zext i8 %230 to i32, !dbg !1635
  %add312 = add nsw i32 %conv311, 4, !dbg !1636
  %231 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1637
  %state_out_len313 = getelementptr inbounds %struct.DState, %struct.DState* %231, i32 0, i32 3, !dbg !1638
  store i32 %add312, i32* %state_out_len313, align 8, !dbg !1639
  %232 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1640
  %tPos314 = getelementptr inbounds %struct.DState, %struct.DState* %232, i32 0, i32 14, !dbg !1640
  %233 = load i32, i32* %tPos314, align 4, !dbg !1640
  %234 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1640
  %blockSize100k315 = getelementptr inbounds %struct.DState, %struct.DState* %234, i32 0, i32 9, !dbg !1640
  %235 = load i32, i32* %blockSize100k315, align 8, !dbg !1640
  %mul316 = mul i32 100000, %235, !dbg !1640
  %cmp317 = icmp uge i32 %233, %mul316, !dbg !1640
  br i1 %cmp317, label %if.then319, label %if.end320, !dbg !1642

if.then319:                                       ; preds = %if.end299
  store i8 1, i8* %retval, align 1, !dbg !1643
  br label %return, !dbg !1643

if.end320:                                        ; preds = %if.end299
  %236 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1645
  %tPos321 = getelementptr inbounds %struct.DState, %struct.DState* %236, i32 0, i32 14, !dbg !1645
  %237 = load i32, i32* %tPos321, align 4, !dbg !1645
  %238 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1645
  %cftab322 = getelementptr inbounds %struct.DState, %struct.DState* %238, i32 0, i32 18, !dbg !1645
  %arraydecay323 = getelementptr inbounds [257 x i32], [257 x i32]* %cftab322, i32 0, i32 0, !dbg !1645
  %call324 = call i32 @BZ2_indexIntoF(i32 %237, i32* %arraydecay323), !dbg !1645
  %239 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1645
  %k0325 = getelementptr inbounds %struct.DState, %struct.DState* %239, i32 0, i32 15, !dbg !1645
  store i32 %call324, i32* %k0325, align 8, !dbg !1645
  %240 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1645
  %tPos326 = getelementptr inbounds %struct.DState, %struct.DState* %240, i32 0, i32 14, !dbg !1645
  %241 = load i32, i32* %tPos326, align 4, !dbg !1645
  %idxprom327 = zext i32 %241 to i64, !dbg !1645
  %242 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1645
  %ll16328 = getelementptr inbounds %struct.DState, %struct.DState* %242, i32 0, i32 21, !dbg !1645
  %243 = load i16*, i16** %ll16328, align 8, !dbg !1645
  %arrayidx329 = getelementptr inbounds i16, i16* %243, i64 %idxprom327, !dbg !1645
  %244 = load i16, i16* %arrayidx329, align 2, !dbg !1645
  %conv330 = zext i16 %244 to i32, !dbg !1645
  %245 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1645
  %tPos331 = getelementptr inbounds %struct.DState, %struct.DState* %245, i32 0, i32 14, !dbg !1645
  %246 = load i32, i32* %tPos331, align 4, !dbg !1645
  %shr332 = lshr i32 %246, 1, !dbg !1645
  %idxprom333 = zext i32 %shr332 to i64, !dbg !1645
  %247 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1645
  %ll4334 = getelementptr inbounds %struct.DState, %struct.DState* %247, i32 0, i32 22, !dbg !1645
  %248 = load i8*, i8** %ll4334, align 8, !dbg !1645
  %arrayidx335 = getelementptr inbounds i8, i8* %248, i64 %idxprom333, !dbg !1645
  %249 = load i8, i8* %arrayidx335, align 1, !dbg !1645
  %conv336 = zext i8 %249 to i32, !dbg !1645
  %250 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1645
  %tPos337 = getelementptr inbounds %struct.DState, %struct.DState* %250, i32 0, i32 14, !dbg !1645
  %251 = load i32, i32* %tPos337, align 4, !dbg !1645
  %shl338 = shl i32 %251, 2, !dbg !1645
  %and339 = and i32 %shl338, 4, !dbg !1645
  %shr340 = lshr i32 %conv336, %and339, !dbg !1645
  %and341 = and i32 %shr340, 15, !dbg !1645
  %shl342 = shl i32 %and341, 16, !dbg !1645
  %or343 = or i32 %conv330, %shl342, !dbg !1645
  %252 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1645
  %tPos344 = getelementptr inbounds %struct.DState, %struct.DState* %252, i32 0, i32 14, !dbg !1645
  store i32 %or343, i32* %tPos344, align 4, !dbg !1645
  %253 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1646
  %rNToGo345 = getelementptr inbounds %struct.DState, %struct.DState* %253, i32 0, i32 5, !dbg !1646
  %254 = load i32, i32* %rNToGo345, align 8, !dbg !1646
  %cmp346 = icmp eq i32 %254, 0, !dbg !1646
  br i1 %cmp346, label %if.then348, label %if.end361, !dbg !1646

if.then348:                                       ; preds = %if.end320
  %255 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1647
  %rTPos349 = getelementptr inbounds %struct.DState, %struct.DState* %255, i32 0, i32 6, !dbg !1647
  %256 = load i32, i32* %rTPos349, align 4, !dbg !1647
  %idxprom350 = sext i32 %256 to i64, !dbg !1647
  %arrayidx351 = getelementptr inbounds [512 x i32], [512 x i32]* @BZ2_rNums, i64 0, i64 %idxprom350, !dbg !1647
  %257 = load i32, i32* %arrayidx351, align 4, !dbg !1647
  %258 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1647
  %rNToGo352 = getelementptr inbounds %struct.DState, %struct.DState* %258, i32 0, i32 5, !dbg !1647
  store i32 %257, i32* %rNToGo352, align 8, !dbg !1647
  %259 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1647
  %rTPos353 = getelementptr inbounds %struct.DState, %struct.DState* %259, i32 0, i32 6, !dbg !1647
  %260 = load i32, i32* %rTPos353, align 4, !dbg !1647
  %inc354 = add nsw i32 %260, 1, !dbg !1647
  store i32 %inc354, i32* %rTPos353, align 4, !dbg !1647
  %261 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1647
  %rTPos355 = getelementptr inbounds %struct.DState, %struct.DState* %261, i32 0, i32 6, !dbg !1647
  %262 = load i32, i32* %rTPos355, align 4, !dbg !1647
  %cmp356 = icmp eq i32 %262, 512, !dbg !1647
  br i1 %cmp356, label %if.then358, label %if.end360, !dbg !1647

if.then358:                                       ; preds = %if.then348
  %263 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1651
  %rTPos359 = getelementptr inbounds %struct.DState, %struct.DState* %263, i32 0, i32 6, !dbg !1651
  store i32 0, i32* %rTPos359, align 4, !dbg !1651
  br label %if.end360, !dbg !1651

if.end360:                                        ; preds = %if.then358, %if.then348
  br label %if.end361, !dbg !1654

if.end361:                                        ; preds = %if.end360, %if.end320
  %264 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1656
  %rNToGo362 = getelementptr inbounds %struct.DState, %struct.DState* %264, i32 0, i32 5, !dbg !1656
  %265 = load i32, i32* %rNToGo362, align 8, !dbg !1656
  %dec363 = add nsw i32 %265, -1, !dbg !1656
  store i32 %dec363, i32* %rNToGo362, align 8, !dbg !1656
  %266 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1657
  %rNToGo364 = getelementptr inbounds %struct.DState, %struct.DState* %266, i32 0, i32 5, !dbg !1657
  %267 = load i32, i32* %rNToGo364, align 8, !dbg !1657
  %cmp365 = icmp eq i32 %267, 1, !dbg !1657
  %cond367 = select i1 %cmp365, i32 1, i32 0, !dbg !1657
  %268 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1658
  %k0368 = getelementptr inbounds %struct.DState, %struct.DState* %268, i32 0, i32 15, !dbg !1659
  %269 = load i32, i32* %k0368, align 8, !dbg !1660
  %xor369 = xor i32 %269, %cond367, !dbg !1660
  store i32 %xor369, i32* %k0368, align 8, !dbg !1660
  %270 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1661
  %nblock_used370 = getelementptr inbounds %struct.DState, %struct.DState* %270, i32 0, i32 17, !dbg !1662
  %271 = load i32, i32* %nblock_used370, align 4, !dbg !1663
  %inc371 = add nsw i32 %271, 1, !dbg !1663
  store i32 %inc371, i32* %nblock_used370, align 4, !dbg !1663
  br label %while.body, !dbg !1664

if.else:                                          ; preds = %entry
  br label %while.body372, !dbg !1666

while.body372:                                    ; preds = %if.else, %if.then477, %if.then483, %if.then526, %if.then532, %if.then575, %if.then581, %if.end627
  br label %while.body374, !dbg !1668

while.body374:                                    ; preds = %while.body372, %if.end419
  %272 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1670
  %strm375 = getelementptr inbounds %struct.DState, %struct.DState* %272, i32 0, i32 0, !dbg !1673
  %273 = load %struct.bz_stream*, %struct.bz_stream** %strm375, align 8, !dbg !1673
  %avail_out376 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %273, i32 0, i32 5, !dbg !1674
  %274 = load i32, i32* %avail_out376, align 8, !dbg !1674
  %cmp377 = icmp eq i32 %274, 0, !dbg !1675
  br i1 %cmp377, label %if.then379, label %if.end380, !dbg !1676

if.then379:                                       ; preds = %while.body374
  store i8 0, i8* %retval, align 1, !dbg !1677
  br label %return, !dbg !1677

if.end380:                                        ; preds = %while.body374
  %275 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1679
  %state_out_len381 = getelementptr inbounds %struct.DState, %struct.DState* %275, i32 0, i32 3, !dbg !1681
  %276 = load i32, i32* %state_out_len381, align 8, !dbg !1681
  %cmp382 = icmp eq i32 %276, 0, !dbg !1682
  br i1 %cmp382, label %if.then384, label %if.end385, !dbg !1683

if.then384:                                       ; preds = %if.end380
  br label %while.end420, !dbg !1684

if.end385:                                        ; preds = %if.end380
  %277 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1686
  %state_out_ch386 = getelementptr inbounds %struct.DState, %struct.DState* %277, i32 0, i32 2, !dbg !1687
  %278 = load i8, i8* %state_out_ch386, align 4, !dbg !1687
  %279 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1688
  %strm387 = getelementptr inbounds %struct.DState, %struct.DState* %279, i32 0, i32 0, !dbg !1689
  %280 = load %struct.bz_stream*, %struct.bz_stream** %strm387, align 8, !dbg !1689
  %next_out388 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %280, i32 0, i32 4, !dbg !1690
  %281 = load i8*, i8** %next_out388, align 8, !dbg !1690
  store i8 %278, i8* %281, align 1, !dbg !1691
  %282 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1692
  %calculatedBlockCRC389 = getelementptr inbounds %struct.DState, %struct.DState* %282, i32 0, i32 25, !dbg !1692
  %283 = load i32, i32* %calculatedBlockCRC389, align 8, !dbg !1692
  %shl390 = shl i32 %283, 8, !dbg !1692
  %284 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1692
  %calculatedBlockCRC391 = getelementptr inbounds %struct.DState, %struct.DState* %284, i32 0, i32 25, !dbg !1692
  %285 = load i32, i32* %calculatedBlockCRC391, align 8, !dbg !1692
  %shr392 = lshr i32 %285, 24, !dbg !1692
  %286 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1692
  %state_out_ch393 = getelementptr inbounds %struct.DState, %struct.DState* %286, i32 0, i32 2, !dbg !1692
  %287 = load i8, i8* %state_out_ch393, align 4, !dbg !1692
  %conv394 = zext i8 %287 to i32, !dbg !1692
  %xor395 = xor i32 %shr392, %conv394, !dbg !1692
  %idxprom396 = zext i32 %xor395 to i64, !dbg !1692
  %arrayidx397 = getelementptr inbounds [256 x i32], [256 x i32]* @BZ2_crc32Table, i64 0, i64 %idxprom396, !dbg !1692
  %288 = load i32, i32* %arrayidx397, align 4, !dbg !1692
  %xor398 = xor i32 %shl390, %288, !dbg !1692
  %289 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1692
  %calculatedBlockCRC399 = getelementptr inbounds %struct.DState, %struct.DState* %289, i32 0, i32 25, !dbg !1692
  store i32 %xor398, i32* %calculatedBlockCRC399, align 8, !dbg !1692
  %290 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1694
  %state_out_len400 = getelementptr inbounds %struct.DState, %struct.DState* %290, i32 0, i32 3, !dbg !1695
  %291 = load i32, i32* %state_out_len400, align 8, !dbg !1696
  %dec401 = add nsw i32 %291, -1, !dbg !1696
  store i32 %dec401, i32* %state_out_len400, align 8, !dbg !1696
  %292 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1697
  %strm402 = getelementptr inbounds %struct.DState, %struct.DState* %292, i32 0, i32 0, !dbg !1698
  %293 = load %struct.bz_stream*, %struct.bz_stream** %strm402, align 8, !dbg !1698
  %next_out403 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %293, i32 0, i32 4, !dbg !1699
  %294 = load i8*, i8** %next_out403, align 8, !dbg !1700
  %incdec.ptr404 = getelementptr inbounds i8, i8* %294, i32 1, !dbg !1700
  store i8* %incdec.ptr404, i8** %next_out403, align 8, !dbg !1700
  %295 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1701
  %strm405 = getelementptr inbounds %struct.DState, %struct.DState* %295, i32 0, i32 0, !dbg !1702
  %296 = load %struct.bz_stream*, %struct.bz_stream** %strm405, align 8, !dbg !1702
  %avail_out406 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %296, i32 0, i32 5, !dbg !1703
  %297 = load i32, i32* %avail_out406, align 8, !dbg !1704
  %dec407 = add i32 %297, -1, !dbg !1704
  store i32 %dec407, i32* %avail_out406, align 8, !dbg !1704
  %298 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1705
  %strm408 = getelementptr inbounds %struct.DState, %struct.DState* %298, i32 0, i32 0, !dbg !1706
  %299 = load %struct.bz_stream*, %struct.bz_stream** %strm408, align 8, !dbg !1706
  %total_out_lo32409 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %299, i32 0, i32 6, !dbg !1707
  %300 = load i32, i32* %total_out_lo32409, align 4, !dbg !1708
  %inc410 = add i32 %300, 1, !dbg !1708
  store i32 %inc410, i32* %total_out_lo32409, align 4, !dbg !1708
  %301 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1709
  %strm411 = getelementptr inbounds %struct.DState, %struct.DState* %301, i32 0, i32 0, !dbg !1711
  %302 = load %struct.bz_stream*, %struct.bz_stream** %strm411, align 8, !dbg !1711
  %total_out_lo32412 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %302, i32 0, i32 6, !dbg !1712
  %303 = load i32, i32* %total_out_lo32412, align 4, !dbg !1712
  %cmp413 = icmp eq i32 %303, 0, !dbg !1713
  br i1 %cmp413, label %if.then415, label %if.end419, !dbg !1714

if.then415:                                       ; preds = %if.end385
  %304 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1715
  %strm416 = getelementptr inbounds %struct.DState, %struct.DState* %304, i32 0, i32 0, !dbg !1717
  %305 = load %struct.bz_stream*, %struct.bz_stream** %strm416, align 8, !dbg !1717
  %total_out_hi32417 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %305, i32 0, i32 7, !dbg !1718
  %306 = load i32, i32* %total_out_hi32417, align 8, !dbg !1719
  %inc418 = add i32 %306, 1, !dbg !1719
  store i32 %inc418, i32* %total_out_hi32417, align 8, !dbg !1719
  br label %if.end419, !dbg !1715

if.end419:                                        ; preds = %if.then415, %if.end385
  br label %while.body374, !dbg !1720

while.end420:                                     ; preds = %if.then384
  %307 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1722
  %nblock_used421 = getelementptr inbounds %struct.DState, %struct.DState* %307, i32 0, i32 17, !dbg !1724
  %308 = load i32, i32* %nblock_used421, align 4, !dbg !1724
  %309 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1725
  %save_nblock422 = getelementptr inbounds %struct.DState, %struct.DState* %309, i32 0, i32 51, !dbg !1726
  %310 = load i32, i32* %save_nblock422, align 8, !dbg !1726
  %add423 = add nsw i32 %310, 1, !dbg !1727
  %cmp424 = icmp eq i32 %308, %add423, !dbg !1728
  br i1 %cmp424, label %if.then426, label %if.end427, !dbg !1729

if.then426:                                       ; preds = %while.end420
  store i8 0, i8* %retval, align 1, !dbg !1730
  br label %return, !dbg !1730

if.end427:                                        ; preds = %while.end420
  %311 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1732
  %nblock_used428 = getelementptr inbounds %struct.DState, %struct.DState* %311, i32 0, i32 17, !dbg !1734
  %312 = load i32, i32* %nblock_used428, align 4, !dbg !1734
  %313 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1735
  %save_nblock429 = getelementptr inbounds %struct.DState, %struct.DState* %313, i32 0, i32 51, !dbg !1736
  %314 = load i32, i32* %save_nblock429, align 8, !dbg !1736
  %add430 = add nsw i32 %314, 1, !dbg !1737
  %cmp431 = icmp sgt i32 %312, %add430, !dbg !1738
  br i1 %cmp431, label %if.then433, label %if.end434, !dbg !1739

if.then433:                                       ; preds = %if.end427
  store i8 1, i8* %retval, align 1, !dbg !1740
  br label %return, !dbg !1740

if.end434:                                        ; preds = %if.end427
  %315 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1741
  %state_out_len435 = getelementptr inbounds %struct.DState, %struct.DState* %315, i32 0, i32 3, !dbg !1742
  store i32 1, i32* %state_out_len435, align 8, !dbg !1743
  %316 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1744
  %k0436 = getelementptr inbounds %struct.DState, %struct.DState* %316, i32 0, i32 15, !dbg !1745
  %317 = load i32, i32* %k0436, align 8, !dbg !1745
  %conv437 = trunc i32 %317 to i8, !dbg !1744
  %318 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1746
  %state_out_ch438 = getelementptr inbounds %struct.DState, %struct.DState* %318, i32 0, i32 2, !dbg !1747
  store i8 %conv437, i8* %state_out_ch438, align 4, !dbg !1748
  %319 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1749
  %tPos439 = getelementptr inbounds %struct.DState, %struct.DState* %319, i32 0, i32 14, !dbg !1749
  %320 = load i32, i32* %tPos439, align 4, !dbg !1749
  %321 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1749
  %blockSize100k440 = getelementptr inbounds %struct.DState, %struct.DState* %321, i32 0, i32 9, !dbg !1749
  %322 = load i32, i32* %blockSize100k440, align 8, !dbg !1749
  %mul441 = mul i32 100000, %322, !dbg !1749
  %cmp442 = icmp uge i32 %320, %mul441, !dbg !1749
  br i1 %cmp442, label %if.then444, label %if.end445, !dbg !1751

if.then444:                                       ; preds = %if.end434
  store i8 1, i8* %retval, align 1, !dbg !1752
  br label %return, !dbg !1752

if.end445:                                        ; preds = %if.end434
  %323 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1754
  %tPos446 = getelementptr inbounds %struct.DState, %struct.DState* %323, i32 0, i32 14, !dbg !1754
  %324 = load i32, i32* %tPos446, align 4, !dbg !1754
  %325 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1754
  %cftab447 = getelementptr inbounds %struct.DState, %struct.DState* %325, i32 0, i32 18, !dbg !1754
  %arraydecay448 = getelementptr inbounds [257 x i32], [257 x i32]* %cftab447, i32 0, i32 0, !dbg !1754
  %call449 = call i32 @BZ2_indexIntoF(i32 %324, i32* %arraydecay448), !dbg !1754
  %conv450 = trunc i32 %call449 to i8, !dbg !1754
  store i8 %conv450, i8* %k1, align 1, !dbg !1754
  %326 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1754
  %tPos451 = getelementptr inbounds %struct.DState, %struct.DState* %326, i32 0, i32 14, !dbg !1754
  %327 = load i32, i32* %tPos451, align 4, !dbg !1754
  %idxprom452 = zext i32 %327 to i64, !dbg !1754
  %328 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1754
  %ll16453 = getelementptr inbounds %struct.DState, %struct.DState* %328, i32 0, i32 21, !dbg !1754
  %329 = load i16*, i16** %ll16453, align 8, !dbg !1754
  %arrayidx454 = getelementptr inbounds i16, i16* %329, i64 %idxprom452, !dbg !1754
  %330 = load i16, i16* %arrayidx454, align 2, !dbg !1754
  %conv455 = zext i16 %330 to i32, !dbg !1754
  %331 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1754
  %tPos456 = getelementptr inbounds %struct.DState, %struct.DState* %331, i32 0, i32 14, !dbg !1754
  %332 = load i32, i32* %tPos456, align 4, !dbg !1754
  %shr457 = lshr i32 %332, 1, !dbg !1754
  %idxprom458 = zext i32 %shr457 to i64, !dbg !1754
  %333 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1754
  %ll4459 = getelementptr inbounds %struct.DState, %struct.DState* %333, i32 0, i32 22, !dbg !1754
  %334 = load i8*, i8** %ll4459, align 8, !dbg !1754
  %arrayidx460 = getelementptr inbounds i8, i8* %334, i64 %idxprom458, !dbg !1754
  %335 = load i8, i8* %arrayidx460, align 1, !dbg !1754
  %conv461 = zext i8 %335 to i32, !dbg !1754
  %336 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1754
  %tPos462 = getelementptr inbounds %struct.DState, %struct.DState* %336, i32 0, i32 14, !dbg !1754
  %337 = load i32, i32* %tPos462, align 4, !dbg !1754
  %shl463 = shl i32 %337, 2, !dbg !1754
  %and464 = and i32 %shl463, 4, !dbg !1754
  %shr465 = lshr i32 %conv461, %and464, !dbg !1754
  %and466 = and i32 %shr465, 15, !dbg !1754
  %shl467 = shl i32 %and466, 16, !dbg !1754
  %or468 = or i32 %conv455, %shl467, !dbg !1754
  %338 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1754
  %tPos469 = getelementptr inbounds %struct.DState, %struct.DState* %338, i32 0, i32 14, !dbg !1754
  store i32 %or468, i32* %tPos469, align 4, !dbg !1754
  %339 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1756
  %nblock_used470 = getelementptr inbounds %struct.DState, %struct.DState* %339, i32 0, i32 17, !dbg !1757
  %340 = load i32, i32* %nblock_used470, align 4, !dbg !1758
  %inc471 = add nsw i32 %340, 1, !dbg !1758
  store i32 %inc471, i32* %nblock_used470, align 4, !dbg !1758
  %341 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1759
  %nblock_used472 = getelementptr inbounds %struct.DState, %struct.DState* %341, i32 0, i32 17, !dbg !1761
  %342 = load i32, i32* %nblock_used472, align 4, !dbg !1761
  %343 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1762
  %save_nblock473 = getelementptr inbounds %struct.DState, %struct.DState* %343, i32 0, i32 51, !dbg !1763
  %344 = load i32, i32* %save_nblock473, align 8, !dbg !1763
  %add474 = add nsw i32 %344, 1, !dbg !1764
  %cmp475 = icmp eq i32 %342, %add474, !dbg !1765
  br i1 %cmp475, label %if.then477, label %if.end478, !dbg !1766

if.then477:                                       ; preds = %if.end445
  br label %while.body372, !dbg !1767

if.end478:                                        ; preds = %if.end445
  %345 = load i8, i8* %k1, align 1, !dbg !1769
  %conv479 = zext i8 %345 to i32, !dbg !1769
  %346 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1771
  %k0480 = getelementptr inbounds %struct.DState, %struct.DState* %346, i32 0, i32 15, !dbg !1772
  %347 = load i32, i32* %k0480, align 8, !dbg !1772
  %cmp481 = icmp ne i32 %conv479, %347, !dbg !1773
  br i1 %cmp481, label %if.then483, label %if.end486, !dbg !1774

if.then483:                                       ; preds = %if.end478
  %348 = load i8, i8* %k1, align 1, !dbg !1775
  %conv484 = zext i8 %348 to i32, !dbg !1775
  %349 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1778
  %k0485 = getelementptr inbounds %struct.DState, %struct.DState* %349, i32 0, i32 15, !dbg !1779
  store i32 %conv484, i32* %k0485, align 8, !dbg !1780
  br label %while.body372, !dbg !1781

if.end486:                                        ; preds = %if.end478
  %350 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1782
  %state_out_len487 = getelementptr inbounds %struct.DState, %struct.DState* %350, i32 0, i32 3, !dbg !1783
  store i32 2, i32* %state_out_len487, align 8, !dbg !1784
  %351 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1785
  %tPos488 = getelementptr inbounds %struct.DState, %struct.DState* %351, i32 0, i32 14, !dbg !1785
  %352 = load i32, i32* %tPos488, align 4, !dbg !1785
  %353 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1785
  %blockSize100k489 = getelementptr inbounds %struct.DState, %struct.DState* %353, i32 0, i32 9, !dbg !1785
  %354 = load i32, i32* %blockSize100k489, align 8, !dbg !1785
  %mul490 = mul i32 100000, %354, !dbg !1785
  %cmp491 = icmp uge i32 %352, %mul490, !dbg !1785
  br i1 %cmp491, label %if.then493, label %if.end494, !dbg !1787

if.then493:                                       ; preds = %if.end486
  store i8 1, i8* %retval, align 1, !dbg !1788
  br label %return, !dbg !1788

if.end494:                                        ; preds = %if.end486
  %355 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1790
  %tPos495 = getelementptr inbounds %struct.DState, %struct.DState* %355, i32 0, i32 14, !dbg !1790
  %356 = load i32, i32* %tPos495, align 4, !dbg !1790
  %357 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1790
  %cftab496 = getelementptr inbounds %struct.DState, %struct.DState* %357, i32 0, i32 18, !dbg !1790
  %arraydecay497 = getelementptr inbounds [257 x i32], [257 x i32]* %cftab496, i32 0, i32 0, !dbg !1790
  %call498 = call i32 @BZ2_indexIntoF(i32 %356, i32* %arraydecay497), !dbg !1790
  %conv499 = trunc i32 %call498 to i8, !dbg !1790
  store i8 %conv499, i8* %k1, align 1, !dbg !1790
  %358 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1790
  %tPos500 = getelementptr inbounds %struct.DState, %struct.DState* %358, i32 0, i32 14, !dbg !1790
  %359 = load i32, i32* %tPos500, align 4, !dbg !1790
  %idxprom501 = zext i32 %359 to i64, !dbg !1790
  %360 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1790
  %ll16502 = getelementptr inbounds %struct.DState, %struct.DState* %360, i32 0, i32 21, !dbg !1790
  %361 = load i16*, i16** %ll16502, align 8, !dbg !1790
  %arrayidx503 = getelementptr inbounds i16, i16* %361, i64 %idxprom501, !dbg !1790
  %362 = load i16, i16* %arrayidx503, align 2, !dbg !1790
  %conv504 = zext i16 %362 to i32, !dbg !1790
  %363 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1790
  %tPos505 = getelementptr inbounds %struct.DState, %struct.DState* %363, i32 0, i32 14, !dbg !1790
  %364 = load i32, i32* %tPos505, align 4, !dbg !1790
  %shr506 = lshr i32 %364, 1, !dbg !1790
  %idxprom507 = zext i32 %shr506 to i64, !dbg !1790
  %365 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1790
  %ll4508 = getelementptr inbounds %struct.DState, %struct.DState* %365, i32 0, i32 22, !dbg !1790
  %366 = load i8*, i8** %ll4508, align 8, !dbg !1790
  %arrayidx509 = getelementptr inbounds i8, i8* %366, i64 %idxprom507, !dbg !1790
  %367 = load i8, i8* %arrayidx509, align 1, !dbg !1790
  %conv510 = zext i8 %367 to i32, !dbg !1790
  %368 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1790
  %tPos511 = getelementptr inbounds %struct.DState, %struct.DState* %368, i32 0, i32 14, !dbg !1790
  %369 = load i32, i32* %tPos511, align 4, !dbg !1790
  %shl512 = shl i32 %369, 2, !dbg !1790
  %and513 = and i32 %shl512, 4, !dbg !1790
  %shr514 = lshr i32 %conv510, %and513, !dbg !1790
  %and515 = and i32 %shr514, 15, !dbg !1790
  %shl516 = shl i32 %and515, 16, !dbg !1790
  %or517 = or i32 %conv504, %shl516, !dbg !1790
  %370 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1790
  %tPos518 = getelementptr inbounds %struct.DState, %struct.DState* %370, i32 0, i32 14, !dbg !1790
  store i32 %or517, i32* %tPos518, align 4, !dbg !1790
  %371 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1791
  %nblock_used519 = getelementptr inbounds %struct.DState, %struct.DState* %371, i32 0, i32 17, !dbg !1792
  %372 = load i32, i32* %nblock_used519, align 4, !dbg !1793
  %inc520 = add nsw i32 %372, 1, !dbg !1793
  store i32 %inc520, i32* %nblock_used519, align 4, !dbg !1793
  %373 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1794
  %nblock_used521 = getelementptr inbounds %struct.DState, %struct.DState* %373, i32 0, i32 17, !dbg !1796
  %374 = load i32, i32* %nblock_used521, align 4, !dbg !1796
  %375 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1797
  %save_nblock522 = getelementptr inbounds %struct.DState, %struct.DState* %375, i32 0, i32 51, !dbg !1798
  %376 = load i32, i32* %save_nblock522, align 8, !dbg !1798
  %add523 = add nsw i32 %376, 1, !dbg !1799
  %cmp524 = icmp eq i32 %374, %add523, !dbg !1800
  br i1 %cmp524, label %if.then526, label %if.end527, !dbg !1801

if.then526:                                       ; preds = %if.end494
  br label %while.body372, !dbg !1802

if.end527:                                        ; preds = %if.end494
  %377 = load i8, i8* %k1, align 1, !dbg !1804
  %conv528 = zext i8 %377 to i32, !dbg !1804
  %378 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1806
  %k0529 = getelementptr inbounds %struct.DState, %struct.DState* %378, i32 0, i32 15, !dbg !1807
  %379 = load i32, i32* %k0529, align 8, !dbg !1807
  %cmp530 = icmp ne i32 %conv528, %379, !dbg !1808
  br i1 %cmp530, label %if.then532, label %if.end535, !dbg !1809

if.then532:                                       ; preds = %if.end527
  %380 = load i8, i8* %k1, align 1, !dbg !1810
  %conv533 = zext i8 %380 to i32, !dbg !1810
  %381 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1813
  %k0534 = getelementptr inbounds %struct.DState, %struct.DState* %381, i32 0, i32 15, !dbg !1814
  store i32 %conv533, i32* %k0534, align 8, !dbg !1815
  br label %while.body372, !dbg !1816

if.end535:                                        ; preds = %if.end527
  %382 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1817
  %state_out_len536 = getelementptr inbounds %struct.DState, %struct.DState* %382, i32 0, i32 3, !dbg !1818
  store i32 3, i32* %state_out_len536, align 8, !dbg !1819
  %383 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1820
  %tPos537 = getelementptr inbounds %struct.DState, %struct.DState* %383, i32 0, i32 14, !dbg !1820
  %384 = load i32, i32* %tPos537, align 4, !dbg !1820
  %385 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1820
  %blockSize100k538 = getelementptr inbounds %struct.DState, %struct.DState* %385, i32 0, i32 9, !dbg !1820
  %386 = load i32, i32* %blockSize100k538, align 8, !dbg !1820
  %mul539 = mul i32 100000, %386, !dbg !1820
  %cmp540 = icmp uge i32 %384, %mul539, !dbg !1820
  br i1 %cmp540, label %if.then542, label %if.end543, !dbg !1822

if.then542:                                       ; preds = %if.end535
  store i8 1, i8* %retval, align 1, !dbg !1823
  br label %return, !dbg !1823

if.end543:                                        ; preds = %if.end535
  %387 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1825
  %tPos544 = getelementptr inbounds %struct.DState, %struct.DState* %387, i32 0, i32 14, !dbg !1825
  %388 = load i32, i32* %tPos544, align 4, !dbg !1825
  %389 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1825
  %cftab545 = getelementptr inbounds %struct.DState, %struct.DState* %389, i32 0, i32 18, !dbg !1825
  %arraydecay546 = getelementptr inbounds [257 x i32], [257 x i32]* %cftab545, i32 0, i32 0, !dbg !1825
  %call547 = call i32 @BZ2_indexIntoF(i32 %388, i32* %arraydecay546), !dbg !1825
  %conv548 = trunc i32 %call547 to i8, !dbg !1825
  store i8 %conv548, i8* %k1, align 1, !dbg !1825
  %390 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1825
  %tPos549 = getelementptr inbounds %struct.DState, %struct.DState* %390, i32 0, i32 14, !dbg !1825
  %391 = load i32, i32* %tPos549, align 4, !dbg !1825
  %idxprom550 = zext i32 %391 to i64, !dbg !1825
  %392 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1825
  %ll16551 = getelementptr inbounds %struct.DState, %struct.DState* %392, i32 0, i32 21, !dbg !1825
  %393 = load i16*, i16** %ll16551, align 8, !dbg !1825
  %arrayidx552 = getelementptr inbounds i16, i16* %393, i64 %idxprom550, !dbg !1825
  %394 = load i16, i16* %arrayidx552, align 2, !dbg !1825
  %conv553 = zext i16 %394 to i32, !dbg !1825
  %395 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1825
  %tPos554 = getelementptr inbounds %struct.DState, %struct.DState* %395, i32 0, i32 14, !dbg !1825
  %396 = load i32, i32* %tPos554, align 4, !dbg !1825
  %shr555 = lshr i32 %396, 1, !dbg !1825
  %idxprom556 = zext i32 %shr555 to i64, !dbg !1825
  %397 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1825
  %ll4557 = getelementptr inbounds %struct.DState, %struct.DState* %397, i32 0, i32 22, !dbg !1825
  %398 = load i8*, i8** %ll4557, align 8, !dbg !1825
  %arrayidx558 = getelementptr inbounds i8, i8* %398, i64 %idxprom556, !dbg !1825
  %399 = load i8, i8* %arrayidx558, align 1, !dbg !1825
  %conv559 = zext i8 %399 to i32, !dbg !1825
  %400 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1825
  %tPos560 = getelementptr inbounds %struct.DState, %struct.DState* %400, i32 0, i32 14, !dbg !1825
  %401 = load i32, i32* %tPos560, align 4, !dbg !1825
  %shl561 = shl i32 %401, 2, !dbg !1825
  %and562 = and i32 %shl561, 4, !dbg !1825
  %shr563 = lshr i32 %conv559, %and562, !dbg !1825
  %and564 = and i32 %shr563, 15, !dbg !1825
  %shl565 = shl i32 %and564, 16, !dbg !1825
  %or566 = or i32 %conv553, %shl565, !dbg !1825
  %402 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1825
  %tPos567 = getelementptr inbounds %struct.DState, %struct.DState* %402, i32 0, i32 14, !dbg !1825
  store i32 %or566, i32* %tPos567, align 4, !dbg !1825
  %403 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1826
  %nblock_used568 = getelementptr inbounds %struct.DState, %struct.DState* %403, i32 0, i32 17, !dbg !1827
  %404 = load i32, i32* %nblock_used568, align 4, !dbg !1828
  %inc569 = add nsw i32 %404, 1, !dbg !1828
  store i32 %inc569, i32* %nblock_used568, align 4, !dbg !1828
  %405 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1829
  %nblock_used570 = getelementptr inbounds %struct.DState, %struct.DState* %405, i32 0, i32 17, !dbg !1831
  %406 = load i32, i32* %nblock_used570, align 4, !dbg !1831
  %407 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1832
  %save_nblock571 = getelementptr inbounds %struct.DState, %struct.DState* %407, i32 0, i32 51, !dbg !1833
  %408 = load i32, i32* %save_nblock571, align 8, !dbg !1833
  %add572 = add nsw i32 %408, 1, !dbg !1834
  %cmp573 = icmp eq i32 %406, %add572, !dbg !1835
  br i1 %cmp573, label %if.then575, label %if.end576, !dbg !1836

if.then575:                                       ; preds = %if.end543
  br label %while.body372, !dbg !1837

if.end576:                                        ; preds = %if.end543
  %409 = load i8, i8* %k1, align 1, !dbg !1839
  %conv577 = zext i8 %409 to i32, !dbg !1839
  %410 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1841
  %k0578 = getelementptr inbounds %struct.DState, %struct.DState* %410, i32 0, i32 15, !dbg !1842
  %411 = load i32, i32* %k0578, align 8, !dbg !1842
  %cmp579 = icmp ne i32 %conv577, %411, !dbg !1843
  br i1 %cmp579, label %if.then581, label %if.end584, !dbg !1844

if.then581:                                       ; preds = %if.end576
  %412 = load i8, i8* %k1, align 1, !dbg !1845
  %conv582 = zext i8 %412 to i32, !dbg !1845
  %413 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1848
  %k0583 = getelementptr inbounds %struct.DState, %struct.DState* %413, i32 0, i32 15, !dbg !1849
  store i32 %conv582, i32* %k0583, align 8, !dbg !1850
  br label %while.body372, !dbg !1851

if.end584:                                        ; preds = %if.end576
  %414 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1852
  %tPos585 = getelementptr inbounds %struct.DState, %struct.DState* %414, i32 0, i32 14, !dbg !1852
  %415 = load i32, i32* %tPos585, align 4, !dbg !1852
  %416 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1852
  %blockSize100k586 = getelementptr inbounds %struct.DState, %struct.DState* %416, i32 0, i32 9, !dbg !1852
  %417 = load i32, i32* %blockSize100k586, align 8, !dbg !1852
  %mul587 = mul i32 100000, %417, !dbg !1852
  %cmp588 = icmp uge i32 %415, %mul587, !dbg !1852
  br i1 %cmp588, label %if.then590, label %if.end591, !dbg !1854

if.then590:                                       ; preds = %if.end584
  store i8 1, i8* %retval, align 1, !dbg !1855
  br label %return, !dbg !1855

if.end591:                                        ; preds = %if.end584
  %418 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1857
  %tPos592 = getelementptr inbounds %struct.DState, %struct.DState* %418, i32 0, i32 14, !dbg !1857
  %419 = load i32, i32* %tPos592, align 4, !dbg !1857
  %420 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1857
  %cftab593 = getelementptr inbounds %struct.DState, %struct.DState* %420, i32 0, i32 18, !dbg !1857
  %arraydecay594 = getelementptr inbounds [257 x i32], [257 x i32]* %cftab593, i32 0, i32 0, !dbg !1857
  %call595 = call i32 @BZ2_indexIntoF(i32 %419, i32* %arraydecay594), !dbg !1857
  %conv596 = trunc i32 %call595 to i8, !dbg !1857
  store i8 %conv596, i8* %k1, align 1, !dbg !1857
  %421 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1857
  %tPos597 = getelementptr inbounds %struct.DState, %struct.DState* %421, i32 0, i32 14, !dbg !1857
  %422 = load i32, i32* %tPos597, align 4, !dbg !1857
  %idxprom598 = zext i32 %422 to i64, !dbg !1857
  %423 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1857
  %ll16599 = getelementptr inbounds %struct.DState, %struct.DState* %423, i32 0, i32 21, !dbg !1857
  %424 = load i16*, i16** %ll16599, align 8, !dbg !1857
  %arrayidx600 = getelementptr inbounds i16, i16* %424, i64 %idxprom598, !dbg !1857
  %425 = load i16, i16* %arrayidx600, align 2, !dbg !1857
  %conv601 = zext i16 %425 to i32, !dbg !1857
  %426 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1857
  %tPos602 = getelementptr inbounds %struct.DState, %struct.DState* %426, i32 0, i32 14, !dbg !1857
  %427 = load i32, i32* %tPos602, align 4, !dbg !1857
  %shr603 = lshr i32 %427, 1, !dbg !1857
  %idxprom604 = zext i32 %shr603 to i64, !dbg !1857
  %428 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1857
  %ll4605 = getelementptr inbounds %struct.DState, %struct.DState* %428, i32 0, i32 22, !dbg !1857
  %429 = load i8*, i8** %ll4605, align 8, !dbg !1857
  %arrayidx606 = getelementptr inbounds i8, i8* %429, i64 %idxprom604, !dbg !1857
  %430 = load i8, i8* %arrayidx606, align 1, !dbg !1857
  %conv607 = zext i8 %430 to i32, !dbg !1857
  %431 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1857
  %tPos608 = getelementptr inbounds %struct.DState, %struct.DState* %431, i32 0, i32 14, !dbg !1857
  %432 = load i32, i32* %tPos608, align 4, !dbg !1857
  %shl609 = shl i32 %432, 2, !dbg !1857
  %and610 = and i32 %shl609, 4, !dbg !1857
  %shr611 = lshr i32 %conv607, %and610, !dbg !1857
  %and612 = and i32 %shr611, 15, !dbg !1857
  %shl613 = shl i32 %and612, 16, !dbg !1857
  %or614 = or i32 %conv601, %shl613, !dbg !1857
  %433 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1857
  %tPos615 = getelementptr inbounds %struct.DState, %struct.DState* %433, i32 0, i32 14, !dbg !1857
  store i32 %or614, i32* %tPos615, align 4, !dbg !1857
  %434 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1858
  %nblock_used616 = getelementptr inbounds %struct.DState, %struct.DState* %434, i32 0, i32 17, !dbg !1859
  %435 = load i32, i32* %nblock_used616, align 4, !dbg !1860
  %inc617 = add nsw i32 %435, 1, !dbg !1860
  store i32 %inc617, i32* %nblock_used616, align 4, !dbg !1860
  %436 = load i8, i8* %k1, align 1, !dbg !1861
  %conv618 = zext i8 %436 to i32, !dbg !1862
  %add619 = add nsw i32 %conv618, 4, !dbg !1863
  %437 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1864
  %state_out_len620 = getelementptr inbounds %struct.DState, %struct.DState* %437, i32 0, i32 3, !dbg !1865
  store i32 %add619, i32* %state_out_len620, align 8, !dbg !1866
  %438 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1867
  %tPos621 = getelementptr inbounds %struct.DState, %struct.DState* %438, i32 0, i32 14, !dbg !1867
  %439 = load i32, i32* %tPos621, align 4, !dbg !1867
  %440 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1867
  %blockSize100k622 = getelementptr inbounds %struct.DState, %struct.DState* %440, i32 0, i32 9, !dbg !1867
  %441 = load i32, i32* %blockSize100k622, align 8, !dbg !1867
  %mul623 = mul i32 100000, %441, !dbg !1867
  %cmp624 = icmp uge i32 %439, %mul623, !dbg !1867
  br i1 %cmp624, label %if.then626, label %if.end627, !dbg !1869

if.then626:                                       ; preds = %if.end591
  store i8 1, i8* %retval, align 1, !dbg !1870
  br label %return, !dbg !1870

if.end627:                                        ; preds = %if.end591
  %442 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1872
  %tPos628 = getelementptr inbounds %struct.DState, %struct.DState* %442, i32 0, i32 14, !dbg !1872
  %443 = load i32, i32* %tPos628, align 4, !dbg !1872
  %444 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1872
  %cftab629 = getelementptr inbounds %struct.DState, %struct.DState* %444, i32 0, i32 18, !dbg !1872
  %arraydecay630 = getelementptr inbounds [257 x i32], [257 x i32]* %cftab629, i32 0, i32 0, !dbg !1872
  %call631 = call i32 @BZ2_indexIntoF(i32 %443, i32* %arraydecay630), !dbg !1872
  %445 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1872
  %k0632 = getelementptr inbounds %struct.DState, %struct.DState* %445, i32 0, i32 15, !dbg !1872
  store i32 %call631, i32* %k0632, align 8, !dbg !1872
  %446 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1872
  %tPos633 = getelementptr inbounds %struct.DState, %struct.DState* %446, i32 0, i32 14, !dbg !1872
  %447 = load i32, i32* %tPos633, align 4, !dbg !1872
  %idxprom634 = zext i32 %447 to i64, !dbg !1872
  %448 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1872
  %ll16635 = getelementptr inbounds %struct.DState, %struct.DState* %448, i32 0, i32 21, !dbg !1872
  %449 = load i16*, i16** %ll16635, align 8, !dbg !1872
  %arrayidx636 = getelementptr inbounds i16, i16* %449, i64 %idxprom634, !dbg !1872
  %450 = load i16, i16* %arrayidx636, align 2, !dbg !1872
  %conv637 = zext i16 %450 to i32, !dbg !1872
  %451 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1872
  %tPos638 = getelementptr inbounds %struct.DState, %struct.DState* %451, i32 0, i32 14, !dbg !1872
  %452 = load i32, i32* %tPos638, align 4, !dbg !1872
  %shr639 = lshr i32 %452, 1, !dbg !1872
  %idxprom640 = zext i32 %shr639 to i64, !dbg !1872
  %453 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1872
  %ll4641 = getelementptr inbounds %struct.DState, %struct.DState* %453, i32 0, i32 22, !dbg !1872
  %454 = load i8*, i8** %ll4641, align 8, !dbg !1872
  %arrayidx642 = getelementptr inbounds i8, i8* %454, i64 %idxprom640, !dbg !1872
  %455 = load i8, i8* %arrayidx642, align 1, !dbg !1872
  %conv643 = zext i8 %455 to i32, !dbg !1872
  %456 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1872
  %tPos644 = getelementptr inbounds %struct.DState, %struct.DState* %456, i32 0, i32 14, !dbg !1872
  %457 = load i32, i32* %tPos644, align 4, !dbg !1872
  %shl645 = shl i32 %457, 2, !dbg !1872
  %and646 = and i32 %shl645, 4, !dbg !1872
  %shr647 = lshr i32 %conv643, %and646, !dbg !1872
  %and648 = and i32 %shr647, 15, !dbg !1872
  %shl649 = shl i32 %and648, 16, !dbg !1872
  %or650 = or i32 %conv637, %shl649, !dbg !1872
  %458 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1872
  %tPos651 = getelementptr inbounds %struct.DState, %struct.DState* %458, i32 0, i32 14, !dbg !1872
  store i32 %or650, i32* %tPos651, align 4, !dbg !1872
  %459 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1873
  %nblock_used652 = getelementptr inbounds %struct.DState, %struct.DState* %459, i32 0, i32 17, !dbg !1874
  %460 = load i32, i32* %nblock_used652, align 4, !dbg !1875
  %inc653 = add nsw i32 %460, 1, !dbg !1875
  store i32 %inc653, i32* %nblock_used652, align 4, !dbg !1875
  br label %while.body372, !dbg !1876

return:                                           ; preds = %if.then626, %if.then590, %if.then542, %if.then493, %if.then444, %if.then433, %if.then426, %if.then379, %if.then319, %if.then257, %if.then183, %if.then108, %if.then43, %if.then36, %if.then29, %if.then3
  %461 = load i8, i8* %retval, align 1, !dbg !1878
  ret i8 %461, !dbg !1878
}

; Function Attrs: nounwind uwtable
define internal zeroext i8 @unRLE_obuf_to_output_FAST(%struct.DState* %s) #0 !dbg !378 {
entry:
  %retval = alloca i8, align 1
  %s.addr = alloca %struct.DState*, align 8
  %k1 = alloca i8, align 1
  %c_calculatedBlockCRC = alloca i32, align 4
  %c_state_out_ch = alloca i8, align 1
  %c_state_out_len = alloca i32, align 4
  %c_nblock_used = alloca i32, align 4
  %c_k0 = alloca i32, align 4
  %c_tt = alloca i32*, align 8
  %c_tPos = alloca i32, align 4
  %cs_next_out = alloca i8*, align 8
  %cs_avail_out = alloca i32, align 4
  %ro_blockSize100k = alloca i32, align 4
  %avail_out_INIT = alloca i32, align 4
  %s_save_nblockPP = alloca i32, align 4
  %total_out_lo32_old = alloca i32, align 4
  store %struct.DState* %s, %struct.DState** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.DState** %s.addr, metadata !1879, metadata !392), !dbg !1880
  call void @llvm.dbg.declare(metadata i8* %k1, metadata !1881, metadata !392), !dbg !1882
  %0 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1883
  %blockRandomised = getelementptr inbounds %struct.DState, %struct.DState* %0, i32 0, i32 4, !dbg !1885
  %1 = load i8, i8* %blockRandomised, align 4, !dbg !1885
  %tobool = icmp ne i8 %1, 0, !dbg !1883
  br i1 %tobool, label %if.then, label %if.else, !dbg !1886

if.then:                                          ; preds = %entry
  br label %while.body, !dbg !1887

while.body:                                       ; preds = %if.then, %if.then83, %if.then89, %if.then144, %if.then150, %if.then205, %if.then211, %if.end298
  br label %while.body2, !dbg !1889

while.body2:                                      ; preds = %while.body, %if.end26
  %2 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1891
  %strm = getelementptr inbounds %struct.DState, %struct.DState* %2, i32 0, i32 0, !dbg !1894
  %3 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !1894
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %3, i32 0, i32 5, !dbg !1895
  %4 = load i32, i32* %avail_out, align 8, !dbg !1895
  %cmp = icmp eq i32 %4, 0, !dbg !1896
  br i1 %cmp, label %if.then3, label %if.end, !dbg !1897

if.then3:                                         ; preds = %while.body2
  store i8 0, i8* %retval, align 1, !dbg !1898
  br label %return, !dbg !1898

if.end:                                           ; preds = %while.body2
  %5 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1900
  %state_out_len = getelementptr inbounds %struct.DState, %struct.DState* %5, i32 0, i32 3, !dbg !1902
  %6 = load i32, i32* %state_out_len, align 8, !dbg !1902
  %cmp4 = icmp eq i32 %6, 0, !dbg !1903
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !1904

if.then5:                                         ; preds = %if.end
  br label %while.end, !dbg !1905

if.end6:                                          ; preds = %if.end
  %7 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1907
  %state_out_ch = getelementptr inbounds %struct.DState, %struct.DState* %7, i32 0, i32 2, !dbg !1908
  %8 = load i8, i8* %state_out_ch, align 4, !dbg !1908
  %9 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1909
  %strm7 = getelementptr inbounds %struct.DState, %struct.DState* %9, i32 0, i32 0, !dbg !1910
  %10 = load %struct.bz_stream*, %struct.bz_stream** %strm7, align 8, !dbg !1910
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %10, i32 0, i32 4, !dbg !1911
  %11 = load i8*, i8** %next_out, align 8, !dbg !1911
  store i8 %8, i8* %11, align 1, !dbg !1912
  %12 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1913
  %calculatedBlockCRC = getelementptr inbounds %struct.DState, %struct.DState* %12, i32 0, i32 25, !dbg !1913
  %13 = load i32, i32* %calculatedBlockCRC, align 8, !dbg !1913
  %shl = shl i32 %13, 8, !dbg !1913
  %14 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1913
  %calculatedBlockCRC8 = getelementptr inbounds %struct.DState, %struct.DState* %14, i32 0, i32 25, !dbg !1913
  %15 = load i32, i32* %calculatedBlockCRC8, align 8, !dbg !1913
  %shr = lshr i32 %15, 24, !dbg !1913
  %16 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1913
  %state_out_ch9 = getelementptr inbounds %struct.DState, %struct.DState* %16, i32 0, i32 2, !dbg !1913
  %17 = load i8, i8* %state_out_ch9, align 4, !dbg !1913
  %conv = zext i8 %17 to i32, !dbg !1913
  %xor = xor i32 %shr, %conv, !dbg !1913
  %idxprom = zext i32 %xor to i64, !dbg !1913
  %arrayidx = getelementptr inbounds [256 x i32], [256 x i32]* @BZ2_crc32Table, i64 0, i64 %idxprom, !dbg !1913
  %18 = load i32, i32* %arrayidx, align 4, !dbg !1913
  %xor10 = xor i32 %shl, %18, !dbg !1913
  %19 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1913
  %calculatedBlockCRC11 = getelementptr inbounds %struct.DState, %struct.DState* %19, i32 0, i32 25, !dbg !1913
  store i32 %xor10, i32* %calculatedBlockCRC11, align 8, !dbg !1913
  %20 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1915
  %state_out_len12 = getelementptr inbounds %struct.DState, %struct.DState* %20, i32 0, i32 3, !dbg !1916
  %21 = load i32, i32* %state_out_len12, align 8, !dbg !1917
  %dec = add nsw i32 %21, -1, !dbg !1917
  store i32 %dec, i32* %state_out_len12, align 8, !dbg !1917
  %22 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1918
  %strm13 = getelementptr inbounds %struct.DState, %struct.DState* %22, i32 0, i32 0, !dbg !1919
  %23 = load %struct.bz_stream*, %struct.bz_stream** %strm13, align 8, !dbg !1919
  %next_out14 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %23, i32 0, i32 4, !dbg !1920
  %24 = load i8*, i8** %next_out14, align 8, !dbg !1921
  %incdec.ptr = getelementptr inbounds i8, i8* %24, i32 1, !dbg !1921
  store i8* %incdec.ptr, i8** %next_out14, align 8, !dbg !1921
  %25 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1922
  %strm15 = getelementptr inbounds %struct.DState, %struct.DState* %25, i32 0, i32 0, !dbg !1923
  %26 = load %struct.bz_stream*, %struct.bz_stream** %strm15, align 8, !dbg !1923
  %avail_out16 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %26, i32 0, i32 5, !dbg !1924
  %27 = load i32, i32* %avail_out16, align 8, !dbg !1925
  %dec17 = add i32 %27, -1, !dbg !1925
  store i32 %dec17, i32* %avail_out16, align 8, !dbg !1925
  %28 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1926
  %strm18 = getelementptr inbounds %struct.DState, %struct.DState* %28, i32 0, i32 0, !dbg !1927
  %29 = load %struct.bz_stream*, %struct.bz_stream** %strm18, align 8, !dbg !1927
  %total_out_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %29, i32 0, i32 6, !dbg !1928
  %30 = load i32, i32* %total_out_lo32, align 4, !dbg !1929
  %inc = add i32 %30, 1, !dbg !1929
  store i32 %inc, i32* %total_out_lo32, align 4, !dbg !1929
  %31 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1930
  %strm19 = getelementptr inbounds %struct.DState, %struct.DState* %31, i32 0, i32 0, !dbg !1932
  %32 = load %struct.bz_stream*, %struct.bz_stream** %strm19, align 8, !dbg !1932
  %total_out_lo3220 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %32, i32 0, i32 6, !dbg !1933
  %33 = load i32, i32* %total_out_lo3220, align 4, !dbg !1933
  %cmp21 = icmp eq i32 %33, 0, !dbg !1934
  br i1 %cmp21, label %if.then23, label %if.end26, !dbg !1935

if.then23:                                        ; preds = %if.end6
  %34 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1936
  %strm24 = getelementptr inbounds %struct.DState, %struct.DState* %34, i32 0, i32 0, !dbg !1938
  %35 = load %struct.bz_stream*, %struct.bz_stream** %strm24, align 8, !dbg !1938
  %total_out_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %35, i32 0, i32 7, !dbg !1939
  %36 = load i32, i32* %total_out_hi32, align 8, !dbg !1940
  %inc25 = add i32 %36, 1, !dbg !1940
  store i32 %inc25, i32* %total_out_hi32, align 8, !dbg !1940
  br label %if.end26, !dbg !1936

if.end26:                                         ; preds = %if.then23, %if.end6
  br label %while.body2, !dbg !1941

while.end:                                        ; preds = %if.then5
  %37 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1943
  %nblock_used = getelementptr inbounds %struct.DState, %struct.DState* %37, i32 0, i32 17, !dbg !1945
  %38 = load i32, i32* %nblock_used, align 4, !dbg !1945
  %39 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1946
  %save_nblock = getelementptr inbounds %struct.DState, %struct.DState* %39, i32 0, i32 51, !dbg !1947
  %40 = load i32, i32* %save_nblock, align 8, !dbg !1947
  %add = add nsw i32 %40, 1, !dbg !1948
  %cmp27 = icmp eq i32 %38, %add, !dbg !1949
  br i1 %cmp27, label %if.then29, label %if.end30, !dbg !1950

if.then29:                                        ; preds = %while.end
  store i8 0, i8* %retval, align 1, !dbg !1951
  br label %return, !dbg !1951

if.end30:                                         ; preds = %while.end
  %41 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1953
  %nblock_used31 = getelementptr inbounds %struct.DState, %struct.DState* %41, i32 0, i32 17, !dbg !1955
  %42 = load i32, i32* %nblock_used31, align 4, !dbg !1955
  %43 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1956
  %save_nblock32 = getelementptr inbounds %struct.DState, %struct.DState* %43, i32 0, i32 51, !dbg !1957
  %44 = load i32, i32* %save_nblock32, align 8, !dbg !1957
  %add33 = add nsw i32 %44, 1, !dbg !1958
  %cmp34 = icmp sgt i32 %42, %add33, !dbg !1959
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !1960

if.then36:                                        ; preds = %if.end30
  store i8 1, i8* %retval, align 1, !dbg !1961
  br label %return, !dbg !1961

if.end37:                                         ; preds = %if.end30
  %45 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1962
  %state_out_len38 = getelementptr inbounds %struct.DState, %struct.DState* %45, i32 0, i32 3, !dbg !1963
  store i32 1, i32* %state_out_len38, align 8, !dbg !1964
  %46 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1965
  %k0 = getelementptr inbounds %struct.DState, %struct.DState* %46, i32 0, i32 15, !dbg !1966
  %47 = load i32, i32* %k0, align 8, !dbg !1966
  %conv39 = trunc i32 %47 to i8, !dbg !1965
  %48 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1967
  %state_out_ch40 = getelementptr inbounds %struct.DState, %struct.DState* %48, i32 0, i32 2, !dbg !1968
  store i8 %conv39, i8* %state_out_ch40, align 4, !dbg !1969
  %49 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1970
  %tPos = getelementptr inbounds %struct.DState, %struct.DState* %49, i32 0, i32 14, !dbg !1970
  %50 = load i32, i32* %tPos, align 4, !dbg !1970
  %51 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1970
  %blockSize100k = getelementptr inbounds %struct.DState, %struct.DState* %51, i32 0, i32 9, !dbg !1970
  %52 = load i32, i32* %blockSize100k, align 8, !dbg !1970
  %mul = mul i32 100000, %52, !dbg !1970
  %cmp41 = icmp uge i32 %50, %mul, !dbg !1970
  br i1 %cmp41, label %if.then43, label %if.end44, !dbg !1972

if.then43:                                        ; preds = %if.end37
  store i8 1, i8* %retval, align 1, !dbg !1973
  br label %return, !dbg !1973

if.end44:                                         ; preds = %if.end37
  %53 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1975
  %tPos45 = getelementptr inbounds %struct.DState, %struct.DState* %53, i32 0, i32 14, !dbg !1975
  %54 = load i32, i32* %tPos45, align 4, !dbg !1975
  %idxprom46 = zext i32 %54 to i64, !dbg !1975
  %55 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1975
  %tt = getelementptr inbounds %struct.DState, %struct.DState* %55, i32 0, i32 20, !dbg !1975
  %56 = load i32*, i32** %tt, align 8, !dbg !1975
  %arrayidx47 = getelementptr inbounds i32, i32* %56, i64 %idxprom46, !dbg !1975
  %57 = load i32, i32* %arrayidx47, align 4, !dbg !1975
  %58 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1975
  %tPos48 = getelementptr inbounds %struct.DState, %struct.DState* %58, i32 0, i32 14, !dbg !1975
  store i32 %57, i32* %tPos48, align 4, !dbg !1975
  %59 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1975
  %tPos49 = getelementptr inbounds %struct.DState, %struct.DState* %59, i32 0, i32 14, !dbg !1975
  %60 = load i32, i32* %tPos49, align 4, !dbg !1975
  %and = and i32 %60, 255, !dbg !1975
  %conv50 = trunc i32 %and to i8, !dbg !1975
  store i8 %conv50, i8* %k1, align 1, !dbg !1975
  %61 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1975
  %tPos51 = getelementptr inbounds %struct.DState, %struct.DState* %61, i32 0, i32 14, !dbg !1975
  %62 = load i32, i32* %tPos51, align 4, !dbg !1975
  %shr52 = lshr i32 %62, 8, !dbg !1975
  store i32 %shr52, i32* %tPos51, align 4, !dbg !1975
  %63 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1977
  %rNToGo = getelementptr inbounds %struct.DState, %struct.DState* %63, i32 0, i32 5, !dbg !1977
  %64 = load i32, i32* %rNToGo, align 8, !dbg !1977
  %cmp53 = icmp eq i32 %64, 0, !dbg !1977
  br i1 %cmp53, label %if.then55, label %if.end67, !dbg !1977

if.then55:                                        ; preds = %if.end44
  %65 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1978
  %rTPos = getelementptr inbounds %struct.DState, %struct.DState* %65, i32 0, i32 6, !dbg !1978
  %66 = load i32, i32* %rTPos, align 4, !dbg !1978
  %idxprom56 = sext i32 %66 to i64, !dbg !1978
  %arrayidx57 = getelementptr inbounds [512 x i32], [512 x i32]* @BZ2_rNums, i64 0, i64 %idxprom56, !dbg !1978
  %67 = load i32, i32* %arrayidx57, align 4, !dbg !1978
  %68 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1978
  %rNToGo58 = getelementptr inbounds %struct.DState, %struct.DState* %68, i32 0, i32 5, !dbg !1978
  store i32 %67, i32* %rNToGo58, align 8, !dbg !1978
  %69 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1978
  %rTPos59 = getelementptr inbounds %struct.DState, %struct.DState* %69, i32 0, i32 6, !dbg !1978
  %70 = load i32, i32* %rTPos59, align 4, !dbg !1978
  %inc60 = add nsw i32 %70, 1, !dbg !1978
  store i32 %inc60, i32* %rTPos59, align 4, !dbg !1978
  %71 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1978
  %rTPos61 = getelementptr inbounds %struct.DState, %struct.DState* %71, i32 0, i32 6, !dbg !1978
  %72 = load i32, i32* %rTPos61, align 4, !dbg !1978
  %cmp62 = icmp eq i32 %72, 512, !dbg !1978
  br i1 %cmp62, label %if.then64, label %if.end66, !dbg !1978

if.then64:                                        ; preds = %if.then55
  %73 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1982
  %rTPos65 = getelementptr inbounds %struct.DState, %struct.DState* %73, i32 0, i32 6, !dbg !1982
  store i32 0, i32* %rTPos65, align 4, !dbg !1982
  br label %if.end66, !dbg !1982

if.end66:                                         ; preds = %if.then64, %if.then55
  br label %if.end67, !dbg !1985

if.end67:                                         ; preds = %if.end66, %if.end44
  %74 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1987
  %rNToGo68 = getelementptr inbounds %struct.DState, %struct.DState* %74, i32 0, i32 5, !dbg !1987
  %75 = load i32, i32* %rNToGo68, align 8, !dbg !1987
  %dec69 = add nsw i32 %75, -1, !dbg !1987
  store i32 %dec69, i32* %rNToGo68, align 8, !dbg !1987
  %76 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1989
  %rNToGo70 = getelementptr inbounds %struct.DState, %struct.DState* %76, i32 0, i32 5, !dbg !1989
  %77 = load i32, i32* %rNToGo70, align 8, !dbg !1989
  %cmp71 = icmp eq i32 %77, 1, !dbg !1989
  %cond = select i1 %cmp71, i32 1, i32 0, !dbg !1989
  %78 = load i8, i8* %k1, align 1, !dbg !1990
  %conv73 = zext i8 %78 to i32, !dbg !1990
  %xor74 = xor i32 %conv73, %cond, !dbg !1990
  %conv75 = trunc i32 %xor74 to i8, !dbg !1990
  store i8 %conv75, i8* %k1, align 1, !dbg !1990
  %79 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1991
  %nblock_used76 = getelementptr inbounds %struct.DState, %struct.DState* %79, i32 0, i32 17, !dbg !1992
  %80 = load i32, i32* %nblock_used76, align 4, !dbg !1993
  %inc77 = add nsw i32 %80, 1, !dbg !1993
  store i32 %inc77, i32* %nblock_used76, align 4, !dbg !1993
  %81 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1994
  %nblock_used78 = getelementptr inbounds %struct.DState, %struct.DState* %81, i32 0, i32 17, !dbg !1996
  %82 = load i32, i32* %nblock_used78, align 4, !dbg !1996
  %83 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !1997
  %save_nblock79 = getelementptr inbounds %struct.DState, %struct.DState* %83, i32 0, i32 51, !dbg !1998
  %84 = load i32, i32* %save_nblock79, align 8, !dbg !1998
  %add80 = add nsw i32 %84, 1, !dbg !1999
  %cmp81 = icmp eq i32 %82, %add80, !dbg !2000
  br i1 %cmp81, label %if.then83, label %if.end84, !dbg !2001

if.then83:                                        ; preds = %if.end67
  br label %while.body, !dbg !2002

if.end84:                                         ; preds = %if.end67
  %85 = load i8, i8* %k1, align 1, !dbg !2004
  %conv85 = zext i8 %85 to i32, !dbg !2004
  %86 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2006
  %k086 = getelementptr inbounds %struct.DState, %struct.DState* %86, i32 0, i32 15, !dbg !2007
  %87 = load i32, i32* %k086, align 8, !dbg !2007
  %cmp87 = icmp ne i32 %conv85, %87, !dbg !2008
  br i1 %cmp87, label %if.then89, label %if.end92, !dbg !2009

if.then89:                                        ; preds = %if.end84
  %88 = load i8, i8* %k1, align 1, !dbg !2010
  %conv90 = zext i8 %88 to i32, !dbg !2010
  %89 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2013
  %k091 = getelementptr inbounds %struct.DState, %struct.DState* %89, i32 0, i32 15, !dbg !2014
  store i32 %conv90, i32* %k091, align 8, !dbg !2015
  br label %while.body, !dbg !2016

if.end92:                                         ; preds = %if.end84
  %90 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2017
  %state_out_len93 = getelementptr inbounds %struct.DState, %struct.DState* %90, i32 0, i32 3, !dbg !2018
  store i32 2, i32* %state_out_len93, align 8, !dbg !2019
  %91 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2020
  %tPos94 = getelementptr inbounds %struct.DState, %struct.DState* %91, i32 0, i32 14, !dbg !2020
  %92 = load i32, i32* %tPos94, align 4, !dbg !2020
  %93 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2020
  %blockSize100k95 = getelementptr inbounds %struct.DState, %struct.DState* %93, i32 0, i32 9, !dbg !2020
  %94 = load i32, i32* %blockSize100k95, align 8, !dbg !2020
  %mul96 = mul i32 100000, %94, !dbg !2020
  %cmp97 = icmp uge i32 %92, %mul96, !dbg !2020
  br i1 %cmp97, label %if.then99, label %if.end100, !dbg !2022

if.then99:                                        ; preds = %if.end92
  store i8 1, i8* %retval, align 1, !dbg !2023
  br label %return, !dbg !2023

if.end100:                                        ; preds = %if.end92
  %95 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2025
  %tPos101 = getelementptr inbounds %struct.DState, %struct.DState* %95, i32 0, i32 14, !dbg !2025
  %96 = load i32, i32* %tPos101, align 4, !dbg !2025
  %idxprom102 = zext i32 %96 to i64, !dbg !2025
  %97 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2025
  %tt103 = getelementptr inbounds %struct.DState, %struct.DState* %97, i32 0, i32 20, !dbg !2025
  %98 = load i32*, i32** %tt103, align 8, !dbg !2025
  %arrayidx104 = getelementptr inbounds i32, i32* %98, i64 %idxprom102, !dbg !2025
  %99 = load i32, i32* %arrayidx104, align 4, !dbg !2025
  %100 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2025
  %tPos105 = getelementptr inbounds %struct.DState, %struct.DState* %100, i32 0, i32 14, !dbg !2025
  store i32 %99, i32* %tPos105, align 4, !dbg !2025
  %101 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2025
  %tPos106 = getelementptr inbounds %struct.DState, %struct.DState* %101, i32 0, i32 14, !dbg !2025
  %102 = load i32, i32* %tPos106, align 4, !dbg !2025
  %and107 = and i32 %102, 255, !dbg !2025
  %conv108 = trunc i32 %and107 to i8, !dbg !2025
  store i8 %conv108, i8* %k1, align 1, !dbg !2025
  %103 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2025
  %tPos109 = getelementptr inbounds %struct.DState, %struct.DState* %103, i32 0, i32 14, !dbg !2025
  %104 = load i32, i32* %tPos109, align 4, !dbg !2025
  %shr110 = lshr i32 %104, 8, !dbg !2025
  store i32 %shr110, i32* %tPos109, align 4, !dbg !2025
  %105 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2026
  %rNToGo111 = getelementptr inbounds %struct.DState, %struct.DState* %105, i32 0, i32 5, !dbg !2026
  %106 = load i32, i32* %rNToGo111, align 8, !dbg !2026
  %cmp112 = icmp eq i32 %106, 0, !dbg !2026
  br i1 %cmp112, label %if.then114, label %if.end127, !dbg !2026

if.then114:                                       ; preds = %if.end100
  %107 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2027
  %rTPos115 = getelementptr inbounds %struct.DState, %struct.DState* %107, i32 0, i32 6, !dbg !2027
  %108 = load i32, i32* %rTPos115, align 4, !dbg !2027
  %idxprom116 = sext i32 %108 to i64, !dbg !2027
  %arrayidx117 = getelementptr inbounds [512 x i32], [512 x i32]* @BZ2_rNums, i64 0, i64 %idxprom116, !dbg !2027
  %109 = load i32, i32* %arrayidx117, align 4, !dbg !2027
  %110 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2027
  %rNToGo118 = getelementptr inbounds %struct.DState, %struct.DState* %110, i32 0, i32 5, !dbg !2027
  store i32 %109, i32* %rNToGo118, align 8, !dbg !2027
  %111 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2027
  %rTPos119 = getelementptr inbounds %struct.DState, %struct.DState* %111, i32 0, i32 6, !dbg !2027
  %112 = load i32, i32* %rTPos119, align 4, !dbg !2027
  %inc120 = add nsw i32 %112, 1, !dbg !2027
  store i32 %inc120, i32* %rTPos119, align 4, !dbg !2027
  %113 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2027
  %rTPos121 = getelementptr inbounds %struct.DState, %struct.DState* %113, i32 0, i32 6, !dbg !2027
  %114 = load i32, i32* %rTPos121, align 4, !dbg !2027
  %cmp122 = icmp eq i32 %114, 512, !dbg !2027
  br i1 %cmp122, label %if.then124, label %if.end126, !dbg !2027

if.then124:                                       ; preds = %if.then114
  %115 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2031
  %rTPos125 = getelementptr inbounds %struct.DState, %struct.DState* %115, i32 0, i32 6, !dbg !2031
  store i32 0, i32* %rTPos125, align 4, !dbg !2031
  br label %if.end126, !dbg !2031

if.end126:                                        ; preds = %if.then124, %if.then114
  br label %if.end127, !dbg !2034

if.end127:                                        ; preds = %if.end126, %if.end100
  %116 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2036
  %rNToGo128 = getelementptr inbounds %struct.DState, %struct.DState* %116, i32 0, i32 5, !dbg !2036
  %117 = load i32, i32* %rNToGo128, align 8, !dbg !2036
  %dec129 = add nsw i32 %117, -1, !dbg !2036
  store i32 %dec129, i32* %rNToGo128, align 8, !dbg !2036
  %118 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2037
  %rNToGo130 = getelementptr inbounds %struct.DState, %struct.DState* %118, i32 0, i32 5, !dbg !2037
  %119 = load i32, i32* %rNToGo130, align 8, !dbg !2037
  %cmp131 = icmp eq i32 %119, 1, !dbg !2037
  %cond133 = select i1 %cmp131, i32 1, i32 0, !dbg !2037
  %120 = load i8, i8* %k1, align 1, !dbg !2038
  %conv134 = zext i8 %120 to i32, !dbg !2038
  %xor135 = xor i32 %conv134, %cond133, !dbg !2038
  %conv136 = trunc i32 %xor135 to i8, !dbg !2038
  store i8 %conv136, i8* %k1, align 1, !dbg !2038
  %121 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2039
  %nblock_used137 = getelementptr inbounds %struct.DState, %struct.DState* %121, i32 0, i32 17, !dbg !2040
  %122 = load i32, i32* %nblock_used137, align 4, !dbg !2041
  %inc138 = add nsw i32 %122, 1, !dbg !2041
  store i32 %inc138, i32* %nblock_used137, align 4, !dbg !2041
  %123 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2042
  %nblock_used139 = getelementptr inbounds %struct.DState, %struct.DState* %123, i32 0, i32 17, !dbg !2044
  %124 = load i32, i32* %nblock_used139, align 4, !dbg !2044
  %125 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2045
  %save_nblock140 = getelementptr inbounds %struct.DState, %struct.DState* %125, i32 0, i32 51, !dbg !2046
  %126 = load i32, i32* %save_nblock140, align 8, !dbg !2046
  %add141 = add nsw i32 %126, 1, !dbg !2047
  %cmp142 = icmp eq i32 %124, %add141, !dbg !2048
  br i1 %cmp142, label %if.then144, label %if.end145, !dbg !2049

if.then144:                                       ; preds = %if.end127
  br label %while.body, !dbg !2050

if.end145:                                        ; preds = %if.end127
  %127 = load i8, i8* %k1, align 1, !dbg !2052
  %conv146 = zext i8 %127 to i32, !dbg !2052
  %128 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2054
  %k0147 = getelementptr inbounds %struct.DState, %struct.DState* %128, i32 0, i32 15, !dbg !2055
  %129 = load i32, i32* %k0147, align 8, !dbg !2055
  %cmp148 = icmp ne i32 %conv146, %129, !dbg !2056
  br i1 %cmp148, label %if.then150, label %if.end153, !dbg !2057

if.then150:                                       ; preds = %if.end145
  %130 = load i8, i8* %k1, align 1, !dbg !2058
  %conv151 = zext i8 %130 to i32, !dbg !2058
  %131 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2061
  %k0152 = getelementptr inbounds %struct.DState, %struct.DState* %131, i32 0, i32 15, !dbg !2062
  store i32 %conv151, i32* %k0152, align 8, !dbg !2063
  br label %while.body, !dbg !2064

if.end153:                                        ; preds = %if.end145
  %132 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2065
  %state_out_len154 = getelementptr inbounds %struct.DState, %struct.DState* %132, i32 0, i32 3, !dbg !2066
  store i32 3, i32* %state_out_len154, align 8, !dbg !2067
  %133 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2068
  %tPos155 = getelementptr inbounds %struct.DState, %struct.DState* %133, i32 0, i32 14, !dbg !2068
  %134 = load i32, i32* %tPos155, align 4, !dbg !2068
  %135 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2068
  %blockSize100k156 = getelementptr inbounds %struct.DState, %struct.DState* %135, i32 0, i32 9, !dbg !2068
  %136 = load i32, i32* %blockSize100k156, align 8, !dbg !2068
  %mul157 = mul i32 100000, %136, !dbg !2068
  %cmp158 = icmp uge i32 %134, %mul157, !dbg !2068
  br i1 %cmp158, label %if.then160, label %if.end161, !dbg !2070

if.then160:                                       ; preds = %if.end153
  store i8 1, i8* %retval, align 1, !dbg !2071
  br label %return, !dbg !2071

if.end161:                                        ; preds = %if.end153
  %137 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2073
  %tPos162 = getelementptr inbounds %struct.DState, %struct.DState* %137, i32 0, i32 14, !dbg !2073
  %138 = load i32, i32* %tPos162, align 4, !dbg !2073
  %idxprom163 = zext i32 %138 to i64, !dbg !2073
  %139 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2073
  %tt164 = getelementptr inbounds %struct.DState, %struct.DState* %139, i32 0, i32 20, !dbg !2073
  %140 = load i32*, i32** %tt164, align 8, !dbg !2073
  %arrayidx165 = getelementptr inbounds i32, i32* %140, i64 %idxprom163, !dbg !2073
  %141 = load i32, i32* %arrayidx165, align 4, !dbg !2073
  %142 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2073
  %tPos166 = getelementptr inbounds %struct.DState, %struct.DState* %142, i32 0, i32 14, !dbg !2073
  store i32 %141, i32* %tPos166, align 4, !dbg !2073
  %143 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2073
  %tPos167 = getelementptr inbounds %struct.DState, %struct.DState* %143, i32 0, i32 14, !dbg !2073
  %144 = load i32, i32* %tPos167, align 4, !dbg !2073
  %and168 = and i32 %144, 255, !dbg !2073
  %conv169 = trunc i32 %and168 to i8, !dbg !2073
  store i8 %conv169, i8* %k1, align 1, !dbg !2073
  %145 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2073
  %tPos170 = getelementptr inbounds %struct.DState, %struct.DState* %145, i32 0, i32 14, !dbg !2073
  %146 = load i32, i32* %tPos170, align 4, !dbg !2073
  %shr171 = lshr i32 %146, 8, !dbg !2073
  store i32 %shr171, i32* %tPos170, align 4, !dbg !2073
  %147 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2074
  %rNToGo172 = getelementptr inbounds %struct.DState, %struct.DState* %147, i32 0, i32 5, !dbg !2074
  %148 = load i32, i32* %rNToGo172, align 8, !dbg !2074
  %cmp173 = icmp eq i32 %148, 0, !dbg !2074
  br i1 %cmp173, label %if.then175, label %if.end188, !dbg !2074

if.then175:                                       ; preds = %if.end161
  %149 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2075
  %rTPos176 = getelementptr inbounds %struct.DState, %struct.DState* %149, i32 0, i32 6, !dbg !2075
  %150 = load i32, i32* %rTPos176, align 4, !dbg !2075
  %idxprom177 = sext i32 %150 to i64, !dbg !2075
  %arrayidx178 = getelementptr inbounds [512 x i32], [512 x i32]* @BZ2_rNums, i64 0, i64 %idxprom177, !dbg !2075
  %151 = load i32, i32* %arrayidx178, align 4, !dbg !2075
  %152 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2075
  %rNToGo179 = getelementptr inbounds %struct.DState, %struct.DState* %152, i32 0, i32 5, !dbg !2075
  store i32 %151, i32* %rNToGo179, align 8, !dbg !2075
  %153 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2075
  %rTPos180 = getelementptr inbounds %struct.DState, %struct.DState* %153, i32 0, i32 6, !dbg !2075
  %154 = load i32, i32* %rTPos180, align 4, !dbg !2075
  %inc181 = add nsw i32 %154, 1, !dbg !2075
  store i32 %inc181, i32* %rTPos180, align 4, !dbg !2075
  %155 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2075
  %rTPos182 = getelementptr inbounds %struct.DState, %struct.DState* %155, i32 0, i32 6, !dbg !2075
  %156 = load i32, i32* %rTPos182, align 4, !dbg !2075
  %cmp183 = icmp eq i32 %156, 512, !dbg !2075
  br i1 %cmp183, label %if.then185, label %if.end187, !dbg !2075

if.then185:                                       ; preds = %if.then175
  %157 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2079
  %rTPos186 = getelementptr inbounds %struct.DState, %struct.DState* %157, i32 0, i32 6, !dbg !2079
  store i32 0, i32* %rTPos186, align 4, !dbg !2079
  br label %if.end187, !dbg !2079

if.end187:                                        ; preds = %if.then185, %if.then175
  br label %if.end188, !dbg !2082

if.end188:                                        ; preds = %if.end187, %if.end161
  %158 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2084
  %rNToGo189 = getelementptr inbounds %struct.DState, %struct.DState* %158, i32 0, i32 5, !dbg !2084
  %159 = load i32, i32* %rNToGo189, align 8, !dbg !2084
  %dec190 = add nsw i32 %159, -1, !dbg !2084
  store i32 %dec190, i32* %rNToGo189, align 8, !dbg !2084
  %160 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2085
  %rNToGo191 = getelementptr inbounds %struct.DState, %struct.DState* %160, i32 0, i32 5, !dbg !2085
  %161 = load i32, i32* %rNToGo191, align 8, !dbg !2085
  %cmp192 = icmp eq i32 %161, 1, !dbg !2085
  %cond194 = select i1 %cmp192, i32 1, i32 0, !dbg !2085
  %162 = load i8, i8* %k1, align 1, !dbg !2086
  %conv195 = zext i8 %162 to i32, !dbg !2086
  %xor196 = xor i32 %conv195, %cond194, !dbg !2086
  %conv197 = trunc i32 %xor196 to i8, !dbg !2086
  store i8 %conv197, i8* %k1, align 1, !dbg !2086
  %163 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2087
  %nblock_used198 = getelementptr inbounds %struct.DState, %struct.DState* %163, i32 0, i32 17, !dbg !2088
  %164 = load i32, i32* %nblock_used198, align 4, !dbg !2089
  %inc199 = add nsw i32 %164, 1, !dbg !2089
  store i32 %inc199, i32* %nblock_used198, align 4, !dbg !2089
  %165 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2090
  %nblock_used200 = getelementptr inbounds %struct.DState, %struct.DState* %165, i32 0, i32 17, !dbg !2092
  %166 = load i32, i32* %nblock_used200, align 4, !dbg !2092
  %167 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2093
  %save_nblock201 = getelementptr inbounds %struct.DState, %struct.DState* %167, i32 0, i32 51, !dbg !2094
  %168 = load i32, i32* %save_nblock201, align 8, !dbg !2094
  %add202 = add nsw i32 %168, 1, !dbg !2095
  %cmp203 = icmp eq i32 %166, %add202, !dbg !2096
  br i1 %cmp203, label %if.then205, label %if.end206, !dbg !2097

if.then205:                                       ; preds = %if.end188
  br label %while.body, !dbg !2098

if.end206:                                        ; preds = %if.end188
  %169 = load i8, i8* %k1, align 1, !dbg !2100
  %conv207 = zext i8 %169 to i32, !dbg !2100
  %170 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2102
  %k0208 = getelementptr inbounds %struct.DState, %struct.DState* %170, i32 0, i32 15, !dbg !2103
  %171 = load i32, i32* %k0208, align 8, !dbg !2103
  %cmp209 = icmp ne i32 %conv207, %171, !dbg !2104
  br i1 %cmp209, label %if.then211, label %if.end214, !dbg !2105

if.then211:                                       ; preds = %if.end206
  %172 = load i8, i8* %k1, align 1, !dbg !2106
  %conv212 = zext i8 %172 to i32, !dbg !2106
  %173 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2109
  %k0213 = getelementptr inbounds %struct.DState, %struct.DState* %173, i32 0, i32 15, !dbg !2110
  store i32 %conv212, i32* %k0213, align 8, !dbg !2111
  br label %while.body, !dbg !2112

if.end214:                                        ; preds = %if.end206
  %174 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2113
  %tPos215 = getelementptr inbounds %struct.DState, %struct.DState* %174, i32 0, i32 14, !dbg !2113
  %175 = load i32, i32* %tPos215, align 4, !dbg !2113
  %176 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2113
  %blockSize100k216 = getelementptr inbounds %struct.DState, %struct.DState* %176, i32 0, i32 9, !dbg !2113
  %177 = load i32, i32* %blockSize100k216, align 8, !dbg !2113
  %mul217 = mul i32 100000, %177, !dbg !2113
  %cmp218 = icmp uge i32 %175, %mul217, !dbg !2113
  br i1 %cmp218, label %if.then220, label %if.end221, !dbg !2115

if.then220:                                       ; preds = %if.end214
  store i8 1, i8* %retval, align 1, !dbg !2116
  br label %return, !dbg !2116

if.end221:                                        ; preds = %if.end214
  %178 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2118
  %tPos222 = getelementptr inbounds %struct.DState, %struct.DState* %178, i32 0, i32 14, !dbg !2118
  %179 = load i32, i32* %tPos222, align 4, !dbg !2118
  %idxprom223 = zext i32 %179 to i64, !dbg !2118
  %180 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2118
  %tt224 = getelementptr inbounds %struct.DState, %struct.DState* %180, i32 0, i32 20, !dbg !2118
  %181 = load i32*, i32** %tt224, align 8, !dbg !2118
  %arrayidx225 = getelementptr inbounds i32, i32* %181, i64 %idxprom223, !dbg !2118
  %182 = load i32, i32* %arrayidx225, align 4, !dbg !2118
  %183 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2118
  %tPos226 = getelementptr inbounds %struct.DState, %struct.DState* %183, i32 0, i32 14, !dbg !2118
  store i32 %182, i32* %tPos226, align 4, !dbg !2118
  %184 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2118
  %tPos227 = getelementptr inbounds %struct.DState, %struct.DState* %184, i32 0, i32 14, !dbg !2118
  %185 = load i32, i32* %tPos227, align 4, !dbg !2118
  %and228 = and i32 %185, 255, !dbg !2118
  %conv229 = trunc i32 %and228 to i8, !dbg !2118
  store i8 %conv229, i8* %k1, align 1, !dbg !2118
  %186 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2118
  %tPos230 = getelementptr inbounds %struct.DState, %struct.DState* %186, i32 0, i32 14, !dbg !2118
  %187 = load i32, i32* %tPos230, align 4, !dbg !2118
  %shr231 = lshr i32 %187, 8, !dbg !2118
  store i32 %shr231, i32* %tPos230, align 4, !dbg !2118
  %188 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2119
  %rNToGo232 = getelementptr inbounds %struct.DState, %struct.DState* %188, i32 0, i32 5, !dbg !2119
  %189 = load i32, i32* %rNToGo232, align 8, !dbg !2119
  %cmp233 = icmp eq i32 %189, 0, !dbg !2119
  br i1 %cmp233, label %if.then235, label %if.end248, !dbg !2119

if.then235:                                       ; preds = %if.end221
  %190 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2120
  %rTPos236 = getelementptr inbounds %struct.DState, %struct.DState* %190, i32 0, i32 6, !dbg !2120
  %191 = load i32, i32* %rTPos236, align 4, !dbg !2120
  %idxprom237 = sext i32 %191 to i64, !dbg !2120
  %arrayidx238 = getelementptr inbounds [512 x i32], [512 x i32]* @BZ2_rNums, i64 0, i64 %idxprom237, !dbg !2120
  %192 = load i32, i32* %arrayidx238, align 4, !dbg !2120
  %193 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2120
  %rNToGo239 = getelementptr inbounds %struct.DState, %struct.DState* %193, i32 0, i32 5, !dbg !2120
  store i32 %192, i32* %rNToGo239, align 8, !dbg !2120
  %194 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2120
  %rTPos240 = getelementptr inbounds %struct.DState, %struct.DState* %194, i32 0, i32 6, !dbg !2120
  %195 = load i32, i32* %rTPos240, align 4, !dbg !2120
  %inc241 = add nsw i32 %195, 1, !dbg !2120
  store i32 %inc241, i32* %rTPos240, align 4, !dbg !2120
  %196 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2120
  %rTPos242 = getelementptr inbounds %struct.DState, %struct.DState* %196, i32 0, i32 6, !dbg !2120
  %197 = load i32, i32* %rTPos242, align 4, !dbg !2120
  %cmp243 = icmp eq i32 %197, 512, !dbg !2120
  br i1 %cmp243, label %if.then245, label %if.end247, !dbg !2120

if.then245:                                       ; preds = %if.then235
  %198 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2124
  %rTPos246 = getelementptr inbounds %struct.DState, %struct.DState* %198, i32 0, i32 6, !dbg !2124
  store i32 0, i32* %rTPos246, align 4, !dbg !2124
  br label %if.end247, !dbg !2124

if.end247:                                        ; preds = %if.then245, %if.then235
  br label %if.end248, !dbg !2127

if.end248:                                        ; preds = %if.end247, %if.end221
  %199 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2129
  %rNToGo249 = getelementptr inbounds %struct.DState, %struct.DState* %199, i32 0, i32 5, !dbg !2129
  %200 = load i32, i32* %rNToGo249, align 8, !dbg !2129
  %dec250 = add nsw i32 %200, -1, !dbg !2129
  store i32 %dec250, i32* %rNToGo249, align 8, !dbg !2129
  %201 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2130
  %rNToGo251 = getelementptr inbounds %struct.DState, %struct.DState* %201, i32 0, i32 5, !dbg !2130
  %202 = load i32, i32* %rNToGo251, align 8, !dbg !2130
  %cmp252 = icmp eq i32 %202, 1, !dbg !2130
  %cond254 = select i1 %cmp252, i32 1, i32 0, !dbg !2130
  %203 = load i8, i8* %k1, align 1, !dbg !2131
  %conv255 = zext i8 %203 to i32, !dbg !2131
  %xor256 = xor i32 %conv255, %cond254, !dbg !2131
  %conv257 = trunc i32 %xor256 to i8, !dbg !2131
  store i8 %conv257, i8* %k1, align 1, !dbg !2131
  %204 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2132
  %nblock_used258 = getelementptr inbounds %struct.DState, %struct.DState* %204, i32 0, i32 17, !dbg !2133
  %205 = load i32, i32* %nblock_used258, align 4, !dbg !2134
  %inc259 = add nsw i32 %205, 1, !dbg !2134
  store i32 %inc259, i32* %nblock_used258, align 4, !dbg !2134
  %206 = load i8, i8* %k1, align 1, !dbg !2135
  %conv260 = zext i8 %206 to i32, !dbg !2136
  %add261 = add nsw i32 %conv260, 4, !dbg !2137
  %207 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2138
  %state_out_len262 = getelementptr inbounds %struct.DState, %struct.DState* %207, i32 0, i32 3, !dbg !2139
  store i32 %add261, i32* %state_out_len262, align 8, !dbg !2140
  %208 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2141
  %tPos263 = getelementptr inbounds %struct.DState, %struct.DState* %208, i32 0, i32 14, !dbg !2141
  %209 = load i32, i32* %tPos263, align 4, !dbg !2141
  %210 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2141
  %blockSize100k264 = getelementptr inbounds %struct.DState, %struct.DState* %210, i32 0, i32 9, !dbg !2141
  %211 = load i32, i32* %blockSize100k264, align 8, !dbg !2141
  %mul265 = mul i32 100000, %211, !dbg !2141
  %cmp266 = icmp uge i32 %209, %mul265, !dbg !2141
  br i1 %cmp266, label %if.then268, label %if.end269, !dbg !2143

if.then268:                                       ; preds = %if.end248
  store i8 1, i8* %retval, align 1, !dbg !2144
  br label %return, !dbg !2144

if.end269:                                        ; preds = %if.end248
  %212 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2146
  %tPos270 = getelementptr inbounds %struct.DState, %struct.DState* %212, i32 0, i32 14, !dbg !2146
  %213 = load i32, i32* %tPos270, align 4, !dbg !2146
  %idxprom271 = zext i32 %213 to i64, !dbg !2146
  %214 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2146
  %tt272 = getelementptr inbounds %struct.DState, %struct.DState* %214, i32 0, i32 20, !dbg !2146
  %215 = load i32*, i32** %tt272, align 8, !dbg !2146
  %arrayidx273 = getelementptr inbounds i32, i32* %215, i64 %idxprom271, !dbg !2146
  %216 = load i32, i32* %arrayidx273, align 4, !dbg !2146
  %217 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2146
  %tPos274 = getelementptr inbounds %struct.DState, %struct.DState* %217, i32 0, i32 14, !dbg !2146
  store i32 %216, i32* %tPos274, align 4, !dbg !2146
  %218 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2146
  %tPos275 = getelementptr inbounds %struct.DState, %struct.DState* %218, i32 0, i32 14, !dbg !2146
  %219 = load i32, i32* %tPos275, align 4, !dbg !2146
  %and276 = and i32 %219, 255, !dbg !2146
  %conv277 = trunc i32 %and276 to i8, !dbg !2146
  %conv278 = zext i8 %conv277 to i32, !dbg !2146
  %220 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2146
  %k0279 = getelementptr inbounds %struct.DState, %struct.DState* %220, i32 0, i32 15, !dbg !2146
  store i32 %conv278, i32* %k0279, align 8, !dbg !2146
  %221 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2146
  %tPos280 = getelementptr inbounds %struct.DState, %struct.DState* %221, i32 0, i32 14, !dbg !2146
  %222 = load i32, i32* %tPos280, align 4, !dbg !2146
  %shr281 = lshr i32 %222, 8, !dbg !2146
  store i32 %shr281, i32* %tPos280, align 4, !dbg !2146
  %223 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2147
  %rNToGo282 = getelementptr inbounds %struct.DState, %struct.DState* %223, i32 0, i32 5, !dbg !2147
  %224 = load i32, i32* %rNToGo282, align 8, !dbg !2147
  %cmp283 = icmp eq i32 %224, 0, !dbg !2147
  br i1 %cmp283, label %if.then285, label %if.end298, !dbg !2147

if.then285:                                       ; preds = %if.end269
  %225 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2148
  %rTPos286 = getelementptr inbounds %struct.DState, %struct.DState* %225, i32 0, i32 6, !dbg !2148
  %226 = load i32, i32* %rTPos286, align 4, !dbg !2148
  %idxprom287 = sext i32 %226 to i64, !dbg !2148
  %arrayidx288 = getelementptr inbounds [512 x i32], [512 x i32]* @BZ2_rNums, i64 0, i64 %idxprom287, !dbg !2148
  %227 = load i32, i32* %arrayidx288, align 4, !dbg !2148
  %228 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2148
  %rNToGo289 = getelementptr inbounds %struct.DState, %struct.DState* %228, i32 0, i32 5, !dbg !2148
  store i32 %227, i32* %rNToGo289, align 8, !dbg !2148
  %229 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2148
  %rTPos290 = getelementptr inbounds %struct.DState, %struct.DState* %229, i32 0, i32 6, !dbg !2148
  %230 = load i32, i32* %rTPos290, align 4, !dbg !2148
  %inc291 = add nsw i32 %230, 1, !dbg !2148
  store i32 %inc291, i32* %rTPos290, align 4, !dbg !2148
  %231 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2148
  %rTPos292 = getelementptr inbounds %struct.DState, %struct.DState* %231, i32 0, i32 6, !dbg !2148
  %232 = load i32, i32* %rTPos292, align 4, !dbg !2148
  %cmp293 = icmp eq i32 %232, 512, !dbg !2148
  br i1 %cmp293, label %if.then295, label %if.end297, !dbg !2148

if.then295:                                       ; preds = %if.then285
  %233 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2152
  %rTPos296 = getelementptr inbounds %struct.DState, %struct.DState* %233, i32 0, i32 6, !dbg !2152
  store i32 0, i32* %rTPos296, align 4, !dbg !2152
  br label %if.end297, !dbg !2152

if.end297:                                        ; preds = %if.then295, %if.then285
  br label %if.end298, !dbg !2155

if.end298:                                        ; preds = %if.end297, %if.end269
  %234 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2157
  %rNToGo299 = getelementptr inbounds %struct.DState, %struct.DState* %234, i32 0, i32 5, !dbg !2157
  %235 = load i32, i32* %rNToGo299, align 8, !dbg !2157
  %dec300 = add nsw i32 %235, -1, !dbg !2157
  store i32 %dec300, i32* %rNToGo299, align 8, !dbg !2157
  %236 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2158
  %rNToGo301 = getelementptr inbounds %struct.DState, %struct.DState* %236, i32 0, i32 5, !dbg !2158
  %237 = load i32, i32* %rNToGo301, align 8, !dbg !2158
  %cmp302 = icmp eq i32 %237, 1, !dbg !2158
  %cond304 = select i1 %cmp302, i32 1, i32 0, !dbg !2158
  %238 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2159
  %k0305 = getelementptr inbounds %struct.DState, %struct.DState* %238, i32 0, i32 15, !dbg !2160
  %239 = load i32, i32* %k0305, align 8, !dbg !2161
  %xor306 = xor i32 %239, %cond304, !dbg !2161
  store i32 %xor306, i32* %k0305, align 8, !dbg !2161
  %240 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2162
  %nblock_used307 = getelementptr inbounds %struct.DState, %struct.DState* %240, i32 0, i32 17, !dbg !2163
  %241 = load i32, i32* %nblock_used307, align 4, !dbg !2164
  %inc308 = add nsw i32 %241, 1, !dbg !2164
  store i32 %inc308, i32* %nblock_used307, align 4, !dbg !2164
  br label %while.body, !dbg !2165

if.else:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %c_calculatedBlockCRC, metadata !2167, metadata !392), !dbg !2169
  %242 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2170
  %calculatedBlockCRC309 = getelementptr inbounds %struct.DState, %struct.DState* %242, i32 0, i32 25, !dbg !2171
  %243 = load i32, i32* %calculatedBlockCRC309, align 8, !dbg !2171
  store i32 %243, i32* %c_calculatedBlockCRC, align 4, !dbg !2169
  call void @llvm.dbg.declare(metadata i8* %c_state_out_ch, metadata !2172, metadata !392), !dbg !2173
  %244 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2174
  %state_out_ch310 = getelementptr inbounds %struct.DState, %struct.DState* %244, i32 0, i32 2, !dbg !2175
  %245 = load i8, i8* %state_out_ch310, align 4, !dbg !2175
  store i8 %245, i8* %c_state_out_ch, align 1, !dbg !2173
  call void @llvm.dbg.declare(metadata i32* %c_state_out_len, metadata !2176, metadata !392), !dbg !2177
  %246 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2178
  %state_out_len311 = getelementptr inbounds %struct.DState, %struct.DState* %246, i32 0, i32 3, !dbg !2179
  %247 = load i32, i32* %state_out_len311, align 8, !dbg !2179
  store i32 %247, i32* %c_state_out_len, align 4, !dbg !2177
  call void @llvm.dbg.declare(metadata i32* %c_nblock_used, metadata !2180, metadata !392), !dbg !2181
  %248 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2182
  %nblock_used312 = getelementptr inbounds %struct.DState, %struct.DState* %248, i32 0, i32 17, !dbg !2183
  %249 = load i32, i32* %nblock_used312, align 4, !dbg !2183
  store i32 %249, i32* %c_nblock_used, align 4, !dbg !2181
  call void @llvm.dbg.declare(metadata i32* %c_k0, metadata !2184, metadata !392), !dbg !2185
  %250 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2186
  %k0313 = getelementptr inbounds %struct.DState, %struct.DState* %250, i32 0, i32 15, !dbg !2187
  %251 = load i32, i32* %k0313, align 8, !dbg !2187
  store i32 %251, i32* %c_k0, align 4, !dbg !2185
  call void @llvm.dbg.declare(metadata i32** %c_tt, metadata !2188, metadata !392), !dbg !2189
  %252 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2190
  %tt314 = getelementptr inbounds %struct.DState, %struct.DState* %252, i32 0, i32 20, !dbg !2191
  %253 = load i32*, i32** %tt314, align 8, !dbg !2191
  store i32* %253, i32** %c_tt, align 8, !dbg !2189
  call void @llvm.dbg.declare(metadata i32* %c_tPos, metadata !2192, metadata !392), !dbg !2193
  %254 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2194
  %tPos315 = getelementptr inbounds %struct.DState, %struct.DState* %254, i32 0, i32 14, !dbg !2195
  %255 = load i32, i32* %tPos315, align 4, !dbg !2195
  store i32 %255, i32* %c_tPos, align 4, !dbg !2193
  call void @llvm.dbg.declare(metadata i8** %cs_next_out, metadata !2196, metadata !392), !dbg !2197
  %256 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2198
  %strm316 = getelementptr inbounds %struct.DState, %struct.DState* %256, i32 0, i32 0, !dbg !2199
  %257 = load %struct.bz_stream*, %struct.bz_stream** %strm316, align 8, !dbg !2199
  %next_out317 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %257, i32 0, i32 4, !dbg !2200
  %258 = load i8*, i8** %next_out317, align 8, !dbg !2200
  store i8* %258, i8** %cs_next_out, align 8, !dbg !2197
  call void @llvm.dbg.declare(metadata i32* %cs_avail_out, metadata !2201, metadata !392), !dbg !2202
  %259 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2203
  %strm318 = getelementptr inbounds %struct.DState, %struct.DState* %259, i32 0, i32 0, !dbg !2204
  %260 = load %struct.bz_stream*, %struct.bz_stream** %strm318, align 8, !dbg !2204
  %avail_out319 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %260, i32 0, i32 5, !dbg !2205
  %261 = load i32, i32* %avail_out319, align 8, !dbg !2205
  store i32 %261, i32* %cs_avail_out, align 4, !dbg !2202
  call void @llvm.dbg.declare(metadata i32* %ro_blockSize100k, metadata !2206, metadata !392), !dbg !2207
  %262 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2208
  %blockSize100k320 = getelementptr inbounds %struct.DState, %struct.DState* %262, i32 0, i32 9, !dbg !2209
  %263 = load i32, i32* %blockSize100k320, align 8, !dbg !2209
  store i32 %263, i32* %ro_blockSize100k, align 4, !dbg !2207
  call void @llvm.dbg.declare(metadata i32* %avail_out_INIT, metadata !2210, metadata !392), !dbg !2211
  %264 = load i32, i32* %cs_avail_out, align 4, !dbg !2212
  store i32 %264, i32* %avail_out_INIT, align 4, !dbg !2211
  call void @llvm.dbg.declare(metadata i32* %s_save_nblockPP, metadata !2213, metadata !392), !dbg !2214
  %265 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2215
  %save_nblock321 = getelementptr inbounds %struct.DState, %struct.DState* %265, i32 0, i32 51, !dbg !2216
  %266 = load i32, i32* %save_nblock321, align 8, !dbg !2216
  %add322 = add nsw i32 %266, 1, !dbg !2217
  store i32 %add322, i32* %s_save_nblockPP, align 4, !dbg !2214
  call void @llvm.dbg.declare(metadata i32* %total_out_lo32_old, metadata !2218, metadata !392), !dbg !2219
  br label %while.body323, !dbg !2220

while.body323:                                    ; preds = %if.else, %if.then405, %if.then410, %if.then426, %if.then431, %if.end451
  %267 = load i32, i32* %c_state_out_len, align 4, !dbg !2221
  %cmp324 = icmp sgt i32 %267, 0, !dbg !2224
  br i1 %cmp324, label %if.then326, label %if.end361, !dbg !2225

if.then326:                                       ; preds = %while.body323
  br label %while.body328, !dbg !2226

while.body328:                                    ; preds = %if.then326, %if.end336
  %268 = load i32, i32* %cs_avail_out, align 4, !dbg !2228
  %cmp329 = icmp eq i32 %268, 0, !dbg !2231
  br i1 %cmp329, label %if.then331, label %if.end332, !dbg !2232

if.then331:                                       ; preds = %while.body328
  br label %return_notr, !dbg !2233

if.end332:                                        ; preds = %while.body328
  %269 = load i32, i32* %c_state_out_len, align 4, !dbg !2235
  %cmp333 = icmp eq i32 %269, 1, !dbg !2237
  br i1 %cmp333, label %if.then335, label %if.end336, !dbg !2238

if.then335:                                       ; preds = %if.end332
  br label %while.end347, !dbg !2239

if.end336:                                        ; preds = %if.end332
  %270 = load i8, i8* %c_state_out_ch, align 1, !dbg !2241
  %271 = load i8*, i8** %cs_next_out, align 8, !dbg !2242
  store i8 %270, i8* %271, align 1, !dbg !2243
  %272 = load i32, i32* %c_calculatedBlockCRC, align 4, !dbg !2244
  %shl337 = shl i32 %272, 8, !dbg !2244
  %273 = load i32, i32* %c_calculatedBlockCRC, align 4, !dbg !2244
  %shr338 = lshr i32 %273, 24, !dbg !2244
  %274 = load i8, i8* %c_state_out_ch, align 1, !dbg !2244
  %conv339 = zext i8 %274 to i32, !dbg !2244
  %xor340 = xor i32 %shr338, %conv339, !dbg !2244
  %idxprom341 = zext i32 %xor340 to i64, !dbg !2244
  %arrayidx342 = getelementptr inbounds [256 x i32], [256 x i32]* @BZ2_crc32Table, i64 0, i64 %idxprom341, !dbg !2244
  %275 = load i32, i32* %arrayidx342, align 4, !dbg !2244
  %xor343 = xor i32 %shl337, %275, !dbg !2244
  store i32 %xor343, i32* %c_calculatedBlockCRC, align 4, !dbg !2244
  %276 = load i32, i32* %c_state_out_len, align 4, !dbg !2246
  %dec344 = add nsw i32 %276, -1, !dbg !2246
  store i32 %dec344, i32* %c_state_out_len, align 4, !dbg !2246
  %277 = load i8*, i8** %cs_next_out, align 8, !dbg !2247
  %incdec.ptr345 = getelementptr inbounds i8, i8* %277, i32 1, !dbg !2247
  store i8* %incdec.ptr345, i8** %cs_next_out, align 8, !dbg !2247
  %278 = load i32, i32* %cs_avail_out, align 4, !dbg !2248
  %dec346 = add i32 %278, -1, !dbg !2248
  store i32 %dec346, i32* %cs_avail_out, align 4, !dbg !2248
  br label %while.body328, !dbg !2249

while.end347:                                     ; preds = %if.then335
  br label %s_state_out_len_eq_one, !dbg !2251

s_state_out_len_eq_one:                           ; preds = %if.then390, %if.then385, %while.end347
  %279 = load i32, i32* %cs_avail_out, align 4, !dbg !2253
  %cmp348 = icmp eq i32 %279, 0, !dbg !2256
  br i1 %cmp348, label %if.then350, label %if.end351, !dbg !2257

if.then350:                                       ; preds = %s_state_out_len_eq_one
  store i32 1, i32* %c_state_out_len, align 4, !dbg !2258
  br label %return_notr, !dbg !2260

if.end351:                                        ; preds = %s_state_out_len_eq_one
  %280 = load i8, i8* %c_state_out_ch, align 1, !dbg !2261
  %281 = load i8*, i8** %cs_next_out, align 8, !dbg !2262
  store i8 %280, i8* %281, align 1, !dbg !2263
  %282 = load i32, i32* %c_calculatedBlockCRC, align 4, !dbg !2264
  %shl352 = shl i32 %282, 8, !dbg !2264
  %283 = load i32, i32* %c_calculatedBlockCRC, align 4, !dbg !2264
  %shr353 = lshr i32 %283, 24, !dbg !2264
  %284 = load i8, i8* %c_state_out_ch, align 1, !dbg !2264
  %conv354 = zext i8 %284 to i32, !dbg !2264
  %xor355 = xor i32 %shr353, %conv354, !dbg !2264
  %idxprom356 = zext i32 %xor355 to i64, !dbg !2264
  %arrayidx357 = getelementptr inbounds [256 x i32], [256 x i32]* @BZ2_crc32Table, i64 0, i64 %idxprom356, !dbg !2264
  %285 = load i32, i32* %arrayidx357, align 4, !dbg !2264
  %xor358 = xor i32 %shl352, %285, !dbg !2264
  store i32 %xor358, i32* %c_calculatedBlockCRC, align 4, !dbg !2264
  %286 = load i8*, i8** %cs_next_out, align 8, !dbg !2266
  %incdec.ptr359 = getelementptr inbounds i8, i8* %286, i32 1, !dbg !2266
  store i8* %incdec.ptr359, i8** %cs_next_out, align 8, !dbg !2266
  %287 = load i32, i32* %cs_avail_out, align 4, !dbg !2267
  %dec360 = add i32 %287, -1, !dbg !2267
  store i32 %dec360, i32* %cs_avail_out, align 4, !dbg !2267
  br label %if.end361, !dbg !2268

if.end361:                                        ; preds = %if.end351, %while.body323
  %288 = load i32, i32* %c_nblock_used, align 4, !dbg !2269
  %289 = load i32, i32* %s_save_nblockPP, align 4, !dbg !2271
  %cmp362 = icmp sgt i32 %288, %289, !dbg !2272
  br i1 %cmp362, label %if.then364, label %if.end365, !dbg !2273

if.then364:                                       ; preds = %if.end361
  store i8 1, i8* %retval, align 1, !dbg !2274
  br label %return, !dbg !2274

if.end365:                                        ; preds = %if.end361
  %290 = load i32, i32* %c_nblock_used, align 4, !dbg !2275
  %291 = load i32, i32* %s_save_nblockPP, align 4, !dbg !2277
  %cmp366 = icmp eq i32 %290, %291, !dbg !2278
  br i1 %cmp366, label %if.then368, label %if.end369, !dbg !2279

if.then368:                                       ; preds = %if.end365
  store i32 0, i32* %c_state_out_len, align 4, !dbg !2280
  br label %return_notr, !dbg !2282

if.end369:                                        ; preds = %if.end365
  %292 = load i32, i32* %c_k0, align 4, !dbg !2283
  %conv370 = trunc i32 %292 to i8, !dbg !2283
  store i8 %conv370, i8* %c_state_out_ch, align 1, !dbg !2284
  %293 = load i32, i32* %c_tPos, align 4, !dbg !2285
  %294 = load i32, i32* %ro_blockSize100k, align 4, !dbg !2285
  %mul371 = mul i32 100000, %294, !dbg !2285
  %cmp372 = icmp uge i32 %293, %mul371, !dbg !2285
  br i1 %cmp372, label %if.then374, label %if.end375, !dbg !2287

if.then374:                                       ; preds = %if.end369
  store i8 1, i8* %retval, align 1, !dbg !2288
  br label %return, !dbg !2288

if.end375:                                        ; preds = %if.end369
  %295 = load i32, i32* %c_tPos, align 4, !dbg !2290
  %idxprom376 = zext i32 %295 to i64, !dbg !2290
  %296 = load i32*, i32** %c_tt, align 8, !dbg !2290
  %arrayidx377 = getelementptr inbounds i32, i32* %296, i64 %idxprom376, !dbg !2290
  %297 = load i32, i32* %arrayidx377, align 4, !dbg !2290
  store i32 %297, i32* %c_tPos, align 4, !dbg !2290
  %298 = load i32, i32* %c_tPos, align 4, !dbg !2290
  %and378 = and i32 %298, 255, !dbg !2290
  %conv379 = trunc i32 %and378 to i8, !dbg !2290
  store i8 %conv379, i8* %k1, align 1, !dbg !2290
  %299 = load i32, i32* %c_tPos, align 4, !dbg !2290
  %shr380 = lshr i32 %299, 8, !dbg !2290
  store i32 %shr380, i32* %c_tPos, align 4, !dbg !2290
  %300 = load i32, i32* %c_nblock_used, align 4, !dbg !2292
  %inc381 = add nsw i32 %300, 1, !dbg !2292
  store i32 %inc381, i32* %c_nblock_used, align 4, !dbg !2292
  %301 = load i8, i8* %k1, align 1, !dbg !2293
  %conv382 = zext i8 %301 to i32, !dbg !2293
  %302 = load i32, i32* %c_k0, align 4, !dbg !2295
  %cmp383 = icmp ne i32 %conv382, %302, !dbg !2296
  br i1 %cmp383, label %if.then385, label %if.end387, !dbg !2297

if.then385:                                       ; preds = %if.end375
  %303 = load i8, i8* %k1, align 1, !dbg !2298
  %conv386 = zext i8 %303 to i32, !dbg !2298
  store i32 %conv386, i32* %c_k0, align 4, !dbg !2300
  br label %s_state_out_len_eq_one, !dbg !2301

if.end387:                                        ; preds = %if.end375
  %304 = load i32, i32* %c_nblock_used, align 4, !dbg !2302
  %305 = load i32, i32* %s_save_nblockPP, align 4, !dbg !2304
  %cmp388 = icmp eq i32 %304, %305, !dbg !2305
  br i1 %cmp388, label %if.then390, label %if.end391, !dbg !2306

if.then390:                                       ; preds = %if.end387
  br label %s_state_out_len_eq_one, !dbg !2307

if.end391:                                        ; preds = %if.end387
  store i32 2, i32* %c_state_out_len, align 4, !dbg !2308
  %306 = load i32, i32* %c_tPos, align 4, !dbg !2309
  %307 = load i32, i32* %ro_blockSize100k, align 4, !dbg !2309
  %mul392 = mul i32 100000, %307, !dbg !2309
  %cmp393 = icmp uge i32 %306, %mul392, !dbg !2309
  br i1 %cmp393, label %if.then395, label %if.end396, !dbg !2311

if.then395:                                       ; preds = %if.end391
  store i8 1, i8* %retval, align 1, !dbg !2312
  br label %return, !dbg !2312

if.end396:                                        ; preds = %if.end391
  %308 = load i32, i32* %c_tPos, align 4, !dbg !2314
  %idxprom397 = zext i32 %308 to i64, !dbg !2314
  %309 = load i32*, i32** %c_tt, align 8, !dbg !2314
  %arrayidx398 = getelementptr inbounds i32, i32* %309, i64 %idxprom397, !dbg !2314
  %310 = load i32, i32* %arrayidx398, align 4, !dbg !2314
  store i32 %310, i32* %c_tPos, align 4, !dbg !2314
  %311 = load i32, i32* %c_tPos, align 4, !dbg !2314
  %and399 = and i32 %311, 255, !dbg !2314
  %conv400 = trunc i32 %and399 to i8, !dbg !2314
  store i8 %conv400, i8* %k1, align 1, !dbg !2314
  %312 = load i32, i32* %c_tPos, align 4, !dbg !2314
  %shr401 = lshr i32 %312, 8, !dbg !2314
  store i32 %shr401, i32* %c_tPos, align 4, !dbg !2314
  %313 = load i32, i32* %c_nblock_used, align 4, !dbg !2315
  %inc402 = add nsw i32 %313, 1, !dbg !2315
  store i32 %inc402, i32* %c_nblock_used, align 4, !dbg !2315
  %314 = load i32, i32* %c_nblock_used, align 4, !dbg !2316
  %315 = load i32, i32* %s_save_nblockPP, align 4, !dbg !2318
  %cmp403 = icmp eq i32 %314, %315, !dbg !2319
  br i1 %cmp403, label %if.then405, label %if.end406, !dbg !2320

if.then405:                                       ; preds = %if.end396
  br label %while.body323, !dbg !2321

if.end406:                                        ; preds = %if.end396
  %316 = load i8, i8* %k1, align 1, !dbg !2323
  %conv407 = zext i8 %316 to i32, !dbg !2323
  %317 = load i32, i32* %c_k0, align 4, !dbg !2325
  %cmp408 = icmp ne i32 %conv407, %317, !dbg !2326
  br i1 %cmp408, label %if.then410, label %if.end412, !dbg !2327

if.then410:                                       ; preds = %if.end406
  %318 = load i8, i8* %k1, align 1, !dbg !2328
  %conv411 = zext i8 %318 to i32, !dbg !2328
  store i32 %conv411, i32* %c_k0, align 4, !dbg !2331
  br label %while.body323, !dbg !2332

if.end412:                                        ; preds = %if.end406
  store i32 3, i32* %c_state_out_len, align 4, !dbg !2333
  %319 = load i32, i32* %c_tPos, align 4, !dbg !2334
  %320 = load i32, i32* %ro_blockSize100k, align 4, !dbg !2334
  %mul413 = mul i32 100000, %320, !dbg !2334
  %cmp414 = icmp uge i32 %319, %mul413, !dbg !2334
  br i1 %cmp414, label %if.then416, label %if.end417, !dbg !2336

if.then416:                                       ; preds = %if.end412
  store i8 1, i8* %retval, align 1, !dbg !2337
  br label %return, !dbg !2337

if.end417:                                        ; preds = %if.end412
  %321 = load i32, i32* %c_tPos, align 4, !dbg !2339
  %idxprom418 = zext i32 %321 to i64, !dbg !2339
  %322 = load i32*, i32** %c_tt, align 8, !dbg !2339
  %arrayidx419 = getelementptr inbounds i32, i32* %322, i64 %idxprom418, !dbg !2339
  %323 = load i32, i32* %arrayidx419, align 4, !dbg !2339
  store i32 %323, i32* %c_tPos, align 4, !dbg !2339
  %324 = load i32, i32* %c_tPos, align 4, !dbg !2339
  %and420 = and i32 %324, 255, !dbg !2339
  %conv421 = trunc i32 %and420 to i8, !dbg !2339
  store i8 %conv421, i8* %k1, align 1, !dbg !2339
  %325 = load i32, i32* %c_tPos, align 4, !dbg !2339
  %shr422 = lshr i32 %325, 8, !dbg !2339
  store i32 %shr422, i32* %c_tPos, align 4, !dbg !2339
  %326 = load i32, i32* %c_nblock_used, align 4, !dbg !2340
  %inc423 = add nsw i32 %326, 1, !dbg !2340
  store i32 %inc423, i32* %c_nblock_used, align 4, !dbg !2340
  %327 = load i32, i32* %c_nblock_used, align 4, !dbg !2341
  %328 = load i32, i32* %s_save_nblockPP, align 4, !dbg !2343
  %cmp424 = icmp eq i32 %327, %328, !dbg !2344
  br i1 %cmp424, label %if.then426, label %if.end427, !dbg !2345

if.then426:                                       ; preds = %if.end417
  br label %while.body323, !dbg !2346

if.end427:                                        ; preds = %if.end417
  %329 = load i8, i8* %k1, align 1, !dbg !2348
  %conv428 = zext i8 %329 to i32, !dbg !2348
  %330 = load i32, i32* %c_k0, align 4, !dbg !2350
  %cmp429 = icmp ne i32 %conv428, %330, !dbg !2351
  br i1 %cmp429, label %if.then431, label %if.end433, !dbg !2352

if.then431:                                       ; preds = %if.end427
  %331 = load i8, i8* %k1, align 1, !dbg !2353
  %conv432 = zext i8 %331 to i32, !dbg !2353
  store i32 %conv432, i32* %c_k0, align 4, !dbg !2356
  br label %while.body323, !dbg !2357

if.end433:                                        ; preds = %if.end427
  %332 = load i32, i32* %c_tPos, align 4, !dbg !2358
  %333 = load i32, i32* %ro_blockSize100k, align 4, !dbg !2358
  %mul434 = mul i32 100000, %333, !dbg !2358
  %cmp435 = icmp uge i32 %332, %mul434, !dbg !2358
  br i1 %cmp435, label %if.then437, label %if.end438, !dbg !2360

if.then437:                                       ; preds = %if.end433
  store i8 1, i8* %retval, align 1, !dbg !2361
  br label %return, !dbg !2361

if.end438:                                        ; preds = %if.end433
  %334 = load i32, i32* %c_tPos, align 4, !dbg !2363
  %idxprom439 = zext i32 %334 to i64, !dbg !2363
  %335 = load i32*, i32** %c_tt, align 8, !dbg !2363
  %arrayidx440 = getelementptr inbounds i32, i32* %335, i64 %idxprom439, !dbg !2363
  %336 = load i32, i32* %arrayidx440, align 4, !dbg !2363
  store i32 %336, i32* %c_tPos, align 4, !dbg !2363
  %337 = load i32, i32* %c_tPos, align 4, !dbg !2363
  %and441 = and i32 %337, 255, !dbg !2363
  %conv442 = trunc i32 %and441 to i8, !dbg !2363
  store i8 %conv442, i8* %k1, align 1, !dbg !2363
  %338 = load i32, i32* %c_tPos, align 4, !dbg !2363
  %shr443 = lshr i32 %338, 8, !dbg !2363
  store i32 %shr443, i32* %c_tPos, align 4, !dbg !2363
  %339 = load i32, i32* %c_nblock_used, align 4, !dbg !2364
  %inc444 = add nsw i32 %339, 1, !dbg !2364
  store i32 %inc444, i32* %c_nblock_used, align 4, !dbg !2364
  %340 = load i8, i8* %k1, align 1, !dbg !2365
  %conv445 = zext i8 %340 to i32, !dbg !2366
  %add446 = add nsw i32 %conv445, 4, !dbg !2367
  store i32 %add446, i32* %c_state_out_len, align 4, !dbg !2368
  %341 = load i32, i32* %c_tPos, align 4, !dbg !2369
  %342 = load i32, i32* %ro_blockSize100k, align 4, !dbg !2369
  %mul447 = mul i32 100000, %342, !dbg !2369
  %cmp448 = icmp uge i32 %341, %mul447, !dbg !2369
  br i1 %cmp448, label %if.then450, label %if.end451, !dbg !2371

if.then450:                                       ; preds = %if.end438
  store i8 1, i8* %retval, align 1, !dbg !2372
  br label %return, !dbg !2372

if.end451:                                        ; preds = %if.end438
  %343 = load i32, i32* %c_tPos, align 4, !dbg !2374
  %idxprom452 = zext i32 %343 to i64, !dbg !2374
  %344 = load i32*, i32** %c_tt, align 8, !dbg !2374
  %arrayidx453 = getelementptr inbounds i32, i32* %344, i64 %idxprom452, !dbg !2374
  %345 = load i32, i32* %arrayidx453, align 4, !dbg !2374
  store i32 %345, i32* %c_tPos, align 4, !dbg !2374
  %346 = load i32, i32* %c_tPos, align 4, !dbg !2374
  %and454 = and i32 %346, 255, !dbg !2374
  %conv455 = trunc i32 %and454 to i8, !dbg !2374
  %conv456 = zext i8 %conv455 to i32, !dbg !2374
  store i32 %conv456, i32* %c_k0, align 4, !dbg !2374
  %347 = load i32, i32* %c_tPos, align 4, !dbg !2374
  %shr457 = lshr i32 %347, 8, !dbg !2374
  store i32 %shr457, i32* %c_tPos, align 4, !dbg !2374
  %348 = load i32, i32* %c_nblock_used, align 4, !dbg !2375
  %inc458 = add nsw i32 %348, 1, !dbg !2375
  store i32 %inc458, i32* %c_nblock_used, align 4, !dbg !2375
  br label %while.body323, !dbg !2376

return_notr:                                      ; preds = %if.then368, %if.then350, %if.then331
  %349 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2378
  %strm459 = getelementptr inbounds %struct.DState, %struct.DState* %349, i32 0, i32 0, !dbg !2379
  %350 = load %struct.bz_stream*, %struct.bz_stream** %strm459, align 8, !dbg !2379
  %total_out_lo32460 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %350, i32 0, i32 6, !dbg !2380
  %351 = load i32, i32* %total_out_lo32460, align 4, !dbg !2380
  store i32 %351, i32* %total_out_lo32_old, align 4, !dbg !2381
  %352 = load i32, i32* %avail_out_INIT, align 4, !dbg !2382
  %353 = load i32, i32* %cs_avail_out, align 4, !dbg !2383
  %sub = sub i32 %352, %353, !dbg !2384
  %354 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2385
  %strm461 = getelementptr inbounds %struct.DState, %struct.DState* %354, i32 0, i32 0, !dbg !2386
  %355 = load %struct.bz_stream*, %struct.bz_stream** %strm461, align 8, !dbg !2386
  %total_out_lo32462 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %355, i32 0, i32 6, !dbg !2387
  %356 = load i32, i32* %total_out_lo32462, align 4, !dbg !2388
  %add463 = add i32 %356, %sub, !dbg !2388
  store i32 %add463, i32* %total_out_lo32462, align 4, !dbg !2388
  %357 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2389
  %strm464 = getelementptr inbounds %struct.DState, %struct.DState* %357, i32 0, i32 0, !dbg !2391
  %358 = load %struct.bz_stream*, %struct.bz_stream** %strm464, align 8, !dbg !2391
  %total_out_lo32465 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %358, i32 0, i32 6, !dbg !2392
  %359 = load i32, i32* %total_out_lo32465, align 4, !dbg !2392
  %360 = load i32, i32* %total_out_lo32_old, align 4, !dbg !2393
  %cmp466 = icmp ult i32 %359, %360, !dbg !2394
  br i1 %cmp466, label %if.then468, label %if.end472, !dbg !2395

if.then468:                                       ; preds = %return_notr
  %361 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2396
  %strm469 = getelementptr inbounds %struct.DState, %struct.DState* %361, i32 0, i32 0, !dbg !2397
  %362 = load %struct.bz_stream*, %struct.bz_stream** %strm469, align 8, !dbg !2397
  %total_out_hi32470 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %362, i32 0, i32 7, !dbg !2398
  %363 = load i32, i32* %total_out_hi32470, align 8, !dbg !2399
  %inc471 = add i32 %363, 1, !dbg !2399
  store i32 %inc471, i32* %total_out_hi32470, align 8, !dbg !2399
  br label %if.end472, !dbg !2396

if.end472:                                        ; preds = %if.then468, %return_notr
  %364 = load i32, i32* %c_calculatedBlockCRC, align 4, !dbg !2400
  %365 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2401
  %calculatedBlockCRC473 = getelementptr inbounds %struct.DState, %struct.DState* %365, i32 0, i32 25, !dbg !2402
  store i32 %364, i32* %calculatedBlockCRC473, align 8, !dbg !2403
  %366 = load i8, i8* %c_state_out_ch, align 1, !dbg !2404
  %367 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2405
  %state_out_ch474 = getelementptr inbounds %struct.DState, %struct.DState* %367, i32 0, i32 2, !dbg !2406
  store i8 %366, i8* %state_out_ch474, align 4, !dbg !2407
  %368 = load i32, i32* %c_state_out_len, align 4, !dbg !2408
  %369 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2409
  %state_out_len475 = getelementptr inbounds %struct.DState, %struct.DState* %369, i32 0, i32 3, !dbg !2410
  store i32 %368, i32* %state_out_len475, align 8, !dbg !2411
  %370 = load i32, i32* %c_nblock_used, align 4, !dbg !2412
  %371 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2413
  %nblock_used476 = getelementptr inbounds %struct.DState, %struct.DState* %371, i32 0, i32 17, !dbg !2414
  store i32 %370, i32* %nblock_used476, align 4, !dbg !2415
  %372 = load i32, i32* %c_k0, align 4, !dbg !2416
  %373 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2417
  %k0477 = getelementptr inbounds %struct.DState, %struct.DState* %373, i32 0, i32 15, !dbg !2418
  store i32 %372, i32* %k0477, align 8, !dbg !2419
  %374 = load i32*, i32** %c_tt, align 8, !dbg !2420
  %375 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2421
  %tt478 = getelementptr inbounds %struct.DState, %struct.DState* %375, i32 0, i32 20, !dbg !2422
  store i32* %374, i32** %tt478, align 8, !dbg !2423
  %376 = load i32, i32* %c_tPos, align 4, !dbg !2424
  %377 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2425
  %tPos479 = getelementptr inbounds %struct.DState, %struct.DState* %377, i32 0, i32 14, !dbg !2426
  store i32 %376, i32* %tPos479, align 4, !dbg !2427
  %378 = load i8*, i8** %cs_next_out, align 8, !dbg !2428
  %379 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2429
  %strm480 = getelementptr inbounds %struct.DState, %struct.DState* %379, i32 0, i32 0, !dbg !2430
  %380 = load %struct.bz_stream*, %struct.bz_stream** %strm480, align 8, !dbg !2430
  %next_out481 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %380, i32 0, i32 4, !dbg !2431
  store i8* %378, i8** %next_out481, align 8, !dbg !2432
  %381 = load i32, i32* %cs_avail_out, align 4, !dbg !2433
  %382 = load %struct.DState*, %struct.DState** %s.addr, align 8, !dbg !2434
  %strm482 = getelementptr inbounds %struct.DState, %struct.DState* %382, i32 0, i32 0, !dbg !2435
  %383 = load %struct.bz_stream*, %struct.bz_stream** %strm482, align 8, !dbg !2435
  %avail_out483 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %383, i32 0, i32 5, !dbg !2436
  store i32 %381, i32* %avail_out483, align 8, !dbg !2437
  br label %if.end484

if.end484:                                        ; preds = %if.end472
  store i8 0, i8* %retval, align 1, !dbg !2438
  br label %return, !dbg !2438

return:                                           ; preds = %if.end484, %if.then450, %if.then437, %if.then416, %if.then395, %if.then374, %if.then364, %if.then268, %if.then220, %if.then160, %if.then99, %if.then43, %if.then36, %if.then29, %if.then3
  %384 = load i8, i8* %retval, align 1, !dbg !2439
  ret i8 %384, !dbg !2439
}

declare i32 @BZ2_decompress(%struct.DState*) #2

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzDecompressEnd(%struct.bz_stream* %strm) #0 !dbg !153 {
entry:
  %retval = alloca i32, align 4
  %strm.addr = alloca %struct.bz_stream*, align 8
  %s = alloca %struct.DState*, align 8
  store %struct.bz_stream* %strm, %struct.bz_stream** %strm.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.bz_stream** %strm.addr, metadata !2440, metadata !392), !dbg !2441
  call void @llvm.dbg.declare(metadata %struct.DState** %s, metadata !2442, metadata !392), !dbg !2443
  %0 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2444
  %cmp = icmp eq %struct.bz_stream* %0, null, !dbg !2446
  br i1 %cmp, label %if.then, label %if.end, !dbg !2447

if.then:                                          ; preds = %entry
  store i32 -2, i32* %retval, align 4, !dbg !2448
  br label %return, !dbg !2448

if.end:                                           ; preds = %entry
  %1 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2450
  %state = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %1, i32 0, i32 8, !dbg !2451
  %2 = load i8*, i8** %state, align 8, !dbg !2451
  %3 = bitcast i8* %2 to %struct.DState*, !dbg !2450
  store %struct.DState* %3, %struct.DState** %s, align 8, !dbg !2452
  %4 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !2453
  %cmp1 = icmp eq %struct.DState* %4, null, !dbg !2455
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !2456

if.then2:                                         ; preds = %if.end
  store i32 -2, i32* %retval, align 4, !dbg !2457
  br label %return, !dbg !2457

if.end3:                                          ; preds = %if.end
  %5 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !2459
  %strm4 = getelementptr inbounds %struct.DState, %struct.DState* %5, i32 0, i32 0, !dbg !2461
  %6 = load %struct.bz_stream*, %struct.bz_stream** %strm4, align 8, !dbg !2461
  %7 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2462
  %cmp5 = icmp ne %struct.bz_stream* %6, %7, !dbg !2463
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !2464

if.then6:                                         ; preds = %if.end3
  store i32 -2, i32* %retval, align 4, !dbg !2465
  br label %return, !dbg !2465

if.end7:                                          ; preds = %if.end3
  %8 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !2467
  %tt = getelementptr inbounds %struct.DState, %struct.DState* %8, i32 0, i32 20, !dbg !2469
  %9 = load i32*, i32** %tt, align 8, !dbg !2469
  %cmp8 = icmp ne i32* %9, null, !dbg !2470
  br i1 %cmp8, label %if.then9, label %if.end11, !dbg !2471

if.then9:                                         ; preds = %if.end7
  %10 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2472
  %bzfree = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %10, i32 0, i32 10, !dbg !2472
  %11 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree, align 8, !dbg !2472
  %12 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2472
  %opaque = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %12, i32 0, i32 11, !dbg !2472
  %13 = load i8*, i8** %opaque, align 8, !dbg !2472
  %14 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !2472
  %tt10 = getelementptr inbounds %struct.DState, %struct.DState* %14, i32 0, i32 20, !dbg !2472
  %15 = load i32*, i32** %tt10, align 8, !dbg !2472
  %16 = bitcast i32* %15 to i8*, !dbg !2472
  call void %11(i8* %13, i8* %16), !dbg !2472
  br label %if.end11, !dbg !2472

if.end11:                                         ; preds = %if.then9, %if.end7
  %17 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !2474
  %ll16 = getelementptr inbounds %struct.DState, %struct.DState* %17, i32 0, i32 21, !dbg !2476
  %18 = load i16*, i16** %ll16, align 8, !dbg !2476
  %cmp12 = icmp ne i16* %18, null, !dbg !2477
  br i1 %cmp12, label %if.then13, label %if.end17, !dbg !2478

if.then13:                                        ; preds = %if.end11
  %19 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2479
  %bzfree14 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %19, i32 0, i32 10, !dbg !2479
  %20 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree14, align 8, !dbg !2479
  %21 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2479
  %opaque15 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %21, i32 0, i32 11, !dbg !2479
  %22 = load i8*, i8** %opaque15, align 8, !dbg !2479
  %23 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !2479
  %ll1616 = getelementptr inbounds %struct.DState, %struct.DState* %23, i32 0, i32 21, !dbg !2479
  %24 = load i16*, i16** %ll1616, align 8, !dbg !2479
  %25 = bitcast i16* %24 to i8*, !dbg !2479
  call void %20(i8* %22, i8* %25), !dbg !2479
  br label %if.end17, !dbg !2479

if.end17:                                         ; preds = %if.then13, %if.end11
  %26 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !2481
  %ll4 = getelementptr inbounds %struct.DState, %struct.DState* %26, i32 0, i32 22, !dbg !2483
  %27 = load i8*, i8** %ll4, align 8, !dbg !2483
  %cmp18 = icmp ne i8* %27, null, !dbg !2484
  br i1 %cmp18, label %if.then19, label %if.end23, !dbg !2485

if.then19:                                        ; preds = %if.end17
  %28 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2486
  %bzfree20 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %28, i32 0, i32 10, !dbg !2486
  %29 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree20, align 8, !dbg !2486
  %30 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2486
  %opaque21 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %30, i32 0, i32 11, !dbg !2486
  %31 = load i8*, i8** %opaque21, align 8, !dbg !2486
  %32 = load %struct.DState*, %struct.DState** %s, align 8, !dbg !2486
  %ll422 = getelementptr inbounds %struct.DState, %struct.DState* %32, i32 0, i32 22, !dbg !2486
  %33 = load i8*, i8** %ll422, align 8, !dbg !2486
  call void %29(i8* %31, i8* %33), !dbg !2486
  br label %if.end23, !dbg !2486

if.end23:                                         ; preds = %if.then19, %if.end17
  %34 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2488
  %bzfree24 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %34, i32 0, i32 10, !dbg !2488
  %35 = load void (i8*, i8*)*, void (i8*, i8*)** %bzfree24, align 8, !dbg !2488
  %36 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2488
  %opaque25 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %36, i32 0, i32 11, !dbg !2488
  %37 = load i8*, i8** %opaque25, align 8, !dbg !2488
  %38 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2488
  %state26 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %38, i32 0, i32 8, !dbg !2488
  %39 = load i8*, i8** %state26, align 8, !dbg !2488
  call void %35(i8* %37, i8* %39), !dbg !2488
  %40 = load %struct.bz_stream*, %struct.bz_stream** %strm.addr, align 8, !dbg !2489
  %state27 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %40, i32 0, i32 8, !dbg !2490
  store i8* null, i8** %state27, align 8, !dbg !2491
  store i32 0, i32* %retval, align 4, !dbg !2492
  br label %return, !dbg !2492

return:                                           ; preds = %if.end23, %if.then6, %if.then2, %if.then
  %41 = load i32, i32* %retval, align 4, !dbg !2493
  ret i32 %41, !dbg !2493
}

; Function Attrs: nounwind uwtable
define i8* @BZ2_bzWriteOpen(i32* %bzerror, %struct._IO_FILE* %f, i32 %blockSize100k, i32 %verbosity, i32 %workFactor) #0 !dbg !154 {
entry:
  %retval = alloca i8*, align 8
  %bzerror.addr = alloca i32*, align 8
  %f.addr = alloca %struct._IO_FILE*, align 8
  %blockSize100k.addr = alloca i32, align 4
  %verbosity.addr = alloca i32, align 4
  %workFactor.addr = alloca i32, align 4
  %ret = alloca i32, align 4
  %bzf = alloca %struct.bzFile*, align 8
  store i32* %bzerror, i32** %bzerror.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %bzerror.addr, metadata !2494, metadata !392), !dbg !2495
  store %struct._IO_FILE* %f, %struct._IO_FILE** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %f.addr, metadata !2496, metadata !392), !dbg !2497
  store i32 %blockSize100k, i32* %blockSize100k.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %blockSize100k.addr, metadata !2498, metadata !392), !dbg !2499
  store i32 %verbosity, i32* %verbosity.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %verbosity.addr, metadata !2500, metadata !392), !dbg !2501
  store i32 %workFactor, i32* %workFactor.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %workFactor.addr, metadata !2502, metadata !392), !dbg !2503
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !2504, metadata !392), !dbg !2505
  call void @llvm.dbg.declare(metadata %struct.bzFile** %bzf, metadata !2506, metadata !392), !dbg !2507
  store %struct.bzFile* null, %struct.bzFile** %bzf, align 8, !dbg !2507
  %0 = load i32*, i32** %bzerror.addr, align 8, !dbg !2508
  %cmp = icmp ne i32* %0, null, !dbg !2508
  br i1 %cmp, label %if.then, label %if.end, !dbg !2511

if.then:                                          ; preds = %entry
  %1 = load i32*, i32** %bzerror.addr, align 8, !dbg !2512
  store i32 0, i32* %1, align 4, !dbg !2512
  br label %if.end, !dbg !2512

if.end:                                           ; preds = %if.then, %entry
  %2 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2514
  %cmp1 = icmp ne %struct.bzFile* %2, null, !dbg !2514
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !2514

if.then2:                                         ; preds = %if.end
  %3 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2517
  %lastErr = getelementptr inbounds %struct.bzFile, %struct.bzFile* %3, i32 0, i32 5, !dbg !2517
  store i32 0, i32* %lastErr, align 8, !dbg !2517
  br label %if.end3, !dbg !2517

if.end3:                                          ; preds = %if.then2, %if.end
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** %f.addr, align 8, !dbg !2519
  %cmp4 = icmp eq %struct._IO_FILE* %4, null, !dbg !2521
  br i1 %cmp4, label %if.then16, label %lor.lhs.false, !dbg !2522

lor.lhs.false:                                    ; preds = %if.end3
  %5 = load i32, i32* %blockSize100k.addr, align 4, !dbg !2523
  %cmp5 = icmp slt i32 %5, 1, !dbg !2524
  br i1 %cmp5, label %if.then16, label %lor.lhs.false6, !dbg !2525

lor.lhs.false6:                                   ; preds = %lor.lhs.false
  %6 = load i32, i32* %blockSize100k.addr, align 4, !dbg !2526
  %cmp7 = icmp sgt i32 %6, 9, !dbg !2528
  br i1 %cmp7, label %if.then16, label %lor.lhs.false8, !dbg !2529

lor.lhs.false8:                                   ; preds = %lor.lhs.false6
  %7 = load i32, i32* %workFactor.addr, align 4, !dbg !2530
  %cmp9 = icmp slt i32 %7, 0, !dbg !2531
  br i1 %cmp9, label %if.then16, label %lor.lhs.false10, !dbg !2532

lor.lhs.false10:                                  ; preds = %lor.lhs.false8
  %8 = load i32, i32* %workFactor.addr, align 4, !dbg !2533
  %cmp11 = icmp sgt i32 %8, 250, !dbg !2534
  br i1 %cmp11, label %if.then16, label %lor.lhs.false12, !dbg !2535

lor.lhs.false12:                                  ; preds = %lor.lhs.false10
  %9 = load i32, i32* %verbosity.addr, align 4, !dbg !2536
  %cmp13 = icmp slt i32 %9, 0, !dbg !2537
  br i1 %cmp13, label %if.then16, label %lor.lhs.false14, !dbg !2538

lor.lhs.false14:                                  ; preds = %lor.lhs.false12
  %10 = load i32, i32* %verbosity.addr, align 4, !dbg !2539
  %cmp15 = icmp sgt i32 %10, 4, !dbg !2540
  br i1 %cmp15, label %if.then16, label %if.end24, !dbg !2541

if.then16:                                        ; preds = %lor.lhs.false14, %lor.lhs.false12, %lor.lhs.false10, %lor.lhs.false8, %lor.lhs.false6, %lor.lhs.false, %if.end3
  %11 = load i32*, i32** %bzerror.addr, align 8, !dbg !2543
  %cmp17 = icmp ne i32* %11, null, !dbg !2543
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !2547

if.then18:                                        ; preds = %if.then16
  %12 = load i32*, i32** %bzerror.addr, align 8, !dbg !2548
  store i32 -2, i32* %12, align 4, !dbg !2548
  br label %if.end19, !dbg !2548

if.end19:                                         ; preds = %if.then18, %if.then16
  %13 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2550
  %cmp20 = icmp ne %struct.bzFile* %13, null, !dbg !2550
  br i1 %cmp20, label %if.then21, label %if.end23, !dbg !2550

if.then21:                                        ; preds = %if.end19
  %14 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2553
  %lastErr22 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %14, i32 0, i32 5, !dbg !2553
  store i32 -2, i32* %lastErr22, align 8, !dbg !2553
  br label %if.end23, !dbg !2553

if.end23:                                         ; preds = %if.then21, %if.end19
  store i8* null, i8** %retval, align 8, !dbg !2555
  br label %return, !dbg !2555

if.end24:                                         ; preds = %lor.lhs.false14
  %15 = load %struct._IO_FILE*, %struct._IO_FILE** %f.addr, align 8, !dbg !2557
  %call = call i32 @ferror(%struct._IO_FILE* %15) #10, !dbg !2559
  %tobool = icmp ne i32 %call, 0, !dbg !2559
  br i1 %tobool, label %if.then25, label %if.end33, !dbg !2560

if.then25:                                        ; preds = %if.end24
  %16 = load i32*, i32** %bzerror.addr, align 8, !dbg !2561
  %cmp26 = icmp ne i32* %16, null, !dbg !2561
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !2565

if.then27:                                        ; preds = %if.then25
  %17 = load i32*, i32** %bzerror.addr, align 8, !dbg !2566
  store i32 -6, i32* %17, align 4, !dbg !2566
  br label %if.end28, !dbg !2566

if.end28:                                         ; preds = %if.then27, %if.then25
  %18 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2568
  %cmp29 = icmp ne %struct.bzFile* %18, null, !dbg !2568
  br i1 %cmp29, label %if.then30, label %if.end32, !dbg !2568

if.then30:                                        ; preds = %if.end28
  %19 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2571
  %lastErr31 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %19, i32 0, i32 5, !dbg !2571
  store i32 -6, i32* %lastErr31, align 8, !dbg !2571
  br label %if.end32, !dbg !2571

if.end32:                                         ; preds = %if.then30, %if.end28
  store i8* null, i8** %retval, align 8, !dbg !2573
  br label %return, !dbg !2573

if.end33:                                         ; preds = %if.end24
  %call34 = call noalias i8* @malloc(i64 5104) #10, !dbg !2575
  %20 = bitcast i8* %call34 to %struct.bzFile*, !dbg !2575
  store %struct.bzFile* %20, %struct.bzFile** %bzf, align 8, !dbg !2576
  %21 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2577
  %cmp35 = icmp eq %struct.bzFile* %21, null, !dbg !2579
  br i1 %cmp35, label %if.then36, label %if.end44, !dbg !2580

if.then36:                                        ; preds = %if.end33
  %22 = load i32*, i32** %bzerror.addr, align 8, !dbg !2581
  %cmp37 = icmp ne i32* %22, null, !dbg !2581
  br i1 %cmp37, label %if.then38, label %if.end39, !dbg !2585

if.then38:                                        ; preds = %if.then36
  %23 = load i32*, i32** %bzerror.addr, align 8, !dbg !2586
  store i32 -3, i32* %23, align 4, !dbg !2586
  br label %if.end39, !dbg !2586

if.end39:                                         ; preds = %if.then38, %if.then36
  %24 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2588
  %cmp40 = icmp ne %struct.bzFile* %24, null, !dbg !2588
  br i1 %cmp40, label %if.then41, label %if.end43, !dbg !2588

if.then41:                                        ; preds = %if.end39
  %25 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2591
  %lastErr42 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %25, i32 0, i32 5, !dbg !2591
  store i32 -3, i32* %lastErr42, align 8, !dbg !2591
  br label %if.end43, !dbg !2591

if.end43:                                         ; preds = %if.then41, %if.end39
  store i8* null, i8** %retval, align 8, !dbg !2593
  br label %return, !dbg !2593

if.end44:                                         ; preds = %if.end33
  %26 = load i32*, i32** %bzerror.addr, align 8, !dbg !2595
  %cmp45 = icmp ne i32* %26, null, !dbg !2595
  br i1 %cmp45, label %if.then46, label %if.end47, !dbg !2598

if.then46:                                        ; preds = %if.end44
  %27 = load i32*, i32** %bzerror.addr, align 8, !dbg !2599
  store i32 0, i32* %27, align 4, !dbg !2599
  br label %if.end47, !dbg !2599

if.end47:                                         ; preds = %if.then46, %if.end44
  %28 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2601
  %cmp48 = icmp ne %struct.bzFile* %28, null, !dbg !2601
  br i1 %cmp48, label %if.then49, label %if.end51, !dbg !2601

if.then49:                                        ; preds = %if.end47
  %29 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2604
  %lastErr50 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %29, i32 0, i32 5, !dbg !2604
  store i32 0, i32* %lastErr50, align 8, !dbg !2604
  br label %if.end51, !dbg !2604

if.end51:                                         ; preds = %if.then49, %if.end47
  %30 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2606
  %initialisedOk = getelementptr inbounds %struct.bzFile, %struct.bzFile* %30, i32 0, i32 6, !dbg !2607
  store i8 0, i8* %initialisedOk, align 4, !dbg !2608
  %31 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2609
  %bufN = getelementptr inbounds %struct.bzFile, %struct.bzFile* %31, i32 0, i32 2, !dbg !2610
  store i32 0, i32* %bufN, align 8, !dbg !2611
  %32 = load %struct._IO_FILE*, %struct._IO_FILE** %f.addr, align 8, !dbg !2612
  %33 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2613
  %handle = getelementptr inbounds %struct.bzFile, %struct.bzFile* %33, i32 0, i32 0, !dbg !2614
  store %struct._IO_FILE* %32, %struct._IO_FILE** %handle, align 8, !dbg !2615
  %34 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2616
  %writing = getelementptr inbounds %struct.bzFile, %struct.bzFile* %34, i32 0, i32 3, !dbg !2617
  store i8 1, i8* %writing, align 4, !dbg !2618
  %35 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2619
  %strm = getelementptr inbounds %struct.bzFile, %struct.bzFile* %35, i32 0, i32 4, !dbg !2620
  %bzalloc = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 9, !dbg !2621
  store i8* (i8*, i32, i32)* null, i8* (i8*, i32, i32)** %bzalloc, align 8, !dbg !2622
  %36 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2623
  %strm52 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %36, i32 0, i32 4, !dbg !2624
  %bzfree = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm52, i32 0, i32 10, !dbg !2625
  store void (i8*, i8*)* null, void (i8*, i8*)** %bzfree, align 8, !dbg !2626
  %37 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2627
  %strm53 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %37, i32 0, i32 4, !dbg !2628
  %opaque = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm53, i32 0, i32 11, !dbg !2629
  store i8* null, i8** %opaque, align 8, !dbg !2630
  %38 = load i32, i32* %workFactor.addr, align 4, !dbg !2631
  %cmp54 = icmp eq i32 %38, 0, !dbg !2633
  br i1 %cmp54, label %if.then55, label %if.end56, !dbg !2634

if.then55:                                        ; preds = %if.end51
  store i32 30, i32* %workFactor.addr, align 4, !dbg !2635
  br label %if.end56, !dbg !2637

if.end56:                                         ; preds = %if.then55, %if.end51
  %39 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2638
  %strm57 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %39, i32 0, i32 4, !dbg !2639
  %40 = load i32, i32* %blockSize100k.addr, align 4, !dbg !2640
  %41 = load i32, i32* %verbosity.addr, align 4, !dbg !2641
  %42 = load i32, i32* %workFactor.addr, align 4, !dbg !2642
  %call58 = call i32 @BZ2_bzCompressInit(%struct.bz_stream* %strm57, i32 %40, i32 %41, i32 %42), !dbg !2643
  store i32 %call58, i32* %ret, align 4, !dbg !2644
  %43 = load i32, i32* %ret, align 4, !dbg !2645
  %cmp59 = icmp ne i32 %43, 0, !dbg !2647
  br i1 %cmp59, label %if.then60, label %if.end68, !dbg !2648

if.then60:                                        ; preds = %if.end56
  %44 = load i32*, i32** %bzerror.addr, align 8, !dbg !2649
  %cmp61 = icmp ne i32* %44, null, !dbg !2649
  br i1 %cmp61, label %if.then62, label %if.end63, !dbg !2653

if.then62:                                        ; preds = %if.then60
  %45 = load i32, i32* %ret, align 4, !dbg !2654
  %46 = load i32*, i32** %bzerror.addr, align 8, !dbg !2654
  store i32 %45, i32* %46, align 4, !dbg !2654
  br label %if.end63, !dbg !2654

if.end63:                                         ; preds = %if.then62, %if.then60
  %47 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2656
  %cmp64 = icmp ne %struct.bzFile* %47, null, !dbg !2656
  br i1 %cmp64, label %if.then65, label %if.end67, !dbg !2656

if.then65:                                        ; preds = %if.end63
  %48 = load i32, i32* %ret, align 4, !dbg !2659
  %49 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2659
  %lastErr66 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %49, i32 0, i32 5, !dbg !2659
  store i32 %48, i32* %lastErr66, align 8, !dbg !2659
  br label %if.end67, !dbg !2659

if.end67:                                         ; preds = %if.then65, %if.end63
  %50 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2661
  %51 = bitcast %struct.bzFile* %50 to i8*, !dbg !2661
  call void @free(i8* %51) #10, !dbg !2663
  store i8* null, i8** %retval, align 8, !dbg !2664
  br label %return, !dbg !2664

if.end68:                                         ; preds = %if.end56
  %52 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2665
  %strm69 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %52, i32 0, i32 4, !dbg !2666
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm69, i32 0, i32 1, !dbg !2667
  store i32 0, i32* %avail_in, align 8, !dbg !2668
  %53 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2669
  %initialisedOk70 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %53, i32 0, i32 6, !dbg !2670
  store i8 1, i8* %initialisedOk70, align 4, !dbg !2671
  %54 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2672
  %55 = bitcast %struct.bzFile* %54 to i8*, !dbg !2672
  store i8* %55, i8** %retval, align 8, !dbg !2673
  br label %return, !dbg !2673

return:                                           ; preds = %if.end68, %if.end67, %if.end43, %if.end32, %if.end23
  %56 = load i8*, i8** %retval, align 8, !dbg !2674
  ret i8* %56, !dbg !2674
}

; Function Attrs: nounwind
declare i32 @ferror(%struct._IO_FILE*) #5

; Function Attrs: nounwind
declare noalias i8* @malloc(i64) #5

; Function Attrs: nounwind
declare void @free(i8*) #5

; Function Attrs: nounwind uwtable
define void @BZ2_bzWrite(i32* %bzerror, i8* %b, i8* %buf, i32 %len) #0 !dbg !160 {
entry:
  %bzerror.addr = alloca i32*, align 8
  %b.addr = alloca i8*, align 8
  %buf.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %n = alloca i32, align 4
  %n2 = alloca i32, align 4
  %ret = alloca i32, align 4
  %bzf = alloca %struct.bzFile*, align 8
  store i32* %bzerror, i32** %bzerror.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %bzerror.addr, metadata !2675, metadata !392), !dbg !2676
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !2677, metadata !392), !dbg !2678
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !2679, metadata !392), !dbg !2680
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !2681, metadata !392), !dbg !2682
  call void @llvm.dbg.declare(metadata i32* %n, metadata !2683, metadata !392), !dbg !2684
  call void @llvm.dbg.declare(metadata i32* %n2, metadata !2685, metadata !392), !dbg !2686
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !2687, metadata !392), !dbg !2688
  call void @llvm.dbg.declare(metadata %struct.bzFile** %bzf, metadata !2689, metadata !392), !dbg !2690
  %0 = load i8*, i8** %b.addr, align 8, !dbg !2691
  %1 = bitcast i8* %0 to %struct.bzFile*, !dbg !2692
  store %struct.bzFile* %1, %struct.bzFile** %bzf, align 8, !dbg !2690
  %2 = load i32*, i32** %bzerror.addr, align 8, !dbg !2693
  %cmp = icmp ne i32* %2, null, !dbg !2693
  br i1 %cmp, label %if.then, label %if.end, !dbg !2696

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %bzerror.addr, align 8, !dbg !2697
  store i32 0, i32* %3, align 4, !dbg !2697
  br label %if.end, !dbg !2697

if.end:                                           ; preds = %if.then, %entry
  %4 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2699
  %cmp1 = icmp ne %struct.bzFile* %4, null, !dbg !2699
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !2699

if.then2:                                         ; preds = %if.end
  %5 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2702
  %lastErr = getelementptr inbounds %struct.bzFile, %struct.bzFile* %5, i32 0, i32 5, !dbg !2702
  store i32 0, i32* %lastErr, align 8, !dbg !2702
  br label %if.end3, !dbg !2702

if.end3:                                          ; preds = %if.then2, %if.end
  %6 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2704
  %cmp4 = icmp eq %struct.bzFile* %6, null, !dbg !2706
  br i1 %cmp4, label %if.then8, label %lor.lhs.false, !dbg !2707

lor.lhs.false:                                    ; preds = %if.end3
  %7 = load i8*, i8** %buf.addr, align 8, !dbg !2708
  %cmp5 = icmp eq i8* %7, null, !dbg !2710
  br i1 %cmp5, label %if.then8, label %lor.lhs.false6, !dbg !2711

lor.lhs.false6:                                   ; preds = %lor.lhs.false
  %8 = load i32, i32* %len.addr, align 4, !dbg !2712
  %cmp7 = icmp slt i32 %8, 0, !dbg !2714
  br i1 %cmp7, label %if.then8, label %if.end16, !dbg !2715

if.then8:                                         ; preds = %lor.lhs.false6, %lor.lhs.false, %if.end3
  %9 = load i32*, i32** %bzerror.addr, align 8, !dbg !2716
  %cmp9 = icmp ne i32* %9, null, !dbg !2716
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !2720

if.then10:                                        ; preds = %if.then8
  %10 = load i32*, i32** %bzerror.addr, align 8, !dbg !2721
  store i32 -2, i32* %10, align 4, !dbg !2721
  br label %if.end11, !dbg !2721

if.end11:                                         ; preds = %if.then10, %if.then8
  %11 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2723
  %cmp12 = icmp ne %struct.bzFile* %11, null, !dbg !2723
  br i1 %cmp12, label %if.then13, label %if.end15, !dbg !2723

if.then13:                                        ; preds = %if.end11
  %12 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2726
  %lastErr14 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %12, i32 0, i32 5, !dbg !2726
  store i32 -2, i32* %lastErr14, align 8, !dbg !2726
  br label %if.end15, !dbg !2726

if.end15:                                         ; preds = %if.then13, %if.end11
  br label %return, !dbg !2728

if.end16:                                         ; preds = %lor.lhs.false6
  %13 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2730
  %writing = getelementptr inbounds %struct.bzFile, %struct.bzFile* %13, i32 0, i32 3, !dbg !2732
  %14 = load i8, i8* %writing, align 4, !dbg !2732
  %tobool = icmp ne i8 %14, 0, !dbg !2733
  br i1 %tobool, label %if.end25, label %if.then17, !dbg !2734

if.then17:                                        ; preds = %if.end16
  %15 = load i32*, i32** %bzerror.addr, align 8, !dbg !2735
  %cmp18 = icmp ne i32* %15, null, !dbg !2735
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !2739

if.then19:                                        ; preds = %if.then17
  %16 = load i32*, i32** %bzerror.addr, align 8, !dbg !2740
  store i32 -1, i32* %16, align 4, !dbg !2740
  br label %if.end20, !dbg !2740

if.end20:                                         ; preds = %if.then19, %if.then17
  %17 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2742
  %cmp21 = icmp ne %struct.bzFile* %17, null, !dbg !2742
  br i1 %cmp21, label %if.then22, label %if.end24, !dbg !2742

if.then22:                                        ; preds = %if.end20
  %18 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2745
  %lastErr23 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %18, i32 0, i32 5, !dbg !2745
  store i32 -1, i32* %lastErr23, align 8, !dbg !2745
  br label %if.end24, !dbg !2745

if.end24:                                         ; preds = %if.then22, %if.end20
  br label %return, !dbg !2747

if.end25:                                         ; preds = %if.end16
  %19 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2749
  %handle = getelementptr inbounds %struct.bzFile, %struct.bzFile* %19, i32 0, i32 0, !dbg !2751
  %20 = load %struct._IO_FILE*, %struct._IO_FILE** %handle, align 8, !dbg !2751
  %call = call i32 @ferror(%struct._IO_FILE* %20) #10, !dbg !2752
  %tobool26 = icmp ne i32 %call, 0, !dbg !2752
  br i1 %tobool26, label %if.then27, label %if.end35, !dbg !2753

if.then27:                                        ; preds = %if.end25
  %21 = load i32*, i32** %bzerror.addr, align 8, !dbg !2754
  %cmp28 = icmp ne i32* %21, null, !dbg !2754
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !2758

if.then29:                                        ; preds = %if.then27
  %22 = load i32*, i32** %bzerror.addr, align 8, !dbg !2759
  store i32 -6, i32* %22, align 4, !dbg !2759
  br label %if.end30, !dbg !2759

if.end30:                                         ; preds = %if.then29, %if.then27
  %23 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2761
  %cmp31 = icmp ne %struct.bzFile* %23, null, !dbg !2761
  br i1 %cmp31, label %if.then32, label %if.end34, !dbg !2761

if.then32:                                        ; preds = %if.end30
  %24 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2764
  %lastErr33 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %24, i32 0, i32 5, !dbg !2764
  store i32 -6, i32* %lastErr33, align 8, !dbg !2764
  br label %if.end34, !dbg !2764

if.end34:                                         ; preds = %if.then32, %if.end30
  br label %return, !dbg !2766

if.end35:                                         ; preds = %if.end25
  %25 = load i32, i32* %len.addr, align 4, !dbg !2768
  %cmp36 = icmp eq i32 %25, 0, !dbg !2770
  br i1 %cmp36, label %if.then37, label %if.end45, !dbg !2771

if.then37:                                        ; preds = %if.end35
  %26 = load i32*, i32** %bzerror.addr, align 8, !dbg !2772
  %cmp38 = icmp ne i32* %26, null, !dbg !2772
  br i1 %cmp38, label %if.then39, label %if.end40, !dbg !2776

if.then39:                                        ; preds = %if.then37
  %27 = load i32*, i32** %bzerror.addr, align 8, !dbg !2777
  store i32 0, i32* %27, align 4, !dbg !2777
  br label %if.end40, !dbg !2777

if.end40:                                         ; preds = %if.then39, %if.then37
  %28 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2779
  %cmp41 = icmp ne %struct.bzFile* %28, null, !dbg !2779
  br i1 %cmp41, label %if.then42, label %if.end44, !dbg !2779

if.then42:                                        ; preds = %if.end40
  %29 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2782
  %lastErr43 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %29, i32 0, i32 5, !dbg !2782
  store i32 0, i32* %lastErr43, align 8, !dbg !2782
  br label %if.end44, !dbg !2782

if.end44:                                         ; preds = %if.then42, %if.end40
  br label %return, !dbg !2784

if.end45:                                         ; preds = %if.end35
  %30 = load i32, i32* %len.addr, align 4, !dbg !2786
  %31 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2787
  %strm = getelementptr inbounds %struct.bzFile, %struct.bzFile* %31, i32 0, i32 4, !dbg !2788
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 1, !dbg !2789
  store i32 %30, i32* %avail_in, align 8, !dbg !2790
  %32 = load i8*, i8** %buf.addr, align 8, !dbg !2791
  %33 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2792
  %strm46 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %33, i32 0, i32 4, !dbg !2793
  %next_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm46, i32 0, i32 0, !dbg !2794
  store i8* %32, i8** %next_in, align 8, !dbg !2795
  br label %while.body, !dbg !2796

while.body:                                       ; preds = %if.end45, %if.end105
  %34 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2797
  %strm47 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %34, i32 0, i32 4, !dbg !2799
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm47, i32 0, i32 5, !dbg !2800
  store i32 5000, i32* %avail_out, align 8, !dbg !2801
  %35 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2802
  %buf48 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %35, i32 0, i32 1, !dbg !2803
  %arraydecay = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf48, i32 0, i32 0, !dbg !2802
  %36 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2804
  %strm49 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %36, i32 0, i32 4, !dbg !2805
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm49, i32 0, i32 4, !dbg !2806
  store i8* %arraydecay, i8** %next_out, align 8, !dbg !2807
  %37 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2808
  %strm50 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %37, i32 0, i32 4, !dbg !2809
  %call51 = call i32 @BZ2_bzCompress(%struct.bz_stream* %strm50, i32 0), !dbg !2810
  store i32 %call51, i32* %ret, align 4, !dbg !2811
  %38 = load i32, i32* %ret, align 4, !dbg !2812
  %cmp52 = icmp ne i32 %38, 1, !dbg !2814
  br i1 %cmp52, label %if.then53, label %if.end61, !dbg !2815

if.then53:                                        ; preds = %while.body
  %39 = load i32*, i32** %bzerror.addr, align 8, !dbg !2816
  %cmp54 = icmp ne i32* %39, null, !dbg !2816
  br i1 %cmp54, label %if.then55, label %if.end56, !dbg !2820

if.then55:                                        ; preds = %if.then53
  %40 = load i32, i32* %ret, align 4, !dbg !2821
  %41 = load i32*, i32** %bzerror.addr, align 8, !dbg !2821
  store i32 %40, i32* %41, align 4, !dbg !2821
  br label %if.end56, !dbg !2821

if.end56:                                         ; preds = %if.then55, %if.then53
  %42 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2823
  %cmp57 = icmp ne %struct.bzFile* %42, null, !dbg !2823
  br i1 %cmp57, label %if.then58, label %if.end60, !dbg !2823

if.then58:                                        ; preds = %if.end56
  %43 = load i32, i32* %ret, align 4, !dbg !2826
  %44 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2826
  %lastErr59 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %44, i32 0, i32 5, !dbg !2826
  store i32 %43, i32* %lastErr59, align 8, !dbg !2826
  br label %if.end60, !dbg !2826

if.end60:                                         ; preds = %if.then58, %if.end56
  br label %return, !dbg !2828

if.end61:                                         ; preds = %while.body
  %45 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2830
  %strm62 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %45, i32 0, i32 4, !dbg !2832
  %avail_out63 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm62, i32 0, i32 5, !dbg !2833
  %46 = load i32, i32* %avail_out63, align 8, !dbg !2833
  %cmp64 = icmp ult i32 %46, 5000, !dbg !2834
  br i1 %cmp64, label %if.then65, label %if.end90, !dbg !2835

if.then65:                                        ; preds = %if.end61
  %47 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2836
  %strm66 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %47, i32 0, i32 4, !dbg !2838
  %avail_out67 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm66, i32 0, i32 5, !dbg !2839
  %48 = load i32, i32* %avail_out67, align 8, !dbg !2839
  %sub = sub i32 5000, %48, !dbg !2840
  store i32 %sub, i32* %n, align 4, !dbg !2841
  %49 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2842
  %buf68 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %49, i32 0, i32 1, !dbg !2843
  %arraydecay69 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf68, i32 0, i32 0, !dbg !2844
  %50 = load i32, i32* %n, align 4, !dbg !2845
  %conv = sext i32 %50 to i64, !dbg !2845
  %51 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2846
  %handle70 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %51, i32 0, i32 0, !dbg !2847
  %52 = load %struct._IO_FILE*, %struct._IO_FILE** %handle70, align 8, !dbg !2847
  %call71 = call i64 @fwrite(i8* %arraydecay69, i64 1, i64 %conv, %struct._IO_FILE* %52), !dbg !2848
  %conv72 = trunc i64 %call71 to i32, !dbg !2848
  store i32 %conv72, i32* %n2, align 4, !dbg !2849
  %53 = load i32, i32* %n, align 4, !dbg !2850
  %54 = load i32, i32* %n2, align 4, !dbg !2852
  %cmp73 = icmp ne i32 %53, %54, !dbg !2853
  br i1 %cmp73, label %if.then79, label %lor.lhs.false75, !dbg !2854

lor.lhs.false75:                                  ; preds = %if.then65
  %55 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2855
  %handle76 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %55, i32 0, i32 0, !dbg !2857
  %56 = load %struct._IO_FILE*, %struct._IO_FILE** %handle76, align 8, !dbg !2857
  %call77 = call i32 @ferror(%struct._IO_FILE* %56) #10, !dbg !2858
  %tobool78 = icmp ne i32 %call77, 0, !dbg !2858
  br i1 %tobool78, label %if.then79, label %if.end89, !dbg !2859

if.then79:                                        ; preds = %lor.lhs.false75, %if.then65
  %57 = load i32*, i32** %bzerror.addr, align 8, !dbg !2860
  %cmp80 = icmp ne i32* %57, null, !dbg !2860
  br i1 %cmp80, label %if.then82, label %if.end83, !dbg !2864

if.then82:                                        ; preds = %if.then79
  %58 = load i32*, i32** %bzerror.addr, align 8, !dbg !2865
  store i32 -6, i32* %58, align 4, !dbg !2865
  br label %if.end83, !dbg !2865

if.end83:                                         ; preds = %if.then82, %if.then79
  %59 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2867
  %cmp84 = icmp ne %struct.bzFile* %59, null, !dbg !2867
  br i1 %cmp84, label %if.then86, label %if.end88, !dbg !2867

if.then86:                                        ; preds = %if.end83
  %60 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2870
  %lastErr87 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %60, i32 0, i32 5, !dbg !2870
  store i32 -6, i32* %lastErr87, align 8, !dbg !2870
  br label %if.end88, !dbg !2870

if.end88:                                         ; preds = %if.then86, %if.end83
  br label %return, !dbg !2872

if.end89:                                         ; preds = %lor.lhs.false75
  br label %if.end90, !dbg !2874

if.end90:                                         ; preds = %if.end89, %if.end61
  %61 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2875
  %strm91 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %61, i32 0, i32 4, !dbg !2877
  %avail_in92 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm91, i32 0, i32 1, !dbg !2878
  %62 = load i32, i32* %avail_in92, align 8, !dbg !2878
  %cmp93 = icmp eq i32 %62, 0, !dbg !2879
  br i1 %cmp93, label %if.then95, label %if.end105, !dbg !2880

if.then95:                                        ; preds = %if.end90
  %63 = load i32*, i32** %bzerror.addr, align 8, !dbg !2881
  %cmp96 = icmp ne i32* %63, null, !dbg !2881
  br i1 %cmp96, label %if.then98, label %if.end99, !dbg !2885

if.then98:                                        ; preds = %if.then95
  %64 = load i32*, i32** %bzerror.addr, align 8, !dbg !2886
  store i32 0, i32* %64, align 4, !dbg !2886
  br label %if.end99, !dbg !2886

if.end99:                                         ; preds = %if.then98, %if.then95
  %65 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2888
  %cmp100 = icmp ne %struct.bzFile* %65, null, !dbg !2888
  br i1 %cmp100, label %if.then102, label %if.end104, !dbg !2888

if.then102:                                       ; preds = %if.end99
  %66 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2891
  %lastErr103 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %66, i32 0, i32 5, !dbg !2891
  store i32 0, i32* %lastErr103, align 8, !dbg !2891
  br label %if.end104, !dbg !2891

if.end104:                                        ; preds = %if.then102, %if.end99
  br label %return, !dbg !2893

if.end105:                                        ; preds = %if.end90
  br label %while.body, !dbg !2895

return:                                           ; preds = %if.end104, %if.end88, %if.end60, %if.end44, %if.end34, %if.end24, %if.end15
  ret void, !dbg !2897
}

declare i64 @fwrite(i8*, i64, i64, %struct._IO_FILE*) #2

; Function Attrs: nounwind uwtable
define void @BZ2_bzWriteClose(i32* %bzerror, i8* %b, i32 %abandon, i32* %nbytes_in, i32* %nbytes_out) #0 !dbg !163 {
entry:
  %bzerror.addr = alloca i32*, align 8
  %b.addr = alloca i8*, align 8
  %abandon.addr = alloca i32, align 4
  %nbytes_in.addr = alloca i32*, align 8
  %nbytes_out.addr = alloca i32*, align 8
  store i32* %bzerror, i32** %bzerror.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %bzerror.addr, metadata !2898, metadata !392), !dbg !2899
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !2900, metadata !392), !dbg !2901
  store i32 %abandon, i32* %abandon.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %abandon.addr, metadata !2902, metadata !392), !dbg !2903
  store i32* %nbytes_in, i32** %nbytes_in.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %nbytes_in.addr, metadata !2904, metadata !392), !dbg !2905
  store i32* %nbytes_out, i32** %nbytes_out.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %nbytes_out.addr, metadata !2906, metadata !392), !dbg !2907
  %0 = load i32*, i32** %bzerror.addr, align 8, !dbg !2908
  %1 = load i8*, i8** %b.addr, align 8, !dbg !2909
  %2 = load i32, i32* %abandon.addr, align 4, !dbg !2910
  %3 = load i32*, i32** %nbytes_in.addr, align 8, !dbg !2911
  %4 = load i32*, i32** %nbytes_out.addr, align 8, !dbg !2912
  call void @BZ2_bzWriteClose64(i32* %0, i8* %1, i32 %2, i32* %3, i32* null, i32* %4, i32* null), !dbg !2913
  ret void, !dbg !2914
}

; Function Attrs: nounwind uwtable
define void @BZ2_bzWriteClose64(i32* %bzerror, i8* %b, i32 %abandon, i32* %nbytes_in_lo32, i32* %nbytes_in_hi32, i32* %nbytes_out_lo32, i32* %nbytes_out_hi32) #0 !dbg !167 {
entry:
  %bzerror.addr = alloca i32*, align 8
  %b.addr = alloca i8*, align 8
  %abandon.addr = alloca i32, align 4
  %nbytes_in_lo32.addr = alloca i32*, align 8
  %nbytes_in_hi32.addr = alloca i32*, align 8
  %nbytes_out_lo32.addr = alloca i32*, align 8
  %nbytes_out_hi32.addr = alloca i32*, align 8
  %n = alloca i32, align 4
  %n2 = alloca i32, align 4
  %ret = alloca i32, align 4
  %bzf = alloca %struct.bzFile*, align 8
  store i32* %bzerror, i32** %bzerror.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %bzerror.addr, metadata !2915, metadata !392), !dbg !2916
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !2917, metadata !392), !dbg !2918
  store i32 %abandon, i32* %abandon.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %abandon.addr, metadata !2919, metadata !392), !dbg !2920
  store i32* %nbytes_in_lo32, i32** %nbytes_in_lo32.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %nbytes_in_lo32.addr, metadata !2921, metadata !392), !dbg !2922
  store i32* %nbytes_in_hi32, i32** %nbytes_in_hi32.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %nbytes_in_hi32.addr, metadata !2923, metadata !392), !dbg !2924
  store i32* %nbytes_out_lo32, i32** %nbytes_out_lo32.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %nbytes_out_lo32.addr, metadata !2925, metadata !392), !dbg !2926
  store i32* %nbytes_out_hi32, i32** %nbytes_out_hi32.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %nbytes_out_hi32.addr, metadata !2927, metadata !392), !dbg !2928
  call void @llvm.dbg.declare(metadata i32* %n, metadata !2929, metadata !392), !dbg !2930
  call void @llvm.dbg.declare(metadata i32* %n2, metadata !2931, metadata !392), !dbg !2932
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !2933, metadata !392), !dbg !2934
  call void @llvm.dbg.declare(metadata %struct.bzFile** %bzf, metadata !2935, metadata !392), !dbg !2936
  %0 = load i8*, i8** %b.addr, align 8, !dbg !2937
  %1 = bitcast i8* %0 to %struct.bzFile*, !dbg !2938
  store %struct.bzFile* %1, %struct.bzFile** %bzf, align 8, !dbg !2936
  %2 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2939
  %cmp = icmp eq %struct.bzFile* %2, null, !dbg !2941
  br i1 %cmp, label %if.then, label %if.end6, !dbg !2942

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %bzerror.addr, align 8, !dbg !2943
  %cmp1 = icmp ne i32* %3, null, !dbg !2943
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !2947

if.then2:                                         ; preds = %if.then
  %4 = load i32*, i32** %bzerror.addr, align 8, !dbg !2948
  store i32 0, i32* %4, align 4, !dbg !2948
  br label %if.end, !dbg !2948

if.end:                                           ; preds = %if.then2, %if.then
  %5 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2950
  %cmp3 = icmp ne %struct.bzFile* %5, null, !dbg !2950
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !2950

if.then4:                                         ; preds = %if.end
  %6 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2953
  %lastErr = getelementptr inbounds %struct.bzFile, %struct.bzFile* %6, i32 0, i32 5, !dbg !2953
  store i32 0, i32* %lastErr, align 8, !dbg !2953
  br label %if.end5, !dbg !2953

if.end5:                                          ; preds = %if.then4, %if.end
  br label %return, !dbg !2955

if.end6:                                          ; preds = %entry
  %7 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2957
  %writing = getelementptr inbounds %struct.bzFile, %struct.bzFile* %7, i32 0, i32 3, !dbg !2959
  %8 = load i8, i8* %writing, align 4, !dbg !2959
  %tobool = icmp ne i8 %8, 0, !dbg !2960
  br i1 %tobool, label %if.end15, label %if.then7, !dbg !2961

if.then7:                                         ; preds = %if.end6
  %9 = load i32*, i32** %bzerror.addr, align 8, !dbg !2962
  %cmp8 = icmp ne i32* %9, null, !dbg !2962
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !2966

if.then9:                                         ; preds = %if.then7
  %10 = load i32*, i32** %bzerror.addr, align 8, !dbg !2967
  store i32 -1, i32* %10, align 4, !dbg !2967
  br label %if.end10, !dbg !2967

if.end10:                                         ; preds = %if.then9, %if.then7
  %11 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2969
  %cmp11 = icmp ne %struct.bzFile* %11, null, !dbg !2969
  br i1 %cmp11, label %if.then12, label %if.end14, !dbg !2969

if.then12:                                        ; preds = %if.end10
  %12 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2972
  %lastErr13 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %12, i32 0, i32 5, !dbg !2972
  store i32 -1, i32* %lastErr13, align 8, !dbg !2972
  br label %if.end14, !dbg !2972

if.end14:                                         ; preds = %if.then12, %if.end10
  br label %return, !dbg !2974

if.end15:                                         ; preds = %if.end6
  %13 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2976
  %handle = getelementptr inbounds %struct.bzFile, %struct.bzFile* %13, i32 0, i32 0, !dbg !2978
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** %handle, align 8, !dbg !2978
  %call = call i32 @ferror(%struct._IO_FILE* %14) #10, !dbg !2979
  %tobool16 = icmp ne i32 %call, 0, !dbg !2979
  br i1 %tobool16, label %if.then17, label %if.end25, !dbg !2980

if.then17:                                        ; preds = %if.end15
  %15 = load i32*, i32** %bzerror.addr, align 8, !dbg !2981
  %cmp18 = icmp ne i32* %15, null, !dbg !2981
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !2985

if.then19:                                        ; preds = %if.then17
  %16 = load i32*, i32** %bzerror.addr, align 8, !dbg !2986
  store i32 -6, i32* %16, align 4, !dbg !2986
  br label %if.end20, !dbg !2986

if.end20:                                         ; preds = %if.then19, %if.then17
  %17 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2988
  %cmp21 = icmp ne %struct.bzFile* %17, null, !dbg !2988
  br i1 %cmp21, label %if.then22, label %if.end24, !dbg !2988

if.then22:                                        ; preds = %if.end20
  %18 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !2991
  %lastErr23 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %18, i32 0, i32 5, !dbg !2991
  store i32 -6, i32* %lastErr23, align 8, !dbg !2991
  br label %if.end24, !dbg !2991

if.end24:                                         ; preds = %if.then22, %if.end20
  br label %return, !dbg !2993

if.end25:                                         ; preds = %if.end15
  %19 = load i32*, i32** %nbytes_in_lo32.addr, align 8, !dbg !2995
  %cmp26 = icmp ne i32* %19, null, !dbg !2997
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !2998

if.then27:                                        ; preds = %if.end25
  %20 = load i32*, i32** %nbytes_in_lo32.addr, align 8, !dbg !2999
  store i32 0, i32* %20, align 4, !dbg !3001
  br label %if.end28, !dbg !3002

if.end28:                                         ; preds = %if.then27, %if.end25
  %21 = load i32*, i32** %nbytes_in_hi32.addr, align 8, !dbg !3003
  %cmp29 = icmp ne i32* %21, null, !dbg !3005
  br i1 %cmp29, label %if.then30, label %if.end31, !dbg !3006

if.then30:                                        ; preds = %if.end28
  %22 = load i32*, i32** %nbytes_in_hi32.addr, align 8, !dbg !3007
  store i32 0, i32* %22, align 4, !dbg !3009
  br label %if.end31, !dbg !3010

if.end31:                                         ; preds = %if.then30, %if.end28
  %23 = load i32*, i32** %nbytes_out_lo32.addr, align 8, !dbg !3011
  %cmp32 = icmp ne i32* %23, null, !dbg !3013
  br i1 %cmp32, label %if.then33, label %if.end34, !dbg !3014

if.then33:                                        ; preds = %if.end31
  %24 = load i32*, i32** %nbytes_out_lo32.addr, align 8, !dbg !3015
  store i32 0, i32* %24, align 4, !dbg !3017
  br label %if.end34, !dbg !3018

if.end34:                                         ; preds = %if.then33, %if.end31
  %25 = load i32*, i32** %nbytes_out_hi32.addr, align 8, !dbg !3019
  %cmp35 = icmp ne i32* %25, null, !dbg !3021
  br i1 %cmp35, label %if.then36, label %if.end37, !dbg !3022

if.then36:                                        ; preds = %if.end34
  %26 = load i32*, i32** %nbytes_out_hi32.addr, align 8, !dbg !3023
  store i32 0, i32* %26, align 4, !dbg !3025
  br label %if.end37, !dbg !3026

if.end37:                                         ; preds = %if.then36, %if.end34
  %27 = load i32, i32* %abandon.addr, align 4, !dbg !3027
  %tobool38 = icmp ne i32 %27, 0, !dbg !3027
  br i1 %tobool38, label %if.end89, label %land.lhs.true, !dbg !3029

land.lhs.true:                                    ; preds = %if.end37
  %28 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3030
  %lastErr39 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %28, i32 0, i32 5, !dbg !3032
  %29 = load i32, i32* %lastErr39, align 8, !dbg !3032
  %cmp40 = icmp eq i32 %29, 0, !dbg !3033
  br i1 %cmp40, label %if.then41, label %if.end89, !dbg !3034

if.then41:                                        ; preds = %land.lhs.true
  br label %while.body, !dbg !3035

while.body:                                       ; preds = %if.then41, %if.end88
  %30 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3037
  %strm = getelementptr inbounds %struct.bzFile, %struct.bzFile* %30, i32 0, i32 4, !dbg !3039
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 5, !dbg !3040
  store i32 5000, i32* %avail_out, align 8, !dbg !3041
  %31 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3042
  %buf = getelementptr inbounds %struct.bzFile, %struct.bzFile* %31, i32 0, i32 1, !dbg !3043
  %arraydecay = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i32 0, i32 0, !dbg !3042
  %32 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3044
  %strm42 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %32, i32 0, i32 4, !dbg !3045
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm42, i32 0, i32 4, !dbg !3046
  store i8* %arraydecay, i8** %next_out, align 8, !dbg !3047
  %33 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3048
  %strm43 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %33, i32 0, i32 4, !dbg !3049
  %call44 = call i32 @BZ2_bzCompress(%struct.bz_stream* %strm43, i32 2), !dbg !3050
  store i32 %call44, i32* %ret, align 4, !dbg !3051
  %34 = load i32, i32* %ret, align 4, !dbg !3052
  %cmp45 = icmp ne i32 %34, 3, !dbg !3054
  br i1 %cmp45, label %land.lhs.true46, label %if.end56, !dbg !3055

land.lhs.true46:                                  ; preds = %while.body
  %35 = load i32, i32* %ret, align 4, !dbg !3056
  %cmp47 = icmp ne i32 %35, 4, !dbg !3058
  br i1 %cmp47, label %if.then48, label %if.end56, !dbg !3059

if.then48:                                        ; preds = %land.lhs.true46
  %36 = load i32*, i32** %bzerror.addr, align 8, !dbg !3060
  %cmp49 = icmp ne i32* %36, null, !dbg !3060
  br i1 %cmp49, label %if.then50, label %if.end51, !dbg !3064

if.then50:                                        ; preds = %if.then48
  %37 = load i32, i32* %ret, align 4, !dbg !3065
  %38 = load i32*, i32** %bzerror.addr, align 8, !dbg !3065
  store i32 %37, i32* %38, align 4, !dbg !3065
  br label %if.end51, !dbg !3065

if.end51:                                         ; preds = %if.then50, %if.then48
  %39 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3067
  %cmp52 = icmp ne %struct.bzFile* %39, null, !dbg !3067
  br i1 %cmp52, label %if.then53, label %if.end55, !dbg !3067

if.then53:                                        ; preds = %if.end51
  %40 = load i32, i32* %ret, align 4, !dbg !3070
  %41 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3070
  %lastErr54 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %41, i32 0, i32 5, !dbg !3070
  store i32 %40, i32* %lastErr54, align 8, !dbg !3070
  br label %if.end55, !dbg !3070

if.end55:                                         ; preds = %if.then53, %if.end51
  br label %return, !dbg !3072

if.end56:                                         ; preds = %land.lhs.true46, %while.body
  %42 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3074
  %strm57 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %42, i32 0, i32 4, !dbg !3076
  %avail_out58 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm57, i32 0, i32 5, !dbg !3077
  %43 = load i32, i32* %avail_out58, align 8, !dbg !3077
  %cmp59 = icmp ult i32 %43, 5000, !dbg !3078
  br i1 %cmp59, label %if.then60, label %if.end84, !dbg !3079

if.then60:                                        ; preds = %if.end56
  %44 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3080
  %strm61 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %44, i32 0, i32 4, !dbg !3082
  %avail_out62 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm61, i32 0, i32 5, !dbg !3083
  %45 = load i32, i32* %avail_out62, align 8, !dbg !3083
  %sub = sub i32 5000, %45, !dbg !3084
  store i32 %sub, i32* %n, align 4, !dbg !3085
  %46 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3086
  %buf63 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %46, i32 0, i32 1, !dbg !3087
  %arraydecay64 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf63, i32 0, i32 0, !dbg !3088
  %47 = load i32, i32* %n, align 4, !dbg !3089
  %conv = sext i32 %47 to i64, !dbg !3089
  %48 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3090
  %handle65 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %48, i32 0, i32 0, !dbg !3091
  %49 = load %struct._IO_FILE*, %struct._IO_FILE** %handle65, align 8, !dbg !3091
  %call66 = call i64 @fwrite(i8* %arraydecay64, i64 1, i64 %conv, %struct._IO_FILE* %49), !dbg !3092
  %conv67 = trunc i64 %call66 to i32, !dbg !3092
  store i32 %conv67, i32* %n2, align 4, !dbg !3093
  %50 = load i32, i32* %n, align 4, !dbg !3094
  %51 = load i32, i32* %n2, align 4, !dbg !3096
  %cmp68 = icmp ne i32 %50, %51, !dbg !3097
  br i1 %cmp68, label %if.then73, label %lor.lhs.false, !dbg !3098

lor.lhs.false:                                    ; preds = %if.then60
  %52 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3099
  %handle70 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %52, i32 0, i32 0, !dbg !3101
  %53 = load %struct._IO_FILE*, %struct._IO_FILE** %handle70, align 8, !dbg !3101
  %call71 = call i32 @ferror(%struct._IO_FILE* %53) #10, !dbg !3102
  %tobool72 = icmp ne i32 %call71, 0, !dbg !3102
  br i1 %tobool72, label %if.then73, label %if.end83, !dbg !3103

if.then73:                                        ; preds = %lor.lhs.false, %if.then60
  %54 = load i32*, i32** %bzerror.addr, align 8, !dbg !3104
  %cmp74 = icmp ne i32* %54, null, !dbg !3104
  br i1 %cmp74, label %if.then76, label %if.end77, !dbg !3108

if.then76:                                        ; preds = %if.then73
  %55 = load i32*, i32** %bzerror.addr, align 8, !dbg !3109
  store i32 -6, i32* %55, align 4, !dbg !3109
  br label %if.end77, !dbg !3109

if.end77:                                         ; preds = %if.then76, %if.then73
  %56 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3111
  %cmp78 = icmp ne %struct.bzFile* %56, null, !dbg !3111
  br i1 %cmp78, label %if.then80, label %if.end82, !dbg !3111

if.then80:                                        ; preds = %if.end77
  %57 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3114
  %lastErr81 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %57, i32 0, i32 5, !dbg !3114
  store i32 -6, i32* %lastErr81, align 8, !dbg !3114
  br label %if.end82, !dbg !3114

if.end82:                                         ; preds = %if.then80, %if.end77
  br label %return, !dbg !3116

if.end83:                                         ; preds = %lor.lhs.false
  br label %if.end84, !dbg !3118

if.end84:                                         ; preds = %if.end83, %if.end56
  %58 = load i32, i32* %ret, align 4, !dbg !3119
  %cmp85 = icmp eq i32 %58, 4, !dbg !3121
  br i1 %cmp85, label %if.then87, label %if.end88, !dbg !3122

if.then87:                                        ; preds = %if.end84
  br label %while.end, !dbg !3123

if.end88:                                         ; preds = %if.end84
  br label %while.body, !dbg !3125

while.end:                                        ; preds = %if.then87
  br label %if.end89, !dbg !3127

if.end89:                                         ; preds = %while.end, %land.lhs.true, %if.end37
  %59 = load i32, i32* %abandon.addr, align 4, !dbg !3128
  %tobool90 = icmp ne i32 %59, 0, !dbg !3128
  br i1 %tobool90, label %if.end112, label %land.lhs.true91, !dbg !3130

land.lhs.true91:                                  ; preds = %if.end89
  %60 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3131
  %handle92 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %60, i32 0, i32 0, !dbg !3133
  %61 = load %struct._IO_FILE*, %struct._IO_FILE** %handle92, align 8, !dbg !3133
  %call93 = call i32 @ferror(%struct._IO_FILE* %61) #10, !dbg !3134
  %tobool94 = icmp ne i32 %call93, 0, !dbg !3134
  br i1 %tobool94, label %if.end112, label %if.then95, !dbg !3135

if.then95:                                        ; preds = %land.lhs.true91
  %62 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3136
  %handle96 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %62, i32 0, i32 0, !dbg !3138
  %63 = load %struct._IO_FILE*, %struct._IO_FILE** %handle96, align 8, !dbg !3138
  %call97 = call i32 @fflush(%struct._IO_FILE* %63), !dbg !3139
  %64 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3140
  %handle98 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %64, i32 0, i32 0, !dbg !3142
  %65 = load %struct._IO_FILE*, %struct._IO_FILE** %handle98, align 8, !dbg !3142
  %call99 = call i32 @ferror(%struct._IO_FILE* %65) #10, !dbg !3143
  %tobool100 = icmp ne i32 %call99, 0, !dbg !3143
  br i1 %tobool100, label %if.then101, label %if.end111, !dbg !3144

if.then101:                                       ; preds = %if.then95
  %66 = load i32*, i32** %bzerror.addr, align 8, !dbg !3145
  %cmp102 = icmp ne i32* %66, null, !dbg !3145
  br i1 %cmp102, label %if.then104, label %if.end105, !dbg !3149

if.then104:                                       ; preds = %if.then101
  %67 = load i32*, i32** %bzerror.addr, align 8, !dbg !3150
  store i32 -6, i32* %67, align 4, !dbg !3150
  br label %if.end105, !dbg !3150

if.end105:                                        ; preds = %if.then104, %if.then101
  %68 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3152
  %cmp106 = icmp ne %struct.bzFile* %68, null, !dbg !3152
  br i1 %cmp106, label %if.then108, label %if.end110, !dbg !3152

if.then108:                                       ; preds = %if.end105
  %69 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3155
  %lastErr109 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %69, i32 0, i32 5, !dbg !3155
  store i32 -6, i32* %lastErr109, align 8, !dbg !3155
  br label %if.end110, !dbg !3155

if.end110:                                        ; preds = %if.then108, %if.end105
  br label %return, !dbg !3157

if.end111:                                        ; preds = %if.then95
  br label %if.end112, !dbg !3159

if.end112:                                        ; preds = %if.end111, %land.lhs.true91, %if.end89
  %70 = load i32*, i32** %nbytes_in_lo32.addr, align 8, !dbg !3160
  %cmp113 = icmp ne i32* %70, null, !dbg !3162
  br i1 %cmp113, label %if.then115, label %if.end117, !dbg !3163

if.then115:                                       ; preds = %if.end112
  %71 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3164
  %strm116 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %71, i32 0, i32 4, !dbg !3165
  %total_in_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm116, i32 0, i32 2, !dbg !3166
  %72 = load i32, i32* %total_in_lo32, align 4, !dbg !3166
  %73 = load i32*, i32** %nbytes_in_lo32.addr, align 8, !dbg !3167
  store i32 %72, i32* %73, align 4, !dbg !3168
  br label %if.end117, !dbg !3169

if.end117:                                        ; preds = %if.then115, %if.end112
  %74 = load i32*, i32** %nbytes_in_hi32.addr, align 8, !dbg !3170
  %cmp118 = icmp ne i32* %74, null, !dbg !3172
  br i1 %cmp118, label %if.then120, label %if.end122, !dbg !3173

if.then120:                                       ; preds = %if.end117
  %75 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3174
  %strm121 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %75, i32 0, i32 4, !dbg !3175
  %total_in_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm121, i32 0, i32 3, !dbg !3176
  %76 = load i32, i32* %total_in_hi32, align 8, !dbg !3176
  %77 = load i32*, i32** %nbytes_in_hi32.addr, align 8, !dbg !3177
  store i32 %76, i32* %77, align 4, !dbg !3178
  br label %if.end122, !dbg !3179

if.end122:                                        ; preds = %if.then120, %if.end117
  %78 = load i32*, i32** %nbytes_out_lo32.addr, align 8, !dbg !3180
  %cmp123 = icmp ne i32* %78, null, !dbg !3182
  br i1 %cmp123, label %if.then125, label %if.end127, !dbg !3183

if.then125:                                       ; preds = %if.end122
  %79 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3184
  %strm126 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %79, i32 0, i32 4, !dbg !3185
  %total_out_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm126, i32 0, i32 6, !dbg !3186
  %80 = load i32, i32* %total_out_lo32, align 4, !dbg !3186
  %81 = load i32*, i32** %nbytes_out_lo32.addr, align 8, !dbg !3187
  store i32 %80, i32* %81, align 4, !dbg !3188
  br label %if.end127, !dbg !3189

if.end127:                                        ; preds = %if.then125, %if.end122
  %82 = load i32*, i32** %nbytes_out_hi32.addr, align 8, !dbg !3190
  %cmp128 = icmp ne i32* %82, null, !dbg !3192
  br i1 %cmp128, label %if.then130, label %if.end132, !dbg !3193

if.then130:                                       ; preds = %if.end127
  %83 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3194
  %strm131 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %83, i32 0, i32 4, !dbg !3195
  %total_out_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm131, i32 0, i32 7, !dbg !3196
  %84 = load i32, i32* %total_out_hi32, align 8, !dbg !3196
  %85 = load i32*, i32** %nbytes_out_hi32.addr, align 8, !dbg !3197
  store i32 %84, i32* %85, align 4, !dbg !3198
  br label %if.end132, !dbg !3199

if.end132:                                        ; preds = %if.then130, %if.end127
  %86 = load i32*, i32** %bzerror.addr, align 8, !dbg !3200
  %cmp133 = icmp ne i32* %86, null, !dbg !3200
  br i1 %cmp133, label %if.then135, label %if.end136, !dbg !3203

if.then135:                                       ; preds = %if.end132
  %87 = load i32*, i32** %bzerror.addr, align 8, !dbg !3204
  store i32 0, i32* %87, align 4, !dbg !3204
  br label %if.end136, !dbg !3204

if.end136:                                        ; preds = %if.then135, %if.end132
  %88 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3206
  %cmp137 = icmp ne %struct.bzFile* %88, null, !dbg !3206
  br i1 %cmp137, label %if.then139, label %if.end141, !dbg !3206

if.then139:                                       ; preds = %if.end136
  %89 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3209
  %lastErr140 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %89, i32 0, i32 5, !dbg !3209
  store i32 0, i32* %lastErr140, align 8, !dbg !3209
  br label %if.end141, !dbg !3209

if.end141:                                        ; preds = %if.then139, %if.end136
  %90 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3211
  %strm142 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %90, i32 0, i32 4, !dbg !3212
  %call143 = call i32 @BZ2_bzCompressEnd(%struct.bz_stream* %strm142), !dbg !3213
  %91 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3214
  %92 = bitcast %struct.bzFile* %91 to i8*, !dbg !3214
  call void @free(i8* %92) #10, !dbg !3215
  br label %return, !dbg !3216

return:                                           ; preds = %if.end141, %if.end110, %if.end82, %if.end55, %if.end24, %if.end14, %if.end5
  ret void, !dbg !3217
}

declare i32 @fflush(%struct._IO_FILE*) #2

; Function Attrs: nounwind uwtable
define i8* @BZ2_bzReadOpen(i32* %bzerror, %struct._IO_FILE* %f, i32 %verbosity, i32 %small, i8* %unused, i32 %nUnused) #0 !dbg !170 {
entry:
  %retval = alloca i8*, align 8
  %bzerror.addr = alloca i32*, align 8
  %f.addr = alloca %struct._IO_FILE*, align 8
  %verbosity.addr = alloca i32, align 4
  %small.addr = alloca i32, align 4
  %unused.addr = alloca i8*, align 8
  %nUnused.addr = alloca i32, align 4
  %bzf = alloca %struct.bzFile*, align 8
  %ret = alloca i32, align 4
  store i32* %bzerror, i32** %bzerror.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %bzerror.addr, metadata !3219, metadata !392), !dbg !3220
  store %struct._IO_FILE* %f, %struct._IO_FILE** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %f.addr, metadata !3221, metadata !392), !dbg !3222
  store i32 %verbosity, i32* %verbosity.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %verbosity.addr, metadata !3223, metadata !392), !dbg !3224
  store i32 %small, i32* %small.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %small.addr, metadata !3225, metadata !392), !dbg !3226
  store i8* %unused, i8** %unused.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %unused.addr, metadata !3227, metadata !392), !dbg !3228
  store i32 %nUnused, i32* %nUnused.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %nUnused.addr, metadata !3229, metadata !392), !dbg !3230
  call void @llvm.dbg.declare(metadata %struct.bzFile** %bzf, metadata !3231, metadata !392), !dbg !3232
  store %struct.bzFile* null, %struct.bzFile** %bzf, align 8, !dbg !3232
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3233, metadata !392), !dbg !3234
  %0 = load i32*, i32** %bzerror.addr, align 8, !dbg !3235
  %cmp = icmp ne i32* %0, null, !dbg !3235
  br i1 %cmp, label %if.then, label %if.end, !dbg !3238

if.then:                                          ; preds = %entry
  %1 = load i32*, i32** %bzerror.addr, align 8, !dbg !3239
  store i32 0, i32* %1, align 4, !dbg !3239
  br label %if.end, !dbg !3239

if.end:                                           ; preds = %if.then, %entry
  %2 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3241
  %cmp1 = icmp ne %struct.bzFile* %2, null, !dbg !3241
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !3241

if.then2:                                         ; preds = %if.end
  %3 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3244
  %lastErr = getelementptr inbounds %struct.bzFile, %struct.bzFile* %3, i32 0, i32 5, !dbg !3244
  store i32 0, i32* %lastErr, align 8, !dbg !3244
  br label %if.end3, !dbg !3244

if.end3:                                          ; preds = %if.then2, %if.end
  %4 = load %struct._IO_FILE*, %struct._IO_FILE** %f.addr, align 8, !dbg !3246
  %cmp4 = icmp eq %struct._IO_FILE* %4, null, !dbg !3248
  br i1 %cmp4, label %if.then21, label %lor.lhs.false, !dbg !3249

lor.lhs.false:                                    ; preds = %if.end3
  %5 = load i32, i32* %small.addr, align 4, !dbg !3250
  %cmp5 = icmp ne i32 %5, 0, !dbg !3251
  br i1 %cmp5, label %land.lhs.true, label %lor.lhs.false7, !dbg !3252

land.lhs.true:                                    ; preds = %lor.lhs.false
  %6 = load i32, i32* %small.addr, align 4, !dbg !3253
  %cmp6 = icmp ne i32 %6, 1, !dbg !3255
  br i1 %cmp6, label %if.then21, label %lor.lhs.false7, !dbg !3256

lor.lhs.false7:                                   ; preds = %land.lhs.true, %lor.lhs.false
  %7 = load i32, i32* %verbosity.addr, align 4, !dbg !3257
  %cmp8 = icmp slt i32 %7, 0, !dbg !3258
  br i1 %cmp8, label %if.then21, label %lor.lhs.false9, !dbg !3259

lor.lhs.false9:                                   ; preds = %lor.lhs.false7
  %8 = load i32, i32* %verbosity.addr, align 4, !dbg !3260
  %cmp10 = icmp sgt i32 %8, 4, !dbg !3261
  br i1 %cmp10, label %if.then21, label %lor.lhs.false11, !dbg !3262

lor.lhs.false11:                                  ; preds = %lor.lhs.false9
  %9 = load i8*, i8** %unused.addr, align 8, !dbg !3263
  %cmp12 = icmp eq i8* %9, null, !dbg !3264
  br i1 %cmp12, label %land.lhs.true13, label %lor.lhs.false15, !dbg !3265

land.lhs.true13:                                  ; preds = %lor.lhs.false11
  %10 = load i32, i32* %nUnused.addr, align 4, !dbg !3266
  %cmp14 = icmp ne i32 %10, 0, !dbg !3267
  br i1 %cmp14, label %if.then21, label %lor.lhs.false15, !dbg !3268

lor.lhs.false15:                                  ; preds = %land.lhs.true13, %lor.lhs.false11
  %11 = load i8*, i8** %unused.addr, align 8, !dbg !3269
  %cmp16 = icmp ne i8* %11, null, !dbg !3270
  br i1 %cmp16, label %land.lhs.true17, label %if.end29, !dbg !3271

land.lhs.true17:                                  ; preds = %lor.lhs.false15
  %12 = load i32, i32* %nUnused.addr, align 4, !dbg !3272
  %cmp18 = icmp slt i32 %12, 0, !dbg !3273
  br i1 %cmp18, label %if.then21, label %lor.lhs.false19, !dbg !3274

lor.lhs.false19:                                  ; preds = %land.lhs.true17
  %13 = load i32, i32* %nUnused.addr, align 4, !dbg !3275
  %cmp20 = icmp sgt i32 %13, 5000, !dbg !3277
  br i1 %cmp20, label %if.then21, label %if.end29, !dbg !3278

if.then21:                                        ; preds = %lor.lhs.false19, %land.lhs.true17, %land.lhs.true13, %lor.lhs.false9, %lor.lhs.false7, %land.lhs.true, %if.end3
  %14 = load i32*, i32** %bzerror.addr, align 8, !dbg !3280
  %cmp22 = icmp ne i32* %14, null, !dbg !3280
  br i1 %cmp22, label %if.then23, label %if.end24, !dbg !3284

if.then23:                                        ; preds = %if.then21
  %15 = load i32*, i32** %bzerror.addr, align 8, !dbg !3285
  store i32 -2, i32* %15, align 4, !dbg !3285
  br label %if.end24, !dbg !3285

if.end24:                                         ; preds = %if.then23, %if.then21
  %16 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3287
  %cmp25 = icmp ne %struct.bzFile* %16, null, !dbg !3287
  br i1 %cmp25, label %if.then26, label %if.end28, !dbg !3287

if.then26:                                        ; preds = %if.end24
  %17 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3290
  %lastErr27 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %17, i32 0, i32 5, !dbg !3290
  store i32 -2, i32* %lastErr27, align 8, !dbg !3290
  br label %if.end28, !dbg !3290

if.end28:                                         ; preds = %if.then26, %if.end24
  store i8* null, i8** %retval, align 8, !dbg !3292
  br label %return, !dbg !3292

if.end29:                                         ; preds = %lor.lhs.false19, %lor.lhs.false15
  %18 = load %struct._IO_FILE*, %struct._IO_FILE** %f.addr, align 8, !dbg !3294
  %call = call i32 @ferror(%struct._IO_FILE* %18) #10, !dbg !3296
  %tobool = icmp ne i32 %call, 0, !dbg !3296
  br i1 %tobool, label %if.then30, label %if.end38, !dbg !3297

if.then30:                                        ; preds = %if.end29
  %19 = load i32*, i32** %bzerror.addr, align 8, !dbg !3298
  %cmp31 = icmp ne i32* %19, null, !dbg !3298
  br i1 %cmp31, label %if.then32, label %if.end33, !dbg !3302

if.then32:                                        ; preds = %if.then30
  %20 = load i32*, i32** %bzerror.addr, align 8, !dbg !3303
  store i32 -6, i32* %20, align 4, !dbg !3303
  br label %if.end33, !dbg !3303

if.end33:                                         ; preds = %if.then32, %if.then30
  %21 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3305
  %cmp34 = icmp ne %struct.bzFile* %21, null, !dbg !3305
  br i1 %cmp34, label %if.then35, label %if.end37, !dbg !3305

if.then35:                                        ; preds = %if.end33
  %22 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3308
  %lastErr36 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %22, i32 0, i32 5, !dbg !3308
  store i32 -6, i32* %lastErr36, align 8, !dbg !3308
  br label %if.end37, !dbg !3308

if.end37:                                         ; preds = %if.then35, %if.end33
  store i8* null, i8** %retval, align 8, !dbg !3310
  br label %return, !dbg !3310

if.end38:                                         ; preds = %if.end29
  %call39 = call noalias i8* @malloc(i64 5104) #10, !dbg !3312
  %23 = bitcast i8* %call39 to %struct.bzFile*, !dbg !3312
  store %struct.bzFile* %23, %struct.bzFile** %bzf, align 8, !dbg !3313
  %24 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3314
  %cmp40 = icmp eq %struct.bzFile* %24, null, !dbg !3316
  br i1 %cmp40, label %if.then41, label %if.end49, !dbg !3317

if.then41:                                        ; preds = %if.end38
  %25 = load i32*, i32** %bzerror.addr, align 8, !dbg !3318
  %cmp42 = icmp ne i32* %25, null, !dbg !3318
  br i1 %cmp42, label %if.then43, label %if.end44, !dbg !3322

if.then43:                                        ; preds = %if.then41
  %26 = load i32*, i32** %bzerror.addr, align 8, !dbg !3323
  store i32 -3, i32* %26, align 4, !dbg !3323
  br label %if.end44, !dbg !3323

if.end44:                                         ; preds = %if.then43, %if.then41
  %27 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3325
  %cmp45 = icmp ne %struct.bzFile* %27, null, !dbg !3325
  br i1 %cmp45, label %if.then46, label %if.end48, !dbg !3325

if.then46:                                        ; preds = %if.end44
  %28 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3328
  %lastErr47 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %28, i32 0, i32 5, !dbg !3328
  store i32 -3, i32* %lastErr47, align 8, !dbg !3328
  br label %if.end48, !dbg !3328

if.end48:                                         ; preds = %if.then46, %if.end44
  store i8* null, i8** %retval, align 8, !dbg !3330
  br label %return, !dbg !3330

if.end49:                                         ; preds = %if.end38
  %29 = load i32*, i32** %bzerror.addr, align 8, !dbg !3332
  %cmp50 = icmp ne i32* %29, null, !dbg !3332
  br i1 %cmp50, label %if.then51, label %if.end52, !dbg !3335

if.then51:                                        ; preds = %if.end49
  %30 = load i32*, i32** %bzerror.addr, align 8, !dbg !3336
  store i32 0, i32* %30, align 4, !dbg !3336
  br label %if.end52, !dbg !3336

if.end52:                                         ; preds = %if.then51, %if.end49
  %31 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3338
  %cmp53 = icmp ne %struct.bzFile* %31, null, !dbg !3338
  br i1 %cmp53, label %if.then54, label %if.end56, !dbg !3338

if.then54:                                        ; preds = %if.end52
  %32 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3341
  %lastErr55 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %32, i32 0, i32 5, !dbg !3341
  store i32 0, i32* %lastErr55, align 8, !dbg !3341
  br label %if.end56, !dbg !3341

if.end56:                                         ; preds = %if.then54, %if.end52
  %33 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3343
  %initialisedOk = getelementptr inbounds %struct.bzFile, %struct.bzFile* %33, i32 0, i32 6, !dbg !3344
  store i8 0, i8* %initialisedOk, align 4, !dbg !3345
  %34 = load %struct._IO_FILE*, %struct._IO_FILE** %f.addr, align 8, !dbg !3346
  %35 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3347
  %handle = getelementptr inbounds %struct.bzFile, %struct.bzFile* %35, i32 0, i32 0, !dbg !3348
  store %struct._IO_FILE* %34, %struct._IO_FILE** %handle, align 8, !dbg !3349
  %36 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3350
  %bufN = getelementptr inbounds %struct.bzFile, %struct.bzFile* %36, i32 0, i32 2, !dbg !3351
  store i32 0, i32* %bufN, align 8, !dbg !3352
  %37 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3353
  %writing = getelementptr inbounds %struct.bzFile, %struct.bzFile* %37, i32 0, i32 3, !dbg !3354
  store i8 0, i8* %writing, align 4, !dbg !3355
  %38 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3356
  %strm = getelementptr inbounds %struct.bzFile, %struct.bzFile* %38, i32 0, i32 4, !dbg !3357
  %bzalloc = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 9, !dbg !3358
  store i8* (i8*, i32, i32)* null, i8* (i8*, i32, i32)** %bzalloc, align 8, !dbg !3359
  %39 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3360
  %strm57 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %39, i32 0, i32 4, !dbg !3361
  %bzfree = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm57, i32 0, i32 10, !dbg !3362
  store void (i8*, i8*)* null, void (i8*, i8*)** %bzfree, align 8, !dbg !3363
  %40 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3364
  %strm58 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %40, i32 0, i32 4, !dbg !3365
  %opaque = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm58, i32 0, i32 11, !dbg !3366
  store i8* null, i8** %opaque, align 8, !dbg !3367
  br label %while.cond, !dbg !3368

while.cond:                                       ; preds = %while.body, %if.end56
  %41 = load i32, i32* %nUnused.addr, align 4, !dbg !3369
  %cmp59 = icmp sgt i32 %41, 0, !dbg !3370
  br i1 %cmp59, label %while.body, label %while.end, !dbg !3371

while.body:                                       ; preds = %while.cond
  %42 = load i8*, i8** %unused.addr, align 8, !dbg !3372
  %43 = load i8, i8* %42, align 1, !dbg !3374
  %44 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3375
  %bufN60 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %44, i32 0, i32 2, !dbg !3376
  %45 = load i32, i32* %bufN60, align 8, !dbg !3376
  %idxprom = sext i32 %45 to i64, !dbg !3377
  %46 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3377
  %buf = getelementptr inbounds %struct.bzFile, %struct.bzFile* %46, i32 0, i32 1, !dbg !3378
  %arrayidx = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf, i64 0, i64 %idxprom, !dbg !3377
  store i8 %43, i8* %arrayidx, align 1, !dbg !3379
  %47 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3380
  %bufN61 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %47, i32 0, i32 2, !dbg !3381
  %48 = load i32, i32* %bufN61, align 8, !dbg !3382
  %inc = add nsw i32 %48, 1, !dbg !3382
  store i32 %inc, i32* %bufN61, align 8, !dbg !3382
  %49 = load i8*, i8** %unused.addr, align 8, !dbg !3383
  %add.ptr = getelementptr inbounds i8, i8* %49, i64 1, !dbg !3384
  store i8* %add.ptr, i8** %unused.addr, align 8, !dbg !3385
  %50 = load i32, i32* %nUnused.addr, align 4, !dbg !3386
  %dec = add nsw i32 %50, -1, !dbg !3386
  store i32 %dec, i32* %nUnused.addr, align 4, !dbg !3386
  br label %while.cond, !dbg !3387

while.end:                                        ; preds = %while.cond
  %51 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3389
  %strm62 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %51, i32 0, i32 4, !dbg !3390
  %52 = load i32, i32* %verbosity.addr, align 4, !dbg !3391
  %53 = load i32, i32* %small.addr, align 4, !dbg !3392
  %call63 = call i32 @BZ2_bzDecompressInit(%struct.bz_stream* %strm62, i32 %52, i32 %53), !dbg !3393
  store i32 %call63, i32* %ret, align 4, !dbg !3394
  %54 = load i32, i32* %ret, align 4, !dbg !3395
  %cmp64 = icmp ne i32 %54, 0, !dbg !3397
  br i1 %cmp64, label %if.then65, label %if.end73, !dbg !3398

if.then65:                                        ; preds = %while.end
  %55 = load i32*, i32** %bzerror.addr, align 8, !dbg !3399
  %cmp66 = icmp ne i32* %55, null, !dbg !3399
  br i1 %cmp66, label %if.then67, label %if.end68, !dbg !3403

if.then67:                                        ; preds = %if.then65
  %56 = load i32, i32* %ret, align 4, !dbg !3404
  %57 = load i32*, i32** %bzerror.addr, align 8, !dbg !3404
  store i32 %56, i32* %57, align 4, !dbg !3404
  br label %if.end68, !dbg !3404

if.end68:                                         ; preds = %if.then67, %if.then65
  %58 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3406
  %cmp69 = icmp ne %struct.bzFile* %58, null, !dbg !3406
  br i1 %cmp69, label %if.then70, label %if.end72, !dbg !3406

if.then70:                                        ; preds = %if.end68
  %59 = load i32, i32* %ret, align 4, !dbg !3409
  %60 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3409
  %lastErr71 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %60, i32 0, i32 5, !dbg !3409
  store i32 %59, i32* %lastErr71, align 8, !dbg !3409
  br label %if.end72, !dbg !3409

if.end72:                                         ; preds = %if.then70, %if.end68
  %61 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3411
  %62 = bitcast %struct.bzFile* %61 to i8*, !dbg !3411
  call void @free(i8* %62) #10, !dbg !3413
  store i8* null, i8** %retval, align 8, !dbg !3414
  br label %return, !dbg !3414

if.end73:                                         ; preds = %while.end
  %63 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3415
  %bufN74 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %63, i32 0, i32 2, !dbg !3416
  %64 = load i32, i32* %bufN74, align 8, !dbg !3416
  %65 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3417
  %strm75 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %65, i32 0, i32 4, !dbg !3418
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm75, i32 0, i32 1, !dbg !3419
  store i32 %64, i32* %avail_in, align 8, !dbg !3420
  %66 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3421
  %buf76 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %66, i32 0, i32 1, !dbg !3422
  %arraydecay = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf76, i32 0, i32 0, !dbg !3421
  %67 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3423
  %strm77 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %67, i32 0, i32 4, !dbg !3424
  %next_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm77, i32 0, i32 0, !dbg !3425
  store i8* %arraydecay, i8** %next_in, align 8, !dbg !3426
  %68 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3427
  %initialisedOk78 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %68, i32 0, i32 6, !dbg !3428
  store i8 1, i8* %initialisedOk78, align 4, !dbg !3429
  %69 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3430
  %70 = bitcast %struct.bzFile* %69 to i8*, !dbg !3430
  store i8* %70, i8** %retval, align 8, !dbg !3431
  br label %return, !dbg !3431

return:                                           ; preds = %if.end73, %if.end72, %if.end48, %if.end37, %if.end28
  %71 = load i8*, i8** %retval, align 8, !dbg !3432
  ret i8* %71, !dbg !3432
}

; Function Attrs: nounwind uwtable
define void @BZ2_bzReadClose(i32* %bzerror, i8* %b) #0 !dbg !173 {
entry:
  %bzerror.addr = alloca i32*, align 8
  %b.addr = alloca i8*, align 8
  %bzf = alloca %struct.bzFile*, align 8
  store i32* %bzerror, i32** %bzerror.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %bzerror.addr, metadata !3433, metadata !392), !dbg !3434
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !3435, metadata !392), !dbg !3436
  call void @llvm.dbg.declare(metadata %struct.bzFile** %bzf, metadata !3437, metadata !392), !dbg !3438
  %0 = load i8*, i8** %b.addr, align 8, !dbg !3439
  %1 = bitcast i8* %0 to %struct.bzFile*, !dbg !3440
  store %struct.bzFile* %1, %struct.bzFile** %bzf, align 8, !dbg !3438
  %2 = load i32*, i32** %bzerror.addr, align 8, !dbg !3441
  %cmp = icmp ne i32* %2, null, !dbg !3441
  br i1 %cmp, label %if.then, label %if.end, !dbg !3444

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %bzerror.addr, align 8, !dbg !3445
  store i32 0, i32* %3, align 4, !dbg !3445
  br label %if.end, !dbg !3445

if.end:                                           ; preds = %if.then, %entry
  %4 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3447
  %cmp1 = icmp ne %struct.bzFile* %4, null, !dbg !3447
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !3447

if.then2:                                         ; preds = %if.end
  %5 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3450
  %lastErr = getelementptr inbounds %struct.bzFile, %struct.bzFile* %5, i32 0, i32 5, !dbg !3450
  store i32 0, i32* %lastErr, align 8, !dbg !3450
  br label %if.end3, !dbg !3450

if.end3:                                          ; preds = %if.then2, %if.end
  %6 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3452
  %cmp4 = icmp eq %struct.bzFile* %6, null, !dbg !3454
  br i1 %cmp4, label %if.then5, label %if.end13, !dbg !3455

if.then5:                                         ; preds = %if.end3
  %7 = load i32*, i32** %bzerror.addr, align 8, !dbg !3456
  %cmp6 = icmp ne i32* %7, null, !dbg !3456
  br i1 %cmp6, label %if.then7, label %if.end8, !dbg !3460

if.then7:                                         ; preds = %if.then5
  %8 = load i32*, i32** %bzerror.addr, align 8, !dbg !3461
  store i32 0, i32* %8, align 4, !dbg !3461
  br label %if.end8, !dbg !3461

if.end8:                                          ; preds = %if.then7, %if.then5
  %9 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3463
  %cmp9 = icmp ne %struct.bzFile* %9, null, !dbg !3463
  br i1 %cmp9, label %if.then10, label %if.end12, !dbg !3463

if.then10:                                        ; preds = %if.end8
  %10 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3466
  %lastErr11 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %10, i32 0, i32 5, !dbg !3466
  store i32 0, i32* %lastErr11, align 8, !dbg !3466
  br label %if.end12, !dbg !3466

if.end12:                                         ; preds = %if.then10, %if.end8
  br label %return, !dbg !3468

if.end13:                                         ; preds = %if.end3
  %11 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3470
  %writing = getelementptr inbounds %struct.bzFile, %struct.bzFile* %11, i32 0, i32 3, !dbg !3472
  %12 = load i8, i8* %writing, align 4, !dbg !3472
  %tobool = icmp ne i8 %12, 0, !dbg !3470
  br i1 %tobool, label %if.then14, label %if.end22, !dbg !3473

if.then14:                                        ; preds = %if.end13
  %13 = load i32*, i32** %bzerror.addr, align 8, !dbg !3474
  %cmp15 = icmp ne i32* %13, null, !dbg !3474
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !3478

if.then16:                                        ; preds = %if.then14
  %14 = load i32*, i32** %bzerror.addr, align 8, !dbg !3479
  store i32 -1, i32* %14, align 4, !dbg !3479
  br label %if.end17, !dbg !3479

if.end17:                                         ; preds = %if.then16, %if.then14
  %15 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3481
  %cmp18 = icmp ne %struct.bzFile* %15, null, !dbg !3481
  br i1 %cmp18, label %if.then19, label %if.end21, !dbg !3481

if.then19:                                        ; preds = %if.end17
  %16 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3484
  %lastErr20 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %16, i32 0, i32 5, !dbg !3484
  store i32 -1, i32* %lastErr20, align 8, !dbg !3484
  br label %if.end21, !dbg !3484

if.end21:                                         ; preds = %if.then19, %if.end17
  br label %return, !dbg !3486

if.end22:                                         ; preds = %if.end13
  %17 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3488
  %initialisedOk = getelementptr inbounds %struct.bzFile, %struct.bzFile* %17, i32 0, i32 6, !dbg !3490
  %18 = load i8, i8* %initialisedOk, align 4, !dbg !3490
  %tobool23 = icmp ne i8 %18, 0, !dbg !3488
  br i1 %tobool23, label %if.then24, label %if.end25, !dbg !3491

if.then24:                                        ; preds = %if.end22
  %19 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3492
  %strm = getelementptr inbounds %struct.bzFile, %struct.bzFile* %19, i32 0, i32 4, !dbg !3493
  %call = call i32 @BZ2_bzDecompressEnd(%struct.bz_stream* %strm), !dbg !3494
  br label %if.end25, !dbg !3495

if.end25:                                         ; preds = %if.then24, %if.end22
  %20 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3496
  %21 = bitcast %struct.bzFile* %20 to i8*, !dbg !3496
  call void @free(i8* %21) #10, !dbg !3497
  br label %return, !dbg !3498

return:                                           ; preds = %if.end25, %if.end21, %if.end12
  ret void, !dbg !3499
}

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzRead(i32* %bzerror, i8* %b, i8* %buf, i32 %len) #0 !dbg !176 {
entry:
  %retval = alloca i32, align 4
  %bzerror.addr = alloca i32*, align 8
  %b.addr = alloca i8*, align 8
  %buf.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %n = alloca i32, align 4
  %ret = alloca i32, align 4
  %bzf = alloca %struct.bzFile*, align 8
  store i32* %bzerror, i32** %bzerror.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %bzerror.addr, metadata !3501, metadata !392), !dbg !3502
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !3503, metadata !392), !dbg !3504
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !3505, metadata !392), !dbg !3506
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !3507, metadata !392), !dbg !3508
  call void @llvm.dbg.declare(metadata i32* %n, metadata !3509, metadata !392), !dbg !3510
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3511, metadata !392), !dbg !3512
  call void @llvm.dbg.declare(metadata %struct.bzFile** %bzf, metadata !3513, metadata !392), !dbg !3514
  %0 = load i8*, i8** %b.addr, align 8, !dbg !3515
  %1 = bitcast i8* %0 to %struct.bzFile*, !dbg !3516
  store %struct.bzFile* %1, %struct.bzFile** %bzf, align 8, !dbg !3514
  %2 = load i32*, i32** %bzerror.addr, align 8, !dbg !3517
  %cmp = icmp ne i32* %2, null, !dbg !3517
  br i1 %cmp, label %if.then, label %if.end, !dbg !3520

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %bzerror.addr, align 8, !dbg !3521
  store i32 0, i32* %3, align 4, !dbg !3521
  br label %if.end, !dbg !3521

if.end:                                           ; preds = %if.then, %entry
  %4 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3523
  %cmp1 = icmp ne %struct.bzFile* %4, null, !dbg !3523
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !3523

if.then2:                                         ; preds = %if.end
  %5 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3526
  %lastErr = getelementptr inbounds %struct.bzFile, %struct.bzFile* %5, i32 0, i32 5, !dbg !3526
  store i32 0, i32* %lastErr, align 8, !dbg !3526
  br label %if.end3, !dbg !3526

if.end3:                                          ; preds = %if.then2, %if.end
  %6 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3528
  %cmp4 = icmp eq %struct.bzFile* %6, null, !dbg !3530
  br i1 %cmp4, label %if.then8, label %lor.lhs.false, !dbg !3531

lor.lhs.false:                                    ; preds = %if.end3
  %7 = load i8*, i8** %buf.addr, align 8, !dbg !3532
  %cmp5 = icmp eq i8* %7, null, !dbg !3534
  br i1 %cmp5, label %if.then8, label %lor.lhs.false6, !dbg !3535

lor.lhs.false6:                                   ; preds = %lor.lhs.false
  %8 = load i32, i32* %len.addr, align 4, !dbg !3536
  %cmp7 = icmp slt i32 %8, 0, !dbg !3538
  br i1 %cmp7, label %if.then8, label %if.end16, !dbg !3539

if.then8:                                         ; preds = %lor.lhs.false6, %lor.lhs.false, %if.end3
  %9 = load i32*, i32** %bzerror.addr, align 8, !dbg !3540
  %cmp9 = icmp ne i32* %9, null, !dbg !3540
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !3544

if.then10:                                        ; preds = %if.then8
  %10 = load i32*, i32** %bzerror.addr, align 8, !dbg !3545
  store i32 -2, i32* %10, align 4, !dbg !3545
  br label %if.end11, !dbg !3545

if.end11:                                         ; preds = %if.then10, %if.then8
  %11 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3547
  %cmp12 = icmp ne %struct.bzFile* %11, null, !dbg !3547
  br i1 %cmp12, label %if.then13, label %if.end15, !dbg !3547

if.then13:                                        ; preds = %if.end11
  %12 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3550
  %lastErr14 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %12, i32 0, i32 5, !dbg !3550
  store i32 -2, i32* %lastErr14, align 8, !dbg !3550
  br label %if.end15, !dbg !3550

if.end15:                                         ; preds = %if.then13, %if.end11
  store i32 0, i32* %retval, align 4, !dbg !3552
  br label %return, !dbg !3552

if.end16:                                         ; preds = %lor.lhs.false6
  %13 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3554
  %writing = getelementptr inbounds %struct.bzFile, %struct.bzFile* %13, i32 0, i32 3, !dbg !3556
  %14 = load i8, i8* %writing, align 4, !dbg !3556
  %tobool = icmp ne i8 %14, 0, !dbg !3554
  br i1 %tobool, label %if.then17, label %if.end25, !dbg !3557

if.then17:                                        ; preds = %if.end16
  %15 = load i32*, i32** %bzerror.addr, align 8, !dbg !3558
  %cmp18 = icmp ne i32* %15, null, !dbg !3558
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !3562

if.then19:                                        ; preds = %if.then17
  %16 = load i32*, i32** %bzerror.addr, align 8, !dbg !3563
  store i32 -1, i32* %16, align 4, !dbg !3563
  br label %if.end20, !dbg !3563

if.end20:                                         ; preds = %if.then19, %if.then17
  %17 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3565
  %cmp21 = icmp ne %struct.bzFile* %17, null, !dbg !3565
  br i1 %cmp21, label %if.then22, label %if.end24, !dbg !3565

if.then22:                                        ; preds = %if.end20
  %18 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3568
  %lastErr23 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %18, i32 0, i32 5, !dbg !3568
  store i32 -1, i32* %lastErr23, align 8, !dbg !3568
  br label %if.end24, !dbg !3568

if.end24:                                         ; preds = %if.then22, %if.end20
  store i32 0, i32* %retval, align 4, !dbg !3570
  br label %return, !dbg !3570

if.end25:                                         ; preds = %if.end16
  %19 = load i32, i32* %len.addr, align 4, !dbg !3572
  %cmp26 = icmp eq i32 %19, 0, !dbg !3574
  br i1 %cmp26, label %if.then27, label %if.end35, !dbg !3575

if.then27:                                        ; preds = %if.end25
  %20 = load i32*, i32** %bzerror.addr, align 8, !dbg !3576
  %cmp28 = icmp ne i32* %20, null, !dbg !3576
  br i1 %cmp28, label %if.then29, label %if.end30, !dbg !3580

if.then29:                                        ; preds = %if.then27
  %21 = load i32*, i32** %bzerror.addr, align 8, !dbg !3581
  store i32 0, i32* %21, align 4, !dbg !3581
  br label %if.end30, !dbg !3581

if.end30:                                         ; preds = %if.then29, %if.then27
  %22 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3583
  %cmp31 = icmp ne %struct.bzFile* %22, null, !dbg !3583
  br i1 %cmp31, label %if.then32, label %if.end34, !dbg !3583

if.then32:                                        ; preds = %if.end30
  %23 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3586
  %lastErr33 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %23, i32 0, i32 5, !dbg !3586
  store i32 0, i32* %lastErr33, align 8, !dbg !3586
  br label %if.end34, !dbg !3586

if.end34:                                         ; preds = %if.then32, %if.end30
  store i32 0, i32* %retval, align 4, !dbg !3588
  br label %return, !dbg !3588

if.end35:                                         ; preds = %if.end25
  %24 = load i32, i32* %len.addr, align 4, !dbg !3590
  %25 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3591
  %strm = getelementptr inbounds %struct.bzFile, %struct.bzFile* %25, i32 0, i32 4, !dbg !3592
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 5, !dbg !3593
  store i32 %24, i32* %avail_out, align 8, !dbg !3594
  %26 = load i8*, i8** %buf.addr, align 8, !dbg !3595
  %27 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3596
  %strm36 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %27, i32 0, i32 4, !dbg !3597
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm36, i32 0, i32 4, !dbg !3598
  store i8* %26, i8** %next_out, align 8, !dbg !3599
  br label %while.body, !dbg !3600

while.body:                                       ; preds = %if.end35, %if.end152
  %28 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3601
  %handle = getelementptr inbounds %struct.bzFile, %struct.bzFile* %28, i32 0, i32 0, !dbg !3604
  %29 = load %struct._IO_FILE*, %struct._IO_FILE** %handle, align 8, !dbg !3604
  %call = call i32 @ferror(%struct._IO_FILE* %29) #10, !dbg !3605
  %tobool37 = icmp ne i32 %call, 0, !dbg !3605
  br i1 %tobool37, label %if.then38, label %if.end46, !dbg !3606

if.then38:                                        ; preds = %while.body
  %30 = load i32*, i32** %bzerror.addr, align 8, !dbg !3607
  %cmp39 = icmp ne i32* %30, null, !dbg !3607
  br i1 %cmp39, label %if.then40, label %if.end41, !dbg !3611

if.then40:                                        ; preds = %if.then38
  %31 = load i32*, i32** %bzerror.addr, align 8, !dbg !3612
  store i32 -6, i32* %31, align 4, !dbg !3612
  br label %if.end41, !dbg !3612

if.end41:                                         ; preds = %if.then40, %if.then38
  %32 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3614
  %cmp42 = icmp ne %struct.bzFile* %32, null, !dbg !3614
  br i1 %cmp42, label %if.then43, label %if.end45, !dbg !3614

if.then43:                                        ; preds = %if.end41
  %33 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3617
  %lastErr44 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %33, i32 0, i32 5, !dbg !3617
  store i32 -6, i32* %lastErr44, align 8, !dbg !3617
  br label %if.end45, !dbg !3617

if.end45:                                         ; preds = %if.then43, %if.end41
  store i32 0, i32* %retval, align 4, !dbg !3619
  br label %return, !dbg !3619

if.end46:                                         ; preds = %while.body
  %34 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3621
  %strm47 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %34, i32 0, i32 4, !dbg !3623
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm47, i32 0, i32 1, !dbg !3624
  %35 = load i32, i32* %avail_in, align 8, !dbg !3624
  %cmp48 = icmp eq i32 %35, 0, !dbg !3625
  br i1 %cmp48, label %land.lhs.true, label %if.end76, !dbg !3626

land.lhs.true:                                    ; preds = %if.end46
  %36 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3627
  %handle49 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %36, i32 0, i32 0, !dbg !3629
  %37 = load %struct._IO_FILE*, %struct._IO_FILE** %handle49, align 8, !dbg !3629
  %call50 = call zeroext i8 @myfeof(%struct._IO_FILE* %37), !dbg !3630
  %tobool51 = icmp ne i8 %call50, 0, !dbg !3630
  br i1 %tobool51, label %if.end76, label %if.then52, !dbg !3631

if.then52:                                        ; preds = %land.lhs.true
  %38 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3632
  %buf53 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %38, i32 0, i32 1, !dbg !3634
  %arraydecay = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf53, i32 0, i32 0, !dbg !3632
  %39 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3635
  %handle54 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %39, i32 0, i32 0, !dbg !3636
  %40 = load %struct._IO_FILE*, %struct._IO_FILE** %handle54, align 8, !dbg !3636
  %call55 = call i64 @fread(i8* %arraydecay, i64 1, i64 5000, %struct._IO_FILE* %40), !dbg !3637
  %conv = trunc i64 %call55 to i32, !dbg !3637
  store i32 %conv, i32* %n, align 4, !dbg !3638
  %41 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3639
  %handle56 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %41, i32 0, i32 0, !dbg !3641
  %42 = load %struct._IO_FILE*, %struct._IO_FILE** %handle56, align 8, !dbg !3641
  %call57 = call i32 @ferror(%struct._IO_FILE* %42) #10, !dbg !3642
  %tobool58 = icmp ne i32 %call57, 0, !dbg !3642
  br i1 %tobool58, label %if.then59, label %if.end69, !dbg !3643

if.then59:                                        ; preds = %if.then52
  %43 = load i32*, i32** %bzerror.addr, align 8, !dbg !3644
  %cmp60 = icmp ne i32* %43, null, !dbg !3644
  br i1 %cmp60, label %if.then62, label %if.end63, !dbg !3648

if.then62:                                        ; preds = %if.then59
  %44 = load i32*, i32** %bzerror.addr, align 8, !dbg !3649
  store i32 -6, i32* %44, align 4, !dbg !3649
  br label %if.end63, !dbg !3649

if.end63:                                         ; preds = %if.then62, %if.then59
  %45 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3651
  %cmp64 = icmp ne %struct.bzFile* %45, null, !dbg !3651
  br i1 %cmp64, label %if.then66, label %if.end68, !dbg !3651

if.then66:                                        ; preds = %if.end63
  %46 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3654
  %lastErr67 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %46, i32 0, i32 5, !dbg !3654
  store i32 -6, i32* %lastErr67, align 8, !dbg !3654
  br label %if.end68, !dbg !3654

if.end68:                                         ; preds = %if.then66, %if.end63
  store i32 0, i32* %retval, align 4, !dbg !3656
  br label %return, !dbg !3656

if.end69:                                         ; preds = %if.then52
  %47 = load i32, i32* %n, align 4, !dbg !3658
  %48 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3659
  %bufN = getelementptr inbounds %struct.bzFile, %struct.bzFile* %48, i32 0, i32 2, !dbg !3660
  store i32 %47, i32* %bufN, align 8, !dbg !3661
  %49 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3662
  %bufN70 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %49, i32 0, i32 2, !dbg !3663
  %50 = load i32, i32* %bufN70, align 8, !dbg !3663
  %51 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3664
  %strm71 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %51, i32 0, i32 4, !dbg !3665
  %avail_in72 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm71, i32 0, i32 1, !dbg !3666
  store i32 %50, i32* %avail_in72, align 8, !dbg !3667
  %52 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3668
  %buf73 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %52, i32 0, i32 1, !dbg !3669
  %arraydecay74 = getelementptr inbounds [5000 x i8], [5000 x i8]* %buf73, i32 0, i32 0, !dbg !3668
  %53 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3670
  %strm75 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %53, i32 0, i32 4, !dbg !3671
  %next_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm75, i32 0, i32 0, !dbg !3672
  store i8* %arraydecay74, i8** %next_in, align 8, !dbg !3673
  br label %if.end76, !dbg !3674

if.end76:                                         ; preds = %if.end69, %land.lhs.true, %if.end46
  %54 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3675
  %strm77 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %54, i32 0, i32 4, !dbg !3676
  %call78 = call i32 @BZ2_bzDecompress(%struct.bz_stream* %strm77), !dbg !3677
  store i32 %call78, i32* %ret, align 4, !dbg !3678
  %55 = load i32, i32* %ret, align 4, !dbg !3679
  %cmp79 = icmp ne i32 %55, 0, !dbg !3681
  br i1 %cmp79, label %land.lhs.true81, label %if.end94, !dbg !3682

land.lhs.true81:                                  ; preds = %if.end76
  %56 = load i32, i32* %ret, align 4, !dbg !3683
  %cmp82 = icmp ne i32 %56, 4, !dbg !3685
  br i1 %cmp82, label %if.then84, label %if.end94, !dbg !3686

if.then84:                                        ; preds = %land.lhs.true81
  %57 = load i32*, i32** %bzerror.addr, align 8, !dbg !3687
  %cmp85 = icmp ne i32* %57, null, !dbg !3687
  br i1 %cmp85, label %if.then87, label %if.end88, !dbg !3691

if.then87:                                        ; preds = %if.then84
  %58 = load i32, i32* %ret, align 4, !dbg !3692
  %59 = load i32*, i32** %bzerror.addr, align 8, !dbg !3692
  store i32 %58, i32* %59, align 4, !dbg !3692
  br label %if.end88, !dbg !3692

if.end88:                                         ; preds = %if.then87, %if.then84
  %60 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3694
  %cmp89 = icmp ne %struct.bzFile* %60, null, !dbg !3694
  br i1 %cmp89, label %if.then91, label %if.end93, !dbg !3694

if.then91:                                        ; preds = %if.end88
  %61 = load i32, i32* %ret, align 4, !dbg !3697
  %62 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3697
  %lastErr92 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %62, i32 0, i32 5, !dbg !3697
  store i32 %61, i32* %lastErr92, align 8, !dbg !3697
  br label %if.end93, !dbg !3697

if.end93:                                         ; preds = %if.then91, %if.end88
  store i32 0, i32* %retval, align 4, !dbg !3699
  br label %return, !dbg !3699

if.end94:                                         ; preds = %land.lhs.true81, %if.end76
  %63 = load i32, i32* %ret, align 4, !dbg !3701
  %cmp95 = icmp eq i32 %63, 0, !dbg !3703
  br i1 %cmp95, label %land.lhs.true97, label %if.end122, !dbg !3704

land.lhs.true97:                                  ; preds = %if.end94
  %64 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3705
  %handle98 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %64, i32 0, i32 0, !dbg !3707
  %65 = load %struct._IO_FILE*, %struct._IO_FILE** %handle98, align 8, !dbg !3707
  %call99 = call zeroext i8 @myfeof(%struct._IO_FILE* %65), !dbg !3708
  %conv100 = zext i8 %call99 to i32, !dbg !3708
  %tobool101 = icmp ne i32 %conv100, 0, !dbg !3708
  br i1 %tobool101, label %land.lhs.true102, label %if.end122, !dbg !3709

land.lhs.true102:                                 ; preds = %land.lhs.true97
  %66 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3710
  %strm103 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %66, i32 0, i32 4, !dbg !3711
  %avail_in104 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm103, i32 0, i32 1, !dbg !3712
  %67 = load i32, i32* %avail_in104, align 8, !dbg !3712
  %cmp105 = icmp eq i32 %67, 0, !dbg !3713
  br i1 %cmp105, label %land.lhs.true107, label %if.end122, !dbg !3714

land.lhs.true107:                                 ; preds = %land.lhs.true102
  %68 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3715
  %strm108 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %68, i32 0, i32 4, !dbg !3716
  %avail_out109 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm108, i32 0, i32 5, !dbg !3717
  %69 = load i32, i32* %avail_out109, align 8, !dbg !3717
  %cmp110 = icmp ugt i32 %69, 0, !dbg !3718
  br i1 %cmp110, label %if.then112, label %if.end122, !dbg !3719

if.then112:                                       ; preds = %land.lhs.true107
  %70 = load i32*, i32** %bzerror.addr, align 8, !dbg !3721
  %cmp113 = icmp ne i32* %70, null, !dbg !3721
  br i1 %cmp113, label %if.then115, label %if.end116, !dbg !3725

if.then115:                                       ; preds = %if.then112
  %71 = load i32*, i32** %bzerror.addr, align 8, !dbg !3726
  store i32 -7, i32* %71, align 4, !dbg !3726
  br label %if.end116, !dbg !3726

if.end116:                                        ; preds = %if.then115, %if.then112
  %72 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3728
  %cmp117 = icmp ne %struct.bzFile* %72, null, !dbg !3728
  br i1 %cmp117, label %if.then119, label %if.end121, !dbg !3728

if.then119:                                       ; preds = %if.end116
  %73 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3731
  %lastErr120 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %73, i32 0, i32 5, !dbg !3731
  store i32 -7, i32* %lastErr120, align 8, !dbg !3731
  br label %if.end121, !dbg !3731

if.end121:                                        ; preds = %if.then119, %if.end116
  store i32 0, i32* %retval, align 4, !dbg !3733
  br label %return, !dbg !3733

if.end122:                                        ; preds = %land.lhs.true107, %land.lhs.true102, %land.lhs.true97, %if.end94
  %74 = load i32, i32* %ret, align 4, !dbg !3735
  %cmp123 = icmp eq i32 %74, 4, !dbg !3737
  br i1 %cmp123, label %if.then125, label %if.end137, !dbg !3738

if.then125:                                       ; preds = %if.end122
  %75 = load i32*, i32** %bzerror.addr, align 8, !dbg !3739
  %cmp126 = icmp ne i32* %75, null, !dbg !3739
  br i1 %cmp126, label %if.then128, label %if.end129, !dbg !3743

if.then128:                                       ; preds = %if.then125
  %76 = load i32*, i32** %bzerror.addr, align 8, !dbg !3744
  store i32 4, i32* %76, align 4, !dbg !3744
  br label %if.end129, !dbg !3744

if.end129:                                        ; preds = %if.then128, %if.then125
  %77 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3746
  %cmp130 = icmp ne %struct.bzFile* %77, null, !dbg !3746
  br i1 %cmp130, label %if.then132, label %if.end134, !dbg !3746

if.then132:                                       ; preds = %if.end129
  %78 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3749
  %lastErr133 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %78, i32 0, i32 5, !dbg !3749
  store i32 4, i32* %lastErr133, align 8, !dbg !3749
  br label %if.end134, !dbg !3749

if.end134:                                        ; preds = %if.then132, %if.end129
  %79 = load i32, i32* %len.addr, align 4, !dbg !3751
  %80 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3752
  %strm135 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %80, i32 0, i32 4, !dbg !3753
  %avail_out136 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm135, i32 0, i32 5, !dbg !3754
  %81 = load i32, i32* %avail_out136, align 8, !dbg !3754
  %sub = sub i32 %79, %81, !dbg !3755
  store i32 %sub, i32* %retval, align 4, !dbg !3756
  br label %return, !dbg !3756

if.end137:                                        ; preds = %if.end122
  %82 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3757
  %strm138 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %82, i32 0, i32 4, !dbg !3759
  %avail_out139 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm138, i32 0, i32 5, !dbg !3760
  %83 = load i32, i32* %avail_out139, align 8, !dbg !3760
  %cmp140 = icmp eq i32 %83, 0, !dbg !3761
  br i1 %cmp140, label %if.then142, label %if.end152, !dbg !3762

if.then142:                                       ; preds = %if.end137
  %84 = load i32*, i32** %bzerror.addr, align 8, !dbg !3763
  %cmp143 = icmp ne i32* %84, null, !dbg !3763
  br i1 %cmp143, label %if.then145, label %if.end146, !dbg !3767

if.then145:                                       ; preds = %if.then142
  %85 = load i32*, i32** %bzerror.addr, align 8, !dbg !3768
  store i32 0, i32* %85, align 4, !dbg !3768
  br label %if.end146, !dbg !3768

if.end146:                                        ; preds = %if.then145, %if.then142
  %86 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3770
  %cmp147 = icmp ne %struct.bzFile* %86, null, !dbg !3770
  br i1 %cmp147, label %if.then149, label %if.end151, !dbg !3770

if.then149:                                       ; preds = %if.end146
  %87 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3773
  %lastErr150 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %87, i32 0, i32 5, !dbg !3773
  store i32 0, i32* %lastErr150, align 8, !dbg !3773
  br label %if.end151, !dbg !3773

if.end151:                                        ; preds = %if.then149, %if.end146
  %88 = load i32, i32* %len.addr, align 4, !dbg !3775
  store i32 %88, i32* %retval, align 4, !dbg !3777
  br label %return, !dbg !3777

if.end152:                                        ; preds = %if.end137
  br label %while.body, !dbg !3778

return:                                           ; preds = %if.end151, %if.end134, %if.end121, %if.end93, %if.end68, %if.end45, %if.end34, %if.end24, %if.end15
  %89 = load i32, i32* %retval, align 4, !dbg !3780
  ret i32 %89, !dbg !3780
}

; Function Attrs: nounwind uwtable
define internal zeroext i8 @myfeof(%struct._IO_FILE* %f) #0 !dbg !379 {
entry:
  %retval = alloca i8, align 1
  %f.addr = alloca %struct._IO_FILE*, align 8
  %c = alloca i32, align 4
  store %struct._IO_FILE* %f, %struct._IO_FILE** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %f.addr, metadata !3781, metadata !392), !dbg !3782
  call void @llvm.dbg.declare(metadata i32* %c, metadata !3783, metadata !392), !dbg !3784
  %0 = load %struct._IO_FILE*, %struct._IO_FILE** %f.addr, align 8, !dbg !3785
  %call = call i32 @fgetc(%struct._IO_FILE* %0), !dbg !3786
  store i32 %call, i32* %c, align 4, !dbg !3784
  %1 = load i32, i32* %c, align 4, !dbg !3787
  %cmp = icmp eq i32 %1, -1, !dbg !3789
  br i1 %cmp, label %if.then, label %if.end, !dbg !3790

if.then:                                          ; preds = %entry
  store i8 1, i8* %retval, align 1, !dbg !3791
  br label %return, !dbg !3791

if.end:                                           ; preds = %entry
  %2 = load i32, i32* %c, align 4, !dbg !3793
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** %f.addr, align 8, !dbg !3794
  %call1 = call i32 @ungetc(i32 %2, %struct._IO_FILE* %3), !dbg !3795
  store i8 0, i8* %retval, align 1, !dbg !3796
  br label %return, !dbg !3796

return:                                           ; preds = %if.end, %if.then
  %4 = load i8, i8* %retval, align 1, !dbg !3797
  ret i8 %4, !dbg !3797
}

declare i64 @fread(i8*, i64, i64, %struct._IO_FILE*) #2

; Function Attrs: nounwind uwtable
define void @BZ2_bzReadGetUnused(i32* %bzerror, i8* %b, i8** %unused, i32* %nUnused) #0 !dbg !179 {
entry:
  %bzerror.addr = alloca i32*, align 8
  %b.addr = alloca i8*, align 8
  %unused.addr = alloca i8**, align 8
  %nUnused.addr = alloca i32*, align 8
  %bzf = alloca %struct.bzFile*, align 8
  store i32* %bzerror, i32** %bzerror.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %bzerror.addr, metadata !3798, metadata !392), !dbg !3799
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !3800, metadata !392), !dbg !3801
  store i8** %unused, i8*** %unused.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %unused.addr, metadata !3802, metadata !392), !dbg !3803
  store i32* %nUnused, i32** %nUnused.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %nUnused.addr, metadata !3804, metadata !392), !dbg !3805
  call void @llvm.dbg.declare(metadata %struct.bzFile** %bzf, metadata !3806, metadata !392), !dbg !3807
  %0 = load i8*, i8** %b.addr, align 8, !dbg !3808
  %1 = bitcast i8* %0 to %struct.bzFile*, !dbg !3809
  store %struct.bzFile* %1, %struct.bzFile** %bzf, align 8, !dbg !3807
  %2 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3810
  %cmp = icmp eq %struct.bzFile* %2, null, !dbg !3812
  br i1 %cmp, label %if.then, label %if.end6, !dbg !3813

if.then:                                          ; preds = %entry
  %3 = load i32*, i32** %bzerror.addr, align 8, !dbg !3814
  %cmp1 = icmp ne i32* %3, null, !dbg !3814
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !3818

if.then2:                                         ; preds = %if.then
  %4 = load i32*, i32** %bzerror.addr, align 8, !dbg !3819
  store i32 -2, i32* %4, align 4, !dbg !3819
  br label %if.end, !dbg !3819

if.end:                                           ; preds = %if.then2, %if.then
  %5 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3821
  %cmp3 = icmp ne %struct.bzFile* %5, null, !dbg !3821
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !3821

if.then4:                                         ; preds = %if.end
  %6 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3824
  %lastErr = getelementptr inbounds %struct.bzFile, %struct.bzFile* %6, i32 0, i32 5, !dbg !3824
  store i32 -2, i32* %lastErr, align 8, !dbg !3824
  br label %if.end5, !dbg !3824

if.end5:                                          ; preds = %if.then4, %if.end
  br label %return, !dbg !3826

if.end6:                                          ; preds = %entry
  %7 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3828
  %lastErr7 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %7, i32 0, i32 5, !dbg !3830
  %8 = load i32, i32* %lastErr7, align 8, !dbg !3830
  %cmp8 = icmp ne i32 %8, 4, !dbg !3831
  br i1 %cmp8, label %if.then9, label %if.end17, !dbg !3832

if.then9:                                         ; preds = %if.end6
  %9 = load i32*, i32** %bzerror.addr, align 8, !dbg !3833
  %cmp10 = icmp ne i32* %9, null, !dbg !3833
  br i1 %cmp10, label %if.then11, label %if.end12, !dbg !3837

if.then11:                                        ; preds = %if.then9
  %10 = load i32*, i32** %bzerror.addr, align 8, !dbg !3838
  store i32 -1, i32* %10, align 4, !dbg !3838
  br label %if.end12, !dbg !3838

if.end12:                                         ; preds = %if.then11, %if.then9
  %11 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3840
  %cmp13 = icmp ne %struct.bzFile* %11, null, !dbg !3840
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !3840

if.then14:                                        ; preds = %if.end12
  %12 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3843
  %lastErr15 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %12, i32 0, i32 5, !dbg !3843
  store i32 -1, i32* %lastErr15, align 8, !dbg !3843
  br label %if.end16, !dbg !3843

if.end16:                                         ; preds = %if.then14, %if.end12
  br label %return, !dbg !3845

if.end17:                                         ; preds = %if.end6
  %13 = load i8**, i8*** %unused.addr, align 8, !dbg !3847
  %cmp18 = icmp eq i8** %13, null, !dbg !3849
  br i1 %cmp18, label %if.then20, label %lor.lhs.false, !dbg !3850

lor.lhs.false:                                    ; preds = %if.end17
  %14 = load i32*, i32** %nUnused.addr, align 8, !dbg !3851
  %cmp19 = icmp eq i32* %14, null, !dbg !3853
  br i1 %cmp19, label %if.then20, label %if.end28, !dbg !3854

if.then20:                                        ; preds = %lor.lhs.false, %if.end17
  %15 = load i32*, i32** %bzerror.addr, align 8, !dbg !3855
  %cmp21 = icmp ne i32* %15, null, !dbg !3855
  br i1 %cmp21, label %if.then22, label %if.end23, !dbg !3859

if.then22:                                        ; preds = %if.then20
  %16 = load i32*, i32** %bzerror.addr, align 8, !dbg !3860
  store i32 -2, i32* %16, align 4, !dbg !3860
  br label %if.end23, !dbg !3860

if.end23:                                         ; preds = %if.then22, %if.then20
  %17 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3862
  %cmp24 = icmp ne %struct.bzFile* %17, null, !dbg !3862
  br i1 %cmp24, label %if.then25, label %if.end27, !dbg !3862

if.then25:                                        ; preds = %if.end23
  %18 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3865
  %lastErr26 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %18, i32 0, i32 5, !dbg !3865
  store i32 -2, i32* %lastErr26, align 8, !dbg !3865
  br label %if.end27, !dbg !3865

if.end27:                                         ; preds = %if.then25, %if.end23
  br label %return, !dbg !3867

if.end28:                                         ; preds = %lor.lhs.false
  %19 = load i32*, i32** %bzerror.addr, align 8, !dbg !3869
  %cmp29 = icmp ne i32* %19, null, !dbg !3869
  br i1 %cmp29, label %if.then30, label %if.end31, !dbg !3872

if.then30:                                        ; preds = %if.end28
  %20 = load i32*, i32** %bzerror.addr, align 8, !dbg !3873
  store i32 0, i32* %20, align 4, !dbg !3873
  br label %if.end31, !dbg !3873

if.end31:                                         ; preds = %if.then30, %if.end28
  %21 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3875
  %cmp32 = icmp ne %struct.bzFile* %21, null, !dbg !3875
  br i1 %cmp32, label %if.then33, label %if.end35, !dbg !3875

if.then33:                                        ; preds = %if.end31
  %22 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3878
  %lastErr34 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %22, i32 0, i32 5, !dbg !3878
  store i32 0, i32* %lastErr34, align 8, !dbg !3878
  br label %if.end35, !dbg !3878

if.end35:                                         ; preds = %if.then33, %if.end31
  %23 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3880
  %strm = getelementptr inbounds %struct.bzFile, %struct.bzFile* %23, i32 0, i32 4, !dbg !3881
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 1, !dbg !3882
  %24 = load i32, i32* %avail_in, align 8, !dbg !3882
  %25 = load i32*, i32** %nUnused.addr, align 8, !dbg !3883
  store i32 %24, i32* %25, align 4, !dbg !3884
  %26 = load %struct.bzFile*, %struct.bzFile** %bzf, align 8, !dbg !3885
  %strm36 = getelementptr inbounds %struct.bzFile, %struct.bzFile* %26, i32 0, i32 4, !dbg !3886
  %next_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm36, i32 0, i32 0, !dbg !3887
  %27 = load i8*, i8** %next_in, align 8, !dbg !3887
  %28 = load i8**, i8*** %unused.addr, align 8, !dbg !3888
  store i8* %27, i8** %28, align 8, !dbg !3889
  br label %return, !dbg !3890

return:                                           ; preds = %if.end35, %if.end27, %if.end16, %if.end5
  ret void, !dbg !3891
}

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzBuffToBuffCompress(i8* %dest, i32* %destLen, i8* %source, i32 %sourceLen, i32 %blockSize100k, i32 %verbosity, i32 %workFactor) #0 !dbg !183 {
entry:
  %retval = alloca i32, align 4
  %dest.addr = alloca i8*, align 8
  %destLen.addr = alloca i32*, align 8
  %source.addr = alloca i8*, align 8
  %sourceLen.addr = alloca i32, align 4
  %blockSize100k.addr = alloca i32, align 4
  %verbosity.addr = alloca i32, align 4
  %workFactor.addr = alloca i32, align 4
  %strm = alloca %struct.bz_stream, align 8
  %ret = alloca i32, align 4
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !3893, metadata !392), !dbg !3894
  store i32* %destLen, i32** %destLen.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %destLen.addr, metadata !3895, metadata !392), !dbg !3896
  store i8* %source, i8** %source.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %source.addr, metadata !3897, metadata !392), !dbg !3898
  store i32 %sourceLen, i32* %sourceLen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sourceLen.addr, metadata !3899, metadata !392), !dbg !3900
  store i32 %blockSize100k, i32* %blockSize100k.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %blockSize100k.addr, metadata !3901, metadata !392), !dbg !3902
  store i32 %verbosity, i32* %verbosity.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %verbosity.addr, metadata !3903, metadata !392), !dbg !3904
  store i32 %workFactor, i32* %workFactor.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %workFactor.addr, metadata !3905, metadata !392), !dbg !3906
  call void @llvm.dbg.declare(metadata %struct.bz_stream* %strm, metadata !3907, metadata !392), !dbg !3908
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !3909, metadata !392), !dbg !3910
  %0 = load i8*, i8** %dest.addr, align 8, !dbg !3911
  %cmp = icmp eq i8* %0, null, !dbg !3913
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !3914

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32*, i32** %destLen.addr, align 8, !dbg !3915
  %cmp1 = icmp eq i32* %1, null, !dbg !3917
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !3918

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i8*, i8** %source.addr, align 8, !dbg !3919
  %cmp3 = icmp eq i8* %2, null, !dbg !3920
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !3921

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %3 = load i32, i32* %blockSize100k.addr, align 4, !dbg !3922
  %cmp5 = icmp slt i32 %3, 1, !dbg !3923
  br i1 %cmp5, label %if.then, label %lor.lhs.false6, !dbg !3924

lor.lhs.false6:                                   ; preds = %lor.lhs.false4
  %4 = load i32, i32* %blockSize100k.addr, align 4, !dbg !3925
  %cmp7 = icmp sgt i32 %4, 9, !dbg !3926
  br i1 %cmp7, label %if.then, label %lor.lhs.false8, !dbg !3927

lor.lhs.false8:                                   ; preds = %lor.lhs.false6
  %5 = load i32, i32* %verbosity.addr, align 4, !dbg !3928
  %cmp9 = icmp slt i32 %5, 0, !dbg !3929
  br i1 %cmp9, label %if.then, label %lor.lhs.false10, !dbg !3930

lor.lhs.false10:                                  ; preds = %lor.lhs.false8
  %6 = load i32, i32* %verbosity.addr, align 4, !dbg !3931
  %cmp11 = icmp sgt i32 %6, 4, !dbg !3932
  br i1 %cmp11, label %if.then, label %lor.lhs.false12, !dbg !3933

lor.lhs.false12:                                  ; preds = %lor.lhs.false10
  %7 = load i32, i32* %workFactor.addr, align 4, !dbg !3934
  %cmp13 = icmp slt i32 %7, 0, !dbg !3935
  br i1 %cmp13, label %if.then, label %lor.lhs.false14, !dbg !3936

lor.lhs.false14:                                  ; preds = %lor.lhs.false12
  %8 = load i32, i32* %workFactor.addr, align 4, !dbg !3937
  %cmp15 = icmp sgt i32 %8, 250, !dbg !3938
  br i1 %cmp15, label %if.then, label %if.end, !dbg !3939

if.then:                                          ; preds = %lor.lhs.false14, %lor.lhs.false12, %lor.lhs.false10, %lor.lhs.false8, %lor.lhs.false6, %lor.lhs.false4, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !3941
  br label %return, !dbg !3941

if.end:                                           ; preds = %lor.lhs.false14
  %9 = load i32, i32* %workFactor.addr, align 4, !dbg !3942
  %cmp16 = icmp eq i32 %9, 0, !dbg !3944
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !3945

if.then17:                                        ; preds = %if.end
  store i32 30, i32* %workFactor.addr, align 4, !dbg !3946
  br label %if.end18, !dbg !3948

if.end18:                                         ; preds = %if.then17, %if.end
  %bzalloc = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 9, !dbg !3949
  store i8* (i8*, i32, i32)* null, i8* (i8*, i32, i32)** %bzalloc, align 8, !dbg !3950
  %bzfree = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 10, !dbg !3951
  store void (i8*, i8*)* null, void (i8*, i8*)** %bzfree, align 8, !dbg !3952
  %opaque = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 11, !dbg !3953
  store i8* null, i8** %opaque, align 8, !dbg !3954
  %10 = load i32, i32* %blockSize100k.addr, align 4, !dbg !3955
  %11 = load i32, i32* %verbosity.addr, align 4, !dbg !3956
  %12 = load i32, i32* %workFactor.addr, align 4, !dbg !3957
  %call = call i32 @BZ2_bzCompressInit(%struct.bz_stream* %strm, i32 %10, i32 %11, i32 %12), !dbg !3958
  store i32 %call, i32* %ret, align 4, !dbg !3959
  %13 = load i32, i32* %ret, align 4, !dbg !3960
  %cmp19 = icmp ne i32 %13, 0, !dbg !3962
  br i1 %cmp19, label %if.then20, label %if.end21, !dbg !3963

if.then20:                                        ; preds = %if.end18
  %14 = load i32, i32* %ret, align 4, !dbg !3964
  store i32 %14, i32* %retval, align 4, !dbg !3966
  br label %return, !dbg !3966

if.end21:                                         ; preds = %if.end18
  %15 = load i8*, i8** %source.addr, align 8, !dbg !3967
  %next_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 0, !dbg !3968
  store i8* %15, i8** %next_in, align 8, !dbg !3969
  %16 = load i8*, i8** %dest.addr, align 8, !dbg !3970
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 4, !dbg !3971
  store i8* %16, i8** %next_out, align 8, !dbg !3972
  %17 = load i32, i32* %sourceLen.addr, align 4, !dbg !3973
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 1, !dbg !3974
  store i32 %17, i32* %avail_in, align 8, !dbg !3975
  %18 = load i32*, i32** %destLen.addr, align 8, !dbg !3976
  %19 = load i32, i32* %18, align 4, !dbg !3977
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 5, !dbg !3978
  store i32 %19, i32* %avail_out, align 8, !dbg !3979
  %call22 = call i32 @BZ2_bzCompress(%struct.bz_stream* %strm, i32 2), !dbg !3980
  store i32 %call22, i32* %ret, align 4, !dbg !3981
  %20 = load i32, i32* %ret, align 4, !dbg !3982
  %cmp23 = icmp eq i32 %20, 3, !dbg !3984
  br i1 %cmp23, label %if.then24, label %if.end25, !dbg !3985

if.then24:                                        ; preds = %if.end21
  br label %output_overflow, !dbg !3986

if.end25:                                         ; preds = %if.end21
  %21 = load i32, i32* %ret, align 4, !dbg !3988
  %cmp26 = icmp ne i32 %21, 4, !dbg !3990
  br i1 %cmp26, label %if.then27, label %if.end28, !dbg !3991

if.then27:                                        ; preds = %if.end25
  br label %errhandler, !dbg !3992

if.end28:                                         ; preds = %if.end25
  %avail_out29 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 5, !dbg !3994
  %22 = load i32, i32* %avail_out29, align 8, !dbg !3994
  %23 = load i32*, i32** %destLen.addr, align 8, !dbg !3995
  %24 = load i32, i32* %23, align 4, !dbg !3996
  %sub = sub i32 %24, %22, !dbg !3996
  store i32 %sub, i32* %23, align 4, !dbg !3996
  %call30 = call i32 @BZ2_bzCompressEnd(%struct.bz_stream* %strm), !dbg !3997
  store i32 0, i32* %retval, align 4, !dbg !3998
  br label %return, !dbg !3998

output_overflow:                                  ; preds = %if.then24
  %call31 = call i32 @BZ2_bzCompressEnd(%struct.bz_stream* %strm), !dbg !3999
  store i32 -8, i32* %retval, align 4, !dbg !4000
  br label %return, !dbg !4000

errhandler:                                       ; preds = %if.then27
  %call32 = call i32 @BZ2_bzCompressEnd(%struct.bz_stream* %strm), !dbg !4001
  %25 = load i32, i32* %ret, align 4, !dbg !4002
  store i32 %25, i32* %retval, align 4, !dbg !4003
  br label %return, !dbg !4003

return:                                           ; preds = %errhandler, %output_overflow, %if.end28, %if.then20, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !4004
  ret i32 %26, !dbg !4004
}

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzBuffToBuffDecompress(i8* %dest, i32* %destLen, i8* %source, i32 %sourceLen, i32 %small, i32 %verbosity) #0 !dbg !186 {
entry:
  %retval = alloca i32, align 4
  %dest.addr = alloca i8*, align 8
  %destLen.addr = alloca i32*, align 8
  %source.addr = alloca i8*, align 8
  %sourceLen.addr = alloca i32, align 4
  %small.addr = alloca i32, align 4
  %verbosity.addr = alloca i32, align 4
  %strm = alloca %struct.bz_stream, align 8
  %ret = alloca i32, align 4
  store i8* %dest, i8** %dest.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %dest.addr, metadata !4005, metadata !392), !dbg !4006
  store i32* %destLen, i32** %destLen.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %destLen.addr, metadata !4007, metadata !392), !dbg !4008
  store i8* %source, i8** %source.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %source.addr, metadata !4009, metadata !392), !dbg !4010
  store i32 %sourceLen, i32* %sourceLen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sourceLen.addr, metadata !4011, metadata !392), !dbg !4012
  store i32 %small, i32* %small.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %small.addr, metadata !4013, metadata !392), !dbg !4014
  store i32 %verbosity, i32* %verbosity.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %verbosity.addr, metadata !4015, metadata !392), !dbg !4016
  call void @llvm.dbg.declare(metadata %struct.bz_stream* %strm, metadata !4017, metadata !392), !dbg !4018
  call void @llvm.dbg.declare(metadata i32* %ret, metadata !4019, metadata !392), !dbg !4020
  %0 = load i8*, i8** %dest.addr, align 8, !dbg !4021
  %cmp = icmp eq i8* %0, null, !dbg !4023
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !4024

lor.lhs.false:                                    ; preds = %entry
  %1 = load i32*, i32** %destLen.addr, align 8, !dbg !4025
  %cmp1 = icmp eq i32* %1, null, !dbg !4027
  br i1 %cmp1, label %if.then, label %lor.lhs.false2, !dbg !4028

lor.lhs.false2:                                   ; preds = %lor.lhs.false
  %2 = load i8*, i8** %source.addr, align 8, !dbg !4029
  %cmp3 = icmp eq i8* %2, null, !dbg !4030
  br i1 %cmp3, label %if.then, label %lor.lhs.false4, !dbg !4031

lor.lhs.false4:                                   ; preds = %lor.lhs.false2
  %3 = load i32, i32* %small.addr, align 4, !dbg !4032
  %cmp5 = icmp ne i32 %3, 0, !dbg !4033
  br i1 %cmp5, label %land.lhs.true, label %lor.lhs.false7, !dbg !4034

land.lhs.true:                                    ; preds = %lor.lhs.false4
  %4 = load i32, i32* %small.addr, align 4, !dbg !4035
  %cmp6 = icmp ne i32 %4, 1, !dbg !4036
  br i1 %cmp6, label %if.then, label %lor.lhs.false7, !dbg !4037

lor.lhs.false7:                                   ; preds = %land.lhs.true, %lor.lhs.false4
  %5 = load i32, i32* %verbosity.addr, align 4, !dbg !4038
  %cmp8 = icmp slt i32 %5, 0, !dbg !4039
  br i1 %cmp8, label %if.then, label %lor.lhs.false9, !dbg !4040

lor.lhs.false9:                                   ; preds = %lor.lhs.false7
  %6 = load i32, i32* %verbosity.addr, align 4, !dbg !4041
  %cmp10 = icmp sgt i32 %6, 4, !dbg !4042
  br i1 %cmp10, label %if.then, label %if.end, !dbg !4043

if.then:                                          ; preds = %lor.lhs.false9, %lor.lhs.false7, %land.lhs.true, %lor.lhs.false2, %lor.lhs.false, %entry
  store i32 -2, i32* %retval, align 4, !dbg !4045
  br label %return, !dbg !4045

if.end:                                           ; preds = %lor.lhs.false9
  %bzalloc = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 9, !dbg !4046
  store i8* (i8*, i32, i32)* null, i8* (i8*, i32, i32)** %bzalloc, align 8, !dbg !4047
  %bzfree = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 10, !dbg !4048
  store void (i8*, i8*)* null, void (i8*, i8*)** %bzfree, align 8, !dbg !4049
  %opaque = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 11, !dbg !4050
  store i8* null, i8** %opaque, align 8, !dbg !4051
  %7 = load i32, i32* %verbosity.addr, align 4, !dbg !4052
  %8 = load i32, i32* %small.addr, align 4, !dbg !4053
  %call = call i32 @BZ2_bzDecompressInit(%struct.bz_stream* %strm, i32 %7, i32 %8), !dbg !4054
  store i32 %call, i32* %ret, align 4, !dbg !4055
  %9 = load i32, i32* %ret, align 4, !dbg !4056
  %cmp11 = icmp ne i32 %9, 0, !dbg !4058
  br i1 %cmp11, label %if.then12, label %if.end13, !dbg !4059

if.then12:                                        ; preds = %if.end
  %10 = load i32, i32* %ret, align 4, !dbg !4060
  store i32 %10, i32* %retval, align 4, !dbg !4062
  br label %return, !dbg !4062

if.end13:                                         ; preds = %if.end
  %11 = load i8*, i8** %source.addr, align 8, !dbg !4063
  %next_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 0, !dbg !4064
  store i8* %11, i8** %next_in, align 8, !dbg !4065
  %12 = load i8*, i8** %dest.addr, align 8, !dbg !4066
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 4, !dbg !4067
  store i8* %12, i8** %next_out, align 8, !dbg !4068
  %13 = load i32, i32* %sourceLen.addr, align 4, !dbg !4069
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 1, !dbg !4070
  store i32 %13, i32* %avail_in, align 8, !dbg !4071
  %14 = load i32*, i32** %destLen.addr, align 8, !dbg !4072
  %15 = load i32, i32* %14, align 4, !dbg !4073
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 5, !dbg !4074
  store i32 %15, i32* %avail_out, align 8, !dbg !4075
  %call14 = call i32 @BZ2_bzDecompress(%struct.bz_stream* %strm), !dbg !4076
  store i32 %call14, i32* %ret, align 4, !dbg !4077
  %16 = load i32, i32* %ret, align 4, !dbg !4078
  %cmp15 = icmp eq i32 %16, 0, !dbg !4080
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !4081

if.then16:                                        ; preds = %if.end13
  br label %output_overflow_or_eof, !dbg !4082

if.end17:                                         ; preds = %if.end13
  %17 = load i32, i32* %ret, align 4, !dbg !4084
  %cmp18 = icmp ne i32 %17, 4, !dbg !4086
  br i1 %cmp18, label %if.then19, label %if.end20, !dbg !4087

if.then19:                                        ; preds = %if.end17
  br label %errhandler, !dbg !4088

if.end20:                                         ; preds = %if.end17
  %avail_out21 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 5, !dbg !4090
  %18 = load i32, i32* %avail_out21, align 8, !dbg !4090
  %19 = load i32*, i32** %destLen.addr, align 8, !dbg !4091
  %20 = load i32, i32* %19, align 4, !dbg !4092
  %sub = sub i32 %20, %18, !dbg !4092
  store i32 %sub, i32* %19, align 4, !dbg !4092
  %call22 = call i32 @BZ2_bzDecompressEnd(%struct.bz_stream* %strm), !dbg !4093
  store i32 0, i32* %retval, align 4, !dbg !4094
  br label %return, !dbg !4094

output_overflow_or_eof:                           ; preds = %if.then16
  %avail_out23 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %strm, i32 0, i32 5, !dbg !4095
  %21 = load i32, i32* %avail_out23, align 8, !dbg !4095
  %cmp24 = icmp ugt i32 %21, 0, !dbg !4097
  br i1 %cmp24, label %if.then25, label %if.else, !dbg !4098

if.then25:                                        ; preds = %output_overflow_or_eof
  %call26 = call i32 @BZ2_bzDecompressEnd(%struct.bz_stream* %strm), !dbg !4099
  store i32 -7, i32* %retval, align 4, !dbg !4101
  br label %return, !dbg !4101

if.else:                                          ; preds = %output_overflow_or_eof
  %call27 = call i32 @BZ2_bzDecompressEnd(%struct.bz_stream* %strm), !dbg !4102
  store i32 -8, i32* %retval, align 4, !dbg !4104
  br label %return, !dbg !4104

errhandler:                                       ; preds = %if.then19
  %call28 = call i32 @BZ2_bzDecompressEnd(%struct.bz_stream* %strm), !dbg !4105
  %22 = load i32, i32* %ret, align 4, !dbg !4106
  store i32 %22, i32* %retval, align 4, !dbg !4107
  br label %return, !dbg !4107

return:                                           ; preds = %errhandler, %if.else, %if.then25, %if.end20, %if.then12, %if.then
  %23 = load i32, i32* %retval, align 4, !dbg !4108
  ret i32 %23, !dbg !4108
}

; Function Attrs: nounwind uwtable
define i8* @BZ2_bzopen(i8* %path, i8* %mode) #0 !dbg !194 {
entry:
  %path.addr = alloca i8*, align 8
  %mode.addr = alloca i8*, align 8
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !4109, metadata !392), !dbg !4110
  store i8* %mode, i8** %mode.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %mode.addr, metadata !4111, metadata !392), !dbg !4112
  %0 = load i8*, i8** %path.addr, align 8, !dbg !4113
  %1 = load i8*, i8** %mode.addr, align 8, !dbg !4114
  %call = call i8* @bzopen_or_bzdopen(i8* %0, i32 -1, i8* %1, i32 0), !dbg !4115
  ret i8* %call, !dbg !4116
}

; Function Attrs: nounwind uwtable
define internal i8* @bzopen_or_bzdopen(i8* %path, i32 %fd, i8* %mode, i32 %open_mode) #0 !dbg !382 {
entry:
  %retval = alloca i8*, align 8
  %path.addr = alloca i8*, align 8
  %fd.addr = alloca i32, align 4
  %mode.addr = alloca i8*, align 8
  %open_mode.addr = alloca i32, align 4
  %bzerr = alloca i32, align 4
  %unused = alloca [5000 x i8], align 16
  %blockSize100k = alloca i32, align 4
  %writing = alloca i32, align 4
  %mode2 = alloca [10 x i8], align 1
  %fp = alloca %struct._IO_FILE*, align 8
  %bzfp = alloca i8*, align 8
  %verbosity = alloca i32, align 4
  %workFactor = alloca i32, align 4
  %smallMode = alloca i32, align 4
  %nUnused = alloca i32, align 4
  store i8* %path, i8** %path.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %path.addr, metadata !4117, metadata !392), !dbg !4118
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !4119, metadata !392), !dbg !4120
  store i8* %mode, i8** %mode.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %mode.addr, metadata !4121, metadata !392), !dbg !4122
  store i32 %open_mode, i32* %open_mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %open_mode.addr, metadata !4123, metadata !392), !dbg !4124
  call void @llvm.dbg.declare(metadata i32* %bzerr, metadata !4125, metadata !392), !dbg !4126
  call void @llvm.dbg.declare(metadata [5000 x i8]* %unused, metadata !4127, metadata !392), !dbg !4129
  call void @llvm.dbg.declare(metadata i32* %blockSize100k, metadata !4130, metadata !392), !dbg !4131
  store i32 9, i32* %blockSize100k, align 4, !dbg !4131
  call void @llvm.dbg.declare(metadata i32* %writing, metadata !4132, metadata !392), !dbg !4133
  store i32 0, i32* %writing, align 4, !dbg !4133
  call void @llvm.dbg.declare(metadata [10 x i8]* %mode2, metadata !4134, metadata !392), !dbg !4138
  %0 = bitcast [10 x i8]* %mode2 to i8*, !dbg !4138
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 10, i32 1, i1 false), !dbg !4138
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %fp, metadata !4139, metadata !392), !dbg !4140
  store %struct._IO_FILE* null, %struct._IO_FILE** %fp, align 8, !dbg !4140
  call void @llvm.dbg.declare(metadata i8** %bzfp, metadata !4141, metadata !392), !dbg !4142
  store i8* null, i8** %bzfp, align 8, !dbg !4142
  call void @llvm.dbg.declare(metadata i32* %verbosity, metadata !4143, metadata !392), !dbg !4144
  store i32 0, i32* %verbosity, align 4, !dbg !4144
  call void @llvm.dbg.declare(metadata i32* %workFactor, metadata !4145, metadata !392), !dbg !4146
  store i32 30, i32* %workFactor, align 4, !dbg !4146
  call void @llvm.dbg.declare(metadata i32* %smallMode, metadata !4147, metadata !392), !dbg !4148
  store i32 0, i32* %smallMode, align 4, !dbg !4148
  call void @llvm.dbg.declare(metadata i32* %nUnused, metadata !4149, metadata !392), !dbg !4150
  store i32 0, i32* %nUnused, align 4, !dbg !4150
  %1 = load i8*, i8** %mode.addr, align 8, !dbg !4151
  %cmp = icmp eq i8* %1, null, !dbg !4153
  br i1 %cmp, label %if.then, label %if.end, !dbg !4154

if.then:                                          ; preds = %entry
  store i8* null, i8** %retval, align 8, !dbg !4155
  br label %return, !dbg !4155

if.end:                                           ; preds = %entry
  br label %while.cond, !dbg !4157

while.cond:                                       ; preds = %sw.epilog, %if.end
  %2 = load i8*, i8** %mode.addr, align 8, !dbg !4158
  %3 = load i8, i8* %2, align 1, !dbg !4160
  %tobool = icmp ne i8 %3, 0, !dbg !4161
  br i1 %tobool, label %while.body, label %while.end, !dbg !4161

while.body:                                       ; preds = %while.cond
  %4 = load i8*, i8** %mode.addr, align 8, !dbg !4162
  %5 = load i8, i8* %4, align 1, !dbg !4164
  %conv = sext i8 %5 to i32, !dbg !4164
  switch i32 %conv, label %sw.default [
    i32 114, label %sw.bb
    i32 119, label %sw.bb1
    i32 115, label %sw.bb2
  ], !dbg !4165

sw.bb:                                            ; preds = %while.body
  store i32 0, i32* %writing, align 4, !dbg !4166
  br label %sw.epilog, !dbg !4168

sw.bb1:                                           ; preds = %while.body
  store i32 1, i32* %writing, align 4, !dbg !4169
  br label %sw.epilog, !dbg !4170

sw.bb2:                                           ; preds = %while.body
  store i32 1, i32* %smallMode, align 4, !dbg !4171
  br label %sw.epilog, !dbg !4172

sw.default:                                       ; preds = %while.body
  %6 = load i8*, i8** %mode.addr, align 8, !dbg !4173
  %7 = load i8, i8* %6, align 1, !dbg !4173
  %conv3 = sext i8 %7 to i32, !dbg !4173
  %idxprom = sext i32 %conv3 to i64, !dbg !4173
  %call = call i16** @__ctype_b_loc() #1, !dbg !4173
  %8 = load i16*, i16** %call, align 8, !dbg !4173
  %arrayidx = getelementptr inbounds i16, i16* %8, i64 %idxprom, !dbg !4173
  %9 = load i16, i16* %arrayidx, align 2, !dbg !4173
  %conv4 = zext i16 %9 to i32, !dbg !4173
  %and = and i32 %conv4, 2048, !dbg !4173
  %tobool5 = icmp ne i32 %and, 0, !dbg !4173
  br i1 %tobool5, label %if.then6, label %if.end8, !dbg !4175

if.then6:                                         ; preds = %sw.default
  %10 = load i8*, i8** %mode.addr, align 8, !dbg !4176
  %11 = load i8, i8* %10, align 1, !dbg !4178
  %conv7 = sext i8 %11 to i32, !dbg !4178
  %sub = sub nsw i32 %conv7, 48, !dbg !4179
  store i32 %sub, i32* %blockSize100k, align 4, !dbg !4180
  br label %if.end8, !dbg !4181

if.end8:                                          ; preds = %if.then6, %sw.default
  br label %sw.epilog, !dbg !4182

sw.epilog:                                        ; preds = %if.end8, %sw.bb2, %sw.bb1, %sw.bb
  %12 = load i8*, i8** %mode.addr, align 8, !dbg !4183
  %incdec.ptr = getelementptr inbounds i8, i8* %12, i32 1, !dbg !4183
  store i8* %incdec.ptr, i8** %mode.addr, align 8, !dbg !4183
  br label %while.cond, !dbg !4184

while.end:                                        ; preds = %while.cond
  %arraydecay = getelementptr inbounds [10 x i8], [10 x i8]* %mode2, i32 0, i32 0, !dbg !4186
  %13 = load i32, i32* %writing, align 4, !dbg !4187
  %tobool9 = icmp ne i32 %13, 0, !dbg !4187
  %cond = select i1 %tobool9, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.7, i32 0, i32 0), !dbg !4187
  %call10 = call i8* @strcat(i8* %arraydecay, i8* %cond) #10, !dbg !4188
  %arraydecay11 = getelementptr inbounds [10 x i8], [10 x i8]* %mode2, i32 0, i32 0, !dbg !4189
  %call12 = call i8* @strcat(i8* %arraydecay11, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.8, i32 0, i32 0)) #10, !dbg !4190
  %14 = load i32, i32* %open_mode.addr, align 4, !dbg !4191
  %cmp13 = icmp eq i32 %14, 0, !dbg !4193
  br i1 %cmp13, label %if.then15, label %if.else27, !dbg !4194

if.then15:                                        ; preds = %while.end
  %15 = load i8*, i8** %path.addr, align 8, !dbg !4195
  %cmp16 = icmp eq i8* %15, null, !dbg !4198
  br i1 %cmp16, label %if.then21, label %lor.lhs.false, !dbg !4199

lor.lhs.false:                                    ; preds = %if.then15
  %16 = load i8*, i8** %path.addr, align 8, !dbg !4200
  %call18 = call i32 @strcmp(i8* %16, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.9, i32 0, i32 0)) #11, !dbg !4202
  %cmp19 = icmp eq i32 %call18, 0, !dbg !4203
  br i1 %cmp19, label %if.then21, label %if.else, !dbg !4204

if.then21:                                        ; preds = %lor.lhs.false, %if.then15
  %17 = load i32, i32* %writing, align 4, !dbg !4205
  %tobool22 = icmp ne i32 %17, 0, !dbg !4205
  br i1 %tobool22, label %cond.true, label %cond.false, !dbg !4205

cond.true:                                        ; preds = %if.then21
  %18 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !4207
  br label %cond.end, !dbg !4209

cond.false:                                       ; preds = %if.then21
  %19 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !4210
  br label %cond.end, !dbg !4212

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond23 = phi %struct._IO_FILE* [ %18, %cond.true ], [ %19, %cond.false ], !dbg !4213
  store %struct._IO_FILE* %cond23, %struct._IO_FILE** %fp, align 8, !dbg !4215
  br label %if.end26, !dbg !4216

if.else:                                          ; preds = %lor.lhs.false
  %20 = load i8*, i8** %path.addr, align 8, !dbg !4217
  %arraydecay24 = getelementptr inbounds [10 x i8], [10 x i8]* %mode2, i32 0, i32 0, !dbg !4219
  %call25 = call %struct._IO_FILE* @fopen64(i8* %20, i8* %arraydecay24), !dbg !4220
  store %struct._IO_FILE* %call25, %struct._IO_FILE** %fp, align 8, !dbg !4221
  br label %if.end26

if.end26:                                         ; preds = %if.else, %cond.end
  br label %if.end30, !dbg !4222

if.else27:                                        ; preds = %while.end
  %21 = load i32, i32* %fd.addr, align 4, !dbg !4223
  %arraydecay28 = getelementptr inbounds [10 x i8], [10 x i8]* %mode2, i32 0, i32 0, !dbg !4225
  %call29 = call %struct._IO_FILE* @fdopen(i32 %21, i8* %arraydecay28) #10, !dbg !4226
  store %struct._IO_FILE* %call29, %struct._IO_FILE** %fp, align 8, !dbg !4227
  br label %if.end30

if.end30:                                         ; preds = %if.else27, %if.end26
  %22 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !4228
  %cmp31 = icmp eq %struct._IO_FILE* %22, null, !dbg !4230
  br i1 %cmp31, label %if.then33, label %if.end34, !dbg !4231

if.then33:                                        ; preds = %if.end30
  store i8* null, i8** %retval, align 8, !dbg !4232
  br label %return, !dbg !4232

if.end34:                                         ; preds = %if.end30
  %23 = load i32, i32* %writing, align 4, !dbg !4234
  %tobool35 = icmp ne i32 %23, 0, !dbg !4234
  br i1 %tobool35, label %if.then36, label %if.else46, !dbg !4236

if.then36:                                        ; preds = %if.end34
  %24 = load i32, i32* %blockSize100k, align 4, !dbg !4237
  %cmp37 = icmp slt i32 %24, 1, !dbg !4240
  br i1 %cmp37, label %if.then39, label %if.end40, !dbg !4241

if.then39:                                        ; preds = %if.then36
  store i32 1, i32* %blockSize100k, align 4, !dbg !4242
  br label %if.end40, !dbg !4244

if.end40:                                         ; preds = %if.then39, %if.then36
  %25 = load i32, i32* %blockSize100k, align 4, !dbg !4245
  %cmp41 = icmp sgt i32 %25, 9, !dbg !4247
  br i1 %cmp41, label %if.then43, label %if.end44, !dbg !4248

if.then43:                                        ; preds = %if.end40
  store i32 9, i32* %blockSize100k, align 4, !dbg !4249
  br label %if.end44, !dbg !4251

if.end44:                                         ; preds = %if.then43, %if.end40
  %26 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !4252
  %27 = load i32, i32* %blockSize100k, align 4, !dbg !4253
  %28 = load i32, i32* %verbosity, align 4, !dbg !4254
  %29 = load i32, i32* %workFactor, align 4, !dbg !4255
  %call45 = call i8* @BZ2_bzWriteOpen(i32* %bzerr, %struct._IO_FILE* %26, i32 %27, i32 %28, i32 %29), !dbg !4256
  store i8* %call45, i8** %bzfp, align 8, !dbg !4257
  br label %if.end49, !dbg !4258

if.else46:                                        ; preds = %if.end34
  %30 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !4259
  %31 = load i32, i32* %verbosity, align 4, !dbg !4261
  %32 = load i32, i32* %smallMode, align 4, !dbg !4262
  %arraydecay47 = getelementptr inbounds [5000 x i8], [5000 x i8]* %unused, i32 0, i32 0, !dbg !4263
  %33 = load i32, i32* %nUnused, align 4, !dbg !4264
  %call48 = call i8* @BZ2_bzReadOpen(i32* %bzerr, %struct._IO_FILE* %30, i32 %31, i32 %32, i8* %arraydecay47, i32 %33), !dbg !4265
  store i8* %call48, i8** %bzfp, align 8, !dbg !4266
  br label %if.end49

if.end49:                                         ; preds = %if.else46, %if.end44
  %34 = load i8*, i8** %bzfp, align 8, !dbg !4267
  %cmp50 = icmp eq i8* %34, null, !dbg !4269
  br i1 %cmp50, label %if.then52, label %if.end60, !dbg !4270

if.then52:                                        ; preds = %if.end49
  %35 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !4271
  %36 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !4274
  %cmp53 = icmp ne %struct._IO_FILE* %35, %36, !dbg !4275
  br i1 %cmp53, label %land.lhs.true, label %if.end59, !dbg !4276

land.lhs.true:                                    ; preds = %if.then52
  %37 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !4277
  %38 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !4279
  %cmp55 = icmp ne %struct._IO_FILE* %37, %38, !dbg !4280
  br i1 %cmp55, label %if.then57, label %if.end59, !dbg !4281

if.then57:                                        ; preds = %land.lhs.true
  %39 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !4282
  %call58 = call i32 @fclose(%struct._IO_FILE* %39), !dbg !4284
  br label %if.end59, !dbg !4284

if.end59:                                         ; preds = %if.then57, %land.lhs.true, %if.then52
  store i8* null, i8** %retval, align 8, !dbg !4285
  br label %return, !dbg !4285

if.end60:                                         ; preds = %if.end49
  %40 = load i8*, i8** %bzfp, align 8, !dbg !4286
  store i8* %40, i8** %retval, align 8, !dbg !4287
  br label %return, !dbg !4287

return:                                           ; preds = %if.end60, %if.end59, %if.then33, %if.then
  %41 = load i8*, i8** %retval, align 8, !dbg !4288
  ret i8* %41, !dbg !4288
}

; Function Attrs: nounwind uwtable
define i8* @BZ2_bzdopen(i32 %fd, i8* %mode) #0 !dbg !197 {
entry:
  %fd.addr = alloca i32, align 4
  %mode.addr = alloca i8*, align 8
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !4289, metadata !392), !dbg !4290
  store i8* %mode, i8** %mode.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %mode.addr, metadata !4291, metadata !392), !dbg !4292
  %0 = load i32, i32* %fd.addr, align 4, !dbg !4293
  %1 = load i8*, i8** %mode.addr, align 8, !dbg !4294
  %call = call i8* @bzopen_or_bzdopen(i8* null, i32 %0, i8* %1, i32 1), !dbg !4295
  ret i8* %call, !dbg !4296
}

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzread(i8* %b, i8* %buf, i32 %len) #0 !dbg !200 {
entry:
  %retval = alloca i32, align 4
  %b.addr = alloca i8*, align 8
  %buf.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %bzerr = alloca i32, align 4
  %nread = alloca i32, align 4
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !4297, metadata !392), !dbg !4298
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !4299, metadata !392), !dbg !4300
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !4301, metadata !392), !dbg !4302
  call void @llvm.dbg.declare(metadata i32* %bzerr, metadata !4303, metadata !392), !dbg !4304
  call void @llvm.dbg.declare(metadata i32* %nread, metadata !4305, metadata !392), !dbg !4306
  %0 = load i8*, i8** %b.addr, align 8, !dbg !4307
  %1 = bitcast i8* %0 to %struct.bzFile*, !dbg !4309
  %lastErr = getelementptr inbounds %struct.bzFile, %struct.bzFile* %1, i32 0, i32 5, !dbg !4310
  %2 = load i32, i32* %lastErr, align 8, !dbg !4310
  %cmp = icmp eq i32 %2, 4, !dbg !4311
  br i1 %cmp, label %if.then, label %if.end, !dbg !4312

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !4313
  br label %return, !dbg !4313

if.end:                                           ; preds = %entry
  %3 = load i8*, i8** %b.addr, align 8, !dbg !4315
  %4 = load i8*, i8** %buf.addr, align 8, !dbg !4316
  %5 = load i32, i32* %len.addr, align 4, !dbg !4317
  %call = call i32 @BZ2_bzRead(i32* %bzerr, i8* %3, i8* %4, i32 %5), !dbg !4318
  store i32 %call, i32* %nread, align 4, !dbg !4319
  %6 = load i32, i32* %bzerr, align 4, !dbg !4320
  %cmp1 = icmp eq i32 %6, 0, !dbg !4322
  br i1 %cmp1, label %if.then3, label %lor.lhs.false, !dbg !4323

lor.lhs.false:                                    ; preds = %if.end
  %7 = load i32, i32* %bzerr, align 4, !dbg !4324
  %cmp2 = icmp eq i32 %7, 4, !dbg !4326
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !4327

if.then3:                                         ; preds = %lor.lhs.false, %if.end
  %8 = load i32, i32* %nread, align 4, !dbg !4328
  store i32 %8, i32* %retval, align 4, !dbg !4330
  br label %return, !dbg !4330

if.else:                                          ; preds = %lor.lhs.false
  store i32 -1, i32* %retval, align 4, !dbg !4331
  br label %return, !dbg !4331

return:                                           ; preds = %if.else, %if.then3, %if.then
  %9 = load i32, i32* %retval, align 4, !dbg !4333
  ret i32 %9, !dbg !4333
}

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzwrite(i8* %b, i8* %buf, i32 %len) #0 !dbg !203 {
entry:
  %retval = alloca i32, align 4
  %b.addr = alloca i8*, align 8
  %buf.addr = alloca i8*, align 8
  %len.addr = alloca i32, align 4
  %bzerr = alloca i32, align 4
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !4334, metadata !392), !dbg !4335
  store i8* %buf, i8** %buf.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buf.addr, metadata !4336, metadata !392), !dbg !4337
  store i32 %len, i32* %len.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %len.addr, metadata !4338, metadata !392), !dbg !4339
  call void @llvm.dbg.declare(metadata i32* %bzerr, metadata !4340, metadata !392), !dbg !4341
  %0 = load i8*, i8** %b.addr, align 8, !dbg !4342
  %1 = load i8*, i8** %buf.addr, align 8, !dbg !4343
  %2 = load i32, i32* %len.addr, align 4, !dbg !4344
  call void @BZ2_bzWrite(i32* %bzerr, i8* %0, i8* %1, i32 %2), !dbg !4345
  %3 = load i32, i32* %bzerr, align 4, !dbg !4346
  %cmp = icmp eq i32 %3, 0, !dbg !4348
  br i1 %cmp, label %if.then, label %if.else, !dbg !4349

if.then:                                          ; preds = %entry
  %4 = load i32, i32* %len.addr, align 4, !dbg !4350
  store i32 %4, i32* %retval, align 4, !dbg !4352
  br label %return, !dbg !4352

if.else:                                          ; preds = %entry
  store i32 -1, i32* %retval, align 4, !dbg !4353
  br label %return, !dbg !4353

return:                                           ; preds = %if.else, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !4355
  ret i32 %5, !dbg !4355
}

; Function Attrs: nounwind uwtable
define i32 @BZ2_bzflush(i8* %b) #0 !dbg !204 {
entry:
  %b.addr = alloca i8*, align 8
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !4356, metadata !392), !dbg !4357
  %0 = load i8*, i8** %b.addr, align 8, !dbg !4358
  ret i32 0, !dbg !4359
}

; Function Attrs: nounwind uwtable
define void @BZ2_bzclose(i8* %b) #0 !dbg !207 {
entry:
  %b.addr = alloca i8*, align 8
  %bzerr = alloca i32, align 4
  %fp = alloca %struct._IO_FILE*, align 8
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !4360, metadata !392), !dbg !4361
  call void @llvm.dbg.declare(metadata i32* %bzerr, metadata !4362, metadata !392), !dbg !4363
  call void @llvm.dbg.declare(metadata %struct._IO_FILE** %fp, metadata !4364, metadata !392), !dbg !4365
  %0 = load i8*, i8** %b.addr, align 8, !dbg !4366
  %cmp = icmp eq i8* %0, null, !dbg !4368
  br i1 %cmp, label %if.then, label %if.end, !dbg !4369

if.then:                                          ; preds = %entry
  br label %if.end9, !dbg !4370

if.end:                                           ; preds = %entry
  %1 = load i8*, i8** %b.addr, align 8, !dbg !4373
  %2 = bitcast i8* %1 to %struct.bzFile*, !dbg !4374
  %handle = getelementptr inbounds %struct.bzFile, %struct.bzFile* %2, i32 0, i32 0, !dbg !4375
  %3 = load %struct._IO_FILE*, %struct._IO_FILE** %handle, align 8, !dbg !4375
  store %struct._IO_FILE* %3, %struct._IO_FILE** %fp, align 8, !dbg !4376
  %4 = load i8*, i8** %b.addr, align 8, !dbg !4377
  %5 = bitcast i8* %4 to %struct.bzFile*, !dbg !4379
  %writing = getelementptr inbounds %struct.bzFile, %struct.bzFile* %5, i32 0, i32 3, !dbg !4380
  %6 = load i8, i8* %writing, align 4, !dbg !4380
  %tobool = icmp ne i8 %6, 0, !dbg !4381
  br i1 %tobool, label %if.then1, label %if.else, !dbg !4382

if.then1:                                         ; preds = %if.end
  %7 = load i8*, i8** %b.addr, align 8, !dbg !4383
  call void @BZ2_bzWriteClose(i32* %bzerr, i8* %7, i32 0, i32* null, i32* null), !dbg !4385
  %8 = load i32, i32* %bzerr, align 4, !dbg !4386
  %cmp2 = icmp ne i32 %8, 0, !dbg !4388
  br i1 %cmp2, label %if.then3, label %if.end4, !dbg !4389

if.then3:                                         ; preds = %if.then1
  %9 = load i8*, i8** %b.addr, align 8, !dbg !4390
  call void @BZ2_bzWriteClose(i32* null, i8* %9, i32 1, i32* null, i32* null), !dbg !4392
  br label %if.end4, !dbg !4393

if.end4:                                          ; preds = %if.then3, %if.then1
  br label %if.end5, !dbg !4394

if.else:                                          ; preds = %if.end
  %10 = load i8*, i8** %b.addr, align 8, !dbg !4395
  call void @BZ2_bzReadClose(i32* %bzerr, i8* %10), !dbg !4397
  br label %if.end5

if.end5:                                          ; preds = %if.else, %if.end4
  %11 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !4398
  %12 = load %struct._IO_FILE*, %struct._IO_FILE** @stdin, align 8, !dbg !4400
  %cmp6 = icmp ne %struct._IO_FILE* %11, %12, !dbg !4401
  br i1 %cmp6, label %land.lhs.true, label %if.end9, !dbg !4402

land.lhs.true:                                    ; preds = %if.end5
  %13 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !4403
  %14 = load %struct._IO_FILE*, %struct._IO_FILE** @stdout, align 8, !dbg !4405
  %cmp7 = icmp ne %struct._IO_FILE* %13, %14, !dbg !4406
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !4407

if.then8:                                         ; preds = %land.lhs.true
  %15 = load %struct._IO_FILE*, %struct._IO_FILE** %fp, align 8, !dbg !4408
  %call = call i32 @fclose(%struct._IO_FILE* %15), !dbg !4410
  br label %if.end9, !dbg !4411

if.end9:                                          ; preds = %if.then, %if.then8, %land.lhs.true, %if.end5
  ret void, !dbg !4412
}

declare i32 @fclose(%struct._IO_FILE*) #2

; Function Attrs: nounwind uwtable
define i8* @BZ2_bzerror(i8* %b, i32* %errnum) #0 !dbg !210 {
entry:
  %b.addr = alloca i8*, align 8
  %errnum.addr = alloca i32*, align 8
  %err = alloca i32, align 4
  store i8* %b, i8** %b.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %b.addr, metadata !4413, metadata !392), !dbg !4414
  store i32* %errnum, i32** %errnum.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %errnum.addr, metadata !4415, metadata !392), !dbg !4416
  call void @llvm.dbg.declare(metadata i32* %err, metadata !4417, metadata !392), !dbg !4418
  %0 = load i8*, i8** %b.addr, align 8, !dbg !4419
  %1 = bitcast i8* %0 to %struct.bzFile*, !dbg !4420
  %lastErr = getelementptr inbounds %struct.bzFile, %struct.bzFile* %1, i32 0, i32 5, !dbg !4421
  %2 = load i32, i32* %lastErr, align 8, !dbg !4421
  store i32 %2, i32* %err, align 4, !dbg !4418
  %3 = load i32, i32* %err, align 4, !dbg !4422
  %cmp = icmp sgt i32 %3, 0, !dbg !4424
  br i1 %cmp, label %if.then, label %if.end, !dbg !4425

if.then:                                          ; preds = %entry
  store i32 0, i32* %err, align 4, !dbg !4426
  br label %if.end, !dbg !4428

if.end:                                           ; preds = %if.then, %entry
  %4 = load i32, i32* %err, align 4, !dbg !4429
  %5 = load i32*, i32** %errnum.addr, align 8, !dbg !4430
  store i32 %4, i32* %5, align 4, !dbg !4431
  %6 = load i32, i32* %err, align 4, !dbg !4432
  %mul = mul nsw i32 %6, -1, !dbg !4433
  %idxprom = sext i32 %mul to i64, !dbg !4434
  %arrayidx = getelementptr inbounds [16 x i8*], [16 x i8*]* @bzerrorstrings, i64 0, i64 %idxprom, !dbg !4434
  %7 = load i8*, i8** %arrayidx, align 8, !dbg !4434
  ret i8* %7, !dbg !4435
}

; Function Attrs: nounwind uwtable
define internal zeroext i8 @copy_output_until_stop(%struct.EState* %s) #0 !dbg !287 {
entry:
  %s.addr = alloca %struct.EState*, align 8
  %progress_out = alloca i8, align 1
  store %struct.EState* %s, %struct.EState** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.EState** %s.addr, metadata !4436, metadata !392), !dbg !4437
  call void @llvm.dbg.declare(metadata i8* %progress_out, metadata !4438, metadata !392), !dbg !4439
  store i8 0, i8* %progress_out, align 1, !dbg !4439
  br label %while.body, !dbg !4440

while.body:                                       ; preds = %entry, %if.end19
  %0 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4441
  %strm = getelementptr inbounds %struct.EState, %struct.EState* %0, i32 0, i32 0, !dbg !4444
  %1 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !4444
  %avail_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %1, i32 0, i32 5, !dbg !4445
  %2 = load i32, i32* %avail_out, align 8, !dbg !4445
  %cmp = icmp eq i32 %2, 0, !dbg !4446
  br i1 %cmp, label %if.then, label %if.end, !dbg !4447

if.then:                                          ; preds = %while.body
  br label %while.end, !dbg !4448

if.end:                                           ; preds = %while.body
  %3 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4450
  %state_out_pos = getelementptr inbounds %struct.EState, %struct.EState* %3, i32 0, i32 20, !dbg !4452
  %4 = load i32, i32* %state_out_pos, align 8, !dbg !4452
  %5 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4453
  %numZ = getelementptr inbounds %struct.EState, %struct.EState* %5, i32 0, i32 19, !dbg !4454
  %6 = load i32, i32* %numZ, align 4, !dbg !4454
  %cmp1 = icmp sge i32 %4, %6, !dbg !4455
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !4456

if.then2:                                         ; preds = %if.end
  br label %while.end, !dbg !4457

if.end3:                                          ; preds = %if.end
  store i8 1, i8* %progress_out, align 1, !dbg !4459
  %7 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4460
  %state_out_pos4 = getelementptr inbounds %struct.EState, %struct.EState* %7, i32 0, i32 20, !dbg !4461
  %8 = load i32, i32* %state_out_pos4, align 8, !dbg !4461
  %idxprom = sext i32 %8 to i64, !dbg !4462
  %9 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4462
  %zbits = getelementptr inbounds %struct.EState, %struct.EState* %9, i32 0, i32 11, !dbg !4463
  %10 = load i8*, i8** %zbits, align 8, !dbg !4463
  %arrayidx = getelementptr inbounds i8, i8* %10, i64 %idxprom, !dbg !4462
  %11 = load i8, i8* %arrayidx, align 1, !dbg !4462
  %12 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4464
  %strm5 = getelementptr inbounds %struct.EState, %struct.EState* %12, i32 0, i32 0, !dbg !4465
  %13 = load %struct.bz_stream*, %struct.bz_stream** %strm5, align 8, !dbg !4465
  %next_out = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %13, i32 0, i32 4, !dbg !4466
  %14 = load i8*, i8** %next_out, align 8, !dbg !4466
  store i8 %11, i8* %14, align 1, !dbg !4467
  %15 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4468
  %state_out_pos6 = getelementptr inbounds %struct.EState, %struct.EState* %15, i32 0, i32 20, !dbg !4469
  %16 = load i32, i32* %state_out_pos6, align 8, !dbg !4470
  %inc = add nsw i32 %16, 1, !dbg !4470
  store i32 %inc, i32* %state_out_pos6, align 8, !dbg !4470
  %17 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4471
  %strm7 = getelementptr inbounds %struct.EState, %struct.EState* %17, i32 0, i32 0, !dbg !4472
  %18 = load %struct.bz_stream*, %struct.bz_stream** %strm7, align 8, !dbg !4472
  %avail_out8 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %18, i32 0, i32 5, !dbg !4473
  %19 = load i32, i32* %avail_out8, align 8, !dbg !4474
  %dec = add i32 %19, -1, !dbg !4474
  store i32 %dec, i32* %avail_out8, align 8, !dbg !4474
  %20 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4475
  %strm9 = getelementptr inbounds %struct.EState, %struct.EState* %20, i32 0, i32 0, !dbg !4476
  %21 = load %struct.bz_stream*, %struct.bz_stream** %strm9, align 8, !dbg !4476
  %next_out10 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %21, i32 0, i32 4, !dbg !4477
  %22 = load i8*, i8** %next_out10, align 8, !dbg !4478
  %incdec.ptr = getelementptr inbounds i8, i8* %22, i32 1, !dbg !4478
  store i8* %incdec.ptr, i8** %next_out10, align 8, !dbg !4478
  %23 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4479
  %strm11 = getelementptr inbounds %struct.EState, %struct.EState* %23, i32 0, i32 0, !dbg !4480
  %24 = load %struct.bz_stream*, %struct.bz_stream** %strm11, align 8, !dbg !4480
  %total_out_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %24, i32 0, i32 6, !dbg !4481
  %25 = load i32, i32* %total_out_lo32, align 4, !dbg !4482
  %inc12 = add i32 %25, 1, !dbg !4482
  store i32 %inc12, i32* %total_out_lo32, align 4, !dbg !4482
  %26 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4483
  %strm13 = getelementptr inbounds %struct.EState, %struct.EState* %26, i32 0, i32 0, !dbg !4485
  %27 = load %struct.bz_stream*, %struct.bz_stream** %strm13, align 8, !dbg !4485
  %total_out_lo3214 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %27, i32 0, i32 6, !dbg !4486
  %28 = load i32, i32* %total_out_lo3214, align 4, !dbg !4486
  %cmp15 = icmp eq i32 %28, 0, !dbg !4487
  br i1 %cmp15, label %if.then16, label %if.end19, !dbg !4488

if.then16:                                        ; preds = %if.end3
  %29 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4489
  %strm17 = getelementptr inbounds %struct.EState, %struct.EState* %29, i32 0, i32 0, !dbg !4491
  %30 = load %struct.bz_stream*, %struct.bz_stream** %strm17, align 8, !dbg !4491
  %total_out_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %30, i32 0, i32 7, !dbg !4492
  %31 = load i32, i32* %total_out_hi32, align 8, !dbg !4493
  %inc18 = add i32 %31, 1, !dbg !4493
  store i32 %inc18, i32* %total_out_hi32, align 8, !dbg !4493
  br label %if.end19, !dbg !4489

if.end19:                                         ; preds = %if.then16, %if.end3
  br label %while.body, !dbg !4494

while.end:                                        ; preds = %if.then2, %if.then
  %32 = load i8, i8* %progress_out, align 1, !dbg !4496
  ret i8 %32, !dbg !4497
}

; Function Attrs: nounwind uwtable
define internal zeroext i8 @copy_input_until_stop(%struct.EState* %s) #0 !dbg !290 {
entry:
  %s.addr = alloca %struct.EState*, align 8
  %progress_in = alloca i8, align 1
  %zchh = alloca i32, align 4
  %ch = alloca i8, align 1
  %zchh77 = alloca i32, align 4
  %ch89 = alloca i8, align 1
  store %struct.EState* %s, %struct.EState** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.EState** %s.addr, metadata !4498, metadata !392), !dbg !4499
  call void @llvm.dbg.declare(metadata i8* %progress_in, metadata !4500, metadata !392), !dbg !4501
  store i8 0, i8* %progress_in, align 1, !dbg !4501
  %0 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4502
  %mode = getelementptr inbounds %struct.EState, %struct.EState* %0, i32 0, i32 1, !dbg !4504
  %1 = load i32, i32* %mode, align 8, !dbg !4504
  %cmp = icmp eq i32 %1, 2, !dbg !4505
  br i1 %cmp, label %if.then, label %if.else59, !dbg !4506

if.then:                                          ; preds = %entry
  br label %while.body, !dbg !4507

while.body:                                       ; preds = %if.then, %if.end58
  %2 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4509
  %nblock = getelementptr inbounds %struct.EState, %struct.EState* %2, i32 0, i32 17, !dbg !4512
  %3 = load i32, i32* %nblock, align 4, !dbg !4512
  %4 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4513
  %nblockMAX = getelementptr inbounds %struct.EState, %struct.EState* %4, i32 0, i32 18, !dbg !4514
  %5 = load i32, i32* %nblockMAX, align 8, !dbg !4514
  %cmp1 = icmp sge i32 %3, %5, !dbg !4515
  br i1 %cmp1, label %if.then2, label %if.end, !dbg !4516

if.then2:                                         ; preds = %while.body
  br label %while.end, !dbg !4517

if.end:                                           ; preds = %while.body
  %6 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4519
  %strm = getelementptr inbounds %struct.EState, %struct.EState* %6, i32 0, i32 0, !dbg !4521
  %7 = load %struct.bz_stream*, %struct.bz_stream** %strm, align 8, !dbg !4521
  %avail_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %7, i32 0, i32 1, !dbg !4522
  %8 = load i32, i32* %avail_in, align 8, !dbg !4522
  %cmp3 = icmp eq i32 %8, 0, !dbg !4523
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !4524

if.then4:                                         ; preds = %if.end
  br label %while.end, !dbg !4525

if.end5:                                          ; preds = %if.end
  store i8 1, i8* %progress_in, align 1, !dbg !4527
  call void @llvm.dbg.declare(metadata i32* %zchh, metadata !4528, metadata !392), !dbg !4530
  %9 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4530
  %strm6 = getelementptr inbounds %struct.EState, %struct.EState* %9, i32 0, i32 0, !dbg !4530
  %10 = load %struct.bz_stream*, %struct.bz_stream** %strm6, align 8, !dbg !4530
  %next_in = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %10, i32 0, i32 0, !dbg !4530
  %11 = load i8*, i8** %next_in, align 8, !dbg !4530
  %12 = load i8, i8* %11, align 1, !dbg !4530
  %conv = zext i8 %12 to i32, !dbg !4530
  store i32 %conv, i32* %zchh, align 4, !dbg !4530
  %13 = load i32, i32* %zchh, align 4, !dbg !4531
  %14 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4531
  %state_in_ch = getelementptr inbounds %struct.EState, %struct.EState* %14, i32 0, i32 13, !dbg !4531
  %15 = load i32, i32* %state_in_ch, align 4, !dbg !4531
  %cmp7 = icmp ne i32 %13, %15, !dbg !4531
  br i1 %cmp7, label %land.lhs.true, label %if.else, !dbg !4531

land.lhs.true:                                    ; preds = %if.end5
  %16 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4533
  %state_in_len = getelementptr inbounds %struct.EState, %struct.EState* %16, i32 0, i32 14, !dbg !4533
  %17 = load i32, i32* %state_in_len, align 8, !dbg !4533
  %cmp9 = icmp eq i32 %17, 1, !dbg !4533
  br i1 %cmp9, label %if.then11, label %if.else, !dbg !4533

if.then11:                                        ; preds = %land.lhs.true
  call void @llvm.dbg.declare(metadata i8* %ch, metadata !4535, metadata !392), !dbg !4537
  %18 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4538
  %state_in_ch12 = getelementptr inbounds %struct.EState, %struct.EState* %18, i32 0, i32 13, !dbg !4538
  %19 = load i32, i32* %state_in_ch12, align 4, !dbg !4538
  %conv13 = trunc i32 %19 to i8, !dbg !4538
  store i8 %conv13, i8* %ch, align 1, !dbg !4538
  %20 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4538
  %blockCRC = getelementptr inbounds %struct.EState, %struct.EState* %20, i32 0, i32 26, !dbg !4538
  %21 = load i32, i32* %blockCRC, align 8, !dbg !4538
  %shl = shl i32 %21, 8, !dbg !4538
  %22 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4538
  %blockCRC14 = getelementptr inbounds %struct.EState, %struct.EState* %22, i32 0, i32 26, !dbg !4538
  %23 = load i32, i32* %blockCRC14, align 8, !dbg !4538
  %shr = lshr i32 %23, 24, !dbg !4538
  %24 = load i8, i8* %ch, align 1, !dbg !4538
  %conv15 = zext i8 %24 to i32, !dbg !4538
  %xor = xor i32 %shr, %conv15, !dbg !4538
  %idxprom = zext i32 %xor to i64, !dbg !4538
  %arrayidx = getelementptr inbounds [256 x i32], [256 x i32]* @BZ2_crc32Table, i64 0, i64 %idxprom, !dbg !4538
  %25 = load i32, i32* %arrayidx, align 4, !dbg !4538
  %xor16 = xor i32 %shl, %25, !dbg !4538
  %26 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4538
  %blockCRC17 = getelementptr inbounds %struct.EState, %struct.EState* %26, i32 0, i32 26, !dbg !4538
  store i32 %xor16, i32* %blockCRC17, align 8, !dbg !4538
  %27 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4538
  %state_in_ch18 = getelementptr inbounds %struct.EState, %struct.EState* %27, i32 0, i32 13, !dbg !4538
  %28 = load i32, i32* %state_in_ch18, align 4, !dbg !4538
  %idxprom19 = zext i32 %28 to i64, !dbg !4538
  %29 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4538
  %inUse = getelementptr inbounds %struct.EState, %struct.EState* %29, i32 0, i32 22, !dbg !4538
  %arrayidx20 = getelementptr inbounds [256 x i8], [256 x i8]* %inUse, i64 0, i64 %idxprom19, !dbg !4538
  store i8 1, i8* %arrayidx20, align 1, !dbg !4538
  %30 = load i8, i8* %ch, align 1, !dbg !4538
  %31 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4538
  %nblock21 = getelementptr inbounds %struct.EState, %struct.EState* %31, i32 0, i32 17, !dbg !4538
  %32 = load i32, i32* %nblock21, align 4, !dbg !4538
  %idxprom22 = sext i32 %32 to i64, !dbg !4538
  %33 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4538
  %block = getelementptr inbounds %struct.EState, %struct.EState* %33, i32 0, i32 9, !dbg !4538
  %34 = load i8*, i8** %block, align 8, !dbg !4538
  %arrayidx23 = getelementptr inbounds i8, i8* %34, i64 %idxprom22, !dbg !4538
  store i8 %30, i8* %arrayidx23, align 1, !dbg !4538
  %35 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4538
  %nblock24 = getelementptr inbounds %struct.EState, %struct.EState* %35, i32 0, i32 17, !dbg !4538
  %36 = load i32, i32* %nblock24, align 4, !dbg !4538
  %inc = add nsw i32 %36, 1, !dbg !4538
  store i32 %inc, i32* %nblock24, align 4, !dbg !4538
  %37 = load i32, i32* %zchh, align 4, !dbg !4538
  %38 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4538
  %state_in_ch25 = getelementptr inbounds %struct.EState, %struct.EState* %38, i32 0, i32 13, !dbg !4538
  store i32 %37, i32* %state_in_ch25, align 4, !dbg !4538
  br label %if.end44, !dbg !4538

if.else:                                          ; preds = %land.lhs.true, %if.end5
  %39 = load i32, i32* %zchh, align 4, !dbg !4540
  %40 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4540
  %state_in_ch26 = getelementptr inbounds %struct.EState, %struct.EState* %40, i32 0, i32 13, !dbg !4540
  %41 = load i32, i32* %state_in_ch26, align 4, !dbg !4540
  %cmp27 = icmp ne i32 %39, %41, !dbg !4540
  br i1 %cmp27, label %if.then32, label %lor.lhs.false, !dbg !4540

lor.lhs.false:                                    ; preds = %if.else
  %42 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4543
  %state_in_len29 = getelementptr inbounds %struct.EState, %struct.EState* %42, i32 0, i32 14, !dbg !4543
  %43 = load i32, i32* %state_in_len29, align 8, !dbg !4543
  %cmp30 = icmp eq i32 %43, 255, !dbg !4543
  br i1 %cmp30, label %if.then32, label %if.else40, !dbg !4543

if.then32:                                        ; preds = %lor.lhs.false, %if.else
  %44 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4545
  %state_in_ch33 = getelementptr inbounds %struct.EState, %struct.EState* %44, i32 0, i32 13, !dbg !4545
  %45 = load i32, i32* %state_in_ch33, align 4, !dbg !4545
  %cmp34 = icmp ult i32 %45, 256, !dbg !4545
  br i1 %cmp34, label %if.then36, label %if.end37, !dbg !4545

if.then36:                                        ; preds = %if.then32
  %46 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4549
  call void @add_pair_to_block(%struct.EState* %46), !dbg !4549
  br label %if.end37, !dbg !4549

if.end37:                                         ; preds = %if.then36, %if.then32
  %47 = load i32, i32* %zchh, align 4, !dbg !4551
  %48 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4551
  %state_in_ch38 = getelementptr inbounds %struct.EState, %struct.EState* %48, i32 0, i32 13, !dbg !4551
  store i32 %47, i32* %state_in_ch38, align 4, !dbg !4551
  %49 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4551
  %state_in_len39 = getelementptr inbounds %struct.EState, %struct.EState* %49, i32 0, i32 14, !dbg !4551
  store i32 1, i32* %state_in_len39, align 8, !dbg !4551
  br label %if.end43, !dbg !4551

if.else40:                                        ; preds = %lor.lhs.false
  %50 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4553
  %state_in_len41 = getelementptr inbounds %struct.EState, %struct.EState* %50, i32 0, i32 14, !dbg !4553
  %51 = load i32, i32* %state_in_len41, align 8, !dbg !4553
  %inc42 = add nsw i32 %51, 1, !dbg !4553
  store i32 %inc42, i32* %state_in_len41, align 8, !dbg !4553
  br label %if.end43

if.end43:                                         ; preds = %if.else40, %if.end37
  br label %if.end44

if.end44:                                         ; preds = %if.end43, %if.then11
  %52 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4556
  %strm45 = getelementptr inbounds %struct.EState, %struct.EState* %52, i32 0, i32 0, !dbg !4557
  %53 = load %struct.bz_stream*, %struct.bz_stream** %strm45, align 8, !dbg !4557
  %next_in46 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %53, i32 0, i32 0, !dbg !4558
  %54 = load i8*, i8** %next_in46, align 8, !dbg !4559
  %incdec.ptr = getelementptr inbounds i8, i8* %54, i32 1, !dbg !4559
  store i8* %incdec.ptr, i8** %next_in46, align 8, !dbg !4559
  %55 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4560
  %strm47 = getelementptr inbounds %struct.EState, %struct.EState* %55, i32 0, i32 0, !dbg !4561
  %56 = load %struct.bz_stream*, %struct.bz_stream** %strm47, align 8, !dbg !4561
  %avail_in48 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %56, i32 0, i32 1, !dbg !4562
  %57 = load i32, i32* %avail_in48, align 8, !dbg !4563
  %dec = add i32 %57, -1, !dbg !4563
  store i32 %dec, i32* %avail_in48, align 8, !dbg !4563
  %58 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4564
  %strm49 = getelementptr inbounds %struct.EState, %struct.EState* %58, i32 0, i32 0, !dbg !4565
  %59 = load %struct.bz_stream*, %struct.bz_stream** %strm49, align 8, !dbg !4565
  %total_in_lo32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %59, i32 0, i32 2, !dbg !4566
  %60 = load i32, i32* %total_in_lo32, align 4, !dbg !4567
  %inc50 = add i32 %60, 1, !dbg !4567
  store i32 %inc50, i32* %total_in_lo32, align 4, !dbg !4567
  %61 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4568
  %strm51 = getelementptr inbounds %struct.EState, %struct.EState* %61, i32 0, i32 0, !dbg !4570
  %62 = load %struct.bz_stream*, %struct.bz_stream** %strm51, align 8, !dbg !4570
  %total_in_lo3252 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %62, i32 0, i32 2, !dbg !4571
  %63 = load i32, i32* %total_in_lo3252, align 4, !dbg !4571
  %cmp53 = icmp eq i32 %63, 0, !dbg !4572
  br i1 %cmp53, label %if.then55, label %if.end58, !dbg !4573

if.then55:                                        ; preds = %if.end44
  %64 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4574
  %strm56 = getelementptr inbounds %struct.EState, %struct.EState* %64, i32 0, i32 0, !dbg !4576
  %65 = load %struct.bz_stream*, %struct.bz_stream** %strm56, align 8, !dbg !4576
  %total_in_hi32 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %65, i32 0, i32 3, !dbg !4577
  %66 = load i32, i32* %total_in_hi32, align 8, !dbg !4578
  %inc57 = add i32 %66, 1, !dbg !4578
  store i32 %inc57, i32* %total_in_hi32, align 8, !dbg !4578
  br label %if.end58, !dbg !4574

if.end58:                                         ; preds = %if.then55, %if.end44
  br label %while.body, !dbg !4579

while.end:                                        ; preds = %if.then4, %if.then2
  br label %if.end155, !dbg !4581

if.else59:                                        ; preds = %entry
  br label %while.body60, !dbg !4582

while.body60:                                     ; preds = %if.else59, %if.end151
  %67 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4584
  %nblock61 = getelementptr inbounds %struct.EState, %struct.EState* %67, i32 0, i32 17, !dbg !4587
  %68 = load i32, i32* %nblock61, align 4, !dbg !4587
  %69 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4588
  %nblockMAX62 = getelementptr inbounds %struct.EState, %struct.EState* %69, i32 0, i32 18, !dbg !4589
  %70 = load i32, i32* %nblockMAX62, align 8, !dbg !4589
  %cmp63 = icmp sge i32 %68, %70, !dbg !4590
  br i1 %cmp63, label %if.then65, label %if.end66, !dbg !4591

if.then65:                                        ; preds = %while.body60
  br label %while.end154, !dbg !4592

if.end66:                                         ; preds = %while.body60
  %71 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4594
  %strm67 = getelementptr inbounds %struct.EState, %struct.EState* %71, i32 0, i32 0, !dbg !4596
  %72 = load %struct.bz_stream*, %struct.bz_stream** %strm67, align 8, !dbg !4596
  %avail_in68 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %72, i32 0, i32 1, !dbg !4597
  %73 = load i32, i32* %avail_in68, align 8, !dbg !4597
  %cmp69 = icmp eq i32 %73, 0, !dbg !4598
  br i1 %cmp69, label %if.then71, label %if.end72, !dbg !4599

if.then71:                                        ; preds = %if.end66
  br label %while.end154, !dbg !4600

if.end72:                                         ; preds = %if.end66
  %74 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4602
  %avail_in_expect = getelementptr inbounds %struct.EState, %struct.EState* %74, i32 0, i32 3, !dbg !4604
  %75 = load i32, i32* %avail_in_expect, align 8, !dbg !4604
  %cmp73 = icmp eq i32 %75, 0, !dbg !4605
  br i1 %cmp73, label %if.then75, label %if.end76, !dbg !4606

if.then75:                                        ; preds = %if.end72
  br label %while.end154, !dbg !4607

if.end76:                                         ; preds = %if.end72
  store i8 1, i8* %progress_in, align 1, !dbg !4609
  call void @llvm.dbg.declare(metadata i32* %zchh77, metadata !4610, metadata !392), !dbg !4612
  %76 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4612
  %strm78 = getelementptr inbounds %struct.EState, %struct.EState* %76, i32 0, i32 0, !dbg !4612
  %77 = load %struct.bz_stream*, %struct.bz_stream** %strm78, align 8, !dbg !4612
  %next_in79 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %77, i32 0, i32 0, !dbg !4612
  %78 = load i8*, i8** %next_in79, align 8, !dbg !4612
  %79 = load i8, i8* %78, align 1, !dbg !4612
  %conv80 = zext i8 %79 to i32, !dbg !4612
  store i32 %conv80, i32* %zchh77, align 4, !dbg !4612
  %80 = load i32, i32* %zchh77, align 4, !dbg !4613
  %81 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4613
  %state_in_ch81 = getelementptr inbounds %struct.EState, %struct.EState* %81, i32 0, i32 13, !dbg !4613
  %82 = load i32, i32* %state_in_ch81, align 4, !dbg !4613
  %cmp82 = icmp ne i32 %80, %82, !dbg !4613
  br i1 %cmp82, label %land.lhs.true84, label %if.else113, !dbg !4613

land.lhs.true84:                                  ; preds = %if.end76
  %83 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4615
  %state_in_len85 = getelementptr inbounds %struct.EState, %struct.EState* %83, i32 0, i32 14, !dbg !4615
  %84 = load i32, i32* %state_in_len85, align 8, !dbg !4615
  %cmp86 = icmp eq i32 %84, 1, !dbg !4615
  br i1 %cmp86, label %if.then88, label %if.else113, !dbg !4615

if.then88:                                        ; preds = %land.lhs.true84
  call void @llvm.dbg.declare(metadata i8* %ch89, metadata !4617, metadata !392), !dbg !4619
  %85 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4620
  %state_in_ch90 = getelementptr inbounds %struct.EState, %struct.EState* %85, i32 0, i32 13, !dbg !4620
  %86 = load i32, i32* %state_in_ch90, align 4, !dbg !4620
  %conv91 = trunc i32 %86 to i8, !dbg !4620
  store i8 %conv91, i8* %ch89, align 1, !dbg !4620
  %87 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4620
  %blockCRC92 = getelementptr inbounds %struct.EState, %struct.EState* %87, i32 0, i32 26, !dbg !4620
  %88 = load i32, i32* %blockCRC92, align 8, !dbg !4620
  %shl93 = shl i32 %88, 8, !dbg !4620
  %89 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4620
  %blockCRC94 = getelementptr inbounds %struct.EState, %struct.EState* %89, i32 0, i32 26, !dbg !4620
  %90 = load i32, i32* %blockCRC94, align 8, !dbg !4620
  %shr95 = lshr i32 %90, 24, !dbg !4620
  %91 = load i8, i8* %ch89, align 1, !dbg !4620
  %conv96 = zext i8 %91 to i32, !dbg !4620
  %xor97 = xor i32 %shr95, %conv96, !dbg !4620
  %idxprom98 = zext i32 %xor97 to i64, !dbg !4620
  %arrayidx99 = getelementptr inbounds [256 x i32], [256 x i32]* @BZ2_crc32Table, i64 0, i64 %idxprom98, !dbg !4620
  %92 = load i32, i32* %arrayidx99, align 4, !dbg !4620
  %xor100 = xor i32 %shl93, %92, !dbg !4620
  %93 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4620
  %blockCRC101 = getelementptr inbounds %struct.EState, %struct.EState* %93, i32 0, i32 26, !dbg !4620
  store i32 %xor100, i32* %blockCRC101, align 8, !dbg !4620
  %94 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4620
  %state_in_ch102 = getelementptr inbounds %struct.EState, %struct.EState* %94, i32 0, i32 13, !dbg !4620
  %95 = load i32, i32* %state_in_ch102, align 4, !dbg !4620
  %idxprom103 = zext i32 %95 to i64, !dbg !4620
  %96 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4620
  %inUse104 = getelementptr inbounds %struct.EState, %struct.EState* %96, i32 0, i32 22, !dbg !4620
  %arrayidx105 = getelementptr inbounds [256 x i8], [256 x i8]* %inUse104, i64 0, i64 %idxprom103, !dbg !4620
  store i8 1, i8* %arrayidx105, align 1, !dbg !4620
  %97 = load i8, i8* %ch89, align 1, !dbg !4620
  %98 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4620
  %nblock106 = getelementptr inbounds %struct.EState, %struct.EState* %98, i32 0, i32 17, !dbg !4620
  %99 = load i32, i32* %nblock106, align 4, !dbg !4620
  %idxprom107 = sext i32 %99 to i64, !dbg !4620
  %100 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4620
  %block108 = getelementptr inbounds %struct.EState, %struct.EState* %100, i32 0, i32 9, !dbg !4620
  %101 = load i8*, i8** %block108, align 8, !dbg !4620
  %arrayidx109 = getelementptr inbounds i8, i8* %101, i64 %idxprom107, !dbg !4620
  store i8 %97, i8* %arrayidx109, align 1, !dbg !4620
  %102 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4620
  %nblock110 = getelementptr inbounds %struct.EState, %struct.EState* %102, i32 0, i32 17, !dbg !4620
  %103 = load i32, i32* %nblock110, align 4, !dbg !4620
  %inc111 = add nsw i32 %103, 1, !dbg !4620
  store i32 %inc111, i32* %nblock110, align 4, !dbg !4620
  %104 = load i32, i32* %zchh77, align 4, !dbg !4620
  %105 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4620
  %state_in_ch112 = getelementptr inbounds %struct.EState, %struct.EState* %105, i32 0, i32 13, !dbg !4620
  store i32 %104, i32* %state_in_ch112, align 4, !dbg !4620
  br label %if.end133, !dbg !4620

if.else113:                                       ; preds = %land.lhs.true84, %if.end76
  %106 = load i32, i32* %zchh77, align 4, !dbg !4622
  %107 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4622
  %state_in_ch114 = getelementptr inbounds %struct.EState, %struct.EState* %107, i32 0, i32 13, !dbg !4622
  %108 = load i32, i32* %state_in_ch114, align 4, !dbg !4622
  %cmp115 = icmp ne i32 %106, %108, !dbg !4622
  br i1 %cmp115, label %if.then121, label %lor.lhs.false117, !dbg !4622

lor.lhs.false117:                                 ; preds = %if.else113
  %109 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4625
  %state_in_len118 = getelementptr inbounds %struct.EState, %struct.EState* %109, i32 0, i32 14, !dbg !4625
  %110 = load i32, i32* %state_in_len118, align 8, !dbg !4625
  %cmp119 = icmp eq i32 %110, 255, !dbg !4625
  br i1 %cmp119, label %if.then121, label %if.else129, !dbg !4625

if.then121:                                       ; preds = %lor.lhs.false117, %if.else113
  %111 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4627
  %state_in_ch122 = getelementptr inbounds %struct.EState, %struct.EState* %111, i32 0, i32 13, !dbg !4627
  %112 = load i32, i32* %state_in_ch122, align 4, !dbg !4627
  %cmp123 = icmp ult i32 %112, 256, !dbg !4627
  br i1 %cmp123, label %if.then125, label %if.end126, !dbg !4627

if.then125:                                       ; preds = %if.then121
  %113 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4631
  call void @add_pair_to_block(%struct.EState* %113), !dbg !4631
  br label %if.end126, !dbg !4631

if.end126:                                        ; preds = %if.then125, %if.then121
  %114 = load i32, i32* %zchh77, align 4, !dbg !4633
  %115 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4633
  %state_in_ch127 = getelementptr inbounds %struct.EState, %struct.EState* %115, i32 0, i32 13, !dbg !4633
  store i32 %114, i32* %state_in_ch127, align 4, !dbg !4633
  %116 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4633
  %state_in_len128 = getelementptr inbounds %struct.EState, %struct.EState* %116, i32 0, i32 14, !dbg !4633
  store i32 1, i32* %state_in_len128, align 8, !dbg !4633
  br label %if.end132, !dbg !4633

if.else129:                                       ; preds = %lor.lhs.false117
  %117 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4635
  %state_in_len130 = getelementptr inbounds %struct.EState, %struct.EState* %117, i32 0, i32 14, !dbg !4635
  %118 = load i32, i32* %state_in_len130, align 8, !dbg !4635
  %inc131 = add nsw i32 %118, 1, !dbg !4635
  store i32 %inc131, i32* %state_in_len130, align 8, !dbg !4635
  br label %if.end132

if.end132:                                        ; preds = %if.else129, %if.end126
  br label %if.end133

if.end133:                                        ; preds = %if.end132, %if.then88
  %119 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4638
  %strm134 = getelementptr inbounds %struct.EState, %struct.EState* %119, i32 0, i32 0, !dbg !4639
  %120 = load %struct.bz_stream*, %struct.bz_stream** %strm134, align 8, !dbg !4639
  %next_in135 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %120, i32 0, i32 0, !dbg !4640
  %121 = load i8*, i8** %next_in135, align 8, !dbg !4641
  %incdec.ptr136 = getelementptr inbounds i8, i8* %121, i32 1, !dbg !4641
  store i8* %incdec.ptr136, i8** %next_in135, align 8, !dbg !4641
  %122 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4642
  %strm137 = getelementptr inbounds %struct.EState, %struct.EState* %122, i32 0, i32 0, !dbg !4643
  %123 = load %struct.bz_stream*, %struct.bz_stream** %strm137, align 8, !dbg !4643
  %avail_in138 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %123, i32 0, i32 1, !dbg !4644
  %124 = load i32, i32* %avail_in138, align 8, !dbg !4645
  %dec139 = add i32 %124, -1, !dbg !4645
  store i32 %dec139, i32* %avail_in138, align 8, !dbg !4645
  %125 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4646
  %strm140 = getelementptr inbounds %struct.EState, %struct.EState* %125, i32 0, i32 0, !dbg !4647
  %126 = load %struct.bz_stream*, %struct.bz_stream** %strm140, align 8, !dbg !4647
  %total_in_lo32141 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %126, i32 0, i32 2, !dbg !4648
  %127 = load i32, i32* %total_in_lo32141, align 4, !dbg !4649
  %inc142 = add i32 %127, 1, !dbg !4649
  store i32 %inc142, i32* %total_in_lo32141, align 4, !dbg !4649
  %128 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4650
  %strm143 = getelementptr inbounds %struct.EState, %struct.EState* %128, i32 0, i32 0, !dbg !4652
  %129 = load %struct.bz_stream*, %struct.bz_stream** %strm143, align 8, !dbg !4652
  %total_in_lo32144 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %129, i32 0, i32 2, !dbg !4653
  %130 = load i32, i32* %total_in_lo32144, align 4, !dbg !4653
  %cmp145 = icmp eq i32 %130, 0, !dbg !4654
  br i1 %cmp145, label %if.then147, label %if.end151, !dbg !4655

if.then147:                                       ; preds = %if.end133
  %131 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4656
  %strm148 = getelementptr inbounds %struct.EState, %struct.EState* %131, i32 0, i32 0, !dbg !4658
  %132 = load %struct.bz_stream*, %struct.bz_stream** %strm148, align 8, !dbg !4658
  %total_in_hi32149 = getelementptr inbounds %struct.bz_stream, %struct.bz_stream* %132, i32 0, i32 3, !dbg !4659
  %133 = load i32, i32* %total_in_hi32149, align 8, !dbg !4660
  %inc150 = add i32 %133, 1, !dbg !4660
  store i32 %inc150, i32* %total_in_hi32149, align 8, !dbg !4660
  br label %if.end151, !dbg !4656

if.end151:                                        ; preds = %if.then147, %if.end133
  %134 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4661
  %avail_in_expect152 = getelementptr inbounds %struct.EState, %struct.EState* %134, i32 0, i32 3, !dbg !4662
  %135 = load i32, i32* %avail_in_expect152, align 8, !dbg !4663
  %dec153 = add i32 %135, -1, !dbg !4663
  store i32 %dec153, i32* %avail_in_expect152, align 8, !dbg !4663
  br label %while.body60, !dbg !4664

while.end154:                                     ; preds = %if.then75, %if.then71, %if.then65
  br label %if.end155

if.end155:                                        ; preds = %while.end154, %while.end
  %136 = load i8, i8* %progress_in, align 1, !dbg !4666
  ret i8 %136, !dbg !4667
}

; Function Attrs: nounwind uwtable
define internal void @flush_RL(%struct.EState* %s) #0 !dbg !292 {
entry:
  %s.addr = alloca %struct.EState*, align 8
  store %struct.EState* %s, %struct.EState** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.EState** %s.addr, metadata !4668, metadata !392), !dbg !4669
  %0 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4670
  %state_in_ch = getelementptr inbounds %struct.EState, %struct.EState* %0, i32 0, i32 13, !dbg !4672
  %1 = load i32, i32* %state_in_ch, align 4, !dbg !4672
  %cmp = icmp ult i32 %1, 256, !dbg !4673
  br i1 %cmp, label %if.then, label %if.end, !dbg !4674

if.then:                                          ; preds = %entry
  %2 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4675
  call void @add_pair_to_block(%struct.EState* %2), !dbg !4677
  br label %if.end, !dbg !4677

if.end:                                           ; preds = %if.then, %entry
  %3 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4678
  call void @init_RL(%struct.EState* %3), !dbg !4679
  ret void, !dbg !4680
}

declare void @BZ2_compressBlock(%struct.EState*, i8 zeroext) #2

; Function Attrs: nounwind uwtable
define internal void @add_pair_to_block(%struct.EState* %s) #0 !dbg !291 {
entry:
  %s.addr = alloca %struct.EState*, align 8
  %i = alloca i32, align 4
  %ch = alloca i8, align 1
  store %struct.EState* %s, %struct.EState** %s.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.EState** %s.addr, metadata !4681, metadata !392), !dbg !4682
  call void @llvm.dbg.declare(metadata i32* %i, metadata !4683, metadata !392), !dbg !4684
  call void @llvm.dbg.declare(metadata i8* %ch, metadata !4685, metadata !392), !dbg !4686
  %0 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4687
  %state_in_ch = getelementptr inbounds %struct.EState, %struct.EState* %0, i32 0, i32 13, !dbg !4688
  %1 = load i32, i32* %state_in_ch, align 4, !dbg !4688
  %conv = trunc i32 %1 to i8, !dbg !4689
  store i8 %conv, i8* %ch, align 1, !dbg !4686
  store i32 0, i32* %i, align 4, !dbg !4690
  br label %for.cond, !dbg !4692

for.cond:                                         ; preds = %for.inc, %entry
  %2 = load i32, i32* %i, align 4, !dbg !4693
  %3 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4696
  %state_in_len = getelementptr inbounds %struct.EState, %struct.EState* %3, i32 0, i32 14, !dbg !4697
  %4 = load i32, i32* %state_in_len, align 8, !dbg !4697
  %cmp = icmp slt i32 %2, %4, !dbg !4698
  br i1 %cmp, label %for.body, label %for.end, !dbg !4699

for.body:                                         ; preds = %for.cond
  %5 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4700
  %blockCRC = getelementptr inbounds %struct.EState, %struct.EState* %5, i32 0, i32 26, !dbg !4700
  %6 = load i32, i32* %blockCRC, align 8, !dbg !4700
  %shl = shl i32 %6, 8, !dbg !4700
  %7 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4700
  %blockCRC2 = getelementptr inbounds %struct.EState, %struct.EState* %7, i32 0, i32 26, !dbg !4700
  %8 = load i32, i32* %blockCRC2, align 8, !dbg !4700
  %shr = lshr i32 %8, 24, !dbg !4700
  %9 = load i8, i8* %ch, align 1, !dbg !4700
  %conv3 = zext i8 %9 to i32, !dbg !4700
  %xor = xor i32 %shr, %conv3, !dbg !4700
  %idxprom = zext i32 %xor to i64, !dbg !4700
  %arrayidx = getelementptr inbounds [256 x i32], [256 x i32]* @BZ2_crc32Table, i64 0, i64 %idxprom, !dbg !4700
  %10 = load i32, i32* %arrayidx, align 4, !dbg !4700
  %xor4 = xor i32 %shl, %10, !dbg !4700
  %11 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4700
  %blockCRC5 = getelementptr inbounds %struct.EState, %struct.EState* %11, i32 0, i32 26, !dbg !4700
  store i32 %xor4, i32* %blockCRC5, align 8, !dbg !4700
  br label %for.inc, !dbg !4703

for.inc:                                          ; preds = %for.body
  %12 = load i32, i32* %i, align 4, !dbg !4704
  %inc = add nsw i32 %12, 1, !dbg !4704
  store i32 %inc, i32* %i, align 4, !dbg !4704
  br label %for.cond, !dbg !4706

for.end:                                          ; preds = %for.cond
  %13 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4707
  %state_in_ch6 = getelementptr inbounds %struct.EState, %struct.EState* %13, i32 0, i32 13, !dbg !4708
  %14 = load i32, i32* %state_in_ch6, align 4, !dbg !4708
  %idxprom7 = zext i32 %14 to i64, !dbg !4709
  %15 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4709
  %inUse = getelementptr inbounds %struct.EState, %struct.EState* %15, i32 0, i32 22, !dbg !4710
  %arrayidx8 = getelementptr inbounds [256 x i8], [256 x i8]* %inUse, i64 0, i64 %idxprom7, !dbg !4709
  store i8 1, i8* %arrayidx8, align 1, !dbg !4711
  %16 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4712
  %state_in_len9 = getelementptr inbounds %struct.EState, %struct.EState* %16, i32 0, i32 14, !dbg !4713
  %17 = load i32, i32* %state_in_len9, align 8, !dbg !4713
  switch i32 %17, label %sw.default [
    i32 1, label %sw.bb
    i32 2, label %sw.bb14
    i32 3, label %sw.bb27
  ], !dbg !4714

sw.bb:                                            ; preds = %for.end
  %18 = load i8, i8* %ch, align 1, !dbg !4715
  %19 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4717
  %nblock = getelementptr inbounds %struct.EState, %struct.EState* %19, i32 0, i32 17, !dbg !4718
  %20 = load i32, i32* %nblock, align 4, !dbg !4718
  %idxprom10 = sext i32 %20 to i64, !dbg !4719
  %21 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4719
  %block = getelementptr inbounds %struct.EState, %struct.EState* %21, i32 0, i32 9, !dbg !4720
  %22 = load i8*, i8** %block, align 8, !dbg !4720
  %arrayidx11 = getelementptr inbounds i8, i8* %22, i64 %idxprom10, !dbg !4719
  store i8 %18, i8* %arrayidx11, align 1, !dbg !4721
  %23 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4722
  %nblock12 = getelementptr inbounds %struct.EState, %struct.EState* %23, i32 0, i32 17, !dbg !4723
  %24 = load i32, i32* %nblock12, align 4, !dbg !4724
  %inc13 = add nsw i32 %24, 1, !dbg !4724
  store i32 %inc13, i32* %nblock12, align 4, !dbg !4724
  br label %sw.epilog, !dbg !4725

sw.bb14:                                          ; preds = %for.end
  %25 = load i8, i8* %ch, align 1, !dbg !4726
  %26 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4727
  %nblock15 = getelementptr inbounds %struct.EState, %struct.EState* %26, i32 0, i32 17, !dbg !4728
  %27 = load i32, i32* %nblock15, align 4, !dbg !4728
  %idxprom16 = sext i32 %27 to i64, !dbg !4729
  %28 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4729
  %block17 = getelementptr inbounds %struct.EState, %struct.EState* %28, i32 0, i32 9, !dbg !4730
  %29 = load i8*, i8** %block17, align 8, !dbg !4730
  %arrayidx18 = getelementptr inbounds i8, i8* %29, i64 %idxprom16, !dbg !4729
  store i8 %25, i8* %arrayidx18, align 1, !dbg !4731
  %30 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4732
  %nblock19 = getelementptr inbounds %struct.EState, %struct.EState* %30, i32 0, i32 17, !dbg !4733
  %31 = load i32, i32* %nblock19, align 4, !dbg !4734
  %inc20 = add nsw i32 %31, 1, !dbg !4734
  store i32 %inc20, i32* %nblock19, align 4, !dbg !4734
  %32 = load i8, i8* %ch, align 1, !dbg !4735
  %33 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4736
  %nblock21 = getelementptr inbounds %struct.EState, %struct.EState* %33, i32 0, i32 17, !dbg !4737
  %34 = load i32, i32* %nblock21, align 4, !dbg !4737
  %idxprom22 = sext i32 %34 to i64, !dbg !4738
  %35 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4738
  %block23 = getelementptr inbounds %struct.EState, %struct.EState* %35, i32 0, i32 9, !dbg !4739
  %36 = load i8*, i8** %block23, align 8, !dbg !4739
  %arrayidx24 = getelementptr inbounds i8, i8* %36, i64 %idxprom22, !dbg !4738
  store i8 %32, i8* %arrayidx24, align 1, !dbg !4740
  %37 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4741
  %nblock25 = getelementptr inbounds %struct.EState, %struct.EState* %37, i32 0, i32 17, !dbg !4742
  %38 = load i32, i32* %nblock25, align 4, !dbg !4743
  %inc26 = add nsw i32 %38, 1, !dbg !4743
  store i32 %inc26, i32* %nblock25, align 4, !dbg !4743
  br label %sw.epilog, !dbg !4744

sw.bb27:                                          ; preds = %for.end
  %39 = load i8, i8* %ch, align 1, !dbg !4745
  %40 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4746
  %nblock28 = getelementptr inbounds %struct.EState, %struct.EState* %40, i32 0, i32 17, !dbg !4747
  %41 = load i32, i32* %nblock28, align 4, !dbg !4747
  %idxprom29 = sext i32 %41 to i64, !dbg !4748
  %42 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4748
  %block30 = getelementptr inbounds %struct.EState, %struct.EState* %42, i32 0, i32 9, !dbg !4749
  %43 = load i8*, i8** %block30, align 8, !dbg !4749
  %arrayidx31 = getelementptr inbounds i8, i8* %43, i64 %idxprom29, !dbg !4748
  store i8 %39, i8* %arrayidx31, align 1, !dbg !4750
  %44 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4751
  %nblock32 = getelementptr inbounds %struct.EState, %struct.EState* %44, i32 0, i32 17, !dbg !4752
  %45 = load i32, i32* %nblock32, align 4, !dbg !4753
  %inc33 = add nsw i32 %45, 1, !dbg !4753
  store i32 %inc33, i32* %nblock32, align 4, !dbg !4753
  %46 = load i8, i8* %ch, align 1, !dbg !4754
  %47 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4755
  %nblock34 = getelementptr inbounds %struct.EState, %struct.EState* %47, i32 0, i32 17, !dbg !4756
  %48 = load i32, i32* %nblock34, align 4, !dbg !4756
  %idxprom35 = sext i32 %48 to i64, !dbg !4757
  %49 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4757
  %block36 = getelementptr inbounds %struct.EState, %struct.EState* %49, i32 0, i32 9, !dbg !4758
  %50 = load i8*, i8** %block36, align 8, !dbg !4758
  %arrayidx37 = getelementptr inbounds i8, i8* %50, i64 %idxprom35, !dbg !4757
  store i8 %46, i8* %arrayidx37, align 1, !dbg !4759
  %51 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4760
  %nblock38 = getelementptr inbounds %struct.EState, %struct.EState* %51, i32 0, i32 17, !dbg !4761
  %52 = load i32, i32* %nblock38, align 4, !dbg !4762
  %inc39 = add nsw i32 %52, 1, !dbg !4762
  store i32 %inc39, i32* %nblock38, align 4, !dbg !4762
  %53 = load i8, i8* %ch, align 1, !dbg !4763
  %54 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4764
  %nblock40 = getelementptr inbounds %struct.EState, %struct.EState* %54, i32 0, i32 17, !dbg !4765
  %55 = load i32, i32* %nblock40, align 4, !dbg !4765
  %idxprom41 = sext i32 %55 to i64, !dbg !4766
  %56 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4766
  %block42 = getelementptr inbounds %struct.EState, %struct.EState* %56, i32 0, i32 9, !dbg !4767
  %57 = load i8*, i8** %block42, align 8, !dbg !4767
  %arrayidx43 = getelementptr inbounds i8, i8* %57, i64 %idxprom41, !dbg !4766
  store i8 %53, i8* %arrayidx43, align 1, !dbg !4768
  %58 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4769
  %nblock44 = getelementptr inbounds %struct.EState, %struct.EState* %58, i32 0, i32 17, !dbg !4770
  %59 = load i32, i32* %nblock44, align 4, !dbg !4771
  %inc45 = add nsw i32 %59, 1, !dbg !4771
  store i32 %inc45, i32* %nblock44, align 4, !dbg !4771
  br label %sw.epilog, !dbg !4772

sw.default:                                       ; preds = %for.end
  %60 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4773
  %state_in_len46 = getelementptr inbounds %struct.EState, %struct.EState* %60, i32 0, i32 14, !dbg !4774
  %61 = load i32, i32* %state_in_len46, align 8, !dbg !4774
  %sub = sub nsw i32 %61, 4, !dbg !4775
  %idxprom47 = sext i32 %sub to i64, !dbg !4776
  %62 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4776
  %inUse48 = getelementptr inbounds %struct.EState, %struct.EState* %62, i32 0, i32 22, !dbg !4777
  %arrayidx49 = getelementptr inbounds [256 x i8], [256 x i8]* %inUse48, i64 0, i64 %idxprom47, !dbg !4776
  store i8 1, i8* %arrayidx49, align 1, !dbg !4778
  %63 = load i8, i8* %ch, align 1, !dbg !4779
  %64 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4780
  %nblock50 = getelementptr inbounds %struct.EState, %struct.EState* %64, i32 0, i32 17, !dbg !4781
  %65 = load i32, i32* %nblock50, align 4, !dbg !4781
  %idxprom51 = sext i32 %65 to i64, !dbg !4782
  %66 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4782
  %block52 = getelementptr inbounds %struct.EState, %struct.EState* %66, i32 0, i32 9, !dbg !4783
  %67 = load i8*, i8** %block52, align 8, !dbg !4783
  %arrayidx53 = getelementptr inbounds i8, i8* %67, i64 %idxprom51, !dbg !4782
  store i8 %63, i8* %arrayidx53, align 1, !dbg !4784
  %68 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4785
  %nblock54 = getelementptr inbounds %struct.EState, %struct.EState* %68, i32 0, i32 17, !dbg !4786
  %69 = load i32, i32* %nblock54, align 4, !dbg !4787
  %inc55 = add nsw i32 %69, 1, !dbg !4787
  store i32 %inc55, i32* %nblock54, align 4, !dbg !4787
  %70 = load i8, i8* %ch, align 1, !dbg !4788
  %71 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4789
  %nblock56 = getelementptr inbounds %struct.EState, %struct.EState* %71, i32 0, i32 17, !dbg !4790
  %72 = load i32, i32* %nblock56, align 4, !dbg !4790
  %idxprom57 = sext i32 %72 to i64, !dbg !4791
  %73 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4791
  %block58 = getelementptr inbounds %struct.EState, %struct.EState* %73, i32 0, i32 9, !dbg !4792
  %74 = load i8*, i8** %block58, align 8, !dbg !4792
  %arrayidx59 = getelementptr inbounds i8, i8* %74, i64 %idxprom57, !dbg !4791
  store i8 %70, i8* %arrayidx59, align 1, !dbg !4793
  %75 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4794
  %nblock60 = getelementptr inbounds %struct.EState, %struct.EState* %75, i32 0, i32 17, !dbg !4795
  %76 = load i32, i32* %nblock60, align 4, !dbg !4796
  %inc61 = add nsw i32 %76, 1, !dbg !4796
  store i32 %inc61, i32* %nblock60, align 4, !dbg !4796
  %77 = load i8, i8* %ch, align 1, !dbg !4797
  %78 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4798
  %nblock62 = getelementptr inbounds %struct.EState, %struct.EState* %78, i32 0, i32 17, !dbg !4799
  %79 = load i32, i32* %nblock62, align 4, !dbg !4799
  %idxprom63 = sext i32 %79 to i64, !dbg !4800
  %80 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4800
  %block64 = getelementptr inbounds %struct.EState, %struct.EState* %80, i32 0, i32 9, !dbg !4801
  %81 = load i8*, i8** %block64, align 8, !dbg !4801
  %arrayidx65 = getelementptr inbounds i8, i8* %81, i64 %idxprom63, !dbg !4800
  store i8 %77, i8* %arrayidx65, align 1, !dbg !4802
  %82 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4803
  %nblock66 = getelementptr inbounds %struct.EState, %struct.EState* %82, i32 0, i32 17, !dbg !4804
  %83 = load i32, i32* %nblock66, align 4, !dbg !4805
  %inc67 = add nsw i32 %83, 1, !dbg !4805
  store i32 %inc67, i32* %nblock66, align 4, !dbg !4805
  %84 = load i8, i8* %ch, align 1, !dbg !4806
  %85 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4807
  %nblock68 = getelementptr inbounds %struct.EState, %struct.EState* %85, i32 0, i32 17, !dbg !4808
  %86 = load i32, i32* %nblock68, align 4, !dbg !4808
  %idxprom69 = sext i32 %86 to i64, !dbg !4809
  %87 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4809
  %block70 = getelementptr inbounds %struct.EState, %struct.EState* %87, i32 0, i32 9, !dbg !4810
  %88 = load i8*, i8** %block70, align 8, !dbg !4810
  %arrayidx71 = getelementptr inbounds i8, i8* %88, i64 %idxprom69, !dbg !4809
  store i8 %84, i8* %arrayidx71, align 1, !dbg !4811
  %89 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4812
  %nblock72 = getelementptr inbounds %struct.EState, %struct.EState* %89, i32 0, i32 17, !dbg !4813
  %90 = load i32, i32* %nblock72, align 4, !dbg !4814
  %inc73 = add nsw i32 %90, 1, !dbg !4814
  store i32 %inc73, i32* %nblock72, align 4, !dbg !4814
  %91 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4815
  %state_in_len74 = getelementptr inbounds %struct.EState, %struct.EState* %91, i32 0, i32 14, !dbg !4816
  %92 = load i32, i32* %state_in_len74, align 8, !dbg !4816
  %sub75 = sub nsw i32 %92, 4, !dbg !4817
  %conv76 = trunc i32 %sub75 to i8, !dbg !4818
  %93 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4819
  %nblock77 = getelementptr inbounds %struct.EState, %struct.EState* %93, i32 0, i32 17, !dbg !4820
  %94 = load i32, i32* %nblock77, align 4, !dbg !4820
  %idxprom78 = sext i32 %94 to i64, !dbg !4821
  %95 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4821
  %block79 = getelementptr inbounds %struct.EState, %struct.EState* %95, i32 0, i32 9, !dbg !4822
  %96 = load i8*, i8** %block79, align 8, !dbg !4822
  %arrayidx80 = getelementptr inbounds i8, i8* %96, i64 %idxprom78, !dbg !4821
  store i8 %conv76, i8* %arrayidx80, align 1, !dbg !4823
  %97 = load %struct.EState*, %struct.EState** %s.addr, align 8, !dbg !4824
  %nblock81 = getelementptr inbounds %struct.EState, %struct.EState* %97, i32 0, i32 17, !dbg !4825
  %98 = load i32, i32* %nblock81, align 4, !dbg !4826
  %inc82 = add nsw i32 %98, 1, !dbg !4826
  store i32 %inc82, i32* %nblock81, align 4, !dbg !4826
  br label %sw.epilog, !dbg !4827

sw.epilog:                                        ; preds = %sw.default, %sw.bb27, %sw.bb14, %sw.bb
  ret void, !dbg !4828
}

declare i32 @fgetc(%struct._IO_FILE*) #2

declare i32 @ungetc(i32, %struct._IO_FILE*) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #6

; Function Attrs: nounwind readnone
declare i16** @__ctype_b_loc() #7

; Function Attrs: nounwind
declare i8* @strcat(i8*, i8*) #5

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #8

declare %struct._IO_FILE* @fopen64(i8*, i8*) #2

; Function Attrs: nounwind
declare %struct._IO_FILE* @fdopen(i32, i8*) #5

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { inlinehint nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { argmemonly nounwind }
attributes #7 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #9 = { noreturn nounwind }
attributes #10 = { nounwind }
attributes #11 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!388, !389}
!llvm.ident = !{!390}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !18, subprograms: !130, globals: !385)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmbzip2/bzlib.c", directory: "/data/download/cmake/cmake-master/Utilities/cmbzip2")
!2 = !{!3}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 46, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/usr/include/ctype.h", directory: "/data/download/cmake/cmake-master/Utilities/cmbzip2")
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
!18 = !{!19, !20, !24, !27, !30, !31, !28, !21, !103, !43, !26}
!19 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!20 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !21, size: 64, align: 64)
!21 = !DIDerivedType(tag: DW_TAG_typedef, name: "UChar", file: !22, line: 60, baseType: !23)
!22 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmbzip2/bzlib_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmbzip2")
!23 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!24 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !25, size: 64, align: 64)
!25 = !DIDerivedType(tag: DW_TAG_typedef, name: "UInt16", file: !22, line: 64, baseType: !26)
!26 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DIDerivedType(tag: DW_TAG_typedef, name: "UInt32", file: !22, line: 62, baseType: !29)
!29 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!30 = !DIDerivedType(tag: DW_TAG_typedef, name: "Bool", file: !22, line: 59, baseType: !23)
!31 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !32, size: 64, align: 64)
!32 = !DIDerivedType(tag: DW_TAG_typedef, name: "bzFile", file: !1, line: 904, baseType: !33)
!33 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 895, size: 40832, align: 64, elements: !34)
!34 = !{!35, !97, !102, !104, !105, !128, !129}
!35 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !33, file: !1, line: 896, baseType: !36, size: 64, align: 64)
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DIDerivedType(tag: DW_TAG_typedef, name: "FILE", file: !38, line: 48, baseType: !39)
!38 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmbzip2")
!39 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_FILE", file: !40, line: 245, size: 1728, align: 64, elements: !41)
!40 = !DIFile(filename: "/usr/include/libio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmbzip2")
!41 = !{!42, !44, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !65, !66, !67, !68, !72, !73, !75, !79, !82, !84, !85, !86, !87, !88, !92, !93}
!42 = !DIDerivedType(tag: DW_TAG_member, name: "_flags", scope: !39, file: !40, line: 246, baseType: !43, size: 32, align: 32)
!43 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!44 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_ptr", scope: !39, file: !40, line: 251, baseType: !45, size: 64, align: 64, offset: 64)
!45 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !46, size: 64, align: 64)
!46 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!47 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_end", scope: !39, file: !40, line: 252, baseType: !45, size: 64, align: 64, offset: 128)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_read_base", scope: !39, file: !40, line: 253, baseType: !45, size: 64, align: 64, offset: 192)
!49 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_base", scope: !39, file: !40, line: 254, baseType: !45, size: 64, align: 64, offset: 256)
!50 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_ptr", scope: !39, file: !40, line: 255, baseType: !45, size: 64, align: 64, offset: 320)
!51 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_write_end", scope: !39, file: !40, line: 256, baseType: !45, size: 64, align: 64, offset: 384)
!52 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_base", scope: !39, file: !40, line: 257, baseType: !45, size: 64, align: 64, offset: 448)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_buf_end", scope: !39, file: !40, line: 258, baseType: !45, size: 64, align: 64, offset: 512)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_base", scope: !39, file: !40, line: 260, baseType: !45, size: 64, align: 64, offset: 576)
!55 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_backup_base", scope: !39, file: !40, line: 261, baseType: !45, size: 64, align: 64, offset: 640)
!56 = !DIDerivedType(tag: DW_TAG_member, name: "_IO_save_end", scope: !39, file: !40, line: 262, baseType: !45, size: 64, align: 64, offset: 704)
!57 = !DIDerivedType(tag: DW_TAG_member, name: "_markers", scope: !39, file: !40, line: 264, baseType: !58, size: 64, align: 64, offset: 768)
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !59, size: 64, align: 64)
!59 = !DICompositeType(tag: DW_TAG_structure_type, name: "_IO_marker", file: !40, line: 160, size: 192, align: 64, elements: !60)
!60 = !{!61, !62, !64}
!61 = !DIDerivedType(tag: DW_TAG_member, name: "_next", scope: !59, file: !40, line: 161, baseType: !58, size: 64, align: 64)
!62 = !DIDerivedType(tag: DW_TAG_member, name: "_sbuf", scope: !59, file: !40, line: 162, baseType: !63, size: 64, align: 64, offset: 64)
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !39, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "_pos", scope: !59, file: !40, line: 166, baseType: !43, size: 32, align: 32, offset: 128)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "_chain", scope: !39, file: !40, line: 266, baseType: !63, size: 64, align: 64, offset: 832)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "_fileno", scope: !39, file: !40, line: 268, baseType: !43, size: 32, align: 32, offset: 896)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "_flags2", scope: !39, file: !40, line: 272, baseType: !43, size: 32, align: 32, offset: 928)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "_old_offset", scope: !39, file: !40, line: 274, baseType: !69, size: 64, align: 64, offset: 960)
!69 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !70, line: 131, baseType: !71)
!70 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmbzip2")
!71 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "_cur_column", scope: !39, file: !40, line: 278, baseType: !26, size: 16, align: 16, offset: 1024)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "_vtable_offset", scope: !39, file: !40, line: 279, baseType: !74, size: 8, align: 8, offset: 1040)
!74 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!75 = !DIDerivedType(tag: DW_TAG_member, name: "_shortbuf", scope: !39, file: !40, line: 280, baseType: !76, size: 8, align: 8, offset: 1048)
!76 = !DICompositeType(tag: DW_TAG_array_type, baseType: !46, size: 8, align: 8, elements: !77)
!77 = !{!78}
!78 = !DISubrange(count: 1)
!79 = !DIDerivedType(tag: DW_TAG_member, name: "_lock", scope: !39, file: !40, line: 284, baseType: !80, size: 64, align: 64, offset: 1088)
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_typedef, name: "_IO_lock_t", file: !40, line: 154, baseType: null)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "_offset", scope: !39, file: !40, line: 293, baseType: !83, size: 64, align: 64, offset: 1152)
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off64_t", file: !70, line: 132, baseType: !71)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !39, file: !40, line: 302, baseType: !19, size: 64, align: 64, offset: 1216)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !39, file: !40, line: 303, baseType: !19, size: 64, align: 64, offset: 1280)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "__pad3", scope: !39, file: !40, line: 304, baseType: !19, size: 64, align: 64, offset: 1344)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "__pad4", scope: !39, file: !40, line: 305, baseType: !19, size: 64, align: 64, offset: 1408)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "__pad5", scope: !39, file: !40, line: 306, baseType: !89, size: 64, align: 64, offset: 1472)
!89 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !90, line: 62, baseType: !91)
!90 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmbzip2")
!91 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "_mode", scope: !39, file: !40, line: 308, baseType: !43, size: 32, align: 32, offset: 1536)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "_unused2", scope: !39, file: !40, line: 310, baseType: !94, size: 160, align: 8, offset: 1568)
!94 = !DICompositeType(tag: DW_TAG_array_type, baseType: !46, size: 160, align: 8, elements: !95)
!95 = !{!96}
!96 = !DISubrange(count: 20)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buf", scope: !33, file: !1, line: 897, baseType: !98, size: 40000, align: 8, offset: 64)
!98 = !DICompositeType(tag: DW_TAG_array_type, baseType: !99, size: 40000, align: 8, elements: !100)
!99 = !DIDerivedType(tag: DW_TAG_typedef, name: "Char", file: !22, line: 58, baseType: !46)
!100 = !{!101}
!101 = !DISubrange(count: 5000)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "bufN", scope: !33, file: !1, line: 898, baseType: !103, size: 32, align: 32, offset: 40064)
!103 = !DIDerivedType(tag: DW_TAG_typedef, name: "Int32", file: !22, line: 61, baseType: !43)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "writing", scope: !33, file: !1, line: 899, baseType: !30, size: 8, align: 8, offset: 40096)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "strm", scope: !33, file: !1, line: 900, baseType: !106, size: 640, align: 64, offset: 40128)
!106 = !DIDerivedType(tag: DW_TAG_typedef, name: "bz_stream", file: !107, line: 66, baseType: !108)
!107 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmbzip2/bzlib.h", directory: "/data/download/cmake/cmake-master/Utilities/cmbzip2")
!108 = !DICompositeType(tag: DW_TAG_structure_type, file: !107, line: 49, size: 640, align: 64, elements: !109)
!109 = !{!110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !123, !127}
!110 = !DIDerivedType(tag: DW_TAG_member, name: "next_in", scope: !108, file: !107, line: 50, baseType: !45, size: 64, align: 64)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in", scope: !108, file: !107, line: 51, baseType: !29, size: 32, align: 32, offset: 64)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "total_in_lo32", scope: !108, file: !107, line: 52, baseType: !29, size: 32, align: 32, offset: 96)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "total_in_hi32", scope: !108, file: !107, line: 53, baseType: !29, size: 32, align: 32, offset: 128)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "next_out", scope: !108, file: !107, line: 55, baseType: !45, size: 64, align: 64, offset: 192)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "avail_out", scope: !108, file: !107, line: 56, baseType: !29, size: 32, align: 32, offset: 256)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "total_out_lo32", scope: !108, file: !107, line: 57, baseType: !29, size: 32, align: 32, offset: 288)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "total_out_hi32", scope: !108, file: !107, line: 58, baseType: !29, size: 32, align: 32, offset: 320)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !108, file: !107, line: 60, baseType: !19, size: 64, align: 64, offset: 384)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "bzalloc", scope: !108, file: !107, line: 62, baseType: !120, size: 64, align: 64, offset: 448)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DISubroutineType(types: !122)
!122 = !{!19, !19, !43, !43}
!123 = !DIDerivedType(tag: DW_TAG_member, name: "bzfree", scope: !108, file: !107, line: 63, baseType: !124, size: 64, align: 64, offset: 512)
!124 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !125, size: 64, align: 64)
!125 = !DISubroutineType(types: !126)
!126 = !{null, !19, !19}
!127 = !DIDerivedType(tag: DW_TAG_member, name: "opaque", scope: !108, file: !107, line: 64, baseType: !19, size: 64, align: 64, offset: 576)
!128 = !DIDerivedType(tag: DW_TAG_member, name: "lastErr", scope: !33, file: !1, line: 901, baseType: !103, size: 32, align: 32, offset: 40768)
!129 = !DIDerivedType(tag: DW_TAG_member, name: "initialisedOk", scope: !33, file: !1, line: 902, baseType: !30, size: 8, align: 8, offset: 40800)
!130 = !{!131, !135, !139, !142, !145, !148, !152, !153, !154, !160, !163, !167, !170, !173, !176, !179, !183, !186, !189, !194, !197, !200, !203, !204, !207, !210, !213, !216, !219, !220, !283, !284, !287, !290, !291, !292, !293, !294, !378, !379, !382}
!131 = distinct !DISubprogram(name: "BZ2_bz__AssertH__fail", scope: !1, file: !1, line: 41, type: !132, isLocal: false, isDefinition: true, scopeLine: 42, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!132 = !DISubroutineType(types: !133)
!133 = !{null, !43}
!134 = !{}
!135 = distinct !DISubprogram(name: "BZ2_bzCompressInit", scope: !1, file: !1, line: 150, type: !136, isLocal: false, isDefinition: true, scopeLine: 155, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!136 = !DISubroutineType(types: !137)
!137 = !{!43, !138, !43, !43, !43}
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!139 = distinct !DISubprogram(name: "BZ2_bzCompress", scope: !1, file: !1, line: 409, type: !140, isLocal: false, isDefinition: true, scopeLine: 410, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!140 = !DISubroutineType(types: !141)
!141 = !{!43, !138, !43}
!142 = distinct !DISubprogram(name: "BZ2_bzCompressEnd", scope: !1, file: !1, line: 470, type: !143, isLocal: false, isDefinition: true, scopeLine: 471, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!143 = !DISubroutineType(types: !144)
!144 = !{!43, !138}
!145 = distinct !DISubprogram(name: "BZ2_bzDecompressInit", scope: !1, file: !1, line: 494, type: !146, isLocal: false, isDefinition: true, scopeLine: 498, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!146 = !DISubroutineType(types: !147)
!147 = !{!43, !138, !43, !43}
!148 = distinct !DISubprogram(name: "BZ2_indexIntoF", scope: !1, file: !1, line: 689, type: !149, isLocal: false, isDefinition: true, scopeLine: 690, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!149 = !DISubroutineType(types: !150)
!150 = !{!103, !103, !151}
!151 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!152 = distinct !DISubprogram(name: "BZ2_bzDecompress", scope: !1, file: !1, line: 810, type: !143, isLocal: false, isDefinition: true, scopeLine: 811, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!153 = distinct !DISubprogram(name: "BZ2_bzDecompressEnd", scope: !1, file: !1, line: 864, type: !143, isLocal: false, isDefinition: true, scopeLine: 865, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!154 = distinct !DISubprogram(name: "BZ2_bzWriteOpen", scope: !1, file: !1, line: 918, type: !155, isLocal: false, isDefinition: true, scopeLine: 924, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!155 = !DISubroutineType(types: !156)
!156 = !{!157, !159, !36, !43, !43, !43}
!157 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64, align: 64)
!158 = !DIDerivedType(tag: DW_TAG_typedef, name: "BZFILE", file: !107, line: 137, baseType: null)
!159 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!160 = distinct !DISubprogram(name: "BZ2_bzWrite", scope: !1, file: !1, line: 966, type: !161, isLocal: false, isDefinition: true, scopeLine: 971, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!161 = !DISubroutineType(types: !162)
!162 = !{null, !159, !157, !19, !43}
!163 = distinct !DISubprogram(name: "BZ2_bzWriteClose", scope: !1, file: !1, line: 1011, type: !164, isLocal: false, isDefinition: true, scopeLine: 1017, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!164 = !DISubroutineType(types: !165)
!165 = !{null, !159, !157, !43, !166, !166}
!166 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !29, size: 64, align: 64)
!167 = distinct !DISubprogram(name: "BZ2_bzWriteClose64", scope: !1, file: !1, line: 1023, type: !168, isLocal: false, isDefinition: true, scopeLine: 1031, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!168 = !DISubroutineType(types: !169)
!169 = !{null, !159, !157, !43, !166, !166, !166, !166}
!170 = distinct !DISubprogram(name: "BZ2_bzReadOpen", scope: !1, file: !1, line: 1089, type: !171, isLocal: false, isDefinition: true, scopeLine: 1096, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!171 = !DISubroutineType(types: !172)
!172 = !{!157, !159, !36, !43, !43, !19, !43}
!173 = distinct !DISubprogram(name: "BZ2_bzReadClose", scope: !1, file: !1, line: 1145, type: !174, isLocal: false, isDefinition: true, scopeLine: 1146, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!174 = !DISubroutineType(types: !175)
!175 = !{null, !159, !157}
!176 = distinct !DISubprogram(name: "BZ2_bzRead", scope: !1, file: !1, line: 1163, type: !177, isLocal: false, isDefinition: true, scopeLine: 1168, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!177 = !DISubroutineType(types: !178)
!178 = !{!43, !159, !157, !19, !43}
!179 = distinct !DISubprogram(name: "BZ2_bzReadGetUnused", scope: !1, file: !1, line: 1223, type: !180, isLocal: false, isDefinition: true, scopeLine: 1228, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!180 = !DISubroutineType(types: !181)
!181 = !{null, !159, !157, !182, !159}
!182 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!183 = distinct !DISubprogram(name: "BZ2_bzBuffToBuffCompress", scope: !1, file: !1, line: 1249, type: !184, isLocal: false, isDefinition: true, scopeLine: 1257, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!184 = !DISubroutineType(types: !185)
!185 = !{!43, !45, !166, !45, !29, !43, !43, !43}
!186 = distinct !DISubprogram(name: "BZ2_bzBuffToBuffDecompress", scope: !1, file: !1, line: 1301, type: !187, isLocal: false, isDefinition: true, scopeLine: 1308, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!187 = !DISubroutineType(types: !188)
!188 = !{!43, !45, !166, !45, !29, !43, !43}
!189 = distinct !DISubprogram(name: "BZ2_bzlibVersion", scope: !1, file: !1, line: 1368, type: !190, isLocal: false, isDefinition: true, scopeLine: 1369, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!190 = !DISubroutineType(types: !191)
!191 = !{!192}
!192 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !193, size: 64, align: 64)
!193 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !46)
!194 = distinct !DISubprogram(name: "BZ2_bzopen", scope: !1, file: !1, line: 1462, type: !195, isLocal: false, isDefinition: true, scopeLine: 1465, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!195 = !DISubroutineType(types: !196)
!196 = !{!157, !192, !192}
!197 = distinct !DISubprogram(name: "BZ2_bzdopen", scope: !1, file: !1, line: 1471, type: !198, isLocal: false, isDefinition: true, scopeLine: 1474, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!198 = !DISubroutineType(types: !199)
!199 = !{!157, !43, !192}
!200 = distinct !DISubprogram(name: "BZ2_bzread", scope: !1, file: !1, line: 1480, type: !201, isLocal: false, isDefinition: true, scopeLine: 1481, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!201 = !DISubroutineType(types: !202)
!202 = !{!43, !157, !19, !43}
!203 = distinct !DISubprogram(name: "BZ2_bzwrite", scope: !1, file: !1, line: 1494, type: !201, isLocal: false, isDefinition: true, scopeLine: 1495, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!204 = distinct !DISubprogram(name: "BZ2_bzflush", scope: !1, file: !1, line: 1508, type: !205, isLocal: false, isDefinition: true, scopeLine: 1509, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!205 = !DISubroutineType(types: !206)
!206 = !{!43, !157}
!207 = distinct !DISubprogram(name: "BZ2_bzclose", scope: !1, file: !1, line: 1517, type: !208, isLocal: false, isDefinition: true, scopeLine: 1518, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!208 = !DISubroutineType(types: !209)
!209 = !{null, !157}
!210 = distinct !DISubprogram(name: "BZ2_bzerror", scope: !1, file: !1, line: 1562, type: !211, isLocal: false, isDefinition: true, scopeLine: 1563, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!211 = !DISubroutineType(types: !212)
!212 = !{!192, !157, !159}
!213 = distinct !DISubprogram(name: "bz_config_ok", scope: !1, file: !1, line: 91, type: !214, isLocal: true, isDefinition: true, scopeLine: 92, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!214 = !DISubroutineType(types: !215)
!215 = !{!43}
!216 = distinct !DISubprogram(name: "default_bzalloc", scope: !1, file: !1, line: 102, type: !217, isLocal: true, isDefinition: true, scopeLine: 103, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!217 = !DISubroutineType(types: !218)
!218 = !{!19, !19, !103, !103}
!219 = distinct !DISubprogram(name: "default_bzfree", scope: !1, file: !1, line: 110, type: !125, isLocal: true, isDefinition: true, scopeLine: 111, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!220 = distinct !DISubprogram(name: "init_RL", scope: !1, file: !1, line: 133, type: !221, isLocal: true, isDefinition: true, scopeLine: 134, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!221 = !DISubroutineType(types: !222)
!222 = !{null, !223}
!223 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !224, size: 64, align: 64)
!224 = !DIDerivedType(tag: DW_TAG_typedef, name: "EState", file: !22, line: 283, baseType: !225)
!225 = !DICompositeType(tag: DW_TAG_structure_type, file: !22, line: 214, size: 446144, align: 64, elements: !226)
!226 = !{!227, !228, !229, !230, !231, !232, !233, !234, !235, !236, !237, !238, !239, !240, !241, !242, !243, !244, !245, !246, !247, !248, !249, !253, !255, !256, !257, !258, !259, !260, !261, !262, !263, !267, !271, !272, !276, !278, !279}
!227 = !DIDerivedType(tag: DW_TAG_member, name: "strm", scope: !225, file: !22, line: 216, baseType: !138, size: 64, align: 64)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !225, file: !22, line: 220, baseType: !103, size: 32, align: 32, offset: 64)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !225, file: !22, line: 221, baseType: !103, size: 32, align: 32, offset: 96)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "avail_in_expect", scope: !225, file: !22, line: 224, baseType: !28, size: 32, align: 32, offset: 128)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "arr1", scope: !225, file: !22, line: 227, baseType: !27, size: 64, align: 64, offset: 192)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "arr2", scope: !225, file: !22, line: 228, baseType: !27, size: 64, align: 64, offset: 256)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "ftab", scope: !225, file: !22, line: 229, baseType: !27, size: 64, align: 64, offset: 320)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "origPtr", scope: !225, file: !22, line: 230, baseType: !103, size: 32, align: 32, offset: 384)
!235 = !DIDerivedType(tag: DW_TAG_member, name: "ptr", scope: !225, file: !22, line: 233, baseType: !27, size: 64, align: 64, offset: 448)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "block", scope: !225, file: !22, line: 234, baseType: !20, size: 64, align: 64, offset: 512)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "mtfv", scope: !225, file: !22, line: 235, baseType: !24, size: 64, align: 64, offset: 576)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "zbits", scope: !225, file: !22, line: 236, baseType: !20, size: 64, align: 64, offset: 640)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "workFactor", scope: !225, file: !22, line: 239, baseType: !103, size: 32, align: 32, offset: 704)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "state_in_ch", scope: !225, file: !22, line: 242, baseType: !28, size: 32, align: 32, offset: 736)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "state_in_len", scope: !225, file: !22, line: 243, baseType: !103, size: 32, align: 32, offset: 768)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "rNToGo", scope: !225, file: !22, line: 244, baseType: !103, size: 32, align: 32, offset: 800)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "rTPos", scope: !225, file: !22, line: 244, baseType: !103, size: 32, align: 32, offset: 832)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "nblock", scope: !225, file: !22, line: 247, baseType: !103, size: 32, align: 32, offset: 864)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "nblockMAX", scope: !225, file: !22, line: 248, baseType: !103, size: 32, align: 32, offset: 896)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "numZ", scope: !225, file: !22, line: 249, baseType: !103, size: 32, align: 32, offset: 928)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "state_out_pos", scope: !225, file: !22, line: 250, baseType: !103, size: 32, align: 32, offset: 960)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "nInUse", scope: !225, file: !22, line: 253, baseType: !103, size: 32, align: 32, offset: 992)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "inUse", scope: !225, file: !22, line: 254, baseType: !250, size: 2048, align: 8, offset: 1024)
!250 = !DICompositeType(tag: DW_TAG_array_type, baseType: !30, size: 2048, align: 8, elements: !251)
!251 = !{!252}
!252 = !DISubrange(count: 256)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "unseqToSeq", scope: !225, file: !22, line: 255, baseType: !254, size: 2048, align: 8, offset: 3072)
!254 = !DICompositeType(tag: DW_TAG_array_type, baseType: !21, size: 2048, align: 8, elements: !251)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "bsBuff", scope: !225, file: !22, line: 258, baseType: !28, size: 32, align: 32, offset: 5120)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "bsLive", scope: !225, file: !22, line: 259, baseType: !103, size: 32, align: 32, offset: 5152)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "blockCRC", scope: !225, file: !22, line: 262, baseType: !28, size: 32, align: 32, offset: 5184)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "combinedCRC", scope: !225, file: !22, line: 263, baseType: !28, size: 32, align: 32, offset: 5216)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "verbosity", scope: !225, file: !22, line: 266, baseType: !103, size: 32, align: 32, offset: 5248)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "blockNo", scope: !225, file: !22, line: 267, baseType: !103, size: 32, align: 32, offset: 5280)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "blockSize100k", scope: !225, file: !22, line: 268, baseType: !103, size: 32, align: 32, offset: 5312)
!262 = !DIDerivedType(tag: DW_TAG_member, name: "nMTF", scope: !225, file: !22, line: 271, baseType: !103, size: 32, align: 32, offset: 5344)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "mtfFreq", scope: !225, file: !22, line: 272, baseType: !264, size: 8256, align: 32, offset: 5376)
!264 = !DICompositeType(tag: DW_TAG_array_type, baseType: !103, size: 8256, align: 32, elements: !265)
!265 = !{!266}
!266 = !DISubrange(count: 258)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "selector", scope: !225, file: !22, line: 273, baseType: !268, size: 144016, align: 8, offset: 13632)
!268 = !DICompositeType(tag: DW_TAG_array_type, baseType: !21, size: 144016, align: 8, elements: !269)
!269 = !{!270}
!270 = !DISubrange(count: 18002)
!271 = !DIDerivedType(tag: DW_TAG_member, name: "selectorMtf", scope: !225, file: !22, line: 274, baseType: !268, size: 144016, align: 8, offset: 157648)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !225, file: !22, line: 276, baseType: !273, size: 12384, align: 8, offset: 301664)
!273 = !DICompositeType(tag: DW_TAG_array_type, baseType: !21, size: 12384, align: 8, elements: !274)
!274 = !{!275, !266}
!275 = !DISubrange(count: 6)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !225, file: !22, line: 277, baseType: !277, size: 49536, align: 32, offset: 314048)
!277 = !DICompositeType(tag: DW_TAG_array_type, baseType: !103, size: 49536, align: 32, elements: !274)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "rfreq", scope: !225, file: !22, line: 278, baseType: !277, size: 49536, align: 32, offset: 363584)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "len_pack", scope: !225, file: !22, line: 280, baseType: !280, size: 33024, align: 32, offset: 413120)
!280 = !DICompositeType(tag: DW_TAG_array_type, baseType: !28, size: 33024, align: 32, elements: !281)
!281 = !{!266, !282}
!282 = !DISubrange(count: 4)
!283 = distinct !DISubprogram(name: "prepare_new_block", scope: !1, file: !1, line: 119, type: !221, isLocal: true, isDefinition: true, scopeLine: 120, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!284 = distinct !DISubprogram(name: "handle_compress", scope: !1, file: !1, line: 363, type: !285, isLocal: true, isDefinition: true, scopeLine: 364, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!285 = !DISubroutineType(types: !286)
!286 = !{!30, !138}
!287 = distinct !DISubprogram(name: "copy_output_until_stop", scope: !1, file: !1, line: 336, type: !288, isLocal: true, isDefinition: true, scopeLine: 337, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!288 = !DISubroutineType(types: !289)
!289 = !{!30, !223}
!290 = distinct !DISubprogram(name: "copy_input_until_stop", scope: !1, file: !1, line: 291, type: !288, isLocal: true, isDefinition: true, scopeLine: 292, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!291 = distinct !DISubprogram(name: "add_pair_to_block", scope: !1, file: !1, line: 218, type: !221, isLocal: true, isDefinition: true, scopeLine: 219, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!292 = distinct !DISubprogram(name: "flush_RL", scope: !1, file: !1, line: 254, type: !221, isLocal: true, isDefinition: true, scopeLine: 255, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!293 = distinct !DISubprogram(name: "isempty_RL", scope: !1, file: !1, line: 141, type: !288, isLocal: true, isDefinition: true, scopeLine: 142, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!294 = distinct !DISubprogram(name: "unRLE_obuf_to_output_SMALL", scope: !1, file: !1, line: 708, type: !295, isLocal: true, isDefinition: true, scopeLine: 709, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!295 = !DISubroutineType(types: !296)
!296 = !{!30, !297}
!297 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !298, size: 64, align: 64)
!298 = !DIDerivedType(tag: DW_TAG_typedef, name: "DState", file: !22, line: 455, baseType: !299)
!299 = !DICompositeType(tag: DW_TAG_structure_type, file: !22, line: 365, size: 513152, align: 64, elements: !300)
!300 = !{!301, !302, !303, !304, !305, !306, !307, !308, !309, !310, !311, !312, !313, !314, !315, !316, !317, !319, !320, !324, !325, !326, !327, !328, !329, !330, !331, !332, !333, !334, !338, !339, !343, !345, !346, !347, !348, !349, !350, !351, !354, !355, !356, !357, !358, !359, !360, !361, !362, !363, !364, !365, !366, !367, !368, !369, !370, !371, !372, !373, !374, !375, !376, !377}
!301 = !DIDerivedType(tag: DW_TAG_member, name: "strm", scope: !299, file: !22, line: 367, baseType: !138, size: 64, align: 64)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !299, file: !22, line: 370, baseType: !103, size: 32, align: 32, offset: 64)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "state_out_ch", scope: !299, file: !22, line: 373, baseType: !21, size: 8, align: 8, offset: 96)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "state_out_len", scope: !299, file: !22, line: 374, baseType: !103, size: 32, align: 32, offset: 128)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "blockRandomised", scope: !299, file: !22, line: 375, baseType: !30, size: 8, align: 8, offset: 160)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "rNToGo", scope: !299, file: !22, line: 376, baseType: !103, size: 32, align: 32, offset: 192)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "rTPos", scope: !299, file: !22, line: 376, baseType: !103, size: 32, align: 32, offset: 224)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "bsBuff", scope: !299, file: !22, line: 379, baseType: !28, size: 32, align: 32, offset: 256)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "bsLive", scope: !299, file: !22, line: 380, baseType: !103, size: 32, align: 32, offset: 288)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "blockSize100k", scope: !299, file: !22, line: 383, baseType: !103, size: 32, align: 32, offset: 320)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "smallDecompress", scope: !299, file: !22, line: 384, baseType: !30, size: 8, align: 8, offset: 352)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "currBlockNo", scope: !299, file: !22, line: 385, baseType: !103, size: 32, align: 32, offset: 384)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "verbosity", scope: !299, file: !22, line: 386, baseType: !103, size: 32, align: 32, offset: 416)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "origPtr", scope: !299, file: !22, line: 389, baseType: !103, size: 32, align: 32, offset: 448)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "tPos", scope: !299, file: !22, line: 390, baseType: !28, size: 32, align: 32, offset: 480)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "k0", scope: !299, file: !22, line: 391, baseType: !103, size: 32, align: 32, offset: 512)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "unzftab", scope: !299, file: !22, line: 392, baseType: !318, size: 8192, align: 32, offset: 544)
!318 = !DICompositeType(tag: DW_TAG_array_type, baseType: !103, size: 8192, align: 32, elements: !251)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "nblock_used", scope: !299, file: !22, line: 393, baseType: !103, size: 32, align: 32, offset: 8736)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "cftab", scope: !299, file: !22, line: 394, baseType: !321, size: 8224, align: 32, offset: 8768)
!321 = !DICompositeType(tag: DW_TAG_array_type, baseType: !103, size: 8224, align: 32, elements: !322)
!322 = !{!323}
!323 = !DISubrange(count: 257)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "cftabCopy", scope: !299, file: !22, line: 395, baseType: !321, size: 8224, align: 32, offset: 16992)
!325 = !DIDerivedType(tag: DW_TAG_member, name: "tt", scope: !299, file: !22, line: 398, baseType: !27, size: 64, align: 64, offset: 25216)
!326 = !DIDerivedType(tag: DW_TAG_member, name: "ll16", scope: !299, file: !22, line: 401, baseType: !24, size: 64, align: 64, offset: 25280)
!327 = !DIDerivedType(tag: DW_TAG_member, name: "ll4", scope: !299, file: !22, line: 402, baseType: !20, size: 64, align: 64, offset: 25344)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "storedBlockCRC", scope: !299, file: !22, line: 405, baseType: !28, size: 32, align: 32, offset: 25408)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "storedCombinedCRC", scope: !299, file: !22, line: 406, baseType: !28, size: 32, align: 32, offset: 25440)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "calculatedBlockCRC", scope: !299, file: !22, line: 407, baseType: !28, size: 32, align: 32, offset: 25472)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "calculatedCombinedCRC", scope: !299, file: !22, line: 408, baseType: !28, size: 32, align: 32, offset: 25504)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "nInUse", scope: !299, file: !22, line: 411, baseType: !103, size: 32, align: 32, offset: 25536)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "inUse", scope: !299, file: !22, line: 412, baseType: !250, size: 2048, align: 8, offset: 25568)
!334 = !DIDerivedType(tag: DW_TAG_member, name: "inUse16", scope: !299, file: !22, line: 413, baseType: !335, size: 128, align: 8, offset: 27616)
!335 = !DICompositeType(tag: DW_TAG_array_type, baseType: !30, size: 128, align: 8, elements: !336)
!336 = !{!337}
!337 = !DISubrange(count: 16)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "seqToUnseq", scope: !299, file: !22, line: 414, baseType: !254, size: 2048, align: 8, offset: 27744)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "mtfa", scope: !299, file: !22, line: 417, baseType: !340, size: 32768, align: 8, offset: 29792)
!340 = !DICompositeType(tag: DW_TAG_array_type, baseType: !21, size: 32768, align: 8, elements: !341)
!341 = !{!342}
!342 = !DISubrange(count: 4096)
!343 = !DIDerivedType(tag: DW_TAG_member, name: "mtfbase", scope: !299, file: !22, line: 418, baseType: !344, size: 512, align: 32, offset: 62560)
!344 = !DICompositeType(tag: DW_TAG_array_type, baseType: !103, size: 512, align: 32, elements: !336)
!345 = !DIDerivedType(tag: DW_TAG_member, name: "selector", scope: !299, file: !22, line: 419, baseType: !268, size: 144016, align: 8, offset: 63072)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "selectorMtf", scope: !299, file: !22, line: 420, baseType: !268, size: 144016, align: 8, offset: 207088)
!347 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !299, file: !22, line: 421, baseType: !273, size: 12384, align: 8, offset: 351104)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "limit", scope: !299, file: !22, line: 423, baseType: !277, size: 49536, align: 32, offset: 363488)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !299, file: !22, line: 424, baseType: !277, size: 49536, align: 32, offset: 413024)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "perm", scope: !299, file: !22, line: 425, baseType: !277, size: 49536, align: 32, offset: 462560)
!351 = !DIDerivedType(tag: DW_TAG_member, name: "minLens", scope: !299, file: !22, line: 426, baseType: !352, size: 192, align: 32, offset: 512096)
!352 = !DICompositeType(tag: DW_TAG_array_type, baseType: !103, size: 192, align: 32, elements: !353)
!353 = !{!275}
!354 = !DIDerivedType(tag: DW_TAG_member, name: "save_i", scope: !299, file: !22, line: 429, baseType: !103, size: 32, align: 32, offset: 512288)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "save_j", scope: !299, file: !22, line: 430, baseType: !103, size: 32, align: 32, offset: 512320)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "save_t", scope: !299, file: !22, line: 431, baseType: !103, size: 32, align: 32, offset: 512352)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "save_alphaSize", scope: !299, file: !22, line: 432, baseType: !103, size: 32, align: 32, offset: 512384)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "save_nGroups", scope: !299, file: !22, line: 433, baseType: !103, size: 32, align: 32, offset: 512416)
!359 = !DIDerivedType(tag: DW_TAG_member, name: "save_nSelectors", scope: !299, file: !22, line: 434, baseType: !103, size: 32, align: 32, offset: 512448)
!360 = !DIDerivedType(tag: DW_TAG_member, name: "save_EOB", scope: !299, file: !22, line: 435, baseType: !103, size: 32, align: 32, offset: 512480)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "save_groupNo", scope: !299, file: !22, line: 436, baseType: !103, size: 32, align: 32, offset: 512512)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "save_groupPos", scope: !299, file: !22, line: 437, baseType: !103, size: 32, align: 32, offset: 512544)
!363 = !DIDerivedType(tag: DW_TAG_member, name: "save_nextSym", scope: !299, file: !22, line: 438, baseType: !103, size: 32, align: 32, offset: 512576)
!364 = !DIDerivedType(tag: DW_TAG_member, name: "save_nblockMAX", scope: !299, file: !22, line: 439, baseType: !103, size: 32, align: 32, offset: 512608)
!365 = !DIDerivedType(tag: DW_TAG_member, name: "save_nblock", scope: !299, file: !22, line: 440, baseType: !103, size: 32, align: 32, offset: 512640)
!366 = !DIDerivedType(tag: DW_TAG_member, name: "save_es", scope: !299, file: !22, line: 441, baseType: !103, size: 32, align: 32, offset: 512672)
!367 = !DIDerivedType(tag: DW_TAG_member, name: "save_N", scope: !299, file: !22, line: 442, baseType: !103, size: 32, align: 32, offset: 512704)
!368 = !DIDerivedType(tag: DW_TAG_member, name: "save_curr", scope: !299, file: !22, line: 443, baseType: !103, size: 32, align: 32, offset: 512736)
!369 = !DIDerivedType(tag: DW_TAG_member, name: "save_zt", scope: !299, file: !22, line: 444, baseType: !103, size: 32, align: 32, offset: 512768)
!370 = !DIDerivedType(tag: DW_TAG_member, name: "save_zn", scope: !299, file: !22, line: 445, baseType: !103, size: 32, align: 32, offset: 512800)
!371 = !DIDerivedType(tag: DW_TAG_member, name: "save_zvec", scope: !299, file: !22, line: 446, baseType: !103, size: 32, align: 32, offset: 512832)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "save_zj", scope: !299, file: !22, line: 447, baseType: !103, size: 32, align: 32, offset: 512864)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "save_gSel", scope: !299, file: !22, line: 448, baseType: !103, size: 32, align: 32, offset: 512896)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "save_gMinlen", scope: !299, file: !22, line: 449, baseType: !103, size: 32, align: 32, offset: 512928)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "save_gLimit", scope: !299, file: !22, line: 450, baseType: !151, size: 64, align: 64, offset: 512960)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "save_gBase", scope: !299, file: !22, line: 451, baseType: !151, size: 64, align: 64, offset: 513024)
!377 = !DIDerivedType(tag: DW_TAG_member, name: "save_gPerm", scope: !299, file: !22, line: 452, baseType: !151, size: 64, align: 64, offset: 513088)
!378 = distinct !DISubprogram(name: "unRLE_obuf_to_output_FAST", scope: !1, file: !1, line: 538, type: !295, isLocal: true, isDefinition: true, scopeLine: 539, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!379 = distinct !DISubprogram(name: "myfeof", scope: !1, file: !1, line: 908, type: !380, isLocal: true, isDefinition: true, scopeLine: 909, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!380 = !DISubroutineType(types: !381)
!381 = !{!30, !36}
!382 = distinct !DISubprogram(name: "bzopen_or_bzdopen", scope: !1, file: !1, line: 1385, type: !383, isLocal: true, isDefinition: true, scopeLine: 1390, flags: DIFlagPrototyped, isOptimized: false, variables: !134)
!383 = !DISubroutineType(types: !384)
!384 = !{!157, !192, !43, !192, !43}
!385 = !{!386}
!386 = !DIGlobalVariable(name: "bzerrorstrings", scope: !0, file: !1, line: 1542, type: !387, isLocal: true, isDefinition: true, variable: [16 x i8*]* @bzerrorstrings)
!387 = !DICompositeType(tag: DW_TAG_array_type, baseType: !192, size: 1024, align: 64, elements: !336)
!388 = !{i32 2, !"Dwarf Version", i32 4}
!389 = !{i32 2, !"Debug Info Version", i32 3}
!390 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!391 = !DILocalVariable(name: "errcode", arg: 1, scope: !131, file: !1, line: 41, type: !43)
!392 = !DIExpression()
!393 = !DILocation(line: 41, column: 34, scope: !131)
!394 = !DILocation(line: 43, column: 12, scope: !131)
!395 = !DILocation(line: 52, column: 7, scope: !131)
!396 = !DILocation(line: 53, column: 7, scope: !131)
!397 = !DILocation(line: 43, column: 4, scope: !131)
!398 = !DILocation(line: 56, column: 8, scope: !399)
!399 = distinct !DILexicalBlock(scope: !131, file: !1, line: 56, column: 8)
!400 = !DILocation(line: 56, column: 16, scope: !399)
!401 = !DILocation(line: 56, column: 8, scope: !131)
!402 = !DILocation(line: 57, column: 12, scope: !403)
!403 = distinct !DILexicalBlock(scope: !399, file: !1, line: 56, column: 25)
!404 = !DILocation(line: 57, column: 4, scope: !403)
!405 = !DILocation(line: 82, column: 4, scope: !403)
!406 = !DILocation(line: 84, column: 4, scope: !131)
!407 = !DILocation(line: 85, column: 1, scope: !131)
!408 = !DILocation(line: 1370, column: 4, scope: !189)
!409 = !DILocalVariable(name: "strm", arg: 1, scope: !135, file: !1, line: 151, type: !138)
!410 = !DILocation(line: 151, column: 34, scope: !135)
!411 = !DILocalVariable(name: "blockSize100k", arg: 2, scope: !135, file: !1, line: 152, type: !43)
!412 = !DILocation(line: 152, column: 33, scope: !135)
!413 = !DILocalVariable(name: "verbosity", arg: 3, scope: !135, file: !1, line: 153, type: !43)
!414 = !DILocation(line: 153, column: 33, scope: !135)
!415 = !DILocalVariable(name: "workFactor", arg: 4, scope: !135, file: !1, line: 154, type: !43)
!416 = !DILocation(line: 154, column: 33, scope: !135)
!417 = !DILocalVariable(name: "n", scope: !135, file: !1, line: 156, type: !103)
!418 = !DILocation(line: 156, column: 12, scope: !135)
!419 = !DILocalVariable(name: "s", scope: !135, file: !1, line: 157, type: !223)
!420 = !DILocation(line: 157, column: 12, scope: !135)
!421 = !DILocation(line: 159, column: 9, scope: !422)
!422 = distinct !DILexicalBlock(scope: !135, file: !1, line: 159, column: 8)
!423 = !DILocation(line: 159, column: 8, scope: !135)
!424 = !DILocation(line: 159, column: 25, scope: !425)
!425 = !DILexicalBlockFile(scope: !422, file: !1, discriminator: 1)
!426 = !DILocation(line: 161, column: 8, scope: !427)
!427 = distinct !DILexicalBlock(scope: !135, file: !1, line: 161, column: 8)
!428 = !DILocation(line: 161, column: 13, scope: !427)
!429 = !DILocation(line: 161, column: 21, scope: !427)
!430 = !DILocation(line: 162, column: 8, scope: !427)
!431 = !DILocation(line: 162, column: 22, scope: !427)
!432 = !DILocation(line: 162, column: 26, scope: !427)
!433 = !DILocation(line: 162, column: 29, scope: !434)
!434 = !DILexicalBlockFile(scope: !427, file: !1, discriminator: 1)
!435 = !DILocation(line: 162, column: 43, scope: !434)
!436 = !DILocation(line: 162, column: 47, scope: !434)
!437 = !DILocation(line: 163, column: 8, scope: !427)
!438 = !DILocation(line: 163, column: 19, scope: !427)
!439 = !DILocation(line: 163, column: 23, scope: !427)
!440 = !DILocation(line: 163, column: 26, scope: !434)
!441 = !DILocation(line: 163, column: 37, scope: !434)
!442 = !DILocation(line: 161, column: 8, scope: !443)
!443 = !DILexicalBlockFile(scope: !135, file: !1, discriminator: 1)
!444 = !DILocation(line: 164, column: 6, scope: !427)
!445 = !DILocation(line: 166, column: 8, scope: !446)
!446 = distinct !DILexicalBlock(scope: !135, file: !1, line: 166, column: 8)
!447 = !DILocation(line: 166, column: 19, scope: !446)
!448 = !DILocation(line: 166, column: 8, scope: !135)
!449 = !DILocation(line: 166, column: 36, scope: !450)
!450 = !DILexicalBlockFile(scope: !446, file: !1, discriminator: 1)
!451 = !DILocation(line: 166, column: 25, scope: !450)
!452 = !DILocation(line: 167, column: 8, scope: !453)
!453 = distinct !DILexicalBlock(scope: !135, file: !1, line: 167, column: 8)
!454 = !DILocation(line: 167, column: 14, scope: !453)
!455 = !DILocation(line: 167, column: 22, scope: !453)
!456 = !DILocation(line: 167, column: 8, scope: !135)
!457 = !DILocation(line: 167, column: 31, scope: !458)
!458 = !DILexicalBlockFile(scope: !453, file: !1, discriminator: 1)
!459 = !DILocation(line: 167, column: 37, scope: !458)
!460 = !DILocation(line: 167, column: 45, scope: !458)
!461 = !DILocation(line: 168, column: 8, scope: !462)
!462 = distinct !DILexicalBlock(scope: !135, file: !1, line: 168, column: 8)
!463 = !DILocation(line: 168, column: 14, scope: !462)
!464 = !DILocation(line: 168, column: 21, scope: !462)
!465 = !DILocation(line: 168, column: 8, scope: !135)
!466 = !DILocation(line: 168, column: 30, scope: !467)
!467 = !DILexicalBlockFile(scope: !462, file: !1, discriminator: 1)
!468 = !DILocation(line: 168, column: 36, scope: !467)
!469 = !DILocation(line: 168, column: 43, scope: !467)
!470 = !DILocation(line: 170, column: 8, scope: !135)
!471 = !DILocation(line: 170, column: 6, scope: !135)
!472 = !DILocation(line: 171, column: 8, scope: !473)
!473 = distinct !DILexicalBlock(scope: !135, file: !1, line: 171, column: 8)
!474 = !DILocation(line: 171, column: 10, scope: !473)
!475 = !DILocation(line: 171, column: 8, scope: !135)
!476 = !DILocation(line: 171, column: 19, scope: !477)
!477 = !DILexicalBlockFile(scope: !473, file: !1, discriminator: 1)
!478 = !DILocation(line: 172, column: 14, scope: !135)
!479 = !DILocation(line: 172, column: 4, scope: !135)
!480 = !DILocation(line: 172, column: 7, scope: !135)
!481 = !DILocation(line: 172, column: 12, scope: !135)
!482 = !DILocation(line: 174, column: 4, scope: !135)
!483 = !DILocation(line: 174, column: 7, scope: !135)
!484 = !DILocation(line: 174, column: 12, scope: !135)
!485 = !DILocation(line: 175, column: 4, scope: !135)
!486 = !DILocation(line: 175, column: 7, scope: !135)
!487 = !DILocation(line: 175, column: 12, scope: !135)
!488 = !DILocation(line: 176, column: 4, scope: !135)
!489 = !DILocation(line: 176, column: 7, scope: !135)
!490 = !DILocation(line: 176, column: 12, scope: !135)
!491 = !DILocation(line: 178, column: 23, scope: !135)
!492 = !DILocation(line: 178, column: 21, scope: !135)
!493 = !DILocation(line: 178, column: 12, scope: !135)
!494 = !DILocation(line: 179, column: 14, scope: !135)
!495 = !DILocation(line: 179, column: 4, scope: !135)
!496 = !DILocation(line: 179, column: 7, scope: !135)
!497 = !DILocation(line: 179, column: 12, scope: !135)
!498 = !DILocation(line: 180, column: 14, scope: !135)
!499 = !DILocation(line: 180, column: 4, scope: !135)
!500 = !DILocation(line: 180, column: 7, scope: !135)
!501 = !DILocation(line: 180, column: 12, scope: !135)
!502 = !DILocation(line: 181, column: 14, scope: !135)
!503 = !DILocation(line: 181, column: 4, scope: !135)
!504 = !DILocation(line: 181, column: 7, scope: !135)
!505 = !DILocation(line: 181, column: 12, scope: !135)
!506 = !DILocation(line: 183, column: 8, scope: !507)
!507 = distinct !DILexicalBlock(scope: !135, file: !1, line: 183, column: 8)
!508 = !DILocation(line: 183, column: 11, scope: !507)
!509 = !DILocation(line: 183, column: 16, scope: !507)
!510 = !DILocation(line: 183, column: 24, scope: !507)
!511 = !DILocation(line: 183, column: 27, scope: !512)
!512 = !DILexicalBlockFile(scope: !507, file: !1, discriminator: 1)
!513 = !DILocation(line: 183, column: 30, scope: !512)
!514 = !DILocation(line: 183, column: 35, scope: !512)
!515 = !DILocation(line: 183, column: 43, scope: !512)
!516 = !DILocation(line: 183, column: 46, scope: !517)
!517 = !DILexicalBlockFile(scope: !507, file: !1, discriminator: 2)
!518 = !DILocation(line: 183, column: 49, scope: !517)
!519 = !DILocation(line: 183, column: 54, scope: !517)
!520 = !DILocation(line: 183, column: 8, scope: !517)
!521 = !DILocation(line: 184, column: 11, scope: !522)
!522 = distinct !DILexicalBlock(scope: !523, file: !1, line: 184, column: 11)
!523 = distinct !DILexicalBlock(scope: !507, file: !1, line: 183, column: 63)
!524 = !DILocation(line: 184, column: 14, scope: !522)
!525 = !DILocation(line: 184, column: 19, scope: !522)
!526 = !DILocation(line: 184, column: 11, scope: !523)
!527 = !DILocation(line: 184, column: 28, scope: !528)
!528 = !DILexicalBlockFile(scope: !522, file: !1, discriminator: 1)
!529 = !DILocation(line: 185, column: 11, scope: !530)
!530 = distinct !DILexicalBlock(scope: !523, file: !1, line: 185, column: 11)
!531 = !DILocation(line: 185, column: 14, scope: !530)
!532 = !DILocation(line: 185, column: 19, scope: !530)
!533 = !DILocation(line: 185, column: 11, scope: !523)
!534 = !DILocation(line: 185, column: 28, scope: !535)
!535 = !DILexicalBlockFile(scope: !530, file: !1, discriminator: 1)
!536 = !DILocation(line: 186, column: 11, scope: !537)
!537 = distinct !DILexicalBlock(scope: !523, file: !1, line: 186, column: 11)
!538 = !DILocation(line: 186, column: 14, scope: !537)
!539 = !DILocation(line: 186, column: 19, scope: !537)
!540 = !DILocation(line: 186, column: 11, scope: !523)
!541 = !DILocation(line: 186, column: 28, scope: !542)
!542 = !DILexicalBlockFile(scope: !537, file: !1, discriminator: 1)
!543 = !DILocation(line: 187, column: 11, scope: !544)
!544 = distinct !DILexicalBlock(scope: !523, file: !1, line: 187, column: 11)
!545 = !DILocation(line: 187, column: 19, scope: !544)
!546 = !DILocation(line: 187, column: 11, scope: !523)
!547 = !DILocation(line: 187, column: 28, scope: !548)
!548 = !DILexicalBlockFile(scope: !544, file: !1, discriminator: 1)
!549 = !DILocation(line: 188, column: 7, scope: !523)
!550 = !DILocation(line: 191, column: 4, scope: !135)
!551 = !DILocation(line: 191, column: 7, scope: !135)
!552 = !DILocation(line: 191, column: 25, scope: !135)
!553 = !DILocation(line: 192, column: 4, scope: !135)
!554 = !DILocation(line: 192, column: 7, scope: !135)
!555 = !DILocation(line: 192, column: 25, scope: !135)
!556 = !DILocation(line: 193, column: 4, scope: !135)
!557 = !DILocation(line: 193, column: 7, scope: !135)
!558 = !DILocation(line: 193, column: 25, scope: !135)
!559 = !DILocation(line: 194, column: 4, scope: !135)
!560 = !DILocation(line: 194, column: 7, scope: !135)
!561 = !DILocation(line: 194, column: 25, scope: !135)
!562 = !DILocation(line: 195, column: 27, scope: !135)
!563 = !DILocation(line: 195, column: 4, scope: !135)
!564 = !DILocation(line: 195, column: 7, scope: !135)
!565 = !DILocation(line: 195, column: 25, scope: !135)
!566 = !DILocation(line: 196, column: 36, scope: !135)
!567 = !DILocation(line: 196, column: 34, scope: !135)
!568 = !DILocation(line: 196, column: 50, scope: !135)
!569 = !DILocation(line: 196, column: 4, scope: !135)
!570 = !DILocation(line: 196, column: 7, scope: !135)
!571 = !DILocation(line: 196, column: 25, scope: !135)
!572 = !DILocation(line: 197, column: 27, scope: !135)
!573 = !DILocation(line: 197, column: 4, scope: !135)
!574 = !DILocation(line: 197, column: 7, scope: !135)
!575 = !DILocation(line: 197, column: 25, scope: !135)
!576 = !DILocation(line: 198, column: 27, scope: !135)
!577 = !DILocation(line: 198, column: 4, scope: !135)
!578 = !DILocation(line: 198, column: 7, scope: !135)
!579 = !DILocation(line: 198, column: 25, scope: !135)
!580 = !DILocation(line: 200, column: 35, scope: !135)
!581 = !DILocation(line: 200, column: 38, scope: !135)
!582 = !DILocation(line: 200, column: 27, scope: !135)
!583 = !DILocation(line: 200, column: 4, scope: !135)
!584 = !DILocation(line: 200, column: 7, scope: !135)
!585 = !DILocation(line: 200, column: 25, scope: !135)
!586 = !DILocation(line: 201, column: 36, scope: !135)
!587 = !DILocation(line: 201, column: 39, scope: !135)
!588 = !DILocation(line: 201, column: 27, scope: !135)
!589 = !DILocation(line: 201, column: 4, scope: !135)
!590 = !DILocation(line: 201, column: 7, scope: !135)
!591 = !DILocation(line: 201, column: 25, scope: !135)
!592 = !DILocation(line: 202, column: 4, scope: !135)
!593 = !DILocation(line: 202, column: 7, scope: !135)
!594 = !DILocation(line: 202, column: 25, scope: !135)
!595 = !DILocation(line: 203, column: 36, scope: !135)
!596 = !DILocation(line: 203, column: 39, scope: !135)
!597 = !DILocation(line: 203, column: 4, scope: !135)
!598 = !DILocation(line: 203, column: 7, scope: !135)
!599 = !DILocation(line: 203, column: 25, scope: !135)
!600 = !DILocation(line: 205, column: 27, scope: !135)
!601 = !DILocation(line: 205, column: 4, scope: !135)
!602 = !DILocation(line: 205, column: 10, scope: !135)
!603 = !DILocation(line: 205, column: 25, scope: !135)
!604 = !DILocation(line: 206, column: 4, scope: !135)
!605 = !DILocation(line: 206, column: 10, scope: !135)
!606 = !DILocation(line: 206, column: 25, scope: !135)
!607 = !DILocation(line: 207, column: 4, scope: !135)
!608 = !DILocation(line: 207, column: 10, scope: !135)
!609 = !DILocation(line: 207, column: 25, scope: !135)
!610 = !DILocation(line: 208, column: 4, scope: !135)
!611 = !DILocation(line: 208, column: 10, scope: !135)
!612 = !DILocation(line: 208, column: 25, scope: !135)
!613 = !DILocation(line: 209, column: 4, scope: !135)
!614 = !DILocation(line: 209, column: 10, scope: !135)
!615 = !DILocation(line: 209, column: 25, scope: !135)
!616 = !DILocation(line: 210, column: 14, scope: !135)
!617 = !DILocation(line: 210, column: 4, scope: !135)
!618 = !DILocation(line: 211, column: 24, scope: !135)
!619 = !DILocation(line: 211, column: 4, scope: !135)
!620 = !DILocation(line: 212, column: 4, scope: !135)
!621 = !DILocation(line: 213, column: 1, scope: !135)
!622 = !DILocation(line: 96, column: 4, scope: !213)
!623 = !DILocalVariable(name: "opaque", arg: 1, scope: !216, file: !1, line: 102, type: !19)
!624 = !DILocation(line: 102, column: 31, scope: !216)
!625 = !DILocalVariable(name: "items", arg: 2, scope: !216, file: !1, line: 102, type: !103)
!626 = !DILocation(line: 102, column: 45, scope: !216)
!627 = !DILocalVariable(name: "size", arg: 3, scope: !216, file: !1, line: 102, type: !103)
!628 = !DILocation(line: 102, column: 58, scope: !216)
!629 = !DILocalVariable(name: "v", scope: !216, file: !1, line: 104, type: !19)
!630 = !DILocation(line: 104, column: 10, scope: !216)
!631 = !DILocation(line: 104, column: 23, scope: !216)
!632 = !DILocation(line: 104, column: 31, scope: !216)
!633 = !DILocation(line: 104, column: 29, scope: !216)
!634 = !DILocation(line: 104, column: 14, scope: !216)
!635 = !DILocation(line: 105, column: 9, scope: !216)
!636 = !DILocation(line: 106, column: 11, scope: !216)
!637 = !DILocation(line: 106, column: 4, scope: !216)
!638 = !DILocalVariable(name: "opaque", arg: 1, scope: !219, file: !1, line: 110, type: !19)
!639 = !DILocation(line: 110, column: 29, scope: !219)
!640 = !DILocalVariable(name: "addr", arg: 2, scope: !219, file: !1, line: 110, type: !19)
!641 = !DILocation(line: 110, column: 43, scope: !219)
!642 = !DILocation(line: 112, column: 8, scope: !643)
!643 = distinct !DILexicalBlock(scope: !219, file: !1, line: 112, column: 8)
!644 = !DILocation(line: 112, column: 13, scope: !643)
!645 = !DILocation(line: 112, column: 8, scope: !219)
!646 = !DILocation(line: 112, column: 29, scope: !647)
!647 = !DILexicalBlockFile(scope: !643, file: !1, discriminator: 1)
!648 = !DILocation(line: 112, column: 22, scope: !647)
!649 = !DILocation(line: 113, column: 9, scope: !219)
!650 = !DILocation(line: 114, column: 1, scope: !219)
!651 = !DILocalVariable(name: "s", arg: 1, scope: !220, file: !1, line: 133, type: !223)
!652 = !DILocation(line: 133, column: 24, scope: !220)
!653 = !DILocation(line: 135, column: 4, scope: !220)
!654 = !DILocation(line: 135, column: 7, scope: !220)
!655 = !DILocation(line: 135, column: 20, scope: !220)
!656 = !DILocation(line: 136, column: 4, scope: !220)
!657 = !DILocation(line: 136, column: 7, scope: !220)
!658 = !DILocation(line: 136, column: 20, scope: !220)
!659 = !DILocation(line: 137, column: 1, scope: !220)
!660 = !DILocalVariable(name: "s", arg: 1, scope: !283, file: !1, line: 119, type: !223)
!661 = !DILocation(line: 119, column: 34, scope: !283)
!662 = !DILocalVariable(name: "i", scope: !283, file: !1, line: 121, type: !103)
!663 = !DILocation(line: 121, column: 10, scope: !283)
!664 = !DILocation(line: 122, column: 4, scope: !283)
!665 = !DILocation(line: 122, column: 7, scope: !283)
!666 = !DILocation(line: 122, column: 14, scope: !283)
!667 = !DILocation(line: 123, column: 4, scope: !283)
!668 = !DILocation(line: 123, column: 7, scope: !283)
!669 = !DILocation(line: 123, column: 12, scope: !283)
!670 = !DILocation(line: 124, column: 4, scope: !283)
!671 = !DILocation(line: 124, column: 7, scope: !283)
!672 = !DILocation(line: 124, column: 21, scope: !283)
!673 = !DILocation(line: 125, column: 4, scope: !674)
!674 = distinct !DILexicalBlock(scope: !283, file: !1, line: 125, column: 4)
!675 = !DILocation(line: 126, column: 11, scope: !676)
!676 = distinct !DILexicalBlock(scope: !283, file: !1, line: 126, column: 4)
!677 = !DILocation(line: 126, column: 9, scope: !676)
!678 = !DILocation(line: 126, column: 16, scope: !679)
!679 = !DILexicalBlockFile(scope: !680, file: !1, discriminator: 1)
!680 = distinct !DILexicalBlock(scope: !676, file: !1, line: 126, column: 4)
!681 = !DILocation(line: 126, column: 18, scope: !679)
!682 = !DILocation(line: 126, column: 4, scope: !679)
!683 = !DILocation(line: 126, column: 39, scope: !684)
!684 = !DILexicalBlockFile(scope: !680, file: !1, discriminator: 2)
!685 = !DILocation(line: 126, column: 30, scope: !684)
!686 = !DILocation(line: 126, column: 33, scope: !684)
!687 = !DILocation(line: 126, column: 42, scope: !684)
!688 = !DILocation(line: 126, column: 26, scope: !689)
!689 = !DILexicalBlockFile(scope: !680, file: !1, discriminator: 3)
!690 = !DILocation(line: 126, column: 4, scope: !689)
!691 = !DILocation(line: 127, column: 4, scope: !283)
!692 = !DILocation(line: 127, column: 7, scope: !283)
!693 = !DILocation(line: 127, column: 14, scope: !283)
!694 = !DILocation(line: 128, column: 1, scope: !283)
!695 = !DILocalVariable(name: "strm", arg: 1, scope: !139, file: !1, line: 409, type: !138)
!696 = !DILocation(line: 409, column: 41, scope: !139)
!697 = !DILocalVariable(name: "action", arg: 2, scope: !139, file: !1, line: 409, type: !43)
!698 = !DILocation(line: 409, column: 51, scope: !139)
!699 = !DILocalVariable(name: "progress", scope: !139, file: !1, line: 411, type: !30)
!700 = !DILocation(line: 411, column: 9, scope: !139)
!701 = !DILocalVariable(name: "s", scope: !139, file: !1, line: 412, type: !223)
!702 = !DILocation(line: 412, column: 12, scope: !139)
!703 = !DILocation(line: 413, column: 8, scope: !704)
!704 = distinct !DILexicalBlock(scope: !139, file: !1, line: 413, column: 8)
!705 = !DILocation(line: 413, column: 13, scope: !704)
!706 = !DILocation(line: 413, column: 8, scope: !139)
!707 = !DILocation(line: 413, column: 22, scope: !708)
!708 = !DILexicalBlockFile(scope: !704, file: !1, discriminator: 1)
!709 = !DILocation(line: 414, column: 8, scope: !139)
!710 = !DILocation(line: 414, column: 14, scope: !139)
!711 = !DILocation(line: 414, column: 6, scope: !139)
!712 = !DILocation(line: 415, column: 8, scope: !713)
!713 = distinct !DILexicalBlock(scope: !139, file: !1, line: 415, column: 8)
!714 = !DILocation(line: 415, column: 10, scope: !713)
!715 = !DILocation(line: 415, column: 8, scope: !139)
!716 = !DILocation(line: 415, column: 19, scope: !717)
!717 = !DILexicalBlockFile(scope: !713, file: !1, discriminator: 1)
!718 = !DILocation(line: 416, column: 8, scope: !719)
!719 = distinct !DILexicalBlock(scope: !139, file: !1, line: 416, column: 8)
!720 = !DILocation(line: 416, column: 11, scope: !719)
!721 = !DILocation(line: 416, column: 19, scope: !719)
!722 = !DILocation(line: 416, column: 16, scope: !719)
!723 = !DILocation(line: 416, column: 8, scope: !139)
!724 = !DILocation(line: 416, column: 25, scope: !725)
!725 = !DILexicalBlockFile(scope: !719, file: !1, discriminator: 1)
!726 = !DILocation(line: 416, column: 19, scope: !727)
!727 = !DILexicalBlockFile(scope: !719, file: !1, discriminator: 2)
!728 = !DILocation(line: 419, column: 12, scope: !139)
!729 = !DILocation(line: 419, column: 15, scope: !139)
!730 = !DILocation(line: 419, column: 4, scope: !139)
!731 = !DILocation(line: 422, column: 10, scope: !732)
!732 = distinct !DILexicalBlock(scope: !139, file: !1, line: 419, column: 21)
!733 = !DILocation(line: 425, column: 14, scope: !734)
!734 = distinct !DILexicalBlock(scope: !732, file: !1, line: 425, column: 14)
!735 = !DILocation(line: 425, column: 21, scope: !734)
!736 = !DILocation(line: 425, column: 14, scope: !732)
!737 = !DILocation(line: 426, column: 42, scope: !738)
!738 = distinct !DILexicalBlock(scope: !734, file: !1, line: 425, column: 32)
!739 = !DILocation(line: 426, column: 24, scope: !738)
!740 = !DILocation(line: 426, column: 22, scope: !738)
!741 = !DILocation(line: 427, column: 20, scope: !738)
!742 = !DILocation(line: 427, column: 13, scope: !738)
!743 = !DILocation(line: 430, column: 10, scope: !744)
!744 = distinct !DILexicalBlock(scope: !734, file: !1, line: 430, column: 10)
!745 = !DILocation(line: 430, column: 17, scope: !744)
!746 = !DILocation(line: 430, column: 10, scope: !734)
!747 = !DILocation(line: 431, column: 34, scope: !748)
!748 = distinct !DILexicalBlock(scope: !744, file: !1, line: 430, column: 30)
!749 = !DILocation(line: 431, column: 40, scope: !748)
!750 = !DILocation(line: 431, column: 13, scope: !748)
!751 = !DILocation(line: 431, column: 16, scope: !748)
!752 = !DILocation(line: 431, column: 32, scope: !748)
!753 = !DILocation(line: 432, column: 13, scope: !748)
!754 = !DILocation(line: 432, column: 16, scope: !748)
!755 = !DILocation(line: 432, column: 21, scope: !748)
!756 = !DILocation(line: 433, column: 13, scope: !748)
!757 = !DILocation(line: 436, column: 14, scope: !758)
!758 = distinct !DILexicalBlock(scope: !744, file: !1, line: 436, column: 14)
!759 = !DILocation(line: 436, column: 21, scope: !758)
!760 = !DILocation(line: 436, column: 14, scope: !744)
!761 = !DILocation(line: 437, column: 34, scope: !762)
!762 = distinct !DILexicalBlock(scope: !758, file: !1, line: 436, column: 35)
!763 = !DILocation(line: 437, column: 40, scope: !762)
!764 = !DILocation(line: 437, column: 13, scope: !762)
!765 = !DILocation(line: 437, column: 16, scope: !762)
!766 = !DILocation(line: 437, column: 32, scope: !762)
!767 = !DILocation(line: 438, column: 13, scope: !762)
!768 = !DILocation(line: 438, column: 16, scope: !762)
!769 = !DILocation(line: 438, column: 21, scope: !762)
!770 = !DILocation(line: 439, column: 13, scope: !762)
!771 = !DILocation(line: 442, column: 13, scope: !758)
!772 = !DILocation(line: 445, column: 14, scope: !773)
!773 = distinct !DILexicalBlock(scope: !732, file: !1, line: 445, column: 14)
!774 = !DILocation(line: 445, column: 21, scope: !773)
!775 = !DILocation(line: 445, column: 14, scope: !732)
!776 = !DILocation(line: 445, column: 34, scope: !777)
!777 = !DILexicalBlockFile(scope: !773, file: !1, discriminator: 1)
!778 = !DILocation(line: 446, column: 14, scope: !779)
!779 = distinct !DILexicalBlock(scope: !732, file: !1, line: 446, column: 14)
!780 = !DILocation(line: 446, column: 17, scope: !779)
!781 = !DILocation(line: 446, column: 36, scope: !779)
!782 = !DILocation(line: 446, column: 39, scope: !779)
!783 = !DILocation(line: 446, column: 45, scope: !779)
!784 = !DILocation(line: 446, column: 33, scope: !779)
!785 = !DILocation(line: 446, column: 14, scope: !732)
!786 = !DILocation(line: 447, column: 13, scope: !779)
!787 = !DILocation(line: 448, column: 39, scope: !732)
!788 = !DILocation(line: 448, column: 21, scope: !732)
!789 = !DILocation(line: 448, column: 19, scope: !732)
!790 = !DILocation(line: 449, column: 14, scope: !791)
!791 = distinct !DILexicalBlock(scope: !732, file: !1, line: 449, column: 14)
!792 = !DILocation(line: 449, column: 17, scope: !791)
!793 = !DILocation(line: 449, column: 33, scope: !791)
!794 = !DILocation(line: 449, column: 37, scope: !791)
!795 = !DILocation(line: 449, column: 52, scope: !796)
!796 = !DILexicalBlockFile(scope: !791, file: !1, discriminator: 1)
!797 = !DILocation(line: 449, column: 41, scope: !796)
!798 = !DILocation(line: 449, column: 55, scope: !796)
!799 = !DILocation(line: 450, column: 14, scope: !791)
!800 = !DILocation(line: 450, column: 17, scope: !791)
!801 = !DILocation(line: 450, column: 33, scope: !791)
!802 = !DILocation(line: 450, column: 36, scope: !791)
!803 = !DILocation(line: 450, column: 31, scope: !791)
!804 = !DILocation(line: 449, column: 14, scope: !805)
!805 = !DILexicalBlockFile(scope: !732, file: !1, discriminator: 2)
!806 = !DILocation(line: 450, column: 42, scope: !796)
!807 = !DILocation(line: 451, column: 10, scope: !732)
!808 = !DILocation(line: 451, column: 13, scope: !732)
!809 = !DILocation(line: 451, column: 18, scope: !732)
!810 = !DILocation(line: 452, column: 10, scope: !732)
!811 = !DILocation(line: 455, column: 14, scope: !812)
!812 = distinct !DILexicalBlock(scope: !732, file: !1, line: 455, column: 14)
!813 = !DILocation(line: 455, column: 21, scope: !812)
!814 = !DILocation(line: 455, column: 14, scope: !732)
!815 = !DILocation(line: 455, column: 35, scope: !816)
!816 = !DILexicalBlockFile(scope: !812, file: !1, discriminator: 1)
!817 = !DILocation(line: 456, column: 14, scope: !818)
!818 = distinct !DILexicalBlock(scope: !732, file: !1, line: 456, column: 14)
!819 = !DILocation(line: 456, column: 17, scope: !818)
!820 = !DILocation(line: 456, column: 36, scope: !818)
!821 = !DILocation(line: 456, column: 39, scope: !818)
!822 = !DILocation(line: 456, column: 45, scope: !818)
!823 = !DILocation(line: 456, column: 33, scope: !818)
!824 = !DILocation(line: 456, column: 14, scope: !732)
!825 = !DILocation(line: 457, column: 13, scope: !818)
!826 = !DILocation(line: 458, column: 39, scope: !732)
!827 = !DILocation(line: 458, column: 21, scope: !732)
!828 = !DILocation(line: 458, column: 19, scope: !732)
!829 = !DILocation(line: 459, column: 15, scope: !830)
!830 = distinct !DILexicalBlock(scope: !732, file: !1, line: 459, column: 14)
!831 = !DILocation(line: 459, column: 14, scope: !732)
!832 = !DILocation(line: 459, column: 25, scope: !833)
!833 = !DILexicalBlockFile(scope: !830, file: !1, discriminator: 1)
!834 = !DILocation(line: 460, column: 14, scope: !835)
!835 = distinct !DILexicalBlock(scope: !732, file: !1, line: 460, column: 14)
!836 = !DILocation(line: 460, column: 17, scope: !835)
!837 = !DILocation(line: 460, column: 33, scope: !835)
!838 = !DILocation(line: 460, column: 37, scope: !835)
!839 = !DILocation(line: 460, column: 52, scope: !840)
!840 = !DILexicalBlockFile(scope: !835, file: !1, discriminator: 1)
!841 = !DILocation(line: 460, column: 41, scope: !840)
!842 = !DILocation(line: 460, column: 55, scope: !840)
!843 = !DILocation(line: 461, column: 14, scope: !835)
!844 = !DILocation(line: 461, column: 17, scope: !835)
!845 = !DILocation(line: 461, column: 33, scope: !835)
!846 = !DILocation(line: 461, column: 36, scope: !835)
!847 = !DILocation(line: 461, column: 31, scope: !835)
!848 = !DILocation(line: 460, column: 14, scope: !805)
!849 = !DILocation(line: 461, column: 42, scope: !840)
!850 = !DILocation(line: 462, column: 10, scope: !732)
!851 = !DILocation(line: 462, column: 13, scope: !732)
!852 = !DILocation(line: 462, column: 18, scope: !732)
!853 = !DILocation(line: 463, column: 10, scope: !732)
!854 = !DILocation(line: 465, column: 4, scope: !139)
!855 = !DILocation(line: 466, column: 1, scope: !139)
!856 = !DILocalVariable(name: "strm", arg: 1, scope: !284, file: !1, line: 363, type: !138)
!857 = !DILocation(line: 363, column: 35, scope: !284)
!858 = !DILocalVariable(name: "progress_in", scope: !284, file: !1, line: 365, type: !30)
!859 = !DILocation(line: 365, column: 9, scope: !284)
!860 = !DILocalVariable(name: "progress_out", scope: !284, file: !1, line: 366, type: !30)
!861 = !DILocation(line: 366, column: 9, scope: !284)
!862 = !DILocalVariable(name: "s", scope: !284, file: !1, line: 367, type: !223)
!863 = !DILocation(line: 367, column: 12, scope: !284)
!864 = !DILocation(line: 367, column: 16, scope: !284)
!865 = !DILocation(line: 367, column: 22, scope: !284)
!866 = !DILocation(line: 369, column: 4, scope: !284)
!867 = !DILocation(line: 371, column: 11, scope: !868)
!868 = distinct !DILexicalBlock(scope: !869, file: !1, line: 371, column: 11)
!869 = distinct !DILexicalBlock(scope: !284, file: !1, line: 369, column: 17)
!870 = !DILocation(line: 371, column: 14, scope: !868)
!871 = !DILocation(line: 371, column: 20, scope: !868)
!872 = !DILocation(line: 371, column: 11, scope: !869)
!873 = !DILocation(line: 372, column: 51, scope: !874)
!874 = distinct !DILexicalBlock(scope: !868, file: !1, line: 371, column: 36)
!875 = !DILocation(line: 372, column: 26, scope: !874)
!876 = !DILocation(line: 372, column: 23, scope: !874)
!877 = !DILocation(line: 373, column: 14, scope: !878)
!878 = distinct !DILexicalBlock(scope: !874, file: !1, line: 373, column: 14)
!879 = !DILocation(line: 373, column: 17, scope: !878)
!880 = !DILocation(line: 373, column: 33, scope: !878)
!881 = !DILocation(line: 373, column: 36, scope: !878)
!882 = !DILocation(line: 373, column: 31, scope: !878)
!883 = !DILocation(line: 373, column: 14, scope: !874)
!884 = !DILocation(line: 373, column: 42, scope: !885)
!885 = !DILexicalBlockFile(scope: !878, file: !1, discriminator: 1)
!886 = !DILocation(line: 374, column: 14, scope: !887)
!887 = distinct !DILexicalBlock(scope: !874, file: !1, line: 374, column: 14)
!888 = !DILocation(line: 374, column: 17, scope: !887)
!889 = !DILocation(line: 374, column: 22, scope: !887)
!890 = !DILocation(line: 374, column: 40, scope: !887)
!891 = !DILocation(line: 375, column: 14, scope: !887)
!892 = !DILocation(line: 375, column: 17, scope: !887)
!893 = !DILocation(line: 375, column: 33, scope: !887)
!894 = !DILocation(line: 375, column: 38, scope: !887)
!895 = !DILocation(line: 376, column: 25, scope: !887)
!896 = !DILocation(line: 376, column: 14, scope: !887)
!897 = !DILocation(line: 374, column: 14, scope: !898)
!898 = !DILexicalBlockFile(scope: !874, file: !1, discriminator: 1)
!899 = !DILocation(line: 376, column: 29, scope: !900)
!900 = !DILexicalBlockFile(scope: !887, file: !1, discriminator: 1)
!901 = !DILocation(line: 377, column: 30, scope: !874)
!902 = !DILocation(line: 377, column: 10, scope: !874)
!903 = !DILocation(line: 378, column: 10, scope: !874)
!904 = !DILocation(line: 378, column: 13, scope: !874)
!905 = !DILocation(line: 378, column: 19, scope: !874)
!906 = !DILocation(line: 379, column: 14, scope: !907)
!907 = distinct !DILexicalBlock(scope: !874, file: !1, line: 379, column: 14)
!908 = !DILocation(line: 379, column: 17, scope: !907)
!909 = !DILocation(line: 379, column: 22, scope: !907)
!910 = !DILocation(line: 379, column: 39, scope: !907)
!911 = !DILocation(line: 380, column: 14, scope: !907)
!912 = !DILocation(line: 380, column: 17, scope: !907)
!913 = !DILocation(line: 380, column: 33, scope: !907)
!914 = !DILocation(line: 380, column: 38, scope: !907)
!915 = !DILocation(line: 381, column: 25, scope: !907)
!916 = !DILocation(line: 381, column: 14, scope: !907)
!917 = !DILocation(line: 379, column: 14, scope: !898)
!918 = !DILocation(line: 381, column: 29, scope: !919)
!919 = !DILexicalBlockFile(scope: !907, file: !1, discriminator: 1)
!920 = !DILocation(line: 382, column: 7, scope: !874)
!921 = !DILocation(line: 384, column: 11, scope: !922)
!922 = distinct !DILexicalBlock(scope: !869, file: !1, line: 384, column: 11)
!923 = !DILocation(line: 384, column: 14, scope: !922)
!924 = !DILocation(line: 384, column: 20, scope: !922)
!925 = !DILocation(line: 384, column: 11, scope: !869)
!926 = !DILocation(line: 385, column: 49, scope: !927)
!927 = distinct !DILexicalBlock(scope: !922, file: !1, line: 384, column: 35)
!928 = !DILocation(line: 385, column: 25, scope: !927)
!929 = !DILocation(line: 385, column: 22, scope: !927)
!930 = !DILocation(line: 386, column: 14, scope: !931)
!931 = distinct !DILexicalBlock(scope: !927, file: !1, line: 386, column: 14)
!932 = !DILocation(line: 386, column: 17, scope: !931)
!933 = !DILocation(line: 386, column: 22, scope: !931)
!934 = !DILocation(line: 386, column: 38, scope: !931)
!935 = !DILocation(line: 386, column: 41, scope: !936)
!936 = !DILexicalBlockFile(scope: !931, file: !1, discriminator: 1)
!937 = !DILocation(line: 386, column: 44, scope: !936)
!938 = !DILocation(line: 386, column: 60, scope: !936)
!939 = !DILocation(line: 386, column: 14, scope: !936)
!940 = !DILocation(line: 387, column: 24, scope: !941)
!941 = distinct !DILexicalBlock(scope: !931, file: !1, line: 386, column: 66)
!942 = !DILocation(line: 387, column: 13, scope: !941)
!943 = !DILocation(line: 388, column: 33, scope: !941)
!944 = !DILocation(line: 388, column: 43, scope: !941)
!945 = !DILocation(line: 388, column: 46, scope: !941)
!946 = !DILocation(line: 388, column: 51, scope: !941)
!947 = !DILocation(line: 388, column: 36, scope: !941)
!948 = !DILocation(line: 388, column: 13, scope: !941)
!949 = !DILocation(line: 389, column: 13, scope: !941)
!950 = !DILocation(line: 389, column: 16, scope: !941)
!951 = !DILocation(line: 389, column: 22, scope: !941)
!952 = !DILocation(line: 390, column: 10, scope: !941)
!953 = !DILocation(line: 392, column: 14, scope: !954)
!954 = distinct !DILexicalBlock(scope: !931, file: !1, line: 392, column: 14)
!955 = !DILocation(line: 392, column: 17, scope: !954)
!956 = !DILocation(line: 392, column: 27, scope: !954)
!957 = !DILocation(line: 392, column: 30, scope: !954)
!958 = !DILocation(line: 392, column: 24, scope: !954)
!959 = !DILocation(line: 392, column: 14, scope: !931)
!960 = !DILocation(line: 393, column: 33, scope: !961)
!961 = distinct !DILexicalBlock(scope: !954, file: !1, line: 392, column: 41)
!962 = !DILocation(line: 393, column: 13, scope: !961)
!963 = !DILocation(line: 394, column: 13, scope: !961)
!964 = !DILocation(line: 394, column: 16, scope: !961)
!965 = !DILocation(line: 394, column: 22, scope: !961)
!966 = !DILocation(line: 395, column: 10, scope: !961)
!967 = !DILocation(line: 397, column: 14, scope: !968)
!968 = distinct !DILexicalBlock(scope: !954, file: !1, line: 397, column: 14)
!969 = !DILocation(line: 397, column: 17, scope: !968)
!970 = !DILocation(line: 397, column: 23, scope: !968)
!971 = !DILocation(line: 397, column: 32, scope: !968)
!972 = !DILocation(line: 397, column: 14, scope: !954)
!973 = !DILocation(line: 398, column: 13, scope: !974)
!974 = distinct !DILexicalBlock(scope: !968, file: !1, line: 397, column: 38)
!975 = !DILocation(line: 400, column: 7, scope: !927)
!976 = !DILocation(line: 369, column: 4, scope: !977)
!977 = !DILexicalBlockFile(scope: !284, file: !1, discriminator: 1)
!978 = !DILocation(line: 404, column: 11, scope: !284)
!979 = !DILocation(line: 404, column: 23, scope: !284)
!980 = !DILocation(line: 404, column: 26, scope: !977)
!981 = !DILocation(line: 404, column: 23, scope: !977)
!982 = !DILocation(line: 404, column: 23, scope: !983)
!983 = !DILexicalBlockFile(scope: !284, file: !1, discriminator: 2)
!984 = !DILocation(line: 404, column: 11, scope: !983)
!985 = !DILocation(line: 404, column: 4, scope: !983)
!986 = !DILocalVariable(name: "s", arg: 1, scope: !293, file: !1, line: 141, type: !223)
!987 = !DILocation(line: 141, column: 27, scope: !293)
!988 = !DILocation(line: 143, column: 8, scope: !989)
!989 = distinct !DILexicalBlock(scope: !293, file: !1, line: 143, column: 8)
!990 = !DILocation(line: 143, column: 11, scope: !989)
!991 = !DILocation(line: 143, column: 23, scope: !989)
!992 = !DILocation(line: 143, column: 29, scope: !989)
!993 = !DILocation(line: 143, column: 32, scope: !994)
!994 = !DILexicalBlockFile(scope: !989, file: !1, discriminator: 1)
!995 = !DILocation(line: 143, column: 35, scope: !994)
!996 = !DILocation(line: 143, column: 48, scope: !994)
!997 = !DILocation(line: 143, column: 8, scope: !994)
!998 = !DILocation(line: 144, column: 7, scope: !989)
!999 = !DILocation(line: 145, column: 7, scope: !989)
!1000 = !DILocation(line: 146, column: 1, scope: !293)
!1001 = !DILocalVariable(name: "strm", arg: 1, scope: !142, file: !1, line: 470, type: !138)
!1002 = !DILocation(line: 470, column: 45, scope: !142)
!1003 = !DILocalVariable(name: "s", scope: !142, file: !1, line: 472, type: !223)
!1004 = !DILocation(line: 472, column: 12, scope: !142)
!1005 = !DILocation(line: 473, column: 8, scope: !1006)
!1006 = distinct !DILexicalBlock(scope: !142, file: !1, line: 473, column: 8)
!1007 = !DILocation(line: 473, column: 13, scope: !1006)
!1008 = !DILocation(line: 473, column: 8, scope: !142)
!1009 = !DILocation(line: 473, column: 22, scope: !1010)
!1010 = !DILexicalBlockFile(scope: !1006, file: !1, discriminator: 1)
!1011 = !DILocation(line: 474, column: 8, scope: !142)
!1012 = !DILocation(line: 474, column: 14, scope: !142)
!1013 = !DILocation(line: 474, column: 6, scope: !142)
!1014 = !DILocation(line: 475, column: 8, scope: !1015)
!1015 = distinct !DILexicalBlock(scope: !142, file: !1, line: 475, column: 8)
!1016 = !DILocation(line: 475, column: 10, scope: !1015)
!1017 = !DILocation(line: 475, column: 8, scope: !142)
!1018 = !DILocation(line: 475, column: 19, scope: !1019)
!1019 = !DILexicalBlockFile(scope: !1015, file: !1, discriminator: 1)
!1020 = !DILocation(line: 476, column: 8, scope: !1021)
!1021 = distinct !DILexicalBlock(scope: !142, file: !1, line: 476, column: 8)
!1022 = !DILocation(line: 476, column: 11, scope: !1021)
!1023 = !DILocation(line: 476, column: 19, scope: !1021)
!1024 = !DILocation(line: 476, column: 16, scope: !1021)
!1025 = !DILocation(line: 476, column: 8, scope: !142)
!1026 = !DILocation(line: 476, column: 25, scope: !1027)
!1027 = !DILexicalBlockFile(scope: !1021, file: !1, discriminator: 1)
!1028 = !DILocation(line: 478, column: 8, scope: !1029)
!1029 = distinct !DILexicalBlock(scope: !142, file: !1, line: 478, column: 8)
!1030 = !DILocation(line: 478, column: 11, scope: !1029)
!1031 = !DILocation(line: 478, column: 16, scope: !1029)
!1032 = !DILocation(line: 478, column: 8, scope: !142)
!1033 = !DILocation(line: 478, column: 25, scope: !1034)
!1034 = !DILexicalBlockFile(scope: !1029, file: !1, discriminator: 1)
!1035 = !DILocation(line: 479, column: 8, scope: !1036)
!1036 = distinct !DILexicalBlock(scope: !142, file: !1, line: 479, column: 8)
!1037 = !DILocation(line: 479, column: 11, scope: !1036)
!1038 = !DILocation(line: 479, column: 16, scope: !1036)
!1039 = !DILocation(line: 479, column: 8, scope: !142)
!1040 = !DILocation(line: 479, column: 25, scope: !1041)
!1041 = !DILexicalBlockFile(scope: !1036, file: !1, discriminator: 1)
!1042 = !DILocation(line: 480, column: 8, scope: !1043)
!1043 = distinct !DILexicalBlock(scope: !142, file: !1, line: 480, column: 8)
!1044 = !DILocation(line: 480, column: 11, scope: !1043)
!1045 = !DILocation(line: 480, column: 16, scope: !1043)
!1046 = !DILocation(line: 480, column: 8, scope: !142)
!1047 = !DILocation(line: 480, column: 25, scope: !1048)
!1048 = !DILexicalBlockFile(scope: !1043, file: !1, discriminator: 1)
!1049 = !DILocation(line: 481, column: 4, scope: !142)
!1050 = !DILocation(line: 483, column: 4, scope: !142)
!1051 = !DILocation(line: 483, column: 10, scope: !142)
!1052 = !DILocation(line: 483, column: 16, scope: !142)
!1053 = !DILocation(line: 485, column: 4, scope: !142)
!1054 = !DILocation(line: 486, column: 1, scope: !142)
!1055 = !DILocalVariable(name: "strm", arg: 1, scope: !145, file: !1, line: 495, type: !138)
!1056 = !DILocation(line: 495, column: 35, scope: !145)
!1057 = !DILocalVariable(name: "verbosity", arg: 2, scope: !145, file: !1, line: 496, type: !43)
!1058 = !DILocation(line: 496, column: 35, scope: !145)
!1059 = !DILocalVariable(name: "small", arg: 3, scope: !145, file: !1, line: 497, type: !43)
!1060 = !DILocation(line: 497, column: 35, scope: !145)
!1061 = !DILocalVariable(name: "s", scope: !145, file: !1, line: 499, type: !297)
!1062 = !DILocation(line: 499, column: 12, scope: !145)
!1063 = !DILocation(line: 501, column: 9, scope: !1064)
!1064 = distinct !DILexicalBlock(scope: !145, file: !1, line: 501, column: 8)
!1065 = !DILocation(line: 501, column: 8, scope: !145)
!1066 = !DILocation(line: 501, column: 25, scope: !1067)
!1067 = !DILexicalBlockFile(scope: !1064, file: !1, discriminator: 1)
!1068 = !DILocation(line: 503, column: 8, scope: !1069)
!1069 = distinct !DILexicalBlock(scope: !145, file: !1, line: 503, column: 8)
!1070 = !DILocation(line: 503, column: 13, scope: !1069)
!1071 = !DILocation(line: 503, column: 8, scope: !145)
!1072 = !DILocation(line: 503, column: 22, scope: !1073)
!1073 = !DILexicalBlockFile(scope: !1069, file: !1, discriminator: 1)
!1074 = !DILocation(line: 504, column: 8, scope: !1075)
!1075 = distinct !DILexicalBlock(scope: !145, file: !1, line: 504, column: 8)
!1076 = !DILocation(line: 504, column: 14, scope: !1075)
!1077 = !DILocation(line: 504, column: 19, scope: !1075)
!1078 = !DILocation(line: 504, column: 22, scope: !1079)
!1079 = !DILexicalBlockFile(scope: !1075, file: !1, discriminator: 1)
!1080 = !DILocation(line: 504, column: 28, scope: !1079)
!1081 = !DILocation(line: 504, column: 8, scope: !1079)
!1082 = !DILocation(line: 504, column: 34, scope: !1083)
!1083 = !DILexicalBlockFile(scope: !1075, file: !1, discriminator: 2)
!1084 = !DILocation(line: 505, column: 8, scope: !1085)
!1085 = distinct !DILexicalBlock(scope: !145, file: !1, line: 505, column: 8)
!1086 = !DILocation(line: 505, column: 18, scope: !1085)
!1087 = !DILocation(line: 505, column: 22, scope: !1085)
!1088 = !DILocation(line: 505, column: 25, scope: !1089)
!1089 = !DILexicalBlockFile(scope: !1085, file: !1, discriminator: 1)
!1090 = !DILocation(line: 505, column: 35, scope: !1089)
!1091 = !DILocation(line: 505, column: 8, scope: !1089)
!1092 = !DILocation(line: 505, column: 40, scope: !1093)
!1093 = !DILexicalBlockFile(scope: !1085, file: !1, discriminator: 2)
!1094 = !DILocation(line: 507, column: 8, scope: !1095)
!1095 = distinct !DILexicalBlock(scope: !145, file: !1, line: 507, column: 8)
!1096 = !DILocation(line: 507, column: 14, scope: !1095)
!1097 = !DILocation(line: 507, column: 22, scope: !1095)
!1098 = !DILocation(line: 507, column: 8, scope: !145)
!1099 = !DILocation(line: 507, column: 31, scope: !1100)
!1100 = !DILexicalBlockFile(scope: !1095, file: !1, discriminator: 1)
!1101 = !DILocation(line: 507, column: 37, scope: !1100)
!1102 = !DILocation(line: 507, column: 45, scope: !1100)
!1103 = !DILocation(line: 508, column: 8, scope: !1104)
!1104 = distinct !DILexicalBlock(scope: !145, file: !1, line: 508, column: 8)
!1105 = !DILocation(line: 508, column: 14, scope: !1104)
!1106 = !DILocation(line: 508, column: 21, scope: !1104)
!1107 = !DILocation(line: 508, column: 8, scope: !145)
!1108 = !DILocation(line: 508, column: 30, scope: !1109)
!1109 = !DILexicalBlockFile(scope: !1104, file: !1, discriminator: 1)
!1110 = !DILocation(line: 508, column: 36, scope: !1109)
!1111 = !DILocation(line: 508, column: 43, scope: !1109)
!1112 = !DILocation(line: 510, column: 8, scope: !145)
!1113 = !DILocation(line: 510, column: 6, scope: !145)
!1114 = !DILocation(line: 511, column: 8, scope: !1115)
!1115 = distinct !DILexicalBlock(scope: !145, file: !1, line: 511, column: 8)
!1116 = !DILocation(line: 511, column: 10, scope: !1115)
!1117 = !DILocation(line: 511, column: 8, scope: !145)
!1118 = !DILocation(line: 511, column: 19, scope: !1119)
!1119 = !DILexicalBlockFile(scope: !1115, file: !1, discriminator: 1)
!1120 = !DILocation(line: 512, column: 31, scope: !145)
!1121 = !DILocation(line: 512, column: 4, scope: !145)
!1122 = !DILocation(line: 512, column: 7, scope: !145)
!1123 = !DILocation(line: 512, column: 29, scope: !145)
!1124 = !DILocation(line: 513, column: 31, scope: !145)
!1125 = !DILocation(line: 513, column: 4, scope: !145)
!1126 = !DILocation(line: 513, column: 10, scope: !145)
!1127 = !DILocation(line: 513, column: 29, scope: !145)
!1128 = !DILocation(line: 514, column: 4, scope: !145)
!1129 = !DILocation(line: 514, column: 7, scope: !145)
!1130 = !DILocation(line: 514, column: 29, scope: !145)
!1131 = !DILocation(line: 515, column: 4, scope: !145)
!1132 = !DILocation(line: 515, column: 7, scope: !145)
!1133 = !DILocation(line: 515, column: 29, scope: !145)
!1134 = !DILocation(line: 516, column: 4, scope: !145)
!1135 = !DILocation(line: 516, column: 7, scope: !145)
!1136 = !DILocation(line: 516, column: 29, scope: !145)
!1137 = !DILocation(line: 517, column: 4, scope: !145)
!1138 = !DILocation(line: 517, column: 7, scope: !145)
!1139 = !DILocation(line: 517, column: 29, scope: !145)
!1140 = !DILocation(line: 518, column: 4, scope: !145)
!1141 = !DILocation(line: 518, column: 10, scope: !145)
!1142 = !DILocation(line: 518, column: 29, scope: !145)
!1143 = !DILocation(line: 519, column: 4, scope: !145)
!1144 = !DILocation(line: 519, column: 10, scope: !145)
!1145 = !DILocation(line: 519, column: 29, scope: !145)
!1146 = !DILocation(line: 520, column: 4, scope: !145)
!1147 = !DILocation(line: 520, column: 10, scope: !145)
!1148 = !DILocation(line: 520, column: 29, scope: !145)
!1149 = !DILocation(line: 521, column: 4, scope: !145)
!1150 = !DILocation(line: 521, column: 10, scope: !145)
!1151 = !DILocation(line: 521, column: 29, scope: !145)
!1152 = !DILocation(line: 522, column: 37, scope: !145)
!1153 = !DILocation(line: 522, column: 31, scope: !145)
!1154 = !DILocation(line: 522, column: 4, scope: !145)
!1155 = !DILocation(line: 522, column: 7, scope: !145)
!1156 = !DILocation(line: 522, column: 29, scope: !145)
!1157 = !DILocation(line: 523, column: 4, scope: !145)
!1158 = !DILocation(line: 523, column: 7, scope: !145)
!1159 = !DILocation(line: 523, column: 29, scope: !145)
!1160 = !DILocation(line: 524, column: 4, scope: !145)
!1161 = !DILocation(line: 524, column: 7, scope: !145)
!1162 = !DILocation(line: 524, column: 29, scope: !145)
!1163 = !DILocation(line: 525, column: 4, scope: !145)
!1164 = !DILocation(line: 525, column: 7, scope: !145)
!1165 = !DILocation(line: 525, column: 29, scope: !145)
!1166 = !DILocation(line: 526, column: 4, scope: !145)
!1167 = !DILocation(line: 526, column: 7, scope: !145)
!1168 = !DILocation(line: 526, column: 29, scope: !145)
!1169 = !DILocation(line: 527, column: 31, scope: !145)
!1170 = !DILocation(line: 527, column: 4, scope: !145)
!1171 = !DILocation(line: 527, column: 7, scope: !145)
!1172 = !DILocation(line: 527, column: 29, scope: !145)
!1173 = !DILocation(line: 529, column: 4, scope: !145)
!1174 = !DILocation(line: 530, column: 1, scope: !145)
!1175 = !DILocalVariable(name: "indx", arg: 1, scope: !148, file: !1, line: 689, type: !103)
!1176 = !DILocation(line: 689, column: 41, scope: !148)
!1177 = !DILocalVariable(name: "cftab", arg: 2, scope: !148, file: !1, line: 689, type: !151)
!1178 = !DILocation(line: 689, column: 54, scope: !148)
!1179 = !DILocalVariable(name: "nb", scope: !148, file: !1, line: 691, type: !103)
!1180 = !DILocation(line: 691, column: 10, scope: !148)
!1181 = !DILocalVariable(name: "na", scope: !148, file: !1, line: 691, type: !103)
!1182 = !DILocation(line: 691, column: 14, scope: !148)
!1183 = !DILocalVariable(name: "mid", scope: !148, file: !1, line: 691, type: !103)
!1184 = !DILocation(line: 691, column: 18, scope: !148)
!1185 = !DILocation(line: 692, column: 7, scope: !148)
!1186 = !DILocation(line: 693, column: 7, scope: !148)
!1187 = !DILocation(line: 694, column: 4, scope: !148)
!1188 = !DILocation(line: 695, column: 14, scope: !1189)
!1189 = distinct !DILexicalBlock(scope: !148, file: !1, line: 694, column: 7)
!1190 = !DILocation(line: 695, column: 19, scope: !1189)
!1191 = !DILocation(line: 695, column: 17, scope: !1189)
!1192 = !DILocation(line: 695, column: 23, scope: !1189)
!1193 = !DILocation(line: 695, column: 11, scope: !1189)
!1194 = !DILocation(line: 696, column: 11, scope: !1195)
!1195 = distinct !DILexicalBlock(scope: !1189, file: !1, line: 696, column: 11)
!1196 = !DILocation(line: 696, column: 25, scope: !1195)
!1197 = !DILocation(line: 696, column: 19, scope: !1195)
!1198 = !DILocation(line: 696, column: 16, scope: !1195)
!1199 = !DILocation(line: 696, column: 11, scope: !1189)
!1200 = !DILocation(line: 696, column: 36, scope: !1201)
!1201 = !DILexicalBlockFile(scope: !1195, file: !1, discriminator: 1)
!1202 = !DILocation(line: 696, column: 34, scope: !1201)
!1203 = !DILocation(line: 696, column: 31, scope: !1201)
!1204 = !DILocation(line: 696, column: 51, scope: !1205)
!1205 = !DILexicalBlockFile(scope: !1195, file: !1, discriminator: 2)
!1206 = !DILocation(line: 696, column: 49, scope: !1205)
!1207 = !DILocation(line: 697, column: 4, scope: !1189)
!1208 = !DILocation(line: 698, column: 11, scope: !148)
!1209 = !DILocation(line: 698, column: 16, scope: !148)
!1210 = !DILocation(line: 698, column: 14, scope: !148)
!1211 = !DILocation(line: 698, column: 19, scope: !148)
!1212 = !DILocation(line: 697, column: 4, scope: !1213)
!1213 = !DILexicalBlockFile(scope: !1189, file: !1, discriminator: 1)
!1214 = !DILocation(line: 699, column: 11, scope: !148)
!1215 = !DILocation(line: 699, column: 4, scope: !148)
!1216 = !DILocalVariable(name: "strm", arg: 1, scope: !152, file: !1, line: 810, type: !138)
!1217 = !DILocation(line: 810, column: 43, scope: !152)
!1218 = !DILocalVariable(name: "corrupt", scope: !152, file: !1, line: 812, type: !30)
!1219 = !DILocation(line: 812, column: 12, scope: !152)
!1220 = !DILocalVariable(name: "s", scope: !152, file: !1, line: 813, type: !297)
!1221 = !DILocation(line: 813, column: 12, scope: !152)
!1222 = !DILocation(line: 814, column: 8, scope: !1223)
!1223 = distinct !DILexicalBlock(scope: !152, file: !1, line: 814, column: 8)
!1224 = !DILocation(line: 814, column: 13, scope: !1223)
!1225 = !DILocation(line: 814, column: 8, scope: !152)
!1226 = !DILocation(line: 814, column: 22, scope: !1227)
!1227 = !DILexicalBlockFile(scope: !1223, file: !1, discriminator: 1)
!1228 = !DILocation(line: 815, column: 8, scope: !152)
!1229 = !DILocation(line: 815, column: 14, scope: !152)
!1230 = !DILocation(line: 815, column: 6, scope: !152)
!1231 = !DILocation(line: 816, column: 8, scope: !1232)
!1232 = distinct !DILexicalBlock(scope: !152, file: !1, line: 816, column: 8)
!1233 = !DILocation(line: 816, column: 10, scope: !1232)
!1234 = !DILocation(line: 816, column: 8, scope: !152)
!1235 = !DILocation(line: 816, column: 19, scope: !1236)
!1236 = !DILexicalBlockFile(scope: !1232, file: !1, discriminator: 1)
!1237 = !DILocation(line: 817, column: 8, scope: !1238)
!1238 = distinct !DILexicalBlock(scope: !152, file: !1, line: 817, column: 8)
!1239 = !DILocation(line: 817, column: 11, scope: !1238)
!1240 = !DILocation(line: 817, column: 19, scope: !1238)
!1241 = !DILocation(line: 817, column: 16, scope: !1238)
!1242 = !DILocation(line: 817, column: 8, scope: !152)
!1243 = !DILocation(line: 817, column: 25, scope: !1244)
!1244 = !DILexicalBlockFile(scope: !1238, file: !1, discriminator: 1)
!1245 = !DILocation(line: 819, column: 4, scope: !152)
!1246 = !DILocation(line: 820, column: 11, scope: !1247)
!1247 = distinct !DILexicalBlock(scope: !1248, file: !1, line: 820, column: 11)
!1248 = distinct !DILexicalBlock(scope: !152, file: !1, line: 819, column: 17)
!1249 = !DILocation(line: 820, column: 14, scope: !1247)
!1250 = !DILocation(line: 820, column: 20, scope: !1247)
!1251 = !DILocation(line: 820, column: 11, scope: !1248)
!1252 = !DILocation(line: 820, column: 34, scope: !1253)
!1253 = !DILexicalBlockFile(scope: !1247, file: !1, discriminator: 1)
!1254 = !DILocation(line: 821, column: 11, scope: !1255)
!1255 = distinct !DILexicalBlock(scope: !1248, file: !1, line: 821, column: 11)
!1256 = !DILocation(line: 821, column: 14, scope: !1255)
!1257 = !DILocation(line: 821, column: 20, scope: !1255)
!1258 = !DILocation(line: 821, column: 11, scope: !1248)
!1259 = !DILocation(line: 822, column: 14, scope: !1260)
!1260 = distinct !DILexicalBlock(scope: !1261, file: !1, line: 822, column: 14)
!1261 = distinct !DILexicalBlock(scope: !1255, file: !1, line: 821, column: 36)
!1262 = !DILocation(line: 822, column: 17, scope: !1260)
!1263 = !DILocation(line: 822, column: 14, scope: !1261)
!1264 = !DILocation(line: 823, column: 52, scope: !1260)
!1265 = !DILocation(line: 823, column: 23, scope: !1260)
!1266 = !DILocation(line: 823, column: 21, scope: !1260)
!1267 = !DILocation(line: 823, column: 13, scope: !1260)
!1268 = !DILocation(line: 824, column: 52, scope: !1260)
!1269 = !DILocation(line: 824, column: 23, scope: !1260)
!1270 = !DILocation(line: 824, column: 21, scope: !1260)
!1271 = !DILocation(line: 825, column: 14, scope: !1272)
!1272 = distinct !DILexicalBlock(scope: !1261, file: !1, line: 825, column: 14)
!1273 = !DILocation(line: 825, column: 14, scope: !1261)
!1274 = !DILocation(line: 825, column: 23, scope: !1275)
!1275 = !DILexicalBlockFile(scope: !1272, file: !1, discriminator: 1)
!1276 = !DILocation(line: 826, column: 14, scope: !1277)
!1277 = distinct !DILexicalBlock(scope: !1261, file: !1, line: 826, column: 14)
!1278 = !DILocation(line: 826, column: 17, scope: !1277)
!1279 = !DILocation(line: 826, column: 32, scope: !1277)
!1280 = !DILocation(line: 826, column: 35, scope: !1277)
!1281 = !DILocation(line: 826, column: 46, scope: !1277)
!1282 = !DILocation(line: 826, column: 29, scope: !1277)
!1283 = !DILocation(line: 826, column: 49, scope: !1277)
!1284 = !DILocation(line: 826, column: 52, scope: !1285)
!1285 = !DILexicalBlockFile(scope: !1277, file: !1, discriminator: 1)
!1286 = !DILocation(line: 826, column: 55, scope: !1285)
!1287 = !DILocation(line: 826, column: 69, scope: !1285)
!1288 = !DILocation(line: 826, column: 14, scope: !1285)
!1289 = !DILocation(line: 827, column: 13, scope: !1290)
!1290 = distinct !DILexicalBlock(scope: !1291, file: !1, line: 827, column: 13)
!1291 = distinct !DILexicalBlock(scope: !1277, file: !1, line: 826, column: 75)
!1292 = !DILocation(line: 828, column: 17, scope: !1293)
!1293 = distinct !DILexicalBlock(scope: !1291, file: !1, line: 828, column: 17)
!1294 = !DILocation(line: 828, column: 20, scope: !1293)
!1295 = !DILocation(line: 828, column: 30, scope: !1293)
!1296 = !DILocation(line: 828, column: 17, scope: !1291)
!1297 = !DILocation(line: 829, column: 16, scope: !1293)
!1298 = !DILocation(line: 831, column: 17, scope: !1299)
!1299 = distinct !DILexicalBlock(scope: !1291, file: !1, line: 831, column: 17)
!1300 = !DILocation(line: 831, column: 20, scope: !1299)
!1301 = !DILocation(line: 831, column: 30, scope: !1299)
!1302 = !DILocation(line: 831, column: 17, scope: !1291)
!1303 = !DILocation(line: 831, column: 36, scope: !1304)
!1304 = !DILexicalBlockFile(scope: !1299, file: !1, discriminator: 1)
!1305 = !DILocation(line: 832, column: 17, scope: !1306)
!1306 = distinct !DILexicalBlock(scope: !1291, file: !1, line: 832, column: 17)
!1307 = !DILocation(line: 832, column: 20, scope: !1306)
!1308 = !DILocation(line: 832, column: 42, scope: !1306)
!1309 = !DILocation(line: 832, column: 45, scope: !1306)
!1310 = !DILocation(line: 832, column: 39, scope: !1306)
!1311 = !DILocation(line: 832, column: 17, scope: !1291)
!1312 = !DILocation(line: 833, column: 16, scope: !1306)
!1313 = !DILocation(line: 835, column: 19, scope: !1291)
!1314 = !DILocation(line: 835, column: 22, scope: !1291)
!1315 = !DILocation(line: 835, column: 44, scope: !1291)
!1316 = !DILocation(line: 836, column: 22, scope: !1291)
!1317 = !DILocation(line: 836, column: 25, scope: !1291)
!1318 = !DILocation(line: 836, column: 47, scope: !1291)
!1319 = !DILocation(line: 835, column: 50, scope: !1291)
!1320 = !DILocation(line: 834, column: 13, scope: !1291)
!1321 = !DILocation(line: 834, column: 16, scope: !1291)
!1322 = !DILocation(line: 835, column: 16, scope: !1291)
!1323 = !DILocation(line: 837, column: 41, scope: !1291)
!1324 = !DILocation(line: 837, column: 44, scope: !1291)
!1325 = !DILocation(line: 837, column: 13, scope: !1291)
!1326 = !DILocation(line: 837, column: 16, scope: !1291)
!1327 = !DILocation(line: 837, column: 38, scope: !1291)
!1328 = !DILocation(line: 838, column: 13, scope: !1291)
!1329 = !DILocation(line: 838, column: 16, scope: !1291)
!1330 = !DILocation(line: 838, column: 22, scope: !1291)
!1331 = !DILocation(line: 839, column: 10, scope: !1291)
!1332 = !DILocation(line: 840, column: 13, scope: !1333)
!1333 = distinct !DILexicalBlock(scope: !1277, file: !1, line: 839, column: 17)
!1334 = !DILocation(line: 842, column: 7, scope: !1261)
!1335 = !DILocation(line: 843, column: 11, scope: !1336)
!1336 = distinct !DILexicalBlock(scope: !1248, file: !1, line: 843, column: 11)
!1337 = !DILocation(line: 843, column: 14, scope: !1336)
!1338 = !DILocation(line: 843, column: 20, scope: !1336)
!1339 = !DILocation(line: 843, column: 11, scope: !1248)
!1340 = !DILocalVariable(name: "r", scope: !1341, file: !1, line: 844, type: !103)
!1341 = distinct !DILexicalBlock(scope: !1336, file: !1, line: 843, column: 37)
!1342 = !DILocation(line: 844, column: 16, scope: !1341)
!1343 = !DILocation(line: 844, column: 37, scope: !1341)
!1344 = !DILocation(line: 844, column: 20, scope: !1341)
!1345 = !DILocation(line: 845, column: 14, scope: !1346)
!1346 = distinct !DILexicalBlock(scope: !1341, file: !1, line: 845, column: 14)
!1347 = !DILocation(line: 845, column: 16, scope: !1346)
!1348 = !DILocation(line: 845, column: 14, scope: !1341)
!1349 = !DILocation(line: 846, column: 17, scope: !1350)
!1350 = distinct !DILexicalBlock(scope: !1351, file: !1, line: 846, column: 17)
!1351 = distinct !DILexicalBlock(scope: !1346, file: !1, line: 845, column: 34)
!1352 = !DILocation(line: 846, column: 20, scope: !1350)
!1353 = !DILocation(line: 846, column: 30, scope: !1350)
!1354 = !DILocation(line: 846, column: 17, scope: !1351)
!1355 = !DILocation(line: 847, column: 16, scope: !1350)
!1356 = !DILocation(line: 849, column: 17, scope: !1357)
!1357 = distinct !DILexicalBlock(scope: !1351, file: !1, line: 849, column: 17)
!1358 = !DILocation(line: 849, column: 20, scope: !1357)
!1359 = !DILocation(line: 849, column: 45, scope: !1357)
!1360 = !DILocation(line: 849, column: 48, scope: !1357)
!1361 = !DILocation(line: 849, column: 42, scope: !1357)
!1362 = !DILocation(line: 849, column: 17, scope: !1351)
!1363 = !DILocation(line: 850, column: 16, scope: !1357)
!1364 = !DILocation(line: 851, column: 20, scope: !1351)
!1365 = !DILocation(line: 851, column: 13, scope: !1351)
!1366 = !DILocation(line: 853, column: 14, scope: !1367)
!1367 = distinct !DILexicalBlock(scope: !1341, file: !1, line: 853, column: 14)
!1368 = !DILocation(line: 853, column: 17, scope: !1367)
!1369 = !DILocation(line: 853, column: 23, scope: !1367)
!1370 = !DILocation(line: 853, column: 14, scope: !1341)
!1371 = !DILocation(line: 853, column: 46, scope: !1372)
!1372 = !DILexicalBlockFile(scope: !1367, file: !1, discriminator: 1)
!1373 = !DILocation(line: 853, column: 39, scope: !1372)
!1374 = !DILocation(line: 854, column: 7, scope: !1341)
!1375 = !DILocation(line: 819, column: 4, scope: !1376)
!1376 = !DILexicalBlockFile(scope: !152, file: !1, discriminator: 1)
!1377 = !DILocation(line: 860, column: 1, scope: !152)
!1378 = !DILocalVariable(name: "s", arg: 1, scope: !294, file: !1, line: 708, type: !297)
!1379 = !DILocation(line: 708, column: 43, scope: !294)
!1380 = !DILocalVariable(name: "k1", scope: !294, file: !1, line: 710, type: !21)
!1381 = !DILocation(line: 710, column: 10, scope: !294)
!1382 = !DILocation(line: 712, column: 8, scope: !1383)
!1383 = distinct !DILexicalBlock(scope: !294, file: !1, line: 712, column: 8)
!1384 = !DILocation(line: 712, column: 11, scope: !1383)
!1385 = !DILocation(line: 712, column: 8, scope: !294)
!1386 = !DILocation(line: 714, column: 7, scope: !1387)
!1387 = distinct !DILexicalBlock(scope: !1383, file: !1, line: 712, column: 28)
!1388 = !DILocation(line: 716, column: 10, scope: !1389)
!1389 = distinct !DILexicalBlock(scope: !1387, file: !1, line: 714, column: 20)
!1390 = !DILocation(line: 717, column: 17, scope: !1391)
!1391 = distinct !DILexicalBlock(scope: !1392, file: !1, line: 717, column: 17)
!1392 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 716, column: 23)
!1393 = !DILocation(line: 717, column: 20, scope: !1391)
!1394 = !DILocation(line: 717, column: 26, scope: !1391)
!1395 = !DILocation(line: 717, column: 36, scope: !1391)
!1396 = !DILocation(line: 717, column: 17, scope: !1392)
!1397 = !DILocation(line: 717, column: 42, scope: !1398)
!1398 = !DILexicalBlockFile(scope: !1391, file: !1, discriminator: 1)
!1399 = !DILocation(line: 718, column: 17, scope: !1400)
!1400 = distinct !DILexicalBlock(scope: !1392, file: !1, line: 718, column: 17)
!1401 = !DILocation(line: 718, column: 20, scope: !1400)
!1402 = !DILocation(line: 718, column: 34, scope: !1400)
!1403 = !DILocation(line: 718, column: 17, scope: !1392)
!1404 = !DILocation(line: 718, column: 40, scope: !1405)
!1405 = !DILexicalBlockFile(scope: !1400, file: !1, discriminator: 1)
!1406 = !DILocation(line: 719, column: 48, scope: !1392)
!1407 = !DILocation(line: 719, column: 51, scope: !1392)
!1408 = !DILocation(line: 719, column: 25, scope: !1392)
!1409 = !DILocation(line: 719, column: 28, scope: !1392)
!1410 = !DILocation(line: 719, column: 34, scope: !1392)
!1411 = !DILocation(line: 719, column: 46, scope: !1392)
!1412 = !DILocation(line: 720, column: 13, scope: !1413)
!1413 = distinct !DILexicalBlock(scope: !1392, file: !1, line: 720, column: 13)
!1414 = !DILocation(line: 721, column: 13, scope: !1392)
!1415 = !DILocation(line: 721, column: 16, scope: !1392)
!1416 = !DILocation(line: 721, column: 29, scope: !1392)
!1417 = !DILocation(line: 722, column: 13, scope: !1392)
!1418 = !DILocation(line: 722, column: 16, scope: !1392)
!1419 = !DILocation(line: 722, column: 22, scope: !1392)
!1420 = !DILocation(line: 722, column: 30, scope: !1392)
!1421 = !DILocation(line: 723, column: 13, scope: !1392)
!1422 = !DILocation(line: 723, column: 16, scope: !1392)
!1423 = !DILocation(line: 723, column: 22, scope: !1392)
!1424 = !DILocation(line: 723, column: 31, scope: !1392)
!1425 = !DILocation(line: 724, column: 13, scope: !1392)
!1426 = !DILocation(line: 724, column: 16, scope: !1392)
!1427 = !DILocation(line: 724, column: 22, scope: !1392)
!1428 = !DILocation(line: 724, column: 36, scope: !1392)
!1429 = !DILocation(line: 725, column: 17, scope: !1430)
!1430 = distinct !DILexicalBlock(scope: !1392, file: !1, line: 725, column: 17)
!1431 = !DILocation(line: 725, column: 20, scope: !1430)
!1432 = !DILocation(line: 725, column: 26, scope: !1430)
!1433 = !DILocation(line: 725, column: 41, scope: !1430)
!1434 = !DILocation(line: 725, column: 17, scope: !1392)
!1435 = !DILocation(line: 725, column: 47, scope: !1436)
!1436 = !DILexicalBlockFile(scope: !1430, file: !1, discriminator: 1)
!1437 = !DILocation(line: 725, column: 50, scope: !1436)
!1438 = !DILocation(line: 725, column: 56, scope: !1436)
!1439 = !DILocation(line: 725, column: 70, scope: !1436)
!1440 = !DILocation(line: 716, column: 10, scope: !1441)
!1441 = !DILexicalBlockFile(scope: !1389, file: !1, discriminator: 1)
!1442 = !DILocation(line: 729, column: 14, scope: !1443)
!1443 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 729, column: 14)
!1444 = !DILocation(line: 729, column: 17, scope: !1443)
!1445 = !DILocation(line: 729, column: 32, scope: !1443)
!1446 = !DILocation(line: 729, column: 35, scope: !1443)
!1447 = !DILocation(line: 729, column: 46, scope: !1443)
!1448 = !DILocation(line: 729, column: 29, scope: !1443)
!1449 = !DILocation(line: 729, column: 14, scope: !1389)
!1450 = !DILocation(line: 729, column: 50, scope: !1451)
!1451 = !DILexicalBlockFile(scope: !1443, file: !1, discriminator: 1)
!1452 = !DILocation(line: 732, column: 14, scope: !1453)
!1453 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 732, column: 14)
!1454 = !DILocation(line: 732, column: 17, scope: !1453)
!1455 = !DILocation(line: 732, column: 31, scope: !1453)
!1456 = !DILocation(line: 732, column: 34, scope: !1453)
!1457 = !DILocation(line: 732, column: 45, scope: !1453)
!1458 = !DILocation(line: 732, column: 29, scope: !1453)
!1459 = !DILocation(line: 732, column: 14, scope: !1389)
!1460 = !DILocation(line: 733, column: 13, scope: !1453)
!1461 = !DILocation(line: 735, column: 10, scope: !1389)
!1462 = !DILocation(line: 735, column: 13, scope: !1389)
!1463 = !DILocation(line: 735, column: 27, scope: !1389)
!1464 = !DILocation(line: 736, column: 28, scope: !1389)
!1465 = !DILocation(line: 736, column: 31, scope: !1389)
!1466 = !DILocation(line: 736, column: 10, scope: !1389)
!1467 = !DILocation(line: 736, column: 13, scope: !1389)
!1468 = !DILocation(line: 736, column: 26, scope: !1389)
!1469 = !DILocation(line: 737, column: 10, scope: !1470)
!1470 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 737, column: 10)
!1471 = !DILocation(line: 737, column: 10, scope: !1389)
!1472 = !DILocation(line: 737, column: 10, scope: !1473)
!1473 = !DILexicalBlockFile(scope: !1470, file: !1, discriminator: 1)
!1474 = !DILocation(line: 737, column: 10, scope: !1475)
!1475 = !DILexicalBlockFile(scope: !1389, file: !1, discriminator: 2)
!1476 = !DILocation(line: 737, column: 28, scope: !1475)
!1477 = !DILocation(line: 737, column: 28, scope: !1478)
!1478 = !DILexicalBlockFile(scope: !1479, file: !1, discriminator: 3)
!1479 = distinct !DILexicalBlock(scope: !1480, file: !1, line: 737, column: 28)
!1480 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 737, column: 28)
!1481 = !DILocation(line: 737, column: 28, scope: !1482)
!1482 = !DILexicalBlockFile(scope: !1483, file: !1, discriminator: 4)
!1483 = distinct !DILexicalBlock(scope: !1479, file: !1, line: 737, column: 28)
!1484 = !DILocation(line: 737, column: 28, scope: !1485)
!1485 = !DILexicalBlockFile(scope: !1479, file: !1, discriminator: 5)
!1486 = !DILocation(line: 737, column: 28, scope: !1487)
!1487 = !DILexicalBlockFile(scope: !1389, file: !1, discriminator: 6)
!1488 = !DILocation(line: 738, column: 16, scope: !1389)
!1489 = !DILocation(line: 738, column: 13, scope: !1389)
!1490 = !DILocation(line: 738, column: 30, scope: !1389)
!1491 = !DILocation(line: 738, column: 33, scope: !1389)
!1492 = !DILocation(line: 738, column: 44, scope: !1389)
!1493 = !DILocation(line: 739, column: 14, scope: !1494)
!1494 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 739, column: 14)
!1495 = !DILocation(line: 739, column: 17, scope: !1494)
!1496 = !DILocation(line: 739, column: 32, scope: !1494)
!1497 = !DILocation(line: 739, column: 35, scope: !1494)
!1498 = !DILocation(line: 739, column: 46, scope: !1494)
!1499 = !DILocation(line: 739, column: 29, scope: !1494)
!1500 = !DILocation(line: 739, column: 14, scope: !1389)
!1501 = !DILocation(line: 739, column: 50, scope: !1502)
!1502 = !DILexicalBlockFile(scope: !1494, file: !1, discriminator: 1)
!1503 = !DILocation(line: 740, column: 14, scope: !1504)
!1504 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 740, column: 14)
!1505 = !DILocation(line: 740, column: 20, scope: !1504)
!1506 = !DILocation(line: 740, column: 23, scope: !1504)
!1507 = !DILocation(line: 740, column: 17, scope: !1504)
!1508 = !DILocation(line: 740, column: 14, scope: !1389)
!1509 = !DILocation(line: 740, column: 37, scope: !1510)
!1510 = !DILexicalBlockFile(scope: !1511, file: !1, discriminator: 1)
!1511 = distinct !DILexicalBlock(scope: !1504, file: !1, line: 740, column: 27)
!1512 = !DILocation(line: 740, column: 29, scope: !1510)
!1513 = !DILocation(line: 740, column: 32, scope: !1510)
!1514 = !DILocation(line: 740, column: 35, scope: !1510)
!1515 = !DILocation(line: 740, column: 41, scope: !1510)
!1516 = !DILocation(line: 742, column: 10, scope: !1389)
!1517 = !DILocation(line: 742, column: 13, scope: !1389)
!1518 = !DILocation(line: 742, column: 27, scope: !1389)
!1519 = !DILocation(line: 743, column: 10, scope: !1520)
!1520 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 743, column: 10)
!1521 = !DILocation(line: 743, column: 10, scope: !1389)
!1522 = !DILocation(line: 743, column: 10, scope: !1523)
!1523 = !DILexicalBlockFile(scope: !1520, file: !1, discriminator: 1)
!1524 = !DILocation(line: 743, column: 10, scope: !1475)
!1525 = !DILocation(line: 743, column: 28, scope: !1475)
!1526 = !DILocation(line: 743, column: 28, scope: !1527)
!1527 = !DILexicalBlockFile(scope: !1528, file: !1, discriminator: 3)
!1528 = distinct !DILexicalBlock(scope: !1529, file: !1, line: 743, column: 28)
!1529 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 743, column: 28)
!1530 = !DILocation(line: 743, column: 28, scope: !1531)
!1531 = !DILexicalBlockFile(scope: !1532, file: !1, discriminator: 4)
!1532 = distinct !DILexicalBlock(scope: !1528, file: !1, line: 743, column: 28)
!1533 = !DILocation(line: 743, column: 28, scope: !1534)
!1534 = !DILexicalBlockFile(scope: !1528, file: !1, discriminator: 5)
!1535 = !DILocation(line: 743, column: 28, scope: !1487)
!1536 = !DILocation(line: 744, column: 16, scope: !1389)
!1537 = !DILocation(line: 744, column: 13, scope: !1389)
!1538 = !DILocation(line: 744, column: 30, scope: !1389)
!1539 = !DILocation(line: 744, column: 33, scope: !1389)
!1540 = !DILocation(line: 744, column: 44, scope: !1389)
!1541 = !DILocation(line: 745, column: 14, scope: !1542)
!1542 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 745, column: 14)
!1543 = !DILocation(line: 745, column: 17, scope: !1542)
!1544 = !DILocation(line: 745, column: 32, scope: !1542)
!1545 = !DILocation(line: 745, column: 35, scope: !1542)
!1546 = !DILocation(line: 745, column: 46, scope: !1542)
!1547 = !DILocation(line: 745, column: 29, scope: !1542)
!1548 = !DILocation(line: 745, column: 14, scope: !1389)
!1549 = !DILocation(line: 745, column: 50, scope: !1550)
!1550 = !DILexicalBlockFile(scope: !1542, file: !1, discriminator: 1)
!1551 = !DILocation(line: 746, column: 14, scope: !1552)
!1552 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 746, column: 14)
!1553 = !DILocation(line: 746, column: 20, scope: !1552)
!1554 = !DILocation(line: 746, column: 23, scope: !1552)
!1555 = !DILocation(line: 746, column: 17, scope: !1552)
!1556 = !DILocation(line: 746, column: 14, scope: !1389)
!1557 = !DILocation(line: 746, column: 37, scope: !1558)
!1558 = !DILexicalBlockFile(scope: !1559, file: !1, discriminator: 1)
!1559 = distinct !DILexicalBlock(scope: !1552, file: !1, line: 746, column: 27)
!1560 = !DILocation(line: 746, column: 29, scope: !1558)
!1561 = !DILocation(line: 746, column: 32, scope: !1558)
!1562 = !DILocation(line: 746, column: 35, scope: !1558)
!1563 = !DILocation(line: 746, column: 41, scope: !1558)
!1564 = !DILocation(line: 748, column: 10, scope: !1389)
!1565 = !DILocation(line: 748, column: 13, scope: !1389)
!1566 = !DILocation(line: 748, column: 27, scope: !1389)
!1567 = !DILocation(line: 749, column: 10, scope: !1568)
!1568 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 749, column: 10)
!1569 = !DILocation(line: 749, column: 10, scope: !1389)
!1570 = !DILocation(line: 749, column: 10, scope: !1571)
!1571 = !DILexicalBlockFile(scope: !1568, file: !1, discriminator: 1)
!1572 = !DILocation(line: 749, column: 10, scope: !1475)
!1573 = !DILocation(line: 749, column: 28, scope: !1475)
!1574 = !DILocation(line: 749, column: 28, scope: !1575)
!1575 = !DILexicalBlockFile(scope: !1576, file: !1, discriminator: 3)
!1576 = distinct !DILexicalBlock(scope: !1577, file: !1, line: 749, column: 28)
!1577 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 749, column: 28)
!1578 = !DILocation(line: 749, column: 28, scope: !1579)
!1579 = !DILexicalBlockFile(scope: !1580, file: !1, discriminator: 4)
!1580 = distinct !DILexicalBlock(scope: !1576, file: !1, line: 749, column: 28)
!1581 = !DILocation(line: 749, column: 28, scope: !1582)
!1582 = !DILexicalBlockFile(scope: !1576, file: !1, discriminator: 5)
!1583 = !DILocation(line: 749, column: 28, scope: !1487)
!1584 = !DILocation(line: 750, column: 16, scope: !1389)
!1585 = !DILocation(line: 750, column: 13, scope: !1389)
!1586 = !DILocation(line: 750, column: 30, scope: !1389)
!1587 = !DILocation(line: 750, column: 33, scope: !1389)
!1588 = !DILocation(line: 750, column: 44, scope: !1389)
!1589 = !DILocation(line: 751, column: 14, scope: !1590)
!1590 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 751, column: 14)
!1591 = !DILocation(line: 751, column: 17, scope: !1590)
!1592 = !DILocation(line: 751, column: 32, scope: !1590)
!1593 = !DILocation(line: 751, column: 35, scope: !1590)
!1594 = !DILocation(line: 751, column: 46, scope: !1590)
!1595 = !DILocation(line: 751, column: 29, scope: !1590)
!1596 = !DILocation(line: 751, column: 14, scope: !1389)
!1597 = !DILocation(line: 751, column: 50, scope: !1598)
!1598 = !DILexicalBlockFile(scope: !1590, file: !1, discriminator: 1)
!1599 = !DILocation(line: 752, column: 14, scope: !1600)
!1600 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 752, column: 14)
!1601 = !DILocation(line: 752, column: 20, scope: !1600)
!1602 = !DILocation(line: 752, column: 23, scope: !1600)
!1603 = !DILocation(line: 752, column: 17, scope: !1600)
!1604 = !DILocation(line: 752, column: 14, scope: !1389)
!1605 = !DILocation(line: 752, column: 37, scope: !1606)
!1606 = !DILexicalBlockFile(scope: !1607, file: !1, discriminator: 1)
!1607 = distinct !DILexicalBlock(scope: !1600, file: !1, line: 752, column: 27)
!1608 = !DILocation(line: 752, column: 29, scope: !1606)
!1609 = !DILocation(line: 752, column: 32, scope: !1606)
!1610 = !DILocation(line: 752, column: 35, scope: !1606)
!1611 = !DILocation(line: 752, column: 41, scope: !1606)
!1612 = !DILocation(line: 754, column: 10, scope: !1613)
!1613 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 754, column: 10)
!1614 = !DILocation(line: 754, column: 10, scope: !1389)
!1615 = !DILocation(line: 754, column: 10, scope: !1616)
!1616 = !DILexicalBlockFile(scope: !1613, file: !1, discriminator: 1)
!1617 = !DILocation(line: 754, column: 10, scope: !1475)
!1618 = !DILocation(line: 754, column: 28, scope: !1475)
!1619 = !DILocation(line: 754, column: 28, scope: !1620)
!1620 = !DILexicalBlockFile(scope: !1621, file: !1, discriminator: 3)
!1621 = distinct !DILexicalBlock(scope: !1622, file: !1, line: 754, column: 28)
!1622 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 754, column: 28)
!1623 = !DILocation(line: 754, column: 28, scope: !1624)
!1624 = !DILexicalBlockFile(scope: !1625, file: !1, discriminator: 4)
!1625 = distinct !DILexicalBlock(scope: !1621, file: !1, line: 754, column: 28)
!1626 = !DILocation(line: 754, column: 28, scope: !1627)
!1627 = !DILexicalBlockFile(scope: !1621, file: !1, discriminator: 5)
!1628 = !DILocation(line: 754, column: 28, scope: !1487)
!1629 = !DILocation(line: 755, column: 16, scope: !1389)
!1630 = !DILocation(line: 755, column: 13, scope: !1389)
!1631 = !DILocation(line: 755, column: 30, scope: !1389)
!1632 = !DILocation(line: 755, column: 33, scope: !1389)
!1633 = !DILocation(line: 755, column: 44, scope: !1389)
!1634 = !DILocation(line: 756, column: 37, scope: !1389)
!1635 = !DILocation(line: 756, column: 30, scope: !1389)
!1636 = !DILocation(line: 756, column: 41, scope: !1389)
!1637 = !DILocation(line: 756, column: 10, scope: !1389)
!1638 = !DILocation(line: 756, column: 13, scope: !1389)
!1639 = !DILocation(line: 756, column: 27, scope: !1389)
!1640 = !DILocation(line: 757, column: 10, scope: !1641)
!1641 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 757, column: 10)
!1642 = !DILocation(line: 757, column: 10, scope: !1389)
!1643 = !DILocation(line: 757, column: 10, scope: !1644)
!1644 = !DILexicalBlockFile(scope: !1641, file: !1, discriminator: 1)
!1645 = !DILocation(line: 757, column: 10, scope: !1475)
!1646 = !DILocation(line: 757, column: 31, scope: !1475)
!1647 = !DILocation(line: 757, column: 31, scope: !1648)
!1648 = !DILexicalBlockFile(scope: !1649, file: !1, discriminator: 3)
!1649 = distinct !DILexicalBlock(scope: !1650, file: !1, line: 757, column: 31)
!1650 = distinct !DILexicalBlock(scope: !1389, file: !1, line: 757, column: 31)
!1651 = !DILocation(line: 757, column: 31, scope: !1652)
!1652 = !DILexicalBlockFile(scope: !1653, file: !1, discriminator: 4)
!1653 = distinct !DILexicalBlock(scope: !1649, file: !1, line: 757, column: 31)
!1654 = !DILocation(line: 757, column: 31, scope: !1655)
!1655 = !DILexicalBlockFile(scope: !1649, file: !1, discriminator: 5)
!1656 = !DILocation(line: 757, column: 31, scope: !1487)
!1657 = !DILocation(line: 758, column: 19, scope: !1389)
!1658 = !DILocation(line: 758, column: 10, scope: !1389)
!1659 = !DILocation(line: 758, column: 13, scope: !1389)
!1660 = !DILocation(line: 758, column: 16, scope: !1389)
!1661 = !DILocation(line: 758, column: 33, scope: !1389)
!1662 = !DILocation(line: 758, column: 36, scope: !1389)
!1663 = !DILocation(line: 758, column: 47, scope: !1389)
!1664 = !DILocation(line: 714, column: 7, scope: !1665)
!1665 = !DILexicalBlockFile(scope: !1387, file: !1, discriminator: 1)
!1666 = !DILocation(line: 763, column: 7, scope: !1667)
!1667 = distinct !DILexicalBlock(scope: !1383, file: !1, line: 761, column: 11)
!1668 = !DILocation(line: 765, column: 10, scope: !1669)
!1669 = distinct !DILexicalBlock(scope: !1667, file: !1, line: 763, column: 20)
!1670 = !DILocation(line: 766, column: 17, scope: !1671)
!1671 = distinct !DILexicalBlock(scope: !1672, file: !1, line: 766, column: 17)
!1672 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 765, column: 23)
!1673 = !DILocation(line: 766, column: 20, scope: !1671)
!1674 = !DILocation(line: 766, column: 26, scope: !1671)
!1675 = !DILocation(line: 766, column: 36, scope: !1671)
!1676 = !DILocation(line: 766, column: 17, scope: !1672)
!1677 = !DILocation(line: 766, column: 42, scope: !1678)
!1678 = !DILexicalBlockFile(scope: !1671, file: !1, discriminator: 1)
!1679 = !DILocation(line: 767, column: 17, scope: !1680)
!1680 = distinct !DILexicalBlock(scope: !1672, file: !1, line: 767, column: 17)
!1681 = !DILocation(line: 767, column: 20, scope: !1680)
!1682 = !DILocation(line: 767, column: 34, scope: !1680)
!1683 = !DILocation(line: 767, column: 17, scope: !1672)
!1684 = !DILocation(line: 767, column: 40, scope: !1685)
!1685 = !DILexicalBlockFile(scope: !1680, file: !1, discriminator: 1)
!1686 = !DILocation(line: 768, column: 48, scope: !1672)
!1687 = !DILocation(line: 768, column: 51, scope: !1672)
!1688 = !DILocation(line: 768, column: 25, scope: !1672)
!1689 = !DILocation(line: 768, column: 28, scope: !1672)
!1690 = !DILocation(line: 768, column: 34, scope: !1672)
!1691 = !DILocation(line: 768, column: 46, scope: !1672)
!1692 = !DILocation(line: 769, column: 13, scope: !1693)
!1693 = distinct !DILexicalBlock(scope: !1672, file: !1, line: 769, column: 13)
!1694 = !DILocation(line: 770, column: 13, scope: !1672)
!1695 = !DILocation(line: 770, column: 16, scope: !1672)
!1696 = !DILocation(line: 770, column: 29, scope: !1672)
!1697 = !DILocation(line: 771, column: 13, scope: !1672)
!1698 = !DILocation(line: 771, column: 16, scope: !1672)
!1699 = !DILocation(line: 771, column: 22, scope: !1672)
!1700 = !DILocation(line: 771, column: 30, scope: !1672)
!1701 = !DILocation(line: 772, column: 13, scope: !1672)
!1702 = !DILocation(line: 772, column: 16, scope: !1672)
!1703 = !DILocation(line: 772, column: 22, scope: !1672)
!1704 = !DILocation(line: 772, column: 31, scope: !1672)
!1705 = !DILocation(line: 773, column: 13, scope: !1672)
!1706 = !DILocation(line: 773, column: 16, scope: !1672)
!1707 = !DILocation(line: 773, column: 22, scope: !1672)
!1708 = !DILocation(line: 773, column: 36, scope: !1672)
!1709 = !DILocation(line: 774, column: 17, scope: !1710)
!1710 = distinct !DILexicalBlock(scope: !1672, file: !1, line: 774, column: 17)
!1711 = !DILocation(line: 774, column: 20, scope: !1710)
!1712 = !DILocation(line: 774, column: 26, scope: !1710)
!1713 = !DILocation(line: 774, column: 41, scope: !1710)
!1714 = !DILocation(line: 774, column: 17, scope: !1672)
!1715 = !DILocation(line: 774, column: 47, scope: !1716)
!1716 = !DILexicalBlockFile(scope: !1710, file: !1, discriminator: 1)
!1717 = !DILocation(line: 774, column: 50, scope: !1716)
!1718 = !DILocation(line: 774, column: 56, scope: !1716)
!1719 = !DILocation(line: 774, column: 70, scope: !1716)
!1720 = !DILocation(line: 765, column: 10, scope: !1721)
!1721 = !DILexicalBlockFile(scope: !1669, file: !1, discriminator: 1)
!1722 = !DILocation(line: 778, column: 14, scope: !1723)
!1723 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 778, column: 14)
!1724 = !DILocation(line: 778, column: 17, scope: !1723)
!1725 = !DILocation(line: 778, column: 32, scope: !1723)
!1726 = !DILocation(line: 778, column: 35, scope: !1723)
!1727 = !DILocation(line: 778, column: 46, scope: !1723)
!1728 = !DILocation(line: 778, column: 29, scope: !1723)
!1729 = !DILocation(line: 778, column: 14, scope: !1669)
!1730 = !DILocation(line: 778, column: 50, scope: !1731)
!1731 = !DILexicalBlockFile(scope: !1723, file: !1, discriminator: 1)
!1732 = !DILocation(line: 781, column: 14, scope: !1733)
!1733 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 781, column: 14)
!1734 = !DILocation(line: 781, column: 17, scope: !1733)
!1735 = !DILocation(line: 781, column: 31, scope: !1733)
!1736 = !DILocation(line: 781, column: 34, scope: !1733)
!1737 = !DILocation(line: 781, column: 45, scope: !1733)
!1738 = !DILocation(line: 781, column: 29, scope: !1733)
!1739 = !DILocation(line: 781, column: 14, scope: !1669)
!1740 = !DILocation(line: 782, column: 13, scope: !1733)
!1741 = !DILocation(line: 784, column: 10, scope: !1669)
!1742 = !DILocation(line: 784, column: 13, scope: !1669)
!1743 = !DILocation(line: 784, column: 27, scope: !1669)
!1744 = !DILocation(line: 785, column: 28, scope: !1669)
!1745 = !DILocation(line: 785, column: 31, scope: !1669)
!1746 = !DILocation(line: 785, column: 10, scope: !1669)
!1747 = !DILocation(line: 785, column: 13, scope: !1669)
!1748 = !DILocation(line: 785, column: 26, scope: !1669)
!1749 = !DILocation(line: 786, column: 10, scope: !1750)
!1750 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 786, column: 10)
!1751 = !DILocation(line: 786, column: 10, scope: !1669)
!1752 = !DILocation(line: 786, column: 10, scope: !1753)
!1753 = !DILexicalBlockFile(scope: !1750, file: !1, discriminator: 1)
!1754 = !DILocation(line: 786, column: 10, scope: !1755)
!1755 = !DILexicalBlockFile(scope: !1669, file: !1, discriminator: 2)
!1756 = !DILocation(line: 786, column: 28, scope: !1755)
!1757 = !DILocation(line: 786, column: 31, scope: !1755)
!1758 = !DILocation(line: 786, column: 42, scope: !1755)
!1759 = !DILocation(line: 787, column: 14, scope: !1760)
!1760 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 787, column: 14)
!1761 = !DILocation(line: 787, column: 17, scope: !1760)
!1762 = !DILocation(line: 787, column: 32, scope: !1760)
!1763 = !DILocation(line: 787, column: 35, scope: !1760)
!1764 = !DILocation(line: 787, column: 46, scope: !1760)
!1765 = !DILocation(line: 787, column: 29, scope: !1760)
!1766 = !DILocation(line: 787, column: 14, scope: !1669)
!1767 = !DILocation(line: 787, column: 50, scope: !1768)
!1768 = !DILexicalBlockFile(scope: !1760, file: !1, discriminator: 1)
!1769 = !DILocation(line: 788, column: 14, scope: !1770)
!1770 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 788, column: 14)
!1771 = !DILocation(line: 788, column: 20, scope: !1770)
!1772 = !DILocation(line: 788, column: 23, scope: !1770)
!1773 = !DILocation(line: 788, column: 17, scope: !1770)
!1774 = !DILocation(line: 788, column: 14, scope: !1669)
!1775 = !DILocation(line: 788, column: 37, scope: !1776)
!1776 = !DILexicalBlockFile(scope: !1777, file: !1, discriminator: 1)
!1777 = distinct !DILexicalBlock(scope: !1770, file: !1, line: 788, column: 27)
!1778 = !DILocation(line: 788, column: 29, scope: !1776)
!1779 = !DILocation(line: 788, column: 32, scope: !1776)
!1780 = !DILocation(line: 788, column: 35, scope: !1776)
!1781 = !DILocation(line: 788, column: 41, scope: !1776)
!1782 = !DILocation(line: 790, column: 10, scope: !1669)
!1783 = !DILocation(line: 790, column: 13, scope: !1669)
!1784 = !DILocation(line: 790, column: 27, scope: !1669)
!1785 = !DILocation(line: 791, column: 10, scope: !1786)
!1786 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 791, column: 10)
!1787 = !DILocation(line: 791, column: 10, scope: !1669)
!1788 = !DILocation(line: 791, column: 10, scope: !1789)
!1789 = !DILexicalBlockFile(scope: !1786, file: !1, discriminator: 1)
!1790 = !DILocation(line: 791, column: 10, scope: !1755)
!1791 = !DILocation(line: 791, column: 28, scope: !1755)
!1792 = !DILocation(line: 791, column: 31, scope: !1755)
!1793 = !DILocation(line: 791, column: 42, scope: !1755)
!1794 = !DILocation(line: 792, column: 14, scope: !1795)
!1795 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 792, column: 14)
!1796 = !DILocation(line: 792, column: 17, scope: !1795)
!1797 = !DILocation(line: 792, column: 32, scope: !1795)
!1798 = !DILocation(line: 792, column: 35, scope: !1795)
!1799 = !DILocation(line: 792, column: 46, scope: !1795)
!1800 = !DILocation(line: 792, column: 29, scope: !1795)
!1801 = !DILocation(line: 792, column: 14, scope: !1669)
!1802 = !DILocation(line: 792, column: 50, scope: !1803)
!1803 = !DILexicalBlockFile(scope: !1795, file: !1, discriminator: 1)
!1804 = !DILocation(line: 793, column: 14, scope: !1805)
!1805 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 793, column: 14)
!1806 = !DILocation(line: 793, column: 20, scope: !1805)
!1807 = !DILocation(line: 793, column: 23, scope: !1805)
!1808 = !DILocation(line: 793, column: 17, scope: !1805)
!1809 = !DILocation(line: 793, column: 14, scope: !1669)
!1810 = !DILocation(line: 793, column: 37, scope: !1811)
!1811 = !DILexicalBlockFile(scope: !1812, file: !1, discriminator: 1)
!1812 = distinct !DILexicalBlock(scope: !1805, file: !1, line: 793, column: 27)
!1813 = !DILocation(line: 793, column: 29, scope: !1811)
!1814 = !DILocation(line: 793, column: 32, scope: !1811)
!1815 = !DILocation(line: 793, column: 35, scope: !1811)
!1816 = !DILocation(line: 793, column: 41, scope: !1811)
!1817 = !DILocation(line: 795, column: 10, scope: !1669)
!1818 = !DILocation(line: 795, column: 13, scope: !1669)
!1819 = !DILocation(line: 795, column: 27, scope: !1669)
!1820 = !DILocation(line: 796, column: 10, scope: !1821)
!1821 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 796, column: 10)
!1822 = !DILocation(line: 796, column: 10, scope: !1669)
!1823 = !DILocation(line: 796, column: 10, scope: !1824)
!1824 = !DILexicalBlockFile(scope: !1821, file: !1, discriminator: 1)
!1825 = !DILocation(line: 796, column: 10, scope: !1755)
!1826 = !DILocation(line: 796, column: 28, scope: !1755)
!1827 = !DILocation(line: 796, column: 31, scope: !1755)
!1828 = !DILocation(line: 796, column: 42, scope: !1755)
!1829 = !DILocation(line: 797, column: 14, scope: !1830)
!1830 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 797, column: 14)
!1831 = !DILocation(line: 797, column: 17, scope: !1830)
!1832 = !DILocation(line: 797, column: 32, scope: !1830)
!1833 = !DILocation(line: 797, column: 35, scope: !1830)
!1834 = !DILocation(line: 797, column: 46, scope: !1830)
!1835 = !DILocation(line: 797, column: 29, scope: !1830)
!1836 = !DILocation(line: 797, column: 14, scope: !1669)
!1837 = !DILocation(line: 797, column: 50, scope: !1838)
!1838 = !DILexicalBlockFile(scope: !1830, file: !1, discriminator: 1)
!1839 = !DILocation(line: 798, column: 14, scope: !1840)
!1840 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 798, column: 14)
!1841 = !DILocation(line: 798, column: 20, scope: !1840)
!1842 = !DILocation(line: 798, column: 23, scope: !1840)
!1843 = !DILocation(line: 798, column: 17, scope: !1840)
!1844 = !DILocation(line: 798, column: 14, scope: !1669)
!1845 = !DILocation(line: 798, column: 37, scope: !1846)
!1846 = !DILexicalBlockFile(scope: !1847, file: !1, discriminator: 1)
!1847 = distinct !DILexicalBlock(scope: !1840, file: !1, line: 798, column: 27)
!1848 = !DILocation(line: 798, column: 29, scope: !1846)
!1849 = !DILocation(line: 798, column: 32, scope: !1846)
!1850 = !DILocation(line: 798, column: 35, scope: !1846)
!1851 = !DILocation(line: 798, column: 41, scope: !1846)
!1852 = !DILocation(line: 800, column: 10, scope: !1853)
!1853 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 800, column: 10)
!1854 = !DILocation(line: 800, column: 10, scope: !1669)
!1855 = !DILocation(line: 800, column: 10, scope: !1856)
!1856 = !DILexicalBlockFile(scope: !1853, file: !1, discriminator: 1)
!1857 = !DILocation(line: 800, column: 10, scope: !1755)
!1858 = !DILocation(line: 800, column: 28, scope: !1755)
!1859 = !DILocation(line: 800, column: 31, scope: !1755)
!1860 = !DILocation(line: 800, column: 42, scope: !1755)
!1861 = !DILocation(line: 801, column: 37, scope: !1669)
!1862 = !DILocation(line: 801, column: 30, scope: !1669)
!1863 = !DILocation(line: 801, column: 41, scope: !1669)
!1864 = !DILocation(line: 801, column: 10, scope: !1669)
!1865 = !DILocation(line: 801, column: 13, scope: !1669)
!1866 = !DILocation(line: 801, column: 27, scope: !1669)
!1867 = !DILocation(line: 802, column: 10, scope: !1868)
!1868 = distinct !DILexicalBlock(scope: !1669, file: !1, line: 802, column: 10)
!1869 = !DILocation(line: 802, column: 10, scope: !1669)
!1870 = !DILocation(line: 802, column: 10, scope: !1871)
!1871 = !DILexicalBlockFile(scope: !1868, file: !1, discriminator: 1)
!1872 = !DILocation(line: 802, column: 10, scope: !1755)
!1873 = !DILocation(line: 802, column: 31, scope: !1755)
!1874 = !DILocation(line: 802, column: 34, scope: !1755)
!1875 = !DILocation(line: 802, column: 45, scope: !1755)
!1876 = !DILocation(line: 763, column: 7, scope: !1877)
!1877 = !DILexicalBlockFile(scope: !1667, file: !1, discriminator: 1)
!1878 = !DILocation(line: 806, column: 1, scope: !294)
!1879 = !DILocalVariable(name: "s", arg: 1, scope: !378, file: !1, line: 538, type: !297)
!1880 = !DILocation(line: 538, column: 42, scope: !378)
!1881 = !DILocalVariable(name: "k1", scope: !378, file: !1, line: 540, type: !21)
!1882 = !DILocation(line: 540, column: 10, scope: !378)
!1883 = !DILocation(line: 542, column: 8, scope: !1884)
!1884 = distinct !DILexicalBlock(scope: !378, file: !1, line: 542, column: 8)
!1885 = !DILocation(line: 542, column: 11, scope: !1884)
!1886 = !DILocation(line: 542, column: 8, scope: !378)
!1887 = !DILocation(line: 544, column: 7, scope: !1888)
!1888 = distinct !DILexicalBlock(scope: !1884, file: !1, line: 542, column: 28)
!1889 = !DILocation(line: 546, column: 10, scope: !1890)
!1890 = distinct !DILexicalBlock(scope: !1888, file: !1, line: 544, column: 20)
!1891 = !DILocation(line: 547, column: 17, scope: !1892)
!1892 = distinct !DILexicalBlock(scope: !1893, file: !1, line: 547, column: 17)
!1893 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 546, column: 23)
!1894 = !DILocation(line: 547, column: 20, scope: !1892)
!1895 = !DILocation(line: 547, column: 26, scope: !1892)
!1896 = !DILocation(line: 547, column: 36, scope: !1892)
!1897 = !DILocation(line: 547, column: 17, scope: !1893)
!1898 = !DILocation(line: 547, column: 42, scope: !1899)
!1899 = !DILexicalBlockFile(scope: !1892, file: !1, discriminator: 1)
!1900 = !DILocation(line: 548, column: 17, scope: !1901)
!1901 = distinct !DILexicalBlock(scope: !1893, file: !1, line: 548, column: 17)
!1902 = !DILocation(line: 548, column: 20, scope: !1901)
!1903 = !DILocation(line: 548, column: 34, scope: !1901)
!1904 = !DILocation(line: 548, column: 17, scope: !1893)
!1905 = !DILocation(line: 548, column: 40, scope: !1906)
!1906 = !DILexicalBlockFile(scope: !1901, file: !1, discriminator: 1)
!1907 = !DILocation(line: 549, column: 48, scope: !1893)
!1908 = !DILocation(line: 549, column: 51, scope: !1893)
!1909 = !DILocation(line: 549, column: 25, scope: !1893)
!1910 = !DILocation(line: 549, column: 28, scope: !1893)
!1911 = !DILocation(line: 549, column: 34, scope: !1893)
!1912 = !DILocation(line: 549, column: 46, scope: !1893)
!1913 = !DILocation(line: 550, column: 13, scope: !1914)
!1914 = distinct !DILexicalBlock(scope: !1893, file: !1, line: 550, column: 13)
!1915 = !DILocation(line: 551, column: 13, scope: !1893)
!1916 = !DILocation(line: 551, column: 16, scope: !1893)
!1917 = !DILocation(line: 551, column: 29, scope: !1893)
!1918 = !DILocation(line: 552, column: 13, scope: !1893)
!1919 = !DILocation(line: 552, column: 16, scope: !1893)
!1920 = !DILocation(line: 552, column: 22, scope: !1893)
!1921 = !DILocation(line: 552, column: 30, scope: !1893)
!1922 = !DILocation(line: 553, column: 13, scope: !1893)
!1923 = !DILocation(line: 553, column: 16, scope: !1893)
!1924 = !DILocation(line: 553, column: 22, scope: !1893)
!1925 = !DILocation(line: 553, column: 31, scope: !1893)
!1926 = !DILocation(line: 554, column: 13, scope: !1893)
!1927 = !DILocation(line: 554, column: 16, scope: !1893)
!1928 = !DILocation(line: 554, column: 22, scope: !1893)
!1929 = !DILocation(line: 554, column: 36, scope: !1893)
!1930 = !DILocation(line: 555, column: 17, scope: !1931)
!1931 = distinct !DILexicalBlock(scope: !1893, file: !1, line: 555, column: 17)
!1932 = !DILocation(line: 555, column: 20, scope: !1931)
!1933 = !DILocation(line: 555, column: 26, scope: !1931)
!1934 = !DILocation(line: 555, column: 41, scope: !1931)
!1935 = !DILocation(line: 555, column: 17, scope: !1893)
!1936 = !DILocation(line: 555, column: 47, scope: !1937)
!1937 = !DILexicalBlockFile(scope: !1931, file: !1, discriminator: 1)
!1938 = !DILocation(line: 555, column: 50, scope: !1937)
!1939 = !DILocation(line: 555, column: 56, scope: !1937)
!1940 = !DILocation(line: 555, column: 70, scope: !1937)
!1941 = !DILocation(line: 546, column: 10, scope: !1942)
!1942 = !DILexicalBlockFile(scope: !1890, file: !1, discriminator: 1)
!1943 = !DILocation(line: 559, column: 14, scope: !1944)
!1944 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 559, column: 14)
!1945 = !DILocation(line: 559, column: 17, scope: !1944)
!1946 = !DILocation(line: 559, column: 32, scope: !1944)
!1947 = !DILocation(line: 559, column: 35, scope: !1944)
!1948 = !DILocation(line: 559, column: 46, scope: !1944)
!1949 = !DILocation(line: 559, column: 29, scope: !1944)
!1950 = !DILocation(line: 559, column: 14, scope: !1890)
!1951 = !DILocation(line: 559, column: 50, scope: !1952)
!1952 = !DILexicalBlockFile(scope: !1944, file: !1, discriminator: 1)
!1953 = !DILocation(line: 562, column: 14, scope: !1954)
!1954 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 562, column: 14)
!1955 = !DILocation(line: 562, column: 17, scope: !1954)
!1956 = !DILocation(line: 562, column: 31, scope: !1954)
!1957 = !DILocation(line: 562, column: 34, scope: !1954)
!1958 = !DILocation(line: 562, column: 45, scope: !1954)
!1959 = !DILocation(line: 562, column: 29, scope: !1954)
!1960 = !DILocation(line: 562, column: 14, scope: !1890)
!1961 = !DILocation(line: 563, column: 13, scope: !1954)
!1962 = !DILocation(line: 565, column: 10, scope: !1890)
!1963 = !DILocation(line: 565, column: 13, scope: !1890)
!1964 = !DILocation(line: 565, column: 27, scope: !1890)
!1965 = !DILocation(line: 566, column: 28, scope: !1890)
!1966 = !DILocation(line: 566, column: 31, scope: !1890)
!1967 = !DILocation(line: 566, column: 10, scope: !1890)
!1968 = !DILocation(line: 566, column: 13, scope: !1890)
!1969 = !DILocation(line: 566, column: 26, scope: !1890)
!1970 = !DILocation(line: 567, column: 10, scope: !1971)
!1971 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 567, column: 10)
!1972 = !DILocation(line: 567, column: 10, scope: !1890)
!1973 = !DILocation(line: 567, column: 10, scope: !1974)
!1974 = !DILexicalBlockFile(scope: !1971, file: !1, discriminator: 1)
!1975 = !DILocation(line: 567, column: 10, scope: !1976)
!1976 = !DILexicalBlockFile(scope: !1890, file: !1, discriminator: 2)
!1977 = !DILocation(line: 567, column: 27, scope: !1976)
!1978 = !DILocation(line: 567, column: 27, scope: !1979)
!1979 = !DILexicalBlockFile(scope: !1980, file: !1, discriminator: 3)
!1980 = distinct !DILexicalBlock(scope: !1981, file: !1, line: 567, column: 27)
!1981 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 567, column: 27)
!1982 = !DILocation(line: 567, column: 27, scope: !1983)
!1983 = !DILexicalBlockFile(scope: !1984, file: !1, discriminator: 4)
!1984 = distinct !DILexicalBlock(scope: !1980, file: !1, line: 567, column: 27)
!1985 = !DILocation(line: 567, column: 27, scope: !1986)
!1986 = !DILexicalBlockFile(scope: !1980, file: !1, discriminator: 5)
!1987 = !DILocation(line: 567, column: 27, scope: !1988)
!1988 = !DILexicalBlockFile(scope: !1890, file: !1, discriminator: 6)
!1989 = !DILocation(line: 568, column: 16, scope: !1890)
!1990 = !DILocation(line: 568, column: 13, scope: !1890)
!1991 = !DILocation(line: 568, column: 30, scope: !1890)
!1992 = !DILocation(line: 568, column: 33, scope: !1890)
!1993 = !DILocation(line: 568, column: 44, scope: !1890)
!1994 = !DILocation(line: 569, column: 14, scope: !1995)
!1995 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 569, column: 14)
!1996 = !DILocation(line: 569, column: 17, scope: !1995)
!1997 = !DILocation(line: 569, column: 32, scope: !1995)
!1998 = !DILocation(line: 569, column: 35, scope: !1995)
!1999 = !DILocation(line: 569, column: 46, scope: !1995)
!2000 = !DILocation(line: 569, column: 29, scope: !1995)
!2001 = !DILocation(line: 569, column: 14, scope: !1890)
!2002 = !DILocation(line: 569, column: 50, scope: !2003)
!2003 = !DILexicalBlockFile(scope: !1995, file: !1, discriminator: 1)
!2004 = !DILocation(line: 570, column: 14, scope: !2005)
!2005 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 570, column: 14)
!2006 = !DILocation(line: 570, column: 20, scope: !2005)
!2007 = !DILocation(line: 570, column: 23, scope: !2005)
!2008 = !DILocation(line: 570, column: 17, scope: !2005)
!2009 = !DILocation(line: 570, column: 14, scope: !1890)
!2010 = !DILocation(line: 570, column: 37, scope: !2011)
!2011 = !DILexicalBlockFile(scope: !2012, file: !1, discriminator: 1)
!2012 = distinct !DILexicalBlock(scope: !2005, file: !1, line: 570, column: 27)
!2013 = !DILocation(line: 570, column: 29, scope: !2011)
!2014 = !DILocation(line: 570, column: 32, scope: !2011)
!2015 = !DILocation(line: 570, column: 35, scope: !2011)
!2016 = !DILocation(line: 570, column: 41, scope: !2011)
!2017 = !DILocation(line: 572, column: 10, scope: !1890)
!2018 = !DILocation(line: 572, column: 13, scope: !1890)
!2019 = !DILocation(line: 572, column: 27, scope: !1890)
!2020 = !DILocation(line: 573, column: 10, scope: !2021)
!2021 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 573, column: 10)
!2022 = !DILocation(line: 573, column: 10, scope: !1890)
!2023 = !DILocation(line: 573, column: 10, scope: !2024)
!2024 = !DILexicalBlockFile(scope: !2021, file: !1, discriminator: 1)
!2025 = !DILocation(line: 573, column: 10, scope: !1976)
!2026 = !DILocation(line: 573, column: 27, scope: !1976)
!2027 = !DILocation(line: 573, column: 27, scope: !2028)
!2028 = !DILexicalBlockFile(scope: !2029, file: !1, discriminator: 3)
!2029 = distinct !DILexicalBlock(scope: !2030, file: !1, line: 573, column: 27)
!2030 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 573, column: 27)
!2031 = !DILocation(line: 573, column: 27, scope: !2032)
!2032 = !DILexicalBlockFile(scope: !2033, file: !1, discriminator: 4)
!2033 = distinct !DILexicalBlock(scope: !2029, file: !1, line: 573, column: 27)
!2034 = !DILocation(line: 573, column: 27, scope: !2035)
!2035 = !DILexicalBlockFile(scope: !2029, file: !1, discriminator: 5)
!2036 = !DILocation(line: 573, column: 27, scope: !1988)
!2037 = !DILocation(line: 574, column: 16, scope: !1890)
!2038 = !DILocation(line: 574, column: 13, scope: !1890)
!2039 = !DILocation(line: 574, column: 30, scope: !1890)
!2040 = !DILocation(line: 574, column: 33, scope: !1890)
!2041 = !DILocation(line: 574, column: 44, scope: !1890)
!2042 = !DILocation(line: 575, column: 14, scope: !2043)
!2043 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 575, column: 14)
!2044 = !DILocation(line: 575, column: 17, scope: !2043)
!2045 = !DILocation(line: 575, column: 32, scope: !2043)
!2046 = !DILocation(line: 575, column: 35, scope: !2043)
!2047 = !DILocation(line: 575, column: 46, scope: !2043)
!2048 = !DILocation(line: 575, column: 29, scope: !2043)
!2049 = !DILocation(line: 575, column: 14, scope: !1890)
!2050 = !DILocation(line: 575, column: 50, scope: !2051)
!2051 = !DILexicalBlockFile(scope: !2043, file: !1, discriminator: 1)
!2052 = !DILocation(line: 576, column: 14, scope: !2053)
!2053 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 576, column: 14)
!2054 = !DILocation(line: 576, column: 20, scope: !2053)
!2055 = !DILocation(line: 576, column: 23, scope: !2053)
!2056 = !DILocation(line: 576, column: 17, scope: !2053)
!2057 = !DILocation(line: 576, column: 14, scope: !1890)
!2058 = !DILocation(line: 576, column: 37, scope: !2059)
!2059 = !DILexicalBlockFile(scope: !2060, file: !1, discriminator: 1)
!2060 = distinct !DILexicalBlock(scope: !2053, file: !1, line: 576, column: 27)
!2061 = !DILocation(line: 576, column: 29, scope: !2059)
!2062 = !DILocation(line: 576, column: 32, scope: !2059)
!2063 = !DILocation(line: 576, column: 35, scope: !2059)
!2064 = !DILocation(line: 576, column: 41, scope: !2059)
!2065 = !DILocation(line: 578, column: 10, scope: !1890)
!2066 = !DILocation(line: 578, column: 13, scope: !1890)
!2067 = !DILocation(line: 578, column: 27, scope: !1890)
!2068 = !DILocation(line: 579, column: 10, scope: !2069)
!2069 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 579, column: 10)
!2070 = !DILocation(line: 579, column: 10, scope: !1890)
!2071 = !DILocation(line: 579, column: 10, scope: !2072)
!2072 = !DILexicalBlockFile(scope: !2069, file: !1, discriminator: 1)
!2073 = !DILocation(line: 579, column: 10, scope: !1976)
!2074 = !DILocation(line: 579, column: 27, scope: !1976)
!2075 = !DILocation(line: 579, column: 27, scope: !2076)
!2076 = !DILexicalBlockFile(scope: !2077, file: !1, discriminator: 3)
!2077 = distinct !DILexicalBlock(scope: !2078, file: !1, line: 579, column: 27)
!2078 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 579, column: 27)
!2079 = !DILocation(line: 579, column: 27, scope: !2080)
!2080 = !DILexicalBlockFile(scope: !2081, file: !1, discriminator: 4)
!2081 = distinct !DILexicalBlock(scope: !2077, file: !1, line: 579, column: 27)
!2082 = !DILocation(line: 579, column: 27, scope: !2083)
!2083 = !DILexicalBlockFile(scope: !2077, file: !1, discriminator: 5)
!2084 = !DILocation(line: 579, column: 27, scope: !1988)
!2085 = !DILocation(line: 580, column: 16, scope: !1890)
!2086 = !DILocation(line: 580, column: 13, scope: !1890)
!2087 = !DILocation(line: 580, column: 30, scope: !1890)
!2088 = !DILocation(line: 580, column: 33, scope: !1890)
!2089 = !DILocation(line: 580, column: 44, scope: !1890)
!2090 = !DILocation(line: 581, column: 14, scope: !2091)
!2091 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 581, column: 14)
!2092 = !DILocation(line: 581, column: 17, scope: !2091)
!2093 = !DILocation(line: 581, column: 32, scope: !2091)
!2094 = !DILocation(line: 581, column: 35, scope: !2091)
!2095 = !DILocation(line: 581, column: 46, scope: !2091)
!2096 = !DILocation(line: 581, column: 29, scope: !2091)
!2097 = !DILocation(line: 581, column: 14, scope: !1890)
!2098 = !DILocation(line: 581, column: 50, scope: !2099)
!2099 = !DILexicalBlockFile(scope: !2091, file: !1, discriminator: 1)
!2100 = !DILocation(line: 582, column: 14, scope: !2101)
!2101 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 582, column: 14)
!2102 = !DILocation(line: 582, column: 20, scope: !2101)
!2103 = !DILocation(line: 582, column: 23, scope: !2101)
!2104 = !DILocation(line: 582, column: 17, scope: !2101)
!2105 = !DILocation(line: 582, column: 14, scope: !1890)
!2106 = !DILocation(line: 582, column: 37, scope: !2107)
!2107 = !DILexicalBlockFile(scope: !2108, file: !1, discriminator: 1)
!2108 = distinct !DILexicalBlock(scope: !2101, file: !1, line: 582, column: 27)
!2109 = !DILocation(line: 582, column: 29, scope: !2107)
!2110 = !DILocation(line: 582, column: 32, scope: !2107)
!2111 = !DILocation(line: 582, column: 35, scope: !2107)
!2112 = !DILocation(line: 582, column: 41, scope: !2107)
!2113 = !DILocation(line: 584, column: 10, scope: !2114)
!2114 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 584, column: 10)
!2115 = !DILocation(line: 584, column: 10, scope: !1890)
!2116 = !DILocation(line: 584, column: 10, scope: !2117)
!2117 = !DILexicalBlockFile(scope: !2114, file: !1, discriminator: 1)
!2118 = !DILocation(line: 584, column: 10, scope: !1976)
!2119 = !DILocation(line: 584, column: 27, scope: !1976)
!2120 = !DILocation(line: 584, column: 27, scope: !2121)
!2121 = !DILexicalBlockFile(scope: !2122, file: !1, discriminator: 3)
!2122 = distinct !DILexicalBlock(scope: !2123, file: !1, line: 584, column: 27)
!2123 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 584, column: 27)
!2124 = !DILocation(line: 584, column: 27, scope: !2125)
!2125 = !DILexicalBlockFile(scope: !2126, file: !1, discriminator: 4)
!2126 = distinct !DILexicalBlock(scope: !2122, file: !1, line: 584, column: 27)
!2127 = !DILocation(line: 584, column: 27, scope: !2128)
!2128 = !DILexicalBlockFile(scope: !2122, file: !1, discriminator: 5)
!2129 = !DILocation(line: 584, column: 27, scope: !1988)
!2130 = !DILocation(line: 585, column: 16, scope: !1890)
!2131 = !DILocation(line: 585, column: 13, scope: !1890)
!2132 = !DILocation(line: 585, column: 30, scope: !1890)
!2133 = !DILocation(line: 585, column: 33, scope: !1890)
!2134 = !DILocation(line: 585, column: 44, scope: !1890)
!2135 = !DILocation(line: 586, column: 37, scope: !1890)
!2136 = !DILocation(line: 586, column: 30, scope: !1890)
!2137 = !DILocation(line: 586, column: 41, scope: !1890)
!2138 = !DILocation(line: 586, column: 10, scope: !1890)
!2139 = !DILocation(line: 586, column: 13, scope: !1890)
!2140 = !DILocation(line: 586, column: 27, scope: !1890)
!2141 = !DILocation(line: 587, column: 10, scope: !2142)
!2142 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 587, column: 10)
!2143 = !DILocation(line: 587, column: 10, scope: !1890)
!2144 = !DILocation(line: 587, column: 10, scope: !2145)
!2145 = !DILexicalBlockFile(scope: !2142, file: !1, discriminator: 1)
!2146 = !DILocation(line: 587, column: 10, scope: !1976)
!2147 = !DILocation(line: 587, column: 30, scope: !1976)
!2148 = !DILocation(line: 587, column: 30, scope: !2149)
!2149 = !DILexicalBlockFile(scope: !2150, file: !1, discriminator: 3)
!2150 = distinct !DILexicalBlock(scope: !2151, file: !1, line: 587, column: 30)
!2151 = distinct !DILexicalBlock(scope: !1890, file: !1, line: 587, column: 30)
!2152 = !DILocation(line: 587, column: 30, scope: !2153)
!2153 = !DILexicalBlockFile(scope: !2154, file: !1, discriminator: 4)
!2154 = distinct !DILexicalBlock(scope: !2150, file: !1, line: 587, column: 30)
!2155 = !DILocation(line: 587, column: 30, scope: !2156)
!2156 = !DILexicalBlockFile(scope: !2150, file: !1, discriminator: 5)
!2157 = !DILocation(line: 587, column: 30, scope: !1988)
!2158 = !DILocation(line: 588, column: 19, scope: !1890)
!2159 = !DILocation(line: 588, column: 10, scope: !1890)
!2160 = !DILocation(line: 588, column: 13, scope: !1890)
!2161 = !DILocation(line: 588, column: 16, scope: !1890)
!2162 = !DILocation(line: 588, column: 33, scope: !1890)
!2163 = !DILocation(line: 588, column: 36, scope: !1890)
!2164 = !DILocation(line: 588, column: 47, scope: !1890)
!2165 = !DILocation(line: 544, column: 7, scope: !2166)
!2166 = !DILexicalBlockFile(scope: !1888, file: !1, discriminator: 1)
!2167 = !DILocalVariable(name: "c_calculatedBlockCRC", scope: !2168, file: !1, line: 594, type: !28)
!2168 = distinct !DILexicalBlock(scope: !1884, file: !1, line: 591, column: 11)
!2169 = !DILocation(line: 594, column: 21, scope: !2168)
!2170 = !DILocation(line: 594, column: 44, scope: !2168)
!2171 = !DILocation(line: 594, column: 47, scope: !2168)
!2172 = !DILocalVariable(name: "c_state_out_ch", scope: !2168, file: !1, line: 595, type: !21)
!2173 = !DILocation(line: 595, column: 21, scope: !2168)
!2174 = !DILocation(line: 595, column: 44, scope: !2168)
!2175 = !DILocation(line: 595, column: 47, scope: !2168)
!2176 = !DILocalVariable(name: "c_state_out_len", scope: !2168, file: !1, line: 596, type: !103)
!2177 = !DILocation(line: 596, column: 21, scope: !2168)
!2178 = !DILocation(line: 596, column: 44, scope: !2168)
!2179 = !DILocation(line: 596, column: 47, scope: !2168)
!2180 = !DILocalVariable(name: "c_nblock_used", scope: !2168, file: !1, line: 597, type: !103)
!2181 = !DILocation(line: 597, column: 21, scope: !2168)
!2182 = !DILocation(line: 597, column: 44, scope: !2168)
!2183 = !DILocation(line: 597, column: 47, scope: !2168)
!2184 = !DILocalVariable(name: "c_k0", scope: !2168, file: !1, line: 598, type: !103)
!2185 = !DILocation(line: 598, column: 21, scope: !2168)
!2186 = !DILocation(line: 598, column: 44, scope: !2168)
!2187 = !DILocation(line: 598, column: 47, scope: !2168)
!2188 = !DILocalVariable(name: "c_tt", scope: !2168, file: !1, line: 599, type: !27)
!2189 = !DILocation(line: 599, column: 21, scope: !2168)
!2190 = !DILocation(line: 599, column: 44, scope: !2168)
!2191 = !DILocation(line: 599, column: 47, scope: !2168)
!2192 = !DILocalVariable(name: "c_tPos", scope: !2168, file: !1, line: 600, type: !28)
!2193 = !DILocation(line: 600, column: 21, scope: !2168)
!2194 = !DILocation(line: 600, column: 44, scope: !2168)
!2195 = !DILocation(line: 600, column: 47, scope: !2168)
!2196 = !DILocalVariable(name: "cs_next_out", scope: !2168, file: !1, line: 601, type: !45)
!2197 = !DILocation(line: 601, column: 21, scope: !2168)
!2198 = !DILocation(line: 601, column: 44, scope: !2168)
!2199 = !DILocation(line: 601, column: 47, scope: !2168)
!2200 = !DILocation(line: 601, column: 53, scope: !2168)
!2201 = !DILocalVariable(name: "cs_avail_out", scope: !2168, file: !1, line: 602, type: !29)
!2202 = !DILocation(line: 602, column: 21, scope: !2168)
!2203 = !DILocation(line: 602, column: 44, scope: !2168)
!2204 = !DILocation(line: 602, column: 47, scope: !2168)
!2205 = !DILocation(line: 602, column: 53, scope: !2168)
!2206 = !DILocalVariable(name: "ro_blockSize100k", scope: !2168, file: !1, line: 603, type: !103)
!2207 = !DILocation(line: 603, column: 21, scope: !2168)
!2208 = !DILocation(line: 603, column: 44, scope: !2168)
!2209 = !DILocation(line: 603, column: 47, scope: !2168)
!2210 = !DILocalVariable(name: "avail_out_INIT", scope: !2168, file: !1, line: 606, type: !28)
!2211 = !DILocation(line: 606, column: 20, scope: !2168)
!2212 = !DILocation(line: 606, column: 37, scope: !2168)
!2213 = !DILocalVariable(name: "s_save_nblockPP", scope: !2168, file: !1, line: 607, type: !103)
!2214 = !DILocation(line: 607, column: 20, scope: !2168)
!2215 = !DILocation(line: 607, column: 38, scope: !2168)
!2216 = !DILocation(line: 607, column: 41, scope: !2168)
!2217 = !DILocation(line: 607, column: 52, scope: !2168)
!2218 = !DILocalVariable(name: "total_out_lo32_old", scope: !2168, file: !1, line: 608, type: !29)
!2219 = !DILocation(line: 608, column: 20, scope: !2168)
!2220 = !DILocation(line: 610, column: 7, scope: !2168)
!2221 = !DILocation(line: 613, column: 14, scope: !2222)
!2222 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 613, column: 14)
!2223 = distinct !DILexicalBlock(scope: !2168, file: !1, line: 610, column: 20)
!2224 = !DILocation(line: 613, column: 30, scope: !2222)
!2225 = !DILocation(line: 613, column: 14, scope: !2223)
!2226 = !DILocation(line: 614, column: 13, scope: !2227)
!2227 = distinct !DILexicalBlock(scope: !2222, file: !1, line: 613, column: 35)
!2228 = !DILocation(line: 615, column: 20, scope: !2229)
!2229 = distinct !DILexicalBlock(scope: !2230, file: !1, line: 615, column: 20)
!2230 = distinct !DILexicalBlock(scope: !2227, file: !1, line: 614, column: 26)
!2231 = !DILocation(line: 615, column: 33, scope: !2229)
!2232 = !DILocation(line: 615, column: 20, scope: !2230)
!2233 = !DILocation(line: 615, column: 39, scope: !2234)
!2234 = !DILexicalBlockFile(scope: !2229, file: !1, discriminator: 1)
!2235 = !DILocation(line: 616, column: 20, scope: !2236)
!2236 = distinct !DILexicalBlock(scope: !2230, file: !1, line: 616, column: 20)
!2237 = !DILocation(line: 616, column: 36, scope: !2236)
!2238 = !DILocation(line: 616, column: 20, scope: !2230)
!2239 = !DILocation(line: 616, column: 42, scope: !2240)
!2240 = !DILexicalBlockFile(scope: !2236, file: !1, discriminator: 1)
!2241 = !DILocation(line: 617, column: 45, scope: !2230)
!2242 = !DILocation(line: 617, column: 28, scope: !2230)
!2243 = !DILocation(line: 617, column: 43, scope: !2230)
!2244 = !DILocation(line: 618, column: 16, scope: !2245)
!2245 = distinct !DILexicalBlock(scope: !2230, file: !1, line: 618, column: 16)
!2246 = !DILocation(line: 619, column: 31, scope: !2230)
!2247 = !DILocation(line: 620, column: 27, scope: !2230)
!2248 = !DILocation(line: 621, column: 28, scope: !2230)
!2249 = !DILocation(line: 614, column: 13, scope: !2250)
!2250 = !DILexicalBlockFile(scope: !2227, file: !1, discriminator: 1)
!2251 = !DILocation(line: 614, column: 13, scope: !2252)
!2252 = !DILexicalBlockFile(scope: !2227, file: !1, discriminator: 2)
!2253 = !DILocation(line: 625, column: 20, scope: !2254)
!2254 = distinct !DILexicalBlock(scope: !2255, file: !1, line: 625, column: 20)
!2255 = distinct !DILexicalBlock(scope: !2227, file: !1, line: 624, column: 13)
!2256 = !DILocation(line: 625, column: 33, scope: !2254)
!2257 = !DILocation(line: 625, column: 20, scope: !2255)
!2258 = !DILocation(line: 626, column: 35, scope: !2259)
!2259 = distinct !DILexicalBlock(scope: !2254, file: !1, line: 625, column: 39)
!2260 = !DILocation(line: 626, column: 40, scope: !2259)
!2261 = !DILocation(line: 628, column: 45, scope: !2255)
!2262 = !DILocation(line: 628, column: 28, scope: !2255)
!2263 = !DILocation(line: 628, column: 43, scope: !2255)
!2264 = !DILocation(line: 629, column: 16, scope: !2265)
!2265 = distinct !DILexicalBlock(scope: !2255, file: !1, line: 629, column: 16)
!2266 = !DILocation(line: 630, column: 27, scope: !2255)
!2267 = !DILocation(line: 631, column: 28, scope: !2255)
!2268 = !DILocation(line: 633, column: 10, scope: !2227)
!2269 = !DILocation(line: 635, column: 14, scope: !2270)
!2270 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 635, column: 14)
!2271 = !DILocation(line: 635, column: 30, scope: !2270)
!2272 = !DILocation(line: 635, column: 28, scope: !2270)
!2273 = !DILocation(line: 635, column: 14, scope: !2223)
!2274 = !DILocation(line: 636, column: 13, scope: !2270)
!2275 = !DILocation(line: 639, column: 14, scope: !2276)
!2276 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 639, column: 14)
!2277 = !DILocation(line: 639, column: 31, scope: !2276)
!2278 = !DILocation(line: 639, column: 28, scope: !2276)
!2279 = !DILocation(line: 639, column: 14, scope: !2223)
!2280 = !DILocation(line: 640, column: 29, scope: !2281)
!2281 = distinct !DILexicalBlock(scope: !2276, file: !1, line: 639, column: 48)
!2282 = !DILocation(line: 640, column: 34, scope: !2281)
!2283 = !DILocation(line: 642, column: 27, scope: !2223)
!2284 = !DILocation(line: 642, column: 25, scope: !2223)
!2285 = !DILocation(line: 643, column: 10, scope: !2286)
!2286 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 643, column: 10)
!2287 = !DILocation(line: 643, column: 10, scope: !2223)
!2288 = !DILocation(line: 643, column: 10, scope: !2289)
!2289 = !DILexicalBlockFile(scope: !2286, file: !1, discriminator: 1)
!2290 = !DILocation(line: 643, column: 10, scope: !2291)
!2291 = !DILexicalBlockFile(scope: !2223, file: !1, discriminator: 2)
!2292 = !DILocation(line: 643, column: 42, scope: !2291)
!2293 = !DILocation(line: 644, column: 14, scope: !2294)
!2294 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 644, column: 14)
!2295 = !DILocation(line: 644, column: 20, scope: !2294)
!2296 = !DILocation(line: 644, column: 17, scope: !2294)
!2297 = !DILocation(line: 644, column: 14, scope: !2223)
!2298 = !DILocation(line: 645, column: 20, scope: !2299)
!2299 = distinct !DILexicalBlock(scope: !2294, file: !1, line: 644, column: 26)
!2300 = !DILocation(line: 645, column: 18, scope: !2299)
!2301 = !DILocation(line: 645, column: 24, scope: !2299)
!2302 = !DILocation(line: 647, column: 14, scope: !2303)
!2303 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 647, column: 14)
!2304 = !DILocation(line: 647, column: 31, scope: !2303)
!2305 = !DILocation(line: 647, column: 28, scope: !2303)
!2306 = !DILocation(line: 647, column: 14, scope: !2223)
!2307 = !DILocation(line: 648, column: 13, scope: !2303)
!2308 = !DILocation(line: 650, column: 26, scope: !2223)
!2309 = !DILocation(line: 651, column: 10, scope: !2310)
!2310 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 651, column: 10)
!2311 = !DILocation(line: 651, column: 10, scope: !2223)
!2312 = !DILocation(line: 651, column: 10, scope: !2313)
!2313 = !DILexicalBlockFile(scope: !2310, file: !1, discriminator: 1)
!2314 = !DILocation(line: 651, column: 10, scope: !2291)
!2315 = !DILocation(line: 651, column: 42, scope: !2291)
!2316 = !DILocation(line: 652, column: 14, scope: !2317)
!2317 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 652, column: 14)
!2318 = !DILocation(line: 652, column: 31, scope: !2317)
!2319 = !DILocation(line: 652, column: 28, scope: !2317)
!2320 = !DILocation(line: 652, column: 14, scope: !2223)
!2321 = !DILocation(line: 652, column: 48, scope: !2322)
!2322 = !DILexicalBlockFile(scope: !2317, file: !1, discriminator: 1)
!2323 = !DILocation(line: 653, column: 14, scope: !2324)
!2324 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 653, column: 14)
!2325 = !DILocation(line: 653, column: 20, scope: !2324)
!2326 = !DILocation(line: 653, column: 17, scope: !2324)
!2327 = !DILocation(line: 653, column: 14, scope: !2223)
!2328 = !DILocation(line: 653, column: 35, scope: !2329)
!2329 = !DILexicalBlockFile(scope: !2330, file: !1, discriminator: 1)
!2330 = distinct !DILexicalBlock(scope: !2324, file: !1, line: 653, column: 26)
!2331 = !DILocation(line: 653, column: 33, scope: !2329)
!2332 = !DILocation(line: 653, column: 39, scope: !2329)
!2333 = !DILocation(line: 655, column: 26, scope: !2223)
!2334 = !DILocation(line: 656, column: 10, scope: !2335)
!2335 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 656, column: 10)
!2336 = !DILocation(line: 656, column: 10, scope: !2223)
!2337 = !DILocation(line: 656, column: 10, scope: !2338)
!2338 = !DILexicalBlockFile(scope: !2335, file: !1, discriminator: 1)
!2339 = !DILocation(line: 656, column: 10, scope: !2291)
!2340 = !DILocation(line: 656, column: 42, scope: !2291)
!2341 = !DILocation(line: 657, column: 14, scope: !2342)
!2342 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 657, column: 14)
!2343 = !DILocation(line: 657, column: 31, scope: !2342)
!2344 = !DILocation(line: 657, column: 28, scope: !2342)
!2345 = !DILocation(line: 657, column: 14, scope: !2223)
!2346 = !DILocation(line: 657, column: 48, scope: !2347)
!2347 = !DILexicalBlockFile(scope: !2342, file: !1, discriminator: 1)
!2348 = !DILocation(line: 658, column: 14, scope: !2349)
!2349 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 658, column: 14)
!2350 = !DILocation(line: 658, column: 20, scope: !2349)
!2351 = !DILocation(line: 658, column: 17, scope: !2349)
!2352 = !DILocation(line: 658, column: 14, scope: !2223)
!2353 = !DILocation(line: 658, column: 35, scope: !2354)
!2354 = !DILexicalBlockFile(scope: !2355, file: !1, discriminator: 1)
!2355 = distinct !DILexicalBlock(scope: !2349, file: !1, line: 658, column: 26)
!2356 = !DILocation(line: 658, column: 33, scope: !2354)
!2357 = !DILocation(line: 658, column: 39, scope: !2354)
!2358 = !DILocation(line: 660, column: 10, scope: !2359)
!2359 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 660, column: 10)
!2360 = !DILocation(line: 660, column: 10, scope: !2223)
!2361 = !DILocation(line: 660, column: 10, scope: !2362)
!2362 = !DILexicalBlockFile(scope: !2359, file: !1, discriminator: 1)
!2363 = !DILocation(line: 660, column: 10, scope: !2291)
!2364 = !DILocation(line: 660, column: 42, scope: !2291)
!2365 = !DILocation(line: 661, column: 36, scope: !2223)
!2366 = !DILocation(line: 661, column: 29, scope: !2223)
!2367 = !DILocation(line: 661, column: 40, scope: !2223)
!2368 = !DILocation(line: 661, column: 26, scope: !2223)
!2369 = !DILocation(line: 662, column: 10, scope: !2370)
!2370 = distinct !DILexicalBlock(scope: !2223, file: !1, line: 662, column: 10)
!2371 = !DILocation(line: 662, column: 10, scope: !2223)
!2372 = !DILocation(line: 662, column: 10, scope: !2373)
!2373 = !DILexicalBlockFile(scope: !2370, file: !1, discriminator: 1)
!2374 = !DILocation(line: 662, column: 10, scope: !2291)
!2375 = !DILocation(line: 662, column: 44, scope: !2291)
!2376 = !DILocation(line: 610, column: 7, scope: !2377)
!2377 = !DILexicalBlockFile(scope: !2168, file: !1, discriminator: 1)
!2378 = !DILocation(line: 666, column: 28, scope: !2168)
!2379 = !DILocation(line: 666, column: 31, scope: !2168)
!2380 = !DILocation(line: 666, column: 37, scope: !2168)
!2381 = !DILocation(line: 666, column: 26, scope: !2168)
!2382 = !DILocation(line: 667, column: 35, scope: !2168)
!2383 = !DILocation(line: 667, column: 52, scope: !2168)
!2384 = !DILocation(line: 667, column: 50, scope: !2168)
!2385 = !DILocation(line: 667, column: 7, scope: !2168)
!2386 = !DILocation(line: 667, column: 10, scope: !2168)
!2387 = !DILocation(line: 667, column: 16, scope: !2168)
!2388 = !DILocation(line: 667, column: 31, scope: !2168)
!2389 = !DILocation(line: 668, column: 11, scope: !2390)
!2390 = distinct !DILexicalBlock(scope: !2168, file: !1, line: 668, column: 11)
!2391 = !DILocation(line: 668, column: 14, scope: !2390)
!2392 = !DILocation(line: 668, column: 20, scope: !2390)
!2393 = !DILocation(line: 668, column: 37, scope: !2390)
!2394 = !DILocation(line: 668, column: 35, scope: !2390)
!2395 = !DILocation(line: 668, column: 11, scope: !2168)
!2396 = !DILocation(line: 669, column: 10, scope: !2390)
!2397 = !DILocation(line: 669, column: 13, scope: !2390)
!2398 = !DILocation(line: 669, column: 19, scope: !2390)
!2399 = !DILocation(line: 669, column: 33, scope: !2390)
!2400 = !DILocation(line: 672, column: 31, scope: !2168)
!2401 = !DILocation(line: 672, column: 7, scope: !2168)
!2402 = !DILocation(line: 672, column: 10, scope: !2168)
!2403 = !DILocation(line: 672, column: 29, scope: !2168)
!2404 = !DILocation(line: 673, column: 31, scope: !2168)
!2405 = !DILocation(line: 673, column: 7, scope: !2168)
!2406 = !DILocation(line: 673, column: 10, scope: !2168)
!2407 = !DILocation(line: 673, column: 29, scope: !2168)
!2408 = !DILocation(line: 674, column: 31, scope: !2168)
!2409 = !DILocation(line: 674, column: 7, scope: !2168)
!2410 = !DILocation(line: 674, column: 10, scope: !2168)
!2411 = !DILocation(line: 674, column: 29, scope: !2168)
!2412 = !DILocation(line: 675, column: 31, scope: !2168)
!2413 = !DILocation(line: 675, column: 7, scope: !2168)
!2414 = !DILocation(line: 675, column: 10, scope: !2168)
!2415 = !DILocation(line: 675, column: 29, scope: !2168)
!2416 = !DILocation(line: 676, column: 31, scope: !2168)
!2417 = !DILocation(line: 676, column: 7, scope: !2168)
!2418 = !DILocation(line: 676, column: 10, scope: !2168)
!2419 = !DILocation(line: 676, column: 29, scope: !2168)
!2420 = !DILocation(line: 677, column: 31, scope: !2168)
!2421 = !DILocation(line: 677, column: 7, scope: !2168)
!2422 = !DILocation(line: 677, column: 10, scope: !2168)
!2423 = !DILocation(line: 677, column: 29, scope: !2168)
!2424 = !DILocation(line: 678, column: 31, scope: !2168)
!2425 = !DILocation(line: 678, column: 7, scope: !2168)
!2426 = !DILocation(line: 678, column: 10, scope: !2168)
!2427 = !DILocation(line: 678, column: 29, scope: !2168)
!2428 = !DILocation(line: 679, column: 31, scope: !2168)
!2429 = !DILocation(line: 679, column: 7, scope: !2168)
!2430 = !DILocation(line: 679, column: 10, scope: !2168)
!2431 = !DILocation(line: 679, column: 16, scope: !2168)
!2432 = !DILocation(line: 679, column: 29, scope: !2168)
!2433 = !DILocation(line: 680, column: 31, scope: !2168)
!2434 = !DILocation(line: 680, column: 7, scope: !2168)
!2435 = !DILocation(line: 680, column: 10, scope: !2168)
!2436 = !DILocation(line: 680, column: 16, scope: !2168)
!2437 = !DILocation(line: 680, column: 29, scope: !2168)
!2438 = !DILocation(line: 683, column: 4, scope: !378)
!2439 = !DILocation(line: 684, column: 1, scope: !378)
!2440 = !DILocalVariable(name: "strm", arg: 1, scope: !153, file: !1, line: 864, type: !138)
!2441 = !DILocation(line: 864, column: 47, scope: !153)
!2442 = !DILocalVariable(name: "s", scope: !153, file: !1, line: 866, type: !297)
!2443 = !DILocation(line: 866, column: 12, scope: !153)
!2444 = !DILocation(line: 867, column: 8, scope: !2445)
!2445 = distinct !DILexicalBlock(scope: !153, file: !1, line: 867, column: 8)
!2446 = !DILocation(line: 867, column: 13, scope: !2445)
!2447 = !DILocation(line: 867, column: 8, scope: !153)
!2448 = !DILocation(line: 867, column: 22, scope: !2449)
!2449 = !DILexicalBlockFile(scope: !2445, file: !1, discriminator: 1)
!2450 = !DILocation(line: 868, column: 8, scope: !153)
!2451 = !DILocation(line: 868, column: 14, scope: !153)
!2452 = !DILocation(line: 868, column: 6, scope: !153)
!2453 = !DILocation(line: 869, column: 8, scope: !2454)
!2454 = distinct !DILexicalBlock(scope: !153, file: !1, line: 869, column: 8)
!2455 = !DILocation(line: 869, column: 10, scope: !2454)
!2456 = !DILocation(line: 869, column: 8, scope: !153)
!2457 = !DILocation(line: 869, column: 19, scope: !2458)
!2458 = !DILexicalBlockFile(scope: !2454, file: !1, discriminator: 1)
!2459 = !DILocation(line: 870, column: 8, scope: !2460)
!2460 = distinct !DILexicalBlock(scope: !153, file: !1, line: 870, column: 8)
!2461 = !DILocation(line: 870, column: 11, scope: !2460)
!2462 = !DILocation(line: 870, column: 19, scope: !2460)
!2463 = !DILocation(line: 870, column: 16, scope: !2460)
!2464 = !DILocation(line: 870, column: 8, scope: !153)
!2465 = !DILocation(line: 870, column: 25, scope: !2466)
!2466 = !DILexicalBlockFile(scope: !2460, file: !1, discriminator: 1)
!2467 = !DILocation(line: 872, column: 8, scope: !2468)
!2468 = distinct !DILexicalBlock(scope: !153, file: !1, line: 872, column: 8)
!2469 = !DILocation(line: 872, column: 11, scope: !2468)
!2470 = !DILocation(line: 872, column: 16, scope: !2468)
!2471 = !DILocation(line: 872, column: 8, scope: !153)
!2472 = !DILocation(line: 872, column: 25, scope: !2473)
!2473 = !DILexicalBlockFile(scope: !2468, file: !1, discriminator: 1)
!2474 = !DILocation(line: 873, column: 8, scope: !2475)
!2475 = distinct !DILexicalBlock(scope: !153, file: !1, line: 873, column: 8)
!2476 = !DILocation(line: 873, column: 11, scope: !2475)
!2477 = !DILocation(line: 873, column: 16, scope: !2475)
!2478 = !DILocation(line: 873, column: 8, scope: !153)
!2479 = !DILocation(line: 873, column: 25, scope: !2480)
!2480 = !DILexicalBlockFile(scope: !2475, file: !1, discriminator: 1)
!2481 = !DILocation(line: 874, column: 8, scope: !2482)
!2482 = distinct !DILexicalBlock(scope: !153, file: !1, line: 874, column: 8)
!2483 = !DILocation(line: 874, column: 11, scope: !2482)
!2484 = !DILocation(line: 874, column: 16, scope: !2482)
!2485 = !DILocation(line: 874, column: 8, scope: !153)
!2486 = !DILocation(line: 874, column: 25, scope: !2487)
!2487 = !DILexicalBlockFile(scope: !2482, file: !1, discriminator: 1)
!2488 = !DILocation(line: 876, column: 4, scope: !153)
!2489 = !DILocation(line: 877, column: 4, scope: !153)
!2490 = !DILocation(line: 877, column: 10, scope: !153)
!2491 = !DILocation(line: 877, column: 16, scope: !153)
!2492 = !DILocation(line: 879, column: 4, scope: !153)
!2493 = !DILocation(line: 880, column: 1, scope: !153)
!2494 = !DILocalVariable(name: "bzerror", arg: 1, scope: !154, file: !1, line: 919, type: !159)
!2495 = !DILocation(line: 919, column: 29, scope: !154)
!2496 = !DILocalVariable(name: "f", arg: 2, scope: !154, file: !1, line: 920, type: !36)
!2497 = !DILocation(line: 920, column: 29, scope: !154)
!2498 = !DILocalVariable(name: "blockSize100k", arg: 3, scope: !154, file: !1, line: 921, type: !43)
!2499 = !DILocation(line: 921, column: 29, scope: !154)
!2500 = !DILocalVariable(name: "verbosity", arg: 4, scope: !154, file: !1, line: 922, type: !43)
!2501 = !DILocation(line: 922, column: 29, scope: !154)
!2502 = !DILocalVariable(name: "workFactor", arg: 5, scope: !154, file: !1, line: 923, type: !43)
!2503 = !DILocation(line: 923, column: 29, scope: !154)
!2504 = !DILocalVariable(name: "ret", scope: !154, file: !1, line: 925, type: !103)
!2505 = !DILocation(line: 925, column: 12, scope: !154)
!2506 = !DILocalVariable(name: "bzf", scope: !154, file: !1, line: 926, type: !31)
!2507 = !DILocation(line: 926, column: 12, scope: !154)
!2508 = !DILocation(line: 928, column: 4, scope: !2509)
!2509 = distinct !DILexicalBlock(scope: !2510, file: !1, line: 928, column: 4)
!2510 = distinct !DILexicalBlock(scope: !154, file: !1, line: 928, column: 4)
!2511 = !DILocation(line: 928, column: 4, scope: !2510)
!2512 = !DILocation(line: 928, column: 4, scope: !2513)
!2513 = !DILexicalBlockFile(scope: !2509, file: !1, discriminator: 1)
!2514 = !DILocation(line: 928, column: 4, scope: !2515)
!2515 = !DILexicalBlockFile(scope: !2516, file: !1, discriminator: 2)
!2516 = distinct !DILexicalBlock(scope: !2510, file: !1, line: 928, column: 4)
!2517 = !DILocation(line: 928, column: 4, scope: !2518)
!2518 = !DILexicalBlockFile(scope: !2516, file: !1, discriminator: 3)
!2519 = !DILocation(line: 930, column: 8, scope: !2520)
!2520 = distinct !DILexicalBlock(scope: !154, file: !1, line: 930, column: 8)
!2521 = !DILocation(line: 930, column: 10, scope: !2520)
!2522 = !DILocation(line: 930, column: 18, scope: !2520)
!2523 = !DILocation(line: 931, column: 9, scope: !2520)
!2524 = !DILocation(line: 931, column: 23, scope: !2520)
!2525 = !DILocation(line: 931, column: 27, scope: !2520)
!2526 = !DILocation(line: 931, column: 30, scope: !2527)
!2527 = !DILexicalBlockFile(scope: !2520, file: !1, discriminator: 1)
!2528 = !DILocation(line: 931, column: 44, scope: !2527)
!2529 = !DILocation(line: 931, column: 49, scope: !2527)
!2530 = !DILocation(line: 932, column: 9, scope: !2520)
!2531 = !DILocation(line: 932, column: 20, scope: !2520)
!2532 = !DILocation(line: 932, column: 24, scope: !2520)
!2533 = !DILocation(line: 932, column: 27, scope: !2527)
!2534 = !DILocation(line: 932, column: 38, scope: !2527)
!2535 = !DILocation(line: 932, column: 45, scope: !2527)
!2536 = !DILocation(line: 933, column: 9, scope: !2520)
!2537 = !DILocation(line: 933, column: 19, scope: !2520)
!2538 = !DILocation(line: 933, column: 23, scope: !2520)
!2539 = !DILocation(line: 933, column: 26, scope: !2527)
!2540 = !DILocation(line: 933, column: 36, scope: !2527)
!2541 = !DILocation(line: 930, column: 8, scope: !2542)
!2542 = !DILexicalBlockFile(scope: !154, file: !1, discriminator: 1)
!2543 = !DILocation(line: 934, column: 9, scope: !2544)
!2544 = distinct !DILexicalBlock(scope: !2545, file: !1, line: 934, column: 9)
!2545 = distinct !DILexicalBlock(scope: !2546, file: !1, line: 934, column: 9)
!2546 = distinct !DILexicalBlock(scope: !2520, file: !1, line: 934, column: 7)
!2547 = !DILocation(line: 934, column: 9, scope: !2545)
!2548 = !DILocation(line: 934, column: 9, scope: !2549)
!2549 = !DILexicalBlockFile(scope: !2544, file: !1, discriminator: 1)
!2550 = !DILocation(line: 934, column: 9, scope: !2551)
!2551 = !DILexicalBlockFile(scope: !2552, file: !1, discriminator: 2)
!2552 = distinct !DILexicalBlock(scope: !2545, file: !1, line: 934, column: 9)
!2553 = !DILocation(line: 934, column: 9, scope: !2554)
!2554 = !DILexicalBlockFile(scope: !2552, file: !1, discriminator: 3)
!2555 = !DILocation(line: 934, column: 36, scope: !2556)
!2556 = !DILexicalBlockFile(scope: !2546, file: !1, discriminator: 4)
!2557 = !DILocation(line: 936, column: 15, scope: !2558)
!2558 = distinct !DILexicalBlock(scope: !154, file: !1, line: 936, column: 8)
!2559 = !DILocation(line: 936, column: 8, scope: !2558)
!2560 = !DILocation(line: 936, column: 8, scope: !154)
!2561 = !DILocation(line: 937, column: 9, scope: !2562)
!2562 = distinct !DILexicalBlock(scope: !2563, file: !1, line: 937, column: 9)
!2563 = distinct !DILexicalBlock(scope: !2564, file: !1, line: 937, column: 9)
!2564 = distinct !DILexicalBlock(scope: !2558, file: !1, line: 937, column: 7)
!2565 = !DILocation(line: 937, column: 9, scope: !2563)
!2566 = !DILocation(line: 937, column: 9, scope: !2567)
!2567 = !DILexicalBlockFile(scope: !2562, file: !1, discriminator: 1)
!2568 = !DILocation(line: 937, column: 9, scope: !2569)
!2569 = !DILexicalBlockFile(scope: !2570, file: !1, discriminator: 2)
!2570 = distinct !DILexicalBlock(scope: !2563, file: !1, line: 937, column: 9)
!2571 = !DILocation(line: 937, column: 9, scope: !2572)
!2572 = !DILexicalBlockFile(scope: !2570, file: !1, discriminator: 3)
!2573 = !DILocation(line: 937, column: 33, scope: !2574)
!2574 = !DILexicalBlockFile(scope: !2564, file: !1, discriminator: 4)
!2575 = !DILocation(line: 939, column: 10, scope: !154)
!2576 = !DILocation(line: 939, column: 8, scope: !154)
!2577 = !DILocation(line: 940, column: 8, scope: !2578)
!2578 = distinct !DILexicalBlock(scope: !154, file: !1, line: 940, column: 8)
!2579 = !DILocation(line: 940, column: 12, scope: !2578)
!2580 = !DILocation(line: 940, column: 8, scope: !154)
!2581 = !DILocation(line: 941, column: 9, scope: !2582)
!2582 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 941, column: 9)
!2583 = distinct !DILexicalBlock(scope: !2584, file: !1, line: 941, column: 9)
!2584 = distinct !DILexicalBlock(scope: !2578, file: !1, line: 941, column: 7)
!2585 = !DILocation(line: 941, column: 9, scope: !2583)
!2586 = !DILocation(line: 941, column: 9, scope: !2587)
!2587 = !DILexicalBlockFile(scope: !2582, file: !1, discriminator: 1)
!2588 = !DILocation(line: 941, column: 9, scope: !2589)
!2589 = !DILexicalBlockFile(scope: !2590, file: !1, discriminator: 2)
!2590 = distinct !DILexicalBlock(scope: !2583, file: !1, line: 941, column: 9)
!2591 = !DILocation(line: 941, column: 9, scope: !2592)
!2592 = !DILexicalBlockFile(scope: !2590, file: !1, discriminator: 3)
!2593 = !DILocation(line: 941, column: 34, scope: !2594)
!2594 = !DILexicalBlockFile(scope: !2584, file: !1, discriminator: 4)
!2595 = !DILocation(line: 943, column: 4, scope: !2596)
!2596 = distinct !DILexicalBlock(scope: !2597, file: !1, line: 943, column: 4)
!2597 = distinct !DILexicalBlock(scope: !154, file: !1, line: 943, column: 4)
!2598 = !DILocation(line: 943, column: 4, scope: !2597)
!2599 = !DILocation(line: 943, column: 4, scope: !2600)
!2600 = !DILexicalBlockFile(scope: !2596, file: !1, discriminator: 1)
!2601 = !DILocation(line: 943, column: 4, scope: !2602)
!2602 = !DILexicalBlockFile(scope: !2603, file: !1, discriminator: 2)
!2603 = distinct !DILexicalBlock(scope: !2597, file: !1, line: 943, column: 4)
!2604 = !DILocation(line: 943, column: 4, scope: !2605)
!2605 = !DILexicalBlockFile(scope: !2603, file: !1, discriminator: 3)
!2606 = !DILocation(line: 944, column: 4, scope: !154)
!2607 = !DILocation(line: 944, column: 9, scope: !154)
!2608 = !DILocation(line: 944, column: 23, scope: !154)
!2609 = !DILocation(line: 945, column: 4, scope: !154)
!2610 = !DILocation(line: 945, column: 9, scope: !154)
!2611 = !DILocation(line: 945, column: 23, scope: !154)
!2612 = !DILocation(line: 946, column: 25, scope: !154)
!2613 = !DILocation(line: 946, column: 4, scope: !154)
!2614 = !DILocation(line: 946, column: 9, scope: !154)
!2615 = !DILocation(line: 946, column: 23, scope: !154)
!2616 = !DILocation(line: 947, column: 4, scope: !154)
!2617 = !DILocation(line: 947, column: 9, scope: !154)
!2618 = !DILocation(line: 947, column: 23, scope: !154)
!2619 = !DILocation(line: 948, column: 4, scope: !154)
!2620 = !DILocation(line: 948, column: 9, scope: !154)
!2621 = !DILocation(line: 948, column: 14, scope: !154)
!2622 = !DILocation(line: 948, column: 23, scope: !154)
!2623 = !DILocation(line: 949, column: 4, scope: !154)
!2624 = !DILocation(line: 949, column: 9, scope: !154)
!2625 = !DILocation(line: 949, column: 14, scope: !154)
!2626 = !DILocation(line: 949, column: 23, scope: !154)
!2627 = !DILocation(line: 950, column: 4, scope: !154)
!2628 = !DILocation(line: 950, column: 9, scope: !154)
!2629 = !DILocation(line: 950, column: 14, scope: !154)
!2630 = !DILocation(line: 950, column: 23, scope: !154)
!2631 = !DILocation(line: 952, column: 8, scope: !2632)
!2632 = distinct !DILexicalBlock(scope: !154, file: !1, line: 952, column: 8)
!2633 = !DILocation(line: 952, column: 19, scope: !2632)
!2634 = !DILocation(line: 952, column: 8, scope: !154)
!2635 = !DILocation(line: 952, column: 36, scope: !2636)
!2636 = !DILexicalBlockFile(scope: !2632, file: !1, discriminator: 1)
!2637 = !DILocation(line: 952, column: 25, scope: !2636)
!2638 = !DILocation(line: 953, column: 33, scope: !154)
!2639 = !DILocation(line: 953, column: 38, scope: !154)
!2640 = !DILocation(line: 953, column: 45, scope: !154)
!2641 = !DILocation(line: 954, column: 31, scope: !154)
!2642 = !DILocation(line: 954, column: 42, scope: !154)
!2643 = !DILocation(line: 953, column: 10, scope: !154)
!2644 = !DILocation(line: 953, column: 8, scope: !154)
!2645 = !DILocation(line: 955, column: 8, scope: !2646)
!2646 = distinct !DILexicalBlock(scope: !154, file: !1, line: 955, column: 8)
!2647 = !DILocation(line: 955, column: 12, scope: !2646)
!2648 = !DILocation(line: 955, column: 8, scope: !154)
!2649 = !DILocation(line: 956, column: 9, scope: !2650)
!2650 = distinct !DILexicalBlock(scope: !2651, file: !1, line: 956, column: 9)
!2651 = distinct !DILexicalBlock(scope: !2652, file: !1, line: 956, column: 9)
!2652 = distinct !DILexicalBlock(scope: !2646, file: !1, line: 956, column: 7)
!2653 = !DILocation(line: 956, column: 9, scope: !2651)
!2654 = !DILocation(line: 956, column: 9, scope: !2655)
!2655 = !DILexicalBlockFile(scope: !2650, file: !1, discriminator: 1)
!2656 = !DILocation(line: 956, column: 9, scope: !2657)
!2657 = !DILexicalBlockFile(scope: !2658, file: !1, discriminator: 2)
!2658 = distinct !DILexicalBlock(scope: !2651, file: !1, line: 956, column: 9)
!2659 = !DILocation(line: 956, column: 9, scope: !2660)
!2660 = !DILexicalBlockFile(scope: !2658, file: !1, discriminator: 3)
!2661 = !DILocation(line: 956, column: 30, scope: !2662)
!2662 = !DILexicalBlockFile(scope: !2652, file: !1, discriminator: 4)
!2663 = !DILocation(line: 956, column: 25, scope: !2662)
!2664 = !DILocation(line: 956, column: 36, scope: !2662)
!2665 = !DILocation(line: 958, column: 4, scope: !154)
!2666 = !DILocation(line: 958, column: 9, scope: !154)
!2667 = !DILocation(line: 958, column: 14, scope: !154)
!2668 = !DILocation(line: 958, column: 23, scope: !154)
!2669 = !DILocation(line: 959, column: 4, scope: !154)
!2670 = !DILocation(line: 959, column: 9, scope: !154)
!2671 = !DILocation(line: 959, column: 23, scope: !154)
!2672 = !DILocation(line: 960, column: 11, scope: !154)
!2673 = !DILocation(line: 960, column: 4, scope: !154)
!2674 = !DILocation(line: 961, column: 1, scope: !154)
!2675 = !DILocalVariable(name: "bzerror", arg: 1, scope: !160, file: !1, line: 967, type: !159)
!2676 = !DILocation(line: 967, column: 24, scope: !160)
!2677 = !DILocalVariable(name: "b", arg: 2, scope: !160, file: !1, line: 968, type: !157)
!2678 = !DILocation(line: 968, column: 24, scope: !160)
!2679 = !DILocalVariable(name: "buf", arg: 3, scope: !160, file: !1, line: 969, type: !19)
!2680 = !DILocation(line: 969, column: 24, scope: !160)
!2681 = !DILocalVariable(name: "len", arg: 4, scope: !160, file: !1, line: 970, type: !43)
!2682 = !DILocation(line: 970, column: 24, scope: !160)
!2683 = !DILocalVariable(name: "n", scope: !160, file: !1, line: 972, type: !103)
!2684 = !DILocation(line: 972, column: 10, scope: !160)
!2685 = !DILocalVariable(name: "n2", scope: !160, file: !1, line: 972, type: !103)
!2686 = !DILocation(line: 972, column: 13, scope: !160)
!2687 = !DILocalVariable(name: "ret", scope: !160, file: !1, line: 972, type: !103)
!2688 = !DILocation(line: 972, column: 17, scope: !160)
!2689 = !DILocalVariable(name: "bzf", scope: !160, file: !1, line: 973, type: !31)
!2690 = !DILocation(line: 973, column: 12, scope: !160)
!2691 = !DILocation(line: 973, column: 27, scope: !160)
!2692 = !DILocation(line: 973, column: 18, scope: !160)
!2693 = !DILocation(line: 975, column: 4, scope: !2694)
!2694 = distinct !DILexicalBlock(scope: !2695, file: !1, line: 975, column: 4)
!2695 = distinct !DILexicalBlock(scope: !160, file: !1, line: 975, column: 4)
!2696 = !DILocation(line: 975, column: 4, scope: !2695)
!2697 = !DILocation(line: 975, column: 4, scope: !2698)
!2698 = !DILexicalBlockFile(scope: !2694, file: !1, discriminator: 1)
!2699 = !DILocation(line: 975, column: 4, scope: !2700)
!2700 = !DILexicalBlockFile(scope: !2701, file: !1, discriminator: 2)
!2701 = distinct !DILexicalBlock(scope: !2695, file: !1, line: 975, column: 4)
!2702 = !DILocation(line: 975, column: 4, scope: !2703)
!2703 = !DILexicalBlockFile(scope: !2701, file: !1, discriminator: 3)
!2704 = !DILocation(line: 976, column: 8, scope: !2705)
!2705 = distinct !DILexicalBlock(scope: !160, file: !1, line: 976, column: 8)
!2706 = !DILocation(line: 976, column: 12, scope: !2705)
!2707 = !DILocation(line: 976, column: 20, scope: !2705)
!2708 = !DILocation(line: 976, column: 23, scope: !2709)
!2709 = !DILexicalBlockFile(scope: !2705, file: !1, discriminator: 1)
!2710 = !DILocation(line: 976, column: 27, scope: !2709)
!2711 = !DILocation(line: 976, column: 35, scope: !2709)
!2712 = !DILocation(line: 976, column: 38, scope: !2713)
!2713 = !DILexicalBlockFile(scope: !2705, file: !1, discriminator: 2)
!2714 = !DILocation(line: 976, column: 42, scope: !2713)
!2715 = !DILocation(line: 976, column: 8, scope: !2713)
!2716 = !DILocation(line: 977, column: 9, scope: !2717)
!2717 = distinct !DILexicalBlock(scope: !2718, file: !1, line: 977, column: 9)
!2718 = distinct !DILexicalBlock(scope: !2719, file: !1, line: 977, column: 9)
!2719 = distinct !DILexicalBlock(scope: !2705, file: !1, line: 977, column: 7)
!2720 = !DILocation(line: 977, column: 9, scope: !2718)
!2721 = !DILocation(line: 977, column: 9, scope: !2722)
!2722 = !DILexicalBlockFile(scope: !2717, file: !1, discriminator: 1)
!2723 = !DILocation(line: 977, column: 9, scope: !2724)
!2724 = !DILexicalBlockFile(scope: !2725, file: !1, discriminator: 2)
!2725 = distinct !DILexicalBlock(scope: !2718, file: !1, line: 977, column: 9)
!2726 = !DILocation(line: 977, column: 9, scope: !2727)
!2727 = !DILexicalBlockFile(scope: !2725, file: !1, discriminator: 3)
!2728 = !DILocation(line: 977, column: 36, scope: !2729)
!2729 = !DILexicalBlockFile(scope: !2719, file: !1, discriminator: 4)
!2730 = !DILocation(line: 978, column: 10, scope: !2731)
!2731 = distinct !DILexicalBlock(scope: !160, file: !1, line: 978, column: 8)
!2732 = !DILocation(line: 978, column: 15, scope: !2731)
!2733 = !DILocation(line: 978, column: 9, scope: !2731)
!2734 = !DILocation(line: 978, column: 8, scope: !160)
!2735 = !DILocation(line: 979, column: 9, scope: !2736)
!2736 = distinct !DILexicalBlock(scope: !2737, file: !1, line: 979, column: 9)
!2737 = distinct !DILexicalBlock(scope: !2738, file: !1, line: 979, column: 9)
!2738 = distinct !DILexicalBlock(scope: !2731, file: !1, line: 979, column: 7)
!2739 = !DILocation(line: 979, column: 9, scope: !2737)
!2740 = !DILocation(line: 979, column: 9, scope: !2741)
!2741 = !DILexicalBlockFile(scope: !2736, file: !1, discriminator: 1)
!2742 = !DILocation(line: 979, column: 9, scope: !2743)
!2743 = !DILexicalBlockFile(scope: !2744, file: !1, discriminator: 2)
!2744 = distinct !DILexicalBlock(scope: !2737, file: !1, line: 979, column: 9)
!2745 = !DILocation(line: 979, column: 9, scope: !2746)
!2746 = !DILexicalBlockFile(scope: !2744, file: !1, discriminator: 3)
!2747 = !DILocation(line: 979, column: 39, scope: !2748)
!2748 = !DILexicalBlockFile(scope: !2738, file: !1, discriminator: 4)
!2749 = !DILocation(line: 980, column: 15, scope: !2750)
!2750 = distinct !DILexicalBlock(scope: !160, file: !1, line: 980, column: 8)
!2751 = !DILocation(line: 980, column: 20, scope: !2750)
!2752 = !DILocation(line: 980, column: 8, scope: !2750)
!2753 = !DILocation(line: 980, column: 8, scope: !160)
!2754 = !DILocation(line: 981, column: 9, scope: !2755)
!2755 = distinct !DILexicalBlock(scope: !2756, file: !1, line: 981, column: 9)
!2756 = distinct !DILexicalBlock(scope: !2757, file: !1, line: 981, column: 9)
!2757 = distinct !DILexicalBlock(scope: !2750, file: !1, line: 981, column: 7)
!2758 = !DILocation(line: 981, column: 9, scope: !2756)
!2759 = !DILocation(line: 981, column: 9, scope: !2760)
!2760 = !DILexicalBlockFile(scope: !2755, file: !1, discriminator: 1)
!2761 = !DILocation(line: 981, column: 9, scope: !2762)
!2762 = !DILexicalBlockFile(scope: !2763, file: !1, discriminator: 2)
!2763 = distinct !DILexicalBlock(scope: !2756, file: !1, line: 981, column: 9)
!2764 = !DILocation(line: 981, column: 9, scope: !2765)
!2765 = !DILexicalBlockFile(scope: !2763, file: !1, discriminator: 3)
!2766 = !DILocation(line: 981, column: 33, scope: !2767)
!2767 = !DILexicalBlockFile(scope: !2757, file: !1, discriminator: 4)
!2768 = !DILocation(line: 983, column: 8, scope: !2769)
!2769 = distinct !DILexicalBlock(scope: !160, file: !1, line: 983, column: 8)
!2770 = !DILocation(line: 983, column: 12, scope: !2769)
!2771 = !DILocation(line: 983, column: 8, scope: !160)
!2772 = !DILocation(line: 984, column: 9, scope: !2773)
!2773 = distinct !DILexicalBlock(scope: !2774, file: !1, line: 984, column: 9)
!2774 = distinct !DILexicalBlock(scope: !2775, file: !1, line: 984, column: 9)
!2775 = distinct !DILexicalBlock(scope: !2769, file: !1, line: 984, column: 7)
!2776 = !DILocation(line: 984, column: 9, scope: !2774)
!2777 = !DILocation(line: 984, column: 9, scope: !2778)
!2778 = !DILexicalBlockFile(scope: !2773, file: !1, discriminator: 1)
!2779 = !DILocation(line: 984, column: 9, scope: !2780)
!2780 = !DILexicalBlockFile(scope: !2781, file: !1, discriminator: 2)
!2781 = distinct !DILexicalBlock(scope: !2774, file: !1, line: 984, column: 9)
!2782 = !DILocation(line: 984, column: 9, scope: !2783)
!2783 = !DILexicalBlockFile(scope: !2781, file: !1, discriminator: 3)
!2784 = !DILocation(line: 984, column: 27, scope: !2785)
!2785 = !DILexicalBlockFile(scope: !2775, file: !1, discriminator: 4)
!2786 = !DILocation(line: 986, column: 25, scope: !160)
!2787 = !DILocation(line: 986, column: 4, scope: !160)
!2788 = !DILocation(line: 986, column: 9, scope: !160)
!2789 = !DILocation(line: 986, column: 14, scope: !160)
!2790 = !DILocation(line: 986, column: 23, scope: !160)
!2791 = !DILocation(line: 987, column: 25, scope: !160)
!2792 = !DILocation(line: 987, column: 4, scope: !160)
!2793 = !DILocation(line: 987, column: 9, scope: !160)
!2794 = !DILocation(line: 987, column: 14, scope: !160)
!2795 = !DILocation(line: 987, column: 23, scope: !160)
!2796 = !DILocation(line: 989, column: 4, scope: !160)
!2797 = !DILocation(line: 990, column: 7, scope: !2798)
!2798 = distinct !DILexicalBlock(scope: !160, file: !1, line: 989, column: 17)
!2799 = !DILocation(line: 990, column: 12, scope: !2798)
!2800 = !DILocation(line: 990, column: 17, scope: !2798)
!2801 = !DILocation(line: 990, column: 27, scope: !2798)
!2802 = !DILocation(line: 991, column: 28, scope: !2798)
!2803 = !DILocation(line: 991, column: 33, scope: !2798)
!2804 = !DILocation(line: 991, column: 7, scope: !2798)
!2805 = !DILocation(line: 991, column: 12, scope: !2798)
!2806 = !DILocation(line: 991, column: 17, scope: !2798)
!2807 = !DILocation(line: 991, column: 26, scope: !2798)
!2808 = !DILocation(line: 992, column: 32, scope: !2798)
!2809 = !DILocation(line: 992, column: 37, scope: !2798)
!2810 = !DILocation(line: 992, column: 13, scope: !2798)
!2811 = !DILocation(line: 992, column: 11, scope: !2798)
!2812 = !DILocation(line: 993, column: 11, scope: !2813)
!2813 = distinct !DILexicalBlock(scope: !2798, file: !1, line: 993, column: 11)
!2814 = !DILocation(line: 993, column: 15, scope: !2813)
!2815 = !DILocation(line: 993, column: 11, scope: !2798)
!2816 = !DILocation(line: 994, column: 12, scope: !2817)
!2817 = distinct !DILexicalBlock(scope: !2818, file: !1, line: 994, column: 12)
!2818 = distinct !DILexicalBlock(scope: !2819, file: !1, line: 994, column: 12)
!2819 = distinct !DILexicalBlock(scope: !2813, file: !1, line: 994, column: 10)
!2820 = !DILocation(line: 994, column: 12, scope: !2818)
!2821 = !DILocation(line: 994, column: 12, scope: !2822)
!2822 = !DILexicalBlockFile(scope: !2817, file: !1, discriminator: 1)
!2823 = !DILocation(line: 994, column: 12, scope: !2824)
!2824 = !DILexicalBlockFile(scope: !2825, file: !1, discriminator: 2)
!2825 = distinct !DILexicalBlock(scope: !2818, file: !1, line: 994, column: 12)
!2826 = !DILocation(line: 994, column: 12, scope: !2827)
!2827 = !DILexicalBlockFile(scope: !2825, file: !1, discriminator: 3)
!2828 = !DILocation(line: 994, column: 28, scope: !2829)
!2829 = !DILexicalBlockFile(scope: !2819, file: !1, discriminator: 4)
!2830 = !DILocation(line: 996, column: 11, scope: !2831)
!2831 = distinct !DILexicalBlock(scope: !2798, file: !1, line: 996, column: 11)
!2832 = !DILocation(line: 996, column: 16, scope: !2831)
!2833 = !DILocation(line: 996, column: 21, scope: !2831)
!2834 = !DILocation(line: 996, column: 31, scope: !2831)
!2835 = !DILocation(line: 996, column: 11, scope: !2798)
!2836 = !DILocation(line: 997, column: 30, scope: !2837)
!2837 = distinct !DILexicalBlock(scope: !2831, file: !1, line: 996, column: 48)
!2838 = !DILocation(line: 997, column: 35, scope: !2837)
!2839 = !DILocation(line: 997, column: 40, scope: !2837)
!2840 = !DILocation(line: 997, column: 28, scope: !2837)
!2841 = !DILocation(line: 997, column: 12, scope: !2837)
!2842 = !DILocation(line: 998, column: 32, scope: !2837)
!2843 = !DILocation(line: 998, column: 37, scope: !2837)
!2844 = !DILocation(line: 998, column: 31, scope: !2837)
!2845 = !DILocation(line: 999, column: 24, scope: !2837)
!2846 = !DILocation(line: 999, column: 27, scope: !2837)
!2847 = !DILocation(line: 999, column: 32, scope: !2837)
!2848 = !DILocation(line: 998, column: 15, scope: !2837)
!2849 = !DILocation(line: 998, column: 13, scope: !2837)
!2850 = !DILocation(line: 1000, column: 14, scope: !2851)
!2851 = distinct !DILexicalBlock(scope: !2837, file: !1, line: 1000, column: 14)
!2852 = !DILocation(line: 1000, column: 19, scope: !2851)
!2853 = !DILocation(line: 1000, column: 16, scope: !2851)
!2854 = !DILocation(line: 1000, column: 22, scope: !2851)
!2855 = !DILocation(line: 1000, column: 32, scope: !2856)
!2856 = !DILexicalBlockFile(scope: !2851, file: !1, discriminator: 1)
!2857 = !DILocation(line: 1000, column: 37, scope: !2856)
!2858 = !DILocation(line: 1000, column: 25, scope: !2856)
!2859 = !DILocation(line: 1000, column: 14, scope: !2856)
!2860 = !DILocation(line: 1001, column: 15, scope: !2861)
!2861 = distinct !DILexicalBlock(scope: !2862, file: !1, line: 1001, column: 15)
!2862 = distinct !DILexicalBlock(scope: !2863, file: !1, line: 1001, column: 15)
!2863 = distinct !DILexicalBlock(scope: !2851, file: !1, line: 1001, column: 13)
!2864 = !DILocation(line: 1001, column: 15, scope: !2862)
!2865 = !DILocation(line: 1001, column: 15, scope: !2866)
!2866 = !DILexicalBlockFile(scope: !2861, file: !1, discriminator: 1)
!2867 = !DILocation(line: 1001, column: 15, scope: !2868)
!2868 = !DILexicalBlockFile(scope: !2869, file: !1, discriminator: 2)
!2869 = distinct !DILexicalBlock(scope: !2862, file: !1, line: 1001, column: 15)
!2870 = !DILocation(line: 1001, column: 15, scope: !2871)
!2871 = !DILexicalBlockFile(scope: !2869, file: !1, discriminator: 3)
!2872 = !DILocation(line: 1001, column: 39, scope: !2873)
!2873 = !DILexicalBlockFile(scope: !2863, file: !1, discriminator: 4)
!2874 = !DILocation(line: 1002, column: 7, scope: !2837)
!2875 = !DILocation(line: 1004, column: 11, scope: !2876)
!2876 = distinct !DILexicalBlock(scope: !2798, file: !1, line: 1004, column: 11)
!2877 = !DILocation(line: 1004, column: 16, scope: !2876)
!2878 = !DILocation(line: 1004, column: 21, scope: !2876)
!2879 = !DILocation(line: 1004, column: 30, scope: !2876)
!2880 = !DILocation(line: 1004, column: 11, scope: !2798)
!2881 = !DILocation(line: 1005, column: 12, scope: !2882)
!2882 = distinct !DILexicalBlock(scope: !2883, file: !1, line: 1005, column: 12)
!2883 = distinct !DILexicalBlock(scope: !2884, file: !1, line: 1005, column: 12)
!2884 = distinct !DILexicalBlock(scope: !2876, file: !1, line: 1005, column: 10)
!2885 = !DILocation(line: 1005, column: 12, scope: !2883)
!2886 = !DILocation(line: 1005, column: 12, scope: !2887)
!2887 = !DILexicalBlockFile(scope: !2882, file: !1, discriminator: 1)
!2888 = !DILocation(line: 1005, column: 12, scope: !2889)
!2889 = !DILexicalBlockFile(scope: !2890, file: !1, discriminator: 2)
!2890 = distinct !DILexicalBlock(scope: !2883, file: !1, line: 1005, column: 12)
!2891 = !DILocation(line: 1005, column: 12, scope: !2892)
!2892 = !DILexicalBlockFile(scope: !2890, file: !1, discriminator: 3)
!2893 = !DILocation(line: 1005, column: 30, scope: !2894)
!2894 = !DILexicalBlockFile(scope: !2884, file: !1, discriminator: 4)
!2895 = !DILocation(line: 989, column: 4, scope: !2896)
!2896 = !DILexicalBlockFile(scope: !160, file: !1, discriminator: 1)
!2897 = !DILocation(line: 1007, column: 1, scope: !160)
!2898 = !DILocalVariable(name: "bzerror", arg: 1, scope: !163, file: !1, line: 1012, type: !159)
!2899 = !DILocation(line: 1012, column: 35, scope: !163)
!2900 = !DILocalVariable(name: "b", arg: 2, scope: !163, file: !1, line: 1013, type: !157)
!2901 = !DILocation(line: 1013, column: 35, scope: !163)
!2902 = !DILocalVariable(name: "abandon", arg: 3, scope: !163, file: !1, line: 1014, type: !43)
!2903 = !DILocation(line: 1014, column: 35, scope: !163)
!2904 = !DILocalVariable(name: "nbytes_in", arg: 4, scope: !163, file: !1, line: 1015, type: !166)
!2905 = !DILocation(line: 1015, column: 35, scope: !163)
!2906 = !DILocalVariable(name: "nbytes_out", arg: 5, scope: !163, file: !1, line: 1016, type: !166)
!2907 = !DILocation(line: 1016, column: 35, scope: !163)
!2908 = !DILocation(line: 1018, column: 25, scope: !163)
!2909 = !DILocation(line: 1018, column: 34, scope: !163)
!2910 = !DILocation(line: 1018, column: 37, scope: !163)
!2911 = !DILocation(line: 1019, column: 25, scope: !163)
!2912 = !DILocation(line: 1019, column: 42, scope: !163)
!2913 = !DILocation(line: 1018, column: 4, scope: !163)
!2914 = !DILocation(line: 1020, column: 1, scope: !163)
!2915 = !DILocalVariable(name: "bzerror", arg: 1, scope: !167, file: !1, line: 1024, type: !159)
!2916 = !DILocation(line: 1024, column: 35, scope: !167)
!2917 = !DILocalVariable(name: "b", arg: 2, scope: !167, file: !1, line: 1025, type: !157)
!2918 = !DILocation(line: 1025, column: 35, scope: !167)
!2919 = !DILocalVariable(name: "abandon", arg: 3, scope: !167, file: !1, line: 1026, type: !43)
!2920 = !DILocation(line: 1026, column: 35, scope: !167)
!2921 = !DILocalVariable(name: "nbytes_in_lo32", arg: 4, scope: !167, file: !1, line: 1027, type: !166)
!2922 = !DILocation(line: 1027, column: 35, scope: !167)
!2923 = !DILocalVariable(name: "nbytes_in_hi32", arg: 5, scope: !167, file: !1, line: 1028, type: !166)
!2924 = !DILocation(line: 1028, column: 35, scope: !167)
!2925 = !DILocalVariable(name: "nbytes_out_lo32", arg: 6, scope: !167, file: !1, line: 1029, type: !166)
!2926 = !DILocation(line: 1029, column: 35, scope: !167)
!2927 = !DILocalVariable(name: "nbytes_out_hi32", arg: 7, scope: !167, file: !1, line: 1030, type: !166)
!2928 = !DILocation(line: 1030, column: 35, scope: !167)
!2929 = !DILocalVariable(name: "n", scope: !167, file: !1, line: 1032, type: !103)
!2930 = !DILocation(line: 1032, column: 12, scope: !167)
!2931 = !DILocalVariable(name: "n2", scope: !167, file: !1, line: 1032, type: !103)
!2932 = !DILocation(line: 1032, column: 15, scope: !167)
!2933 = !DILocalVariable(name: "ret", scope: !167, file: !1, line: 1032, type: !103)
!2934 = !DILocation(line: 1032, column: 19, scope: !167)
!2935 = !DILocalVariable(name: "bzf", scope: !167, file: !1, line: 1033, type: !31)
!2936 = !DILocation(line: 1033, column: 12, scope: !167)
!2937 = !DILocation(line: 1033, column: 27, scope: !167)
!2938 = !DILocation(line: 1033, column: 18, scope: !167)
!2939 = !DILocation(line: 1035, column: 8, scope: !2940)
!2940 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1035, column: 8)
!2941 = !DILocation(line: 1035, column: 12, scope: !2940)
!2942 = !DILocation(line: 1035, column: 8, scope: !167)
!2943 = !DILocation(line: 1036, column: 9, scope: !2944)
!2944 = distinct !DILexicalBlock(scope: !2945, file: !1, line: 1036, column: 9)
!2945 = distinct !DILexicalBlock(scope: !2946, file: !1, line: 1036, column: 9)
!2946 = distinct !DILexicalBlock(scope: !2940, file: !1, line: 1036, column: 7)
!2947 = !DILocation(line: 1036, column: 9, scope: !2945)
!2948 = !DILocation(line: 1036, column: 9, scope: !2949)
!2949 = !DILexicalBlockFile(scope: !2944, file: !1, discriminator: 1)
!2950 = !DILocation(line: 1036, column: 9, scope: !2951)
!2951 = !DILexicalBlockFile(scope: !2952, file: !1, discriminator: 2)
!2952 = distinct !DILexicalBlock(scope: !2945, file: !1, line: 1036, column: 9)
!2953 = !DILocation(line: 1036, column: 9, scope: !2954)
!2954 = !DILexicalBlockFile(scope: !2952, file: !1, discriminator: 3)
!2955 = !DILocation(line: 1036, column: 27, scope: !2956)
!2956 = !DILexicalBlockFile(scope: !2946, file: !1, discriminator: 4)
!2957 = !DILocation(line: 1037, column: 10, scope: !2958)
!2958 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1037, column: 8)
!2959 = !DILocation(line: 1037, column: 15, scope: !2958)
!2960 = !DILocation(line: 1037, column: 9, scope: !2958)
!2961 = !DILocation(line: 1037, column: 8, scope: !167)
!2962 = !DILocation(line: 1038, column: 9, scope: !2963)
!2963 = distinct !DILexicalBlock(scope: !2964, file: !1, line: 1038, column: 9)
!2964 = distinct !DILexicalBlock(scope: !2965, file: !1, line: 1038, column: 9)
!2965 = distinct !DILexicalBlock(scope: !2958, file: !1, line: 1038, column: 7)
!2966 = !DILocation(line: 1038, column: 9, scope: !2964)
!2967 = !DILocation(line: 1038, column: 9, scope: !2968)
!2968 = !DILexicalBlockFile(scope: !2963, file: !1, discriminator: 1)
!2969 = !DILocation(line: 1038, column: 9, scope: !2970)
!2970 = !DILexicalBlockFile(scope: !2971, file: !1, discriminator: 2)
!2971 = distinct !DILexicalBlock(scope: !2964, file: !1, line: 1038, column: 9)
!2972 = !DILocation(line: 1038, column: 9, scope: !2973)
!2973 = !DILexicalBlockFile(scope: !2971, file: !1, discriminator: 3)
!2974 = !DILocation(line: 1038, column: 39, scope: !2975)
!2975 = !DILexicalBlockFile(scope: !2965, file: !1, discriminator: 4)
!2976 = !DILocation(line: 1039, column: 15, scope: !2977)
!2977 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1039, column: 8)
!2978 = !DILocation(line: 1039, column: 20, scope: !2977)
!2979 = !DILocation(line: 1039, column: 8, scope: !2977)
!2980 = !DILocation(line: 1039, column: 8, scope: !167)
!2981 = !DILocation(line: 1040, column: 9, scope: !2982)
!2982 = distinct !DILexicalBlock(scope: !2983, file: !1, line: 1040, column: 9)
!2983 = distinct !DILexicalBlock(scope: !2984, file: !1, line: 1040, column: 9)
!2984 = distinct !DILexicalBlock(scope: !2977, file: !1, line: 1040, column: 7)
!2985 = !DILocation(line: 1040, column: 9, scope: !2983)
!2986 = !DILocation(line: 1040, column: 9, scope: !2987)
!2987 = !DILexicalBlockFile(scope: !2982, file: !1, discriminator: 1)
!2988 = !DILocation(line: 1040, column: 9, scope: !2989)
!2989 = !DILexicalBlockFile(scope: !2990, file: !1, discriminator: 2)
!2990 = distinct !DILexicalBlock(scope: !2983, file: !1, line: 1040, column: 9)
!2991 = !DILocation(line: 1040, column: 9, scope: !2992)
!2992 = !DILexicalBlockFile(scope: !2990, file: !1, discriminator: 3)
!2993 = !DILocation(line: 1040, column: 33, scope: !2994)
!2994 = !DILexicalBlockFile(scope: !2984, file: !1, discriminator: 4)
!2995 = !DILocation(line: 1042, column: 8, scope: !2996)
!2996 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1042, column: 8)
!2997 = !DILocation(line: 1042, column: 23, scope: !2996)
!2998 = !DILocation(line: 1042, column: 8, scope: !167)
!2999 = !DILocation(line: 1042, column: 33, scope: !3000)
!3000 = !DILexicalBlockFile(scope: !2996, file: !1, discriminator: 1)
!3001 = !DILocation(line: 1042, column: 48, scope: !3000)
!3002 = !DILocation(line: 1042, column: 32, scope: !3000)
!3003 = !DILocation(line: 1043, column: 8, scope: !3004)
!3004 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1043, column: 8)
!3005 = !DILocation(line: 1043, column: 23, scope: !3004)
!3006 = !DILocation(line: 1043, column: 8, scope: !167)
!3007 = !DILocation(line: 1043, column: 33, scope: !3008)
!3008 = !DILexicalBlockFile(scope: !3004, file: !1, discriminator: 1)
!3009 = !DILocation(line: 1043, column: 48, scope: !3008)
!3010 = !DILocation(line: 1043, column: 32, scope: !3008)
!3011 = !DILocation(line: 1044, column: 8, scope: !3012)
!3012 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1044, column: 8)
!3013 = !DILocation(line: 1044, column: 24, scope: !3012)
!3014 = !DILocation(line: 1044, column: 8, scope: !167)
!3015 = !DILocation(line: 1044, column: 34, scope: !3016)
!3016 = !DILexicalBlockFile(scope: !3012, file: !1, discriminator: 1)
!3017 = !DILocation(line: 1044, column: 50, scope: !3016)
!3018 = !DILocation(line: 1044, column: 33, scope: !3016)
!3019 = !DILocation(line: 1045, column: 8, scope: !3020)
!3020 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1045, column: 8)
!3021 = !DILocation(line: 1045, column: 24, scope: !3020)
!3022 = !DILocation(line: 1045, column: 8, scope: !167)
!3023 = !DILocation(line: 1045, column: 34, scope: !3024)
!3024 = !DILexicalBlockFile(scope: !3020, file: !1, discriminator: 1)
!3025 = !DILocation(line: 1045, column: 50, scope: !3024)
!3026 = !DILocation(line: 1045, column: 33, scope: !3024)
!3027 = !DILocation(line: 1047, column: 10, scope: !3028)
!3028 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1047, column: 8)
!3029 = !DILocation(line: 1047, column: 19, scope: !3028)
!3030 = !DILocation(line: 1047, column: 22, scope: !3031)
!3031 = !DILexicalBlockFile(scope: !3028, file: !1, discriminator: 1)
!3032 = !DILocation(line: 1047, column: 27, scope: !3031)
!3033 = !DILocation(line: 1047, column: 35, scope: !3031)
!3034 = !DILocation(line: 1047, column: 8, scope: !3031)
!3035 = !DILocation(line: 1048, column: 7, scope: !3036)
!3036 = distinct !DILexicalBlock(scope: !3028, file: !1, line: 1047, column: 45)
!3037 = !DILocation(line: 1049, column: 10, scope: !3038)
!3038 = distinct !DILexicalBlock(scope: !3036, file: !1, line: 1048, column: 20)
!3039 = !DILocation(line: 1049, column: 15, scope: !3038)
!3040 = !DILocation(line: 1049, column: 20, scope: !3038)
!3041 = !DILocation(line: 1049, column: 30, scope: !3038)
!3042 = !DILocation(line: 1050, column: 31, scope: !3038)
!3043 = !DILocation(line: 1050, column: 36, scope: !3038)
!3044 = !DILocation(line: 1050, column: 10, scope: !3038)
!3045 = !DILocation(line: 1050, column: 15, scope: !3038)
!3046 = !DILocation(line: 1050, column: 20, scope: !3038)
!3047 = !DILocation(line: 1050, column: 29, scope: !3038)
!3048 = !DILocation(line: 1051, column: 35, scope: !3038)
!3049 = !DILocation(line: 1051, column: 40, scope: !3038)
!3050 = !DILocation(line: 1051, column: 16, scope: !3038)
!3051 = !DILocation(line: 1051, column: 14, scope: !3038)
!3052 = !DILocation(line: 1052, column: 14, scope: !3053)
!3053 = distinct !DILexicalBlock(scope: !3038, file: !1, line: 1052, column: 14)
!3054 = !DILocation(line: 1052, column: 18, scope: !3053)
!3055 = !DILocation(line: 1052, column: 34, scope: !3053)
!3056 = !DILocation(line: 1052, column: 37, scope: !3057)
!3057 = !DILexicalBlockFile(scope: !3053, file: !1, discriminator: 1)
!3058 = !DILocation(line: 1052, column: 41, scope: !3057)
!3059 = !DILocation(line: 1052, column: 14, scope: !3057)
!3060 = !DILocation(line: 1053, column: 15, scope: !3061)
!3061 = distinct !DILexicalBlock(scope: !3062, file: !1, line: 1053, column: 15)
!3062 = distinct !DILexicalBlock(scope: !3063, file: !1, line: 1053, column: 15)
!3063 = distinct !DILexicalBlock(scope: !3053, file: !1, line: 1053, column: 13)
!3064 = !DILocation(line: 1053, column: 15, scope: !3062)
!3065 = !DILocation(line: 1053, column: 15, scope: !3066)
!3066 = !DILexicalBlockFile(scope: !3061, file: !1, discriminator: 1)
!3067 = !DILocation(line: 1053, column: 15, scope: !3068)
!3068 = !DILexicalBlockFile(scope: !3069, file: !1, discriminator: 2)
!3069 = distinct !DILexicalBlock(scope: !3062, file: !1, line: 1053, column: 15)
!3070 = !DILocation(line: 1053, column: 15, scope: !3071)
!3071 = !DILexicalBlockFile(scope: !3069, file: !1, discriminator: 3)
!3072 = !DILocation(line: 1053, column: 31, scope: !3073)
!3073 = !DILexicalBlockFile(scope: !3063, file: !1, discriminator: 4)
!3074 = !DILocation(line: 1055, column: 14, scope: !3075)
!3075 = distinct !DILexicalBlock(scope: !3038, file: !1, line: 1055, column: 14)
!3076 = !DILocation(line: 1055, column: 19, scope: !3075)
!3077 = !DILocation(line: 1055, column: 24, scope: !3075)
!3078 = !DILocation(line: 1055, column: 34, scope: !3075)
!3079 = !DILocation(line: 1055, column: 14, scope: !3038)
!3080 = !DILocation(line: 1056, column: 33, scope: !3081)
!3081 = distinct !DILexicalBlock(scope: !3075, file: !1, line: 1055, column: 51)
!3082 = !DILocation(line: 1056, column: 38, scope: !3081)
!3083 = !DILocation(line: 1056, column: 43, scope: !3081)
!3084 = !DILocation(line: 1056, column: 31, scope: !3081)
!3085 = !DILocation(line: 1056, column: 15, scope: !3081)
!3086 = !DILocation(line: 1057, column: 35, scope: !3081)
!3087 = !DILocation(line: 1057, column: 40, scope: !3081)
!3088 = !DILocation(line: 1057, column: 34, scope: !3081)
!3089 = !DILocation(line: 1058, column: 27, scope: !3081)
!3090 = !DILocation(line: 1058, column: 30, scope: !3081)
!3091 = !DILocation(line: 1058, column: 35, scope: !3081)
!3092 = !DILocation(line: 1057, column: 18, scope: !3081)
!3093 = !DILocation(line: 1057, column: 16, scope: !3081)
!3094 = !DILocation(line: 1059, column: 17, scope: !3095)
!3095 = distinct !DILexicalBlock(scope: !3081, file: !1, line: 1059, column: 17)
!3096 = !DILocation(line: 1059, column: 22, scope: !3095)
!3097 = !DILocation(line: 1059, column: 19, scope: !3095)
!3098 = !DILocation(line: 1059, column: 25, scope: !3095)
!3099 = !DILocation(line: 1059, column: 35, scope: !3100)
!3100 = !DILexicalBlockFile(scope: !3095, file: !1, discriminator: 1)
!3101 = !DILocation(line: 1059, column: 40, scope: !3100)
!3102 = !DILocation(line: 1059, column: 28, scope: !3100)
!3103 = !DILocation(line: 1059, column: 17, scope: !3100)
!3104 = !DILocation(line: 1060, column: 18, scope: !3105)
!3105 = distinct !DILexicalBlock(scope: !3106, file: !1, line: 1060, column: 18)
!3106 = distinct !DILexicalBlock(scope: !3107, file: !1, line: 1060, column: 18)
!3107 = distinct !DILexicalBlock(scope: !3095, file: !1, line: 1060, column: 16)
!3108 = !DILocation(line: 1060, column: 18, scope: !3106)
!3109 = !DILocation(line: 1060, column: 18, scope: !3110)
!3110 = !DILexicalBlockFile(scope: !3105, file: !1, discriminator: 1)
!3111 = !DILocation(line: 1060, column: 18, scope: !3112)
!3112 = !DILexicalBlockFile(scope: !3113, file: !1, discriminator: 2)
!3113 = distinct !DILexicalBlock(scope: !3106, file: !1, line: 1060, column: 18)
!3114 = !DILocation(line: 1060, column: 18, scope: !3115)
!3115 = !DILexicalBlockFile(scope: !3113, file: !1, discriminator: 3)
!3116 = !DILocation(line: 1060, column: 42, scope: !3117)
!3117 = !DILexicalBlockFile(scope: !3107, file: !1, discriminator: 4)
!3118 = !DILocation(line: 1061, column: 10, scope: !3081)
!3119 = !DILocation(line: 1063, column: 14, scope: !3120)
!3120 = distinct !DILexicalBlock(scope: !3038, file: !1, line: 1063, column: 14)
!3121 = !DILocation(line: 1063, column: 18, scope: !3120)
!3122 = !DILocation(line: 1063, column: 14, scope: !3038)
!3123 = !DILocation(line: 1063, column: 36, scope: !3124)
!3124 = !DILexicalBlockFile(scope: !3120, file: !1, discriminator: 1)
!3125 = !DILocation(line: 1048, column: 7, scope: !3126)
!3126 = !DILexicalBlockFile(scope: !3036, file: !1, discriminator: 1)
!3127 = !DILocation(line: 1065, column: 4, scope: !3036)
!3128 = !DILocation(line: 1067, column: 10, scope: !3129)
!3129 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1067, column: 9)
!3130 = !DILocation(line: 1067, column: 18, scope: !3129)
!3131 = !DILocation(line: 1067, column: 31, scope: !3132)
!3132 = !DILexicalBlockFile(scope: !3129, file: !1, discriminator: 1)
!3133 = !DILocation(line: 1067, column: 36, scope: !3132)
!3134 = !DILocation(line: 1067, column: 22, scope: !3132)
!3135 = !DILocation(line: 1067, column: 9, scope: !3132)
!3136 = !DILocation(line: 1068, column: 16, scope: !3137)
!3137 = distinct !DILexicalBlock(scope: !3129, file: !1, line: 1067, column: 47)
!3138 = !DILocation(line: 1068, column: 21, scope: !3137)
!3139 = !DILocation(line: 1068, column: 7, scope: !3137)
!3140 = !DILocation(line: 1069, column: 18, scope: !3141)
!3141 = distinct !DILexicalBlock(scope: !3137, file: !1, line: 1069, column: 11)
!3142 = !DILocation(line: 1069, column: 23, scope: !3141)
!3143 = !DILocation(line: 1069, column: 11, scope: !3141)
!3144 = !DILocation(line: 1069, column: 11, scope: !3137)
!3145 = !DILocation(line: 1070, column: 12, scope: !3146)
!3146 = distinct !DILexicalBlock(scope: !3147, file: !1, line: 1070, column: 12)
!3147 = distinct !DILexicalBlock(scope: !3148, file: !1, line: 1070, column: 12)
!3148 = distinct !DILexicalBlock(scope: !3141, file: !1, line: 1070, column: 10)
!3149 = !DILocation(line: 1070, column: 12, scope: !3147)
!3150 = !DILocation(line: 1070, column: 12, scope: !3151)
!3151 = !DILexicalBlockFile(scope: !3146, file: !1, discriminator: 1)
!3152 = !DILocation(line: 1070, column: 12, scope: !3153)
!3153 = !DILexicalBlockFile(scope: !3154, file: !1, discriminator: 2)
!3154 = distinct !DILexicalBlock(scope: !3147, file: !1, line: 1070, column: 12)
!3155 = !DILocation(line: 1070, column: 12, scope: !3156)
!3156 = !DILexicalBlockFile(scope: !3154, file: !1, discriminator: 3)
!3157 = !DILocation(line: 1070, column: 36, scope: !3158)
!3158 = !DILexicalBlockFile(scope: !3148, file: !1, discriminator: 4)
!3159 = !DILocation(line: 1071, column: 4, scope: !3137)
!3160 = !DILocation(line: 1073, column: 8, scope: !3161)
!3161 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1073, column: 8)
!3162 = !DILocation(line: 1073, column: 23, scope: !3161)
!3163 = !DILocation(line: 1073, column: 8, scope: !167)
!3164 = !DILocation(line: 1074, column: 25, scope: !3161)
!3165 = !DILocation(line: 1074, column: 30, scope: !3161)
!3166 = !DILocation(line: 1074, column: 35, scope: !3161)
!3167 = !DILocation(line: 1074, column: 8, scope: !3161)
!3168 = !DILocation(line: 1074, column: 23, scope: !3161)
!3169 = !DILocation(line: 1074, column: 7, scope: !3161)
!3170 = !DILocation(line: 1075, column: 8, scope: !3171)
!3171 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1075, column: 8)
!3172 = !DILocation(line: 1075, column: 23, scope: !3171)
!3173 = !DILocation(line: 1075, column: 8, scope: !167)
!3174 = !DILocation(line: 1076, column: 25, scope: !3171)
!3175 = !DILocation(line: 1076, column: 30, scope: !3171)
!3176 = !DILocation(line: 1076, column: 35, scope: !3171)
!3177 = !DILocation(line: 1076, column: 8, scope: !3171)
!3178 = !DILocation(line: 1076, column: 23, scope: !3171)
!3179 = !DILocation(line: 1076, column: 7, scope: !3171)
!3180 = !DILocation(line: 1077, column: 8, scope: !3181)
!3181 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1077, column: 8)
!3182 = !DILocation(line: 1077, column: 24, scope: !3181)
!3183 = !DILocation(line: 1077, column: 8, scope: !167)
!3184 = !DILocation(line: 1078, column: 26, scope: !3181)
!3185 = !DILocation(line: 1078, column: 31, scope: !3181)
!3186 = !DILocation(line: 1078, column: 36, scope: !3181)
!3187 = !DILocation(line: 1078, column: 8, scope: !3181)
!3188 = !DILocation(line: 1078, column: 24, scope: !3181)
!3189 = !DILocation(line: 1078, column: 7, scope: !3181)
!3190 = !DILocation(line: 1079, column: 8, scope: !3191)
!3191 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1079, column: 8)
!3192 = !DILocation(line: 1079, column: 24, scope: !3191)
!3193 = !DILocation(line: 1079, column: 8, scope: !167)
!3194 = !DILocation(line: 1080, column: 26, scope: !3191)
!3195 = !DILocation(line: 1080, column: 31, scope: !3191)
!3196 = !DILocation(line: 1080, column: 36, scope: !3191)
!3197 = !DILocation(line: 1080, column: 8, scope: !3191)
!3198 = !DILocation(line: 1080, column: 24, scope: !3191)
!3199 = !DILocation(line: 1080, column: 7, scope: !3191)
!3200 = !DILocation(line: 1082, column: 4, scope: !3201)
!3201 = distinct !DILexicalBlock(scope: !3202, file: !1, line: 1082, column: 4)
!3202 = distinct !DILexicalBlock(scope: !167, file: !1, line: 1082, column: 4)
!3203 = !DILocation(line: 1082, column: 4, scope: !3202)
!3204 = !DILocation(line: 1082, column: 4, scope: !3205)
!3205 = !DILexicalBlockFile(scope: !3201, file: !1, discriminator: 1)
!3206 = !DILocation(line: 1082, column: 4, scope: !3207)
!3207 = !DILexicalBlockFile(scope: !3208, file: !1, discriminator: 2)
!3208 = distinct !DILexicalBlock(scope: !3202, file: !1, line: 1082, column: 4)
!3209 = !DILocation(line: 1082, column: 4, scope: !3210)
!3210 = !DILexicalBlockFile(scope: !3208, file: !1, discriminator: 3)
!3211 = !DILocation(line: 1083, column: 26, scope: !167)
!3212 = !DILocation(line: 1083, column: 31, scope: !167)
!3213 = !DILocation(line: 1083, column: 4, scope: !167)
!3214 = !DILocation(line: 1084, column: 11, scope: !167)
!3215 = !DILocation(line: 1084, column: 4, scope: !167)
!3216 = !DILocation(line: 1085, column: 1, scope: !167)
!3217 = !DILocation(line: 1085, column: 1, scope: !3218)
!3218 = !DILexicalBlockFile(scope: !167, file: !1, discriminator: 1)
!3219 = !DILocalVariable(name: "bzerror", arg: 1, scope: !170, file: !1, line: 1090, type: !159)
!3220 = !DILocation(line: 1090, column: 28, scope: !170)
!3221 = !DILocalVariable(name: "f", arg: 2, scope: !170, file: !1, line: 1091, type: !36)
!3222 = !DILocation(line: 1091, column: 28, scope: !170)
!3223 = !DILocalVariable(name: "verbosity", arg: 3, scope: !170, file: !1, line: 1092, type: !43)
!3224 = !DILocation(line: 1092, column: 28, scope: !170)
!3225 = !DILocalVariable(name: "small", arg: 4, scope: !170, file: !1, line: 1093, type: !43)
!3226 = !DILocation(line: 1093, column: 28, scope: !170)
!3227 = !DILocalVariable(name: "unused", arg: 5, scope: !170, file: !1, line: 1094, type: !19)
!3228 = !DILocation(line: 1094, column: 28, scope: !170)
!3229 = !DILocalVariable(name: "nUnused", arg: 6, scope: !170, file: !1, line: 1095, type: !43)
!3230 = !DILocation(line: 1095, column: 28, scope: !170)
!3231 = !DILocalVariable(name: "bzf", scope: !170, file: !1, line: 1097, type: !31)
!3232 = !DILocation(line: 1097, column: 12, scope: !170)
!3233 = !DILocalVariable(name: "ret", scope: !170, file: !1, line: 1098, type: !43)
!3234 = !DILocation(line: 1098, column: 12, scope: !170)
!3235 = !DILocation(line: 1100, column: 4, scope: !3236)
!3236 = distinct !DILexicalBlock(scope: !3237, file: !1, line: 1100, column: 4)
!3237 = distinct !DILexicalBlock(scope: !170, file: !1, line: 1100, column: 4)
!3238 = !DILocation(line: 1100, column: 4, scope: !3237)
!3239 = !DILocation(line: 1100, column: 4, scope: !3240)
!3240 = !DILexicalBlockFile(scope: !3236, file: !1, discriminator: 1)
!3241 = !DILocation(line: 1100, column: 4, scope: !3242)
!3242 = !DILexicalBlockFile(scope: !3243, file: !1, discriminator: 2)
!3243 = distinct !DILexicalBlock(scope: !3237, file: !1, line: 1100, column: 4)
!3244 = !DILocation(line: 1100, column: 4, scope: !3245)
!3245 = !DILexicalBlockFile(scope: !3243, file: !1, discriminator: 3)
!3246 = !DILocation(line: 1102, column: 8, scope: !3247)
!3247 = distinct !DILexicalBlock(scope: !170, file: !1, line: 1102, column: 8)
!3248 = !DILocation(line: 1102, column: 10, scope: !3247)
!3249 = !DILocation(line: 1102, column: 18, scope: !3247)
!3250 = !DILocation(line: 1103, column: 9, scope: !3247)
!3251 = !DILocation(line: 1103, column: 15, scope: !3247)
!3252 = !DILocation(line: 1103, column: 20, scope: !3247)
!3253 = !DILocation(line: 1103, column: 23, scope: !3254)
!3254 = !DILexicalBlockFile(scope: !3247, file: !1, discriminator: 1)
!3255 = !DILocation(line: 1103, column: 29, scope: !3254)
!3256 = !DILocation(line: 1103, column: 35, scope: !3254)
!3257 = !DILocation(line: 1104, column: 9, scope: !3247)
!3258 = !DILocation(line: 1104, column: 19, scope: !3247)
!3259 = !DILocation(line: 1104, column: 23, scope: !3247)
!3260 = !DILocation(line: 1104, column: 26, scope: !3254)
!3261 = !DILocation(line: 1104, column: 36, scope: !3254)
!3262 = !DILocation(line: 1104, column: 41, scope: !3254)
!3263 = !DILocation(line: 1105, column: 9, scope: !3247)
!3264 = !DILocation(line: 1105, column: 16, scope: !3247)
!3265 = !DILocation(line: 1105, column: 24, scope: !3247)
!3266 = !DILocation(line: 1105, column: 27, scope: !3254)
!3267 = !DILocation(line: 1105, column: 35, scope: !3254)
!3268 = !DILocation(line: 1105, column: 41, scope: !3254)
!3269 = !DILocation(line: 1106, column: 9, scope: !3247)
!3270 = !DILocation(line: 1106, column: 16, scope: !3247)
!3271 = !DILocation(line: 1106, column: 24, scope: !3247)
!3272 = !DILocation(line: 1106, column: 28, scope: !3254)
!3273 = !DILocation(line: 1106, column: 36, scope: !3254)
!3274 = !DILocation(line: 1106, column: 40, scope: !3254)
!3275 = !DILocation(line: 1106, column: 43, scope: !3276)
!3276 = !DILexicalBlockFile(scope: !3247, file: !1, discriminator: 2)
!3277 = !DILocation(line: 1106, column: 51, scope: !3276)
!3278 = !DILocation(line: 1102, column: 8, scope: !3279)
!3279 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 1)
!3280 = !DILocation(line: 1107, column: 9, scope: !3281)
!3281 = distinct !DILexicalBlock(scope: !3282, file: !1, line: 1107, column: 9)
!3282 = distinct !DILexicalBlock(scope: !3283, file: !1, line: 1107, column: 9)
!3283 = distinct !DILexicalBlock(scope: !3247, file: !1, line: 1107, column: 7)
!3284 = !DILocation(line: 1107, column: 9, scope: !3282)
!3285 = !DILocation(line: 1107, column: 9, scope: !3286)
!3286 = !DILexicalBlockFile(scope: !3281, file: !1, discriminator: 1)
!3287 = !DILocation(line: 1107, column: 9, scope: !3288)
!3288 = !DILexicalBlockFile(scope: !3289, file: !1, discriminator: 2)
!3289 = distinct !DILexicalBlock(scope: !3282, file: !1, line: 1107, column: 9)
!3290 = !DILocation(line: 1107, column: 9, scope: !3291)
!3291 = !DILexicalBlockFile(scope: !3289, file: !1, discriminator: 3)
!3292 = !DILocation(line: 1107, column: 36, scope: !3293)
!3293 = !DILexicalBlockFile(scope: !3283, file: !1, discriminator: 4)
!3294 = !DILocation(line: 1109, column: 15, scope: !3295)
!3295 = distinct !DILexicalBlock(scope: !170, file: !1, line: 1109, column: 8)
!3296 = !DILocation(line: 1109, column: 8, scope: !3295)
!3297 = !DILocation(line: 1109, column: 8, scope: !170)
!3298 = !DILocation(line: 1110, column: 9, scope: !3299)
!3299 = distinct !DILexicalBlock(scope: !3300, file: !1, line: 1110, column: 9)
!3300 = distinct !DILexicalBlock(scope: !3301, file: !1, line: 1110, column: 9)
!3301 = distinct !DILexicalBlock(scope: !3295, file: !1, line: 1110, column: 7)
!3302 = !DILocation(line: 1110, column: 9, scope: !3300)
!3303 = !DILocation(line: 1110, column: 9, scope: !3304)
!3304 = !DILexicalBlockFile(scope: !3299, file: !1, discriminator: 1)
!3305 = !DILocation(line: 1110, column: 9, scope: !3306)
!3306 = !DILexicalBlockFile(scope: !3307, file: !1, discriminator: 2)
!3307 = distinct !DILexicalBlock(scope: !3300, file: !1, line: 1110, column: 9)
!3308 = !DILocation(line: 1110, column: 9, scope: !3309)
!3309 = !DILexicalBlockFile(scope: !3307, file: !1, discriminator: 3)
!3310 = !DILocation(line: 1110, column: 33, scope: !3311)
!3311 = !DILexicalBlockFile(scope: !3301, file: !1, discriminator: 4)
!3312 = !DILocation(line: 1112, column: 10, scope: !170)
!3313 = !DILocation(line: 1112, column: 8, scope: !170)
!3314 = !DILocation(line: 1113, column: 8, scope: !3315)
!3315 = distinct !DILexicalBlock(scope: !170, file: !1, line: 1113, column: 8)
!3316 = !DILocation(line: 1113, column: 12, scope: !3315)
!3317 = !DILocation(line: 1113, column: 8, scope: !170)
!3318 = !DILocation(line: 1114, column: 9, scope: !3319)
!3319 = distinct !DILexicalBlock(scope: !3320, file: !1, line: 1114, column: 9)
!3320 = distinct !DILexicalBlock(scope: !3321, file: !1, line: 1114, column: 9)
!3321 = distinct !DILexicalBlock(scope: !3315, file: !1, line: 1114, column: 7)
!3322 = !DILocation(line: 1114, column: 9, scope: !3320)
!3323 = !DILocation(line: 1114, column: 9, scope: !3324)
!3324 = !DILexicalBlockFile(scope: !3319, file: !1, discriminator: 1)
!3325 = !DILocation(line: 1114, column: 9, scope: !3326)
!3326 = !DILexicalBlockFile(scope: !3327, file: !1, discriminator: 2)
!3327 = distinct !DILexicalBlock(scope: !3320, file: !1, line: 1114, column: 9)
!3328 = !DILocation(line: 1114, column: 9, scope: !3329)
!3329 = !DILexicalBlockFile(scope: !3327, file: !1, discriminator: 3)
!3330 = !DILocation(line: 1114, column: 34, scope: !3331)
!3331 = !DILexicalBlockFile(scope: !3321, file: !1, discriminator: 4)
!3332 = !DILocation(line: 1116, column: 4, scope: !3333)
!3333 = distinct !DILexicalBlock(scope: !3334, file: !1, line: 1116, column: 4)
!3334 = distinct !DILexicalBlock(scope: !170, file: !1, line: 1116, column: 4)
!3335 = !DILocation(line: 1116, column: 4, scope: !3334)
!3336 = !DILocation(line: 1116, column: 4, scope: !3337)
!3337 = !DILexicalBlockFile(scope: !3333, file: !1, discriminator: 1)
!3338 = !DILocation(line: 1116, column: 4, scope: !3339)
!3339 = !DILexicalBlockFile(scope: !3340, file: !1, discriminator: 2)
!3340 = distinct !DILexicalBlock(scope: !3334, file: !1, line: 1116, column: 4)
!3341 = !DILocation(line: 1116, column: 4, scope: !3342)
!3342 = !DILexicalBlockFile(scope: !3340, file: !1, discriminator: 3)
!3343 = !DILocation(line: 1118, column: 4, scope: !170)
!3344 = !DILocation(line: 1118, column: 9, scope: !170)
!3345 = !DILocation(line: 1118, column: 23, scope: !170)
!3346 = !DILocation(line: 1119, column: 25, scope: !170)
!3347 = !DILocation(line: 1119, column: 4, scope: !170)
!3348 = !DILocation(line: 1119, column: 9, scope: !170)
!3349 = !DILocation(line: 1119, column: 23, scope: !170)
!3350 = !DILocation(line: 1120, column: 4, scope: !170)
!3351 = !DILocation(line: 1120, column: 9, scope: !170)
!3352 = !DILocation(line: 1120, column: 23, scope: !170)
!3353 = !DILocation(line: 1121, column: 4, scope: !170)
!3354 = !DILocation(line: 1121, column: 9, scope: !170)
!3355 = !DILocation(line: 1121, column: 23, scope: !170)
!3356 = !DILocation(line: 1122, column: 4, scope: !170)
!3357 = !DILocation(line: 1122, column: 9, scope: !170)
!3358 = !DILocation(line: 1122, column: 14, scope: !170)
!3359 = !DILocation(line: 1122, column: 23, scope: !170)
!3360 = !DILocation(line: 1123, column: 4, scope: !170)
!3361 = !DILocation(line: 1123, column: 9, scope: !170)
!3362 = !DILocation(line: 1123, column: 14, scope: !170)
!3363 = !DILocation(line: 1123, column: 23, scope: !170)
!3364 = !DILocation(line: 1124, column: 4, scope: !170)
!3365 = !DILocation(line: 1124, column: 9, scope: !170)
!3366 = !DILocation(line: 1124, column: 14, scope: !170)
!3367 = !DILocation(line: 1124, column: 23, scope: !170)
!3368 = !DILocation(line: 1126, column: 4, scope: !170)
!3369 = !DILocation(line: 1126, column: 11, scope: !3279)
!3370 = !DILocation(line: 1126, column: 19, scope: !3279)
!3371 = !DILocation(line: 1126, column: 4, scope: !3279)
!3372 = !DILocation(line: 1127, column: 40, scope: !3373)
!3373 = distinct !DILexicalBlock(scope: !170, file: !1, line: 1126, column: 24)
!3374 = !DILocation(line: 1127, column: 29, scope: !3373)
!3375 = !DILocation(line: 1127, column: 16, scope: !3373)
!3376 = !DILocation(line: 1127, column: 21, scope: !3373)
!3377 = !DILocation(line: 1127, column: 7, scope: !3373)
!3378 = !DILocation(line: 1127, column: 12, scope: !3373)
!3379 = !DILocation(line: 1127, column: 27, scope: !3373)
!3380 = !DILocation(line: 1127, column: 50, scope: !3373)
!3381 = !DILocation(line: 1127, column: 55, scope: !3373)
!3382 = !DILocation(line: 1127, column: 59, scope: !3373)
!3383 = !DILocation(line: 1128, column: 40, scope: !3373)
!3384 = !DILocation(line: 1128, column: 28, scope: !3373)
!3385 = !DILocation(line: 1128, column: 14, scope: !3373)
!3386 = !DILocation(line: 1129, column: 14, scope: !3373)
!3387 = !DILocation(line: 1126, column: 4, scope: !3388)
!3388 = !DILexicalBlockFile(scope: !170, file: !1, discriminator: 2)
!3389 = !DILocation(line: 1132, column: 35, scope: !170)
!3390 = !DILocation(line: 1132, column: 40, scope: !170)
!3391 = !DILocation(line: 1132, column: 47, scope: !170)
!3392 = !DILocation(line: 1132, column: 58, scope: !170)
!3393 = !DILocation(line: 1132, column: 10, scope: !170)
!3394 = !DILocation(line: 1132, column: 8, scope: !170)
!3395 = !DILocation(line: 1133, column: 8, scope: !3396)
!3396 = distinct !DILexicalBlock(scope: !170, file: !1, line: 1133, column: 8)
!3397 = !DILocation(line: 1133, column: 12, scope: !3396)
!3398 = !DILocation(line: 1133, column: 8, scope: !170)
!3399 = !DILocation(line: 1134, column: 9, scope: !3400)
!3400 = distinct !DILexicalBlock(scope: !3401, file: !1, line: 1134, column: 9)
!3401 = distinct !DILexicalBlock(scope: !3402, file: !1, line: 1134, column: 9)
!3402 = distinct !DILexicalBlock(scope: !3396, file: !1, line: 1134, column: 7)
!3403 = !DILocation(line: 1134, column: 9, scope: !3401)
!3404 = !DILocation(line: 1134, column: 9, scope: !3405)
!3405 = !DILexicalBlockFile(scope: !3400, file: !1, discriminator: 1)
!3406 = !DILocation(line: 1134, column: 9, scope: !3407)
!3407 = !DILexicalBlockFile(scope: !3408, file: !1, discriminator: 2)
!3408 = distinct !DILexicalBlock(scope: !3401, file: !1, line: 1134, column: 9)
!3409 = !DILocation(line: 1134, column: 9, scope: !3410)
!3410 = !DILexicalBlockFile(scope: !3408, file: !1, discriminator: 3)
!3411 = !DILocation(line: 1134, column: 30, scope: !3412)
!3412 = !DILexicalBlockFile(scope: !3402, file: !1, discriminator: 4)
!3413 = !DILocation(line: 1134, column: 25, scope: !3412)
!3414 = !DILocation(line: 1134, column: 36, scope: !3412)
!3415 = !DILocation(line: 1136, column: 25, scope: !170)
!3416 = !DILocation(line: 1136, column: 30, scope: !170)
!3417 = !DILocation(line: 1136, column: 4, scope: !170)
!3418 = !DILocation(line: 1136, column: 9, scope: !170)
!3419 = !DILocation(line: 1136, column: 14, scope: !170)
!3420 = !DILocation(line: 1136, column: 23, scope: !170)
!3421 = !DILocation(line: 1137, column: 25, scope: !170)
!3422 = !DILocation(line: 1137, column: 30, scope: !170)
!3423 = !DILocation(line: 1137, column: 4, scope: !170)
!3424 = !DILocation(line: 1137, column: 9, scope: !170)
!3425 = !DILocation(line: 1137, column: 14, scope: !170)
!3426 = !DILocation(line: 1137, column: 23, scope: !170)
!3427 = !DILocation(line: 1139, column: 4, scope: !170)
!3428 = !DILocation(line: 1139, column: 9, scope: !170)
!3429 = !DILocation(line: 1139, column: 23, scope: !170)
!3430 = !DILocation(line: 1140, column: 11, scope: !170)
!3431 = !DILocation(line: 1140, column: 4, scope: !170)
!3432 = !DILocation(line: 1141, column: 1, scope: !170)
!3433 = !DILocalVariable(name: "bzerror", arg: 1, scope: !173, file: !1, line: 1145, type: !159)
!3434 = !DILocation(line: 1145, column: 37, scope: !173)
!3435 = !DILocalVariable(name: "b", arg: 2, scope: !173, file: !1, line: 1145, type: !157)
!3436 = !DILocation(line: 1145, column: 54, scope: !173)
!3437 = !DILocalVariable(name: "bzf", scope: !173, file: !1, line: 1147, type: !31)
!3438 = !DILocation(line: 1147, column: 12, scope: !173)
!3439 = !DILocation(line: 1147, column: 27, scope: !173)
!3440 = !DILocation(line: 1147, column: 18, scope: !173)
!3441 = !DILocation(line: 1149, column: 4, scope: !3442)
!3442 = distinct !DILexicalBlock(scope: !3443, file: !1, line: 1149, column: 4)
!3443 = distinct !DILexicalBlock(scope: !173, file: !1, line: 1149, column: 4)
!3444 = !DILocation(line: 1149, column: 4, scope: !3443)
!3445 = !DILocation(line: 1149, column: 4, scope: !3446)
!3446 = !DILexicalBlockFile(scope: !3442, file: !1, discriminator: 1)
!3447 = !DILocation(line: 1149, column: 4, scope: !3448)
!3448 = !DILexicalBlockFile(scope: !3449, file: !1, discriminator: 2)
!3449 = distinct !DILexicalBlock(scope: !3443, file: !1, line: 1149, column: 4)
!3450 = !DILocation(line: 1149, column: 4, scope: !3451)
!3451 = !DILexicalBlockFile(scope: !3449, file: !1, discriminator: 3)
!3452 = !DILocation(line: 1150, column: 8, scope: !3453)
!3453 = distinct !DILexicalBlock(scope: !173, file: !1, line: 1150, column: 8)
!3454 = !DILocation(line: 1150, column: 12, scope: !3453)
!3455 = !DILocation(line: 1150, column: 8, scope: !173)
!3456 = !DILocation(line: 1151, column: 9, scope: !3457)
!3457 = distinct !DILexicalBlock(scope: !3458, file: !1, line: 1151, column: 9)
!3458 = distinct !DILexicalBlock(scope: !3459, file: !1, line: 1151, column: 9)
!3459 = distinct !DILexicalBlock(scope: !3453, file: !1, line: 1151, column: 7)
!3460 = !DILocation(line: 1151, column: 9, scope: !3458)
!3461 = !DILocation(line: 1151, column: 9, scope: !3462)
!3462 = !DILexicalBlockFile(scope: !3457, file: !1, discriminator: 1)
!3463 = !DILocation(line: 1151, column: 9, scope: !3464)
!3464 = !DILexicalBlockFile(scope: !3465, file: !1, discriminator: 2)
!3465 = distinct !DILexicalBlock(scope: !3458, file: !1, line: 1151, column: 9)
!3466 = !DILocation(line: 1151, column: 9, scope: !3467)
!3467 = !DILexicalBlockFile(scope: !3465, file: !1, discriminator: 3)
!3468 = !DILocation(line: 1151, column: 27, scope: !3469)
!3469 = !DILexicalBlockFile(scope: !3459, file: !1, discriminator: 4)
!3470 = !DILocation(line: 1153, column: 8, scope: !3471)
!3471 = distinct !DILexicalBlock(scope: !173, file: !1, line: 1153, column: 8)
!3472 = !DILocation(line: 1153, column: 13, scope: !3471)
!3473 = !DILocation(line: 1153, column: 8, scope: !173)
!3474 = !DILocation(line: 1154, column: 9, scope: !3475)
!3475 = distinct !DILexicalBlock(scope: !3476, file: !1, line: 1154, column: 9)
!3476 = distinct !DILexicalBlock(scope: !3477, file: !1, line: 1154, column: 9)
!3477 = distinct !DILexicalBlock(scope: !3471, file: !1, line: 1154, column: 7)
!3478 = !DILocation(line: 1154, column: 9, scope: !3476)
!3479 = !DILocation(line: 1154, column: 9, scope: !3480)
!3480 = !DILexicalBlockFile(scope: !3475, file: !1, discriminator: 1)
!3481 = !DILocation(line: 1154, column: 9, scope: !3482)
!3482 = !DILexicalBlockFile(scope: !3483, file: !1, discriminator: 2)
!3483 = distinct !DILexicalBlock(scope: !3476, file: !1, line: 1154, column: 9)
!3484 = !DILocation(line: 1154, column: 9, scope: !3485)
!3485 = !DILexicalBlockFile(scope: !3483, file: !1, discriminator: 3)
!3486 = !DILocation(line: 1154, column: 39, scope: !3487)
!3487 = !DILexicalBlockFile(scope: !3477, file: !1, discriminator: 4)
!3488 = !DILocation(line: 1156, column: 8, scope: !3489)
!3489 = distinct !DILexicalBlock(scope: !173, file: !1, line: 1156, column: 8)
!3490 = !DILocation(line: 1156, column: 13, scope: !3489)
!3491 = !DILocation(line: 1156, column: 8, scope: !173)
!3492 = !DILocation(line: 1157, column: 37, scope: !3489)
!3493 = !DILocation(line: 1157, column: 42, scope: !3489)
!3494 = !DILocation(line: 1157, column: 13, scope: !3489)
!3495 = !DILocation(line: 1157, column: 7, scope: !3489)
!3496 = !DILocation(line: 1158, column: 11, scope: !173)
!3497 = !DILocation(line: 1158, column: 4, scope: !173)
!3498 = !DILocation(line: 1159, column: 1, scope: !173)
!3499 = !DILocation(line: 1159, column: 1, scope: !3500)
!3500 = !DILexicalBlockFile(scope: !173, file: !1, discriminator: 1)
!3501 = !DILocalVariable(name: "bzerror", arg: 1, scope: !176, file: !1, line: 1164, type: !159)
!3502 = !DILocation(line: 1164, column: 22, scope: !176)
!3503 = !DILocalVariable(name: "b", arg: 2, scope: !176, file: !1, line: 1165, type: !157)
!3504 = !DILocation(line: 1165, column: 22, scope: !176)
!3505 = !DILocalVariable(name: "buf", arg: 3, scope: !176, file: !1, line: 1166, type: !19)
!3506 = !DILocation(line: 1166, column: 22, scope: !176)
!3507 = !DILocalVariable(name: "len", arg: 4, scope: !176, file: !1, line: 1167, type: !43)
!3508 = !DILocation(line: 1167, column: 22, scope: !176)
!3509 = !DILocalVariable(name: "n", scope: !176, file: !1, line: 1169, type: !103)
!3510 = !DILocation(line: 1169, column: 12, scope: !176)
!3511 = !DILocalVariable(name: "ret", scope: !176, file: !1, line: 1169, type: !103)
!3512 = !DILocation(line: 1169, column: 15, scope: !176)
!3513 = !DILocalVariable(name: "bzf", scope: !176, file: !1, line: 1170, type: !31)
!3514 = !DILocation(line: 1170, column: 12, scope: !176)
!3515 = !DILocation(line: 1170, column: 27, scope: !176)
!3516 = !DILocation(line: 1170, column: 18, scope: !176)
!3517 = !DILocation(line: 1172, column: 4, scope: !3518)
!3518 = distinct !DILexicalBlock(scope: !3519, file: !1, line: 1172, column: 4)
!3519 = distinct !DILexicalBlock(scope: !176, file: !1, line: 1172, column: 4)
!3520 = !DILocation(line: 1172, column: 4, scope: !3519)
!3521 = !DILocation(line: 1172, column: 4, scope: !3522)
!3522 = !DILexicalBlockFile(scope: !3518, file: !1, discriminator: 1)
!3523 = !DILocation(line: 1172, column: 4, scope: !3524)
!3524 = !DILexicalBlockFile(scope: !3525, file: !1, discriminator: 2)
!3525 = distinct !DILexicalBlock(scope: !3519, file: !1, line: 1172, column: 4)
!3526 = !DILocation(line: 1172, column: 4, scope: !3527)
!3527 = !DILexicalBlockFile(scope: !3525, file: !1, discriminator: 3)
!3528 = !DILocation(line: 1174, column: 8, scope: !3529)
!3529 = distinct !DILexicalBlock(scope: !176, file: !1, line: 1174, column: 8)
!3530 = !DILocation(line: 1174, column: 12, scope: !3529)
!3531 = !DILocation(line: 1174, column: 20, scope: !3529)
!3532 = !DILocation(line: 1174, column: 23, scope: !3533)
!3533 = !DILexicalBlockFile(scope: !3529, file: !1, discriminator: 1)
!3534 = !DILocation(line: 1174, column: 27, scope: !3533)
!3535 = !DILocation(line: 1174, column: 35, scope: !3533)
!3536 = !DILocation(line: 1174, column: 38, scope: !3537)
!3537 = !DILexicalBlockFile(scope: !3529, file: !1, discriminator: 2)
!3538 = !DILocation(line: 1174, column: 42, scope: !3537)
!3539 = !DILocation(line: 1174, column: 8, scope: !3537)
!3540 = !DILocation(line: 1175, column: 9, scope: !3541)
!3541 = distinct !DILexicalBlock(scope: !3542, file: !1, line: 1175, column: 9)
!3542 = distinct !DILexicalBlock(scope: !3543, file: !1, line: 1175, column: 9)
!3543 = distinct !DILexicalBlock(scope: !3529, file: !1, line: 1175, column: 7)
!3544 = !DILocation(line: 1175, column: 9, scope: !3542)
!3545 = !DILocation(line: 1175, column: 9, scope: !3546)
!3546 = !DILexicalBlockFile(scope: !3541, file: !1, discriminator: 1)
!3547 = !DILocation(line: 1175, column: 9, scope: !3548)
!3548 = !DILexicalBlockFile(scope: !3549, file: !1, discriminator: 2)
!3549 = distinct !DILexicalBlock(scope: !3542, file: !1, line: 1175, column: 9)
!3550 = !DILocation(line: 1175, column: 9, scope: !3551)
!3551 = !DILexicalBlockFile(scope: !3549, file: !1, discriminator: 3)
!3552 = !DILocation(line: 1175, column: 36, scope: !3553)
!3553 = !DILexicalBlockFile(scope: !3543, file: !1, discriminator: 4)
!3554 = !DILocation(line: 1177, column: 8, scope: !3555)
!3555 = distinct !DILexicalBlock(scope: !176, file: !1, line: 1177, column: 8)
!3556 = !DILocation(line: 1177, column: 13, scope: !3555)
!3557 = !DILocation(line: 1177, column: 8, scope: !176)
!3558 = !DILocation(line: 1178, column: 9, scope: !3559)
!3559 = distinct !DILexicalBlock(scope: !3560, file: !1, line: 1178, column: 9)
!3560 = distinct !DILexicalBlock(scope: !3561, file: !1, line: 1178, column: 9)
!3561 = distinct !DILexicalBlock(scope: !3555, file: !1, line: 1178, column: 7)
!3562 = !DILocation(line: 1178, column: 9, scope: !3560)
!3563 = !DILocation(line: 1178, column: 9, scope: !3564)
!3564 = !DILexicalBlockFile(scope: !3559, file: !1, discriminator: 1)
!3565 = !DILocation(line: 1178, column: 9, scope: !3566)
!3566 = !DILexicalBlockFile(scope: !3567, file: !1, discriminator: 2)
!3567 = distinct !DILexicalBlock(scope: !3560, file: !1, line: 1178, column: 9)
!3568 = !DILocation(line: 1178, column: 9, scope: !3569)
!3569 = !DILexicalBlockFile(scope: !3567, file: !1, discriminator: 3)
!3570 = !DILocation(line: 1178, column: 39, scope: !3571)
!3571 = !DILexicalBlockFile(scope: !3561, file: !1, discriminator: 4)
!3572 = !DILocation(line: 1180, column: 8, scope: !3573)
!3573 = distinct !DILexicalBlock(scope: !176, file: !1, line: 1180, column: 8)
!3574 = !DILocation(line: 1180, column: 12, scope: !3573)
!3575 = !DILocation(line: 1180, column: 8, scope: !176)
!3576 = !DILocation(line: 1181, column: 9, scope: !3577)
!3577 = distinct !DILexicalBlock(scope: !3578, file: !1, line: 1181, column: 9)
!3578 = distinct !DILexicalBlock(scope: !3579, file: !1, line: 1181, column: 9)
!3579 = distinct !DILexicalBlock(scope: !3573, file: !1, line: 1181, column: 7)
!3580 = !DILocation(line: 1181, column: 9, scope: !3578)
!3581 = !DILocation(line: 1181, column: 9, scope: !3582)
!3582 = !DILexicalBlockFile(scope: !3577, file: !1, discriminator: 1)
!3583 = !DILocation(line: 1181, column: 9, scope: !3584)
!3584 = !DILexicalBlockFile(scope: !3585, file: !1, discriminator: 2)
!3585 = distinct !DILexicalBlock(scope: !3578, file: !1, line: 1181, column: 9)
!3586 = !DILocation(line: 1181, column: 9, scope: !3587)
!3587 = !DILexicalBlockFile(scope: !3585, file: !1, discriminator: 3)
!3588 = !DILocation(line: 1181, column: 27, scope: !3589)
!3589 = !DILexicalBlockFile(scope: !3579, file: !1, discriminator: 4)
!3590 = !DILocation(line: 1183, column: 26, scope: !176)
!3591 = !DILocation(line: 1183, column: 4, scope: !176)
!3592 = !DILocation(line: 1183, column: 9, scope: !176)
!3593 = !DILocation(line: 1183, column: 14, scope: !176)
!3594 = !DILocation(line: 1183, column: 24, scope: !176)
!3595 = !DILocation(line: 1184, column: 25, scope: !176)
!3596 = !DILocation(line: 1184, column: 4, scope: !176)
!3597 = !DILocation(line: 1184, column: 9, scope: !176)
!3598 = !DILocation(line: 1184, column: 14, scope: !176)
!3599 = !DILocation(line: 1184, column: 23, scope: !176)
!3600 = !DILocation(line: 1186, column: 4, scope: !176)
!3601 = !DILocation(line: 1188, column: 18, scope: !3602)
!3602 = distinct !DILexicalBlock(scope: !3603, file: !1, line: 1188, column: 11)
!3603 = distinct !DILexicalBlock(scope: !176, file: !1, line: 1186, column: 17)
!3604 = !DILocation(line: 1188, column: 23, scope: !3602)
!3605 = !DILocation(line: 1188, column: 11, scope: !3602)
!3606 = !DILocation(line: 1188, column: 11, scope: !3603)
!3607 = !DILocation(line: 1189, column: 12, scope: !3608)
!3608 = distinct !DILexicalBlock(scope: !3609, file: !1, line: 1189, column: 12)
!3609 = distinct !DILexicalBlock(scope: !3610, file: !1, line: 1189, column: 12)
!3610 = distinct !DILexicalBlock(scope: !3602, file: !1, line: 1189, column: 10)
!3611 = !DILocation(line: 1189, column: 12, scope: !3609)
!3612 = !DILocation(line: 1189, column: 12, scope: !3613)
!3613 = !DILexicalBlockFile(scope: !3608, file: !1, discriminator: 1)
!3614 = !DILocation(line: 1189, column: 12, scope: !3615)
!3615 = !DILexicalBlockFile(scope: !3616, file: !1, discriminator: 2)
!3616 = distinct !DILexicalBlock(scope: !3609, file: !1, line: 1189, column: 12)
!3617 = !DILocation(line: 1189, column: 12, scope: !3618)
!3618 = !DILexicalBlockFile(scope: !3616, file: !1, discriminator: 3)
!3619 = !DILocation(line: 1189, column: 36, scope: !3620)
!3620 = !DILexicalBlockFile(scope: !3610, file: !1, discriminator: 4)
!3621 = !DILocation(line: 1191, column: 11, scope: !3622)
!3622 = distinct !DILexicalBlock(scope: !3603, file: !1, line: 1191, column: 11)
!3623 = !DILocation(line: 1191, column: 16, scope: !3622)
!3624 = !DILocation(line: 1191, column: 21, scope: !3622)
!3625 = !DILocation(line: 1191, column: 30, scope: !3622)
!3626 = !DILocation(line: 1191, column: 35, scope: !3622)
!3627 = !DILocation(line: 1191, column: 46, scope: !3628)
!3628 = !DILexicalBlockFile(scope: !3622, file: !1, discriminator: 1)
!3629 = !DILocation(line: 1191, column: 51, scope: !3628)
!3630 = !DILocation(line: 1191, column: 39, scope: !3628)
!3631 = !DILocation(line: 1191, column: 11, scope: !3628)
!3632 = !DILocation(line: 1192, column: 22, scope: !3633)
!3633 = distinct !DILexicalBlock(scope: !3622, file: !1, line: 1191, column: 60)
!3634 = !DILocation(line: 1192, column: 27, scope: !3633)
!3635 = !DILocation(line: 1193, column: 37, scope: !3633)
!3636 = !DILocation(line: 1193, column: 42, scope: !3633)
!3637 = !DILocation(line: 1192, column: 14, scope: !3633)
!3638 = !DILocation(line: 1192, column: 12, scope: !3633)
!3639 = !DILocation(line: 1194, column: 21, scope: !3640)
!3640 = distinct !DILexicalBlock(scope: !3633, file: !1, line: 1194, column: 14)
!3641 = !DILocation(line: 1194, column: 26, scope: !3640)
!3642 = !DILocation(line: 1194, column: 14, scope: !3640)
!3643 = !DILocation(line: 1194, column: 14, scope: !3633)
!3644 = !DILocation(line: 1195, column: 15, scope: !3645)
!3645 = distinct !DILexicalBlock(scope: !3646, file: !1, line: 1195, column: 15)
!3646 = distinct !DILexicalBlock(scope: !3647, file: !1, line: 1195, column: 15)
!3647 = distinct !DILexicalBlock(scope: !3640, file: !1, line: 1195, column: 13)
!3648 = !DILocation(line: 1195, column: 15, scope: !3646)
!3649 = !DILocation(line: 1195, column: 15, scope: !3650)
!3650 = !DILexicalBlockFile(scope: !3645, file: !1, discriminator: 1)
!3651 = !DILocation(line: 1195, column: 15, scope: !3652)
!3652 = !DILexicalBlockFile(scope: !3653, file: !1, discriminator: 2)
!3653 = distinct !DILexicalBlock(scope: !3646, file: !1, line: 1195, column: 15)
!3654 = !DILocation(line: 1195, column: 15, scope: !3655)
!3655 = !DILexicalBlockFile(scope: !3653, file: !1, discriminator: 3)
!3656 = !DILocation(line: 1195, column: 39, scope: !3657)
!3657 = !DILexicalBlockFile(scope: !3647, file: !1, discriminator: 4)
!3658 = !DILocation(line: 1196, column: 22, scope: !3633)
!3659 = !DILocation(line: 1196, column: 10, scope: !3633)
!3660 = !DILocation(line: 1196, column: 15, scope: !3633)
!3661 = !DILocation(line: 1196, column: 20, scope: !3633)
!3662 = !DILocation(line: 1197, column: 31, scope: !3633)
!3663 = !DILocation(line: 1197, column: 36, scope: !3633)
!3664 = !DILocation(line: 1197, column: 10, scope: !3633)
!3665 = !DILocation(line: 1197, column: 15, scope: !3633)
!3666 = !DILocation(line: 1197, column: 20, scope: !3633)
!3667 = !DILocation(line: 1197, column: 29, scope: !3633)
!3668 = !DILocation(line: 1198, column: 30, scope: !3633)
!3669 = !DILocation(line: 1198, column: 35, scope: !3633)
!3670 = !DILocation(line: 1198, column: 10, scope: !3633)
!3671 = !DILocation(line: 1198, column: 15, scope: !3633)
!3672 = !DILocation(line: 1198, column: 20, scope: !3633)
!3673 = !DILocation(line: 1198, column: 28, scope: !3633)
!3674 = !DILocation(line: 1199, column: 7, scope: !3633)
!3675 = !DILocation(line: 1201, column: 34, scope: !3603)
!3676 = !DILocation(line: 1201, column: 39, scope: !3603)
!3677 = !DILocation(line: 1201, column: 13, scope: !3603)
!3678 = !DILocation(line: 1201, column: 11, scope: !3603)
!3679 = !DILocation(line: 1203, column: 11, scope: !3680)
!3680 = distinct !DILexicalBlock(scope: !3603, file: !1, line: 1203, column: 11)
!3681 = !DILocation(line: 1203, column: 15, scope: !3680)
!3682 = !DILocation(line: 1203, column: 24, scope: !3680)
!3683 = !DILocation(line: 1203, column: 27, scope: !3684)
!3684 = !DILexicalBlockFile(scope: !3680, file: !1, discriminator: 1)
!3685 = !DILocation(line: 1203, column: 31, scope: !3684)
!3686 = !DILocation(line: 1203, column: 11, scope: !3684)
!3687 = !DILocation(line: 1204, column: 12, scope: !3688)
!3688 = distinct !DILexicalBlock(scope: !3689, file: !1, line: 1204, column: 12)
!3689 = distinct !DILexicalBlock(scope: !3690, file: !1, line: 1204, column: 12)
!3690 = distinct !DILexicalBlock(scope: !3680, file: !1, line: 1204, column: 10)
!3691 = !DILocation(line: 1204, column: 12, scope: !3689)
!3692 = !DILocation(line: 1204, column: 12, scope: !3693)
!3693 = !DILexicalBlockFile(scope: !3688, file: !1, discriminator: 1)
!3694 = !DILocation(line: 1204, column: 12, scope: !3695)
!3695 = !DILexicalBlockFile(scope: !3696, file: !1, discriminator: 2)
!3696 = distinct !DILexicalBlock(scope: !3689, file: !1, line: 1204, column: 12)
!3697 = !DILocation(line: 1204, column: 12, scope: !3698)
!3698 = !DILexicalBlockFile(scope: !3696, file: !1, discriminator: 3)
!3699 = !DILocation(line: 1204, column: 28, scope: !3700)
!3700 = !DILexicalBlockFile(scope: !3690, file: !1, discriminator: 4)
!3701 = !DILocation(line: 1206, column: 11, scope: !3702)
!3702 = distinct !DILexicalBlock(scope: !3603, file: !1, line: 1206, column: 11)
!3703 = !DILocation(line: 1206, column: 15, scope: !3702)
!3704 = !DILocation(line: 1206, column: 24, scope: !3702)
!3705 = !DILocation(line: 1206, column: 34, scope: !3706)
!3706 = !DILexicalBlockFile(scope: !3702, file: !1, discriminator: 1)
!3707 = !DILocation(line: 1206, column: 39, scope: !3706)
!3708 = !DILocation(line: 1206, column: 27, scope: !3706)
!3709 = !DILocation(line: 1206, column: 47, scope: !3706)
!3710 = !DILocation(line: 1207, column: 11, scope: !3702)
!3711 = !DILocation(line: 1207, column: 16, scope: !3702)
!3712 = !DILocation(line: 1207, column: 21, scope: !3702)
!3713 = !DILocation(line: 1207, column: 30, scope: !3702)
!3714 = !DILocation(line: 1207, column: 35, scope: !3702)
!3715 = !DILocation(line: 1207, column: 38, scope: !3706)
!3716 = !DILocation(line: 1207, column: 43, scope: !3706)
!3717 = !DILocation(line: 1207, column: 48, scope: !3706)
!3718 = !DILocation(line: 1207, column: 58, scope: !3706)
!3719 = !DILocation(line: 1206, column: 11, scope: !3720)
!3720 = !DILexicalBlockFile(scope: !3603, file: !1, discriminator: 2)
!3721 = !DILocation(line: 1208, column: 12, scope: !3722)
!3722 = distinct !DILexicalBlock(scope: !3723, file: !1, line: 1208, column: 12)
!3723 = distinct !DILexicalBlock(scope: !3724, file: !1, line: 1208, column: 12)
!3724 = distinct !DILexicalBlock(scope: !3702, file: !1, line: 1208, column: 10)
!3725 = !DILocation(line: 1208, column: 12, scope: !3723)
!3726 = !DILocation(line: 1208, column: 12, scope: !3727)
!3727 = !DILexicalBlockFile(scope: !3722, file: !1, discriminator: 1)
!3728 = !DILocation(line: 1208, column: 12, scope: !3729)
!3729 = !DILexicalBlockFile(scope: !3730, file: !1, discriminator: 2)
!3730 = distinct !DILexicalBlock(scope: !3723, file: !1, line: 1208, column: 12)
!3731 = !DILocation(line: 1208, column: 12, scope: !3732)
!3732 = !DILexicalBlockFile(scope: !3730, file: !1, discriminator: 3)
!3733 = !DILocation(line: 1208, column: 42, scope: !3734)
!3734 = !DILexicalBlockFile(scope: !3724, file: !1, discriminator: 4)
!3735 = !DILocation(line: 1210, column: 11, scope: !3736)
!3736 = distinct !DILexicalBlock(scope: !3603, file: !1, line: 1210, column: 11)
!3737 = !DILocation(line: 1210, column: 15, scope: !3736)
!3738 = !DILocation(line: 1210, column: 11, scope: !3603)
!3739 = !DILocation(line: 1211, column: 12, scope: !3740)
!3740 = distinct !DILexicalBlock(scope: !3741, file: !1, line: 1211, column: 12)
!3741 = distinct !DILexicalBlock(scope: !3742, file: !1, line: 1211, column: 12)
!3742 = distinct !DILexicalBlock(scope: !3736, file: !1, line: 1211, column: 10)
!3743 = !DILocation(line: 1211, column: 12, scope: !3741)
!3744 = !DILocation(line: 1211, column: 12, scope: !3745)
!3745 = !DILexicalBlockFile(scope: !3740, file: !1, discriminator: 1)
!3746 = !DILocation(line: 1211, column: 12, scope: !3747)
!3747 = !DILexicalBlockFile(scope: !3748, file: !1, discriminator: 2)
!3748 = distinct !DILexicalBlock(scope: !3741, file: !1, line: 1211, column: 12)
!3749 = !DILocation(line: 1211, column: 12, scope: !3750)
!3750 = !DILexicalBlockFile(scope: !3748, file: !1, discriminator: 3)
!3751 = !DILocation(line: 1212, column: 19, scope: !3742)
!3752 = !DILocation(line: 1212, column: 25, scope: !3742)
!3753 = !DILocation(line: 1212, column: 30, scope: !3742)
!3754 = !DILocation(line: 1212, column: 35, scope: !3742)
!3755 = !DILocation(line: 1212, column: 23, scope: !3742)
!3756 = !DILocation(line: 1212, column: 12, scope: !3742)
!3757 = !DILocation(line: 1213, column: 11, scope: !3758)
!3758 = distinct !DILexicalBlock(scope: !3603, file: !1, line: 1213, column: 11)
!3759 = !DILocation(line: 1213, column: 16, scope: !3758)
!3760 = !DILocation(line: 1213, column: 21, scope: !3758)
!3761 = !DILocation(line: 1213, column: 31, scope: !3758)
!3762 = !DILocation(line: 1213, column: 11, scope: !3603)
!3763 = !DILocation(line: 1214, column: 12, scope: !3764)
!3764 = distinct !DILexicalBlock(scope: !3765, file: !1, line: 1214, column: 12)
!3765 = distinct !DILexicalBlock(scope: !3766, file: !1, line: 1214, column: 12)
!3766 = distinct !DILexicalBlock(scope: !3758, file: !1, line: 1214, column: 10)
!3767 = !DILocation(line: 1214, column: 12, scope: !3765)
!3768 = !DILocation(line: 1214, column: 12, scope: !3769)
!3769 = !DILexicalBlockFile(scope: !3764, file: !1, discriminator: 1)
!3770 = !DILocation(line: 1214, column: 12, scope: !3771)
!3771 = !DILexicalBlockFile(scope: !3772, file: !1, discriminator: 2)
!3772 = distinct !DILexicalBlock(scope: !3765, file: !1, line: 1214, column: 12)
!3773 = !DILocation(line: 1214, column: 12, scope: !3774)
!3774 = !DILexicalBlockFile(scope: !3772, file: !1, discriminator: 3)
!3775 = !DILocation(line: 1214, column: 37, scope: !3776)
!3776 = !DILexicalBlockFile(scope: !3766, file: !1, discriminator: 4)
!3777 = !DILocation(line: 1214, column: 30, scope: !3776)
!3778 = !DILocation(line: 1186, column: 4, scope: !3779)
!3779 = !DILexicalBlockFile(scope: !176, file: !1, discriminator: 1)
!3780 = !DILocation(line: 1219, column: 1, scope: !176)
!3781 = !DILocalVariable(name: "f", arg: 1, scope: !379, file: !1, line: 908, type: !36)
!3782 = !DILocation(line: 908, column: 28, scope: !379)
!3783 = !DILocalVariable(name: "c", scope: !379, file: !1, line: 910, type: !103)
!3784 = !DILocation(line: 910, column: 10, scope: !379)
!3785 = !DILocation(line: 910, column: 22, scope: !379)
!3786 = !DILocation(line: 910, column: 14, scope: !379)
!3787 = !DILocation(line: 911, column: 8, scope: !3788)
!3788 = distinct !DILexicalBlock(scope: !379, file: !1, line: 911, column: 8)
!3789 = !DILocation(line: 911, column: 10, scope: !3788)
!3790 = !DILocation(line: 911, column: 8, scope: !379)
!3791 = !DILocation(line: 911, column: 18, scope: !3792)
!3792 = !DILexicalBlockFile(scope: !3788, file: !1, discriminator: 1)
!3793 = !DILocation(line: 912, column: 13, scope: !379)
!3794 = !DILocation(line: 912, column: 16, scope: !379)
!3795 = !DILocation(line: 912, column: 4, scope: !379)
!3796 = !DILocation(line: 913, column: 4, scope: !379)
!3797 = !DILocation(line: 914, column: 1, scope: !379)
!3798 = !DILocalVariable(name: "bzerror", arg: 1, scope: !179, file: !1, line: 1224, type: !159)
!3799 = !DILocation(line: 1224, column: 32, scope: !179)
!3800 = !DILocalVariable(name: "b", arg: 2, scope: !179, file: !1, line: 1225, type: !157)
!3801 = !DILocation(line: 1225, column: 32, scope: !179)
!3802 = !DILocalVariable(name: "unused", arg: 3, scope: !179, file: !1, line: 1226, type: !182)
!3803 = !DILocation(line: 1226, column: 32, scope: !179)
!3804 = !DILocalVariable(name: "nUnused", arg: 4, scope: !179, file: !1, line: 1227, type: !159)
!3805 = !DILocation(line: 1227, column: 32, scope: !179)
!3806 = !DILocalVariable(name: "bzf", scope: !179, file: !1, line: 1229, type: !31)
!3807 = !DILocation(line: 1229, column: 12, scope: !179)
!3808 = !DILocation(line: 1229, column: 27, scope: !179)
!3809 = !DILocation(line: 1229, column: 18, scope: !179)
!3810 = !DILocation(line: 1230, column: 8, scope: !3811)
!3811 = distinct !DILexicalBlock(scope: !179, file: !1, line: 1230, column: 8)
!3812 = !DILocation(line: 1230, column: 12, scope: !3811)
!3813 = !DILocation(line: 1230, column: 8, scope: !179)
!3814 = !DILocation(line: 1231, column: 9, scope: !3815)
!3815 = distinct !DILexicalBlock(scope: !3816, file: !1, line: 1231, column: 9)
!3816 = distinct !DILexicalBlock(scope: !3817, file: !1, line: 1231, column: 9)
!3817 = distinct !DILexicalBlock(scope: !3811, file: !1, line: 1231, column: 7)
!3818 = !DILocation(line: 1231, column: 9, scope: !3816)
!3819 = !DILocation(line: 1231, column: 9, scope: !3820)
!3820 = !DILexicalBlockFile(scope: !3815, file: !1, discriminator: 1)
!3821 = !DILocation(line: 1231, column: 9, scope: !3822)
!3822 = !DILexicalBlockFile(scope: !3823, file: !1, discriminator: 2)
!3823 = distinct !DILexicalBlock(scope: !3816, file: !1, line: 1231, column: 9)
!3824 = !DILocation(line: 1231, column: 9, scope: !3825)
!3825 = !DILexicalBlockFile(scope: !3823, file: !1, discriminator: 3)
!3826 = !DILocation(line: 1231, column: 36, scope: !3827)
!3827 = !DILexicalBlockFile(scope: !3817, file: !1, discriminator: 4)
!3828 = !DILocation(line: 1232, column: 8, scope: !3829)
!3829 = distinct !DILexicalBlock(scope: !179, file: !1, line: 1232, column: 8)
!3830 = !DILocation(line: 1232, column: 13, scope: !3829)
!3831 = !DILocation(line: 1232, column: 21, scope: !3829)
!3832 = !DILocation(line: 1232, column: 8, scope: !179)
!3833 = !DILocation(line: 1233, column: 9, scope: !3834)
!3834 = distinct !DILexicalBlock(scope: !3835, file: !1, line: 1233, column: 9)
!3835 = distinct !DILexicalBlock(scope: !3836, file: !1, line: 1233, column: 9)
!3836 = distinct !DILexicalBlock(scope: !3829, file: !1, line: 1233, column: 7)
!3837 = !DILocation(line: 1233, column: 9, scope: !3835)
!3838 = !DILocation(line: 1233, column: 9, scope: !3839)
!3839 = !DILexicalBlockFile(scope: !3834, file: !1, discriminator: 1)
!3840 = !DILocation(line: 1233, column: 9, scope: !3841)
!3841 = !DILexicalBlockFile(scope: !3842, file: !1, discriminator: 2)
!3842 = distinct !DILexicalBlock(scope: !3835, file: !1, line: 1233, column: 9)
!3843 = !DILocation(line: 1233, column: 9, scope: !3844)
!3844 = !DILexicalBlockFile(scope: !3842, file: !1, discriminator: 3)
!3845 = !DILocation(line: 1233, column: 39, scope: !3846)
!3846 = !DILexicalBlockFile(scope: !3836, file: !1, discriminator: 4)
!3847 = !DILocation(line: 1234, column: 8, scope: !3848)
!3848 = distinct !DILexicalBlock(scope: !179, file: !1, line: 1234, column: 8)
!3849 = !DILocation(line: 1234, column: 15, scope: !3848)
!3850 = !DILocation(line: 1234, column: 23, scope: !3848)
!3851 = !DILocation(line: 1234, column: 26, scope: !3852)
!3852 = !DILexicalBlockFile(scope: !3848, file: !1, discriminator: 1)
!3853 = !DILocation(line: 1234, column: 34, scope: !3852)
!3854 = !DILocation(line: 1234, column: 8, scope: !3852)
!3855 = !DILocation(line: 1235, column: 9, scope: !3856)
!3856 = distinct !DILexicalBlock(scope: !3857, file: !1, line: 1235, column: 9)
!3857 = distinct !DILexicalBlock(scope: !3858, file: !1, line: 1235, column: 9)
!3858 = distinct !DILexicalBlock(scope: !3848, file: !1, line: 1235, column: 7)
!3859 = !DILocation(line: 1235, column: 9, scope: !3857)
!3860 = !DILocation(line: 1235, column: 9, scope: !3861)
!3861 = !DILexicalBlockFile(scope: !3856, file: !1, discriminator: 1)
!3862 = !DILocation(line: 1235, column: 9, scope: !3863)
!3863 = !DILexicalBlockFile(scope: !3864, file: !1, discriminator: 2)
!3864 = distinct !DILexicalBlock(scope: !3857, file: !1, line: 1235, column: 9)
!3865 = !DILocation(line: 1235, column: 9, scope: !3866)
!3866 = !DILexicalBlockFile(scope: !3864, file: !1, discriminator: 3)
!3867 = !DILocation(line: 1235, column: 36, scope: !3868)
!3868 = !DILexicalBlockFile(scope: !3858, file: !1, discriminator: 4)
!3869 = !DILocation(line: 1237, column: 4, scope: !3870)
!3870 = distinct !DILexicalBlock(scope: !3871, file: !1, line: 1237, column: 4)
!3871 = distinct !DILexicalBlock(scope: !179, file: !1, line: 1237, column: 4)
!3872 = !DILocation(line: 1237, column: 4, scope: !3871)
!3873 = !DILocation(line: 1237, column: 4, scope: !3874)
!3874 = !DILexicalBlockFile(scope: !3870, file: !1, discriminator: 1)
!3875 = !DILocation(line: 1237, column: 4, scope: !3876)
!3876 = !DILexicalBlockFile(scope: !3877, file: !1, discriminator: 2)
!3877 = distinct !DILexicalBlock(scope: !3871, file: !1, line: 1237, column: 4)
!3878 = !DILocation(line: 1237, column: 4, scope: !3879)
!3879 = !DILexicalBlockFile(scope: !3877, file: !1, discriminator: 3)
!3880 = !DILocation(line: 1238, column: 15, scope: !179)
!3881 = !DILocation(line: 1238, column: 20, scope: !179)
!3882 = !DILocation(line: 1238, column: 25, scope: !179)
!3883 = !DILocation(line: 1238, column: 5, scope: !179)
!3884 = !DILocation(line: 1238, column: 13, scope: !179)
!3885 = !DILocation(line: 1239, column: 14, scope: !179)
!3886 = !DILocation(line: 1239, column: 19, scope: !179)
!3887 = !DILocation(line: 1239, column: 24, scope: !179)
!3888 = !DILocation(line: 1239, column: 5, scope: !179)
!3889 = !DILocation(line: 1239, column: 12, scope: !179)
!3890 = !DILocation(line: 1240, column: 1, scope: !179)
!3891 = !DILocation(line: 1240, column: 1, scope: !3892)
!3892 = !DILexicalBlockFile(scope: !179, file: !1, discriminator: 1)
!3893 = !DILocalVariable(name: "dest", arg: 1, scope: !183, file: !1, line: 1250, type: !45)
!3894 = !DILocation(line: 1250, column: 42, scope: !183)
!3895 = !DILocalVariable(name: "destLen", arg: 2, scope: !183, file: !1, line: 1251, type: !166)
!3896 = !DILocation(line: 1251, column: 42, scope: !183)
!3897 = !DILocalVariable(name: "source", arg: 3, scope: !183, file: !1, line: 1252, type: !45)
!3898 = !DILocation(line: 1252, column: 42, scope: !183)
!3899 = !DILocalVariable(name: "sourceLen", arg: 4, scope: !183, file: !1, line: 1253, type: !29)
!3900 = !DILocation(line: 1253, column: 42, scope: !183)
!3901 = !DILocalVariable(name: "blockSize100k", arg: 5, scope: !183, file: !1, line: 1254, type: !43)
!3902 = !DILocation(line: 1254, column: 42, scope: !183)
!3903 = !DILocalVariable(name: "verbosity", arg: 6, scope: !183, file: !1, line: 1255, type: !43)
!3904 = !DILocation(line: 1255, column: 42, scope: !183)
!3905 = !DILocalVariable(name: "workFactor", arg: 7, scope: !183, file: !1, line: 1256, type: !43)
!3906 = !DILocation(line: 1256, column: 42, scope: !183)
!3907 = !DILocalVariable(name: "strm", scope: !183, file: !1, line: 1258, type: !106)
!3908 = !DILocation(line: 1258, column: 14, scope: !183)
!3909 = !DILocalVariable(name: "ret", scope: !183, file: !1, line: 1259, type: !43)
!3910 = !DILocation(line: 1259, column: 8, scope: !183)
!3911 = !DILocation(line: 1261, column: 8, scope: !3912)
!3912 = distinct !DILexicalBlock(scope: !183, file: !1, line: 1261, column: 8)
!3913 = !DILocation(line: 1261, column: 13, scope: !3912)
!3914 = !DILocation(line: 1261, column: 21, scope: !3912)
!3915 = !DILocation(line: 1261, column: 24, scope: !3916)
!3916 = !DILexicalBlockFile(scope: !3912, file: !1, discriminator: 1)
!3917 = !DILocation(line: 1261, column: 32, scope: !3916)
!3918 = !DILocation(line: 1261, column: 40, scope: !3916)
!3919 = !DILocation(line: 1262, column: 8, scope: !3912)
!3920 = !DILocation(line: 1262, column: 15, scope: !3912)
!3921 = !DILocation(line: 1262, column: 23, scope: !3912)
!3922 = !DILocation(line: 1263, column: 8, scope: !3912)
!3923 = !DILocation(line: 1263, column: 22, scope: !3912)
!3924 = !DILocation(line: 1263, column: 26, scope: !3912)
!3925 = !DILocation(line: 1263, column: 29, scope: !3916)
!3926 = !DILocation(line: 1263, column: 43, scope: !3916)
!3927 = !DILocation(line: 1263, column: 47, scope: !3916)
!3928 = !DILocation(line: 1264, column: 8, scope: !3912)
!3929 = !DILocation(line: 1264, column: 18, scope: !3912)
!3930 = !DILocation(line: 1264, column: 22, scope: !3912)
!3931 = !DILocation(line: 1264, column: 25, scope: !3916)
!3932 = !DILocation(line: 1264, column: 35, scope: !3916)
!3933 = !DILocation(line: 1264, column: 39, scope: !3916)
!3934 = !DILocation(line: 1265, column: 8, scope: !3912)
!3935 = !DILocation(line: 1265, column: 19, scope: !3912)
!3936 = !DILocation(line: 1265, column: 23, scope: !3912)
!3937 = !DILocation(line: 1265, column: 26, scope: !3916)
!3938 = !DILocation(line: 1265, column: 37, scope: !3916)
!3939 = !DILocation(line: 1261, column: 8, scope: !3940)
!3940 = !DILexicalBlockFile(scope: !183, file: !1, discriminator: 2)
!3941 = !DILocation(line: 1266, column: 7, scope: !3912)
!3942 = !DILocation(line: 1268, column: 8, scope: !3943)
!3943 = distinct !DILexicalBlock(scope: !183, file: !1, line: 1268, column: 8)
!3944 = !DILocation(line: 1268, column: 19, scope: !3943)
!3945 = !DILocation(line: 1268, column: 8, scope: !183)
!3946 = !DILocation(line: 1268, column: 36, scope: !3947)
!3947 = !DILexicalBlockFile(scope: !3943, file: !1, discriminator: 1)
!3948 = !DILocation(line: 1268, column: 25, scope: !3947)
!3949 = !DILocation(line: 1269, column: 9, scope: !183)
!3950 = !DILocation(line: 1269, column: 17, scope: !183)
!3951 = !DILocation(line: 1270, column: 9, scope: !183)
!3952 = !DILocation(line: 1270, column: 16, scope: !183)
!3953 = !DILocation(line: 1271, column: 9, scope: !183)
!3954 = !DILocation(line: 1271, column: 16, scope: !183)
!3955 = !DILocation(line: 1272, column: 38, scope: !183)
!3956 = !DILocation(line: 1273, column: 31, scope: !183)
!3957 = !DILocation(line: 1273, column: 42, scope: !183)
!3958 = !DILocation(line: 1272, column: 10, scope: !183)
!3959 = !DILocation(line: 1272, column: 8, scope: !183)
!3960 = !DILocation(line: 1274, column: 8, scope: !3961)
!3961 = distinct !DILexicalBlock(scope: !183, file: !1, line: 1274, column: 8)
!3962 = !DILocation(line: 1274, column: 12, scope: !3961)
!3963 = !DILocation(line: 1274, column: 8, scope: !183)
!3964 = !DILocation(line: 1274, column: 29, scope: !3965)
!3965 = !DILexicalBlockFile(scope: !3961, file: !1, discriminator: 1)
!3966 = !DILocation(line: 1274, column: 22, scope: !3965)
!3967 = !DILocation(line: 1276, column: 19, scope: !183)
!3968 = !DILocation(line: 1276, column: 9, scope: !183)
!3969 = !DILocation(line: 1276, column: 17, scope: !183)
!3970 = !DILocation(line: 1277, column: 20, scope: !183)
!3971 = !DILocation(line: 1277, column: 9, scope: !183)
!3972 = !DILocation(line: 1277, column: 18, scope: !183)
!3973 = !DILocation(line: 1278, column: 20, scope: !183)
!3974 = !DILocation(line: 1278, column: 9, scope: !183)
!3975 = !DILocation(line: 1278, column: 18, scope: !183)
!3976 = !DILocation(line: 1279, column: 22, scope: !183)
!3977 = !DILocation(line: 1279, column: 21, scope: !183)
!3978 = !DILocation(line: 1279, column: 9, scope: !183)
!3979 = !DILocation(line: 1279, column: 19, scope: !183)
!3980 = !DILocation(line: 1281, column: 10, scope: !183)
!3981 = !DILocation(line: 1281, column: 8, scope: !183)
!3982 = !DILocation(line: 1282, column: 8, scope: !3983)
!3983 = distinct !DILexicalBlock(scope: !183, file: !1, line: 1282, column: 8)
!3984 = !DILocation(line: 1282, column: 12, scope: !3983)
!3985 = !DILocation(line: 1282, column: 8, scope: !183)
!3986 = !DILocation(line: 1282, column: 29, scope: !3987)
!3987 = !DILexicalBlockFile(scope: !3983, file: !1, discriminator: 1)
!3988 = !DILocation(line: 1283, column: 8, scope: !3989)
!3989 = distinct !DILexicalBlock(scope: !183, file: !1, line: 1283, column: 8)
!3990 = !DILocation(line: 1283, column: 12, scope: !3989)
!3991 = !DILocation(line: 1283, column: 8, scope: !183)
!3992 = !DILocation(line: 1283, column: 30, scope: !3993)
!3993 = !DILexicalBlockFile(scope: !3989, file: !1, discriminator: 1)
!3994 = !DILocation(line: 1286, column: 21, scope: !183)
!3995 = !DILocation(line: 1286, column: 5, scope: !183)
!3996 = !DILocation(line: 1286, column: 13, scope: !183)
!3997 = !DILocation(line: 1287, column: 4, scope: !183)
!3998 = !DILocation(line: 1288, column: 4, scope: !183)
!3999 = !DILocation(line: 1291, column: 4, scope: !183)
!4000 = !DILocation(line: 1292, column: 4, scope: !183)
!4001 = !DILocation(line: 1295, column: 4, scope: !183)
!4002 = !DILocation(line: 1296, column: 11, scope: !183)
!4003 = !DILocation(line: 1296, column: 4, scope: !183)
!4004 = !DILocation(line: 1297, column: 1, scope: !183)
!4005 = !DILocalVariable(name: "dest", arg: 1, scope: !186, file: !1, line: 1302, type: !45)
!4006 = !DILocation(line: 1302, column: 44, scope: !186)
!4007 = !DILocalVariable(name: "destLen", arg: 2, scope: !186, file: !1, line: 1303, type: !166)
!4008 = !DILocation(line: 1303, column: 44, scope: !186)
!4009 = !DILocalVariable(name: "source", arg: 3, scope: !186, file: !1, line: 1304, type: !45)
!4010 = !DILocation(line: 1304, column: 44, scope: !186)
!4011 = !DILocalVariable(name: "sourceLen", arg: 4, scope: !186, file: !1, line: 1305, type: !29)
!4012 = !DILocation(line: 1305, column: 44, scope: !186)
!4013 = !DILocalVariable(name: "small", arg: 5, scope: !186, file: !1, line: 1306, type: !43)
!4014 = !DILocation(line: 1306, column: 44, scope: !186)
!4015 = !DILocalVariable(name: "verbosity", arg: 6, scope: !186, file: !1, line: 1307, type: !43)
!4016 = !DILocation(line: 1307, column: 44, scope: !186)
!4017 = !DILocalVariable(name: "strm", scope: !186, file: !1, line: 1309, type: !106)
!4018 = !DILocation(line: 1309, column: 14, scope: !186)
!4019 = !DILocalVariable(name: "ret", scope: !186, file: !1, line: 1310, type: !43)
!4020 = !DILocation(line: 1310, column: 8, scope: !186)
!4021 = !DILocation(line: 1312, column: 8, scope: !4022)
!4022 = distinct !DILexicalBlock(scope: !186, file: !1, line: 1312, column: 8)
!4023 = !DILocation(line: 1312, column: 13, scope: !4022)
!4024 = !DILocation(line: 1312, column: 21, scope: !4022)
!4025 = !DILocation(line: 1312, column: 24, scope: !4026)
!4026 = !DILexicalBlockFile(scope: !4022, file: !1, discriminator: 1)
!4027 = !DILocation(line: 1312, column: 32, scope: !4026)
!4028 = !DILocation(line: 1312, column: 40, scope: !4026)
!4029 = !DILocation(line: 1313, column: 8, scope: !4022)
!4030 = !DILocation(line: 1313, column: 15, scope: !4022)
!4031 = !DILocation(line: 1313, column: 23, scope: !4022)
!4032 = !DILocation(line: 1314, column: 9, scope: !4022)
!4033 = !DILocation(line: 1314, column: 15, scope: !4022)
!4034 = !DILocation(line: 1314, column: 20, scope: !4022)
!4035 = !DILocation(line: 1314, column: 23, scope: !4026)
!4036 = !DILocation(line: 1314, column: 29, scope: !4026)
!4037 = !DILocation(line: 1314, column: 35, scope: !4026)
!4038 = !DILocation(line: 1315, column: 8, scope: !4022)
!4039 = !DILocation(line: 1315, column: 18, scope: !4022)
!4040 = !DILocation(line: 1315, column: 22, scope: !4022)
!4041 = !DILocation(line: 1315, column: 25, scope: !4026)
!4042 = !DILocation(line: 1315, column: 35, scope: !4026)
!4043 = !DILocation(line: 1312, column: 8, scope: !4044)
!4044 = !DILexicalBlockFile(scope: !186, file: !1, discriminator: 2)
!4045 = !DILocation(line: 1316, column: 11, scope: !4022)
!4046 = !DILocation(line: 1318, column: 9, scope: !186)
!4047 = !DILocation(line: 1318, column: 17, scope: !186)
!4048 = !DILocation(line: 1319, column: 9, scope: !186)
!4049 = !DILocation(line: 1319, column: 16, scope: !186)
!4050 = !DILocation(line: 1320, column: 9, scope: !186)
!4051 = !DILocation(line: 1320, column: 16, scope: !186)
!4052 = !DILocation(line: 1321, column: 40, scope: !186)
!4053 = !DILocation(line: 1321, column: 51, scope: !186)
!4054 = !DILocation(line: 1321, column: 10, scope: !186)
!4055 = !DILocation(line: 1321, column: 8, scope: !186)
!4056 = !DILocation(line: 1322, column: 8, scope: !4057)
!4057 = distinct !DILexicalBlock(scope: !186, file: !1, line: 1322, column: 8)
!4058 = !DILocation(line: 1322, column: 12, scope: !4057)
!4059 = !DILocation(line: 1322, column: 8, scope: !186)
!4060 = !DILocation(line: 1322, column: 29, scope: !4061)
!4061 = !DILexicalBlockFile(scope: !4057, file: !1, discriminator: 1)
!4062 = !DILocation(line: 1322, column: 22, scope: !4061)
!4063 = !DILocation(line: 1324, column: 19, scope: !186)
!4064 = !DILocation(line: 1324, column: 9, scope: !186)
!4065 = !DILocation(line: 1324, column: 17, scope: !186)
!4066 = !DILocation(line: 1325, column: 20, scope: !186)
!4067 = !DILocation(line: 1325, column: 9, scope: !186)
!4068 = !DILocation(line: 1325, column: 18, scope: !186)
!4069 = !DILocation(line: 1326, column: 20, scope: !186)
!4070 = !DILocation(line: 1326, column: 9, scope: !186)
!4071 = !DILocation(line: 1326, column: 18, scope: !186)
!4072 = !DILocation(line: 1327, column: 22, scope: !186)
!4073 = !DILocation(line: 1327, column: 21, scope: !186)
!4074 = !DILocation(line: 1327, column: 9, scope: !186)
!4075 = !DILocation(line: 1327, column: 19, scope: !186)
!4076 = !DILocation(line: 1329, column: 10, scope: !186)
!4077 = !DILocation(line: 1329, column: 8, scope: !186)
!4078 = !DILocation(line: 1330, column: 8, scope: !4079)
!4079 = distinct !DILexicalBlock(scope: !186, file: !1, line: 1330, column: 8)
!4080 = !DILocation(line: 1330, column: 12, scope: !4079)
!4081 = !DILocation(line: 1330, column: 8, scope: !186)
!4082 = !DILocation(line: 1330, column: 22, scope: !4083)
!4083 = !DILexicalBlockFile(scope: !4079, file: !1, discriminator: 1)
!4084 = !DILocation(line: 1331, column: 8, scope: !4085)
!4085 = distinct !DILexicalBlock(scope: !186, file: !1, line: 1331, column: 8)
!4086 = !DILocation(line: 1331, column: 12, scope: !4085)
!4087 = !DILocation(line: 1331, column: 8, scope: !186)
!4088 = !DILocation(line: 1331, column: 30, scope: !4089)
!4089 = !DILexicalBlockFile(scope: !4085, file: !1, discriminator: 1)
!4090 = !DILocation(line: 1334, column: 21, scope: !186)
!4091 = !DILocation(line: 1334, column: 5, scope: !186)
!4092 = !DILocation(line: 1334, column: 13, scope: !186)
!4093 = !DILocation(line: 1335, column: 4, scope: !186)
!4094 = !DILocation(line: 1336, column: 4, scope: !186)
!4095 = !DILocation(line: 1339, column: 13, scope: !4096)
!4096 = distinct !DILexicalBlock(scope: !186, file: !1, line: 1339, column: 8)
!4097 = !DILocation(line: 1339, column: 23, scope: !4096)
!4098 = !DILocation(line: 1339, column: 8, scope: !186)
!4099 = !DILocation(line: 1340, column: 7, scope: !4100)
!4100 = distinct !DILexicalBlock(scope: !4096, file: !1, line: 1339, column: 28)
!4101 = !DILocation(line: 1341, column: 7, scope: !4100)
!4102 = !DILocation(line: 1343, column: 7, scope: !4103)
!4103 = distinct !DILexicalBlock(scope: !4096, file: !1, line: 1342, column: 11)
!4104 = !DILocation(line: 1344, column: 7, scope: !4103)
!4105 = !DILocation(line: 1348, column: 4, scope: !186)
!4106 = !DILocation(line: 1349, column: 11, scope: !186)
!4107 = !DILocation(line: 1349, column: 4, scope: !186)
!4108 = !DILocation(line: 1350, column: 1, scope: !186)
!4109 = !DILocalVariable(name: "path", arg: 1, scope: !194, file: !1, line: 1463, type: !192)
!4110 = !DILocation(line: 1463, column: 30, scope: !194)
!4111 = !DILocalVariable(name: "mode", arg: 2, scope: !194, file: !1, line: 1464, type: !192)
!4112 = !DILocation(line: 1464, column: 30, scope: !194)
!4113 = !DILocation(line: 1466, column: 29, scope: !194)
!4114 = !DILocation(line: 1466, column: 37, scope: !194)
!4115 = !DILocation(line: 1466, column: 11, scope: !194)
!4116 = !DILocation(line: 1466, column: 4, scope: !194)
!4117 = !DILocalVariable(name: "path", arg: 1, scope: !382, file: !1, line: 1386, type: !192)
!4118 = !DILocation(line: 1386, column: 30, scope: !382)
!4119 = !DILocalVariable(name: "fd", arg: 2, scope: !382, file: !1, line: 1387, type: !43)
!4120 = !DILocation(line: 1387, column: 22, scope: !382)
!4121 = !DILocalVariable(name: "mode", arg: 3, scope: !382, file: !1, line: 1388, type: !192)
!4122 = !DILocation(line: 1388, column: 30, scope: !382)
!4123 = !DILocalVariable(name: "open_mode", arg: 4, scope: !382, file: !1, line: 1389, type: !43)
!4124 = !DILocation(line: 1389, column: 22, scope: !382)
!4125 = !DILocalVariable(name: "bzerr", scope: !382, file: !1, line: 1391, type: !43)
!4126 = !DILocation(line: 1391, column: 11, scope: !382)
!4127 = !DILocalVariable(name: "unused", scope: !382, file: !1, line: 1392, type: !4128)
!4128 = !DICompositeType(tag: DW_TAG_array_type, baseType: !46, size: 40000, align: 8, elements: !100)
!4129 = !DILocation(line: 1392, column: 11, scope: !382)
!4130 = !DILocalVariable(name: "blockSize100k", scope: !382, file: !1, line: 1393, type: !43)
!4131 = !DILocation(line: 1393, column: 11, scope: !382)
!4132 = !DILocalVariable(name: "writing", scope: !382, file: !1, line: 1394, type: !43)
!4133 = !DILocation(line: 1394, column: 11, scope: !382)
!4134 = !DILocalVariable(name: "mode2", scope: !382, file: !1, line: 1395, type: !4135)
!4135 = !DICompositeType(tag: DW_TAG_array_type, baseType: !46, size: 80, align: 8, elements: !4136)
!4136 = !{!4137}
!4137 = !DISubrange(count: 10)
!4138 = !DILocation(line: 1395, column: 11, scope: !382)
!4139 = !DILocalVariable(name: "fp", scope: !382, file: !1, line: 1396, type: !36)
!4140 = !DILocation(line: 1396, column: 12, scope: !382)
!4141 = !DILocalVariable(name: "bzfp", scope: !382, file: !1, line: 1397, type: !157)
!4142 = !DILocation(line: 1397, column: 12, scope: !382)
!4143 = !DILocalVariable(name: "verbosity", scope: !382, file: !1, line: 1398, type: !43)
!4144 = !DILocation(line: 1398, column: 11, scope: !382)
!4145 = !DILocalVariable(name: "workFactor", scope: !382, file: !1, line: 1399, type: !43)
!4146 = !DILocation(line: 1399, column: 11, scope: !382)
!4147 = !DILocalVariable(name: "smallMode", scope: !382, file: !1, line: 1400, type: !43)
!4148 = !DILocation(line: 1400, column: 11, scope: !382)
!4149 = !DILocalVariable(name: "nUnused", scope: !382, file: !1, line: 1401, type: !43)
!4150 = !DILocation(line: 1401, column: 11, scope: !382)
!4151 = !DILocation(line: 1403, column: 8, scope: !4152)
!4152 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1403, column: 8)
!4153 = !DILocation(line: 1403, column: 13, scope: !4152)
!4154 = !DILocation(line: 1403, column: 8, scope: !382)
!4155 = !DILocation(line: 1403, column: 22, scope: !4156)
!4156 = !DILexicalBlockFile(scope: !4152, file: !1, discriminator: 1)
!4157 = !DILocation(line: 1404, column: 4, scope: !382)
!4158 = !DILocation(line: 1404, column: 12, scope: !4159)
!4159 = !DILexicalBlockFile(scope: !382, file: !1, discriminator: 1)
!4160 = !DILocation(line: 1404, column: 11, scope: !4159)
!4161 = !DILocation(line: 1404, column: 4, scope: !4159)
!4162 = !DILocation(line: 1405, column: 16, scope: !4163)
!4163 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1404, column: 18)
!4164 = !DILocation(line: 1405, column: 15, scope: !4163)
!4165 = !DILocation(line: 1405, column: 7, scope: !4163)
!4166 = !DILocation(line: 1407, column: 18, scope: !4167)
!4167 = distinct !DILexicalBlock(scope: !4163, file: !1, line: 1405, column: 22)
!4168 = !DILocation(line: 1407, column: 23, scope: !4167)
!4169 = !DILocation(line: 1409, column: 18, scope: !4167)
!4170 = !DILocation(line: 1409, column: 23, scope: !4167)
!4171 = !DILocation(line: 1411, column: 20, scope: !4167)
!4172 = !DILocation(line: 1411, column: 25, scope: !4167)
!4173 = !DILocation(line: 1413, column: 14, scope: !4174)
!4174 = distinct !DILexicalBlock(scope: !4167, file: !1, line: 1413, column: 14)
!4175 = !DILocation(line: 1413, column: 14, scope: !4167)
!4176 = !DILocation(line: 1414, column: 30, scope: !4177)
!4177 = distinct !DILexicalBlock(scope: !4174, file: !1, line: 1413, column: 37)
!4178 = !DILocation(line: 1414, column: 29, scope: !4177)
!4179 = !DILocation(line: 1414, column: 34, scope: !4177)
!4180 = !DILocation(line: 1414, column: 27, scope: !4177)
!4181 = !DILocation(line: 1415, column: 10, scope: !4177)
!4182 = !DILocation(line: 1416, column: 7, scope: !4167)
!4183 = !DILocation(line: 1417, column: 11, scope: !4163)
!4184 = !DILocation(line: 1404, column: 4, scope: !4185)
!4185 = !DILexicalBlockFile(scope: !382, file: !1, discriminator: 2)
!4186 = !DILocation(line: 1419, column: 11, scope: !382)
!4187 = !DILocation(line: 1419, column: 18, scope: !382)
!4188 = !DILocation(line: 1419, column: 4, scope: !382)
!4189 = !DILocation(line: 1420, column: 11, scope: !382)
!4190 = !DILocation(line: 1420, column: 4, scope: !382)
!4191 = !DILocation(line: 1422, column: 8, scope: !4192)
!4192 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1422, column: 8)
!4193 = !DILocation(line: 1422, column: 17, scope: !4192)
!4194 = !DILocation(line: 1422, column: 8, scope: !382)
!4195 = !DILocation(line: 1423, column: 11, scope: !4196)
!4196 = distinct !DILexicalBlock(scope: !4197, file: !1, line: 1423, column: 11)
!4197 = distinct !DILexicalBlock(scope: !4192, file: !1, line: 1422, column: 22)
!4198 = !DILocation(line: 1423, column: 15, scope: !4196)
!4199 = !DILocation(line: 1423, column: 22, scope: !4196)
!4200 = !DILocation(line: 1423, column: 32, scope: !4201)
!4201 = !DILexicalBlockFile(scope: !4196, file: !1, discriminator: 1)
!4202 = !DILocation(line: 1423, column: 25, scope: !4201)
!4203 = !DILocation(line: 1423, column: 40, scope: !4201)
!4204 = !DILocation(line: 1423, column: 11, scope: !4201)
!4205 = !DILocation(line: 1424, column: 15, scope: !4206)
!4206 = distinct !DILexicalBlock(scope: !4196, file: !1, line: 1423, column: 45)
!4207 = !DILocation(line: 1424, column: 25, scope: !4208)
!4208 = !DILexicalBlockFile(scope: !4206, file: !1, discriminator: 1)
!4209 = !DILocation(line: 1424, column: 15, scope: !4208)
!4210 = !DILocation(line: 1424, column: 34, scope: !4211)
!4211 = !DILexicalBlockFile(scope: !4206, file: !1, discriminator: 2)
!4212 = !DILocation(line: 1424, column: 15, scope: !4211)
!4213 = !DILocation(line: 1424, column: 15, scope: !4214)
!4214 = !DILexicalBlockFile(scope: !4206, file: !1, discriminator: 3)
!4215 = !DILocation(line: 1424, column: 12, scope: !4214)
!4216 = !DILocation(line: 1426, column: 7, scope: !4206)
!4217 = !DILocation(line: 1427, column: 20, scope: !4218)
!4218 = distinct !DILexicalBlock(scope: !4196, file: !1, line: 1426, column: 14)
!4219 = !DILocation(line: 1427, column: 25, scope: !4218)
!4220 = !DILocation(line: 1427, column: 14, scope: !4218)
!4221 = !DILocation(line: 1427, column: 12, scope: !4218)
!4222 = !DILocation(line: 1429, column: 4, scope: !4197)
!4223 = !DILocation(line: 1433, column: 19, scope: !4224)
!4224 = distinct !DILexicalBlock(scope: !4192, file: !1, line: 1429, column: 11)
!4225 = !DILocation(line: 1433, column: 22, scope: !4224)
!4226 = !DILocation(line: 1433, column: 12, scope: !4224)
!4227 = !DILocation(line: 1433, column: 10, scope: !4224)
!4228 = !DILocation(line: 1436, column: 8, scope: !4229)
!4229 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1436, column: 8)
!4230 = !DILocation(line: 1436, column: 11, scope: !4229)
!4231 = !DILocation(line: 1436, column: 8, scope: !382)
!4232 = !DILocation(line: 1436, column: 20, scope: !4233)
!4233 = !DILexicalBlockFile(scope: !4229, file: !1, discriminator: 1)
!4234 = !DILocation(line: 1438, column: 8, scope: !4235)
!4235 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1438, column: 8)
!4236 = !DILocation(line: 1438, column: 8, scope: !382)
!4237 = !DILocation(line: 1440, column: 11, scope: !4238)
!4238 = distinct !DILexicalBlock(scope: !4239, file: !1, line: 1440, column: 11)
!4239 = distinct !DILexicalBlock(scope: !4235, file: !1, line: 1438, column: 17)
!4240 = !DILocation(line: 1440, column: 25, scope: !4238)
!4241 = !DILocation(line: 1440, column: 11, scope: !4239)
!4242 = !DILocation(line: 1440, column: 44, scope: !4243)
!4243 = !DILexicalBlockFile(scope: !4238, file: !1, discriminator: 1)
!4244 = !DILocation(line: 1440, column: 30, scope: !4243)
!4245 = !DILocation(line: 1441, column: 11, scope: !4246)
!4246 = distinct !DILexicalBlock(scope: !4239, file: !1, line: 1441, column: 11)
!4247 = !DILocation(line: 1441, column: 25, scope: !4246)
!4248 = !DILocation(line: 1441, column: 11, scope: !4239)
!4249 = !DILocation(line: 1441, column: 44, scope: !4250)
!4250 = !DILexicalBlockFile(scope: !4246, file: !1, discriminator: 1)
!4251 = !DILocation(line: 1441, column: 30, scope: !4250)
!4252 = !DILocation(line: 1442, column: 37, scope: !4239)
!4253 = !DILocation(line: 1442, column: 40, scope: !4239)
!4254 = !DILocation(line: 1443, column: 30, scope: !4239)
!4255 = !DILocation(line: 1443, column: 40, scope: !4239)
!4256 = !DILocation(line: 1442, column: 14, scope: !4239)
!4257 = !DILocation(line: 1442, column: 12, scope: !4239)
!4258 = !DILocation(line: 1444, column: 4, scope: !4239)
!4259 = !DILocation(line: 1445, column: 36, scope: !4260)
!4260 = distinct !DILexicalBlock(scope: !4235, file: !1, line: 1444, column: 11)
!4261 = !DILocation(line: 1445, column: 39, scope: !4260)
!4262 = !DILocation(line: 1445, column: 49, scope: !4260)
!4263 = !DILocation(line: 1446, column: 29, scope: !4260)
!4264 = !DILocation(line: 1446, column: 36, scope: !4260)
!4265 = !DILocation(line: 1445, column: 14, scope: !4260)
!4266 = !DILocation(line: 1445, column: 12, scope: !4260)
!4267 = !DILocation(line: 1448, column: 8, scope: !4268)
!4268 = distinct !DILexicalBlock(scope: !382, file: !1, line: 1448, column: 8)
!4269 = !DILocation(line: 1448, column: 13, scope: !4268)
!4270 = !DILocation(line: 1448, column: 8, scope: !382)
!4271 = !DILocation(line: 1449, column: 11, scope: !4272)
!4272 = distinct !DILexicalBlock(scope: !4273, file: !1, line: 1449, column: 11)
!4273 = distinct !DILexicalBlock(scope: !4268, file: !1, line: 1448, column: 22)
!4274 = !DILocation(line: 1449, column: 17, scope: !4272)
!4275 = !DILocation(line: 1449, column: 14, scope: !4272)
!4276 = !DILocation(line: 1449, column: 23, scope: !4272)
!4277 = !DILocation(line: 1449, column: 26, scope: !4278)
!4278 = !DILexicalBlockFile(scope: !4272, file: !1, discriminator: 1)
!4279 = !DILocation(line: 1449, column: 32, scope: !4278)
!4280 = !DILocation(line: 1449, column: 29, scope: !4278)
!4281 = !DILocation(line: 1449, column: 11, scope: !4278)
!4282 = !DILocation(line: 1449, column: 47, scope: !4283)
!4283 = !DILexicalBlockFile(scope: !4272, file: !1, discriminator: 2)
!4284 = !DILocation(line: 1449, column: 40, scope: !4283)
!4285 = !DILocation(line: 1450, column: 7, scope: !4273)
!4286 = !DILocation(line: 1452, column: 11, scope: !382)
!4287 = !DILocation(line: 1452, column: 4, scope: !382)
!4288 = !DILocation(line: 1453, column: 1, scope: !382)
!4289 = !DILocalVariable(name: "fd", arg: 1, scope: !197, file: !1, line: 1472, type: !43)
!4290 = !DILocation(line: 1472, column: 22, scope: !197)
!4291 = !DILocalVariable(name: "mode", arg: 2, scope: !197, file: !1, line: 1473, type: !192)
!4292 = !DILocation(line: 1473, column: 30, scope: !197)
!4293 = !DILocation(line: 1475, column: 34, scope: !197)
!4294 = !DILocation(line: 1475, column: 37, scope: !197)
!4295 = !DILocation(line: 1475, column: 11, scope: !197)
!4296 = !DILocation(line: 1475, column: 4, scope: !197)
!4297 = !DILocalVariable(name: "b", arg: 1, scope: !200, file: !1, line: 1480, type: !157)
!4298 = !DILocation(line: 1480, column: 33, scope: !200)
!4299 = !DILocalVariable(name: "buf", arg: 2, scope: !200, file: !1, line: 1480, type: !19)
!4300 = !DILocation(line: 1480, column: 42, scope: !200)
!4301 = !DILocalVariable(name: "len", arg: 3, scope: !200, file: !1, line: 1480, type: !43)
!4302 = !DILocation(line: 1480, column: 51, scope: !200)
!4303 = !DILocalVariable(name: "bzerr", scope: !200, file: !1, line: 1482, type: !43)
!4304 = !DILocation(line: 1482, column: 8, scope: !200)
!4305 = !DILocalVariable(name: "nread", scope: !200, file: !1, line: 1482, type: !43)
!4306 = !DILocation(line: 1482, column: 15, scope: !200)
!4307 = !DILocation(line: 1483, column: 18, scope: !4308)
!4308 = distinct !DILexicalBlock(scope: !200, file: !1, line: 1483, column: 8)
!4309 = !DILocation(line: 1483, column: 9, scope: !4308)
!4310 = !DILocation(line: 1483, column: 22, scope: !4308)
!4311 = !DILocation(line: 1483, column: 30, scope: !4308)
!4312 = !DILocation(line: 1483, column: 8, scope: !200)
!4313 = !DILocation(line: 1483, column: 48, scope: !4314)
!4314 = !DILexicalBlockFile(scope: !4308, file: !1, discriminator: 1)
!4315 = !DILocation(line: 1484, column: 30, scope: !200)
!4316 = !DILocation(line: 1484, column: 32, scope: !200)
!4317 = !DILocation(line: 1484, column: 36, scope: !200)
!4318 = !DILocation(line: 1484, column: 12, scope: !200)
!4319 = !DILocation(line: 1484, column: 10, scope: !200)
!4320 = !DILocation(line: 1485, column: 8, scope: !4321)
!4321 = distinct !DILexicalBlock(scope: !200, file: !1, line: 1485, column: 8)
!4322 = !DILocation(line: 1485, column: 14, scope: !4321)
!4323 = !DILocation(line: 1485, column: 23, scope: !4321)
!4324 = !DILocation(line: 1485, column: 26, scope: !4325)
!4325 = !DILexicalBlockFile(scope: !4321, file: !1, discriminator: 1)
!4326 = !DILocation(line: 1485, column: 32, scope: !4325)
!4327 = !DILocation(line: 1485, column: 8, scope: !4325)
!4328 = !DILocation(line: 1486, column: 14, scope: !4329)
!4329 = distinct !DILexicalBlock(scope: !4321, file: !1, line: 1485, column: 50)
!4330 = !DILocation(line: 1486, column: 7, scope: !4329)
!4331 = !DILocation(line: 1488, column: 7, scope: !4332)
!4332 = distinct !DILexicalBlock(scope: !4321, file: !1, line: 1487, column: 11)
!4333 = !DILocation(line: 1490, column: 1, scope: !200)
!4334 = !DILocalVariable(name: "b", arg: 1, scope: !203, file: !1, line: 1494, type: !157)
!4335 = !DILocation(line: 1494, column: 34, scope: !203)
!4336 = !DILocalVariable(name: "buf", arg: 2, scope: !203, file: !1, line: 1494, type: !19)
!4337 = !DILocation(line: 1494, column: 43, scope: !203)
!4338 = !DILocalVariable(name: "len", arg: 3, scope: !203, file: !1, line: 1494, type: !43)
!4339 = !DILocation(line: 1494, column: 52, scope: !203)
!4340 = !DILocalVariable(name: "bzerr", scope: !203, file: !1, line: 1496, type: !43)
!4341 = !DILocation(line: 1496, column: 8, scope: !203)
!4342 = !DILocation(line: 1498, column: 23, scope: !203)
!4343 = !DILocation(line: 1498, column: 25, scope: !203)
!4344 = !DILocation(line: 1498, column: 29, scope: !203)
!4345 = !DILocation(line: 1498, column: 4, scope: !203)
!4346 = !DILocation(line: 1499, column: 7, scope: !4347)
!4347 = distinct !DILexicalBlock(scope: !203, file: !1, line: 1499, column: 7)
!4348 = !DILocation(line: 1499, column: 13, scope: !4347)
!4349 = !DILocation(line: 1499, column: 7, scope: !203)
!4350 = !DILocation(line: 1500, column: 14, scope: !4351)
!4351 = distinct !DILexicalBlock(scope: !4347, file: !1, line: 1499, column: 22)
!4352 = !DILocation(line: 1500, column: 7, scope: !4351)
!4353 = !DILocation(line: 1502, column: 7, scope: !4354)
!4354 = distinct !DILexicalBlock(scope: !4347, file: !1, line: 1501, column: 9)
!4355 = !DILocation(line: 1504, column: 1, scope: !203)
!4356 = !DILocalVariable(name: "b", arg: 1, scope: !204, file: !1, line: 1508, type: !157)
!4357 = !DILocation(line: 1508, column: 34, scope: !204)
!4358 = !DILocation(line: 1510, column: 10, scope: !204)
!4359 = !DILocation(line: 1512, column: 4, scope: !204)
!4360 = !DILocalVariable(name: "b", arg: 1, scope: !207, file: !1, line: 1517, type: !157)
!4361 = !DILocation(line: 1517, column: 35, scope: !207)
!4362 = !DILocalVariable(name: "bzerr", scope: !207, file: !1, line: 1519, type: !43)
!4363 = !DILocation(line: 1519, column: 8, scope: !207)
!4364 = !DILocalVariable(name: "fp", scope: !207, file: !1, line: 1520, type: !36)
!4365 = !DILocation(line: 1520, column: 10, scope: !207)
!4366 = !DILocation(line: 1522, column: 8, scope: !4367)
!4367 = distinct !DILexicalBlock(scope: !207, file: !1, line: 1522, column: 8)
!4368 = !DILocation(line: 1522, column: 9, scope: !4367)
!4369 = !DILocation(line: 1522, column: 8, scope: !207)
!4370 = !DILocation(line: 1522, column: 18, scope: !4371)
!4371 = !DILexicalBlockFile(scope: !4372, file: !1, discriminator: 1)
!4372 = distinct !DILexicalBlock(scope: !4367, file: !1, line: 1522, column: 17)
!4373 = !DILocation(line: 1523, column: 20, scope: !207)
!4374 = !DILocation(line: 1523, column: 10, scope: !207)
!4375 = !DILocation(line: 1523, column: 24, scope: !207)
!4376 = !DILocation(line: 1523, column: 7, scope: !207)
!4377 = !DILocation(line: 1524, column: 17, scope: !4378)
!4378 = distinct !DILexicalBlock(scope: !207, file: !1, line: 1524, column: 7)
!4379 = !DILocation(line: 1524, column: 8, scope: !4378)
!4380 = !DILocation(line: 1524, column: 21, scope: !4378)
!4381 = !DILocation(line: 1524, column: 7, scope: !4378)
!4382 = !DILocation(line: 1524, column: 7, scope: !207)
!4383 = !DILocation(line: 1525, column: 31, scope: !4384)
!4384 = distinct !DILexicalBlock(scope: !4378, file: !1, line: 1524, column: 29)
!4385 = !DILocation(line: 1525, column: 7, scope: !4384)
!4386 = !DILocation(line: 1526, column: 10, scope: !4387)
!4387 = distinct !DILexicalBlock(scope: !4384, file: !1, line: 1526, column: 10)
!4388 = !DILocation(line: 1526, column: 16, scope: !4387)
!4389 = !DILocation(line: 1526, column: 10, scope: !4384)
!4390 = !DILocation(line: 1527, column: 32, scope: !4391)
!4391 = distinct !DILexicalBlock(scope: !4387, file: !1, line: 1526, column: 25)
!4392 = !DILocation(line: 1527, column: 10, scope: !4391)
!4393 = !DILocation(line: 1528, column: 7, scope: !4391)
!4394 = !DILocation(line: 1529, column: 4, scope: !4384)
!4395 = !DILocation(line: 1530, column: 30, scope: !4396)
!4396 = distinct !DILexicalBlock(scope: !4378, file: !1, line: 1529, column: 9)
!4397 = !DILocation(line: 1530, column: 7, scope: !4396)
!4398 = !DILocation(line: 1532, column: 7, scope: !4399)
!4399 = distinct !DILexicalBlock(scope: !207, file: !1, line: 1532, column: 7)
!4400 = !DILocation(line: 1532, column: 11, scope: !4399)
!4401 = !DILocation(line: 1532, column: 9, scope: !4399)
!4402 = !DILocation(line: 1532, column: 17, scope: !4399)
!4403 = !DILocation(line: 1532, column: 20, scope: !4404)
!4404 = !DILexicalBlockFile(scope: !4399, file: !1, discriminator: 1)
!4405 = !DILocation(line: 1532, column: 24, scope: !4404)
!4406 = !DILocation(line: 1532, column: 22, scope: !4404)
!4407 = !DILocation(line: 1532, column: 7, scope: !4404)
!4408 = !DILocation(line: 1533, column: 14, scope: !4409)
!4409 = distinct !DILexicalBlock(scope: !4399, file: !1, line: 1532, column: 31)
!4410 = !DILocation(line: 1533, column: 7, scope: !4409)
!4411 = !DILocation(line: 1534, column: 4, scope: !4409)
!4412 = !DILocation(line: 1535, column: 1, scope: !207)
!4413 = !DILocalVariable(name: "b", arg: 1, scope: !210, file: !1, line: 1562, type: !157)
!4414 = !DILocation(line: 1562, column: 43, scope: !210)
!4415 = !DILocalVariable(name: "errnum", arg: 2, scope: !210, file: !1, line: 1562, type: !159)
!4416 = !DILocation(line: 1562, column: 51, scope: !210)
!4417 = !DILocalVariable(name: "err", scope: !210, file: !1, line: 1564, type: !43)
!4418 = !DILocation(line: 1564, column: 8, scope: !210)
!4419 = !DILocation(line: 1564, column: 25, scope: !210)
!4420 = !DILocation(line: 1564, column: 15, scope: !210)
!4421 = !DILocation(line: 1564, column: 29, scope: !210)
!4422 = !DILocation(line: 1566, column: 7, scope: !4423)
!4423 = distinct !DILexicalBlock(scope: !210, file: !1, line: 1566, column: 7)
!4424 = !DILocation(line: 1566, column: 10, scope: !4423)
!4425 = !DILocation(line: 1566, column: 7, scope: !210)
!4426 = !DILocation(line: 1566, column: 18, scope: !4427)
!4427 = !DILexicalBlockFile(scope: !4423, file: !1, discriminator: 1)
!4428 = !DILocation(line: 1566, column: 14, scope: !4427)
!4429 = !DILocation(line: 1567, column: 14, scope: !210)
!4430 = !DILocation(line: 1567, column: 5, scope: !210)
!4431 = !DILocation(line: 1567, column: 12, scope: !210)
!4432 = !DILocation(line: 1568, column: 26, scope: !210)
!4433 = !DILocation(line: 1568, column: 29, scope: !210)
!4434 = !DILocation(line: 1568, column: 11, scope: !210)
!4435 = !DILocation(line: 1568, column: 4, scope: !210)
!4436 = !DILocalVariable(name: "s", arg: 1, scope: !287, file: !1, line: 336, type: !223)
!4437 = !DILocation(line: 336, column: 39, scope: !287)
!4438 = !DILocalVariable(name: "progress_out", scope: !287, file: !1, line: 338, type: !30)
!4439 = !DILocation(line: 338, column: 9, scope: !287)
!4440 = !DILocation(line: 340, column: 4, scope: !287)
!4441 = !DILocation(line: 343, column: 11, scope: !4442)
!4442 = distinct !DILexicalBlock(scope: !4443, file: !1, line: 343, column: 11)
!4443 = distinct !DILexicalBlock(scope: !287, file: !1, line: 340, column: 17)
!4444 = !DILocation(line: 343, column: 14, scope: !4442)
!4445 = !DILocation(line: 343, column: 20, scope: !4442)
!4446 = !DILocation(line: 343, column: 30, scope: !4442)
!4447 = !DILocation(line: 343, column: 11, scope: !4443)
!4448 = !DILocation(line: 343, column: 36, scope: !4449)
!4449 = !DILexicalBlockFile(scope: !4442, file: !1, discriminator: 1)
!4450 = !DILocation(line: 346, column: 11, scope: !4451)
!4451 = distinct !DILexicalBlock(scope: !4443, file: !1, line: 346, column: 11)
!4452 = !DILocation(line: 346, column: 14, scope: !4451)
!4453 = !DILocation(line: 346, column: 31, scope: !4451)
!4454 = !DILocation(line: 346, column: 34, scope: !4451)
!4455 = !DILocation(line: 346, column: 28, scope: !4451)
!4456 = !DILocation(line: 346, column: 11, scope: !4443)
!4457 = !DILocation(line: 346, column: 40, scope: !4458)
!4458 = !DILexicalBlockFile(scope: !4451, file: !1, discriminator: 1)
!4459 = !DILocation(line: 348, column: 20, scope: !4443)
!4460 = !DILocation(line: 349, column: 39, scope: !4443)
!4461 = !DILocation(line: 349, column: 42, scope: !4443)
!4462 = !DILocation(line: 349, column: 30, scope: !4443)
!4463 = !DILocation(line: 349, column: 33, scope: !4443)
!4464 = !DILocation(line: 349, column: 9, scope: !4443)
!4465 = !DILocation(line: 349, column: 12, scope: !4443)
!4466 = !DILocation(line: 349, column: 18, scope: !4443)
!4467 = !DILocation(line: 349, column: 28, scope: !4443)
!4468 = !DILocation(line: 350, column: 7, scope: !4443)
!4469 = !DILocation(line: 350, column: 10, scope: !4443)
!4470 = !DILocation(line: 350, column: 23, scope: !4443)
!4471 = !DILocation(line: 351, column: 7, scope: !4443)
!4472 = !DILocation(line: 351, column: 10, scope: !4443)
!4473 = !DILocation(line: 351, column: 16, scope: !4443)
!4474 = !DILocation(line: 351, column: 25, scope: !4443)
!4475 = !DILocation(line: 352, column: 7, scope: !4443)
!4476 = !DILocation(line: 352, column: 10, scope: !4443)
!4477 = !DILocation(line: 352, column: 16, scope: !4443)
!4478 = !DILocation(line: 352, column: 24, scope: !4443)
!4479 = !DILocation(line: 353, column: 7, scope: !4443)
!4480 = !DILocation(line: 353, column: 10, scope: !4443)
!4481 = !DILocation(line: 353, column: 16, scope: !4443)
!4482 = !DILocation(line: 353, column: 30, scope: !4443)
!4483 = !DILocation(line: 354, column: 11, scope: !4484)
!4484 = distinct !DILexicalBlock(scope: !4443, file: !1, line: 354, column: 11)
!4485 = !DILocation(line: 354, column: 14, scope: !4484)
!4486 = !DILocation(line: 354, column: 20, scope: !4484)
!4487 = !DILocation(line: 354, column: 35, scope: !4484)
!4488 = !DILocation(line: 354, column: 11, scope: !4443)
!4489 = !DILocation(line: 354, column: 41, scope: !4490)
!4490 = !DILexicalBlockFile(scope: !4484, file: !1, discriminator: 1)
!4491 = !DILocation(line: 354, column: 44, scope: !4490)
!4492 = !DILocation(line: 354, column: 50, scope: !4490)
!4493 = !DILocation(line: 354, column: 64, scope: !4490)
!4494 = !DILocation(line: 340, column: 4, scope: !4495)
!4495 = !DILexicalBlockFile(scope: !287, file: !1, discriminator: 1)
!4496 = !DILocation(line: 357, column: 11, scope: !287)
!4497 = !DILocation(line: 357, column: 4, scope: !287)
!4498 = !DILocalVariable(name: "s", arg: 1, scope: !290, file: !1, line: 291, type: !223)
!4499 = !DILocation(line: 291, column: 38, scope: !290)
!4500 = !DILocalVariable(name: "progress_in", scope: !290, file: !1, line: 293, type: !30)
!4501 = !DILocation(line: 293, column: 9, scope: !290)
!4502 = !DILocation(line: 295, column: 8, scope: !4503)
!4503 = distinct !DILexicalBlock(scope: !290, file: !1, line: 295, column: 8)
!4504 = !DILocation(line: 295, column: 11, scope: !4503)
!4505 = !DILocation(line: 295, column: 16, scope: !4503)
!4506 = !DILocation(line: 295, column: 8, scope: !290)
!4507 = !DILocation(line: 298, column: 7, scope: !4508)
!4508 = distinct !DILexicalBlock(scope: !4503, file: !1, line: 295, column: 33)
!4509 = !DILocation(line: 300, column: 14, scope: !4510)
!4510 = distinct !DILexicalBlock(scope: !4511, file: !1, line: 300, column: 14)
!4511 = distinct !DILexicalBlock(scope: !4508, file: !1, line: 298, column: 20)
!4512 = !DILocation(line: 300, column: 17, scope: !4510)
!4513 = !DILocation(line: 300, column: 27, scope: !4510)
!4514 = !DILocation(line: 300, column: 30, scope: !4510)
!4515 = !DILocation(line: 300, column: 24, scope: !4510)
!4516 = !DILocation(line: 300, column: 14, scope: !4511)
!4517 = !DILocation(line: 300, column: 41, scope: !4518)
!4518 = !DILexicalBlockFile(scope: !4510, file: !1, discriminator: 1)
!4519 = !DILocation(line: 302, column: 14, scope: !4520)
!4520 = distinct !DILexicalBlock(scope: !4511, file: !1, line: 302, column: 14)
!4521 = !DILocation(line: 302, column: 17, scope: !4520)
!4522 = !DILocation(line: 302, column: 23, scope: !4520)
!4523 = !DILocation(line: 302, column: 32, scope: !4520)
!4524 = !DILocation(line: 302, column: 14, scope: !4511)
!4525 = !DILocation(line: 302, column: 38, scope: !4526)
!4526 = !DILexicalBlockFile(scope: !4520, file: !1, discriminator: 1)
!4527 = !DILocation(line: 303, column: 22, scope: !4511)
!4528 = !DILocalVariable(name: "zchh", scope: !4529, file: !1, line: 304, type: !28)
!4529 = distinct !DILexicalBlock(scope: !4511, file: !1, line: 304, column: 10)
!4530 = !DILocation(line: 304, column: 10, scope: !4529)
!4531 = !DILocation(line: 304, column: 10, scope: !4532)
!4532 = distinct !DILexicalBlock(scope: !4529, file: !1, line: 304, column: 10)
!4533 = !DILocation(line: 304, column: 10, scope: !4534)
!4534 = !DILexicalBlockFile(scope: !4532, file: !1, discriminator: 1)
!4535 = !DILocalVariable(name: "ch", scope: !4536, file: !1, line: 304, type: !21)
!4536 = distinct !DILexicalBlock(scope: !4532, file: !1, line: 304, column: 10)
!4537 = !DILocation(line: 304, column: 10, scope: !4536)
!4538 = !DILocation(line: 304, column: 10, scope: !4539)
!4539 = !DILexicalBlockFile(scope: !4536, file: !1, discriminator: 2)
!4540 = !DILocation(line: 304, column: 10, scope: !4541)
!4541 = !DILexicalBlockFile(scope: !4542, file: !1, discriminator: 3)
!4542 = distinct !DILexicalBlock(scope: !4532, file: !1, line: 304, column: 10)
!4543 = !DILocation(line: 304, column: 10, scope: !4544)
!4544 = !DILexicalBlockFile(scope: !4542, file: !1, discriminator: 4)
!4545 = !DILocation(line: 304, column: 10, scope: !4546)
!4546 = !DILexicalBlockFile(scope: !4547, file: !1, discriminator: 5)
!4547 = distinct !DILexicalBlock(scope: !4548, file: !1, line: 304, column: 10)
!4548 = distinct !DILexicalBlock(scope: !4542, file: !1, line: 304, column: 10)
!4549 = !DILocation(line: 304, column: 10, scope: !4550)
!4550 = !DILexicalBlockFile(scope: !4547, file: !1, discriminator: 6)
!4551 = !DILocation(line: 304, column: 10, scope: !4552)
!4552 = !DILexicalBlockFile(scope: !4548, file: !1, discriminator: 7)
!4553 = !DILocation(line: 304, column: 10, scope: !4554)
!4554 = !DILexicalBlockFile(scope: !4555, file: !1, discriminator: 8)
!4555 = distinct !DILexicalBlock(scope: !4542, file: !1, line: 304, column: 10)
!4556 = !DILocation(line: 305, column: 10, scope: !4511)
!4557 = !DILocation(line: 305, column: 13, scope: !4511)
!4558 = !DILocation(line: 305, column: 19, scope: !4511)
!4559 = !DILocation(line: 305, column: 26, scope: !4511)
!4560 = !DILocation(line: 306, column: 10, scope: !4511)
!4561 = !DILocation(line: 306, column: 13, scope: !4511)
!4562 = !DILocation(line: 306, column: 19, scope: !4511)
!4563 = !DILocation(line: 306, column: 27, scope: !4511)
!4564 = !DILocation(line: 307, column: 10, scope: !4511)
!4565 = !DILocation(line: 307, column: 13, scope: !4511)
!4566 = !DILocation(line: 307, column: 19, scope: !4511)
!4567 = !DILocation(line: 307, column: 32, scope: !4511)
!4568 = !DILocation(line: 308, column: 14, scope: !4569)
!4569 = distinct !DILexicalBlock(scope: !4511, file: !1, line: 308, column: 14)
!4570 = !DILocation(line: 308, column: 17, scope: !4569)
!4571 = !DILocation(line: 308, column: 23, scope: !4569)
!4572 = !DILocation(line: 308, column: 37, scope: !4569)
!4573 = !DILocation(line: 308, column: 14, scope: !4511)
!4574 = !DILocation(line: 308, column: 43, scope: !4575)
!4575 = !DILexicalBlockFile(scope: !4569, file: !1, discriminator: 1)
!4576 = !DILocation(line: 308, column: 46, scope: !4575)
!4577 = !DILocation(line: 308, column: 52, scope: !4575)
!4578 = !DILocation(line: 308, column: 65, scope: !4575)
!4579 = !DILocation(line: 298, column: 7, scope: !4580)
!4580 = !DILexicalBlockFile(scope: !4508, file: !1, discriminator: 1)
!4581 = !DILocation(line: 311, column: 4, scope: !4508)
!4582 = !DILocation(line: 314, column: 7, scope: !4583)
!4583 = distinct !DILexicalBlock(scope: !4503, file: !1, line: 311, column: 11)
!4584 = !DILocation(line: 316, column: 14, scope: !4585)
!4585 = distinct !DILexicalBlock(scope: !4586, file: !1, line: 316, column: 14)
!4586 = distinct !DILexicalBlock(scope: !4583, file: !1, line: 314, column: 20)
!4587 = !DILocation(line: 316, column: 17, scope: !4585)
!4588 = !DILocation(line: 316, column: 27, scope: !4585)
!4589 = !DILocation(line: 316, column: 30, scope: !4585)
!4590 = !DILocation(line: 316, column: 24, scope: !4585)
!4591 = !DILocation(line: 316, column: 14, scope: !4586)
!4592 = !DILocation(line: 316, column: 41, scope: !4593)
!4593 = !DILexicalBlockFile(scope: !4585, file: !1, discriminator: 1)
!4594 = !DILocation(line: 318, column: 14, scope: !4595)
!4595 = distinct !DILexicalBlock(scope: !4586, file: !1, line: 318, column: 14)
!4596 = !DILocation(line: 318, column: 17, scope: !4595)
!4597 = !DILocation(line: 318, column: 23, scope: !4595)
!4598 = !DILocation(line: 318, column: 32, scope: !4595)
!4599 = !DILocation(line: 318, column: 14, scope: !4586)
!4600 = !DILocation(line: 318, column: 38, scope: !4601)
!4601 = !DILexicalBlockFile(scope: !4595, file: !1, discriminator: 1)
!4602 = !DILocation(line: 320, column: 14, scope: !4603)
!4603 = distinct !DILexicalBlock(scope: !4586, file: !1, line: 320, column: 14)
!4604 = !DILocation(line: 320, column: 17, scope: !4603)
!4605 = !DILocation(line: 320, column: 33, scope: !4603)
!4606 = !DILocation(line: 320, column: 14, scope: !4586)
!4607 = !DILocation(line: 320, column: 39, scope: !4608)
!4608 = !DILexicalBlockFile(scope: !4603, file: !1, discriminator: 1)
!4609 = !DILocation(line: 321, column: 22, scope: !4586)
!4610 = !DILocalVariable(name: "zchh", scope: !4611, file: !1, line: 322, type: !28)
!4611 = distinct !DILexicalBlock(scope: !4586, file: !1, line: 322, column: 10)
!4612 = !DILocation(line: 322, column: 10, scope: !4611)
!4613 = !DILocation(line: 322, column: 10, scope: !4614)
!4614 = distinct !DILexicalBlock(scope: !4611, file: !1, line: 322, column: 10)
!4615 = !DILocation(line: 322, column: 10, scope: !4616)
!4616 = !DILexicalBlockFile(scope: !4614, file: !1, discriminator: 1)
!4617 = !DILocalVariable(name: "ch", scope: !4618, file: !1, line: 322, type: !21)
!4618 = distinct !DILexicalBlock(scope: !4614, file: !1, line: 322, column: 10)
!4619 = !DILocation(line: 322, column: 10, scope: !4618)
!4620 = !DILocation(line: 322, column: 10, scope: !4621)
!4621 = !DILexicalBlockFile(scope: !4618, file: !1, discriminator: 2)
!4622 = !DILocation(line: 322, column: 10, scope: !4623)
!4623 = !DILexicalBlockFile(scope: !4624, file: !1, discriminator: 3)
!4624 = distinct !DILexicalBlock(scope: !4614, file: !1, line: 322, column: 10)
!4625 = !DILocation(line: 322, column: 10, scope: !4626)
!4626 = !DILexicalBlockFile(scope: !4624, file: !1, discriminator: 4)
!4627 = !DILocation(line: 322, column: 10, scope: !4628)
!4628 = !DILexicalBlockFile(scope: !4629, file: !1, discriminator: 5)
!4629 = distinct !DILexicalBlock(scope: !4630, file: !1, line: 322, column: 10)
!4630 = distinct !DILexicalBlock(scope: !4624, file: !1, line: 322, column: 10)
!4631 = !DILocation(line: 322, column: 10, scope: !4632)
!4632 = !DILexicalBlockFile(scope: !4629, file: !1, discriminator: 6)
!4633 = !DILocation(line: 322, column: 10, scope: !4634)
!4634 = !DILexicalBlockFile(scope: !4630, file: !1, discriminator: 7)
!4635 = !DILocation(line: 322, column: 10, scope: !4636)
!4636 = !DILexicalBlockFile(scope: !4637, file: !1, discriminator: 8)
!4637 = distinct !DILexicalBlock(scope: !4624, file: !1, line: 322, column: 10)
!4638 = !DILocation(line: 323, column: 10, scope: !4586)
!4639 = !DILocation(line: 323, column: 13, scope: !4586)
!4640 = !DILocation(line: 323, column: 19, scope: !4586)
!4641 = !DILocation(line: 323, column: 26, scope: !4586)
!4642 = !DILocation(line: 324, column: 10, scope: !4586)
!4643 = !DILocation(line: 324, column: 13, scope: !4586)
!4644 = !DILocation(line: 324, column: 19, scope: !4586)
!4645 = !DILocation(line: 324, column: 27, scope: !4586)
!4646 = !DILocation(line: 325, column: 10, scope: !4586)
!4647 = !DILocation(line: 325, column: 13, scope: !4586)
!4648 = !DILocation(line: 325, column: 19, scope: !4586)
!4649 = !DILocation(line: 325, column: 32, scope: !4586)
!4650 = !DILocation(line: 326, column: 14, scope: !4651)
!4651 = distinct !DILexicalBlock(scope: !4586, file: !1, line: 326, column: 14)
!4652 = !DILocation(line: 326, column: 17, scope: !4651)
!4653 = !DILocation(line: 326, column: 23, scope: !4651)
!4654 = !DILocation(line: 326, column: 37, scope: !4651)
!4655 = !DILocation(line: 326, column: 14, scope: !4586)
!4656 = !DILocation(line: 326, column: 43, scope: !4657)
!4657 = !DILexicalBlockFile(scope: !4651, file: !1, discriminator: 1)
!4658 = !DILocation(line: 326, column: 46, scope: !4657)
!4659 = !DILocation(line: 326, column: 52, scope: !4657)
!4660 = !DILocation(line: 326, column: 65, scope: !4657)
!4661 = !DILocation(line: 327, column: 10, scope: !4586)
!4662 = !DILocation(line: 327, column: 13, scope: !4586)
!4663 = !DILocation(line: 327, column: 28, scope: !4586)
!4664 = !DILocation(line: 314, column: 7, scope: !4665)
!4665 = !DILexicalBlockFile(scope: !4583, file: !1, discriminator: 1)
!4666 = !DILocation(line: 330, column: 11, scope: !290)
!4667 = !DILocation(line: 330, column: 4, scope: !290)
!4668 = !DILocalVariable(name: "s", arg: 1, scope: !292, file: !1, line: 254, type: !223)
!4669 = !DILocation(line: 254, column: 25, scope: !292)
!4670 = !DILocation(line: 256, column: 8, scope: !4671)
!4671 = distinct !DILexicalBlock(scope: !292, file: !1, line: 256, column: 8)
!4672 = !DILocation(line: 256, column: 11, scope: !4671)
!4673 = !DILocation(line: 256, column: 23, scope: !4671)
!4674 = !DILocation(line: 256, column: 8, scope: !292)
!4675 = !DILocation(line: 256, column: 50, scope: !4676)
!4676 = !DILexicalBlockFile(scope: !4671, file: !1, discriminator: 1)
!4677 = !DILocation(line: 256, column: 30, scope: !4676)
!4678 = !DILocation(line: 257, column: 14, scope: !292)
!4679 = !DILocation(line: 257, column: 4, scope: !292)
!4680 = !DILocation(line: 258, column: 1, scope: !292)
!4681 = !DILocalVariable(name: "s", arg: 1, scope: !291, file: !1, line: 218, type: !223)
!4682 = !DILocation(line: 218, column: 34, scope: !291)
!4683 = !DILocalVariable(name: "i", scope: !291, file: !1, line: 220, type: !103)
!4684 = !DILocation(line: 220, column: 10, scope: !291)
!4685 = !DILocalVariable(name: "ch", scope: !291, file: !1, line: 221, type: !21)
!4686 = !DILocation(line: 221, column: 10, scope: !291)
!4687 = !DILocation(line: 221, column: 23, scope: !291)
!4688 = !DILocation(line: 221, column: 26, scope: !291)
!4689 = !DILocation(line: 221, column: 15, scope: !291)
!4690 = !DILocation(line: 222, column: 11, scope: !4691)
!4691 = distinct !DILexicalBlock(scope: !291, file: !1, line: 222, column: 4)
!4692 = !DILocation(line: 222, column: 9, scope: !4691)
!4693 = !DILocation(line: 222, column: 16, scope: !4694)
!4694 = !DILexicalBlockFile(scope: !4695, file: !1, discriminator: 1)
!4695 = distinct !DILexicalBlock(scope: !4691, file: !1, line: 222, column: 4)
!4696 = !DILocation(line: 222, column: 20, scope: !4694)
!4697 = !DILocation(line: 222, column: 23, scope: !4694)
!4698 = !DILocation(line: 222, column: 18, scope: !4694)
!4699 = !DILocation(line: 222, column: 4, scope: !4694)
!4700 = !DILocation(line: 223, column: 7, scope: !4701)
!4701 = distinct !DILexicalBlock(scope: !4702, file: !1, line: 223, column: 7)
!4702 = distinct !DILexicalBlock(scope: !4695, file: !1, line: 222, column: 42)
!4703 = !DILocation(line: 224, column: 4, scope: !4702)
!4704 = !DILocation(line: 222, column: 38, scope: !4705)
!4705 = !DILexicalBlockFile(scope: !4695, file: !1, discriminator: 2)
!4706 = !DILocation(line: 222, column: 4, scope: !4705)
!4707 = !DILocation(line: 225, column: 13, scope: !291)
!4708 = !DILocation(line: 225, column: 16, scope: !291)
!4709 = !DILocation(line: 225, column: 4, scope: !291)
!4710 = !DILocation(line: 225, column: 7, scope: !291)
!4711 = !DILocation(line: 225, column: 29, scope: !291)
!4712 = !DILocation(line: 226, column: 12, scope: !291)
!4713 = !DILocation(line: 226, column: 15, scope: !291)
!4714 = !DILocation(line: 226, column: 4, scope: !291)
!4715 = !DILocation(line: 228, column: 39, scope: !4716)
!4716 = distinct !DILexicalBlock(scope: !291, file: !1, line: 226, column: 29)
!4717 = !DILocation(line: 228, column: 19, scope: !4716)
!4718 = !DILocation(line: 228, column: 22, scope: !4716)
!4719 = !DILocation(line: 228, column: 10, scope: !4716)
!4720 = !DILocation(line: 228, column: 13, scope: !4716)
!4721 = !DILocation(line: 228, column: 30, scope: !4716)
!4722 = !DILocation(line: 228, column: 43, scope: !4716)
!4723 = !DILocation(line: 228, column: 46, scope: !4716)
!4724 = !DILocation(line: 228, column: 52, scope: !4716)
!4725 = !DILocation(line: 229, column: 10, scope: !4716)
!4726 = !DILocation(line: 231, column: 39, scope: !4716)
!4727 = !DILocation(line: 231, column: 19, scope: !4716)
!4728 = !DILocation(line: 231, column: 22, scope: !4716)
!4729 = !DILocation(line: 231, column: 10, scope: !4716)
!4730 = !DILocation(line: 231, column: 13, scope: !4716)
!4731 = !DILocation(line: 231, column: 30, scope: !4716)
!4732 = !DILocation(line: 231, column: 43, scope: !4716)
!4733 = !DILocation(line: 231, column: 46, scope: !4716)
!4734 = !DILocation(line: 231, column: 52, scope: !4716)
!4735 = !DILocation(line: 232, column: 39, scope: !4716)
!4736 = !DILocation(line: 232, column: 19, scope: !4716)
!4737 = !DILocation(line: 232, column: 22, scope: !4716)
!4738 = !DILocation(line: 232, column: 10, scope: !4716)
!4739 = !DILocation(line: 232, column: 13, scope: !4716)
!4740 = !DILocation(line: 232, column: 30, scope: !4716)
!4741 = !DILocation(line: 232, column: 43, scope: !4716)
!4742 = !DILocation(line: 232, column: 46, scope: !4716)
!4743 = !DILocation(line: 232, column: 52, scope: !4716)
!4744 = !DILocation(line: 233, column: 10, scope: !4716)
!4745 = !DILocation(line: 235, column: 39, scope: !4716)
!4746 = !DILocation(line: 235, column: 19, scope: !4716)
!4747 = !DILocation(line: 235, column: 22, scope: !4716)
!4748 = !DILocation(line: 235, column: 10, scope: !4716)
!4749 = !DILocation(line: 235, column: 13, scope: !4716)
!4750 = !DILocation(line: 235, column: 30, scope: !4716)
!4751 = !DILocation(line: 235, column: 43, scope: !4716)
!4752 = !DILocation(line: 235, column: 46, scope: !4716)
!4753 = !DILocation(line: 235, column: 52, scope: !4716)
!4754 = !DILocation(line: 236, column: 39, scope: !4716)
!4755 = !DILocation(line: 236, column: 19, scope: !4716)
!4756 = !DILocation(line: 236, column: 22, scope: !4716)
!4757 = !DILocation(line: 236, column: 10, scope: !4716)
!4758 = !DILocation(line: 236, column: 13, scope: !4716)
!4759 = !DILocation(line: 236, column: 30, scope: !4716)
!4760 = !DILocation(line: 236, column: 43, scope: !4716)
!4761 = !DILocation(line: 236, column: 46, scope: !4716)
!4762 = !DILocation(line: 236, column: 52, scope: !4716)
!4763 = !DILocation(line: 237, column: 39, scope: !4716)
!4764 = !DILocation(line: 237, column: 19, scope: !4716)
!4765 = !DILocation(line: 237, column: 22, scope: !4716)
!4766 = !DILocation(line: 237, column: 10, scope: !4716)
!4767 = !DILocation(line: 237, column: 13, scope: !4716)
!4768 = !DILocation(line: 237, column: 30, scope: !4716)
!4769 = !DILocation(line: 237, column: 43, scope: !4716)
!4770 = !DILocation(line: 237, column: 46, scope: !4716)
!4771 = !DILocation(line: 237, column: 52, scope: !4716)
!4772 = !DILocation(line: 238, column: 10, scope: !4716)
!4773 = !DILocation(line: 240, column: 19, scope: !4716)
!4774 = !DILocation(line: 240, column: 22, scope: !4716)
!4775 = !DILocation(line: 240, column: 34, scope: !4716)
!4776 = !DILocation(line: 240, column: 10, scope: !4716)
!4777 = !DILocation(line: 240, column: 13, scope: !4716)
!4778 = !DILocation(line: 240, column: 38, scope: !4716)
!4779 = !DILocation(line: 241, column: 39, scope: !4716)
!4780 = !DILocation(line: 241, column: 19, scope: !4716)
!4781 = !DILocation(line: 241, column: 22, scope: !4716)
!4782 = !DILocation(line: 241, column: 10, scope: !4716)
!4783 = !DILocation(line: 241, column: 13, scope: !4716)
!4784 = !DILocation(line: 241, column: 30, scope: !4716)
!4785 = !DILocation(line: 241, column: 43, scope: !4716)
!4786 = !DILocation(line: 241, column: 46, scope: !4716)
!4787 = !DILocation(line: 241, column: 52, scope: !4716)
!4788 = !DILocation(line: 242, column: 39, scope: !4716)
!4789 = !DILocation(line: 242, column: 19, scope: !4716)
!4790 = !DILocation(line: 242, column: 22, scope: !4716)
!4791 = !DILocation(line: 242, column: 10, scope: !4716)
!4792 = !DILocation(line: 242, column: 13, scope: !4716)
!4793 = !DILocation(line: 242, column: 30, scope: !4716)
!4794 = !DILocation(line: 242, column: 43, scope: !4716)
!4795 = !DILocation(line: 242, column: 46, scope: !4716)
!4796 = !DILocation(line: 242, column: 52, scope: !4716)
!4797 = !DILocation(line: 243, column: 39, scope: !4716)
!4798 = !DILocation(line: 243, column: 19, scope: !4716)
!4799 = !DILocation(line: 243, column: 22, scope: !4716)
!4800 = !DILocation(line: 243, column: 10, scope: !4716)
!4801 = !DILocation(line: 243, column: 13, scope: !4716)
!4802 = !DILocation(line: 243, column: 30, scope: !4716)
!4803 = !DILocation(line: 243, column: 43, scope: !4716)
!4804 = !DILocation(line: 243, column: 46, scope: !4716)
!4805 = !DILocation(line: 243, column: 52, scope: !4716)
!4806 = !DILocation(line: 244, column: 39, scope: !4716)
!4807 = !DILocation(line: 244, column: 19, scope: !4716)
!4808 = !DILocation(line: 244, column: 22, scope: !4716)
!4809 = !DILocation(line: 244, column: 10, scope: !4716)
!4810 = !DILocation(line: 244, column: 13, scope: !4716)
!4811 = !DILocation(line: 244, column: 30, scope: !4716)
!4812 = !DILocation(line: 244, column: 43, scope: !4716)
!4813 = !DILocation(line: 244, column: 46, scope: !4716)
!4814 = !DILocation(line: 244, column: 52, scope: !4716)
!4815 = !DILocation(line: 245, column: 41, scope: !4716)
!4816 = !DILocation(line: 245, column: 44, scope: !4716)
!4817 = !DILocation(line: 245, column: 56, scope: !4716)
!4818 = !DILocation(line: 245, column: 33, scope: !4716)
!4819 = !DILocation(line: 245, column: 19, scope: !4716)
!4820 = !DILocation(line: 245, column: 22, scope: !4716)
!4821 = !DILocation(line: 245, column: 10, scope: !4716)
!4822 = !DILocation(line: 245, column: 13, scope: !4716)
!4823 = !DILocation(line: 245, column: 30, scope: !4716)
!4824 = !DILocation(line: 246, column: 10, scope: !4716)
!4825 = !DILocation(line: 246, column: 13, scope: !4716)
!4826 = !DILocation(line: 246, column: 19, scope: !4716)
!4827 = !DILocation(line: 247, column: 10, scope: !4716)
!4828 = !DILocation(line: 249, column: 1, scope: !291)
