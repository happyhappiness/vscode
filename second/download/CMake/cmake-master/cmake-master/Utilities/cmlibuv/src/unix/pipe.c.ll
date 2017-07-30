; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/pipe.c'
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
%struct.uv_pipe_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8*, i32, i8* }
%union.anon.4 = type { [4 x i8*] }
%struct.uv_buf_t = type { i8*, i64 }
%struct.uv_stream_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.5, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, {}*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.5 = type { [4 x i8*] }
%struct.uv_connect_s = type { i8*, i32, [2 x i8*], [4 x i8*], void (%struct.uv_connect_s*, i32)*, %struct.uv_stream_s*, [2 x i8*] }
%struct.uv_shutdown_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_stream_s*, void (%struct.uv_shutdown_s*, i32)* }
%struct.sockaddr_un = type { i16, [108 x i8] }
%union.__CONST_SOCKADDR_ARG = type { %struct.sockaddr* }
%struct.sockaddr = type { i16, [14 x i8] }
%struct.uv__stream_queued_fds_s = type { i32, i32, [1 x i32] }

; Function Attrs: nounwind uwtable
define i32 @uv_pipe_init(%struct.uv_loop_s* %loop, %struct.uv_pipe_s* %handle, i32 %ipc) #0 !dbg !457 {
entry:
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  %ipc.addr = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !538, metadata !539), !dbg !540
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !541, metadata !539), !dbg !542
  store i32 %ipc, i32* %ipc.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %ipc.addr, metadata !543, metadata !539), !dbg !544
  %0 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !545
  %1 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !546
  %2 = bitcast %struct.uv_pipe_s* %1 to %struct.uv_stream_s*, !dbg !547
  call void @uv__stream_init(%struct.uv_loop_s* %0, %struct.uv_stream_s* %2, i32 7), !dbg !548
  %3 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !549
  %shutdown_req = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %3, i32 0, i32 12, !dbg !550
  store %struct.uv_shutdown_s* null, %struct.uv_shutdown_s** %shutdown_req, align 8, !dbg !551
  %4 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !552
  %connect_req = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %4, i32 0, i32 11, !dbg !553
  store %struct.uv_connect_s* null, %struct.uv_connect_s** %connect_req, align 8, !dbg !554
  %5 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !555
  %pipe_fname = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %5, i32 0, i32 21, !dbg !556
  store i8* null, i8** %pipe_fname, align 8, !dbg !557
  %6 = load i32, i32* %ipc.addr, align 4, !dbg !558
  %7 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !559
  %ipc1 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %7, i32 0, i32 20, !dbg !560
  store i32 %6, i32* %ipc1, align 8, !dbg !561
  ret i32 0, !dbg !562
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare void @uv__stream_init(%struct.uv_loop_s*, %struct.uv_stream_s*, i32) #2

; Function Attrs: nounwind uwtable
define i32 @uv_pipe_bind(%struct.uv_pipe_s* %handle, i8* %name) #0 !dbg !493 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  %name.addr = alloca i8*, align 8
  %saddr = alloca %struct.sockaddr_un, align 2
  %pipe_fname = alloca i8*, align 8
  %sockfd = alloca i32, align 4
  %err = alloca i32, align 4
  %agg.tmp = alloca %union.__CONST_SOCKADDR_ARG, align 8
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !563, metadata !539), !dbg !564
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !565, metadata !539), !dbg !566
  call void @llvm.dbg.declare(metadata %struct.sockaddr_un* %saddr, metadata !567, metadata !539), !dbg !576
  call void @llvm.dbg.declare(metadata i8** %pipe_fname, metadata !577, metadata !539), !dbg !578
  store i8* null, i8** %pipe_fname, align 8, !dbg !578
  call void @llvm.dbg.declare(metadata i32* %sockfd, metadata !579, metadata !539), !dbg !580
  store i32 -1, i32* %sockfd, align 4, !dbg !580
  call void @llvm.dbg.declare(metadata i32* %err, metadata !581, metadata !539), !dbg !582
  %0 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !583
  %io_watcher = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %0, i32 0, i32 13, !dbg !583
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !583
  %1 = load i32, i32* %fd, align 8, !dbg !583
  %cmp = icmp sge i32 %1, 0, !dbg !585
  br i1 %cmp, label %if.then, label %if.end, !dbg !586

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !587
  br label %return, !dbg !587

if.end:                                           ; preds = %entry
  %2 = load i8*, i8** %name.addr, align 8, !dbg !588
  %call = call i8* @uv__strdup(i8* %2), !dbg !589
  store i8* %call, i8** %pipe_fname, align 8, !dbg !590
  %3 = load i8*, i8** %pipe_fname, align 8, !dbg !591
  %cmp1 = icmp eq i8* %3, null, !dbg !593
  br i1 %cmp1, label %if.then2, label %if.end3, !dbg !594

if.then2:                                         ; preds = %if.end
  store i32 -12, i32* %retval, align 4, !dbg !595
  br label %return, !dbg !595

if.end3:                                          ; preds = %if.end
  store i8* null, i8** %name.addr, align 8, !dbg !596
  %call4 = call i32 @uv__socket(i32 1, i32 1, i32 0), !dbg !597
  store i32 %call4, i32* %err, align 4, !dbg !598
  %4 = load i32, i32* %err, align 4, !dbg !599
  %cmp5 = icmp slt i32 %4, 0, !dbg !601
  br i1 %cmp5, label %if.then6, label %if.end7, !dbg !602

if.then6:                                         ; preds = %if.end3
  br label %err_socket, !dbg !603

if.end7:                                          ; preds = %if.end3
  %5 = load i32, i32* %err, align 4, !dbg !604
  store i32 %5, i32* %sockfd, align 4, !dbg !605
  %6 = bitcast %struct.sockaddr_un* %saddr to i8*, !dbg !606
  call void @llvm.memset.p0i8.i64(i8* %6, i8 0, i64 110, i32 2, i1 false), !dbg !606
  %sun_path = getelementptr inbounds %struct.sockaddr_un, %struct.sockaddr_un* %saddr, i32 0, i32 1, !dbg !607
  %arraydecay = getelementptr inbounds [108 x i8], [108 x i8]* %sun_path, i32 0, i32 0, !dbg !608
  %7 = load i8*, i8** %pipe_fname, align 8, !dbg !609
  %call8 = call i8* @strncpy(i8* %arraydecay, i8* %7, i64 107) #7, !dbg !610
  %sun_path9 = getelementptr inbounds %struct.sockaddr_un, %struct.sockaddr_un* %saddr, i32 0, i32 1, !dbg !611
  %arrayidx = getelementptr inbounds [108 x i8], [108 x i8]* %sun_path9, i64 0, i64 107, !dbg !612
  store i8 0, i8* %arrayidx, align 1, !dbg !613
  %sun_family = getelementptr inbounds %struct.sockaddr_un, %struct.sockaddr_un* %saddr, i32 0, i32 0, !dbg !614
  store i16 1, i16* %sun_family, align 2, !dbg !615
  %8 = load i32, i32* %sockfd, align 4, !dbg !616
  %__sockaddr__ = bitcast %union.__CONST_SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !618
  %9 = bitcast %struct.sockaddr_un* %saddr to %struct.sockaddr*, !dbg !618
  store %struct.sockaddr* %9, %struct.sockaddr** %__sockaddr__, align 8, !dbg !618
  %coerce.dive = getelementptr inbounds %union.__CONST_SOCKADDR_ARG, %union.__CONST_SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !619
  %10 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !619
  %call10 = call i32 @bind(i32 %8, %struct.sockaddr* %10, i32 110) #7, !dbg !619
  %tobool = icmp ne i32 %call10, 0, !dbg !619
  br i1 %tobool, label %if.then11, label %if.end17, !dbg !620

if.then11:                                        ; preds = %if.end7
  %call12 = call i32* @__errno_location() #1, !dbg !621
  %11 = load i32, i32* %call12, align 4, !dbg !621
  %sub = sub nsw i32 0, %11, !dbg !623
  store i32 %sub, i32* %err, align 4, !dbg !624
  %12 = load i32, i32* %err, align 4, !dbg !625
  %cmp13 = icmp eq i32 %12, -2, !dbg !627
  br i1 %cmp13, label %if.then14, label %if.end15, !dbg !628

if.then14:                                        ; preds = %if.then11
  store i32 -13, i32* %err, align 4, !dbg !629
  br label %if.end15, !dbg !630

if.end15:                                         ; preds = %if.then14, %if.then11
  %13 = load i32, i32* %sockfd, align 4, !dbg !631
  %call16 = call i32 @uv__close(i32 %13), !dbg !632
  br label %err_socket, !dbg !633

if.end17:                                         ; preds = %if.end7
  %14 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !634
  %flags = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %14, i32 0, i32 7, !dbg !635
  %15 = load i32, i32* %flags, align 8, !dbg !636
  %or = or i32 %15, 262144, !dbg !636
  store i32 %or, i32* %flags, align 8, !dbg !636
  %16 = load i8*, i8** %pipe_fname, align 8, !dbg !637
  %17 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !638
  %pipe_fname18 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %17, i32 0, i32 21, !dbg !639
  store i8* %16, i8** %pipe_fname18, align 8, !dbg !640
  %18 = load i32, i32* %sockfd, align 4, !dbg !641
  %19 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !642
  %io_watcher19 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %19, i32 0, i32 13, !dbg !643
  %fd20 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher19, i32 0, i32 5, !dbg !644
  store i32 %18, i32* %fd20, align 8, !dbg !645
  store i32 0, i32* %retval, align 4, !dbg !646
  br label %return, !dbg !646

err_socket:                                       ; preds = %if.end15, %if.then6
  %20 = load i8*, i8** %pipe_fname, align 8, !dbg !647
  call void @uv__free(i8* %20), !dbg !648
  %21 = load i32, i32* %err, align 4, !dbg !649
  store i32 %21, i32* %retval, align 4, !dbg !650
  br label %return, !dbg !650

return:                                           ; preds = %err_socket, %if.end17, %if.then2, %if.then
  %22 = load i32, i32* %retval, align 4, !dbg !651
  ret i32 %22, !dbg !651
}

declare i8* @uv__strdup(i8*) #2

declare i32 @uv__socket(i32, i32, i32) #2

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #3

; Function Attrs: nounwind
declare i8* @strncpy(i8*, i8*, i64) #4

; Function Attrs: nounwind
declare i32 @bind(i32, %struct.sockaddr*, i32) #4

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #5

declare i32 @uv__close(i32) #2

declare void @uv__free(i8*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_pipe_listen(%struct.uv_pipe_s* %handle, i32 %backlog, void (%struct.uv_stream_s*, i32)* %cb) #0 !dbg !496 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  %backlog.addr = alloca i32, align 4
  %cb.addr = alloca void (%struct.uv_stream_s*, i32)*, align 8
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !652, metadata !539), !dbg !653
  store i32 %backlog, i32* %backlog.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %backlog.addr, metadata !654, metadata !539), !dbg !655
  store void (%struct.uv_stream_s*, i32)* %cb, void (%struct.uv_stream_s*, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_stream_s*, i32)** %cb.addr, metadata !656, metadata !539), !dbg !657
  %0 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !658
  %io_watcher = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %0, i32 0, i32 13, !dbg !658
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !658
  %1 = load i32, i32* %fd, align 8, !dbg !658
  %cmp = icmp eq i32 %1, -1, !dbg !660
  br i1 %cmp, label %if.then, label %if.end, !dbg !661

if.then:                                          ; preds = %entry
  store i32 -22, i32* %retval, align 4, !dbg !662
  br label %return, !dbg !662

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !663
  %io_watcher1 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %2, i32 0, i32 13, !dbg !663
  %fd2 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher1, i32 0, i32 5, !dbg !663
  %3 = load i32, i32* %fd2, align 8, !dbg !663
  %4 = load i32, i32* %backlog.addr, align 4, !dbg !665
  %call = call i32 @listen(i32 %3, i32 %4) #7, !dbg !666
  %tobool = icmp ne i32 %call, 0, !dbg !666
  br i1 %tobool, label %if.then3, label %if.end5, !dbg !667

if.then3:                                         ; preds = %if.end
  %call4 = call i32* @__errno_location() #1, !dbg !668
  %5 = load i32, i32* %call4, align 4, !dbg !668
  %sub = sub nsw i32 0, %5, !dbg !669
  store i32 %sub, i32* %retval, align 4, !dbg !670
  br label %return, !dbg !670

if.end5:                                          ; preds = %if.end
  %6 = load void (%struct.uv_stream_s*, i32)*, void (%struct.uv_stream_s*, i32)** %cb.addr, align 8, !dbg !671
  %7 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !672
  %connection_cb = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %7, i32 0, i32 16, !dbg !673
  store void (%struct.uv_stream_s*, i32)* %6, void (%struct.uv_stream_s*, i32)** %connection_cb, align 8, !dbg !674
  %8 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !675
  %io_watcher6 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %8, i32 0, i32 13, !dbg !676
  %cb7 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher6, i32 0, i32 0, !dbg !677
  store void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)* @uv__server_io, void (%struct.uv_loop_s*, %struct.uv__io_s*, i32)** %cb7, align 8, !dbg !678
  %9 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !679
  %loop = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %9, i32 0, i32 1, !dbg !680
  %10 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !680
  %11 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !681
  %io_watcher8 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %11, i32 0, i32 13, !dbg !682
  call void @uv__io_start(%struct.uv_loop_s* %10, %struct.uv__io_s* %io_watcher8, i32 1), !dbg !683
  store i32 0, i32* %retval, align 4, !dbg !684
  br label %return, !dbg !684

return:                                           ; preds = %if.end5, %if.then3, %if.then
  %12 = load i32, i32* %retval, align 4, !dbg !685
  ret i32 %12, !dbg !685
}

; Function Attrs: nounwind
declare i32 @listen(i32, i32) #4

declare void @uv__server_io(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

declare void @uv__io_start(%struct.uv_loop_s*, %struct.uv__io_s*, i32) #2

; Function Attrs: nounwind uwtable
define void @uv__pipe_close(%struct.uv_pipe_s* %handle) #0 !dbg !499 {
entry:
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !686, metadata !539), !dbg !687
  %0 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !688
  %pipe_fname = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %0, i32 0, i32 21, !dbg !690
  %1 = load i8*, i8** %pipe_fname, align 8, !dbg !690
  %tobool = icmp ne i8* %1, null, !dbg !688
  br i1 %tobool, label %if.then, label %if.end, !dbg !691

if.then:                                          ; preds = %entry
  %2 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !692
  %pipe_fname1 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %2, i32 0, i32 21, !dbg !694
  %3 = load i8*, i8** %pipe_fname1, align 8, !dbg !694
  %call = call i32 @unlink(i8* %3) #7, !dbg !695
  %4 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !696
  %pipe_fname2 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %4, i32 0, i32 21, !dbg !697
  %5 = load i8*, i8** %pipe_fname2, align 8, !dbg !697
  call void @uv__free(i8* %5), !dbg !698
  %6 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !699
  %pipe_fname3 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %6, i32 0, i32 21, !dbg !700
  store i8* null, i8** %pipe_fname3, align 8, !dbg !701
  br label %if.end, !dbg !702

if.end:                                           ; preds = %if.then, %entry
  %7 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !703
  %8 = bitcast %struct.uv_pipe_s* %7 to %struct.uv_stream_s*, !dbg !704
  call void @uv__stream_close(%struct.uv_stream_s* %8), !dbg !705
  ret void, !dbg !706
}

