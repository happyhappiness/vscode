; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/tcp.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

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
%struct.uv_tcp_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.4 = type { [4 x i8*] }
%struct.uv_buf_t = type { i8*, i64 }
%struct.uv_stream_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.5, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, {}*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.5 = type { [4 x i8*] }
%struct.uv_connect_s = type { i8*, i32, [2 x i8*], [4 x i8*], void (%struct.uv_connect_s*, i32)*, %struct.uv_stream_s*, [2 x i8*] }
%struct.uv_shutdown_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_stream_s*, void (%struct.uv_shutdown_s*, i32)* }
%struct.sockaddr = type { i16, [14 x i8] }
%union.__CONST_SOCKADDR_ARG = type { %struct.sockaddr* }
%union.__SOCKADDR_ARG = type { %struct.sockaddr* }

@.str = private unnamed_addr constant [23 x i8] c"handle->type == UV_TCP\00", align 1
@.str.1 = private unnamed_addr constant [67 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/tcp.c\00", align 1
@__PRETTY_FUNCTION__.uv__tcp_connect = private unnamed_addr constant [102 x i8] c"int uv__tcp_connect(uv_connect_t *, uv_tcp_t *, const struct sockaddr *, unsigned int, uv_connect_cb)\00", align 1
@uv_tcp_listen.single_accept = internal global i32 -1, align 4
@.str.2 = private unnamed_addr constant [21 x i8] c"UV_TCP_SINGLE_ACCEPT\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_init_ex(%struct.uv_loop_s* %loop, %struct.uv_tcp_s* %tcp, i32 %flags) #0 !dbg !400 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %tcp.addr = alloca %struct.uv_tcp_s*, align 8
  %flags.addr = alloca i32, align 4
  %domain = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !492, metadata !493), !dbg !494
  store %struct.uv_tcp_s* %tcp, %struct.uv_tcp_s** %tcp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %tcp.addr, metadata !495, metadata !493), !dbg !496
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !497, metadata !493), !dbg !498
  call void @llvm.dbg.declare(metadata i32* %domain, metadata !499, metadata !493), !dbg !500
  %0 = load i32, i32* %flags.addr, align 4, !dbg !501
  %and = and i32 %0, 255, !dbg !502
  store i32 %and, i32* %domain, align 4, !dbg !503
  %1 = load i32, i32* %domain, align 4, !dbg !504
  %cmp = icmp ne i32 %1, 2, !dbg !506
  br i1 %cmp, label %land.lhs.true, label %if.end, !dbg !507

land.lhs.true:                                    ; preds = %entry
  %2 = load i32, i32* %domain, align 4, !dbg !508
  %cmp1 = icmp ne i32 %2, 10, !dbg !510
  br i1 %cmp1, label %land.lhs.true2, label %if.end, !dbg !511

land.lhs.true2:                                   ; preds = %land.lhs.true
  %3 = load i32, i32* %domain, align 4, !dbg !512
  %cmp3 = icmp ne i32 %3, 0, !dbg !514
  br i1 %cmp3, label %if.then, label %if.end, !dbg !515

if.then:                                          ; preds = %land.lhs.true2
  store i32 -22, i32* %retval, align 4, !dbg !516
  br label %return, !dbg !516

if.end:                                           ; preds = %land.lhs.true2, %land.lhs.true, %entry
  %4 = load i32, i32* %flags.addr, align 4, !dbg !517
  %and4 = and i32 %4, -256, !dbg !519
  %tobool = icmp ne i32 %and4, 0, !dbg !519
  br i1 %tobool, label %if.then5, label %if.end6, !dbg !520

if.then5:                                         ; preds = %if.end
  store i32 -22, i32* %retval, align 4, !dbg !521
  br label %return, !dbg !521

if.end6:                                          ; preds = %if.end
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !522
  %6 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !523
  %7 = bitcast %struct.uv_tcp_s* %6 to %struct.uv_stream_s*, !dbg !524
  call void @uv__stream_init(%struct.uv_loop_s* %5, %struct.uv_stream_s* %7, i32 12), !dbg !525
  %8 = load i32, i32* %domain, align 4, !dbg !526
  %cmp7 = icmp ne i32 %8, 0, !dbg !528
  br i1 %cmp7, label %if.then8, label %if.end20, !dbg !529

if.then8:                                         ; preds = %if.end6
  call void @llvm.dbg.declare(metadata i32* %err, metadata !530, metadata !493), !dbg !532
  %9 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !533
  %10 = load i32, i32* %domain, align 4, !dbg !534
  %call = call i32 @maybe_new_socket(%struct.uv_tcp_s* %9, i32 %10, i32 0), !dbg !535
  store i32 %call, i32* %err, align 4, !dbg !532
  %11 = load i32, i32* %err, align 4, !dbg !536
  %tobool9 = icmp ne i32 %11, 0, !dbg !536
  br i1 %tobool9, label %if.then10, label %if.end19, !dbg !538

if.then10:                                        ; preds = %if.then8
  br label %do.body, !dbg !539

do.body:                                          ; preds = %if.then10
  %12 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !541
  %handle_queue = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %12, i32 0, i32 4, !dbg !541
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue, i64 0, i64 0, !dbg !541
  %13 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !541
  %14 = load [2 x i8*]*, [2 x i8*]** %13, align 8, !dbg !541
  %15 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !541
  %handle_queue11 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %15, i32 0, i32 4, !dbg !541
  %arrayidx12 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue11, i64 0, i64 1, !dbg !541
  %16 = bitcast i8** %arrayidx12 to [2 x i8*]**, !dbg !541
  %17 = load [2 x i8*]*, [2 x i8*]** %16, align 8, !dbg !541
  %arrayidx13 = getelementptr inbounds [2 x i8*], [2 x i8*]* %17, i64 0, i64 0, !dbg !541
  %18 = bitcast i8** %arrayidx13 to [2 x i8*]**, !dbg !541
  store [2 x i8*]* %14, [2 x i8*]** %18, align 8, !dbg !541
  %19 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !541
  %handle_queue14 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %19, i32 0, i32 4, !dbg !541
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue14, i64 0, i64 1, !dbg !541
  %20 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !541
  %21 = load [2 x i8*]*, [2 x i8*]** %20, align 8, !dbg !541
  %22 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !541
  %handle_queue16 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %22, i32 0, i32 4, !dbg !541
  %arrayidx17 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue16, i64 0, i64 0, !dbg !541
  %23 = bitcast i8** %arrayidx17 to [2 x i8*]**, !dbg !541
  %24 = load [2 x i8*]*, [2 x i8*]** %23, align 8, !dbg !541
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %24, i64 0, i64 1, !dbg !541
  %25 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !541
  store [2 x i8*]* %21, [2 x i8*]** %25, align 8, !dbg !541
  br label %do.end, !dbg !541

do.end:                                           ; preds = %do.body
  %26 = load i32, i32* %err, align 4, !dbg !544
  store i32 %26, i32* %retval, align 4, !dbg !545
  br label %return, !dbg !545

if.end19:                                         ; preds = %if.then8
  br label %if.end20, !dbg !546

if.end20:                                         ; preds = %if.end19, %if.end6
  store i32 0, i32* %retval, align 4, !dbg !547
  br label %return, !dbg !547

return:                                           ; preds = %if.end20, %do.end, %if.then5, %if.then
  %27 = load i32, i32* %retval, align 4, !dbg !548
  ret i32 %27, !dbg !548
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @uv__stream_init(%struct.uv_loop_s*, %struct.uv_stream_s*, i32) #2

; Function Attrs: nounwind uwtable
define internal i32 @maybe_new_socket(%struct.uv_tcp_s* %handle, i32 %domain, i32 %flags) #0 !dbg !484 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  %domain.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  %sockfd = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !549, metadata !493), !dbg !550
  store i32 %domain, i32* %domain.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %domain.addr, metadata !551, metadata !493), !dbg !552
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !553, metadata !493), !dbg !554
  call void @llvm.dbg.declare(metadata i32* %sockfd, metadata !555, metadata !493), !dbg !556
  call void @llvm.dbg.declare(metadata i32* %err, metadata !557, metadata !493), !dbg !558
  %0 = load i32, i32* %domain.addr, align 4, !dbg !559
  %cmp = icmp eq i32 %0, 0, !dbg !561
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !562

lor.lhs.false:                                    ; preds = %entry
  %1 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !563
  %io_watcher = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %1, i32 0, i32 13, !dbg !563
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !563
  %2 = load i32, i32* %fd, align 8, !dbg !563
  %cmp1 = icmp ne i32 %2, -1, !dbg !565
  br i1 %cmp1, label %if.then, label %if.end, !dbg !566

if.then:                                          ; preds = %lor.lhs.false, %entry
  %3 = load i32, i32* %flags.addr, align 4, !dbg !567
  %4 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !569
  %flags2 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %4, i32 0, i32 7, !dbg !570
  %5 = load i32, i32* %flags2, align 8, !dbg !571
  %or = or i32 %5, %3, !dbg !571
  store i32 %or, i32* %flags2, align 8, !dbg !571
  store i32 0, i32* %retval, align 4, !dbg !572
  br label %return, !dbg !572

if.end:                                           ; preds = %lor.lhs.false
  %6 = load i32, i32* %domain.addr, align 4, !dbg !573
  %call = call i32 @uv__socket(i32 %6, i32 1, i32 0), !dbg !574
  store i32 %call, i32* %err, align 4, !dbg !575
  %7 = load i32, i32* %err, align 4, !dbg !576
  %cmp3 = icmp slt i32 %7, 0, !dbg !578
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !579

if.then4:                                         ; preds = %if.end
  %8 = load i32, i32* %err, align 4, !dbg !580
  store i32 %8, i32* %retval, align 4, !dbg !581
  br label %return, !dbg !581

if.end5:                                          ; preds = %if.end
  %9 = load i32, i32* %err, align 4, !dbg !582
  store i32 %9, i32* %sockfd, align 4, !dbg !583
  %10 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !584
  %11 = bitcast %struct.uv_tcp_s* %10 to %struct.uv_stream_s*, !dbg !585
  %12 = load i32, i32* %sockfd, align 4, !dbg !586
  %13 = load i32, i32* %flags.addr, align 4, !dbg !587
  %call6 = call i32 @uv__stream_open(%struct.uv_stream_s* %11, i32 %12, i32 %13), !dbg !588
  store i32 %call6, i32* %err, align 4, !dbg !589
  %14 = load i32, i32* %err, align 4, !dbg !590
  %tobool = icmp ne i32 %14, 0, !dbg !590
  br i1 %tobool, label %if.then7, label %if.end9, !dbg !592

if.then7:                                         ; preds = %if.end5
  %15 = load i32, i32* %sockfd, align 4, !dbg !593
  %call8 = call i32 @uv__close(i32 %15), !dbg !595
  %16 = load i32, i32* %err, align 4, !dbg !596
  store i32 %16, i32* %retval, align 4, !dbg !597
  br label %return, !dbg !597

if.end9:                                          ; preds = %if.end5
  store i32 0, i32* %retval, align 4, !dbg !598
  br label %return, !dbg !598

return:                                           ; preds = %if.end9, %if.then7, %if.then4, %if.then
  %17 = load i32, i32* %retval, align 4, !dbg !599
  ret i32 %17, !dbg !599
}

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_init(%struct.uv_loop_s* %loop, %struct.uv_tcp_s* %tcp) #0 !dbg !432 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %tcp.addr = alloca %struct.uv_tcp_s*, align 8
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !600, metadata !493), !dbg !601
  store %struct.uv_tcp_s* %tcp, %struct.uv_tcp_s** %tcp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %tcp.addr, metadata !602, metadata !493), !dbg !603
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !604
  %1 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !605
  %call = call i32 @uv_tcp_init_ex(%struct.uv_loop_s* %0, %struct.uv_tcp_s* %1, i32 0), !dbg !606
  ret i32 %call, !dbg !607
}

; Function Attrs: nounwind uwtable
define i32 @uv__tcp_bind(%struct.uv_tcp_s* %tcp, %struct.sockaddr* %addr, i32 %addrlen, i32 %flags) #0 !dbg !435 {
entry:
  %retval = alloca i32, align 4
  %tcp.addr = alloca %struct.uv_tcp_s*, align 8
  %addr.addr = alloca %struct.sockaddr*, align 8
  %addrlen.addr = alloca i32, align 4
  %flags.addr = alloca i32, align 4
  %err = alloca i32, align 4
  %on = alloca i32, align 4
  %agg.tmp = alloca %union.__CONST_SOCKADDR_ARG, align 8
  store %struct.uv_tcp_s* %tcp, %struct.uv_tcp_s** %tcp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %tcp.addr, metadata !608, metadata !493), !dbg !609
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !610, metadata !493), !dbg !611
  store i32 %addrlen, i32* %addrlen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %addrlen.addr, metadata !612, metadata !493), !dbg !613
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !614, metadata !493), !dbg !615
  call void @llvm.dbg.declare(metadata i32* %err, metadata !616, metadata !493), !dbg !617
  call void @llvm.dbg.declare(metadata i32* %on, metadata !618, metadata !493), !dbg !619
  %0 = load i32, i32* %flags.addr, align 4, !dbg !620
  %and = and i32 %0, 1, !dbg !622
  %tobool = icmp ne i32 %and, 0, !dbg !622
  br i1 %tobool, label %land.lhs.true, label %if.end, !dbg !623

land.lhs.true:                                    ; preds = %entry
  %1 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !624
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %1, i32 0, i32 0, !dbg !626
  %2 = load i16, i16* %sa_family, align 2, !dbg !626
  %conv = zext i16 %2 to i32, !dbg !624
  %cmp = icmp ne i32 %conv, 10, !dbg !627
  br i1 %cmp, label %if.then, label %if.end, !dbg !628

if.then:                                          ; preds = %land.lhs.true
  store i32 -22, i32* %retval, align 4, !dbg !629
  br label %return, !dbg !629

if.end:                                           ; preds = %land.lhs.true, %entry
  %3 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !630
  %4 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !631
  %sa_family2 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %4, i32 0, i32 0, !dbg !632
  %5 = load i16, i16* %sa_family2, align 2, !dbg !632
  %conv3 = zext i16 %5 to i32, !dbg !631
  %call = call i32 @maybe_new_socket(%struct.uv_tcp_s* %3, i32 %conv3, i32 96), !dbg !633
  store i32 %call, i32* %err, align 4, !dbg !634
  %6 = load i32, i32* %err, align 4, !dbg !635
  %tobool4 = icmp ne i32 %6, 0, !dbg !635
  br i1 %tobool4, label %if.then5, label %if.end6, !dbg !637

if.then5:                                         ; preds = %if.end
  %7 = load i32, i32* %err, align 4, !dbg !638
  store i32 %7, i32* %retval, align 4, !dbg !639
  br label %return, !dbg !639

if.end6:                                          ; preds = %if.end
  store i32 1, i32* %on, align 4, !dbg !640
  %8 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !641
  %io_watcher = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %8, i32 0, i32 13, !dbg !643
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !644
  %9 = load i32, i32* %fd, align 8, !dbg !644
  %10 = bitcast i32* %on to i8*, !dbg !645
  %call7 = call i32 @setsockopt(i32 %9, i32 1, i32 2, i8* %10, i32 4) #7, !dbg !646
  %tobool8 = icmp ne i32 %call7, 0, !dbg !646
  br i1 %tobool8, label %if.then9, label %if.end11, !dbg !647

if.then9:                                         ; preds = %if.end6
  %call10 = call i32* @__errno_location() #1, !dbg !648
  %11 = load i32, i32* %call10, align 4, !dbg !648
  %sub = sub nsw i32 0, %11, !dbg !649
  store i32 %sub, i32* %retval, align 4, !dbg !650
  br label %return, !dbg !650

if.end11:                                         ; preds = %if.end6
  %12 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !651
  %sa_family12 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %12, i32 0, i32 0, !dbg !653
  %13 = load i16, i16* %sa_family12, align 2, !dbg !653
  %conv13 = zext i16 %13 to i32, !dbg !651
  %cmp14 = icmp eq i32 %conv13, 10, !dbg !654
  br i1 %cmp14, label %if.then16, label %if.end29, !dbg !655

if.then16:                                        ; preds = %if.end11
  %14 = load i32, i32* %flags.addr, align 4, !dbg !656
  %and17 = and i32 %14, 1, !dbg !658
  %cmp18 = icmp ne i32 %and17, 0, !dbg !659
  %conv19 = zext i1 %cmp18 to i32, !dbg !659
  store i32 %conv19, i32* %on, align 4, !dbg !660
  %15 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !661
  %io_watcher20 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %15, i32 0, i32 13, !dbg !663
  %fd21 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher20, i32 0, i32 5, !dbg !664
  %16 = load i32, i32* %fd21, align 8, !dbg !664
  %17 = bitcast i32* %on to i8*, !dbg !665
  %call22 = call i32 @setsockopt(i32 %16, i32 41, i32 26, i8* %17, i32 4) #7, !dbg !666
  %cmp23 = icmp eq i32 %call22, -1, !dbg !667
  br i1 %cmp23, label %if.then25, label %if.end28, !dbg !668

if.then25:                                        ; preds = %if.then16
  %call26 = call i32* @__errno_location() #1, !dbg !669
  %18 = load i32, i32* %call26, align 4, !dbg !669
  %sub27 = sub nsw i32 0, %18, !dbg !671
  store i32 %sub27, i32* %retval, align 4, !dbg !672
  br label %return, !dbg !672

if.end28:                                         ; preds = %if.then16
  br label %if.end29, !dbg !673

if.end29:                                         ; preds = %if.end28, %if.end11
  %call30 = call i32* @__errno_location() #1, !dbg !674
  store i32 0, i32* %call30, align 4, !dbg !675
  %19 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !676
  %io_watcher31 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %19, i32 0, i32 13, !dbg !678
  %fd32 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher31, i32 0, i32 5, !dbg !679
  %20 = load i32, i32* %fd32, align 8, !dbg !679
  %__sockaddr__ = bitcast %union.__CONST_SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !680
  %21 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !680
  store %struct.sockaddr* %21, %struct.sockaddr** %__sockaddr__, align 8, !dbg !680
  %22 = load i32, i32* %addrlen.addr, align 4, !dbg !681
  %coerce.dive = getelementptr inbounds %union.__CONST_SOCKADDR_ARG, %union.__CONST_SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !682
  %23 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !682
  %call33 = call i32 @bind(i32 %20, %struct.sockaddr* %23, i32 %22) #7, !dbg !682
  %tobool34 = icmp ne i32 %call33, 0, !dbg !682
  br i1 %tobool34, label %land.lhs.true35, label %if.end47, !dbg !683

