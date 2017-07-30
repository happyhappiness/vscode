; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/process.c'
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
%struct.uv_process_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.4, %struct.uv_handle_s*, i32, void (%struct.uv_process_s*, i64, i32)*, i32, [2 x i8*], i32 }
%union.anon.4 = type { [4 x i8*] }
%struct.uv_process_options_s = type { void (%struct.uv_process_s*, i64, i32)*, i8*, i8**, i8**, i8*, i32, i32, %struct.uv_stdio_container_s*, i32, i32 }
%struct.uv_stdio_container_s = type { i32, %union.anon.5 }
%union.anon.5 = type { %struct.uv_stream_s* }
%struct.uv_stream_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.6, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8* }
%union.anon.6 = type { [4 x i8*] }
%struct.uv_buf_t = type { i8*, i64 }
%struct.uv_connect_s = type { i8*, i32, [2 x i8*], [4 x i8*], void (%struct.uv_connect_s*, i32)*, %struct.uv_stream_s*, [2 x i8*] }
%struct.uv_shutdown_s = type { i8*, i32, [2 x i8*], [4 x i8*], %struct.uv_stream_s*, void (%struct.uv_shutdown_s*, i32)* }
%union.anon.7 = type { i32 }
%union.anon.8 = type { i32 }
%union.anon.9 = type { i32 }
%union.anon.10 = type { i32 }
%struct.uv_pipe_s = type { i8*, %struct.uv_loop_s*, i32, void (%struct.uv_handle_s*)*, [2 x i8*], %union.anon.11, %struct.uv_handle_s*, i32, i64, void (%struct.uv_handle_s*, i64, %struct.uv_buf_t*)*, void (%struct.uv_stream_s*, i64, %struct.uv_buf_t*)*, %struct.uv_connect_s*, %struct.uv_shutdown_s*, %struct.uv__io_s, [2 x i8*], [2 x i8*], void (%struct.uv_stream_s*, i32)*, i32, i32, i8*, i32, i8* }
%union.anon.11 = type { [4 x i8*] }

@uv__make_socketpair.no_cloexec = internal global i32 0, align 4
@uv__make_pipe.no_pipe2 = internal global i32 0, align 4
@uv_spawn.signal_pipe = private unnamed_addr constant [2 x i32] [i32 -1, i32 -1], align 4
@.str = private unnamed_addr constant [28 x i8] c"options->file != ((void*)0)\00", align 1
@.str.1 = private unnamed_addr constant [71 x i8] c"/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/process.c\00", align 1
@__PRETTY_FUNCTION__.uv_spawn = private unnamed_addr constant [72 x i8] c"int uv_spawn(uv_loop_t *, uv_process_t *, const uv_process_options_t *)\00", align 1
@.str.2 = private unnamed_addr constant [149 x i8] c"!(options->flags & ~(UV_PROCESS_DETACHED | UV_PROCESS_SETGID | UV_PROCESS_SETUID | UV_PROCESS_WINDOWS_HIDE | UV_PROCESS_WINDOWS_VERBATIM_ARGUMENTS))\00", align 1
@.str.3 = private unnamed_addr constant [11 x i8] c"err == pid\00", align 1
@.str.4 = private unnamed_addr constant [45 x i8] c"((process)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@.str.5 = private unnamed_addr constant [44 x i8] c"((handle)->flags & UV__HANDLE_CLOSING) == 0\00", align 1
@__PRETTY_FUNCTION__.uv__process_close = private unnamed_addr constant [39 x i8] c"void uv__process_close(uv_process_t *)\00", align 1
@.str.6 = private unnamed_addr constant [37 x i8] c"container->data.stream != ((void*)0)\00", align 1
@__PRETTY_FUNCTION__.uv__process_init_stdio = private unnamed_addr constant [58 x i8] c"int uv__process_init_stdio(uv_stdio_container_t *, int *)\00", align 1
@.str.7 = private unnamed_addr constant [24 x i8] c"0 && \22Unexpected flags\22\00", align 1
@.str.8 = private unnamed_addr constant [13 x i8] c"signum == 17\00", align 1
@__PRETTY_FUNCTION__.uv__chld = private unnamed_addr constant [34 x i8] c"void uv__chld(uv_signal_t *, int)\00", align 1
@.str.9 = private unnamed_addr constant [82 x i8] c"((const QUEUE *) (&pending) == (const QUEUE *) (*(QUEUE **) &((*(&pending))[0])))\00", align 1
@.str.10 = private unnamed_addr constant [10 x i8] c"/dev/null\00", align 1
@environ = external global i8**, align 8
@.str.11 = private unnamed_addr constant [17 x i8] c"n == sizeof(val)\00", align 1
@__PRETTY_FUNCTION__.uv__write_int = private unnamed_addr constant [29 x i8] c"void uv__write_int(int, int)\00", align 1

; Function Attrs: nounwind uwtable
define i32 @uv__make_socketpair(i32* %fds, i32 %flags) #0 !dbg !449 {
entry:
  %retval = alloca i32, align 4
  %fds.addr = alloca i32*, align 8
  %flags.addr = alloca i32, align 4
  store i32* %fds, i32** %fds.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %fds.addr, metadata !524, metadata !525), !dbg !526
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !527, metadata !525), !dbg !528
  %0 = load i32, i32* @uv__make_socketpair.no_cloexec, align 4, !dbg !529
  %tobool = icmp ne i32 %0, 0, !dbg !529
  br i1 %tobool, label %if.then, label %if.end, !dbg !531

if.then:                                          ; preds = %entry
  br label %skip, !dbg !532

if.end:                                           ; preds = %entry
  %1 = load i32, i32* %flags.addr, align 4, !dbg !533
  %or = or i32 524289, %1, !dbg !535
  %2 = load i32*, i32** %fds.addr, align 8, !dbg !536
  %call = call i32 @socketpair(i32 1, i32 %or, i32 0, i32* %2) #8, !dbg !537
  %cmp = icmp eq i32 %call, 0, !dbg !538
  br i1 %cmp, label %if.then1, label %if.end2, !dbg !539

if.then1:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !540
  br label %return, !dbg !540

if.end2:                                          ; preds = %if.end
  %call3 = call i32* @__errno_location() #1, !dbg !541
  %3 = load i32, i32* %call3, align 4, !dbg !541
  %cmp4 = icmp ne i32 %3, 22, !dbg !543
  br i1 %cmp4, label %if.then5, label %if.end7, !dbg !544

if.then5:                                         ; preds = %if.end2
  %call6 = call i32* @__errno_location() #1, !dbg !545
  %4 = load i32, i32* %call6, align 4, !dbg !545
  %sub = sub nsw i32 0, %4, !dbg !546
  store i32 %sub, i32* %retval, align 4, !dbg !547
  br label %return, !dbg !547

if.end7:                                          ; preds = %if.end2
  store i32 1, i32* @uv__make_socketpair.no_cloexec, align 4, !dbg !548
  br label %skip, !dbg !549

skip:                                             ; preds = %if.end7, %if.then
  %5 = load i32*, i32** %fds.addr, align 8, !dbg !550
  %call8 = call i32 @socketpair(i32 1, i32 1, i32 0, i32* %5) #8, !dbg !552
  %tobool9 = icmp ne i32 %call8, 0, !dbg !552
  br i1 %tobool9, label %if.then10, label %if.end13, !dbg !553

if.then10:                                        ; preds = %skip
  %call11 = call i32* @__errno_location() #1, !dbg !554
  %6 = load i32, i32* %call11, align 4, !dbg !554
  %sub12 = sub nsw i32 0, %6, !dbg !555
  store i32 %sub12, i32* %retval, align 4, !dbg !556
  br label %return, !dbg !556

if.end13:                                         ; preds = %skip
  %7 = load i32*, i32** %fds.addr, align 8, !dbg !557
  %arrayidx = getelementptr inbounds i32, i32* %7, i64 0, !dbg !557
  %8 = load i32, i32* %arrayidx, align 4, !dbg !557
  %call14 = call i32 @uv__cloexec_ioctl(i32 %8, i32 1), !dbg !558
  %9 = load i32*, i32** %fds.addr, align 8, !dbg !559
  %arrayidx15 = getelementptr inbounds i32, i32* %9, i64 1, !dbg !559
  %10 = load i32, i32* %arrayidx15, align 4, !dbg !559
  %call16 = call i32 @uv__cloexec_ioctl(i32 %10, i32 1), !dbg !560
  %11 = load i32, i32* %flags.addr, align 4, !dbg !561
  %and = and i32 %11, 2048, !dbg !563
  %tobool17 = icmp ne i32 %and, 0, !dbg !563
  br i1 %tobool17, label %if.then18, label %if.end23, !dbg !564

if.then18:                                        ; preds = %if.end13
  %12 = load i32*, i32** %fds.addr, align 8, !dbg !565
  %arrayidx19 = getelementptr inbounds i32, i32* %12, i64 0, !dbg !565
  %13 = load i32, i32* %arrayidx19, align 4, !dbg !565
  %call20 = call i32 @uv__nonblock_ioctl(i32 %13, i32 1), !dbg !567
  %14 = load i32*, i32** %fds.addr, align 8, !dbg !568
  %arrayidx21 = getelementptr inbounds i32, i32* %14, i64 1, !dbg !568
  %15 = load i32, i32* %arrayidx21, align 4, !dbg !568
  %call22 = call i32 @uv__nonblock_ioctl(i32 %15, i32 1), !dbg !569
  br label %if.end23, !dbg !570

if.end23:                                         ; preds = %if.then18, %if.end13
  store i32 0, i32* %retval, align 4, !dbg !571
  br label %return, !dbg !571

return:                                           ; preds = %if.end23, %if.then10, %if.then5, %if.then1
  %16 = load i32, i32* %retval, align 4, !dbg !572
  ret i32 %16, !dbg !572
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind
declare i32 @socketpair(i32, i32, i32, i32*) #2

; Function Attrs: nounwind readnone
declare i32* @__errno_location() #3

declare i32 @uv__cloexec_ioctl(i32, i32) #4

declare i32 @uv__nonblock_ioctl(i32, i32) #4

; Function Attrs: nounwind uwtable
define i32 @uv__make_pipe(i32* %fds, i32 %flags) #0 !dbg !454 {
entry:
  %retval = alloca i32, align 4
  %fds.addr = alloca i32*, align 8
  %flags.addr = alloca i32, align 4
  store i32* %fds, i32** %fds.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %fds.addr, metadata !573, metadata !525), !dbg !574
  store i32 %flags, i32* %flags.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %flags.addr, metadata !575, metadata !525), !dbg !576
  %0 = load i32, i32* @uv__make_pipe.no_pipe2, align 4, !dbg !577
  %tobool = icmp ne i32 %0, 0, !dbg !577
  br i1 %tobool, label %if.then, label %if.end, !dbg !579

if.then:                                          ; preds = %entry
  br label %skip, !dbg !580

if.end:                                           ; preds = %entry
  %1 = load i32*, i32** %fds.addr, align 8, !dbg !581
  %2 = load i32, i32* %flags.addr, align 4, !dbg !583
  %or = or i32 %2, 524288, !dbg !584
  %call = call i32 @uv__pipe2(i32* %1, i32 %or), !dbg !585
  %cmp = icmp eq i32 %call, 0, !dbg !586
  br i1 %cmp, label %if.then1, label %if.end2, !dbg !587

if.then1:                                         ; preds = %if.end
  store i32 0, i32* %retval, align 4, !dbg !588
  br label %return, !dbg !588

if.end2:                                          ; preds = %if.end
  %call3 = call i32* @__errno_location() #1, !dbg !589
  %3 = load i32, i32* %call3, align 4, !dbg !589
  %cmp4 = icmp ne i32 %3, 38, !dbg !591
  br i1 %cmp4, label %if.then5, label %if.end7, !dbg !592

if.then5:                                         ; preds = %if.end2
  %call6 = call i32* @__errno_location() #1, !dbg !593
  %4 = load i32, i32* %call6, align 4, !dbg !593
  %sub = sub nsw i32 0, %4, !dbg !594
  store i32 %sub, i32* %retval, align 4, !dbg !595
  br label %return, !dbg !595

if.end7:                                          ; preds = %if.end2
  store i32 1, i32* @uv__make_pipe.no_pipe2, align 4, !dbg !596
  br label %skip, !dbg !597

skip:                                             ; preds = %if.end7, %if.then
  %5 = load i32*, i32** %fds.addr, align 8, !dbg !598
  %call8 = call i32 @pipe(i32* %5) #8, !dbg !600
  %tobool9 = icmp ne i32 %call8, 0, !dbg !600
  br i1 %tobool9, label %if.then10, label %if.end13, !dbg !601

if.then10:                                        ; preds = %skip
  %call11 = call i32* @__errno_location() #1, !dbg !602
  %6 = load i32, i32* %call11, align 4, !dbg !602
  %sub12 = sub nsw i32 0, %6, !dbg !603
  store i32 %sub12, i32* %retval, align 4, !dbg !604
  br label %return, !dbg !604

if.end13:                                         ; preds = %skip
  %7 = load i32*, i32** %fds.addr, align 8, !dbg !605
  %arrayidx = getelementptr inbounds i32, i32* %7, i64 0, !dbg !605
  %8 = load i32, i32* %arrayidx, align 4, !dbg !605
  %call14 = call i32 @uv__cloexec_ioctl(i32 %8, i32 1), !dbg !606
  %9 = load i32*, i32** %fds.addr, align 8, !dbg !607
  %arrayidx15 = getelementptr inbounds i32, i32* %9, i64 1, !dbg !607
  %10 = load i32, i32* %arrayidx15, align 4, !dbg !607
  %call16 = call i32 @uv__cloexec_ioctl(i32 %10, i32 1), !dbg !608
  %11 = load i32, i32* %flags.addr, align 4, !dbg !609
  %and = and i32 %11, 2048, !dbg !611
  %tobool17 = icmp ne i32 %and, 0, !dbg !611
  br i1 %tobool17, label %if.then18, label %if.end23, !dbg !612

if.then18:                                        ; preds = %if.end13
  %12 = load i32*, i32** %fds.addr, align 8, !dbg !613
  %arrayidx19 = getelementptr inbounds i32, i32* %12, i64 0, !dbg !613
  %13 = load i32, i32* %arrayidx19, align 4, !dbg !613
  %call20 = call i32 @uv__nonblock_ioctl(i32 %13, i32 1), !dbg !615
  %14 = load i32*, i32** %fds.addr, align 8, !dbg !616
  %arrayidx21 = getelementptr inbounds i32, i32* %14, i64 1, !dbg !616
  %15 = load i32, i32* %arrayidx21, align 4, !dbg !616
  %call22 = call i32 @uv__nonblock_ioctl(i32 %15, i32 1), !dbg !617
  br label %if.end23, !dbg !618

if.end23:                                         ; preds = %if.then18, %if.end13
  store i32 0, i32* %retval, align 4, !dbg !619
  br label %return, !dbg !619

return:                                           ; preds = %if.end23, %if.then10, %if.then5, %if.then1
  %16 = load i32, i32* %retval, align 4, !dbg !620
  ret i32 %16, !dbg !620
}

declare i32 @uv__pipe2(i32*, i32) #4

; Function Attrs: nounwind
declare i32 @pipe(i32*) #2

; Function Attrs: nounwind uwtable
define i32 @uv_spawn(%struct.uv_loop_s* %loop, %struct.uv_process_s* %process, %struct.uv_process_options_s* %options) #0 !dbg !455 {
entry:
  %retval = alloca i32, align 4
  %loop.addr = alloca %struct.uv_loop_s*, align 8
  %process.addr = alloca %struct.uv_process_s*, align 8
  %options.addr = alloca %struct.uv_process_options_s*, align 8
  %signal_pipe = alloca [2 x i32], align 4
  %pipes = alloca [2 x i32]*, align 8
  %stdio_count = alloca i32, align 4
  %r = alloca i64, align 8
  %pid = alloca i32, align 4
  %err = alloca i32, align 4
  %exec_errorno = alloca i32, align 4
  %i = alloca i32, align 4
  %status = alloca i32, align 4
  store %struct.uv_loop_s* %loop, %struct.uv_loop_s** %loop.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop.addr, metadata !621, metadata !525), !dbg !622
  store %struct.uv_process_s* %process, %struct.uv_process_s** %process.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_process_s** %process.addr, metadata !623, metadata !525), !dbg !624
  store %struct.uv_process_options_s* %options, %struct.uv_process_options_s** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_process_options_s** %options.addr, metadata !625, metadata !525), !dbg !626
  call void @llvm.dbg.declare(metadata [2 x i32]* %signal_pipe, metadata !627, metadata !525), !dbg !628
  %0 = bitcast [2 x i32]* %signal_pipe to i8*, !dbg !628
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* bitcast ([2 x i32]* @uv_spawn.signal_pipe to i8*), i64 8, i32 4, i1 false), !dbg !628
  call void @llvm.dbg.declare(metadata [2 x i32]** %pipes, metadata !629, metadata !525), !dbg !630
  call void @llvm.dbg.declare(metadata i32* %stdio_count, metadata !631, metadata !525), !dbg !632
  call void @llvm.dbg.declare(metadata i64* %r, metadata !633, metadata !525), !dbg !634
  call void @llvm.dbg.declare(metadata i32* %pid, metadata !635, metadata !525), !dbg !638
  call void @llvm.dbg.declare(metadata i32* %err, metadata !639, metadata !525), !dbg !640
  call void @llvm.dbg.declare(metadata i32* %exec_errorno, metadata !641, metadata !525), !dbg !642
  call void @llvm.dbg.declare(metadata i32* %i, metadata !643, metadata !525), !dbg !644
  call void @llvm.dbg.declare(metadata i32* %status, metadata !645, metadata !525), !dbg !646
  %1 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !647
  %file = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %1, i32 0, i32 1, !dbg !647
  %2 = load i8*, i8** %file, align 8, !dbg !647
  %cmp = icmp ne i8* %2, null, !dbg !647
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !647

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !648

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 403, i8* getelementptr inbounds ([72 x i8], [72 x i8]* @__PRETTY_FUNCTION__.uv_spawn, i32 0, i32 0)) #9, !dbg !650
  unreachable, !dbg !650
                                                  ; No predecessors!
  br label %cond.end, !dbg !652

cond.end:                                         ; preds = %3, %cond.true
  %4 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !654
  %flags = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %4, i32 0, i32 5, !dbg !654
  %5 = load i32, i32* %flags, align 8, !dbg !654
  %and = and i32 %5, -32, !dbg !654
  %tobool = icmp ne i32 %and, 0, !dbg !654
  br i1 %tobool, label %cond.false2, label %cond.true1, !dbg !654

cond.true1:                                       ; preds = %cond.end
  br label %cond.end3, !dbg !655