; Function Attrs: nounwind
declare i32 @unlink(i8*) #4

declare void @uv__stream_close(%struct.uv_stream_s*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_pipe_open(%struct.uv_pipe_s* %handle, i32 %fd) #0 !dbg !502 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  %fd.addr = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !707, metadata !539), !dbg !708
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !709, metadata !539), !dbg !710
  call void @llvm.dbg.declare(metadata i32* %err, metadata !711, metadata !539), !dbg !712
  %0 = load i32, i32* %fd.addr, align 4, !dbg !713
  %call = call i32 @uv__nonblock_ioctl(i32 %0, i32 1), !dbg !714
  store i32 %call, i32* %err, align 4, !dbg !715
  %1 = load i32, i32* %err, align 4, !dbg !716
  %tobool = icmp ne i32 %1, 0, !dbg !716
  br i1 %tobool, label %if.then, label %if.end, !dbg !718

if.then:                                          ; preds = %entry
  %2 = load i32, i32* %err, align 4, !dbg !719
  store i32 %2, i32* %retval, align 4, !dbg !720
  br label %return, !dbg !720

if.end:                                           ; preds = %entry
  %3 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !721
  %4 = bitcast %struct.uv_pipe_s* %3 to %struct.uv_stream_s*, !dbg !722
  %5 = load i32, i32* %fd.addr, align 4, !dbg !723
  %call1 = call i32 @uv__stream_open(%struct.uv_stream_s* %4, i32 %5, i32 96), !dbg !724
  store i32 %call1, i32* %retval, align 4, !dbg !725
  br label %return, !dbg !725

return:                                           ; preds = %if.end, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !726
  ret i32 %6, !dbg !726
}

declare i32 @uv__nonblock_ioctl(i32, i32) #2

declare i32 @uv__stream_open(%struct.uv_stream_s*, i32, i32) #2

; Function Attrs: nounwind uwtable
define void @uv_pipe_connect(%struct.uv_connect_s* %req, %struct.uv_pipe_s* %handle, i8* %name, void (%struct.uv_connect_s*, i32)* %cb) #0 !dbg !506 {
entry:
  %req.addr = alloca %struct.uv_connect_s*, align 8
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  %name.addr = alloca i8*, align 8
  %cb.addr = alloca void (%struct.uv_connect_s*, i32)*, align 8
  %saddr = alloca %struct.sockaddr_un, align 2
  %new_sock = alloca i32, align 4
  %err = alloca i32, align 4
  %r = alloca i32, align 4
  %agg.tmp = alloca %union.__CONST_SOCKADDR_ARG, align 8
  store %struct.uv_connect_s* %req, %struct.uv_connect_s** %req.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_connect_s** %req.addr, metadata !727, metadata !539), !dbg !728
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !729, metadata !539), !dbg !730
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !731, metadata !539), !dbg !732
  store void (%struct.uv_connect_s*, i32)* %cb, void (%struct.uv_connect_s*, i32)** %cb.addr, align 8
  call void @llvm.dbg.declare(metadata void (%struct.uv_connect_s*, i32)** %cb.addr, metadata !733, metadata !539), !dbg !734
  call void @llvm.dbg.declare(metadata %struct.sockaddr_un* %saddr, metadata !735, metadata !539), !dbg !736
  call void @llvm.dbg.declare(metadata i32* %new_sock, metadata !737, metadata !539), !dbg !738
  call void @llvm.dbg.declare(metadata i32* %err, metadata !739, metadata !539), !dbg !740
  call void @llvm.dbg.declare(metadata i32* %r, metadata !741, metadata !539), !dbg !742
  %0 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !743
  %io_watcher = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %0, i32 0, i32 13, !dbg !743
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !743
  %1 = load i32, i32* %fd, align 8, !dbg !743
  %cmp = icmp eq i32 %1, -1, !dbg !744
  %conv = zext i1 %cmp to i32, !dbg !744
  store i32 %conv, i32* %new_sock, align 4, !dbg !745
  %2 = load i32, i32* %new_sock, align 4, !dbg !746
  %tobool = icmp ne i32 %2, 0, !dbg !746
  br i1 %tobool, label %if.then, label %if.end6, !dbg !748

if.then:                                          ; preds = %entry
  %call = call i32 @uv__socket(i32 1, i32 1, i32 0), !dbg !749
  store i32 %call, i32* %err, align 4, !dbg !751
  %3 = load i32, i32* %err, align 4, !dbg !752
  %cmp1 = icmp slt i32 %3, 0, !dbg !754
  br i1 %cmp1, label %if.then3, label %if.end, !dbg !755

if.then3:                                         ; preds = %if.then
  br label %out, !dbg !756

if.end:                                           ; preds = %if.then
  %4 = load i32, i32* %err, align 4, !dbg !757
  %5 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !758
  %io_watcher4 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %5, i32 0, i32 13, !dbg !759
  %fd5 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher4, i32 0, i32 5, !dbg !760
  store i32 %4, i32* %fd5, align 8, !dbg !761
  br label %if.end6, !dbg !762

if.end6:                                          ; preds = %if.end, %entry
  %6 = bitcast %struct.sockaddr_un* %saddr to i8*, !dbg !763
  call void @llvm.memset.p0i8.i64(i8* %6, i8 0, i64 110, i32 2, i1 false), !dbg !763
  %sun_path = getelementptr inbounds %struct.sockaddr_un, %struct.sockaddr_un* %saddr, i32 0, i32 1, !dbg !764
  %arraydecay = getelementptr inbounds [108 x i8], [108 x i8]* %sun_path, i32 0, i32 0, !dbg !765
  %7 = load i8*, i8** %name.addr, align 8, !dbg !766
  %call7 = call i8* @strncpy(i8* %arraydecay, i8* %7, i64 107) #7, !dbg !767
  %sun_path8 = getelementptr inbounds %struct.sockaddr_un, %struct.sockaddr_un* %saddr, i32 0, i32 1, !dbg !768
  %arrayidx = getelementptr inbounds [108 x i8], [108 x i8]* %sun_path8, i64 0, i64 107, !dbg !769
  store i8 0, i8* %arrayidx, align 1, !dbg !770
  %sun_family = getelementptr inbounds %struct.sockaddr_un, %struct.sockaddr_un* %saddr, i32 0, i32 0, !dbg !771
  store i16 1, i16* %sun_family, align 2, !dbg !772
  br label %do.body, !dbg !773

do.body:                                          ; preds = %land.end, %if.end6
  %8 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !774
  %io_watcher9 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %8, i32 0, i32 13, !dbg !774
  %fd10 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher9, i32 0, i32 5, !dbg !774
  %9 = load i32, i32* %fd10, align 8, !dbg !774
  %__sockaddr__ = bitcast %union.__CONST_SOCKADDR_ARG* %agg.tmp to %struct.sockaddr**, !dbg !776
  %10 = bitcast %struct.sockaddr_un* %saddr to %struct.sockaddr*, !dbg !776
  store %struct.sockaddr* %10, %struct.sockaddr** %__sockaddr__, align 8, !dbg !776
  %coerce.dive = getelementptr inbounds %union.__CONST_SOCKADDR_ARG, %union.__CONST_SOCKADDR_ARG* %agg.tmp, i32 0, i32 0, !dbg !777
  %11 = load %struct.sockaddr*, %struct.sockaddr** %coerce.dive, align 8, !dbg !777
  %call11 = call i32 @connect(i32 %9, %struct.sockaddr* %11, i32 110), !dbg !777
  store i32 %call11, i32* %r, align 4, !dbg !778
  br label %do.cond, !dbg !779

do.cond:                                          ; preds = %do.body
  %12 = load i32, i32* %r, align 4, !dbg !780
  %cmp12 = icmp eq i32 %12, -1, !dbg !781
  br i1 %cmp12, label %land.rhs, label %land.end, !dbg !782

land.rhs:                                         ; preds = %do.cond
  %call14 = call i32* @__errno_location() #1, !dbg !783
  %13 = load i32, i32* %call14, align 4, !dbg !783
  %cmp15 = icmp eq i32 %13, 4, !dbg !785
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %14 = phi i1 [ false, %do.cond ], [ %cmp15, %land.rhs ]
  br i1 %14, label %do.body, label %do.end, !dbg !786

do.end:                                           ; preds = %land.end
  %15 = load i32, i32* %r, align 4, !dbg !788
  %cmp17 = icmp eq i32 %15, -1, !dbg !790
  br i1 %cmp17, label %land.lhs.true, label %if.end24, !dbg !791

land.lhs.true:                                    ; preds = %do.end
  %call19 = call i32* @__errno_location() #1, !dbg !792
  %16 = load i32, i32* %call19, align 4, !dbg !792
  %cmp20 = icmp ne i32 %16, 115, !dbg !794
  br i1 %cmp20, label %if.then22, label %if.end24, !dbg !795

if.then22:                                        ; preds = %land.lhs.true
  %call23 = call i32* @__errno_location() #1, !dbg !796
  %17 = load i32, i32* %call23, align 4, !dbg !796
  %sub = sub nsw i32 0, %17, !dbg !798
  store i32 %sub, i32* %err, align 4, !dbg !799
  br label %out, !dbg !800

if.end24:                                         ; preds = %land.lhs.true, %do.end
  store i32 0, i32* %err, align 4, !dbg !801
  %18 = load i32, i32* %new_sock, align 4, !dbg !802
  %tobool25 = icmp ne i32 %18, 0, !dbg !802
  br i1 %tobool25, label %if.then26, label %if.end30, !dbg !804

if.then26:                                        ; preds = %if.end24
  %19 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !805
  %20 = bitcast %struct.uv_pipe_s* %19 to %struct.uv_stream_s*, !dbg !807
  %21 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !808
  %io_watcher27 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %21, i32 0, i32 13, !dbg !808
  %fd28 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher27, i32 0, i32 5, !dbg !808
  %22 = load i32, i32* %fd28, align 8, !dbg !808
  %call29 = call i32 @uv__stream_open(%struct.uv_stream_s* %20, i32 %22, i32 96), !dbg !809
  store i32 %call29, i32* %err, align 4, !dbg !810
  br label %if.end30, !dbg !811

if.end30:                                         ; preds = %if.then26, %if.end24
  %23 = load i32, i32* %err, align 4, !dbg !812
  %cmp31 = icmp eq i32 %23, 0, !dbg !814
  br i1 %cmp31, label %if.then33, label %if.end35, !dbg !815

if.then33:                                        ; preds = %if.end30
  %24 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !816
  %loop = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %24, i32 0, i32 1, !dbg !817
  %25 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !817
  %26 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !818
  %io_watcher34 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %26, i32 0, i32 13, !dbg !819
  call void @uv__io_start(%struct.uv_loop_s* %25, %struct.uv__io_s* %io_watcher34, i32 5), !dbg !820
  br label %if.end35, !dbg !820

if.end35:                                         ; preds = %if.then33, %if.end30
  br label %out, !dbg !821

out:                                              ; preds = %if.end35, %if.then22, %if.then3
  %27 = load i32, i32* %err, align 4, !dbg !823
  %28 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !824
  %delayed_error = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %28, i32 0, i32 17, !dbg !825
  store i32 %27, i32* %delayed_error, align 8, !dbg !826
  %29 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !827
  %30 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !828
  %connect_req = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %30, i32 0, i32 11, !dbg !829
  store %struct.uv_connect_s* %29, %struct.uv_connect_s** %connect_req, align 8, !dbg !830
  br label %do.body36, !dbg !831

do.body36:                                        ; preds = %out
  br label %do.body37, !dbg !832

do.body37:                                        ; preds = %do.body36
  %31 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !835
  %type = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %31, i32 0, i32 1, !dbg !835
  store i32 2, i32* %type, align 8, !dbg !835
  br label %do.end39, !dbg !835

do.end39:                                         ; preds = %do.body37
  br label %do.body40, !dbg !838

do.body40:                                        ; preds = %do.end39
  br label %do.body41, !dbg !840

do.body41:                                        ; preds = %do.body40
  %32 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !843
  %loop42 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %32, i32 0, i32 1, !dbg !843
  %33 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop42, align 8, !dbg !843
  %active_reqs = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %33, i32 0, i32 3, !dbg !843
  %34 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !843
  %active_queue = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %34, i32 0, i32 2, !dbg !843
  %arrayidx43 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue, i64 0, i64 0, !dbg !843
  %35 = bitcast i8** %arrayidx43 to [2 x i8*]**, !dbg !843
  store [2 x i8*]* %active_reqs, [2 x i8*]** %35, align 8, !dbg !843
  %36 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !843
  %loop44 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %36, i32 0, i32 1, !dbg !843
  %37 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop44, align 8, !dbg !843
  %active_reqs45 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %37, i32 0, i32 3, !dbg !843
  %arrayidx46 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs45, i64 0, i64 1, !dbg !843
  %38 = bitcast i8** %arrayidx46 to [2 x i8*]**, !dbg !843
  %39 = load [2 x i8*]*, [2 x i8*]** %38, align 8, !dbg !843
  %40 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !843
  %active_queue47 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %40, i32 0, i32 2, !dbg !843
  %arrayidx48 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue47, i64 0, i64 1, !dbg !843
  %41 = bitcast i8** %arrayidx48 to [2 x i8*]**, !dbg !843
  store [2 x i8*]* %39, [2 x i8*]** %41, align 8, !dbg !843
  %42 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !843
  %active_queue49 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %42, i32 0, i32 2, !dbg !843
  %43 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !843
  %active_queue50 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %43, i32 0, i32 2, !dbg !843
  %arrayidx51 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_queue50, i64 0, i64 1, !dbg !843
  %44 = bitcast i8** %arrayidx51 to [2 x i8*]**, !dbg !843
  %45 = load [2 x i8*]*, [2 x i8*]** %44, align 8, !dbg !843
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %45, i64 0, i64 0, !dbg !843
  %46 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !843
  store [2 x i8*]* %active_queue49, [2 x i8*]** %46, align 8, !dbg !843
  %47 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !843
  %active_queue53 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %47, i32 0, i32 2, !dbg !843
  %48 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !843
  %loop54 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %48, i32 0, i32 1, !dbg !843
  %49 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop54, align 8, !dbg !843
  %active_reqs55 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %49, i32 0, i32 3, !dbg !843
  %arrayidx56 = getelementptr inbounds [2 x i8*], [2 x i8*]* %active_reqs55, i64 0, i64 1, !dbg !843
  %50 = bitcast i8** %arrayidx56 to [2 x i8*]**, !dbg !843
  store [2 x i8*]* %active_queue53, [2 x i8*]** %50, align 8, !dbg !843
  br label %do.end58, !dbg !843

do.end58:                                         ; preds = %do.body41
  br label %do.end60, !dbg !846

do.end60:                                         ; preds = %do.end58
  br label %do.end62, !dbg !848

do.end62:                                         ; preds = %do.end60
  %51 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !850
  %52 = bitcast %struct.uv_pipe_s* %51 to %struct.uv_stream_s*, !dbg !851
  %53 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !852
  %handle63 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %53, i32 0, i32 5, !dbg !853
  store %struct.uv_stream_s* %52, %struct.uv_stream_s** %handle63, align 8, !dbg !854
  %54 = load void (%struct.uv_connect_s*, i32)*, void (%struct.uv_connect_s*, i32)** %cb.addr, align 8, !dbg !855
  %55 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !856
  %cb64 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %55, i32 0, i32 4, !dbg !857
  store void (%struct.uv_connect_s*, i32)* %54, void (%struct.uv_connect_s*, i32)** %cb64, align 8, !dbg !858
  br label %do.body65, !dbg !859

