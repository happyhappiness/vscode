; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/tty.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.uv_spinlock_t = type { i32 }
%struct.termios = type { i32, i32, i32, i32, i8, [32 x i8], i32, i32 }
%struct.uv_loop_s = type { i8*, i32, [2 x i8*], [2 x i8*], i32, i64, i32, [2 x i8*], [2 x i8*], %struct.uv__io_s**, i32, i32, [2 x i8*], %union.pthread_mutex_t, %struct.uv_async_s, %union.pthread_rwlock_t, %struct.uv_handle_s*, [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], [2 x i8*], void ()*, %struct.uv__io_s, i32, %struct.anon.1, i64, i64, [2 x i32], %struct.uv__io_s, %struct.uv_signal_s, i32, %struct.uv__io_s, i8*, i32 }
%union.pthread_mutex_t = type { %struct.__pthread_mutex_s }
%struct.__pthread_mutex_s = type { i32, i32, i32, i32, i32, i16, i16, %struct.__pthread_internal_list }
%struct.__pthread_internal_list = type { %struct.__pthread_internal_list*, %struct.__pthread_internal_list* }
%struct.uv_async_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.0, %struct.uv_handle_s*, i32, void (%struct.uv_async_s*)*, [2 x i8*], i32 }
%union.anon.0 = type { [4 x i8*] }
%union.pthread_rwlock_t = type { %struct.anon }
%struct.anon = type { i32, i32, i32, i32, i32, i32, i32, i32, i64, i64, i32 }
%struct.uv_handle_s = type { i8*, %struct.uv_loop_s*, i32, {}*, [2 x i8*], %union.anon, %struct.uv_handle_s*, i32 }
%union.anon = type { [4 x i8*] }
%struct.anon.1 = type { i8*, i32 }
%struct.uv_signal_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.2, %struct.uv_handle_s*, i32, void (%struct.uv_signal_s*, i32)*, i32, %struct.anon.3, i32, i32 }
%union.anon.2 = type { [4 x i8*] }
%struct.anon.3 = type { %struct.uv_signal_s*, %struct.uv_signal_s*, %struct.uv_signal_s*, i32 }
%struct.uv__io_s = type { void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)*, [2 x i8*], [2 x i8*], i32, i32, i32 }
%struct.uv_tty_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8*, %struct.termios, i32 }
%union.anon.4 = type { [4 x i8*] }
%struct.uv_buf_t = type { i8*, i64 }
%struct.uv_stream_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.5, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, {}*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.5 = type { [4 x i8*] }
%struct.uv_connect_s = type { i8*, i32, [2 x i8*], [4 x i8*], void (%struct.uv_connect_s*, i32)*, %struct.uv_stream_s*, [2 x i8*] }
%struct.uv_shutdown_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_stream_s*, void (%struct.uv_shutdown_s*, i32)* }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.stat = type { i64, i64, i64, i32, i32, i32, i32, i64, i64, i64, i64, %struct.timespec, %struct.timespec, %struct.timespec, [3 x i64] }
%struct.timespec = type { i64, i64 }
%union.__SOCKADDR_ARG = type { %struct.sockaddr* }
%struct.winsize = type { i16, i16, i16, i16 }

@termios_spinlock = internal global %struct.uv_spinlock_t zeroinitializer, align 4
@orig_termios_fd = internal global i32 -1, align 4
@orig_termios = internal global %struct.termios zeroinitializer, align 4
@.str = private unnamed_addr constant [18 x i8] c"tio != ((void*)0)\00", align 1
@.str.1 = private unnamed_addr constant [67 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/tty.c\00", align 1
@__PRETTY_FUNCTION__.uv__tty_make_raw = private unnamed_addr constant [40 x i8] c"void uv__tty_make_raw(struct termios *)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_tty_init(%struct.uv_loop_s* %loop, %struct.uv_tty_s* %tty, i32 %fd, i32 %readable) #0 !dbg !369 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %tty.addr = alloca %struct.uv_tty_s*, align 8
  %fd.addr = alloca i32, align 4
  %readable.addr = alloca i32, align 4
  %type = alloca i32, align 4
  %flags = alloca i32, align 4
  %newfd = alloca i32, align 4
  %r = alloca i32, align 4
  %saved_flags = alloca i32, align 4
  %path = alloca [256 x i8], align 16
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !469, metadata !470), !dbg !471
  store %struct.uv_tty_s* %tty, %struct.uv_tty_s** %tty.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tty_s** %tty.addr, metadata !472, metadata !470), !dbg !473
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !474, metadata !470), !dbg !475
  store i32 %readable, i32* %readable.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %readable.addr, metadata !476, metadata !470), !dbg !477
  call void @llvm.dbg.declare(metadata i32* %type, metadata !478, metadata !470), !dbg !479
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !480, metadata !470), !dbg !481
  store i32 0, i32* %flags, align 4, !dbg !481
  call void @llvm.dbg.declare(metadata i32* %newfd, metadata !482, metadata !470), !dbg !483
  store i32 -1, i32* %newfd, align 4, !dbg !483
  call void @llvm.dbg.declare(metadata i32* %r, metadata !484, metadata !470), !dbg !485
  call void @llvm.dbg.declare(metadata i32* %saved_flags, metadata !486, metadata !470), !dbg !487
  call void @llvm.dbg.declare(metadata [256 x i8]* %path, metadata !488, metadata !470), !dbg !492
  %0 = load i32, i32* %fd.addr, align 4, !dbg !493
  %call = call i32 @uv_guess_handle(i32 %0), !dbg !494
  store i32 %call, i32* %type, align 4, !dbg !495
  %1 = load i32, i32* %type, align 4, !dbg !496
  %cmp = icmp eq i32 %1, 17, !dbg !498
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !499

lor.lhs.false:                                    ; preds = %entry
  %2 = load i32, i32* %type, align 4, !dbg !500
  %cmp1 = icmp eq i32 %2, 0, !dbg !502
  br i1 %cmp1, label %if.then, label %if.end, !dbg !503

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -22, i32* %retval, align 4, !dbg !504
  br label %return, !dbg !504

if.end:                                           ; preds = %lor.lhs.false
  %3 = load i32, i32* %type, align 4, !dbg !505
  %cmp2 = icmp eq i32 %3, 14, !dbg !507
  br i1 %cmp2, label %if.then3, label %if.end24, !dbg !508

if.then3:                                         ; preds = %if.end
  %4 = load i32, i32* %fd.addr, align 4, !dbg !509
  %call4 = call i32 @uv__tty_is_slave(i32 %4), !dbg !512
  %tobool = icmp ne i32 %call4, 0, !dbg !512
  br i1 %tobool, label %land.lhs.true, label %if.else, !dbg !513

land.lhs.true:                                    ; preds = %if.then3
  %5 = load i32, i32* %fd.addr, align 4, !dbg !514
  %arraydecay = getelementptr inbounds [256 x i8], [256 x i8]* %path, i32 0, i32 0, !dbg !516
  %call5 = call i32 @ttyname_r(i32 %5, i8* %arraydecay, i64 256) #7, !dbg !517
  %cmp6 = icmp eq i32 %call5, 0, !dbg !518
  br i1 %cmp6, label %if.then7, label %if.else, !dbg !519

if.then7:                                         ; preds = %land.lhs.true
  %arraydecay8 = getelementptr inbounds [256 x i8], [256 x i8]* %path, i32 0, i32 0, !dbg !520
  %call9 = call i32 @uv__open_cloexec(i8* %arraydecay8, i32 2), !dbg !521
  store i32 %call9, i32* %r, align 4, !dbg !522
  br label %if.end10, !dbg !523

if.else:                                          ; preds = %land.lhs.true, %if.then3
  store i32 -1, i32* %r, align 4, !dbg !524
  br label %if.end10

if.end10:                                         ; preds = %if.else, %if.then7
  %6 = load i32, i32* %r, align 4, !dbg !525
  %cmp11 = icmp slt i32 %6, 0, !dbg !527
  br i1 %cmp11, label %if.then12, label %if.end16, !dbg !528

if.then12:                                        ; preds = %if.end10
  %7 = load i32, i32* %readable.addr, align 4, !dbg !529
  %tobool13 = icmp ne i32 %7, 0, !dbg !529
  br i1 %tobool13, label %if.end15, label %if.then14, !dbg !532

if.then14:                                        ; preds = %if.then12
  %8 = load i32, i32* %flags, align 4, !dbg !533
  %or = or i32 %8, 128, !dbg !533
  store i32 %or, i32* %flags, align 4, !dbg !533
  br label %if.end15, !dbg !534

if.end15:                                         ; preds = %if.then14, %if.then12
  br label %skip, !dbg !535

if.end16:                                         ; preds = %if.end10
  %9 = load i32, i32* %r, align 4, !dbg !536
  store i32 %9, i32* %newfd, align 4, !dbg !537
  %10 = load i32, i32* %newfd, align 4, !dbg !538
  %11 = load i32, i32* %fd.addr, align 4, !dbg !539
  %call17 = call i32 @uv__dup2_cloexec(i32 %10, i32 %11), !dbg !540
  store i32 %call17, i32* %r, align 4, !dbg !541
  %12 = load i32, i32* %r, align 4, !dbg !542
  %cmp18 = icmp slt i32 %12, 0, !dbg !544
  br i1 %cmp18, label %land.lhs.true19, label %if.end23, !dbg !545

land.lhs.true19:                                  ; preds = %if.end16
  %13 = load i32, i32* %r, align 4, !dbg !546
  %cmp20 = icmp ne i32 %13, -22, !dbg !548
  br i1 %cmp20, label %if.then21, label %if.end23, !dbg !549

if.then21:                                        ; preds = %land.lhs.true19
  %14 = load i32, i32* %newfd, align 4, !dbg !550
  %call22 = call i32 @uv__close(i32 %14), !dbg !552
  %15 = load i32, i32* %r, align 4, !dbg !553
  store i32 %15, i32* %retval, align 4, !dbg !554
  br label %return, !dbg !554

if.end23:                                         ; preds = %land.lhs.true19, %if.end16
  %16 = load i32, i32* %newfd, align 4, !dbg !555
  store i32 %16, i32* %fd.addr, align 4, !dbg !556
  br label %if.end24, !dbg !557

if.end24:                                         ; preds = %if.end23, %if.end
  br label %skip, !dbg !558

skip:                                             ; preds = %if.end24, %if.end15
  %17 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !559
  %18 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !560
  %19 = bitcast %struct.uv_tty_s* %18 to %struct.uv_stream_s*, !dbg !561
  call void @uv__stream_init(%struct.uv_loop_s* %17, %struct.uv_stream_s* %19, i32 14), !dbg !562
  %20 = load i32, i32* %flags, align 4, !dbg !563
  %and = and i32 %20, 128, !dbg !565
  %tobool25 = icmp ne i32 %and, 0, !dbg !565
  br i1 %tobool25, label %if.end28, label %if.then26, !dbg !566

if.then26:                                        ; preds = %skip
  %21 = load i32, i32* %fd.addr, align 4, !dbg !567
  %call27 = call i32 @uv__nonblock_ioctl(i32 %21, i32 1), !dbg !568
  br label %if.end28, !dbg !568

if.end28:                                         ; preds = %if.then26, %skip
  %22 = load i32, i32* %readable.addr, align 4, !dbg !569
  %tobool29 = icmp ne i32 %22, 0, !dbg !569
  br i1 %tobool29, label %if.then30, label %if.else32, !dbg !571

if.then30:                                        ; preds = %if.end28
  %23 = load i32, i32* %flags, align 4, !dbg !572
  %or31 = or i32 %23, 32, !dbg !572
  store i32 %or31, i32* %flags, align 4, !dbg !572
  br label %if.end34, !dbg !573

if.else32:                                        ; preds = %if.end28
  %24 = load i32, i32* %flags, align 4, !dbg !574
  %or33 = or i32 %24, 64, !dbg !574
  store i32 %or33, i32* %flags, align 4, !dbg !574
  br label %if.end34

if.end34:                                         ; preds = %if.else32, %if.then30
  %25 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !575
  %26 = bitcast %struct.uv_tty_s* %25 to %struct.uv_stream_s*, !dbg !576
  %27 = load i32, i32* %fd.addr, align 4, !dbg !577
  %28 = load i32, i32* %flags, align 4, !dbg !578
  %call35 = call i32 @uv__stream_open(%struct.uv_stream_s* %26, i32 %27, i32 %28), !dbg !579
  %29 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !580
  %mode = getelementptr inbounds %struct.uv_tty_s, %struct.uv_tty_s* %29, i32 0, i32 21, !dbg !581
  store i32 0, i32* %mode, align 4, !dbg !582
  store i32 0, i32* %retval, align 4, !dbg !583
  br label %return, !dbg !583

return:                                           ; preds = %if.end34, %if.then21, %if.then
  %30 = load i32, i32* %retval, align 4, !dbg !584
  ret i32 %30, !dbg !584
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @uv_guess_handle(i32 %file) #0 !dbg !429 {
entry:
  %retval = alloca i32, align 4
  %file.addr = alloca i32, align 4
  %sa = alloca %struct.sockaddr, align 2
  %s = alloca %struct.stat, align 8
  %len = alloca i32, align 4
  %type = alloca i32, align 4
  %agg.tmp = alloca %union.__SOCKADDR_ARG, align 8
  store i32 %file, i32* %file.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %file.addr, metadata !585, metadata !470), !dbg !586
  call void @llvm.dbg.declare(metadata %struct.sockaddr* %sa, metadata !587, metadata !470), !dbg !599
  call void @llvm.dbg.declare(metadata %struct.stat* %s, metadata !600, metadata !470), !dbg !638
  call void @llvm.dbg.declare(metadata i32* %len, metadata !639, metadata !470), !dbg !642
  call void @llvm.dbg.declare(metadata i32* %type, metadata !643, metadata !470), !dbg !644
  %0 = load i32, i32* %file.addr, align 4, !dbg !645
  %cmp = icmp slt i32 %0, 0, !dbg !647
  br i1 %cmp, label %if.then, label %if.end, !dbg !648

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !649
  br label %return, !dbg !649

if.end:                                           ; preds = %entry
  %1 = load i32, i32* %file.addr, align 4, !dbg !650
  %call = call i32 @isatty(i32 %1) #7, !dbg !652
  %tobool = icmp ne i32 %call, 0, !dbg !652
  br i1 %tobool, label %if.then1, label %if.end2, !dbg !653

if.then1:                                         ; preds = %if.end
  store i32 14, i32* %retval, align 4, !dbg !654
  br label %return, !dbg !654

if.end2:                                          ; preds = %if.end
  %2 = load i32, i32* %file.addr, align 4, !dbg !655
  %call3 = call i32 @fstat64(i32 %2, %struct.stat* %s) #7, !dbg !657
  %tobool4 = icmp ne i32 %call3, 0, !dbg !657
  br i1 %tobool4, label %if.then5, label %if.end6, !dbg !658

if.then5:                                         ; preds = %if.end2
  store i32 0, i32* %retval, align 4, !dbg !659
  br label %return, !dbg !659