cond.false2:                                      ; preds = %cond.end
  call void @__assert_fail(i8* getelementptr inbounds ([149 x i8], [149 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 408, i8* getelementptr inbounds ([72 x i8], [72 x i8]* @__PRETTY_FUNCTION__.uv_spawn, i32 0, i32 0)) #9, !dbg !656
  unreachable, !dbg !656
                                                  ; No predecessors!
  br label %cond.end3, !dbg !657

cond.end3:                                        ; preds = %6, %cond.true1
  br label %do.body, !dbg !658

do.body:                                          ; preds = %cond.end3
  %7 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !659
  %8 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !659
  %9 = bitcast %struct.uv_process_s* %8 to %struct.uv_handle_s*, !dbg !659
  %loop4 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %9, i32 0, i32 1, !dbg !659
  store %struct.uv_loop_s* %7, %struct.uv_loop_s** %loop4, align 8, !dbg !659
  %10 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !659
  %11 = bitcast %struct.uv_process_s* %10 to %struct.uv_handle_s*, !dbg !659
  %type = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %11, i32 0, i32 2, !dbg !659
  store i32 10, i32* %type, align 8, !dbg !659
  %12 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !659
  %13 = bitcast %struct.uv_process_s* %12 to %struct.uv_handle_s*, !dbg !659
  %flags5 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %13, i32 0, i32 7, !dbg !659
  store i32 8192, i32* %flags5, align 8, !dbg !659
  br label %do.body6, !dbg !659

do.body6:                                         ; preds = %do.body
  %14 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !662
  %handle_queue = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %14, i32 0, i32 2, !dbg !662
  %15 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !662
  %16 = bitcast %struct.uv_process_s* %15 to %struct.uv_handle_s*, !dbg !662
  %handle_queue7 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %16, i32 0, i32 4, !dbg !662
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue7, i64 0, i64 0, !dbg !662
  %17 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !662
  store [2 x i8*]* %handle_queue, [2 x i8*]** %17, align 8, !dbg !662
  %18 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !662
  %handle_queue8 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %18, i32 0, i32 2, !dbg !662
  %arrayidx9 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue8, i64 0, i64 1, !dbg !662
  %19 = bitcast i8** %arrayidx9 to [2 x i8*]**, !dbg !662
  %20 = load [2 x i8*]*, [2 x i8*]** %19, align 8, !dbg !662
  %21 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !662
  %22 = bitcast %struct.uv_process_s* %21 to %struct.uv_handle_s*, !dbg !662
  %handle_queue10 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %22, i32 0, i32 4, !dbg !662
  %arrayidx11 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue10, i64 0, i64 1, !dbg !662
  %23 = bitcast i8** %arrayidx11 to [2 x i8*]**, !dbg !662
  store [2 x i8*]* %20, [2 x i8*]** %23, align 8, !dbg !662
  %24 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !662
  %25 = bitcast %struct.uv_process_s* %24 to %struct.uv_handle_s*, !dbg !662
  %handle_queue12 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %25, i32 0, i32 4, !dbg !662
  %26 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !662
  %27 = bitcast %struct.uv_process_s* %26 to %struct.uv_handle_s*, !dbg !662
  %handle_queue13 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %27, i32 0, i32 4, !dbg !662
  %arrayidx14 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue13, i64 0, i64 1, !dbg !662
  %28 = bitcast i8** %arrayidx14 to [2 x i8*]**, !dbg !662
  %29 = load [2 x i8*]*, [2 x i8*]** %28, align 8, !dbg !662
  %arrayidx15 = getelementptr inbounds [2 x i8*], [2 x i8*]* %29, i64 0, i64 0, !dbg !662
  %30 = bitcast i8** %arrayidx15 to [2 x i8*]**, !dbg !662
  store [2 x i8*]* %handle_queue12, [2 x i8*]** %30, align 8, !dbg !662
  %31 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !662
  %32 = bitcast %struct.uv_process_s* %31 to %struct.uv_handle_s*, !dbg !662
  %handle_queue16 = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %32, i32 0, i32 4, !dbg !662
  %33 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !662
  %handle_queue17 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %33, i32 0, i32 2, !dbg !662
  %arrayidx18 = getelementptr inbounds [2 x i8*], [2 x i8*]* %handle_queue17, i64 0, i64 1, !dbg !662
  %34 = bitcast i8** %arrayidx18 to [2 x i8*]**, !dbg !662
  store [2 x i8*]* %handle_queue16, [2 x i8*]** %34, align 8, !dbg !662
  br label %do.end, !dbg !662

do.end:                                           ; preds = %do.body6
  %35 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !665
  %36 = bitcast %struct.uv_process_s* %35 to %struct.uv_handle_s*, !dbg !665
  %next_closing = getelementptr inbounds %struct.uv_handle_s, %struct.uv_handle_s* %36, i32 0, i32 6, !dbg !665
  store %struct.uv_handle_s* null, %struct.uv_handle_s** %next_closing, align 8, !dbg !665
  br label %do.end19, !dbg !665

do.end19:                                         ; preds = %do.end
  br label %do.body20, !dbg !667

do.body20:                                        ; preds = %do.end19
  %37 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !668
  %queue = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %37, i32 0, i32 10, !dbg !668
  %38 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !668
  %queue21 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %38, i32 0, i32 10, !dbg !668
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue21, i64 0, i64 0, !dbg !668
  %39 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !668
  store [2 x i8*]* %queue, [2 x i8*]** %39, align 8, !dbg !668
  %40 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !668
  %queue23 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %40, i32 0, i32 10, !dbg !668
  %41 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !668
  %queue24 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %41, i32 0, i32 10, !dbg !668
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue24, i64 0, i64 1, !dbg !668
  %42 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !668
  store [2 x i8*]* %queue23, [2 x i8*]** %42, align 8, !dbg !668
  br label %do.end26, !dbg !668

do.end26:                                         ; preds = %do.body20
  %43 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !671
  %stdio_count27 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %43, i32 0, i32 6, !dbg !672
  %44 = load i32, i32* %stdio_count27, align 4, !dbg !672
  store i32 %44, i32* %stdio_count, align 4, !dbg !673
  %45 = load i32, i32* %stdio_count, align 4, !dbg !674
  %cmp28 = icmp slt i32 %45, 3, !dbg !676
  br i1 %cmp28, label %if.then, label %if.end, !dbg !677

if.then:                                          ; preds = %do.end26
  store i32 3, i32* %stdio_count, align 4, !dbg !678
  br label %if.end, !dbg !679

if.end:                                           ; preds = %if.then, %do.end26
  store i32 -12, i32* %err, align 4, !dbg !680
  %46 = load i32, i32* %stdio_count, align 4, !dbg !681
  %conv = sext i32 %46 to i64, !dbg !681
  %mul = mul i64 %conv, 8, !dbg !682
  %call = call i8* @uv__malloc(i64 %mul), !dbg !683
  %47 = bitcast i8* %call to [2 x i32]*, !dbg !683
  store [2 x i32]* %47, [2 x i32]** %pipes, align 8, !dbg !684
  %48 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !685
  %cmp29 = icmp eq [2 x i32]* %48, null, !dbg !687
  br i1 %cmp29, label %if.then31, label %if.end32, !dbg !688

if.then31:                                        ; preds = %if.end
  br label %error, !dbg !689

if.end32:                                         ; preds = %if.end
  store i32 0, i32* %i, align 4, !dbg !690
  br label %for.cond, !dbg !692

for.cond:                                         ; preds = %for.inc, %if.end32
  %49 = load i32, i32* %i, align 4, !dbg !693
  %50 = load i32, i32* %stdio_count, align 4, !dbg !696
  %cmp33 = icmp slt i32 %49, %50, !dbg !697
  br i1 %cmp33, label %for.body, label %for.end, !dbg !698

for.body:                                         ; preds = %for.cond
  %51 = load i32, i32* %i, align 4, !dbg !699
  %idxprom = sext i32 %51 to i64, !dbg !701
  %52 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !701
  %arrayidx35 = getelementptr inbounds [2 x i32], [2 x i32]* %52, i64 %idxprom, !dbg !701
  %arrayidx36 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx35, i64 0, i64 0, !dbg !701
  store i32 -1, i32* %arrayidx36, align 4, !dbg !702
  %53 = load i32, i32* %i, align 4, !dbg !703
  %idxprom37 = sext i32 %53 to i64, !dbg !704
  %54 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !704
  %arrayidx38 = getelementptr inbounds [2 x i32], [2 x i32]* %54, i64 %idxprom37, !dbg !704
  %arrayidx39 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx38, i64 0, i64 1, !dbg !704
  store i32 -1, i32* %arrayidx39, align 4, !dbg !705
  br label %for.inc, !dbg !706

for.inc:                                          ; preds = %for.body
  %55 = load i32, i32* %i, align 4, !dbg !707
  %inc = add nsw i32 %55, 1, !dbg !707
  store i32 %inc, i32* %i, align 4, !dbg !707
  br label %for.cond, !dbg !709

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %i, align 4, !dbg !710
  br label %for.cond40, !dbg !712

for.cond40:                                       ; preds = %for.inc51, %for.end
  %56 = load i32, i32* %i, align 4, !dbg !713
  %57 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !716
  %stdio_count41 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %57, i32 0, i32 6, !dbg !717
  %58 = load i32, i32* %stdio_count41, align 4, !dbg !717
  %cmp42 = icmp slt i32 %56, %58, !dbg !718
  br i1 %cmp42, label %for.body44, label %for.end53, !dbg !719

for.body44:                                       ; preds = %for.cond40
  %59 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !720
  %stdio = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %59, i32 0, i32 7, !dbg !722
  %60 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %stdio, align 8, !dbg !722
  %61 = load i32, i32* %i, align 4, !dbg !723
  %idx.ext = sext i32 %61 to i64, !dbg !724
  %add.ptr = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %60, i64 %idx.ext, !dbg !724
  %62 = load i32, i32* %i, align 4, !dbg !725
  %idxprom45 = sext i32 %62 to i64, !dbg !726
  %63 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !726
  %arrayidx46 = getelementptr inbounds [2 x i32], [2 x i32]* %63, i64 %idxprom45, !dbg !726
  %arraydecay = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx46, i32 0, i32 0, !dbg !726
  %call47 = call i32 @uv__process_init_stdio(%struct.uv_stdio_container_s* %add.ptr, i32* %arraydecay), !dbg !727
  store i32 %call47, i32* %err, align 4, !dbg !728
  %64 = load i32, i32* %err, align 4, !dbg !729
  %tobool48 = icmp ne i32 %64, 0, !dbg !729
  br i1 %tobool48, label %if.then49, label %if.end50, !dbg !731

if.then49:                                        ; preds = %for.body44
  br label %error, !dbg !732

if.end50:                                         ; preds = %for.body44
  br label %for.inc51, !dbg !733

for.inc51:                                        ; preds = %if.end50
  %65 = load i32, i32* %i, align 4, !dbg !734
  %inc52 = add nsw i32 %65, 1, !dbg !734
  store i32 %inc52, i32* %i, align 4, !dbg !734
  br label %for.cond40, !dbg !736

for.end53:                                        ; preds = %for.cond40
  %arraydecay54 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipe, i32 0, i32 0, !dbg !737
  %call55 = call i32 @uv__make_pipe(i32* %arraydecay54, i32 0), !dbg !738
  store i32 %call55, i32* %err, align 4, !dbg !739
  %66 = load i32, i32* %err, align 4, !dbg !740
  %tobool56 = icmp ne i32 %66, 0, !dbg !740
  br i1 %tobool56, label %if.then57, label %if.end58, !dbg !742

if.then57:                                        ; preds = %for.end53
  br label %error, !dbg !743

if.end58:                                         ; preds = %for.end53
  %67 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !744
  %child_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %67, i32 0, i32 30, !dbg !745
  %call59 = call i32 @uv_signal_start(%struct.uv_signal_s* %child_watcher, void (%struct.uv_signal_s*, i32)* @uv__chld, i32 17), !dbg !746
  %68 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !747
  %cloexec_lock = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %68, i32 0, i32 15, !dbg !748
  call void @uv_rwlock_wrlock(%union.pthread_rwlock_t* %cloexec_lock), !dbg !749
  %call60 = call i32 @fork() #8, !dbg !750
  store i32 %call60, i32* %pid, align 4, !dbg !751
  %69 = load i32, i32* %pid, align 4, !dbg !752
  %cmp61 = icmp eq i32 %69, -1, !dbg !754
  br i1 %cmp61, label %if.then63, label %if.end70, !dbg !755

if.then63:                                        ; preds = %if.end58
  %call64 = call i32* @__errno_location() #1, !dbg !756
  %70 = load i32, i32* %call64, align 4, !dbg !756
  %sub = sub nsw i32 0, %70, !dbg !758
  store i32 %sub, i32* %err, align 4, !dbg !759
  %71 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !760
  %cloexec_lock65 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %71, i32 0, i32 15, !dbg !761
  call void @uv_rwlock_wrunlock(%union.pthread_rwlock_t* %cloexec_lock65), !dbg !762
  %arrayidx66 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipe, i64 0, i64 0, !dbg !763
  %72 = load i32, i32* %arrayidx66, align 4, !dbg !763
  %call67 = call i32 @uv__close(i32 %72), !dbg !764
  %arrayidx68 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipe, i64 0, i64 1, !dbg !765
  %73 = load i32, i32* %arrayidx68, align 4, !dbg !765
  %call69 = call i32 @uv__close(i32 %73), !dbg !766
  br label %error, !dbg !767

if.end70:                                         ; preds = %if.end58
  %74 = load i32, i32* %pid, align 4, !dbg !768
  %cmp71 = icmp eq i32 %74, 0, !dbg !770
  br i1 %cmp71, label %if.then73, label %if.end75, !dbg !771

if.then73:                                        ; preds = %if.end70
  %75 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !772
  %76 = load i32, i32* %stdio_count, align 4, !dbg !774
  %77 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !775
  %arrayidx74 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipe, i64 0, i64 1, !dbg !776
  %78 = load i32, i32* %arrayidx74, align 4, !dbg !776
  call void @uv__process_child_init(%struct.uv_process_options_s* %75, i32 %76, [2 x i32]* %77, i32 %78), !dbg !777
  call void @abort() #9, !dbg !778
  unreachable, !dbg !778

if.end75:                                         ; preds = %if.end70
  %79 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !779
  %cloexec_lock76 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %79, i32 0, i32 15, !dbg !780
  call void @uv_rwlock_wrunlock(%union.pthread_rwlock_t* %cloexec_lock76), !dbg !781
  %arrayidx77 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipe, i64 0, i64 1, !dbg !782
  %80 = load i32, i32* %arrayidx77, align 4, !dbg !782
  %call78 = call i32 @uv__close(i32 %80), !dbg !783
  %81 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !784
  %status79 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %81, i32 0, i32 11, !dbg !785
  store i32 0, i32* %status79, align 8, !dbg !786
  store i32 0, i32* %exec_errorno, align 4, !dbg !787
  br label %do.body80, !dbg !788

do.body80:                                        ; preds = %land.end, %if.end75
  %arrayidx81 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipe, i64 0, i64 0, !dbg !789
  %82 = load i32, i32* %arrayidx81, align 4, !dbg !789
  %83 = bitcast i32* %exec_errorno to i8*, !dbg !790
  %call82 = call i64 @read(i32 %82, i8* %83, i64 4), !dbg !791
  store i64 %call82, i64* %r, align 8, !dbg !792
  br label %do.cond, !dbg !793

do.cond:                                          ; preds = %do.body80
  %84 = load i64, i64* %r, align 8, !dbg !794
  %cmp83 = icmp eq i64 %84, -1, !dbg !795
  br i1 %cmp83, label %land.rhs, label %land.end, !dbg !796

land.rhs:                                         ; preds = %do.cond
  %call85 = call i32* @__errno_location() #1, !dbg !797
  %85 = load i32, i32* %call85, align 4, !dbg !797
  %cmp86 = icmp eq i32 %85, 4, !dbg !798
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %86 = phi i1 [ false, %do.cond ], [ %cmp86, %land.rhs ]
  br i1 %86, label %do.body80, label %do.end88, !dbg !799

do.end88:                                         ; preds = %land.end
  %87 = load i64, i64* %r, align 8, !dbg !800
  %cmp89 = icmp eq i64 %87, 0, !dbg !802
  br i1 %cmp89, label %if.then91, label %if.else, !dbg !803

if.then91:                                        ; preds = %do.end88
  br label %if.end137, !dbg !804

if.else:                                          ; preds = %do.end88
  %88 = load i64, i64* %r, align 8, !dbg !805
  %cmp92 = icmp eq i64 %88, 4, !dbg !807
  br i1 %cmp92, label %if.then94, label %if.else111, !dbg !808

if.then94:                                        ; preds = %if.else
  br label %do.body95, !dbg !809

do.body95:                                        ; preds = %land.end104, %if.then94
  %89 = load i32, i32* %pid, align 4, !dbg !811
  %call96 = call i32 @waitpid(i32 %89, i32* %status, i32 0), !dbg !812
  store i32 %call96, i32* %err, align 4, !dbg !813
  br label %do.cond97, !dbg !814

do.cond97:                                        ; preds = %do.body95
  %90 = load i32, i32* %err, align 4, !dbg !815
  %cmp98 = icmp eq i32 %90, -1, !dbg !816
  br i1 %cmp98, label %land.rhs100, label %land.end104, !dbg !817

land.rhs100:                                      ; preds = %do.cond97
  %call101 = call i32* @__errno_location() #1, !dbg !818
  %91 = load i32, i32* %call101, align 4, !dbg !818
  %cmp102 = icmp eq i32 %91, 4, !dbg !820
  br label %land.end104

land.end104:                                      ; preds = %land.rhs100, %do.cond97
  %92 = phi i1 [ false, %do.cond97 ], [ %cmp102, %land.rhs100 ]
  br i1 %92, label %do.body95, label %do.end105, !dbg !821

do.end105:                                        ; preds = %land.end104
  %93 = load i32, i32* %err, align 4, !dbg !822
  %94 = load i32, i32* %pid, align 4, !dbg !822
  %cmp106 = icmp eq i32 %93, %94, !dbg !822
  br i1 %cmp106, label %cond.true108, label %cond.false109, !dbg !822

cond.true108:                                     ; preds = %do.end105
  br label %cond.end110, !dbg !823

cond.false109:                                    ; preds = %do.end105
  call void @__assert_fail(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 492, i8* getelementptr inbounds ([72 x i8], [72 x i8]* @__PRETTY_FUNCTION__.uv_spawn, i32 0, i32 0)) #9, !dbg !824
  unreachable, !dbg !824
                                                  ; No predecessors!
  br label %cond.end110, !dbg !826

cond.end110:                                      ; preds = %95, %cond.true108
  br label %if.end136, !dbg !828

if.else111:                                       ; preds = %if.else
  %96 = load i64, i64* %r, align 8, !dbg !829
  %cmp112 = icmp eq i64 %96, -1, !dbg !832
  br i1 %cmp112, label %land.lhs.true, label %if.else134, !dbg !833

land.lhs.true:                                    ; preds = %if.else111
  %call114 = call i32* @__errno_location() #1, !dbg !834
  %97 = load i32, i32* %call114, align 4, !dbg !834
  %cmp115 = icmp eq i32 %97, 32, !dbg !836
  br i1 %cmp115, label %if.then117, label %if.else134, !dbg !837

if.then117:                                       ; preds = %land.lhs.true
  br label %do.body118, !dbg !838

do.body118:                                       ; preds = %land.end127, %if.then117
  %98 = load i32, i32* %pid, align 4, !dbg !840
  %call119 = call i32 @waitpid(i32 %98, i32* %status, i32 0), !dbg !841
  store i32 %call119, i32* %err, align 4, !dbg !842
  br label %do.cond120, !dbg !843

do.cond120:                                       ; preds = %do.body118
  %99 = load i32, i32* %err, align 4, !dbg !844
  %cmp121 = icmp eq i32 %99, -1, !dbg !845
  br i1 %cmp121, label %land.rhs123, label %land.end127, !dbg !846

land.rhs123:                                      ; preds = %do.cond120
  %call124 = call i32* @__errno_location() #1, !dbg !847
  %100 = load i32, i32* %call124, align 4, !dbg !847
  %cmp125 = icmp eq i32 %100, 4, !dbg !849
  br label %land.end127

land.end127:                                      ; preds = %land.rhs123, %do.cond120
  %101 = phi i1 [ false, %do.cond120 ], [ %cmp125, %land.rhs123 ]
  br i1 %101, label %do.body118, label %do.end128, !dbg !850

do.end128:                                        ; preds = %land.end127
  %102 = load i32, i32* %err, align 4, !dbg !851
  %103 = load i32, i32* %pid, align 4, !dbg !851
  %cmp129 = icmp eq i32 %102, %103, !dbg !851
  br i1 %cmp129, label %cond.true131, label %cond.false132, !dbg !851

cond.true131:                                     ; preds = %do.end128
  br label %cond.end133, !dbg !852

cond.false132:                                    ; preds = %do.end128
  call void @__assert_fail(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 497, i8* getelementptr inbounds ([72 x i8], [72 x i8]* @__PRETTY_FUNCTION__.uv_spawn, i32 0, i32 0)) #9, !dbg !853
  unreachable, !dbg !853
                                                  ; No predecessors!
  br label %cond.end133, !dbg !855

cond.end133:                                      ; preds = %104, %cond.true131
  br label %if.end135, !dbg !857

if.else134:                                       ; preds = %land.lhs.true, %if.else111
  call void @abort() #9, !dbg !858
  unreachable, !dbg !858

if.end135:                                        ; preds = %cond.end133
  br label %if.end136

if.end136:                                        ; preds = %if.end135, %cond.end110
  br label %if.end137

if.end137:                                        ; preds = %if.end136, %if.then91
  %arrayidx138 = getelementptr inbounds [2 x i32], [2 x i32]* %signal_pipe, i64 0, i64 0, !dbg !859
  %105 = load i32, i32* %arrayidx138, align 4, !dbg !859
  %call139 = call i32 @uv__close_nocheckstdio(i32 %105), !dbg !860
  store i32 0, i32* %i, align 4, !dbg !861
  br label %for.cond140, !dbg !863

for.cond140:                                      ; preds = %for.inc162, %if.end137
  %106 = load i32, i32* %i, align 4, !dbg !864
  %107 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !867
  %stdio_count141 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %107, i32 0, i32 6, !dbg !868
  %108 = load i32, i32* %stdio_count141, align 4, !dbg !868
  %cmp142 = icmp slt i32 %106, %108, !dbg !869
  br i1 %cmp142, label %for.body144, label %for.end164, !dbg !870

for.body144:                                      ; preds = %for.cond140
  %109 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !871
  %stdio145 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %109, i32 0, i32 7, !dbg !873
  %110 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %stdio145, align 8, !dbg !873
  %111 = load i32, i32* %i, align 4, !dbg !874
  %idx.ext146 = sext i32 %111 to i64, !dbg !875
  %add.ptr147 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %110, i64 %idx.ext146, !dbg !875
  %112 = load i32, i32* %i, align 4, !dbg !876
  %idxprom148 = sext i32 %112 to i64, !dbg !877
  %113 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !877
  %arrayidx149 = getelementptr inbounds [2 x i32], [2 x i32]* %113, i64 %idxprom148, !dbg !877
  %arraydecay150 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx149, i32 0, i32 0, !dbg !877
  %114 = load i32, i32* %i, align 4, !dbg !878
  %cmp151 = icmp eq i32 %114, 0, !dbg !879
  %conv152 = zext i1 %cmp151 to i32, !dbg !879
  %call153 = call i32 @uv__process_open_stream(%struct.uv_stdio_container_s* %add.ptr147, i32* %arraydecay150, i32 %conv152), !dbg !880
  store i32 %call153, i32* %err, align 4, !dbg !881
  %115 = load i32, i32* %err, align 4, !dbg !882
  %cmp154 = icmp eq i32 %115, 0, !dbg !884
  br i1 %cmp154, label %if.then156, label %if.end157, !dbg !885

if.then156:                                       ; preds = %for.body144
  br label %for.inc162, !dbg !886

if.end157:                                        ; preds = %for.body144
  br label %while.cond, !dbg !887

while.cond:                                       ; preds = %while.body, %if.end157
  %116 = load i32, i32* %i, align 4, !dbg !888
  %dec = add nsw i32 %116, -1, !dbg !888
  store i32 %dec, i32* %i, align 4, !dbg !888
  %tobool158 = icmp ne i32 %116, 0, !dbg !890
  br i1 %tobool158, label %while.body, label %while.end, !dbg !890

while.body:                                       ; preds = %while.cond
  %117 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !891
  %stdio159 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %117, i32 0, i32 7, !dbg !892
  %118 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %stdio159, align 8, !dbg !892
  %119 = load i32, i32* %i, align 4, !dbg !893
  %idx.ext160 = sext i32 %119 to i64, !dbg !894
  %add.ptr161 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %118, i64 %idx.ext160, !dbg !894
  call void @uv__process_close_stream(%struct.uv_stdio_container_s* %add.ptr161), !dbg !895
  br label %while.cond, !dbg !896

while.end:                                        ; preds = %while.cond
  br label %error, !dbg !898

for.inc162:                                       ; preds = %if.then156
  %120 = load i32, i32* %i, align 4, !dbg !899
  %inc163 = add nsw i32 %120, 1, !dbg !899
  store i32 %inc163, i32* %i, align 4, !dbg !899
  br label %for.cond140, !dbg !901

for.end164:                                       ; preds = %for.cond140
  %121 = load i32, i32* %exec_errorno, align 4, !dbg !902
  %cmp165 = icmp eq i32 %121, 0, !dbg !904
  br i1 %cmp165, label %if.then167, label %if.end212, !dbg !905

if.then167:                                       ; preds = %for.end164
  br label %do.body168, !dbg !906

do.body168:                                       ; preds = %if.then167
  %122 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !908
  %process_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %122, i32 0, i32 17, !dbg !908
  %123 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !908
  %queue169 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %123, i32 0, i32 10, !dbg !908
  %arrayidx170 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue169, i64 0, i64 0, !dbg !908
  %124 = bitcast i8** %arrayidx170 to [2 x i8*]**, !dbg !908
  store [2 x i8*]* %process_handles, [2 x i8*]** %124, align 8, !dbg !908
  %125 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !908
  %process_handles171 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %125, i32 0, i32 17, !dbg !908
  %arrayidx172 = getelementptr inbounds [2 x i8*], [2 x i8*]* %process_handles171, i64 0, i64 1, !dbg !908
  %126 = bitcast i8** %arrayidx172 to [2 x i8*]**, !dbg !908
  %127 = load [2 x i8*]*, [2 x i8*]** %126, align 8, !dbg !908
  %128 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !908
  %queue173 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %128, i32 0, i32 10, !dbg !908
  %arrayidx174 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue173, i64 0, i64 1, !dbg !908
  %129 = bitcast i8** %arrayidx174 to [2 x i8*]**, !dbg !908
  store [2 x i8*]* %127, [2 x i8*]** %129, align 8, !dbg !908
  %130 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !908
  %queue175 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %130, i32 0, i32 10, !dbg !908
  %131 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !908
  %queue176 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %131, i32 0, i32 10, !dbg !908
  %arrayidx177 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue176, i64 0, i64 1, !dbg !908
  %132 = bitcast i8** %arrayidx177 to [2 x i8*]**, !dbg !908
  %133 = load [2 x i8*]*, [2 x i8*]** %132, align 8, !dbg !908
  %arrayidx178 = getelementptr inbounds [2 x i8*], [2 x i8*]* %133, i64 0, i64 0, !dbg !908
  %134 = bitcast i8** %arrayidx178 to [2 x i8*]**, !dbg !908
  store [2 x i8*]* %queue175, [2 x i8*]** %134, align 8, !dbg !908
  %135 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !908
  %queue179 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %135, i32 0, i32 10, !dbg !908
  %136 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop.addr, align 8, !dbg !908
  %process_handles180 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %136, i32 0, i32 17, !dbg !908
  %arrayidx181 = getelementptr inbounds [2 x i8*], [2 x i8*]* %process_handles180, i64 0, i64 1, !dbg !908
  %137 = bitcast i8** %arrayidx181 to [2 x i8*]**, !dbg !908
  store [2 x i8*]* %queue179, [2 x i8*]** %137, align 8, !dbg !908
  br label %do.end183, !dbg !908

do.end183:                                        ; preds = %do.body168
  br label %do.body184, !dbg !911

do.body184:                                       ; preds = %do.end183
  %138 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !912
  %flags185 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %138, i32 0, i32 7, !dbg !912
  %139 = load i32, i32* %flags185, align 8, !dbg !912
  %and186 = and i32 %139, 0, !dbg !912
  %cmp187 = icmp eq i32 %and186, 0, !dbg !912
  br i1 %cmp187, label %cond.true189, label %cond.false190, !dbg !912

cond.true189:                                     ; preds = %do.body184
  br label %cond.end191, !dbg !915

cond.false190:                                    ; preds = %do.body184
  call void @__assert_fail(i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 517, i8* getelementptr inbounds ([72 x i8], [72 x i8]* @__PRETTY_FUNCTION__.uv_spawn, i32 0, i32 0)) #9, !dbg !917
  unreachable, !dbg !917
                                                  ; No predecessors!
  br label %cond.end191, !dbg !919

cond.end191:                                      ; preds = %140, %cond.true189
  %141 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !921
  %flags192 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %141, i32 0, i32 7, !dbg !921
  %142 = load i32, i32* %flags192, align 8, !dbg !921
  %and193 = and i32 %142, 16384, !dbg !921
  %cmp194 = icmp ne i32 %and193, 0, !dbg !921
  br i1 %cmp194, label %if.then196, label %if.end197, !dbg !921

if.then196:                                       ; preds = %cond.end191
  br label %do.end211, !dbg !924

if.end197:                                        ; preds = %cond.end191
  %143 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !926
  %flags198 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %143, i32 0, i32 7, !dbg !926
  %144 = load i32, i32* %flags198, align 8, !dbg !926
  %or = or i32 %144, 16384, !dbg !926
  store i32 %or, i32* %flags198, align 8, !dbg !926
  %145 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !926
  %flags199 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %145, i32 0, i32 7, !dbg !926
  %146 = load i32, i32* %flags199, align 8, !dbg !926
  %and200 = and i32 %146, 8192, !dbg !926
  %cmp201 = icmp ne i32 %and200, 0, !dbg !926
  br i1 %cmp201, label %if.then203, label %if.end209, !dbg !926

if.then203:                                       ; preds = %if.end197
  br label %do.body204, !dbg !928

do.body204:                                       ; preds = %if.then203
  %147 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !931
  %loop205 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %147, i32 0, i32 1, !dbg !931
  %148 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop205, align 8, !dbg !931
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %148, i32 0, i32 1, !dbg !931
  %149 = load i32, i32* %active_handles, align 8, !dbg !931
  %inc206 = add i32 %149, 1, !dbg !931
  store i32 %inc206, i32* %active_handles, align 8, !dbg !931
  br label %do.end208, !dbg !931

do.end208:                                        ; preds = %do.body204
  br label %if.end209, !dbg !934

if.end209:                                        ; preds = %do.end208, %if.end197
  br label %do.end211, !dbg !936

do.end211:                                        ; preds = %if.end209, %if.then196
  br label %if.end212, !dbg !938

if.end212:                                        ; preds = %do.end211, %for.end164
  %150 = load i32, i32* %pid, align 4, !dbg !939
  %151 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !940
  %pid213 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %151, i32 0, i32 9, !dbg !941
  store i32 %150, i32* %pid213, align 8, !dbg !942
  %152 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !943
  %exit_cb = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %152, i32 0, i32 0, !dbg !944
  %153 = load void (%struct.uv_process_s*, i64, i32)*, void (%struct.uv_process_s*, i64, i32)** %exit_cb, align 8, !dbg !944
  %154 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !945
  %exit_cb214 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %154, i32 0, i32 8, !dbg !946
  store void (%struct.uv_process_s*, i64, i32)* %153, void (%struct.uv_process_s*, i64, i32)** %exit_cb214, align 8, !dbg !947
  %155 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !948
  %156 = bitcast [2 x i32]* %155 to i8*, !dbg !948
  call void @uv__free(i8* %156), !dbg !949
  %157 = load i32, i32* %exec_errorno, align 4, !dbg !950
  store i32 %157, i32* %retval, align 4, !dbg !951
  br label %return, !dbg !951

error:                                            ; preds = %while.end, %if.then63, %if.then57, %if.then49, %if.then31
  %158 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !952
  %cmp215 = icmp ne [2 x i32]* %158, null, !dbg !954
  br i1 %cmp215, label %if.then217, label %if.end260, !dbg !955

if.then217:                                       ; preds = %error
  store i32 0, i32* %i, align 4, !dbg !956
  br label %for.cond218, !dbg !959

for.cond218:                                      ; preds = %for.inc257, %if.then217
  %159 = load i32, i32* %i, align 4, !dbg !960
  %160 = load i32, i32* %stdio_count, align 4, !dbg !963
  %cmp219 = icmp slt i32 %159, %160, !dbg !964
  br i1 %cmp219, label %for.body221, label %for.end259, !dbg !965

for.body221:                                      ; preds = %for.cond218
  %161 = load i32, i32* %i, align 4, !dbg !966
  %162 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !969
  %stdio_count222 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %162, i32 0, i32 6, !dbg !970
  %163 = load i32, i32* %stdio_count222, align 4, !dbg !970
  %cmp223 = icmp slt i32 %161, %163, !dbg !971
  br i1 %cmp223, label %if.then225, label %if.end234, !dbg !972

if.then225:                                       ; preds = %for.body221
  %164 = load i32, i32* %i, align 4, !dbg !973
  %idxprom226 = sext i32 %164 to i64, !dbg !975
  %165 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !975
  %stdio227 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %165, i32 0, i32 7, !dbg !976
  %166 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %stdio227, align 8, !dbg !976
  %arrayidx228 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %166, i64 %idxprom226, !dbg !975
  %flags229 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %arrayidx228, i32 0, i32 0, !dbg !977
  %167 = load i32, i32* %flags229, align 8, !dbg !977
  %and230 = and i32 %167, 6, !dbg !978
  %tobool231 = icmp ne i32 %and230, 0, !dbg !978
  br i1 %tobool231, label %if.then232, label %if.end233, !dbg !979

if.then232:                                       ; preds = %if.then225
  br label %for.inc257, !dbg !980

if.end233:                                        ; preds = %if.then225
  br label %if.end234, !dbg !981

if.end234:                                        ; preds = %if.end233, %for.body221
  %168 = load i32, i32* %i, align 4, !dbg !983
  %idxprom235 = sext i32 %168 to i64, !dbg !985
  %169 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !985
  %arrayidx236 = getelementptr inbounds [2 x i32], [2 x i32]* %169, i64 %idxprom235, !dbg !985
  %arrayidx237 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx236, i64 0, i64 0, !dbg !985
  %170 = load i32, i32* %arrayidx237, align 4, !dbg !985
  %cmp238 = icmp ne i32 %170, -1, !dbg !986
  br i1 %cmp238, label %if.then240, label %if.end245, !dbg !987

if.then240:                                       ; preds = %if.end234
  %171 = load i32, i32* %i, align 4, !dbg !988
  %idxprom241 = sext i32 %171 to i64, !dbg !989
  %172 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !989
  %arrayidx242 = getelementptr inbounds [2 x i32], [2 x i32]* %172, i64 %idxprom241, !dbg !989
  %arrayidx243 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx242, i64 0, i64 0, !dbg !989
  %173 = load i32, i32* %arrayidx243, align 4, !dbg !989
  %call244 = call i32 @uv__close_nocheckstdio(i32 %173), !dbg !990
  br label %if.end245, !dbg !990

if.end245:                                        ; preds = %if.then240, %if.end234
  %174 = load i32, i32* %i, align 4, !dbg !991
  %idxprom246 = sext i32 %174 to i64, !dbg !993
  %175 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !993
  %arrayidx247 = getelementptr inbounds [2 x i32], [2 x i32]* %175, i64 %idxprom246, !dbg !993
  %arrayidx248 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx247, i64 0, i64 1, !dbg !993
  %176 = load i32, i32* %arrayidx248, align 4, !dbg !993
  %cmp249 = icmp ne i32 %176, -1, !dbg !994
  br i1 %cmp249, label %if.then251, label %if.end256, !dbg !995

if.then251:                                       ; preds = %if.end245
  %177 = load i32, i32* %i, align 4, !dbg !996
  %idxprom252 = sext i32 %177 to i64, !dbg !997
  %178 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !997
  %arrayidx253 = getelementptr inbounds [2 x i32], [2 x i32]* %178, i64 %idxprom252, !dbg !997
  %arrayidx254 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx253, i64 0, i64 1, !dbg !997
  %179 = load i32, i32* %arrayidx254, align 4, !dbg !997
  %call255 = call i32 @uv__close_nocheckstdio(i32 %179), !dbg !998
  br label %if.end256, !dbg !998

if.end256:                                        ; preds = %if.then251, %if.end245
  br label %for.inc257, !dbg !999

for.inc257:                                       ; preds = %if.end256, %if.then232
  %180 = load i32, i32* %i, align 4, !dbg !1000
  %inc258 = add nsw i32 %180, 1, !dbg !1000
  store i32 %inc258, i32* %i, align 4, !dbg !1000
  br label %for.cond218, !dbg !1002

for.end259:                                       ; preds = %for.cond218
  %181 = load [2 x i32]*, [2 x i32]** %pipes, align 8, !dbg !1003
  %182 = bitcast [2 x i32]* %181 to i8*, !dbg !1003
  call void @uv__free(i8* %182), !dbg !1004
  br label %if.end260, !dbg !1005

if.end260:                                        ; preds = %for.end259, %error
  %183 = load i32, i32* %err, align 4, !dbg !1006
  store i32 %183, i32* %retval, align 4, !dbg !1007
  br label %return, !dbg !1007

return:                                           ; preds = %if.end260, %if.end212
  %184 = load i32, i32* %retval, align 4, !dbg !1008
  ret i32 %184, !dbg !1008
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #5

; Function Attrs: noreturn nounwind
declare void @__assert_fail(i8*, i8*, i32, i8*) #6

declare i8* @uv__malloc(i64) #4

; Function Attrs: nounwind uwtable
define internal i32 @uv__process_init_stdio(%struct.uv_stdio_container_s* %container, i32* %fds) #0 !dbg !501 {
entry:
  %retval = alloca i32, align 4
  %container.addr = alloca %struct.uv_stdio_container_s*, align 8
  %fds.addr = alloca i32*, align 8
  %mask = alloca i32, align 4
  %fd = alloca i32, align 4
  store %struct.uv_stdio_container_s* %container, %struct.uv_stdio_container_s** %container.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stdio_container_s** %container.addr, metadata !1009, metadata !525), !dbg !1010
  store i32* %fds, i32** %fds.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %fds.addr, metadata !1011, metadata !525), !dbg !1012
  call void @llvm.dbg.declare(metadata i32* %mask, metadata !1013, metadata !525), !dbg !1014
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1015, metadata !525), !dbg !1016
  store i32 7, i32* %mask, align 4, !dbg !1017
  %0 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1018
  %flags = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %0, i32 0, i32 0, !dbg !1019
  %1 = load i32, i32* %flags, align 8, !dbg !1019
  %2 = load i32, i32* %mask, align 4, !dbg !1020
  %and = and i32 %1, %2, !dbg !1021
  switch i32 %and, label %sw.default [
    i32 0, label %sw.bb
    i32 1, label %sw.bb1
    i32 2, label %sw.bb5
    i32 4, label %sw.bb5
  ], !dbg !1022

sw.bb:                                            ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1023
  br label %return, !dbg !1023

sw.bb1:                                           ; preds = %entry
  %3 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1025
  %data = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %3, i32 0, i32 1, !dbg !1025
  %stream = bitcast %union.anon.5* %data to %struct.uv_stream_s**, !dbg !1025
  %4 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1025
  %cmp = icmp ne %struct.uv_stream_s* %4, null, !dbg !1025
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1025

cond.true:                                        ; preds = %sw.bb1
  br label %cond.end, !dbg !1026

cond.false:                                       ; preds = %sw.bb1
  call void @__assert_fail(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 199, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv__process_init_stdio, i32 0, i32 0)) #9, !dbg !1028
  unreachable, !dbg !1028
                                                  ; No predecessors!
  br label %cond.end, !dbg !1030

cond.end:                                         ; preds = %5, %cond.true
  %6 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1032
  %data2 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %6, i32 0, i32 1, !dbg !1034
  %stream3 = bitcast %union.anon.5* %data2 to %struct.uv_stream_s**, !dbg !1035
  %7 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream3, align 8, !dbg !1035
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %7, i32 0, i32 2, !dbg !1036
  %8 = load i32, i32* %type, align 8, !dbg !1036
  %cmp4 = icmp ne i32 %8, 7, !dbg !1037
  br i1 %cmp4, label %if.then, label %if.else, !dbg !1038

if.then:                                          ; preds = %cond.end
  store i32 -22, i32* %retval, align 4, !dbg !1039
  br label %return, !dbg !1039

if.else:                                          ; preds = %cond.end
  %9 = load i32*, i32** %fds.addr, align 8, !dbg !1040
  %call = call i32 @uv__make_socketpair(i32* %9, i32 0), !dbg !1041
  store i32 %call, i32* %retval, align 4, !dbg !1042
  br label %return, !dbg !1042

sw.bb5:                                           ; preds = %entry, %entry
  %10 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1043
  %flags6 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %10, i32 0, i32 0, !dbg !1045
  %11 = load i32, i32* %flags6, align 8, !dbg !1045
  %and7 = and i32 %11, 2, !dbg !1046
  %tobool = icmp ne i32 %and7, 0, !dbg !1046
  br i1 %tobool, label %if.then8, label %if.else11, !dbg !1047

if.then8:                                         ; preds = %sw.bb5
  %12 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1048
  %data9 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %12, i32 0, i32 1, !dbg !1049
  %fd10 = bitcast %union.anon.5* %data9 to i32*, !dbg !1050
  %13 = load i32, i32* %fd10, align 8, !dbg !1050
  store i32 %13, i32* %fd, align 4, !dbg !1051
  br label %if.end, !dbg !1052

if.else11:                                        ; preds = %sw.bb5
  %14 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1053
  %data12 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %14, i32 0, i32 1, !dbg !1053
  %stream13 = bitcast %union.anon.5* %data12 to %struct.uv_stream_s**, !dbg !1053
  %15 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream13, align 8, !dbg !1053
  %io_watcher = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %15, i32 0, i32 13, !dbg !1053
  %fd14 = getelementptr inbounds %struct.uv__io_s, %struct.uv__io_s* %io_watcher, i32 0, i32 5, !dbg !1053
  %16 = load i32, i32* %fd14, align 8, !dbg !1053
  store i32 %16, i32* %fd, align 4, !dbg !1054
  br label %if.end

if.end:                                           ; preds = %if.else11, %if.then8
  %17 = load i32, i32* %fd, align 4, !dbg !1055
  %cmp15 = icmp eq i32 %17, -1, !dbg !1057
  br i1 %cmp15, label %if.then16, label %if.end17, !dbg !1058

if.then16:                                        ; preds = %if.end
  store i32 -22, i32* %retval, align 4, !dbg !1059
  br label %return, !dbg !1059

if.end17:                                         ; preds = %if.end
  %18 = load i32, i32* %fd, align 4, !dbg !1060
  %19 = load i32*, i32** %fds.addr, align 8, !dbg !1061
  %arrayidx = getelementptr inbounds i32, i32* %19, i64 1, !dbg !1061
  store i32 %18, i32* %arrayidx, align 4, !dbg !1062
  store i32 0, i32* %retval, align 4, !dbg !1063
  br label %return, !dbg !1063

sw.default:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 219, i8* getelementptr inbounds ([58 x i8], [58 x i8]* @__PRETTY_FUNCTION__.uv__process_init_stdio, i32 0, i32 0)) #9, !dbg !1064
  unreachable, !dbg !1064

return:                                           ; preds = %if.end17, %if.then16, %if.else, %if.then, %sw.bb
  %20 = load i32, i32* %retval, align 4, !dbg !1065
  ret i32 %20, !dbg !1065
}

declare i32 @uv_signal_start(%struct.uv_signal_s*, void (%struct.uv_signal_s*, i32)*, i32) #4

; Function Attrs: nounwind uwtable
define internal void @uv__chld(%struct.uv_signal_s* %handle, i32 %signum) #0 !dbg !504 {
entry:
  %handle.addr = alloca %struct.uv_signal_s*, align 8
  %signum.addr = alloca i32, align 4
  %process = alloca %struct.uv_process_s*, align 8
  %loop = alloca %struct.uv_loop_s*, align 8
  %exit_status = alloca i32, align 4
  %term_signal = alloca i32, align 4
  %status = alloca i32, align 4
  %pid = alloca i32, align 4
  %pending = alloca [2 x i8*], align 16
  %q = alloca [2 x i8*]*, align 8
  %h = alloca [2 x i8*]*, align 8
  %.compoundliteral = alloca %union.anon.7, align 4
  %.compoundliteral105 = alloca %union.anon.8, align 4
  %.compoundliteral111 = alloca %union.anon.9, align 4
  %.compoundliteral121 = alloca %union.anon.10, align 4
  store %struct.uv_signal_s* %handle, %struct.uv_signal_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_signal_s** %handle.addr, metadata !1066, metadata !525), !dbg !1067
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !1068, metadata !525), !dbg !1069
  call void @llvm.dbg.declare(metadata %struct.uv_process_s** %process, metadata !1070, metadata !525), !dbg !1071
  call void @llvm.dbg.declare(metadata %struct.uv_loop_s** %loop, metadata !1072, metadata !525), !dbg !1073
  call void @llvm.dbg.declare(metadata i32* %exit_status, metadata !1074, metadata !525), !dbg !1075
  call void @llvm.dbg.declare(metadata i32* %term_signal, metadata !1076, metadata !525), !dbg !1077
  call void @llvm.dbg.declare(metadata i32* %status, metadata !1078, metadata !525), !dbg !1079
  call void @llvm.dbg.declare(metadata i32* %pid, metadata !1080, metadata !525), !dbg !1081
  call void @llvm.dbg.declare(metadata [2 x i8*]* %pending, metadata !1082, metadata !525), !dbg !1083
  call void @llvm.dbg.declare(metadata [2 x i8*]** %q, metadata !1084, metadata !525), !dbg !1085
  call void @llvm.dbg.declare(metadata [2 x i8*]** %h, metadata !1086, metadata !525), !dbg !1087
  %0 = load i32, i32* %signum.addr, align 4, !dbg !1088
  %cmp = icmp eq i32 %0, 17, !dbg !1088
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1088

cond.true:                                        ; preds = %entry
  br label %cond.end, !dbg !1089

cond.false:                                       ; preds = %entry
  call void @__assert_fail(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 59, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @__PRETTY_FUNCTION__.uv__chld, i32 0, i32 0)) #9, !dbg !1091
  unreachable, !dbg !1091
                                                  ; No predecessors!
  br label %cond.end, !dbg !1093

cond.end:                                         ; preds = %1, %cond.true
  br label %do.body, !dbg !1095

do.body:                                          ; preds = %cond.end
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending, i64 0, i64 0, !dbg !1096
  %2 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1096
  store [2 x i8*]* %pending, [2 x i8*]** %2, align 16, !dbg !1096
  %arrayidx1 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending, i64 0, i64 1, !dbg !1096
  %3 = bitcast i8** %arrayidx1 to [2 x i8*]**, !dbg !1096
  store [2 x i8*]* %pending, [2 x i8*]** %3, align 8, !dbg !1096
  br label %do.end, !dbg !1096

do.end:                                           ; preds = %do.body
  %4 = load %struct.uv_signal_s*, %struct.uv_signal_s** %handle.addr, align 8, !dbg !1099
  %loop2 = getelementptr inbounds %struct.uv_signal_s, %struct.uv_signal_s* %4, i32 0, i32 1, !dbg !1100
  %5 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop2, align 8, !dbg !1100
  store %struct.uv_loop_s* %5, %struct.uv_loop_s** %loop, align 8, !dbg !1101
  %6 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1102
  %process_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %6, i32 0, i32 17, !dbg !1103
  store [2 x i8*]* %process_handles, [2 x i8*]** %h, align 8, !dbg !1104
  %7 = load [2 x i8*]*, [2 x i8*]** %h, align 8, !dbg !1105
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %7, i64 0, i64 0, !dbg !1105
  %8 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !1105
  %9 = load [2 x i8*]*, [2 x i8*]** %8, align 8, !dbg !1105
  store [2 x i8*]* %9, [2 x i8*]** %q, align 8, !dbg !1106
  br label %while.cond, !dbg !1107

while.cond:                                       ; preds = %do.end46, %if.end18, %if.then, %do.end
  %10 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1108
  %11 = load [2 x i8*]*, [2 x i8*]** %h, align 8, !dbg !1109
  %cmp4 = icmp ne [2 x i8*]* %10, %11, !dbg !1110
  br i1 %cmp4, label %while.body, label %while.end, !dbg !1111