land.lhs.true35:                                  ; preds = %if.end29
  %call36 = call i32* @__errno_location() #1, !dbg !684
  %24 = load i32, i32* %call36, align 4, !dbg !684
  %cmp37 = icmp ne i32 %24, 98, !dbg !686
  br i1 %cmp37, label %if.then39, label %if.end47, !dbg !687

if.then39:                                        ; preds = %land.lhs.true35
  %call40 = call i32* @__errno_location() #1, !dbg !688
  %25 = load i32, i32* %call40, align 4, !dbg !688
  %cmp41 = icmp eq i32 %25, 97, !dbg !691
  br i1 %cmp41, label %if.then43, label %if.end44, !dbg !692

if.then43:                                        ; preds = %if.then39
  store i32 -22, i32* %retval, align 4, !dbg !693
  br label %return, !dbg !693

if.end44:                                         ; preds = %if.then39
  %call45 = call i32* @__errno_location() #1, !dbg !694
  %26 = load i32, i32* %call45, align 4, !dbg !694
  %sub46 = sub nsw i32 0, %26, !dbg !695
  store i32 %sub46, i32* %retval, align 4, !dbg !696
  br label %return, !dbg !696

if.end47:                                         ; preds = %land.lhs.true35, %if.end29
  %call48 = call i32* @__errno_location() #1, !dbg !697
  %27 = load i32, i32* %call48, align 4, !dbg !697
  %sub49 = sub nsw i32 0, %27, !dbg !698
  %28 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !699
  %delayed_error = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %28, i32 0, i32 17, !dbg !700
  store i32 %sub49, i32* %delayed_error, align 8, !dbg !701
  %29 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !702
  %flags50 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %29, i32 0, i32 7, !dbg !703
  %30 = load i32, i32* %flags50, align 8, !dbg !704
  %or = or i32 %30, 262144, !dbg !704
  store i32 %or, i32* %flags50, align 8, !dbg !704
  %31 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !705
  %sa_family51 = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %31, i32 0, i32 0, !dbg !707
  %32 = load i16, i16* %sa_family51, align 2, !dbg !707
  %conv52 = zext i16 %32 to i32, !dbg !705
  %cmp53 = icmp eq i32 %conv52, 10, !dbg !708
  br i1 %cmp53, label %if.then55, label %if.end58, !dbg !709

if.then55:                                        ; preds = %if.end47
  %33 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !710
  %flags56 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %33, i32 0, i32 7, !dbg !711
  %34 = load i32, i32* %flags56, align 8, !dbg !712
  %or57 = or i32 %34, 65536, !dbg !712
  store i32 %or57, i32* %flags56, align 8, !dbg !712
  br label %if.end58, !dbg !710

if.end58:                                         ; preds = %if.then55, %if.end47
  store i32 0, i32* %retval, align 4, !dbg !713
  br label %return, !dbg !713

return:                                           ; preds = %if.end58, %if.end44, %if.then43, %if.then25, %if.then9, %if.then5, %if.then
  %35 = load i32, i32* %retval, align 4, !dbg !714
  ret i32 %35, !dbg !714
}

; Function Attrs: nounwind
declare i32 @setsockopt(i32, i32, i32, i8*, i32) #3

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #4

; Function Attrs: nounwind
declare i32 @bind(i32, %struct.sockaddr*, i32) #3

; Function Attrs: nounwind uwtable
define i32 @uv__tcp_connect(%struct.uv_connect_s* %req, %struct.uv_tcp_s* %handle, %struct.sockaddr* %addr, i32 %addrlen, void (%struct.uv_connect_s*, i32)* %cb) #0 !dbg !450 {
entry:
  %retval = alloca i32, align 4
  %req.addr = alloca %struct.uv_connect_s*, align 8
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  %addr.addr = alloca %struct.sockaddr*, align 8
  %addrlen.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_connect_s*, i32)*, align 8
  %err = alloca i32, align 4
  %r = alloca i32, align 4
  %agg.tmp = alloca %union.__CONST_SOCKADDR_ARG, align 8
  store %struct.uv_connect_s* %req, %struct.uv_connect_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_connect_s** %req.addr, metadata !715, metadata !493), !dbg !716
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !717, metadata !493), !dbg !718
  store %struct.sockaddr* %addr, %struct.sockaddr** %addr.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %addr.addr, metadata !719, metadata !493), !dbg !720
  store i32 %addrlen, i32* %addrlen.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %addrlen.addr, metadata !721, metadata !493), !dbg !722
  store void (%struct.uv_connect_s*, i32)* %cb, void (%struct.uv_connect_s*, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_connect_s*, i32)** %cb.addr, metadata !723, metadata !493), !dbg !724
  call void @llvm.dbg.declare(metadata i32* %err, metadata !725, metadata !493), !dbg !726
  call void @llvm.dbg.declare(metadata i32* %r, metadata !727, metadata !493), !dbg !728
  %0 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !729
  %type = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %0, i32 0, i32 2, !dbg !729
  %1 = load i32, i32* %type, align 8, !dbg !729
  %cmp = icmp eq i32 %1, 12, !dbg !729
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !729

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !730

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.1, i32 0, i32 0), i32 153, i8* getelementptr inbounds ([102 x i8], [102 x i8]* @__PRETTY_FUNCTION__.uv__tcp_connect, i32 0, i32 0)) #8, !dbg !732
  unreachable, !dbg !732
                                                  ; No predecessors!
  br label %cond.end, !dbg !734

cond.end:                                         ; preds = %2, %cond.true
  %3 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !736
  %connect_req = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %3, i32 0, i32 11, !dbg !738
  %4 = load %struct.uv_connect_s*, %struct.uv_connect_s** %connect_req, align 8, !dbg !738
  %cmp1 = icmp ne %struct.uv_connect_s* %4, null, !dbg !739
  br i1 %cmp1, label %if.then, label %if.end, !dbg !740

if.then:                                          ; preds = %cond.end
  store i32 -114, i32* %retval, align 4, !dbg !741
  br label %return, !dbg !741

if.end:                                           ; preds = %cond.end
  %5 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !742
  %6 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !743
  %sa_family = getelementptr inbounds %struct.sockaddr, %struct.sockaddr* %6, i32 0, i32 0, !dbg !744
  %7 = load i16, i16* %sa_family, align 2, !dbg !744
  %conv = zext i16 %7 to i32, !dbg !743
  %call = call i32 @maybe_new_socket(%struct.uv_tcp_s* %5, i32 %conv, i32 96), !dbg !745
  store i32 %call, i32* %err, align 4, !dbg !746
  %8 = load i32, i32* %err, align 4, !dbg !747
  %tobool = icmp ne i32 %8, 0, !dbg !747
  br i1 %tobool, label %if.then2, label %if.end3, !dbg !749

if.then2:                                         ; preds = %if.end
  %9 = load i32, i32* %err, align 4, !dbg !750
  store i32 %9, i32* %retval, align 4, !dbg !751
  br label %return, !dbg !751

if.end3:                                          ; preds = %if.end
  %10 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !752
  %delayed_error = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %10, i32 0, i32 17, !dbg !753
  store i32 0, i32* %delayed_error, align 8, !dbg !754
  br label %do.body, !dbg !755

do.body:                                          ; preds = %land.end, %if.end3
  %call4 = call i32* @__errno_location() #1, !dbg !756
  store i32 0, i32* %call4, align 4, !dbg !758
  %11 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !759
  %io_watcher = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %11, i32 0, i32 13, !dbg !759
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !759
  %12 = load i32, i32* %fd, align 8, !dbg !759
  %__sockaddr__ = bitcast %union.__CONST_SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !760
  %13 = load %struct.sockaddr*, %struct.sockaddr** %addr.addr, align 8, !dbg !760
  store %struct.sockaddr* %13, %struct.sockaddr** %__sockaddr__, align 8, !dbg !760
  %14 = load i32, i32* %addrlen.addr, align 4, !dbg !761
  %coerce.dive = getelementptr inbounds %union.__CONST_SOCKADDR_ARG, %union.__CONST_SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !762
  %15 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !762
  %call5 = call i32 @connect(i32 %12, %struct.sockaddr* %15, i32 %14), !dbg !762
  store i32 %call5, i32* %r, align 4, !dbg !763
  br label %do.cond, !dbg !764

do.cond:                                          ; preds = %do.body
  %16 = load i32, i32* %r, align 4, !dbg !765
  %cmp6 = icmp eq i32 %16, -1, !dbg !766
  br i1 %cmp6, label %land.rhs, label %land.end, !dbg !767

land.rhs:                                         ; preds = %do.cond
  %call8 = call i32* @__errno_location() #1, !dbg !768
  %17 = load i32, i32* %call8, align 4, !dbg !768
  %cmp9 = icmp eq i32 %17, 4, !dbg !769
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %18 = phi i1 [ false, %do.cond ], [ %cmp9, %land.rhs ]
  br i1 %18, label %do.body, label %do.end, !dbg !770

do.end:                                           ; preds = %land.end
  %19 = load i32, i32* %r, align 4, !dbg !772
  %cmp11 = icmp eq i32 %19, -1, !dbg !774
  br i1 %cmp11, label %land.lhs.true, label %if.end32, !dbg !775

land.lhs.true:                                    ; preds = %do.end
  %call13 = call i32* @__errno_location() #1, !dbg !776
  %20 = load i32, i32* %call13, align 4, !dbg !776
  %cmp14 = icmp ne i32 %20, 0, !dbg !778
  br i1 %cmp14, label %if.then16, label %if.end32, !dbg !779

if.then16:                                        ; preds = %land.lhs.true
  %call17 = call i32* @__errno_location() #1, !dbg !780
  %21 = load i32, i32* %call17, align 4, !dbg !780
  %cmp18 = icmp eq i32 %21, 115, !dbg !783
  br i1 %cmp18, label %if.then20, label %if.else, !dbg !784

if.then20:                                        ; preds = %if.then16
  br label %if.end31, !dbg !785

if.else:                                          ; preds = %if.then16
  %call21 = call i32* @__errno_location() #1, !dbg !787
  %22 = load i32, i32* %call21, align 4, !dbg !787
  %cmp22 = icmp eq i32 %22, 111, !dbg !789
  br i1 %cmp22, label %if.then24, label %if.else27, !dbg !790

if.then24:                                        ; preds = %if.else
  %call25 = call i32* @__errno_location() #1, !dbg !791
  %23 = load i32, i32* %call25, align 4, !dbg !791
  %sub = sub nsw i32 0, %23, !dbg !792
  %24 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !793
  %delayed_error26 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %24, i32 0, i32 17, !dbg !794
  store i32 %sub, i32* %delayed_error26, align 8, !dbg !795
  br label %if.end30, !dbg !793

if.else27:                                        ; preds = %if.else
  %call28 = call i32* @__errno_location() #1, !dbg !796
  %25 = load i32, i32* %call28, align 4, !dbg !796
  %sub29 = sub nsw i32 0, %25, !dbg !797
  store i32 %sub29, i32* %retval, align 4, !dbg !798
  br label %return, !dbg !798

if.end30:                                         ; preds = %if.then24
  br label %if.end31

if.end31:                                         ; preds = %if.end30, %if.then20
  br label %if.end32, !dbg !799

if.end32:                                         ; preds = %if.end31, %land.lhs.true, %do.end
  br label %do.body33, !dbg !800

do.body33:                                        ; preds = %if.end32
  br label %do.body34, !dbg !801

do.body34:                                        ; preds = %do.body33
  %26 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !804
  %type35 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %26, i32 0, i32 1, !dbg !804
  store i32 2, i32* %type35, align 8, !dbg !804
  br label %do.end37, !dbg !804

do.end37:                                         ; preds = %do.body34
  br label %do.body38, !dbg !807

do.body38:                                        ; preds = %do.end37
  br label %do.body39, !dbg !809

do.body39:                                        ; preds = %do.body38
  %27 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !812
  %loop = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %27, i32 0, i32 1, !dbg !812
  %28 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !812
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %28, i32 0, i32 3, !dbg !812
  %29 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !812
  %active_queue = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %29, i32 0, i32 2, !dbg !812
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !812
  %30 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !812
  store [2 x i8*]* %active_reqs, [2 x i8*]** %30, align 8, !dbg !812
  %31 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !812
  %loop40 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %31, i32 0, i32 1, !dbg !812
  %32 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop40, align 8, !dbg !812
  %active_reqs41 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %32, i32 0, i32 3, !dbg !812
  %arrayidx42 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs41, i64 0, i64 1, !dbg !812
  %33 = bitcast i8** %arrayidx42 to [2 x i8*]**, !dbg !812
  %34 = load [2 x i8*]*, [2 x i8*]** %33, align 8, !dbg !812
  %35 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !812
  %active_queue43 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %35, i32 0, i32 2, !dbg !812
  %arrayidx44 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue43, i64 0, i64 1, !dbg !812
  %36 = bitcast i8** %arrayidx44 to [2 x i8*]**, !dbg !812
  store [2 x i8*]* %34, [2 x i8*]** %36, align 8, !dbg !812
  %37 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !812
  %active_queue45 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %37, i32 0, i32 2, !dbg !812
  %38 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !812
  %active_queue46 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %38, i32 0, i32 2, !dbg !812
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue46, i64 0, i64 1, !dbg !812
  %39 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !812
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !812
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %40, i64 0, i64 0, !dbg !812
  %41 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !812
  store [2 x i8*]* %active_queue45, [2 x i8*]** %41, align 8, !dbg !812
  %42 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !812
  %active_queue49 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %42, i32 0, i32 2, !dbg !812
  %43 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !812
  %loop50 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %43, i32 0, i32 1, !dbg !812
  %44 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop50, align 8, !dbg !812
  %active_reqs51 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %44, i32 0, i32 3, !dbg !812
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs51, i64 0, i64 1, !dbg !812
  %45 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !812
  store [2 x i8*]* %active_queue49, [2 x i8*]** %45, align 8, !dbg !812
  br label %do.end54, !dbg !812

do.end54:                                         ; preds = %do.body39
  br label %do.end56, !dbg !815

do.end56:                                         ; preds = %do.end54
  br label %do.end58, !dbg !817

do.end58:                                         ; preds = %do.end56
  %46 = load void (%struct.uv_connect_s*, i32)*, void (%struct.uv_connect_s*, i32)** %cb.addr, align 8, !dbg !819
  %47 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !820
  %cb59 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %47, i32 0, i32 4, !dbg !821
  store void (%struct.uv_connect_s*, i32)* %46, void (%struct.uv_connect_s*, i32)** %cb59, align 8, !dbg !822
  %48 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !823
  %49 = bitcast %struct.uv_tcp_s* %48 to %struct.uv_stream_s*, !dbg !824
  %50 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !825
  %handle60 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %50, i32 0, i32 5, !dbg !826
  store %struct.uv_stream_s* %49, %struct.uv_stream_s** %handle60, align 8, !dbg !827
  br label %do.body61, !dbg !828

do.body61:                                        ; preds = %do.end58
  %51 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !829
  %queue = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %51, i32 0, i32 6, !dbg !829
  %52 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !829
  %queue62 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %52, i32 0, i32 6, !dbg !829
  %arrayidx63 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue62, i64 0, i64 0, !dbg !829
  %53 = bitcast i8** %arrayidx63 to [2 x i8*]**, !dbg !829
  store [2 x i8*]* %queue, [2 x i8*]** %53, align 8, !dbg !829
  %54 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !829
  %queue64 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %54, i32 0, i32 6, !dbg !829
  %55 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !829
  %queue65 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %55, i32 0, i32 6, !dbg !829
  %arrayidx66 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue65, i64 0, i64 1, !dbg !829
  %56 = bitcast i8** %arrayidx66 to [2 x i8*]**, !dbg !829
  store [2 x i8*]* %queue64, [2 x i8*]** %56, align 8, !dbg !829
  br label %do.end68, !dbg !829

do.end68:                                         ; preds = %do.body61
  %57 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !832
  %58 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !833
  %connect_req69 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %58, i32 0, i32 11, !dbg !834
  store %struct.uv_connect_s* %57, %struct.uv_connect_s** %connect_req69, align 8, !dbg !835
  %59 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !836
  %loop70 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %59, i32 0, i32 1, !dbg !837
  %60 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop70, align 8, !dbg !837
  %61 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !838
  %io_watcher71 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %61, i32 0, i32 13, !dbg !839
  call void @uv__io_start(%struct.uv_loop_s* %60, %struct.uv__io_s* %io_watcher71, i32 4), !dbg !840
  %62 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !841
  %delayed_error72 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %62, i32 0, i32 17, !dbg !843
  %63 = load i32, i32* %delayed_error72, align 8, !dbg !843
  %tobool73 = icmp ne i32 %63, 0, !dbg !841
  br i1 %tobool73, label %if.then74, label %if.end77, !dbg !844

if.then74:                                        ; preds = %do.end68
  %64 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !845
  %loop75 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %64, i32 0, i32 1, !dbg !846
  %65 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop75, align 8, !dbg !846
  %66 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !847
  %io_watcher76 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %66, i32 0, i32 13, !dbg !848
  call void @uv__io_feed(%struct.uv_loop_s* %65, %struct.uv__io_s* %io_watcher76), !dbg !849
  br label %if.end77, !dbg !849

if.end77:                                         ; preds = %if.then74, %do.end68
  store i32 0, i32* %retval, align 4, !dbg !850
  br label %return, !dbg !850

return:                                           ; preds = %if.end77, %if.else27, %if.then2, %if.then
  %67 = load i32, i32* %retval, align 4, !dbg !851
  ret i32 %67, !dbg !851
}

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #5

declare i32 @connect(i32, %struct.sockaddr*, i32) #2