if.end6:                                          ; preds = %if.end2
  %st_mode = getelementptr inbounds %struct.stat, %struct.stat* %s, i32 0, i32 3, !dbg !660
  %3 = load i32, i32* %st_mode, align 8, !dbg !660
  %and = and i32 %3, 61440, !dbg !660
  %cmp7 = icmp eq i32 %and, 32768, !dbg !660
  br i1 %cmp7, label %if.then8, label %if.end9, !dbg !662

if.then8:                                         ; preds = %if.end6
  store i32 17, i32* %retval, align 4, !dbg !663
  br label %return, !dbg !663

if.end9:                                          ; preds = %if.end6
  %st_mode10 = getelementptr inbounds %struct.stat, %struct.stat* %s, i32 0, i32 3, !dbg !664
  %4 = load i32, i32* %st_mode10, align 8, !dbg !664
  %and11 = and i32 %4, 61440, !dbg !664
  %cmp12 = icmp eq i32 %and11, 8192, !dbg !664
  br i1 %cmp12, label %if.then13, label %if.end14, !dbg !666

if.then13:                                        ; preds = %if.end9
  store i32 17, i32* %retval, align 4, !dbg !667
  br label %return, !dbg !667

if.end14:                                         ; preds = %if.end9
  %st_mode15 = getelementptr inbounds %struct.stat, %struct.stat* %s, i32 0, i32 3, !dbg !668
  %5 = load i32, i32* %st_mode15, align 8, !dbg !668
  %and16 = and i32 %5, 61440, !dbg !668
  %cmp17 = icmp eq i32 %and16, 4096, !dbg !668
  br i1 %cmp17, label %if.then18, label %if.end19, !dbg !670

if.then18:                                        ; preds = %if.end14
  store i32 7, i32* %retval, align 4, !dbg !671
  br label %return, !dbg !671

if.end19:                                         ; preds = %if.end14
  %st_mode20 = getelementptr inbounds %struct.stat, %struct.stat* %s, i32 0, i32 3, !dbg !672
  %6 = load i32, i32* %st_mode20, align 8, !dbg !672
  %and21 = and i32 %6, 61440, !dbg !672
  %cmp22 = icmp eq i32 %and21, 49152, !dbg !672
  br i1 %cmp22, label %if.end24, label %if.then23, !dbg !674

if.then23:                                        ; preds = %if.end19
  store i32 0, i32* %retval, align 4, !dbg !675
  br label %return, !dbg !675

if.end24:                                         ; preds = %if.end19
  store i32 4, i32* %len, align 4, !dbg !676
  %7 = load i32, i32* %file.addr, align 4, !dbg !677
  %8 = bitcast i32* %type to i8*, !dbg !679
  %call25 = call i32 @getsockopt(i32 %7, i32 1, i32 3, i8* %8, i32* %len) #7, !dbg !680
  %tobool26 = icmp ne i32 %call25, 0, !dbg !680
  br i1 %tobool26, label %if.then27, label %if.end28, !dbg !681

if.then27:                                        ; preds = %if.end24
  store i32 0, i32* %retval, align 4, !dbg !682
  br label %return, !dbg !682

if.end28:                                         ; preds = %if.end24
  store i32 16, i32* %len, align 4, !dbg !683
  %9 = load i32, i32* %file.addr, align 4, !dbg !684
  %__sockaddr__ = bitcast %union.__SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !686
  store %struct.sockaddr* %sa, %struct.sockaddr** %__sockaddr__, align 8, !dbg !686
  %coerce.dive = getelementptr inbounds %union.__SOCKADDR_ARG, %union.__SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !687
  %10 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !687
  %call29 = call i32 @getsockname(i32 %9, %struct.sockaddr* %10, i32* %len) #7, !dbg !687
  %tobool30 = icmp ne i32 %call29, 0, !dbg !687
  br i1 %tobool30, label %if.then31, label %if.end32, !dbg !688

if.then31:                                        ; preds = %if.end28
  store i32 0, i32* %retval, align 4, !dbg !689
  br label %return, !dbg !689

if.end32:                                         ; preds = %if.end28
  %11 = load i32, i32* %type, align 4, !dbg !690
  %cmp33 = icmp eq i32 %11, 2, !dbg !692
  br i1 %cmp33, label %if.then34, label %if.end43, !dbg !693

if.then34:                                        ; preds = %if.end32
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %sa, i32 0, i32 0, !dbg !694
  %12 = load i16, i16* %sa_family, align 2, !dbg !694
  %conv = zext i16 %12 to i32, !dbg !696
  %cmp35 = icmp eq i32 %conv, 2, !dbg !697
  br i1 %cmp35, label %if.then41, label %lor.lhs.false, !dbg !698

lor.lhs.false:                                    ; preds = %if.then34
  %sa_family37 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %sa, i32 0, i32 0, !dbg !699
  %13 = load i16, i16* %sa_family37, align 2, !dbg !699
  %conv38 = zext i16 %13 to i32, !dbg !701
  %cmp39 = icmp eq i32 %conv38, 10, !dbg !702
  br i1 %cmp39, label %if.then41, label %if.end42, !dbg !703

if.then41:                                        ; preds = %lor.lhs.false, %if.then34
  store i32 15, i32* %retval, align 4, !dbg !704
  br label %return, !dbg !704

if.end42:                                         ; preds = %lor.lhs.false
  br label %if.end43, !dbg !705

if.end43:                                         ; preds = %if.end42, %if.end32
  %14 = load i32, i32* %type, align 4, !dbg !707
  %cmp44 = icmp eq i32 %14, 1, !dbg !709
  br i1 %cmp44, label %if.then46, label %if.end64, !dbg !710

if.then46:                                        ; preds = %if.end43
  %sa_family47 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %sa, i32 0, i32 0, !dbg !711
  %15 = load i16, i16* %sa_family47, align 2, !dbg !711
  %conv48 = zext i16 %15 to i32, !dbg !714
  %cmp49 = icmp eq i32 %conv48, 2, !dbg !715
  br i1 %cmp49, label %if.then56, label %lor.lhs.false51, !dbg !716

lor.lhs.false51:                                  ; preds = %if.then46
  %sa_family52 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %sa, i32 0, i32 0, !dbg !717
  %16 = load i16, i16* %sa_family52, align 2, !dbg !717
  %conv53 = zext i16 %16 to i32, !dbg !719
  %cmp54 = icmp eq i32 %conv53, 10, !dbg !720
  br i1 %cmp54, label %if.then56, label %if.end57, !dbg !721

if.then56:                                        ; preds = %lor.lhs.false51, %if.then46
  store i32 12, i32* %retval, align 4, !dbg !722
  br label %return, !dbg !722

if.end57:                                         ; preds = %lor.lhs.false51
  %sa_family58 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %sa, i32 0, i32 0, !dbg !723
  %17 = load i16, i16* %sa_family58, align 2, !dbg !723
  %conv59 = zext i16 %17 to i32, !dbg !725
  %cmp60 = icmp eq i32 %conv59, 1, !dbg !726
  br i1 %cmp60, label %if.then62, label %if.end63, !dbg !727

if.then62:                                        ; preds = %if.end57
  store i32 7, i32* %retval, align 4, !dbg !728
  br label %return, !dbg !728

if.end63:                                         ; preds = %if.end57
  br label %if.end64, !dbg !729

if.end64:                                         ; preds = %if.end63, %if.end43
  store i32 0, i32* %retval, align 4, !dbg !730
  br label %return, !dbg !730

return:                                           ; preds = %if.end64, %if.then62, %if.then56, %if.then41, %if.then31, %if.then27, %if.then23, %if.then18, %if.then13, %if.then8, %if.then5, %if.then1, %if.then
  %18 = load i32, i32* %retval, align 4, !dbg !731
  ret i32 %18, !dbg !731
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__tty_is_slave(i32 %fd) #0 !dbg !436 {
entry:
  %fd.addr = alloca i32, align 4
  %result = alloca i32, align 4
  %dummy = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !732, metadata !470), !dbg !733
  call void @llvm.dbg.declare(metadata i32* %result, metadata !734, metadata !470), !dbg !735
  call void @llvm.dbg.declare(metadata i32* %dummy, metadata !736, metadata !470), !dbg !737
  %0 = load i32, i32* %fd.addr, align 4, !dbg !738
  %call = call i32 (i32, i64, ...) @ioctl(i32 %0, i64 2147767344, i32* %dummy) #7, !dbg !739
  %cmp = icmp ne i32 %call, 0, !dbg !740
  %conv = zext i1 %cmp to i32, !dbg !740
  store i32 %conv, i32* %result, align 4, !dbg !741
  %1 = load i32, i32* %result, align 4, !dbg !742
  ret i32 %1, !dbg !743
}

; Function Attrs: nounwind
declare i32 @ttyname_r(i32, i8*, i64) #2

declare i32 @uv__open_cloexec(i8*, i32) #3

declare i32 @uv__dup2_cloexec(i32, i32) #3

declare i32 @uv__close(i32) #3

declare void @uv__stream_init(%struct.uv_loop_s*, %struct.uv_stream_s*, i32) #3

declare i32 @uv__nonblock_ioctl(i32, i32) #3

declare i32 @uv__stream_open(%struct.uv_stream_s*, i32, i32) #3

; Function Attrs: nounwind uwtable
define i32 @uv_tty_set_mode(%struct.uv_tty_s* %tty, i32 %mode) #0 !dbg !421 {
entry:
  %retval = alloca i32, align 4
  %tty.addr = alloca %struct.uv_tty_s*, align 8
  %mode.addr = alloca i32, align 4
  %tmp = alloca %struct.termios, align 4
  %fd = alloca i32, align 4
  store %struct.uv_tty_s* %tty, %struct.uv_tty_s** %tty.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tty_s** %tty.addr, metadata !744, metadata !470), !dbg !745
  store i32 %mode, i32* %mode.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %mode.addr, metadata !746, metadata !470), !dbg !747
  call void @llvm.dbg.declare(metadata %struct.termios* %tmp, metadata !748, metadata !470), !dbg !749
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !750, metadata !470), !dbg !751
  %0 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !752
  %mode2 = getelementptr inbounds %struct.uv_tty_s, %struct.uv_tty_s* %0, i32 0, i32 21, !dbg !754
  %1 = load i32, i32* %mode2, align 4, !dbg !754
  %2 = load i32, i32* %mode.addr, align 4, !dbg !755
  %cmp = icmp eq i32 %1, %2, !dbg !756
  br i1 %cmp, label %if.then, label %if.end, !dbg !757

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !758
  br label %return, !dbg !758

if.end:                                           ; preds = %entry
  %3 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !759
  %io_watcher = getelementptr inbounds %struct.uv_tty_s, %struct.uv_tty_s* %3, i32 0, i32 13, !dbg !759
  %fd3 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !759
  %4 = load i32, i32* %fd3, align 8, !dbg !759
  store i32 %4, i32* %fd, align 4, !dbg !760
  %5 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !761
  %mode4 = getelementptr inbounds %struct.uv_tty_s, %struct.uv_tty_s* %5, i32 0, i32 21, !dbg !763
  %6 = load i32, i32* %mode4, align 4, !dbg !763
  %cmp5 = icmp eq i32 %6, 0, !dbg !764
  br i1 %cmp5, label %land.lhs.true, label %if.end15, !dbg !765

land.lhs.true:                                    ; preds = %if.end
  %7 = load i32, i32* %mode.addr, align 4, !dbg !766
  %cmp6 = icmp ne i32 %7, 0, !dbg !768
  br i1 %cmp6, label %if.then7, label %if.end15, !dbg !769

if.then7:                                         ; preds = %land.lhs.true
  %8 = load i32, i32* %fd, align 4, !dbg !770
  %9 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !773
  %orig_termios = getelementptr inbounds %struct.uv_tty_s, %struct.uv_tty_s* %9, i32 0, i32 20, !dbg !774
  %call = call i32 @tcgetattr(i32 %8, %struct.termios* %orig_termios) #7, !dbg !775
  %tobool = icmp ne i32 %call, 0, !dbg !775
  br i1 %tobool, label %if.then8, label %if.end10, !dbg !776

if.then8:                                         ; preds = %if.then7
  %call9 = call i32* @__errno_location() #1, !dbg !777
  %10 = load i32, i32* %call9, align 4, !dbg !777
  %sub = sub nsw i32 0, %10, !dbg !778
  store i32 %sub, i32* %retval, align 4, !dbg !779
  br label %return, !dbg !779

if.end10:                                         ; preds = %if.then7
  call void @uv_spinlock_lock(%struct.uv_spinlock_t* @termios_spinlock), !dbg !780
  %11 = load i32, i32* @orig_termios_fd, align 4, !dbg !781
  %cmp11 = icmp eq i32 %11, -1, !dbg !783
  br i1 %cmp11, label %if.then12, label %if.end14, !dbg !784

if.then12:                                        ; preds = %if.end10
  %12 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !785
  %orig_termios13 = getelementptr inbounds %struct.uv_tty_s, %struct.uv_tty_s* %12, i32 0, i32 20, !dbg !787
  %13 = bitcast %struct.termios* %orig_termios13 to i8*, !dbg !787
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* bitcast (%struct.termios* @orig_termios to i8*), i8* %13, i64 60, i32 4, i1 false), !dbg !787
  %14 = load i32, i32* %fd, align 4, !dbg !788
  store i32 %14, i32* @orig_termios_fd, align 4, !dbg !789
  br label %if.end14, !dbg !790

if.end14:                                         ; preds = %if.then12, %if.end10
  call void @uv_spinlock_unlock(%struct.uv_spinlock_t* @termios_spinlock), !dbg !791
  br label %if.end15, !dbg !792

if.end15:                                         ; preds = %if.end14, %land.lhs.true, %if.end
  %15 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !793
  %orig_termios16 = getelementptr inbounds %struct.uv_tty_s, %struct.uv_tty_s* %15, i32 0, i32 20, !dbg !794
  %16 = bitcast %struct.termios* %tmp to i8*, !dbg !794
  %17 = bitcast %struct.termios* %orig_termios16 to i8*, !dbg !794
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %16, i8* %17, i64 60, i32 4, i1 false), !dbg !794
  %18 = load i32, i32* %mode.addr, align 4, !dbg !795
  switch i32 %18, label %sw.epilog [
    i32 0, label %sw.bb
    i32 1, label %sw.bb17
    i32 2, label %sw.bb22
  ], !dbg !796

sw.bb:                                            ; preds = %if.end15
  br label %sw.epilog, !dbg !797