while.body:                                       ; preds = %while.cond
  %12 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1112
  %13 = bitcast [2 x i8*]* %12 to i8*, !dbg !1112
  %add.ptr = getelementptr inbounds i8, i8* %13, i64 -112, !dbg !1112
  %14 = bitcast i8* %add.ptr to %struct.uv_process_s*, !dbg !1112
  store %struct.uv_process_s* %14, %struct.uv_process_s** %process, align 8, !dbg !1114
  %15 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1115
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %15, i64 0, i64 0, !dbg !1115
  %16 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !1115
  %17 = load [2 x i8*]*, [2 x i8*]** %16, align 8, !dbg !1115
  store [2 x i8*]* %17, [2 x i8*]** %q, align 8, !dbg !1116
  br label %do.body6, !dbg !1117

do.body6:                                         ; preds = %land.end, %while.body
  %18 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1118
  %pid7 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %18, i32 0, i32 9, !dbg !1119
  %19 = load i32, i32* %pid7, align 8, !dbg !1119
  %call = call i32 @waitpid(i32 %19, i32* %status, i32 1), !dbg !1120
  store i32 %call, i32* %pid, align 4, !dbg !1121
  br label %do.cond, !dbg !1122

do.cond:                                          ; preds = %do.body6
  %20 = load i32, i32* %pid, align 4, !dbg !1123
  %cmp8 = icmp eq i32 %20, -1, !dbg !1124
  br i1 %cmp8, label %land.rhs, label %land.end, !dbg !1125

land.rhs:                                         ; preds = %do.cond
  %call9 = call i32* @__errno_location() #1, !dbg !1126
  %21 = load i32, i32* %call9, align 4, !dbg !1126
  %cmp10 = icmp eq i32 %21, 4, !dbg !1128
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %22 = phi i1 [ false, %do.cond ], [ %cmp10, %land.rhs ]
  br i1 %22, label %do.body6, label %do.end11, !dbg !1129

do.end11:                                         ; preds = %land.end
  %23 = load i32, i32* %pid, align 4, !dbg !1130
  %cmp12 = icmp eq i32 %23, 0, !dbg !1132
  br i1 %cmp12, label %if.then, label %if.end, !dbg !1133

if.then:                                          ; preds = %do.end11
  br label %while.cond, !dbg !1134

if.end:                                           ; preds = %do.end11
  %24 = load i32, i32* %pid, align 4, !dbg !1135
  %cmp13 = icmp eq i32 %24, -1, !dbg !1137
  br i1 %cmp13, label %if.then14, label %if.end19, !dbg !1138

if.then14:                                        ; preds = %if.end
  %call15 = call i32* @__errno_location() #1, !dbg !1139
  %25 = load i32, i32* %call15, align 4, !dbg !1139
  %cmp16 = icmp ne i32 %25, 10, !dbg !1142
  br i1 %cmp16, label %if.then17, label %if.end18, !dbg !1143

if.then17:                                        ; preds = %if.then14
  call void @abort() #9, !dbg !1144
  unreachable, !dbg !1144

if.end18:                                         ; preds = %if.then14
  br label %while.cond, !dbg !1145

if.end19:                                         ; preds = %if.end
  %26 = load i32, i32* %status, align 4, !dbg !1146
  %27 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1147
  %status20 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %27, i32 0, i32 11, !dbg !1148
  store i32 %26, i32* %status20, align 8, !dbg !1149
  br label %do.body21, !dbg !1150

do.body21:                                        ; preds = %if.end19
  %28 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1151
  %queue = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %28, i32 0, i32 10, !dbg !1151
  %arrayidx22 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1151
  %29 = bitcast i8** %arrayidx22 to [2 x i8*]**, !dbg !1151
  %30 = load [2 x i8*]*, [2 x i8*]** %29, align 8, !dbg !1151
  %31 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1151
  %queue23 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %31, i32 0, i32 10, !dbg !1151
  %arrayidx24 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue23, i64 0, i64 1, !dbg !1151
  %32 = bitcast i8** %arrayidx24 to [2 x i8*]**, !dbg !1151
  %33 = load [2 x i8*]*, [2 x i8*]** %32, align 8, !dbg !1151
  %arrayidx25 = getelementptr inbounds [2 x i8*], [2 x i8*]* %33, i64 0, i64 0, !dbg !1151
  %34 = bitcast i8** %arrayidx25 to [2 x i8*]**, !dbg !1151
  store [2 x i8*]* %30, [2 x i8*]** %34, align 8, !dbg !1151
  %35 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1151
  %queue26 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %35, i32 0, i32 10, !dbg !1151
  %arrayidx27 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue26, i64 0, i64 1, !dbg !1151
  %36 = bitcast i8** %arrayidx27 to [2 x i8*]**, !dbg !1151
  %37 = load [2 x i8*]*, [2 x i8*]** %36, align 8, !dbg !1151
  %38 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1151
  %queue28 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %38, i32 0, i32 10, !dbg !1151
  %arrayidx29 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue28, i64 0, i64 0, !dbg !1151
  %39 = bitcast i8** %arrayidx29 to [2 x i8*]**, !dbg !1151
  %40 = load [2 x i8*]*, [2 x i8*]** %39, align 8, !dbg !1151
  %arrayidx30 = getelementptr inbounds [2 x i8*], [2 x i8*]* %40, i64 0, i64 1, !dbg !1151
  %41 = bitcast i8** %arrayidx30 to [2 x i8*]**, !dbg !1151
  store [2 x i8*]* %37, [2 x i8*]** %41, align 8, !dbg !1151
  br label %do.end32, !dbg !1151

do.end32:                                         ; preds = %do.body21
  br label %do.body33, !dbg !1154

do.body33:                                        ; preds = %do.end32
  %42 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1155
  %queue34 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %42, i32 0, i32 10, !dbg !1155
  %arrayidx35 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue34, i64 0, i64 0, !dbg !1155
  %43 = bitcast i8** %arrayidx35 to [2 x i8*]**, !dbg !1155
  store [2 x i8*]* %pending, [2 x i8*]** %43, align 8, !dbg !1155
  %arrayidx36 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending, i64 0, i64 1, !dbg !1155
  %44 = bitcast i8** %arrayidx36 to [2 x i8*]**, !dbg !1155
  %45 = load [2 x i8*]*, [2 x i8*]** %44, align 8, !dbg !1155
  %46 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1155
  %queue37 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %46, i32 0, i32 10, !dbg !1155
  %arrayidx38 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue37, i64 0, i64 1, !dbg !1155
  %47 = bitcast i8** %arrayidx38 to [2 x i8*]**, !dbg !1155
  store [2 x i8*]* %45, [2 x i8*]** %47, align 8, !dbg !1155
  %48 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1155
  %queue39 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %48, i32 0, i32 10, !dbg !1155
  %49 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1155
  %queue40 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %49, i32 0, i32 10, !dbg !1155
  %arrayidx41 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue40, i64 0, i64 1, !dbg !1155
  %50 = bitcast i8** %arrayidx41 to [2 x i8*]**, !dbg !1155
  %51 = load [2 x i8*]*, [2 x i8*]** %50, align 8, !dbg !1155
  %arrayidx42 = getelementptr inbounds [2 x i8*], [2 x i8*]* %51, i64 0, i64 0, !dbg !1155
  %52 = bitcast i8** %arrayidx42 to [2 x i8*]**, !dbg !1155
  store [2 x i8*]* %queue39, [2 x i8*]** %52, align 8, !dbg !1155
  %53 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1155
  %queue43 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %53, i32 0, i32 10, !dbg !1155
  %arrayidx44 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending, i64 0, i64 1, !dbg !1155
  %54 = bitcast i8** %arrayidx44 to [2 x i8*]**, !dbg !1155
  store [2 x i8*]* %queue43, [2 x i8*]** %54, align 8, !dbg !1155
  br label %do.end46, !dbg !1155

do.end46:                                         ; preds = %do.body33
  br label %while.cond, !dbg !1158

while.end:                                        ; preds = %while.cond
  store [2 x i8*]* %pending, [2 x i8*]** %h, align 8, !dbg !1159
  %55 = load [2 x i8*]*, [2 x i8*]** %h, align 8, !dbg !1160
  %arrayidx47 = getelementptr inbounds [2 x i8*], [2 x i8*]* %55, i64 0, i64 0, !dbg !1160
  %56 = bitcast i8** %arrayidx47 to [2 x i8*]**, !dbg !1160
  %57 = load [2 x i8*]*, [2 x i8*]** %56, align 8, !dbg !1160
  store [2 x i8*]* %57, [2 x i8*]** %q, align 8, !dbg !1161
  br label %while.cond48, !dbg !1162

while.cond48:                                     ; preds = %if.end126, %if.then99, %while.end
  %58 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1163
  %59 = load [2 x i8*]*, [2 x i8*]** %h, align 8, !dbg !1164
  %cmp49 = icmp ne [2 x i8*]* %58, %59, !dbg !1165
  br i1 %cmp49, label %while.body50, label %while.end129, !dbg !1166

while.body50:                                     ; preds = %while.cond48
  %60 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1167
  %61 = bitcast [2 x i8*]* %60 to i8*, !dbg !1167
  %add.ptr51 = getelementptr inbounds i8, i8* %61, i64 -112, !dbg !1167
  %62 = bitcast i8* %add.ptr51 to %struct.uv_process_s*, !dbg !1167
  store %struct.uv_process_s* %62, %struct.uv_process_s** %process, align 8, !dbg !1169
  %63 = load [2 x i8*]*, [2 x i8*]** %q, align 8, !dbg !1170
  %arrayidx52 = getelementptr inbounds [2 x i8*], [2 x i8*]* %63, i64 0, i64 0, !dbg !1170
  %64 = bitcast i8** %arrayidx52 to [2 x i8*]**, !dbg !1170
  %65 = load [2 x i8*]*, [2 x i8*]** %64, align 8, !dbg !1170
  store [2 x i8*]* %65, [2 x i8*]** %q, align 8, !dbg !1171
  br label %do.body53, !dbg !1172

do.body53:                                        ; preds = %while.body50
  %66 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1173
  %queue54 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %66, i32 0, i32 10, !dbg !1173
  %arrayidx55 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue54, i64 0, i64 0, !dbg !1173
  %67 = bitcast i8** %arrayidx55 to [2 x i8*]**, !dbg !1173
  %68 = load [2 x i8*]*, [2 x i8*]** %67, align 8, !dbg !1173
  %69 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1173
  %queue56 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %69, i32 0, i32 10, !dbg !1173
  %arrayidx57 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue56, i64 0, i64 1, !dbg !1173
  %70 = bitcast i8** %arrayidx57 to [2 x i8*]**, !dbg !1173
  %71 = load [2 x i8*]*, [2 x i8*]** %70, align 8, !dbg !1173
  %arrayidx58 = getelementptr inbounds [2 x i8*], [2 x i8*]* %71, i64 0, i64 0, !dbg !1173
  %72 = bitcast i8** %arrayidx58 to [2 x i8*]**, !dbg !1173
  store [2 x i8*]* %68, [2 x i8*]** %72, align 8, !dbg !1173
  %73 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1173
  %queue59 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %73, i32 0, i32 10, !dbg !1173
  %arrayidx60 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue59, i64 0, i64 1, !dbg !1173
  %74 = bitcast i8** %arrayidx60 to [2 x i8*]**, !dbg !1173
  %75 = load [2 x i8*]*, [2 x i8*]** %74, align 8, !dbg !1173
  %76 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1173
  %queue61 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %76, i32 0, i32 10, !dbg !1173
  %arrayidx62 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue61, i64 0, i64 0, !dbg !1173
  %77 = bitcast i8** %arrayidx62 to [2 x i8*]**, !dbg !1173
  %78 = load [2 x i8*]*, [2 x i8*]** %77, align 8, !dbg !1173
  %arrayidx63 = getelementptr inbounds [2 x i8*], [2 x i8*]* %78, i64 0, i64 1, !dbg !1173
  %79 = bitcast i8** %arrayidx63 to [2 x i8*]**, !dbg !1173
  store [2 x i8*]* %75, [2 x i8*]** %79, align 8, !dbg !1173
  br label %do.end65, !dbg !1173

do.end65:                                         ; preds = %do.body53
  br label %do.body66, !dbg !1176

do.body66:                                        ; preds = %do.end65
  %80 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1177
  %queue67 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %80, i32 0, i32 10, !dbg !1177
  %81 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1177
  %queue68 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %81, i32 0, i32 10, !dbg !1177
  %arrayidx69 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue68, i64 0, i64 0, !dbg !1177
  %82 = bitcast i8** %arrayidx69 to [2 x i8*]**, !dbg !1177
  store [2 x i8*]* %queue67, [2 x i8*]** %82, align 8, !dbg !1177
  %83 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1177
  %queue70 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %83, i32 0, i32 10, !dbg !1177
  %84 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1177
  %queue71 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %84, i32 0, i32 10, !dbg !1177
  %arrayidx72 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue71, i64 0, i64 1, !dbg !1177
  %85 = bitcast i8** %arrayidx72 to [2 x i8*]**, !dbg !1177
  store [2 x i8*]* %queue70, [2 x i8*]** %85, align 8, !dbg !1177
  br label %do.end74, !dbg !1177

do.end74:                                         ; preds = %do.body66
  br label %do.body75, !dbg !1180

do.body75:                                        ; preds = %do.end74
  %86 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1181
  %flags = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %86, i32 0, i32 7, !dbg !1181
  %87 = load i32, i32* %flags, align 8, !dbg !1181
  %and = and i32 %87, 0, !dbg !1181
  %cmp76 = icmp eq i32 %and, 0, !dbg !1181
  br i1 %cmp76, label %cond.true77, label %cond.false78, !dbg !1181

cond.true77:                                      ; preds = %do.body75
  br label %cond.end79, !dbg !1184

cond.false78:                                     ; preds = %do.body75
  call void @__assert_fail(i8* getelementptr inbounds ([45 x i8], [45 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 96, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @__PRETTY_FUNCTION__.uv__chld, i32 0, i32 0)) #9, !dbg !1186
  unreachable, !dbg !1186
                                                  ; No predecessors!
  br label %cond.end79, !dbg !1188

cond.end79:                                       ; preds = %88, %cond.true77
  %89 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1190
  %flags80 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %89, i32 0, i32 7, !dbg !1190
  %90 = load i32, i32* %flags80, align 8, !dbg !1190
  %and81 = and i32 %90, 16384, !dbg !1190
  %cmp82 = icmp eq i32 %and81, 0, !dbg !1190
  br i1 %cmp82, label %if.then83, label %if.end84, !dbg !1190

if.then83:                                        ; preds = %cond.end79
  br label %do.end97, !dbg !1193

if.end84:                                         ; preds = %cond.end79
  %91 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1195
  %flags85 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %91, i32 0, i32 7, !dbg !1195
  %92 = load i32, i32* %flags85, align 8, !dbg !1195
  %and86 = and i32 %92, -16385, !dbg !1195
  store i32 %and86, i32* %flags85, align 8, !dbg !1195
  %93 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1195
  %flags87 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %93, i32 0, i32 7, !dbg !1195
  %94 = load i32, i32* %flags87, align 8, !dbg !1195
  %and88 = and i32 %94, 8192, !dbg !1195
  %cmp89 = icmp ne i32 %and88, 0, !dbg !1195
  br i1 %cmp89, label %if.then90, label %if.end95, !dbg !1195

if.then90:                                        ; preds = %if.end84
  br label %do.body91, !dbg !1197

do.body91:                                        ; preds = %if.then90
  %95 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1200
  %loop92 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %95, i32 0, i32 1, !dbg !1200
  %96 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop92, align 8, !dbg !1200
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %96, i32 0, i32 1, !dbg !1200
  %97 = load i32, i32* %active_handles, align 8, !dbg !1200
  %dec = add i32 %97, -1, !dbg !1200
  store i32 %dec, i32* %active_handles, align 8, !dbg !1200
  br label %do.end94, !dbg !1200

do.end94:                                         ; preds = %do.body91
  br label %if.end95, !dbg !1203

if.end95:                                         ; preds = %do.end94, %if.end84
  br label %do.end97, !dbg !1205

do.end97:                                         ; preds = %if.end95, %if.then83
  %98 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1207
  %exit_cb = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %98, i32 0, i32 8, !dbg !1209
  %99 = load void (%struct.uv_process_s*, i64, i32)*, void (%struct.uv_process_s*, i64, i32)** %exit_cb, align 8, !dbg !1209
  %cmp98 = icmp eq void (%struct.uv_process_s*, i64, i32)* %99, null, !dbg !1210
  br i1 %cmp98, label %if.then99, label %if.end100, !dbg !1211

if.then99:                                        ; preds = %do.end97
  br label %while.cond48, !dbg !1212

if.end100:                                        ; preds = %do.end97
  store i32 0, i32* %exit_status, align 4, !dbg !1213
  %__in = bitcast %union.anon.7* %.compoundliteral to i32*, !dbg !1214
  %100 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1214
  %status101 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %100, i32 0, i32 11, !dbg !1214
  %101 = load i32, i32* %status101, align 8, !dbg !1214
  store i32 %101, i32* %__in, align 4, !dbg !1214
  %__i = bitcast %union.anon.7* %.compoundliteral to i32*, !dbg !1214
  %102 = load i32, i32* %__i, align 4, !dbg !1214
  %and102 = and i32 %102, 127, !dbg !1214
  %cmp103 = icmp eq i32 %and102, 0, !dbg !1214
  br i1 %cmp103, label %if.then104, label %if.end110, !dbg !1216

if.then104:                                       ; preds = %if.end100
  %__in106 = bitcast %union.anon.8* %.compoundliteral105 to i32*, !dbg !1217
  %103 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1217
  %status107 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %103, i32 0, i32 11, !dbg !1217
  %104 = load i32, i32* %status107, align 8, !dbg !1217
  store i32 %104, i32* %__in106, align 4, !dbg !1217
  %__i108 = bitcast %union.anon.8* %.compoundliteral105 to i32*, !dbg !1217
  %105 = load i32, i32* %__i108, align 4, !dbg !1217
  %and109 = and i32 %105, 65280, !dbg !1217
  %shr = ashr i32 %and109, 8, !dbg !1217
  store i32 %shr, i32* %exit_status, align 4, !dbg !1218
  br label %if.end110, !dbg !1219

if.end110:                                        ; preds = %if.then104, %if.end100
  store i32 0, i32* %term_signal, align 4, !dbg !1220
  %__in112 = bitcast %union.anon.9* %.compoundliteral111 to i32*, !dbg !1221
  %106 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1221
  %status113 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %106, i32 0, i32 11, !dbg !1221
  %107 = load i32, i32* %status113, align 8, !dbg !1221
  store i32 %107, i32* %__in112, align 4, !dbg !1221
  %__i114 = bitcast %union.anon.9* %.compoundliteral111 to i32*, !dbg !1221
  %108 = load i32, i32* %__i114, align 4, !dbg !1221
  %and115 = and i32 %108, 127, !dbg !1221
  %add = add nsw i32 %and115, 1, !dbg !1221
  %conv = trunc i32 %add to i8, !dbg !1221
  %conv116 = sext i8 %conv to i32, !dbg !1221
  %shr117 = ashr i32 %conv116, 1, !dbg !1221
  %cmp118 = icmp sgt i32 %shr117, 0, !dbg !1221
  br i1 %cmp118, label %if.then120, label %if.end126, !dbg !1223

if.then120:                                       ; preds = %if.end110
  %__in122 = bitcast %union.anon.10* %.compoundliteral121 to i32*, !dbg !1224
  %109 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1224
  %status123 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %109, i32 0, i32 11, !dbg !1224
  %110 = load i32, i32* %status123, align 8, !dbg !1224
  store i32 %110, i32* %__in122, align 4, !dbg !1224
  %__i124 = bitcast %union.anon.10* %.compoundliteral121 to i32*, !dbg !1224
  %111 = load i32, i32* %__i124, align 4, !dbg !1224
  %and125 = and i32 %111, 127, !dbg !1224
  store i32 %and125, i32* %term_signal, align 4, !dbg !1225
  br label %if.end126, !dbg !1226

if.end126:                                        ; preds = %if.then120, %if.end110
  %112 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1227
  %exit_cb127 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %112, i32 0, i32 8, !dbg !1228
  %113 = load void (%struct.uv_process_s*, i64, i32)*, void (%struct.uv_process_s*, i64, i32)** %exit_cb127, align 8, !dbg !1228
  %114 = load %struct.uv_process_s*, %struct.uv_process_s** %process, align 8, !dbg !1229
  %115 = load i32, i32* %exit_status, align 4, !dbg !1230
  %conv128 = sext i32 %115 to i64, !dbg !1230
  %116 = load i32, i32* %term_signal, align 4, !dbg !1231
  call void %113(%struct.uv_process_s* %114, i64 %conv128, i32 %116), !dbg !1227
  br label %while.cond48, !dbg !1232

while.end129:                                     ; preds = %while.cond48
  %arrayidx130 = getelementptr inbounds [2 x i8*], [2 x i8*]* %pending, i64 0, i64 0, !dbg !1233
  %117 = bitcast i8** %arrayidx130 to [2 x i8*]**, !dbg !1233
  %118 = load [2 x i8*]*, [2 x i8*]** %117, align 16, !dbg !1233
  %cmp131 = icmp eq [2 x i8*]* %pending, %118, !dbg !1233
  br i1 %cmp131, label %cond.true133, label %cond.false134, !dbg !1233

cond.true133:                                     ; preds = %while.end129
  br label %cond.end135, !dbg !1234

cond.false134:                                    ; preds = %while.end129
  call void @__assert_fail(i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 111, i8* getelementptr inbounds ([34 x i8], [34 x i8]* @__PRETTY_FUNCTION__.uv__chld, i32 0, i32 0)) #9, !dbg !1235
  unreachable, !dbg !1235
                                                  ; No predecessors!
  br label %cond.end135, !dbg !1236

cond.end135:                                      ; preds = %119, %cond.true133
  ret void, !dbg !1237
}

declare void @uv_rwlock_wrlock(%union.pthread_rwlock_t*) #4

; Function Attrs: nounwind
declare i32 @fork() #2

declare void @uv_rwlock_wrunlock(%union.pthread_rwlock_t*) #4

declare i32 @uv__close(i32) #4

; Function Attrs: nounwind uwtable
define internal void @uv__process_child_init(%struct.uv_process_options_s* %options, i32 %stdio_count, [2 x i32]* %pipes, i32 %error_fd) #0 !dbg !505 {
entry:
  %options.addr = alloca %struct.uv_process_options_s*, align 8
  %stdio_count.addr = alloca i32, align 4
  %pipes.addr = alloca [2 x i32]*, align 8
  %error_fd.addr = alloca i32, align 4
  %close_fd = alloca i32, align 4
  %use_fd = alloca i32, align 4
  %fd = alloca i32, align 4
  %_saved_errno = alloca i32, align 4
  store %struct.uv_process_options_s* %options, %struct.uv_process_options_s** %options.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_process_options_s** %options.addr, metadata !1238, metadata !525), !dbg !1239
  store i32 %stdio_count, i32* %stdio_count.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %stdio_count.addr, metadata !1240, metadata !525), !dbg !1241
  store [2 x i32]* %pipes, [2 x i32]** %pipes.addr, align 8
  call void @llvm.dbg.declare(metadata [2 x i32]** %pipes.addr, metadata !1242, metadata !525), !dbg !1243
  store i32 %error_fd, i32* %error_fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %error_fd.addr, metadata !1244, metadata !525), !dbg !1245
  call void @llvm.dbg.declare(metadata i32* %close_fd, metadata !1246, metadata !525), !dbg !1247
  call void @llvm.dbg.declare(metadata i32* %use_fd, metadata !1248, metadata !525), !dbg !1249
  call void @llvm.dbg.declare(metadata i32* %fd, metadata !1250, metadata !525), !dbg !1251
  %0 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1252
  %flags = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %0, i32 0, i32 5, !dbg !1254
  %1 = load i32, i32* %flags, align 8, !dbg !1254
  %and = and i32 %1, 8, !dbg !1255
  %tobool = icmp ne i32 %and, 0, !dbg !1255
  br i1 %tobool, label %if.then, label %if.end, !dbg !1256

if.then:                                          ; preds = %entry
  %call = call i32 @setsid() #8, !dbg !1257
  br label %if.end, !dbg !1257

if.end:                                           ; preds = %if.then, %entry
  store i32 0, i32* %fd, align 4, !dbg !1258
  br label %for.cond, !dbg !1260

for.cond:                                         ; preds = %for.inc, %if.end
  %2 = load i32, i32* %fd, align 4, !dbg !1261
  %3 = load i32, i32* %stdio_count.addr, align 4, !dbg !1264
  %cmp = icmp slt i32 %2, %3, !dbg !1265
  br i1 %cmp, label %for.body, label %for.end, !dbg !1266

for.body:                                         ; preds = %for.cond
  %4 = load i32, i32* %fd, align 4, !dbg !1267
  %idxprom = sext i32 %4 to i64, !dbg !1269
  %5 = load [2 x i32]*, [2 x i32]** %pipes.addr, align 8, !dbg !1269
  %arrayidx = getelementptr inbounds [2 x i32], [2 x i32]* %5, i64 %idxprom, !dbg !1269
  %arrayidx1 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx, i64 0, i64 1, !dbg !1269
  %6 = load i32, i32* %arrayidx1, align 4, !dbg !1269
  store i32 %6, i32* %use_fd, align 4, !dbg !1270
  %7 = load i32, i32* %use_fd, align 4, !dbg !1271
  %cmp2 = icmp slt i32 %7, 0, !dbg !1273
  br i1 %cmp2, label %if.then4, label %lor.lhs.false, !dbg !1274

lor.lhs.false:                                    ; preds = %for.body
  %8 = load i32, i32* %use_fd, align 4, !dbg !1275
  %9 = load i32, i32* %fd, align 4, !dbg !1277
  %cmp3 = icmp sge i32 %8, %9, !dbg !1278
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1279

if.then4:                                         ; preds = %lor.lhs.false, %for.body
  br label %for.inc, !dbg !1280

if.end5:                                          ; preds = %lor.lhs.false
  %10 = load i32, i32* %use_fd, align 4, !dbg !1281
  %11 = load i32, i32* %stdio_count.addr, align 4, !dbg !1282
  %call6 = call i32 (i32, i32, ...) @fcntl(i32 %10, i32 0, i32 %11), !dbg !1283
  %12 = load i32, i32* %fd, align 4, !dbg !1284
  %idxprom7 = sext i32 %12 to i64, !dbg !1285
  %13 = load [2 x i32]*, [2 x i32]** %pipes.addr, align 8, !dbg !1285
  %arrayidx8 = getelementptr inbounds [2 x i32], [2 x i32]* %13, i64 %idxprom7, !dbg !1285
  %arrayidx9 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx8, i64 0, i64 1, !dbg !1285
  store i32 %call6, i32* %arrayidx9, align 4, !dbg !1286
  %14 = load i32, i32* %fd, align 4, !dbg !1287
  %idxprom10 = sext i32 %14 to i64, !dbg !1289
  %15 = load [2 x i32]*, [2 x i32]** %pipes.addr, align 8, !dbg !1289
  %arrayidx11 = getelementptr inbounds [2 x i32], [2 x i32]* %15, i64 %idxprom10, !dbg !1289
  %arrayidx12 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx11, i64 0, i64 1, !dbg !1289
  %16 = load i32, i32* %arrayidx12, align 4, !dbg !1289
  %cmp13 = icmp eq i32 %16, -1, !dbg !1290
  br i1 %cmp13, label %if.then14, label %if.end16, !dbg !1291

if.then14:                                        ; preds = %if.end5
  %17 = load i32, i32* %error_fd.addr, align 4, !dbg !1292
  %call15 = call i32* @__errno_location() #1, !dbg !1294
  %18 = load i32, i32* %call15, align 4, !dbg !1294
  %sub = sub nsw i32 0, %18, !dbg !1295
  call void @uv__write_int(i32 %17, i32 %sub), !dbg !1296
  call void @_exit(i32 127) #10, !dbg !1298
  unreachable, !dbg !1298

if.end16:                                         ; preds = %if.end5
  br label %for.inc, !dbg !1299

for.inc:                                          ; preds = %if.end16, %if.then4
  %19 = load i32, i32* %fd, align 4, !dbg !1300
  %inc = add nsw i32 %19, 1, !dbg !1300
  store i32 %inc, i32* %fd, align 4, !dbg !1300
  br label %for.cond, !dbg !1302

for.end:                                          ; preds = %for.cond
  store i32 0, i32* %fd, align 4, !dbg !1303
  br label %for.cond17, !dbg !1305

for.cond17:                                       ; preds = %for.inc58, %for.end
  %20 = load i32, i32* %fd, align 4, !dbg !1306
  %21 = load i32, i32* %stdio_count.addr, align 4, !dbg !1309
  %cmp18 = icmp slt i32 %20, %21, !dbg !1310
  br i1 %cmp18, label %for.body19, label %for.end60, !dbg !1311

for.body19:                                       ; preds = %for.cond17
  %22 = load i32, i32* %fd, align 4, !dbg !1312
  %idxprom20 = sext i32 %22 to i64, !dbg !1314
  %23 = load [2 x i32]*, [2 x i32]** %pipes.addr, align 8, !dbg !1314
  %arrayidx21 = getelementptr inbounds [2 x i32], [2 x i32]* %23, i64 %idxprom20, !dbg !1314
  %arrayidx22 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx21, i64 0, i64 0, !dbg !1314
  %24 = load i32, i32* %arrayidx22, align 4, !dbg !1314
  store i32 %24, i32* %close_fd, align 4, !dbg !1315
  %25 = load i32, i32* %fd, align 4, !dbg !1316
  %idxprom23 = sext i32 %25 to i64, !dbg !1317
  %26 = load [2 x i32]*, [2 x i32]** %pipes.addr, align 8, !dbg !1317
  %arrayidx24 = getelementptr inbounds [2 x i32], [2 x i32]* %26, i64 %idxprom23, !dbg !1317
  %arrayidx25 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx24, i64 0, i64 1, !dbg !1317
  %27 = load i32, i32* %arrayidx25, align 4, !dbg !1317
  store i32 %27, i32* %use_fd, align 4, !dbg !1318
  %28 = load i32, i32* %use_fd, align 4, !dbg !1319
  %cmp26 = icmp slt i32 %28, 0, !dbg !1321
  br i1 %cmp26, label %if.then27, label %if.end38, !dbg !1322

if.then27:                                        ; preds = %for.body19
  %29 = load i32, i32* %fd, align 4, !dbg !1323
  %cmp28 = icmp sge i32 %29, 3, !dbg !1326
  br i1 %cmp28, label %if.then29, label %if.else, !dbg !1327

if.then29:                                        ; preds = %if.then27
  br label %for.inc58, !dbg !1328

if.else:                                          ; preds = %if.then27
  %30 = load i32, i32* %fd, align 4, !dbg !1329
  %cmp30 = icmp eq i32 %30, 0, !dbg !1331
  %cond = select i1 %cmp30, i32 0, i32 2, !dbg !1329
  %call31 = call i32 (i8*, i32, ...) @open64(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.10, i32 0, i32 0), i32 %cond), !dbg !1332
  store i32 %call31, i32* %use_fd, align 4, !dbg !1333
  %31 = load i32, i32* %use_fd, align 4, !dbg !1334
  store i32 %31, i32* %close_fd, align 4, !dbg !1335
  %32 = load i32, i32* %use_fd, align 4, !dbg !1336
  %cmp32 = icmp eq i32 %32, -1, !dbg !1338
  br i1 %cmp32, label %if.then33, label %if.end36, !dbg !1339

if.then33:                                        ; preds = %if.else
  %33 = load i32, i32* %error_fd.addr, align 4, !dbg !1340
  %call34 = call i32* @__errno_location() #1, !dbg !1342
  %34 = load i32, i32* %call34, align 4, !dbg !1342
  %sub35 = sub nsw i32 0, %34, !dbg !1343
  call void @uv__write_int(i32 %33, i32 %sub35), !dbg !1344
  call void @_exit(i32 127) #10, !dbg !1346
  unreachable, !dbg !1346

if.end36:                                         ; preds = %if.else
  br label %if.end37

if.end37:                                         ; preds = %if.end36
  br label %if.end38, !dbg !1347

if.end38:                                         ; preds = %if.end37, %for.body19
  %35 = load i32, i32* %fd, align 4, !dbg !1348
  %36 = load i32, i32* %use_fd, align 4, !dbg !1350
  %cmp39 = icmp eq i32 %35, %36, !dbg !1351
  br i1 %cmp39, label %if.then40, label %if.else42, !dbg !1352

if.then40:                                        ; preds = %if.end38
  %37 = load i32, i32* %use_fd, align 4, !dbg !1353
  %call41 = call i32 @uv__cloexec_fcntl(i32 %37, i32 0), !dbg !1354
  br label %if.end44, !dbg !1354

if.else42:                                        ; preds = %if.end38
  %38 = load i32, i32* %use_fd, align 4, !dbg !1355
  %39 = load i32, i32* %fd, align 4, !dbg !1356
  %call43 = call i32 @dup2(i32 %38, i32 %39) #8, !dbg !1357
  store i32 %call43, i32* %fd, align 4, !dbg !1358
  br label %if.end44

if.end44:                                         ; preds = %if.else42, %if.then40
  %40 = load i32, i32* %fd, align 4, !dbg !1359
  %cmp45 = icmp eq i32 %40, -1, !dbg !1361
  br i1 %cmp45, label %if.then46, label %if.end49, !dbg !1362

if.then46:                                        ; preds = %if.end44
  %41 = load i32, i32* %error_fd.addr, align 4, !dbg !1363
  %call47 = call i32* @__errno_location() #1, !dbg !1365
  %42 = load i32, i32* %call47, align 4, !dbg !1365
  %sub48 = sub nsw i32 0, %42, !dbg !1366
  call void @uv__write_int(i32 %41, i32 %sub48), !dbg !1367
  call void @_exit(i32 127) #10, !dbg !1369
  unreachable, !dbg !1369

if.end49:                                         ; preds = %if.end44
  %43 = load i32, i32* %fd, align 4, !dbg !1370
  %cmp50 = icmp sle i32 %43, 2, !dbg !1372
  br i1 %cmp50, label %if.then51, label %if.end53, !dbg !1373