declare void @uv__io_start(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

declare void @uv__io_feed(%struct.uv_loop_s*, %struct.uv__io_s*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_open(%struct.uv_tcp_s* %handle, i32 %sock) #0 !dbg !453 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  %sock.addr = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !852, metadata !493), !dbg !853
  store i32 %sock, i32* %sock.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %sock.addr, metadata !854, metadata !493), !dbg !855
  call void @llvm.dbg.declare(metadata i32* %err, metadata !856, metadata !493), !dbg !857
  %0 = load i32, i32* %sock.addr, align 4, !dbg !858
  %call = call i32 @uv__nonblock_ioctl(i32 %0, i32 1), !dbg !859
  store i32 %call, i32* %err, align 4, !dbg !860
  %1 = load i32, i32* %err, align 4, !dbg !861
  %tobool = icmp ne i32 %1, 0, !dbg !861
  br i1 %tobool, label %if.then, label %if.end, !dbg !863

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %err, align 4, !dbg !864
  store i32 %2, i32* %retval, align 4, !dbg !865
  br label %return, !dbg !865

if.end:                                           ; preds = %entry
  %3 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !866
  %4 = bitcast %struct.uv_tcp_s* %3 to %struct.uv_stream_s*, !dbg !867
  %5 = load i32, i32* %sock.addr, align 4, !dbg !868
  %call1 = call i32 @uv__stream_open(%struct.uv_stream_s* %4, i32 %5, i32 96), !dbg !869
  store i32 %call1, i32* %retval, align 4, !dbg !870
  br label %return, !dbg !870

return:                                           ; preds = %if.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !871
  ret i32 %6, !dbg !871
}

declare i32 @uv__nonblock_ioctl(i32, i32) #2

declare i32 @uv__stream_open(%struct.uv_stream_s*, i32, i32) #2

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_getsockname(%struct.uv_tcp_s* %handle, %struct.sockaddr* %name, i32* %namelen) #0 !dbg !457 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  %name.addr = alloca %struct.sockaddr*, align 8
  %namelen.addr = alloca i32*, align 8
  %socklen = alloca i32, align 4
  %agg.tmp = alloca %union.__SOCKADDR_ARG, align 8
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !872, metadata !493), !dbg !873
  store %struct.sockaddr* %name, %struct.sockaddr** %name.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %name.addr, metadata !874, metadata !493), !dbg !875
  store i32* %namelen, i32** %namelen.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %namelen.addr, metadata !876, metadata !493), !dbg !877
  call void @llvm.dbg.declare(metadata i32* %socklen, metadata !878, metadata !493), !dbg !879
  %0 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !880
  %delayed_error = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %0, i32 0, i32 17, !dbg !882
  %1 = load i32, i32* %delayed_error, align 8, !dbg !882
  %tobool = icmp ne i32 %1, 0, !dbg !880
  br i1 %tobool, label %if.then, label %if.end, !dbg !883

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !884
  %delayed_error1 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %2, i32 0, i32 17, !dbg !885
  %3 = load i32, i32* %delayed_error1, align 8, !dbg !885
  store i32 %3, i32* %retval, align 4, !dbg !886
  br label %return, !dbg !886

if.end:                                           ; preds = %entry
  %4 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !887
  %io_watcher = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %4, i32 0, i32 13, !dbg !887
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !887
  %5 = load i32, i32* %fd, align 8, !dbg !887
  %cmp = icmp slt i32 %5, 0, !dbg !889
  br i1 %cmp, label %if.then2, label %if.end3, !dbg !890

if.then2:                                         ; preds = %if.end
  store i32 -22, i32* %retval, align 4, !dbg !891
  br label %return, !dbg !891

if.end3:                                          ; preds = %if.end
  %6 = load i32*, i32** %namelen.addr, align 8, !dbg !892
  %7 = load i32, i32* %6, align 4, !dbg !893
  store i32 %7, i32* %socklen, align 4, !dbg !894
  %8 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !895
  %io_watcher4 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %8, i32 0, i32 13, !dbg !895
  %fd5 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher4, i32 0, i32 5, !dbg !895
  %9 = load i32, i32* %fd5, align 8, !dbg !895
  %__sockaddr__ = bitcast %union.__SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !897
  %10 = load %struct.sockaddr*, %struct.sockaddr** %name.addr, align 8, !dbg !897
  store %struct.sockaddr* %10, %struct.sockaddr** %__sockaddr__, align 8, !dbg !897
  %coerce.dive = getelementptr inbounds %union.__SOCKADDR_ARG, %union.__SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !898
  %11 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !898
  %call = call i32 @getsockname(i32 %9, %struct.sockaddr* %11, i32* %socklen) #7, !dbg !898
  %tobool6 = icmp ne i32 %call, 0, !dbg !898
  br i1 %tobool6, label %if.then7, label %if.end9, !dbg !899

if.then7:                                         ; preds = %if.end3
  %call8 = call i32* @__errno_location() #1, !dbg !900
  %12 = load i32, i32* %call8, align 4, !dbg !900
  %sub = sub nsw i32 0, %12, !dbg !901
  store i32 %sub, i32* %retval, align 4, !dbg !902
  br label %return, !dbg !902

if.end9:                                          ; preds = %if.end3
  %13 = load i32, i32* %socklen, align 4, !dbg !903
  %14 = load i32*, i32** %namelen.addr, align 8, !dbg !904
  store i32 %13, i32* %14, align 4, !dbg !905
  store i32 0, i32* %retval, align 4, !dbg !906
  br label %return, !dbg !906

return:                                           ; preds = %if.end9, %if.then7, %if.then2, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !907
  ret i32 %15, !dbg !907
}

; Function Attrs: nounwind
declare i32 @getsockname(i32, %struct.sockaddr*, i32*) #3

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_getpeername(%struct.uv_tcp_s* %handle, %struct.sockaddr* %name, i32* %namelen) #0 !dbg !464 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  %name.addr = alloca %struct.sockaddr*, align 8
  %namelen.addr = alloca i32*, align 8
  %socklen = alloca i32, align 4
  %agg.tmp = alloca %union.__SOCKADDR_ARG, align 8
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !908, metadata !493), !dbg !909
  store %struct.sockaddr* %name, %struct.sockaddr** %name.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.sockaddr** %name.addr, metadata !910, metadata !493), !dbg !911
  store i32* %namelen, i32** %namelen.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %namelen.addr, metadata !912, metadata !493), !dbg !913
  call void @llvm.dbg.declare(metadata i32* %socklen, metadata !914, metadata !493), !dbg !915
  %0 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !916
  %delayed_error = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %0, i32 0, i32 17, !dbg !918
  %1 = load i32, i32* %delayed_error, align 8, !dbg !918
  %tobool = icmp ne i32 %1, 0, !dbg !916
  br i1 %tobool, label %if.then, label %if.end, !dbg !919

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !920
  %delayed_error1 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %2, i32 0, i32 17, !dbg !921
  %3 = load i32, i32* %delayed_error1, align 8, !dbg !921
  store i32 %3, i32* %retval, align 4, !dbg !922
  br label %return, !dbg !922

if.end:                                           ; preds = %entry
  %4 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !923
  %io_watcher = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %4, i32 0, i32 13, !dbg !923
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !923
  %5 = load i32, i32* %fd, align 8, !dbg !923
  %cmp = icmp slt i32 %5, 0, !dbg !925
  br i1 %cmp, label %if.then2, label %if.end3, !dbg !926

if.then2:                                         ; preds = %if.end
  store i32 -22, i32* %retval, align 4, !dbg !927
  br label %return, !dbg !927

if.end3:                                          ; preds = %if.end
  %6 = load i32*, i32** %namelen.addr, align 8, !dbg !928
  %7 = load i32, i32* %6, align 4, !dbg !929
  store i32 %7, i32* %socklen, align 4, !dbg !930
  %8 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !931
  %io_watcher4 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %8, i32 0, i32 13, !dbg !931
  %fd5 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher4, i32 0, i32 5, !dbg !931
  %9 = load i32, i32* %fd5, align 8, !dbg !931
  %__sockaddr__ = bitcast %union.__SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !933
  %10 = load %struct.sockaddr*, %struct.sockaddr** %name.addr, align 8, !dbg !933
  store %struct.sockaddr* %10, %struct.sockaddr** %__sockaddr__, align 8, !dbg !933
  %coerce.dive = getelementptr inbounds %union.__SOCKADDR_ARG, %union.__SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !934
  %11 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !934
  %call = call i32 @getpeername(i32 %9, %struct.sockaddr* %11, i32* %socklen) #7, !dbg !934
  %tobool6 = icmp ne i32 %call, 0, !dbg !934
  br i1 %tobool6, label %if.then7, label %if.end9, !dbg !935

if.then7:                                         ; preds = %if.end3
  %call8 = call i32* @__errno_location() #1, !dbg !936
  %12 = load i32, i32* %call8, align 4, !dbg !936
  %sub = sub nsw i32 0, %12, !dbg !937
  store i32 %sub, i32* %retval, align 4, !dbg !938
  br label %return, !dbg !938

if.end9:                                          ; preds = %if.end3
  %13 = load i32, i32* %socklen, align 4, !dbg !939
  %14 = load i32*, i32** %namelen.addr, align 8, !dbg !940
  store i32 %13, i32* %14, align 4, !dbg !941
  store i32 0, i32* %retval, align 4, !dbg !942
  br label %return, !dbg !942

return:                                           ; preds = %if.end9, %if.then7, %if.then2, %if.then
  %15 = load i32, i32* %retval, align 4, !dbg !943
  ret i32 %15, !dbg !943
}

; Function Attrs: nounwind
declare i32 @getpeername(i32, %struct.sockaddr*, i32*) #3

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_listen(%struct.uv_tcp_s* %tcp, i32 %backlog, void (%struct.uv_stream_s*, i32)* %cb) #0 !dbg !465 {
entry:
  %retval = alloca i32, align 4
  %tcp.addr = alloca %struct.uv_tcp_s*, align 8
  %backlog.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_stream_s*, i32)*, align 8
  %err = alloca i32, align 4
  %val = alloca i8*, align 8
  store %struct.uv_tcp_s* %tcp, %struct.uv_tcp_s** %tcp.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %tcp.addr, metadata !944, metadata !493), !dbg !945
  store i32 %backlog, i32* %backlog.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %backlog.addr, metadata !946, metadata !493), !dbg !947
  store void (%struct.uv_stream_s*, i32)* %cb, void (%struct.uv_stream_s*, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_stream_s*, i32)** %cb.addr, metadata !948, metadata !493), !dbg !949
  call void @llvm.dbg.declare(metadata i32* %err, metadata !950, metadata !493), !dbg !951
  %0 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !952
  %delayed_error = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %0, i32 0, i32 17, !dbg !954
  %1 = load i32, i32* %delayed_error, align 8, !dbg !954
  %tobool = icmp ne i32 %1, 0, !dbg !952
  br i1 %tobool, label %if.then, label %if.end, !dbg !955

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !956
  %delayed_error1 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %2, i32 0, i32 17, !dbg !957
  %3 = load i32, i32* %delayed_error1, align 8, !dbg !957
  store i32 %3, i32* %retval, align 4, !dbg !958
  br label %return, !dbg !958

if.end:                                           ; preds = %entry
  %4 = load i32, i32* @uv_tcp_listen.single_accept, align 4, !dbg !959
  %cmp = icmp eq i32 %4, -1, !dbg !961
  br i1 %cmp, label %if.then2, label %if.end6, !dbg !962

if.then2:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i8** %val, metadata !963, metadata !493), !dbg !967
  %call = call i8* @getenv(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.2, i32 0, i32 0)) #7, !dbg !968
  store i8* %call, i8** %val, align 8, !dbg !967
  %5 = load i8*, i8** %val, align 8, !dbg !969
  %cmp3 = icmp ne i8* %5, null, !dbg !970
  br i1 %cmp3, label %land.rhs, label %land.end, !dbg !971

land.rhs:                                         ; preds = %if.then2
  %6 = load i8*, i8** %val, align 8, !dbg !972
  %call4 = call i32 @atoi(i8* %6) #9, !dbg !974
  %cmp5 = icmp ne i32 %call4, 0, !dbg !975
  br label %land.end

land.end:                                         ; preds = %land.rhs, %if.then2
  %7 = phi i1 [ false, %if.then2 ], [ %cmp5, %land.rhs ]
  %land.ext = zext i1 %7 to i32, !dbg !976
  store i32 %land.ext, i32* @uv_tcp_listen.single_accept, align 4, !dbg !978
  br label %if.end6, !dbg !979

if.end6:                                          ; preds = %land.end, %if.end
  %8 = load i32, i32* @uv_tcp_listen.single_accept, align 4, !dbg !980
  %tobool7 = icmp ne i32 %8, 0, !dbg !980
  br i1 %tobool7, label %if.then8, label %if.end9, !dbg !982

if.then8:                                         ; preds = %if.end6
  %9 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !983
  %flags = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %9, i32 0, i32 7, !dbg !984
  %10 = load i32, i32* %flags, align 8, !dbg !985
  %or = or i32 %10, 4096, !dbg !985
  store i32 %or, i32* %flags, align 8, !dbg !985
  br label %if.end9, !dbg !983

if.end9:                                          ; preds = %if.then8, %if.end6
  %11 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !986
  %call10 = call i32 @maybe_new_socket(%struct.uv_tcp_s* %11, i32 2, i32 32), !dbg !987
  store i32 %call10, i32* %err, align 4, !dbg !988
  %12 = load i32, i32* %err, align 4, !dbg !989
  %tobool11 = icmp ne i32 %12, 0, !dbg !989
  br i1 %tobool11, label %if.then12, label %if.end13, !dbg !991

if.then12:                                        ; preds = %if.end9
  %13 = load i32, i32* %err, align 4, !dbg !992
  store i32 %13, i32* %retval, align 4, !dbg !993
  br label %return, !dbg !993

if.end13:                                         ; preds = %if.end9
  %14 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !994
  %io_watcher = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %14, i32 0, i32 13, !dbg !996
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !997
  %15 = load i32, i32* %fd, align 8, !dbg !997
  %16 = load i32, i32* %backlog.addr, align 4, !dbg !998
  %call14 = call i32 @listen(i32 %15, i32 %16) #7, !dbg !999
  %tobool15 = icmp ne i32 %call14, 0, !dbg !999
  br i1 %tobool15, label %if.then16, label %if.end18, !dbg !1000

if.then16:                                        ; preds = %if.end13
  %call17 = call i32* @__errno_location() #1, !dbg !1001
  %17 = load i32, i32* %call17, align 4, !dbg !1001
  %sub = sub nsw i32 0, %17, !dbg !1002
  store i32 %sub, i32* %retval, align 4, !dbg !1003
  br label %return, !dbg !1003

if.end18:                                         ; preds = %if.end13
  %18 = load void (%struct.uv_stream_s*, i32)*, void (%struct.uv_stream_s*, i32)** %cb.addr, align 8, !dbg !1004
  %19 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !1005
  %connection_cb = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %19, i32 0, i32 16, !dbg !1006
  store void (%struct.uv_stream_s*, i32)* %18, void (%struct.uv_stream_s*, i32)** %connection_cb, align 8, !dbg !1007
  %20 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !1008
  %flags19 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %20, i32 0, i32 7, !dbg !1009
  %21 = load i32, i32* %flags19, align 8, !dbg !1010
  %or20 = or i32 %21, 262144, !dbg !1010
  store i32 %or20, i32* %flags19, align 8, !dbg !1010
  %22 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !1011
  %io_watcher21 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %22, i32 0, i32 13, !dbg !1012
  %cb22 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher21, i32 0, i32 0, !dbg !1013
  store void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* @uv__server_io, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)** %cb22, align 8, !dbg !1014
  %23 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !1015
  %loop = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %23, i32 0, i32 1, !dbg !1016
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1016
  %25 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %tcp.addr, align 8, !dbg !1017
  %io_watcher23 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %25, i32 0, i32 13, !dbg !1018
  call void @uv__io_start(%struct.uv_loop_s* %24, %struct.uv__io_s* %io_watcher23, i32 1), !dbg !1019
  store i32 0, i32* %retval, align 4, !dbg !1020
  br label %return, !dbg !1020

return:                                           ; preds = %if.end18, %if.then16, %if.then12, %if.then
  %26 = load i32, i32* %retval, align 4, !dbg !1021
  ret i32 %26, !dbg !1021
}

; Function Attrs: nounwind
declare i8* @getenv(i8*) #3

; Function Attrs: nounwind readonly
declare i32 @atoi(i8*) #6

; Function Attrs: nounwind
declare i32 @listen(i32, i32) #3

declare void @uv__server_io(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

; Function Attrs: nounwind uwtable
define i32 @uv__tcp_nodelay(i32 %fd, i32 %on) #0 !dbg !468 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %on.addr = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1022, metadata !493), !dbg !1023
  store i32 %on, i32* %on.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %on.addr, metadata !1024, metadata !493), !dbg !1025
  %0 = load i32, i32* %fd.addr, align 4, !dbg !1026
  %1 = bitcast i32* %on.addr to i8*, !dbg !1028
  %call = call i32 @setsockopt(i32 %0, i32 6, i32 1, i8* %1, i32 4) #7, !dbg !1029
  %tobool = icmp ne i32 %call, 0, !dbg !1029
  br i1 %tobool, label %if.then, label %if.end, !dbg !1030

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !1031
  %2 = load i32, i32* %call1, align 4, !dbg !1031
  %sub = sub nsw i32 0, %2, !dbg !1032
  store i32 %sub, i32* %retval, align 4, !dbg !1033
  br label %return, !dbg !1033

if.end:                                           ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1034
  br label %return, !dbg !1034

return:                                           ; preds = %if.end, %if.then
  %3 = load i32, i32* %retval, align 4, !dbg !1035
  ret i32 %3, !dbg !1035
}

; Function Attrs: nounwind uwtable
define i32 @uv__tcp_keepalive(i32 %fd, i32 %on, i32 %delay) #0 !dbg !471 {
entry:
  %retval = alloca i32, align 4
  %fd.addr = alloca i32, align 4
  %on.addr = alloca i32, align 4
  %delay.addr = alloca i32, align 4
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1036, metadata !493), !dbg !1037
  store i32 %on, i32* %on.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %on.addr, metadata !1038, metadata !493), !dbg !1039
  store i32 %delay, i32* %delay.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %delay.addr, metadata !1040, metadata !493), !dbg !1041
  %0 = load i32, i32* %fd.addr, align 4, !dbg !1042
  %1 = bitcast i32* %on.addr to i8*, !dbg !1044
  %call = call i32 @setsockopt(i32 %0, i32 1, i32 9, i8* %1, i32 4) #7, !dbg !1045
  %tobool = icmp ne i32 %call, 0, !dbg !1045
  br i1 %tobool, label %if.then, label %if.end, !dbg !1046

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !1047
  %2 = load i32, i32* %call1, align 4, !dbg !1047
  %sub = sub nsw i32 0, %2, !dbg !1048
  store i32 %sub, i32* %retval, align 4, !dbg !1049
  br label %return, !dbg !1049

if.end:                                           ; preds = %entry
  %3 = load i32, i32* %on.addr, align 4, !dbg !1050
  %tobool2 = icmp ne i32 %3, 0, !dbg !1050
  br i1 %tobool2, label %land.lhs.true, label %if.end8, !dbg !1052