do.body65:                                        ; preds = %do.end62
  %56 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !860
  %queue = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %56, i32 0, i32 6, !dbg !860
  %57 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !860
  %queue66 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %57, i32 0, i32 6, !dbg !860
  %arrayidx67 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue66, i64 0, i64 0, !dbg !860
  %58 = bitcast i8** %arrayidx67 to [2 x i8*]**, !dbg !860
  store [2 x i8*]* %queue, [2 x i8*]** %58, align 8, !dbg !860
  %59 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !860
  %queue68 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %59, i32 0, i32 6, !dbg !860
  %60 = load %struct.uv_connect_s*, %struct.uv_connect_s** %req.addr, align 8, !dbg !860
  %queue69 = getelementptr inbounds %struct.uv_connect_s, %struct.uv_connect_s* %60, i32 0, i32 6, !dbg !860
  %arrayidx70 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue69, i64 0, i64 1, !dbg !860
  %61 = bitcast i8** %arrayidx70 to [2 x i8*]**, !dbg !860
  store [2 x i8*]* %queue68, [2 x i8*]** %61, align 8, !dbg !860
  br label %do.end72, !dbg !860

do.end72:                                         ; preds = %do.body65
  %62 = load i32, i32* %err, align 4, !dbg !863
  %tobool73 = icmp ne i32 %62, 0, !dbg !863
  br i1 %tobool73, label %if.then74, label %if.end77, !dbg !865

if.then74:                                        ; preds = %do.end72
  %63 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !866
  %loop75 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %63, i32 0, i32 1, !dbg !867
  %64 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop75, align 8, !dbg !867
  %65 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !868
  %io_watcher76 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %65, i32 0, i32 13, !dbg !869
  call void @uv__io_feed(%struct.uv_loop_s* %64, %struct.uv__io_s* %io_watcher76), !dbg !870
  br label %if.end77, !dbg !870

if.end77:                                         ; preds = %if.then74, %do.end72
  ret void, !dbg !871
}

declare i32 @connect(i32, %struct.sockaddr*, i32) #2

declare void @uv__io_feed(%struct.uv_loop_s*, %struct.uv__io_s*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_pipe_getsockname(%struct.uv_pipe_s* %handle, i8* %buffer, i64* %size) #0 !dbg !509 {
entry:
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64*, align 8
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !872, metadata !539), !dbg !873
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !874, metadata !539), !dbg !875
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !876, metadata !539), !dbg !877
  %0 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !878
  %1 = load i8*, i8** %buffer.addr, align 8, !dbg !879
  %2 = load i64*, i64** %size.addr, align 8, !dbg !880
  %call = call i32 @uv__pipe_getsockpeername(%struct.uv_pipe_s* %0, i32 (i32, %struct.sockaddr*, i32*)* @getsockname, i8* %1, i64* %2), !dbg !881
  ret i32 %call, !dbg !882
}

; Function Attrs: nounwind uwtable
define internal i32 @uv__pipe_getsockpeername(%struct.uv_pipe_s* %handle, i32 (i32, %struct.sockaddr*, i32*)* %func, i8* %buffer, i64* %size) #0 !dbg !525 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  %func.addr = alloca i32 (i32, %struct.sockaddr*, i32*)*, align 8
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64*, align 8
  %sa = alloca %struct.sockaddr_un, align 2
  %addrlen = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !883, metadata !539), !dbg !884
  store i32 (i32, %struct.sockaddr*, i32*)* %func, i32 (i32, %struct.sockaddr*, i32*)** %func.addr, align 8
  call void @llvm.dbg.declare(metadata i32 (i32, %struct.sockaddr*, i32*)** %func.addr, metadata !885, metadata !539), !dbg !886
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !887, metadata !539), !dbg !888
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !889, metadata !539), !dbg !890
  call void @llvm.dbg.declare(metadata %struct.sockaddr_un* %sa, metadata !891, metadata !539), !dbg !892
  call void @llvm.dbg.declare(metadata i32* %addrlen, metadata !893, metadata !539), !dbg !894
  call void @llvm.dbg.declare(metadata i32* %err, metadata !895, metadata !539), !dbg !896
  store i32 110, i32* %addrlen, align 4, !dbg !897
  %0 = bitcast %struct.sockaddr_un* %sa to i8*, !dbg !898
  %1 = load i32, i32* %addrlen, align 4, !dbg !899
  %conv = zext i32 %1 to i64, !dbg !899
  call void @llvm.memset.p0i8.i64(i8* %0, i8 0, i64 %conv, i32 2, i1 false), !dbg !898
  %2 = load i32 (i32, %struct.sockaddr*, i32*)*, i32 (i32, %struct.sockaddr*, i32*)** %func.addr, align 8, !dbg !900
  %3 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !901
  %io_watcher = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %3, i32 0, i32 13, !dbg !901
  %fd = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !901
  %4 = load i32, i32* %fd, align 8, !dbg !901
  %5 = bitcast %struct.sockaddr_un* %sa to %struct.sockaddr*, !dbg !902
  %call = call i32 %2(i32 %4, %struct.sockaddr* %5, i32* %addrlen), !dbg !900
  store i32 %call, i32* %err, align 4, !dbg !903
  %6 = load i32, i32* %err, align 4, !dbg !904
  %cmp = icmp slt i32 %6, 0, !dbg !906
  br i1 %cmp, label %if.then, label %if.end, !dbg !907

if.then:                                          ; preds = %entry
  %7 = load i64*, i64** %size.addr, align 8, !dbg !908
  store i64 0, i64* %7, align 8, !dbg !910
  %call2 = call i32* @__errno_location() #1, !dbg !911
  %8 = load i32, i32* %call2, align 4, !dbg !911
  %sub = sub nsw i32 0, %8, !dbg !912
  store i32 %sub, i32* %retval, align 4, !dbg !913
  br label %return, !dbg !913

if.end:                                           ; preds = %entry
  %sun_path = getelementptr inbounds %struct.sockaddr_un, %struct.sockaddr_un* %sa, i32 0, i32 1, !dbg !914
  %arrayidx = getelementptr inbounds [108 x i8], [108 x i8]* %sun_path, i64 0, i64 0, !dbg !916
  %9 = load i8, i8* %arrayidx, align 2, !dbg !916
  %conv3 = sext i8 %9 to i32, !dbg !916
  %cmp4 = icmp eq i32 %conv3, 0, !dbg !917
  br i1 %cmp4, label %if.then6, label %if.else, !dbg !918

if.then6:                                         ; preds = %if.end
  %10 = load i32, i32* %addrlen, align 4, !dbg !919
  %conv7 = zext i32 %10 to i64, !dbg !919
  %sub8 = sub i64 %conv7, 2, !dbg !919
  %conv9 = trunc i64 %sub8 to i32, !dbg !919
  store i32 %conv9, i32* %addrlen, align 4, !dbg !919
  br label %if.end13, !dbg !920

if.else:                                          ; preds = %if.end
  %sun_path10 = getelementptr inbounds %struct.sockaddr_un, %struct.sockaddr_un* %sa, i32 0, i32 1, !dbg !921
  %arraydecay = getelementptr inbounds [108 x i8], [108 x i8]* %sun_path10, i32 0, i32 0, !dbg !922
  %call11 = call i64 @strlen(i8* %arraydecay) #8, !dbg !923
  %conv12 = trunc i64 %call11 to i32, !dbg !923
  store i32 %conv12, i32* %addrlen, align 4, !dbg !924
  br label %if.end13

if.end13:                                         ; preds = %if.else, %if.then6
  %11 = load i32, i32* %addrlen, align 4, !dbg !925
  %conv14 = zext i32 %11 to i64, !dbg !925
  %12 = load i64*, i64** %size.addr, align 8, !dbg !927
  %13 = load i64, i64* %12, align 8, !dbg !928
  %cmp15 = icmp uge i64 %conv14, %13, !dbg !929
  br i1 %cmp15, label %if.then17, label %if.end19, !dbg !930

if.then17:                                        ; preds = %if.end13
  %14 = load i32, i32* %addrlen, align 4, !dbg !931
  %add = add i32 %14, 1, !dbg !933
  %conv18 = zext i32 %add to i64, !dbg !931
  %15 = load i64*, i64** %size.addr, align 8, !dbg !934
  store i64 %conv18, i64* %15, align 8, !dbg !935
  store i32 -105, i32* %retval, align 4, !dbg !936
  br label %return, !dbg !936

if.end19:                                         ; preds = %if.end13
  %16 = load i8*, i8** %buffer.addr, align 8, !dbg !937
  %sun_path20 = getelementptr inbounds %struct.sockaddr_un, %struct.sockaddr_un* %sa, i32 0, i32 1, !dbg !938
  %arraydecay21 = getelementptr inbounds [108 x i8], [108 x i8]* %sun_path20, i32 0, i32 0, !dbg !939
  %17 = load i32, i32* %addrlen, align 4, !dbg !940
  %conv22 = zext i32 %17 to i64, !dbg !940
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %16, i8* %arraydecay21, i64 %conv22, i32 1, i1 false), !dbg !939
  %18 = load i32, i32* %addrlen, align 4, !dbg !941
  %conv23 = zext i32 %18 to i64, !dbg !941
  %19 = load i64*, i64** %size.addr, align 8, !dbg !942
  store i64 %conv23, i64* %19, align 8, !dbg !943
  %20 = load i8*, i8** %buffer.addr, align 8, !dbg !944
  %arrayidx24 = getelementptr inbounds i8, i8* %20, i64 0, !dbg !944
  %21 = load i8, i8* %arrayidx24, align 1, !dbg !944
  %conv25 = sext i8 %21 to i32, !dbg !944
  %cmp26 = icmp ne i32 %conv25, 0, !dbg !946
  br i1 %cmp26, label %if.then28, label %if.end30, !dbg !947

if.then28:                                        ; preds = %if.end19
  %22 = load i32, i32* %addrlen, align 4, !dbg !948
  %idxprom = zext i32 %22 to i64, !dbg !949
  %23 = load i8*, i8** %buffer.addr, align 8, !dbg !949
  %arrayidx29 = getelementptr inbounds i8, i8* %23, i64 %idxprom, !dbg !949
  store i8 0, i8* %arrayidx29, align 1, !dbg !950
  br label %if.end30, !dbg !949

if.end30:                                         ; preds = %if.then28, %if.end19
  store i32 0, i32* %retval, align 4, !dbg !951
  br label %return, !dbg !951

return:                                           ; preds = %if.end30, %if.then17, %if.then
  %24 = load i32, i32* %retval, align 4, !dbg !952
  ret i32 %24, !dbg !952
}

; Function Attrs: nounwind
declare i32 @getsockname(i32, %struct.sockaddr*, i32*) #4

; Function Attrs: nounwind uwtable
define i32 @uv_pipe_getpeername(%struct.uv_pipe_s* %handle, i8* %buffer, i64* %size) #0 !dbg !515 {
entry:
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  %buffer.addr = alloca i8*, align 8
  %size.addr = alloca i64*, align 8
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !953, metadata !539), !dbg !954
  store i8* %buffer, i8** %buffer.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buffer.addr, metadata !955, metadata !539), !dbg !956
  store i64* %size, i64** %size.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %size.addr, metadata !957, metadata !539), !dbg !958
  %0 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !959
  %1 = load i8*, i8** %buffer.addr, align 8, !dbg !960
  %2 = load i64*, i64** %size.addr, align 8, !dbg !961
  %call = call i32 @uv__pipe_getsockpeername(%struct.uv_pipe_s* %0, i32 (i32, %struct.sockaddr*, i32*)* @getpeername, i8* %1, i64* %2), !dbg !962
  ret i32 %call, !dbg !963
}

; Function Attrs: nounwind
declare i32 @getpeername(i32, %struct.sockaddr*, i32*) #4

; Function Attrs: nounwind uwtable
define void @uv_pipe_pending_instances(%struct.uv_pipe_s* %handle, i32 %count) #0 !dbg !516 {
entry:
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  %count.addr = alloca i32, align 4
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !964, metadata !539), !dbg !965
  store i32 %count, i32* %count.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %count.addr, metadata !966, metadata !539), !dbg !967
  ret void, !dbg !968
}

; Function Attrs: nounwind uwtable
define i32 @uv_pipe_pending_count(%struct.uv_pipe_s* %handle) #0 !dbg !519 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  %queued_fds = alloca %struct.uv__stream_queued_fds_s*, align 8
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !969, metadata !539), !dbg !970
  call void @llvm.dbg.declare(metadata %struct.uv__stream_queued_fds_s** %queued_fds, metadata !971, metadata !539), !dbg !982
  %0 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !983
  %ipc = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %0, i32 0, i32 20, !dbg !985
  %1 = load i32, i32* %ipc, align 8, !dbg !985
  %tobool = icmp ne i32 %1, 0, !dbg !983
  br i1 %tobool, label %if.end, label %if.then, !dbg !986

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !987
  br label %return, !dbg !987

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !988
  %accepted_fd = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %2, i32 0, i32 18, !dbg !990
  %3 = load i32, i32* %accepted_fd, align 4, !dbg !990
  %cmp = icmp eq i32 %3, -1, !dbg !991
  br i1 %cmp, label %if.then1, label %if.end2, !dbg !992

if.then1:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !993
  br label %return, !dbg !993

if.end2:                                          ; preds = %if.end
  %4 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !994
  %queued_fds3 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %4, i32 0, i32 19, !dbg !996
  %5 = load i8*, i8** %queued_fds3, align 8, !dbg !996
  %cmp4 = icmp eq i8* %5, null, !dbg !997
  br i1 %cmp4, label %if.then5, label %if.end6, !dbg !998

if.then5:                                         ; preds = %if.end2
  store i32 1, i32* %retval, align 4, !dbg !999
  br label %return, !dbg !999

if.end6:                                          ; preds = %if.end2
  %6 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !1000
  %queued_fds7 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %6, i32 0, i32 19, !dbg !1001
  %7 = load i8*, i8** %queued_fds7, align 8, !dbg !1001
  %8 = bitcast i8* %7 to %struct.uv__stream_queued_fds_s*, !dbg !1000
  store %struct.uv__stream_queued_fds_s* %8, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !1002
  %9 = load %struct.uv__stream_queued_fds_s*, %struct.uv__stream_queued_fds_s** %queued_fds, align 8, !dbg !1003
  %offset = getelementptr inbounds %struct.uv__stream_queued_fds_s, %struct.uv__stream_queued_fds_s* %9, i32 0, i32 1, !dbg !1004
  %10 = load i32, i32* %offset, align 4, !dbg !1004
  %add = add i32 %10, 1, !dbg !1005
  store i32 %add, i32* %retval, align 4, !dbg !1006
  br label %return, !dbg !1006

return:                                           ; preds = %if.end6, %if.then5, %if.then1, %if.then
  %11 = load i32, i32* %retval, align 4, !dbg !1007
  ret i32 %11, !dbg !1007
}