if.then51:                                        ; preds = %if.end49
  %44 = load i32, i32* %fd, align 4, !dbg !1374
  %call52 = call i32 @uv__nonblock_fcntl(i32 %44, i32 0), !dbg !1375
  br label %if.end53, !dbg !1375

if.end53:                                         ; preds = %if.then51, %if.end49
  %45 = load i32, i32* %close_fd, align 4, !dbg !1376
  %46 = load i32, i32* %stdio_count.addr, align 4, !dbg !1378
  %cmp54 = icmp sge i32 %45, %46, !dbg !1379
  br i1 %cmp54, label %if.then55, label %if.end57, !dbg !1380

if.then55:                                        ; preds = %if.end53
  %47 = load i32, i32* %close_fd, align 4, !dbg !1381
  %call56 = call i32 @uv__close(i32 %47), !dbg !1382
  br label %if.end57, !dbg !1382

if.end57:                                         ; preds = %if.then55, %if.end53
  br label %for.inc58, !dbg !1383

for.inc58:                                        ; preds = %if.end57, %if.then29
  %48 = load i32, i32* %fd, align 4, !dbg !1384
  %inc59 = add nsw i32 %48, 1, !dbg !1384
  store i32 %inc59, i32* %fd, align 4, !dbg !1384
  br label %for.cond17, !dbg !1386

for.end60:                                        ; preds = %for.cond17
  store i32 0, i32* %fd, align 4, !dbg !1387
  br label %for.cond61, !dbg !1389

for.cond61:                                       ; preds = %for.inc71, %for.end60
  %49 = load i32, i32* %fd, align 4, !dbg !1390
  %50 = load i32, i32* %stdio_count.addr, align 4, !dbg !1393
  %cmp62 = icmp slt i32 %49, %50, !dbg !1394
  br i1 %cmp62, label %for.body63, label %for.end73, !dbg !1395

for.body63:                                       ; preds = %for.cond61
  %51 = load i32, i32* %fd, align 4, !dbg !1396
  %idxprom64 = sext i32 %51 to i64, !dbg !1398
  %52 = load [2 x i32]*, [2 x i32]** %pipes.addr, align 8, !dbg !1398
  %arrayidx65 = getelementptr inbounds [2 x i32], [2 x i32]* %52, i64 %idxprom64, !dbg !1398
  %arrayidx66 = getelementptr inbounds [2 x i32], [2 x i32]* %arrayidx65, i64 0, i64 1, !dbg !1398
  %53 = load i32, i32* %arrayidx66, align 4, !dbg !1398
  store i32 %53, i32* %use_fd, align 4, !dbg !1399
  %54 = load i32, i32* %use_fd, align 4, !dbg !1400
  %55 = load i32, i32* %stdio_count.addr, align 4, !dbg !1402
  %cmp67 = icmp sge i32 %54, %55, !dbg !1403
  br i1 %cmp67, label %if.then68, label %if.end70, !dbg !1404

if.then68:                                        ; preds = %for.body63
  %56 = load i32, i32* %use_fd, align 4, !dbg !1405
  %call69 = call i32 @uv__close(i32 %56), !dbg !1406
  br label %if.end70, !dbg !1406

if.end70:                                         ; preds = %if.then68, %for.body63
  br label %for.inc71, !dbg !1407

for.inc71:                                        ; preds = %if.end70
  %57 = load i32, i32* %fd, align 4, !dbg !1408
  %inc72 = add nsw i32 %57, 1, !dbg !1408
  store i32 %inc72, i32* %fd, align 4, !dbg !1408
  br label %for.cond61, !dbg !1410

for.end73:                                        ; preds = %for.cond61
  %58 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1411
  %cwd = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %58, i32 0, i32 4, !dbg !1413
  %59 = load i8*, i8** %cwd, align 8, !dbg !1413
  %cmp74 = icmp ne i8* %59, null, !dbg !1414
  br i1 %cmp74, label %land.lhs.true, label %if.end81, !dbg !1415

land.lhs.true:                                    ; preds = %for.end73
  %60 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1416
  %cwd75 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %60, i32 0, i32 4, !dbg !1418
  %61 = load i8*, i8** %cwd75, align 8, !dbg !1418
  %call76 = call i32 @chdir(i8* %61) #8, !dbg !1419
  %tobool77 = icmp ne i32 %call76, 0, !dbg !1419
  br i1 %tobool77, label %if.then78, label %if.end81, !dbg !1420

if.then78:                                        ; preds = %land.lhs.true
  %62 = load i32, i32* %error_fd.addr, align 4, !dbg !1421
  %call79 = call i32* @__errno_location() #1, !dbg !1423
  %63 = load i32, i32* %call79, align 4, !dbg !1423
  %sub80 = sub nsw i32 0, %63, !dbg !1424
  call void @uv__write_int(i32 %62, i32 %sub80), !dbg !1425
  call void @_exit(i32 127) #10, !dbg !1427
  unreachable, !dbg !1427

if.end81:                                         ; preds = %land.lhs.true, %for.end73
  %64 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1428
  %flags82 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %64, i32 0, i32 5, !dbg !1430
  %65 = load i32, i32* %flags82, align 8, !dbg !1430
  %and83 = and i32 %65, 3, !dbg !1431
  %tobool84 = icmp ne i32 %and83, 0, !dbg !1431
  br i1 %tobool84, label %if.then85, label %if.end91, !dbg !1432

if.then85:                                        ; preds = %if.end81
  br label %do.body, !dbg !1433

do.body:                                          ; preds = %if.then85
  call void @llvm.dbg.declare(metadata i32* %_saved_errno, metadata !1435, metadata !525), !dbg !1437
  %call86 = call i32* @__errno_location() #1, !dbg !1438
  %66 = load i32, i32* %call86, align 4, !dbg !1438
  store i32 %66, i32* %_saved_errno, align 4, !dbg !1438
  br label %do.body87, !dbg !1438

do.body87:                                        ; preds = %do.body
  %call88 = call i32 @setgroups(i64 0, i32* null) #8, !dbg !1440
  br label %do.end, !dbg !1440

do.end:                                           ; preds = %do.body87
  %67 = load i32, i32* %_saved_errno, align 4, !dbg !1443
  %call89 = call i32* @__errno_location() #1, !dbg !1443
  store i32 %67, i32* %call89, align 4, !dbg !1443
  br label %do.end90, !dbg !1443

do.end90:                                         ; preds = %do.end
  br label %if.end91, !dbg !1445

if.end91:                                         ; preds = %do.end90, %if.end81
  %68 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1446
  %flags92 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %68, i32 0, i32 5, !dbg !1448
  %69 = load i32, i32* %flags92, align 8, !dbg !1448
  %and93 = and i32 %69, 2, !dbg !1449
  %tobool94 = icmp ne i32 %and93, 0, !dbg !1449
  br i1 %tobool94, label %land.lhs.true95, label %if.end101, !dbg !1450

land.lhs.true95:                                  ; preds = %if.end91
  %70 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1451
  %gid = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %70, i32 0, i32 9, !dbg !1453
  %71 = load i32, i32* %gid, align 4, !dbg !1453
  %call96 = call i32 @setgid(i32 %71) #8, !dbg !1454
  %tobool97 = icmp ne i32 %call96, 0, !dbg !1454
  br i1 %tobool97, label %if.then98, label %if.end101, !dbg !1455

if.then98:                                        ; preds = %land.lhs.true95
  %72 = load i32, i32* %error_fd.addr, align 4, !dbg !1456
  %call99 = call i32* @__errno_location() #1, !dbg !1458
  %73 = load i32, i32* %call99, align 4, !dbg !1458
  %sub100 = sub nsw i32 0, %73, !dbg !1459
  call void @uv__write_int(i32 %72, i32 %sub100), !dbg !1460
  call void @_exit(i32 127) #10, !dbg !1462
  unreachable, !dbg !1462

if.end101:                                        ; preds = %land.lhs.true95, %if.end91
  %74 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1463
  %flags102 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %74, i32 0, i32 5, !dbg !1465
  %75 = load i32, i32* %flags102, align 8, !dbg !1465
  %and103 = and i32 %75, 1, !dbg !1466
  %tobool104 = icmp ne i32 %and103, 0, !dbg !1466
  br i1 %tobool104, label %land.lhs.true105, label %if.end111, !dbg !1467

land.lhs.true105:                                 ; preds = %if.end101
  %76 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1468
  %uid = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %76, i32 0, i32 8, !dbg !1470
  %77 = load i32, i32* %uid, align 8, !dbg !1470
  %call106 = call i32 @setuid(i32 %77) #8, !dbg !1471
  %tobool107 = icmp ne i32 %call106, 0, !dbg !1471
  br i1 %tobool107, label %if.then108, label %if.end111, !dbg !1472

if.then108:                                       ; preds = %land.lhs.true105
  %78 = load i32, i32* %error_fd.addr, align 4, !dbg !1473
  %call109 = call i32* @__errno_location() #1, !dbg !1475
  %79 = load i32, i32* %call109, align 4, !dbg !1475
  %sub110 = sub nsw i32 0, %79, !dbg !1476
  call void @uv__write_int(i32 %78, i32 %sub110), !dbg !1477
  call void @_exit(i32 127) #10, !dbg !1479
  unreachable, !dbg !1479

if.end111:                                        ; preds = %land.lhs.true105, %if.end101
  %80 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1480
  %env = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %80, i32 0, i32 3, !dbg !1482
  %81 = load i8**, i8*** %env, align 8, !dbg !1482
  %cmp112 = icmp ne i8** %81, null, !dbg !1483
  br i1 %cmp112, label %if.then113, label %if.end115, !dbg !1484

if.then113:                                       ; preds = %if.end111
  %82 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1485
  %env114 = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %82, i32 0, i32 3, !dbg !1487
  %83 = load i8**, i8*** %env114, align 8, !dbg !1487
  store i8** %83, i8*** @environ, align 8, !dbg !1488
  br label %if.end115, !dbg !1489

if.end115:                                        ; preds = %if.then113, %if.end111
  %84 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1490
  %file = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %84, i32 0, i32 1, !dbg !1491
  %85 = load i8*, i8** %file, align 8, !dbg !1491
  %86 = load %struct.uv_process_options_s*, %struct.uv_process_options_s** %options.addr, align 8, !dbg !1492
  %args = getelementptr inbounds %struct.uv_process_options_s, %struct.uv_process_options_s* %86, i32 0, i32 2, !dbg !1493
  %87 = load i8**, i8*** %args, align 8, !dbg !1493
  %call116 = call i32 @execvp(i8* %85, i8** %87) #8, !dbg !1494
  %88 = load i32, i32* %error_fd.addr, align 4, !dbg !1495
  %call117 = call i32* @__errno_location() #1, !dbg !1496
  %89 = load i32, i32* %call117, align 4, !dbg !1496
  %sub118 = sub nsw i32 0, %89, !dbg !1497
  call void @uv__write_int(i32 %88, i32 %sub118), !dbg !1498
  call void @_exit(i32 127) #10, !dbg !1500
  unreachable, !dbg !1500

return:                                           ; No predecessors!
  ret void, !dbg !1501
}

; Function Attrs: noreturn nounwind
declare void @abort() #6

declare i64 @read(i32, i8*, i64) #4

declare i32 @waitpid(i32, i32*, i32) #4

declare i32 @uv__close_nocheckstdio(i32) #4

; Function Attrs: nounwind uwtable
define internal i32 @uv__process_open_stream(%struct.uv_stdio_container_s* %container, i32* %pipefds, i32 %writable) #0 !dbg !512 {
entry:
  %retval = alloca i32, align 4
  %container.addr = alloca %struct.uv_stdio_container_s*, align 8
  %pipefds.addr = alloca i32*, align 8
  %writable.addr = alloca i32, align 4
  %flags = alloca i32, align 4
  %err = alloca i32, align 4
  store %struct.uv_stdio_container_s* %container, %struct.uv_stdio_container_s** %container.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stdio_container_s** %container.addr, metadata !1502, metadata !525), !dbg !1503
  store i32* %pipefds, i32** %pipefds.addr, align 8
  call void @llvm.dbg.declare(metadata i32** %pipefds.addr, metadata !1504, metadata !525), !dbg !1505
  store i32 %writable, i32* %writable.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %writable.addr, metadata !1506, metadata !525), !dbg !1507
  call void @llvm.dbg.declare(metadata i32* %flags, metadata !1508, metadata !525), !dbg !1509
  call void @llvm.dbg.declare(metadata i32* %err, metadata !1510, metadata !525), !dbg !1511
  %0 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1512
  %flags1 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %0, i32 0, i32 0, !dbg !1514
  %1 = load i32, i32* %flags1, align 8, !dbg !1514
  %and = and i32 %1, 1, !dbg !1515
  %tobool = icmp ne i32 %and, 0, !dbg !1515
  br i1 %tobool, label %lor.lhs.false, label %if.then, !dbg !1516

lor.lhs.false:                                    ; preds = %entry
  %2 = load i32*, i32** %pipefds.addr, align 8, !dbg !1517
  %arrayidx = getelementptr inbounds i32, i32* %2, i64 0, !dbg !1517
  %3 = load i32, i32* %arrayidx, align 4, !dbg !1517
  %cmp = icmp slt i32 %3, 0, !dbg !1519
  br i1 %cmp, label %if.then, label %if.end, !dbg !1520

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 0, i32* %retval, align 4, !dbg !1521
  br label %return, !dbg !1521

if.end:                                           ; preds = %lor.lhs.false
  %4 = load i32*, i32** %pipefds.addr, align 8, !dbg !1522
  %arrayidx2 = getelementptr inbounds i32, i32* %4, i64 1, !dbg !1522
  %5 = load i32, i32* %arrayidx2, align 4, !dbg !1522
  %call = call i32 @uv__close(i32 %5), !dbg !1523
  store i32 %call, i32* %err, align 4, !dbg !1524
  %6 = load i32, i32* %err, align 4, !dbg !1525
  %cmp3 = icmp ne i32 %6, 0, !dbg !1527
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !1528

if.then4:                                         ; preds = %if.end
  call void @abort() #9, !dbg !1529
  unreachable, !dbg !1529

if.end5:                                          ; preds = %if.end
  %7 = load i32*, i32** %pipefds.addr, align 8, !dbg !1530
  %arrayidx6 = getelementptr inbounds i32, i32* %7, i64 1, !dbg !1530
  store i32 -1, i32* %arrayidx6, align 4, !dbg !1531
  %8 = load i32*, i32** %pipefds.addr, align 8, !dbg !1532
  %arrayidx7 = getelementptr inbounds i32, i32* %8, i64 0, !dbg !1532
  %9 = load i32, i32* %arrayidx7, align 4, !dbg !1532
  %call8 = call i32 @uv__nonblock_ioctl(i32 %9, i32 1), !dbg !1533
  %10 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1534
  %data = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %10, i32 0, i32 1, !dbg !1536
  %stream = bitcast %union.anon.5* %data to %struct.uv_stream_s**, !dbg !1537
  %11 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1537
  %type = getelementptr inbounds %struct.uv_stream_s, %struct.uv_stream_s* %11, i32 0, i32 2, !dbg !1538
  %12 = load i32, i32* %type, align 8, !dbg !1538
  %cmp9 = icmp eq i32 %12, 7, !dbg !1539
  br i1 %cmp9, label %land.lhs.true, label %if.else, !dbg !1540

land.lhs.true:                                    ; preds = %if.end5
  %13 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1541
  %data10 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %13, i32 0, i32 1, !dbg !1542
  %stream11 = bitcast %union.anon.5* %data10 to %struct.uv_stream_s**, !dbg !1543
  %14 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream11, align 8, !dbg !1543
  %15 = bitcast %struct.uv_stream_s* %14 to %struct.uv_pipe_s*, !dbg !1544
  %ipc = getelementptr inbounds %struct.uv_pipe_s, %struct.uv_pipe_s* %15, i32 0, i32 20, !dbg !1544
  %16 = load i32, i32* %ipc, align 8, !dbg !1544
  %tobool12 = icmp ne i32 %16, 0, !dbg !1545
  br i1 %tobool12, label %if.then13, label %if.else, !dbg !1546

if.then13:                                        ; preds = %land.lhs.true
  store i32 96, i32* %flags, align 4, !dbg !1548
  br label %if.end18, !dbg !1549

if.else:                                          ; preds = %land.lhs.true, %if.end5
  %17 = load i32, i32* %writable.addr, align 4, !dbg !1550
  %tobool14 = icmp ne i32 %17, 0, !dbg !1550
  br i1 %tobool14, label %if.then15, label %if.else16, !dbg !1552

if.then15:                                        ; preds = %if.else
  store i32 64, i32* %flags, align 4, !dbg !1553
  br label %if.end17, !dbg !1554

if.else16:                                        ; preds = %if.else
  store i32 32, i32* %flags, align 4, !dbg !1555
  br label %if.end17

if.end17:                                         ; preds = %if.else16, %if.then15
  br label %if.end18

if.end18:                                         ; preds = %if.end17, %if.then13
  %18 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1556
  %data19 = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %18, i32 0, i32 1, !dbg !1557
  %stream20 = bitcast %union.anon.5* %data19 to %struct.uv_stream_s**, !dbg !1558
  %19 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream20, align 8, !dbg !1558
  %20 = load i32*, i32** %pipefds.addr, align 8, !dbg !1559
  %arrayidx21 = getelementptr inbounds i32, i32* %20, i64 0, !dbg !1559
  %21 = load i32, i32* %arrayidx21, align 4, !dbg !1559
  %22 = load i32, i32* %flags, align 4, !dbg !1560
  %call22 = call i32 @uv__stream_open(%struct.uv_stream_s* %19, i32 %21, i32 %22), !dbg !1561
  store i32 %call22, i32* %retval, align 4, !dbg !1562
  br label %return, !dbg !1562

return:                                           ; preds = %if.end18, %if.then
  %23 = load i32, i32* %retval, align 4, !dbg !1563
  ret i32 %23, !dbg !1563
}

; Function Attrs: nounwind uwtable
define internal void @uv__process_close_stream(%struct.uv_stdio_container_s* %container) #0 !dbg !515 {
entry:
  %container.addr = alloca %struct.uv_stdio_container_s*, align 8
  store %struct.uv_stdio_container_s* %container, %struct.uv_stdio_container_s** %container.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_stdio_container_s** %container.addr, metadata !1564, metadata !525), !dbg !1565
  %0 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1566
  %flags = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %0, i32 0, i32 0, !dbg !1568
  %1 = load i32, i32* %flags, align 8, !dbg !1568
  %and = and i32 %1, 1, !dbg !1569
  %tobool = icmp ne i32 %and, 0, !dbg !1569
  br i1 %tobool, label %if.end, label %if.then, !dbg !1570

if.then:                                          ; preds = %entry
  br label %return, !dbg !1571

if.end:                                           ; preds = %entry
  %2 = load %struct.uv_stdio_container_s*, %struct.uv_stdio_container_s** %container.addr, align 8, !dbg !1573
  %data = getelementptr inbounds %struct.uv_stdio_container_s, %struct.uv_stdio_container_s* %2, i32 0, i32 1, !dbg !1574
  %stream = bitcast %union.anon.5* %data to %struct.uv_stream_s**, !dbg !1575
  %3 = load %struct.uv_stream_s*, %struct.uv_stream_s** %stream, align 8, !dbg !1575
  call void @uv__stream_close(%struct.uv_stream_s* %3), !dbg !1576
  br label %return, !dbg !1577

return:                                           ; preds = %if.end, %if.then
  ret void, !dbg !1578
}

declare void @uv__free(i8*) #4

; Function Attrs: nounwind uwtable
define i32 @uv_process_kill(%struct.uv_process_s* %process, i32 %signum) #0 !dbg !492 {
entry:
  %process.addr = alloca %struct.uv_process_s*, align 8
  %signum.addr = alloca i32, align 4
  store %struct.uv_process_s* %process, %struct.uv_process_s** %process.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_process_s** %process.addr, metadata !1580, metadata !525), !dbg !1581
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !1582, metadata !525), !dbg !1583
  %0 = load %struct.uv_process_s*, %struct.uv_process_s** %process.addr, align 8, !dbg !1584
  %pid = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %0, i32 0, i32 9, !dbg !1585
  %1 = load i32, i32* %pid, align 8, !dbg !1585
  %2 = load i32, i32* %signum.addr, align 4, !dbg !1586
  %call = call i32 @uv_kill(i32 %1, i32 %2), !dbg !1587
  ret i32 %call, !dbg !1588
}

; Function Attrs: nounwind uwtable
define i32 @uv_kill(i32 %pid, i32 %signum) #0 !dbg !495 {
entry:
  %retval = alloca i32, align 4
  %pid.addr = alloca i32, align 4
  %signum.addr = alloca i32, align 4
  store i32 %pid, i32* %pid.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %pid.addr, metadata !1589, metadata !525), !dbg !1590
  store i32 %signum, i32* %signum.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %signum.addr, metadata !1591, metadata !525), !dbg !1592
  %0 = load i32, i32* %pid.addr, align 4, !dbg !1593
  %1 = load i32, i32* %signum.addr, align 4, !dbg !1595
  %call = call i32 @kill(i32 %0, i32 %1) #8, !dbg !1596
  %tobool = icmp ne i32 %call, 0, !dbg !1596
  br i1 %tobool, label %if.then, label %if.else, !dbg !1597

if.then:                                          ; preds = %entry
  %call1 = call i32* @__errno_location() #1, !dbg !1598
  %2 = load i32, i32* %call1, align 4, !dbg !1598
  %sub = sub nsw i32 0, %2, !dbg !1599
  store i32 %sub, i32* %retval, align 4, !dbg !1600
  br label %return, !dbg !1600

if.else:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !1601
  br label %return, !dbg !1601

return:                                           ; preds = %if.else, %if.then
  %3 = load i32, i32* %retval, align 4, !dbg !1602
  ret i32 %3, !dbg !1602
}

; Function Attrs: nounwind
declare i32 @kill(i32, i32) #2

; Function Attrs: nounwind uwtable
define void @uv__process_close(%struct.uv_process_s* %handle) #0 !dbg !498 {
entry:
  %handle.addr = alloca %struct.uv_process_s*, align 8
  store %struct.uv_process_s* %handle, %struct.uv_process_s** %handle.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.uv_process_s** %handle.addr, metadata !1603, metadata !525), !dbg !1604
  br label %do.body, !dbg !1605

do.body:                                          ; preds = %entry
  %0 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1606
  %queue = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %0, i32 0, i32 10, !dbg !1606
  %arrayidx = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue, i64 0, i64 0, !dbg !1606
  %1 = bitcast i8** %arrayidx to [2 x i8*]**, !dbg !1606
  %2 = load [2 x i8*]*, [2 x i8*]** %1, align 8, !dbg !1606
  %3 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1606
  %queue1 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %3, i32 0, i32 10, !dbg !1606
  %arrayidx2 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue1, i64 0, i64 1, !dbg !1606
  %4 = bitcast i8** %arrayidx2 to [2 x i8*]**, !dbg !1606
  %5 = load [2 x i8*]*, [2 x i8*]** %4, align 8, !dbg !1606
  %arrayidx3 = getelementptr inbounds [2 x i8*], [2 x i8*]* %5, i64 0, i64 0, !dbg !1606
  %6 = bitcast i8** %arrayidx3 to [2 x i8*]**, !dbg !1606
  store [2 x i8*]* %2, [2 x i8*]** %6, align 8, !dbg !1606
  %7 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1606
  %queue4 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %7, i32 0, i32 10, !dbg !1606
  %arrayidx5 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue4, i64 0, i64 1, !dbg !1606
  %8 = bitcast i8** %arrayidx5 to [2 x i8*]**, !dbg !1606
  %9 = load [2 x i8*]*, [2 x i8*]** %8, align 8, !dbg !1606
  %10 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1606
  %queue6 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %10, i32 0, i32 10, !dbg !1606
  %arrayidx7 = getelementptr inbounds [2 x i8*], [2 x i8*]* %queue6, i64 0, i64 0, !dbg !1606
  %11 = bitcast i8** %arrayidx7 to [2 x i8*]**, !dbg !1606
  %12 = load [2 x i8*]*, [2 x i8*]** %11, align 8, !dbg !1606
  %arrayidx8 = getelementptr inbounds [2 x i8*], [2 x i8*]* %12, i64 0, i64 1, !dbg !1606
  %13 = bitcast i8** %arrayidx8 to [2 x i8*]**, !dbg !1606
  store [2 x i8*]* %9, [2 x i8*]** %13, align 8, !dbg !1606
  br label %do.end, !dbg !1606

do.end:                                           ; preds = %do.body
  br label %do.body9, !dbg !1609

do.body9:                                         ; preds = %do.end
  %14 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1610
  %flags = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %14, i32 0, i32 7, !dbg !1610
  %15 = load i32, i32* %flags, align 8, !dbg !1610
  %and = and i32 %15, 0, !dbg !1610
  %cmp = icmp eq i32 %and, 0, !dbg !1610
  br i1 %cmp, label %cond.true, label %cond.false, !dbg !1610

cond.true:                                        ; preds = %do.body9
  br label %cond.end, !dbg !1613

cond.false:                                       ; preds = %do.body9
  call void @__assert_fail(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 560, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @__PRETTY_FUNCTION__.uv__process_close, i32 0, i32 0)) #9, !dbg !1615
  unreachable, !dbg !1615
                                                  ; No predecessors!
  br label %cond.end, !dbg !1617

cond.end:                                         ; preds = %16, %cond.true
  %17 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1619
  %flags10 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %17, i32 0, i32 7, !dbg !1619
  %18 = load i32, i32* %flags10, align 8, !dbg !1619
  %and11 = and i32 %18, 16384, !dbg !1619
  %cmp12 = icmp eq i32 %and11, 0, !dbg !1619
  br i1 %cmp12, label %if.then, label %if.end, !dbg !1619

if.then:                                          ; preds = %cond.end
  br label %do.end22, !dbg !1622

if.end:                                           ; preds = %cond.end
  %19 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1624
  %flags13 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %19, i32 0, i32 7, !dbg !1624
  %20 = load i32, i32* %flags13, align 8, !dbg !1624
  %and14 = and i32 %20, -16385, !dbg !1624
  store i32 %and14, i32* %flags13, align 8, !dbg !1624
  %21 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1624
  %flags15 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %21, i32 0, i32 7, !dbg !1624
  %22 = load i32, i32* %flags15, align 8, !dbg !1624
  %and16 = and i32 %22, 8192, !dbg !1624
  %cmp17 = icmp ne i32 %and16, 0, !dbg !1624
  br i1 %cmp17, label %if.then18, label %if.end21, !dbg !1624

if.then18:                                        ; preds = %if.end
  br label %do.body19, !dbg !1626

do.body19:                                        ; preds = %if.then18
  %23 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1629
  %loop = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %23, i32 0, i32 1, !dbg !1629
  %24 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop, align 8, !dbg !1629
  %active_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %24, i32 0, i32 1, !dbg !1629
  %25 = load i32, i32* %active_handles, align 8, !dbg !1629
  %dec = add i32 %25, -1, !dbg !1629
  store i32 %dec, i32* %active_handles, align 8, !dbg !1629
  br label %do.end20, !dbg !1629

do.end20:                                         ; preds = %do.body19
  br label %if.end21, !dbg !1632

if.end21:                                         ; preds = %do.end20, %if.end
  br label %do.end22, !dbg !1634

do.end22:                                         ; preds = %if.end21, %if.then
  %26 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1636
  %loop23 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %26, i32 0, i32 1, !dbg !1636
  %27 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop23, align 8, !dbg !1636
  %process_handles = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %27, i32 0, i32 17, !dbg !1636
  %28 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1636
  %loop24 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %28, i32 0, i32 1, !dbg !1636
  %29 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop24, align 8, !dbg !1636
  %process_handles25 = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %29, i32 0, i32 17, !dbg !1636
  %arrayidx26 = getelementptr inbounds [2 x i8*], [2 x i8*]* %process_handles25, i64 0, i64 0, !dbg !1636
  %30 = bitcast i8** %arrayidx26 to [2 x i8*]**, !dbg !1636
  %31 = load [2 x i8*]*, [2 x i8*]** %30, align 8, !dbg !1636
  %cmp27 = icmp eq [2 x i8*]* %process_handles, %31, !dbg !1636
  br i1 %cmp27, label %if.then28, label %if.end30, !dbg !1638

if.then28:                                        ; preds = %do.end22
  %32 = load %struct.uv_process_s*, %struct.uv_process_s** %handle.addr, align 8, !dbg !1639
  %loop29 = getelementptr inbounds %struct.uv_process_s, %struct.uv_process_s* %32, i32 0, i32 1, !dbg !1640
  %33 = load %struct.uv_loop_s*, %struct.uv_loop_s** %loop29, align 8, !dbg !1640
  %child_watcher = getelementptr inbounds %struct.uv_loop_s, %struct.uv_loop_s* %33, i32 0, i32 30, !dbg !1641
  %call = call i32 @uv_signal_stop(%struct.uv_signal_s* %child_watcher), !dbg !1642
  br label %if.end30, !dbg !1642

if.end30:                                         ; preds = %if.then28, %do.end22
  ret void, !dbg !1643
}

declare i32 @uv_signal_stop(%struct.uv_signal_s*) #4

; Function Attrs: nounwind
declare i32 @setsid() #2

declare i32 @fcntl(i32, i32, ...) #4

; Function Attrs: nounwind uwtable
define internal void @uv__write_int(i32 %fd, i32 %val) #0 !dbg !509 {
entry:
  %fd.addr = alloca i32, align 4
  %val.addr = alloca i32, align 4
  %n = alloca i64, align 8
  store i32 %fd, i32* %fd.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %fd.addr, metadata !1644, metadata !525), !dbg !1645
  store i32 %val, i32* %val.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %val.addr, metadata !1646, metadata !525), !dbg !1647
  call void @llvm.dbg.declare(metadata i64* %n, metadata !1648, metadata !525), !dbg !1649
  br label %do.body, !dbg !1650

do.body:                                          ; preds = %land.end, %entry
  %0 = load i32, i32* %fd.addr, align 4, !dbg !1651
  %1 = bitcast i32* %val.addr to i8*, !dbg !1652
  %call = call i64 @write(i32 %0, i8* %1, i64 4), !dbg !1653
  store i64 %call, i64* %n, align 8, !dbg !1654
  br label %do.cond, !dbg !1655

do.cond:                                          ; preds = %do.body
  %2 = load i64, i64* %n, align 8, !dbg !1656
  %cmp = icmp eq i64 %2, -1, !dbg !1657
  br i1 %cmp, label %land.rhs, label %land.end, !dbg !1658

land.rhs:                                         ; preds = %do.cond
  %call1 = call i32* @__errno_location() #1, !dbg !1659
  %3 = load i32, i32* %call1, align 4, !dbg !1659
  %cmp2 = icmp eq i32 %3, 4, !dbg !1661
  br label %land.end

land.end:                                         ; preds = %land.rhs, %do.cond
  %4 = phi i1 [ false, %do.cond ], [ %cmp2, %land.rhs ]
  br i1 %4, label %do.body, label %do.end, !dbg !1662

do.end:                                           ; preds = %land.end
  %5 = load i64, i64* %n, align 8, !dbg !1663
  %cmp3 = icmp eq i64 %5, -1, !dbg !1665
  br i1 %cmp3, label %land.lhs.true, label %if.end, !dbg !1666

land.lhs.true:                                    ; preds = %do.end
  %call4 = call i32* @__errno_location() #1, !dbg !1667
  %6 = load i32, i32* %call4, align 4, !dbg !1667
  %cmp5 = icmp eq i32 %6, 32, !dbg !1669
  br i1 %cmp5, label %if.then, label %if.end, !dbg !1670

if.then:                                          ; preds = %land.lhs.true
  br label %cond.end, !dbg !1671

if.end:                                           ; preds = %land.lhs.true, %do.end
  %7 = load i64, i64* %n, align 8, !dbg !1672
  %cmp6 = icmp eq i64 %7, 4, !dbg !1672
  br i1 %cmp6, label %cond.true, label %cond.false, !dbg !1672

cond.true:                                        ; preds = %if.end
  br label %cond.end, !dbg !1673

cond.false:                                       ; preds = %if.end
  call void @__assert_fail(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([71 x i8], [71 x i8]* @.str.1, i32 0, i32 0), i32 269, i8* getelementptr inbounds ([29 x i8], [29 x i8]* @__PRETTY_FUNCTION__.uv__write_int, i32 0, i32 0)) #9, !dbg !1674
  unreachable, !dbg !1674
                                                  ; No predecessors!
  br label %cond.end, !dbg !1676

cond.end:                                         ; preds = %if.then, %8, %cond.true
  ret void, !dbg !1678
}

; Function Attrs: noreturn
declare void @_exit(i32) #7

declare i32 @open64(i8*, i32, ...) #4

declare i32 @uv__cloexec_fcntl(i32, i32) #4

; Function Attrs: nounwind
declare i32 @dup2(i32, i32) #2

declare i32 @uv__nonblock_fcntl(i32, i32) #4

; Function Attrs: nounwind
declare i32 @chdir(i8*) #2

; Function Attrs: nounwind
declare i32 @setgroups(i64, i32*) #2

; Function Attrs: nounwind
declare i32 @setgid(i32) #2

; Function Attrs: nounwind
declare i32 @setuid(i32) #2

; Function Attrs: nounwind
declare i32 @execvp(i8*, i8**) #2

declare i64 @write(i32, i8*, i64) #4

declare i32 @uv__stream_open(%struct.uv_stream_s*, i32, i32) #4