land.lhs.true:                                    ; preds = %if.end
  %4 = load i32, i32* %fd.addr, align 4, !dbg !1053
  %5 = bitcast i32* %delay.addr to i8*, !dbg !1055
  %call3 = call i32 @setsockopt(i32 %4, i32 6, i32 4, i8* %5, i32 4) #7, !dbg !1056
  %tobool4 = icmp ne i32 %call3, 0, !dbg !1056
  br i1 %tobool4, label %if.then5, label %if.end8, !dbg !1057

if.then5:                                         ; preds = %land.lhs.true
  %call6 = call i32* @__errno_location() #1, !dbg !1058
  %6 = load i32, i32* %call6, align 4, !dbg !1058
  %sub7 = sub nsw i32 0, %6, !dbg !1059
  store i32 %sub7, i32* %retval, align 4, !dbg !1060
  br label %return, !dbg !1060

if.end8:                                          ; preds = %land.lhs.true, %if.end
  store i32 0, i32* %retval, align 4, !dbg !1061
  br label %return, !dbg !1061

return:                                           ; preds = %if.end8, %if.then5, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !1062
  ret i32 %7, !dbg !1062
}

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_nodelay(%struct.uv_tcp_s* %handle, i32 %on) #0 !dbg !474 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  %on.addr = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !1063, metadata !493), !dbg !1064
  store i32 %on, i32* %on.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %on.addr, metadata !1065, metadata !493), !dbg !1066
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1067, metadata !493), !dbg !1068
  %0 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1069
  %io_watcher = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %0, i32 0, i32 13, !dbg !1069
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1069
  %1 = load i32, i32* %fd, align 8, !dbg !1069
  %cmp = icmp ne i32 %1, -1, !dbg !1071
  br i1 %cmp, label %if.then, label %if.end4, !dbg !1072

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1073
  %io_watcher1 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %2, i32 0, i32 13, !dbg !1073
  %fd2 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher1, i32 0, i32 5, !dbg !1073
  %3 = load i32, i32* %fd2, align 8, !dbg !1073
  %4 = load i32, i32* %on.addr, align 4, !dbg !1075
  %call = call i32 @uv__tcp_nodelay(i32 %3, i32 %4), !dbg !1076
  store i32 %call, i32* %err, align 4, !dbg !1077
  %5 = load i32, i32* %err, align 4, !dbg !1078
  %tobool = icmp ne i32 %5, 0, !dbg !1078
  br i1 %tobool, label %if.then3, label %if.end, !dbg !1080

if.then3:                                         ; preds = %if.then
  %6 = load i32, i32* %err, align 4, !dbg !1081
  store i32 %6, i32* %retval, align 4, !dbg !1082
  br label %return, !dbg !1082

if.end:                                           ; preds = %if.then
  br label %if.end4, !dbg !1083

if.end4:                                          ; preds = %if.end, %entry
  %7 = load i32, i32* %on.addr, align 4, !dbg !1084
  %tobool5 = icmp ne i32 %7, 0, !dbg !1084
  br i1 %tobool5, label %if.then6, label %if.else, !dbg !1086

if.then6:                                         ; preds = %if.end4
  %8 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1087
  %flags = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %8, i32 0, i32 7, !dbg !1088
  %9 = load i32, i32* %flags, align 8, !dbg !1089
  %or = or i32 %9, 1024, !dbg !1089
  store i32 %or, i32* %flags, align 8, !dbg !1089
  br label %if.end8, !dbg !1087

if.else:                                          ; preds = %if.end4
  %10 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1090
  %flags7 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %10, i32 0, i32 7, !dbg !1091
  %11 = load i32, i32* %flags7, align 8, !dbg !1092
  %and = and i32 %11, -1025, !dbg !1092
  store i32 %and, i32* %flags7, align 8, !dbg !1092
  br label %if.end8

if.end8:                                          ; preds = %if.else, %if.then6
  store i32 0, i32* %retval, align 4, !dbg !1093
  br label %return, !dbg !1093

return:                                           ; preds = %if.end8, %if.then3
  %12 = load i32, i32* %retval, align 4, !dbg !1094
  ret i32 %12, !dbg !1094
}

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_keepalive(%struct.uv_tcp_s* %handle, i32 %on, i32 %delay) #0 !dbg !477 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  %on.addr = alloca i32, align 4
  %delay.addr = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !1095, metadata !493), !dbg !1096
  store i32 %on, i32* %on.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %on.addr, metadata !1097, metadata !493), !dbg !1098
  store i32 %delay, i32* %delay.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %delay.addr, metadata !1099, metadata !493), !dbg !1100
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1101, metadata !493), !dbg !1102
  %0 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1103
  %io_watcher = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %0, i32 0, i32 13, !dbg !1103
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1103
  %1 = load i32, i32* %fd, align 8, !dbg !1103
  %cmp = icmp ne i32 %1, -1, !dbg !1105
  br i1 %cmp, label %if.then, label %if.end4, !dbg !1106

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1107
  %io_watcher1 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %2, i32 0, i32 13, !dbg !1107
  %fd2 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher1, i32 0, i32 5, !dbg !1107
  %3 = load i32, i32* %fd2, align 8, !dbg !1107
  %4 = load i32, i32* %on.addr, align 4, !dbg !1109
  %5 = load i32, i32* %delay.addr, align 4, !dbg !1110
  %call = call i32 @uv__tcp_keepalive(i32 %3, i32 %4, i32 %5), !dbg !1111
  store i32 %call, i32* %err, align 4, !dbg !1112
  %6 = load i32, i32* %err, align 4, !dbg !1113
  %tobool = icmp ne i32 %6, 0, !dbg !1113
  br i1 %tobool, label %if.then3, label %if.end, !dbg !1115

if.then3:                                         ; preds = %if.then
  %7 = load i32, i32* %err, align 4, !dbg !1116
  store i32 %7, i32* %retval, align 4, !dbg !1117
  br label %return, !dbg !1117

if.end:                                           ; preds = %if.then
  br label %if.end4, !dbg !1118

if.end4:                                          ; preds = %if.end, %entry
  %8 = load i32, i32* %on.addr, align 4, !dbg !1119
  %tobool5 = icmp ne i32 %8, 0, !dbg !1119
  br i1 %tobool5, label %if.then6, label %if.else, !dbg !1121

if.then6:                                         ; preds = %if.end4
  %9 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1122
  %flags = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %9, i32 0, i32 7, !dbg !1123
  %10 = load i32, i32* %flags, align 8, !dbg !1124
  %or = or i32 %10, 2048, !dbg !1124
  store i32 %or, i32* %flags, align 8, !dbg !1124
  br label %if.end8, !dbg !1122

if.else:                                          ; preds = %if.end4
  %11 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1125
  %flags7 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %11, i32 0, i32 7, !dbg !1126
  %12 = load i32, i32* %flags7, align 8, !dbg !1127
  %and = and i32 %12, -2049, !dbg !1127
  store i32 %and, i32* %flags7, align 8, !dbg !1127
  br label %if.end8

if.end8:                                          ; preds = %if.else, %if.then6
  store i32 0, i32* %retval, align 4, !dbg !1128
  br label %return, !dbg !1128

return:                                           ; preds = %if.end8, %if.then3
  %13 = load i32, i32* %retval, align 4, !dbg !1129
  ret i32 %13, !dbg !1129
}

; Function Attrs: nounwind uwtable
define i32 @uv_tcp_simultaneous_accepts(%struct.uv_tcp_s* %handle, i32 %enable) #0 !dbg !480 {
entry:
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  %enable.addr = alloca i32, align 4
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !1130, metadata !493), !dbg !1131
  store i32 %enable, i32* %enable.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %enable.addr, metadata !1132, metadata !493), !dbg !1133
  %0 = load i32, i32* %enable.addr, align 4, !dbg !1134
  %tobool = icmp ne i32 %0, 0, !dbg !1134
  br i1 %tobool, label %if.then, label %if.else, !dbg !1136

if.then:                                          ; preds = %entry
  %1 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1137
  %flags = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %1, i32 0, i32 7, !dbg !1138
  %2 = load i32, i32* %flags, align 8, !dbg !1139
  %and = and i32 %2, -4097, !dbg !1139
  store i32 %and, i32* %flags, align 8, !dbg !1139
  br label %if.end, !dbg !1137

if.else:                                          ; preds = %entry
  %3 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1140
  %flags1 = getelementptr inbounds %struct.uv_tcp_s, %struct.uv_tcp_s* %3, i32 0, i32 7, !dbg !1141
  %4 = load i32, i32* %flags1, align 8, !dbg !1142
  %or = or i32 %4, 4096, !dbg !1142
  store i32 %or, i32* %flags1, align 8, !dbg !1142
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret i32 0, !dbg !1143
}

; Function Attrs: nounwind uwtable
define void @uv__tcp_close(%struct.uv_tcp_s* %handle) #0 !dbg !481 {
entry:
  %handle.addr = alloca %struct.uv_tcp_s*, align 8
  store %struct.uv_tcp_s* %handle, %struct.uv_tcp_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_tcp_s** %handle.addr, metadata !1144, metadata !493), !dbg !1145
  %0 = load %struct.uv_tcp_s*, %struct.uv_tcp_s** %handle.addr, align 8, !dbg !1146
  %1 = bitcast %struct.uv_tcp_s* %0 to %struct.uv_stream_s*, !dbg !1147
  call void @uv__stream_close(%struct.uv_stream_s* %1), !dbg !1148
  ret void, !dbg !1149
}

declare void @uv__stream_close(%struct.uv_stream_s*) #2

declare i32 @uv__socket(i32, i32, i32) #2