sw.bb17:                                          ; preds = %if.end15
  %c_iflag = getelementptr inbounds %struct.termios, %struct.termios* %tmp, i32 0, i32 0, !dbg !799
  %19 = load i32, i32* %c_iflag, align 4, !dbg !800
  %and = and i32 %19, -1331, !dbg !800
  store i32 %and, i32* %c_iflag, align 4, !dbg !800
  %c_oflag = getelementptr inbounds %struct.termios, %struct.termios* %tmp, i32 0, i32 1, !dbg !801
  %20 = load i32, i32* %c_oflag, align 4, !dbg !802
  %or = or i32 %20, 4, !dbg !802
  store i32 %or, i32* %c_oflag, align 4, !dbg !802
  %c_cflag = getelementptr inbounds %struct.termios, %struct.termios* %tmp, i32 0, i32 2, !dbg !803
  %21 = load i32, i32* %c_cflag, align 4, !dbg !804
  %or18 = or i32 %21, 48, !dbg !804
  store i32 %or18, i32* %c_cflag, align 4, !dbg !804
  %c_lflag = getelementptr inbounds %struct.termios, %struct.termios* %tmp, i32 0, i32 3, !dbg !805
  %22 = load i32, i32* %c_lflag, align 4, !dbg !806
  %and19 = and i32 %22, -32780, !dbg !806
  store i32 %and19, i32* %c_lflag, align 4, !dbg !806
  %c_cc = getelementptr inbounds %struct.termios, %struct.termios* %tmp, i32 0, i32 5, !dbg !807
  %arrayidx = getelementptr inbounds [32 x i8], [32 x i8]* %c_cc, i64 0, i64 6, !dbg !808
  store i8 1, i8* %arrayidx, align 1, !dbg !809
  %c_cc20 = getelementptr inbounds %struct.termios, %struct.termios* %tmp, i32 0, i32 5, !dbg !810
  %arrayidx21 = getelementptr inbounds [32 x i8], [32 x i8]* %c_cc20, i64 0, i64 5, !dbg !811
  store i8 0, i8* %arrayidx21, align 1, !dbg !812
  br label %sw.epilog, !dbg !813

sw.bb22:                                          ; preds = %if.end15
  call void @uv__tty_make_raw(%struct.termios* %tmp), !dbg !814
  br label %sw.epilog, !dbg !815

sw.epilog:                                        ; preds = %if.end15, %sw.bb22, %sw.bb17, %sw.bb
  %23 = load i32, i32* %fd, align 4, !dbg !816
  %call23 = call i32 @tcsetattr(i32 %23, i32 1, %struct.termios* %tmp) #7, !dbg !818
  %tobool24 = icmp ne i32 %call23, 0, !dbg !818
  br i1 %tobool24, label %if.then25, label %if.end28, !dbg !819

if.then25:                                        ; preds = %sw.epilog
  %call26 = call i32* @__errno_location() #1, !dbg !820
  %24 = load i32, i32* %call26, align 4, !dbg !820
  %sub27 = sub nsw i32 0, %24, !dbg !821
  store i32 %sub27, i32* %retval, align 4, !dbg !822
  br label %return, !dbg !822

if.end28:                                         ; preds = %sw.epilog
  %25 = load i32, i32* %mode.addr, align 4, !dbg !823
  %26 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !824
  %mode29 = getelementptr inbounds %struct.uv_tty_s, %struct.uv_tty_s* %26, i32 0, i32 21, !dbg !825
  store i32 %25, i32* %mode29, align 4, !dbg !826
  store i32 0, i32* %retval, align 4, !dbg !827
  br label %return, !dbg !827

return:                                           ; preds = %if.end28, %if.then25, %if.then8, %if.then
  %27 = load i32, i32* %retval, align 4, !dbg !828
  ret i32 %27, !dbg !828
}

; Function Attrs: nounwind
declare i32 @tcgetattr(i32, %struct.termios*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

; Function Attrs: nounwind uwtable
define internal void @uv_spinlock_lock(%struct.uv_spinlock_t* %spinlock) #0 !dbg !440 {
entry:
  %spinlock.addr = alloca %struct.uv_spinlock_t*, align 8
  store %struct.uv_spinlock_t* %spinlock, %struct.uv_spinlock_t** %spinlock.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_spinlock_t** %spinlock.addr, metadata !829, metadata !470), !dbg !830
  br label %while.cond, !dbg !831

while.cond:                                       ; preds = %while.body, %entry
  %0 = load %struct.uv_spinlock_t*, %struct.uv_spinlock_t** %spinlock.addr, align 8, !dbg !832
  %call = call i32 @uv_spinlock_trylock(%struct.uv_spinlock_t* %0), !dbg !834
  %tobool = icmp ne i32 %call, 0, !dbg !835
  %lnot = xor i1 %tobool, true, !dbg !835
  br i1 %lnot, label %while.body, label %while.end, !dbg !836

while.body:                                       ; preds = %while.cond
  call void @cpu_relax(), !dbg !837
  br label %while.cond, !dbg !839

while.end:                                        ; preds = %while.cond
  ret void, !dbg !840
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: nounwind uwtable
define internal void @uv_spinlock_unlock(%struct.uv_spinlock_t* %spinlock) #0 !dbg !451 {
entry:
  %spinlock.addr = alloca %struct.uv_spinlock_t*, align 8
  store %struct.uv_spinlock_t* %spinlock, %struct.uv_spinlock_t** %spinlock.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_spinlock_t** %spinlock.addr, metadata !841, metadata !470), !dbg !842
  %0 = load %struct.uv_spinlock_t*, %struct.uv_spinlock_t** %spinlock.addr, align 8, !dbg !843
  %lock = getelementptr inbounds %struct.uv_spinlock_t, %struct.uv_spinlock_t* %0, i32 0, i32 0, !dbg !843
  store volatile i32 0, i32* %lock, align 4, !dbg !844
  ret void, !dbg !845
}

; Function Attrs: nounwind uwtable
define internal void @uv__tty_make_raw(%struct.termios* %tio) #0 !dbg !452 {
entry:
  %tio.addr = alloca %struct.termios*, align 8
  store %struct.termios* %tio, %struct.termios** %tio.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.termios** %tio.addr, metadata !846, metadata !470), !dbg !847
  %0 = load %struct.termios*, %struct.termios** %tio.addr, align 8, !dbg !848
  %cmp = icmp ne %struct.termios* %0, null, !dbg !848
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !848

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !849

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 170, i8* getelementptr inbounds ([40 x i8], [40 x i8]* @__PRETTY_FUNCTION__.uv__tty_make_raw, i32 0, i32 0)) #8, !dbg !851
  unreachable, !dbg !851
                                                  ; No predecessors!
  br label %cond.end, !dbg !853

cond.end:                                         ; preds = %1, %cond.true
  %2 = load %struct.termios*, %struct.termios** %tio.addr, align 8, !dbg !855
  call void @cfmakeraw(%struct.termios* %2) #7, !dbg !856
  ret void, !dbg !857
}

; Function Attrs: nounwind
declare i32 @tcsetattr(i32, i32, %struct.termios*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_tty_get_winsize(%struct.uv_tty_s* %tty, i32* %width, i32* %height) #0 !dbg !425 {
entry:
  %retval = alloca i32, align 4
  %tty.addr = alloca %struct.uv_tty_s*, align 8
  %width.addr = alloca i32*, align 8
  %height.addr = alloca i32*, align 8
  %ws = alloca %struct.winsize, align 2
  %err = alloca i32, align 4
  store %struct.uv_tty_s* %tty, %struct.uv_tty_s** %tty.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tty_s** %tty.addr, metadata !858, metadata !470), !dbg !859
  store i32* %width, i32** %width.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %width.addr, metadata !860, metadata !470), !dbg !861
  store i32* %height, i32** %height.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %height.addr, metadata !862, metadata !470), !dbg !863
  call void @llvm.dbg.declare(metadata %struct.winsize* %ws, metadata !864, metadata !470), !dbg !872
  call void @llvm.dbg.declare(metadata i32* %err, metadata !873, metadata !470), !dbg !874
  br label %do.body, !dbg !875

do.body:                                          ; preds = %land.end, %entry
  %0 = load %struct.uv_tty_s*, %struct.uv_tty_s** %tty.addr, align 8, !dbg !876
  %io_watcher = getelementptr inbounds %struct.uv_tty_s, %struct.uv_tty_s* %0, i32 0, i32 13, !dbg !876
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !876
  %1 = load i32, i32* %fd, align 8, !dbg !876
  %call = call i32 (i32, i64, ...) @ioctl(i32 %1, i64 21523, %struct.winsize* %ws) #7, !dbg !877
  store i32 %call, i32* %err, align 4, !dbg !878
  br label %do.cond, !dbg !879

do.cond:                                          ; preds = %do.body
  %2 = load i32, i32* %err, align 4, !dbg !880
  %cmp = icmp eq i32 %2, -1, !dbg !881
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !882

land.rhs:                                         ; preds = %do.cond
  %call1 = call i32* @__errno_location() #1, !dbg !883
  %3 = load i32, i32* %call1, align 4, !dbg !883
  %cmp2 = icmp eq i32 %3, 4, !dbg !885
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %4 = phi i1 [ false, %do.cond ], [ %cmp2, %land.rhs ]
  br i1 %4, label %do.body, label %do.end, !dbg !886

do.end:                                           ; preds = %land.end
  %5 = load i32, i32* %err, align 4, !dbg !887
  %cmp3 = icmp eq i32 %5, -1, !dbg !889
  br i1 %cmp3, label %if.then, label %if.end, !dbg !890

if.then:                                          ; preds = %do.end
  %call4 = call i32* @__errno_location() #1, !dbg !891
  %6 = load i32, i32* %call4, align 4, !dbg !891
  %sub = sub nsw i32 0, %6, !dbg !892
  store i32 %sub, i32* %retval, align 4, !dbg !893
  br label %return, !dbg !893

if.end:                                           ; preds = %do.end
  %ws_col = getelementptr inbounds %struct.winsize, %struct.winsize* %ws, i32 0, i32 1, !dbg !894
  %7 = load i16, i16* %ws_col, align 2, !dbg !894
  %conv = zext i16 %7 to i32, !dbg !895
  %8 = load i32*, i32** %width.addr, align 8, !dbg !896
  store i32 %conv, i32* %8, align 4, !dbg !897
  %ws_row = getelementptr inbounds %struct.winsize, %struct.winsize* %ws, i32 0, i32 0, !dbg !898
  %9 = load i16, i16* %ws_row, align 2, !dbg !898
  %conv5 = zext i16 %9 to i32, !dbg !899
  %10 = load i32*, i32** %height.addr, align 8, !dbg !900
  store i32 %conv5, i32* %10, align 4, !dbg !901
  store i32 0, i32* %retval, align 4, !dbg !902
  br label %return, !dbg !902

return:                                           ; preds = %if.end, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !903
  ret i32 %11, !dbg !903
}

; Function Attrs: nounwind
declare i32 @ioctl(i32, i64, ...) #2

; Function Attrs: nounwind
declare i32 @isatty(i32) #2

; Function Attrs: nounwind
declare i32 @fstat64(i32, %struct.stat*) #2

; Function Attrs: nounwind
declare i32 @getsockopt(i32, i32, i32, i8*, i32*) #2

; Function Attrs: nounwind
declare i32 @getsockname(i32, %struct.sockaddr*, i32*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_tty_reset_mode() #0 !dbg !433 {
entry:
  %retval = alloca i32, align 4
  %saved_errno = alloca i32, align 4
  %err = alloca i32, align 4
  call void @llvm.dbg.declare(metadata i32* %saved_errno, metadata !904, metadata !470), !dbg !905
  call void @llvm.dbg.declare(metadata i32* %err, metadata !906, metadata !470), !dbg !907
  %call = call i32* @__errno_location() #1, !dbg !908
  %0 = load i32, i32* %call, align 4, !dbg !908
  store i32 %0, i32* %saved_errno, align 4, !dbg !909
  %call1 = call i32 @uv_spinlock_trylock(%struct.uv_spinlock_t* @termios_spinlock), !dbg !910
  %tobool = icmp ne i32 %call1, 0, !dbg !910
  br i1 %tobool, label %if.end, label %if.then, !dbg !912

if.then:                                          ; preds = %entry
  store i32 -16, i32* %retval, align 4, !dbg !913
  br label %return, !dbg !913

if.end:                                           ; preds = %entry
  store i32 0, i32* %err, align 4, !dbg !914
  %1 = load i32, i32* @orig_termios_fd, align 4, !dbg !915
  %cmp = icmp ne i32 %1, -1, !dbg !917
  br i1 %cmp, label %if.then2, label %if.end8, !dbg !918

if.then2:                                         ; preds = %if.end
  %2 = load i32, i32* @orig_termios_fd, align 4, !dbg !919
  %call3 = call i32 @tcsetattr(i32 %2, i32 0, %struct.termios* @orig_termios) #7, !dbg !921
  %tobool4 = icmp ne i32 %call3, 0, !dbg !921
  br i1 %tobool4, label %if.then5, label %if.end7, !dbg !922

if.then5:                                         ; preds = %if.then2
  %call6 = call i32* @__errno_location() #1, !dbg !923
  %3 = load i32, i32* %call6, align 4, !dbg !923
  %sub = sub nsw i32 0, %3, !dbg !924
  store i32 %sub, i32* %err, align 4, !dbg !925
  br label %if.end7, !dbg !926

if.end7:                                          ; preds = %if.then5, %if.then2
  br label %if.end8, !dbg !927

if.end8:                                          ; preds = %if.end7, %if.end
  call void @uv_spinlock_unlock(%struct.uv_spinlock_t* @termios_spinlock), !dbg !929
  %4 = load i32, i32* %saved_errno, align 4, !dbg !930
  %call9 = call i32* @__errno_location() #1, !dbg !931
  store i32 %4, i32* %call9, align 4, !dbg !932
  %5 = load i32, i32* %err, align 4, !dbg !933
  store i32 %5, i32* %retval, align 4, !dbg !934
  br label %return, !dbg !934

return:                                           ; preds = %if.end8, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !935
  ret i32 %6, !dbg !935
}

; Function Attrs: nounwind uwtable
define internal i32 @uv_spinlock_trylock(%struct.uv_spinlock_t* %spinlock) #0 !dbg !456 {
entry:
  %spinlock.addr = alloca %struct.uv_spinlock_t*, align 8
  store %struct.uv_spinlock_t* %spinlock, %struct.uv_spinlock_t** %spinlock.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_spinlock_t** %spinlock.addr, metadata !936, metadata !470), !dbg !937
  %0 = load %struct.uv_spinlock_t*, %struct.uv_spinlock_t** %spinlock.addr, align 8, !dbg !938
  %lock = getelementptr inbounds %struct.uv_spinlock_t, %struct.uv_spinlock_t* %0, i32 0, i32 0, !dbg !939
  %call = call i32 @cmpxchgi(i32* %lock, i32 0, i32 1), !dbg !940
  %cmp = icmp eq i32 0, %call, !dbg !941
  %conv = zext i1 %cmp to i32, !dbg !941
  ret i32 %conv, !dbg !942
}

; Function Attrs: nounwind uwtable
define internal void @cpu_relax() #0 !dbg !449 {
entry:
  call void asm sideeffect "rep; nop", "~{dirflag},~{fpsr},~{flags}"() #7, !dbg !943, !srcloc !944
  ret void, !dbg !945
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #6

; Function Attrs: nounwind
declare void @cfmakeraw(%struct.termios*) #2