declare void @uv__stream_close(%struct.uv_stream_s*) #4

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readnone "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { noreturn nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { noreturn "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind }
attributes #9 = { noreturn nounwind }
attributes #10 = { noreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!521, !522}
!llvm.ident = !{!523}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !92, subprograms: !448, globals: !518)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/process.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!2 = !{!3, !15, !37, !45, !58, !65, !73}
!3 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "__socket_type", file: !4, line: 24, size: 32, align: 32, elements: !5)
!4 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/socket_type.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!5 = !{!6, !7, !8, !9, !10, !11, !12, !13, !14}
!6 = !DIEnumerator(name: "SOCK_STREAM", value: 1)
!7 = !DIEnumerator(name: "SOCK_DGRAM", value: 2)
!8 = !DIEnumerator(name: "SOCK_RAW", value: 3)
!9 = !DIEnumerator(name: "SOCK_RDM", value: 4)
!10 = !DIEnumerator(name: "SOCK_SEQPACKET", value: 5)
!11 = !DIEnumerator(name: "SOCK_DCCP", value: 6)
!12 = !DIEnumerator(name: "SOCK_PACKET", value: 10)
!13 = !DIEnumerator(name: "SOCK_CLOEXEC", value: 524288)
!14 = !DIEnumerator(name: "SOCK_NONBLOCK", value: 2048)
!15 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !16, line: 184, size: 32, align: 32, elements: !17)
!16 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!17 = !{!18, !19, !20, !21, !22, !23, !24, !25, !26, !27, !28, !29, !30, !31, !32, !33, !34, !35, !36}
!18 = !DIEnumerator(name: "UV_UNKNOWN_HANDLE", value: 0)
!19 = !DIEnumerator(name: "UV_ASYNC", value: 1)
!20 = !DIEnumerator(name: "UV_CHECK", value: 2)
!21 = !DIEnumerator(name: "UV_FS_EVENT", value: 3)
!22 = !DIEnumerator(name: "UV_FS_POLL", value: 4)
!23 = !DIEnumerator(name: "UV_HANDLE", value: 5)
!24 = !DIEnumerator(name: "UV_IDLE", value: 6)
!25 = !DIEnumerator(name: "UV_NAMED_PIPE", value: 7)
!26 = !DIEnumerator(name: "UV_POLL", value: 8)
!27 = !DIEnumerator(name: "UV_PREPARE", value: 9)
!28 = !DIEnumerator(name: "UV_PROCESS", value: 10)
!29 = !DIEnumerator(name: "UV_STREAM", value: 11)
!30 = !DIEnumerator(name: "UV_TCP", value: 12)
!31 = !DIEnumerator(name: "UV_TIMER", value: 13)
!32 = !DIEnumerator(name: "UV_TTY", value: 14)
!33 = !DIEnumerator(name: "UV_UDP", value: 15)
!34 = !DIEnumerator(name: "UV_SIGNAL", value: 16)
!35 = !DIEnumerator(name: "UV_FILE", value: 17)
!36 = !DIEnumerator(name: "UV_HANDLE_TYPE_MAX", value: 18)
!37 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !16, line: 843, size: 32, align: 32, elements: !38)
!38 = !{!39, !40, !41, !42, !43, !44}
!39 = !DIEnumerator(name: "UV_IGNORE", value: 0)
!40 = !DIEnumerator(name: "UV_CREATE_PIPE", value: 1)
!41 = !DIEnumerator(name: "UV_INHERIT_FD", value: 2)
!42 = !DIEnumerator(name: "UV_INHERIT_STREAM", value: 4)
!43 = !DIEnumerator(name: "UV_READABLE_PIPE", value: 16)
!44 = !DIEnumerator(name: "UV_WRITABLE_PIPE", value: 32)
!45 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !16, line: 193, size: 32, align: 32, elements: !46)
!46 = !{!47, !48, !49, !50, !51, !52, !53, !54, !55, !56, !57}
!47 = !DIEnumerator(name: "UV_UNKNOWN_REQ", value: 0)
!48 = !DIEnumerator(name: "UV_REQ", value: 1)
!49 = !DIEnumerator(name: "UV_CONNECT", value: 2)
!50 = !DIEnumerator(name: "UV_WRITE", value: 3)
!51 = !DIEnumerator(name: "UV_SHUTDOWN", value: 4)
!52 = !DIEnumerator(name: "UV_UDP_SEND", value: 5)
!53 = !DIEnumerator(name: "UV_FS", value: 6)
!54 = !DIEnumerator(name: "UV_WORK", value: 7)
!55 = !DIEnumerator(name: "UV_GETADDRINFO", value: 8)
!56 = !DIEnumerator(name: "UV_GETNAMEINFO", value: 9)
!57 = !DIEnumerator(name: "UV_REQ_TYPE_MAX", value: 10)
!58 = !DICompositeType(tag: DW_TAG_enumeration_type, name: "uv_process_flags", file: !16, line: 915, size: 32, align: 32, elements: !59)
!59 = !{!60, !61, !62, !63, !64}
!60 = !DIEnumerator(name: "UV_PROCESS_SETUID", value: 1)
!61 = !DIEnumerator(name: "UV_PROCESS_SETGID", value: 2)
!62 = !DIEnumerator(name: "UV_PROCESS_WINDOWS_VERBATIM_ARGUMENTS", value: 4)
!63 = !DIEnumerator(name: "UV_PROCESS_DETACHED", value: 8)
!64 = !DIEnumerator(name: "UV_PROCESS_WINDOWS_HIDE", value: 16)
!65 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !66, line: 57, size: 32, align: 32, elements: !67)
!66 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/uv-common.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!67 = !{!68, !69, !70, !71, !72}
!68 = !DIEnumerator(name: "UV__SIGNAL_ONE_SHOT", value: 524288)
!69 = !DIEnumerator(name: "UV__HANDLE_INTERNAL", value: 32768)
!70 = !DIEnumerator(name: "UV__HANDLE_ACTIVE", value: 16384)
!71 = !DIEnumerator(name: "UV__HANDLE_REF", value: 8192)
!72 = !DIEnumerator(name: "UV__HANDLE_CLOSING", value: 0)
!73 = !DICompositeType(tag: DW_TAG_enumeration_type, file: !74, line: 124, size: 32, align: 32, elements: !75)
!74 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/unix/internal.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!75 = !{!76, !77, !78, !79, !80, !81, !82, !83, !84, !85, !86, !87, !88, !89, !90, !91}
!76 = !DIEnumerator(name: "UV_CLOSING", value: 1)
!77 = !DIEnumerator(name: "UV_CLOSED", value: 2)
!78 = !DIEnumerator(name: "UV_STREAM_READING", value: 4)
!79 = !DIEnumerator(name: "UV_STREAM_SHUTTING", value: 8)
!80 = !DIEnumerator(name: "UV_STREAM_SHUT", value: 16)
!81 = !DIEnumerator(name: "UV_STREAM_READABLE", value: 32)
!82 = !DIEnumerator(name: "UV_STREAM_WRITABLE", value: 64)
!83 = !DIEnumerator(name: "UV_STREAM_BLOCKING", value: 128)
!84 = !DIEnumerator(name: "UV_STREAM_READ_PARTIAL", value: 256)
!85 = !DIEnumerator(name: "UV_STREAM_READ_EOF", value: 512)
!86 = !DIEnumerator(name: "UV_TCP_NODELAY", value: 1024)
!87 = !DIEnumerator(name: "UV_TCP_KEEPALIVE", value: 2048)
!88 = !DIEnumerator(name: "UV_TCP_SINGLE_ACCEPT", value: 4096)
!89 = !DIEnumerator(name: "UV_HANDLE_IPV6", value: 65536)
!90 = !DIEnumerator(name: "UV_UDP_PROCESSING", value: 131072)
!91 = !DIEnumerator(name: "UV_HANDLE_BOUND", value: 262144)
!92 = !{!93, !94, !299, !303, !305, !330, !331, !332, !367}
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_t", file: !16, line: 205, baseType: !96)
!96 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_handle_s", file: !16, line: 425, size: 768, align: 64, elements: !97)
!97 = !{!98, !99, !289, !290, !291, !292, !297, !298}
!98 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !96, file: !16, line: 426, baseType: !93, size: 64, align: 64)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !96, file: !16, line: 426, baseType: !100, size: 64, align: 64, offset: 64)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_loop_t", file: !16, line: 204, baseType: !102)
!102 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_loop_s", file: !16, line: 1473, size: 6784, align: 64, elements: !103)
!103 = !{!104, !105, !107, !111, !112, !113, !115, !117, !118, !119, !138, !139, !140, !141, !172, !204, !228, !229, !230, !231, !232, !233, !234, !238, !239, !240, !245, !248, !249, !251, !252, !285, !286, !287, !288}
!104 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !102, file: !16, line: 1475, baseType: !93, size: 64, align: 64)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "active_handles", scope: !102, file: !16, line: 1477, baseType: !106, size: 32, align: 32, offset: 64)
!106 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !102, file: !16, line: 1478, baseType: !108, size: 128, align: 64, offset: 128)
!108 = !DICompositeType(tag: DW_TAG_array_type, baseType: !93, size: 128, align: 64, elements: !109)
!109 = !{!110}
!110 = !DISubrange(count: 2)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "active_reqs", scope: !102, file: !16, line: 1479, baseType: !108, size: 128, align: 64, offset: 256)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "stop_flag", scope: !102, file: !16, line: 1481, baseType: !106, size: 32, align: 32, offset: 384)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !102, file: !16, line: 1482, baseType: !114, size: 64, align: 64, offset: 448)
!114 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "backend_fd", scope: !102, file: !16, line: 1482, baseType: !116, size: 32, align: 32, offset: 512)
!116 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!117 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !102, file: !16, line: 1482, baseType: !108, size: 128, align: 64, offset: 576)
!118 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !102, file: !16, line: 1482, baseType: !108, size: 128, align: 64, offset: 704)
!119 = !DIDerivedType(tag: DW_TAG_member, name: "watchers", scope: !102, file: !16, line: 1482, baseType: !120, size: 64, align: 64, offset: 832)
!120 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !121, size: 64, align: 64)
!121 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !122, size: 64, align: 64)
!122 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_t", file: !123, line: 87, baseType: !124)
!123 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/include/uv-unix.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!124 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv__io_s", file: !123, line: 89, size: 448, align: 64, elements: !125)
!125 = !{!126, !133, !134, !135, !136, !137}
!126 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !124, file: !123, line: 90, baseType: !127, size: 64, align: 64)
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv__io_cb", file: !123, line: 84, baseType: !128)
!128 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !129, size: 64, align: 64)
!129 = !DISubroutineType(types: !130)
!130 = !{null, !131, !132, !106}
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !102, size: 64, align: 64)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !124, size: 64, align: 64)
!133 = !DIDerivedType(tag: DW_TAG_member, name: "pending_queue", scope: !124, file: !123, line: 91, baseType: !108, size: 128, align: 64, offset: 64)
!134 = !DIDerivedType(tag: DW_TAG_member, name: "watcher_queue", scope: !124, file: !123, line: 92, baseType: !108, size: 128, align: 64, offset: 192)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "pevents", scope: !124, file: !123, line: 93, baseType: !106, size: 32, align: 32, offset: 320)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "events", scope: !124, file: !123, line: 94, baseType: !106, size: 32, align: 32, offset: 352)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !124, file: !123, line: 95, baseType: !116, size: 32, align: 32, offset: 384)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "nwatchers", scope: !102, file: !16, line: 1482, baseType: !106, size: 32, align: 32, offset: 896)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "nfds", scope: !102, file: !16, line: 1482, baseType: !106, size: 32, align: 32, offset: 928)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "wq", scope: !102, file: !16, line: 1482, baseType: !108, size: 128, align: 64, offset: 960)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "wq_mutex", scope: !102, file: !16, line: 1482, baseType: !142, size: 320, align: 64, offset: 1088)
!142 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_mutex_t", file: !123, line: 129, baseType: !143)
!143 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_mutex_t", file: !144, line: 127, baseType: !145)
!144 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/pthreadtypes.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!145 = !DICompositeType(tag: DW_TAG_union_type, file: !144, line: 90, size: 320, align: 64, elements: !146)
!146 = !{!147, !165, !170}
!147 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !145, file: !144, line: 124, baseType: !148, size: 320, align: 64)
!148 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_mutex_s", file: !144, line: 92, size: 320, align: 64, elements: !149)
!149 = !{!150, !151, !152, !153, !154, !155, !157, !158}
!150 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !148, file: !144, line: 94, baseType: !116, size: 32, align: 32)
!151 = !DIDerivedType(tag: DW_TAG_member, name: "__count", scope: !148, file: !144, line: 95, baseType: !106, size: 32, align: 32, offset: 32)
!152 = !DIDerivedType(tag: DW_TAG_member, name: "__owner", scope: !148, file: !144, line: 96, baseType: !116, size: 32, align: 32, offset: 64)
!153 = !DIDerivedType(tag: DW_TAG_member, name: "__nusers", scope: !148, file: !144, line: 98, baseType: !106, size: 32, align: 32, offset: 96)
!154 = !DIDerivedType(tag: DW_TAG_member, name: "__kind", scope: !148, file: !144, line: 102, baseType: !116, size: 32, align: 32, offset: 128)
!155 = !DIDerivedType(tag: DW_TAG_member, name: "__spins", scope: !148, file: !144, line: 104, baseType: !156, size: 16, align: 16, offset: 160)
!156 = !DIBasicType(name: "short", size: 16, align: 16, encoding: DW_ATE_signed)
!157 = !DIDerivedType(tag: DW_TAG_member, name: "__elision", scope: !148, file: !144, line: 105, baseType: !156, size: 16, align: 16, offset: 176)
!158 = !DIDerivedType(tag: DW_TAG_member, name: "__list", scope: !148, file: !144, line: 106, baseType: !159, size: 128, align: 64, offset: 192)
!159 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pthread_list_t", file: !144, line: 79, baseType: !160)
!160 = !DICompositeType(tag: DW_TAG_structure_type, name: "__pthread_internal_list", file: !144, line: 75, size: 128, align: 64, elements: !161)
!161 = !{!162, !164}
!162 = !DIDerivedType(tag: DW_TAG_member, name: "__prev", scope: !160, file: !144, line: 77, baseType: !163, size: 64, align: 64)
!163 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !160, size: 64, align: 64)
!164 = !DIDerivedType(tag: DW_TAG_member, name: "__next", scope: !160, file: !144, line: 78, baseType: !163, size: 64, align: 64, offset: 64)
!165 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !145, file: !144, line: 125, baseType: !166, size: 320, align: 8)
!166 = !DICompositeType(tag: DW_TAG_array_type, baseType: !167, size: 320, align: 8, elements: !168)
!167 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!168 = !{!169}
!169 = !DISubrange(count: 40)
!170 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !145, file: !144, line: 126, baseType: !171, size: 64, align: 64)
!171 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!172 = !DIDerivedType(tag: DW_TAG_member, name: "wq_async", scope: !102, file: !16, line: 1482, baseType: !173, size: 1024, align: 64, offset: 1408)
!173 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_t", file: !16, line: 216, baseType: !174)
!174 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_async_s", file: !16, line: 767, size: 1024, align: 64, elements: !175)
!175 = !{!176, !177, !178, !180, !185, !186, !194, !195, !196, !202, !203}
!176 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !174, file: !16, line: 768, baseType: !93, size: 64, align: 64)
!177 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !174, file: !16, line: 768, baseType: !100, size: 64, align: 64, offset: 64)
!178 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !174, file: !16, line: 768, baseType: !179, size: 32, align: 32, offset: 128)
!179 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_handle_type", file: !16, line: 191, baseType: !15)
!180 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !174, file: !16, line: 768, baseType: !181, size: 64, align: 64, offset: 192)
!181 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_close_cb", file: !16, line: 306, baseType: !182)
!182 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !183, size: 64, align: 64)
!183 = !DISubroutineType(types: !184)
!184 = !{null, !94}
!185 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !174, file: !16, line: 768, baseType: !108, size: 128, align: 64, offset: 256)
!186 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !174, file: !16, line: 768, baseType: !187, size: 256, align: 64, offset: 384)
!187 = !DICompositeType(tag: DW_TAG_union_type, scope: !174, file: !16, line: 768, size: 256, align: 64, elements: !188)
!188 = !{!189, !190}
!189 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !187, file: !16, line: 768, baseType: !116, size: 32, align: 32)
!190 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !187, file: !16, line: 768, baseType: !191, size: 256, align: 64)
!191 = !DICompositeType(tag: DW_TAG_array_type, baseType: !93, size: 256, align: 64, elements: !192)
!192 = !{!193}
!193 = !DISubrange(count: 4)
!194 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !174, file: !16, line: 768, baseType: !94, size: 64, align: 64, offset: 640)
!195 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !174, file: !16, line: 768, baseType: !106, size: 32, align: 32, offset: 704)
!196 = !DIDerivedType(tag: DW_TAG_member, name: "async_cb", scope: !174, file: !16, line: 769, baseType: !197, size: 64, align: 64, offset: 768)
!197 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_async_cb", file: !16, line: 309, baseType: !198)
!198 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !199, size: 64, align: 64)
!199 = !DISubroutineType(types: !200)
!200 = !{null, !201}
!201 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !173, size: 64, align: 64)
!202 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !174, file: !16, line: 769, baseType: !108, size: 128, align: 64, offset: 832)
!203 = !DIDerivedType(tag: DW_TAG_member, name: "pending", scope: !174, file: !16, line: 769, baseType: !116, size: 32, align: 32, offset: 960)
!204 = !DIDerivedType(tag: DW_TAG_member, name: "cloexec_lock", scope: !102, file: !16, line: 1482, baseType: !205, size: 448, align: 64, offset: 2432)
!205 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_rwlock_t", file: !123, line: 130, baseType: !206)
!206 = !DIDerivedType(tag: DW_TAG_typedef, name: "pthread_rwlock_t", file: !144, line: 213, baseType: !207)
!207 = !DICompositeType(tag: DW_TAG_union_type, file: !144, line: 173, size: 448, align: 64, elements: !208)
!208 = !{!209, !223, !227}
!209 = !DIDerivedType(tag: DW_TAG_member, name: "__data", scope: !207, file: !144, line: 192, baseType: !210, size: 448, align: 64)
!210 = !DICompositeType(tag: DW_TAG_structure_type, scope: !207, file: !144, line: 176, size: 448, align: 64, elements: !211)
!211 = !{!212, !213, !214, !215, !216, !217, !218, !219, !220, !221, !222}
!212 = !DIDerivedType(tag: DW_TAG_member, name: "__lock", scope: !210, file: !144, line: 178, baseType: !116, size: 32, align: 32)
!213 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers", scope: !210, file: !144, line: 179, baseType: !106, size: 32, align: 32, offset: 32)
!214 = !DIDerivedType(tag: DW_TAG_member, name: "__readers_wakeup", scope: !210, file: !144, line: 180, baseType: !106, size: 32, align: 32, offset: 64)
!215 = !DIDerivedType(tag: DW_TAG_member, name: "__writer_wakeup", scope: !210, file: !144, line: 181, baseType: !106, size: 32, align: 32, offset: 96)
!216 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_readers_queued", scope: !210, file: !144, line: 182, baseType: !106, size: 32, align: 32, offset: 128)
!217 = !DIDerivedType(tag: DW_TAG_member, name: "__nr_writers_queued", scope: !210, file: !144, line: 183, baseType: !106, size: 32, align: 32, offset: 160)
!218 = !DIDerivedType(tag: DW_TAG_member, name: "__writer", scope: !210, file: !144, line: 184, baseType: !116, size: 32, align: 32, offset: 192)
!219 = !DIDerivedType(tag: DW_TAG_member, name: "__shared", scope: !210, file: !144, line: 185, baseType: !116, size: 32, align: 32, offset: 224)
!220 = !DIDerivedType(tag: DW_TAG_member, name: "__pad1", scope: !210, file: !144, line: 186, baseType: !114, size: 64, align: 64, offset: 256)
!221 = !DIDerivedType(tag: DW_TAG_member, name: "__pad2", scope: !210, file: !144, line: 187, baseType: !114, size: 64, align: 64, offset: 320)
!222 = !DIDerivedType(tag: DW_TAG_member, name: "__flags", scope: !210, file: !144, line: 190, baseType: !106, size: 32, align: 32, offset: 384)
!223 = !DIDerivedType(tag: DW_TAG_member, name: "__size", scope: !207, file: !144, line: 211, baseType: !224, size: 448, align: 8)
!224 = !DICompositeType(tag: DW_TAG_array_type, baseType: !167, size: 448, align: 8, elements: !225)
!225 = !{!226}
!226 = !DISubrange(count: 56)
!227 = !DIDerivedType(tag: DW_TAG_member, name: "__align", scope: !207, file: !144, line: 212, baseType: !171, size: 64, align: 64)
!228 = !DIDerivedType(tag: DW_TAG_member, name: "closing_handles", scope: !102, file: !16, line: 1482, baseType: !94, size: 64, align: 64, offset: 2880)
!229 = !DIDerivedType(tag: DW_TAG_member, name: "process_handles", scope: !102, file: !16, line: 1482, baseType: !108, size: 128, align: 64, offset: 2944)
!230 = !DIDerivedType(tag: DW_TAG_member, name: "prepare_handles", scope: !102, file: !16, line: 1482, baseType: !108, size: 128, align: 64, offset: 3072)
!231 = !DIDerivedType(tag: DW_TAG_member, name: "check_handles", scope: !102, file: !16, line: 1482, baseType: !108, size: 128, align: 64, offset: 3200)
!232 = !DIDerivedType(tag: DW_TAG_member, name: "idle_handles", scope: !102, file: !16, line: 1482, baseType: !108, size: 128, align: 64, offset: 3328)
!233 = !DIDerivedType(tag: DW_TAG_member, name: "async_handles", scope: !102, file: !16, line: 1482, baseType: !108, size: 128, align: 64, offset: 3456)
!234 = !DIDerivedType(tag: DW_TAG_member, name: "async_unused", scope: !102, file: !16, line: 1482, baseType: !235, size: 64, align: 64, offset: 3584)
!235 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !236, size: 64, align: 64)
!236 = !DISubroutineType(types: !237)
!237 = !{null}
!238 = !DIDerivedType(tag: DW_TAG_member, name: "async_io_watcher", scope: !102, file: !16, line: 1482, baseType: !122, size: 448, align: 64, offset: 3648)
!239 = !DIDerivedType(tag: DW_TAG_member, name: "async_wfd", scope: !102, file: !16, line: 1482, baseType: !116, size: 32, align: 32, offset: 4096)
!240 = !DIDerivedType(tag: DW_TAG_member, name: "timer_heap", scope: !102, file: !16, line: 1482, baseType: !241, size: 128, align: 64, offset: 4160)
!241 = !DICompositeType(tag: DW_TAG_structure_type, scope: !102, file: !16, line: 1482, size: 128, align: 64, elements: !242)
!242 = !{!243, !244}
!243 = !DIDerivedType(tag: DW_TAG_member, name: "min", scope: !241, file: !16, line: 1482, baseType: !93, size: 64, align: 64)
!244 = !DIDerivedType(tag: DW_TAG_member, name: "nelts", scope: !241, file: !16, line: 1482, baseType: !106, size: 32, align: 32, offset: 64)
!245 = !DIDerivedType(tag: DW_TAG_member, name: "timer_counter", scope: !102, file: !16, line: 1482, baseType: !246, size: 64, align: 64, offset: 4288)
!246 = !DIDerivedType(tag: DW_TAG_typedef, name: "uint64_t", file: !247, line: 55, baseType: !114)
!247 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!248 = !DIDerivedType(tag: DW_TAG_member, name: "time", scope: !102, file: !16, line: 1482, baseType: !246, size: 64, align: 64, offset: 4352)
!249 = !DIDerivedType(tag: DW_TAG_member, name: "signal_pipefd", scope: !102, file: !16, line: 1482, baseType: !250, size: 64, align: 32, offset: 4416)
!250 = !DICompositeType(tag: DW_TAG_array_type, baseType: !116, size: 64, align: 32, elements: !109)
!251 = !DIDerivedType(tag: DW_TAG_member, name: "signal_io_watcher", scope: !102, file: !16, line: 1482, baseType: !122, size: 448, align: 64, offset: 4480)
!252 = !DIDerivedType(tag: DW_TAG_member, name: "child_watcher", scope: !102, file: !16, line: 1482, baseType: !253, size: 1216, align: 64, offset: 4928)
!253 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_t", file: !16, line: 220, baseType: !254)
!254 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_signal_s", file: !16, line: 1325, size: 1216, align: 64, elements: !255)
!255 = !{!256, !257, !258, !259, !260, !261, !266, !267, !268, !274, !275, !283, !284}
!256 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !254, file: !16, line: 1326, baseType: !93, size: 64, align: 64)
!257 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !254, file: !16, line: 1326, baseType: !100, size: 64, align: 64, offset: 64)
!258 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !254, file: !16, line: 1326, baseType: !179, size: 32, align: 32, offset: 128)
!259 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !254, file: !16, line: 1326, baseType: !181, size: 64, align: 64, offset: 192)
!260 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !254, file: !16, line: 1326, baseType: !108, size: 128, align: 64, offset: 256)
!261 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !254, file: !16, line: 1326, baseType: !262, size: 256, align: 64, offset: 384)
!262 = !DICompositeType(tag: DW_TAG_union_type, scope: !254, file: !16, line: 1326, size: 256, align: 64, elements: !263)
!263 = !{!264, !265}
!264 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !262, file: !16, line: 1326, baseType: !116, size: 32, align: 32)
!265 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !262, file: !16, line: 1326, baseType: !191, size: 256, align: 64)
!266 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !254, file: !16, line: 1326, baseType: !94, size: 64, align: 64, offset: 640)
!267 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !254, file: !16, line: 1326, baseType: !106, size: 32, align: 32, offset: 704)
!268 = !DIDerivedType(tag: DW_TAG_member, name: "signal_cb", scope: !254, file: !16, line: 1327, baseType: !269, size: 64, align: 64, offset: 768)
!269 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_signal_cb", file: !16, line: 362, baseType: !270)
!270 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !271, size: 64, align: 64)
!271 = !DISubroutineType(types: !272)
!272 = !{null, !273, !116}
!273 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !253, size: 64, align: 64)
!274 = !DIDerivedType(tag: DW_TAG_member, name: "signum", scope: !254, file: !16, line: 1328, baseType: !116, size: 32, align: 32, offset: 832)
!275 = !DIDerivedType(tag: DW_TAG_member, name: "tree_entry", scope: !254, file: !16, line: 1329, baseType: !276, size: 256, align: 64, offset: 896)
!276 = !DICompositeType(tag: DW_TAG_structure_type, scope: !254, file: !16, line: 1329, size: 256, align: 64, elements: !277)
!277 = !{!278, !280, !281, !282}
!278 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_left", scope: !276, file: !16, line: 1329, baseType: !279, size: 64, align: 64)
!279 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !254, size: 64, align: 64)
!280 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_right", scope: !276, file: !16, line: 1329, baseType: !279, size: 64, align: 64, offset: 64)
!281 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_parent", scope: !276, file: !16, line: 1329, baseType: !279, size: 64, align: 64, offset: 128)
!282 = !DIDerivedType(tag: DW_TAG_member, name: "rbe_color", scope: !276, file: !16, line: 1329, baseType: !116, size: 32, align: 32, offset: 192)
!283 = !DIDerivedType(tag: DW_TAG_member, name: "caught_signals", scope: !254, file: !16, line: 1329, baseType: !106, size: 32, align: 32, offset: 1152)
!284 = !DIDerivedType(tag: DW_TAG_member, name: "dispatched_signals", scope: !254, file: !16, line: 1329, baseType: !106, size: 32, align: 32, offset: 1184)
!285 = !DIDerivedType(tag: DW_TAG_member, name: "emfile_fd", scope: !102, file: !16, line: 1482, baseType: !116, size: 32, align: 32, offset: 6144)
!286 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_read_watcher", scope: !102, file: !16, line: 1482, baseType: !122, size: 448, align: 64, offset: 6208)
!287 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_watchers", scope: !102, file: !16, line: 1482, baseType: !93, size: 64, align: 64, offset: 6656)
!288 = !DIDerivedType(tag: DW_TAG_member, name: "inotify_fd", scope: !102, file: !16, line: 1482, baseType: !116, size: 32, align: 32, offset: 6720)
!289 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !96, file: !16, line: 426, baseType: !179, size: 32, align: 32, offset: 128)
!290 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !96, file: !16, line: 426, baseType: !181, size: 64, align: 64, offset: 192)
!291 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !96, file: !16, line: 426, baseType: !108, size: 128, align: 64, offset: 256)
!292 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !96, file: !16, line: 426, baseType: !293, size: 256, align: 64, offset: 384)
!293 = !DICompositeType(tag: DW_TAG_union_type, scope: !96, file: !16, line: 426, size: 256, align: 64, elements: !294)
!294 = !{!295, !296}
!295 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !293, file: !16, line: 426, baseType: !116, size: 32, align: 32)
!296 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !293, file: !16, line: 426, baseType: !191, size: 256, align: 64)
!297 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !96, file: !16, line: 426, baseType: !94, size: 64, align: 64, offset: 640)
!298 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !96, file: !16, line: 426, baseType: !106, size: 32, align: 32, offset: 704)
!299 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !300, size: 64, align: 64)
!300 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !301, size: 64, align: 64)
!301 = !DIDerivedType(tag: DW_TAG_typedef, name: "QUEUE", file: !302, line: 21, baseType: !108)
!302 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibuv/src/queue.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!303 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !304, size: 64, align: 64)
!304 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !301)
!305 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !306, size: 64, align: 64)
!306 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_process_t", file: !16, line: 217, baseType: !307)
!307 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_process_s", file: !16, line: 953, size: 1088, align: 64, elements: !308)
!308 = !{!309, !310, !311, !312, !313, !314, !319, !320, !321, !327, !328, !329}
!309 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !307, file: !16, line: 954, baseType: !93, size: 64, align: 64)
!310 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !307, file: !16, line: 954, baseType: !100, size: 64, align: 64, offset: 64)
!311 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !307, file: !16, line: 954, baseType: !179, size: 32, align: 32, offset: 128)
!312 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !307, file: !16, line: 954, baseType: !181, size: 64, align: 64, offset: 192)
!313 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !307, file: !16, line: 954, baseType: !108, size: 128, align: 64, offset: 256)
!314 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !307, file: !16, line: 954, baseType: !315, size: 256, align: 64, offset: 384)
!315 = !DICompositeType(tag: DW_TAG_union_type, scope: !307, file: !16, line: 954, size: 256, align: 64, elements: !316)
!316 = !{!317, !318}
!317 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !315, file: !16, line: 954, baseType: !116, size: 32, align: 32)
!318 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !315, file: !16, line: 954, baseType: !191, size: 256, align: 64)
!319 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !307, file: !16, line: 954, baseType: !94, size: 64, align: 64, offset: 640)
!320 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !307, file: !16, line: 954, baseType: !106, size: 32, align: 32, offset: 704)
!321 = !DIDerivedType(tag: DW_TAG_member, name: "exit_cb", scope: !307, file: !16, line: 955, baseType: !322, size: 64, align: 64, offset: 768)
!322 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_exit_cb", file: !16, line: 313, baseType: !323)
!323 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !324, size: 64, align: 64)
!324 = !DISubroutineType(types: !325)
!325 = !{null, !305, !326, !116}
!326 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !247, line: 40, baseType: !171)
!327 = !DIDerivedType(tag: DW_TAG_member, name: "pid", scope: !307, file: !16, line: 956, baseType: !116, size: 32, align: 32, offset: 832)
!328 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !307, file: !16, line: 957, baseType: !108, size: 128, align: 64, offset: 896)
!329 = !DIDerivedType(tag: DW_TAG_member, name: "status", scope: !307, file: !16, line: 957, baseType: !116, size: 32, align: 32, offset: 1024)
!330 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !167, size: 64, align: 64)
!331 = !DIBasicType(name: "signed char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!332 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !333, size: 64, align: 64)
!333 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_pipe_t", file: !16, line: 209, baseType: !334)
!334 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_pipe_s", file: !16, line: 692, size: 2112, align: 64, elements: !335)
!335 = !{!336, !337, !338, !339, !340, !341, !346, !347, !348, !351, !362, !435, !436, !437, !438, !439, !440, !441, !442, !443, !444, !445}
!336 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !334, file: !16, line: 693, baseType: !93, size: 64, align: 64)
!337 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !334, file: !16, line: 693, baseType: !100, size: 64, align: 64, offset: 64)
!338 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !334, file: !16, line: 693, baseType: !179, size: 32, align: 32, offset: 128)
!339 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !334, file: !16, line: 693, baseType: !181, size: 64, align: 64, offset: 192)
!340 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !334, file: !16, line: 693, baseType: !108, size: 128, align: 64, offset: 256)
!341 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !334, file: !16, line: 693, baseType: !342, size: 256, align: 64, offset: 384)
!342 = !DICompositeType(tag: DW_TAG_union_type, scope: !334, file: !16, line: 693, size: 256, align: 64, elements: !343)
!343 = !{!344, !345}
!344 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !342, file: !16, line: 693, baseType: !116, size: 32, align: 32)
!345 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !342, file: !16, line: 693, baseType: !191, size: 256, align: 64)
!346 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !334, file: !16, line: 693, baseType: !94, size: 64, align: 64, offset: 640)
!347 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !334, file: !16, line: 693, baseType: !106, size: 32, align: 32, offset: 704)
!348 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !334, file: !16, line: 694, baseType: !349, size: 64, align: 64, offset: 768)
!349 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !350, line: 62, baseType: !114)
!350 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!351 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !334, file: !16, line: 694, baseType: !352, size: 64, align: 64, offset: 832)
!352 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_alloc_cb", file: !16, line: 296, baseType: !353)
!353 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !354, size: 64, align: 64)
!354 = !DISubroutineType(types: !355)
!355 = !{null, !94, !349, !356}
!356 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !357, size: 64, align: 64)
!357 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_buf_t", file: !123, line: 119, baseType: !358)
!358 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_buf_t", file: !123, line: 116, size: 128, align: 64, elements: !359)
!359 = !{!360, !361}
!360 = !DIDerivedType(tag: DW_TAG_member, name: "base", scope: !358, file: !123, line: 117, baseType: !330, size: 64, align: 64)
!361 = !DIDerivedType(tag: DW_TAG_member, name: "len", scope: !358, file: !123, line: 118, baseType: !349, size: 64, align: 64, offset: 64)
!362 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !334, file: !16, line: 694, baseType: !363, size: 64, align: 64, offset: 896)
!363 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_read_cb", file: !16, line: 299, baseType: !364)
!364 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !365, size: 64, align: 64)
!365 = !DISubroutineType(types: !366)
!366 = !{null, !367, !429, !433}
!367 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !368, size: 64, align: 64)
!368 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stream_t", file: !16, line: 206, baseType: !369)
!369 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_stream_s", file: !16, line: 465, size: 1984, align: 64, elements: !370)
!370 = !{!371, !372, !373, !374, !375, !376, !381, !382, !383, !384, !385, !386, !403, !418, !419, !420, !421, !426, !427, !428}
!371 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !369, file: !16, line: 466, baseType: !93, size: 64, align: 64)
!372 = !DIDerivedType(tag: DW_TAG_member, name: "loop", scope: !369, file: !16, line: 466, baseType: !100, size: 64, align: 64, offset: 64)
!373 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !369, file: !16, line: 466, baseType: !179, size: 32, align: 32, offset: 128)
!374 = !DIDerivedType(tag: DW_TAG_member, name: "close_cb", scope: !369, file: !16, line: 466, baseType: !181, size: 64, align: 64, offset: 192)
!375 = !DIDerivedType(tag: DW_TAG_member, name: "handle_queue", scope: !369, file: !16, line: 466, baseType: !108, size: 128, align: 64, offset: 256)
!376 = !DIDerivedType(tag: DW_TAG_member, name: "u", scope: !369, file: !16, line: 466, baseType: !377, size: 256, align: 64, offset: 384)
!377 = !DICompositeType(tag: DW_TAG_union_type, scope: !369, file: !16, line: 466, size: 256, align: 64, elements: !378)
!378 = !{!379, !380}
!379 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !377, file: !16, line: 466, baseType: !116, size: 32, align: 32)
!380 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !377, file: !16, line: 466, baseType: !191, size: 256, align: 64)
!381 = !DIDerivedType(tag: DW_TAG_member, name: "next_closing", scope: !369, file: !16, line: 466, baseType: !94, size: 64, align: 64, offset: 640)
!382 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !369, file: !16, line: 466, baseType: !106, size: 32, align: 32, offset: 704)
!383 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue_size", scope: !369, file: !16, line: 467, baseType: !349, size: 64, align: 64, offset: 768)
!384 = !DIDerivedType(tag: DW_TAG_member, name: "alloc_cb", scope: !369, file: !16, line: 467, baseType: !352, size: 64, align: 64, offset: 832)
!385 = !DIDerivedType(tag: DW_TAG_member, name: "read_cb", scope: !369, file: !16, line: 467, baseType: !363, size: 64, align: 64, offset: 896)
!386 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !369, file: !16, line: 467, baseType: !387, size: 64, align: 64, offset: 960)
!387 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !388, size: 64, align: 64)
!388 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_t", file: !16, line: 228, baseType: !389)
!389 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_connect_s", file: !16, line: 551, size: 768, align: 64, elements: !390)
!390 = !{!391, !392, !394, !395, !396, !401, !402}
!391 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !389, file: !16, line: 552, baseType: !93, size: 64, align: 64)
!392 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !389, file: !16, line: 552, baseType: !393, size: 32, align: 32, offset: 64)
!393 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_req_type", file: !16, line: 200, baseType: !45)
!394 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !389, file: !16, line: 552, baseType: !108, size: 128, align: 64, offset: 128)
!395 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !389, file: !16, line: 552, baseType: !191, size: 256, align: 64, offset: 256)
!396 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !389, file: !16, line: 553, baseType: !397, size: 64, align: 64, offset: 512)
!397 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connect_cb", file: !16, line: 303, baseType: !398)
!398 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !399, size: 64, align: 64)
!399 = !DISubroutineType(types: !400)
!400 = !{null, !387, !116}
!401 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !389, file: !16, line: 554, baseType: !367, size: 64, align: 64, offset: 576)
!402 = !DIDerivedType(tag: DW_TAG_member, name: "queue", scope: !389, file: !16, line: 555, baseType: !108, size: 128, align: 64, offset: 640)
!403 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !369, file: !16, line: 467, baseType: !404, size: 64, align: 64, offset: 1024)
!404 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !405, size: 64, align: 64)
!405 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_t", file: !16, line: 226, baseType: !406)
!406 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_shutdown_s", file: !16, line: 401, size: 640, align: 64, elements: !407)
!407 = !{!408, !409, !410, !411, !412, !413}
!408 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !406, file: !16, line: 402, baseType: !93, size: 64, align: 64)
!409 = !DIDerivedType(tag: DW_TAG_member, name: "type", scope: !406, file: !16, line: 402, baseType: !393, size: 32, align: 32, offset: 64)
!410 = !DIDerivedType(tag: DW_TAG_member, name: "active_queue", scope: !406, file: !16, line: 402, baseType: !108, size: 128, align: 64, offset: 128)
!411 = !DIDerivedType(tag: DW_TAG_member, name: "reserved", scope: !406, file: !16, line: 402, baseType: !191, size: 256, align: 64, offset: 256)
!412 = !DIDerivedType(tag: DW_TAG_member, name: "handle", scope: !406, file: !16, line: 403, baseType: !367, size: 64, align: 64, offset: 512)
!413 = !DIDerivedType(tag: DW_TAG_member, name: "cb", scope: !406, file: !16, line: 404, baseType: !414, size: 64, align: 64, offset: 576)
!414 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_shutdown_cb", file: !16, line: 304, baseType: !415)
!415 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !416, size: 64, align: 64)
!416 = !DISubroutineType(types: !417)
!417 = !{null, !404, !116}
!418 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !369, file: !16, line: 467, baseType: !122, size: 448, align: 64, offset: 1088)
!419 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !369, file: !16, line: 467, baseType: !108, size: 128, align: 64, offset: 1536)
!420 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !369, file: !16, line: 467, baseType: !108, size: 128, align: 64, offset: 1664)
!421 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !369, file: !16, line: 467, baseType: !422, size: 64, align: 64, offset: 1792)
!422 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_connection_cb", file: !16, line: 305, baseType: !423)
!423 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !424, size: 64, align: 64)
!424 = !DISubroutineType(types: !425)
!425 = !{null, !367, !116}
!426 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !369, file: !16, line: 467, baseType: !116, size: 32, align: 32, offset: 1856)
!427 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !369, file: !16, line: 467, baseType: !116, size: 32, align: 32, offset: 1888)
!428 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !369, file: !16, line: 467, baseType: !93, size: 64, align: 64, offset: 1920)
!429 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !430, line: 102, baseType: !431)
!430 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!431 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !432, line: 172, baseType: !171)
!432 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!433 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !434, size: 64, align: 64)
!434 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !357)
!435 = !DIDerivedType(tag: DW_TAG_member, name: "connect_req", scope: !334, file: !16, line: 694, baseType: !387, size: 64, align: 64, offset: 960)
!436 = !DIDerivedType(tag: DW_TAG_member, name: "shutdown_req", scope: !334, file: !16, line: 694, baseType: !404, size: 64, align: 64, offset: 1024)
!437 = !DIDerivedType(tag: DW_TAG_member, name: "io_watcher", scope: !334, file: !16, line: 694, baseType: !122, size: 448, align: 64, offset: 1088)
!438 = !DIDerivedType(tag: DW_TAG_member, name: "write_queue", scope: !334, file: !16, line: 694, baseType: !108, size: 128, align: 64, offset: 1536)
!439 = !DIDerivedType(tag: DW_TAG_member, name: "write_completed_queue", scope: !334, file: !16, line: 694, baseType: !108, size: 128, align: 64, offset: 1664)
!440 = !DIDerivedType(tag: DW_TAG_member, name: "connection_cb", scope: !334, file: !16, line: 694, baseType: !422, size: 64, align: 64, offset: 1792)
!441 = !DIDerivedType(tag: DW_TAG_member, name: "delayed_error", scope: !334, file: !16, line: 694, baseType: !116, size: 32, align: 32, offset: 1856)
!442 = !DIDerivedType(tag: DW_TAG_member, name: "accepted_fd", scope: !334, file: !16, line: 694, baseType: !116, size: 32, align: 32, offset: 1888)
!443 = !DIDerivedType(tag: DW_TAG_member, name: "queued_fds", scope: !334, file: !16, line: 694, baseType: !93, size: 64, align: 64, offset: 1920)
!444 = !DIDerivedType(tag: DW_TAG_member, name: "ipc", scope: !334, file: !16, line: 695, baseType: !116, size: 32, align: 32, offset: 1984)
!445 = !DIDerivedType(tag: DW_TAG_member, name: "pipe_fname", scope: !334, file: !16, line: 696, baseType: !446, size: 64, align: 64, offset: 2048)
!446 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !447, size: 64, align: 64)
!447 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !167)
!448 = !{!449, !454, !455, !492, !495, !498, !501, !504, !505, !509, !512, !515}
!449 = distinct !DISubprogram(name: "uv__make_socketpair", scope: !1, file: !1, line: 115, type: !450, isLocal: false, isDefinition: true, scopeLine: 115, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!450 = !DISubroutineType(types: !451)
!451 = !{!116, !452, !116}
!452 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !116, size: 64, align: 64)
!453 = !{}
!454 = distinct !DISubprogram(name: "uv__make_pipe", scope: !1, file: !1, line: 151, type: !450, isLocal: false, isDefinition: true, scopeLine: 151, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!455 = distinct !DISubprogram(name: "uv_spawn", scope: !1, file: !1, line: 386, type: !456, isLocal: false, isDefinition: true, scopeLine: 388, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!456 = !DISubroutineType(types: !457)
!457 = !{!116, !100, !305, !458}
!458 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !459, size: 64, align: 64)
!459 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !460)
!460 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_process_options_t", file: !16, line: 910, baseType: !461)
!461 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_process_options_s", file: !16, line: 867, size: 512, align: 64, elements: !462)
!462 = !{!463, !464, !465, !467, !468, !469, !470, !471, !483, !488}
!463 = !DIDerivedType(tag: DW_TAG_member, name: "exit_cb", scope: !461, file: !16, line: 868, baseType: !322, size: 64, align: 64)
!464 = !DIDerivedType(tag: DW_TAG_member, name: "file", scope: !461, file: !16, line: 869, baseType: !446, size: 64, align: 64, offset: 64)
!465 = !DIDerivedType(tag: DW_TAG_member, name: "args", scope: !461, file: !16, line: 876, baseType: !466, size: 64, align: 64, offset: 128)
!466 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !330, size: 64, align: 64)
!467 = !DIDerivedType(tag: DW_TAG_member, name: "env", scope: !461, file: !16, line: 881, baseType: !466, size: 64, align: 64, offset: 192)
!468 = !DIDerivedType(tag: DW_TAG_member, name: "cwd", scope: !461, file: !16, line: 886, baseType: !446, size: 64, align: 64, offset: 256)
!469 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !461, file: !16, line: 891, baseType: !106, size: 32, align: 32, offset: 320)
!470 = !DIDerivedType(tag: DW_TAG_member, name: "stdio_count", scope: !461, file: !16, line: 901, baseType: !116, size: 32, align: 32, offset: 352)
!471 = !DIDerivedType(tag: DW_TAG_member, name: "stdio", scope: !461, file: !16, line: 902, baseType: !472, size: 64, align: 64, offset: 384)
!472 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !473, size: 64, align: 64)
!473 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stdio_container_t", file: !16, line: 865, baseType: !474)
!474 = !DICompositeType(tag: DW_TAG_structure_type, name: "uv_stdio_container_s", file: !16, line: 858, size: 128, align: 64, elements: !475)
!475 = !{!476, !478}
!476 = !DIDerivedType(tag: DW_TAG_member, name: "flags", scope: !474, file: !16, line: 859, baseType: !477, size: 32, align: 32)
!477 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_stdio_flags", file: !16, line: 856, baseType: !37)
!478 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !474, file: !16, line: 864, baseType: !479, size: 64, align: 64, offset: 64)
!479 = !DICompositeType(tag: DW_TAG_union_type, scope: !474, file: !16, line: 861, size: 64, align: 64, elements: !480)
!480 = !{!481, !482}
!481 = !DIDerivedType(tag: DW_TAG_member, name: "stream", scope: !479, file: !16, line: 862, baseType: !367, size: 64, align: 64)
!482 = !DIDerivedType(tag: DW_TAG_member, name: "fd", scope: !479, file: !16, line: 863, baseType: !116, size: 32, align: 32)
!483 = !DIDerivedType(tag: DW_TAG_member, name: "uid", scope: !461, file: !16, line: 908, baseType: !484, size: 32, align: 32, offset: 448)
!484 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_uid_t", file: !123, line: 139, baseType: !485)
!485 = !DIDerivedType(tag: DW_TAG_typedef, name: "uid_t", file: !486, line: 80, baseType: !487)
!486 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibuv")
!487 = !DIDerivedType(tag: DW_TAG_typedef, name: "__uid_t", file: !432, line: 125, baseType: !106)
!488 = !DIDerivedType(tag: DW_TAG_member, name: "gid", scope: !461, file: !16, line: 909, baseType: !489, size: 32, align: 32, offset: 480)
!489 = !DIDerivedType(tag: DW_TAG_typedef, name: "uv_gid_t", file: !123, line: 138, baseType: !490)
!490 = !DIDerivedType(tag: DW_TAG_typedef, name: "gid_t", file: !486, line: 65, baseType: !491)
!491 = !DIDerivedType(tag: DW_TAG_typedef, name: "__gid_t", file: !432, line: 126, baseType: !106)
!492 = distinct !DISubprogram(name: "uv_process_kill", scope: !1, file: !1, line: 545, type: !493, isLocal: false, isDefinition: true, scopeLine: 545, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!493 = !DISubroutineType(types: !494)
!494 = !{!116, !305, !116}
!495 = distinct !DISubprogram(name: "uv_kill", scope: !1, file: !1, line: 550, type: !496, isLocal: false, isDefinition: true, scopeLine: 550, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!496 = !DISubroutineType(types: !497)
!497 = !{!116, !116, !116}
!498 = distinct !DISubprogram(name: "uv__process_close", scope: !1, file: !1, line: 558, type: !499, isLocal: false, isDefinition: true, scopeLine: 558, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!499 = !DISubroutineType(types: !500)
!500 = !{null, !305}
!501 = distinct !DISubprogram(name: "uv__process_init_stdio", scope: !1, file: !1, line: 188, type: !502, isLocal: true, isDefinition: true, scopeLine: 188, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!502 = !DISubroutineType(types: !503)
!503 = !{!116, !472, !452}
!504 = distinct !DISubprogram(name: "uv__chld", scope: !1, file: !1, line: 48, type: !271, isLocal: true, isDefinition: true, scopeLine: 48, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!505 = distinct !DISubprogram(name: "uv__process_child_init", scope: !1, file: !1, line: 278, type: !506, isLocal: true, isDefinition: true, scopeLine: 281, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!506 = !DISubroutineType(types: !507)
!507 = !{null, !458, !116, !508, !116}
!508 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !250, size: 64, align: 64)
!509 = distinct !DISubprogram(name: "uv__write_int", scope: !1, file: !1, line: 259, type: !510, isLocal: true, isDefinition: true, scopeLine: 259, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!510 = !DISubroutineType(types: !511)
!511 = !{null, !116, !116}
!512 = distinct !DISubprogram(name: "uv__process_open_stream", scope: !1, file: !1, line: 225, type: !513, isLocal: true, isDefinition: true, scopeLine: 227, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!513 = !DISubroutineType(types: !514)
!514 = !{!116, !472, !452, !116}
!515 = distinct !DISubprogram(name: "uv__process_close_stream", scope: !1, file: !1, line: 253, type: !516, isLocal: true, isDefinition: true, scopeLine: 253, flags: DIFlagPrototyped, isOptimized: false, variables: !453)
!516 = !DISubroutineType(types: !517)
!517 = !{null, !472}
!518 = !{!519, !520}
!519 = !DIGlobalVariable(name: "no_cloexec", scope: !449, file: !1, line: 117, type: !116, isLocal: true, isDefinition: true, variable: i32* @uv__make_socketpair.no_cloexec)
!520 = !DIGlobalVariable(name: "no_pipe2", scope: !454, file: !1, line: 153, type: !116, isLocal: true, isDefinition: true, variable: i32* @uv__make_pipe.no_pipe2)
!521 = !{i32 2, !"Dwarf Version", i32 4}
!522 = !{i32 2, !"Debug Info Version", i32 3}
!523 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!524 = !DILocalVariable(name: "fds", arg: 1, scope: !449, file: !1, line: 115, type: !452)
!525 = !DIExpression()
!526 = !DILocation(line: 115, column: 29, scope: !449)
!527 = !DILocalVariable(name: "flags", arg: 2, scope: !449, file: !1, line: 115, type: !116)
!528 = !DILocation(line: 115, column: 41, scope: !449)
!529 = !DILocation(line: 119, column: 7, scope: !530)
!530 = distinct !DILexicalBlock(scope: !449, file: !1, line: 119, column: 7)
!531 = !DILocation(line: 119, column: 7, scope: !449)
!532 = !DILocation(line: 120, column: 5, scope: !530)
!533 = !DILocation(line: 122, column: 60, scope: !534)
!534 = distinct !DILexicalBlock(scope: !449, file: !1, line: 122, column: 7)
!535 = !DILocation(line: 122, column: 58, scope: !534)
!536 = !DILocation(line: 122, column: 70, scope: !534)
!537 = !DILocation(line: 122, column: 7, scope: !534)
!538 = !DILocation(line: 122, column: 75, scope: !534)
!539 = !DILocation(line: 122, column: 7, scope: !449)
!540 = !DILocation(line: 123, column: 5, scope: !534)
!541 = !DILocation(line: 128, column: 7, scope: !542)
!542 = distinct !DILexicalBlock(scope: !449, file: !1, line: 128, column: 7)
!543 = !DILocation(line: 128, column: 13, scope: !542)
!544 = !DILocation(line: 128, column: 7, scope: !449)
!545 = !DILocation(line: 129, column: 13, scope: !542)
!546 = !DILocation(line: 129, column: 12, scope: !542)
!547 = !DILocation(line: 129, column: 5, scope: !542)
!548 = !DILocation(line: 131, column: 14, scope: !449)
!549 = !DILocation(line: 131, column: 3, scope: !449)
!550 = !DILocation(line: 136, column: 43, scope: !551)
!551 = distinct !DILexicalBlock(scope: !449, file: !1, line: 136, column: 7)
!552 = !DILocation(line: 136, column: 7, scope: !551)
!553 = !DILocation(line: 136, column: 7, scope: !449)
!554 = !DILocation(line: 137, column: 13, scope: !551)
!555 = !DILocation(line: 137, column: 12, scope: !551)
!556 = !DILocation(line: 137, column: 5, scope: !551)
!557 = !DILocation(line: 139, column: 15, scope: !449)
!558 = !DILocation(line: 139, column: 3, scope: !449)
!559 = !DILocation(line: 140, column: 15, scope: !449)
!560 = !DILocation(line: 140, column: 3, scope: !449)
!561 = !DILocation(line: 142, column: 7, scope: !562)
!562 = distinct !DILexicalBlock(scope: !449, file: !1, line: 142, column: 7)
!563 = !DILocation(line: 142, column: 13, scope: !562)
!564 = !DILocation(line: 142, column: 7, scope: !449)
!565 = !DILocation(line: 143, column: 18, scope: !566)
!566 = distinct !DILexicalBlock(scope: !562, file: !1, line: 142, column: 31)
!567 = !DILocation(line: 143, column: 5, scope: !566)
!568 = !DILocation(line: 144, column: 18, scope: !566)
!569 = !DILocation(line: 144, column: 5, scope: !566)
!570 = !DILocation(line: 145, column: 3, scope: !566)
!571 = !DILocation(line: 147, column: 3, scope: !449)
!572 = !DILocation(line: 148, column: 1, scope: !449)
!573 = !DILocalVariable(name: "fds", arg: 1, scope: !454, file: !1, line: 151, type: !452)
!574 = !DILocation(line: 151, column: 23, scope: !454)
!575 = !DILocalVariable(name: "flags", arg: 2, scope: !454, file: !1, line: 151, type: !116)
!576 = !DILocation(line: 151, column: 35, scope: !454)
!577 = !DILocation(line: 155, column: 7, scope: !578)
!578 = distinct !DILexicalBlock(scope: !454, file: !1, line: 155, column: 7)
!579 = !DILocation(line: 155, column: 7, scope: !454)
!580 = !DILocation(line: 156, column: 5, scope: !578)
!581 = !DILocation(line: 158, column: 17, scope: !582)
!582 = distinct !DILexicalBlock(scope: !454, file: !1, line: 158, column: 7)
!583 = !DILocation(line: 158, column: 22, scope: !582)
!584 = !DILocation(line: 158, column: 28, scope: !582)
!585 = !DILocation(line: 158, column: 7, scope: !582)
!586 = !DILocation(line: 158, column: 45, scope: !582)
!587 = !DILocation(line: 158, column: 7, scope: !454)
!588 = !DILocation(line: 159, column: 5, scope: !582)
!589 = !DILocation(line: 161, column: 7, scope: !590)
!590 = distinct !DILexicalBlock(scope: !454, file: !1, line: 161, column: 7)
!591 = !DILocation(line: 161, column: 13, scope: !590)
!592 = !DILocation(line: 161, column: 7, scope: !454)
!593 = !DILocation(line: 162, column: 13, scope: !590)
!594 = !DILocation(line: 162, column: 12, scope: !590)
!595 = !DILocation(line: 162, column: 5, scope: !590)
!596 = !DILocation(line: 164, column: 12, scope: !454)
!597 = !DILocation(line: 164, column: 3, scope: !454)
!598 = !DILocation(line: 169, column: 12, scope: !599)
!599 = distinct !DILexicalBlock(scope: !454, file: !1, line: 169, column: 7)
!600 = !DILocation(line: 169, column: 7, scope: !599)
!601 = !DILocation(line: 169, column: 7, scope: !454)
!602 = !DILocation(line: 170, column: 13, scope: !599)
!603 = !DILocation(line: 170, column: 12, scope: !599)
!604 = !DILocation(line: 170, column: 5, scope: !599)
!605 = !DILocation(line: 172, column: 15, scope: !454)
!606 = !DILocation(line: 172, column: 3, scope: !454)
!607 = !DILocation(line: 173, column: 15, scope: !454)
!608 = !DILocation(line: 173, column: 3, scope: !454)
!609 = !DILocation(line: 175, column: 7, scope: !610)
!610 = distinct !DILexicalBlock(scope: !454, file: !1, line: 175, column: 7)
!611 = !DILocation(line: 175, column: 13, scope: !610)
!612 = !DILocation(line: 175, column: 7, scope: !454)
!613 = !DILocation(line: 176, column: 18, scope: !614)
!614 = distinct !DILexicalBlock(scope: !610, file: !1, line: 175, column: 31)
!615 = !DILocation(line: 176, column: 5, scope: !614)
!616 = !DILocation(line: 177, column: 18, scope: !614)
!617 = !DILocation(line: 177, column: 5, scope: !614)
!618 = !DILocation(line: 178, column: 3, scope: !614)
!619 = !DILocation(line: 180, column: 3, scope: !454)
!620 = !DILocation(line: 181, column: 1, scope: !454)
!621 = !DILocalVariable(name: "loop", arg: 1, scope: !455, file: !1, line: 386, type: !100)
!622 = !DILocation(line: 386, column: 25, scope: !455)
!623 = !DILocalVariable(name: "process", arg: 2, scope: !455, file: !1, line: 387, type: !305)
!624 = !DILocation(line: 387, column: 28, scope: !455)
!625 = !DILocalVariable(name: "options", arg: 3, scope: !455, file: !1, line: 388, type: !458)
!626 = !DILocation(line: 388, column: 42, scope: !455)
!627 = !DILocalVariable(name: "signal_pipe", scope: !455, file: !1, line: 393, type: !250)
!628 = !DILocation(line: 393, column: 7, scope: !455)
!629 = !DILocalVariable(name: "pipes", scope: !455, file: !1, line: 394, type: !508)
!630 = !DILocation(line: 394, column: 9, scope: !455)
!631 = !DILocalVariable(name: "stdio_count", scope: !455, file: !1, line: 395, type: !116)
!632 = !DILocation(line: 395, column: 7, scope: !455)
!633 = !DILocalVariable(name: "r", scope: !455, file: !1, line: 396, type: !429)
!634 = !DILocation(line: 396, column: 11, scope: !455)
!635 = !DILocalVariable(name: "pid", scope: !455, file: !1, line: 397, type: !636)
!636 = !DIDerivedType(tag: DW_TAG_typedef, name: "pid_t", file: !486, line: 98, baseType: !637)
!637 = !DIDerivedType(tag: DW_TAG_typedef, name: "__pid_t", file: !432, line: 133, baseType: !116)
!638 = !DILocation(line: 397, column: 9, scope: !455)
!639 = !DILocalVariable(name: "err", scope: !455, file: !1, line: 398, type: !116)
!640 = !DILocation(line: 398, column: 7, scope: !455)
!641 = !DILocalVariable(name: "exec_errorno", scope: !455, file: !1, line: 399, type: !116)
!642 = !DILocation(line: 399, column: 7, scope: !455)
!643 = !DILocalVariable(name: "i", scope: !455, file: !1, line: 400, type: !116)
!644 = !DILocation(line: 400, column: 7, scope: !455)
!645 = !DILocalVariable(name: "status", scope: !455, file: !1, line: 401, type: !116)
!646 = !DILocation(line: 401, column: 7, scope: !455)
!647 = !DILocation(line: 403, column: 3, scope: !455)
!648 = !DILocation(line: 403, column: 3, scope: !649)
!649 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 1)
!650 = !DILocation(line: 403, column: 3, scope: !651)
!651 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 2)
!652 = !DILocation(line: 403, column: 3, scope: !653)
!653 = !DILexicalBlockFile(scope: !455, file: !1, discriminator: 3)
!654 = !DILocation(line: 404, column: 3, scope: !455)
!655 = !DILocation(line: 404, column: 3, scope: !649)
!656 = !DILocation(line: 404, column: 3, scope: !651)
!657 = !DILocation(line: 404, column: 3, scope: !653)
!658 = !DILocation(line: 410, column: 3, scope: !455)
!659 = !DILocation(line: 410, column: 3, scope: !660)
!660 = !DILexicalBlockFile(scope: !661, file: !1, discriminator: 1)
!661 = distinct !DILexicalBlock(scope: !455, file: !1, line: 410, column: 3)
!662 = !DILocation(line: 410, column: 3, scope: !663)
!663 = !DILexicalBlockFile(scope: !664, file: !1, discriminator: 2)
!664 = distinct !DILexicalBlock(scope: !661, file: !1, line: 410, column: 3)
!665 = !DILocation(line: 410, column: 3, scope: !666)
!666 = !DILexicalBlockFile(scope: !661, file: !1, discriminator: 3)
!667 = !DILocation(line: 411, column: 3, scope: !455)
!668 = !DILocation(line: 411, column: 3, scope: !669)
!669 = !DILexicalBlockFile(scope: !670, file: !1, discriminator: 1)
!670 = distinct !DILexicalBlock(scope: !455, file: !1, line: 411, column: 3)
!671 = !DILocation(line: 413, column: 17, scope: !455)
!672 = !DILocation(line: 413, column: 26, scope: !455)
!673 = !DILocation(line: 413, column: 15, scope: !455)
!674 = !DILocation(line: 414, column: 7, scope: !675)
!675 = distinct !DILexicalBlock(scope: !455, file: !1, line: 414, column: 7)
!676 = !DILocation(line: 414, column: 19, scope: !675)
!677 = !DILocation(line: 414, column: 7, scope: !455)
!678 = !DILocation(line: 415, column: 17, scope: !675)
!679 = !DILocation(line: 415, column: 5, scope: !675)
!680 = !DILocation(line: 417, column: 7, scope: !455)
!681 = !DILocation(line: 418, column: 22, scope: !455)
!682 = !DILocation(line: 418, column: 34, scope: !455)
!683 = !DILocation(line: 418, column: 11, scope: !455)
!684 = !DILocation(line: 418, column: 9, scope: !455)
!685 = !DILocation(line: 419, column: 7, scope: !686)
!686 = distinct !DILexicalBlock(scope: !455, file: !1, line: 419, column: 7)
!687 = !DILocation(line: 419, column: 13, scope: !686)
!688 = !DILocation(line: 419, column: 7, scope: !455)
!689 = !DILocation(line: 420, column: 5, scope: !686)
!690 = !DILocation(line: 422, column: 10, scope: !691)
!691 = distinct !DILexicalBlock(scope: !455, file: !1, line: 422, column: 3)
!692 = !DILocation(line: 422, column: 8, scope: !691)
!693 = !DILocation(line: 422, column: 15, scope: !694)
!694 = !DILexicalBlockFile(scope: !695, file: !1, discriminator: 1)
!695 = distinct !DILexicalBlock(scope: !691, file: !1, line: 422, column: 3)
!696 = !DILocation(line: 422, column: 19, scope: !694)
!697 = !DILocation(line: 422, column: 17, scope: !694)
!698 = !DILocation(line: 422, column: 3, scope: !694)
!699 = !DILocation(line: 423, column: 11, scope: !700)
!700 = distinct !DILexicalBlock(scope: !695, file: !1, line: 422, column: 37)
!701 = !DILocation(line: 423, column: 5, scope: !700)
!702 = !DILocation(line: 423, column: 17, scope: !700)
!703 = !DILocation(line: 424, column: 11, scope: !700)
!704 = !DILocation(line: 424, column: 5, scope: !700)
!705 = !DILocation(line: 424, column: 17, scope: !700)
!706 = !DILocation(line: 425, column: 3, scope: !700)
!707 = !DILocation(line: 422, column: 33, scope: !708)
!708 = !DILexicalBlockFile(scope: !695, file: !1, discriminator: 2)
!709 = !DILocation(line: 422, column: 3, scope: !708)
!710 = !DILocation(line: 427, column: 10, scope: !711)
!711 = distinct !DILexicalBlock(scope: !455, file: !1, line: 427, column: 3)
!712 = !DILocation(line: 427, column: 8, scope: !711)
!713 = !DILocation(line: 427, column: 15, scope: !714)
!714 = !DILexicalBlockFile(scope: !715, file: !1, discriminator: 1)
!715 = distinct !DILexicalBlock(scope: !711, file: !1, line: 427, column: 3)
!716 = !DILocation(line: 427, column: 19, scope: !714)
!717 = !DILocation(line: 427, column: 28, scope: !714)
!718 = !DILocation(line: 427, column: 17, scope: !714)
!719 = !DILocation(line: 427, column: 3, scope: !714)
!720 = !DILocation(line: 428, column: 34, scope: !721)
!721 = distinct !DILexicalBlock(scope: !715, file: !1, line: 427, column: 46)
!722 = !DILocation(line: 428, column: 43, scope: !721)
!723 = !DILocation(line: 428, column: 51, scope: !721)
!724 = !DILocation(line: 428, column: 49, scope: !721)
!725 = !DILocation(line: 428, column: 60, scope: !721)
!726 = !DILocation(line: 428, column: 54, scope: !721)
!727 = !DILocation(line: 428, column: 11, scope: !721)
!728 = !DILocation(line: 428, column: 9, scope: !721)
!729 = !DILocation(line: 429, column: 9, scope: !730)
!730 = distinct !DILexicalBlock(scope: !721, file: !1, line: 429, column: 9)
!731 = !DILocation(line: 429, column: 9, scope: !721)
!732 = !DILocation(line: 430, column: 7, scope: !730)
!733 = !DILocation(line: 431, column: 3, scope: !721)
!734 = !DILocation(line: 427, column: 42, scope: !735)
!735 = !DILexicalBlockFile(scope: !715, file: !1, discriminator: 2)
!736 = !DILocation(line: 427, column: 3, scope: !735)
!737 = !DILocation(line: 453, column: 23, scope: !455)
!738 = !DILocation(line: 453, column: 9, scope: !455)
!739 = !DILocation(line: 453, column: 7, scope: !455)
!740 = !DILocation(line: 454, column: 7, scope: !741)
!741 = distinct !DILexicalBlock(scope: !455, file: !1, line: 454, column: 7)
!742 = !DILocation(line: 454, column: 7, scope: !455)
!743 = !DILocation(line: 455, column: 5, scope: !741)
!744 = !DILocation(line: 457, column: 20, scope: !455)
!745 = !DILocation(line: 457, column: 26, scope: !455)
!746 = !DILocation(line: 457, column: 3, scope: !455)
!747 = !DILocation(line: 460, column: 21, scope: !455)
!748 = !DILocation(line: 460, column: 27, scope: !455)
!749 = !DILocation(line: 460, column: 3, scope: !455)
!750 = !DILocation(line: 461, column: 9, scope: !455)
!751 = !DILocation(line: 461, column: 7, scope: !455)
!752 = !DILocation(line: 463, column: 7, scope: !753)
!753 = distinct !DILexicalBlock(scope: !455, file: !1, line: 463, column: 7)
!754 = !DILocation(line: 463, column: 11, scope: !753)
!755 = !DILocation(line: 463, column: 7, scope: !455)
!756 = !DILocation(line: 464, column: 12, scope: !757)
!757 = distinct !DILexicalBlock(scope: !753, file: !1, line: 463, column: 18)
!758 = !DILocation(line: 464, column: 11, scope: !757)
!759 = !DILocation(line: 464, column: 9, scope: !757)
!760 = !DILocation(line: 465, column: 25, scope: !757)
!761 = !DILocation(line: 465, column: 31, scope: !757)
!762 = !DILocation(line: 465, column: 5, scope: !757)
!763 = !DILocation(line: 466, column: 15, scope: !757)
!764 = !DILocation(line: 466, column: 5, scope: !757)
!765 = !DILocation(line: 467, column: 15, scope: !757)
!766 = !DILocation(line: 467, column: 5, scope: !757)
!767 = !DILocation(line: 468, column: 5, scope: !757)
!768 = !DILocation(line: 471, column: 7, scope: !769)
!769 = distinct !DILexicalBlock(scope: !455, file: !1, line: 471, column: 7)
!770 = !DILocation(line: 471, column: 11, scope: !769)
!771 = !DILocation(line: 471, column: 7, scope: !455)
!772 = !DILocation(line: 472, column: 28, scope: !773)
!773 = distinct !DILexicalBlock(scope: !769, file: !1, line: 471, column: 17)
!774 = !DILocation(line: 472, column: 37, scope: !773)
!775 = !DILocation(line: 472, column: 50, scope: !773)
!776 = !DILocation(line: 472, column: 57, scope: !773)
!777 = !DILocation(line: 472, column: 5, scope: !773)
!778 = !DILocation(line: 473, column: 5, scope: !773)
!779 = !DILocation(line: 477, column: 23, scope: !455)
!780 = !DILocation(line: 477, column: 29, scope: !455)
!781 = !DILocation(line: 477, column: 3, scope: !455)
!782 = !DILocation(line: 478, column: 13, scope: !455)
!783 = !DILocation(line: 478, column: 3, scope: !455)
!784 = !DILocation(line: 480, column: 3, scope: !455)
!785 = !DILocation(line: 480, column: 12, scope: !455)
!786 = !DILocation(line: 480, column: 19, scope: !455)
!787 = !DILocation(line: 481, column: 16, scope: !455)
!788 = !DILocation(line: 482, column: 3, scope: !455)
!789 = !DILocation(line: 483, column: 14, scope: !455)
!790 = !DILocation(line: 483, column: 30, scope: !455)
!791 = !DILocation(line: 483, column: 9, scope: !455)
!792 = !DILocation(line: 483, column: 7, scope: !455)
!793 = !DILocation(line: 483, column: 5, scope: !455)
!794 = !DILocation(line: 484, column: 10, scope: !455)
!795 = !DILocation(line: 484, column: 12, scope: !455)
!796 = !DILocation(line: 484, column: 18, scope: !455)
!797 = !DILocation(line: 484, column: 21, scope: !649)
!798 = !DILocation(line: 484, column: 27, scope: !649)
!799 = !DILocation(line: 483, column: 5, scope: !649)
!800 = !DILocation(line: 486, column: 7, scope: !801)
!801 = distinct !DILexicalBlock(scope: !455, file: !1, line: 486, column: 7)
!802 = !DILocation(line: 486, column: 9, scope: !801)
!803 = !DILocation(line: 486, column: 7, scope: !455)
!804 = !DILocation(line: 486, column: 7, scope: !649)
!805 = !DILocation(line: 488, column: 12, scope: !806)
!806 = distinct !DILexicalBlock(scope: !801, file: !1, line: 488, column: 12)
!807 = !DILocation(line: 488, column: 14, scope: !806)
!808 = !DILocation(line: 488, column: 12, scope: !801)
!809 = !DILocation(line: 489, column: 5, scope: !810)
!810 = distinct !DILexicalBlock(scope: !806, file: !1, line: 488, column: 39)
!811 = !DILocation(line: 490, column: 21, scope: !810)
!812 = !DILocation(line: 490, column: 13, scope: !810)
!813 = !DILocation(line: 490, column: 11, scope: !810)
!814 = !DILocation(line: 490, column: 7, scope: !810)
!815 = !DILocation(line: 491, column: 12, scope: !810)
!816 = !DILocation(line: 491, column: 16, scope: !810)
!817 = !DILocation(line: 491, column: 22, scope: !810)
!818 = !DILocation(line: 491, column: 25, scope: !819)
!819 = !DILexicalBlockFile(scope: !810, file: !1, discriminator: 1)
!820 = !DILocation(line: 491, column: 31, scope: !819)
!821 = !DILocation(line: 490, column: 7, scope: !819)
!822 = !DILocation(line: 492, column: 5, scope: !810)
!823 = !DILocation(line: 492, column: 5, scope: !819)
!824 = !DILocation(line: 492, column: 5, scope: !825)
!825 = !DILexicalBlockFile(scope: !810, file: !1, discriminator: 2)
!826 = !DILocation(line: 492, column: 5, scope: !827)
!827 = !DILexicalBlockFile(scope: !810, file: !1, discriminator: 3)
!828 = !DILocation(line: 493, column: 3, scope: !810)
!829 = !DILocation(line: 493, column: 14, scope: !830)
!830 = !DILexicalBlockFile(scope: !831, file: !1, discriminator: 1)
!831 = distinct !DILexicalBlock(scope: !806, file: !1, line: 493, column: 14)
!832 = !DILocation(line: 493, column: 16, scope: !830)
!833 = !DILocation(line: 493, column: 22, scope: !830)
!834 = !DILocation(line: 493, column: 25, scope: !835)
!835 = !DILexicalBlockFile(scope: !831, file: !1, discriminator: 2)
!836 = !DILocation(line: 493, column: 31, scope: !835)
!837 = !DILocation(line: 493, column: 14, scope: !835)
!838 = !DILocation(line: 494, column: 5, scope: !839)
!839 = distinct !DILexicalBlock(scope: !831, file: !1, line: 493, column: 41)
!840 = !DILocation(line: 495, column: 21, scope: !839)
!841 = !DILocation(line: 495, column: 13, scope: !839)
!842 = !DILocation(line: 495, column: 11, scope: !839)
!843 = !DILocation(line: 495, column: 7, scope: !839)
!844 = !DILocation(line: 496, column: 12, scope: !839)
!845 = !DILocation(line: 496, column: 16, scope: !839)
!846 = !DILocation(line: 496, column: 22, scope: !839)
!847 = !DILocation(line: 496, column: 25, scope: !848)
!848 = !DILexicalBlockFile(scope: !839, file: !1, discriminator: 1)
!849 = !DILocation(line: 496, column: 31, scope: !848)
!850 = !DILocation(line: 495, column: 7, scope: !848)
!851 = !DILocation(line: 497, column: 5, scope: !839)
!852 = !DILocation(line: 497, column: 5, scope: !848)
!853 = !DILocation(line: 497, column: 5, scope: !854)
!854 = !DILexicalBlockFile(scope: !839, file: !1, discriminator: 2)
!855 = !DILocation(line: 497, column: 5, scope: !856)
!856 = !DILexicalBlockFile(scope: !839, file: !1, discriminator: 3)
!857 = !DILocation(line: 498, column: 3, scope: !839)
!858 = !DILocation(line: 499, column: 5, scope: !831)
!859 = !DILocation(line: 501, column: 26, scope: !455)
!860 = !DILocation(line: 501, column: 3, scope: !455)
!861 = !DILocation(line: 503, column: 10, scope: !862)
!862 = distinct !DILexicalBlock(scope: !455, file: !1, line: 503, column: 3)
!863 = !DILocation(line: 503, column: 8, scope: !862)
!864 = !DILocation(line: 503, column: 15, scope: !865)
!865 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 1)
!866 = distinct !DILexicalBlock(scope: !862, file: !1, line: 503, column: 3)
!867 = !DILocation(line: 503, column: 19, scope: !865)
!868 = !DILocation(line: 503, column: 28, scope: !865)
!869 = !DILocation(line: 503, column: 17, scope: !865)
!870 = !DILocation(line: 503, column: 3, scope: !865)
!871 = !DILocation(line: 504, column: 35, scope: !872)
!872 = distinct !DILexicalBlock(scope: !866, file: !1, line: 503, column: 46)
!873 = !DILocation(line: 504, column: 44, scope: !872)
!874 = !DILocation(line: 504, column: 52, scope: !872)
!875 = !DILocation(line: 504, column: 50, scope: !872)
!876 = !DILocation(line: 504, column: 61, scope: !872)
!877 = !DILocation(line: 504, column: 55, scope: !872)
!878 = !DILocation(line: 504, column: 65, scope: !872)
!879 = !DILocation(line: 504, column: 67, scope: !872)
!880 = !DILocation(line: 504, column: 11, scope: !872)
!881 = !DILocation(line: 504, column: 9, scope: !872)
!882 = !DILocation(line: 505, column: 9, scope: !883)
!883 = distinct !DILexicalBlock(scope: !872, file: !1, line: 505, column: 9)
!884 = !DILocation(line: 505, column: 13, scope: !883)
!885 = !DILocation(line: 505, column: 9, scope: !872)
!886 = !DILocation(line: 506, column: 7, scope: !883)
!887 = !DILocation(line: 508, column: 5, scope: !872)
!888 = !DILocation(line: 508, column: 13, scope: !889)
!889 = !DILexicalBlockFile(scope: !872, file: !1, discriminator: 1)
!890 = !DILocation(line: 508, column: 5, scope: !889)
!891 = !DILocation(line: 509, column: 32, scope: !872)
!892 = !DILocation(line: 509, column: 41, scope: !872)
!893 = !DILocation(line: 509, column: 49, scope: !872)
!894 = !DILocation(line: 509, column: 47, scope: !872)
!895 = !DILocation(line: 509, column: 7, scope: !872)
!896 = !DILocation(line: 508, column: 5, scope: !897)
!897 = !DILexicalBlockFile(scope: !872, file: !1, discriminator: 2)
!898 = !DILocation(line: 511, column: 5, scope: !872)
!899 = !DILocation(line: 503, column: 42, scope: !900)
!900 = !DILexicalBlockFile(scope: !866, file: !1, discriminator: 2)
!901 = !DILocation(line: 503, column: 3, scope: !900)
!902 = !DILocation(line: 515, column: 7, scope: !903)
!903 = distinct !DILexicalBlock(scope: !455, file: !1, line: 515, column: 7)
!904 = !DILocation(line: 515, column: 20, scope: !903)
!905 = !DILocation(line: 515, column: 7, scope: !455)
!906 = !DILocation(line: 516, column: 5, scope: !907)
!907 = distinct !DILexicalBlock(scope: !903, file: !1, line: 515, column: 26)
!908 = !DILocation(line: 516, column: 5, scope: !909)
!909 = !DILexicalBlockFile(scope: !910, file: !1, discriminator: 1)
!910 = distinct !DILexicalBlock(scope: !907, file: !1, line: 516, column: 5)
!911 = !DILocation(line: 517, column: 5, scope: !907)
!912 = !DILocation(line: 517, column: 5, scope: !913)
!913 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 1)
!914 = distinct !DILexicalBlock(scope: !907, file: !1, line: 517, column: 5)
!915 = !DILocation(line: 517, column: 5, scope: !916)
!916 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 2)
!917 = !DILocation(line: 517, column: 5, scope: !918)
!918 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 3)
!919 = !DILocation(line: 517, column: 5, scope: !920)
!920 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 4)
!921 = !DILocation(line: 517, column: 5, scope: !922)
!922 = !DILexicalBlockFile(scope: !923, file: !1, discriminator: 5)
!923 = distinct !DILexicalBlock(scope: !914, file: !1, line: 517, column: 5)
!924 = !DILocation(line: 517, column: 5, scope: !925)
!925 = !DILexicalBlockFile(scope: !923, file: !1, discriminator: 6)
!926 = !DILocation(line: 517, column: 5, scope: !927)
!927 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 7)
!928 = !DILocation(line: 517, column: 5, scope: !929)
!929 = !DILexicalBlockFile(scope: !930, file: !1, discriminator: 8)
!930 = distinct !DILexicalBlock(scope: !914, file: !1, line: 517, column: 5)
!931 = !DILocation(line: 517, column: 5, scope: !932)
!932 = !DILexicalBlockFile(scope: !933, file: !1, discriminator: 9)
!933 = distinct !DILexicalBlock(scope: !930, file: !1, line: 517, column: 5)
!934 = !DILocation(line: 517, column: 5, scope: !935)
!935 = !DILexicalBlockFile(scope: !933, file: !1, discriminator: 10)
!936 = !DILocation(line: 517, column: 5, scope: !937)
!937 = !DILexicalBlockFile(scope: !914, file: !1, discriminator: 11)
!938 = !DILocation(line: 518, column: 3, scope: !907)
!939 = !DILocation(line: 520, column: 18, scope: !455)
!940 = !DILocation(line: 520, column: 3, scope: !455)
!941 = !DILocation(line: 520, column: 12, scope: !455)
!942 = !DILocation(line: 520, column: 16, scope: !455)
!943 = !DILocation(line: 521, column: 22, scope: !455)
!944 = !DILocation(line: 521, column: 31, scope: !455)
!945 = !DILocation(line: 521, column: 3, scope: !455)
!946 = !DILocation(line: 521, column: 12, scope: !455)
!947 = !DILocation(line: 521, column: 20, scope: !455)
!948 = !DILocation(line: 523, column: 12, scope: !455)
!949 = !DILocation(line: 523, column: 3, scope: !455)
!950 = !DILocation(line: 524, column: 10, scope: !455)
!951 = !DILocation(line: 524, column: 3, scope: !455)
!952 = !DILocation(line: 527, column: 7, scope: !953)
!953 = distinct !DILexicalBlock(scope: !455, file: !1, line: 527, column: 7)
!954 = !DILocation(line: 527, column: 13, scope: !953)
!955 = !DILocation(line: 527, column: 7, scope: !455)
!956 = !DILocation(line: 528, column: 12, scope: !957)
!957 = distinct !DILexicalBlock(scope: !958, file: !1, line: 528, column: 5)
!958 = distinct !DILexicalBlock(scope: !953, file: !1, line: 527, column: 22)
!959 = !DILocation(line: 528, column: 10, scope: !957)
!960 = !DILocation(line: 528, column: 17, scope: !961)
!961 = !DILexicalBlockFile(scope: !962, file: !1, discriminator: 1)
!962 = distinct !DILexicalBlock(scope: !957, file: !1, line: 528, column: 5)
!963 = !DILocation(line: 528, column: 21, scope: !961)
!964 = !DILocation(line: 528, column: 19, scope: !961)
!965 = !DILocation(line: 528, column: 5, scope: !961)
!966 = !DILocation(line: 529, column: 11, scope: !967)
!967 = distinct !DILexicalBlock(scope: !968, file: !1, line: 529, column: 11)
!968 = distinct !DILexicalBlock(scope: !962, file: !1, line: 528, column: 39)
!969 = !DILocation(line: 529, column: 15, scope: !967)
!970 = !DILocation(line: 529, column: 24, scope: !967)
!971 = !DILocation(line: 529, column: 13, scope: !967)
!972 = !DILocation(line: 529, column: 11, scope: !968)
!973 = !DILocation(line: 530, column: 28, scope: !974)
!974 = distinct !DILexicalBlock(scope: !967, file: !1, line: 530, column: 13)
!975 = !DILocation(line: 530, column: 13, scope: !974)
!976 = !DILocation(line: 530, column: 22, scope: !974)
!977 = !DILocation(line: 530, column: 31, scope: !974)
!978 = !DILocation(line: 530, column: 37, scope: !974)
!979 = !DILocation(line: 530, column: 13, scope: !967)
!980 = !DILocation(line: 531, column: 11, scope: !974)
!981 = !DILocation(line: 530, column: 73, scope: !982)
!982 = !DILexicalBlockFile(scope: !974, file: !1, discriminator: 1)
!983 = !DILocation(line: 532, column: 17, scope: !984)
!984 = distinct !DILexicalBlock(scope: !968, file: !1, line: 532, column: 11)
!985 = !DILocation(line: 532, column: 11, scope: !984)
!986 = !DILocation(line: 532, column: 23, scope: !984)
!987 = !DILocation(line: 532, column: 11, scope: !968)
!988 = !DILocation(line: 533, column: 38, scope: !984)
!989 = !DILocation(line: 533, column: 32, scope: !984)
!990 = !DILocation(line: 533, column: 9, scope: !984)
!991 = !DILocation(line: 534, column: 17, scope: !992)
!992 = distinct !DILexicalBlock(scope: !968, file: !1, line: 534, column: 11)
!993 = !DILocation(line: 534, column: 11, scope: !992)
!994 = !DILocation(line: 534, column: 23, scope: !992)
!995 = !DILocation(line: 534, column: 11, scope: !968)
!996 = !DILocation(line: 535, column: 38, scope: !992)
!997 = !DILocation(line: 535, column: 32, scope: !992)
!998 = !DILocation(line: 535, column: 9, scope: !992)
!999 = !DILocation(line: 536, column: 5, scope: !968)
!1000 = !DILocation(line: 528, column: 35, scope: !1001)
!1001 = !DILexicalBlockFile(scope: !962, file: !1, discriminator: 2)
!1002 = !DILocation(line: 528, column: 5, scope: !1001)
!1003 = !DILocation(line: 537, column: 14, scope: !958)
!1004 = !DILocation(line: 537, column: 5, scope: !958)
!1005 = !DILocation(line: 538, column: 3, scope: !958)
!1006 = !DILocation(line: 540, column: 10, scope: !455)
!1007 = !DILocation(line: 540, column: 3, scope: !455)
!1008 = !DILocation(line: 542, column: 1, scope: !455)
!1009 = !DILocalVariable(name: "container", arg: 1, scope: !501, file: !1, line: 188, type: !472)
!1010 = !DILocation(line: 188, column: 57, scope: !501)
!1011 = !DILocalVariable(name: "fds", arg: 2, scope: !501, file: !1, line: 188, type: !452)
!1012 = !DILocation(line: 188, column: 72, scope: !501)
!1013 = !DILocalVariable(name: "mask", scope: !501, file: !1, line: 189, type: !116)
!1014 = !DILocation(line: 189, column: 7, scope: !501)
!1015 = !DILocalVariable(name: "fd", scope: !501, file: !1, line: 190, type: !116)
!1016 = !DILocation(line: 190, column: 7, scope: !501)
!1017 = !DILocation(line: 192, column: 8, scope: !501)
!1018 = !DILocation(line: 194, column: 11, scope: !501)
!1019 = !DILocation(line: 194, column: 22, scope: !501)
!1020 = !DILocation(line: 194, column: 30, scope: !501)
!1021 = !DILocation(line: 194, column: 28, scope: !501)
!1022 = !DILocation(line: 194, column: 3, scope: !501)
!1023 = !DILocation(line: 196, column: 5, scope: !1024)
!1024 = distinct !DILexicalBlock(scope: !501, file: !1, line: 194, column: 36)
!1025 = !DILocation(line: 199, column: 5, scope: !1024)
!1026 = !DILocation(line: 199, column: 5, scope: !1027)
!1027 = !DILexicalBlockFile(scope: !1024, file: !1, discriminator: 1)
!1028 = !DILocation(line: 199, column: 5, scope: !1029)
!1029 = !DILexicalBlockFile(scope: !1024, file: !1, discriminator: 2)
!1030 = !DILocation(line: 199, column: 5, scope: !1031)
!1031 = !DILexicalBlockFile(scope: !1024, file: !1, discriminator: 3)
!1032 = !DILocation(line: 200, column: 9, scope: !1033)
!1033 = distinct !DILexicalBlock(scope: !1024, file: !1, line: 200, column: 9)
!1034 = !DILocation(line: 200, column: 20, scope: !1033)
!1035 = !DILocation(line: 200, column: 25, scope: !1033)
!1036 = !DILocation(line: 200, column: 33, scope: !1033)
!1037 = !DILocation(line: 200, column: 38, scope: !1033)
!1038 = !DILocation(line: 200, column: 9, scope: !1024)
!1039 = !DILocation(line: 201, column: 7, scope: !1033)
!1040 = !DILocation(line: 203, column: 34, scope: !1033)
!1041 = !DILocation(line: 203, column: 14, scope: !1033)
!1042 = !DILocation(line: 203, column: 7, scope: !1033)
!1043 = !DILocation(line: 207, column: 9, scope: !1044)
!1044 = distinct !DILexicalBlock(scope: !1024, file: !1, line: 207, column: 9)
!1045 = !DILocation(line: 207, column: 20, scope: !1044)
!1046 = !DILocation(line: 207, column: 26, scope: !1044)
!1047 = !DILocation(line: 207, column: 9, scope: !1024)
!1048 = !DILocation(line: 208, column: 12, scope: !1044)
!1049 = !DILocation(line: 208, column: 23, scope: !1044)
!1050 = !DILocation(line: 208, column: 28, scope: !1044)
!1051 = !DILocation(line: 208, column: 10, scope: !1044)
!1052 = !DILocation(line: 208, column: 7, scope: !1044)
!1053 = !DILocation(line: 210, column: 12, scope: !1044)
!1054 = !DILocation(line: 210, column: 10, scope: !1044)
!1055 = !DILocation(line: 212, column: 9, scope: !1056)
!1056 = distinct !DILexicalBlock(scope: !1024, file: !1, line: 212, column: 9)
!1057 = !DILocation(line: 212, column: 12, scope: !1056)
!1058 = !DILocation(line: 212, column: 9, scope: !1024)
!1059 = !DILocation(line: 213, column: 7, scope: !1056)
!1060 = !DILocation(line: 215, column: 14, scope: !1024)
!1061 = !DILocation(line: 215, column: 5, scope: !1024)
!1062 = !DILocation(line: 215, column: 12, scope: !1024)
!1063 = !DILocation(line: 216, column: 5, scope: !1024)
!1064 = !DILocation(line: 219, column: 5, scope: !1024)
!1065 = !DILocation(line: 222, column: 1, scope: !501)
!1066 = !DILocalVariable(name: "handle", arg: 1, scope: !504, file: !1, line: 48, type: !273)
!1067 = !DILocation(line: 48, column: 35, scope: !504)
!1068 = !DILocalVariable(name: "signum", arg: 2, scope: !504, file: !1, line: 48, type: !116)
!1069 = !DILocation(line: 48, column: 47, scope: !504)
!1070 = !DILocalVariable(name: "process", scope: !504, file: !1, line: 49, type: !305)
!1071 = !DILocation(line: 49, column: 17, scope: !504)
!1072 = !DILocalVariable(name: "loop", scope: !504, file: !1, line: 50, type: !100)
!1073 = !DILocation(line: 50, column: 14, scope: !504)
!1074 = !DILocalVariable(name: "exit_status", scope: !504, file: !1, line: 51, type: !116)
!1075 = !DILocation(line: 51, column: 7, scope: !504)
!1076 = !DILocalVariable(name: "term_signal", scope: !504, file: !1, line: 52, type: !116)
!1077 = !DILocation(line: 52, column: 7, scope: !504)
!1078 = !DILocalVariable(name: "status", scope: !504, file: !1, line: 53, type: !116)
!1079 = !DILocation(line: 53, column: 7, scope: !504)
!1080 = !DILocalVariable(name: "pid", scope: !504, file: !1, line: 54, type: !636)
!1081 = !DILocation(line: 54, column: 9, scope: !504)
!1082 = !DILocalVariable(name: "pending", scope: !504, file: !1, line: 55, type: !301)
!1083 = !DILocation(line: 55, column: 9, scope: !504)
!1084 = !DILocalVariable(name: "q", scope: !504, file: !1, line: 56, type: !300)
!1085 = !DILocation(line: 56, column: 10, scope: !504)
!1086 = !DILocalVariable(name: "h", scope: !504, file: !1, line: 57, type: !300)
!1087 = !DILocation(line: 57, column: 10, scope: !504)
!1088 = !DILocation(line: 59, column: 3, scope: !504)
!1089 = !DILocation(line: 59, column: 3, scope: !1090)
!1090 = !DILexicalBlockFile(scope: !504, file: !1, discriminator: 1)
!1091 = !DILocation(line: 59, column: 3, scope: !1092)
!1092 = !DILexicalBlockFile(scope: !504, file: !1, discriminator: 2)
!1093 = !DILocation(line: 59, column: 3, scope: !1094)
!1094 = !DILexicalBlockFile(scope: !504, file: !1, discriminator: 3)
!1095 = !DILocation(line: 61, column: 3, scope: !504)
!1096 = !DILocation(line: 61, column: 3, scope: !1097)
!1097 = !DILexicalBlockFile(scope: !1098, file: !1, discriminator: 1)
!1098 = distinct !DILexicalBlock(scope: !504, file: !1, line: 61, column: 3)
!1099 = !DILocation(line: 62, column: 10, scope: !504)
!1100 = !DILocation(line: 62, column: 18, scope: !504)
!1101 = !DILocation(line: 62, column: 8, scope: !504)
!1102 = !DILocation(line: 64, column: 8, scope: !504)
!1103 = !DILocation(line: 64, column: 14, scope: !504)
!1104 = !DILocation(line: 64, column: 5, scope: !504)
!1105 = !DILocation(line: 65, column: 7, scope: !504)
!1106 = !DILocation(line: 65, column: 5, scope: !504)
!1107 = !DILocation(line: 66, column: 3, scope: !504)
!1108 = !DILocation(line: 66, column: 10, scope: !1090)
!1109 = !DILocation(line: 66, column: 15, scope: !1090)
!1110 = !DILocation(line: 66, column: 12, scope: !1090)
!1111 = !DILocation(line: 66, column: 3, scope: !1090)
!1112 = !DILocation(line: 67, column: 15, scope: !1113)
!1113 = distinct !DILexicalBlock(scope: !504, file: !1, line: 66, column: 18)
!1114 = !DILocation(line: 67, column: 13, scope: !1113)
!1115 = !DILocation(line: 68, column: 9, scope: !1113)
!1116 = !DILocation(line: 68, column: 7, scope: !1113)
!1117 = !DILocation(line: 70, column: 5, scope: !1113)
!1118 = !DILocation(line: 71, column: 21, scope: !1113)
!1119 = !DILocation(line: 71, column: 30, scope: !1113)
!1120 = !DILocation(line: 71, column: 13, scope: !1113)
!1121 = !DILocation(line: 71, column: 11, scope: !1113)
!1122 = !DILocation(line: 71, column: 7, scope: !1113)
!1123 = !DILocation(line: 72, column: 12, scope: !1113)
!1124 = !DILocation(line: 72, column: 16, scope: !1113)
!1125 = !DILocation(line: 72, column: 22, scope: !1113)
!1126 = !DILocation(line: 72, column: 25, scope: !1127)
!1127 = !DILexicalBlockFile(scope: !1113, file: !1, discriminator: 1)
!1128 = !DILocation(line: 72, column: 31, scope: !1127)
!1129 = !DILocation(line: 71, column: 7, scope: !1127)
!1130 = !DILocation(line: 74, column: 9, scope: !1131)
!1131 = distinct !DILexicalBlock(scope: !1113, file: !1, line: 74, column: 9)
!1132 = !DILocation(line: 74, column: 13, scope: !1131)
!1133 = !DILocation(line: 74, column: 9, scope: !1113)
!1134 = !DILocation(line: 75, column: 7, scope: !1131)
!1135 = !DILocation(line: 77, column: 9, scope: !1136)
!1136 = distinct !DILexicalBlock(scope: !1113, file: !1, line: 77, column: 9)
!1137 = !DILocation(line: 77, column: 13, scope: !1136)
!1138 = !DILocation(line: 77, column: 9, scope: !1113)
!1139 = !DILocation(line: 78, column: 11, scope: !1140)
!1140 = distinct !DILexicalBlock(scope: !1141, file: !1, line: 78, column: 11)
!1141 = distinct !DILexicalBlock(scope: !1136, file: !1, line: 77, column: 20)
!1142 = !DILocation(line: 78, column: 17, scope: !1140)
!1143 = !DILocation(line: 78, column: 11, scope: !1141)
!1144 = !DILocation(line: 79, column: 9, scope: !1140)
!1145 = !DILocation(line: 80, column: 7, scope: !1141)
!1146 = !DILocation(line: 83, column: 23, scope: !1113)
!1147 = !DILocation(line: 83, column: 5, scope: !1113)
!1148 = !DILocation(line: 83, column: 14, scope: !1113)
!1149 = !DILocation(line: 83, column: 21, scope: !1113)
!1150 = !DILocation(line: 84, column: 5, scope: !1113)
!1151 = !DILocation(line: 84, column: 5, scope: !1152)
!1152 = !DILexicalBlockFile(scope: !1153, file: !1, discriminator: 1)
!1153 = distinct !DILexicalBlock(scope: !1113, file: !1, line: 84, column: 5)
!1154 = !DILocation(line: 85, column: 5, scope: !1113)
!1155 = !DILocation(line: 85, column: 5, scope: !1156)
!1156 = !DILexicalBlockFile(scope: !1157, file: !1, discriminator: 1)
!1157 = distinct !DILexicalBlock(scope: !1113, file: !1, line: 85, column: 5)
!1158 = !DILocation(line: 66, column: 3, scope: !1092)
!1159 = !DILocation(line: 88, column: 5, scope: !504)
!1160 = !DILocation(line: 89, column: 7, scope: !504)
!1161 = !DILocation(line: 89, column: 5, scope: !504)
!1162 = !DILocation(line: 90, column: 3, scope: !504)
!1163 = !DILocation(line: 90, column: 10, scope: !1090)
!1164 = !DILocation(line: 90, column: 15, scope: !1090)
!1165 = !DILocation(line: 90, column: 12, scope: !1090)
!1166 = !DILocation(line: 90, column: 3, scope: !1090)
!1167 = !DILocation(line: 91, column: 15, scope: !1168)
!1168 = distinct !DILexicalBlock(scope: !504, file: !1, line: 90, column: 18)
!1169 = !DILocation(line: 91, column: 13, scope: !1168)
!1170 = !DILocation(line: 92, column: 9, scope: !1168)
!1171 = !DILocation(line: 92, column: 7, scope: !1168)
!1172 = !DILocation(line: 94, column: 5, scope: !1168)
!1173 = !DILocation(line: 94, column: 5, scope: !1174)
!1174 = !DILexicalBlockFile(scope: !1175, file: !1, discriminator: 1)
!1175 = distinct !DILexicalBlock(scope: !1168, file: !1, line: 94, column: 5)
!1176 = !DILocation(line: 95, column: 5, scope: !1168)
!1177 = !DILocation(line: 95, column: 5, scope: !1178)
!1178 = !DILexicalBlockFile(scope: !1179, file: !1, discriminator: 1)
!1179 = distinct !DILexicalBlock(scope: !1168, file: !1, line: 95, column: 5)
!1180 = !DILocation(line: 96, column: 5, scope: !1168)
!1181 = !DILocation(line: 96, column: 5, scope: !1182)
!1182 = !DILexicalBlockFile(scope: !1183, file: !1, discriminator: 1)
!1183 = distinct !DILexicalBlock(scope: !1168, file: !1, line: 96, column: 5)
!1184 = !DILocation(line: 96, column: 5, scope: !1185)
!1185 = !DILexicalBlockFile(scope: !1183, file: !1, discriminator: 2)
!1186 = !DILocation(line: 96, column: 5, scope: !1187)
!1187 = !DILexicalBlockFile(scope: !1183, file: !1, discriminator: 3)
!1188 = !DILocation(line: 96, column: 5, scope: !1189)
!1189 = !DILexicalBlockFile(scope: !1183, file: !1, discriminator: 4)
!1190 = !DILocation(line: 96, column: 5, scope: !1191)
!1191 = !DILexicalBlockFile(scope: !1192, file: !1, discriminator: 5)
!1192 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 96, column: 5)
!1193 = !DILocation(line: 96, column: 5, scope: !1194)
!1194 = !DILexicalBlockFile(scope: !1192, file: !1, discriminator: 6)
!1195 = !DILocation(line: 96, column: 5, scope: !1196)
!1196 = !DILexicalBlockFile(scope: !1183, file: !1, discriminator: 7)
!1197 = !DILocation(line: 96, column: 5, scope: !1198)
!1198 = !DILexicalBlockFile(scope: !1199, file: !1, discriminator: 8)
!1199 = distinct !DILexicalBlock(scope: !1183, file: !1, line: 96, column: 5)
!1200 = !DILocation(line: 96, column: 5, scope: !1201)
!1201 = !DILexicalBlockFile(scope: !1202, file: !1, discriminator: 9)
!1202 = distinct !DILexicalBlock(scope: !1199, file: !1, line: 96, column: 5)
!1203 = !DILocation(line: 96, column: 5, scope: !1204)
!1204 = !DILexicalBlockFile(scope: !1202, file: !1, discriminator: 10)
!1205 = !DILocation(line: 96, column: 5, scope: !1206)
!1206 = !DILexicalBlockFile(scope: !1183, file: !1, discriminator: 11)
!1207 = !DILocation(line: 98, column: 9, scope: !1208)
!1208 = distinct !DILexicalBlock(scope: !1168, file: !1, line: 98, column: 9)
!1209 = !DILocation(line: 98, column: 18, scope: !1208)
!1210 = !DILocation(line: 98, column: 26, scope: !1208)
!1211 = !DILocation(line: 98, column: 9, scope: !1168)
!1212 = !DILocation(line: 99, column: 7, scope: !1208)
!1213 = !DILocation(line: 101, column: 17, scope: !1168)
!1214 = !DILocation(line: 102, column: 9, scope: !1215)
!1215 = distinct !DILexicalBlock(scope: !1168, file: !1, line: 102, column: 9)
!1216 = !DILocation(line: 102, column: 9, scope: !1168)
!1217 = !DILocation(line: 103, column: 21, scope: !1215)
!1218 = !DILocation(line: 103, column: 19, scope: !1215)
!1219 = !DILocation(line: 103, column: 7, scope: !1215)
!1220 = !DILocation(line: 105, column: 17, scope: !1168)
!1221 = !DILocation(line: 106, column: 9, scope: !1222)
!1222 = distinct !DILexicalBlock(scope: !1168, file: !1, line: 106, column: 9)
!1223 = !DILocation(line: 106, column: 9, scope: !1168)
!1224 = !DILocation(line: 107, column: 21, scope: !1222)
!1225 = !DILocation(line: 107, column: 19, scope: !1222)
!1226 = !DILocation(line: 107, column: 7, scope: !1222)
!1227 = !DILocation(line: 109, column: 5, scope: !1168)
!1228 = !DILocation(line: 109, column: 14, scope: !1168)
!1229 = !DILocation(line: 109, column: 22, scope: !1168)
!1230 = !DILocation(line: 109, column: 31, scope: !1168)
!1231 = !DILocation(line: 109, column: 44, scope: !1168)
!1232 = !DILocation(line: 90, column: 3, scope: !1092)
!1233 = !DILocation(line: 111, column: 3, scope: !504)
!1234 = !DILocation(line: 111, column: 3, scope: !1090)
!1235 = !DILocation(line: 111, column: 3, scope: !1092)
!1236 = !DILocation(line: 111, column: 3, scope: !1094)
!1237 = !DILocation(line: 112, column: 1, scope: !504)
!1238 = !DILocalVariable(name: "options", arg: 1, scope: !505, file: !1, line: 278, type: !458)
!1239 = !DILocation(line: 278, column: 64, scope: !505)
!1240 = !DILocalVariable(name: "stdio_count", arg: 2, scope: !505, file: !1, line: 279, type: !116)
!1241 = !DILocation(line: 279, column: 40, scope: !505)
!1242 = !DILocalVariable(name: "pipes", arg: 3, scope: !505, file: !1, line: 280, type: !508)
!1243 = !DILocation(line: 280, column: 42, scope: !505)
!1244 = !DILocalVariable(name: "error_fd", arg: 4, scope: !505, file: !1, line: 281, type: !116)
!1245 = !DILocation(line: 281, column: 40, scope: !505)
!1246 = !DILocalVariable(name: "close_fd", scope: !505, file: !1, line: 282, type: !116)
!1247 = !DILocation(line: 282, column: 7, scope: !505)
!1248 = !DILocalVariable(name: "use_fd", scope: !505, file: !1, line: 283, type: !116)
!1249 = !DILocation(line: 283, column: 7, scope: !505)
!1250 = !DILocalVariable(name: "fd", scope: !505, file: !1, line: 284, type: !116)
!1251 = !DILocation(line: 284, column: 7, scope: !505)
!1252 = !DILocation(line: 286, column: 7, scope: !1253)
!1253 = distinct !DILexicalBlock(scope: !505, file: !1, line: 286, column: 7)
!1254 = !DILocation(line: 286, column: 16, scope: !1253)
!1255 = !DILocation(line: 286, column: 22, scope: !1253)
!1256 = !DILocation(line: 286, column: 7, scope: !505)
!1257 = !DILocation(line: 287, column: 5, scope: !1253)
!1258 = !DILocation(line: 293, column: 11, scope: !1259)
!1259 = distinct !DILexicalBlock(scope: !505, file: !1, line: 293, column: 3)
!1260 = !DILocation(line: 293, column: 8, scope: !1259)
!1261 = !DILocation(line: 293, column: 16, scope: !1262)
!1262 = !DILexicalBlockFile(scope: !1263, file: !1, discriminator: 1)
!1263 = distinct !DILexicalBlock(scope: !1259, file: !1, line: 293, column: 3)
!1264 = !DILocation(line: 293, column: 21, scope: !1262)
!1265 = !DILocation(line: 293, column: 19, scope: !1262)
!1266 = !DILocation(line: 293, column: 3, scope: !1262)
!1267 = !DILocation(line: 294, column: 20, scope: !1268)
!1268 = distinct !DILexicalBlock(scope: !1263, file: !1, line: 293, column: 40)
!1269 = !DILocation(line: 294, column: 14, scope: !1268)
!1270 = !DILocation(line: 294, column: 12, scope: !1268)
!1271 = !DILocation(line: 295, column: 9, scope: !1272)
!1272 = distinct !DILexicalBlock(scope: !1268, file: !1, line: 295, column: 9)
!1273 = !DILocation(line: 295, column: 16, scope: !1272)
!1274 = !DILocation(line: 295, column: 20, scope: !1272)
!1275 = !DILocation(line: 295, column: 23, scope: !1276)
!1276 = !DILexicalBlockFile(scope: !1272, file: !1, discriminator: 1)
!1277 = !DILocation(line: 295, column: 33, scope: !1276)
!1278 = !DILocation(line: 295, column: 30, scope: !1276)
!1279 = !DILocation(line: 295, column: 9, scope: !1276)
!1280 = !DILocation(line: 296, column: 7, scope: !1272)
!1281 = !DILocation(line: 297, column: 26, scope: !1268)
!1282 = !DILocation(line: 297, column: 43, scope: !1268)
!1283 = !DILocation(line: 297, column: 20, scope: !1268)
!1284 = !DILocation(line: 297, column: 11, scope: !1268)
!1285 = !DILocation(line: 297, column: 5, scope: !1268)
!1286 = !DILocation(line: 297, column: 18, scope: !1268)
!1287 = !DILocation(line: 298, column: 15, scope: !1288)
!1288 = distinct !DILexicalBlock(scope: !1268, file: !1, line: 298, column: 9)
!1289 = !DILocation(line: 298, column: 9, scope: !1288)
!1290 = !DILocation(line: 298, column: 22, scope: !1288)
!1291 = !DILocation(line: 298, column: 9, scope: !1268)
!1292 = !DILocation(line: 299, column: 21, scope: !1293)
!1293 = distinct !DILexicalBlock(scope: !1288, file: !1, line: 298, column: 29)
!1294 = !DILocation(line: 299, column: 32, scope: !1293)
!1295 = !DILocation(line: 299, column: 31, scope: !1293)
!1296 = !DILocation(line: 299, column: 7, scope: !1297)
!1297 = !DILexicalBlockFile(scope: !1293, file: !1, discriminator: 1)
!1298 = !DILocation(line: 300, column: 7, scope: !1293)
!1299 = !DILocation(line: 302, column: 3, scope: !1268)
!1300 = !DILocation(line: 293, column: 36, scope: !1301)
!1301 = !DILexicalBlockFile(scope: !1263, file: !1, discriminator: 2)
!1302 = !DILocation(line: 293, column: 3, scope: !1301)
!1303 = !DILocation(line: 304, column: 11, scope: !1304)
!1304 = distinct !DILexicalBlock(scope: !505, file: !1, line: 304, column: 3)
!1305 = !DILocation(line: 304, column: 8, scope: !1304)
!1306 = !DILocation(line: 304, column: 16, scope: !1307)
!1307 = !DILexicalBlockFile(scope: !1308, file: !1, discriminator: 1)
!1308 = distinct !DILexicalBlock(scope: !1304, file: !1, line: 304, column: 3)
!1309 = !DILocation(line: 304, column: 21, scope: !1307)
!1310 = !DILocation(line: 304, column: 19, scope: !1307)
!1311 = !DILocation(line: 304, column: 3, scope: !1307)
!1312 = !DILocation(line: 305, column: 22, scope: !1313)
!1313 = distinct !DILexicalBlock(scope: !1308, file: !1, line: 304, column: 40)
!1314 = !DILocation(line: 305, column: 16, scope: !1313)
!1315 = !DILocation(line: 305, column: 14, scope: !1313)
!1316 = !DILocation(line: 306, column: 20, scope: !1313)
!1317 = !DILocation(line: 306, column: 14, scope: !1313)
!1318 = !DILocation(line: 306, column: 12, scope: !1313)
!1319 = !DILocation(line: 308, column: 9, scope: !1320)
!1320 = distinct !DILexicalBlock(scope: !1313, file: !1, line: 308, column: 9)
!1321 = !DILocation(line: 308, column: 16, scope: !1320)
!1322 = !DILocation(line: 308, column: 9, scope: !1313)
!1323 = !DILocation(line: 309, column: 11, scope: !1324)
!1324 = distinct !DILexicalBlock(scope: !1325, file: !1, line: 309, column: 11)
!1325 = distinct !DILexicalBlock(scope: !1320, file: !1, line: 308, column: 21)
!1326 = !DILocation(line: 309, column: 14, scope: !1324)
!1327 = !DILocation(line: 309, column: 11, scope: !1325)
!1328 = !DILocation(line: 310, column: 9, scope: !1324)
!1329 = !DILocation(line: 315, column: 36, scope: !1330)
!1330 = distinct !DILexicalBlock(scope: !1324, file: !1, line: 311, column: 12)
!1331 = !DILocation(line: 315, column: 39, scope: !1330)
!1332 = !DILocation(line: 315, column: 18, scope: !1330)
!1333 = !DILocation(line: 315, column: 16, scope: !1330)
!1334 = !DILocation(line: 316, column: 20, scope: !1330)
!1335 = !DILocation(line: 316, column: 18, scope: !1330)
!1336 = !DILocation(line: 318, column: 13, scope: !1337)
!1337 = distinct !DILexicalBlock(scope: !1330, file: !1, line: 318, column: 13)
!1338 = !DILocation(line: 318, column: 20, scope: !1337)
!1339 = !DILocation(line: 318, column: 13, scope: !1330)
!1340 = !DILocation(line: 319, column: 25, scope: !1341)
!1341 = distinct !DILexicalBlock(scope: !1337, file: !1, line: 318, column: 27)
!1342 = !DILocation(line: 319, column: 36, scope: !1341)
!1343 = !DILocation(line: 319, column: 35, scope: !1341)
!1344 = !DILocation(line: 319, column: 11, scope: !1345)
!1345 = !DILexicalBlockFile(scope: !1341, file: !1, discriminator: 1)
!1346 = !DILocation(line: 320, column: 11, scope: !1341)
!1347 = !DILocation(line: 323, column: 5, scope: !1325)
!1348 = !DILocation(line: 325, column: 9, scope: !1349)
!1349 = distinct !DILexicalBlock(scope: !1313, file: !1, line: 325, column: 9)
!1350 = !DILocation(line: 325, column: 15, scope: !1349)
!1351 = !DILocation(line: 325, column: 12, scope: !1349)
!1352 = !DILocation(line: 325, column: 9, scope: !1313)
!1353 = !DILocation(line: 326, column: 25, scope: !1349)
!1354 = !DILocation(line: 326, column: 7, scope: !1349)
!1355 = !DILocation(line: 328, column: 17, scope: !1349)
!1356 = !DILocation(line: 328, column: 25, scope: !1349)
!1357 = !DILocation(line: 328, column: 12, scope: !1349)
!1358 = !DILocation(line: 328, column: 10, scope: !1349)
!1359 = !DILocation(line: 330, column: 9, scope: !1360)
!1360 = distinct !DILexicalBlock(scope: !1313, file: !1, line: 330, column: 9)
!1361 = !DILocation(line: 330, column: 12, scope: !1360)
!1362 = !DILocation(line: 330, column: 9, scope: !1313)
!1363 = !DILocation(line: 331, column: 21, scope: !1364)
!1364 = distinct !DILexicalBlock(scope: !1360, file: !1, line: 330, column: 19)
!1365 = !DILocation(line: 331, column: 32, scope: !1364)
!1366 = !DILocation(line: 331, column: 31, scope: !1364)
!1367 = !DILocation(line: 331, column: 7, scope: !1368)
!1368 = !DILexicalBlockFile(scope: !1364, file: !1, discriminator: 1)
!1369 = !DILocation(line: 332, column: 7, scope: !1364)
!1370 = !DILocation(line: 335, column: 9, scope: !1371)
!1371 = distinct !DILexicalBlock(scope: !1313, file: !1, line: 335, column: 9)
!1372 = !DILocation(line: 335, column: 12, scope: !1371)
!1373 = !DILocation(line: 335, column: 9, scope: !1313)
!1374 = !DILocation(line: 336, column: 26, scope: !1371)
!1375 = !DILocation(line: 336, column: 7, scope: !1371)
!1376 = !DILocation(line: 338, column: 9, scope: !1377)
!1377 = distinct !DILexicalBlock(scope: !1313, file: !1, line: 338, column: 9)
!1378 = !DILocation(line: 338, column: 21, scope: !1377)
!1379 = !DILocation(line: 338, column: 18, scope: !1377)
!1380 = !DILocation(line: 338, column: 9, scope: !1313)
!1381 = !DILocation(line: 339, column: 17, scope: !1377)
!1382 = !DILocation(line: 339, column: 7, scope: !1377)
!1383 = !DILocation(line: 340, column: 3, scope: !1313)
!1384 = !DILocation(line: 304, column: 36, scope: !1385)
!1385 = !DILexicalBlockFile(scope: !1308, file: !1, discriminator: 2)
!1386 = !DILocation(line: 304, column: 3, scope: !1385)
!1387 = !DILocation(line: 342, column: 11, scope: !1388)
!1388 = distinct !DILexicalBlock(scope: !505, file: !1, line: 342, column: 3)
!1389 = !DILocation(line: 342, column: 8, scope: !1388)
!1390 = !DILocation(line: 342, column: 16, scope: !1391)
!1391 = !DILexicalBlockFile(scope: !1392, file: !1, discriminator: 1)
!1392 = distinct !DILexicalBlock(scope: !1388, file: !1, line: 342, column: 3)
!1393 = !DILocation(line: 342, column: 21, scope: !1391)
!1394 = !DILocation(line: 342, column: 19, scope: !1391)
!1395 = !DILocation(line: 342, column: 3, scope: !1391)
!1396 = !DILocation(line: 343, column: 20, scope: !1397)
!1397 = distinct !DILexicalBlock(scope: !1392, file: !1, line: 342, column: 40)
!1398 = !DILocation(line: 343, column: 14, scope: !1397)
!1399 = !DILocation(line: 343, column: 12, scope: !1397)
!1400 = !DILocation(line: 345, column: 9, scope: !1401)
!1401 = distinct !DILexicalBlock(scope: !1397, file: !1, line: 345, column: 9)
!1402 = !DILocation(line: 345, column: 19, scope: !1401)
!1403 = !DILocation(line: 345, column: 16, scope: !1401)
!1404 = !DILocation(line: 345, column: 9, scope: !1397)
!1405 = !DILocation(line: 346, column: 17, scope: !1401)
!1406 = !DILocation(line: 346, column: 7, scope: !1401)
!1407 = !DILocation(line: 347, column: 3, scope: !1397)
!1408 = !DILocation(line: 342, column: 36, scope: !1409)
!1409 = !DILexicalBlockFile(scope: !1392, file: !1, discriminator: 2)
!1410 = !DILocation(line: 342, column: 3, scope: !1409)
!1411 = !DILocation(line: 349, column: 7, scope: !1412)
!1412 = distinct !DILexicalBlock(scope: !505, file: !1, line: 349, column: 7)
!1413 = !DILocation(line: 349, column: 16, scope: !1412)
!1414 = !DILocation(line: 349, column: 20, scope: !1412)
!1415 = !DILocation(line: 349, column: 28, scope: !1412)
!1416 = !DILocation(line: 349, column: 37, scope: !1417)
!1417 = !DILexicalBlockFile(scope: !1412, file: !1, discriminator: 1)
!1418 = !DILocation(line: 349, column: 46, scope: !1417)
!1419 = !DILocation(line: 349, column: 31, scope: !1417)
!1420 = !DILocation(line: 349, column: 7, scope: !1417)
!1421 = !DILocation(line: 350, column: 19, scope: !1422)
!1422 = distinct !DILexicalBlock(scope: !1412, file: !1, line: 349, column: 52)
!1423 = !DILocation(line: 350, column: 30, scope: !1422)
!1424 = !DILocation(line: 350, column: 29, scope: !1422)
!1425 = !DILocation(line: 350, column: 5, scope: !1426)
!1426 = !DILexicalBlockFile(scope: !1422, file: !1, discriminator: 1)
!1427 = !DILocation(line: 351, column: 5, scope: !1422)
!1428 = !DILocation(line: 354, column: 7, scope: !1429)
!1429 = distinct !DILexicalBlock(scope: !505, file: !1, line: 354, column: 7)
!1430 = !DILocation(line: 354, column: 16, scope: !1429)
!1431 = !DILocation(line: 354, column: 22, scope: !1429)
!1432 = !DILocation(line: 354, column: 7, scope: !505)
!1433 = !DILocation(line: 362, column: 5, scope: !1434)
!1434 = distinct !DILexicalBlock(scope: !1429, file: !1, line: 354, column: 65)
!1435 = !DILocalVariable(name: "_saved_errno", scope: !1436, file: !1, line: 362, type: !116)
!1436 = distinct !DILexicalBlock(scope: !1434, file: !1, line: 362, column: 5)
!1437 = !DILocation(line: 362, column: 5, scope: !1436)
!1438 = !DILocation(line: 362, column: 5, scope: !1439)
!1439 = !DILexicalBlockFile(scope: !1436, file: !1, discriminator: 1)
!1440 = !DILocation(line: 362, column: 5, scope: !1441)
!1441 = !DILexicalBlockFile(scope: !1442, file: !1, discriminator: 2)
!1442 = distinct !DILexicalBlock(scope: !1436, file: !1, line: 362, column: 5)
!1443 = !DILocation(line: 362, column: 5, scope: !1444)
!1444 = !DILexicalBlockFile(scope: !1436, file: !1, discriminator: 3)
!1445 = !DILocation(line: 363, column: 3, scope: !1434)
!1446 = !DILocation(line: 365, column: 8, scope: !1447)
!1447 = distinct !DILexicalBlock(scope: !505, file: !1, line: 365, column: 7)
!1448 = !DILocation(line: 365, column: 17, scope: !1447)
!1449 = !DILocation(line: 365, column: 23, scope: !1447)
!1450 = !DILocation(line: 365, column: 44, scope: !1447)
!1451 = !DILocation(line: 365, column: 54, scope: !1452)
!1452 = !DILexicalBlockFile(scope: !1447, file: !1, discriminator: 1)
!1453 = !DILocation(line: 365, column: 63, scope: !1452)
!1454 = !DILocation(line: 365, column: 47, scope: !1452)
!1455 = !DILocation(line: 365, column: 7, scope: !1452)
!1456 = !DILocation(line: 366, column: 19, scope: !1457)
!1457 = distinct !DILexicalBlock(scope: !1447, file: !1, line: 365, column: 69)
!1458 = !DILocation(line: 366, column: 30, scope: !1457)
!1459 = !DILocation(line: 366, column: 29, scope: !1457)
!1460 = !DILocation(line: 366, column: 5, scope: !1461)
!1461 = !DILexicalBlockFile(scope: !1457, file: !1, discriminator: 1)
!1462 = !DILocation(line: 367, column: 5, scope: !1457)
!1463 = !DILocation(line: 370, column: 8, scope: !1464)
!1464 = distinct !DILexicalBlock(scope: !505, file: !1, line: 370, column: 7)
!1465 = !DILocation(line: 370, column: 17, scope: !1464)
!1466 = !DILocation(line: 370, column: 23, scope: !1464)
!1467 = !DILocation(line: 370, column: 44, scope: !1464)
!1468 = !DILocation(line: 370, column: 54, scope: !1469)
!1469 = !DILexicalBlockFile(scope: !1464, file: !1, discriminator: 1)
!1470 = !DILocation(line: 370, column: 63, scope: !1469)
!1471 = !DILocation(line: 370, column: 47, scope: !1469)
!1472 = !DILocation(line: 370, column: 7, scope: !1469)
!1473 = !DILocation(line: 371, column: 19, scope: !1474)
!1474 = distinct !DILexicalBlock(scope: !1464, file: !1, line: 370, column: 69)
!1475 = !DILocation(line: 371, column: 30, scope: !1474)
!1476 = !DILocation(line: 371, column: 29, scope: !1474)
!1477 = !DILocation(line: 371, column: 5, scope: !1478)
!1478 = !DILexicalBlockFile(scope: !1474, file: !1, discriminator: 1)
!1479 = !DILocation(line: 372, column: 5, scope: !1474)
!1480 = !DILocation(line: 375, column: 7, scope: !1481)
!1481 = distinct !DILexicalBlock(scope: !505, file: !1, line: 375, column: 7)
!1482 = !DILocation(line: 375, column: 16, scope: !1481)
!1483 = !DILocation(line: 375, column: 20, scope: !1481)
!1484 = !DILocation(line: 375, column: 7, scope: !505)
!1485 = !DILocation(line: 376, column: 15, scope: !1486)
!1486 = distinct !DILexicalBlock(scope: !1481, file: !1, line: 375, column: 29)
!1487 = !DILocation(line: 376, column: 24, scope: !1486)
!1488 = !DILocation(line: 376, column: 13, scope: !1486)
!1489 = !DILocation(line: 377, column: 3, scope: !1486)
!1490 = !DILocation(line: 379, column: 10, scope: !505)
!1491 = !DILocation(line: 379, column: 19, scope: !505)
!1492 = !DILocation(line: 379, column: 25, scope: !505)
!1493 = !DILocation(line: 379, column: 34, scope: !505)
!1494 = !DILocation(line: 379, column: 3, scope: !505)
!1495 = !DILocation(line: 380, column: 17, scope: !505)
!1496 = !DILocation(line: 380, column: 28, scope: !505)
!1497 = !DILocation(line: 380, column: 27, scope: !505)
!1498 = !DILocation(line: 380, column: 3, scope: !1499)
!1499 = !DILexicalBlockFile(scope: !505, file: !1, discriminator: 1)
!1500 = !DILocation(line: 381, column: 3, scope: !505)
!1501 = !DILocation(line: 382, column: 1, scope: !505)
!1502 = !DILocalVariable(name: "container", arg: 1, scope: !512, file: !1, line: 225, type: !472)
!1503 = !DILocation(line: 225, column: 58, scope: !512)
!1504 = !DILocalVariable(name: "pipefds", arg: 2, scope: !512, file: !1, line: 226, type: !452)
!1505 = !DILocation(line: 226, column: 40, scope: !512)
!1506 = !DILocalVariable(name: "writable", arg: 3, scope: !512, file: !1, line: 227, type: !116)
!1507 = !DILocation(line: 227, column: 40, scope: !512)
!1508 = !DILocalVariable(name: "flags", scope: !512, file: !1, line: 228, type: !116)
!1509 = !DILocation(line: 228, column: 7, scope: !512)
!1510 = !DILocalVariable(name: "err", scope: !512, file: !1, line: 229, type: !116)
!1511 = !DILocation(line: 229, column: 7, scope: !512)
!1512 = !DILocation(line: 231, column: 9, scope: !1513)
!1513 = distinct !DILexicalBlock(scope: !512, file: !1, line: 231, column: 7)
!1514 = !DILocation(line: 231, column: 20, scope: !1513)
!1515 = !DILocation(line: 231, column: 26, scope: !1513)
!1516 = !DILocation(line: 231, column: 44, scope: !1513)
!1517 = !DILocation(line: 231, column: 47, scope: !1518)
!1518 = !DILexicalBlockFile(scope: !1513, file: !1, discriminator: 1)
!1519 = !DILocation(line: 231, column: 58, scope: !1518)
!1520 = !DILocation(line: 231, column: 7, scope: !1518)
!1521 = !DILocation(line: 232, column: 5, scope: !1513)
!1522 = !DILocation(line: 234, column: 19, scope: !512)
!1523 = !DILocation(line: 234, column: 9, scope: !512)
!1524 = !DILocation(line: 234, column: 7, scope: !512)
!1525 = !DILocation(line: 235, column: 7, scope: !1526)
!1526 = distinct !DILexicalBlock(scope: !512, file: !1, line: 235, column: 7)
!1527 = !DILocation(line: 235, column: 11, scope: !1526)
!1528 = !DILocation(line: 235, column: 7, scope: !512)
!1529 = !DILocation(line: 236, column: 5, scope: !1526)
!1530 = !DILocation(line: 238, column: 3, scope: !512)
!1531 = !DILocation(line: 238, column: 14, scope: !512)
!1532 = !DILocation(line: 239, column: 16, scope: !512)
!1533 = !DILocation(line: 239, column: 3, scope: !512)
!1534 = !DILocation(line: 241, column: 7, scope: !1535)
!1535 = distinct !DILexicalBlock(scope: !512, file: !1, line: 241, column: 7)
!1536 = !DILocation(line: 241, column: 18, scope: !1535)
!1537 = !DILocation(line: 241, column: 23, scope: !1535)
!1538 = !DILocation(line: 241, column: 31, scope: !1535)
!1539 = !DILocation(line: 241, column: 36, scope: !1535)
!1540 = !DILocation(line: 241, column: 53, scope: !1535)
!1541 = !DILocation(line: 242, column: 20, scope: !1535)
!1542 = !DILocation(line: 242, column: 31, scope: !1535)
!1543 = !DILocation(line: 242, column: 36, scope: !1535)
!1544 = !DILocation(line: 242, column: 45, scope: !1535)
!1545 = !DILocation(line: 242, column: 7, scope: !1535)
!1546 = !DILocation(line: 241, column: 7, scope: !1547)
!1547 = !DILexicalBlockFile(scope: !512, file: !1, discriminator: 1)
!1548 = !DILocation(line: 243, column: 11, scope: !1535)
!1549 = !DILocation(line: 243, column: 5, scope: !1535)
!1550 = !DILocation(line: 244, column: 12, scope: !1551)
!1551 = distinct !DILexicalBlock(scope: !1535, file: !1, line: 244, column: 12)
!1552 = !DILocation(line: 244, column: 12, scope: !1535)
!1553 = !DILocation(line: 245, column: 11, scope: !1551)
!1554 = !DILocation(line: 245, column: 5, scope: !1551)
!1555 = !DILocation(line: 247, column: 11, scope: !1551)
!1556 = !DILocation(line: 249, column: 26, scope: !512)
!1557 = !DILocation(line: 249, column: 37, scope: !512)
!1558 = !DILocation(line: 249, column: 42, scope: !512)
!1559 = !DILocation(line: 249, column: 50, scope: !512)
!1560 = !DILocation(line: 249, column: 62, scope: !512)
!1561 = !DILocation(line: 249, column: 10, scope: !512)
!1562 = !DILocation(line: 249, column: 3, scope: !512)
!1563 = !DILocation(line: 250, column: 1, scope: !512)
!1564 = !DILocalVariable(name: "container", arg: 1, scope: !515, file: !1, line: 253, type: !472)
!1565 = !DILocation(line: 253, column: 60, scope: !515)
!1566 = !DILocation(line: 254, column: 9, scope: !1567)
!1567 = distinct !DILexicalBlock(scope: !515, file: !1, line: 254, column: 7)
!1568 = !DILocation(line: 254, column: 20, scope: !1567)
!1569 = !DILocation(line: 254, column: 26, scope: !1567)
!1570 = !DILocation(line: 254, column: 7, scope: !515)
!1571 = !DILocation(line: 254, column: 45, scope: !1572)
!1572 = !DILexicalBlockFile(scope: !1567, file: !1, discriminator: 1)
!1573 = !DILocation(line: 255, column: 34, scope: !515)
!1574 = !DILocation(line: 255, column: 45, scope: !515)
!1575 = !DILocation(line: 255, column: 50, scope: !515)
!1576 = !DILocation(line: 255, column: 3, scope: !515)
!1577 = !DILocation(line: 256, column: 1, scope: !515)
!1578 = !DILocation(line: 256, column: 1, scope: !1579)
!1579 = !DILexicalBlockFile(scope: !515, file: !1, discriminator: 1)
!1580 = !DILocalVariable(name: "process", arg: 1, scope: !492, file: !1, line: 545, type: !305)
!1581 = !DILocation(line: 545, column: 35, scope: !492)
!1582 = !DILocalVariable(name: "signum", arg: 2, scope: !492, file: !1, line: 545, type: !116)
!1583 = !DILocation(line: 545, column: 48, scope: !492)
!1584 = !DILocation(line: 546, column: 18, scope: !492)
!1585 = !DILocation(line: 546, column: 27, scope: !492)
!1586 = !DILocation(line: 546, column: 32, scope: !492)
!1587 = !DILocation(line: 546, column: 10, scope: !492)
!1588 = !DILocation(line: 546, column: 3, scope: !492)
!1589 = !DILocalVariable(name: "pid", arg: 1, scope: !495, file: !1, line: 550, type: !116)
!1590 = !DILocation(line: 550, column: 17, scope: !495)
!1591 = !DILocalVariable(name: "signum", arg: 2, scope: !495, file: !1, line: 550, type: !116)
!1592 = !DILocation(line: 550, column: 26, scope: !495)
!1593 = !DILocation(line: 551, column: 12, scope: !1594)
!1594 = distinct !DILexicalBlock(scope: !495, file: !1, line: 551, column: 7)
!1595 = !DILocation(line: 551, column: 17, scope: !1594)
!1596 = !DILocation(line: 551, column: 7, scope: !1594)
!1597 = !DILocation(line: 551, column: 7, scope: !495)
!1598 = !DILocation(line: 552, column: 13, scope: !1594)
!1599 = !DILocation(line: 552, column: 12, scope: !1594)
!1600 = !DILocation(line: 552, column: 5, scope: !1594)
!1601 = !DILocation(line: 554, column: 5, scope: !1594)
!1602 = !DILocation(line: 555, column: 1, scope: !495)
!1603 = !DILocalVariable(name: "handle", arg: 1, scope: !498, file: !1, line: 558, type: !305)
!1604 = !DILocation(line: 558, column: 38, scope: !498)
!1605 = !DILocation(line: 559, column: 3, scope: !498)
!1606 = !DILocation(line: 559, column: 3, scope: !1607)
!1607 = !DILexicalBlockFile(scope: !1608, file: !1, discriminator: 1)
!1608 = distinct !DILexicalBlock(scope: !498, file: !1, line: 559, column: 3)
!1609 = !DILocation(line: 560, column: 3, scope: !498)
!1610 = !DILocation(line: 560, column: 3, scope: !1611)
!1611 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 1)
!1612 = distinct !DILexicalBlock(scope: !498, file: !1, line: 560, column: 3)
!1613 = !DILocation(line: 560, column: 3, scope: !1614)
!1614 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 2)
!1615 = !DILocation(line: 560, column: 3, scope: !1616)
!1616 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 3)
!1617 = !DILocation(line: 560, column: 3, scope: !1618)
!1618 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 4)
!1619 = !DILocation(line: 560, column: 3, scope: !1620)
!1620 = !DILexicalBlockFile(scope: !1621, file: !1, discriminator: 5)
!1621 = distinct !DILexicalBlock(scope: !1612, file: !1, line: 560, column: 3)
!1622 = !DILocation(line: 560, column: 3, scope: !1623)
!1623 = !DILexicalBlockFile(scope: !1621, file: !1, discriminator: 6)
!1624 = !DILocation(line: 560, column: 3, scope: !1625)
!1625 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 7)
!1626 = !DILocation(line: 560, column: 3, scope: !1627)
!1627 = !DILexicalBlockFile(scope: !1628, file: !1, discriminator: 8)
!1628 = distinct !DILexicalBlock(scope: !1612, file: !1, line: 560, column: 3)
!1629 = !DILocation(line: 560, column: 3, scope: !1630)
!1630 = !DILexicalBlockFile(scope: !1631, file: !1, discriminator: 9)
!1631 = distinct !DILexicalBlock(scope: !1628, file: !1, line: 560, column: 3)
!1632 = !DILocation(line: 560, column: 3, scope: !1633)
!1633 = !DILexicalBlockFile(scope: !1631, file: !1, discriminator: 10)
!1634 = !DILocation(line: 560, column: 3, scope: !1635)
!1635 = !DILexicalBlockFile(scope: !1612, file: !1, discriminator: 11)
!1636 = !DILocation(line: 561, column: 7, scope: !1637)
!1637 = distinct !DILexicalBlock(scope: !498, file: !1, line: 561, column: 7)
!1638 = !DILocation(line: 561, column: 7, scope: !498)
!1639 = !DILocation(line: 562, column: 21, scope: !1637)
!1640 = !DILocation(line: 562, column: 29, scope: !1637)
!1641 = !DILocation(line: 562, column: 35, scope: !1637)
!1642 = !DILocation(line: 562, column: 5, scope: !1637)
!1643 = !DILocation(line: 563, column: 1, scope: !498)
!1644 = !DILocalVariable(name: "fd", arg: 1, scope: !509, file: !1, line: 259, type: !116)
!1645 = !DILocation(line: 259, column: 31, scope: !509)
!1646 = !DILocalVariable(name: "val", arg: 2, scope: !509, file: !1, line: 259, type: !116)
!1647 = !DILocation(line: 259, column: 39, scope: !509)
!1648 = !DILocalVariable(name: "n", scope: !509, file: !1, line: 260, type: !429)
!1649 = !DILocation(line: 260, column: 11, scope: !509)
!1650 = !DILocation(line: 262, column: 3, scope: !509)
!1651 = !DILocation(line: 263, column: 15, scope: !509)
!1652 = !DILocation(line: 263, column: 19, scope: !509)
!1653 = !DILocation(line: 263, column: 9, scope: !509)
!1654 = !DILocation(line: 263, column: 7, scope: !509)
!1655 = !DILocation(line: 263, column: 5, scope: !509)
!1656 = !DILocation(line: 264, column: 10, scope: !509)
!1657 = !DILocation(line: 264, column: 12, scope: !509)
!1658 = !DILocation(line: 264, column: 18, scope: !509)
!1659 = !DILocation(line: 264, column: 21, scope: !1660)
!1660 = !DILexicalBlockFile(scope: !509, file: !1, discriminator: 1)
!1661 = !DILocation(line: 264, column: 27, scope: !1660)
!1662 = !DILocation(line: 263, column: 5, scope: !1660)
!1663 = !DILocation(line: 266, column: 7, scope: !1664)
!1664 = distinct !DILexicalBlock(scope: !509, file: !1, line: 266, column: 7)
!1665 = !DILocation(line: 266, column: 9, scope: !1664)
!1666 = !DILocation(line: 266, column: 15, scope: !1664)
!1667 = !DILocation(line: 266, column: 18, scope: !1668)
!1668 = !DILexicalBlockFile(scope: !1664, file: !1, discriminator: 1)
!1669 = !DILocation(line: 266, column: 24, scope: !1668)
!1670 = !DILocation(line: 266, column: 7, scope: !1668)
!1671 = !DILocation(line: 267, column: 5, scope: !1664)
!1672 = !DILocation(line: 269, column: 3, scope: !509)
!1673 = !DILocation(line: 269, column: 3, scope: !1660)
!1674 = !DILocation(line: 269, column: 3, scope: !1675)
!1675 = !DILexicalBlockFile(scope: !509, file: !1, discriminator: 2)
!1676 = !DILocation(line: 269, column: 3, scope: !1677)
!1677 = !DILexicalBlockFile(scope: !509, file: !1, discriminator: 3)
!1678 = !DILocation(line: 270, column: 1, scope: !509)