; Function Attrs: nounwind uwtable
define i32 @uv_pipe_pending_type(%struct.uv_pipe_s* %handle) #0 !dbg !522 {
entry:
  %retval = alloca i32, align 4
  %handle.addr = alloca %struct.uv_pipe_s*, align 8
  store %struct.uv_pipe_s* %handle, %struct.uv_pipe_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_pipe_s** %handle.addr, metadata !1008, metadata !539), !dbg !1009
  %0 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !1010
  %ipc = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %0, i32 0, i32 20, !dbg !1012
  %1 = load i32, i32* %ipc, align 8, !dbg !1012
  %tobool = icmp ne i32 %1, 0, !dbg !1010
  br i1 %tobool, label %if.end, label %if.then, !dbg !1013

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1014
  br label %return, !dbg !1014

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !1015
  %accepted_fd = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %2, i32 0, i32 18, !dbg !1017
  %3 = load i32, i32* %accepted_fd, align 4, !dbg !1017
  %cmp = icmp eq i32 %3, -1, !dbg !1018
  br i1 %cmp, label %if.then1, label %if.else, !dbg !1019

if.then1:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !1020
  br label %return, !dbg !1020

if.else:                                          ; preds = %if.end
  %4 = load %struct.uv_pipe_s*, %struct.uv_pipe_s** %handle.addr, align 8, !dbg !1021
  %accepted_fd2 = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %4, i32 0, i32 18, !dbg !1022
  %5 = load i32, i32* %accepted_fd2, align 4, !dbg !1022
  %call = call i32 @uv__handle_type(i32 %5), !dbg !1023
  store i32 %call, i32* %retval, align 4, !dbg !1024
  br label %return, !dbg !1024

return:                                           ; preds = %if.else, %if.then1, %if.then
  %6 = load i32, i32* %retval, align 4, !dbg !1025
  ret i32 %6, !dbg !1025
}