declare i32 @uv__close(i32) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { noreturn nounwind }
attributes #9 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!489, !490}
!llvm.ident = !{!491}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !100, subprograms: !399, globals: !487)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/tcp.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !38, !41, !60, !88}
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
!38 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "uv_tcp_flags", file: !4, line: 531, size: 32, align: 32, elements: !39)
!39 = !{!40}
!40 = !DIEnumerator(name: "UV_TCP_IPV6ONLY", value: 1)
!41 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !42, line: 124, size: 32, align: 32, elements: !43)
!42 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!43 = !{!44, !45, !46, !47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57, !58, !59}
!44 = !DIEnumerator(name: "UV_CLOSING", value: 1)
!45 = !DIEnumerator(name: "UV_CLOSED", value: 2)
!46 = !DIEnumerator(name: "UV_STREAM_READING", value: 4)
!47 = !DIEnumerator(name: "UV_STREAM_SHUTTING", value: 8)
!48 = !DIEnumerator(name: "UV_STREAM_SHUT", value: 16)
!49 = !DIEnumerator(name: "UV_STREAM_READABLE", value: 32)
!50 = !DIEnumerator(name: "UV_STREAM_WRITABLE", value: 64)
!51 = !DIEnumerator(name: "UV_STREAM_BLOCKING", value: 128)
!52 = !DIEnumerator(name: "UV_STREAM_READ_PARTIAL", value: 256)
!53 = !DIEnumerator(name: "UV_STREAM_READ_EOF", value: 512)
!54 = !DIEnumerator(name: "UV_TCP_NODELAY", value: 1024)
!55 = !DIEnumerator(name: "UV_TCP_KEEPALIVE", value: 2048)
!56 = !DIEnumerator(name: "UV_TCP_SINGLE_ACCEPT", value: 4096)
!57 = !DIEnumerator(name: "UV_HANDLE_IPV6", value: 65536)
!58 = !DIEnumerator(name: "UV_UDP_PROCESSING", value: 131072)
!59 = !DIEnumerator(name: "UV_HANDLE_BOUND", value: 262144)
!60 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !61, line: 40, size: 32, align: 32, elements: !62)
!61 = !DIFile(filename: "/usr/include/netinet/in.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!62 = !{!63, !64, !65, !66, !67, !68, !69, !70, !71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87}
!63 = !DIEnumerator(name: "IPPROTO_IP", value: 0)
!64 = !DIEnumerator(name: "IPPROTO_ICMP", value: 1)
!65 = !DIEnumerator(name: "IPPROTO_IGMP", value: 2)
!66 = !DIEnumerator(name: "IPPROTO_IPIP", value: 4)
!67 = !DIEnumerator(name: "IPPROTO_TCP", value: 6)
!68 = !DIEnumerator(name: "IPPROTO_EGP", value: 8)
!69 = !DIEnumerator(name: "IPPROTO_PUP", value: 12)
!70 = !DIEnumerator(name: "IPPROTO_UDP", value: 17)
!71 = !DIEnumerator(name: "IPPROTO_IDP", value: 22)
!72 = !DIEnumerator(name: "IPPROTO_TP", value: 29)
!73 = !DIEnumerator(name: "IPPROTO_DCCP", value: 33)
!74 = !DIEnumerator(name: "IPPROTO_IPV6", value: 41)
!75 = !DIEnumerator(name: "IPPROTO_RSVP", value: 46)
!76 = !DIEnumerator(name: "IPPROTO_GRE", value: 47)
!77 = !DIEnumerator(name: "IPPROTO_ESP", value: 50)
!78 = !DIEnumerator(name: "IPPROTO_AH", value: 51)
!79 = !DIEnumerator(name: "IPPROTO_MTP", value: 92)
!80 = !DIEnumerator(name: "IPPROTO_BEETPH", value: 94)
!81 = !DIEnumerator(name: "IPPROTO_ENCAP", value: 98)
!82 = !DIEnumerator(name: "IPPROTO_PIM", value: 103)
!83 = !DIEnumerator(name: "IPPROTO_COMP", value: 108)
!84 = !DIEnumerator(name: "IPPROTO_SCTP", value: 132)
!85 = !DIEnumerator(name: "IPPROTO_UDPLITE", value: 136)
!86 = !DIEnumerator(name: "IPPROTO_RAW", value: 255)
!87 = !DIEnumerator(name: "IPPROTO_MAX", value: 256)
!88 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !89, line: 24, size: 32, align: 32, elements: !90)
!89 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!90 = !{!91, !92, !93, !94, !95, !96, !97, !98, !99}
!91 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!92 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!93 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!94 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!95 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!96 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!97 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!98 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!99 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!100 = !{!101, !392, !106, !396, !124}
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stream_t", file: !4, line: 206, baseType: !103)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_stream_s", file: !4, line: 465, size: 1984, align: 64, elements: !104)
!104 = !{!105, !107, !313, !314, !315, !316, !321, !322, !323, !326, !338, !349, !366, !381, !382, !383, !384, !389, !390, !391}
!105 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !103, file: !4, line: 466, baseType: !106, size: 64, align: 64)
!106 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !103, file: !4, line: 466, baseType: !108, size: 64, align: 64, offset: 64)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !110)
!110 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !111)
!111 = !{!112, !113, !115, !119, !120, !121, !123, !125, !126, !127, !146, !147, !148, !149, !180, !228, !252, !253, !254, !255, !256, !257, !258, !262, !263, !264, !269, !272, !273, !275, !276, !309, !310, !311, !312}
!112 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !110, file: !4, line: 1475, baseType: !106, size: 64, align: 64)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !110, file: !4, line: 1477, baseType: !114, size: 32, align: 32, offset: 64)
!114 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !110, file: !4, line: 1478, baseType: !116, size: 128, align: 64, offset: 128)
!116 = !DICompositeType(tag: DW_TAG_array_type, baseType: !106, size: 128, align: 64, elements: !117)
!117 = !{!118}
!118 = !DISubrange(count: 2)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !110, file: !4, line: 1479, baseType: !116, size: 128, align: 64, offset: 256)
!120 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !110, file: !4, line: 1481, baseType: !114, size: 32, align: 32, offset: 384)
!121 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !110, file: !4, line: 1482, baseType: !122, size: 64, align: 64, offset: 448)
!122 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !110, file: !4, line: 1482, baseType: !124, size: 32, align: 32, offset: 512)
!124 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !110, file: !4, line: 1482, baseType: !116, size: 128, align: 64, offset: 576)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !110, file: !4, line: 1482, baseType: !116, size: 128, align: 64, offset: 704)
!127 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !110, file: !4, line: 1482, baseType: !128, size: 64, align: 64, offset: 832)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !129, size: 64, align: 64)
!129 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !130, size: 64, align: 64)
!130 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !131, line: 87, baseType: !132)
!131 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!132 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !131, line: 89, size: 448, align: 64, elements: !133)
!133 = !{!134, !141, !142, !143, !144, !145}
!134 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !132, file: !131, line: 90, baseType: !135, size: 64, align: 64)
!135 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !131, line: 84, baseType: !136)
!136 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !137, size: 64, align: 64)
!137 = !DISubroutineType(types: !138)
!138 = !{null, !139, !140, !114}
!139 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !110, size: 64, align: 64)
!140 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !132, file: !131, line: 91, baseType: !116, size: 128, align: 64, offset: 64)
!142 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !132, file: !131, line: 92, baseType: !116, size: 128, align: 64, offset: 192)
!143 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !132, file: !131, line: 93, baseType: !114, size: 32, align: 32, offset: 320)
!144 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !132, file: !131, line: 94, baseType: !114, size: 32, align: 32, offset: 352)
!145 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !132, file: !131, line: 95, baseType: !124, size: 32, align: 32, offset: 384)
!146 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !110, file: !4, line: 1482, baseType: !114, size: 32, align: 32, offset: 896)
!147 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !110, file: !4, line: 1482, baseType: !114, size: 32, align: 32, offset: 928)
!148 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !110, file: !4, line: 1482, baseType: !116, size: 128, align: 64, offset: 960)
!149 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !110, file: !4, line: 1482, baseType: !150, size: 320, align: 64, offset: 1088)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !131, line: 129, baseType: !151)
!151 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !152, line: 127, baseType: !153)
!152 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!153 = !DICompositeType(tag: DW_TAG_union_type, file: !152, line: 90, size: 320, align: 64, elements: !154)
!154 = !{!155, !173, !178}
!155 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !153, file: !152, line: 124, baseType: !156, size: 320, align: 64)
!156 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !152, line: 92, size: 320, align: 64, elements: !157)
!157 = !{!158, !159, !160, !161, !162, !163, !165, !166}
!158 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !156, file: !152, line: 94, baseType: !124, size: 32, align: 32)
!159 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !156, file: !152, line: 95, baseType: !114, size: 32, align: 32, offset: 32)
!160 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !156, file: !152, line: 96, baseType: !124, size: 32, align: 32, offset: 64)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !156, file: !152, line: 98, baseType: !114, size: 32, align: 32, offset: 96)
!162 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !156, file: !152, line: 102, baseType: !124, size: 32, align: 32, offset: 128)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !156, file: !152, line: 104, baseType: !164, size: 16, align: 16, offset: 160)
!164 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !156, file: !152, line: 105, baseType: !164, size: 16, align: 16, offset: 176)
!166 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !156, file: !152, line: 106, baseType: !167, size: 128, align: 64, offset: 192)
!167 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !152, line: 79, baseType: !168)
!168 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !152, line: 75, size: 128, align: 64, elements: !169)
!169 = !{!170, !172}
!170 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !168, file: !152, line: 77, baseType: !171, size: 64, align: 64)
!171 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !168, size: 64, align: 64)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !168, file: !152, line: 78, baseType: !171, size: 64, align: 64, offset: 64)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !153, file: !152, line: 125, baseType: !174, size: 320, align: 8)
!174 = !DICompositeType(tag: DW_TAG_array_type, baseType: !175, size: 320, align: 8, elements: !176)
!175 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!176 = !{!177}
!177 = !DISubrange(count: 40)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !153, file: !152, line: 126, baseType: !179, size: 64, align: 64)
!179 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !110, file: !4, line: 1482, baseType: !181, size: 1024, align: 64, offset: 1408)
!181 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !182)
!182 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !183)
!183 = !{!184, !185, !186, !188, !212, !213, !218, !219, !220, !226, !227}
!184 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !182, file: !4, line: 768, baseType: !106, size: 64, align: 64)
!185 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !182, file: !4, line: 768, baseType: !108, size: 64, align: 64, offset: 64)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !182, file: !4, line: 768, baseType: !187, size: 32, align: 32, offset: 128)
!187 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!188 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !182, file: !4, line: 768, baseType: !189, size: 64, align: 64, offset: 192)
!189 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !190)
!190 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !191, size: 64, align: 64)
!191 = !DISubroutineType(types: !192)
!192 = !{null, !193}
!193 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !194, size: 64, align: 64)
!194 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !195)
!195 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !196)
!196 = !{!197, !198, !199, !200, !201, !202, !210, !211}
!197 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !195, file: !4, line: 426, baseType: !106, size: 64, align: 64)
!198 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !195, file: !4, line: 426, baseType: !108, size: 64, align: 64, offset: 64)
!199 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !195, file: !4, line: 426, baseType: !187, size: 32, align: 32, offset: 128)
!200 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !195, file: !4, line: 426, baseType: !189, size: 64, align: 64, offset: 192)
!201 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !195, file: !4, line: 426, baseType: !116, size: 128, align: 64, offset: 256)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !195, file: !4, line: 426, baseType: !203, size: 256, align: 64, offset: 384)
!203 = !DICompositeType(tag: DW_TAG_union_type, scope: !195, file: !4, line: 426, size: 256, align: 64, elements: !204)
!204 = !{!205, !206}
!205 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !203, file: !4, line: 426, baseType: !124, size: 32, align: 32)
!206 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !203, file: !4, line: 426, baseType: !207, size: 256, align: 64)
!207 = !DICompositeType(tag: DW_TAG_array_type, baseType: !106, size: 256, align: 64, elements: !208)
!208 = !{!209}
!209 = !DISubrange(count: 4)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !195, file: !4, line: 426, baseType: !193, size: 64, align: 64, offset: 640)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !195, file: !4, line: 426, baseType: !114, size: 32, align: 32, offset: 704)
!212 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !182, file: !4, line: 768, baseType: !116, size: 128, align: 64, offset: 256)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !182, file: !4, line: 768, baseType: !214, size: 256, align: 64, offset: 384)
!214 = !DICompositeType(tag: DW_TAG_union_type, scope: !182, file: !4, line: 768, size: 256, align: 64, elements: !215)
!215 = !{!216, !217}
!216 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !214, file: !4, line: 768, baseType: !124, size: 32, align: 32)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !214, file: !4, line: 768, baseType: !207, size: 256, align: 64)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !182, file: !4, line: 768, baseType: !193, size: 64, align: 64, offset: 640)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !182, file: !4, line: 768, baseType: !114, size: 32, align: 32, offset: 704)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !182, file: !4, line: 769, baseType: !221, size: 64, align: 64, offset: 768)
!221 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !222)
!222 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !223, size: 64, align: 64)
!223 = !DISubroutineType(types: !224)
!224 = !{null, !225}
!225 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !181, size: 64, align: 64)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !182, file: !4, line: 769, baseType: !116, size: 128, align: 64, offset: 832)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !182, file: !4, line: 769, baseType: !124, size: 32, align: 32, offset: 960)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !110, file: !4, line: 1482, baseType: !229, size: 448, align: 64, offset: 2432)
!229 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !131, line: 130, baseType: !230)
!230 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !152, line: 213, baseType: !231)
!231 = !DICompositeType(tag: DW_TAG_union_type, file: !152, line: 173, size: 448, align: 64, elements: !232)
!232 = !{!233, !247, !251}
!233 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !231, file: !152, line: 192, baseType: !234, size: 448, align: 64)
!234 = !DICompositeType(tag: DW_TAG_structure_type, scope: !231, file: !152, line: 176, size: 448, align: 64, elements: !235)
!235 = !{!236, !237, !238, !239, !240, !241, !242, !243, !244, !245, !246}
!236 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !234, file: !152, line: 178, baseType: !124, size: 32, align: 32)
!237 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !234, file: !152, line: 179, baseType: !114, size: 32, align: 32, offset: 32)
!238 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !234, file: !152, line: 180, baseType: !114, size: 32, align: 32, offset: 64)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !234, file: !152, line: 181, baseType: !114, size: 32, align: 32, offset: 96)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !234, file: !152, line: 182, baseType: !114, size: 32, align: 32, offset: 128)
!241 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !234, file: !152, line: 183, baseType: !114, size: 32, align: 32, offset: 160)
!242 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !234, file: !152, line: 184, baseType: !124, size: 32, align: 32, offset: 192)
!243 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !234, file: !152, line: 185, baseType: !124, size: 32, align: 32, offset: 224)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !234, file: !152, line: 186, baseType: !122, size: 64, align: 64, offset: 256)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !234, file: !152, line: 187, baseType: !122, size: 64, align: 64, offset: 320)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !234, file: !152, line: 190, baseType: !114, size: 32, align: 32, offset: 384)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !231, file: !152, line: 211, baseType: !248, size: 448, align: 8)
!248 = !DICompositeType(tag: DW_TAG_array_type, baseType: !175, size: 448, align: 8, elements: !249)
!249 = !{!250}
!250 = !DISubrange(count: 56)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !231, file: !152, line: 212, baseType: !179, size: 64, align: 64)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !110, file: !4, line: 1482, baseType: !193, size: 64, align: 64, offset: 2880)
!253 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !110, file: !4, line: 1482, baseType: !116, size: 128, align: 64, offset: 2944)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !110, file: !4, line: 1482, baseType: !116, size: 128, align: 64, offset: 3072)
!255 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !110, file: !4, line: 1482, baseType: !116, size: 128, align: 64, offset: 3200)
!256 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !110, file: !4, line: 1482, baseType: !116, size: 128, align: 64, offset: 3328)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !110, file: !4, line: 1482, baseType: !116, size: 128, align: 64, offset: 3456)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !110, file: !4, line: 1482, baseType: !259, size: 64, align: 64, offset: 3584)
!259 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !260, size: 64, align: 64)
!260 = !DISubroutineType(types: !261)
!261 = !{null}
!262 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !110, file: !4, line: 1482, baseType: !130, size: 448, align: 64, offset: 3648)
!263 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !110, file: !4, line: 1482, baseType: !124, size: 32, align: 32, offset: 4096)
!264 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !110, file: !4, line: 1482, baseType: !265, size: 128, align: 64, offset: 4160)
!265 = !DICompositeType(tag: DW_TAG_structure_type, scope: !110, file: !4, line: 1482, size: 128, align: 64, elements: !266)
!266 = !{!267, !268}
!267 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !265, file: !4, line: 1482, baseType: !106, size: 64, align: 64)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !265, file: !4, line: 1482, baseType: !114, size: 32, align: 32, offset: 64)
!269 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !110, file: !4, line: 1482, baseType: !270, size: 64, align: 64, offset: 4288)
!270 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !271, line: 55, baseType: !122)
!271 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!272 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !110, file: !4, line: 1482, baseType: !270, size: 64, align: 64, offset: 4352)
!273 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !110, file: !4, line: 1482, baseType: !274, size: 64, align: 32, offset: 4416)
!274 = !DICompositeType(tag: DW_TAG_array_type, baseType: !124, size: 64, align: 32, elements: !117)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !110, file: !4, line: 1482, baseType: !130, size: 448, align: 64, offset: 4480)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !110, file: !4, line: 1482, baseType: !277, size: 1216, align: 64, offset: 4928)
!277 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !278)
!278 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !279)
!279 = !{!280, !281, !282, !283, !284, !285, !290, !291, !292, !298, !299, !307, !308}
!280 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !278, file: !4, line: 1326, baseType: !106, size: 64, align: 64)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !278, file: !4, line: 1326, baseType: !108, size: 64, align: 64, offset: 64)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !278, file: !4, line: 1326, baseType: !187, size: 32, align: 32, offset: 128)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !278, file: !4, line: 1326, baseType: !189, size: 64, align: 64, offset: 192)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !278, file: !4, line: 1326, baseType: !116, size: 128, align: 64, offset: 256)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !278, file: !4, line: 1326, baseType: !286, size: 256, align: 64, offset: 384)
!286 = !DICompositeType(tag: DW_TAG_union_type, scope: !278, file: !4, line: 1326, size: 256, align: 64, elements: !287)
!287 = !{!288, !289}
!288 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !286, file: !4, line: 1326, baseType: !124, size: 32, align: 32)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !286, file: !4, line: 1326, baseType: !207, size: 256, align: 64)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !278, file: !4, line: 1326, baseType: !193, size: 64, align: 64, offset: 640)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !278, file: !4, line: 1326, baseType: !114, size: 32, align: 32, offset: 704)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !278, file: !4, line: 1327, baseType: !293, size: 64, align: 64, offset: 768)
!293 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !294)
!294 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !295, size: 64, align: 64)
!295 = !DISubroutineType(types: !296)
!296 = !{null, !297, !124}
!297 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !277, size: 64, align: 64)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !278, file: !4, line: 1328, baseType: !124, size: 32, align: 32, offset: 832)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !278, file: !4, line: 1329, baseType: !300, size: 256, align: 64, offset: 896)
!300 = !DICompositeType(tag: DW_TAG_structure_type, scope: !278, file: !4, line: 1329, size: 256, align: 64, elements: !301)
!301 = !{!302, !304, !305, !306}
!302 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !300, file: !4, line: 1329, baseType: !303, size: 64, align: 64)
!303 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !278, size: 64, align: 64)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !300, file: !4, line: 1329, baseType: !303, size: 64, align: 64, offset: 64)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !300, file: !4, line: 1329, baseType: !303, size: 64, align: 64, offset: 128)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !300, file: !4, line: 1329, baseType: !124, size: 32, align: 32, offset: 192)
!307 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !278, file: !4, line: 1329, baseType: !114, size: 32, align: 32, offset: 1152)
!308 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !278, file: !4, line: 1329, baseType: !114, size: 32, align: 32, offset: 1184)
!309 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !110, file: !4, line: 1482, baseType: !124, size: 32, align: 32, offset: 6144)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !110, file: !4, line: 1482, baseType: !130, size: 448, align: 64, offset: 6208)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !110, file: !4, line: 1482, baseType: !106, size: 64, align: 64, offset: 6656)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !110, file: !4, line: 1482, baseType: !124, size: 32, align: 32, offset: 6720)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !103, file: !4, line: 466, baseType: !187, size: 32, align: 32, offset: 128)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !103, file: !4, line: 466, baseType: !189, size: 64, align: 64, offset: 192)
!315 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !103, file: !4, line: 466, baseType: !116, size: 128, align: 64, offset: 256)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !103, file: !4, line: 466, baseType: !317, size: 256, align: 64, offset: 384)
!317 = !DICompositeType(tag: DW_TAG_union_type, scope: !103, file: !4, line: 466, size: 256, align: 64, elements: !318)
!318 = !{!319, !320}
!319 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !317, file: !4, line: 466, baseType: !124, size: 32, align: 32)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !317, file: !4, line: 466, baseType: !207, size: 256, align: 64)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !103, file: !4, line: 466, baseType: !193, size: 64, align: 64, offset: 640)
!322 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !103, file: !4, line: 466, baseType: !114, size: 32, align: 32, offset: 704)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !103, file: !4, line: 467, baseType: !324, size: 64, align: 64, offset: 768)
!324 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !325, line: 62, baseType: !122)
!325 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!326 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !103, file: !4, line: 467, baseType: !327, size: 64, align: 64, offset: 832)
!327 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_alloc_cb", file: !4, line: 296, baseType: !328)
!328 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !329, size: 64, align: 64)
!329 = !DISubroutineType(types: !330)
!330 = !{null, !193, !324, !331}
!331 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !332, size: 64, align: 64)
!332 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !131, line: 119, baseType: !333)
!333 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !131, line: 116, size: 128, align: 64, elements: !334)
!334 = !{!335, !337}
!335 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !333, file: !131, line: 117, baseType: !336, size: 64, align: 64)
!336 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !175, size: 64, align: 64)
!337 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !333, file: !131, line: 118, baseType: !324, size: 64, align: 64, offset: 64)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !103, file: !4, line: 467, baseType: !339, size: 64, align: 64, offset: 896)
!339 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_read_cb", file: !4, line: 299, baseType: !340)
!340 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !341, size: 64, align: 64)
!341 = !DISubroutineType(types: !342)
!342 = !{null, !101, !343, !347}
!343 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !344, line: 102, baseType: !345)
!344 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!345 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !346, line: 172, baseType: !179)
!346 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!347 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !348, size: 64, align: 64)
!348 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !332)
!349 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !103, file: !4, line: 467, baseType: !350, size: 64, align: 64, offset: 960)
!350 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !351, size: 64, align: 64)
!351 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_t", file: !4, line: 228, baseType: !352)
!352 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_connect_s", file: !4, line: 551, size: 768, align: 64, elements: !353)
!353 = !{!354, !355, !357, !358, !359, !364, !365}
!354 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !352, file: !4, line: 552, baseType: !106, size: 64, align: 64)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !352, file: !4, line: 552, baseType: !356, size: 32, align: 32, offset: 64)
!356 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !25)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !352, file: !4, line: 552, baseType: !116, size: 128, align: 64, offset: 128)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !352, file: !4, line: 552, baseType: !207, size: 256, align: 64, offset: 256)
!359 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !352, file: !4, line: 553, baseType: !360, size: 64, align: 64, offset: 512)
!360 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_cb", file: !4, line: 303, baseType: !361)
!361 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !362, size: 64, align: 64)
!362 = !DISubroutineType(types: !363)
!363 = !{null, !350, !124}
!364 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !352, file: !4, line: 554, baseType: !101, size: 64, align: 64, offset: 576)
!365 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !352, file: !4, line: 555, baseType: !116, size: 128, align: 64, offset: 640)
!366 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !103, file: !4, line: 467, baseType: !367, size: 64, align: 64, offset: 1024)
!367 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !368, size: 64, align: 64)
!368 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_t", file: !4, line: 226, baseType: !369)
!369 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_shutdown_s", file: !4, line: 401, size: 640, align: 64, elements: !370)
!370 = !{!371, !372, !373, !374, !375, !376}
!371 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !369, file: !4, line: 402, baseType: !106, size: 64, align: 64)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !369, file: !4, line: 402, baseType: !356, size: 32, align: 32, offset: 64)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !369, file: !4, line: 402, baseType: !116, size: 128, align: 64, offset: 128)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !369, file: !4, line: 402, baseType: !207, size: 256, align: 64, offset: 256)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !369, file: !4, line: 403, baseType: !101, size: 64, align: 64, offset: 512)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !369, file: !4, line: 404, baseType: !377, size: 64, align: 64, offset: 576)
!377 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_cb", file: !4, line: 304, baseType: !378)
!378 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !379, size: 64, align: 64)
!379 = !DISubroutineType(types: !380)
!380 = !{null, !367, !124}
!381 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !103, file: !4, line: 467, baseType: !130, size: 448, align: 64, offset: 1088)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !103, file: !4, line: 467, baseType: !116, size: 128, align: 64, offset: 1536)
!383 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !103, file: !4, line: 467, baseType: !116, size: 128, align: 64, offset: 1664)
!384 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !103, file: !4, line: 467, baseType: !385, size: 64, align: 64, offset: 1792)
!385 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connection_cb", file: !4, line: 305, baseType: !386)
!386 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !387, size: 64, align: 64)
!387 = !DISubroutineType(types: !388)
!388 = !{null, !101, !124}
!389 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !103, file: !4, line: 467, baseType: !124, size: 32, align: 32, offset: 1856)
!390 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !103, file: !4, line: 467, baseType: !124, size: 32, align: 32, offset: 1888)
!391 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !103, file: !4, line: 467, baseType: !106, size: 64, align: 64, offset: 1920)
!392 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !393, size: 64, align: 64)
!393 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !394, size: 64, align: 64)
!394 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !395, line: 21, baseType: !116)
!395 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!396 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !397, line: 33, baseType: !398)
!397 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!398 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !346, line: 189, baseType: !114)
!399 = !{!400, !432, !435, !450, !453, !457, !464, !465, !468, !471, !474, !477, !480, !481, !484}
!400 = distinct !DISubprogram(name: "uv_tcp_init_ex", scope: !1, file: !1, line: 55, type: !401, isLocal: false, isDefinition: true, scopeLine: 55, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!401 = !DISubroutineType(types: !402)
!402 = !{!124, !108, !403, !114}
!403 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !404, size: 64, align: 64)
!404 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_tcp_t", file: !4, line: 207, baseType: !405)
!405 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_tcp_s", file: !4, line: 516, size: 1984, align: 64, elements: !406)
!406 = !{!407, !408, !409, !410, !411, !412, !417, !418, !419, !420, !421, !422, !423, !424, !425, !426, !427, !428, !429, !430}
!407 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !405, file: !4, line: 517, baseType: !106, size: 64, align: 64)
!408 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !405, file: !4, line: 517, baseType: !108, size: 64, align: 64, offset: 64)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !405, file: !4, line: 517, baseType: !187, size: 32, align: 32, offset: 128)
!410 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !405, file: !4, line: 517, baseType: !189, size: 64, align: 64, offset: 192)
!411 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !405, file: !4, line: 517, baseType: !116, size: 128, align: 64, offset: 256)
!412 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !405, file: !4, line: 517, baseType: !413, size: 256, align: 64, offset: 384)
!413 = !DICompositeType(tag: DW_TAG_union_type, scope: !405, file: !4, line: 517, size: 256, align: 64, elements: !414)
!414 = !{!415, !416}
!415 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !413, file: !4, line: 517, baseType: !124, size: 32, align: 32)
!416 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !413, file: !4, line: 517, baseType: !207, size: 256, align: 64)
!417 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !405, file: !4, line: 517, baseType: !193, size: 64, align: 64, offset: 640)
!418 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !405, file: !4, line: 517, baseType: !114, size: 32, align: 32, offset: 704)
!419 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !405, file: !4, line: 518, baseType: !324, size: 64, align: 64, offset: 768)
!420 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !405, file: !4, line: 518, baseType: !327, size: 64, align: 64, offset: 832)
!421 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !405, file: !4, line: 518, baseType: !339, size: 64, align: 64, offset: 896)
!422 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !405, file: !4, line: 518, baseType: !350, size: 64, align: 64, offset: 960)
!423 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !405, file: !4, line: 518, baseType: !367, size: 64, align: 64, offset: 1024)
!424 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !405, file: !4, line: 518, baseType: !130, size: 448, align: 64, offset: 1088)
!425 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !405, file: !4, line: 518, baseType: !116, size: 128, align: 64, offset: 1536)
!426 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !405, file: !4, line: 518, baseType: !116, size: 128, align: 64, offset: 1664)
!427 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !405, file: !4, line: 518, baseType: !385, size: 64, align: 64, offset: 1792)
!428 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !405, file: !4, line: 518, baseType: !124, size: 32, align: 32, offset: 1856)
!429 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !405, file: !4, line: 518, baseType: !124, size: 32, align: 32, offset: 1888)
!430 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !405, file: !4, line: 518, baseType: !106, size: 64, align: 64, offset: 1920)
!431 = !{}
!432 = distinct !DISubprogram(name: "uv_tcp_init", scope: !1, file: !1, line: 84, type: !433, isLocal: false, isDefinition: true, scopeLine: 84, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!433 = !DISubroutineType(types: !434)
!434 = !{!124, !108, !403}
!435 = distinct !DISubprogram(name: "uv__tcp_bind", scope: !1, file: !1, line: 89, type: !436, isLocal: false, isDefinition: true, scopeLine: 92, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!436 = !DISubroutineType(types: !437)
!437 = !{!124, !403, !438, !114, !114}
!438 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !439, size: 64, align: 64)
!439 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !440)
!440 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !397, line: 149, size: 128, align: 16, elements: !441)
!441 = !{!442, !446}
!442 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !440, file: !397, line: 151, baseType: !443, size: 16, align: 16)
!443 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !444, line: 28, baseType: !445)
!444 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!445 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!446 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !440, file: !397, line: 152, baseType: !447, size: 112, align: 8, offset: 16)
!447 = !DICompositeType(tag: DW_TAG_array_type, baseType: !175, size: 112, align: 8, elements: !448)
!448 = !{!449}
!449 = !DISubrange(count: 14)
!450 = distinct !DISubprogram(name: "uv__tcp_connect", scope: !1, file: !1, line: 145, type: !451, isLocal: false, isDefinition: true, scopeLine: 149, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!451 = !DISubroutineType(types: !452)
!452 = !{!124, !350, !403, !438, !114, !360}
!453 = distinct !DISubprogram(name: "uv_tcp_open", scope: !1, file: !1, line: 204, type: !454, isLocal: false, isDefinition: true, scopeLine: 204, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!454 = !DISubroutineType(types: !455)
!455 = !{!124, !403, !456}
!456 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_os_sock_t", file: !131, line: 122, baseType: !124)
!457 = distinct !DISubprogram(name: "uv_tcp_getsockname", scope: !1, file: !1, line: 217, type: !458, isLocal: false, isDefinition: true, scopeLine: 219, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!458 = !DISubroutineType(types: !459)
!459 = !{!124, !460, !462, !463}
!460 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !461, size: 64, align: 64)
!461 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !404)
!462 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !440, size: 64, align: 64)
!463 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!464 = distinct !DISubprogram(name: "uv_tcp_getpeername", scope: !1, file: !1, line: 239, type: !458, isLocal: false, isDefinition: true, scopeLine: 241, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!465 = distinct !DISubprogram(name: "uv_tcp_listen", scope: !1, file: !1, line: 261, type: !466, isLocal: false, isDefinition: true, scopeLine: 261, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!466 = !DISubroutineType(types: !467)
!467 = !{!124, !403, !124, !385}
!468 = distinct !DISubprogram(name: "uv__tcp_nodelay", scope: !1, file: !1, line: 315, type: !469, isLocal: false, isDefinition: true, scopeLine: 315, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!469 = !DISubroutineType(types: !470)
!470 = !{!124, !124, !124}
!471 = distinct !DISubprogram(name: "uv__tcp_keepalive", scope: !1, file: !1, line: 322, type: !472, isLocal: false, isDefinition: true, scopeLine: 322, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!472 = !DISubroutineType(types: !473)
!473 = !{!124, !124, !124, !114}
!474 = distinct !DISubprogram(name: "uv_tcp_nodelay", scope: !1, file: !1, line: 344, type: !475, isLocal: false, isDefinition: true, scopeLine: 344, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!475 = !DISubroutineType(types: !476)
!476 = !{!124, !403, !124}
!477 = distinct !DISubprogram(name: "uv_tcp_keepalive", scope: !1, file: !1, line: 362, type: !478, isLocal: false, isDefinition: true, scopeLine: 362, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!478 = !DISubroutineType(types: !479)
!479 = !{!124, !403, !124, !114}
!480 = distinct !DISubprogram(name: "uv_tcp_simultaneous_accepts", scope: !1, file: !1, line: 384, type: !475, isLocal: false, isDefinition: true, scopeLine: 384, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!481 = distinct !DISubprogram(name: "uv__tcp_close", scope: !1, file: !1, line: 393, type: !482, isLocal: false, isDefinition: true, scopeLine: 393, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!482 = !DISubroutineType(types: !483)
!483 = !{null, !403}
!484 = distinct !DISubprogram(name: "maybe_new_socket", scope: !1, file: !1, line: 31, type: !485, isLocal: true, isDefinition: true, scopeLine: 31, flags: DIFlagPrototyped, isOptimized: false, variables: !431)
!485 = !DISubroutineType(types: !486)
!486 = !{!124, !403, !124, !124}
!487 = !{!488}
!488 = !DIGlobalVariable(name: "single_accept", scope: !465, file: !1, line: 262, type: !124, isLocal: true, isDefinition: true, variable: i32* @uv_tcp_listen.single_accept)
!489 = !{i32 2, !"Dwarf Version", i32 4}
!490 = !{i32 2, !"Debug Info Version", i32 3}
!491 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!492 = !DILocalVariable(name: "loop", arg: 1, scope: !400, file: !1, line: 55, type: !108)
!493 = !DIExpression()
!494 = !DILocation(line: 55, column: 31, scope: !400)
!495 = !DILocalVariable(name: "tcp", arg: 2, scope: !400, file: !1, line: 55, type: !403)
!496 = !DILocation(line: 55, column: 47, scope: !400)
!497 = !DILocalVariable(name: "flags", arg: 3, scope: !400, file: !1, line: 55, type: !114)
!498 = !DILocation(line: 55, column: 65, scope: !400)
!499 = !DILocalVariable(name: "domain", scope: !400, file: !1, line: 56, type: !124)
!500 = !DILocation(line: 56, column: 7, scope: !400)
!501 = !DILocation(line: 59, column: 12, scope: !400)
!502 = !DILocation(line: 59, column: 18, scope: !400)
!503 = !DILocation(line: 59, column: 10, scope: !400)
!504 = !DILocation(line: 60, column: 7, scope: !505)
!505 = distinct !DILexicalBlock(scope: !400, file: !1, line: 60, column: 7)
!506 = !DILocation(line: 60, column: 14, scope: !505)
!507 = !DILocation(line: 60, column: 25, scope: !505)
!508 = !DILocation(line: 60, column: 28, scope: !509)
!509 = !DILexicalBlockFile(scope: !505, file: !1, discriminator: 1)
!510 = !DILocation(line: 60, column: 35, scope: !509)
!511 = !DILocation(line: 60, column: 47, scope: !509)
!512 = !DILocation(line: 60, column: 50, scope: !513)
!513 = !DILexicalBlockFile(scope: !505, file: !1, discriminator: 2)
!514 = !DILocation(line: 60, column: 57, scope: !513)
!515 = !DILocation(line: 60, column: 7, scope: !513)
!516 = !DILocation(line: 61, column: 5, scope: !505)
!517 = !DILocation(line: 63, column: 7, scope: !518)
!518 = distinct !DILexicalBlock(scope: !400, file: !1, line: 63, column: 7)
!519 = !DILocation(line: 63, column: 13, scope: !518)
!520 = !DILocation(line: 63, column: 7, scope: !400)
!521 = !DILocation(line: 64, column: 5, scope: !518)
!522 = !DILocation(line: 66, column: 19, scope: !400)
!523 = !DILocation(line: 66, column: 39, scope: !400)
!524 = !DILocation(line: 66, column: 25, scope: !400)
!525 = !DILocation(line: 66, column: 3, scope: !400)
!526 = !DILocation(line: 72, column: 7, scope: !527)
!527 = distinct !DILexicalBlock(scope: !400, file: !1, line: 72, column: 7)
!528 = !DILocation(line: 72, column: 14, scope: !527)
!529 = !DILocation(line: 72, column: 7, scope: !400)
!530 = !DILocalVariable(name: "err", scope: !531, file: !1, line: 73, type: !124)
!531 = distinct !DILexicalBlock(scope: !527, file: !1, line: 72, column: 28)
!532 = !DILocation(line: 73, column: 9, scope: !531)
!533 = !DILocation(line: 73, column: 32, scope: !531)
!534 = !DILocation(line: 73, column: 37, scope: !531)
!535 = !DILocation(line: 73, column: 15, scope: !531)
!536 = !DILocation(line: 74, column: 9, scope: !537)
!537 = distinct !DILexicalBlock(scope: !531, file: !1, line: 74, column: 9)
!538 = !DILocation(line: 74, column: 9, scope: !531)
!539 = !DILocation(line: 75, column: 7, scope: !540)
!540 = distinct !DILexicalBlock(scope: !537, file: !1, line: 74, column: 14)
!541 = !DILocation(line: 75, column: 7, scope: !542)
!542 = !DILexicalBlockFile(scope: !543, file: !1, discriminator: 1)
!543 = distinct !DILexicalBlock(scope: !540, file: !1, line: 75, column: 7)
!544 = !DILocation(line: 76, column: 14, scope: !540)
!545 = !DILocation(line: 76, column: 7, scope: !540)
!546 = !DILocation(line: 78, column: 3, scope: !531)
!547 = !DILocation(line: 80, column: 3, scope: !400)
!548 = !DILocation(line: 81, column: 1, scope: !400)
!549 = !DILocalVariable(name: "handle", arg: 1, scope: !484, file: !1, line: 31, type: !403)
!550 = !DILocation(line: 31, column: 39, scope: !484)
!551 = !DILocalVariable(name: "domain", arg: 2, scope: !484, file: !1, line: 31, type: !124)
!552 = !DILocation(line: 31, column: 51, scope: !484)
!553 = !DILocalVariable(name: "flags", arg: 3, scope: !484, file: !1, line: 31, type: !124)
!554 = !DILocation(line: 31, column: 63, scope: !484)
!555 = !DILocalVariable(name: "sockfd", scope: !484, file: !1, line: 32, type: !124)
!556 = !DILocation(line: 32, column: 7, scope: !484)
!557 = !DILocalVariable(name: "err", scope: !484, file: !1, line: 33, type: !124)
!558 = !DILocation(line: 33, column: 7, scope: !484)
!559 = !DILocation(line: 35, column: 7, scope: !560)
!560 = distinct !DILexicalBlock(scope: !484, file: !1, line: 35, column: 7)
!561 = !DILocation(line: 35, column: 14, scope: !560)
!562 = !DILocation(line: 35, column: 27, scope: !560)
!563 = !DILocation(line: 35, column: 30, scope: !564)
!564 = !DILexicalBlockFile(scope: !560, file: !1, discriminator: 1)
!565 = !DILocation(line: 35, column: 52, scope: !564)
!566 = !DILocation(line: 35, column: 7, scope: !564)
!567 = !DILocation(line: 36, column: 22, scope: !568)
!568 = distinct !DILexicalBlock(scope: !560, file: !1, line: 35, column: 59)
!569 = !DILocation(line: 36, column: 5, scope: !568)
!570 = !DILocation(line: 36, column: 13, scope: !568)
!571 = !DILocation(line: 36, column: 19, scope: !568)
!572 = !DILocation(line: 37, column: 5, scope: !568)
!573 = !DILocation(line: 40, column: 20, scope: !484)
!574 = !DILocation(line: 40, column: 9, scope: !484)
!575 = !DILocation(line: 40, column: 7, scope: !484)
!576 = !DILocation(line: 41, column: 7, scope: !577)
!577 = distinct !DILexicalBlock(scope: !484, file: !1, line: 41, column: 7)
!578 = !DILocation(line: 41, column: 11, scope: !577)
!579 = !DILocation(line: 41, column: 7, scope: !484)
!580 = !DILocation(line: 42, column: 12, scope: !577)
!581 = !DILocation(line: 42, column: 5, scope: !577)
!582 = !DILocation(line: 43, column: 12, scope: !484)
!583 = !DILocation(line: 43, column: 10, scope: !484)
!584 = !DILocation(line: 45, column: 40, scope: !484)
!585 = !DILocation(line: 45, column: 25, scope: !484)
!586 = !DILocation(line: 45, column: 48, scope: !484)
!587 = !DILocation(line: 45, column: 56, scope: !484)
!588 = !DILocation(line: 45, column: 9, scope: !484)
!589 = !DILocation(line: 45, column: 7, scope: !484)
!590 = !DILocation(line: 46, column: 7, scope: !591)
!591 = distinct !DILexicalBlock(scope: !484, file: !1, line: 46, column: 7)
!592 = !DILocation(line: 46, column: 7, scope: !484)
!593 = !DILocation(line: 47, column: 15, scope: !594)
!594 = distinct !DILexicalBlock(scope: !591, file: !1, line: 46, column: 12)
!595 = !DILocation(line: 47, column: 5, scope: !594)
!596 = !DILocation(line: 48, column: 12, scope: !594)
!597 = !DILocation(line: 48, column: 5, scope: !594)
!598 = !DILocation(line: 51, column: 3, scope: !484)
!599 = !DILocation(line: 52, column: 1, scope: !484)
!600 = !DILocalVariable(name: "loop", arg: 1, scope: !432, file: !1, line: 84, type: !108)
!601 = !DILocation(line: 84, column: 28, scope: !432)
!602 = !DILocalVariable(name: "tcp", arg: 2, scope: !432, file: !1, line: 84, type: !403)
!603 = !DILocation(line: 84, column: 44, scope: !432)
!604 = !DILocation(line: 85, column: 25, scope: !432)
!605 = !DILocation(line: 85, column: 31, scope: !432)
!606 = !DILocation(line: 85, column: 10, scope: !432)
!607 = !DILocation(line: 85, column: 3, scope: !432)
!608 = !DILocalVariable(name: "tcp", arg: 1, scope: !435, file: !1, line: 89, type: !403)
!609 = !DILocation(line: 89, column: 28, scope: !435)
!610 = !DILocalVariable(name: "addr", arg: 2, scope: !435, file: !1, line: 90, type: !438)
!611 = !DILocation(line: 90, column: 41, scope: !435)
!612 = !DILocalVariable(name: "addrlen", arg: 3, scope: !435, file: !1, line: 91, type: !114)
!613 = !DILocation(line: 91, column: 31, scope: !435)
!614 = !DILocalVariable(name: "flags", arg: 4, scope: !435, file: !1, line: 92, type: !114)
!615 = !DILocation(line: 92, column: 31, scope: !435)
!616 = !DILocalVariable(name: "err", scope: !435, file: !1, line: 93, type: !124)
!617 = !DILocation(line: 93, column: 7, scope: !435)
!618 = !DILocalVariable(name: "on", scope: !435, file: !1, line: 94, type: !124)
!619 = !DILocation(line: 94, column: 7, scope: !435)
!620 = !DILocation(line: 97, column: 8, scope: !621)
!621 = distinct !DILexicalBlock(scope: !435, file: !1, line: 97, column: 7)
!622 = !DILocation(line: 97, column: 14, scope: !621)
!623 = !DILocation(line: 97, column: 33, scope: !621)
!624 = !DILocation(line: 97, column: 36, scope: !625)
!625 = !DILexicalBlockFile(scope: !621, file: !1, discriminator: 1)
!626 = !DILocation(line: 97, column: 42, scope: !625)
!627 = !DILocation(line: 97, column: 52, scope: !625)
!628 = !DILocation(line: 97, column: 7, scope: !625)
!629 = !DILocation(line: 98, column: 5, scope: !621)
!630 = !DILocation(line: 100, column: 26, scope: !435)
!631 = !DILocation(line: 101, column: 26, scope: !435)
!632 = !DILocation(line: 101, column: 32, scope: !435)
!633 = !DILocation(line: 100, column: 9, scope: !435)
!634 = !DILocation(line: 100, column: 7, scope: !435)
!635 = !DILocation(line: 103, column: 7, scope: !636)
!636 = distinct !DILexicalBlock(scope: !435, file: !1, line: 103, column: 7)
!637 = !DILocation(line: 103, column: 7, scope: !435)
!638 = !DILocation(line: 104, column: 12, scope: !636)
!639 = !DILocation(line: 104, column: 5, scope: !636)
!640 = !DILocation(line: 106, column: 6, scope: !435)
!641 = !DILocation(line: 107, column: 18, scope: !642)
!642 = distinct !DILexicalBlock(scope: !435, file: !1, line: 107, column: 7)
!643 = !DILocation(line: 107, column: 23, scope: !642)
!644 = !DILocation(line: 107, column: 34, scope: !642)
!645 = !DILocation(line: 107, column: 64, scope: !642)
!646 = !DILocation(line: 107, column: 7, scope: !642)
!647 = !DILocation(line: 107, column: 7, scope: !435)
!648 = !DILocation(line: 108, column: 13, scope: !642)
!649 = !DILocation(line: 108, column: 12, scope: !642)
!650 = !DILocation(line: 108, column: 5, scope: !642)
!651 = !DILocation(line: 111, column: 7, scope: !652)
!652 = distinct !DILexicalBlock(scope: !435, file: !1, line: 111, column: 7)
!653 = !DILocation(line: 111, column: 13, scope: !652)
!654 = !DILocation(line: 111, column: 23, scope: !652)
!655 = !DILocation(line: 111, column: 7, scope: !435)
!656 = !DILocation(line: 112, column: 11, scope: !657)
!657 = distinct !DILexicalBlock(scope: !652, file: !1, line: 111, column: 36)
!658 = !DILocation(line: 112, column: 17, scope: !657)
!659 = !DILocation(line: 112, column: 36, scope: !657)
!660 = !DILocation(line: 112, column: 8, scope: !657)
!661 = !DILocation(line: 113, column: 20, scope: !662)
!662 = distinct !DILexicalBlock(scope: !657, file: !1, line: 113, column: 9)
!663 = !DILocation(line: 113, column: 25, scope: !662)
!664 = !DILocation(line: 113, column: 36, scope: !662)
!665 = !DILocation(line: 116, column: 20, scope: !662)
!666 = !DILocation(line: 113, column: 9, scope: !662)
!667 = !DILocation(line: 117, column: 31, scope: !662)
!668 = !DILocation(line: 113, column: 9, scope: !657)
!669 = !DILocation(line: 122, column: 15, scope: !670)
!670 = distinct !DILexicalBlock(scope: !662, file: !1, line: 117, column: 38)
!671 = !DILocation(line: 122, column: 14, scope: !670)
!672 = !DILocation(line: 122, column: 7, scope: !670)
!673 = !DILocation(line: 124, column: 3, scope: !657)
!674 = !DILocation(line: 127, column: 3, scope: !435)
!675 = !DILocation(line: 127, column: 9, scope: !435)
!676 = !DILocation(line: 128, column: 12, scope: !677)
!677 = distinct !DILexicalBlock(scope: !435, file: !1, line: 128, column: 7)
!678 = !DILocation(line: 128, column: 17, scope: !677)
!679 = !DILocation(line: 128, column: 28, scope: !677)
!680 = !DILocation(line: 128, column: 32, scope: !677)
!681 = !DILocation(line: 128, column: 38, scope: !677)
!682 = !DILocation(line: 128, column: 7, scope: !677)
!683 = !DILocation(line: 128, column: 47, scope: !677)
!684 = !DILocation(line: 128, column: 50, scope: !685)
!685 = !DILexicalBlockFile(scope: !677, file: !1, discriminator: 1)
!686 = !DILocation(line: 128, column: 56, scope: !685)
!687 = !DILocation(line: 128, column: 7, scope: !685)
!688 = !DILocation(line: 129, column: 9, scope: !689)
!689 = distinct !DILexicalBlock(scope: !690, file: !1, line: 129, column: 9)
!690 = distinct !DILexicalBlock(scope: !677, file: !1, line: 128, column: 71)
!691 = !DILocation(line: 129, column: 15, scope: !689)
!692 = !DILocation(line: 129, column: 9, scope: !690)
!693 = !DILocation(line: 132, column: 7, scope: !689)
!694 = !DILocation(line: 133, column: 13, scope: !690)
!695 = !DILocation(line: 133, column: 12, scope: !690)
!696 = !DILocation(line: 133, column: 5, scope: !690)
!697 = !DILocation(line: 135, column: 25, scope: !435)
!698 = !DILocation(line: 135, column: 24, scope: !435)
!699 = !DILocation(line: 135, column: 3, scope: !435)
!700 = !DILocation(line: 135, column: 8, scope: !435)
!701 = !DILocation(line: 135, column: 22, scope: !435)
!702 = !DILocation(line: 137, column: 3, scope: !435)
!703 = !DILocation(line: 137, column: 8, scope: !435)
!704 = !DILocation(line: 137, column: 14, scope: !435)
!705 = !DILocation(line: 138, column: 7, scope: !706)
!706 = distinct !DILexicalBlock(scope: !435, file: !1, line: 138, column: 7)
!707 = !DILocation(line: 138, column: 13, scope: !706)
!708 = !DILocation(line: 138, column: 23, scope: !706)
!709 = !DILocation(line: 138, column: 7, scope: !435)
!710 = !DILocation(line: 139, column: 5, scope: !706)
!711 = !DILocation(line: 139, column: 10, scope: !706)
!712 = !DILocation(line: 139, column: 16, scope: !706)
!713 = !DILocation(line: 141, column: 3, scope: !435)
!714 = !DILocation(line: 142, column: 1, scope: !435)
!715 = !DILocalVariable(name: "req", arg: 1, scope: !450, file: !1, line: 145, type: !350)
!716 = !DILocation(line: 145, column: 35, scope: !450)
!717 = !DILocalVariable(name: "handle", arg: 2, scope: !450, file: !1, line: 146, type: !403)
!718 = !DILocation(line: 146, column: 31, scope: !450)
!719 = !DILocalVariable(name: "addr", arg: 3, scope: !450, file: !1, line: 147, type: !438)
!720 = !DILocation(line: 147, column: 44, scope: !450)
!721 = !DILocalVariable(name: "addrlen", arg: 4, scope: !450, file: !1, line: 148, type: !114)
!722 = !DILocation(line: 148, column: 34, scope: !450)
!723 = !DILocalVariable(name: "cb", arg: 5, scope: !450, file: !1, line: 149, type: !360)
!724 = !DILocation(line: 149, column: 35, scope: !450)
!725 = !DILocalVariable(name: "err", scope: !450, file: !1, line: 150, type: !124)
!726 = !DILocation(line: 150, column: 7, scope: !450)
!727 = !DILocalVariable(name: "r", scope: !450, file: !1, line: 151, type: !124)
!728 = !DILocation(line: 151, column: 7, scope: !450)
!729 = !DILocation(line: 153, column: 3, scope: !450)
!730 = !DILocation(line: 153, column: 3, scope: !731)
!731 = !DILexicalBlockFile(scope: !450, file: !1, discriminator: 1)
!732 = !DILocation(line: 153, column: 3, scope: !733)
!733 = !DILexicalBlockFile(scope: !450, file: !1, discriminator: 2)
!734 = !DILocation(line: 153, column: 3, scope: !735)
!735 = !DILexicalBlockFile(scope: !450, file: !1, discriminator: 3)
!736 = !DILocation(line: 155, column: 7, scope: !737)
!737 = distinct !DILexicalBlock(scope: !450, file: !1, line: 155, column: 7)
!738 = !DILocation(line: 155, column: 15, scope: !737)
!739 = !DILocation(line: 155, column: 27, scope: !737)
!740 = !DILocation(line: 155, column: 7, scope: !450)
!741 = !DILocation(line: 156, column: 5, scope: !737)
!742 = !DILocation(line: 158, column: 26, scope: !450)
!743 = !DILocation(line: 159, column: 26, scope: !450)
!744 = !DILocation(line: 159, column: 32, scope: !450)
!745 = !DILocation(line: 158, column: 9, scope: !450)
!746 = !DILocation(line: 158, column: 7, scope: !450)
!747 = !DILocation(line: 161, column: 7, scope: !748)
!748 = distinct !DILexicalBlock(scope: !450, file: !1, line: 161, column: 7)
!749 = !DILocation(line: 161, column: 7, scope: !450)
!750 = !DILocation(line: 162, column: 12, scope: !748)
!751 = !DILocation(line: 162, column: 5, scope: !748)
!752 = !DILocation(line: 164, column: 3, scope: !450)
!753 = !DILocation(line: 164, column: 11, scope: !450)
!754 = !DILocation(line: 164, column: 25, scope: !450)
!755 = !DILocation(line: 166, column: 3, scope: !450)
!756 = !DILocation(line: 167, column: 5, scope: !757)
!757 = distinct !DILexicalBlock(scope: !450, file: !1, line: 166, column: 6)
!758 = !DILocation(line: 167, column: 11, scope: !757)
!759 = !DILocation(line: 168, column: 17, scope: !757)
!760 = !DILocation(line: 168, column: 40, scope: !757)
!761 = !DILocation(line: 168, column: 46, scope: !757)
!762 = !DILocation(line: 168, column: 9, scope: !757)
!763 = !DILocation(line: 168, column: 7, scope: !757)
!764 = !DILocation(line: 169, column: 3, scope: !757)
!765 = !DILocation(line: 169, column: 12, scope: !731)
!766 = !DILocation(line: 169, column: 14, scope: !731)
!767 = !DILocation(line: 169, column: 20, scope: !731)
!768 = !DILocation(line: 169, column: 23, scope: !733)
!769 = !DILocation(line: 169, column: 29, scope: !733)
!770 = !DILocation(line: 169, column: 3, scope: !771)
!771 = !DILexicalBlockFile(scope: !757, file: !1, discriminator: 3)
!772 = !DILocation(line: 176, column: 7, scope: !773)
!773 = distinct !DILexicalBlock(scope: !450, file: !1, line: 176, column: 7)
!774 = !DILocation(line: 176, column: 9, scope: !773)
!775 = !DILocation(line: 176, column: 15, scope: !773)
!776 = !DILocation(line: 176, column: 18, scope: !777)
!777 = !DILexicalBlockFile(scope: !773, file: !1, discriminator: 1)
!778 = !DILocation(line: 176, column: 24, scope: !777)
!779 = !DILocation(line: 176, column: 7, scope: !777)
!780 = !DILocation(line: 177, column: 9, scope: !781)
!781 = distinct !DILexicalBlock(scope: !782, file: !1, line: 177, column: 9)
!782 = distinct !DILexicalBlock(scope: !773, file: !1, line: 176, column: 30)
!783 = !DILocation(line: 177, column: 15, scope: !781)
!784 = !DILocation(line: 177, column: 9, scope: !782)
!785 = !DILocation(line: 177, column: 9, scope: !786)
!786 = !DILexicalBlockFile(scope: !782, file: !1, discriminator: 1)
!787 = !DILocation(line: 179, column: 14, scope: !788)
!788 = distinct !DILexicalBlock(scope: !781, file: !1, line: 179, column: 14)
!789 = !DILocation(line: 179, column: 20, scope: !788)
!790 = !DILocation(line: 179, column: 14, scope: !781)
!791 = !DILocation(line: 184, column: 32, scope: !788)
!792 = !DILocation(line: 184, column: 31, scope: !788)
!793 = !DILocation(line: 184, column: 7, scope: !788)
!794 = !DILocation(line: 184, column: 15, scope: !788)
!795 = !DILocation(line: 184, column: 29, scope: !788)
!796 = !DILocation(line: 186, column: 15, scope: !788)
!797 = !DILocation(line: 186, column: 14, scope: !788)
!798 = !DILocation(line: 186, column: 7, scope: !788)
!799 = !DILocation(line: 187, column: 3, scope: !782)
!800 = !DILocation(line: 189, column: 3, scope: !450)
!801 = !DILocation(line: 189, column: 3, scope: !802)
!802 = !DILexicalBlockFile(scope: !803, file: !1, discriminator: 1)
!803 = distinct !DILexicalBlock(scope: !450, file: !1, line: 189, column: 3)
!804 = !DILocation(line: 189, column: 3, scope: !805)
!805 = !DILexicalBlockFile(scope: !806, file: !1, discriminator: 2)
!806 = distinct !DILexicalBlock(scope: !803, file: !1, line: 189, column: 3)
!807 = !DILocation(line: 189, column: 3, scope: !808)
!808 = !DILexicalBlockFile(scope: !803, file: !1, discriminator: 3)
!809 = !DILocation(line: 189, column: 3, scope: !810)
!810 = !DILexicalBlockFile(scope: !811, file: !1, discriminator: 4)
!811 = distinct !DILexicalBlock(scope: !803, file: !1, line: 189, column: 3)
!812 = !DILocation(line: 189, column: 3, scope: !813)
!813 = !DILexicalBlockFile(scope: !814, file: !1, discriminator: 5)
!814 = distinct !DILexicalBlock(scope: !811, file: !1, line: 189, column: 3)
!815 = !DILocation(line: 189, column: 3, scope: !816)
!816 = !DILexicalBlockFile(scope: !811, file: !1, discriminator: 6)
!817 = !DILocation(line: 189, column: 3, scope: !818)
!818 = !DILexicalBlockFile(scope: !803, file: !1, discriminator: 7)
!819 = !DILocation(line: 190, column: 13, scope: !450)
!820 = !DILocation(line: 190, column: 3, scope: !450)
!821 = !DILocation(line: 190, column: 8, scope: !450)
!822 = !DILocation(line: 190, column: 11, scope: !450)
!823 = !DILocation(line: 191, column: 32, scope: !450)
!824 = !DILocation(line: 191, column: 17, scope: !450)
!825 = !DILocation(line: 191, column: 3, scope: !450)
!826 = !DILocation(line: 191, column: 8, scope: !450)
!827 = !DILocation(line: 191, column: 15, scope: !450)
!828 = !DILocation(line: 192, column: 3, scope: !450)
!829 = !DILocation(line: 192, column: 3, scope: !830)
!830 = !DILexicalBlockFile(scope: !831, file: !1, discriminator: 1)
!831 = distinct !DILexicalBlock(scope: !450, file: !1, line: 192, column: 3)
!832 = !DILocation(line: 193, column: 25, scope: !450)
!833 = !DILocation(line: 193, column: 3, scope: !450)
!834 = !DILocation(line: 193, column: 11, scope: !450)
!835 = !DILocation(line: 193, column: 23, scope: !450)
!836 = !DILocation(line: 195, column: 16, scope: !450)
!837 = !DILocation(line: 195, column: 24, scope: !450)
!838 = !DILocation(line: 195, column: 31, scope: !450)
!839 = !DILocation(line: 195, column: 39, scope: !450)
!840 = !DILocation(line: 195, column: 3, scope: !450)
!841 = !DILocation(line: 197, column: 7, scope: !842)
!842 = distinct !DILexicalBlock(scope: !450, file: !1, line: 197, column: 7)
!843 = !DILocation(line: 197, column: 15, scope: !842)
!844 = !DILocation(line: 197, column: 7, scope: !450)
!845 = !DILocation(line: 198, column: 17, scope: !842)
!846 = !DILocation(line: 198, column: 25, scope: !842)
!847 = !DILocation(line: 198, column: 32, scope: !842)
!848 = !DILocation(line: 198, column: 40, scope: !842)
!849 = !DILocation(line: 198, column: 5, scope: !842)
!850 = !DILocation(line: 200, column: 3, scope: !450)
!851 = !DILocation(line: 201, column: 1, scope: !450)
!852 = !DILocalVariable(name: "handle", arg: 1, scope: !453, file: !1, line: 204, type: !403)
!853 = !DILocation(line: 204, column: 27, scope: !453)
!854 = !DILocalVariable(name: "sock", arg: 2, scope: !453, file: !1, line: 204, type: !456)
!855 = !DILocation(line: 204, column: 48, scope: !453)
!856 = !DILocalVariable(name: "err", scope: !453, file: !1, line: 205, type: !124)
!857 = !DILocation(line: 205, column: 7, scope: !453)
!858 = !DILocation(line: 207, column: 22, scope: !453)
!859 = !DILocation(line: 207, column: 9, scope: !453)
!860 = !DILocation(line: 207, column: 7, scope: !453)
!861 = !DILocation(line: 208, column: 7, scope: !862)
!862 = distinct !DILexicalBlock(scope: !453, file: !1, line: 208, column: 7)
!863 = !DILocation(line: 208, column: 7, scope: !453)
!864 = !DILocation(line: 209, column: 12, scope: !862)
!865 = !DILocation(line: 209, column: 5, scope: !862)
!866 = !DILocation(line: 211, column: 40, scope: !453)
!867 = !DILocation(line: 211, column: 26, scope: !453)
!868 = !DILocation(line: 212, column: 26, scope: !453)
!869 = !DILocation(line: 211, column: 10, scope: !453)
!870 = !DILocation(line: 211, column: 3, scope: !453)
!871 = !DILocation(line: 214, column: 1, scope: !453)
!872 = !DILocalVariable(name: "handle", arg: 1, scope: !457, file: !1, line: 217, type: !460)
!873 = !DILocation(line: 217, column: 40, scope: !457)
!874 = !DILocalVariable(name: "name", arg: 2, scope: !457, file: !1, line: 218, type: !462)
!875 = !DILocation(line: 218, column: 41, scope: !457)
!876 = !DILocalVariable(name: "namelen", arg: 3, scope: !457, file: !1, line: 219, type: !463)
!877 = !DILocation(line: 219, column: 29, scope: !457)
!878 = !DILocalVariable(name: "socklen", scope: !457, file: !1, line: 220, type: !396)
!879 = !DILocation(line: 220, column: 13, scope: !457)
!880 = !DILocation(line: 222, column: 7, scope: !881)
!881 = distinct !DILexicalBlock(scope: !457, file: !1, line: 222, column: 7)
!882 = !DILocation(line: 222, column: 15, scope: !881)
!883 = !DILocation(line: 222, column: 7, scope: !457)
!884 = !DILocation(line: 223, column: 12, scope: !881)
!885 = !DILocation(line: 223, column: 20, scope: !881)
!886 = !DILocation(line: 223, column: 5, scope: !881)
!887 = !DILocation(line: 225, column: 7, scope: !888)
!888 = distinct !DILexicalBlock(scope: !457, file: !1, line: 225, column: 7)
!889 = !DILocation(line: 225, column: 29, scope: !888)
!890 = !DILocation(line: 225, column: 7, scope: !457)
!891 = !DILocation(line: 226, column: 5, scope: !888)
!892 = !DILocation(line: 229, column: 26, scope: !457)
!893 = !DILocation(line: 229, column: 25, scope: !457)
!894 = !DILocation(line: 229, column: 11, scope: !457)
!895 = !DILocation(line: 231, column: 19, scope: !896)
!896 = distinct !DILexicalBlock(scope: !457, file: !1, line: 231, column: 7)
!897 = !DILocation(line: 231, column: 42, scope: !896)
!898 = !DILocation(line: 231, column: 7, scope: !896)
!899 = !DILocation(line: 231, column: 7, scope: !457)
!900 = !DILocation(line: 232, column: 13, scope: !896)
!901 = !DILocation(line: 232, column: 12, scope: !896)
!902 = !DILocation(line: 232, column: 5, scope: !896)
!903 = !DILocation(line: 234, column: 20, scope: !457)
!904 = !DILocation(line: 234, column: 4, scope: !457)
!905 = !DILocation(line: 234, column: 12, scope: !457)
!906 = !DILocation(line: 235, column: 3, scope: !457)
!907 = !DILocation(line: 236, column: 1, scope: !457)
!908 = !DILocalVariable(name: "handle", arg: 1, scope: !464, file: !1, line: 239, type: !460)
!909 = !DILocation(line: 239, column: 40, scope: !464)
!910 = !DILocalVariable(name: "name", arg: 2, scope: !464, file: !1, line: 240, type: !462)
!911 = !DILocation(line: 240, column: 41, scope: !464)
!912 = !DILocalVariable(name: "namelen", arg: 3, scope: !464, file: !1, line: 241, type: !463)
!913 = !DILocation(line: 241, column: 29, scope: !464)
!914 = !DILocalVariable(name: "socklen", scope: !464, file: !1, line: 242, type: !396)
!915 = !DILocation(line: 242, column: 13, scope: !464)
!916 = !DILocation(line: 244, column: 7, scope: !917)
!917 = distinct !DILexicalBlock(scope: !464, file: !1, line: 244, column: 7)
!918 = !DILocation(line: 244, column: 15, scope: !917)
!919 = !DILocation(line: 244, column: 7, scope: !464)
!920 = !DILocation(line: 245, column: 12, scope: !917)
!921 = !DILocation(line: 245, column: 20, scope: !917)
!922 = !DILocation(line: 245, column: 5, scope: !917)
!923 = !DILocation(line: 247, column: 7, scope: !924)
!924 = distinct !DILexicalBlock(scope: !464, file: !1, line: 247, column: 7)
!925 = !DILocation(line: 247, column: 29, scope: !924)
!926 = !DILocation(line: 247, column: 7, scope: !464)
!927 = !DILocation(line: 248, column: 5, scope: !924)
!928 = !DILocation(line: 251, column: 26, scope: !464)
!929 = !DILocation(line: 251, column: 25, scope: !464)
!930 = !DILocation(line: 251, column: 11, scope: !464)
!931 = !DILocation(line: 253, column: 19, scope: !932)
!932 = distinct !DILexicalBlock(scope: !464, file: !1, line: 253, column: 7)
!933 = !DILocation(line: 253, column: 42, scope: !932)
!934 = !DILocation(line: 253, column: 7, scope: !932)
!935 = !DILocation(line: 253, column: 7, scope: !464)
!936 = !DILocation(line: 254, column: 13, scope: !932)
!937 = !DILocation(line: 254, column: 12, scope: !932)
!938 = !DILocation(line: 254, column: 5, scope: !932)
!939 = !DILocation(line: 256, column: 20, scope: !464)
!940 = !DILocation(line: 256, column: 4, scope: !464)
!941 = !DILocation(line: 256, column: 12, scope: !464)
!942 = !DILocation(line: 257, column: 3, scope: !464)
!943 = !DILocation(line: 258, column: 1, scope: !464)
!944 = !DILocalVariable(name: "tcp", arg: 1, scope: !465, file: !1, line: 261, type: !403)
!945 = !DILocation(line: 261, column: 29, scope: !465)
!946 = !DILocalVariable(name: "backlog", arg: 2, scope: !465, file: !1, line: 261, type: !124)
!947 = !DILocation(line: 261, column: 38, scope: !465)
!948 = !DILocalVariable(name: "cb", arg: 3, scope: !465, file: !1, line: 261, type: !385)
!949 = !DILocation(line: 261, column: 64, scope: !465)
!950 = !DILocalVariable(name: "err", scope: !465, file: !1, line: 263, type: !124)
!951 = !DILocation(line: 263, column: 7, scope: !465)
!952 = !DILocation(line: 265, column: 7, scope: !953)
!953 = distinct !DILexicalBlock(scope: !465, file: !1, line: 265, column: 7)
!954 = !DILocation(line: 265, column: 12, scope: !953)
!955 = !DILocation(line: 265, column: 7, scope: !465)
!956 = !DILocation(line: 266, column: 12, scope: !953)
!957 = !DILocation(line: 266, column: 17, scope: !953)
!958 = !DILocation(line: 266, column: 5, scope: !953)
!959 = !DILocation(line: 268, column: 7, scope: !960)
!960 = distinct !DILexicalBlock(scope: !465, file: !1, line: 268, column: 7)
!961 = !DILocation(line: 268, column: 21, scope: !960)
!962 = !DILocation(line: 268, column: 7, scope: !465)
!963 = !DILocalVariable(name: "val", scope: !964, file: !1, line: 269, type: !965)
!964 = distinct !DILexicalBlock(scope: !960, file: !1, line: 268, column: 28)
!965 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !966, size: 64, align: 64)
!966 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !175)
!967 = !DILocation(line: 269, column: 17, scope: !964)
!968 = !DILocation(line: 269, column: 23, scope: !964)
!969 = !DILocation(line: 270, column: 22, scope: !964)
!970 = !DILocation(line: 270, column: 26, scope: !964)
!971 = !DILocation(line: 270, column: 34, scope: !964)
!972 = !DILocation(line: 270, column: 42, scope: !973)
!973 = !DILexicalBlockFile(scope: !964, file: !1, discriminator: 1)
!974 = !DILocation(line: 270, column: 37, scope: !973)
!975 = !DILocation(line: 270, column: 47, scope: !973)
!976 = !DILocation(line: 270, column: 34, scope: !977)
!977 = !DILexicalBlockFile(scope: !964, file: !1, discriminator: 2)
!978 = !DILocation(line: 270, column: 19, scope: !977)
!979 = !DILocation(line: 271, column: 3, scope: !964)
!980 = !DILocation(line: 273, column: 7, scope: !981)
!981 = distinct !DILexicalBlock(scope: !465, file: !1, line: 273, column: 7)
!982 = !DILocation(line: 273, column: 7, scope: !465)
!983 = !DILocation(line: 274, column: 5, scope: !981)
!984 = !DILocation(line: 274, column: 10, scope: !981)
!985 = !DILocation(line: 274, column: 16, scope: !981)
!986 = !DILocation(line: 276, column: 26, scope: !465)
!987 = !DILocation(line: 276, column: 9, scope: !465)
!988 = !DILocation(line: 276, column: 7, scope: !465)
!989 = !DILocation(line: 277, column: 7, scope: !990)
!990 = distinct !DILexicalBlock(scope: !465, file: !1, line: 277, column: 7)
!991 = !DILocation(line: 277, column: 7, scope: !465)
!992 = !DILocation(line: 278, column: 12, scope: !990)
!993 = !DILocation(line: 278, column: 5, scope: !990)
!994 = !DILocation(line: 301, column: 14, scope: !995)
!995 = distinct !DILexicalBlock(scope: !465, file: !1, line: 301, column: 7)
!996 = !DILocation(line: 301, column: 19, scope: !995)
!997 = !DILocation(line: 301, column: 30, scope: !995)
!998 = !DILocation(line: 301, column: 34, scope: !995)
!999 = !DILocation(line: 301, column: 7, scope: !995)
!1000 = !DILocation(line: 301, column: 7, scope: !465)
!1001 = !DILocation(line: 302, column: 13, scope: !995)
!1002 = !DILocation(line: 302, column: 12, scope: !995)
!1003 = !DILocation(line: 302, column: 5, scope: !995)
!1004 = !DILocation(line: 304, column: 24, scope: !465)
!1005 = !DILocation(line: 304, column: 3, scope: !465)
!1006 = !DILocation(line: 304, column: 8, scope: !465)
!1007 = !DILocation(line: 304, column: 22, scope: !465)
!1008 = !DILocation(line: 305, column: 3, scope: !465)
!1009 = !DILocation(line: 305, column: 8, scope: !465)
!1010 = !DILocation(line: 305, column: 14, scope: !465)
!1011 = !DILocation(line: 308, column: 3, scope: !465)
!1012 = !DILocation(line: 308, column: 8, scope: !465)
!1013 = !DILocation(line: 308, column: 19, scope: !465)
!1014 = !DILocation(line: 308, column: 22, scope: !465)
!1015 = !DILocation(line: 309, column: 16, scope: !465)
!1016 = !DILocation(line: 309, column: 21, scope: !465)
!1017 = !DILocation(line: 309, column: 28, scope: !465)
!1018 = !DILocation(line: 309, column: 33, scope: !465)
!1019 = !DILocation(line: 309, column: 3, scope: !465)
!1020 = !DILocation(line: 311, column: 3, scope: !465)
!1021 = !DILocation(line: 312, column: 1, scope: !465)
!1022 = !DILocalVariable(name: "fd", arg: 1, scope: !468, file: !1, line: 315, type: !124)
!1023 = !DILocation(line: 315, column: 25, scope: !468)
!1024 = !DILocalVariable(name: "on", arg: 2, scope: !468, file: !1, line: 315, type: !124)
!1025 = !DILocation(line: 315, column: 33, scope: !468)
!1026 = !DILocation(line: 316, column: 18, scope: !1027)
!1027 = distinct !DILexicalBlock(scope: !468, file: !1, line: 316, column: 7)
!1028 = !DILocation(line: 316, column: 48, scope: !1027)
!1029 = !DILocation(line: 316, column: 7, scope: !1027)
!1030 = !DILocation(line: 316, column: 7, scope: !468)
!1031 = !DILocation(line: 317, column: 13, scope: !1027)
!1032 = !DILocation(line: 317, column: 12, scope: !1027)
!1033 = !DILocation(line: 317, column: 5, scope: !1027)
!1034 = !DILocation(line: 318, column: 3, scope: !468)
!1035 = !DILocation(line: 319, column: 1, scope: !468)
!1036 = !DILocalVariable(name: "fd", arg: 1, scope: !471, file: !1, line: 322, type: !124)
!1037 = !DILocation(line: 322, column: 27, scope: !471)
!1038 = !DILocalVariable(name: "on", arg: 2, scope: !471, file: !1, line: 322, type: !124)
!1039 = !DILocation(line: 322, column: 35, scope: !471)
!1040 = !DILocalVariable(name: "delay", arg: 3, scope: !471, file: !1, line: 322, type: !114)
!1041 = !DILocation(line: 322, column: 52, scope: !471)
!1042 = !DILocation(line: 323, column: 18, scope: !1043)
!1043 = distinct !DILexicalBlock(scope: !471, file: !1, line: 323, column: 7)
!1044 = !DILocation(line: 323, column: 48, scope: !1043)
!1045 = !DILocation(line: 323, column: 7, scope: !1043)
!1046 = !DILocation(line: 323, column: 7, scope: !471)
!1047 = !DILocation(line: 324, column: 13, scope: !1043)
!1048 = !DILocation(line: 324, column: 12, scope: !1043)
!1049 = !DILocation(line: 324, column: 5, scope: !1043)
!1050 = !DILocation(line: 327, column: 7, scope: !1051)
!1051 = distinct !DILexicalBlock(scope: !471, file: !1, line: 327, column: 7)
!1052 = !DILocation(line: 327, column: 10, scope: !1051)
!1053 = !DILocation(line: 327, column: 24, scope: !1054)
!1054 = !DILexicalBlockFile(scope: !1051, file: !1, discriminator: 1)
!1055 = !DILocation(line: 327, column: 55, scope: !1054)
!1056 = !DILocation(line: 327, column: 13, scope: !1054)
!1057 = !DILocation(line: 327, column: 7, scope: !1054)
!1058 = !DILocation(line: 328, column: 13, scope: !1051)
!1059 = !DILocation(line: 328, column: 12, scope: !1051)
!1060 = !DILocation(line: 328, column: 5, scope: !1051)
!1061 = !DILocation(line: 340, column: 3, scope: !471)
!1062 = !DILocation(line: 341, column: 1, scope: !471)
!1063 = !DILocalVariable(name: "handle", arg: 1, scope: !474, file: !1, line: 344, type: !403)
!1064 = !DILocation(line: 344, column: 30, scope: !474)
!1065 = !DILocalVariable(name: "on", arg: 2, scope: !474, file: !1, line: 344, type: !124)
!1066 = !DILocation(line: 344, column: 42, scope: !474)
!1067 = !DILocalVariable(name: "err", scope: !474, file: !1, line: 345, type: !124)
!1068 = !DILocation(line: 345, column: 7, scope: !474)
!1069 = !DILocation(line: 347, column: 7, scope: !1070)
!1070 = distinct !DILexicalBlock(scope: !474, file: !1, line: 347, column: 7)
!1071 = !DILocation(line: 347, column: 29, scope: !1070)
!1072 = !DILocation(line: 347, column: 7, scope: !474)
!1073 = !DILocation(line: 348, column: 27, scope: !1074)
!1074 = distinct !DILexicalBlock(scope: !1070, file: !1, line: 347, column: 36)
!1075 = !DILocation(line: 348, column: 50, scope: !1074)
!1076 = !DILocation(line: 348, column: 11, scope: !1074)
!1077 = !DILocation(line: 348, column: 9, scope: !1074)
!1078 = !DILocation(line: 349, column: 9, scope: !1079)
!1079 = distinct !DILexicalBlock(scope: !1074, file: !1, line: 349, column: 9)
!1080 = !DILocation(line: 349, column: 9, scope: !1074)
!1081 = !DILocation(line: 350, column: 14, scope: !1079)
!1082 = !DILocation(line: 350, column: 7, scope: !1079)
!1083 = !DILocation(line: 351, column: 3, scope: !1074)
!1084 = !DILocation(line: 353, column: 7, scope: !1085)
!1085 = distinct !DILexicalBlock(scope: !474, file: !1, line: 353, column: 7)
!1086 = !DILocation(line: 353, column: 7, scope: !474)
!1087 = !DILocation(line: 354, column: 5, scope: !1085)
!1088 = !DILocation(line: 354, column: 13, scope: !1085)
!1089 = !DILocation(line: 354, column: 19, scope: !1085)
!1090 = !DILocation(line: 356, column: 5, scope: !1085)
!1091 = !DILocation(line: 356, column: 13, scope: !1085)
!1092 = !DILocation(line: 356, column: 19, scope: !1085)
!1093 = !DILocation(line: 358, column: 3, scope: !474)
!1094 = !DILocation(line: 359, column: 1, scope: !474)
!1095 = !DILocalVariable(name: "handle", arg: 1, scope: !477, file: !1, line: 362, type: !403)
!1096 = !DILocation(line: 362, column: 32, scope: !477)
!1097 = !DILocalVariable(name: "on", arg: 2, scope: !477, file: !1, line: 362, type: !124)
!1098 = !DILocation(line: 362, column: 44, scope: !477)
!1099 = !DILocalVariable(name: "delay", arg: 3, scope: !477, file: !1, line: 362, type: !114)
!1100 = !DILocation(line: 362, column: 61, scope: !477)
!1101 = !DILocalVariable(name: "err", scope: !477, file: !1, line: 363, type: !124)
!1102 = !DILocation(line: 363, column: 7, scope: !477)
!1103 = !DILocation(line: 365, column: 7, scope: !1104)
!1104 = distinct !DILexicalBlock(scope: !477, file: !1, line: 365, column: 7)
!1105 = !DILocation(line: 365, column: 29, scope: !1104)
!1106 = !DILocation(line: 365, column: 7, scope: !477)
!1107 = !DILocation(line: 366, column: 28, scope: !1108)
!1108 = distinct !DILexicalBlock(scope: !1104, file: !1, line: 365, column: 36)
!1109 = !DILocation(line: 366, column: 51, scope: !1108)
!1110 = !DILocation(line: 366, column: 55, scope: !1108)
!1111 = !DILocation(line: 366, column: 10, scope: !1108)
!1112 = !DILocation(line: 366, column: 9, scope: !1108)
!1113 = !DILocation(line: 367, column: 9, scope: !1114)
!1114 = distinct !DILexicalBlock(scope: !1108, file: !1, line: 367, column: 9)
!1115 = !DILocation(line: 367, column: 9, scope: !1108)
!1116 = !DILocation(line: 368, column: 14, scope: !1114)
!1117 = !DILocation(line: 368, column: 7, scope: !1114)
!1118 = !DILocation(line: 369, column: 3, scope: !1108)
!1119 = !DILocation(line: 371, column: 7, scope: !1120)
!1120 = distinct !DILexicalBlock(scope: !477, file: !1, line: 371, column: 7)
!1121 = !DILocation(line: 371, column: 7, scope: !477)
!1122 = !DILocation(line: 372, column: 5, scope: !1120)
!1123 = !DILocation(line: 372, column: 13, scope: !1120)
!1124 = !DILocation(line: 372, column: 19, scope: !1120)
!1125 = !DILocation(line: 374, column: 5, scope: !1120)
!1126 = !DILocation(line: 374, column: 13, scope: !1120)
!1127 = !DILocation(line: 374, column: 19, scope: !1120)
!1128 = !DILocation(line: 380, column: 3, scope: !477)
!1129 = !DILocation(line: 381, column: 1, scope: !477)
!1130 = !DILocalVariable(name: "handle", arg: 1, scope: !480, file: !1, line: 384, type: !403)
!1131 = !DILocation(line: 384, column: 43, scope: !480)
!1132 = !DILocalVariable(name: "enable", arg: 2, scope: !480, file: !1, line: 384, type: !124)
!1133 = !DILocation(line: 384, column: 55, scope: !480)
!1134 = !DILocation(line: 385, column: 7, scope: !1135)
!1135 = distinct !DILexicalBlock(scope: !480, file: !1, line: 385, column: 7)
!1136 = !DILocation(line: 385, column: 7, scope: !480)
!1137 = !DILocation(line: 386, column: 5, scope: !1135)
!1138 = !DILocation(line: 386, column: 13, scope: !1135)
!1139 = !DILocation(line: 386, column: 19, scope: !1135)
!1140 = !DILocation(line: 388, column: 5, scope: !1135)
!1141 = !DILocation(line: 388, column: 13, scope: !1135)
!1142 = !DILocation(line: 388, column: 19, scope: !1135)
!1143 = !DILocation(line: 389, column: 3, scope: !480)
!1144 = !DILocalVariable(name: "handle", arg: 1, scope: !481, file: !1, line: 393, type: !403)
!1145 = !DILocation(line: 393, column: 30, scope: !481)
!1146 = !DILocation(line: 394, column: 34, scope: !481)
!1147 = !DILocation(line: 394, column: 20, scope: !481)
!1148 = !DILocation(line: 394, column: 3, scope: !481)
!1149 = !DILocation(line: 395, column: 1, scope: !481)