; Function Attrs: nounwind uwtable
define internal i32 @cmpxchgi(i32* %ptr, i32 %oldval, i32 %newval) #0 !dbg !459 {
entry:
  %ptr.addr = alloca i32*, align 8
  %oldval.addr = alloca i32, align 4
  %newval.addr = alloca i32, align 4
  %out = alloca i32, align 4
  store i32* %ptr, i32** %ptr.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %ptr.addr, metadata !946, metadata !470), !dbg !947
  store i32 %oldval, i32* %oldval.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %oldval.addr, metadata !948, metadata !470), !dbg !947
  store i32 %newval, i32* %newval.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %newval.addr, metadata !949, metadata !470), !dbg !947
  call void @llvm.dbg.declare(metadata i32* %out, metadata !950, metadata !470), !dbg !951
  %0 = load i32*, i32** %ptr.addr, align 8, !dbg !952
  %1 = load i32, i32* %newval.addr, align 4, !dbg !953
  %2 = load i32, i32* %oldval.addr, align 4, !dbg !954
  %3 = call i32 asm sideeffect "lock; cmpxchg $2, $1;", "={ax},=*m,r,0,*m,~{memory},~{dirflag},~{fpsr},~{flags}"(i32* %0, i32 %1, i32 %2, i32* %0) #7, !dbg !955, !srcloc !956
  store i32 %3, i32* %out, align 4, !dbg !955
  %4 = load i32, i32* %out, align 4, !dbg !957
  ret i32 %4, !dbg !958
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { noreturn nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!466, !467}
!llvm.ident = !{!468}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !74, subprograms: !368, globals: !462)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/tty.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !38, !57, !62}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 184, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14, !15, !16, !17, !18, !19, !20, !21, !22, !23, !24}
!6 = !DIEnumerator(name: "UV_UNKNOWN_HANDLE", value: 0)
!7 = !DIEnumerator(name: "UV_ASYNC", value: 1)
!8 = !DIEnumerator(name: "UV_CHECK", value: 2)
!9 = !DIEnumerator(name: "UV_FS_EVENT", value: 3)
!10 = !DIEnumerator(name: "UV_FS_POLL", value: 4)
!11 = !DIEnumerator(name: "UV_HANDLE", value: 5)
!12 = !DIEnumerator(name: "UV_IDLE", value: 6)
!13 = !DIEnumerator(name: "UV_NAMED_PIPE", value: 7)
!14 = !DIEnumerator(name: "UV_POLL", value: 8)
!15 = !DIEnumerator(name: "UV_PREPARE", value: 9)
!16 = !DIEnumerator(name: "UV_PROCESS", value: 10)
!17 = !DIEnumerator(name: "UV_STREAM", value: 11)
!18 = !DIEnumerator(name: "UV_TCP", value: 12)
!19 = !DIEnumerator(name: "UV_TIMER", value: 13)
!20 = !DIEnumerator(name: "UV_TTY", value: 14)
!21 = !DIEnumerator(name: "UV_UDP", value: 15)
!22 = !DIEnumerator(name: "UV_SIGNAL", value: 16)
!23 = !DIEnumerator(name: "UV_FILE", value: 17)
!24 = !DIEnumerator(name: "UV_HANDLE_TYPE_MAX", value: 18)
!25 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 193, size: 32, align: 32, elements: !26)
!26 = !{!27, !28, !29, !30, !31, !32, !33, !34, !35, !36, !37}
!27 = !DIEnumerator(name: "UV_UNKNOWN_REQ", value: 0)
!28 = !DIEnumerator(name: "UV_REQ", value: 1)
!29 = !DIEnumerator(name: "UV_CONNECT", value: 2)
!30 = !DIEnumerator(name: "UV_WRITE", value: 3)
!31 = !DIEnumerator(name: "UV_SHUTDOWN", value: 4)
!32 = !DIEnumerator(name: "UV_UDP_SEND", value: 5)
!33 = !DIEnumerator(name: "UV_FS", value: 6)
!34 = !DIEnumerator(name: "UV_WORK", value: 7)
!35 = !DIEnumerator(name: "UV_GETADDRINFO", value: 8)
!36 = !DIEnumerator(name: "UV_GETNAMEINFO", value: 9)
!37 = !DIEnumerator(name: "UV_REQ_TYPE_MAX", value: 10)
!38 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !39, line: 124, size: 32, align: 32, elements: !40)
!39 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!40 = !{!41, !42, !43, !44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56}
!41 = !DIEnumerator(name: "UV_CLOSING", value: 1)
!42 = !DIEnumerator(name: "UV_CLOSED", value: 2)
!43 = !DIEnumerator(name: "UV_STREAM_READING", value: 4)
!44 = !DIEnumerator(name: "UV_STREAM_SHUTTING", value: 8)
!45 = !DIEnumerator(name: "UV_STREAM_SHUT", value: 16)
!46 = !DIEnumerator(name: "UV_STREAM_READABLE", value: 32)
!47 = !DIEnumerator(name: "UV_STREAM_WRITABLE", value: 64)
!48 = !DIEnumerator(name: "UV_STREAM_BLOCKING", value: 128)
!49 = !DIEnumerator(name: "UV_STREAM_READ_PARTIAL", value: 256)
!50 = !DIEnumerator(name: "UV_STREAM_READ_EOF", value: 512)
!51 = !DIEnumerator(name: "UV_TCP_NODELAY", value: 1024)
!52 = !DIEnumerator(name: "UV_TCP_KEEPALIVE", value: 2048)
!53 = !DIEnumerator(name: "UV_TCP_SINGLE_ACCEPT", value: 4096)
!54 = !DIEnumerator(name: "UV_HANDLE_IPV6", value: 65536)
!55 = !DIEnumerator(name: "UV_UDP_PROCESSING", value: 131072)
!56 = !DIEnumerator(name: "UV_HANDLE_BOUND", value: 262144)
!57 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 660, size: 32, align: 32, elements: !58)
!58 = !{!59, !60, !61}
!59 = !DIEnumerator(name: "UV_TTY_MODE_NORMAL", value: 0)
!60 = !DIEnumerator(name: "UV_TTY_MODE_RAW", value: 1)
!61 = !DIEnumerator(name: "UV_TTY_MODE_IO", value: 2)
!62 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !63, line: 24, size: 32, align: 32, elements: !64)
!63 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!64 = !{!65, !66, !67, !68, !69, !70, !71, !72, !73}
!65 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!66 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!67 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!68 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!69 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!70 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!71 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!72 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!73 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!74 = !{!75, !98, !366, !80}
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!76 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stream_t", file: !4, line: 206, baseType: !77)
!77 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_stream_s", file: !4, line: 465, size: 1984, align: 64, elements: !78)
!78 = !{!79, !81, !287, !288, !289, !290, !295, !296, !297, !300, !312, !323, !340, !355, !356, !357, !358, !363, !364, !365}
!79 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !77, file: !4, line: 466, baseType: !80, size: 64, align: 64)
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !77, file: !4, line: 466, baseType: !82, size: 64, align: 64, offset: 64)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !84)
!84 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !85)
!85 = !{!86, !87, !89, !93, !94, !95, !97, !99, !100, !101, !120, !121, !122, !123, !154, !202, !226, !227, !228, !229, !230, !231, !232, !236, !237, !238, !243, !246, !247, !249, !250, !283, !284, !285, !286}
!86 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !84, file: !4, line: 1475, baseType: !80, size: 64, align: 64)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !84, file: !4, line: 1477, baseType: !88, size: 32, align: 32, offset: 64)
!88 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !84, file: !4, line: 1478, baseType: !90, size: 128, align: 64, offset: 128)
!90 = !DICompositeType(tag: DW_TAG_array_type, baseType: !80, size: 128, align: 64, elements: !91)
!91 = !{!92}
!92 = !DISubrange(count: 2)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !84, file: !4, line: 1479, baseType: !90, size: 128, align: 64, offset: 256)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !84, file: !4, line: 1481, baseType: !88, size: 32, align: 32, offset: 384)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !84, file: !4, line: 1482, baseType: !96, size: 64, align: 64, offset: 448)
!96 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !84, file: !4, line: 1482, baseType: !98, size: 32, align: 32, offset: 512)
!98 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !84, file: !4, line: 1482, baseType: !90, size: 128, align: 64, offset: 576)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !84, file: !4, line: 1482, baseType: !90, size: 128, align: 64, offset: 704)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !84, file: !4, line: 1482, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !104, size: 64, align: 64)
!104 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !105, line: 87, baseType: !106)
!105 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!106 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !105, line: 89, size: 448, align: 64, elements: !107)
!107 = !{!108, !115, !116, !117, !118, !119}
!108 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !106, file: !105, line: 90, baseType: !109, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !105, line: 84, baseType: !110)
!110 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !111, size: 64, align: 64)
!111 = !DISubroutineType(types: !112)
!112 = !{null, !113, !114, !88}
!113 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !84, size: 64, align: 64)
!114 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !106, size: 64, align: 64)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !106, file: !105, line: 91, baseType: !90, size: 128, align: 64, offset: 64)
!116 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !106, file: !105, line: 92, baseType: !90, size: 128, align: 64, offset: 192)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !106, file: !105, line: 93, baseType: !88, size: 32, align: 32, offset: 320)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !106, file: !105, line: 94, baseType: !88, size: 32, align: 32, offset: 352)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !106, file: !105, line: 95, baseType: !98, size: 32, align: 32, offset: 384)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !84, file: !4, line: 1482, baseType: !88, size: 32, align: 32, offset: 896)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !84, file: !4, line: 1482, baseType: !88, size: 32, align: 32, offset: 928)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !84, file: !4, line: 1482, baseType: !90, size: 128, align: 64, offset: 960)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !84, file: !4, line: 1482, baseType: !124, size: 320, align: 64, offset: 1088)
!124 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !105, line: 129, baseType: !125)
!125 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !126, line: 127, baseType: !127)
!126 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!127 = !DICompositeType(tag: DW_TAG_union_type, file: !126, line: 90, size: 320, align: 64, elements: !128)
!128 = !{!129, !147, !152}
!129 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !127, file: !126, line: 124, baseType: !130, size: 320, align: 64)
!130 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !126, line: 92, size: 320, align: 64, elements: !131)
!131 = !{!132, !133, !134, !135, !136, !137, !139, !140}
!132 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !130, file: !126, line: 94, baseType: !98, size: 32, align: 32)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !130, file: !126, line: 95, baseType: !88, size: 32, align: 32, offset: 32)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !130, file: !126, line: 96, baseType: !98, size: 32, align: 32, offset: 64)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !130, file: !126, line: 98, baseType: !88, size: 32, align: 32, offset: 96)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !130, file: !126, line: 102, baseType: !98, size: 32, align: 32, offset: 128)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !130, file: !126, line: 104, baseType: !138, size: 16, align: 16, offset: 160)
!138 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !130, file: !126, line: 105, baseType: !138, size: 16, align: 16, offset: 176)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !130, file: !126, line: 106, baseType: !141, size: 128, align: 64, offset: 192)
!141 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !126, line: 79, baseType: !142)
!142 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !126, line: 75, size: 128, align: 64, elements: !143)
!143 = !{!144, !146}
!144 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !142, file: !126, line: 77, baseType: !145, size: 64, align: 64)
!145 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !142, size: 64, align: 64)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !142, file: !126, line: 78, baseType: !145, size: 64, align: 64, offset: 64)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !127, file: !126, line: 125, baseType: !148, size: 320, align: 8)
!148 = !DICompositeType(tag: DW_TAG_array_type, baseType: !149, size: 320, align: 8, elements: !150)
!149 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!150 = !{!151}
!151 = !DISubrange(count: 40)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !127, file: !126, line: 126, baseType: !153, size: 64, align: 64)
!153 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !84, file: !4, line: 1482, baseType: !155, size: 1024, align: 64, offset: 1408)
!155 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !156)
!156 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !157)
!157 = !{!158, !159, !160, !162, !186, !187, !192, !193, !194, !200, !201}
!158 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !156, file: !4, line: 768, baseType: !80, size: 64, align: 64)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !156, file: !4, line: 768, baseType: !82, size: 64, align: 64, offset: 64)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !156, file: !4, line: 768, baseType: !161, size: 32, align: 32, offset: 128)
!161 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !156, file: !4, line: 768, baseType: !163, size: 64, align: 64, offset: 192)
!163 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !164)
!164 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !165, size: 64, align: 64)
!165 = !DISubroutineType(types: !166)
!166 = !{null, !167}
!167 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !168, size: 64, align: 64)
!168 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !169)
!169 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !170)
!170 = !{!171, !172, !173, !174, !175, !176, !184, !185}
!171 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !169, file: !4, line: 426, baseType: !80, size: 64, align: 64)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !169, file: !4, line: 426, baseType: !82, size: 64, align: 64, offset: 64)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !169, file: !4, line: 426, baseType: !161, size: 32, align: 32, offset: 128)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !169, file: !4, line: 426, baseType: !163, size: 64, align: 64, offset: 192)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !169, file: !4, line: 426, baseType: !90, size: 128, align: 64, offset: 256)
!176 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !169, file: !4, line: 426, baseType: !177, size: 256, align: 64, offset: 384)
!177 = !DICompositeType(tag: DW_TAG_union_type, scope: !169, file: !4, line: 426, size: 256, align: 64, elements: !178)
!178 = !{!179, !180}
!179 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !177, file: !4, line: 426, baseType: !98, size: 32, align: 32)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !177, file: !4, line: 426, baseType: !181, size: 256, align: 64)
!181 = !DICompositeType(tag: DW_TAG_array_type, baseType: !80, size: 256, align: 64, elements: !182)
!182 = !{!183}
!183 = !DISubrange(count: 4)
!184 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !169, file: !4, line: 426, baseType: !167, size: 64, align: 64, offset: 640)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !169, file: !4, line: 426, baseType: !88, size: 32, align: 32, offset: 704)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !156, file: !4, line: 768, baseType: !90, size: 128, align: 64, offset: 256)
!187 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !156, file: !4, line: 768, baseType: !188, size: 256, align: 64, offset: 384)
!188 = !DICompositeType(tag: DW_TAG_union_type, scope: !156, file: !4, line: 768, size: 256, align: 64, elements: !189)
!189 = !{!190, !191}
!190 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !188, file: !4, line: 768, baseType: !98, size: 32, align: 32)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !188, file: !4, line: 768, baseType: !181, size: 256, align: 64)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !156, file: !4, line: 768, baseType: !167, size: 64, align: 64, offset: 640)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !156, file: !4, line: 768, baseType: !88, size: 32, align: 32, offset: 704)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !156, file: !4, line: 769, baseType: !195, size: 64, align: 64, offset: 768)
!195 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !196)
!196 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !197, size: 64, align: 64)
!197 = !DISubroutineType(types: !198)
!198 = !{null, !199}
!199 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !155, size: 64, align: 64)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !156, file: !4, line: 769, baseType: !90, size: 128, align: 64, offset: 832)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !156, file: !4, line: 769, baseType: !98, size: 32, align: 32, offset: 960)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !84, file: !4, line: 1482, baseType: !203, size: 448, align: 64, offset: 2432)
!203 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !105, line: 130, baseType: !204)
!204 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !126, line: 213, baseType: !205)
!205 = !DICompositeType(tag: DW_TAG_union_type, file: !126, line: 173, size: 448, align: 64, elements: !206)
!206 = !{!207, !221, !225}
!207 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !205, file: !126, line: 192, baseType: !208, size: 448, align: 64)
!208 = !DICompositeType(tag: DW_TAG_structure_type, scope: !205, file: !126, line: 176, size: 448, align: 64, elements: !209)
!209 = !{!210, !211, !212, !213, !214, !215, !216, !217, !218, !219, !220}
!210 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !208, file: !126, line: 178, baseType: !98, size: 32, align: 32)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !208, file: !126, line: 179, baseType: !88, size: 32, align: 32, offset: 32)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !208, file: !126, line: 180, baseType: !88, size: 32, align: 32, offset: 64)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !208, file: !126, line: 181, baseType: !88, size: 32, align: 32, offset: 96)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !208, file: !126, line: 182, baseType: !88, size: 32, align: 32, offset: 128)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !208, file: !126, line: 183, baseType: !88, size: 32, align: 32, offset: 160)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !208, file: !126, line: 184, baseType: !98, size: 32, align: 32, offset: 192)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !208, file: !126, line: 185, baseType: !98, size: 32, align: 32, offset: 224)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !208, file: !126, line: 186, baseType: !96, size: 64, align: 64, offset: 256)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !208, file: !126, line: 187, baseType: !96, size: 64, align: 64, offset: 320)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !208, file: !126, line: 190, baseType: !88, size: 32, align: 32, offset: 384)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !205, file: !126, line: 211, baseType: !222, size: 448, align: 8)
!222 = !DICompositeType(tag: DW_TAG_array_type, baseType: !149, size: 448, align: 8, elements: !223)
!223 = !{!224}
!224 = !DISubrange(count: 56)
!225 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !205, file: !126, line: 212, baseType: !153, size: 64, align: 64)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !84, file: !4, line: 1482, baseType: !167, size: 64, align: 64, offset: 2880)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !84, file: !4, line: 1482, baseType: !90, size: 128, align: 64, offset: 2944)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !84, file: !4, line: 1482, baseType: !90, size: 128, align: 64, offset: 3072)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !84, file: !4, line: 1482, baseType: !90, size: 128, align: 64, offset: 3200)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !84, file: !4, line: 1482, baseType: !90, size: 128, align: 64, offset: 3328)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !84, file: !4, line: 1482, baseType: !90, size: 128, align: 64, offset: 3456)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !84, file: !4, line: 1482, baseType: !233, size: 64, align: 64, offset: 3584)
!233 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !234, size: 64, align: 64)
!234 = !DISubroutineType(types: !235)
!235 = !{null}
!236 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !84, file: !4, line: 1482, baseType: !104, size: 448, align: 64, offset: 3648)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !84, file: !4, line: 1482, baseType: !98, size: 32, align: 32, offset: 4096)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !84, file: !4, line: 1482, baseType: !239, size: 128, align: 64, offset: 4160)
!239 = !DICompositeType(tag: DW_TAG_structure_type, scope: !84, file: !4, line: 1482, size: 128, align: 64, elements: !240)
!240 = !{!241, !242}
!241 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !239, file: !4, line: 1482, baseType: !80, size: 64, align: 64)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !239, file: !4, line: 1482, baseType: !88, size: 32, align: 32, offset: 64)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !84, file: !4, line: 1482, baseType: !244, size: 64, align: 64, offset: 4288)
!244 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !245, line: 55, baseType: !96)
!245 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!246 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !84, file: !4, line: 1482, baseType: !244, size: 64, align: 64, offset: 4352)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !84, file: !4, line: 1482, baseType: !248, size: 64, align: 32, offset: 4416)
!248 = !DICompositeType(tag: DW_TAG_array_type, baseType: !98, size: 64, align: 32, elements: !91)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !84, file: !4, line: 1482, baseType: !104, size: 448, align: 64, offset: 4480)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !84, file: !4, line: 1482, baseType: !251, size: 1216, align: 64, offset: 4928)
!251 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !252)
!252 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !253)
!253 = !{!254, !255, !256, !257, !258, !259, !264, !265, !266, !272, !273, !281, !282}
!254 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !252, file: !4, line: 1326, baseType: !80, size: 64, align: 64)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !252, file: !4, line: 1326, baseType: !82, size: 64, align: 64, offset: 64)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !252, file: !4, line: 1326, baseType: !161, size: 32, align: 32, offset: 128)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !252, file: !4, line: 1326, baseType: !163, size: 64, align: 64, offset: 192)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !252, file: !4, line: 1326, baseType: !90, size: 128, align: 64, offset: 256)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !252, file: !4, line: 1326, baseType: !260, size: 256, align: 64, offset: 384)
!260 = !DICompositeType(tag: DW_TAG_union_type, scope: !252, file: !4, line: 1326, size: 256, align: 64, elements: !261)
!261 = !{!262, !263}
!262 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !260, file: !4, line: 1326, baseType: !98, size: 32, align: 32)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !260, file: !4, line: 1326, baseType: !181, size: 256, align: 64)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !252, file: !4, line: 1326, baseType: !167, size: 64, align: 64, offset: 640)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !252, file: !4, line: 1326, baseType: !88, size: 32, align: 32, offset: 704)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !252, file: !4, line: 1327, baseType: !267, size: 64, align: 64, offset: 768)
!267 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !268)
!268 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !269, size: 64, align: 64)
!269 = !DISubroutineType(types: !270)
!270 = !{null, !271, !98}
!271 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !251, size: 64, align: 64)
!272 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !252, file: !4, line: 1328, baseType: !98, size: 32, align: 32, offset: 832)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !252, file: !4, line: 1329, baseType: !274, size: 256, align: 64, offset: 896)
!274 = !DICompositeType(tag: DW_TAG_structure_type, scope: !252, file: !4, line: 1329, size: 256, align: 64, elements: !275)
!275 = !{!276, !278, !279, !280}
!276 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !274, file: !4, line: 1329, baseType: !277, size: 64, align: 64)
!277 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !252, size: 64, align: 64)
!278 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !274, file: !4, line: 1329, baseType: !277, size: 64, align: 64, offset: 64)
!279 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !274, file: !4, line: 1329, baseType: !277, size: 64, align: 64, offset: 128)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !274, file: !4, line: 1329, baseType: !98, size: 32, align: 32, offset: 192)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !252, file: !4, line: 1329, baseType: !88, size: 32, align: 32, offset: 1152)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !252, file: !4, line: 1329, baseType: !88, size: 32, align: 32, offset: 1184)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !84, file: !4, line: 1482, baseType: !98, size: 32, align: 32, offset: 6144)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !84, file: !4, line: 1482, baseType: !104, size: 448, align: 64, offset: 6208)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !84, file: !4, line: 1482, baseType: !80, size: 64, align: 64, offset: 6656)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !84, file: !4, line: 1482, baseType: !98, size: 32, align: 32, offset: 6720)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !77, file: !4, line: 466, baseType: !161, size: 32, align: 32, offset: 128)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !77, file: !4, line: 466, baseType: !163, size: 64, align: 64, offset: 192)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !77, file: !4, line: 466, baseType: !90, size: 128, align: 64, offset: 256)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !77, file: !4, line: 466, baseType: !291, size: 256, align: 64, offset: 384)
!291 = !DICompositeType(tag: DW_TAG_union_type, scope: !77, file: !4, line: 466, size: 256, align: 64, elements: !292)
!292 = !{!293, !294}
!293 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !291, file: !4, line: 466, baseType: !98, size: 32, align: 32)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !291, file: !4, line: 466, baseType: !181, size: 256, align: 64)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !77, file: !4, line: 466, baseType: !167, size: 64, align: 64, offset: 640)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !77, file: !4, line: 466, baseType: !88, size: 32, align: 32, offset: 704)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !77, file: !4, line: 467, baseType: !298, size: 64, align: 64, offset: 768)
!298 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !299, line: 62, baseType: !96)
!299 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!300 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !77, file: !4, line: 467, baseType: !301, size: 64, align: 64, offset: 832)
!301 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_alloc_cb", file: !4, line: 296, baseType: !302)
!302 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !303, size: 64, align: 64)
!303 = !DISubroutineType(types: !304)
!304 = !{null, !167, !298, !305}
!305 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !306, size: 64, align: 64)
!306 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !105, line: 119, baseType: !307)
!307 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !105, line: 116, size: 128, align: 64, elements: !308)
!308 = !{!309, !311}
!309 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !307, file: !105, line: 117, baseType: !310, size: 64, align: 64)
!310 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !149, size: 64, align: 64)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !307, file: !105, line: 118, baseType: !298, size: 64, align: 64, offset: 64)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !77, file: !4, line: 467, baseType: !313, size: 64, align: 64, offset: 896)
!313 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_read_cb", file: !4, line: 299, baseType: !314)
!314 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !315, size: 64, align: 64)
!315 = !DISubroutineType(types: !316)
!316 = !{null, !75, !317, !321}
!317 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !318, line: 102, baseType: !319)
!318 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!319 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !320, line: 172, baseType: !153)
!320 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!321 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !322, size: 64, align: 64)
!322 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !306)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !77, file: !4, line: 467, baseType: !324, size: 64, align: 64, offset: 960)
!324 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !325, size: 64, align: 64)
!325 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_t", file: !4, line: 228, baseType: !326)
!326 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_connect_s", file: !4, line: 551, size: 768, align: 64, elements: !327)
!327 = !{!328, !329, !331, !332, !333, !338, !339}
!328 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !326, file: !4, line: 552, baseType: !80, size: 64, align: 64)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !326, file: !4, line: 552, baseType: !330, size: 32, align: 32, offset: 64)
!330 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !25)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !326, file: !4, line: 552, baseType: !90, size: 128, align: 64, offset: 128)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !326, file: !4, line: 552, baseType: !181, size: 256, align: 64, offset: 256)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !326, file: !4, line: 553, baseType: !334, size: 64, align: 64, offset: 512)
!334 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_cb", file: !4, line: 303, baseType: !335)
!335 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !336, size: 64, align: 64)
!336 = !DISubroutineType(types: !337)
!337 = !{null, !324, !98}
!338 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !326, file: !4, line: 554, baseType: !75, size: 64, align: 64, offset: 576)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !326, file: !4, line: 555, baseType: !90, size: 128, align: 64, offset: 640)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !77, file: !4, line: 467, baseType: !341, size: 64, align: 64, offset: 1024)
!341 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !342, size: 64, align: 64)
!342 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_t", file: !4, line: 226, baseType: !343)
!343 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_shutdown_s", file: !4, line: 401, size: 640, align: 64, elements: !344)
!344 = !{!345, !346, !347, !348, !349, !350}
!345 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !343, file: !4, line: 402, baseType: !80, size: 64, align: 64)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !343, file: !4, line: 402, baseType: !330, size: 32, align: 32, offset: 64)
!347 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !343, file: !4, line: 402, baseType: !90, size: 128, align: 64, offset: 128)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !343, file: !4, line: 402, baseType: !181, size: 256, align: 64, offset: 256)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !343, file: !4, line: 403, baseType: !75, size: 64, align: 64, offset: 512)
!350 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !343, file: !4, line: 404, baseType: !351, size: 64, align: 64, offset: 576)
!351 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_cb", file: !4, line: 304, baseType: !352)
!352 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !353, size: 64, align: 64)
!353 = !DISubroutineType(types: !354)
!354 = !{null, !341, !98}
!355 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !77, file: !4, line: 467, baseType: !104, size: 448, align: 64, offset: 1088)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !77, file: !4, line: 467, baseType: !90, size: 128, align: 64, offset: 1536)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !77, file: !4, line: 467, baseType: !90, size: 128, align: 64, offset: 1664)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !77, file: !4, line: 467, baseType: !359, size: 64, align: 64, offset: 1792)
!359 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connection_cb", file: !4, line: 305, baseType: !360)
!360 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !361, size: 64, align: 64)
!361 = !DISubroutineType(types: !362)
!362 = !{null, !75, !98}
!363 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !77, file: !4, line: 467, baseType: !98, size: 32, align: 32, offset: 1856)
!364 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !77, file: !4, line: 467, baseType: !98, size: 32, align: 32, offset: 1888)
!365 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !77, file: !4, line: 467, baseType: !80, size: 64, align: 64, offset: 1920)
!366 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !367, size: 64, align: 64)
!367 = !DIDerivedType(tag: DW_TAG_volatile_type, baseType: !98)
!368 = !{!369, !421, !425, !429, !433, !436, !440, !449, !451, !452, !456, !459}
!369 = distinct !DISubprogram(name: "uv_tty_init", scope: !1, file: !1, line: 59, type: !370, isLocal: false, isDefinition: true, scopeLine: 59, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!370 = !DISubroutineType(types: !371)
!371 = !{!98, !82, !372, !98, !98}
!372 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !373, size: 64, align: 64)
!373 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_tty_t", file: !4, line: 210, baseType: !374)
!374 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_tty_s", file: !4, line: 654, size: 2496, align: 64, elements: !375)
!375 = !{!376, !377, !378, !379, !380, !381, !386, !387, !388, !389, !390, !391, !392, !393, !394, !395, !396, !397, !398, !399, !400, !419}
!376 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !374, file: !4, line: 655, baseType: !80, size: 64, align: 64)
!377 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !374, file: !4, line: 655, baseType: !82, size: 64, align: 64, offset: 64)
!378 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !374, file: !4, line: 655, baseType: !161, size: 32, align: 32, offset: 128)
!379 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !374, file: !4, line: 655, baseType: !163, size: 64, align: 64, offset: 192)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !374, file: !4, line: 655, baseType: !90, size: 128, align: 64, offset: 256)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !374, file: !4, line: 655, baseType: !382, size: 256, align: 64, offset: 384)
!382 = !DICompositeType(tag: DW_TAG_union_type, scope: !374, file: !4, line: 655, size: 256, align: 64, elements: !383)
!383 = !{!384, !385}
!384 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !382, file: !4, line: 655, baseType: !98, size: 32, align: 32)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !382, file: !4, line: 655, baseType: !181, size: 256, align: 64)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !374, file: !4, line: 655, baseType: !167, size: 64, align: 64, offset: 640)
!387 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !374, file: !4, line: 655, baseType: !88, size: 32, align: 32, offset: 704)
!388 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !374, file: !4, line: 656, baseType: !298, size: 64, align: 64, offset: 768)
!389 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !374, file: !4, line: 656, baseType: !301, size: 64, align: 64, offset: 832)
!390 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !374, file: !4, line: 656, baseType: !313, size: 64, align: 64, offset: 896)
!391 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !374, file: !4, line: 656, baseType: !324, size: 64, align: 64, offset: 960)
!392 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !374, file: !4, line: 656, baseType: !341, size: 64, align: 64, offset: 1024)
!393 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !374, file: !4, line: 656, baseType: !104, size: 448, align: 64, offset: 1088)
!394 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !374, file: !4, line: 656, baseType: !90, size: 128, align: 64, offset: 1536)
!395 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !374, file: !4, line: 656, baseType: !90, size: 128, align: 64, offset: 1664)
!396 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !374, file: !4, line: 656, baseType: !359, size: 64, align: 64, offset: 1792)
!397 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !374, file: !4, line: 656, baseType: !98, size: 32, align: 32, offset: 1856)
!398 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !374, file: !4, line: 656, baseType: !98, size: 32, align: 32, offset: 1888)
!399 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !374, file: !4, line: 656, baseType: !80, size: 64, align: 64, offset: 1920)
!400 = !DIDerivedType(tag: DW_TAG_member, name: "orig_termios", scope: !374, file: !4, line: 657, baseType: !401, size: 480, align: 32, offset: 1984)
!401 = !DICompositeType(tag: DW_TAG_structure_type, name: "termios", file: !402, line: 28, size: 480, align: 32, elements: !403)
!402 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/termios.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!403 = !{!404, !406, !407, !408, !409, !412, !416, !418}
!404 = !DIDerivedType(tag: DW_TAG_member, name: "c_iflag", scope: !401, file: !402, line: 30, baseType: !405, size: 32, align: 32)
!405 = !DIDerivedType(tag: DW_TAG_typedef, name: "tcflag_t", file: !402, line: 25, baseType: !88)
!406 = !DIDerivedType(tag: DW_TAG_member, name: "c_oflag", scope: !401, file: !402, line: 31, baseType: !405, size: 32, align: 32, offset: 32)
!407 = !DIDerivedType(tag: DW_TAG_member, name: "c_cflag", scope: !401, file: !402, line: 32, baseType: !405, size: 32, align: 32, offset: 64)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "c_lflag", scope: !401, file: !402, line: 33, baseType: !405, size: 32, align: 32, offset: 96)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "c_line", scope: !401, file: !402, line: 34, baseType: !410, size: 8, align: 8, offset: 128)
!410 = !DIDerivedType(tag: DW_TAG_typedef, name: "cc_t", file: !402, line: 23, baseType: !411)
!411 = !DIBasicType(name: "unsigned char", size: 8, align: 8, encoding: DW_ATE_unsigned_char)
!412 = !DIDerivedType(tag: DW_TAG_member, name: "c_cc", scope: !401, file: !402, line: 35, baseType: !413, size: 256, align: 8, offset: 136)
!413 = !DICompositeType(tag: DW_TAG_array_type, baseType: !410, size: 256, align: 8, elements: !414)
!414 = !{!415}
!415 = !DISubrange(count: 32)
!416 = !DIDerivedType(tag: DW_TAG_member, name: "c_ispeed", scope: !401, file: !402, line: 36, baseType: !417, size: 32, align: 32, offset: 416)
!417 = !DIDerivedType(tag: DW_TAG_typedef, name: "speed_t", file: !402, line: 24, baseType: !88)
!418 = !DIDerivedType(tag: DW_TAG_member, name: "c_ospeed", scope: !401, file: !402, line: 37, baseType: !417, size: 32, align: 32, offset: 448)
!419 = !DIDerivedType(tag: DW_TAG_member, name: "mode", scope: !374, file: !4, line: 657, baseType: !98, size: 32, align: 32, offset: 2464)
!420 = !{}
!421 = distinct !DISubprogram(name: "uv_tty_set_mode", scope: !1, file: !1, line: 188, type: !422, isLocal: false, isDefinition: true, scopeLine: 188, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!422 = !DISubroutineType(types: !423)
!423 = !{!98, !372, !424}
!424 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_tty_mode_t", file: !4, line: 667, baseType: !57)
!425 = distinct !DISubprogram(name: "uv_tty_get_winsize", scope: !1, file: !1, line: 235, type: !426, isLocal: false, isDefinition: true, scopeLine: 235, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!426 = !DISubroutineType(types: !427)
!427 = !{!98, !372, !428, !428}
!428 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !98, size: 64, align: 64)
!429 = distinct !DISubprogram(name: "uv_guess_handle", scope: !1, file: !1, line: 253, type: !430, isLocal: false, isDefinition: true, scopeLine: 253, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!430 = !DISubroutineType(types: !431)
!431 = !{!161, !432}
!432 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_file", file: !105, line: 121, baseType: !98)
!433 = distinct !DISubprogram(name: "uv_tty_reset_mode", scope: !1, file: !1, line: 316, type: !434, isLocal: false, isDefinition: true, scopeLine: 316, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!434 = !DISubroutineType(types: !435)
!435 = !{!98}
!436 = distinct !DISubprogram(name: "uv__tty_is_slave", scope: !1, file: !1, line: 41, type: !437, isLocal: true, isDefinition: true, scopeLine: 41, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!437 = !DISubroutineType(types: !438)
!438 = !{!98, !439}
!439 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !98)
!440 = distinct !DISubprogram(name: "uv_spinlock_lock", scope: !441, file: !441, line: 37, type: !442, isLocal: true, isDefinition: true, scopeLine: 37, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!441 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/spinlock.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!442 = !DISubroutineType(types: !443)
!443 = !{null, !444}
!444 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !445, size: 64, align: 64)
!445 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_spinlock_t", file: !441, line: 26, baseType: !446)
!446 = !DICompositeType(tag: DW_TAG_structure_type, file: !441, line: 24, size: 32, align: 32, elements: !447)
!447 = !{!448}
!448 = !DIDerivedType(tag: DW_TAG_member, name: "lock", scope: !446, file: !441, line: 25, baseType: !98, size: 32, align: 32)
!449 = distinct !DISubprogram(name: "cpu_relax", scope: !450, file: !450, line: 91, type: !234, isLocal: true, isDefinition: true, scopeLine: 91, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!450 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/atomic-ops.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!451 = distinct !DISubprogram(name: "uv_spinlock_unlock", scope: !441, file: !441, line: 41, type: !442, isLocal: true, isDefinition: true, scopeLine: 41, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!452 = distinct !DISubprogram(name: "uv__tty_make_raw", scope: !1, file: !1, line: 169, type: !453, isLocal: true, isDefinition: true, scopeLine: 169, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!453 = !DISubroutineType(types: !454)
!454 = !{null, !455}
!455 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !401, size: 64, align: 64)
!456 = distinct !DISubprogram(name: "uv_spinlock_trylock", scope: !441, file: !441, line: 45, type: !457, isLocal: true, isDefinition: true, scopeLine: 45, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!457 = !DISubroutineType(types: !458)
!458 = !{!98, !444}
!459 = distinct !DISubprogram(name: "cmpxchgi", scope: !450, file: !450, line: 33, type: !460, isLocal: true, isDefinition: true, scopeLine: 33, flags: DIFlagPrototyped, isOptimized: false, variables: !420)
!460 = !DISubroutineType(types: !461)
!461 = !{!98, !428, !98, !98}
!462 = !{!463, !464, !465}
!463 = !DIGlobalVariable(name: "orig_termios", scope: !0, file: !1, line: 38, type: !401, isLocal: true, isDefinition: true, variable: %struct.termios* @orig_termios)
!464 = !DIGlobalVariable(name: "termios_spinlock", scope: !0, file: !1, line: 39, type: !445, isLocal: true, isDefinition: true, variable: %struct.uv_spinlock_t* @termios_spinlock)
!465 = !DIGlobalVariable(name: "orig_termios_fd", scope: !0, file: !1, line: 37, type: !98, isLocal: true, isDefinition: true, variable: i32* @orig_termios_fd)
!466 = !{i32 2, !"Dwarf Version", i32 4}
!467 = !{i32 2, !"Debug Info Version", i32 3}
!468 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!469 = !DILocalVariable(name: "loop", arg: 1, scope: !369, file: !1, line: 59, type: !82)
!470 = !DIExpression()
!471 = !DILocation(line: 59, column: 28, scope: !369)
!472 = !DILocalVariable(name: "tty", arg: 2, scope: !369, file: !1, line: 59, type: !372)
!473 = !DILocation(line: 59, column: 44, scope: !369)
!474 = !DILocalVariable(name: "fd", arg: 3, scope: !369, file: !1, line: 59, type: !98)
!475 = !DILocation(line: 59, column: 53, scope: !369)
!476 = !DILocalVariable(name: "readable", arg: 4, scope: !369, file: !1, line: 59, type: !98)
!477 = !DILocation(line: 59, column: 61, scope: !369)
!478 = !DILocalVariable(name: "type", scope: !369, file: !1, line: 60, type: !161)
!479 = !DILocation(line: 60, column: 18, scope: !369)
!480 = !DILocalVariable(name: "flags", scope: !369, file: !1, line: 61, type: !98)
!481 = !DILocation(line: 61, column: 7, scope: !369)
!482 = !DILocalVariable(name: "newfd", scope: !369, file: !1, line: 62, type: !98)
!483 = !DILocation(line: 62, column: 7, scope: !369)
!484 = !DILocalVariable(name: "r", scope: !369, file: !1, line: 63, type: !98)
!485 = !DILocation(line: 63, column: 7, scope: !369)
!486 = !DILocalVariable(name: "saved_flags", scope: !369, file: !1, line: 64, type: !98)
!487 = !DILocation(line: 64, column: 7, scope: !369)
!488 = !DILocalVariable(name: "path", scope: !369, file: !1, line: 65, type: !489)
!489 = !DICompositeType(tag: DW_TAG_array_type, baseType: !149, size: 2048, align: 8, elements: !490)
!490 = !{!491}
!491 = !DISubrange(count: 256)
!492 = !DILocation(line: 65, column: 8, scope: !369)
!493 = !DILocation(line: 71, column: 26, scope: !369)
!494 = !DILocation(line: 71, column: 10, scope: !369)
!495 = !DILocation(line: 71, column: 8, scope: !369)
!496 = !DILocation(line: 72, column: 7, scope: !497)
!497 = distinct !DILexicalBlock(scope: !369, file: !1, line: 72, column: 7)
!498 = !DILocation(line: 72, column: 12, scope: !497)
!499 = !DILocation(line: 72, column: 23, scope: !497)
!500 = !DILocation(line: 72, column: 26, scope: !501)
!501 = !DILexicalBlockFile(scope: !497, file: !1, discriminator: 1)
!502 = !DILocation(line: 72, column: 31, scope: !501)
!503 = !DILocation(line: 72, column: 7, scope: !501)
!504 = !DILocation(line: 73, column: 5, scope: !497)
!505 = !DILocation(line: 85, column: 7, scope: !506)
!506 = distinct !DILexicalBlock(scope: !369, file: !1, line: 85, column: 7)
!507 = !DILocation(line: 85, column: 12, scope: !506)
!508 = !DILocation(line: 85, column: 7, scope: !369)
!509 = !DILocation(line: 91, column: 26, scope: !510)
!510 = distinct !DILexicalBlock(scope: !511, file: !1, line: 91, column: 9)
!511 = distinct !DILexicalBlock(scope: !506, file: !1, line: 85, column: 23)
!512 = !DILocation(line: 91, column: 9, scope: !510)
!513 = !DILocation(line: 91, column: 30, scope: !510)
!514 = !DILocation(line: 91, column: 43, scope: !515)
!515 = !DILexicalBlockFile(scope: !510, file: !1, discriminator: 1)
!516 = !DILocation(line: 91, column: 47, scope: !515)
!517 = !DILocation(line: 91, column: 33, scope: !515)
!518 = !DILocation(line: 91, column: 67, scope: !515)
!519 = !DILocation(line: 91, column: 9, scope: !515)
!520 = !DILocation(line: 92, column: 28, scope: !510)
!521 = !DILocation(line: 92, column: 11, scope: !510)
!522 = !DILocation(line: 92, column: 9, scope: !510)
!523 = !DILocation(line: 92, column: 7, scope: !510)
!524 = !DILocation(line: 94, column: 9, scope: !510)
!525 = !DILocation(line: 96, column: 9, scope: !526)
!526 = distinct !DILexicalBlock(scope: !511, file: !1, line: 96, column: 9)
!527 = !DILocation(line: 96, column: 11, scope: !526)
!528 = !DILocation(line: 96, column: 9, scope: !511)
!529 = !DILocation(line: 98, column: 12, scope: !530)
!530 = distinct !DILexicalBlock(scope: !531, file: !1, line: 98, column: 11)
!531 = distinct !DILexicalBlock(scope: !526, file: !1, line: 96, column: 16)
!532 = !DILocation(line: 98, column: 11, scope: !531)
!533 = !DILocation(line: 99, column: 15, scope: !530)
!534 = !DILocation(line: 99, column: 9, scope: !530)
!535 = !DILocation(line: 100, column: 7, scope: !531)
!536 = !DILocation(line: 103, column: 13, scope: !511)
!537 = !DILocation(line: 103, column: 11, scope: !511)
!538 = !DILocation(line: 105, column: 26, scope: !511)
!539 = !DILocation(line: 105, column: 33, scope: !511)
!540 = !DILocation(line: 105, column: 9, scope: !511)
!541 = !DILocation(line: 105, column: 7, scope: !511)
!542 = !DILocation(line: 106, column: 9, scope: !543)
!543 = distinct !DILexicalBlock(scope: !511, file: !1, line: 106, column: 9)
!544 = !DILocation(line: 106, column: 11, scope: !543)
!545 = !DILocation(line: 106, column: 15, scope: !543)
!546 = !DILocation(line: 106, column: 18, scope: !547)
!547 = !DILexicalBlockFile(scope: !543, file: !1, discriminator: 1)
!548 = !DILocation(line: 106, column: 20, scope: !547)
!549 = !DILocation(line: 106, column: 9, scope: !547)
!550 = !DILocation(line: 111, column: 17, scope: !551)
!551 = distinct !DILexicalBlock(scope: !543, file: !1, line: 106, column: 32)
!552 = !DILocation(line: 111, column: 7, scope: !551)
!553 = !DILocation(line: 112, column: 14, scope: !551)
!554 = !DILocation(line: 112, column: 7, scope: !551)
!555 = !DILocation(line: 115, column: 10, scope: !511)
!556 = !DILocation(line: 115, column: 8, scope: !511)
!557 = !DILocation(line: 116, column: 3, scope: !511)
!558 = !DILocation(line: 132, column: 3, scope: !369)
!559 = !DILocation(line: 135, column: 19, scope: !369)
!560 = !DILocation(line: 135, column: 40, scope: !369)
!561 = !DILocation(line: 135, column: 25, scope: !369)
!562 = !DILocation(line: 135, column: 3, scope: !369)
!563 = !DILocation(line: 141, column: 9, scope: !564)
!564 = distinct !DILexicalBlock(scope: !369, file: !1, line: 141, column: 7)
!565 = !DILocation(line: 141, column: 15, scope: !564)
!566 = !DILocation(line: 141, column: 7, scope: !369)
!567 = !DILocation(line: 142, column: 18, scope: !564)
!568 = !DILocation(line: 142, column: 5, scope: !564)
!569 = !DILocation(line: 158, column: 7, scope: !570)
!570 = distinct !DILexicalBlock(scope: !369, file: !1, line: 158, column: 7)
!571 = !DILocation(line: 158, column: 7, scope: !369)
!572 = !DILocation(line: 159, column: 11, scope: !570)
!573 = !DILocation(line: 159, column: 5, scope: !570)
!574 = !DILocation(line: 161, column: 11, scope: !570)
!575 = !DILocation(line: 163, column: 34, scope: !369)
!576 = !DILocation(line: 163, column: 19, scope: !369)
!577 = !DILocation(line: 163, column: 39, scope: !369)
!578 = !DILocation(line: 163, column: 43, scope: !369)
!579 = !DILocation(line: 163, column: 3, scope: !369)
!580 = !DILocation(line: 164, column: 3, scope: !369)
!581 = !DILocation(line: 164, column: 8, scope: !369)
!582 = !DILocation(line: 164, column: 13, scope: !369)
!583 = !DILocation(line: 166, column: 3, scope: !369)
!584 = !DILocation(line: 167, column: 1, scope: !369)
!585 = !DILocalVariable(name: "file", arg: 1, scope: !429, file: !1, line: 253, type: !432)
!586 = !DILocation(line: 253, column: 40, scope: !429)
!587 = !DILocalVariable(name: "sa", scope: !429, file: !1, line: 254, type: !588)
!588 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !589, line: 149, size: 128, align: 16, elements: !590)
!589 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!590 = !{!591, !595}
!591 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !588, file: !589, line: 151, baseType: !592, size: 16, align: 16)
!592 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !593, line: 28, baseType: !594)
!593 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!594 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!595 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !588, file: !589, line: 152, baseType: !596, size: 112, align: 8, offset: 16)
!596 = !DICompositeType(tag: DW_TAG_array_type, baseType: !149, size: 112, align: 8, elements: !597)
!597 = !{!598}
!598 = !DISubrange(count: 14)
!599 = !DILocation(line: 254, column: 19, scope: !429)
!600 = !DILocalVariable(name: "s", scope: !429, file: !1, line: 255, type: !601)
!601 = !DICompositeType(tag: DW_TAG_structure_type, name: "stat", file: !602, line: 46, size: 1152, align: 64, elements: !603)
!602 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/stat.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!603 = !{!604, !606, !608, !610, !612, !614, !616, !617, !618, !620, !622, !624, !632, !633, !634}
!604 = !DIDerivedType(tag: DW_TAG_member, name: "st_dev", scope: !601, file: !602, line: 48, baseType: !605, size: 64, align: 64)
!605 = !DIDerivedType(tag: DW_TAG_typedef, name: "__dev_t", file: !320, line: 124, baseType: !96)
!606 = !DIDerivedType(tag: DW_TAG_member, name: "st_ino", scope: !601, file: !602, line: 53, baseType: !607, size: 64, align: 64, offset: 64)
!607 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ino_t", file: !320, line: 127, baseType: !96)
!608 = !DIDerivedType(tag: DW_TAG_member, name: "st_nlink", scope: !601, file: !602, line: 61, baseType: !609, size: 64, align: 64, offset: 128)
!609 = !DIDerivedType(tag: DW_TAG_typedef, name: "__nlink_t", file: !320, line: 130, baseType: !96)
!610 = !DIDerivedType(tag: DW_TAG_member, name: "st_mode", scope: !601, file: !602, line: 62, baseType: !611, size: 32, align: 32, offset: 192)
!611 = !DIDerivedType(tag: DW_TAG_typedef, name: "__mode_t", file: !320, line: 129, baseType: !88)
!612 = !DIDerivedType(tag: DW_TAG_member, name: "st_uid", scope: !601, file: !602, line: 64, baseType: !613, size: 32, align: 32, offset: 224)
!613 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !320, line: 125, baseType: !88)
!614 = !DIDerivedType(tag: DW_TAG_member, name: "st_gid", scope: !601, file: !602, line: 65, baseType: !615, size: 32, align: 32, offset: 256)
!615 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !320, line: 126, baseType: !88)
!616 = !DIDerivedType(tag: DW_TAG_member, name: "__pad0", scope: !601, file: !602, line: 67, baseType: !98, size: 32, align: 32, offset: 288)
!617 = !DIDerivedType(tag: DW_TAG_member, name: "st_rdev", scope: !601, file: !602, line: 69, baseType: !605, size: 64, align: 64, offset: 320)
!618 = !DIDerivedType(tag: DW_TAG_member, name: "st_size", scope: !601, file: !602, line: 74, baseType: !619, size: 64, align: 64, offset: 384)
!619 = !DIDerivedType(tag: DW_TAG_typedef, name: "__off_t", file: !320, line: 131, baseType: !153)
!620 = !DIDerivedType(tag: DW_TAG_member, name: "st_blksize", scope: !601, file: !602, line: 78, baseType: !621, size: 64, align: 64, offset: 448)
!621 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blksize_t", file: !320, line: 153, baseType: !153)
!622 = !DIDerivedType(tag: DW_TAG_member, name: "st_blocks", scope: !601, file: !602, line: 80, baseType: !623, size: 64, align: 64, offset: 512)
!623 = !DIDerivedType(tag: DW_TAG_typedef, name: "__blkcnt_t", file: !320, line: 158, baseType: !153)
!624 = !DIDerivedType(tag: DW_TAG_member, name: "st_atim", scope: !601, file: !602, line: 91, baseType: !625, size: 128, align: 64, offset: 576)
!625 = !DICompositeType(tag: DW_TAG_structure_type, name: "timespec", file: !626, line: 120, size: 128, align: 64, elements: !627)
!626 = !DIFile(filename: "/usr/include/time.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!627 = !{!628, !630}
!628 = !DIDerivedType(tag: DW_TAG_member, name: "tv_sec", scope: !625, file: !626, line: 122, baseType: !629, size: 64, align: 64)
!629 = !DIDerivedType(tag: DW_TAG_typedef, name: "__time_t", file: !320, line: 139, baseType: !153)
!630 = !DIDerivedType(tag: DW_TAG_member, name: "tv_nsec", scope: !625, file: !626, line: 123, baseType: !631, size: 64, align: 64, offset: 64)
!631 = !DIDerivedType(tag: DW_TAG_typedef, name: "__syscall_slong_t", file: !320, line: 175, baseType: !153)
!632 = !DIDerivedType(tag: DW_TAG_member, name: "st_mtim", scope: !601, file: !602, line: 92, baseType: !625, size: 128, align: 64, offset: 704)
!633 = !DIDerivedType(tag: DW_TAG_member, name: "st_ctim", scope: !601, file: !602, line: 93, baseType: !625, size: 128, align: 64, offset: 832)
!634 = !DIDerivedType(tag: DW_TAG_member, name: "__glibc_reserved", scope: !601, file: !602, line: 106, baseType: !635, size: 192, align: 64, offset: 960)
!635 = !DICompositeType(tag: DW_TAG_array_type, baseType: !631, size: 192, align: 64, elements: !636)
!636 = !{!637}
!637 = !DISubrange(count: 3)
!638 = !DILocation(line: 255, column: 15, scope: !429)
!639 = !DILocalVariable(name: "len", scope: !429, file: !1, line: 256, type: !640)
!640 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !589, line: 33, baseType: !641)
!641 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !320, line: 189, baseType: !88)
!642 = !DILocation(line: 256, column: 13, scope: !429)
!643 = !DILocalVariable(name: "type", scope: !429, file: !1, line: 257, type: !98)
!644 = !DILocation(line: 257, column: 7, scope: !429)
!645 = !DILocation(line: 259, column: 7, scope: !646)
!646 = distinct !DILexicalBlock(scope: !429, file: !1, line: 259, column: 7)
!647 = !DILocation(line: 259, column: 12, scope: !646)
!648 = !DILocation(line: 259, column: 7, scope: !429)
!649 = !DILocation(line: 260, column: 5, scope: !646)
!650 = !DILocation(line: 262, column: 14, scope: !651)
!651 = distinct !DILexicalBlock(scope: !429, file: !1, line: 262, column: 7)
!652 = !DILocation(line: 262, column: 7, scope: !651)
!653 = !DILocation(line: 262, column: 7, scope: !429)
!654 = !DILocation(line: 263, column: 5, scope: !651)
!655 = !DILocation(line: 265, column: 13, scope: !656)
!656 = distinct !DILexicalBlock(scope: !429, file: !1, line: 265, column: 7)
!657 = !DILocation(line: 265, column: 7, scope: !656)
!658 = !DILocation(line: 265, column: 7, scope: !429)
!659 = !DILocation(line: 266, column: 5, scope: !656)
!660 = !DILocation(line: 268, column: 7, scope: !661)
!661 = distinct !DILexicalBlock(scope: !429, file: !1, line: 268, column: 7)
!662 = !DILocation(line: 268, column: 7, scope: !429)
!663 = !DILocation(line: 269, column: 5, scope: !661)
!664 = !DILocation(line: 271, column: 7, scope: !665)
!665 = distinct !DILexicalBlock(scope: !429, file: !1, line: 271, column: 7)
!666 = !DILocation(line: 271, column: 7, scope: !429)
!667 = !DILocation(line: 272, column: 5, scope: !665)
!668 = !DILocation(line: 274, column: 7, scope: !669)
!669 = distinct !DILexicalBlock(scope: !429, file: !1, line: 274, column: 7)
!670 = !DILocation(line: 274, column: 7, scope: !429)
!671 = !DILocation(line: 275, column: 5, scope: !669)
!672 = !DILocation(line: 277, column: 8, scope: !673)
!673 = distinct !DILexicalBlock(scope: !429, file: !1, line: 277, column: 7)
!674 = !DILocation(line: 277, column: 7, scope: !429)
!675 = !DILocation(line: 278, column: 5, scope: !673)
!676 = !DILocation(line: 280, column: 7, scope: !429)
!677 = !DILocation(line: 281, column: 18, scope: !678)
!678 = distinct !DILexicalBlock(scope: !429, file: !1, line: 281, column: 7)
!679 = !DILocation(line: 281, column: 45, scope: !678)
!680 = !DILocation(line: 281, column: 7, scope: !678)
!681 = !DILocation(line: 281, column: 7, scope: !429)
!682 = !DILocation(line: 282, column: 5, scope: !678)
!683 = !DILocation(line: 284, column: 7, scope: !429)
!684 = !DILocation(line: 285, column: 19, scope: !685)
!685 = distinct !DILexicalBlock(scope: !429, file: !1, line: 285, column: 7)
!686 = !DILocation(line: 285, column: 25, scope: !685)
!687 = !DILocation(line: 285, column: 7, scope: !685)
!688 = !DILocation(line: 285, column: 7, scope: !429)
!689 = !DILocation(line: 286, column: 5, scope: !685)
!690 = !DILocation(line: 288, column: 7, scope: !691)
!691 = distinct !DILexicalBlock(scope: !429, file: !1, line: 288, column: 7)
!692 = !DILocation(line: 288, column: 12, scope: !691)
!693 = !DILocation(line: 288, column: 7, scope: !429)
!694 = !DILocation(line: 289, column: 12, scope: !695)
!695 = distinct !DILexicalBlock(scope: !691, file: !1, line: 289, column: 9)
!696 = !DILocation(line: 289, column: 9, scope: !695)
!697 = !DILocation(line: 289, column: 22, scope: !695)
!698 = !DILocation(line: 289, column: 33, scope: !695)
!699 = !DILocation(line: 289, column: 39, scope: !700)
!700 = !DILexicalBlockFile(scope: !695, file: !1, discriminator: 1)
!701 = !DILocation(line: 289, column: 36, scope: !700)
!702 = !DILocation(line: 289, column: 49, scope: !700)
!703 = !DILocation(line: 289, column: 9, scope: !700)
!704 = !DILocation(line: 290, column: 7, scope: !695)
!705 = !DILocation(line: 289, column: 52, scope: !706)
!706 = !DILexicalBlockFile(scope: !695, file: !1, discriminator: 2)
!707 = !DILocation(line: 292, column: 7, scope: !708)
!708 = distinct !DILexicalBlock(scope: !429, file: !1, line: 292, column: 7)
!709 = !DILocation(line: 292, column: 12, scope: !708)
!710 = !DILocation(line: 292, column: 7, scope: !429)
!711 = !DILocation(line: 302, column: 12, scope: !712)
!712 = distinct !DILexicalBlock(scope: !713, file: !1, line: 302, column: 9)
!713 = distinct !DILexicalBlock(scope: !708, file: !1, line: 292, column: 28)
!714 = !DILocation(line: 302, column: 9, scope: !712)
!715 = !DILocation(line: 302, column: 22, scope: !712)
!716 = !DILocation(line: 302, column: 33, scope: !712)
!717 = !DILocation(line: 302, column: 39, scope: !718)
!718 = !DILexicalBlockFile(scope: !712, file: !1, discriminator: 1)
!719 = !DILocation(line: 302, column: 36, scope: !718)
!720 = !DILocation(line: 302, column: 49, scope: !718)
!721 = !DILocation(line: 302, column: 9, scope: !718)
!722 = !DILocation(line: 303, column: 7, scope: !712)
!723 = !DILocation(line: 304, column: 12, scope: !724)
!724 = distinct !DILexicalBlock(scope: !713, file: !1, line: 304, column: 9)
!725 = !DILocation(line: 304, column: 9, scope: !724)
!726 = !DILocation(line: 304, column: 22, scope: !724)
!727 = !DILocation(line: 304, column: 9, scope: !713)
!728 = !DILocation(line: 305, column: 7, scope: !724)
!729 = !DILocation(line: 306, column: 3, scope: !713)
!730 = !DILocation(line: 308, column: 3, scope: !429)
!731 = !DILocation(line: 309, column: 1, scope: !429)
!732 = !DILocalVariable(name: "fd", arg: 1, scope: !436, file: !1, line: 41, type: !439)
!733 = !DILocation(line: 41, column: 39, scope: !436)
!734 = !DILocalVariable(name: "result", scope: !436, file: !1, line: 42, type: !98)
!735 = !DILocation(line: 42, column: 7, scope: !436)
!736 = !DILocalVariable(name: "dummy", scope: !436, file: !1, line: 44, type: !98)
!737 = !DILocation(line: 44, column: 7, scope: !436)
!738 = !DILocation(line: 46, column: 18, scope: !436)
!739 = !DILocation(line: 46, column: 12, scope: !436)
!740 = !DILocation(line: 46, column: 40, scope: !436)
!741 = !DILocation(line: 46, column: 10, scope: !436)
!742 = !DILocation(line: 56, column: 10, scope: !436)
!743 = !DILocation(line: 56, column: 3, scope: !436)
!744 = !DILocalVariable(name: "tty", arg: 1, scope: !421, file: !1, line: 188, type: !372)
!745 = !DILocation(line: 188, column: 31, scope: !421)
!746 = !DILocalVariable(name: "mode", arg: 2, scope: !421, file: !1, line: 188, type: !424)
!747 = !DILocation(line: 188, column: 50, scope: !421)
!748 = !DILocalVariable(name: "tmp", scope: !421, file: !1, line: 189, type: !401)
!749 = !DILocation(line: 189, column: 18, scope: !421)
!750 = !DILocalVariable(name: "fd", scope: !421, file: !1, line: 190, type: !98)
!751 = !DILocation(line: 190, column: 7, scope: !421)
!752 = !DILocation(line: 192, column: 7, scope: !753)
!753 = distinct !DILexicalBlock(scope: !421, file: !1, line: 192, column: 7)
!754 = !DILocation(line: 192, column: 12, scope: !753)
!755 = !DILocation(line: 192, column: 26, scope: !753)
!756 = !DILocation(line: 192, column: 17, scope: !753)
!757 = !DILocation(line: 192, column: 7, scope: !421)
!758 = !DILocation(line: 193, column: 5, scope: !753)
!759 = !DILocation(line: 195, column: 8, scope: !421)
!760 = !DILocation(line: 195, column: 6, scope: !421)
!761 = !DILocation(line: 196, column: 7, scope: !762)
!762 = distinct !DILexicalBlock(scope: !421, file: !1, line: 196, column: 7)
!763 = !DILocation(line: 196, column: 12, scope: !762)
!764 = !DILocation(line: 196, column: 17, scope: !762)
!765 = !DILocation(line: 196, column: 39, scope: !762)
!766 = !DILocation(line: 196, column: 42, scope: !767)
!767 = !DILexicalBlockFile(scope: !762, file: !1, discriminator: 1)
!768 = !DILocation(line: 196, column: 47, scope: !767)
!769 = !DILocation(line: 196, column: 7, scope: !767)
!770 = !DILocation(line: 197, column: 19, scope: !771)
!771 = distinct !DILexicalBlock(scope: !772, file: !1, line: 197, column: 9)
!772 = distinct !DILexicalBlock(scope: !762, file: !1, line: 196, column: 70)
!773 = !DILocation(line: 197, column: 24, scope: !771)
!774 = !DILocation(line: 197, column: 29, scope: !771)
!775 = !DILocation(line: 197, column: 9, scope: !771)
!776 = !DILocation(line: 197, column: 9, scope: !772)
!777 = !DILocation(line: 198, column: 15, scope: !771)
!778 = !DILocation(line: 198, column: 14, scope: !771)
!779 = !DILocation(line: 198, column: 7, scope: !771)
!780 = !DILocation(line: 201, column: 5, scope: !772)
!781 = !DILocation(line: 202, column: 9, scope: !782)
!782 = distinct !DILexicalBlock(scope: !772, file: !1, line: 202, column: 9)
!783 = !DILocation(line: 202, column: 25, scope: !782)
!784 = !DILocation(line: 202, column: 9, scope: !772)
!785 = !DILocation(line: 203, column: 22, scope: !786)
!786 = distinct !DILexicalBlock(scope: !782, file: !1, line: 202, column: 32)
!787 = !DILocation(line: 203, column: 27, scope: !786)
!788 = !DILocation(line: 204, column: 25, scope: !786)
!789 = !DILocation(line: 204, column: 23, scope: !786)
!790 = !DILocation(line: 205, column: 5, scope: !786)
!791 = !DILocation(line: 206, column: 5, scope: !772)
!792 = !DILocation(line: 207, column: 3, scope: !772)
!793 = !DILocation(line: 209, column: 9, scope: !421)
!794 = !DILocation(line: 209, column: 14, scope: !421)
!795 = !DILocation(line: 210, column: 11, scope: !421)
!796 = !DILocation(line: 210, column: 3, scope: !421)
!797 = !DILocation(line: 212, column: 7, scope: !798)
!798 = distinct !DILexicalBlock(scope: !421, file: !1, line: 210, column: 17)
!799 = !DILocation(line: 214, column: 11, scope: !798)
!800 = !DILocation(line: 214, column: 19, scope: !798)
!801 = !DILocation(line: 215, column: 11, scope: !798)
!802 = !DILocation(line: 215, column: 19, scope: !798)
!803 = !DILocation(line: 216, column: 11, scope: !798)
!804 = !DILocation(line: 216, column: 19, scope: !798)
!805 = !DILocation(line: 217, column: 11, scope: !798)
!806 = !DILocation(line: 217, column: 19, scope: !798)
!807 = !DILocation(line: 218, column: 11, scope: !798)
!808 = !DILocation(line: 218, column: 7, scope: !798)
!809 = !DILocation(line: 218, column: 22, scope: !798)
!810 = !DILocation(line: 219, column: 11, scope: !798)
!811 = !DILocation(line: 219, column: 7, scope: !798)
!812 = !DILocation(line: 219, column: 23, scope: !798)
!813 = !DILocation(line: 220, column: 7, scope: !798)
!814 = !DILocation(line: 222, column: 7, scope: !798)
!815 = !DILocation(line: 223, column: 7, scope: !798)
!816 = !DILocation(line: 227, column: 17, scope: !817)
!817 = distinct !DILexicalBlock(scope: !421, file: !1, line: 227, column: 7)
!818 = !DILocation(line: 227, column: 7, scope: !817)
!819 = !DILocation(line: 227, column: 7, scope: !421)
!820 = !DILocation(line: 228, column: 13, scope: !817)
!821 = !DILocation(line: 228, column: 12, scope: !817)
!822 = !DILocation(line: 228, column: 5, scope: !817)
!823 = !DILocation(line: 230, column: 15, scope: !421)
!824 = !DILocation(line: 230, column: 3, scope: !421)
!825 = !DILocation(line: 230, column: 8, scope: !421)
!826 = !DILocation(line: 230, column: 13, scope: !421)
!827 = !DILocation(line: 231, column: 3, scope: !421)
!828 = !DILocation(line: 232, column: 1, scope: !421)
!829 = !DILocalVariable(name: "spinlock", arg: 1, scope: !440, file: !441, line: 37, type: !444)
!830 = !DILocation(line: 37, column: 1, scope: !440)
!831 = !DILocation(line: 38, column: 3, scope: !440)
!832 = !DILocation(line: 38, column: 31, scope: !833)
!833 = !DILexicalBlockFile(scope: !440, file: !441, discriminator: 1)
!834 = !DILocation(line: 38, column: 11, scope: !833)
!835 = !DILocation(line: 38, column: 10, scope: !833)
!836 = !DILocation(line: 38, column: 3, scope: !833)
!837 = !DILocation(line: 38, column: 42, scope: !838)
!838 = !DILexicalBlockFile(scope: !440, file: !441, discriminator: 2)
!839 = !DILocation(line: 38, column: 3, scope: !838)
!840 = !DILocation(line: 39, column: 1, scope: !440)
!841 = !DILocalVariable(name: "spinlock", arg: 1, scope: !451, file: !441, line: 41, type: !444)
!842 = !DILocation(line: 41, column: 1, scope: !451)
!843 = !DILocation(line: 42, column: 3, scope: !451)
!844 = !DILocation(line: 42, column: 36, scope: !451)
!845 = !DILocation(line: 43, column: 1, scope: !451)
!846 = !DILocalVariable(name: "tio", arg: 1, scope: !452, file: !1, line: 169, type: !455)
!847 = !DILocation(line: 169, column: 46, scope: !452)
!848 = !DILocation(line: 170, column: 3, scope: !452)
!849 = !DILocation(line: 170, column: 3, scope: !850)
!850 = !DILexicalBlockFile(scope: !452, file: !1, discriminator: 1)
!851 = !DILocation(line: 170, column: 3, scope: !852)
!852 = !DILexicalBlockFile(scope: !452, file: !1, discriminator: 2)
!853 = !DILocation(line: 170, column: 3, scope: !854)
!854 = !DILexicalBlockFile(scope: !452, file: !1, discriminator: 3)
!855 = !DILocation(line: 184, column: 13, scope: !452)
!856 = !DILocation(line: 184, column: 3, scope: !452)
!857 = !DILocation(line: 186, column: 1, scope: !452)
!858 = !DILocalVariable(name: "tty", arg: 1, scope: !425, file: !1, line: 235, type: !372)
!859 = !DILocation(line: 235, column: 34, scope: !425)
!860 = !DILocalVariable(name: "width", arg: 2, scope: !425, file: !1, line: 235, type: !428)
!861 = !DILocation(line: 235, column: 44, scope: !425)
!862 = !DILocalVariable(name: "height", arg: 3, scope: !425, file: !1, line: 235, type: !428)
!863 = !DILocation(line: 235, column: 56, scope: !425)
!864 = !DILocalVariable(name: "ws", scope: !425, file: !1, line: 236, type: !865)
!865 = !DICompositeType(tag: DW_TAG_structure_type, name: "winsize", file: !866, line: 27, size: 64, align: 16, elements: !867)
!866 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/ioctl-types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!867 = !{!868, !869, !870, !871}
!868 = !DIDerivedType(tag: DW_TAG_member, name: "ws_row", scope: !865, file: !866, line: 29, baseType: !594, size: 16, align: 16)
!869 = !DIDerivedType(tag: DW_TAG_member, name: "ws_col", scope: !865, file: !866, line: 30, baseType: !594, size: 16, align: 16, offset: 16)
!870 = !DIDerivedType(tag: DW_TAG_member, name: "ws_xpixel", scope: !865, file: !866, line: 31, baseType: !594, size: 16, align: 16, offset: 32)
!871 = !DIDerivedType(tag: DW_TAG_member, name: "ws_ypixel", scope: !865, file: !866, line: 32, baseType: !594, size: 16, align: 16, offset: 48)
!872 = !DILocation(line: 236, column: 18, scope: !425)
!873 = !DILocalVariable(name: "err", scope: !425, file: !1, line: 237, type: !98)
!874 = !DILocation(line: 237, column: 7, scope: !425)
!875 = !DILocation(line: 239, column: 3, scope: !425)
!876 = !DILocation(line: 240, column: 17, scope: !425)
!877 = !DILocation(line: 240, column: 11, scope: !425)
!878 = !DILocation(line: 240, column: 9, scope: !425)
!879 = !DILocation(line: 240, column: 5, scope: !425)
!880 = !DILocation(line: 241, column: 10, scope: !425)
!881 = !DILocation(line: 241, column: 14, scope: !425)
!882 = !DILocation(line: 241, column: 20, scope: !425)
!883 = !DILocation(line: 241, column: 23, scope: !884)
!884 = !DILexicalBlockFile(scope: !425, file: !1, discriminator: 1)
!885 = !DILocation(line: 241, column: 29, scope: !884)
!886 = !DILocation(line: 240, column: 5, scope: !884)
!887 = !DILocation(line: 243, column: 7, scope: !888)
!888 = distinct !DILexicalBlock(scope: !425, file: !1, line: 243, column: 7)
!889 = !DILocation(line: 243, column: 11, scope: !888)
!890 = !DILocation(line: 243, column: 7, scope: !425)
!891 = !DILocation(line: 244, column: 13, scope: !888)
!892 = !DILocation(line: 244, column: 12, scope: !888)
!893 = !DILocation(line: 244, column: 5, scope: !888)
!894 = !DILocation(line: 246, column: 15, scope: !425)
!895 = !DILocation(line: 246, column: 12, scope: !425)
!896 = !DILocation(line: 246, column: 4, scope: !425)
!897 = !DILocation(line: 246, column: 10, scope: !425)
!898 = !DILocation(line: 247, column: 16, scope: !425)
!899 = !DILocation(line: 247, column: 13, scope: !425)
!900 = !DILocation(line: 247, column: 4, scope: !425)
!901 = !DILocation(line: 247, column: 11, scope: !425)
!902 = !DILocation(line: 249, column: 3, scope: !425)
!903 = !DILocation(line: 250, column: 1, scope: !425)
!904 = !DILocalVariable(name: "saved_errno", scope: !433, file: !1, line: 317, type: !98)
!905 = !DILocation(line: 317, column: 7, scope: !433)
!906 = !DILocalVariable(name: "err", scope: !433, file: !1, line: 318, type: !98)
!907 = !DILocation(line: 318, column: 7, scope: !433)
!908 = !DILocation(line: 320, column: 17, scope: !433)
!909 = !DILocation(line: 320, column: 15, scope: !433)
!910 = !DILocation(line: 321, column: 8, scope: !911)
!911 = distinct !DILexicalBlock(scope: !433, file: !1, line: 321, column: 7)
!912 = !DILocation(line: 321, column: 7, scope: !433)
!913 = !DILocation(line: 322, column: 5, scope: !911)
!914 = !DILocation(line: 324, column: 7, scope: !433)
!915 = !DILocation(line: 325, column: 7, scope: !916)
!916 = distinct !DILexicalBlock(scope: !433, file: !1, line: 325, column: 7)
!917 = !DILocation(line: 325, column: 23, scope: !916)
!918 = !DILocation(line: 325, column: 7, scope: !433)
!919 = !DILocation(line: 326, column: 19, scope: !920)
!920 = distinct !DILexicalBlock(scope: !916, file: !1, line: 326, column: 9)
!921 = !DILocation(line: 326, column: 9, scope: !920)
!922 = !DILocation(line: 326, column: 9, scope: !916)
!923 = !DILocation(line: 327, column: 14, scope: !920)
!924 = !DILocation(line: 327, column: 13, scope: !920)
!925 = !DILocation(line: 327, column: 11, scope: !920)
!926 = !DILocation(line: 327, column: 7, scope: !920)
!927 = !DILocation(line: 326, column: 58, scope: !928)
!928 = !DILexicalBlockFile(scope: !920, file: !1, discriminator: 1)
!929 = !DILocation(line: 329, column: 3, scope: !433)
!930 = !DILocation(line: 330, column: 11, scope: !433)
!931 = !DILocation(line: 330, column: 3, scope: !433)
!932 = !DILocation(line: 330, column: 9, scope: !433)
!933 = !DILocation(line: 332, column: 10, scope: !433)
!934 = !DILocation(line: 332, column: 3, scope: !433)
!935 = !DILocation(line: 333, column: 1, scope: !433)
!936 = !DILocalVariable(name: "spinlock", arg: 1, scope: !456, file: !441, line: 45, type: !444)
!937 = !DILocation(line: 45, column: 1, scope: !456)
!938 = !DILocation(line: 50, column: 25, scope: !456)
!939 = !DILocation(line: 50, column: 35, scope: !456)
!940 = !DILocation(line: 50, column: 15, scope: !456)
!941 = !DILocation(line: 50, column: 12, scope: !456)
!942 = !DILocation(line: 50, column: 3, scope: !456)
!943 = !DILocation(line: 93, column: 3, scope: !449)
!944 = !{i32 1176946}
!945 = !DILocation(line: 95, column: 1, scope: !449)
!946 = !DILocalVariable(name: "ptr", arg: 1, scope: !459, file: !450, line: 33, type: !428)
!947 = !DILocation(line: 33, column: 1, scope: !459)
!948 = !DILocalVariable(name: "oldval", arg: 2, scope: !459, file: !450, line: 33, type: !98)
!949 = !DILocalVariable(name: "newval", arg: 3, scope: !459, file: !450, line: 33, type: !98)
!950 = !DILocalVariable(name: "out", scope: !459, file: !450, line: 35, type: !98)
!951 = !DILocation(line: 35, column: 7, scope: !459)
!952 = !DILocation(line: 37, column: 62, scope: !459)
!953 = !DILocation(line: 38, column: 32, scope: !459)
!954 = !DILocation(line: 38, column: 46, scope: !459)
!955 = !DILocation(line: 36, column: 3, scope: !459)
!956 = !{i32 1175196}
!957 = !DILocation(line: 40, column: 10, scope: !459)
!958 = !DILocation(line: 40, column: 3, scope: !459)