declare i32 @uv__handle_type(i32) #2

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #6

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #3

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind }
attributes #4 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!535, !536}
!llvm.ident = !{!537}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !148, subprograms: !456)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/pipe.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !25, !38, !50, !69}
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
!38 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !39, line: 24, size: 32, align: 32, elements: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!40 = !{!41, !42, !43, !44, !45, !46, !47, !48, !49}
!41 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!42 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!43 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!44 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!45 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!46 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!47 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!48 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!49 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!50 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !51, line: 124, size: 32, align: 32, elements: !52)
!51 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!52 = !{!53, !54, !55, !56, !57, !58, !59, !60, !61, !62, !63, !64, !65, !66, !67, !68}
!53 = !DIEnumerator(name: "UV_CLOSING", value: 1)
!54 = !DIEnumerator(name: "UV_CLOSED", value: 2)
!55 = !DIEnumerator(name: "UV_STREAM_READING", value: 4)
!56 = !DIEnumerator(name: "UV_STREAM_SHUTTING", value: 8)
!57 = !DIEnumerator(name: "UV_STREAM_SHUT", value: 16)
!58 = !DIEnumerator(name: "UV_STREAM_READABLE", value: 32)
!59 = !DIEnumerator(name: "UV_STREAM_WRITABLE", value: 64)
!60 = !DIEnumerator(name: "UV_STREAM_BLOCKING", value: 128)
!61 = !DIEnumerator(name: "UV_STREAM_READ_PARTIAL", value: 256)
!62 = !DIEnumerator(name: "UV_STREAM_READ_EOF", value: 512)
!63 = !DIEnumerator(name: "UV_TCP_NODELAY", value: 1024)
!64 = !DIEnumerator(name: "UV_TCP_KEEPALIVE", value: 2048)
!65 = !DIEnumerator(name: "UV_TCP_SINGLE_ACCEPT", value: 4096)
!66 = !DIEnumerator(name: "UV_HANDLE_IPV6", value: 65536)
!67 = !DIEnumerator(name: "UV_UDP_PROCESSING", value: 131072)
!68 = !DIEnumerator(name: "UV_HANDLE_BOUND", value: 262144)
!69 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !4, line: 177, size: 32, align: 32, elements: !70)
!70 = !{!71, !72, !73, !74, !75, !76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91, !92, !93, !94, !95, !96, !97, !98, !99, !100, !101, !102, !103, !104, !105, !106, !107, !108, !109, !110, !111, !112, !113, !114, !115, !116, !117, !118, !119, !120, !121, !122, !123, !124, !125, !126, !127, !128, !129, !130, !131, !132, !133, !134, !135, !136, !137, !138, !139, !140, !141, !142, !143, !144, !145, !146, !147}
!71 = !DIEnumerator(name: "UV_E2BIG", value: -7)
!72 = !DIEnumerator(name: "UV_EACCES", value: -13)
!73 = !DIEnumerator(name: "UV_EADDRINUSE", value: -98)
!74 = !DIEnumerator(name: "UV_EADDRNOTAVAIL", value: -99)
!75 = !DIEnumerator(name: "UV_EAFNOSUPPORT", value: -97)
!76 = !DIEnumerator(name: "UV_EAGAIN", value: -11)
!77 = !DIEnumerator(name: "UV_EAI_ADDRFAMILY", value: -3000)
!78 = !DIEnumerator(name: "UV_EAI_AGAIN", value: -3001)
!79 = !DIEnumerator(name: "UV_EAI_BADFLAGS", value: -3002)
!80 = !DIEnumerator(name: "UV_EAI_BADHINTS", value: -3013)
!81 = !DIEnumerator(name: "UV_EAI_CANCELED", value: -3003)
!82 = !DIEnumerator(name: "UV_EAI_FAIL", value: -3004)
!83 = !DIEnumerator(name: "UV_EAI_FAMILY", value: -3005)
!84 = !DIEnumerator(name: "UV_EAI_MEMORY", value: -3006)
!85 = !DIEnumerator(name: "UV_EAI_NODATA", value: -3007)
!86 = !DIEnumerator(name: "UV_EAI_NONAME", value: -3008)
!87 = !DIEnumerator(name: "UV_EAI_OVERFLOW", value: -3009)
!88 = !DIEnumerator(name: "UV_EAI_PROTOCOL", value: -3014)
!89 = !DIEnumerator(name: "UV_EAI_SERVICE", value: -3010)
!90 = !DIEnumerator(name: "UV_EAI_SOCKTYPE", value: -3011)
!91 = !DIEnumerator(name: "UV_EALREADY", value: -114)
!92 = !DIEnumerator(name: "UV_EBADF", value: -9)
!93 = !DIEnumerator(name: "UV_EBUSY", value: -16)
!94 = !DIEnumerator(name: "UV_ECANCELED", value: -125)
!95 = !DIEnumerator(name: "UV_ECHARSET", value: -4080)
!96 = !DIEnumerator(name: "UV_ECONNABORTED", value: -103)
!97 = !DIEnumerator(name: "UV_ECONNREFUSED", value: -111)
!98 = !DIEnumerator(name: "UV_ECONNRESET", value: -104)
!99 = !DIEnumerator(name: "UV_EDESTADDRREQ", value: -89)
!100 = !DIEnumerator(name: "UV_EEXIST", value: -17)
!101 = !DIEnumerator(name: "UV_EFAULT", value: -14)
!102 = !DIEnumerator(name: "UV_EFBIG", value: -27)
!103 = !DIEnumerator(name: "UV_EHOSTUNREACH", value: -113)
!104 = !DIEnumerator(name: "UV_EINTR", value: -4)
!105 = !DIEnumerator(name: "UV_EINVAL", value: -22)
!106 = !DIEnumerator(name: "UV_EIO", value: -5)
!107 = !DIEnumerator(name: "UV_EISCONN", value: -106)
!108 = !DIEnumerator(name: "UV_EISDIR", value: -21)
!109 = !DIEnumerator(name: "UV_ELOOP", value: -40)
!110 = !DIEnumerator(name: "UV_EMFILE", value: -24)
!111 = !DIEnumerator(name: "UV_EMSGSIZE", value: -90)
!112 = !DIEnumerator(name: "UV_ENAMETOOLONG", value: -36)
!113 = !DIEnumerator(name: "UV_ENETDOWN", value: -100)
!114 = !DIEnumerator(name: "UV_ENETUNREACH", value: -101)
!115 = !DIEnumerator(name: "UV_ENFILE", value: -23)
!116 = !DIEnumerator(name: "UV_ENOBUFS", value: -105)
!117 = !DIEnumerator(name: "UV_ENODEV", value: -19)
!118 = !DIEnumerator(name: "UV_ENOENT", value: -2)
!119 = !DIEnumerator(name: "UV_ENOMEM", value: -12)
!120 = !DIEnumerator(name: "UV_ENONET", value: -64)
!121 = !DIEnumerator(name: "UV_ENOPROTOOPT", value: -92)
!122 = !DIEnumerator(name: "UV_ENOSPC", value: -28)
!123 = !DIEnumerator(name: "UV_ENOSYS", value: -38)
!124 = !DIEnumerator(name: "UV_ENOTCONN", value: -107)
!125 = !DIEnumerator(name: "UV_ENOTDIR", value: -20)
!126 = !DIEnumerator(name: "UV_ENOTEMPTY", value: -39)
!127 = !DIEnumerator(name: "UV_ENOTSOCK", value: -88)
!128 = !DIEnumerator(name: "UV_ENOTSUP", value: -95)
!129 = !DIEnumerator(name: "UV_EPERM", value: -1)
!130 = !DIEnumerator(name: "UV_EPIPE", value: -32)
!131 = !DIEnumerator(name: "UV_EPROTO", value: -71)
!132 = !DIEnumerator(name: "UV_EPROTONOSUPPORT", value: -93)
!133 = !DIEnumerator(name: "UV_EPROTOTYPE", value: -91)
!134 = !DIEnumerator(name: "UV_ERANGE", value: -34)
!135 = !DIEnumerator(name: "UV_EROFS", value: -30)
!136 = !DIEnumerator(name: "UV_ESHUTDOWN", value: -108)
!137 = !DIEnumerator(name: "UV_ESPIPE", value: -29)
!138 = !DIEnumerator(name: "UV_ESRCH", value: -3)
!139 = !DIEnumerator(name: "UV_ETIMEDOUT", value: -110)
!140 = !DIEnumerator(name: "UV_ETXTBSY", value: -26)
!141 = !DIEnumerator(name: "UV_EXDEV", value: -18)
!142 = !DIEnumerator(name: "UV_UNKNOWN", value: -4094)
!143 = !DIEnumerator(name: "UV_EOF", value: -4095)
!144 = !DIEnumerator(name: "UV_ENXIO", value: -6)
!145 = !DIEnumerator(name: "UV_EMLINK", value: -31)
!146 = !DIEnumerator(name: "UV_EHOSTDOWN", value: -112)
!147 = !DIEnumerator(name: "UV_ERRNO_MAX", value: -4096)
!148 = !{!149, !154, !440, !452}
!149 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !150, size: 64, align: 64)
!150 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stream_t", file: !4, line: 206, baseType: !151)
!151 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_stream_s", file: !4, line: 465, size: 1984, align: 64, elements: !152)
!152 = !{!153, !155, !361, !362, !363, !364, !369, !370, !371, !374, !386, !397, !414, !429, !430, !431, !432, !437, !438, !439}
!153 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !151, file: !4, line: 466, baseType: !154, size: 64, align: 64)
!154 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !151, file: !4, line: 466, baseType: !156, size: 64, align: 64, offset: 64)
!156 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !157, size: 64, align: 64)
!157 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !4, line: 204, baseType: !158)
!158 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !4, line: 1473, size: 6784, align: 64, elements: !159)
!159 = !{!160, !161, !163, !167, !168, !169, !171, !173, !174, !175, !194, !195, !196, !197, !228, !276, !300, !301, !302, !303, !304, !305, !306, !310, !311, !312, !317, !320, !321, !323, !324, !357, !358, !359, !360}
!160 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !158, file: !4, line: 1475, baseType: !154, size: 64, align: 64)
!161 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !158, file: !4, line: 1477, baseType: !162, size: 32, align: 32, offset: 64)
!162 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!163 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !158, file: !4, line: 1478, baseType: !164, size: 128, align: 64, offset: 128)
!164 = !DICompositeType(tag: DW_TAG_array_type, baseType: !154, size: 128, align: 64, elements: !165)
!165 = !{!166}
!166 = !DISubrange(count: 2)
!167 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !158, file: !4, line: 1479, baseType: !164, size: 128, align: 64, offset: 256)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !158, file: !4, line: 1481, baseType: !162, size: 32, align: 32, offset: 384)
!169 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !158, file: !4, line: 1482, baseType: !170, size: 64, align: 64, offset: 448)
!170 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!171 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !158, file: !4, line: 1482, baseType: !172, size: 32, align: 32, offset: 512)
!172 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!173 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !158, file: !4, line: 1482, baseType: !164, size: 128, align: 64, offset: 576)
!174 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !158, file: !4, line: 1482, baseType: !164, size: 128, align: 64, offset: 704)
!175 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !158, file: !4, line: 1482, baseType: !176, size: 64, align: 64, offset: 832)
!176 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !177, size: 64, align: 64)
!177 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !178, size: 64, align: 64)
!178 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !179, line: 87, baseType: !180)
!179 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!180 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !179, line: 89, size: 448, align: 64, elements: !181)
!181 = !{!182, !189, !190, !191, !192, !193}
!182 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !180, file: !179, line: 90, baseType: !183, size: 64, align: 64)
!183 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !179, line: 84, baseType: !184)
!184 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !185, size: 64, align: 64)
!185 = !DISubroutineType(types: !186)
!186 = !{null, !187, !188, !162}
!187 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !158, size: 64, align: 64)
!188 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !180, size: 64, align: 64)
!189 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !180, file: !179, line: 91, baseType: !164, size: 128, align: 64, offset: 64)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !180, file: !179, line: 92, baseType: !164, size: 128, align: 64, offset: 192)
!191 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !180, file: !179, line: 93, baseType: !162, size: 32, align: 32, offset: 320)
!192 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !180, file: !179, line: 94, baseType: !162, size: 32, align: 32, offset: 352)
!193 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !180, file: !179, line: 95, baseType: !172, size: 32, align: 32, offset: 384)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !158, file: !4, line: 1482, baseType: !162, size: 32, align: 32, offset: 896)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !158, file: !4, line: 1482, baseType: !162, size: 32, align: 32, offset: 928)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !158, file: !4, line: 1482, baseType: !164, size: 128, align: 64, offset: 960)
!197 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !158, file: !4, line: 1482, baseType: !198, size: 320, align: 64, offset: 1088)
!198 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !179, line: 129, baseType: !199)
!199 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !200, line: 127, baseType: !201)
!200 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!201 = !DICompositeType(tag: DW_TAG_union_type, file: !200, line: 90, size: 320, align: 64, elements: !202)
!202 = !{!203, !221, !226}
!203 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !201, file: !200, line: 124, baseType: !204, size: 320, align: 64)
!204 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !200, line: 92, size: 320, align: 64, elements: !205)
!205 = !{!206, !207, !208, !209, !210, !211, !213, !214}
!206 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !204, file: !200, line: 94, baseType: !172, size: 32, align: 32)
!207 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !204, file: !200, line: 95, baseType: !162, size: 32, align: 32, offset: 32)
!208 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !204, file: !200, line: 96, baseType: !172, size: 32, align: 32, offset: 64)
!209 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !204, file: !200, line: 98, baseType: !162, size: 32, align: 32, offset: 96)
!210 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !204, file: !200, line: 102, baseType: !172, size: 32, align: 32, offset: 128)
!211 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !204, file: !200, line: 104, baseType: !212, size: 16, align: 16, offset: 160)
!212 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !204, file: !200, line: 105, baseType: !212, size: 16, align: 16, offset: 176)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !204, file: !200, line: 106, baseType: !215, size: 128, align: 64, offset: 192)
!215 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !200, line: 79, baseType: !216)
!216 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !200, line: 75, size: 128, align: 64, elements: !217)
!217 = !{!218, !220}
!218 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !216, file: !200, line: 77, baseType: !219, size: 64, align: 64)
!219 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !216, size: 64, align: 64)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !216, file: !200, line: 78, baseType: !219, size: 64, align: 64, offset: 64)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !201, file: !200, line: 125, baseType: !222, size: 320, align: 8)
!222 = !DICompositeType(tag: DW_TAG_array_type, baseType: !223, size: 320, align: 8, elements: !224)
!223 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!224 = !{!225}
!225 = !DISubrange(count: 40)
!226 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !201, file: !200, line: 126, baseType: !227, size: 64, align: 64)
!227 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !158, file: !4, line: 1482, baseType: !229, size: 1024, align: 64, offset: 1408)
!229 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !4, line: 216, baseType: !230)
!230 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !4, line: 767, size: 1024, align: 64, elements: !231)
!231 = !{!232, !233, !234, !236, !260, !261, !266, !267, !268, !274, !275}
!232 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !230, file: !4, line: 768, baseType: !154, size: 64, align: 64)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !230, file: !4, line: 768, baseType: !156, size: 64, align: 64, offset: 64)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !230, file: !4, line: 768, baseType: !235, size: 32, align: 32, offset: 128)
!235 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !4, line: 191, baseType: !3)
!236 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !230, file: !4, line: 768, baseType: !237, size: 64, align: 64, offset: 192)
!237 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !4, line: 306, baseType: !238)
!238 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !239, size: 64, align: 64)
!239 = !DISubroutineType(types: !240)
!240 = !{null, !241}
!241 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !242, size: 64, align: 64)
!242 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !4, line: 205, baseType: !243)
!243 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !4, line: 425, size: 768, align: 64, elements: !244)
!244 = !{!245, !246, !247, !248, !249, !250, !258, !259}
!245 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !243, file: !4, line: 426, baseType: !154, size: 64, align: 64)
!246 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !243, file: !4, line: 426, baseType: !156, size: 64, align: 64, offset: 64)
!247 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !243, file: !4, line: 426, baseType: !235, size: 32, align: 32, offset: 128)
!248 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !243, file: !4, line: 426, baseType: !237, size: 64, align: 64, offset: 192)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !243, file: !4, line: 426, baseType: !164, size: 128, align: 64, offset: 256)
!250 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !243, file: !4, line: 426, baseType: !251, size: 256, align: 64, offset: 384)
!251 = !DICompositeType(tag: DW_TAG_union_type, scope: !243, file: !4, line: 426, size: 256, align: 64, elements: !252)
!252 = !{!253, !254}
!253 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !251, file: !4, line: 426, baseType: !172, size: 32, align: 32)
!254 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !251, file: !4, line: 426, baseType: !255, size: 256, align: 64)
!255 = !DICompositeType(tag: DW_TAG_array_type, baseType: !154, size: 256, align: 64, elements: !256)
!256 = !{!257}
!257 = !DISubrange(count: 4)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !243, file: !4, line: 426, baseType: !241, size: 64, align: 64, offset: 640)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !243, file: !4, line: 426, baseType: !162, size: 32, align: 32, offset: 704)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !230, file: !4, line: 768, baseType: !164, size: 128, align: 64, offset: 256)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !230, file: !4, line: 768, baseType: !262, size: 256, align: 64, offset: 384)
!262 = !DICompositeType(tag: DW_TAG_union_type, scope: !230, file: !4, line: 768, size: 256, align: 64, elements: !263)
!263 = !{!264, !265}
!264 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !262, file: !4, line: 768, baseType: !172, size: 32, align: 32)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !262, file: !4, line: 768, baseType: !255, size: 256, align: 64)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !230, file: !4, line: 768, baseType: !241, size: 64, align: 64, offset: 640)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !230, file: !4, line: 768, baseType: !162, size: 32, align: 32, offset: 704)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !230, file: !4, line: 769, baseType: !269, size: 64, align: 64, offset: 768)
!269 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !4, line: 309, baseType: !270)
!270 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !271, size: 64, align: 64)
!271 = !DISubroutineType(types: !272)
!272 = !{null, !273}
!273 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !229, size: 64, align: 64)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !230, file: !4, line: 769, baseType: !164, size: 128, align: 64, offset: 832)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !230, file: !4, line: 769, baseType: !172, size: 32, align: 32, offset: 960)
!276 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !158, file: !4, line: 1482, baseType: !277, size: 448, align: 64, offset: 2432)
!277 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !179, line: 130, baseType: !278)
!278 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !200, line: 213, baseType: !279)
!279 = !DICompositeType(tag: DW_TAG_union_type, file: !200, line: 173, size: 448, align: 64, elements: !280)
!280 = !{!281, !295, !299}
!281 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !279, file: !200, line: 192, baseType: !282, size: 448, align: 64)
!282 = !DICompositeType(tag: DW_TAG_structure_type, scope: !279, file: !200, line: 176, size: 448, align: 64, elements: !283)
!283 = !{!284, !285, !286, !287, !288, !289, !290, !291, !292, !293, !294}
!284 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !282, file: !200, line: 178, baseType: !172, size: 32, align: 32)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !282, file: !200, line: 179, baseType: !162, size: 32, align: 32, offset: 32)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !282, file: !200, line: 180, baseType: !162, size: 32, align: 32, offset: 64)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !282, file: !200, line: 181, baseType: !162, size: 32, align: 32, offset: 96)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !282, file: !200, line: 182, baseType: !162, size: 32, align: 32, offset: 128)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !282, file: !200, line: 183, baseType: !162, size: 32, align: 32, offset: 160)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !282, file: !200, line: 184, baseType: !172, size: 32, align: 32, offset: 192)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !282, file: !200, line: 185, baseType: !172, size: 32, align: 32, offset: 224)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !282, file: !200, line: 186, baseType: !170, size: 64, align: 64, offset: 256)
!293 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !282, file: !200, line: 187, baseType: !170, size: 64, align: 64, offset: 320)
!294 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !282, file: !200, line: 190, baseType: !162, size: 32, align: 32, offset: 384)
!295 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !279, file: !200, line: 211, baseType: !296, size: 448, align: 8)
!296 = !DICompositeType(tag: DW_TAG_array_type, baseType: !223, size: 448, align: 8, elements: !297)
!297 = !{!298}
!298 = !DISubrange(count: 56)
!299 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !279, file: !200, line: 212, baseType: !227, size: 64, align: 64)
!300 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !158, file: !4, line: 1482, baseType: !241, size: 64, align: 64, offset: 2880)
!301 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !158, file: !4, line: 1482, baseType: !164, size: 128, align: 64, offset: 2944)
!302 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !158, file: !4, line: 1482, baseType: !164, size: 128, align: 64, offset: 3072)
!303 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !158, file: !4, line: 1482, baseType: !164, size: 128, align: 64, offset: 3200)
!304 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !158, file: !4, line: 1482, baseType: !164, size: 128, align: 64, offset: 3328)
!305 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !158, file: !4, line: 1482, baseType: !164, size: 128, align: 64, offset: 3456)
!306 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !158, file: !4, line: 1482, baseType: !307, size: 64, align: 64, offset: 3584)
!307 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !308, size: 64, align: 64)
!308 = !DISubroutineType(types: !309)
!309 = !{null}
!310 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !158, file: !4, line: 1482, baseType: !178, size: 448, align: 64, offset: 3648)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !158, file: !4, line: 1482, baseType: !172, size: 32, align: 32, offset: 4096)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !158, file: !4, line: 1482, baseType: !313, size: 128, align: 64, offset: 4160)
!313 = !DICompositeType(tag: DW_TAG_structure_type, scope: !158, file: !4, line: 1482, size: 128, align: 64, elements: !314)
!314 = !{!315, !316}
!315 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !313, file: !4, line: 1482, baseType: !154, size: 64, align: 64)
!316 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !313, file: !4, line: 1482, baseType: !162, size: 32, align: 32, offset: 64)
!317 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !158, file: !4, line: 1482, baseType: !318, size: 64, align: 64, offset: 4288)
!318 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !319, line: 55, baseType: !170)
!319 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!320 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !158, file: !4, line: 1482, baseType: !318, size: 64, align: 64, offset: 4352)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !158, file: !4, line: 1482, baseType: !322, size: 64, align: 32, offset: 4416)
!322 = !DICompositeType(tag: DW_TAG_array_type, baseType: !172, size: 64, align: 32, elements: !165)
!323 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !158, file: !4, line: 1482, baseType: !178, size: 448, align: 64, offset: 4480)
!324 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !158, file: !4, line: 1482, baseType: !325, size: 1216, align: 64, offset: 4928)
!325 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !4, line: 220, baseType: !326)
!326 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !4, line: 1325, size: 1216, align: 64, elements: !327)
!327 = !{!328, !329, !330, !331, !332, !333, !338, !339, !340, !346, !347, !355, !356}
!328 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !326, file: !4, line: 1326, baseType: !154, size: 64, align: 64)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !326, file: !4, line: 1326, baseType: !156, size: 64, align: 64, offset: 64)
!330 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !326, file: !4, line: 1326, baseType: !235, size: 32, align: 32, offset: 128)
!331 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !326, file: !4, line: 1326, baseType: !237, size: 64, align: 64, offset: 192)
!332 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !326, file: !4, line: 1326, baseType: !164, size: 128, align: 64, offset: 256)
!333 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !326, file: !4, line: 1326, baseType: !334, size: 256, align: 64, offset: 384)
!334 = !DICompositeType(tag: DW_TAG_union_type, scope: !326, file: !4, line: 1326, size: 256, align: 64, elements: !335)
!335 = !{!336, !337}
!336 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !334, file: !4, line: 1326, baseType: !172, size: 32, align: 32)
!337 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !334, file: !4, line: 1326, baseType: !255, size: 256, align: 64)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !326, file: !4, line: 1326, baseType: !241, size: 64, align: 64, offset: 640)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !326, file: !4, line: 1326, baseType: !162, size: 32, align: 32, offset: 704)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !326, file: !4, line: 1327, baseType: !341, size: 64, align: 64, offset: 768)
!341 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !4, line: 362, baseType: !342)
!342 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !343, size: 64, align: 64)
!343 = !DISubroutineType(types: !344)
!344 = !{null, !345, !172}
!345 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !325, size: 64, align: 64)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !326, file: !4, line: 1328, baseType: !172, size: 32, align: 32, offset: 832)
!347 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !326, file: !4, line: 1329, baseType: !348, size: 256, align: 64, offset: 896)
!348 = !DICompositeType(tag: DW_TAG_structure_type, scope: !326, file: !4, line: 1329, size: 256, align: 64, elements: !349)
!349 = !{!350, !352, !353, !354}
!350 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !348, file: !4, line: 1329, baseType: !351, size: 64, align: 64)
!351 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !326, size: 64, align: 64)
!352 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !348, file: !4, line: 1329, baseType: !351, size: 64, align: 64, offset: 64)
!353 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !348, file: !4, line: 1329, baseType: !351, size: 64, align: 64, offset: 128)
!354 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !348, file: !4, line: 1329, baseType: !172, size: 32, align: 32, offset: 192)
!355 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !326, file: !4, line: 1329, baseType: !162, size: 32, align: 32, offset: 1152)
!356 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !326, file: !4, line: 1329, baseType: !162, size: 32, align: 32, offset: 1184)
!357 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !158, file: !4, line: 1482, baseType: !172, size: 32, align: 32, offset: 6144)
!358 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !158, file: !4, line: 1482, baseType: !178, size: 448, align: 64, offset: 6208)
!359 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !158, file: !4, line: 1482, baseType: !154, size: 64, align: 64, offset: 6656)
!360 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !158, file: !4, line: 1482, baseType: !172, size: 32, align: 32, offset: 6720)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !151, file: !4, line: 466, baseType: !235, size: 32, align: 32, offset: 128)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !151, file: !4, line: 466, baseType: !237, size: 64, align: 64, offset: 192)
!363 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !151, file: !4, line: 466, baseType: !164, size: 128, align: 64, offset: 256)
!364 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !151, file: !4, line: 466, baseType: !365, size: 256, align: 64, offset: 384)
!365 = !DICompositeType(tag: DW_TAG_union_type, scope: !151, file: !4, line: 466, size: 256, align: 64, elements: !366)
!366 = !{!367, !368}
!367 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !365, file: !4, line: 466, baseType: !172, size: 32, align: 32)
!368 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !365, file: !4, line: 466, baseType: !255, size: 256, align: 64)
!369 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !151, file: !4, line: 466, baseType: !241, size: 64, align: 64, offset: 640)
!370 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !151, file: !4, line: 466, baseType: !162, size: 32, align: 32, offset: 704)
!371 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !151, file: !4, line: 467, baseType: !372, size: 64, align: 64, offset: 768)
!372 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !373, line: 62, baseType: !170)
!373 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!374 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !151, file: !4, line: 467, baseType: !375, size: 64, align: 64, offset: 832)
!375 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_alloc_cb", file: !4, line: 296, baseType: !376)
!376 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !377, size: 64, align: 64)
!377 = !DISubroutineType(types: !378)
!378 = !{null, !241, !372, !379}
!379 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !380, size: 64, align: 64)
!380 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !179, line: 119, baseType: !381)
!381 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !179, line: 116, size: 128, align: 64, elements: !382)
!382 = !{!383, !385}
!383 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !381, file: !179, line: 117, baseType: !384, size: 64, align: 64)
!384 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !223, size: 64, align: 64)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !381, file: !179, line: 118, baseType: !372, size: 64, align: 64, offset: 64)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !151, file: !4, line: 467, baseType: !387, size: 64, align: 64, offset: 896)
!387 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_read_cb", file: !4, line: 299, baseType: !388)
!388 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !389, size: 64, align: 64)
!389 = !DISubroutineType(types: !390)
!390 = !{null, !149, !391, !395}
!391 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !392, line: 102, baseType: !393)
!392 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!393 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !394, line: 172, baseType: !227)
!394 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!395 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !396, size: 64, align: 64)
!396 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !380)
!397 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !151, file: !4, line: 467, baseType: !398, size: 64, align: 64, offset: 960)
!398 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !399, size: 64, align: 64)
!399 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_t", file: !4, line: 228, baseType: !400)
!400 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_connect_s", file: !4, line: 551, size: 768, align: 64, elements: !401)
!401 = !{!402, !403, !405, !406, !407, !412, !413}
!402 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !400, file: !4, line: 552, baseType: !154, size: 64, align: 64)
!403 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !400, file: !4, line: 552, baseType: !404, size: 32, align: 32, offset: 64)
!404 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !4, line: 200, baseType: !25)
!405 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !400, file: !4, line: 552, baseType: !164, size: 128, align: 64, offset: 128)
!406 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !400, file: !4, line: 552, baseType: !255, size: 256, align: 64, offset: 256)
!407 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !400, file: !4, line: 553, baseType: !408, size: 64, align: 64, offset: 512)
!408 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_cb", file: !4, line: 303, baseType: !409)
!409 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !410, size: 64, align: 64)
!410 = !DISubroutineType(types: !411)
!411 = !{null, !398, !172}
!412 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !400, file: !4, line: 554, baseType: !149, size: 64, align: 64, offset: 576)
!413 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !400, file: !4, line: 555, baseType: !164, size: 128, align: 64, offset: 640)
!414 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !151, file: !4, line: 467, baseType: !415, size: 64, align: 64, offset: 1024)
!415 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !416, size: 64, align: 64)
!416 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_t", file: !4, line: 226, baseType: !417)
!417 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_shutdown_s", file: !4, line: 401, size: 640, align: 64, elements: !418)
!418 = !{!419, !420, !421, !422, !423, !424}
!419 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !417, file: !4, line: 402, baseType: !154, size: 64, align: 64)
!420 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !417, file: !4, line: 402, baseType: !404, size: 32, align: 32, offset: 64)
!421 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !417, file: !4, line: 402, baseType: !164, size: 128, align: 64, offset: 128)
!422 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !417, file: !4, line: 402, baseType: !255, size: 256, align: 64, offset: 256)
!423 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !417, file: !4, line: 403, baseType: !149, size: 64, align: 64, offset: 512)
!424 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !417, file: !4, line: 404, baseType: !425, size: 64, align: 64, offset: 576)
!425 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_cb", file: !4, line: 304, baseType: !426)
!426 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !427, size: 64, align: 64)
!427 = !DISubroutineType(types: !428)
!428 = !{null, !415, !172}
!429 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !151, file: !4, line: 467, baseType: !178, size: 448, align: 64, offset: 1088)
!430 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !151, file: !4, line: 467, baseType: !164, size: 128, align: 64, offset: 1536)
!431 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !151, file: !4, line: 467, baseType: !164, size: 128, align: 64, offset: 1664)
!432 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !151, file: !4, line: 467, baseType: !433, size: 64, align: 64, offset: 1792)
!433 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connection_cb", file: !4, line: 305, baseType: !434)
!434 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !435, size: 64, align: 64)
!435 = !DISubroutineType(types: !436)
!436 = !{null, !149, !172}
!437 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !151, file: !4, line: 467, baseType: !172, size: 32, align: 32, offset: 1856)
!438 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !151, file: !4, line: 467, baseType: !172, size: 32, align: 32, offset: 1888)
!439 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !151, file: !4, line: 467, baseType: !154, size: 64, align: 64, offset: 1920)
!440 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !441, size: 64, align: 64)
!441 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr", file: !442, line: 149, size: 128, align: 16, elements: !443)
!442 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!443 = !{!444, !448}
!444 = !DIDerivedType(tag: DW_TAG_member, name: "sa_family", scope: !441, file: !442, line: 151, baseType: !445, size: 16, align: 16)
!445 = !DIDerivedType(tag: DW_TAG_typedef, name: "sa_family_t", file: !446, line: 28, baseType: !447)
!446 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/sockaddr.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!447 = !DIBasicType(name: "unsigned short", size: 16, align: 16, encoding: DW_ATE_unsigned)
!448 = !DIDerivedType(tag: DW_TAG_member, name: "sa_data", scope: !441, file: !442, line: 152, baseType: !449, size: 112, align: 8, offset: 16)
!449 = !DICompositeType(tag: DW_TAG_array_type, baseType: !223, size: 112, align: 8, elements: !450)
!450 = !{!451}
!451 = !DISubrange(count: 14)
!452 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !453, size: 64, align: 64)
!453 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !454, size: 64, align: 64)
!454 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !455, line: 21, baseType: !164)
!455 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!456 = !{!457, !493, !496, !499, !502, !506, !509, !515, !516, !519, !522, !525}
!457 = distinct !DISubprogram(name: "uv_pipe_init", scope: !1, file: !1, line: 33, type: !458, isLocal: false, isDefinition: true, scopeLine: 33, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!458 = !DISubroutineType(types: !459)
!459 = !{!172, !156, !460, !172}
!460 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !461, size: 64, align: 64)
!461 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_pipe_t", file: !4, line: 209, baseType: !462)
!462 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_pipe_s", file: !4, line: 692, size: 2112, align: 64, elements: !463)
!463 = !{!464, !465, !466, !467, !468, !469, !474, !475, !476, !477, !478, !479, !480, !481, !482, !483, !484, !485, !486, !487, !488, !489}
!464 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !462, file: !4, line: 693, baseType: !154, size: 64, align: 64)
!465 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !462, file: !4, line: 693, baseType: !156, size: 64, align: 64, offset: 64)
!466 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !462, file: !4, line: 693, baseType: !235, size: 32, align: 32, offset: 128)
!467 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !462, file: !4, line: 693, baseType: !237, size: 64, align: 64, offset: 192)
!468 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !462, file: !4, line: 693, baseType: !164, size: 128, align: 64, offset: 256)
!469 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !462, file: !4, line: 693, baseType: !470, size: 256, align: 64, offset: 384)
!470 = !DICompositeType(tag: DW_TAG_union_type, scope: !462, file: !4, line: 693, size: 256, align: 64, elements: !471)
!471 = !{!472, !473}
!472 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !470, file: !4, line: 693, baseType: !172, size: 32, align: 32)
!473 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !470, file: !4, line: 693, baseType: !255, size: 256, align: 64)
!474 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !462, file: !4, line: 693, baseType: !241, size: 64, align: 64, offset: 640)
!475 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !462, file: !4, line: 693, baseType: !162, size: 32, align: 32, offset: 704)
!476 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !462, file: !4, line: 694, baseType: !372, size: 64, align: 64, offset: 768)
!477 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !462, file: !4, line: 694, baseType: !375, size: 64, align: 64, offset: 832)
!478 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !462, file: !4, line: 694, baseType: !387, size: 64, align: 64, offset: 896)
!479 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !462, file: !4, line: 694, baseType: !398, size: 64, align: 64, offset: 960)
!480 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !462, file: !4, line: 694, baseType: !415, size: 64, align: 64, offset: 1024)
!481 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !462, file: !4, line: 694, baseType: !178, size: 448, align: 64, offset: 1088)
!482 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !462, file: !4, line: 694, baseType: !164, size: 128, align: 64, offset: 1536)
!483 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !462, file: !4, line: 694, baseType: !164, size: 128, align: 64, offset: 1664)
!484 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !462, file: !4, line: 694, baseType: !433, size: 64, align: 64, offset: 1792)
!485 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !462, file: !4, line: 694, baseType: !172, size: 32, align: 32, offset: 1856)
!486 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !462, file: !4, line: 694, baseType: !172, size: 32, align: 32, offset: 1888)
!487 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !462, file: !4, line: 694, baseType: !154, size: 64, align: 64, offset: 1920)
!488 = !DIDerivedType(tag: DW_TAG_member, name: "ipc", scope: !462, file: !4, line: 695, baseType: !172, size: 32, align: 32, offset: 1984)
!489 = !DIDerivedType(tag: DW_TAG_member, name: "pipe_fname", scope: !462, file: !4, line: 696, baseType: !490, size: 64, align: 64, offset: 2048)
!490 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !491, size: 64, align: 64)
!491 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !223)
!492 = !{}
!493 = distinct !DISubprogram(name: "uv_pipe_bind", scope: !1, file: !1, line: 43, type: !494, isLocal: false, isDefinition: true, scopeLine: 43, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!494 = !DISubroutineType(types: !495)
!495 = !{!172, !460, !490}
!496 = distinct !DISubprogram(name: "uv_pipe_listen", scope: !1, file: !1, line: 93, type: !497, isLocal: false, isDefinition: true, scopeLine: 93, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!497 = !DISubroutineType(types: !498)
!498 = !{!172, !460, !172, !433}
!499 = distinct !DISubprogram(name: "uv__pipe_close", scope: !1, file: !1, line: 115, type: !500, isLocal: false, isDefinition: true, scopeLine: 115, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!500 = !DISubroutineType(types: !501)
!501 = !{null, !460}
!502 = distinct !DISubprogram(name: "uv_pipe_open", scope: !1, file: !1, line: 132, type: !503, isLocal: false, isDefinition: true, scopeLine: 132, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!503 = !DISubroutineType(types: !504)
!504 = !{!172, !460, !505}
!505 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_file", file: !179, line: 121, baseType: !172)
!506 = distinct !DISubprogram(name: "uv_pipe_connect", scope: !1, file: !1, line: 151, type: !507, isLocal: false, isDefinition: true, scopeLine: 154, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!507 = !DISubroutineType(types: !508)
!508 = !{null, !398, !460, !490, !408}
!509 = distinct !DISubprogram(name: "uv_pipe_getsockname", scope: !1, file: !1, line: 255, type: !510, isLocal: false, isDefinition: true, scopeLine: 255, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!510 = !DISubroutineType(types: !511)
!511 = !{!172, !512, !384, !514}
!512 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !513, size: 64, align: 64)
!513 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !461)
!514 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !372, size: 64, align: 64)
!515 = distinct !DISubprogram(name: "uv_pipe_getpeername", scope: !1, file: !1, line: 260, type: !510, isLocal: false, isDefinition: true, scopeLine: 260, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!516 = distinct !DISubprogram(name: "uv_pipe_pending_instances", scope: !1, file: !1, line: 265, type: !517, isLocal: false, isDefinition: true, scopeLine: 265, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!517 = !DISubroutineType(types: !518)
!518 = !{null, !460, !172}
!519 = distinct !DISubprogram(name: "uv_pipe_pending_count", scope: !1, file: !1, line: 269, type: !520, isLocal: false, isDefinition: true, scopeLine: 269, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!520 = !DISubroutineType(types: !521)
!521 = !{!172, !460}
!522 = distinct !DISubprogram(name: "uv_pipe_pending_type", scope: !1, file: !1, line: 286, type: !523, isLocal: false, isDefinition: true, scopeLine: 286, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!523 = !DISubroutineType(types: !524)
!524 = !{!235, !460}
!525 = distinct !DISubprogram(name: "uv__pipe_getsockpeername", scope: !1, file: !1, line: 214, type: !526, isLocal: true, isDefinition: true, scopeLine: 217, flags: DIFlagPrototyped, isOptimized: false, variables: !492)
!526 = !DISubroutineType(types: !527)
!527 = !{!172, !512, !528, !384, !514}
!528 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__peersockfunc", file: !1, line: 211, baseType: !529)
!529 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !530, size: 64, align: 64)
!530 = !DISubroutineType(types: !531)
!531 = !{!172, !172, !440, !532}
!532 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !533, size: 64, align: 64)
!533 = !DIDerivedType(tag: DW_TAG_typedef, name: "socklen_t", file: !442, line: 33, baseType: !534)
!534 = !DIDerivedType(tag: DW_TAG_typedef, name: "__socklen_t", file: !394, line: 189, baseType: !162)
!535 = !{i32 2, !"Dwarf Version", i32 4}
!536 = !{i32 2, !"Debug Info Version", i32 3}
!537 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!538 = !DILocalVariable(name: "loop", arg: 1, scope: !457, file: !1, line: 33, type: !156)
!539 = !DIExpression()
!540 = !DILocation(line: 33, column: 29, scope: !457)
!541 = !DILocalVariable(name: "handle", arg: 2, scope: !457, file: !1, line: 33, type: !460)
!542 = !DILocation(line: 33, column: 46, scope: !457)
!543 = !DILocalVariable(name: "ipc", arg: 3, scope: !457, file: !1, line: 33, type: !172)
!544 = !DILocation(line: 33, column: 58, scope: !457)
!545 = !DILocation(line: 34, column: 19, scope: !457)
!546 = !DILocation(line: 34, column: 39, scope: !457)
!547 = !DILocation(line: 34, column: 25, scope: !457)
!548 = !DILocation(line: 34, column: 3, scope: !457)
!549 = !DILocation(line: 35, column: 3, scope: !457)
!550 = !DILocation(line: 35, column: 11, scope: !457)
!551 = !DILocation(line: 35, column: 24, scope: !457)
!552 = !DILocation(line: 36, column: 3, scope: !457)
!553 = !DILocation(line: 36, column: 11, scope: !457)
!554 = !DILocation(line: 36, column: 23, scope: !457)
!555 = !DILocation(line: 37, column: 3, scope: !457)
!556 = !DILocation(line: 37, column: 11, scope: !457)
!557 = !DILocation(line: 37, column: 22, scope: !457)
!558 = !DILocation(line: 38, column: 17, scope: !457)
!559 = !DILocation(line: 38, column: 3, scope: !457)
!560 = !DILocation(line: 38, column: 11, scope: !457)
!561 = !DILocation(line: 38, column: 15, scope: !457)
!562 = !DILocation(line: 39, column: 3, scope: !457)
!563 = !DILocalVariable(name: "handle", arg: 1, scope: !493, file: !1, line: 43, type: !460)
!564 = !DILocation(line: 43, column: 29, scope: !493)
!565 = !DILocalVariable(name: "name", arg: 2, scope: !493, file: !1, line: 43, type: !490)
!566 = !DILocation(line: 43, column: 49, scope: !493)
!567 = !DILocalVariable(name: "saddr", scope: !493, file: !1, line: 44, type: !568)
!568 = !DICompositeType(tag: DW_TAG_structure_type, name: "sockaddr_un", file: !569, line: 29, size: 880, align: 16, elements: !570)
!569 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/un.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!570 = !{!571, !572}
!571 = !DIDerivedType(tag: DW_TAG_member, name: "sun_family", scope: !568, file: !569, line: 31, baseType: !445, size: 16, align: 16)
!572 = !DIDerivedType(tag: DW_TAG_member, name: "sun_path", scope: !568, file: !569, line: 32, baseType: !573, size: 864, align: 8, offset: 16)
!573 = !DICompositeType(tag: DW_TAG_array_type, baseType: !223, size: 864, align: 8, elements: !574)
!574 = !{!575}
!575 = !DISubrange(count: 108)
!576 = !DILocation(line: 44, column: 22, scope: !493)
!577 = !DILocalVariable(name: "pipe_fname", scope: !493, file: !1, line: 45, type: !490)
!578 = !DILocation(line: 45, column: 15, scope: !493)
!579 = !DILocalVariable(name: "sockfd", scope: !493, file: !1, line: 46, type: !172)
!580 = !DILocation(line: 46, column: 7, scope: !493)
!581 = !DILocalVariable(name: "err", scope: !493, file: !1, line: 47, type: !172)
!582 = !DILocation(line: 47, column: 7, scope: !493)
!583 = !DILocation(line: 50, column: 7, scope: !584)
!584 = distinct !DILexicalBlock(scope: !493, file: !1, line: 50, column: 7)
!585 = !DILocation(line: 50, column: 29, scope: !584)
!586 = !DILocation(line: 50, column: 7, scope: !493)
!587 = !DILocation(line: 51, column: 5, scope: !584)
!588 = !DILocation(line: 54, column: 27, scope: !493)
!589 = !DILocation(line: 54, column: 16, scope: !493)
!590 = !DILocation(line: 54, column: 14, scope: !493)
!591 = !DILocation(line: 55, column: 7, scope: !592)
!592 = distinct !DILexicalBlock(scope: !493, file: !1, line: 55, column: 7)
!593 = !DILocation(line: 55, column: 18, scope: !592)
!594 = !DILocation(line: 55, column: 7, scope: !493)
!595 = !DILocation(line: 56, column: 5, scope: !592)
!596 = !DILocation(line: 59, column: 8, scope: !493)
!597 = !DILocation(line: 61, column: 9, scope: !493)
!598 = !DILocation(line: 61, column: 7, scope: !493)
!599 = !DILocation(line: 62, column: 7, scope: !600)
!600 = distinct !DILexicalBlock(scope: !493, file: !1, line: 62, column: 7)
!601 = !DILocation(line: 62, column: 11, scope: !600)
!602 = !DILocation(line: 62, column: 7, scope: !493)
!603 = !DILocation(line: 63, column: 5, scope: !600)
!604 = !DILocation(line: 64, column: 12, scope: !493)
!605 = !DILocation(line: 64, column: 10, scope: !493)
!606 = !DILocation(line: 66, column: 3, scope: !493)
!607 = !DILocation(line: 67, column: 17, scope: !493)
!608 = !DILocation(line: 67, column: 11, scope: !493)
!609 = !DILocation(line: 67, column: 27, scope: !493)
!610 = !DILocation(line: 67, column: 3, scope: !493)
!611 = !DILocation(line: 68, column: 9, scope: !493)
!612 = !DILocation(line: 68, column: 3, scope: !493)
!613 = !DILocation(line: 68, column: 46, scope: !493)
!614 = !DILocation(line: 69, column: 9, scope: !493)
!615 = !DILocation(line: 69, column: 20, scope: !493)
!616 = !DILocation(line: 71, column: 12, scope: !617)
!617 = distinct !DILexicalBlock(scope: !493, file: !1, line: 71, column: 7)
!618 = !DILocation(line: 71, column: 20, scope: !617)
!619 = !DILocation(line: 71, column: 7, scope: !617)
!620 = !DILocation(line: 71, column: 7, scope: !493)
!621 = !DILocation(line: 72, column: 12, scope: !622)
!622 = distinct !DILexicalBlock(scope: !617, file: !1, line: 71, column: 61)
!623 = !DILocation(line: 72, column: 11, scope: !622)
!624 = !DILocation(line: 72, column: 9, scope: !622)
!625 = !DILocation(line: 74, column: 9, scope: !626)
!626 = distinct !DILexicalBlock(scope: !622, file: !1, line: 74, column: 9)
!627 = !DILocation(line: 74, column: 13, scope: !626)
!628 = !DILocation(line: 74, column: 9, scope: !622)
!629 = !DILocation(line: 75, column: 11, scope: !626)
!630 = !DILocation(line: 75, column: 7, scope: !626)
!631 = !DILocation(line: 77, column: 15, scope: !622)
!632 = !DILocation(line: 77, column: 5, scope: !622)
!633 = !DILocation(line: 78, column: 5, scope: !622)
!634 = !DILocation(line: 82, column: 3, scope: !493)
!635 = !DILocation(line: 82, column: 11, scope: !493)
!636 = !DILocation(line: 82, column: 17, scope: !493)
!637 = !DILocation(line: 83, column: 24, scope: !493)
!638 = !DILocation(line: 83, column: 3, scope: !493)
!639 = !DILocation(line: 83, column: 11, scope: !493)
!640 = !DILocation(line: 83, column: 22, scope: !493)
!641 = !DILocation(line: 84, column: 27, scope: !493)
!642 = !DILocation(line: 84, column: 3, scope: !493)
!643 = !DILocation(line: 84, column: 11, scope: !493)
!644 = !DILocation(line: 84, column: 22, scope: !493)
!645 = !DILocation(line: 84, column: 25, scope: !493)
!646 = !DILocation(line: 85, column: 3, scope: !493)
!647 = !DILocation(line: 88, column: 19, scope: !493)
!648 = !DILocation(line: 88, column: 3, scope: !493)
!649 = !DILocation(line: 89, column: 10, scope: !493)
!650 = !DILocation(line: 89, column: 3, scope: !493)
!651 = !DILocation(line: 90, column: 1, scope: !493)
!652 = !DILocalVariable(name: "handle", arg: 1, scope: !496, file: !1, line: 93, type: !460)
!653 = !DILocation(line: 93, column: 31, scope: !496)
!654 = !DILocalVariable(name: "backlog", arg: 2, scope: !496, file: !1, line: 93, type: !172)
!655 = !DILocation(line: 93, column: 43, scope: !496)
!656 = !DILocalVariable(name: "cb", arg: 3, scope: !496, file: !1, line: 93, type: !433)
!657 = !DILocation(line: 93, column: 69, scope: !496)
!658 = !DILocation(line: 94, column: 7, scope: !659)
!659 = distinct !DILexicalBlock(scope: !496, file: !1, line: 94, column: 7)
!660 = !DILocation(line: 94, column: 29, scope: !659)
!661 = !DILocation(line: 94, column: 7, scope: !496)
!662 = !DILocation(line: 95, column: 5, scope: !659)
!663 = !DILocation(line: 105, column: 14, scope: !664)
!664 = distinct !DILexicalBlock(scope: !496, file: !1, line: 105, column: 7)
!665 = !DILocation(line: 105, column: 37, scope: !664)
!666 = !DILocation(line: 105, column: 7, scope: !664)
!667 = !DILocation(line: 105, column: 7, scope: !496)
!668 = !DILocation(line: 106, column: 13, scope: !664)
!669 = !DILocation(line: 106, column: 12, scope: !664)
!670 = !DILocation(line: 106, column: 5, scope: !664)
!671 = !DILocation(line: 108, column: 27, scope: !496)
!672 = !DILocation(line: 108, column: 3, scope: !496)
!673 = !DILocation(line: 108, column: 11, scope: !496)
!674 = !DILocation(line: 108, column: 25, scope: !496)
!675 = !DILocation(line: 109, column: 3, scope: !496)
!676 = !DILocation(line: 109, column: 11, scope: !496)
!677 = !DILocation(line: 109, column: 22, scope: !496)
!678 = !DILocation(line: 109, column: 25, scope: !496)
!679 = !DILocation(line: 110, column: 16, scope: !496)
!680 = !DILocation(line: 110, column: 24, scope: !496)
!681 = !DILocation(line: 110, column: 31, scope: !496)
!682 = !DILocation(line: 110, column: 39, scope: !496)
!683 = !DILocation(line: 110, column: 3, scope: !496)
!684 = !DILocation(line: 111, column: 3, scope: !496)
!685 = !DILocation(line: 112, column: 1, scope: !496)
!686 = !DILocalVariable(name: "handle", arg: 1, scope: !499, file: !1, line: 115, type: !460)
!687 = !DILocation(line: 115, column: 32, scope: !499)
!688 = !DILocation(line: 116, column: 7, scope: !689)
!689 = distinct !DILexicalBlock(scope: !499, file: !1, line: 116, column: 7)
!690 = !DILocation(line: 116, column: 15, scope: !689)
!691 = !DILocation(line: 116, column: 7, scope: !499)
!692 = !DILocation(line: 123, column: 12, scope: !693)
!693 = distinct !DILexicalBlock(scope: !689, file: !1, line: 116, column: 27)
!694 = !DILocation(line: 123, column: 20, scope: !693)
!695 = !DILocation(line: 123, column: 5, scope: !693)
!696 = !DILocation(line: 124, column: 21, scope: !693)
!697 = !DILocation(line: 124, column: 29, scope: !693)
!698 = !DILocation(line: 124, column: 5, scope: !693)
!699 = !DILocation(line: 125, column: 5, scope: !693)
!700 = !DILocation(line: 125, column: 13, scope: !693)
!701 = !DILocation(line: 125, column: 24, scope: !693)
!702 = !DILocation(line: 126, column: 3, scope: !693)
!703 = !DILocation(line: 128, column: 34, scope: !499)
!704 = !DILocation(line: 128, column: 20, scope: !499)
!705 = !DILocation(line: 128, column: 3, scope: !499)
!706 = !DILocation(line: 129, column: 1, scope: !499)
!707 = !DILocalVariable(name: "handle", arg: 1, scope: !502, file: !1, line: 132, type: !460)
!708 = !DILocation(line: 132, column: 29, scope: !502)
!709 = !DILocalVariable(name: "fd", arg: 2, scope: !502, file: !1, line: 132, type: !505)
!710 = !DILocation(line: 132, column: 45, scope: !502)
!711 = !DILocalVariable(name: "err", scope: !502, file: !1, line: 133, type: !172)
!712 = !DILocation(line: 133, column: 7, scope: !502)
!713 = !DILocation(line: 135, column: 22, scope: !502)
!714 = !DILocation(line: 135, column: 9, scope: !502)
!715 = !DILocation(line: 135, column: 7, scope: !502)
!716 = !DILocation(line: 136, column: 7, scope: !717)
!717 = distinct !DILexicalBlock(scope: !502, file: !1, line: 136, column: 7)
!718 = !DILocation(line: 136, column: 7, scope: !502)
!719 = !DILocation(line: 137, column: 12, scope: !717)
!720 = !DILocation(line: 137, column: 5, scope: !717)
!721 = !DILocation(line: 145, column: 40, scope: !502)
!722 = !DILocation(line: 145, column: 26, scope: !502)
!723 = !DILocation(line: 146, column: 26, scope: !502)
!724 = !DILocation(line: 145, column: 10, scope: !502)
!725 = !DILocation(line: 145, column: 3, scope: !502)
!726 = !DILocation(line: 148, column: 1, scope: !502)
!727 = !DILocalVariable(name: "req", arg: 1, scope: !506, file: !1, line: 151, type: !398)
!728 = !DILocation(line: 151, column: 36, scope: !506)
!729 = !DILocalVariable(name: "handle", arg: 2, scope: !506, file: !1, line: 152, type: !460)
!730 = !DILocation(line: 152, column: 32, scope: !506)
!731 = !DILocalVariable(name: "name", arg: 3, scope: !506, file: !1, line: 153, type: !490)
!732 = !DILocation(line: 153, column: 33, scope: !506)
!733 = !DILocalVariable(name: "cb", arg: 4, scope: !506, file: !1, line: 154, type: !408)
!734 = !DILocation(line: 154, column: 35, scope: !506)
!735 = !DILocalVariable(name: "saddr", scope: !506, file: !1, line: 155, type: !568)
!736 = !DILocation(line: 155, column: 22, scope: !506)
!737 = !DILocalVariable(name: "new_sock", scope: !506, file: !1, line: 156, type: !172)
!738 = !DILocation(line: 156, column: 7, scope: !506)
!739 = !DILocalVariable(name: "err", scope: !506, file: !1, line: 157, type: !172)
!740 = !DILocation(line: 157, column: 7, scope: !506)
!741 = !DILocalVariable(name: "r", scope: !506, file: !1, line: 158, type: !172)
!742 = !DILocation(line: 158, column: 7, scope: !506)
!743 = !DILocation(line: 160, column: 15, scope: !506)
!744 = !DILocation(line: 160, column: 37, scope: !506)
!745 = !DILocation(line: 160, column: 12, scope: !506)
!746 = !DILocation(line: 162, column: 7, scope: !747)
!747 = distinct !DILexicalBlock(scope: !506, file: !1, line: 162, column: 7)
!748 = !DILocation(line: 162, column: 7, scope: !506)
!749 = !DILocation(line: 163, column: 11, scope: !750)
!750 = distinct !DILexicalBlock(scope: !747, file: !1, line: 162, column: 17)
!751 = !DILocation(line: 163, column: 9, scope: !750)
!752 = !DILocation(line: 164, column: 9, scope: !753)
!753 = distinct !DILexicalBlock(scope: !750, file: !1, line: 164, column: 9)
!754 = !DILocation(line: 164, column: 13, scope: !753)
!755 = !DILocation(line: 164, column: 9, scope: !750)
!756 = !DILocation(line: 165, column: 7, scope: !753)
!757 = !DILocation(line: 166, column: 29, scope: !750)
!758 = !DILocation(line: 166, column: 5, scope: !750)
!759 = !DILocation(line: 166, column: 13, scope: !750)
!760 = !DILocation(line: 166, column: 24, scope: !750)
!761 = !DILocation(line: 166, column: 27, scope: !750)
!762 = !DILocation(line: 167, column: 3, scope: !750)
!763 = !DILocation(line: 169, column: 3, scope: !506)
!764 = !DILocation(line: 170, column: 17, scope: !506)
!765 = !DILocation(line: 170, column: 11, scope: !506)
!766 = !DILocation(line: 170, column: 27, scope: !506)
!767 = !DILocation(line: 170, column: 3, scope: !506)
!768 = !DILocation(line: 171, column: 9, scope: !506)
!769 = !DILocation(line: 171, column: 3, scope: !506)
!770 = !DILocation(line: 171, column: 46, scope: !506)
!771 = !DILocation(line: 172, column: 9, scope: !506)
!772 = !DILocation(line: 172, column: 20, scope: !506)
!773 = !DILocation(line: 174, column: 3, scope: !506)
!774 = !DILocation(line: 175, column: 17, scope: !775)
!775 = distinct !DILexicalBlock(scope: !506, file: !1, line: 174, column: 6)
!776 = !DILocation(line: 176, column: 17, scope: !775)
!777 = !DILocation(line: 175, column: 9, scope: !775)
!778 = !DILocation(line: 175, column: 7, scope: !775)
!779 = !DILocation(line: 177, column: 3, scope: !775)
!780 = !DILocation(line: 178, column: 10, scope: !506)
!781 = !DILocation(line: 178, column: 12, scope: !506)
!782 = !DILocation(line: 178, column: 18, scope: !506)
!783 = !DILocation(line: 178, column: 21, scope: !784)
!784 = !DILexicalBlockFile(scope: !506, file: !1, discriminator: 1)
!785 = !DILocation(line: 178, column: 27, scope: !784)
!786 = !DILocation(line: 177, column: 3, scope: !787)
!787 = !DILexicalBlockFile(scope: !775, file: !1, discriminator: 1)
!788 = !DILocation(line: 180, column: 7, scope: !789)
!789 = distinct !DILexicalBlock(scope: !506, file: !1, line: 180, column: 7)
!790 = !DILocation(line: 180, column: 9, scope: !789)
!791 = !DILocation(line: 180, column: 15, scope: !789)
!792 = !DILocation(line: 180, column: 18, scope: !793)
!793 = !DILexicalBlockFile(scope: !789, file: !1, discriminator: 1)
!794 = !DILocation(line: 180, column: 24, scope: !793)
!795 = !DILocation(line: 180, column: 7, scope: !793)
!796 = !DILocation(line: 181, column: 12, scope: !797)
!797 = distinct !DILexicalBlock(scope: !789, file: !1, line: 180, column: 40)
!798 = !DILocation(line: 181, column: 11, scope: !797)
!799 = !DILocation(line: 181, column: 9, scope: !797)
!800 = !DILocation(line: 182, column: 5, scope: !797)
!801 = !DILocation(line: 185, column: 7, scope: !506)
!802 = !DILocation(line: 186, column: 7, scope: !803)
!803 = distinct !DILexicalBlock(scope: !506, file: !1, line: 186, column: 7)
!804 = !DILocation(line: 186, column: 7, scope: !506)
!805 = !DILocation(line: 187, column: 41, scope: !806)
!806 = distinct !DILexicalBlock(scope: !803, file: !1, line: 186, column: 17)
!807 = !DILocation(line: 187, column: 27, scope: !806)
!808 = !DILocation(line: 188, column: 27, scope: !806)
!809 = !DILocation(line: 187, column: 11, scope: !806)
!810 = !DILocation(line: 187, column: 9, scope: !806)
!811 = !DILocation(line: 190, column: 3, scope: !806)
!812 = !DILocation(line: 192, column: 7, scope: !813)
!813 = distinct !DILexicalBlock(scope: !506, file: !1, line: 192, column: 7)
!814 = !DILocation(line: 192, column: 11, scope: !813)
!815 = !DILocation(line: 192, column: 7, scope: !506)
!816 = !DILocation(line: 193, column: 18, scope: !813)
!817 = !DILocation(line: 193, column: 26, scope: !813)
!818 = !DILocation(line: 193, column: 33, scope: !813)
!819 = !DILocation(line: 193, column: 41, scope: !813)
!820 = !DILocation(line: 193, column: 5, scope: !813)
!821 = !DILocation(line: 192, column: 14, scope: !822)
!822 = !DILexicalBlockFile(scope: !813, file: !1, discriminator: 1)
!823 = !DILocation(line: 196, column: 27, scope: !506)
!824 = !DILocation(line: 196, column: 3, scope: !506)
!825 = !DILocation(line: 196, column: 11, scope: !506)
!826 = !DILocation(line: 196, column: 25, scope: !506)
!827 = !DILocation(line: 197, column: 25, scope: !506)
!828 = !DILocation(line: 197, column: 3, scope: !506)
!829 = !DILocation(line: 197, column: 11, scope: !506)
!830 = !DILocation(line: 197, column: 23, scope: !506)
!831 = !DILocation(line: 199, column: 3, scope: !506)
!832 = !DILocation(line: 199, column: 3, scope: !833)
!833 = !DILexicalBlockFile(scope: !834, file: !1, discriminator: 1)
!834 = distinct !DILexicalBlock(scope: !506, file: !1, line: 199, column: 3)
!835 = !DILocation(line: 199, column: 3, scope: !836)
!836 = !DILexicalBlockFile(scope: !837, file: !1, discriminator: 2)
!837 = distinct !DILexicalBlock(scope: !834, file: !1, line: 199, column: 3)
!838 = !DILocation(line: 199, column: 3, scope: !839)
!839 = !DILexicalBlockFile(scope: !834, file: !1, discriminator: 3)
!840 = !DILocation(line: 199, column: 3, scope: !841)
!841 = !DILexicalBlockFile(scope: !842, file: !1, discriminator: 4)
!842 = distinct !DILexicalBlock(scope: !834, file: !1, line: 199, column: 3)
!843 = !DILocation(line: 199, column: 3, scope: !844)
!844 = !DILexicalBlockFile(scope: !845, file: !1, discriminator: 5)
!845 = distinct !DILexicalBlock(scope: !842, file: !1, line: 199, column: 3)
!846 = !DILocation(line: 199, column: 3, scope: !847)
!847 = !DILexicalBlockFile(scope: !842, file: !1, discriminator: 6)
!848 = !DILocation(line: 199, column: 3, scope: !849)
!849 = !DILexicalBlockFile(scope: !834, file: !1, discriminator: 7)
!850 = !DILocation(line: 200, column: 31, scope: !506)
!851 = !DILocation(line: 200, column: 17, scope: !506)
!852 = !DILocation(line: 200, column: 3, scope: !506)
!853 = !DILocation(line: 200, column: 8, scope: !506)
!854 = !DILocation(line: 200, column: 15, scope: !506)
!855 = !DILocation(line: 201, column: 13, scope: !506)
!856 = !DILocation(line: 201, column: 3, scope: !506)
!857 = !DILocation(line: 201, column: 8, scope: !506)
!858 = !DILocation(line: 201, column: 11, scope: !506)
!859 = !DILocation(line: 202, column: 3, scope: !506)
!860 = !DILocation(line: 202, column: 3, scope: !861)
!861 = !DILexicalBlockFile(scope: !862, file: !1, discriminator: 1)
!862 = distinct !DILexicalBlock(scope: !506, file: !1, line: 202, column: 3)
!863 = !DILocation(line: 205, column: 7, scope: !864)
!864 = distinct !DILexicalBlock(scope: !506, file: !1, line: 205, column: 7)
!865 = !DILocation(line: 205, column: 7, scope: !506)
!866 = !DILocation(line: 206, column: 17, scope: !864)
!867 = !DILocation(line: 206, column: 25, scope: !864)
!868 = !DILocation(line: 206, column: 32, scope: !864)
!869 = !DILocation(line: 206, column: 40, scope: !864)
!870 = !DILocation(line: 206, column: 5, scope: !864)
!871 = !DILocation(line: 208, column: 1, scope: !506)
!872 = !DILocalVariable(name: "handle", arg: 1, scope: !509, file: !1, line: 255, type: !512)
!873 = !DILocation(line: 255, column: 42, scope: !509)
!874 = !DILocalVariable(name: "buffer", arg: 2, scope: !509, file: !1, line: 255, type: !384)
!875 = !DILocation(line: 255, column: 56, scope: !509)
!876 = !DILocalVariable(name: "size", arg: 3, scope: !509, file: !1, line: 255, type: !514)
!877 = !DILocation(line: 255, column: 72, scope: !509)
!878 = !DILocation(line: 256, column: 35, scope: !509)
!879 = !DILocation(line: 256, column: 56, scope: !509)
!880 = !DILocation(line: 256, column: 64, scope: !509)
!881 = !DILocation(line: 256, column: 10, scope: !509)
!882 = !DILocation(line: 256, column: 3, scope: !509)
!883 = !DILocalVariable(name: "handle", arg: 1, scope: !525, file: !1, line: 214, type: !512)
!884 = !DILocation(line: 214, column: 54, scope: !525)
!885 = !DILocalVariable(name: "func", arg: 2, scope: !525, file: !1, line: 215, type: !528)
!886 = !DILocation(line: 215, column: 54, scope: !525)
!887 = !DILocalVariable(name: "buffer", arg: 3, scope: !525, file: !1, line: 216, type: !384)
!888 = !DILocation(line: 216, column: 43, scope: !525)
!889 = !DILocalVariable(name: "size", arg: 4, scope: !525, file: !1, line: 217, type: !514)
!890 = !DILocation(line: 217, column: 45, scope: !525)
!891 = !DILocalVariable(name: "sa", scope: !525, file: !1, line: 218, type: !568)
!892 = !DILocation(line: 218, column: 22, scope: !525)
!893 = !DILocalVariable(name: "addrlen", scope: !525, file: !1, line: 219, type: !533)
!894 = !DILocation(line: 219, column: 13, scope: !525)
!895 = !DILocalVariable(name: "err", scope: !525, file: !1, line: 220, type: !172)
!896 = !DILocation(line: 220, column: 7, scope: !525)
!897 = !DILocation(line: 222, column: 11, scope: !525)
!898 = !DILocation(line: 223, column: 3, scope: !525)
!899 = !DILocation(line: 223, column: 18, scope: !525)
!900 = !DILocation(line: 224, column: 9, scope: !525)
!901 = !DILocation(line: 224, column: 14, scope: !525)
!902 = !DILocation(line: 224, column: 37, scope: !525)
!903 = !DILocation(line: 224, column: 7, scope: !525)
!904 = !DILocation(line: 225, column: 7, scope: !905)
!905 = distinct !DILexicalBlock(scope: !525, file: !1, line: 225, column: 7)
!906 = !DILocation(line: 225, column: 11, scope: !905)
!907 = !DILocation(line: 225, column: 7, scope: !525)
!908 = !DILocation(line: 226, column: 6, scope: !909)
!909 = distinct !DILexicalBlock(scope: !905, file: !1, line: 225, column: 16)
!910 = !DILocation(line: 226, column: 11, scope: !909)
!911 = !DILocation(line: 227, column: 13, scope: !909)
!912 = !DILocation(line: 227, column: 12, scope: !909)
!913 = !DILocation(line: 227, column: 5, scope: !909)
!914 = !DILocation(line: 231, column: 10, scope: !915)
!915 = distinct !DILexicalBlock(scope: !525, file: !1, line: 231, column: 7)
!916 = !DILocation(line: 231, column: 7, scope: !915)
!917 = !DILocation(line: 231, column: 22, scope: !915)
!918 = !DILocation(line: 231, column: 7, scope: !525)
!919 = !DILocation(line: 233, column: 13, scope: !915)
!920 = !DILocation(line: 233, column: 5, scope: !915)
!921 = !DILocation(line: 236, column: 25, scope: !915)
!922 = !DILocation(line: 236, column: 22, scope: !915)
!923 = !DILocation(line: 236, column: 15, scope: !915)
!924 = !DILocation(line: 236, column: 13, scope: !915)
!925 = !DILocation(line: 239, column: 7, scope: !926)
!926 = distinct !DILexicalBlock(scope: !525, file: !1, line: 239, column: 7)
!927 = !DILocation(line: 239, column: 19, scope: !926)
!928 = !DILocation(line: 239, column: 18, scope: !926)
!929 = !DILocation(line: 239, column: 15, scope: !926)
!930 = !DILocation(line: 239, column: 7, scope: !525)
!931 = !DILocation(line: 240, column: 13, scope: !932)
!932 = distinct !DILexicalBlock(scope: !926, file: !1, line: 239, column: 25)
!933 = !DILocation(line: 240, column: 21, scope: !932)
!934 = !DILocation(line: 240, column: 6, scope: !932)
!935 = !DILocation(line: 240, column: 11, scope: !932)
!936 = !DILocation(line: 241, column: 5, scope: !932)
!937 = !DILocation(line: 244, column: 10, scope: !525)
!938 = !DILocation(line: 244, column: 21, scope: !525)
!939 = !DILocation(line: 244, column: 3, scope: !525)
!940 = !DILocation(line: 244, column: 31, scope: !525)
!941 = !DILocation(line: 245, column: 11, scope: !525)
!942 = !DILocation(line: 245, column: 4, scope: !525)
!943 = !DILocation(line: 245, column: 9, scope: !525)
!944 = !DILocation(line: 248, column: 7, scope: !945)
!945 = distinct !DILexicalBlock(scope: !525, file: !1, line: 248, column: 7)
!946 = !DILocation(line: 248, column: 17, scope: !945)
!947 = !DILocation(line: 248, column: 7, scope: !525)
!948 = !DILocation(line: 249, column: 12, scope: !945)
!949 = !DILocation(line: 249, column: 5, scope: !945)
!950 = !DILocation(line: 249, column: 21, scope: !945)
!951 = !DILocation(line: 251, column: 3, scope: !525)
!952 = !DILocation(line: 252, column: 1, scope: !525)
!953 = !DILocalVariable(name: "handle", arg: 1, scope: !515, file: !1, line: 260, type: !512)
!954 = !DILocation(line: 260, column: 42, scope: !515)
!955 = !DILocalVariable(name: "buffer", arg: 2, scope: !515, file: !1, line: 260, type: !384)
!956 = !DILocation(line: 260, column: 56, scope: !515)
!957 = !DILocalVariable(name: "size", arg: 3, scope: !515, file: !1, line: 260, type: !514)
!958 = !DILocation(line: 260, column: 72, scope: !515)
!959 = !DILocation(line: 261, column: 35, scope: !515)
!960 = !DILocation(line: 261, column: 56, scope: !515)
!961 = !DILocation(line: 261, column: 64, scope: !515)
!962 = !DILocation(line: 261, column: 10, scope: !515)
!963 = !DILocation(line: 261, column: 3, scope: !515)
!964 = !DILocalVariable(name: "handle", arg: 1, scope: !516, file: !1, line: 265, type: !460)
!965 = !DILocation(line: 265, column: 43, scope: !516)
!966 = !DILocalVariable(name: "count", arg: 2, scope: !516, file: !1, line: 265, type: !172)
!967 = !DILocation(line: 265, column: 55, scope: !516)
!968 = !DILocation(line: 266, column: 1, scope: !516)
!969 = !DILocalVariable(name: "handle", arg: 1, scope: !519, file: !1, line: 269, type: !460)
!970 = !DILocation(line: 269, column: 38, scope: !519)
!971 = !DILocalVariable(name: "queued_fds", scope: !519, file: !1, line: 270, type: !972)
!972 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !973, size: 64, align: 64)
!973 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__stream_queued_fds_t", file: !51, line: 121, baseType: !974)
!974 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__stream_queued_fds_s", file: !51, line: 153, size: 96, align: 32, elements: !975)
!975 = !{!976, !977, !978}
!976 = !DIDerivedType(tag: DW_TAG_member, name: "size", scope: !974, file: !51, line: 154, baseType: !162, size: 32, align: 32)
!977 = !DIDerivedType(tag: DW_TAG_member, name: "offset", scope: !974, file: !51, line: 155, baseType: !162, size: 32, align: 32, offset: 32)
!978 = !DIDerivedType(tag: DW_TAG_member, name: "fds", scope: !974, file: !51, line: 156, baseType: !979, size: 32, align: 32, offset: 64)
!979 = !DICompositeType(tag: DW_TAG_array_type, baseType: !172, size: 32, align: 32, elements: !980)
!980 = !{!981}
!981 = !DISubrange(count: 1)
!982 = !DILocation(line: 270, column: 28, scope: !519)
!983 = !DILocation(line: 272, column: 8, scope: !984)
!984 = distinct !DILexicalBlock(scope: !519, file: !1, line: 272, column: 7)
!985 = !DILocation(line: 272, column: 16, scope: !984)
!986 = !DILocation(line: 272, column: 7, scope: !519)
!987 = !DILocation(line: 273, column: 5, scope: !984)
!988 = !DILocation(line: 275, column: 7, scope: !989)
!989 = distinct !DILexicalBlock(scope: !519, file: !1, line: 275, column: 7)
!990 = !DILocation(line: 275, column: 15, scope: !989)
!991 = !DILocation(line: 275, column: 27, scope: !989)
!992 = !DILocation(line: 275, column: 7, scope: !519)
!993 = !DILocation(line: 276, column: 5, scope: !989)
!994 = !DILocation(line: 278, column: 7, scope: !995)
!995 = distinct !DILexicalBlock(scope: !519, file: !1, line: 278, column: 7)
!996 = !DILocation(line: 278, column: 15, scope: !995)
!997 = !DILocation(line: 278, column: 26, scope: !995)
!998 = !DILocation(line: 278, column: 7, scope: !519)
!999 = !DILocation(line: 279, column: 5, scope: !995)
!1000 = !DILocation(line: 281, column: 16, scope: !519)
!1001 = !DILocation(line: 281, column: 24, scope: !519)
!1002 = !DILocation(line: 281, column: 14, scope: !519)
!1003 = !DILocation(line: 282, column: 10, scope: !519)
!1004 = !DILocation(line: 282, column: 22, scope: !519)
!1005 = !DILocation(line: 282, column: 29, scope: !519)
!1006 = !DILocation(line: 282, column: 3, scope: !519)
!1007 = !DILocation(line: 283, column: 1, scope: !519)
!1008 = !DILocalVariable(name: "handle", arg: 1, scope: !522, file: !1, line: 286, type: !460)
!1009 = !DILocation(line: 286, column: 48, scope: !522)
!1010 = !DILocation(line: 287, column: 8, scope: !1011)
!1011 = distinct !DILexicalBlock(scope: !522, file: !1, line: 287, column: 7)
!1012 = !DILocation(line: 287, column: 16, scope: !1011)
!1013 = !DILocation(line: 287, column: 7, scope: !522)
!1014 = !DILocation(line: 288, column: 5, scope: !1011)
!1015 = !DILocation(line: 290, column: 7, scope: !1016)
!1016 = distinct !DILexicalBlock(scope: !522, file: !1, line: 290, column: 7)
!1017 = !DILocation(line: 290, column: 15, scope: !1016)
!1018 = !DILocation(line: 290, column: 27, scope: !1016)
!1019 = !DILocation(line: 290, column: 7, scope: !522)
!1020 = !DILocation(line: 291, column: 5, scope: !1016)
!1021 = !DILocation(line: 293, column: 28, scope: !1016)
!1022 = !DILocation(line: 293, column: 36, scope: !1016)
!1023 = !DILocation(line: 293, column: 12, scope: !1016)
!1024 = !DILocation(line: 293, column: 5, scope: !1016)
!1025 = !DILocation(line: 294, column: 1, scope: !522)
